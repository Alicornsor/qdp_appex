/////////////////////////////////////////////////////////////////////////
///@system 极速风控前置系统
///@company 上海量投网络科技有限公司
///@file LogMemoryDatabaseTable.h
///@brief定义了类LogMemoryDatabaseTable，把内存数据库的表写入日志
///@history 
///20130114	longqy@cffex.net 创建文件
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
