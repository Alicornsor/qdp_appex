#include "Processor.h"
#include "QdpFtdcUserApiDataType.h"
#include "errorDefine.h"


extern const char * INI_FILE_NAME;
extern ST_INPUT_CMD  *sInputCmd;
extern ST_INPUT_CMD  *sInputCmdArray;
extern bool bFastFlag;
extern bool bCmdLFlag;
extern int  iMarcoCount;
extern ST_MARCO sMarcoArray[200];
extern int iWaitOrderPos;
extern int iLastCmdPos;		// ���һ��ί��Ӧ���InputCmd �� ���
extern int iCurCmdPos;		// ��ǰ�ύ��InputCmd �� ���


extern char  m_TradeIp[30];
extern char  m_DefaultUser[30];
extern char  m_DefaultPass[30];

extern int iWaitOrderPos;  // ��;ί������ 
extern int iTotalOrderCnt;  // ��ί������
extern UF_INT8    lReqTime;    //����ʼʱ�� 
extern UF_INT8    lRspTime;	   //�������ʱ��

CProcessor::CProcessor(int iId)
{
	memset(m_sUserID,0,sizeof(m_sUserID));
	memset(m_sPassword,0,sizeof(m_sPassword));

	m_iLocalNo = 0;
	m_nRequestID = 0;
	m_nRecvCount = 0;
	m_bTradeIsLogin = false;

	m_semAction.Lock();
	m_fOutFile = NULL;

	m_bFirstPackage = true;
	m_bNoOut = false;
	m_bConnected = false;
	m_InstrumentStatusMap.clear();
	m_pFfexFtdcUserApi = NULL;
	m_iId = iId;
	m_bWaitResult = true;
}
CProcessor::CProcessor(int iId,char *pBrokerID,char *pUserID,char *pPassword,FILE* fOut,bool bUserType)
{
	memset(m_sBrokerID,0,sizeof(m_sBrokerID));
	memset(m_sUserID,0,sizeof(m_sUserID));
	memset(m_sPassword,0,sizeof(m_sPassword));

	strncpy(m_sBrokerID,pBrokerID,sizeof(m_sBrokerID));
	strncpy(m_sUserID,pUserID,sizeof(m_sUserID));
	strncpy(m_sPassword,pPassword,sizeof(m_sPassword));
	
	m_iLocalNo = 0;
	m_nRequestID = 0;
	m_nRecvCount = 0;
	m_bTradeIsLogin = false;
	m_iId = iId;
	char sTemp[50];
	sprintf(sTemp,"./flow/Trade%d",iId);
	m_pFfexFtdcUserApi = CQdpFtdcUserApi::CreateFtdcUserApi(sTemp);
	m_pFfexFtdcUserApi->RegisterSpi(this);
//	m_pFfexFtdcUserApi->SubscribePrivateTopic(TERT_QUICK);
//	m_pFfexFtdcUserApi->SubscribePublicTopic(TERT_QUICK);

	//20140425 ���Ӷ���ģʽ���趨
	//tload���ڻ�Ƶ������ǳ�ϵͳ��������ķ�ʽ���ò��ԣ���������
	//�������Ϊrestart������Ƶ����¼�������front ��slog ����
	//�������Ϊquick����Ҫ�����Ƿ���Ҫ��������׼ȷ�Ե�����

// 	TE_RESUME_TYPE resumeType=TERT_QUICK;
 	m_pConfig = new CConfig(INI_FILE_NAME);
// 	int resumeTypeInt=atoi(m_pConfig->getConfig("ResumeType"));
// 	switch(resumeTypeInt)
// 	{
// 	case 0:
// 		{
// 			resumeType=TERT_RESTART;
// 			break;
// 		}
// 	case 1:
// 		{
// 			resumeType=TERT_RESUME;
// 			break;
// 		}
// 	case 2:
// 		{
// 			resumeType=TERT_QUICK;
// 			break;
// 		}
// 	default:
// 		{
// 			printf("���� ResumeType ֵ����! ����quickģʽ \n");
// 		}
// 	}
	

//	m_pFfexFtdcUserApi->SubscribePublicTopic(resumeType);	
//	if (bUserType)
//	{
//		m_pFfexFtdcUserApi->SubscribeUserTopic(resumeType);
//	}
//	else
//	{
//		m_pFfexFtdcUserApi->SubscribePrivateTopic(resumeType);
//	}
	
	m_pFfexFtdcUserApi->RegisterFront(m_TradeIp);
	m_bReLogin = false;
	m_fOutFile = NULL;
	m_bFirstPackage = true;
	m_bNoOut = false;
	m_bConnected = false;
	m_InstrumentStatusMap.clear();
	m_bWaitResult = true;
	m_nSleepControl=1;
	m_nSleepControl=atoi(m_pConfig->getConfig("SleepControl"));
	m_bResend = false;

	m_fp_out = fOut;

	m_pFfexFtdcUserApi->OpenResponseLog("Response.log");
	m_pFfexFtdcUserApi->Init(12000);
	m_semAction.Lock();
	//�ȴ�ǰ�õ�onFrontConnect����
	m_semAction.Lock(20);
}
CProcessor::~CProcessor()
{	
	delete m_pConfig;
}

void CProcessor::WaitAction(int iTimeOut)
{
	sInputCmd->bReciveRsp=false;
	//ShowMsg("\n set bReciveRsp false %d \n",x);	
	//20140516 xuzh ����һ���ȴ�ʱ�䣬��λΪ���룬���ڿ����ٶ�
	SLEEP(m_nSleepControl);
	//20140508 xuzh �̵߳��û��г�ͻ���⣬�����ǳ�ʱ�ȴ�
	m_semAction.Lock(iTimeOut);
}

void CProcessor::EndAction()
{
	//ShowMsg("\n set bReciveRsp ture %d\n",x);
	sInputCmd->bReciveRsp=true;
	m_semAction.UnLock();
}

