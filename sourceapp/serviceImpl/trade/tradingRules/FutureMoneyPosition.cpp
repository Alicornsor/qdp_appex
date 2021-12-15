#include "FutureMoneyPosition.h"

extern const CClientIDType defaultClientID;

CFutureMoneyPosition::CFutureMoneyPosition(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig):CMoneyPosition(pDB, pErrorEngine,pConfig)
{
}

CFutureMoneyPosition::~CFutureMoneyPosition()
{
}

///�����ʽ�
///@param	pPreOrder  ����
///@param	pMoneyField	��¼����ı�֤���������
///@param	pTransaction �����־
bool CFutureMoneyPosition::OrderInsertMoneyFrozen(CWriteablePreOrder* pPreOrder, CWriteableIndexPreOrder* pIndexPreOrder, CMoneyField* pMoneyField,CTransaction* pTransaction, bool bRedo)
{
	//���㶳��������
	if (pPreOrder->Direction == D_Buy)
	{
		pMoneyField->Fee = pPreOrder->Volume*pIndexPreOrder->OpenFeeAmt;
	}
	else
	{
		pMoneyField->Fee = pPreOrder->Volume*pIndexPreOrder->OffsetFeeAmt;
	}

	//���㶳�ᱣ֤��
	pMoneyField->FrozenMarginChanged=0.0;
	CMoneyType  frozenMargin=0.0;
	bool IsClosed = false;
	if (pIndexPreOrder->PositionType == PT_Gross)
	{
		CVolumeType LongPosition;
		CVolumeType ShortPosition;
		if (pIndexPreOrder->Position >=0)
		{
			LongPosition = pIndexPreOrder->Position + pIndexPreOrder->LongYdPosition;
			ShortPosition = pIndexPreOrder->ShortYdPosition;
		}
		else
		{
			LongPosition = pIndexPreOrder->LongYdPosition;
			ShortPosition = -1 *pIndexPreOrder->Position + pIndexPreOrder->ShortYdPosition;
		}
		
		if (pPreOrder->Direction == D_Buy)
		{
			LongPosition += (pIndexPreOrder->LongFrozen + pPreOrder->Volume);
			ShortPosition += pIndexPreOrder->ShortFrozen;
		}
		else
		{
			ShortPosition += (pIndexPreOrder->ShortFrozen + pPreOrder->Volume);
			LongPosition += pIndexPreOrder->LongFrozen;
		}
		frozenMargin = MAX(LongPosition*pIndexPreOrder->LongMarginAmt,ShortPosition*pIndexPreOrder->ShortMarginAmt);
		frozenMargin -= pIndexPreOrder->ActualMargin;
		if (frozenMargin <= 0.0)
		{
			frozenMargin=0.0;
		}
		if (frozenMargin > pIndexPreOrder->ActualFrozenMargin)
		{
			pMoneyField->FrozenMarginChanged = frozenMargin - pIndexPreOrder->ActualFrozenMargin;
			pIndexPreOrder->ActualFrozenMargin = frozenMargin;
		}
		else
		{
			pMoneyField->FrozenMarginChanged = 0.0;
		}	
	}
	else
	{
		//modified by chengm 20180529 kgiҪ�󾻳ֲֿͻ���clientidд��businessunit��
		pPreOrder->BusinessUnit = pIndexPreOrder->ClientID.getValue();
		CVolumeType Position=0;
		CMoneyType  frozenMargin=0.0;
		if (pPreOrder->Direction == D_Buy)
		{
			Position = pIndexPreOrder->Position + pIndexPreOrder->LongFrozen + pPreOrder->Volume;
		}
		else
		{
			Position = pIndexPreOrder->Position - pIndexPreOrder->ShortFrozen - pPreOrder->Volume;
		}
		if (pIndexPreOrder->Position * Position >0 && fabs(pIndexPreOrder->Position.getValue()) > fabs(Position.getValue()) 
			|| Position ==0)
		{
			IsClosed=true;
		}

		if (Position >0)
		{
			frozenMargin = 	Position*pIndexPreOrder->LongMarginAmt;
		}
		else
		{
			frozenMargin = 	-1*Position*pIndexPreOrder->ShortMarginAmt;
		}
		frozenMargin -= pIndexPreOrder->ActualMargin;
		//�ó�ʵ�ʶ��ᱣ֤��
		if (frozenMargin <0.0)
		{
			frozenMargin = 0.0;
		}
		if (pPreOrder->Direction == D_Buy)
		{
			pMoneyField->FrozenMarginChanged += (frozenMargin -pIndexPreOrder->LongFrozenMargin);
			pIndexPreOrder->LongFrozenMargin = frozenMargin;
		}
		else
		{
			pMoneyField->FrozenMarginChanged += (frozenMargin -pIndexPreOrder->ShortFrozenMargin);
			pIndexPreOrder->ShortFrozenMargin = frozenMargin;
		}
		pIndexPreOrder->ActualFrozenMargin = pIndexPreOrder->LongFrozenMargin + pIndexPreOrder->ShortFrozenMargin;
	}	

	CMoneyType preFrozenMoney = pMoneyField->FrozenMarginChanged + pMoneyField->Fee;
	CInvestorAccount* pInvestorAccount = pIndexPreOrder->getInvestorAccount();
	if(pInvestorAccount == NULL)
	{
		m_pErrorEngine->reportError(ERROR_CAN_NOT_FIND_ACCOUNT);
		return false;
	}
	if(pIndexPreOrder->getClientTradingID()->CheckAccount && !bRedo &&!IsClosed && pInvestorAccount->Available < preFrozenMoney )  // �����ʽ����Ԥ���ᱣ֤��
	{
		//�ʽ���
		m_pErrorEngine->reportError(ERROR_INSUFFICIENT_MONEY);
		return false;
	}
	return true;	
}


///���ⶳ�ʽ�
///@param   pInvestorAccount ��Ӧ�ʽ��˻�ָ��
///@param	pInputOrder  �����ʹ��ⶳ�ʽ�
///@param	pMoney	���ڶ���ı�֤���������
bool CFutureMoneyPosition::MoneyUnFrozen(CPreOrder* pPreOrder,CTransaction* pTransaction)
{
	CVolumeType freeVolume = pPreOrder->Volume - pPreOrder->VolumeTraded;	
	CMoneyField theMoneyField;
	memset(&theMoneyField,0,sizeof(CMoneyField));
	theMoneyField.Fee = pPreOrder->FrozenFee * freeVolume / pPreOrder->Volume;
	CIndexPreOrder *pIndexPreOrder = pPreOrder->getIndexPreOrder();
	CWriteableIndexPreOrder wtbIndexPreOrder;
	m_pDB->m_IndexPreOrderFactory->retrieve(pIndexPreOrder,&wtbIndexPreOrder);

	//�����ͷŶ��ᱣ֤��
	theMoneyField.FrozenMarginChanged=0.0;
	CMoneyType  frozenMargin=0.0;
	if (pIndexPreOrder->PositionType == PT_Gross)
	{
		CVolumeType LongPosition;
		CVolumeType ShortPosition;
		if (pIndexPreOrder->Position >=0)
		{
			LongPosition = pIndexPreOrder->Position + pIndexPreOrder->LongYdPosition;
			ShortPosition = pIndexPreOrder->ShortYdPosition;
		}
		else
		{
			LongPosition = pIndexPreOrder->LongYdPosition;
			ShortPosition = -1 *pIndexPreOrder->Position + pIndexPreOrder->ShortYdPosition;
		}
		
		if (pPreOrder->Direction == D_Buy)
		{
			LongPosition += (pIndexPreOrder->LongFrozen - freeVolume);
			ShortPosition += pIndexPreOrder->ShortFrozen;
		}
		else
		{
			ShortPosition += (pIndexPreOrder->ShortFrozen - freeVolume);
			LongPosition += pIndexPreOrder->LongFrozen;
		}
		frozenMargin = MAX(LongPosition*pIndexPreOrder->LongMarginAmt,ShortPosition*pIndexPreOrder->ShortMarginAmt);
		frozenMargin -= pIndexPreOrder->ActualMargin;
		if (frozenMargin < 0.0)
		{
			frozenMargin = 0.0;
		}
		theMoneyField.FrozenMarginChanged = (frozenMargin - pIndexPreOrder->ActualFrozenMargin);
		wtbIndexPreOrder.ActualFrozenMargin = frozenMargin;
	}
	else
	{
		CVolumeType Position=0;
		CMoneyType  frozenMargin=0.0;
		if (pPreOrder->Direction == D_Buy)
		{
			Position = pIndexPreOrder->Position + wtbIndexPreOrder.LongFrozen - freeVolume;
		}
		else
		{
			Position = pIndexPreOrder->Position - wtbIndexPreOrder.ShortFrozen + freeVolume;
		}
		if (Position >0)
		{
			frozenMargin = 	Position*pIndexPreOrder->LongMarginAmt;
		}
		else
		{
			frozenMargin = 	-1*Position*pIndexPreOrder->ShortMarginAmt;
		}
		frozenMargin -= pIndexPreOrder->ActualMargin;
		//�ó�ʵ�ʶ��ᱣ֤��
		if (frozenMargin <0.0)
		{
			frozenMargin = 0.0;
		}
		if (pPreOrder->Direction == D_Buy)
		{
			theMoneyField.FrozenMarginChanged += (frozenMargin -pIndexPreOrder->LongFrozenMargin);
			wtbIndexPreOrder.LongFrozenMargin = frozenMargin;
		}
		else
		{
			theMoneyField.FrozenMarginChanged += (frozenMargin -pIndexPreOrder->ShortFrozenMargin);
			wtbIndexPreOrder.ShortFrozenMargin = frozenMargin;
		}
		wtbIndexPreOrder.ActualFrozenMargin = wtbIndexPreOrder.LongFrozenMargin + wtbIndexPreOrder.ShortFrozenMargin;
	}
	

	CInvestorAccount* pInvestorAccount = pIndexPreOrder->getInvestorAccount();
	CWriteableInvestorAccount theWriteableInvestorAccount;
	m_pDB->m_InvestorAccountFactory->retrieve(pInvestorAccount,&theWriteableInvestorAccount);

	//����ʵʱ�ʽ��
	theWriteableInvestorAccount.FrozenFee  -= theMoneyField.Fee;
	theWriteableInvestorAccount.FrozenMargin += theMoneyField.FrozenMarginChanged;
	
	//���½���׼����ͺͿ����ʽ�
	CFutureMoneyPosition::ChangeBalanceAndAvailable(&theWriteableInvestorAccount);
	m_pDB->m_InvestorAccountFactory->update(pInvestorAccount,&theWriteableInvestorAccount,pTransaction);
	m_pDB->m_IndexPreOrderFactory->update(pIndexPreOrder,&wtbIndexPreOrder,pTransaction);	
	return true;
}


