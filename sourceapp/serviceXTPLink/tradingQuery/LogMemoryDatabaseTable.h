/////////////////////////////////////////////////////////////////////////
///@system ���ٷ��ǰ��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file LogMemoryDatabaseTable.h
///@brief��������LogMemoryDatabaseTable�����ڴ����ݿ�ı�д����־
///@history 
///20130114	longqy@cffex.net �����ļ�
/////////////////////////////////////////////////////////////////////////
#ifndef LOGMEMORYDATABASETABLE_H
#define LOGMEMORYDATABASETABLE_H

#include "CTransaction.h"
#include "ServiceXTPLink.h"
#include "CConfig.h"

#include "XtpPackageDesc.h"
#include "UFCopy.h"

enum MemTableIDType{
	NO_TABLE,
	ORDER,
	TRADE,
	INVESTORPOSITION,
	INSTRUMENT,
	MARKETDATA,
	CLIENTTRADINGID,
	EXCHANGE,
	INVESTORACCOUNT,
	USERINVESTOR,
	COMPLIANCEPARAM,
	USERSESSION,
	INVESTORFEE,
	INVESTORMARGIN,
	EXCHTIMEDIFF,
	BANKACC,
	BFTRANSFERINTERFACE
};

enum LogOperateType{
	NO_OPERATE,
	LOG_INSERT,
	LOG_UPDATE,
	LOG_DELETE,
	LOG_QUERY
};


class CLogMemoryDatabaseTable
{
public:
	CLogMemoryDatabaseTable();
	~CLogMemoryDatabaseTable();
	void logField(void *pField,char *sTableName,LogOperateType nLogOperate);
	void logCurrentTime();
	void logQuery(const TSessionRef &sessionRef,long startTime,long endTime,char *queryInfo);
	bool canLog();
	void init();

private:
	void initMap();

	map<string,MemTableIDType> m_mMemTableLog;
	FILE *m_fQueryLog;	
};

#endif
