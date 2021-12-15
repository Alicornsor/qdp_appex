/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseFactories.pp
///@brief 实现了若干个内存数据库的对象工厂
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "BaseDataStruct.h"
#include "databaseFactories.h"
#include "databaseResources.h"
#include "monitorIndex.h"

//#define COUNT_SEARCH
int compareForTradingdayIndexinDataSyncStatus(const void *pV1, const void *pV2)
{
	CDataSyncStatus *p1,*p2;
	p1=(CDataSyncStatus *)pV1;
	p2=(CDataSyncStatus *)pV2;
	switch (compare(p1->TradingDay.getValue(),p2->TradingDay.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByTradingdayForDataSyncStatus=0;
#endif
CDataSyncStatus *CDataSyncStatusFactory::findByTradingday( const CReadOnlyDateType&  TradingDay)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByTradingday of CDataSyncStatus while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByTradingdayForDataSyncStatus++;
#endif
	CAVLNode *pNode;
	compareObject.TradingDay=TradingDay.getValue();
	pNode=pTradingdayIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CDataSyncStatus *)(pNode->pObject);
}


int compareForTradingDayinSystemStatus(const void *pV1, const void *pV2)
{
	CSystemStatus *p1,*p2;
	p1=(CSystemStatus *)pV1;
	p2=(CSystemStatus *)pV2;
	switch (compare(p1->TradingDay.getValue(),p2->TradingDay.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByTradingDayForSystemStatus=0;
#endif
CSystemStatus *CSystemStatusFactory::findByTradingDay( const CReadOnlyDateType&  TradingDay)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByTradingDay of CSystemStatus while run level < 0");
	}
	CSystemStatus *theSystemStatus;
	for (theSystemStatus=(CSystemStatus *)(pMem->getFirst());
		theSystemStatus!=NULL;
		theSystemStatus=(CSystemStatus *)(pMem->getNext()))
	{
		if (compare(theSystemStatus->TradingDay.getValue(),TradingDay.getValue())!=0)
		{
			continue;
		}
		return theSystemStatus;
	}
	return NULL;
}

CSystemStatus *CSystemStatusFactory::findByPK( const CReadOnlyDateType&  TradingDay)
{
	return findByTradingDay(TradingDay);
}
	
CSystemStatus *CSystemStatusFactory::findByPK(CWriteableSystemStatus *pSystemStatus)
{
	return findByPK(
		pSystemStatus->TradingDay
		);
}

bool CSystemStatusFactory::retrieveByPK(CWriteableSystemStatus *pSystemStatus)
{
	CSystemStatus *pOriginalSystemStatus;
	pOriginalSystemStatus=findByPK(pSystemStatus);
	if (pOriginalSystemStatus==NULL)
	{
		return false;
	}
	retrieve(pOriginalSystemStatus,pSystemStatus);
	return true;
}

CSystemStatus *CSystemStatusFactory::addByPK(CWriteableSystemStatus *pSystemStatus, CTransaction *pTransaction)
{
	CSystemStatus *pOriginalSystemStatus;
	pOriginalSystemStatus=findByPK(pSystemStatus);
	if (pOriginalSystemStatus != NULL)
	{
		return NULL;
	}
	return add(pSystemStatus,pTransaction);
}

bool CSystemStatusFactory::updateByPK(CWriteableSystemStatus *pSystemStatus, CTransaction *pTransaction, bool updateIndex)
{
	CSystemStatus *pOriginalSystemStatus;
	pOriginalSystemStatus=findByPK(pSystemStatus);
	if (pOriginalSystemStatus==NULL)
	{
		return false;
	}
	pSystemStatus->calAllHash();
	update(pOriginalSystemStatus,pSystemStatus,pTransaction,updateIndex);
	return true;
}

bool CSystemStatusFactory::removeByPK(CWriteableSystemStatus *pSystemStatus, CTransaction *pTransaction)
{
	CSystemStatus *pOriginalSystemStatus;
	pOriginalSystemStatus=findByPK(pSystemStatus);
	if (pOriginalSystemStatus==NULL)
	{
		return false;
	}
	remove(pOriginalSystemStatus,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int findByExchangeIDAndOrderSysIDForOrder=0;
#endif
COrder *COrderFactory::findByExchangeIDAndOrderSysID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyOrderSysIDType&  OrderSysID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByExchangeIDAndOrderSysID of COrder while run level < 0");
	}
	CHashIndexNode *pNode;
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.OrderSysID=OrderSysID.getValue();
	
	compareObject.calHashExchangeIDOrderSysID();
	for (pNode=pExchangeIDOrderSysIDHashIndex->searchFirstEqual(compareObject.HashExchangeIDOrderSysID);
		pNode!=NULL;
		pNode=pExchangeIDOrderSysIDHashIndex->searchNextEqual(pNode))
	{
		if (((COrder *)(pNode->pObject))->HashExchangeIDOrderSysID != compareObject.HashExchangeIDOrderSysID)
		{
			continue;
		}
		if (compare(((COrder *)(pNode->pObject))->ExchangeID.getValue(),ExchangeID.getValue())!=0)
		{
			continue;
		}
		if (compare(((COrder *)(pNode->pObject))->OrderSysID.getValue(),OrderSysID.getValue())!=0)
		{
			continue;
		}
		return (COrder *)(pNode->pObject);
	}
	return NULL;
}

COrder *COrderFactory::findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyOrderSysIDType&  OrderSysID)
{
	return findByExchangeIDAndOrderSysID(ExchangeID, OrderSysID);
}
	
COrder *COrderFactory::findByPK(CWriteableOrder *pOrder)
{
	return findByPK(
		pOrder->ExchangeID
		,
		pOrder->OrderSysID
		);
}

bool COrderFactory::retrieveByPK(CWriteableOrder *pOrder)
{
	COrder *pOriginalOrder;
	pOriginalOrder=findByPK(pOrder);
	if (pOriginalOrder==NULL)
	{
		return false;
	}
	retrieve(pOriginalOrder,pOrder);
	return true;
}

COrder *COrderFactory::addByPK(CWriteableOrder *pOrder, CTransaction *pTransaction)
{
	COrder *pOriginalOrder;
	pOriginalOrder=findByPK(pOrder);
	if (pOriginalOrder != NULL)
	{
		return NULL;
	}
	return add(pOrder,pTransaction);
}

bool COrderFactory::updateByPK(CWriteableOrder *pOrder, CTransaction *pTransaction, bool updateIndex)
{
	COrder *pOriginalOrder;
	pOriginalOrder=findByPK(pOrder);
	if (pOriginalOrder==NULL)
	{
		return false;
	}
	pOrder->calAllHash();
	update(pOriginalOrder,pOrder,pTransaction,updateIndex);
	return true;
}

bool COrderFactory::removeByPK(CWriteableOrder *pOrder, CTransaction *pTransaction)
{
	COrder *pOriginalOrder;
	pOriginalOrder=findByPK(pOrder);
	if (pOriginalOrder==NULL)
	{
		return false;
	}
	remove(pOriginalOrder,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int findByUserIDAndUserOrderLocalIDForOrder=0;
#endif
COrder *COrderFactory::findByUserIDAndUserOrderLocalID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyUserOrderLocalIDType&  UserOrderLocalID,  const CReadOnlyFrontIDType&  FrontID,  const CReadOnlySessionIDType&  SessionID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByUserIDAndUserOrderLocalID of COrder while run level < 0");
	}
	CHashIndexNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.UserID=UserID.getValue();
	compareObject.UserOrderLocalID=UserOrderLocalID.getValue();
	compareObject.FrontID=FrontID.getValue();
	compareObject.SessionID=SessionID.getValue();
	
	compareObject.calHashUserIDAndUserOrderLocalID();
	for (pNode=pUserIDAndUserOrderLocalIDHashIndex->searchFirstEqual(compareObject.HashUserIDAndUserOrderLocalID);
		pNode!=NULL;
		pNode=pUserIDAndUserOrderLocalIDHashIndex->searchNextEqual(pNode))
	{
		if (((COrder *)(pNode->pObject))->HashUserIDAndUserOrderLocalID != compareObject.HashUserIDAndUserOrderLocalID)
		{
			continue;
		}
		if (compare(((COrder *)(pNode->pObject))->BrokerID.getValue(),BrokerID.getValue())!=0)
		{
			continue;
		}
		if (compare(((COrder *)(pNode->pObject))->UserID.getValue(),UserID.getValue())!=0)
		{
			continue;
		}
		if (compare(((COrder *)(pNode->pObject))->UserOrderLocalID.getValue(),UserOrderLocalID.getValue())!=0)
		{
			continue;
		}
		if (compare(((COrder *)(pNode->pObject))->FrontID.getValue(),FrontID.getValue())!=0)
		{
			continue;
		}
		if (compare(((COrder *)(pNode->pObject))->SessionID.getValue(),SessionID.getValue())!=0)
		{
			continue;
		}
		return (COrder *)(pNode->pObject);
	}
	return NULL;
}



#ifdef COUNT_SEARCH
int multiFindAllByUserIDForOrder=0;
#endif

COrder *COrderFactory::startFindAllByUserID( const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByUserID of COrder while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByUserID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByUserID();
	}

	///记录所有的查询值
	queryUserIDInSearchAllByUserID= UserID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByUserID=(COrder *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByUserID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByUserID来寻找下一个
	if (compare(pLastFoundInSearchAllByUserID->UserID.getValue(),UserID.getValue()))
	{
		return findNextAllByUserID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByUserID;
}

COrder *COrderFactory::findNextAllByUserID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByUserID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByUserID=(COrder *)(pMem->getNext());
		if (pLastFoundInSearchAllByUserID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByUserID->UserID,queryUserIDInSearchAllByUserID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByUserID;
	}
}

void COrderFactory::endFindAllByUserID(void)
{
	pLastFoundInSearchAllByUserID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByInvestorIDForOrder=0;
#endif

COrder *COrderFactory::startFindAllByInvestorID( const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByInvestorID of COrder while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByInvestorID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByInvestorID();
	}

	///记录所有的查询值
	queryInvestorIDInSearchAllByInvestorID= InvestorID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByInvestorID=(COrder *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByInvestorID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByInvestorID来寻找下一个
	if (compare(pLastFoundInSearchAllByInvestorID->InvestorID.getValue(),InvestorID.getValue()))
	{
		return findNextAllByInvestorID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByInvestorID;
}

COrder *COrderFactory::findNextAllByInvestorID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByInvestorID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByInvestorID=(COrder *)(pMem->getNext());
		if (pLastFoundInSearchAllByInvestorID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByInvestorID->InvestorID,queryInvestorIDInSearchAllByInvestorID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByInvestorID;
	}
}

void COrderFactory::endFindAllByInvestorID(void)
{
	pLastFoundInSearchAllByInvestorID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByExchIDInvIDUserIDForOrder=0;
#endif

COrder *COrderFactory::startFindAllByExchIDInvIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInvestorIDType& InvestorID,  const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByExchIDInvIDUserID of COrder while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByExchIDInvIDUserID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByExchIDInvIDUserID();
	}

	///记录所有的查询值
	queryExchangeIDInSearchAllByExchIDInvIDUserID= ExchangeID.getValue();
	queryInvestorIDInSearchAllByExchIDInvIDUserID= InvestorID.getValue();
	queryUserIDInSearchAllByExchIDInvIDUserID= UserID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByExchIDInvIDUserID=(COrder *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByExchIDInvIDUserID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByExchIDInvIDUserID来寻找下一个
	if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->ExchangeID.getValue(),ExchangeID.getValue()))
	{
		return findNextAllByExchIDInvIDUserID();
	}
	if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->InvestorID.getValue(),InvestorID.getValue()))
	{
		return findNextAllByExchIDInvIDUserID();
	}
	if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->UserID.getValue(),UserID.getValue()))
	{
		return findNextAllByExchIDInvIDUserID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByExchIDInvIDUserID;
}

COrder *COrderFactory::findNextAllByExchIDInvIDUserID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByExchIDInvIDUserID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByExchIDInvIDUserID=(COrder *)(pMem->getNext());
		if (pLastFoundInSearchAllByExchIDInvIDUserID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->ExchangeID,queryExchangeIDInSearchAllByExchIDInvIDUserID))
		{
			continue;
		}
		if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->InvestorID,queryInvestorIDInSearchAllByExchIDInvIDUserID))
		{
			continue;
		}
		if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->UserID,queryUserIDInSearchAllByExchIDInvIDUserID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByExchIDInvIDUserID;
	}
}

void COrderFactory::endFindAllByExchIDInvIDUserID(void)
{
	pLastFoundInSearchAllByExchIDInvIDUserID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByExchIDInstruIDUserIDForOrder=0;
#endif

COrder *COrderFactory::startFindAllByExchIDInstruIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& InstrumentID,  const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByExchIDInstruIDUserID of COrder while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByExchIDInstruIDUserID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByExchIDInstruIDUserID();
	}

	///记录所有的查询值
	queryExchangeIDInSearchAllByExchIDInstruIDUserID= ExchangeID.getValue();
	queryInstrumentIDInSearchAllByExchIDInstruIDUserID= InstrumentID.getValue();
	queryUserIDInSearchAllByExchIDInstruIDUserID= UserID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByExchIDInstruIDUserID=(COrder *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByExchIDInstruIDUserID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByExchIDInstruIDUserID来寻找下一个
	if (compare(pLastFoundInSearchAllByExchIDInstruIDUserID->ExchangeID.getValue(),ExchangeID.getValue()))
	{
		return findNextAllByExchIDInstruIDUserID();
	}
	if (compare(pLastFoundInSearchAllByExchIDInstruIDUserID->UserID.getValue(),UserID.getValue()))
	{
		return findNextAllByExchIDInstruIDUserID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByExchIDInstruIDUserID;
}

COrder *COrderFactory::findNextAllByExchIDInstruIDUserID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByExchIDInstruIDUserID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByExchIDInstruIDUserID=(COrder *)(pMem->getNext());
		if (pLastFoundInSearchAllByExchIDInstruIDUserID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByExchIDInstruIDUserID->ExchangeID,queryExchangeIDInSearchAllByExchIDInstruIDUserID))
		{
			continue;
		}
		if (compare(pLastFoundInSearchAllByExchIDInstruIDUserID->UserID,queryUserIDInSearchAllByExchIDInstruIDUserID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByExchIDInstruIDUserID;
	}
}

void COrderFactory::endFindAllByExchIDInstruIDUserID(void)
{
	pLastFoundInSearchAllByExchIDInstruIDUserID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllForOrder=0;
#endif

COrder *COrderFactory::startFindAll()
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAll of COrder while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAll!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAll();
	}

	///记录所有的查询值

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAll=(COrder *)(pMem->getFirst());
	
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAll来寻找下一个
	
	///返回找到的结果
	return pLastFoundInSearchAll;
}

COrder *COrderFactory::findNextAll(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAll=(COrder *)(pMem->getNext());
		if (pLastFoundInSearchAll==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		///返回找到的结果
		return pLastFoundInSearchAll;
	}
}

void COrderFactory::endFindAll(void)
{
	pLastFoundInSearchAll=NULL;
}

int compareForExchangeIDTradeIDIndexinTrade(const void *pV1, const void *pV2)
{
	CTrade *p1,*p2;
	p1=(CTrade *)pV1;
	p2=(CTrade *)pV2;
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->TradeID.getValue(),p2->TradeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForExchangeIDTradeIDOrderSysIDIndexinTrade(const void *pV1, const void *pV2)
{
	CTrade *p1,*p2;
	p1=(CTrade *)pV1;
	p2=(CTrade *)pV2;
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->TradeID.getValue(),p2->TradeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->OrderSysID.getValue(),p2->OrderSysID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByExchangeIDTradeIDOrderSysIDForTrade=0;
#endif
CTrade *CTradeFactory::findByExchangeIDTradeIDOrderSysID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyTradeIDType&  TradeID,  const CReadOnlyOrderSysIDType&  OrderSysID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByExchangeIDTradeIDOrderSysID of CTrade while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByExchangeIDTradeIDOrderSysIDForTrade++;
#endif
	CAVLNode *pNode;
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.TradeID=TradeID.getValue();
	compareObject.OrderSysID=OrderSysID.getValue();
	compareObject.ParticipantID="";
	compareObject.ClientID="";
	compareObject.InstrumentID="";
	pNode=pExchangeIDTradeIDOrderSysIDIndex->searchFirstGreatEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	if (compare(((CTrade *)(pNode->pObject))->ExchangeID.getValue(),ExchangeID.getValue())!=0)
	{
		return NULL;
	}
	if (compare(((CTrade *)(pNode->pObject))->TradeID.getValue(),TradeID.getValue())!=0)
	{
		return NULL;
	}
	if (compare(((CTrade *)(pNode->pObject))->OrderSysID.getValue(),OrderSysID.getValue())!=0)
	{
		return NULL;
	}
	return (CTrade *)(pNode->pObject);
}

CTrade *CTradeFactory::findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyTradeIDType&  TradeID,  const CReadOnlyOrderSysIDType&  OrderSysID)
{
	return findByExchangeIDTradeIDOrderSysID(ExchangeID, TradeID, OrderSysID);
}
	
CTrade *CTradeFactory::findByPK(CWriteableTrade *pTrade)
{
	return findByPK(
		pTrade->ExchangeID
		,
		pTrade->TradeID
		,
		pTrade->OrderSysID
		);
}

bool CTradeFactory::retrieveByPK(CWriteableTrade *pTrade)
{
	CTrade *pOriginalTrade;
	pOriginalTrade=findByPK(pTrade);
	if (pOriginalTrade==NULL)
	{
		return false;
	}
	retrieve(pOriginalTrade,pTrade);
	return true;
}

CTrade *CTradeFactory::addByPK(CWriteableTrade *pTrade, CTransaction *pTransaction)
{
	CTrade *pOriginalTrade;
	pOriginalTrade=findByPK(pTrade);
	if (pOriginalTrade != NULL)
	{
		return NULL;
	}
	return add(pTrade,pTransaction);
}

bool CTradeFactory::updateByPK(CWriteableTrade *pTrade, CTransaction *pTransaction, bool updateIndex)
{
	CTrade *pOriginalTrade;
	pOriginalTrade=findByPK(pTrade);
	if (pOriginalTrade==NULL)
	{
		return false;
	}
	pTrade->calAllHash();
	update(pOriginalTrade,pTrade,pTransaction,updateIndex);
	return true;
}

bool CTradeFactory::removeByPK(CWriteableTrade *pTrade, CTransaction *pTransaction)
{
	CTrade *pOriginalTrade;
	pOriginalTrade=findByPK(pTrade);
	if (pOriginalTrade==NULL)
	{
		return false;
	}
	remove(pOriginalTrade,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int multiFindByExchangeIDAndTradeIDForTrade=0;
#endif

CTrade *CTradeFactory::startFindByExchangeIDAndTradeID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyTradeIDType& TradeID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindByExchangeIDAndTradeID of CTrade while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchByExchangeIDAndTradeID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindByExchangeIDAndTradeID();
	}

	///记录所有的查询值
	queryExchangeIDInSearchByExchangeIDAndTradeID= ExchangeID.getValue();
	queryTradeIDInSearchByExchangeIDAndTradeID= TradeID.getValue();

#ifdef COUNT_SEARCH
	multiFindByExchangeIDAndTradeIDForTrade++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CTrade *theTrade;
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.TradeID=TradeID.getValue();
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchByExchangeIDAndTradeID=pExchangeIDTradeIDIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchByExchangeIDAndTradeID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	theTrade=(CTrade *)(pLastFoundInSearchByExchangeIDAndTradeID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theTrade->ExchangeID.getValue(),ExchangeID.getValue()))
	{
		pLastFoundInSearchByExchangeIDAndTradeID=NULL;
		return NULL;
	}
	if (compare(theTrade->TradeID.getValue(),TradeID.getValue()))
	{
		pLastFoundInSearchByExchangeIDAndTradeID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theTrade;
}

CTrade *CTradeFactory::findNextByExchangeIDAndTradeID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchByExchangeIDAndTradeID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindByExchangeIDAndTradeIDForTrade++;
#endif
	CTrade *theTrade;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchByExchangeIDAndTradeID=pExchangeIDTradeIDIndex->getNextNode(pLastFoundInSearchByExchangeIDAndTradeID);
	if (pLastFoundInSearchByExchangeIDAndTradeID==NULL)
	{
		return NULL;
	}

	theTrade=(CTrade *)(pLastFoundInSearchByExchangeIDAndTradeID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theTrade->ExchangeID,queryExchangeIDInSearchByExchangeIDAndTradeID))
	{
		pLastFoundInSearchByExchangeIDAndTradeID=NULL;
		return NULL;
	}
	if (compare(theTrade->TradeID,queryTradeIDInSearchByExchangeIDAndTradeID))
	{
		pLastFoundInSearchByExchangeIDAndTradeID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theTrade;
}

void CTradeFactory::endFindByExchangeIDAndTradeID(void)
{
	pLastFoundInSearchByExchangeIDAndTradeID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByExchIDInvIDUserIDForTrade=0;
#endif

CTrade *CTradeFactory::startFindAllByExchIDInvIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInvestorIDType& InvestorID,  const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByExchIDInvIDUserID of CTrade while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByExchIDInvIDUserID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByExchIDInvIDUserID();
	}

	///记录所有的查询值
	queryExchangeIDInSearchAllByExchIDInvIDUserID= ExchangeID.getValue();
	queryInvestorIDInSearchAllByExchIDInvIDUserID= InvestorID.getValue();
	queryUserIDInSearchAllByExchIDInvIDUserID= UserID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByExchIDInvIDUserID=(CTrade *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByExchIDInvIDUserID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByExchIDInvIDUserID来寻找下一个
	if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->ExchangeID.getValue(),ExchangeID.getValue()))
	{
		return findNextAllByExchIDInvIDUserID();
	}
	if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->InvestorID.getValue(),InvestorID.getValue()))
	{
		return findNextAllByExchIDInvIDUserID();
	}
	if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->UserID.getValue(),UserID.getValue()))
	{
		return findNextAllByExchIDInvIDUserID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByExchIDInvIDUserID;
}

CTrade *CTradeFactory::findNextAllByExchIDInvIDUserID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByExchIDInvIDUserID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByExchIDInvIDUserID=(CTrade *)(pMem->getNext());
		if (pLastFoundInSearchAllByExchIDInvIDUserID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->ExchangeID,queryExchangeIDInSearchAllByExchIDInvIDUserID))
		{
			continue;
		}
		if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->InvestorID,queryInvestorIDInSearchAllByExchIDInvIDUserID))
		{
			continue;
		}
		if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->UserID,queryUserIDInSearchAllByExchIDInvIDUserID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByExchIDInvIDUserID;
	}
}

void CTradeFactory::endFindAllByExchIDInvIDUserID(void)
{
	pLastFoundInSearchAllByExchIDInvIDUserID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByInvestorIDForTrade=0;
#endif

CTrade *CTradeFactory::startFindAllByInvestorID( const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByInvestorID of CTrade while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByInvestorID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByInvestorID();
	}

	///记录所有的查询值
	queryInvestorIDInSearchAllByInvestorID= InvestorID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByInvestorID=(CTrade *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByInvestorID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByInvestorID来寻找下一个
	if (compare(pLastFoundInSearchAllByInvestorID->InvestorID.getValue(),InvestorID.getValue()))
	{
		return findNextAllByInvestorID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByInvestorID;
}

CTrade *CTradeFactory::findNextAllByInvestorID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByInvestorID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByInvestorID=(CTrade *)(pMem->getNext());
		if (pLastFoundInSearchAllByInvestorID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByInvestorID->InvestorID,queryInvestorIDInSearchAllByInvestorID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByInvestorID;
	}
}

void CTradeFactory::endFindAllByInvestorID(void)
{
	pLastFoundInSearchAllByInvestorID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByExchIDInstruIDUserIDForTrade=0;
#endif

CTrade *CTradeFactory::startFindAllByExchIDInstruIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& InstrumentID,  const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByExchIDInstruIDUserID of CTrade while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByExchIDInstruIDUserID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByExchIDInstruIDUserID();
	}

	///记录所有的查询值
	queryExchangeIDInSearchAllByExchIDInstruIDUserID= ExchangeID.getValue();
	queryInstrumentIDInSearchAllByExchIDInstruIDUserID= InstrumentID.getValue();
	queryUserIDInSearchAllByExchIDInstruIDUserID= UserID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByExchIDInstruIDUserID=(CTrade *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByExchIDInstruIDUserID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByExchIDInstruIDUserID来寻找下一个
	if (compare(pLastFoundInSearchAllByExchIDInstruIDUserID->ExchangeID.getValue(),ExchangeID.getValue()))
	{
		return findNextAllByExchIDInstruIDUserID();
	}
	if (compare(pLastFoundInSearchAllByExchIDInstruIDUserID->UserID.getValue(),UserID.getValue()))
	{
		return findNextAllByExchIDInstruIDUserID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByExchIDInstruIDUserID;
}

CTrade *CTradeFactory::findNextAllByExchIDInstruIDUserID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByExchIDInstruIDUserID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByExchIDInstruIDUserID=(CTrade *)(pMem->getNext());
		if (pLastFoundInSearchAllByExchIDInstruIDUserID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByExchIDInstruIDUserID->ExchangeID,queryExchangeIDInSearchAllByExchIDInstruIDUserID))
		{
			continue;
		}
		if (compare(pLastFoundInSearchAllByExchIDInstruIDUserID->UserID,queryUserIDInSearchAllByExchIDInstruIDUserID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByExchIDInstruIDUserID;
	}
}

void CTradeFactory::endFindAllByExchIDInstruIDUserID(void)
{
	pLastFoundInSearchAllByExchIDInstruIDUserID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllForTrade=0;
#endif

CTrade *CTradeFactory::startFindAll()
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAll of CTrade while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAll!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAll();
	}

	///记录所有的查询值

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAll=(CTrade *)(pMem->getFirst());
	
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAll来寻找下一个
	
	///返回找到的结果
	return pLastFoundInSearchAll;
}

CTrade *CTradeFactory::findNextAll(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAll=(CTrade *)(pMem->getNext());
		if (pLastFoundInSearchAll==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		///返回找到的结果
		return pLastFoundInSearchAll;
	}
}

void CTradeFactory::endFindAll(void)
{
	pLastFoundInSearchAll=NULL;
}