//�����ⶳ�ʽ�  
///@param   pInvestorAccount ��Ӧ�ʽ��˻�ָ��
///@param   pOrder     ������Ӧ�Ķ���   
///@param	pOrderActionField  ����Ӧ����
///@param	pMoney	���ڶ���ı�֤���������
bool CFutureMoneyPosition::MoneyUnFrozen(COrder* pOrder,CTransaction* pTransaction)
{
	CVolumeType freeVolume = pOrder->Volume - pOrder->VolumeTraded;
	if (pOrder->TimeCondition == TC_IOC)
	{
		freeVolume = pOrder->CancleVolume;
	}

	CMoneyField theMoneyField;
	memset(&theMoneyField,0,sizeof(CMoneyField));
	theMoneyField.Fee = pOrder->FrozenFee * freeVolume / pOrder->Volume;
	CIndexPreOrder *pIndexPreOrder = pOrder->getIndexPreOrder();
	CWriteableIndexPreOrder wtbIndexPreOrder;
	m_pDB->m_IndexPreOrderFactory->retrieve(pIndexPreOrder,&wtbIndexPreOrder);
	
	//�����ͷŶ��ᱣ֤��
	theMoneyField.FrozenMarginChanged=0.0;
	CMoneyType  frozenMargin=0.0;
	if (pIndexPreOrder->PositionType == PT_Gross)
	{
		CVolumeType LongPosition;
		CVolumeType ShortPosition;
		if (pIndexPreOrder->Position >=0)
		{
			LongPosition = pIndexPreOrder->Position + pIndexPreOrder->LongYdPosition;
			ShortPosition = pIndexPreOrder->ShortYdPosition;
		}
		else
		{
			LongPosition = pIndexPreOrder->LongYdPosition;
			ShortPosition = -1 *pIndexPreOrder->Position + pIndexPreOrder->ShortYdPosition;
		}
		
		if (pOrder->Direction == D_Buy)
		{
			LongPosition += (pIndexPreOrder->LongFrozen - freeVolume);
			ShortPosition += pIndexPreOrder->ShortFrozen;
		}
		else
		{
			ShortPosition += (pIndexPreOrder->ShortFrozen - freeVolume);
			LongPosition += pIndexPreOrder->LongFrozen;
		}
		frozenMargin = MAX(LongPosition*pIndexPreOrder->LongMarginAmt,ShortPosition*pIndexPreOrder->ShortMarginAmt);
		frozenMargin -= pIndexPreOrder->ActualMargin;
		if (frozenMargin < 0.0)
		{
			frozenMargin = 0.0;
		}
		theMoneyField.FrozenMarginChanged = (frozenMargin - pIndexPreOrder->ActualFrozenMargin);
		wtbIndexPreOrder.ActualFrozenMargin = frozenMargin;
	}
	else
	{
		CVolumeType Position=0;
		CMoneyType  frozenMargin=0.0;
		if (pOrder->Direction == D_Buy)
		{
			Position = pIndexPreOrder->Position + wtbIndexPreOrder.LongFrozen - freeVolume;
		}
		else
		{
			Position = pIndexPreOrder->Position - wtbIndexPreOrder.ShortFrozen + freeVolume;
		}
		if (Position >0)
		{
			frozenMargin = 	Position*pIndexPreOrder->LongMarginAmt;
		}
		else
		{
			frozenMargin = 	-1*Position*pIndexPreOrder->ShortMarginAmt;
		}
		frozenMargin -= pIndexPreOrder->ActualMargin;
		//�ó�ʵ�ʶ��ᱣ֤��
		if (frozenMargin <0.0)
		{
			frozenMargin = 0.0;
		}
		if (pOrder->Direction == D_Buy)
		{
			theMoneyField.FrozenMarginChanged += (frozenMargin -pIndexPreOrder->LongFrozenMargin);
			wtbIndexPreOrder.LongFrozenMargin = frozenMargin;
		}
		else
		{
			theMoneyField.FrozenMarginChanged += (frozenMargin -pIndexPreOrder->ShortFrozenMargin);
			wtbIndexPreOrder.ShortFrozenMargin = frozenMargin;
		}
		wtbIndexPreOrder.ActualFrozenMargin = wtbIndexPreOrder.LongFrozenMargin + wtbIndexPreOrder.ShortFrozenMargin;
	}
	
	
	CInvestorAccount* pInvestorAccount = pIndexPreOrder->getInvestorAccount();
	CWriteableInvestorAccount theWriteableInvestorAccount;
	m_pDB->m_InvestorAccountFactory->retrieve(pInvestorAccount,&theWriteableInvestorAccount);
	
	//����ʵʱ�ʽ��
	theWriteableInvestorAccount.FrozenFee  -= theMoneyField.Fee;
	theWriteableInvestorAccount.FrozenMargin += theMoneyField.FrozenMarginChanged;
	
	//���½���׼����ͺͿ����ʽ�
	CFutureMoneyPosition::ChangeBalanceAndAvailable(&theWriteableInvestorAccount);
	m_pDB->m_InvestorAccountFactory->update(pInvestorAccount,&theWriteableInvestorAccount,pTransaction);
	m_pDB->m_IndexPreOrderFactory->update(pIndexPreOrder,&wtbIndexPreOrder,pTransaction);	
	return true;
}

