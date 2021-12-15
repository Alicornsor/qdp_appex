/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company 上海量投网络科技有限公司
///@file CDbmtServiceBase.h
///@brief	实现了CDbmtServiceBase
///@history 
///20060113	xuzh		创建该文件
///20070725	xuzh		增加了DBMT日志
/////////////////////////////////////////////////////////////////////////

#include "CDbmtServiceBase.h"
#include "monitorIndex.h"
#include "databaseIteratorRepository.h"

static CEventMonitor eventMonitor;

CDbmtServiceBase::CDbmtServiceBase(CMemoryDB* pDB,CErrorEngine* pErrorEngine)
{
	m_DB=pDB;
	m_ErrorEngine=pErrorEngine;

	char *fileName;
	fileName=currentConfig->getConfig("DBMTLog");
	if (fileName[0]!='\0')
	{
		m_dbmtLog=mfopen(fileName,"w+t");
	}
	else
	{
		m_dbmtLog=NULL;
	}
}

CDbmtServiceBase::~CDbmtServiceBase(void)
{
	if (m_dbmtLog!=NULL)
	{
		fclose(m_dbmtLog);
	}
}

bool CDbmtServiceBase::isDuplicate(CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID)
{
	if (seqID>0)
	{
		map<CDbmtTopicIDType,CDbmtSequenceIDType>::iterator it;
		it=m_lastSeqMap.find(topicID);
		if (it==m_lastSeqMap.end())
		{
			///这个主题号是初次出现
			m_lastSeqMap.insert(pair<CDbmtTopicIDType,CDbmtSequenceIDType>(topicID,seqID));
			return false;
		}
		if (seqID<=it->second)
		{
			///小于等于上次的序列号，说明是重复的
			return true;
		}
		else
		{
			///设置上次的序列号
			it->second=seqID;
			return false;
		}
	}
	return false;
}


bool CDbmtServiceBase::suitableTime(void)
{
	return (getDataSyncStatus(m_DB)==DS_Synchronized);
}

/* 2013-11-27 longqy 这个函数是空函数，目前没有什么用 */
void CDbmtServiceBase::saveCommand(void *buffer, int len, int waitingSeqID, int tid)
{
	TCommand theCommand;
	theCommand.tid=tid;
	theCommand.buffer=new char[len];
	memcpy(theCommand.buffer,buffer,len);
	theCommand.len=len;	
}

bool CDbmtServiceBase::SyncInvestorAccountDeposit(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit,CAccountDepositResField *pResDeposit,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
									const TSessionRef &sessionRef,CTransaction *pTransaction)
{
/*** SIR XXXXX BEGIN ***/
    std::string accountSeqNo( pInvestorAccountDeposit->AccountSeqNo.getValue() );
    if ( accountSeqNo.size() < 3 )
    {//资金流水号格式错误
        printf("[ERR][%s]AccountSeqNo format error, eg A_1 or B_1\n", accountSeqNo.c_str());
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
    default:
    	//资金流水号格式错误
	printf("[ERR][%s]AccountSeqNo format error, eg A_1 or B_1\n", accountSeqNo.c_str());
	//用AccountInsideSeqNo将错误码返回
	pInvestorAccountDeposit->AccountInsideSeqNo = ERROR_DUPLICATE_DEPOSIT_FIELD;
	return false;  
	break;
    }
    /*if ( accountSeqNo[0] == INVESTORACCOUNTDEPOSIT_FROM_CHAIRMAN )
    {
        topicID = INVESTORACCOUNTDEPOSIT_TOPICID_CHAIRMAN;
    }
    else if ( accountSeqNo[0] == INVESTORACCOUNTDEPOSIT_FROM_FIELD )
    {
        topicID = INVESTORACCOUNTDEPOSIT_TOPICID_FIELD;
    }
    else
    {//资金流水号格式错误
        printf("[ERR][%s]AccountSeqNo format error, eg A_1 or B_1\n", accountSeqNo.c_str());
		//用AccountInsideSeqNo将错误码返回
		pInvestorAccountDeposit->AccountInsideSeqNo = ERROR_DUPLICATE_DEPOSIT_FIELD;
        return false;    
    }*/
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

	return SyncInvestorAccountDepositImpl(pInvestorAccountDeposit,pResDeposit,pTransaction);
}

bool CDbmtServiceBase::SyncInsUser(CWriteableUser *pUser,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	
	if (isDuplicate(topicID,seqID))
	{
		return false;
	}
	if (!suitableTime())
	{
		return false;
	}

	return SyncInsUserImpl(pUser,pTransaction);
}