int compareForAPIIDAndOrderLocalIDIndexinPreOrder(const void *pV1, const void *pV2)
{
	CPreOrder *p1,*p2;
	p1=(CPreOrder *)pV1;
	p2=(CPreOrder *)pV2;
	switch (compare(p1->APIID.getValue(),p2->APIID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->OrderLocalID.getValue(),p2->OrderLocalID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForAPIIDIndexinPreOrder(const void *pV1, const void *pV2)
{
	CPreOrder *p1,*p2;
	p1=(CPreOrder *)pV1;
	p2=(CPreOrder *)pV2;
	switch (compare(p1->APIID.getValue(),p2->APIID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByAPIIDAndOrderLocalIDForPreOrder=0;
#endif
CPreOrder *CPreOrderFactory::findByAPIIDAndOrderLocalID( const CReadOnlyNumberType&  APIID,  const CReadOnlyOrderLocalIDType&  OrderLocalID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByAPIIDAndOrderLocalID of CPreOrder while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByAPIIDAndOrderLocalIDForPreOrder++;
#endif
	CAVLNode *pNode;
	compareObject.APIID=APIID.getValue();
	compareObject.OrderLocalID=OrderLocalID.getValue();
	pNode=pAPIIDAndOrderLocalIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CPreOrder *)(pNode->pObject);
}

CPreOrder *CPreOrderFactory::findByPK( const CReadOnlyNumberType&  APIID,  const CReadOnlyOrderLocalIDType&  OrderLocalID)
{
	return findByAPIIDAndOrderLocalID(APIID, OrderLocalID);
}
	
CPreOrder *CPreOrderFactory::findByPK(CWriteablePreOrder *pPreOrder)
{
	return findByPK(
		pPreOrder->APIID
		,
		pPreOrder->OrderLocalID
		);
}

bool CPreOrderFactory::retrieveByPK(CWriteablePreOrder *pPreOrder)
{
	CPreOrder *pOriginalPreOrder;
	pOriginalPreOrder=findByPK(pPreOrder);
	if (pOriginalPreOrder==NULL)
	{
		return false;
	}
	retrieve(pOriginalPreOrder,pPreOrder);
	return true;
}

CPreOrder *CPreOrderFactory::addByPK(CWriteablePreOrder *pPreOrder, CTransaction *pTransaction)
{
	CPreOrder *pOriginalPreOrder;
	pOriginalPreOrder=findByPK(pPreOrder);
	if (pOriginalPreOrder != NULL)
	{
		return NULL;
	}
	return add(pPreOrder,pTransaction);
}

bool CPreOrderFactory::updateByPK(CWriteablePreOrder *pPreOrder, CTransaction *pTransaction, bool updateIndex)
{
	CPreOrder *pOriginalPreOrder;
	pOriginalPreOrder=findByPK(pPreOrder);
	if (pOriginalPreOrder==NULL)
	{
		return false;
	}
	pPreOrder->calAllHash();
	update(pOriginalPreOrder,pPreOrder,pTransaction,updateIndex);
	return true;
}

bool CPreOrderFactory::removeByPK(CWriteablePreOrder *pPreOrder, CTransaction *pTransaction)
{
	CPreOrder *pOriginalPreOrder;
	pOriginalPreOrder=findByPK(pPreOrder);
	if (pOriginalPreOrder==NULL)
	{
		return false;
	}
	remove(pOriginalPreOrder,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int findByUserIDAndUserOrderLocalIDForPreOrder=0;
#endif
CPreOrder *CPreOrderFactory::findByUserIDAndUserOrderLocalID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyUserOrderLocalIDType&  UserOrderLocalID,  const CReadOnlyFrontIDType&  FrontID,  const CReadOnlySessionIDType&  SessionID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByUserIDAndUserOrderLocalID of CPreOrder while run level < 0");
	}
	CHashIndexNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.UserID=UserID.getValue();
	compareObject.UserOrderLocalID=UserOrderLocalID.getValue();
	compareObject.FrontID=FrontID.getValue();
	compareObject.SessionID=SessionID.getValue();
	
	compareObject.calHashUserIDAndUserOrderLocalID();
	for (pNode=pUserIDAndUserOrderLocalIDHashIndex->searchFirstEqual(compareObject.HashUserIDAndUserOrderLocalID);
		pNode!=NULL;
		pNode=pUserIDAndUserOrderLocalIDHashIndex->searchNextEqual(pNode))
	{
		if (((CPreOrder *)(pNode->pObject))->HashUserIDAndUserOrderLocalID != compareObject.HashUserIDAndUserOrderLocalID)
		{
			continue;
		}
		if (compare(((CPreOrder *)(pNode->pObject))->BrokerID.getValue(),BrokerID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CPreOrder *)(pNode->pObject))->UserID.getValue(),UserID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CPreOrder *)(pNode->pObject))->UserOrderLocalID.getValue(),UserOrderLocalID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CPreOrder *)(pNode->pObject))->FrontID.getValue(),FrontID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CPreOrder *)(pNode->pObject))->SessionID.getValue(),SessionID.getValue())!=0)
		{
			continue;
		}
		return (CPreOrder *)(pNode->pObject);
	}
	return NULL;
}



#ifdef COUNT_SEARCH
int multiFindByAPIIDForPreOrder=0;
#endif

CPreOrder *CPreOrderFactory::startFindByAPIID( const CReadOnlyNumberType& APIID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindByAPIID of CPreOrder while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchByAPIID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindByAPIID();
	}

	///记录所有的查询值
	queryAPIIDInSearchByAPIID= APIID.getValue();

#ifdef COUNT_SEARCH
	multiFindByAPIIDForPreOrder++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CPreOrder *thePreOrder;
	compareObject.APIID=APIID.getValue();
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchByAPIID=pAPIIDIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchByAPIID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	thePreOrder=(CPreOrder *)(pLastFoundInSearchByAPIID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(thePreOrder->APIID.getValue(),APIID.getValue()))
	{
		pLastFoundInSearchByAPIID=NULL;
		return NULL;
	}

	///返回找到的结果
	return thePreOrder;
}

CPreOrder *CPreOrderFactory::findNextByAPIID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchByAPIID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindByAPIIDForPreOrder++;
#endif
	CPreOrder *thePreOrder;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchByAPIID=pAPIIDIndex->getNextNode(pLastFoundInSearchByAPIID);
	if (pLastFoundInSearchByAPIID==NULL)
	{
		return NULL;
	}

	thePreOrder=(CPreOrder *)(pLastFoundInSearchByAPIID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(thePreOrder->APIID,queryAPIIDInSearchByAPIID))
	{
		pLastFoundInSearchByAPIID=NULL;
		return NULL;
	}

	///返回找到的结果
	return thePreOrder;
}

void CPreOrderFactory::endFindByAPIID(void)
{
	pLastFoundInSearchByAPIID=NULL;
}


#ifdef COUNT_SEARCH
int findByALLFldsForIndexPreOrder=0;
#endif
CIndexPreOrder *CIndexPreOrderFactory::findByALLFlds( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyHedgeFlagType&  HedgeFlag)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByALLFlds of CIndexPreOrder while run level < 0");
	}
	CHashIndexNode *pNode;
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.InvestorID=InvestorID.getValue();
	compareObject.InstrumentID=InstrumentID.getValue();
	compareObject.HedgeFlag=HedgeFlag.getValue();
	
	compareObject.calHashALLFlds();
	for (pNode=pALLFldsHashIndex->searchFirstEqual(compareObject.HashALLFlds);
		pNode!=NULL;
		pNode=pALLFldsHashIndex->searchNextEqual(pNode))
	{
		if (((CIndexPreOrder *)(pNode->pObject))->HashALLFlds != compareObject.HashALLFlds)
		{
			continue;
		}
		if (compare(((CIndexPreOrder *)(pNode->pObject))->ExchangeID.getValue(),ExchangeID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CIndexPreOrder *)(pNode->pObject))->InvestorID.getValue(),InvestorID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CIndexPreOrder *)(pNode->pObject))->InstrumentID.getValue(),InstrumentID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CIndexPreOrder *)(pNode->pObject))->HedgeFlag.getValue(),HedgeFlag.getValue())!=0)
		{
			continue;
		}
		return (CIndexPreOrder *)(pNode->pObject);
	}
	return NULL;
}

CIndexPreOrder *CIndexPreOrderFactory::findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyHedgeFlagType&  HedgeFlag)
{
	return findByALLFlds(ExchangeID, InvestorID, InstrumentID, HedgeFlag);
}
	
CIndexPreOrder *CIndexPreOrderFactory::findByPK(CWriteableIndexPreOrder *pIndexPreOrder)
{
	return findByPK(
		pIndexPreOrder->ExchangeID
		,
		pIndexPreOrder->InvestorID
		,
		pIndexPreOrder->InstrumentID
		,
		pIndexPreOrder->HedgeFlag
		);
}

bool CIndexPreOrderFactory::retrieveByPK(CWriteableIndexPreOrder *pIndexPreOrder)
{
	CIndexPreOrder *pOriginalIndexPreOrder;
	pOriginalIndexPreOrder=findByPK(pIndexPreOrder);
	if (pOriginalIndexPreOrder==NULL)
	{
		return false;
	}
	retrieve(pOriginalIndexPreOrder,pIndexPreOrder);
	return true;
}

CIndexPreOrder *CIndexPreOrderFactory::addByPK(CWriteableIndexPreOrder *pIndexPreOrder, CTransaction *pTransaction)
{
	CIndexPreOrder *pOriginalIndexPreOrder;
	pOriginalIndexPreOrder=findByPK(pIndexPreOrder);
	if (pOriginalIndexPreOrder != NULL)
	{
		return NULL;
	}
	return add(pIndexPreOrder,pTransaction);
}

bool CIndexPreOrderFactory::updateByPK(CWriteableIndexPreOrder *pIndexPreOrder, CTransaction *pTransaction, bool updateIndex)
{
	CIndexPreOrder *pOriginalIndexPreOrder;
	pOriginalIndexPreOrder=findByPK(pIndexPreOrder);
	if (pOriginalIndexPreOrder==NULL)
	{
		return false;
	}
	pIndexPreOrder->calAllHash();
	update(pOriginalIndexPreOrder,pIndexPreOrder,pTransaction,updateIndex);
	return true;
}

bool CIndexPreOrderFactory::removeByPK(CWriteableIndexPreOrder *pIndexPreOrder, CTransaction *pTransaction)
{
	CIndexPreOrder *pOriginalIndexPreOrder;
	pOriginalIndexPreOrder=findByPK(pIndexPreOrder);
	if (pOriginalIndexPreOrder==NULL)
	{
		return false;
	}
	remove(pOriginalIndexPreOrder,pTransaction);
	return true;
}


