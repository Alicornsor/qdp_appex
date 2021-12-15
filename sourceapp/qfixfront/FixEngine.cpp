/////////////////////////////////////////////////////////////////////////
///@system  TMDBScheduler.cpp: implementation of the CTMDBScheduler class.
///@company 上海量投网络科技有限公司
///@brief 下场模块，将kernel的结果流的关键数据入库
///@history 
///20160814	xlong		               创建该文件
///20170925 xlong       BUG-005        熵一qfixfront带流重启 异常退出
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "FixEngine.h"
#include "utility.h"
#include "BaseFunction.h"
#define MSG_SSLERR_INVALID_USERID	0xB001

extern const char *APP_NAME;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define ORDER_RSPTIME_TIMER_ID  10
#define ORDER_RSPTIME_INTERVAL	1000
#define TYPE_IN                 1
#define TYPE_OUT                2
#define SECURITY_TYPE           3
#define SECURITY_TYPE_IN        4


//CFixEngine::CFixEngine(CReactor *pReactor, CFixFrontForwarder *pFrontForwarder,
//					   const char *pszFlowPath,CSelectReactor* pConnReactor,
//					   CConfig *pConf)
CFixEngine::CFixEngine(CCachedFileFlow *m_pSendFlow, CConfig *pConf, CFrontForwarder *m_pFrontForwarder)
:m_bEnableFixServer(false), m_bStop(false),m_pConf(pConf),m_pFixServerSession(NULL), m_pSendFlow(m_pSendFlow), m_pFrontForwarder(m_pFrontForwarder)
{
	//m_pFrontForwarder = pFrontForwarder;
	m_reqPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE, 1000);
	
	m_pCUserMap = new CUserMap();
	//m_pCodeMapingMapIn   = new CStringStringMap();
	//m_pCodeMapingMapOut  = new CStringStringMap();
	//m_pSecurityTypeMap   = new CStringStringMap();
	//m_pSecurityTypeMapIn = new CStringStringMap();
	m_QryUserInvestorMap = new CStringStringMap();
	updateUser = false;
	m_SenderCompID  = m_pConf->getConfig("SenderCompID");
}

CFixEngine::~CFixEngine()
{
	if (NULL != m_pCUserMap)
	{
		delete m_pCUserMap;
		m_pCUserMap = NULL;
	}
}

bool CFixEngine::ChkFrontID(DWORD dwFrontID)
{
	return true;
}

bool CFixEngine::DispatcherEvent(int nEventID, DWORD dwParam, void *pParam)
{
//	return PostEvent(nEventID,dwParam,pParam);
	return true;
}

int CFixEngine::HandlePackage(const std::string &type, const FIX::Message& msg, const FIX::SessionID& sessionID)
{
	//if (!m_pFrontForwarder->IsFrontClientConnected())
	//{
	//	return -1;
	//}
	int nRet = 0;
	if (type == FIX::MsgType_NewOrderSingle) {
		nRet = OnReqFixOrderInsert(msg, sessionID);
		return nRet;
	}
	else if (type == FIX::MsgType_OrderCancelRequest) {
		nRet = OnReqFixOrderAction(msg, sessionID);
		return nRet;
	}
	else if (type == FIX::MsgType_FillOrderListRequest) {
		nRet = OnReqQryFillOrder(msg, sessionID);
		return nRet;
	}
	else if (type == FIX::MsgType_OrderListRequest) {
		nRet = OnReqQryOrder(msg, sessionID);
		return nRet;
	}
	else if (type == FIX::MsgType_SecurityDefinitionRequest) {
		nRet = OnReqQrySecurityDefinition(msg, sessionID);
		return nRet;
	}
	else if (type == FIX::MsgType_RequestForMargin) {
		nRet = OnReqFixUserMargin(msg, sessionID);
		return nRet;
	}
	else if (type == FIX::MsgType_RequestForPosition) {
		nRet = OnReqFixUserPosition(msg, sessionID);
		return nRet;
	}
	else if (type == FIX::MsgType_RequestForFee) {
		nRet = OnReqFixFee(msg, sessionID);
		return nRet;
	}
	else if (type == FIX::MsgType_AvailableAccountRequest) {
		nRet = OnReqFixAvailableAccount(msg, sessionID);
		return nRet;
	}
	else if (type == FIX::MsgType_AccountDataRequest) {
		nRet = OnReqFixAccountData(msg, sessionID);
		return nRet;
	}
	else if (type == FIX::MsgType_UserRequest) {
		nRet = OnReqFixUserPasswd(msg, sessionID);
		return nRet;
	}
	else if (type == FIX::MsgType_Logon) {
		nRet = OnReqFixUserLogin(msg, sessionID);
		return nRet;
	}
	else if (type == FIX::MsgType_Logout) {
		nRet = OnReqFixUserLogout(msg, sessionID);
		return nRet;
	}
	else
	{
		REPORT_EVENT(LOG_INFO, "CFixEngine::HandlePackage", "unknown msgtype=[%s]", type.c_str() );
	}
	
	return nRet;
}

