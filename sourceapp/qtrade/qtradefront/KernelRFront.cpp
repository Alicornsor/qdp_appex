// KernelFront.cpp: implementation of the CKernelRFront class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "KernelRFront.h"
#include "XtpPackageDesc.h"
#include "CConfig.h"
#include "ExchangeLinkTimer.h"

#ifdef LINUX
//这个头文件是为了用函数 sync() 20141031 longqy
#include <unistd.h>
#endif
#include "FtdData.h"
#include "FtdPackageDesc.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//extern  char *INI_FILE_NAME;
const int QUERY_SERVER_ID = 1;
extern const char *APP_NAME;
extern CConfig	*g_pConfig; // 全局的配置文件对象指针，给CKernelRFrontReactor 对象用 longqy 2014-03-25。
extern CLinkReactor* g_pConnReactor;
extern CCachedFlow* g_pQueryFlow;

extern bool g_bLatencyOut;

#define FTD_REQ_QUERY(XtpTid, FtdFieldType, XtpFieldType, CopyField)			\
	{																			\
		m_reqPackage.PreparePublish(XtpTid);									\
		m_reqPackage.SetFrontID(m_dwFrontID);									\
		m_reqPackage.SetSessionID(pSession->GetSessionID());					\
		m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());				\
		FtdFieldType ftdField;													\
		FTDC_GET_SINGLE_FIELD(pFTDCPackage, &ftdField);							\
		XtpFieldType xtpField;													\
		memset(&xtpField, 0, sizeof(xtpField));									\
		CopyField																\
		XTP_ADD_FIELD(&m_reqPackage, &xtpField);								\
		m_reqPackage.GetXTPHeader()->Type = XTP_REQUEST;						\
		m_ClientApi->Request(m_nQueryServerID, &m_reqPackage);					\
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CFtdREngine

#define EVOKE_CPU_TIMER_ID  10

CFtdREngine::CFtdREngine(CReactor *pReactor,char *pQquery,CFlow* pReqFlow,CFlow* pReadSlogResult,DWORD nFrontID,int nLifeCycleID,int nEvokeCpuInterval,CSelectReactor* pConnReactor)
:CSessionFactory(pReactor, 500, pConnReactor)
{
	m_reqPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE, 1000);
	m_rspPackage.ConstructAllocate(FTDC_PACKAGE_MAX_SIZE, 1000);
	m_mapSessionInfo.Clear();
	m_dwFrontID = nFrontID;
	m_nLifeCycleID = nLifeCycleID;
	m_pReadSlogFlow = pReadSlogResult;
	m_pReqFlow = pReqFlow;
	m_nQueryServerID = QUERY_SERVER_ID;

	//查询
	if (strcmp(pQquery,""))
	{
		m_pQueryFlowHandler = new CQueryFlowHandler();
		m_ClientApi = CFibClientApi::CreateClientApi(m_pReactor, m_dwFrontID);
		m_ClientApi->RegisterServer(m_nQueryServerID, pQquery, m_pQueryFlowHandler);
		m_ClientApi->Start();
	}

	m_nEvokeCpuInterval = nEvokeCpuInterval;
	if (m_nEvokeCpuInterval > 0 && m_nEvokeCpuInterval <20)
	{
		m_nEvokeCpuInterval = 20;
	}
	if (m_nEvokeCpuInterval >0)
	{
		SetTimer(EVOKE_CPU_TIMER_ID,m_nEvokeCpuInterval);
	}

}

CFtdREngine::~CFtdREngine()
{
}

