// SessionFactory.cpp: implementation of the CSessionFactory class.
//
// 20070410 hwp 修改BUG：注册多个前置，USERAPI同时都会连接成功。
//				   原因是OnTimer使用PostEvent通知SessionFactory,使得
//				   m_mapSession.GetCount没有及时更新
// 20070822 hwp 当注册多个服务器时，原来总是从第一个开始逐个尝试连接,
//				   现改为随机从列表中某个服务器开始，依次尝试连接
// 20070828 hwp 调整日志的级别和分类
// 20070921 hwp 调整了结构，Listener不再由单独的线程驱动，改为读写线程驱动；
//                 Connecter只在连接部分由单独的线程驱动。
//                 增加了对连接模式的设定，可以指定对多个服务器是采用
//                 随机连接还是按注册顺序连接
// 20070924 hwp 支持nameserver
// 20071011 hwp 为网络连接建立、断开事件增加IP地址信息
///20080727 hwp NT-0048 : 
///                1.CSessionConnecter、RegisterListener、RegisterConnecter
///                  参数改为const, 降低对传入参数的要求。
///                2.注册地址时增加标记参数，在连接成功时会返回，以区分通过
///                  不同地址创建的连接
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "SessionFactory.h"

const int TIMER_INTERVAL_CONNECT = 5000;

//////////////////////////////////////////////////////////////////////
CSessionConnecter::CSessionConnecter(const char *location, DWORD dwMark)
	:m_ServiceName(location)
{
	m_pChannel = NULL;
	m_dwMark = dwMark;
}

CChannel *CSessionConnecter::GetChannel()
{
	return m_pChannel;
}

CServiceName *CSessionConnecter::GetServiceName()
{
	return &m_ServiceName;
}

DWORD CSessionConnecter::GetMark()
{
	return m_dwMark;
}

void CSessionConnecter::CheckChannel(CChannel *pChannel)
{
	if (m_pChannel == pChannel)
	{
		m_pChannel = NULL;
	}
}

void CSessionConnecter::OnConnected(CChannel *pChannel)
{
	m_pChannel = pChannel;
}

CChannel *CSessionConnecter::Connect()
{
	CChannel *pNewChannel = CNetworkFactory::GetInstance()->CreateChannel(&m_ServiceName);
	if(pNewChannel==NULL)
	{
		REPORT_EVENT(LOG_INFO, "Connect", "Connect to %s:%d Error",
			m_ServiceName.GetHost(),m_ServiceName.GetPort());
	}
	else
	{
		REPORT_EVENT(LOG_INFO, "Connect", "Connect to %s:%d",
			m_ServiceName.GetHost(),m_ServiceName.GetPort());
	}
	return pNewChannel;
}

//////////////////////////////////////////////////////////////////////

CConnecterManager::CConnecterManager(CReactor *pReactor, CEventHandler *pSessionFactory)
:CEventHandler(pReactor)
{
	m_pSessionFactory = pSessionFactory;
	Clear();
}

CConnecterManager::~CConnecterManager()
{
	Clear();
}

void CConnecterManager::AppendConnecter(CSessionConnecter *pConnecter)
{
	m_connecters.push_back(pConnecter);
}

void CConnecterManager::Clear()
{
	for(int i=0; i<m_connecters.size(); i++)
	{
		delete m_connecters[i];
	}
	m_connecters.clear();
	m_nConnecterPos = -1;
}

void CConnecterManager::OnDiscconnected(CChannel *pChannel)
{
	for(int i=0; i<m_connecters.size(); i++)
	{
		m_connecters[i]->CheckChannel(pChannel);
	}
	m_pSessionFactory->PostEvent(UM_CONNECT_LOOP, 0, this);
}

void CConnecterManager::OnConnected(CChannel *pChannel)
{
	m_connecters[m_nConnecterPos]->OnConnected(pChannel);
}

void CConnecterManager::RandomConnecters()
{
	int nConnecterSize = m_connecters.size();
	if (nConnecterSize <= 0)
	{
		return;
	}
	int nStartPos = rand()%nConnecterSize;
//	NET_CONNECT_LOG1("nStartPos = %d\n", nStartPos);
	for (int i=0; i<nStartPos; i++)
	{
		CSessionConnecter *pBack = m_connecters.back();
		m_connecters.pop_back();
		m_connecters.insert(m_connecters.begin(), pBack);
	}
}

