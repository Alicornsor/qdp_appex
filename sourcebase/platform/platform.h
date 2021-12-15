/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file platform.h
///@brief�������п�ƽ̨��Ҫ�ĺ꣬�Լ�������Ӧ��ͷ�ļ�
///@history 
///20020214	xuzh		�������ļ�
///20070912 hwp		�޸�UNIX��
///20070927 hwp		����LINUX��singalͷ�ļ�
///20080603 hwp		����WIN32�µ�getopt����
///20080727 hwp		����stackͷ�ļ�
///20090119 hwp		�޸�GET_ACCURATE_TIME��ʹ��UNIX��WINN�º�����ͬ��
///						���պ�������NT-0065��
/////////////////////////////////////////////////////////////////////////

#ifndef PLATFORM_H
#define PLATFORM_H

///Ŀǰ���ļ�֧�����ֲ�ͬ��ƽ̨���û���ʹ��WINDOWS��ʾmicrosoft windows�ĸ���
///ƽ̨��ʹ��VC 6.0���ϱ��룩��Ҳ����ʹ��UNIX��ʾ���ֲ�ͬ��unixƽ̨��ʹ��g++���룩��
///Ҳ����ʹ��VOS��ʾStratus��VOSƽ̨(ʹ��g++���룩
///#define WINDOWS
///#define VOS
///#define UNIX

/////////////////////////////////////////////////////////////////////////
///����ƽ̨����Ҫ�������ļ�
/////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <errno.h>
#include <memory.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <float.h>
#include <limits.h>

/////////////////////////////////////////////////////////////////////////
///STL
/////////////////////////////////////////////////////////////////////////
#ifdef WINDOWS
	#pragma warning(disable:4786)
#endif
#include <algorithm>
#include <map>
#include <set>
#include <list>
#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <stack>
using namespace std;

/////////////////////////////////////////////////////////////////////////
///Windows����ĺ�
/////////////////////////////////////////////////////////////////////////
#ifdef WINDOWS
#define WIN32
#define _CONSOLE
#define _MBCS
#endif

/////////////////////////////////////////////////////////////////////////
///Unix����ĺ�
/////////////////////////////////////////////////////////////////////////
#ifdef LINUX
#define UNIX
#endif

#ifdef HP_UX
#define UNIX
#define _BIG_ENDIAN_
//#define _XOPEN_SOURCE_EXTENDED
//#define _INCLUDE_POSIX_SOURCE
#endif

#ifdef DEBUG
#ifndef _DEBUG
#define _DEBUG
#endif
#endif

/////////////////////////////////////////////////////////////////////////
///�򿪻��߹رյ���ģʽ
/////////////////////////////////////////////////////////////////////////
//#define DEBUG

/////////////////////////////////////////////////////////////////////////
///����ƽ̨���е�ͷ�ļ�
/////////////////////////////////////////////////////////////////////////
#ifdef WINDOWS
#include <windows.h>
#include <io.h>
#include <process.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <winsock.h>
#include <fcntl.h>
//#include <iphlpapi.h>
#include  "conio.h"
#endif

#ifdef WINDOWS

#else
	
#endif

#ifdef UNIX
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <ifaddrs.h>
#include <net/if.h>
typedef int cid_t;
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <pthread.h>
#include <sys/timeb.h>
#include <fcntl.h>
#include <termios.h>

#ifdef LINUX
#include <semaphore.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#else
#include <sys/semaphore.h>
#endif

#endif

#ifdef AIX
#include <strings.h>
#endif
#ifdef HP_UX
#include <strings.h>
#endif

#ifdef VOS
#define $shortmap
#define $longmap
#define $memset memset
#include <voslib.h>
#include <c_utilities.h>
#include <errno.h>
#include <streams_utilities.h>
#include <error_codes.h>
#include <tcp_types.h>
#include <socket.h>
#include <tcp_socket.h>
#include <in.h>
#include <ioctl.h>
#define _TYPEDEF_DEV_T
#define _TYPEDEF_OFF_T
#include <sys/stat.h>
#endif

/////////////////////////////////////////////////////////////////////////
///·��������
/////////////////////////////////////////////////////////////////////////
#include "mpath.h"