//处理从核心来的信息
int CFixEngine::HandleXTPMessage( CXTPPackage * pMessage )
{
	switch(pMessage->GetTid())
	{
	case TID_InitUser:             //用户
	{
			CUserField field;
			CUserMapIter userIter;
			CNamedFieldIterator it = pMessage->GetNamedFieldIterator(&field.m_Describe);
			while (!it.IsEnd())
			{
				memset(&field, 0x00, sizeof(CUserField));
				it.Retrieve(&field);
				userIter = m_pCUserMap->find(std::string(field.UserID.getValue()));
				if (userIter == m_pCUserMap->end())
				{
					m_pCUserMap->insert(make_pair(std::string(field.UserID.getValue()), field));
				}
				it.Next();
			}
	}
	break;
	case TID_InitInvestor:         //投资者
		break;
	case TID_InitUserInvestor:     //用户投资者关系
		{
			CUserInvestorField field;
			CNamedFieldIterator it = pMessage->GetNamedFieldIterator(&field.m_Describe);
			while(!it.IsEnd())
			{		
				memset(&field, 0x00, sizeof(CUserInvestorField));
				it.Retrieve(&field);
				it.Next();
			}
		}
		break;
	case TID_DataSyncEnd:          //数据同步结束
		{
			if (!updateUser)
			{
				GenFixConfFile();
				updateUser = true;
			}
		}
		break;
	default:
		return 0;
	}
	return 1;
}


int CFixEngine::OnReqFixUserLogin(const FIX::Message &msg, FIX::SessionID sessionID)
{
	std::string loginUser = msg.getHeader().getField(FIX::FIELD::SenderCompID);
	CUserField *pUser                = GetUserInfo(loginUser.c_str());
	if (NULL == pUser)
	{
		//不在可登录的用户信息中
		m_pFixServerSession->SendBusinessRejectMessage(&msg, sessionID, ERR_FIX_ENGINE_INVAILD_USER_ID, FIX::MsgType_Logon, BusinessRejectReason_0);
		return -1;
	}

	if(!ChkNeedSendLogin(loginUser.c_str())) return -1;
	InitLoginInfo(loginUser.c_str(), sessionID, false);

	FIX::Header head = msg.getHeader();
	CUserLoginField userLoginField;
	memset(&userLoginField, 0x0, sizeof(CUserLoginField));
	userLoginField.UserID			 = loginUser.c_str();
	//m_pFixServerSession->SendBusinessRspRejectMessage(&msg, 0, "Miss Tag Password", FIX::MsgType_Logon, BusinessRejectReason_0, sessionID);
	if(msg.isSetField(FIX::FIELD::Password))
		userLoginField.Password      = msg.getField(FIX::FIELD::Password).c_str();
	else {
		m_pFixServerSession->SendBusinessRspRejectMessage(&msg, 0, "Require Tag Password", FIX::MsgType_Logon, BusinessRejectReason_0, sessionID );
		return -1;
	}
	userLoginField.TradingSystemName = GenAppName().c_str();
	userLoginField.FrontID           = FRONTID;
	userLoginField.MaxOrderLocalID   = 0;
	userLoginField.ProtocolInfo      = FIXPROTOCOL_42;
	if(msg.isSetField(FIX::FIELD::ExecBroker))
		userLoginField.BrokerID		 = msg.getField(FIX::FIELD::ExecBroker).c_str();
	else {
		m_pFixServerSession->SendBusinessRspRejectMessage(&msg, 0, "Require Tag ExecBroker", FIX::MsgType_Logon, BusinessRejectReason_0, sessionID);
		return -1;
	}
	
	PrepareForward(&m_reqPackage, TID_ReqUserLogin, GetSessionID(userLoginField.UserID.getValue()), GetReqID(userLoginField.UserID.getValue()));
	XTP_ADD_FIELD(&m_reqPackage, &userLoginField);
	sendTradeBusiness(&m_reqPackage);

	REPORT_EVENT(LOG_WARNING, "OnReqFixUserLogin", "user=[%s]",userLoginField.UserID.getValue());
	return 0;
}

int CFixEngine::OnReqFixUserLogout( FIX::Message msg, FIX::SessionID sessionID)
{
	FIX::Header head  = msg.getHeader();
	const char *pUserID     = head.getField(FIX::FIELD::SenderCompID).c_str();
	IterUserLoginMap it = m_userLoginMap.find(pUserID);
	if (it == m_userLoginMap.end())
	{
		return 0;
	}
	
	CUserField *pUser = GetUserInfo(pUserID);
	CUserLogoutField userLogoutField;
	
	memset(&userLogoutField, 0x00, sizeof(CUserLogoutField));
	if (msg.isSetField(FIX::FIELD::ExecBroker))
		userLogoutField.BrokerID = msg.getField(FIX::FIELD::ExecBroker).c_str();
	else {
		userLogoutField.BrokerID = pUser->BrokerID;
	}
	userLogoutField.UserID   = pUserID;	
	PrepareForward(&m_reqPackage, TID_ReqUserLogout, GetSessionID(pUserID), GetReqID(pUserID));
	XTP_ADD_FIELD(&m_reqPackage, &userLogoutField);
	sendTradeBusiness(&m_reqPackage);
	
	REPORT_EVENT(LOG_WARNING, "OnReqFixUserLogout", "user=[%s]", userLogoutField.UserID.getValue());
	return 0;
}


