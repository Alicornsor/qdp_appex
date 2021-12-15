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
extern int iLastCmdPos;		// 最后一笔委托应答的InputCmd 的 序号
extern int iCurCmdPos;		// 当前提交的InputCmd 的 序号


extern char  m_TradeIp[30];
extern char  m_DefaultUser[30];
extern char  m_DefaultPass[30];

extern int iWaitOrderPos;  // 在途委托总数 
extern int iTotalOrderCnt;  // 总委托总数
extern UF_INT8    lReqTime;    //请求开始时间 
extern UF_INT8    lRspTime;	   //请求结束时间

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

	//20140425 增加订阅模式的设定
	//tload由于会频繁登入登出系统，如果订阅方式设置不对，会有问题
	//如果设置为restart，不能频繁登录，会造成front 的slog 过大
	//如果设置为quick，需要考虑是否需要下行流的准确性的问题

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
// 			printf("配置 ResumeType 值不对! 采用quick模式 \n");
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
	//等待前置的onFrontConnect解锁
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
	//20140516 xuzh 增加一个等待时间，单位为毫秒，用于控制速度
	SLEEP(m_nSleepControl);
	//20140508 xuzh 线程调用会有冲突问题，不考虑超时等待
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

///初始化
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
///用户登录请求
int CProcessor::ReqUserLogin(char *pBrokerID,char *pUser,char *pPassword)
{
	if (!m_bConnected)
	{
		ShowMsg("\n UserLogin Error : 未连接 \n");
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
	
	strcpy(ReqField.UserProductInfo,"TLOAD QDP 控制台客户端v1.0");
	GET_ACCURATE_USEC_TIME(lReqTime);
	int res = m_pFfexFtdcUserApi->ReqUserLogin(&ReqField,m_nRequestID++);
	return res;
}

///////////////////////////////////////////////////////////////////////////////////
///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
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
	
	ShowMsg("\n warning : disconnect 连接中断,错误代码 %d \n",nReason);
	m_bTradeIsLogin = false;
	m_bConnected = false;
	m_bReLogin = true;
//	exit(9);
}

void CProcessor::OnRtnInstrumentStatus(CQdpFtdcInstrumentStatusField *pInstrumentStatus)
{
	ShowMsg("合约状态通知,%s==>[%c]\n",pInstrumentStatus->InstrumentID,pInstrumentStatus->InstrumentStatus);
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
			Output("%s,修改密码切换失败，原因:%s",sInputCmd->sCmdNo,pRspInfo->ErrorMsg);	
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}
		Output("%s,修改密码成功: %s@%s : %s -> %s",sInputCmd->sCmdNo,pUserPasswordUpdate->UserID,pUserPasswordUpdate->BrokerID,pUserPasswordUpdate->OldPassword,pUserPasswordUpdate->NewPassword); 
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
		ShowMsg("交易日 %s 时间 %s 最大报单号[%s] rsplogin delay[%ld]us",	pRspUserLogin->TradingDay,pRspUserLogin->LoginTime,
			pRspUserLogin->MaxOrderLocalID,delay);
		strcat(sInputCmd->sNote,buf);
		memcpy(&sInputCmd->pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));

		ShowMsg(" ==> ");

		if (0 != pRspInfo->ErrorID) 
		{			
			EndAction();
			m_bTradeIsLogin = false;
			ShowMsg("失败,%s",pRspInfo->ErrorMsg);
			if(m_bReLogin)
			{
				ReqUserLogin(NULL,NULL,NULL);
			}
			return;
		}	



		m_bTradeIsLogin = true;
		///会员代码
		memset(m_sBrokerID,0,sizeof(m_sBrokerID));
		strcpy(m_sBrokerID,pRspUserLogin->BrokerID);
		//上次最大本地报单号
		//如果是断线重连，不取本地保单号
		if(!m_bReLogin)
		{
			m_iLocalNo = atoi(pRspUserLogin->MaxOrderLocalID) + 1;
			EndAction();
		}
		m_bReLogin = false;
	}
}

