//
// qfixfront
// 
// ���¼ǣ�
// 20210806 ���ڴ�gts��qtrade�����Ŷӻ���ˮ
// 
#include "public.h"
#include "BaseFunction.h"
#include "SelectReactor.h"
#include "CachedFileFlow.h"
#include "FileFlow.h"
#include "Config.h"
#include "CConfig.h"
#include "version.h"
#include "XtpClient.h"
#include "monitorIndex.h"
#include "CFilelogService.h"
#include "XtpPackageDesc.h"
#include "WsServer.h"

const char *INI_FILE_NAME = "xtpclient.ini";
const char* APP_NAME = "xtpclient";

char g_szFlowPath[300];

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

string ConvertIntToString(int num)
{
	int m = num;
	int i = 0, j = 0;
	char s[1024];
	char ss[1024];

	//����num=0�����
	if (0 == num)
	{
		ss[0] = '0';
		ss[1] = '\0';
		return ss;
	}
	//������
	if (num < 0)
	{
		m = 0 - m;
		j = 1;
		ss[0] = '-';
	}
	while (m > 0)
	{
		s[i++] = m % 10 + '0';
		m /= 10;
	}
	s[i] = '\0';

	i = i - 1;
	while (i >= 0)
	{
		ss[j++] = s[i--];
	}
	ss[j] = '\0';

	return ss;
}

//��ӡXTPPackage����
void PrintXTPPackage(CXTPPackage *pPackage)
{
	TXTPHeader *pHeader = pPackage->GetXTPHeader();
	REPORT_EVENT(LOG_CRITICAL, "PrintXTPPackage", "XTP PACKAGE HEADER: Type[0X%02X],Chain[0X%02X],ContentLength[%d],SubjectID[0X%08X],Tid[0X%08X],CommPhaseNo[%d],SequenceNo[%d],RequestID[%d],SessionID[%d],FrontID[%d]",
		pHeader->Type & 0xFF, pHeader->Chain & 0xFF, pHeader->ContentLength & 0xFFFF, pHeader->SubjectID, pHeader->Tid,
		pHeader->CommPhaseNo, pHeader->SequenceNo, pHeader->RequestID, pHeader->SessionID, pHeader->FrontID);
	
	REPORT_EVENT(LOG_CRITICAL, "PrintXTPPackage", "XTP PACKAGE CONTENT START");
	int nTid = pPackage->GetTid();
	TPackageDefine **pFind = g_XTPPackageDefineMap.Find(nTid);
	if (pFind == NULL)
	{
		REPORT_EVENT(LOG_CRITICAL, "PrintXTPPackage", "Can't find package define [%08x]", nTid);
		return;
	}
	char buf[10000];
	TPackageDefine *pPackageDefine = *pFind;
	CFieldTypeIterator itor = pPackage->GetFieldTypeIterator();
	while (!itor.IsEnd())
	{
		TFieldHeader fieldHeader;
		itor.RetrieveHeader(fieldHeader);
		TFieldUse *pFieldUse = pPackageDefine->fieldUse;
		for (int i = 0; i < pPackageDefine->fieldUseCount; i++)
		{
			if (pFieldUse->fid == fieldHeader.FieldID)
			{
				itor.Retrieve(pFieldUse->pFieldDescribe, buf);
				CFieldDescribe *pFieldDescribe = pFieldUse->pFieldDescribe;
				REPORT_EVENT(LOG_CRITICAL, "PrintXTPPackage", "FIELD [%s] START", pFieldDescribe->GetFieldName());
				for (int i = 0; i < pFieldDescribe->GetMemberCount(); i++)
				{
					string strFieldInfo = "\t[";
					TMemberDesc *pMemberDesc = pFieldDescribe->GetMemberDesc(i);
					strFieldInfo = strFieldInfo + string(pMemberDesc->szName) + "][" + ConvertIntToString((pMemberDesc->nType & 0xFF)) + "]";
					char *pMember = buf + pMemberDesc->nStructOffset;
					switch (pMemberDesc->nType)
					{
					case FT_WORD:
					{
						strFieldInfo = strFieldInfo + "[" + ConvertIntToString(*((WORD *)pMember) & 0xFFFF) + "]";
						break;
					}
					case FT_DWORD:
					{
						strFieldInfo = strFieldInfo + "[" + ConvertIntToString(*((DWORD *)pMember)) + "]";
						break;
					}
					case FT_BYTE:
					{
						if (pMemberDesc->nSize == 1)
						{
							strFieldInfo = strFieldInfo + "[" + ConvertIntToString(*pMember & 0xFF) + "]";
						}
						else
						{
							strFieldInfo = strFieldInfo + "[" + string(pMember) + "]";
						}
						break;
					}
					case FT_REAL4:
					{
						char strTemp[1024];
						memset(&strTemp, 0, sizeof(strTemp));
						sprintf(strTemp, "%f", *((REAL4 *)pMember));
						strFieldInfo = strFieldInfo + "[" + strTemp + "]";
						break;
					}
					case FT_REAL8:
					{
						double d;
						memcpy(&d, pMember, sizeof(REAL8));
						if (d == DOUBLE_NaN)
						{
							strFieldInfo += "[]";
						}
						else
						{
							char strTemp[1024];
							memset(&strTemp, 0, sizeof(strTemp));
							sprintf(strTemp, "%lf", d);
							strFieldInfo = strFieldInfo + "[" + strTemp + "]";
						}
						break;
					}
					default:
						break;
					}
					REPORT_EVENT(LOG_CRITICAL, "PrintXTPPackage", "%s", strFieldInfo.c_str());
				}
				REPORT_EVENT(LOG_CRITICAL, "PrintXTPPackage", "FIELD [%s] END", pFieldDescribe->GetFieldName());
				break;
			}
			pFieldUse++;
		}
		itor.Next();
	}
	REPORT_EVENT(LOG_CRITICAL, "PrintXTPPackage", "XTP PACKAGE CONTENT END");
}

