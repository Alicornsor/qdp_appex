// TinitServer.cpp: implementation of the CTinitServer class.
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "TinitServer.h"
#include "XtpPackageDesc.h"
#include "FlowReader.h"
#include "CachedFileFlow.h"
#include "CDate.h"
#include "monitorIndex.h"
#include "Config.h"
#include "CConfig.h"
#include "BaseFunction.h"

static CEventMonitor TinitEventMonitor;
extern DWORD DBMT_PACKAGE_MODE;
extern const char *APP_NAME;
extern DWORD TINIT_SUBJECTID;

#define DEF_RSP_INFO(name, id, msg)				\
	const int name##_ID = id;					\
	const char *name##_MSG = msg;				 

DEF_RSP_INFO(RI_SUCCESS,			0, "操作成功");
DEF_RSP_INFO(RI_ERR_DATA_FIELD,		1, "数据域错误");
DEF_RSP_INFO(RI_ERR_LOGIN,			2, "登录失败");
DEF_RSP_INFO(RI_ERR_DAYINIT_AGAIN,	3, "已经初始化过了");
DEF_RSP_INFO(RI_ERR_LOGIN_AGAIN,	4, "重复登录");
DEF_RSP_INFO(RI_ERR_LOGIN_MUTEX,	5, "同一时刻只能一个终端登录");
DEF_RSP_INFO(RI_ERR_UN_LOGIN,		6, "尚未登录");
DEF_RSP_INFO(RI_ERR_SYS_BUSY,		7, "系统忙");
DEF_RSP_INFO(RI_ERR_SP_CHECK,		8, "未通过SP合法性检查");
DEF_RSP_INFO(RI_ERR_DB_CONN,		9, "数据库连接中断");
DEF_RSP_INFO(RI_ERR_DATABASE,		10, "数据库错误");


#define SET_RSP_INFO(_rspInfo, _name)						\
	_rspInfo.ErrorID = (const int)_name##_ID;				\
	_rspInfo.ErrorMsg = _name##_MSG;

const int TIMER_CHECK_CONNECTION	= 1;
extern char * FLOW_FILE_NAME;
extern const char *INI_FILE_NAME;
extern const char *CMDFILENAME;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTinitServer::CTinitServer(CReactor *pReactor):CEventHandler(pReactor)
{
	char szBuffer[300];
	m_DataSyncStatus = DS_Asynchronous;
//mod by lihh 20130508,初始状态
//	m_SystemStatus  = SS_SyncDataReady;
//end modi
	m_pDbConnection = new CDbConnection();
	GetConfigString(INI_FILE_NAME, "FlowPath",szBuffer, sizeof(szBuffer));
	m_pTinitFlow = 	new CCachedFileFlow(FLOW_FILE_NAME, szBuffer, true, 1000000, 1000000);
	m_pPubMessage = CXTPPackage::CreatePackage(XTPHLEN);

	int nCommandNo = Redo();
	//建立实时上场，但是不启动
	m_pDbmtHandler = new CDbmtHandler(pReactor, GetDbConnection(), m_pTinitFlow,nCommandNo);
//此时set没有用，tinitflow没有东西	
//	m_pDbmtHandler->SetCommPhaseNo(m_pTinitFlow->GetCommPhaseNo());
	m_pDfmtHandler = new CDfmtHandler(pReactor,CMDFILENAME,m_pTinitFlow,nCommandNo);
//	m_pDfmtHandler->SetCommPhaseNo(m_pTinitFlow->GetCommPhaseNo());
	if(DS_Synchronized == m_DataSyncStatus)
	{
		m_pDbmtHandler->SetSystemID(m_pSystemID);
		//打开实时上场，这样保证顺序性
		m_pDbmtHandler->MySetTimer(1000);
		m_pDfmtHandler->MySetTimer(1000);
	}
	
	m_pDataLoader = new CTinitDataLoader(this, szBuffer);

	m_bLoadDataOK = false;
	SetTimer(TIMER_CHECK_CONNECTION, 1000);

	GetConfigString(INI_FILE_NAME, "qdata",szBuffer, sizeof(szBuffer));
// 	m_pGateway=new CTcpXtpGateway(pReactor,m_pTinitFlow);
// 	m_pGateway->SetSubjectID(TINIT_SUBJECTID);
// 	m_pGateway->RegisterListener(szBuffer);
// 	m_pGateway->Init(}

	m_pSendClient = new CXtpExClient((CSelectReactor*)pReactor, m_pTinitFlow, 0, NULL);
	m_pSendClient->RegClientCallback(this);
	m_pSendClient->RegisterReportServer(szBuffer);
	m_pSendClient->Init();
	memset(m_pSystemID,0,sizeof(m_pSystemID));
}

