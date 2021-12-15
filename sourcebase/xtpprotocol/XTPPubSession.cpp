// XTPPubSession.cpp: implementation of the CXTPPubSession class.
//
// 20080620 hwp CProtocol不再自动删除上层协议，m_pControlProtocol要
//                 自行删除
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "XTPPubSession.h"
#include "SCPPackageDesc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CXTPPubSession::CXTPPubSession(CReactor *pReactor, CChannel *pChannel,
							   CXTPFlowManager *pFlowManager)
:CXTPSession(pReactor, pChannel)
{
	m_pFlowManager = pFlowManager;
 	m_pControlProtocol = new CSCPProtocol(pReactor);
	m_pControlProtocol->AttachLower(m_pXMPProtocol, XMPTypeSCP);
	m_controlPackage.ConstructAllocate(SCP_PACKAGE_MAX_SIZE, m_pControlProtocol->GetHdrReserveLen());
	m_pControlProtocol->RegisterUpperHandler(this);
	m_pXMPProtocol->EnableHeartbeat(false);
}

CXTPPubSession::~CXTPPubSession()
{
	delete m_pControlProtocol;
}

int CXTPPubSession::HandlePackage(CPackage *pPackage, CProtocol *pProtocol)
{
	if (m_pControlProtocol == pProtocol)
	{
		CSCPPackage *pSCPPackage = (CSCPPackage *)pPackage;
//		DEBUG_LOG1("STID = %04x\n", pSCPPackage->GetTid());
		switch(pSCPPackage->GetTid()) 
		{
		case STID_SUBSCRIBE:
			OnSubscribeReq(pSCPPackage);
			break;
		case STID_UN_SUBSCRIBE:
			OnUnSubscribeReq(pSCPPackage);
			break;
		case STID_PUBLISH:
			OnHeartBeat(pSCPPackage);
			break;
		case STID_ACK:
			OnAck(pSCPPackage);
			break;
		default:
			break;
		}

		return 0;
	}
	
	return CXTPSession::HandlePackage(pPackage, pProtocol);
}

void CXTPPubSession::OnSubscribeReq(CSCPPackage *pPackage)
{
	CSCPSubscribeField subscribeField;
	CNamedFieldIterator i = pPackage->GetNamedFieldIterator(&subscribeField.m_Describe);

	while (!i.IsEnd()) 
	{
		i.Retrieve(&subscribeField);

		if (m_pFlowManager == NULL)
		{
			break;
		}
		CReadOnlyFlow *pFlow = m_pFlowManager->GetFlow(subscribeField.SubjectID);
		if (pFlow != NULL) 
		{
			NET_STATUS_LOG3("publish : reqCommPase[%d] SubscriberID[%x] startid[%d]\n", 
				(const WORD)subscribeField.CommPhaseNo,
				(const WORD)subscribeField.SubscriberID,
				(const int)subscribeField.StartID);
			Publish(pFlow, subscribeField.SubjectID, subscribeField.CommPhaseNo, 
				subscribeField.SubscriberID, subscribeField.StartID);		
		}
		i.Next();
	}
}

void CXTPPubSession::OnUnSubscribeReq(CSCPPackage *pPackage)
{
	CSCPSubscribeField subscribeField;
	CNamedFieldIterator i = pPackage->GetNamedFieldIterator(&subscribeField.m_Describe);

	while (!i.IsEnd()) 
	{
		i.Retrieve(&subscribeField);

		UnPublish(subscribeField.SubjectID);

		i.Next();
	}	
}

void CXTPPubSession::OnHeartBeat(CSCPPackage *pPackage)
{
	CSCPPublishField publishField;
	CNamedFieldIterator i = pPackage->GetNamedFieldIterator(&publishField.m_Describe);

	while (!i.IsEnd()) 
	{
		i.Retrieve(&publishField);

		CXTPSession::OnHeartBeat(publishField.SubjectID, publishField.CommPhaseNo, publishField.SeqNo);

		i.Next();
	}
}

