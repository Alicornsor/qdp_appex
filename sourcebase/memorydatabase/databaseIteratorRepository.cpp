/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseIteratorRepository.cpp
///@brief	实现了若干个内存数据库的iterator库，以便各种查询
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "databaseIteratorRepository.h"

CDataSyncStatus *CDataSyncStatusSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CDataSyncStatusSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CDataSyncStatusSingleIterator::UpdateCurrent(CWriteableDataSyncStatus * pDataSyncStatus,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pDataSyncStatus,pTransaction,updateIndex);
}

CDataSyncStatus *CDataSyncStatusFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CDataSyncStatus *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CDataSyncStatusFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CDataSyncStatusFilter::UpdateCurrent(CWriteableDataSyncStatus * pDataSyncStatus,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pDataSyncStatus,pTransaction,updateIndex);
}

CDataSyncStatus *CDataSyncStatusLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CDataSyncStatus *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CDataSyncStatusLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CDataSyncStatusLinkIterator::UpdateCurrent(CWriteableDataSyncStatus * pDataSyncStatus,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pDataSyncStatus,pTransaction,updateIndex);
}

CSystemStatus *CSystemStatusSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CSystemStatusSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CSystemStatusSingleIterator::UpdateCurrent(CWriteableSystemStatus * pSystemStatus,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pSystemStatus,pTransaction,updateIndex);
}

CSystemStatus *CSystemStatusFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CSystemStatus *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CSystemStatusFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CSystemStatusFilter::UpdateCurrent(CWriteableSystemStatus * pSystemStatus,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pSystemStatus,pTransaction,updateIndex);
}

CSystemStatus *CSystemStatusLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CSystemStatus *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CSystemStatusLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CSystemStatusLinkIterator::UpdateCurrent(CWriteableSystemStatus * pSystemStatus,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pSystemStatus,pTransaction,updateIndex);
}

COrderAction *COrderActionSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void COrderActionSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void COrderActionSingleIterator::UpdateCurrent(CWriteableOrderAction * pOrderAction,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pOrderAction,pTransaction,updateIndex);
}

COrderAction *COrderActionFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		COrderAction *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void COrderActionFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void COrderActionFilter::UpdateCurrent(CWriteableOrderAction * pOrderAction,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pOrderAction,pTransaction,updateIndex);
}

COrderAction *COrderActionLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			COrderAction *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void COrderActionLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void COrderActionLinkIterator::UpdateCurrent(CWriteableOrderAction * pOrderAction,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pOrderAction,pTransaction,updateIndex);
}

COrder *COrderOfOrderActionIterator::next(void)
{
	COrderAction *pOrderAction;
	while ((pOrderAction=m_baseIterator->next())!=NULL)
	{
		m_current=pOrderAction->getOrder();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void COrderOfOrderActionIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void COrderOfOrderActionIterator::UpdateCurrent(CWriteableOrder *pOrder,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pOrder,pTransaction,updateIndex);
}

CPreOrder *CPreOrderOfOrderActionIterator::next(void)
{
	COrderAction *pOrderAction;
	while ((pOrderAction=m_baseIterator->next())!=NULL)
	{
		m_current=pOrderAction->getPreOrder();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CPreOrderOfOrderActionIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CPreOrderOfOrderActionIterator::UpdateCurrent(CWriteablePreOrder *pPreOrder,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pPreOrder,pTransaction,updateIndex);
}

COrder *COrderSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void COrderSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void COrderSingleIterator::UpdateCurrent(CWriteableOrder * pOrder,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pOrder,pTransaction,updateIndex);
}

COrder *COrderFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		COrder *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void COrderFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void COrderFilter::UpdateCurrent(CWriteableOrder * pOrder,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pOrder,pTransaction,updateIndex);
}

COrder *COrderLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			COrder *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void COrderLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void COrderLinkIterator::UpdateCurrent(CWriteableOrder * pOrder,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pOrder,pTransaction,updateIndex);
}

