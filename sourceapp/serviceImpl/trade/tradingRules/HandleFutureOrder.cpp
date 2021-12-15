/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file HandleFutureOrder.cpp
///@brief实现了类COrderInsertRules
///@history 
///20060113	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "HandleFutureOrder.h"
#include "tradingTools.h"

CHandleFutureOrder::CHandleFutureOrder(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult)
:CHandleOrder(pDB,pErrorEngine,pConfig,pTradeResult)
{
	m_pMoneyPosition = new CFutureMoneyPosition(pDB,pErrorEngine,pConfig);	
}

CHandleFutureOrder::~CHandleFutureOrder()
{
}

