#include "baseAlgorithms.h"
#include "errorDefine.h"
#include "system.h"
#include "tradingTools.h"

extern const CClientIDType defaultClientID;
extern const CClientIDType defaultInvestorID;
extern const CProductIDType defaultProductID;
extern const CHedgeFlagType defaultHedgeFlag;

CBaseAlgorithms::CBaseAlgorithms()
{

}

CBaseAlgorithms::~CBaseAlgorithms()
{
	
}

CInvestorMargin * CBaseAlgorithms::getInvestorMargin(CMemoryDB *m_pDB,CInstrument *pInstrument,const CReadOnlyBrokerIDType&  BrokerID,const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag)
{
	if(NULL==pInstrument || NULL==m_pDB)
		return NULL;

	//首先使用客户号和合约号进行查找
    CInvestorMargin *pInvestorMargin = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,InvestorID,HedgeFlag);
	if(NULL == pInvestorMargin)
	{
		//其次使用产品号进行查找
		CInstrumentIDType ProductID = (CInstrumentIDType)pInstrument->ProductID;
		pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,InvestorID,HedgeFlag);
		if(NULL == pInvestorMargin)
		{
			//再次使用 '00000000' 和合约号进行查找
			pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,defaultClientID,HedgeFlag);
			if(NULL == pInvestorMargin)
			{
				//最后使用 '00000000' 和产品号进行查找
				pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
				if(NULL == pInvestorMargin)
				{
					///使用00000000和defaultProductID进行查找
					CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
					pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
					if (NULL == pInvestorMargin)
					{
						//交易所设置为default
						///使用00000000和defaultProductID进行查找
						CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
						CExchangeIDType defaultExchID = defaultProductID.getValue();
						pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,defaultExchID,ProductID,defaultClientID,HedgeFlag);					}
				}
			}
		}
	}
	if(NULL==pInvestorMargin)
	{
		//这里再没有找到，就要报错了
		REPORT_EVENT(LOG_CRITICAL,"getInvestorMargin","can not find investor margin data:BrokerID:[%s],InstrumentID:[%s],ClientID:[%s]",BrokerID.getValue(),pInstrument->InstrumentID.getValue(),InvestorID.getValue());
	}
	return pInvestorMargin;
}

vector<CInvestorMargin*> CBaseAlgorithms::getInvestorMargin(CMemoryDB *m_pDB,const CExchangeIDType& ExchangeID,
															const CProductIDType& ProductID,
															const CInstrumentIDType& InstrumentID, 
															const CBrokerIDType&  BrokerID,
															const CInvestorIDType&  InvestorID)
{
	vector<CInvestorMargin*> result;
	//首先使用客户号和合约号进行查找
    CInvestorMargin *pInvestorMargin = m_pDB->m_InvestorMarginFactory->startFindByBrkIDExIDIstIDVstID(BrokerID,ExchangeID,InstrumentID,InvestorID);
	for(;NULL!=pInvestorMargin;pInvestorMargin=m_pDB->m_InvestorMarginFactory->findNextByBrkIDExIDIstIDVstID())
	{
		result.push_back(pInvestorMargin);
	}
	m_pDB->m_InvestorMarginFactory->findNextByBrkIDExIDIstIDVstID();
	if(result.size()>0)
	{
		return result;
	}
	
	//其次使用产品号进行查找
	CInstrumentIDType TmpProductID = ProductID.getValue();
    pInvestorMargin = m_pDB->m_InvestorMarginFactory->startFindByBrkIDExIDIstIDVstID(BrokerID,ExchangeID,TmpProductID,InvestorID);
	for(;NULL!=pInvestorMargin;pInvestorMargin=m_pDB->m_InvestorMarginFactory->findNextByBrkIDExIDIstIDVstID())
	{
		result.push_back(pInvestorMargin);
	}
	m_pDB->m_InvestorMarginFactory->findNextByBrkIDExIDIstIDVstID();
	if(result.size()>0)
	{
		return result;
	}	
	
	//使用defaultProductID进行查找
	TmpProductID = defaultProductID.getValue();
    pInvestorMargin = m_pDB->m_InvestorMarginFactory->startFindByBrkIDExIDIstIDVstID(BrokerID,ExchangeID,TmpProductID,InvestorID);
	for(;NULL!=pInvestorMargin;pInvestorMargin=m_pDB->m_InvestorMarginFactory->findNextByBrkIDExIDIstIDVstID())
	{
		result.push_back(pInvestorMargin);
	}
	m_pDB->m_InvestorMarginFactory->findNextByBrkIDExIDIstIDVstID();
	if(result.size()>0)
	{
		return result;
	}	
	
	
	//使用00000000和合约号进行查找
    pInvestorMargin = m_pDB->m_InvestorMarginFactory->startFindByBrkIDExIDIstIDVstID(BrokerID,ExchangeID,InstrumentID,defaultInvestorID);
	for(;NULL!=pInvestorMargin;pInvestorMargin=m_pDB->m_InvestorMarginFactory->findNextByBrkIDExIDIstIDVstID())
	{
		result.push_back(pInvestorMargin);
	}
	m_pDB->m_InvestorMarginFactory->findNextByBrkIDExIDIstIDVstID();
	if(result.size()>0)
	{
		return result;
	}
	
	//使用00000000产品号进行查找
	TmpProductID = ProductID.getValue();
    pInvestorMargin = m_pDB->m_InvestorMarginFactory->startFindByBrkIDExIDIstIDVstID(BrokerID,ExchangeID,TmpProductID,defaultInvestorID);
	for(;NULL!=pInvestorMargin;pInvestorMargin=m_pDB->m_InvestorMarginFactory->findNextByBrkIDExIDIstIDVstID())
	{
		result.push_back(pInvestorMargin);
	}
	m_pDB->m_InvestorMarginFactory->findNextByBrkIDExIDIstIDVstID();
	if(result.size()>0)
	{
		return result;
	}	
	
	//使用00000000和defaultProductID进行查找
	TmpProductID = defaultProductID.getValue();
    pInvestorMargin = m_pDB->m_InvestorMarginFactory->startFindByBrkIDExIDIstIDVstID(BrokerID,ExchangeID,TmpProductID,defaultInvestorID);
	for(;NULL!=pInvestorMargin;pInvestorMargin=m_pDB->m_InvestorMarginFactory->findNextByBrkIDExIDIstIDVstID())
	{
		result.push_back(pInvestorMargin);
	}
	m_pDB->m_InvestorMarginFactory->findNextByBrkIDExIDIstIDVstID();
	if(result.size()>0)
	{
		return result;
	}	
	
	if(result.size()==0)
	{
		//这里再没有找到，就要报错了
		REPORT_EVENT(LOG_CRITICAL,"getInvestorMargin","can not find investor margin data:BrokerID:[%s],InstrumentID:[%s],ClientID:[%s]",BrokerID.getValue(),InstrumentID.getValue(),InvestorID.getValue());
	}
	return result;
}

