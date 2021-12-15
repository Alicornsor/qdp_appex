/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file MemoryTradeEngine.h
///@brief��������CMemoryTradeEngine
///@history 
///20060118	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef TRADEQUERYENGINE_H
#define TRADEQUERYENGINE_H

#include "Engine.h"

//#include "CInitServiceCheckImpl.h" //longqy
//#include "InitServiceXTPLink.h" //longqy

#include "TradingQueryServiceImpl.h"
#include "TradingQueryServiceXTPLink.h"

#include "TradingResultImpl.h"
#include "TradingResultServiceXtpLink.h"

#include "CConfig.h"
#include "Flow.h"
#include "FibServerApi.h"
#include "CMemoryDB.h"
#include "XtpData.h"



class CUsScheduler
{
public:
	CUsScheduler(CFlow *pMemChangeFlow);
	virtual ~CUsScheduler();
	virtual void Dispatch(const char *pszObjectName, CFieldDescribe *pDescirbe, const void *pData, CMdbActionTypeType nActionType);
	
private:	
	CXTPPackage	*m_pPubMessage;
	CFlow *m_pMemChangeFlow;	
};


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

#define DEFINE_US_MDB_TRIGGER(objtype, objname)		\
	typedef CUsTrigger<C##objtype##Field,CWriteable##objname,C##objname,C##objname##CommitTrigger > C##objname##Trigger; \
C##objname##Trigger  *m_p##objname##Trigger;

#define DEFINE_US_MDB_DELETE_TRIGGER(objtype, objname)		\
	typedef CUsTrigger<C##objtype##Field,CWriteable##objname,C##objname,C##objname##CommitTrigger,true,true,true > C##objname##Trigger; \
	C##objname##Trigger  *m_p##objname##Trigger;


/////////////////////////////////////////////////////////////////////////
///CMemoryTradeEngine��һ�������ڴ���Ϣ���͵Ľ������棬�����˽����õ��ڴ�
///��������
///@author	xuzh
///@version	1.0,20060118
/////////////////////////////////////////////////////////////////////////
class CTradingQueryEngine: public CEngine
{
public:
	///���캯��
	///@param	pConfig	����������Ҫʹ�õ�����
	///@param	pApi	���ڷ��ز�ѯ�����API
	///@param	recovery	�Ƿ�ʹ�ûָ�ģʽ
	///@param	verbose	true��ʾҪ��������flase��ʾ��Ҫ������
	CTradingQueryEngine(CConfig *pConfig,CFibServerApi *pApi,CFlow * pSendFlow,CUsScheduler *pMDBScheduler,bool verbose=true);
	
	virtual ~CTradingQueryEngine(void);	

private:
	DEFINE_US_MDB_TRIGGER(Order, Order);//ί��
	DEFINE_US_MDB_TRIGGER(Trade, Trade);//�ɽ�
	DEFINE_US_MDB_TRIGGER(InvestorAccount, InvestorAccount);//�ʽ�
	DEFINE_US_MDB_TRIGGER(InvestorPosition, InvestorPosition);//�ֲ�
	DEFINE_US_MDB_TRIGGER(User, User);//�޸��û�����
	DEFINE_US_MDB_DELETE_TRIGGER(UserSession, UserSession);//UserSession
	DEFINE_US_MDB_TRIGGER(Instrument, Instrument);//��Լ��
	DEFINE_US_MDB_TRIGGER(MarketData, MarketData);
	DEFINE_US_MDB_TRIGGER(Exchange, Exchange);//��������
	//DEFINE_US_MDB_TRIGGER(ExchTimeDiff, ExchTimeDiff);//������ʱ��ƫ��
	//	DEFINE_US_MDB_TRIGGER(SystemStatus, SystemStatus);//ϵͳ״̬��
	DEFINE_US_MDB_TRIGGER(OrderInsertFailed, OrderInsertFailed);//����  liumeng 20140817
	DEFINE_US_MDB_TRIGGER(ClientTradingID, ClientTradingID);
	DEFINE_US_MDB_TRIGGER(InvestorMargin, InvestorMargin);
	DEFINE_US_MDB_TRIGGER(InvestorFee, InvestorFee);
	DEFINE_US_MDB_TRIGGER(Investor, Investor);
	DEFINE_US_MDB_TRIGGER(UserInvestor, UserInvestor);
	DEFINE_US_MDB_TRIGGER(Seat, Seat);
	DEFINE_US_MDB_TRIGGER(DataSyncStatus,DataSyncStatus);
	DEFINE_US_MDB_TRIGGER(SGEDeferRate,SGEDeferRate);
	DEFINE_US_MDB_DELETE_TRIGGER(InvestorTradingRight, InvestorTradingRight);
	DEFINE_US_MDB_TRIGGER(InvestorOptionFee, InvestorOptionFee);
	DEFINE_US_MDB_TRIGGER(SystemInfo, SystemInfo);

	IServiceResponser	 *m_pServiceResponser;
	IServiceResponser    *m_pRequestResponser;
	CFibServerApi *m_pServerApi;

	CTradingQueryServiceXtpLink *m_pTradingQueryXTPLink;
	CTradingQueryImpl			*m_pTradingQueryService;
	
	CTradingResultServiceXtpLink *m_pTradingResultServiceXtpLink;
	CTradingResultImpl			*m_pTradingResultService;

	CUsScheduler *m_pMDBScheduler;
	
};

#endif