CInvestor *CInvestorOfOrderIterator::next(void)
{
	COrder *pOrder;
	while ((pOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pOrder->getInvestor();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorOfOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorOfOrderIterator::UpdateCurrent(CWriteableInvestor *pInvestor,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestor,pTransaction,updateIndex);
}

CClientTradingID *CClientTradingIDOfOrderIterator::next(void)
{
	COrder *pOrder;
	while ((pOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pOrder->getClientTradingID();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CClientTradingIDOfOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CClientTradingIDOfOrderIterator::UpdateCurrent(CWriteableClientTradingID *pClientTradingID,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pClientTradingID,pTransaction,updateIndex);
}

CInvestorAccount *CInvestorAccountOfOrderIterator::next(void)
{
	COrder *pOrder;
	while ((pOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pOrder->getInvestorAccount();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorAccountOfOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorAccountOfOrderIterator::UpdateCurrent(CWriteableInvestorAccount *pInvestorAccount,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorAccount,pTransaction,updateIndex);
}

CInvestorPosition *CInvestorPositionOfOrderIterator::next(void)
{
	COrder *pOrder;
	while ((pOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pOrder->getInvestorPosition();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorPositionOfOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorPositionOfOrderIterator::UpdateCurrent(CWriteableInvestorPosition *pInvestorPosition,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorPosition,pTransaction,updateIndex);
}

CInstrument *CInstrumentOfOrderIterator::next(void)
{
	COrder *pOrder;
	while ((pOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pOrder->getInstrument();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInstrumentOfOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInstrumentOfOrderIterator::UpdateCurrent(CWriteableInstrument *pInstrument,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInstrument,pTransaction,updateIndex);
}

CInvestorMargin *CInvestorMarginOfOrderIterator::next(void)
{
	COrder *pOrder;
	while ((pOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pOrder->getInvestorMargin();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorMarginOfOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorMarginOfOrderIterator::UpdateCurrent(CWriteableInvestorMargin *pInvestorMargin,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorMargin,pTransaction,updateIndex);
}

CInvestorFee *CInvestorFeeOfOrderIterator::next(void)
{
	COrder *pOrder;
	while ((pOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pOrder->getInvestorFee();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorFeeOfOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorFeeOfOrderIterator::UpdateCurrent(CWriteableInvestorFee *pInvestorFee,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorFee,pTransaction,updateIndex);
}

CInvestorOptionFee *CInvestorOptionFeeOfOrderIterator::next(void)
{
	COrder *pOrder;
	while ((pOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pOrder->getInvestorOptionFee();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorOptionFeeOfOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorOptionFeeOfOrderIterator::UpdateCurrent(CWriteableInvestorOptionFee *pInvestorOptionFee,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorOptionFee,pTransaction,updateIndex);
}

CPartClientInsGroupPosition *CClientGroupPositionOfOrderIterator::next(void)
{
	COrder *pOrder;
	while ((pOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pOrder->getClientGroupPosition();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CClientGroupPositionOfOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CClientGroupPositionOfOrderIterator::UpdateCurrent(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pPartClientInsGroupPosition,pTransaction,updateIndex);
}

CTrade *CTradeSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CTradeSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CTradeSingleIterator::UpdateCurrent(CWriteableTrade * pTrade,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pTrade,pTransaction,updateIndex);
}

CTrade *CTradeFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CTrade *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CTradeFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CTradeFilter::UpdateCurrent(CWriteableTrade * pTrade,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pTrade,pTransaction,updateIndex);
}

CTrade *CTradeLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CTrade *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CTradeLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CTradeLinkIterator::UpdateCurrent(CWriteableTrade * pTrade,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pTrade,pTransaction,updateIndex);
}

CPreOrder *CPreOrderSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CPreOrderSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CPreOrderSingleIterator::UpdateCurrent(CWriteablePreOrder * pPreOrder,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pPreOrder,pTransaction,updateIndex);
}

CPreOrder *CPreOrderFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CPreOrder *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CPreOrderFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CPreOrderFilter::UpdateCurrent(CWriteablePreOrder * pPreOrder,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pPreOrder,pTransaction,updateIndex);
}

CPreOrder *CPreOrderLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CPreOrder *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CPreOrderLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CPreOrderLinkIterator::UpdateCurrent(CWriteablePreOrder * pPreOrder,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pPreOrder,pTransaction,updateIndex);
}

CInvestor *CInvestorOfPreOrderIterator::next(void)
{
	CPreOrder *pPreOrder;
	while ((pPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pPreOrder->getInvestor();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorOfPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorOfPreOrderIterator::UpdateCurrent(CWriteableInvestor *pInvestor,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestor,pTransaction,updateIndex);
}

CClientTradingID *CClientTradingIDOfPreOrderIterator::next(void)
{
	CPreOrder *pPreOrder;
	while ((pPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pPreOrder->getClientTradingID();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CClientTradingIDOfPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CClientTradingIDOfPreOrderIterator::UpdateCurrent(CWriteableClientTradingID *pClientTradingID,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pClientTradingID,pTransaction,updateIndex);
}

CInvestorAccount *CInvestorAccountOfPreOrderIterator::next(void)
{
	CPreOrder *pPreOrder;
	while ((pPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pPreOrder->getInvestorAccount();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorAccountOfPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorAccountOfPreOrderIterator::UpdateCurrent(CWriteableInvestorAccount *pInvestorAccount,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorAccount,pTransaction,updateIndex);
}

CInvestorPosition *CInvestorPositionOfPreOrderIterator::next(void)
{
	CPreOrder *pPreOrder;
	while ((pPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pPreOrder->getInvestorPosition();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorPositionOfPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorPositionOfPreOrderIterator::UpdateCurrent(CWriteableInvestorPosition *pInvestorPosition,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorPosition,pTransaction,updateIndex);
}

CInstrument *CInstrumentOfPreOrderIterator::next(void)
{
	CPreOrder *pPreOrder;
	while ((pPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pPreOrder->getInstrument();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInstrumentOfPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInstrumentOfPreOrderIterator::UpdateCurrent(CWriteableInstrument *pInstrument,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInstrument,pTransaction,updateIndex);
}

CInvestorMargin *CInvestorMarginOfPreOrderIterator::next(void)
{
	CPreOrder *pPreOrder;
	while ((pPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pPreOrder->getInvestorMargin();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorMarginOfPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorMarginOfPreOrderIterator::UpdateCurrent(CWriteableInvestorMargin *pInvestorMargin,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorMargin,pTransaction,updateIndex);
}

CInvestorFee *CInvestorFeeOfPreOrderIterator::next(void)
{
	CPreOrder *pPreOrder;
	while ((pPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pPreOrder->getInvestorFee();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorFeeOfPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorFeeOfPreOrderIterator::UpdateCurrent(CWriteableInvestorFee *pInvestorFee,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorFee,pTransaction,updateIndex);
}

CInvestorOptionFee *CInvestorOptionFeeOfPreOrderIterator::next(void)
{
	CPreOrder *pPreOrder;
	while ((pPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pPreOrder->getInvestorOptionFee();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorOptionFeeOfPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorOptionFeeOfPreOrderIterator::UpdateCurrent(CWriteableInvestorOptionFee *pInvestorOptionFee,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorOptionFee,pTransaction,updateIndex);
}

CPartClientInsGroupPosition *CClientGroupPositionOfPreOrderIterator::next(void)
{
	CPreOrder *pPreOrder;
	while ((pPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pPreOrder->getClientGroupPosition();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CClientGroupPositionOfPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CClientGroupPositionOfPreOrderIterator::UpdateCurrent(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pPartClientInsGroupPosition,pTransaction,updateIndex);
}

CIndexPreOrder *CIndexPreOrderSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CIndexPreOrderSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CIndexPreOrderSingleIterator::UpdateCurrent(CWriteableIndexPreOrder * pIndexPreOrder,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pIndexPreOrder,pTransaction,updateIndex);
}

CIndexPreOrder *CIndexPreOrderFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CIndexPreOrder *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CIndexPreOrderFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CIndexPreOrderFilter::UpdateCurrent(CWriteableIndexPreOrder * pIndexPreOrder,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pIndexPreOrder,pTransaction,updateIndex);
}

CIndexPreOrder *CIndexPreOrderLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CIndexPreOrder *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CIndexPreOrderLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CIndexPreOrderLinkIterator::UpdateCurrent(CWriteableIndexPreOrder * pIndexPreOrder,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pIndexPreOrder,pTransaction,updateIndex);
}

CInvestor *CInvestorOfIndexPreOrderIterator::next(void)
{
	CIndexPreOrder *pIndexPreOrder;
	while ((pIndexPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pIndexPreOrder->getInvestor();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorOfIndexPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorOfIndexPreOrderIterator::UpdateCurrent(CWriteableInvestor *pInvestor,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestor,pTransaction,updateIndex);
}

CClientTradingID *CClientTradingIDOfIndexPreOrderIterator::next(void)
{
	CIndexPreOrder *pIndexPreOrder;
	while ((pIndexPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pIndexPreOrder->getClientTradingID();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CClientTradingIDOfIndexPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CClientTradingIDOfIndexPreOrderIterator::UpdateCurrent(CWriteableClientTradingID *pClientTradingID,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pClientTradingID,pTransaction,updateIndex);
}

CInvestorAccount *CInvestorAccountOfIndexPreOrderIterator::next(void)
{
	CIndexPreOrder *pIndexPreOrder;
	while ((pIndexPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pIndexPreOrder->getInvestorAccount();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorAccountOfIndexPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorAccountOfIndexPreOrderIterator::UpdateCurrent(CWriteableInvestorAccount *pInvestorAccount,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorAccount,pTransaction,updateIndex);
}

CInstrument *CInstrumentOfIndexPreOrderIterator::next(void)
{
	CIndexPreOrder *pIndexPreOrder;
	while ((pIndexPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pIndexPreOrder->getInstrument();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInstrumentOfIndexPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInstrumentOfIndexPreOrderIterator::UpdateCurrent(CWriteableInstrument *pInstrument,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInstrument,pTransaction,updateIndex);
}

CInvestorMargin *CInvestorMarginOfIndexPreOrderIterator::next(void)
{
	CIndexPreOrder *pIndexPreOrder;
	while ((pIndexPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pIndexPreOrder->getInvestorMargin();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorMarginOfIndexPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorMarginOfIndexPreOrderIterator::UpdateCurrent(CWriteableInvestorMargin *pInvestorMargin,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorMargin,pTransaction,updateIndex);
}

CInvestorFee *CInvestorFeeOfIndexPreOrderIterator::next(void)
{
	CIndexPreOrder *pIndexPreOrder;
	while ((pIndexPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pIndexPreOrder->getInvestorFee();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorFeeOfIndexPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorFeeOfIndexPreOrderIterator::UpdateCurrent(CWriteableInvestorFee *pInvestorFee,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorFee,pTransaction,updateIndex);
}

CPartClientInsGroupPosition *CClientGroupPositionOfIndexPreOrderIterator::next(void)
{
	CIndexPreOrder *pIndexPreOrder;
	while ((pIndexPreOrder=m_baseIterator->next())!=NULL)
	{
		m_current=pIndexPreOrder->getClientGroupPosition();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CClientGroupPositionOfIndexPreOrderIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CClientGroupPositionOfIndexPreOrderIterator::UpdateCurrent(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pPartClientInsGroupPosition,pTransaction,updateIndex);
}

CInvestorPosition *CInvestorPositionSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CInvestorPositionSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CInvestorPositionSingleIterator::UpdateCurrent(CWriteableInvestorPosition * pInvestorPosition,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pInvestorPosition,pTransaction,updateIndex);
}

CInvestorPosition *CInvestorPositionFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CInvestorPosition *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CInvestorPositionFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CInvestorPositionFilter::UpdateCurrent(CWriteableInvestorPosition * pInvestorPosition,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pInvestorPosition,pTransaction,updateIndex);
}

CInvestorPosition *CInvestorPositionLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CInvestorPosition *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CInvestorPositionLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CInvestorPositionLinkIterator::UpdateCurrent(CWriteableInvestorPosition * pInvestorPosition,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pInvestorPosition,pTransaction,updateIndex);
}

CInvestorAccount *CInvestorAccountSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CInvestorAccountSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CInvestorAccountSingleIterator::UpdateCurrent(CWriteableInvestorAccount * pInvestorAccount,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pInvestorAccount,pTransaction,updateIndex);
}

CInvestorAccount *CInvestorAccountFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CInvestorAccount *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CInvestorAccountFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CInvestorAccountFilter::UpdateCurrent(CWriteableInvestorAccount * pInvestorAccount,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pInvestorAccount,pTransaction,updateIndex);
}

CInvestorAccount *CInvestorAccountLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CInvestorAccount *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CInvestorAccountLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CInvestorAccountLinkIterator::UpdateCurrent(CWriteableInvestorAccount * pInvestorAccount,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pInvestorAccount,pTransaction,updateIndex);
}

CInvestorAccountDeposit *CInvestorAccountDepositSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CInvestorAccountDepositSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CInvestorAccountDepositSingleIterator::UpdateCurrent(CWriteableInvestorAccountDeposit * pInvestorAccountDeposit,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pInvestorAccountDeposit,pTransaction,updateIndex);
}

CInvestorAccountDeposit *CInvestorAccountDepositFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CInvestorAccountDeposit *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CInvestorAccountDepositFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CInvestorAccountDepositFilter::UpdateCurrent(CWriteableInvestorAccountDeposit * pInvestorAccountDeposit,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pInvestorAccountDeposit,pTransaction,updateIndex);
}

CInvestorAccountDeposit *CInvestorAccountDepositLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CInvestorAccountDeposit *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CInvestorAccountDepositLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CInvestorAccountDepositLinkIterator::UpdateCurrent(CWriteableInvestorAccountDeposit * pInvestorAccountDeposit,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pInvestorAccountDeposit,pTransaction,updateIndex);
}

CExchange *CExchangeSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CExchangeSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CExchangeSingleIterator::UpdateCurrent(CWriteableExchange * pExchange,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pExchange,pTransaction,updateIndex);
}

CExchange *CExchangeFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CExchange *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CExchangeFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CExchangeFilter::UpdateCurrent(CWriteableExchange * pExchange,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pExchange,pTransaction,updateIndex);
}

CExchange *CExchangeLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CExchange *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CExchangeLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CExchangeLinkIterator::UpdateCurrent(CWriteableExchange * pExchange,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pExchange,pTransaction,updateIndex);
}

CSeat *CSeatSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CSeatSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CSeatSingleIterator::UpdateCurrent(CWriteableSeat * pSeat,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pSeat,pTransaction,updateIndex);
}

CSeat *CSeatFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CSeat *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CSeatFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CSeatFilter::UpdateCurrent(CWriteableSeat * pSeat,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pSeat,pTransaction,updateIndex);
}

CSeat *CSeatLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CSeat *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CSeatLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CSeatLinkIterator::UpdateCurrent(CWriteableSeat * pSeat,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pSeat,pTransaction,updateIndex);
}

CInstrument *CInstrumentSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CInstrumentSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CInstrumentSingleIterator::UpdateCurrent(CWriteableInstrument * pInstrument,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pInstrument,pTransaction,updateIndex);
}

CInstrument *CInstrumentFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CInstrument *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CInstrumentFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CInstrumentFilter::UpdateCurrent(CWriteableInstrument * pInstrument,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pInstrument,pTransaction,updateIndex);
}

CInstrument *CInstrumentLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CInstrument *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CInstrumentLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CInstrumentLinkIterator::UpdateCurrent(CWriteableInstrument * pInstrument,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pInstrument,pTransaction,updateIndex);
}

CCmbInstrumentDetail *CCmbInstrumentDetailSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CCmbInstrumentDetailSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CCmbInstrumentDetailSingleIterator::UpdateCurrent(CWriteableCmbInstrumentDetail * pCmbInstrumentDetail,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pCmbInstrumentDetail,pTransaction,updateIndex);
}

CCmbInstrumentDetail *CCmbInstrumentDetailFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CCmbInstrumentDetail *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CCmbInstrumentDetailFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CCmbInstrumentDetailFilter::UpdateCurrent(CWriteableCmbInstrumentDetail * pCmbInstrumentDetail,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pCmbInstrumentDetail,pTransaction,updateIndex);
}

CCmbInstrumentDetail *CCmbInstrumentDetailLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CCmbInstrumentDetail *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CCmbInstrumentDetailLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CCmbInstrumentDetailLinkIterator::UpdateCurrent(CWriteableCmbInstrumentDetail * pCmbInstrumentDetail,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pCmbInstrumentDetail,pTransaction,updateIndex);
}

CClientTradingID *CClientTradingIDSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CClientTradingIDSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CClientTradingIDSingleIterator::UpdateCurrent(CWriteableClientTradingID * pClientTradingID,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pClientTradingID,pTransaction,updateIndex);
}

CClientTradingID *CClientTradingIDFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CClientTradingID *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CClientTradingIDFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CClientTradingIDFilter::UpdateCurrent(CWriteableClientTradingID * pClientTradingID,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pClientTradingID,pTransaction,updateIndex);
}

CClientTradingID *CClientTradingIDLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CClientTradingID *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CClientTradingIDLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CClientTradingIDLinkIterator::UpdateCurrent(CWriteableClientTradingID * pClientTradingID,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pClientTradingID,pTransaction,updateIndex);
}

CInvestorAccount *CInvestorAccountOfClientTradingIDIterator::next(void)
{
	CClientTradingID *pClientTradingID;
	while ((pClientTradingID=m_baseIterator->next())!=NULL)
	{
		m_current=pClientTradingID->getInvestorAccount();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorAccountOfClientTradingIDIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorAccountOfClientTradingIDIterator::UpdateCurrent(CWriteableInvestorAccount *pInvestorAccount,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorAccount,pTransaction,updateIndex);
}

CInvestor *CInvestorSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CInvestorSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CInvestorSingleIterator::UpdateCurrent(CWriteableInvestor * pInvestor,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pInvestor,pTransaction,updateIndex);
}

CInvestor *CInvestorFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CInvestor *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CInvestorFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CInvestorFilter::UpdateCurrent(CWriteableInvestor * pInvestor,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pInvestor,pTransaction,updateIndex);
}

CInvestor *CInvestorLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CInvestor *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CInvestorLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CInvestorLinkIterator::UpdateCurrent(CWriteableInvestor * pInvestor,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pInvestor,pTransaction,updateIndex);
}

CInvestorMargin *CInvestorMarginSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CInvestorMarginSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CInvestorMarginSingleIterator::UpdateCurrent(CWriteableInvestorMargin * pInvestorMargin,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pInvestorMargin,pTransaction,updateIndex);
}

CInvestorMargin *CInvestorMarginFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CInvestorMargin *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CInvestorMarginFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CInvestorMarginFilter::UpdateCurrent(CWriteableInvestorMargin * pInvestorMargin,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pInvestorMargin,pTransaction,updateIndex);
}

CInvestorMargin *CInvestorMarginLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CInvestorMargin *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CInvestorMarginLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CInvestorMarginLinkIterator::UpdateCurrent(CWriteableInvestorMargin * pInvestorMargin,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pInvestorMargin,pTransaction,updateIndex);
}

CInvestorFee *CInvestorFeeSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CInvestorFeeSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CInvestorFeeSingleIterator::UpdateCurrent(CWriteableInvestorFee * pInvestorFee,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pInvestorFee,pTransaction,updateIndex);
}

CInvestorFee *CInvestorFeeFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CInvestorFee *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CInvestorFeeFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CInvestorFeeFilter::UpdateCurrent(CWriteableInvestorFee * pInvestorFee,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pInvestorFee,pTransaction,updateIndex);
}

CInvestorFee *CInvestorFeeLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CInvestorFee *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CInvestorFeeLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CInvestorFeeLinkIterator::UpdateCurrent(CWriteableInvestorFee * pInvestorFee,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pInvestorFee,pTransaction,updateIndex);
}

CUser *CUserSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CUserSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CUserSingleIterator::UpdateCurrent(CWriteableUser * pUser,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pUser,pTransaction,updateIndex);
}

CUser *CUserFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CUser *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CUserFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CUserFilter::UpdateCurrent(CWriteableUser * pUser,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pUser,pTransaction,updateIndex);
}

CUser *CUserLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CUser *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CUserLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CUserLinkIterator::UpdateCurrent(CWriteableUser * pUser,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pUser,pTransaction,updateIndex);
}

CUserInvestor *CUserInvestorSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CUserInvestorSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CUserInvestorSingleIterator::UpdateCurrent(CWriteableUserInvestor * pUserInvestor,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pUserInvestor,pTransaction,updateIndex);
}

CUserInvestor *CUserInvestorFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CUserInvestor *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CUserInvestorFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CUserInvestorFilter::UpdateCurrent(CWriteableUserInvestor * pUserInvestor,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pUserInvestor,pTransaction,updateIndex);
}

CUserInvestor *CUserInvestorLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CUserInvestor *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CUserInvestorLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CUserInvestorLinkIterator::UpdateCurrent(CWriteableUserInvestor * pUserInvestor,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pUserInvestor,pTransaction,updateIndex);
}

COrderInsertFailed *COrderInsertFailedSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void COrderInsertFailedSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void COrderInsertFailedSingleIterator::UpdateCurrent(CWriteableOrderInsertFailed * pOrderInsertFailed,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pOrderInsertFailed,pTransaction,updateIndex);
}

COrderInsertFailed *COrderInsertFailedFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		COrderInsertFailed *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void COrderInsertFailedFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void COrderInsertFailedFilter::UpdateCurrent(CWriteableOrderInsertFailed * pOrderInsertFailed,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pOrderInsertFailed,pTransaction,updateIndex);
}

