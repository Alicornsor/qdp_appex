#include "InnerTradeLink.h"
#include "XtpPackageDesc.h"
#include "XtpData.h"
#include "CachedFileFlow.h"

CInnerTradeLink::CInnerTradeLink(const char *pSendAdr)
{
	memset(m_sIdInfo,0,sizeof(m_sIdInfo));
	m_TradeDate = 0;
	m_iMaxLocalNo = 0;
	m_iReqSeqNo = 0;
	m_bLogin = false;
	m_Status = '9';

	m_pSeriesFlow = new CExCachedFlow(false, 0x7fffffff, 0x100000);
	m_reader.AttachFlow(m_pSeriesFlow, 0);

	m_pPubPackage = new CXTPPackage();
	m_pPubPackage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	m_bInitSeat = false;

	strncpy(m_sSendAdr,pSendAdr,sizeof(m_sSendAdr)-1);
	m_sSendAdr[sizeof(m_sSendAdr)-1] = 0;
	trim(m_sSendAdr);
	/*strncpy(m_sRecvAdr,pRecvAdr,sizeof(m_sRecvAdr)-1);
	m_sRecvAdr[sizeof(m_sRecvAdr)-1] = 0;
	trim(m_sRecvAdr);*/
}

CInnerTradeLink::~CInnerTradeLink()
{
	delete m_pPubPackage;
}


void CInnerTradeLink::StartWork()
{	
	//���Ͷ�����
//	m_pSendFlow = new CCachedFileFlow("send","",false, 0x7fffffff, 0x100000);
	CSelectReactor *pSendReactor= new CSelectReactor();
	//m_pSendGetWay = new CTcpXtpGateway(pSendReactor,m_pSendFlow,NULL);
	//m_pSendGetWay->RegisterListener(pSendAdr);
	//m_pSendGetWay->Init();
	m_pSendClient = new CXtpClient(pSendReactor, m_pSeriesFlow, 0, NULL);
	m_pSendClient->RegClientCallback(this);
	m_pSendClient->RegisterReportServer(m_sSendAdr);
	m_pSendClient->Init();	

	/*CSelectReactor *pRecvReactor= new CSelectReactor();
	m_pRevSessionFactory = new CTcpXtpSessionFactory(m_pSeriesFlow,pRecvReactor,0,NULL);
	m_pRevSessionFactory->RegisterReportServer(m_sRecvAdr);
	m_pRevSessionFactory->Init();*/
}

int CInnerTradeLink::ReqOrderInsert(CInputOrderField &Order)
{
	if(!m_bLogin)
		return -1;
	//����localid
//	Order.OrderLocalID = GetLocalID();
	//����ϯλ��Ϣ
//	Order.UserID = m_Seat.SeatID; 

	//���
	m_pPubPackage->PreparePublish(TID_ReqOrderInsert);
	XTP_ADD_FIELD(m_pPubPackage, &Order);
	int ret = m_pSendClient->SendReportPackage(m_pPubPackage);

#ifdef PERFORM_TEST
    long ltm;
    GET_ACCURATE_USEC_TIME(ltm);
    printf("SendTo%s, %ld,",m_Seat.ExchangeID.getValue(),ltm);   
#endif	
	return ret;
}

int CInnerTradeLink::ReqOrderInsert(CWriteablePreOrder &Order, bool needOrderLocalID)
{
	if(!m_bLogin)
		return -1;

	Order.SeatID = m_Seat.SeatID;
	if (needOrderLocalID)
	{
		Order.OrderLocalID = GetLocalID();
	}
	Order.APIID = m_Seat.APIID;

	//���
	m_pPubPackage->PreparePublish(TID_ReqOrderInsert);
	XTP_ADD_FIELD(m_pPubPackage, &Order);
	int ret = m_pSendClient->SendReportPackage(m_pPubPackage);
	
#ifdef PERFORM_TEST
    long ltm;
    GET_ACCURATE_USEC_TIME(ltm);
    printf("SendTo%s, %ld,",m_Seat.ExchangeID.getValue(),ltm);   
#endif	
	return ret;
}

int CInnerTradeLink::ReqOrderAction(COrderActionField &OrderAction)
{
	if(!m_bLogin)
		return -1;

	//����localid
//	OrderAction.ActionLocalID = GetLocalID();
	//����ϯλ��Ϣ
	OrderAction.UserID = m_Seat.SeatID; 
	//���
	m_pPubPackage->PreparePublish(TID_ReqOrderAction);
	XTP_ADD_FIELD(m_pPubPackage, &OrderAction);
	int ret = m_pSendClient->SendReportPackage(m_pPubPackage);

#ifdef PERFORM_TEST
    long ltm;
    GET_ACCURATE_USEC_TIME(ltm);
    printf("SendTo%s, %ld,",m_Seat.ExchangeID.getValue(),ltm);   
#endif

	return ret;	
}


