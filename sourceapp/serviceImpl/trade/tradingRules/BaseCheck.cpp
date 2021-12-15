/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file BaseCheck.cpp
///@brief实现了类CBaseCheck(订单基础检查类)
///@history 
///20121222	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "BaseCheck.h"
#include <stdlib.h>
#include "tradingTools.h"
#include "public.h"
#include "UFEntityCopy.h"
#include "BaseExchApi.h"
#include "ExchangeLinkManager.h"
#include "system.h"

#define REPORT_ERROR(errorid)	{ m_pErrorEngine->reportError(errorid);return false;}

extern CExchangeLinkManager* g_pExchangeLinkManager;

CBaseCheck::CBaseCheck(CMemoryDB *pDB, CErrorEngine *pErrorEngine)
{
	m_pDB=pDB;
	m_pErrorEngine=pErrorEngine;
}

CBaseCheck::~CBaseCheck()
{	
// 	delete m_pMapSeatOrdLocalID;
}

bool CBaseCheck::OrderCheck(CWriteablePreOrder *pOrder,const TSessionRef &sessionRef,CTransaction* pTransaction)
{
	bool success=true;
	if(!LocalIDCheck(pOrder->BrokerID,pOrder->UserOrderLocalID,pOrder->UserID,sessionRef,pTransaction))
	{
		//printf("基础检查错误，本地报单号错误\n");
		REPORT_EVENT(LOG_CRITICAL,"OrderCheck","基础检查错误，本地报单号错误");
		return false;
	}
	
	///2.检查该User是否有对投资者投资的权限	
	if(m_pDB->m_UserInvestorFactory->findByBrokerIDUserIDInvestorID(pOrder->BrokerID,pOrder->UserID,pOrder->InvestorID)==NULL)
	{
		REPORT_ERROR(ERROR_USER_INVESTOR_NOT_RELATED);//User没有对该客户下单的权限
		return false;
	}
	
	
	///检查投资者账户是否存在
	CInvestorAccount *pInvestorAccount = m_pDB->m_InvestorAccountFactory->findByBrokerIDInvestorID(pOrder->BrokerID,pOrder->InvestorID);
	if(pInvestorAccount == NULL)
	{
		REPORT_ERROR(ERROR_CAN_NOT_FIND_ACCOUNT);
		return false;
	}
	pOrder->getIndexPreOrder()->linkInvestorAccount(pInvestorAccount);
	
	//通过所有检查之后，添加交易日，报单时间信息
	pOrder->TradingDay=getTradingDay(m_pDB);
	return true;
}

///会话检查
// bool CBaseCheck::SessionCheck(CWriteablePreOrder *pOrder,const TSessionRef &sessionRef)
// {
// 	pOrder->OrderSource=OS_Participant;
// 	return SessionCheck(pOrder->UserID,pOrder->BrokerID,sessionRef);
// }