CTinitServer::~CTinitServer()
{
	delete m_pDataLoader;
	delete m_pDbmtHandler;
	delete m_pDfmtHandler;
	m_pPubMessage->Release();
	delete m_pDbConnection;
	delete m_pTinitFlow;
}

int CTinitServer::Redo()
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

		//modified by lihh 20130508, 消息类型
		if(TID_DataSyncEnd == dwTid)
		{
			//无需启动文件上场
			//modi lihh
			m_DataSyncStatus = DS_Synchronized;
		}
		else if (TID_InitSystemInfo == dwTid)
		{
			CSystemInfoField system;
			XTP_GET_SINGLE_FIELD(&m_pubPackage,&system);
			strncpy(m_pSystemID,system.SystemID.getValue(),4);
		}
		
		//end modi
	}
	//modified by lihh 20130508
	if( DS_Synchronized != m_DataSyncStatus && nAllNo !=0)
//	if( SS_DataSynced !=  m_SystemStatus && nAllNo !=0)
	{
		//如果redo的情况下，有文件个数但是却没有上场完成，说明这个文件是错误的
		//，需要清理掉文件之后重新上场
		REPORT_EVENT(LOG_CRITICAL, "Init", "TradingDayInit: 上场文件没有上场完成标志，上场文件错误，需要清理之后重新上场!");
		exit(-1);
	}
	m_pubPackage.BufRelease();
	return nCommandNo;
}

bool CTinitServer::ConnectDB(char *pszDatabaseName, char *pszUserName, char *pszPassword)
{
	if(!m_pDbConnection->ConnectDB(pszDatabaseName, pszUserName, pszPassword))
	{
		return false;
	}
	return m_pDataLoader->ConnectDB(pszDatabaseName, pszUserName, pszPassword);
}

void CTinitServer::GetSystemID()
{
	char szBuffer[300];
	GetConfigString(INI_FILE_NAME, "SystemID",szBuffer, sizeof(szBuffer));
	if (atoi(szBuffer)>0)
	{
		strncpy(m_pSystemID,szBuffer,4);
		m_pPubMessage->PreparePublish(TID_InitSystemInfo);
		CSystemInfoField system;
		system.SystemID = m_pSystemID;
		system.SystemIP = "127.0.0.1";
		system.SystemName = "localhost";
		XTP_ADD_FIELD(m_pPubMessage, &system);
		m_pPubMessage->MakePackage();
		m_pTinitFlow->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
	}
	else
	{
		typedef vector<string> CIPVec;
		CIPVec IPVect;
		IPVect.clear();
		bool ret =GetIPAddress(&IPVect);
		if (!ret || IPVect.size()==0)
		{
			REPORT_EVENT(LOG_CRITICAL, "GetSystemID", "获取本机IP地址失败! ret=%d ip_size=%d",ret,IPVect.size());
			exit(-1);
		}
		
		typedef map<string,CSystemInfoField> CSystemMap;
		CSystemMap SystemMap;
		SystemMap.clear();
		CSystemInfoField SystemInfo;
		SACommand cmd(m_pDbConnection,"SELECT systemip,systemid,systemname FROM t_sync_systeminfo");
		cmd.Execute();
		while (cmd.FetchNext())
		{
			CDbConnection::GetRow(&cmd,(char *)&SystemInfo, &SystemInfo.m_Describe);
			SystemMap.insert(CSystemMap::value_type(SystemInfo.SystemIP.getValue(),SystemInfo));
		}
		
		if (SystemMap.size()==0)
		{
			REPORT_EVENT(LOG_CRITICAL, "GetSystemID", "从数据库获取交易中心失败!");
			exit(-1);
		}

		int len = IPVect.size();
		for (int i=0;i<len;i++)
		{
			for(CSystemMap::iterator pSysIter =SystemMap.begin();pSysIter!=SystemMap.end();pSysIter++)
			{
				if (strcmp(IPVect[i].c_str(),pSysIter->first.c_str())==0)
				{
					strcpy(m_pSystemID,pSysIter->second.SystemID.getValue());
					info.SystemID = pSysIter->second.SystemID;
					info.SystemName = pSysIter->second.SystemName;
					info.SystemIP = pSysIter->second.SystemIP;
					return;
				}
			}
		}
		REPORT_EVENT(LOG_CRITICAL, "GetSystemID", "从数据库获取匹配的交易中心失败!");
		exit(-1);
	}
}

