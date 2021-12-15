#include "TcpXtpSessionFactory.h"
//#include "CDate.h"
#include "XtpPackageDesc.h"
#include "CachedFlow.h"


//同时只有一个会话存在
CTcpXtpSessionFactory::CTcpXtpSessionFactory(CFlow *pSubFlow,CSelectReactor *pReactor,int subcount,CSelectReactor* pConnReactor):CSessionFactory(pReactor,1,pConnReactor)
{
	m_pSubFlow = pSubFlow;
	m_LoginPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN, 1000);
	if(subcount<0)
	{
		m_nsubcount = pSubFlow->GetCount();
	}
	else
	{
		m_nsubcount = subcount;
	}
}

CTcpXtpSessionFactory::~CTcpXtpSessionFactory()
{
}

void CTcpXtpSessionFactory::RegisterReportServer(const char *pszServerAddress)
{
	RegisterConnecter(pszServerAddress);
}

void  CTcpXtpSessionFactory::Init()
{
	m_pReactor->Create();
	Start();
}

//将主动断开服务器连接，如果要恢复连接需要执行StartConnect()
void CTcpXtpSessionFactory::StopConnect()
{
	PostEvent(USER_CHANNEL_DISCONNECTED_ALL, 0, NULL);
}

//开始连接服务器，执行init()后，该方法自动被执行
void CTcpXtpSessionFactory::StartConnect()
{
	EnableConnecter(true);
}


CSession *CTcpXtpSessionFactory::CreateSession(CChannel *pChannel, DWORD dwMark)
{
	CTcpXtpSession *pSession = new CTcpXtpSession(m_pReactor, pChannel,this);
	return pSession;
}

void CTcpXtpSessionFactory::OnSessionConnected(CSession *pSession)
{
	//自动触发登录
	InterLogin((CTcpXtpSession *)pSession);
	CSessionFactory::OnSessionConnected(pSession);
}

void CTcpXtpSessionFactory::OnSessionDisconnected(CSession *pSession, int nReason)
{
	CSessionFactory::OnSessionDisconnected(pSession, nReason);	
}

void CTcpXtpSessionFactory::InterLogin(CTcpXtpSession *pSession)
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

int CTcpXtpSessionFactory::HandlePackage(CXTPPackage *pXTPPackage, CTcpXtpSession *pSession)
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


int CTcpXtpSessionFactory::HandleEvent(int nEventID, DWORD dwParam, void *pParam)
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