///��������ֲ֡�ƽ�ֶ���ƽ��
///@param	pInvestorPosition  ��Ӧ�ֲ�
///@param	pInputOrderField  ������
///@param	pTransaction �����־
bool CFutureMoneyPosition::OrderInsertPositionFrozen(CWriteablePreOrder* pPreOrder, CWriteableIndexPreOrder* pIndexPreOrder,CMoneyField* pMoneyField,CTransaction* pTransaction, bool bRedo)
{
	bool bSuccess = false;
	CPositionTypeType PositionType = pIndexPreOrder->PositionType;

	//��Լ�ֲ��޶���
	CVolumeType Position;
	if (pIndexPreOrder->LongPositionLimit>0 && pPreOrder->Direction == D_Buy)
	{
		if (PositionType == PT_Gross)
		{
			if (pIndexPreOrder->Position >=0)
			{
				Position = pIndexPreOrder->LongYdPosition + pIndexPreOrder->Position + pIndexPreOrder->LongFrozen + pPreOrder->Volume;
			}
			else
			{
				Position = pIndexPreOrder->LongYdPosition + pIndexPreOrder->LongFrozen + pPreOrder->Volume;
			}
			
		}
		else
		{
			Position = pIndexPreOrder->Position + pIndexPreOrder->LongFrozen + pPreOrder->Volume;
		}
		if (!bRedo && Position > pIndexPreOrder->LongPositionLimit)
		{
			REPORT_EVENT(LOG_DEBUG, "Position exceed clientlimit in OrderInsertPositionFrozen ", " InvestorID:%s,UserOrderLocalID:%s,Direction:%c,FrozenPosition:%d,Position:%d,LongPosiLimit:%d",\
				pPreOrder->InvestorID.getValue(),pPreOrder->UserOrderLocalID.getValue(),pPreOrder->Direction.getValue(),pIndexPreOrder->LongFrozen.getValue(),pIndexPreOrder->Position.getValue(),pIndexPreOrder->LongPositionLimit.getValue());
			m_pErrorEngine->reportError(ERROR_CLIENT_POSITION_LIMIT_EXCEED);
			return false;
		}
	}
	else if (pIndexPreOrder->ShortPositionLimit>0 && pPreOrder->Direction == D_Sell)
	{
		if (PositionType == PT_Gross)
		{
			if (pIndexPreOrder->Position <0)
			{
				Position = pIndexPreOrder->ShortYdPosition - pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen + pPreOrder->Volume;
			}
			else
			{
				Position = pIndexPreOrder->ShortYdPosition + pIndexPreOrder->ShortFrozen + pPreOrder->Volume;
			}
			
		}
		else
		{
			Position = -1 * pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen + pPreOrder->Volume;
		}
		if (!bRedo && Position > pIndexPreOrder->ShortPositionLimit)
		{
			REPORT_EVENT(LOG_DEBUG, "Position exceed clientlimit in OrderInsertPositionFrozen ", " InvestorID:%s,UserOrderLocalID:%s,Direction:%c,FrozenClosing:%d,Position:%d,ShortPosiLimit:%d",\
				pPreOrder->InvestorID.getValue(),pPreOrder->UserOrderLocalID.getValue(),pPreOrder->Direction.getValue(),pIndexPreOrder->ShortFrozen.getValue(),pIndexPreOrder->Position.getValue(),pIndexPreOrder->ShortPositionLimit.getValue());
			m_pErrorEngine->reportError(ERROR_CLIENT_POSITION_LIMIT_EXCEED);
			return false;
		}
	}

	//��ȡƷ�ֲֳ��޶�
	CInvestorPositionLimit *pVarietyPosiLimit = pIndexPreOrder->getVarietyPositionLimit();
	if (pVarietyPosiLimit != NULL)
	{
		CWriteableInvestorPositionLimit theWritableVarietyLimit;
		m_pDB->m_InvestorPositionLimitFactory->retrieve(pVarietyPosiLimit,&theWritableVarietyLimit);
		CVolumeType LongPosition=0;
		CVolumeType ShortPosition=0;
		CVolumeType LastLongPosition=0;
		CVolumeType LastShortPosition=0;
		if (pPreOrder->Direction == D_Buy)
		{
			if (PositionType == PT_Gross)
			{
				if (pIndexPreOrder->Position >=0 )
				{
					LastLongPosition = pIndexPreOrder->LongYdPosition + pIndexPreOrder->Position + pIndexPreOrder->LongFrozen;
					LongPosition = pIndexPreOrder->LongYdPosition + pIndexPreOrder->Position + pIndexPreOrder->LongFrozen + pPreOrder->Volume;
				}
				else
				{
					LastLongPosition = pIndexPreOrder->LongYdPosition + pIndexPreOrder->LongFrozen;
					LongPosition = pIndexPreOrder->LongYdPosition + pIndexPreOrder->LongFrozen + pPreOrder->Volume;
				}				
				if (LastLongPosition <0)
				{
					LastLongPosition=0;
				}
				if (LongPosition <0)
				{
					LongPosition =0;
				}
				theWritableVarietyLimit.LongPosition += (LongPosition - LastLongPosition);
			}
			else
			{
				LastLongPosition = pIndexPreOrder->Position + pIndexPreOrder->LongFrozen;
				if (LastLongPosition <0)
				{
					LastLongPosition=0;
				}
				LongPosition = pIndexPreOrder->Position + pIndexPreOrder->LongFrozen + pPreOrder->Volume;
				if (LongPosition <0)
				{
					LongPosition =0;
				}
				theWritableVarietyLimit.LongPosition += (LongPosition - LastLongPosition);
			}
			if (!bRedo && pVarietyPosiLimit->LongPosiLimit>0 && theWritableVarietyLimit.LongPosition > pVarietyPosiLimit->LongPosiLimit)
			{
				REPORT_EVENT(LOG_DEBUG, "VarietyPosition exceed clientlimit in OrderInsertPositionFrozen ", " InvestorID:%s,UserOrderLocalID:%s,Direction:%c,LongPositionChange:%d,OldLongPosition:%d,LongPosition:%d,LongPosiLimit:%d",\
					pPreOrder->InvestorID.getValue(),pPreOrder->UserOrderLocalID.getValue(),pPreOrder->Direction.getValue(),LongPosition.getValue() - LastLongPosition.getValue(),pVarietyPosiLimit->LongPosition.getValue(),theWritableVarietyLimit.LongPosition.getValue(),pVarietyPosiLimit->LongPosiLimit.getValue());
				m_pErrorEngine->reportError(ERROR_CLIENT_POSITION_LIMIT_EXCEED);
				return false;
			}
		}
		else
		{
			if (PositionType == PT_Gross)
			{
				if (pIndexPreOrder->Position <0 )
				{
					LastShortPosition = pIndexPreOrder->ShortYdPosition - pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen;
					ShortPosition = pIndexPreOrder->ShortYdPosition - pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen + pPreOrder->Volume;
				}
				else
				{
					LastShortPosition = pIndexPreOrder->ShortYdPosition + pIndexPreOrder->ShortFrozen;
					ShortPosition = pIndexPreOrder->ShortYdPosition + pIndexPreOrder->ShortFrozen + pPreOrder->Volume;
				}				
				if (LastShortPosition <0)
				{
					LastShortPosition=0;
				}
				if (ShortPosition <0)
				{
					ShortPosition =0;
				}
				theWritableVarietyLimit.ShortPosition += (ShortPosition - LastShortPosition);				
			}
			else
			{
				LastShortPosition = -1 *pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen;
				if (LastShortPosition <0)
				{
					LastShortPosition=0;
				}
				ShortPosition = -1 *pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen + pPreOrder->Volume;
				if (ShortPosition <0)
				{
					ShortPosition =0;
				}
				theWritableVarietyLimit.ShortPosition += (ShortPosition - LastShortPosition);
			}
			if (!bRedo && pVarietyPosiLimit->ShortPosiLimit>0 && theWritableVarietyLimit.ShortPosition > pVarietyPosiLimit->ShortPosiLimit)
			{
				REPORT_EVENT(LOG_DEBUG, "VarietyPosition exceed clientlimit in OrderInsertPositionFrozen ", " InvestorID:%s,UserOrderLocalID:%s,Direction:%c,ShortPositionChange:%d,OldShortPosition:%d,ShortPosition:%d,ShortPosiLimit:%d",\
					pPreOrder->InvestorID.getValue(),pPreOrder->UserOrderLocalID.getValue(),pPreOrder->Direction.getValue(),ShortPosition.getValue() - LastShortPosition.getValue(),pVarietyPosiLimit->ShortPosition.getValue(),\
					theWritableVarietyLimit.ShortPosition.getValue(),pVarietyPosiLimit->ShortPosiLimit.getValue());
				m_pErrorEngine->reportError(ERROR_CLIENT_POSITION_LIMIT_EXCEED);
				return false;
			}
		}
		m_pDB->m_InvestorPositionLimitFactory->update(pVarietyPosiLimit,&theWritableVarietyLimit,pTransaction);
	}

	if (pPreOrder->Direction == D_Buy)
	{
		pIndexPreOrder->LongFrozen += pPreOrder->Volume;
	}
	else
	{
		pIndexPreOrder->ShortFrozen += pPreOrder->Volume;
	}

#ifdef APP_QQUERY
	CDirectionType Direction;
	if (pIndexPreOrder->PositionType == PT_Net)
	{
		Direction = D_Net;
	}
	else
	{
		Direction = pPreOrder->Direction;
	}
	CInvestorPosition *pInvestorPosition = m_pDB->m_InvestorPositionFactory->findByBrkIDExIDInvIDInsDirHed(pPreOrder->BrokerID,pPreOrder->ExchangeID,\
			pPreOrder->InvestorID,pPreOrder->InstrumentID,Direction,pPreOrder->HedgeFlag);
	CWriteableInvestorPosition theWritableInvestorPosition;
	if (pInvestorPosition == NULL)
	{
		theWritableInvestorPosition.init();
		theWritableInvestorPosition.BrokerID         = pPreOrder->BrokerID;
		theWritableInvestorPosition.InvestorID       = pPreOrder->InvestorID;
		theWritableInvestorPosition.HedgeFlag        = pPreOrder->HedgeFlag;
		theWritableInvestorPosition.ParticipantID    = pPreOrder->ParticipantID;
		theWritableInvestorPosition.ClientID         = pPreOrder->ClientID;
		theWritableInvestorPosition.AccountID        = pPreOrder->AccountID;
		theWritableInvestorPosition.ExchangeID       = pPreOrder->ExchangeID;
		theWritableInvestorPosition.InstrumentID     = pPreOrder->InstrumentID;	
		theWritableInvestorPosition.LastOrderLocalID =pPreOrder->OrderLocalID;
		theWritableInvestorPosition.Currency	     = pIndexPreOrder->Currency; //????
		theWritableInvestorPosition.Direction	     = Direction;
		theWritableInvestorPosition.FrozenPosition   = 0;
		theWritableInvestorPosition.FrozenClosing    = 0;
		theWritableInvestorPosition.HedgeFlag        = pPreOrder->HedgeFlag;
	}
	else
	{
		m_pDB->m_InvestorPositionFactory->retrieve(pInvestorPosition,&theWritableInvestorPosition);
	}
	CMoneyType FrozenMargin;
	if (pPreOrder->Direction == D_Buy)
	{
		theWritableInvestorPosition.FrozenPosition += pPreOrder->Volume;
		if (pIndexPreOrder->PositionType == PT_Net)
		{
			theWritableInvestorPosition.UsedMargin = pIndexPreOrder->ActualMargin;
			theWritableInvestorPosition.FrozenMargin = pIndexPreOrder->ActualFrozenMargin;
		}
		else
		{
			theWritableInvestorPosition.UsedMargin = theWritableInvestorPosition.Position * pIndexPreOrder->LongMarginAmt;
			if (pIndexPreOrder->Position >= 0)
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition + pIndexPreOrder->Position+theWritableInvestorPosition.FrozenPosition) *\
							pIndexPreOrder->LongMarginAmt;
			}
			else
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition + theWritableInvestorPosition.FrozenPosition) * pIndexPreOrder->LongMarginAmt;
			}

			FrozenMargin -= pIndexPreOrder->ActualMargin;
			if (FrozenMargin <0.0)
			{
				FrozenMargin =0.0;
			}
			theWritableInvestorPosition.FrozenMargin = FrozenMargin;
		}
	}
	else
	{
		if (pIndexPreOrder->PositionType == PT_Net)
		{
			theWritableInvestorPosition.FrozenClosing += pPreOrder->Volume;
			theWritableInvestorPosition.UsedMargin = pIndexPreOrder->ActualMargin;
			theWritableInvestorPosition.FrozenMargin = pIndexPreOrder->ActualFrozenMargin;
		}
		else
		{
			theWritableInvestorPosition.FrozenPosition += pPreOrder->Volume;
			theWritableInvestorPosition.UsedMargin = theWritableInvestorPosition.Position * pIndexPreOrder->ShortMarginAmt;
			if (pIndexPreOrder->Position < 0)
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition - pIndexPreOrder->Position+theWritableInvestorPosition.FrozenPosition) *\
					pIndexPreOrder->ShortMarginAmt;
			}
			else
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition + theWritableInvestorPosition.FrozenPosition) * pIndexPreOrder->LongMarginAmt;
			}
			FrozenMargin -= pIndexPreOrder->ActualMargin;
			if (FrozenMargin <0.0)
			{
				FrozenMargin =0.0;
			}
			theWritableInvestorPosition.FrozenMargin = FrozenMargin;
		}
	}
	
	theWritableInvestorPosition.LastOrderLocalID=pPreOrder->OrderLocalID;
	CInvestorPosition *ppInvestorPosition = m_pDB->m_InvestorPositionFactory->addOrUpdate(pInvestorPosition,&theWritableInvestorPosition,pTransaction);
	pPreOrder->linkInvestorPosition(ppInvestorPosition);
