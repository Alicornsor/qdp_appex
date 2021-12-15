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

	//����ʹ�ÿͻ��źͺ�Լ�Ž��в���
    CInvestorMargin *pInvestorMargin = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,InvestorID,HedgeFlag);
	if(NULL == pInvestorMargin)
	{
		//���ʹ�ò�Ʒ�Ž��в���
		CInstrumentIDType ProductID = (CInstrumentIDType)pInstrument->ProductID;
		pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,InvestorID,HedgeFlag);
		if(NULL == pInvestorMargin)
		{
			//�ٴ�ʹ�� '00000000' �ͺ�Լ�Ž��в���
			pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,defaultClientID,HedgeFlag);
			if(NULL == pInvestorMargin)
			{
				//���ʹ�� '00000000' �Ͳ�Ʒ�Ž��в���
				pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
				if(NULL == pInvestorMargin)
				{
					///ʹ��00000000��defaultProductID���в���
					CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
					pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
					if (NULL == pInvestorMargin)
					{
						//����������Ϊdefault
						///ʹ��00000000��defaultProductID���в���
						CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
						CExchangeIDType defaultExchID = defaultProductID.getValue();
						pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,defaultExchID,ProductID,defaultClientID,HedgeFlag);					}
				}
			}
		}
	}
	if(NULL==pInvestorMargin)
	{
		//������û���ҵ�����Ҫ������
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
	//����ʹ�ÿͻ��źͺ�Լ�Ž��в���
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
	
	//���ʹ�ò�Ʒ�Ž��в���
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
	
	//ʹ��defaultProductID���в���
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
	
	
	//ʹ��00000000�ͺ�Լ�Ž��в���
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
	
	//ʹ��00000000��Ʒ�Ž��в���
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
	
	//ʹ��00000000��defaultProductID���в���
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
		//������û���ҵ�����Ҫ������
		REPORT_EVENT(LOG_CRITICAL,"getInvestorMargin","can not find investor margin data:BrokerID:[%s],InstrumentID:[%s],ClientID:[%s]",BrokerID.getValue(),InstrumentID.getValue(),InvestorID.getValue());
	}
	return result;
}

CInvestorFee * CBaseAlgorithms::getInvestorFee(CMemoryDB *m_pDB,CInstrument *pInstrument,const CReadOnlyBrokerIDType&  BrokerID,const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag)
{
	if(NULL==pInstrument || NULL==m_pDB)
		return NULL;

	//����ʹ�ú�Լ�Ž��в���
    CInvestorFee *pInvestorFee = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,InvestorID,HedgeFlag);
	if(NULL == pInvestorFee)
	{
		//���ʹ�ò�Ʒ�Ž��в���
		CInstrumentIDType ProductID = (CInstrumentIDType)pInstrument->ProductID;
		pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,InvestorID,HedgeFlag);
		if(NULL == pInvestorFee)
		{
			//�ٴ�ʹ�� '00000000' �ͺ�Լ�Ž��в���
			pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,defaultClientID,HedgeFlag);
			if(NULL == pInvestorFee)
			{
				//���ʹ�� '00000000' �Ͳ�Ʒ�Ž��в���
				pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
				if(NULL == pInvestorFee)
				{
					///ʹ��00000000��defaultProductID���в���
					CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
					pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
					if(NULL == pInvestorFee)
					{
						///ʹ��00000000��defaultProductID���в���
						CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
						//����������Ϊdefault
						CExchangeIDType defaultExchID = defaultProductID.getValue();
						pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,defaultExchID,ProductID,defaultClientID,HedgeFlag);
					}
				}
			}
		}
	}
	if(NULL==pInvestorFee)
	{
		//������û���ҵ�����Ҫ������
		REPORT_EVENT(LOG_CRITICAL,"getInvestorFee","can not find investor fee data:BrokerID:[%s],InstrumentID:[%s],ClientID:[%s]",BrokerID.getValue(),pInstrument->InstrumentID.getValue(),InvestorID.getValue());
	}
	return pInvestorFee;
}