int CConnecterManager::Connect(bool bRandom)
{
	if (bRandom)
	{
		RandomConnecters();
	}
	m_nConnecterPos = -1;
	return ConnectNext();
}

int CConnecterManager::ConnectNext()
{
	for (m_nConnecterPos++; m_nConnecterPos<m_connecters.size(); m_nConnecterPos++)
	{
		CSessionConnecter *pConnecter = m_connecters[m_nConnecterPos];
		if (pConnecter->GetChannel() == NULL)
		{
			PostEvent(UM_TRY_CONNECT, 0, pConnecter);
			return m_nConnecterPos;
		}
	}
	m_nConnecterPos = -1;
	m_pSessionFactory->SendEvent(UM_CONNECT_LOOP, 0, this);
	return m_nConnecterPos;
}

void CConnecterManager::CancelConnect()
{
	m_nConnecterPos = -1;
}

bool CConnecterManager::IsConnecting()
{
	return m_nConnecterPos != -1;
}

int CConnecterManager::HandleEvent(int nEventID, DWORD dwParam, void *pParam)
{
	switch(nEventID) 
	{
	case UM_TRY_CONNECT:
		{
			CSessionConnecter *pConnecter = (CSessionConnecter *)pParam;
			CChannel *pNewChannel = pConnecter->Connect();
			m_pSessionFactory->SendEvent(UM_CONNECT_RESULT, pConnecter->GetMark(), pNewChannel);
		}
		return 0;
	default:
		break;
	} 
	return CEventHandler::HandleEvent(nEventID, dwParam, pParam);
}

//////////////////////////////////////////////////////////////////////
CSessionListener::CSessionListener(CReactor *pReactor, CEventHandler *pSessionFactory, 
								   CServerBase *pServer, DWORD dwMark)
:CListenCtrl(pReactor, pServer)
{
	m_pSessionFactory = pSessionFactory;
	m_dwMark = dwMark;
}