bool CDbmtServiceBase::SyncInsUserImpl(CWriteableUser *pUser,CTransaction *pTransaction)
{
	char buffer[40960];
	pUser->dumpString(buffer);
	eventMonitor.report("InsUser","","",buffer);
	bool success=true;
	success=(m_DB->m_UserFactory->addByPK(pUser,pTransaction) != NULL);
	if (m_dbmtLog!=NULL)
	{
		if (success)
		{
			fprintf(m_dbmtLog,"%s,InsUser,success,",getCurrentTime(m_DB).getValue());
		}
		else
		{
			fprintf(m_dbmtLog,"%s,InsUser,failed,",getCurrentTime(m_DB).getValue());
		}
		pUser->dumpInLine(m_dbmtLog);
		fprintf(m_dbmtLog,"\n");
		fflush(m_dbmtLog);
	}
	return success;
}

bool CDbmtServiceBase::SyncUpdUser(CWriteableUser *pUser,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	
	if (isDuplicate(topicID,seqID))
	{
		return false;
	}
	if (!suitableTime())
	{
		return false;
	}

	return SyncUpdUserImpl(pUser,pTransaction);
}

bool CDbmtServiceBase::SyncUpdUserImpl(CWriteableUser *pUser,CTransaction *pTransaction)
{
	char buffer[40960];
	pUser->dumpString(buffer);
	eventMonitor.report("UpdUser","","",buffer);
	bool success=true;
	success=m_DB->m_UserFactory->updateByPK(pUser,pTransaction);
	if (m_dbmtLog!=NULL)
	{
		if (success)
		{
			fprintf(m_dbmtLog,"%s,UpdUser,success,",getCurrentTime(m_DB).getValue());
		}
		else
		{
			fprintf(m_dbmtLog,"%s,UpdUser,failed,",getCurrentTime(m_DB).getValue());
		}
		pUser->dumpInLine(m_dbmtLog);
		fprintf(m_dbmtLog,"\n");
		fflush(m_dbmtLog);
	}
	return success;
}

bool CDbmtServiceBase::SyncClientTradingID(CWriteableClientTradingID *pClientTradingID,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	
	if (!suitableTime())
	{
		return false;
	}

	return SyncClientTradingIDImpl(pClientTradingID,pTransaction);
}

bool CDbmtServiceBase::SyncUpdInvestorTradingRight(CWriteableInvestorTradingRight *pInvestorTradingRight,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	
	if (isDuplicate(topicID,seqID))
	{
		return false;
	}
	if (!suitableTime())
	{
		return false;
	}

	return SyncUpdInvestorTradingRightImpl(pInvestorTradingRight,pTransaction);
}

bool CDbmtServiceBase::SyncUpdInvestorTradingRightImpl(CWriteableInvestorTradingRight *pInvestorTradingRight,CTransaction *pTransaction)
{
	char buffer[40960];
	pInvestorTradingRight->dumpString(buffer);
	eventMonitor.report("UpdInvestorTradingRight","","",buffer);
	bool success=true;
	success=m_DB->m_InvestorTradingRightFactory->updateByPK(pInvestorTradingRight,pTransaction);
	if (m_dbmtLog!=NULL)
	{
		if (success)
		{
			fprintf(m_dbmtLog,"%s,UpdInvestorTradingRight,success,",getCurrentTime(m_DB).getValue());
		}
		else
		{
			fprintf(m_dbmtLog,"%s,UpdInvestorTradingRight,failed,",getCurrentTime(m_DB).getValue());
		}
		pInvestorTradingRight->dumpInLine(m_dbmtLog);
		fprintf(m_dbmtLog,"\n");
		fflush(m_dbmtLog);
	}
	return success;
}

bool CDbmtServiceBase::SyncInsInvestorTradingRight(CWriteableInvestorTradingRight *pInvestorTradingRight,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	
	if (isDuplicate(topicID,seqID))
	{
		return false;
	}
	if (!suitableTime())
	{
		return false;
	}

	return SyncInsInvestorTradingRightImpl(pInvestorTradingRight,pTransaction);
}

bool CDbmtServiceBase::SyncInsInvestorTradingRightImpl(CWriteableInvestorTradingRight *pInvestorTradingRight,CTransaction *pTransaction)
{
	char buffer[40960];
	pInvestorTradingRight->dumpString(buffer);
	eventMonitor.report("InsInvestorTradingRight","","",buffer);
	bool success=true;
	success=(m_DB->m_InvestorTradingRightFactory->addByPK(pInvestorTradingRight,pTransaction) != NULL);
	if (m_dbmtLog!=NULL)
	{
		if (success)
		{
			fprintf(m_dbmtLog,"%s,InsInvestorTradingRight,success,",getCurrentTime(m_DB).getValue());
		}
		else
		{
			fprintf(m_dbmtLog,"%s,InsInvestorTradingRight,failed,",getCurrentTime(m_DB).getValue());
		}
		pInvestorTradingRight->dumpInLine(m_dbmtLog);
		fprintf(m_dbmtLog,"\n");
		fflush(m_dbmtLog);
	}
	return success;
}

