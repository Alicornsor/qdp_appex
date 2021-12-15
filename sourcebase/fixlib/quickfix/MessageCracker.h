/* -*- C++ -*- */

/****************************************************************************
** Copyright (c) quickfixengine.org  All rights reserved.
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

#ifndef FIX_MESSAGECRACKER_H
#define FIX_MESSAGECRACKER_H


//#include "fix42/MessageCracker.h"
#include "Values.h"
#include "Session.h"

namespace FIX
{
/** Takes in a generic Message and produces an object that represents
 *  its specific version and message type.
 */
//class MessageCracker: public FIX42::MessageCracker
// 
//{
//public:
//	virtual void onSelfMessage( const Message&, const FIX::SessionID& ){}
//
//  void crack( const Message& message,
//              const SessionID& sessionID )
//  {
//    const FIX::BeginString& beginString = 
//      FIELD_GET_REF( message.getHeader(), BeginString );
//
//    crack( message, sessionID, beginString );
//  }
//
//  void crack( const Message& message,
//              const SessionID& sessionID,
//              const BeginString& beginString )
//  {
//	if ( beginString == BeginString_FIX42 )
//      ((FIX42::MessageCracker&)(*this)).crack((const FIX42::Message&) message, sessionID);
//	else if ( beginString == BeginString_FIXALL )
//		onSelfMessage( message, sessionID );
//  }
//
//  void crack( Message& message,
//              const SessionID& sessionID )
//  {
//    const FIX::BeginString& beginString = 
//      FIELD_GET_REF( message.getHeader(), BeginString );
//
//    crack( message, sessionID, beginString );
//  }
//
//  void crack( Message& message,
//              const SessionID& sessionID,
//              const BeginString& beginString )
//  {
//	 if ( beginString == BeginString_FIX42 )
//      ((FIX42::MessageCracker&)(*this)).crack((const FIX42::Message&) message, sessionID);
//  }
//};
}

#endif //FIX_MESSAGECRACKER_H
