/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file QdpFtdcTraderApiImpl.cpp
///@brief ʵ���˿ͻ��˽ӿ�
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

///�û���¼����
int CFtdcTraderApiImpl::ReqUserLogin(CQdpFtdcReqUserLoginField *pReqUserLogin, int nRequestID)
{
	return m_pUserApi->ReqUserLogin(pReqUserLogin, nRequestID);
}
///�û��˳�����
int CFtdcTraderApiImpl::ReqUserLogout(CQdpFtdcReqUserLogoutField *pReqUserLogout, int nRequestID)
{
	return m_pUserApi->ReqUserLogout(pReqUserLogout, nRequestID);
}
///�û������޸�����
int CFtdcTraderApiImpl::ReqUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID)
{
	return m_pUserApi->ReqUserPasswordUpdate(pUserPasswordUpdate, nRequestID);
}
///����¼������
int CFtdcTraderApiImpl::ReqOrderInsert(CQdpFtdcInputOrderField *pInputOrder, int nRequestID)
{
	return m_pUserApi->ReqOrderInsert(pInputOrder, nRequestID);
}
///������������
int CFtdcTraderApiImpl::ReqOrderAction(CQdpFtdcOrderActionField *pOrderAction, int nRequestID)
{
	return m_pUserApi->ReqOrderAction(pOrderAction, nRequestID);
}
///������ѯ����
int CFtdcTraderApiImpl::ReqQryOrder(CQdpFtdcQryOrderField *pQryOrder, int nRequestID)
{
	return m_pUserApi->ReqQryOrder(pQryOrder, nRequestID);
}
///�ɽ�����ѯ����
int CFtdcTraderApiImpl::ReqQryTrade(CQdpFtdcQryTradeField *pQryTrade, int nRequestID)
{
	return m_pUserApi->ReqQryTrade(pQryTrade, nRequestID);
}
///����Ͷ�����˻���ѯ����
int CFtdcTraderApiImpl::ReqQryUserInvestor(CQdpFtdcQryUserInvestorField *pQryUserInvestor, int nRequestID)
{
	return m_pUserApi->ReqQryUserInvestor(pQryUserInvestor, nRequestID);
}
///Ͷ�����ʽ��˻���ѯ����
int CFtdcTraderApiImpl::ReqQryInvestorAccount(CQdpFtdcQryInvestorAccountField *pQryInvestorAccount, int nRequestID)
{
	return m_pUserApi->ReqQryInvestorAccount(pQryInvestorAccount, nRequestID);
}
///��Լ��ѯ����
int CFtdcTraderApiImpl::ReqQryInstrument(CQdpFtdcQryInstrumentField *pQryInstrument, int nRequestID)
{
	return m_pUserApi->ReqQryInstrument(pQryInstrument, nRequestID);
}
///��������ѯ����
int CFtdcTraderApiImpl::ReqQryExchange(CQdpFtdcQryExchangeField *pQryExchange, int nRequestID)
{
	return m_pUserApi->ReqQryExchange(pQryExchange, nRequestID);
}
///Ͷ���ֲֲ߳�ѯ����
int CFtdcTraderApiImpl::ReqQryInvestorPosition(CQdpFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID)
{
	return m_pUserApi->ReqQryInvestorPosition(pQryInvestorPosition, nRequestID);
}
///������������
int CFtdcTraderApiImpl::ReqSubscribeTopic(CQdpFtdcDisseminationField *pDissemination, int nRequestID)
{
	return m_pUserApi->ReqSubscribeTopic(pDissemination, nRequestID);
}
///�����ѯ����
int CFtdcTraderApiImpl::ReqQryTopic(CQdpFtdcDisseminationField *pDissemination, int nRequestID)
{
	return m_pUserApi->ReqQryTopic(pDissemination, nRequestID);
}
///Ͷ�����������ʲ�ѯ����
int CFtdcTraderApiImpl::ReqQryInvestorFee(CQdpFtdcQryInvestorFeeField *pQryInvestorFee, int nRequestID)
{
	return m_pUserApi->ReqQryInvestorFee(pQryInvestorFee, nRequestID);
}
///Ͷ���߱�֤���ʲ�ѯ����
int CFtdcTraderApiImpl::ReqQryInvestorMargin(CQdpFtdcQryInvestorMarginField *pQryInvestorMargin, int nRequestID)
{
	return m_pUserApi->ReqQryInvestorMargin(pQryInvestorMargin, nRequestID);
}
///�������ӷ��ʲ�ѯ����
int CFtdcTraderApiImpl::ReqQrySGEDeferRate(CQdpFtdcQrySGEDeferRateField *pQrySGEDeferRate, int nRequestID)
{
	return m_pUserApi->ReqQrySGEDeferRate(pQrySGEDeferRate, nRequestID);
}
///Ͷ������Ȩ�������ʲ�ѯ����
int CFtdcTraderApiImpl::ReqQryInvestorOptionFee(CQdpFtdcQryInvestorOptionFeeField *pQryInvestorOptionFee, int nRequestID)
{
	return m_pUserApi->ReqQryInvestorOptionFee(pQryInvestorOptionFee, nRequestID);
}
///ʵʱ�����ѯ����
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