CInvestorFee * CBaseAlgorithms::getInvestorFee(CMemoryDB *m_pDB,CInstrument *pInstrument,const CReadOnlyBrokerIDType&  BrokerID,const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag)
{
	if(NULL==pInstrument || NULL==m_pDB)
		return NULL;

	//首先使用合约号进行查找
    CInvestorFee *pInvestorFee = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,InvestorID,HedgeFlag);
	if(NULL == pInvestorFee)
	{
		//其次使用产品号进行查找
		CInstrumentIDType ProductID = (CInstrumentIDType)pInstrument->ProductID;
		pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,InvestorID,HedgeFlag);
		if(NULL == pInvestorFee)
		{
			//再次使用 '00000000' 和合约号进行查找
			pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,defaultClientID,HedgeFlag);
			if(NULL == pInvestorFee)
			{
				//最后使用 '00000000' 和产品号进行查找
				pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
				if(NULL == pInvestorFee)
				{
					///使用00000000和defaultProductID进行查找
					CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
					pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
					if(NULL == pInvestorFee)
					{
						///使用00000000和defaultProductID进行查找
						CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
						//交易所设置为default
						CExchangeIDType defaultExchID = defaultProductID.getValue();
						pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,defaultExchID,ProductID,defaultClientID,HedgeFlag);
					}
				}
			}
		}
	}
	if(NULL==pInvestorFee)
	{
		//这里再没有找到，就要报错了
		REPORT_EVENT(LOG_CRITICAL,"getInvestorFee","can not find investor fee data:BrokerID:[%s],InstrumentID:[%s],ClientID:[%s]",BrokerID.getValue(),pInstrument->InstrumentID.getValue(),InvestorID.getValue());
	}
	return pInvestorFee;
}

CPriceTickType CBaseAlgorithms::GetValuePrice(COrderPriceTypeType OrderPriceType,
									   CPriceType LimitPrice,
									   CInstrument *pInstrument)
{
	CPriceType basePrice = 0.0;
	//市价单、五档价、最优价按照昨结算价计算冻结保证金
	if( OPT_AnyPrice == OrderPriceType ||  OPT_FiveLevelPrice == OrderPriceType || OPT_BestPrice == OrderPriceType)  ////市价单按昨结 											
	{	
		basePrice = pInstrument->PreSettlementPrice;	
	}
	else
	{
		basePrice = LimitPrice;
	}
	return basePrice;
}

void CBaseAlgorithms::GetMargin(CVolumeType Volume,
									   CPriceType basePrice,
									   CDirectionType Direction,
									   COffsetFlagType OffsetFlag,
									   CVolumeMultipleType VolumeMultiple,
									   CInvestorMargin *pInvestorMargin,
									   CMoneyField*  theMoneyField)
{
	// 缺省保证金和手续费按比例
	theMoneyField->Margin = 0.0;
	if(OffsetFlag == OF_Open)
	{
		if(Direction == D_Buy)
		{
			theMoneyField->Margin = Volume*basePrice*VolumeMultiple*pInvestorMargin->LongMarginRate + Volume*pInvestorMargin->LongMarginAmt;
		}
		else
		{
			theMoneyField->Margin = Volume*basePrice*VolumeMultiple*pInvestorMargin->ShortMarginRate + Volume*pInvestorMargin->ShortMarginAmt;
		}
	}
}

