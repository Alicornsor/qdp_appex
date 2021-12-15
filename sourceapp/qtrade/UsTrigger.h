/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file UsTrigger.h
///@brief��������CUsTrigger(�������࣬������/�ɽ�/�ʽ�/�ֲֵ���Ϣͨ��TResult�����ͳ�ȥ)
///@history 
///20130105	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////
#ifndef _US_TRIGGER_H_20130105
#define _US_TRIGGER_H_20130105

#include "UsScheduler.h"

template <typename TF,typename TW,typename T, typename BaseTrigger,bool bInsertSensitive = true, bool bUpdateSensitive = true, bool bDeleteSensitive = false>
class CUsTrigger:public BaseTrigger
{
public:
	///���췽��
	CUsTrigger(CUsScheduler *pMdbSch, const char *pszObjectName, CMemoryDB *pDB, bool bCheckSyncStatus)
	{
		m_pUsSch = pMdbSch;
		m_pszObjectName = pszObjectName;
		m_pDB = pDB;
		m_bCheckSyncStatus = bCheckSyncStatus;	
	}
	
	///��������
	virtual ~CUsTrigger(void)
	{
	}
	
	///����󴥷�
	///@param TW Ҫ�����TW����
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
	
	///���º󴥷�
	///@param T ��ˢ�µ�T
	///@param TW �µ�ֵ
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
	
	///ɾ���󴥷�
	///@param T Ҫɾ����T
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
	CUsScheduler *m_pUsSch;	//������
	const char *m_pszObjectName;
	CMemoryDB *m_pDB;
	bool m_bCheckSyncStatus;	
};

/*	longqy 20130904
//	���������������ڳ�����ڴ����ݿ���ϣ�ÿ���г����仯���򴥷���������������ͻر����û���
*/
class CUsDepositTrigger:public CInvestorAccountDepositCommitTrigger
{
public:
	///���췽��
	CUsDepositTrigger(CUsScheduler *pMdbSch, const char *pszObjectName, CMemoryDB *pDB, bool bCheckSyncStatus)
	{
		m_pUsSch = pMdbSch;
		m_pszObjectName = pszObjectName;
		m_pDB = pDB;
		m_bCheckSyncStatus = bCheckSyncStatus;	
	}
	
	///��������
	virtual ~CUsDepositTrigger(void)
	{
	}

	
	///����󴥷�
	///@param pData Ҫ���͵ĳ����֪ͨ����
	virtual void commitAdd(CInvestorAccountDeposit* pData)
	{
		CInvestorAccountDepositNtfField theDepositField;
		copyInvestorAccountDepositNtfEntity(&theDepositField,pData);
		
		CInvestorAccount *pInvestorAccount = NULL;
		pInvestorAccount=m_pDB->m_InvestorAccountFactory->findByBrokerIDAccountID(theDepositField.BrokerID,theDepositField.AccountID);	

		if (pInvestorAccount == NULL)
		{
			REPORT_EVENT(LOG_CRITICAL,"CUsDepositTriggerError","Can not find investor account deposit for BrokerID�� %s AccountID��%s",theDepositField.BrokerID.getValue(),theDepositField.AccountID.getValue());
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
				{	// ��ͬһ��InvestorID����Ӧ�Ŷ�� UserID��ÿ��UserID������Ҫ���ͳ����֪ͨ
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
	CUsScheduler *m_pUsSch;	//������
	const char *m_pszObjectName;
	CMemoryDB *m_pDB;
	bool m_bCheckSyncStatus;	
};

#endif
