// FrontEngine.cpp: implementation of the CFrontEngine class.
//
// 20070115 hwp 增加对流量控制的设定
// 20070704 hwp 将私有流的分发拆分为进入文件和进入索引两步
// 20070715 hwp 将流量控制的改为按请求个数进行控制
// 20070725 hwp 修正关闭slog文件的BUG
// 20070807 hwp 增加设置客户端接口版本范围的方法
// 20070828 hwp 调整日志的级别和分类
// 20071012 hwp 为会话增加UserType信息，并提供了设置和获取的方法
//                 (为支持FTD的ReqSubscribeTopic）
// 20080626 hwp NT-0041对话流和查询流不再使用Flow对象，只管理序号，减少内存占用
// 20080721 hwp NT-0045-分席位流控：将流控限额放入SessionInfo中，并提供
//                 设置会话流量限额的接口。
// 20080721 hwp NT-0047-修正发出登录请求后立即断线的错误：断线时无论会话
//                 是否有所有者，都向交易核心发出Logout请求。
// 20090512 hwp NT-0078:增加私有流缓冲区长度
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
const int MAX_COMM_FLUX		= 50;	//每SESSION_CHECK_INTERVAL的最大通讯量

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
//因为没有流控，暂时取消该定时器，by wangwei,20130116
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
	///重新开始计算流量
	pSessionInfo->nCommFlux -= pSessionInfo->nMaxCommFlux;
	if (pSessionInfo->nCommFlux < 0)
	{
		pSessionInfo->nCommFlux = 0;
	}
	///若流量超过规定，则挂起该会话的读操作
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
		pSessionInfo->nCommFlux ++; //流量控制改为计数
		///若流量超过规定，则挂起该会话的读操作
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
		//不应出现，这个信息在连接建立后就应该存在了
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

/*	清除前置会话对象的用户信息。这个会话对象还是存在，但是用户信息清空了。
//	会话的状态为未登录。这个方法用于用户主动发出登出请求。
//	longqy 20130906
*/
void CFrontEngine::ClearSessionOwner(const DWORD nSessionID)
{
	TFrontSessionInfo *pFind = m_mapSessionInfo.Find(nSessionID);
	if (pFind == NULL)
	{
		//不应出现，这个信息在连接建立后就应该存在了
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
		//没找到这个会话的信息，返回false
		return false;
	}
	return pFind->bIsLogin;
}

///	设置会话所有者的用户类型
bool CFrontEngine::SetSessionOwnerType(DWORD nSessionID, const CUserTypeType &UserType)
{
	TFrontSessionInfo *pFind = m_mapSessionInfo.Find(nSessionID);
	if (pFind == NULL)
	{
		//没找到这个会话的信息，返回false
		return false;
	}
	pFind->UserType = UserType;
	return true;
}

///	设置这个会话的最大的流量参数
bool CFrontEngine::SetSessionMaxCommFlux(DWORD nSessionID, int nMaxCommFlux)
{
	if (nMaxCommFlux <= 0)
	{
		return false;
	}
	TFrontSessionInfo *pFind = m_mapSessionInfo.Find(nSessionID);
	if (pFind == NULL)
	{
		//没找到这个会话的信息，返回false
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
		//没找到这个会话的信息，返回UT_SingleTrader
		return UT_SingleTrader;
	}
*/
	return pFind->UserType;
}

/*	当会话连接建立的时候，创建前置会话信息对象。一开始的时候，会话状态是没有登录。
//	设置这个会话的日志文件。
*/
void CFrontEngine::OnSessionConnected(CSession *pSession)
{
	//先调用基类的方法
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

/*	当会话断开的时候，删除前置会话信息对象。并主动向交易系统发出登出请求。
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
				
		//如果存在该会话的信息，则将其删除
		m_mapSessionInfo.Erase(pSession->GetSessionID());

		REPORT_EVENT(LOG_DEBUG, "Session", "Send TID_ReqUserLogout [0x%08x]", 
			pSession->GetSessionID());
		//向交易引擎发出该交易员的登出请求，
		//否则交易引擎无法得知其已断线，该交易员就再也无法登录了		
		m_pFrontForwarder->PrepareForward(&m_reqPackage, TID_ReqUserLogout, 
			pSession->GetSessionID(), 0);
		
		XTP_ADD_FIELD(&m_reqPackage, &userLogoutField);

		m_pFrontForwarder->ForwardTransaction(&m_reqPackage);
	}

// 	REPORT_EVENT(LOG_INFO, "Session", "[%s] [%s] disconnected",
// 		pSession->GetChannel()->GetRemoteName(), userLogoutField.UserID.getValue());

//	pSession->CloseChannelLogFile();
	
	//最后调用基类的方法
	CSessionFactory::OnSessionDisconnected(pSession, nReason);
}

/*	打开信道日志文件。文件的名字是 "/path/_00000000"
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
