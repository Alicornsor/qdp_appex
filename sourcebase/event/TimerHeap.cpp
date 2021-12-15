// TimerHeap.cpp: implementation of the CTimerHeap class.
//
// 2006.12.15 hwp 修改毫秒溢出时定时器失效的问题
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "TimerHeap.h"

const DWORD MAX_TIMER_HEAP_TIMEOUT = 3600*24*1000;	//定时器最大不能起过一天
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTimerHeap::CTimerHeap(DWORD nClock)
{
	m_nClock = 0;
	m_nClockAlter = nClock;
}

CTimerHeap::~CTimerHeap()
{

}

void CTimerHeap::RegisterTimer(CEventHandler *pEventHandler, int nIDEvent, int nElapse)
{
	CTimerHeapNode node;
	node.nElapse = nElapse;
	node.nIDEvent = nIDEvent;
	node.pTimer = pEventHandler;
	node.nExpire = m_nClock + nElapse;

	push(node);
}

void CTimerHeap::RemoveTimer(CEventHandler *pEventHandler, int nIDEvent)
{
	for (int i=0; i<size(); i++)
	{
		CTimerHeapNode &node = c[i];
		if (node.pTimer == pEventHandler && 
			(nIDEvent == 0 || node.nIDEvent == nIDEvent))
		{
			node.pTimer = NULL;
		}
	}
}

bool CTimerHeap::CheckExpire(DWORD nClock)
{
	if (size() > 0)
	{
		CTimerHeapNode node = top();
		if (node.nExpire <= m_nClock)
		{
			return true;
		}
		else
			return false;
	}
	else
		return false;
}


void CTimerHeap::Expire(DWORD nClock)
{
	SyncTime(nClock);

	while (size() > 0)
	{
		CTimerHeapNode node = top();
		if (node.nExpire > m_nClock)
		{
			//最近的定时器尚未到期，不需要做更多的检查了
			break;
		}
		
		pop();

		if (node.pTimer != NULL)
		{
			node.nExpire = m_nClock + node.nElapse;

			push(node);

			node.pTimer->OnTimer(node.nIDEvent);
		}		
	}
}

void CTimerHeap::SyncTime(DWORD nClock)
{
	m_nClock = nClock - m_nClockAlter;
	if (m_nClock > MAX_TIMER_HEAP_TIMEOUT)
	{
		vector<CTimerHeapNode> tmpNodes;
		while (size() > 0)
		{
			tmpNodes.push_back(top());
			pop();
		}
		for (int i=0; i<tmpNodes.size(); i++)
		{
			if (tmpNodes[i].nExpire <= m_nClock)
			{
				tmpNodes[i].nExpire = 0;
			}
			else
			{
				tmpNodes[i].nExpire -= m_nClock;
			}
			push(tmpNodes[i]);
		}
		m_nClockAlter += m_nClock;
		m_nClock = 0;
	}

}

