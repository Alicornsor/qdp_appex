/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file UltraSpeedKernel.cpp
///@brief uskernel的核心框架代码
///@history 
///20130703	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////
/*MODIFICATION HISTORY:
*
*    Date      Prog.
*  DD-MMM-YYYY Init.    SIR    Modification Description
*  ----------- -------- ------ ------------------------------------------------
*  09-OCT-2015 Zhuxl    00001  Add signal process func    
******************************************************************************/

#include "platform.h"
#include "public.h"
#include "monitorIndex.h"
#include "CFilelogService.h"
#include "CConfig.h"
#include "Config.h"
#include "Thread.h"
#include "CachedFileFlow.h"
#include "SelectReactor.h"

#include "SimpleReactor.h"
#include "LockFileFlow.h"
#include "FibSubApiManager.h"
#include "TinitFlowSubscriber.h"
#include "ExchangeLinkManager.h"
//#include "KernelFront.h"
#include "UdpNetworkFactory.h"
#include "XtpData.h"
#include "MdUdpSvr.h"
#include "XtpPackageDesc.h"
#include "KernelTradeEngine.h"
#include "FibPubApiManager.h"
#include "ReqFlow.h"
#include "UsScheduler.h"
#include "FileFlow.h"
#include "version.h"
#include "TcpXtpSessionFactory.h"
#include "TcpXtpGateway.h"
#include "KernelRFront.h"
#include "KernelWriteThread.h"
#include "KernelFront.h"
#include "ExchangeLinkTimer.h"

//ppoll函数对应头文件
#ifdef LINUX
#include <poll.h>
#endif
#include "BaseExchApi.h"
#include "GatewayFront.h"



///////////////////////////////变量申明区///////////////////////////////////////////


char *INI_FILE_NAME = "qtrade.ini";
const char *APP_NAME = "qtrade";
const DWORD USKERNEL_APP_ID_BASE = 0x8600;
const int MDBUFSZ=256;//行情CMarketDataField大小为208个字节
CConfig	*g_pConfig; // 全局的配置文件对象指针，给CKernelFrontReactor 对象用 longqy 2014-03-25。

//extern const int MAXEXCHID;

//这里设置tinit的SubjectID，在uskernel需要分析出哪个包是tinit过来的
//需要和tinit对上
DWORD TINIT_SUBJECTID=0x00001121;

//在行情UDP报文广播中，由于没有使用协议栈，只保留XTP报文，故将包头设置为40(XTP报文头大小为36)
//可以一次发送更多的合约行情
//注意，这里需要和发送端一样
//#define MDXTP_PACKAGE_MAX_SIZE 2240




//vector<CBaseExchApi *> m_ExchApiArryMap;//席位信息
//vector<CSeatField *> m_InitSeatVec;//席位信息
//vector<CClientTradingIDField *> m_InitClientTradingIDVec;//客户交易编码信息
CBaseExchApi *g_pExchApiArryMap[MAXEXCHID];//各交易所APImap
//CHashMap<DWORD, CBaseExchApi *, HashInt> m_ExchApiArryMap;

CExchangeLinkManager* g_pExchangeLinkManager =NULL;

//CCachedFlow *g_pSlogResult = NULL;
CCachedFlow *g_pReadSlog = NULL;
CCachedFlow *g_pWriteSlog = NULL;
CCachedFlow *g_pQueryFlow = NULL;

bool g_bLatencyOut = false;
/*bool g_bHasShm = false;*/
bool g_bIsMultiSeat = false;

bool g_bIsQquery = false;

char g_QDPVersion = QDP_AllMarkets;

void * g_pBaseShm = NULL;

//////////////////////////////////////////////////////////////////////////
void CmdLineArgError()
{
	printf("Useage: qtrade \n");
	printf("        qtrade : start qtrade in normal，read basicdata from qdata, then query informations from exchange,last open the port\n");
	printf("        qtrade -v : show version\n");
	exit(0);
}

class CPackageHandleCounter
{
public:
	virtual int GetHandleCount() = 0;
};

