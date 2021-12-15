#include "FixRspClient.h"


//FixRspClient::FixRspClient(CReactor *pReactor, CSelectReactor* pConnReactor)
//:CEventHandler(pReactor)
//{
//}

FixRspClient::FixRspClient(CFixEngine * m_fixEngine)
:m_fixEngine(m_fixEngine)
{
}

FixRspClient::~FixRspClient()
{
}


void FixRspClient::HandleMessage(CXTPPackage * pMessage)
{

	switch (pMessage->GetTid())
	{
	case TID_RspUserLogin:
	{
		OnRspFixUserLogin(pMessage);
	}
	break;
	case TID_RspUserLogout:
	{
		OnRspFixUserLogout(pMessage);
	}
		break;
	case TID_RspOrderInsert:
	{
		OnRspFixOrderInsert(pMessage);
	}
		break;
	case TID_NtfOrder:
	{
		//DWORD SessionID = pMessage->GetSessionID();
		COrderField xtpfield;
		CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&COrderField::m_Describe);
		while (!itor.IsEnd())
		{
			itor.Retrieve(&xtpfield);
			SendRtnOrder(&xtpfield);
			itor.Next();
		}
	}
	break;
	case TID_NtfTrade:
	{
		//DWORD SessionID = pMessage->GetSessionID();
		CTradeField xtpField;
		CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CTradeField::m_Describe);
		while (!itor.IsEnd())
		{
			itor.Retrieve(&xtpField);
			SendRtnTrade(&xtpField);
			itor.Next();
		}
	}
	break;
	case TID_RspOrderAction:
	{
		OnRspFixOrderAction(pMessage);
	}
	break;
	case TID_RspUserPasswordUpdate:
	{
		OnRspFixUserPasswd(pMessage);
	}
	break;
	default:
		break;
	}
}

void FixRspClient::OnResponse(CXTPPackage * pMessage)
{
	//XTP_PACKAGE_DEBUG(pMessage);
	switch(pMessage->GetTid())
	{
	case	TID_RspQryTrade:
	{
		DWORD SessionID = pMessage->GetSessionID();
		CSession2FIXMapIter iter = m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.find(SessionID);
		if (iter == m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.end())
		{
			return;
		}

		CRspInfoField rspInfoField;
		memset(&rspInfoField, 0x00, sizeof(CRspInfoField));
		if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0) return;
		CTradeField xtpField;
		CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CTradeField::m_Describe);
		while (!itor.IsEnd())
		{
			itor.Retrieve(&xtpField);
			OnRspFillOrder(&xtpField, iter->second, &rspInfoField);
			itor.Next();
		}
	}
	break;
	case	TID_RspQryOrder:
	{
		DWORD SessionID = pMessage->GetSessionID();
		CSession2FIXMapIter iter = m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.find(SessionID);
		if (iter == m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.end())
		{
			return;
		}

		CRspInfoField rspInfoField;
		memset(&rspInfoField, 0x00, sizeof(CRspInfoField));
		if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0) return;
		COrderField xtpField;
		CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&COrderField::m_Describe);
		while (!itor.IsEnd())
		{
			itor.Retrieve(&xtpField);
			OnRspOrder(&xtpField, iter->second, &rspInfoField);
			itor.Next();
		}
	}
	break;
	case TID_RspQryInstrument:
		{
			OnRspQryInstrument(pMessage);
		}
		break;
	case TID_RspQryInvestorPosition:
	{
		OnRspFixUserPosition(pMessage);
	}
	break;
	case TID_RspQryUserInvestor:
	{
		OnRspFixAvailableAccount(pMessage);
	}
	break;
	case TID_RspQryInvestorFee:
	{
		OnRspFixFee(pMessage);
	}
	break;
	case TID_RspQryInvestorMargin:
	{
		OnRspFixUserMargin(pMessage);
	}
	break;
	case TID_RspQryInvestorAccount:
	{
		OnRspFixAccountData(pMessage);
	}
	break;
	default:
		break;
	}

}

bool FixRspClient::DispatcherEvent(int nEventID, DWORD dwParam, void * pParam)
{
	//return PostEvent(nEventID, dwParam, pParam);
	return false;
}

//合约查询应答
//void FixRspClient::OnRspQryInstrument( CXTPPackage * pMessage )
//{
//// 	if (NULL == pMessage) return;
//// 	//获取reqID
//// 	int reqID = pMessage->GetRequestID();
//// 	//根据reqID查找对应的SecurityReqID
//// 	CIntStringMapIter iter = m_pReqIDUserOrderLocalIDMap->find(reqID);
//// 	if (iter == m_pReqIDUserOrderLocalIDMap->end())
//// 	{//未找到，则丢弃该消息
//// 		REPORT_EVENT(LOG_CRITICAL, "OnRspQryInstrument", "未找到对应的SecurityReqID，reqID=[%d]", reqID);
//// 		return;
//// 	}
//// 
//// 	/*先处理响应信息*/												
//// 	CRspInfoField rspInfoField;										
//// 	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0) return;
//// 	if (rspInfoField.ErrorID != 0)
//// 	{//查询失败
//// 		REPORT_EVENT(LOG_CRITICAL, "OnRspQryInstrument", "查询合约失败");
//// 		//Send reject message to fix client
//// 		//SendBusinessRejectMessage
//// 		return;
//// 	}
//// 
//// 
//// 
//// 	/*处理业务信息*/								
//// 	CInstrumentField xtpField;										
//// 	CNamedFieldIterator itor =	pMessage->GetNamedFieldIterator(&CInstrumentField::m_Describe);	
//// 	while (!itor.IsEnd())										
//// 	{															
//// 		itor.Retrieve(&xtpField);									
//// 		SendRspQryInstrument(&xtpField, iter->second);
//// 		itor.Next();												
//// 	}
//}

