// NsSessionFactory.h: interface for the CNsSessionFactory class.
//
///20080727 hwp NT-0048 : 配合CSessionFactory的修改，注册地址时增加标记参数，
///                在连接成功时会返回，以区分通过不同地址创建的连接
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NSSESSIONFACTORY_H__B6E230B2_75D9_4E73_ABBF_2E6DB4EC6FDA__INCLUDED_)
#define AFX_NSSESSIONFACTORY_H__B6E230B2_75D9_4E73_ABBF_2E6DB4EC6FDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SessionFactory.h"
#include "NsSession.h"


class CNsSessionFactory : public CSessionFactory, public CNsSessionCallback 
{
public:
	CNsSessionFactory(CReactor *pReactor, int nMaxSession,CSelectReactor* pConnReactor=NULL);
	virtual ~CNsSessionFactory();
	void RegisterNameServer(char *location, DWORD dwMark=0);
	virtual int HandlePackage(CNsPackage *pNsPackage, CNsSession *pSession);
	virtual void OnTimer(int nIDEvent);
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);

protected:
	CConnecterManager *m_pNsConnecterManager;
	CNsSession *m_pNsSession;
	bool m_bInQueryNs;
};

#endif // !defined(AFX_NSSESSIONFACTORY_H__B6E230B2_75D9_4E73_ABBF_2E6DB4EC6FDA__INCLUDED_)
