/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CFilelogService.cpp
///@brief	实现了使用文件实现探针接口
///@history 
///20060724	xuzh		创建该文件
///20060827	hwp		增加了创建实例的方法
/////////////////////////////////////////////////////////////////////////
#include "CFilelogService.h"

void CFilelogService::SendProbeMessageImpl
	(
		const char *programName,
		const int globalSeq,
		const char *parameter,
		const char *value
	)
{
	if (m_fp!=NULL)
	{
/* 20130820 longqy 日志事件也应当精确到微秒级，Unix 下输出 tv_usec 微秒数 */
#ifdef UNIX
		struct timeval now;		
		gettimeofday(&now,NULL);
		char timeBuffer[100];
		strftime(timeBuffer, 100,"%b %d %H:%M:%S",localtime(&now.tv_sec));
		fprintf(m_fp, "%s %dus %s %s %d[%d]: %s %s\n", timeBuffer,now.tv_usec,m_hostname,programName, globalSeq, m_pid, parameter, value );
#else
		time_t now;
		time(&now);
		char timeBuffer[100];
		strftime(timeBuffer, 100,"%b %d %H:%M:%S",localtime(&now));
		fprintf(m_fp, "%s %s %s %d[%d]: %s %s\n", timeBuffer,m_hostname,programName, globalSeq, m_pid, parameter, value );
#endif
		//2014-06-25 longqy 不flush文件，提高性能
		fflush(m_fp);
	}
}

CFilelogService *CFilelogService::CreateInstance(int argc, char *argv[], const char *fileName)
{
	if ((fileName==NULL)||(fileName[0]=='\0'))
	{
		return NULL;
	}
	int globalSeq;
	if (argc>=2)
	{
		globalSeq=atoi(argv[1]);
	}
	else
	{
		globalSeq=0;
	}

	char fullProgramName[500];
	strcpy(fullProgramName,argv[0]);

	char *programName;
	programName=strrchr(fullProgramName,PATH_SPLIT);
	if (programName!=NULL)
	{
		programName++;
	}
	else
	{
		programName=fullProgramName;
	}
#ifdef LINUX
	// WIndows 平台没有函数 strtok_r，用条件编译 longqy 2014-03-25
	char *safeptr;
	programName=strtok_r(programName,".",&safeptr);
#else
	programName=strtok(programName,".");
#endif

	programName=strdup(programName);

	return new CFilelogService(programName,globalSeq,fileName);
}
