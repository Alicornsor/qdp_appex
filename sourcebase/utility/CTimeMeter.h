/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CTimeMeter.h
///@brief定义了类CTimeMeter
///@history 
///20050209	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CTIMEMETER_H
#define CTIMEMETER_H

#include "platform.h"
#include "CBaseObject.h"

enum
{
	TIME_METER_ALL=0,
	TIME_VALID_ORDER,
	TIME_SAVE_ORDER,
	TIME_MAKE_TRADE,
	TIME_ADD,
	TIME_UPDATE,
	TIME_DELETE,
	TIME_RETRIEVE,
	TIME_GET,
	TIME_QUERY,
	TIME_UPDATE_TRANSACTION_DATA,
	TIME_RETRIEVE_TRANSACTION_DATA,
	TIME_GET_TRANSACTION_DATA,
	TIME_UPDATE_COPY,
	TIME_UPDATE_INDEX,
	TIME_UPDATE_TRIGGER,
	TIME_UPDATE_RESOURCE,
	TIME_UPDATE_NO_TRANSACTION,
	MAX_TIME_METER
};

/////////////////////////////////////////////////////////////////////////
///CTimeMeter是一个秒表类，用于在毫秒范围上计算用过的时间。目前的实现不能
///支持跨天
///@author	xuzh
///@version	1.0,20050209
/////////////////////////////////////////////////////////////////////////
class CTimeMeter: public CBaseObject
{
public:
	///构造函数
	///@参数	name	秒表的名称
	///@参数	allowStart	是否允许开始
	CTimeMeter(char *name,int allowStart=1);
	
	///析构函数
	virtual ~CTimeMeter(void);
	
	virtual int isA(char *objectType);
	virtual char *getType(void);
	virtual void output(CLogger *pLogger,int indent=0);

	///开始运行
	///@exception	CDesignError 如果已经开始运行，就派出异常
	void start(void);
	
	///结束运行
	///@exception	CDesignError 如果没有开始运行，就派出异常
	void stop(void);
	
	///@参数	allowStart	是否允许开始
	void allow(int allowStart);
	
	///返回本秒表记录的时间值，以毫秒为单位
	///@return	本秒表记录的时间值
	int getTime(void);
	
	
	///返回本秒表被叫用的次数
	///@return	本秒表记录的叫用次数
	int getCallCount(void);
	
	///将本秒表的结果输出到output上
	///@param	output	用于输出的文件
	void display(FILE *output);

	///获取本秒表的名称
	///@return	返回本秒表的名称
	char *getName(void);
private:
	///本秒表的名称
	char *m_name;
	
	///本秒表记录的总时间值
	int m_time;
	
	///本秒表是否正在运行
	int m_isStarted;
	
	///上次开始运行的时间
	long m_lastStartTime;
	
	///是否允许开始
	int m_allowStart;
	
	///被叫用的次数
	int m_callCount;
};

extern CTimeMeter *timeMeters[MAX_TIME_METER];
/*
#define METER_START(i)	{ timeMeters[i]->start();}
#define METER_END(i)	{ timeMeters[i]->stop(); }
*/
#define METER_START(i)
#define METER_END(i)

#endif