int compareForBrkIDExIDInvIDInsIDDirHedIndexinInvestorPosition(const void *pV1, const void *pV2)
{
	CInvestorPosition *p1,*p2;
	p1=(CInvestorPosition *)pV1;
	p2=(CInvestorPosition *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InvestorID.getValue(),p2->InvestorID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InstrumentID.getValue(),p2->InstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->Direction.getValue(),p2->Direction.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->HedgeFlag.getValue(),p2->HedgeFlag.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForExIDAndInstrumentIDIndexinInvestorPosition(const void *pV1, const void *pV2)
{
	CInvestorPosition *p1,*p2;
	p1=(CInvestorPosition *)pV1;
	p2=(CInvestorPosition *)pV2;
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InstrumentID.getValue(),p2->InstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForInvestorIDIndexinInvestorPosition(const void *pV1, const void *pV2)
{
	CInvestorPosition *p1,*p2;
	p1=(CInvestorPosition *)pV1;
	p2=(CInvestorPosition *)pV2;
	switch (compare(p1->InvestorID.getValue(),p2->InvestorID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByBrkIDExIDInvIDInsDirHedForInvestorPosition=0;
#endif
CInvestorPosition *CInvestorPositionFactory::findByBrkIDExIDInvIDInsDirHed( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyDirectionType&  Direction,  const CReadOnlyHedgeFlagType&  HedgeFlag)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrkIDExIDInvIDInsDirHed of CInvestorPosition while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByBrkIDExIDInvIDInsDirHedForInvestorPosition++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.InvestorID=InvestorID.getValue();
	compareObject.InstrumentID=InstrumentID.getValue();
	compareObject.Direction=Direction.getValue();
	compareObject.HedgeFlag=HedgeFlag.getValue();
	pNode=pBrkIDExIDInvIDInsIDDirHedIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CInvestorPosition *)(pNode->pObject);
}

CInvestorPosition *CInvestorPositionFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyDirectionType&  Direction,  const CReadOnlyHedgeFlagType&  HedgeFlag)
{
	return findByBrkIDExIDInvIDInsDirHed(BrokerID, ExchangeID, InvestorID, InstrumentID, Direction, HedgeFlag);
}
	
CInvestorPosition *CInvestorPositionFactory::findByPK(CWriteableInvestorPosition *pInvestorPosition)
{
	return findByPK(
		pInvestorPosition->BrokerID
		,
		pInvestorPosition->ExchangeID
		,
		pInvestorPosition->InvestorID
		,
		pInvestorPosition->InstrumentID
		,
		pInvestorPosition->Direction
		,
		pInvestorPosition->HedgeFlag
		);
}

bool CInvestorPositionFactory::retrieveByPK(CWriteableInvestorPosition *pInvestorPosition)
{
	CInvestorPosition *pOriginalInvestorPosition;
	pOriginalInvestorPosition=findByPK(pInvestorPosition);
	if (pOriginalInvestorPosition==NULL)
	{
		return false;
	}
	retrieve(pOriginalInvestorPosition,pInvestorPosition);
	return true;
}

CInvestorPosition *CInvestorPositionFactory::addByPK(CWriteableInvestorPosition *pInvestorPosition, CTransaction *pTransaction)
{
	CInvestorPosition *pOriginalInvestorPosition;
	pOriginalInvestorPosition=findByPK(pInvestorPosition);
	if (pOriginalInvestorPosition != NULL)
	{
		return NULL;
	}
	return add(pInvestorPosition,pTransaction);
}

bool CInvestorPositionFactory::updateByPK(CWriteableInvestorPosition *pInvestorPosition, CTransaction *pTransaction, bool updateIndex)
{
	CInvestorPosition *pOriginalInvestorPosition;
	pOriginalInvestorPosition=findByPK(pInvestorPosition);
	if (pOriginalInvestorPosition==NULL)
	{
		return false;
	}
	pInvestorPosition->calAllHash();
	update(pOriginalInvestorPosition,pInvestorPosition,pTransaction,updateIndex);
	return true;
}

bool CInvestorPositionFactory::removeByPK(CWriteableInvestorPosition *pInvestorPosition, CTransaction *pTransaction)
{
	CInvestorPosition *pOriginalInvestorPosition;
	pOriginalInvestorPosition=findByPK(pInvestorPosition);
	if (pOriginalInvestorPosition==NULL)
	{
		return false;
	}
	remove(pOriginalInvestorPosition,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int multiFindAllByExIDAndInstrumentIDForInvestorPosition=0;
#endif

CInvestorPosition *CInvestorPositionFactory::startFindAllByExIDAndInstrumentID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& InstrumentID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByExIDAndInstrumentID of CInvestorPosition while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByExIDAndInstrumentID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByExIDAndInstrumentID();
	}

	///记录所有的查询值
	queryExchangeIDInSearchAllByExIDAndInstrumentID= ExchangeID.getValue();
	queryInstrumentIDInSearchAllByExIDAndInstrumentID= InstrumentID.getValue();

#ifdef COUNT_SEARCH
	multiFindAllByExIDAndInstrumentIDForInvestorPosition++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CInvestorPosition *theInvestorPosition;
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.InstrumentID=InstrumentID.getValue();
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchAllByExIDAndInstrumentID=pExIDAndInstrumentIDIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchAllByExIDAndInstrumentID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	theInvestorPosition=(CInvestorPosition *)(pLastFoundInSearchAllByExIDAndInstrumentID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theInvestorPosition->ExchangeID.getValue(),ExchangeID.getValue()))
	{
		pLastFoundInSearchAllByExIDAndInstrumentID=NULL;
		return NULL;
	}
	if (compare(theInvestorPosition->InstrumentID.getValue(),InstrumentID.getValue()))
	{
		pLastFoundInSearchAllByExIDAndInstrumentID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theInvestorPosition;
}

CInvestorPosition *CInvestorPositionFactory::findNextAllByExIDAndInstrumentID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByExIDAndInstrumentID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindAllByExIDAndInstrumentIDForInvestorPosition++;
#endif
	CInvestorPosition *theInvestorPosition;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchAllByExIDAndInstrumentID=pExIDAndInstrumentIDIndex->getNextNode(pLastFoundInSearchAllByExIDAndInstrumentID);
	if (pLastFoundInSearchAllByExIDAndInstrumentID==NULL)
	{
		return NULL;
	}

	theInvestorPosition=(CInvestorPosition *)(pLastFoundInSearchAllByExIDAndInstrumentID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theInvestorPosition->ExchangeID,queryExchangeIDInSearchAllByExIDAndInstrumentID))
	{
		pLastFoundInSearchAllByExIDAndInstrumentID=NULL;
		return NULL;
	}
	if (compare(theInvestorPosition->InstrumentID,queryInstrumentIDInSearchAllByExIDAndInstrumentID))
	{
		pLastFoundInSearchAllByExIDAndInstrumentID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theInvestorPosition;
}

void CInvestorPositionFactory::endFindAllByExIDAndInstrumentID(void)
{
	pLastFoundInSearchAllByExIDAndInstrumentID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindByInvestorIDForInvestorPosition=0;
#endif

CInvestorPosition *CInvestorPositionFactory::startFindByInvestorID( const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindByInvestorID of CInvestorPosition while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchByInvestorID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindByInvestorID();
	}

	///记录所有的查询值
	queryInvestorIDInSearchByInvestorID= InvestorID.getValue();

#ifdef COUNT_SEARCH
	multiFindByInvestorIDForInvestorPosition++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CInvestorPosition *theInvestorPosition;
	compareObject.InvestorID=InvestorID.getValue();
	compareObject.InvestorID="";
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchByInvestorID=pInvestorIDIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchByInvestorID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	theInvestorPosition=(CInvestorPosition *)(pLastFoundInSearchByInvestorID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theInvestorPosition->InvestorID.getValue(),InvestorID.getValue()))
	{
		pLastFoundInSearchByInvestorID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theInvestorPosition;
}

CInvestorPosition *CInvestorPositionFactory::findNextByInvestorID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchByInvestorID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindByInvestorIDForInvestorPosition++;
#endif
	CInvestorPosition *theInvestorPosition;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchByInvestorID=pInvestorIDIndex->getNextNode(pLastFoundInSearchByInvestorID);
	if (pLastFoundInSearchByInvestorID==NULL)
	{
		return NULL;
	}

	theInvestorPosition=(CInvestorPosition *)(pLastFoundInSearchByInvestorID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theInvestorPosition->InvestorID,queryInvestorIDInSearchByInvestorID))
	{
		pLastFoundInSearchByInvestorID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theInvestorPosition;
}

void CInvestorPositionFactory::endFindByInvestorID(void)
{
	pLastFoundInSearchByInvestorID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByBrokerIDForInvestorPosition=0;
#endif

CInvestorPosition *CInvestorPositionFactory::startFindAllByBrokerID( const CReadOnlyBrokerIDType& BrokerID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByBrokerID of CInvestorPosition while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByBrokerID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByBrokerID();
	}

	///记录所有的查询值
	queryBrokerIDInSearchAllByBrokerID= BrokerID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByBrokerID=(CInvestorPosition *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByBrokerID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByBrokerID来寻找下一个
	if (compare(pLastFoundInSearchAllByBrokerID->BrokerID.getValue(),BrokerID.getValue()))
	{
		return findNextAllByBrokerID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByBrokerID;
}

CInvestorPosition *CInvestorPositionFactory::findNextAllByBrokerID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByBrokerID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByBrokerID=(CInvestorPosition *)(pMem->getNext());
		if (pLastFoundInSearchAllByBrokerID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByBrokerID->BrokerID,queryBrokerIDInSearchAllByBrokerID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByBrokerID;
	}
}

void CInvestorPositionFactory::endFindAllByBrokerID(void)
{
	pLastFoundInSearchAllByBrokerID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByInstrumentIDForInvestorPosition=0;
#endif

CInvestorPosition *CInvestorPositionFactory::startFindAllByInstrumentID( const CReadOnlyInstrumentIDType& InstrumentID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByInstrumentID of CInvestorPosition while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByInstrumentID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByInstrumentID();
	}

	///记录所有的查询值
	queryInstrumentIDInSearchAllByInstrumentID= InstrumentID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByInstrumentID=(CInvestorPosition *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByInstrumentID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByInstrumentID来寻找下一个
	if (compare(pLastFoundInSearchAllByInstrumentID->InstrumentID.getValue(),InstrumentID.getValue()))
	{
		return findNextAllByInstrumentID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByInstrumentID;
}

CInvestorPosition *CInvestorPositionFactory::findNextAllByInstrumentID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByInstrumentID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByInstrumentID=(CInvestorPosition *)(pMem->getNext());
		if (pLastFoundInSearchAllByInstrumentID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByInstrumentID->InstrumentID,queryInstrumentIDInSearchAllByInstrumentID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByInstrumentID;
	}
}

void CInvestorPositionFactory::endFindAllByInstrumentID(void)
{
	pLastFoundInSearchAllByInstrumentID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByExchangeIDForInvestorPosition=0;
#endif

CInvestorPosition *CInvestorPositionFactory::startFindAllByExchangeID( const CReadOnlyExchangeIDType& ExchangeID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByExchangeID of CInvestorPosition while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByExchangeID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByExchangeID();
	}

	///记录所有的查询值
	queryExchangeIDInSearchAllByExchangeID= ExchangeID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByExchangeID=(CInvestorPosition *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByExchangeID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByExchangeID来寻找下一个
	if (compare(pLastFoundInSearchAllByExchangeID->ExchangeID.getValue(),ExchangeID.getValue()))
	{
		return findNextAllByExchangeID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByExchangeID;
}

CInvestorPosition *CInvestorPositionFactory::findNextAllByExchangeID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByExchangeID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByExchangeID=(CInvestorPosition *)(pMem->getNext());
		if (pLastFoundInSearchAllByExchangeID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByExchangeID->ExchangeID,queryExchangeIDInSearchAllByExchangeID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByExchangeID;
	}
}

void CInvestorPositionFactory::endFindAllByExchangeID(void)
{
	pLastFoundInSearchAllByExchangeID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByInvestorIDAndInstrumentIDForInvestorPosition=0;
#endif

CInvestorPosition *CInvestorPositionFactory::startFindAllByInvestorIDAndInstrumentID( const CReadOnlyInvestorIDType& InvestorID,  const CReadOnlyInstrumentIDType& InstrumentID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByInvestorIDAndInstrumentID of CInvestorPosition while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByInvestorIDAndInstrumentID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByInvestorIDAndInstrumentID();
	}

	///记录所有的查询值
	queryInvestorIDInSearchAllByInvestorIDAndInstrumentID= InvestorID.getValue();
	queryInstrumentIDInSearchAllByInvestorIDAndInstrumentID= InstrumentID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByInvestorIDAndInstrumentID=(CInvestorPosition *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByInvestorIDAndInstrumentID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByInvestorIDAndInstrumentID来寻找下一个
	if (compare(pLastFoundInSearchAllByInvestorIDAndInstrumentID->InvestorID.getValue(),InvestorID.getValue()))
	{
		return findNextAllByInvestorIDAndInstrumentID();
	}
	if (compare(pLastFoundInSearchAllByInvestorIDAndInstrumentID->InstrumentID.getValue(),InstrumentID.getValue()))
	{
		return findNextAllByInvestorIDAndInstrumentID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByInvestorIDAndInstrumentID;
}

CInvestorPosition *CInvestorPositionFactory::findNextAllByInvestorIDAndInstrumentID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByInvestorIDAndInstrumentID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByInvestorIDAndInstrumentID=(CInvestorPosition *)(pMem->getNext());
		if (pLastFoundInSearchAllByInvestorIDAndInstrumentID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByInvestorIDAndInstrumentID->InvestorID,queryInvestorIDInSearchAllByInvestorIDAndInstrumentID))
		{
			continue;
		}
		if (compare(pLastFoundInSearchAllByInvestorIDAndInstrumentID->InstrumentID,queryInstrumentIDInSearchAllByInvestorIDAndInstrumentID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByInvestorIDAndInstrumentID;
	}
}

void CInvestorPositionFactory::endFindAllByInvestorIDAndInstrumentID(void)
{
	pLastFoundInSearchAllByInvestorIDAndInstrumentID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllForInvestorPosition=0;
#endif

CInvestorPosition *CInvestorPositionFactory::startFindAll()
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAll of CInvestorPosition while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAll!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAll();
	}

	///记录所有的查询值

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAll=(CInvestorPosition *)(pMem->getFirst());
	
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAll来寻找下一个
	
	///返回找到的结果
	return pLastFoundInSearchAll;
}

CInvestorPosition *CInvestorPositionFactory::findNextAll(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAll=(CInvestorPosition *)(pMem->getNext());
		if (pLastFoundInSearchAll==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		///返回找到的结果
		return pLastFoundInSearchAll;
	}
}

void CInvestorPositionFactory::endFindAll(void)
{
	pLastFoundInSearchAll=NULL;
}

int compareForBrokerIDAccountIDIndexinInvestorAccount(const void *pV1, const void *pV2)
{
	CInvestorAccount *p1,*p2;
	p1=(CInvestorAccount *)pV1;
	p2=(CInvestorAccount *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->AccountID.getValue(),p2->AccountID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForBrokerIDInvestorIDIndexinInvestorAccount(const void *pV1, const void *pV2)
{
	CInvestorAccount *p1,*p2;
	p1=(CInvestorAccount *)pV1;
	p2=(CInvestorAccount *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InvestorID.getValue(),p2->InvestorID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByBrokerIDAccountIDForInvestorAccount=0;
#endif
CInvestorAccount *CInvestorAccountFactory::findByBrokerIDAccountID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyAccountIDType&  AccountID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrokerIDAccountID of CInvestorAccount while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByBrokerIDAccountIDForInvestorAccount++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.AccountID=AccountID.getValue();
	pNode=pBrokerIDAccountIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CInvestorAccount *)(pNode->pObject);
}

CInvestorAccount *CInvestorAccountFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyAccountIDType&  AccountID)
{
	return findByBrokerIDAccountID(BrokerID, AccountID);
}
	
CInvestorAccount *CInvestorAccountFactory::findByPK(CWriteableInvestorAccount *pInvestorAccount)
{
	return findByPK(
		pInvestorAccount->BrokerID
		,
		pInvestorAccount->AccountID
		);
}

bool CInvestorAccountFactory::retrieveByPK(CWriteableInvestorAccount *pInvestorAccount)
{
	CInvestorAccount *pOriginalInvestorAccount;
	pOriginalInvestorAccount=findByPK(pInvestorAccount);
	if (pOriginalInvestorAccount==NULL)
	{
		return false;
	}
	retrieve(pOriginalInvestorAccount,pInvestorAccount);
	return true;
}

CInvestorAccount *CInvestorAccountFactory::addByPK(CWriteableInvestorAccount *pInvestorAccount, CTransaction *pTransaction)
{
	CInvestorAccount *pOriginalInvestorAccount;
	pOriginalInvestorAccount=findByPK(pInvestorAccount);
	if (pOriginalInvestorAccount != NULL)
	{
		return NULL;
	}
	return add(pInvestorAccount,pTransaction);
}

bool CInvestorAccountFactory::updateByPK(CWriteableInvestorAccount *pInvestorAccount, CTransaction *pTransaction, bool updateIndex)
{
	CInvestorAccount *pOriginalInvestorAccount;
	pOriginalInvestorAccount=findByPK(pInvestorAccount);
	if (pOriginalInvestorAccount==NULL)
	{
		return false;
	}
	pInvestorAccount->calAllHash();
	update(pOriginalInvestorAccount,pInvestorAccount,pTransaction,updateIndex);
	return true;
}

bool CInvestorAccountFactory::removeByPK(CWriteableInvestorAccount *pInvestorAccount, CTransaction *pTransaction)
{
	CInvestorAccount *pOriginalInvestorAccount;
	pOriginalInvestorAccount=findByPK(pInvestorAccount);
	if (pOriginalInvestorAccount==NULL)
	{
		return false;
	}
	remove(pOriginalInvestorAccount,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int multiFindAllByInvestorIDForInvestorAccount=0;
#endif

CInvestorAccount *CInvestorAccountFactory::startFindAllByInvestorID( const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByInvestorID of CInvestorAccount while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByInvestorID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByInvestorID();
	}

	///记录所有的查询值
	queryInvestorIDInSearchAllByInvestorID= InvestorID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByInvestorID=(CInvestorAccount *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByInvestorID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByInvestorID来寻找下一个
	if (compare(pLastFoundInSearchAllByInvestorID->InvestorID.getValue(),InvestorID.getValue()))
	{
		return findNextAllByInvestorID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByInvestorID;
}

CInvestorAccount *CInvestorAccountFactory::findNextAllByInvestorID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByInvestorID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByInvestorID=(CInvestorAccount *)(pMem->getNext());
		if (pLastFoundInSearchAllByInvestorID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByInvestorID->InvestorID,queryInvestorIDInSearchAllByInvestorID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByInvestorID;
	}
}

void CInvestorAccountFactory::endFindAllByInvestorID(void)
{
	pLastFoundInSearchAllByInvestorID=NULL;
}


#ifdef COUNT_SEARCH
int findByBrokerIDInvestorIDForInvestorAccount=0;
#endif
CInvestorAccount *CInvestorAccountFactory::findByBrokerIDInvestorID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInvestorIDType&  InvestorID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrokerIDInvestorID of CInvestorAccount while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByBrokerIDInvestorIDForInvestorAccount++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.InvestorID=InvestorID.getValue();
	pNode=pBrokerIDInvestorIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CInvestorAccount *)(pNode->pObject);
}



#ifdef COUNT_SEARCH
int multiFindAllByBrokerIDForInvestorAccount=0;
#endif

CInvestorAccount *CInvestorAccountFactory::startFindAllByBrokerID( const CReadOnlyBrokerIDType& BrokerID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByBrokerID of CInvestorAccount while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByBrokerID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByBrokerID();
	}

	///记录所有的查询值
	queryBrokerIDInSearchAllByBrokerID= BrokerID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByBrokerID=(CInvestorAccount *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByBrokerID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByBrokerID来寻找下一个
	if (compare(pLastFoundInSearchAllByBrokerID->BrokerID.getValue(),BrokerID.getValue()))
	{
		return findNextAllByBrokerID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByBrokerID;
}

CInvestorAccount *CInvestorAccountFactory::findNextAllByBrokerID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByBrokerID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByBrokerID=(CInvestorAccount *)(pMem->getNext());
		if (pLastFoundInSearchAllByBrokerID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByBrokerID->BrokerID,queryBrokerIDInSearchAllByBrokerID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByBrokerID;
	}
}

void CInvestorAccountFactory::endFindAllByBrokerID(void)
{
	pLastFoundInSearchAllByBrokerID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllForInvestorAccount=0;
#endif

CInvestorAccount *CInvestorAccountFactory::startFindAll()
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAll of CInvestorAccount while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAll!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAll();
	}

	///记录所有的查询值

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAll=(CInvestorAccount *)(pMem->getFirst());
	
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAll来寻找下一个
	
	///返回找到的结果
	return pLastFoundInSearchAll;
}

CInvestorAccount *CInvestorAccountFactory::findNextAll(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAll=(CInvestorAccount *)(pMem->getNext());
		if (pLastFoundInSearchAll==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		///返回找到的结果
		return pLastFoundInSearchAll;
	}
}

void CInvestorAccountFactory::endFindAll(void)
{
	pLastFoundInSearchAll=NULL;
}

int compareForBrokerIDAccountSeqNoIndexinInvestorAccountDeposit(const void *pV1, const void *pV2)
{
	CInvestorAccountDeposit *p1,*p2;
	p1=(CInvestorAccountDeposit *)pV1;
	p2=(CInvestorAccountDeposit *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->AccountSeqNo.getValue(),p2->AccountSeqNo.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByBrokerIDAccountSeqNoForInvestorAccountDeposit=0;
#endif
CInvestorAccountDeposit *CInvestorAccountDepositFactory::findByBrokerIDAccountSeqNo( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyAccountSeqNoType&  AccountSeqNo)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrokerIDAccountSeqNo of CInvestorAccountDeposit while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByBrokerIDAccountSeqNoForInvestorAccountDeposit++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.AccountSeqNo=AccountSeqNo.getValue();
	pNode=pBrokerIDAccountSeqNoIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CInvestorAccountDeposit *)(pNode->pObject);
}

CInvestorAccountDeposit *CInvestorAccountDepositFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyAccountSeqNoType&  AccountSeqNo)
{
	return findByBrokerIDAccountSeqNo(BrokerID, AccountSeqNo);
}
	
CInvestorAccountDeposit *CInvestorAccountDepositFactory::findByPK(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit)
{
	return findByPK(
		pInvestorAccountDeposit->BrokerID
		,
		pInvestorAccountDeposit->AccountSeqNo
		);
}

bool CInvestorAccountDepositFactory::retrieveByPK(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit)
{
	CInvestorAccountDeposit *pOriginalInvestorAccountDeposit;
	pOriginalInvestorAccountDeposit=findByPK(pInvestorAccountDeposit);
	if (pOriginalInvestorAccountDeposit==NULL)
	{
		return false;
	}
	retrieve(pOriginalInvestorAccountDeposit,pInvestorAccountDeposit);
	return true;
}

CInvestorAccountDeposit *CInvestorAccountDepositFactory::addByPK(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit, CTransaction *pTransaction)
{
	CInvestorAccountDeposit *pOriginalInvestorAccountDeposit;
	pOriginalInvestorAccountDeposit=findByPK(pInvestorAccountDeposit);
	if (pOriginalInvestorAccountDeposit != NULL)
	{
		return NULL;
	}
	return add(pInvestorAccountDeposit,pTransaction);
}

bool CInvestorAccountDepositFactory::updateByPK(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit, CTransaction *pTransaction, bool updateIndex)
{
	CInvestorAccountDeposit *pOriginalInvestorAccountDeposit;
	pOriginalInvestorAccountDeposit=findByPK(pInvestorAccountDeposit);
	if (pOriginalInvestorAccountDeposit==NULL)
	{
		return false;
	}
	pInvestorAccountDeposit->calAllHash();
	update(pOriginalInvestorAccountDeposit,pInvestorAccountDeposit,pTransaction,updateIndex);
	return true;
}

bool CInvestorAccountDepositFactory::removeByPK(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit, CTransaction *pTransaction)
{
	CInvestorAccountDeposit *pOriginalInvestorAccountDeposit;
	pOriginalInvestorAccountDeposit=findByPK(pInvestorAccountDeposit);
	if (pOriginalInvestorAccountDeposit==NULL)
	{
		return false;
	}
	remove(pOriginalInvestorAccountDeposit,pTransaction);
	return true;
}


int compareForExchangeIDIndexinExchange(const void *pV1, const void *pV2)
{
	CExchange *p1,*p2;
	p1=(CExchange *)pV1;
	p2=(CExchange *)pV2;
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByExchangeIDForExchange=0;
#endif
CExchange *CExchangeFactory::findByExchangeID( const CReadOnlyExchangeIDType&  ExchangeID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByExchangeID of CExchange while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByExchangeIDForExchange++;
#endif
	CAVLNode *pNode;
	compareObject.ExchangeID=ExchangeID.getValue();
	pNode=pExchangeIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CExchange *)(pNode->pObject);
}

CExchange *CExchangeFactory::findByPK( const CReadOnlyExchangeIDType&  ExchangeID)
{
	return findByExchangeID(ExchangeID);
}
	
CExchange *CExchangeFactory::findByPK(CWriteableExchange *pExchange)
{
	return findByPK(
		pExchange->ExchangeID
		);
}

bool CExchangeFactory::retrieveByPK(CWriteableExchange *pExchange)
{
	CExchange *pOriginalExchange;
	pOriginalExchange=findByPK(pExchange);
	if (pOriginalExchange==NULL)
	{
		return false;
	}
	retrieve(pOriginalExchange,pExchange);
	return true;
}

CExchange *CExchangeFactory::addByPK(CWriteableExchange *pExchange, CTransaction *pTransaction)
{
	CExchange *pOriginalExchange;
	pOriginalExchange=findByPK(pExchange);
	if (pOriginalExchange != NULL)
	{
		return NULL;
	}
	return add(pExchange,pTransaction);
}

bool CExchangeFactory::updateByPK(CWriteableExchange *pExchange, CTransaction *pTransaction, bool updateIndex)
{
	CExchange *pOriginalExchange;
	pOriginalExchange=findByPK(pExchange);
	if (pOriginalExchange==NULL)
	{
		return false;
	}
	pExchange->calAllHash();
	update(pOriginalExchange,pExchange,pTransaction,updateIndex);
	return true;
}

bool CExchangeFactory::removeByPK(CWriteableExchange *pExchange, CTransaction *pTransaction)
{
	CExchange *pOriginalExchange;
	pOriginalExchange=findByPK(pExchange);
	if (pOriginalExchange==NULL)
	{
		return false;
	}
	remove(pOriginalExchange,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int multiFindStartByExchangeIDForExchange=0;
#endif

CExchange *CExchangeFactory::startFindStartByExchangeID( const CReadOnlyExchangeIDType& ExchangeID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindStartByExchangeID of CExchange while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchStartByExchangeID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindStartByExchangeID();
	}

	///记录所有的查询值
	queryExchangeIDInSearchStartByExchangeID= ExchangeID.getValue();

#ifdef COUNT_SEARCH
	multiFindStartByExchangeIDForExchange++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CExchange *theExchange;
	compareObject.ExchangeID=ExchangeID.getValue();
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchStartByExchangeID=pExchangeIDIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchStartByExchangeID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	theExchange=(CExchange *)(pLastFoundInSearchStartByExchangeID->pObject);
	
	///如果有一个条件不满足，则失败返回

	///返回找到的结果
	return theExchange;
}

CExchange *CExchangeFactory::findNextStartByExchangeID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchStartByExchangeID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindStartByExchangeIDForExchange++;
#endif
	CExchange *theExchange;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchStartByExchangeID=pExchangeIDIndex->getNextNode(pLastFoundInSearchStartByExchangeID);
	if (pLastFoundInSearchStartByExchangeID==NULL)
	{
		return NULL;
	}

	theExchange=(CExchange *)(pLastFoundInSearchStartByExchangeID->pObject);
	
	///如果有一个条件不满足，则失败返回

	///返回找到的结果
	return theExchange;
}

void CExchangeFactory::endFindStartByExchangeID(void)
{
	pLastFoundInSearchStartByExchangeID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllForExchange=0;
#endif

CExchange *CExchangeFactory::startFindAll()
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAll of CExchange while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAll!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAll();
	}

	///记录所有的查询值

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAll=(CExchange *)(pMem->getFirst());
	
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAll来寻找下一个
	
	///返回找到的结果
	return pLastFoundInSearchAll;
}

CExchange *CExchangeFactory::findNextAll(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAll=(CExchange *)(pMem->getNext());
		if (pLastFoundInSearchAll==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		///返回找到的结果
		return pLastFoundInSearchAll;
	}
}

void CExchangeFactory::endFindAll(void)
{
	pLastFoundInSearchAll=NULL;
}

int compareForBrokerIDExchangeIDSeatIDIndexinSeat(const void *pV1, const void *pV2)
{
	CSeat *p1,*p2;
	p1=(CSeat *)pV1;
	p2=(CSeat *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->SeatID.getValue(),p2->SeatID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForExchangeIDParticipantIDSeatIDIndexinSeat(const void *pV1, const void *pV2)
{
	CSeat *p1,*p2;
	p1=(CSeat *)pV1;
	p2=(CSeat *)pV2;
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->ParticipantID.getValue(),p2->ParticipantID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->SeatID.getValue(),p2->SeatID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByBrokerIDExchangeIDSeatIDForSeat=0;
#endif
CSeat *CSeatFactory::findByBrokerIDExchangeIDSeatID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlySeatIDType&  SeatID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrokerIDExchangeIDSeatID of CSeat while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByBrokerIDExchangeIDSeatIDForSeat++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.SeatID=SeatID.getValue();
	pNode=pBrokerIDExchangeIDSeatIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CSeat *)(pNode->pObject);
}

CSeat *CSeatFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlySeatIDType&  SeatID)
{
	return findByBrokerIDExchangeIDSeatID(BrokerID, ExchangeID, SeatID);
}
	
CSeat *CSeatFactory::findByPK(CWriteableSeat *pSeat)
{
	return findByPK(
		pSeat->BrokerID
		,
		pSeat->ExchangeID
		,
		pSeat->SeatID
		);
}

bool CSeatFactory::retrieveByPK(CWriteableSeat *pSeat)
{
	CSeat *pOriginalSeat;
	pOriginalSeat=findByPK(pSeat);
	if (pOriginalSeat==NULL)
	{
		return false;
	}
	retrieve(pOriginalSeat,pSeat);
	return true;
}

CSeat *CSeatFactory::addByPK(CWriteableSeat *pSeat, CTransaction *pTransaction)
{
	CSeat *pOriginalSeat;
	pOriginalSeat=findByPK(pSeat);
	if (pOriginalSeat != NULL)
	{
		return NULL;
	}
	return add(pSeat,pTransaction);
}

bool CSeatFactory::updateByPK(CWriteableSeat *pSeat, CTransaction *pTransaction, bool updateIndex)
{
	CSeat *pOriginalSeat;
	pOriginalSeat=findByPK(pSeat);
	if (pOriginalSeat==NULL)
	{
		return false;
	}
	pSeat->calAllHash();
	update(pOriginalSeat,pSeat,pTransaction,updateIndex);
	return true;
}

bool CSeatFactory::removeByPK(CWriteableSeat *pSeat, CTransaction *pTransaction)
{
	CSeat *pOriginalSeat;
	pOriginalSeat=findByPK(pSeat);
	if (pOriginalSeat==NULL)
	{
		return false;
	}
	remove(pOriginalSeat,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int findByExchangeIDParticipantIDSeatIDForSeat=0;
#endif
CSeat *CSeatFactory::findByExchangeIDParticipantIDSeatID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyParticipantIDType&  ParticipantID,  const CReadOnlySeatIDType&  SeatID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByExchangeIDParticipantIDSeatID of CSeat while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByExchangeIDParticipantIDSeatIDForSeat++;
#endif
	CAVLNode *pNode;
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.ParticipantID=ParticipantID.getValue();
	compareObject.SeatID=SeatID.getValue();
	pNode=pExchangeIDParticipantIDSeatIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CSeat *)(pNode->pObject);
}


int compareForExchangeIDInstrumentIDIndexinInstrument(const void *pV1, const void *pV2)
{
	CInstrument *p1,*p2;
	p1=(CInstrument *)pV1;
	p2=(CInstrument *)pV2;
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InstrumentID.getValue(),p2->InstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForInstrumentIDIndexinInstrument(const void *pV1, const void *pV2)
{
	CInstrument *p1,*p2;
	p1=(CInstrument *)pV1;
	p2=(CInstrument *)pV2;
	switch (compare(p1->InstrumentID.getValue(),p2->InstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByExchangeIDAndInstrumentIDForInstrument=0;
#endif
CInstrument *CInstrumentFactory::findByExchangeIDAndInstrumentID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByExchangeIDAndInstrumentID of CInstrument while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByExchangeIDAndInstrumentIDForInstrument++;
#endif
	CAVLNode *pNode;
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.InstrumentID=InstrumentID.getValue();
	pNode=pExchangeIDInstrumentIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CInstrument *)(pNode->pObject);
}

CInstrument *CInstrumentFactory::findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID)
{
	return findByExchangeIDAndInstrumentID(ExchangeID, InstrumentID);
}
	
CInstrument *CInstrumentFactory::findByPK(CWriteableInstrument *pInstrument)
{
	return findByPK(
		pInstrument->ExchangeID
		,
		pInstrument->InstrumentID
		);
}

bool CInstrumentFactory::retrieveByPK(CWriteableInstrument *pInstrument)
{
	CInstrument *pOriginalInstrument;
	pOriginalInstrument=findByPK(pInstrument);
	if (pOriginalInstrument==NULL)
	{
		return false;
	}
	retrieve(pOriginalInstrument,pInstrument);
	return true;
}

CInstrument *CInstrumentFactory::addByPK(CWriteableInstrument *pInstrument, CTransaction *pTransaction)
{
	CInstrument *pOriginalInstrument;
	pOriginalInstrument=findByPK(pInstrument);
	if (pOriginalInstrument != NULL)
	{
		return NULL;
	}
	return add(pInstrument,pTransaction);
}

bool CInstrumentFactory::updateByPK(CWriteableInstrument *pInstrument, CTransaction *pTransaction, bool updateIndex)
{
	CInstrument *pOriginalInstrument;
	pOriginalInstrument=findByPK(pInstrument);
	if (pOriginalInstrument==NULL)
	{
		return false;
	}
	pInstrument->calAllHash();
	update(pOriginalInstrument,pInstrument,pTransaction,updateIndex);
	return true;
}

bool CInstrumentFactory::removeByPK(CWriteableInstrument *pInstrument, CTransaction *pTransaction)
{
	CInstrument *pOriginalInstrument;
	pOriginalInstrument=findByPK(pInstrument);
	if (pOriginalInstrument==NULL)
	{
		return false;
	}
	remove(pOriginalInstrument,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int multiFindAllByInstrumentIDForInstrument=0;
#endif

CInstrument *CInstrumentFactory::startFindAllByInstrumentID( const CReadOnlyInstrumentIDType& InstrumentID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByInstrumentID of CInstrument while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByInstrumentID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByInstrumentID();
	}

	///记录所有的查询值
	queryInstrumentIDInSearchAllByInstrumentID= InstrumentID.getValue();

#ifdef COUNT_SEARCH
	multiFindAllByInstrumentIDForInstrument++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CInstrument *theInstrument;
	compareObject.InstrumentID=InstrumentID.getValue();
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchAllByInstrumentID=pInstrumentIDIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchAllByInstrumentID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	theInstrument=(CInstrument *)(pLastFoundInSearchAllByInstrumentID->pObject);
	
	///如果有一个条件不满足，则失败返回

	///返回找到的结果
	return theInstrument;
}

CInstrument *CInstrumentFactory::findNextAllByInstrumentID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByInstrumentID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindAllByInstrumentIDForInstrument++;
#endif
	CInstrument *theInstrument;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchAllByInstrumentID=pInstrumentIDIndex->getNextNode(pLastFoundInSearchAllByInstrumentID);
	if (pLastFoundInSearchAllByInstrumentID==NULL)
	{
		return NULL;
	}

	theInstrument=(CInstrument *)(pLastFoundInSearchAllByInstrumentID->pObject);
	
	///如果有一个条件不满足，则失败返回

	///返回找到的结果
	return theInstrument;
}

void CInstrumentFactory::endFindAllByInstrumentID(void)
{
	pLastFoundInSearchAllByInstrumentID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByExchangeIDForInstrument=0;
#endif

CInstrument *CInstrumentFactory::startFindAllByExchangeID( const CReadOnlyExchangeIDType& ExchangeID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByExchangeID of CInstrument while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByExchangeID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByExchangeID();
	}

	///记录所有的查询值
	queryExchangeIDInSearchAllByExchangeID= ExchangeID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByExchangeID=(CInstrument *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByExchangeID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByExchangeID来寻找下一个
	if (compare(pLastFoundInSearchAllByExchangeID->ExchangeID.getValue(),ExchangeID.getValue()))
	{
		return findNextAllByExchangeID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByExchangeID;
}

CInstrument *CInstrumentFactory::findNextAllByExchangeID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByExchangeID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByExchangeID=(CInstrument *)(pMem->getNext());
		if (pLastFoundInSearchAllByExchangeID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByExchangeID->ExchangeID,queryExchangeIDInSearchAllByExchangeID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByExchangeID;
	}
}

void CInstrumentFactory::endFindAllByExchangeID(void)
{
	pLastFoundInSearchAllByExchangeID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByProductIDForInstrument=0;
#endif

CInstrument *CInstrumentFactory::startFindAllByProductID( const CReadOnlyProductIDType& ProductID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByProductID of CInstrument while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByProductID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByProductID();
	}

	///记录所有的查询值
	queryProductIDInSearchAllByProductID= ProductID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByProductID=(CInstrument *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByProductID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByProductID来寻找下一个
	if (compare(pLastFoundInSearchAllByProductID->ProductID.getValue(),ProductID.getValue()))
	{
		return findNextAllByProductID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByProductID;
}

CInstrument *CInstrumentFactory::findNextAllByProductID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByProductID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByProductID=(CInstrument *)(pMem->getNext());
		if (pLastFoundInSearchAllByProductID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByProductID->ProductID,queryProductIDInSearchAllByProductID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByProductID;
	}
}

void CInstrumentFactory::endFindAllByProductID(void)
{
	pLastFoundInSearchAllByProductID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllForInstrument=0;
#endif

CInstrument *CInstrumentFactory::startFindAll()
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAll of CInstrument while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAll!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAll();
	}

	///记录所有的查询值

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAll=(CInstrument *)(pMem->getFirst());
	
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAll来寻找下一个
	
	///返回找到的结果
	return pLastFoundInSearchAll;
}

CInstrument *CInstrumentFactory::findNextAll(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAll=(CInstrument *)(pMem->getNext());
		if (pLastFoundInSearchAll==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		///返回找到的结果
		return pLastFoundInSearchAll;
	}
}

void CInstrumentFactory::endFindAll(void)
{
	pLastFoundInSearchAll=NULL;
}

int compareForExchangeIDArbiInstrumentIDSingelInstrumentIDIndexinCmbInstrumentDetail(const void *pV1, const void *pV2)
{
	CCmbInstrumentDetail *p1,*p2;
	p1=(CCmbInstrumentDetail *)pV1;
	p2=(CCmbInstrumentDetail *)pV2;
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->ArbiInstrumentID.getValue(),p2->ArbiInstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->SingleInstrumentID.getValue(),p2->SingleInstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForExchangeIDArbiInstrumentIDIndexinCmbInstrumentDetail(const void *pV1, const void *pV2)
{
	CCmbInstrumentDetail *p1,*p2;
	p1=(CCmbInstrumentDetail *)pV1;
	p2=(CCmbInstrumentDetail *)pV2;
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->ArbiInstrumentID.getValue(),p2->ArbiInstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForExchangeIDSingleInstrumentIDIndexinCmbInstrumentDetail(const void *pV1, const void *pV2)
{
	CCmbInstrumentDetail *p1,*p2;
	p1=(CCmbInstrumentDetail *)pV1;
	p2=(CCmbInstrumentDetail *)pV2;
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->SingleInstrumentID.getValue(),p2->SingleInstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByExchangeIDAndArbiInstrumentIDAndSingelInstrumentIDForCmbInstrumentDetail=0;
#endif
CCmbInstrumentDetail *CCmbInstrumentDetailFactory::findByExchangeIDAndArbiInstrumentIDAndSingelInstrumentID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  ArbiInstrumentID,  const CReadOnlyInstrumentIDType&  SingleInstrumentID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByExchangeIDAndArbiInstrumentIDAndSingelInstrumentID of CCmbInstrumentDetail while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByExchangeIDAndArbiInstrumentIDAndSingelInstrumentIDForCmbInstrumentDetail++;
#endif
	CAVLNode *pNode;
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.ArbiInstrumentID=ArbiInstrumentID.getValue();
	compareObject.SingleInstrumentID=SingleInstrumentID.getValue();
	pNode=pExchangeIDArbiInstrumentIDSingelInstrumentIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CCmbInstrumentDetail *)(pNode->pObject);
}

CCmbInstrumentDetail *CCmbInstrumentDetailFactory::findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  ArbiInstrumentID,  const CReadOnlyInstrumentIDType&  SingleInstrumentID)
{
	return findByExchangeIDAndArbiInstrumentIDAndSingelInstrumentID(ExchangeID, ArbiInstrumentID, SingleInstrumentID);
}
	
CCmbInstrumentDetail *CCmbInstrumentDetailFactory::findByPK(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail)
{
	return findByPK(
		pCmbInstrumentDetail->ExchangeID
		,
		pCmbInstrumentDetail->ArbiInstrumentID
		,
		pCmbInstrumentDetail->SingleInstrumentID
		);
}

bool CCmbInstrumentDetailFactory::retrieveByPK(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail)
{
	CCmbInstrumentDetail *pOriginalCmbInstrumentDetail;
	pOriginalCmbInstrumentDetail=findByPK(pCmbInstrumentDetail);
	if (pOriginalCmbInstrumentDetail==NULL)
	{
		return false;
	}
	retrieve(pOriginalCmbInstrumentDetail,pCmbInstrumentDetail);
	return true;
}

CCmbInstrumentDetail *CCmbInstrumentDetailFactory::addByPK(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail, CTransaction *pTransaction)
{
	CCmbInstrumentDetail *pOriginalCmbInstrumentDetail;
	pOriginalCmbInstrumentDetail=findByPK(pCmbInstrumentDetail);
	if (pOriginalCmbInstrumentDetail != NULL)
	{
		return NULL;
	}
	return add(pCmbInstrumentDetail,pTransaction);
}

bool CCmbInstrumentDetailFactory::updateByPK(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail, CTransaction *pTransaction, bool updateIndex)
{
	CCmbInstrumentDetail *pOriginalCmbInstrumentDetail;
	pOriginalCmbInstrumentDetail=findByPK(pCmbInstrumentDetail);
	if (pOriginalCmbInstrumentDetail==NULL)
	{
		return false;
	}
	pCmbInstrumentDetail->calAllHash();
	update(pOriginalCmbInstrumentDetail,pCmbInstrumentDetail,pTransaction,updateIndex);
	return true;
}

bool CCmbInstrumentDetailFactory::removeByPK(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail, CTransaction *pTransaction)
{
	CCmbInstrumentDetail *pOriginalCmbInstrumentDetail;
	pOriginalCmbInstrumentDetail=findByPK(pCmbInstrumentDetail);
	if (pOriginalCmbInstrumentDetail==NULL)
	{
		return false;
	}
	remove(pOriginalCmbInstrumentDetail,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int multiFindAllByExchangeIDAndArbiInstrumentIDForCmbInstrumentDetail=0;
#endif

CCmbInstrumentDetail *CCmbInstrumentDetailFactory::startFindAllByExchangeIDAndArbiInstrumentID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& ArbiInstrumentID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByExchangeIDAndArbiInstrumentID of CCmbInstrumentDetail while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByExchangeIDAndArbiInstrumentID();
	}

	///记录所有的查询值
	queryExchangeIDInSearchAllByExchangeIDAndArbiInstrumentID= ExchangeID.getValue();
	queryArbiInstrumentIDInSearchAllByExchangeIDAndArbiInstrumentID= ArbiInstrumentID.getValue();

#ifdef COUNT_SEARCH
	multiFindAllByExchangeIDAndArbiInstrumentIDForCmbInstrumentDetail++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CCmbInstrumentDetail *theCmbInstrumentDetail;
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.ArbiInstrumentID=ArbiInstrumentID.getValue();
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID=pExchangeIDArbiInstrumentIDIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	theCmbInstrumentDetail=(CCmbInstrumentDetail *)(pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theCmbInstrumentDetail->ExchangeID.getValue(),ExchangeID.getValue()))
	{
		pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID=NULL;
		return NULL;
	}
	if (compare(theCmbInstrumentDetail->ArbiInstrumentID.getValue(),ArbiInstrumentID.getValue()))
	{
		pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theCmbInstrumentDetail;
}

CCmbInstrumentDetail *CCmbInstrumentDetailFactory::findNextAllByExchangeIDAndArbiInstrumentID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindAllByExchangeIDAndArbiInstrumentIDForCmbInstrumentDetail++;
#endif
	CCmbInstrumentDetail *theCmbInstrumentDetail;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID=pExchangeIDArbiInstrumentIDIndex->getNextNode(pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID);
	if (pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID==NULL)
	{
		return NULL;
	}

	theCmbInstrumentDetail=(CCmbInstrumentDetail *)(pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theCmbInstrumentDetail->ExchangeID,queryExchangeIDInSearchAllByExchangeIDAndArbiInstrumentID))
	{
		pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID=NULL;
		return NULL;
	}
	if (compare(theCmbInstrumentDetail->ArbiInstrumentID,queryArbiInstrumentIDInSearchAllByExchangeIDAndArbiInstrumentID))
	{
		pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theCmbInstrumentDetail;
}

void CCmbInstrumentDetailFactory::endFindAllByExchangeIDAndArbiInstrumentID(void)
{
	pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByExchangeIDAndSingleInstrumentIDForCmbInstrumentDetail=0;
#endif

CCmbInstrumentDetail *CCmbInstrumentDetailFactory::startFindAllByExchangeIDAndSingleInstrumentID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& SingleInstrumentID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByExchangeIDAndSingleInstrumentID of CCmbInstrumentDetail while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByExchangeIDAndSingleInstrumentID();
	}

	///记录所有的查询值
	queryExchangeIDInSearchAllByExchangeIDAndSingleInstrumentID= ExchangeID.getValue();
	querySingleInstrumentIDInSearchAllByExchangeIDAndSingleInstrumentID= SingleInstrumentID.getValue();

#ifdef COUNT_SEARCH
	multiFindAllByExchangeIDAndSingleInstrumentIDForCmbInstrumentDetail++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CCmbInstrumentDetail *theCmbInstrumentDetail;
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.SingleInstrumentID=SingleInstrumentID.getValue();
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID=pExchangeIDSingleInstrumentIDIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	theCmbInstrumentDetail=(CCmbInstrumentDetail *)(pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theCmbInstrumentDetail->ExchangeID.getValue(),ExchangeID.getValue()))
	{
		pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID=NULL;
		return NULL;
	}
	if (compare(theCmbInstrumentDetail->SingleInstrumentID.getValue(),SingleInstrumentID.getValue()))
	{
		pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theCmbInstrumentDetail;
}

CCmbInstrumentDetail *CCmbInstrumentDetailFactory::findNextAllByExchangeIDAndSingleInstrumentID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindAllByExchangeIDAndSingleInstrumentIDForCmbInstrumentDetail++;
#endif
	CCmbInstrumentDetail *theCmbInstrumentDetail;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID=pExchangeIDSingleInstrumentIDIndex->getNextNode(pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID);
	if (pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID==NULL)
	{
		return NULL;
	}

	theCmbInstrumentDetail=(CCmbInstrumentDetail *)(pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theCmbInstrumentDetail->ExchangeID,queryExchangeIDInSearchAllByExchangeIDAndSingleInstrumentID))
	{
		pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID=NULL;
		return NULL;
	}
	if (compare(theCmbInstrumentDetail->SingleInstrumentID,querySingleInstrumentIDInSearchAllByExchangeIDAndSingleInstrumentID))
	{
		pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theCmbInstrumentDetail;
}

void CCmbInstrumentDetailFactory::endFindAllByExchangeIDAndSingleInstrumentID(void)
{
	pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID=NULL;
}

int compareForBrkIDExIDInvIDHdgFlgIndexinClientTradingID(const void *pV1, const void *pV2)
{
	CClientTradingID *p1,*p2;
	p1=(CClientTradingID *)pV1;
	p2=(CClientTradingID *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InvestorID.getValue(),p2->InvestorID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->ClientHedgeFlag.getValue(),p2->ClientHedgeFlag.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForBrokerIDInvestorIDIndexinClientTradingID(const void *pV1, const void *pV2)
{
	CClientTradingID *p1,*p2;
	p1=(CClientTradingID *)pV1;
	p2=(CClientTradingID *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InvestorID.getValue(),p2->InvestorID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByBrokerIDExchangeIDPartClientIDForClientTradingID=0;
#endif
CClientTradingID *CClientTradingIDFactory::findByBrokerIDExchangeIDPartClientID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyParticipantIDType&  ParticipantID,  const CReadOnlyClientIDType&  ClientID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrokerIDExchangeIDPartClientID of CClientTradingID while run level < 0");
	}
	CHashIndexNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.ParticipantID=ParticipantID.getValue();
	compareObject.ClientID=ClientID.getValue();
	
	compareObject.calHashBrokerIDExchangeIDPartClientID();
	for (pNode=pBrokerIDExchangeIDPartClientIDHashIndex->searchFirstEqual(compareObject.HashBrokerIDExchangeIDPartClientID);
		pNode!=NULL;
		pNode=pBrokerIDExchangeIDPartClientIDHashIndex->searchNextEqual(pNode))
	{
		if (((CClientTradingID *)(pNode->pObject))->HashBrokerIDExchangeIDPartClientID != compareObject.HashBrokerIDExchangeIDPartClientID)
		{
			continue;
		}
		if (compare(((CClientTradingID *)(pNode->pObject))->BrokerID.getValue(),BrokerID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CClientTradingID *)(pNode->pObject))->ExchangeID.getValue(),ExchangeID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CClientTradingID *)(pNode->pObject))->ParticipantID.getValue(),ParticipantID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CClientTradingID *)(pNode->pObject))->ClientID.getValue(),ClientID.getValue())!=0)
		{
			continue;
		}
		return (CClientTradingID *)(pNode->pObject);
	}
	return NULL;
}

