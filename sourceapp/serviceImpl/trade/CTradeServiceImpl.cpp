/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file CTradeServiceImpl.h
///@brief实现了类CTradeServiceImpl
///@history 
///20060113	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CTradeServiceImpl.h"
#include "tradingTools.h"
#include "ExchangeLinkManager.h"
#include "system.h"
extern const CClientIDType defaultClientID;
extern CExchangeLinkManager* g_pExchangeLinkManager;
extern bool    g_bLatencyOut;
#ifdef DEBUG_NOT_LOG_1
void increaseCount(void)
{
	static int lastCount=0;
	static int count=0;
	static time_t lastTime=0;
	static time_t firstTime=0;
	if (count==0)
	{
		time(&lastTime);
		firstTime=lastTime;
	}
	else if (count%100==0)
	{
		time_t thisTime;
		time(&thisTime);
		if (thisTime!=lastTime)
		{
			printf("init:%d,%d,%d\n",thisTime-firstTime,(count)/(thisTime-firstTime),(count-lastCount)/(thisTime-lastTime));
			fflush(stdout);
			lastCount=count;
			lastTime=thisTime;
		}
	}
	count++;
}
#endif

CTradeServiceImpl::CTradeServiceImpl(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow *pTradeResult)
{
	m_pDB=pDB;
	m_pErrorEngine=pErrorEngine;
	m_pConfig=pConfig;
	m_pTradeResult = pTradeResult;
	m_pPubMessage = new CXTPPackage();
	m_pPubMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE, XTPHLEN);


	m_pHandleFutureOrder  = new CHandleFutureOrder(pDB,pErrorEngine,pConfig,pTradeResult);
//	m_pHandleOptionOrder  = new CHandleOptionOrder(pDB,pErrorEngine,pConfig,pTradeResult);
	
	m_pHandleNotify = new CHandleNotify(pDB,pErrorEngine,pConfig,pTradeResult);
	

	m_pHandleFutureTrade  = new CHandleFutureTrade(pDB,pErrorEngine,pConfig,pTradeResult);
//	m_pHandleOptionTrade  = new CHandleOptionTrade(pDB,pErrorEngine,pConfig,pTradeResult);


	m_pHandleFutureOrderAction =  new CHandleFutureOrderAction(pDB,pErrorEngine,pConfig,pTradeResult);
//	m_pHandleOptionOrderAction =  new CHandleOptionOrderAction(pDB,pErrorEngine,pConfig,pTradeResult);	
	
	char* fileName=currentConfig->getConfig("OrderActionFailedLog");
	if (fileName[0]!='\0')
	{
		m_orderActionFailedLog=mfopen(fileName,"w+t");
	}
	else
	{
		m_orderActionFailedLog=NULL;
	}
	if (m_orderActionFailedLog!=NULL)
	{
		fprintf(m_orderActionFailedLog,"Time,Reason,");
		CWriteableOrderAction::writeCSVHead(m_orderActionFailedLog);
		fflush(m_orderActionFailedLog);
	}

	m_PartGroupPosition.clear();
}

bool CTradeServiceImpl::isSuperSession(const TSessionRef &sessionRef)
{
	if (sessionRef.SessionID!=0)
	{
		m_pErrorEngine->reportError(ERROR_INVALID_SESSION);
		return false;
	}
	return true;
}

bool CTradeServiceImpl::initExchange(CWriteableExchange *pExchange,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//检查是否超级会话
	if (!isSuperSession(sessionRef))
	{
		return false;
	}

	//判断状态是否允许
//	if (getExchangeDataSyncStatus(m_DB)!=DS_Synchronizing)
//	{
//		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
//		return false;
//	}

#ifdef DEBUG_NOT_LOG_1
	increaseCount();
#endif

	m_pDB->m_ExchangeFactory->add(pExchange,pTransaction);
	return true;
}