void FixRspClient::OnRspFixUserLogin(CXTPPackage * pMessage)
{
	//printf("%s\n", __FUNCTION__);
	CRspInfoField   rspInfoField;
	CUserLoginField userLoginField;
	memset(&rspInfoField, 0x00, sizeof(CRspInfoField));
	memset(&userLoginField, 0x00, sizeof(CUserLoginField));
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0) return;
	if (XTP_GET_SINGLE_FIELD(pMessage, &userLoginField) <= 0) return;

	IterUserLoginMap it = m_fixEngine->m_userLoginMap.find(userLoginField.UserID.getValue());
	if (it == m_fixEngine->m_userLoginMap.end())
	{
		return;
	}
	

	if (rspInfoField.ErrorID == 0)
	{
		it->second->loginSuccess = true;
		if (NULL == m_fixEngine->m_pFixServerSession) return;

		m_fixEngine->m_pFixServerSession->OnRspLogon(userLoginField.BrokerID.getValue(),
				userLoginField.UserID.getValue(), userLoginField.Password.getValue(), 0);

		REPORT_EVENT(LOG_INFO, "OnRspFixUserLogin", "login success,user=[%s],BrokerID=[%s]",
			userLoginField.UserID.getValue(), userLoginField.BrokerID.getValue());
	}
	else
	{
		delete it->second;
		it->second = NULL;
		m_fixEngine->m_userLoginMap.erase(it);

		////1、先发送一个登出消息给qtrade
		//m_fixEngine->PrepareForward(&m_fixEngine->m_reqPackage, TID_ReqUserLogout, m_fixEngine->GetSessionID(userLoginField.UserID.getValue()), m_fixEngine->GetReqID(userLoginField.UserID.getValue()));
		//CUserLogoutField userLogoutField;
		//memset(&userLogoutField, 0x00, sizeof(CUserLogoutField));
		//userLogoutField.BrokerID = userLoginField.BrokerID;
		//userLogoutField.UserID = userLoginField.UserID;
		//XTP_ADD_FIELD(&m_fixEngine->m_reqPackage, &userLogoutField);
		//m_fixEngine->sendTradeBusiness(&m_fixEngine->m_reqPackage);

		//2、登录失败，发送logout消息
		if (NULL == m_fixEngine->m_pFixServerSession) return;
		m_fixEngine->m_pFixServerSession->OnErrLogonRsp(userLoginField.UserID.getValue(), rspInfoField.ErrorMsg.getValue());
		REPORT_EVENT(LOG_CRITICAL, "OnRspFixUserLogin", "login failed,user=[%s],passwd=[%s],BrokerID=[%s],errCode=[%d],errMsg=[%s]",
			userLoginField.UserID.getValue(), userLoginField.Password.getValue(), userLoginField.BrokerID.getValue(),
			rspInfoField.ErrorID.getValue(), rspInfoField.ErrorMsg.getValue());
	}
}

void FixRspClient::OnRspFixUserLogout(CXTPPackage * pMessage)
{
	CRspInfoField   rspInfoField;
	CUserLogoutField userField;
	memset(&rspInfoField, 0x00, sizeof(CRspInfoField));
	memset(&userField, 0x00, sizeof(CUserLogoutField));
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0) return;
	if (XTP_GET_SINGLE_FIELD(pMessage, &userField) <= 0) return;

	IterUserLoginMap it = m_fixEngine->m_userLoginMap.find(userField.UserID.getValue());
	if (it == m_fixEngine->m_userLoginMap.end())
	{
		return;
	}

	delete it->second;
	it->second = NULL;
	m_fixEngine->m_userLoginMap.erase(it);
	if (rspInfoField.ErrorID == 0)
	{
		REPORT_EVENT(LOG_ERROR, "OnRspFixUserLogout", "client[%s]登出成功", userField.UserID.getValue());
	}
	else
	{
		REPORT_EVENT(LOG_ERROR, "OnRspFixUserLogout", "client[%s]登出失败", userField.UserID.getValue());
	}
	m_fixEngine->m_pFixServerSession->OnErrLogonRsp(userField.UserID.getValue(), rspInfoField.ErrorMsg.getValue());

}

void FixRspClient::OnRspFixOrderInsert(CXTPPackage *pMessage)
{
	//printf("%s\n", __FUNCTION__);
	if (NULL == pMessage) return;

	CRspInfoField rspInfoField;
	CInputOrderField rspField;
	CInputOrderField *pField = &rspField;
	memset(&rspInfoField, 0x00, sizeof(CRspInfoField));
	memset(&rspField, 0x00, sizeof(CInputOrderField));
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0) return;
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspField) <= 0) return;


	IterUserLoginMap it = m_fixEngine->m_userLoginMap.find(pField->UserID.getValue());
	if (it == m_fixEngine->m_userLoginMap.end())
	{
		return;
	}

	FIX::Message msg;
	msg.getHeader().setField(FIX::BeginString(STRING_QUICKFIX_VERSION_42));
	msg.getHeader().setField(FIX::SenderCompID(m_fixEngine->m_SenderCompID));
	msg.getHeader().setField(FIX::TargetCompID(pField->UserID.getValue()));
	if (rspInfoField.ErrorID != 0)
	{
		m_fixEngine->m_pFixServerSession->SendBusinessRspRejectMessage2(&msg, rspInfoField.ErrorID.getValue(), rspInfoField.ErrorMsg.getValue(), FIX::MsgType_NewOrderSingle, BusinessRejectReason_0);
		return;
	}
	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_ExecutionReport));
	SafeSetFixField(FIX::Account, pField->InvestorID);
	SafeSetFixField(FIX::ExecBroker,pField->BrokerID);
	SafeSetFixField(FIX::OrderID, pField->OrderSysID);
	SafeSetFixField(FIX::ClOrdID, pField->UserOrderLocalID);
	SafeSetFixField(FIX::OrderQty, pField->Volume);
	msg.setField(FIX::OrdType(pField->OrderPriceType.getValue()));
	SafeSetFixField(FIX::Price, pField->LimitPrice);
	SafeSetFixField(FIX::SecurityID, pField->InstrumentID);
	msg.setField(FIX::Side((pField->Direction == D_Buy) ? SideType_Buy : SideType_Sell));
	SafeSetFixField(FIX::SecurityExchange, pField->ExchangeID);
	/* SecurityType_CS SecurityType_FUT SecurityType_OPT */
	msg.setField(FIX::SecurityType(SecurityType_FUT));
	msg.setField(FIX::ExecID(m_fixEngine->GetExecID(m_fixEngine->GetExecID(pField->UserID.getValue())).c_str()));
	msg.setField(FIX::TransactTime());

	msg.setField(FIX::ExecType(ExecType_New));
	msg.setField(FIX::ExecTransType(ExecTransType_New));
	msg.setField(FIX::OrdStatus(OrdStatusType_InsertSubmitted));
	m_fixEngine->m_pFixServerSession->SendMsg2FixClient(msg);
	//REPORT_EVENT(LOG_INFO, "OnRspFixOrderInsert", "InvestorID=[%s],OrderSysID=[%s],UserOrderLocalID=[%s]", rspField.InvestorID.getValue(), rspField.OrderSysID.getValue(), rspField.UserOrderLocalID.getValue());



}