void CTinitServer::OnTradingDayInit()
{
	//如果已经上场了，不需要重复上场
	//modified by lihh 20130508
	if( DS_Asynchronous != m_DataSyncStatus)
	{
		REPORT_EVENT(LOG_CRITICAL, "Init", "TradingDayInit: 已经初始化过了，无需数据库上场，直接接受实时上场!");
		return;
	}

	//获取系统中心编号
	GetSystemID();
	

	//取出系统状态
 	CSystemStatusField filedSystemStatusField;
	try 
	{
		///增加对记录数是否唯一的判断
		SACommand cmdcount(m_pDbConnection,"SELECT count(*) FROM t_sync_systemstatus WHERE systemid=:1");
		cmdcount.Param(1).setAsString() = m_pSystemID;
		cmdcount.Execute();
		cmdcount.FetchNext();
 		long statusnumber = cmdcount.Field(1).asLong();
		if(statusnumber!=1)
		{
			REPORT_EVENT(LOG_ERROR, "Init", "TradingDayInit: t_sync_systemstatus 数目不唯一 退出!");
			return;			
		}
		cmdcount.Close();

		SACommand cmd(m_pDbConnection,"SELECT tradingday,systemstatus FROM t_sync_systemstatus WHERE systemid=:1");
		cmd.Param(1).setAsString() = m_pSystemID;
		cmd.Execute();
		cmd.FetchNext();
		CDbConnection::GetRow(&cmd,(char *)&filedSystemStatusField, &filedSystemStatusField.m_Describe);
	}	
	catch(SAException &x)
	{
		try
		{
			m_pDbConnection->CheckConntectionError(x.ErrNativeCode());
			// on error rollback changes
			m_pDbConnection->Rollback();
			REPORT_EVENT(LOG_ERROR, "Init", "TradingDayInit: 获取系统状态出错，退出!");
		}
		catch(SAException &)
		{
		}
		return;	
	}

	//判断是否是可以上场的状态
//	if(filedSystemStatusField.SystemStatus!=SS_Yes)
// modified by lihh 20130508
//modified by chengm 20160616 夜盘上场后状态变为5,早盘开盘的时候需要重新上场，注释掉
// 	if(filedSystemStatusField.SystemStatus!=SS_SyncDataReady)
// 	{
// 		//不可上场，直接退出
// 		REPORT_EVENT(LOG_ERROR, "Init", "TradingDayInit: 获取系统状态为不可上场，退出!");
// 		return;
// 	}

	CTradingDayField ExchangeTradingDay;
	ExchangeTradingDay.TradingDay = filedSystemStatusField.TradingDay;
	LoadTradingDay(ExchangeTradingDay);	
	m_DataSyncStatus = DS_Synchronizing;
//modified by lihh 20130508
//	m_SystemStatus = SS_DataSyncing;
}

bool CTinitServer::IsBusy()
{
	return m_pDataLoader->IsBusy();
}

int CTinitServer::HandleEvent(int nEventID, DWORD dwParam, void *pParam)
{
	switch(nEventID) 
	{
	case UM_TINIT_APPEND_DATA:
		{
		return OnTinitAppendData((CFileFlow *)pParam, (int) dwParam);
		break;
		}
	case UM_TINIT_APPEND_END:
		{
			//标志已经初始化过了
			//modified by lihh 20130508
			m_DataSyncStatus = DS_Synchronized;
//			m_SystemStatus = SS_DataSynced;
								//InstrumentTradingDayDown;
								//TradingDayOver;
			//end modified
			OnTinitAppendEnd((TTinitInitType)dwParam);
			//设置通讯阶段号
			DWORD commPhaseNo = (WORD)CDate::DateToLong(m_TradingDay.TradingDay);
			m_pDbmtHandler->SetCommPhaseNo(commPhaseNo);
			m_pDfmtHandler->SetCommPhaseNo(commPhaseNo);
			m_pDbmtHandler->SetSystemID(m_pSystemID);
			//打开实时上场，这样保证顺序性
			m_pDbmtHandler->MySetTimer(1000);
			m_pDfmtHandler->MySetTimer(1000);
			return 0;
		}
	case UM_TINIT_ERROR:
		{
			if (dwParam != 0)
			{
				TinitEventMonitor.report("LoadTableError", (char *)pParam);
				m_bLoadDataOK = false;
			}
			else
			{
				TinitEventMonitor.report("LoadTableOK", (char *)pParam);
			}
			return 0;	
		}
	default:
		break;
	}
	return CEventHandler::HandleEvent(nEventID, dwParam, pParam);
}

