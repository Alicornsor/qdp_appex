// DbmtHandler.cpp: implementation of the CDbmtHandler class.
//
// 20070828 王维 调整日志的级别和分类
//                 修改异常退出的方式
// 20080623 王维 NT-0033：每个dbmt命令增加序列号，与dfmt文件中的
//                 CommandNo相同。
// 20081204 王维 NT-0033：定期检查指令是否上场会导致交易所和结算组之
///                间乱序,现改为读到指令马上检查上场（一定会通过检查）。
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "CachedFileFlow.h"
#include "FlowReader.h"
#include "XtpPackageDesc.h"
#include "CDate.h"
#include "DfmtHandler.h"

const int DFMT_TOPIC_ID = 2;

//REGISTER_FIELD(0, TDbmtPackageHeader,"DbmtPackageHeader");

#define DEFINE_DBMT_COMMAND(operation, object)			\
{#operation#object, TID_##operation##object, &C##object##Field::m_Describe}

extern TDbmtCommandInfo g_dbmtCommandInfo[];
int TIMER_CHECK_DFCOMMAND	= 1;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDfmtHandler::CDfmtHandler(CReactor *pReactor, const char *pszDataFile, CFlow *pUnderFlow,int nDbmtCount)
:CEventHandler(pReactor)
{
	m_nDbmtCount = nDbmtCount;
	CDbmtPackage::InitCommandInfoMap(g_dbmtCommandInfo);
	strcpy(m_sDataFile,pszDataFile);
	//20061211 wang.xp修改
	//将流文件编号改成1,以区分DBMT流文件 
	m_pUnderFlow = pUnderFlow;
	m_dbmtPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE, XTPHLEN);

//	m_TradingDay = CDate::LongToDate((long)m_pUnderFlow->GetCommPhaseNo());
//	SetTimer(TIMER_CHECK_DFCOMMAND, 1000);
}


CDfmtHandler::~CDfmtHandler()
{

}

void CDfmtHandler::MySetTimer(int nElapse)
{
	SetTimer(TIMER_CHECK_DFCOMMAND, nElapse);
}

void CDfmtHandler::SetCommPhaseNo(WORD nCommPhaseNo)
{
	m_TradingDay = CDate::LongToDate((long) nCommPhaseNo);
}

int CDfmtHandler::CheckDfCommand()
{
	CTradingDayType tradingDay;
	CCommandNoType commandNo;
	CDateType commandDate;
	CTimeType commandTime;
	CCommandTypeType commandType;
	CFieldNameType fieldName;
	CFieldContentType fieldContent;

	CTBCommandFile cmdFile(m_sDataFile);
	struct sTBCMD cmdRecord;

	if(!cmdFile.ReadCommand(cmdRecord))
	{
		return 0;
	}

	if(strcmp("",cmdRecord.TradingDay.getValue())==0)
	{
		cmdRecord.TradingDay=m_TradingDay;
	}

	if(strcmp(m_TradingDay.getValue(),cmdRecord.TradingDay.getValue())==0&& m_nDbmtCount< cmdRecord.CommandNo)
	{
		m_dbmtPackage.SetCommandType(cmdRecord.CommandType);
		m_dbmtPackage.SetCommandNo(cmdRecord.CommandNo);
		
		//补充序号
		char *pszFieldName = (char *)cmdRecord.FieldName.getValue();
		strcat(pszFieldName, ",\"DbmtTopicID\",\"DbmtSequenceID\"");
		char *pszFieldContent = (char *)cmdRecord.FieldContent.getValue();
		sprintf(pszFieldContent+strlen(pszFieldContent), ",\"%d\",\"%d\"", 
			DFMT_TOPIC_ID, cmdRecord.CommandNo.getValue());

		if(!m_dbmtPackage.AnalysisRecord(pszFieldName, pszFieldContent))
		{
			REPORT_EVENT(LOG_ERROR, "Dfmt", "AnalysisRecord error, CommandNo=[%d][%s][%s]",
				m_dbmtPackage.GetCommandNo().getValue(),
				(const char *)cmdRecord.FieldName.getValue(),
				(const char *)cmdRecord.FieldContent.getValue());
		}
		m_dbmtPackage.MakePackage();
		m_pUnderFlow->Append(m_dbmtPackage.Address(), m_dbmtPackage.Length());
		
		REPORT_EVENT(LOG_INFO, "Dfmt", "read dfmt package %s", (const char *)m_dbmtPackage.GetCommandType()); 
	}

	return 0;
}


void CDfmtHandler::OnTimer(int nIDEvent)
{
	if (nIDEvent == TIMER_CHECK_DFCOMMAND)
	{
		CheckDfCommand();
	}
}