bool CTradeServiceImpl::ReqOrderInsert(CXTPPackage *pPackage,const TSessionRef &sessionRef)
{
	int CoreRecvDown=0;
	GET_ACCURATE_USEC_TIME(CoreRecvDown);
	bool bSuccess = true;
	
	CWriteablePreOrder thePreOrder;
	thePreOrder.init();
	XTP_GET_SINGLE_FIELD(pPackage,&thePreOrder);
	if (thePreOrder.HedgeFlag.isNull() ||
		!thePreOrder.HedgeFlag.isValid())
	{
		thePreOrder.HedgeFlag = CHF_Speculation;
	}
	// 	//增加frontid和sesssionid
	COPY_SESSIONREF_INFO(&thePreOrder,&sessionRef);
	thePreOrder.CoreRecvDown = CoreRecvDown;
	thePreOrder.FTdRecvDown = pPackage->GetGroupID();


	CWriteableIndexPreOrder wtbIndexPreOrder;
	CIndexPreOrder *pIndexPreOrder=m_pDB->m_IndexPreOrderFactory->findByALLFlds(thePreOrder.BrokerID,thePreOrder.ExchangeID,thePreOrder.InvestorID,thePreOrder.InstrumentID,thePreOrder.HedgeFlag);
	if (likely(pIndexPreOrder != NULL))
	{
		thePreOrder.linkIndexPreOrder(pIndexPreOrder);
		m_pDB->m_IndexPreOrderFactory->retrieve(pIndexPreOrder,&wtbIndexPreOrder);
	}
	else
	{
		wtbIndexPreOrder.init();
		bSuccess =m_pHandleFutureOrder->InitIndexPreOrder(&thePreOrder,&wtbIndexPreOrder,&m_Transaction);
		if (!bSuccess)
		{
			char* errMsg;
			int errorCode;
			m_pErrorEngine->getLastError(&errorCode,&errMsg);
			m_pPubMessage->PrepareResponse(pPackage,TID_RspOrderInsert);
			CRspInfoField responseField;				
			responseField.ErrorID = errorCode;
			responseField.ErrorMsg = errMsg;
			thePreOrder.DealFlag = DF_Wait;
			XTP_ADD_FIELD(m_pPubMessage,&thePreOrder);
			XTP_ADD_FIELD(m_pPubMessage,&responseField);
			m_pPubMessage->MakePackage();
			m_pTradeResult->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
			
			m_Transaction.rollback();
			return false;
		}
		pIndexPreOrder =thePreOrder.getIndexPreOrder();
	}


	switch (pIndexPreOrder->ProductClass )
	{
	case PC_Futures:
		{
			thePreOrder.BusinessType = BT_Normal;
			m_pHandleOrder = m_pHandleFutureOrder;
			break;
		}
// 	case PC_Options:
// 		{
// 			thePreOrder.BusinessType = BT_Normal;
// 			m_pHandleOrder = m_pHandleOptionOrder;
// 			break;
// 		}
	default:   // 未找到合约类型，为错单。用期货对象进行本地报单错误处理，直接返回。
		{	
			m_pErrorEngine->reportError(ERROR_INSTRUMENT_NOT_FOUND);
			m_pHandleOrder = m_pHandleFutureOrder;
			m_pHandleOrder->HandleLocalOrderInsertFailed(&thePreOrder);
			return false;
		}
	}
	bSuccess = m_pHandleOrder->HandleOrderInsert(&wtbIndexPreOrder,&thePreOrder,sessionRef,&m_Transaction);
	//插入错单表不需要事务过程，直接插入
	if(bSuccess)
	{
		m_pDB->m_IndexPreOrderFactory->update(pIndexPreOrder,&wtbIndexPreOrder,&m_Transaction);
		m_Transaction.commit();
	}
	else
	{
		char* errMsg;
		int errorCode;
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		m_pPubMessage->PrepareResponse(pPackage,TID_RspOrderInsert);
		CRspInfoField responseField;				
		responseField.ErrorID = errorCode;
		responseField.ErrorMsg = errMsg;
		thePreOrder.DealFlag = DF_Wait;
		XTP_ADD_FIELD(m_pPubMessage,&thePreOrder);
		XTP_ADD_FIELD(m_pPubMessage,&responseField);
		m_pPubMessage->MakePackage();
		m_pTradeResult->Append(m_pPubMessage->Address(), m_pPubMessage->Length());

		m_Transaction.rollback();
	}
	
	
	return bSuccess;
}

bool CTradeServiceImpl::ReqOrderAction(CWriteableOrderAction *pOrderAction,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//add by jinpc 20160928
	//业务处理

	bool bSuccess = true;   // 撤单操作对于期货和期权品种是一样的,用期货对象进行处理

	if (pOrderAction->SessionID == 0)
	{
		pOrderAction->FrontID = sessionRef.FrontID;
		pOrderAction->SessionID = sessionRef.SessionID;
	}

	bSuccess = m_pHandleFutureOrderAction->HandleReqOrderAction(pOrderAction,sessionRef,pTransaction);
	return bSuccess;
}

