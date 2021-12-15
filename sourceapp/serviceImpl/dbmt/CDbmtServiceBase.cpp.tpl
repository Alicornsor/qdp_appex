!!enter XTP!!
!!function!!
#include <string>
#include <vector>
using namespace std;

int isDbmtPackage(char *name)
{
	if (!strncmp(name,"dbmt",4))
	{
		return 1;
	}
	return 0;
}

char *getTableName(char *name)
{
	return name+2;
}

char *getRecordName(char *name)
{
	return name+4;
}

int getOperatorType(char *name)
{
	if(strncmp(name,"Ins",3) == 0)
		return 1;		///insert
	if(strncmp(name,"Upd",3) == 0)
		return 2;		///Update
	if(strncmp(name,"Del",3) == 0)
		return 3;		///Delete
	return 0;
}

vector<char *> sgDbmtCommands;

void addSgDbmtCommand(char * command)
{
	sgDbmtCommands.push_back(command);
}

bool isSgDbmtCommand(char *command)
{
	if (!strcmp(command,"UpdMarketData"))
	{
		return false;
	}
	vector<char *>::iterator it;
	for (it=sgDbmtCommands.begin();it!=sgDbmtCommands.end();it++)
	{
		if (!strcmp(*it,command))
		{
			return true;
		}
	}
	return false;
}

!!endfunction!!
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

!!** 判断是否由结算组控制的dbmt命令!!
!!travel packages!!
	!!if isDbmtPackage(@usage)!!
		!!let tableName=getTableName(@name)!!
		!!travel self!!
			!!let fieldName=@name!!
			!!enter XTP!!
				!!travel fields!!
					!!if !strcmp(@name,@fieldName)!!
						!!travel self!!
							!!if !strcmp(@name,"SettlementGroupID")!!
								!!command addSgDbmtCommand(@tableName)!!
							!!endif!!
						!!next!!
					!!endif!!
				!!next!!
			!!leave!!
		!!next!!
	!!endif!!
!!next!!

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

!!travel packages!!
!!if isDbmtPackage(@usage)!!
!!let tableName=getTableName(@name)!!
!!travel self!!
!!let recordName=getRecordName(@name)!!
!!if (strcmp("ClientTradingID",@recordName) && strcmp("InvestorAccountDeposit",@recordName))!!
bool CDbmtServiceBase::Sync!!@tableName!!(CWriteable!!@recordName!! *p!!@recordName!!,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction)
{	

	if (isDuplicate(topicID,seqID))
	{
		return false;
	}

	!!if isSgDbmtCommand(@tableName)!!
	if (!suitableTime(p!!@recordName!!->SettlementGroupID))
	!!else!!
	if (!suitableTime())
	!!endif!!
	{
		return false;
	}

	return Sync!!@tableName!!Impl(p!!@recordName!!,pTransaction);
}


bool CDbmtServiceBase::Sync!!@tableName!!Impl(CWriteable!!@recordName!! *p!!@recordName!!,CTransaction *pTransaction)
{
	char buffer[40960];
	p!!@recordName!!->dumpString(buffer);
	eventMonitor.report("!!@tableName!!","","",buffer);
!!if (strcmp(@recordName,"HedgeDetail") == 0)!!
	return true;
!!else!!
	bool success=true;
!!if (getOperatorType(@tableName) == 1)!!
	success=(m_DB->m_!!@recordName!!Factory->addByPK(p!!@recordName!!,pTransaction) != NULL);
!!endif
!!if(getOperatorType(@tableName) == 2)!!
	success=m_DB->m_!!@recordName!!Factory->updateByPK(p!!@recordName!!,pTransaction);
!!endif
!!if(getOperatorType(@tableName) == 3)!!
	success=m_DB->m_!!@recordName!!Factory->removeByPK(p!!@recordName!!,pTransaction);	
!!endif!!
	if (m_dbmtLog!=NULL)
	{
		if (success)
		{
			fprintf(m_dbmtLog,"%s,!!@tableName!!,success,",getCurrentTime(m_DB).getValue());
		}
		else
		{
			fprintf(m_dbmtLog,"%s,!!@tableName!!,failed,",getCurrentTime(m_DB).getValue());
		}
		p!!@recordName!!->dumpInLine(m_dbmtLog);
		fprintf(m_dbmtLog,"\n");
		fflush(m_dbmtLog);
	}
	return success;
!!endif!!	
}

!!endif!!

!!next!!
!!endif!!
!!next!!
!!leave!!