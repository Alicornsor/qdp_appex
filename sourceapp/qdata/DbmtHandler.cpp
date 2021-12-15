// DbmtHandler.cpp: implementation of the CDbmtHandler class.
//
// 20061215 王维 增加DBMT指令CurrPriceBanding和CurrFuse
// 20070727 王维 删除部分DBMT指令
//                 修正读tbCommand的记录排序问题
//                 支持数据库断线重连
// 20070828 王维 调整日志的级别和分类
//                 修改异常退出的方式
// 20071010 王维 对于CommandNo不连续的DBMT指令，中间的缺口用TID_Nop
//                 填充，防止同一个指令多次发送。
// 20080618 王维 增加DbUpdateAllInstrumentStatus指令
// 20080623 王维 dbmt读到指令就直接发送，何时执行指令由交易核心决定
// 20080623 王维 NT-0033：每个dbmt命令增加序列号，与t_tbcommand中的
//                 CommandNo相同。
// 20081204 王维 NT-0033：定期检查指令是否上场会导致交易所和结算组之
///                间乱序,现改为读到指令马上检查上场（一定会通过检查）。
///20120424 林惜斌 交易编码权限上场指令添加
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "CachedFileFlow.h"
#include "XtpPackageDesc.h"
#include "CDate.h"
#include "DbmtHandler.h"
#include "FlowReader.h"

const int DBMT_TOPIC_ID = 1;
DWORD DBMT_PACKAGE_MODE = 5;

REGISTER_FIELD(0, TDbmtPackageHeader,"DbmtPackageHeader");

