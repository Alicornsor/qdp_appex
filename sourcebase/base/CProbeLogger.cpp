/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CProbeLogger.cpp
///@brief	ʵ��̽��Ľӿ�
///@history 
///20060716	xuzh		�������ļ�
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
