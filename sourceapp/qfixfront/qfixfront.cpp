// fgateway.cpp: 
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "BaseFunction.h"
#include "SelectReactor.h"
#include "EpollReactor.h"
//#include "FrontTerminal.h"
#include "FixEngine.h"
#include "CachedFileFlow.h"
#include "FileFlow.h"
#include "Config.h"
#include "FlowSubscriber.h"
#include "monitorIndex.h"
#include "CConfig.h"
#include "version.h"
#include "CFilelogService.h"
#include "PipeEventHandler.h"
#include "SynFlowSubscriber.h"

#include "FlowReader.h"
#include "XtpClient.h"
#include "FrontForwarder.h"
#include "FrontTerminal.h"
#include "FixRspClient.h"

const int QUERY_SERVER_ID = 1;
const DWORD FRONT_APP_ID_BASE = 0x1700;
const char *INI_FILE_NAME = "qfixfront.ini";
const char *APP_NAME = "qfixfront";



#define MAX_FRONT_REACTOR	10
//启动模式
#define NORMAL_START_MODE   0
#define RESTORE_START_MODE  1

//启动模式
int g_StartMode = NORMAL_START_MODE;

//CSemaphore g_semThread;
char g_szFlowPath[300];

bool LatencyOut = false;


//add by wyl 
bool g_bLatencyOut = false;
CFlow *g_pMemResult = NULL;
bool g_bIsMultiSeat = false;
CConfig *g_pConfig = NULL;
CSelectReactor* g_pConnReactor = NULL;
bool g_bIsQquery = false;


class CPackageHandleCounter
{
public:
	virtual int GetHandleCount() = 0;
};

class CMonitorIndexTimer : public CEventHandler
{
public:
	CMonitorIndexTimer(CReactor *pReactor)
		:CEventHandler(pReactor)
	{
		SetTimer(0, 1000);
	}
protected:
	virtual void OnTimer(int nIDEvent)
	{
		CMonitorIndex::handleOne();
	}
};
//////////////////////////////////////////////////////////////////////////
//CFrontWriteLogReactor
//20130827 huwp 修改写slog慢的问题
//////////////////////////////////////////////////////////////////////////
class CFrontWriteLogReactor : public CThread
{
public:
	CFrontWriteLogReactor(DWORD dwFrontID, CCachedFlow *pSlogResult)
	{
		m_pSlogResult = pSlogResult;
		char szBuffer[300];
		strcpy(szBuffer, g_szFlowPath);
		sprintf(szBuffer + strlen(szBuffer), "%d", dwFrontID);
		strcat(szBuffer, "ftd");
		m_strFlowPathName = szBuffer;
		OpenChannelLogFile(szBuffer);
		m_reader.AttachFlow(m_pSlogResult, 0);
	}
	virtual void Run();
	virtual int GetHandleCount();
	bool OpenChannelLogFile(const char *pszPath);
	int *GetCountPtr(void);
private:
	CCachedFlow * m_pSlogResult;
	FILE *m_fpChannelLog;
	CFlowReader m_reader;
	string m_strFlowPathName;
	int m_nCount;					/**在cache里还没被写到文件的长度 */
};
bool CFrontWriteLogReactor::OpenChannelLogFile(const char *pszPath)
{
	char szFullFilename[512];
	sprintf(szFullFilename, "%s_%s.slog", pszPath, "00000000");
	m_fpChannelLog = fopen(szFullFilename, "ab");
	if (m_fpChannelLog == NULL)
	{
		return false;
	}
	return true;
}
int CFrontWriteLogReactor::GetHandleCount()
{
	return m_reader.GetId();
}
void CFrontWriteLogReactor::Run()
{
	char sBuff[8192];
	int nDataLen = 8192;
	int iLen = 0;
	for (;;)
	{
		//不等需要清理Slog流
		if (m_reader.GetCommPhaseNo() != m_pSlogResult->GetCommPhaseNo())
		{
			fclose(m_fpChannelLog);
			OpenChannelLogFile(m_strFlowPathName.c_str());
		}
		iLen = m_reader.GetNext(sBuff, nDataLen);
		if (iLen <= 0)
		{
			SLEEP(1000);
			continue;
		}
		if (NULL != m_fpChannelLog)
		{
			fwrite(sBuff, 1, iLen, m_fpChannelLog);
			fflush(m_fpChannelLog);
		}
		m_nCount = m_pSlogResult->GetCount() - m_reader.GetId();
	}
}
int *CFrontWriteLogReactor::GetCountPtr(void)
{
	return &m_nCount;
}