///资金应答
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
			Output("资金查询失败，原因:%s",pRspInfo->ErrorMsg);		
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}
		if (NULL == pRspInvestorAccount)
		{
			Output("查无记录");	
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

//报单查询应答
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
				ShowMsg("报单查询失败，原因:%s\n",pRspInfo->ErrorMsg);
	
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}
		if (NULL == pOrder)
		{			
			if(bFastFlag == false)
				ShowMsg("查无记录\n");

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

		//	保存所有可撤销的OrderSysid	// 部分成交还在队列中// 未成交还在队列中
		if(pOrder->OrderStatus == QDP_FTDC_OS_PartTradedQueueing || pOrder->OrderStatus == QDP_FTDC_OS_NoTradeQueueing)
		{
			m_iTotalRecordCnt++;
		}

		char szbuf[1024];
		//20120703 jiangyuan 增加输出	
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
			ShowMsg(" => 查询成功\n");	

		if (bIsLast) 
		{
			if (m_bWaitResult)
			{
				EndAction();
			}
		}
	}
}

///成交单查询应答
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
				ShowMsg("成交查询失败，原因:%s\n",pRspInfo->ErrorMsg);
			
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}
		if (NULL == pTrade)
		{
			//Output("查无记录");
			if(bFastFlag == false)
					ShowMsg("查无记录\n");
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
				"成交编号","报单编号","会员号","客户号","席位号",\
				"合约号","买卖方向","开平标志","价格","数量",\
				"成交时间");*/		
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
			//20120703 jiangyuan 增加输出	
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
					ShowMsg("查询成功\n");
		}

		if (bIsLast) 
		{
//			Output("总共 %d 个成交单",m_iTotalRecordCnt);
			if (m_bWaitResult)
			{
				EndAction();
			}
		}
	}
}


///错误应答
void CProcessor::OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CProcessor::OnRspUserLogout(CQdpFtdcRspUserLogoutField *pRspUserLogout, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
}

///合约查询应答
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
		ShowMsg("失败, %s",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
		if (m_bWaitResult)
		{
			EndAction();
		}
		return;
	}

	if (NULL == pRspInstrument)
	{
		ShowMsg("失败, 查无记录");
		if (m_bWaitResult)
		{
			EndAction();
		}
		return;
	}


	//将合约信息记入全局宏
	iMarcoCount ++;
	sMarcoArray[iMarcoCount].iType = 0;    //	字符
	sprintf(sMarcoArray[iMarcoCount].sMarcoId,"#%s_%d#",
			"INSTRUMENT",m_iTotalRecordCnt);
	strcpy(sMarcoArray[iMarcoCount].sMarcoValue,pRspInstrument->InstrumentID);
	
	//全局宏记录结束
	//打印合约属性
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

