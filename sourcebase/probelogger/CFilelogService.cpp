/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CFilelogService.cpp
///@brief	ʵ����ʹ���ļ�ʵ��̽��ӿ�
///@history 
///20060724	xuzh		�������ļ�
///20060827	hwp		�����˴���ʵ���ķ���
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
/* 20130820 longqy ��־�¼�ҲӦ����ȷ��΢�뼶��Unix ����� tv_usec ΢���� */
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
		//2014-06-25 longqy ��flush�ļ����������
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
	// WIndows ƽ̨û�к��� strtok_r������������ longqy 2014-03-25
	char *safeptr;
	programName=strtok_r(programName,".",&safeptr);
#else
	programName=strtok(programName,".");
#endif

	programName=strdup(programName);

	return new CFilelogService(programName,globalSeq,fileName);
}