//////////////////////////////////////////////////////////////////////////
//CQkernelSubscribeReactor
//////////////////////////////////////////////////////////////////////////
class CExXtpClient : public CXtpClient
{
public:
	CExXtpClient(CSelectReactor *pReactor, CFlow *pSerailFlow)
		:CXtpClient(pReactor, pSerailFlow, 0, g_pConnReactor)
	{

		m_LoginPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE + XTPHLEN, 1000);
		m_nsubcount = 0;
	}

	virtual CSession* CreateSession(CChannel *pChannel, DWORD dwMark)
	{
		CTcpXtpSession *pSession = new CTcpXtpSession(m_pReactor, pChannel, this);
		return pSession;
	}

	virtual void OnSessionConnected(CSession *pSession)
	{
		m_bConnected = true;
		REPORT_EVENT(LOG_CRITICAL, "pmemchange", "pmemchange connected\n");
		CSessionFactory::OnSessionConnected(pSession);
		m_pSession = (CTcpXtpSession *)pSession;
		InterLogin(m_pSession);
	}

	void InterLogin(CTcpXtpSession *pSession)
	{
		CLifeCycleIDField field;
		field.LifeCycleID = m_nsubcount;

		m_LoginPackage.PreparePublish(FID_LifeCycleID);
		m_LoginPackage.AddField(&CLifeCycleIDField::m_Describe, &field);
		if (pSession)
		{
			pSession->SendReportPackage(&m_LoginPackage);
		}
	}

	virtual void OnSessionDisconnected(CSession *pSession, int nReason)
	{
		//设置为不可发送
		m_bConnected = false;
		REPORT_EVENT(LOG_CRITICAL, "pmemchange", "pmemchange disConnected\n");
		CSessionFactory::OnSessionDisconnected(pSession, nReason);
	}

	int HandlePackage(CXTPPackage *pXTPPackage, CTcpXtpSession *pSession)
	{
		pXTPPackage->MakePackage();
		m_pSerialFlow->Append(pXTPPackage->Address(), pXTPPackage->Length());
		pXTPPackage->Pop(XTPHLEN);
		m_nsubcount++;
		return 0;
	}

private:
	CXTPPackage m_LoginPackage;
	int m_nsubcount;
};

