/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file UltraSpeedKernel.cpp
///@brief uskernel�ĺ��Ŀ�ܴ���
///@history 
///20130703	hwp		�������ļ�
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

//ppoll������Ӧͷ�ļ�
#ifdef LINUX
#include <poll.h>
#endif
#include "BaseExchApi.h"
#include "GatewayFront.h"



///////////////////////////////����������///////////////////////////////////////////


char *INI_FILE_NAME = "qtrade.ini";
const char *APP_NAME = "qtrade";
const DWORD USKERNEL_APP_ID_BASE = 0x8600;
const int MDBUFSZ=256;//����CMarketDataField��СΪ208���ֽ�
CConfig	*g_pConfig; // ȫ�ֵ������ļ�����ָ�룬��CKernelFrontReactor ������ longqy 2014-03-25��

//extern const int MAXEXCHID;

//��������tinit��SubjectID����uskernel��Ҫ�������ĸ�����tinit������
//��Ҫ��tinit����
DWORD TINIT_SUBJECTID=0x00001121;

//������UDP���Ĺ㲥�У�����û��ʹ��Э��ջ��ֻ����XTP���ģ��ʽ���ͷ����Ϊ40(XTP����ͷ��СΪ36)
//����һ�η��͸���ĺ�Լ����
//ע�⣬������Ҫ�ͷ��Ͷ�һ��
//#define MDXTP_PACKAGE_MAX_SIZE 2240




//vector<CBaseExchApi *> m_ExchApiArryMap;//ϯλ��Ϣ
//vector<CSeatField *> m_InitSeatVec;//ϯλ��Ϣ
//vector<CClientTradingIDField *> m_InitClientTradingIDVec;//�ͻ����ױ�����Ϣ
CBaseExchApi *g_pExchApiArryMap[MAXEXCHID];//��������APImap
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
	printf("        qtrade : start qtrade in normal��read basicdata from qdata, then query informations from exchange,last open the port\n");
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
//20130827 huwp �޸�дslog��������
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
	int m_nCount;					/**��cache�ﻹû��д���ļ��ĳ��� */
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
	CCachedFlow *m_pTradeResult;//��ǰ�õĽ������ֻ����Ӧ���֪ͨ��Ϣ
	CCachedFlow *m_pMemChangeFlow;//�����ڴ��仯������front����Ϣ�������ϳ���Ϣ���ڴ����Ϣ����Сfront�ĸ���

	CSelectReactor *m_pQdataReactor;//qdata���߳�

	CXtpGateFront *m_pXtpGateFront;//tinit������

	//	�ڴ����ݿ��Ĵ�����������ʱ������������󡣷����ڴ�����ı仯�������֪ͨ�ȡ�
	CUsScheduler	*m_pMDBSchulder;
	CXTPPackage m_pubPackage;
	CFlowReader m_reader;
	int m_nTinitFlowCount;
	int m_nLifeCycleID;//�������ںţ�����֪ͨǰ�ô򿪶˿�ʱ��
	//ǰ�ô���ʱ���������ε��������ںţ��´ε�api��½�ɹ�֮��֪ͨǰ�ô򿪶˿�֮ʱ��������������ںţ��������������򿪶˿�
	//redoʱ�����Ĵ򿪶˿���Ϣ��Ϊ�������ں��봴����ǰ��ʱ��һ�£���Ϊ����ʷ��Ϣ�����������Ŷ˿�
	CSelectReactor m_PublishReactor;//����������߳�
	CFibPubApiManager *m_pPubApiManager;//���������Manager
	DWORD m_dwTinitSubjectID;//tinit���Ķ�������
	int m_nPipeIniID;//Pipe�������һ����ʼ����ID���ظ��ĺ���ᵼ������
	bool m_bSyncDataEnd;//����ͬ��������־
	CTcpXtpGateway *m_pGateway;//���������tcp
	bool m_bRecover;//�Ƿ�ʹ�����ָ�,��ʱ�����ѯ��������
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
	//�����������ں�
	srand(time(NULL));
	m_nLifeCycleID=rand();	
	printf("LifeCycleID= 0x%x\n",m_nLifeCycleID);
	
	m_pConfig = new CConfig(INI_FILE_NAME);		
	g_pConfig = m_pConfig;
	
	PROCESS_LOG1("read config %s\n", INI_FILE_NAME);


	//����һ������ͨѶ���е�֪ͨ����
	CPipeEventHandler *pPipePublish=new CPipeEventHandler(&m_PublishReactor,m_nPipeIniID++);
	//����TSeries,TResult,TMemChange
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

	
	//1������ҵ������
	m_pKernelTradingEngine = new CKernelTradeEngine(m_pConfig,m_pTradeResult);
	
	//4��������pdata�Ķ���
	m_pQdataReactor = new CSelectReactor();
	m_pXtpGateFront =  new CXtpGateFront(m_pQdataReactor,g_pConnReactor);
	g_pExchangeLinkManager->setBaseExchAPI(m_pXtpGateFront,EX_PDATA);
	
	char  *qdataAddr = m_pConfig->getConfig("qdata");
	m_pXtpGateFront->RegisterListener(qdataAddr);

	//5����������ݣ���ø����������ϴ�������ż�pdata�����������к�
	m_dwTinitSubjectID=TINIT_SUBJECTID;
	Redo();	

	//6�����ݽ�����򿪸�������
	//5.1 �򿪶�qdata������	
