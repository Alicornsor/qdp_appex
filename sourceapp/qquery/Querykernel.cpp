// Querykernel.cpp: 
//
// 20070828 王维 修改monitorIndex的初始化
// 20090510 王维 NT-0074：Reactor派生类原重载DispatchIOs改为重载HandleOtherTask
// 20090618 王维 NT-0084:屏蔽SIGPIPE等信号
/////////////////////////////////////////////////////////////////////////

#include "public.h"
#include "SelectReactor.h"
#include "Config.h"
#include "FibSubApiManager.h"
#include "FibServerApi.h"
#include "CachedFileFlow.h"
#include "FileFlow.h"
#include "FlowReader.h"
#include "TradingQueryEngine.h"
#include "FlowSubscriber.h"
#include "monitorIndex.h"
#include "version.h"
#include "tradingTools.h"
#include "CFilelogService.h"
#include "TcpXtpSessionFactory.h"
#include "XtpClient.h"
#include "BaseExchApi.h"
#include "ExchangeLinkManager.h"
//#include "CheckFlowSubscriber.h"
//#include "PreMessageHandle.h"

#include "TMDBEngine.h"
#include "TMDBScheduler.h"
#include "AccomplishFlow.h"
#include "printinfo.h"

const DWORD TQUERY_APP_ID_BASE = 0x2300;

CBaseExchApi *g_pExchApiArryMap[MAXEXCHID];//各交易所APImap
//CHashMap<DWORD, CBaseExchApi *, HashInt> m_ExchApiArryMap;

CExchangeLinkManager* g_pExchangeLinkManager =NULL;

bool g_bLatencyOut = false;

CFlow *g_pMemResult =NULL;

bool g_bIsMultiSeat = false;

CConfig *g_pConfig = NULL;

CSelectReactor* g_pConnReactor =NULL;

bool g_bIsQquery = false;

//////////////////////////////////////////////////////////////////////////
//CQkernelSubscribeReactor
//////////////////////////////////////////////////////////////////////////
class CExXtpClient : public CXtpClient
{
public:
	CExXtpClient(CSelectReactor *pReactor,CFlow *pSerailFlow)
		:CXtpClient(pReactor,pSerailFlow,0,g_pConnReactor)
	{
		
		m_LoginPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN, 1000);
		m_nsubcount = 0;
	}
	
	virtual CSession* CreateSession(CChannel *pChannel, DWORD dwMark)
	{
		CTcpXtpSession *pSession = new CTcpXtpSession(m_pReactor, pChannel,this);
		return pSession;
	}
	
	virtual void OnSessionConnected(CSession *pSession)
	{
		m_bConnected = true;
		CSessionFactory::OnSessionConnected(pSession);
		m_pSession = (CTcpXtpSession *)pSession;
		InterLogin(m_pSession);
	}
	
	void InterLogin(CTcpXtpSession *pSession)
	{
		CLifeCycleIDField field;
		field.LifeCycleID=m_nsubcount;
		
		m_LoginPackage.PreparePublish(FID_LifeCycleID);
		m_LoginPackage.AddField(&CLifeCycleIDField::m_Describe,&field);
		if (pSession)
		{
			pSession->SendReportPackage(&m_LoginPackage);
		}
	}
	
	virtual void OnSessionDisconnected(CSession *pSession, int nReason)
	{
		//设置为不可发送
		m_bConnected = false;
		CSessionFactory::OnSessionDisconnected(pSession, nReason);
	}
	
	int HandlePackage(CXTPPackage *pXTPPackage, CTcpXtpSession *pSession)
	{
		pXTPPackage->MakePackage();
		m_pSerialFlow->Append(pXTPPackage->Address(),pXTPPackage->Length());
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
	CTradeDataClient(CSelectReactor *pReactor,CFlow *pSerailFlow)
		:CXtpClient(pReactor,pSerailFlow,0,g_pConnReactor)
	{
		
		m_LoginPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN, 1000);
		m_nsubcount = 0;
	}
	
	virtual CSession* CreateSession(CChannel *pChannel, DWORD dwMark)
	{
		CTcpXtpSession *pSession = new CTcpXtpSession(m_pReactor, pChannel,this);
		pSession->PublishFlow(m_pSerialFlow,0);
		return pSession;
	}
	
	virtual void OnSessionConnected(CSession *pSession)
	{
		m_bConnected = true;
		CSessionFactory::OnSessionConnected(pSession);
		m_pSession = (CTcpXtpSession *)pSession;
		InterLogin(m_pSession);
	}
	
	void InterLogin(CTcpXtpSession *pSession)
	{
		CLifeCycleIDField field;
		field.LifeCycleID=m_nsubcount;
		
		m_LoginPackage.PreparePublish(FID_LifeCycleID);
		m_LoginPackage.AddField(&CLifeCycleIDField::m_Describe,&field);
		if (pSession)
		{
			pSession->SendReportPackage(&m_LoginPackage);
		}
	}
	
	virtual void OnSessionDisconnected(CSession *pSession, int nReason)
	{
		//设置为不可发送
		m_bConnected = false;
		CSessionFactory::OnSessionDisconnected(pSession, nReason);
	}
	
	int HandlePackage(CXTPPackage *pXTPPackage, CTcpXtpSession *pSession)
	{
		pXTPPackage->MakePackage();
		m_pSerialFlow->Append(pXTPPackage->Address(),pXTPPackage->Length());
		pXTPPackage->Pop(XTPHLEN);
		m_nsubcount++;		
		return 0;
	}
	
