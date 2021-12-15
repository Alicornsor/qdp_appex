#include "RuleHandleBase.h"

extern const CClientIDType defaultClientID;
CRuleHandleBase::CRuleHandleBase(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult)
{
	m_pDB=pDB;
	m_pErrorEngine=pErrorEngine;
	m_pTradeResult= pTradeResult;
	m_pConfig = pConfig;
	// 移到子类中去生成资金持仓对象
	// m_pMoneyPosition = new CMoneyPosition(pDB,pErrorEngine,pConfig);
}

CRuleHandleBase::~CRuleHandleBase()
{
	
}

bool CRuleHandleBase::InitIndexPreOrder(CPreOrder *pOrder,CWriteableIndexPreOrder *pIndexPreOrder,CTransaction *pTransaction, bool isRecover)
{
	if(!isRecover && m_pDB->m_UserInvestorFactory->findByBrokerIDUserIDInvestorID(pOrder->BrokerID,pOrder->UserID,pOrder->InvestorID)==NULL)
	{
		m_pErrorEngine->reportError(ERROR_USER_INVESTOR_NOT_RELATED);//User没有对该客户下单的权限
		return false;
	}
	pIndexPreOrder->InvestorID = pOrder->InvestorID;
	pIndexPreOrder->ExchangeID = pOrder->ExchangeID;
	pIndexPreOrder->InstrumentID = pOrder->InstrumentID;
	pIndexPreOrder->HedgeFlag = pOrder->HedgeFlag;
	pIndexPreOrder->BrokerID = pOrder->BrokerID;
	pIndexPreOrder->UserID = pOrder->UserID;
	//查找合约
	CInstrument *pInstrument = m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pOrder->ExchangeID,pOrder->InstrumentID);
	if (pInstrument ==NULL)
	{
		m_pErrorEngine->reportError(ERROR_INSTRUMENT_NOT_FOUND);
		return false;
	}
	pIndexPreOrder->ProductClass = pInstrument->ProductClass;
	pIndexPreOrder->ProductID    = pInstrument->ProductID;
	pIndexPreOrder->UnderlyingInstrID = pInstrument->UnderlyingInstrID;
	pIndexPreOrder->StrikePrice = pInstrument->StrikePrice;
	pIndexPreOrder->OptionsType = pInstrument->OptionsType;
	pIndexPreOrder->VolumeMultiple = pInstrument->VolumeMultiple;
	char tmp[3]={0};
	sprintf(tmp,"%c",pInstrument->Currency.getValue());
	pIndexPreOrder->Currency = tmp;

	//查找交易编码
	CClientTradingID *pClientTradingID = m_pDB->m_ClientTradingIDFactory->findByBrkIDExIDInvIDHdgFlg(pOrder->BrokerID,\
										pOrder->ExchangeID,pOrder->InvestorID,pOrder->HedgeFlag);
	if (pClientTradingID == NULL)
	{
		m_pErrorEngine->reportError(ERROR_TRADINGID_NOT_EXIST);
		return false;
	}
	pIndexPreOrder->linkClientTradingID(pClientTradingID);
	pIndexPreOrder->ParticipantID = pClientTradingID->ParticipantID;
	pIndexPreOrder->ClientID = pClientTradingID->ClientID;
	pIndexPreOrder->APIID = pClientTradingID->APIID;
	pIndexPreOrder->PositionType = pClientTradingID->PositionType;

	//查找资金账号
	CInvestorAccount *pAccount = m_pDB->m_InvestorAccountFactory->findByBrokerIDInvestorID(pOrder->BrokerID,pOrder->InvestorID);
	if (pAccount == NULL)
	{
		m_pErrorEngine->reportError(ERROR_CAN_NOT_FIND_ACCOUNT);
		return false;
	}
	pIndexPreOrder->linkInvestorAccount(pAccount);

	if (pIndexPreOrder->ProductClass == PC_Futures)
	{
		//获取保证金率
		CInvestorMargin *pInvestorMargin = baseAlgorithms.getInvestorMargin(m_pDB,pInstrument,pOrder->BrokerID,pOrder->InvestorID,pOrder->HedgeFlag);
		if (pInvestorMargin == NULL)
		{
			m_pErrorEngine->reportError(ERROR_NO_CLIENT_MARGIN_FEE_DATA);
			return false;
		}
		pIndexPreOrder->LongMarginRate = pInvestorMargin->LongMarginRate;
		pIndexPreOrder->LongMarginAmt = pInvestorMargin->LongMarginAmt;
		pIndexPreOrder->ShortMarginRate = pInvestorMargin->ShortMarginRate;
		pIndexPreOrder->ShortMarginAmt = pInvestorMargin->ShortMarginAmt;
		
		//获取手续费率
		CInvestorFee *pInvestorFee = baseAlgorithms.getInvestorFee(m_pDB,pInstrument,pOrder->BrokerID,pOrder->InvestorID,pOrder->HedgeFlag);
		if (pInvestorFee == NULL)
		{
			m_pErrorEngine->reportError(ERROR_NO_CLIENT_MARGIN_FEE_DATA);
			return false;
		}
		pIndexPreOrder->OpenFeeRate = pInvestorFee->OpenFeeRate;
		pIndexPreOrder->OpenFeeAmt = pInvestorFee->OpenFeeAmt;
		pIndexPreOrder->OffsetFeeRate = pInvestorFee->OffsetFeeRate;
		pIndexPreOrder->OffsetFeeAmt = pInvestorFee->OffsetFeeAmt;

		//获取昨结算价
		CMarketData *pMarketData = m_pDB->m_MarketDataFactory->findByExchangeIDAndInstrumentID(pOrder->ExchangeID,pOrder->InstrumentID);
		if (pMarketData == NULL)
		{
			m_pErrorEngine->reportError(ERROR_CAN_NOT_FIND_INSTRUMENT_MARKET_DATA);
			return false;
		}
		pIndexPreOrder->PreSettlementPrice = pMarketData->PreSettlementPrice;

		//查询持仓
		CInvestorPosition *pPosition = NULL;
		if (pClientTradingID->PositionType == PT_Net)
		{
			pPosition = m_pDB->m_InvestorPositionFactory->findByBrkIDExIDInvIDInsDirHed(pOrder->BrokerID,pOrder->ExchangeID,\
				pOrder->InvestorID,pOrder->InstrumentID,D_Net,pOrder->HedgeFlag);
			if (pPosition != NULL)
			{
				pIndexPreOrder->Position = pPosition->YdPosition;
				if (pIndexPreOrder->Position >0)
				{
					pIndexPreOrder->PositionCost = pIndexPreOrder->Position * pIndexPreOrder->PreSettlementPrice * pIndexPreOrder->VolumeMultiple;
					pIndexPreOrder->ActualMargin = pIndexPreOrder->Position * pIndexPreOrder->LongMarginAmt;
				}
				else
				{
					pIndexPreOrder->PositionCost = -1 *pIndexPreOrder->Position * pIndexPreOrder->PreSettlementPrice * pIndexPreOrder->VolumeMultiple;
					pIndexPreOrder->ActualMargin = -1 *pIndexPreOrder->Position * pIndexPreOrder->ShortMarginAmt;
				}
				pOrder->linkInvestorPosition(pPosition);
			}
		}
		else
		{
			pPosition = m_pDB->m_InvestorPositionFactory->findByBrkIDExIDInvIDInsDirHed(pOrder->BrokerID,pOrder->ExchangeID,\
				pOrder->InvestorID,pOrder->InstrumentID,D_Buy,pOrder->HedgeFlag);
			if (pPosition != NULL)
			{
				pIndexPreOrder->LongYdPosition = pPosition->YdPosition;
				CMoneyType LongMargin = pPosition->YdPosition * pIndexPreOrder->LongMarginAmt;
				if (LongMargin > pIndexPreOrder->ActualMargin)
				{
					pIndexPreOrder->ActualMargin = LongMargin;
				}
			}
			else
			{
				pIndexPreOrder->LongYdPosition = 0;
			}
			
			pPosition = m_pDB->m_InvestorPositionFactory->findByBrkIDExIDInvIDInsDirHed(pOrder->BrokerID,pOrder->ExchangeID,\
				pOrder->InvestorID,pOrder->InstrumentID,D_Sell,pOrder->HedgeFlag);
			if (pPosition != NULL)
			{
				pIndexPreOrder->ShortYdPosition = pPosition->YdPosition;
				CMoneyType ShortMargin = pPosition->YdPosition * pIndexPreOrder->ShortMarginAmt;
				if (ShortMargin > pIndexPreOrder->ActualMargin)
				{
					pIndexPreOrder->ActualMargin = ShortMargin;
				}
			}
			else
			{
				pIndexPreOrder->ShortYdPosition = 0;
			}
		}

		//查找合约持仓限额
		CInvestorPositionLimit *pPostionLimit = m_pDB->m_InvestorPositionLimitFactory->findByBrkIDVstIDExIDIstID(pOrder->BrokerID,pOrder->InvestorID,\
													pOrder->ExchangeID,pOrder->InstrumentID);
		if (pPostionLimit != NULL)
		{
			pIndexPreOrder->LongPositionLimit = pPostionLimit->LongPosiLimit;
			pIndexPreOrder->ShortPositionLimit = pPostionLimit->ShortPosiLimit;
		}
		//查找品种持仓限额
		CInvestorPositionLimit *pProductLimit = m_pDB->m_InvestorPositionLimitFactory->findByBrkIDVstIDExIDIstID(pOrder->BrokerID,pOrder->InvestorID,\
			pOrder->ExchangeID,pIndexPreOrder->ProductID.getValue());
		if (pProductLimit != NULL)
		{
			pIndexPreOrder->linkVarietyPositionLimit(pProductLimit);
		}
	}
	else if (pIndexPreOrder->ProductClass == PC_Options)
	{
		//获取期权合约对应的期货合约的保证金率
		CInstrument *pUlyInstrument = m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pOrder->ExchangeID,pInstrument->UnderlyingInstrID);
		if (pUlyInstrument == NULL)
		{
			m_pErrorEngine->reportError(ERROR_INSTRUMENT_NOT_FOUND);
			return false;
		}
		//获取期货合约昨结算价
		CMarketData *pMarketData = m_pDB->m_MarketDataFactory->findByExchangeIDAndInstrumentID(pUlyInstrument->ExchangeID,pUlyInstrument->InstrumentID);
		if (pMarketData == NULL)
		{
			m_pErrorEngine->reportError(ERROR_CAN_NOT_FIND_INSTRUMENT_MARKET_DATA);
			return false;
		}
		pIndexPreOrder->PreSettlementPrice = pMarketData->PreSettlementPrice;
		//获取保证金率
		CInvestorMargin *pInvestorMargin = baseAlgorithms.getInvestorMargin(m_pDB,pUlyInstrument,pOrder->BrokerID,pOrder->InvestorID,pOrder->HedgeFlag);
		if (pInvestorMargin == NULL)
		{
			m_pErrorEngine->reportError(ERROR_NO_CLIENT_MARGIN_FEE_DATA);
			return false;
		}
		pIndexPreOrder->LongMarginRate = pInvestorMargin->LongMarginRate;
		pIndexPreOrder->LongMarginAmt = pInvestorMargin->LongMarginAmt;
		pIndexPreOrder->ShortMarginRate = pInvestorMargin->ShortMarginRate;
		pIndexPreOrder->ShortMarginAmt = pInvestorMargin->ShortMarginAmt;

		//获取手续费率
		CInvestorOptionFee *pInvestorOptionFee = baseAlgorithms.getInvestorOptionFee(m_pDB,pInstrument,pOrder->BrokerID,pOrder->InvestorID);
		if (pInvestorOptionFee == NULL)
		{
			m_pErrorEngine->reportError(ERROR_NO_CLIENT_MARGIN_FEE_DATA);
			return false;
		}
		pIndexPreOrder->OpenFeeRate = pInvestorOptionFee->OpenFeeRate;
		pIndexPreOrder->OpenFeeAmt = pInvestorOptionFee->OpenFeeAmt;
		pIndexPreOrder->OffsetFeeRate = pInvestorOptionFee->OffsetFeeRate;
		pIndexPreOrder->OffsetFeeAmt = pInvestorOptionFee->OffsetFeeAmt;
	}
	else
	{	
		//获取手续费率
		CInvestorFee *pInvestorFee = baseAlgorithms.getInvestorFee(m_pDB,pInstrument,pOrder->BrokerID,pOrder->InvestorID,pOrder->HedgeFlag);
		if (pInvestorFee == NULL)
		{
			m_pErrorEngine->reportError(ERROR_NO_CLIENT_MARGIN_FEE_DATA);
			return false;
		}
		pIndexPreOrder->OpenFeeRate = pInvestorFee->OpenFeeRate;
		pIndexPreOrder->OpenFeeAmt = pInvestorFee->OpenFeeAmt;
		pIndexPreOrder->OffsetFeeRate = pInvestorFee->OffsetFeeRate;
		pIndexPreOrder->OffsetFeeAmt = pInvestorFee->OffsetFeeAmt;
	}
	if (pOrder->SessionID !=0)
	{
		CMaxLocalID *pMaxLocalID = m_pDB->m_MaxLocalIDFactory->findByFrontIDSessionID(pOrder->FrontID,pOrder->SessionID);
		if (pMaxLocalID ==NULL)
		{
			m_pErrorEngine->reportError(ERROR_USER_NOT_LOGIN);
			return false;
		}
		pIndexPreOrder->linkMaxLocalID(pMaxLocalID);
	}
	
	CIndexPreOrder *pNewIndexPreOrder = m_pDB->m_IndexPreOrderFactory->add(pIndexPreOrder,NULL);
	pOrder->linkIndexPreOrder(pNewIndexPreOrder);
	return true;
}