void CFtdREngine::OnTimer(int nIDEvent)
{
	if (nIDEvent == EVOKE_CPU_TIMER_ID)
	{
#ifndef WIN32
		struct timeval nCurrTime; //原始采样时间
#else
		struct _timeb  nCurrTime;
#endif

#ifndef  WIN32
		gettimeofday(&nCurrTime, NULL);
#else
		_ftime( &nCurrTime );
#endif

#ifndef  WIN32
		int inter=(nCurrTime.tv_sec-m_nBeginTime.tv_sec)*1000+(nCurrTime.tv_usec-m_nBeginTime.tv_usec)/1000;
#else
		int inter=(nCurrTime.time-m_nBeginTime.time)*1000+nCurrTime.millitm-m_nBeginTime.millitm;
#endif

		if (inter >= m_nEvokeCpuInterval)
		{
			CCurrentTimeField timeField;
			timeField.CurrDate = "20150508";//日期暂时填
			
			m_reqPackage.PreparePublish(TID_NtfTimeSync);
			XTP_ADD_FIELD(&m_reqPackage, &timeField);
			m_reqPackage.MakePackage();				
			m_pReqFlow->Append(m_reqPackage.Address(), m_reqPackage.Length());

			m_nBeginTime = nCurrTime;
		}
	}
}

CSession *CFtdREngine::CreateSession(CChannel *pChannel, DWORD)
{
	CFTDCRSession *pSession =  new CFTDCRSession(m_pReactor, pChannel);
	pSession->RegisterPackageHandler(this);
	
	return pSession;
}

void CFtdREngine::OnSessionConnected(CSession *pSession)
{
	//先调用基类的方法
	CSessionFactory::OnSessionConnected(pSession);
	
	TFtdSessionInfo sinfo;
	memset(&sinfo, 0, sizeof(TFtdSessionInfo));
	sinfo.nSessionID = pSession->GetSessionID();
	sinfo.bIsLogin = false;
	sinfo.nConnectTime = m_pReactor->Time();
	sinfo.nCommFlux = 0;
	m_mapSessionInfo.Insert(sinfo.nSessionID, sinfo);
	pSession->GetChannel()->SetLogFlow(m_pReadSlogFlow);
}

void CFtdREngine::OnSessionDisconnected(CSession *pSession, int nReason)
{
	CUserLogoutField userLogoutField;
	if (GetSessionOwner(pSession->GetSessionID(),
		userLogoutField.UserID, userLogoutField.BrokerID))
	{		
		//如果存在该会话的信息，则将其删除
		m_mapSessionInfo.Erase(pSession->GetSessionID());
		m_reqPackage.PreparePublish(TID_ReqUserLogout);
		m_reqPackage.SetSessionID(pSession->GetSessionID());
		m_reqPackage.SetFrontID(m_dwFrontID);
		userLogoutField.LogoutReason = nReason;
		userLogoutField.FrontID = m_dwFrontID;
		userLogoutField.SessionID = pSession->GetSessionID();
		XTP_ADD_FIELD(&m_reqPackage, &userLogoutField);
		m_reqPackage.MakePackage();
		m_pReqFlow->Append(m_reqPackage.Address(),m_reqPackage.Length());
	}
	
	//最后调用基类的方法
	CSessionFactory::OnSessionDisconnected(pSession, nReason);
	delete pSession;
}

TFtdSessionInfo *CFtdREngine::GetSessionInfo(DWORD nSessionID)
{
	return m_mapSessionInfo.Find(nSessionID);
}

bool CFtdREngine::GetSessionOwner(DWORD nSessionID, CUserIDType &userID, 
							  CBrokerIDType &brokerID)
{
	TFtdSessionInfo *pSessionInfo = m_mapSessionInfo.Find(nSessionID);
	if (pSessionInfo == NULL)
	{
		return false;
	}
	userID = pSessionInfo->UserID;
	brokerID = pSessionInfo->BrokerID;
	return true;
}

void CFtdREngine::SetSessionOwner(DWORD nSessionID, const CUserIDType &userID, 
							  const CBrokerIDType &brokerID)
{
	TFtdSessionInfo *pFind = m_mapSessionInfo.Find(nSessionID);
	if (pFind == NULL)
	{
		//不应出现，这个信息在连接建立后就应该存在了
		return;
	}
	pFind->bIsLogin = true;
	pFind->UserID =userID;
	pFind->BrokerID = brokerID;

	CSession *pSession = GetSession(nSessionID);
	assert(pSession != NULL);
}

