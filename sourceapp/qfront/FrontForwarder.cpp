// FrontForwarder.cpp: implementation of the CFrontForwarder class.
//
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "FrontForwarder.h"

CFrontForwarder::CFrontForwarder(DWORD nFrontID,CGateWayClient *pFrontClient,DWORD nQueryServerID, CFibClientApi *pFibClientApi)
{
	m_nFrontID = nFrontID;
	m_nQueryServerID = nQueryServerID;
	m_pFibClientApi = pFibClientApi;	
	m_pFrontClient = pFrontClient;
}

CFrontForwarder::~CFrontForwarder()
{

}

void CFrontForwarder::PrepareForward(CXTPPackage *pXTPPackage, DWORD tid,DWORD nSessionID, DWORD nRequestID)
{
	pXTPPackage->PreparePublish(tid);
	pXTPPackage->SetFrontID(m_nFrontID);
	pXTPPackage->SetSessionID(nSessionID);
	pXTPPackage->SetRequestID(nRequestID);
}

void CFrontForwarder::ForwardTransaction(CXTPPackage *pXTPPackage)
{
	//NET_IO_LOG0("CFrontForwarder::ForwardTransaction\n");
	XTP_HEADER_DEBUG(pXTPPackage);
//	pXTPPackage->MakePackage();
	m_pFrontClient->SendReportPackage(pXTPPackage);
}

int CFrontForwarder::ForwardQuery(CXTPPackage *pXTPPackage)
{
	pXTPPackage->GetXTPHeader()->Type = XTP_REQUEST;
	return m_pFibClientApi->Request(m_nQueryServerID, pXTPPackage);
}
void CFrontForwarder::SetCommPhaseNo(WORD nCommPhaseNo)
{
//	m_pPublishFlow->SetCommPhaseNo(nCommPhaseNo);
}