void CProcessor::Release()
{
	CQdpFtdcReqUserLogoutField ReqField;
	memset(&ReqField,0,sizeof(ReqField));

	strcpy(ReqField.BrokerID,m_sBrokerID);
	strcpy(ReqField.UserID,m_sUserID);

	m_pFfexFtdcUserApi->ReqUserLogout(&ReqField,m_nRequestID++);
	
	m_pFfexFtdcUserApi->Release();
	m_pFfexFtdcUserApi = NULL;
	if (NULL != m_fOutFile)
	{
		fclose(m_fOutFile);
		m_fOutFile = NULL;
	}
	m_bReLogin = false;
}

///��ʼ��
void CProcessor::Init() 
{
	m_pFfexFtdcUserApi->Init(12000);
}
int CProcessor::Join()
{
	return m_pFfexFtdcUserApi->Join();
}
const char *CProcessor::GetTradingDay()
{
	return m_pFfexFtdcUserApi->GetTradingDay();
}
///�û���¼����
int CProcessor::ReqUserLogin(char *pBrokerID,char *pUser,char *pPassword)
{
	if (!m_bConnected)
	{
		ShowMsg("\n UserLogin Error : δ���� \n");
		return -3;
	}
	CQdpFtdcReqUserLoginField ReqField;
	memset(&ReqField,0,sizeof(ReqField));
	strcpy(ReqField.TradingDay, GetTradingDay());
	
	if (NULL == pBrokerID)
	{
		strcpy(ReqField.BrokerID,m_sBrokerID);
	}
	else
	{
		strcpy(ReqField.BrokerID,pBrokerID);
		strcpy(m_sBrokerID,pBrokerID);
	}

	if (NULL == pUser)
	{
		strcpy(ReqField.UserID,m_sUserID);
	}
	else
	{
		strcpy(ReqField.UserID,pUser);
		strcpy(m_sUserID,pUser);
	}
	if (NULL == pPassword)
	{
		strcpy(ReqField.Password,m_sPassword);
	}
	else
	{
		strcpy(ReqField.Password,pPassword);
		strcpy(m_sPassword,pPassword);
	}
	
	strcpy(ReqField.UserProductInfo,"TLOAD QDP ����̨�ͻ���v1.0");
	GET_ACCURATE_USEC_TIME(lReqTime);
	int res = m_pFfexFtdcUserApi->ReqUserLogin(&ReqField,m_nRequestID++);
	return res;
}

///////////////////////////////////////////////////////////////////////////////////
///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
void CProcessor::OnFrontConnected()
{
	m_bConnected = true;
	
	if(m_bReLogin)
	{
		ShowMsg("\n OnConnect : relogin: \n");
		ReqUserLogin(NULL,NULL,NULL);
	}
	else
	{
		ShowMsg("\n OnConnect: nologin: \n");
		m_semAction.UnLock();
	}
};

void CProcessor::OnFrontDisconnected(int nReason)
{
	char buf[200] = {0};	
	
	ShowMsg("\n warning : disconnect �����ж�,������� %d \n",nReason);
	m_bTradeIsLogin = false;
	m_bConnected = false;
	m_bReLogin = true;
//	exit(9);
}

void CProcessor::OnRtnInstrumentStatus(CQdpFtdcInstrumentStatusField *pInstrumentStatus)
{
	ShowMsg("��Լ״̬֪ͨ,%s==>[%c]\n",pInstrumentStatus->InstrumentID,pInstrumentStatus->InstrumentStatus);
	return ;
}

void CProcessor::OnRspUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (m_nRequestID-1 == nRequestID)
	{
		memcpy(&sInputCmd->pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));

		if (NULL != pRspInfo) 
		{
			m_iRspValue = pRspInfo->ErrorID;
		}
		if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
		{		
			Output("%s,�޸������л�ʧ�ܣ�ԭ��:%s",sInputCmd->sCmdNo,pRspInfo->ErrorMsg);	
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}
		Output("%s,�޸�����ɹ�: %s@%s : %s -> %s",sInputCmd->sCmdNo,pUserPasswordUpdate->UserID,pUserPasswordUpdate->BrokerID,pUserPasswordUpdate->OldPassword,pUserPasswordUpdate->NewPassword); 
		if (m_bWaitResult)
		{
			EndAction();
		}

	}
}

void CProcessor::OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	m_nRecvCount ++;

	if (m_nRequestID)
	{
		GET_ACCURATE_USEC_TIME(lRspTime);
		char buf[200] = {0};
		int delay = lRspTime-lReqTime;
		ShowMsg("������ %s ʱ�� %s ��󱨵���[%s] rsplogin delay[%ld]us",	pRspUserLogin->TradingDay,pRspUserLogin->LoginTime,
			pRspUserLogin->MaxOrderLocalID,delay);
		strcat(sInputCmd->sNote,buf);
		memcpy(&sInputCmd->pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));

		ShowMsg(" ==> ");

		if (0 != pRspInfo->ErrorID) 
		{			
			EndAction();
			m_bTradeIsLogin = false;
			ShowMsg("ʧ��,%s",pRspInfo->ErrorMsg);
			if(m_bReLogin)
			{
				ReqUserLogin(NULL,NULL,NULL);
			}
			return;
		}	



		m_bTradeIsLogin = true;
		///��Ա����
		memset(m_sBrokerID,0,sizeof(m_sBrokerID));
		strcpy(m_sBrokerID,pRspUserLogin->BrokerID);
		//�ϴ���󱾵ر�����
		//����Ƕ�����������ȡ���ر�����
		if(!m_bReLogin)
		{
			m_iLocalNo = atoi(pRspUserLogin->MaxOrderLocalID) + 1;
			EndAction();
		}
		m_bReLogin = false;
	}
}

