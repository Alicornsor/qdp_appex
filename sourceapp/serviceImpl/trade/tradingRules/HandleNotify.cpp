/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file COrderInsertRules.h
///@briefʵ������COrderInsertRules
///@history 
///20060113	xuzh		�������ļ�
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
// 		printf("CHandleNotify::HandleSeatDisconnected �Ҳ��� ExchangeID=[%s],SeatID=[%s] ��Ӧ��ϯλ״̬��¼\n",pLoginInfo->ExchangeID.getValue(),pLoginInfo->SeatID.getValue());
// 		return false;
// 	}
// 	// longqy ����ϯλ�����������ӣ���;������Ҫ��Ԥί�б���ɾ��
// 	int	nOldLocalID = 0;
// 	int nNewLocalID = 0;
// 	if(pLoginInfo->OrderLocalID.isNull())
// 	{	// �����¼��������ʱ��û�б���������󱾵ر�����Ϊ�ա���ʱ����ɾ����ʧ����;������
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
// 	{	// �ж������������ܾ�
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
// 	// ���ر�����ȡΪ������ȷ�ϵĺ��룬�뱾�صĺ�������ֵ���ټ�1 ��ȷ�������غ���
// 	sprintf(buf,"%012d",++nMaxLocalID);
// 	theSeat.OrderLocalID = buf;
// 	theSeat.SeatStatus = SS_Login;//ϯλ�Ѿ����� by wangwei
// 	m_pDB->m_SeatFactory->addOrUpdate(pTSeat,&theSeat,NULL);
// 	return bSuccess;
// }
/*	��ʱ��ͬ�����ݰ��е�ʱ�䣬ͬ�����ڴ����ݿ�� CurrentTime ��ȥ�������������������ݵ�ʱ���õ�ʱ�䣬
//	���ǵ�ʱʵ�ʽ��׵�ʱ�䡣�� CurrentTime ��ʵ����ֻ��һ��ʱ���¼�������˵�ǰʱ�����һ�ε�ʱ�䡣
//	��ʱ�������㶯̬ӯ����Ҳ�Ǹ������ʱ������ʱ�ӵģ��������ü�������ص�ʱ�䡣 longqy 20130822 ��
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

/*	�յ����µ��������ݣ�Ŀǰ������һ�����飬���������ݱ��浽�ڴ����ݿ�� MarketData �С�
//  �� MarketData �е�ÿ����Լֻ��һ����¼���ǰ��µ����ݸ��»������ӵ�������С�
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

//�˻��ֲ�ӯ��
//wangwei,20130502, ֧�ֶ��Ա�ĸ���
struct stBrokerAccount
{
	CBrokerIDType BrokerID;
	CAccountIDType AccountID;
	//��������������������޷��õ�map��ȥ
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
	//���ݳֲ�������ҵ��ֲֵ����к�Լ��������ѯ����
	CSendInstrumentMap SendInstrumentMap;
	CInvestorPosition* pInvestorPosition = m_pDB->m_InvestorPositionFactory->getFirst();
	while(NULL != pInvestorPosition)
	{
		//ԭ�����ǵ��гֲֲŷ��������ѯ����
		//����1������۵Ĳ�ѯֻҪ�гɽ�����Ҫ��ѯ���飬�ͳֲ����޹�
		//    2��һ��Ͷ����û�гֲ֡���������гֲ֣�Ҳ��Ҫ����������Ͷ���߶������£���Լ��ѯ����Ŀ���ܲ�����̫��ı�
		//���ԣ�ֻҪ�гֲּ�¼���ھͲ�ѯ����
		CInstrument *pInstrument = m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pInvestorPosition->ExchangeID,pInvestorPosition->InstrumentID);
		if (pInstrument != NULL && 
			PC_Futures == pInstrument->ProductClass)
		{		
			//�����ѯ��������,����Ѿ����͹��ˣ������ٷ�����
			CSendInstrumentMap::iterator iter = SendInstrumentMap.find(pInvestorPosition->InstrumentID);
			if(iter == SendInstrumentMap.end())
			{
				SendInstrumentMap.insert(CSendInstrumentMap::value_type(pInvestorPosition->InstrumentID,pInvestorPosition));
				//QDPMD ��Ϊ�������ű������ϳ��ļ��й̶������������ҵ���Ӧ��ģ��
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
	// xuzh ����ʹ�ã�ǧ��Ҫ�������д�
	//	CConfig *pConfig= new CConfig("qtrade.ini");
	//	m_pDB->m_InvestorPositionFactory->writeCSV(pConfig);
	
	//	mpAcntPosPrft tmpMpAcntPosPrft;
	//	tmpMpAcntPosPrft.clear();
	
	if(!m_bCalcDynamicProfitSwitch)
	{
		return;
	}
	
	//���������ǰ��պ�Լ�����㣬���ǰ������еĳֲּ��㣬����ͳһ����ӯ��
	//ֻ�ܰ���ӯ���ı仯������ӯ���ı䶯
	//���ڻ����������Ӻ�Լ
	if(pInstrument==NULL||pMarketData==NULL||
		PC_Futures !=pInstrument->ProductClass )
	{
		//�Ҳ�����Լ�����ټ���ֲ�ӯ��-wangwei,20130814
		return;
	}
	
	//������㼸�����¼���Ч�������1.ΪDBL_MAX;2.Nan;3.Ϊ0.0
	//modified by chengm 20161212 ���Ӷ�lastprice=0���ж�
	if(pMarketData->LastPrice.isNull() || pMarketData->LastPrice == 0.0)
	{
		return;
	}
	
	//�����ͻ��ֱֲ�
	CInvestorPosition* pInvestorPosition=m_pDB->m_InvestorPositionFactory->startFindAllByExIDAndInstrumentID(pInstrument->ExchangeID,pInstrument->InstrumentID);
	CWriteableInvestorPosition WriteableInvestorPosition;
	bool bFirtst=true;
	for(;pInvestorPosition!=NULL;pInvestorPosition=m_pDB->m_InvestorPositionFactory->findNextAllByExIDAndInstrumentID())	
	{
		//����ֲ�Ϊ0������ӯ��ҲΪ0,����Ҫ�ټ�����		
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
		
		//���Ͷ���߲���Ҫ����ʽ𣬲�����ֲ�ӯ��
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
	
	pTime++;//����ð��
	
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
		//CTP�ĺ�Լ״̬�ǲ�Ʒ�ţ���̫������
		//������Ҫ���ղ�Ʒ�ҵ����еĺ�Լ�����ú�Լ״̬
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
				//added by chengm 20160816 ���Ӷ���Ϻ�Լ״̬����
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

/*	���� RemoveFaildPreOrder ����ʧ����;�������Ѷ�ʧ�Ķ�����Ԥ��������ɾ�������������
//	�������ر����� OrderLocalID ����Ϊ ��1 �������ҵġ��п��ܴ�Ԥ�������в鲻�����������������ġ�
//  longqy@cffex.net 2013-05-13
*/
// int CHandleNotify::RemoveFaildPreOrder(CExchangeIDType&  ExchangeID,CSeatIDType&  SeatID,COrderLocalIDType  &OrderLocalID,CTransaction *pTransaction,vector<CWriteablePreOrder*> &PreOrders)
// {
// 	CPreOrder* pPreOrder   = NULL;
// 	pPreOrder = m_pDB->m_PreOrderFactory->findByAPIIDAndOrderLocalID(ExchangeID,SeatID,OrderLocalID);
// 
// 	if(pPreOrder == NULL)  //��Ԥί�б����޷��ҵ������ǿ��ܵġ����ر������������Ծ����������
// 	{
// 		REPORT_EVENT(LOG_WARNING,"This order cann't be found in PreOrder table ", "ExchangeID: %s, SeatID: %s , OrderLocalID: %s \n", ExchangeID.getValue(),SeatID.getValue(),OrderLocalID.getValue());
// 		return -1;
// 	}else //�� -  �����ɽ��������ص�δ��ȷ�ϵ���Ϣ  Ԥί�б����
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
// 		if( NULL ==  pOrderInsertFailed)    //Ԥί�б��д��ڣ������в�����
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
// 				default: 	// δ�ҵ���Լ����,ֱ�ӷ��ء�
// 				   {   
// 					   REPORT_EVENT(LOG_WARNING,"Can not Find Instrument Class ", "In Line %d of File %s.\n",__LINE__,__FILE__);
// 					   m_pErrorEngine->reportError(ERROR_INSTRUMENT_NOT_FOUND);
// 					   return 2;
// 				   }
// 			   }
// 			}
// 			//ʧЧ�����ʽ�
// 			bSuccess = m_pMoneyPosition->RspOrderMoneyUnFrozen(pInvestorAccount,pPreOrder,pTransaction);
// 			if(false == bSuccess )      
// 			{
// 				REPORT_EVENT(LOG_CRITICAL,"Can not UnFrozen Money  ", "In Line %d of File %s.\n",__LINE__,__FILE__);
// 				return 2;
// 			}
// 			//ʧЧ����ֲ�
// 			bSuccess  = m_pMoneyPosition->RspPositionUnFrozen(pInvestorPosition,pPreOrder,pTransaction);
// 			if(false == bSuccess)
// 			{
// 				REPORT_EVENT(LOG_CRITICAL,"Can not UnFrozen  Position ", "In Line %d of File %s.\n",__LINE__,__FILE__);
// 				return 3;
// 			}
// 			//�������
// 			CWriteableOrderInsertFailed theWriteableOrderInsertFailed;
// 			theWriteableOrderInsertFailed.init();
// 			CopyOrderEntity(&theWriteableOrderInsertFailed,pPreOrder);
// 			theWriteableOrderInsertFailed.ErrorMsg = "Order lost on the way from FEMAS to Exchange. \n";
// 
// 			//��΢���ȷʱ����뵽UserCustom�ֶΣ���Ϊ���������֮һ liumeng 20140820
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
// 				//���ش��󣬲������ʧ��
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
/* ��ʼ���ļ��ȫ���ƶ�������ط� by wangwei ,20130510                                                                     */
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
				genError("%s�е��ֶ�%s��ֵ%s�ظ�",#tableName,#fieldName,value);\
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
				genError("%s�е��ֶ�%s��ֵ%d�ظ�",#tableName,#fieldName,value);\
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
				genError("%s�е��ֶ�%s,%s��ֵ%s,%s�ظ�",#tableName,#fieldName1,#fieldName2,buffer1,buffer2);\
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
				genError("%s�е��ֶ�%s,%s,%s��ֵ%s,%s,%s�ظ�",#tableName,#fieldName1,#fieldName2,#fieldName3,buffer1,buffer2,buffer3);\
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
				genError("%s�е��ֶ�%s,%s,%s,%s��ֵ%s,%s,%s,%s�ظ�",#tableName,#fieldName1,#fieldName2,#fieldName3,#fieldName4,buffer1,buffer2,buffer3,buffer4);\
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
				genError("%s�е��ֶ�%s,%s,%s,%s,%s��ֵ%s,%s,%s,%s,%s�ظ�",#tableName,#fieldName1,#fieldName2,#fieldName3,#fieldName4,#fieldName5,buffer1,buffer2,buffer3,buffer4,buffer5);\
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
			genError("%s�е��ֶ�%s,%s,%s,%s,%s,%s��ֵ%s,%s,%s,%s,%s,%s�ظ�",#tableName,#fieldName1,#fieldName2,#fieldName3,#fieldName4,#fieldName5,#fieldName6,buffer1,buffer2,buffer3,buffer4,buffer5,buffer6);\
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
				genError("%s���ֶ�%s��ֵ%s��Ӧ��%s�Ҳ���",#tableName,#keyName,buffer,#factoryName);		\
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
					genError("%s���ֶ�%s��ֵ%s��Ӧ��%s�Ҳ���",#tableName,#keyName,buffer,#factoryName);		\
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
				genError("%s���ֶ�%s��ֵ%s��Ӧ��%s�Ҳ���",#tableName,#keyName,buffer,#factoryName);		\
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
				genError("%s���ֶ�%s��ֵ%s��Ӧ��%s�Ҳ���",#tableName,#keyName,buffer,#factoryName);		\
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
				genError("%s���ֶ�%s��ֵ%s��Ӧ�����%s�Ҳ���",#tableName,#keyName,buffer,#foreignName);		\
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
				genError("%s���ֶ�%s��ֵ%s��Ӧ��%s�Ҳ���",#tableName,#keyName,buffer,#factoryName);		\
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
				genError("%s���ֶ�%s��ֵ%s��Ӧ��%s�Ҳ���",#tableName,#keyName,buffer,#factoryName);		\
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
				genError("%s���ֶ�%s,%s��ֵ%s,%s��Ӧ��%s�Ҳ���",#tableName,#keyName1,#keyName2,buffer1,buffer2,#factoryName);		\
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
			genError("%s���ֶ�%s,%s,%s��ֵ%s,%s,%s��Ӧ��%s�Ҳ���",#tableName,#keyName1,#keyName2,#keyName3,buffer1,buffer2,buffer3,#factoryName);		\
			}																\
			pitem=m_pDB->m_ ## tableName ## Factory->getNext();				\
		}																	\
		m_pDB->m_ ## tableName ## Factory->endGet();							\
	}

///-----------------------
///	xuzh��20080416�������˶������ʼ��������ȱ����������������ʱ�ı���
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
			genError("%s����%s��¼��%sȡֵ������Ϊ�ջ���Ϊ0",#tableName,buffer,#checkName);	\
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
				genError("%s����%s��¼��%sȡֵ������Ϊ�ջ���Ϊ0",#tableName,buffer,#checkName);	\
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
	//����
	CBaseCheck::m_SystemStatus=pSystemStatus->SystemStatus;
	
	if (pSystemStatus->SystemStatus==SS_InstrumentTradingDayDown)
	{
		//��Լ�Ѿ���ѯ���������Կ�ʼ���г�ʼ�����ݵļ��
		///�����ݼ�������ļ�
		char *filename=m_Config->getConfig("ConsistentCheck");
		if (filename[0]=='\0')
		{
			///û�д������ã��Ǿͷ���
			return;
		}
		output=mfopen(filename,"w+t");
		if (output==NULL)
		{
			///�޷����ļ����Ǿͷ���
			REPORT_EVENT(LOG_CRITICAL,"EnvError","can not open consistent check file");
			return;
		}
		
		///��ʼ����һ���Լ��
		errorCount=0;
		fprintf(output,"--------ͬ����ɺ���--------\n");
		
		///�����Ǹ�����Ҫ���ݱ�Ĵ�С
		fprintf(output,"�����С\n");
		//2014-06-25 longqy ��flush�ļ����������
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
		
		///���ݸ�ʽ���
		///���ȼ�齻����
		
		if (m_pDB->m_SystemStatusFactory->getCount()!=1)
		{
			genError("DataSyncStatus���������Ŀ����");
		}
		
		///���ͻ�����
		if (m_pDB->m_InvestorFeeFactory->getCount()<1)
		{
			genError("InvestorFee���������Ŀ����С��1");
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
		
		
		///���ͻ���֤����
		if (m_pDB->m_InvestorMarginFactory->getCount()<1)
		{
			genError("InvestorMargin���������Ŀ����С��1");
		}
		checkUnique5(InvestorMargin,BrokerID,ExchangeID,InstrumentID,InvestorID,HedgeFlag,ByBrkIDExIDIstIDVstIDHdg);
//		checkForeign3(InvestorMargin,BrokerID,ExchangeID,ClientID,ClientTradingID,ByBrokerIDExchangeIDClientID);
//		checkForeign2(InvestorMargin,ExchangeID,InstrumentID,Instrument,ByExchangeIDAndInstrumentID);	
		checkValidField(InvestorMargin,InvestorID,LongMarginRate,notNullRatio);
		checkValidField(InvestorMargin,InvestorID,ShortMarginRate,notNullRatio);
		checkValidField(InvestorMargin,InvestorID,LongMarginAmt,notNullRatio);
		checkValidField(InvestorMargin,InvestorID,ShortMarginAmt,notNullRatio);
		
		///���ͻ��ֱֲ�
		checkUnique6(InvestorPosition,BrokerID,ExchangeID,InvestorID,InstrumentID,Direction,HedgeFlag,ByBrkIDExIDInvIDInsDirHed);
		//	checkForeign(InvestorPosition,TradingDay,DataSyncStatus,ByTradingday);
//		checkForeign4(InvestorPosition,BrokerID,ExchangeID,Participant,ClientID,ClientTradingID,ByBrokerIDExchangeIDPartClientID);
		
		///��齻�ױ����ClientTradingID
		checkUnique4(ClientTradingID,BrokerID,ExchangeID,ParticipantID,ClientID,ByBrokerIDExchangeIDPartClientID);
		checkForeign2(ClientTradingID,BrokerID,AccountID,InvestorAccount,ByBrokerIDAccountID);
//		checkForeign3(ClientTradingID,BrokerID,ExchangeID,ParticipantID,Participant,ByBrokerIDExchangeIDAndParticipantID);
			
		///��齻����Exchange
		checkUnique(Exchange,ExchangeID);
		if (m_pDB->m_ExchangeFactory->getCount()<1)
		{
			genError("Exchange���������Ŀ����");
		}
		
		///����Լ��Instrument
		//del by wangwei, 20130530, ��Լ�����ϳ��ģ�ȡ�����

// 		checkUnique2(Instrument,ExchangeID,InstrumentID,ByExchangeIDAndInstrumentID);
// 		checkForeign2(Instrument,ExchangeID,ProductID,Product,ByExchangeIDAndProductID);
// 		checkValidField(Instrument,InstrumentID,UnderlyingMultiple,notNullMultiple);
// 		checkValidField(Instrument,InstrumentID,PriceTick,notNullPrice);	
// 		checkValidField(Instrument,InstrumentID,LowerLimitPrice,notNullPrice);
// 		checkValidField(Instrument,InstrumentID,UpperLimitPrice,notNullPrice);		
// 		checkValidField(Instrument,InstrumentID,PreSettlementPrice,notNullPrice);			
		
		///Ͷ���� Investor
		checkUnique2(Investor,BrokerID,InvestorID,ByBrokerIDInvestorID);
		if (m_pDB->m_InvestorFactory->getCount()<1)
		{
			genError("Investor���������Ŀ����");
		}
		
		///����ʽ�� InvestorAccount
		checkUnique2(InvestorAccount,BrokerID,AccountID,ByBrokerIDAccountID);
		//	checkForeign(InvestorAccount,TradingDay,DataSyncStatus,ByTradingday);
		checkForeign2(InvestorAccount,BrokerID,InvestorID,Investor,ByBrokerIDInvestorID);
		checkValidField(InvestorAccount,AccountID,PreAvailable,notNullMoney);
		checkValidField(InvestorAccount,AccountID,LongMargin,notNullMoney);
		checkValidField(InvestorAccount,AccountID,ShortMargin,notNullMoney);
		checkValidField(InvestorAccount,AccountID,PreBalance,notNullMoney);
		checkValidField(InvestorAccount,AccountID,Margin,notNullMoney);
						
		///���ϯλ�� Seat
		checkUnique3(Seat,BrokerID,ExchangeID,SeatID,ByBrokerIDExchangeIDSeatID);
		if (m_pDB->m_SeatFactory->getCount()<1)
		{
			genError("Seat���������Ŀ����");
		}
		
		///�û��� User
		checkUnique2(User,BrokerID,UserID,ByBrokerIDUserID);
		if (m_pDB->m_UserFactory->getCount()<1)
		{
			genError("User���������Ŀ����");
		}
		
		///�û�ϯλ�� UserInvestor
		checkUnique3(UserInvestor,BrokerID,UserID,InvestorID,ByBrokerIDUserIDInvestorID);
		checkForeign2(UserInvestor,BrokerID,UserID,User,ByBrokerIDUserID);
		checkForeign2(UserInvestor,BrokerID,InvestorID,Investor,ByBrokerIDInvestorID);
		
		///�û�����Ȩ�ޱ� UserTradingRight
		checkUnique5(UserTradingRight,BrokerID,ExchangeID,InstrumentID,UserID,InvestorID,ByBrkExIDInsUserInv);
		checkForeign2(UserTradingRight,ExchangeID,InstrumentID,Instrument,ByExchangeIDAndInstrumentID);
		
		///ҵ����
		businessCheck();
		
		///����˼��
		fprintf(output,"��%d������\n",errorCount);
		fclose(output);
		//add by wangwei, 20130607
		m_pDB->save(m_Config);
	}
}


void CInitCheckTrigger::businessCheck()
{
	fprintf(output,"ҵ����\n");
	CInvestorPosition *pInvestorPosition=NULL;
	CAcntDirMarginMap acntDirMarginMap;
	acntDirMarginMap.clear();

	CAcntDirIdx idx;
	//�˴���ʱ������YdPosition
	for (pInvestorPosition=m_pDB->m_InvestorPositionFactory->getFirst();
	pInvestorPosition!=NULL;
	pInvestorPosition=m_pDB->m_InvestorPositionFactory->getNext())			
	{
		//1.���ֲ��Ƿ�Ϊ0
		if (pInvestorPosition->Position==0)
		{
			genError("�ͻ��ֱֲ���ClientID[%s],InstrumentID[%s],Direction[%c],HedgeFlag[%c]��Ӧ�ļ�¼Position�ֶ�Ϊ0����û�б�ɾ��",
				pInvestorPosition->ClientID.getValue(),pInvestorPosition->InstrumentID.getValue(),
				pInvestorPosition->Direction.getValue(),pInvestorPosition->HedgeFlag.getValue());
			continue;
		}		
		//2.����Լ�Ƿ����
		CInstrument *pInstrument=m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pInvestorPosition->ExchangeID,pInvestorPosition->InstrumentID);
		if (pInstrument==NULL)
		{
			genError("��Instrument�����Ҳ���������[%s]��Լ[%s]��Ӧ�ļ�¼",pInvestorPosition->ExchangeID.getValue(),pInvestorPosition->InstrumentID.getValue());
			continue;
		}
		//3.���Ͷ�����˻��Ƿ����
		CInvestorAccount* pInvestorAccount=m_pDB->m_InvestorAccountFactory->findByBrokerIDAccountID(pInvestorPosition->BrokerID,pInvestorPosition->AccountID);
		if (pInvestorAccount==NULL)
		{
			genError("�ͻ��ֲּ�¼�е�AccountID[%s]��InvestorAccount�����Ҳ���",pInvestorPosition->AccountID.getValue());
			continue;
		}
		//4.��齻�ױ���
		CClientTradingID* pClientTradingID=m_pDB->m_ClientTradingIDFactory->findByBrokerIDExchangeIDPartClientID(pInvestorPosition->BrokerID,pInvestorPosition->ExchangeID,pInvestorPosition->ParticipantID,pInvestorPosition->ClientID);
		if (pClientTradingID==NULL)
		{
			pClientTradingID=m_pDB->m_ClientTradingIDFactory->findByBrokerIDExchangeIDPartClientID(pInvestorPosition->BrokerID,"Broker",pInvestorPosition->ParticipantID,pInvestorPosition->ClientID);
			if (pClientTradingID==NULL)
			{
				genError("�ͻ��ֲּ�¼�е�ExchangeID[%s],ClientID[%s]��ClientTradingID�����Ҳ�����Ӧ�ļ�¼",pInvestorPosition->ExchangeID.getValue(),pInvestorPosition->ClientID.getValue());
				continue;
			}

		}
		//5.���InvestorID�Ƿ����
		CInvestor* pInvestor=m_pDB->m_InvestorFactory->findByBrokerIDInvestorID(pInvestorPosition->BrokerID,pClientTradingID->InvestorID);
		if (pInvestor==NULL)
		{
			genError("Ͷ���ߺ�InvestorID[%s]��Investor�����Ҳ���",pClientTradingID->InvestorID.getValue());
			continue;
		}
		//6.���ͻ���֤�����Ƿ����
		CInvestorMargin* pInvestorMargin=m_pDB->m_InvestorMarginFactory->findByBrkIDExIDIstIDVstIDHdg(pInvestorPosition->BrokerID,pInvestorPosition->ExchangeID,pInvestorPosition->InstrumentID,pInvestorPosition->InvestorID,pInvestorPosition->HedgeFlag);
		if (pInvestorMargin==NULL)
		{
			genError("ExchangeID[%s],ClientID[%s],InstrumentID[%s]�Ŀͻ���֤������InvestorMargin�����Ҳ���",
				pInvestorPosition->ExchangeID.getValue(),pInvestorPosition->ClientID.getValue(),pInvestorPosition->InstrumentID.getValue());
			continue;
		}
		//7.��鱣֤��ռ���Ƿ���ȷ
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

		//20131010 xuzh ���ڳ������ݿ�ֻ����3λС��,���ϼ�����Ҫ����ΧΪ0.001����
		if (fabs(pInvestorPosition->UsedMargin-UsedMargin)>0.001)
		{
			genError("�ͻ��ֱֲ���ClientID[%s],InstrumentID[%s],PosiDirection[%c]�Ŀͻ��ֱֲ�֤��UsedMargin���㲻��ȷ"
				"��ʼ����Ϊ[%f]�����ݹ������ӦΪ[%f]",				
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
		//�ۼ�ռ�ñ�֤��
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

	//8.��鱣֤��ռ���Ƿ���account����һ��
	for (CAcntDirMarginMap::iterator itMargin=acntDirMarginMap.begin();itMargin!=acntDirMarginMap.end();itMargin++)
	{
		CInvestorAccount* pInvestorAccount=m_pDB->m_InvestorAccountFactory->findByBrokerIDAccountID(itMargin->first.BrokerID,itMargin->first.AccountID);
		if (pInvestorAccount!=NULL)
		{
			if (itMargin->first.Direction==D_Buy&&itMargin->second!=pInvestorAccount->LongMargin)
			{
				genError("�ʺ�[%s]�Ķ�ͷ��֤��ռ�ý��Ϊ[%f]�����Ǹ��ݿͻ��ֲּ���Ľ��Ϊ[%f]",
					pInvestorAccount->AccountID.getValue(),pInvestorAccount->LongMargin.getValue(),itMargin->second.getValue());
			}
			if (itMargin->first.Direction==D_Sell&&itMargin->second!=pInvestorAccount->ShortMargin)
			{
				genError("�ʺ�[%s]�Ŀ�ͷ��֤��ռ�ý��Ϊ[%f]�����Ǹ��ݿͻ��ֲּ���Ľ��Ϊ[%f]",
					pInvestorAccount->AccountID.getValue(),pInvestorAccount->ShortMargin.getValue(),itMargin->second.getValue());
			}
		}
	}
	//9.���Account���ж�ձ�֤��֮��longmargin+shortmargin=margin,ͬʱPrebalance�ֶβ���Ϊ0����DBL_MAX
	CInvestorAccount* pInvestorAccount=m_pDB->m_InvestorAccountFactory->getFirst();
	while(pInvestorAccount!=NULL)
	{
		//20131010 xuzh ���ڳ������ݿ�ֻ����3λС��,���ϼ�����Ҫ����ΧΪ0.001����
		if (fabs(pInvestorAccount->LongMargin+pInvestorAccount->ShortMargin-pInvestorAccount->Margin)>0.001)
		{
			genError("�ʺ�[%s]�Ķ�/��ͷ��֤��ռ�ý��ֱ�Ϊ[%f],[%f]�������ܵ�ռ�ñ�֤��Ϊ[%f]",
				pInvestorAccount->AccountID.getValue(),pInvestorAccount->LongMargin.getValue(),pInvestorAccount->ShortMargin.getValue(),pInvestorAccount->Margin.getValue());
		}
		if (pInvestorAccount->PreBalance==0.0)
		{
			genError("�ʺ�[%s]��������ʽ�PreBalanceΪ0.0",pInvestorAccount->AccountID.getValue());
		}
		if (pInvestorAccount->PreBalance==DBL_MAX)
		{
			genError("�ʺ�[%s]��������ʽ�PreBalanceΪDBL_MAX",pInvestorAccount->AccountID.getValue());
		}
		//���InvestorID�Ƿ����,20130520,wangwei
		CInvestor* pInvestor=m_pDB->m_InvestorFactory->findByBrokerIDInvestorID(pInvestorAccount->BrokerID,pInvestorAccount->InvestorID);
		if (pInvestor==NULL)
		{
			genError("�ʺ�[%s]��Ӧ��InvestorID[%s]��Investor�����Ҳ���",pInvestorAccount->AccountID.getValue(),pInvestorAccount->InvestorID.getValue());
		}
		pInvestorAccount=m_pDB->m_InvestorAccountFactory->getNext();
	}
	m_pDB->m_InvestorAccountFactory->endGet();

	//10. ����Լ���������ۡ��޼�/�м������С����������ֵ�Ƿ����
	CInstrument* pInstrument = m_pDB->m_InstrumentFactory->getFirst();
	while(pInstrument != NULL )
	{
        if( !pInstrument->PreSettlementPrice.isValid()  || 
		 	 pInstrument->MaxLimitOrderVolume  < 0      ||
			 pInstrument->MinLimitOrderVolume  < 0      ||
			 pInstrument->MaxMarketOrderVolume < 0      ||
			 pInstrument->MinMarketOrderVolume < 0 )
		{
			 genError("��Լ[%s]���Թؼ��ֶδ���:PreSettlementPrice:[%f], MaxLimitOrderVolume:[%d],MinLimitOrderVolume:[%d],MaxMarketOrderVolume:[%d],MinMarketOrderVolume:[%d]", \
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