void FixRspClient::OnRspFixOrderAction(CXTPPackage * pMessage)
{
	//printf("%s\n", __FUNCTION__);
	if (NULL == pMessage) return;

	CRspInfoField rspInfoField;
	COrderActionField rspField;
	COrderActionField *pField = &rspField;
	memset(&rspInfoField, 0x00, sizeof(CRspInfoField));
	memset(&rspField, 0x00, sizeof(COrderActionField));
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0) return;
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspField) <= 0) return;

	IterUserLoginMap it = m_fixEngine->m_userLoginMap.find(pField->UserID.getValue());
	if (it == m_fixEngine->m_userLoginMap.end())
	{
		return;
	}

	FIX::Message msg;
	msg.getHeader().setField(FIX::BeginString(STRING_QUICKFIX_VERSION_42));
	msg.getHeader().setField(FIX::SenderCompID(m_fixEngine->m_SenderCompID));
	msg.getHeader().setField(FIX::TargetCompID(pField->UserID.getValue()));
	if (rspInfoField.ErrorID != 0)
	{
		m_fixEngine->m_pFixServerSession->SendBusinessRspRejectMessage2(&msg, rspInfoField.ErrorID.getValue(), rspInfoField.ErrorMsg.getValue(), FIX::MsgType_OrderCancelRequest, BusinessRejectReason_0);
		return;
	}
	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_ExecutionReport));
	SafeSetFixField(FIX::Account, pField->InvestorID);
	SafeSetFixField(FIX::ExecBroker, pField->BrokerID);
	SafeSetFixField(FIX::OrderID, pField->OrderSysID);
	SafeSetFixField(FIX::OrigClOrdID, rspField.UserOrderActionLocalID);
	SafeSetFixField(FIX::Price, pField->LimitPrice);
	SafeSetFixField(FIX::SecurityID, pField->InstrumentID);
	SafeSetFixField(FIX::SecurityExchange, pField->ExchangeID);
	msg.setField(FIX::ExecID(m_fixEngine->GetExecID(m_fixEngine->GetExecID(pField->UserID.getValue())).c_str()));
	msg.setField(FIX::TransactTime());

	msg.setField(FIX::ExecType(ExecType_Cancel));
	msg.setField(FIX::ExecTransType(ExecTransType_Cancel));
	msg.setField(FIX::OrdStatus(OrdStatusType_CancelSubmitted));
	m_fixEngine->m_pFixServerSession->SendMsg2FixClient(msg);
	//REPORT_EVENT(LOG_INFO, "OnRspFixOrderAction", "OrderSysID=[%s]", pField->OrderSysID.getValue());
	
}

void FixRspClient::OnRspQryInstrument(CXTPPackage * pMessage)
{
	if (NULL == pMessage) return;
	CSession2FIXMapIter iter = m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.find(pMessage->GetSessionID());
	if (iter == m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.end())
	{
		return;
	}
	CRspInfoField rspInfoField;
	CInstrumentField rspField;
	CInstrumentField *pField = &rspField;
	memset(&rspInfoField, 0x00, sizeof(CRspInfoField));
	memset(&rspField, 0x00, sizeof(CInstrumentField));
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0) return;
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspField) <= 0) return;

	FIX::SessionID tmpFixSession;
	tmpFixSession.fromString(iter->second);
	FIX::Message msg;
	msg.getHeader().setField(tmpFixSession.getBeginString());
	msg.getHeader().setField(tmpFixSession.getSenderCompID());
	msg.getHeader().setField(tmpFixSession.getTargetCompID());
	if (rspInfoField.ErrorID != 0)
	{
		m_fixEngine->m_pFixServerSession->SendBusinessRspRejectMessage(&msg, rspInfoField.ErrorID.getValue(), rspInfoField.ErrorMsg.getValue(), FIX::MsgType_SecurityDefinitionRequest, BusinessRejectReason_0, tmpFixSession);
		return;
	}

	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_SecurityDefinition));
	SafeSetFixField(FIX::SecurityExchange, pField->ExchangeID);
	SafeSetFixField(FIX::Symbol, pField->ProductID);
	SafeSetFixField(FIX::SecurityID, pField->InstrumentID);
	SafeSetFixField(FIX::SymbolRef, pField->ProductName);
	SafeSetFixField(FIX::SecurityRef, pField->InstrumentName);
	SafeSetFixField(FIX::DeliveryYear, pField->DeliveryYear);
	SafeSetFixField(FIX::DeliveryMonth, pField->DeliveryMonth);
	SafeSetFixField(FIX::MaxLimitOrderVolume, pField->MaxLimitOrderVolume);
	SafeSetFixField(FIX::MinLimitOrderVolume, pField->MinLimitOrderVolume);
	SafeSetFixField(FIX::MaxMarketOrderVolume, pField->MaxMarketOrderVolume);
	SafeSetFixField(FIX::MinMarketOrderVolume, pField->MinMarketOrderVolume);
	SafeSetFixField(FIX::VolumeMultiple, pField->VolumeMultiple);
	SafeSetFixField(FIX::PriceTick, pField->PriceTick);
	string tcurrency; tcurrency += pField->Currency.getValue();
	msg.setField(FIX::Currency(tcurrency));
	SafeSetFixField(FIX::LongPosLimit, pField->LongPosLimit);
	SafeSetFixField(FIX::ShortPosLimit, pField->ShortPosLimit);
	SafeSetFixField(FIX::LowerLimitPrice, pField->LowerLimitPrice);
	SafeSetFixField(FIX::UpperLimitPrice, pField->UpperLimitPrice);
	SafeSetFixField(FIX::PreSettlementPrice, pField->PreSettlementPrice);
	SafeSetFixCharField(FIX::SecurityRefStatus, pField->InstrumentStatus);
	SafeSetFixField(FIX::CreateDate, pField->CreateDate);
	SafeSetFixField(FIX::OpenDate, pField->OpenDate);
	SafeSetFixField(FIX::ExpireDate, pField->ExpireDate);
	SafeSetFixField(FIX::StartDelivDate, pField->StartDelivDate);
	SafeSetFixField(FIX::EndDelivDate, pField->EndDelivDate);
	SafeSetFixField(FIX::BasisPrice, pField->BasisPrice);
	SafeSetFixCharField(FIX::IsTrading, pField->IsTrading);
	SafeSetFixField(FIX::UnderlyingInstrID, pField->UnderlyingInstrID);
	SafeSetFixField(FIX::UnderlyingMultiple, pField->UnderlyingMultiple);
	SafeSetFixCharField(FIX::PositionType, pField->PositionType);
	SafeSetFixField(FIX::StrikePrice, pField->StrikePrice);
	SafeSetFixCharField(FIX::OptionsType, pField->OptionsType);
	SafeSetFixCharField(FIX::ProductClass, pField->ProductClass);
	SafeSetFixCharField(FIX::OptionsMode, pField->OptionsMode);

	m_fixEngine->m_pFixServerSession->SendMsg2FixClient(msg, tmpFixSession);
}

