/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file COrderInsertRules.h
///@brief实现了类COrderInsertRules
///@history 
///20060113	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "HandleOrder.h"
#include "tradingTools.h"
#include "BaseExchApi.h"
#include "ExchangeLinkManager.h"
#include "system.h"
#include "printinfo.h"

extern CBaseExchApi *g_pExchApiArryMap[];//各交易所APImap
extern CExchangeLinkManager* g_pExchangeLinkManager;
extern bool    g_bLatencyOut;
extern bool g_bIsMultiSeat;
extern bool g_bIsQquery;
extern char g_QDPVersion;
CHandleOrder::CHandleOrder(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult)
:CRuleHandleBase(pDB,pErrorEngine,pConfig,pTradeResult)
{
	m_pPubMessage   = new CXTPPackage();
	m_pPubMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE, XTPHLEN);
	m_pBaseCheck = new CBaseCheck(pDB,pErrorEngine);

	m_CZCEForQuoteInterval = atoi(m_pConfig->getConfig("CZCEForQuoteSeconds"));
}

CHandleOrder::~CHandleOrder()
{
}

bool CHandleOrder::HandleLocalOrderInsertFailed(CInputOrderField *pOrderField)
{
	CWriteableOrderInsertFailed theWriteableOrderInsertFailed ;
	theWriteableOrderInsertFailed.init();
	CopyOrderEntity(&theWriteableOrderInsertFailed,pOrderField);
    char* errMsg;
	int errorCode;
	m_pErrorEngine->getLastErrorWithoutClear(&errorCode,&errMsg);
	theWriteableOrderInsertFailed.ErrorMsg = errMsg;
	
	//此处不需要事务，直接插入内存表
	m_pDB->m_OrderInsertFailedFactory->add(&theWriteableOrderInsertFailed,NULL);
	return true;
}


bool CHandleOrder::HandleLocalOrderInsertFailed(CWriteablePreOrder *pPreOrder)
{
    CWriteableOrderInsertFailed theWriteableOrderInsertFailed ;
	theWriteableOrderInsertFailed.init();
	CopyOrderEntity(&theWriteableOrderInsertFailed,pPreOrder);
	char* errMsg;
	int errorCode;
    m_pErrorEngine->getLastErrorWithoutClear(&errorCode,&errMsg);
	theWriteableOrderInsertFailed.ErrorMsg = errMsg;

	//将微妙级精确时间插入到UserCustom字段，作为错单表的主键之一 liumeng 20140820
	long nCurrentTime =0;
 	GET_ACCURATE_USEC_TIME(nCurrentTime);
	theWriteableOrderInsertFailed.UserCustom = nCurrentTime;
			
	//此处不需要事务，直接插入内存表
	m_pDB->m_OrderInsertFailedFactory->add(&theWriteableOrderInsertFailed,NULL); 
	return true;
}