int CFixEngine::OnReqFixOrderInsert(const FIX::Message& msg, FIX::SessionID sessionID)
{
	//printf("%s\n",__FUNCTION__);
	FIX::Header head  = msg.getHeader();
	const char *pUserID     = head.getField(FIX::FIELD::SenderCompID).c_str();
	IterUserLoginMap it = m_userLoginMap.find(pUserID);
	if (it == m_userLoginMap.end() || it->second->loginSuccess == false)
	{
		return 0;
	}
	
	CInputOrderField req;
	memset(&req, 0x00, sizeof(CInputOrderField));
	req.UserID			= pUserID;
	req.BrokerID		= msg.getField(FIX::FIELD::ExecBroker).c_str();
	req.InvestorID		= msg.getField(FIX::FIELD::Account).c_str();
	req.Direction       = (msg.getField(FIX::FIELD::Side).c_str()[0] == SideType_Buy)?D_Buy:D_Sell;
	req.ExchangeID		= msg.getField(FIX::FIELD::SecurityExchange).c_str();
	req.HedgeFlag       = msg.getField(FIX::FIELD::HedgeFlag).c_str()[0];
	req.InstrumentID    = msg.getField(FIX::FIELD::SecurityID).c_str();
	req.LimitPrice      = msg.getField(FIX::FIELD::Price).c_str();
	req.OffsetFlag		= (req.Direction == D_Buy) ? OF_Open : OF_Close;
	req.Volume          = msg.getField(FIX::FIELD::OrderQty).c_str();
	req.OrderPriceType  = msg.getField(FIX::FIELD::OrdType).c_str()[0];
	if (msg.isSetField(FIX::FIELD::TimeInForce))
	{
		switch (msg.getField(FIX::FIELD::TimeInForce)[0])
		{
		case FIX::TimeInForce_DAY:				   //GFD
			req.TimeCondition    = TC_GFD;
			break;
		case FIX::TimeInForce_GOOD_TILL_CANCEL:    //GTC
			req.TimeCondition    = TC_GTC;
			break;
		case FIX::TimeInForce_IMMEDIATE_OR_CANCEL: //IOC
			req.TimeCondition    = TC_IOC;
			break;
		case FIX::TimeInForce_FILL_OR_KILL:        //FOK
			m_pFixServerSession->SendBusinessRejectMessage(&msg, sessionID, ERR_FIX_ENGINE_UNSUPPORT_ORDER_TYPE, RefMsgType_D, BusinessRejectReason_0);
			return 0;
		case FIX::TimeInForce_GOOD_TILL_DATE:      //GTD
			req.TimeCondition    = TC_GTD;
			if(msg.isSetField(FIX::FIELD::ExpireDate))
				req.GTDDate = msg.getField(FIX::FIELD::ExpireDate).c_str();
			break;
		default:
			req.TimeCondition = TC_GFD;
			break;
		}
	}
	else
	{//不含有，默认是当日有效
		req.TimeCondition    = TC_GFD;
	}
	
	req.VolumeCondition  = VC_AV;  //任何数量
	req.ForceCloseReason = FCR_NotForceClose; //非强平
	req.IsAutoSuspend    = 0;
	req.UserOrderLocalID = msg.getField(FIX::FIELD::ClOrdID).c_str();

	PrepareForward(&m_reqPackage, TID_ReqOrderInsert, GetSessionID(pUserID), GetReqID(pUserID));
	XTP_ADD_FIELD(&m_reqPackage, &req);
	sendTradeBusiness(&m_reqPackage);
	
	return 0;
}

int CFixEngine::OnReqFixOrderAction(FIX::Message msg, FIX::SessionID sessionID)
{
	//printf("%s\n", __FUNCTION__);
	FIX::Header head = msg.getHeader();
	const char *pUserID = head.getField(FIX::FIELD::SenderCompID).c_str();
	IterUserLoginMap it = m_userLoginMap.find(pUserID);
	if (it == m_userLoginMap.end() || it->second->loginSuccess == false)
	{
		return 0;
	}

	COrderActionField req;
	memset(&req, 0x00, sizeof(COrderActionField));
	req.UserID = pUserID;
	req.BrokerID				= msg.getField(FIX::FIELD::ExecBroker).c_str();
	req.InvestorID				= msg.getField(FIX::FIELD::Account).c_str();
	req.UserOrderLocalID		= msg.getField(FIX::FIELD::ClOrdID).c_str();
	req.OrderSysID				= msg.getField(FIX::FIELD::OrderID).c_str();
	req.UserOrderActionLocalID	= msg.getField(FIX::FIELD::OrigClOrdID).c_str();
	req.ExchangeID				= msg.getField(FIX::FIELD::SecurityExchange).c_str();
	req.ActionFlag				= AF_Delete;

	PrepareForward(&m_reqPackage, TID_ReqOrderAction, GetSessionID(pUserID), GetReqID(pUserID));
	XTP_ADD_FIELD(&m_reqPackage, &req);
	sendTradeBusiness(&m_reqPackage);
	return 0;
}

int CFixEngine::OnReqFixUserMargin(const FIX::Message & msg, FIX::SessionID sessionID)
{
	FIX::Header head = msg.getHeader();
	const char *pUserID = head.getField(FIX::FIELD::SenderCompID).c_str();
	IterUserLoginMap it = m_userLoginMap.find(pUserID);
	if (it == m_userLoginMap.end() || it->second->loginSuccess == false)
	{
		return 0;
	}
	
	CQryInvestorMarginField req;
	memset(&req, 0x00, sizeof(CQryInvestorMarginField));
	req.UserID				= pUserID;
	req.BrokerID			= msg.getField(FIX::FIELD::ExecBroker).c_str();
	req.InvestorID			= msg.getField(FIX::FIELD::Account).c_str();
	req.ExchangeID			= msg.getField(FIX::FIELD::SecurityExchange).c_str();
	req.InstrumentID		= msg.getField(FIX::FIELD::SecurityID).c_str();
	req.HedgeFlag			= msg.getField(FIX::FIELD::HedgeFlag).c_str()[0];
	req.LogUserID			= pUserID;
	req.LogBrokerID			= req.BrokerID;
	PrepareForward(&m_reqPackage, TID_ReqQryInvestorMargin, GetSessionID(pUserID), GetReqID(pUserID));
	XTP_ADD_FIELD(&m_reqPackage, &req);
	m_pFrontForwarder->ForwardQuery(&m_reqPackage);
	//REPORT_EVENT(LOG_INFO, "OnReqFixUserMargin", "UserID=[%s]", req.UserID.getValue());

	return 0;
}

