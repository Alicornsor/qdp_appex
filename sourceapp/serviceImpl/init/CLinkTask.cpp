/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CLinkTask.cpp
///@brief	ʵ������CLinkTask
///@history 
///20091203	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#include "CLinkTask.h"

CLinkTask::CLinkTask(void): ITask(1)
{
}

CLinkTask::~CLinkTask(void)
{
	while (!m_tasks.empty())
	{
		delete m_tasks.front();
		m_tasks.pop();
	}
}
	
void CLinkTask::addTask(ITask *pTask)
{
	m_tasks.push(pTask);
}

bool CLinkTask::step(int *pCost)
{
	*pCost=1;
	double fulfillRate=0.0;
	while (fulfillRate<1.0)
	{
		if (m_tasks.empty())
		{
			return false;
		}
		ITask *pTask=m_tasks.front();
		int fulfillCost=pTask->getFullfilCost();
		int thisFulfillCost;
		if (!pTask->step(&thisFulfillCost))
		{
			delete pTask;
			m_tasks.pop();
		}
		fulfillRate+=thisFulfillCost*1.0/fulfillCost;
	}
	return true;
}
