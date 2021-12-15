/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file COrderInsertRules.h
///@brief实现了类COrderInsertRules
///@history 
///20060113	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "HandleNotify.h"
#include "tradingTools.h"
#include "BaseCheck.h"
#include "MoneyPosition.h"
#include "ExchangeLinkManager.h"
#include "system.h"

extern CExchangeLinkManager* g_pExchangeLinkManager;

CHandleNotify::CHandleNotify(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult)
:CRuleHandleBase(pDB,pErrorEngine,pConfig,pTradeResult)
{
	m_pErrorEngine   = pErrorEngine;
	m_pConfig        = pConfig;
	m_pPubMessage    = new CXTPPackage();
	m_pPubMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE, XTPHLEN);
	m_LastCalcDynamiceProfitTime.init();
	m_nCalcDynamicProfitTimeCycle=2000;
	m_bCalcDynamicProfitSwitch=false;
	char *pszCalcDynamicProfitTimeCycle=m_pConfig->getConfig("CalcDynamicProfitTimeCycle");
	if (strcmp(pszCalcDynamicProfitTimeCycle,""))
	{
		m_nCalcDynamicProfitTimeCycle = atoi(pszCalcDynamicProfitTimeCycle);
	}
	char *pszCalcDynamicProfitSwitch=m_pConfig->getConfig("CalcDynamicProfitSwitch");
	if (!strcmp(pszCalcDynamicProfitSwitch,"yes"))
	{
		m_bCalcDynamicProfitSwitch = true;
	}
	if (initCount==0)
	{
		m_initTrigger=new CInitCheckTrigger(pDB,m_pConfig);
		pDB->m_SystemStatusFactory->addActionTrigger(m_initTrigger);		
	}
	initCount++;

	m_pFutureMoneyPosition = new CFutureMoneyPosition(pDB,pErrorEngine,pConfig);
}

// bool CHandleNotify::HandleSeatLoginSuccess(CLoginInfoField *pLoginInfo,const TSessionRef &sessionRef,CTransaction *pTransaction,CSeatIDType  &GetSeatID,COrderLocalIDType  &GetOrderLocalID,vector<CWriteablePreOrder*> &PreOrders)
// {
//     bool bSuccess = true;
//     CSeat* pTSeat = m_pDB->m_SeatFactory->findByExchangeIDParticipantIDSeatID(pLoginInfo->ExchangeID,pLoginInfo->ParticipantID,pLoginInfo->SeatID);
// 	if (pTSeat==NULL)
// 	{
// 		printf("CHandleNotify::HandleSeatDisconnected 找不到 ExchangeID=[%s],SeatID=[%s] 对应的席位状态记录\n",pLoginInfo->ExchangeID.getValue(),pLoginInfo->SeatID.getValue());
// 		return false;
// 	}
// 	// longqy 处理席位断线重新连接，在途订单需要从预委托表中删除
// 	int	nOldLocalID = 0;
// 	int nNewLocalID = 0;
// 	if(pLoginInfo->OrderLocalID.isNull())
// 	{	// 最初登录到交易所时，没有报单，则最大本地报单号为空。此时允许删除丢失的在途订单。
// 		nNewLocalID = 0;
// 	}else
// 	{
// 		nNewLocalID = atoi(pLoginInfo->OrderLocalID);
// 	}
// 	if(pTSeat->OrderLocalID.isNull())
// 	{
// 		nOldLocalID = -1;
// 	}else
// 	{
// 		nOldLocalID = atoi(pTSeat->OrderLocalID);
// 	}
// 	char buf[256];
// 	if(( nNewLocalID > -1) && (nOldLocalID >0) && (nOldLocalID > nNewLocalID ))
// 	{	// 有订单被交易所拒绝
// 		for(int i=nNewLocalID +1;i<= nOldLocalID; i++)
// 		{
// 			sprintf(buf,"%012d",i);
// 			COrderLocalIDType failedOrderID=buf;
// 			int bRemove = -1;
// 			bRemove = RemoveFaildPreOrder(pLoginInfo->ExchangeID,pLoginInfo->SeatID,failedOrderID,pTransaction,PreOrders);
// 
// 			if( bRemove > 0)
// 			{
// 				m_pErrorEngine->reportError(ERROR_ORDER_LOST_ONTHEWAY);
// 								
// 				GetSeatID = pLoginInfo->SeatID;
// 				GetOrderLocalID = failedOrderID;
// 			}
// 		}
// 	}
// 	
// 	int nMaxLocalID = (nOldLocalID > nNewLocalID ) ? nOldLocalID : nNewLocalID;
//     CWriteableSeat theSeat;
// 	theSeat.init();
// 	CopySeatEntity(&theSeat,pTSeat);
// 	theSeat.ExchangeID = pLoginInfo->ExchangeID;
// 	theSeat.SeatID = pLoginInfo->SeatID;
// 	//theSeat.OrderLocalID = pLoginInfo->OrderLocalID;
// 	// 本地报单号取为交易所确认的号码，与本地的号码的最大值，再加1 。确保不能重号码
// 	sprintf(buf,"%012d",++nMaxLocalID);
// 	theSeat.OrderLocalID = buf;
// 	theSeat.SeatStatus = SS_Login;//席位已经就绪 by wangwei
// 	m_pDB->m_SeatFactory->addOrUpdate(pTSeat,&theSeat,NULL);
// 	return bSuccess;
// }
/*	把时钟同步数据包中的时间，同步到内存数据库表 CurrentTime 中去。这样，在数据流反演的时候，用的时间，
//	就是当时实际交易的时间。表 CurrentTime 中实际上只有一条时间记录，包括了当前时间和上一次的时间。
//	定时触发计算动态盈亏，也是根据这个时间来做时钟的，而不是用计算机本地的时间。 longqy 20130822 。
*/
bool CHandleNotify::HandleNtfTimeSync(CCurrentTimeField *pCurrTime,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	CWriteableCurrentTime theWriteableCurrentTime;
	theWriteableCurrentTime.init();
	
	theWriteableCurrentTime.CurrDate=pCurrTime->CurrDate;
	theWriteableCurrentTime.CurrMillisec=pCurrTime->CurrMillisec;
	theWriteableCurrentTime.CurrTime=pCurrTime->CurrTime;	
	setCurrentTime(m_pDB,&theWriteableCurrentTime,pTransaction);
	if (m_bCalcDynamicProfitSwitch)
	{
		if (GetTimeDiff(&theWriteableCurrentTime)>=m_nCalcDynamicProfitTimeCycle ||
			theWriteableCurrentTime.CurrDate>m_LastCalcDynamiceProfitTime.CurrDate)
		{		
			SendQryMarketData();
			CopyCurrentTimeEntity(&m_LastCalcDynamiceProfitTime,pCurrTime);
		}
	}
	return true;
}

/*	收到最新的行情数据，目前行情是一档行情，把行情数据保存到内存数据库表 MarketData 中。
//  表 MarketData 中的每个合约只有一条记录，是把新的数据更新或者增加到这个表中。
*/
bool CHandleNotify::HandleMarketDataLastMatch(CMarketDataLastMatchField *marketDataLastMatchedField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	bool bSuccess = true;
	CExchangeIDType ExchangeID=marketDataLastMatchedField->ExchangeID;	
	CInstrumentIDType InstrumentID=marketDataLastMatchedField->InstrumentID;
	CWriteableMarketData theWriteableMarketData;		
	theWriteableMarketData.init();
	theWriteableMarketData.ExchangeID=ExchangeID;
	theWriteableMarketData.InstrumentID=InstrumentID;
	theWriteableMarketData.LastPrice=marketDataLastMatchedField->LastPrice;
    theWriteableMarketData.Volume=marketDataLastMatchedField->Volume;
	
    CMarketData* pMarketDataLastMatched = m_pDB->m_MarketDataFactory->findByExchangeIDAndInstrumentID(ExchangeID,InstrumentID);	
	if(pMarketDataLastMatched != NULL)
	{
		m_pDB->m_MarketDataFactory->retrieve(pMarketDataLastMatched,&theWriteableMarketData);
        theWriteableMarketData.LastPrice = marketDataLastMatchedField->LastPrice;
        theWriteableMarketData.Volume    = marketDataLastMatchedField->Volume;
		m_pDB->m_MarketDataFactory->update(pMarketDataLastMatched,&theWriteableMarketData,pTransaction);
	}
	else
	{
		m_pDB->m_MarketDataFactory->add(&theWriteableMarketData,pTransaction);
	}
	return bSuccess;
}