/////////////////////////////////////////////////////////////////////////
///�����׼���ȵ�����
/////////////////////////////////////////////////////////////////////////
typedef unsigned char	BYTE;
typedef unsigned short	WORD;
typedef char	INT1;
typedef short	INT2;
typedef int	INT4;

//20130828 xuzh ����UF_INT8�Ķ��壬����64�ֽڵ����ļ�id����
//INT8���������windows���Ѿ��ж����ˣ����������redefinition���󣬸���ΪUF_INT8
//wangwei,20150506
#ifdef  UNIX
typedef long long	UF_INT8;
#else
typedef __int64		UF_INT8;
#endif
//20130828 xuzh end


typedef float	REAL4;
typedef double	REAL8;

#ifndef  WINDOWS
typedef unsigned int	DWORD;
#else 
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma  warning(disable:4819 4996)
#else 
typedef unsigned int	DWORD;
#endif
#endif


/////////////////////////////////////////////////////////////////////////
///�ֽ������
/////////////////////////////////////////////////////////////////////////
inline WORD ChangeEndian(WORD value)
{
	return	((value&0x00ff)<<8)|
			((value&0xff00)>>8);
}

inline DWORD ChangeEndian(DWORD value)
{
	return	((value&0x000000ff)<<24) |
			((value&0x0000ff00)<<8)  |
			((value&0x00ff0000)>>8)  |
			((value&0xff000000)>>24);
}

inline UF_INT8 ChangeEndian(UF_INT8 value)
{
	UF_INT8 temp = value;
	char *pSource = (char *)&value;
	char *pTarget = (char *)&temp;
	pTarget[7] = pSource[0];
	pTarget[6] = pSource[1];
	pTarget[5] = pSource[2];
	pTarget[4] = pSource[3];
	pTarget[3] = pSource[4];
	pTarget[2] = pSource[5];
	pTarget[1] = pSource[6];
	pTarget[0] = pSource[7];
	return temp;
}

// inline fpos_t ChangeEndian(fpos_t value)
// {
// 	fpos_t temp = value;
// 	char *pSource = (char *)&value;
// 	char *pTarget = (char *)&temp;
// 	pTarget[7] = pSource[0];
// 	pTarget[6] = pSource[1];
// 	pTarget[5] = pSource[2];
// 	pTarget[4] = pSource[3];
// 	pTarget[3] = pSource[4];
// 	pTarget[2] = pSource[5];
// 	pTarget[1] = pSource[6];
// 	pTarget[0] = pSource[7];
// 	return temp;
// }

#ifndef _BIG_ENDIAN_
#define CHANGE_ENDIAN(value)	value = ::ChangeEndian(value)
#else
#define CHANGE_ENDIAN(value)
#endif