//////////////////////////////////////////////////////////////////////////
//CFrontWriteLogReactor
//20130827 huwp 修改写slog慢的问题
//////////////////////////////////////////////////////////////////////////
class CFrontWriteLogTimer
{
public:
	CFrontWriteLogTimer(DWORD dwFrontID,CCachedFlow *pReadSlog,CCachedFlow *pWriteSlog=NULL)
	{
		m_pReadSlog = pReadSlog;
		char szBuffer[300];
		strcpy(szBuffer, "../flow/");
		sprintf(szBuffer+strlen(szBuffer), "%d", dwFrontID);
		strcat(szBuffer, "ftd");
		m_strFlowPathName = szBuffer;
		OpenChannelLogFile(szBuffer);
		m_reader.AttachFlow(m_pReadSlog,0);
		m_pWriteSlog = pWriteSlog;
		if (m_pWriteSlog != NULL)
		{
			m_writer.AttachFlow(m_pWriteSlog,0);
		}
	}
	virtual void Run();
	bool OpenChannelLogFile(const char *pszPath);
private:
	CCachedFlow *m_pReadSlog;
	CCachedFlow *m_pWriteSlog;
	FILE *m_fpChannelLog;
	CFlowReader m_reader;
	CFlowReader m_writer;
	string m_strFlowPathName;
	int m_nCount;					/**在cache里还没被写到文件的长度 */
};
bool CFrontWriteLogTimer::OpenChannelLogFile(const char *pszPath)
{
	char szFullFilename[512];
	sprintf(szFullFilename, "%s_%s.slog",pszPath, "00000000");
	m_fpChannelLog = fopen(szFullFilename, "ab");
	if (m_fpChannelLog == NULL)
	{
		return false;
	}
	return true;
}

void CFrontWriteLogTimer::Run()
{
	char sBuff[8192];
	int nDataLen = 8192;
	int iLen = 0;
	for (;;)
	{	
		for (int i=0;i<100;i++)
		{
			iLen = m_reader.GetNext(sBuff, nDataLen);
			if(iLen<= 0)
			{
				SLEEP(1000);
				break;
			}
			if(NULL != m_fpChannelLog)
			{
				fwrite(sBuff, 1,iLen,m_fpChannelLog);
				fflush(m_fpChannelLog);
			}
		}

		if (m_pWriteSlog != NULL)
		{
			for (int j=0;j<100;j++)
			{
				iLen = m_writer.GetNext(sBuff, nDataLen);
				if(iLen<= 0)
				{
					SLEEP(1000);
					break;
				}
				if(NULL != m_fpChannelLog)
				{
					fwrite(sBuff, 1,iLen,m_fpChannelLog);
					fflush(m_fpChannelLog);
				}
			}
		}
	}
}

CLinkReactor* g_pConnReactor =NULL;

class CXtpGateFront : public CSessionFactory,public CTcpXtpSessionCallback,public CBaseExchApi
{
public:
	CXtpGateFront(CSelectReactor *pReactor,CSelectReactor* pConnReactor=NULL) :CSessionFactory(pReactor, 500,pConnReactor)
	{
		m_pSeriesFlow =new CExCachedFlow(false, 0x7fffffff, 0x100000);
		m_reader.AttachFlow(m_pSeriesFlow,0);
	};
	
	~CXtpGateFront() {}
	virtual int HandlePackage(CXTPPackage *pPackage, CTcpXtpSession *pSession)
	{
		switch(pPackage->GetTid()) 
		{
		case FID_LifeCycleID:
			OnReqClientLogin(pPackage, pSession);
			break;
		default:
			{
				pPackage->SetAPIID(EX_PDATA);
				pPackage->SetSubjectID(PRIVATE_FLOW);
				pPackage->SetSequenceNo(0);
				pPackage->MakePackage();
				m_pSeriesFlow->Append(pPackage->Address(),pPackage->Length());
				pPackage->Pop(XTPHLEN);	
			}
			break;
		}
		return 0;
	}
	int OnReqClientLogin(CXTPPackage *pPackage, CTcpXtpSession *pSession)
	{
		CLifeCycleIDField field;
		if (XTP_GET_SINGLE_FIELD(pPackage, &field) <= 0)
		{
			return 0;
		}
		
		REPORT_EVENT(LOG_CRITICAL, "Init", "receive TCP request, requestid:%d \n",field.LifeCycleID.getValue());
		return 0;
	}
	void  Init()
	{
		m_pReactor->Create();
		Start();
	}
protected:
	virtual CSession *CreateSession(CChannel *pChannel, DWORD bIsListener)
	{
		CTcpXtpSession *pSession =  new CTcpXtpSession(m_pReactor, pChannel,this,0);
		return pSession;
	}
};