CClientTradingID *CClientTradingIDFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyParticipantIDType&  ParticipantID,  const CReadOnlyClientIDType&  ClientID)
{
	return findByBrokerIDExchangeIDPartClientID(BrokerID, ExchangeID, ParticipantID, ClientID);
}
	
CClientTradingID *CClientTradingIDFactory::findByPK(CWriteableClientTradingID *pClientTradingID)
{
	return findByPK(
		pClientTradingID->BrokerID
		,
		pClientTradingID->ExchangeID
		,
		pClientTradingID->ParticipantID
		,
		pClientTradingID->ClientID
		);
}

bool CClientTradingIDFactory::retrieveByPK(CWriteableClientTradingID *pClientTradingID)
{
	CClientTradingID *pOriginalClientTradingID;
	pOriginalClientTradingID=findByPK(pClientTradingID);
	if (pOriginalClientTradingID==NULL)
	{
		return false;
	}
	retrieve(pOriginalClientTradingID,pClientTradingID);
	return true;
}

CClientTradingID *CClientTradingIDFactory::addByPK(CWriteableClientTradingID *pClientTradingID, CTransaction *pTransaction)
{
	CClientTradingID *pOriginalClientTradingID;
	pOriginalClientTradingID=findByPK(pClientTradingID);
	if (pOriginalClientTradingID != NULL)
	{
		return NULL;
	}
	return add(pClientTradingID,pTransaction);
}

bool CClientTradingIDFactory::updateByPK(CWriteableClientTradingID *pClientTradingID, CTransaction *pTransaction, bool updateIndex)
{
	CClientTradingID *pOriginalClientTradingID;
	pOriginalClientTradingID=findByPK(pClientTradingID);
	if (pOriginalClientTradingID==NULL)
	{
		return false;
	}
	pClientTradingID->calAllHash();
	update(pOriginalClientTradingID,pClientTradingID,pTransaction,updateIndex);
	return true;
}

bool CClientTradingIDFactory::removeByPK(CWriteableClientTradingID *pClientTradingID, CTransaction *pTransaction)
{
	CClientTradingID *pOriginalClientTradingID;
	pOriginalClientTradingID=findByPK(pClientTradingID);
	if (pOriginalClientTradingID==NULL)
	{
		return false;
	}
	remove(pOriginalClientTradingID,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int findByBrkIDExIDInvIDHdgFlgForClientTradingID=0;
#endif
CClientTradingID *CClientTradingIDFactory::findByBrkIDExIDInvIDHdgFlg( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  ClientHedgeFlag)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrkIDExIDInvIDHdgFlg of CClientTradingID while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByBrkIDExIDInvIDHdgFlgForClientTradingID++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.InvestorID=InvestorID.getValue();
	compareObject.ClientHedgeFlag=ClientHedgeFlag.getValue();
	pNode=pBrkIDExIDInvIDHdgFlgIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CClientTradingID *)(pNode->pObject);
}



#ifdef COUNT_SEARCH
int multiFindByBrokerIDInvestorIDForClientTradingID=0;
#endif

CClientTradingID *CClientTradingIDFactory::startFindByBrokerIDInvestorID( const CReadOnlyBrokerIDType& BrokerID,  const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindByBrokerIDInvestorID of CClientTradingID while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchByBrokerIDInvestorID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindByBrokerIDInvestorID();
	}

	///记录所有的查询值
	queryBrokerIDInSearchByBrokerIDInvestorID= BrokerID.getValue();
	queryInvestorIDInSearchByBrokerIDInvestorID= InvestorID.getValue();

#ifdef COUNT_SEARCH
	multiFindByBrokerIDInvestorIDForClientTradingID++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CClientTradingID *theClientTradingID;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.InvestorID=InvestorID.getValue();
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchByBrokerIDInvestorID=pBrokerIDInvestorIDIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchByBrokerIDInvestorID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	theClientTradingID=(CClientTradingID *)(pLastFoundInSearchByBrokerIDInvestorID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theClientTradingID->BrokerID.getValue(),BrokerID.getValue()))
	{
		pLastFoundInSearchByBrokerIDInvestorID=NULL;
		return NULL;
	}
	if (compare(theClientTradingID->InvestorID.getValue(),InvestorID.getValue()))
	{
		pLastFoundInSearchByBrokerIDInvestorID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theClientTradingID;
}

CClientTradingID *CClientTradingIDFactory::findNextByBrokerIDInvestorID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchByBrokerIDInvestorID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindByBrokerIDInvestorIDForClientTradingID++;
#endif
	CClientTradingID *theClientTradingID;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchByBrokerIDInvestorID=pBrokerIDInvestorIDIndex->getNextNode(pLastFoundInSearchByBrokerIDInvestorID);
	if (pLastFoundInSearchByBrokerIDInvestorID==NULL)
	{
		return NULL;
	}

	theClientTradingID=(CClientTradingID *)(pLastFoundInSearchByBrokerIDInvestorID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theClientTradingID->BrokerID,queryBrokerIDInSearchByBrokerIDInvestorID))
	{
		pLastFoundInSearchByBrokerIDInvestorID=NULL;
		return NULL;
	}
	if (compare(theClientTradingID->InvestorID,queryInvestorIDInSearchByBrokerIDInvestorID))
	{
		pLastFoundInSearchByBrokerIDInvestorID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theClientTradingID;
}

void CClientTradingIDFactory::endFindByBrokerIDInvestorID(void)
{
	pLastFoundInSearchByBrokerIDInvestorID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByBrokerIDForClientTradingID=0;
#endif

CClientTradingID *CClientTradingIDFactory::startFindAllByBrokerID( const CReadOnlyBrokerIDType& BrokerID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByBrokerID of CClientTradingID while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByBrokerID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByBrokerID();
	}

	///记录所有的查询值
	queryBrokerIDInSearchAllByBrokerID= BrokerID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByBrokerID=(CClientTradingID *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByBrokerID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByBrokerID来寻找下一个
	if (compare(pLastFoundInSearchAllByBrokerID->BrokerID.getValue(),BrokerID.getValue()))
	{
		return findNextAllByBrokerID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByBrokerID;
}

CClientTradingID *CClientTradingIDFactory::findNextAllByBrokerID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByBrokerID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByBrokerID=(CClientTradingID *)(pMem->getNext());
		if (pLastFoundInSearchAllByBrokerID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByBrokerID->BrokerID,queryBrokerIDInSearchAllByBrokerID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByBrokerID;
	}
}

void CClientTradingIDFactory::endFindAllByBrokerID(void)
{
	pLastFoundInSearchAllByBrokerID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllForClientTradingID=0;
#endif

CClientTradingID *CClientTradingIDFactory::startFindAll()
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAll of CClientTradingID while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAll!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAll();
	}

	///记录所有的查询值

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAll=(CClientTradingID *)(pMem->getFirst());
	
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAll来寻找下一个
	
	///返回找到的结果
	return pLastFoundInSearchAll;
}

CClientTradingID *CClientTradingIDFactory::findNextAll(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAll=(CClientTradingID *)(pMem->getNext());
		if (pLastFoundInSearchAll==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		///返回找到的结果
		return pLastFoundInSearchAll;
	}
}

void CClientTradingIDFactory::endFindAll(void)
{
	pLastFoundInSearchAll=NULL;
}

int compareForBrokerIDInvestorIDIndexinInvestor(const void *pV1, const void *pV2)
{
	CInvestor *p1,*p2;
	p1=(CInvestor *)pV1;
	p2=(CInvestor *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InvestorID.getValue(),p2->InvestorID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByBrokerIDInvestorIDForInvestor=0;
#endif
CInvestor *CInvestorFactory::findByBrokerIDInvestorID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInvestorIDType&  InvestorID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrokerIDInvestorID of CInvestor while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByBrokerIDInvestorIDForInvestor++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.InvestorID=InvestorID.getValue();
	pNode=pBrokerIDInvestorIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CInvestor *)(pNode->pObject);
}

CInvestor *CInvestorFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInvestorIDType&  InvestorID)
{
	return findByBrokerIDInvestorID(BrokerID, InvestorID);
}
	
CInvestor *CInvestorFactory::findByPK(CWriteableInvestor *pInvestor)
{
	return findByPK(
		pInvestor->BrokerID
		,
		pInvestor->InvestorID
		);
}

bool CInvestorFactory::retrieveByPK(CWriteableInvestor *pInvestor)
{
	CInvestor *pOriginalInvestor;
	pOriginalInvestor=findByPK(pInvestor);
	if (pOriginalInvestor==NULL)
	{
		return false;
	}
	retrieve(pOriginalInvestor,pInvestor);
	return true;
}

CInvestor *CInvestorFactory::addByPK(CWriteableInvestor *pInvestor, CTransaction *pTransaction)
{
	CInvestor *pOriginalInvestor;
	pOriginalInvestor=findByPK(pInvestor);
	if (pOriginalInvestor != NULL)
	{
		return NULL;
	}
	return add(pInvestor,pTransaction);
}

bool CInvestorFactory::updateByPK(CWriteableInvestor *pInvestor, CTransaction *pTransaction, bool updateIndex)
{
	CInvestor *pOriginalInvestor;
	pOriginalInvestor=findByPK(pInvestor);
	if (pOriginalInvestor==NULL)
	{
		return false;
	}
	pInvestor->calAllHash();
	update(pOriginalInvestor,pInvestor,pTransaction,updateIndex);
	return true;
}

bool CInvestorFactory::removeByPK(CWriteableInvestor *pInvestor, CTransaction *pTransaction)
{
	CInvestor *pOriginalInvestor;
	pOriginalInvestor=findByPK(pInvestor);
	if (pOriginalInvestor==NULL)
	{
		return false;
	}
	remove(pOriginalInvestor,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int multiFindByInvestorIDForInvestor=0;
#endif

CInvestor *CInvestorFactory::startFindByInvestorID( const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindByInvestorID of CInvestor while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchByInvestorID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindByInvestorID();
	}

	///记录所有的查询值
	queryInvestorIDInSearchByInvestorID= InvestorID.getValue();

#ifdef COUNT_SEARCH
	multiFindByInvestorIDForInvestor++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CInvestor *theInvestor;
	compareObject.InvestorID=InvestorID.getValue();
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchByInvestorID=pBrokerIDInvestorIDIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchByInvestorID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	theInvestor=(CInvestor *)(pLastFoundInSearchByInvestorID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theInvestor->InvestorID.getValue(),InvestorID.getValue()))
	{
		pLastFoundInSearchByInvestorID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theInvestor;
}

CInvestor *CInvestorFactory::findNextByInvestorID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchByInvestorID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindByInvestorIDForInvestor++;
#endif
	CInvestor *theInvestor;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchByInvestorID=pBrokerIDInvestorIDIndex->getNextNode(pLastFoundInSearchByInvestorID);
	if (pLastFoundInSearchByInvestorID==NULL)
	{
		return NULL;
	}

	theInvestor=(CInvestor *)(pLastFoundInSearchByInvestorID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theInvestor->InvestorID,queryInvestorIDInSearchByInvestorID))
	{
		pLastFoundInSearchByInvestorID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theInvestor;
}

void CInvestorFactory::endFindByInvestorID(void)
{
	pLastFoundInSearchByInvestorID=NULL;
}

