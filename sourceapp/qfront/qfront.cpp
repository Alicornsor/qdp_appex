// fgateway.cpp: 
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "BaseFunction.h"

#include "SelectReactor.h"
#include "EpollReactor.h"
#include "FrontTerminal.h"
#include "FtdEngine.h"
//#include "FrontStatusManager.h"
#include "CachedFileFlow.h"
#include "FileFlow.h"
#include "Config.h"
#include "FlowSubscriber.h"
#include "monitorIndex.h"
#include "CConfig.h"
#include "version.h"
#include "SslNetworkFactory.h"
#include "CFilelogService.h"

#include "PipeEventHandler.h"
#include "SynFlowSubscriber.h"

#include "GatewayClient.h"

const int QUERY_SERVER_ID = 1;
const DWORD FRONT_APP_ID_BASE = 0x1700;
const char *INI_FILE_NAME = "qfront.ini";
const char *APP_NAME = "qfront";

#define MAX_FRONT_REACTOR	10
//����ģʽ
#define NORMAL_START_MODE   0
#define RESTORE_START_MODE  1

//����ģʽ
int g_StartMode=NORMAL_START_MODE;

//CSemaphore g_semThread;
char g_szFlowPath[300];

bool LatencyOut=false;
long LatencyRecvDown=0;
long LatencySendUp=0;
long LatencyRecvUp=0;
long LatencySendDown=0;

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
		SetTimer(0,1000);
	}
protected:
	virtual void OnTimer(int nIDEvent)
	{
		CMonitorIndex::handleOne();
	}
};
//////////////////////////////////////////////////////////////////////////
//CFrontWriteLogReactor
//20130827 huwp �޸�дslog��������
//////////////////////////////////////////////////////////////////////////
class CFrontWriteLogReactor : public CThread
{
public:
	CFrontWriteLogReactor(DWORD dwFrontID,CCachedFlow *pSlogResult)
	{
		m_pSlogResult = pSlogResult;
		char szBuffer[300];
		strcpy(szBuffer, g_szFlowPath);
		sprintf(szBuffer+strlen(szBuffer), "%d", dwFrontID);
		strcat(szBuffer, "ftd");
		m_strFlowPathName = szBuffer;
		OpenChannelLogFile(szBuffer);
		m_reader.AttachFlow(m_pSlogResult,0);
	}
	virtual void Run();
	virtual int GetHandleCount();
	bool OpenChannelLogFile(const char *pszPath);
	int *GetCountPtr(void);
private:
	CCachedFlow *m_pSlogResult;
	FILE *m_fpChannelLog;
	CFlowReader m_reader;
	string m_strFlowPathName;
	int m_nCount;					/**��cache�ﻹû��д���ļ��ĳ��� */
};
bool CFrontWriteLogReactor::OpenChannelLogFile(const char *pszPath)
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
		//������Ҫ����Slog��
		if(m_reader.GetCommPhaseNo() != m_pSlogResult->GetCommPhaseNo())
		{
			fclose(m_fpChannelLog);
			OpenChannelLogFile(m_strFlowPathName.c_str());			
		}
		iLen = m_reader.GetNext(sBuff, nDataLen);
		if(iLen<= 0)
		{
			SLEEP(1000);
			continue;
		}
		if(NULL != m_fpChannelLog)
		{
			fwrite(sBuff, 1,iLen,m_fpChannelLog);
			fflush(m_fpChannelLog);
		}	
		m_nCount = m_pSlogResult->GetCount() - m_reader.GetId();
	}
}
int *CFrontWriteLogReactor::GetCountPtr(void)
{
	return &m_nCount;	
}