class CQTradeApp : public CThread, public CPackageHandleCounter
{
public:
	CQTradeApp(bool recover);
private:
	virtual bool InitInstance();
	virtual void ExitInstance();	
//	virtual bool HandleOtherTask();
	void Run();
	void Redo();
	virtual int GetHandleCount();
public:
 	CKernelFront* m_pKernelFront;
// 	CGateWayFront *m_pGatewayFront;
	CKernelRFront* m_pRFront;
	CKernelWriteThread* m_pWThread;
	CKernelTradeEngine* m_pKernelTradingEngine;
	bool b_FinishInit;
private:
	CConfig *m_pConfig;
	CCachedFlow *m_pTradeResult;//给前置的结果流，只包含应答和通知信息
	CCachedFlow *m_pMemChangeFlow;//增加内存表变化流，给front的信息不包含上场信息和内存表信息，减小front的负担

	CSelectReactor *m_pQdataReactor;//qdata的线程

	CXtpGateFront *m_pXtpGateFront;//tinit流订阅

	//	内存数据库表的触发器，触发时将调用这个对象。发送内存表流的变化、出入金通知等。
	CUsScheduler	*m_pMDBSchulder;
	CXTPPackage m_pubPackage;
	CFlowReader m_reader;
	int m_nTinitFlowCount;
	int m_nLifeCycleID;//生命周期号，用于通知前置打开端口时，
	//前置创建时告诉他本次的生命周期号，下次等api登陆成功之后，通知前置打开端口之时必须包含生命周期号，如果相符才真正打开端口
	//redo时产生的打开端口信息因为生命周期号与创建本前置时不一致，认为是历史信息，不真正开放端口
	CSelectReactor m_PublishReactor;//结果流发布线程
	CFibPubApiManager *m_pPubApiManager;//结果流发布Manager
	DWORD m_dwTinitSubjectID;//tinit流的订阅主题
	int m_nPipeIniID;//Pipe必须分配一个初始化的ID，重复的号码会导致问题
	bool m_bSyncDataEnd;//数据同步结束标志
	CTcpXtpGateway *m_pGateway;//结果流发布tcp
	bool m_bRecover;//是否使用流恢复,此时无需查询基础数据
};

CQTradeApp::CQTradeApp(bool recover)
{
	m_pConfig=NULL;
	m_pKernelTradingEngine=NULL;
	m_pTradeResult=NULL;
	m_pKernelFront=NULL;
	m_pQdataReactor = NULL;
	m_pubPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	m_nLifeCycleID=0;
	m_nTinitFlowCount=0;
	m_pPubApiManager =  new CFibPubApiManager(&m_PublishReactor, 0);
	m_dwTinitSubjectID=0;
	m_nPipeIniID=1;
	m_bSyncDataEnd=false;
	m_pMDBSchulder=NULL;
	m_pMemChangeFlow=NULL;
	m_pGateway = NULL;
	b_FinishInit = false;
	m_bRecover = recover;
//	m_pGatewayFront=NULL;
}