///�ʽ�Ӧ��
void CProcessor::OnRspQryInvestorAccount(CQdpFtdcRspInvestorAccountField *pRspInvestorAccount, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (m_nRequestID-1 == nRequestID)
	{
		memcpy(&sInputCmd->pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));

		if (NULL != pRspInfo) 
		{
			m_iRspValue = pRspInfo->ErrorID;
		}
		if (m_bNoOut)
		{
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}

		if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
		{		
			Output("�ʽ��ѯʧ�ܣ�ԭ��:%s",pRspInfo->ErrorMsg);		
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}
		if (NULL == pRspInvestorAccount)
		{
			Output("���޼�¼");	
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}
		if (m_bFirstPackage)
		{		
			m_bFirstPackage = false;
			m_iTotalRecordCnt = 1;
			ShowMsg(" ==> ");	
		}	
		else
		{
			m_iTotalRecordCnt++;
		}

		sInputCmd->dFrozenMargin = pRspInvestorAccount->FrozenMargin;
		sInputCmd->dCurrMargin = pRspInvestorAccount->Margin;
		sInputCmd->dCurMoney = pRspInvestorAccount->Available;

		char szbuf[1024];
		sprintf(szbuf,"BrokerID:%s,InvestorID:%s,AccountID:%s,LongFrozenMargin:%.3f,ShortFrozenMargin:%.3f,FrozenMargin:%.3f,FrozenFee:%.3f,\
LongMargin:%.3f,ShortMargin:%.3f,Margin:%.3f,Fee:%.3f,CloseProfit:%.3f,PositionProfit:%.3f,\
Balance:%.3f,Available:%.3f,Deposit:%.3f,Withdraw:%.3f,FrozenPremium:%.3f,Premium:%.3f",
			pRspInvestorAccount->BrokerID,\
			pRspInvestorAccount->InvestorID,\
			pRspInvestorAccount->AccountID,\
			pRspInvestorAccount->LongFrozenMargin,\
			pRspInvestorAccount->ShortFrozenMargin,\
			pRspInvestorAccount->FrozenMargin,\
			pRspInvestorAccount->FrozenFee,\
			pRspInvestorAccount->LongMargin,\
			pRspInvestorAccount->ShortMargin,\
			pRspInvestorAccount->Margin,\
			pRspInvestorAccount->Fee,\
			pRspInvestorAccount->CloseProfit,\
			pRspInvestorAccount->PositionProfit,\
			pRspInvestorAccount->Balance,\
			pRspInvestorAccount->Available,\
			pRspInvestorAccount->Deposit,\
			pRspInvestorAccount->Withdraw,\
			pRspInvestorAccount->FrozenPremium,\
			pRspInvestorAccount->Premium);		
		strcat(sInputCmd->sNote,szbuf);
		ShowMsg(szbuf);
		if (bIsLast) 
		{
			if (m_bWaitResult)
			{
				EndAction();
			}
		}
	}
}

//������ѯӦ��
void CProcessor::OnRspQryOrder(CQdpFtdcOrderField *pOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	if (m_nRequestID-1 == nRequestID)
	{
		if (NULL != pRspInfo) 
		{
			m_iRspValue = pRspInfo->ErrorID;
		}
		if (0 == strcmp(sInputCmd->sCmdType,"QRYORDER"))
		{
			memcpy(&sInputCmd->pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));
			if(bFastFlag == false)
			ShowMsg(" ==> ");
		}		
		if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
		{							
			if(bFastFlag == false)
				ShowMsg("������ѯʧ�ܣ�ԭ��:%s\n",pRspInfo->ErrorMsg);
	
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}
		if (NULL == pOrder)
		{			
			if(bFastFlag == false)
				ShowMsg("���޼�¼\n");

			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}
		if (m_bFirstPackage)
		{		
			m_bFirstPackage = false;
			m_iTotalRecordCnt = 0;	
		}	

		//	�������пɳ�����OrderSysid	// ���ֳɽ����ڶ�����// δ�ɽ����ڶ�����
		if(pOrder->OrderStatus == QDP_FTDC_OS_PartTradedQueueing || pOrder->OrderStatus == QDP_FTDC_OS_NoTradeQueueing)
		{
			m_iTotalRecordCnt++;
		}

		char szbuf[1024];
		//20120703 jiangyuan �������	
		sprintf(szbuf,"OrderSysID:%s,InstrumentID:%s,OrderStatus:%c,LimitPrice:%.3f,Volume:%d,\
VolumeTraded:%d,OrderSource:%c,ForceCloseReason:%c,\
OrderPriceType:%c,Direction:%c,HedgeFlag:%c,OffsetFlag:%c,TimeCondition:%c",\
		pOrder->OrderSysID,pOrder->InstrumentID,pOrder->OrderStatus,\
		pOrder->LimitPrice,pOrder->Volume,pOrder->VolumeTraded,\
		pOrder->OrderSource,pOrder->ForceCloseReason,\
		pOrder->OrderPriceType,pOrder->Direction,pOrder->HedgeFlag,\
		pOrder->OffsetFlag,pOrder->TimeCondition);
		strcat(sInputCmd->sNote,szbuf);	
		ShowMsg(szbuf);
		//20120703 end	
		if(bFastFlag == false)
			ShowMsg(" => ��ѯ�ɹ�\n");	

		if (bIsLast) 
		{
			if (m_bWaitResult)
			{
				EndAction();
			}
		}
	}
}