void CFtdREngine::SendError(CFTDCRSession *pSession, 
							  const int nErrorCode, const char *pszErrorMsg)
{	
	CRspInfoField ftdRspInfoField;
	ftdRspInfoField.ErrorID = nErrorCode;
	ftdRspInfoField.ErrorMsg = pszErrorMsg;
	m_reqPackage.PreparePublish(TID_RspError, FTDC_CHAIN_LAST);
	m_reqPackage.SetFrontID(m_dwFrontID);
	m_reqPackage.SetSessionID(pSession->GetSessionID());
	XTP_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);
	m_reqPackage.MakePackage();
	m_pReqFlow->Append(m_rspPackage.Address(),m_rspPackage.Length());	
}

void CFtdREngine::SendErrorRsp(CFTDCPackage *pRequest, CFTDCRSession *pSession, 
							   const int nErrorCode, const char *pszErrorMsg)
{
	CFTDRspInfoField ftdRspInfoField;
	ftdRspInfoField.ErrorID = nErrorCode;
	ftdRspInfoField.ErrorMsg = pszErrorMsg;
	m_rspPackage.PrepareResponse(pRequest, FTD_TID_RspError, FTDC_CHAIN_LAST, FTD_VERSION);
	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);
	TFTDCHeader  *pHeader = pRequest->GetFTDCHeader();
	pHeader->SequenceSeries = TSS_DIALOG;
	pSession->SendRequestPackage(pRequest);	
}

int CFtdREngine::OnReqUserLogin(CFTDCPackage *pPackage, CFTDCRSession *pSession)
{	
	CFTDReqUserLoginField ftdReqUserLoginField;
	memset(&ftdReqUserLoginField, 0, sizeof(ftdReqUserLoginField));
	if(FTDC_GET_SINGLE_FIELD(pPackage, &ftdReqUserLoginField) <= 0)
	{
		//没有取到登录请求域，断开连接
		pSession->Disconnect(MSG_FTDCERR_BADPACKAGE);
		return -1;
	}
		
	CUserLoginField userLoginField;
	userLoginField.PrivateSeqno = NO_SUBSCRIBE;
	userLoginField.PublicSeqno = NO_SUBSCRIBE;
	CFTDDisseminationField ftdDisseminationField;
	CNamedFieldIterator dfIterator = pPackage->GetNamedFieldIterator(
		&CFTDDisseminationField::m_Describe);
	for(int i=0; i<FTDE_MAX_SEQUENCE_SERIES && !dfIterator.IsEnd(); i++)
	{
		dfIterator.Retrieve(&ftdDisseminationField);
		if (ftdDisseminationField.SequenceSeries == TSS_DIALOG)
		{
			userLoginField.DialogSeqno = ftdDisseminationField.SequenceNo;
		}
		else if (ftdDisseminationField.SequenceSeries == TSS_PRIVATE ||
				 ftdDisseminationField.SequenceSeries == TSS_USER)
		{
			userLoginField.PrivateSeqno = ftdDisseminationField.SequenceNo;
		}
		else if (ftdDisseminationField.SequenceSeries == TSS_PUBLIC)
		{
			userLoginField.PublicSeqno = ftdDisseminationField.SequenceNo;
		}
		dfIterator.Next();
	}
	
	m_reqPackage.PreparePublish(TID_ReqUserLogin);
	m_reqPackage.SetFrontID(m_dwFrontID);
	m_reqPackage.SetSessionID(pSession->GetSessionID());
	m_reqPackage.SetRequestID(pPackage->GetRequestId());
	
	
	userLoginField.IPAddress = pSession->GetChannel()->GetRemoteName();
	userLoginField.MaxOrderLocalID = 0;
	userLoginField.LoginTime = "";
	userLoginField.TradingSystemName = "";
	
	CopyLoginBaseEntity(&userLoginField,&ftdReqUserLoginField);
	char buffer[sizeof(CProtocolInfoType)];
	sprintf(buffer,"FTD %d",pPackage->GetVersion());
	userLoginField.ProtocolInfo=buffer;
	userLoginField.SockID = pSession->GetChannel()->GetId();
	userLoginField.ClientTradingDay = ftdReqUserLoginField.TradingDay;
	userLoginField.Heartbeat = pSession->GetTimeout();
	userLoginField.FrontID = m_dwFrontID;
	userLoginField.SessionID = pSession->GetSessionID();
	userLoginField.LifeCycleID = m_nLifeCycleID;
	
	XTP_ADD_FIELD(&m_reqPackage, &userLoginField);
	m_reqPackage.MakePackage();
	m_pReqFlow->Append(m_reqPackage.Address(),m_reqPackage.Length());

	SetSessionOwner(pSession->GetSessionID(), userLoginField.UserID, userLoginField.BrokerID);
	return 0;
}

