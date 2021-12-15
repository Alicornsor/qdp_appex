#include "QdpMDLink.h"

#include "XtpPackageDesc.h"
#include "XtpData.h"
#include "system.h"


CQdpMDLink::CQdpMDLink(char *pszFlowPath)
{
	memset(m_sFlowPath,0,sizeof(m_sFlowPath));
	memset(m_sIdInfo,0,sizeof(m_sIdInfo));
	strncpy(m_sFlowPath,pszFlowPath,sizeof(m_sFlowPath));
	m_pUserApi = NULL;
	m_DisconnectNum = 0;

	m_pPubPackage = new CXTPPackage();
	m_pPubPackage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);

	m_pSeriesFlow = new CExCachedFlow(false, 0x7fffffff, 0x100000);
	m_reader.AttachFlow(m_pSeriesFlow, 0);
}

CQdpMDLink::~CQdpMDLink()
{
}

//连接
void CQdpMDLink::OnFrontConnected()
{
	REPORT_EVENT(LOG_CRITICAL,"OnFrontConnected","%s:交易所[%s]席位[%s]连接成功",m_sIdInfo,m_Seat.ExchangeID.getValue(),m_Seat.SeatID.getValue());
	Login();
}

//断开
void CQdpMDLink::OnFrontDisconnected(int nReason)
{
	REPORT_EVENT(LOG_CRITICAL,"%s,OnFrontDisConnected","%s:交易所[%s]席位[%s]断开,Reason=[%d]",m_sIdInfo,m_Seat.ExchangeID.getValue(),m_Seat.SeatID.getValue(),nReason);
	m_bLogin = false;
	m_DisconnectNum++;
}

//登录
void CQdpMDLink::Login()
{
	CQdFtdcReqUserLoginField reqUserLogin;
	memset(&reqUserLogin, 0, sizeof(reqUserLogin));
	strncpy(reqUserLogin.BrokerID, m_Seat.ParticipantID.getValue(),sizeof(reqUserLogin.BrokerID));
	strncpy(reqUserLogin.UserID, m_Seat.SeatID.getValue(),sizeof(reqUserLogin.UserID));
	strncpy(reqUserLogin.Password, m_Seat.SeatPassword.getValue(),sizeof(reqUserLogin.Password));
	strcpy(reqUserLogin.UserProductInfo, ProductInfo);
	m_pUserApi->ReqUserLogin(&reqUserLogin, 0);
}

void CQdpMDLink::StartWork()
{
	m_pUserApi = CQdFtdcMduserApi::CreateFtdcMduserApi(m_sFlowPath);
	m_pUserApi->RegisterSpi(this);

	m_pUserApi->RegisterFront(m_FrontIP);
	//设置心跳超时时间
	m_pUserApi->SetHeartbeatTimeout(m_Seat.Heartbeat.getValue());
	m_pUserApi->SubscribeMarketDataTopic(120, QD_TERT_QUICK);
	m_pUserApi->Init();
}

void CQdpMDLink::SetFrontIp(const char *pIpFrontIP)
{
	if ( NULL == pIpFrontIP )
		return;
	if(!strcmp(pIpFrontIP,""))
		return;
	strncpy(m_FrontIP,pIpFrontIP,sizeof(m_FrontIP));
}

void CQdpMDLink::OnRspUserLogin(CQdFtdcRspUserLoginField *pRspUserLogin, CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo->ErrorID == 0)
	{	
		REPORT_EVENT(LOG_CRITICAL,"OnRspUserLogin","%s:交易席位[%s]登录成功 TradeDate=[%s] TradeTime=[%s] MaxLocalID=[%s]",m_sIdInfo,m_Seat.SeatID.getValue(),pRspUserLogin->TradingDay,pRspUserLogin->LoginTime,pRspUserLogin->MaxOrderLocalID);
		sprintf(m_sIdInfo,"APIID:%d,EXID:%s,SeatID:%s,PartID:%s,Main:%d",m_Seat.APIID.getValue(),m_Seat.ExchangeID.getValue(),m_Seat.SeatID.getValue(),m_Seat.ParticipantID.getValue(),m_Seat.MainSeat.getValue());
		m_bLogin = true;

		char * contracts[1]={""};
		contracts[0]="1";
		m_pUserApi->SubMarketData(contracts, 1);
		
		CQdFtdcDisseminationField pDissemination;
		pDissemination.SequenceNo=-1;
		pDissemination.SequenceSeries=120;
		m_pUserApi->ReqSubscribeTopic(&pDissemination,0);
	}
	else
	{
		REPORT_EVENT(LOG_CRITICAL,"OnRspUserLogin","%s:交易席位[%s]登录失败[%d]: %s",m_sIdInfo,m_Seat.SeatID.getValue(),pRspInfo->ErrorID,pRspInfo->ErrorMsg);
		SLEEP_SECONDS(5);
		Login();
	}
}