bool CHandleOrder::HandleOrderInsert(CWriteableIndexPreOrder *pIndexPreOrder,CWriteablePreOrder *pPreOrder,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	bool bSuccess = false;
	//20160817 huwp 从之前委托成功过的定单信息留痕里获得各类指针
	pPreOrder->APIID = 0;
	if (likely(!g_bIsMultiSeat))
	{
		pPreOrder->APIID = pIndexPreOrder->APIID;
	}
	else if (unlikely(!pPreOrder->BranchID.isNull()))
	{
		pPreOrder->APIID = atoi(pPreOrder->BranchID.getValue());
	}

	//投资者权限检查
	bSuccess = m_pBaseCheck->RightCheck(pPreOrder,pTransaction);
	if (unlikely(!bSuccess))
	{
		return false;
	}

	pPreOrder->FrozenFee=0.0;
	pPreOrder->FrozenMargin=0.0;
	//资金规则计算
	CMoneyField   theMoneyField;
	memset(&theMoneyField, 0, sizeof(theMoneyField));
	bSuccess  = m_pMoneyPosition->OrderInsertMoneyFrozen(pPreOrder,pIndexPreOrder,&theMoneyField,pTransaction);
   	if(bSuccess == false)  
	{
		//REPORT_EVENT(LOG_CRITICAL,"HandleOrderInsert","frozen margin error investorid:%s instrumentid:%s\n",pPreOrder->InvestorID.getValue(),pPreOrder->InstrumentID.getValue());
		return false;
	}
	pPreOrder->FrozenFee=theMoneyField.Fee;
	pPreOrder->FrozenMargin=theMoneyField.FrozenMarginChanged;
	pPreOrder->VolumeRemain = pPreOrder->Volume;
	pPreOrder->VolumeTraded = 0;
	
	//持仓限额计算
	bSuccess = m_pMoneyPosition->OrderInsertPositionFrozen(pPreOrder,pIndexPreOrder,&theMoneyField,pTransaction);
	if (!bSuccess)
	{
		//REPORT_EVENT(LOG_CRITICAL,"HandleOrderInsert","frozen position error investorid:%s instrumentid:%s\n",pPreOrder->InvestorID.getValue(),pPreOrder->InstrumentID.getValue());
		return false;
	}


	//通道检查
	CBaseExchApi *pBaseExchApi = NULL;
	if (likely(pPreOrder->APIID > 0))
	{
		pBaseExchApi = g_pExchangeLinkManager->getExchangeLink(pPreOrder->APIID);
	}
	else
	{
		pBaseExchApi = g_pExchangeLinkManager->getExchangeLink(pPreOrder->ExchangeID,pPreOrder->ParticipantID);
	}
	
	if(unlikely(pBaseExchApi == NULL || !pBaseExchApi->GetStatus()))
	{		
		m_pErrorEngine->reportError(ERROR_CURRENT_SEAT_NOT_AVAILABLE);
		return false;
	}
	
	
	int ret = pBaseExchApi->ReqOrderInsert(*pPreOrder);
	if (likely(ret ==0))
	{
		pIndexPreOrder->APIID = pPreOrder->APIID;
		pIndexPreOrder->UserID = pPreOrder->UserID;
		bSuccess = true;
		m_pDB->m_PreOrderFactory->add(pPreOrder,pTransaction);
		//更新MaxLocalID
		CWriteableMaxLocalID theMaxLocalID;
		m_pDB->m_MaxLocalIDFactory->retrieve(pPreOrder->getIndexPreOrder()->getMaxLocalID(),&theMaxLocalID);
		theMaxLocalID.MaxOrderLocalID=pPreOrder->UserOrderLocalID;
		m_pDB->m_MaxLocalIDFactory->update(pPreOrder->getIndexPreOrder()->getMaxLocalID(),&theMaxLocalID,pTransaction);
		//更新InvestorAccount
		CWriteableInvestorAccount theWriteableInvestorAccount ;
		m_pDB->m_InvestorAccountFactory->retrieve(pIndexPreOrder->getInvestorAccount(),&theWriteableInvestorAccount);			
		//更新实时资金表
		theWriteableInvestorAccount.FrozenFee  = theWriteableInvestorAccount.FrozenFee + theMoneyField.Fee;			
		theWriteableInvestorAccount.FrozenMargin += theMoneyField.FrozenMarginChanged;			
		//更新结算准备金和和可用资金
		CFutureMoneyPosition::ChangeBalanceAndAvailable(&theWriteableInvestorAccount);
		m_pDB->m_InvestorAccountFactory->update(pIndexPreOrder->getInvestorAccount(),&theWriteableInvestorAccount,pTransaction);
	}
	else if (ret == -2)
	{
		m_pErrorEngine->reportError(ERROR_FLOWCONTROL_TOOLARGE_UNFINISHED_ORDERS);
		bSuccess = false;
	}
	else if (ret == -3)
	{
		m_pErrorEngine->reportError(ERROR_FLOWCONTROL_TOOQUICK_ORDERSPEED_FORORDER);
		bSuccess = false;
	}
	else
	{
		m_pErrorEngine->reportError(ERROR_NO_AVAIL_EXCHANGE_SEAT);
		bSuccess = false;
	}
    return bSuccess;
}

bool CHandleOrder::HandleRspOrderInsert(CPreOrder *PreOrder,CWriteablePreOrder *wtbPreOrder,CRspInfoField*  pRspInfoField,CTransaction *pTransaction)
{
	bool bSuccess = false;
	CInstrument*      pInstrument = NULL;
	CInvestorAccount* pInvestorAccount = NULL;
	
	if(0 == pRspInfoField->ErrorID )   // 交易所返回成功报单，已报入。
	{		
		COrder* pOrder = m_pDB->m_OrderFactory->findByExchangeIDAndOrderSysID(wtbPreOrder->ExchangeID,wtbPreOrder->OrderSysID);
		if(NULL == pOrder)  //对于委托表记录为空，将预委托表拷贝至委托表
		{
			CWriteableOrder theWriteableOrder ;
			PrepareWritableOrder(&theWriteableOrder,wtbPreOrder);
			theWriteableOrder.OrderStatus='\0';
			theWriteableOrder.RecNum=0;
			if (g_bLatencyOut)
			{
				AddOrderDelay(wtbPreOrder);
			}
			if( m_pDB->m_OrderFactory->add(&theWriteableOrder,pTransaction) != NULL)
			{		
				m_pDB->m_PreOrderFactory->remove(PreOrder,pTransaction);
			}
			else
			{
				//严重错误，插入订单表失败
				REPORT_EVENT(LOG_CRITICAL,"HandleRtnOrder ERR,OrderSysID=[%s]\n",wtbPreOrder->OrderSysID.getValue());
				return false;
			}
		}
		else    //委托表记录已经存在，直接删除预委托表
		{  
			m_pPubMessage->PreparePublish(TID_NtfOrder);
			XTP_ADD_FIELD(m_pPubMessage, pOrder);
			m_pPubMessage->MakePackage();
			m_pTradeResult->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
			m_pDB->m_PreOrderFactory->remove(PreOrder,NULL);
		}
		return true;  
	}
	else     //错单 -  并且由交易所返回撤单消息  预委托表存在
	{	
		//解冻资金
		if (!m_pMoneyPosition->MoneyUnFrozen(PreOrder,pTransaction))
		{
			REPORT_EVENT(LOG_CRITICAL,"MoneyUnFrozen","unfrozen position error in order cancel");
			return false;
		}
		

		//解冻持仓
		if (!m_pMoneyPosition->PositionUnFrozen(PreOrder,pTransaction))
		{
			REPORT_EVENT(LOG_CRITICAL,"PositionUnFrozen","unfrozen position error in order cancel");
			return false;
		}
		if (g_bLatencyOut)
		{
			AddOrderDelay(wtbPreOrder);
		}

		m_pDB->m_PreOrderFactory->remove(PreOrder,pTransaction);
	}
	
	return true;
}