bool CQTradeApp::InitInstance()
{
#ifdef LINUX
	REPORT_EVENT(LOG_CRITICAL,"qtrade core buiness thread", " [%ld]\n", gettid());
#endif
	//创建生命周期号
	srand(time(NULL));
	m_nLifeCycleID=rand();	
	printf("LifeCycleID= 0x%x\n",m_nLifeCycleID);
	
	m_pConfig = new CConfig(INI_FILE_NAME);		
	g_pConfig = m_pConfig;
	
	PROCESS_LOG1("read config %s\n", INI_FILE_NAME);


	//创建一个基于通讯队列的通知对象
	CPipeEventHandler *pPipePublish=new CPipeEventHandler(&m_PublishReactor,m_nPipeIniID++);
	//创建TSeries,TResult,TMemChange
	char *pszFlowPath  = m_pConfig->getConfig("FlowPath");
	
	int runMode = GetConfigInt(INI_FILE_NAME,"RunMode"); 
	if(runMode==1)
	{
		m_pTradeResult =new CCachedFlow(false, 2000000, 0x200000);
	}
	else
	{
		m_pTradeResult =new CCachedFileFlow("TradeResult", pszFlowPath, true, 2000, 0x200000);
	}
	g_pQueryFlow =new CCachedFileFlow("QueryResult", pszFlowPath, false, 200000, 0x200000);	
	int RedoFlowCnt = m_pTradeResult->GetCount();

	
	//1、创建业务处理器
	m_pKernelTradingEngine = new CKernelTradeEngine(m_pConfig,m_pTradeResult);
	
	//4、创建对pdata的订阅
	m_pQdataReactor = new CSelectReactor();
	m_pXtpGateFront =  new CXtpGateFront(m_pQdataReactor,g_pConnReactor);
	g_pExchangeLinkManager->setBaseExchAPI(m_pXtpGateFront,EX_PDATA);
	
	char  *qdataAddr = m_pConfig->getConfig("qdata");
	m_pXtpGateFront->RegisterListener(qdataAddr);

	//5、结果流反演，获得各个交易所上次流的序号及pdata的续传的序列号
	m_dwTinitSubjectID=TINIT_SUBJECTID;
	Redo();	

	//6、反演结束后打开各项链接
	//5.1 打开对qdata的连接	
//	m_pSubscribeReactor->Create();
	m_pXtpGateFront->Init();

	//8.创建（但不启动）对外服务线程-前置
	if (g_QDPVersion == QDP_OnlyFuture)
	{
		m_pRFront = new CKernelRFront(g_pReadSlog,m_pConfig,m_nLifeCycleID);
		g_pExchangeLinkManager->setBaseExchAPI(m_pRFront,EX_PFRONT);
		
		g_pQueryFlow =new CCachedFileFlow("QueryResult", pszFlowPath, false, 200000, 0x200000);	
		int RedoFlowCnt = m_pTradeResult->GetCount();
		
		m_pWThread = new CKernelWriteThread(m_pTradeResult,g_pWriteSlog,1,m_nLifeCycleID);
		m_pWThread->SetRedoFlowCnt(RedoFlowCnt);
	}
	else
	{
		m_pKernelFront=new CKernelFront(m_pTradeResult,g_pReadSlog,m_nLifeCycleID,m_pConfig);	
		//创建Tresult之间与KernelFront之间的Pipe
		CPipeEventHandler *pPipe_TResult_Front=new CPipeEventHandler(m_pKernelFront,m_nPipeIniID++);
		m_pTradeResult->AttachObserver(pPipe_TResult_Front);
		//m_ExchApiArryMap[EX_PFRONT] = m_pKernelFront;	
		g_pExchangeLinkManager->setBaseExchAPI(m_pKernelFront,EX_PFRONT);
	}


	//9、结果流的发布 改成traderresult流发布  chengm 20170620
	char  *memchangeAddr = m_pConfig->getConfig("memchange");
	m_pGateway=new CTcpXtpGateway(&m_PublishReactor,m_pTradeResult,g_pConnReactor);
	m_pGateway->RegisterListener(memchangeAddr);
	m_pGateway->Init();

#ifdef LINUX
	if(g_bBindThreadsToCPU)
	{  
		// 线程绑定CPU
		BindThd2CPU(pthread_self(),g_n_cpucount-2);
	}
#endif
	
	//启动监控定时
	//m_pMonitorTimer= new CMonitorTimer(this);
	//m_pMonitorTimer->StartTimer();
	b_FinishInit = true;
	return true;
}

