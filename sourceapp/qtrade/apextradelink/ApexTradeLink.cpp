#include "ApexTradeLink.h"
#include "ApexFtdcUserApiDataType.h"
#include "XtpPackageDesc.h"
#include "XtpData.h"
#include "CDate.h"
extern bool    g_bLatencyOut;
CApexTradeLink::CApexTradeLink(char *pszFlowPath)
{
	memset(m_sFlowPath,0,sizeof(m_sFlowPath));
	memset(m_sIdInfo,0,sizeof(m_sIdInfo));
	strncpy(m_sFlowPath,pszFlowPath,sizeof(m_sFlowPath));

	memset(m_TradeDate,0,sizeof(m_TradeDate));
	m_iMaxLocalNo = 0;
	m_iReqSeqNo = 0;
	m_pUserApi = NULL;
	m_bLogin = false;

	m_Status = '9';
	
	m_pSeriesFlow =new CExCachedFlow(false, 0x7fffffff, 0x100000);
	m_reader.AttachFlow(m_pSeriesFlow,0);

	m_pRryFlow =new CExCachedFlow(false, 0x7fffffff, 0x100000);
	m_qryReader.AttachFlow(m_pRryFlow,0);

	m_pPubPackage = new CXTPPackage();
	m_pPubPackage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	m_FensId = 0;
	m_FrontId = 0;
	m_bInitSeat = false;
	m_bCanGetBuf = false;
	m_breveOver = false;
//	memset(m_ExchangeName,0,sizeof(m_ExchangeName));
//	strcpy(m_ExchangeName,CFFEX_NAME);
//	m_ExchangeID = EX_CFFEX;
	m_nQryClientTradingCount = 0;
	m_NetPosiMap.clear();
	m_ClientTradingIDMap.clear();
}

CApexTradeLink::~CApexTradeLink()
{
	delete m_pPubPackage;
}

//����
void CApexTradeLink::OnFrontConnected()
{
	REPORT_EVENT(LOG_CRITICAL,"OnFrontConnected","%s:seat[%s]connected",m_sIdInfo,m_Seat.SeatID.getValue());
	Login();
}

//�Ͽ�
void CApexTradeLink::OnFrontDisconnected(int nReason)
{
	REPORT_EVENT(LOG_CRITICAL,"OnFrontDisconnected","%s:seat[%s]disconnected,Reason=[%d]",m_sIdInfo,m_Seat.SeatID.getValue(),nReason);
	m_bLogin = false;
}

//��¼
void CApexTradeLink::Login()
{
	CApexFtdcReqUserLoginField reqUserLogin;
	memset(&reqUserLogin, 0, sizeof(reqUserLogin));
	strncpy(reqUserLogin.ParticipantID, m_Seat.ParticipantID.getValue(),sizeof(reqUserLogin.ParticipantID));
	strncpy(reqUserLogin.UserID, m_Seat.SeatID.getValue(),sizeof(reqUserLogin.UserID));
	strncpy(reqUserLogin.Password, m_Seat.SeatPassword.getValue(),sizeof(reqUserLogin.Password));
	strcpy(reqUserLogin.UserProductInfo, ProductInfo);
	m_pUserApi->ReqUserLogin(&reqUserLogin, 0);
}

void CApexTradeLink::OnRspUserLogin(CApexFtdcRspUserLoginField *pRspUserLogin, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo->ErrorID == 0)
	{
		if(m_Seat.CheckTradingDay)
		{
			if(m_Seat.TradingDay!=pRspUserLogin->TradingDay)
			{
				REPORT_EVENT(LOG_ERROR,"OnRspUserLogin","%s:seat[%s]login failed:tradedate not match,seatdate[%s]  Apex exchangedate[%s]",m_sIdInfo,m_Seat.SeatID.getValue(),
					m_Seat.TradingDay.getValue(),pRspUserLogin->TradingDay);
				return;
			}
		}
		m_bRevRtn = true;
		REPORT_EVENT(LOG_CRITICAL,"OnRspUserLogin","%s:seat[%s]login sucess TradeDate=[%s] TradeTime=[%s] MaxLocalID=[%s]",m_sIdInfo,m_Seat.SeatID.getValue(),pRspUserLogin->TradingDay,pRspUserLogin->LoginTime,pRspUserLogin->MaxOrderLocalID);
#ifdef LINUX
		REPORT_EVENT(LOG_CRITICAL,"qtrade cffexlink thread", " [%ld]\n", gettid());
#endif
		strncpy(m_TradeDate,pRspUserLogin->TradingDay,8);
		//m_TradeDate = atol(pRspUserLogin->TradingDay);
		//20160425 1315 added by chengm qdp���˶�ʴ����������������������ص���󱾵ر�����<qdp��󱾵ر�����,���qdp��󱾵ر����ű�����
		int i_MaxLocalNo=atoi(pRspUserLogin->MaxOrderLocalID+1);
		if(m_iMaxLocalNo < i_MaxLocalNo)
			m_iMaxLocalNo = i_MaxLocalNo;
		m_Seat.ParticipantID = pRspUserLogin->ParticipantID;

		sprintf(m_sIdInfo,"APIID:%d,EXID:%s,SeatID:%s,PartID:%s,Main:%d",m_Seat.APIID.getValue(),m_Seat.ExchangeID.getValue(),m_Seat.SeatID.getValue(),m_Seat.ParticipantID.getValue(),m_Seat.MainSeat.getValue());		
		//����kernel��������
		m_pPubPackage->PreparePublish(TID_RspQueryExTradingDay);//Ĭ����CHAIN_LAST
		m_pPubPackage->SetAPIID(m_Seat.APIID);
		m_pPubPackage->SetSubjectID(QUERY_FLOW);
		m_pPubPackage->SetSequenceNo(m_iSeqNo);

		CExchangeTradingDayField ExTradingday;
		ExTradingday.ExchangeID=m_Seat.ExchangeID.getValue();
		ExTradingday.TradingDay=pRspUserLogin->TradingDay;
		XTP_ADD_FIELD(m_pPubPackage, &ExTradingday);
		m_pPubPackage->MakePackage();
		m_pRryFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());

		m_bLogin = true;
		//�����Ҫ��Ҫ��ѯ�����ѯ��Լ��Ϣ
		if(m_Seat.QueryBase)
		{
			ReqContract();
		}
		else
		{
			ReqMarketData();
		}
	}
	else
	{
		REPORT_EVENT(LOG_CRITICAL,"OnRspUserLogin","%s:seat[%s]login failed[%d]: %s",m_sIdInfo,m_Seat.SeatID.getValue(),pRspInfo->ErrorID,pRspInfo->ErrorMsg);
		SLEEP_SECONDS(5);
		Login();
	}
}

void CApexTradeLink::OnRspError(CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	REPORT_EVENT(LOG_CRITICAL,"OnRspError","%s:seat[%s]OnRspError[%d]: %s",m_sIdInfo,m_Seat.SeatID.getValue(),pRspInfo->ErrorID,pRspInfo->ErrorMsg);
}

