/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �н���������˾
///@file CDbmtServiceBase.h
///@brief	ʵ����CDbmtServiceBase
///@history 
///20130119	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#include "CDbmtServiceImpl.h"
#include "monitorIndex.h"
#include "UFEntityCopy.h"
#include "system.h"

static CEventMonitor eventMonitor;

///ͬ�����ݿ��ͻ��ʽ��ʻ������
///@param	pInvestorAccountDeposit	Ҫͬ���Ŀͻ��ʽ��ʻ��������Ϣ
///@param	pResDeposit	�����Ӧ����Ϣ
///@param	topicID	DBMT�������
///@param	seqID	DBMT�����к�
///@param	sessionRef	�Ự����
///@param	pTransaction	���������ڵ�����
///@return	true��ʾ�ɹ���false��ʾʧ��
bool CDbmtServiceImpl::SyncInvestorAccountDeposit(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit,CAccountDepositResField *pResDeposit,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
		const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	/*** SIR XXXXX BEGIN ***/
    std::string accountSeqNo( pInvestorAccountDeposit->AccountSeqNo.getValue() );
    if ( accountSeqNo.size() < 3 )
    {//�ʽ���ˮ�Ÿ�ʽ����
        printf("[ERR][%s]AccountSeqNo format error, eg A_1 or B_1 or C_1\n", accountSeqNo.c_str());
		//��AccountInsideSeqNo�������뷵��
		pInvestorAccountDeposit->AccountInsideSeqNo = ERROR_DUPLICATE_DEPOSIT_FIELD;
        return false;    
    }
    
    switch(accountSeqNo[0])
    {
    case INVESTORACCOUNTDEPOSIT_FROM_CHAIRMAN:
    	topicID = INVESTORACCOUNTDEPOSIT_TOPICID_CHAIRMAN;
		break;
    case INVESTORACCOUNTDEPOSIT_FROM_MONEYGATE:
    	topicID = INVESTORACCOUNTDEPOSIT_TOPICID_CHAIRMAN;
		break;
    case INVESTORACCOUNTDEPOSIT_FROM_FIELD:
    	topicID = INVESTORACCOUNTDEPOSIT_TOPICID_FIELD;
		break;
	case INVESTORACCOUNTDEPOSIT_FROM_Netting:
		topicID = INVESTORACCOUNTDEPOSIT_TOPICID_Netting;
		break;
    default:
    	//�ʽ���ˮ�Ÿ�ʽ����
	printf("[ERR][%s]AccountSeqNo format error, eg A_1 or B_1 or C_1\n", accountSeqNo.c_str());
	//��AccountInsideSeqNo�������뷵��
	pInvestorAccountDeposit->AccountInsideSeqNo = ERROR_DUPLICATE_DEPOSIT_FIELD;
	return false; 
    }

    seqID = atoi(accountSeqNo.substr(2).c_str());
/*** SIR XXXXX END ***/
	
	if (isDuplicate(topicID,seqID))
	{
	    printf("[ERR][%s]AccountSeqNo is duplicate\n", accountSeqNo.c_str());
		//��AccountInsideSeqNo�������뷵��
		pInvestorAccountDeposit->AccountInsideSeqNo = ERROR_DUPLICATE_DEPOSIT_FIELD;
		return false;
	}
	if (!suitableTime())
	{
		return false;
	}

	bool success=true;
	CInvestorAccount *pInvestorAccount=NULL;
	CWriteableInvestorAccount theInvestorAccount;
	theInvestorAccount.init();
	if (pInvestorAccountDeposit->BrokerID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_BROKERID_CANNOT_BE_BLANK);
		return false;
	}

	if(pInvestorAccountDeposit->AccountID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_ACCOUNT_CANNOT_BE_BLANK);
		return false;
	}
	
	pInvestorAccount=m_DB->m_InvestorAccountFactory->findByBrokerIDAccountID(pInvestorAccountDeposit->BrokerID,pInvestorAccountDeposit->AccountID);	
	
	if (pInvestorAccount==NULL)
	{
		m_ErrorEngine->reportError(ERROR_CAN_NOT_FIND_ACCOUNT);
		REPORT_EVENT(LOG_CRITICAL,"DBMTError","Can sync account deposit for %s",pInvestorAccountDeposit->AccountID.getValue());
		success=false;
	}
	else
	{
		m_DB->m_InvestorAccountFactory->retrieve(pInvestorAccount,&theInvestorAccount);
		
		//pInvestorAccountDeposit->Amountʼ����һ����ֵ��������ǿ������жϵ�
		if (pInvestorAccountDeposit->AmountDirection==AD_In)
		{
			theInvestorAccount.Deposit+=pInvestorAccountDeposit->Amount;
			theInvestorAccount.Balance+=pInvestorAccountDeposit->Amount;
			theInvestorAccount.Available+=pInvestorAccountDeposit->Amount;
			theInvestorAccount.DynamicRights+=pInvestorAccountDeposit->Amount;
			REPORT_EVENT(LOG_CRITICAL,"AccountDeposit","Ͷ�����˺�[%s]���[%f]Ԫ\n",pInvestorAccountDeposit->AccountID.getValue(),pInvestorAccountDeposit->Amount.getValue());
		}
		else
		{
			theInvestorAccount.Withdraw+=pInvestorAccountDeposit->Amount;
			theInvestorAccount.Balance-=pInvestorAccountDeposit->Amount;
			theInvestorAccount.Available-=pInvestorAccountDeposit->Amount;
			theInvestorAccount.DynamicRights-=pInvestorAccountDeposit->Amount;
/*** SIR XXXXX BEGIN ***/
			//���������ʽ�ͽ���׼������Ϊ����
			//��������ʱ������
#if 0
			if (theInvestorAccount.Available < SMALL_DOUBLE)
#else
            if (false)
#endif
			{
				REPORT_EVENT(LOG_CRITICAL,"AccountDeposit","Ͷ�����˺�[%s]����[%f]Ԫ, ���������ʽ�[%f]Ϊ����������ʧ��\n",
					pInvestorAccountDeposit->AccountID.getValue(),pInvestorAccountDeposit->Amount.getValue(),theInvestorAccount.Available.getValue());
				
				//���ô����룬����AccountInsideSeqNo�ֶ�
				pInvestorAccountDeposit->AccountInsideSeqNo = ERROR_DEPOSIT_AMOUNT_NOT_ENOUGH;
				success = false;
			}
			else
			{
			    std::string accountSeqNo( pInvestorAccountDeposit->AccountSeqNo.getValue() );
                if (INVESTORACCOUNTDEPOSIT_FROM_MONEYGATE == accountSeqNo[0])
                {
                	theInvestorAccount.ManualFrozen-=pInvestorAccountDeposit->Amount;//ͨ������ʵ�ֵĳ���Ҫ�ⶳ��ʱ�����ʽ�
                	theInvestorAccount.Available+=pInvestorAccountDeposit->Amount;//��Чǰ���Ѿ������,�ⶳ��Ҫ�ӻ���
                }
                REPORT_EVENT(LOG_CRITICAL,"AccountDeposit","Ͷ�����˺�[%s]����[%f]Ԫ\n",pInvestorAccountDeposit->AccountID.getValue(),pInvestorAccountDeposit->Amount.getValue());
			}
/*** SIR XXXXX END ***/

		}
		if (success)
		{
			pResDeposit->Balance = theInvestorAccount.Balance;
			pResDeposit->Available = theInvestorAccount.Available;
			m_DB->m_InvestorAccountFactory->update(pInvestorAccount,&theInvestorAccount,pTransaction);
		}
	}
	if (success)
	{
/*** SIR XXXXX BEGIN ***/
		///����������ˮ��+1
		m_DB->m_memTableItemInfo.InvestorAccountDepositCurrentMaxItem++;
		pInvestorAccountDeposit->AccountInsideSeqNo = m_DB->m_memTableItemInfo.InvestorAccountDepositCurrentMaxItem;
		pResDeposit->AccountInsideSeqNo = m_DB->m_memTableItemInfo.InvestorAccountDepositCurrentMaxItem;
/*** SIR XXXXX END ***/

		//�����ɹ�,д�� �������ˮ�� 
		m_DB->m_InvestorAccountDepositFactory->add(pInvestorAccountDeposit,pTransaction);
	}
	
	if (m_dbmtLog!=NULL)
	{
		if (success)
		{
			fprintf(m_dbmtLog,"%s,AccountDeposit,success,",getCurrentTime(m_DB).getValue());
		}
		else
		{
			fprintf(m_dbmtLog,"%s,AccountDeposit,failed,",getCurrentTime(m_DB).getValue());
		}
		pInvestorAccountDeposit->dumpInLine(m_dbmtLog);
		fprintf(m_dbmtLog,"\n");
		fflush(m_dbmtLog);
	}
	return success;
}