class CTradeDataClient : public CXtpClient
{
public:
	CTradeDataClient(CSelectReactor *pReactor, CFlow *pSerailFlow)
		:CXtpClient(pReactor, pSerailFlow, 0, g_pConnReactor)
	{

		m_LoginPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE + XTPHLEN, 1000);
		m_nsubcount = 0;
	}

	virtual CSession* CreateSession(CChannel *pChannel, DWORD dwMark)
	{
		CTcpXtpSession *pSession = new CTcpXtpSession(m_pReactor, pChannel, this);
		pSession->PublishFlow(m_pSerialFlow, 0);
		return pSession;
	}

	virtual void OnSessionConnected(CSession *pSession)
	{
		m_bConnected = true;
		REPORT_EVENT(LOG_CRITICAL, "qtrade", "qtrade connected\n");
		CSessionFactory::OnSessionConnected(pSession);
		m_pSession = (CTcpXtpSession *)pSession;
		InterLogin(m_pSession);
	}

	void InterLogin(CTcpXtpSession *pSession)
	{
		CLifeCycleIDField field;
		field.LifeCycleID = m_nsubcount;

		m_LoginPackage.PreparePublish(FID_LifeCycleID);
		m_LoginPackage.AddField(&CLifeCycleIDField::m_Describe, &field);
		if (pSession)
		{
			pSession->SendReportPackage(&m_LoginPackage);
		}
	}

	virtual void OnSessionDisconnected(CSession *pSession, int nReason)
	{
		//设置为不可发送
		m_bConnected = false;
		REPORT_EVENT(LOG_CRITICAL, "qtrade", "qtrade disConnected\n");
		CSessionFactory::OnSessionDisconnected(pSession, nReason);
	}

	int HandlePackage(CXTPPackage *pXTPPackage, CTcpXtpSession *pSession)
	{
		pXTPPackage->MakePackage();
		m_pSerialFlow->Append(pXTPPackage->Address(), pXTPPackage->Length());
		pXTPPackage->Pop(XTPHLEN);
		m_nsubcount++;
		return 0;
	}

private:
	CXTPPackage m_LoginPackage;
	int m_nsubcount;
};


class CFrontReactor : public CSelectReactor, public CPackageHandleCounter
{
public:
	/**构造函数
	*/
	CFrontReactor(DWORD dwFrontID = 9999)
	{
		m_dwFrontID = dwFrontID;
		m_pubPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE, 1000);
		m_pConfig = NULL;
		//m_pClientApi = NULL;
		//m_pFrontTerminal = NULL;
		//m_pFrontForwarder = NULL;
		//m_pFrontClient = NULL;
		m_pFixEngine = NULL;
		//20130827 huwp 修改写slog慢的问题		
		m_pSlogResult = NULL;
		m_nHandleCount = 0;

