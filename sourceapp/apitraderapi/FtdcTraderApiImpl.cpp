/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file QdpFtdcTraderApiImpl.cpp
///@brief 实现了客户端接口
///@history 
/////////////////////////////////////////////////////////////////////////

#include "public.h"
#include "FtdcTraderApiImpl.h"
#include "FtdPackageDesc.h"
#include "FtdcUserApiMacro.h"

CFtdcTraderApiImpl::CFtdcTraderApiImpl(const char *pszFlowPath)
{
	m_pUserApi = CQdpFtdcUserApi::CreateFtdcUserApi(pszFlowPath, "TraderApi");
	m_pUserApi->RegisterSpi(this);
	m_pSpi = NULL;
}

void CFtdcTraderApiImpl::Init()
{
	static int nTradePrivatePort=39900;
	nTradePrivatePort++;
	m_pUserApi->Init(nTradePrivatePort);
}

int CFtdcTraderApiImpl::Join()
{
	return m_pUserApi->Join();
}

void CFtdcTraderApiImpl::Release()
{
	m_pUserApi->Release();
	m_pUserApi = NULL;
	delete this;
}

const char *CFtdcTraderApiImpl::GetTradingDay()
{
	return m_pUserApi->GetTradingDay();
}

void CFtdcTraderApiImpl::RegisterFront(char *pszFrontAddress)
{
	m_pUserApi->RegisterFront(pszFrontAddress);
}

void CFtdcTraderApiImpl::RegisterNameServer(char *pszNsAddress)
{
	m_pUserApi->RegisterNameServer(pszNsAddress);
}

void CFtdcTraderApiImpl::RegisterSpi(CQdpFtdcTraderSpi *pSpi)
{
	m_pSpi = pSpi;
}

void CFtdcTraderApiImpl::SubscribePrivateTopic(QDP_TE_RESUME_TYPE nResumeType)
{
	m_pUserApi->SubscribePrivateTopic(nResumeType);
}

void CFtdcTraderApiImpl::SubscribePublicTopic(QDP_TE_RESUME_TYPE nResumeType)
{
	m_pUserApi->SubscribePublicTopic(nResumeType);
}

void CFtdcTraderApiImpl::SubscribeUserTopic(QDP_TE_RESUME_TYPE nResumeType)
{
	m_pUserApi->SubscribeUserTopic(nResumeType);
}

void CFtdcTraderApiImpl::SetHeartbeatTimeout(unsigned int timeout)
{
	m_pUserApi->SetHeartbeatTimeout(timeout);
}
	
int CFtdcTraderApiImpl::OpenRequestLog(const char *pszReqLogFileName)
{
	return m_pUserApi->OpenRequestLog(pszReqLogFileName);
}

int CFtdcTraderApiImpl::OpenResponseLog(const char *pszRspLogFileName)
{
	return m_pUserApi->OpenResponseLog(pszRspLogFileName);
}