COrderInsertFailed *COrderInsertFailedLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			COrderInsertFailed *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void COrderInsertFailedLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void COrderInsertFailedLinkIterator::UpdateCurrent(CWriteableOrderInsertFailed * pOrderInsertFailed,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pOrderInsertFailed,pTransaction,updateIndex);
}

CInvestorAccount *CInvestorAccountOfOrderInsertFailedIterator::next(void)
{
	COrderInsertFailed *pOrderInsertFailed;
	while ((pOrderInsertFailed=m_baseIterator->next())!=NULL)
	{
		m_current=pOrderInsertFailed->getInvestorAccount();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorAccountOfOrderInsertFailedIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorAccountOfOrderInsertFailedIterator::UpdateCurrent(CWriteableInvestorAccount *pInvestorAccount,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorAccount,pTransaction,updateIndex);
}

CInvestorPosition *CInvestorPositionOfOrderInsertFailedIterator::next(void)
{
	COrderInsertFailed *pOrderInsertFailed;
	while ((pOrderInsertFailed=m_baseIterator->next())!=NULL)
	{
		m_current=pOrderInsertFailed->getInvestorPosition();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorPositionOfOrderInsertFailedIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorPositionOfOrderInsertFailedIterator::UpdateCurrent(CWriteableInvestorPosition *pInvestorPosition,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorPosition,pTransaction,updateIndex);
}

CInstrument *CInstrumentOfOrderInsertFailedIterator::next(void)
{
	COrderInsertFailed *pOrderInsertFailed;
	while ((pOrderInsertFailed=m_baseIterator->next())!=NULL)
	{
		m_current=pOrderInsertFailed->getInstrument();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInstrumentOfOrderInsertFailedIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInstrumentOfOrderInsertFailedIterator::UpdateCurrent(CWriteableInstrument *pInstrument,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInstrument,pTransaction,updateIndex);
}

CInvestorMargin *CInvestorMarginOfOrderInsertFailedIterator::next(void)
{
	COrderInsertFailed *pOrderInsertFailed;
	while ((pOrderInsertFailed=m_baseIterator->next())!=NULL)
	{
		m_current=pOrderInsertFailed->getInvestorMargin();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorMarginOfOrderInsertFailedIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorMarginOfOrderInsertFailedIterator::UpdateCurrent(CWriteableInvestorMargin *pInvestorMargin,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorMargin,pTransaction,updateIndex);
}

CInvestorFee *CInvestorFeeOfOrderInsertFailedIterator::next(void)
{
	COrderInsertFailed *pOrderInsertFailed;
	while ((pOrderInsertFailed=m_baseIterator->next())!=NULL)
	{
		m_current=pOrderInsertFailed->getInvestorFee();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CInvestorFeeOfOrderInsertFailedIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CInvestorFeeOfOrderInsertFailedIterator::UpdateCurrent(CWriteableInvestorFee *pInvestorFee,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pInvestorFee,pTransaction,updateIndex);
}

CUserTradingRight *CUserTradingRightSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CUserTradingRightSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CUserTradingRightSingleIterator::UpdateCurrent(CWriteableUserTradingRight * pUserTradingRight,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pUserTradingRight,pTransaction,updateIndex);
}

CUserTradingRight *CUserTradingRightFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CUserTradingRight *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CUserTradingRightFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CUserTradingRightFilter::UpdateCurrent(CWriteableUserTradingRight * pUserTradingRight,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pUserTradingRight,pTransaction,updateIndex);
}

CUserTradingRight *CUserTradingRightLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CUserTradingRight *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CUserTradingRightLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CUserTradingRightLinkIterator::UpdateCurrent(CWriteableUserTradingRight * pUserTradingRight,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pUserTradingRight,pTransaction,updateIndex);
}

CCurrentTime *CCurrentTimeSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CCurrentTimeSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CCurrentTimeSingleIterator::UpdateCurrent(CWriteableCurrentTime * pCurrentTime,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pCurrentTime,pTransaction,updateIndex);
}

CCurrentTime *CCurrentTimeFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CCurrentTime *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CCurrentTimeFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CCurrentTimeFilter::UpdateCurrent(CWriteableCurrentTime * pCurrentTime,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pCurrentTime,pTransaction,updateIndex);
}