bool CInnerTradeLink::ReqQryInvestorPosition(CQryInvestorPositionField &pInvestor)
{
	if(!m_bLogin)
		return false;
	//����localid
	//	Order.OrderLocalID = GetLocalID();
	//����ϯλ��Ϣ
	pInvestor.InvestorID = m_Seat.SeatID; 
	
	//���
	m_pPubPackage->PreparePublish(TID_ReqQryInvestorPosition);
	XTP_ADD_FIELD(m_pPubPackage, &pInvestor);
	int ret = m_pSendClient->SendReportPackage(m_pPubPackage);
	
#ifdef PERFORM_TEST
    long ltm;
    GET_ACCURATE_USEC_TIME(ltm);
    printf("SendTo%s, %ld,",m_Seat.ExchangeID.getValue(),ltm);   
#endif	
	if(ret==0)
		return true;	
	else
		return false;
}

bool CInnerTradeLink::ReqQry(CInputOrderField &pInvestor)
{
	if(!m_bLogin)
		return false;
	//����localid
//	Order.OrderLocalID = GetLocalID();
	//����ϯλ��Ϣ
	pInvestor.UserID = m_Seat.SeatID; 
	
	//���
	m_pPubPackage->PreparePublish(TID_ReqQryOrder);
	XTP_ADD_FIELD(m_pPubPackage, &pInvestor);
	int ret = m_pSendClient->SendReportPackage(m_pPubPackage);

#ifdef PERFORM_TEST
    long ltm;
    GET_ACCURATE_USEC_TIME(ltm);
    printf("SendTo%s, %ld,",m_Seat.ExchangeID.getValue(),ltm);   
#endif	
	if(ret==0)
		return true;	
	else
		return false;
}

bool CInnerTradeLink::RspQryInvestorPosition(CInvestorPositionField &pInvestor)
{
	if(!m_bLogin)
		return false;
// 	bool successful=true ;
// 	COrderActionField oFld;
// 	//�������memset��COrderActionField��һ��struct
//  	memset(&oFld,0,sizeof(oFld));
// 	//���ر������
// 	oFld.ActionLocalID=GetLocalID(OrderAction.ClientID.getValue());
// 	//�����û�����
// 	oFld.UserID=m_Seat.SeatID;
// 	//��Ա����
// 	oFld.ParticipantID=m_Seat.ParticipantID;
//	return successful; 

	//����localid
//	OrderAction.ActionLocalID = GetLocalID();
	//����ϯλ��Ϣ
//	OrderAction.UserID = m_Seat.SeatID; 
	//���
	m_pPubPackage->PreparePublish(TID_RspQryInvestorPosition);
	XTP_ADD_FIELD(m_pPubPackage, &pInvestor);
	int ret = m_pSendClient->SendReportPackage(m_pPubPackage);

#ifdef PERFORM_TEST
    long ltm;
    GET_ACCURATE_USEC_TIME(ltm);
    printf("SendTo%s, %ld,",m_Seat.ExchangeID.getValue(),ltm);   
#endif
	if(ret==0)
		return true;	
	else
		return false;
}

void CInnerTradeLink::InterLogin()
{
//	m_Seat.SeatID="x2";
 	CUserLoginField field; 
	field.UserID = m_Seat.SeatID;
	field.MaxCommFlux = m_pSendClient->m_nsubcount;
 	m_pPubPackage->PreparePublish(TID_ReqUserLogin);
 	m_pPubPackage->AddField(&CUserLoginField::m_Describe,&field);
	m_pSendClient->SendReportPackage(m_pPubPackage);
}

