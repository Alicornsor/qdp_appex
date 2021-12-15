/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CLogger.cpp
///@brief实现了类CLogger
///@history 
///20041218	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////
#include "CLogger.h"

///下面的宏定义影响的是缺省的日志设置，在运行时，可以通过改变上述布尔值来改变此缺省设置

///业务日志
	///是否使用业务状态日志
	#define USE_BIZ_STATUS_LOG
	///是否使用业务处理日志
	#define USE_BIZ_OPERATION_LOG
	///是否使用业务异常日志
	#define USE_BIZ_EXCEPTION_LOG

///通讯日志
	///是否使用网络状态日志
	#define USE_NET_STATUS_LOG
	///是否使用网络连接断开日志
	#define USE_NET_CONNECT_LOG
	///是否使用网络收发日志
	#define USE_NET_IO_LOG
	///是否使用网络报文日志
	#define USE_NET_PACKAGE_LOG
	///是否使用网络压缩日志
	#define USE_NET_COMPRESS_LOG
	///是否使用网络异常日志
	#define USE_NET_EXCEPTION_LOG

///运行日志
	///是否使用运行日志
	#define USE_PROCESS_LOG


///业务日志
	///是否使用业务状态日志
	#ifdef USE_BIZ_STATUS_LOG
		bool UseBizStatusLog=true;
	#else
		bool UseBizStatusLog=false;
	#endif
	
	///是否使用业务处理日志
	#ifdef USE_BIZ_OPERATION_LOG
		bool UseBizOperationLog=true;
	#else
		bool UseBizOperationLog=false;
	#endif
	
	///是否使用业务异常日志
	#ifdef USE_BIZ_EXCEPTION_LOG
		bool UseBizExceptionLog=true;
	#else
		bool UseBizExceptionLog=false;
	#endif

///通讯日志
	///是否使用网络状态日志
	#ifdef USE_NET_STATUS_LOG
		bool UseNetStatusLog=true;
	#else
		bool UseNetStatusLog=false;
	#endif

	///是否使用网络连接断开日志
	#ifdef USE_NET_CONNECT_LOG
		bool UseNetConnectLog=true;
	#else
		bool UseNetConnectLog=false;
	#endif

	///是否使用网络收发日志
	#ifdef USE_NET_IO_LOG
		bool UseNetIOLog=true;
	#else
		bool UseNetIOLog=false;
	#endif
	
	///是否使用网络报文日志
	#ifdef USE_NET_PACKAGE_LOG
		bool UseNetPackageLog=true;
	#else
		bool UseNetPackageLog=false;
	#endif
	
	///是否使用网络压缩日志
	#ifdef USE_NET_COMPRESS_LOG
		bool UseNetCompressLog=true;
	#else
		bool UseNetCompressLog=false;
	#endif
	
	///是否使用网络异常日志
	#ifdef USE_NET_EXCEPTION_LOG
		bool UseNetExceptionLog=true;
	#else
		bool UseNetExceptionLog=false;
	#endif

///运行日志
	///是否使用运行日志
	#ifdef USE_PROCESS_LOG
		bool UseProcessLog=true;
	#else
		bool UseProcessLog=false;
	#endif

CLogger * CLogger::m_pInstance;

CLogger * CLogger::GetInstance()
{
	return m_pInstance;
}

void CLogger::output(int indent,int level,char *format,...)
{
	output(level,"\n");
	for (int i=0;i<indent;i++)
	{
		output(level,"\t");
	}
	va_list v;
	va_start(v,format);
	output(level,format,v);
	va_end(v);
}

void CLogger::output(char *format,...)
{
	va_list v;
	va_start(v,format);
	output(LL_DEBUG, format, v);
	va_end(v);
}


class CStdLogger :public CLogger
{
public:
	CStdLogger()
	{
		m_pInstance = this;
		INIT_CRITICAL_VAR(m_varCritical);
	}
	~CStdLogger()
	{
		DELETE_CRITICAL_VAR(m_varCritical);
	}
	
	virtual void output(int level, char *format, ...)
	{
		ENTER_CRITICAL(m_varCritical);
		va_list v;
		va_start(v,format);
		vfprintf(stdout,format,v);
		va_end(v);

		fflush(stdout);
		LEAVE_CRITICAL(m_varCritical);
	}
private:
	static CStdLogger m_stdLogger;
	CRITICAL_VAR m_varCritical;
};

CStdLogger CStdLogger::m_stdLogger;