CCurrentTime *CCurrentTimeLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CCurrentTime *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CCurrentTimeLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CCurrentTimeLinkIterator::UpdateCurrent(CWriteableCurrentTime * pCurrentTime,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pCurrentTime,pTransaction,updateIndex);
}

CUserSession *CUserSessionSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CUserSessionSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CUserSessionSingleIterator::UpdateCurrent(CWriteableUserSession * pUserSession,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pUserSession,pTransaction,updateIndex);
}

CUserSession *CUserSessionFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CUserSession *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CUserSessionFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CUserSessionFilter::UpdateCurrent(CWriteableUserSession * pUserSession,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pUserSession,pTransaction,updateIndex);
}

CUserSession *CUserSessionLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CUserSession *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CUserSessionLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CUserSessionLinkIterator::UpdateCurrent(CWriteableUserSession * pUserSession,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pUserSession,pTransaction,updateIndex);
}

CMaxLocalID *CMaxLocalIDSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CMaxLocalIDSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CMaxLocalIDSingleIterator::UpdateCurrent(CWriteableMaxLocalID * pMaxLocalID,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pMaxLocalID,pTransaction,updateIndex);
}

CMaxLocalID *CMaxLocalIDFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CMaxLocalID *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CMaxLocalIDFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CMaxLocalIDFilter::UpdateCurrent(CWriteableMaxLocalID * pMaxLocalID,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pMaxLocalID,pTransaction,updateIndex);
}

