// NsSession.cpp: implementation of the CNsSession class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "NsSession.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNsSession::CNsSession(CReactor *pReactor,CChannel *pChannel)
:CSession(pReactor, pChannel, NS_PACKAGE_MAX_SIZE)
{
	m_pNsProtocol = new CNsProtocol(pReactor);
	m_pNsProtocol->AttachLower(m_pChannelProtocol, 0);
	m_pNsProtocol->RegisterErrorHandler(this);
	m_pNsProtocol->RegisterUpperHandler(this);

	m_pPackageHandler = NULL;
}

CNsSession::~CNsSession()
{
	// longqy 2013-02-19
	delete m_pNsProtocol;
}

void CNsSession::RegisterPackageHandler(CNsSessionCallback *pPackageHandler)
{
	m_pPackageHandler = pPackageHandler;
}

int CNsSession::HandlePackage(CPackage *pPackage,CProtocol *pProtocol)
{
	if (pProtocol == m_pNsProtocol)
	{
		CNsPackage *pNsPacakge = (CNsPackage *)pPackage;
		if (m_pPackageHandler == NULL)
		{
			return 0;
		}
		return m_pPackageHandler->HandlePackage(pNsPacakge, this);
	}
	return 0;
}

void CNsSession::Send(CNsPackage *pPackage)
{
	m_pNsProtocol->Send(pPackage);
}