bool CTradeServiceImpl::RspOrderInsert(CXTPPackage *pPackage,const TSessionRef &sessionRef)
{
	int time=0;
	GET_ACCURATE_USEC_TIME(time);
	CInputOrderField  inputOrderField;
	CRspInfoField     exRspInfoField;//交易所应答信息
	XTP_GET_SINGLE_FIELD(pPackage,&inputOrderField);
	XTP_GET_SINGLE_FIELD(pPackage,&exRspInfoField);
	
	CPreOrder *pPreOrder   =  m_pDB->m_PreOrderFactory->findByAPIIDAndOrderLocalID(inputOrderField.APIID,inputOrderField.OrderLocalID);
	//如果预委托表中不存在，还有一种可能是重启反演的情况下也会出现，此时需要计算逻辑的
	if(pPreOrder == NULL)  //在预委托表中无法找到
	{
		return false;
	}

	CWriteablePreOrder wtbPreOrder;
	m_pDB->m_PreOrderFactory->retrieve(pPreOrder,&wtbPreOrder);
	wtbPreOrder.InsertTime = inputOrderField.InsertTime;
	wtbPreOrder.TradingDay = inputOrderField.TradingDay;
	wtbPreOrder.OrderSysID = inputOrderField.OrderSysID;
	wtbPreOrder.CoreRecvUp = inputOrderField.CoreRecvUp;
	wtbPreOrder.MinVolume = time;
	
	if (pPackage->GetNoReplayFlag())
	{
		m_pPubMessage->PreparePublish(TID_RspOrderInsert);	
		m_pPubMessage->SetFrontID(pPreOrder->FrontID.getValue());
		m_pPubMessage->SetSessionID(pPreOrder->SessionID.getValue());
		m_pPubMessage->SetRequestID(wtbPreOrder.RequestID.getValue());
		XTP_ADD_FIELD(m_pPubMessage,&wtbPreOrder);
		if (exRspInfoField.ErrorID !=0)
		{
			memset(tmp,0,sizeof(tmp));
			sprintf(tmp,"交易所返回:%s",exRspInfoField.ErrorMsg.getValue());
			exRspInfoField.ErrorMsg = tmp;
		}

		XTP_ADD_FIELD(m_pPubMessage,&exRspInfoField);
		m_pPubMessage->MakePackage();
		m_pTradeResult->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
	}

	GET_ACCURATE_USEC_TIME(time);
	wtbPreOrder.RecNum =time;

    bool bSuccess = true;
	switch (pPreOrder->getIndexPreOrder()->ProductClass.getValue() )
	{
	case PC_Futures:
		{
			m_pHandleOrder = m_pHandleFutureOrder;
			break;
		}
// 	case PC_Options:
// 		{
// 			m_pHandleOrder = m_pHandleOptionOrder;
// 			break;
// 		}
	default:     // 未找到合约类型,直接返回。
		{	
			REPORT_EVENT(LOG_WARNING,"Can not Find Instrument Class ", "In Line %d of File %s.\n",__LINE__,__FILE__);
//					m_pErrorEngine->reportError(ERROR_INSTRUMENT_NOT_FOUND);
			return false;
		}
	}
	bSuccess = m_pHandleOrder->HandleRspOrderInsert(pPreOrder,&wtbPreOrder,&exRspInfoField,&m_Transaction);

	if (bSuccess)
	{
		m_Transaction.commit();
	}
	else
	{
		m_Transaction.rollback();
	}
	return bSuccess;
}

bool CTradeServiceImpl::RspOrderAction(COrderField *pRspOrder,CWriteableOrderAction *pOrderAction,COrderActionField* pActField,CRspInfoField*  pRspInfoField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
    bool bSuccess = true;
	if (pRspInfoField->ErrorID != 0)
	{
		return false;
	}
	COrder* pOrder = m_pDB->m_OrderFactory->findByExchangeIDAndOrderSysID(pActField->ExchangeID,pActField->OrderSysID);
	if(NULL == pOrder || pOrder->getIndexPreOrder() == NULL)  //找不到该笔订单
	{
      REPORT_EVENT(LOG_WARNING,"Can not Find Ref Order ", "In Line %d of File %s.\n",__LINE__,__FILE__);
      m_pErrorEngine->reportError(ERROR_ORDER_SYS_ID_NOT_FOUND);
      return false;
	}

	pActField->InvestorID = pOrder->InvestorID;
	pActField->ClientID = pOrder->ClientID;
	pActField->ParticipantID = pOrder->ParticipantID;
	switch (pOrder->getIndexPreOrder()->ProductClass)
	{
	case PC_Futures:
		{
			m_pHandleOrderAction = m_pHandleFutureOrderAction;
			break;
		}
// 	case PC_Options:
// 		{
// 			m_pHandleOrderAction = m_pHandleOptionOrderAction;
// 			break;
// 		}
	default:     // 未找到合约类型，直接返回。
		{	
			REPORT_EVENT(LOG_WARNING,"Can not Find Instrument Class ", "In Line %d of File %s.\n",__LINE__,__FILE__);
			m_pErrorEngine->reportError(ERROR_INSTRUMENT_NOT_FOUND);
			return false;
		}
	}

	bSuccess = m_pHandleOrderAction->HandleRspOrderAction(pOrderAction,pActField,pRspInfoField,pOrder,sessionRef,pTransaction);
	if (bSuccess && pActField->IsForgeRtn)
	{
		CopyAPIOrderEntity(pRspOrder, pOrder);
		pRspOrder->VolumeRemain =pOrder->VolumeRemain;
		pRspOrder->CancleVolume =pOrder->VolumeRemain;
	}
	return bSuccess;
}

