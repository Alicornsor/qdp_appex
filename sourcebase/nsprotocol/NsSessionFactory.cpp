// NsSessionFactory.cpp: implementation of the CNsSessionFactory class.
//
///20080727 hwp NT-0048 : 配合CSessionFactory的修改，注册地址时增加标记参数，
///                在连接成功时会返回，以区分通过不同地址创建的连接
// 20081230 hwp NT-0042 ：改为随机连接FENS，逐个连接前置。
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "NsSessionFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNsSessionFactory::CNsSessionFactory(CReactor *pReactor, int nMaxSession,CSelectReactor* pConnReactor)
:CSessionFactory(pReactor, nMaxSession,pConnReactor)
{
	m_bInQueryNs = false;
	m_pNsSession = NULL;
	m_pNsConnecterManager = new CConnecterManager(m_pConnReactor, this);
	SetConnectMode(false);
}

CNsSessionFactory::~CNsSessionFactory()
{

}

void CNsSessionFactory::RegisterNameServer(char *location, DWORD dwMark)
{
 	CSessionConnecter *pConnecter = new CSessionConnecter(location, dwMark);
	m_pNsConnecterManager->AppendConnecter(pConnecter);
}

int CNsSessionFactory::HandlePackage(CNsPackage *pNsPackage, CNsSession *pSession)
{
	char *p = pNsPackage->Address();
	char seps[] = "\r\n";
	m_pConnecterManager->Clear();
	// 20071128_hwp 使用strtok可能不安全，自已解析。
	char *token = p;
	for (int i=0; i<pNsPackage->Length(); i++,p++)
	{
		if (strchr(seps, *p))
		{
			if (token != NULL)
			{
				*p = '\0';
				RegisterConnecter(token);
				token = NULL;
			}
		}
		else
		{
			if (token == NULL)
			{
				token = p;
			}
		}
	}
	m_pNsConnecterManager->OnDiscconnected(m_pNsSession->GetChannel());
	m_pNsSession->Disconnect(0);
	m_pNsSession = NULL;
//	m_pNsConnecterManager->CancelConnect();
	// 20071128_hwp UM_CONNECT_LOOP事件导致NS状态切换，因此，该事件必须
	//                 在一个循环中只出现一次，否则切不到下一个状态。
//	SendEvent(UM_CONNECT_LOOP, 0, NULL);
	return -1;
}

void CNsSessionFactory::OnTimer(int nIDEvent)
{
	if (nIDEvent == TIMER_ID_CONNECT)
	{
		if (m_bInQueryNs)
		{
			KillTimer(TIMER_ID_CONNECT);
			if (m_pNsSession == NULL && !m_pNsConnecterManager->IsConnecting())
			{
				m_pNsConnecterManager->Connect(true);
			}
			return;
		}
	}
	CSessionFactory::OnTimer(nIDEvent);
}

int CNsSessionFactory::HandleEvent(int nEventID, DWORD dwParam, void *pParam)
{
	switch(nEventID) {
	case UM_CONNECT_RESULT:
		if(m_bInQueryNs)
		{
			CChannel *pChannel = (CChannel *)pParam;
			if (pChannel != NULL)
			{
				m_pNsConnecterManager->OnConnected(pChannel);
				m_pNsSession = new CNsSession(m_pReactor, pChannel);
				m_pReactor->RegisterIO(m_pNsSession);
//				m_pNsSession->RegisterSessionCallback(this);	//不要这一句
				m_pNsSession->RegisterPackageHandler(this);
			}
			if (m_pNsSession == NULL)
			{
				m_pNsConnecterManager->ConnectNext();
			}
			else
			{
				m_pNsConnecterManager->CancelConnect();
			}
			return 0;
		}
		break;
	case UM_CONNECT_LOOP:
		m_bInQueryNs = !m_bInQueryNs;
		//20071128_hwp 每次都直接调用OnTimer会导致在Linux下重连太频繁。	
		if (!m_bInQueryNs)	
		{
			OnTimer(TIMER_ID_CONNECT);
			return 0;
		}
		break;
	default:
		break;
	}
	return CSessionFactory::HandleEvent(nEventID, dwParam, pParam);
}