CMoneyType CBaseAlgorithms::GetFee(CVolumeType Volume,
							 CPriceType basePrice,
							 CDirectionType Direction,
							 COffsetFlagType OffsetFlag,
							 CVolumeMultipleType VolumeMultiple,
							 CInvestorFee *pInvestorFee)
{
	// 缺省保证金和手续费按比例
	CMoneyType Fee = 0.0;
	if(OF_Open == OffsetFlag)  // 如果是开仓
	{
		Fee = Volume*basePrice*VolumeMultiple*pInvestorFee->OpenFeeRate + Volume*pInvestorFee->OpenFeeAmt;
	}
	else // 如果是平仓
	{
		//20151020 xuzh 平今和平昨手续费不一样
		switch(OffsetFlag)
		{
		case OF_CloseToday:
			{
				Fee = Volume*basePrice*VolumeMultiple*pInvestorFee->OTFeeRate + Volume*pInvestorFee->OTFeeAmt;
				break;
			}
		case OF_CloseYesterday:
		case OF_Close:
		default:
			{
				Fee = Volume*basePrice*VolumeMultiple*pInvestorFee->OffsetFeeRate + Volume*pInvestorFee->OffsetFeeAmt;
				break;
			}
		}
	}
	return Fee;
}

void CBaseAlgorithms::GetFee(CVolumeType Volume,
									   CPriceType basePrice,
									   CDirectionType Direction,
									   COffsetFlagType OffsetFlag,
									   CVolumeMultipleType VolumeMultiple,
									   CInvestorFee *pInvestorFee,
									   CMoneyField*  theMoneyField)
{
	// 缺省保证金和手续费按比例
	theMoneyField->Fee = 0.0;
	if(OF_Open == OffsetFlag)  // 如果是开仓
	{
		theMoneyField->Fee = Volume*basePrice*VolumeMultiple*pInvestorFee->OpenFeeRate + Volume*pInvestorFee->OpenFeeAmt;
	}
	else // 如果是平仓
	{
		//20151020 xuzh 平今和平昨手续费不一样
		switch(OffsetFlag)
		{
			case OF_CloseToday:
			{
				theMoneyField->Fee = Volume*basePrice*VolumeMultiple*pInvestorFee->OTFeeRate + Volume*pInvestorFee->OTFeeAmt;
				break;
			}
			case OF_CloseYesterday:
			case OF_Close:
			default:
			{
				theMoneyField->Fee = Volume*basePrice*VolumeMultiple*pInvestorFee->OffsetFeeRate + Volume*pInvestorFee->OffsetFeeAmt;
				break;
			}
		}
	}
}

void CBaseAlgorithms::GetPremium(CVolumeType Volume,
									   CPriceType basePrice,
									   CDirectionType Direction,
									   CVolumeMultipleType VolumeMultiple,
									   CMoneyField*  theMoneyField)
{
	theMoneyField->Premium = 0.0; 
	//计算权利金
	if(D_Buy  == Direction )   //如果是买
	{
	   theMoneyField->Premium = Volume*basePrice*VolumeMultiple;
	}
}