int compareForBrokerIDClientIDIndexinInvestorMargin(const void *pV1, const void *pV2)
{
	CInvestorMargin *p1,*p2;
	p1=(CInvestorMargin *)pV1;
	p2=(CInvestorMargin *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InvestorID.getValue(),p2->InvestorID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForBrkIDExIDIstIDVstIDHdgIndexinInvestorMargin(const void *pV1, const void *pV2)
{
	CInvestorMargin *p1,*p2;
	p1=(CInvestorMargin *)pV1;
	p2=(CInvestorMargin *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InstrumentID.getValue(),p2->InstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InvestorID.getValue(),p2->InvestorID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->HedgeFlag.getValue(),p2->HedgeFlag.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForBrkIDExIDIstIDVstIDIndexinInvestorMargin(const void *pV1, const void *pV2)
{
	CInvestorMargin *p1,*p2;
	p1=(CInvestorMargin *)pV1;
	p2=(CInvestorMargin *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InstrumentID.getValue(),p2->InstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InvestorID.getValue(),p2->InvestorID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByBrokerIDClientIDForInvestorMargin=0;
#endif
CInvestorMargin *CInvestorMarginFactory::findByBrokerIDClientID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInvestorIDType&  InvestorID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrokerIDClientID of CInvestorMargin while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByBrokerIDClientIDForInvestorMargin++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.InvestorID=InvestorID.getValue();
	pNode=pBrokerIDClientIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CInvestorMargin *)(pNode->pObject);
}



#ifdef COUNT_SEARCH
int findByBrkIDExIDIstIDVstIDHdgForInvestorMargin=0;
#endif
CInvestorMargin *CInvestorMarginFactory::findByBrkIDExIDIstIDVstIDHdg( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrkIDExIDIstIDVstIDHdg of CInvestorMargin while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByBrkIDExIDIstIDVstIDHdgForInvestorMargin++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.InstrumentID=InstrumentID.getValue();
	compareObject.InvestorID=InvestorID.getValue();
	compareObject.HedgeFlag=HedgeFlag.getValue();
	pNode=pBrkIDExIDIstIDVstIDHdgIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CInvestorMargin *)(pNode->pObject);
}

CInvestorMargin *CInvestorMarginFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag)
{
	return findByBrkIDExIDIstIDVstIDHdg(BrokerID, ExchangeID, InstrumentID, InvestorID, HedgeFlag);
}
	
CInvestorMargin *CInvestorMarginFactory::findByPK(CWriteableInvestorMargin *pInvestorMargin)
{
	return findByPK(
		pInvestorMargin->BrokerID
		,
		pInvestorMargin->ExchangeID
		,
		pInvestorMargin->InstrumentID
		,
		pInvestorMargin->InvestorID
		,
		pInvestorMargin->HedgeFlag
		);
}

bool CInvestorMarginFactory::retrieveByPK(CWriteableInvestorMargin *pInvestorMargin)
{
	CInvestorMargin *pOriginalInvestorMargin;
	pOriginalInvestorMargin=findByPK(pInvestorMargin);
	if (pOriginalInvestorMargin==NULL)
	{
		return false;
	}
	retrieve(pOriginalInvestorMargin,pInvestorMargin);
	return true;
}

CInvestorMargin *CInvestorMarginFactory::addByPK(CWriteableInvestorMargin *pInvestorMargin, CTransaction *pTransaction)
{
	CInvestorMargin *pOriginalInvestorMargin;
	pOriginalInvestorMargin=findByPK(pInvestorMargin);
	if (pOriginalInvestorMargin != NULL)
	{
		return NULL;
	}
	return add(pInvestorMargin,pTransaction);
}

bool CInvestorMarginFactory::updateByPK(CWriteableInvestorMargin *pInvestorMargin, CTransaction *pTransaction, bool updateIndex)
{
	CInvestorMargin *pOriginalInvestorMargin;
	pOriginalInvestorMargin=findByPK(pInvestorMargin);
	if (pOriginalInvestorMargin==NULL)
	{
		return false;
	}
	pInvestorMargin->calAllHash();
	update(pOriginalInvestorMargin,pInvestorMargin,pTransaction,updateIndex);
	return true;
}

bool CInvestorMarginFactory::removeByPK(CWriteableInvestorMargin *pInvestorMargin, CTransaction *pTransaction)
{
	CInvestorMargin *pOriginalInvestorMargin;
	pOriginalInvestorMargin=findByPK(pInvestorMargin);
	if (pOriginalInvestorMargin==NULL)
	{
		return false;
	}
	remove(pOriginalInvestorMargin,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int multiFindByBrkIDExIDIstIDVstIDForInvestorMargin=0;
#endif

CInvestorMargin *CInvestorMarginFactory::startFindByBrkIDExIDIstIDVstID( const CReadOnlyBrokerIDType& BrokerID,  const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& InstrumentID,  const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindByBrkIDExIDIstIDVstID of CInvestorMargin while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchByBrkIDExIDIstIDVstID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindByBrkIDExIDIstIDVstID();
	}

	///记录所有的查询值
	queryBrokerIDInSearchByBrkIDExIDIstIDVstID= BrokerID.getValue();
	queryExchangeIDInSearchByBrkIDExIDIstIDVstID= ExchangeID.getValue();
	queryInstrumentIDInSearchByBrkIDExIDIstIDVstID= InstrumentID.getValue();
	queryInvestorIDInSearchByBrkIDExIDIstIDVstID= InvestorID.getValue();

#ifdef COUNT_SEARCH
	multiFindByBrkIDExIDIstIDVstIDForInvestorMargin++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CInvestorMargin *theInvestorMargin;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.InstrumentID=InstrumentID.getValue();
	compareObject.InvestorID=InvestorID.getValue();
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchByBrkIDExIDIstIDVstID=pBrkIDExIDIstIDVstIDIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchByBrkIDExIDIstIDVstID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	theInvestorMargin=(CInvestorMargin *)(pLastFoundInSearchByBrkIDExIDIstIDVstID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theInvestorMargin->BrokerID.getValue(),BrokerID.getValue()))
	{
		pLastFoundInSearchByBrkIDExIDIstIDVstID=NULL;
		return NULL;
	}
	if (compare(theInvestorMargin->ExchangeID.getValue(),ExchangeID.getValue()))
	{
		pLastFoundInSearchByBrkIDExIDIstIDVstID=NULL;
		return NULL;
	}
	if (compare(theInvestorMargin->InstrumentID.getValue(),InstrumentID.getValue()))
	{
		pLastFoundInSearchByBrkIDExIDIstIDVstID=NULL;
		return NULL;
	}
	if (compare(theInvestorMargin->InvestorID.getValue(),InvestorID.getValue()))
	{
		pLastFoundInSearchByBrkIDExIDIstIDVstID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theInvestorMargin;
}

CInvestorMargin *CInvestorMarginFactory::findNextByBrkIDExIDIstIDVstID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchByBrkIDExIDIstIDVstID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindByBrkIDExIDIstIDVstIDForInvestorMargin++;
#endif
	CInvestorMargin *theInvestorMargin;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchByBrkIDExIDIstIDVstID=pBrkIDExIDIstIDVstIDIndex->getNextNode(pLastFoundInSearchByBrkIDExIDIstIDVstID);
	if (pLastFoundInSearchByBrkIDExIDIstIDVstID==NULL)
	{
		return NULL;
	}

	theInvestorMargin=(CInvestorMargin *)(pLastFoundInSearchByBrkIDExIDIstIDVstID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theInvestorMargin->BrokerID,queryBrokerIDInSearchByBrkIDExIDIstIDVstID))
	{
		pLastFoundInSearchByBrkIDExIDIstIDVstID=NULL;
		return NULL;
	}
	if (compare(theInvestorMargin->ExchangeID,queryExchangeIDInSearchByBrkIDExIDIstIDVstID))
	{
		pLastFoundInSearchByBrkIDExIDIstIDVstID=NULL;
		return NULL;
	}
	if (compare(theInvestorMargin->InstrumentID,queryInstrumentIDInSearchByBrkIDExIDIstIDVstID))
	{
		pLastFoundInSearchByBrkIDExIDIstIDVstID=NULL;
		return NULL;
	}
	if (compare(theInvestorMargin->InvestorID,queryInvestorIDInSearchByBrkIDExIDIstIDVstID))
	{
		pLastFoundInSearchByBrkIDExIDIstIDVstID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theInvestorMargin;
}

void CInvestorMarginFactory::endFindByBrkIDExIDIstIDVstID(void)
{
	pLastFoundInSearchByBrkIDExIDIstIDVstID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindByInstrumentIDForInvestorMargin=0;
#endif

CInvestorMargin *CInvestorMarginFactory::startFindByInstrumentID( const CReadOnlyInstrumentIDType& InstrumentID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindByInstrumentID of CInvestorMargin while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchByInstrumentID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindByInstrumentID();
	}

	///记录所有的查询值
	queryInstrumentIDInSearchByInstrumentID= InstrumentID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchByInstrumentID=(CInvestorMargin *)(pMem->getFirst());
	
	if (pLastFoundInSearchByInstrumentID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextByInstrumentID来寻找下一个
	if (compare(pLastFoundInSearchByInstrumentID->InstrumentID.getValue(),InstrumentID.getValue()))
	{
		return findNextByInstrumentID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchByInstrumentID;
}

CInvestorMargin *CInvestorMarginFactory::findNextByInstrumentID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchByInstrumentID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchByInstrumentID=(CInvestorMargin *)(pMem->getNext());
		if (pLastFoundInSearchByInstrumentID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchByInstrumentID->InstrumentID,queryInstrumentIDInSearchByInstrumentID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchByInstrumentID;
	}
}

void CInvestorMarginFactory::endFindByInstrumentID(void)
{
	pLastFoundInSearchByInstrumentID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindByBrokerIDForInvestorMargin=0;
#endif

CInvestorMargin *CInvestorMarginFactory::startFindByBrokerID( const CReadOnlyBrokerIDType& BrokerID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindByBrokerID of CInvestorMargin while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchByBrokerID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindByBrokerID();
	}

	///记录所有的查询值
	queryBrokerIDInSearchByBrokerID= BrokerID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchByBrokerID=(CInvestorMargin *)(pMem->getFirst());
	
	if (pLastFoundInSearchByBrokerID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextByBrokerID来寻找下一个
	if (compare(pLastFoundInSearchByBrokerID->BrokerID.getValue(),BrokerID.getValue()))
	{
		return findNextByBrokerID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchByBrokerID;
}

CInvestorMargin *CInvestorMarginFactory::findNextByBrokerID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchByBrokerID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchByBrokerID=(CInvestorMargin *)(pMem->getNext());
		if (pLastFoundInSearchByBrokerID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchByBrokerID->BrokerID,queryBrokerIDInSearchByBrokerID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchByBrokerID;
	}
}

void CInvestorMarginFactory::endFindByBrokerID(void)
{
	pLastFoundInSearchByBrokerID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllForInvestorMargin=0;
#endif

CInvestorMargin *CInvestorMarginFactory::startFindAll()
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAll of CInvestorMargin while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAll!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAll();
	}

	///记录所有的查询值

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAll=(CInvestorMargin *)(pMem->getFirst());
	
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAll来寻找下一个
	
	///返回找到的结果
	return pLastFoundInSearchAll;
}

CInvestorMargin *CInvestorMarginFactory::findNextAll(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAll=(CInvestorMargin *)(pMem->getNext());
		if (pLastFoundInSearchAll==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		///返回找到的结果
		return pLastFoundInSearchAll;
	}
}

void CInvestorMarginFactory::endFindAll(void)
{
	pLastFoundInSearchAll=NULL;
}

int compareForInstrumentIDIndexinInvestorFee(const void *pV1, const void *pV2)
{
	CInvestorFee *p1,*p2;
	p1=(CInvestorFee *)pV1;
	p2=(CInvestorFee *)pV2;
	switch (compare(p1->InstrumentID.getValue(),p2->InstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForBrkIDExIDIstIDVstIDHdgIndexinInvestorFee(const void *pV1, const void *pV2)
{
	CInvestorFee *p1,*p2;
	p1=(CInvestorFee *)pV1;
	p2=(CInvestorFee *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InstrumentID.getValue(),p2->InstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InvestorID.getValue(),p2->InvestorID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->HedgeFlag.getValue(),p2->HedgeFlag.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByBrkIDExIDIstIDVstIDHdgForInvestorFee=0;
#endif
CInvestorFee *CInvestorFeeFactory::findByBrkIDExIDIstIDVstIDHdg( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrkIDExIDIstIDVstIDHdg of CInvestorFee while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByBrkIDExIDIstIDVstIDHdgForInvestorFee++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.InstrumentID=InstrumentID.getValue();
	compareObject.InvestorID=InvestorID.getValue();
	compareObject.HedgeFlag=HedgeFlag.getValue();
	pNode=pBrkIDExIDIstIDVstIDHdgIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CInvestorFee *)(pNode->pObject);
}

CInvestorFee *CInvestorFeeFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag)
{
	return findByBrkIDExIDIstIDVstIDHdg(BrokerID, ExchangeID, InstrumentID, InvestorID, HedgeFlag);
}
	
CInvestorFee *CInvestorFeeFactory::findByPK(CWriteableInvestorFee *pInvestorFee)
{
	return findByPK(
		pInvestorFee->BrokerID
		,
		pInvestorFee->ExchangeID
		,
		pInvestorFee->InstrumentID
		,
		pInvestorFee->InvestorID
		,
		pInvestorFee->HedgeFlag
		);
}

bool CInvestorFeeFactory::retrieveByPK(CWriteableInvestorFee *pInvestorFee)
{
	CInvestorFee *pOriginalInvestorFee;
	pOriginalInvestorFee=findByPK(pInvestorFee);
	if (pOriginalInvestorFee==NULL)
	{
		return false;
	}
	retrieve(pOriginalInvestorFee,pInvestorFee);
	return true;
}

CInvestorFee *CInvestorFeeFactory::addByPK(CWriteableInvestorFee *pInvestorFee, CTransaction *pTransaction)
{
	CInvestorFee *pOriginalInvestorFee;
	pOriginalInvestorFee=findByPK(pInvestorFee);
	if (pOriginalInvestorFee != NULL)
	{
		return NULL;
	}
	return add(pInvestorFee,pTransaction);
}

bool CInvestorFeeFactory::updateByPK(CWriteableInvestorFee *pInvestorFee, CTransaction *pTransaction, bool updateIndex)
{
	CInvestorFee *pOriginalInvestorFee;
	pOriginalInvestorFee=findByPK(pInvestorFee);
	if (pOriginalInvestorFee==NULL)
	{
		return false;
	}
	pInvestorFee->calAllHash();
	update(pOriginalInvestorFee,pInvestorFee,pTransaction,updateIndex);
	return true;
}

bool CInvestorFeeFactory::removeByPK(CWriteableInvestorFee *pInvestorFee, CTransaction *pTransaction)
{
	CInvestorFee *pOriginalInvestorFee;
	pOriginalInvestorFee=findByPK(pInvestorFee);
	if (pOriginalInvestorFee==NULL)
	{
		return false;
	}
	remove(pOriginalInvestorFee,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int multiFindByInstrumentIDForInvestorFee=0;
#endif

CInvestorFee *CInvestorFeeFactory::startFindByInstrumentID( const CReadOnlyInstrumentIDType& InstrumentID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindByInstrumentID of CInvestorFee while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchByInstrumentID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindByInstrumentID();
	}

	///记录所有的查询值
	queryInstrumentIDInSearchByInstrumentID= InstrumentID.getValue();

#ifdef COUNT_SEARCH
	multiFindByInstrumentIDForInvestorFee++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CInvestorFee *theInvestorFee;
	compareObject.InstrumentID=InstrumentID.getValue();
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchByInstrumentID=pInstrumentIDIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchByInstrumentID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	theInvestorFee=(CInvestorFee *)(pLastFoundInSearchByInstrumentID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theInvestorFee->InstrumentID.getValue(),InstrumentID.getValue()))
	{
		pLastFoundInSearchByInstrumentID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theInvestorFee;
}

CInvestorFee *CInvestorFeeFactory::findNextByInstrumentID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchByInstrumentID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindByInstrumentIDForInvestorFee++;
#endif
	CInvestorFee *theInvestorFee;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchByInstrumentID=pInstrumentIDIndex->getNextNode(pLastFoundInSearchByInstrumentID);
	if (pLastFoundInSearchByInstrumentID==NULL)
	{
		return NULL;
	}

	theInvestorFee=(CInvestorFee *)(pLastFoundInSearchByInstrumentID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theInvestorFee->InstrumentID,queryInstrumentIDInSearchByInstrumentID))
	{
		pLastFoundInSearchByInstrumentID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theInvestorFee;
}

void CInvestorFeeFactory::endFindByInstrumentID(void)
{
	pLastFoundInSearchByInstrumentID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindByBrokerIDForInvestorFee=0;
#endif

CInvestorFee *CInvestorFeeFactory::startFindByBrokerID( const CReadOnlyBrokerIDType& BrokerID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindByBrokerID of CInvestorFee while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchByBrokerID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindByBrokerID();
	}

	///记录所有的查询值
	queryBrokerIDInSearchByBrokerID= BrokerID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchByBrokerID=(CInvestorFee *)(pMem->getFirst());
	
	if (pLastFoundInSearchByBrokerID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextByBrokerID来寻找下一个
	if (compare(pLastFoundInSearchByBrokerID->BrokerID.getValue(),BrokerID.getValue()))
	{
		return findNextByBrokerID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchByBrokerID;
}

CInvestorFee *CInvestorFeeFactory::findNextByBrokerID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchByBrokerID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchByBrokerID=(CInvestorFee *)(pMem->getNext());
		if (pLastFoundInSearchByBrokerID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchByBrokerID->BrokerID,queryBrokerIDInSearchByBrokerID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchByBrokerID;
	}
}

void CInvestorFeeFactory::endFindByBrokerID(void)
{
	pLastFoundInSearchByBrokerID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllForInvestorFee=0;
#endif

CInvestorFee *CInvestorFeeFactory::startFindAll()
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAll of CInvestorFee while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAll!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAll();
	}

	///记录所有的查询值

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAll=(CInvestorFee *)(pMem->getFirst());
	
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAll来寻找下一个
	
	///返回找到的结果
	return pLastFoundInSearchAll;
}

CInvestorFee *CInvestorFeeFactory::findNextAll(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAll=(CInvestorFee *)(pMem->getNext());
		if (pLastFoundInSearchAll==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		///返回找到的结果
		return pLastFoundInSearchAll;
	}
}

void CInvestorFeeFactory::endFindAll(void)
{
	pLastFoundInSearchAll=NULL;
}

int compareForBrokerIDUserIDIndexinUser(const void *pV1, const void *pV2)
{
	CUser *p1,*p2;
	p1=(CUser *)pV1;
	p2=(CUser *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->UserID.getValue(),p2->UserID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForUserIDIndexinUser(const void *pV1, const void *pV2)
{
	CUser *p1,*p2;
	p1=(CUser *)pV1;
	p2=(CUser *)pV2;
	switch (compare(p1->UserID.getValue(),p2->UserID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByBrokerIDUserIDForUser=0;
#endif
CUser *CUserFactory::findByBrokerIDUserID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrokerIDUserID of CUser while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByBrokerIDUserIDForUser++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.UserID=UserID.getValue();
	pNode=pBrokerIDUserIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CUser *)(pNode->pObject);
}

CUser *CUserFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID)
{
	return findByBrokerIDUserID(BrokerID, UserID);
}
	
CUser *CUserFactory::findByPK(CWriteableUser *pUser)
{
	return findByPK(
		pUser->BrokerID
		,
		pUser->UserID
		);
}

bool CUserFactory::retrieveByPK(CWriteableUser *pUser)
{
	CUser *pOriginalUser;
	pOriginalUser=findByPK(pUser);
	if (pOriginalUser==NULL)
	{
		return false;
	}
	retrieve(pOriginalUser,pUser);
	return true;
}

CUser *CUserFactory::addByPK(CWriteableUser *pUser, CTransaction *pTransaction)
{
	CUser *pOriginalUser;
	pOriginalUser=findByPK(pUser);
	if (pOriginalUser != NULL)
	{
		return NULL;
	}
	return add(pUser,pTransaction);
}

bool CUserFactory::updateByPK(CWriteableUser *pUser, CTransaction *pTransaction, bool updateIndex)
{
	CUser *pOriginalUser;
	pOriginalUser=findByPK(pUser);
	if (pOriginalUser==NULL)
	{
		return false;
	}
	pUser->calAllHash();
	update(pOriginalUser,pUser,pTransaction,updateIndex);
	return true;
}

bool CUserFactory::removeByPK(CWriteableUser *pUser, CTransaction *pTransaction)
{
	CUser *pOriginalUser;
	pOriginalUser=findByPK(pUser);
	if (pOriginalUser==NULL)
	{
		return false;
	}
	remove(pOriginalUser,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int multiFindStartByUserIDForUser=0;
#endif

CUser *CUserFactory::startFindStartByUserID( const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindStartByUserID of CUser while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchStartByUserID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindStartByUserID();
	}

	///记录所有的查询值
	queryUserIDInSearchStartByUserID= UserID.getValue();

#ifdef COUNT_SEARCH
	multiFindStartByUserIDForUser++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CUser *theUser;
	compareObject.UserID=UserID.getValue();
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchStartByUserID=pUserIDIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchStartByUserID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	theUser=(CUser *)(pLastFoundInSearchStartByUserID->pObject);
	
	///如果有一个条件不满足，则失败返回

	///返回找到的结果
	return theUser;
}

CUser *CUserFactory::findNextStartByUserID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchStartByUserID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindStartByUserIDForUser++;
#endif
	CUser *theUser;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchStartByUserID=pUserIDIndex->getNextNode(pLastFoundInSearchStartByUserID);
	if (pLastFoundInSearchStartByUserID==NULL)
	{
		return NULL;
	}

	theUser=(CUser *)(pLastFoundInSearchStartByUserID->pObject);
	
	///如果有一个条件不满足，则失败返回

	///返回找到的结果
	return theUser;
}

void CUserFactory::endFindStartByUserID(void)
{
	pLastFoundInSearchStartByUserID=NULL;
}

int compareForBrokerIDUserIDInvestorIDIndexinUserInvestor(const void *pV1, const void *pV2)
{
	CUserInvestor *p1,*p2;
	p1=(CUserInvestor *)pV1;
	p2=(CUserInvestor *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->UserID.getValue(),p2->UserID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InvestorID.getValue(),p2->InvestorID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForBrokerIDInvestorIDIndexinUserInvestor(const void *pV1, const void *pV2)
{
	CUserInvestor *p1,*p2;
	p1=(CUserInvestor *)pV1;
	p2=(CUserInvestor *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InvestorID.getValue(),p2->InvestorID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByBrokerIDUserIDInvestorIDForUserInvestor=0;
#endif
CUserInvestor *CUserInvestorFactory::findByBrokerIDUserIDInvestorID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyInvestorIDType&  InvestorID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrokerIDUserIDInvestorID of CUserInvestor while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByBrokerIDUserIDInvestorIDForUserInvestor++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.UserID=UserID.getValue();
	compareObject.InvestorID=InvestorID.getValue();
	pNode=pBrokerIDUserIDInvestorIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CUserInvestor *)(pNode->pObject);
}

CUserInvestor *CUserInvestorFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyInvestorIDType&  InvestorID)
{
	return findByBrokerIDUserIDInvestorID(BrokerID, UserID, InvestorID);
}
	
CUserInvestor *CUserInvestorFactory::findByPK(CWriteableUserInvestor *pUserInvestor)
{
	return findByPK(
		pUserInvestor->BrokerID
		,
		pUserInvestor->UserID
		,
		pUserInvestor->InvestorID
		);
}

bool CUserInvestorFactory::retrieveByPK(CWriteableUserInvestor *pUserInvestor)
{
	CUserInvestor *pOriginalUserInvestor;
	pOriginalUserInvestor=findByPK(pUserInvestor);
	if (pOriginalUserInvestor==NULL)
	{
		return false;
	}
	retrieve(pOriginalUserInvestor,pUserInvestor);
	return true;
}

CUserInvestor *CUserInvestorFactory::addByPK(CWriteableUserInvestor *pUserInvestor, CTransaction *pTransaction)
{
	CUserInvestor *pOriginalUserInvestor;
	pOriginalUserInvestor=findByPK(pUserInvestor);
	if (pOriginalUserInvestor != NULL)
	{
		return NULL;
	}
	return add(pUserInvestor,pTransaction);
}

bool CUserInvestorFactory::updateByPK(CWriteableUserInvestor *pUserInvestor, CTransaction *pTransaction, bool updateIndex)
{
	CUserInvestor *pOriginalUserInvestor;
	pOriginalUserInvestor=findByPK(pUserInvestor);
	if (pOriginalUserInvestor==NULL)
	{
		return false;
	}
	pUserInvestor->calAllHash();
	update(pOriginalUserInvestor,pUserInvestor,pTransaction,updateIndex);
	return true;
}

bool CUserInvestorFactory::removeByPK(CWriteableUserInvestor *pUserInvestor, CTransaction *pTransaction)
{
	CUserInvestor *pOriginalUserInvestor;
	pOriginalUserInvestor=findByPK(pUserInvestor);
	if (pOriginalUserInvestor==NULL)
	{
		return false;
	}
	remove(pOriginalUserInvestor,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int multiFindByBrokerIDInvestorIDForUserInvestor=0;
#endif

CUserInvestor *CUserInvestorFactory::startFindByBrokerIDInvestorID( const CReadOnlyBrokerIDType& BrokerID,  const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindByBrokerIDInvestorID of CUserInvestor while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchByBrokerIDInvestorID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindByBrokerIDInvestorID();
	}

	///记录所有的查询值
	queryBrokerIDInSearchByBrokerIDInvestorID= BrokerID.getValue();
	queryInvestorIDInSearchByBrokerIDInvestorID= InvestorID.getValue();

#ifdef COUNT_SEARCH
	multiFindByBrokerIDInvestorIDForUserInvestor++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CUserInvestor *theUserInvestor;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.InvestorID=InvestorID.getValue();
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchByBrokerIDInvestorID=pBrokerIDInvestorIDIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchByBrokerIDInvestorID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	theUserInvestor=(CUserInvestor *)(pLastFoundInSearchByBrokerIDInvestorID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theUserInvestor->BrokerID.getValue(),BrokerID.getValue()))
	{
		pLastFoundInSearchByBrokerIDInvestorID=NULL;
		return NULL;
	}
	if (compare(theUserInvestor->InvestorID.getValue(),InvestorID.getValue()))
	{
		pLastFoundInSearchByBrokerIDInvestorID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theUserInvestor;
}

CUserInvestor *CUserInvestorFactory::findNextByBrokerIDInvestorID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchByBrokerIDInvestorID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindByBrokerIDInvestorIDForUserInvestor++;
#endif
	CUserInvestor *theUserInvestor;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchByBrokerIDInvestorID=pBrokerIDInvestorIDIndex->getNextNode(pLastFoundInSearchByBrokerIDInvestorID);
	if (pLastFoundInSearchByBrokerIDInvestorID==NULL)
	{
		return NULL;
	}

	theUserInvestor=(CUserInvestor *)(pLastFoundInSearchByBrokerIDInvestorID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theUserInvestor->BrokerID,queryBrokerIDInSearchByBrokerIDInvestorID))
	{
		pLastFoundInSearchByBrokerIDInvestorID=NULL;
		return NULL;
	}
	if (compare(theUserInvestor->InvestorID,queryInvestorIDInSearchByBrokerIDInvestorID))
	{
		pLastFoundInSearchByBrokerIDInvestorID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theUserInvestor;
}

void CUserInvestorFactory::endFindByBrokerIDInvestorID(void)
{
	pLastFoundInSearchByBrokerIDInvestorID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByUserIDForUserInvestor=0;
#endif

CUserInvestor *CUserInvestorFactory::startFindAllByUserID( const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByUserID of CUserInvestor while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByUserID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByUserID();
	}

	///记录所有的查询值
	queryUserIDInSearchAllByUserID= UserID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByUserID=(CUserInvestor *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByUserID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByUserID来寻找下一个
	if (compare(pLastFoundInSearchAllByUserID->UserID.getValue(),UserID.getValue()))
	{
		return findNextAllByUserID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByUserID;
}

CUserInvestor *CUserInvestorFactory::findNextAllByUserID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByUserID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByUserID=(CUserInvestor *)(pMem->getNext());
		if (pLastFoundInSearchAllByUserID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByUserID->UserID,queryUserIDInSearchAllByUserID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByUserID;
	}
}

void CUserInvestorFactory::endFindAllByUserID(void)
{
	pLastFoundInSearchAllByUserID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByBrokerIDUserIDForUserInvestor=0;
#endif

CUserInvestor *CUserInvestorFactory::startFindAllByBrokerIDUserID( const CReadOnlyBrokerIDType& BrokerID,  const CReadOnlyUserIDType& UserID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByBrokerIDUserID of CUserInvestor while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByBrokerIDUserID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByBrokerIDUserID();
	}

	///记录所有的查询值
	queryBrokerIDInSearchAllByBrokerIDUserID= BrokerID.getValue();
	queryUserIDInSearchAllByBrokerIDUserID= UserID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByBrokerIDUserID=(CUserInvestor *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByBrokerIDUserID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByBrokerIDUserID来寻找下一个
	if (compare(pLastFoundInSearchAllByBrokerIDUserID->BrokerID.getValue(),BrokerID.getValue()))
	{
		return findNextAllByBrokerIDUserID();
	}
	if (compare(pLastFoundInSearchAllByBrokerIDUserID->UserID.getValue(),UserID.getValue()))
	{
		return findNextAllByBrokerIDUserID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByBrokerIDUserID;
}

CUserInvestor *CUserInvestorFactory::findNextAllByBrokerIDUserID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByBrokerIDUserID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByBrokerIDUserID=(CUserInvestor *)(pMem->getNext());
		if (pLastFoundInSearchAllByBrokerIDUserID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByBrokerIDUserID->BrokerID,queryBrokerIDInSearchAllByBrokerIDUserID))
		{
			continue;
		}
		if (compare(pLastFoundInSearchAllByBrokerIDUserID->UserID,queryUserIDInSearchAllByBrokerIDUserID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByBrokerIDUserID;
	}
}

void CUserInvestorFactory::endFindAllByBrokerIDUserID(void)
{
	pLastFoundInSearchAllByBrokerIDUserID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByBrokerIDForUserInvestor=0;
#endif

CUserInvestor *CUserInvestorFactory::startFindAllByBrokerID( const CReadOnlyBrokerIDType& BrokerID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByBrokerID of CUserInvestor while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByBrokerID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByBrokerID();
	}

	///记录所有的查询值
	queryBrokerIDInSearchAllByBrokerID= BrokerID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByBrokerID=(CUserInvestor *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByBrokerID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByBrokerID来寻找下一个
	if (compare(pLastFoundInSearchAllByBrokerID->BrokerID.getValue(),BrokerID.getValue()))
	{
		return findNextAllByBrokerID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByBrokerID;
}

CUserInvestor *CUserInvestorFactory::findNextAllByBrokerID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByBrokerID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByBrokerID=(CUserInvestor *)(pMem->getNext());
		if (pLastFoundInSearchAllByBrokerID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByBrokerID->BrokerID,queryBrokerIDInSearchAllByBrokerID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByBrokerID;
	}
}

void CUserInvestorFactory::endFindAllByBrokerID(void)
{
	pLastFoundInSearchAllByBrokerID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllForUserInvestor=0;
#endif

CUserInvestor *CUserInvestorFactory::startFindAll()
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAll of CUserInvestor while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAll!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAll();
	}

	///记录所有的查询值

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAll=(CUserInvestor *)(pMem->getFirst());
	
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAll来寻找下一个
	
	///返回找到的结果
	return pLastFoundInSearchAll;
}

CUserInvestor *CUserInvestorFactory::findNextAll(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAll=(CUserInvestor *)(pMem->getNext());
		if (pLastFoundInSearchAll==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		///返回找到的结果
		return pLastFoundInSearchAll;
	}
}

void CUserInvestorFactory::endFindAll(void)
{
	pLastFoundInSearchAll=NULL;
}

int compareForOrderUserIDIndexinOrderInsertFailed(const void *pV1, const void *pV2)
{
	COrderInsertFailed *p1,*p2;
	p1=(COrderInsertFailed *)pV1;
	p2=(COrderInsertFailed *)pV2;
	switch (compare(p1->OrderUserID.getValue(),p2->OrderUserID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForOrderLocalIDIndexinOrderInsertFailed(const void *pV1, const void *pV2)
{
	COrderInsertFailed *p1,*p2;
	p1=(COrderInsertFailed *)pV1;
	p2=(COrderInsertFailed *)pV2;
	switch (compare(p1->OrderLocalID.getValue(),p2->OrderLocalID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForExchangeIDOrderSysIDIndexinOrderInsertFailed(const void *pV1, const void *pV2)
{
	COrderInsertFailed *p1,*p2;
	p1=(COrderInsertFailed *)pV1;
	p2=(COrderInsertFailed *)pV2;
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->OrderSysID.getValue(),p2->OrderSysID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForExchangeIDSeatIDOrderLocalIDIndexinOrderInsertFailed(const void *pV1, const void *pV2)
{
	COrderInsertFailed *p1,*p2;
	p1=(COrderInsertFailed *)pV1;
	p2=(COrderInsertFailed *)pV2;
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->SeatID.getValue(),p2->SeatID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->OrderLocalID.getValue(),p2->OrderLocalID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByOrderUserIDForOrderInsertFailed=0;
#endif
COrderInsertFailed *COrderInsertFailedFactory::findByOrderUserID( const CReadOnlyUserIDType&  OrderUserID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByOrderUserID of COrderInsertFailed while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByOrderUserIDForOrderInsertFailed++;
#endif
	CAVLNode *pNode;
	compareObject.OrderUserID=OrderUserID.getValue();
	pNode=pOrderUserIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (COrderInsertFailed *)(pNode->pObject);
}



#ifdef COUNT_SEARCH
int findByOrderLocalIDForOrderInsertFailed=0;
#endif
COrderInsertFailed *COrderInsertFailedFactory::findByOrderLocalID( const CReadOnlyOrderLocalIDType&  OrderLocalID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByOrderLocalID of COrderInsertFailed while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByOrderLocalIDForOrderInsertFailed++;
#endif
	CAVLNode *pNode;
	compareObject.OrderLocalID=OrderLocalID.getValue();
	pNode=pOrderLocalIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (COrderInsertFailed *)(pNode->pObject);
}



#ifdef COUNT_SEARCH
int findByExchangeIDAndOrderSysIDForOrderInsertFailed=0;
#endif
COrderInsertFailed *COrderInsertFailedFactory::findByExchangeIDAndOrderSysID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyOrderSysIDType&  OrderSysID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByExchangeIDAndOrderSysID of COrderInsertFailed while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByExchangeIDAndOrderSysIDForOrderInsertFailed++;
#endif
	CAVLNode *pNode;
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.OrderSysID=OrderSysID.getValue();
	pNode=pExchangeIDOrderSysIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (COrderInsertFailed *)(pNode->pObject);
}



#ifdef COUNT_SEARCH
int multiFindAllByExchIDInvIDUserIDForOrderInsertFailed=0;
#endif

COrderInsertFailed *COrderInsertFailedFactory::startFindAllByExchIDInvIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInvestorIDType& InvestorID,  const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByExchIDInvIDUserID of COrderInsertFailed while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByExchIDInvIDUserID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByExchIDInvIDUserID();
	}

	///记录所有的查询值
	queryExchangeIDInSearchAllByExchIDInvIDUserID= ExchangeID.getValue();
	queryInvestorIDInSearchAllByExchIDInvIDUserID= InvestorID.getValue();
	queryUserIDInSearchAllByExchIDInvIDUserID= UserID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByExchIDInvIDUserID=(COrderInsertFailed *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByExchIDInvIDUserID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByExchIDInvIDUserID来寻找下一个
	if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->ExchangeID.getValue(),ExchangeID.getValue()))
	{
		return findNextAllByExchIDInvIDUserID();
	}
	if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->InvestorID.getValue(),InvestorID.getValue()))
	{
		return findNextAllByExchIDInvIDUserID();
	}
	if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->UserID.getValue(),UserID.getValue()))
	{
		return findNextAllByExchIDInvIDUserID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByExchIDInvIDUserID;
}

COrderInsertFailed *COrderInsertFailedFactory::findNextAllByExchIDInvIDUserID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByExchIDInvIDUserID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByExchIDInvIDUserID=(COrderInsertFailed *)(pMem->getNext());
		if (pLastFoundInSearchAllByExchIDInvIDUserID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->ExchangeID,queryExchangeIDInSearchAllByExchIDInvIDUserID))
		{
			continue;
		}
		if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->InvestorID,queryInvestorIDInSearchAllByExchIDInvIDUserID))
		{
			continue;
		}
		if (compare(pLastFoundInSearchAllByExchIDInvIDUserID->UserID,queryUserIDInSearchAllByExchIDInvIDUserID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByExchIDInvIDUserID;
	}
}

void COrderInsertFailedFactory::endFindAllByExchIDInvIDUserID(void)
{
	pLastFoundInSearchAllByExchIDInvIDUserID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllByExchIDInstruIDUserIDForOrderInsertFailed=0;
#endif

COrderInsertFailed *COrderInsertFailedFactory::startFindAllByExchIDInstruIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& InstrumentID,  const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByExchIDInstruIDUserID of COrderInsertFailed while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByExchIDInstruIDUserID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByExchIDInstruIDUserID();
	}

	///记录所有的查询值
	queryExchangeIDInSearchAllByExchIDInstruIDUserID= ExchangeID.getValue();
	queryInstrumentIDInSearchAllByExchIDInstruIDUserID= InstrumentID.getValue();
	queryUserIDInSearchAllByExchIDInstruIDUserID= UserID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByExchIDInstruIDUserID=(COrderInsertFailed *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByExchIDInstruIDUserID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByExchIDInstruIDUserID来寻找下一个
	if (compare(pLastFoundInSearchAllByExchIDInstruIDUserID->ExchangeID.getValue(),ExchangeID.getValue()))
	{
		return findNextAllByExchIDInstruIDUserID();
	}
	if (compare(pLastFoundInSearchAllByExchIDInstruIDUserID->UserID.getValue(),UserID.getValue()))
	{
		return findNextAllByExchIDInstruIDUserID();
	}
	
	///返回找到的结果
	return pLastFoundInSearchAllByExchIDInstruIDUserID;
}

COrderInsertFailed *COrderInsertFailedFactory::findNextAllByExchIDInstruIDUserID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByExchIDInstruIDUserID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByExchIDInstruIDUserID=(COrderInsertFailed *)(pMem->getNext());
		if (pLastFoundInSearchAllByExchIDInstruIDUserID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		if (compare(pLastFoundInSearchAllByExchIDInstruIDUserID->ExchangeID,queryExchangeIDInSearchAllByExchIDInstruIDUserID))
		{
			continue;
		}
		if (compare(pLastFoundInSearchAllByExchIDInstruIDUserID->UserID,queryUserIDInSearchAllByExchIDInstruIDUserID))
		{
			continue;
		}
		///返回找到的结果
		return pLastFoundInSearchAllByExchIDInstruIDUserID;
	}
}

void COrderInsertFailedFactory::endFindAllByExchIDInstruIDUserID(void)
{
	pLastFoundInSearchAllByExchIDInstruIDUserID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllForOrderInsertFailed=0;
#endif

COrderInsertFailed *COrderInsertFailedFactory::startFindAll()
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAll of COrderInsertFailed while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAll!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAll();
	}

	///记录所有的查询值

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAll=(COrderInsertFailed *)(pMem->getFirst());
	
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAll来寻找下一个
	
	///返回找到的结果
	return pLastFoundInSearchAll;
}

COrderInsertFailed *COrderInsertFailedFactory::findNextAll(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAll=(COrderInsertFailed *)(pMem->getNext());
		if (pLastFoundInSearchAll==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		///返回找到的结果
		return pLastFoundInSearchAll;
	}
}

void COrderInsertFailedFactory::endFindAll(void)
{
	pLastFoundInSearchAll=NULL;
}


#ifdef COUNT_SEARCH
int findByExchangeIDSeatIDAndOrderLocalIDForOrderInsertFailed=0;
#endif
COrderInsertFailed *COrderInsertFailedFactory::findByExchangeIDSeatIDAndOrderLocalID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlySeatIDType&  SeatID,  const CReadOnlyOrderLocalIDType&  OrderLocalID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByExchangeIDSeatIDAndOrderLocalID of COrderInsertFailed while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByExchangeIDSeatIDAndOrderLocalIDForOrderInsertFailed++;
#endif
	CAVLNode *pNode;
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.SeatID=SeatID.getValue();
	compareObject.OrderLocalID=OrderLocalID.getValue();
	pNode=pExchangeIDSeatIDOrderLocalIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (COrderInsertFailed *)(pNode->pObject);
}

COrderInsertFailed *COrderInsertFailedFactory::findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlySeatIDType&  SeatID,  const CReadOnlyOrderLocalIDType&  OrderLocalID)
{
	return findByExchangeIDSeatIDAndOrderLocalID(ExchangeID, SeatID, OrderLocalID);
}
	
COrderInsertFailed *COrderInsertFailedFactory::findByPK(CWriteableOrderInsertFailed *pOrderInsertFailed)
{
	return findByPK(
		pOrderInsertFailed->ExchangeID
		,
		pOrderInsertFailed->SeatID
		,
		pOrderInsertFailed->OrderLocalID
		);
}

bool COrderInsertFailedFactory::retrieveByPK(CWriteableOrderInsertFailed *pOrderInsertFailed)
{
	COrderInsertFailed *pOriginalOrderInsertFailed;
	pOriginalOrderInsertFailed=findByPK(pOrderInsertFailed);
	if (pOriginalOrderInsertFailed==NULL)
	{
		return false;
	}
	retrieve(pOriginalOrderInsertFailed,pOrderInsertFailed);
	return true;
}

COrderInsertFailed *COrderInsertFailedFactory::addByPK(CWriteableOrderInsertFailed *pOrderInsertFailed, CTransaction *pTransaction)
{
	COrderInsertFailed *pOriginalOrderInsertFailed;
	pOriginalOrderInsertFailed=findByPK(pOrderInsertFailed);
	if (pOriginalOrderInsertFailed != NULL)
	{
		return NULL;
	}
	return add(pOrderInsertFailed,pTransaction);
}

bool COrderInsertFailedFactory::updateByPK(CWriteableOrderInsertFailed *pOrderInsertFailed, CTransaction *pTransaction, bool updateIndex)
{
	COrderInsertFailed *pOriginalOrderInsertFailed;
	pOriginalOrderInsertFailed=findByPK(pOrderInsertFailed);
	if (pOriginalOrderInsertFailed==NULL)
	{
		return false;
	}
	pOrderInsertFailed->calAllHash();
	update(pOriginalOrderInsertFailed,pOrderInsertFailed,pTransaction,updateIndex);
	return true;
}

bool COrderInsertFailedFactory::removeByPK(CWriteableOrderInsertFailed *pOrderInsertFailed, CTransaction *pTransaction)
{
	COrderInsertFailed *pOriginalOrderInsertFailed;
	pOriginalOrderInsertFailed=findByPK(pOrderInsertFailed);
	if (pOriginalOrderInsertFailed==NULL)
	{
		return false;
	}
	remove(pOriginalOrderInsertFailed,pTransaction);
	return true;
}


int compareForBrkExIDInsUserInvIndexinUserTradingRight(const void *pV1, const void *pV2)
{
	CUserTradingRight *p1,*p2;
	p1=(CUserTradingRight *)pV1;
	p2=(CUserTradingRight *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InstrumentID.getValue(),p2->InstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->UserID.getValue(),p2->UserID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InvestorID.getValue(),p2->InvestorID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByBrkExIDInsUserInvForUserTradingRight=0;
#endif
CUserTradingRight *CUserTradingRightFactory::findByBrkExIDInsUserInv( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyInvestorIDType&  InvestorID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrkExIDInsUserInv of CUserTradingRight while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByBrkExIDInsUserInvForUserTradingRight++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.InstrumentID=InstrumentID.getValue();
	compareObject.UserID=UserID.getValue();
	compareObject.InvestorID=InvestorID.getValue();
	pNode=pBrkExIDInsUserInvIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CUserTradingRight *)(pNode->pObject);
}

CUserTradingRight *CUserTradingRightFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyInvestorIDType&  InvestorID)
{
	return findByBrkExIDInsUserInv(BrokerID, ExchangeID, InstrumentID, UserID, InvestorID);
}
	
CUserTradingRight *CUserTradingRightFactory::findByPK(CWriteableUserTradingRight *pUserTradingRight)
{
	return findByPK(
		pUserTradingRight->BrokerID
		,
		pUserTradingRight->ExchangeID
		,
		pUserTradingRight->InstrumentID
		,
		pUserTradingRight->UserID
		,
		pUserTradingRight->InvestorID
		);
}

bool CUserTradingRightFactory::retrieveByPK(CWriteableUserTradingRight *pUserTradingRight)
{
	CUserTradingRight *pOriginalUserTradingRight;
	pOriginalUserTradingRight=findByPK(pUserTradingRight);
	if (pOriginalUserTradingRight==NULL)
	{
		return false;
	}
	retrieve(pOriginalUserTradingRight,pUserTradingRight);
	return true;
}

CUserTradingRight *CUserTradingRightFactory::addByPK(CWriteableUserTradingRight *pUserTradingRight, CTransaction *pTransaction)
{
	CUserTradingRight *pOriginalUserTradingRight;
	pOriginalUserTradingRight=findByPK(pUserTradingRight);
	if (pOriginalUserTradingRight != NULL)
	{
		return NULL;
	}
	return add(pUserTradingRight,pTransaction);
}

bool CUserTradingRightFactory::updateByPK(CWriteableUserTradingRight *pUserTradingRight, CTransaction *pTransaction, bool updateIndex)
{
	CUserTradingRight *pOriginalUserTradingRight;
	pOriginalUserTradingRight=findByPK(pUserTradingRight);
	if (pOriginalUserTradingRight==NULL)
	{
		return false;
	}
	pUserTradingRight->calAllHash();
	update(pOriginalUserTradingRight,pUserTradingRight,pTransaction,updateIndex);
	return true;
}

bool CUserTradingRightFactory::removeByPK(CWriteableUserTradingRight *pUserTradingRight, CTransaction *pTransaction)
{
	CUserTradingRight *pOriginalUserTradingRight;
	pOriginalUserTradingRight=findByPK(pUserTradingRight);
	if (pOriginalUserTradingRight==NULL)
	{
		return false;
	}
	remove(pOriginalUserTradingRight,pTransaction);
	return true;
}


int compareForSessionIDFrontIDIndexinUserSession(const void *pV1, const void *pV2)
{
	CUserSession *p1,*p2;
	p1=(CUserSession *)pV1;
	p2=(CUserSession *)pV2;
	switch (compare(p1->SessionID.getValue(),p2->SessionID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->FrontID.getValue(),p2->FrontID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForBrokerIDUserIDSFIDIndexinUserSession(const void *pV1, const void *pV2)
{
	CUserSession *p1,*p2;
	p1=(CUserSession *)pV1;
	p2=(CUserSession *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->UserID.getValue(),p2->UserID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->SessionID.getValue(),p2->SessionID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->FrontID.getValue(),p2->FrontID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}
int compareForUserIndexinUserSession(const void *pV1, const void *pV2)
{
	CUserSession *p1,*p2;
	p1=(CUserSession *)pV1;
	p2=(CUserSession *)pV2;
	switch (compare(p1->UserID.getValue(),p2->UserID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findBySessionIDFrontIDForUserSession=0;
#endif
CUserSession *CUserSessionFactory::findBySessionIDFrontID( const CReadOnlySessionIDType&  SessionID,  const CReadOnlyFrontIDType&  FrontID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findBySessionIDFrontID of CUserSession while run level < 0");
	}
#ifdef COUNT_SEARCH
	findBySessionIDFrontIDForUserSession++;
#endif
	CAVLNode *pNode;
	compareObject.SessionID=SessionID.getValue();
	compareObject.FrontID=FrontID.getValue();
	pNode=pSessionIDFrontIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CUserSession *)(pNode->pObject);
}

CUserSession *CUserSessionFactory::findByPK( const CReadOnlySessionIDType&  SessionID,  const CReadOnlyFrontIDType&  FrontID)
{
	return findBySessionIDFrontID(SessionID, FrontID);
}
	
CUserSession *CUserSessionFactory::findByPK(CWriteableUserSession *pUserSession)
{
	return findByPK(
		pUserSession->SessionID
		,
		pUserSession->FrontID
		);
}

bool CUserSessionFactory::retrieveByPK(CWriteableUserSession *pUserSession)
{
	CUserSession *pOriginalUserSession;
	pOriginalUserSession=findByPK(pUserSession);
	if (pOriginalUserSession==NULL)
	{
		return false;
	}
	retrieve(pOriginalUserSession,pUserSession);
	return true;
}

CUserSession *CUserSessionFactory::addByPK(CWriteableUserSession *pUserSession, CTransaction *pTransaction)
{
	CUserSession *pOriginalUserSession;
	pOriginalUserSession=findByPK(pUserSession);
	if (pOriginalUserSession != NULL)
	{
		return NULL;
	}
	return add(pUserSession,pTransaction);
}

bool CUserSessionFactory::updateByPK(CWriteableUserSession *pUserSession, CTransaction *pTransaction, bool updateIndex)
{
	CUserSession *pOriginalUserSession;
	pOriginalUserSession=findByPK(pUserSession);
	if (pOriginalUserSession==NULL)
	{
		return false;
	}
	pUserSession->calAllHash();
	update(pOriginalUserSession,pUserSession,pTransaction,updateIndex);
	return true;
}

bool CUserSessionFactory::removeByPK(CWriteableUserSession *pUserSession, CTransaction *pTransaction)
{
	CUserSession *pOriginalUserSession;
	pOriginalUserSession=findByPK(pUserSession);
	if (pOriginalUserSession==NULL)
	{
		return false;
	}
	remove(pOriginalUserSession,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int findByBrokerIDUserIDSFIDForUserSession=0;
#endif
CUserSession *CUserSessionFactory::findByBrokerIDUserIDSFID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlySessionIDType&  SessionID,  const CReadOnlyFrontIDType&  FrontID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrokerIDUserIDSFID of CUserSession while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByBrokerIDUserIDSFIDForUserSession++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.UserID=UserID.getValue();
	compareObject.SessionID=SessionID.getValue();
	compareObject.FrontID=FrontID.getValue();
	pNode=pBrokerIDUserIDSFIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CUserSession *)(pNode->pObject);
}



#ifdef COUNT_SEARCH
int multiFindByUserIDForUserSession=0;
#endif

CUserSession *CUserSessionFactory::startFindByUserID( const CReadOnlyUserIDType& UserID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindByUserID of CUserSession while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchByUserID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindByUserID();
	}

	///记录所有的查询值
	queryUserIDInSearchByUserID= UserID.getValue();

#ifdef COUNT_SEARCH
	multiFindByUserIDForUserSession++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CUserSession *theUserSession;
	compareObject.UserID=UserID.getValue();
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchByUserID=pUserIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchByUserID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	theUserSession=(CUserSession *)(pLastFoundInSearchByUserID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theUserSession->UserID.getValue(),UserID.getValue()))
	{
		pLastFoundInSearchByUserID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theUserSession;
}

CUserSession *CUserSessionFactory::findNextByUserID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchByUserID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindByUserIDForUserSession++;
#endif
	CUserSession *theUserSession;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchByUserID=pUserIndex->getNextNode(pLastFoundInSearchByUserID);
	if (pLastFoundInSearchByUserID==NULL)
	{
		return NULL;
	}

	theUserSession=(CUserSession *)(pLastFoundInSearchByUserID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theUserSession->UserID,queryUserIDInSearchByUserID))
	{
		pLastFoundInSearchByUserID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theUserSession;
}

void CUserSessionFactory::endFindByUserID(void)
{
	pLastFoundInSearchByUserID=NULL;
}


#ifdef COUNT_SEARCH
int findByFrontIDSessionIDForMaxLocalID=0;
#endif
CMaxLocalID *CMaxLocalIDFactory::findByFrontIDSessionID( const CReadOnlyFrontIDType&  FrontID,  const CReadOnlySessionIDType&  SessionID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByFrontIDSessionID of CMaxLocalID while run level < 0");
	}
	CHashIndexNode *pNode;
	compareObject.FrontID=FrontID.getValue();
	compareObject.SessionID=SessionID.getValue();
	
	compareObject.calHashFrontIDSessionID();
	for (pNode=pFrontIDSessionIDHashIndex->searchFirstEqual(compareObject.HashFrontIDSessionID);
		pNode!=NULL;
		pNode=pFrontIDSessionIDHashIndex->searchNextEqual(pNode))
	{
		if (((CMaxLocalID *)(pNode->pObject))->HashFrontIDSessionID != compareObject.HashFrontIDSessionID)
		{
			continue;
		}
		if (compare(((CMaxLocalID *)(pNode->pObject))->FrontID.getValue(),FrontID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CMaxLocalID *)(pNode->pObject))->SessionID.getValue(),SessionID.getValue())!=0)
		{
			continue;
		}
		return (CMaxLocalID *)(pNode->pObject);
	}
	return NULL;
}

CMaxLocalID *CMaxLocalIDFactory::findByPK( const CReadOnlyFrontIDType&  FrontID,  const CReadOnlySessionIDType&  SessionID)
{
	return findByFrontIDSessionID(FrontID, SessionID);
}
	
CMaxLocalID *CMaxLocalIDFactory::findByPK(CWriteableMaxLocalID *pMaxLocalID)
{
	return findByPK(
		pMaxLocalID->FrontID
		,
		pMaxLocalID->SessionID
		);
}

bool CMaxLocalIDFactory::retrieveByPK(CWriteableMaxLocalID *pMaxLocalID)
{
	CMaxLocalID *pOriginalMaxLocalID;
	pOriginalMaxLocalID=findByPK(pMaxLocalID);
	if (pOriginalMaxLocalID==NULL)
	{
		return false;
	}
	retrieve(pOriginalMaxLocalID,pMaxLocalID);
	return true;
}

CMaxLocalID *CMaxLocalIDFactory::addByPK(CWriteableMaxLocalID *pMaxLocalID, CTransaction *pTransaction)
{
	CMaxLocalID *pOriginalMaxLocalID;
	pOriginalMaxLocalID=findByPK(pMaxLocalID);
	if (pOriginalMaxLocalID != NULL)
	{
		return NULL;
	}
	return add(pMaxLocalID,pTransaction);
}

bool CMaxLocalIDFactory::updateByPK(CWriteableMaxLocalID *pMaxLocalID, CTransaction *pTransaction, bool updateIndex)
{
	CMaxLocalID *pOriginalMaxLocalID;
	pOriginalMaxLocalID=findByPK(pMaxLocalID);
	if (pOriginalMaxLocalID==NULL)
	{
		return false;
	}
	pMaxLocalID->calAllHash();
	update(pOriginalMaxLocalID,pMaxLocalID,pTransaction,updateIndex);
	return true;
}

bool CMaxLocalIDFactory::removeByPK(CWriteableMaxLocalID *pMaxLocalID, CTransaction *pTransaction)
{
	CMaxLocalID *pOriginalMaxLocalID;
	pOriginalMaxLocalID=findByPK(pMaxLocalID);
	if (pOriginalMaxLocalID==NULL)
	{
		return false;
	}
	remove(pOriginalMaxLocalID,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int findByBrokerIDUserIDLocalIDForBrkUserIDLocalID=0;
#endif
CBrkUserIDLocalID *CBrkUserIDLocalIDFactory::findByBrokerIDUserIDLocalID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyUserOrderLocalIDType&  UserOrderLocalID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrokerIDUserIDLocalID of CBrkUserIDLocalID while run level < 0");
	}
	CHashIndexNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.UserID=UserID.getValue();
	compareObject.UserOrderLocalID=UserOrderLocalID.getValue();
	
	compareObject.calHashBrokerIDUserIDLocalID();
	for (pNode=pBrokerIDUserIDLocalIDHashIndex->searchFirstEqual(compareObject.HashBrokerIDUserIDLocalID);
		pNode!=NULL;
		pNode=pBrokerIDUserIDLocalIDHashIndex->searchNextEqual(pNode))
	{
		if (((CBrkUserIDLocalID *)(pNode->pObject))->HashBrokerIDUserIDLocalID != compareObject.HashBrokerIDUserIDLocalID)
		{
			continue;
		}
		if (compare(((CBrkUserIDLocalID *)(pNode->pObject))->BrokerID.getValue(),BrokerID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CBrkUserIDLocalID *)(pNode->pObject))->UserID.getValue(),UserID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CBrkUserIDLocalID *)(pNode->pObject))->UserOrderLocalID.getValue(),UserOrderLocalID.getValue())!=0)
		{
			continue;
		}
		return (CBrkUserIDLocalID *)(pNode->pObject);
	}
	return NULL;
}

CBrkUserIDLocalID *CBrkUserIDLocalIDFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyUserOrderLocalIDType&  UserOrderLocalID)
{
	return findByBrokerIDUserIDLocalID(BrokerID, UserID, UserOrderLocalID);
}
	