CMaxLocalID *CMaxLocalIDLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CMaxLocalID *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CMaxLocalIDLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CMaxLocalIDLinkIterator::UpdateCurrent(CWriteableMaxLocalID * pMaxLocalID,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pMaxLocalID,pTransaction,updateIndex);
}

CBrkUserIDLocalID *CBrkUserIDLocalIDSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CBrkUserIDLocalIDSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CBrkUserIDLocalIDSingleIterator::UpdateCurrent(CWriteableBrkUserIDLocalID * pBrkUserIDLocalID,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pBrkUserIDLocalID,pTransaction,updateIndex);
}

CBrkUserIDLocalID *CBrkUserIDLocalIDFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CBrkUserIDLocalID *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CBrkUserIDLocalIDFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CBrkUserIDLocalIDFilter::UpdateCurrent(CWriteableBrkUserIDLocalID * pBrkUserIDLocalID,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pBrkUserIDLocalID,pTransaction,updateIndex);
}

CBrkUserIDLocalID *CBrkUserIDLocalIDLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CBrkUserIDLocalID *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CBrkUserIDLocalIDLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CBrkUserIDLocalIDLinkIterator::UpdateCurrent(CWriteableBrkUserIDLocalID * pBrkUserIDLocalID,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pBrkUserIDLocalID,pTransaction,updateIndex);
}