CInvestorAccount* CBaseAlgorithms::getInvestorAccount(CMemoryDB *m_pDB,CInstrument *pInstrument,const CReadOnlyBrokerIDType BrokerID,const CReadOnlyInvestorIDType InvestorID)
{
	return m_pDB->m_InvestorAccountFactory->findByBrokerIDInvestorID(BrokerID,InvestorID);
}
// bool CBaseAlgorithms::RightCheck(CErrorEngine *pErrorEngine,CTradingRightType TradingRightType,COffsetFlagType OffsetFlag)
// {
// 	if(TradingRightType.isNull())
// 	{
// 		return true;
// 	}
// 
// 	switch(TradingRightType)
// 	{
// 	case TR_Allow:
// 		{
// 			return true;
// 		}
// 	case TR_CloseOnly:
// 		{
// 			if(OF_Open==OffsetFlag)
// 			{
// 				pErrorEngine->reportError(ERROR_CLOSE_ONLY);
// 				return false;
// 			}
// 			return true;
// 		}
// 	case TR_Forbidden:
// 		{
// 			pErrorEngine->reportError(ERROR_NO_TRADING_RIGHT);
// 			return false;
// 		}
// 	default:
// 		{
// 			pErrorEngine->reportError(ERROR_ERROR);
// 			return false;
// 		}
// 	}
// 	
// 	return true;
// }
// 
// //查找客户交易权限
// CTradingRightType CBaseAlgorithms::getInvestorTradingRight(CMemoryDB *m_pDB,CBrokerIDType BrokerID,CExchangeIDType ExchangeID, CInvestorIDType InvestorID,CInstrumentIDType InstrumentID,CProductIDType ProductID)
// {
// 	///1 找（投资者，合约）	
// 	CInvestorIDType findInvestorID = InvestorID;
// 	CInstrumentIDType findInstrumentID = InstrumentID;
// 	CInvestorTradingRight *pInvestorTradingRight = m_pDB->m_InvestorTradingRightFactory->findByBrkExIDInsInv(BrokerID,ExchangeID,findInstrumentID,findInvestorID);
// 	if(NULL != pInvestorTradingRight)
// 	{
// 		return pInvestorTradingRight->TradingRight;
// 	}
// 	
// 	///2 找（投资者，产品）
// 	findInvestorID = InvestorID;
// 	findInstrumentID = ProductID;
// 	pInvestorTradingRight = m_pDB->m_InvestorTradingRightFactory->findByBrkExIDInsInv(BrokerID,ExchangeID,findInstrumentID,findInvestorID);
// 	if(NULL != pInvestorTradingRight)
// 	{
// 		return pInvestorTradingRight->TradingRight;
// 	}
// 	
// 	///3 找（投资者，缺省产品）
// 	findInvestorID = InvestorID;
// 	findInstrumentID = defaultProductID;
// 	pInvestorTradingRight = m_pDB->m_InvestorTradingRightFactory->findByBrkExIDInsInv(BrokerID,ExchangeID,findInstrumentID,findInvestorID);
// 	if(NULL != pInvestorTradingRight)
// 	{
// 		return pInvestorTradingRight->TradingRight;
// 	}
// 	
// 	///4 找（缺省投资者，合约）
// 	findInvestorID = defaultInvestorID;
// 	findInstrumentID = InstrumentID;
// 	pInvestorTradingRight = m_pDB->m_InvestorTradingRightFactory->findByBrkExIDInsInv(BrokerID,ExchangeID,findInstrumentID,findInvestorID);
// 	if(NULL != pInvestorTradingRight)
// 	{
// 		return pInvestorTradingRight->TradingRight;
// 	}
// 	
// 	///5 找（缺省投资者，产品）
// 	findInvestorID = defaultInvestorID;
// 	findInstrumentID = ProductID;
// 	pInvestorTradingRight = m_pDB->m_InvestorTradingRightFactory->findByBrkExIDInsInv(BrokerID,ExchangeID,findInstrumentID,findInvestorID);
// 	if(NULL != pInvestorTradingRight)
// 	{
// 		return pInvestorTradingRight->TradingRight;
// 	}
// 	
// 	///6 找（缺省投资者，缺省产品）
// 	findInvestorID = defaultInvestorID;
// 	findInstrumentID = defaultProductID;
// 	pInvestorTradingRight = m_pDB->m_InvestorTradingRightFactory->findByBrkExIDInsInv(BrokerID,ExchangeID,findInstrumentID,findInvestorID);
// 	if(NULL != pInvestorTradingRight)
// 	{
// 		return pInvestorTradingRight->TradingRight;
// 	}
// 	
// 	return TR_Allow;
// }
///计算可用资金
///@paramp  pInvestorAccount   资金账户
void CBaseAlgorithms::ChangeBalanceAndAvailable(CWriteableInvestorAccount* pWtbInvestorAccount)
{
	
	CMoneyType  theBalance = 0.0;
	CMoneyType  theAvailable = 0.0;
    
	theBalance  =   pWtbInvestorAccount->PreBalance  \
				+  pWtbInvestorAccount->Deposit   \
				-  pWtbInvestorAccount->Withdraw \
				+  pWtbInvestorAccount->CloseProfit \
				+  pWtbInvestorAccount->Premium \
				+  pWtbInvestorAccount->PositionProfit
				-  pWtbInvestorAccount->Fee
				-  pWtbInvestorAccount->OtherFee;
	
	pWtbInvestorAccount->DynamicRights = theBalance;
	if(pWtbInvestorAccount->DynamicRights != 0.0)
	{
		pWtbInvestorAccount->Risk = pWtbInvestorAccount->Margin/pWtbInvestorAccount->DynamicRights;
	}
	
	//20151216 huwp 如果浮盈不可用于开仓，则从总资金里扣除上面已经加入的值，浮亏默认从总资金里扣除
	//20160420 chengm 如果浮盈可用于开仓,结算准备金需要加上持仓盈亏
	if (!pWtbInvestorAccount->IsProfitCanUse && pWtbInvestorAccount->PositionProfit >0)
	{
		theBalance -= pWtbInvestorAccount->PositionProfit;
	}
    pWtbInvestorAccount->Balance  = theBalance;
    
	theAvailable    =   pWtbInvestorAccount->Balance \
		-   pWtbInvestorAccount->Margin \
		-   pWtbInvestorAccount->FrozenMargin \
		-   pWtbInvestorAccount->FrozenFee \
		-   pWtbInvestorAccount->FrozenPremium;
	
    pWtbInvestorAccount->Available  = theAvailable;
	return;
}
bool CBaseAlgorithms::CalcPositionProfit(CWriteableInvestorAccount *pInvestorAccount,CWriteableInvestorPosition *pInvestorPosition,CInstrument *pInstrument)
{
	if(NULL == pInvestorAccount || NULL == pInvestorPosition || NULL == pInstrument)
	{
		return false;
	}
	//如果找不到持仓对应的合约，或者找不到账号，就不算动态盈亏
	//持仓量为0的记录有可能存在
	//持仓量为0也应该计算，否则无法触发变动
	//如果是持仓量或者行情的合约乘数为0时，就直接将持仓盈亏赋值为0,wangwei,20130626
	CMoneyType PositionProfit=0.0;
	CMoneyType PositionProfitChange=0.0;
	
	if ( (pInvestorPosition->Direction == D_Net && pInvestorPosition->Position>=0) ||
		 pInvestorPosition->Direction == D_Buy )
	{
		PositionProfit = (pInvestorPosition->LastPrice*pInstrument->VolumeMultiple*pInvestorPosition->Position) - pInvestorPosition->PositionCost;
	}
	else if (pInvestorPosition->Direction == D_Net && pInvestorPosition->Position <0)
	{
		//卖净持仓
		PositionProfit = pInvestorPosition->PositionCost + (pInvestorPosition->LastPrice*pInstrument->VolumeMultiple*pInvestorPosition->Position);
	}
	else
	{
		//卖综合持仓
		PositionProfit = pInvestorPosition->PositionCost - (pInvestorPosition->LastPrice*pInstrument->VolumeMultiple*pInvestorPosition->Position);
	}
	
	PositionProfitChange = PositionProfit - pInvestorPosition->PositionProfit;
	pInvestorPosition->PositionProfit = PositionProfit;

	pInvestorAccount->PositionProfit += PositionProfitChange;
	return true;			
}