void CInnerTradeLink::InterLogined(CInterLoginInfoField *pInterLoginInfoField)
{
	//m_bLogin = true;
	//���ñ��������

	//m_iMaxLocalNo = pInterLoginInfoField->MaxLocalID;

	//�������������ճ���
	//���ն�����,�������ļ�
	//���������ϯ������Ҫ�������ն�

	if(!m_Seat.RecvRtn)
	{
		return;
	}

	
	//���ͽ��ױ���Ͷ������Ϣ
	for (VecClientTradingID::iterator iter=m_ClientTradingIDVec.begin();iter !=m_ClientTradingIDVec.end();iter++)
	{
		m_pPubPackage->PreparePublish(TID_InitClientTradingID);
		XTP_ADD_FIELD(m_pPubPackage,*iter);
		m_pSendClient->SendReportPackage(m_pPubPackage);
	}

	//��¼�ɹ�֮����ϯλ��Ϣ	
	m_pPubPackage->PreparePublish(TID_InitSeat);
	XTP_ADD_FIELD(m_pPubPackage, &m_Seat);
	int ret = m_pSendClient->SendReportPackage(m_pPubPackage);
}

void CInnerTradeLink::OnSessionConnected(CSession *pSession)
{
	InterLogin();
}

void CInnerTradeLink::OnSessionDisconnected(CSession *pSession, int nReason)
{
	m_bLogin = false;
}


bool CInnerTradeLink::GetNextUseNoBuf(CPackage *pPackage)
{
	bool bRet = m_reader.GetNextUseNoBuf(pPackage);
	if (!bRet)
		return false;

	//�ڼ���InnerLink����ͬһ�����̻���ʱ�����ڱ��̻�������еı��ķ��͸�innerlink��
	//��ʱ��Ҫ���˵��Ǳ�ϯλ���̵ı���

	if (((CXTPPackage *)pPackage)->GetAPIID() == m_Seat.APIID)
	{
		return true;
	}
	else
	{
		return false;
	}

	return true;
}

char *CInnerTradeLink::GetLocalID(char cExchangID)
{	
	sprintf(m_sMaxLocalNo,"%010u",++m_iMaxLocalNo);
	return m_sMaxLocalNo;
}

void CInnerTradeLink::InitClientTradingID(CClientTradingIDField *clientTradingID)
{
	CClientTradingIDField *pField = new CClientTradingIDField;
	memcpy(pField,clientTradingID,sizeof(CClientTradingIDField));
	m_ClientTradingIDVec.push_back(pField);
}

void CInnerTradeLink::SetMaxLocalID(int nMaxLocalID)
{
	//���ñ��������
	if (m_iMaxLocalNo < nMaxLocalID)
		m_iMaxLocalNo = nMaxLocalID;
	m_bLogin = true;
	REPORT_EVENT(LOG_CRITICAL,"CInnerTradeLink::SetMaxLocalID","maxlocalid:%d", m_iMaxLocalNo);
}

int CInnerTradeLink::GetAPIID()
{
	return m_Seat.APIID.getValue();
}

// bool CInnerTradeLink::ReqQryInnerInvestorAccount(CQryInnerInvestorAccountField &pInvestor)
// {
// 	if(!m_bLogin)
// 		return false;
// 	
// 	//���
// 	m_pPubPackage->PreparePublish(TID_ReqQryInnerInvestorAccount);
// 	m_pPubPackage->SetSessionID(pInvestor.SessionID);
// 	m_pPubPackage->SetFrontID(pInvestor.FrontID);
// 	m_pPubPackage->SetRequestID(pInvestor.RequestID);
// 	XTP_ADD_FIELD(m_pPubPackage, &pInvestor);
// 	int ret = m_pSendClient->SendReportPackage(m_pPubPackage);
// 
// 	if(ret==0)
// 		return true;	
// 	else
// 		return false;
// }

// bool CInnerTradeLink::ReqQryInnerInvestorPosition(CQryInnerInvestorPositionField &pInvestor)
// {
// 	if(!m_bLogin)
// 		return false;
// 	
// 	//���
// 	m_pPubPackage->PreparePublish(TID_ReqQryInnerInvestorPosition);
// 	m_pPubPackage->SetSessionID(pInvestor.SessionID);
// 	m_pPubPackage->SetFrontID(pInvestor.FrontID);
// 	m_pPubPackage->SetRequestID(pInvestor.RequestID);
// 	XTP_ADD_FIELD(m_pPubPackage, &pInvestor);
// 	int ret = m_pSendClient->SendReportPackage(m_pPubPackage);
// 
// 	if(ret==0)
// 		return true;	
// 	else
// 		return false;
// }

CSGETradeLink::CSGETradeLink(const char *pSendAdr)
:CInnerTradeLink(pSendAdr)
{
	
}

CSGETradeLink::~CSGETradeLink()
{
	
}

char * CSGETradeLink::GetLocalID(char cExchangID)
{
	sprintf(m_sMaxLocalNo,"%08u",++m_iMaxLocalNo);
	return m_sMaxLocalNo;
}