bool CHandleOrder::HandleRtnOrder(COrderField *pOrderField,const TSessionRef &sessionRef,CTransaction *pTransaction,bool bSendRtn)
{
	bool bSuccess = false;
	CPreOrder*           pPreOrder    = NULL;
	COrder*              pOrder       = NULL;
	CInstrument*         pInstrument = NULL;
	CInvestorAccount*    pInvestorAccount = NULL;
	CInvestorPosition*     pInvestorPosition  = NULL;
	if (pOrderField->TradingDay.isNull())
	{
		pOrderField->TradingDay=getTradingDay(m_pDB);
	}	
	if(pOrderField->OrderStatus == OS_Canceled)   // 如果状态为已撤单
	{
		bSuccess = HandleRtnOrderCancel(pOrderField,sessionRef,pTransaction,bSendRtn);
	}
    else   // 如果状态为订单提交、订单成交
	{
		pOrder =   m_pDB->m_OrderFactory->findByExchangeIDAndOrderSysID(pOrderField->ExchangeID,pOrderField->OrderSysID);
		if(NULL != pOrder  )    //如果在委托表中不存在
		{
			//如果此次没有发生任何撤单增加和成交增加，说明是重复回来的情况
// 			if(pOrder->ExchangeID == EXID_SGE && pOrder->OrderStatus !='\0' &&
// 				(pOrderField->VolumeTraded <= pOrder->RecNum || pOrder->OrderStatus == OS_Canceled) )
// 			{
// 				REPORT_EVENT(LOG_CRITICAL, "Duplicate rtnOrder","In Line %d of File %s.\n",__LINE__,__FILE__);
// 				m_pErrorEngine->reportError(ERROR_DUPLICATE_RTN_ORDER);
// 				return false;
// 			}
			CopyFieldOrderFromOrder(pOrderField,pOrder);
			SendOrderField(pOrderField,bSendRtn);
			// 更新委托表状态
			CWriteableOrder   theWriteableOrder ;
			theWriteableOrder.init();
			m_pDB->m_OrderFactory->retrieve(pOrder,&theWriteableOrder);
			
			///longqy 2013-12-13 先到的撤单回报错误撤单，之前的部分成交回报来后，会引起错误
			// 只有状态不是撤单状态，才能改变为其它的新状态
			if (OS_Canceled != theWriteableOrder.OrderStatus)
			{	// 如果报单状态已经是撤单状态，这是最后状态，不能够再改为其它的状态
				theWriteableOrder.OrderStatus = pOrderField->OrderStatus;
			}
			if (pOrder->TradingDay.isNull())
			{
				theWriteableOrder.TradingDay = pOrderField->TradingDay;
			}
			theWriteableOrder.InsertTime = pOrderField->InsertTime;
			theWriteableOrder.RecNum = pOrderField->VolumeTraded;
			m_pDB->m_OrderFactory->update(pOrder,&theWriteableOrder,pTransaction);
			return true; 
		}
		else
		{
			pPreOrder   =  m_pDB->m_PreOrderFactory->findByAPIIDAndOrderLocalID(pOrderField->APIID,pOrderField->OrderLocalID);
			if(pPreOrder!=NULL)   //如果在预委托表中存在
			{
				//补充信息给前置
				CopyFieldOrderFromPreOrder(pOrderField,pPreOrder);
				SendOrderField(pOrderField,bSendRtn);
				//插入委托表
				CWriteableOrder theWriteableOrder;
				PrepareWritableOrder(&theWriteableOrder,pPreOrder,pOrderField);
				theWriteableOrder.RecNum = pOrderField->VolumeTraded;
				theWriteableOrder.TradingDay = pOrderField->TradingDay;
				if (m_pDB->m_OrderFactory->add(&theWriteableOrder,pTransaction)!=NULL)
				{
					m_pDB->m_PreOrderFactory->remove(pPreOrder,pTransaction);
				}
				else
				{
					REPORT_EVENT(LOG_CRITICAL,"HandleRtnOrder ERR,OrderSysID=[%s]\n",pOrderField->OrderSysID.getValue());
					return false;
				}
				return true;
			}
			else
			{
				// 来自私有流其他席位的报单回报或反演，进行资金持仓冻结处理。
				bSuccess = RtnOrderFromRecoveryOrPrivateFlow(&pOrderField,pTransaction);
				SendOrderField(pOrderField,bSendRtn);
				return bSuccess;  
			}
		}
	}	
    return true;
}

