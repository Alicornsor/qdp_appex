#include "FixServerSession.h"
#include "FileStore.h"



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

CFixServerSession::CFixServerSession(const char *pFixServerCfgFile)
:m_iMaxSsID(0), m_FixServerStarted(false),m_dwSessionIDBase(0)
{
	std::string file = pFixServerCfgFile;
	FIX::SessionSettings  settings( file );
	InitSession(settings);
}

CFixServerSession::CFixServerSession(FIX::SessionSettings sSettings, std::string sSenderCompID)
:m_iMaxSsID(0), m_FixServerStarted(false)
{
	if (sSenderCompID.size() == 0)
	{
		m_SenderCompID = QDP_TARGET_COMP_ID;
	}
	else
	{
		m_SenderCompID = sSenderCompID;
	}

	InitSession(sSettings);
}

void CFixServerSession::InitSession(FIX::SessionSettings &sSettings)
{
	m_CFixApplication.RegisterCB(this);
	FIX::FileStoreFactory storeFactory( sSettings );
	if (sSettings.get().has("LogType"))
	{
		try
		{
			if (sSettings.get().getLong("LogType") == 1)
			{//printf
				FIX::ScreenLogFactory logFactory( sSettings );		
				m_CSocketAcceptor  = new FIX::SocketAcceptor(m_CFixApplication, storeFactory, sSettings, logFactory);
			}
			else if (sSettings.get().getLong("LogType") == 2)
			{
				FIX::FileLogFactory fileLogFactory( sSettings );
				m_CSocketAcceptor  = new FIX::SocketAcceptor(m_CFixApplication, storeFactory, sSettings, fileLogFactory);
			}
			else
			{
				m_CSocketAcceptor  = new FIX::SocketAcceptor(m_CFixApplication, storeFactory, sSettings);
			}
		}
		catch (FIX::ConfigError& e)
		{
			printf("SocketAcceptor error:%s\n", e.what());
			SLEEP(1);
			exit(-1);
		}
		catch ( ... )
		{
			printf("SocketAcceptor error");
			exit(-1);
		}

	}
	else
	{
		m_CSocketAcceptor  = new FIX::SocketAcceptor(m_CFixApplication, storeFactory, sSettings);
	}

	m_ClOrdIDSessionIDMap = new ClOrdIDSessionIDMap();
	m_CSessionMap.clear();
	
	m_CSocketAcceptor->RegisterCB(this);
	m_FixEngineErrMsgMap  = new FixEngineErrMsgMap();
	InitErrMsgMap(m_FixEngineErrMsgMap);
	printf("FIX::SocketAcceptor InitFinished\n");
}

CFixServerSession::~CFixServerSession()
{

	if (NULL != m_CSocketAcceptor)
	{
		delete m_CSocketAcceptor;
		m_CSocketAcceptor = NULL;
	}
	
	if (NULL != m_ClOrdIDSessionIDMap)
	{
		delete m_ClOrdIDSessionIDMap;
		m_ClOrdIDSessionIDMap = NULL;
	}

	if (NULL != m_FixEngineErrMsgMap)
	{
		delete m_FixEngineErrMsgMap;
		m_FixEngineErrMsgMap = NULL;
	}
}

bool CFixServerSession::IsFixServerStarted()
{
	return m_FixServerStarted;
}