///客户持仓查询应答
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
		ShowMsg("失败, %s",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
		if (m_bWaitResult)
		{
			EndAction();
		}
		return;
	}

	if (NULL == pRspInvestorPosition)
	{
		ShowMsg("失败, 查无记录");
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

///会员客户查询应答
//void CProcessor::OnRspQryClient(CQdpFtdcRspClientField *pRspClient, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//}

///报单录入应答
void CProcessor::OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	// 保持系统报单号，做撤单用
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
	
	//2014/05/08 jiangyuan 应该从上一条执行过的指令的下面一条指令开始查找,
	//否则如果有连续的两笔报单(OrderLocalID、UserID都相同)，这个地方就会判断出错
	iLastCmdPos++;
	// 找对应的编号
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

	// 异常处理中会重新发送相同本地编号的报单，此时会有错误12：错误的本地编号
	// 对此的错误，需要忽略
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
				ShowMsg("失败: %s,错误码 %d \n",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}

		
		if(bFastFlag == false)
			ShowMsg("成功:  系统号:%s \n",pInputOrder->OrderSysID);
	
		m_iRspValue = 0;
		if (m_bWaitResult)
		{
			EndAction();
		}
	}
	else// 非同步的应答
	{
		// 需要根据席位及本地报单号查询到对应的InputCmd 的 序号
		char szbuf[1024];

		sprintf(szbuf,"\n%s,委托应答,%s,%s,%s,%s,%s,%s ==> ",
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
		
		strcpy(m_sLastOrderSysID,pInputOrder->OrderSysID); // 貌似没有用

		if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
		{		
//			ShowMsg("%s 失败: %s,错误码 %d",szbuf,pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}

//		ShowMsg("%s 成功:  系统号:%s",szbuf,pInputOrder->OrderSysID);
	
		m_iRspValue = 0;
		if (m_bWaitResult)
		{
			EndAction();
		}
	}
}

///报单操作应答
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

		///20140506 xuzh 对于CANCELALL 的指令，认为都是对的,不需要记录 pRspInfo
		if(sInputCmd->sCmdTypeNum==3)
			memcpy(&sInputCmd->pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));
	
		ShowMsg(" ==> ");

		if (NULL != pRspInfo) 
		{
			m_iRspValue = pRspInfo->ErrorID;
		}
		
		if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
		{		
			ShowMsg("失败: %s,错误码 %d \n",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}

		ShowMsg("成功: 系统号 %s \n",pOrderAction->OrderSysID);
		if (m_bWaitResult)
		{
			EndAction();
		}
	}
};

///投资者资金帐户出入金应答
void CProcessor::OnRspAccountDeposit(CQdpFtdcRspAccountDepositField *pRspAccountDeposit, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (m_nRequestID-1 == nRequestID)
	{
		///20140506 xuzh 对于CANCELALL 的指令，认为都是对的,不需要记录 pRspInfo
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
			ShowMsg("失败: %s,错误码 %d \n",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
			if (m_bWaitResult)
			{
				EndAction();
			}
			return;
		}
		
		ShowMsg("成功: 资金流水号号 %s \n",pRspAccountDeposit->AccountSeqNo);
		if (m_bWaitResult)
		{
			EndAction();
		}
	}
}

///账户出入金回报
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

///成交回报
void CProcessor::OnRtnTrade(CQdpFtdcTradeField *pTrade)
{
	int i = 0;
	// 找对应的编号
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
		// 保持系统报单号，做撤单用
		strcpy(sInputCmdArray[i].TradeID,pTrade->TradeID);
	}
}
///报单回报
void CProcessor::OnRtnOrder(CQdpFtdcOrderField *pOrder)
{

}

