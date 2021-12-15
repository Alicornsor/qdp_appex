// KernelFront.cpp: implementation of the CKernelFront class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "KernelFront.h"
#include "XtpPackageDesc.h"
#include "CConfig.h"
#include "ExchangeLinkTimer.h"

#ifdef LINUX
//这个头文件是为了用函数 sync() 20141031 longqy
#include <unistd.h>
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//extern  char *INI_FILE_NAME;
const int QUERY_SERVER_ID = 1;
extern const char *APP_NAME;
extern CConfig	*g_pConfig; // 全局的配置文件对象指针，给CKernelFrontReactor 对象用 longqy 2014-03-25。
extern CLinkReactor* g_pConnReactor;

CKernelFront::CKernelFront(CFlow* pTradeResult,CFlow* pSlogResult, int nLifeCycleID,CConfig * pConfig)
{
	m_pTradeResult=pTradeResult;
	m_pSlogResult=pSlogResult;
	m_nLifeCycleID=nLifeCycleID;
	m_pConfig = pConfig;
	m_pSeriesFlow =new CExCachedFlow(false, 0x7fffffff, 0x100000);
	m_reader.AttachFlow(m_pSeriesFlow,0);
	m_rspPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	m_ResultReader.AttachFlow(m_pTradeResult,0);

	m_pClientApiVect.clear();
	m_pFrontTerminal = NULL;

	m_pFrontForwarderVect.clear();
	m_pFtdEngineVect.clear();
	m_ReactorVect.clear();
	m_pFrontTimeSyncTimer = NULL;
	m_dwFrontID=1;//只有1个前置
	m_nLifeCycleID=nLifeCycleID;
	memset(m_shmAddr,0,sizeof(m_shmAddr));
	m_pFrontAddressVect.clear();
	Init();
}

CKernelFront::~CKernelFront()
{
	delete m_pFrontTerminal;	
	int ftd=m_pFtdEngineVect.size();
	int i=0;
	for(i=0; i<ftd; i++)
	{		
		CFtdEngine *pFtdEngine = m_pFtdEngineVect[i];
		delete pFtdEngine;
		CFrontForwarder *pFrontForwarder = m_pFrontForwarderVect[i];
		delete pFrontForwarder;
		
		CFibClientApi *pClientApi=m_pClientApiVect[i];
		pClientApi->Release();
	}
	for(i=0;i<m_ReactorVect.size();i++)
	{
		CSelectReactor *pReactor = (CSelectReactor *)m_ReactorVect[i];
		pReactor->Stop();
		delete pReactor;
	}		
}

bool CKernelFront::InitInstance()
{
		//	BindThd2CPU(pthread_self());
	return true;
}

bool CKernelFront::Init()
{
    // CConfig 没有办法从参数传进来 longqy 2014-03-25
	CConfig *m_pConfig = g_pConfig;	
	
	vector<char *> pClientApiAddressVect;
//	vector<char *> pFrontAddressVect;
	m_pFrontTerminal = new CFrontTerminal();//将tresult发回给客户	

	//qkernel的tcp
	char* pQquery=m_pConfig->getConfig("qquery");
	pClientApiAddressVect.push_back(pQquery);

	char* pUfd=m_pConfig->getConfig("ufd");
	m_pFrontAddressVect.push_back(pUfd);

	char* pShmaddr=m_pConfig->getConfig("shmaddr");
	if (strcmp(pShmaddr,""))
	{
		strncpy(m_shmAddr,pShmaddr,sizeof(m_shmAddr));
	}
	InitFront(m_pFrontAddressVect,pClientApiAddressVect,m_pConfig->getConfig("FlowPath"));
	
	pClientApiAddressVect.clear();
//	pFrontAddressVect.clear();
	//delete m_pConfig;
	
	return true;
}

