!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company 上海量投网络科技有限公司
///@file CDumpLog.h
///@brief定义了类CDumpLog
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CDUMPLOG_H
#define CDUMPLOG_H

#include "CMemoryDB.h"

!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
/////////////////////////////////////////////////////////////////////////
///C!!@name!!DumpTrigger是操作!!@usage!!时的触发器，在变化时进行输出
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@name!!DumpTrigger: public C!!@name!!ActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	C!!@name!!DumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~C!!@name!!DumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	p!!@name!!	要加入的!!@name!!
	virtual void beforeAdd(CWriteable!!@name!! *p!!@name!!);
	
	///更新前触发	
	///@param	p!!@name!!	被刷新的C!!@name!!
	///@param	pNew!!@name!!	新的值
	virtual void beforeUpdate(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pNew!!@name!!);
	
	///删除前触发
	///@param	p!!@name!!	要删除的C!!@name!!
	virtual void beforeRemove(C!!@name!! *p!!@name!!);
	
private:
	FILE *m_output;
	int m_flag;
};

!!endif!!
!!next!!
/////////////////////////////////////////////////////////////////////////
///CDumpLog是一个将所有的修改以Dump方式输出的交易引擎提醒实现
///@author	xuzh
///@version	1.0,20041001
/////////////////////////////////////////////////////////////////////////
class CDumpLog
{
public:
	///构造方法，创建一个输出器
	///@param	pDB	要输出的内存数据库
	///@param	pConfig	配置信息
	CDumpLog(CMemoryDB *pDB, CConfig *pConfig);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CDumpLog(void);

	///启动dump
	void start(void);
	
	///停止dump
	void stop(void);
	
	///是否已经启动
	///@return	1表示已经启动，0表示没有启动
	int isStarted(void);
	
	///输出信息
	///@param	format	信息格式，按照fprintf的要求
	///@param	...	信息的详细内容
	void dumpMsg(char *format,...);

private:
	///输出文件
	FILE *m_DumpOutput;
	
	///内存数据库
	CMemoryDB *m_DB;
	
	///是否已经启动
	int m_Started;
	
	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!
	C!!@name!!DumpTrigger *m_!!@name!!Trigger;
	!!endif!!
	!!next!!
};

#endif
!!leave!!