private:
	CXTPPackage m_LoginPackage;
	int m_nsubcount;
};

//////////////////////////////////////////////////////////////////////////
//CQkernelServer
//////////////////////////////////////////////////////////////////////////
class CQkernelServer : public CService  
{	
public:
	CQkernelServer(CEngine* pEngine)
	{
		m_pTradingEngine = pEngine;
	}
	virtual ~CQkernelServer()
	{
	}

	virtual void OnRequest(CXTPPackage *pRequest,DWORD dwSessionID)
	{
		m_pTradingEngine->handleRequest(pRequest, dwSessionID);
	}
	virtual void OnSessionConnected(DWORD nSessionID)
	{
	}
	virtual void OnSessionDisconnected(DWORD nSessionID)
	{
	}
private:
	CEngine *m_pTradingEngine;
};

//add by zbz
//目的是说明本进程是否在运行
class CLocalTimerLog  : public CEventHandler
{
public:
	CLocalTimerLog(CReactor *pReactor);
	virtual ~CLocalTimerLog() {}
	virtual void OnTimer(int nIDEvent);
};

CLocalTimerLog::CLocalTimerLog(CReactor *pReactor):CEventHandler(pReactor)
{
	SetTimer(1, 1000);
}

void CLocalTimerLog::OnTimer(int nIDEvent)
{
	CMonitorIndex::handleOne();
}


////////////////////////////////////////////////////////////////////////////////////////////
//CFrontTimeSyncTimer

const int FRONT_TIME_SYNC_TIMER_ID=0x000009600;//前置定时器
const int FRONT_TIME_SYNC_TIMER_FREQUENCY=1000;//毫秒

class CFrontTimeSyncTimer : public CEventHandler
{
public:
	CFrontTimeSyncTimer(CReactor *pReactor,CFlow* pFlow):CEventHandler(pReactor)
	{
		m_pLockFlow=pFlow;
		m_pNotifyPackage = CXTPPackage::CreatePackage(1000);
		this->SetTimer(FRONT_TIME_SYNC_TIMER_ID,FRONT_TIME_SYNC_TIMER_FREQUENCY);
	}
protected:
	virtual void OnTimer(int nIDEvent)
	{
		//		printf("OnTimer\n");
		switch(nIDEvent)
		{
			//定时信息增加到kernel的输入流
		case FRONT_TIME_SYNC_TIMER_ID:
			{
				SyncTime();
				CCurrentTimeField timeField;
				timeField.CurrDate = getCurrDate();//日期暂时填
				time_t dwCurrTime = (time_t)m_nCurrTime;
				strftime(m_timeBuffer, sizeof(timeField.CurrTime),"%H:%M:%S",localtime(&dwCurrTime));
				timeField.CurrTime=m_timeBuffer;
				timeField.CurrMillisec = m_nCurrMilTime;
				
				m_pNotifyPackage->PreparePublish(TID_NtfTimeSync);
				XTP_ADD_FIELD(m_pNotifyPackage, &timeField);
				m_pNotifyPackage->MakePackage();				
				m_pLockFlow->Append(m_pNotifyPackage->Address(), m_pNotifyPackage->Length());	
				break;
			}	
		}
	}	
private:
	void SyncTime()
	{
#ifdef WIN32	
		struct _timeb timebuffer;
		_ftime( &timebuffer );
		m_nCurrTime = (DWORD)timebuffer.time;	
		m_nCurrMilTime = timebuffer.millitm;
		m_nCurrClock = m_nCurrTime*1000 + timebuffer.millitm;
#else
		struct timeval timeout;
		gettimeofday(&timeout, 0);
		m_nCurrTime = timeout.tv_sec;	
		m_nCurrMilTime = timeout.tv_usec/1000;
		m_nCurrClock = m_nCurrTime*1000 + timeout.tv_usec/1000;
#endif
	}
private:
	CXTPPackage *m_pNotifyPackage;//时钟包
	char m_timeBuffer[20];//存放当前时间	
	CFlow* m_pLockFlow;//流文件
	DWORD m_nCurrTime;//当前系统时间秒
	DWORD m_nCurrMilTime;//当前系统时间毫秒
	DWORD m_nCurrClock;//当前滴答数
};

