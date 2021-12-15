/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CSyslogService.cpp
///@brief	实现了使用syslog实现探针接口
///@history 
///20060716	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////
#ifdef UNIX

#include "CSyslogService.h"

void CSyslogService::SendProbeMessageImpl
	(
		const char *programName,
		const int globalSeq,
		const char *parameter,
		const char *value
	)
{
	syslog( LOG_INFO, "%s %s\n", parameter, value );
}

#endif
