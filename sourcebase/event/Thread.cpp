// Thread.cpp: implementation of the CThread class.
//
// 20070919 hwp	�޸ģ�����һ��CThread���󴴽�����߳�
// 20080724 hwp  NT-0003-UserAPI֧��NameServer:
//                  WIN32�������������TLS���߳�����ʱ���ȳ�ʼ����������ӡ�HP/LINUXû����
// 20090122 hwp	NT-0061:Join�����߳̾������Ϊ�գ���ֹLINUX�³����쳣
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "Thread.h"

#ifdef WIN32
DWORD WINAPI CThread::_ThreadEntry(LPVOID pParam)
#else
void * CThread::_ThreadEntry(void *pParam)
#endif
{
	CThread *pThread = (CThread *)pParam;
	try 
  	{
#ifdef WIN32
		srand((unsigned)time(NULL));
#endif
		if(pThread->InitInstance())
		{
			pThread->Run();
		}
	}
	
	catch (CDesignError *pError)
	{
		printf("design error:\n%s\nin file %s, line %d\n",pError->GetMsg(),pError->GetFile(),pError->GetLineNo());
		exit(0);
	}
	catch (CRuntimeError *pError)
	{
		printf("runtime error:\n%s\nin file %s, line %d\n",pError->GetMsg(),pError->GetFile(),pError->GetLineNo());
		exit(0);
	}

	pThread->ExitInstance();

	//20140613 xuzh �������Ϊ0��join���־��޷�join�ˣ�������Դ�޷��ͷ�
	//pThread->m_hThread = (THREAD_HANDLE)0;
	
	return NULL;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThread::CThread()
{
	m_hThread = (THREAD_HANDLE)0;
	m_IDThread = 0;
}

CThread::~CThread()
{
}

bool  CThread::Create()
{
	if (m_hThread != (THREAD_HANDLE)0)
	{
		return true;
	}
	bool ret = true;
#ifdef WIN32
	m_hThread = ::CreateThread(NULL,0,_ThreadEntry,this,0,&m_IDThread);
	if(m_hThread==NULL)
	{
		ret = false;
	}
#else
	ret = (::pthread_create(&m_hThread,NULL,&_ThreadEntry , this) == 0);
#endif
	return ret;
}

bool CThread::InitInstance()
{
	return true;
}

void CThread::ExitInstance()
{
}

void CThread::OSSleep(int seconds)
{
#ifdef WIN32
	::Sleep(seconds*1000);
#else
	::sleep(seconds);
#endif
}

void CThread::SleepMs(int nMilliseconds)
{
#ifdef WIN32
	::Sleep(nMilliseconds);
#else
//	::usleep(nMilliseconds*1000);
	// 2014-04-09 Sleep ʱ��̫������Ϊ΢�뼶
	::usleep(nMilliseconds);
#endif
}

bool CThread::IsCurrentThread()
{
#ifdef WIN32
	return ::GetCurrentThreadId() == m_IDThread;
#else
	return ::pthread_self() == m_hThread;
#endif
}

bool CThread::Join()
{
	//20090122 hwp ��ֹLINUX��join�����쳣
	THREAD_HANDLE hThread = GetHandle();
	if(hThread == (THREAD_HANDLE)0)
	{
		return true;
	}
#ifdef WIN32
	return (WaitForSingleObject(hThread,INFINITE) != 0);
#else
	return (pthread_join(hThread, NULL) == 0);
#endif
}

void CThread::ExitThread()
{
#ifdef WIN32
	::ExitThread(0);
#else
#endif
}

#ifdef LINUX
int g_n_cpucount=0;//����cpu����
int g_n_cpuindx=0;//δ�����cpu���,0��cpu�����߳�ռ�ã����һ��cpu��exchangemanagerռ�ã�����İ����̴߳���˳����䣬���亯����selectreactor�Ĺ��캯����ʵ�֣�by wangwei,20150225
//��CPU�ı�־���������ΪTrue����Ѹ��̰߳󶨵���Ӧ��CPU������ȥ��Ĭ��Ϊfalse������
bool g_bBindThreadsToCPU=false;
bool g_bBinded[MAX_CPU_COUNT]={false};


//cpu bind
void BindThd2CPU(pthread_t thdid,int ncpuid)
{
	CMutex mtx;
	mtx.Lock();
	cpu_set_t mask;
        CPU_ZERO(&mask);

	if(g_n_cpucount<2)
	{	
		//only 1 cpu
		CPU_SET(0, &mask);
	}
	else
	{
		++g_n_cpuindx;
		if(ncpuid==-1)
		{
		/*
			g_n_cpuindx=(++g_n_cpuindx)%g_n_cpucount;
			if(g_n_cpuindx==0 || g_n_cpuindx==g_n_cpucount-1)
			{
				g_n_cpuindx=1;
			}
			ncpuid=g_n_cpuindx;
		*/
			int nNewIndex=(g_n_cpucount - g_n_cpuindx)%g_n_cpucount;
			if(nNewIndex==0 || nNewIndex==g_n_cpucount-1)
			{
				nNewIndex= g_n_cpucount - CPU_LOAD_100_THREADS;
			}
			ncpuid=nNewIndex;
			while(g_bBinded[ncpuid] && (ncpuid>0))
			{// CPU�ں˴Ӹ�������
				ncpuid--;
			}
			if(ncpuid<1){
				ncpuid=1;
			}
			g_bBinded[ncpuid]=true;
		
		}
		else{
			while(g_bBinded[ncpuid] && (ncpuid>0))
			{// CPU�ں˴Ӹ�������
				ncpuid--;
			}
			if(ncpuid<1){
				ncpuid=1;
			}
			g_bBinded[ncpuid]=true;			
		}
			
		CPU_SET(ncpuid, &mask);
	}

    if (pthread_setaffinity_np(thdid, sizeof(mask), &mask) < 0) {
    	printf("set thread affinity failed\n");
    }
	else
	{
        printf("set thread %lu affinity to cpu %d\n",thdid,ncpuid);
	}
	mtx.UnLock();
}
#endif