//��ȡqtrade�Ľ����
class CExXtpClient : public CXtpClient
{
public:
	CExXtpClient(CSelectReactor *pReactor, CFlow *pSerialFlow) : CXtpClient(pReactor, pSerialFlow, 0)
	{
		m_LoginPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE + XTPHLEN, 1000);
		m_nsubcount = 0;
	}

	virtual CSession *CreateSession(CChannel *pChannel, DWORD dwMark)
	{
		CTcpXtpSession *pSession = new CTcpXtpSession(m_pReactor, pChannel, this);
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
		//����Ϊ���ɷ���
		m_bConnected = false;
		CSessionFactory::OnSessionDisconnected(pSession, nReason);
	}

	int HandlePackage(CXTPPackage *pXTPPackage, CTcpXtpSession *pSession)
	{
		//����ֱ��д��ˮ�ļ�
		pXTPPackage->MakePackage();
		m_pSerialFlow->Append(pXTPPackage->Address(), pXTPPackage->Length());
		pXTPPackage->Pop(XTPHLEN);
		m_nsubcount++;

		//��ӡpackage����
		//XTP_PACKAGE_DEBUG(pXTPPackage);
		PrintXTPPackage(pXTPPackage);

		return 0;
	}

private:
	CXTPPackage m_LoginPackage;
	int m_nsubcount;
};

const int ON_READFLOW_GET_ALL_MESSAGE_EVENT = 12001;
//������ȡ���ļ����߳� ɸѡ�����͵�websocket�ͻ���
class CReadFlowHandler : public CEventHandler
{
	CReadFlowHandler(CSelectReactor *pReactor, CWsServer *pWsServer, CFlow *pSerailFlow) : CEventHandler(pReactor)
	{
		m_pConnReactor = pReactor;
		m_pWsServer = pWsServer;
		m_pSerialFlow = pSerailFlow;
	}

	~CReadFlowHandler() {}

	//�����߳�
	void Start()
	{
		m_pConnReactor->Create();
	}

	//ֹͣ�߳�
	void Stop()
	{
		m_pConnReactor->Stop();
		m_pConnReactor->Join();
	}

	/**����һ���¼�
	* @param nEventID �¼�ID
	* @param dwParam ��һ������
	* @param pParam �ڶ�������
	* @return ������
	*/
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam)
	{
		switch (nEventID)
		{
		case ON_READFLOW_GET_ALL_MESSAGE_EVENT:
		{
			OnReadFlowProcess();
			break;
		}
		default:
			break;
		}
	}

	void OnReadFlowProcess()
	{
		m_reader.AttachFlow();
	}

private:
	CSelectReactor *m_pConnReactor;
	CWsServer *m_pWsServer;
	CFlowReader m_reader;
	CFlow *m_pSerialFlow; //�����
	CXTPPackage m_ReadPackage;
};


/*** SIR 00001 BEGIN ***/
#ifdef LINUX
static void SignHandler(int iSignNo)
{
	switch (iSignNo)
	{
	case SIGABRT:
		REPORT_EVENT(LOG_CRITICAL, "SignHandler", "Rcv system signal[%d](SIGABRT), app exit\n", iSignNo);
		exit(0);
	case SIGINT:
		REPORT_EVENT(LOG_CRITICAL, "SignHandler", "Rcv system signal[%d](SIGINT), app exit\n", iSignNo);
		exit(0);
	case SIGPIPE:
		REPORT_EVENT(LOG_CRITICAL, "SignHandler", "Rcv system signal[%d](SIGPIPE), app ignore this signal\n", iSignNo);
		return;
	default:              //���������źţ�����Ӧ�˳�
		return;
	}
}
#endif
/*** SIR 00001 END ***/

int main(int argc, char *argv[])
{
#ifdef LINUX
	/*** SIR 00001 BEGIN ***/
	signal(SIGABRT, SignHandler);    //��ʾ���˳�
	signal(SIGPIPE, SignHandler);    //����SIGPIPE
	signal(SIGINT, SignHandler);     //��ʾ���˳�
	/*** SIR 00001 END ***/
#endif
	//��ȡ������Ϣ
	CConfig *pConfig = new CConfig(INI_FILE_NAME);
	char *syslogFileName=pConfig->getConfig("SyslogPath");
	CMonitorIndex::init(CFilelogService::CreateInstance(argc,argv,syslogFileName),pConfig);
	showVersion(argc,argv);

	GetConfigString(INI_FILE_NAME, "FlowPath", g_szFlowPath, sizeof(g_szFlowPath));
	CCachedFileFlow      *pCompLogFlow = new CCachedFileFlow("CompLog", g_szFlowPath, true, 0x70000, 0x20000);
	new CIntPtrMonitorIndex("CompLogLen",pCompLogFlow->GetCountPtr(),20);
	new CPerIntPtrMonitorIndex("CompLog",pCompLogFlow->GetCountPtr(),10);

	CSelectReactor     m_reactorPublish;
	CExXtpClient *pFrontClient = new CExXtpClient(&m_reactorPublish, pCompLogFlow);
	
	CMonitorIndexTimer    *m_pMonitorIndexTimer = new CMonitorIndexTimer(&m_reactorPublish);
	//ע���ں��ĵ�ͨ�ŵ�ַ
	pFrontClient->RegisterConnecter(pConfig->getConfig("xtpgate"));
	//��������
	pFrontClient->Init();
	//m_reactorPublish.Create();
	m_reactorPublish.Join();
	return 0;
}

