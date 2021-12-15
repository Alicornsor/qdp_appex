// SelectReactor.h: interface for the CSelectReactor class.
//
// 20090316 hwp  增加虚拟函数GetSelectTimeOut，使派生类可以在主循环中
//                  插入自己的处理，并可控制select的超时时间（NT-0069）
// 20090510 hwp  NT-0074：取消GetSelectTimeOut函数，根据HandleOtherTask
//                  返回值决定Select超时时间   
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELECTREACTOR_H__0EB9BAD9_FE38_4CE1_9923_9FB932010E5B__INCLUDED_)
#define AFX_SELECTREACTOR_H__0EB9BAD9_FE38_4CE1_9923_9FB932010E5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Reactor.h"
#include "SocketInit.h"

class CSelectReactor : public CReactor  
{
public:
	CSelectReactor(bool bBindThreadsToCPU=false);
	virtual ~CSelectReactor();

	void SetNoShmChannelFlag(bool bFlag);

protected:
	bool  m_bWait;
	bool  m_bBindThreadsToCPU ;
private:
	virtual void DispatchIOs();
	void PrepareIds(fd_set &readfds,fd_set  &writefds, int &MaxID);
	void DispatchIO(fd_set &readfds,fd_set  &writefds, int &MaxID);
	bool m_bNoShmChannelFlag;

};

#endif // !defined(AFX_SELECTREACTOR_H__0EB9BAD9_FE38_4CE1_9923_9FB932010E5B__INCLUDED_)