void CXTPPubSession::OnAck(CSCPPackage *pPackage)
{
	CSCPSubscribeField subscribeField;
	CNamedFieldIterator i = pPackage->GetNamedFieldIterator(&subscribeField.m_Describe);

	while (!i.IsEnd()) 
	{
		i.Retrieve(&subscribeField);

		CXTPSession::OnAck(subscribeField.SubscriberID, subscribeField.SubjectID, 
			subscribeField.StartID, subscribeField.CommPhaseNo);

		i.Next();
	}
}

void CXTPPubSession::RegisterSubscriber(CSubscriber *pSubscriber, DWORD dwSubscriberID)
{
	CXTPSession::RegisterSubscriber(pSubscriber, dwSubscriberID);
	SendSubscribeReq(pSubscriber->GetSubjectID(),
		pSubscriber->GetCommPhaseNo(),
		dwSubscriberID,
		pSubscriber->GetReceivedCount());
}

void CXTPPubSession::UnRegisterSubscriber( CSubscriber *pSubscriber)
{
	CXTPSession::UnRegisterSubscriber(pSubscriber);
	SendUnSubscribeReq(pSubscriber->GetSubjectID());
}


CSCPPackage *CXTPPubSession::PrepareControlPackage(WORD stid)
{
	m_controlPackage.AllocateMax();
	m_controlPackage.Truncate(0);
	m_controlPackage.SetTid(stid);
	return &m_controlPackage;
}

void CXTPPubSession::SendControlPackage(CSCPPackage *pPackage)
{
	m_pControlProtocol->Send(pPackage);
}

void CXTPPubSession::SendSubscribeReq(DWORD nSubjectID, WORD nCommPhaseNo, DWORD dwSubscriberID, DWORD nStartID)
{
//	DEBUG_LOG3("SendSubscribeReq SubjectID:[%x], CommPhaseNo[%d], StartID:[%d]\n",
//		nSubjectID, nCommPhaseNo, nStartID);

	CSCPSubscribeField subscribeField;
	subscribeField.SubjectID = nSubjectID;
	subscribeField.StartID = nStartID;
	subscribeField.CommPhaseNo = nCommPhaseNo;
	subscribeField.SubscriberID = dwSubscriberID;

	CSCPPackage *pPackage = PrepareControlPackage(STID_SUBSCRIBE);
	SCP_ADD_FIELD(pPackage, &subscribeField);

	SendControlPackage(pPackage);

}

void CXTPPubSession::SendUnSubscribeReq(DWORD nSubjectID)
{
	CSCPSubscribeField subscribeField;
	subscribeField.SubjectID = nSubjectID;
	subscribeField.StartID = 0;

	CSCPPackage *pPackage = PrepareControlPackage(STID_UN_SUBSCRIBE);
	SCP_ADD_FIELD(pPackage, &subscribeField);

	SendControlPackage(pPackage);

}

void CXTPPubSession::SendNak(DWORD nSubjectID, WORD nCommPhaseNo, DWORD dwSubscriberID, DWORD nSeqNo)
{
	SendSubscribeReq(nSubjectID, nCommPhaseNo, dwSubscriberID, nSeqNo);
}

void CXTPPubSession::SendAck(DWORD nSubjectID, WORD nCommPhaseNo, DWORD dwSubscriberID, DWORD nSeqNo)
{
	CSCPSubscribeField subscribeField;
	subscribeField.SubjectID = nSubjectID;
	subscribeField.StartID = nSeqNo;
	subscribeField.CommPhaseNo = nCommPhaseNo;
	subscribeField.SubscriberID = dwSubscriberID;

	CSCPPackage *pPackage = PrepareControlPackage(STID_ACK);
	SCP_ADD_FIELD(pPackage, &subscribeField);

	SendControlPackage(pPackage);

}

void CXTPPubSession::SendHeartBeat(DWORD nSubjectID, WORD nCommPhaseNo, DWORD nSeqNo)
{
	CSCPPublishField publishField;
	publishField.CommPhaseNo = nCommPhaseNo;
	publishField.SubjectID = nSubjectID;
	publishField.SeqNo = nSeqNo;

	CSCPPackage *pPackage = PrepareControlPackage(STID_PUBLISH);
	SCP_ADD_FIELD(pPackage, &publishField);

	SendControlPackage(pPackage);
}
