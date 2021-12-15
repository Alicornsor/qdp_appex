/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file CLinkTask.h
///@brief	定义了类CLinkTask
///@history 
///20091203	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CLINKTASK_H
#define CLINKTASK_H

#include "platform.h"
#include "ITask.h"

/////////////////////////////////////////////////////////////////////////
///CLinkTask是一个定义将多个任务连接成一个任务的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CLinkTask: public ITask
{
private:
	queue<ITask *> m_tasks;

public:
	///构造函数
	CLinkTask(void);
	
	///析构函数
	virtual ~CLinkTask(void);
	
	///添加任务
	///@param	pTask	要添加的任务
	void addTask(ITask *pTask);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);
};

#endif
