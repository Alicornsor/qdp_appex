/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CProbeLogger.h
///@brief	定义探针的接口
///@history 
///20060716	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////
#ifndef CPROBELOGGER_H
#define CPROBELOGGER_H

#include "platform.h"

#define MAX_PARAMETER_NAME 100

class CProbeLogger
{
private:
	const char *m_programName;
	int m_globalSeq;
public:
	///构造方法
	///@param	programName	指定的程序名
	///@param	globalSeq	程序全局序列号
	CProbeLogger(const char *programName, const int globalSeq)
	{
		m_programName=programName;
		m_globalSeq=globalSeq;
	}
	
	///析构方法
	virtual ~CProbeLogger(void)
	{
	}

	///发送探针消息，值为字符串
	///@param	parameter	参数名
	///@param	value	要发送的消息
	void SendProbeMessage(const char *parameter, const char *value);

	///发送探针消息，值为整数
	///@param	parameter	参数名
	///@param	value	要发送的消息
	void SendProbeMessage(const char *parameter, const int value);

	///发送探针消息，值为浮点数
	///@param	parameter	参数名
	///@param	value	要发送的消息
	void SendProbeMessage(const char *parameter, const double value);

	///发送探针消息，值为浮点数，以百分比方式显示
	///@param	parameter	参数名
	///@param	value	要发送的消息
	void SendPercentageProbeMessage(const char *parameter, const double value);
protected:
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
	) = 0;
};

#endif
