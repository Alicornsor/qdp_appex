/*************************************************************************
	> File Name: ThreadQueue.h
	> Author: 
	> Mail: 
	> Created Time: Fri 11 Mar 2016 10:32:29 AM CST
 ************************************************************************/

#ifndef _THREADQUEUE_H
#define _THREADQUEUE_H


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//#include "platform.h"
#include "Mutex.h"
#include "Parser.h"

#ifdef _MSC_VER
typedef HANDLE QUEUE_THREAD_HANDLE;
#else
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
typedef pthread_t QUEUE_THREAD_HANDLE;
#endif

namespace FREE_QUEUE
{
	typedef void (*pThreadQFunc)(int, const std::string);

class ThreadQueue
{
public:
	ThreadQueue();
	~ThreadQueue();

	//User function
	void RegReadFunc(pThreadQFunc pRegFunc);
	void RegWriteFunc(pThreadQFunc pRegFunc);
	bool StartQueue();
	bool StopQueue();
	bool QueueWriteFunc(const char *pBuff);
	bool IsQueueEmpty();
	bool IsQueueFull();
	bool IsQueueStop(){return m_bStop;}

public:
	pThreadQFunc GetReadFunc(){return m_pReadFunc;}
	bool QueuePop(std::string &str)
	{
		//return m_pFreeQueue->Pop();
		bool ret = false;
		try
		{
			ret = m_parser.readFixMessage(str);
		}
		catch (...)
		{
			ret = false;
		}
		return ret;
	}

private:

private:
	pThreadQFunc m_pReadFunc;
	pThreadQFunc m_pWriteFunc;
	bool         m_bStop;
	QUEUE_THREAD_HANDLE    m_nReadThread;
	FIX::Parser            m_parser;
};
}
#endif