int CSessionListener::OnConnected(CChannel *pChannel)
{
	m_pSessionFactory->SendEvent(UM_LISTEN_RESULT, m_dwMark, pChannel);
	return 0;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSessionFactory::CSessionFactory(CReactor *pReactor, int nMaxSession,CSelectReactor* pConnReactor)
:CEventHandler(pReactor)
{
	srand(time(NULL));
	m_nMaxSession = nMaxSession;
	m_bConnecterEnable = true;
	m_bListenerEnable = true;
	m_bRandomConnect = true;
	if(NULL==pConnReactor)
	{
		m_pConnReactor=new CSelectReactor(
			#ifdef LINUX 
				g_bBindThreadsToCPU
			#endif
			);
		m_bSessionCreateBySelf=true;
	}
	else
	{	
		m_pConnReactor=pConnReactor;
		m_bSessionCreateBySelf=false;
	}
	m_pConnecterManager = new CConnecterManager(m_pConnReactor, this);
}

CSessionFactory::~CSessionFactory()
{
	Stop();
	for (int i=0; i<m_listeners.size(); i++)
	{
		delete m_listeners[i];
	}
	m_listeners.clear();
	delete m_pConnecterManager;
	if(m_bSessionCreateBySelf)
	{
		delete m_pConnReactor;
	}
}

void CSessionFactory::Start()
{
	if(m_bSessionCreateBySelf)
	{
		m_pConnReactor->Create();
	}
	OnTimer(TIMER_ID_CONNECT);
}

void CSessionFactory::Stop()
{
	if(m_bSessionCreateBySelf)
	{
		m_pConnReactor->Stop();
		m_pConnReactor->Join();
	}
	DisconnectAll(0);
}

void CSessionFactory::DisconnectAll(int nReason)
{
	for (;;)
	{
		CSessionMap::iterator itor = m_mapSession.Begin();
		if (itor.IsEnd())
		{
			break;
		}
		(*itor)->Disconnect(nReason);
	}
}

void CSessionFactory::RegisterConnecter(const char *location, DWORD dwMark)
{
 	CSessionConnecter *pConnecter = new CSessionConnecter(location, dwMark);
	m_pConnecterManager->AppendConnecter(pConnecter);
}

void CSessionFactory::RegisterListener(const char *location, DWORD dwMark)
{
	CServiceName srvname(location);
	CServerBase *pServer = CNetworkFactory::GetInstance()->CreateServer(&srvname);
	if (pServer == NULL) 
	{
		return;
	}
	CSessionListener *pListener = 
		new CSessionListener(m_pReactor, this, pServer, dwMark);
	m_pReactor->RegisterIO(pListener);
	m_listeners.push_back(pListener);
}

void CSessionFactory::OnTimer(int nIDEvent)
{
	if (nIDEvent == TIMER_ID_CONNECT)
	{
		KillTimer(TIMER_ID_CONNECT);
		if (m_mapSession.GetCount()<m_nMaxSession && IsConnecterEnable() &&
			!m_pConnecterManager->IsConnecting())
		{
			m_pConnecterManager->Connect(m_bRandomConnect);
		}
		return;
	}
	CEventHandler::OnTimer(nIDEvent);
}

int CSessionFactory::HandleEvent(int nEventID, DWORD dwParam, void *pParam)
{
	switch(nEventID) {
	case UM_CONNECT_RESULT:
		{
			CChannel *pChannel = (CChannel *)pParam;
			if (pChannel != NULL)
			{
				m_pConnecterManager->OnConnected(pChannel);
				OnChannelCreated(pChannel, dwParam);
			}
			if (m_mapSession.GetCount()<m_nMaxSession && IsConnecterEnable())
			{
				m_pConnecterManager->ConnectNext();
			}		
			else
			{
				m_pConnecterManager->CancelConnect();
			}
		}
		return 0;
	case UM_CONNECT_LOOP:
		{
			SetTimer(TIMER_ID_CONNECT, TIMER_INTERVAL_CONNECT);
		}
		return 0;
	case UM_LISTEN_RESULT:
		{
			CChannel *pChannel = (CChannel *)pParam;
			if (m_mapSession.GetCount()>m_nMaxSession || !IsListenerEnable())
			{
				pChannel->Disconnect();	
			}
			else
			{
				OnChannelCreated(pChannel, dwParam);
			}
		}
		return 0;
	default:
		break;
	}
	return CEventHandler::HandleEvent(nEventID, dwParam, pParam);
}

void CSessionFactory::OnChannelCreated(CChannel *pChannel, DWORD dwMark)
{
	CSession *pSession = CreateSession(pChannel, dwMark) ;
	if (pSession != NULL) 
	{
		m_pReactor->RegisterIO(pSession);
		pSession->RegisterSessionCallback(this);
		OnSessionConnected(pSession);
	}
}

void CSessionFactory::OnSessionConnected(CSession *pSession)
{
	REPORT_EVENT(LOG_INFO, "Connect", "Session 0x%08x Connected, IP=%s",
		pSession->GetSessionID(), pSession->GetChannel()->GetRemoteName());
	m_mapSession.Insert(pSession->GetSessionID(), pSession);
}

void CSessionFactory::OnSessionDisconnected(CSession *pSession, int nReason)
{
	REPORT_EVENT(LOG_INFO, "Connect", 
		"Session 0x%08x Disconnected, reason = [0x%08x], IP=%s",
		pSession->GetSessionID(), nReason,
		pSession->GetChannel()->GetRemoteName());
	m_mapSession.Erase(pSession->GetSessionID());
	if (m_pConnecterManager != NULL)
	{
		m_pConnecterManager->OnDiscconnected(pSession->GetChannel());
	}
}

void CSessionFactory::OnSessionWarning(CSession *pSession, int nReason, int nParam)
{
}

void CSessionFactory::EnableConnecter(bool bEnable)
{
	m_bConnecterEnable = bEnable;
	OnTimer(TIMER_ID_CONNECT);
}

void CSessionFactory::EnableListener(bool bEnable)
{
	m_bListenerEnable = bEnable;
}

void CSessionFactory::SetConnectMode(bool bRandomConnect)
{
	m_bRandomConnect = bRandomConnect;
}

CSession *CSessionFactory::GetSession(DWORD nSessionID)
{
	CSession **pFind = m_mapSession.Find(nSessionID);
	if (pFind == NULL)
	{
		return NULL;
	}
	return *pFind;
}
