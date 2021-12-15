/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file HandleFutureOrder.h
///@brief定义了类 CHandleFutureOrder 。该类处理期货子类的订单
///@history 
///20130502	longqy@cffex.net		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CHandleFutureOrder_H
#define CHandleFutureOrder_H

#include "HandleOrder.h"


/////////////////////////////////////////////////////////////////////////
///CHandleFutureOrder 是一个处理期货类交易订单的类，是处理订单类的子类
///@author	xuzh
///@version	1.0,20130502
/////////////////////////////////////////////////////////////////////////
class CHandleFutureOrder : public CHandleOrder
{
public:
	///构造函数
	///@param	pDB	本实现使用的内存数据库
	///@param	pErrorEngine	用于报错的错误引擎
	CHandleFutureOrder(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult);
   ~CHandleFutureOrder();

protected:
	
};

#endif