//处理从下游上发的消息
void CFixServerSession::HandleMessage( FIX::IntFIXMsgType type, FIX::Message msg, FIX::SessionID sessionID)
{
	std::string msgType = msg.getHeader().getField(FIX::FIELD::MsgType);
	//if (msgType == "D")
	//{
	//	std::string ClOrdID = msg.getField(FIX::FIELD::ClOrdID);
	//	if (!ClOrdID.empty())
	//	{
	//		if (!SetOrderInfo(ClOrdID.c_str(), sessionID))
	//		{
	//			//fixme:: rturn duplicate order
	//			printf("收到重复的报单：%s\n", ClOrdID.c_str());
	//			SendBusinessRejectMessage(const_cast<FIX::Message*>(&msg), sessionID, ERR_FIX_ENGINE_DUPLICATE_ORDER, RefMsgType_D, BusinessRejectReason_0);
	//			return;
	//		}
	//	}
	//}
	//else 
	if (msgType == "A")
	{
		GenSSID(sessionID);
	}

	if (m_CFixServerSessionCB)
	{
		//m_CFixServerSessionCB->HandlePackage(type, msg, sessionID);
	}
}

void CFixServerSession::HandleFixMessage(const std::string &type, FIX::Message msg, FIX::SessionID sessionID)
{
	if (type == "A")
	{
		GenSSID(sessionID);
	}
	if (m_CFixServerSessionCB)
	{
		m_CFixServerSessionCB->HandlePackage(type, msg, sessionID);
	}
}

bool CFixServerSession::SetOrderInfo(const char *pClOrdID, FIX::SessionID sessionID)
{
	std::string ssID;
	sessionID.toString(ssID);
	ClOrdIDSessionIDMapIter iter = m_ClOrdIDSessionIDMap->find(std::string(pClOrdID));
	if (iter == m_ClOrdIDSessionIDMap->end())
	{
		m_ClOrdIDSessionIDMap->insert(make_pair(std::string(pClOrdID), ssID));
		return true;
	}
	return false;
}

void CFixServerSession::OnErrLogonRsp(const char *pUser, const char *iErrCode)
{
	FIX::Message rsp;
	rsp.getHeader().setField(FIX::BeginString(STRING_QUICKFIX_VERSION_42));
	rsp.getHeader().setField(FIX::MsgType(FIX::MsgType_Logout));
	rsp.getHeader().setField(FIX::SenderCompID(m_SenderCompID));
	rsp.getHeader().setField(FIX::TargetCompID(pUser));
	rsp.setField(FIX::Text(iErrCode));
	
	SendMsg2FixClient(rsp);
	DelSSID(FIX::SessionID(STRING_QUICKFIX_VERSION_42, m_SenderCompID, pUser));
}

void CFixServerSession::OnErrLogonRsp(const FIX::SessionID& sessionID, const char *pUser, std::string errmsg )
{
	FIX::Message rsp;
	rsp.getHeader().setField(FIX::BeginString(STRING_QUICKFIX_VERSION_42));
	rsp.getHeader().setField(FIX::MsgType(FIX::MsgType_Logout));
	rsp.getHeader().setField(FIX::SenderCompID(m_SenderCompID));
	rsp.getHeader().setField(FIX::TargetCompID(pUser));
	rsp.setField(FIX::Text(errmsg));
	
	SendMsg2FixClient(rsp,sessionID);
}

void CFixServerSession::StartServer()
{
	if (m_FixServerStarted) return;
	m_CSocketAcceptor->start();
	m_FixServerStarted = true;
}

void CFixServerSession::OnRspLogon(const FIX::SessionID& sessionID, const char *pBrokerID, const char *pUser, const char *pPwd, int HeartBtInt )
{
	FIX::Message rsp;
	rsp.getHeader().setField(FIX::BeginString(STRING_QUICKFIX_VERSION_42));
	rsp.getHeader().setField(FIX::MsgType(FIX::MsgType_Logon));
	rsp.getHeader().setField(FIX::SenderCompID(m_SenderCompID));
	rsp.getHeader().setField(FIX::TargetCompID(pUser));
	rsp.setField(FIX::EncryptMethod(0));
	rsp.setField(FIX::HeartBtInt(HeartBtInt));

	SendMsg2FixClient(rsp, sessionID);
}

