/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file UsTrigger.h
///@brief定义了类CUsTrigger(触发器类，将订单/成交/资金/持仓等信息通过TResult流发送出去)
///@history 
///20130105	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////
#ifndef _US_TRIGGER_H_20130105
#define _US_TRIGGER_H_20130105

#include "UsScheduler.h"

template <typename TF,typename TW,typename T, typename BaseTrigger,bool bInsertSensitive = true, bool bUpdateSensitive = true, bool bDeleteSensitive = false>
class CUsTrigger:public BaseTrigger
{
public:
	///构造方法
	CUsTrigger(CUsScheduler *pMdbSch, const char *pszObjectName, CMemoryDB *pDB, bool bCheckSyncStatus)
	{
		m_pUsSch = pMdbSch;
		m_pszObjectName = pszObjectName;
		m_pDB = pDB;
		m_bCheckSyncStatus = bCheckSyncStatus;	
	}
	
	///析构方法
	virtual ~CUsTrigger(void)
	{
	}
	
	///加入后触发
	///@param TW 要加入的TW数据
	virtual void commitAdd(T* pData)
	{
		if (bInsertSensitive)
		{
			if (!m_bCheckSyncStatus || getDataSyncStatus() == DS_Synchronized)
			{
				m_pUsSch->Dispatch(m_pszObjectName, &TF::m_Describe, pData, MDB_INSERT);
			}
		}
	}
	
	///更新后触发
	///@param T 被刷新的T
	///@param TW 新的值
	virtual void commitUpdate(T* pData, TW *pWriteable)
	{
		if (bUpdateSensitive)
		{
			if (!m_bCheckSyncStatus || getDataSyncStatus() == DS_Synchronized)
			{
				m_pUsSch->Dispatch(m_pszObjectName, &TF::m_Describe, pData, MDB_UPDATE);
			}			
		}
	}
	
	///删除后触发
	///@param T 要删除的T
	virtual void commitRemove(TW* pWriteable)
	{
		if (bDeleteSensitive)
		{
			if (!m_bCheckSyncStatus || getDataSyncStatus() == DS_Synchronized)
			{
				m_pUsSch->Dispatch(m_pszObjectName, &TF::m_Describe, pWriteable, MDB_DELETE);
			}			
		}
	}

protected:
	CDataSyncStatusType getDataSyncStatus()
	{
		CDataSyncStatusType retDataSyncStatus=DS_Asynchronous;
		CDataSyncStatus* pDataSyncStatus=m_pDB->m_DataSyncStatusFactory->getFirst();
		m_pDB->m_DataSyncStatusFactory->endGet();
		if (pDataSyncStatus!=NULL)
		{
			retDataSyncStatus=pDataSyncStatus->DataSyncStatus;
		}
		return retDataSyncStatus;
	}

protected:
	CUsScheduler *m_pUsSch;	//调度器
	const char *m_pszObjectName;
	CMemoryDB *m_pDB;
	bool m_bCheckSyncStatus;	
};

/*	longqy 20130904
//	这个触发器，添加在出入金内存数据库表上，每当有出入金变化，则触发这个触发器，发送回报给用户。
*/
class CUsDepositTrigger:public CInvestorAccountDepositCommitTrigger
{
public:
	///构造方法
	CUsDepositTrigger(CUsScheduler *pMdbSch, const char *pszObjectName, CMemoryDB *pDB, bool bCheckSyncStatus)
	{
		m_pUsSch = pMdbSch;
		m_pszObjectName = pszObjectName;
		m_pDB = pDB;
		m_bCheckSyncStatus = bCheckSyncStatus;	
	}
	
	///析构方法
	virtual ~CUsDepositTrigger(void)
	{
	}

	
	///加入后触发
	///@param pData 要发送的出入金通知数据
	virtual void commitAdd(CInvestorAccountDeposit* pData)
	{
		CInvestorAccountDepositNtfField theDepositField;
		copyInvestorAccountDepositNtfEntity(&theDepositField,pData);
		
		CInvestorAccount *pInvestorAccount = NULL;
		pInvestorAccount=m_pDB->m_InvestorAccountFactory->findByBrokerIDAccountID(theDepositField.BrokerID,theDepositField.AccountID);	

		if (pInvestorAccount == NULL)
		{
			REPORT_EVENT(LOG_CRITICAL,"CUsDepositTriggerError","Can not find investor account deposit for BrokerID： %s AccountID：%s",theDepositField.BrokerID.getValue(),theDepositField.AccountID.getValue());
		}
		else
		{
			theDepositField.Balance   = pInvestorAccount->Balance;
			theDepositField.Available = pInvestorAccount->Available;
			
			REPORT_EVENT(LOG_INFO, "CUsDepositTrigger", "Investor Deposit, BrokerID=[%s],InvestorID=[%s],Amount=[%d],AmountDirection=[%d]",	theDepositField.BrokerID.getValue(),theDepositField.InvestorID.getValue(),
			theDepositField.Amount.getValue(),theDepositField.AmountDirection.getValue());
			
			if (!m_bCheckSyncStatus || getDataSyncStatus() == DS_Synchronized)
			{
				CUserInvestor * p_UserInvestor = m_pDB->m_UserInvestorFactory->startFindByBrokerIDInvestorID(theDepositField.BrokerID,theDepositField.InvestorID);
				while (p_UserInvestor)
				{	// 对同一个InvestorID，对应着多个 UserID；每个UserID，都需要发送出入金通知
					theDepositField.UserID = p_UserInvestor->UserID;
					m_pUsSch->InvestorAccountDepositNotify(&CInvestorAccountDepositNtfField::m_Describe, &theDepositField);
					p_UserInvestor = m_pDB->m_UserInvestorFactory->findNextByBrokerIDInvestorID();
				}
				m_pDB->m_UserInvestorFactory->endFindByBrokerIDInvestorID();
			}
		}
	}
	
protected:

	CDataSyncStatusType getDataSyncStatus()
	{
		CDataSyncStatusType retDataSyncStatus=DS_Asynchronous;
		CDataSyncStatus* pDataSyncStatus=m_pDB->m_DataSyncStatusFactory->getFirst();
		m_pDB->m_DataSyncStatusFactory->endGet();
		if (pDataSyncStatus!=NULL)
		{
			retDataSyncStatus=pDataSyncStatus->DataSyncStatus;
		}
		return retDataSyncStatus;
	}
	
	void copyInvestorAccountDepositNtfEntity(CInvestorAccountDepositNtfField* target,CInvestorAccountDeposit* source)
	{
		(target)->BrokerID = (source)->BrokerID;	
		(target)->AccountSeqNo = (source)->AccountSeqNo;	
		(target)->AccountID = (source)->AccountID;
		(target)->InvestorID = (source)->InvestorID;
		(target)->Amount = (source)->Amount;
		(target)->AmountDirection = (source)->AmountDirection;
	}

	
protected:
	CUsScheduler *m_pUsSch;	//调度器
	const char *m_pszObjectName;
	CMemoryDB *m_pDB;
	bool m_bCheckSyncStatus;	
};

#endif
