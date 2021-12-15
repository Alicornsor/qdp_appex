// FrontEngine.cpp: implementation of the CFrontEngine class.
//
// 20070115 hwp ���Ӷ��������Ƶ��趨
// 20070704 hwp ��˽�����ķַ����Ϊ�����ļ��ͽ�����������
// 20070715 hwp ���������Ƶĸ�Ϊ������������п���
// 20070725 hwp �����ر�slog�ļ���BUG
// 20070807 hwp �������ÿͻ��˽ӿڰ汾��Χ�ķ���
// 20070828 hwp ������־�ļ���ͷ���
// 20071012 hwp Ϊ�Ự����UserType��Ϣ�����ṩ�����úͻ�ȡ�ķ���
//                 (Ϊ֧��FTD��ReqSubscribeTopic��
// 20080626 hwp NT-0041�Ի����Ͳ�ѯ������ʹ��Flow����ֻ������ţ������ڴ�ռ��
// 20080721 hwp NT-0045-��ϯλ���أ��������޶����SessionInfo�У����ṩ
//                 ���ûỰ�����޶�Ľӿڡ�
// 20080721 hwp NT-0047-����������¼������������ߵĴ��󣺶���ʱ���ۻỰ
//                 �Ƿ��������ߣ������׺��ķ���Logout����
// 20090512 hwp NT-0078:����˽��������������
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "FrontEngine.h"
#include "CachedFlow.h"
#include "CachedFileFlow.h"
#include "XtpPackageDesc.h"
#include "monitorIndex.h"
#include "CDate.h"

const int SESSION_CHECK_TIMER_ID	= 9;
const int SESSION_CHECK_INTERVAL	= 1000;
const int MAX_COMM_FLUX		= 50;	//ÿSESSION_CHECK_INTERVAL�����ͨѶ��

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFrontEngine::CFrontEngine(CReactor *pReactor, CFrontForwarder *pFrontForwarder,
						   const char *pszFlowPath,CSelectReactor* pConnReactor)
:CSessionFactory(pReactor, 500, pConnReactor)
{
	m_pFrontForwarder = pFrontForwarder;
	m_reqPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE, 1000);
	m_pPrivateFlow = new CCachedFlow(false, 10000000, 100000);
	m_pPublicFlow = new CCachedFlow(false, 100000, 100000);

	m_strFlowPathName = pszFlowPath;

	m_fpChannelLog = NULL;
//��Ϊû�����أ���ʱȡ���ö�ʱ����by wangwei,20130116
// 	SetTimer(SESSION_CHECK_TIMER_ID, SESSION_CHECK_INTERVAL);

	m_nMaxCommFlux = MAX_COMM_FLUX;
}

CFrontEngine::~CFrontEngine()
{
	ClearAllMap();
	delete m_pPrivateFlow;
	delete m_pPublicFlow;
	CloseChannelLogFile();
}

void CFrontEngine::ClearAllMap()
{
	CParticipantFlowMap::iterator pfitor = m_mapPrivateFlow.Begin();
	while (!pfitor.IsEnd())
	{
		delete (*pfitor);
		pfitor ++;
	}
	m_mapPrivateFlow.Clear();

	m_mapSessionInfo.Clear();
}

void CFrontEngine::OnTimer(int nIDEvent)
{
	if (nIDEvent == SESSION_CHECK_TIMER_ID)
	{
		CSessionMap::iterator itor = m_mapSession.Begin();
		while (!itor.IsEnd())
		{
			TFrontSessionInfo *pFind = m_mapSessionInfo.Find((*itor)->GetSessionID());
			if (pFind != NULL)
			{
				CheckSession(*itor, pFind);
			}
			itor++;
		}
	}
}

void CFrontEngine::CheckSession(CSession *pSession, TFrontSessionInfo *pSessionInfo)
{
	///���¿�ʼ��������
	pSessionInfo->nCommFlux -= pSessionInfo->nMaxCommFlux;
	if (pSessionInfo->nCommFlux < 0)
	{
		pSessionInfo->nCommFlux = 0;
	}
	///�����������涨�������ûỰ�Ķ�����
	pSession->SuspendRead(pSessionInfo->nCommFlux >= pSessionInfo->nMaxCommFlux);
}

CIndexPackageFlow * CFrontEngine::GetPrivateFlow(const CBrokerIDType &brokerID)
{
	CIndexPackageFlow *pFlow = NULL;
	CIndexPackageFlow **pFind = m_mapPrivateFlow.Find(brokerID);
	if (pFind == NULL)
	{
		pFlow = new CIndexPackageFlow();
		pFlow->AttachUnderFlow(m_pPrivateFlow);
		m_mapPrivateFlow.Insert(brokerID, pFlow);
	}
	else
	{
		pFlow = *pFind;
	}
	return pFlow;
}