CBrkUserIDLocalID *CBrkUserIDLocalIDFactory::findByPK(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID)
{
	return findByPK(
		pBrkUserIDLocalID->BrokerID
		,
		pBrkUserIDLocalID->UserID
		,
		pBrkUserIDLocalID->UserOrderLocalID
		);
}

bool CBrkUserIDLocalIDFactory::retrieveByPK(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID)
{
	CBrkUserIDLocalID *pOriginalBrkUserIDLocalID;
	pOriginalBrkUserIDLocalID=findByPK(pBrkUserIDLocalID);
	if (pOriginalBrkUserIDLocalID==NULL)
	{
		return false;
	}
	retrieve(pOriginalBrkUserIDLocalID,pBrkUserIDLocalID);
	return true;
}

CBrkUserIDLocalID *CBrkUserIDLocalIDFactory::addByPK(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID, CTransaction *pTransaction)
{
	CBrkUserIDLocalID *pOriginalBrkUserIDLocalID;
	pOriginalBrkUserIDLocalID=findByPK(pBrkUserIDLocalID);
	if (pOriginalBrkUserIDLocalID != NULL)
	{
		return NULL;
	}
	return add(pBrkUserIDLocalID,pTransaction);
}

bool CBrkUserIDLocalIDFactory::updateByPK(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID, CTransaction *pTransaction, bool updateIndex)
{
	CBrkUserIDLocalID *pOriginalBrkUserIDLocalID;
	pOriginalBrkUserIDLocalID=findByPK(pBrkUserIDLocalID);
	if (pOriginalBrkUserIDLocalID==NULL)
	{
		return false;
	}
	pBrkUserIDLocalID->calAllHash();
	update(pOriginalBrkUserIDLocalID,pBrkUserIDLocalID,pTransaction,updateIndex);
	return true;
}

bool CBrkUserIDLocalIDFactory::removeByPK(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID, CTransaction *pTransaction)
{
	CBrkUserIDLocalID *pOriginalBrkUserIDLocalID;
	pOriginalBrkUserIDLocalID=findByPK(pBrkUserIDLocalID);
	if (pOriginalBrkUserIDLocalID==NULL)
	{
		return false;
	}
	remove(pOriginalBrkUserIDLocalID,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int findByBrokerClientAndInsGroupForPartClientInsGroupPosition=0;
#endif
CPartClientInsGroupPosition *CPartClientInsGroupPositionFactory::findByBrokerClientAndInsGroup( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyClientIDType&  ClientID,  const CReadOnlyInstrumentGroupIDType&  InstrumentGroupID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrokerClientAndInsGroup of CPartClientInsGroupPosition while run level < 0");
	}
	CHashIndexNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.ClientID=ClientID.getValue();
	compareObject.InstrumentGroupID=InstrumentGroupID.getValue();
	
	compareObject.calHashPartClientAndInsGroup();
	for (pNode=pPartClientAndInsGroupHashIndex->searchFirstEqual(compareObject.HashPartClientAndInsGroup);
		pNode!=NULL;
		pNode=pPartClientAndInsGroupHashIndex->searchNextEqual(pNode))
	{
		if (((CPartClientInsGroupPosition *)(pNode->pObject))->HashPartClientAndInsGroup != compareObject.HashPartClientAndInsGroup)
		{
			continue;
		}
		if (compare(((CPartClientInsGroupPosition *)(pNode->pObject))->BrokerID.getValue(),BrokerID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CPartClientInsGroupPosition *)(pNode->pObject))->ClientID.getValue(),ClientID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CPartClientInsGroupPosition *)(pNode->pObject))->InstrumentGroupID.getValue(),InstrumentGroupID.getValue())!=0)
		{
			continue;
		}
		return (CPartClientInsGroupPosition *)(pNode->pObject);
	}
	return NULL;
}



#ifdef COUNT_SEARCH
int findByBrokerClientAndInsGroupForClientMarginCombType=0;
#endif
CClientMarginCombType *CClientMarginCombTypeFactory::findByBrokerClientAndInsGroup( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyClientIDType&  ClientID,  const CReadOnlyInstrumentGroupIDType&  InstrumentGroupID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrokerClientAndInsGroup of CClientMarginCombType while run level < 0");
	}
	CHashIndexNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.ClientID=ClientID.getValue();
	compareObject.InstrumentGroupID=InstrumentGroupID.getValue();
	
	compareObject.calHashClientAndInsGroup();
	for (pNode=pClientAndInsGroupHashIndex->searchFirstEqual(compareObject.HashClientAndInsGroup);
		pNode!=NULL;
		pNode=pClientAndInsGroupHashIndex->searchNextEqual(pNode))
	{
		if (((CClientMarginCombType *)(pNode->pObject))->HashClientAndInsGroup != compareObject.HashClientAndInsGroup)
		{
			continue;
		}
		if (compare(((CClientMarginCombType *)(pNode->pObject))->BrokerID.getValue(),BrokerID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CClientMarginCombType *)(pNode->pObject))->ClientID.getValue(),ClientID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CClientMarginCombType *)(pNode->pObject))->InstrumentGroupID.getValue(),InstrumentGroupID.getValue())!=0)
		{
			continue;
		}
		return (CClientMarginCombType *)(pNode->pObject);
	}
	return NULL;
}

CClientMarginCombType *CClientMarginCombTypeFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyClientIDType&  ClientID,  const CReadOnlyInstrumentGroupIDType&  InstrumentGroupID)
{
	return findByBrokerClientAndInsGroup(BrokerID, ClientID, InstrumentGroupID);
}
	
CClientMarginCombType *CClientMarginCombTypeFactory::findByPK(CWriteableClientMarginCombType *pClientMarginCombType)
{
	return findByPK(
		pClientMarginCombType->BrokerID
		,
		pClientMarginCombType->ClientID
		,
		pClientMarginCombType->InstrumentGroupID
		);
}

bool CClientMarginCombTypeFactory::retrieveByPK(CWriteableClientMarginCombType *pClientMarginCombType)
{
	CClientMarginCombType *pOriginalClientMarginCombType;
	pOriginalClientMarginCombType=findByPK(pClientMarginCombType);
	if (pOriginalClientMarginCombType==NULL)
	{
		return false;
	}
	retrieve(pOriginalClientMarginCombType,pClientMarginCombType);
	return true;
}

CClientMarginCombType *CClientMarginCombTypeFactory::addByPK(CWriteableClientMarginCombType *pClientMarginCombType, CTransaction *pTransaction)
{
	CClientMarginCombType *pOriginalClientMarginCombType;
	pOriginalClientMarginCombType=findByPK(pClientMarginCombType);
	if (pOriginalClientMarginCombType != NULL)
	{
		return NULL;
	}
	return add(pClientMarginCombType,pTransaction);
}

bool CClientMarginCombTypeFactory::updateByPK(CWriteableClientMarginCombType *pClientMarginCombType, CTransaction *pTransaction, bool updateIndex)
{
	CClientMarginCombType *pOriginalClientMarginCombType;
	pOriginalClientMarginCombType=findByPK(pClientMarginCombType);
	if (pOriginalClientMarginCombType==NULL)
	{
		return false;
	}
	pClientMarginCombType->calAllHash();
	update(pOriginalClientMarginCombType,pClientMarginCombType,pTransaction,updateIndex);
	return true;
}

bool CClientMarginCombTypeFactory::removeByPK(CWriteableClientMarginCombType *pClientMarginCombType, CTransaction *pTransaction)
{
	CClientMarginCombType *pOriginalClientMarginCombType;
	pOriginalClientMarginCombType=findByPK(pClientMarginCombType);
	if (pOriginalClientMarginCombType==NULL)
	{
		return false;
	}
	remove(pOriginalClientMarginCombType,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int findByBrokerInstrumentIDForInstrumentGroup=0;
#endif
CInstrumentGroup *CInstrumentGroupFactory::findByBrokerInstrumentID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInstrumentIDType&  InstrumentID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrokerInstrumentID of CInstrumentGroup while run level < 0");
	}
	CHashIndexNode *pNode;
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.InstrumentID=InstrumentID.getValue();
	
	compareObject.calHashBrokerInstrumentID();
	for (pNode=pBrokerInstrumentIDHashIndex->searchFirstEqual(compareObject.HashBrokerInstrumentID);
		pNode!=NULL;
		pNode=pBrokerInstrumentIDHashIndex->searchNextEqual(pNode))
	{
		if (((CInstrumentGroup *)(pNode->pObject))->HashBrokerInstrumentID != compareObject.HashBrokerInstrumentID)
		{
			continue;
		}
		if (compare(((CInstrumentGroup *)(pNode->pObject))->ExchangeID.getValue(),ExchangeID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CInstrumentGroup *)(pNode->pObject))->BrokerID.getValue(),BrokerID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CInstrumentGroup *)(pNode->pObject))->InstrumentID.getValue(),InstrumentID.getValue())!=0)
		{
			continue;
		}
		return (CInstrumentGroup *)(pNode->pObject);
	}
	return NULL;
}