//����Ӧ��
void CApexTradeLink::OnRspOrderInsert(CApexFtdcInputOrderField *pInputOrder, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	if (pRspInfo!=NULL)
	{
		CInputOrderField Order;
		if (g_bLatencyOut)
		{
			InputSample(Order.CoreRecvUp);
		}
		TransRspOrder(pInputOrder,Order);	
		Order.ExchangeID = m_Seat.ExchangeID.getValue();	
		Order.APIID = m_Seat.APIID;
		Order.RequestID = nRequestID;

		CRspInfoField Rsp;
		Rsp.ErrorID = pRspInfo->ErrorID;
		Rsp.ErrorMsg = pRspInfo->ErrorMsg;


	
		//���
		m_pPubPackage->PreparePublish(TID_RspOrderInsert);
		m_pPubPackage->SetAPIID(m_Seat.APIID);
		m_pPubPackage->SetSubjectID(DIALOG_FLOW);
		m_pPubPackage->SetSequenceNo(m_iSeqNo);
		XTP_ADD_FIELD(m_pPubPackage, &Order);
		XTP_ADD_FIELD(m_pPubPackage,&Rsp);
		m_pPubPackage->MakePackage();			
		m_pSeriesFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());
	}
}

//����Ӧ��
void CApexTradeLink::OnRspOrderAction(CApexFtdcOrderActionField *pOrderAction, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	CRspInfoField Rsp;
	Rsp.ErrorID = pRspInfo->ErrorID;
	Rsp.ErrorMsg = pRspInfo->ErrorMsg;
	
	COrderActionField OrderAction;
	TransRspAction(pOrderAction,OrderAction);
	OrderAction.ExchangeID = m_Seat.ExchangeID.getValue();
	OrderAction.SeatID = m_Seat.SeatID;
	OrderAction.APIID = m_Seat.APIID;
	//���
	m_pPubPackage->PreparePublish(TID_RspOrderAction);
	m_pPubPackage->SetAPIID(m_Seat.APIID);
	m_pPubPackage->SetSubjectID(DIALOG_FLOW);
	m_pPubPackage->SetSequenceNo(m_iSeqNo);
	XTP_ADD_FIELD(m_pPubPackage, &OrderAction);
	XTP_ADD_FIELD(m_pPubPackage,&Rsp);
	m_pPubPackage->MakePackage();
	//дtseries��
	m_pSeriesFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());
}

//����֪ͨ
void CApexTradeLink::OnRtnOrder(CApexFtdcOrderField *pOrder)
{
	if (!m_bRevRtn || 
		!ClientIDExist(pOrder->ClientID))
	{
		//�����ոÿͻ���ί�лر�
		return;
	}

	COrderField FldOrder;		
	TransRtnOrder(pOrder,FldOrder);
	FldOrder.ExchangeID = m_Seat.ExchangeID;
	FldOrder.BrokerID = m_Seat.BrokerID;
	FldOrder.ParticipantID = m_Seat.ParticipantID;
	FldOrder.SeatID = m_Seat.SeatID;
	FldOrder.APIID = m_Seat.APIID;

	switch (pOrder->OrderStatus)
	{
	case APEX_FTDC_OST_AllTraded:
	case APEX_FTDC_OST_PartTradedQueueing:
	case APEX_FTDC_OST_NoTradeQueueing:
		{
			m_pPubPackage->PreparePublish(TID_NtfOrder);
			m_pPubPackage->SetAPIID(m_Seat.APIID);
			m_pPubPackage->SetSubjectID(PRIVATE_FLOW);
			m_pPubPackage->SetSequenceNo(m_iSeqNo);
			XTP_ADD_FIELD(m_pPubPackage, &FldOrder);
			m_pPubPackage->MakePackage();
			//дtseries��
			m_pSeriesFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());	
		}
		break;
	case APEX_FTDC_OST_PartTradedNotQueueing:
		break;
	case APEX_FTDC_OST_NoTradeNotQueueing:
		break;
	case APEX_FTDC_OST_Canceled:
		{		
			//α��һ��
			if(pOrder != NULL && pOrder->TimeCondition == APEX_FTDC_TC_IOC && pOrder->OrderStatus == APEX_FTDC_OST_Canceled)
			{
				COrderField newFldOrder;	
				CopyOrderEntity(&newFldOrder, &FldOrder);	
				newFldOrder.OrderStatus = OS_NoTradeQueueing;
				newFldOrder.VolumeTraded = 0;//�ɽ�������0
				newFldOrder.UserCustom = "FakeRtnOrder";//�ڲ���ʶ		
				//���
				m_pPubPackage->PreparePublish(TID_NtfOrder);
				m_pPubPackage->SetAPIID(m_Seat.APIID);
				m_pPubPackage->SetSubjectID(PRIVATE_FLOW);
				m_pPubPackage->SetSequenceNo(m_iSeqNo);
				XTP_ADD_FIELD(m_pPubPackage, &newFldOrder);
				m_pPubPackage->MakePackage();
				//дtseries��
				m_pSeriesFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());
			}
			
			//���
			m_pPubPackage->PreparePublish(TID_NtfOrder);
			m_pPubPackage->SetAPIID(m_Seat.APIID);
			m_pPubPackage->SetSubjectID(PRIVATE_FLOW);
			m_pPubPackage->SetSequenceNo(m_iSeqNo);
			XTP_ADD_FIELD(m_pPubPackage, &FldOrder);
			m_pPubPackage->MakePackage();
			//дtseries��
			m_pSeriesFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());	
			
			
			CRspInfoField Rsp;
	 		Rsp.ErrorID = 0;
	 		Rsp.ErrorMsg = "none";
			COrderActionField OrderAction;		
			TransRtnDelOrder(pOrder,OrderAction);
			OrderAction.ExchangeID = m_Seat.ExchangeID.getValue();
			OrderAction.SeatID = m_Seat.SeatID.getValue();
			
			//���
			m_pPubPackage->PreparePublish(TID_RspOrderAction);
			m_pPubPackage->SetAPIID(m_Seat.APIID);
			m_pPubPackage->SetSubjectID(PRIVATE_FLOW);
			m_pPubPackage->SetSequenceNo(m_iSeqNo);
			XTP_ADD_FIELD(m_pPubPackage,&Rsp);
			XTP_ADD_FIELD(m_pPubPackage, &OrderAction);
			m_pPubPackage->MakePackage();
			//дtseries��
			m_pSeriesFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());	
		}
		break;
	default:
		break;
	}
}

//�ɽ�֪ͨ
void CApexTradeLink::OnRtnTrade(CApexFtdcTradeField *pTrade)
{
	if (!m_bRevRtn ||
		!ClientIDExist(pTrade->ClientID))
	{
		return;
	}
	
	CTradeField FldMatch;	
	TransRtnTrade(pTrade,FldMatch);
	FldMatch.ExchangeID = m_Seat.ExchangeID.getValue();
	//���
	m_pPubPackage->PreparePublish(TID_NtfTrade);
	m_pPubPackage->SetAPIID(m_Seat.APIID);
	m_pPubPackage->SetSubjectID(PRIVATE_FLOW);
	m_pPubPackage->SetSequenceNo(m_iSeqNo);
	XTP_ADD_FIELD(m_pPubPackage, &FldMatch);
	m_pPubPackage->MakePackage();
	//дtseries��
	m_pSeriesFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());
	
}