#endif

	return true;
}


///���ͷŶ���ֲ�
///@paramp  pPreOrder   ����
//@param	pTransaction �����־
bool CFutureMoneyPosition::PositionUnFrozen(CPreOrder* pPreOrder,CTransaction* pTransaction)
{
	bool bSuccess = false;
	CIndexPreOrder *pIndexPreOrder = pPreOrder->getIndexPreOrder();
	CWriteableIndexPreOrder wtbIndexPreOrder;
	m_pDB->m_IndexPreOrderFactory->retrieve(pIndexPreOrder,&wtbIndexPreOrder);
	CPositionTypeType PositionType = pIndexPreOrder->PositionType;
	
	CVolumeType freeVolume = pPreOrder->Volume - pPreOrder->VolumeTraded;
	//��ȡƷ���޶�
	CInvestorPositionLimit *pVarietyPosiLimit = pIndexPreOrder->getVarietyPositionLimit();
	if (pVarietyPosiLimit != NULL)
	{
		CWriteableInvestorPositionLimit theWritableVarietyLimit;
		m_pDB->m_InvestorPositionLimitFactory->retrieve(pVarietyPosiLimit,&theWritableVarietyLimit);
		CVolumeType LongPosition=0;
		CVolumeType ShortPosition=0;
		CVolumeType LastLongPosition=0;
		CVolumeType LastShortPosition=0;
		if (pPreOrder->Direction == D_Buy)
		{
			if (PositionType == PT_Gross)
			{
				if (pIndexPreOrder->Position >=0)
				{
					LastLongPosition = pIndexPreOrder->LongYdPosition + pIndexPreOrder->Position + pIndexPreOrder->LongFrozen;
					LongPosition = pIndexPreOrder->LongYdPosition + pIndexPreOrder->Position + pIndexPreOrder->LongFrozen - freeVolume;
				}
				else
				{
					LastLongPosition = pIndexPreOrder->LongYdPosition + pIndexPreOrder->LongFrozen;
					LongPosition = pIndexPreOrder->LongYdPosition + pIndexPreOrder->LongFrozen - freeVolume;
				}

				if (LastLongPosition <0)
				{
					LastLongPosition=0;
				}
				if (LongPosition <0)
				{
					LongPosition =0;
				}
				theWritableVarietyLimit.LongPosition += (LongPosition - LastLongPosition);
			}
			else
			{
				LastLongPosition = pIndexPreOrder->Position + pIndexPreOrder->LongFrozen;
				if (LastLongPosition <0)
				{
					LastLongPosition=0;
				}
				LongPosition = pIndexPreOrder->Position + pIndexPreOrder->LongFrozen - freeVolume;
				if (LongPosition <0)
				{
					LongPosition =0;
				}
				theWritableVarietyLimit.LongPosition += (LongPosition - LastLongPosition);
			}
		}
		else
		{
			if (PositionType == PT_Gross)
			{
				if (pIndexPreOrder->Position <0)
				{
					LastShortPosition = pIndexPreOrder->ShortYdPosition - pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen;
					ShortPosition = pIndexPreOrder->ShortYdPosition - pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen - freeVolume;
				}
				else
				{
					LastShortPosition = pIndexPreOrder->ShortYdPosition + pIndexPreOrder->ShortFrozen;
					ShortPosition = pIndexPreOrder->ShortYdPosition + pIndexPreOrder->ShortFrozen - freeVolume;
				}
				
				if (LastShortPosition <0)
				{
					LastShortPosition=0;
				}
				if (ShortPosition <0)
				{
					ShortPosition =0;
				}
				theWritableVarietyLimit.ShortPosition += (ShortPosition - LastShortPosition);
			}
			else
			{
				LastShortPosition = -1 *pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen;
				if (LastShortPosition <0)
				{
					LastShortPosition=0;
				}
				ShortPosition = -1 *pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen - freeVolume;
				if (ShortPosition <0)
				{
					ShortPosition =0;
				}
				theWritableVarietyLimit.ShortPosition += (ShortPosition - LastShortPosition);
			}
		}
		m_pDB->m_InvestorPositionLimitFactory->update(pVarietyPosiLimit,&theWritableVarietyLimit,pTransaction);
	}

	if (pPreOrder->Direction == D_Buy)
	{
		wtbIndexPreOrder.LongFrozen -= freeVolume;
	}
	else
	{
		wtbIndexPreOrder.ShortFrozen -= freeVolume;
	}
	m_pDB->m_IndexPreOrderFactory->update(pIndexPreOrder,&wtbIndexPreOrder,pTransaction);

#ifdef APP_QQUERY
	CDirectionType Direction;
	if (pIndexPreOrder->PositionType == PT_Net)
	{
		Direction = D_Net;
	}
	else
	{
		Direction = pPreOrder->Direction;
	}
	CInvestorPosition *pInvestorPosition = m_pDB->m_InvestorPositionFactory->findByBrkIDExIDInvIDInsDirHed(pPreOrder->BrokerID,pPreOrder->ExchangeID,\
		pPreOrder->InvestorID,pPreOrder->InstrumentID,Direction,pPreOrder->HedgeFlag);
	if (pInvestorPosition == NULL)
	{
		REPORT_EVENT(LOG_CRITICAL, "Not findPosition  in PreOrder PositionUnFrozen ", " InvestorID:%s,UserOrderLocalID:%s,InstrumentID:%s,SessionID:%d",\
			pPreOrder->InvestorID.getValue(),pPreOrder->UserOrderLocalID.getValue(),pPreOrder->InstrumentID.getValue(),pPreOrder->SessionID.getValue());
		m_pErrorEngine->reportError(ERROR_CAN_NOT_FIND_POSITION);
		return false;	
	}
	pPreOrder->linkInvestorPosition(pInvestorPosition);
	CWriteableInvestorPosition theWritableInvestorPosition;
	m_pDB->m_InvestorPositionFactory->retrieve(pInvestorPosition,&theWritableInvestorPosition);
	CMoneyType FrozenMargin;
	if (pPreOrder->Direction == D_Buy)
	{
		theWritableInvestorPosition.FrozenPosition -= freeVolume;
		if (pIndexPreOrder->PositionType == PT_Net)
		{
			theWritableInvestorPosition.UsedMargin = pIndexPreOrder->ActualMargin;
			theWritableInvestorPosition.FrozenMargin = pIndexPreOrder->ActualFrozenMargin;
		}
		else
		{
			theWritableInvestorPosition.UsedMargin = theWritableInvestorPosition.Position * pIndexPreOrder->LongMarginAmt;
			if (pIndexPreOrder->Position >=0)
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition +pIndexPreOrder->Position +theWritableInvestorPosition.FrozenPosition) *pIndexPreOrder->LongMarginAmt;
			}
			else
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition +theWritableInvestorPosition.FrozenPosition) *pIndexPreOrder->LongMarginAmt;
			}

			FrozenMargin -= pIndexPreOrder->ActualMargin;
			if (FrozenMargin <0.0)
			{
				FrozenMargin =0.0;
			}
			theWritableInvestorPosition.FrozenMargin = FrozenMargin;
		}
	}
	else
	{
		if (pIndexPreOrder->PositionType == PT_Net)
		{
			theWritableInvestorPosition.FrozenClosing -= freeVolume;
			theWritableInvestorPosition.UsedMargin = pIndexPreOrder->ActualMargin;
			theWritableInvestorPosition.FrozenMargin = pIndexPreOrder->ActualFrozenMargin;
		}
		else
		{
			theWritableInvestorPosition.FrozenPosition -= freeVolume;
			theWritableInvestorPosition.UsedMargin = theWritableInvestorPosition.Position * pIndexPreOrder->ShortMarginAmt;
			if (pIndexPreOrder->Position <0)
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition -pIndexPreOrder->Position +theWritableInvestorPosition.FrozenPosition) *pIndexPreOrder->ShortMarginAmt;
			}
			else
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition +theWritableInvestorPosition.FrozenPosition) *pIndexPreOrder->ShortMarginAmt;
			}
			FrozenMargin -= pIndexPreOrder->ActualMargin;
			if (FrozenMargin <0.0)
			{
				FrozenMargin =0.0;
			}
			theWritableInvestorPosition.FrozenMargin = FrozenMargin;
		}
	}
	theWritableInvestorPosition.LastOrderLocalID=pPreOrder->OrderLocalID;
	m_pDB->m_InvestorPositionFactory->update(pInvestorPosition,&theWritableInvestorPosition,pTransaction);