void CFixServerSession::OnRspLogon( const char *pBrokerID, const char *pUser, const char *pPwd, int HeartBtInt )
{
	FIX::Message rsp;
	rsp.getHeader().setField(FIX::BeginString(STRING_QUICKFIX_VERSION_42));
	rsp.getHeader().setField(FIX::MsgType(FIX::MsgType_Logon));
	rsp.getHeader().setField(FIX::SenderCompID(m_SenderCompID));
	rsp.getHeader().setField(FIX::TargetCompID(pUser));
	rsp.setField(FIX::EncryptMethod(0));
	rsp.setField(FIX::HeartBtInt(HeartBtInt));
	rsp.setField(FIX::RawData("logon success"));
	SendMsg2FixClient(rsp);
}

//维护一个FIX::SessionID 和 int sessionID的关系
DWORD CFixServerSession::GenSSID( FIX::SessionID sessionID )
{
	std::string sSessionID;
	sessionID.toString(sSessionID);
	DWORD ssID = ++m_dwSessionIDBase + (time(NULL)<<16);
	CSessionIdMapIter iter = m_CSessionMap.find(sSessionID);
	if (iter == m_CSessionMap.end())
	{
		m_CSessionMap.insert(make_pair(sSessionID, ssID));
		m_CSession2FIXMap.insert(make_pair(ssID, sSessionID));
	}
	else
	{
		ssID = iter->second;
	}

	return ssID;
}

void CFixServerSession::DelSSID( FIX::SessionID sessionID )
{
	std::string sSessionID;
	sessionID.toString(sSessionID);
	CSessionIdMapIter iter = m_CSessionMap.find(sSessionID);
	if (iter != m_CSessionMap.end())
	{
		m_CSession2FIXMap.erase(iter->second);
		m_CSessionMap.erase(iter);
		
	}
}

//维护一个FIX::SessionID 和 int sessionID的关系
DWORD CFixServerSession::GetSSID( FIX::SessionID sessionID )
{
	DWORD ssID = -1;
	std::string sSessionID;
	sessionID.toString(sSessionID);
	CSessionIdMapIter iter = m_CSessionMap.find(sSessionID);
	if (iter != m_CSessionMap.end())
	{
		ssID = iter->second;
	}

	return ssID;
}

void CFixServerSession::onConnect(  )
{
	//printf("收到连接请求\n");
}
void CFixServerSession::onDisconnect( FIX::Session* pSession )
{
	if (NULL == pSession) return;
	printf("Disconnected:%s\n", pSession->getSessionID().toString().c_str());

	//发送logout给qtrade
	FIX::Message rsp;
	rsp.getHeader().setField(FIX::BeginString(STRING_QUICKFIX_VERSION_42));
	rsp.getHeader().setField(FIX::MsgType(FIX::MsgType_Logout));
	rsp.getHeader().setField(FIX::SenderCompID(pSession->getSessionID().getTargetCompID().getValue().c_str()));
	rsp.getHeader().setField(FIX::TargetCompID(pSession->getSessionID().getSenderCompID().getValue().c_str()));
	rsp.getHeader().setField(FIX::OnBehalfOfCompID(pSession->getBrokerID().c_str()));
	rsp.setField(FIX::Text("Session disconnect"));

	if (m_CFixServerSessionCB)
	{
		m_CFixServerSessionCB->HandlePackage(FIX::MsgType_Logout, rsp, pSession->getSessionID());
	}
	FIX::SessionID ssID = pSession->getSessionID();
	DelSSID(ssID);
}

void CFixServerSession::SendExecutionReportMessage(FIX::Message* pMsg, const char *pClOrdID)
{
	if (NULL == pMsg) return;
	pMsg->getHeader().setField(FIX::MsgType(FIX::MsgType_ExecutionReport));
	SendMsg2FixClient(*pMsg);
}

void CFixServerSession::SendExecutionReportMessage(const FIX::SessionID& sessionID, FIX::Message* pMsg, const char *pClOrdID)
{
	if (NULL == pMsg) return;
	pMsg->getHeader().setField(FIX::MsgType(FIX::MsgType_ExecutionReport));
	SendMsg2FixClient(*pMsg, sessionID);
}

