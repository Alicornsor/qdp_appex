// DbmtHandler.cpp: implementation of the CDbmtHandler class.
//
// 20061215 ��ά ����DBMTָ��CurrPriceBanding��CurrFuse
// 20070727 ��ά ɾ������DBMTָ��
//                 ������tbCommand�ļ�¼��������
//                 ֧�����ݿ��������
// 20070828 ��ά ������־�ļ���ͷ���
//                 �޸��쳣�˳��ķ�ʽ
// 20071010 ��ά ����CommandNo��������DBMTָ��м��ȱ����TID_Nop
//                 ��䣬��ֹͬһ��ָ���η��͡�
// 20080618 ��ά ����DbUpdateAllInstrumentStatusָ��
// 20080623 ��ά dbmt����ָ���ֱ�ӷ��ͣ���ʱִ��ָ���ɽ��׺��ľ���
// 20080623 ��ά NT-0033��ÿ��dbmt�����������кţ���t_tbcommand�е�
//                 CommandNo��ͬ��
// 20081204 ��ά NT-0033�����ڼ��ָ���Ƿ��ϳ��ᵼ�½������ͽ�����֮
///                ������,�ָ�Ϊ����ָ�����ϼ���ϳ���һ����ͨ����飩��
///20120424 ��ϧ�� ���ױ���Ȩ���ϳ�ָ�����
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
// 	//���ױ���Ȩ���ϳ��� huwp 20120420
// 	DEFINE_DBMT_COMMAND(DbIns, PartClientProductRight),
// 	DEFINE_DBMT_COMMAND(DbUpd, PartClientProductRight),
// 	DEFINE_DBMT_COMMAND(DbDel, PartClientProductRight),
// 	DEFINE_DBMT_COMMAND(DbIns, PartClientInstrumentRight),
// 	DEFINE_DBMT_COMMAND(DbUpd, PartClientInstrumentRight),
// 	DEFINE_DBMT_COMMAND(DbDel, PartClientInstrumentRight),
//	DEFINE_DBMT_COMMAND(DbIns, CurrFuse),
//	DEFINE_DBMT_COMMAND(DbUpd, CurrFuse),
//	DEFINE_DBMT_COMMAND(DbDel, CurrFuse),
	{NULL, 0, NULL}				//��һ��һ��Ҫ�У�������mapʱ�ж��Ƿ����һ����¼
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
			//������㣬��Ҫ��0��ֱ���������Ϊֹ
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
				//�������
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
