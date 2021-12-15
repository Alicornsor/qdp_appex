#include "public.h"
#include "GatewayServer.h"
#include "XtpData.h"


CGateWayServer::CGateWayServer(CReactor *pReactor,CFlow *pDownFlow,CFrontForwarder *pFrontForwarder):CSessionFactory(pReactor,5000)
{
	m_pDownFlow = pDownFlow;
	m_SendPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE+4000,1000);
	m_pReactor = pReactor;
	m_nSubjectID = 0;
	m_pFrontForwarder = pFrontForwarder;
}

CGateWayServer::~CGateWayServer()
{
	m_mapFrontSession.Clear();
}

void CGateWayServer::Init()
{
	m_pReactor->Create();
	Start();
}

void CGateWayServer::SetSubjectID(DWORD nSubjectID)
{
	m_nSubjectID = nSubjectID;
}

CSession *CGateWayServer::CreateSession(CChannel *pChannel, DWORD bIsListener)
{
	CTcpXtpSession *pSession =  new CTcpXtpSession(m_pReactor, pChannel,this,m_nSubjectID);
	return pSession;
}

int CGateWayServer::HandlePackage(CXTPPackage *pPackage, CTcpXtpSession *pSession)
{	
	switch(pPackage->GetTid()) 
	{
	case TID_InnerLogin:
		OnReqClientLogin(pPackage, pSession);
		break;
	default:
		{
			//直接向上转发
//			printf("向上转发%0x\n", pPackage->GetTid());
			m_pFrontForwarder->ForwardTransaction(pPackage);
			break;
		}
	}
	return 0;
}

int CGateWayServer::OnReqClientLogin(CXTPPackage *pPackage, CTcpXtpSession *pSession)
{
	CInnerLoginField field;
	if (XTP_GET_SINGLE_FIELD(pPackage, &field) <= 0)
	{
		return 0;
	}

	DWORD frontid = pPackage->GetFrontID();
	REPORT_EVENT(LOG_CRITICAL, "Init", "receive TCP sub request,frontid:%d, sequenceno:%d\n",frontid, field.SequenceNo.getValue());	

	if (field.SequenceNo.getValue()<0)
		pSession->PublishFlow(m_pDownFlow,0);
	else
		pSession->PublishFlow(m_pDownFlow,field.SequenceNo.getValue());

	//增加session号,如果存在则替换为新的Session
	CTcpXtpSession **tmpSession = m_mapFrontSession.Find(frontid);
	if(tmpSession == NULL)
	{
		m_mapFrontSession.Insert(frontid,pSession);
	}
	else
	{
		*tmpSession = pSession;
	}	
	return 0;
}


CTcpXtpSession* CGateWayServer::GetTcpXtpSession(DWORD nFrontID)
{
	CTcpXtpSession **pSession = m_mapFrontSession.Find(nFrontID);
	if(pSession == NULL)
	{
		return NULL;
	}
	else
	{
		return *pSession;
	}
}
