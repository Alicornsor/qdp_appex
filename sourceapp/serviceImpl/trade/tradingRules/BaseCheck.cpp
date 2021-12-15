/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file BaseCheck.cpp
///@briefʵ������CBaseCheck(�������������)
///@history 
///20121222	hwp		�������ļ�
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
		//printf("���������󣬱��ر����Ŵ���\n");
		REPORT_EVENT(LOG_CRITICAL,"OrderCheck","���������󣬱��ر����Ŵ���");
		return false;
	}
	
	///2.����User�Ƿ��ж�Ͷ����Ͷ�ʵ�Ȩ��	
	if(m_pDB->m_UserInvestorFactory->findByBrokerIDUserIDInvestorID(pOrder->BrokerID,pOrder->UserID,pOrder->InvestorID)==NULL)
	{
		REPORT_ERROR(ERROR_USER_INVESTOR_NOT_RELATED);//Userû�жԸÿͻ��µ���Ȩ��
		return false;
	}
	
	
	///���Ͷ�����˻��Ƿ����
	CInvestorAccount *pInvestorAccount = m_pDB->m_InvestorAccountFactory->findByBrokerIDInvestorID(pOrder->BrokerID,pOrder->InvestorID);
	if(pInvestorAccount == NULL)
	{
		REPORT_ERROR(ERROR_CAN_NOT_FIND_ACCOUNT);
		return false;
	}
	pOrder->getIndexPreOrder()->linkInvestorAccount(pInvestorAccount);
	
	//ͨ�����м��֮����ӽ����գ�����ʱ����Ϣ
	pOrder->TradingDay=getTradingDay(m_pDB);
	return true;
}

///�Ự���
// bool CBaseCheck::SessionCheck(CWriteablePreOrder *pOrder,const TSessionRef &sessionRef)
// {
// 	pOrder->OrderSource=OS_Participant;
// 	return SessionCheck(pOrder->UserID,pOrder->BrokerID,sessionRef);
// }

///Ȩ�޼��
bool CBaseCheck::RightCheck(CWriteablePreOrder *pOrder,CTransaction* pTransaction)
{
	CIndexPreOrder *pIndexPreOrder = pOrder->getIndexPreOrder();
	CClientTradingID *pClientTradingID = pIndexPreOrder->getClientTradingID();	
	if (unlikely(pClientTradingID->ClientRight!=TR_Allow))
	{
		REPORT_ERROR(ERROR_CLIENTID_CANNOT_TRADE);
		return false;
	}	
	///����ͻ���/��Ա��
	pOrder->ClientID=pIndexPreOrder->ClientID;
	pOrder->ParticipantID=pIndexPreOrder->ParticipantID;

	//�û���󱨵��ż��
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

	//UserID��������UserID��һ��ʱ,��Ҫ����У��UserID��InvestorID�Ĺ�ϵ
	if (unlikely(pIndexPreOrder->UserID != pOrder->UserID))
	{
		if(m_pDB->m_UserInvestorFactory->findByBrokerIDUserIDInvestorID(pOrder->BrokerID,pOrder->UserID,pOrder->InvestorID)==NULL)
		{
			m_pErrorEngine->reportError(ERROR_USER_INVESTOR_NOT_RELATED);//Userû�жԸÿͻ��µ���Ȩ��
			return false;
		}
	}


}	

//4.�ͻ����ر����ż��
// bool CBaseCheck::LocalIDCheck(CWriteablePreOrder *pOrder,CTransaction* pTransaction)
// {
// 	return LocalIDCheck(pOrder->BrokerID,pOrder->ExchangeID,pOrder->SeatID,pOrder->UserOrderLocalID,pOrder->UserID,pOrder->OrderLocalID,pTransaction);
// }	