// void CFtdREngine::OnUserLoginRsp(CXTPPackage *pMessage, CFTDCRSession *pSession)
// {
// 	if (pSession == NULL)
// 	{
// 		return;
// 	}
// 	m_rspPackage.PreparePackage(FTD_TID_RspUserLogin, FTDC_CHAIN_LAST, FTD_VERSION);
// 	m_rspPackage.SetRequestId(pMessage->GetRequestID());
// 
// 	CRspInfoField rspInfoField;
// 	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
// 	{
// 		//没有取到响应信息
// 		return ;
// 	}
// 
// 	//登录成功,将信息转发到发送线程
// 	if (rspInfoField.ErrorID ==0)
// 	{
// 		return;
// 	}
// 	CFTDRspInfoField ftdRspInfoField;
// 	CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);
// 
// 	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);
// 	
// 	CUserLoginField userLoginField;
// 	if(XTP_GET_SINGLE_FIELD(pMessage, &userLoginField) <= 0)
// 	{
// 		//没有取到登录域
// 		return ;
// 	}
// 	//组织FTDC报文的登录应答域
// 	
// 	CFTDRspUserLoginField ftdRspUserLoginField;
// 	memset(&ftdRspUserLoginField, 0, sizeof(CFTDRspUserLoginField));
// 	ftdRspUserLoginField.MaxOrderLocalID = userLoginField.MaxOrderLocalID;
// 	ftdRspUserLoginField.TradingDay = userLoginField.TradingDay;
// 	ftdRspUserLoginField.LoginTime = userLoginField.LoginTime;
// 	ftdRspUserLoginField.UserID = userLoginField.UserID;
// 	ftdRspUserLoginField.TradingSystemName = userLoginField.TradingSystemName;
// 	ftdRspUserLoginField.BrokerID=userLoginField.BrokerID;
// 	ftdRspUserLoginField.SessionID=userLoginField.SessionID;
// 	ftdRspUserLoginField.FrontID=userLoginField.FrontID;
// 
// 	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspUserLoginField);
// 	
// 	//走对话流会导致登录应答后到，这里直接发送
// 	pSession->SendRequestPackage(&m_rspPackage);
// }