//��Լ����״̬֪ͨ
void CApexTradeLink::OnRtnInstrumentStatus(CApexFtdcInstrumentStatusField *pInstrumentStatus)
{	
	CInstrumentStatusField InstrumentStatus;
	InstrumentStatus.InstrumentID = pInstrumentStatus->InstrumentID;
	InstrumentStatus.InstrumentStatus = pInstrumentStatus->InstrumentStatus;
	InstrumentStatus.ExchangeID = m_Seat.ExchangeID.getValue();
	//���
	m_pPubPackage->PreparePublish(TID_NtfInstrumentStatusUpdate);
	m_pPubPackage->SetAPIID(m_Seat.APIID);
	m_pPubPackage->SetSubjectID(PUBLIC_FLOW);
	m_pPubPackage->SetSequenceNo(m_iSeqNo);
	XTP_ADD_FIELD(m_pPubPackage, &InstrumentStatus);
	m_pPubPackage->MakePackage();
	//дtseries��
	m_pSeriesFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());
}

void CApexTradeLink::StartWork()
{
	//�������Ҫ��ѯ����������Ϊֱ�Ӵӻر���ȡ����
	if(!m_Seat.QueryBase)
	{
		m_bCanGetBuf = true;
	}
	m_pUserApi = CApexFtdcTraderApi::CreateFtdcTraderApi(m_sFlowPath);
	m_pUserApi->RegisterSpi(this);

	if(m_Seat.RecvRtn)
	{
		APEX_TE_RESUME_TYPE resumeType=APEX_TERT_RESTART;
		switch(m_Seat.ResumeType)
		{
		case APEX_TERT_RESTART:
			resumeType = APEX_TERT_RESTART;
			break;
		case APEX_TERT_RESUME:
			resumeType = APEX_TERT_RESUME;
			break;
		case APEX_TERT_QUICK:
			resumeType = APEX_TERT_QUICK;
			break;
		}
		if (m_Seat.MainSeat)
		{
			m_pUserApi->SubscribePrivateTopic(resumeType);
		}
		else
		{
			m_pUserApi->SubscribeUserTopic(resumeType);
		}
		m_pUserApi->SubscribePublicTopic(resumeType);
	}


	CApexIpPoolMap::iterator iter;
	for(iter = m_FrontIpPoolMap.begin(); iter != m_FrontIpPoolMap.end(); iter++) //����map�ķ���
	{
		string ipaddress = (*iter).second;
		m_pUserApi->RegisterFront((char *)ipaddress.c_str());
	}
	
	for(iter = m_FensIpPoolMap.begin(); iter != m_FensIpPoolMap.end(); iter++) //����map�ķ���
	{
		string ipaddress = (*iter).second;
		m_pUserApi->RegisterNameServer((char *)ipaddress.c_str());
	}
	//����������ʱʱ��
	m_pUserApi->SetHeartbeatTimeout(m_Seat.Heartbeat.getValue());

	m_pUserApi->Init();
		
	//���������ڿͻ��ֲֲ�ѯ�������ж����ѯ����Щ��ѯ���͵�ʱ��Ҫ�м��
	//��ֹ���������ܾ�������ÿ����һ������Ҫ�ȴ��������ܷ��¸�����
	//�����ǰһ����ѯӦ��Ļص������з�����һ����ѯ������ô��û����һ���ļ������Ϊ
	//��סapi�̲߳�ѯ���ܳɹ�	
	
	
}
int CApexTradeLink::ReqOrderInsert(CInputOrderField &Order)
{
	CApexFtdcInputOrderField oFld;
	//�������memset��CApexFtdcInputOrderField��һ��struct
 	memset(&oFld,0,sizeof(oFld));
	TransReqOrderInsert(oFld,Order);		
	//�����û�����
//	strncpy(oFld.UserID,m_Seat.SeatID.getValue(),sizeof(oFld.UserID));
	//��Ա����
	strncpy(oFld.ParticipantID,m_Seat.ParticipantID,sizeof(oFld.ParticipantID));			
//	strncpy(oFld.OrderLocalID,m_sMaxLocalNo,sizeof(oFld.OrderLocalID));

#ifdef PERFORM_TEST
    long ltm;
    GET_ACCURATE_USEC_TIME(ltm);
    printf("SendTo%s, %ld,",m_Seat.ExchangeID.getValue(),ltm);   
#endif
	
	int ret = m_pUserApi->ReqOrderInsert(&oFld, m_iReqSeqNo); 	
	return ret;	
}

int CApexTradeLink::ReqOrderInsert(CWriteablePreOrder &Order, bool needOrderLocalID)
{
	Order.SeatID = m_Seat.SeatID;
	if (needOrderLocalID)
	{
		Order.OrderLocalID = GetLocalID();
	}
	Order.APIID = m_Seat.APIID;
	
	CApexFtdcInputOrderField oFld;
	//�������memset��CApexFtdcInputOrderField��һ��struct
	memset(&oFld,0,sizeof(oFld));
	TransReqOrderInsert(oFld,Order);
	//��Ա����
	strncpy(oFld.ParticipantID,m_Seat.ParticipantID,sizeof(oFld.ParticipantID));
	
	int ret = m_pUserApi->ReqOrderInsert(&oFld, Order.RequestID.getValue());
	if (g_bLatencyOut)
	{
		InputSample(Order.CoreSendUp);
	}
	return ret;	
}


int CApexTradeLink::ReqOrderAction(COrderActionField &OrderAction)
{
	CApexFtdcOrderActionField oFld;
	//�������memset��CApexFtdcOrderActionField��һ��struct
 	memset(&oFld,0,sizeof(oFld));
	TransReqOrderAction(oFld,OrderAction);
	//���ر������
//	sprintf(oFld.ActionLocalID,"%s",GetLocalID(OrderAction.ClientID.getValue()));
	//�����û�����
	strncpy(oFld.UserID,m_Seat.SeatID.getValue(),sizeof(oFld.UserID));	
	//��Ա����
	strncpy(oFld.ParticipantID,m_Seat.ParticipantID,sizeof(oFld.ParticipantID));
	strncpy(oFld.ActionLocalID,m_sMaxLocalNo,sizeof(oFld.ActionLocalID));
	int ret = m_pUserApi->ReqOrderAction(&oFld, m_iReqSeqNo); 			
	if (ret!=0)		
	{
		REPORT_EVENT(LOG_CRITICAL,"%s:ReqOrderAction:send failed!user:%s,OrderSysId:%s,ret=%d",m_sIdInfo,OrderAction.UserID.getValue(),OrderAction.OrderSysID.getValue(),ret);	
	}	
	return ret; 
}

void CApexTradeLink::OnPackageStart(int nTopicID, int nSequenceNo)
{
	m_iSeqNo = nSequenceNo;
}

