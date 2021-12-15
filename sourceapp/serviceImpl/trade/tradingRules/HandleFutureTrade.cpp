/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file HandleFutureTrade.cpp
///@brief实现了类 CHandleFutureTrade
///@history 
///20130503	longqy@cffex.net		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "HandleFutureTrade.h"
#include "tradingTools.h"

CHandleFutureTrade::CHandleFutureTrade(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult)
:CHandleTrade(pDB,pErrorEngine,pConfig,pTradeResult)
{
    m_pMoneyPosition = new CFutureMoneyPosition(pDB,pErrorEngine,pConfig);
}

CHandleFutureTrade::~CHandleFutureTrade()
{
}