#ifdef LINUX
class CFrontReactor : public CEpollReactor, public CPackageHandleCounter
#else
class CFrontReactor : public CSelectReactor, public CPackageHandleCounter
#endif
{
public:
	/**���캯��
	*/
	CFrontReactor()
	{
		m_pubPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
		m_pConfig =NULL;
		m_pClientApi = NULL;
		m_pFrontTerminal = NULL;
		m_pFrontForwarder = NULL;
		m_pFrontClient = NULL;
		m_pFtdEngine = NULL;
		//20130827 huwp �޸�дslog��������		
		m_pSlogResult = NULL;
		m_nHandleCount = 0;
		
		//�ɸ��߳̽�����־���
		m_pMonitorIndexTimer = new CMonitorIndexTimer(this);
	}

	/**��ʼ��ʵ��
	* @reutrn true ��ʼ���ɹ�  false ��ʼ��ʧ��
	* @remark ��ʼ��ͨѶ�ӿڡ������������Ŷӷ����
	*/
	virtual bool InitInstance()
	{
		char szBuffer[300];
		GetConfigString(INI_FILE_NAME, "ConfigPath",szBuffer, sizeof(szBuffer));
		GetConfigString(INI_FILE_NAME, "FlowPath", g_szFlowPath, sizeof(g_szFlowPath));
		m_pConfig = new CConfig(INI_FILE_NAME);

		if (!strcmp(m_pConfig->getConfig("LatencyOut"),"yes"))
		{
			LatencyOut = true;
		}

		m_dwFrontID = GetConfigInt(INI_FILE_NAME,"FrontID");

		int runMode = GetConfigInt(INI_FILE_NAME,"RunMode"); 
		if(runMode==1)
		{
			m_pTradeResult = new CCachedFlow(false, 2000000, 0x200000);
		}
		else
		{
			m_pTradeResult = new CCachedFileFlow("traderesult", g_szFlowPath, true, 0x70000, 0x20000);
		}
		//��ؽ������������־
// 		new CPerIntPtrMonitorIndex("traderesult",((CCachedFileFlow *)m_pTradeResult)->GetCountPtr(),1);
// 		new CIntPtrMonitorIndex("traderesultdealed",m_reader.GetIdPtr(),1);

		//�յ����׽����ˮ֮��֪ͨ���̴���
		CPipeEventHandler *pPipeHandler=new CPipeEventHandler(this);
		m_pTradeResult->AttachObserver(pPipeHandler);

		m_pFrontClient = new CGateWayClient(m_pTradeResult,&m_reactorPublish,m_dwFrontID);
		//��ѯ
		m_pClientApi = CFibClientApi::CreateClientApi(this, m_dwFrontID);
		char* pQquery=m_pConfig->getConfig("qquery");
		m_pFrontTerminal = new CFrontTerminal();
		m_pClientApi->RegisterServer(QUERY_SERVER_ID, pQquery, m_pFrontTerminal);
		m_pFrontForwarder = new CFrontForwarder(m_dwFrontID,m_pFrontClient,QUERY_SERVER_ID,m_pClientApi);

		//ǰ��
		m_pSlogResult =new CCachedFlow(false, 2000000, 0x100000);
		m_pFtdEngine = new CFtdEngine(this, m_pFrontForwarder, g_szFlowPath,m_pSlogResult);//����ͻ���
		m_pFrontTerminal->RegisterCallback(m_pFtdEngine);

		Redo();

		m_pFtdEngine->RegisterListener(m_pConfig->getConfig("qgateway"));//���������ַ+�˿�
		m_pFtdEngine->EnableListener(true);

		m_pFrontClient->RegisterConnecter(m_pConfig->getConfig("gateufd"));

		m_pFtdEngine->Start();
		m_pFrontClient->Start();
		m_pClientApi->Start();
		
		m_reactorPublish.Create();

		//20130827 huwp �޸�дslog�������� ����дchannel��־���߳�	
		m_pFrontWriteLogReactor = new CFrontWriteLogReactor(m_dwFrontID,m_pSlogResult);
		m_pFrontWriteLogReactor->Create();
		return true;
	}

	/**����ʵ��
	* @remark ����ͨѶ�ӿڡ������������Ŷӷ����
	*/
	virtual void ExitInstance()
	{
		m_pClientApi->Release();
		delete m_pFrontTerminal;
		delete m_pFtdEngine;
		delete m_pFrontClient;
		delete m_pFrontForwarder;
		delete m_pTradeResult;
		delete m_pSlogResult;
	}

	void Redo()
	{
		m_reader.AttachFlow(m_pTradeResult, 0);
		for(;;)
		{
			m_pubPackage.Allocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN);
			if(!m_reader.GetNext(&m_pubPackage))
				break;
			m_pFrontTerminal->HandleMessage(&m_pubPackage);
		}
	}

	virtual bool HandleOtherTask()
	{
		for (int i=0; i<100; i++)
		{
			m_pubPackage.Allocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN);
			if(!m_reader.GetNext(&m_pubPackage))
			{
				return CReactor::HandleOtherTask();
			}
			m_pFrontTerminal->HandleMessage(&m_pubPackage);
		}
		//20130827 huwp �޸�дslog��������
		//20141212 xuzh ȥ��popfront����ֹ�����ʱ��ë�̷��������п��ܻ�����bug
		//int nHandleCount = m_pFrontWriteLogReactor->GetHandleCount();
		//while (m_nHandleCount < nHandleCount)
		//{
		//	m_pSlogResult->PopFront();
		//	m_nHandleCount++;
		//}	
		return true;
	}
	
	virtual int GetHandleCount()
	{
		return m_reader.GetId();
	}

