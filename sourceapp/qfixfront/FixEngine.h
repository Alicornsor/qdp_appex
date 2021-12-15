#if !defined(AFX_FTDENGINE_H__A2F23839_A3FB_492C_AF58_0BB3B5CDD26A__INCLUDED_)
#define AFX_FTDENGINE_H__A2F23839_A3FB_492C_AF58_0BB3B5CDD26A__INCLUDED_



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000

#include "FixValues.h"
#include "FixServerSession.h"
#include "XtpPackageDesc.h"
#include "Mutex.h"
#include "CConfig.h"
#include "quickfix/Settings.h"
#include "SelectReactor.h"
#include "Session.h"
#include "XTPPackage.h"
#include "CachedFileFlow.h"
#include <iostream>   
#include <fstream>
#include "FrontForwarder.h"
using namespace std;

#define FRONTID 12
#define FIXPROTOCOL_42 "FIX42" 

#define SafeSetFixField(FixEntity,Value) \
	if(!Value.isNull()) {		\
		msg.setField(FixEntity(Value.getValue()));\
	}	\

#define SafeSetFixCharField(FixEntity,Value) \
	if(Value.isValid()) {		\
		msg.setField(FixEntity(Value.getValue()));\
	}	\

struct UserMessage 
{
	int   iReqID; 
	int   iExecID;
	int	  iQryID;
	DWORD sessionID;
	double FixVersion;
	bool loginSuccess;

	UserMessage()
	{
		iReqID = 1;
		iExecID = 1;
		iQryID = 1;
		sessionID = 0;
		FixVersion = 0.0;
		loginSuccess = false;
	}
};

//用户map
typedef std::map<std::string, CUserField> CUserMap;
typedef CUserMap::iterator CUserMapIter;

//userInvestor
typedef std::map<std::string, CUserInvestorField> CUserInvestorMap;
typedef CUserInvestorMap::iterator CUserInvestorMapIter;
//userLoginMap
typedef map<string, UserMessage*> UserLoginMap;
typedef UserLoginMap::iterator IterUserLoginMap;
//报单请求map
typedef std::map<std::string, CInputOrderField> CInsertOrderFieldMap;//key=orderSysID
typedef CInsertOrderFieldMap::iterator CInsertOrderFieldMapIter;
//撤单请求map
typedef std::map<std::string, COrderActionField> COrderActionFieldMap;//key=orderSysID
typedef COrderActionFieldMap::iterator COrderActionFieldMapIter;

typedef std::map<int, std::string> CIntStringMap;
typedef CIntStringMap::iterator CIntStringMapIter;

typedef std::map<std::string, std::string> CStringStringMap;
typedef CStringStringMap::iterator CStringStringMapIter;

typedef struct UserOrderInfoTag
{
	CInsertOrderFieldMap *pRtnOrderMap;          //订单map
	COrderActionFieldMap *pReqActionMap;    //撤单请求map
}UserOrderInfoT;


//class CFixEngine: public CFrontTerminalCallback, public CFixServerSessionCB, public CSessionCallback, public CThread
class CFixEngine :public CThread, public CFixServerSessionCB, public CSessionCallback
{
public:
	CFixEngine(CCachedFileFlow *m_pSendFlow,CConfig *pConf,CFrontForwarder *m_pFrontForwarder);
	virtual ~CFixEngine();

	virtual void Run();
	//处理fix用户报文
	virtual int HandlePackage(const std::string &type, const FIX::Message& msg, const FIX::SessionID &sessionID);
	bool DispatcherEvent(int nEventID, DWORD dwParam, void *pParam);

	//从CSessionCallback重载
	virtual void OnSessionConnected(CSession *pSession);
	virtual void OnSessionDisconnected(CSession *pSession, int nReason);
	virtual void OnSessionWarning(CSession *pSession, int nReason, int nParam){}

