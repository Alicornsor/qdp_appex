/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file KernelTradeEngine.cpp
///@brief实现了类CKernelTradeEngine
///@history 
///20130703	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "KernelTradeEngine.h"
#include "XtpPackageDesc.h"
#include "UFEntityCopy.h"
#include "XTPResponser.h"

#define NEW_MDB_TRIGGER(objtype, objname, checksync)												\
	m_p##objtype##Trigger = new C##objtype##Trigger(pMDBScheduler,objname,m_pDB,checksync);	\
	m_pDB->m_##objtype##Factory->addCommitTrigger(m_p##objtype##Trigger);

CKernelTradeEngine::CKernelTradeEngine(CConfig *pConfig,CFlow *pTradeResult):CEngine(pConfig,true)
{
	m_pTradeResult=pTradeResult;
	m_nLifeCycleID=0;
	m_nUpCount=0;
	CHandleNotify *pHandleNotify = new CHandleNotify(m_pDB,m_pErrorEngine,pConfig,pTradeResult);
	m_pServiceResponser=new CXTPResponser(pTradeResult);
	//初始化login服务
	if (m_verbose)
	{
		PROCESS_LOG0("create login service\n");
	}
	m_pLoginService=new CLoginServiceImpl(m_pDB,m_pErrorEngine);
	m_pLoginServiceXTPLink=new CLoginServiceXTPLink(m_pLoginService,m_pErrorEngine,m_pServiceResponser,m_verbose);
	addServiceXTPLink(m_pLoginServiceXTPLink);

	//初始化上场服务
	m_pNullResponser = new CNullResponser(NULL);
	if (m_verbose)
	{
		PROCESS_LOG0("create init service\n");
	}
	m_pInitService=new CInitServiceCheckImpl(m_pDB,m_pErrorEngine,pConfig,pHandleNotify);
	m_pInitServiceXTPLink=new CInitServiceXTPLink(m_pInitService,m_pErrorEngine,m_pNullResponser,pTradeResult,m_verbose);
	addServiceXTPLink(m_pInitServiceXTPLink);	

	//初始化交易服务
	if (m_verbose)
	{
		PROCESS_LOG0("create trade service\n");
	}
	m_pTradeService=new CTradeServiceImpl(m_pDB,m_pErrorEngine,pConfig,pTradeResult);
	m_pTradeServiceXTPLink=new CTradeServiceXTPLink(m_pTradeService,m_pErrorEngine,m_pNullResponser,pTradeResult,m_verbose);
	addServiceXTPLink(m_pTradeServiceXTPLink);

	//实时上场服务
	if (m_verbose)
	{
		PROCESS_LOG0("create dbmt service\n");
	}
	m_pDbmtService=new CDbmtServiceImpl(m_pDB,m_pErrorEngine);
	m_pDbmtServiceXtpLink=new CDbmtServiceXtpLink(m_pDbmtService,m_pErrorEngine,m_pNullResponser,pTradeResult,m_verbose);
	addServiceXTPLink(m_pDbmtServiceXtpLink);

	//创建Trigger,用于向结果流中写入内存表变化消息,by wangwei,20130105
// 	NEW_MDB_TRIGGER(Order, "t_Order",false);
// 	NEW_MDB_TRIGGER(Trade, "t_Trade",false);
// 	NEW_MDB_TRIGGER(InvestorAccount, "t_InvestorAccount",false);
// 	NEW_MDB_TRIGGER(InvestorPosition, "t_InvestorPosition",false);
// 	NEW_MDB_TRIGGER(User,"t_User",false);
// 	NEW_MDB_TRIGGER(UserSession,"t_UserSession",false);
// 	NEW_MDB_TRIGGER(Instrument,"t_Instrument",false);//把合约和交易日的变化也送出去,wangwei,20130502
// 	NEW_MDB_TRIGGER(MarketData,"t_MarketData",false);
// 	NEW_MDB_TRIGGER(Exchange,"t_Exchange",false);
//	NEW_MDB_TRIGGER(ExchTimeDiff,"t_ExchangeTimeDiff",false);
//	NEW_MDB_TRIGGER(SystemStatus,"t_SystemStatus",false);
//	NEW_MDB_TRIGGER(OrderInsertFailed,"t_OrderInsertFailed",false);
//	NEW_MDB_TRIGGER(OrderActionFailed,"t_OrderActionFailed",false);
// 	NEW_MDB_TRIGGER(ClientTradingID,"t_ClientTradingID",false);
// 	NEW_MDB_TRIGGER(InvestorMargin,"t_InvestorMargin",false);
// 	NEW_MDB_TRIGGER(InvestorFee,"t_InvestorFee",false);
// 	NEW_MDB_TRIGGER(Investor,"t_Investor",false);
// 	NEW_MDB_TRIGGER(UserInvestor,"t_UserInvestor",false);
// 	NEW_MDB_TRIGGER(Seat,"t_Seat",false);
//	NEW_MDB_TRIGGER(BankAcc,"t_BankAcc",false);
//	NEW_MDB_TRIGGER(BFTransferInterface,"t_BFTransferInterface",false);
// 	NEW_MDB_TRIGGER(DataSyncStatus,"t_DataSyncStatus",false);
// 	NEW_MDB_TRIGGER(SGEDeferRate,"t_SGEDeferRate",false);
//	NEW_MDB_TRIGGER(InvestorTradingRight,"t_InvestorTradingRight",false);
// 	NEW_MDB_TRIGGER(InvestorOptionFee,"t_InvestorOptionFee",false);

	// 删除用户会话,将会触发这个触发器，把删除用户会话的消息，发送到 TradeResult 流中去。 longqy 20130912
//	m_pUserSessionNotifyTrigger = new CTradingTrigger<CUserSessionCommitTrigger,CUserSession,CWriteableUserSession,CUserSessionField,NULLTID,NULLTID,TID_NtfDelUserSession>(m_pTradeResult);
//	m_pDB->m_UserSessionFactory->addCommitTrigger(m_pUserSessionNotifyTrigger);
	
	// longqy 20130904  为出入金发送回报通知添加触发器
// 	m_pInvestorAccountDepositNotifyTrigger = new CUsDepositTrigger(pMDBScheduler,"t_InvestorAccountDeposit",m_pDB,false); 
// 	m_pDB->m_InvestorAccountDepositFactory->addCommitTrigger(m_pInvestorAccountDepositNotifyTrigger);
}
	