//处理状态为已撤单的情况
bool CHandleOrder::HandleRtnOrderCancel(COrderField *pOrderField,const TSessionRef &sessionRef,CTransaction *pTransaction,bool bSendRtn)
{ 
	//找委托表是否存在
	COrder *pOrder=m_pDB->m_OrderFactory->findByExchangeIDAndOrderSysID(pOrderField->ExchangeID,pOrderField->OrderSysID);
	if (pOrder != NULL)
	{
		//如果报单已经撤单了，说明是重复回来的情况
// 		if(pOrder->ExchangeID == EXID_SGE && pOrder->OrderStatus == OS_Canceled && pOrder->VolumeRemain == pOrder->CancleVolume)
// 		{
// 			REPORT_EVENT(LOG_CRITICAL, "Duplicate rtnOrder","In Line %d of File %s.\n",__LINE__,__FILE__);
// 			m_pErrorEngine->reportError(ERROR_DUPLICATE_RTN_ORDER);
// 			return false;
// 		}
		// 报单回报中不修改字段 VolumeTraded，放到成交回报中修改 2014-03-19 longqy
		// 处理全撤单时，内存数据库中的VolumeTraded\VolumeRemain为0\0的情况 2014-08-01 liumeng
		CWriteableOrder   theWriteableOrder ;
		theWriteableOrder.init();
		m_pDB->m_OrderFactory->retrieve(pOrder,&theWriteableOrder);
		pOrderField->VolumeRemain = pOrder->Volume - pOrderField->VolumeTraded;
		theWriteableOrder.CancleVolume = pOrderField->VolumeRemain;
		theWriteableOrder.RecNum = pOrderField->VolumeTraded;
		// 2015-02-05 longqy 撤单时间补充
		theWriteableOrder.CancelTime = pOrderField->CancelTime;
		m_pDB->m_OrderFactory->update(pOrder,&theWriteableOrder,pTransaction);
		
		if (pOrder->TradingDay.isNull())
		{
			theWriteableOrder.TradingDay    = pOrderField->TradingDay;
		}
		pOrderField->UserID           = pOrder->UserID;
		pOrderField->UserCustom       = pOrder->UserCustom;
		pOrderField->UserOrderLocalID = pOrder->UserOrderLocalID;	
		pOrderField->OrderSysID       = pOrder->OrderSysID;
		
		//解决OnRtnOrder中HedgeFlag始终为1的错误  added by liumeng  2014-10-28
		pOrderField->HedgeFlag       = pOrder->HedgeFlag;
		//解决有些交易所撤单通知没有开平标志字段
		pOrderField->OffsetFlag		 = pOrder->OffsetFlag;
		//补充私有流前置信息 chengm 20151220
		pOrderField->UserID			 = pOrder->UserID;
		pOrderField->InvestorID		 = pOrder->InvestorID;
		pOrderField->FrontID		 = pOrder->FrontID;
		pOrderField->SessionID		 = pOrder->SessionID;
		SendOrderField(pOrderField,bSendRtn);
		return true;
	}
	else
	{
		//2.找预委托表是否存在
		CPreOrder *pPreOrder =  m_pDB->m_PreOrderFactory->findByAPIIDAndOrderLocalID(pOrderField->APIID,pOrderField->OrderLocalID);
		if (pPreOrder != NULL)
		{
			pOrderField->UserID           =  pPreOrder->UserID;
			pOrderField->UserCustom       =  pPreOrder->UserCustom;
			pOrderField->UserOrderLocalID =  pPreOrder->UserOrderLocalID;
			pOrderField->InvestorID		  =  pPreOrder->InvestorID;
			//解决OnRtnOrder中HedgeFlag始终为1的错误  added by liumeng  2014-10-28
			pOrderField->HedgeFlag       = pPreOrder->HedgeFlag;
			pOrderField->FrontID		 = pPreOrder->FrontID;
			pOrderField->SessionID		 = pPreOrder->SessionID;
			SendOrderField(pOrderField,bSendRtn);

			CWriteableOrder   theWriteableOrder ;
			PrepareWritableOrder(&theWriteableOrder,pPreOrder,pOrderField);
			//订单的状态不能改为已撤单，按照设计，由RspOrderAction统一处理
			theWriteableOrder.OrderStatus  = OS_NoTradeNotQueueing;
			theWriteableOrder.TradingDay = pOrderField->TradingDay;
			// 2015-02-05 longqy 撤单时间补充
			theWriteableOrder.CancelTime = pOrderField->CancelTime;
			if( m_pDB->m_OrderFactory->add(&theWriteableOrder,pTransaction) != NULL)
			{
				m_pDB->m_PreOrderFactory->remove(pPreOrder,pTransaction);
			}
		}
		else
		{
			if (pOrderField->TimeCondition==TC_IOC)
			{
				pOrderField->OrderStatus = OS_NoTradeQueueing;
				pOrderField->CancleVolume = pOrderField->Volume - pOrderField->VolumeTraded;
				RtnOrderFromRecoveryOrPrivateFlow(&pOrderField,pTransaction);
				pOrderField->OrderStatus = OS_Canceled;
				SendOrderField(pOrderField,bSendRtn);
				return true;
			}

			//获取InvestorID
			CClientTradingID *pClientTradingID =  m_pDB->m_ClientTradingIDFactory->findByBrokerIDExchangeIDPartClientID(pOrderField->BrokerID,\
				pOrderField->ExchangeID,pOrderField->ParticipantID,pOrderField->ClientID);
			if( pClientTradingID == NULL)
			{
				REPORT_EVENT(LOG_CRITICAL, "Order From Other Seat Cann't Find InvestorID ","ClientID:%s, OrderSysID:%s In Line %d of File %s.\n",\
					pOrderField->ClientID.getValue(),pOrderField->OrderSysID.getValue(),__LINE__,__FILE__);
				return false;
			}
			pOrderField->AccountID=pClientTradingID->AccountID;
			pOrderField->InvestorID=pClientTradingID->InvestorID;
			SendOrderField(pOrderField,bSendRtn);
			CWriteableOrder   theWriteableOrder ;
			theWriteableOrder.init();
			PrepareWritableOrder(&theWriteableOrder,pOrderField);
			theWriteableOrder.VolumeRemain = pOrderField->Volume;
			theWriteableOrder.VolumeTraded = 0;
			theWriteableOrder.RecNum = pOrderField->VolumeTraded;
			m_pDB->m_OrderFactory->add(&theWriteableOrder,pTransaction);
		}
	}

	return true;
}


