/////////////////////////////////////////////////////////////////////////
///@system ���ٷ��ǰ��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file LogMemoryDatabaseTable.cpp
///@brief��������LogMemoryDatabaseTable����ÿ�β�ѯ�ڴ����ݿ�ı��¼д����־
///			����ֻ࣬���ڵ��Ե�ʱ�����á��ڳ�����ʽ���ߺ󣬿��Բ�������־�ļ�����
///			����ļ�¼��־�����¼����д����־�ļ�������������Ӱ���ѯ���ܡ�
///@history 
///20130114	longqy@cffex.net �����ļ�
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

/*	logCurrentTime �ѵ�ǰ��ʱ��д����־�ļ���
//  ���λ��ʱ�侫����΢��
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
	// �Ự��ID���޷��ŵ��������� llu��ʽ�����
	fprintf(m_fQueryLog,"Current time  %02d:%02d:%02d:ms %03d:us %03d \n",hours,minutes,seconds,milliSecs,microSecs);
	fflush(m_fQueryLog);
}

/* ����initMapΪ��Ա�������ù̶�ֵ���ѱ������ӳ��Ϊö������ */
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


/*	logField �����Ѳ�ѯ�����д����־�ļ��������־�ļ�����unquery.ini������QuerylogPathָ���ġ�
//  ���û����������������򲻻�Ѳ�ѯ���д����־��
//  pField 		���������ָ��ѯ�����
//  sTableName	�����������ѯ�ı�����
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
		// �ӿͻ��˽ӿڲ�ѯ����InvestorPosition�������ڴ����ݿ����ǲ�ѯClientPosition���
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
		
	// �Ự��ID���޷��ŵ��������� ld��ʽ�����
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
