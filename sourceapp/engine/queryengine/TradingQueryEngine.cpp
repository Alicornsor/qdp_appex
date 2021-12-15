/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file MemoryTradeEngine.h
///@brief实现了类CMemoryTradeEngine
///@history 
///20060118	xuzh		创建该文件
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
	
	// longqy 20130910 原来只有一个流对象，发送内存数据库变化的表。现添加一个流对象，发送出入金通知给前置。
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
	fld.MemTableName=pszObjectName;//操作内存表
	//数据变化类型
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
			//严重错误，不支持的数据库操作类型
			printf("不支持的变化类型\n");
			return;
		}
	}	
	m_pPubMessage->PreparePublish(TID_NtfMemtableChange);
	XTP_ADD_FIELD(m_pPubMessage,&fld);
	m_pPubMessage->AddField(pDescirbe,(void *)pData);//增加可变消息域
	m_pPubMessage->MakePackage();
	//m_pResultFlow->Append(m_pPubMessage->Address(),m_pPubMessage->Length());
	// longqy 20130910 实际上原来就是内存流，这次只是修改了传入参数的名字
	m_pMemChangeFlow->Append(m_pPubMessage->Address(),m_pPubMessage->Length());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CTradingQueryEngine::CTradingQueryEngine(CConfig *pConfig,CFibServerApi *pApi,CFlow * pSendFlow,CUsScheduler *pMDBScheduler, bool verbose):CEngine(pConfig,true)
{
	m_pServiceResponser = new CNullResponser(NULL);
	m_pRequestResponser = new CXTPRequestResponser(pApi);

	m_pMDBScheduler = pMDBScheduler;
	
	///初始化运行级别
	runLevel = atoi(pConfig->getConfig("RunLevel"));

	//初始化查询服务
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

	//创建Trigger,用于向结果流中写入内存表变化消息,by wangwei,20130105
	NEW_MDB_TRIGGER(Order, "t_Order",false);
	NEW_MDB_TRIGGER(Trade, "t_Trade",false);
	NEW_MDB_TRIGGER(InvestorAccount, "t_InvestorAccount",false);
	NEW_MDB_TRIGGER(InvestorPosition, "t_InvestorPosition",false);
	NEW_MDB_TRIGGER(User,"t_User",false);
	NEW_MDB_TRIGGER(UserSession,"t_UserSession",false);
	NEW_MDB_TRIGGER(Instrument,"t_Instrument",false);//把合约和交易日的变化也送出去,wangwei,20130502
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
	//结束查询服务
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

	//结束trade服务
//	if (m_verbose)
//	{
//		PROCESS_LOG0("destroy trade service\n");
//	}
	delete m_pServiceResponser;
	delete m_pRequestResponser;
}
