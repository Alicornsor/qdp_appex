/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file tradingTools.cpp
///@brief实现了与交易有关的若干工具函数
///@history 
///20050214	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "errorDefine.h"
#include "CMemorySequence.h"
#include "tradingTools.h"
#include "monitorIndex.h"

const CInvestorIDType defaultInvestorID="00000000";
const CParticipantIDType defaultParticipantID="00000000";
const CParticipantIDType defaultClearingParticipantID="clearing";
const CClientIDType defaultClientID="00000000";
const CInstrumentIDType defaultInstrumentID="default";
const CProductIDType defaultProductID="default";
const CHedgeFlagType defaultHedgeFlag='1';
const CUserIDType defaultUserID="00000000";
CTradingSystemNameType tradingSystemName;
const CDateType defaultDate="19000101";
const CTimeType defaultTime="00:00:00";
const CExchangeIDType defaultExchangeID="default";

//#define TEST_RULE

//日期改为从Exchange表取，by wangwei,20130604
CReadOnlyDateType getTradingDay(CMemoryDB *pDB)
{
// 	//暂时不考虑对多交易所的支持
// 	CExchange *pExchange=NULL;
// 	pExchange=pDB->m_ExchangeFactory->getFirst();
// 	pDB->m_ExchangeFactory->endGet();
// 	if (pExchange==NULL)
// 	{
// 	#ifdef TEST_RULE
// 		static CDateType defaultDate="20060101";
// 	#else
// 		static CDateType defaultDate="19000101";
// 	#endif
// 		return defaultDate;
// 	}
//	return pExchange->TradingDay;
	//从system里面取得交易日

	CSystemStatus *pSystemStatus=NULL;
	pSystemStatus = pDB->m_SystemStatusFactory->getFirst();
	pDB->m_SystemStatusFactory->endGet();
	if(pSystemStatus==NULL)
	{
		return defaultDate;
	}
	return pSystemStatus->TradingDay;
}


void getTradingDay(CMemoryDB *pDB,int *pYear,int *pMonth,int *pDay)
{
	CReadOnlyDateType &today=getTradingDay(pDB);
	*pYear=(today[0]-'0')*1000+
		(today[1]-'0')*100+
		(today[2]-'0')*10+
		(today[3]-'0');
	*pMonth=(today[4]-'0')*10+
		(today[5]-'0');
	*pDay=(today[6]-'0')*10+
		(today[7]-'0');
}

CReadOnlyTimeType getCurrentTime(CMemoryDB *pDB)
{
	static CMemoryDB *pLastDB=NULL;

	if (pDB!=NULL)
	{
		pLastDB=pDB;
	}
	else
	{
		pDB=pLastDB;
	}

	if (pDB==NULL)
	{
		return defaultTime;
	}

	CCurrentTime *pCurrTime;
	pCurrTime=pDB->m_CurrentTimeFactory->getFirst();
	pDB->m_CurrentTimeFactory->endGet();
	if (pCurrTime==NULL)
	{
		///没有设过时间
		return defaultTime;
	}
	else
	{
		///设过时间
		return pCurrTime->CurrTime;
	}
}

CReadOnlyTimeType getOldTime(CMemoryDB *pDB)
{
	CCurrentTime *pCurrTime;
	pCurrTime=pDB->m_CurrentTimeFactory->getFirst();
	pDB->m_CurrentTimeFactory->endGet();
	if (pCurrTime==NULL)
	{
		///没有设过时间
		return defaultTime;
	}
	else
	{
		///设过时间
		return pCurrTime->OldTime;
	}
}

void getCurrentTime(CMemoryDB *pDB, CTimeType *pTime, CMillisecType *pMillisec)
{
	CCurrentTime *pCurrTime;
	pCurrTime=pDB->m_CurrentTimeFactory->getFirst();
	pDB->m_CurrentTimeFactory->endGet();
	if (pCurrTime==NULL)
	{
		///没有设过时间
		*pTime="00:00:00";
		*pMillisec=0;
		return;
	}
	else
	{
		///设过时间
		*pTime=pCurrTime->CurrTime.getValue();
		*pMillisec=pCurrTime->CurrMillisec;
		return;
	}
}

void setCurrentTime(CMemoryDB *pDB, CWriteableCurrentTime *pTime, CTransaction *pTransaction)
{
	CCurrentTime *pOldTime;
	pOldTime=pDB->m_CurrentTimeFactory->getFirst();
	pDB->m_CurrentTimeFactory->endGet();
	if (pOldTime==NULL)
	{
		///第一次设时间
		pTime->CurrDate="19700101";
		pTime->OldTime="00:00:00";
		pTime->OldMillisec=0;
		pOldTime=pDB->m_CurrentTimeFactory->add(pTime,pTransaction);
//		new CStringMonitorIndex("CurrentTime",pOldTime->CurrTime,10);
	}
	else
	{
		///非第一次设时间
		pTime->OldTime=pOldTime->CurrTime;
		pTime->OldMillisec=pOldTime->CurrMillisec;
		pDB->m_CurrentTimeFactory->update(pOldTime,pTime,pTransaction);
	}
}

