// EventQueue.h: interface for the CEventQueue class .
//
// 20090316 hwp  增加Empty方法，用以判断消息队列是否为空(NT-0069)
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTQUEUE_H__EE2334FD_F12F_46B4_9FA2_77C71AEB11BB__INCLUDED_)
#define AFX_EVENTQUEUE_H__EE2334FD_F12F_46B4_9FA2_77C71AEB11BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Semaphore.h"
#include "Mutex.h"
#include "EventHandler.h"

struct CSyncEvent
{
	CEvent event;
	CSemaphore sem;
	int nRetval;
	CSyncEvent *pNext;
};

class  CEventQueue  
{
public:
	CEventQueue(int nQueueSize);
	virtual ~CEventQueue();

	bool AddPostEvent(CEventHandler *pEventHandler, int nEventID, DWORD dwParam, void *pParam);
	bool AddSyncEvent(CSyncEvent *pEvent);
	bool PeekEvent(CEvent &event);

	void ClearEvent(CEventHandler *pEventHandler);
	void RemoveAll();
	bool Empty();
protected:
	CEvent *m_pPostEvent;
	int m_nEventSize;
	int m_nReadPos;
	int m_nWritePos;

	CSyncEvent *m_pFirstSyncEvent;
	CSyncEvent *m_pLastSyncEvent;

	CMutex m_lock;
};

#endif // !defined(AFX_EVENTQUEUE_H__EE2334FD_F12F_46B4_9FA2_77C71AEB11BB__INCLUDED_)