///�ɽ�����ѯӦ��
void CProcessor::OnRspQryTrade(CQdpFtdcTradeField *pTrade, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (m_nRequestID-1 == nRequestID)
	{
		if (NULL != pRspInfo) 
		{
			m_iRspValue = pRspInfo->ErrorID;
			
			memcpy(&sInputCmd->pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));
			if(bFastFlag == false)
			ShowMsg(" ==> ");
		}

	
		if (m_bNoOut)
		{
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}
		if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
		{	
		
			if(bFastFlag == false)
				ShowMsg("�ɽ���ѯʧ�ܣ�ԭ��:%s\n",pRspInfo->ErrorMsg);
			
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}
		if (NULL == pTrade)
		{
			//Output("���޼�¼");
			if(bFastFlag == false)
					ShowMsg("���޼�¼\n");
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}
		if (m_bFirstPackage)
		{		
			m_bFirstPackage = false;
			m_iTotalRecordCnt = 1;
			/*Output("%13s%13s%9s%7s%9s%9s%9s%9s%9s%6s%9s",\
				"�ɽ����","�������","��Ա��","�ͻ���","ϯλ��",\
				"��Լ��","��������","��ƽ��־","�۸�","����",\
				"�ɽ�ʱ��");*/		
		}	
		else
		{
			m_iTotalRecordCnt++;
		}
		
		/*Output("%13s%13s%9s%9s%7s%9s%9s%9s%9.2f%6d%9s",pTrade->TradeID,\
			pTrade->OrderSysID,\
			pTrade->ParticipantID,pTrade->ClientID,\
			pTrade->UserID,pTrade->InstrumentID,\
			GetBsflag(pTrade->Direction),GetOffsetFlag(pTrade->OffsetFlag),\
			pTrade->Price,pTrade->Volume,\
			pTrade->TradeTime);*/
		if (strcmp(sInputCmd->ReqField.OrderSysID,pTrade->OrderSysID) == 0)
		{
			char szbuf[1024];
			//20120703 jiangyuan �������	
			sprintf(szbuf,"TradeID:%s,OrderSysID:%s,ParticipantID:%s,ClientID:%s,\
					UserID:%s,InstrumentID:%s,Direction:%c,OffsetFlag:%c,\
					Price:%.3f,TradeVolume:%d,TradeTime:%s,HedgeFlag:%c",\
					pTrade->TradeID,\
					pTrade->OrderSysID,\
					pTrade->ParticipantID,pTrade->ClientID,\
					pTrade->UserID,pTrade->InstrumentID,\
					pTrade->Direction,pTrade->OffsetFlag,\
					pTrade->TradePrice,pTrade->TradeVolume,\
					pTrade->TradeTime,\
					pTrade->HedgeFlag);
			//20120703 end	
			strcat(sInputCmd->sNote,szbuf);	
			if(bFastFlag == false)
					ShowMsg("��ѯ�ɹ�\n");
		}

		if (bIsLast) 
		{
//			Output("�ܹ� %d ���ɽ���",m_iTotalRecordCnt);
			if (m_bWaitResult)
			{
				EndAction();
			}
		}
	}
}


///����Ӧ��
void CProcessor::OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CProcessor::OnRspUserLogout(CQdpFtdcRspUserLogoutField *pRspUserLogout, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
}

///��Լ��ѯӦ��
void CProcessor::OnRspQryInstrument(CQdpFtdcRspInstrumentField *pRspInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if (m_nRequestID-1 != nRequestID)
		return;

	if (NULL != pRspInfo) 
	{
		m_iRspValue = pRspInfo->ErrorID;
		memcpy(&sInputCmd->pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));
	}

	if (m_bFirstPackage)	
	{
		ShowMsg(" ==> ");
		m_bFirstPackage = false;
		m_iTotalRecordCnt = 1;
	}	
	else
	{
		m_iTotalRecordCnt++;
	}


	if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
	{	
		ShowMsg("ʧ��, %s",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
		if (m_bWaitResult)
		{
			EndAction();
		}
		return;
	}

	if (NULL == pRspInstrument)
	{
		ShowMsg("ʧ��, ���޼�¼");
		if (m_bWaitResult)
		{
			EndAction();
		}
		return;
	}


	//����Լ��Ϣ����ȫ�ֺ�
	iMarcoCount ++;
	sMarcoArray[iMarcoCount].iType = 0;    //	�ַ�
	sprintf(sMarcoArray[iMarcoCount].sMarcoId,"#%s_%d#",
			"INSTRUMENT",m_iTotalRecordCnt);
	strcpy(sMarcoArray[iMarcoCount].sMarcoValue,pRspInstrument->InstrumentID);
	
	//ȫ�ֺ��¼����
	//��ӡ��Լ����
	ShowMsg("%.3f,%d,%d,%d,%d,%.3f,%d\n",
			pRspInstrument->BasisPrice,
			pRspInstrument->MaxMarketOrderVolume,
			pRspInstrument->MinMarketOrderVolume,
			pRspInstrument->MaxLimitOrderVolume,
			pRspInstrument->MinLimitOrderVolume,
			pRspInstrument->PriceTick,
			pRspInstrument->VolumeMultiple);

	if (bIsLast) 
	{
		if (m_bWaitResult)
		{
			EndAction();
		}
	}
}

///�ͻ��ֲֲ�ѯӦ��
void CProcessor::OnRspQryInvestorPosition(CQdpFtdcRspInvestorPositionField *pRspInvestorPosition, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (m_nRequestID-1 != nRequestID)
		return;

	if (NULL != pRspInfo) 
	{
		m_iRspValue = pRspInfo->ErrorID;
	}

	memcpy(&sInputCmd->pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));

	if (m_bFirstPackage)	
	{
		m_bFirstPackage =  false;
		ShowMsg(" ==> ");
	}
	if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
	{		
		ShowMsg("ʧ��, %s",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
		if (m_bWaitResult)
		{
			EndAction();
		}
		return;
	}

	if (NULL == pRspInvestorPosition)
	{
		ShowMsg("ʧ��, ���޼�¼");
		if (m_bWaitResult)
		{
			EndAction();
		}
		return;
	}

	if (m_bFirstPackage)
	{		
		m_bFirstPackage = false;
		m_iTotalRecordCnt = 1;
	}	
	else
	{
		m_iTotalRecordCnt++;
	}

	char szbuf[1024];
	sprintf(szbuf," || BrokerID:%s,InvestorID:%s,InstrumentID:%s,Direction:%c,HedgeFlag:%c,UseMargin:%.3f,Position:%d,\
PositionCost:%.3f,FrozenMargin:%.3f,FrozenPosition:%d,FrozenClosing:%d,FrozenPremium:%.3f",
		pRspInvestorPosition->BrokerID,
		pRspInvestorPosition->InvestorID,
		pRspInvestorPosition->InstrumentID,
		pRspInvestorPosition->Direction,
		pRspInvestorPosition->HedgeFlag,
		pRspInvestorPosition->UsedMargin,
		pRspInvestorPosition->Position,
		pRspInvestorPosition->PositionCost,
		pRspInvestorPosition->FrozenMargin,
		pRspInvestorPosition->FrozenPosition,
		pRspInvestorPosition->FrozenClosing,
		pRspInvestorPosition->FrozenPremium);
	strcat(sInputCmd->sNote,szbuf);	
	ShowMsg(szbuf);

	if (bIsLast) 
	{
		if (m_bWaitResult)
		{
			EndAction();
		}
	}
}

