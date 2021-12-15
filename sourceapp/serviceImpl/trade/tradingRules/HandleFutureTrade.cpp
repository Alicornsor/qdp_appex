/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file HandleFutureTrade.cpp
///@briefʵ������ CHandleFutureTrade
///@history 
///20130503	longqy@cffex.net		�������ļ�
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