#endif

	return true;
}


///�����ͷŶ���ֲ�
///@paramp  pPreOrder   ����
//@param	pTransaction �����־
bool CFutureMoneyPosition::PositionUnFrozen(COrder* pOrder,CTransaction* pTransaction)
{
	bool bSuccess = false;
	CIndexPreOrder *pIndexPreOrder = pOrder->getIndexPreOrder();
	CWriteableIndexPreOrder wtbIndexPreOrder;
	m_pDB->m_IndexPreOrderFactory->retrieve(pIndexPreOrder,&wtbIndexPreOrder);
	CPositionTypeType PositionType = pIndexPreOrder->PositionType;
	
	CVolumeType freeVolume = pOrder->Volume - pOrder->VolumeTraded;
	if (pOrder->TimeCondition == TC_IOC)
	{
		freeVolume = pOrder->CancleVolume;
	}
	////��ȡƷ���޶�
	CInvestorPositionLimit *pVarietyPosiLimit = pIndexPreOrder->getVarietyPositionLimit();
	if (pVarietyPosiLimit != NULL)
	{
		CWriteableInvestorPositionLimit theWritableVarietyLimit;
		m_pDB->m_InvestorPositionLimitFactory->retrieve(pVarietyPosiLimit,&theWritableVarietyLimit);
		CVolumeType LongPosition=0;
		CVolumeType ShortPosition=0;
		CVolumeType LastLongPosition=0;
		CVolumeType LastShortPosition=0;
		if (pOrder->Direction == D_Buy)
		{
			if (PositionType == PT_Gross)
			{
				if (pIndexPreOrder->Position >=0)
				{
					LastLongPosition = pIndexPreOrder->LongYdPosition + pIndexPreOrder->Position + pIndexPreOrder->LongFrozen;
					LongPosition = pIndexPreOrder->LongYdPosition + pIndexPreOrder->Position + pIndexPreOrder->LongFrozen - freeVolume;
				}
				else
				{
					LastLongPosition = pIndexPreOrder->LongYdPosition + pIndexPreOrder->LongFrozen;
					LongPosition = pIndexPreOrder->LongYdPosition + pIndexPreOrder->LongFrozen - freeVolume;
				}
				
				if (LastLongPosition <0)
				{
					LastLongPosition=0;
				}
				if (LongPosition <0)
				{
					LongPosition =0;
				}
				theWritableVarietyLimit.LongPosition += (LongPosition - LastLongPosition);
			}
			else
			{
				LastLongPosition = pIndexPreOrder->Position + pIndexPreOrder->LongFrozen;
				if (LastLongPosition <0)
				{
					LastLongPosition=0;
				}
				LongPosition = pIndexPreOrder->Position + pIndexPreOrder->LongFrozen - freeVolume;
				if (LongPosition <0)
				{
					LongPosition =0;
				}
				theWritableVarietyLimit.LongPosition += (LongPosition - LastLongPosition);
			}
		}
		else
		{
			if (PositionType == PT_Gross)
			{
				if (pIndexPreOrder->Position <0)
				{
					LastShortPosition = pIndexPreOrder->ShortYdPosition - pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen;
					ShortPosition = pIndexPreOrder->ShortYdPosition - pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen - freeVolume;
				}
				else
				{
					LastShortPosition = pIndexPreOrder->ShortYdPosition + pIndexPreOrder->ShortFrozen;
					ShortPosition = pIndexPreOrder->ShortYdPosition + pIndexPreOrder->ShortFrozen - freeVolume;
				}
				
				if (LastShortPosition <0)
				{
					LastShortPosition=0;
				}
				if (ShortPosition <0)
				{
					ShortPosition =0;
				}
				theWritableVarietyLimit.ShortPosition += (ShortPosition - LastShortPosition);
			}
			else
			{
				LastShortPosition = -1 *pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen;
				if (LastShortPosition <0)
				{
					LastShortPosition=0;
				}
				ShortPosition = -1 *pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen - freeVolume;
				if (ShortPosition <0)
				{
					ShortPosition =0;
				}
				theWritableVarietyLimit.ShortPosition += (ShortPosition - LastShortPosition);
			}
		}
		m_pDB->m_InvestorPositionLimitFactory->update(pVarietyPosiLimit,&theWritableVarietyLimit,pTransaction);
	}
	
	if (pOrder->Direction == D_Buy)
	{
		wtbIndexPreOrder.LongFrozen -= freeVolume;
	}
	else
	{
		wtbIndexPreOrder.ShortFrozen -= freeVolume;
	}
	m_pDB->m_IndexPreOrderFactory->update(pIndexPreOrder,&wtbIndexPreOrder,pTransaction);
	
#ifdef APP_QQUERY
	CDirectionType Direction;
	if (pIndexPreOrder->PositionType == PT_Net)
	{
		Direction = D_Net;
	}
	else
	{
		Direction = pOrder->Direction;
	}
	CInvestorPosition *pInvestorPosition = m_pDB->m_InvestorPositionFactory->findByBrkIDExIDInvIDInsDirHed(pOrder->BrokerID,pOrder->ExchangeID,\
		pOrder->InvestorID,pOrder->InstrumentID,Direction,pOrder->HedgeFlag);
	if (pInvestorPosition == NULL)
	{
		REPORT_EVENT(LOG_CRITICAL, "Not findPosition  in PreOrder PositionUnFrozen ", " InvestorID:%s,UserOrderLocalID:%s,InstrumentID:%s,SessionID:%d",\
			pOrder->InvestorID.getValue(),pOrder->UserOrderLocalID.getValue(),pOrder->InstrumentID.getValue(),pOrder->SessionID.getValue());
		m_pErrorEngine->reportError(ERROR_CAN_NOT_FIND_POSITION);
		return false;	
	}
	pOrder->linkInvestorPosition(pInvestorPosition);
	CWriteableInvestorPosition theWritableInvestorPosition;
	m_pDB->m_InvestorPositionFactory->retrieve(pInvestorPosition,&theWritableInvestorPosition);
	CMoneyType FrozenMargin;
	if (pOrder->Direction == D_Buy)
	{
		theWritableInvestorPosition.FrozenPosition -= freeVolume;
		if (pIndexPreOrder->PositionType == PT_Net)
		{
			theWritableInvestorPosition.UsedMargin = pIndexPreOrder->ActualMargin;
			theWritableInvestorPosition.FrozenMargin = pIndexPreOrder->ActualFrozenMargin;
		}
		else
		{
			theWritableInvestorPosition.UsedMargin = theWritableInvestorPosition.Position * pIndexPreOrder->LongMarginAmt;
			if (pIndexPreOrder->Position >=0)
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition + pIndexPreOrder->Position +theWritableInvestorPosition.FrozenPosition) *pIndexPreOrder->LongMarginAmt;
			}
			else
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition +theWritableInvestorPosition.FrozenPosition) *pIndexPreOrder->LongMarginAmt;
			}

			FrozenMargin -= pIndexPreOrder->ActualMargin;
			if (FrozenMargin <0.0)
			{
				FrozenMargin =0.0;
			}
			theWritableInvestorPosition.FrozenMargin = FrozenMargin;
		}
	}
	else
	{
		if (pIndexPreOrder->PositionType == PT_Net)
		{
			theWritableInvestorPosition.FrozenClosing -= freeVolume;
			theWritableInvestorPosition.UsedMargin = pIndexPreOrder->ActualMargin;
			theWritableInvestorPosition.FrozenMargin = pIndexPreOrder->ActualFrozenMargin;
		}
		else
		{
			theWritableInvestorPosition.FrozenPosition -= freeVolume;
			theWritableInvestorPosition.UsedMargin = theWritableInvestorPosition.Position * pIndexPreOrder->ShortMarginAmt;
			if (pIndexPreOrder->Position <0)
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition - pIndexPreOrder->Position +theWritableInvestorPosition.FrozenPosition) *pIndexPreOrder->ShortMarginAmt;
			}
			else
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition +theWritableInvestorPosition.FrozenPosition) *pIndexPreOrder->ShortMarginAmt;
			}
			FrozenMargin -= pIndexPreOrder->ActualMargin;
			if (FrozenMargin <0.0)
			{
				FrozenMargin =0.0;
			}
			theWritableInvestorPosition.FrozenMargin = FrozenMargin;
		}
	}
	theWritableInvestorPosition.LastOrderLocalID=pOrder->OrderLocalID;
	m_pDB->m_InvestorPositionFactory->update(pInvestorPosition,&theWritableInvestorPosition,pTransaction);
