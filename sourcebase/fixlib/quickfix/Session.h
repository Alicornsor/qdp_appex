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

#ifndef FIX_SESSION_H
#define FIX_SESSION_H

#ifdef _MSC_VER
#pragma warning( disable : 4503 4355 4786 4290 )
#endif

#include "SessionState.h"
#include "TimeRange.h"
#include "SessionID.h"
#include "Responder.h"
#include "Fields.h"
#include "DataDictionaryProvider.h"
#include "Application.h"
#include "Mutex.h"
#include "Log.h"
#include <utility>
#include <map>
#include <queue>

namespace FIX
{
/// Maintains the state and implements the logic of a %FIX %session.
class Session
{
public:
  Session( Application&, MessageStoreFactory&,
           const SessionID&,
           const DataDictionaryProvider&,
           const TimeRange&,
           int heartBtInt, LogFactory* pLogFactory, LogFactory* pFileLogFactory=NULL );
  ~Session();
  /*** SIR XXXXX BEGIN ***/
  void setLogLevel( int level )
  {
		m_state.setLogLevel(level);
  }
  void setFileLog( const std::string& path ) 
  {
	  m_state.setFileLog( new FileLog(path) );
  }
/*** SIR XXXXX END ***/
	  const std::string& getPassword()
	  { return m_sPassword; }
  void setPassword( const std::string& str	)
	  { m_sPassword = str; } 
  
	 const std::string& getInvestorID()
	{ return m_sInvestorID; }
	void setInvestorID( const std::string& str	)
	  { m_sInvestorID = str; } 
  
	const std::string& getBrokerID()
	{ return m_sBrokerID; }
	void setBrokerID( const std::string& str  )
	  { m_sBrokerID = str; }

  void logon() 
  { m_state.enabled( true ); m_state.logoutReason( "" ); }
  void logout( const std::string& reason = "" ) 
  { m_state.enabled( false ); m_state.logoutReason( reason ); }
  bool isEnabled() 
  { return m_state.enabled(); }

  bool sentLogon() { return m_state.sentLogon(); }
  bool sentLogout() { return m_state.sentLogout(); }
  bool receivedLogon() { return m_state.receivedLogon(); }
  bool isLoggedOn() { return receivedLogon() && sentLogon(); }
  void SetAutoSendLogon(bool a);
  void reset() throw( IOException ) 
  { generateLogout(); disconnect(); m_state.reset(); }
  void refresh() throw( IOException )
  { m_state.refresh(); }
  void setNextSenderMsgSeqNum( int num ) throw( IOException )
  { m_state.setNextSenderMsgSeqNum( num ); }
  void setNextTargetMsgSeqNum( int num ) throw( IOException )
  { m_state.setNextTargetMsgSeqNum( num ); }

  const SessionID& getSessionID() const
  { return m_sessionID; }
  void setDataDictionaryProvider( const DataDictionaryProvider& dataDictionaryProvider )
  { m_dataDictionaryProvider = dataDictionaryProvider; }
  const DataDictionaryProvider& getDataDictionaryProvider() const
  { return m_dataDictionaryProvider; }

  static bool sendToTarget( Message& message,
                            const std::string& qualifier = "" )
  throw( SessionNotFound );
  static bool sendToTarget( Message& message, const SessionID& sessionID )
  throw( SessionNotFound );
  static bool sendToTarget( Message&,
                            const SenderCompID& senderCompID,
                            const TargetCompID& targetCompID,
                            const std::string& qualifier = "" )
  throw( SessionNotFound );
  static bool sendToTarget( Message& message,
                            const std::string& senderCompID,
                            const std::string& targetCompID,
                            const std::string& qualifier = "" )
  throw( SessionNotFound );

  static std::set<SessionID> getSessions();
  static bool doesSessionExist( const SessionID& );
  static Session* lookupSession( const SessionID& );
  static Session* lookupSession( const std::string&, bool reverse = false );
  static bool isSessionRegistered( const SessionID& );
  static Session* registerSession( const SessionID& );
  static void unregisterSession( const SessionID& );

  static int numSessions();
  void mindApplication( char eventType, int begin, int end );
  bool isSessionTime(const DateTime& time)
    { 
      if (!m_bNeedChkTime) return true;
      return m_sessionTime.isInRange(time); 
	}
  bool isLogonTime(const DateTime& time)
    { 
		if (!m_bNeedChkTime) return true;
		return m_logonTime.isInRange(time); 
	}
  bool isInitiator()
    { return m_state.initiate(); }
  bool isAcceptor()
    { return !m_state.initiate(); }

  const TimeRange& getLogonTime()
    { return m_logonTime; }
  void setLogonTime( const TimeRange& value )
    { m_logonTime = value; }

  const std::string& getSenderDefaultApplVerID()
    { return m_senderDefaultApplVerID; }
  void setSenderDefaultApplVerID( const std::string& senderDefaultApplVerID )
    { m_senderDefaultApplVerID = senderDefaultApplVerID; }

