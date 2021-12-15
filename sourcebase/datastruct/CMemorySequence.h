/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CMemorySequence.h
///@brief定义了类CMemorySequence
///@history 
///20041001	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CMEMORYSEQUENCE_H
#define CMEMORYSEQUENCE_H

#include "CSequenceInterface.h"

/////////////////////////////////////////////////////////////////////////
///CMemorySequence是一个在内存中定义序列的类
///@author	xuzh
///@version	1.0,20041001
/////////////////////////////////////////////////////////////////////////
class CMemorySequence: public CSequenceInterface
{
public:
	///构造方法，创建此序列
	///@param	startValue	本系列的起始值
	CMemorySequence(int startValue=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CMemorySequence(void);
	
	virtual int isA(char *objectType);
	virtual char *getType(void);
	virtual void output(CLogger *pLogger,int indent=0);

	///获取此序列的下一个值
	///@return	下一个值
	virtual int getNextValue(void);

	///获取此需要的当前值
	///@return	当前值
	virtual int getCurrentValue(void);

	///初始化该序列
	///@param nCurrValue 序列初始值
	virtual void initValue(int nCurrValue);
private:
	int m_CurrentValue;
	int m_StartValue;
};

#endif