CInvestorMargin * CBaseAlgorithms::getInvestorStockMargin(CMemoryDB *m_pDB,CInstrument *pInstrument,const CReadOnlyBrokerIDType&  BrokerID,const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag)
{
	if(NULL==pInstrument || NULL==m_pDB)
		return NULL;

	//首先使用客户号和合约号进行查找
    CInvestorMargin *pInvestorMargin = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,InvestorID,HedgeFlag);
	if(NULL == pInvestorMargin)
	{
		//其次使用客户号和品种进行查找
		CInstrumentIDType ProductID = (CInstrumentIDType)pInstrument->ProductID;
		pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,InvestorID,HedgeFlag);
		if(NULL == pInvestorMargin)
		{
			//再次使用 '00000000' 和合约号进行查找
			pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,defaultClientID,HedgeFlag);
			if(NULL == pInvestorMargin)
			{
				//最后使用 '00000000' 和品种进行查找
				pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
				if(NULL == pInvestorMargin)
				{
					///使用00000000和defaultProductID进行查找
					CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
					pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
					if (NULL == pInvestorMargin)
					{
						//交易所设置为default
						///使用00000000和defaultProductID进行查找
						CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
						pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,defaultHedgeFlag);					
						if (NULL == pInvestorMargin)
						{
							//交易所设置为default
							///使用00000000和defaultProductID进行查找
							CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
							CExchangeIDType defaultExchID = defaultProductID.getValue();
							pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,defaultExchID,ProductID,defaultClientID,defaultHedgeFlag);					
						}
					}
				}
			}
		}
	}
	if(NULL==pInvestorMargin)
	{
		//这里再没有找到，就要报错了
		REPORT_EVENT(LOG_CRITICAL,"getInvestorMargin","can not find investor margin data:BrokerID:[%s],InstrumentID:[%s],ClientID:[%s]",BrokerID.getValue(),pInstrument->InstrumentID.getValue(),InvestorID.getValue());
	}
	return pInvestorMargin;
}

CInvestorFee * CBaseAlgorithms::getInvestorStockFee(CMemoryDB *m_pDB,CInstrument *pInstrument,const CReadOnlyBrokerIDType&  BrokerID,const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag)
{
	if(NULL==pInstrument || NULL==m_pDB)
		return NULL;

	//首先使用合约号进行查找
    CInvestorFee *pInvestorFee = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,InvestorID,HedgeFlag);
	if(NULL == pInvestorFee)
	{
		//其次使用产品号进行查找
		CInstrumentIDType ProductID = (CInstrumentIDType)pInstrument->ProductID;
		pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,InvestorID,HedgeFlag);
		if(NULL == pInvestorFee)
		{
			//再次使用 '00000000' 和合约号进行查找
			pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,defaultClientID,HedgeFlag);
			if(NULL == pInvestorFee)
			{
				//最后使用 '00000000' 和产品号进行查找
				pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
				if(NULL == pInvestorFee)
				{
					///使用00000000和defaultProductID进行查找
					CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
					pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
					if(NULL == pInvestorFee)
					{
						///使用00000000和defaultProductID进行查找
						CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
						pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,defaultHedgeFlag);
						if(NULL == pInvestorFee)
						{
							///使用00000000和defaultProductID进行查找
							CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
							//交易所设置为default
							CExchangeIDType defaultExchID = defaultProductID.getValue();
							pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,defaultExchID,ProductID,defaultClientID,defaultHedgeFlag);
						}
					}
				}
			}
		}
	}
	if(NULL==pInvestorFee)
	{
		//这里再没有找到，就要报错了
		REPORT_EVENT(LOG_CRITICAL,"getInvestorFee","can not find investor fee data:BrokerID:[%s],InstrumentID:[%s],ClientID:[%s]",BrokerID.getValue(),pInstrument->InstrumentID.getValue(),InvestorID.getValue());
	}
	return pInvestorFee;
}