CPriceTickType CBaseAlgorithms::GetValuePrice(COrderPriceTypeType OrderPriceType,
									   CPriceType LimitPrice,
									   CInstrument *pInstrument)
{
	CPriceType basePrice = 0.0;
	//�м۵����嵵�ۡ����ż۰��������ۼ��㶳�ᱣ֤��
	if( OPT_AnyPrice == OrderPriceType ||  OPT_FiveLevelPrice == OrderPriceType || OPT_BestPrice == OrderPriceType)  ////�м۵������ 											
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
	// ȱʡ��֤��������Ѱ�����
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
	// ȱʡ��֤��������Ѱ�����
	CMoneyType Fee = 0.0;
	if(OF_Open == OffsetFlag)  // ����ǿ���
	{
		Fee = Volume*basePrice*VolumeMultiple*pInvestorFee->OpenFeeRate + Volume*pInvestorFee->OpenFeeAmt;
	}
	else // �����ƽ��
	{
		//20151020 xuzh ƽ���ƽ�������Ѳ�һ��
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
	// ȱʡ��֤��������Ѱ�����
	theMoneyField->Fee = 0.0;
	if(OF_Open == OffsetFlag)  // ����ǿ���
	{
		theMoneyField->Fee = Volume*basePrice*VolumeMultiple*pInvestorFee->OpenFeeRate + Volume*pInvestorFee->OpenFeeAmt;
	}
	else // �����ƽ��
	{
		//20151020 xuzh ƽ���ƽ�������Ѳ�һ��
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
	//����Ȩ����
	if(D_Buy  == Direction )   //�������
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
// //���ҿͻ�����Ȩ��
// CTradingRightType CBaseAlgorithms::getInvestorTradingRight(CMemoryDB *m_pDB,CBrokerIDType BrokerID,CExchangeIDType ExchangeID, CInvestorIDType InvestorID,CInstrumentIDType InstrumentID,CProductIDType ProductID)
// {
// 	///1 �ң�Ͷ���ߣ���Լ��	
// 	CInvestorIDType findInvestorID = InvestorID;
// 	CInstrumentIDType findInstrumentID = InstrumentID;
// 	CInvestorTradingRight *pInvestorTradingRight = m_pDB->m_InvestorTradingRightFactory->findByBrkExIDInsInv(BrokerID,ExchangeID,findInstrumentID,findInvestorID);
// 	if(NULL != pInvestorTradingRight)
// 	{
// 		return pInvestorTradingRight->TradingRight;
// 	}
// 	
// 	///2 �ң�Ͷ���ߣ���Ʒ��
// 	findInvestorID = InvestorID;
// 	findInstrumentID = ProductID;
// 	pInvestorTradingRight = m_pDB->m_InvestorTradingRightFactory->findByBrkExIDInsInv(BrokerID,ExchangeID,findInstrumentID,findInvestorID);
// 	if(NULL != pInvestorTradingRight)
// 	{
// 		return pInvestorTradingRight->TradingRight;
// 	}
// 	
// 	///3 �ң�Ͷ���ߣ�ȱʡ��Ʒ��
// 	findInvestorID = InvestorID;
// 	findInstrumentID = defaultProductID;
// 	pInvestorTradingRight = m_pDB->m_InvestorTradingRightFactory->findByBrkExIDInsInv(BrokerID,ExchangeID,findInstrumentID,findInvestorID);
// 	if(NULL != pInvestorTradingRight)
// 	{
// 		return pInvestorTradingRight->TradingRight;
// 	}
// 	
// 	///4 �ң�ȱʡͶ���ߣ���Լ��
// 	findInvestorID = defaultInvestorID;
// 	findInstrumentID = InstrumentID;
// 	pInvestorTradingRight = m_pDB->m_InvestorTradingRightFactory->findByBrkExIDInsInv(BrokerID,ExchangeID,findInstrumentID,findInvestorID);
// 	if(NULL != pInvestorTradingRight)
// 	{
// 		return pInvestorTradingRight->TradingRight;
// 	}
// 	
// 	///5 �ң�ȱʡͶ���ߣ���Ʒ��
// 	findInvestorID = defaultInvestorID;
// 	findInstrumentID = ProductID;
// 	pInvestorTradingRight = m_pDB->m_InvestorTradingRightFactory->findByBrkExIDInsInv(BrokerID,ExchangeID,findInstrumentID,findInvestorID);
// 	if(NULL != pInvestorTradingRight)
// 	{
// 		return pInvestorTradingRight->TradingRight;
// 	}
// 	
// 	///6 �ң�ȱʡͶ���ߣ�ȱʡ��Ʒ��
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
///��������ʽ�
///@paramp  pInvestorAccount   �ʽ��˻�
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
	
	//20151216 huwp �����ӯ�������ڿ��֣�������ʽ���۳������Ѿ������ֵ������Ĭ�ϴ����ʽ���۳�
	//20160420 chengm �����ӯ�����ڿ���,����׼������Ҫ���ϳֲ�ӯ��
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
	//����Ҳ����ֲֶ�Ӧ�ĺ�Լ�������Ҳ����˺ţ��Ͳ��㶯̬ӯ��
	//�ֲ���Ϊ0�ļ�¼�п��ܴ���
	//�ֲ���Ϊ0ҲӦ�ü��㣬�����޷������䶯
	//����ǳֲ�����������ĺ�Լ����Ϊ0ʱ����ֱ�ӽ��ֲ�ӯ����ֵΪ0,wangwei,20130626
	CMoneyType PositionProfit=0.0;
	CMoneyType PositionProfitChange=0.0;
	
	if ( (pInvestorPosition->Direction == D_Net && pInvestorPosition->Position>=0) ||
		 pInvestorPosition->Direction == D_Buy )
	{
		PositionProfit = (pInvestorPosition->LastPrice*pInstrument->VolumeMultiple*pInvestorPosition->Position) - pInvestorPosition->PositionCost;
	}
	else if (pInvestorPosition->Direction == D_Net && pInvestorPosition->Position <0)
	{
		//�����ֲ�
		PositionProfit = pInvestorPosition->PositionCost + (pInvestorPosition->LastPrice*pInstrument->VolumeMultiple*pInvestorPosition->Position);
	}
	else
	{
		//���ۺϳֲ�
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

	//����ʹ�ÿͻ��źͺ�Լ�Ž��в���
    CInvestorMargin *pInvestorMargin = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,InvestorID,HedgeFlag);
	if(NULL == pInvestorMargin)
	{
		//���ʹ�ÿͻ��ź�Ʒ�ֽ��в���
		CInstrumentIDType ProductID = (CInstrumentIDType)pInstrument->ProductID;
		pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,InvestorID,HedgeFlag);
		if(NULL == pInvestorMargin)
		{
			//�ٴ�ʹ�� '00000000' �ͺ�Լ�Ž��в���
			pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,defaultClientID,HedgeFlag);
			if(NULL == pInvestorMargin)
			{
				//���ʹ�� '00000000' ��Ʒ�ֽ��в���
				pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
				if(NULL == pInvestorMargin)
				{
					///ʹ��00000000��defaultProductID���в���
					CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
					pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
					if (NULL == pInvestorMargin)
					{
						//����������Ϊdefault
						///ʹ��00000000��defaultProductID���в���
						CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
						pInvestorMargin  = m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,defaultHedgeFlag);					
						if (NULL == pInvestorMargin)
						{
							//����������Ϊdefault
							///ʹ��00000000��defaultProductID���в���
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
		//������û���ҵ�����Ҫ������
		REPORT_EVENT(LOG_CRITICAL,"getInvestorMargin","can not find investor margin data:BrokerID:[%s],InstrumentID:[%s],ClientID:[%s]",BrokerID.getValue(),pInstrument->InstrumentID.getValue(),InvestorID.getValue());
	}
	return pInvestorMargin;
}

CInvestorFee * CBaseAlgorithms::getInvestorStockFee(CMemoryDB *m_pDB,CInstrument *pInstrument,const CReadOnlyBrokerIDType&  BrokerID,const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag)
{
	if(NULL==pInstrument || NULL==m_pDB)
		return NULL;

	//����ʹ�ú�Լ�Ž��в���
    CInvestorFee *pInvestorFee = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,InvestorID,HedgeFlag);
	if(NULL == pInvestorFee)
	{
		//���ʹ�ò�Ʒ�Ž��в���
		CInstrumentIDType ProductID = (CInstrumentIDType)pInstrument->ProductID;
		pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,InvestorID,HedgeFlag);
		if(NULL == pInvestorFee)
		{
			//�ٴ�ʹ�� '00000000' �ͺ�Լ�Ž��в���
			pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,defaultClientID,HedgeFlag);
			if(NULL == pInvestorFee)
			{
				//���ʹ�� '00000000' �Ͳ�Ʒ�Ž��в���
				pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
				if(NULL == pInvestorFee)
				{
					///ʹ��00000000��defaultProductID���в���
					CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
					pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,HedgeFlag);
					if(NULL == pInvestorFee)
					{
						///ʹ��00000000��defaultProductID���в���
						CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
						pInvestorFee  = m_pDB->m_InvestorFeeFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID,defaultHedgeFlag);
						if(NULL == pInvestorFee)
						{
							///ʹ��00000000��defaultProductID���в���
							CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
							//����������Ϊdefault
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
		//������û���ҵ�����Ҫ������
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
		basePrice = pOrder->LimitPrice + pInstrument->StrikePrice;//ծȯȫ�ۼ������
		break;
	case 9:
		basePrice = 1;
		break;
	default:
		if( OPT_AnyPrice == pOrder->OrderPriceType ||  OPT_FiveLevelPrice == pOrder->OrderPriceType || OPT_BestPrice == pOrder->OrderPriceType)  
		{
			if (D_Buy == pOrder->Direction)
				basePrice = pInstrument->UpperLimitPrice;////�����м۵�����ͣ��
			else
				basePrice = pInstrument->LowerLimitPrice;////�����м۵�����ͣ��
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

/*ӡ��˰Ŀǰ�����շ�,���Խ���pInvestorMargin��*/
void CBaseAlgorithms::GetStockYhs(CPriceType basePrice,
									   CVolumeType baseVolume,
									   CWriteablePreOrder* pOrder,
									   CInvestorMargin *pInvestorMargin,
									   CInstrument *pInstrument,
									   CMoneyField*  theMoneyField)
{
	// ȱʡӡ��˰������
	theMoneyField->Margin = 0.0;
	if(OF_Open == pOrder->OffsetFlag)
	{
		theMoneyField->Margin = baseVolume * basePrice * pInvestorMargin->LongMarginRate;//Ŀǰ��������
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
	// ȱʡ�����Ѱ�����
	theMoneyField->Fee = 0.0;
	if(OF_Open == pOrder->OffsetFlag)  // ����ǿ���
	{
		theMoneyField->Fee = baseVolume * basePrice * pInvestorFee->OpenFeeRate;
	}
	else // �����ƽ��
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
	// ȱʡ�����Ѱ�����
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

	//������򿪲ֻ�����ƽ(ǿƽ)�� 
	if((OF_Open==OffsetFlag && D_Buy == Direction) || ( OF_Open!= OffsetFlag && D_Sell == Direction))
	{
		//���Ҷ�ͷ�ֲ�
		PositionDirection = D_Buy;
	}
	// �����ֻ�����ƽ��ǿƽ����
	else if((OF_Open ==OffsetFlag && D_Sell == Direction ) ||(( OF_Open !=OffsetFlag) && D_Buy == Direction))
	{
		//���ҿ�ͷ�ֲ�
		PositionDirection = D_Sell; 
	}

	pInvestorPosition = m_pDB->m_InvestorPositionFactory->findByBrkIDExIDInvIDInsDirHed(BrokerID,ExchangeID,InvestorID,InstrumentID,PositionDirection,HedgeFlag);   
	//���û��position������һ��
	if(NULL == pInvestorPosition)
	{

		if( OF_Open != OffsetFlag )    //�����ƽ�֣�����
		{
			REPORT_EVENT(LOG_CRITICAL, "no��position but order is not open","In Line %d of File %s.\n",__LINE__,__FILE__);
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
		//Ѱ�ҽ��ױ���
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
	//����Ȩ����
	if(D_Buy  == Direction )   //�������
	{
		Premium = basePrice*baseVolume*VolumeMultiple;
	}
	return Premium;
}

CInvestorOptionFee * CBaseAlgorithms::getInvestorOptionFee(CMemoryDB *m_pDB,CInstrument *pInstrument,const CReadOnlyBrokerIDType&  BrokerID,const CReadOnlyInvestorIDType&  InvestorID)
{
	if(NULL==pInstrument || NULL==m_pDB)
		return NULL;
	
	//����ʹ�ú�Լ�Ž��в���
    CInvestorOptionFee *pInvestorOptionFee = m_pDB->m_InvestorOptionFeeFactory->findByBrkIDExIDIstIDVstID(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,InvestorID);
	if(NULL == pInvestorOptionFee)
	{
		//���ʹ�ò�Ʒ�Ž��в���
		CInstrumentIDType ProductID = (CInstrumentIDType)pInstrument->ProductID;
		pInvestorOptionFee  = m_pDB->m_InvestorOptionFeeFactory->findByBrkIDExIDIstIDVstID(BrokerID,pInstrument->ExchangeID,ProductID,InvestorID);
		if(NULL == pInvestorOptionFee)
		{
			//�ٴ�ʹ�� '00000000' �ͺ�Լ�Ž��в���
			pInvestorOptionFee  = m_pDB->m_InvestorOptionFeeFactory->findByBrkIDExIDIstIDVstID(BrokerID,pInstrument->ExchangeID,pInstrument->InstrumentID,defaultClientID);
			if(NULL == pInvestorOptionFee)
			{
				//���ʹ�� '00000000' �Ͳ�Ʒ�Ž��в���
				pInvestorOptionFee  = m_pDB->m_InvestorOptionFeeFactory->findByBrkIDExIDIstIDVstID(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID);
				if(NULL == pInvestorOptionFee)
				{
					///ʹ��00000000��defaultProductID���в���
					CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
					pInvestorOptionFee  = m_pDB->m_InvestorOptionFeeFactory->findByBrkIDExIDIstIDVstID(BrokerID,pInstrument->ExchangeID,ProductID,defaultClientID);
					if(NULL == pInvestorOptionFee)
					{
						///ʹ��00000000��defaultProductID���в���
						CInstrumentIDType ProductID = (CInstrumentIDType)defaultProductID;
						//����������Ϊdefault
						CExchangeIDType defaultExchID = defaultProductID.getValue();
						pInvestorOptionFee  = m_pDB->m_InvestorOptionFeeFactory->findByBrkIDExIDIstIDVstID(BrokerID,defaultExchID,ProductID,defaultClientID);
					}
				}
			}
		}
	}
	if(NULL==pInvestorOptionFee)
	{
		//������û���ҵ�����Ҫ������
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
	// ȱʡ��֤��������Ѱ�����
	theMoneyField->Fee = 0.0;
	if(OF_Open == OffsetFlag)  // ����ǿ���
	{
		theMoneyField->Fee = Volume*basePrice*VolumeMultiple*pInvestorOptionFee->OpenFeeRate + Volume*pInvestorOptionFee->OpenFeeAmt;
	}
	else // �����ƽ��
	{
		//20151020 xuzh ƽ���ƽ�������Ѳ�һ��
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
	// ȱʡ��֤��������Ѱ�����
	CMoneyType Fee = 0.0;
	if(OF_Open == OffsetFlag)  // ����ǿ���
	{
		Fee = Volume*basePrice*VolumeMultiple*pInvestorFee->OpenFeeRate + Volume*pInvestorFee->OpenFeeAmt;
	}
	else // �����ƽ��
	{
		//20151020 xuzh ƽ���ƽ�������Ѳ�һ��
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
	//xuzh 20161209 ���û�����������ѣ�����0��ȡ
	if(NULL==pInvestorOptionFee)
	{
		theMoneyField->Fee = 0.0;
	}
	
	// ȱʡ��֤��������Ѱ�����
	theMoneyField->Fee = Volume*(basePrice*VolumeMultiple*pInvestorOptionFee->StrikeFeeRate + pInvestorOptionFee->StrikeFeeAmt);
}





