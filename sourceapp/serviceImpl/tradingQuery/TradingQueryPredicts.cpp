/////////////////////////////////////////////////////////////////////////
///@system 极速风控前置 执行引擎系统
///@company 上海量投网络科技有限公司
///@file TradingQueryPredicts.h
///@brief	定义了查询用的各种基础的谓词
///@history 
///20121115		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "TradingQueryPredicts.h"

///-----
///	20121115：修改了所有对合约查询的条件，变为可以输入前段的方式
///-----

bool COrderActionExchangeIDPredict::isValid(COrderAction *pOrderAction)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pOrderAction->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pOrderAction->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderActionOrderSysIDPredict::isValid(COrderAction *pOrderAction)
{
	if ((m_pOrderSysIDStart!=NULL)&&(!m_pOrderSysIDStart->isNull()))
	{
		if (pOrderAction->OrderSysID<*m_pOrderSysIDStart)
		{
			return false;
		}
	}
	if ((m_pOrderSysIDEnd!=NULL)&&(!m_pOrderSysIDEnd->isNull()))
	{
		if (pOrderAction->OrderSysID>*m_pOrderSysIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderActionBrokerIDPredict::isValid(COrderAction *pOrderAction)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pOrderAction->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pOrderAction->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderActionInvestorIDPredict::isValid(COrderAction *pOrderAction)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pOrderAction->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pOrderAction->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderActionUserIDPredict::isValid(COrderAction *pOrderAction)
{
	if ((m_pUserIDStart!=NULL)&&(!m_pUserIDStart->isNull()))
	{
		if (pOrderAction->UserID<*m_pUserIDStart)
		{
			return false;
		}
	}
	if ((m_pUserIDEnd!=NULL)&&(!m_pUserIDEnd->isNull()))
	{
		if (pOrderAction->UserID>*m_pUserIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderActionInstrumentIDStartPredict::isValid(COrderAction *pOrderAction)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pOrderAction->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pOrderAction->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pOrderAction->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool COrderActionClientIDPredict::isValid(COrderAction *pOrderAction)
{
	if ((m_pClientIDStart!=NULL)&&(!m_pClientIDStart->isNull()))
	{
		if (pOrderAction->ClientID<*m_pClientIDStart)
		{
			return false;
		}
	}
	if ((m_pClientIDEnd!=NULL)&&(!m_pClientIDEnd->isNull()))
	{
		if (pOrderAction->ClientID>*m_pClientIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderActionParticipantIDPredict::isValid(COrderAction *pOrderAction)
{
	if ((m_pParticipantIDStart!=NULL)&&(!m_pParticipantIDStart->isNull()))
	{
		if (pOrderAction->ParticipantID<*m_pParticipantIDStart)
		{
			return false;
		}
	}
	if ((m_pParticipantIDEnd!=NULL)&&(!m_pParticipantIDEnd->isNull()))
	{
		if (pOrderAction->ParticipantID>*m_pParticipantIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderBrokerIDPredict::isValid(COrder *pOrder)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pOrder->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pOrder->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderExchangeIDPredict::isValid(COrder *pOrder)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pOrder->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pOrder->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderOrderSysIDPredict::isValid(COrder *pOrder)
{
	if ((m_pOrderSysIDStart!=NULL)&&(!m_pOrderSysIDStart->isNull()))
	{
		if (pOrder->OrderSysID<*m_pOrderSysIDStart)
		{
			return false;
		}
	}
	if ((m_pOrderSysIDEnd!=NULL)&&(!m_pOrderSysIDEnd->isNull()))
	{
		if (pOrder->OrderSysID>*m_pOrderSysIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderInvestorIDPredict::isValid(COrder *pOrder)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pOrder->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pOrder->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderUserIDPredict::isValid(COrder *pOrder)
{
	if ((m_pUserIDStart!=NULL)&&(!m_pUserIDStart->isNull()))
	{
		if (pOrder->UserID<*m_pUserIDStart)
		{
			return false;
		}
	}
	if ((m_pUserIDEnd!=NULL)&&(!m_pUserIDEnd->isNull()))
	{
		if (pOrder->UserID>*m_pUserIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderInstrumentIDStartPredict::isValid(COrder *pOrder)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pOrder->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pOrder->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pOrder->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool COrderDirectionPredict::isValid(COrder *pOrder)
{
	if ((m_pDirectionStart!=NULL)&&(!m_pDirectionStart->isNull()))
	{
		if (pOrder->Direction<*m_pDirectionStart)
		{
			return false;
		}
	}
	if ((m_pDirectionEnd!=NULL)&&(!m_pDirectionEnd->isNull()))
	{
		if (pOrder->Direction>*m_pDirectionEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderParticipantIDPredict::isValid(COrder *pOrder)
{
	if ((m_pParticipantIDStart!=NULL)&&(!m_pParticipantIDStart->isNull()))
	{
		if (pOrder->ParticipantID<*m_pParticipantIDStart)
		{
			return false;
		}
	}
	if ((m_pParticipantIDEnd!=NULL)&&(!m_pParticipantIDEnd->isNull()))
	{
		if (pOrder->ParticipantID>*m_pParticipantIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderClientIDPredict::isValid(COrder *pOrder)
{
	if ((m_pClientIDStart!=NULL)&&(!m_pClientIDStart->isNull()))
	{
		if (pOrder->ClientID<*m_pClientIDStart)
		{
			return false;
		}
	}
	if ((m_pClientIDEnd!=NULL)&&(!m_pClientIDEnd->isNull()))
	{
		if (pOrder->ClientID>*m_pClientIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderInsertTimePredict::isValid(COrder *pOrder)
{
	if ((m_pInsertTimeStart!=NULL)&&(!m_pInsertTimeStart->isNull()))
	{
		if (pOrder->InsertTime<*m_pInsertTimeStart)
		{
			return false;
		}
	}
	if ((m_pInsertTimeEnd!=NULL)&&(!m_pInsertTimeEnd->isNull()))
	{
		if (pOrder->InsertTime>*m_pInsertTimeEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderAccountIDPredict::isValid(COrder *pOrder)
{
	if ((m_pAccountIDStart!=NULL)&&(!m_pAccountIDStart->isNull()))
	{
		if (pOrder->AccountID<*m_pAccountIDStart)
		{
			return false;
		}
	}
	if ((m_pAccountIDEnd!=NULL)&&(!m_pAccountIDEnd->isNull()))
	{
		if (pOrder->AccountID>*m_pAccountIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CTradeBrokerIDPredict::isValid(CTrade *pTrade)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pTrade->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pTrade->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CTradeExchangeIDPredict::isValid(CTrade *pTrade)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pTrade->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pTrade->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CTradeParticipantIDPredict::isValid(CTrade *pTrade)
{
	if ((m_pParticipantIDStart!=NULL)&&(!m_pParticipantIDStart->isNull()))
	{
		if (pTrade->ParticipantID<*m_pParticipantIDStart)
		{
			return false;
		}
	}
	if ((m_pParticipantIDEnd!=NULL)&&(!m_pParticipantIDEnd->isNull()))
	{
		if (pTrade->ParticipantID>*m_pParticipantIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CTradeInvestorIDPredict::isValid(CTrade *pTrade)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pTrade->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pTrade->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CTradeClientIDPredict::isValid(CTrade *pTrade)
{
	if ((m_pClientIDStart!=NULL)&&(!m_pClientIDStart->isNull()))
	{
		if (pTrade->ClientID<*m_pClientIDStart)
		{
			return false;
		}
	}
	if ((m_pClientIDEnd!=NULL)&&(!m_pClientIDEnd->isNull()))
	{
		if (pTrade->ClientID>*m_pClientIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CTradeUserIDPredict::isValid(CTrade *pTrade)
{
	if ((m_pUserIDStart!=NULL)&&(!m_pUserIDStart->isNull()))
	{
		if (pTrade->UserID<*m_pUserIDStart)
		{
			return false;
		}
	}
	if ((m_pUserIDEnd!=NULL)&&(!m_pUserIDEnd->isNull()))
	{
		if (pTrade->UserID>*m_pUserIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CTradeTradeIDPredict::isValid(CTrade *pTrade)
{
	if ((m_pTradeIDStart!=NULL)&&(!m_pTradeIDStart->isNull()))
	{
		if (pTrade->TradeID<*m_pTradeIDStart)
		{
			return false;
		}
	}
	if ((m_pTradeIDEnd!=NULL)&&(!m_pTradeIDEnd->isNull()))
	{
		if (pTrade->TradeID>*m_pTradeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CTradeOrderSysIDPredict::isValid(CTrade *pTrade)
{
	if ((m_pOrderSysIDStart!=NULL)&&(!m_pOrderSysIDStart->isNull()))
	{
		if (pTrade->OrderSysID<*m_pOrderSysIDStart)
		{
			return false;
		}
	}
	if ((m_pOrderSysIDEnd!=NULL)&&(!m_pOrderSysIDEnd->isNull()))
	{
		if (pTrade->OrderSysID>*m_pOrderSysIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CTradeInstrumentIDStartPredict::isValid(CTrade *pTrade)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pTrade->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pTrade->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pTrade->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool CTradeDirectionPredict::isValid(CTrade *pTrade)
{
	if ((m_pDirectionStart!=NULL)&&(!m_pDirectionStart->isNull()))
	{
		if (pTrade->Direction<*m_pDirectionStart)
		{
			return false;
		}
	}
	if ((m_pDirectionEnd!=NULL)&&(!m_pDirectionEnd->isNull()))
	{
		if (pTrade->Direction>*m_pDirectionEnd)
		{
			return false;
		}
	}
	return true;
}

bool CTradeTradeTimePredict::isValid(CTrade *pTrade)
{
	if ((m_pTradeTimeStart!=NULL)&&(!m_pTradeTimeStart->isNull()))
	{
		if (pTrade->TradeTime<*m_pTradeTimeStart)
		{
			return false;
		}
	}
	if ((m_pTradeTimeEnd!=NULL)&&(!m_pTradeTimeEnd->isNull()))
	{
		if (pTrade->TradeTime>*m_pTradeTimeEnd)
		{
			return false;
		}
	}
	return true;
}

bool CTradeClearingPartIDPredict::isValid(CTrade *pTrade)
{
	if ((m_pClearingPartIDStart!=NULL)&&(!m_pClearingPartIDStart->isNull()))
	{
		if (pTrade->ClearingPartID<*m_pClearingPartIDStart)
		{
			return false;
		}
	}
	if ((m_pClearingPartIDEnd!=NULL)&&(!m_pClearingPartIDEnd->isNull()))
	{
		if (pTrade->ClearingPartID>*m_pClearingPartIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CTradeAccountIDPredict::isValid(CTrade *pTrade)
{
	if ((m_pAccountIDStart!=NULL)&&(!m_pAccountIDStart->isNull()))
	{
		if (pTrade->AccountID<*m_pAccountIDStart)
		{
			return false;
		}
	}
	if ((m_pAccountIDEnd!=NULL)&&(!m_pAccountIDEnd->isNull()))
	{
		if (pTrade->AccountID>*m_pAccountIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CPreOrderBrokerIDPredict::isValid(CPreOrder *pPreOrder)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pPreOrder->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pPreOrder->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CPreOrderExchangeIDPredict::isValid(CPreOrder *pPreOrder)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pPreOrder->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pPreOrder->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CPreOrderOrderSysIDPredict::isValid(CPreOrder *pPreOrder)
{
	if ((m_pOrderSysIDStart!=NULL)&&(!m_pOrderSysIDStart->isNull()))
	{
		if (pPreOrder->OrderSysID<*m_pOrderSysIDStart)
		{
			return false;
		}
	}
	if ((m_pOrderSysIDEnd!=NULL)&&(!m_pOrderSysIDEnd->isNull()))
	{
		if (pPreOrder->OrderSysID>*m_pOrderSysIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CPreOrderInvestorIDPredict::isValid(CPreOrder *pPreOrder)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pPreOrder->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pPreOrder->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CPreOrderUserIDPredict::isValid(CPreOrder *pPreOrder)
{
	if ((m_pUserIDStart!=NULL)&&(!m_pUserIDStart->isNull()))
	{
		if (pPreOrder->UserID<*m_pUserIDStart)
		{
			return false;
		}
	}
	if ((m_pUserIDEnd!=NULL)&&(!m_pUserIDEnd->isNull()))
	{
		if (pPreOrder->UserID>*m_pUserIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CPreOrderInstrumentIDStartPredict::isValid(CPreOrder *pPreOrder)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pPreOrder->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pPreOrder->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pPreOrder->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool CPreOrderDirectionPredict::isValid(CPreOrder *pPreOrder)
{
	if ((m_pDirectionStart!=NULL)&&(!m_pDirectionStart->isNull()))
	{
		if (pPreOrder->Direction<*m_pDirectionStart)
		{
			return false;
		}
	}
	if ((m_pDirectionEnd!=NULL)&&(!m_pDirectionEnd->isNull()))
	{
		if (pPreOrder->Direction>*m_pDirectionEnd)
		{
			return false;
		}
	}
	return true;
}

bool CPreOrderParticipantIDPredict::isValid(CPreOrder *pPreOrder)
{
	if ((m_pParticipantIDStart!=NULL)&&(!m_pParticipantIDStart->isNull()))
	{
		if (pPreOrder->ParticipantID<*m_pParticipantIDStart)
		{
			return false;
		}
	}
	if ((m_pParticipantIDEnd!=NULL)&&(!m_pParticipantIDEnd->isNull()))
	{
		if (pPreOrder->ParticipantID>*m_pParticipantIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CPreOrderClientIDPredict::isValid(CPreOrder *pPreOrder)
{
	if ((m_pClientIDStart!=NULL)&&(!m_pClientIDStart->isNull()))
	{
		if (pPreOrder->ClientID<*m_pClientIDStart)
		{
			return false;
		}
	}
	if ((m_pClientIDEnd!=NULL)&&(!m_pClientIDEnd->isNull()))
	{
		if (pPreOrder->ClientID>*m_pClientIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CPreOrderInsertTimePredict::isValid(CPreOrder *pPreOrder)
{
	if ((m_pInsertTimeStart!=NULL)&&(!m_pInsertTimeStart->isNull()))
	{
		if (pPreOrder->InsertTime<*m_pInsertTimeStart)
		{
			return false;
		}
	}
	if ((m_pInsertTimeEnd!=NULL)&&(!m_pInsertTimeEnd->isNull()))
	{
		if (pPreOrder->InsertTime>*m_pInsertTimeEnd)
		{
			return false;
		}
	}
	return true;
}

bool CPreOrderAccountIDPredict::isValid(CPreOrder *pPreOrder)
{
	if ((m_pAccountIDStart!=NULL)&&(!m_pAccountIDStart->isNull()))
	{
		if (pPreOrder->AccountID<*m_pAccountIDStart)
		{
			return false;
		}
	}
	if ((m_pAccountIDEnd!=NULL)&&(!m_pAccountIDEnd->isNull()))
	{
		if (pPreOrder->AccountID>*m_pAccountIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CIndexPreOrderBrokerIDPredict::isValid(CIndexPreOrder *pIndexPreOrder)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pIndexPreOrder->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pIndexPreOrder->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CIndexPreOrderExchangeIDPredict::isValid(CIndexPreOrder *pIndexPreOrder)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pIndexPreOrder->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pIndexPreOrder->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CIndexPreOrderInvestorIDPredict::isValid(CIndexPreOrder *pIndexPreOrder)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pIndexPreOrder->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pIndexPreOrder->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CIndexPreOrderInstrumentIDStartPredict::isValid(CIndexPreOrder *pIndexPreOrder)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pIndexPreOrder->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pIndexPreOrder->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pIndexPreOrder->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool CIndexPreOrderDirectionPredict::isValid(CIndexPreOrder *pIndexPreOrder)
{
	if ((m_pDirectionStart!=NULL)&&(!m_pDirectionStart->isNull()))
	{
		if (pIndexPreOrder->Direction<*m_pDirectionStart)
		{
			return false;
		}
	}
	if ((m_pDirectionEnd!=NULL)&&(!m_pDirectionEnd->isNull()))
	{
		if (pIndexPreOrder->Direction>*m_pDirectionEnd)
		{
			return false;
		}
	}
	return true;
}

bool CIndexPreOrderClientIDPredict::isValid(CIndexPreOrder *pIndexPreOrder)
{
	if ((m_pClientIDStart!=NULL)&&(!m_pClientIDStart->isNull()))
	{
		if (pIndexPreOrder->ClientID<*m_pClientIDStart)
		{
			return false;
		}
	}
	if ((m_pClientIDEnd!=NULL)&&(!m_pClientIDEnd->isNull()))
	{
		if (pIndexPreOrder->ClientID>*m_pClientIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorPositionBrokerIDPredict::isValid(CInvestorPosition *pInvestorPosition)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pInvestorPosition->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pInvestorPosition->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorPositionExchangeIDPredict::isValid(CInvestorPosition *pInvestorPosition)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pInvestorPosition->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pInvestorPosition->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorPositionInvestorIDPredict::isValid(CInvestorPosition *pInvestorPosition)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pInvestorPosition->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pInvestorPosition->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorPositionParticipantIDPredict::isValid(CInvestorPosition *pInvestorPosition)
{
	if ((m_pParticipantIDStart!=NULL)&&(!m_pParticipantIDStart->isNull()))
	{
		if (pInvestorPosition->ParticipantID<*m_pParticipantIDStart)
		{
			return false;
		}
	}
	if ((m_pParticipantIDEnd!=NULL)&&(!m_pParticipantIDEnd->isNull()))
	{
		if (pInvestorPosition->ParticipantID>*m_pParticipantIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorPositionClientIDPredict::isValid(CInvestorPosition *pInvestorPosition)
{
	if ((m_pClientIDStart!=NULL)&&(!m_pClientIDStart->isNull()))
	{
		if (pInvestorPosition->ClientID<*m_pClientIDStart)
		{
			return false;
		}
	}
	if ((m_pClientIDEnd!=NULL)&&(!m_pClientIDEnd->isNull()))
	{
		if (pInvestorPosition->ClientID>*m_pClientIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorPositionInstrumentIDStartPredict::isValid(CInvestorPosition *pInvestorPosition)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pInvestorPosition->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pInvestorPosition->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pInvestorPosition->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool CInvestorPositionDirectionPredict::isValid(CInvestorPosition *pInvestorPosition)
{
	if ((m_pDirectionStart!=NULL)&&(!m_pDirectionStart->isNull()))
	{
		if (pInvestorPosition->Direction<*m_pDirectionStart)
		{
			return false;
		}
	}
	if ((m_pDirectionEnd!=NULL)&&(!m_pDirectionEnd->isNull()))
	{
		if (pInvestorPosition->Direction>*m_pDirectionEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorPositionAccountIDPredict::isValid(CInvestorPosition *pInvestorPosition)
{
	if ((m_pAccountIDStart!=NULL)&&(!m_pAccountIDStart->isNull()))
	{
		if (pInvestorPosition->AccountID<*m_pAccountIDStart)
		{
			return false;
		}
	}
	if ((m_pAccountIDEnd!=NULL)&&(!m_pAccountIDEnd->isNull()))
	{
		if (pInvestorPosition->AccountID>*m_pAccountIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorAccountBrokerIDPredict::isValid(CInvestorAccount *pInvestorAccount)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pInvestorAccount->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pInvestorAccount->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorAccountInvestorIDPredict::isValid(CInvestorAccount *pInvestorAccount)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pInvestorAccount->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pInvestorAccount->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorAccountAccountIDPredict::isValid(CInvestorAccount *pInvestorAccount)
{
	if ((m_pAccountIDStart!=NULL)&&(!m_pAccountIDStart->isNull()))
	{
		if (pInvestorAccount->AccountID<*m_pAccountIDStart)
		{
			return false;
		}
	}
	if ((m_pAccountIDEnd!=NULL)&&(!m_pAccountIDEnd->isNull()))
	{
		if (pInvestorAccount->AccountID>*m_pAccountIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorAccountDepositBrokerIDPredict::isValid(CInvestorAccountDeposit *pInvestorAccountDeposit)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pInvestorAccountDeposit->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pInvestorAccountDeposit->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorAccountDepositAccountIDPredict::isValid(CInvestorAccountDeposit *pInvestorAccountDeposit)
{
	if ((m_pAccountIDStart!=NULL)&&(!m_pAccountIDStart->isNull()))
	{
		if (pInvestorAccountDeposit->AccountID<*m_pAccountIDStart)
		{
			return false;
		}
	}
	if ((m_pAccountIDEnd!=NULL)&&(!m_pAccountIDEnd->isNull()))
	{
		if (pInvestorAccountDeposit->AccountID>*m_pAccountIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorAccountDepositInvestorIDPredict::isValid(CInvestorAccountDeposit *pInvestorAccountDeposit)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pInvestorAccountDeposit->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pInvestorAccountDeposit->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CExchangeExchangeIDPredict::isValid(CExchange *pExchange)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pExchange->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pExchange->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CSeatBrokerIDPredict::isValid(CSeat *pSeat)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pSeat->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pSeat->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CSeatExchangeIDPredict::isValid(CSeat *pSeat)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pSeat->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pSeat->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CSeatParticipantIDPredict::isValid(CSeat *pSeat)
{
	if ((m_pParticipantIDStart!=NULL)&&(!m_pParticipantIDStart->isNull()))
	{
		if (pSeat->ParticipantID<*m_pParticipantIDStart)
		{
			return false;
		}
	}
	if ((m_pParticipantIDEnd!=NULL)&&(!m_pParticipantIDEnd->isNull()))
	{
		if (pSeat->ParticipantID>*m_pParticipantIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInstrumentExchangeIDPredict::isValid(CInstrument *pInstrument)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pInstrument->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pInstrument->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInstrumentProductIDPredict::isValid(CInstrument *pInstrument)
{
	if ((m_pProductIDStart!=NULL)&&(!m_pProductIDStart->isNull()))
	{
		if (pInstrument->ProductID<*m_pProductIDStart)
		{
			return false;
		}
	}
	if ((m_pProductIDEnd!=NULL)&&(!m_pProductIDEnd->isNull()))
	{
		if (pInstrument->ProductID>*m_pProductIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInstrumentInstrumentIDStartPredict::isValid(CInstrument *pInstrument)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pInstrument->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pInstrument->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pInstrument->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool CInstrumentProductGroupIDPredict::isValid(CInstrument *pInstrument)
{
	if ((m_pProductGroupIDStart!=NULL)&&(!m_pProductGroupIDStart->isNull()))
	{
		if (pInstrument->ProductGroupID<*m_pProductGroupIDStart)
		{
			return false;
		}
	}
	if ((m_pProductGroupIDEnd!=NULL)&&(!m_pProductGroupIDEnd->isNull()))
	{
		if (pInstrument->ProductGroupID>*m_pProductGroupIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CCmbInstrumentDetailExchangeIDPredict::isValid(CCmbInstrumentDetail *pCmbInstrumentDetail)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pCmbInstrumentDetail->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pCmbInstrumentDetail->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CCmbInstrumentDetailDirectionPredict::isValid(CCmbInstrumentDetail *pCmbInstrumentDetail)
{
	if ((m_pDirectionStart!=NULL)&&(!m_pDirectionStart->isNull()))
	{
		if (pCmbInstrumentDetail->Direction<*m_pDirectionStart)
		{
			return false;
		}
	}
	if ((m_pDirectionEnd!=NULL)&&(!m_pDirectionEnd->isNull()))
	{
		if (pCmbInstrumentDetail->Direction>*m_pDirectionEnd)
		{
			return false;
		}
	}
	return true;
}

bool CClientTradingIDBrokerIDPredict::isValid(CClientTradingID *pClientTradingID)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pClientTradingID->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pClientTradingID->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CClientTradingIDInvestorIDPredict::isValid(CClientTradingID *pClientTradingID)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pClientTradingID->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pClientTradingID->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CClientTradingIDAccountIDPredict::isValid(CClientTradingID *pClientTradingID)
{
	if ((m_pAccountIDStart!=NULL)&&(!m_pAccountIDStart->isNull()))
	{
		if (pClientTradingID->AccountID<*m_pAccountIDStart)
		{
			return false;
		}
	}
	if ((m_pAccountIDEnd!=NULL)&&(!m_pAccountIDEnd->isNull()))
	{
		if (pClientTradingID->AccountID>*m_pAccountIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CClientTradingIDExchangeIDPredict::isValid(CClientTradingID *pClientTradingID)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pClientTradingID->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pClientTradingID->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CClientTradingIDParticipantIDPredict::isValid(CClientTradingID *pClientTradingID)
{
	if ((m_pParticipantIDStart!=NULL)&&(!m_pParticipantIDStart->isNull()))
	{
		if (pClientTradingID->ParticipantID<*m_pParticipantIDStart)
		{
			return false;
		}
	}
	if ((m_pParticipantIDEnd!=NULL)&&(!m_pParticipantIDEnd->isNull()))
	{
		if (pClientTradingID->ParticipantID>*m_pParticipantIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CClientTradingIDClientIDPredict::isValid(CClientTradingID *pClientTradingID)
{
	if ((m_pClientIDStart!=NULL)&&(!m_pClientIDStart->isNull()))
	{
		if (pClientTradingID->ClientID<*m_pClientIDStart)
		{
			return false;
		}
	}
	if ((m_pClientIDEnd!=NULL)&&(!m_pClientIDEnd->isNull()))
	{
		if (pClientTradingID->ClientID>*m_pClientIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorBrokerIDPredict::isValid(CInvestor *pInvestor)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pInvestor->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pInvestor->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorInvestorIDPredict::isValid(CInvestor *pInvestor)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pInvestor->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pInvestor->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorMarginBrokerIDPredict::isValid(CInvestorMargin *pInvestorMargin)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pInvestorMargin->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pInvestorMargin->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorMarginExchangeIDPredict::isValid(CInvestorMargin *pInvestorMargin)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pInvestorMargin->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pInvestorMargin->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorMarginInvestorIDPredict::isValid(CInvestorMargin *pInvestorMargin)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pInvestorMargin->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pInvestorMargin->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorMarginInstrumentIDStartPredict::isValid(CInvestorMargin *pInvestorMargin)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pInvestorMargin->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pInvestorMargin->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pInvestorMargin->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool CInvestorFeeBrokerIDPredict::isValid(CInvestorFee *pInvestorFee)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pInvestorFee->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pInvestorFee->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorFeeExchangeIDPredict::isValid(CInvestorFee *pInvestorFee)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pInvestorFee->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pInvestorFee->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorFeeInvestorIDPredict::isValid(CInvestorFee *pInvestorFee)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pInvestorFee->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pInvestorFee->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorFeeInstrumentIDStartPredict::isValid(CInvestorFee *pInvestorFee)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pInvestorFee->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pInvestorFee->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pInvestorFee->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool CUserBrokerIDPredict::isValid(CUser *pUser)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pUser->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pUser->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CUserUserIDPredict::isValid(CUser *pUser)
{
	if ((m_pUserIDStart!=NULL)&&(!m_pUserIDStart->isNull()))
	{
		if (pUser->UserID<*m_pUserIDStart)
		{
			return false;
		}
	}
	if ((m_pUserIDEnd!=NULL)&&(!m_pUserIDEnd->isNull()))
	{
		if (pUser->UserID>*m_pUserIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CUserInvestorBrokerIDPredict::isValid(CUserInvestor *pUserInvestor)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pUserInvestor->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pUserInvestor->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CUserInvestorUserIDPredict::isValid(CUserInvestor *pUserInvestor)
{
	if ((m_pUserIDStart!=NULL)&&(!m_pUserIDStart->isNull()))
	{
		if (pUserInvestor->UserID<*m_pUserIDStart)
		{
			return false;
		}
	}
	if ((m_pUserIDEnd!=NULL)&&(!m_pUserIDEnd->isNull()))
	{
		if (pUserInvestor->UserID>*m_pUserIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CUserInvestorInvestorIDPredict::isValid(CUserInvestor *pUserInvestor)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pUserInvestor->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pUserInvestor->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderInsertFailedBrokerIDPredict::isValid(COrderInsertFailed *pOrderInsertFailed)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pOrderInsertFailed->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pOrderInsertFailed->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderInsertFailedExchangeIDPredict::isValid(COrderInsertFailed *pOrderInsertFailed)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pOrderInsertFailed->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pOrderInsertFailed->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderInsertFailedOrderSysIDPredict::isValid(COrderInsertFailed *pOrderInsertFailed)
{
	if ((m_pOrderSysIDStart!=NULL)&&(!m_pOrderSysIDStart->isNull()))
	{
		if (pOrderInsertFailed->OrderSysID<*m_pOrderSysIDStart)
		{
			return false;
		}
	}
	if ((m_pOrderSysIDEnd!=NULL)&&(!m_pOrderSysIDEnd->isNull()))
	{
		if (pOrderInsertFailed->OrderSysID>*m_pOrderSysIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderInsertFailedInvestorIDPredict::isValid(COrderInsertFailed *pOrderInsertFailed)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pOrderInsertFailed->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pOrderInsertFailed->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderInsertFailedUserIDPredict::isValid(COrderInsertFailed *pOrderInsertFailed)
{
	if ((m_pUserIDStart!=NULL)&&(!m_pUserIDStart->isNull()))
	{
		if (pOrderInsertFailed->UserID<*m_pUserIDStart)
		{
			return false;
		}
	}
	if ((m_pUserIDEnd!=NULL)&&(!m_pUserIDEnd->isNull()))
	{
		if (pOrderInsertFailed->UserID>*m_pUserIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderInsertFailedInstrumentIDStartPredict::isValid(COrderInsertFailed *pOrderInsertFailed)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pOrderInsertFailed->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pOrderInsertFailed->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pOrderInsertFailed->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool COrderInsertFailedDirectionPredict::isValid(COrderInsertFailed *pOrderInsertFailed)
{
	if ((m_pDirectionStart!=NULL)&&(!m_pDirectionStart->isNull()))
	{
		if (pOrderInsertFailed->Direction<*m_pDirectionStart)
		{
			return false;
		}
	}
	if ((m_pDirectionEnd!=NULL)&&(!m_pDirectionEnd->isNull()))
	{
		if (pOrderInsertFailed->Direction>*m_pDirectionEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderInsertFailedParticipantIDPredict::isValid(COrderInsertFailed *pOrderInsertFailed)
{
	if ((m_pParticipantIDStart!=NULL)&&(!m_pParticipantIDStart->isNull()))
	{
		if (pOrderInsertFailed->ParticipantID<*m_pParticipantIDStart)
		{
			return false;
		}
	}
	if ((m_pParticipantIDEnd!=NULL)&&(!m_pParticipantIDEnd->isNull()))
	{
		if (pOrderInsertFailed->ParticipantID>*m_pParticipantIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderInsertFailedClientIDPredict::isValid(COrderInsertFailed *pOrderInsertFailed)
{
	if ((m_pClientIDStart!=NULL)&&(!m_pClientIDStart->isNull()))
	{
		if (pOrderInsertFailed->ClientID<*m_pClientIDStart)
		{
			return false;
		}
	}
	if ((m_pClientIDEnd!=NULL)&&(!m_pClientIDEnd->isNull()))
	{
		if (pOrderInsertFailed->ClientID>*m_pClientIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderInsertFailedInsertTimePredict::isValid(COrderInsertFailed *pOrderInsertFailed)
{
	if ((m_pInsertTimeStart!=NULL)&&(!m_pInsertTimeStart->isNull()))
	{
		if (pOrderInsertFailed->InsertTime<*m_pInsertTimeStart)
		{
			return false;
		}
	}
	if ((m_pInsertTimeEnd!=NULL)&&(!m_pInsertTimeEnd->isNull()))
	{
		if (pOrderInsertFailed->InsertTime>*m_pInsertTimeEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderInsertFailedAccountIDPredict::isValid(COrderInsertFailed *pOrderInsertFailed)
{
	if ((m_pAccountIDStart!=NULL)&&(!m_pAccountIDStart->isNull()))
	{
		if (pOrderInsertFailed->AccountID<*m_pAccountIDStart)
		{
			return false;
		}
	}
	if ((m_pAccountIDEnd!=NULL)&&(!m_pAccountIDEnd->isNull()))
	{
		if (pOrderInsertFailed->AccountID>*m_pAccountIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CUserTradingRightBrokerIDPredict::isValid(CUserTradingRight *pUserTradingRight)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pUserTradingRight->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pUserTradingRight->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CUserTradingRightExchangeIDPredict::isValid(CUserTradingRight *pUserTradingRight)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pUserTradingRight->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pUserTradingRight->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CUserTradingRightInstrumentIDStartPredict::isValid(CUserTradingRight *pUserTradingRight)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pUserTradingRight->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pUserTradingRight->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pUserTradingRight->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool CUserTradingRightUserIDPredict::isValid(CUserTradingRight *pUserTradingRight)
{
	if ((m_pUserIDStart!=NULL)&&(!m_pUserIDStart->isNull()))
	{
		if (pUserTradingRight->UserID<*m_pUserIDStart)
		{
			return false;
		}
	}
	if ((m_pUserIDEnd!=NULL)&&(!m_pUserIDEnd->isNull()))
	{
		if (pUserTradingRight->UserID>*m_pUserIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CUserTradingRightInvestorIDPredict::isValid(CUserTradingRight *pUserTradingRight)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pUserTradingRight->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pUserTradingRight->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CUserSessionBrokerIDPredict::isValid(CUserSession *pUserSession)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pUserSession->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pUserSession->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CUserSessionUserIDPredict::isValid(CUserSession *pUserSession)
{
	if ((m_pUserIDStart!=NULL)&&(!m_pUserIDStart->isNull()))
	{
		if (pUserSession->UserID<*m_pUserIDStart)
		{
			return false;
		}
	}
	if ((m_pUserIDEnd!=NULL)&&(!m_pUserIDEnd->isNull()))
	{
		if (pUserSession->UserID>*m_pUserIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CMaxLocalIDBrokerIDPredict::isValid(CMaxLocalID *pMaxLocalID)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pMaxLocalID->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pMaxLocalID->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CMaxLocalIDUserIDPredict::isValid(CMaxLocalID *pMaxLocalID)
{
	if ((m_pUserIDStart!=NULL)&&(!m_pUserIDStart->isNull()))
	{
		if (pMaxLocalID->UserID<*m_pUserIDStart)
		{
			return false;
		}
	}
	if ((m_pUserIDEnd!=NULL)&&(!m_pUserIDEnd->isNull()))
	{
		if (pMaxLocalID->UserID>*m_pUserIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CBrkUserIDLocalIDBrokerIDPredict::isValid(CBrkUserIDLocalID *pBrkUserIDLocalID)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pBrkUserIDLocalID->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pBrkUserIDLocalID->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CBrkUserIDLocalIDUserIDPredict::isValid(CBrkUserIDLocalID *pBrkUserIDLocalID)
{
	if ((m_pUserIDStart!=NULL)&&(!m_pUserIDStart->isNull()))
	{
		if (pBrkUserIDLocalID->UserID<*m_pUserIDStart)
		{
			return false;
		}
	}
	if ((m_pUserIDEnd!=NULL)&&(!m_pUserIDEnd->isNull()))
	{
		if (pBrkUserIDLocalID->UserID>*m_pUserIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CPartClientInsGroupPositionBrokerIDPredict::isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pPartClientInsGroupPosition->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pPartClientInsGroupPosition->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CPartClientInsGroupPositionParticipantIDPredict::isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
{
	if ((m_pParticipantIDStart!=NULL)&&(!m_pParticipantIDStart->isNull()))
	{
		if (pPartClientInsGroupPosition->ParticipantID<*m_pParticipantIDStart)
		{
			return false;
		}
	}
	if ((m_pParticipantIDEnd!=NULL)&&(!m_pParticipantIDEnd->isNull()))
	{
		if (pPartClientInsGroupPosition->ParticipantID>*m_pParticipantIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CPartClientInsGroupPositionClientIDPredict::isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
{
	if ((m_pClientIDStart!=NULL)&&(!m_pClientIDStart->isNull()))
	{
		if (pPartClientInsGroupPosition->ClientID<*m_pClientIDStart)
		{
			return false;
		}
	}
	if ((m_pClientIDEnd!=NULL)&&(!m_pClientIDEnd->isNull()))
	{
		if (pPartClientInsGroupPosition->ClientID>*m_pClientIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CClientMarginCombTypeBrokerIDPredict::isValid(CClientMarginCombType *pClientMarginCombType)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pClientMarginCombType->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pClientMarginCombType->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CClientMarginCombTypeParticipantIDPredict::isValid(CClientMarginCombType *pClientMarginCombType)
{
	if ((m_pParticipantIDStart!=NULL)&&(!m_pParticipantIDStart->isNull()))
	{
		if (pClientMarginCombType->ParticipantID<*m_pParticipantIDStart)
		{
			return false;
		}
	}
	if ((m_pParticipantIDEnd!=NULL)&&(!m_pParticipantIDEnd->isNull()))
	{
		if (pClientMarginCombType->ParticipantID>*m_pParticipantIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CClientMarginCombTypeClientIDPredict::isValid(CClientMarginCombType *pClientMarginCombType)
{
	if ((m_pClientIDStart!=NULL)&&(!m_pClientIDStart->isNull()))
	{
		if (pClientMarginCombType->ClientID<*m_pClientIDStart)
		{
			return false;
		}
	}
	if ((m_pClientIDEnd!=NULL)&&(!m_pClientIDEnd->isNull()))
	{
		if (pClientMarginCombType->ClientID>*m_pClientIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInstrumentGroupExchangeIDPredict::isValid(CInstrumentGroup *pInstrumentGroup)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pInstrumentGroup->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pInstrumentGroup->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInstrumentGroupBrokerIDPredict::isValid(CInstrumentGroup *pInstrumentGroup)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pInstrumentGroup->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pInstrumentGroup->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInstrumentGroupInstrumentIDStartPredict::isValid(CInstrumentGroup *pInstrumentGroup)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pInstrumentGroup->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pInstrumentGroup->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pInstrumentGroup->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool CSGEDeferRateInstrumentIDStartPredict::isValid(CSGEDeferRate *pSGEDeferRate)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pSGEDeferRate->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pSGEDeferRate->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pSGEDeferRate->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool CSGEDeferRateExchangeIDPredict::isValid(CSGEDeferRate *pSGEDeferRate)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pSGEDeferRate->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pSGEDeferRate->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CSGEDeferRateDirectionPredict::isValid(CSGEDeferRate *pSGEDeferRate)
{
	if ((m_pDirectionStart!=NULL)&&(!m_pDirectionStart->isNull()))
	{
		if (pSGEDeferRate->Direction<*m_pDirectionStart)
		{
			return false;
		}
	}
	if ((m_pDirectionEnd!=NULL)&&(!m_pDirectionEnd->isNull()))
	{
		if (pSGEDeferRate->Direction>*m_pDirectionEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorTradingRightBrokerIDPredict::isValid(CInvestorTradingRight *pInvestorTradingRight)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pInvestorTradingRight->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pInvestorTradingRight->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorTradingRightInvestorIDPredict::isValid(CInvestorTradingRight *pInvestorTradingRight)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pInvestorTradingRight->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pInvestorTradingRight->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorTradingRightExchangeIDPredict::isValid(CInvestorTradingRight *pInvestorTradingRight)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pInvestorTradingRight->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pInvestorTradingRight->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorTradingRightInstrumentIDStartPredict::isValid(CInvestorTradingRight *pInvestorTradingRight)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pInvestorTradingRight->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pInvestorTradingRight->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pInvestorTradingRight->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool CUserIPBrokerIDPredict::isValid(CUserIP *pUserIP)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pUserIP->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pUserIP->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CUserIPUserIDPredict::isValid(CUserIP *pUserIP)
{
	if ((m_pUserIDStart!=NULL)&&(!m_pUserIDStart->isNull()))
	{
		if (pUserIP->UserID<*m_pUserIDStart)
		{
			return false;
		}
	}
	if ((m_pUserIDEnd!=NULL)&&(!m_pUserIDEnd->isNull()))
	{
		if (pUserIP->UserID>*m_pUserIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorOptionFeeBrokerIDPredict::isValid(CInvestorOptionFee *pInvestorOptionFee)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pInvestorOptionFee->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pInvestorOptionFee->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorOptionFeeExchangeIDPredict::isValid(CInvestorOptionFee *pInvestorOptionFee)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pInvestorOptionFee->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pInvestorOptionFee->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorOptionFeeInvestorIDPredict::isValid(CInvestorOptionFee *pInvestorOptionFee)
{
	if ((m_pInvestorIDStart!=NULL)&&(!m_pInvestorIDStart->isNull()))
	{
		if (pInvestorOptionFee->InvestorID<*m_pInvestorIDStart)
		{
			return false;
		}
	}
	if ((m_pInvestorIDEnd!=NULL)&&(!m_pInvestorIDEnd->isNull()))
	{
		if (pInvestorOptionFee->InvestorID>*m_pInvestorIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CInvestorOptionFeeInstrumentIDStartPredict::isValid(CInvestorOptionFee *pInvestorOptionFee)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pInvestorOptionFee->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pInvestorOptionFee->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pInvestorOptionFee->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool CMarketDataExchangeIDPredict::isValid(CMarketData *pMarketData)
{
	if ((m_pExchangeIDStart!=NULL)&&(!m_pExchangeIDStart->isNull()))
	{
		if (pMarketData->ExchangeID<*m_pExchangeIDStart)
		{
			return false;
		}
	}
	if ((m_pExchangeIDEnd!=NULL)&&(!m_pExchangeIDEnd->isNull()))
	{
		if (pMarketData->ExchangeID>*m_pExchangeIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool CMarketDataInstrumentIDStartPredict::isValid(CMarketData *pMarketData)
{
	if ((m_pInstrumentIDStart!=NULL)&&(!m_pInstrumentIDStart->isNull()))
	{
		if (pMarketData->InstrumentID<*m_pInstrumentIDStart)
		{
			return false;
		}
	}
	if ((m_pInstrumentIDEnd!=NULL)&&(!m_pInstrumentIDEnd->isNull()))
	{
		if (pMarketData->InstrumentID>*m_pInstrumentIDEnd)
		{
			if (!strncmp(pMarketData->InstrumentID,*m_pInstrumentIDEnd,strlen(*m_pInstrumentIDEnd)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

bool COrderDelayBrokerIDPredict::isValid(COrderDelay *pOrderDelay)
{
	if ((m_pBrokerIDStart!=NULL)&&(!m_pBrokerIDStart->isNull()))
	{
		if (pOrderDelay->BrokerID<*m_pBrokerIDStart)
		{
			return false;
		}
	}
	if ((m_pBrokerIDEnd!=NULL)&&(!m_pBrokerIDEnd->isNull()))
	{
		if (pOrderDelay->BrokerID>*m_pBrokerIDEnd)
		{
			return false;
		}
	}
	return true;
}

bool COrderDelayUserIDPredict::isValid(COrderDelay *pOrderDelay)
{
	if ((m_pUserIDStart!=NULL)&&(!m_pUserIDStart->isNull()))
	{
		if (pOrderDelay->UserID<*m_pUserIDStart)
		{
			return false;
		}
	}
	if ((m_pUserIDEnd!=NULL)&&(!m_pUserIDEnd->isNull()))
	{
		if (pOrderDelay->UserID>*m_pUserIDEnd)
		{
			return false;
		}
	}
	return true;
}