///��Ա�ͻ���ѯӦ��
//void CProcessor::OnRspQryClient(CQdpFtdcRspClientField *pRspClient, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//}

///����¼��Ӧ��
void CProcessor::OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	// ����ϵͳ�����ţ���������
	GET_ACCURATE_USEC_TIME(lRspTime);
#ifdef WIN32
	printf("RecvRsp UserOrderLocalID[%s]-[%I64d],",pInputOrder->UserOrderLocalID,lRspTime);
#else
	printf("RecvRsp UserOrderLocalID[%s]-[%lld],",pInputOrder->UserOrderLocalID,lRspTime);
#endif
//	printf("||| %d --- %d \n",m_nRequestID,nRequestID);
	int i;

	m_nRecvCount ++;
	
	iWaitOrderPos++;
	
	//2014/05/08 jiangyuan Ӧ�ô���һ��ִ�й���ָ�������һ��ָ�ʼ����,
	//������������������ʱ���(OrderLocalID��UserID����ͬ)������ط��ͻ��жϳ���
	iLastCmdPos++;
	// �Ҷ�Ӧ�ı��
	for(i=iLastCmdPos; i<= iCurCmdPos;i++)
	{
		if(strcmp(pInputOrder->UserOrderLocalID,sInputCmdArray[i].ReqField.UserOrderLocalID) == 0\
			&&\
		   strcmp(pInputOrder->UserID,sInputCmdArray[i].ReqField.UserID) == 0\
		   )

		{
			break;
		}
	}

	iLastCmdPos = i;	

	// �쳣�����л����·�����ͬ���ر�ŵı�������ʱ���д���12������ı��ر��
	// �Դ˵Ĵ�����Ҫ����
	if(m_bResend)
	{
		if(ERROR_DUPLICATE_ORDER==pRspInfo->ErrorID)
			pRspInfo->ErrorID=0;
	}
	memcpy(&sInputCmdArray[iLastCmdPos].pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));

	strcpy(sInputCmdArray[i].ReqField.OrderSysID,pInputOrder->OrderSysID);
	char szbuf[1024];
	sprintf(szbuf,"OrderSysID:%s,rsporder delay[%ld]us",pInputOrder->OrderSysID,lRspTime-lReqTime);
	strcat(sInputCmd->sNote,szbuf);

	if (m_nRequestID-1 == nRequestID)
	{

		if(bFastFlag == false)
			ShowMsg(" ==> ");

		if (NULL != pRspInfo) 
		{
			m_iRspValue = pRspInfo->ErrorID;
		}

		strcpy(m_sLastOrderSysID,pInputOrder->OrderSysID);

		if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
		{		
			if(bFastFlag == false)
				ShowMsg("ʧ��: %s,������ %d \n",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}

		
		if(bFastFlag == false)
			ShowMsg("�ɹ�:  ϵͳ��:%s \n",pInputOrder->OrderSysID);
	
		m_iRspValue = 0;
		if (m_bWaitResult)
		{
			EndAction();
		}
	}
	else// ��ͬ����Ӧ��
	{
		// ��Ҫ����ϯλ�����ر����Ų�ѯ����Ӧ��InputCmd �� ���
		char szbuf[1024];

		sprintf(szbuf,"\n%s,ί��Ӧ��,%s,%s,%s,%s,%s,%s ==> ",
				  sInputCmdArray[i].sCmdNo,
				  pInputOrder->BrokerID,
				  pInputOrder->UserID,
				  pInputOrder->InvestorID,
				  pInputOrder->InstrumentID,
				  pInputOrder->UserOrderLocalID,
				  pInputOrder->OrderSysID);

		if (NULL != pRspInfo) 
		{
			m_iRspValue = pRspInfo->ErrorID;
		}
		
		strcpy(m_sLastOrderSysID,pInputOrder->OrderSysID); // ò��û����

		if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
		{		
//			ShowMsg("%s ʧ��: %s,������ %d",szbuf,pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}

//		ShowMsg("%s �ɹ�:  ϵͳ��:%s",szbuf,pInputOrder->OrderSysID);
	
		m_iRspValue = 0;
		if (m_bWaitResult)
		{
			EndAction();
		}
	}
}

///��������Ӧ��
void CProcessor::OnRspOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (m_nRequestID-1 == nRequestID)
	{
		GET_ACCURATE_USEC_TIME(lRspTime);
#ifdef WIN32
		printf("RecvRsp UserOrderLocalID[%s]-[%I64d],",pOrderAction->OrderSysID,lRspTime);
#else
		printf("RecvRsp UserOrderLocalID[%s]-[%lld],",pOrderAction->OrderSysID,lRspTime);
#endif
		char szbuf[1024];
		sprintf(szbuf,"OrderSysID:%s,rsporderaction delay[%ld]us",pOrderAction->OrderSysID,lRspTime-lReqTime);
		strcat(sInputCmd->sNote,szbuf);

		///20140506 xuzh ����CANCELALL ��ָ���Ϊ���ǶԵ�,����Ҫ��¼ pRspInfo
		if(sInputCmd->sCmdTypeNum==3)
			memcpy(&sInputCmd->pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));
	
		ShowMsg(" ==> ");

		if (NULL != pRspInfo) 
		{
			m_iRspValue = pRspInfo->ErrorID;
		}
		
		if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
		{		
			ShowMsg("ʧ��: %s,������ %d \n",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}

		ShowMsg("�ɹ�: ϵͳ�� %s \n",pOrderAction->OrderSysID);
		if (m_bWaitResult)
		{
			EndAction();
		}
	}
};

