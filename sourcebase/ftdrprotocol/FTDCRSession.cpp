// KernelFront.cpp: implementation of the CKernelRFront class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "FTDCRSession.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define WRITE_TIMEOUT_DEFAULT		60
#define READ_TIMEOUT_DEFAULT		120
#define WARNING_TIMEOUT_DEFAULT		80

#define EXXMP_HEARTBEAT_TIMER_ID		1
#define EXXMP_WRITE_HEARTBEAT_TIMER_ID		2

#define FTD_REQ_QUERY(XtpTid, FtdFieldType, XtpFieldType, CopyField)			\
	{																			\
		m_reqPackage.PreparePublish(XtpTid);									\
		m_reqPackage.SetFrontID(m_dwFrontID);									\
		m_reqPackage.SetSessionID(pSession->GetSessionID());					\
		m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());				\
		FtdFieldType ftdField;													\
		FTDC_GET_SINGLE_FIELD(pFTDCPackage, &ftdField);							\
		XtpFieldType xtpField;													\
		memset(&xtpField, 0, sizeof(xtpField));									\
		CopyField																\
		XTP_ADD_FIELD(&m_reqPackage, &xtpField);								\
		m_reqPackage.GetXTPHeader()->Type = XTP_REQUEST;						\
		m_ClientApi->Request(m_nQueryServerID, &m_reqPackage);					\
	}

////////////////////////////////////////////////////////////////////////////////////////
//CExXMPProtocol
CExXMPProtocol::CExXMPProtocol(CReactor *pReactor, int type)
:CProtocol(pReactor, XMPHLEN+XMPEXTHLEN+XMP_EXTHEAD_MAX_SIZE,
		   new CXMPPackage(), new CXMPPackage())
{
	m_LastReadTime = pReactor->Time();	
	m_bHeartEnable = false;
	m_Type = type;
	
	m_dwWriteTimeout = WRITE_TIMEOUT_DEFAULT;
	m_dwReadTimeout = READ_TIMEOUT_DEFAULT;

	if (m_Type == XMP_READ)
	{
		SetTimer(EXXMP_HEARTBEAT_TIMER_ID, 1000);
	}
}

CExXMPProtocol::~CExXMPProtocol()
{

}

void CExXMPProtocol::EnableHeartbeat(bool bEnable)
{
	if (m_bHeartEnable == bEnable)
	{
		return ;
	}

	if (m_Type == XMP_WRITE)
	{
		if (bEnable)
		{
			m_LastWriteTime = m_pReactor->Time();
			SetTimer(EXXMP_WRITE_HEARTBEAT_TIMER_ID, 1000);
		}
		else
		{
			KillTimer(EXXMP_WRITE_HEARTBEAT_TIMER_ID);
		}
		m_bHeartEnable = bEnable;
	}
}

void CExXMPProtocol::OnTimer(int nIDEvent)
{
	if(m_Type == XMP_READ && nIDEvent == EXXMP_HEARTBEAT_TIMER_ID)
	{
		if(m_pReactor->Time()-m_LastReadTime > m_dwReadTimeout)
		{
			//心跳读超时，通知下层协议
			REPORT_EVENT(LOG_CRITICAL,"Heartbeat Receive Timeout", "ReadTimeout=%lu CurrentTime=%lu LastTime=%lu\n",m_dwReadTimeout,m_pReactor->Time(),m_LastReadTime);	
			NotifyError(MSG_XMPERR_RECVHEARTBEAT, 0, this);
			return ;
		}
	}
	else if (m_Type == XMP_WRITE && nIDEvent == EXXMP_WRITE_HEARTBEAT_TIMER_ID)
	{
		if(m_pReactor->Time()-m_LastWriteTime >= m_dwWriteTimeout)
		{
			NET_CONNECT_LOG1("Send Heartbeat %d\n", m_pReactor->Time());			
			//心跳读超时，发送心跳包
			if(SendHeartbeat()<0)
			{
				NotifyError(MSG_XMPERR_SENDHEARTBEAT, 0, this);
				return ;
			}
		}		
	}
}