//账户持仓盈亏
//wangwei,20130502, 支持多会员的改造
struct stBrokerAccount
{
	CBrokerIDType BrokerID;
	CAccountIDType AccountID;
	//必须重载运算符，否则无法用到map中去
	bool operator < (const stBrokerAccount& stBrkrAccnt) const
	{
		if (BrokerID<stBrkrAccnt.BrokerID)
		{
			return true;
		}
		else if (BrokerID>stBrkrAccnt.BrokerID)
		{
			return false;
		}
		else
		{
			if (AccountID<stBrkrAccnt.AccountID)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	bool operator > (const stBrokerAccount& stBrkrAccnt) const
	{
		if (BrokerID>stBrkrAccnt.BrokerID)
		{
			return true;
		}
		else if (BrokerID<stBrkrAccnt.BrokerID)
		{
			return false;
		}
		else
		{
			if (AccountID>stBrkrAccnt.AccountID)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
};
typedef map<stBrokerAccount,CMoneyType> mpAcntPosPrft;

void CHandleNotify::SendQryMarketData(bool bQuerySettlementPrice)
{
	//根据持仓情况，找到持仓的所有合约，发出查询请求
	CSendInstrumentMap SendInstrumentMap;
	CInvestorPosition* pInvestorPosition = m_pDB->m_InvestorPositionFactory->getFirst();
	while(NULL != pInvestorPosition)
	{
		//原本考虑到有持仓才发送行情查询请求
		//鉴于1、结算价的查询只要有成交就需要查询行情，和持仓量无关
		//    2、一个投资者没有持仓、其他如果有持仓，也需要发送请求，在投资者多的情况下，合约查询的数目可能不会有太多改变
		//所以，只要有持仓记录存在就查询行情
		CInstrument *pInstrument = m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pInvestorPosition->ExchangeID,pInvestorPosition->InstrumentID);
		if (pInstrument != NULL && 
			PC_Futures == pInstrument->ProductClass)
		{		
			//发起查询行情请求,如果已经发送过了，必须再发送了
			CSendInstrumentMap::iterator iter = SendInstrumentMap.find(pInvestorPosition->InstrumentID);
			if(iter == SendInstrumentMap.end())
			{
				SendInstrumentMap.insert(CSendInstrumentMap::value_type(pInvestorPosition->InstrumentID,pInvestorPosition));
				//QDPMD 作为交易所号必须在上场文件中固定，这样才能找到相应的模块
				CBaseExchApi* pBaseExchApi = g_pExchangeLinkManager->getExchangeLink(EX_PMarket);
				if (pBaseExchApi != NULL)
				{
					pBaseExchApi->ReqQryMarketData(pInvestorPosition->ExchangeID,pInvestorPosition->InstrumentID);
					REPORT_EVENT(LOG_DEBUG,"SendQryMarketData ", "ExchangeID:%s, InstrumentID:%s",pInvestorPosition->ExchangeID.getValue(),
					pInvestorPosition->InstrumentID.getValue());
				}
			}
		}
		pInvestorPosition = m_pDB->m_InvestorPositionFactory->getNext();
	}
	m_pDB->m_InvestorPositionFactory->endGet();
}

void CHandleNotify::CalcDynamicProfit(CWriteableMarketData *pMarketData,CInstrument *pInstrument,CTransaction *pTransaction)
{
	// xuzh 调试使用，千万不要再生产中打开
	//	CConfig *pConfig= new CConfig("qtrade.ini");
	//	m_pDB->m_InvestorPositionFactory->writeCSV(pConfig);
	
	//	mpAcntPosPrft tmpMpAcntPosPrft;
	//	tmpMpAcntPosPrft.clear();
	
	if(!m_bCalcDynamicProfitSwitch)
	{
		return;
	}
	
	//由于这里是按照合约来计算，不是按照所有的持仓计算，不能统一计算盈亏
	//只能按照盈亏的变化来计算盈亏的变动
	//非期货、金交所递延合约
	if(pInstrument==NULL||pMarketData==NULL||
		PC_Futures !=pInstrument->ProductClass )
	{
		//找不到合约，不再计算持仓盈亏-wangwei,20130814
		return;
	}
	
	//无需计算几种最新价无效的情况：1.为DBL_MAX;2.Nan;3.为0.0
	//modified by chengm 20161212 增加对lastprice=0的判断
	if(pMarketData->LastPrice.isNull() || pMarketData->LastPrice == 0.0)
	{
		return;
	}
	
	//遍历客户持仓表
	CInvestorPosition* pInvestorPosition=m_pDB->m_InvestorPositionFactory->startFindAllByExIDAndInstrumentID(pInstrument->ExchangeID,pInstrument->InstrumentID);
	CWriteableInvestorPosition WriteableInvestorPosition;
	bool bFirtst=true;
	for(;pInvestorPosition!=NULL;pInvestorPosition=m_pDB->m_InvestorPositionFactory->findNextAllByExIDAndInstrumentID())	
	{
		//如果持仓为0，并且盈亏也为0,则不需要再计算了		
		if(pInvestorPosition->Position == pInvestorPosition->CacalProfitPosition)
		{
			if (pInvestorPosition->Position ==0)
			{
				m_pDB->m_InvestorPositionFactory->retrieve(pInvestorPosition,&WriteableInvestorPosition);
				WriteableInvestorPosition.LastPrice = pMarketData->LastPrice;
				m_pDB->m_InvestorPositionFactory->update(pInvestorPosition,&WriteableInvestorPosition,pTransaction);
				continue;
			}
			else if (pInvestorPosition->LastPrice == pMarketData->LastPrice)
			{
				continue;
			}
		}
		
		//如果投资者不需要检查资金，不计算持仓盈亏
		CInvestor *pInvestor = m_pDB->m_InvestorFactory->findByBrokerIDInvestorID(pInvestorPosition->BrokerID,pInvestorPosition->InvestorID);
		
		if(NULL == pInvestor)
		{
			REPORT_EVENT(LOG_CRITICAL,"CalcDynamicProfit","no investor[%s] In Line %d of File %s ",pInvestorPosition->InvestorID.getValue(),__LINE__,__FILE__);
			continue;
		}
		
		m_pDB->m_InvestorPositionFactory->retrieve(pInvestorPosition,&WriteableInvestorPosition);
		WriteableInvestorPosition.LastPrice = pMarketData->LastPrice;
		
		CInvestorAccount *pInvestorAccount = baseAlgorithms.getInvestorAccount(m_pDB,pInstrument,pInvestorPosition->BrokerID,pInvestorPosition->InvestorID);
		if(NULL!=pInvestorAccount)
		{
			CWriteableInvestorAccount WriteableInvestorAccount;
			m_pDB->m_InvestorAccountFactory->retrieve(pInvestorAccount,&WriteableInvestorAccount);
			baseAlgorithms.CalcPositionProfit(&WriteableInvestorAccount,&WriteableInvestorPosition,pInstrument);
			baseAlgorithms.ChangeBalanceAndAvailable(&WriteableInvestorAccount);
			m_pDB->m_InvestorAccountFactory->update(pInvestorAccount,&WriteableInvestorAccount);
			
			if (bFirtst)
			{
				m_pPubMessage->PreparePublish(TID_NtfPositionProfit);
				bFirtst = false;
			}
			
			CPositionProfitField field;
			memset(&field,0,sizeof(CPositionProfitField));
			field.BrokerID = pInvestorPosition->BrokerID;
			field.InvestorID = pInvestorPosition->InvestorID;
			field.PositionProfit = WriteableInvestorAccount.PositionProfit;
			
			while(XTP_ADD_FIELD(m_pPubMessage,&field) < 0) 
			{
				m_pPubMessage->MakePackage();
				m_pTradeResult->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
				m_pPubMessage->PreparePublish(TID_NtfPositionProfit);
				XTP_ADD_FIELD(m_pPubMessage,&field);						
			}
		}
		WriteableInvestorPosition.CacalProfitPosition = pInvestorPosition->Position;
		m_pDB->m_InvestorPositionFactory->update(pInvestorPosition,&WriteableInvestorPosition,pTransaction);
	}
	m_pDB->m_InvestorPositionFactory->endFindAllByExIDAndInstrumentID();
	if (!bFirtst)
	{
		m_pPubMessage->MakePackage();
		m_pTradeResult->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
	}

	REPORT_EVENT(LOG_DEBUG,"CalcDynamicProfit ", "ExchangeID:%s, InstrumentID:%s, LastPrice:%f",pMarketData->ExchangeID.getValue(),
					pMarketData->InstrumentID.getValue(),pMarketData->LastPrice.getValue());
}

long CHandleNotify::GetTimeDiff(CWriteableCurrentTime* pCurrTime)
{
	long lCurr=GetSecFromString(pCurrTime->CurrTime.getValue());
	long lLast=GetSecFromString(m_LastCalcDynamiceProfitTime.CurrTime.getValue());
	long lMSecDiff=(lCurr-lLast)*1000+(pCurrTime->CurrMillisec.getValue()-m_LastCalcDynamiceProfitTime.CurrMillisec.getValue());	
	return lMSecDiff;
}

long CHandleNotify::GetSecFromString(const char* pTime)
{
	if (pTime[0]=='\0')
	{
		return 0;
	}
	
	char szhour[3];
	char szmin[3];
	char szsec[3];
	
	szhour[0]=*pTime++;
	szhour[1]=*pTime++;
	szhour[2]=0x0;
	
	pTime++;//跳掉冒号
	
	szmin[0]=*pTime++;
	szmin[1]=*pTime++;
	szmin[2]=0x0;
	
	pTime++;
	
	szsec[0]=*pTime++;
	szsec[1]=*pTime++;
	szsec[2]=0x0;
	
	return (atoi(szhour)*3600+atoi(szmin)*60+atoi(szsec));
}

bool CHandleNotify::HandleInstrumentStatusUpdate(CInstrumentStatusField* pInstrumentStatusField,bool bSendRtn,CTransaction *pTransaction)
{
	bool bSuccess=true;
	if(NULL == pInstrumentStatusField)
	{
		return false;
	}
	CInstrument* pInstrument = m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pInstrumentStatusField->ExchangeID,
													pInstrumentStatusField->InstrumentID);
	if(NULL == pInstrument)
	{
		//CTP的合约状态是产品号，这太恶心了
		//所以需要按照产品找到所有的合约，并置合约状态
		CProductIDType ProductID = pInstrumentStatusField->InstrumentID.getValue();
		CInstrument *pInstrumentByProduct = m_pDB->m_InstrumentFactory->startFindAllByProductID(ProductID);
		if (pInstrumentByProduct == NULL)
		{
			CInstrumentStatusField* InstrumentStatusField=new CInstrumentStatusField;
			memcpy(InstrumentStatusField,pInstrumentStatusField,sizeof(CInstrumentStatusField));
			m_ProductStatusMap.insert(CProductStatusMap::value_type(ProductID,InstrumentStatusField));
		}
		else
		{
			while(pInstrumentByProduct!=NULL)
			{
				pInstrumentStatusField->InstrumentID = pInstrumentByProduct->InstrumentID;
				HandleInstrumentStatusUpdateEach(pInstrumentByProduct,pInstrumentStatusField,bSendRtn,pTransaction);
				//added by chengm 20160816 增加对组合合约状态推送
				if (pInstrumentByProduct->ExchangeID ==EXID_CZCE ||
					pInstrumentByProduct->ExchangeID ==EXID_DCE)
				{
					CInstrumentStatusField CmbInstrumentStatusField;
					CCmbInstrumentDetail *pCmbInstrumentDetail = m_pDB->m_CmbInstrumentDetailFactory->startFindAllByExchangeIDAndSingleInstrumentID(
						pInstrumentStatusField->ExchangeID, pInstrumentStatusField->InstrumentID);
					while(pCmbInstrumentDetail!=NULL)
					{
						CInstrument *pCmbInstrument = m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pInstrumentStatusField->ExchangeID,
							pCmbInstrumentDetail->ArbiInstrumentID);
						if (pCmbInstrumentDetail->LegNo ==1 &&
							pCmbInstrument != NULL)
						{
							CopyInstrumentStatusEntity(&CmbInstrumentStatusField,pInstrumentStatusField);
							CmbInstrumentStatusField.InstrumentID =pCmbInstrument->InstrumentID;
							CmbInstrumentStatusField.InstrumentName= pCmbInstrument->InstrumentName;
							HandleInstrumentStatusUpdateEach(pCmbInstrument,&CmbInstrumentStatusField,bSendRtn,pTransaction);
						}
						pCmbInstrumentDetail = m_pDB->m_CmbInstrumentDetailFactory->findNextAllByExchangeIDAndSingleInstrumentID();
					}
					m_pDB->m_CmbInstrumentDetailFactory->endFindAllByExchangeIDAndSingleInstrumentID();
					
				}
				pInstrumentByProduct = m_pDB->m_InstrumentFactory->findNextAllByProductID();
			}
			m_pDB->m_InstrumentFactory->endFindAllByProductID();
		}
		
	}
	else
	{
		if (pInstrument->InstrumentStatus != pInstrumentStatusField->InstrumentStatus)
		{
			HandleInstrumentStatusUpdateEach(pInstrument,pInstrumentStatusField,bSendRtn,pTransaction);
		}
	}
	return true;
}

bool CHandleNotify::HandleInstrumentStatusUpdateEach(CInstrument* pInstrument,CInstrumentStatusField* pInstrumentStatusField,bool bSendRtn,CTransaction *pTransaction)
{
	CWriteableInstrument  theInstrument;
	m_pDB->m_InstrumentFactory->retrieve(pInstrument,&theInstrument);
	theInstrument.InstrumentStatus = pInstrumentStatusField->InstrumentStatus;
	m_pDB->m_InstrumentFactory->update(pInstrument,&theInstrument,pTransaction);
	
	if (bSendRtn)
	{	
		m_pPubMessage->PreparePublish(TID_NtfInstrumentStatusUpdate);
		XTP_ADD_FIELD(m_pPubMessage, pInstrumentStatusField);
		m_pPubMessage->MakePackage();
		m_pTradeResult->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
	}
	
	return true;
}

/*	函数 RemoveFaildPreOrder 处理丢失的在途订单。把丢失的订单从预报单表中删除，并插入错单表。
//	参数本地报单号 OrderLocalID 是人为 加1 后，来查找的。有可能从预报单表中查不到报单，这是正常的。
//  longqy@cffex.net 2013-05-13
*/
// int CHandleNotify::RemoveFaildPreOrder(CExchangeIDType&  ExchangeID,CSeatIDType&  SeatID,COrderLocalIDType  &OrderLocalID,CTransaction *pTransaction,vector<CWriteablePreOrder*> &PreOrders)
// {
// 	CPreOrder* pPreOrder   = NULL;
// 	pPreOrder = m_pDB->m_PreOrderFactory->findByAPIIDAndOrderLocalID(ExchangeID,SeatID,OrderLocalID);
// 
// 	if(pPreOrder == NULL)  //在预委托表中无法找到，这是可能的。本地报单号码可能跳跃而不连续。
// 	{
// 		REPORT_EVENT(LOG_WARNING,"This order cann't be found in PreOrder table ", "ExchangeID: %s, SeatID: %s , OrderLocalID: %s \n", ExchangeID.getValue(),SeatID.getValue(),OrderLocalID.getValue());
// 		return -1;
// 	}else //错单 -  并且由交易所返回的未经确认的消息  预委托表存在
// 	{
// 		CWriteablePreOrder* pSavePreOrder = new CWriteablePreOrder();
// 		CopyPreOrderEntity(pSavePreOrder,pPreOrder);
// 		PreOrders.push_back(pSavePreOrder);
// 
//        	//pInputOrderField->FrozenMargin = 0.0;
// 		//pInputOrderField->FrozenFee    = 0.0;
// 		CInvestorAccount* pInvestorAccount = NULL;
// 		CInvestorPosition*  pInvestorPosition  = NULL;
// 		bool bSuccess = false;
// 		
// 		COrderInsertFailed *pOrderInsertFailed = m_pDB->m_OrderInsertFailedFactory->findByExchangeIDSeatIDAndOrderLocalID(ExchangeID,SeatID,OrderLocalID);
// 		if( NULL ==  pOrderInsertFailed)    //预委托表中存在，错单表中不存在
// 		{ 
// 			CInstrument* pInstrument = m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(ExchangeID,pPreOrder->InstrumentID);
// 			if(NULL == pInstrument)
// 			{
// 				return 2;   
// 			}
// 			else
// 			{
// 				switch (pInstrument->ProductClass )
// 				{
// 				case PC_Futures:
// 				   {
// 					   m_pMoneyPosition = m_pFutureMoneyPosition;
// 					   break;
// 				   }
// 				case PC_Options:
// 				   {
// 					   m_pMoneyPosition = m_pOptionMoneyPosition;
// 					   break;
// 				   }
// 				default: 	// 未找到合约类型,直接返回。
// 				   {   
// 					   REPORT_EVENT(LOG_WARNING,"Can not Find Instrument Class ", "In Line %d of File %s.\n",__LINE__,__FILE__);
// 					   m_pErrorEngine->reportError(ERROR_INSTRUMENT_NOT_FOUND);
// 					   return 2;
// 				   }
// 			   }
// 			}
// 			//失效冻结资金
// 			bSuccess = m_pMoneyPosition->RspOrderMoneyUnFrozen(pInvestorAccount,pPreOrder,pTransaction);
// 			if(false == bSuccess )      
// 			{
// 				REPORT_EVENT(LOG_CRITICAL,"Can not UnFrozen Money  ", "In Line %d of File %s.\n",__LINE__,__FILE__);
// 				return 2;
// 			}
// 			//失效冻结持仓
// 			bSuccess  = m_pMoneyPosition->RspPositionUnFrozen(pInvestorPosition,pPreOrder,pTransaction);
// 			if(false == bSuccess)
// 			{
// 				REPORT_EVENT(LOG_CRITICAL,"Can not UnFrozen  Position ", "In Line %d of File %s.\n",__LINE__,__FILE__);
// 				return 3;
// 			}
// 			//插入错单表
// 			CWriteableOrderInsertFailed theWriteableOrderInsertFailed;
// 			theWriteableOrderInsertFailed.init();
// 			CopyOrderEntity(&theWriteableOrderInsertFailed,pPreOrder);
// 			theWriteableOrderInsertFailed.ErrorMsg = "Order lost on the way from FEMAS to Exchange. \n";
// 
// 			//将微妙级精确时间插入到UserCustom字段，作为错单表的主键之一 liumeng 20140820
// 			long nCurrentTime =0;
// 			GET_ACCURATE_USEC_TIME(nCurrentTime);
// 			theWriteableOrderInsertFailed.UserCustom = nCurrentTime;
// 	
// 			if( m_pDB->m_OrderInsertFailedFactory->add(&theWriteableOrderInsertFailed,pTransaction) != NULL)
// 			{
// 				m_pDB->m_PreOrderFactory->remove(pPreOrder,pTransaction);
// 				return 6;  
// 			}
// 			else
// 			{
// 				//严重错误，插入错单表失败
// 
// 				REPORT_EVENT(LOG_CRITICAL,"RemoveFaildPreOrder ERR,ExchangeID=[%s],SeatID=[%s],OrderLocalID=[%s]\n",ExchangeID.getValue(),SeatID.getValue(),OrderLocalID.getValue());
// 				return 4;
// 			}
// 		} 
// 		else
// 		{
// 			m_pDB->m_PreOrderFactory->remove(pPreOrder,pTransaction);
// 			return 5;    
// 		}
// 	}
// 	return 7;
// }

void CHandleNotify::CZCEInstrumentStatusUpdate(bool bSendRtn /* = true */)
{
	for (CProductStatusMap::iterator pIter=m_ProductStatusMap.begin();pIter!=m_ProductStatusMap.end();pIter++)
	{
		HandleInstrumentStatusUpdate(pIter->second,bSendRtn,NULL);
	}
}

/************************************************************************/
/* 初始化的检查全部移动到这个地方 by wangwei ,20130510                                                                     */
/************************************************************************/
CInitCheckTrigger *CHandleNotify::m_initTrigger=NULL;
int CHandleNotify::initCount=0;

#define reportSize(tableName)												\
{																		\
	fprintf(output,"\t%sSize=%d\n",#tableName,m_pDB->m_ ## tableName ## Factory -> getCount());	\
}

#define checkUnique(tableName,fieldName)									\
	{																		\
		map<string,string> list;											\
		C ## tableName *pitem;												\
		pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
		while (pitem!=NULL)													\
		{																	\
			const char *value=pitem->fieldName;								\
			map<string,string>::iterator it;								\
			it=list.find(string(value));									\
			if (it!=list.end())												\
			{																\
				genError("%s中的字段%s的值%s重复",#tableName,#fieldName,value);\
			}																\
			else															\
			{																\
				list[string(value)]=string(value);							\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

#define checkUniqueInt(tableName,fieldName)									\
	{																		\
		map<int,int> list;													\
		C ## tableName *pitem;												\
		pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
		while (pitem!=NULL)													\
		{																	\
			int value=pitem->fieldName;										\
			map<int,int>::iterator it;										\
			it=list.find(value);											\
			if (it!=list.end())												\
			{																\
				genError("%s中的字段%s的值%d重复",#tableName,#fieldName,value);\
			}																\
			else															\
			{																\
				list[value]=value;											\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

#define checkUnique2(tableName,fieldName1,fieldName2, methodName)			\
	{																		\
		C ## tableName *pitem;												\
		pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
		while (pitem!=NULL)													\
		{																	\
			C ## tableName *pFoundItem;										\
			pFoundItem=m_pDB->m_ ## tableName ## Factory->find ## methodName(pitem->fieldName1,pitem->fieldName2);\
			if (pitem!=pFoundItem)											\
			{																\
				char buffer1[4000],buffer2[4000];							\
				pitem->fieldName1.getString(buffer1);						\
				pitem->fieldName2.getString(buffer2);						\
				genError("%s中的字段%s,%s的值%s,%s重复",#tableName,#fieldName1,#fieldName2,buffer1,buffer2);\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

#define checkUnique3(tableName,fieldName1,fieldName2,fieldName3,methodName)	\
	{																		\
		C ## tableName *pitem;												\
		pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
		while (pitem!=NULL)													\
		{																	\
			C ## tableName *pFoundItem;										\
			pFoundItem=m_pDB->m_ ## tableName ## Factory->find ## methodName(pitem->fieldName1,pitem->fieldName2,pitem->fieldName3);\
			if (pitem!=pFoundItem)											\
			{																\
				char buffer1[4000],buffer2[4000],buffer3[4000];				\
				pitem->fieldName1.getString(buffer1);						\
				pitem->fieldName2.getString(buffer2);						\
				pitem->fieldName3.getString(buffer3);						\
				genError("%s中的字段%s,%s,%s的值%s,%s,%s重复",#tableName,#fieldName1,#fieldName2,#fieldName3,buffer1,buffer2,buffer3);\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

#define checkUnique4(tableName,fieldName1,fieldName2,fieldName3,fieldName4,methodName)\
	{																		\
		C ## tableName *pitem;												\
		pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
		while (pitem!=NULL)													\
		{																	\
			C ## tableName *pFoundItem;										\
			pFoundItem=m_pDB->m_ ## tableName ## Factory->find ## methodName(pitem->fieldName1,pitem->fieldName2,pitem->fieldName3,pitem->fieldName4);\
			if (pitem!=pFoundItem)											\
			{																\
				char buffer1[4000],buffer2[4000],buffer3[4000],buffer4[4000];\
				pitem->fieldName1.getString(buffer1);						\
				pitem->fieldName2.getString(buffer2);						\
				pitem->fieldName3.getString(buffer3);						\
				pitem->fieldName4.getString(buffer4);						\
				genError("%s中的字段%s,%s,%s,%s的值%s,%s,%s,%s重复",#tableName,#fieldName1,#fieldName2,#fieldName3,#fieldName4,buffer1,buffer2,buffer3,buffer4);\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

#define checkUnique5(tableName,fieldName1,fieldName2,fieldName3,fieldName4,fieldName5,methodName)\
	{																		\
		C ## tableName *pitem;												\
		pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
		while (pitem!=NULL)													\
		{																	\
			C ## tableName *pFoundItem;										\
			pFoundItem=m_pDB->m_ ## tableName ## Factory->find ## methodName(pitem->fieldName1,pitem->fieldName2,pitem->fieldName3,pitem->fieldName4,pitem->fieldName5);\
			if (pitem!=pFoundItem)											\
			{																\
				char buffer1[4000],buffer2[4000],buffer3[4000],buffer4[4000],buffer5[4000];\
				pitem->fieldName1.getString(buffer1);						\
				pitem->fieldName2.getString(buffer2);						\
				pitem->fieldName3.getString(buffer3);						\
				pitem->fieldName4.getString(buffer4);						\
				pitem->fieldName5.getString(buffer5);						\
				genError("%s中的字段%s,%s,%s,%s,%s的值%s,%s,%s,%s,%s重复",#tableName,#fieldName1,#fieldName2,#fieldName3,#fieldName4,#fieldName5,buffer1,buffer2,buffer3,buffer4,buffer5);\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

#define checkUnique6(tableName,fieldName1,fieldName2,fieldName3,fieldName4,fieldName5,fieldName6,methodName)\
	{																		\
	C ## tableName *pitem;												\
	pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
	while (pitem!=NULL)													\
		{																	\
		C ## tableName *pFoundItem;										\
		pFoundItem=m_pDB->m_ ## tableName ## Factory->find ## methodName(pitem->fieldName1,pitem->fieldName2,pitem->fieldName3,pitem->fieldName4,pitem->fieldName5,pitem->fieldName6);\
		if (pitem!=pFoundItem)											\
			{																\
			char buffer1[4000],buffer2[4000],buffer3[4000],buffer4[4000],buffer5[4000],buffer6[4000];\
			pitem->fieldName1.getString(buffer1);						\
			pitem->fieldName2.getString(buffer2);						\
			pitem->fieldName3.getString(buffer3);						\
			pitem->fieldName4.getString(buffer4);						\
			pitem->fieldName5.getString(buffer5);						\
			pitem->fieldName6.getString(buffer6);						\
			genError("%s中的字段%s,%s,%s,%s,%s,%s的值%s,%s,%s,%s,%s,%s重复",#tableName,#fieldName1,#fieldName2,#fieldName3,#fieldName4,#fieldName5,#fieldName6,buffer1,buffer2,buffer3,buffer4,buffer5,buffer6);\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

#define checkForeign(tableName,keyName,factoryName,methodName)				\
	{																		\
		C ## tableName *pitem;												\
		pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
		while (pitem!=NULL)													\
		{																	\
			if (m_pDB->m_ ## factoryName ## Factory->find ## methodName (pitem->keyName)==NULL)		\
			{																\
				char buffer[4000];											\
				pitem->keyName.getString(buffer);							\
				genError("%s的字段%s的值%s对应的%s找不到",#tableName,#keyName,buffer,#factoryName);		\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

#define checkForeignEX(tableName,keyName,factoryName,methodName,exception)	\
	{																		\
		C ## tableName *pitem;												\
		pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
		while (pitem!=NULL)													\
		{																	\
			if (m_pDB->m_ ## factoryName ## Factory->find ## methodName (pitem->keyName)==NULL)		\
			{																\
				char buffer[4000];											\
				pitem->keyName.getString(buffer);							\
				if (strcmp(buffer,exception))								\
				{															\
					genError("%s的字段%s的值%s对应的%s找不到",#tableName,#keyName,buffer,#factoryName);		\
				}															\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

#define checkForeignIgnore(tableName,keyName,factoryName,methodName,ignoreFunc)\
	{																		\
		C ## tableName *pitem;												\
		pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
		while (pitem!=NULL)													\
		{																	\
			if (ignoreFunc(pitem))											\
			{																\
				pitem=m_pDB->m_ ## tableName ## Factory->getNext();			\
				continue;													\
			}																\
			if (m_pDB->m_ ## factoryName ## Factory->find ## methodName (pitem->keyName)==NULL)		\
			{																\
				char buffer[4000];											\
				pitem->keyName.getString(buffer);							\
				genError("%s的字段%s的值%s对应的%s找不到",#tableName,#keyName,buffer,#factoryName);		\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

#define checkMultiForeign(tableName,keyName,factoryName,methodName)			\
	{																		\
		C ## tableName *pitem;												\
		pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
		while (pitem!=NULL)													\
		{																	\
			if (m_pDB->m_ ## factoryName ## Factory->startFind ## methodName (pitem->keyName)==NULL)		\
			{																\
				char buffer[4000];											\
				pitem->keyName.getString(buffer);							\
				genError("%s的字段%s的值%s对应的%s找不到",#tableName,#keyName,buffer,#factoryName);		\
			}																\
			m_pDB->m_ ## factoryName ## Factory->endFind ##methodName();		\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

#define checkLinkedForeign(tableName,keyName,foreignName)					\
	{																		\
		C ## tableName *pitem;												\
		pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
		while (pitem!=NULL)													\
		{																	\
			if (pitem->get ## foreignName()==NULL)							\
			{																\
				char buffer[4000];											\
				pitem->keyName.getString(buffer);							\
				genError("%s的字段%s的值%s对应的外键%s找不到",#tableName,#keyName,buffer,#foreignName);		\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

#define checkRawForeign(tableName,keyName,factoryName,idName)				\
	{																		\
		C ## tableName *pitem;												\
		pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
		while (pitem!=NULL)													\
		{																	\
			C ## factoryName *pID;											\
			bool found=false;												\
			pID=m_pDB->m_ ## factoryName ## Factory->getFirst();				\
			while (pID!=NULL)												\
			{																\
				if (pitem->keyName==pID->idName)							\
				{															\
					found=true;												\
					break;													\
				}															\
				pID=m_pDB->m_ ## factoryName ## Factory->getNext();			\
			}																\
			m_pDB->m_ ## factoryName ## Factory->endGet();					\
			if (!found)														\
			{																\
				char buffer[4000];											\
				pitem->keyName.getString(buffer);							\
				genError("%s的字段%s的值%s对应的%s找不到",#tableName,#keyName,buffer,#factoryName);		\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

#define checkRawForeignIgnore(tableName,keyName,factoryName,idName,ignoreFunc)\
	{																		\
		C ## tableName *pitem;												\
		pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
		while (pitem!=NULL)													\
		{																	\
			if (ignoreFunc(pitem))											\
			{																\
				pitem=m_pDB->m_ ## tableName ## Factory->getNext();			\
				continue;													\
			}																\
			C ## factoryName *pID;											\
			bool found=false;												\
			pID=m_pDB->m_ ## factoryName ## Factory->getFirst();				\
			while (pID!=NULL)												\
			{																\
				if (pitem->keyName==pID->idName)							\
				{															\
					found=true;												\
					break;													\
				}															\
				pID=m_pDB->m_ ## factoryName ## Factory->getNext();			\
			}																\
			m_pDB->m_ ## factoryName ## Factory->endGet();					\
			if (!found)														\
			{																\
				char buffer[4000];											\
				pitem->keyName.getString(buffer);							\
				genError("%s的字段%s的值%s对应的%s找不到",#tableName,#keyName,buffer,#factoryName);		\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

#define checkForeign2(tableName,keyName1,keyName2,factoryName,methodName)	\
	{																		\
		C ## tableName *pitem;												\
		pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
		while (pitem!=NULL)													\
		{																	\
			if (m_pDB->m_ ## factoryName ## Factory->find ## methodName (pitem->keyName1, pitem->keyName2)==NULL)		\
			{																\
				char buffer1[4000];											\
				pitem->keyName1.getString(buffer1);							\
				char buffer2[4000];											\
				pitem->keyName2.getString(buffer2);							\
				genError("%s的字段%s,%s的值%s,%s对应的%s找不到",#tableName,#keyName1,#keyName2,buffer1,buffer2,#factoryName);		\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

#define checkForeign3(tableName,keyName1,keyName2,keyName3,factoryName,methodName)	\
	{																		\
	C ## tableName *pitem;												\
	pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
	while (pitem!=NULL)													\
		{																	\
		if (m_pDB->m_ ## factoryName ## Factory->find ## methodName (pitem->keyName1, pitem->keyName2, pitem->keyName3)==NULL)		\
			{																\
			char buffer1[4000];											\
			pitem->keyName1.getString(buffer1);							\
			char buffer2[4000];											\
			pitem->keyName2.getString(buffer2);							\
			char buffer3[4000];											\
			pitem->keyName3.getString(buffer3);							\
			genError("%s的字段%s,%s,%s的值%s,%s,%s对应的%s找不到",#tableName,#keyName1,#keyName2,#keyName3,buffer1,buffer2,buffer3,#factoryName);		\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

///-----------------------
///	xuzh，20080416：增加了对行情初始化数据中缺少昨结算或者昨收盘时的报错
///-----------------------
//
#define checkValidField(tableName,keyName,checkName,checkMethod)	\
	{																		\
	C ## tableName *pitem;												\
	pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
	while (pitem!=NULL)													\
		{																	\
		if (!checkMethod(pitem->checkName))			\
			{																\
			char buffer[4000];											\
			pitem->keyName.getString(buffer);							\
			genError("%s表中%s记录的%s取值不合理，为空或者为0",#tableName,buffer,#checkName);	\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}
 
#define checkValidFieldIgnore(tableName,keyName,checkName,checkMethod,ignoreFunc)	\
	{																		\
		C ## tableName *pitem;												\
		pitem=m_pDB->m_ ## tableName ## Factory->getFirst();					\
		while (pitem!=NULL)													\
		{																	\
			if (!ignoreFunc(pitem)&&!checkMethod(pitem->checkName))			\
			{																\
				char buffer[4000];											\
				pitem->keyName.getString(buffer);							\
				genError("%s表中%s记录的%s取值不合理，为空或者为0",#tableName,buffer,#checkName);	\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}


bool notNullPrice(const CPriceType &price)
{
	return !price.isNull()&&(price!=0.0);
}

bool notNullMoney(const CMoneyType &money)
{
	return !money.isNull();
}

bool notNullRatio(const CRatioType &ratio)
{
	return !ratio.isNull();
}

bool notNullMultiple(const CUnderlyingMultipleType &multiple)
{
	return !multiple.isNull()&&(multiple!=0.0);
}

bool notNullTradingday(const CTradingDayType &tradingday)
{
	return !tradingday.isNull();
}

class CAcntDirIdx
{
public:
	CAcntDirIdx(){};
	~CAcntDirIdx(){};
public:
	CBrokerIDType BrokerID;
	CAccountIDType AccountID;
	CDirectionType Direction;
	bool operator > (const CAcntDirIdx &m)const
	{
		if (BrokerID > m.BrokerID)
		{
			return true;
		}
		else if (BrokerID < m.BrokerID)
		{
			return false;
		}
		else
		{
			if (AccountID > m.AccountID)
			{
				return true;
			}
			else if (AccountID < m.AccountID)
			{
				return false;
			}
			else
			{
				if (Direction > m.Direction)
				{
					return true;
				}
				else if (Direction < m.Direction)
				{
					return false;
				}
				else
				{
					return false;
				}
			}
		}

	}
};

typedef map<CAcntDirIdx, CMoneyType , greater<CAcntDirIdx> >  CAcntDirMarginMap;

void CInitCheckTrigger::afterUpdate(CSystemStatus *pSystemStatus)
{
	//设置
	CBaseCheck::m_SystemStatus=pSystemStatus->SystemStatus;
	
	if (pSystemStatus->SystemStatus==SS_InstrumentTradingDayDown)
	{
		//合约已经查询回来，可以开始进行初始化数据的检查
		///打开数据检查结果的文件
		char *filename=m_Config->getConfig("ConsistentCheck");
		if (filename[0]=='\0')
		{
			///没有此项配置，那就放弃
			return;
		}
		output=mfopen(filename,"w+t");
		if (output==NULL)
		{
			///无法打开文件，那就放弃
			REPORT_EVENT(LOG_CRITICAL,"EnvError","can not open consistent check file");
			return;
		}
		
		///开始各项一致性检查
		errorCount=0;
		fprintf(output,"--------同步完成后检查--------\n");
		
		///以下是各个主要数据表的大小
		fprintf(output,"各表大小\n");
		//2014-06-25 longqy 不flush文件，提高性能
		//fflush(output);
		reportSize(InvestorFee);
		reportSize(InvestorMargin);
		reportSize(InvestorPosition);
		reportSize(ClientTradingID);
		reportSize(Exchange);
		reportSize(Instrument);
		reportSize(Investor);
		reportSize(InvestorAccount);
		reportSize(Seat);
		reportSize(User);
		reportSize(UserInvestor);
		reportSize(UserTradingRight);
		
		///数据格式检查
		///首先检查交易日
		
		if (m_pDB->m_SystemStatusFactory->getCount()!=1)
		{
			genError("DataSyncStatus表的数据数目不对");
		}
		
		///检查客户费率
		if (m_pDB->m_InvestorFeeFactory->getCount()<1)
		{
			genError("InvestorFee表的数据数目不能小于1");
		}
		checkUnique5(InvestorFee,BrokerID,ExchangeID,InstrumentID,InvestorID,HedgeFlag,ByBrkIDExIDIstIDVstIDHdg);
//		checkForeign3(InvestorFee,BrokerID,ExchangeID,ClientID,ClientTradingID,ByBrokerIDExchangeIDClientID);
//		checkForeign2(InvestorFee,ExchangeID,InstrumentID,Instrument,ByExchangeIDAndInstrumentID);	
		checkValidField(InvestorFee,InvestorID,OpenFeeRate,notNullRatio);
		checkValidField(InvestorFee,InvestorID,OpenFeeAmt,notNullRatio);
		checkValidField(InvestorFee,InvestorID,OffsetFeeRate,notNullRatio);
		checkValidField(InvestorFee,InvestorID,OffsetFeeAmt,notNullRatio);
		checkValidField(InvestorFee,InvestorID,OTFeeRate,notNullRatio);
		checkValidField(InvestorFee,InvestorID,OTFeeAmt,notNullRatio);
		
		
		///检查客户保证金率
		if (m_pDB->m_InvestorMarginFactory->getCount()<1)
		{
			genError("InvestorMargin表的数据数目不能小于1");
		}
		checkUnique5(InvestorMargin,BrokerID,ExchangeID,InstrumentID,InvestorID,HedgeFlag,ByBrkIDExIDIstIDVstIDHdg);
//		checkForeign3(InvestorMargin,BrokerID,ExchangeID,ClientID,ClientTradingID,ByBrokerIDExchangeIDClientID);
//		checkForeign2(InvestorMargin,ExchangeID,InstrumentID,Instrument,ByExchangeIDAndInstrumentID);	
		checkValidField(InvestorMargin,InvestorID,LongMarginRate,notNullRatio);
		checkValidField(InvestorMargin,InvestorID,ShortMarginRate,notNullRatio);
		checkValidField(InvestorMargin,InvestorID,LongMarginAmt,notNullRatio);
		checkValidField(InvestorMargin,InvestorID,ShortMarginAmt,notNullRatio);
		
		///检查客户持仓表
		checkUnique6(InvestorPosition,BrokerID,ExchangeID,InvestorID,InstrumentID,Direction,HedgeFlag,ByBrkIDExIDInvIDInsDirHed);
		//	checkForeign(InvestorPosition,TradingDay,DataSyncStatus,ByTradingday);
//		checkForeign4(InvestorPosition,BrokerID,ExchangeID,Participant,ClientID,ClientTradingID,ByBrokerIDExchangeIDPartClientID);
		
		///检查交易编码表ClientTradingID
		checkUnique4(ClientTradingID,BrokerID,ExchangeID,ParticipantID,ClientID,ByBrokerIDExchangeIDPartClientID);
		checkForeign2(ClientTradingID,BrokerID,AccountID,InvestorAccount,ByBrokerIDAccountID);
//		checkForeign3(ClientTradingID,BrokerID,ExchangeID,ParticipantID,Participant,ByBrokerIDExchangeIDAndParticipantID);
			
		///检查交易所Exchange
		checkUnique(Exchange,ExchangeID);
		if (m_pDB->m_ExchangeFactory->getCount()<1)
		{
			genError("Exchange表的数据数目不对");
		}
		
		///检查合约表Instrument
		//del by wangwei, 20130530, 合约表不是上场的，取消检查

// 		checkUnique2(Instrument,ExchangeID,InstrumentID,ByExchangeIDAndInstrumentID);
// 		checkForeign2(Instrument,ExchangeID,ProductID,Product,ByExchangeIDAndProductID);
// 		checkValidField(Instrument,InstrumentID,UnderlyingMultiple,notNullMultiple);
// 		checkValidField(Instrument,InstrumentID,PriceTick,notNullPrice);	
// 		checkValidField(Instrument,InstrumentID,LowerLimitPrice,notNullPrice);
// 		checkValidField(Instrument,InstrumentID,UpperLimitPrice,notNullPrice);		
// 		checkValidField(Instrument,InstrumentID,PreSettlementPrice,notNullPrice);			
		
		///投资者 Investor
		checkUnique2(Investor,BrokerID,InvestorID,ByBrokerIDInvestorID);
		if (m_pDB->m_InvestorFactory->getCount()<1)
		{
			genError("Investor表的数据数目不对");
		}
		
		///检查资金表 InvestorAccount
		checkUnique2(InvestorAccount,BrokerID,AccountID,ByBrokerIDAccountID);
		//	checkForeign(InvestorAccount,TradingDay,DataSyncStatus,ByTradingday);
		checkForeign2(InvestorAccount,BrokerID,InvestorID,Investor,ByBrokerIDInvestorID);
		checkValidField(InvestorAccount,AccountID,PreAvailable,notNullMoney);
		checkValidField(InvestorAccount,AccountID,LongMargin,notNullMoney);
		checkValidField(InvestorAccount,AccountID,ShortMargin,notNullMoney);
		checkValidField(InvestorAccount,AccountID,PreBalance,notNullMoney);
		checkValidField(InvestorAccount,AccountID,Margin,notNullMoney);
						
		///检查席位表 Seat
		checkUnique3(Seat,BrokerID,ExchangeID,SeatID,ByBrokerIDExchangeIDSeatID);
		if (m_pDB->m_SeatFactory->getCount()<1)
		{
			genError("Seat表的数据数目不对");
		}
		
		///用户表 User
		checkUnique2(User,BrokerID,UserID,ByBrokerIDUserID);
		if (m_pDB->m_UserFactory->getCount()<1)
		{
			genError("User表的数据数目不对");
		}
		
		///用户席位表 UserInvestor
		checkUnique3(UserInvestor,BrokerID,UserID,InvestorID,ByBrokerIDUserIDInvestorID);
		checkForeign2(UserInvestor,BrokerID,UserID,User,ByBrokerIDUserID);
		checkForeign2(UserInvestor,BrokerID,InvestorID,Investor,ByBrokerIDInvestorID);
		
		///用户交易权限表 UserTradingRight
		checkUnique5(UserTradingRight,BrokerID,ExchangeID,InstrumentID,UserID,InvestorID,ByBrkExIDInsUserInv);
		checkForeign2(UserTradingRight,ExchangeID,InstrumentID,Instrument,ByExchangeIDAndInstrumentID);
		
		///业务检查
		businessCheck();
		
		///完成了检查
		fprintf(output,"共%d个错误\n",errorCount);
		fclose(output);
		//add by wangwei, 20130607
		m_pDB->save(m_Config);
	}
}


void CInitCheckTrigger::businessCheck()
{
	fprintf(output,"业务检查\n");
	CInvestorPosition *pInvestorPosition=NULL;
	CAcntDirMarginMap acntDirMarginMap;
	acntDirMarginMap.clear();

	CAcntDirIdx idx;
	//此处暂时不考虑YdPosition
	for (pInvestorPosition=m_pDB->m_InvestorPositionFactory->getFirst();
	pInvestorPosition!=NULL;
	pInvestorPosition=m_pDB->m_InvestorPositionFactory->getNext())			
	{
		//1.检查持仓是否为0
		if (pInvestorPosition->Position==0)
		{
			genError("客户持仓表中ClientID[%s],InstrumentID[%s],Direction[%c],HedgeFlag[%c]对应的记录Position字段为0，但没有被删除",
				pInvestorPosition->ClientID.getValue(),pInvestorPosition->InstrumentID.getValue(),
				pInvestorPosition->Direction.getValue(),pInvestorPosition->HedgeFlag.getValue());
			continue;
		}		
		//2.检查合约是否存在
		CInstrument *pInstrument=m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pInvestorPosition->ExchangeID,pInvestorPosition->InstrumentID);
		if (pInstrument==NULL)
		{
			genError("在Instrument表中找不到交易所[%s]合约[%s]对应的记录",pInvestorPosition->ExchangeID.getValue(),pInvestorPosition->InstrumentID.getValue());
			continue;
		}
		//3.检查投资者账户是否存在
		CInvestorAccount* pInvestorAccount=m_pDB->m_InvestorAccountFactory->findByBrokerIDAccountID(pInvestorPosition->BrokerID,pInvestorPosition->AccountID);
		if (pInvestorAccount==NULL)
		{
			genError("客户持仓记录中的AccountID[%s]在InvestorAccount表中找不到",pInvestorPosition->AccountID.getValue());
			continue;
		}
		//4.检查交易编码
		CClientTradingID* pClientTradingID=m_pDB->m_ClientTradingIDFactory->findByBrokerIDExchangeIDPartClientID(pInvestorPosition->BrokerID,pInvestorPosition->ExchangeID,pInvestorPosition->ParticipantID,pInvestorPosition->ClientID);
		if (pClientTradingID==NULL)
		{
			pClientTradingID=m_pDB->m_ClientTradingIDFactory->findByBrokerIDExchangeIDPartClientID(pInvestorPosition->BrokerID,"Broker",pInvestorPosition->ParticipantID,pInvestorPosition->ClientID);
			if (pClientTradingID==NULL)
			{
				genError("客户持仓记录中的ExchangeID[%s],ClientID[%s]在ClientTradingID表中找不到对应的记录",pInvestorPosition->ExchangeID.getValue(),pInvestorPosition->ClientID.getValue());
				continue;
			}

		}
		//5.检查InvestorID是否存在
		CInvestor* pInvestor=m_pDB->m_InvestorFactory->findByBrokerIDInvestorID(pInvestorPosition->BrokerID,pClientTradingID->InvestorID);
		if (pInvestor==NULL)
		{
			genError("投资者号InvestorID[%s]在Investor表中找不到",pClientTradingID->InvestorID.getValue());
			continue;
		}
		//6.检查客户保证金率是否存在
		CInvestorMargin* pInvestorMargin=m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(pInvestorPosition->BrokerID,pInvestorPosition->ExchangeID,pInvestorPosition->InstrumentID,pInvestorPosition->InvestorID,pInvestorPosition->HedgeFlag);
		if (pInvestorMargin==NULL)
		{
			genError("ExchangeID[%s],ClientID[%s],InstrumentID[%s]的客户保证金率在InvestorMargin表中找不到",
				pInvestorPosition->ExchangeID.getValue(),pInvestorPosition->ClientID.getValue(),pInvestorPosition->InstrumentID.getValue());
			continue;
		}
		//7.检查保证金占用是否正确
		CMoneyType UsedMargin=0.0;
		if(pInvestorPosition->Direction==D_Buy)
		{
			UsedMargin = pInvestorPosition->Position*pInstrument->PreSettlementPrice*pInstrument->VolumeMultiple*pInvestorMargin->LongMarginRate \
				       + pInvestorPosition->Position*pInvestorMargin->LongMarginAmt;
		}
		else
		{
			UsedMargin = pInvestorPosition->Position*pInstrument->PreSettlementPrice*pInstrument->VolumeMultiple*pInvestorMargin->ShortMarginRate \
		               + pInvestorPosition->Position*pInvestorMargin->ShortMarginAmt; 
		} 

		//20131010 xuzh 由于场下数据库只保留3位小数,场上计算需要的误差范围为0.001即可
		if (fabs(pInvestorPosition->UsedMargin-UsedMargin)>0.001)
		{
			genError("客户持仓表中ClientID[%s],InstrumentID[%s],PosiDirection[%c]的客户持仓保证金UsedMargin计算不正确"
				"初始数据为[%f]，根据规则计算应为[%f]",				
				pInvestorPosition->ClientID.getValue(),
				pInvestorPosition->InstrumentID.getValue(),
				pInvestorPosition->Direction.getValue(),				
				pInvestorPosition->UsedMargin.getValue(),
				UsedMargin.getValue());
		}
	
		idx.BrokerID=pInvestorPosition->BrokerID;
		idx.AccountID=pInvestorPosition->AccountID;
		idx.Direction=pInvestorPosition->Direction;
		CAcntDirMarginMap::iterator itMargin=acntDirMarginMap.find(idx);
		//累计占用保证金
		if (itMargin!=acntDirMarginMap.end())
		{
			itMargin->second+=pInvestorPosition->UsedMargin;
		}
		else
		{
			acntDirMarginMap.insert(CAcntDirMarginMap::value_type(idx,pInvestorPosition->UsedMargin));
		}
	}
	m_pDB->m_InvestorPositionFactory->endGet();

	//8.检查保证金占用是否与account表中一致
	for (CAcntDirMarginMap::iterator itMargin=acntDirMarginMap.begin();itMargin!=acntDirMarginMap.end();itMargin++)
	{
		CInvestorAccount* pInvestorAccount=m_pDB->m_InvestorAccountFactory->findByBrokerIDAccountID(itMargin->first.BrokerID,itMargin->first.AccountID);
		if (pInvestorAccount!=NULL)
		{
			if (itMargin->first.Direction==D_Buy&&itMargin->second!=pInvestorAccount->LongMargin)
			{
				genError("帐号[%s]的多头保证金占用金额为[%f]，但是根据客户持仓计算的结果为[%f]",
					pInvestorAccount->AccountID.getValue(),pInvestorAccount->LongMargin.getValue(),itMargin->second.getValue());
			}
			if (itMargin->first.Direction==D_Sell&&itMargin->second!=pInvestorAccount->ShortMargin)
			{
				genError("帐号[%s]的空头保证金占用金额为[%f]，但是根据客户持仓计算的结果为[%f]",
					pInvestorAccount->AccountID.getValue(),pInvestorAccount->ShortMargin.getValue(),itMargin->second.getValue());
			}
		}
	}
	//9.检查Account表中多空保证金之和longmargin+shortmargin=margin,同时Prebalance字段不能为0或者DBL_MAX
	CInvestorAccount* pInvestorAccount=m_pDB->m_InvestorAccountFactory->getFirst();
	while(pInvestorAccount!=NULL)
	{
		//20131010 xuzh 由于场下数据库只保留3位小数,场上计算需要的误差范围为0.001即可
		if (fabs(pInvestorAccount->LongMargin+pInvestorAccount->ShortMargin-pInvestorAccount->Margin)>0.001)
		{
			genError("帐号[%s]的多/空头保证金占用金额分别为[%f],[%f]，但是总的占用保证金为[%f]",
				pInvestorAccount->AccountID.getValue(),pInvestorAccount->LongMargin.getValue(),pInvestorAccount->ShortMargin.getValue(),pInvestorAccount->Margin.getValue());
		}
		if (pInvestorAccount->PreBalance==0.0)
		{
			genError("帐号[%s]的昨可用资金PreBalance为0.0",pInvestorAccount->AccountID.getValue());
		}
		if (pInvestorAccount->PreBalance==DBL_MAX)
		{
			genError("帐号[%s]的昨可用资金PreBalance为DBL_MAX",pInvestorAccount->AccountID.getValue());
		}
		//检查InvestorID是否存在,20130520,wangwei
		CInvestor* pInvestor=m_pDB->m_InvestorFactory->findByBrokerIDInvestorID(pInvestorAccount->BrokerID,pInvestorAccount->InvestorID);
		if (pInvestor==NULL)
		{
			genError("帐号[%s]对应的InvestorID[%s]在Investor表中找不到",pInvestorAccount->AccountID.getValue(),pInvestorAccount->InvestorID.getValue());
		}
		pInvestorAccount=m_pDB->m_InvestorAccountFactory->getNext();
	}
	m_pDB->m_InvestorAccountFactory->endGet();

	//10. 检查合约表中昨结算价、限价/市价最大最小报单手数的值是否合理
	CInstrument* pInstrument = m_pDB->m_InstrumentFactory->getFirst();
	while(pInstrument != NULL )
	{
        if( !pInstrument->PreSettlementPrice.isValid()  || 
		 	 pInstrument->MaxLimitOrderVolume  < 0      ||
			 pInstrument->MinLimitOrderVolume  < 0      ||
			 pInstrument->MaxMarketOrderVolume < 0      ||
			 pInstrument->MinMarketOrderVolume < 0 )
		{
			 genError("合约[%s]属性关键字段错误:PreSettlementPrice:[%f], MaxLimitOrderVolume:[%d],MinLimitOrderVolume:[%d],MaxMarketOrderVolume:[%d],MinMarketOrderVolume:[%d]", \
				       pInstrument->InstrumentID.getValue(),pInstrument->PreSettlementPrice.getValue(),pInstrument->MaxLimitOrderVolume.getValue(), \
					   pInstrument->MinLimitOrderVolume.getValue(), pInstrument->MaxMarketOrderVolume.getValue(),pInstrument->MinMarketOrderVolume.getValue());
			     
		}
		pInstrument = m_pDB->m_InstrumentFactory->getNext();
	}
    m_pDB->m_InstrumentFactory->endGet();
}

void CInitCheckTrigger::genError(const char *format,...)
{
	va_list v;
	va_start(v,format);
	fprintf(output,"\t");
	vfprintf(output,format,v);
	fprintf(output,"\n");
	errorCount++;
	va_end(v);
}

