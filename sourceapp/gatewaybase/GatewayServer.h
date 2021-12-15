#ifndef __CGateWayServer_H__
#define __CGateWayServer_H__

#include "SessionFactory.h"
#include "customDataType.h"
#include "TcpXtpSession.h"
#include "Reactor.h"
#include "CachedFileFlow.h"
#include "XtpPackageDesc.h"
#include "FrontForwarder.h"

class CGateWayServer : public CSessionFactory,public CTcpXtpSessionCallback
{
public:
	CGateWayServer(CReactor *pReactor,CFlow *pDownFlow,CFrontForwarder *pFrontForwarder);
	~CGateWayServer();
	virtual int HandlePackage(CXTPPackage *pPackage, CTcpXtpSession *pSession);
	int OnReqClientLogin(CXTPPackage *pPackage, CTcpXtpSession *pSession);
	void  Init();
	void SetSubjectID(DWORD nSubjectID);

protected:
	virtual CSession *CreateSession(CChannel *pChannel, DWORD bIsListener);
	CTcpXtpSession *GetTcpXtpSession(DWORD nFrontID);

private:
	//��client���͵���ˮ
	CFlow   *m_pDownFlow;

	CXTPPackage  m_SendPackage;
	//CReactor  * m_pReactor;
	DWORD m_nSubjectID;

	CFrontForwarder *m_pFrontForwarder;

	//�����ϵ�����gateway���б�
	typedef CHashMap<DWORD, CTcpXtpSession*, HashInt> CTcpXtpSessionMap;
	CTcpXtpSessionMap m_mapFrontSession;	
};
#endif