void CFrontEngine::CalcFlux(CSession *pSession, const int nFlux)
{
	TFrontSessionInfo *pSessionInfo = m_mapSessionInfo.Find(pSession->GetSessionID());
	if (pSessionInfo != NULL)
	{
//		pSessionInfo->nCommFlux += nFlux;
		pSessionInfo->nCommFlux ++; //�������Ƹ�Ϊ����
		///�����������涨�������ûỰ�Ķ�����
		if (pSessionInfo->nCommFlux >= pSessionInfo->nMaxCommFlux)
		{
			pSession->SuspendRead(true);
		}
	}
}
 
void CFrontEngine::SendToPrivateFlow(const CBrokerIDType &brokerID, CPackage *pPackage)
{
	pPackage->MakePackage();
	CIndexPackageFlow *pFlow = GetPrivateFlow(brokerID);
	int nIndex = m_pPrivateFlow->Append(pPackage->Address(), pPackage->Length());
	pFlow->Append(nIndex);
}

void CFrontEngine::SendToPublicFlow(CPackage *pPackage)
{
	pPackage->MakePackage();
	CFlow *pFlow = GetPublicFlow();
	pFlow->Append(pPackage->Address(), pPackage->Length());
}

TFrontSessionInfo *CFrontEngine::GetSessionInfo(DWORD nSessionID)
{
	return m_mapSessionInfo.Find(nSessionID);
}

bool CFrontEngine::GetSessionOwner(DWORD nSessionID, CUserIDType &userID, 
							  CBrokerIDType &brokerID)
{
	TFrontSessionInfo *pSessionInfo = m_mapSessionInfo.Find(nSessionID);
	if (pSessionInfo == NULL)
	{
		return false;
	}
	userID = pSessionInfo->UserID;
	brokerID = pSessionInfo->BrokerID;
	return true;
}

void CFrontEngine::SetSessionOwner(DWORD nSessionID, const CUserIDType &userID, 
							  const CBrokerIDType &brokerID)
{
	TFrontSessionInfo *pFind = m_mapSessionInfo.Find(nSessionID);
	if (pFind == NULL)
	{
		//��Ӧ���֣������Ϣ�����ӽ������Ӧ�ô�����
		return;
	}
	pFind->bIsLogin = true;
	pFind->UserID =userID;
	pFind->BrokerID = brokerID;

	CSession *pSession = GetSession(nSessionID);
	assert(pSession != NULL);

//	pSession->OpenChannelLogFile(userID, 
//		CDate::LongToDate(m_pPrivateFlow->GetCommPhaseNo()));
}

/*	���ǰ�ûỰ������û���Ϣ������Ự�����Ǵ��ڣ������û���Ϣ����ˡ�
//	�Ự��״̬Ϊδ��¼��������������û����������ǳ�����
//	longqy 20130906
*/
void CFrontEngine::ClearSessionOwner(const DWORD nSessionID)
{
	TFrontSessionInfo *pFind = m_mapSessionInfo.Find(nSessionID);
	if (pFind == NULL)
	{
		//��Ӧ���֣������Ϣ�����ӽ������Ӧ�ô�����
		return;
	}
	pFind->bIsLogin = false;
	pFind->UserID.clear();
	pFind->BrokerID.clear();
}

bool CFrontEngine::IsSessionLogin(DWORD nSessionID)
{
	TFrontSessionInfo *pFind = m_mapSessionInfo.Find(nSessionID);
	if (pFind == NULL)
	{
		//û�ҵ�����Ự����Ϣ������false
		return false;
	}
	return pFind->bIsLogin;
}

///	���ûỰ�����ߵ��û�����
bool CFrontEngine::SetSessionOwnerType(DWORD nSessionID, const CUserTypeType &UserType)
{
	TFrontSessionInfo *pFind = m_mapSessionInfo.Find(nSessionID);
	if (pFind == NULL)
	{
		//û�ҵ�����Ự����Ϣ������false
		return false;
	}
	pFind->UserType = UserType;
	return true;
}

///	��������Ự��������������
bool CFrontEngine::SetSessionMaxCommFlux(DWORD nSessionID, int nMaxCommFlux)
{
	if (nMaxCommFlux <= 0)
	{
		return false;
	}
	TFrontSessionInfo *pFind = m_mapSessionInfo.Find(nSessionID);
	if (pFind == NULL)
	{
		//û�ҵ�����Ự����Ϣ������false
		return false;
	}
	pFind->nMaxCommFlux = nMaxCommFlux;
	return true;
}

CUserTypeType CFrontEngine::GetSessionOwnerType(DWORD nSessionID)
{
	TFrontSessionInfo *pFind = m_mapSessionInfo.Find(nSessionID);
/*
	if (pFind == NULL)
	{
		//û�ҵ�����Ự����Ϣ������UT_SingleTrader
		return UT_SingleTrader;
	}
*/
	return pFind->UserType;
}