CInstrumentGroup *CInstrumentGroupFactory::findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInstrumentIDType&  InstrumentID)
{
	return findByBrokerInstrumentID(ExchangeID, BrokerID, InstrumentID);
}
	
CInstrumentGroup *CInstrumentGroupFactory::findByPK(CWriteableInstrumentGroup *pInstrumentGroup)
{
	return findByPK(
		pInstrumentGroup->ExchangeID
		,
		pInstrumentGroup->BrokerID
		,
		pInstrumentGroup->InstrumentID
		);
}

bool CInstrumentGroupFactory::retrieveByPK(CWriteableInstrumentGroup *pInstrumentGroup)
{
	CInstrumentGroup *pOriginalInstrumentGroup;
	pOriginalInstrumentGroup=findByPK(pInstrumentGroup);
	if (pOriginalInstrumentGroup==NULL)
	{
		return false;
	}
	retrieve(pOriginalInstrumentGroup,pInstrumentGroup);
	return true;
}

CInstrumentGroup *CInstrumentGroupFactory::addByPK(CWriteableInstrumentGroup *pInstrumentGroup, CTransaction *pTransaction)
{
	CInstrumentGroup *pOriginalInstrumentGroup;
	pOriginalInstrumentGroup=findByPK(pInstrumentGroup);
	if (pOriginalInstrumentGroup != NULL)
	{
		return NULL;
	}
	return add(pInstrumentGroup,pTransaction);
}

bool CInstrumentGroupFactory::updateByPK(CWriteableInstrumentGroup *pInstrumentGroup, CTransaction *pTransaction, bool updateIndex)
{
	CInstrumentGroup *pOriginalInstrumentGroup;
	pOriginalInstrumentGroup=findByPK(pInstrumentGroup);
	if (pOriginalInstrumentGroup==NULL)
	{
		return false;
	}
	pInstrumentGroup->calAllHash();
	update(pOriginalInstrumentGroup,pInstrumentGroup,pTransaction,updateIndex);
	return true;
}

bool CInstrumentGroupFactory::removeByPK(CWriteableInstrumentGroup *pInstrumentGroup, CTransaction *pTransaction)
{
	CInstrumentGroup *pOriginalInstrumentGroup;
	pOriginalInstrumentGroup=findByPK(pInstrumentGroup);
	if (pOriginalInstrumentGroup==NULL)
	{
		return false;
	}
	remove(pOriginalInstrumentGroup,pTransaction);
	return true;
}


int compareForTradeDateInstrumentIDIndexinSGEDeferRate(const void *pV1, const void *pV2)
{
	CSGEDeferRate *p1,*p2;
	p1=(CSGEDeferRate *)pV1;
	p2=(CSGEDeferRate *)pV2;
	switch (compare(p1->TradeDate.getValue(),p2->TradeDate.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InstrumentID.getValue(),p2->InstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByTradeDateInstrumentIDIndexForSGEDeferRate=0;
#endif
CSGEDeferRate *CSGEDeferRateFactory::findByTradeDateInstrumentIDIndex( const CReadOnlyTradingDayType&  TradeDate,  const CReadOnlyInstrumentIDType&  InstrumentID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByTradeDateInstrumentIDIndex of CSGEDeferRate while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByTradeDateInstrumentIDIndexForSGEDeferRate++;
#endif
	CAVLNode *pNode;
	compareObject.TradeDate=TradeDate.getValue();
	compareObject.InstrumentID=InstrumentID.getValue();
	pNode=pTradeDateInstrumentIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CSGEDeferRate *)(pNode->pObject);
}

CSGEDeferRate *CSGEDeferRateFactory::findByPK( const CReadOnlyTradingDayType&  TradeDate,  const CReadOnlyInstrumentIDType&  InstrumentID)
{
	return findByTradeDateInstrumentIDIndex(TradeDate, InstrumentID);
}
	
CSGEDeferRate *CSGEDeferRateFactory::findByPK(CWriteableSGEDeferRate *pSGEDeferRate)
{
	return findByPK(
		pSGEDeferRate->TradeDate
		,
		pSGEDeferRate->InstrumentID
		);
}

bool CSGEDeferRateFactory::retrieveByPK(CWriteableSGEDeferRate *pSGEDeferRate)
{
	CSGEDeferRate *pOriginalSGEDeferRate;
	pOriginalSGEDeferRate=findByPK(pSGEDeferRate);
	if (pOriginalSGEDeferRate==NULL)
	{
		return false;
	}
	retrieve(pOriginalSGEDeferRate,pSGEDeferRate);
	return true;
}

CSGEDeferRate *CSGEDeferRateFactory::addByPK(CWriteableSGEDeferRate *pSGEDeferRate, CTransaction *pTransaction)
{
	CSGEDeferRate *pOriginalSGEDeferRate;
	pOriginalSGEDeferRate=findByPK(pSGEDeferRate);
	if (pOriginalSGEDeferRate != NULL)
	{
		return NULL;
	}
	return add(pSGEDeferRate,pTransaction);
}

bool CSGEDeferRateFactory::updateByPK(CWriteableSGEDeferRate *pSGEDeferRate, CTransaction *pTransaction, bool updateIndex)
{
	CSGEDeferRate *pOriginalSGEDeferRate;
	pOriginalSGEDeferRate=findByPK(pSGEDeferRate);
	if (pOriginalSGEDeferRate==NULL)
	{
		return false;
	}
	pSGEDeferRate->calAllHash();
	update(pOriginalSGEDeferRate,pSGEDeferRate,pTransaction,updateIndex);
	return true;
}

bool CSGEDeferRateFactory::removeByPK(CWriteableSGEDeferRate *pSGEDeferRate, CTransaction *pTransaction)
{
	CSGEDeferRate *pOriginalSGEDeferRate;
	pOriginalSGEDeferRate=findByPK(pSGEDeferRate);
	if (pOriginalSGEDeferRate==NULL)
	{
		return false;
	}
	remove(pOriginalSGEDeferRate,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int multiFindAllByInstrumentIDForSGEDeferRate=0;
#endif

CSGEDeferRate *CSGEDeferRateFactory::startFindAllByInstrumentID( const CReadOnlyInstrumentIDType& InstrumentID)
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAllByInstrumentID of CSGEDeferRate while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAllByInstrumentID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAllByInstrumentID();
	}

	///记录所有的查询值
	queryInstrumentIDInSearchAllByInstrumentID= InstrumentID.getValue();

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAllByInstrumentID=(CSGEDeferRate *)(pMem->getFirst());
	
	if (pLastFoundInSearchAllByInstrumentID==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAllByInstrumentID来寻找下一个
	
	///返回找到的结果
	return pLastFoundInSearchAllByInstrumentID;
}

CSGEDeferRate *CSGEDeferRateFactory::findNextAllByInstrumentID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAllByInstrumentID==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAllByInstrumentID=(CSGEDeferRate *)(pMem->getNext());
		if (pLastFoundInSearchAllByInstrumentID==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		///返回找到的结果
		return pLastFoundInSearchAllByInstrumentID;
	}
}

void CSGEDeferRateFactory::endFindAllByInstrumentID(void)
{
	pLastFoundInSearchAllByInstrumentID=NULL;
}


#ifdef COUNT_SEARCH
int multiFindAllForSGEDeferRate=0;
#endif

CSGEDeferRate *CSGEDeferRateFactory::startFindAll()
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAll of CSGEDeferRate while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAll!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAll();
	}

	///记录所有的查询值

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAll=(CSGEDeferRate *)(pMem->getFirst());
	
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAll来寻找下一个
	
	///返回找到的结果
	return pLastFoundInSearchAll;
}

CSGEDeferRate *CSGEDeferRateFactory::findNextAll(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAll=(CSGEDeferRate *)(pMem->getNext());
		if (pLastFoundInSearchAll==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		///返回找到的结果
		return pLastFoundInSearchAll;
	}
}

void CSGEDeferRateFactory::endFindAll(void)
{
	pLastFoundInSearchAll=NULL;
}

int compareForBrkExIDInsInvIndexinInvestorTradingRight(const void *pV1, const void *pV2)
{
	CInvestorTradingRight *p1,*p2;
	p1=(CInvestorTradingRight *)pV1;
	p2=(CInvestorTradingRight *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InstrumentID.getValue(),p2->InstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InvestorID.getValue(),p2->InvestorID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->ProductClass.getValue(),p2->ProductClass.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByBrkExIDInsInvForInvestorTradingRight=0;
#endif
CInvestorTradingRight *CInvestorTradingRightFactory::findByBrkExIDInsInv( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyProductClassType&  ProductClass)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrkExIDInsInv of CInvestorTradingRight while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByBrkExIDInsInvForInvestorTradingRight++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.InstrumentID=InstrumentID.getValue();
	compareObject.InvestorID=InvestorID.getValue();
	compareObject.ProductClass=ProductClass.getValue();
	pNode=pBrkExIDInsInvIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CInvestorTradingRight *)(pNode->pObject);
}

CInvestorTradingRight *CInvestorTradingRightFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyProductClassType&  ProductClass)
{
	return findByBrkExIDInsInv(BrokerID, ExchangeID, InstrumentID, InvestorID, ProductClass);
}
	
CInvestorTradingRight *CInvestorTradingRightFactory::findByPK(CWriteableInvestorTradingRight *pInvestorTradingRight)
{
	return findByPK(
		pInvestorTradingRight->BrokerID
		,
		pInvestorTradingRight->ExchangeID
		,
		pInvestorTradingRight->InstrumentID
		,
		pInvestorTradingRight->InvestorID
		,
		pInvestorTradingRight->ProductClass
		);
}

bool CInvestorTradingRightFactory::retrieveByPK(CWriteableInvestorTradingRight *pInvestorTradingRight)
{
	CInvestorTradingRight *pOriginalInvestorTradingRight;
	pOriginalInvestorTradingRight=findByPK(pInvestorTradingRight);
	if (pOriginalInvestorTradingRight==NULL)
	{
		return false;
	}
	retrieve(pOriginalInvestorTradingRight,pInvestorTradingRight);
	return true;
}

CInvestorTradingRight *CInvestorTradingRightFactory::addByPK(CWriteableInvestorTradingRight *pInvestorTradingRight, CTransaction *pTransaction)
{
	CInvestorTradingRight *pOriginalInvestorTradingRight;
	pOriginalInvestorTradingRight=findByPK(pInvestorTradingRight);
	if (pOriginalInvestorTradingRight != NULL)
	{
		return NULL;
	}
	return add(pInvestorTradingRight,pTransaction);
}

bool CInvestorTradingRightFactory::updateByPK(CWriteableInvestorTradingRight *pInvestorTradingRight, CTransaction *pTransaction, bool updateIndex)
{
	CInvestorTradingRight *pOriginalInvestorTradingRight;
	pOriginalInvestorTradingRight=findByPK(pInvestorTradingRight);
	if (pOriginalInvestorTradingRight==NULL)
	{
		return false;
	}
	pInvestorTradingRight->calAllHash();
	update(pOriginalInvestorTradingRight,pInvestorTradingRight,pTransaction,updateIndex);
	return true;
}

bool CInvestorTradingRightFactory::removeByPK(CWriteableInvestorTradingRight *pInvestorTradingRight, CTransaction *pTransaction)
{
	CInvestorTradingRight *pOriginalInvestorTradingRight;
	pOriginalInvestorTradingRight=findByPK(pInvestorTradingRight);
	if (pOriginalInvestorTradingRight==NULL)
	{
		return false;
	}
	remove(pOriginalInvestorTradingRight,pTransaction);
	return true;
}


int compareForUserIPMaskIndexinUserIP(const void *pV1, const void *pV2)
{
	CUserIP *p1,*p2;
	p1=(CUserIP *)pV1;
	p2=(CUserIP *)pV2;
	switch (compare(p1->BrokerID.getValue(),p2->BrokerID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->UserID.getValue(),p2->UserID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->IPAddress.getValue(),p2->IPAddress.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->IPMask.getValue(),p2->IPMask.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int multiFindByUserIDForUserIP=0;
#endif

CUserIP *CUserIPFactory::startFindByUserID( const CReadOnlyBrokerIDType& BrokerID,  const CReadOnlyUserIDType& UserID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindByUserID of CUserIP while run level < 0");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchByUserID!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindByUserID();
	}

	///记录所有的查询值
	queryBrokerIDInSearchByUserID= BrokerID.getValue();
	queryUserIDInSearchByUserID= UserID.getValue();

#ifdef COUNT_SEARCH
	multiFindByUserIDForUserIP++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	CUserIP *theUserIP;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.UserID=UserID.getValue();
	compareObject.IPAddress="";
	compareObject.IPMask="";
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearchByUserID=pUserIPMaskIndex->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearchByUserID==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	theUserIP=(CUserIP *)(pLastFoundInSearchByUserID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theUserIP->BrokerID.getValue(),BrokerID.getValue()))
	{
		pLastFoundInSearchByUserID=NULL;
		return NULL;
	}
	if (compare(theUserIP->UserID.getValue(),UserID.getValue()))
	{
		pLastFoundInSearchByUserID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theUserIP;
}

CUserIP *CUserIPFactory::findNextByUserID(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchByUserID==NULL)
	{
		return NULL;
	}

#ifdef COUNT_SEARCH
	multiFindByUserIDForUserIP++;
#endif
	CUserIP *theUserIP;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearchByUserID=pUserIPMaskIndex->getNextNode(pLastFoundInSearchByUserID);
	if (pLastFoundInSearchByUserID==NULL)
	{
		return NULL;
	}

	theUserIP=(CUserIP *)(pLastFoundInSearchByUserID->pObject);
	
	///如果有一个条件不满足，则失败返回
	if (compare(theUserIP->BrokerID,queryBrokerIDInSearchByUserID))
	{
		pLastFoundInSearchByUserID=NULL;
		return NULL;
	}
	if (compare(theUserIP->UserID,queryUserIDInSearchByUserID))
	{
		pLastFoundInSearchByUserID=NULL;
		return NULL;
	}

	///返回找到的结果
	return theUserIP;
}

void CUserIPFactory::endFindByUserID(void)
{
	pLastFoundInSearchByUserID=NULL;
}


#ifdef COUNT_SEARCH
int findByUserIPAndMaskForUserIP=0;
#endif
CUserIP *CUserIPFactory::findByUserIPAndMask( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyIPAddressType&  IPAddress,  const CReadOnlyIPAddressType&  IPMask)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByUserIPAndMask of CUserIP while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByUserIPAndMaskForUserIP++;
#endif
	CAVLNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.UserID=UserID.getValue();
	compareObject.IPAddress=IPAddress.getValue();
	compareObject.IPMask=IPMask.getValue();
	pNode=pUserIPMaskIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CUserIP *)(pNode->pObject);
}

CUserIP *CUserIPFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyIPAddressType&  IPAddress,  const CReadOnlyIPAddressType&  IPMask)
{
	return findByUserIPAndMask(BrokerID, UserID, IPAddress, IPMask);
}
	
CUserIP *CUserIPFactory::findByPK(CWriteableUserIP *pUserIP)
{
	return findByPK(
		pUserIP->BrokerID
		,
		pUserIP->UserID
		,
		pUserIP->IPAddress
		,
		pUserIP->IPMask
		);
}

bool CUserIPFactory::retrieveByPK(CWriteableUserIP *pUserIP)
{
	CUserIP *pOriginalUserIP;
	pOriginalUserIP=findByPK(pUserIP);
	if (pOriginalUserIP==NULL)
	{
		return false;
	}
	retrieve(pOriginalUserIP,pUserIP);
	return true;
}

CUserIP *CUserIPFactory::addByPK(CWriteableUserIP *pUserIP, CTransaction *pTransaction)
{
	CUserIP *pOriginalUserIP;
	pOriginalUserIP=findByPK(pUserIP);
	if (pOriginalUserIP != NULL)
	{
		return NULL;
	}
	return add(pUserIP,pTransaction);
}

bool CUserIPFactory::updateByPK(CWriteableUserIP *pUserIP, CTransaction *pTransaction, bool updateIndex)
{
	CUserIP *pOriginalUserIP;
	pOriginalUserIP=findByPK(pUserIP);
	if (pOriginalUserIP==NULL)
	{
		return false;
	}
	pUserIP->calAllHash();
	update(pOriginalUserIP,pUserIP,pTransaction,updateIndex);
	return true;
}

bool CUserIPFactory::removeByPK(CWriteableUserIP *pUserIP, CTransaction *pTransaction)
{
	CUserIP *pOriginalUserIP;
	pOriginalUserIP=findByPK(pUserIP);
	if (pOriginalUserIP==NULL)
	{
		return false;
	}
	remove(pOriginalUserIP,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int findByBrkIDExIDIstIDVstIDForInvestorOptionFee=0;
#endif
CInvestorOptionFee *CInvestorOptionFeeFactory::findByBrkIDExIDIstIDVstID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByBrkIDExIDIstIDVstID of CInvestorOptionFee while run level < 0");
	}
	CHashIndexNode *pNode;
	compareObject.BrokerID=BrokerID.getValue();
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.InstrumentID=InstrumentID.getValue();
	compareObject.InvestorID=InvestorID.getValue();
	
	compareObject.calHashBrkIDExIDIstIDVstID();
	for (pNode=pBrkIDExIDIstIDVstIDHashIndex->searchFirstEqual(compareObject.HashBrkIDExIDIstIDVstID);
		pNode!=NULL;
		pNode=pBrkIDExIDIstIDVstIDHashIndex->searchNextEqual(pNode))
	{
		if (((CInvestorOptionFee *)(pNode->pObject))->HashBrkIDExIDIstIDVstID != compareObject.HashBrkIDExIDIstIDVstID)
		{
			continue;
		}
		if (compare(((CInvestorOptionFee *)(pNode->pObject))->BrokerID.getValue(),BrokerID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CInvestorOptionFee *)(pNode->pObject))->ExchangeID.getValue(),ExchangeID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CInvestorOptionFee *)(pNode->pObject))->InstrumentID.getValue(),InstrumentID.getValue())!=0)
		{
			continue;
		}
		if (compare(((CInvestorOptionFee *)(pNode->pObject))->InvestorID.getValue(),InvestorID.getValue())!=0)
		{
			continue;
		}
		return (CInvestorOptionFee *)(pNode->pObject);
	}
	return NULL;
}

CInvestorOptionFee *CInvestorOptionFeeFactory::findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID)
{
	return findByBrkIDExIDIstIDVstID(BrokerID, ExchangeID, InstrumentID, InvestorID);
}
	
CInvestorOptionFee *CInvestorOptionFeeFactory::findByPK(CWriteableInvestorOptionFee *pInvestorOptionFee)
{
	return findByPK(
		pInvestorOptionFee->BrokerID
		,
		pInvestorOptionFee->ExchangeID
		,
		pInvestorOptionFee->InstrumentID
		,
		pInvestorOptionFee->InvestorID
		);
}

bool CInvestorOptionFeeFactory::retrieveByPK(CWriteableInvestorOptionFee *pInvestorOptionFee)
{
	CInvestorOptionFee *pOriginalInvestorOptionFee;
	pOriginalInvestorOptionFee=findByPK(pInvestorOptionFee);
	if (pOriginalInvestorOptionFee==NULL)
	{
		return false;
	}
	retrieve(pOriginalInvestorOptionFee,pInvestorOptionFee);
	return true;
}

CInvestorOptionFee *CInvestorOptionFeeFactory::addByPK(CWriteableInvestorOptionFee *pInvestorOptionFee, CTransaction *pTransaction)
{
	CInvestorOptionFee *pOriginalInvestorOptionFee;
	pOriginalInvestorOptionFee=findByPK(pInvestorOptionFee);
	if (pOriginalInvestorOptionFee != NULL)
	{
		return NULL;
	}
	return add(pInvestorOptionFee,pTransaction);
}

bool CInvestorOptionFeeFactory::updateByPK(CWriteableInvestorOptionFee *pInvestorOptionFee, CTransaction *pTransaction, bool updateIndex)
{
	CInvestorOptionFee *pOriginalInvestorOptionFee;
	pOriginalInvestorOptionFee=findByPK(pInvestorOptionFee);
	if (pOriginalInvestorOptionFee==NULL)
	{
		return false;
	}
	pInvestorOptionFee->calAllHash();
	update(pOriginalInvestorOptionFee,pInvestorOptionFee,pTransaction,updateIndex);
	return true;
}

bool CInvestorOptionFeeFactory::removeByPK(CWriteableInvestorOptionFee *pInvestorOptionFee, CTransaction *pTransaction)
{
	CInvestorOptionFee *pOriginalInvestorOptionFee;
	pOriginalInvestorOptionFee=findByPK(pInvestorOptionFee);
	if (pOriginalInvestorOptionFee==NULL)
	{
		return false;
	}
	remove(pOriginalInvestorOptionFee,pTransaction);
	return true;
}


int compareForExchangeIDAndInstrumentIDIndexinMarketData(const void *pV1, const void *pV2)
{
	CMarketData *p1,*p2;
	p1=(CMarketData *)pV1;
	p2=(CMarketData *)pV2;
	switch (compare(p1->ExchangeID.getValue(),p2->ExchangeID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	switch (compare(p1->InstrumentID.getValue(),p2->InstrumentID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findByExchangeIDAndInstrumentIDForMarketData=0;
#endif
CMarketData *CMarketDataFactory::findByExchangeIDAndInstrumentID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findByExchangeIDAndInstrumentID of CMarketData while run level < 0");
	}
#ifdef COUNT_SEARCH
	findByExchangeIDAndInstrumentIDForMarketData++;
#endif
	CAVLNode *pNode;
	compareObject.ExchangeID=ExchangeID.getValue();
	compareObject.InstrumentID=InstrumentID.getValue();
	pNode=pExchangeIDAndInstrumentIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CMarketData *)(pNode->pObject);
}

CMarketData *CMarketDataFactory::findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID)
{
	return findByExchangeIDAndInstrumentID(ExchangeID, InstrumentID);
}
	
CMarketData *CMarketDataFactory::findByPK(CWriteableMarketData *pMarketData)
{
	return findByPK(
		pMarketData->ExchangeID
		,
		pMarketData->InstrumentID
		);
}

bool CMarketDataFactory::retrieveByPK(CWriteableMarketData *pMarketData)
{
	CMarketData *pOriginalMarketData;
	pOriginalMarketData=findByPK(pMarketData);
	if (pOriginalMarketData==NULL)
	{
		return false;
	}
	retrieve(pOriginalMarketData,pMarketData);
	return true;
}

CMarketData *CMarketDataFactory::addByPK(CWriteableMarketData *pMarketData, CTransaction *pTransaction)
{
	CMarketData *pOriginalMarketData;
	pOriginalMarketData=findByPK(pMarketData);
	if (pOriginalMarketData != NULL)
	{
		return NULL;
	}
	return add(pMarketData,pTransaction);
}

bool CMarketDataFactory::updateByPK(CWriteableMarketData *pMarketData, CTransaction *pTransaction, bool updateIndex)
{
	CMarketData *pOriginalMarketData;
	pOriginalMarketData=findByPK(pMarketData);
	if (pOriginalMarketData==NULL)
	{
		return false;
	}
	pMarketData->calAllHash();
	update(pOriginalMarketData,pMarketData,pTransaction,updateIndex);
	return true;
}

bool CMarketDataFactory::removeByPK(CWriteableMarketData *pMarketData, CTransaction *pTransaction)
{
	CMarketData *pOriginalMarketData;
	pOriginalMarketData=findByPK(pMarketData);
	if (pOriginalMarketData==NULL)
	{
		return false;
	}
	remove(pOriginalMarketData,pTransaction);
	return true;
}



#ifdef COUNT_SEARCH
int multiFindAllForMarketData=0;
#endif

CMarketData *CMarketDataFactory::startFindAll()
{
	if (runLevel<1)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFindAll of CMarketData while run level < 1");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearchAll!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFindAll();
	}

	///记录所有的查询值

	///如果一个对象也没有，就返回失败
	pLastFoundInSearchAll=(CMarketData *)(pMem->getFirst());
	
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNextAll来寻找下一个
	
	///返回找到的结果
	return pLastFoundInSearchAll;
}

CMarketData *CMarketDataFactory::findNextAll(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearchAll==NULL)
	{
		return NULL;
	}

	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearchAll=(CMarketData *)(pMem->getNext());
		if (pLastFoundInSearchAll==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		///返回找到的结果
		return pLastFoundInSearchAll;
	}
}

void CMarketDataFactory::endFindAll(void)
{
	pLastFoundInSearchAll=NULL;
}

int compareForSystemIDIndexinSystemInfo(const void *pV1, const void *pV2)
{
	CSystemInfo *p1,*p2;
	p1=(CSystemInfo *)pV1;
	p2=(CSystemInfo *)pV2;
	switch (compare(p1->SystemID.getValue(),p2->SystemID.getValue()))
	{
	case 1:
		return 1;
	case -1:
		return -1;
	case 0:
	default:
		break;
	}
	return 0;
}

#ifdef COUNT_SEARCH
int findBySystemIDForSystemInfo=0;
#endif
CSystemInfo *CSystemInfoFactory::findBySystemID( const CReadOnlySystemIDType&  SystemID)
{
	if (runLevel<0)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use findBySystemID of CSystemInfo while run level < 0");
	}
#ifdef COUNT_SEARCH
	findBySystemIDForSystemInfo++;
#endif
	CAVLNode *pNode;
	compareObject.SystemID=SystemID.getValue();
	pNode=pSystemIDIndex->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	return (CSystemInfo *)(pNode->pObject);
}

CSystemInfo *CSystemInfoFactory::findByPK( const CReadOnlySystemIDType&  SystemID)
{
	return findBySystemID(SystemID);
}
	
CSystemInfo *CSystemInfoFactory::findByPK(CWriteableSystemInfo *pSystemInfo)
{
	return findByPK(
		pSystemInfo->SystemID
		);
}

bool CSystemInfoFactory::retrieveByPK(CWriteableSystemInfo *pSystemInfo)
{
	CSystemInfo *pOriginalSystemInfo;
	pOriginalSystemInfo=findByPK(pSystemInfo);
	if (pOriginalSystemInfo==NULL)
	{
		return false;
	}
	retrieve(pOriginalSystemInfo,pSystemInfo);
	return true;
}

CSystemInfo *CSystemInfoFactory::addByPK(CWriteableSystemInfo *pSystemInfo, CTransaction *pTransaction)
{
	CSystemInfo *pOriginalSystemInfo;
	pOriginalSystemInfo=findByPK(pSystemInfo);
	if (pOriginalSystemInfo != NULL)
	{
		return NULL;
	}
	return add(pSystemInfo,pTransaction);
}

bool CSystemInfoFactory::updateByPK(CWriteableSystemInfo *pSystemInfo, CTransaction *pTransaction, bool updateIndex)
{
	CSystemInfo *pOriginalSystemInfo;
	pOriginalSystemInfo=findByPK(pSystemInfo);
	if (pOriginalSystemInfo==NULL)
	{
		return false;
	}
	pSystemInfo->calAllHash();
	update(pOriginalSystemInfo,pSystemInfo,pTransaction,updateIndex);
	return true;
}

bool CSystemInfoFactory::removeByPK(CWriteableSystemInfo *pSystemInfo, CTransaction *pTransaction)
{
	CSystemInfo *pOriginalSystemInfo;
	pOriginalSystemInfo=findByPK(pSystemInfo);
	if (pOriginalSystemInfo==NULL)
	{
		return false;
	}
	remove(pOriginalSystemInfo,pTransaction);
	return true;
}


