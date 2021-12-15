/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CFiniteState.cpp
///@brief实现了类CFiniteState
///@history 
///20041219	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CFiniteState.h"
#include "monitorIndex.h"

CFiniteState::CFiniteState(int totalState, int allowTable[], char *stateName[], int initState)
{
	m_totalState=totalState;
	m_allowTable=allowTable;
	m_stateName=stateName;
	m_currentState=initState;
	if ((totalState>32)||(initState<0)||(initState>=totalState))
	{
		RAISE_DESIGN_ERROR("invalid finite state machine");
	}
}

CFiniteState::~CFiniteState(void)
{
}

int CFiniteState::isA(char *objectType)
{
	if (!strcmp(objectType,"CFiniteState"))
		return 1;
	return CBaseObject::isA(objectType);
}

char *CFiniteState::getType(void)
{
	return "CFiniteState";
}

void CFiniteState::output(CLogger *pLogger,int indent)
{
	CHECK_TYPE("CFiniteState");
	pLogger->output(indent,0,"CTransaction");
	for (int i=0;i<m_totalState;i++)
	{
		pLogger->output(indent+1,0,m_stateName[i]);
		if (i==m_currentState)
		{
			pLogger->output("*");
		}
	}
}

int CFiniteState::shiftState(int newState)
{
	if ((newState<0)||(newState>=m_totalState))
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","state out of range");
		return 0;
	}
	if (m_currentState==newState)
	{
		return 0;
	}
	if ((m_allowTable[m_currentState]&(1<<newState))==0)
	{
		return 0;
	}
	shiftAction(m_currentState,newState);
	m_currentState=newState;
	return 1;
}
	
int CFiniteState::getState(void)
{
	return m_currentState;
}

void CFiniteState::shiftAction(int oldState, int newState)
{
}
