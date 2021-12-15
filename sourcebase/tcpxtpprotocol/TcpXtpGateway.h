#ifndef __CTcpXtpGateway_H__
#define __CTcpXtpGateway_H__

#include "SessionFactory.h"
#include "customDataType.h"
#include "TcpXtpSession.h"
#include "Reactor.h"
#include "CachedFileFlow.h"


class CTcpXtpGateway : public CSessionFactory,public CTcpXtpSessionCallback
{
public:
	CTcpXtpGateway(CReactor *pReactor,CFlow *pMemFlow,CSelectReactor* pConnReactor=NULL);
	~CTcpXtpGateway();
	virtual int HandlePackage(CXTPPackage *pPackage, CTcpXtpSession *pSession);
	int OnReqClientLogin(CXTPPackage *pPackage, CTcpXtpSession *pSession);
	void  Init();
	void SetSubjectID(DWORD nSubjectID);
protected:
	virtual CSession *CreateSession(CChannel *pChannel, DWORD bIsListener);
	virtual void OnSessionConnected(CSession *pSession);
	virtual void OnSessionDisconnected(CSession *pSession, int nReason);
	
private:
	CFlow   *m_pMemFlow;
	CXTPPackage  m_SendPackage;
	//CReactor  * m_pReactor;
	DWORD m_nSubjectID;
};
#endif