char *CApexTradeLink::GetLocalID(char cExchangID)
{	
	sprintf(m_sMaxLocalNo,"C%011u",++m_iMaxLocalNo);
	return m_sMaxLocalNo;
}
char *CApexTradeLink::GetLocalID(const char *pClientID,char cEoFlag)
{
/*	CCltExchIndex CltExchIndex;
	CltExchIndex.ClientID = pClientID;
	CltExchIndex.ExchangID = EX_CFFEX;
	int NCount = 0;
	//�������ͻ���		
	CExchangeCltMap::iterator Cur5 = g_pCommAdapter->m_ExchangeCltMap.find(CltExchIndex);	
	if (Cur5 != g_pCommAdapter->m_ExchangeCltMap.end()) 
	{
		CCltExchIndex *pCltExchIndex = Cur5->second;
		if (pCltExchIndex->IsSubClient)
		{
			NCount = pCltExchIndex->NCount;
		}
	}
	sprintf(m_sMaxLocalNo,"C%08u%03u",++m_iMaxLocalNo,NCount);*/
	return m_sMaxLocalNo;
}

void CApexTradeLink::ReqContract(int reqTime)
{
	if(reqTime>2)
	{
		///�������β�ѯʧ�ܣ��Ͳ���ѯ��
		return;
	}
	SLEEP_SECONDS(2);
	//���ͺ�Լ��ѯ
	REPORT_EVENT(LOG_CRITICAL,"ReqContract","%s:%d times query contract info!",m_sIdInfo,reqTime);	
		
	CApexFtdcQryInstrumentField oFld;
	memset(&oFld,0,sizeof(oFld));	
	int ret = m_pUserApi->ReqQryInstrument(&oFld, m_iReqSeqNo); 
	if (ret!=0)
	{	
		REPORT_EVENT(LOG_CRITICAL,"%s:ReqContract:send contract query failed!",m_sIdInfo);
		ReqContract(reqTime+1);
	}
}

void CApexTradeLink::OnRspQryInstrument(CApexFtdcRspInstrumentField *pRspInstrument, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (NULL != pRspInstrument && pRspInstrument->ProductClass == APEX_FTDC_PC_Futures) 
	{
		CInstrumentField InstrumentField;
		InstrumentField.InstrumentID = pRspInstrument->InstrumentID;
		InstrumentField.BasisPrice = pRspInstrument->BasisPrice;
		InstrumentField.CreateDate = pRspInstrument->CreateDate;
		InstrumentField.DeliveryMonth = pRspInstrument->DeliveryMonth;
		InstrumentField.DeliveryYear = pRspInstrument->DeliveryYear;
		InstrumentField.EndDelivDate = pRspInstrument->EndDelivDate;
		InstrumentField.ExchangeID  = m_Seat.ExchangeID.getValue();
		InstrumentField.ExpireDate = pRspInstrument->ExpireDate;
		InstrumentField.InstrumentName = pRspInstrument->InstrumentName;
		InstrumentField.IsTrading = pRspInstrument->IsTrading;
		InstrumentField.MaxLimitOrderVolume = pRspInstrument->MaxLimitOrderVolume;
		InstrumentField.MinLimitOrderVolume = pRspInstrument->MinLimitOrderVolume;
		InstrumentField.MaxMarketOrderVolume = pRspInstrument->MaxMarketOrderVolume;
		InstrumentField.MinMarketOrderVolume = pRspInstrument->MinMarketOrderVolume;
		
		InstrumentField.OpenDate = pRspInstrument->OpenDate;
		InstrumentField.OptionsType = pRspInstrument->OptionsType;
		InstrumentField.PositionType = pRspInstrument->PositionType;
		InstrumentField.PriceTick = pRspInstrument->PriceTick;
		InstrumentField.ProductClass = pRspInstrument->ProductClass;
		InstrumentField.ProductGroupID = pRspInstrument->ProductGroupID;
		InstrumentField.ProductID = pRspInstrument->ProductID;
		InstrumentField.StartDelivDate = pRspInstrument->StartDelivDate;
		InstrumentField.StrikePrice = pRspInstrument->StrikePrice;
		InstrumentField.UnderlyingInstrID = pRspInstrument->UnderlyingInstrID;
		InstrumentField.UnderlyingMultiple = pRspInstrument->UnderlyingMultiple;//������Ʒ����
		InstrumentField.VolumeMultiple = pRspInstrument->VolumeMultiple;//��������
		memset(tmp,0,sizeof(tmp));
		sprintf(tmp,"%c",C_UDOLLAR);
		InstrumentField.Currency =tmp;
		InstrumentField.APIID = m_Seat.APIID;
	
		//���
		if (bIsLast)
		{
			m_pPubPackage->PreparePublish(TID_RspQueryExInstrument);//Ĭ����CHAIN_LAST
		}
		else
		{
			m_pPubPackage->PreparePublish(TID_RspQueryExInstrument,CHAIN_CONTINUE);
		}
		m_pPubPackage->SetAPIID(m_Seat.APIID);
		m_pPubPackage->SetSubjectID(QUERY_FLOW);
		m_pPubPackage->SetSequenceNo(m_iSeqNo);
		XTP_ADD_FIELD(m_pPubPackage, &InstrumentField);
		m_pPubPackage->MakePackage();
		m_pRryFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());
	}

	if (bIsLast)
	{
		REPORT_EVENT(LOG_CRITICAL,"ReqContract","%s:end query contract!",m_sIdInfo);	
		//ReqClientPosi();
		ReqMarketData();
	}
}

void CApexTradeLink::SetFensIp(const char *pIpFensIP)
{
	if ( NULL == pIpFensIP )
		return;
	if(!strcmp(pIpFensIP,""))
		return;
	m_FensIpPoolMap.insert(pair<int,string>(m_FensId++,pIpFensIP));
}

void CApexTradeLink::SetFrontIp(const char *pIpFrontIP)
{
	if ( NULL == pIpFrontIP )
		return;
	if(!strcmp(pIpFrontIP,""))
		return;
	m_FrontIpPoolMap.insert(pair<int,string>(m_FrontId++,pIpFrontIP));
}

///����������֪ͨ
void CApexTradeLink::OnRtnFlowMessageCancel(CApexFtdcFlowMessageCancelField *pFlowMessageCancel)
{	
}

bool CApexTradeLink::InitClientIDSet(string szClientID)
{
	if (m_SetClientID.insert(szClientID).second)
	{
		REPORT_EVENT(LOG_CRITICAL,"CApexTradeLink::InitClientIDSet","ClientID:%s ", szClientID.c_str());
		return true;
	}
	return false;
}

