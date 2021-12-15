#include "MoneyPosition.h"

CInitAccountTrigger *CMoneyPosition::m_initTrigger=NULL;
int CMoneyPosition::initCount=0;

CMoneyPosition::CMoneyPosition(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig)
{
	m_pDB = pDB;
	m_pErrorEngine = pErrorEngine;
	m_pConfig = pConfig;
	if (initCount==0)
	{
		m_initTrigger=new CInitAccountTrigger(m_pDB);
		m_pDB->m_DataSyncStatusFactory->addActionTrigger(m_initTrigger);		
	}
	initCount++;
}


///计算可用资金
///@paramp  pInvestorAccount   资金账户
void CMoneyPosition::ChangeBalanceAndAvailable(CWriteableInvestorAccount* pWtbInvestorAccount)
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
	                -   pWtbInvestorAccount->FrozenPremium \
					-   pWtbInvestorAccount->ManualFrozen;
    pWtbInvestorAccount->Available  = theAvailable;
	return;
}

void CInitAccountTrigger::afterUpdate(CDataSyncStatus *pDataSyncStatus)
{
	if (pDataSyncStatus->DataSyncStatus==DS_Synchronized)
	{		
		// 初始化资金账户信息
		CInvestorAccount *pInvestorAccount=m_DB->m_InvestorAccountFactory->getFirst();
		while(pInvestorAccount!=NULL)
		{
			CWriteableInvestorAccount theInvestorAccount;
			theInvestorAccount.init();
			m_DB->m_InvestorAccountFactory->retrieve(pInvestorAccount,&theInvestorAccount);
//			theInvestorAccount.PreAvailable=0.0;
			theInvestorAccount.ReleaseMargin=0.0;
			theInvestorAccount.CloseProfit=0.0;
//			theInvestorAccount.DynamicRights=0.0;
			theInvestorAccount.TodayInOut=0.0;
			theInvestorAccount.LongFrozenMargin=0.0;
			theInvestorAccount.ShortFrozenMargin=0.0;
			theInvestorAccount.TotalFrozenPos=0.0;
			theInvestorAccount.FrozenMargin=0.0;
			theInvestorAccount.Fee=0.0;
			theInvestorAccount.FrozenFee=0.0;
			theInvestorAccount.OtherFee=0.0;
			theInvestorAccount.Deposit=0.0;
			theInvestorAccount.Withdraw=0.0;
			theInvestorAccount.PositionProfit=0.0;
			theInvestorAccount.Premium=0.0;
			theInvestorAccount.Balance=theInvestorAccount.PreBalance;
			theInvestorAccount.DynamicRights=theInvestorAccount.PreBalance;
			theInvestorAccount.Available=theInvestorAccount.Balance-theInvestorAccount.Margin;
			m_DB->m_InvestorAccountFactory->update(pInvestorAccount,&theInvestorAccount);
			pInvestorAccount=m_DB->m_InvestorAccountFactory->getNext();
		}
		m_DB->m_InvestorAccountFactory->endGet();

//20150804 xuzh 客户持仓信息如果从交易所查询得来的情况，不需要再次初始化

// 		CClientPosition *pClientPosition = m_DB->m_ClientPositionFactory->getFirst();
// 	    while(pClientPosition != NULL)
// 		{
// 			CWriteableClientPosition theClientPosition;
// 			theClientPosition.init();
// 			m_DB->m_ClientPositionFactory->retrieve(pClientPosition,&theClientPosition);
//             
// 			CInstrument* pInstrument = m_DB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pClientPosition->ExchangeID,pClientPosition->InstrumentID);
//             if(NULL != pInstrument)
// 			{
// 				theClientPosition.PositionCost = fabs(theClientPosition.Position*pInstrument->PreSettlementPrice*pInstrument->VolumeMultiple);
// 				theClientPosition.FrozenMargin = 0.0;
// 				theClientPosition.FrozenPosition = 0.0;
// 				theClientPosition.FrozenPremium  = 0.0;
// 				theClientPosition.FrozenClosing  = 0.0;
// 				theClientPosition.LastOrderLocalID = "";
// 				theClientPosition.LastTradeID = "";
// 				m_DB->m_ClientPositionFactory->update(pClientPosition,&theClientPosition);								
// 			}
// 			else
// 			{
// 				REPORT_EVENT(LOG_CRITICAL,"uskernel","Can not Find Instrument [%s]  ExchangeID [%s] in MDB",pClientPosition->InstrumentID.getValue(),pClientPosition->ExchangeID.getValue());
// 			}
// 			pClientPosition = m_DB->m_ClientPositionFactory->getNext();
//	    }
//	    m_DB->m_ClientPositionFactory->endGet();

	}
}
