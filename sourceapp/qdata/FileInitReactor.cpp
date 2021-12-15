// FileInitReactor.cpp: implementation of the CFileInitReactor class.
//
/* ----------------------------------------------------------
 * 修改日期：2006.9.29
 * 修改人员：王维 
 * 修改描述：调整日志信息
 * 备注信息：增加CFileInitMonitorIndexTimer类的实现
 *           将原来的DEBUG_LOG转为syslog
 * ----------------------------------------------------------
*/
// 20061020 王维 改正DFMT未发布的BUG
// 20070828 王维 调整日志的级别和分类
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "FileInitReactor.h"
#include "DbmtRecord.h"
#include "TinitDataLoadThread.h"
#include "XtpPackageDesc.h"
#include "Config.h"
#include "CachedFileFlow.h"
#include "monitorIndex.h"
#include "CDate.h"
#include "FlowReader.h"

extern TTinitTableInfo g_DayTableInfo[];
extern char * FLOW_FILE_NAME;
extern DWORD DBMT_PACKAGE_MODE;
#define MAX_LINE_LEGTH	10000

extern const char *INI_FILE_NAME;
extern const char *APP_NAME;
extern const char *CMDFILENAME;
extern DWORD TINIT_SUBJECTID;

class CFileInitMonitorIndexTimer : public CEventHandler
{
public:
	CFileInitMonitorIndexTimer(CReactor *pReactor)
		:CEventHandler(pReactor)
	{
	}
	virtual void OnTimer(int nIDEvent)
	{
		CMonitorIndex::handleOne();
	}
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileInitReactor::CFileInitReactor( const char *pszWorkDay)
{
	m_WorkDay = pszWorkDay;
	m_pTinitFlow= NULL;
	//m_pPubApiManager = new CFibPubApiManager(this, 0);
	m_pPubApiManager = NULL;
	m_pPubMessage = new CXTPPackage();
	m_pPubMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE, XTPHLEN);
	m_pDfmtHandler = NULL;
	m_pMonitorIndexTimer = new CFileInitMonitorIndexTimer(this);
	m_bNeedLoad = true;
//	m_pGateway = NULL;
}

CFileInitReactor::~CFileInitReactor()
{
	delete m_pMonitorIndexTimer;
	delete m_pDfmtHandler;
	delete m_pPubApiManager;
	delete m_pTinitFlow;
	delete m_pPubMessage;
//	delete m_pGateway;
	delete m_pSendClient;
}

bool CFileInitReactor::InitInstance()
{
	char szBuffer[300];
	
	GetConfigString(INI_FILE_NAME, "FlowPath",szBuffer, sizeof(szBuffer));
	DWORD commPhaseNo = (WORD)CDate::DateToLong(m_WorkDay);

	m_pTinitFlow = new CCachedFileFlow(FLOW_FILE_NAME, szBuffer, true, 1000000, 1000000);
	CIntPtrMonitorIndex *pTinitLenIndex = new CIntPtrMonitorIndex("qdataLen",m_pTinitFlow->GetCountPtr(),20);

	int nCommandNo = Redo();
	
	if(m_bNeedLoad)
	{
		GetConfigString(INI_FILE_NAME, "CSVPath",szBuffer, sizeof(szBuffer));
		if(!LoadFromCSV(szBuffer))
		{
			return false;
		}
	}	

	//在加载完csv之后循环读写CMDFILENAME文件，保证前后一致性
	m_pDfmtHandler = new CDfmtHandler(this, CMDFILENAME, m_pTinitFlow,nCommandNo);
	m_pDfmtHandler->MySetTimer(1000);

	GetConfigString(INI_FILE_NAME, "qdata",szBuffer, sizeof(szBuffer));
// 	m_pGateway=new CTcpXtpGateway(this,m_pTinitFlow);
// 	m_pGateway->SetSubjectID(TINIT_SUBJECTID);
// 	m_pGateway->RegisterListener(szBuffer);
// 	m_pGateway->Init();	

	m_pSendClient = new CXtpExClient(this, m_pTinitFlow, 0, NULL);
	m_pSendClient->RegClientCallback(this);
	m_pSendClient->RegisterReportServer(szBuffer);
	m_pSendClient->Init();

	RegisterTimer(m_pMonitorIndexTimer, 1, 5000);	
	return true;
}

void CFileInitReactor::ExitInstance()
{
}

int CFileInitReactor::Redo()
{
	CFlowReader reader;
	CXTPPackage m_pubPackage;
	int nCommandNo = 0;
	int nAllNo = 0;
	reader.AttachFlow(m_pTinitFlow, 0);	
	m_pubPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	for (;;)
	{
		m_pubPackage.Allocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN);
		if (!reader.GetNext(&m_pubPackage)) 
		{
			break;
		}
		//使用SessionID标记包是否为dbmt报文
		DWORD dwType = m_pubPackage.GetSessionID();
		nAllNo ++;
		if (DBMT_PACKAGE_MODE==dwType)
		{
			//使用FrontID保存每个dbmt的nCommandNo
			//nCommandNo的顺序是递增的,所以将每次过来的报文赋值给m_nCommandNo即可
			nCommandNo = m_pubPackage.GetFrontID();
		}
		//如果tid是 TID_DataSyncEnd,说明上场结束了,可以启动实时上场
		DWORD dwTid = m_pubPackage.GetTid();
		if(TID_DataSyncEnd == dwTid)
		{
			//无需启动文件上场
			m_bNeedLoad = false;
		}
	}
	if(m_bNeedLoad && (nAllNo !=0))
	{
		//如果redo的情况下，有文件个数但是却没有上场完成，说明这个文件是错误的
		//，需要清理掉文件之后重新上场
		REPORT_EVENT(LOG_CRITICAL, "Init", "TradingDayInit: 上场文件没有上场完成标志，上场文件错误，需要清理之后重新上场!");
		exit(-1);
	}
	m_pubPackage.BufRelease();
	return nCommandNo;
}