CPriceTickType CBaseAlgorithms::GetStockValuePrice(CWriteablePreOrder* pOrder, CInstrument *pInstrument)
{
	CPriceType basePrice = 0.0;

	switch( atoi(pInstrument->ProductID.getValue()) )
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		basePrice = pOrder->LimitPrice + pInstrument->StrikePrice;//债券全价计算费用
		break;
	case 9:
		basePrice = 1;
		break;
	default:
		if( OPT_AnyPrice == pOrder->OrderPriceType ||  OPT_FiveLevelPrice == pOrder->OrderPriceType || OPT_BestPrice == pOrder->OrderPriceType)  
		{
			if (D_Buy == pOrder->Direction)
				basePrice = pInstrument->UpperLimitPrice;////买入市价单按涨停价
			else
				basePrice = pInstrument->LowerLimitPrice;////卖出市价单按跌停价
		}
		else
		{
			basePrice = pOrder->LimitPrice;
		}
		break;
	}

	return basePrice;
}

CVolumeType CBaseAlgorithms::GetStockValueVolume(CWriteablePreOrder* pOrder, CInstrument *pInstrument)
{
	CVolumeType baseVolume = 0;

	switch( atoi(pInstrument->ProductID.getValue()) )
	{
	case 9:
		baseVolume = pOrder->Volume  * pInstrument->VolumeMultiple * pInstrument->BasisPrice;
		break;
	default:
		baseVolume = pOrder->Volume * pInstrument->VolumeMultiple ;
		break;
	}

	return baseVolume;
}

/*印花税目前单向收费,所以借用pInvestorMargin表*/
void CBaseAlgorithms::GetStockYhs(CPriceType basePrice,
									   CVolumeType baseVolume,
									   CWriteablePreOrder* pOrder,
									   CInvestorMargin *pInvestorMargin,
									   CInstrument *pInstrument,
									   CMoneyField*  theMoneyField)
{
	// 缺省印花税按比例
	theMoneyField->Margin = 0.0;
	if(OF_Open == pOrder->OffsetFlag)
	{
		theMoneyField->Margin = baseVolume * basePrice * pInvestorMargin->LongMarginRate;//目前单向买不收
	}
	else
	{
		theMoneyField->Margin = baseVolume * basePrice * pInvestorMargin->ShortMarginRate;
	}
}

void CBaseAlgorithms::GetStockSxf(CPriceType basePrice,
									   CVolumeType baseVolume,
									   CWriteablePreOrder* pOrder,
									   CInvestorFee *pInvestorFee,
									   CInstrument *pInstrument,
									   CMoneyField*  theMoneyField)
{
	// 缺省手续费按比例
	theMoneyField->Fee = 0.0;
	if(OF_Open == pOrder->OffsetFlag)  // 如果是开仓
	{
		theMoneyField->Fee = baseVolume * basePrice * pInvestorFee->OpenFeeRate;
	}
	else // 如果是平仓
	{
		theMoneyField->Fee = baseVolume * basePrice * pInvestorFee->OffsetFeeRate;
	}
}

void CBaseAlgorithms::GetStockGhf(CPriceType basePrice,
									   CVolumeType baseVolume,
									   CWriteablePreOrder* pOrder,
									   CInvestorFee *pInvestorFee,
									   CInstrument *pInstrument,
									   CMoneyField*  theMoneyField)
{
	// 缺省过户费按比例
	theMoneyField->Premium = 0.0;

	theMoneyField->Premium = baseVolume * basePrice * pInvestorFee->OTFeeRate;
}


void CBaseAlgorithms::fromUserGetInvestors(CMemoryDB *m_pDB,const CBrokerIDType& brokerID,const CUserIDType& userID,InvestorIDVector& vInvestorID)
{
	int	count = 1;
	CInvestorIDType sInvestorID;
	
	CUserInvestorFactory *thisFactory = m_pDB->m_UserInvestorFactory;	
	CUserInvestor * pData = thisFactory->startFindAllByBrokerIDUserID(brokerID,userID);		
	while(pData)
	{	
		sInvestorID = pData->InvestorID;
		vInvestorID.push_back(sInvestorID);
		pData = thisFactory->findNextAllByBrokerIDUserID();
	}
	thisFactory->endFindAllByBrokerIDUserID();
	return ;
}