///ͬ�����ݿ��ͻ��ʽ��ʻ�������ʵ��
///@param	pClientTradingID	Ҫͬ���Ŀͻ��ʽ��ʻ��������Ϣ
///@param	pTransaction	���������ڵ�����
///@return	true��ʾ�ɹ���false��ʾʧ��
bool CDbmtServiceImpl::SyncClientTradingID(CWriteableClientTradingID *pClientTradingID,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
		const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	bool success=true;
	CClientTradingID *pClientTradingIDRight=NULL;
	CWriteableClientTradingID theClientTradingID;
	theClientTradingID.init();

	if (pClientTradingID->BrokerID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_BROKERID_CANNOT_BE_BLANK);
		return false;
	}

	if(pClientTradingID->ExchangeID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_EXCHANGEID_CANNOTBEBLANK);
		return false;
	}

	if(pClientTradingID->ParticipantID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_PARTICIPANTID_NOTNULL);
		return false;
	}

	if(pClientTradingID->ClientID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_CLIENTID_NOTNULL);
		return false;
	}

	
	pClientTradingIDRight=m_DB->m_ClientTradingIDFactory->findByBrokerIDExchangeIDPartClientID(pClientTradingID->BrokerID,pClientTradingID->ExchangeID,
		pClientTradingID->ParticipantID,pClientTradingID->ClientID);	
	
	if (pClientTradingIDRight==NULL)
	{
		m_DB->m_ClientTradingIDFactory->add(pClientTradingID,pTransaction);
	}
	else
	{
		m_DB->m_ClientTradingIDFactory->retrieve(pClientTradingIDRight,&theClientTradingID);
		//�ϳ�ֻ�޸�isActive��ClientRight�ֶ�
		theClientTradingID.IsActive=pClientTradingID->IsActive;
		theClientTradingID.ClientRight=pClientTradingID->ClientRight;
		m_DB->m_ClientTradingIDFactory->update(pClientTradingIDRight,&theClientTradingID,pTransaction);
	}

	
	if (m_dbmtLog!=NULL)
	{
		fprintf(m_dbmtLog,"%s,ClientTradingID,success,",getCurrentTime(m_DB).getValue());
		pClientTradingID->dumpInLine(m_dbmtLog);
		fprintf(m_dbmtLog,"\n");
		fflush(m_dbmtLog);
	}
	return success;
}