bool CTradeServiceImpl::OnRtnOrder(CXTPPackage *pPackage,const TSessionRef &sessionRef)
{
	bool bSuccess = true;
	COrderField theOrderField;
	XTP_GET_SINGLE_FIELD(pPackage,&theOrderField);


	CNumberType APIID;
	CProductClassType eProductType = getProductClassType(theOrderField.ExchangeID,theOrderField.InstrumentID,APIID);
	switch (eProductType )
	{
	case PC_Futures:
		{
			m_pHandleOrder = m_pHandleFutureOrder;
			break;
		}
// 	case PC_Options:
// 		{
// 			m_pHandleOrder = m_pHandleOptionOrder;
// 			break;
// 		}
	default:     // 未找到合约类型，直接返回。
		{	
			REPORT_EVENT(LOG_WARNING,"Can not Find Instrument Class ", "In Line %d of File %s.\n",__LINE__,__FILE__);
//				m_pErrorEngine->reportError(ERROR_INSTRUMENT_NOT_FOUND);
			return false;
		}
	}

	bSuccess = m_pHandleOrder->HandleRtnOrder(&theOrderField,sessionRef,&m_Transaction,pPackage->GetNoReplayFlag());
	m_pErrorEngine->reportError(0);
	if (bSuccess)
	{
		m_Transaction.commit();
	}
	else
	{
		m_Transaction.rollback();
	}
	return bSuccess;
}

bool CTradeServiceImpl::OnRtnTrade(CXTPPackage *pPackage,const TSessionRef &sessionRef)
{
    bool bSuccess = false;
	CTradeField theTradeField;
	XTP_GET_SINGLE_FIELD(pPackage,&theTradeField);

	COrder *pOrder = m_pDB->m_OrderFactory->findByExchangeIDAndOrderSysID(theTradeField.ExchangeID,theTradeField.OrderSysID);
    if(NULL == pOrder)  //找不到对应报单
	{
	   REPORT_EVENT(LOG_CRITICAL, "Cann't Find Corresponding Order For Trade ","ClientID=[%s], OrderSysID=[%s].\n",theTradeField.ClientID.getValue(),theTradeField.OrderSysID.getValue());   
//	   m_pErrorEngine->reportError(ERROR_ORDER_NOT_FOUND);
	   return false;
	}
   
	CTrade *pTrade  = m_pDB->m_TradeFactory->findByExchangeIDTradeIDOrderSysID(theTradeField.ExchangeID,theTradeField.TradeID,theTradeField.OrderSysID);
    if(NULL != pTrade)   // 重复的成交
	{
	   REPORT_EVENT(LOG_CRITICAL, "Duplicate Trade ","ClientID=[%s], OrderSysID=[%s].\n",theTradeField.ClientID.getValue(),theTradeField.OrderSysID.getValue());   
//	   m_pErrorEngine->reportError(ERROR_DUPLICATE_RTN_TRADE);
	   return false;
	}

	//伪造委托通知,4大期货交易所只伪造部分成交,金交所额外伪造撤单通知
	if (theTradeField.IsForgeRtn && pPackage->GetNoReplayFlag())
	{
		CVolumeType VolumeTraded = pOrder->VolumeTraded + theTradeField.TradeVolume;
		CVolumeType VolumeRemain = pOrder->Volume - VolumeTraded;
		COrderStatusType OrderStatus;
		if (VolumeRemain ==0)
		{
			OrderStatus = OS_AllTraded;
		}
		else
		{
			OrderStatus = OS_PartTradedQueueing;
		}
		if (pOrder->OrderStatus == OS_Canceled)
		{
			OrderStatus = OS_Canceled;
		}

		if(OrderStatus == OS_PartTradedQueueing && VolumeTraded > pOrder->RecNum || 
			theTradeField.ExchangeID == EXID_SGE)
		{
			COrderField theOrderField;
			CopyAPIOrderEntity(&theOrderField,pOrder);
			theOrderField.VolumeTraded = VolumeTraded;
			theOrderField.VolumeRemain = VolumeRemain;
			theOrderField.OrderStatus = OrderStatus;

			m_pPubMessage->PreparePublish(TID_NtfOrder);
			XTP_ADD_FIELD(m_pPubMessage, &theOrderField);
			m_pPubMessage->MakePackage();
			m_pTradeResult->Append(m_pPubMessage->Address(), m_pPubMessage->Length());	
		}
	}


	//发送成交回报
   theTradeField.AccountID         =  pOrder->AccountID;
   theTradeField.BrokerID          =  pOrder->BrokerID;
   theTradeField.UserID			  =  pOrder->UserID;
   theTradeField.InvestorID        =  pOrder->InvestorID;
   theTradeField.UserOrderLocalID  =  pOrder->UserOrderLocalID;
   theTradeField.OrderLocalID      =  pOrder->OrderLocalID;   
   //解决OnRtnTrade中HedgeFlag始终为1的错误  added by liumeng  2014-08-07
   theTradeField.HedgeFlag         =  pOrder->HedgeFlag;
   //解决pats成交没有推送开平标志 added by chengm 2016-01-04
//    theTradeField.OffsetFlag		  =  pOrder->OffsetFlag;
//    theTradeField.Direction		  =  pOrder->Direction;
   if (theTradeField.TradingDay.isNull())
   {
	   theTradeField.TradingDay = getTradingDay(m_pDB);
   }
   
	if (pPackage->GetNoReplayFlag())
	{
	   m_pPubMessage->PreparePublish(TID_NtfTrade);
	   XTP_ADD_FIELD(m_pPubMessage, &theTradeField);
	   m_pPubMessage->MakePackage();
	   m_pTradeResult->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
	}

	
	switch (pOrder->getIndexPreOrder()->ProductClass)
	{
		case PC_Futures:
			{
				m_pHandleTrade = m_pHandleFutureTrade;
				break;
			}
// 		case PC_Options:
// 			{
// 				m_pHandleTrade = m_pHandleOptionTrade;
// 				break;
// 			}
		default:
			{
				REPORT_EVENT(LOG_WARNING,"Can not Find Instrument Class ", "In Line %d of File %s.\n",__LINE__,__FILE__);
				m_pErrorEngine->reportError(ERROR_INSTRUMENT_NOT_FOUND);
				return false;
			}
	}
	bSuccess = m_pHandleTrade->HandleRtnTrade(pOrder,&theTradeField,sessionRef,&m_Transaction);
	m_pErrorEngine->reportError(0);
	if (bSuccess)
	{
		m_Transaction.commit();
	}
	else
	{
		m_Transaction.rollback();
	}
	return bSuccess;
}