void CProcessor::OnRtnMessageNotify(CQdpFtdcMessageNotifyInfoField *pMessageNotifyInfo)
{
	if (NULL != pMessageNotifyInfo)
	{
		char		szbuf[100];
		sprintf(szbuf,"BrokerID[%s],InvestorID[%s],UserID[%s],ExchangeID[%s] =>,撤单数量[%d]\n",
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


///询价录入应答
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
// 		ShowMsg("失败, %s",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
// 		if (m_bWaitResult)
// 		{
// 			EndAction();
// 		}
// 		return;
// 	}
// 	
// 	if (NULL == pInputForQuote)
// 	{
// 		ShowMsg("失败, 查无记录");
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
// ///询价查询应答
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
// 		ShowMsg("失败, %s",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
// 		if (m_bWaitResult)
// 		{
// 			EndAction();
// 		}
// 		return;
// 	}
// 	
// 	if (NULL == pForQuote)
// 	{
// 		ShowMsg("失败, 查无记录");
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
// ///行权录入应答
// void CProcessor::OnRspExecOrderInsert(CQdpFtdcInputExecOrderField *pInputExecOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
// {
// //	printf("||| %d --- %d \n",m_nRequestID,nRequestID);
// 	int i;
// 
// 	m_nRecvCount ++;
// 	
// 	iWaitOrderPos++;
// 	
// 	//2014/05/08 jiangyuan 应该从上一条执行过的指令的下面一条指令开始查找,
// 	//否则如果有连续的两笔报单(OrderLocalID、UserID都相同)，这个地方就会判断出错
// 	iLastCmdPos++;
// 	// 找对应的编号
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
// 	// 异常处理中会重新发送相同本地编号的报单，此时会有错误12：错误的本地编号
// 	// 对此的错误，需要忽略
// 	if(m_bResend)
// 	{
// 		if(ERROR_DUPLICATE_ORDER==pRspInfo->ErrorID||ERROR_DUPLICATE_QUOTE==pRspInfo->ErrorID)
// 			pRspInfo->ErrorID=0;
// 	}
// 	memcpy(&sInputCmdArray[iLastCmdPos].pRspInfo,pRspInfo,sizeof(CQdpFtdcRspInfoField));
// 
// 	// 保持系统报单号，做撤单用
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
// 				ShowMsg("失败:%s,错误码:%d \n",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
// 			if (m_bWaitResult)
// 			{
// 				EndAction();
// 			}
// 			return;
// 		}
// 
// 		if(bFastFlag == false)
// 			ShowMsg("成功:系统号:%s \n",pInputExecOrder->OrderSysID);
// 	
// 		m_iRspValue = 0;
// 		if (m_bWaitResult)
// 		{
// 			EndAction();
// 		}
// 	}
// 	else// 非同步的应答
// 	{
// 		// 需要根据席位及本地报单号查询到对应的InputCmd 的 序号
// 		char szbuf[1024];
// 
// 		sprintf(szbuf,"\n%s,行权录入应答,%s,%s,%s,%s,%s,%s ==> ",
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
// 		strcpy(m_sLastOrderSysID,pInputExecOrder->OrderSysID); // 貌似没有用
// 
// 		if (NULL != pRspInfo && 0 != pRspInfo->ErrorID)
// 		{		
// //			ShowMsg("%s 失败: %s,错误码 %d",szbuf,pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
// 			if (m_bWaitResult)
// 			{
// 				EndAction();
// 			}
// 			return;
// 		}
// 
// //		ShowMsg("%s 成功:  系统号:%s",szbuf,pInputExecOrder->OrderSysID);
// 	
// 		m_iRspValue = 0;
// 		if (m_bWaitResult)
// 		{
// 			EndAction();
// 		}
// 	}
// }
// 
// ///报单操作应答
// void CProcessor::OnRspExecOrderAction(CQdpFtdcExecOrderActionField *pExecOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
// {
// 	if (m_nRequestID-1 == nRequestID)
// 	{
// 		///20140506 xuzh 对于CANCELALL 的指令，认为都是对的,不需要记录 pRspInfo
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
// 			ShowMsg("失败: %s,错误码 %d \n",pRspInfo->ErrorMsg,pRspInfo->ErrorID);	
// 			if (m_bWaitResult)
// 			{
// 				EndAction();
// 			}
// 			return;
// 		}
// 
// 		ShowMsg("成功: 系统号 %s \n",pExecOrderAction->OrderSysID);
// 		if (m_bWaitResult)
// 		{
// 			EndAction();
// 		}
// 	}
// }
// 
// ///行权通知
// void CProcessor::OnRtnExecOrder(CQdpFtdcExecOrderField *pExecOrder)
// {
// 	
// }
// 
// //行权报单查询应答
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
// 				ShowMsg("报单查询失败，原因:%s\n",pRspInfo->ErrorMsg);
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
// 				ShowMsg("查无记录\n");
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
// 		//	保存所有可撤销的OrderSysid	// 部分成交还在队列中// 未成交还在队列中
// 		if(pExecOrder->OrderStatus == QDP_FTDC_OS_PartTradedQueueing || pExecOrder->OrderStatus == QDP_FTDC_OS_NoTradeQueueing)
// 		{
// 			m_iTotalRecordCnt++;
// 		}
// 		
// 		char szbuf[1024];
// 		//20120703 jiangyuan 增加输出	
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
// 			ShowMsg(" => 查询成功\n");	
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