/////////////////////////////////////////////////////////////////////////
///���Ƴ����еĶ���
/////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define ASSERT(booleanExpression )					\
	if(!(booleanExpression)){						\
		RAISE_DESIGN_ERROR(#booleanExpression);		\
	}
#else
#define ASSERT(booleanExpression )
#endif


/////////////////////////////////////////////////////////////////////////
///�����ļ�������
/////////////////////////////////////////////////////////////////////////
///��Unix�£�����ʹ��stat����ȡ�ļ�״̬
#ifdef UNIX
#define struct_stat struct stat
#define STAT	stat
#endif
///��Windows�£�����ʹ��_stat����ȡ�ļ�״̬
#ifdef WINDOWS
#define struct_stat struct _stat
#define STAT	_stat
#endif
///��Vos�£�����ʹ��stat����ȡ�ļ�״̬
#ifdef VOS
#define struct_stat struct stat
#define STAT    stat
#endif

///��Unix�£�����ʹ��unlink��ɾ���ļ�
#ifdef UNIX
#define UNLINK unlink
#endif
///��Windows�£�����ʹ��_unlink��ɾ���ļ�
#ifdef WINDOWS
#define UNLINK _unlink
#endif
///��Vos�£�����ʹ��vos_unlink��ɾ���ļ�
#ifdef VOS
#define UNLINK vos_unlink
#endif

///����openʱ�Ĳ�������
#ifdef UNIX
#define OPEN_FOR_READ (O_RDONLY)
#define OPEN_FOR_WRITE (O_RDWR)
#define OPEN_FOR_CREATE (O_RDWR|O_CREAT|O_TRUNC)
#endif
#ifdef WINDOWS
#define OPEN_FOR_READ (O_BINARY|O_RDONLY)
#define OPEN_FOR_WRITE (O_BINARY|O_RDWR)
#define OPEN_FOR_CREATE (O_BINARY|O_RDWR|O_CREAT|O_TRUNC)
#endif

/////////////////////////////////////////////////////////////////////////
///�������ڴ������
/////////////////////////////////////////////////////////////////////////
#ifdef UNIX
#ifndef SHM_FAILED
#define SHM_FAILED (char *)(-1)
#endif
#define ALLOC_SHARE_MEMORY(ptr_addr, id,size)  				\
	{								\
		int shmid = shmget(id,size, IPC_CREAT|0644);		\
		if(shmid<0) 						\
		{							\
			*ptr_addr=NULL;					\
		}							\
		else 							\
		{ 							\
			*ptr_addr=(char *)shmat(shmid,(char *)0,0);	\
			if (*ptr_addr == SHM_FAILED)			\
				*ptr_addr=NULL;				\
		}							\
	}
#define REUSE_SHARE_MEMORY(ptr_addr, id,size)  				\
	{								\
 		int shmid = shmget(id,size, 0644);			\
		if(shmid<0) 						\
		{							\
			*ptr_addr=NULL;					\
		}							\
		else 							\
		{ 							\
			*ptr_addr=(char *)shmat(shmid,(char *)0,0);	\
			if(*ptr_addr == SHM_FAILED)			\
				*ptr_addr=NULL;				\
		}							\
	}
#endif

#ifdef WINDOWS
#define ALLOC_SHARE_MEMORY(ptr_addr,id,size)				\
	{								\
		HANDLE hfile,hmap;					\
		char buffer[80];					\
		sprintf(buffer,"\\mapping%d.mem",id);			\
		hfile=CreateFile(buffer,GENERIC_READ|GENERIC_WRITE,	\
			FILE_SHARE_READ|FILE_SHARE_WRITE,		\
			NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);	\
		if (hfile==INVALID_HANDLE_VALUE)			\
		{							\
			*ptr_addr=NULL;					\
		}							\
		else							\
		{							\
			hmap=CreateFileMapping(hfile,NULL,		\
				PAGE_READWRITE,0,size,NULL);		\
			if (hmap==NULL)					\
			{						\
				*ptr_addr=NULL;				\
			}						\
			else						\
			{						\
				*ptr_addr=(char *)MapViewOfFile(hmap,	\
					FILE_MAP_WRITE,0,0,size);	\
			}						\
		}							\
	}
#define REUSE_SHARE_MEMORY(ptr_addr,id,size)	ALLOC_SHARE_MEMORY(ptr_addr,id,size)
#endif

#ifdef VOS
#define ALLOC_SHARE_MEMORY(ptr_addr,id,size)	{*ptr_addr=NULL;}
#define REUSE_SHARE_MEMORY(ptr_addr,id,size)	{*ptr_addr=NULL;}
#endif

/////////////////////////////////////////////////////////////////////////
///�����̵߳�����
/////////////////////////////////////////////////////////////////////////


#ifdef WINDOWS
#define CREATE_PTHREAD(ptrThreadHandle,ptrThreadId, ptrFunc, ptrArgument)   ( (*ptrThreadHandle = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)ptrFunc,ptrArgument,0,ptrThreadId))==NULL?0:1)
#endif

#ifdef UNIX
#define CREATE_PTHREAD(ptrThreadHandle,ptrThreadId, ptrFunc, ptrArgument)  (pthread_create(ptrThreadHandle, NULL,ptrFunc,ptrArgument)?0:1)
#endif

#ifdef VOS
#define CREATE_PTHREAD(ptrThreadHandle,ptrThreadId, ptrFunc, ptrArgument)  0
#endif

//////////////////////////////////////////////////////////////////////////
/// �̺߳�����������ͬ
//////////////////////////////////////////////////////////////////////////
#ifdef WIN32
#define TheadEntry		\
		DWORD WINAPI _ThreadEntry(LPVOID pParam)
#else
#define TheadEntry		\
		void * _ThreadEntry(void *pParam)
#endif
 
//**********************************************************************
//�����ٽ���������
//**********************************************************************
#ifdef WINDOWS
#define CRITICAL_VAR		CRITICAL_SECTION
#define INIT_CRITICAL_VAR(v)	InitializeCriticalSection(&(v))
#define ENTER_CRITICAL(v)	EnterCriticalSection(&(v))
#define LEAVE_CRITICAL(v)	LeaveCriticalSection(&(v))
#define DELETE_CRITICAL_VAR(v)	DeleteCriticalSection(&(v))
#endif

#ifdef UNIX
#define CRITICAL_VAR		pthread_mutex_t
#define INIT_CRITICAL_VAR(v)	pthread_mutex_init(&(v), NULL);
#define ENTER_CRITICAL(v)	pthread_mutex_lock(&(v))
#define LEAVE_CRITICAL(v)	pthread_mutex_unlock(&(v))
#define DELETE_CRITICAL_VAR(v)	pthread_mutex_destroy(&(v));
#endif

/////////////////////////////////////////////////////////////////////////
///��windows������dll
/////////////////////////////////////////////////////////////////////////
#ifdef WINDOWS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT 
#endif

/////////////////////////////////////////////////////////////////////////
///����ȷʱ�������
/////////////////////////////////////////////////////////////////////////
#ifdef WINDOWS
#define GET_ACCURATE_SEC_TIME(v) 			\
	{					\
	SYSTEMTIME t;			\
	GetLocalTime(&t);		\
	v=t.wHour*3600+		\
	t.wMinute*60+	\
	t.wSecond;		\
	}
#endif

#ifdef UNIX
#define GET_ACCURATE_SEC_TIME(v)			\
	{					\
	struct timeval t;		\
	gettimeofday(&t,NULL);		\
	tm *now=localtime(&t.tv_sec);		\
	v=now->tm_hour*3600+now->tm_min*60+now->tm_sec;		\
	}
#endif

#ifdef WINDOWS
#define GET_ACCURATE_TIME(v) 			\
	{					\
		SYSTEMTIME t;			\
		GetLocalTime(&t);		\
		v=t.wHour*3600000+		\
			t.wMinute*60000+	\
			t.wSecond*1000+		\
			t.wMilliseconds;	\
	}

#define GET_ACCURATE_MSEC_TIME(v) 			\
	{					\
	SYSTEMTIME t;			\
	GetLocalTime(&t);		\
	v=t.wMilliseconds;	\
	}
#endif

//ʱ�侫��Ϊus,20130111,wangwei
#ifdef WINDOWS
#define GET_ACCURATE_USEC_TIME(v) 			\
	{					\
		SYSTEMTIME t;			\
		GetLocalTime(&t);		\
		v=t.wHour*3600000000+		\
			t.wMinute*60000000+	\
			t.wSecond*1000000+		\
			t.wMilliseconds*1000;	\
	}
#endif

//ʱ�侫��Ϊus,20130111,wangwei
//2013.08.12 longqy@cffex.net ����������ӵ�ʱ�򣬳���32λ�ĳ������������ǿ��ת��Ϊ(long)����
//���� v Ҳ����Ϊ long ���ͣ�����Ż���ȷ
#ifdef UNIX
#define GET_ACCURATE_USEC_TIME(v)			\
	{					\
		struct timeval t;		\
		gettimeofday(&t,NULL);		\
		tm *now=localtime(&t.tv_sec);		\
		v=(long)now->tm_hour*3600000000 + (long)now->tm_min*60000000+now->tm_sec*1000000+		\
			t.tv_usec;		\
	}
#endif

#ifdef UNIX
#define GET_ACCURATE_TIME(v)			\
	{					\
		struct timeval t;		\
		gettimeofday(&t,NULL);		\
		tm *now=localtime(&t.tv_sec);		\
		v=now->tm_hour*3600000+now->tm_min*60000+now->tm_sec*1000+		\
			t.tv_usec/1000;		\
	}
#define GET_ACCURATE_MSEC_TIME(v)			\
	{					\
	struct timeval t;		\
	gettimeofday(&t,NULL);		\
	tm *now=localtime(&t.tv_sec);		\
	v=t.tv_usec/1000;		\
	}
#endif

/////////////////////////////////////////////////////////////////////////
///�������ϵ�����
/////////////////////////////////////////////////////////////////////////
#define DOUBLE_NaN DBL_MAX

/////////////////////////////////////////////////////////////////////////
///���ֳ��ú���������
/////////////////////////////////////////////////////////////////////////
///��Windows�£�������Ҫʹ��Sleep��������sleep������ͳһ��SLEEP
#ifdef WINDOWS
#define SLEEP(ms) Sleep(ms)
#else
#define SLEEP(ms) sleep((ms)/1000)
#endif

///Sleep ʹ�õĲ�����һ��������˵����Sleep������Ϊ�����
#ifdef WINDOWS
#define SLEEP_SECONDS(seconds) Sleep((seconds)*1000)
#else
#define SLEEP_SECONDS(seconds) sleep(seconds)
#endif

///��ȡ��ǰ�̺߳�
#ifdef WINDOWS 
#define GetThreadID() ::GetCurrentThreadId()
#else
#define GetThreadID() ::pthread_self()
#endif

///�ȴ��źŵĸı�
#ifdef WINDOWS
#define WaitForObject(handle) (WaitForSingleObject(handle,INFINITE) != 0) 
#else
#define WaitForObject(handle) (pthread_join(handle, NULL) == 0)
#endif


#ifdef WINDOWS
#define GetSyncTime(currentTime,currentMilTime)	\
		currentMilTime = GetTickCount()/1000;		\
		currentTime = GetTickCount();
#else	
#define GetSyncTime(currentTime,currentMilTime)	\
		struct timeval timeout;					\
		gettimeofday(&timeout, 0);				\
		currentTime = timeout.tv_sec;			\
		currentMilTime = timeout.tv_sec*1000 + timeout.tv_usec/1000;
#endif
///��Windows�£�������Ҫ���¶���MAX��MIN��
#ifdef WINDOWS
#ifndef MAX
#define MAX(a,b) max(a,b)
#endif
#ifndef MIN
#define MIN(a,b) min(a,b)
#endif
#endif
#ifdef UNIX
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif


//windows�µĲ�ͬ�����Ķ���
#ifdef WINDOWS
#define isnan _isnan
//ע��window��linux����Ĳ�ͬ������涨ʹ��ʱ��Ҫ��ʼ��Ϊ0
#define snprintf _snprintf
#endif

#ifdef WINDOWS
#define sh_open(a,b,c)  _sopen(a,b|O_BINARY,c,S_IREAD | S_IWRITE)
#else
#define sh_open(a,b,c)  open(a,b,S_IREAD | S_IWRITE)
#endif

/////////////////////////////////////////////////////////////////////////
///Difference for fpos_t
/////////////////////////////////////////////////////////////////////////
#ifdef LINUX
#define FPOS_SET(fposValue,longValue)	(fposValue).__pos=(longValue)
#define FPOS_GET(fposValue)	(fposValue).__pos
#else
#define FPOS_SET(fposValue,longValue)	(fposValue)=(longValue)
#define FPOS_GET(fposValue)	(fposValue)
#endif

/////////////////////////////////////////////////////////////////////////
///����ָ���ϵĲ��
/////////////////////////////////////////////////////////////////////////
///��Windows�£�������Ҫʹ��pack(1)������pragma��ʾ��Ҫѹ���ṹ������ƽ̨�µ���Ӧ
///���ܶ��ڱ���ѡ����ʵ��
#ifdef WINDOWS
//#pragma pack(1)
#endif

///��Vos�£�������Ҫʹ��pack(1)������pragma��ʾ��Ҫѹ���ṹ������ƽ̨�µ���Ӧ
///���ܶ��ڱ���ѡ����ʵ��
#ifdef VOS
//#pragma pack(1)
#endif

#ifdef WIN32
extern char	*optarg;		// global argument pointer
extern int	optind; 		// global argv index

extern int getopt(int argc, char *argv[], char *optstring);
#else
void strupr(char   *pcSrc);
#endif

#ifdef LINUX
#define __NR_gettid 186
long int gettid();
#endif

#ifdef LINUX
#define likely(x)  __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#else
#define likely(x) (x)
#define unlikely(x) (x)
#endif

void doodle8(unsigned char *p);
void undoodle8(unsigned char *p);
void doodle4(unsigned char *p);
void undoodle4(unsigned char *p);
void init_gene(long gene);

#endif