#endif
	
	return true;
}

bool CFutureMoneyPosition::TradeMoneyTradeWithNet(CIndexPreOrder *pIndexPreOrder,CWriteableIndexPreOrder *pWtbIndexPreOrder,CWriteableOrder* pOrder,CWriteableTrade* pTrade,CMoneyField* pMoneyField,CTransaction* pTransaction)
{
	//�ͷ�ռ�ñ�֤��
	CVolumeType CloseVolume=0;
	CVolumeType OpenVolume=0;
	if (pIndexPreOrder->Position >0 && pTrade->Direction == D_Sell)
	{
		if (pIndexPreOrder->Position >= pTrade->TradeVolume)
		{
			CloseVolume = pTrade->TradeVolume;
		}
		else
		{
			CloseVolume = pIndexPreOrder->Position;
			OpenVolume = pTrade->TradeVolume - pIndexPreOrder->Position;
		}
	}
	else if (pIndexPreOrder->Position <0 && pTrade->Direction == D_Buy)
	{
		if (-1*pIndexPreOrder->Position >= pTrade->TradeVolume)
		{
			CloseVolume = pTrade->TradeVolume;
		}
		else
		{
			CloseVolume = pIndexPreOrder->Position * -1;
			OpenVolume = pTrade->TradeVolume + pIndexPreOrder->Position;
		}
	}
	else
	{
		OpenVolume = pTrade->TradeVolume;
	}

	//�ͷųֲ�ռ�ñ�֤��Ŀǰ���óֲ־����ͷ�
	CMoneyType avgPositonPrice =0.0;
	if (CloseVolume >0)
	{
		pMoneyField->ReleaseMargin = fabs(pIndexPreOrder->ActualMargin * CloseVolume / pIndexPreOrder->Position);
		avgPositonPrice = fabs(pIndexPreOrder->PositionCost/pIndexPreOrder->Position/pIndexPreOrder->VolumeMultiple);//�ֲ־���;
		if (pTrade->Direction == D_Sell)
		{
			pMoneyField->CloseProfit = (pTrade->TradePrice - avgPositonPrice) * CloseVolume*pIndexPreOrder->VolumeMultiple;
			pWtbIndexPreOrder->Position -= CloseVolume;
			pWtbIndexPreOrder->PositionCost -= pIndexPreOrder->PositionCost * CloseVolume / pIndexPreOrder->Position;
			pWtbIndexPreOrder->ActualMargin -= pMoneyField->ReleaseMargin;
			pWtbIndexPreOrder->ShortFrozen -= CloseVolume;
		}
		else
		{
			pMoneyField->CloseProfit = (avgPositonPrice - pTrade->TradePrice) * CloseVolume*pIndexPreOrder->VolumeMultiple;
			pWtbIndexPreOrder->Position += CloseVolume;
			pWtbIndexPreOrder->PositionCost += pIndexPreOrder->PositionCost * CloseVolume / pIndexPreOrder->Position;
			pWtbIndexPreOrder->ActualMargin -= pMoneyField->ReleaseMargin;
			pWtbIndexPreOrder->LongFrozen -= CloseVolume;
		}

	}

	//����ռ�ñ�֤��
	if (OpenVolume >0)
	{
		if (pTrade->Direction == D_Buy)
		{
			pWtbIndexPreOrder->Position += OpenVolume;
			pWtbIndexPreOrder->PositionCost += OpenVolume * pIndexPreOrder->VolumeMultiple * pTrade->TradePrice;
			pWtbIndexPreOrder->ActualMargin += OpenVolume * pIndexPreOrder->LongMarginAmt;
			pWtbIndexPreOrder->LongFrozen -= OpenVolume;
		}
		else
		{
			pWtbIndexPreOrder->Position -= OpenVolume;
			pWtbIndexPreOrder->PositionCost += OpenVolume * pIndexPreOrder->VolumeMultiple * pTrade->TradePrice;
			pWtbIndexPreOrder->ActualMargin += OpenVolume * pIndexPreOrder->ShortMarginAmt;
			pWtbIndexPreOrder->ShortFrozen -= OpenVolume;
		}
	}

	//����ʵ�ʶ��ᱣ֤��
	CMoneyType  frozenMargin=0.0;
	CVolumeType Position=0;
	//�����ͷ���ᱣ֤��
	Position = pWtbIndexPreOrder->Position + pWtbIndexPreOrder->LongFrozen;
	if (Position >0)
	{
		frozenMargin = 	Position*pIndexPreOrder->LongMarginAmt;
	}
	else
	{
		frozenMargin = 	-1*Position*pIndexPreOrder->ShortMarginAmt;
	}
	frozenMargin -= pWtbIndexPreOrder->ActualMargin;
	if (frozenMargin <0.0)
	{
		frozenMargin = 0.0;
	}
	pWtbIndexPreOrder->LongFrozenMargin = frozenMargin;
	//�����ͷ���ᱣ֤��
	Position = pWtbIndexPreOrder->Position - pWtbIndexPreOrder->ShortFrozen;
	if (Position >0)
	{
		frozenMargin = 	Position*pIndexPreOrder->LongMarginAmt;
	}
	else
	{
		frozenMargin = 	-1*Position*pIndexPreOrder->ShortMarginAmt;
	}
	frozenMargin -= pWtbIndexPreOrder->ActualMargin;
	if (frozenMargin <0.0)
	{
		frozenMargin = 0.0;
	}
	pWtbIndexPreOrder->ShortFrozenMargin = frozenMargin;
	pWtbIndexPreOrder->ActualFrozenMargin = pWtbIndexPreOrder->LongFrozenMargin + pWtbIndexPreOrder->ShortFrozenMargin;

	//����ռ�úͶ��ᱣ֤��仯ֵ	
	pMoneyField->MarginChanged = pWtbIndexPreOrder->ActualMargin - pIndexPreOrder->ActualMargin;
	pMoneyField->FrozenMarginChanged = (pWtbIndexPreOrder->LongFrozenMargin+pWtbIndexPreOrder->ShortFrozenMargin) - 
											(pIndexPreOrder->LongFrozenMargin + pIndexPreOrder->ShortFrozenMargin);

	return true;
}


