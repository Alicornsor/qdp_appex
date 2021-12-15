// Semaphore.h: interface for the CSemaphore class .
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEMAPHORE_H__30AE18F7_6781_4EA3_BD87_83C6CD8AE587__INCLUDED_)
#define AFX_SEMAPHORE_H__30AE18F7_6781_4EA3_BD87_83C6CD8AE587__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "platform.h"
#ifdef WIN32
#include <windows.h>
#elif defined(AIX) 
#include <pthread.h>
#elif defined(HP_UX)
#include <pthread.h>
#include <sys/semaphore.h>
#else
#include <semaphore.h>
#endif

class  CSemaphore
{
public:
	CSemaphore(int nValue = 1);
	~CSemaphore();
	bool Lock(int timeout);
	bool Lock();
	bool UnLock(int *pPrevCount = NULL);
private:
#ifdef WIN32
	HANDLE m_sid;
#elif defined(AIX)
	pthread_mutex_t m_mutex;
	pthread_cond_t m_cond;
	int m_value;
#elif defined(HP_UX)
	pthread_mutex_t m_mutex;
	pthread_cond_t m_cond;
	int m_nValue;		
#else
	sem_t m_sid;
#endif
};

#endif // !defined(AFX_SEMAPHORE_H__30AE18F7_6781_4EA3_BD87_83C6CD8AE587__INCLUDED_)