///用户登录请求
int CFtdcTraderApiImpl::ReqUserLogin(CQdpFtdcReqUserLoginField *pReqUserLogin, int nRequestID)
{
	return m_pUserApi->ReqUserLogin(pReqUserLogin, nRequestID);
}
///用户退出请求
int CFtdcTraderApiImpl::ReqUserLogout(CQdpFtdcReqUserLogoutField *pReqUserLogout, int nRequestID)
{
	return m_pUserApi->ReqUserLogout(pReqUserLogout, nRequestID);
}
///用户密码修改请求
int CFtdcTraderApiImpl::ReqUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID)
{
	return m_pUserApi->ReqUserPasswordUpdate(pUserPasswordUpdate, nRequestID);
}
///报单录入请求
int CFtdcTraderApiImpl::ReqOrderInsert(CQdpFtdcInputOrderField *pInputOrder, int nRequestID)
{
	return m_pUserApi->ReqOrderInsert(pInputOrder, nRequestID);
}
///报单操作请求
int CFtdcTraderApiImpl::ReqOrderAction(CQdpFtdcOrderActionField *pOrderAction, int nRequestID)
{
	return m_pUserApi->ReqOrderAction(pOrderAction, nRequestID);
}
///报单查询请求
int CFtdcTraderApiImpl::ReqQryOrder(CQdpFtdcQryOrderField *pQryOrder, int nRequestID)
{
	return m_pUserApi->ReqQryOrder(pQryOrder, nRequestID);
}
///成交单查询请求
int CFtdcTraderApiImpl::ReqQryTrade(CQdpFtdcQryTradeField *pQryTrade, int nRequestID)
{
	return m_pUserApi->ReqQryTrade(pQryTrade, nRequestID);
}
///可用投资者账户查询请求
int CFtdcTraderApiImpl::ReqQryUserInvestor(CQdpFtdcQryUserInvestorField *pQryUserInvestor, int nRequestID)
{
	return m_pUserApi->ReqQryUserInvestor(pQryUserInvestor, nRequestID);
}
///投资者资金账户查询请求
int CFtdcTraderApiImpl::ReqQryInvestorAccount(CQdpFtdcQryInvestorAccountField *pQryInvestorAccount, int nRequestID)
{
	return m_pUserApi->ReqQryInvestorAccount(pQryInvestorAccount, nRequestID);
}
///合约查询请求
int CFtdcTraderApiImpl::ReqQryInstrument(CQdpFtdcQryInstrumentField *pQryInstrument, int nRequestID)
{
	return m_pUserApi->ReqQryInstrument(pQryInstrument, nRequestID);
}
///交易所查询请求
int CFtdcTraderApiImpl::ReqQryExchange(CQdpFtdcQryExchangeField *pQryExchange, int nRequestID)
{
	return m_pUserApi->ReqQryExchange(pQryExchange, nRequestID);
}
///投资者持仓查询请求
int CFtdcTraderApiImpl::ReqQryInvestorPosition(CQdpFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID)
{
	return m_pUserApi->ReqQryInvestorPosition(pQryInvestorPosition, nRequestID);
}
///订阅主题请求
int CFtdcTraderApiImpl::ReqSubscribeTopic(CQdpFtdcDisseminationField *pDissemination, int nRequestID)
{
	return m_pUserApi->ReqSubscribeTopic(pDissemination, nRequestID);
}
///主题查询请求
int CFtdcTraderApiImpl::ReqQryTopic(CQdpFtdcDisseminationField *pDissemination, int nRequestID)
{
	return m_pUserApi->ReqQryTopic(pDissemination, nRequestID);
}
///投资者手续费率查询请求
int CFtdcTraderApiImpl::ReqQryInvestorFee(CQdpFtdcQryInvestorFeeField *pQryInvestorFee, int nRequestID)
{
	return m_pUserApi->ReqQryInvestorFee(pQryInvestorFee, nRequestID);
}
///投资者保证金率查询请求
int CFtdcTraderApiImpl::ReqQryInvestorMargin(CQdpFtdcQryInvestorMarginField *pQryInvestorMargin, int nRequestID)
{
	return m_pUserApi->ReqQryInvestorMargin(pQryInvestorMargin, nRequestID);
}
///金交所递延费率查询请求
int CFtdcTraderApiImpl::ReqQrySGEDeferRate(CQdpFtdcQrySGEDeferRateField *pQrySGEDeferRate, int nRequestID)
{
	return m_pUserApi->ReqQrySGEDeferRate(pQrySGEDeferRate, nRequestID);
}
///投资者期权手续费率查询请求
int CFtdcTraderApiImpl::ReqQryInvestorOptionFee(CQdpFtdcQryInvestorOptionFeeField *pQryInvestorOptionFee, int nRequestID)
{
	return m_pUserApi->ReqQryInvestorOptionFee(pQryInvestorOptionFee, nRequestID);
}
///实时行情查询请求
int CFtdcTraderApiImpl::ReqQryMarketData(CQdpFtdcQryMarketDataField *pQryMarketData, int nRequestID)
{
	return m_pUserApi->ReqQryMarketData(pQryMarketData, nRequestID);
}