void CTradeServiceImpl::DumpDebugInfo(const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	m_pHandleOrder=m_pHandleFutureOrder;
	m_pHandleOrder->DumpDebugInfo();

	CRspInfoField RspInfoFld;//给客户的应答信息
	RspInfoFld.ErrorID = 0;
	RspInfoFld.ErrorMsg = "success to dumped memdb，please quit";
	
	//不管成功失败，都需要发送撤单应答
	m_pPubMessage->PreparePublish(TID_RspError);		 				
	//补充frontid和sessionid,找到发送给谁
	COPY_SESSIONREF_INFO(m_pPubMessage->GetXTPHeader(),&sessionRef);
	XTP_ADD_FIELD(m_pPubMessage,&RspInfoFld);
	m_pPubMessage->MakePackage();
	m_pTradeResult->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
	
}

bool CTradeServiceImpl::NtfInstrumentStatusUpdate(CInstrumentStatusField* pInstrumentStatusField,bool bSendRtn,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
   bool bSuccess = true;
   bSuccess = m_pHandleNotify->HandleInstrumentStatusUpdate(pInstrumentStatusField,bSendRtn,pTransaction);
   return bSuccess;
}

CProductClassType CTradeServiceImpl::getProductClassType(CExchangeIDType ExchangeID,CInstrumentIDType InstrumentID, CNumberType& APIID)
{
   CInstrument* pInstrument = m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(ExchangeID,InstrumentID);
   if(NULL == pInstrument)
   {
	 return PC_Unknown;   
   }
   else
   {
	 APIID = pInstrument->APIID;
     return pInstrument->ProductClass;
   }	
}


/*	QuantDo Platform对交易系统而言，就是客户端，QuantDo Platform需要维护自己的本地报单号。
//	QuantDo Platform可能会配置多个席位，每个席位会保持自己的本地报单号，与其它的席位的本地报单号是独立的。
//	在qdp刚启动的时候，各个席位的本地报单号都从 0 开始。 longqy 20130822
*/
void CTradeServiceImpl::CleanOrderLocalID()
{
	//清0所有席位表中的OrderLocalID字段
	char buf[128];
	int i = 0;
	sprintf(buf,"%012d",i);
	CSeat* pSeat=m_pDB->m_SeatFactory->getFirst();
	while(pSeat!=NULL)
	{
		CWriteableSeat wtbSeat;
		wtbSeat.init();
		m_pDB->m_SeatFactory->retrieve(pSeat,&wtbSeat);
		wtbSeat.OrderLocalID=buf;
		m_pDB->m_SeatFactory->update(pSeat,&wtbSeat,NULL);
		pSeat=m_pDB->m_SeatFactory->getNext();
	}
	m_pDB->m_SeatFactory->endGet();
}