	int  OnReqFixUserLogin( const FIX::Message& msg, FIX::SessionID sessionID);
	int  OnReqFixUserLogout( FIX::Message msg, FIX::SessionID sessionID);
	int  OnReqFixSecurityListInfo(FIX::Message msg, FIX::SessionID sessionID);
	int  OnReqFixOrderAction(FIX::Message msg, FIX::SessionID sessionID);
	int  OnReqFixOrderInsert(const FIX::Message& msg, FIX::SessionID sessionID);
	int  OnReqFixUserMargin(const FIX::Message& msg, FIX::SessionID sessionID);
	int  OnReqFixUserPosition(const FIX::Message& msg, FIX::SessionID sessionID);
	int  OnReqFixAccountData(const FIX::Message& msg, FIX::SessionID sessionID);
	int  OnReqFixOrderMassStatus(const FIX::Message& msg, FIX::SessionID sessionID);
	int  OnReqFixUserPasswd(const FIX::Message& msg, FIX::SessionID sessionID);
	int  OnReqFixAvailableAccount(const FIX::Message& msg, FIX::SessionID sessionID);
	int  OnReqFixFee(const FIX::Message& msg, FIX::SessionID sessionID);
	int  OnReqQrySecurityDefinition(const FIX::Message& msg, FIX::SessionID sessionID);
	int  OnReqQryFillOrder(const FIX::Message& msg, FIX::SessionID sessionID);
	int  OnReqQryOrder(const FIX::Message& msg, FIX::SessionID sessionID);
	int  OnReqQryExange(const FIX::Message& msg, FIX::SessionID sessionID);
	
	int  GetReqID( const char * pUser );
	int  GetExecID( const char * pUser );
	void StartServer();
	int HandleXTPMessage( CXTPPackage * pMessage );
	
	//void SendRspOrderInsert( CAdviceOrderField* pField );
	//void SendRtnOrderInsert( CAdviceOrderField* pField );
	//void FillOrder(FIX::Message &rsp, CAdviceOrderField* pField);
	//void FillOrder(FIX::Message &rsp, CAdviceOrderField* pField, CTradeField* pTrade);
	bool SaveOrderInfo(CInputOrderField *pField, bool bReplace );
	bool SaveOrderInfo( COrderActionField &field, bool bReplace );
	//void SendRtnOrderAction( CAdviceOrderField* pField );

	void GenFixConfFile();
	void SendRspQryInstrument( CInstrumentField* pField, std::string sSecurityReqID );
	void SendOrderCancelReject( FIX::Message &msg, const char *pErrMsg );
	bool InitLoginInfo(const char* pUser, FIX::SessionID &sessionID, bool bLogin = false);
	bool DecodeUserOrderLocalID( const char* pUserOrderLocalID, char *pClOrdID, int &reqID );
	bool DecodeUserOrderLocalID( const char* pUserOrderLocalID, char *pClOrdID );
	bool DecodeUserOrderLocalID( const char* pUserOrderLocalID, int &reqID );
	bool ChkNeedSendLogin(const char* pUser);
	bool ChkFrontID(DWORD dwFrontID);
	bool isComment( const std::string& line );
	std::string GetExecRefID( int recNum );
	std::string EncodeUserOrderLocalID( const std::string& sClOrdID, int reqID );
	std::string GetExecID( int reqID );
	std::string GenAppName();
	CUserField *GetUserInfo( const char * pUser );
	DWORD GetSessionID( const char * pUserID );
	int   Float2Int( float avgpx, int iPoint );
	float FloatFormat(float avgpx, int iPoint);
	std::string GenLmeCodeDate();

	int sendTradeBusiness(CXTPPackage *pXTPPackage);
	void PrepareForward(CXTPPackage *pXTPPackage, DWORD tid, DWORD nSessionID, DWORD nRequestID, DWORD nFrontID = -1);

public:
	CFixServerSession * m_pFixServerSession;
	CUserMap*          m_pCUserMap;
	CUserInvestorMap*	m_UserInvestorMap;
	CStringStringMap*  m_QryUserInvestorMap;
	UserLoginMap	   m_userLoginMap;
	string        m_SenderCompID;
	CXTPPackage        m_reqPackage;

private:
	
	CFrontForwarder	   *m_pFrontForwarder;
	bool               m_bEnableFixServer;
	bool               m_bStop;
	CMutex             m_mFixEngineMutex;
	CConfig*           m_pConf;
	FIX::Settings      m_Settings;

	CCachedFileFlow	*m_pSendFlow;
	bool updateUser;
};

#endif // !defined(AFX_FTDENGINE_H__A2F23839_A3FB_492C_AF58_0BB3B5CDD26A__INCLUDED_)