bool CHandleOrder::RtnOrderFromRecoveryOrPrivateFlow(COrderField** ppOrderField,CTransaction *pTransaction)
{
    bool bSuccess = true;
	CWriteableOrder   theWriteableOrder ;
	CMoneyField       theMoneyField;

	CWriteablePreOrder thePreOrder;
	thePreOrder.init();
	CopyOrderEntity(&thePreOrder,*ppOrderField);
	thePreOrder.SessionID =0;

		
	//首先要把订单信息补全
	CClientTradingID *pClientTradingID =  m_pDB->m_ClientTradingIDFactory->findByBrokerIDExchangeIDPartClientID(thePreOrder.BrokerID,\
		thePreOrder.ExchangeID,thePreOrder.ParticipantID,thePreOrder.ClientID);
    if( pClientTradingID == NULL)
	{
		REPORT_EVENT(LOG_CRITICAL, "Order From Other Seat Cann't Find InvestorID ","ClientID:%s, OrderSysID:%s In Line %d of File %s.\n",\
			thePreOrder.ClientID.getValue(),thePreOrder.OrderSysID.getValue(),__LINE__,__FILE__);
		return false;
	}	
	thePreOrder.InvestorID = pClientTradingID->InvestorID;
	thePreOrder.BrokerID   = pClientTradingID->BrokerID;
    thePreOrder.AccountID  = pClientTradingID->AccountID;

	CWriteableIndexPreOrder wtbIndexPreOrder;
	CIndexPreOrder *pIndexPreOrder=m_pDB->m_IndexPreOrderFactory->findByALLFlds(thePreOrder.BrokerID,thePreOrder.ExchangeID,thePreOrder.InvestorID,\
		thePreOrder.InstrumentID,thePreOrder.HedgeFlag);
	if (pIndexPreOrder != NULL)
	{
		thePreOrder.linkIndexPreOrder(pIndexPreOrder);
		m_pDB->m_IndexPreOrderFactory->retrieve(pIndexPreOrder,&wtbIndexPreOrder);
	}
	else
	{
		wtbIndexPreOrder.init();
		bSuccess = InitIndexPreOrder(&thePreOrder,&wtbIndexPreOrder,pTransaction,true);
		if (!bSuccess)
		{
			char* errMsg;
			int errorCode;
			m_pErrorEngine->getLastError(&errorCode,&errMsg);
			REPORT_EVENT(LOG_CRITICAL, "RtnOrderFromRecoveryOrPrivateFlow  Error "," ErrorID:%d ErrorMsg:%s\n",  errorCode,errMsg);
			return false;
		}
		pIndexPreOrder = thePreOrder.getIndexPreOrder();
	}  

	thePreOrder.FrozenMargin  = 0.0;
	thePreOrder.FrozenFee     = 0.0;
	// 资金规则检查，同时把资金账户指针通过引用参数返回
	bSuccess  = m_pMoneyPosition->OrderInsertMoneyFrozen(&thePreOrder,&wtbIndexPreOrder,&theMoneyField,pTransaction,true);
	if(!bSuccess)  
	{
		return false;
	}
	thePreOrder.FrozenMargin  = theMoneyField.FrozenMarginChanged;
	thePreOrder.FrozenFee      = theMoneyField.Fee;

	bSuccess = m_pMoneyPosition->OrderInsertPositionFrozen(&thePreOrder,&wtbIndexPreOrder,&theMoneyField,pTransaction,true);
	if (!bSuccess)
	{
		return false;
	}

	//更新InvestorAccount
	CWriteableInvestorAccount theWriteableInvestorAccount ;
	m_pDB->m_InvestorAccountFactory->retrieve(pIndexPreOrder->getInvestorAccount(),&theWriteableInvestorAccount);
	
	//更新实时资金表
	theWriteableInvestorAccount.FrozenFee  += theMoneyField.Fee;
	theWriteableInvestorAccount.FrozenMargin += theMoneyField.FrozenMarginChanged;
	
	//更新结算准备金和和可用资金
	CFutureMoneyPosition::ChangeBalanceAndAvailable(&theWriteableInvestorAccount);
	m_pDB->m_InvestorAccountFactory->update(pIndexPreOrder->getInvestorAccount(),&theWriteableInvestorAccount,pTransaction);
	m_pDB->m_IndexPreOrderFactory->update(pIndexPreOrder,&wtbIndexPreOrder,pTransaction);

	if (thePreOrder.TradingDay.isNull())
	{
		thePreOrder.TradingDay     = getTradingDay(m_pDB);
	}
    theWriteableOrder.init();
    CopyOrderEntity(&theWriteableOrder,&thePreOrder);
	
	// 注释掉对 VolumeTraded 的赋值
	theWriteableOrder.VolumeTraded = 0;
	theWriteableOrder.RecNum = thePreOrder.VolumeTraded;
	
	
	//为了qkernel通过检查,强制赋值
	if( !theWriteableOrder.DealFlag.isValid())
	{	
		theWriteableOrder.DealFlag=DF_Done;
	}
	if( !theWriteableOrder.OrderSource.isValid())
	{
		theWriteableOrder.OrderSource=OS_Participant;
	}
	if( ! theWriteableOrder.TimeCondition.isValid())
	{
		theWriteableOrder.TimeCondition=TC_GFD;
	}
    if( !theWriteableOrder.ForceCloseReason.isValid())
    {
		theWriteableOrder.ForceCloseReason=FCR_NotForceClose;
	}
	theWriteableOrder.SessionID = (*ppOrderField)->SessionID;

	theWriteableOrder.linkIndexPreOrder(thePreOrder.getIndexPreOrder());
#ifdef APP_QQUERY
	theWriteableOrder.linkInvestorPosition(thePreOrder.getInvestorPosition());
#endif
	CopyOrderEntity(*ppOrderField,&thePreOrder);
	if (strcmp(thePreOrder.UserCustom,"FakeRtnOrder")==0)
	{
		theWriteableOrder.UserCustom="";
	}
	m_pDB->m_OrderFactory->add(&theWriteableOrder,pTransaction);
	return true;
}


