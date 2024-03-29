// ServiceStub.cpp: implementation of the CServiceStub class.
//
// 20070822	hwp 配合SessionFactory修改，支持随机连接服务器
// 20080727 hwp NT-0048:扩展CSessionFactory::CreateSession参数，便于创建
//                 会话时区分不同的连接
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "ServiceStub.h"
#include "SessionFactory.h"
#include "ServiceSession.h"

const int FIB_IMPL_HEADER_RESERVED = 200;

class CServiceStubSessionFactory : public CSessionFactory, public CXTPRspCallback
{
public:
	CServiceStubSessionFactory(CReactor *pReactor, DWORD nServerID, CResponseHandler *pRspHandler,CSelectReactor* pConnReactor)
	:CSessionFactory(pReactor, 1,pConnReactor)
	{
		m_nServerID = nServerID;
		m_pResponseHandler = pRspHandler;
	}

	virtual CSession *CreateSession(CChannel *pChannel, DWORD)
	{
		CServiceSession *pSession = new CServiceSession(m_pReactor, pChannel);
		pSession->RegisterRspHandler(this);
		return pSession;
	}

	CServiceSession *GetSession()
	{
		CSessionMap::iterator itor = m_mapSession.Begin();
		if (!itor.IsEnd())
		{
			return (CServiceSession *)(*itor);
		}
		return NULL;
	}

	virtual int HandleResponse(CXTPPackage *pXTPPackage, CXTPSession *pSession)
	{
		if (m_pResponseHandler != NULL)
		{
			m_pResponseHandler->OnResponse(pXTPPackage);
		}
		return 0;
	}
private:
	CResponseHandler *m_pResponseHandler;
	DWORD m_nServerID;
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServiceStub::CServiceStub(CReactor *pReactor, DWORD nNodeID,CSelectReactor* pConnReactor):CFibClientApi(pConnReactor)
{
	m_pReactor = pReactor;
	m_nNodeID = nNodeID;
	m_pConnReactor=pConnReactor;
	m_bUseGlobalReactor=false;
	if(NULL!=pConnReactor)
	{
		m_bUseGlobalReactor=true;
	}
}

CServiceStub::~CServiceStub()
{
	CServerMap::iterator itor = m_mapServer.Begin();
	while (!itor.IsEnd())
	{
		delete (*itor);
		itor ++;
	}
}

void CServiceStub::RegisterServer(DWORD nServerID, char *pszAddress, CResponseHandler *pRspHandler)
{
	CSessionFactory *pSessionFactory = GetSessionFactory(nServerID);
	if (pSessionFactory == NULL)
	{
		pSessionFactory = new CServiceStubSessionFactory(m_pReactor, nServerID, pRspHandler,m_pConnReactor);
		m_mapServer.Insert(nServerID, pSessionFactory);
//		pSessionFactory->Start();
	}
	
	pSessionFactory->RegisterConnecter(pszAddress);
		
}

void CServiceStub::Start()
{
	if(!m_bUseGlobalReactor)
	{
		CServerMap::iterator itor = m_mapServer.Begin();
		for (;!itor.IsEnd(); itor++)
		{
			(*itor)->Start();
		}
	}
}

CXTPPackage *CServiceStub::CreateMessage()
{
	CXTPPackage *pMessage = new CXTPPackage;
	pMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE, FIB_IMPL_HEADER_RESERVED);
	return pMessage;
}

CSessionFactory *CServiceStub::GetSessionFactory(DWORD nServerID)
{
	CSessionFactory **pFind = m_mapServer.Find(nServerID);
	if (pFind != NULL)
	{
		return *pFind;
	}
	return NULL;
}

CServiceSession *CServiceStub::GetServerSession(DWORD nServerID)
{
	CServiceStubSessionFactory *pSessionFactory = 
		(CServiceStubSessionFactory*)GetSessionFactory(nServerID);
	if (pSessionFactory != NULL)
	{
		return pSessionFactory->GetSession();
	}

	return NULL;
}

DWORD CServiceStub::GetNodeID()
{
	return m_nNodeID;
}

int CServiceStub::Request(DWORD nServerID, CXTPPackage *pMessage)
{
	CServiceSession *pSession = GetServerSession(nServerID);
	if (pSession == NULL)
	{
		return -1;
	}

	pSession->SendRequestPackage(pMessage);
	return 0;
}

void CServiceStub::Release()
{
	delete this;
}

CFibClientApi *CFibClientApi::CreateClientApi(CReactor *pReactor, DWORD nNodeID)
{
	return new CServiceStub(pReactor, nNodeID,m_pConnReactor);
}

CSelectReactor* CFibClientApi::m_pConnReactor=NULL;