void CExXMPProtocol::SetHeartbeatTimeout(DWORD dwReadTimeout)
{
	if (m_dwReadTimeout != dwReadTimeout)
	{
		m_dwReadTimeout = dwReadTimeout;
		if (m_dwReadTimeout < 4)
		{
			m_dwReadTimeout = 4;
		}
		m_dwWriteTimeout = (m_dwReadTimeout-1)/3;
		SendWriteTimeout(m_dwWriteTimeout);
	}
}

void CExXMPProtocol::SetWriteTimeout(CXMPPackage *pPackage)
{
	if (pPackage->GetExtTagLen() != sizeof(DWORD))
	{
		return;
	}
	memcpy(&m_dwWriteTimeout, pPackage->GetExtData(), sizeof(DWORD ));
	CHANGE_ENDIAN(m_dwWriteTimeout);
	SetHeartbeatTimeout(m_dwWriteTimeout*3+1+3);
}


int CExXMPProtocol::Pop(CPackage *pPackage)
{
	m_LastReadTime = m_pReactor->Time();

	//检查是不是心跳
	CXMPPackage *pXMPPackage = (CXMPPackage *)pPackage;
	if(pXMPPackage->GetActiveID() == XMPTypeNone&& 
		pXMPPackage->GetExtTag() == XMPTagHeartbeatTimeOut)
	{
		SetWriteTimeout(pXMPPackage);
		return 0;
	}
	return CProtocol::Pop(pPackage);
}

int CExXMPProtocol::Push(CPackage *pPackage, CProtocol *pUpper)
{
	((CXMPPackage *)m_pSendPackage)->GetXMPHeader()->Type = (BYTE)pUpper->GetActiveID();

	//设置最新发送数据包的时间
	m_LastWriteTime = m_pReactor->Time();
	
	return CProtocol::Push(pPackage, pUpper);
}

int CExXMPProtocol::OnRecvErrorPackage(CPackage *pPackage)
{
	NotifyError(MSG_XMPERR_BADPACKAGE, 0, this);
	return 0;
}

int CExXMPProtocol::SendWriteTimeout(DWORD dwWriteTimeout)
{
	int len = GetHdrReserveLen();
	CXMPPackage pkgHeartbeatTimeout;
	pkgHeartbeatTimeout.ConstructAllocate(sizeof(dwWriteTimeout), len);
	
	CHANGE_ENDIAN(dwWriteTimeout);
	
	pkgHeartbeatTimeout.SetExtHeader(XMPTagHeartbeatTimeOut, 
		sizeof(dwWriteTimeout), (BYTE *)&dwWriteTimeout);
	
	//设置最新发送数据包的时间
	m_LastWriteTime = m_pReactor->Time();
	
	int ret = Send(&pkgHeartbeatTimeout);
	
	return ret;
}

int CExXMPProtocol::SendHeartbeat()
{
	int len = GetHdrReserveLen();
	CXMPPackage HeartbeatPackage;
	HeartbeatPackage.ConstructAllocate(0, len);
	
	HeartbeatPackage.SetExtHeader(XMPTagKeepAlive, 0, NULL);
	
	//设置最新发送数据包的时间
	m_LastWriteTime = m_pReactor->Time();
	
	int ret = Send(&HeartbeatPackage);
	
	return ret;
}