void CHandleOrder::CopyFieldInputOrderFromPreOrder(CInputOrderField* pOrderField, CPreOrder* pPreOrder)
{
	
	pOrderField->BrokerID         = pPreOrder->BrokerID;
    pOrderField->ClientID         = pPreOrder->ClientID;
	pOrderField->Direction        = pPreOrder->Direction;
    pOrderField->ExchangeID       = pPreOrder->ExchangeID;
  	pOrderField->FrozenFee        = pPreOrder->FrozenFee;
	pOrderField->FrozenMargin     = pPreOrder->FrozenMargin;
	pOrderField->HedgeFlag        = pPreOrder->HedgeFlag;
	pOrderField->InsertTime       = pPreOrder->InsertTime;
	pOrderField->InstrumentID     = pPreOrder->InstrumentID;
	pOrderField->InvestorID       = pPreOrder->InvestorID;
	pOrderField->LimitPrice       = pPreOrder->LimitPrice;
	pOrderField->OffsetFlag       = pPreOrder->OffsetFlag;
	pOrderField->OrderLocalID     = pPreOrder->OrderLocalID;
	pOrderField->ParticipantID    = pPreOrder->ParticipantID;
	pOrderField->TradingDay       = pPreOrder->TradingDay;
	pOrderField->UserOrderLocalID = pPreOrder->UserOrderLocalID;
	pOrderField->Volume           = pPreOrder->Volume;
	pOrderField->UserID           = pPreOrder->UserID;	
    pOrderField->UserCustom       = pPreOrder->UserCustom;
	
    return;
}


//供RspOrderInsert调用
void CHandleOrder::PrepareWritableOrder(CWriteableOrder* pWritableOrder, CPreOrder* pPreOrder)
{
	
	pWritableOrder->init();
//	CopyOrderEntity(pWritableOrder,pPreOrder);
	memcpy(pWritableOrder,pPreOrder,sizeof(COrderField));
	if (pPreOrder->getIndexPreOrder()!=NULL)
	{
		pWritableOrder->linkIndexPreOrder(pPreOrder->getIndexPreOrder());
	}
	if (pPreOrder->getInvestorPosition()!=NULL)
	{
		pWritableOrder->linkInvestorPosition(pPreOrder->getInvestorPosition());
	}
	
	//为了qkernel通过检查,强制赋值
	if( !pWritableOrder->DealFlag.isValid())
	{	
		pWritableOrder->DealFlag=DF_Done;
	}
	if( !pWritableOrder->OrderSource.isValid())
	{
		pWritableOrder->OrderSource=OS_Participant;
	}
	if( ! pWritableOrder->TimeCondition.isValid())
	{
		pWritableOrder->TimeCondition=TC_GFD;
	}
    if( !pWritableOrder->ForceCloseReason.isValid())
    {
		pWritableOrder->ForceCloseReason=FCR_NotForceClose;
	}
    return; 
}