  const std::string& getTargetDefaultApplVerID()
    { return m_targetDefaultApplVerID; }
  void setTargetDefaultApplVerID( const std::string& targetDefaultApplVerID )
    { m_targetDefaultApplVerID = targetDefaultApplVerID; }

  bool getSendRedundantResendRequests()
    { return m_sendRedundantResendRequests; }
  void setSendRedundantResendRequests ( bool value )
    { m_sendRedundantResendRequests = value; } 

  bool getCheckCompId()
    { return m_checkCompId; }
  void setCheckCompId ( bool value )
    { m_checkCompId = value; }

  bool getCheckLatency()
    { return m_checkLatency; }
  void setCheckLatency ( bool value )
    { m_checkLatency = value; }

  int getMaxLatency()
    { return m_maxLatency; }
  void setMaxLatency ( int value )
    { m_maxLatency = value; }

  int getLogonTimeout()
    { return m_state.logonTimeout(); }
  void setLogonTimeout ( int value )
    { m_state.logonTimeout( value ); }

  int getLogoutTimeout()
    { return m_state.logoutTimeout(); }
  void setLogoutTimeout ( int value )
    { m_state.logoutTimeout( value ); }

  bool getResetOnLogon()
    { return m_resetOnLogon; }
  void setResetOnLogon ( bool value )
    { m_resetOnLogon = value; }

  bool getResetOnLogout()
    { return m_resetOnLogout; }
  void setResetOnLogout ( bool value )
    { m_resetOnLogout = value; }

  bool getResetOnDisconnect()
    { return m_resetOnDisconnect; }
  void setResetOnDisconnect( bool value )
    { m_resetOnDisconnect = value; }

  bool getRefreshOnLogon()
    { return m_refreshOnLogon; }
  void setRefreshOnLogon( bool value )
    { m_refreshOnLogon = value; } 

  bool getMillisecondsInTimeStamp()
    { return m_millisecondsInTimeStamp; }
  void setMillisecondsInTimeStamp ( bool value )
    { m_millisecondsInTimeStamp = value; }

  const std::string& getSenderSubID()
    { return m_sSenderSubID; }
  void setSenderSubID ( std::string value )
    { m_sSenderSubID = value; }

  	const std::string& getOnBehalfOfCompID()
    { return m_sOnBehalfOfCompID; }
  void setOnBehalfOfCompID ( std::string value )
    { m_sOnBehalfOfCompID = value; }

  const std::string& getTargetSubID()
	  { return m_sTargetSubID; }
	void setTargetSubID ( std::string value )
	  { m_sTargetSubID = value; }

	bool getPersistMessages()
    { return m_persistMessages; }
  void setPersistMessages ( bool value )
    { m_persistMessages = value; }

  bool getNeedUpLogon()
    { return m_bNeedUpLogon; }
  void setNeedUpLogon ( bool value )
    { m_bNeedUpLogon = value; }

  void setNeedChkTime(bool value)
  	{
		m_bNeedChkTime = value;
  	}
  bool getNeedChkTime()
  	{
		return m_bNeedChkTime;
  	}
  void setResponder( Responder* pR )
  {
    m_pResponder = pR;
  }

  bool send( Message& );
  void next();
  void next( const UtcTimeStamp& timeStamp );
  void next( const std::string&, const UtcTimeStamp& timeStamp, bool queued = false );
  void next( const Message&, const UtcTimeStamp& timeStamp, bool queued = false );
  void disconnect();

  long getExpectedSenderNum() { return m_state.getNextSenderMsgSeqNum(); }
  long getExpectedTargetNum() { return m_state.getNextTargetMsgSeqNum(); }

  Log* getLog() { return &m_state; }
  const MessageStore* getStore() { return &m_state; }

  void nextSLC( const UtcTimeStamp& timeStamp );
  void nextSLC( const std::string&, const UtcTimeStamp& timeStamp, bool queued = false );
  bool sendSLC( const int iRequestid,const std::string& );
  std::string& getServerID()
  { return m_sServerID; }
  void setServerID( const std::string& str  )
  { 
	  if(str.size() <= 5)
	  {
		m_sServerID.append(5-str.size(),'0'); 
		m_sServerID += str;
	  }
 }
  bool getServerFlag()
  { return m_bServer; }
  void setServerFlag( bool bServer  )
  { 
	m_bServer = bServer;
  } 
  
private:
  typedef std::map < SessionID, Session* > Sessions;
  typedef std::set < SessionID > SessionIDs;

  static bool addSession( Session& );
  static void removeSession( Session& );

  bool send( const std::string& );
  bool sendRaw( Message&, int msgSeqNum = 0 );
  bool resend( Message& message );
  void persist( const Message&, const std::string& ) throw ( IOException );

