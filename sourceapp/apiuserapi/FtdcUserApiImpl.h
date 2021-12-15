/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file QdpFtdcUserApiImpl.h
///@brief 定义了客户端接口实现
///@history 
///20150522 xuzh create
/////////////////////////////////////////////////////////////////////////

#if !defined(_FTDCUSERAPIIMPL_H)
#define _FTDCUSERAPIIMPL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FtdcUserApiImplBase.h"

class CFtdcUserApiImpl : public CFtdcUserApiImplBase
{
public:	
	CFtdcUserApiImpl(const char *pszFlowPath, const char *pszUserApiType, CReactor *pReactor);
	virtual void HandleResponse(CFTDCPackage *pMessage, WORD nSequenceSeries);

	///用户退出请求
	virtual int ReqUserLogout(CQdpFtdcReqUserLogoutField *pReqUserLogout, int nRequestID);

	///用户密码修改请求
	virtual int ReqUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID);

	///强制用户退出请求
	virtual int ReqForceUserExit(CQdpFtdcForceUserExitField *pForceUserExit, int nRequestID);

	///用户会话删除请求
	virtual int ReqForceUserLogout(CQdpFtdcForceUserExitField *pForceUserExit, int nRequestID);

	///请求导出内存数据库
	virtual int ReqDumpMemDb(CQdpFtdcMemDbField *pMemDb, int nRequestID);

	///报单录入请求
	virtual int ReqOrderInsert(CQdpFtdcInputOrderField *pInputOrder, int nRequestID);

	///报单操作请求
	virtual int ReqOrderAction(CQdpFtdcOrderActionField *pOrderAction, int nRequestID);

	///投资者资金帐户出入金请求
	virtual int ReqAccountDeposit(CQdpFtdcReqAccountDepositField *pReqAccountDeposit, int nRequestID);

	///报单查询请求
	virtual int ReqQryOrder(CQdpFtdcQryOrderField *pQryOrder, int nRequestID);

	///成交单查询请求
	virtual int ReqQryTrade(CQdpFtdcQryTradeField *pQryTrade, int nRequestID);

	///可用投资者账户查询请求
	virtual int ReqQryUserInvestor(CQdpFtdcQryUserInvestorField *pQryUserInvestor, int nRequestID);

	///交易编码查询请求
	virtual int ReqQryTradingCode(CQdpFtdcQryTradingCodeField *pQryTradingCode, int nRequestID);

	///投资者资金账户查询请求
	virtual int ReqQryInvestorAccount(CQdpFtdcQryInvestorAccountField *pQryInvestorAccount, int nRequestID);

	///合约查询请求
	virtual int ReqQryInstrument(CQdpFtdcQryInstrumentField *pQryInstrument, int nRequestID);

	///交易所查询请求
	virtual int ReqQryExchange(CQdpFtdcQryExchangeField *pQryExchange, int nRequestID);

	///投资者持仓查询请求
	virtual int ReqQryInvestorPosition(CQdpFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID);

	///订阅主题请求
	virtual int ReqSubscribeTopic(CQdpFtdcDisseminationField *pDissemination, int nRequestID);

	///主题查询请求
	virtual int ReqQryTopic(CQdpFtdcDisseminationField *pDissemination, int nRequestID);

	///用户查询请求
	virtual int ReqQryUser(CQdpFtdcQryUserField *pQryUser, int nRequestID);

	///投资者手续费率查询请求
	virtual int ReqQryInvestorFee(CQdpFtdcQryInvestorFeeField *pQryInvestorFee, int nRequestID);

	///投资者保证金率查询请求
	virtual int ReqQryInvestorMargin(CQdpFtdcQryInvestorMarginField *pQryInvestorMargin, int nRequestID);

	///金交所递延费率查询请求
	virtual int ReqQrySGEDeferRate(CQdpFtdcQrySGEDeferRateField *pQrySGEDeferRate, int nRequestID);

	///持仓明细查询请求
	virtual int ReqQryInvestorPositionDetail(CQdpFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID);

	///投资者期权手续费率查询请求
	virtual int ReqQryInvestorOptionFee(CQdpFtdcQryInvestorOptionFeeField *pQryInvestorOptionFee, int nRequestID);

	///Topic查询
	virtual int ReqTopicSearch(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID);

	///订阅合约的相关信息
	virtual int ReqSubMarketData(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID);

	///退订合约的相关信息
	virtual int ReqUnSubMarketData(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID);

	///实时行情查询请求
	virtual int ReqQryMarketData(CQdpFtdcQryMarketDataField *pQryMarketData, int nRequestID);

	///行情查询请求
	virtual int ReqQryDepthMarketData(CQdpFtdcQryMarketDataField *pQryMarketData, int nRequestID);

	///分价表查询请求
	virtual int ReqQryMBLMarketData(CQdpFtdcQryMBLMarketDataField *pQryMBLMarketData, int nRequestID);
private:
	///错误应答
	void OnRspError(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///用户登录应答
	void OnRspUserLogin(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///用户退出应答
	void OnRspUserLogout(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///用户密码修改应答
	void OnRspUserPasswordUpdate(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///强制用户退出应答
	void OnRspForceUserExit(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///用户会话删除应答
	void OnRspForceUserLogout(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///报单录入应答
	void OnRspOrderInsert(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///报单操作应答
	void OnRspOrderAction(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///投资者资金帐户出入金应答
	void OnRspAccountDeposit(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///数据流回退通知
	void OnRtnFlowMessageCancel(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///成交回报
	void OnRtnTrade(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///报单回报
	void OnRtnOrder(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///报单录入错误回报
	void OnErrRtnOrderInsert(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///报单操作错误回报
	void OnErrRtnOrderAction(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///合约交易状态通知
	void OnRtnInstrumentStatus(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///账户出入金回报
	void OnRtnInvestorAccountDeposit(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///QDP警告消息通知
	void OnRtnMessageNotify(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///金交所递延费率通知
	void OnRtnSGEDeferRate(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///郑州合约状态
	void OnRtnQmdInstrumentStatu(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///报单查询应答
	void OnRspQryOrder(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///成交单查询应答
	void OnRspQryTrade(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///可用投资者账户查询应答
	void OnRspQryUserInvestor(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///交易编码查询应答
	void OnRspQryTradingCode(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///投资者资金账户查询应答
	void OnRspQryInvestorAccount(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///合约查询应答
	void OnRspQryInstrument(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///交易所查询应答
	void OnRspQryExchange(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///投资者持仓查询应答
	void OnRspQryInvestorPosition(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///订阅主题应答
	void OnRspSubscribeTopic(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///主题查询应答
	void OnRspQryTopic(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///用户查询应答
	void OnRspQryUser(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///投资者手续费率查询应答
	void OnRspQryInvestorFee(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///投资者保证金率查询应答
	void OnRspQryInvestorMargin(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///金交所递延费率查询应答
	void OnRspQrySGEDeferRate(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///持仓明细查询应答
	void OnRspQryInvestorPositionDetail(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///投资者期权手续费率查询应答
	void OnRspQryInvestorOptionFee(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///深度行情通知
	void OnRtnDepthMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///深度行情通知
	void OnRtnMultiDepthMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///订阅合约的相关信息
	void OnRspSubMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///退订合约的相关信息
	void OnRspUnSubMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///实时行情查询应答
	void OnRspQryMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///行情查询应答
	void OnRspQryDepthMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///分价表查询应答
	void OnRspQryMBLMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
};

#endif
