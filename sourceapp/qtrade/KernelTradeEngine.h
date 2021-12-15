/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file KernelTradeEngine.h
///@brief��������CKernelTradeEngine
///@history 
///20130703	hwp		�������ļ�
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
	//�����ڴ����ݿ�
	virtual void DumpMemDb();
	//xuzh 20150821 ����ϵͳ״̬���� 
	void ChangeSystemStatus(CSystemStatusType systemStatusType);
	CSystemStatusType GetSystemStatus();

	///����һ���ڴ�XTP��
	///@param	pPackage	Ҫ�����XTP��
	virtual void handleMessage(CXTPPackage *pPackage);
private:
	IServiceResponser *m_pServiceResponser;
	CFlow *m_pTradeResult;
	CFlow *m_pLoginResult;	
	int m_nLifeCycleID;//�������ں�
	int m_nUpCount;//�ϳ���Ϣ��
	CInitServiceImpl *m_pInitService;
	CInitServiceXTPLink *m_pInitServiceXTPLink;

	CTradeServiceImpl *m_pTradeService;
	CTradeServiceXTPLink *m_pTradeServiceXTPLink;
	CTransaction m_Transaction;
	CNullResponser *m_pNullResponser; 
	
	CLoginServiceImpl *m_pLoginService;
	CLoginServiceXTPLink *m_pLoginServiceXTPLink;

	CDbmtServiceImpl *m_pDbmtService;//ʵʱ�ϳ�����
	CDbmtServiceXtpLink *m_pDbmtServiceXtpLink;

// 	DEFINE_US_MDB_TRIGGER(Order, Order);//ί��
// 	DEFINE_US_MDB_TRIGGER(Trade, Trade);//�ɽ�
// 	DEFINE_US_MDB_TRIGGER(InvestorAccount, InvestorAccount);//�ʽ�
// 	DEFINE_US_MDB_TRIGGER(InvestorPosition, InvestorPosition);//�ֲ�
// 	DEFINE_US_MDB_TRIGGER(User, User);//�޸��û�����
// 	DEFINE_US_MDB_DELETE_TRIGGER(UserSession, UserSession);//UserSession
// 	DEFINE_US_MDB_TRIGGER(Instrument, Instrument);//��Լ��
// 	DEFINE_US_MDB_TRIGGER(MarketData, MarketData);
// 	DEFINE_US_MDB_TRIGGER(Exchange, Exchange);//��������
//	DEFINE_US_MDB_TRIGGER(ExchTimeDiff, ExchTimeDiff);//������ʱ��ƫ��
//	DEFINE_US_MDB_TRIGGER(SystemStatus, SystemStatus);//ϵͳ״̬��
//	DEFINE_US_MDB_TRIGGER(OrderInsertFailed, OrderInsertFailed);//����  liumeng 20140817
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

	// longqy 20130904 Ϊ������ͻر�֪ͨ��Ӵ�����
//	CUsDepositTrigger* m_pInvestorAccountDepositNotifyTrigger;
};
#endif