///权限检查
bool CBaseCheck::RightCheck(CWriteablePreOrder *pOrder,CTransaction* pTransaction)
{
	CIndexPreOrder *pIndexPreOrder = pOrder->getIndexPreOrder();
	CClientTradingID *pClientTradingID = pIndexPreOrder->getClientTradingID();	
	if (unlikely(pClientTradingID->ClientRight!=TR_Allow))
	{
		REPORT_ERROR(ERROR_CLIENTID_CANNOT_TRADE);
		return false;
	}	
	///填入客户号/会员号
	pOrder->ClientID=pIndexPreOrder->ClientID;
	pOrder->ParticipantID=pIndexPreOrder->ParticipantID;

	//用户最大报单号检查
	CMaxLocalID *pMaxLocalID=NULL;
	if (likely(pIndexPreOrder->SessionID == pOrder->SessionID))
	{
		pMaxLocalID = pIndexPreOrder->getMaxLocalID();
	}
	else
	{
		pMaxLocalID = m_pDB->m_MaxLocalIDFactory->findByFrontIDSessionID(pOrder->FrontID,pOrder->SessionID);
		pIndexPreOrder->linkMaxLocalID(pMaxLocalID);
	}
	
	if (unlikely(pMaxLocalID==NULL))
	{		
		m_pErrorEngine->reportError(ERROR_NOT_LOGIN_YET);
		return false;
	}
	else
	{
		if (unlikely(pMaxLocalID->UserID != pOrder->UserID))
		{
			m_pErrorEngine->reportError(ERROR_NOT_LOGINED_BY_THIS_USER);
			return false;
		}
		else if (unlikely(pMaxLocalID->MaxOrderLocalID>=pOrder->UserOrderLocalID))
		{
			m_pErrorEngine->reportError(ERROR_DUPLICATE_ORDER);
			return false;
		}
		else
		{
			pOrder->IPAddress = pMaxLocalID->IPAddress;
			pOrder->MacAddress = pMaxLocalID->MacAddress;
			return true;
		}	
	}

	//UserID和索引的UserID不一致时,需要重新校验UserID和InvestorID的关系
	if (unlikely(pIndexPreOrder->UserID != pOrder->UserID))
	{
		if(m_pDB->m_UserInvestorFactory->findByBrokerIDUserIDInvestorID(pOrder->BrokerID,pOrder->UserID,pOrder->InvestorID)==NULL)
		{
			m_pErrorEngine->reportError(ERROR_USER_INVESTOR_NOT_RELATED);//User没有对该客户下单的权限
			return false;
		}
	}


}	

//4.客户本地报单号检查
// bool CBaseCheck::LocalIDCheck(CWriteablePreOrder *pOrder,CTransaction* pTransaction)
// {
// 	return LocalIDCheck(pOrder->BrokerID,pOrder->ExchangeID,pOrder->SeatID,pOrder->UserOrderLocalID,pOrder->UserID,pOrder->OrderLocalID,pTransaction);
// }	

bool CBaseCheck::VolumePriceCheck(CWriteablePreOrder *pOrder)
{
// 	///1.检查报单合约是否存在
// 	CInstrument* pInstrument= pOrder->getInstrument();
// 	if (NULL == pInstrument)
// 	{
// 		CInstrumentMap::iterator it = m_InstrumentMap.find(pOrder->InstrumentID);	
// 		if (it!=m_InstrumentMap.end())
// 		{	// 合约表不上场了，此分支不会运行到。此MAP总是为空。
// 			CWriteableInstrument* pWriteableInstrument=it->second;
// 			pInstrument=pOrder->linkInstrument(pWriteableInstrument);
// 		}
// 		else
// 		{
// 			pInstrument=pOrder->linkInstrument(m_pDB->m_InstrumentFactory);
// 		}
// 		
// 		if (pInstrument == NULL)
// 		{
// 			REPORT_ERROR(ERROR_INSTRUMENT_NOT_FOUND);
// 		}
// 		///2.检查合约是否在交易
// 		if(!pInstrument->IsTrading)
// 		{
// 			REPORT_ERROR(ERROR_BAD_INSTRUMENT_STATUS_FIELD);
// 		}
// 		
// 		///3.限价单价格检查
// 		///对最大浮点数进行控制 20130729 linxb
// 		if(pOrder->LimitPrice == DOUBLE_NaN)
// 		{
// 			REPORT_ERROR(ERROR_PRICE_OUT_OF_UPPER_BOUND);
// 		}	
// 	}
// 
// 
// 	///4.报单数量检查
// 	if(OPT_LimitPrice == pOrder->OrderPriceType)
// 	{
// 		///限价单
// 		if((pOrder->Volume < pInstrument->MinLimitOrderVolume) ||
// 			(pOrder->Volume > pInstrument->MaxLimitOrderVolume) )   //放宽检查条件，不检查整数倍 20130729 linxb
// 		{
// 			REPORT_ERROR(ERROR_INVALID_VOLUME);		
// 		}	
// 	}
// 	if(OPT_AnyPrice == pOrder->OrderPriceType || OPT_FiveLevelPrice == pOrder->OrderPriceType || OPT_BestPrice == pOrder->OrderPriceType)
// 	{
// 		///市价单
// 		if((pOrder->Volume < pInstrument->MinMarketOrderVolume) ||
// 			(pOrder->Volume > pInstrument->MaxMarketOrderVolume) )   // 放宽检查条件，不检查整数倍 20130729 linxb
// 		{
// 			REPORT_ERROR(ERROR_INVALID_VOLUME);		
// 		}
// 	}
	
	return true;
}

