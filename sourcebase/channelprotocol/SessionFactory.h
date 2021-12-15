// SessionFactory.h: interface for the CSessionFactory class.
//
// 20070921 hwp 调整了结构，Listener不再由单独的线程驱动，改为读写线程驱动；
//                 Connecter只在连接部分由单独的线程驱动。
//                 增加了对连接模式的设定，可以指定对多个服务器是采用
//                 随机连接还是按注册顺序连接
// 20070924 hwp 支持nameserver
///20080727 hwp NT-0048:
///                1.CSessionConnecter、RegisterListener、RegisterConnecter
///                  参数改为const, 降低对传入参数的要求。
///                2.注册地址时增加标记参数，在连接成功时会返回，以区分通过
///                  不同地址创建的连接
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SESSIONFACTORY_H__375DDDE4_5E34_446C_884F_B81EE4789A15__INCLUDED_)
#define AFX_SESSIONFACTORY_H__375DDDE4_5E34_446C_884F_B81EE4789A15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SelectReactor.h"
#include "ListenCtrl.h"
#include "Session.h"
#include "NetworkFactory.h"
#include "HashMap.h"

const int UM_LISTEN_RESULT			= 0x40901 + SM_USER;
const int UM_CONNECT_RESULT			= 0x40902 + SM_USER;
const int UM_TRY_CONNECT			= 0x40903 + SM_USER;
const int UM_CONNECT_LOOP			= 0x40904 + SM_USER;

const int TIMER_ID_CONNECT = 1;

class CSessionConnecter
{
public:
	CSessionConnecter(const char *location, DWORD dwMark);
	void CheckChannel(CChannel *pChannel);
	void OnConnected(CChannel *pChannel);
	CChannel *GetChannel();
	CChannel *Connect();
	CServiceName *GetServiceName();
	DWORD GetMark();
private:
	CServiceName m_ServiceName;
	CChannel *m_pChannel;
	CEventHandler *m_pSessionFactory;
	DWORD m_dwMark;
};

class CConnecterManager : public CEventHandler
{
public:
	CConnecterManager(CReactor *pReactor, CEventHandler *pSessionFactory);
	~CConnecterManager();
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);
	void AppendConnecter(CSessionConnecter *pConnecter);
	void Clear();
	int Connect(bool bRandom);
	int ConnectNext();
	void OnConnected(CChannel *pChannel);
	void OnDiscconnected(CChannel *pChannel);
	void CancelConnect();
	bool IsConnecting();
private:
	void RandomConnecters();
private:
	vector<CSessionConnecter *> m_connecters;
	CEventHandler *m_pSessionFactory;
	int m_nConnecterPos;
};

class CSessionListener : public CListenCtrl
{
public:
	CSessionListener(CReactor *pReactor, CEventHandler *pSessionFactory, CServerBase *pServer,
		DWORD dwMark);
	int OnConnected(CChannel *pChannel);
private:
	CEventHandler *m_pSessionFactory;
	DWORD m_dwMark;
};

class CSessionFactory : public CEventHandler, public CSessionCallback
{
public:
	CSessionFactory(CReactor *pReactor, int nMaxSession,CSelectReactor* pConnReactor=NULL);
	virtual ~CSessionFactory();
	virtual void Start();
	void Stop();
	void DisconnectAll(int nReason);
	virtual void OnTimer(int nIDEvent);
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);
	void RegisterConnecter(const char *location, DWORD dwMark = 0);
	void RegisterListener(const char *location, DWORD dwMark = 1);
	void EnableConnecter(bool bEnable);
	void EnableListener(bool bEnable);
	void SetConnectMode(bool bRandomConnect);
	inline bool IsConnecterEnable();
	inline bool IsListenerEnable();
	CSession *GetSession(DWORD nSessionID);
protected:
	virtual CSession *CreateSession(CChannel *pChannel, DWORD dwMark) = 0;
	virtual void OnSessionConnected(CSession *pSession);
	virtual void OnSessionDisconnected(CSession *pSession, int nReason);
	virtual void OnSessionWarning(CSession *pSession, int nReason, int nParam);	

	void OnChannelCreated(CChannel *pChannel, DWORD dwMark);
protected:
//	CSelectReactor m_reactorConnect;
	CSelectReactor* m_pConnReactor;
	vector<CSessionListener *> m_listeners;
	CConnecterManager *m_pConnecterManager;
	int m_nMaxSession;
	
	bool m_bRandomConnect;
	bool m_bConnecterEnable;
	bool m_bListenerEnable;
	bool m_bSessionCreateBySelf;

	typedef CHashMap<DWORD, CSession *, HashInt> CSessionMap;
	CSessionMap m_mapSession;	
};

inline bool CSessionFactory::IsConnecterEnable()
{
	return m_bConnecterEnable;
}

inline bool CSessionFactory::IsListenerEnable()
{
	return m_bListenerEnable;
}

#endif // !defined(AFX_SESSIONFACTORY_H__375DDDE4_5E34_446C_884F_B81EE4789A15__INCLUDED_)