void FixRspClient::OnRspFixUserMargin(CXTPPackage * pMessage)
{
	//printf("%s\n", __FUNCTION__);
	if (NULL == pMessage) return;
	CSession2FIXMapIter iter = m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.find(pMessage->GetSessionID());
	if (iter == m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.end())
	{
		return;
	}
	CRspInfoField rspInfoField;
	CInvestorMarginField rspField;
	CInvestorMarginField *pField = &rspField;
	memset(&rspInfoField, 0x00, sizeof(CRspInfoField));
	memset(&rspField, 0x00, sizeof(CInvestorMarginField));
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0) return;
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspField) <= 0) return;

	FIX::SessionID tmpFixSession;
	tmpFixSession.fromString(iter->second);
	FIX::Message msg;
	msg.getHeader().setField(tmpFixSession.getBeginString());
	msg.getHeader().setField(tmpFixSession.getSenderCompID());
	msg.getHeader().setField(tmpFixSession.getTargetCompID());
	if (rspInfoField.ErrorID != 0)
	{
		m_fixEngine->m_pFixServerSession->SendBusinessRspRejectMessage(&msg, rspInfoField.ErrorID.getValue(), rspInfoField.ErrorMsg.getValue(), FIX::MsgType_RequestForMargin, BusinessRejectReason_0, tmpFixSession);
		return;
	}

	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_RequestForMarginAck));
	SafeSetFixField(FIX::ExecBroker, pField->BrokerID);
	SafeSetFixField(FIX::SecurityExchange, pField->ExchangeID);
	SafeSetFixField(FIX::Account, pField->InvestorID);
	SafeSetFixField(FIX::SecurityID, pField->InstrumentID);
	SafeSetFixField(FIX::HedgeFlag, pField->HedgeFlag);
	SafeSetFixField(FIX::LongMarginRate, pField->LongMarginRate);
	SafeSetFixField(FIX::LongMarginAmt, pField->LongMarginRate);
	SafeSetFixField(FIX::ShortMarginRate, pField->ShortMarginRate);
	SafeSetFixField(FIX::ShortMarginAmt, pField->ShortMarginAmt);

	m_fixEngine->m_pFixServerSession->SendMsg2FixClient(msg, tmpFixSession);
}

void FixRspClient::OnRspFixUserPosition(CXTPPackage * pMessage)
{
	//printf("%s\n", __FUNCTION__);
	if (NULL == pMessage) return;
	CSession2FIXMapIter iter = m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.find(pMessage->GetSessionID());
	if (iter == m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.end())
	{
		return;
	}
	CRspInfoField rspInfoField;
	CInvestorPositionField rspField;
	CInvestorPositionField *pField = &rspField;
	memset(&rspInfoField, 0x00, sizeof(CRspInfoField));
	memset(&rspField, 0x00, sizeof(CInvestorPositionField));
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0) return;
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspField) <= 0) return;

	FIX::SessionID tmpFixSession;
	tmpFixSession.fromString(iter->second);
	FIX::Message msg;
	msg.getHeader().setField(tmpFixSession.getBeginString());
	msg.getHeader().setField(tmpFixSession.getSenderCompID());
	msg.getHeader().setField(tmpFixSession.getTargetCompID());
	if (rspInfoField.ErrorID != 0)
	{
		m_fixEngine->m_pFixServerSession->SendBusinessRspRejectMessage(&msg, rspInfoField.ErrorID.getValue(), rspInfoField.ErrorMsg.getValue(), FIX::MsgType_RequestForPosition, BusinessRejectReason_0, tmpFixSession);
		return;
	}

	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_RequestForPositionAck));
	SafeSetFixField(FIX::ExecBroker, pField->BrokerID);
	SafeSetFixField(FIX::SecurityExchange, pField->ExchangeID);
	SafeSetFixField(FIX::Account, pField->InvestorID);
	SafeSetFixField(FIX::ParticipantID, pField->ParticipantID);
	SafeSetFixField(FIX::ClientID, pField->ClientID);
	SafeSetFixField(FIX::SecurityID, pField->InstrumentID);
	msg.setField(FIX::Side((pField->Direction == D_Buy) ? SideType_Buy : SideType_Sell));
	SafeSetFixCharField(FIX::HedgeFlag, pField->HedgeFlag);
	SafeSetFixField(FIX::UsedMargin, pField->UsedMargin);
	SafeSetFixField(FIX::TotalPosition, pField->Position);
	SafeSetFixField(FIX::PositionCost, pField->PositionCost);
	SafeSetFixField(FIX::YdPosition, pField->YdPosition);
	SafeSetFixField(FIX::YdPositionCost, pField->YdPositionCost);
	SafeSetFixField(FIX::FrozenMargin, pField->FrozenMargin);
	SafeSetFixField(FIX::FrozenPosition, pField->FrozenPosition);
	SafeSetFixField(FIX::FrozenClosing, pField->FrozenClosing);
	SafeSetFixField(FIX::FrozenPremium, pField->FrozenPremium);
	SafeSetFixField(FIX::LastTradeID, pField->LastTradeID);
	SafeSetFixField(FIX::LastOrderLocalID, pField->LastOrderLocalID);
	SafeSetFixField(FIX::Currency, pField->Currency);
	SafeSetFixField(FIX::PositionProfit, pField->PositionProfit);
	SafeSetFixField(FIX::TodayPosition, pField->TodayPosition);
	SafeSetFixField(FIX::FrozenTodayClosing, pField->FrozenTodayClosing);
	
	m_fixEngine->m_pFixServerSession->SendMsg2FixClient(msg, tmpFixSession);

}