  void insertSendingTime( Header& );
  void insertOrigSendingTime( Header&,
                              const UtcTimeStamp& when = UtcTimeStamp () );
  void insertSendingTimeHR( Header& );
  void fill( Header& );

  bool isGoodTime( const SendingTime& sendingTime )
  {
    if ( !m_checkLatency ) return true;
    UtcTimeStamp now;
    return labs( now - sendingTime ) <= m_maxLatency;
  }
  bool checkSessionTime( const UtcTimeStamp& timeStamp )
  {
    if (!m_bNeedChkTime) return true;
    UtcTimeStamp creationTime = m_state.getCreationTime();
    return m_sessionTime.isInSameRange( timeStamp, creationTime );
  }
  bool isTargetTooHigh( const MsgSeqNum& msgSeqNum )
  { return msgSeqNum > ( m_state.getNextTargetMsgSeqNum() ); }
  bool isTargetTooLow( const MsgSeqNum& msgSeqNum )
  { return msgSeqNum < ( m_state.getNextTargetMsgSeqNum() ); }
  bool isCorrectCompID( const SenderCompID& senderCompID,
                        const TargetCompID& targetCompID )
  {
    if( !m_checkCompId ) return true;

    return
      m_sessionID.getSenderCompID().getValue() == targetCompID.getValue()
      && m_sessionID.getTargetCompID().getValue() == senderCompID.getValue();
  }
  bool shouldSendReset();
  
  bool validLogonState( const MsgType& msgType );
  void fromCallback( const MsgType& msgType, const Message& msg,
                     const SessionID& sessionID );

  void doBadTime( const Message& msg );
  void doBadCompID( const Message& msg );
  bool doPossDup( const Message& msg );
  bool doTargetTooLow( const Message& msg );
  void doTargetTooHigh( const Message& msg );
  void nextQueued( const UtcTimeStamp& timeStamp );
  bool nextQueued( int num, const UtcTimeStamp& timeStamp );

  void nextLogon( const Message&, const UtcTimeStamp& timeStamp );
  void nextHeartbeat( const Message&, const UtcTimeStamp& timeStamp );
  void nextTestRequest( const Message&, const UtcTimeStamp& timeStamp );
  void nextLogout( const Message&, const UtcTimeStamp& timeStamp );
  void nextReject( const Message&, const UtcTimeStamp& timeStamp );
  void nextSequenceReset( const Message&, const UtcTimeStamp& timeStamp );
  void nextResendRequest( const Message&, const UtcTimeStamp& timeStamp );

  void generateLogon();
  void generateLogon( const Message& );
  void generateResendRequest( const BeginString&, const MsgSeqNum& );
  void generateSequenceReset( int, int );
  void generateHeartbeat();
  void generateHeartbeat( const Message& );
  void generateTestRequest( const std::string& );
  void generateReject( const Message&, int err, int field = 0 );
  void generateReject( const Message&, const std::string& );
  void generateBusinessReject( const Message&, int err, int field = 0 );
  void generateLogout( const std::string& text = "" );

  void populateRejectReason( Message&, int field, const std::string& );
  void populateRejectReason( Message&, const std::string& );

  bool verify( const Message& msg,
               bool checkTooHigh = true, bool checkTooLow = true );

  bool set( int s, const Message& m );
  bool get( int s, Message& m ) const;

  Application& m_application;
  SessionID m_sessionID;
  TimeRange m_sessionTime;
  TimeRange m_logonTime;

  std::string m_senderDefaultApplVerID;
  std::string m_targetDefaultApplVerID;
  bool m_sendRedundantResendRequests;
  bool m_checkCompId;
  bool m_checkLatency;
  int m_maxLatency;
  bool m_resetOnLogon;
  bool m_resetOnLogout;
  bool m_resetOnDisconnect;
  bool m_refreshOnLogon;
  bool m_millisecondsInTimeStamp;
  bool m_persistMessages;
  bool m_bNeedChkTime;
  bool m_bNeedUpLogon;            //是否需要向上发送登录消息
  bool m_bServer;                 //是否为server 
  SessionState m_state;
  DataDictionaryProvider m_dataDictionaryProvider;
  MessageStoreFactory& m_messageStoreFactory;
  LogFactory* m_pLogFactory;
  LogFactory* m_pFileLogFactory;
  Responder* m_pResponder;
  Mutex m_mutex;

  static Sessions s_sessions;
  static SessionIDs s_sessionIDs;
  static Sessions s_registered;
  static Mutex s_mutex;

  std::string m_sOnBehalfOfCompID;
  std::string m_sSenderSubID;
  std::string m_sTargetSubID;
  std::string m_sPassword;
  std::string m_sServerID;
  std::string m_sInvestorID;
  std::string m_sBrokerID;
 
  int m_iTimeDiff; //与fix服务器之间的时间差
  FIX::UtcTimeStamp     m_bLogonReqUtcTime;  //登录请求发送的时间
  
};
}

#endif //FIX_SESSION_H
