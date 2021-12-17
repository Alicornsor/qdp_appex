//
// qfixfront
// 
// 大事记：
// 20210806 用于从gts的qtrade接收排队机流水
// 
#ifdef WINDOWS
#pragma push_macro("_WINSOCKAPI_") //为了屏蔽winsock.h
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif
#include <winsock2.h>
#endif

#include "public.h"
//#include "BaseFunction.h"
#include "CachedFileFlow.h"
//#include "FileFlow.h"
#include "Config.h"
#include "CConfig.h"
#include "version.h"
#include "XtpClient.h"
#include "monitorIndex.h"
#include "CFilelogService.h"
#include "XtpPackageDesc.h"
#include "cryptAll.h"
#include "WsServer.h"

const char *INI_FILE_NAME = "xtpclient.ini";
const char* APP_NAME = "xtpclient";
//const DWORD TID_RspUserLogin = 0x00009003;

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

	//处理num=0的情况
	if (0 == num)
	{
		ss[0] = '0';
		ss[1] = '\0';
		return ss;
	}
	//处理负数
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

//打印XTPPackage内容
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

//获取qtrade的结果流
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
		//设置为不可发送
		m_bConnected = false;
		CSessionFactory::OnSessionDisconnected(pSession, nReason);
	}

	int HandlePackage(CXTPPackage *pXTPPackage, CTcpXtpSession *pSession)
	{
		//判断是否为登录Rsp的消息，需要对登录密码加密
		if (TID_RspUserLogin == pXTPPackage->GetTid())
		{
			CUserLoginField userLoginField;
			CRspInfoField   rspInfoField;
			memset(&userLoginField, 0x00, sizeof(CUserLoginField));
			memset(&rspInfoField, 0x00, sizeof(CRspInfoField));
			if (XTP_GET_SINGLE_FIELD(pXTPPackage, &userLoginField) <= 0)
			{
				REPORT_EVENT(LOG_CRITICAL, "HandlePackage", "Get CUserLoginField from package error.");
				return 0;
			}
			if (XTP_GET_SINGLE_FIELD(pXTPPackage, &rspInfoField) <= 0)
			{
				REPORT_EVENT(LOG_CRITICAL, "HandlePackage", "Get CRspInfoField from package error.");
				return 0;
			}
			//对密码进行加密
			printf("OldPasswd:%s\n", userLoginField.Password.getValue());
			char md5Password[33];
			MD5Hex(md5Password, userLoginField.UserID.getValue(), userLoginField.Password.getValue());
			userLoginField.Password = md5Password;
			printf("Md5Passwd:%s\n", userLoginField.Password.getValue());

			//重新初始化package
			CXTPPackage *pTempPackage = CXTPPackage::CreatePackage(1000);
			pTempPackage->PrepareResponse(pXTPPackage, TID_RspUserLogin);
			XTP_ADD_FIELD(pTempPackage, &userLoginField);
			XTP_ADD_FIELD(pTempPackage, &rspInfoField);
			pTempPackage->MakePackage();
			m_pSerialFlow->Append(pTempPackage->Address(), pTempPackage->Length());
			pTempPackage->Pop(XTPHLEN);

			//发送RspLogin
			if (NULL != m_pWsServer)
			{
				string strMsg = ConvertXtpToStr(pTempPackage);
				m_pWsServer->send_messages_to_all(strMsg); //新消息发送所有的连接
			}
			m_nsubcount++;
			return 0;
		}
		//否则直接写流水文件
		//这里直接写流水文件
		pXTPPackage->MakePackage();
		m_pSerialFlow->Append(pXTPPackage->Address(), pXTPPackage->Length());
		pXTPPackage->Pop(XTPHLEN);
		m_nsubcount++;

		//打印package内容
		//XTP_PACKAGE_DEBUG(pXTPPackage);
		//PrintXTPPackage(pXTPPackage);
		if (NULL != m_pWsServer)
		{
			string strMsg = ConvertXtpToStr(pXTPPackage);
			m_pWsServer->send_messages_to_all(strMsg); //新消息发送所有的连接
		}

		return 0;
	}

	void RegisterWsServer(CWsServer *pWsServer)
	{
		m_pWsServer = pWsServer;
	}

private:
	CXTPPackage m_LoginPackage;
	int m_nsubcount;
	CWsServer *m_pWsServer;
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
	default:              //出现其他信号，程序不应退出
		return;
	}
}
#endif
/*** SIR 00001 END ***/

int main(int argc, char *argv[])
{
#ifdef LINUX
	/*** SIR 00001 BEGIN ***/
	signal(SIGABRT, SignHandler);    //提示并退出
	signal(SIGPIPE, SignHandler);    //忽略SIGPIPE
	signal(SIGINT, SignHandler);     //提示并退出
	/*** SIR 00001 END ***/
#endif
	//获取配置信息
	CConfig *pConfig = new CConfig(INI_FILE_NAME);
	char *syslogFileName=pConfig->getConfig("SyslogPath");
	CMonitorIndex::init(CFilelogService::CreateInstance(argc,argv,syslogFileName),pConfig);
	showVersion(argc,argv);

	GetConfigString(INI_FILE_NAME, "FlowPath", g_szFlowPath, sizeof(g_szFlowPath));
	CCachedFileFlow      *pCompLogFlow = new CCachedFileFlow("CompLog", g_szFlowPath, true, 0x70000, 0x20000);
	new CIntPtrMonitorIndex("CompLogLen",pCompLogFlow->GetCountPtr(),20);
	new CPerIntPtrMonitorIndex("CompLog",pCompLogFlow->GetCountPtr(),10);

	//定义WsServer
	CWsServer *pWsServer = new CWsServer(pCompLogFlow);

	CSelectReactor     m_reactorPublish;
	CExXtpClient *pFrontClient = new CExXtpClient(&m_reactorPublish, pCompLogFlow);
	pFrontClient->RegisterWsServer(pWsServer);
	
	CMonitorIndexTimer    *m_pMonitorIndexTimer = new CMonitorIndexTimer(&m_reactorPublish);
	//注册于核心的通信地址
	pFrontClient->RegisterConnecter(pConfig->getConfig("xtpgate"));
	//启动服务
	pFrontClient->Init();
	//m_reactorPublish.Create();
	//启动websocket server
	pWsServer->run(9002);
	m_reactorPublish.Join();
	return 0;
}