/* 2013-12-24 longqy qdp为支持大边保证金，增加了一个合约组合持仓表。这个合约组合持仓表不从场下上场，
// 而是从客户的持仓表中的数据中从 0 构建。当qdp从场下把数据上场完毕，就可以开始构建这个表中的记录。
*/
//void CTradeServiceImpl::BuildInsGroupPosition(CTransaction *pTransaction)
void CTradeServiceImpl::BuildInsGroupPosition(CExchangeIDType exchangeID)
{
	if (!m_PartGroupPosition.insert(exchangeID.getValue()).second)
	{
		return;
	}
	CInvestorPositionFactory *pPositionFactory = m_pDB->m_InvestorPositionFactory;
	CInvestorPosition* pInvestorPosition=NULL;
	CInvestorAccount *pInvestorAccount=NULL;
	CWriteableInvestorAccount wtbAccount;
	CWriteableInvestorPositionLimit wtbLimit;
	m_PosiMap.clear();
	CPosiMap::iterator posi_iter;
	TPosi posi;
	for (pInvestorPosition = pPositionFactory->getFirst();pInvestorPosition != NULL;pInvestorPosition = pPositionFactory->getNext())	
	{
		//如果交易所对不上，不需要计算
		if(pInvestorPosition->ExchangeID != exchangeID ||
		   pInvestorPosition->Position == 0)
		{
			continue;
		}

		//获取品种限额
		CInstrument *pInstrument = m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pInvestorPosition->ExchangeID,pInvestorPosition->InstrumentID);
		if (pInstrument == NULL)
		{
			REPORT_EVENT(LOG_CRITICAL,"BuildInsGroupPosition","can not find instrument:%s,exchangeid:%s",\
				pInvestorPosition->InstrumentID.getValue(),pInvestorPosition->ExchangeID.getValue());
			continue;
		}
		CInvestorPositionLimit *pLimit = m_pDB->m_InvestorPositionLimitFactory->findByBrkIDVstIDExIDIstID(pInvestorPosition->BrokerID,\
			pInvestorPosition->InvestorID,pInvestorPosition->ExchangeID,pInstrument->ProductID.getValue());
		if (pLimit != NULL)
		{
			wtbLimit.init();
			m_pDB->m_InvestorPositionLimitFactory->retrieve(pLimit,&wtbLimit);
			if (pInvestorPosition->Direction == D_Buy)
			{
				wtbLimit.LongPosition += pInvestorPosition->YdPosition;
			}
			else if (pInvestorPosition->Direction == D_Sell)
			{
				wtbLimit.ShortPosition += pInvestorPosition->YdPosition;
			}
			else
			{
				if (pInvestorPosition->Position >0)
				{
					wtbLimit.LongPosition += pInvestorPosition->YdPosition;
				}
				else
				{
					wtbLimit.ShortPosition -= pInvestorPosition->YdPosition;
				}
			}
			m_pDB->m_InvestorPositionLimitFactory->update(pLimit,&wtbLimit);
		}

		pInvestorAccount = m_pDB->m_InvestorAccountFactory->findByBrokerIDInvestorID(pInvestorPosition->BrokerID,pInvestorPosition->InvestorID);
		if (pInvestorAccount == NULL)
		{
			REPORT_EVENT(LOG_CRITICAL,"BuildInsGroupPosition","can not find account,but have positions brokerid:%s,investorid:%s",\
				pInvestorPosition->BrokerID.getValue(),pInvestorPosition->InvestorID.getValue());
			continue;
		}
		m_pDB->m_InvestorAccountFactory->retrieve(pInvestorAccount,&wtbAccount);
		if (pInvestorPosition->Direction == D_Net)
		{
			wtbAccount.Margin += pInvestorPosition->UsedMargin;
		}
		else
		{
			//综合持仓按大边保证金计算
			memset(&posi,0,sizeof(TPosi));
			posi.BrokerID = pInvestorPosition->BrokerID;
			posi.InvestorID = pInvestorPosition->InvestorID;
			posi.ExchangeID = pInvestorPosition->ExchangeID;
			posi.InstrumentID = pInvestorPosition->InstrumentID;
			posi.HedgeFlag = pInvestorPosition->HedgeFlag;
			posi.Direction = pInvestorPosition->Direction==D_Buy ? D_Sell : D_Buy;
			posi_iter = m_PosiMap.find(posi);
			if (posi_iter == m_PosiMap.end())
			{
				posi.Direction=pInvestorPosition->Direction;
				m_PosiMap.insert(CPosiMap::value_type(posi,pInvestorPosition->UsedMargin));
				wtbAccount.Margin += pInvestorPosition->UsedMargin;
			}
			else 
			{
				if (pInvestorPosition->UsedMargin > posi_iter->second)
				{
					wtbAccount.Margin += (pInvestorPosition->UsedMargin - posi_iter->second);
					m_PosiMap.erase(posi_iter);
				}
				else
				{
					m_PosiMap.erase(posi_iter);
					continue;
				}
			}
		}
		baseAlgorithms.ChangeBalanceAndAvailable(&wtbAccount);
		m_pDB->m_InvestorAccountFactory->update(pInvestorAccount,&wtbAccount);
	}
	pPositionFactory->endGet();
}

bool CTradeServiceImpl::UpdateSystemStatus(CSystemStatusField *pSystemStatusField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	CWriteableSystemStatus SystemStatus;
	SystemStatus.SystemStatus = pSystemStatusField->SystemStatus;

	CSystemStatus* pSystemStatus=m_pDB->m_SystemStatusFactory->getFirst();
	m_pDB->m_SystemStatusFactory->endGet();
	if (pSystemStatus==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"UpdateSystemStatus","error:no UpdateSystemStatus");
	}
	else
	{
		SystemStatus.TradingDay = pSystemStatus->TradingDay;
		m_pDB->m_SystemStatusFactory->addOrUpdate(pSystemStatus,&SystemStatus,pTransaction);	
	}
	return true;
}

