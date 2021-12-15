/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CProbeLogger.cpp
///@brief	实现探针的接口
///@history 
///20060716	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CProbeLogger.h"

void CProbeLogger::SendProbeMessage(const char *parameter, const char *value)
{
	SendProbeMessageImpl(m_programName,m_globalSeq,parameter,value);
}

void CProbeLogger::SendProbeMessage(const char *parameter, const int value)
{
	char buffer[100];
	sprintf(buffer,"%d",value);
	SendProbeMessageImpl(m_programName,m_globalSeq,parameter,buffer);
}

void CProbeLogger::SendProbeMessage(const char *parameter, const double value)
{
	char buffer[100];
	sprintf(buffer,"%lf",value);
	SendProbeMessageImpl(m_programName,m_globalSeq,parameter,buffer);
}

void CProbeLogger::SendPercentageProbeMessage(const char *parameter, const double value)
{
	char buffer[100];
	sprintf(buffer,"%.2lf%%",value*100);
	SendProbeMessageImpl(m_programName,m_globalSeq,parameter,buffer);
}