CPreOrder *CPreOrderOfBrkUserIDLocalIDIterator::next(void)
{
	CBrkUserIDLocalID *pBrkUserIDLocalID;
	while ((pBrkUserIDLocalID=m_baseIterator->next())!=NULL)
	{
		m_current=pBrkUserIDLocalID->getPreOrder();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void CPreOrderOfBrkUserIDLocalIDIterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void CPreOrderOfBrkUserIDLocalIDIterator::UpdateCurrent(CWriteablePreOrder *pPreOrder,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,pPreOrder,pTransaction,updateIndex);
}

CPartClientInsGroupPosition *CPartClientInsGroupPositionSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CPartClientInsGroupPositionSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CPartClientInsGroupPositionSingleIterator::UpdateCurrent(CWriteablePartClientInsGroupPosition * pPartClientInsGroupPosition,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pPartClientInsGroupPosition,pTransaction,updateIndex);
}

CPartClientInsGroupPosition *CPartClientInsGroupPositionFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CPartClientInsGroupPosition *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CPartClientInsGroupPositionFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CPartClientInsGroupPositionFilter::UpdateCurrent(CWriteablePartClientInsGroupPosition * pPartClientInsGroupPosition,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pPartClientInsGroupPosition,pTransaction,updateIndex);
}

CPartClientInsGroupPosition *CPartClientInsGroupPositionLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CPartClientInsGroupPosition *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CPartClientInsGroupPositionLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CPartClientInsGroupPositionLinkIterator::UpdateCurrent(CWriteablePartClientInsGroupPosition * pPartClientInsGroupPosition,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pPartClientInsGroupPosition,pTransaction,updateIndex);
}