bool CDbmtServiceBase::SyncDelInvestorTradingRight(CWriteableInvestorTradingRight *pInvestorTradingRight,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	
	if (isDuplicate(topicID,seqID))
	{
		return false;
	}
	if (!suitableTime())
	{
		return false;
	}

	return SyncDelInvestorTradingRightImpl(pInvestorTradingRight,pTransaction);
}

bool CDbmtServiceBase::SyncDelInvestorTradingRightImpl(CWriteableInvestorTradingRight *pInvestorTradingRight,CTransaction *pTransaction)
{
	char buffer[40960];
	pInvestorTradingRight->dumpString(buffer);
	eventMonitor.report("DelInvestorTradingRight","","",buffer);
	bool success=true;
	success=m_DB->m_InvestorTradingRightFactory->removeByPK(pInvestorTradingRight,pTransaction);	
	if (m_dbmtLog!=NULL)
	{
		if (success)
		{
			fprintf(m_dbmtLog,"%s,DelInvestorTradingRight,success,",getCurrentTime(m_DB).getValue());
		}
		else
		{
			fprintf(m_dbmtLog,"%s,DelInvestorTradingRight,failed,",getCurrentTime(m_DB).getValue());
		}
		pInvestorTradingRight->dumpInLine(m_dbmtLog);
		fprintf(m_dbmtLog,"\n");
		fflush(m_dbmtLog);
	}
	return success;
}

bool CDbmtServiceBase::SyncUpdUserIP(CWriteableUserIP *pUserIP,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	
	if (isDuplicate(topicID,seqID))
	{
		return false;
	}
	if (!suitableTime())
	{
		return false;
	}

	return SyncUpdUserIPImpl(pUserIP,pTransaction);
}

bool CDbmtServiceBase::SyncUpdUserIPImpl(CWriteableUserIP *pUserIP,CTransaction *pTransaction)
{
	char buffer[40960];
	pUserIP->dumpString(buffer);
	eventMonitor.report("UpdUserIP","","",buffer);
	bool success=true;
	success=m_DB->m_UserIPFactory->updateByPK(pUserIP,pTransaction);
	if (m_dbmtLog!=NULL)
	{
		if (success)
		{
			fprintf(m_dbmtLog,"%s,UpdUserIP,success,",getCurrentTime(m_DB).getValue());
		}
		else
		{
			fprintf(m_dbmtLog,"%s,UpdUserIP,failed,",getCurrentTime(m_DB).getValue());
		}
		pUserIP->dumpInLine(m_dbmtLog);
		fprintf(m_dbmtLog,"\n");
		fflush(m_dbmtLog);
	}
	return success;
}

bool CDbmtServiceBase::SyncInsUserIP(CWriteableUserIP *pUserIP,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	
	if (isDuplicate(topicID,seqID))
	{
		return false;
	}
	if (!suitableTime())
	{
		return false;
	}

	return SyncInsUserIPImpl(pUserIP,pTransaction);
}

bool CDbmtServiceBase::SyncInsUserIPImpl(CWriteableUserIP *pUserIP,CTransaction *pTransaction)
{
	char buffer[40960];
	pUserIP->dumpString(buffer);
	eventMonitor.report("InsUserIP","","",buffer);
	bool success=true;
	success=(m_DB->m_UserIPFactory->addByPK(pUserIP,pTransaction) != NULL);
	if (m_dbmtLog!=NULL)
	{
		if (success)
		{
			fprintf(m_dbmtLog,"%s,InsUserIP,success,",getCurrentTime(m_DB).getValue());
		}
		else
		{
			fprintf(m_dbmtLog,"%s,InsUserIP,failed,",getCurrentTime(m_DB).getValue());
		}
		pUserIP->dumpInLine(m_dbmtLog);
		fprintf(m_dbmtLog,"\n");
		fflush(m_dbmtLog);
	}
	return success;
}

bool CDbmtServiceBase::SyncDelUserIP(CWriteableUserIP *pUserIP,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	
	if (isDuplicate(topicID,seqID))
	{
		return false;
	}
	if (!suitableTime())
	{
		return false;
	}

	return SyncDelUserIPImpl(pUserIP,pTransaction);
}

bool CDbmtServiceBase::SyncDelUserIPImpl(CWriteableUserIP *pUserIP,CTransaction *pTransaction)
{
	char buffer[40960];
	pUserIP->dumpString(buffer);
	eventMonitor.report("DelUserIP","","",buffer);
	bool success=true;
	success=m_DB->m_UserIPFactory->removeByPK(pUserIP,pTransaction);	
	if (m_dbmtLog!=NULL)
	{
		if (success)
		{
			fprintf(m_dbmtLog,"%s,DelUserIP,success,",getCurrentTime(m_DB).getValue());
		}
		else
		{
			fprintf(m_dbmtLog,"%s,DelUserIP,failed,",getCurrentTime(m_DB).getValue());
		}
		pUserIP->dumpInLine(m_dbmtLog);
		fprintf(m_dbmtLog,"\n");
		fflush(m_dbmtLog);
	}
	return success;
}