bool CBaseCheck::FieldCheck(CWriteablePreOrder *pOrder)
{
	if (! pOrder->UserID.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_USERID);}
	if (! pOrder->Direction.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_DIRECTION);}
	if (! pOrder->ExchangeID.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_EXCHANGEID);}
	if (! pOrder->HedgeFlag.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_HEDGEFLAG);}
	if (! pOrder->InstrumentID.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_INSTRUMENTID);}
	if (! pOrder->LimitPrice.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_LIMITPRICE);}
	if (! pOrder->Volume.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_VOLUME);}
	if (! pOrder->OffsetFlag.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_OFFSETFLAG);}
	if (! pOrder->UserOrderLocalID.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_USERORDERLOCALID);}
	if (! pOrder->OrderPriceType.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_ORDERPRICETYPE);}
	if (! pOrder->StopPrice.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_STOPPRICE);}
	if (! pOrder->BrokerID.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_BROKERID);}
	if (! pOrder->InvestorID.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_INVESTORID);}
	if (! pOrder->TimeCondition.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_TIMECONDITION);}
	if (! pOrder->GTDDate.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_GTDDATE);}
	if (! pOrder->VolumeCondition.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_VOLUMECONDITION);}
	if (! pOrder->MinVolume.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_MINVOLUME);}
	if (! pOrder->ForceCloseReason.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_FORCECLOSEREASON);}
	if (! pOrder->IsAutoSuspend.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_ISAUTOSUSPEND);}
	if (! pOrder->BusinessUnit.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_BUSINESSUNIT);}
	if (! pOrder->UserCustom.isValid()){
		REPORT_ERROR(ERROR_FIELDERROR_USERCUSTOM);}	
	return true;
}

/************************************************************************/
/*撤单检查函数                                                                      */
/************************************************************************/

bool CBaseCheck::OrderActionCheck(CWriteableOrderAction *pOrderAction,const TSessionRef &sessionRef,CTransaction* pTransaction)
{
	//系统状态检查
// 	if(!SysStatusCheck())
// 	{
// 		return false;
// 	}
	//操作目标检查
	if(!ActionTargetCheck(pOrderAction))
	{
		return false;
	}
// 	//席位分配
// 	if (!AssignSeat(pOrderAction))
// 	{
// 		return false;
// 	}

	//1.检查会话
	if(!SessionCheck(pOrderAction->IPAddress,pOrderAction->MacAddress,pOrderAction->UserID,pOrderAction->BrokerID,sessionRef))
	{
		return false;
	}
	
	//2.检查字段
/*	if(!FieldCheck(pOrderAction))
	{
		return false;			
	}*/
	//3.交易编码检查
/*	if(!RightCheck(pOrderAction))
	{
		return false;
	}*/
		
	//4.本地报单号检查
// 	if(!LocalIDCheck(pOrderAction,pTransaction))
// 	{
// 		return false;
// 	}

	CBaseExchApi *pBaseExchApi  = g_pExchangeLinkManager->getExchangeLink(pOrderAction->APIID);
	
	if(pBaseExchApi != NULL)
	{
		pOrderAction->ActionLocalID=pBaseExchApi->GetLocalID();	
		pOrderAction->SeatID = pBaseExchApi->GetUserID();
	}
	//通过所有检查之后，添加交易日，报单时间信息
	pOrderAction->CancelTime=getCurrentTime(m_pDB);
	return true;
}