CClientMarginCombType *CClientMarginCombTypeSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CClientMarginCombTypeSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CClientMarginCombTypeSingleIterator::UpdateCurrent(CWriteableClientMarginCombType * pClientMarginCombType,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pClientMarginCombType,pTransaction,updateIndex);
}

CClientMarginCombType *CClientMarginCombTypeFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CClientMarginCombType *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CClientMarginCombTypeFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CClientMarginCombTypeFilter::UpdateCurrent(CWriteableClientMarginCombType * pClientMarginCombType,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pClientMarginCombType,pTransaction,updateIndex);
}

CClientMarginCombType *CClientMarginCombTypeLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CClientMarginCombType *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CClientMarginCombTypeLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CClientMarginCombTypeLinkIterator::UpdateCurrent(CWriteableClientMarginCombType * pClientMarginCombType,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pClientMarginCombType,pTransaction,updateIndex);
}

CInstrumentGroup *CInstrumentGroupSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CInstrumentGroupSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CInstrumentGroupSingleIterator::UpdateCurrent(CWriteableInstrumentGroup * pInstrumentGroup,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pInstrumentGroup,pTransaction,updateIndex);
}

CInstrumentGroup *CInstrumentGroupFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CInstrumentGroup *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CInstrumentGroupFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CInstrumentGroupFilter::UpdateCurrent(CWriteableInstrumentGroup * pInstrumentGroup,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pInstrumentGroup,pTransaction,updateIndex);
}

CInstrumentGroup *CInstrumentGroupLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CInstrumentGroup *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CInstrumentGroupLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CInstrumentGroupLinkIterator::UpdateCurrent(CWriteableInstrumentGroup * pInstrumentGroup,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pInstrumentGroup,pTransaction,updateIndex);
}

CSGEDeferRate *CSGEDeferRateSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CSGEDeferRateSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CSGEDeferRateSingleIterator::UpdateCurrent(CWriteableSGEDeferRate * pSGEDeferRate,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pSGEDeferRate,pTransaction,updateIndex);
}