int CFixEngine::OnReqFixUserPosition(const FIX::Message & msg, FIX::SessionID sessionID)
{
	FIX::Header head = msg.getHeader();
	const char *pUserID = head.getField(FIX::FIELD::SenderCompID).c_str();
	IterUserLoginMap it = m_userLoginMap.find(pUserID);
	if (it == m_userLoginMap.end() || it->second->loginSuccess == false)
	{
		return 0;
	}

	CQryInvestorPositionField req;
	memset(&req, 0x00, sizeof(CQryInvestorPositionField));
	req.UserID				= pUserID;
	req.BrokerID			= msg.getField(FIX::FIELD::ExecBroker).c_str();
	req.InvestorID			= msg.getField(FIX::FIELD::Account).c_str();
	req.ExchangeID			= msg.getField(FIX::FIELD::SecurityExchange).c_str();
	req.InstrumentID		= msg.getField(FIX::FIELD::SecurityID).c_str();
	req.LogUserID			= pUserID;
	req.LogBrokerID			= req.BrokerID;
	PrepareForward(&m_reqPackage, TID_ReqQryInvestorPosition, GetSessionID(pUserID), GetReqID(pUserID));
	XTP_ADD_FIELD(&m_reqPackage, &req);
	m_pFrontForwarder->ForwardQuery(&m_reqPackage);
	//REPORT_EVENT(LOG_INFO, "OnReqFixUserPosition", "UserID=[%s]", req.UserID.getValue());
	return 0;
}

int CFixEngine::OnReqFixAccountData(const FIX::Message & msg, FIX::SessionID sessionID)
{
	FIX::Header head = msg.getHeader();
	const char *pUserID = head.getField(FIX::FIELD::SenderCompID).c_str();
	IterUserLoginMap it = m_userLoginMap.find(pUserID);
	if (it == m_userLoginMap.end() || it->second->loginSuccess == false)
	{
		return 0;
	}

	CQryInvestorAccountField req;
	memset(&req, 0x00, sizeof(CQryInvestorAccountField));
	req.UserID		= pUserID;
	req.BrokerID	= msg.getField(FIX::FIELD::ExecBroker).c_str();
	req.InvestorID	= msg.getField(FIX::FIELD::Account).c_str();
	req.LogUserID	= pUserID;
	req.LogBrokerID = req.BrokerID;
	PrepareForward(&m_reqPackage, TID_ReqQryInvestorAccount, GetSessionID(pUserID), GetReqID(pUserID));
	XTP_ADD_FIELD(&m_reqPackage, &req);
	m_pFrontForwarder->ForwardQuery(&m_reqPackage);
	//REPORT_EVENT(LOG_INFO, "OnReqFixAccountData", "UserID=[%s]", req.UserID.getValue());
	return 0;
}

int CFixEngine::OnReqFixOrderMassStatus(const FIX::Message & msg, FIX::SessionID sessionID)
{
	FIX::Header head = msg.getHeader();
	const char *pUserID = head.getField(FIX::FIELD::SenderCompID).c_str();
	IterUserLoginMap it = m_userLoginMap.find(pUserID);
	if (it == m_userLoginMap.end() || it->second->loginSuccess == false)
	{
		return 0;
	}

	CQryOrderField req;
	memset(&req, 0x00, sizeof(CQryOrderField));
	req.UserID					= pUserID;
	req.BrokerID				= msg.getField(FIX::FIELD::ExecBroker).c_str();
	req.InvestorID				= msg.getField(FIX::FIELD::Account).c_str();
	if(msg.isSetField(FIX::FIELD::SecurityExchange))
		req.ExchangeID			= msg.getField(FIX::FIELD::SecurityExchange).c_str();
	if (msg.isSetField(FIX::FIELD::SecurityID))
		req.InstrumentID		= msg.getField(FIX::FIELD::SecurityID).c_str();
	if (msg.isSetField(FIX::FIELD::OrderID))
		req.OrderSysID			= msg.getField(FIX::FIELD::OrderID).c_str();
	req.LogUserID = pUserID;
	req.LogBrokerID = req.BrokerID;
	PrepareForward(&m_reqPackage, TID_ReqQryOrder, GetSessionID(pUserID), GetReqID(pUserID));
	XTP_ADD_FIELD(&m_reqPackage, &req);
	m_pFrontForwarder->ForwardQuery(&m_reqPackage);
	//REPORT_EVENT(LOG_INFO, "OnReqFixOrderMassStatus", "UserID=[%s]", req.UserID.getValue());
	return 0;
}

int CFixEngine::OnReqFixUserPasswd(const FIX::Message & msg, FIX::SessionID sessionID)
{
	FIX::Header head = msg.getHeader();
	const char *pUserID = head.getField(FIX::FIELD::SenderCompID).c_str();
	IterUserLoginMap it = m_userLoginMap.find(pUserID);
	if (it == m_userLoginMap.end() || it->second->loginSuccess == false)
	{
		return 0;
	}

	CUserPasswordUpdateField req;
	memset(&req, 0x0, sizeof(CUserPasswordUpdateField));
	req.UserID			= pUserID;
	req.BrokerID		= msg.getField(FIX::FIELD::ExecBroker).c_str();
	req.OldPassword		= msg.getField(FIX::FIELD::Password).c_str();
	req.NewPassword		= msg.getField(FIX::FIELD::NewPassword).c_str();

	PrepareForward(&m_reqPackage, TID_ReqUserPasswordUpdate, GetSessionID(pUserID), GetReqID(pUserID));
	XTP_ADD_FIELD(&m_reqPackage, &req);
	sendTradeBusiness(&m_reqPackage);
	REPORT_EVENT(LOG_WARNING, "OnReqFixUpdateUserPasswd", "UserID=[%s]", req.UserID.getValue());

	return 0;
}

