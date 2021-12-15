// MultiNetworkFactory.cpp: implementation of the CMultiNetworkFactory class.
//
// 2006.10.11	赵鸿昊	将变量Multi_NETWORK_NAME移入CPP中，
//						防止多次包含引起的重复定义 
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "MultiNetworkFactory.h"
#include "MultiClient.h"
#include "MultiServer.h"

const char *Multi_NETWORK_NAME = "multi";

CMultiNetworkFactory CMultiNetworkFactory::m_instance;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMultiNetworkFactory::CMultiNetworkFactory()
{
	RegisterFactory();
}

CMultiNetworkFactory::~CMultiNetworkFactory()
{

}

CServerBase *CMultiNetworkFactory::CreateServer(CServiceName *pName)
{
	if (strcmp(pName->GetChannel(), Multi_NETWORK_NAME) == 0)
	{
		return new CMultiServer(pName);
	}
	return CNetworkFactory::CreateServer(pName);
}
	
CClientBase *CMultiNetworkFactory::CreateClient(CServiceName *pName)
{
	printf("CMultiNetworkFactory::CreateClient %s\n",pName->GetChannel());
	if (strcmp(pName->GetChannel(), Multi_NETWORK_NAME) == 0)
	{
		return new CMultiClient();
	}
	return CNetworkFactory::CreateClient(pName);
}