//	m_pSubscribeReactor->Create();
	m_pXtpGateFront->Init();

	//8.������������������������߳�-ǰ��
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
		//����Tresult֮����KernelFront֮���Pipe
		CPipeEventHandler *pPipe_TResult_Front=new CPipeEventHandler(m_pKernelFront,m_nPipeIniID++);
		m_pTradeResult->AttachObserver(pPipe_TResult_Front);
		//m_ExchApiArryMap[EX_PFRONT] = m_pKernelFront;	
		g_pExchangeLinkManager->setBaseExchAPI(m_pKernelFront,EX_PFRONT);
	}


	//9��������ķ��� �ĳ�traderresult������  chengm 20170620
	char  *memchangeAddr = m_pConfig->getConfig("memchange");
	m_pGateway=new CTcpXtpGateway(&m_PublishReactor,m_pTradeResult,g_pConnReactor);
	m_pGateway->RegisterListener(memchangeAddr);
	m_pGateway->Init();

#ifdef LINUX
	if(g_bBindThreadsToCPU)
	{  
		// �̰߳�CPU
		BindThd2CPU(pthread_self(),g_n_cpucount-2);
	}
#endif
	
	//������ض�ʱ
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

	//�Ƿ񵼳��������ļ�����
//	char* pDumpFlag=m_pConfig->getConfig("DumpAfterRedo");
//	if (!strcmp(pDumpFlag,"yes"))
//	{
//		m_pKernelTradingEngine->DumpMemDb();
//	}
	
	REPORT_EVENT(LOG_CRITICAL,"Redo","end redo��the data in memory database are dumped into the files!\n");
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
			///200150616 xuzh ���ǵ���������ѯ�����������е���ˮ֮ǰ��ʹ�ñ�ʶ������
			///������ˮ��˳��qdata�ϳ���ˮ->��������ѯ��ˮ->������������ˮ
			for (int i=0; i<100; i++)
			{	
				///��̽�Ƿ���Զ���ˮ
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
		default:              //���������źţ�����Ӧ�˳�
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
	signal(SIGABRT, SignHandler);    //��ʾ���˳�
	signal(SIGPIPE, SignHandler);    //����SIGPIPE
	signal(SIGINT, SignHandler);     //��ʾ���˳�
/*** SIR 00001 END ***/

	
	g_n_cpucount=sysconf(_SC_NPROCESSORS_CONF);	
	printf("this machine has %d cpus\n",g_n_cpucount);

	// ��ȡ��CPU�ı�־
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

	//if(g_bBindThreadsToCPU){ // �����߳��а󶨣�ʵ���ϣ��ǰ����е����̰߳���ͬһ�����ϡ�
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
	//�������������ı��̻�
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
		//���û�в�ѯ�������Ķ���,���߳����֮����Ϣ1���Ӽ��򿪶˿�
		nSleepTime = 1;
		recover = true;
	}

	CQTradeApp app(recover);
	app.Create();

	//�ȴ����������������Ȼ��--ǰ�ö˿ڴ�
	while(!app.b_FinishInit)
	{
		SLEEP_SECONDS(1);
	//	printf("sleep 1 \n");
	}

	SLEEP_SECONDS(nSleepTime);

	//���������Ҫ���ϵͳ״̬�Ƿ���ȷ��Լ״̬�Ƿ���ȷ
	if(app.m_pKernelTradingEngine->GetSystemStatus()!=SS_InstrumentTradingDayDown)
	{
		app.m_pKernelTradingEngine->ChangeSystemStatus(SS_InstrumentTradingDayDown);
		//����
		//����״̬�ı�֮����Ҫ���ܶ������������Ϣ1��֮���ٴ򿪶˿�
		//����������1�������ڴ����ݿ� 2����߱�֤�����
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