bool CTradeServiceImpl::DelUserSession(CUserField *pUserField,CTransaction *pTransaction)
{
	CUser *pUser = m_pDB->m_UserFactory->findByBrokerIDUserID(pUserField->BrokerID,pUserField->UserID);
	if (pUser == NULL)
	{
		m_pErrorEngine->reportError(ERROR_USER_NOT_FOUND);
		return false;
	}
	CUserSession *pUserSession = m_pDB->m_UserSessionFactory->startFindByUserID(pUserField->UserID);
	for(;NULL!=pUserSession;pUserSession=m_pDB->m_UserSessionFactory->findNextByUserID())
	{
		ForceUserLogout(pUserSession,pTransaction);
	}
	m_pDB->m_UserSessionFactory->endFindByUserID();

	CMaxLocalID *pMaxLocalID = m_pDB->m_MaxLocalIDFactory->getFirst();
	while (	pMaxLocalID!=NULL)
	{
		if (pMaxLocalID->UserID == pUserField->UserID)
		{
			m_pDB->m_MaxLocalIDFactory->remove(pMaxLocalID);
		}
		pMaxLocalID=m_pDB->m_MaxLocalIDFactory->getNext();
	}
	m_pDB->m_MaxLocalIDFactory->endGet();
	pTransaction->commit();
	return true;
}

bool CTradeServiceImpl::ForceUserLogout(CUserSession *pUserSession, CTransaction *pTransaction)
{

	if (pUserSession == NULL)
	{
		m_pErrorEngine->reportError(ERROR_USER_NOT_LOGIN);
		return false;
	}
	
	//多唯一索引，不能修改，只能删除
	m_pDB->m_UserSessionFactory->remove(pUserSession, pTransaction);
	
	return true;
}

bool CTradeServiceImpl::UserUpdate(CUserField *pUserField, CTransaction *pTransaction){

	CWriteableUser wuser;
	CUser *user=m_pDB->m_UserFactory->findByBrokerIDUserID(pUserField->BrokerID,pUserField->UserID);
 	if (NULL == user)
 	{
 		m_pErrorEngine->reportError(ERROR_USER_NOT_FOUND);
		return false;
 	}
 	//更新user表
 	m_pDB->m_UserFactory->retrieve(user,&wuser);
	CopyUserEntity(&wuser,pUserField);
 	m_pDB->m_UserFactory->update(user,&wuser,pTransaction);

	pTransaction->commit();

	return true;
}

bool CTradeServiceImpl::NtfSGEDeferRate(CSGEDeferRateField *pSGEDeferRateField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	CSGEDeferRate* pSGEDeferRate = m_pDB->m_SGEDeferRateFactory->findByTradeDateInstrumentIDIndex(pSGEDeferRateField->TradeDate,
		pSGEDeferRateField->InstrumentID);
	
	CWriteableSGEDeferRate wtbSGEDeferRate;
	if (NULL == pSGEDeferRate)
	{
		memset(&wtbSGEDeferRate,0,sizeof(CWriteableSGEDeferRate));
		CopySGEDeferRateEntity(&wtbSGEDeferRate,pSGEDeferRateField);
		m_pDB->m_SGEDeferRateFactory->add(&wtbSGEDeferRate, pTransaction);
	}
	else
	{
		m_pDB->m_SGEDeferRateFactory->retrieve(pSGEDeferRate, &wtbSGEDeferRate);
		wtbSGEDeferRate.DeferRate = pSGEDeferRateField->DeferRate;
		wtbSGEDeferRate.Direction = pSGEDeferRateField->Direction;
		m_pDB->m_SGEDeferRateFactory->update(pSGEDeferRate, &wtbSGEDeferRate, pTransaction);
	}
	
	return true;
}