CQdpFtdcTraderApi *CQdpFtdcTraderApi::CreateFtdcTraderApi(const char *pszFlowPath)
{
	return new CFtdcTraderApiImpl(pszFlowPath);
}

const char *CQdpFtdcTraderApi::GetVersion(int &nMajorVersion, int &nMinorVersion)
{
		return INTERFACE_PRODUCT_INFO;
}

void CFtdcTraderApiImpl::OnFrontConnected()
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnFrontConnected();
	}
}

void CFtdcTraderApiImpl::OnFrontDisconnected(int nReason)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnFrontDisconnected(nReason);
	}
}
		
void CFtdcTraderApiImpl::OnHeartBeatWarning(int nTimeLapse)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnHeartBeatWarning(nTimeLapse);
	}
}

void CFtdcTraderApiImpl::OnPackageStart(int nTopicID, int nSequenceNo)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnPackageStart(nTopicID, nSequenceNo);
	}
}
	
void CFtdcTraderApiImpl::OnPackageEnd(int nTopicID, int nSequenceNo)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnPackageEnd(nTopicID, nSequenceNo);
	}
}


///错误应答
void CFtdcTraderApiImpl::OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspError(pRspInfo, nRequestID, bIsLast);
	}
}

///用户登录应答
void CFtdcTraderApiImpl::OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspUserLogin(pRspUserLogin, pRspInfo, nRequestID, bIsLast);
	}
}

///用户退出应答
void CFtdcTraderApiImpl::OnRspUserLogout(CQdpFtdcRspUserLogoutField *pRspUserLogout, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspUserLogout(pRspUserLogout, pRspInfo, nRequestID, bIsLast);
	}
}

///用户密码修改应答
void CFtdcTraderApiImpl::OnRspUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspUserPasswordUpdate(pUserPasswordUpdate, pRspInfo, nRequestID, bIsLast);
	}
}

///报单录入应答
void CFtdcTraderApiImpl::OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspOrderInsert(pInputOrder, pRspInfo, nRequestID, bIsLast);
	}
}

///报单操作应答
void CFtdcTraderApiImpl::OnRspOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspOrderAction(pOrderAction, pRspInfo, nRequestID, bIsLast);
	}
}

///数据流回退通知
void CFtdcTraderApiImpl::OnRtnFlowMessageCancel(CQdpFtdcFlowMessageCancelField *pFlowMessageCancel)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRtnFlowMessageCancel(pFlowMessageCancel);
	}
}

///成交回报
void CFtdcTraderApiImpl::OnRtnTrade(CQdpFtdcTradeField *pTrade)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRtnTrade(pTrade);
	}
}

///报单回报
void CFtdcTraderApiImpl::OnRtnOrder(CQdpFtdcOrderField *pOrder)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRtnOrder(pOrder);
	}
}

///报单录入错误回报
void CFtdcTraderApiImpl::OnErrRtnOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnErrRtnOrderInsert(pInputOrder, pRspInfo);
	}
}

///报单操作错误回报
void CFtdcTraderApiImpl::OnErrRtnOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnErrRtnOrderAction(pOrderAction, pRspInfo);
	}
}

///合约交易状态通知
void CFtdcTraderApiImpl::OnRtnInstrumentStatus(CQdpFtdcInstrumentStatusField *pInstrumentStatus)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRtnInstrumentStatus(pInstrumentStatus);
	}
}

///账户出入金回报
void CFtdcTraderApiImpl::OnRtnInvestorAccountDeposit(CQdpFtdcInvestorAccountDepositResField *pInvestorAccountDepositRes)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRtnInvestorAccountDeposit(pInvestorAccountDepositRes);
	}
}

///QDP警告消息通知
void CFtdcTraderApiImpl::OnRtnMessageNotify(CQdpFtdcMessageNotifyInfoField *pMessageNotifyInfo)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRtnMessageNotify(pMessageNotifyInfo);
	}
}