//1.支持本地报单号UserOrderLocalID撤单,这里指的是客户本地自己编号，占用这个字段
//2.支持OrderSysID撤单
//3.如果UserOrderLocalID和OrderSysID均不为空，以OrderSysID优先级为高,wangwei,20130503
//4.如果撤单session与委托表session不一致，更新委托表sessionid,chengm,20151220
bool CBaseCheck::ActionTargetCheck(CWriteableOrderAction *pOrderAction)
{
	//EXRISKG-595
	//撤单时investorid,UserID
	if (pOrderAction->UserID.isNull())
	{
		REPORT_ERROR(ERROR_ORDERACTION_INVESTORID_CANNOTBEBLANK);
	}
	if (pOrderAction->BrokerID.isNull())
	{
		REPORT_ERROR(ERROR_BROKERID_CANNOT_BE_BLANK);
	}

	if (pOrderAction->ExchangeID.isNull())
	{
		REPORT_ERROR(ERROR_EXCHANGEID_CANNOTBEBLANK);
	}
	
	//1.按照系统报单号撤单的情况-wangwei,20130814
	if (!pOrderAction->OrderSysID.isNull())
	{
		//检查是否有操作目标
		const CWriteableOrder * pTargetOrder=pOrderAction->linkOrder(m_pDB->m_OrderFactory);
		if (pTargetOrder==NULL)
		{
			printf("撤单操作对象检查错误，没有找到OrderSysID=[%s]对应的报单\n",pOrderAction->OrderSysID.getValue());
			REPORT_ERROR(ERROR_ORDER_NOT_FOUND);
		}
		else
		{
			//added by chengm 20160422  报单全部成交或者已撤单时不能重复撤单
			if (OS_AllTraded ==pTargetOrder->OrderStatus || 
				OS_Canceled == pTargetOrder->OrderStatus)
			{
				REPORT_ERROR(ERROR_ORDER_HAD_CANCELED_OR_ALLTRADED);
				return false;
			}
			///2.检查该User是否有对投资者投资的权限	
			if(m_pDB->m_UserInvestorFactory->findByBrokerIDUserIDInvestorID(pOrderAction->BrokerID,pOrderAction->UserID,pTargetOrder->InvestorID)==NULL)
			{
				REPORT_ERROR(ERROR_USER_INVESTOR_NOT_RELATED);//User没有对该客户下单的权限
			}

			pOrderAction->InvestorID = pTargetOrder->InvestorID;
			pOrderAction->ClientID=pTargetOrder->ClientID;
/*** SIR XLONG BEGIN ***/
			//发送撤单请求时，将InstrumentID填上
			pOrderAction->InstrumentID=pTargetOrder->InstrumentID;
/*** SIR XLONG END ***/
			//added by chengm 20160120 根据APIID获取ExchLink
			pOrderAction->APIID=pTargetOrder->APIID;
			pOrderAction->OrderLocalID=pTargetOrder->OrderLocalID;
			//如果是同一会员撤自己的单，必须保证走一个席位
			if (pOrderAction->BrokerID==pTargetOrder->BrokerID)
			{
				pOrderAction->SeatID=pTargetOrder->SeatID;
				pOrderAction->ParticipantID=pTargetOrder->ParticipantID;
//				pOrderAction->BranchID=pTargetOrder->BranchID;
			}
			else
			{
				//client在交易所是唯一的，即使对应的是不同的会员
				CClientTradingID* pClntID=m_pDB->m_ClientTradingIDFactory->findByBrokerIDExchangeIDPartClientID(pOrderAction->BrokerID,pOrderAction->ExchangeID,pOrderAction->ParticipantID,pOrderAction->ClientID);
				//EXRISKG-574
				if (pClntID==NULL)
				{
						pClntID =  m_pDB->m_ClientTradingIDFactory->findByBrokerIDExchangeIDPartClientID(pOrderAction->BrokerID,"Broker",pOrderAction->ParticipantID,pOrderAction->ClientID);
						if( NULL == pClntID )
						{
							REPORT_ERROR(ERROR_PART_CLIENT_NOTRELATED_INTHISEXCHANGE);
						}
				}
				pOrderAction->ParticipantID=pClntID->ParticipantID;
			}
		}
	}
	//2.按照本地报单号撤单的情况
	else
	{
		if (!pOrderAction->UserOrderLocalID.isNull())
		{
			//检查是否有操作对象
 			CPreOrder* pTargetOrder=m_pDB->m_PreOrderFactory->findByUserIDAndUserOrderLocalID(pOrderAction->UserOrderLocalID,pOrderAction->FrontID,pOrderAction->SessionID);
			if (pTargetOrder!=NULL)
			{
				pOrderAction->linkPreOrder(pTargetOrder);
				//1.报单还没有被交易所确认，在preorder表中的情况
				//EXRISKG-595
				if (pOrderAction->InvestorID!=pTargetOrder->InvestorID)
				{
					REPORT_ERROR(ERROR_CANNOT_WITHDRAW_OTHERINVESTOR_ORDER);
				}			

				
				//!!此时强行将席位号改成跟报单席位号一样，以防撤单上去了，报单还没有上去
				//如果是同一会员撤自己的单，必须保证走一个席位
				//订单报入，但交易所尚未应答的情况，订单在预委托表中
				pOrderAction->ClientID=pTargetOrder->ClientID;
				//added by chengm 20160120 根据APIID获取ExchLink
				pOrderAction->APIID=pTargetOrder->APIID;
				if (pOrderAction->BrokerID==pTargetOrder->BrokerID)
				{
					pOrderAction->SeatID=pTargetOrder->SeatID;
					pOrderAction->ParticipantID=pTargetOrder->ParticipantID;
//					pOrderAction->BranchID=pTargetOrder->BranchID;
				}
				else
				{
					//client在交易所是唯一的，即使对应的是不同的会员
					CClientTradingID* pClntID=m_pDB->m_ClientTradingIDFactory->findByBrokerIDExchangeIDPartClientID(pOrderAction->BrokerID,pOrderAction->ExchangeID,pOrderAction->ParticipantID,pOrderAction->ClientID);
					if (pClntID==NULL)
					{
						pClntID =  m_pDB->m_ClientTradingIDFactory->findByBrokerIDExchangeIDPartClientID(pOrderAction->BrokerID,"Broker",pOrderAction->ParticipantID,pOrderAction->ClientID);
						if( NULL == pClntID )
						{
								REPORT_ERROR(ERROR_PART_CLIENT_NOTRELATED_INTHISEXCHANGE);
						}
					}
					pOrderAction->ParticipantID=pClntID->ParticipantID;
				}
				
				//必须将本地报单号附给OrderAction,wangwei,20130814
				pOrderAction->OrderLocalID=pTargetOrder->OrderLocalID;	
				pOrderAction->InstrumentID=pTargetOrder->InstrumentID;
			}
			//2.订单已经被交易所确认，在order表中
			else
			{
				COrder* pTargetOrder=m_pDB->m_OrderFactory->findByFrontIDSessionIDAndUserOrderLocalID(pOrderAction->FrontID,pOrderAction->SessionID,pOrderAction->UserOrderLocalID);
				if (pTargetOrder!=NULL)
				{
					//added by chengm 20160422  报单全部成交或者已撤单时不能重复撤单
					if (OS_AllTraded ==pTargetOrder->OrderStatus || 
						OS_Canceled == pTargetOrder->OrderStatus)
					{
						REPORT_ERROR(ERROR_ORDER_HAD_CANCELED_OR_ALLTRADED);
						return false;
					}
					//订单报入，且交易所已经应答的情况，订单在委托表中
					if (pOrderAction->InvestorID!=pTargetOrder->InvestorID)
					{
						REPORT_ERROR(ERROR_CANNOT_WITHDRAW_OTHERINVESTOR_ORDER);
					}
					pOrderAction->ClientID=pTargetOrder->ClientID;
					pOrderAction->OrderSysID=pTargetOrder->OrderSysID;
					//added by chengm 20160120 根据APIID获取ExchLink
					pOrderAction->APIID=pTargetOrder->APIID;
					//如果是同一会员撤自己的单，必须保证走一个席位
					if (pOrderAction->BrokerID==pTargetOrder->BrokerID)
					{
						pOrderAction->SeatID=pTargetOrder->SeatID;
						pOrderAction->ParticipantID=pTargetOrder->ParticipantID;
//						pOrderAction->BranchID=pTargetOrder->BranchID;
					}
					else
					{
						//client在交易所是唯一的，即使对应的是不同的会员
						CClientTradingID* pClntID=m_pDB->m_ClientTradingIDFactory->findByBrokerIDExchangeIDPartClientID(pOrderAction->BrokerID,pOrderAction->ExchangeID,pOrderAction->ParticipantID,pOrderAction->ClientID);
						if (pClntID==NULL)
						{
							REPORT_ERROR(ERROR_PART_CLIENT_NOTRELATED_INTHISEXCHANGE);
						}
						pOrderAction->ParticipantID=pClntID->ParticipantID;
					}
					pOrderAction->linkOrder(m_pDB->m_OrderFactory);//此时连接一次，后面HandleOrderAction好处理
					
					//必须将本地报单号附给OrderAction,wangwei,20130814
					pOrderAction->OrderLocalID=pTargetOrder->OrderLocalID;
					pOrderAction->InstrumentID=pTargetOrder->InstrumentID;

				}
				else
				{
					//委托表和预委托表中都没有，认为出错
					printf("撤单操作对象检查错误，没有找到UserOrderLocalID=[%s]对应的报单\n",pOrderAction->UserOrderLocalID.getValue());
					REPORT_ERROR(ERROR_ORDER_NOT_FOUND);
				}
			}
		}
		else
		{
			printf("撤单OrderLocalID和OrderSysID不能同时为空\n");
			REPORT_ERROR(ERROR_ORDERACTION_LOCALID_SYSID_BOTHBLANK);
		}
	}
	return true;
}