//设置郑商所组合合约tick值和涨跌停价
bool CTradeServiceImpl::ReqCZCECombMarketData()
{
	if (atoi(m_pConfig->getConfig("OpenCZCECmb")) ==1)
	{
		CExchangeIDType ExchangeID = EXID_CZCE;
		CInstrument *pLegA=NULL;
		CInstrument *pLegB=NULL;
		CMarketData *pMarketA=NULL;
		CMarketData *pMarketB=NULL;
		CCmbInstrumentDetail *pDetail=NULL;
		CWriteableInstrument theInstrument;
		CInstrument *pInstrumentCmb = m_pDB->m_InstrumentFactory->getFirst();
		while(pInstrumentCmb != NULL)
		{
			if (pInstrumentCmb->ExchangeID == ExchangeID && pInstrumentCmb->ProductClass == PC_Combination)
			{
				CCmbInstrumentDetailIterator *pSingelIter=new CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID(
					m_pDB->m_CmbInstrumentDetailFactory,ExchangeID,pInstrumentCmb->InstrumentID);
				while(pDetail=pSingelIter->next())
				{
					if(pDetail->LegNo==1)
					{
						pLegA = m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(ExchangeID,pDetail->SingleInstrumentID);
						pMarketA = m_pDB->m_MarketDataFactory->findByExchangeIDAndInstrumentID(ExchangeID,pDetail->SingleInstrumentID);
					}
					else
					{
						pLegB = m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(ExchangeID,pDetail->SingleInstrumentID);
						pMarketB = m_pDB->m_MarketDataFactory->findByExchangeIDAndInstrumentID(ExchangeID,pDetail->SingleInstrumentID);
					}
				}
				
				theInstrument.init();
				m_pDB->m_InstrumentFactory->retrieve(pInstrumentCmb,&theInstrument);
				if (pLegA && pLegB)
				{			
					theInstrument.PriceTick = MAX(pLegA->PriceTick.getValue(),pLegB->PriceTick.getValue());
				}
				if (pMarketA && pMarketB)
				{
					theInstrument.UpperLimitPrice = pMarketA->UpperLimitPrice - pMarketB->LowerLimitPrice;
					theInstrument.LowerLimitPrice = pMarketA->LowerLimitPrice - pMarketB->UpperLimitPrice;
				}
				m_pDB->m_InstrumentFactory->update(pInstrumentCmb,&theInstrument);
			}
			pInstrumentCmb = m_pDB->m_InstrumentFactory->getNext();
		}
		m_pDB->m_InstrumentFactory->endGet();
	}
	
	m_pHandleNotify->CZCEInstrumentStatusUpdate();
	
	return true;
}

//获取系统交易日
CTradingDayType CTradeServiceImpl::GetTradingDay()
{
	return getTradingDay(m_pDB);
}


/*
分价查询请求
*/
bool CTradeServiceImpl::ReqMBLMarketData(CQryMBLMarketDataField &pMBLMarketData,const TSessionRef &sessionRef)
{
	CRspInfoField		 RspInfoField;
	bool bSuccess		 = true;
	CInvestor* pInvestor = NULL;
	CNumberType ApiID	 = -1;
	
	//获取apiid
	CBaseExchApi *pBaseExchApi = g_pExchangeLinkManager->GetAPIIDByExchangIDUserID(pMBLMarketData.ExchangeID,pMBLMarketData.LogUserID);
	if(pBaseExchApi == NULL || !pBaseExchApi->GetStatus())
	{
		m_pErrorEngine->reportError(ERROR_CURRENT_SEAT_NOT_AVAILABLE);
		REPORT_EVENT(LOG_WARNING,"ReqMBLMarketData","Trader Serser  ApiID=%d",ApiID.getValue());
		bSuccess = false;
	}else{
		bSuccess = pBaseExchApi->ReqQryMBLMarketData(pMBLMarketData,sessionRef);
	}
	
	if ( !bSuccess )
	{
		RspInfoField.ErrorID	=	ERROR_ERROR;
		RspInfoField.ErrorMsg	=	"分价查询请求错误，请重新查询";
		m_pPubMessage->PreparePublish(TID_RspQryMBLMarketData);
		COPY_SESSIONREF_INFO(m_pPubMessage->GetXTPHeader(),&sessionRef);
		XTP_ADD_FIELD(m_pPubMessage,&RspInfoField);	
		m_pPubMessage->MakePackage();
		m_pTradeResult->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
		m_pErrorEngine->reportError(ERROR_DUPLICATE_SESSION);
		REPORT_EVENT(LOG_WARNING,"ReqMBLMarketData","Req is error ");
	}
	return bSuccess;
	
}

bool CTradeServiceImpl::ReqNtfTimeSync(CXTPPackage *pPackage,const TSessionRef &sessionRef)
{
	CCurrentTimeField timeField;
	memset(&timeField,0,sizeof(CCurrentTimeField));
	XTP_GET_SINGLE_FIELD(pPackage,&timeField);
	return true;
}

bool CTradeServiceImpl::ReqNtfPositionProfit(CXTPPackage *pPackage,const TSessionRef &sessionRef)
{
	CPositionProfitField field;
	CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
	while(!it.IsEnd())
	{
		it.Retrieve(&field);
		CInvestorAccount *pAccount = m_pDB->m_InvestorAccountFactory->findByBrokerIDInvestorID(field.BrokerID,field.InvestorID);
		if (pAccount != NULL)
		{
			CWriteableInvestorAccount wtbAccount;
			m_pDB->m_InvestorAccountFactory->retrieve(pAccount,&wtbAccount);
			wtbAccount.PositionProfit = field.PositionProfit;
			CFutureMoneyPosition::ChangeBalanceAndAvailable(&wtbAccount);
			m_pDB->m_InvestorAccountFactory->update(pAccount,&wtbAccount,&m_Transaction);
		}
		
		it.Next();
	}
	m_Transaction.commit();
	return true;
}