int getSecond(CReadOnlyUserIDType &theTime)
{
	return (theTime[6]-'0')*10+theTime[7]-'0';
}

int getSecondOfDay(CReadOnlyUserIDType &theTime)
{
	const char *pTime=theTime;
	int hour=(pTime[0]-'0')*10+(pTime[1]-'0');
	int minute=(pTime[3]-'0')*10+(pTime[4]-'0');
	int second=(pTime[6]-'0')*10+(pTime[7]-'0');
	return (hour*60+minute)*60+second;
}

/*longqy
CInstrumentStatusType getInstrumentStatus(CInstrument *pInstrument)
{
	if (pInstrument->getInstrumentStatus()==NULL)
	{
		return IS_BeforeTrading;
	}
	return pInstrument->getInstrumentStatus()->InstrumentStatus;
}
*/

CReadOnlyDataSyncStatusType getDataSyncStatus(CMemoryDB *pDB)
{
	CDataSyncStatus *pStatus=NULL;
	pStatus=pDB->m_DataSyncStatusFactory->getFirst();
	pDB->m_DataSyncStatusFactory->endGet();
	if (pStatus==NULL)
	{
		return DS_Asynchronous;
	}
	return pStatus->DataSyncStatus;
}

CDirectionType getReverseDirection(CReadOnlyDirectionType direction)
{
	if (direction==D_Buy)
	{
		return D_Sell;
	}
	else
	{
		return D_Buy;
	}
}

void setTradable(CWriteableOrder *pOrder)
{
/*longqy
	switch (pOrder->OrderStatus)
	{
	case OST_PartTradedQueueing:
	case OST_NoTradeQueueing:
		pOrder->Tradable=1;
		break;
	default:
		pOrder->Tradable=0;
	}
*/
}

bool needActiveStopOrder(COrder *pOrder, CReadOnlyPriceType &lastPrice)
{
	if (pOrder->Direction==D_Buy)
	{
		///买入止损单
		if (lastPrice>=pOrder->StopPrice)
		{
			///目前价格已经高于止损价格
			return true;
		}
		else
		{
			///目前价格还没有高于止损价格
			return false;
		}
	}
	else
	{
		///卖出止损单
		if (lastPrice<=pOrder->StopPrice)
		{
			///目前价格已经低于止损价格
			return true;
		}
		else
		{
			///目前价格还没有低于止损价格
			return false;
		}
	}
}
/*longqy
void setStopOrderStatus(CWriteableOrder *pOrder, CMarketData *pMarketData)
{
	if (needActiveStopOrder(pOrder,pMarketData->LastPrice))
	{
		pOrder->OrderStatus=OST_NoTradeQueueing;
	}
	else
	{
		pOrder->OrderStatus=OST_NoTradeNotQueueing;
	}
}
*/

void setOrderStatus(CWriteableOrder *pOrder)
{
/* longqy
	pOrder->VolumeTotal=pOrder->VolumeTotalOriginal-pOrder->VolumeTraded;

	if (pOrder->VolumeTotal<=0)
	{
		//已经全部成交
		pOrder->OrderStatus=OST_AllTraded;
	}
	else if (pOrder->VolumeTotal==pOrder->VolumeTotalOriginal)
	{
		//一点都没有成交
		pOrder->OrderStatus=OST_NoTradeQueueing;
	}
	else
	{
		//成交了部分
		pOrder->OrderStatus=OST_PartTradedQueueing;
	}
*/	
}

/*longqy
CReadOnlyParticipantIDType *getClearingPartID(CParticipant *pParticipant)
{
	if (pParticipant->MemberType==MT_Compositive)
	{
		///综合会员，那就不用找会员号了
		return &(pParticipant->ParticipantID);
	}
	if (pParticipant->MemberType==MT_Settlement)
	{
		///结算会员，没有对应的结算会员了
		return NULL;
	}
	if (pParticipant->getClearingTradingPart()==NULL)
	{
		///找不到对应的结算会员号
		return NULL;
	}
	return &(pParticipant->getClearingTradingPart()->ClearingPartID);
}
*/
/*longqy
CReadOnlyPriceType &getPreSettlementPrice(CInstrument *pInstrument)
{
	static CPriceType defaultPrice=0.0;
	CMarketData *pMarketData=pInstrument->getMarketData();
	if (pMarketData==NULL)
	{
		return defaultPrice;
	}
	if (!pMarketData->PreSettlementPrice.isNull() && (pMarketData->PreSettlementPrice > 0.0))
	{
		return pMarketData->PreSettlementPrice;
	}
	if (!pMarketData->PreClosePrice.isNull())
	{
		return pMarketData->PreClosePrice;
	}
	return defaultPrice;
}
*/

///-----
///	xuzh，20070226：增加了设置交易系统名称的功能，将从登录响应中返回
///-----
void setTradingSystemName(CConfig *pConfig)
{
	tradingSystemName=pConfig->getConfig("TradingSystemName");
	if (tradingSystemName.isNull())
	{
		tradingSystemName="Trading System";
	}
}
