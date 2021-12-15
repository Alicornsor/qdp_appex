// NsSession.h: interface for the CNsSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NSSESSION_H__A1BCFDA2_51EF_4C57_9D8A_2E96155CEA88__INCLUDED_)
#define AFX_NSSESSION_H__A1BCFDA2_51EF_4C57_9D8A_2E96155CEA88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Session.h"
#include "NsProtocol.h"

class CNsSession;
class CNsSessionCallback
{
public:
	virtual int HandlePackage(CNsPackage *pNsPackage, CNsSession *pSession) = 0;
};


class CNsSession : public CSession, public CProtocolCallback  
{
public:
	CNsSession(CReactor *pReactor,CChannel *pChannel);
	virtual ~CNsSession();
	virtual int HandlePackage(CPackage *pPackage,CProtocol *pProtocol);
	void RegisterPackageHandler(CNsSessionCallback *pPackageHandler);
	void Send(CNsPackage *pPackage);

protected:
	CNsProtocol *m_pNsProtocol;
	CNsSessionCallback *m_pPackageHandler;
};

#endif // !defined(AFX_NSSESSION_H__A1BCFDA2_51EF_4C57_9D8A_2E96155CEA88__INCLUDED_)