#ifdef COUNT_SEARCH
void showAllSearchCount(void)
{
	printf("\n");
	if (findByTradingdayForDataSyncStatus !=0)
	{
		printf("\tfindByTradingdayForDataSyncStatus:%d\n",findByTradingdayForDataSyncStatus);
	}
	if (findByTradingDayForSystemStatus !=0)
	{
		printf("\tfindByTradingDayForSystemStatus:%d\n",findByTradingDayForSystemStatus);
	}
	if (findByExchangeIDAndOrderSysIDForOrder !=0)
	{
		printf("\tfindByExchangeIDAndOrderSysIDForOrder:%d\n",findByExchangeIDAndOrderSysIDForOrder);
	}
	if (findByUserIDAndUserOrderLocalIDForOrder !=0)
	{
		printf("\tfindByUserIDAndUserOrderLocalIDForOrder:%d\n",findByUserIDAndUserOrderLocalIDForOrder);
	}
	if (multiFindAllByUserIDForOrder !=0)
	{
		printf("\tmultiFindAllByUserIDForOrder:%d\n",multiFindAllByUserIDForOrder);
	}
	if (multiFindAllByInvestorIDForOrder !=0)
	{
		printf("\tmultiFindAllByInvestorIDForOrder:%d\n",multiFindAllByInvestorIDForOrder);
	}
	if (multiFindAllByExchIDInvIDUserIDForOrder !=0)
	{
		printf("\tmultiFindAllByExchIDInvIDUserIDForOrder:%d\n",multiFindAllByExchIDInvIDUserIDForOrder);
	}
	if (multiFindAllByExchIDInstruIDUserIDForOrder !=0)
	{
		printf("\tmultiFindAllByExchIDInstruIDUserIDForOrder:%d\n",multiFindAllByExchIDInstruIDUserIDForOrder);
	}
	if (multiFindAllForOrder !=0)
	{
		printf("\tmultiFindAllForOrder:%d\n",multiFindAllForOrder);
	}
	if (findByExchangeIDTradeIDOrderSysIDForTrade !=0)
	{
		printf("\tfindByExchangeIDTradeIDOrderSysIDForTrade:%d\n",findByExchangeIDTradeIDOrderSysIDForTrade);
	}
	if (multiFindByExchangeIDAndTradeIDForTrade !=0)
	{
		printf("\tmultiFindByExchangeIDAndTradeIDForTrade:%d\n",multiFindByExchangeIDAndTradeIDForTrade);
	}
	if (multiFindAllByExchIDInvIDUserIDForTrade !=0)
	{
		printf("\tmultiFindAllByExchIDInvIDUserIDForTrade:%d\n",multiFindAllByExchIDInvIDUserIDForTrade);
	}
	if (multiFindAllByInvestorIDForTrade !=0)
	{
		printf("\tmultiFindAllByInvestorIDForTrade:%d\n",multiFindAllByInvestorIDForTrade);
	}
	if (multiFindAllByExchIDInstruIDUserIDForTrade !=0)
	{
		printf("\tmultiFindAllByExchIDInstruIDUserIDForTrade:%d\n",multiFindAllByExchIDInstruIDUserIDForTrade);
	}
	if (multiFindAllForTrade !=0)
	{
		printf("\tmultiFindAllForTrade:%d\n",multiFindAllForTrade);
	}
	if (findByAPIIDAndOrderLocalIDForPreOrder !=0)
	{
		printf("\tfindByAPIIDAndOrderLocalIDForPreOrder:%d\n",findByAPIIDAndOrderLocalIDForPreOrder);
	}
	if (findByUserIDAndUserOrderLocalIDForPreOrder !=0)
	{
		printf("\tfindByUserIDAndUserOrderLocalIDForPreOrder:%d\n",findByUserIDAndUserOrderLocalIDForPreOrder);
	}
	if (multiFindByAPIIDForPreOrder !=0)
	{
		printf("\tmultiFindByAPIIDForPreOrder:%d\n",multiFindByAPIIDForPreOrder);
	}
	if (findByALLFldsForIndexPreOrder !=0)
	{
		printf("\tfindByALLFldsForIndexPreOrder:%d\n",findByALLFldsForIndexPreOrder);
	}
	if (findByBrkIDExIDInvIDInsDirHedForInvestorPosition !=0)
	{
		printf("\tfindByBrkIDExIDInvIDInsDirHedForInvestorPosition:%d\n",findByBrkIDExIDInvIDInsDirHedForInvestorPosition);
	}
	if (multiFindAllByExIDAndInstrumentIDForInvestorPosition !=0)
	{
		printf("\tmultiFindAllByExIDAndInstrumentIDForInvestorPosition:%d\n",multiFindAllByExIDAndInstrumentIDForInvestorPosition);
	}
	if (multiFindByInvestorIDForInvestorPosition !=0)
	{
		printf("\tmultiFindByInvestorIDForInvestorPosition:%d\n",multiFindByInvestorIDForInvestorPosition);
	}
	if (multiFindAllByBrokerIDForInvestorPosition !=0)
	{
		printf("\tmultiFindAllByBrokerIDForInvestorPosition:%d\n",multiFindAllByBrokerIDForInvestorPosition);
	}
	if (multiFindAllByInstrumentIDForInvestorPosition !=0)
	{
		printf("\tmultiFindAllByInstrumentIDForInvestorPosition:%d\n",multiFindAllByInstrumentIDForInvestorPosition);
	}
	if (multiFindAllByExchangeIDForInvestorPosition !=0)
	{
		printf("\tmultiFindAllByExchangeIDForInvestorPosition:%d\n",multiFindAllByExchangeIDForInvestorPosition);
	}
	if (multiFindAllByInvestorIDAndInstrumentIDForInvestorPosition !=0)
	{
		printf("\tmultiFindAllByInvestorIDAndInstrumentIDForInvestorPosition:%d\n",multiFindAllByInvestorIDAndInstrumentIDForInvestorPosition);
	}
	if (multiFindAllForInvestorPosition !=0)
	{
		printf("\tmultiFindAllForInvestorPosition:%d\n",multiFindAllForInvestorPosition);
	}
	if (findByBrokerIDAccountIDForInvestorAccount !=0)
	{
		printf("\tfindByBrokerIDAccountIDForInvestorAccount:%d\n",findByBrokerIDAccountIDForInvestorAccount);
	}
	if (multiFindAllByInvestorIDForInvestorAccount !=0)
	{
		printf("\tmultiFindAllByInvestorIDForInvestorAccount:%d\n",multiFindAllByInvestorIDForInvestorAccount);
	}
	if (findByBrokerIDInvestorIDForInvestorAccount !=0)
	{
		printf("\tfindByBrokerIDInvestorIDForInvestorAccount:%d\n",findByBrokerIDInvestorIDForInvestorAccount);
	}
	if (multiFindAllByBrokerIDForInvestorAccount !=0)
	{
		printf("\tmultiFindAllByBrokerIDForInvestorAccount:%d\n",multiFindAllByBrokerIDForInvestorAccount);
	}
	if (multiFindAllForInvestorAccount !=0)
	{
		printf("\tmultiFindAllForInvestorAccount:%d\n",multiFindAllForInvestorAccount);
	}
	if (findByBrokerIDAccountSeqNoForInvestorAccountDeposit !=0)
	{
		printf("\tfindByBrokerIDAccountSeqNoForInvestorAccountDeposit:%d\n",findByBrokerIDAccountSeqNoForInvestorAccountDeposit);
	}
	if (findByExchangeIDForExchange !=0)
	{
		printf("\tfindByExchangeIDForExchange:%d\n",findByExchangeIDForExchange);
	}
	if (multiFindStartByExchangeIDForExchange !=0)
	{
		printf("\tmultiFindStartByExchangeIDForExchange:%d\n",multiFindStartByExchangeIDForExchange);
	}
	if (multiFindAllForExchange !=0)
	{
		printf("\tmultiFindAllForExchange:%d\n",multiFindAllForExchange);
	}
	if (findByBrokerIDExchangeIDSeatIDForSeat !=0)
	{
		printf("\tfindByBrokerIDExchangeIDSeatIDForSeat:%d\n",findByBrokerIDExchangeIDSeatIDForSeat);
	}
	if (findByExchangeIDParticipantIDSeatIDForSeat !=0)
	{
		printf("\tfindByExchangeIDParticipantIDSeatIDForSeat:%d\n",findByExchangeIDParticipantIDSeatIDForSeat);
	}
	if (findByExchangeIDAndInstrumentIDForInstrument !=0)
	{
		printf("\tfindByExchangeIDAndInstrumentIDForInstrument:%d\n",findByExchangeIDAndInstrumentIDForInstrument);
	}
	if (multiFindAllByInstrumentIDForInstrument !=0)
	{
		printf("\tmultiFindAllByInstrumentIDForInstrument:%d\n",multiFindAllByInstrumentIDForInstrument);
	}
	if (multiFindAllByExchangeIDForInstrument !=0)
	{
		printf("\tmultiFindAllByExchangeIDForInstrument:%d\n",multiFindAllByExchangeIDForInstrument);
	}
	if (multiFindAllByProductIDForInstrument !=0)
	{
		printf("\tmultiFindAllByProductIDForInstrument:%d\n",multiFindAllByProductIDForInstrument);
	}
	if (multiFindAllForInstrument !=0)
	{
		printf("\tmultiFindAllForInstrument:%d\n",multiFindAllForInstrument);
	}
	if (findByExchangeIDAndArbiInstrumentIDAndSingelInstrumentIDForCmbInstrumentDetail !=0)
	{
		printf("\tfindByExchangeIDAndArbiInstrumentIDAndSingelInstrumentIDForCmbInstrumentDetail:%d\n",findByExchangeIDAndArbiInstrumentIDAndSingelInstrumentIDForCmbInstrumentDetail);
	}
	if (multiFindAllByExchangeIDAndArbiInstrumentIDForCmbInstrumentDetail !=0)
	{
		printf("\tmultiFindAllByExchangeIDAndArbiInstrumentIDForCmbInstrumentDetail:%d\n",multiFindAllByExchangeIDAndArbiInstrumentIDForCmbInstrumentDetail);
	}
	if (multiFindAllByExchangeIDAndSingleInstrumentIDForCmbInstrumentDetail !=0)
	{
		printf("\tmultiFindAllByExchangeIDAndSingleInstrumentIDForCmbInstrumentDetail:%d\n",multiFindAllByExchangeIDAndSingleInstrumentIDForCmbInstrumentDetail);
	}
	if (findByBrokerIDExchangeIDPartClientIDForClientTradingID !=0)
	{
		printf("\tfindByBrokerIDExchangeIDPartClientIDForClientTradingID:%d\n",findByBrokerIDExchangeIDPartClientIDForClientTradingID);
	}
	if (findByBrkIDExIDInvIDHdgFlgForClientTradingID !=0)
	{
		printf("\tfindByBrkIDExIDInvIDHdgFlgForClientTradingID:%d\n",findByBrkIDExIDInvIDHdgFlgForClientTradingID);
	}
	if (multiFindByBrokerIDInvestorIDForClientTradingID !=0)
	{
		printf("\tmultiFindByBrokerIDInvestorIDForClientTradingID:%d\n",multiFindByBrokerIDInvestorIDForClientTradingID);
	}
	if (multiFindAllByBrokerIDForClientTradingID !=0)
	{
		printf("\tmultiFindAllByBrokerIDForClientTradingID:%d\n",multiFindAllByBrokerIDForClientTradingID);
	}
	if (multiFindAllForClientTradingID !=0)
	{
		printf("\tmultiFindAllForClientTradingID:%d\n",multiFindAllForClientTradingID);
	}
	if (findByBrokerIDInvestorIDForInvestor !=0)
	{
		printf("\tfindByBrokerIDInvestorIDForInvestor:%d\n",findByBrokerIDInvestorIDForInvestor);
	}
	if (multiFindByInvestorIDForInvestor !=0)
	{
		printf("\tmultiFindByInvestorIDForInvestor:%d\n",multiFindByInvestorIDForInvestor);
	}
	if (findByBrokerIDClientIDForInvestorMargin !=0)
	{
		printf("\tfindByBrokerIDClientIDForInvestorMargin:%d\n",findByBrokerIDClientIDForInvestorMargin);
	}
	if (findByBrkIDExIDIstIDVstIDHdgForInvestorMargin !=0)
	{
		printf("\tfindByBrkIDExIDIstIDVstIDHdgForInvestorMargin:%d\n",findByBrkIDExIDIstIDVstIDHdgForInvestorMargin);
	}
	if (multiFindByBrkIDExIDIstIDVstIDForInvestorMargin !=0)
	{
		printf("\tmultiFindByBrkIDExIDIstIDVstIDForInvestorMargin:%d\n",multiFindByBrkIDExIDIstIDVstIDForInvestorMargin);
	}
	if (multiFindByInstrumentIDForInvestorMargin !=0)
	{
		printf("\tmultiFindByInstrumentIDForInvestorMargin:%d\n",multiFindByInstrumentIDForInvestorMargin);
	}
	if (multiFindByBrokerIDForInvestorMargin !=0)
	{
		printf("\tmultiFindByBrokerIDForInvestorMargin:%d\n",multiFindByBrokerIDForInvestorMargin);
	}
	if (multiFindAllForInvestorMargin !=0)
	{
		printf("\tmultiFindAllForInvestorMargin:%d\n",multiFindAllForInvestorMargin);
	}
	if (findByBrkIDExIDIstIDVstIDHdgForInvestorFee !=0)
	{
		printf("\tfindByBrkIDExIDIstIDVstIDHdgForInvestorFee:%d\n",findByBrkIDExIDIstIDVstIDHdgForInvestorFee);
	}
	if (multiFindByInstrumentIDForInvestorFee !=0)
	{
		printf("\tmultiFindByInstrumentIDForInvestorFee:%d\n",multiFindByInstrumentIDForInvestorFee);
	}
	if (multiFindByBrokerIDForInvestorFee !=0)
	{
		printf("\tmultiFindByBrokerIDForInvestorFee:%d\n",multiFindByBrokerIDForInvestorFee);
	}
	if (multiFindAllForInvestorFee !=0)
	{
		printf("\tmultiFindAllForInvestorFee:%d\n",multiFindAllForInvestorFee);
	}
	if (findByBrokerIDUserIDForUser !=0)
	{
		printf("\tfindByBrokerIDUserIDForUser:%d\n",findByBrokerIDUserIDForUser);
	}
	if (multiFindStartByUserIDForUser !=0)
	{
		printf("\tmultiFindStartByUserIDForUser:%d\n",multiFindStartByUserIDForUser);
	}
	if (findByBrokerIDUserIDInvestorIDForUserInvestor !=0)
	{
		printf("\tfindByBrokerIDUserIDInvestorIDForUserInvestor:%d\n",findByBrokerIDUserIDInvestorIDForUserInvestor);
	}
	if (multiFindByBrokerIDInvestorIDForUserInvestor !=0)
	{
		printf("\tmultiFindByBrokerIDInvestorIDForUserInvestor:%d\n",multiFindByBrokerIDInvestorIDForUserInvestor);
	}
	if (multiFindAllByUserIDForUserInvestor !=0)
	{
		printf("\tmultiFindAllByUserIDForUserInvestor:%d\n",multiFindAllByUserIDForUserInvestor);
	}
	if (multiFindAllByBrokerIDUserIDForUserInvestor !=0)
	{
		printf("\tmultiFindAllByBrokerIDUserIDForUserInvestor:%d\n",multiFindAllByBrokerIDUserIDForUserInvestor);
	}
	if (multiFindAllByBrokerIDForUserInvestor !=0)
	{
		printf("\tmultiFindAllByBrokerIDForUserInvestor:%d\n",multiFindAllByBrokerIDForUserInvestor);
	}
	if (multiFindAllForUserInvestor !=0)
	{
		printf("\tmultiFindAllForUserInvestor:%d\n",multiFindAllForUserInvestor);
	}
	if (findByOrderUserIDForOrderInsertFailed !=0)
	{
		printf("\tfindByOrderUserIDForOrderInsertFailed:%d\n",findByOrderUserIDForOrderInsertFailed);
	}
	if (findByOrderLocalIDForOrderInsertFailed !=0)
	{
		printf("\tfindByOrderLocalIDForOrderInsertFailed:%d\n",findByOrderLocalIDForOrderInsertFailed);
	}
	if (findByExchangeIDAndOrderSysIDForOrderInsertFailed !=0)
	{
		printf("\tfindByExchangeIDAndOrderSysIDForOrderInsertFailed:%d\n",findByExchangeIDAndOrderSysIDForOrderInsertFailed);
	}
	if (multiFindAllByExchIDInvIDUserIDForOrderInsertFailed !=0)
	{
		printf("\tmultiFindAllByExchIDInvIDUserIDForOrderInsertFailed:%d\n",multiFindAllByExchIDInvIDUserIDForOrderInsertFailed);
	}
	if (multiFindAllByExchIDInstruIDUserIDForOrderInsertFailed !=0)
	{
		printf("\tmultiFindAllByExchIDInstruIDUserIDForOrderInsertFailed:%d\n",multiFindAllByExchIDInstruIDUserIDForOrderInsertFailed);
	}
	if (multiFindAllForOrderInsertFailed !=0)
	{
		printf("\tmultiFindAllForOrderInsertFailed:%d\n",multiFindAllForOrderInsertFailed);
	}
	if (findByExchangeIDSeatIDAndOrderLocalIDForOrderInsertFailed !=0)
	{
		printf("\tfindByExchangeIDSeatIDAndOrderLocalIDForOrderInsertFailed:%d\n",findByExchangeIDSeatIDAndOrderLocalIDForOrderInsertFailed);
	}
	if (findByBrkExIDInsUserInvForUserTradingRight !=0)
	{
		printf("\tfindByBrkExIDInsUserInvForUserTradingRight:%d\n",findByBrkExIDInsUserInvForUserTradingRight);
	}
	if (findBySessionIDFrontIDForUserSession !=0)
	{
		printf("\tfindBySessionIDFrontIDForUserSession:%d\n",findBySessionIDFrontIDForUserSession);
	}
	if (findByBrokerIDUserIDSFIDForUserSession !=0)
	{
		printf("\tfindByBrokerIDUserIDSFIDForUserSession:%d\n",findByBrokerIDUserIDSFIDForUserSession);
	}
	if (multiFindByUserIDForUserSession !=0)
	{
		printf("\tmultiFindByUserIDForUserSession:%d\n",multiFindByUserIDForUserSession);
	}
	if (findByFrontIDSessionIDForMaxLocalID !=0)
	{
		printf("\tfindByFrontIDSessionIDForMaxLocalID:%d\n",findByFrontIDSessionIDForMaxLocalID);
	}
	if (findByBrokerIDUserIDLocalIDForBrkUserIDLocalID !=0)
	{
		printf("\tfindByBrokerIDUserIDLocalIDForBrkUserIDLocalID:%d\n",findByBrokerIDUserIDLocalIDForBrkUserIDLocalID);
	}
	if (findByBrokerClientAndInsGroupForPartClientInsGroupPosition !=0)
	{
		printf("\tfindByBrokerClientAndInsGroupForPartClientInsGroupPosition:%d\n",findByBrokerClientAndInsGroupForPartClientInsGroupPosition);
	}
	if (findByBrokerClientAndInsGroupForClientMarginCombType !=0)
	{
		printf("\tfindByBrokerClientAndInsGroupForClientMarginCombType:%d\n",findByBrokerClientAndInsGroupForClientMarginCombType);
	}
	if (findByBrokerInstrumentIDForInstrumentGroup !=0)
	{
		printf("\tfindByBrokerInstrumentIDForInstrumentGroup:%d\n",findByBrokerInstrumentIDForInstrumentGroup);
	}
	if (findByTradeDateInstrumentIDIndexForSGEDeferRate !=0)
	{
		printf("\tfindByTradeDateInstrumentIDIndexForSGEDeferRate:%d\n",findByTradeDateInstrumentIDIndexForSGEDeferRate);
	}
	if (multiFindAllByInstrumentIDForSGEDeferRate !=0)
	{
		printf("\tmultiFindAllByInstrumentIDForSGEDeferRate:%d\n",multiFindAllByInstrumentIDForSGEDeferRate);
	}
	if (multiFindAllForSGEDeferRate !=0)
	{
		printf("\tmultiFindAllForSGEDeferRate:%d\n",multiFindAllForSGEDeferRate);
	}
	if (findByBrkExIDInsInvForInvestorTradingRight !=0)
	{
		printf("\tfindByBrkExIDInsInvForInvestorTradingRight:%d\n",findByBrkExIDInsInvForInvestorTradingRight);
	}
	if (multiFindByUserIDForUserIP !=0)
	{
		printf("\tmultiFindByUserIDForUserIP:%d\n",multiFindByUserIDForUserIP);
	}
	if (findByUserIPAndMaskForUserIP !=0)
	{
		printf("\tfindByUserIPAndMaskForUserIP:%d\n",findByUserIPAndMaskForUserIP);
	}
	if (findByBrkIDExIDIstIDVstIDForInvestorOptionFee !=0)
	{
		printf("\tfindByBrkIDExIDIstIDVstIDForInvestorOptionFee:%d\n",findByBrkIDExIDIstIDVstIDForInvestorOptionFee);
	}
	if (findByExchangeIDAndInstrumentIDForMarketData !=0)
	{
		printf("\tfindByExchangeIDAndInstrumentIDForMarketData:%d\n",findByExchangeIDAndInstrumentIDForMarketData);
	}
	if (multiFindAllForMarketData !=0)
	{
		printf("\tmultiFindAllForMarketData:%d\n",multiFindAllForMarketData);
	}
	if (findBySystemIDForSystemInfo !=0)
	{
		printf("\tfindBySystemIDForSystemInfo:%d\n",findBySystemIDForSystemInfo);
	}
}

void initAllSearchCount(void)
{
	findByTradingdayForDataSyncStatus=0;
	findByTradingDayForSystemStatus=0;
	findByExchangeIDAndOrderSysIDForOrder=0;
	findByUserIDAndUserOrderLocalIDForOrder=0;
	multiFindAllByUserIDForOrder=0;
	multiFindAllByInvestorIDForOrder=0;
	multiFindAllByExchIDInvIDUserIDForOrder=0;
	multiFindAllByExchIDInstruIDUserIDForOrder=0;
	multiFindAllForOrder=0;
	findByExchangeIDTradeIDOrderSysIDForTrade=0;
	multiFindByExchangeIDAndTradeIDForTrade=0;
	multiFindAllByExchIDInvIDUserIDForTrade=0;
	multiFindAllByInvestorIDForTrade=0;
	multiFindAllByExchIDInstruIDUserIDForTrade=0;
	multiFindAllForTrade=0;
	findByAPIIDAndOrderLocalIDForPreOrder=0;
	findByUserIDAndUserOrderLocalIDForPreOrder=0;
	multiFindByAPIIDForPreOrder=0;
	findByALLFldsForIndexPreOrder=0;
	findByBrkIDExIDInvIDInsDirHedForInvestorPosition=0;
	multiFindAllByExIDAndInstrumentIDForInvestorPosition=0;
	multiFindByInvestorIDForInvestorPosition=0;
	multiFindAllByBrokerIDForInvestorPosition=0;
	multiFindAllByInstrumentIDForInvestorPosition=0;
	multiFindAllByExchangeIDForInvestorPosition=0;
	multiFindAllByInvestorIDAndInstrumentIDForInvestorPosition=0;
	multiFindAllForInvestorPosition=0;
	findByBrokerIDAccountIDForInvestorAccount=0;
	multiFindAllByInvestorIDForInvestorAccount=0;
	findByBrokerIDInvestorIDForInvestorAccount=0;
	multiFindAllByBrokerIDForInvestorAccount=0;
	multiFindAllForInvestorAccount=0;
	findByBrokerIDAccountSeqNoForInvestorAccountDeposit=0;
	findByExchangeIDForExchange=0;
	multiFindStartByExchangeIDForExchange=0;
	multiFindAllForExchange=0;
	findByBrokerIDExchangeIDSeatIDForSeat=0;
	findByExchangeIDParticipantIDSeatIDForSeat=0;
	findByExchangeIDAndInstrumentIDForInstrument=0;
	multiFindAllByInstrumentIDForInstrument=0;
	multiFindAllByExchangeIDForInstrument=0;
	multiFindAllByProductIDForInstrument=0;
	multiFindAllForInstrument=0;
	findByExchangeIDAndArbiInstrumentIDAndSingelInstrumentIDForCmbInstrumentDetail=0;
	multiFindAllByExchangeIDAndArbiInstrumentIDForCmbInstrumentDetail=0;
	multiFindAllByExchangeIDAndSingleInstrumentIDForCmbInstrumentDetail=0;
	findByBrokerIDExchangeIDPartClientIDForClientTradingID=0;
	findByBrkIDExIDInvIDHdgFlgForClientTradingID=0;
	multiFindByBrokerIDInvestorIDForClientTradingID=0;
	multiFindAllByBrokerIDForClientTradingID=0;
	multiFindAllForClientTradingID=0;
	findByBrokerIDInvestorIDForInvestor=0;
	multiFindByInvestorIDForInvestor=0;
	findByBrokerIDClientIDForInvestorMargin=0;
	findByBrkIDExIDIstIDVstIDHdgForInvestorMargin=0;
	multiFindByBrkIDExIDIstIDVstIDForInvestorMargin=0;
	multiFindByInstrumentIDForInvestorMargin=0;
	multiFindByBrokerIDForInvestorMargin=0;
	multiFindAllForInvestorMargin=0;
	findByBrkIDExIDIstIDVstIDHdgForInvestorFee=0;
	multiFindByInstrumentIDForInvestorFee=0;
	multiFindByBrokerIDForInvestorFee=0;
	multiFindAllForInvestorFee=0;
	findByBrokerIDUserIDForUser=0;
	multiFindStartByUserIDForUser=0;
	findByBrokerIDUserIDInvestorIDForUserInvestor=0;
	multiFindByBrokerIDInvestorIDForUserInvestor=0;
	multiFindAllByUserIDForUserInvestor=0;
	multiFindAllByBrokerIDUserIDForUserInvestor=0;
	multiFindAllByBrokerIDForUserInvestor=0;
	multiFindAllForUserInvestor=0;
	findByOrderUserIDForOrderInsertFailed=0;
	findByOrderLocalIDForOrderInsertFailed=0;
	findByExchangeIDAndOrderSysIDForOrderInsertFailed=0;
	multiFindAllByExchIDInvIDUserIDForOrderInsertFailed=0;
	multiFindAllByExchIDInstruIDUserIDForOrderInsertFailed=0;
	multiFindAllForOrderInsertFailed=0;
	findByExchangeIDSeatIDAndOrderLocalIDForOrderInsertFailed=0;
	findByBrkExIDInsUserInvForUserTradingRight=0;
	findBySessionIDFrontIDForUserSession=0;
	findByBrokerIDUserIDSFIDForUserSession=0;
	multiFindByUserIDForUserSession=0;
	findByFrontIDSessionIDForMaxLocalID=0;
	findByBrokerIDUserIDLocalIDForBrkUserIDLocalID=0;
	findByBrokerClientAndInsGroupForPartClientInsGroupPosition=0;
	findByBrokerClientAndInsGroupForClientMarginCombType=0;
	findByBrokerInstrumentIDForInstrumentGroup=0;
	findByTradeDateInstrumentIDIndexForSGEDeferRate=0;
	multiFindAllByInstrumentIDForSGEDeferRate=0;
	multiFindAllForSGEDeferRate=0;
	findByBrkExIDInsInvForInvestorTradingRight=0;
	multiFindByUserIDForUserIP=0;
	findByUserIPAndMaskForUserIP=0;
	findByBrkIDExIDIstIDVstIDForInvestorOptionFee=0;
	findByExchangeIDAndInstrumentIDForMarketData=0;
	multiFindAllForMarketData=0;
	findBySystemIDForSystemInfo=0;
}
#endif