void FixRspClient::OnRspFixAccountData(CXTPPackage * pMessage)
{
	//printf("%s\n", __FUNCTION__);
	if (NULL == pMessage) return;
	CSession2FIXMapIter iter = m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.find(pMessage->GetSessionID());
	if (iter == m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.end())
	{
		return;
	}
	CRspInfoField rspInfoField;
	CInvestorAccountField rspField;
	CInvestorAccountField *pField = &rspField;
	memset(&rspInfoField, 0x00, sizeof(CRspInfoField));
	memset(&rspField, 0x00, sizeof(CInvestorAccountField));
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0) return;
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspField) <= 0) return;

	FIX::SessionID tmpFixSession;
	tmpFixSession.fromString(iter->second);
	FIX::Message msg;
	msg.getHeader().setField(tmpFixSession.getBeginString());
	msg.getHeader().setField(tmpFixSession.getSenderCompID());
	msg.getHeader().setField(tmpFixSession.getTargetCompID());
	if (rspInfoField.ErrorID != 0)
	{
		m_fixEngine->m_pFixServerSession->SendBusinessRspRejectMessage(&msg, rspInfoField.ErrorID.getValue(), rspInfoField.ErrorMsg.getValue(), FIX::MsgType_AccountDataRequest, BusinessRejectReason_0, tmpFixSession);
		return;
	}

	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_AccountDataRequesAck));
	SafeSetFixField(FIX::ExecBroker, pField->BrokerID);
	SafeSetFixField(FIX::Account, pField->InvestorID);
	SafeSetFixField(FIX::AccountName, pField->AccountID);
	SafeSetFixField(FIX::PreBalance, pField->PreBalance);
	SafeSetFixField(FIX::PreAvailable, pField->PreAvailable);
	SafeSetFixField(FIX::Deposit, pField->Deposit);
	SafeSetFixField(FIX::Withdraw, pField->Withdraw);
	SafeSetFixField(FIX::Margin, pField->Margin);
	SafeSetFixField(FIX::Premium, pField->Premium);
	SafeSetFixField(FIX::Fee, pField->Fee);
	SafeSetFixField(FIX::FrozenMargin, pField->FrozenMargin);
	SafeSetFixField(FIX::FrozenPremium, pField->FrozenPremium);
	SafeSetFixField(FIX::FrozenFee, pField->FrozenFee);
	SafeSetFixField(FIX::CloseProfit, pField->CloseProfit);
	SafeSetFixField(FIX::PositionProfit, pField->PositionProfit);
	SafeSetFixField(FIX::Available, pField->Available);
	SafeSetFixField(FIX::Balance, pField->Balance);
	SafeSetFixField(FIX::LongMargin, pField->LongMargin);
	SafeSetFixField(FIX::ShortMargin, pField->ShortMargin);
	SafeSetFixField(FIX::LongFrozenMargin, pField->LongFrozenMargin);
	SafeSetFixField(FIX::ShortFrozenMargin, pField->ShortFrozenMargin);
	SafeSetFixField(FIX::DynamicRights, pField->DynamicRights);
	SafeSetFixField(FIX::Risk, pField->Risk);
	SafeSetFixField(FIX::OtherFee, pField->OtherFee);
	SafeSetFixField(FIX::Mortgage, pField->Mortgage);
	SafeSetFixField(FIX::Currency, pField->Currency);

	m_fixEngine->m_pFixServerSession->SendMsg2FixClient(msg, tmpFixSession);

}

void FixRspClient::OnRspFixFee(CXTPPackage * pMessage)
{
	//printf("%s\n", __FUNCTION__);
	if (NULL == pMessage) return;
	CSession2FIXMapIter iter = m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.find(pMessage->GetSessionID());
	if (iter == m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.end())
	{
		return;
	}
	CRspInfoField rspInfoField;
	CInvestorFeeField rspField;
	CInvestorFeeField *pField = &rspField;
	memset(&rspInfoField, 0x00, sizeof(CRspInfoField));
	memset(&rspField, 0x00, sizeof(CInvestorFeeField));
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0) return;
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspField) <= 0) return;

	FIX::SessionID tmpFixSession;
	tmpFixSession.fromString(iter->second);
	FIX::Message msg;
	msg.getHeader().setField(tmpFixSession.getBeginString());
	msg.getHeader().setField(tmpFixSession.getSenderCompID());
	msg.getHeader().setField(tmpFixSession.getTargetCompID());
	if (rspInfoField.ErrorID != 0)
	{
		m_fixEngine->m_pFixServerSession->SendBusinessRspRejectMessage(&msg, rspInfoField.ErrorID.getValue(), rspInfoField.ErrorMsg.getValue(), FIX::MsgType_RequestForFee, BusinessRejectReason_0, tmpFixSession);
		return;
	}

	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_RequestForFeeAck));
	SafeSetFixField(FIX::ExecBroker, pField->BrokerID);
	SafeSetFixField(FIX::SecurityExchange, pField->ExchangeID);
	SafeSetFixField(FIX::Account, pField->InvestorID);
	SafeSetFixField(FIX::SecurityID, pField->InstrumentID);
	SafeSetFixCharField(FIX::HedgeFlag, pField->HedgeFlag);
	SafeSetFixField(FIX::OpenFeeRate, pField->OpenFeeRate);
	SafeSetFixField(FIX::OpenFeeAmt, pField->OpenFeeAmt);
	SafeSetFixField(FIX::OffsetFeeRate, pField->OffsetFeeRate);
	SafeSetFixField(FIX::OffsetFeeAmt, pField->OffsetFeeAmt);
	SafeSetFixField(FIX::OTFeeRate, pField->OTFeeRate);
	SafeSetFixField(FIX::OTFeeAmt, pField->OTFeeAmt);
	m_fixEngine->m_pFixServerSession->SendMsg2FixClient(msg, tmpFixSession);


}