// bool CBaseCheck::SessionCheck(CWriteableOrderAction *pOrderAction,const TSessionRef &sessionRef)
// {
// 	pOrderAction->ActionSource=AS_User;
// 	return SessionCheck(pOrderAction->UserID,pOrderAction->BrokerID,sessionRef);
// }

bool CBaseCheck::FieldCheck(CWriteableOrderAction *pOrderAction)
{
	//只支持撤单
	if (pOrderAction->ActionFlag!=AF_Delete)
	{
		REPORT_ERROR(ERROR_FIELDERROR_ACTIONFLAG);
	}

	if (!pOrderAction->isValid())
	{
		REPORT_ERROR(ERROR_BAD_ORDER_ACTION_FIELD);	
	}
	return true;
}

bool CBaseCheck::RightCheck(CWriteableOrderAction *pOrderAction)
{
	///1.检查投资者是否存在
	if(m_pDB->m_InvestorFactory->findByBrokerIDInvestorID(pOrderAction->BrokerID,pOrderAction->InvestorID)==NULL)
	{
		REPORT_ERROR(ERROR_INVESTOR_NOT_FOUND);//客户找不到
	}
	
	///2.检查该User是否有对投资者投资的权限	
	if(m_pDB->m_UserInvestorFactory->findByBrokerIDUserIDInvestorID(pOrderAction->BrokerID,pOrderAction->UserID,pOrderAction->InvestorID)==NULL)
	{
		REPORT_ERROR(ERROR_USER_NORIGHT_WITHDRAW_THISORDER);//User没有对该客户下单的权限
	}
	//3.检查被撤销报单的investorid与这个是否一致
/*
	COrder* pOrder=pOrderAction->getOrder();
	if (pOrder!=NULL&&pOrder->InvestorID!=pOrderAction->InvestorID)
	{
		REPORT_ERROR(ERROR_CANNOT_WITHDRAW_OTHERINVESTOR_ORDER);
	}
*/
	return true;
}

