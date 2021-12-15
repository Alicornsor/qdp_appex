/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CMemorySequence.cpp
///@brief实现了类CMemorySequence
///@history 
///20041001	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CMemorySequence.h"

CMemorySequence::CMemorySequence(int startValue)
{
	m_StartValue=startValue;
	m_CurrentValue=startValue;
}

CMemorySequence::~CMemorySequence(void)
{
	CHECK_TYPE("CMemorySequence");
}

int CMemorySequence::isA(char *objectType)
{
	if (!strcmp(objectType,"CMemorySequence"))
		return 1;
	return CSequenceInterface::isA(objectType);
}

char *CMemorySequence::getType(void)
{
	return "CMemorySequence";
}

void CMemorySequence::output(CLogger *pLogger,int indent)
{
	CHECK_TYPE("CMemorySequence");
	pLogger->output(indent,0,"CMemorySequence:start=%d,current=%d",m_StartValue,m_CurrentValue);
}

int CMemorySequence::getNextValue(void)
{
	return ++m_CurrentValue;
}

int CMemorySequence::getCurrentValue(void)
{
	return m_CurrentValue;
}

void CMemorySequence::initValue(int nCurrValue)
{
	m_CurrentValue=nCurrValue;
}