void FixRspClient::OnRspFillOrder(CTradeField * pField, string& fixsession, CRspInfoField* rspInfoField)
{

	FIX::SessionID tmpFixSession;
	tmpFixSession.fromString(fixsession);
	FIX::Message msg;
	msg.getHeader().setField(tmpFixSession.getBeginString());
	msg.getHeader().setField(tmpFixSession.getSenderCompID());
	msg.getHeader().setField(tmpFixSession.getTargetCompID());
	if (rspInfoField->ErrorID != 0)
	{
		m_fixEngine->m_pFixServerSession->SendBusinessRspRejectMessage(&msg, rspInfoField->ErrorID.getValue(), rspInfoField->ErrorMsg.getValue(), FIX::MsgType_FillOrderListRequest, BusinessRejectReason_0, tmpFixSession);
		return;
	}
	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_FillOrderList));

	SafeSetFixField(FIX::Account, pField->InvestorID);
	SafeSetFixField(FIX::ExecBroker, pField->BrokerID);
	SafeSetFixField(FIX::SecurityExchange, pField->ExchangeID);
	SafeSetFixField(FIX::OrderID, pField->OrderSysID);
	SafeSetFixField(FIX::ClOrdID, pField->UserOrderLocalID);
	SafeSetFixField(FIX::SecurityID, pField->InstrumentID);
	SafeSetFixField(FIX::ClOrdID, pField->UserOrderLocalID);
	msg.setField(FIX::Side((pField->Direction == D_Buy) ? SideType_Buy : SideType_Sell));
	SafeSetFixCharField(FIX::HedgeFlag, pField->HedgeFlag);
	SafeSetFixField(FIX::LastPx, pField->TradePrice);
	SafeSetFixField(FIX::LastShares, pField->TradeVolume);
	SafeSetFixField(FIX::SeatID, pField->SeatID);
	SafeSetFixField(FIX::ClientID, pField->ClientID);
	SafeSetFixField(FIX::TradeDate, pField->TradingDay);
	SafeSetFixField(FIX::TransactTime, pField->TradeTime);
	SafeSetFixField(FIX::TradeID, pField->TradeID);
	if (pField->TradeType == TT_Combination)
	{
		msg.setField(FIX::MultiLegReportingType(FIX::MultiLegReportingType_INDIVIDUAL_LEG_OF_A_MULTI_LEG_SECURITY));
	}

	m_fixEngine->m_pFixServerSession->SendMsg2FixClient(msg, tmpFixSession);
}

void FixRspClient::OnRspOrder(COrderField * pField, string & fixsession, CRspInfoField * rspInfoField)
{
	/*LARGE_INTEGER Freq;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&start);*/

	/*QueryPerformanceCounter(&end);
	printf("\nuse us=[%d]\n", (end.QuadPart - start.QuadPart) * 1000000 / Freq.QuadPart);*/

	FIX::SessionID tmpFixSession;
	tmpFixSession.fromString(fixsession);
	FIX::Message msg;
	msg.getHeader().setField(tmpFixSession.getBeginString());
	msg.getHeader().setField(tmpFixSession.getSenderCompID());
	msg.getHeader().setField(tmpFixSession.getTargetCompID());
	if (rspInfoField->ErrorID != 0)
	{
		m_fixEngine->m_pFixServerSession->SendBusinessRspRejectMessage(&msg, rspInfoField->ErrorID.getValue(), rspInfoField->ErrorMsg.getValue(), FIX::MsgType_FillOrderListRequest, BusinessRejectReason_0, tmpFixSession);
		return;
	}
	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_OrderList));

	SafeSetFixField(FIX::Account, pField->InvestorID);
	SafeSetFixField(FIX::ExecBroker, pField->BrokerID);
	SafeSetFixField(FIX::OrderID, pField->OrderSysID);
	SafeSetFixField(FIX::OrderQty, pField->Volume);
	SafeSetFixCharField(FIX::OrdType, pField->OrderPriceType);
	SafeSetFixField(FIX::Price, pField->LimitPrice);
	SafeSetFixCharField(FIX::HedgeFlag, pField->HedgeFlag);
	SafeSetFixCharField(FIX::TimeInForce, pField->TimeCondition);
	SafeSetFixField(FIX::ExpireDate, pField->GTDDate);
	SafeSetFixField(FIX::SecurityID, pField->InstrumentID);
	SafeSetFixField(FIX::SeatID, pField->SeatID);
	SafeSetFixField(FIX::ClientID, pField->ClientID);
	msg.setField(FIX::Side((pField->Direction == D_Buy) ? SideType_Buy : SideType_Sell));
	SafeSetFixField(FIX::SecurityExchange, pField->ExchangeID);
	SafeSetFixField(FIX::TradeDate, pField->TradingDay);
	SafeSetFixField(FIX::OrderInsertTime, pField->InsertTime);
	SafeSetFixField(FIX::CancelAccountID, pField->CancelUserID);
	SafeSetFixField(FIX::OrderCancelTime, pField->CancelTime);
	SafeSetFixField(FIX::ClOrdID, pField->UserOrderLocalID);
	
	m_fixEngine->m_pFixServerSession->SendMsg2FixClient(msg, tmpFixSession);
}

