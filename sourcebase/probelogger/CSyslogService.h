/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CSyslogService.h
///@brief	定义使用syslog实现探针接口
///@history 
///20060716	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////
#ifndef CSYSLOGSERVICE_H
#define CSYSLOGSERVICE_H

#ifdef UNIX
#include <syslog.h>

#include "CProbeLogger.h"

class CSyslogService : public CProbeLogger
{
private:
	char m_ident[100];
public:
	///构造方法
	///@param	programName	指定的程序名
	///@param	globalSeq	程序全局序列号
	CSyslogService(const char *programName, const int globalSeq): CProbeLogger(programName,globalSeq)
	{
		sprintf( m_ident, "%s %d", programName, globalSeq );
		openlog( m_ident, LOG_PID, LOG_USER );
	}
	
	///析构函数
	virtual ~CSyslogService(void)
	{
		closelog();
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
};

#endif

#endif