bool CFutureMoneyPosition::TradeMoneyTradeWithGross(CIndexPreOrder *pIndexPreOrder,CWriteableIndexPreOrder *pWtbIndexPreOrder,CWriteableOrder* pOrder,CWriteableTrade* pTrade,CMoneyField* pMoneyField,CTransaction* pTransaction)
{
	if (pOrder->Direction == D_Buy)
	{
		pWtbIndexPreOrder->LongPosition += pTrade->TradeVolume;
		pWtbIndexPreOrder->LongFrozen -= pTrade->TradeVolume;
		pWtbIndexPreOrder->Position += pTrade->TradeVolume;
	}
	else
	{
		pWtbIndexPreOrder->ShortPosition += pTrade->TradeVolume;
		pWtbIndexPreOrder->ShortFrozen -= pTrade->TradeVolume;
		pWtbIndexPreOrder->Position -= pTrade->TradeVolume;
	}

	//����ֲ�ռ�ñ�֤��
	CMoneyType LastLongMargin;
	CMoneyType LastShortMargin;
	CMoneyType LongMargin;
	CMoneyType ShortMargin;
	if (pWtbIndexPreOrder->Position >=0)
	{
		LastLongMargin = (pWtbIndexPreOrder->LongYdPosition + pWtbIndexPreOrder->Position) * pIndexPreOrder->LongMarginAmt;
		LastShortMargin = pWtbIndexPreOrder->ShortYdPosition * pIndexPreOrder->ShortMarginAmt;

		LongMargin = (pWtbIndexPreOrder->LongYdPosition + pWtbIndexPreOrder->Position + pWtbIndexPreOrder->LongFrozen) * pIndexPreOrder->LongMarginAmt;
		ShortMargin = (pWtbIndexPreOrder->ShortYdPosition + pWtbIndexPreOrder->ShortFrozen) * pIndexPreOrder->ShortMarginAmt;
	}
	else
	{
		LastLongMargin = pWtbIndexPreOrder->LongYdPosition * pIndexPreOrder->LongMarginAmt;
		LastShortMargin = (pWtbIndexPreOrder->ShortYdPosition - pWtbIndexPreOrder->Position) * pIndexPreOrder->ShortMarginAmt;

		LongMargin = (pWtbIndexPreOrder->LongYdPosition + pWtbIndexPreOrder->LongFrozen) * pIndexPreOrder->LongMarginAmt;
		ShortMargin = (pWtbIndexPreOrder->ShortYdPosition - pWtbIndexPreOrder->Position + pWtbIndexPreOrder->ShortFrozen) * pIndexPreOrder->ShortMarginAmt;
	}
	pWtbIndexPreOrder->ActualMargin = MAX(LastLongMargin,LastShortMargin);
	//���㶳�ᱣ֤��
	pWtbIndexPreOrder->ActualFrozenMargin = MAX(LongMargin,ShortMargin) - pWtbIndexPreOrder->ActualMargin;
	if (pWtbIndexPreOrder->ActualFrozenMargin < 0.0)
	{
		pWtbIndexPreOrder->ActualFrozenMargin = 0.0;
	}


	//����ռ�úͶ��ᱣ֤��仯ֵ	
	pMoneyField->MarginChanged = pWtbIndexPreOrder->ActualMargin - pIndexPreOrder->ActualMargin;
	pMoneyField->FrozenMarginChanged = pWtbIndexPreOrder->ActualFrozenMargin - pIndexPreOrder->ActualFrozenMargin;

	return true;
}


///�ɽ��ͷ��ʽ�
///@param   pInvestorAccount ��Ӧ�ʽ��˻�ָ��
///@param   pOrder  ����
///@param	pTrade  �ɽ�
///@param	pTransaction �����־
//Ĭ��Ϊƽ�֡� �˺���ֻ����ƽ�ֳɽ�����
bool CFutureMoneyPosition::TradeMoneyUpdate(CWriteableOrder* pOrder,CWriteableTrade* pTrade, CMoneyField* pMoneyField,CTransaction* pTransaction)

