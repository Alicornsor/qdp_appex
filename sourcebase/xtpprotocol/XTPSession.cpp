// XTPSession.cpp: implementation of the CXTPSession class.
//
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "XTPPackage.h"
#include "XTPSession.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CXTPSession::CXTPSession(CReactor *pReactor,CChannel *pChannel)
:CXMPSession(pReactor, pChannel)
{
	m_pXTPProtocol = new CXTPProtocol(m_pReactor, this, this);
	m_pXTPProtocol->AttachLower(m_pXMPProtocol, XMPTypeXTP);
	m_pXTPProtocol->RegisterErrorHandler(this);
	m_pXTPProtocol->RegisterUpperHandler(this);
	
	m_pReqHandler = NULL;
	m_pRspHandler = NULL;
	
}

CXTPSession::~CXTPSession()
{
	delete m_pXTPProtocol;
}

int CXTPSession::HandleEvent(int nEventID, DWORD dwParam, void *pParam)
{
	switch(nEventID)
	{
	case MSG_XMPERR_RECVHEARTBEAT:
	case MSG_XMPERR_SENDHEARTBEAT:
	case MSG_XMPERR_BADPACKAGE:
	case MSG_XTPERR_BADPACKAGE:
		m_pChannel->Disconnect();
		OnChannelLost(nEventID);
		delete this;
		return 0;
	}

	return CSession::HandleEvent(nEventID, dwParam, pParam);
}	

void CXTPSession::RegisterReqHandler(CXTPReqCallback *pReqHandler)
{
	m_pReqHandler = pReqHandler;
}

void CXTPSession::RegisterRspHandler(CXTPRspCallback *pRspHandler)
{
	m_pRspHandler = pRspHandler;
}

int CXTPSession::HandlePackage(CPackage *pPackage,CProtocol *pProtocol)
{
	if (pProtocol == m_pXTPProtocol)
	{
		CXTPPackage *pXTPPacakge = (CXTPPackage *)pPackage;
		if (pXTPPacakge->GetXTPHeader()->Type == XTP_REQUEST)
		{
			if (m_pReqHandler == NULL)
			{
				return 0;
			}
			return m_pReqHandler->HandleRequest(pXTPPacakge, this);
		}
		else
		{
			if (m_pRspHandler == NULL)
			{
				return 0;
			}
			return m_pRspHandler->HandleResponse(pXTPPacakge, this);
		}
	}
	return 0;
}


void CXTPSession::Publish(CReadOnlyFlow *pFlow, DWORD nSubjectID, WORD nCommPhaseNo, 
						  DWORD dwSubscriberID, int nStartId)
{
	m_pXTPProtocol->Publish(pFlow, nSubjectID, nCommPhaseNo, dwSubscriberID, nStartId);
}

void CXTPSession::UnPublish(DWORD nSubjectID)
{
	m_pXTPProtocol->UnPublish(nSubjectID);
}

CXTPPackage *CXTPSession::CreatePackage()
{
	CXTPPackage *pPackage = new CXTPPackage;
	pPackage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE, m_pXTPProtocol->GetHdrReserveLen());
	return pPackage;
}

void CXTPSession::SendRequestPackage(CXTPPackage *pPackage)
{
	m_pXTPProtocol->Send(pPackage);
}

void CXTPSession::RegisterSubscriber(CSubscriber *pSubscriber, DWORD dwSubscriberID)
{
	m_pXTPProtocol->RegisterSubscriber(pSubscriber, dwSubscriberID);
}

void CXTPSession::UnRegisterSubscriber(CSubscriber *pSubscriber)
{
	m_pXTPProtocol->UnRegisterSubscriber(pSubscriber);
}

void CXTPSession::OnHeartBeat(DWORD nSubjectID, WORD nCommPhaseNo, int nSeqNo)
{
	m_pXTPProtocol->OnHeartBeat( nSubjectID, nCommPhaseNo,nSeqNo);
}

void CXTPSession::OnAck(DWORD dwSubscriberID, DWORD dwSubjectID, 
		int nStartId, WORD wCommPhaseNo)
{
	m_pXTPProtocol->OnAck(dwSubscriberID, dwSubjectID, nStartId, wCommPhaseNo);
}

void CXTPSession::SetSubCommPhaseNo(WORD nCommPhaseNo)
{
	m_pXTPProtocol->SetSubCommPhaseNo(nCommPhaseNo);
}