void CTinitServer::OnTinitAppendEnd(TTinitInitType nType)
{
	BIZ_OPERATION_LOG0("===============OnTinitAppendEnd\n");
	char szReport[1000];
	sprintf(szReport, "Load %s Data\n", "system");
	if (!m_bLoadDataOK)
	{
		TinitEventMonitor.report("TinitError", szReport);
		return;
	}

	TinitEventMonitor.report("TinitOK", szReport);

	if (nType == TIT_TD_INIT)
	{
		m_pPubMessage->PreparePublish(TID_DataSyncEnd);
		XTP_ADD_FIELD(m_pPubMessage, &m_TradingDay);
	}
	m_pPubMessage->MakePackage();
	m_pTinitFlow->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
}

int CTinitServer::OnTinitAppendData(CFileFlow *pDataFlow, int nOffset)
{
	char buf[10000];
	const int BULK_SIZE = 1000;
	int nCount = pDataFlow->GetCount() - nOffset;
	if (nCount > BULK_SIZE)
	{
		nCount = BULK_SIZE;
	}
	for (int i=0; i<nCount; i++)
	{
		int len = pDataFlow->Get(nOffset, buf, sizeof(buf));
		m_pTinitFlow->Append(buf, len);
		nOffset++;
	}
	return nCount;
}

void CTinitServer::LoadTradingDay(CTradingDayField &ExchangeTradingDay)
{
	m_bLoadDataOK = true;

	m_TradingDay= ExchangeTradingDay;
	m_CommPhase.TradingDay = ExchangeTradingDay.TradingDay;
	m_CommPhase.CommPhaseNo = (WORD)CDate::DateToLong(m_CommPhase.TradingDay);

	m_pTinitFlow->SetCommPhaseNo(m_CommPhase.CommPhaseNo);
	m_pDbmtHandler->SetCommPhaseNo(m_CommPhase.CommPhaseNo);
	if (m_pTinitFlow->GetCount() == 0)
	{
		//每个交易日第一个消息一定是切换交易日
		m_pPubMessage->PreparePublish(TID_NtfCommPhaseChange);
		XTP_ADD_FIELD(m_pPubMessage, &m_CommPhase);
		m_pPubMessage->MakePackage();
		m_pTinitFlow->Append(m_pPubMessage->Address(), m_pPubMessage->Length());

		m_pPubMessage->PreparePublish(TID_InitSystemInfo);
		XTP_ADD_FIELD(m_pPubMessage, &info);
		m_pPubMessage->MakePackage();
		m_pTinitFlow->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
	}
	m_pPubMessage->PreparePublish(TID_DataSyncStart);
	XTP_ADD_FIELD(m_pPubMessage, &m_TradingDay);
	m_pPubMessage->MakePackage();
	m_pTinitFlow->Append(m_pPubMessage->Address(), m_pPubMessage->Length());

	m_pDataLoader->StartLoadDay(m_TradingDay.TradingDay,m_pSystemID);
}

void CTinitServer::SetError(int nErrorCode, const char *pszErrorMsg)
{
	SendEvent(UM_TINIT_ERROR, (DWORD)nErrorCode, (void *)pszErrorMsg);
}

void CTinitServer::OnTimer(int nIDEvent)
{
	if (nIDEvent == TIMER_CHECK_CONNECTION)
	{
		if (!IsBusy())
		{
			if (!m_pDbConnection->isConnected())
			{
				m_pDbConnection->ConnectDB();
			}
		}
		CMonitorIndex::handleOne();
	}
}

