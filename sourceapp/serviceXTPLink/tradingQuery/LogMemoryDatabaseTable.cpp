/////////////////////////////////////////////////////////////////////////
///@system 极速风控前置系统
///@company 上海量投网络科技有限公司
///@file LogMemoryDatabaseTable.cpp
///@brief定义了类LogMemoryDatabaseTable，把每次查询内存数据库的表记录写入日志
///			这个类，只是在调试的时候有用。在程序正式上线后，可以不配置日志文件，则
///			本类的记录日志不会记录，不写入日志文件。这样，不会影响查询性能。
///@history 
///20130114	longqy@cffex.net 创建文件
/////////////////////////////////////////////////////////////////////////

#include "LogMemoryDatabaseTable.h"

CLogMemoryDatabaseTable	g_logMemoryDBTable;

CLogMemoryDatabaseTable::CLogMemoryDatabaseTable()
{
	initMap();
}

CLogMemoryDatabaseTable::~CLogMemoryDatabaseTable()
{
	if (m_fQueryLog != NULL)
	{
		fclose(m_fQueryLog);
	}
}

void CLogMemoryDatabaseTable::init()
{
	if(NULL == m_fQueryLog)
	{
		char *logFilename = currentConfig->getConfig("QuerylogPath");
		if ((logFilename !=NULL )&&(*logFilename != '\0'))
		{
			m_fQueryLog = mfopen(logFilename,"w+t");
		}
	}
}

/*	logCurrentTime 把当前的时间写入日志文件。
//  最低位的时间精度是微妙
*/
void CLogMemoryDatabaseTable::logCurrentTime()
{
	if (m_fQueryLog == NULL)
	{
		return;
	}
	long nCurrentTime;
	GET_ACCURATE_USEC_TIME(nCurrentTime);
	long logTime = nCurrentTime;
	int microSecs = logTime%1000;
	logTime /= 1000;
	int milliSecs = logTime%1000;
	logTime /= 1000;
	int seconds = logTime%60;
	logTime /= 60;
	int minutes = logTime%60;
	logTime /= 60;
	int hours = logTime%24;
	// 会话的ID是无符号的整数，用 llu格式输出。
	fprintf(m_fQueryLog,"Current time  %02d:%02d:%02d:ms %03d:us %03d \n",hours,minutes,seconds,milliSecs,microSecs);
	fflush(m_fQueryLog);
}

/* 函数initMap为成员变量设置固定值，把表的名字映射为枚举类型 */
void CLogMemoryDatabaseTable::initMap()
{
/*
	m_mMemTableLog["Order"] = ORDER;
	m_mMemTableLog["Trade"] = TRADE;
	m_mMemTableLog["InvestorPosition"] = INVESTORPOSITION;
	m_mMemTableLog["Instrument"] = INSTRUMENT;
	m_mMemTableLog["ClientTradingID"]= CLIENTTRADINGID;
	m_mMemTableLog["Exchange"] = EXCHANGE;
	m_mMemTableLog["InvestorAccount"] = INVESTORACCOUNT;
	m_mMemTableLog["UserInvestor"] = USERINVESTOR;
	m_mMemTableLog["ComplianceParam"] = COMPLIANCEPARAM;
*/	
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("Order" , ORDER));
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("Trade" , TRADE));
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("InvestorPosition" , INVESTORPOSITION));
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("Instrument" , INSTRUMENT));
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("MarketData" , MARKETDATA));
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("ClientTradingID" , CLIENTTRADINGID));
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("Exchange" , EXCHANGE));
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("InvestorAccount" , INVESTORACCOUNT));
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("UserInvestor" , USERINVESTOR));
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("ComplianceParam" , COMPLIANCEPARAM));
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("UserSession" , USERSESSION));
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("InvestorFee" , INVESTORFEE));
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("InvestorMargin" , INVESTORMARGIN));
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("ExchTimeDiff" , EXCHTIMEDIFF));
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("BankAcc" , BANKACC));
	m_mMemTableLog.insert(map<string,MemTableIDType>::value_type("BFTransferInterface" , BFTRANSFERINTERFACE));
}


