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
///@system ��������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CDbmtServiceBase.h
///@brief	������CDbmtServiceBase
///@history 
///20060113	xuzh		�������ļ�
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
///����������ڻ���ϯ
#define INVESTORACCOUNTDEPOSIT_TOPICID_CHAIRMAN      "9001"
#define INVESTORACCOUNTDEPOSIT_FROM_CHAIRMAN         'A'
#define INVESTORACCOUNTDEPOSIT_FROM_MONEYGATE        'M'

///��������Գ���
#define INVESTORACCOUNTDEPOSIT_TOPICID_FIELD         "9002"
#define INVESTORACCOUNTDEPOSIT_FROM_FIELD            'B'
/*** SIR XXXXX END ***/

///��������Գ�������
#define INVESTORACCOUNTDEPOSIT_TOPICID_Netting       "9003"
#define INVESTORACCOUNTDEPOSIT_FROM_Netting           'C'
/////////////////////////////////////////////////////////////////////////
///CDbmtServiceBase��һ���������ͬ����������
///�ڴ����ݿ������
///@author	xuzh
///@version	1.0,20060113
///////////////////////////////////////////////////////////////////////// 
class CDbmtServiceBase
{
public:
	///���췽��
	///@param	pDB	ָ�����ڴ����ݿ�
	///@param	pErrorEngine	ָ���Ĵ�������
	CDbmtServiceBase(CMemoryDB *pDB, CErrorEngine *pErrorEngine);

	///��������
	virtual ~CDbmtServiceBase(void);
	
public:
!!travel packages!!
!!if isDbmtPackage(@usage)!!
!!let tableName=getTableName(@name)!!
!!travel self!!
!!let recordName=getRecordName(@name)!!
!!if (strcmp("ClientTradingID",@recordName) && strcmp("InvestorAccountDeposit",@recordName))!!	
	///ͬ�����ݿ��!!@comment!!
	///@param	p!!@tableName!!	Ҫͬ����!!@comment!!��Ϣ
	///@param	topicID	DBMT�������
	///@param	seqID	DBMT�����к�
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool Sync!!@tableName!!(CWriteable!!@recordName!! *p!!@recordName!!,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///ͬ�����ݿ��!!@comment!!��ʵ��
	///@param	p!!@tableName!!	Ҫͬ����!!@comment!!��Ϣ
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool Sync!!@tableName!!Impl(CWriteable!!@recordName!! *p!!@recordName!!,CTransaction *pTransaction);
!!endif!!
!!next!!
!!endif!!
!!next!! 

protected:
	///����Ƿ��ظ������кţ�������ظ������޸����ӳ���
	///@param	topicID	����ʹ�õ������
	///@param	seqID	����ʹ�õ����к�
	///@return	true��ʾ���ظ��ģ�false��ʾ���ظ�
	bool isDuplicate(CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID);

	///���ڽ�������ͬ��ָ�Ŀǰ�Ƿ���ʵĴ���ʱ��
	///@return	true��ʾ���ʣ�false��ʾ������
	bool suitableTime(void);

	///����ͬ��ָ������Ժ���ʵ�ʱ���ٴ���
	///@param	buffer	ָ��Ļ�����
	///@param	len	ָ��ĳ���
	///@param	waitingSeqID	�ȴ����к�
	///@param	tid	ָ���tid
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
