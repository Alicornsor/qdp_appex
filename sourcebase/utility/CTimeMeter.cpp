/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CTimeMeter.cpp
///@brief实现了类CTimeMeter
///@history 
///20050209	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CTimeMeter.h"

CTimeMeter *timeMeters[MAX_TIME_METER];

CTimeMeter::CTimeMeter(char *name, int allowStart)
{
	m_name=name;
	m_time=0;
	m_isStarted=0;
	m_allowStart=allowStart;
	m_callCount=0;
}

CTimeMeter::~CTimeMeter(void)
{
	CHECK_TYPE("CTimeMeter");
}

int CTimeMeter::isA(char *objectType)
{
	if (!strcmp(objectType,"CTimeMeter"))
		return 1;
	return CBaseObject::isA(objectType);
}

char *CTimeMeter::getType(void)
{
	return "CTimeMeter";
}

void CTimeMeter::output(CLogger *pLogger,int indent)
{
	CHECK_TYPE("CTimeMeter");
	pLogger->output(indent,0,"CTimeMeter[%s]=%d",m_name,m_time);
}

void CTimeMeter::start(void)
{
	if (!m_allowStart)
	{
		return;
	}
	if (m_isStarted)
	{
		//printf("%s\n",m_name);
		//RAISE_DESIGN_ERROR("Time meter already started");
		m_isStarted++;
		return;
	}
	GET_ACCURATE_TIME(m_lastStartTime);
	m_callCount++;
	m_isStarted=1;
}

void CTimeMeter::stop(void)
{
	if (!m_allowStart)
	{
		return;
	}
	int stopTime;
	if (!m_isStarted)
	{
		RAISE_DESIGN_ERROR("Time meter havn't started");
		return;
	}
	if (m_isStarted>1)
	{
		m_isStarted--;
		return;
	}
	GET_ACCURATE_TIME(stopTime);
	m_callCount++;
	m_time+=stopTime-m_lastStartTime;
	m_isStarted=0;
}

void CTimeMeter::allow(int allowStart)
{
	m_allowStart=allowStart;
}

int CTimeMeter::getTime(void)
{
	return m_time;
}

int CTimeMeter::getCallCount(void)
{
	return m_callCount;
}

void CTimeMeter::display(FILE *output)
{
	if (m_isStarted)
	{
		fprintf(output,"%s havn't stopped\n",m_name);
	}
	fprintf(output,"%s time: %d milliseconds %d calls\n",m_name,m_time,m_callCount);
}

char *CTimeMeter::getName(void)
{
	return m_name;
}