int CFixEngine::OnReqFixAvailableAccount(const FIX::Message & msg, FIX::SessionID sessionID)
{
	FIX::Header head = msg.getHeader();
	const char *pUserID = head.getField(FIX::FIELD::SenderCompID).c_str();
	IterUserLoginMap it = m_userLoginMap.find(pUserID);
	if (it == m_userLoginMap.end() || it->second->loginSuccess == false)
	{
		return 0;
	}

	CQryUserInvestorField req;
	memset(&req, 0x0, sizeof(CQryUserInvestorField));
	req.UserID		= pUserID;
	req.BrokerID	= msg.getField(FIX::FIELD::ExecBroker).c_str();
	req.LogUserID	= pUserID;
	req.LogBrokerID = req.BrokerID;

	PrepareForward(&m_reqPackage, TID_ReqQryUserInvestor, GetSessionID(pUserID), GetReqID(pUserID));
	XTP_ADD_FIELD(&m_reqPackage, &req);
	m_pFrontForwarder->ForwardQuery(&m_reqPackage);
	//REPORT_EVENT(LOG_INFO, "OnReqFixAvailableAccount", "UserID=[%s]", req.UserID.getValue());

	return 0;
}

int CFixEngine::OnReqFixFee(const FIX::Message & msg, FIX::SessionID sessionID)
{
	FIX::Header head = msg.getHeader();
	const char *pUserID = head.getField(FIX::FIELD::SenderCompID).c_str();
	IterUserLoginMap it = m_userLoginMap.find(pUserID);
	if (it == m_userLoginMap.end() || it->second->loginSuccess == false)
	{
		return 0;
	}

	CQryInvestorFeeField req;
	memset(&req, 0x0, sizeof(CQryInvestorFeeField));
	req.UserID			= pUserID;
	req.BrokerID		= msg.getField(FIX::FIELD::ExecBroker).c_str();
	req.InvestorID		= msg.getField(FIX::FIELD::Account).c_str();
	req.ExchangeID		= msg.getField(FIX::FIELD::SecurityExchange).c_str();
	req.InstrumentID	= msg.getField(FIX::FIELD::SecurityID).c_str();
	req.HedgeFlag		= msg.getField(FIX::FIELD::HedgeFlag).c_str()[0];
	req.LogUserID		= pUserID;
	req.LogBrokerID		= req.BrokerID;
	PrepareForward(&m_reqPackage, TID_ReqQryInvestorFee, GetSessionID(pUserID), GetReqID(pUserID));
	XTP_ADD_FIELD(&m_reqPackage, &req);
	m_pFrontForwarder->ForwardQuery(&m_reqPackage);
	//REPORT_EVENT(LOG_INFO, "OnReqFixUserMargin", "UserID=[%s]", req.UserID.getValue());

	return 0;
}

int CFixEngine::OnReqQrySecurityDefinition(const FIX::Message & msg, FIX::SessionID sessionID)
{
	FIX::Header head = msg.getHeader();
	const char *pUserID = head.getField(FIX::FIELD::SenderCompID).c_str();
	IterUserLoginMap it = m_userLoginMap.find(pUserID);
	if (it == m_userLoginMap.end() || it->second->loginSuccess == false)
	{
		return 0;
	}

	CQryInstrumentField req;
	memset(&req, 0x0, sizeof(CQryInstrumentField));
	req.ExchangeID = msg.getField(FIX::FIELD::SecurityExchange).c_str();
	req.InstrumentID = msg.getField(FIX::FIELD::SecurityID).c_str();
	req.ProductID = msg.getField(FIX::FIELD::Symbol).c_str();
	PrepareForward(&m_reqPackage, TID_ReqQryInstrument, GetSessionID(pUserID), GetReqID(pUserID));
	XTP_ADD_FIELD(&m_reqPackage, &req);
	m_pFrontForwarder->ForwardQuery(&m_reqPackage);

	return 0;
}

int CFixEngine::OnReqQryFillOrder(const FIX::Message & msg, FIX::SessionID sessionID)
{
	FIX::Header head = msg.getHeader();
	const char *pUserID = head.getField(FIX::FIELD::SenderCompID).c_str();
	IterUserLoginMap it = m_userLoginMap.find(pUserID);
	if (it == m_userLoginMap.end() || it->second->loginSuccess == false)
	{
		return 0;
	}

	CQryTradeField req;
	memset(&req, 0x0, sizeof(CQryTradeField));
	req.InvestorID = msg.getField(FIX::FIELD::Account).c_str();
	req.BrokerID = msg.getField(FIX::FIELD::ExecBroker).c_str();
	if (msg.isSetField(FIX::FIELD::SecurityID))
		req.InstrumentID = msg.getField(FIX::FIELD::SecurityID).c_str();
	if (msg.isSetField(FIX::FIELD::SecurityExchange))
		req.ExchangeID = msg.getField(FIX::FIELD::SecurityExchange).c_str();
	if (msg.isSetField(FIX::FIELD::TradeID))
		req.TradeID = msg.getField(FIX::FIELD::TradeID).c_str();
	req.LogUserID = pUserID;
	req.LogBrokerID = req.BrokerID;
	PrepareForward(&m_reqPackage, TID_ReqQryTrade, GetSessionID(pUserID), GetReqID(pUserID));
	XTP_ADD_FIELD(&m_reqPackage, &req);
	m_pFrontForwarder->ForwardQuery(&m_reqPackage);
	return 0;
}