///����Ӧ��
void CFtdcTraderApiImpl::OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspError(pRspInfo, nRequestID, bIsLast);
	}
}

///�û���¼Ӧ��
void CFtdcTraderApiImpl::OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspUserLogin(pRspUserLogin, pRspInfo, nRequestID, bIsLast);
	}
}

///�û��˳�Ӧ��
void CFtdcTraderApiImpl::OnRspUserLogout(CQdpFtdcRspUserLogoutField *pRspUserLogout, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspUserLogout(pRspUserLogout, pRspInfo, nRequestID, bIsLast);
	}
}

///�û������޸�Ӧ��
void CFtdcTraderApiImpl::OnRspUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspUserPasswordUpdate(pUserPasswordUpdate, pRspInfo, nRequestID, bIsLast);
	}
}

///����¼��Ӧ��
void CFtdcTraderApiImpl::OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspOrderInsert(pInputOrder, pRspInfo, nRequestID, bIsLast);
	}
}

///��������Ӧ��
void CFtdcTraderApiImpl::OnRspOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspOrderAction(pOrderAction, pRspInfo, nRequestID, bIsLast);
	}
}

///����������֪ͨ
void CFtdcTraderApiImpl::OnRtnFlowMessageCancel(CQdpFtdcFlowMessageCancelField *pFlowMessageCancel)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRtnFlowMessageCancel(pFlowMessageCancel);
	}
}

///�ɽ��ر�
void CFtdcTraderApiImpl::OnRtnTrade(CQdpFtdcTradeField *pTrade)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRtnTrade(pTrade);
	}
}

///�����ر�
void CFtdcTraderApiImpl::OnRtnOrder(CQdpFtdcOrderField *pOrder)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRtnOrder(pOrder);
	}
}

///����¼�����ر�
void CFtdcTraderApiImpl::OnErrRtnOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnErrRtnOrderInsert(pInputOrder, pRspInfo);
	}
}

///������������ر�
void CFtdcTraderApiImpl::OnErrRtnOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnErrRtnOrderAction(pOrderAction, pRspInfo);
	}
}

///��Լ����״̬֪ͨ
void CFtdcTraderApiImpl::OnRtnInstrumentStatus(CQdpFtdcInstrumentStatusField *pInstrumentStatus)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRtnInstrumentStatus(pInstrumentStatus);
	}
}

///�˻������ر�
void CFtdcTraderApiImpl::OnRtnInvestorAccountDeposit(CQdpFtdcInvestorAccountDepositResField *pInvestorAccountDepositRes)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRtnInvestorAccountDeposit(pInvestorAccountDepositRes);
	}
}

///QDP������Ϣ֪ͨ
void CFtdcTraderApiImpl::OnRtnMessageNotify(CQdpFtdcMessageNotifyInfoField *pMessageNotifyInfo)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRtnMessageNotify(pMessageNotifyInfo);
	}
}

