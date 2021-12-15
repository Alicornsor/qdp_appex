/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CFilelogService.h
///@brief	定义使用文件实现探针接口
///@history 
///20060724	xuzh		创建该文件
///20060827	hwp		增加了创建实例的方法
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
	///构造方法
	///@param	programName	指定的程序名
	///@param	globalSeq	程序全局序列号
	///@param	fileName	文件名称
	//******//
	//	xuzh，20060929：将文件名称从参数中传入
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
	
	///析构函数
	virtual ~CFilelogService(void)
	{
		if (m_fp!=NULL)
		{
			fclose(m_fp);
		}
	}

	/**
	 * 具体实现如何发送消息
	 * @param programName 程序名
	 * @param globalSeq 程序全局序列号
	 * @param parameter 程序参数指标
	 * @param value 参数值
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