void FixRspClient::OnRspFixOrderMassStatus(CXTPPackage * pMessage)
{    
}

void FixRspClient::OnRspFixUserPasswd(CXTPPackage * pMessage)
{
	//printf("%s\n", __FUNCTION__);
	if (NULL == pMessage) return;

	CRspInfoField rspInfoField;
	CUserPasswordUpdateField rspField;
	CUserPasswordUpdateField *pField = &rspField;
	memset(&rspInfoField, 0x00, sizeof(CRspInfoField));
	memset(&rspField, 0x00, sizeof(CUserPasswordUpdateField));
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0) return;
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspField) <= 0) return;

	IterUserLoginMap it = m_fixEngine->m_userLoginMap.find(pField->UserID.getValue());
	if (it == m_fixEngine->m_userLoginMap.end())
	{
		return;
	}

	FIX::Message msg;
	msg.getHeader().setField(FIX::BeginString(STRING_QUICKFIX_VERSION_42));
	msg.getHeader().setField(FIX::SenderCompID(m_fixEngine->m_SenderCompID));
	msg.getHeader().setField(FIX::TargetCompID(pField->UserID.getValue()));
	if (rspInfoField.ErrorID != 0)
	{
		m_fixEngine->m_pFixServerSession->SendBusinessRspRejectMessage2(&msg, rspInfoField.ErrorID.getValue(), rspInfoField.ErrorMsg.getValue(), FIX::MsgType_UserRequest, BusinessRejectReason_0);
		return;
	}

	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_UserResponse));
	SafeSetFixField(FIX::ExecBroker, pField->BrokerID);
	SafeSetFixField(FIX::Password, pField->OldPassword);
	SafeSetFixField(FIX::NewPassword, pField->NewPassword);
	msg.setField(FIX::UserStatusText("Update Passwd Success"));
	REPORT_EVENT(LOG_CRITICAL, "OnRspFixUserPasswd", "success user=[%s],newpasswd=[%s]",pField->UserID.getValue(), pField->NewPassword.getValue());
	
	m_fixEngine->m_pFixServerSession->SendMsg2FixClient(msg);

}

void FixRspClient::OnRspFixAvailableAccount(CXTPPackage * pMessage)
{
	//printf("%s\n", __FUNCTION__);
	if (NULL == pMessage) return;
	CSession2FIXMapIter iter = m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.find(pMessage->GetSessionID());
	if (iter == m_fixEngine->m_pFixServerSession->m_CSession2FIXMap.end())
	{
		return;
	}
	CRspInfoField rspInfoField;
	CUserInvestorField rspField;
	CUserInvestorField *pField = &rspField;
	memset(&rspInfoField, 0x00, sizeof(CRspInfoField));
	memset(&rspField, 0x00, sizeof(CUserInvestorField));
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0) return;
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspField) <= 0) return;


	FIX::SessionID tmpFixSession;
	tmpFixSession.fromString(iter->second);
	FIX::Message msg;
	msg.getHeader().setField(tmpFixSession.getBeginString());
	msg.getHeader().setField(tmpFixSession.getSenderCompID());
	msg.getHeader().setField(tmpFixSession.getTargetCompID());
	if (rspInfoField.ErrorID != 0)
	{
		m_fixEngine->m_pFixServerSession->SendBusinessRspRejectMessage(&msg, rspInfoField.ErrorID.getValue(), rspInfoField.ErrorMsg.getValue(), FIX::MsgType_AvailableAccountRequest, BusinessRejectReason_0, tmpFixSession);
		return;
	}

	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_AvailableAccountRequestAck));
	SafeSetFixField(FIX::ExecBroker, pField->BrokerID);
	SafeSetFixField(FIX::Account, pField->InvestorID);
	m_fixEngine->m_pFixServerSession->SendMsg2FixClient(msg, tmpFixSession);

}



//发送成交信息
void FixRspClient::SendRtnTrade(CTradeField* pField)
{
	IterUserLoginMap it = m_fixEngine->m_userLoginMap.find(pField->UserID.getValue());
	if (it == m_fixEngine->m_userLoginMap.end())
	{
		return;
	}

	FIX::Message msg;
	msg.getHeader().setField(FIX::BeginString(STRING_QUICKFIX_VERSION_42));
	msg.getHeader().setField(FIX::SenderCompID(m_fixEngine->m_SenderCompID));
	msg.getHeader().setField(FIX::TargetCompID(pField->UserID.getValue()));
	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_ExecutionReport));

	SafeSetFixField(FIX::Account, pField->InvestorID);
	SafeSetFixField(FIX::ExecBroker, pField->BrokerID);
	SafeSetFixField(FIX::SecurityExchange, pField->ExchangeID);
	SafeSetFixField(FIX::OrderID, pField->OrderSysID);
	SafeSetFixField(FIX::ClOrdID, pField->UserOrderLocalID);
	SafeSetFixField(FIX::SecurityID, pField->InstrumentID);
	SafeSetFixField(FIX::ClOrdID, pField->UserOrderLocalID);
	msg.setField(FIX::Side((pField->Direction == D_Buy) ? SideType_Buy : SideType_Sell));
	SafeSetFixCharField(FIX::HedgeFlag, pField->HedgeFlag);
	SafeSetFixField(FIX::LastPx, pField->TradePrice);
	SafeSetFixField(FIX::LastShares, pField->TradeVolume);
	SafeSetFixField(FIX::SeatID, pField->SeatID);
	SafeSetFixField(FIX::ClientID, pField->ClientID);
	SafeSetFixField(FIX::TradeDate, pField->TradingDay);
	SafeSetFixField(FIX::TransactTime, pField->TradeTime);
	SafeSetFixField(FIX::TradeID, pField->TradeID);

	msg.setField(FIX::ExecID(m_fixEngine->GetExecID(m_fixEngine->GetExecID(pField->UserID.getValue())).c_str()));
	msg.setField(FIX::ExecType(ExecType_New));
	msg.setField(FIX::ExecTransType(ExecTransType_New));
	msg.setField(FIX::OrdStatus(OrdStatusType_New));

	if (pField->TradeType == TT_Combination)
	{
		msg.setField(FIX::MultiLegReportingType(FIX::MultiLegReportingType_INDIVIDUAL_LEG_OF_A_MULTI_LEG_SECURITY));
	}

	REPORT_EVENT(LOG_INFO, "SendRtnTrade", "success OrderSysID=[%s],TradeID=[%s]", pField->OrderSysID.getValue(), pField->TradeID.getValue());
	m_fixEngine->m_pFixServerSession->SendMsg2FixClient(msg);
	
	
}