///�������ӷ���֪ͨ
void CFtdcTraderApiImpl::OnRtnSGEDeferRate(CQdpFtdcSGEDeferRateField *pSGEDeferRate)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRtnSGEDeferRate(pSGEDeferRate);
	}
}

///������ѯӦ��
void CFtdcTraderApiImpl::OnRspQryOrder(CQdpFtdcOrderField *pOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryOrder(pOrder, pRspInfo, nRequestID, bIsLast);
	}
}

///�ɽ�����ѯӦ��
void CFtdcTraderApiImpl::OnRspQryTrade(CQdpFtdcTradeField *pTrade, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryTrade(pTrade, pRspInfo, nRequestID, bIsLast);
	}
}

///����Ͷ�����˻���ѯӦ��
void CFtdcTraderApiImpl::OnRspQryUserInvestor(CQdpFtdcRspUserInvestorField *pRspUserInvestor, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryUserInvestor(pRspUserInvestor, pRspInfo, nRequestID, bIsLast);
	}
}

///Ͷ�����ʽ��˻���ѯӦ��
void CFtdcTraderApiImpl::OnRspQryInvestorAccount(CQdpFtdcRspInvestorAccountField *pRspInvestorAccount, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorAccount(pRspInvestorAccount, pRspInfo, nRequestID, bIsLast);
	}
}

///��Լ��ѯӦ��
void CFtdcTraderApiImpl::OnRspQryInstrument(CQdpFtdcRspInstrumentField *pRspInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInstrument(pRspInstrument, pRspInfo, nRequestID, bIsLast);
	}
}

///��������ѯӦ��
void CFtdcTraderApiImpl::OnRspQryExchange(CQdpFtdcRspExchangeField *pRspExchange, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryExchange(pRspExchange, pRspInfo, nRequestID, bIsLast);
	}
}

///Ͷ���ֲֲ߳�ѯӦ��
void CFtdcTraderApiImpl::OnRspQryInvestorPosition(CQdpFtdcRspInvestorPositionField *pRspInvestorPosition, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorPosition(pRspInvestorPosition, pRspInfo, nRequestID, bIsLast);
	}
}

///��������Ӧ��
void CFtdcTraderApiImpl::OnRspSubscribeTopic(CQdpFtdcDisseminationField *pDissemination, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspSubscribeTopic(pDissemination, pRspInfo, nRequestID, bIsLast);
	}
}

///�����ѯӦ��
void CFtdcTraderApiImpl::OnRspQryTopic(CQdpFtdcDisseminationField *pDissemination, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryTopic(pDissemination, pRspInfo, nRequestID, bIsLast);
	}
}

///Ͷ�����������ʲ�ѯӦ��
void CFtdcTraderApiImpl::OnRspQryInvestorFee(CQdpFtdcInvestorFeeField *pInvestorFee, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorFee(pInvestorFee, pRspInfo, nRequestID, bIsLast);
	}
}

///Ͷ���߱�֤���ʲ�ѯӦ��
void CFtdcTraderApiImpl::OnRspQryInvestorMargin(CQdpFtdcInvestorMarginField *pInvestorMargin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorMargin(pInvestorMargin, pRspInfo, nRequestID, bIsLast);
	}
}

///�������ӷ��ʲ�ѯӦ��
void CFtdcTraderApiImpl::OnRspQrySGEDeferRate(CQdpFtdcSGEDeferRateField *pSGEDeferRate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQrySGEDeferRate(pSGEDeferRate, pRspInfo, nRequestID, bIsLast);
	}
}

///Ͷ������Ȩ�������ʲ�ѯӦ��
void CFtdcTraderApiImpl::OnRspQryInvestorOptionFee(CQdpFtdcRspInvestorOptionFeeField *pRspInvestorOptionFee, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorOptionFee(pRspInvestorOptionFee, pRspInfo, nRequestID, bIsLast);
	}
}

///ʵʱ�����ѯӦ��
void CFtdcTraderApiImpl::OnRspQryMarketData(CQdpFtdcMarketDataField *pMarketData, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnRspQryMarketData(pMarketData, pRspInfo, nRequestID, bIsLast);
	}
}