bool CBaseCheck::VolumePriceCheck(CWriteablePreOrder *pOrder)
{
// 	///1.��鱨����Լ�Ƿ����
// 	CInstrument* pInstrument= pOrder->getInstrument();
// 	if (NULL == pInstrument)
// 	{
// 		CInstrumentMap::iterator it = m_InstrumentMap.find(pOrder->InstrumentID);	
// 		if (it!=m_InstrumentMap.end())
// 		{	// ��Լ���ϳ��ˣ��˷�֧�������е�����MAP����Ϊ�ա�
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
// 		///2.����Լ�Ƿ��ڽ���
// 		if(!pInstrument->IsTrading)
// 		{
// 			REPORT_ERROR(ERROR_BAD_INSTRUMENT_STATUS_FIELD);
// 		}
// 		
// 		///3.�޼۵��۸���
// 		///����󸡵������п��� 20130729 linxb
// 		if(pOrder->LimitPrice == DOUBLE_NaN)
// 		{
// 			REPORT_ERROR(ERROR_PRICE_OUT_OF_UPPER_BOUND);
// 		}	
// 	}
// 
// 
// 	///4.�����������
// 	if(OPT_LimitPrice == pOrder->OrderPriceType)
// 	{
// 		///�޼۵�
// 		if((pOrder->Volume < pInstrument->MinLimitOrderVolume) ||
// 			(pOrder->Volume > pInstrument->MaxLimitOrderVolume) )   //�ſ�������������������� 20130729 linxb
// 		{
// 			REPORT_ERROR(ERROR_INVALID_VOLUME);		
// 		}	
// 	}
// 	if(OPT_AnyPrice == pOrder->OrderPriceType || OPT_FiveLevelPrice == pOrder->OrderPriceType || OPT_BestPrice == pOrder->OrderPriceType)
// 	{
// 		///�м۵�
// 		if((pOrder->Volume < pInstrument->MinMarketOrderVolume) ||
// 			(pOrder->Volume > pInstrument->MaxMarketOrderVolume) )   // �ſ�������������������� 20130729 linxb
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
/*������麯��                                                                      */
/************************************************************************/

bool CBaseCheck::OrderActionCheck(CWriteableOrderAction *pOrderAction,const TSessionRef &sessionRef,CTransaction* pTransaction)
{
	//ϵͳ״̬���
// 	if(!SysStatusCheck())
// 	{
// 		return false;
// 	}
	//����Ŀ����
	if(!ActionTargetCheck(pOrderAction))
	{
		return false;
	}
// 	//ϯλ����
// 	if (!AssignSeat(pOrderAction))
// 	{
// 		return false;
// 	}

	//1.���Ự
	if(!SessionCheck(pOrderAction->IPAddress,pOrderAction->MacAddress,pOrderAction->UserID,pOrderAction->BrokerID,sessionRef))
	{
		return false;
	}
	
	//2.����ֶ�
/*	if(!FieldCheck(pOrderAction))
	{
		return false;			
	}*/
	//3.���ױ�����
/*	if(!RightCheck(pOrderAction))
	{
		return false;
	}*/
		
	//4.���ر����ż��
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
	//ͨ�����м��֮����ӽ����գ�����ʱ����Ϣ
	pOrderAction->CancelTime=getCurrentTime(m_pDB);
	return true;
}

//1.֧�ֱ��ر�����UserOrderLocalID����,����ָ���ǿͻ������Լ���ţ�ռ������ֶ�
//2.֧��OrderSysID����
//3.���UserOrderLocalID��OrderSysID����Ϊ�գ���OrderSysID���ȼ�Ϊ��,wangwei,20130503
//4.�������session��ί�б�session��һ�£�����ί�б�sessionid,chengm,20151220
bool CBaseCheck::ActionTargetCheck(CWriteableOrderAction *pOrderAction)
{
	//EXRISKG-595
	//����ʱinvestorid,UserID
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
	
	//1.����ϵͳ�����ų��������-wangwei,20130814
	if (!pOrderAction->OrderSysID.isNull())
	{
		//����Ƿ��в���Ŀ��
		const CWriteableOrder * pTargetOrder=pOrderAction->linkOrder(m_pDB->m_OrderFactory);
		if (pTargetOrder==NULL)
		{
			printf("�����������������û���ҵ�OrderSysID=[%s]��Ӧ�ı���\n",pOrderAction->OrderSysID.getValue());
			REPORT_ERROR(ERROR_ORDER_NOT_FOUND);
		}
		else
		{
			//added by chengm 20160422  ����ȫ���ɽ������ѳ���ʱ�����ظ�����
			if (OS_AllTraded ==pTargetOrder->OrderStatus || 
				OS_Canceled == pTargetOrder->OrderStatus)
			{
				REPORT_ERROR(ERROR_ORDER_HAD_CANCELED_OR_ALLTRADED);
				return false;
			}
			///2.����User�Ƿ��ж�Ͷ����Ͷ�ʵ�Ȩ��	
			if(m_pDB->m_UserInvestorFactory->findByBrokerIDUserIDInvestorID(pOrderAction->BrokerID,pOrderAction->UserID,pTargetOrder->InvestorID)==NULL)
			{
				REPORT_ERROR(ERROR_USER_INVESTOR_NOT_RELATED);//Userû�жԸÿͻ��µ���Ȩ��
			}

			pOrderAction->InvestorID = pTargetOrder->InvestorID;
			pOrderAction->ClientID=pTargetOrder->ClientID;
/*** SIR XLONG BEGIN ***/
			//���ͳ�������ʱ����InstrumentID����
			pOrderAction->InstrumentID=pTargetOrder->InstrumentID;
/*** SIR XLONG END ***/
			//added by chengm 20160120 ����APIID��ȡExchLink
			pOrderAction->APIID=pTargetOrder->APIID;
			pOrderAction->OrderLocalID=pTargetOrder->OrderLocalID;
			//�����ͬһ��Ա���Լ��ĵ������뱣֤��һ��ϯλ
			if (pOrderAction->BrokerID==pTargetOrder->BrokerID)
			{
				pOrderAction->SeatID=pTargetOrder->SeatID;
				pOrderAction->ParticipantID=pTargetOrder->ParticipantID;
//				pOrderAction->BranchID=pTargetOrder->BranchID;
			}
			else
			{
				//client�ڽ�������Ψһ�ģ���ʹ��Ӧ���ǲ�ͬ�Ļ�Ա
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
	//2.���ձ��ر����ų��������
	else
	{
		if (!pOrderAction->UserOrderLocalID.isNull())
		{
			//����Ƿ��в�������
 			CPreOrder* pTargetOrder=m_pDB->m_PreOrderFactory->findByUserIDAndUserOrderLocalID(pOrderAction->UserOrderLocalID,pOrderAction->FrontID,pOrderAction->SessionID);
			if (pTargetOrder!=NULL)
			{
				pOrderAction->linkPreOrder(pTargetOrder);
				//1.������û�б�������ȷ�ϣ���preorder���е����
				//EXRISKG-595
				if (pOrderAction->InvestorID!=pTargetOrder->InvestorID)
				{
					REPORT_ERROR(ERROR_CANNOT_WITHDRAW_OTHERINVESTOR_ORDER);
				}			

				
				//!!��ʱǿ�н�ϯλ�Ÿĳɸ�����ϯλ��һ�����Է�������ȥ�ˣ�������û����ȥ
				//�����ͬһ��Ա���Լ��ĵ������뱣֤��һ��ϯλ
				//�������룬����������δӦ��������������Ԥί�б���
				pOrderAction->ClientID=pTargetOrder->ClientID;
				//added by chengm 20160120 ����APIID��ȡExchLink
				pOrderAction->APIID=pTargetOrder->APIID;
				if (pOrderAction->BrokerID==pTargetOrder->BrokerID)
				{
					pOrderAction->SeatID=pTargetOrder->SeatID;
					pOrderAction->ParticipantID=pTargetOrder->ParticipantID;
//					pOrderAction->BranchID=pTargetOrder->BranchID;
				}
				else
				{
					//client�ڽ�������Ψһ�ģ���ʹ��Ӧ���ǲ�ͬ�Ļ�Ա
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
				
				//���뽫���ر����Ÿ���OrderAction,wangwei,20130814
				pOrderAction->OrderLocalID=pTargetOrder->OrderLocalID;	
				pOrderAction->InstrumentID=pTargetOrder->InstrumentID;
			}
			//2.�����Ѿ���������ȷ�ϣ���order����
			else
			{
				COrder* pTargetOrder=m_pDB->m_OrderFactory->findByFrontIDSessionIDAndUserOrderLocalID(pOrderAction->FrontID,pOrderAction->SessionID,pOrderAction->UserOrderLocalID);
				if (pTargetOrder!=NULL)
				{
					//added by chengm 20160422  ����ȫ���ɽ������ѳ���ʱ�����ظ�����
					if (OS_AllTraded ==pTargetOrder->OrderStatus || 
						OS_Canceled == pTargetOrder->OrderStatus)
					{
						REPORT_ERROR(ERROR_ORDER_HAD_CANCELED_OR_ALLTRADED);
						return false;
					}
					//�������룬�ҽ������Ѿ�Ӧ��������������ί�б���
					if (pOrderAction->InvestorID!=pTargetOrder->InvestorID)
					{
						REPORT_ERROR(ERROR_CANNOT_WITHDRAW_OTHERINVESTOR_ORDER);
					}
					pOrderAction->ClientID=pTargetOrder->ClientID;
					pOrderAction->OrderSysID=pTargetOrder->OrderSysID;
					//added by chengm 20160120 ����APIID��ȡExchLink
					pOrderAction->APIID=pTargetOrder->APIID;
					//�����ͬһ��Ա���Լ��ĵ������뱣֤��һ��ϯλ
					if (pOrderAction->BrokerID==pTargetOrder->BrokerID)
					{
						pOrderAction->SeatID=pTargetOrder->SeatID;
						pOrderAction->ParticipantID=pTargetOrder->ParticipantID;
//						pOrderAction->BranchID=pTargetOrder->BranchID;
					}
					else
					{
						//client�ڽ�������Ψһ�ģ���ʹ��Ӧ���ǲ�ͬ�Ļ�Ա
						CClientTradingID* pClntID=m_pDB->m_ClientTradingIDFactory->findByBrokerIDExchangeIDPartClientID(pOrderAction->BrokerID,pOrderAction->ExchangeID,pOrderAction->ParticipantID,pOrderAction->ClientID);
						if (pClntID==NULL)
						{
							REPORT_ERROR(ERROR_PART_CLIENT_NOTRELATED_INTHISEXCHANGE);
						}
						pOrderAction->ParticipantID=pClntID->ParticipantID;
					}
					pOrderAction->linkOrder(m_pDB->m_OrderFactory);//��ʱ����һ�Σ�����HandleOrderAction�ô���
					
					//���뽫���ر����Ÿ���OrderAction,wangwei,20130814
					pOrderAction->OrderLocalID=pTargetOrder->OrderLocalID;
					pOrderAction->InstrumentID=pTargetOrder->InstrumentID;

				}
				else
				{
					//ί�б��Ԥί�б��ж�û�У���Ϊ����
					printf("�����������������û���ҵ�UserOrderLocalID=[%s]��Ӧ�ı���\n",pOrderAction->UserOrderLocalID.getValue());
					REPORT_ERROR(ERROR_ORDER_NOT_FOUND);
				}
			}
		}
		else
		{
			printf("����OrderLocalID��OrderSysID����ͬʱΪ��\n");
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
	//ֻ֧�ֳ���
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
	///1.���Ͷ�����Ƿ����
	if(m_pDB->m_InvestorFactory->findByBrokerIDInvestorID(pOrderAction->BrokerID,pOrderAction->InvestorID)==NULL)
	{
		REPORT_ERROR(ERROR_INVESTOR_NOT_FOUND);//�ͻ��Ҳ���
	}
	
	///2.����User�Ƿ��ж�Ͷ����Ͷ�ʵ�Ȩ��	
	if(m_pDB->m_UserInvestorFactory->findByBrokerIDUserIDInvestorID(pOrderAction->BrokerID,pOrderAction->UserID,pOrderAction->InvestorID)==NULL)
	{
		REPORT_ERROR(ERROR_USER_NORIGHT_WITHDRAW_THISORDER);//Userû�жԸÿͻ��µ���Ȩ��
	}
	//3.��鱻����������investorid������Ƿ�һ��
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
/* ��������                                                                     */
/************************************************************************/

bool CBaseCheck::SessionCheck(CIPAddressType& IPAddress,CMacAddressType& MacAddress,CUserIDType& UserID,CBrokerIDType& BrokerID,const TSessionRef &sessionRef)
{
	//BrokerIDΪ�գ�������������
	if (BrokerID.isNull())
	{
		REPORT_ERROR(ERROR_ORDER_BROKERID_CANNOTBENULL);
	}

	CUserSession *pUserSession = m_pDB->m_UserSessionFactory->findBySessionIDFrontID(sessionRef.SessionID,sessionRef.FrontID);
	if ( NULL == pUserSession)
	{
		///�Ҳ����Ự
		REPORT_EVENT(LOG_CRITICAL,"SessionCheck","�����������Ҳ����Ự\n");
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
	///����Ƿ��Լ�Ѿ���ѯ����
	if (CBaseCheck::m_SystemStatus!=SS_InstrumentTradingDayDown)
	{
		printf("��������������ͬ����δ���\n");
		REPORT_EVENT(LOG_EMERGENCY,"��������������ͬ����δ��� ", "��ǰϵͳ״̬systemstatus:%c\n",CBaseCheck::m_SystemStatus.getValue());
		REPORT_ERROR(ERROR_EXCHANGE_DATA_NOT_SYNCHRONIZED);
	}
	return true;
}

bool CBaseCheck::LocalIDCheck(CBrokerIDType& BrokerID,CUserOrderLocalIDType& UserOrderLocalID,CUserIDType& UserID,const TSessionRef &sessionRef,CTransaction* pTransaction)
{
	///1.���ر����Ų���Ϊ��
	if(UserOrderLocalID.isNull())
	{
		m_pErrorEngine->reportError(ERROR_FIELDERROR_USERORDERLOCALID);
		return false;
	}
	//2.���ұ��غ��Ƿ��Ѿ�����
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
		///�޸Ŀͻ��ı��ر�����
		m_pDB->m_MaxLocalIDFactory->update(pMaxLocalID,&theMaxLocalID,pTransaction);
		return true;
	}
	
	return true;
}

//���徲̬��Ա����
CExchangeSeatOrderLocalIDMap CBaseCheck::m_ExchangeSeatOrderLocalIDMap;
CExPartSeatsMap CBaseCheck::m_ExPartSeatsMap;
CSystemStatusType CBaseCheck::m_SystemStatus=SS_DbOperational;
CInstrumentMap CBaseCheck::m_InstrumentMap;
CMemoryDB * CBaseCheck::m_pDB=NULL;

//��½�ɹ�����¼��ϯλ����󱾵ر�����
void CBaseCheck::HandleSeatLoginSuccess(CLoginInfoField *pLoginInfo)
{
	if (pLoginInfo==NULL)
	{
		return;
	}
	//ϯλ�ı��ر����Ÿ�Ϊ��ϯλ����ȡ��,��Ϊǰ���HandleNotify::HandleSeatLoginSuccess�Ѿ��޸ĺ��˱��ر�����
	CSeat* pSeat=m_pDB->m_SeatFactory->findByExchangeIDParticipantIDSeatID(pLoginInfo->ExchangeID,pLoginInfo->ParticipantID,pLoginInfo->SeatID);

	if(pSeat==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"CBaseCheck::HandleSeatLoginSuccess�Ҳ��� ExchangeID=[%s],ParticipantID=[%s],SeatID=[%s] ��Ӧ��ϯλ״̬��¼\n",pLoginInfo->ExchangeID.getValue(),pLoginInfo->ParticipantID.getValue(),pLoginInfo->SeatID.getValue());
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
		pSeatList->unique();//ȥ���ظ�Ԫ��
	}
}

//�����������ߺ󣬸���map�е���Ϣ
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

	/* ������(ParticipantID) �ҵ�ϯλ������(List)����ϯλ������ɾ�����ߵ�ϯλ */
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
	//��ȡInvestorID
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

