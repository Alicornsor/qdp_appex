/****************************************************************************
** Copyright (c) 2001-2014
**
** This file is part of the QuickFIX FIX Engine
**
** This file may be distributed under the terms of the quickfixengine.org
** license as defined by quickfixengine.org and appearing in the file
** LICENSE included in the packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.quickfixengine.org/LICENSE for licensing information.
**
** Contact ask@quickfixengine.org if any conditions of this licensing are
** not clear to you.
**
****************************************************************************/

#ifndef FIX_WAP_INITIATOR_H
#define FIX_WAP_INITIATOR_H

#include <queue>
#include <set>
#include <map>
#include <string>

#include "quickfix/Session.h"
#include "FixStructDefs.h"
#include "quickfix/Message.h"
#include "quickfix/Application.h"
//#include "quickfix/MessageCracker.h"

namespace FIX
{

class CFixApplicationCB
{
public:
	virtual void HandleMessage( FIX::IntFIXMsgType type, FIX::Message msg, FIX::SessionID sessionID) = 0;
	virtual void HandleFixMessage(const std::string &type, FIX::Message msg, FIX::SessionID sessionID) = 0;
};

class CFixApplication:
      public FIX::Application/*,
      public FIX::MessageCracker*/
{
public:
	CFixApplication(){}
	CFixApplication(CFixApplicationCB *pCFixApplicationCB):m_pCFixApplicationCB(pCFixApplicationCB){}
	~CFixApplication(){}
	void RegisterCB(CFixApplicationCB *pCFixApplicationCB)
	{
		m_pCFixApplicationCB = pCFixApplicationCB;
	}

private:
	//APPLICATION
	void onCreate( const FIX::SessionID& );
	void onLogon( const Message&logon, const FIX::SessionID& sessionID );
	void onLogout( const Message&logout, const FIX::SessionID& sessionID );
	void toAdmin( FIX::Message&, const FIX::SessionID& ) {}
	void toApp( FIX::Message&, const FIX::SessionID& )throw( FIX::DoNotSend );
	void fromAdmin( const FIX::Message&, const FIX::SessionID& )
		throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) {}
	void fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
		throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType );
	void fromAppSLC(const int& , const std::string& );
	void onLogonSLC( const SessionID& );
	void onEvent( const std::string& );
	
// 	void onMessage( const FIX42::BusinessMessageReject&, const FIX::SessionID& ){}
// 	void onMessage( const FIX42::ExecutionReport&, const FIX::SessionID& ){}
// 	void onMessage( const FIX42::SecurityDefinition&, const FIX::SessionID& ){}
// 	void onMessage( const FIX42::OrderCancelReject&, const FIX::SessionID& ){}
// 	void onMessage( const FIX42::RequestForPositionsAck&, const FIX::SessionID& ){}
// 	void onMessage( const FIX42::PositionReport&, const FIX::SessionID& ){}
// 	void onMessage( const FIX42::AccountDataReport&, const FIX::SessionID& ){}
// 	void onMessage( const FIX42::MarketDataSnapshotFullRefresh&, const FIX::SessionID& );
// 	void onMessage( const FIX42::MarketDataRequestReject&, const FIX::SessionID& );
// 	void onMessage( const FIX42::MarketDataIncrementalRefresh&, const FIX::SessionID& );
// //    void onMessage( const FIX42::AuthorizedAccountsReport&, const FIX::SessionID& );
//     void onMessage( const FIX42::AllowedMarketDataReport&, const FIX::SessionID& );
//     void onMessage( const FIX42::AllowedFeatureReport&, const FIX::SessionID& );
//     void onMessage( const FIX42::OrderMassStatusRequestAck&, const FIX::SessionID& );
//     void onMessage( const FIX42::CollateralReport&, const FIX::SessionID& );
// //    void onMessage( const FIX42::AccountRiskParametersReport&, const FIX::SessionID& );
// //    void onMessage( const FIX42::UserResponse&, const FIX::SessionID& );
// //    void onMessage( const FIX42::FCMCurrencyRateReport&, const FIX::SessionID& );
// 	void onMessage( const FIX42::SecurityStatus&, const FIX::SessionID& );
// 	void onMessage( const FIX42::GatewayStatus&, const FIX::SessionID& );
	void onSelfMessage( const Message&, const FIX::SessionID& ){}
 	IntFIXMsgType GetMgsIntType( std::string sMsgType );

private:
	CFixApplicationCB *m_pCFixApplicationCB;

};

}
#endif

