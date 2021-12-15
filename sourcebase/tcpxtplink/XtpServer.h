#ifndef __XtpServer_H__
#define __XtpServer_H__

#include "SessionFactory.h"
#include "customDataType.h"
#include "TcpXtpSession.h"
#include "Reactor.h"
#include "CachedFileFlow.h"
#include "XtpPackageDesc.h"

class CXtpServerCallback
{
public:
	virtual int getnMaxLocalID(const char * nSeatID)= 0;
	virtual ~CXtpServerCallback(){};
};

class CXtpServer : public CSessionFactory,public CTcpXtpSessionCallback
{
public:
	CXtpServer(CReactor *pReactor,CFlow *pSubFlow,CSelectReactor* pConnReactor=NULL);
	~CXtpServer();
	virtual int HandlePackage(CXTPPackage *pPackage, CTcpXtpSession *pSession);
	int OnReqClientLogin(CXTPPackage *pPackage, CTcpXtpSession *pSession);
	void Init(char *tmpAddress);
	void SetSubjectID(DWORD nSubjectID);
	void setXtpServerCallback(CXtpServerCallback *XtpServerCallback);

protected:
	virtual CSession *CreateSession(CChannel *pChannel, DWORD bIsListener);
	virtual void OnSessionConnected(CSession *pSession);
	virtual void OnSessionDisconnected(CSession *pSession, int nReason);
	
private:
	DWORD m_nSubjectID;
	CFlow *m_pSubFlow;
	CXTPPackage m_XtpPackage;
	char m_tmpAddress[256];
	CXtpServerCallback *m_pServerCallBack;
};

#endif