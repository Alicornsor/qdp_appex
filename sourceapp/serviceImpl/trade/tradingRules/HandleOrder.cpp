/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file COrderInsertRules.h
///@briefʵ������COrderInsertRules
///@history 
///20060113	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#include "HandleOrder.h"
#include "tradingTools.h"
#include "BaseExchApi.h"
#include "ExchangeLinkManager.h"
#include "system.h"
#include "printinfo.h"

extern CBaseExchApi *g_pExchApiArryMap[];//��������APImap
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
	
	//�˴�����Ҫ����ֱ�Ӳ����ڴ��
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

	//��΢���ȷʱ����뵽UserCustom�ֶΣ���Ϊ���������֮һ liumeng 20140820
	long nCurrentTime =0;
 	GET_ACCURATE_USEC_TIME(nCurrentTime);
	theWriteableOrderInsertFailed.UserCustom = nCurrentTime;
			
	//�˴�����Ҫ����ֱ�Ӳ����ڴ��
	m_pDB->m_OrderInsertFailedFactory->add(&theWriteableOrderInsertFailed,NULL); 
	return true;
}


bool CHandleOrder::HandleOrderInsert(CWriteableIndexPreOrder *pIndexPreOrder,CWriteablePreOrder *pPreOrder,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	bool bSuccess = false;
	//20160817 huwp ��֮ǰί�гɹ����Ķ�����Ϣ�������ø���ָ��
	pPreOrder->APIID = 0;
	if (likely(!g_bIsMultiSeat))
	{
		pPreOrder->APIID = pIndexPreOrder->APIID;
	}
	else if (unlikely(!pPreOrder->BranchID.isNull()))
	{
		pPreOrder->APIID = atoi(pPreOrder->BranchID.getValue());
	}

	//Ͷ����Ȩ�޼��
	bSuccess = m_pBaseCheck->RightCheck(pPreOrder,pTransaction);
	if (unlikely(!bSuccess))
	{
		return false;
	}

	pPreOrder->FrozenFee=0.0;
	pPreOrder->FrozenMargin=0.0;
	//�ʽ�������
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
	
	//�ֲ��޶����
	bSuccess = m_pMoneyPosition->OrderInsertPositionFrozen(pPreOrder,pIndexPreOrder,&theMoneyField,pTransaction);
	if (!bSuccess)
	{
		//REPORT_EVENT(LOG_CRITICAL,"HandleOrderInsert","frozen position error investorid:%s instrumentid:%s\n",pPreOrder->InvestorID.getValue(),pPreOrder->InstrumentID.getValue());
		return false;
	}


	//ͨ�����
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
		//����MaxLocalID
		CWriteableMaxLocalID theMaxLocalID;
		m_pDB->m_MaxLocalIDFactory->retrieve(pPreOrder->getIndexPreOrder()->getMaxLocalID(),&theMaxLocalID);
		theMaxLocalID.MaxOrderLocalID=pPreOrder->UserOrderLocalID;
		m_pDB->m_MaxLocalIDFactory->update(pPreOrder->getIndexPreOrder()->getMaxLocalID(),&theMaxLocalID,pTransaction);
		//����InvestorAccount
		CWriteableInvestorAccount theWriteableInvestorAccount ;
		m_pDB->m_InvestorAccountFactory->retrieve(pIndexPreOrder->getInvestorAccount(),&theWriteableInvestorAccount);			
		//����ʵʱ�ʽ��
		theWriteableInvestorAccount.FrozenFee  = theWriteableInvestorAccount.FrozenFee + theMoneyField.Fee;			
		theWriteableInvestorAccount.FrozenMargin += theMoneyField.FrozenMarginChanged;			
		//���½���׼����ͺͿ����ʽ�
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
	
	if(0 == pRspInfoField->ErrorID )   // ���������سɹ��������ѱ��롣
	{		
		COrder* pOrder = m_pDB->m_OrderFactory->findByExchangeIDAndOrderSysID(wtbPreOrder->ExchangeID,wtbPreOrder->OrderSysID);
		if(NULL == pOrder)  //����ί�б��¼Ϊ�գ���Ԥί�б�����ί�б�
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
				//���ش��󣬲��붩����ʧ��
				REPORT_EVENT(LOG_CRITICAL,"HandleRtnOrder ERR,OrderSysID=[%s]\n",wtbPreOrder->OrderSysID.getValue());
				return false;
			}
		}
		else    //ί�б��¼�Ѿ����ڣ�ֱ��ɾ��Ԥί�б�
		{  
			m_pPubMessage->PreparePublish(TID_NtfOrder);
			XTP_ADD_FIELD(m_pPubMessage, pOrder);
			m_pPubMessage->MakePackage();
			m_pTradeResult->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
			m_pDB->m_PreOrderFactory->remove(PreOrder,NULL);
		}
		return true;  
	}
	else     //�� -  �����ɽ��������س�����Ϣ  Ԥί�б����
	{	
		//�ⶳ�ʽ�
		if (!m_pMoneyPosition->MoneyUnFrozen(PreOrder,pTransaction))
		{
			REPORT_EVENT(LOG_CRITICAL,"MoneyUnFrozen","unfrozen position error in order cancel");
			return false;
		}
		

		//�ⶳ�ֲ�
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
	if(pOrderField->OrderStatus == OS_Canceled)   // ���״̬Ϊ�ѳ���
	{
		bSuccess = HandleRtnOrderCancel(pOrderField,sessionRef,pTransaction,bSendRtn);
	}
    else   // ���״̬Ϊ�����ύ�������ɽ�
	{
		pOrder =   m_pDB->m_OrderFactory->findByExchangeIDAndOrderSysID(pOrderField->ExchangeID,pOrderField->OrderSysID);
		if(NULL != pOrder  )    //�����ί�б��в�����
		{
			//����˴�û�з����κγ������Ӻͳɽ����ӣ�˵�����ظ����������
// 			if(pOrder->ExchangeID == EXID_SGE && pOrder->OrderStatus !='\0' &&
// 				(pOrderField->VolumeTraded <= pOrder->RecNum || pOrder->OrderStatus == OS_Canceled) )
// 			{
// 				REPORT_EVENT(LOG_CRITICAL, "Duplicate rtnOrder","In Line %d of File %s.\n",__LINE__,__FILE__);
// 				m_pErrorEngine->reportError(ERROR_DUPLICATE_RTN_ORDER);
// 				return false;
// 			}
			CopyFieldOrderFromOrder(pOrderField,pOrder);
			SendOrderField(pOrderField,bSendRtn);
			// ����ί�б�״̬
			CWriteableOrder   theWriteableOrder ;
			theWriteableOrder.init();
			m_pDB->m_OrderFactory->retrieve(pOrder,&theWriteableOrder);
			
			///longqy 2013-12-13 �ȵ��ĳ����ر����󳷵���֮ǰ�Ĳ��ֳɽ��ر����󣬻��������
			// ֻ��״̬���ǳ���״̬�����ܸı�Ϊ��������״̬
			if (OS_Canceled != theWriteableOrder.OrderStatus)
			{	// �������״̬�Ѿ��ǳ���״̬���������״̬�����ܹ��ٸ�Ϊ������״̬
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
			if(pPreOrder!=NULL)   //�����Ԥί�б��д���
			{
				//������Ϣ��ǰ��
				CopyFieldOrderFromPreOrder(pOrderField,pPreOrder);
				SendOrderField(pOrderField,bSendRtn);
				//����ί�б�
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
				// ����˽��������ϯλ�ı����ر����ݣ������ʽ�ֲֶ��ᴦ��
				bSuccess = RtnOrderFromRecoveryOrPrivateFlow(&pOrderField,pTransaction);
				SendOrderField(pOrderField,bSendRtn);
				return bSuccess;  
			}
		}
	}	
    return true;
}

//����״̬Ϊ�ѳ��������
bool CHandleOrder::HandleRtnOrderCancel(COrderField *pOrderField,const TSessionRef &sessionRef,CTransaction *pTransaction,bool bSendRtn)
{ 
	//��ί�б��Ƿ����
	COrder *pOrder=m_pDB->m_OrderFactory->findByExchangeIDAndOrderSysID(pOrderField->ExchangeID,pOrderField->OrderSysID);
	if (pOrder != NULL)
	{
		//��������Ѿ������ˣ�˵�����ظ����������
// 		if(pOrder->ExchangeID == EXID_SGE && pOrder->OrderStatus == OS_Canceled && pOrder->VolumeRemain == pOrder->CancleVolume)
// 		{
// 			REPORT_EVENT(LOG_CRITICAL, "Duplicate rtnOrder","In Line %d of File %s.\n",__LINE__,__FILE__);
// 			m_pErrorEngine->reportError(ERROR_DUPLICATE_RTN_ORDER);
// 			return false;
// 		}
		// �����ر��в��޸��ֶ� VolumeTraded���ŵ��ɽ��ر����޸� 2014-03-19 longqy
		// ����ȫ����ʱ���ڴ����ݿ��е�VolumeTraded\VolumeRemainΪ0\0����� 2014-08-01 liumeng
		CWriteableOrder   theWriteableOrder ;
		theWriteableOrder.init();
		m_pDB->m_OrderFactory->retrieve(pOrder,&theWriteableOrder);
		pOrderField->VolumeRemain = pOrder->Volume - pOrderField->VolumeTraded;
		theWriteableOrder.CancleVolume = pOrderField->VolumeRemain;
		theWriteableOrder.RecNum = pOrderField->VolumeTraded;
		// 2015-02-05 longqy ����ʱ�䲹��
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
		
		//���OnRtnOrder��HedgeFlagʼ��Ϊ1�Ĵ���  added by liumeng  2014-10-28
		pOrderField->HedgeFlag       = pOrder->HedgeFlag;
		//�����Щ����������֪ͨû�п�ƽ��־�ֶ�
		pOrderField->OffsetFlag		 = pOrder->OffsetFlag;
		//����˽����ǰ����Ϣ chengm 20151220
		pOrderField->UserID			 = pOrder->UserID;
		pOrderField->InvestorID		 = pOrder->InvestorID;
		pOrderField->FrontID		 = pOrder->FrontID;
		pOrderField->SessionID		 = pOrder->SessionID;
		SendOrderField(pOrderField,bSendRtn);
		return true;
	}
	else
	{
		//2.��Ԥί�б��Ƿ����
		CPreOrder *pPreOrder =  m_pDB->m_PreOrderFactory->findByAPIIDAndOrderLocalID(pOrderField->APIID,pOrderField->OrderLocalID);
		if (pPreOrder != NULL)
		{
			pOrderField->UserID           =  pPreOrder->UserID;
			pOrderField->UserCustom       =  pPreOrder->UserCustom;
			pOrderField->UserOrderLocalID =  pPreOrder->UserOrderLocalID;
			pOrderField->InvestorID		  =  pPreOrder->InvestorID;
			//���OnRtnOrder��HedgeFlagʼ��Ϊ1�Ĵ���  added by liumeng  2014-10-28
			pOrderField->HedgeFlag       = pPreOrder->HedgeFlag;
			pOrderField->FrontID		 = pPreOrder->FrontID;
			pOrderField->SessionID		 = pPreOrder->SessionID;
			SendOrderField(pOrderField,bSendRtn);

			CWriteableOrder   theWriteableOrder ;
			PrepareWritableOrder(&theWriteableOrder,pPreOrder,pOrderField);
			//������״̬���ܸ�Ϊ�ѳ�����������ƣ���RspOrderActionͳһ����
			theWriteableOrder.OrderStatus  = OS_NoTradeNotQueueing;
			theWriteableOrder.TradingDay = pOrderField->TradingDay;
			// 2015-02-05 longqy ����ʱ�䲹��
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

			//��ȡInvestorID
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

		
	//����Ҫ�Ѷ�����Ϣ��ȫ
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
	// �ʽ�����飬ͬʱ���ʽ��˻�ָ��ͨ�����ò�������
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

	//����InvestorAccount
	CWriteableInvestorAccount theWriteableInvestorAccount ;
	m_pDB->m_InvestorAccountFactory->retrieve(pIndexPreOrder->getInvestorAccount(),&theWriteableInvestorAccount);
	
	//����ʵʱ�ʽ��
	theWriteableInvestorAccount.FrozenFee  += theMoneyField.Fee;
	theWriteableInvestorAccount.FrozenMargin += theMoneyField.FrozenMarginChanged;
	
	//���½���׼����ͺͿ����ʽ�
	CFutureMoneyPosition::ChangeBalanceAndAvailable(&theWriteableInvestorAccount);
	m_pDB->m_InvestorAccountFactory->update(pIndexPreOrder->getInvestorAccount(),&theWriteableInvestorAccount,pTransaction);
	m_pDB->m_IndexPreOrderFactory->update(pIndexPreOrder,&wtbIndexPreOrder,pTransaction);

	if (thePreOrder.TradingDay.isNull())
	{
		thePreOrder.TradingDay     = getTradingDay(m_pDB);
	}
    theWriteableOrder.init();
    CopyOrderEntity(&theWriteableOrder,&thePreOrder);
	
	// ע�͵��� VolumeTraded �ĸ�ֵ
	theWriteableOrder.VolumeTraded = 0;
	theWriteableOrder.RecNum = thePreOrder.VolumeTraded;
	
	
	//Ϊ��qkernelͨ�����,ǿ�Ƹ�ֵ
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


//��RspOrderInsert����
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
	
	//Ϊ��qkernelͨ�����,ǿ�Ƹ�ֵ
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


//��RtnOrder, ��PreOrder�еļ�¼������Order�е���
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
	// �����ر��в��޸��ֶ� VolumeTraded���ŵ��ɽ��ر����޸� 2014-03-19 longqy
	//pWritableOrder->VolumeTraded = pOrderField->VolumeTraded;
	//pWritableOrder->VolumeRemain = pOrderField->VolumeRemain;
	
	//Ϊ��qkernelͨ�����,ǿ�Ƹ�ֵ
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




//��RtnOrder, �յ�������ϯλ���м۵����޼�IOC����׼�����붩����
void CHandleOrder::PrepareWritableOrder(CWriteableOrder* pWritableOrder, COrderField *pOrderField)
{
	CopyOrderEntity(pWritableOrder,pOrderField);
	pWritableOrder->linkIndexPreOrder(m_pDB->m_IndexPreOrderFactory);
//	pWritableOrder->linkInvestorMargin(m_pDB->m_InvestorMarginFactory);
//	pWritableOrder->linkInvestorPosition(m_pDB->m_InvestorPositionFactory);
//	pWritableOrder->linkInstrument(m_pDB->m_InstrumentFactory);
//	pWritableOrder->linkInvestorAccount(m_pDB->m_InvestorAccountFactory);
	
	//�ӱ��ϯλ��ӽ�����˽���������յ����м۵��������޼�IOC��������Ҫ�ⶳ�ʽ���Ϊǰ��û�ж����ʽ�
	//��OrderStatus���óɳ���֮�󣬺���ⶳ�ʽ�ʱ�Ͳ����ٽⶳ
	if (pWritableOrder->OrderPriceType==OPT_AnyPrice)
	{
		if(pWritableOrder->TimeCondition==TC_IOC)
		{
			pWritableOrder->OrderStatus=OS_Canceled;
		}
		else
		{
		//�м۵���GFD��ת�����޼۵���������Ҫ�ⶳ�ʽ�
			pWritableOrder->OrderStatus= OS_NoTradeNotQueueing;
		}
	}
	else
	{//�޼ۡ��嵵�ۡ����ż۵�IOC����ֱ������Ϊ����״̬
		if (pWritableOrder->TimeCondition==TC_IOC)
		{
			pWritableOrder->OrderStatus=OS_Canceled;
		}
		else
		{
			//�޼ۡ��嵵�ۡ����ż۵�GFD������������ͷ��ʽ�
			pWritableOrder->OrderStatus= OS_NoTradeNotQueueing;  //����״̬��RspActioin�ı�
		}
	}
	
	//Ϊ��qkernelͨ�����,ǿ�Ƹ�ֵ
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
    //���OnRtnOrder��HedgeFlagʼ��Ϊ1�Ĵ���  added by liumeng  2014-08-07
	pOrderField->HedgeFlag       = pPreOrder->HedgeFlag;
	//����˽����ǰ����Ϣ chengm 20151220
	pOrderField->UserID			 = pPreOrder->UserID;
	pOrderField->InvestorID		 = pPreOrder->InvestorID;

	
	if(OS_PartTradedQueueing == pOrderField->OrderStatus  || OS_AllTraded == pOrderField->OrderStatus || OS_Canceled == pOrderField->OrderStatus)  //������ֳɽ���ȫ���ɽ�
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
	
    //���OnRtnOrder��HedgeFlagʼ��Ϊ1�Ĵ���  added by liumeng  2014-08-07
	pOrderField->HedgeFlag        = pOrder->HedgeFlag;
	pOrderField->OffsetFlag		  = pOrder->OffsetFlag;
	//����˽����ǰ����Ϣ chengm 20151220
	pOrderField->UserID			 = pOrder->UserID;
	pOrderField->InvestorID		 = pOrder->InvestorID;
	//����frontid��sessionid chengm 20161019
	pOrderField->FrontID		 = pOrder->FrontID;
	pOrderField->SessionID		 = pOrder->SessionID;
	pOrderField->IPAddress		 = pOrder->IPAddress;
	pOrderField->MacAddress		 = pOrder->MacAddress;
	pOrderField->OrderPriceType	 = pOrder->OrderPriceType;
	pOrderField->BusinessType	 = pOrder->BusinessType;


	//������Ҫ��order�����ȡVolumeTraded��VolumeRemain
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