//供RtnOrder, 将PreOrder中的记录拷贝到Order中调用
void CHandleOrder::PrepareWritableOrder(CWriteableOrder* pWritableOrder, CPreOrder* pPreOrder,COrderField* pOrderField)
{
	pWritableOrder->init();
	CopyOrderEntity(pWritableOrder,pPreOrder);
	if (pPreOrder->getIndexPreOrder()!=NULL)
	{
		pWritableOrder->linkIndexPreOrder(pPreOrder->getIndexPreOrder());
	}
	if (pPreOrder->getInvestorPosition()!=NULL)
	{
		pWritableOrder->linkInvestorPosition(pPreOrder->getInvestorPosition());
	}
	
	pWritableOrder->OrderSysID   = pOrderField->OrderSysID;
	pWritableOrder->OrderStatus  = pOrderField->OrderStatus;
	pWritableOrder->InsertTime = pOrderField->InsertTime;
	// 报单回报中不修改字段 VolumeTraded，放到成交回报中修改 2014-03-19 longqy
	//pWritableOrder->VolumeTraded = pOrderField->VolumeTraded;
	//pWritableOrder->VolumeRemain = pOrderField->VolumeRemain;
	
	//为了qkernel通过检查,强制赋值
	if( !pWritableOrder->DealFlag.isValid())
	{	
		pWritableOrder->DealFlag=DF_Done;
	}
	if( !pWritableOrder->OrderSource.isValid())
	{
		pWritableOrder->OrderSource=OS_Participant;
	}
	if( ! pWritableOrder->TimeCondition.isValid())
	{
		pWritableOrder->TimeCondition=TC_GFD;
	}
    if( !pWritableOrder->ForceCloseReason.isValid())
    {
		pWritableOrder->ForceCloseReason=FCR_NotForceClose;
	}
    return; 
}




//供RtnOrder, 收到自其他席位的市价单和限价IOC单，准备插入订单簿
void CHandleOrder::PrepareWritableOrder(CWriteableOrder* pWritableOrder, COrderField *pOrderField)
{
	CopyOrderEntity(pWritableOrder,pOrderField);
	pWritableOrder->linkIndexPreOrder(m_pDB->m_IndexPreOrderFactory);
//	pWritableOrder->linkInvestorMargin(m_pDB->m_InvestorMarginFactory);
//	pWritableOrder->linkInvestorPosition(m_pDB->m_InvestorPositionFactory);
//	pWritableOrder->linkInstrument(m_pDB->m_InstrumentFactory);
//	pWritableOrder->linkInvestorAccount(m_pDB->m_InvestorAccountFactory);
	
	//从别的席位或从交易所私有流反演收到的市价单，或者限价IOC单都不需要解冻资金，因为前面没有冻结资金
	//将OrderStatus设置成撤单之后，后面解冻资金时就不会再解冻
	if (pWritableOrder->OrderPriceType==OPT_AnyPrice)
	{
		if(pWritableOrder->TimeCondition==TC_IOC)
		{
			pWritableOrder->OrderStatus=OS_Canceled;
		}
		else
		{
		//市价单的GFD单转成了限价单，后续需要解冻资金
			pWritableOrder->OrderStatus= OS_NoTradeNotQueueing;
		}
	}
	else
	{//限价、五档价、最优价的IOC单，直接设置为撤单状态
		if (pWritableOrder->TimeCondition==TC_IOC)
		{
			pWritableOrder->OrderStatus=OS_Canceled;
		}
		else
		{
			//限价、五档价、最优价的GFD单，后面必须释放资金
			pWritableOrder->OrderStatus= OS_NoTradeNotQueueing;  //订单状态被RspActioin改变
		}
	}
	
	//为了qkernel通过检查,强制赋值
	if( !pWritableOrder->DealFlag.isValid())
	{	
		pWritableOrder->DealFlag=DF_Done;
	}
	if( !pWritableOrder->OrderSource.isValid())
	{
		pWritableOrder->OrderSource=OS_Participant;
	}
	if( ! pWritableOrder->TimeCondition.isValid())
	{
		pWritableOrder->TimeCondition=TC_GFD;
	}
    if( !pWritableOrder->ForceCloseReason.isValid())
    {
		pWritableOrder->ForceCloseReason=FCR_NotForceClose;
	}
	return ;
}

void CHandleOrder::CopyFieldOrderFromPreOrder(COrderField* pOrderField, CPreOrder* pPreOrder)
{
	pOrderField->UserOrderLocalID = pPreOrder->UserOrderLocalID;
	pOrderField->OrderLocalID     = pPreOrder->OrderLocalID;
	pOrderField->OrderSource      = pPreOrder->OrderSource;
	pOrderField->UserCustom		  = pPreOrder->UserCustom;
    //解决OnRtnOrder中HedgeFlag始终为1的错误  added by liumeng  2014-08-07
	pOrderField->HedgeFlag       = pPreOrder->HedgeFlag;
	//补充私有流前置信息 chengm 20151220
	pOrderField->UserID			 = pPreOrder->UserID;
	pOrderField->InvestorID		 = pPreOrder->InvestorID;

	
	if(OS_PartTradedQueueing == pOrderField->OrderStatus  || OS_AllTraded == pOrderField->OrderStatus || OS_Canceled == pOrderField->OrderStatus)  //如果部分成交或全部成交
    {
		
		pOrderField->FrozenFee   = 0.0;
		pOrderField->FrozenMargin = 0.0;
	}	
	else
	{
        pOrderField->FrozenFee   = pPreOrder->FrozenFee;
		pOrderField->FrozenMargin = pPreOrder->FrozenMargin;
	}
				
	return ;
}