		//由该线程进行日志输出
		m_pMonitorIndexTimer = new CMonitorIndexTimer(this);
	}

	virtual bool InitInstance()
	{
		char szBuffer[300];
		GetConfigString(INI_FILE_NAME, "ConfigPath", szBuffer, sizeof(szBuffer));
		GetConfigString(INI_FILE_NAME, "FlowPath", g_szFlowPath, sizeof(g_szFlowPath));
		m_pConfig = new CConfig(INI_FILE_NAME);

		if (!strcmp(m_pConfig->getConfig("LatencyOut"), "yes"))
		{
			LatencyOut = true;
		}

		m_dwFrontID = GetConfigInt(INI_FILE_NAME, "FrontID");
		int runMode = GetConfigInt(INI_FILE_NAME, "RunMode");
		if (runMode == 1)
		{
			m_pTradeResult = new CCachedFlow(false, 2000000, 0x200000);
		}
		else
		{
			m_pTradeResult = new CCachedFileFlow("traderesult", g_szFlowPath, true, 0x70000, 0x20000);
		}


		m_pSendFlow = new CCachedFileFlow("SendResult", g_szFlowPath, false, 2000000, 0x20000);
		
		//收到交易结果流水之后，通知立刻处理
		CPipeEventHandler *pPipeHandler = new CPipeEventHandler(this);
		m_pTradeResult->AttachObserver(pPipeHandler);
		//receivedflow
		m_pSubscribeReactor = new CSelectReactor();
		m_pMemFlowClient = new CExXtpClient(m_pSubscribeReactor, m_pTradeResult);
		char *pmemchange = m_pConfig->getConfig("memchange");
		m_pMemFlowClient->RegisterConnecter(pmemchange);
		m_pMemFlowClient->Init();
		//sendflow
		m_pTradeFlowClient = new CTradeDataClient(m_pSubscribeReactor, m_pSendFlow);
		char *qdata = m_pConfig->getConfig("qdata");
		m_pTradeFlowClient->RegisterConnecter(qdata);
		m_pTradeFlowClient->Init();
		//qqery
		m_pClientApi = CFibClientApi::CreateClientApi(this, m_dwFrontID);
		char* pQquery = m_pConfig->getConfig("qquery");
		m_pFrontTerminal = new CFrontTerminal();
		m_pClientApi->RegisterServer(QUERY_SERVER_ID, pQquery, m_pFrontTerminal);

		m_pFrontForwarder = new CFrontForwarder(m_dwFrontID, QUERY_SERVER_ID, m_pClientApi);
		//交易请求处理类
		m_pFixEngine = new CFixEngine(m_pSendFlow, m_pConfig, m_pFrontForwarder);
		//查询和交易结果响应类
		m_fixRspClient = new FixRspClient(m_pFixEngine);
		m_pFrontTerminal->RegisterCallback(m_fixRspClient);
		//<!--error-->
		//这里不能attach在最前面, 可能会导致qtrade创建pipeline错误
		m_reader.AttachFlow(m_pTradeResult, 0);
		m_pFixEngine->StartServer();
		m_pClientApi->Start();
		m_reactorPublish.Create();

		return true;
	}

	/**清理实例
	* @remark 清理通讯接口、流管理器、排队服务等
	*/
	virtual void ExitInstance()
	{
		m_pClientApi->Release();
		delete m_pFrontTerminal;
		delete m_pFixEngine;
		//delete m_pFrontClient;
		delete m_fixRspClient;
		delete m_pFrontForwarder;
		delete m_pTradeResult;
		delete m_pSlogResult;
	}


	virtual bool HandleOtherTask()
	{
		for (int i = 0; i<100; i++)
		{
			m_pubPackage.Allocate(XTP_PACKAGE_MAX_SIZE + XTPHLEN);
			if (!m_reader.GetNext(&m_pubPackage))
			{
				return CReactor::HandleOtherTask();
			}
			if (m_pFixEngine->HandleXTPMessage(&m_pubPackage) == 0) 
			{
				m_fixRspClient->HandleMessage(&m_pubPackage);
			}
		}
		return true;
	}

	virtual int GetHandleCount()
	{
		return m_reader.GetId();
	}

private:
	DWORD				m_dwFrontID;
	int					m_nHandleCount;
	CFibClientApi		*m_pClientApi;
	CFrontTerminal		*m_pFrontTerminal;
	CFrontForwarder		*m_pFrontForwarder;
	FixRspClient		*m_fixRspClient;
	//CGateWayClient     *m_pFrontClient;
	CFixEngine			*m_pFixEngine;
	CCachedFlow			*m_pTradeResult;
	CCachedFlow			*m_pSlogResult;
	CConfig				*m_pConfig;
	CSelectReactor		m_reactorPublish;
	CXTPPackage			m_pubPackage;
	CFlowReader			m_reader;
	CMonitorIndexTimer	*m_pMonitorIndexTimer;
	CFrontWriteLogReactor *m_pFrontWriteLogReactor;
	CCachedFileFlow		*m_pSendFlow;
	CSelectReactor		*m_pSubscribeReactor;
	CExXtpClient		*m_pMemFlowClient;
	CTradeDataClient	*m_pTradeFlowClient;
};


int main(int argc, char *argv[])
{
#ifdef UNIX
	signal(SIGABRT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, SIG_IGN);
#endif
	int i = 0;
	i++;


	//获取配置信息
	CConfig *pConfig = new CConfig(INI_FILE_NAME);

	char *syslogFileName = pConfig->getConfig("SyslogPath");
	CMonitorIndex::init(CFilelogService::CreateInstance(argc, argv, syslogFileName), pConfig);
	showVersion(argc, argv);

	delete pConfig;

	CFrontReactor *pFrontReactor;
	pFrontReactor = new CFrontReactor(1);
	pFrontReactor->Create();
	pFrontReactor->Join();
	return 0;
}