int CFixEngine::OnReqQryOrder(const FIX::Message & msg, FIX::SessionID sessionID)
{
	FIX::Header head = msg.getHeader();
	const char *pUserID = head.getField(FIX::FIELD::SenderCompID).c_str();
	IterUserLoginMap it = m_userLoginMap.find(pUserID);
	if (it == m_userLoginMap.end() || it->second->loginSuccess == false)
	{
		return 0;
	}

	CQryOrderField req;
	memset(&req, 0x0, sizeof(CQryOrderField));
	req.InvestorID = msg.getField(FIX::FIELD::Account).c_str();
	req.BrokerID = msg.getField(FIX::FIELD::ExecBroker).c_str();
	if (msg.isSetField(FIX::FIELD::SecurityID))
		req.InstrumentID = msg.getField(FIX::FIELD::SecurityID).c_str();
	if (msg.isSetField(FIX::FIELD::SecurityExchange))
		req.ExchangeID = msg.getField(FIX::FIELD::SecurityExchange).c_str();
	if (msg.isSetField(FIX::FIELD::OrderID))
		req.OrderSysID = msg.getField(FIX::FIELD::OrderID).c_str();
	req.LogUserID = pUserID;
	req.LogBrokerID = req.BrokerID;
	PrepareForward(&m_reqPackage, TID_ReqQryOrder, GetSessionID(pUserID), GetReqID(pUserID));
	XTP_ADD_FIELD(&m_reqPackage, &req);
	m_pFrontForwarder->ForwardQuery(&m_reqPackage);

	return 0;
}

int CFixEngine::OnReqQryExange(const FIX::Message & msg, FIX::SessionID sessionID)
{
	m_pFixServerSession->SendBusinessRspRejectMessage(&msg, 0,"Unsupported Request", FIX::MsgType_SecurityExchangeDefinitionRequest, BusinessRejectReason_0, sessionID);
	return 0;
}


void CFixEngine::SendOrderCancelReject( FIX::Message &msg, const char *pErrMsg )
{
	if (NULL == pErrMsg) return;
	FIX::Message rsp;
	rsp.setField(FIX::Account(msg.getField(FIX::FIELD::Account).c_str()));
	rsp.setField(FIX::ClOrdID(msg.getField(FIX::FIELD::ClOrdID).c_str()));
	rsp.setField(FIX::OrderID(msg.getField(FIX::FIELD::OrderID).c_str()));
	rsp.setField(FIX::OrdStatus(OrdStatusType_Rejected));
	rsp.setField(FIX::Text(pErrMsg));
	rsp.setField(FIX::CxlRejResponseTo(FIX::CxlRejResponseTo_ORDER_CANCEL_REQUEST));
	rsp.setField(FIX::OrigClOrdID(msg.getField(FIX::FIELD::OrigClOrdID).c_str()));
	
	rsp.getHeader().setField(FIX::MsgSeqNum(1));
	rsp.getHeader().setField(FIX::BeginString(STRING_QUICKFIX_VERSION_42));
	rsp.getHeader().setField(FIX::SenderCompID(m_SenderCompID));
	rsp.getHeader().setField(FIX::TargetCompID(msg.getHeader().getField(FIX::FIELD::SenderCompID).c_str()));
	m_pFixServerSession->SendOrderCancelReject(&rsp);
}


bool CFixEngine::ChkNeedSendLogin(const char* pUser)
{
	IterUserLoginMap iter = m_userLoginMap.find(pUser);
	if (iter == m_userLoginMap.end()) return true;
	if (iter->second->loginSuccess)
	{
		REPORT_EVENT(LOG_CRITICAL, "ChkNeedSendLogin", "user=[%s],已经登录成功了，无需重复登陆", pUser);
		return false;
	}
	else
	{
		REPORT_EVENT(LOG_INFO, "ChkNeedSendLogin", "user=[%s],已经发送了登录消息，暂未收到登录应答，请稍后再试", pUser);
		return false;
	}
	return true;
}

void CFixEngine::Run()
{
	int iSleep = 5000; //ms
	SLEEP(iSleep);
	while(!m_bStop)
	{
		if (m_bEnableFixServer)
		{
			if ((NULL != m_pFixServerSession) && !m_pFixServerSession->IsFixServerStarted())
			{
				m_pFixServerSession->StartServer();
				REPORT_EVENT(LOG_CRITICAL, "CFixEngine", "FixEngine has start...");
			}
		}
		SLEEP(iSleep);
	}
}

void CFixEngine::StartServer()
{
	Create();
}

std::string CFixEngine::GenAppName()
{
	char tmpBuf[64] = {0};
	sprintf(tmpBuf, "%s", APP_NAME);
	return std::string(tmpBuf);
}

inline CUserField *CFixEngine::GetUserInfo( const char * pUser )
{
	CUserMapIter userIter = m_pCUserMap->find(std::string(pUser));
	if (userIter == m_pCUserMap->end())
	{
		return NULL;
	}
	return &(userIter->second);
}

//fix client 发送的合约请求消息
int CFixEngine::OnReqFixSecurityListInfo( FIX::Message msg, FIX::SessionID sessionID )
{
	CQryInstrumentField req;
	memset(&req, 0x00, sizeof(CQryInstrumentField));
	if (msg.isSetField(FIX::FIELD::SecurityExchange))
	{
		req.ExchangeID = msg.getField(FIX::FIELD::SecurityExchange).c_str();
	}

	if (msg.isSetField(FIX::FIELD::Symbol))
	{
		req.ProductID = msg.getField(FIX::FIELD::Symbol).c_str();
	}

	if (msg.isSetField(FIX::FIELD::SecurityID))
	{
		req.InstrumentID = msg.getField(FIX::FIELD::SecurityID).c_str();
	}
	return 0;
}