CSGEDeferRate *CSGEDeferRateFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CSGEDeferRate *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CSGEDeferRateFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CSGEDeferRateFilter::UpdateCurrent(CWriteableSGEDeferRate * pSGEDeferRate,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pSGEDeferRate,pTransaction,updateIndex);
}

CSGEDeferRate *CSGEDeferRateLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CSGEDeferRate *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CSGEDeferRateLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CSGEDeferRateLinkIterator::UpdateCurrent(CWriteableSGEDeferRate * pSGEDeferRate,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pSGEDeferRate,pTransaction,updateIndex);
}

CInvestorTradingRight *CInvestorTradingRightSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CInvestorTradingRightSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CInvestorTradingRightSingleIterator::UpdateCurrent(CWriteableInvestorTradingRight * pInvestorTradingRight,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pInvestorTradingRight,pTransaction,updateIndex);
}

CInvestorTradingRight *CInvestorTradingRightFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CInvestorTradingRight *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CInvestorTradingRightFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CInvestorTradingRightFilter::UpdateCurrent(CWriteableInvestorTradingRight * pInvestorTradingRight,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pInvestorTradingRight,pTransaction,updateIndex);
}

CInvestorTradingRight *CInvestorTradingRightLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CInvestorTradingRight *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CInvestorTradingRightLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CInvestorTradingRightLinkIterator::UpdateCurrent(CWriteableInvestorTradingRight * pInvestorTradingRight,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pInvestorTradingRight,pTransaction,updateIndex);
}

CUserIP *CUserIPSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CUserIPSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CUserIPSingleIterator::UpdateCurrent(CWriteableUserIP * pUserIP,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pUserIP,pTransaction,updateIndex);
}

CUserIP *CUserIPFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CUserIP *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CUserIPFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CUserIPFilter::UpdateCurrent(CWriteableUserIP * pUserIP,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pUserIP,pTransaction,updateIndex);
}

CUserIP *CUserIPLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CUserIP *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CUserIPLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CUserIPLinkIterator::UpdateCurrent(CWriteableUserIP * pUserIP,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pUserIP,pTransaction,updateIndex);
}

CInvestorOptionFee *CInvestorOptionFeeSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CInvestorOptionFeeSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CInvestorOptionFeeSingleIterator::UpdateCurrent(CWriteableInvestorOptionFee * pInvestorOptionFee,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pInvestorOptionFee,pTransaction,updateIndex);
}

CInvestorOptionFee *CInvestorOptionFeeFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CInvestorOptionFee *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CInvestorOptionFeeFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CInvestorOptionFeeFilter::UpdateCurrent(CWriteableInvestorOptionFee * pInvestorOptionFee,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pInvestorOptionFee,pTransaction,updateIndex);
}

CInvestorOptionFee *CInvestorOptionFeeLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CInvestorOptionFee *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CInvestorOptionFeeLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CInvestorOptionFeeLinkIterator::UpdateCurrent(CWriteableInvestorOptionFee * pInvestorOptionFee,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pInvestorOptionFee,pTransaction,updateIndex);
}

CMarketData *CMarketDataSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CMarketDataSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CMarketDataSingleIterator::UpdateCurrent(CWriteableMarketData * pMarketData,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pMarketData,pTransaction,updateIndex);
}

CMarketData *CMarketDataFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CMarketData *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CMarketDataFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CMarketDataFilter::UpdateCurrent(CWriteableMarketData * pMarketData,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pMarketData,pTransaction,updateIndex);
}

CMarketData *CMarketDataLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CMarketData *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CMarketDataLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CMarketDataLinkIterator::UpdateCurrent(CWriteableMarketData * pMarketData,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pMarketData,pTransaction,updateIndex);
}

COrderDelay *COrderDelaySingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void COrderDelaySingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void COrderDelaySingleIterator::UpdateCurrent(CWriteableOrderDelay * pOrderDelay,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pOrderDelay,pTransaction,updateIndex);
}

COrderDelay *COrderDelayFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		COrderDelay *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void COrderDelayFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void COrderDelayFilter::UpdateCurrent(CWriteableOrderDelay * pOrderDelay,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pOrderDelay,pTransaction,updateIndex);
}

COrderDelay *COrderDelayLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			COrderDelay *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void COrderDelayLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void COrderDelayLinkIterator::UpdateCurrent(CWriteableOrderDelay * pOrderDelay,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pOrderDelay,pTransaction,updateIndex);
}

CSystemInfo *CSystemInfoSingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void CSystemInfoSingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void CSystemInfoSingleIterator::UpdateCurrent(CWriteableSystemInfo * pSystemInfo,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,pSystemInfo,pTransaction,updateIndex);
}

CSystemInfo *CSystemInfoFilter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		CSystemInfo *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void CSystemInfoFilter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void CSystemInfoFilter::UpdateCurrent(CWriteableSystemInfo * pSystemInfo,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(pSystemInfo,pTransaction,updateIndex);
}

CSystemInfo *CSystemInfoLinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			CSystemInfo *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void CSystemInfoLinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void CSystemInfoLinkIterator::UpdateCurrent(CWriteableSystemInfo * pSystemInfo,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(pSystemInfo,pTransaction,updateIndex);
}

