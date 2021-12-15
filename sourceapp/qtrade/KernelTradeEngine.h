/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file KernelTradeEngine.h
///@brief定义了类CKernelTradeEngine
///@history 
///20130703	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef KERNEL_TRADE_ENGINE_H_20121122
#define KERNEL_TRADE_ENGINE_H_20121122

#include "Engine.h"
#include "CInitServiceImpl.h"
#include "InitServiceXTPLink.h"
#include "TradeServiceXTPLink.h"
#include "XTPPackage.h"
#include "Flow.h"
#include "CInitServiceCheckImpl.h"
#include "CTradeServiceImpl.h"
#include "ServiceXTPLink.h"
#include "NULLResponser.h"
#include "LoginServiceImpl.h"
#include "LoginServiceXTPLink.h"
#include "ReqFlow.h"
#include "UsScheduler.h"
#include "UsTrigger.h"
#include "BaseDataStruct.h"
#include "CDbmtServiceImpl.h"
#include "DbmtServiceXTPLink.h"
#include "TradingTriggers.h"
#include "customDataType.h"

#define DEFINE_US_MDB_TRIGGER(objtype, objname)		\
	typedef CUsTrigger<C##objtype##Field,CWriteable##objname,C##objname,C##objname##CommitTrigger > C##objname##Trigger; \
C##objname##Trigger  *m_p##objname##Trigger;

#define DEFINE_US_MDB_DELETE_TRIGGER(objtype, objname)		\
	typedef CUsTrigger<C##objtype##Field,CWriteable##objname,C##objname,C##objname##CommitTrigger,true,true,true > C##objname##Trigger; \
	C##objname##Trigger  *m_p##objname##Trigger;


class CKernelTradeEngine : public CEngine
{
public:
	CKernelTradeEngine(CConfig *pConfig, CFlow *pTradeResult);
	virtual ~CKernelTradeEngine(void);
	//导出内存数据库
	virtual void DumpMemDb();
	//xuzh 20150821 增加系统状态更新 
	void ChangeSystemStatus(CSystemStatusType systemStatusType);
	CSystemStatusType GetSystemStatus();

	///处理一个内存XTP包
	///@param	pPackage	要处理的XTP包
	virtual void handleMessage(CXTPPackage *pPackage);
private:
	IServiceResponser *m_pServiceResponser;
	CFlow *m_pTradeResult;
	CFlow *m_pLoginResult;	
	int m_nLifeCycleID;//生命周期号
	int m_nUpCount;//上场信息表
	CInitServiceImpl *m_pInitService;
	CInitServiceXTPLink *m_pInitServiceXTPLink;

	CTradeServiceImpl *m_pTradeService;
	CTradeServiceXTPLink *m_pTradeServiceXTPLink;
	CTransaction m_Transaction;
	CNullResponser *m_pNullResponser; 
	
	CLoginServiceImpl *m_pLoginService;
	CLoginServiceXTPLink *m_pLoginServiceXTPLink;

	CDbmtServiceImpl *m_pDbmtService;//实时上场服务
	CDbmtServiceXtpLink *m_pDbmtServiceXtpLink;

// 	DEFINE_US_MDB_TRIGGER(Order, Order);//委托
// 	DEFINE_US_MDB_TRIGGER(Trade, Trade);//成交
// 	DEFINE_US_MDB_TRIGGER(InvestorAccount, InvestorAccount);//资金
// 	DEFINE_US_MDB_TRIGGER(InvestorPosition, InvestorPosition);//持仓
// 	DEFINE_US_MDB_TRIGGER(User, User);//修改用户密码
// 	DEFINE_US_MDB_DELETE_TRIGGER(UserSession, UserSession);//UserSession
// 	DEFINE_US_MDB_TRIGGER(Instrument, Instrument);//合约表
// 	DEFINE_US_MDB_TRIGGER(MarketData, MarketData);
// 	DEFINE_US_MDB_TRIGGER(Exchange, Exchange);//交易所表
//	DEFINE_US_MDB_TRIGGER(ExchTimeDiff, ExchTimeDiff);//交易所时间偏差
//	DEFINE_US_MDB_TRIGGER(SystemStatus, SystemStatus);//系统状态表
//	DEFINE_US_MDB_TRIGGER(OrderInsertFailed, OrderInsertFailed);//错单表  liumeng 20140817
//	DEFINE_US_MDB_TRIGGER(OrderActionFailed, OrderActionFailed);	
// 	DEFINE_US_MDB_TRIGGER(ClientTradingID, ClientTradingID);
// 	DEFINE_US_MDB_TRIGGER(InvestorMargin, InvestorMargin);
// 	DEFINE_US_MDB_TRIGGER(InvestorFee, InvestorFee);
// 	DEFINE_US_MDB_TRIGGER(Investor, Investor);
// 	DEFINE_US_MDB_TRIGGER(UserInvestor, UserInvestor);
// 	DEFINE_US_MDB_TRIGGER(Seat, Seat);
//	DEFINE_US_MDB_TRIGGER(BankAcc, BankAcc);
//	DEFINE_US_MDB_TRIGGER(BFTransferInterface, BFTransferInterface);
// 	DEFINE_US_MDB_TRIGGER(DataSyncStatus,DataSyncStatus);
// 	DEFINE_US_MDB_TRIGGER(SGEDeferRate,SGEDeferRate);
//	DEFINE_US_MDB_DELETE_TRIGGER(InvestorTradingRight, InvestorTradingRight);
// 	DEFINE_US_MDB_TRIGGER(InvestorOptionFee, InvestorOptionFee);

//	CTradingTrigger<CUserSessionCommitTrigger,CUserSession,CWriteableUserSession,CUserSessionField,NULLTID,NULLTID,TID_NtfDelUserSession>* m_pUserSessionNotifyTrigger;

	// longqy 20130904 为出入金发送回报通知添加触发器
//	CUsDepositTrigger* m_pInvestorAccountDepositNotifyTrigger;
};
#endif

