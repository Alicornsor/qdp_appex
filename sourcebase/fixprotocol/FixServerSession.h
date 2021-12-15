#ifndef _FIX_SESSION_H
#define _FIX_SESSION_H
#ifdef _MSC_VER
#pragma warning( disable : 4503 4355 4786 4290 )
#endif


#include "FixStructDefs.h"
#include "FixApplication.h"
//#include "FixSocketAcceptor.h"
#include "quickfix/SocketAcceptor.h"
#include "errorDefine.h"

///////////////////////////////////////////////////////////////////////////////
#define QDP_TARGET_COMP_ID                        "QDP_FRONT"

//ErrCOde
#define ERR_FIX_ENGINE_OTHER_ORDER                 90000
#define ERR_FIX_ENGINE_DUPLICATE_ORDER             90001
#define ERR_FIX_ENGINE_UNSUPPORT_ORDER_TYPE        90002
#define ERR_FIX_ENGINE_INVAILD_USER_ID             90003
#define ERR_FIX_ENGINE_INVAILD_SECURITYID_ID       90004
#define ERR_FIX_ENGINE_ORDER_CANCEL_FAIL           90005
#define ERR_FIX_ENGINE_Undefined_Tag			   90006

///////////////////////////////////////////////////////////////////////////////
// 自定义
typedef struct FixReqRspInfoTag
{
	int				reqID;
	int				errCode;
	int				rejectReason;
	char     		refMsgType[48];
}FixReqRspInfoT;

typedef std::map<std::string, std::string> ClOrdIDSessionIDMap; //key=ClOrdID
typedef ClOrdIDSessionIDMap::iterator ClOrdIDSessionIDMapIter;

//错误码:key=sErrCode, value=sErrMsg
typedef std::map<int, std::string> FixEngineErrMsgMap;
typedef FixEngineErrMsgMap::iterator FixEngineErrMsgMapIter;


typedef std::map<std::string, DWORD > CSessionIdMap;
typedef CSessionIdMap::iterator CSessionIdMapIter;

typedef std::map<DWORD, std::string > CSession2FIXMap;
typedef CSession2FIXMap::iterator CSession2FIXMapIter;

class CFixServerSessionCB
{
public:
	//fixclient -> fixserver
	virtual int HandlePackage(const std::string &type, const FIX::Message& msg, const FIX::SessionID& sessionID)=0;
	
};

class CFixServerSession: public FIX::CFixApplicationCB, public FIX::CSocketAcceptorCB
{

public:
	CFixServerSession(const char *pFixServerCfgFile);
	CFixServerSession(FIX::SessionSettings sSettings, std::string sSenderCompID);
	void RegisterCB(CFixServerSessionCB *pCFixServerSessionCB)
	{
		m_CFixServerSessionCB = pCFixServerSessionCB;
	}
	~CFixServerSession();

	void StartServer();
	void OnRspLogon( const FIX::SessionID& sessionID, const char *pBrokerID, const char *pUser, const char *pPwd, int HeartBtInt );
	void OnErrLogonRsp( const FIX::SessionID& sessionID, const char *pUser, std::string errmsg );
	void OnRspLogon( const char *pBrokerID, const char *pUser, const char *pPwd, int HeartBtInt );
	void OnErrLogonRsp( const char *pUser, const char *iErrCode );
	
	void SendPositionReportMessage(const FIX::SessionID& sessionID, FIX::Message* pMsg);
	void SendExecutionReportMessage(FIX::Message* pMsg, const char *pClOrdID);
	void SendExecutionReportMessage(const FIX::SessionID& sessionID, FIX::Message* pMsg, const char *pClOrdID);
	
	void SendBusinessRejectMessage(const FIX::Message *pMsg, const FIX::SessionID& sessionID, int iErrCode, const	char* pRefMsgType, int iBusinessRejectReason);
	void SendBusinessRspRejectMessage(const FIX::Message *pMsg, const int iErrid,const char* iErrCode, const char* pRefMsgType, int iBusinessRejectReason, FIX::SessionID& tmpFixSession);
	void SendBusinessRspRejectMessage2(const FIX::Message *pMsg, const int iErrid, const char* iErrCode, const char* pRefMsgType, int iBusinessRejectReason);
	void SendOrderCancelReject( FIX::Message* pMsg );
	void SendOrderCancelReject(const FIX::SessionID& sessionID, FIX::Message *pMsg );
	
	bool IsFixServerStarted();
	bool SetOrderInfo(const char *pClOrdID, FIX::SessionID sessionID);
	std::string GetErrMsg(int iErrCode);
	DWORD  GetSSID( FIX::SessionID sessionID );
	void SendMsg2FixClient(FIX::Message &rsp);
	void SendMsg2FixClient(FIX::Message &rsp, const FIX::SessionID& sessionID);

private:
	//CFixApplicationCB
	void HandleMessage( FIX::IntFIXMsgType type, FIX::Message msg, FIX::SessionID sessionID);
	void HandleFixMessage(const std::string &type, FIX::Message msg, FIX::SessionID sessionID);
	void InitErrMsgMap(FixEngineErrMsgMap *pErrMsgMap);
	DWORD  GenSSID(FIX::SessionID sessionID);
	void   DelSSID(FIX::SessionID sessionID);

	void onConnect(  );
	void onDisconnect( FIX::Session* pSession );
	void InitSession(FIX::SessionSettings &sSettings);
public:
	CSession2FIXMap	 m_CSession2FIXMap;
private:
	int                  m_iSessionNum;
	CSessionIdMap        m_CSessionMap;
	FIX::CFixApplication m_CFixApplication;
	FIX::SocketAcceptor  *m_CSocketAcceptor;
	CFixServerSessionCB  *m_CFixServerSessionCB;
	ClOrdIDSessionIDMap  *m_ClOrdIDSessionIDMap; //用来保存ClordID与sessionID之间的关系
	FixEngineErrMsgMap   *m_FixEngineErrMsgMap;
	int                  m_iMaxSsID;
	bool                 m_FixServerStarted;
	DWORD                m_dwSessionIDBase;
	std::string          m_SenderCompID;
};


#endif