///金交所递延费率通知
void CFtdcTraderApiImpl::OnRtnSGEDeferRate(CQdpFtdcSGEDeferRateField *pSGEDeferRate)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRtnSGEDeferRate(pSGEDeferRate);
	}
}

///报单查询应答
void CFtdcTraderApiImpl::OnRspQryOrder(CQdpFtdcOrderField *pOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryOrder(pOrder, pRspInfo, nRequestID, bIsLast);
	}
}

///成交单查询应答
void CFtdcTraderApiImpl::OnRspQryTrade(CQdpFtdcTradeField *pTrade, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryTrade(pTrade, pRspInfo, nRequestID, bIsLast);
	}
}

///可用投资者账户查询应答
void CFtdcTraderApiImpl::OnRspQryUserInvestor(CQdpFtdcRspUserInvestorField *pRspUserInvestor, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryUserInvestor(pRspUserInvestor, pRspInfo, nRequestID, bIsLast);
	}
}

///投资者资金账户查询应答
void CFtdcTraderApiImpl::OnRspQryInvestorAccount(CQdpFtdcRspInvestorAccountField *pRspInvestorAccount, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorAccount(pRspInvestorAccount, pRspInfo, nRequestID, bIsLast);
	}
}

///合约查询应答
void CFtdcTraderApiImpl::OnRspQryInstrument(CQdpFtdcRspInstrumentField *pRspInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInstrument(pRspInstrument, pRspInfo, nRequestID, bIsLast);
	}
}

///交易所查询应答
void CFtdcTraderApiImpl::OnRspQryExchange(CQdpFtdcRspExchangeField *pRspExchange, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryExchange(pRspExchange, pRspInfo, nRequestID, bIsLast);
	}
}

///投资者持仓查询应答
void CFtdcTraderApiImpl::OnRspQryInvestorPosition(CQdpFtdcRspInvestorPositionField *pRspInvestorPosition, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorPosition(pRspInvestorPosition, pRspInfo, nRequestID, bIsLast);
	}
}

///订阅主题应答
void CFtdcTraderApiImpl::OnRspSubscribeTopic(CQdpFtdcDisseminationField *pDissemination, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspSubscribeTopic(pDissemination, pRspInfo, nRequestID, bIsLast);
	}
}

///主题查询应答
void CFtdcTraderApiImpl::OnRspQryTopic(CQdpFtdcDisseminationField *pDissemination, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryTopic(pDissemination, pRspInfo, nRequestID, bIsLast);
	}
}

///投资者手续费率查询应答
void CFtdcTraderApiImpl::OnRspQryInvestorFee(CQdpFtdcInvestorFeeField *pInvestorFee, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorFee(pInvestorFee, pRspInfo, nRequestID, bIsLast);
	}
}

///投资者保证金率查询应答
void CFtdcTraderApiImpl::OnRspQryInvestorMargin(CQdpFtdcInvestorMarginField *pInvestorMargin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorMargin(pInvestorMargin, pRspInfo, nRequestID, bIsLast);
	}
}

///金交所递延费率查询应答
void CFtdcTraderApiImpl::OnRspQrySGEDeferRate(CQdpFtdcSGEDeferRateField *pSGEDeferRate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQrySGEDeferRate(pSGEDeferRate, pRspInfo, nRequestID, bIsLast);
	}
}

///投资者期权手续费率查询应答
void CFtdcTraderApiImpl::OnRspQryInvestorOptionFee(CQdpFtdcRspInvestorOptionFeeField *pRspInvestorOptionFee, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorOptionFee(pRspInvestorOptionFee, pRspInfo, nRequestID, bIsLast);
	}
}

///实时行情查询应答
void CFtdcTraderApiImpl::OnRspQryMarketData(CQdpFtdcMarketDataField *pMarketData, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryMarketData(pMarketData, pRspInfo, nRequestID, bIsLast);
	}
}