void CQTradeApp::Redo()
{	
	REPORT_EVENT(LOG_CRITICAL,"Redo","begin redo!\n");
	m_reader.AttachFlow(m_pTradeResult,0);
	for(int i=1; ;i++)
	{
		m_pubPackage.Allocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN);
		if(!m_reader.GetNext(&m_pubPackage))
		{
			break;
		}

		m_pubPackage.SetNoReplayFlag(false);		
		m_pKernelTradingEngine->handleMessage(&m_pubPackage);	
		//CBaseExchApi *pBaseApi = m_ExchApiArryMap[m_pubPackage.GetAPIID()];
		CBaseExchApi *pBaseApi = g_pExchangeLinkManager->getExchangeLink(m_pubPackage.GetAPIID());
		if(pBaseApi == NULL)
		{
			continue;		
		}
		if(m_pubPackage.GetSubjectID() == PRIVATE_FLOW)
		{
			pBaseApi->m_PrivateSeqNO = m_pubPackage.GetSequenceNo();
		}
		else if (m_pubPackage.GetSubjectID() == PUBLIC_FLOW)
		{	
			pBaseApi->m_PublicSeqNO = m_pubPackage.GetSequenceNo();			
		}	
		//20121230
		if (m_pubPackage.GetTid()==TID_DataSyncEnd)
		{	
			m_bSyncDataEnd=true;
			REPORT_EVENT(LOG_CRITICAL,"Redo","redo datasyncend!\n");
		}
	}

	//是否导出由配置文件决定
//	char* pDumpFlag=m_pConfig->getConfig("DumpAfterRedo");
//	if (!strcmp(pDumpFlag,"yes"))
//	{
//		m_pKernelTradingEngine->DumpMemDb();
//	}
	
	REPORT_EVENT(LOG_CRITICAL,"Redo","end redo，the data in memory database are dumped into the files!\n");
}


int CQTradeApp::GetHandleCount()
{
	return 0;
}

void CQTradeApp::ExitInstance()
{	
}

void CQTradeApp::Run()
{
	while(true)
	{	
		for (int j=0; j<=g_pExchangeLinkManager->m_iMaxAPIID; j++)
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
				if(!pBaseApi->GetNextUseNoBuf(&m_pubPackage))
				{
					break;
				}				

				m_pubPackage.SetNoReplayFlag(true);
				m_pKernelTradingEngine->handleMessage(&m_pubPackage);
			}
		}
	 }
}	

typedef double TFtdcShortFrozenMarginType;

/*** SIR 00001 BEGIN ***/
#ifdef LINUX
void SignHandler(int iSignNo)
{
	switch(iSignNo)
	{
		case SIGABRT:
			REPORT_EVENT(LOG_CRITICAL,"SignHandler","Rcv system signal[%d](SIGABRT), app exit\n", iSignNo);
			exit(0);
		case SIGINT:
			REPORT_EVENT(LOG_CRITICAL,"SignHandler","Rcv system signal[%d](SIGINT), app exit\n", iSignNo);
			exit(0);
		case SIGPIPE:
			REPORT_EVENT(LOG_CRITICAL,"SignHandler","Rcv system signal[%d](SIGPIPE), app ignore this signal\n", iSignNo);
			return;
		default:              //出现其他信号，程序不应退出
			return;
	}
}
#endif
/*** SIR 00001 END ***/

