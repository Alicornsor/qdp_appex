// FrontForwarder.cpp: implementation of the CFrontForwarder class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "FrontForwarder.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//extern void prob(int no,int maxp);


CFrontForwarder::CFrontForwarder(DWORD nFrontID, CFlow *pPublishFlow, 
						   DWORD nQueryServerID, CFibClientApi *pFibClientApi)
{
	m_nFrontID = nFrontID;
	m_pPublishFlow = pPublishFlow;
	m_nQueryServerID = nQueryServerID;
	m_pFibClientApi = pFibClientApi;
}

CFrontForwarder::~CFrontForwarder()
{

}

/*	׼��XTP���ݰ���ͷ��Ϣ�� �ỰID������ID�ȡ�
*/
void CFrontForwarder::PrepareForward(CXTPPackage *pXTPPackage, DWORD tid, 
									 DWORD nSessionID, DWORD nRequestID)
{
	pXTPPackage->PreparePublish(tid);
	pXTPPackage->SetFrontID(m_nFrontID);
	pXTPPackage->SetSessionID(nSessionID);
	pXTPPackage->SetRequestID(nRequestID);
}

/*	��XTP���ݰ���ӵ���������ȥ����qdp���ԣ�������������� m_pTradeSeries ����
*/
void CFrontForwarder::ForwardTransaction(CXTPPackage *pXTPPackage)
{
	//NET_IO_LOG0("CFrontForwarder::ForwardTransaction\n");
// 	printTime("CFrontForwarder::ForwardTransaction");
//	XTP_HEADER_DEBUG(pXTPPackage);
	pXTPPackage->MakePackage();
	m_pPublishFlow->Append(pXTPPackage->Address(), pXTPPackage->Length());
}

int CFrontForwarder::ForwardQuery(CXTPPackage *pXTPPackage)
{
	pXTPPackage->GetXTPHeader()->Type = XTP_REQUEST;
	return m_pFibClientApi->Request(m_nQueryServerID, pXTPPackage);
}

void CFrontForwarder::SetCommPhaseNo(WORD nCommPhaseNo)
{
	m_pPublishFlow->SetCommPhaseNo(nCommPhaseNo);
}