//////////////////////////////////////////////////////////////////////////
//CQkernelApp
//////////////////////////////////////////////////////////////////////////

class CPackageHandleCounter
{
public:
	virtual ~CPackageHandleCounter(){};
	
	virtual int GetHandleCount() = 0;
};

class CQkernelApp : public CSelectReactor, public CPackageHandleCounter, public CBaseExchApi
{
public:
	CQkernelApp(CConfig *pConfig);
private:
	virtual bool InitInstance();
	virtual void ExitInstance();	
	virtual bool HandleOtherTask();
	virtual int GetHandleCount();
private:
	CSelectReactor *m_pSubscribeReactor;
	CCachedFileFlow *m_pTradeResult;
	CFlowReader m_TradeReader;
	DWORD m_dwQkernelID;
	bool m_recovery;
	CCachedFileFlow *m_pSendFlow;
	CFibSubApiManager *m_pSubApiManager;
	CFibServerApi    *m_pServerApi;
	CFlowSubscriber *m_pQkernelSubscriber;
	CEngine		   *m_pTradingEngine;
	CConfig		   *m_pConfig;
	CQkernelServer *m_pQkernelServer;
	CXTPPackage m_pubPackage;
	CXTPPackage m_TradePackage;
//	CTcpXtpSessionFactory *m_pSubServer;
	CExXtpClient *m_pMemFlowClient;
	CTradeDataClient *m_pTradeFlowClient;//推送给qtrade的持仓盈亏流
	CUsScheduler	*m_pMDBSchulder;
	CFrontTimeSyncTimer* m_pFrontTimeSyncTimer;//定时器，输出到pTSeries
};

CQkernelApp::CQkernelApp(CConfig *pConfig)
{
	m_pubPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	m_TradePackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	m_pTradeResult = NULL;
	m_pSendFlow = NULL;
	m_pSubApiManager =  NULL;
	m_pServerApi = NULL;
	m_pQkernelServer = NULL;
	m_pQkernelSubscriber = NULL;
	m_pTradingEngine = NULL;
	m_pConfig = pConfig;
	m_pMemFlowClient = NULL;
	m_pTradeFlowClient = NULL;
	m_pMDBSchulder = NULL;
	m_pFrontTimeSyncTimer = NULL;

	m_pSeriesFlow =new CExCachedFlow(false, 0xffff, 0x100000);
	m_reader.AttachFlow(m_pSeriesFlow,0);
}

const char *APP_NAME = "qquery";
char *INI_FILE_NAME = "qquery.ini";
const char *SUBSCRIBE_FLOW_NAME = "ResultFlowName";  //结果流的名字配置在 .ini文件中