//发送合约信息
void CFixEngine::SendRspQryInstrument( CInstrumentField* pField, std::string sSecurityReqID )
{
	if (NULL == pField) return;
	
}

bool CFixEngine::InitLoginInfo(const char * pUser, FIX::SessionID & sessionID, bool bLogin)
{
	IterUserLoginMap it = m_userLoginMap.find(pUser);
	if (it == m_userLoginMap.end())
	{
		UserMessage *UserLoginEntity = new UserMessage();
		UserLoginEntity->loginSuccess = false;
		UserLoginEntity->sessionID = m_pFixServerSession->GetSSID(sessionID);
		m_userLoginMap.insert(make_pair(pUser, UserLoginEntity));
		return true;
	}
	else
	{
		it->second->sessionID = m_pFixServerSession->GetSSID(sessionID);
		it->second->loginSuccess = bLogin;
		return true;
	}
	return false;
	//m_userLoginMap;
	
}

DWORD CFixEngine::GetSessionID( const char * pUserID )
{
	if (NULL == pUserID) return 0;
	IterUserLoginMap iter = m_userLoginMap.find(pUserID);
	if ( iter == m_userLoginMap.end() ) 
		return 0;
	else
		return iter->second->sessionID;
}

int CFixEngine::GetReqID( const char * pUser )
{
	if (NULL == pUser) return -1;
	IterUserLoginMap iter = m_userLoginMap.find(pUser);
	if (iter == m_userLoginMap.end())
		return 0;
	else
	return (++iter->second->iReqID);
}

int CFixEngine::GetExecID( const char * pUser )
{
	char tmpBuf[128] = {0};
	if (NULL == pUser) return 0;
	IterUserLoginMap iter = m_userLoginMap.find(pUser);
	if (iter == m_userLoginMap.end())
		return 0;
	else
		return (++iter->second->iExecID);
}

std::string CFixEngine::GetExecID( int reqID )
{
	char tmpBuf[128] = {0};
	//sprintf(tmpBuf, "ExecID_%d",  reqID);
	sprintf(tmpBuf, "%d", reqID);
	return std::string(tmpBuf);
}

std::string CFixEngine::GetExecRefID( int recNum )
{
	char tmpBuf[128] = {0};
	sprintf(tmpBuf, "ExecRefID_%d",  recNum);
	return std::string(tmpBuf);
}

void CFixEngine::GenFixConfFile()
{
	char *pFixConfFile = m_pConf->getConfig("FixServerCfg");
	if (NULL == pFixConfFile)
	{
		REPORT_EVENT(LOG_CRITICAL, "GenFixConfFile", "没有找到配置项FixServerCfg，系统无法启动，退出！！！");
		exit(1);
	}

	char newFile[64] = {0};
	char tmpBuf[128] = {0};
	sprintf(newFile, "%s_%s", pFixConfFile, "bakfile");
	
	char *pConfField = NULL;
	FIX::Settings::Sections::iterator section = m_Settings.m_sections.end();
	//1、Default
	section = m_Settings.m_sections.insert( m_Settings.m_sections.end(), FIX::Dictionary("DEFAULT") );
	pConfField = m_pConf->getConfig("SessionDeftList");
	if (NULL != pConfField)
	{
		std::string sDeflt = std::string(pConfField).substr(1);
		std::vector<std::string> tmpVec = Txtsplit(sDeflt, "}");
		if (tmpVec.size() < 1)
		{
			REPORT_EVENT(LOG_CRITICAL, "GenFixConfFile", "配置项SessionDeftList格式不正确[%s]，系统无法启动，退出！！！", pConfField);
			exit(1);
		}
		sDeflt = tmpVec[0];
		FIX::string_strip(sDeflt);
		tmpVec.clear();
		tmpVec = Txtsplit(sDeflt, ",");
		for (int i=0; i<tmpVec.size(); i++)
		{
			pConfField = NULL;
			memset(tmpBuf, 0x00, sizeof(tmpBuf));
			strncpy(tmpBuf, tmpVec[i].c_str(), sizeof(tmpBuf));
			pConfField = m_pConf->getConfig(tmpBuf);
			if (NULL != pConfField)
			{
				(*section).setString( tmpVec[i], pConfField );
			}
			else
			{
				REPORT_EVENT(LOG_CRITICAL, "GenFixConfFile", "没有找到配置项[%s]，系统无法启动，退出！！！", tmpVec[i].c_str());
				exit(1);
			}
		}
	}
	else
	{
		REPORT_EVENT(LOG_CRITICAL, "GenFixConfFile", "没有找到配置项SessionDeftList，系统无法启动，退出！！！");
		exit(1);
	}

	//2、sessions
	pConfField = m_pConf->getConfig("SessionCfgList");
	if (NULL != pConfField)
	{
		std::string sSCfg = std::string(pConfField).substr(1);
		std::vector<std::string> tmpVec = Txtsplit(sSCfg, "}");
		if (tmpVec.size() < 1)
		{
			REPORT_EVENT(LOG_CRITICAL, "GenFixConfFile", "配置项SessionCfgList格式不正确[%s]，系统无法启动，退出！！！", pConfField);
			exit(1);
		}
		sSCfg = tmpVec[0];
		FIX::string_strip(sSCfg);
		tmpVec.clear();
		tmpVec = Txtsplit(sSCfg, ",");
		//根据user信息，添加session
		for (CUserMapIter uIter=m_pCUserMap->begin(); uIter!=m_pCUserMap->end(); uIter++)
		{
			section = m_Settings.m_sections.insert( m_Settings.m_sections.end(), FIX::Dictionary("SESSION") );
			for (int i=0; i<tmpVec.size(); i++)
			{
				pConfField = NULL;
				memset(tmpBuf, 0x00, sizeof(tmpBuf));
				strncpy(tmpBuf, tmpVec[i].c_str(), sizeof(tmpBuf));
				pConfField = m_pConf->getConfig(tmpBuf);
				if (NULL != pConfField)
				{
					(*section).setString( tmpVec[i], pConfField );
				}
				else
				{
					REPORT_EVENT(LOG_CRITICAL, "GenFixConfFile", "没有找到配置项[%s]，系统无法启动，退出！！！", tmpVec[i].c_str());
					exit(1);
				}
			}
			(*section).setString( "SenderSubID", "QDPFixGateway"/*uIter->second.Password.getValue()*/ );
			(*section).setString( "TargetCompID", uIter->second.UserID.getValue() );
		}
	}
	else
	{
		REPORT_EVENT(LOG_CRITICAL, "GenFixConfFile", "没有找到配置项SessionCfgList，系统无法启动，退出！！！");
		exit(1);
	}

	try{

		std::ofstream outStream(newFile);
		if(outStream.is_open())
		{
			
			//exit(1);
			outStream << m_Settings;
			outStream.close();
		}
		else
		{
			REPORT_EVENT(LOG_CRITICAL, "GenFixConfFile", "打开文件[%s]失败", newFile);
		}

		FIX::SessionSettings sSettings(m_Settings);

		//创建fix server
		m_pFixServerSession = new CFixServerSession(sSettings, m_SenderCompID);
		m_pFixServerSession->RegisterCB(this);
		//使能fixserver
		m_bEnableFixServer = true;
	}
	catch ( std::exception & e )
	{
		std::cout << e.what() << std::endl;
		REPORT_EVENT(LOG_CRITICAL, "error FIX::SocketAcceptor", "REASON=%s！！", e.what());
		//SLEEP(2000);
		exit(1);
	}
}

