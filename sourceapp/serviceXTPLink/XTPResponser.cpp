#include "XTPResponser.h"


CXTPResponser::CXTPResponser(CFlow *pFlow)
{
	m_pFlow = pFlow;
}

void CXTPResponser::SendResponse(CXTPPackage *pPackage,DWORD dwSessionID)
{
	m_pFlow->Append(pPackage->Address(), pPackage->Length());
}


CXTPRequestResponser::CXTPRequestResponser(CFibServerApi *pApi)
{
	m_pServerApi = pApi;
}


void CXTPRequestResponser::SendResponse(CXTPPackage *pPackage,DWORD dwSessionID)
{
	m_pServerApi->Response(pPackage,dwSessionID);
}

