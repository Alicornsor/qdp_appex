#include "XtpClient.h"
#include "XtpPackageDesc.h"
#include "CachedFlow.h"
#include "CachedFileFlow.h"


//同时只有一个会话存在
CXtpClient::CXtpClient(CSelectReactor *pReactor,CFlow *pSerailFlow,int subcount,CSelectReactor* pConnReactor):CSessionFactory(pReactor,1,pConnReactor)
{
	m_XtpPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN, 1000);
	m_pSession = NULL;
	m_pClientCallBack = NULL;
	m_bConnected = false;
	m_bFirstLogined=true;
	m_pSendFlow = NULL;
	m_pPipeEventHandler= new CPipeEventHandler(pReactor,110);
	m_pSerialFlow = pSerailFlow;
	if(subcount<0)
	{
		m_nsubcount = pSerailFlow->GetCount();
	}
	else
	{
		m_nsubcount = subcount;
	}
}
CXtpClient::~CXtpClient()
{
}
void CXtpClient::RegisterReportServer(const char *pszServerAddress)
{
	RegisterConnecter(pszServerAddress);
}

void CXtpClient::Init()
{
	m_pReactor->Create();
	Start();
}

//将主动断开服务器连接，如果要恢复连接需要执行StartConnect()
void CXtpClient::StopConnect()
{
	PostEvent(USER_CHANNEL_DISCONNECTED_ALL, 0, NULL);
}

//开始连接服务器，执行init()后，该方法自动被执行
void CXtpClient::StartConnect()
{
	EnableConnecter(true);
}

void CXtpClient::RegClientCallback(CXtpClientCallback *pClientCallback)
{
	m_pClientCallBack = pClientCallback;
}

CSession *CXtpClient::CreateSession(CChannel *pChannel, DWORD dwMark)
{
	CTcpXtpSession *pSession = new CTcpXtpSession(m_pReactor, pChannel,this);
	CreateSendFlow();
	pSession->PublishFlow(m_pSendFlow, 0);
	return pSession;
}

void CXtpClient::OnSessionConnected(CSession *pSession)
{
	m_bConnected = true;
	CSessionFactory::OnSessionConnected(pSession);
	m_pSession = (CTcpXtpSession *)pSession;
	m_pClientCallBack->OnSessionConnected(pSession);
}

void CXtpClient::OnSessionDisconnected(CSession *pSession, int nReason)
{
	//设置为不可发送
	m_bConnected = false;
	RemoveSendFlow();
	m_pClientCallBack->OnSessionDisconnected(pSession, nReason);
	CSessionFactory::OnSessionDisconnected(pSession, nReason);
}

int CXtpClient::SendReportPackage(CXTPPackage *pXTPPackage)
{
	if(!m_bConnected)
	{
		return -1;
	}
	if(m_pSession == NULL)
	{
		return 0;
	}
	return Append(pXTPPackage);
//	return m_pSession->SendReportPackage(pXTPPackage);
}

int CXtpClient::HandlePackage(CXTPPackage *pXTPPackage, CTcpXtpSession *pSession)
{
	DWORD tid=pXTPPackage->GetTid();
	if(tid == TID_InterLoginInfo)
	{
		CInterLoginInfoField field;
		XTP_GET_SINGLE_FIELD(pXTPPackage,&field);
		if (field.MaxLocalID>=0 && !m_bFirstLogined)
		{
			CQueryFinishNotifyField QueryFinish;
			QueryFinish.APIID=m_pClientCallBack->GetAPIID();
			QueryFinish.MaxOrderLocalID=field.MaxLocalID;
			QueryFinish.ApiLinkType=ALT_INNER;
			m_XtpPackage.PrepareRequest(TID_QueryBaseFinish);
			m_XtpPackage.SetAPIID(QueryFinish.APIID);
			XTP_ADD_FIELD(&m_XtpPackage,&QueryFinish);
			m_XtpPackage.MakePackage();
			m_pSerialFlow->Append(m_XtpPackage.Address(),m_XtpPackage.Length());
			m_XtpPackage.Pop(XTPHLEN);
		}
		m_bFirstLogined=false;

		///登录成功，通知上层
		if(m_pClientCallBack != NULL)
		{
			m_pClientCallBack->InterLogined(&field);
		}

		return 0;
	}
	else if(tid == TID_NtfCommPhaseChange)
	{
		CCommPhaseField field;
		XTP_GET_SINGLE_FIELD(pXTPPackage,&field);
		m_pSerialFlow->SetCommPhaseNo(field.CommPhaseNo);
	}
	pXTPPackage->MakePackage();
	m_pSerialFlow->Append(pXTPPackage->Address(),pXTPPackage->Length());
	pXTPPackage->Pop(XTPHLEN);
	m_nsubcount++;

	return 0;
}

int CXtpClient::HandleEvent(int nEventID, DWORD dwParam, void *pParam)
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

void CXtpClient::CreateSendFlow()
{
	RemoveSendFlow();
	m_pSendFlow = new CLockedCacheFlow(false, 10000, 10000);
	//m_pSendFlow = new CCachedFileFlow("inner_xtpclient", ".\\", true, 2000, 0x200000);
	
	//add by zbz
	((CLockedCacheFlow *)m_pSendFlow)->AttachObserver(m_pPipeEventHandler);
	//((CFtdcUserDialogFlow *)m_pDialogReqFlow)->AttachObserver(m_pPipeEventHandler);
}

void CXtpClient::RemoveSendFlow()
{
	if (NULL != m_pSendFlow)
	{
		delete m_pSendFlow;
		m_pSendFlow = NULL;
	}

}

int CXtpClient::Append(CXTPPackage *pXTPPackage)
{
	if (m_pSendFlow == NULL)
	{
		return -1;
	}
	
	pXTPPackage->MakePackage();
	int rtn = m_pSendFlow->Append(pXTPPackage->Address(), pXTPPackage->Length());
	if (rtn < 0)
	{
		return -1;
	}
	return 0;
}
