// ServiceSession.cpp: implementation of the CServiceSession class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "ServiceSession.h"
#include "SCPProtocol.h"
#include "SCPPackageDesc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServiceSession::CServiceSession(CReactor *pReactor, CChannel *pChannel)
:CXTPSession(pReactor, pChannel)
{
}

CServiceSession::~CServiceSession()
{

}

void CServiceSession::SendNak(DWORD nSubjectID, WORD nCommPhaseNo, DWORD dwSubscriberID,
							  DWORD nSeqNo)
{
	//不需要保证可靠传输，什么也不用做
}

void CServiceSession::SendAck(DWORD nSubjectID, WORD nCommPhaseNo, DWORD dwSubscriberID,
							  DWORD nSeqNo)
{
	//不需要保证可靠传输，什么也不用做
}

void CServiceSession::SendHeartBeat(DWORD nSubjectID, DWORD nSeqNo)
{
	//不需要心跳，什么也不用做
}
