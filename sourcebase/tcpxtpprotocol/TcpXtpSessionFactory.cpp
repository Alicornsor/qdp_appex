#include "TcpXtpSessionFactory.h"
//#include "CDate.h"
#include "XtpPackageDesc.h"
#include "CachedFlow.h"


//ͬʱֻ��һ���Ự����
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

//�������Ͽ����������ӣ����Ҫ�ָ�������Ҫִ��StartConnect()
void CTcpXtpSessionFactory::StopConnect()
{
	PostEvent(USER_CHANNEL_DISCONNECTED_ALL, 0, NULL);
}

//��ʼ���ӷ�������ִ��init()�󣬸÷����Զ���ִ��
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
	//�Զ�������¼
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


