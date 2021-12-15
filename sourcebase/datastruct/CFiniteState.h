/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CFiniteState.h
///@brief定义了类CFiniteState
///@history 
///20041219	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CFINITESTATE_H
#define CFINITESTATE_H

#include "platform.h"
#include "CBaseObject.h"
#include "CLogger.h"

/////////////////////////////////////////////////////////////////////////
///CFiniteState是一个控制有限状态自动机的类
///@author	xuzh
///@version	1.0,20041219
/////////////////////////////////////////////////////////////////////////
class CFiniteState : public CBaseObject
{
public:
	///构造方法
	///@param	totalState	本状态机的状态数量，不能超过32
	///@param	allowTable	允许的状态切换表，大小为totalState，每个分量都是用位图的方式表示是否允许
	///@param	stateName	所有状态的名称，大小为totalState
	///@param	initState	初始状态
	CFiniteState(int totalState, int allowTable[], char *stateName[], int initState=0);

	virtual ~CFiniteState(void);
	virtual int isA(char *objectType);
	virtual char *getType(void);
	virtual void output(CLogger *pLogger,int indent=0);
	
	///切换状态
	///@param newState	新的状态
	///@return	1不表示成功，0表示失败	
	int shiftState(int newState);
	
	///获取当前状态
	///@return	当前状态
	int getState(void);
protected:
	///状态发生切换时的动作，一般由继承类实现
	///@param	oldState	原来的状态
	///@param	newState	新的状态
	virtual void shiftAction(int oldState, int newState);
private:
	///总状态数量
	int m_totalState;
	
	///允许的状态切换表
	int *m_allowTable;
	
	///状态名称表
	char **m_stateName;
	
	///当前状态
	int m_currentState;
};

#endif