// bool CBaseCheck::LocalIDCheck(CWriteableOrderAction *pOrderAction,CTransaction* pTransaction)
// {
// 	return LocalIDCheck(pOrderAction->BrokerID,pOrderAction->ExchangeID,pOrderAction->SeatID,pOrderAction->UserOrderActionLocalID,pOrderAction->UserID,pOrderAction->ActionLocalID,pTransaction);
// }

/************************************************************************/
/* 公共函数                                                                     */
/************************************************************************/

bool CBaseCheck::SessionCheck(CIPAddressType& IPAddress,CMacAddressType& MacAddress,CUserIDType& UserID,CBrokerIDType& BrokerID,const TSessionRef &sessionRef)
{
	//BrokerID为空，则立即报错返回
	if (BrokerID.isNull())
	{
		REPORT_ERROR(ERROR_ORDER_BROKERID_CANNOTBENULL);
	}

	CUserSession *pUserSession = m_pDB->m_UserSessionFactory->findBySessionIDFrontID(sessionRef.SessionID,sessionRef.FrontID);
	if ( NULL == pUserSession)
	{
		///找不到会话
		REPORT_EVENT(LOG_CRITICAL,"SessionCheck","基础检查错误，找不到会话\n");
		m_pErrorEngine->reportError(ERROR_SESSION_NOT_FOUND);
		return false;
	}
	else
	{
		UserID = pUserSession->UserID;
		BrokerID = pUserSession->BrokerID;
		IPAddress = pUserSession->IPAddress;
		MacAddress = pUserSession->MacAddress;
	}
	
	return true;
}

