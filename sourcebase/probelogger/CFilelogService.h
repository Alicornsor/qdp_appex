/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CFilelogService.h
///@brief	����ʹ���ļ�ʵ��̽��ӿ�
///@history 
///20060724	xuzh		�������ļ�
///20060827	hwp		�����˴���ʵ���ķ���
/////////////////////////////////////////////////////////////////////////

#ifndef CFILELOGSERVICE_H
#define CFILELOGSERVICE_H

#include "CProbeLogger.h"

class CFilelogService : public CProbeLogger
{
private:
	FILE *m_fp;
	char m_hostname[1000];
	int m_pid;

public:
	///���췽��
	///@param	programName	ָ���ĳ�����
	///@param	globalSeq	����ȫ�����к�
	///@param	fileName	�ļ�����
	//******//
	//	xuzh��20060929�����ļ����ƴӲ����д���
	//******//
	CFilelogService(const char *programName, const int globalSeq, const char *fileName): CProbeLogger(programName,globalSeq)
	{
		m_fp = mfopen(fileName, "a+t");
#ifdef WINDOWS
		WSADATA initData;
		WSAStartup(2,&initData);
		gethostname(m_hostname,100);
		WSACleanup();
#else
		gethostname(m_hostname,100);
#endif
		m_pid=getpid();
	}
	
	///��������
	virtual ~CFilelogService(void)
	{
		if (m_fp!=NULL)
		{
			fclose(m_fp);
		}
	}

	/**
	 * ����ʵ����η�����Ϣ
	 * @param programName ������
	 * @param globalSeq ����ȫ�����к�
	 * @param parameter �������ָ��
	 * @param value ����ֵ
	 */
	virtual void SendProbeMessageImpl
	(
		const char *programName,
		const int globalSeq,
		const char *parameter,
		const char *value
	);

	static CFilelogService *CreateInstance(int argc, char *argv[], const char *fileName);
};

#endif