#define DEFINE_DBMT_COMMAND(operation, object)			\
{#operation#object, TID_##operation##object, &CDbmt##object##Field::m_Describe}

TDbmtCommandInfo g_dbmtCommandInfo[] = 
{
 	DEFINE_DBMT_COMMAND(DbUpd, User),
 	DEFINE_DBMT_COMMAND(DbIns, User),
 	DEFINE_DBMT_COMMAND(Db, InvestorAccountDeposit),
	DEFINE_DBMT_COMMAND(Db, ClientTradingID),
	DEFINE_DBMT_COMMAND(DbIns, InvestorTradingRight),
	DEFINE_DBMT_COMMAND(DbUpd, InvestorTradingRight),
	DEFINE_DBMT_COMMAND(DbDel, InvestorTradingRight),
	DEFINE_DBMT_COMMAND(DbIns, UserIP),
	DEFINE_DBMT_COMMAND(DbUpd, UserIP),
	DEFINE_DBMT_COMMAND(DbDel, UserIP),
//	{"DbUpdateAllInstrumentStatus", TID_DbUpdateAllInstrumentStatus, &CDbmtUpdateAllInstrumentStatusField::m_Describe},
//	{"DbAccountDeposit", TID_DbAccountDeposit, &CDbmtAccountDepositField::m_Describe},
//	DEFINE_DBMT_COMMAND(DbIns, Participant),
//	DEFINE_DBMT_COMMAND(DbUpd, Participant),
//	DEFINE_DBMT_COMMAND(DbDel, Participant),
// 	DEFINE_DBMT_COMMAND(DbIns, Client),
// 	DEFINE_DBMT_COMMAND(DbUpd, Client),
// //	DEFINE_DBMT_COMMAND(DbDel, Client),
// 	DEFINE_DBMT_COMMAND(DbIns, PartClient),
// 	DEFINE_DBMT_COMMAND(DbDel, PartClient),
// 	DEFINE_DBMT_COMMAND(DbIns, CurrPartPosiLimitDetail),
// 	DEFINE_DBMT_COMMAND(DbUpd, CurrPartPosiLimitDetail),
// 	DEFINE_DBMT_COMMAND(DbDel, CurrPartPosiLimitDetail),
// 	DEFINE_DBMT_COMMAND(DbIns, CurrClientPosiLimitDetail),
// 	DEFINE_DBMT_COMMAND(DbUpd, CurrClientPosiLimitDetail),
// 	DEFINE_DBMT_COMMAND(DbDel, CurrClientPosiLimitDetail),
// 	DEFINE_DBMT_COMMAND(DbIns, CurrSpecialPosiLimitDetail),
// 	DEFINE_DBMT_COMMAND(DbUpd, CurrSpecialPosiLimitDetail),
// 	DEFINE_DBMT_COMMAND(DbDel, CurrSpecialPosiLimitDetail),
// 	DEFINE_DBMT_COMMAND(DbIns, HedgeDetail),
// 	DEFINE_DBMT_COMMAND(DbIns, User),
// 	DEFINE_DBMT_COMMAND(DbDel, User),
// 	DEFINE_DBMT_COMMAND(DbIns, PartProductRight),
// 	DEFINE_DBMT_COMMAND(DbUpd, PartProductRight),
// 	DEFINE_DBMT_COMMAND(DbDel, PartProductRight),
// 	DEFINE_DBMT_COMMAND(DbIns, ClientProductRight),
// 	DEFINE_DBMT_COMMAND(DbUpd, ClientProductRight),
// 	DEFINE_DBMT_COMMAND(DbDel, ClientProductRight),
// 	DEFINE_DBMT_COMMAND(DbIns, PartInstrumentRight),
// 	DEFINE_DBMT_COMMAND(DbUpd, PartInstrumentRight),
// 	DEFINE_DBMT_COMMAND(DbDel, PartInstrumentRight),
// 	DEFINE_DBMT_COMMAND(DbIns, ClientInstrumentRight),
// 	DEFINE_DBMT_COMMAND(DbUpd, ClientInstrumentRight),
// 	DEFINE_DBMT_COMMAND(DbDel, ClientInstrumentRight),
// 	DEFINE_DBMT_COMMAND(DbIns, CurrMarginRateDetail),
// 	DEFINE_DBMT_COMMAND(DbUpd, CurrMarginRateDetail),
// 	DEFINE_DBMT_COMMAND(DbDel, CurrMarginRateDetail),
// 	DEFINE_DBMT_COMMAND(DbUpd, MarketData),
// 	DEFINE_DBMT_COMMAND(DbIns, UserIP),
// 	DEFINE_DBMT_COMMAND(DbDel, UserIP),
// 	DEFINE_DBMT_COMMAND(DbIns, CurrPriceBanding),
// 	DEFINE_DBMT_COMMAND(DbUpd, CurrPriceBanding),
// 	DEFINE_DBMT_COMMAND(DbDel, CurrPriceBanding),
// 	//交易编码权限上场－ huwp 20120420
// 	DEFINE_DBMT_COMMAND(DbIns, PartClientProductRight),
// 	DEFINE_DBMT_COMMAND(DbUpd, PartClientProductRight),
// 	DEFINE_DBMT_COMMAND(DbDel, PartClientProductRight),
// 	DEFINE_DBMT_COMMAND(DbIns, PartClientInstrumentRight),
// 	DEFINE_DBMT_COMMAND(DbUpd, PartClientInstrumentRight),
// 	DEFINE_DBMT_COMMAND(DbDel, PartClientInstrumentRight),
//	DEFINE_DBMT_COMMAND(DbIns, CurrFuse),
//	DEFINE_DBMT_COMMAND(DbUpd, CurrFuse),
//	DEFINE_DBMT_COMMAND(DbDel, CurrFuse),
	{NULL, 0, NULL}				//这一行一定要有，供加入map时判断是否最后一条记录
};

const int TIMER_CHECK_TBCOMMAND	= 2;

#define ReportDbError(msg) REPORT_EVENT(LOG_CRITICAL, "Database", "%s", msg)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDbmtHandler::CDbmtHandler(CReactor *pReactor, CDbConnection *pDbConnection,CFlow *pUnderFlow,int nCommandNo)
:CEventHandler(pReactor)
{
	m_nDbmtCount = 0;
	CDbmtPackage::InitCommandInfoMap(g_dbmtCommandInfo);
	m_pDbConnection = pDbConnection;
	m_pUnderFlow = pUnderFlow;
	m_saCommand.setConnection(m_pDbConnection);
	m_dbmtPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE, XTPHLEN);
	m_nDbmtCount = nCommandNo;
	memset(m_pSystemID,0,sizeof(m_pSystemID));
}

CDbmtHandler::~CDbmtHandler()
{

}

void CDbmtHandler::MySetTimer(int nElapse)
{
	SetTimer(TIMER_CHECK_TBCOMMAND, nElapse);
}

