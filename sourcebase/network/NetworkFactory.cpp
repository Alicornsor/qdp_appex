// NetworkFactory.cpp: implementation of the CNetworkFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "NetworkFactory.h"


CNetworkFactory *CNetworkFactory::m_pInstance = NULL;

CNetworkFactory g_NetworkFactory;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CNetworkFactory::CNetworkFactory()
{
	m_pNext = NULL;
}

CNetworkFactory::~CNetworkFactory()
{
}

CNetworkFactory *CNetworkFactory::GetInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = &g_NetworkFactory;
	}
	return m_pInstance;
}
	
void CNetworkFactory::RegisterFactory()
{
	m_pNext = GetInstance();
	m_pInstance = this;
}

CServerBase *CNetworkFactory::CreateServer(CServiceName *pName)
{
	if (m_pNext != NULL)
	{
		return m_pNext->CreateServer(pName);
	}
	RAISE_RUNTIME_ERROR("Unknown channel in CServiceName");
	return NULL;
}

CChannel *CNetworkFactory::CreateChannel(CServiceName *pName)
{
	CClientBase *pClient = CreateClient(pName);
	if (pClient == NULL)
	{
		return NULL;
	}
	CChannel *pChannel =  pClient->Connect(pName);
	delete pClient;
	return pChannel;
}

CClientBase *CNetworkFactory::CreateClient(CServiceName *pName)
{
	if (m_pNext != NULL)
	{
		return m_pNext->CreateClient(pName);
	}
	RAISE_RUNTIME_ERROR("Unknown channel in CServiceName");
	return NULL;
}
