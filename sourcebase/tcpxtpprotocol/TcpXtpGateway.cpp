#include "public.h"
#include "TcpXtpGateway.h"
#include "XtpData.h"


CTcpXtpGateway::CTcpXtpGateway(CReactor *pReactor,CFlow *pMemFlow,CSelectReactor* pConnReactor):CSessionFactory(pReactor, 500,pConnReactor)
{
	m_pMemFlow=pMemFlow;
	m_SendPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE+4000,1000);
	m_pReactor = pReactor;
	m_nSubjectID = 0;
}

CTcpXtpGateway::~CTcpXtpGateway()
{

}

void  CTcpXtpGateway::Init()
{
	m_pReactor->Create();
	Start();
}

void CTcpXtpGateway::SetSubjectID(DWORD nSubjectID)
{
	m_nSubjectID = nSubjectID;
}

CSession *CTcpXtpGateway::CreateSession(CChannel *pChannel, DWORD bIsListener)
{
	CTcpXtpSession *pSession =  new CTcpXtpSession(m_pReactor, pChannel,this,m_nSubjectID);
	return pSession;
}

void CTcpXtpGateway::OnSessionConnected(CSession *pSession)
{
	//先调用基类的方法
	CSessionFactory::OnSessionConnected(pSession);
}

void CTcpXtpGateway::OnSessionDisconnected(CSession *pSession, int nReason)
{
	//最后调用基类的方法
	CSessionFactory::OnSessionDisconnected(pSession, nReason);	
}

int CTcpXtpGateway::HandlePackage(CXTPPackage *pPackage, CTcpXtpSession *pSession)
{	
	switch(pPackage->GetTid()) 
	{
	case FID_LifeCycleID:
		OnReqClientLogin(pPackage, pSession);
		break;
	default:
		break;
	}
	return 0;
}

int CTcpXtpGateway::OnReqClientLogin(CXTPPackage *pPackage, CTcpXtpSession *pSession)
{
	CLifeCycleIDField field;
	if (XTP_GET_SINGLE_FIELD(pPackage, &field) <= 0)
	{
		return 0;
	}

	REPORT_EVENT(LOG_CRITICAL, "Init", "receive TCP sub request, LifeCycleID:%d\n",field.LifeCycleID.getValue());	
	if (field.LifeCycleID.getValue()<0)
		pSession->PublishFlow(m_pMemFlow,0);
	else
		pSession->PublishFlow(m_pMemFlow,field.LifeCycleID.getValue());
	return 0;
}

