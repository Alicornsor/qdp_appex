/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file MemoryTradeEngine.h
///@briefʵ������CMemoryTradeEngine
///@history 
///20060118	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#include "TradingQueryEngine.h"
#include "XTPResponser.h"
#include "XtpPackageDesc.h"
#include "NULLResponser.h"
#include "CachedFileFlow.h"


#define NEW_MDB_TRIGGER(objtype, objname, checksync)												\
	m_p##objtype##Trigger = new C##objtype##Trigger(pMDBScheduler,objname,m_pDB,checksync);	\
	m_pDB->m_##objtype##Factory->addCommitTrigger(m_p##objtype##Trigger);


CUsScheduler::CUsScheduler(CFlow *pMemChangeFlow)
{
	m_pPubMessage = new CXTPPackage();
	m_pPubMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	m_pPubMessage->PreparePublish(TID_NtfMemtableChange);
	
	// longqy 20130910 ԭ��ֻ��һ�������󣬷����ڴ����ݿ�仯�ı������һ�������󣬷��ͳ����֪ͨ��ǰ�á�
	m_pMemChangeFlow = pMemChangeFlow;
}

CUsScheduler::~CUsScheduler()
{
	if(m_pPubMessage!=NULL)
	{
		delete m_pPubMessage;
		m_pPubMessage=NULL;
	}
}

void CUsScheduler::Dispatch(const char *pszObjectName, CFieldDescribe *pDescirbe, const void *pData, CMdbActionTypeType nActionType)
{
	CMemtableChangeField fld;
	fld.MemTableName=pszObjectName;//�����ڴ��
	//���ݱ仯����
	switch(nActionType)
	{
	case MDB_INSERT:
		{
			fld.MemtableChangeType=MTC_INSERT;
			break;
		}
	case MDB_UPDATE:
		{
			fld.MemtableChangeType=MTC_UPDATE;
			break;
		}
	case MDB_DELETE:
		{
			fld.MemtableChangeType=MTC_DELETE;
			break;
		}
	case MDB_COMMIT:
		{
			fld.MemtableChangeType=MTC_COMMIT;
			break;
		}
	default:
		{
			//���ش��󣬲�֧�ֵ����ݿ��������
			printf("��֧�ֵı仯����\n");
			return;
		}
	}	
	m_pPubMessage->PreparePublish(TID_NtfMemtableChange);
	XTP_ADD_FIELD(m_pPubMessage,&fld);
	m_pPubMessage->AddField(pDescirbe,(void *)pData);//���ӿɱ���Ϣ��
	m_pPubMessage->MakePackage();
	//m_pResultFlow->Append(m_pPubMessage->Address(),m_pPubMessage->Length());
	// longqy 20130910 ʵ����ԭ�������ڴ��������ֻ���޸��˴������������
	m_pMemChangeFlow->Append(m_pPubMessage->Address(),m_pPubMessage->Length());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CTradingQueryEngine::CTradingQueryEngine(CConfig *pConfig,CFibServerApi *pApi,CFlow * pSendFlow,CUsScheduler *pMDBScheduler, bool verbose):CEngine(pConfig,true)
{
	m_pServiceResponser = new CNullResponser(NULL);
	m_pRequestResponser = new CXTPRequestResponser(pApi);

	m_pMDBScheduler = pMDBScheduler;
	
	///��ʼ�����м���
	runLevel = atoi(pConfig->getConfig("RunLevel"));

	//��ʼ����ѯ����
	if (m_verbose)
	{
		PROCESS_LOG0("create trading query service\n");
	}
	//m_pTradingQueryService = new CTradingQueryImpl(m_pDB,m_pErrorEngine,pConfig);
	m_pTradingQueryService = new CTradingQueryImpl(m_pDB,m_pErrorEngine);
	m_pTradingQueryXTPLink = new CTradingQueryServiceXtpLink(m_pTradingQueryService,m_pErrorEngine,m_pRequestResponser,m_pDB,m_verbose);
	addServiceXTPLink(m_pTradingQueryXTPLink);

	bool m_md5Password=false;
	if (!strcmp(currentConfig->getConfig("MD5Password"),"yes"))
	{
		m_md5Password=true;
	}

	m_pTradingResultService = new CTradingResultImpl(m_pDB,m_pErrorEngine,pConfig,pSendFlow);
	m_pTradingResultServiceXtpLink = new CTradingResultServiceXtpLink(m_pTradingResultService,m_pErrorEngine,m_pRequestResponser,m_pDB,m_verbose,m_md5Password);
	addServiceXTPLink(m_pTradingResultServiceXtpLink);
	
	m_pServerApi = pApi;

	//����Trigger,������������д���ڴ��仯��Ϣ,by wangwei,20130105
	NEW_MDB_TRIGGER(Order, "t_Order",false);
	NEW_MDB_TRIGGER(Trade, "t_Trade",false);
	NEW_MDB_TRIGGER(InvestorAccount, "t_InvestorAccount",false);
	NEW_MDB_TRIGGER(InvestorPosition, "t_InvestorPosition",false);
	NEW_MDB_TRIGGER(User,"t_User",false);
	NEW_MDB_TRIGGER(UserSession,"t_UserSession",false);
	NEW_MDB_TRIGGER(Instrument,"t_Instrument",false);//�Ѻ�Լ�ͽ����յı仯Ҳ�ͳ�ȥ,wangwei,20130502
	NEW_MDB_TRIGGER(MarketData,"t_MarketData",false);
	NEW_MDB_TRIGGER(Exchange,"t_Exchange",false);
	//NEW_MDB_TRIGGER(ExchTimeDiff,"t_ExchangeTimeDiff",false);
	NEW_MDB_TRIGGER(OrderInsertFailed,"t_OrderInsertFailed",false);
	NEW_MDB_TRIGGER(ClientTradingID,"t_ClientTradingID",false);
	NEW_MDB_TRIGGER(InvestorMargin,"t_InvestorMargin",false);
	NEW_MDB_TRIGGER(InvestorFee,"t_InvestorFee",false);
	NEW_MDB_TRIGGER(Investor,"t_Investor",false);
	NEW_MDB_TRIGGER(UserInvestor,"t_UserInvestor",false);
	NEW_MDB_TRIGGER(Seat,"t_Seat",false);
	NEW_MDB_TRIGGER(DataSyncStatus,"t_DataSyncStatus",false);
	NEW_MDB_TRIGGER(SGEDeferRate,"t_SGEDeferRate",false);
	NEW_MDB_TRIGGER(InvestorTradingRight,"t_InvestorTradingRight",false);
	NEW_MDB_TRIGGER(InvestorOptionFee,"t_InvestorOptionFee",false);
	NEW_MDB_TRIGGER(SystemInfo,"t_SystemInfo",false);
}
	
CTradingQueryEngine::~CTradingQueryEngine(void)
{
	//������ѯ����
	if (m_verbose)
	{
		PROCESS_LOG0("destroy trading query service\n");
	}
	removeServiceXTPLink(m_pTradingQueryXTPLink);
	delete m_pTradingQueryXTPLink;
	delete m_pTradingQueryService;

	if (m_verbose)
	{
		PROCESS_LOG0("destroy dbmt service\n");
	}

	//����trade����
//	if (m_verbose)
//	{
//		PROCESS_LOG0("destroy trade service\n");
//	}
	delete m_pServiceResponser;
	delete m_pRequestResponser;
}
