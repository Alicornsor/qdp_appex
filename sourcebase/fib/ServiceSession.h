// ServiceSession.h: interface for the CServiceSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVICESESSION_H__B0A7A27C_EF9F_45DA_AC06_2906B710C225__INCLUDED_)
#define AFX_SERVICESESSION_H__B0A7A27C_EF9F_45DA_AC06_2906B710C225__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPSession.h"

class CServiceSession : public CXTPSession
{
public:
	CServiceSession(CReactor *pReactor, CChannel *pChannel);
	virtual ~CServiceSession();
	virtual void SendNak(DWORD nSubjectID, WORD nCommPhaseNo, DWORD dwSubscriberID,
		DWORD nSeqNo);
	virtual void SendAck(DWORD nSubjectID, WORD nCommPhaseNo, DWORD dwSubscriberID,
		DWORD nSeqNo);;
	virtual void SendHeartBeat(DWORD nSubjectID, DWORD nSeqNo);
};

#endif // !defined(AFX_SERVICESESSION_H__B0A7A27C_EF9F_45DA_AC06_2906B710C225__INCLUDED_)
