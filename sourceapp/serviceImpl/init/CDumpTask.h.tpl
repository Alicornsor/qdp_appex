/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company 上海量投网络科技有限公司
///@file CDumpTask.h
///@brief	定义了类CDumpTask和相关类
///@history 
///20091203	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CDUMPTASK_H
#define CDUMPTASK_H

#include "CLinkTask.h"
#include "databaseData.h"

!!enter system!!
!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!

/////////////////////////////////////////////////////////////////////////
///CDump!!@name!!Task是一个完成输出!!@usage!!的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDump!!@name!!Task: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDump!!@name!!Task(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDump!!@name!!Task(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	C!!@name!!Factory *m_pFactory;
	FILE *m_output;
	CWriteable!!@name!! *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};

!!endif!!
!!next!!

/////////////////////////////////////////////////////////////////////////
///CDumpTask是一个完成输出整个内存数据库的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpTask: public CLinkTask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	virtual ~CDumpTask(void)
	{
	}
};

!!leave!!

#endif