void CFixServerSession::SendPositionReportMessage(const FIX::SessionID& sessionID, FIX::Message* pMsg)
{
	/*if (NULL == pMsg) return;
	pMsg->getHeader().setField(FIX::MsgType(FIX::MsgType_AccountPositionReport));
	SendMsg2FixClient(*pMsg, sessionID);*/
}


//发送错误信息
void CFixServerSession::SendBusinessRejectMessage(const FIX::Message *pMsg, const FIX::SessionID& sessionID, int iErrCode, const char* pRefMsgType, int iBusinessRejectReason)
{
	if ( NULL == pMsg ) return;
	FIX::Message msg;
	char tmpbuf[128]={0};
	//header
	msg.getHeader().setField(sessionID.getBeginString());
	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_BusinessMessageReject));
	msg.getHeader().setField(sessionID.getSenderCompID());
	msg.getHeader().setField(sessionID.getTargetCompID());
	//body
	msg.setField(FIX::Text(GetErrMsg(iErrCode).c_str()));
	msg.setField(FIX::RefMsgType(pRefMsgType));
	sprintf(tmpbuf, "%d", iErrCode);
	msg.setField(FIX::BusinessRejectRefID(tmpbuf));
	msg.setField(FIX::BusinessRejectReason(iBusinessRejectReason));
	SendMsg2FixClient(msg, sessionID);
}

void CFixServerSession::SendBusinessRspRejectMessage(const FIX::Message * pMsg, const int iErrid, const char* iErrCode, const char * pRefMsgType, int iBusinessRejectReason, FIX::SessionID& tmpFixSession)
{
	if (NULL == pMsg) return;
	FIX::Message msg;
	msg.getHeader().setField(tmpFixSession.getBeginString());
	msg.getHeader().setField(tmpFixSession.getSenderCompID());
	msg.getHeader().setField(tmpFixSession.getTargetCompID());
	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_BusinessMessageReject));
	//body
	msg.setField(FIX::Text(iErrCode));
	msg.setField(FIX::RefMsgType(pRefMsgType));
	char tmpbuf[128] = { 0 };
	sprintf(tmpbuf, "%d", iErrid);
	msg.setField(FIX::BusinessRejectRefID(tmpbuf));
	msg.setField(FIX::BusinessRejectReason(iBusinessRejectReason));

	SendMsg2FixClient(msg, tmpFixSession);
}

void CFixServerSession::SendBusinessRspRejectMessage2(const FIX::Message * pMsg, const int iErrid, const char * iErrCode, const char * pRefMsgType, int iBusinessRejectReason)
{
	if (NULL == pMsg) return;
	FIX::Message msg;
	msg.getHeader().setField(FIX::BeginString(pMsg->getHeader().getField(FIX::FIELD::BeginString)));
	msg.getHeader().setField(FIX::SenderCompID(pMsg->getHeader().getField(FIX::FIELD::SenderCompID)));
	msg.getHeader().setField(FIX::TargetCompID(pMsg->getHeader().getField(FIX::FIELD::TargetCompID)));
	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_BusinessMessageReject));
	//body
	msg.setField(FIX::Text(iErrCode));
	msg.setField(FIX::RefMsgType(pRefMsgType));
	char tmpbuf[128] = { 0 };
	sprintf(tmpbuf, "%d", iErrid);
	msg.setField(FIX::BusinessRejectRefID(tmpbuf));
	msg.setField(FIX::BusinessRejectReason(iBusinessRejectReason));

	SendMsg2FixClient(msg);
}

void CFixServerSession::SendOrderCancelReject( FIX::Message* pMsg )
{
	if (NULL == pMsg) return;
	pMsg->getHeader().setField(FIX::MsgType(FIX::MsgType_OrderCancelReject));
	SendMsg2FixClient(*pMsg);
}