bool CApexTradeLink::ClientIDExist(const char *pClientID)
{
	if (m_SetClientID.count(pClientID))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CApexTradeLink::InitClientTradingID(CClientTradingIDField *clientTradingID)
{
	CClientTradingIDField *pField = new CClientTradingIDField;
	memcpy(pField,clientTradingID,sizeof(CClientTradingIDField));
	m_ClientTradingIDVec.push_back(pField);
	string ClientTradingIDIndex = clientTradingID->ParticipantID.getValue();
	ClientTradingIDIndex+=clientTradingID->ClientID.getValue();
	m_ClientTradingIDMap.insert(ClientTradingIDMap::value_type(ClientTradingIDIndex,pField));
}

bool CApexTradeLink::GetNextUseNoBuf(CPackage *pPackage)
{
	if(m_bCanGetBuf)
	{
		///������Դ�reader�ж���ǰ����qry���޷���������
		return m_reader.GetNextUseNoBuf(pPackage);
	}
	else
	{
		bool bGetqry =  m_qryReader.GetNextUseNoBuf(pPackage);
		//����ѯ��QueryFinish�����
		if(bGetqry && ((CXTPPackage*)pPackage)->GetTid() ==TID_QueryBaseFinish)
		{
			//���Ӳ�ѯ������Ϣ����qtrade���в�������Ҫ�ǽ��д�߱�֤�����				
			m_bCanGetBuf = true;
		}
		return bGetqry;
	}
}

void CApexTradeLink::QueryFinish()
{
	
	for (CNetPosiMap::iterator iter=m_NetPosiMap.begin();
	iter!=m_NetPosiMap.end();iter++)
	{
		//���
		m_pPubPackage->PreparePublish(TID_RspQueryExInvestorPosition);		
		m_pPubPackage->SetAPIID(m_Seat.APIID);
		m_pPubPackage->SetSubjectID(QUERY_FLOW);
		m_pPubPackage->SetSequenceNo(m_iSeqNo);
		int long_posi = iter->second.long_posi;
		int short_posi = iter->second.short_posi;
		iter->second.Position.Position = iter->second.long_posi - iter->second.short_posi;
		iter->second.Position.YdPosition = iter->second.Position.Position;
		XTP_ADD_FIELD(m_pPubPackage, &(iter->second.Position));
		m_pPubPackage->MakePackage();
		m_pRryFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());
			
		REPORT_EVENT(LOG_CRITICAL,"ReqClientPos","%s:clienttradingid[%s+%s],ins[%s],dir[%c],posi[%d]!",m_sIdInfo,iter->second.Position.ParticipantID.getValue(),
			iter->second.Position.ClientID.getValue(),iter->second.Position.InstrumentID.getValue(),iter->second.Position.Direction.getValue(),iter->second.Position.Position.getValue());
	}
	m_pPubPackage->PreparePublish(TID_QueryBaseFinish);
	m_pPubPackage->SetAPIID(m_Seat.APIID);
	m_pPubPackage->SetSubjectID(QUERY_FLOW);
	m_pPubPackage->SetSequenceNo(m_iSeqNo);

	CQueryFinishNotifyField ExTradingday;
	ExTradingday.ExchangeID=m_Seat.ExchangeID.getValue();
	XTP_ADD_FIELD(m_pPubPackage, &ExTradingday);

	m_pPubPackage->MakePackage();
	m_pRryFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());

	//֮���ѯ��������������
	m_breveOver = true;

	REPORT_EVENT(LOG_CRITICAL,"QueryFinish","%s:end query basic data!",m_sIdInfo);
}

void CApexTradeLink::ReqClientPosi(int reqTime)
{
	//�������Ҫ��ѯ�ֲ֣�ֱ���˳�
	if(!m_Seat.QueryPosition)
	{
		QueryFinish();
		return;
	}

// 	if(m_nQryClientTradingCount>=m_ClientTradingIDVec.size())
// 	{
// 		//�����ѯ������������ѯ
// 		QueryFinish();
// 		return;
// 	}
	if(reqTime>2)
	{
		///�������β�ѯʧ�ܣ��Ͳ���ѯ��
		return;
	}
	SLEEP_SECONDS(2);

	CApexFtdcQryClientPositionField oFld;
	memset(&oFld,0,sizeof(oFld));
	//oFld.ClientIDStart
// 	CClientTradingIDField *pClientTradingID = m_ClientTradingIDVec[m_nQryClientTradingCount];
// 	strcpy(oFld.ClientIDStart,pClientTradingID->ClientID.getValue());
// 	strcpy(oFld.ClientIDEnd,pClientTradingID->ClientID.getValue());
// 	strcpy(oFld.PartIDStart,pClientTradingID->ParticipantID.getValue());
// 	strcpy(oFld.PartIDEnd,pClientTradingID->ParticipantID.getValue());
	strcpy(oFld.PartIDStart,m_Seat.ParticipantID.getValue());
	strcpy(oFld.PartIDEnd,m_Seat.ParticipantID.getValue());

	//�����ѯ����пͻ��ֲֲ�ѯ
//	REPORT_EVENT(LOG_CRITICAL,"ReqClientPosi","%s:%d times query clienttradingid %s + %s position!",m_sIdInfo,reqTime,pClientTradingID->ParticipantID.getValue(),pClientTradingID->ClientID.getValue());
	REPORT_EVENT(LOG_CRITICAL,"ReqClientPosi","%s:%d times query participant position!",m_sIdInfo,reqTime);

	int ret = m_pUserApi->ReqQryClientPosition(&oFld, m_iReqSeqNo); 

	if (ret!=0)
	{	
		REPORT_EVENT(LOG_CRITICAL,"ReqClientPosi","%s:send query client position failed!",m_sIdInfo);
		ReqClientPosi(reqTime+1);
	}
	else
	{
		m_nQryClientTradingCount++;
	}
}

void CApexTradeLink::ReqMarketData(int reqTime)
{
	if(reqTime>2)
	{
		///�������β�ѯʧ�ܣ��Ͳ���ѯ��
		return;
	}
	SLEEP_SECONDS(2);

	CApexFtdcQryMarketDataField oFld;
	memset(&oFld,0,sizeof(oFld));

	//�����ѯ����пͻ��ֲֲ�ѯ
	REPORT_EVENT(LOG_CRITICAL,"ReqMarketData","%s:%d times query marketdata!",m_sIdInfo,reqTime);	

	int ret = m_pUserApi->ReqQryMarketData(&oFld, m_iReqSeqNo); 

	if (ret)
	{	
		REPORT_EVENT(LOG_CRITICAL,"ReqMarketData","%s:send query marketdata failed!",m_sIdInfo);
		ReqMarketData(reqTime+1);
	}
}