void CHandleOrder::CopyFieldOrderFromOrderInsertFailed(CInputOrderField* pInputOrderField, COrderInsertFailed* pOrderInsertFailed)
{
	
   	pInputOrderField->BrokerID         = pOrderInsertFailed->BrokerID;
	pInputOrderField->ClientID         = pOrderInsertFailed->ClientID;
	pInputOrderField->Direction        = pOrderInsertFailed->Direction;
	pInputOrderField->ExchangeID       = pOrderInsertFailed->ExchangeID;
	pInputOrderField->FrozenFee        = pOrderInsertFailed->FrozenFee;
	pInputOrderField->FrozenMargin     = pOrderInsertFailed->FrozenMargin;
	pInputOrderField->HedgeFlag        = pOrderInsertFailed->HedgeFlag;
	pInputOrderField->InsertTime       = pOrderInsertFailed->InsertTime;
	pInputOrderField->InstrumentID     = pOrderInsertFailed->InstrumentID;
	pInputOrderField->InvestorID       = pOrderInsertFailed->InvestorID;
	pInputOrderField->LimitPrice       = pOrderInsertFailed->LimitPrice;
	pInputOrderField->OffsetFlag       = pOrderInsertFailed->OffsetFlag;
	pInputOrderField->OrderLocalID     = pOrderInsertFailed->OrderLocalID;
	pInputOrderField->ParticipantID    = pOrderInsertFailed->ParticipantID;
	pInputOrderField->UserOrderLocalID = pOrderInsertFailed->UserOrderLocalID;
	pInputOrderField->Volume           = pOrderInsertFailed->Volume;
	pInputOrderField->UserID           = pOrderInsertFailed->UserID;	
	return ;
}


void CHandleOrder::CopyFieldOrderFromOrder(COrderField* pOrderField, COrder* pOrder)
{
	pOrderField->BrokerID         = pOrder->BrokerID;
	pOrderField->UserID           = pOrder->UserID;
	pOrderField->UserOrderLocalID = pOrder->UserOrderLocalID;
	pOrderField->OrderLocalID     = pOrder->OrderLocalID;
	pOrderField->OrderSource      = pOrder->OrderSource;
	pOrderField->UserCustom		  = pOrder->UserCustom;
	pOrderField->FrozenFee        = pOrder->FrozenFee;
	pOrderField->FrozenMargin     = pOrder->FrozenMargin;
	
    //解决OnRtnOrder中HedgeFlag始终为1的错误  added by liumeng  2014-08-07
	pOrderField->HedgeFlag        = pOrder->HedgeFlag;
	pOrderField->OffsetFlag		  = pOrder->OffsetFlag;
	//补充私有流前置信息 chengm 20151220
	pOrderField->UserID			 = pOrder->UserID;
	pOrderField->InvestorID		 = pOrder->InvestorID;
	//补充frontid和sessionid chengm 20161019
	pOrderField->FrontID		 = pOrder->FrontID;
	pOrderField->SessionID		 = pOrder->SessionID;
	pOrderField->IPAddress		 = pOrder->IPAddress;
	pOrderField->MacAddress		 = pOrder->MacAddress;
	pOrderField->OrderPriceType	 = pOrder->OrderPriceType;
	pOrderField->BusinessType	 = pOrder->BusinessType;


	//金交所需要从order表里获取VolumeTraded和VolumeRemain
	if (pOrderField->ExchangeID == EX_SGE)
	{
		pOrderField->VolumeTraded = pOrder->VolumeTraded;
		pOrderField->VolumeRemain = pOrder->VolumeRemain;
	}


	return ;
}

bool CHandleOrder::DumpDebugInfo()
{
	m_pDB->save(m_pConfig);
	for (int j=2; j<=g_pExchangeLinkManager->m_iMaxAPIID; j++)
	{
		CBaseExchApi *pBaseApi = g_pExchApiArryMap[j];
		if(pBaseApi == NULL)
		{
			continue;
		}
	}

	return true;
}

void CHandleOrder::AddOrderDelay(CPreOrder *pPreOrder)
{
	CWriteableOrderDelay delay;
	delay.BrokerID = pPreOrder->BrokerID;
	delay.UserID = pPreOrder->UserID;
	delay.UserOrderLocalID = pPreOrder->UserOrderLocalID;
	delay.FrontID = pPreOrder->FrontID;
	delay.SessionID = pPreOrder->SessionID;
	delay.RequestID = pPreOrder->RequestID;
	delay.FTdRecvDown = pPreOrder->FTdRecvDown;
	delay.CoreRecvDown = pPreOrder->CoreRecvDown;
	delay.CoreSendUp = pPreOrder->CoreSendUp;
	delay.CoreRecvUp = pPreOrder->CoreRecvUp;
	delay.CoreSendDown = pPreOrder->MinVolume;
	m_pDB->m_OrderDelayFactory->add(&delay);
}

void CHandleOrder::SendOrderField(COrderField *pOrderField,bool bSendRtn)
{
	if (bSendRtn && !g_bIsQquery && strcmp(pOrderField->UserCustom,"FakeRtnOrder") )
	{
		pOrderField->VolumeRemain = pOrderField->Volume - pOrderField->VolumeTraded;
		m_pPubMessage->PreparePublish(TID_NtfOrder);
		XTP_ADD_FIELD(m_pPubMessage, pOrderField);
		m_pPubMessage->MakePackage();
		m_pTradeResult->Append(m_pPubMessage->Address(), m_pPubMessage->Length());	
	}
}