/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file ITask.h
///@brief	定义了类ITask
///@history 
///20091203	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef ITASK_H
#define ITASK_H

/////////////////////////////////////////////////////////////////////////
///ITask是一个定义长时间完成的任务的基类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class ITask
{
private:
	int m_fullfilCost;

public:
	///构造函数
	///@param	fullfilCost	每步完成的权值
	ITask(int fullfilCost=1)
	{
		m_fullfilCost=fullfilCost;
	}
	
	///析构函数
	virtual ~ITask(void)
	{
	}
	
	///获取每步完成的权值
	///@return	每步完成的权值
	int getFullfilCost(void)
	{
		return m_fullfilCost;
	}
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost)=0;
};

#endif