void FixRspClient::SendRtnOrder(COrderField * pField)
{
	//printf("%s\n", __FUNCTION__);

	IterUserLoginMap it = m_fixEngine->m_userLoginMap.find(pField->UserID.getValue());
	if (it == m_fixEngine->m_userLoginMap.end())
	{
		return;
	}

	FIX::Message msg;
	msg.getHeader().setField(FIX::BeginString(STRING_QUICKFIX_VERSION_42));
	msg.getHeader().setField(FIX::SenderCompID(m_fixEngine->m_SenderCompID));
	msg.getHeader().setField(FIX::TargetCompID(pField->UserID.getValue()));
	msg.getHeader().setField(FIX::MsgType(FIX::MsgType_ExecutionReport));

	SafeSetFixField(FIX::Account, pField->InvestorID);
	SafeSetFixField(FIX::ExecBroker, pField->BrokerID);
	SafeSetFixField(FIX::OrderID, pField->OrderSysID);
	SafeSetFixField(FIX::OrderQty, pField->Volume);
	SafeSetFixCharField(FIX::OrdType, pField->OrderPriceType);
	SafeSetFixField(FIX::Price, pField->LimitPrice);
	SafeSetFixCharField(FIX::HedgeFlag, pField->HedgeFlag);
	SafeSetFixCharField(FIX::TimeInForce, pField->TimeCondition);
	SafeSetFixField(FIX::ExpireDate, pField->GTDDate);
	SafeSetFixField(FIX::SecurityID, pField->InstrumentID);
	SafeSetFixField(FIX::SeatID, pField->SeatID);
	SafeSetFixField(FIX::ClientID, pField->ClientID);
	msg.setField(FIX::Side((pField->Direction == D_Buy) ? SideType_Buy : SideType_Sell));
	SafeSetFixField(FIX::SecurityExchange, pField->ExchangeID);
	msg.setField(FIX::SecurityType(SecurityType_FUT));
	SafeSetFixField(FIX::TradeDate, pField->TradingDay);
	SafeSetFixField(FIX::OrderInsertTime, pField->InsertTime);
	SafeSetFixField(FIX::CancelAccountID, pField->CancelUserID);
	SafeSetFixField(FIX::OrderCancelTime, pField->CancelTime);
	//SafeSetFixField(FIX::ClOrdID, pField->UserOrderLocalID);

	 
	msg.setField(FIX::ExecID(m_fixEngine->GetExecID(m_fixEngine->GetExecID(pField->UserID.getValue())).c_str()));

	
	if (pField->OrderStatus == OS_Canceled)
	{
		SafeSetFixField(FIX::OrigClOrdID, pField->UserOrderLocalID);
		msg.setField(FIX::ExecType(ExecType_Cancel));
		msg.setField(FIX::ExecTransType(ExecTransType_Cancel));
		msg.setField(FIX::OrdStatus(OrdStatusType_Cancel));
	}
	else if (pField->OrderStatus == OS_AllTraded)
	{
		SafeSetFixField(FIX::LeavesQty, pField->VolumeRemain);
		SafeSetFixField(FIX::CumQty, pField->VolumeTraded);
		int vrest = pField->VolumeRemain.getValue();
		int vtrade = pField->VolumeTraded.getValue();
		double Px = pField->LimitPrice.getValue() * vtrade / (vtrade + vrest);
		msg.setField(FIX::AvgPx(Px));

		SafeSetFixField(FIX::ClOrdID, pField->UserOrderLocalID);
		msg.setField(FIX::ExecType(ExecType_Fill));
		msg.setField(FIX::ExecTransType(ExecTransType_Correct));
		msg.setField(FIX::OrdStatus(OrdStatusType_Fill));
	}
	else if (pField->OrderStatus == OS_PartTradedQueueing
		|| pField->OrderStatus == OS_PartTradedNotQueueing)
	{
		SafeSetFixField(FIX::LeavesQty, pField->VolumeRemain);
		SafeSetFixField(FIX::CumQty, pField->VolumeTraded);
		int vrest = pField->VolumeRemain.getValue();
		int vtrade = pField->VolumeTraded.getValue();
		double Px = pField->LimitPrice.getValue() * vtrade / (vtrade + vrest);
		msg.setField(FIX::AvgPx(Px));

		SafeSetFixField(FIX::ClOrdID, pField->UserOrderLocalID);
		msg.setField(FIX::ExecType(ExecType_Partial_Fill));
		msg.setField(FIX::ExecTransType(ExecTransType_Correct));
		msg.setField(FIX::OrdStatus(OrdStatusType_Partial_Fill));
	}
	else
	{
		SafeSetFixField(FIX::ClOrdID, pField->UserOrderLocalID);
		msg.setField(FIX::ExecType(ExecType_Suspended));
		msg.setField(FIX::ExecTransType(ExecTransType_Status));
		msg.setField(FIX::OrdStatus(OrdStatusType_Suspended));
	}

	if (NULL != m_fixEngine->m_pFixServerSession)
	{
		REPORT_EVENT(LOG_INFO, "SendRtnOrder", "success OrderSysID=[%s],UserOrderLocalID=[%s]",
			pField->OrderSysID.getValue(), pField->UserOrderLocalID.getValue());
		m_fixEngine->m_pFixServerSession->SendMsg2FixClient(msg);
		
	}
	

}