int CFtdREngine::HandlePackage(CFTDCPackage *pFTDCPackage, CFTDCRSession *pSession)
{
	CUserIDType	UserID;
	CBrokerIDType	BrokerID;
	GetSessionOwner(pSession->GetSessionID(), UserID, BrokerID);

	int nRet = 0;
	long FtdRecDown;
	InputLong(FtdRecDown);
	switch(pFTDCPackage->GetTID()) {
	case FTD_TID_ReqOrderInsert:
		{
			m_reqPackage.PreparePublish(TID_ReqOrderInsert);
			m_reqPackage.SetFrontID(m_dwFrontID);
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
			if (g_bLatencyOut)
			{
				m_reqPackage.SetGroupID(FtdRecDown);
			}
			m_reqPackage.AddField(&(CInputOrderField::m_Describe),pFTDCPackage->Address()+sizeof(TFieldHeader));
			m_reqPackage.MakePackage();
			m_pReqFlow->Append(m_reqPackage.Address(),m_reqPackage.Length());
		}
		break;
	case FTD_TID_ReqOrderAction:
		{
			m_reqPackage.PreparePublish(TID_ReqOrderAction);
			m_reqPackage.SetFrontID(m_dwFrontID);
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
			CFTDOrderActionField FtdcOrderAction;
			pFTDCPackage->GetSingleField(&(FtdcOrderAction.m_Describe),&FtdcOrderAction);
			COrderActionField OrderAction;
			CopyAPIOrderActionEntity(&OrderAction,&FtdcOrderAction);
			OrderAction.UserID = UserID;
			OrderAction.BrokerID = BrokerID;
			m_reqPackage.AddField(&(COrderActionField::m_Describe),&OrderAction);
			m_reqPackage.MakePackage();
			m_pReqFlow->Append(m_reqPackage.Address(),m_reqPackage.Length());
		}
		break;
		//新增，为了内存数据库的导出
		//by wangwei,20130114
	case FTD_TID_ReqDumpMemDb:
		{
			m_reqPackage.PreparePublish(TID_ReqDumpMemDb);
			m_reqPackage.SetFrontID(m_dwFrontID);
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
			CFTDMemDbField FtdField;
			pFTDCPackage->GetSingleField(&(FtdField.m_Describe),&FtdField);
			CMemDbField XtpField;
			CopyMemDbEntity(&XtpField,&FtdField);
			m_reqPackage.AddField(&(CMemDbField::m_Describe),&XtpField);
			m_reqPackage.MakePackage();
			m_pReqFlow->Append(m_reqPackage.Address(),m_reqPackage.Length());

			FTD_REQ_QUERY(TID_ReqDumpMemDb, CFTDMemDbField, CMemDbField,
			{
				CopyMemDbEntity(&xtpField, &ftdField);
			});
		}
		break;
	case FTD_TID_ReqUserLogin:
		{
			nRet = OnReqUserLogin(pFTDCPackage, (CFTDCRSession *)pSession);
		}
		break;
	case FTD_TID_ReqUserLogout:
		{
			m_reqPackage.PreparePublish(TID_ReqUserLogout);
			m_reqPackage.SetFrontID(m_dwFrontID);
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
			CFTDReqUserLogoutField FtdField;
			pFTDCPackage->GetSingleField(&(FtdField.m_Describe),&FtdField);
			CUserLogoutField XtpField;
			CopyAPIUserLogoutEntity(&XtpField,&FtdField);
			XtpField.FrontID = m_dwFrontID;
			XtpField.SessionID = pSession->GetSessionID();
			m_reqPackage.AddField(&(CUserLogoutField::m_Describe),&XtpField);
			m_reqPackage.MakePackage();
			m_pReqFlow->Append(m_reqPackage.Address(),m_reqPackage.Length());
		}
		break;
	case FTD_TID_ReqUserPasswordUpdate:
		{
			m_reqPackage.PreparePublish(TID_ReqUserPasswordUpdate);
			m_reqPackage.SetFrontID(m_dwFrontID);
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
			CFTDUserPasswordUpdateField FtdField;
			pFTDCPackage->GetSingleField(&(FtdField.m_Describe),&FtdField);
			CUserPasswordUpdateField XtpField;
			CopyUserPasswordUpdateEntity(&XtpField,&FtdField);
			m_reqPackage.AddField(&(CUserPasswordUpdateField::m_Describe),&XtpField);
			m_reqPackage.MakePackage();
			m_pReqFlow->Append(m_reqPackage.Address(),m_reqPackage.Length());
		}
		break;
	case FTD_TID_ReqForceUserExit:
		{
			m_reqPackage.PreparePublish(TID_ReqForceUserExit);
			m_reqPackage.SetFrontID(m_dwFrontID);
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
			CFTDForceUserExitField FtdField;
			pFTDCPackage->GetSingleField(&(FtdField.m_Describe),&FtdField);
			CForceUserExitField XtpField;
			CopyForceUserExitEntity(&XtpField,&FtdField);
			m_reqPackage.AddField(&(CForceUserExitField::m_Describe),&XtpField);
			m_reqPackage.MakePackage();
			m_pReqFlow->Append(m_reqPackage.Address(),m_reqPackage.Length());
		}
		break;
	case FTD_TID_ReqForceUserLogout:
		{
			m_reqPackage.PreparePublish(TID_ReqForceUserLogout);
			m_reqPackage.SetFrontID(m_dwFrontID);
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
			CFTDForceUserExitField FtdField;
			pFTDCPackage->GetSingleField(&(FtdField.m_Describe),&FtdField);
			CForceUserExitField XtpField;
			CopyForceUserExitEntity(&XtpField,&FtdField);
			m_reqPackage.AddField(&(CForceUserExitField::m_Describe),&XtpField);
			m_reqPackage.MakePackage();
			m_pReqFlow->Append(m_reqPackage.Address(),m_reqPackage.Length());
		}
		break;
		//add by cgm 在userapi加入投资者出入金
	case FTD_TID_ReqAccountDeposit:
		{
			m_reqPackage.PreparePublish(TID_DbInvestorAccountDeposit);
			m_reqPackage.SetFrontID(m_dwFrontID);
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
			CFTDReqAccountDepositField FtdField;
			pFTDCPackage->GetSingleField(&(FtdField.m_Describe),&FtdField);
			CDbmtInvestorAccountDepositField XtpField;
			CopyInvestorAccountDepositEntity(&XtpField,&FtdField);
			m_reqPackage.AddField(&(CDbmtInvestorAccountDepositField::m_Describe),&XtpField);
			m_reqPackage.MakePackage();
			m_pReqFlow->Append(m_reqPackage.Address(),m_reqPackage.Length());
		}
		break;
		//分价查询
	case FTD_TID_ReqQryMBLMarketData:
		{
			m_reqPackage.PreparePublish(TID_ReqQryMBLMarketData);
			m_reqPackage.SetFrontID(m_dwFrontID);
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
			CFTDQryMBLMarketDataField FtdField;
			pFTDCPackage->GetSingleField(&(FtdField.m_Describe),&FtdField);
			CQryMBLMarketDataField XtpField;
			CopyQryMBLMarketDataEntity(&XtpField,&FtdField);
			XtpField.LogUserID=UserID;
			XtpField.LogBrokerID=BrokerID;
			m_reqPackage.AddField(&(CQryMBLMarketDataField::m_Describe),&XtpField);
			m_reqPackage.MakePackage();
			m_pReqFlow->Append(m_reqPackage.Address(),m_reqPackage.Length());
		}
		break;
	case FTD_TID_ReqQryOrder:			
		FTD_REQ_QUERY(TID_ReqQryOrder, CFTDQryOrderField, CQryOrderField,
		{
			CopyAPIQryOrderEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
		});
		break;
	case FTD_TID_ReqQryTrade:		
		FTD_REQ_QUERY(TID_ReqQryTrade, CFTDQryTradeField, CQryTradeField,
		{
			CopyAPIQryTradeEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
		});		
		break;
	//可用投资者查询
	case FTD_TID_ReqQryUserInvestor:
		FTD_REQ_QUERY(TID_ReqQryUserInvestor, CFTDQryUserInvestorField, CQryUserInvestorField,
		{
			CopyAPIQryUserInvestorEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
		});
		break;
	//投资者账户查询
	case FTD_TID_ReqQryInvestorAccount:	
		FTD_REQ_QUERY(TID_ReqQryInvestorAccount, CFTDQryInvestorAccountField, CQryInvestorAccountField,
		{
			CopyAPIQryInvestorAccountEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
		});
		break;
	case FTD_TID_ReqQryInstrument:
		FTD_REQ_QUERY(TID_ReqQryInstrument, CFTDQryInstrumentField, CQryInstrumentField,
		{
			CopyAPIQryInstrumentEntity(&xtpField, &ftdField);
		});
		break;
	case FTD_TID_ReqQryMarketData:
		FTD_REQ_QUERY(TID_ReqQryMarketData, CFTDQryMarketDataField, CQryMarketDataField,
		{
			CopyAPIQryMarketDataEntity(&xtpField, &ftdField);
		});
		break;
	//交易所查询
	case FTD_TID_ReqQryExchange :
		FTD_REQ_QUERY(TID_ReqQryExchange, CFTDQryExchangeField, CQryExchangeField,
		{
			CopyAPIQryExchangeEntity(&xtpField, &ftdField);
		});
		break;
	//投资者持仓查询
	case FTD_TID_ReqQryInvestorPosition:
		FTD_REQ_QUERY(TID_ReqQryInvestorPosition, CFTDQryInvestorPositionField, CQryInvestorPositionField,
		{
			CopyAPIQryInvestorPositionEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
		});
		break;			
	case FTD_TID_ReqQryInvestorFee:
		FTD_REQ_QUERY(TID_ReqQryInvestorFee, CFTDQryInvestorFeeField, CQryInvestorFeeField,
		{
			CopyAPIQryInvestorFeeEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
		});
		break;
	case FTD_TID_ReqQryInvestorMargin:
		FTD_REQ_QUERY(TID_ReqQryInvestorMargin, CFTDQryInvestorMarginField, CQryInvestorMarginField,
		{
			CopyAPIQryInvestorMarginEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
		});
		break;
		//金交所递延费率查询
	case FTD_TID_ReqQrySGEDeferRate:
		FTD_REQ_QUERY(TID_ReqQrySGEDeferRate, CFTDQrySGEDeferRateField, CQrySGEDeferRateField,
		{
			CopyQrySGEDeferRateEntity(&xtpField, &ftdField);
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
		});
		break;
		//期权手续费率查询
	case FTD_TID_ReqQryInvestorOptionFee:
		FTD_REQ_QUERY(TID_ReqQryInvestorOptionFee, CFTDQryInvestorOptionFeeField, CQryInvestorOptionFeeField,
		{
			CopyAPIQryInvestorOptionFeeEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
		});
		break;
	default:
		SendError(pSession, 1, "Unrecognized ftd tid");
		break;
	}
	
	return nRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CQueryFlowHandler::OnResponse(CXTPPackage *pPackage)
{
	pPackage->MakePackage();
	g_pQueryFlow->Append(pPackage->Address(),pPackage->Length());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CKernelRFront::CKernelRFront(CFlow* pSlogResult, CConfig * pConfig,int nLifeCycleID)
{
	m_pSlogResult=pSlogResult;
	m_pConfig = pConfig;
	m_pSeriesFlow =new CExCachedFlow(false, 0x7fffffff, 0x100000);
	m_reader.AttachFlow(m_pSeriesFlow,0);

	m_rspPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);

	m_dwFrontID=1;//只有1个前置
	m_nLifeCycleID = nLifeCycleID;
	m_bShmFlag = false;
	Init();
}

CKernelRFront::~CKernelRFront()
{
	if (m_pFtdREngine != NULL)
	{
		delete m_pFtdREngine;
	}
			
}

bool CKernelRFront::InitInstance()
{
#ifdef LINUX
	REPORT_EVENT(LOG_CRITICAL,"qtrade api recv thread", " [%ld]\n", gettid());
#endif
	return true;
}

bool CKernelRFront::Init()
{
	m_pFtdREngine = new CFtdREngine(this,m_pConfig->getConfig("qquery"),m_pSeriesFlow,m_pSlogResult,m_dwFrontID,
		m_nLifeCycleID,atoi(m_pConfig->getConfig("EvokeCpuInterval")),g_pConnReactor);//处理客户包
	
	char* pShmaddr=m_pConfig->getConfig("shmaddr");
	if (strcmp(pShmaddr,""))
	{
		m_pFtdREngine->RegisterListener(pShmaddr);//打开共享内存监听			
		SetNoShmChannelFlag(false);
		m_bShmFlag = true;
	}

	return true;
}

void CKernelRFront::FrontStartWork()
{
	Create();
	
	if (m_pFtdREngine != NULL)
	{
		m_pFtdREngine->RegisterListener(m_pConfig->getConfig("ufd"));
		m_pFtdREngine->Start();
	}
	REPORT_EVENT(LOG_CRITICAL,"FrontStartWork","front open port\n");
}


