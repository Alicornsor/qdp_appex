// TMDBScheduler.cpp: implementation of the CTMDBScheduler class.
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "TMDBScheduler.h"
#include "CSVParser.h"
#include "XtpPackageDesc.h"

#define TASK_METHOD_DEFINE(WorkID, field, MethodType, ObjectName, KeyName, HasSystemID)		\
	{ WorkID, &field::m_Describe, MethodType, ObjectName, KeyName, {0}, {0}, {0}, {0},HasSystemID}

#define TASK_METHOD_END															\
	{ -1, NULL, TMT_TABLE, "", "", {0}, {0}, {0}, {0},false}
			
//WorkerID为0表示同步工作线程

TTaskMethod g_TaskMethod[] =
{
	TASK_METHOD_DEFINE(0, CSystemInfoField, TMT_TABLE,"t_Oper_SystemInfo", "SystemID",false),
//	TASK_METHOD_DEFINE(0, CSystemStatusField, TMT_TABLE,"t_Oper_SystemStatus", "TradingDay",true),	
	TASK_METHOD_DEFINE(0, CDataSyncStatusField, TMT_TABLE,"t_Oper_DataSyncStatus", "TradingDay",false),
		
	TASK_METHOD_DEFINE(1, COrderField, TMT_TABLE,"t_Oper_Order", "ExchangeID,OrderSysID",true),//+ExchangeID
	TASK_METHOD_DEFINE(2, CTradeField, TMT_TABLE,"t_Oper_Trade", "ExchangeID,TradeID,OrderSysID",true),//+Direction
	TASK_METHOD_DEFINE(3, CInvestorAccountField, TMT_TABLE,"t_Oper_InvestorAccount", "BrokerID,AccountID",true),	
	TASK_METHOD_DEFINE(4, CInvestorPositionField, TMT_TABLE,"t_Oper_InvestorPosition", "BrokerID,ExchangeID,ClientID,InstrumentID,Direction",true),	

	TASK_METHOD_DEFINE(5, CUserField, TMT_TABLE,"t_Oper_User", "BrokerID,UserID",true),
	TASK_METHOD_DEFINE(5, CUserField, TMT_TABLE,"t_Sync_User", "BrokerID,UserID",false),
	TASK_METHOD_DEFINE(5, CUserSessionField, TMT_TABLE,"t_Oper_UserSession", "BrokerID,UserID,SessionID",true),
	TASK_METHOD_DEFINE(5, CInstrumentField, TMT_TABLE,"t_Oper_Instrument", "ExchangeID,InstrumentID",true),	//InstrumentID
	TASK_METHOD_DEFINE(5, CExchangeField, TMT_TABLE,"t_Oper_Exchange", "ExchangeID",true),
//	TASK_METHOD_DEFINE(5, CInvestorLinkerField, TMT_TABLE,"t_Oper_InvestorLinker", "UserID,APIID,InvestorID"),
//	TASK_METHOD_DEFINE(5, COrderInsertFailedField, TMT_TABLE,"t_Oper_OrderInsertFailed", "BrokerID,UserID,UserCustom"),//+ExchangeID   //错单表，不会重复，不设主键
//	TASK_METHOD_DEFINE(5, CInvestorTradingRightField, TMT_TABLE,"t_Oper_InvestorTradingRight", "BrokerID,ExchangeID,InvestorID,InstrumentID"),
	TASK_METHOD_DEFINE(5, CSGEDeferRateField, TMT_TABLE,"t_Oper_SGEDeferRate", "InstrumentID,ExchangeID,TradeDate",false),
	TASK_METHOD_END
};

const int DBCONN_KEEP_ALIVE_TIMEOUT = 60;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTMDBScheduler::CTMDBScheduler(CReactor *pReactor, CAccomplishFlow *pAccomplishFlow, const char *pszWorkFilePath)
:CEventHandler(pReactor)
{
	m_pAccomplishFlow = pAccomplishFlow;
	RefreshCurrTaskNo();
	SetTimer(1, 1000);
	m_pCountIndex = new CIntTotalMonitorIndex("TMDBCount",20);
	m_strWorkFilePath = pszWorkFilePath;
}