///Ͷ�����ʽ��ʻ������Ӧ��
void CProcessor::OnRspAccountDeposit(CQdpFtdcRspAccountDepositField *pRspAccountDeposit, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (m_nRequestID-1 == nRequestID)
	{
		///20140506 xuzh ����CANCELALL ��ָ���Ϊ���ǶԵ�,����Ҫ��¼ pRspInfo
		memcpy(&sInputCmd->pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));
		
		ShowMsg(" ==> ");
		
		char szbuf[1024];
		sprintf(szbuf,"BrokerID:%s,UserID:%s,InvestorID:%s,AccountID:%s,AccountSeqNo:%s,\
				AmountDirection:%c,Amount:%.3f,Available:%.3f,Balance:%.3f",
			pRspAccountDeposit->BrokerID,\
			pRspAccountDeposit->UserID,\
			pRspAccountDeposit->InvestorID,\
			pRspAccountDeposit->AccountID,\
			pRspAccountDeposit->AccountSeqNo,\
			pRspAccountDeposit->AmountDirection,\
			pRspAccountDeposit->Amount,\
			pRspAccountDeposit->Available,\
			pRspAccountDeposit->Balance);		
		strcpy(sInputCmd->sNote,szbuf);

		if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
		{		
			ShowMsg("ʧ��: %s,������ %d \n",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}
		
		ShowMsg("�ɹ�: �ʽ���ˮ�ź� %s \n",pRspAccountDeposit->AccountSeqNo);
		if (m_bWaitResult)
		{
			EndAction();
		}
	}
}

///�˻������ر�
void CProcessor::OnRtnInvestorAccountDeposit(CQdpFtdcInvestorAccountDepositResField *pInvestorAccountDepositRes)
{
	if (NULL != pInvestorAccountDepositRes)
	{
		char szbuf[100];
		sprintf(szbuf,"BrokerID[%s],InvestorID[%s],AmountDirection[%c],Amount[%.3f],Available[%.3f],Balance[%.3f]\n",
			pInvestorAccountDepositRes->BrokerID, 
			pInvestorAccountDepositRes->InvestorID,
			pInvestorAccountDepositRes->AmountDirection,
			pInvestorAccountDepositRes->Amount,
			pInvestorAccountDepositRes->Available,
			pInvestorAccountDepositRes->Balance);
		ShowMsg("%s", szbuf);
		fwrite(szbuf,strlen(szbuf),1,m_fp_out);
	}
}

///�ɽ��ر�
void CProcessor::OnRtnTrade(CQdpFtdcTradeField *pTrade)
{
	int i = 0;
	// �Ҷ�Ӧ�ı��
	for(i=0; i<= iCurCmdPos;i++)
	{
		if(strcmp(pTrade->OrderSysID,sInputCmdArray[i].ReqField.OrderSysID) == 0\
			&&\
			strcmp(pTrade->BrokerID,sInputCmdArray[i].ReqField.BrokerID) == 0\
			)			
		{
			
			break;
		}
	}	
	if (i <= iCurCmdPos)
	{
		// ����ϵͳ�����ţ���������
		strcpy(sInputCmdArray[i].TradeID,pTrade->TradeID);
	}
}
///�����ر�
void CProcessor::OnRtnOrder(CQdpFtdcOrderField *pOrder)
{

}

void CProcessor::OnRtnMessageNotify(CQdpFtdcMessageNotifyInfoField *pMessageNotifyInfo)
{
	if (NULL != pMessageNotifyInfo)
	{
		char		szbuf[100];
		sprintf(szbuf,"BrokerID[%s],InvestorID[%s],UserID[%s],ExchangeID[%s] =>,��������[%d]\n",
			pMessageNotifyInfo->BrokerID, 
			pMessageNotifyInfo->InvestorID,
			pMessageNotifyInfo->UserID,
			pMessageNotifyInfo->ExchangeID,
			pMessageNotifyInfo->Nums);
		ShowMsg("%s", szbuf);
		fwrite(szbuf,strlen(szbuf),1,m_fp_out);
	}
}

void CProcessor::Output(const char *msg,...)
{
	if (NULL != m_fOutFile) 
	{
		va_list msgargs;
		va_start (msgargs,msg);
		vfprintf(m_fOutFile, msg, msgargs);
		va_end (msgargs);
		fputc('\n', m_fOutFile);
		fflush(m_fOutFile);
	}
	else
	{
		va_list msgargs;
		va_start (msgargs,msg);
		vfprintf(stdout, msg, msgargs);
		va_end (msgargs);
		fputc('\n', stdout);
		fflush(stdout);
	}
}