bool CBaseCheck::SysStatusCheck()
{
	///检查是否合约已经查询结束
	if (CBaseCheck::m_SystemStatus!=SS_InstrumentTradingDayDown)
	{
		printf("基础检查错误，数据同步尚未完成\n");
		REPORT_EVENT(LOG_EMERGENCY,"基础检查错误，数据同步尚未完成 ", "当前系统状态systemstatus:%c\n",CBaseCheck::m_SystemStatus.getValue());
		REPORT_ERROR(ERROR_EXCHANGE_DATA_NOT_SYNCHRONIZED);
	}
	return true;
}

bool CBaseCheck::LocalIDCheck(CBrokerIDType& BrokerID,CUserOrderLocalIDType& UserOrderLocalID,CUserIDType& UserID,const TSessionRef &sessionRef,CTransaction* pTransaction)
{
	///1.本地报单号不能为空
	if(UserOrderLocalID.isNull())
	{
		m_pErrorEngine->reportError(ERROR_FIELDERROR_USERORDERLOCALID);
		return false;
	}
	//2.查找本地号是否已经超出
	CMaxLocalID *pMaxLocalID=NULL;
	CWriteableMaxLocalID theMaxLocalID;
	pMaxLocalID=m_pDB->m_MaxLocalIDFactory->findByFrontIDSessionID(sessionRef.FrontID,sessionRef.SessionID);
	if (pMaxLocalID==NULL)
	{		
		m_pErrorEngine->reportError(ERROR_NOT_LOGIN_YET);
		return false;
	}
	else
	{
		if (pMaxLocalID->UserID != UserID)
		{
			m_pErrorEngine->reportError(ERROR_NOT_LOGINED_BY_THIS_USER);
			return false;
		}
		if (pMaxLocalID->MaxOrderLocalID > UserOrderLocalID)
		{
			m_pErrorEngine->reportError(ERROR_DUPLICATE_ORDER);
			return false;
		}
		m_pDB->m_MaxLocalIDFactory->retrieve(pMaxLocalID,&theMaxLocalID);
		theMaxLocalID.MaxOrderLocalID=UserOrderLocalID;
		///修改客户的本地报单号
		m_pDB->m_MaxLocalIDFactory->update(pMaxLocalID,&theMaxLocalID,pTransaction);
		return true;
	}
	
	return true;
}

//定义静态成员变量
CExchangeSeatOrderLocalIDMap CBaseCheck::m_ExchangeSeatOrderLocalIDMap;
CExPartSeatsMap CBaseCheck::m_ExPartSeatsMap;
CSystemStatusType CBaseCheck::m_SystemStatus=SS_DbOperational;
CInstrumentMap CBaseCheck::m_InstrumentMap;
CMemoryDB * CBaseCheck::m_pDB=NULL;