bool CQkernelApp::InitInstance()
{
	m_pServerApi = CFibServerApi::CreateServerApi(this, 2, 500);
	
//	m_pConfig = new CConfig(INI_FILE_NAME);	
	//获取配置信息
	PROCESS_LOG1("read config %s\n", INI_FILE_NAME);

	char *pszFlowPath  = m_pConfig->getConfig("FlowPath");
//	char *pszResultFlowName = m_pConfig->getConfig((char *)SUBSCRIBE_FLOW_NAME);
	///-------
	//	林惜斌，20061115：调整了缓冲区大小，以提高性能  20130225, longqy 文件流改为不重用
 	///-------
	m_pTradeResult = new CCachedFileFlow("TradeResult", pszFlowPath, false, 2000000, 0x20000);

	m_TradeReader.AttachFlow(m_pTradeResult,0);

	m_pSendFlow = new CCachedFileFlow("SendResult", pszFlowPath, false, 2000000, 0x20000);
//	new CIntPtrMonitorIndex("tseriesLen",m_pTradeResult->GetCountPtr(),20);

	//创建送给报盘的内存流TReq
	m_pMDBSchulder = new CUsScheduler(g_pMemResult);
			
	//创建本机日志驱动
	CLocalTimerLog  *pTimerLog = new CLocalTimerLog(this);

	//创建LinkManageer
	g_pExchangeLinkManager = new CExchangeLinkManager(INI_FILE_NAME,m_pConfig);
	if (strcmp(m_pConfig->getConfig("qmarket"),""))
	{
		//行情作为一个特殊的link，我们在这里设置
		CSeatField SeatField;
		memset(&SeatField,0,sizeof(SeatField));
		SeatField.APIID=EX_PMarket;
		SeatField.ApiLinkType = ALT_QDPMD;
		SeatField.ExchangeID = "QDPMD";
		SeatField.IsActive = true;
		SeatField.ParticipantID =  m_pConfig->getConfig("qmPartID");
		SeatField.SeatID =  m_pConfig->getConfig("qmUserID");
		SeatField.SeatPassword =  m_pConfig->getConfig("qmPassWD");
		SeatField.FrontAddr =  m_pConfig->getConfig("qmarket");
		
		if(SeatField.FrontAddr.isNull())
		{
			REPORT_EVENT(LOG_CRITICAL,"qquery","qmarket front address is null qmarket not active");
		}
		else
		{
			g_pExchangeLinkManager->initLink(&SeatField);
		}
	}
	
	m_pTradingEngine = new CTradingQueryEngine(m_pConfig, m_pServerApi,m_pSendFlow,m_pMDBSchulder,m_recovery);	
	m_pQkernelServer = new CQkernelServer(m_pTradingEngine); 	
	
	m_pSubscribeReactor = new CSelectReactor();
	m_pMemFlowClient = new CExXtpClient(m_pSubscribeReactor, m_pTradeResult);
	char *pmemchange  = m_pConfig->getConfig("memchange");
	m_pMemFlowClient->RegisterConnecter(pmemchange);
	m_pMemFlowClient->Init();
	REPORT_EVENT(LOG_CRITICAL,"pmemchange","pmemchange 端口订阅为 %s\n",pmemchange);

	m_pTradeFlowClient = new CTradeDataClient(m_pSubscribeReactor, m_pSendFlow);
	char *qdata  = m_pConfig->getConfig("qdata");
	m_pTradeFlowClient->RegisterConnecter(qdata);
	m_pTradeFlowClient->Init();
	REPORT_EVENT(LOG_CRITICAL,"qtrade","qtrade 端口订阅为 %s\n",qdata);

	char *pqquery  = m_pConfig->getConfig("qquery");
	m_pServerApi->RegisterListener(pqquery);
	m_pServerApi->RegisterService(m_pQkernelServer);

	if(m_pFrontTimeSyncTimer==NULL &&
		strncmp(m_pConfig->getConfig("CalcDynamicProfitSwitch"),"yes",3)==0)
	{
		m_pFrontTimeSyncTimer = new CFrontTimeSyncTimer(this,m_pSeriesFlow);
		g_pExchangeLinkManager->setBaseExchAPI(this,EX_PDATA);//解压EX_PDATA
	}

	g_pExchangeLinkManager->StartWork();

	
	REPORT_EVENT(LOG_CRITICAL,"qquery","qquery 查询端口开放为 %s\n",pqquery);

	REPORT_EVENT(LOG_CRITICAL,"InitInstance","初始化完成!\n");
	return true;
}

int CQkernelApp::GetHandleCount()
{
	return m_TradeReader.GetId();
}

void CQkernelApp::ExitInstance()
{
	m_pServerApi->Release();
	delete m_pSubApiManager;
	delete m_pSubscribeReactor;
	delete m_pQkernelSubscriber;
	delete m_pQkernelServer;	
	delete m_pTradingEngine;
	delete m_pConfig;
}

bool CQkernelApp::HandleOtherTask()
{
	int i=0;
	for (i=0; i<100; i++)
	{
		m_TradePackage.Allocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN);
		if(!m_TradeReader.GetNext(&m_TradePackage))
		{
			break;
		}
		m_pubPackage.SetNoReplayFlag(false);
		m_pTradingEngine->handleMessage(&m_TradePackage);
	}

	for (int j=0; j<=EX_PMarket; j++)
	{
		CBaseExchApi *pBaseApi = g_pExchApiArryMap[j];
		if(pBaseApi == NULL)
		{
			continue;
		}
		///200150616 xuzh 考虑到交易所查询流必须在所有的流水之前，使用标识符控制
		///输入流水的顺序：qdata上场流水->交易所查询流水->交易所推送流水
		for (int i=0; i<100; i++)
		{	
			///试探是否可以读流水
//			m_pubPackage.Allocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN);
			if(!pBaseApi->GetNextUseNoBuf(&m_pubPackage))
			{
				break;
			}				
			
			m_pubPackage.SetNoReplayFlag(true);
			m_pTradingEngine->handleMessage(&m_pubPackage);
		}
	}
 	if (i>0)
	{
		return true;
	}
	//return true;
	return CSelectReactor::HandleOtherTask();
}