///�ͻ��ֲֲ�ѯӦ��
void CApexTradeLink::OnRspQryClientPosition(CApexFtdcRspClientPositionField *pRspClientPosition, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (NULL != pRspClientPosition && ClientIDExist(pRspClientPosition->ClientID)) 
	{
		string ClientTradingIDIndex = pRspClientPosition->ParticipantID;
		ClientTradingIDIndex+=pRspClientPosition->ClientID;
		CClientTradingIDField *pClientTradingIDField = m_ClientTradingIDMap[ClientTradingIDIndex];
		if (pClientTradingIDField != NULL)
		{
		
			REPORT_EVENT(LOG_DEBUG,"ClientPosition","Clientid:%s,Instrumentid:%s,hedgeflag:%c,posidirtion:%c,posi:%d",\
				pRspClientPosition->ClientID,pRspClientPosition->InstrumentID,pRspClientPosition->HedgeFlag,pRspClientPosition->PosiDirection,pRspClientPosition->Position);
			CInvestorPositionField InvestorPositionField;
			memset(&InvestorPositionField,0,sizeof(CInvestorPositionField));
			
			InvestorPositionField.AccountID = pClientTradingIDField->AccountID;
			InvestorPositionField.BrokerID = pClientTradingIDField->BrokerID;
			InvestorPositionField.ExchangeID = pClientTradingIDField->ExchangeID;
			InvestorPositionField.InvestorID = pClientTradingIDField->InvestorID;
			InvestorPositionField.ParticipantID = pClientTradingIDField->ParticipantID;
			InvestorPositionField.ClientID = pRspClientPosition->ClientID;
			InvestorPositionField.InstrumentID = pRspClientPosition->InstrumentID;
			//PositionCost ���������¼����
			InvestorPositionField.PositionCost = pRspClientPosition->YdPositionCost;
			InvestorPositionField.YdPositionCost = pRspClientPosition->YdPositionCost;
			InvestorPositionField.HedgeFlag = pRspClientPosition->HedgeFlag;
			memset(tmp,0,sizeof(tmp));
			sprintf(tmp,"%c",C_UDOLLAR);
			InvestorPositionField.Currency = tmp;

			if (pRspClientPosition->PosiDirection == PD_Long)
			{
				InvestorPositionField.Position = pRspClientPosition->YdPosition + pRspClientPosition->Position - pRspClientPosition->BuyTradeVolume;
			}
			else if (pRspClientPosition->PosiDirection == PD_Short)
			{
				InvestorPositionField.Position = pRspClientPosition->YdPosition + pRspClientPosition->Position - pRspClientPosition->SellTradeVolume;
			}
			else
			{
				InvestorPositionField.Position = pRspClientPosition->YdPosition + pRspClientPosition->Position - pRspClientPosition->BuyTradeVolume + pRspClientPosition->SellTradeVolume;
			}
			//��ʼ����ֲ־��ǽ�ֲ֣�������ֲֻ�����ƽ�ֱ仯�ģ����ȡ����������ֲ֣��������������Ͳ�����
			InvestorPositionField.YdPosition = InvestorPositionField.Position;


			CPositionTypeType PositionType= pClientTradingIDField->PositionType;
			if (PositionType == PT_Net)
			{
				InvestorPositionField.Direction = D_Net;
				if (pRspClientPosition->PosiDirection != PD_Net)
				{
					memset(tmp,0,sizeof(tmp));
					sprintf(tmp,"%s-%s-%c",pRspClientPosition->ClientID,pRspClientPosition->InstrumentID,pRspClientPosition->HedgeFlag);
					CNetPosiMap::iterator iter = m_NetPosiMap.find(tmp);
					if (iter != m_NetPosiMap.end())
					{
						if (pRspClientPosition->PosiDirection == PD_Long)
						{
							iter->second.long_posi = InvestorPositionField.Position.getValue();
						}
						else
						{
							iter->second.short_posi = InvestorPositionField.Position.getValue();
						}
					}
					else
					{
						memset(&posi,0,sizeof(TNetPosi));
						memcpy(&(posi.Position),&InvestorPositionField,sizeof(CInvestorPositionField));
						if (pRspClientPosition->PosiDirection == PD_Long)
						{
							posi.long_posi = InvestorPositionField.Position.getValue();
						}
						else
						{
							posi.short_posi = InvestorPositionField.Position.getValue();
						}
						m_NetPosiMap.insert(CNetPosiMap::value_type(tmp,posi));
					}
					if (bIsLast)
					{
						//REPORT_EVENT(LOG_CRITICAL,"ReqClientPos","%s:clienttradingid %s + %s end query position!",m_sIdInfo,pRspClientPosition->ParticipantID,pRspClientPosition->ClientID);
						REPORT_EVENT(LOG_CRITICAL,"ReqClientPos","%s: end query position!",m_sIdInfo,m_Seat.ParticipantID.getValue());
						QueryFinish();
					}
					return;
				}
				
			}
			else
			{
				//��̨���õ����ۺϳֲ�
				if (pRspClientPosition->PosiDirection == PD_Net)
				{
					InvestorPositionField.Direction = InvestorPositionField.Position >0 ? D_Buy : D_Sell;
					InvestorPositionField.Position = fabs(InvestorPositionField.Position.getValue());
					InvestorPositionField.YdPosition = InvestorPositionField.Position;
				}
				else
				{
					InvestorPositionField.Direction = pRspClientPosition->PosiDirection == PD_Long ? D_Buy : D_Sell;
				}
			}

			//���
			m_pPubPackage->PreparePublish(TID_RspQueryExInvestorPosition);//Ĭ����CHAIN_LAST	
			m_pPubPackage->SetAPIID(m_Seat.APIID);
			m_pPubPackage->SetSubjectID(QUERY_FLOW);
			m_pPubPackage->SetSequenceNo(m_iSeqNo);
			XTP_ADD_FIELD(m_pPubPackage, &InvestorPositionField);
			m_pPubPackage->MakePackage();
			m_pRryFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());
		}//end of if (pClientTradingIDField != NULL)
	}

	if (bIsLast)
	{
		//REPORT_EVENT(LOG_CRITICAL,"ReqClientPos","%s:clienttradingid %s + %s end query position!",m_sIdInfo,pRspClientPosition->ParticipantID,pRspClientPosition->ClientID);
		REPORT_EVENT(LOG_CRITICAL,"ReqClientPos","%s: end query position!",m_sIdInfo,m_Seat.ParticipantID.getValue());
		QueryFinish();
	}
}

void CApexTradeLink::OnRspQryMarketData(CApexFtdcMarketDataField *pMarketData, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (NULL == pMarketData) 
	{
		return;
	}
	
	CMarketDataField marketDataField;
	memset(&marketDataField,0,sizeof(CMarketDataField));
	
	marketDataField.ExchangeID = m_Seat.ExchangeID.getValue();
	marketDataField.HighestPrice = pMarketData->HighestPrice;
	marketDataField.InstrumentID = pMarketData->InstrumentID;
	marketDataField.LastPrice = pMarketData->LastPrice;
	marketDataField.LowerLimitPrice = pMarketData->LowerLimitPrice;
	marketDataField.LowestPrice = pMarketData->LowestPrice;
	marketDataField.UpdateMillisec = pMarketData->UpdateMillisec;
	marketDataField.OpenInterest = pMarketData->OpenInterest;
	marketDataField.OpenPrice = pMarketData->OpenPrice;
	marketDataField.PreClosePrice = pMarketData->PreClosePrice;
	marketDataField.PreOpenInterest= pMarketData->PreOpenInterest;
	marketDataField.PreSettlementPrice = pMarketData->PreSettlementPrice;
	marketDataField.SettlementPrice = pMarketData->SettlementPrice;
	marketDataField.TradingDay = pMarketData->TradingDay;
	marketDataField.Turnover = pMarketData->Turnover;
	marketDataField.UpdateTime = pMarketData->UpdateTime;
	marketDataField.UpperLimitPrice = pMarketData->UpperLimitPrice;

	//���
	if (bIsLast)
	{
		m_pPubPackage->PreparePublish(TID_RspQueryExMarketData);//Ĭ����CHAIN_LAST
	}
	else
	{
		m_pPubPackage->PreparePublish(TID_RspQueryExMarketData,CHAIN_CONTINUE);
	}
	
	m_pPubPackage->SetAPIID(m_Seat.APIID);
	m_pPubPackage->SetSubjectID(QUERY_FLOW);
	m_pPubPackage->SetSequenceNo(m_iSeqNo);
	XTP_ADD_FIELD(m_pPubPackage, &marketDataField);
	m_pPubPackage->MakePackage();
	m_pRryFlow->Append(m_pPubPackage->Address(), m_pPubPackage->Length());

	if (bIsLast)
	{
		REPORT_EVENT(LOG_CRITICAL,"ReqMarketData","%s:end query marketdata!",m_sIdInfo);
		//�����ѯ֮�󣬿�ʼ��ѯ�ֲ�
		ReqClientPosi();
	}	
}

