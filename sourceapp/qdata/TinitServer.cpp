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

DEF_RSP_INFO(RI_SUCCESS,			0, "�����ɹ�");
DEF_RSP_INFO(RI_ERR_DATA_FIELD,		1, "���������");
DEF_RSP_INFO(RI_ERR_LOGIN,			2, "��¼ʧ��");
DEF_RSP_INFO(RI_ERR_DAYINIT_AGAIN,	3, "�Ѿ���ʼ������");
DEF_RSP_INFO(RI_ERR_LOGIN_AGAIN,	4, "�ظ���¼");
DEF_RSP_INFO(RI_ERR_LOGIN_MUTEX,	5, "ͬһʱ��ֻ��һ���ն˵�¼");
DEF_RSP_INFO(RI_ERR_UN_LOGIN,		6, "��δ��¼");
DEF_RSP_INFO(RI_ERR_SYS_BUSY,		7, "ϵͳæ");
DEF_RSP_INFO(RI_ERR_SP_CHECK,		8, "δͨ��SP�Ϸ��Լ��");
DEF_RSP_INFO(RI_ERR_DB_CONN,		9, "���ݿ������ж�");
DEF_RSP_INFO(RI_ERR_DATABASE,		10, "���ݿ����");


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
//mod by lihh 20130508,��ʼ״̬
//	m_SystemStatus  = SS_SyncDataReady;
//end modi
	m_pDbConnection = new CDbConnection();
	GetConfigString(INI_FILE_NAME, "FlowPath",szBuffer, sizeof(szBuffer));
	m_pTinitFlow = 	new CCachedFileFlow(FLOW_FILE_NAME, szBuffer, true, 1000000, 1000000);
	m_pPubMessage = CXTPPackage::CreatePackage(XTPHLEN);

	int nCommandNo = Redo();
	//����ʵʱ�ϳ������ǲ�����
	m_pDbmtHandler = new CDbmtHandler(pReactor, GetDbConnection(), m_pTinitFlow,nCommandNo);
//��ʱsetû���ã�tinitflowû�ж���	
//	m_pDbmtHandler->SetCommPhaseNo(m_pTinitFlow->GetCommPhaseNo());
	m_pDfmtHandler = new CDfmtHandler(pReactor,CMDFILENAME,m_pTinitFlow,nCommandNo);
//	m_pDfmtHandler->SetCommPhaseNo(m_pTinitFlow->GetCommPhaseNo());
	if(DS_Synchronized == m_DataSyncStatus)
	{
		m_pDbmtHandler->SetSystemID(m_pSystemID);
		//��ʵʱ�ϳ���������֤˳����
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
		//ʹ��SessionID��ǰ��Ƿ�Ϊdbmt����
		DWORD dwType = m_pubPackage.GetSessionID();
		nAllNo ++;
		if (DBMT_PACKAGE_MODE==dwType)
		{
			//ʹ��FrontID����ÿ��dbmt��nCommandNo
			//nCommandNo��˳���ǵ�����,���Խ�ÿ�ι����ı��ĸ�ֵ��m_nCommandNo����
			nCommandNo = m_pubPackage.GetFrontID();
		}
		//���tid�� TID_DataSyncEnd,˵���ϳ�������,��������ʵʱ�ϳ�
		DWORD dwTid = m_pubPackage.GetTid();

		//modified by lihh 20130508, ��Ϣ����
		if(TID_DataSyncEnd == dwTid)
		{
			//���������ļ��ϳ�
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
		//���redo������£����ļ���������ȴû���ϳ���ɣ�˵������ļ��Ǵ����
		//����Ҫ������ļ�֮�������ϳ�
		REPORT_EVENT(LOG_CRITICAL, "Init", "TradingDayInit: �ϳ��ļ�û���ϳ���ɱ�־���ϳ��ļ�������Ҫ����֮�������ϳ�!");
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
			REPORT_EVENT(LOG_CRITICAL, "GetSystemID", "��ȡ����IP��ַʧ��! ret=%d ip_size=%d",ret,IPVect.size());
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
			REPORT_EVENT(LOG_CRITICAL, "GetSystemID", "�����ݿ��ȡ��������ʧ��!");
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
		REPORT_EVENT(LOG_CRITICAL, "GetSystemID", "�����ݿ��ȡƥ��Ľ�������ʧ��!");
		exit(-1);
	}
}

void CTinitServer::OnTradingDayInit()
{
	//����Ѿ��ϳ��ˣ�����Ҫ�ظ��ϳ�
	//modified by lihh 20130508
	if( DS_Asynchronous != m_DataSyncStatus)
	{
		REPORT_EVENT(LOG_CRITICAL, "Init", "TradingDayInit: �Ѿ���ʼ�����ˣ��������ݿ��ϳ���ֱ�ӽ���ʵʱ�ϳ�!");
		return;
	}

	//��ȡϵͳ���ı��
	GetSystemID();
	

	//ȡ��ϵͳ״̬
 	CSystemStatusField filedSystemStatusField;
	try 
	{
		///���ӶԼ�¼���Ƿ�Ψһ���ж�
		SACommand cmdcount(m_pDbConnection,"SELECT count(*) FROM t_sync_systemstatus WHERE systemid=:1");
		cmdcount.Param(1).setAsString() = m_pSystemID;
		cmdcount.Execute();
		cmdcount.FetchNext();
 		long statusnumber = cmdcount.Field(1).asLong();
		if(statusnumber!=1)
		{
			REPORT_EVENT(LOG_ERROR, "Init", "TradingDayInit: t_sync_systemstatus ��Ŀ��Ψһ �˳�!");
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
			REPORT_EVENT(LOG_ERROR, "Init", "TradingDayInit: ��ȡϵͳ״̬�����˳�!");
		}
		catch(SAException &)
		{
		}
		return;	
	}

	//�ж��Ƿ��ǿ����ϳ���״̬
//	if(filedSystemStatusField.SystemStatus!=SS_Yes)
// modified by lihh 20130508
//modified by chengm 20160616 ҹ���ϳ���״̬��Ϊ5,���̿��̵�ʱ����Ҫ�����ϳ���ע�͵�
// 	if(filedSystemStatusField.SystemStatus!=SS_SyncDataReady)
// 	{
// 		//�����ϳ���ֱ���˳�
// 		REPORT_EVENT(LOG_ERROR, "Init", "TradingDayInit: ��ȡϵͳ״̬Ϊ�����ϳ����˳�!");
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
			//��־�Ѿ���ʼ������
			//modified by lihh 20130508
			m_DataSyncStatus = DS_Synchronized;
//			m_SystemStatus = SS_DataSynced;
								//InstrumentTradingDayDown;
								//TradingDayOver;
			//end modified
			OnTinitAppendEnd((TTinitInitType)dwParam);
			//����ͨѶ�׶κ�
			DWORD commPhaseNo = (WORD)CDate::DateToLong(m_TradingDay.TradingDay);
			m_pDbmtHandler->SetCommPhaseNo(commPhaseNo);
			m_pDfmtHandler->SetCommPhaseNo(commPhaseNo);
			m_pDbmtHandler->SetSystemID(m_pSystemID);
			//��ʵʱ�ϳ���������֤˳����
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
		//ÿ�������յ�һ����Ϣһ�����л�������
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