DWORD CExXMPProtocol::GetTimeout()
{
	return m_dwReadTimeout;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//CExXMPSession
CExXMPSession::CExXMPSession(CReactor *pReactor, CChannel *pChannel, int type)
:CSession(pReactor, pChannel, XMP_PACKAGE_MAX_SIZE+XMPHLEN+XMPEXTHLEN+256)
{
	m_pExXMPProtocol = new CExXMPProtocol(m_pReactor,type);
	m_pExXMPProtocol->AttachLower(m_pChannelProtocol, 0);
	m_pExXMPProtocol->RegisterErrorHandler(this);
}

CExXMPSession::~CExXMPSession()
{
	delete m_pExXMPProtocol;
}

void CExXMPSession::SetHeartbeatTimeout(DWORD dwReadTimeout)
{
	m_pExXMPProtocol->SetHeartbeatTimeout(dwReadTimeout);
}

void CExXMPSession::EnableHeartbeat(bool bEnable)
{
	m_pExXMPProtocol->EnableHeartbeat(bEnable);
}

DWORD CExXMPSession::GetTimeout()
{
	return m_pExXMPProtocol->GetTimeout();
}

//////////////////////////////////////////////////////////////////////
// CFTDCRSession

const DWORD EXXMPTypeFTDC = 0x01;

CFTDCRSession::CFTDCRSession(CReactor *pReactor,CChannel *pChannel, int type)
:CExXMPSession(pReactor, pChannel,type)
{
	m_pCRPProtocol = new CCompressProtocol(m_pReactor);
	m_pCRPProtocol->AttachLower(m_pExXMPProtocol, XMPTypeCompressed);
	m_pFTDCProtocol = new CFTDCProtocol(m_pReactor);
	m_pFTDCProtocol->AttachLower(m_pCRPProtocol, EXXMPTypeFTDC);
	
	m_pFTDCProtocol->RegisterErrorHandler(this);
	m_pFTDCProtocol->RegisterUpperHandler(this);
	
	m_pPackageHandler = NULL;
	m_type = type;
}

CFTDCRSession::~CFTDCRSession()
{

}

int CFTDCRSession::HandleEvent(int nEventID, DWORD dwParam, void *pParam)
{
	switch(nEventID)
	{
	case MSG_XMPERR_RECVHEARTBEAT:
	case MSG_XMPERR_SENDHEARTBEAT:
	case MSG_XMPERR_BADPACKAGE:
	case MSG_FTDCERR_BADPACKAGE:
	case MSG_CHNLERR_READ:
	case MSG_CHNLERR_WRITE:
		{
// 			if (m_type == XMP_WRITE)
// 			{
// 				Disconnect(nEventID);
// 				return 0 ;
// 			}
			if (m_pSessionCallback != NULL)
			{
				m_pSessionCallback->OnSessionDisconnected(this, nEventID);
			}
		}

	}
	
	return 0;
}	

void CFTDCRSession::GetIds(int *pReadId, int *pWriteId)
{
	CSession::GetIds(pReadId, pWriteId);
	if (m_type == XMP_READ)
	{
		*pWriteId = 0;
	}
	else
	{
		m_pFTDCProtocol->PublishSend();
		CExXMPSession::GetIds(pReadId, pWriteId);
	}
}

void CFTDCRSession::RegisterPackageHandler(CFTDCRSessionCallback *pPackageHandler)
{
	m_pPackageHandler = pPackageHandler;
}

int CFTDCRSession::HandlePackage(CPackage *pPackage,CProtocol *pProtocol)
{
	if (pProtocol == m_pFTDCProtocol)
	{
		CFTDCPackage *pFTDCPacakge = (CFTDCPackage *)pPackage;
		if (m_pPackageHandler == NULL)
		{
			return 0;
		}
		return m_pPackageHandler->HandlePackage(pFTDCPacakge, this);
	}
	return 0;
}


CFTDCPackage *CFTDCRSession::CreatePackage()
{
	CFTDCPackage *pPackage = new CFTDCPackage;
	pPackage->ConstructAllocate(FTDC_PACKAGE_MAX_SIZE, m_pFTDCProtocol->GetHdrReserveLen());
	return pPackage;
}

void CFTDCRSession::SendRequestPackage(CFTDCPackage *pPackage)
{
	m_pFTDCProtocol->Send(pPackage);
}

void CFTDCRSession::Publish(CReadOnlyFlow *pFlow, WORD wSequenceSeries, int nStartId)
{
	m_pFTDCProtocol->Publish(pFlow, wSequenceSeries, nStartId);
}

void CFTDCRSession::Disconnect(int nErrorCode)
{
	if (nErrorCode == 0)
	{
		//如果是主动断开，则尝试发送流中未发完的包
		m_pFTDCProtocol->PublishSend();
	}
	
	m_pFTDCProtocol->Clear();
	
	CSession::Disconnect(nErrorCode);
}

void CFTDCRSession::Closeconnect(int nErrorCode)
{
	m_pChannel->Disconnect();
	OnChannelLost(nErrorCode);
	//	PostEvent(MSG_DRSTROY_ME, 0, this);
	delete this;
}
void CFTDCRSession::ResetSession(DWORD nSessionID)
{
	m_nSessionID = nSessionID;
}