CTMDBScheduler::~CTMDBScheduler()
{
	CWorkerMap::iterator i = m_mapWorker.begin();
	while (i != m_mapWorker.end())
	{
		delete (*i).second;
		i++;
	}
}

bool CTMDBScheduler::Init(const char *pszDatabaseName,const char *pszUserName, const char *pszPassword)
{
	TTaskMethod *pTaskMethod = g_TaskMethod;
	while (pTaskMethod->nWorkerID >= 0)
	{	
		PrepareTaskMethod(pTaskMethod);
		
		CTMDBWorker *pWorker = GetWorker(pTaskMethod->nWorkerID);
		if (pWorker == NULL)
		{
			//nWorkerID为0表示同步工作线程
			pWorker = new CTMDBWorker(pTaskMethod->nWorkerID, 
				(pTaskMethod->nWorkerID == 0)?this:NULL, 
				m_strWorkFilePath.c_str());
			m_mapWorker[pTaskMethod->nWorkerID] = pWorker;
			if ( !pWorker->ConnectDB(pszDatabaseName, pszUserName, pszPassword) )
			{
				return false;
			}
			pWorker->EnableDbKeepAlive(DBCONN_KEEP_ALIVE_TIMEOUT);
		}
		m_mapDispatch[pTaskMethod->pszObjectName] = pWorker;

		pTaskMethod++;
	}

	
	CWorkerMap::iterator i = m_mapWorker.begin();
	while (i != m_mapWorker.end())
	{
		if((*i).first ==0)
		{
			(*i).second->InitMethod(g_TaskMethod);
			(*i).second->Create();
		}
		i++;
	}
	return true;
}

void CTMDBScheduler::StartAllNonSyncThread(const char *pSystemID)
{
	m_pAccomplishFlow->SetSystemID(pSystemID);
	CWorkerMap::iterator i = m_mapWorker.begin();
	while (i != m_mapWorker.end())
	{
		if((*i).first !=0)
		{
			(*i).second->SetSystemID(pSystemID);
			(*i).second->InitMethod(g_TaskMethod);
			(*i).second->Create();
		}
		i++;
	}
}

void CTMDBScheduler::Dispatch(const char *pszObjectName, CFieldDescribe *pDescirbe, 
							  const void *pData, TTmdbActionType nActionType)
{
	if (m_queueTask.empty())
	{
		return;
	}
	
	CTMDBWorker *pWorker = GetWorker(pszObjectName);
	if (pWorker == NULL)
	{
		REPORT_EVENT(LOG_CRITICAL, "Tmdb", "Can't find worker for %s", pDescirbe->GetFieldName());
		return ;
	}
		
	TTmdbTask &task = m_queueTask.back();
	m_mutexAccomplishCount.Lock();
	task.nActionCount++;
	m_mutexAccomplishCount.UnLock();
	pWorker->AssignTask(&m_mutexAccomplishCount, &(task.nActionCount), task.nTaskNo,
		pszObjectName, pDescirbe, pData, nActionType);
}

CTMDBWorker *CTMDBScheduler::GetWorker(int nWorkerID)
{
	CWorkerMap::iterator i = m_mapWorker.find(nWorkerID);
	if (i == m_mapWorker.end())
	{
		return NULL;
	}

	return (*i).second;
}

CTMDBWorker *CTMDBScheduler::GetWorker(const char *pszObjectName)
{
	CDispatchMap::iterator i = m_mapDispatch.find(pszObjectName);
	if (i == m_mapDispatch.end())
	{
		return NULL;
	}
	return (*i).second;
}

void CTMDBScheduler::RefreshCurrTaskNo()
{
	if (m_queueTask.empty())
	{
		m_nCurrTaskNo = -1;
	}
	else
	{
		m_nCurrTaskNo = m_queueTask.front().nTaskNo;
	}
}