{
	bool bSuccess = false;
	CIndexPreOrder *pIndexPreOrder = pOrder->getIndexPreOrder();
	CWriteableIndexPreOrder wtbIndexPreOrder;
	m_pDB->m_IndexPreOrderFactory->retrieve(pIndexPreOrder,&wtbIndexPreOrder);
	
	CInvestorAccount* pInvestorAccount = pIndexPreOrder->getInvestorAccount();
	CWriteableInvestorAccount theWriteableInvestorAccount;
	m_pDB->m_InvestorAccountFactory->retrieve(pInvestorAccount,&theWriteableInvestorAccount);
	
	
	if (pIndexPreOrder->PositionType == PT_Gross)
	{
		bSuccess = TradeMoneyTradeWithGross(pIndexPreOrder,&wtbIndexPreOrder,pOrder,pTrade,pMoneyField,pTransaction);
	}
	else
	{
		bSuccess = TradeMoneyTradeWithNet(pIndexPreOrder,&wtbIndexPreOrder,pOrder,pTrade,pMoneyField,pTransaction);
		theWriteableInvestorAccount.CloseProfit  += pMoneyField->CloseProfit; 
	}
	
	
	theWriteableInvestorAccount.Margin += pMoneyField->MarginChanged;		
	// 2014-06-25 longqy ƽ�ֳɽ���ʱ��ҲҪ���¶��ᱣ֤��
	theWriteableInvestorAccount.FrozenMargin += pMoneyField->FrozenMarginChanged;
	
	theWriteableInvestorAccount.FrozenFee  -= pOrder->FrozenFee * pTrade->TradeVolume / pOrder->Volume;
	if (pOrder->Direction == D_Buy)
	{
		pMoneyField->Fee =  pTrade->TradeVolume*pIndexPreOrder->OpenFeeAmt;
	}
	else
	{
		pMoneyField->Fee =  pTrade->TradeVolume*pIndexPreOrder->OffsetFeeAmt;
	}
	theWriteableInvestorAccount.Fee  += pMoneyField->Fee;
	theWriteableInvestorAccount.ReleaseMargin   += pMoneyField->ReleaseMargin; 
	
	pTrade->UsedFee =  pMoneyField->Fee;
	pTrade->UsedMargin = 0.0;
	pTrade->Premium    = 0.0;
	
	//����Ʒ�ֲֳ��޶�
	CInvestorPositionLimit *pVarietyPosiLimit = pIndexPreOrder->getVarietyPositionLimit();
	if (pVarietyPosiLimit != NULL)
	{
		CPositionTypeType PositionType = pIndexPreOrder->PositionType;
		CWriteableInvestorPositionLimit theWritableVarietyLimit;
		m_pDB->m_InvestorPositionLimitFactory->retrieve(pVarietyPosiLimit,&theWritableVarietyLimit);
		CVolumeType LongPosition=0;
		CVolumeType ShortPosition=0;
		CVolumeType LastLongPosition=0;
		CVolumeType LastShortPosition=0;
		if (PositionType == PT_Gross)
		{
			if (pIndexPreOrder->Position>=0)
			{
				LastLongPosition = pIndexPreOrder->LongYdPosition + pIndexPreOrder->Position + pIndexPreOrder->LongFrozen;
				LastShortPosition = pIndexPreOrder->ShortYdPosition + pIndexPreOrder->ShortFrozen;
			}
			else
			{
				LastLongPosition = pIndexPreOrder->LongYdPosition + pIndexPreOrder->LongFrozen;
				LastShortPosition = pIndexPreOrder->ShortYdPosition - pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen;
			}

			if (wtbIndexPreOrder.Position>=0)
			{
				LongPosition = wtbIndexPreOrder.LongYdPosition + wtbIndexPreOrder.Position + wtbIndexPreOrder.LongFrozen;
				ShortPosition = wtbIndexPreOrder.ShortYdPosition + wtbIndexPreOrder.ShortFrozen;
			}
			else
			{
				LongPosition = wtbIndexPreOrder.LongYdPosition + wtbIndexPreOrder.LongFrozen;
				ShortPosition = wtbIndexPreOrder.ShortYdPosition - wtbIndexPreOrder.Position + wtbIndexPreOrder.ShortFrozen;
			}

			theWritableVarietyLimit.LongPosition += (LongPosition - LastLongPosition);
			theWritableVarietyLimit.ShortPosition += (ShortPosition - LastShortPosition);
		}
		else
		{
			LastLongPosition = pIndexPreOrder->Position + pIndexPreOrder->LongFrozen;
			if (LastLongPosition <0)
			{
				LastLongPosition=0;
			}
			LongPosition = wtbIndexPreOrder.Position + wtbIndexPreOrder.LongFrozen;
			if (LongPosition <0)
			{
				LongPosition =0;
			}
			theWritableVarietyLimit.LongPosition += (LongPosition - LastLongPosition);
			
			LastShortPosition = -1*pIndexPreOrder->Position + pIndexPreOrder->ShortFrozen;
			if (LastShortPosition <0)
			{
				LastShortPosition=0;
			}
			ShortPosition = -1*wtbIndexPreOrder.Position + wtbIndexPreOrder.ShortFrozen;
			if (ShortPosition <0)
			{
				ShortPosition =0;
			}
			theWritableVarietyLimit.ShortPosition += (ShortPosition - LastShortPosition);
		}
		
		m_pDB->m_InvestorPositionLimitFactory->update(pVarietyPosiLimit,&theWritableVarietyLimit,pTransaction);
	}
	
	CFutureMoneyPosition::ChangeBalanceAndAvailable(&theWriteableInvestorAccount);
	m_pDB->m_InvestorAccountFactory->update(pInvestorAccount,&theWriteableInvestorAccount,pTransaction);
	m_pDB->m_IndexPreOrderFactory->update(pIndexPreOrder,&wtbIndexPreOrder,pTransaction);
	return true;
} 


///�ɽ����³ֲ�
///@param	pInvestorPosition  ��Ӧ�ֲ�
///@param   pOrder
///@param   pTrade   �ɽ�
///@param	pTransaction �����־
bool CFutureMoneyPosition::TradePositionUpdate(COrder* pOrder,CWriteableTrade* pTrade,CMoneyField* pMoneyField,CTransaction* pTransaction)
{
	CIndexPreOrder *pIndexPreOrder = pOrder->getIndexPreOrder();
	CWriteableInvestorPosition theWritableInvestorPosition;
	CDirectionType Direction;
	if (pIndexPreOrder->PositionType == PT_Net)
	{
		Direction = D_Net;
	}
	else
	{
		Direction = pOrder->Direction;
	}
	CInvestorPosition *pInvestorPosition = m_pDB->m_InvestorPositionFactory->findByBrkIDExIDInvIDInsDirHed(pOrder->BrokerID,pOrder->ExchangeID,\
		pOrder->InvestorID,pOrder->InstrumentID,Direction,pOrder->HedgeFlag);
	if (pInvestorPosition == NULL)
	{
		REPORT_EVENT(LOG_CRITICAL, "Not findPosition  in TradePositionUpdate ", " InvestorID:%s,OrderSysID:%s,InstrumentID:%s",\
			pOrder->InvestorID.getValue(),pOrder->OrderSysID.getValue(),pOrder->InstrumentID.getValue(),pOrder->SessionID.getValue());
		m_pErrorEngine->reportError(ERROR_CAN_NOT_FIND_POSITION);
		return false;	
	}
	pOrder->linkInvestorPosition(pInvestorPosition);
	m_pDB->m_InvestorPositionFactory->retrieve(pInvestorPosition,&theWritableInvestorPosition);
	
	if (pOrder->Direction == D_Buy)
	{
		theWritableInvestorPosition.FrozenPosition -= pTrade->TradeVolume;
		theWritableInvestorPosition.Position += pTrade->TradeVolume;	
	}
	else
	{
		if (Direction == D_Net)
		{
			theWritableInvestorPosition.FrozenClosing -= pTrade->TradeVolume;
			theWritableInvestorPosition.Position -= pTrade->TradeVolume;
		}
		else
		{
			theWritableInvestorPosition.FrozenPosition -= pTrade->TradeVolume;
			theWritableInvestorPosition.Position += pTrade->TradeVolume;
		}
		
	}
	if (Direction == D_Net)
	{
		theWritableInvestorPosition.PositionCost = pIndexPreOrder->PositionCost;
		theWritableInvestorPosition.UsedMargin = pIndexPreOrder->ActualMargin;
		theWritableInvestorPosition.FrozenMargin = pIndexPreOrder->ActualFrozenMargin;
	}
	else
	{
		theWritableInvestorPosition.PositionCost += (pTrade->TradePrice * pTrade->TradeVolume * pIndexPreOrder->VolumeMultiple);
		CMoneyType FrozenMargin;
		if (pOrder->Direction == D_Buy)
		{
			theWritableInvestorPosition.UsedMargin = theWritableInvestorPosition.Position * pIndexPreOrder->LongMarginAmt;
			if (pIndexPreOrder->Position >=0)
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition +pIndexPreOrder->Position +theWritableInvestorPosition.FrozenPosition) *pIndexPreOrder->LongMarginAmt;
			}
			else
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition +theWritableInvestorPosition.FrozenPosition) *pIndexPreOrder->LongMarginAmt;
			}
		}
		else
		{
			theWritableInvestorPosition.UsedMargin = theWritableInvestorPosition.Position * pIndexPreOrder->ShortMarginAmt;
			if (pIndexPreOrder->Position <0)
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition -pIndexPreOrder->Position +theWritableInvestorPosition.FrozenPosition) *pIndexPreOrder->ShortMarginAmt;
			}
			else
			{
				FrozenMargin = (theWritableInvestorPosition.YdPosition +theWritableInvestorPosition.FrozenPosition) *pIndexPreOrder->ShortMarginAmt;
			}
		}
		FrozenMargin -= pIndexPreOrder->ActualMargin;
		if (FrozenMargin <0.0)
		{
			FrozenMargin =0.0;
		}
		theWritableInvestorPosition.FrozenMargin = FrozenMargin;
	}
	theWritableInvestorPosition.LastOrderLocalID=pOrder->OrderLocalID;
	theWritableInvestorPosition.LastTradeID=pTrade->TradeID;
	m_pDB->m_InvestorPositionFactory->update(pInvestorPosition,&theWritableInvestorPosition,pTransaction);
	return true;
}