void CQdpMDLink::OnRspError(CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	REPORT_EVENT(LOG_CRITICAL,"OnRspError","%s:交易席位[%s]OnRspError[%d]: %s",m_sIdInfo,m_Seat.SeatID.getValue(),pRspInfo->ErrorID,pRspInfo->ErrorMsg);
}

bool CQdpMDLink::ReqQryMarketData(CExchangeIDType ExchangeID,CInstrumentIDType InstrumentID)
{
	CQdFtdcQryMarketDataField QryMarketDataField;
	strncpy(QryMarketDataField.ExchangeID,ExchangeID,sizeof(QryMarketDataField.ExchangeID));
	strncpy(QryMarketDataField.InstrumentID,InstrumentID,sizeof(QryMarketDataField.InstrumentID));

	int ret =m_pUserApi->ReqQryMarketData(&QryMarketDataField,0);
	return true;
}

void CQdpMDLink::OnRspQryMarketData(CQdFtdcRspMarketDataField *pRspMarketData, CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if(NULL!=pRspMarketData)
	{
		if ( (fabs(pRspMarketData->LastPrice-0.0)<=SMALL_DOUBLE ||fabs(pRspMarketData->LastPrice-DBL_MAX)<=SMALL_DOUBLE) &&
			(fabs(pRspMarketData->SettlementPrice-0.0)<=SMALL_DOUBLE ||fabs(pRspMarketData->SettlementPrice-DBL_MAX)<=SMALL_DOUBLE))
		{
			return;
		}

		//modified by chengm 20180518  apex有些清算会员在夜盘启动前不进行清算操作，也就没有资金文件，这时候需要场上用结算价了结掉
		//   当日的持仓盈亏，将持仓盈亏计算到权益Balance字段里并下场,业务管理端再将t_oper_investoraccount中的balance上场给交易
		if (fabs(pRspMarketData->SettlementPrice-0.0)<=SMALL_DOUBLE || fabs(pRspMarketData->SettlementPrice-DBL_MAX)<=SMALL_DOUBLE)
		{
			REPORT_EVENT(LOG_DEBUG,"CQdpMDLink::OnRspQryDepthMarketData","ExchangeID:%s, InstrumentID:%s, LastPrice:%f",
				pRspMarketData->ExchangeID, pRspMarketData->InstrumentID, pRspMarketData->LastPrice);
		}
		else
		{
			REPORT_EVENT(LOG_CRITICAL,"CQdpMDLink::OnRspQryDepthMarketData","ExchangeID:%s, InstrumentID:%s, SettlementPrice:%f",
				pRspMarketData->ExchangeID, pRspMarketData->InstrumentID, pRspMarketData->SettlementPrice);
			pRspMarketData->LastPrice = pRspMarketData->SettlementPrice;
		}

		CMarketDataField marketDataField;
		memset(&marketDataField,0,sizeof(CMarketDataField));
		CopyMarketDataEntity(&marketDataField,pRspMarketData);
		
		//组包
		if (bIsLast)
		{
			m_pPubPackage->PreparePublish(TID_RspQueryExMarketData);//默认是CHAIN_LAST
		}
		else
		{
			m_pPubPackage->PreparePublish(TID_RspQueryExMarketData,CHAIN_CONTINUE);
		}
		
		m_pPubPackage->SetAPIID(m_Seat.APIID);
		m_pPubPackage->SetSubjectID(QUERY_FLOW);
		XTP_ADD_FIELD(m_pPubPackage, &marketDataField);
		m_pPubPackage->MakePackage();
		m_pSeriesFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());
		
		if (bIsLast)
		{
			REPORT_EVENT(LOG_DEBUG,"ReqMarketData","%s:行情查询结束!",m_sIdInfo);
		}
	}	
}


void CQdpMDLink::OnRtnQmdInstrumentStatu(CQdFtdcQmdInstrumentStateField *pQmdInstrumentState)
{
	if(NULL!=pQmdInstrumentState)
	{
		CInstrumentStatusField InstrumentStatus;
		InstrumentStatus.InstrumentID = pQmdInstrumentState->InstrumentID;
		InstrumentStatus.InstrumentStatus = pQmdInstrumentState->InstrumentStatus;
		InstrumentStatus.ExchangeID =EXID_CZCE;
		//组包
		m_pPubPackage->PreparePublish(TID_NtfInstrumentStatusUpdate);
		m_pPubPackage->SetAPIID(m_Seat.APIID);
		m_pPubPackage->SetSubjectID(PUBLIC_FLOW);
		XTP_ADD_FIELD(m_pPubPackage, &InstrumentStatus);
		m_pPubPackage->MakePackage();
		//写tseries流
		m_pSeriesFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());
		REPORT_EVENT(LOG_DEBUG,"OnRtnQmdInstrumentStatu","InstrumentID:%s, InstrumentStatus:%c",
					pQmdInstrumentState->InstrumentID, pQmdInstrumentState->InstrumentStatus);
	}
}