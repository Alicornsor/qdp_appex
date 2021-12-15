/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file COrderInsertRules.h
///@briefʵ������COrderInsertRules
///@history 
///20060113	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#include "HandleOrderAction.h"

CHandleOrderAction::CHandleOrderAction(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult)
:CRuleHandleBase(pDB,pErrorEngine,pConfig,pTradeResult)
{
	m_pConfig        = pConfig;
	m_pErrorEngine   = pErrorEngine;
	m_pBaseCheck     = new CBaseCheck(pDB,pErrorEngine);
}

CHandleOrderAction::~CHandleOrderAction()
{
}

bool CHandleOrderAction::HandleReqOrderAction(CWriteableOrderAction *pOrderAction,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	return m_pBaseCheck->OrderActionCheck(pOrderAction,sessionRef,pTransaction);
}

bool CHandleOrderAction::HandleRspOrderAction(CWriteableOrderAction *pOrderAction,COrderActionField* pActField,CRspInfoField*  pRspInfoField, COrder* pOrder,const TSessionRef &sessionRef,CTransaction *pTransaction)
{	
	//����ʧ�ܣ�����UserID��ǰ��
	if (pRspInfoField->ErrorID!=0 )
	{
	   if(pOrder != NULL)
	   {
		   pActField->BrokerID     = pOrder->BrokerID;
	       pActField->InvestorID   = pOrder->InvestorID;
	       pActField->OrderLocalID = pOrder->OrderLocalID;
	       pActField->UserID       = pOrder->UserID;
	   }
	   else
	   {
          REPORT_EVENT(LOG_CRITICAL,"CHandleOrderAction","OrderAction Cannot Find Order");
	   }
	   return true;
	}
		
	if (pOrder==NULL)
	{
		//Ϊ��ֹ��ExchangeManagerα���ԭ���ٴ�����һ��
		pOrder=pOrderAction->linkOrder(m_pDB->m_OrderFactory);
		if (pOrder==NULL)
		{
			m_pErrorEngine->reportError(ERROR_ORDER_NOT_FOUND);
			return false;
		}		
	}
	CopyFieldOrderActionFromOrder(pActField,pOrder);
	if (pOrder->OrderStatus==OS_Canceled)
	{
		return true;
	}
	//�޸Ķ���״̬
	CWriteableOrder theOrder;
	theOrder.init();
	m_pDB->m_OrderFactory->retrieve(pOrder,&theOrder);
	theOrder.OrderStatus=OS_Canceled;//�޸Ķ���״̬

	//�����ⶳ�ʽ�
	if (!m_pMoneyPosition->MoneyUnFrozen(pOrder,pTransaction))
	{
		REPORT_EVENT(LOG_CRITICAL,"MoneyUnFrozen","unfrozen money error in order cancel");
		return false;
	}
	//�����ֲֽⶳ
	if (!m_pMoneyPosition->PositionUnFrozen(pOrder,pTransaction))
	{
		REPORT_EVENT(LOG_CRITICAL,"PositionUnFrozen","unfrozen position error in order cancel");
		return false;
	}
	/* �޸��������ڲ��ֳɽ��������ʱ�ѱ����Ķ���ֵȫ���㣬�����ɽ��ٽⶳʱ���Ͳ����ⶳ 
	longqy 2013-12-19 */
	theOrder.FrozenMargin = 0.0;
	if (theOrder.TimeCondition!=TC_IOC)
	{
		theOrder.FrozenFee = 0.0;
	}
	theOrder.FrozenPremium = 0.0;
	//chengm 20161215  �����ɹ�ʱ����CancleVolume  volumeremain��volumetraded�ڳɽ������
//	theOrder.CancleVolume = theOrder.Volume - theOrder.VolumeTraded;
	
	if (pActField->IsForgeRtn)
	{
		theOrder.CancleVolume = theOrder.Volume - theOrder.VolumeTraded;
		theOrder.VolumeRemain = theOrder.CancleVolume;
	}
	m_pDB->m_OrderFactory->update(pOrder,&theOrder,pTransaction);
	return true;
}

void CHandleOrderAction::CopyFieldOrderActionFromOrder(COrderActionField* pActField,COrder* pOrder)
{
   pActField->BrokerID               = pOrder->BrokerID;
   pActField->InvestorID             = pOrder->InvestorID;
   pActField->UserID                 = pOrder->UserID;
   pActField->UserCustom             = pOrder->UserCustom;
}

CHandleFutureOrderAction::CHandleFutureOrderAction(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult)
:CHandleOrderAction(pDB, pErrorEngine,pConfig,pTradeResult)
{
   m_pMoneyPosition = new CFutureMoneyPosition(pDB,pErrorEngine,pConfig);	
}

CHandleFutureOrderAction::~CHandleFutureOrderAction()
{

}