private:

	///ǰ�ñ��
	DWORD m_dwFrontID;	
	//��ѯʹ��
	CFibClientApi *m_pClientApi;
	CFrontTerminal *m_pFrontTerminal;
	CFrontForwarder *m_pFrontForwarder;
	CGateWayClient *m_pFrontClient;

	CFtdEngine *m_pFtdEngine;

//	CFrontStatusManager *m_pFrontStatusManager;
	CCachedFlow *m_pTradeResult;

	CSelectReactor m_reactorPublish;
	CXTPPackage m_pubPackage;
	CFlowReader m_reader;

	CMonitorIndexTimer *m_pMonitorIndexTimer;
	
	//20130827 huwp �޸�дslog��������
	CFrontWriteLogReactor *m_pFrontWriteLogReactor;
	CCachedFlow		*m_pSlogResult;
	int m_nHandleCount;

	CConfig *m_pConfig;
};

// 2006.10.11	huwp	���Ӷ�SSL֧�� 
class CFrontCertCallback : public CSslCertificateCallback
{
public:
	CFrontCertCallback()
		:m_config(INI_FILE_NAME)
	{
	}
	virtual bool GetVerifyMode()
	{
		return (strcmp(m_config.getConfig("SSLVerifyMode"), "1") == 0);
	}
	virtual char *GetCertFileName()
	{
		return m_config.getConfig("SSLCertFileName");
	}
	virtual char *GetKeyFileName()
	{
		return m_config.getConfig("SSLKeyFileName");
	}
	virtual char *GetCaFileName()
	{
		return m_config.getConfig("SSLCaFileName");
	}
	virtual char *GetKeyFilePassword()
	{
		return m_config.getConfig("SSLKeyFilePassword");
	}
private:
	CConfig m_config;
};

void InitSSL(CConfig *pConfig)
{
	if (strcmp(pConfig->getConfig("UseSSL"), "1") != 0)
	{
		return ;
	}
	CFrontCertCallback *pFrontCertCallback = new CFrontCertCallback;
	CSslNetworkFactory::m_instance.RegisterCertificateCallback(pFrontCertCallback);
}

int main(int argc, char *argv[])
{
#ifdef UNIX
	signal(SIGABRT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, SIG_IGN);
#endif

	//******//
	//	huwp��20060929����Syslog���ļ����ƴ������ļ��д���
	//******//

	//��ȡ������Ϣ
	CConfig *pConfig = new CConfig(INI_FILE_NAME);	

	char *syslogFileName=pConfig->getConfig("SyslogPath");
	CMonitorIndex::init(CFilelogService::CreateInstance(argc,argv,syslogFileName),pConfig);
	showVersion(argc,argv);
	
	
	// 2006.10.11	huwp	���Ӷ�SSL֧�� 
	InitSSL(pConfig);

	delete pConfig;

	CFrontReactor *pFrontReactor;
	pFrontReactor = new CFrontReactor();
	pFrontReactor->Create();
	pFrontReactor->Join();
	return 0;
}