CKernelTradeEngine::~CKernelTradeEngine(void)
{
	//结束交易所init服务
	if (m_verbose)
	{
		PROCESS_LOG0("destroy exchange init service\n");
	}
	removeServiceXTPLink(m_pInitServiceXTPLink);
	delete m_pInitServiceXTPLink;
	delete m_pInitService;

	//结束交易所init服务
	if (m_verbose)
	{
		PROCESS_LOG0("destroy trade service\n");
	}
	removeServiceXTPLink(m_pTradeServiceXTPLink);
	delete m_pTradeServiceXTPLink;
	delete m_pTradeService;
}

void CKernelTradeEngine::DumpMemDb()
{
	m_pTradeServiceXTPLink->DumpMemDb();
}

CSystemStatusType CKernelTradeEngine::GetSystemStatus()
{
	CSystemStatus* pSystemStatus=m_pDB->m_SystemStatusFactory->getFirst();
	m_pDB->m_SystemStatusFactory->endGet();
	if (pSystemStatus==NULL)
	{
		m_pErrorEngine->reportError(ERROR_INSUITABLE_DATASYNC_STATUS);
		REPORT_EVENT(LOG_CRITICAL,"InitError","MDB t_SystemStatus is empty!");
		return SS_DbOperational;
	}
	return pSystemStatus->SystemStatus;
}

void CKernelTradeEngine::ChangeSystemStatus(CSystemStatusType systemStatusType)
{
	CSystemStatusField pSystemStatusField;
	pSystemStatusField.SystemStatus = systemStatusType;

	CXTPPackage package;
	package.ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	package.PreparePublish(TID_UpdateSystemStatus);
	package.SetNoReplayFlag(true);
	package.AddField(&pSystemStatusField.m_Describe,&pSystemStatusField);
	handleMessage(&package);
}

void CKernelTradeEngine::handleMessage(CXTPPackage *pPackage)
{
	TSessionRef sessionRef;
	sessionRef.FrontID = pPackage->GetFrontID();
	sessionRef.SessionID = pPackage->GetSessionID();
	sessionRef.RequestID = pPackage->GetRequestID();
	
	int tid = pPackage->GetTid();
	switch(tid)
	{
	case TID_ReqOrderInsert:
		{
			m_pTradeService->ReqOrderInsert(pPackage,sessionRef);
			return;
		}
		
	case TID_RspOrderInsert:
		{
			m_pTradeService->RspOrderInsert(pPackage,sessionRef);
			return;
		}
	case TID_NtfOrder:
		{
			m_pTradeService->OnRtnOrder(pPackage,sessionRef);
			return;
		}		
	case TID_NtfTrade:
		{
			m_pTradeService->OnRtnTrade(pPackage,sessionRef);
			return;
		}
	case TID_NtfPositionProfit:
		{
			m_pTradeService->ReqNtfPositionProfit(pPackage,sessionRef);
			return;
		}
	case TID_NtfTimeSync:
		{		
			m_pTradeService->ReqNtfTimeSync(pPackage,sessionRef);
			return;
		}
	case TID_RspError:
		{
			if (pPackage->GetNoReplayFlag())
			{
				pPackage->MakePackage();
				m_pTradeResult->Append(pPackage->Address(),pPackage->Length());
				return;
			}
		}
	}
	
	iterator it;
	for (it=begin();it<end();it++)
	{
		if (!(*it)->handleMessage(pPackage,sessionRef))
		{
			break;
		}
	}
}
