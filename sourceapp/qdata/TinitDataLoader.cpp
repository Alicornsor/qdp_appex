// TinitDataLoader.cpp: implementation of the CTinitDataLoader class.
//
///20120424 林惜斌 交易编码权限上场指令添加
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "TinitDataLoader.h"
#include "XtpPackageDesc.h"
#include "FileFlow.h"

#define DEF_DAY_TABLE_INFO(name, condition, paraNumber, bHasSystemID)		\
	{"t_Sync_"#name, &C##name##Field::m_Describe,condition, TID_Init##name, paraNumber, false, bHasSystemID,{0}}

TTinitTableInfo g_DayTableInfo[] = 
{
//	DEF_DAY_TABLE_INFO(Exchange          , "",	0),
	DEF_DAY_TABLE_INFO(SystemStatus		 , "",	1,true),
	DEF_DAY_TABLE_INFO(UserInvestor      , "",	1,true),
	//20150620 xuzh seat 需要在 ClientTradingID 之前，因为ClientTradingID中需要使用seat的exchangeid字段
	DEF_DAY_TABLE_INFO(Seat              , "",	1,true),
	DEF_DAY_TABLE_INFO(Investor			 , "",	1,true),
	DEF_DAY_TABLE_INFO(User              , "",	1,true),
	//如果是数据库有线程，需要安装最大线程数目进行排序一下，保证ClientTradingID在Seat之后
	DEF_DAY_TABLE_INFO(ClientTradingID   , "",	1,true),
//	DEF_DAY_TABLE_INFO(UserTradingRight  , "",	1),
	DEF_DAY_TABLE_INFO(InvestorPosition    , "",	1,true),
	DEF_DAY_TABLE_INFO(InvestorAccount   , "",	1,true),
	DEF_DAY_TABLE_INFO(InvestorMargin      , "",	1,false),
	DEF_DAY_TABLE_INFO(InvestorFee         , "",	1,false),
	DEF_DAY_TABLE_INFO(InvestorPositionLimit         , "",	1,false),
//	DEF_DAY_TABLE_INFO(ComplianceParam   , "",	1),
	//lihh:增加系统状态表上场，场上只进行update

	// 2013/12/31 lidp 为支持大边保证金，增加两张sync表
//    DEF_DAY_TABLE_INFO(InstrumentGroup   , "",	1,false),
//	DEF_DAY_TABLE_INFO(ClientMarginCombType   , "",	1,false),
//	DEF_DAY_TABLE_INFO(InvestorLinker   , "",	1),	
//	DEF_DAY_TABLE_INFO(InvestorTradingRight   , "",	1),	
	DEF_DAY_TABLE_INFO(UserIP , "",	1,false),	
	DEF_DAY_TABLE_INFO(InvestorOptionFee         , "",	1,false),
	//DEF_DAY_TABLE_INFO(Product           , "",	0),
	//DEF_DAY_TABLE_INFO(Instrument        , "",	0),
	//DEF_DAY_TABLE_INFO(Participant       , "",	0),
	{NULL, NULL, NULL, 0, 0, true,false}	//一定要有这一行，表示结束
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTinitDataLoader::CTinitDataLoader(CEventHandler *pServer, const char *pszFlowPath)
{
	m_pServer = pServer;
	m_nErrorCode = 0;
	m_pCurrTask = NULL;
	m_pCurrTableInfo = NULL;
	m_nTaskCount = 0;

	for (int i=0; i<MAX_DATA_LOAD_THREAD; i++)
	{
		m_DataLoadThreads[i] = new CTinitDataLoadThread(0x4C00+i, this, pszFlowPath);
	}
}

CTinitDataLoader::~CTinitDataLoader()
{
	for (int i=0; i<MAX_DATA_LOAD_THREAD; i++)
	{
		delete m_DataLoadThreads[i];
	}
}

bool CTinitDataLoader::StartLoadDay(CDateType &WorkDay,CSystemIDType SystemID)
{
	m_WorkDay = WorkDay;
	m_SystemID = SystemID;
	m_nTaskType = TIT_TD_INIT;
	StartWorkThread(g_DayTableInfo);
	return true;
}

void CTinitDataLoader::AppendData(CTinitDataLoadThread *pDataLoadThread)
{
	CFlow *pDataFlow = pDataLoadThread->GetDataFlow();	
	int nCount = 0;
	while (nCount < pDataFlow->GetCount())
	{
		nCount += m_pServer->SendEvent(UM_TINIT_APPEND_DATA, nCount, pDataFlow);
	}
}

void CTinitDataLoader::StartWorkThread(TTinitTableInfo *pTableInfo)
{
	m_pCurrTableInfo = pTableInfo;
	m_pCurrTask = pTableInfo;
	m_nTaskCount = 0;
	for(TTinitTableInfo *p = pTableInfo; p->pszTable != NULL; p++)
	{
		p->bCanceled = false;
		m_nTaskCount ++;
		memset(p->pszSQL,0,MAX_TASK_COMMAND_LEN);
		strcpy(p->pszSQL,"SELECT ");
		for (int i=0; i<p->pFieldDescribe->GetMemberCount(); i++)
		{
			if (i != 0)
			{
				strcat(p->pszSQL, ", ");
			}
			strcat(p->pszSQL, p->pFieldDescribe->GetMemberDesc(i)->szName);
		}
		if (p->bHasSystemID)
		{
			sprintf(p->pszSQL+strlen(p->pszSQL)," FROM %s WHERE systemid=:1",p->pszTable);
			strcpy(p->SystemID,m_SystemID.getValue());
		}
		else
		{
			sprintf(p->pszSQL+strlen(p->pszSQL)," FROM %s",p->pszTable);
		}
	}
	for (int i=0; i<MAX_DATA_LOAD_THREAD; i++)
	{
		m_DataLoadThreads[i]->Create();
	}
}

void CTinitDataLoader::SetError(const char *pszTableName, int nErrorCode, const char *pszErrorMsg)
{
	m_nErrorCode = nErrorCode;
	m_strErrorMsg = pszTableName;
	m_strErrorMsg += " : ";
	m_strErrorMsg += pszErrorMsg;
	if (m_pServer != NULL)
	{
		m_pServer->SendEvent(UM_TINIT_ERROR, (DWORD)nErrorCode, (void *)m_strErrorMsg.c_str());
	}
}

TTinitTableInfo *CTinitDataLoader::GetTinitTableInfo(TTinitInitType &nType)
{
	TTinitTableInfo *pCurrTask = NULL;
	m_lock.Lock();
	if(m_pCurrTask  != NULL && m_pCurrTask->pszTable != NULL)
	{
		pCurrTask = m_pCurrTask;
		m_pCurrTask ++;
	}
	nType = m_nTaskType;
	m_lock.UnLock();
	return pCurrTask;
}

void CTinitDataLoader::OnDataLoadEnd(CTinitDataLoadThread *pTinitDataLoadThread,
		const char *pszTableName, int nErrorCode, const char *pszErrorMsg)
{
	m_lock.Lock();
	SetError(pszTableName, nErrorCode, pszErrorMsg);
	if (nErrorCode == 0)
	{
		AppendData(pTinitDataLoadThread);
	}
	else
	{
		Cancel();
	}
	m_nTaskCount--;
	if (m_nTaskCount <= 0)
	{
		m_pServer->PostEvent(UM_TINIT_APPEND_END, m_nTaskType, NULL);
	}
	m_lock.UnLock();
}


bool CTinitDataLoader::IsBusy()
{
	return m_nTaskCount > 0;
}

void CTinitDataLoader::Cancel()
{
	if (m_pCurrTableInfo == NULL)
	{
		return;
	}
	
	for(TTinitTableInfo *p = m_pCurrTableInfo; p->pszTable != NULL; p++)
	{
		p->bCanceled = true;
	}
}

bool CTinitDataLoader::ConnectDB(char *pszDatabaseName, char *pszUserName, char *pszPassword)
{
	for (int i=0; i<MAX_DATA_LOAD_THREAD; i++)
	{
		if(!m_DataLoadThreads[i]->ConnectDB(pszDatabaseName, pszUserName, pszPassword))
		{
			return false;
		}
	}
	return true;
}

