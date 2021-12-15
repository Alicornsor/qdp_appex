/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company 上海量投网络科技有限公司
///@file CDumpTask.cpp
///@brief	实现了类CDumpTask和相关类
///@history 
///20091203	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CDumpTask.h"

!!enter system!!
!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!

CDump!!@name!!Task::CDump!!@name!!Task(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_!!@name!!Factory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "!!@name!!.csv");
	m_output=mfopen(szFileName,"wt");
}

CDump!!@name!!Task::~CDump!!@name!!Task(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDump!!@name!!Task::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteable!!@name!!::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteable!!@name!![m_size];
		m_next=0;
		C!!@name!! *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}

!!endif!!
!!next!!

CDumpTask::CDumpTask(CConfig *pConfig,CMemoryDB *pDB): CLinkTask()
{
!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
	addTask(new CDump!!@name!!Task(pConfig,pDB));
!!endif!!
!!next!!
}

!!leave!!