bool CFixEngine::isComment( const std::string& line )
{
	if( line.size() == 0 )
		return false;
	
	return line[0] == '#';
}

//Float保留iPoint小数
float CFixEngine::FloatFormat(float avgpx, int iPoint)
{
	int iVal = Float2Int(avgpx, iPoint);
	float ret = (float)iVal;
	for (int i=0; i<iPoint; i++)
	{
		ret /= 10;
	}
	return ret;
}

//float转int，保留iPoint
int CFixEngine::Float2Int( float avgpx, int iPoint )
{
	int ret;
	for(int i=0; i<iPoint; i++)
	{
		avgpx *= 10;
	}
	if (avgpx > 0)
	{
		ret = (int)((avgpx*10+5)/10);
	}
	else if (avgpx < 0)
	{
		ret = (int)((avgpx*10-5)/10);
	}
	else
	{
		ret = 0;
	}
	return ret;
}

void CFixEngine::OnSessionConnected(CSession *pSession)
{
	REPORT_EVENT(LOG_CRITICAL, "CFixEngine::OnSessionConnected", "qtrade 与 qfixfront连接成功");
	printf("qtrade 与 qfixfront连接成功\n");
}

void CFixEngine::OnSessionDisconnected(CSession *pSession, int nReason)
{
	REPORT_EVENT(LOG_CRITICAL, "CFixEngine::OnSessionDisconnected", "qtrade 与 qfixfront断链，通知所有client重新登录");
	//通知所有客户端全部断链

	IterUserLoginMap iter = m_userLoginMap.begin();
	for (; iter != m_userLoginMap.end(); iter++)
	{
		iter->second->loginSuccess  = false;
		iter->second->sessionID     = -1;

		//2、登录失败，发送logout消息
		if (NULL != m_pFixServerSession)
		{
			m_pFixServerSession->OnErrLogonRsp(iter->first.c_str(), "FIX GateWay STOP");
		}
	}
}

//返回LME合约日期的格式230117--->2017年01月23日
std::string CFixEngine::GenLmeCodeDate()
{
	time_t t = time(0);
	char tmp[64] = {0};
	char year[5] = {0}; 
	strftime(tmp,sizeof(tmp),"%d%m",localtime(&t));
	strftime(year,sizeof(year),"%Y",localtime(&t));
	std::string sDate=std::string(tmp)+std::string(year).substr(2,2);
	return sDate;
}

int CFixEngine::sendTradeBusiness(CXTPPackage * pXTPPackage)
{
	if (m_pSendFlow == NULL)
	{
		return -1;
	}

	pXTPPackage->MakePackage();
	int rtn = m_pSendFlow->Append(pXTPPackage->Address(), pXTPPackage->Length());
	if (rtn < 0)
	{
		REPORT_EVENT(LOG_INFO, "sendTradeBusiness", "SendFlow->Append fail");
		return -1;
	}
	return 0;
}

inline void CFixEngine::PrepareForward(CXTPPackage *pXTPPackage, DWORD tid, DWORD nSessionID, DWORD nRequestID, DWORD nFrontID)
{
	pXTPPackage->PreparePublish(tid);
	pXTPPackage->SetFrontID(FRONTID);
	pXTPPackage->SetSessionID(nSessionID);
	pXTPPackage->SetRequestID(nRequestID);
}