int main(int argc, char *argv[])
{
	CConfig *pConfig = new CConfig(INI_FILE_NAME);
	
#ifdef LINUX
/*** SIR 00001 BEGIN ***/
	signal(SIGABRT, SignHandler);    //提示并退出
	signal(SIGPIPE, SignHandler);    //忽略SIGPIPE
	signal(SIGINT, SignHandler);     //提示并退出
/*** SIR 00001 END ***/

	
	g_n_cpucount=sysconf(_SC_NPROCESSORS_CONF);	
	printf("this machine has %d cpus\n",g_n_cpucount);

	// 读取绑定CPU的标志
	if (!strcmp(pConfig->getConfig("BindThreadsToCPU"),"yes"))
	{
		g_bBindThreadsToCPU = true;
		REPORT_EVENT(LOG_CRITICAL,"BindThreadsToCPU = yes", "In CQTradeApp Init.\n");
		int nCPUs=(g_n_cpucount < MAX_CPU_COUNT)?g_n_cpucount:MAX_CPU_COUNT;
		for(int i=0;i<nCPUs;i++)
		{
			g_bBinded[i]=false;
		}
	}
	else
	{
		REPORT_EVENT(LOG_CRITICAL,"BindThreadsToCPU = no", "In CQTradeApp Init.\n");
	}

	//if(g_bBindThreadsToCPU){ // 在主线程中绑定，实际上，是把所有的子线程绑定在同一个核上。
	//	BindThd2CPU(pthread_self());
	//}

#endif

	if (strncmp(pConfig->getConfig("IsMultiSeat"),"yes",3)==0)
	{
		g_bIsMultiSeat = true;
	}

	char *syslogFileName=pConfig->getConfig("SyslogPath");
	CMonitorIndex::init(CFilelogService::CreateInstance(argc,argv,syslogFileName),pConfig);

	if (argc >2 || (argc ==2 && strcmp(argv[1], "-h")==0))
	{
		CmdLineArgError();
	}

	showVersion(argc,argv);


	if (strncmp(pConfig->getConfig("LatencyOut"),"yes",3)==0)
	{
		g_bLatencyOut = true;
	}

	g_QDPVersion = pConfig->getConfig("Version")[0];
	//创建各交易所的报盘机
	memset(g_pExchApiArryMap,0,sizeof(g_pExchApiArryMap));

	g_pExchangeLinkManager = new CExchangeLinkManager(INI_FILE_NAME,pConfig);

	int linkInterval = atoi(pConfig->getConfig("LinkLoopTime"));
	g_pConnReactor=new CLinkReactor(g_pExchangeLinkManager,g_pExchApiArryMap,linkInterval);

	g_pReadSlog =new CCachedFlow(false, 2000000, 0x100000);
	if (g_QDPVersion == QDP_OnlyFuture)
	{
		g_pWriteSlog =new CCachedFlow(false, 2000000, 0x100000);
	}
	
// 	int linkInterval = atoi(pConfig->getConfig("LinkLoopTime"));
// 	CLinkTimer *linkTimer = new CLinkTimer(g_pConnReactor,g_pExchangeLinkManager, linkInterval
	g_pConnReactor->Create();
	
#ifdef LINUX
	REPORT_EVENT(LOG_CRITICAL,"qtrade main thread", " [%ld]\n", gettid());
#endif

	int nSleepTime = GetConfigInt(INI_FILE_NAME,"SleepBeforeOpen");
	bool recover = false;
	if(argc ==2 && strcmp(argv[1], "-r")==0)
	{
		//如果没有查询交易所的动作,主线程完成之后休息1秒钟即打开端口
		nSleepTime = 1;
		recover = true;
	}

	CQTradeApp app(recover);
	app.Create();

	//等待交易所流接收完成然后--前置端口打开
	while(!app.b_FinishInit)
	{
		SLEEP_SECONDS(1);
	//	printf("sleep 1 \n");
	}

	SLEEP_SECONDS(nSleepTime);

	//报单检查需要检查系统状态是否正确合约状态是否正确
	if(app.m_pKernelTradingEngine->GetSystemStatus()!=SS_InstrumentTradingDayDown)
	{
		app.m_pKernelTradingEngine->ChangeSystemStatus(SS_InstrumentTradingDayDown);
		//发送
		//由于状态改变之后，需要做很多操作，这里休息1秒之后再打开端口
		//操作包括：1、导出内存数据库 2、大边保证金计算
		SLEEP_SECONDS(1);
	}

	if (g_QDPVersion == QDP_OnlyFuture)
	{
		app.m_pWThread->Create();
		app.m_pRFront->FrontStartWork();
	}
	else
	{
		app.m_pKernelFront->FrontStartWork();
	}
	
	CFrontWriteLogTimer SlogWriter(0,g_pReadSlog,g_pWriteSlog);
	SlogWriter.Run();


	app.Join();
	g_pConnReactor->Join();

	return 0;
}