bool CFileInitReactor::LoadFromCSV(const char *pszCSVPath)
{
	//load exchange init data
	CCommPhaseField fieldCommPhase;

	fieldCommPhase.TradingDay = m_WorkDay;
	fieldCommPhase.CommPhaseNo = (WORD)CDate::DateToLong(fieldCommPhase.TradingDay);

	m_pTinitFlow->SetCommPhaseNo(fieldCommPhase.CommPhaseNo);
	if (m_pTinitFlow->GetCount() == 0)
	{
		//每个交易日第一个消息一定是切换交易日
		m_pPubMessage->PreparePublish(TID_NtfCommPhaseChange);
		XTP_ADD_FIELD(m_pPubMessage, &fieldCommPhase);
		m_pPubMessage->MakePackage();
		m_pTinitFlow->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
	}

	//数据同步开始
	CTradingDayField fieldTradingDay;
	fieldTradingDay.TradingDay = m_WorkDay;
	m_pPubMessage->PreparePublish(TID_DataSyncStart);
	XTP_ADD_FIELD(m_pPubMessage, &fieldTradingDay);
	m_pPubMessage->MakePackage();
	m_pTinitFlow->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
	REPORT_EVENT(LOG_CRITICAL, "DataSyncStart", "Begin to Load Data");
	
	char szFileName[1000];

	TTinitTableInfo *pInfo = g_DayTableInfo;
	while (pInfo->tid != 0)
	{
		sprintf(szFileName, "%s%s.csv", pszCSVPath, pInfo->pszTable);
		if(!LoadTable(szFileName, pInfo->pFieldDescribe, pInfo->tid))
		{
			REPORT_EVENT(LOG_CRITICAL, "LoadTableInit", "LoadTableError %s", m_strErrorMsg.c_str());
			return false;
		}

		REPORT_EVENT(LOG_CRITICAL, "LoadTable", "LoadTableOK %s", szFileName);
		pInfo ++;
	}
	
	m_pPubMessage->PreparePublish(TID_DataSyncEnd);
	XTP_ADD_FIELD(m_pPubMessage, &fieldTradingDay);
	m_pPubMessage->MakePackage();
	m_pTinitFlow->Append(m_pPubMessage->Address(), m_pPubMessage->Length());

	REPORT_EVENT(LOG_CRITICAL, "DataSyncEnd", "Load Exchange Data OK");	
	return true;
}

bool CFileInitReactor::LoadTable(const char *pszCSVFileName, 
								   CFieldDescribe *pFieldDesc,
								   int nTid)
{
	m_strErrorMsg = pszCSVFileName;
	m_strErrorMsg += ":";
	
	CDbmtRecord record;

	FILE *fp = mfopen(pszCSVFileName, "rb");
	if (fp == NULL)
	{
		m_strErrorMsg += "Can't open csv file";
		return false;
	}

	char bufRead[MAX_LINE_LEGTH];
	if(fgets(bufRead, MAX_LINE_LEGTH, fp) == NULL)
	{
		m_strErrorMsg += "Missing csv file header";
		fclose(fp);
		return false;
	}

	if (!record.AnalysisFieldName(bufRead))
	{
		m_strErrorMsg += "Anlysis csv file header error";
		fclose(fp);
		return false;
	}

//  20121218 xuzh 为了避免将前一个包输出到流，这里应该就只有准备包
//	FlushPackage(nTid);
	m_pPubMessage->PreparePublish(nTid);
//	20121218 xuzh end

	char bufStruct[MAX_LINE_LEGTH];
/*** SIR XLONG BEGIN ***/
	bool bRet = true;
/*** SIR XLONG END ***/
	while (fgets(bufRead, MAX_LINE_LEGTH, fp) != NULL)
	{
		if (!record.AnalysisFieldContent(bufRead))
		{
			m_strErrorMsg += "Anlysis csv file content error";
/*** SIR XLONG BEGIN ***/
			bRet = false;
/*** SIR XLONG END ***/
			break;
		}
		if (!record.TransToStruct(pFieldDesc, bufStruct))
		{
			m_strErrorMsg += "Transfer to struct error";
/*** SIR XLONG BEGIN ***/
			bRet = false;
/*** SIR XLONG END ***/
			break;
		}
		
		while(m_pPubMessage->AddField(pFieldDesc, bufStruct) < 0)
		{
			FlushPackage(nTid);
		}
	}
	
	FlushPackage(nTid);
	fclose(fp);
/*** SIR XLONG BEGIN ***/
	return bRet;
/*** SIR XLONG END ***/
}

void CFileInitReactor::FlushPackage(DWORD newtid)
{
	if (m_pPubMessage->Length() > 0)
	{
		m_pPubMessage->SetSubjectID(0);
		m_pPubMessage->MakePackage();
		m_pTinitFlow->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
	}
	m_pPubMessage->PreparePublish(newtid);
}