//登陆成功，记录本席位的最大本地报单号
void CBaseCheck::HandleSeatLoginSuccess(CLoginInfoField *pLoginInfo)
{
	if (pLoginInfo==NULL)
	{
		return;
	}
	//席位的本地报单号改为从席位表中取出,因为前面的HandleNotify::HandleSeatLoginSuccess已经修改好了本地报单号
	CSeat* pSeat=m_pDB->m_SeatFactory->findByExchangeIDParticipantIDSeatID(pLoginInfo->ExchangeID,pLoginInfo->ParticipantID,pLoginInfo->SeatID);

	if(pSeat==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"CBaseCheck::HandleSeatLoginSuccess找不到 ExchangeID=[%s],ParticipantID=[%s],SeatID=[%s] 对应的席位状态记录\n",pLoginInfo->ExchangeID.getValue(),pLoginInfo->ParticipantID.getValue(),pLoginInfo->SeatID.getValue());
		return;
	}
	COrderLocalIDType OrderLocalID=pSeat->OrderLocalID;

	CExchangeSeatIndex idx;
	idx.ExchangeID=pLoginInfo->ExchangeID;
	idx.SeatID=pLoginInfo->SeatID;
	CExchangeSeatOrderLocalIDMap::iterator it=m_ExchangeSeatOrderLocalIDMap.find(idx);
	if (it==m_ExchangeSeatOrderLocalIDMap.end())
	{		
		m_ExchangeSeatOrderLocalIDMap.insert(CExchangeSeatOrderLocalIDMap::value_type(idx,OrderLocalID));
	}
	else
	{
		it->second=OrderLocalID;
	}

	CExchangePartIndex indx;
	indx.ExchangeID=pLoginInfo->ExchangeID;
	indx.ParticipantID=pLoginInfo->ParticipantID;

	CExPartSeatsMap::iterator it1=m_ExPartSeatsMap.find(indx);
	if (it1==m_ExPartSeatsMap.end())
	{
		list<CSeatIDType>* pSeatList=new list<CSeatIDType>();
		pSeatList->push_back(idx.SeatID);
		m_ExPartSeatsMap.insert(CExPartSeatsMap::value_type(indx,pSeatList));
	}
	else
	{
		list<CSeatIDType>* pSeatList=it1->second;		
		pSeatList->push_back(idx.SeatID);
		pSeatList->unique();//去掉重复元素
	}
}

//跟交易所断线后，更新map中的信息
void CBaseCheck::HandleSeatDisconnected(CSeatField *pSeat)
{
	if (pSeat==NULL)
	{
		return;
	}
	CExchangeSeatIndex idx;
	idx.ExchangeID=pSeat->ExchangeID;
	idx.SeatID=pSeat->SeatID;
	CExchangeSeatOrderLocalIDMap::iterator it=m_ExchangeSeatOrderLocalIDMap.find(idx);
	if (it!=m_ExchangeSeatOrderLocalIDMap.end())
	{		
		m_ExchangeSeatOrderLocalIDMap.erase(idx);
	}
	
	CExchangePartIndex indx;
	indx.ExchangeID=pSeat->ExchangeID;
	indx.ParticipantID=pSeat->ParticipantID;

	/* 由索引(ParticipantID) 找到席位的链表(List)，从席位链表中删除断线的席位 */
	CExPartSeatsMap::iterator it1=m_ExPartSeatsMap.find(indx);
	if (it1!=m_ExPartSeatsMap.end())
	{
		list<CSeatIDType>* pSeatList=it1->second;
		pSeatList->remove(idx.SeatID);
	}
}

int CBaseCheck::m_initcount=0;

bool CBaseCheck::InvestorCheck(CWriteablePreOrder *pOrder,const TSessionRef &sessionRef,CTransaction* pTransaction)
{
	//获取InvestorID
	if (pOrder->InvestorID.isNull())
	{
		m_pErrorEngine->reportError(ERROR_INVESTORID_CANNOT_BE_BLANK);
		return false;
	}
	else
	{
		CUserInvestor *pUserInvestor = m_pDB->m_UserInvestorFactory->findByBrokerIDUserIDInvestorID(pOrder->BrokerID,
				pOrder->UserID, pOrder->InvestorID);
		if (pUserInvestor == NULL)
		{
			m_pErrorEngine->reportError(ERROR_USER_INVESTOR_NOT_RELATED);
			return false;
		}
	}

	return true;
}

