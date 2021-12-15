/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file COrderInsertRules.h
///@briefʵ������COrderInsertRules
///@history 
///20060113	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#include "HandleTrade.h"
#include "tradingTools.h"
#include "BaseExchApi.h"

CHandleTrade::CHandleTrade(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult)
:CRuleHandleBase(pDB,pErrorEngine,pConfig,pTradeResult)
{
	m_pConfig      = pConfig;
	m_pPubMessage  = new CXTPPackage();
	m_pPubMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE, XTPHLEN);
	m_pErrorEngine = pErrorEngine;
}

bool CHandleTrade::HandleRtnTrade(COrder *pOrder,CTradeField *pTradeField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
   bool bSuccess = false;   

   CWriteableTrade      theWritableTrade;
   theWritableTrade.init();
   CopyTradeEntity(&theWritableTrade,pTradeField);

   CWriteableOrder   theWriteableOrder ;
   m_pDB->m_OrderFactory->retrieve(pOrder,&theWriteableOrder);
   // �ڳɽ��ر��и����ѳɽ����� longqy 2014-03-19
	theWriteableOrder.VolumeTraded = pOrder->VolumeTraded + pTradeField->TradeVolume;
	theWriteableOrder.VolumeRemain = theWriteableOrder.Volume - theWriteableOrder.VolumeTraded;
	if (pOrder->OrderStatus == OS_Canceled)
	{
		theWriteableOrder.CancleVolume = theWriteableOrder.VolumeRemain;
	}

	//α��rtn
	if (pTradeField->IsForgeRtn)
	{
		if (theWriteableOrder.VolumeRemain ==0)
		{
			theWriteableOrder.OrderStatus = OS_AllTraded;
		}
		else
		{
			theWriteableOrder.OrderStatus = OS_PartTradedQueueing;
		}
	}
 
	CMoneyField theMoneyField;
	memset(&theMoneyField,0,sizeof(CMoneyField));
	bSuccess = m_pMoneyPosition->TradeMoneyUpdate(&theWriteableOrder,&theWritableTrade,&theMoneyField,pTransaction);
	if(false == bSuccess)
	{
		REPORT_EVENT(LOG_CRITICAL, "Error Calculating FrozenToMargin ","In Line %d of File %s.\n",__LINE__,__FILE__);   
		return false;
	}
   
   m_pDB->m_OrderFactory->update(pOrder,&theWriteableOrder,pTransaction); 
   
   //���벹�ϣ���Ȼqkernelû�������Ϣ������ʧ��
   theWritableTrade.UserID=pOrder->UserID;   
   theWritableTrade.OrderUserID= pOrder->OrderUserID;
   theWritableTrade.UserOrderLocalID=pOrder->UserOrderLocalID;
   theWritableTrade.OrderLocalID=pOrder->OrderLocalID;
   theWritableTrade.AccountID = pOrder->AccountID;
   m_pDB->m_TradeFactory->add(&theWritableTrade,pTransaction);

#ifdef APP_QQUERY
   //�ֲָ���
   bSuccess = m_pMoneyPosition->TradePositionUpdate(pOrder,&theWritableTrade,&theMoneyField,pTransaction);
   if(false == bSuccess)
   {
	   REPORT_EVENT(LOG_CRITICAL, "Error Update Position ","In Line %d of File %s.\n",__LINE__,__FILE__);   
	   return false;
   }
#endif


   return true;    
}


bool CHandleTrade::FieldTransform(CTradeField *pTradeField, COrder* pOrder)
{
   bool bSuccess = false;
   pTradeField->AccountID         =  pOrder->AccountID;
   pTradeField->BrokerID          =  pOrder->BrokerID;
   pTradeField->UserID			  =  pOrder->UserID;
   pTradeField->InvestorID        =  pOrder->InvestorID;
   pTradeField->UserOrderLocalID  =  pOrder->UserOrderLocalID;
   pTradeField->OrderLocalID      =  pOrder->OrderLocalID;

   
   //���OnRtnTrade��HedgeFlagʼ��Ϊ1�Ĵ���  added by liumeng  2014-08-07
   pTradeField->HedgeFlag         =  pOrder->HedgeFlag;
   //���pats�ɽ�û�����Ϳ�ƽ��־ added by chengm 2016-01-04
   pTradeField->OffsetFlag		  =  pOrder->OffsetFlag;
   pTradeField->Direction		  =  pOrder->Direction;
   return true;
}

bool CHandleTrade::HandleRtnCmbTrade(COrderField *pRtnOrder,CTradeField *pTrade,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	return true;
}