#include "GatewayClient.h"
//#include "CDate.h"
#include "XtpPackageDesc.h"
#include "CachedFlow.h"


//同时只有一个会话存在
CGateWayClient::CGateWayClient(CFlow *pSubFlow,CSelectReactor *pReactor,DWORD nFrontID,int subcount):CSessionFactory(pReactor,1)
{
	m_pSubFlow = pSubFlow;
	m_Package.ConstructAllocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN, 1000);
	if(subcount<0)
	{
		m_nsubcount = pSubFlow->GetCount();
	}
	else
	{
		m_nsubcount = subcount;
	}
	m_bConnected =false;
	m_nFrontID = nFrontID;
}

CGateWayClient::~CGateWayClient()
{
}

void CGateWayClient::RegisterReportServer(const char *pszServerAddress)
{
	RegisterConnecter(pszServerAddress);
	REPORT_EVENT(LOG_DEBUG, "Fgateway", "Connect Server %s", pszServerAddress);
}

void CGateWayClient::Init()
{
	m_pReactor->Create();
	Start();
}

//将主动断开服务器连接，如果要恢复连接需要执行StartConnect()
void CGateWayClient::StopConnect()
{
	PostEvent(USER_CHANNEL_DISCONNECTED_ALL, 0, NULL);
}

//开始连接服务器，执行init()后，该方法自动被执行
void CGateWayClient::StartConnect()
{
	EnableConnecter(true);
}


CSession *CGateWayClient::CreateSession(CChannel *pChannel, DWORD dwMark)
{
	CTcpXtpSession *pSession = new CTcpXtpSession(m_pReactor, pChannel,this);
	return pSession;
}

void CGateWayClient::OnSessionConnected(CSession *pSession)
{
	//自动触发登录
	m_pSession = (CTcpXtpSession *)pSession;
	m_bConnected = true;
	InnerLogin();
	CSessionFactory::OnSessionConnected(pSession);
}
void CGateWayClient::OnSessionDisconnected(CSession *pSession, int nReason)
{
	m_bConnected = false;
	m_pSession = NULL;
}

void CGateWayClient::InnerLogin()
{
 	CInnerLoginField field;
	field.SequenceNo=m_nsubcount;
 
 	m_Package.PreparePublish(TID_InnerLogin);
	m_Package.SetFrontID(m_nFrontID);	
 	m_Package.AddField(&CInnerLoginField::m_Describe,&field);
	SendReportPackage(&m_Package);
}

int CGateWayClient::HandlePackage(CXTPPackage *pXTPPackage, CTcpXtpSession *pSession)
{
	DWORD tid=pXTPPackage->GetTid();
	if(tid == TID_NtfCommPhaseChange)
	{
		CCommPhaseField field;
		XTP_GET_SINGLE_FIELD(pXTPPackage,&field);
		m_pSubFlow->SetCommPhaseNo(field.CommPhaseNo);
	}
	pXTPPackage->MakePackage();
	m_pSubFlow->Append(pXTPPackage->Address(),pXTPPackage->Length());
	pXTPPackage->Pop(XTPHLEN);
	m_nsubcount++;
	return 0;
}

int CGateWayClient::SendReportPackage(CXTPPackage *pXTPPackage)
{
	//如果多线程调用发送，需要加锁
	if(!m_bConnected)
	{
		return -1;
	}
	if(m_pSession == NULL)
	{
		return 0;
	}
//	printf("发送包%0x\n", pXTPPackage->GetTid());
//	pXTPPackage->SetFrontID(m_nFrontID);
//	pXTPPackage->MakePackage();
	return m_pSession->SendReportPackage(pXTPPackage);
}


int CGateWayClient::HandleEvent(int nEventID, DWORD dwParam, void *pParam)
{
	if (nEventID == USER_CHANNEL_DISCONNECTED_ALL) 
	{
		CSessionFactory::DisconnectAll(100);
		CSessionFactory::EnableConnecter(false);
	}
	else
		CSessionFactory::HandleEvent(nEventID, dwParam, pParam);
	return 0;
}


