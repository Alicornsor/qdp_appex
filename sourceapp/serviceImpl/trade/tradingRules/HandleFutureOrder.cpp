/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file HandleFutureOrder.cpp
///@briefʵ������COrderInsertRules
///@history 
///20060113	xuzh		�������ļ�
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

