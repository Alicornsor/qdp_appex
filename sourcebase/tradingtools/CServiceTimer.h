/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CServiceTimer.h
///@brief定义了类CServiceTimer
///@history 
///20060213	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CSERVICETIMER_H
#define CSERVICETIMER_H

#include "databaseData.h"

/////////////////////////////////////////////////////////////////////////
///CServiceTimer是一个提供系统服务的定时器，根据时钟同步的情况，发出恰当
///的准点的时钟信号，供业务系统使用
///@author	xuzh
///@version	1.0,20060114
/////////////////////////////////////////////////////////////////////////
class CServiceTimer: public CCurrentTimeCommitTrigger
{
public:
	///构造函数
	///@param	everyMillisec	每隔多少毫秒发出一个服务时间触发
	CServiceTimer(int everyMillisec);
	
	///确认更新后触发
	///@param	pCurrentTime	被刷新的CCurrentTime
	///@param	poldCurrentTime	原来的值
	virtual void commitUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pOldCurrentTime);
	
	///到达服务时间触发的事件
	///@param	pServiceTime	到达的服务时间
	virtual void onTime(CWriteableCurrentTime *pServiceTime)=0;
private:
	///将一天内的时间折算为毫秒数
	///@param	currTime	当前时间
	///@param	currMillisec	当前毫秒
	///@param	折算为的毫秒数
	int getMillisec(CReadOnlyTimeType &currTime, CReadOnlyMillisecType &currMillisec);
	
	///将折算的毫秒数转换为时间
	///@param	pCurrTime	返回的当前时间
	///@param	pMillisec	返回的当前毫秒
	///@param	要折算的毫秒数
	void getTime(CTimeType *pCurrTime, CMillisecType *pMillisec, int millisec);

	///每隔多少毫秒发出一个服务时间触发
	int m_everyMillisec;
};

#endif