///ѯ��¼��Ӧ��
// void CProcessor::OnRspForQuoteInsert(CQdpFtdcInputForQuoteField *pInputForQuote, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
// {
// 	if (m_nRequestID-1 != nRequestID)
// 		return;
// 	
// 	if (NULL != pRspInfo) 
// 	{
// 		m_iRspValue = pRspInfo->ErrorID;
// 	}
// 	
// 	memcpy(&sInputCmd->pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));
// 	
// 	if (m_bFirstPackage)	
// 	{
// 		m_bFirstPackage =  false;
// 		ShowMsg(" ==> ");
// 	}
// 	if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
// 	{		
// 		ShowMsg("ʧ��, %s",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
// 		if (m_bWaitResult)
// 		{
// 			EndAction();
// 		}
// 		return;
// 	}
// 	
// 	if (NULL == pInputForQuote)
// 	{
// 		ShowMsg("ʧ��, ���޼�¼");
// 		if (m_bWaitResult)
// 		{
// 			EndAction();
// 		}
// 		return;
// 	}
// 	
// 	if (m_bFirstPackage)
// 	{		
// 		m_bFirstPackage = false;
// 		m_iTotalRecordCnt = 1;
// 	}	
// 	else
// 	{
// 		m_iTotalRecordCnt++;
// 	}
// 	
// 	char szbuf[1024];
// 	sprintf(szbuf," || BrokerID:%s,InvestorID:%s,UserID:%s,UserOrderLocalID:%s,UserCustom:%s,ExchangeID:%s,InstrumentID:%s,\
// 				OrderLocalID:%s",
// 				pInputForQuote->BrokerID,
// 				pInputForQuote->InvestorID,
// 				pInputForQuote->UserID,
// 				pInputForQuote->UserOrderLocalID,
// 				pInputForQuote->UserCustom,
// 				pInputForQuote->ExchangeID,
// 				pInputForQuote->InstrumentID,
// 				pInputForQuote->OrderLocalID);
// 	strcat(sInputCmd->sNote,szbuf);	
// 	ShowMsg(szbuf);
// 	
// 	if (bIsLast) 
// 	{
// 		if (m_bWaitResult)
// 		{
// 			EndAction();
// 		}
// 	}
// }
// 
// 
// ///ѯ�۲�ѯӦ��
// void CProcessor::OnRspQryForQuote(CQdpFtdcForQuoteField *pForQuote, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
// {
// 	if (m_nRequestID-1 != nRequestID)
// 		return;
// 	
// 	if (NULL != pRspInfo) 
// 	{
// 		m_iRspValue = pRspInfo->ErrorID;
// 	}
// 	
// 	memcpy(&sInputCmd->pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));
// 	
// 	if (m_bFirstPackage)	
// 	{
// 		m_bFirstPackage =  false;
// 		ShowMsg(" ==> ");
// 	}
// 	if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
// 	{		
// 		ShowMsg("ʧ��, %s",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
// 		if (m_bWaitResult)
// 		{
// 			EndAction();
// 		}
// 		return;
// 	}
// 	
// 	if (NULL == pForQuote)
// 	{
// 		ShowMsg("ʧ��, ���޼�¼");
// 		if (m_bWaitResult)
// 		{
// 			EndAction();
// 		}
// 		return;
// 	}
// 	
// 	if (m_bFirstPackage)
// 	{		
// 		m_bFirstPackage = false;
// 		m_iTotalRecordCnt = 1;
// 	}	
// 	else
// 	{
// 		m_iTotalRecordCnt++;
// 	}
// 	
// 	char szbuf[1024];
// 	sprintf(szbuf," || BrokerID:%s,InvestorID:%s,UserID:%s,UserOrderLocalID:%s,UserCustom:%s,ExchangeID:%s,InstrumentID:%s,\
// 				OrderLocalID:%s,ForQuoteStatus:%c,TradingDay:%s,InsertTime:%s",
// 				pForQuote->BrokerID,
// 				pForQuote->InvestorID,
// 				pForQuote->UserID,
// 				pForQuote->UserOrderLocalID,
// 				pForQuote->UserCustom,
// 				pForQuote->ExchangeID,
// 				pForQuote->InstrumentID,
// 				pForQuote->OrderLocalID,
// 				pForQuote->ForQuoteStatus,
// 				pForQuote->TradingDay,
// 				pForQuote->InsertTime);
// 	strcat(sInputCmd->sNote,szbuf);	
// 	ShowMsg(szbuf);
// 	
// 	if (bIsLast) 
// 	{
// 		if (m_bWaitResult)
// 		{
// 			EndAction();
// 		}
// 	}
// }
// 
// 
// ///��Ȩ¼��Ӧ��
// void CProcessor::OnRspExecOrderInsert(CQdpFtdcInputExecOrderField *pInputExecOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
// {
// //	printf("||| %d --- %d \n",m_nRequestID,nRequestID);
// 	int i;
// 
// 	m_nRecvCount ++;
// 	
// 	iWaitOrderPos++;
// 	
// 	//2014/05/08 jiangyuan Ӧ�ô���һ��ִ�й���ָ�������һ��ָ�ʼ����,
// 	//������������������ʱ���(OrderLocalID��UserID����ͬ)������ط��ͻ��жϳ���
// 	iLastCmdPos++;
// 	// �Ҷ�Ӧ�ı��
// 	for(i=iLastCmdPos; i<= iCurCmdPos;i++)
// 	{
// 		if(strcmp(pInputExecOrder->UserOrderLocalID,sInputCmdArray[i].ReqField.UserOrderLocalID) == 0\
// 			&&\
// 		   strcmp(pInputExecOrder->UserID,sInputCmdArray[i].ReqField.UserID) == 0\
// 		   )
// 
// 		{
// 			break;
// 		}
// 	}
// 
// 	iLastCmdPos = i;	
// 
// 	// �쳣�����л����·�����ͬ���ر�ŵı�������ʱ���д���12������ı��ر��
// 	// �Դ˵Ĵ�����Ҫ����
// 	if(m_bResend)
// 	{
// 		if(ERROR_DUPLICATE_ORDER==pRspInfo->ErrorID||ERROR_DUPLICATE_QUOTE==pRspInfo->ErrorID)
// 			pRspInfo->ErrorID=0;
// 	}
// 	memcpy(&sInputCmdArray[iLastCmdPos].pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));
// 
// 	// ����ϵͳ�����ţ���������
// 	strcpy(sInputCmdArray[i].ReqField.OrderSysID,pInputExecOrder->OrderSysID);
// 	char szbuf[1024];
// 	sprintf(szbuf,"OrderSysID:%s",pInputExecOrder->OrderSysID);
// 	strcat(sInputCmd->sNote,szbuf);
// 
// 	if (m_nRequestID-1 == nRequestID)
// 	{
// 
// 		if(bFastFlag == false)
// 			ShowMsg(" ==> ");
// 
// 		if (NULL != pRspInfo) 
// 		{
// 			m_iRspValue = pRspInfo->ErrorID;
// 		}
// 
// 		strcpy(m_sLastOrderSysID,pInputExecOrder->OrderSysID);
// 
// 		if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
// 		{		
// 			if(bFastFlag == false)
// 				ShowMsg("ʧ��:%s,������:%d \n",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
// 			if (m_bWaitResult)
// 			{
// 				EndAction();
// 			}
// 			return;
// 		}
// 
// 		if(bFastFlag == false)
// 			ShowMsg("�ɹ�:ϵͳ��:%s \n",pInputExecOrder->OrderSysID);
// 	
// 		m_iRspValue = 0;
// 		if (m_bWaitResult)
// 		{
// 			EndAction();
// 		}
// 	}
// 	else// ��ͬ����Ӧ��
// 	{
// 		// ��Ҫ����ϯλ�����ر����Ų�ѯ����Ӧ��InputCmd �� ���
// 		char szbuf[1024];
// 
// 		sprintf(szbuf,"\n%s,��Ȩ¼��Ӧ��,%s,%s,%s,%s,%s,%s ==> ",
// 				  sInputCmdArray[i].sCmdNo,
// 				  pInputExecOrder->BrokerID,
// 				  pInputExecOrder->UserID,
// 				  pInputExecOrder->InvestorID,
// 				  pInputExecOrder->InstrumentID,
// 				  pInputExecOrder->UserOrderLocalID,
// 				  pInputExecOrder->OrderSysID);
// 
// 		if (NULL != pRspInfo) 
// 		{
// 			m_iRspValue = pRspInfo->ErrorID;
// 		}
// 		
// 		strcpy(m_sLastOrderSysID,pInputExecOrder->OrderSysID); // ò��û����
// 
// 		if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
// 		{		
// //			ShowMsg("%s ʧ��: %s,������ %d",szbuf,pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
// 			if (m_bWaitResult)
// 			{
// 				EndAction();
// 			}
// 			return;
// 		}
// 
// //		ShowMsg("%s �ɹ�:  ϵͳ��:%s",szbuf,pInputExecOrder->OrderSysID);
// 	
// 		m_iRspValue = 0;
// 		if (m_bWaitResult)
// 		{
// 			EndAction();
// 		}
// 	}
// }
// 
// ///��������Ӧ��
// void CProcessor::OnRspExecOrderAction(CQdpFtdcExecOrderActionField *pExecOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
// {
// 	if (m_nRequestID-1 == nRequestID)
// 	{
// 		///20140506 xuzh ����CANCELALL ��ָ���Ϊ���ǶԵ�,����Ҫ��¼ pRspInfo
// 		if(sInputCmd->sCmdTypeNum==17)
// 			memcpy(&sInputCmd->pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));
// 	
// 		ShowMsg(" ==> ");
// 
// 		if (NULL != pRspInfo) 
// 		{
// 			m_iRspValue = pRspInfo->ErrorID;
// 		}
// 		
// 		if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
// 		{		
// 			ShowMsg("ʧ��: %s,������ %d \n",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
// 			if (m_bWaitResult)
// 			{
// 				EndAction();
// 			}
// 			return;
// 		}
// 
// 		ShowMsg("�ɹ�: ϵͳ�� %s \n",pExecOrderAction->OrderSysID);
// 		if (m_bWaitResult)
// 		{
// 			EndAction();
// 		}
// 	}
// }
// 
// ///��Ȩ֪ͨ
// void CProcessor::OnRtnExecOrder(CQdpFtdcExecOrderField *pExecOrder)
// {
// 	
// }
// 
// //��Ȩ������ѯӦ��
// void CProcessor::OnRspQryExecOrder(CQdpFtdcExecOrderField *pExecOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
// {	
// 	if (m_nRequestID-1 == nRequestID)
// 	{
// 		if (NULL != pRspInfo) 
// 		{
// 			m_iRspValue = pRspInfo->ErrorID;
// 		}
// 		if (0 == strcmp(sInputCmd->sCmdType,"QRYEXECORDER"))
// 		{
// 			memcpy(&sInputCmd->pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));
// 			if(bFastFlag == false)
// 				ShowMsg(" ==> ");
// 		}		
// 		if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
// 		{							
// 			if(bFastFlag == false)
// 				ShowMsg("������ѯʧ�ܣ�ԭ��:%s\n",pRspInfo->ErrorMsg);
// 			
// 			if (m_bWaitResult)
// 			{
// 				EndAction();
// 			}
// 			return;
// 		}
// 		if (NULL == pExecOrder)
// 		{			
// 			if(bFastFlag == false)
// 				ShowMsg("���޼�¼\n");
// 			
// 			if (m_bWaitResult)
// 			{
// 				EndAction();
// 			}
// 			return;
// 		}
// 		if (m_bFirstPackage)
// 		{		
// 			m_bFirstPackage = false;
// 			m_iTotalRecordCnt = 0;	
// 		}	
// 		
// 		//	�������пɳ�����OrderSysid	// ���ֳɽ����ڶ�����// δ�ɽ����ڶ�����
// 		if(pExecOrder->OrderStatus == QDP_FTDC_OS_PartTradedQueueing || pExecOrder->OrderStatus == QDP_FTDC_OS_NoTradeQueueing)
// 		{
// 			m_iTotalRecordCnt++;
// 		}
// 		
// 		char szbuf[1024];
// 		//20120703 jiangyuan �������	
// 		sprintf(szbuf,"OrderSysID:%s,InstrumentID:%s,OrderStatus:%c,Volume:%d,\
// 						VolumeTraded:%d,OrderSource:%c,\
// 						PosiDirection:%c,HedgeFlag:%c,OffsetFlag:%c,ActionType:%c",\
// 						pExecOrder->OrderSysID,pExecOrder->InstrumentID,pExecOrder->OrderStatus,\
// 						pExecOrder->Volume,pExecOrder->VolumeTraded,\
// 						pExecOrder->OrderSource,\
// 						pExecOrder->PosiDirection,pExecOrder->HedgeFlag,\
// 						pExecOrder->OffsetFlag,pExecOrder->ActionType);
// 		strcat(sInputCmd->sNote,szbuf);	
// 		ShowMsg(szbuf);
// 		//20120703 end	
// 		if(bFastFlag == false)
// 			ShowMsg(" => ��ѯ�ɹ�\n");	
// 		
// 		if (bIsLast) 
// 		{
// 			if (m_bWaitResult)
// 			{
// 				EndAction();
// 			}
// 		}
// 	}
// }
