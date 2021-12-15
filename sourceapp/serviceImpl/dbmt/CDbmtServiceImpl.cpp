/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 中金所技术公司
///@file CDbmtServiceBase.h
///@brief	实现了CDbmtServiceBase
///@history 
///20130119	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CDbmtServiceImpl.h"
#include "monitorIndex.h"
#include "UFEntityCopy.h"
#include "system.h"

static CEventMonitor eventMonitor;

///同步数据库表客户资金帐户出入金
///@param	pInvestorAccountDeposit	要同步的客户资金帐户出入金信息
///@param	pResDeposit	出入金应答信息
///@param	topicID	DBMT的主题号
///@param	seqID	DBMT的序列号
///@param	sessionRef	会话引用
///@param	pTransaction	本操作属于的事务
///@return	true表示成功，false表示失败
bool CDbmtServiceImpl::SyncInvestorAccountDeposit(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit,CAccountDepositResField *pResDeposit,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
		const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	/*** SIR XXXXX BEGIN ***/
    std::string accountSeqNo( pInvestorAccountDeposit->AccountSeqNo.getValue() );
    if ( accountSeqNo.size() < 3 )
    {//资金流水号格式错误
        printf("[ERR][%s]AccountSeqNo format error, eg A_1 or B_1 or C_1\n", accountSeqNo.c_str());
		//用AccountInsideSeqNo将错误码返回
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
    	//资金流水号格式错误
	printf("[ERR][%s]AccountSeqNo format error, eg A_1 or B_1 or C_1\n", accountSeqNo.c_str());
	//用AccountInsideSeqNo将错误码返回
	pInvestorAccountDeposit->AccountInsideSeqNo = ERROR_DUPLICATE_DEPOSIT_FIELD;
	return false; 
    }

    seqID = atoi(accountSeqNo.substr(2).c_str());
/*** SIR XXXXX END ***/
	
	if (isDuplicate(topicID,seqID))
	{
	    printf("[ERR][%s]AccountSeqNo is duplicate\n", accountSeqNo.c_str());
		//用AccountInsideSeqNo将错误码返回
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
		
		//pInvestorAccountDeposit->Amount始终是一个正值，出入金是靠方向判断的
		if (pInvestorAccountDeposit->AmountDirection==AD_In)
		{
			theInvestorAccount.Deposit+=pInvestorAccountDeposit->Amount;
			theInvestorAccount.Balance+=pInvestorAccountDeposit->Amount;
			theInvestorAccount.Available+=pInvestorAccountDeposit->Amount;
			theInvestorAccount.DynamicRights+=pInvestorAccountDeposit->Amount;
			REPORT_EVENT(LOG_CRITICAL,"AccountDeposit","投资者账号[%s]入金[%f]元\n",pInvestorAccountDeposit->AccountID.getValue(),pInvestorAccountDeposit->Amount.getValue());
		}
		else
		{
			theInvestorAccount.Withdraw+=pInvestorAccountDeposit->Amount;
			theInvestorAccount.Balance-=pInvestorAccountDeposit->Amount;
			theInvestorAccount.Available-=pInvestorAccountDeposit->Amount;
			theInvestorAccount.DynamicRights-=pInvestorAccountDeposit->Amount;
/*** SIR XXXXX BEGIN ***/
			//出金后可用资金和结算准备金不能为负数
			//此需求暂时不启用
#if 0
			if (theInvestorAccount.Available < SMALL_DOUBLE)
#else
            if (false)
#endif
			{
				REPORT_EVENT(LOG_CRITICAL,"AccountDeposit","投资者账号[%s]出金[%f]元, 出金后可用资金[%f]为负数，出金失败\n",
					pInvestorAccountDeposit->AccountID.getValue(),pInvestorAccountDeposit->Amount.getValue(),theInvestorAccount.Available.getValue());
				
				//设置错误码，借用AccountInsideSeqNo字段
				pInvestorAccountDeposit->AccountInsideSeqNo = ERROR_DEPOSIT_AMOUNT_NOT_ENOUGH;
				success = false;
			}
			else
			{
			    std::string accountSeqNo( pInvestorAccountDeposit->AccountSeqNo.getValue() );
                if (INVESTORACCOUNTDEPOSIT_FROM_MONEYGATE == accountSeqNo[0])
                {
                	theInvestorAccount.ManualFrozen-=pInvestorAccountDeposit->Amount;//通过网关实现的出金要解冻临时冻结资金
                	theInvestorAccount.Available+=pInvestorAccountDeposit->Amount;//有效前面已经冻结过,解冻后要加回来
                }
                REPORT_EVENT(LOG_CRITICAL,"AccountDeposit","投资者账号[%s]出金[%f]元\n",pInvestorAccountDeposit->AccountID.getValue(),pInvestorAccountDeposit->Amount.getValue());
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
		///连续递增流水号+1
		m_DB->m_memTableItemInfo.InvestorAccountDepositCurrentMaxItem++;
		pInvestorAccountDeposit->AccountInsideSeqNo = m_DB->m_memTableItemInfo.InvestorAccountDepositCurrentMaxItem;
		pResDeposit->AccountInsideSeqNo = m_DB->m_memTableItemInfo.InvestorAccountDepositCurrentMaxItem;
/*** SIR XXXXX END ***/

		//出入金成功,写入 出入金流水表 
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


///同步数据库表客户资金帐户出入金的实现
///@param	pClientTradingID	要同步的客户资金帐户出入金信息
///@param	pTransaction	本操作属于的事务
///@return	true表示成功，false表示失败
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
		//上场只修改isActive和ClientRight字段
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