void CApexTradeLink::TransRspOrder(CApexFtdcInputOrderField *pInputOrder,CInputOrderField &Order)
{
	Order.OrderLocalID = pInputOrder->OrderLocalID;
	Order.OrderSysID = pInputOrder->OrderSysID;
	Order.InstrumentID = pInputOrder->InstrumentID;
	Order.ParticipantID = pInputOrder->ParticipantID;
	Order.SeatID = pInputOrder->UserID;
	Order.ClientID = pInputOrder->ClientID;
	Order.Direction = pInputOrder->Direction;
	Order.HedgeFlag = pInputOrder->CombHedgeFlag[0];
	Order.OffsetFlag = pInputOrder->CombOffsetFlag[0];
	Order.LimitPrice = pInputOrder->LimitPrice;
	Order.Volume = pInputOrder->VolumeTotalOriginal;

	Order.BusinessUnit = pInputOrder->BusinessUnit;
	Order.ForceCloseReason = pInputOrder->ForceCloseReason;
	Order.GTDDate = pInputOrder->GTDDate;
	Order.IsAutoSuspend = pInputOrder->IsAutoSuspend;
	Order.MinVolume = pInputOrder->MinVolume;
	Order.OrderPriceType = pInputOrder->OrderPriceType;
	Order.StopPrice = pInputOrder->StopPrice;
	Order.TimeCondition = pInputOrder->TimeCondition;
	Order.VolumeCondition = pInputOrder->VolumeCondition;	
}



void CApexTradeLink::TransRspAction(CApexFtdcOrderActionField *pOrderAction,COrderActionField &OrderAction)
{
	OrderAction.OrderLocalID = pOrderAction->OrderLocalID;
	OrderAction.OrderSysID = pOrderAction->OrderSysID;
	OrderAction.ActionFlag = pOrderAction->ActionFlag;
	OrderAction.ActionLocalID = pOrderAction->ActionLocalID;
	OrderAction.ClientID = pOrderAction->ClientID;
	OrderAction.LimitPrice = pOrderAction->LimitPrice;
	OrderAction.ParticipantID = pOrderAction->ParticipantID;
	OrderAction.VolumeChange = pOrderAction->VolumeChange;	
	OrderAction.SeatID = pOrderAction->UserID;	
//	OrderAction.UserOrderLocalID = pOrderAction->BusinessUnit;
}

void CApexTradeLink::TransRtnOrder(CApexFtdcOrderField *pOrder,COrderField &Order)
{
	Order.BusinessUnit=pOrder->BusinessUnit;
	Order.CancelTime=pOrder->CancelTime;
	Order.ClientID=pOrder->ClientID;
	Order.Direction=pOrder->Direction;
	Order.ForceCloseReason=pOrder->ForceCloseReason;
	Order.GTDDate=pOrder->GTDDate;
	Order.HedgeFlag=pOrder->CombHedgeFlag[0];
	Order.InsertTime=pOrder->InsertTime;
	Order.InstrumentID=pOrder->InstrumentID;
	Order.IsAutoSuspend=pOrder->IsAutoSuspend;
	Order.LimitPrice=pOrder->LimitPrice;
	Order.MinVolume=pOrder->MinVolume;
	Order.OffsetFlag=pOrder->CombOffsetFlag[0];
	Order.OrderLocalID=pOrder->OrderLocalID;
	Order.OrderPriceType=pOrder->OrderPriceType;
	Order.OrderSource=pOrder->OrderSource;
	Order.OrderStatus=pOrder->OrderStatus;
	Order.OrderSysID=pOrder->OrderSysID;
	Order.ParticipantID=pOrder->ParticipantID;
	Order.SeatID=pOrder->UserID;
	Order.StopPrice=pOrder->StopPrice;
	Order.TimeCondition=pOrder->TimeCondition;
	Order.TradingDay=pOrder->TradingDay;
	Order.Volume=pOrder->VolumeTotalOriginal;
	Order.VolumeCondition=pOrder->VolumeCondition;
	Order.VolumeTraded=pOrder->VolumeTotalOriginal - pOrder->VolumeTotal;//����������ȥʣ������
	
	Order.VolumeRemain = pOrder->VolumeTotal;//ʣ������
	Order.BusinessUnit = pOrder->BusinessUnit;
}

void CApexTradeLink::TransRtnDelOrder(CApexFtdcOrderField *pOrder,COrderActionField &OrderAction)
{	
	OrderAction.OrderLocalID = pOrder->OrderLocalID;
	OrderAction.OrderSysID = pOrder->OrderSysID;
	OrderAction.SeatID = pOrder->UserID;
	OrderAction.VolumeChange = pOrder->VolumeTraded;
	OrderAction.ClientID = pOrder->ClientID;
	OrderAction.ParticipantID = pOrder->ParticipantID;
	OrderAction.CancelTime = pOrder->CancelTime;
	OrderAction.LimitPrice = pOrder->LimitPrice;
	OrderAction.UserCustom="FakeRspOrderAction";//�ڲ���ʶ,��Kernel��Լ��
	OrderAction.ActionFlag = '0';
//	OrderAction.UserOrderLocalID = pOrder->BusinessUnit;
}

void CApexTradeLink::TransRtnTrade(CApexFtdcTradeField *pTrade,CTradeField &Trade)
{
	Trade.OrderSysID = pTrade->OrderSysID;
	Trade.OrderLocalID = pTrade->OrderLocalID;
	Trade.TradeID = pTrade->TradeID;
	Trade.TradeVolume = pTrade->Volume;
	Trade.TradePrice = pTrade->Price;
	Trade.AccountID = pTrade->AccountID;
	Trade.ClientID = pTrade->ClientID;
	Trade.Direction = pTrade->Direction;	
	Trade.HedgeFlag = pTrade->HedgeFlag;
	Trade.InstrumentID = pTrade->InstrumentID;
	Trade.OffsetFlag = pTrade->OffsetFlag;
	Trade.ParticipantID = pTrade->ParticipantID;
	Trade.TradeTime = pTrade->TradeTime;
	Trade.TradeType = pTrade->TradeType;
	Trade.TradingDay = pTrade->TradingDay;
	Trade.SeatID = pTrade->UserID;//ϯλ
	Trade.ClearingPartID = pTrade->ClearingPartID;//�����Ա���
	Trade.TradeType = TT_Normal;
//	Trade.UserOrderLocalID = pTrade->BusinessUnit;
}