bool CBaseAlgorithms::CheckUserInvestor(CMemoryDB *m_pDB,const CBrokerIDType& brokerID,const CUserIDType& userID,const CInvestorIDType& investorID)
{
	CUserInvestorFactory *thisFactory = m_pDB->m_UserInvestorFactory;	
	CUserInvestor * pData = thisFactory->findByBrokerIDUserIDInvestorID(brokerID,userID,investorID);		
	if(pData)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CBaseAlgorithms::RightCheck(CErrorEngine *pErrorEngine,CTradingRightType TradingRightType,COffsetFlagType OffsetFlag)
{
	if(TradingRightType.isNull())
	{
		return true;
	}
	
	switch(TradingRightType)
	{
	case TR_Allow:
		{
			return true;
		}
	case TR_CloseOnly:
		{
			if(OF_Open==OffsetFlag)
			{
				pErrorEngine->reportError(ERROR_CLOSE_ONLY);
				return false;
			}
			return true;
		}
	case TR_Forbidden:
		{
			pErrorEngine->reportError(ERROR_NO_TRADING_RIGHT);
			return false;
		}
	default:
		{
			pErrorEngine->reportError(ERROR_ERROR);
			return false;
		}
	}
	
	return true;
}

CInvestorPosition* CBaseAlgorithms::GetInvestorPositon(CMemoryDB *m_pDB,CDirectionType Direction, 
													  COffsetFlagType OffsetFlag, 
													  CBrokerIDType BrokerID, 
													  CExchangeIDType ExchangeID, 
													  CInvestorIDType InvestorID,
													  CInstrumentIDType InstrumentID,
													  CHedgeFlagType HedgeFlag,
													  CTransaction *pTransaction)
{
	CInvestorPosition* pInvestorPosition;
	CDirectionType PositionDirection;

	//如果是买开仓或者卖平(强平)仓 
	if((OF_Open==OffsetFlag && D_Buy == Direction) || ( OF_Open!= OffsetFlag && D_Sell == Direction))
	{
		//查找多头持仓
		PositionDirection = D_Buy;
	}
	// 卖开仓或者买平（强平）仓
	else if((OF_Open ==OffsetFlag && D_Sell == Direction ) ||(( OF_Open !=OffsetFlag) && D_Buy == Direction))
	{
		//查找空头持仓
		PositionDirection = D_Sell; 
	}

	pInvestorPosition = m_pDB->m_InvestorPositionFactory->findByBrkIDExIDInvIDInsDirHed(BrokerID,ExchangeID,InvestorID,InstrumentID,PositionDirection,HedgeFlag);   
	//如果没有position，建立一个
	if(NULL == pInvestorPosition)
	{

		if( OF_Open != OffsetFlag )    //如果是平仓，出错
		{
			REPORT_EVENT(LOG_CRITICAL, "no　position but order is not open","In Line %d of File %s.\n",__LINE__,__FILE__);
			return NULL;
		}

		CWriteableInvestorPosition theWritableInvestorPosition;
		theWritableInvestorPosition.init();
		theWritableInvestorPosition.BrokerID       = BrokerID;
		theWritableInvestorPosition.InvestorID       = InvestorID;
		theWritableInvestorPosition.HedgeFlag       = HedgeFlag;
		theWritableInvestorPosition.ExchangeID     = ExchangeID;
		theWritableInvestorPosition.InstrumentID   = InstrumentID;		
		theWritableInvestorPosition.Direction		=PositionDirection;
		//寻找交易编码
		CClientTradingID *pClientTradingID = m_pDB->m_ClientTradingIDFactory->findByBrkIDExIDInvIDHdgFlg(BrokerID,ExchangeID,InvestorID,HedgeFlag);
		if(pClientTradingID!=NULL)
		{
			theWritableInvestorPosition.ParticipantID = pClientTradingID->ParticipantID;
			theWritableInvestorPosition.ClientID = pClientTradingID->ClientID;
			theWritableInvestorPosition.AccountID = pClientTradingID->AccountID;
			CInvestorAccount *pAccount = m_pDB->m_InvestorAccountFactory->findByBrokerIDInvestorID(BrokerID,InvestorID);
			if (pAccount != NULL)
			{
				theWritableInvestorPosition.Currency = pAccount->Currency;
			}
		}
		pInvestorPosition = m_pDB->m_InvestorPositionFactory->add(&theWritableInvestorPosition,pTransaction);
	}

	return pInvestorPosition;
}

double CBaseAlgorithms::GetPremium(CVolumeType baseVolume, CPriceType basePrice, CDirectionType Direction, CVolumeMultipleType VolumeMultiple)
{
	double Premium = 0.0; 
	//计算权利金
	if(D_Buy  == Direction )   //如果是买
	{
		Premium = basePrice*baseVolume*VolumeMultiple;
	}
	return Premium;
}

CInvestorOptionFee * CBaseAlgorithms::getInvestorOptionFee(CMemoryDB *m_pDB,CInstrument *pInstrument,const CReadOnlyBrokerIDType&  BrokerID,const CReadOnlyInvestorIDType&  InvestorID)
{
	if(NULL==pInstrument || NULL==m_pDB)
		return NULL;
	
	//首先使用合约号进行查找
    CInvestorOptionFee *pInvestorOptionFee = m_pDB->m_InvestorOptionFeeFactory->findByBrkIDExIDIstIDVstID(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,InvestorID);
	if(NULL == pInvestorOptionFee)
	{
		//其次使用产品号进行查找
		CInstrumentIDType ProductID = (CInstrumentIDType)pInstrument->ProductID;
		pInvestorOptionFee  = m_pDB->m_InvestorOptionFeeFactory->findByBrkIDExIDIstIDVstID(BrokerID,pInstrument->ExchangeID,ProductID,InvestorID);
		if(NULL == pInvestorOptionFee)
		{
			//再次使用 '00000000' 和合约号进行查找
			pInvestorOptionFee  = m_pDB->m_InvestorOptionFeeFactory->findByBrkIDExIDIstIDVstID(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,defaultClientID);
			if(NULL == pInvestorOptionFee)
			{
				//最后使用 '00000000' 和产品号进行查找
				pInvestorOptionFee  = m_pDB->m_InvestorOptionFeeFactory->findByBrkIDExIDIstIDVstID(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID);
				if(NULL == pInvestorOptionFee)
				{
					///使用00000000和defaultProductID进行查找
					CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
					pInvestorOptionFee  = m_pDB->m_InvestorOptionFeeFactory->findByBrkIDExIDIstIDVstID(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID);
					if(NULL == pInvestorOptionFee)
					{
						///使用00000000和defaultProductID进行查找
						CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
						//交易所设置为default
						CExchangeIDType defaultExchID = defaultProductID.getValue();
						pInvestorOptionFee  = m_pDB->m_InvestorOptionFeeFactory->findByBrkIDExIDIstIDVstID(BrokerID,defaultExchID,ProductID,defaultClientID);
					}
				}
			}
		}
	}
	if(NULL==pInvestorOptionFee)
	{
		//这里再没有找到，就要报错了
		REPORT_EVENT(LOG_CRITICAL,"getInvestorOptionFee","can not find investor fee data:BrokerID:[%s],InstrumentID:[%s],ClientID:[%s]",BrokerID.getValue(),pInstrument->InstrumentID.getValue(),InvestorID.getValue());
	}
	return pInvestorOptionFee;
}

void CBaseAlgorithms::GetOptionFee(CVolumeType Volume,
							 CPriceType basePrice,
							 CDirectionType Direction,
							 COffsetFlagType OffsetFlag,
							 CVolumeMultipleType VolumeMultiple,
							 CInvestorOptionFee *pInvestorOptionFee,
							 CMoneyField*  theMoneyField)
{
	// 缺省保证金和手续费按比例
	theMoneyField->Fee = 0.0;
	if(OF_Open == OffsetFlag)  // 如果是开仓
	{
		theMoneyField->Fee = Volume*basePrice*VolumeMultiple*pInvestorOptionFee->OpenFeeRate + Volume*pInvestorOptionFee->OpenFeeAmt;
	}
	else // 如果是平仓
	{
		//20151020 xuzh 平今和平昨手续费不一样
		switch(OffsetFlag)
		{
		case OF_CloseToday:
			{
				theMoneyField->Fee = Volume*basePrice*VolumeMultiple*pInvestorOptionFee->OTFeeRate + Volume*pInvestorOptionFee->OTFeeAmt;
				break;
			}
		case OF_CloseYesterday:
		case OF_Close:
		default:
			{
				theMoneyField->Fee = Volume*basePrice*VolumeMultiple*pInvestorOptionFee->OffsetFeeRate + Volume*pInvestorOptionFee->OffsetFeeAmt;
				break;
			}
		}
	}
}


CMoneyType CBaseAlgorithms::GetOptionFee(CVolumeType Volume,
								   CPriceType basePrice,
								   CDirectionType Direction,
								   COffsetFlagType OffsetFlag,
								   CVolumeMultipleType VolumeMultiple,
								   CInvestorOptionFee *pInvestorFee)
{
	// 缺省保证金和手续费按比例
	CMoneyType Fee = 0.0;
	if(OF_Open == OffsetFlag)  // 如果是开仓
	{
		Fee = Volume*basePrice*VolumeMultiple*pInvestorFee->OpenFeeRate + Volume*pInvestorFee->OpenFeeAmt;
	}
	else // 如果是平仓
	{
		//20151020 xuzh 平今和平昨手续费不一样
		switch(OffsetFlag)
		{
		case OF_CloseToday:
			{
				Fee = Volume*basePrice*VolumeMultiple*pInvestorFee->OTFeeRate + Volume*pInvestorFee->OTFeeAmt;
				break;
			}
		case OF_CloseYesterday:
		case OF_Close:
		default:
			{
				Fee = Volume*basePrice*VolumeMultiple*pInvestorFee->OffsetFeeRate + Volume*pInvestorFee->OffsetFeeAmt;
				break;
			}
		}
	}
	return Fee;
}

void CBaseAlgorithms::GetStrikeFee(CVolumeType Volume, 
									    CPriceType basePrice,
										 CVolumeMultipleType  VolumeMultiple,
										 CInvestorOptionFee *pInvestorOptionFee,
									     CMoneyField*  theMoneyField)
{
	//xuzh 20161209 如果没有设置手续费，按照0收取
	if(NULL==pInvestorOptionFee)
	{
		theMoneyField->Fee = 0.0;
	}
	
	// 缺省保证金和手续费按比例
	theMoneyField->Fee = Volume*(basePrice*VolumeMultiple*pInvestorOptionFee->StrikeFeeRate + pInvestorOptionFee->StrikeFeeAmt);
}





