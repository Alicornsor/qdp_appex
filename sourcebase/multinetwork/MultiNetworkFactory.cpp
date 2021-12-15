// MultiNetworkFactory.cpp: implementation of the CMultiNetworkFactory class.
//
// 2006.10.11	�Ժ��	������Multi_NETWORK_NAME����CPP�У�
//						��ֹ��ΰ���������ظ����� 
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


