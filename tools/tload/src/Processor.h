#ifndef _Processor_H
#define _Processor_H

#include "QdpFtdcUserApi.h"
#include "QdpFtdcUserApiStruct.h"
#include "platform.h"
#include "Semaphore.h"
#include "Mutex.h"
#include "CConfig.h"
#include "TypeDefine.h"

#ifdef WINDOWS
#pragma warning(disable:4786)
#endif
using namespace std;

class CProcessor:public CQdpFtdcUserSpi  
{
public:
	CProcessor(int iId);
	CProcessor(int iId,char *BrokerID,char *pUserID,char *pPassword,FILE* fOut,bool bUserType = false);
	~CProcessor();
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason);
		
	virtual void OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///用户登录应答
	virtual void OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///用户退出应答
	virtual void OnRspUserLogout(CQdpFtdcRspUserLogoutField *pRspUserLogout, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///用户密码修改应答
	virtual void OnRspUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///强制用户退出应答
//	virtual void OnRspForceUserExit(CQdpFtdcForceUserExitField *pForceUserExit, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///用户会话删除应答
//	virtual void OnRspForceUserLogout(CQdpFtdcForceUserExitField *pForceUserExit, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单录入应答
	virtual void OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单操作应答
	virtual void OnRspOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///投资者资金帐户出入金应答
	virtual void OnRspAccountDeposit(CQdpFtdcRspAccountDepositField *pRspAccountDeposit, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///数据流回退通知
//	virtual void OnRtnFlowMessageCancel(CQdpFtdcFlowMessageCancelField *pFlowMessageCancel);

	///成交回报
	virtual void OnRtnTrade(CQdpFtdcTradeField *pTrade);

	///报单回报
	virtual void OnRtnOrder(CQdpFtdcOrderField *pOrder);

	///报单录入错误回报
//	virtual void OnErrRtnOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo);

	///报单操作错误回报
//	virtual void OnErrRtnOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo);

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CQdpFtdcInstrumentStatusField *pInstrumentStatus);

	///账户出入金回报
	virtual void OnRtnInvestorAccountDeposit(CQdpFtdcInvestorAccountDepositResField *pInvestorAccountDepositRes);

	///QDP警告消息通知
	virtual void OnRtnMessageNotify(CQdpFtdcMessageNotifyInfoField *pMessageNotifyInfo);

	///报单查询应答
	virtual void OnRspQryOrder(CQdpFtdcOrderField *pOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///成交单查询应答
	virtual void OnRspQryTrade(CQdpFtdcTradeField *pTrade, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///可用投资者账户查询应答
//	virtual void OnRspQryUserInvestor(CQdpFtdcRspUserInvestorField *pRspUserInvestor, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///交易编码查询应答
//	virtual void OnRspQryTradingCode(CQdpFtdcRspTradingCodeField *pRspTradingCode, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///投资者资金账户查询应答
	virtual void OnRspQryInvestorAccount(CQdpFtdcRspInvestorAccountField *pRspInvestorAccount, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///合约查询应答
	virtual void OnRspQryInstrument(CQdpFtdcRspInstrumentField *pRspInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///交易所查询应答
//	virtual void OnRspQryExchange(CQdpFtdcRspExchangeField *pRspExchange, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///投资者持仓查询应答
	virtual void OnRspQryInvestorPosition(CQdpFtdcRspInvestorPositionField *pRspInvestorPosition, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///用户查询应答
//	virtual void OnRspQryUser(CQdpFtdcUserField *pUser, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///投资者手续费率查询应答
//	virtual void OnRspQryInvestorFee(CQdpFtdcInvestorFeeField *pInvestorFee, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///投资者保证金率查询应答
//	virtual void OnRspQryInvestorMargin(CQdpFtdcInvestorMarginField *pInvestorMargin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///询价录入应答
// 	virtual void OnRspForQuoteInsert(CQdpFtdcInputForQuoteField *pInputForQuote, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
// 	
// 	///询价查询应答
// 	virtual void OnRspQryForQuote(CQdpFtdcForQuoteField *pForQuote, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
// 	
// 	///执行宣告录入应答
// 	virtual void OnRspExecOrderInsert(CQdpFtdcInputExecOrderField *pInputExecOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
// 	
// 	///执行宣告操作应答
// 	virtual void OnRspExecOrderAction(CQdpFtdcExecOrderActionField *pExecOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
// 	
// 	///执行宣告回报
// 	virtual void OnRtnExecOrder(CQdpFtdcExecOrderField *pExecOrder);
// 	
// 	///执行宣告查询应答
// 	virtual void OnRspQryExecOrder(CQdpFtdcExecOrderField *pExecOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

public:
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init() ;
	virtual int Join();
	///获取当前交易日
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	const char *GetTradingDay();
	///用户登录请求
	int ReqUserLogin(char *pBrokerID,char *pUser,char *pPassword);
	
	///注册api

	int getApi();

	//这两个是有业务请求和回报的锁和解锁，没有业务含义的直接使用锁
	void WaitAction(int nTimeOut);
	void EndAction();

	void Release();

	int  DealBusinessCmd(char *pOutFile,int argc,char **argv,int iStart,const int iTimeOut,bool bNoOut,int iTestValue);
	int  DealBusinessFile(char *pInFile,char *pOutFile,bool bNoOut);
	int  DealBusinessConsole(char *pConsoleStr,char *pOutFile,const int iTimeOut,bool bNoOut);
	void Output(const char *msg,...);

public:
	CQdpFtdcUserApi *m_pFfexFtdcUserApi;
	char m_sTradeRUL[50];
	int  m_iOrderResumeType;
	bool m_bTradeIsLogin;

	char m_sBrokerID[20];
	char m_sUserID[20];
	char m_sPassword[20];
//	char m_sParticipantID[20];

	int	 m_iLocalNo;
	int  m_nRequestID;
	int  m_nRecvCount;
	char *m_pInFile;
	CSemaphore m_semAction;
	FILE *m_fOutFile;
	int  m_iTotalRecordCnt;
	bool m_bFirstPackage;
	bool m_bNoOut;
	bool m_bConnected;
	CInstrumentStatusMap	m_InstrumentStatusMap;
	int m_iId;
	fpos_t m_fpsize;

	time_t m_lastTime;
//	CMutex m_mutexFlowControl;
	char  m_sLastOrderSysID[13];
	int   m_iRspValue;
	int   m_iCheckValue;
	bool  m_bWaitResult;
	//xuzh 每次req之后sleep的毫秒数
	int m_nSleepControl;
	//增加有与意外frontdisconnect导致的需要重新登录的情况
	bool  m_bReLogin;
	//是否是由于发送失败重新发送的指令的情况
	bool  m_bResend;
	CConfig *m_pConfig;

	FILE	*m_fp_out;
};
#endif