void CDbmtHandler::SetCommPhaseNo(WORD nCommPhaseNo)
{
 	m_TradingDay = CDate::LongToDate((long) nCommPhaseNo);
}

void CDbmtHandler::SetSystemID(char* pSystemID)
{
	strncpy(m_pSystemID,pSystemID,4);
}

int CDbmtHandler::CheckDbCommand()
{
	const char *pszSQL = "SELECT commandno,commanddate,commandtime,commandtype,fieldname,fieldcontent "\
						 "FROM t_sync_tbcommand WHERE CommandNo>:1 AND (SystemID=:2 OR SystemID=:3) ORDER BY CommandNo";
	int nRet = 0;
	try 
	{
		m_saCommand.setCommandText(pszSQL);
		m_saCommand.Param(1).setAsLong() = m_nDbmtCount;
		m_saCommand.Param(2).setAsString() = "0000";
		m_saCommand.Param(3).setAsString() = m_pSystemID;

		m_saCommand.Execute();
//		m_pDbConnection->Commit();
		
		nRet = LoadDbCommand();		
	}
	catch(SAException &x)
	{
		try
		{
			m_pDbConnection->CheckConntectionError(x.ErrNativeCode());
			// on error rollback changes
			m_pDbConnection->Rollback();
		}
		catch(SAException &)
		{
		}
		ReportDbError((const char*)x.ErrText());
	}

	return nRet;
}

int CDbmtHandler::LoadDbCommand()
{
	CFieldNameType FieldName;
	CFieldContentType FieldContent;
	int nSendCount = 0;
	for (;;nSendCount++)
	{
		if (!m_saCommand.FetchNext())
		{
			break;
		}
		m_dbmtPackage.SetCommandType(CCommandTypeType(m_saCommand.Field("CommandType").asString()));

		int nCommandNo = m_saCommand.Field("CommandNo").asLong();
		int nExceptedCommandNo = m_nDbmtCount+1;
		if (nCommandNo != nExceptedCommandNo)
		{
			REPORT_EVENT(LOG_ERROR, "DbCommand", "CommandNo gap [%d]-[%d]",nExceptedCommandNo, nCommandNo);
		}
		while (nCommandNo > m_nDbmtCount)
		{
			//如果不足，需要补0，直到到这个号为止
			nExceptedCommandNo = m_nDbmtCount+1;
			m_dbmtPackage.SetCommandNo(nExceptedCommandNo);
			if (nCommandNo != nExceptedCommandNo)
			{
				m_dbmtPackage.PreparePublish(TID_Nop);
			}
			else
			{
				REPORT_EVENT(LOG_CRITICAL, "DbCommand", "read dbmt package %s", (const char *)m_dbmtPackage.GetCommandType()); 
				FieldName = (const char *)m_saCommand.Field("FieldName").asString();
				FieldContent = (const char *)m_saCommand.Field("FieldContent").asString();
				//补充序号
				char *pszFieldName = (char *)FieldName.getValue();
				strcat(pszFieldName, ",\"DbmtTopicID\",\"DbmtSequenceID\"");
				char *pszFieldContent = (char *)FieldContent.getValue();
				sprintf(pszFieldContent+strlen(pszFieldContent), ",\"%d\",\"%d\"", DBMT_TOPIC_ID, nCommandNo);
				
				if(!m_dbmtPackage.AnalysisRecord(pszFieldName, pszFieldContent))
				{
					REPORT_EVENT(LOG_ERROR, "DbCommand", "AnalysisRecord error, CommandNo=[%d]",m_dbmtPackage.GetCommandNo().getValue());
					m_dbmtPackage.PreparePublish(TID_Nop);
				}
			}			
			m_dbmtPackage.MakePackage();
			m_pUnderFlow->Append(m_dbmtPackage.Address(), m_dbmtPackage.Length());
			m_nDbmtCount ++;
		}
	}
	return nSendCount;
}

void CDbmtHandler::OnTimer(int nIDEvent)
{
	if (nIDEvent == TIMER_CHECK_TBCOMMAND)
	{
		if (!m_pDbConnection->isConnected())
		{
			m_pDbConnection->ConnectDB();
			if (!m_pDbConnection->isConnected())
			{
				REPORT_EVENT(LOG_ERROR, "Database", "DBMT Database Reconnect Error");
				return;
			}
		}
		CheckDbCommand();
	}
}