void CApexTradeLink::TransReqOrderInsert(CApexFtdcInputOrderField &pOrder,CInputOrderField &Order)
{
	//��Ա��
	strncpy(pOrder.ParticipantID,Order.ParticipantID.getValue(),sizeof(pOrder.ParticipantID)-1);
	//�ͻ���
	strncpy(pOrder.ClientID,Order.ClientID.getValue(),sizeof(pOrder.ClientID)-1);
	//�����û�
	strncpy(pOrder.UserID,Order.SeatID.getValue(),sizeof(pOrder.UserID)-1);
	//��Լ
	strncpy(pOrder.InstrumentID,Order.InstrumentID.getValue(),sizeof(pOrder.InstrumentID)-1);
	//�۸�����
	pOrder.OrderPriceType = Order.OrderPriceType.getValue();
	//��������
	pOrder.Direction = Order.Direction.getValue();
	//��ƽ��־
	sprintf(pOrder.CombOffsetFlag,"%c",Order.OffsetFlag.getValue());
	//Ͷ���ױ���־
	sprintf(pOrder.CombHedgeFlag,"%c",Order.HedgeFlag.getValue());
	//�۸�
	pOrder.LimitPrice = Order.LimitPrice.getValue();
	//����
	pOrder.VolumeTotalOriginal = Order.Volume.getValue();
	//���ر�����
	strncpy(pOrder.OrderLocalID,Order.OrderLocalID.getValue(),sizeof(pOrder.OrderLocalID));
	//��Ч������
	pOrder.TimeCondition = Order.TimeCondition;
	// GTD����
	strncpy(pOrder.GTDDate,Order.GTDDate,sizeof(pOrder.GTDDate)-1);
	// �ɽ�������
	pOrder.VolumeCondition = Order.VolumeCondition;
	// ��С�ɽ���
	pOrder.MinVolume = Order.MinVolume;
	// ��������
	pOrder.ContingentCondition = APEX_FTDC_CC_Immediately;
	// ֹ���
	pOrder.StopPrice = Order.StopPrice;
	// ǿƽԭ��
	pOrder.ForceCloseReason = Order.ForceCloseReason;
	// �Զ������־
	pOrder.IsAutoSuspend = Order.IsAutoSuspend;
	//BU
	strncpy(pOrder.BusinessUnit,Order.BusinessUnit.getValue(),sizeof(pOrder.BusinessUnit)-1);
}

void CApexTradeLink::TransReqOrderInsert(CApexFtdcInputOrderField &pOrder,CWriteablePreOrder &Order)
{
	//��Ա��
	strncpy(pOrder.ParticipantID,Order.ParticipantID.getValue(),sizeof(pOrder.ParticipantID)-1);
	//�ͻ���
	strncpy(pOrder.ClientID,Order.ClientID.getValue(),sizeof(pOrder.ClientID)-1);
	//�����û�
	strncpy(pOrder.UserID,Order.SeatID.getValue(),sizeof(pOrder.UserID)-1);
	//��Լ
	strncpy(pOrder.InstrumentID,Order.InstrumentID.getValue(),sizeof(pOrder.InstrumentID)-1);
	//�۸�����
	pOrder.OrderPriceType = Order.OrderPriceType.getValue();
	//��������
	pOrder.Direction = Order.Direction.getValue();
	//��ƽ��־
	sprintf(pOrder.CombOffsetFlag,"%c",Order.OffsetFlag.getValue());
	//Ͷ���ױ���־
	sprintf(pOrder.CombHedgeFlag,"%c",Order.HedgeFlag.getValue());
	//�۸�
	pOrder.LimitPrice = Order.LimitPrice.getValue();
	//����
	pOrder.VolumeTotalOriginal = Order.Volume.getValue();
	//���ر�����
	strncpy(pOrder.OrderLocalID,Order.OrderLocalID.getValue(),sizeof(pOrder.OrderLocalID));
	//��Ч������
	pOrder.TimeCondition = Order.TimeCondition;
	// GTD����
	strncpy(pOrder.GTDDate,Order.GTDDate,sizeof(pOrder.GTDDate)-1);
	// �ɽ�������
	pOrder.VolumeCondition = Order.VolumeCondition;
	// ��С�ɽ���
	pOrder.MinVolume = Order.MinVolume;
	// ��������
	pOrder.ContingentCondition = APEX_FTDC_CC_Immediately;
	// ֹ���
	pOrder.StopPrice = Order.StopPrice;
	// ǿƽԭ��
	pOrder.ForceCloseReason = Order.ForceCloseReason;
	// �Զ������־
	pOrder.IsAutoSuspend = Order.IsAutoSuspend;
	//BU
	strncpy(pOrder.BusinessUnit,Order.BusinessUnit.getValue(),sizeof(pOrder.BusinessUnit)-1);
}

void CApexTradeLink::TransReqOrderAction(CApexFtdcOrderActionField &pOrderAction,COrderActionField &OrderAction)
{
	//ϵͳ������
	strncpy(pOrderAction.OrderSysID,OrderAction.OrderSysID.getValue(),sizeof(pOrderAction.OrderSysID)-1);
	//���ر�����
	strncpy(pOrderAction.OrderLocalID,OrderAction.OrderLocalID.getValue(),sizeof(pOrderAction.OrderLocalID)-1);
	//������־
	pOrderAction.ActionFlag = OrderAction.ActionFlag.getValue();
	//��Ա��
	strncpy(pOrderAction.ParticipantID,OrderAction.ParticipantID.getValue(),sizeof(pOrderAction.ParticipantID)-1);
	//�ͻ���
	strncpy(pOrderAction.ClientID,OrderAction.ClientID.getValue(),sizeof(pOrderAction.ClientID)-1);
	//�����û�
	strncpy(pOrderAction.UserID,OrderAction.SeatID.getValue(),sizeof(pOrderAction.UserID)-1);
	//�������ر��
	strncpy(pOrderAction.ActionLocalID,OrderAction.ActionLocalID.getValue(),sizeof(pOrderAction.ActionLocalID)-1);
	//�����仯
	pOrderAction.VolumeChange = OrderAction.VolumeChange.getValue();
	//�����û�
	strncpy(pOrderAction.UserID,OrderAction.SeatID.getValue(),sizeof(pOrderAction.UserID)-1);
	//BU
//	strncpy(pOrderAction.BusinessUnit,OrderAction.UserOrderLocalID,sizeof(pOrderAction.BusinessUnit)-1);
}