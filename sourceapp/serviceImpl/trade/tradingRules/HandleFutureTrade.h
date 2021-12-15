/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file HandleFutureTrade.h
///@brief定义了类 CHandleFutureTrade
///@history 
///20130503	longqy@cffex.net		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CHandleFutureTrade_H
#define CHandleFutureTrade_H

#include "HandleTrade.h"
#include "baseAlgorithms.h"

/////////////////////////////////////////////////////////////////////////
///CHandleFutureTrade 是一个处理股指期货订单成交的类
///@author	xuzh
///@version	1.0,20130503
/////////////////////////////////////////////////////////////////////////
class CHandleFutureTrade : public CHandleTrade
{
public:
	///构造函数
	///@param	pDB	本实现使用的内存数据库
	///@param	pErrorEngine	用于报错的错误引擎
	CHandleFutureTrade(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult);
   ~CHandleFutureTrade();
protected:

	CBaseAlgorithms baseAlgorithms;
};
#endif