void CTMDBScheduler::SetAccomplishCommPhaseNo(WORD wCommPhaseNo)
{
	m_pAccomplishFlow->SetCommPhaseNo(wCommPhaseNo);
	CWorkerMap::iterator i = m_mapWorker.begin();
	while (i != m_mapWorker.end())
	{
		(*i).second->Reset();
		i++;
	}
}

void CTMDBScheduler::AssignTask(DWORD nTaskNo)
{
	DWORD nCompleteTaskNo = m_pAccomplishFlow->GetCount();
	BIZ_STATUS_LOG2("Complete TaskNo=[%d],Current TaskNo=[%d]\n",nCompleteTaskNo,nTaskNo);
	if (nTaskNo <= nCompleteTaskNo)
	{
		//已处理过，不再重做
		BIZ_STATUS_LOG2("skip TaskNo=[%d],Current TaskNo=[%d]\n",nCompleteTaskNo,nTaskNo);
		return ;
	}
	TTmdbTask task;
	task.nActionCount = 0;
	task.nTaskNo = nTaskNo;
	m_queueTask.push_back(task);

	RefreshCurrTaskNo();
}

void CTMDBScheduler::SetCommitPoint(DWORD nTaskNo)
{
	CWorkerMap::iterator i = m_mapWorker.begin();
	for (; i != m_mapWorker.end(); i++)
	{
		(*i).second->AssignTask(NULL, NULL, nTaskNo,
			"", NULL, NULL, TA_COMMIT);
	}
}

void CTMDBScheduler::OnTimer(int nIDEvent)
{
	int nCompleteTaskNo = 0;
	while (!m_queueTask.empty())
	{
		if (m_queueTask.front().nActionCount != 0)
		{
			break;
		}
		nCompleteTaskNo = m_queueTask.front().nTaskNo;
		m_queueTask.pop_front();
	}
// 	if (nCompleteTaskNo != 0)
// 	{
// 		m_pAccomplishFlow->Truncate(nCompleteTaskNo);
// 	}
		
	CWorkerMap::iterator i = m_mapWorker.begin();
	static int nPreCount=0;
	int nCount=0;
	while (i != m_mapWorker.end())
	{
		nCount+= (*i).second->GetCount();
		i++;
	}
	m_pCountIndex->incValue(nCount-nPreCount);
	nPreCount=nCount;
	CMonitorIndex::handleOne();
	RefreshCurrTaskNo();
}

bool CTMDBScheduler::CheckTaskSync(int nTaskNo)
{
	//m_nCurrTaskNo会被多个线程同时访问，调度线程只写，其它工作线程只读
	if (m_nCurrTaskNo == nTaskNo)
	{
		return true;
	}
	return false;
}