void CKernelFront::InitFront(vector<char *> pFrontAddressVect,vector<char *> pQueryAddressVect,char *pFlowPath)
{
	if (pFrontAddressVect.size()==1)
	{
		//单前置模式
		m_bSingleFrontMode=true;
		
		//查询
		CFibClientApi *pClientApi = CFibClientApi::CreateClientApi(this, m_dwFrontID);
		for(int iClientApiCount=0;iClientApiCount <pQueryAddressVect.size(); iClientApiCount++)
			pClientApi->RegisterServer(QUERY_SERVER_ID, pQueryAddressVect[iClientApiCount], m_pFrontTerminal);
		m_pClientApiVect.push_back(pClientApi);
		
		//前置
		CFrontForwarder *pFrontForwarder = new CFrontForwarder(m_dwFrontID, m_pSeriesFlow,QUERY_SERVER_ID, pClientApi);
		m_pFrontForwarderVect.push_back(pFrontForwarder);
		CFtdEngine *pFtdEngine = new CFtdEngine(this, pFrontForwarder, pFlowPath,m_pSlogResult,g_pConnReactor);//处理客户包
		m_pFtdEngineVect.push_back(pFtdEngine);
		m_pFrontTerminal->RegisterCallback(pFtdEngine);
//		pFtdEngine->RegisterListener(pFrontAddressVect[0]);//对外监听地址+端口
		if (strlen(m_shmAddr) > 0)
		{
			pFtdEngine->RegisterListener(m_shmAddr);//打开共享内存监听			
			SetNoShmChannelFlag(false);
		}
		//初始化时并不打开端口
//		pFtdEngine->EnableListener(false);	
		pClientApi->Start();

	}
	else
	{
		m_bSingleFrontMode=false;
		
		for (int Frontid=0;Frontid<pFrontAddressVect.size();Frontid++)
		{
			CSelectReactor *pReactor = new CSelectReactor(
#ifdef LINUX 
				g_bBindThreadsToCPU
#endif
				);
			m_ReactorVect.push_back(pReactor);
			pReactor->Create();
			
			CFibClientApi *pClientApi = CFibClientApi::CreateClientApi(pReactor, Frontid);
			for(int iClientApiCount=0;iClientApiCount <pQueryAddressVect.size(); iClientApiCount++)
				pClientApi->RegisterServer(QUERY_SERVER_ID, pQueryAddressVect[iClientApiCount], m_pFrontTerminal);
			m_pClientApiVect.push_back(pClientApi);
			
			CFrontForwarder *pFrontForwarder = new CFrontForwarder(Frontid, m_pSeriesFlow,QUERY_SERVER_ID, pClientApi);
			m_pFrontForwarderVect.push_back(pFrontForwarder);
			
			CFtdEngine *pFtdEngine = new CFtdEngine(pReactor, pFrontForwarder, pFlowPath,m_pSlogResult,g_pConnReactor);//处理客户包
			m_pFtdEngineVect.push_back(pFtdEngine);
			
			m_pFrontTerminal->RegisterCallback(pFtdEngine);
//			pFtdEngine->RegisterListener(pFrontAddressVect[Frontid]);//对外监听地址+端口
			if (strlen(m_shmAddr) > 0)
			{
				pFtdEngine->RegisterListener(m_shmAddr);//打开共享内存监听
				SetNoShmChannelFlag(false);
			}
			//初始化时并不打开端口
			//pFtdEngine->EnableListener(false);		
			pClientApi->Start();
		}
	}
	
}

void CKernelFront::StartTimer()
{
	//多次登陆之后会产生一个timer，这样时钟报文越来越多，重大BUG-wangwei,20130814
	if(m_pFrontTimeSyncTimer==NULL)
	{
		m_pFrontTimeSyncTimer = new CFrontTimeSyncTimer(this,m_pSeriesFlow);
	}
}

//处理kernel产生的结果流
bool CKernelFront::HandleOtherTask()
{
	int i=0;
	for (i=0; i<100; i++)
	{
		m_rspPackage.Allocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN);
		if(!m_ResultReader.GetNext(&m_rspPackage))
		{
			break;
			//return CSelectReactor::HandleOtherTask();
		}		
		
		if(m_bSingleFrontMode)
		{
			m_pFrontTerminal->HandleMessage(&m_rspPackage);
		}
		else
		{
			m_pFrontTerminal->DispatcherMessage(&m_rspPackage);
		}

// 		if (m_bSingleFrontMode)
// 		{
// 			m_rspPackage.Allocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN);
// 			if(!m_ResultReader.GetNext(&m_rspPackage))
// 			{
// 				break;
// 				//return CSelectReactor::HandleOtherTask();
// 			}
// 			m_pFrontTerminal->HandleMessage(&m_rspPackage);
// 		}
// 		else
// 		{
// 			CXTPPackage *pRspPackage= new CXTPPackage();
// 			pRspPackage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
// 			pRspPackage->Allocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN);
// 			
// 			if(!m_ResultReader.GetNext(pRspPackage))
// 			{
// 				delete pRspPackage;
// 				break;
// 				//return CSelectReactor::HandleOtherTask();
// 			}	
// 			m_pFrontTerminal->DispatcherMessage(pRspPackage);
//		}
		
	}
	if (i>0)
	{
		return true;
	}
	return CSelectReactor::HandleOtherTask();
}

	
void CKernelFront::FrontStartWork()
{
	Create();
	//m_pFtdEngine->EnableListener(true);
	int ftd=m_pFtdEngineVect.size();
	for(int i=0; i<ftd; i++)
	{
		CFtdEngine *pFtdEngine = m_pFtdEngineVect[i];
		pFtdEngine->RegisterListener(m_pFrontAddressVect[i]);
		pFtdEngine->Start();
	}
	//定时器打开，发送时钟报文
	//StartTimer();
	REPORT_EVENT(LOG_CRITICAL,"FrontStartWork","front open port\n");
}


