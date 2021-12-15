!!enter XTP!!
!!function!!
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

!!endfunction!!
/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company 上海量投网络科技有限公司
///@file CDbmtServiceBase.h
///@brief	定义了CDbmtServiceBase
///@history 
///20060113	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CDBMTSERVICEBASE_H
#define CDBMTSERVICEBASE_H

#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "XtpPackageDesc.h"
#include "CErrorEngine.h"
#include "tradingTools.h"

extern CConfig *currentConfig;

/*** SIR XXXXX BEGIN ***/
///出入金来自期货主席
#define INVESTORACCOUNTDEPOSIT_TOPICID_CHAIRMAN      "9001"
#define INVESTORACCOUNTDEPOSIT_FROM_CHAIRMAN         'A'
#define INVESTORACCOUNTDEPOSIT_FROM_MONEYGATE        'M'

///出入金来自场下
#define INVESTORACCOUNTDEPOSIT_TOPICID_FIELD         "9002"
#define INVESTORACCOUNTDEPOSIT_FROM_FIELD            'B'
/*** SIR XXXXX END ***/

///出入金来自场下轧差
#define INVESTORACCOUNTDEPOSIT_TOPICID_Netting       "9003"
#define INVESTORACCOUNTDEPOSIT_FROM_Netting           'C'
/////////////////////////////////////////////////////////////////////////
///CDbmtServiceBase是一个完成数据同步工作的类
///内存数据库的数据
///@author	xuzh
///@version	1.0,20060113
///////////////////////////////////////////////////////////////////////// 
class CDbmtServiceBase
{
public:
	///构造方法
	///@param	pDB	指定的内存数据库
	///@param	pErrorEngine	指定的错误引擎
	CDbmtServiceBase(CMemoryDB *pDB, CErrorEngine *pErrorEngine);

	///析构方法
	virtual ~CDbmtServiceBase(void);
	
public:
!!travel packages!!
!!if isDbmtPackage(@usage)!!
!!let tableName=getTableName(@name)!!
!!travel self!!
!!let recordName=getRecordName(@name)!!
!!if (strcmp("ClientTradingID",@recordName) && strcmp("InvestorAccountDeposit",@recordName))!!	
	///同步数据库表!!@comment!!
	///@param	p!!@tableName!!	要同步的!!@comment!!信息
	///@param	topicID	DBMT的主题号
	///@param	seqID	DBMT的序列号
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool Sync!!@tableName!!(CWriteable!!@recordName!! *p!!@recordName!!,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///同步数据库表!!@comment!!的实现
	///@param	p!!@tableName!!	要同步的!!@comment!!信息
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool Sync!!@tableName!!Impl(CWriteable!!@recordName!! *p!!@recordName!!,CTransaction *pTransaction);
!!endif!!
!!next!!
!!endif!!
!!next!! 

protected:
	///检查是否重复的序列号，如果不重复，则修改相关映射表
	///@param	topicID	本次使用的主题号
	///@param	seqID	本次使用的序列号
	///@return	true表示是重复的，false表示不重复
	bool isDuplicate(CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID);

	///对于交易所的同步指令，目前是否合适的处理时间
	///@return	true表示合适，false表示不合适
	bool suitableTime(void);

	///保存同步指令，用于以后合适的时间再处理
	///@param	buffer	指令的缓冲区
	///@param	len	指令的长度
	///@param	waitingSeqID	等待序列号
	///@param	tid	指令的tid
	void saveCommand(void *buffer, int len, int waitingSeqID, int tid);

	CMemoryDB *m_DB;
	CErrorEngine *m_ErrorEngine;
	FILE *m_dbmtLog;
	map<CDbmtTopicIDType,CDbmtSequenceIDType> m_lastSeqMap;
	int m_waitingSeqID;
	typedef struct
	{
		int tid;
		void *buffer;
		int len;
	}	TCommand;
};

#endif
!!leave!!