void CFixServerSession::SendOrderCancelReject(const FIX::SessionID& sessionID, FIX::Message *pMsg )
{
	if (NULL == pMsg) return;
	pMsg->getHeader().setField(FIX::MsgType(FIX::MsgType_OrderCancelReject));
	SendMsg2FixClient(*pMsg, sessionID);
}

void CFixServerSession::SendMsg2FixClient( FIX::Message &rsp, const FIX::SessionID& sessionID)
{
	try
	{
		//判断是否已经登录
		FIX::Session::sendToTarget(rsp, sessionID);
	}
	catch (FIX::SessionNotFound& e)
	{
		//printf("SessionNotFound=%s\n", rsp.toString().c_str());
		REPORT_EVENT(LOG_WARNING, "SessionNotFound=[%s],msgtype=[%s]", sessionID.toString().c_str(), rsp.getHeader().getField(FIX::FIELD::MsgType).c_str());
	}
}

void CFixServerSession::SendMsg2FixClient( FIX::Message &rsp )
{
	try
	{
		//判断是否已经登录
		FIX::Session::sendToTarget(rsp);
	}
	catch (FIX::SessionNotFound& e)
	{
		//printf("订单发送失败:%s\n", e.what());
		REPORT_EVENT(LOG_WARNING, "SessionNotFound=[%s],msgtype=[%s]", rsp.getSessionID().toString().c_str(), rsp.getHeader().getField(FIX::FIELD::MsgType).c_str());
	}
}

void CFixServerSession::InitErrMsgMap(FixEngineErrMsgMap *pErrMsgMap)
{
	pErrMsgMap->clear();
	pErrMsgMap->insert(make_pair(ERROR_DUPLICATE_ORDER, std::string("Duplicate order")));
	pErrMsgMap->insert(make_pair(ERR_FIX_ENGINE_DUPLICATE_ORDER, std::string("Duplicate order")));
	pErrMsgMap->insert(make_pair(ERR_FIX_ENGINE_UNSUPPORT_ORDER_TYPE, std::string("Unsupport order type")));
	pErrMsgMap->insert(make_pair(ERR_FIX_ENGINE_INVAILD_USER_ID, std::string("User or passwd invaild")));
	pErrMsgMap->insert(make_pair(ERROR_INSTRUMENT_NOT_FOUND, std::string("SecurityID invaild")));
	pErrMsgMap->insert(make_pair(ERR_FIX_ENGINE_ORDER_CANCEL_FAIL, std::string("Order cancel fail")));
	pErrMsgMap->insert(make_pair(ERR_FIX_ENGINE_OTHER_ORDER, std::string("Other error")));
	pErrMsgMap->insert(make_pair(ERROR_USER_MISMATCH, std::string("UserID not found")));
	pErrMsgMap->insert(make_pair(ERROR_USER_NOT_LOGIN, std::string("The user is not login")));
	pErrMsgMap->insert(make_pair(ERROR_USER_INVESTOR_NOT_RELATED, std::string("User investor relationship does not exist")));
	pErrMsgMap->insert(make_pair(ERROR_CAN_NOT_FIND_ACCOUNT, std::string("Can not found account")));
	pErrMsgMap->insert(make_pair(ERROR_PRICE_OUT_OF_LOWER_BOUND, std::string("Price out of lower bound")));
	pErrMsgMap->insert(make_pair(ERROR_PRICE_OUT_OF_UPPER_BOUND, std::string("Price out of upper bound")));
	
}

std::string CFixServerSession::GetErrMsg(int iErrCode)
{
	FixEngineErrMsgMapIter iter = m_FixEngineErrMsgMap->find(iErrCode);
	if (iter == m_FixEngineErrMsgMap->end())
	{
		return std::string("Other error");
	}
	return iter->second;
}

