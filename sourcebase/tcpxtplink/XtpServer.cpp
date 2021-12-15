#include "public.h"
#include "XtpServer.h"
#include "XtpData.h"

CXtpServer::CXtpServer(CReactor *pReactor,CFlow *pSubFlow,CSelectReactor* pConnReactor):CSessionFactory(pReactor, 500,pConnReactor)
{
	m_pReactor = pReactor;
	m_nSubjectID = 0;
	m_pSubFlow = pSubFlow;
	m_XtpPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN, 1000);
}

CXtpServer::~CXtpServer()
{

}

void  CXtpServer::Init(char *tmpAddress)
{
	strcpy(m_tmpAddress,tmpAddress);
	m_pReactor->Create();
	Start();
}

void CXtpServer::SetSubjectID(DWORD nSubjectID)
{
	m_nSubjectID = nSubjectID;
}

CSession *CXtpServer::CreateSession(CChannel *pChannel, DWORD bIsListener)
{
	CTcpXtpSession *pSession =  new CTcpXtpSession(m_pReactor, pChannel,this,m_nSubjectID);
	return pSession;
}

void CXtpServer::OnSessionConnected(CSession *pSession)
{
	//先调用基类的方法
	CSessionFactory::OnSessionConnected(pSession);
}

void CXtpServer::OnSessionDisconnected(CSession *pSession, int nReason)
{
	//最后调用基类的方法
	CSessionFactory::OnSessionDisconnected(pSession, nReason);	
}

int CXtpServer::HandlePackage(CXTPPackage *pPackage, CTcpXtpSession *pSession)
{	
	switch(pPackage->GetTid()) 
	{
		case TID_ReqUserLogin:
		{
			OnReqClientLogin(pPackage, pSession);
			break;
		}
		default:
		//默认情况下，放入流文件即可，有后续engine处理
		{
			pPackage->MakePackage();
			m_pSubFlow->Append(pPackage->Address(),pPackage->Length());
			pPackage->Pop(XTPHLEN);
		}
		break;
	}
	return 0;
}

int CXtpServer::OnReqClientLogin(CXTPPackage *pPackage, CTcpXtpSession *pSession)
{
	CUserLoginField field;
	if (XTP_GET_SINGLE_FIELD(pPackage, &field) <= 0)
	{
		return 0;
	}
	REPORT_EVENT(LOG_CRITICAL, "Init", "receive TCP login request,SessionID:[%d]\n",pSession->GetSessionID());

	//返回下行流的地址
 	CInterLoginInfoField fieldLoginRsp;
	fieldLoginRsp.ServerAddr = m_tmpAddress;
	//返回最大本地报单号
	fieldLoginRsp.MaxLocalID = m_pServerCallBack->getnMaxLocalID(field.UserID.getValue());

 	m_XtpPackage.PreparePublish(TID_InterLoginInfo);
 	m_XtpPackage.AddField(&CInterLoginInfoField::m_Describe,&fieldLoginRsp);	
	pSession->SendReportPackage(&m_XtpPackage);
	return 0;
}

void CXtpServer::setXtpServerCallback(CXtpServerCallback *XtpServerCallback)
{
	m_pServerCallBack = XtpServerCallback;
}