//////////////////////////////////////////////////////////////////////////
//CTmdbApp
class CTmdbApp : public CSelectReactor
{
public:
	CTmdbApp(CConfig *pConfig);
private:
	virtual bool InitInstance();
	virtual void ExitInstance();	
	virtual bool HandleOtherTask();

private:
	CFlow *m_pTradeResult;
	CAccomplishFlow *m_pAccomplishFlow;
	CTMDBEngine	*m_pTMDBEngine;
	CConfig		*m_pConfig;
	CTMDBScheduler	*m_pTMDBSchulder;
	CXTPPackage m_pubPackage;
	CFlowReader m_reader;
};

CTmdbApp::CTmdbApp(CConfig *pConfig)
{
	m_pTradeResult = NULL;
	m_pAccomplishFlow = NULL;
	m_pTMDBEngine = NULL;
	m_pConfig = pConfig;
	m_pubPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	m_pTMDBSchulder = NULL;
}

bool CTmdbApp::InitInstance()
{
	//获取配置信息
	PROCESS_LOG1("read config %s\n", INI_FILE_NAME);
	m_pConfig = new CConfig(INI_FILE_NAME);	

	char *pszFlowPath  = m_pConfig->getConfig("FlowPath");

	char szBuffer[300];
	char dbname[300];
	char dbpasswd[300];
	char dbuser[300];
	GetConfigString(INI_FILE_NAME, "dbname",szBuffer, sizeof(szBuffer));
	strncpy(dbname,szBuffer,sizeof(szBuffer));
	GetConfigString(INI_FILE_NAME, "dbuser",szBuffer, sizeof(szBuffer));
	strncpy(dbuser,szBuffer,sizeof(szBuffer));
	GetConfigString(INI_FILE_NAME, "dbpasswd",szBuffer, sizeof(szBuffer));
	strncpy(dbpasswd,szBuffer,sizeof(szBuffer));

	m_pAccomplishFlow =	new CAccomplishFlow();
	if(	!m_pAccomplishFlow->ConnectDB(dbname, dbuser, dbpasswd))
	{
		REPORT_EVENT(LOG_CRITICAL, "Database", "AccomplishFlow connect db error");
		return false;
	}
	else
	{
		REPORT_EVENT(LOG_CRITICAL, "Database", "Connected to database ... %s/%s@%s",dbuser,"******",dbname);
	}

	m_pTMDBSchulder = new CTMDBScheduler(this, m_pAccomplishFlow, pszFlowPath);
	if(!m_pTMDBSchulder->Init(dbname,dbuser,dbpasswd))
	{
		REPORT_EVENT(LOG_CRITICAL, APP_NAME, "TMDBSchulder init failure");
		return false;
	}


	m_pTMDBEngine = new CTMDBEngine(m_pTMDBSchulder,m_pConfig->getConfig("Brokers"),m_pConfig->getConfig("Exchanges"));	

	m_pTradeResult = g_pMemResult;

	m_reader.AttachFlow(m_pTradeResult,0);

	return true;
}

void CTmdbApp::ExitInstance()
{
	delete m_pTMDBEngine;
	delete m_pTMDBSchulder;
	delete m_pAccomplishFlow;
	delete m_pTradeResult;
}

bool CTmdbApp::HandleOtherTask()
{
	for (int i=0; i<100; i++)
	{
		m_pubPackage.Allocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN);
		if(!m_reader.GetNext(&m_pubPackage))
		{
			return CSelectReactor::HandleOtherTask();
		}
		m_pubPackage.SetSequenceNo(m_reader.GetId());
		m_pTMDBEngine->handleMessage(&m_pubPackage);
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
//main
//////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	showVersion(argc,argv);		//20090618 王维 移到前面，只看版本时不需要读配置文件

	//获取配置信息 
	g_pConfig = new CConfig(INI_FILE_NAME);	

	g_pMemResult = new CCachedFileFlow("MemResult", g_pConfig->getConfig("FlowPath"), false, 2000000, 0x20000);	

	g_bIsQquery = true;

	g_pConnReactor=new CSelectReactor();
	
	g_pConnReactor->Create();

	char *syslogFileName=g_pConfig->getConfig("SyslogPath");
	CMonitorIndex::init(CFilelogService::CreateInstance(argc,argv,syslogFileName),g_pConfig);

	setTradingSystemName(g_pConfig);
	
	CQkernelApp app(g_pConfig);
	app.Create();
	
	CTmdbApp tmdbApp(g_pConfig);
	tmdbApp.Create();

	app.Join();
	tmdbApp.Join();
	return 0;
}