/*	���Ự���ӽ�����ʱ�򣬴���ǰ�ûỰ��Ϣ����һ��ʼ��ʱ�򣬻Ự״̬��û�е�¼��
//	��������Ự����־�ļ���
*/
void CFrontEngine::OnSessionConnected(CSession *pSession)
{
	//�ȵ��û���ķ���
	CSessionFactory::OnSessionConnected(pSession);

	TFrontSessionInfo sinfo;
	memset(&sinfo, 0, sizeof(TFrontSessionInfo));
	sinfo.nSessionID = pSession->GetSessionID();
	sinfo.bIsLogin = false;
	sinfo.nConnectTime = m_pReactor->Time();
	sinfo.nCommFlux = 0;
	sinfo.nMaxCommFlux = m_nMaxCommFlux;
	m_mapSessionInfo.Insert(sinfo.nSessionID, sinfo);

//by wangwei,20130110
//	pSession->GetChannel()->SetLogFile(m_fpChannelLog);
	pSession->GetChannel()->SetLogFlow(m_pSlogFlow);

// 	REPORT_EVENT(LOG_INFO, "Session", "[%s] [0x%08x] connected",
// 		pSession->GetChannel()->GetRemoteName(), pSession->GetSessionID());
}

/*	���Ự�Ͽ���ʱ��ɾ��ǰ�ûỰ��Ϣ���󡣲���������ϵͳ�����ǳ�����
//	longqy 20130906
*/
void CFrontEngine::OnSessionDisconnected(CSession *pSession, int nReason)
{
	CUserLogoutField userLogoutField;
	if (GetSessionOwner(pSession->GetSessionID(),
		userLogoutField.UserID, userLogoutField.BrokerID))
	{
		NET_CONNECT_LOG2("GetSessionOwner:[%s][%s]\n",
			userLogoutField.BrokerID.getValue(),
			userLogoutField.UserID.getValue());
				
		//������ڸûỰ����Ϣ������ɾ��
		m_mapSessionInfo.Erase(pSession->GetSessionID());

		REPORT_EVENT(LOG_DEBUG, "Session", "Send TID_ReqUserLogout [0x%08x]", 
			pSession->GetSessionID());
		//�������淢���ý���Ա�ĵǳ�����
		//�����������޷���֪���Ѷ��ߣ��ý���Ա����Ҳ�޷���¼��		
		m_pFrontForwarder->PrepareForward(&m_reqPackage, TID_ReqUserLogout, 
			pSession->GetSessionID(), 0);
		
		XTP_ADD_FIELD(&m_reqPackage, &userLogoutField);

		m_pFrontForwarder->ForwardTransaction(&m_reqPackage);
	}

// 	REPORT_EVENT(LOG_INFO, "Session", "[%s] [%s] disconnected",
// 		pSession->GetChannel()->GetRemoteName(), userLogoutField.UserID.getValue());

//	pSession->CloseChannelLogFile();
	
	//�����û���ķ���
	CSessionFactory::OnSessionDisconnected(pSession, nReason);
}

/*	���ŵ���־�ļ����ļ��������� "/path/_00000000"
*/
bool CFrontEngine::OpenChannelLogFile(const char *pszPath)
{
	char szFullFilename[512];
	sprintf(szFullFilename, "%s_%s.slog",
		pszPath, "00000000");//CDate::LongToDate(m_pPrivateFlow->GetCommPhaseNo()));
	m_fpChannelLog = fopen(szFullFilename, "ab");
	if (m_fpChannelLog == NULL)
	{
		return false;
	}
	return true;
}

void CFrontEngine::CloseChannelLogFile()
{
	if (m_fpChannelLog != NULL)
	{
		CSessionMap::iterator itor = m_mapSession.Begin();
		for (; !itor.IsEnd(); itor++)
		{
			(*itor)->GetChannel()->SetLogFile(NULL);
		}
		fclose(m_fpChannelLog);
		m_fpChannelLog = NULL;
	}
}

void CFrontEngine::SetLogFlow(CFlow *fp)
{
	if (NULL != fp)
	{
		m_pSlogFlow =fp;
	}
}

int CFrontEngine::AppendToPrivateFlow(CPackage *pPackage)
{
	pPackage->MakePackage();
	return m_pPrivateFlow->Append(pPackage->Address(), pPackage->Length());
}

void CFrontEngine::SendToPrivateFlow(const CBrokerIDType &brokerID, int nIndex)
{
	CIndexPackageFlow *pFlow = GetPrivateFlow(brokerID);
	pFlow->Append(nIndex);
}

void CFrontEngine::SetInterfaceMinStr(const char *pszInterfaceMinStr)
{
	m_strInterfaceMin = pszInterfaceMinStr;
}

void CFrontEngine::SetInterfaceMaxStr(const char *pszInterfaceMaxStr)
{
	m_strInterfaceMax = pszInterfaceMaxStr;
}