void CTMDBScheduler::PrepareTaskMethod(TTaskMethod *pTaskMethod)
{
	if (pTaskMethod->nMethodType == TMT_SP)
	{
		//SP 不用准备什么
		return;
	}

	int i = 0;	
	int *pKeyPosition = pTaskMethod->keyPosition;

	//prepare key position
	CCSVParser csvParser(pTaskMethod->pszKeyName);
	do {
		char *pToken = csvParser.GetNextToken();
		if (pToken != NULL)
		{
			for (i=0; i<pTaskMethod->pDescirbe->GetMemberCount(); i++)
			{
				if(strcmp(pToken, pTaskMethod->pDescirbe->GetMemberDesc(i)->szName) == 0)
				{
					*pKeyPosition = i+1;
					pKeyPosition++;
					break;
				}
			}
			if (i == pTaskMethod->pDescirbe->GetMemberCount())
			{
				RAISE_DESIGN_ERROR("Can't find key name\n");
			}
		}
	} while(csvParser.GetErrorCode() == CPE_HAS_NEXT);
	*pKeyPosition = 0;		//结束符

	char strSQL[MAX_TASK_COMMAND_LEN];
	//prepare insert statement
	strcpy(strSQL, "INSERT INTO ");
	strcat(strSQL, pTaskMethod->pszObjectName);
	strcat(strSQL, " (");
	for (i=0; i<pTaskMethod->pDescirbe->GetMemberCount(); i++)
	{
		if (i != 0)
		{
			strcat(strSQL, ", ");
		}
		strcat(strSQL, pTaskMethod->pDescirbe->GetMemberDesc(i)->szName);
	}
	if (pTaskMethod->bHasSystemID)
	{
		strcat(strSQL, ",SystemID) VALUES (");
	}
	else
	{
		strcat(strSQL, ") VALUES (");
	}
	for (i=0; i<pTaskMethod->pDescirbe->GetMemberCount(); i++)
	{
		if (i != 0)
		{
			strcat(strSQL, ", ");
		}
		sprintf(strSQL+strlen(strSQL), ":%d", i+1);
	}
	if (pTaskMethod->bHasSystemID)
	{
		sprintf(strSQL+strlen(strSQL), ",:%d)", i+1);
	}
	else
	{
		strcat(strSQL, ")");
	}
	strcpy(pTaskMethod->szInsertCommand, strSQL);
	BIZ_OPERATION_LOG1("SQL: %s\n", strSQL);

	//prepare update statement
	strcpy(strSQL, "UPDATE ");
	strcat(strSQL, pTaskMethod->pszObjectName);
	strcat(strSQL, " SET ");
	for (i=0; i<pTaskMethod->pDescirbe->GetMemberCount(); i++)
	{
		if (i != 0)
		{
			strcat(strSQL, ", ");
		}
		strcat(strSQL, pTaskMethod->pDescirbe->GetMemberDesc(i)->szName);
		sprintf(strSQL+strlen(strSQL), " = :%d", i+1);
	}
	strcat(strSQL, " WHERE ");


	i=0;
	pKeyPosition = pTaskMethod->keyPosition;
	while (*pKeyPosition > 0)
	{
		if (i != 0)
		{
			strcat(strSQL, " AND ");
		}
		sprintf(strSQL+strlen(strSQL), "%s=:%d", 
			pTaskMethod->pDescirbe->GetMemberDesc(*pKeyPosition-1)->szName,
			i+pTaskMethod->pDescirbe->GetMemberCount()+1);
		i++;
		pKeyPosition++;
	}
	if (pTaskMethod->bHasSystemID && strcmp(pTaskMethod->pszObjectName,"t_Oper_User"))
	{
		if (i>0)
		{
			sprintf(strSQL+strlen(strSQL), " AND systemid=:%d",pTaskMethod->pDescirbe->GetMemberCount()+i+1);
		}
		else
		{
			sprintf(strSQL+strlen(strSQL), " systemid=:%d",pTaskMethod->pDescirbe->GetMemberCount()+i+1);
		}
	}
	
	strcpy(pTaskMethod->szUpdateCommand, strSQL);
	BIZ_OPERATION_LOG1("SQL: %s\n", strSQL);

	//prepare delete statement
	strcpy(strSQL, "DELETE FROM ");
	strcat(strSQL, pTaskMethod->pszObjectName);
	strcat(strSQL, " WHERE ");

	i = 0;	
	pKeyPosition = pTaskMethod->keyPosition;
	while (*pKeyPosition > 0)
	{
		if (i != 0)
		{
			strcat(strSQL, " AND ");
		}
		sprintf(strSQL+strlen(strSQL), "%s=:%d", 
			pTaskMethod->pDescirbe->GetMemberDesc(*pKeyPosition-1)->szName,
			i+1);
		i++;
		pKeyPosition++;
	}
	if (pTaskMethod->bHasSystemID)
	{
		if (i>0)
		{
			sprintf(strSQL+strlen(strSQL), " AND systemid=:%d",i+1);
		}
		else
		{
			sprintf(strSQL+strlen(strSQL), " systemid=:%d",i+1);
		}

	}
	strcpy(pTaskMethod->szDeleteCommand, strSQL);
	BIZ_OPERATION_LOG1("SQL: %s\n", strSQL);
}