/*	logField 函数把查询结果，写入日志文件。这个日志文件是由unquery.ini配置项QuerylogPath指定的。
//  如果没有配置这个参数，则不会把查询结果写入日志。
//  pField 		输入参数，指查询结果域
//  sTableName	输入参数，查询的表名字
*/
void CLogMemoryDatabaseTable::logField(void *pField,char *sTableName,LogOperateType nLogOperate)
{
	MemTableIDType nTableID = NO_TABLE;
	map<string,MemTableIDType>::iterator itor = m_mMemTableLog.find(sTableName);
	if(itor == m_mMemTableLog.end())
	{
		nTableID = NO_TABLE;
	}else
	{
		nTableID = itor->second;
	}
	
	char sBuffer[4000];
	memset(sBuffer, 0, 4000);
	const char *sQuery = "Query table:";
	const char *sInsert = "Insert table:";
	const char *sUpdate = "Update table:";
	char *sOperate;

	if (m_fQueryLog == NULL)
	{
		return;
	}

	switch ( nLogOperate )
	{
		case LOG_INSERT:
		{
			sOperate = (char *)sInsert;
			break;
		}
		case LOG_QUERY:
		{
			sOperate = (char *)sQuery;
			break;
		}
		case LOG_UPDATE:
		{
			sOperate = (char *)sUpdate;
			break;
		}
		default:
			printf("Error, CLogMemoryDatabaseTable::logField LogOperate value invalid. \n");
			break;
	}	
	
	switch ( nTableID )
	{
		case ORDER:
		{
			logCurrentTime();
			fprintf(m_fQueryLog,"%s: %s result records \n", sOperate,sTableName);
			COrderField *pTable = (COrderField *)pField;
			pTable->dumpLine(sBuffer,4000);
			fprintf(m_fQueryLog," %s \n\n", sBuffer);
			fflush(m_fQueryLog);
			break;
		}
		case TRADE:
		{
			logCurrentTime();
			fprintf(m_fQueryLog,"%s: %s result records \n", sOperate,sTableName);
			CTradeField *pTable = (CTradeField *)pField;
			pTable->dumpLine(sBuffer,4000);
			fprintf(m_fQueryLog," %s \n\n", sBuffer);
			fflush(m_fQueryLog);
			break;
		}
		// 从客户端接口查询的是InvestorPosition，但是内存数据库中是查询ClientPosition表格。
		case INVESTORPOSITION:
		{
			logCurrentTime();
			fprintf(m_fQueryLog,"%s: %s result records \n", sOperate,sTableName);
			CInvestorPositionField *pTable = (CInvestorPositionField *)pField;
			pTable->dumpLine(sBuffer,4000);
			fprintf(m_fQueryLog," %s \n\n", sBuffer);
			fflush(m_fQueryLog);
			break;
		}
		case INSTRUMENT:
		{
			logCurrentTime();
			fprintf(m_fQueryLog,"%s: %s result records \n", sOperate,sTableName);
			CInstrumentField *pTable = (CInstrumentField *)pField;
			pTable->dumpLine(sBuffer,4000);
			fprintf(m_fQueryLog," %s \n\n", sBuffer);
			fflush(m_fQueryLog);
			break;
		}
		case MARKETDATA:
		{
			logCurrentTime();
			fprintf(m_fQueryLog,"%s: %s result records \n", sOperate,sTableName);
			CMarketDataField *pTable = (CMarketDataField *)pField;
			pTable->dumpLine(sBuffer,4000);
			fprintf(m_fQueryLog," %s \n\n", sBuffer);
			fflush(m_fQueryLog);
			break;
		}
		case CLIENTTRADINGID:
		{
			logCurrentTime();
			fprintf(m_fQueryLog,"%s: %s result records \n", sOperate,sTableName);
			CClientTradingIDField *pTable = (CClientTradingIDField *)pField;
			pTable->dumpLine(sBuffer,4000);
			fprintf(m_fQueryLog," %s \n\n", sBuffer);
			fflush(m_fQueryLog);
			break;
		}
		case EXCHANGE:
		{
			logCurrentTime();
			fprintf(m_fQueryLog,"%s: %s result records \n", sOperate,sTableName);
			CExchangeField *pTable = (CExchangeField *)pField;
			pTable->dumpLine(sBuffer,4000);
			fprintf(m_fQueryLog," %s \n\n", sBuffer);
			fflush(m_fQueryLog);
			break;
		}
		case INVESTORACCOUNT:
		{
			logCurrentTime();
			fprintf(m_fQueryLog,"%s: %s result records \n", sOperate,sTableName);
			CInvestorAccountField *pTable = (CInvestorAccountField *)pField;
			pTable->dumpLine(sBuffer,4000);
			fprintf(m_fQueryLog," %s \n\n", sBuffer);
			fflush(m_fQueryLog);
			break;
		}
		case USERINVESTOR:
		{
			logCurrentTime();
			fprintf(m_fQueryLog,"%s: %s result records \n", sOperate,sTableName);
			CUserInvestorField *pTable = (CUserInvestorField *)pField;
			pTable->dumpLine(sBuffer,4000);
			fprintf(m_fQueryLog," %s \n\n", sBuffer);
			fflush(m_fQueryLog);
			break;
		}
		case USERSESSION:
		{
			logCurrentTime();
			fprintf(m_fQueryLog,"%s: %s result records \n", sOperate,sTableName);
			CUserSessionField *pTable = (CUserSessionField *)pField;
			pTable->dumpLine(sBuffer,4000);
			fprintf(m_fQueryLog," %s \n\n", sBuffer);
			fflush(m_fQueryLog);
			break;
		}
		case INVESTORFEE:
		{
			logCurrentTime();
			fprintf(m_fQueryLog,"%s: %s result records \n", sOperate,sTableName);
			CInvestorFeeField *pTable = (CInvestorFeeField *)pField;
			pTable->dumpLine(sBuffer,4000);
			fprintf(m_fQueryLog," %s \n\n", sBuffer);
			fflush(m_fQueryLog);
			break;
		}
		case INVESTORMARGIN:
		{
			logCurrentTime();
			fprintf(m_fQueryLog,"%s: %s result records \n", sOperate,sTableName);
			CInvestorMarginField *pTable = (CInvestorMarginField *)pField;
			pTable->dumpLine(sBuffer,4000);
			fprintf(m_fQueryLog," %s \n\n", sBuffer);
			fflush(m_fQueryLog);
			break;
		}
		default:
			break;
	}
}

void CLogMemoryDatabaseTable::logQuery(const TSessionRef &sessionRef,long startTime,long endTime,char *queryInfo)
{
	if (m_fQueryLog == NULL)
	{
		return;
	}
	int nElapsedTime = endTime-startTime;

	long logTime = startTime;
	int microSecs = logTime%1000;
	logTime /= 1000;
	int milliSecs = logTime%1000;
	logTime /= 1000;
	int seconds = logTime%60;
	logTime /= 60;
	int minutes = logTime%60;
	logTime /= 60;
	int hours = logTime%24;
	long nSessionID = sessionRef.SessionID.getValue();
		
	// 会话的ID是无符号的整数，用 ld格式输出。
	fprintf(m_fQueryLog,"%02d:%02d:%02d:ms %03d:us %03d,Time Elapsed us:%d , SessionID: %ld, %s\n\n",
		                hours,minutes,seconds,milliSecs,microSecs,nElapsedTime,
		nSessionID,queryInfo);
	fflush(m_fQueryLog);
}

bool CLogMemoryDatabaseTable::canLog()
{
	if (NULL == m_fQueryLog)
	{
		return false;
	}
	else
	{
		return true;
	}
}
