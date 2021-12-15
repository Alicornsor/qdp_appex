// EpollReactor.h: interface for the CEpollReactor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EPOLLREACTOR_H__67EDBACC_3980_4295_9574_9C48D62E979B__INCLUDED_)
#define AFX_EPOLLREACTOR_H__67EDBACC_3980_4295_9574_9C48D62E979B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef LINUX

#include "Reactor.h"
#include <sys/epoll.h>

const int EPOLL_MAX_EVENTS = 4096;

class CEpollReactor : public CReactor  
{
public:
	CEpollReactor();
	virtual ~CEpollReactor();
	virtual void RegisterIO(CEventHandler *pEventHandler);
	virtual void RemoveIO(CEventHandler *pEventHandler);
private:
	virtual void DispatchIOs();
private:
	int m_fdEpoll;
	typedef map<CEventHandler *, int> CEventHandlerIdMap;
	CEventHandlerIdMap m_mapEventHandlerId;
};

#endif

#endif // !defined(AFX_EPOLLREACTOR_H__67EDBACC_3980_4295_9574_9C48D62E979B__INCLUDED_)
