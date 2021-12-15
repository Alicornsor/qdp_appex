// EventDispatcher.h: interface for the CEventDispatcher class.
//
// 20081223 hwp  NT-0061: 修正线程安全结束问题，增加保护线程运行状态
//                  的互斥量
// 20090510 hwp  NT-0074：DispatchIOs改为私有方法
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTDISPATCHER_H__B37EDF0F_3FEF_442A_A5C9_C68C301EF606__INCLUDED_)
#define AFX_EVENTDISPATCHER_H__B37EDF0F_3FEF_442A_A5C9_C68C301EF606__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"
#include "EventHandler.h"
#include "EventQueue.h"
#include "TimerQueue.h"

const int SM_USER		= 0x1000;


class CEventDispatcher : public CThread  
{
public:
	CEventDispatcher();
	virtual ~CEventDispatcher();

	/**注册一个定时类可运行对象
	* @param pEventHandler 定时器的指针 
	* @param nIDEvent 定时器的标示 
	* @param nElapse 定时器的时间间隔 毫秒
	*/
	void RegisterTimer(CEventHandler *pEventHandler, int nIDEvent, int nElapse);

	/**从定时器链表中移去一个定时器对象
	* @param pEventHandler 定时器对象的指针 
	* @param nIDEvent 定时器在CReatctor的标示，=0 移去该定时器所有注册
	*        >0 移去该定时器指定注册
	*/
	void RemoveTimer(CEventHandler *pEventHandler, int nIDEvent);
	
	/*向EventHandler发送异步事件
	* @param pEventHander 目标EventHandler
	* @param nEventID 事件ID
	* @param dwParam 双字型参数
	* @param pParam 无符号指针型参数
	*/
	bool PostEvent(CEventHandler *pEventHandler, int nEventID, DWORD dwParam, void *pParam);

	/*向EventHandler发送同步事件
	* @param pEventHander 目标EventHandler
	* @param nEventID 事件ID
	* @param dwParam 双字型参数
	* @param pParam 无符号指针型参数
	*/
	int SendEvent(CEventHandler *pEventHandler, int nEventID, DWORD dwParam, void *pParam);

	/**没有事件处理器处理该事件时，由Reactor本身处理这条事件,
	* @param nEventID 事件ID
	* @param dwParam 第一个参数
	* @param pParam 第二个参数
	* @return 处理结果
	*/
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);
	
	/**清除一个失效的EventHandler发出的所有的事件
	* @param pEventHander 失效的EventHandler
	*/
	inline void ClearEvent(CEventHandler *pEventHandler);
	/**CReactor开始工作
	*/
	virtual void Run();
	
	/**获取当前系统时间
	* @return 当前系统时间
	*/
	inline DWORD Time();

	/**获取当前系统时间的毫秒部分
	* @return 当前系统时间的毫秒部分
	*/
	inline DWORD GetMilTime();
	
	/**获取当前系统滴哒数
	*@return  当前系统滴哒数（以毫秒计)
	*/
	inline DWORD GetClock();
	
	/**终止程序主循环
	*/
	void Stop(DWORD nStopCode = 0);
	
	inline DWORD GetStopCode();
protected:
	/**检查定时器链表是否有到期事件，如有则执行定时处理器的OnTimer()方法
	*/
	void CheckTimer();
	
	/**获取当前系统时间
	*/
	inline void SyncTime();

	/**从事件队列中取出事件，分派给相应的事件处理器
	*/
	void DispatchEvents();
private:
	virtual void DispatchIOs() = 0;

protected:
	bool m_bShouldRun;				/**< 循环运行标志 */
	DWORD m_nCurrMilTime;			/**< 当前系统时间毫秒*/
	DWORD m_nCurrTime;				/**< 当前系统时间秒*/
	DWORD m_nCurrClock;				/**< 当前系统滴哒数*/

	CEventQueue m_queueEvent;		/**< 事件队列*/
	CTimerQueue *m_pTimerQueue;

	DWORD m_nStopCode;

	CMutex m_lockActive;
};

inline DWORD CEventDispatcher::Time()
{
	return m_nCurrTime;
}

inline DWORD CEventDispatcher::GetMilTime()
{
	return m_nCurrMilTime;
}

inline DWORD CEventDispatcher::GetClock()
{
	return m_nCurrClock;
}

inline void CEventDispatcher::SyncTime()
{
#ifdef WIN32	
   struct _timeb timebuffer;
   _ftime( &timebuffer );
	m_nCurrTime = (DWORD)timebuffer.time;	
	m_nCurrMilTime = timebuffer.millitm;
	m_nCurrClock = m_nCurrTime*1000 + timebuffer.millitm;
#else
	struct timeval timeout;
  gettimeofday(&timeout, 0);
	m_nCurrTime = timeout.tv_sec;	
	m_nCurrMilTime = timeout.tv_usec/1000;
	m_nCurrClock = m_nCurrTime*1000 + timeout.tv_usec/1000;
#endif
}

inline void CEventDispatcher::ClearEvent(CEventHandler *pEventHandler)
{
	m_queueEvent.ClearEvent(pEventHandler);
}

inline DWORD CEventDispatcher::GetStopCode()
{
	return m_nStopCode;
}

#endif // !defined(AFX_EVENTDISPATCHER_H__B37EDF0F_3FEF_442A_A5C9_C68C301EF606__INCLUDED_)
