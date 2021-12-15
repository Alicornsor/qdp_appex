// TMDBWorker.cpp: implementation of the CTMDBWorker class.
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "TMDBWorker.h"
#include "DbConnection.h"
#include "CSVParser.h"

//每TMDB_COMMIT_VOLUME个数据库操作Commit一次
const int TMDB_COMMIT_VOLUME = 1000;
//每隔TMDB_COMMIT_INTERVAL毫秒Commit
const int TMDB_COMMIT_INTERVAL = 100;
//每TMDB_CONNECT_TIMER_COUNT×TMDB_COMMIT_INTERVAL毫秒尝试重连一次数据库
const int TMDB_CONNECT_TIMER_COUNT = 50;

const int TMDB_ACTION_MAX_LENGTH = 4096;

static char *ActionTypeName[] = 
{
	"ins",
	"upd",
	"del",
	"commit"
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTMDBWorker::CTMDBWorker(int nWorkerID, ITMDBSyncChecker *pSyncChecker, const char *pszWorkFilePath)
{
	m_nWorkerID = nWorkerID;
	m_pSyncChecker = pSyncChecker;
	m_pDbConnection = new CDbConnection;
	m_pSACommand = new SACommand(m_pDbConnection);
	m_pWorkData = new char[2048];
	m_bShouldRun = true;
	m_nCount = 0;
	m_fpTmdbAction = NULL;
	FPOS_SET(m_fposWrite, 0);

	m_strWorkFileName = pszWorkFilePath;
	char filename[40];
	sprintf(filename, "%d.tmdb", m_nWorkerID);
	m_strWorkFileName += filename;

	m_nConnectTimerCount = 0;
	m_nActionCount = 0;

	m_nDbKeepAliveTimeout = 0;
	
	m_tLastDbActionTime = time(NULL);
	memset(m_pSystemID,0,sizeof(m_pSystemID));
	Reset();
}

CTMDBWorker::~CTMDBWorker()
{
	if (m_fpTmdbAction != NULL)
	{
		fclose(m_fpTmdbAction);
	}
	CSACommandCache::iterator i=m_cacheSACommand.begin();
	for (; i!= m_cacheSACommand.end(); i++)
	{
		delete (*i).second;
	}
	m_cacheSACommand.clear();
	delete m_pSACommand;
	delete m_pDbConnection;
	delete m_pWorkData;
}

void CTMDBWorker::Stop()
{
	m_bShouldRun = false;
	Join();
}

void CTMDBWorker::Run()
{
	while (m_bShouldRun)
	{
		SleepMs(TMDB_COMMIT_INTERVAL);
		Work();
		DbKeepAlive();
	}
}

void CTMDBWorker::SetSystemID(const char *pSystemID)
{
	strncpy(m_pSystemID,pSystemID,4);
}

void CTMDBWorker::InitMethod(TTaskMethod *pTaskMethod)
{
	while (pTaskMethod->nWorkerID >= 0)
	{
		m_mapTaskMethod[pTaskMethod->pszObjectName] = pTaskMethod;
		pTaskMethod++;
	}
}

bool CTMDBWorker::ConnectDB(const char *pszDatabaseName,const char *pszUserName, 
							const char *pszPassword)
{
	return m_pDbConnection->ConnectDB(pszDatabaseName, pszUserName, pszPassword);
}

void CTMDBWorker::Reset()
{
	m_mutexTask.Lock();
	if (m_fpTmdbAction != NULL)
	{
		fclose(m_fpTmdbAction);
	}
	m_fpTmdbAction = mfopen(m_strWorkFileName.c_str(), "w+b");
	m_queueTask.clear();
	m_nCount = 0;
	m_mutexTask.UnLock();
}

void CTMDBWorker::AssignTask(CMutex *pAccomplisLock, int *pAccomplishRef, int nTaskNo, const char *pszObjectName, 
	CFieldDescribe *pDescirbe, const void *pData, TTmdbActionType nActionType)
{
	//BIZ_STATUS_LOG2("CTMDBWorker::AssignTask %d %s\n", nTaskNo, pszObjectName);

	TTmdbAction tmdbAction;
	tmdbAction.pAccomplisLock = pAccomplisLock;
	tmdbAction.pAccomplishRef = pAccomplishRef;
	tmdbAction.nTaskNo = nTaskNo;
	tmdbAction.nActionType = nActionType;
	tmdbAction.pszObjectName = pszObjectName;
//	tmdbAction.pData = m_listTaskData.PushBack((void *)pData, pDescirbe->GetStructSize());
	tmdbAction.pDescirbe = pDescirbe;
	tmdbAction.fposData = m_fposWrite;

	m_mutexTask.Lock();
	
	if (nActionType != TA_COMMIT || m_nActionCount > 0)
	{
		if (nActionType == TA_COMMIT)
		{
			m_nActionCount = 0;
		}
		else
		{
			m_nActionCount++;
		}
		m_queueTask.push_back(tmdbAction);
		SaveAction(&tmdbAction, (void *)pData, m_fpTmdbAction);
	}

	m_mutexTask.UnLock();
}

void CTMDBWorker::SaveAction(TTmdbAction *pAction, void *pData, FILE *fp)
{
	char buf[TMDB_ACTION_MAX_LENGTH];

	sprintf(buf, "%d,", pAction->nTaskNo);
	strcat(buf, ActionTypeName[pAction->nActionType]);
	strcat(buf, ",");
	strcat(buf, pAction->pszObjectName);

	if (pAction->pDescirbe != NULL)
	{
		for (int i=0; i<pAction->pDescirbe->GetMemberCount(); i++)
		{
			TMemberDesc *pMemberDesc = pAction->pDescirbe->GetMemberDesc(i);
			strcat(buf, ",");
			strcat(buf, pMemberDesc->szName);
			strcat(buf, ",");
			char strTemp[2] = {'\0', '\0'};
			char *pMemberData = (char *)pData+pMemberDesc->nStructOffset;
			switch(pMemberDesc->nType) {
			case FT_WORD:						//short
				sprintf(buf+strlen(buf), "%d", *((short *)pMemberData));
				break;
			case FT_DWORD:						//long
				sprintf(buf+strlen(buf), "%ld", *((int *)pMemberData));
				break;
			case FT_REAL4:
				sprintf(buf+strlen(buf), "%f", *((REAL4 *)pMemberData));
				break;
			case FT_REAL8:						//double
				if (*((REAL8 *)pMemberData) != DOUBLE_NaN)
				{
					sprintf(buf+strlen(buf), "%lf", *((REAL8 *)pMemberData));
				}
				break;
			case FT_BYTE:
				if (pMemberDesc->nSize == 1)
				{
					strTemp[0] = *pMemberData;
					strcat(buf, strTemp);
				}
				else
				{
					strcat(buf, pMemberData);
				}
				break;
			}
		}
	}
	strcat(buf, "\n");

	fsetpos(fp, &m_fposWrite);

	int len = strlen(buf);
	FPOS_SET(m_fposWrite, FPOS_GET(m_fposWrite)+len);

	fwrite(buf, 1, len, fp);
	fflush(fp);
}

void CTMDBWorker::LoadAction(TTmdbAction *pAction, void *pData, FILE *fp)
{
	if (pAction->pDescirbe == NULL)
	{
		return;
	}
	char buf[TMDB_ACTION_MAX_LENGTH];
	fsetpos(fp, &pAction->fposData);
	fread(buf, 1, TMDB_ACTION_MAX_LENGTH, fp);

	CCSVParser parser(buf);
	for(int i=0; ; i++) {
		char *pToken = parser.GetNextToken();
		if (pToken == NULL)
		{
			break;
		}
		if (i < 3 || i%2 != 0)
		{
			continue;
		}
		int nMemberPos = (i-3)/2;
		TMemberDesc *pMemberDesc = pAction->pDescirbe->GetMemberDesc(nMemberPos);
		char *pMemberData = (char *)pData+pMemberDesc->nStructOffset;
		switch(pMemberDesc->nType) {
		case FT_WORD:						//short
			*((short *)pMemberData) = atoi(pToken);
			break;
		case FT_DWORD:						//long
			*((int *)pMemberData) = atoi(pToken);
			break;
		case FT_REAL4:
			*((REAL4 *)pMemberData) = atof(pToken);
			break;
		case FT_REAL8:						//double
			if (*pToken == '\0')
			{
				*((REAL8 *)pMemberData) = DOUBLE_NaN;
			}
			else
			{
				*((REAL8 *)pMemberData) = atof(pToken);
			}
			break;
		case FT_BYTE:
			if (pMemberDesc->nSize == 1)
			{
				*pMemberData = *pToken;
			}
			else
			{
				strcpy(pMemberData, pToken);
			}
			break;
		}
		
		if(parser.GetErrorCode() != CPE_HAS_NEXT)
		{
			break;
		}
	}
}

void CTMDBWorker::Work()
{
	if (!m_pDbConnection->isConnected())
	{
		m_nConnectTimerCount++;
		if(m_nConnectTimerCount > TMDB_CONNECT_TIMER_COUNT)
		{
			m_nConnectTimerCount = 0;
			m_pDbConnection->ConnectDB();
			BIZ_STATUS_LOG1("Connect DB %d\n", m_nWorkerID);
		}
		if (!m_pDbConnection->isConnected())
		{
			if (m_nConnectTimerCount == 0)
			{
				REPORT_EVENT(LOG_CRITICAL, "Database","CTMDBWorker [%d] Connect DB Error", m_nWorkerID);
			}
			return;
		}
	}
	
	CommitActions();
	
	while (m_queueTask.size() > 0)
	{
		m_mutexTask.Lock();

		TTmdbAction tmdbAction = m_queueTask.front();
		
		if (m_pSyncChecker != NULL)			//本线程需要同步执行工作
		{
			if (!m_pSyncChecker->CheckTaskSync(tmdbAction.nTaskNo))
			{
				//还有其它线程在工作，等会儿再查
				m_mutexTask.UnLock();
				break;
			}
		}
		
		//先将任务从队列中取到本地，就可以将任务从队列中去除，
		//防止过长时间锁任务队列
		m_queueTask.pop_front();

		if (tmdbAction.nActionType != TA_COMMIT)
		{
			LoadAction(&tmdbAction, m_pWorkData, m_fpTmdbAction);
		}
//		memcpy(m_pWorkData, tmdbAction.pData, tmdbAction.pDescirbe->GetStructSize());
//		m_listTaskData.PopFront(tmdbAction.pDescirbe->GetStructSize());

		m_mutexTask.UnLock();

		m_actionUncommitted.push_back(tmdbAction);

		if (tmdbAction.nActionType != TA_COMMIT)
		{
			//BIZ_STATUS_LOG3("DbOperation nTaskNo=%d objName=%s ACount=%d\n", tmdbAction.nTaskNo, tmdbAction.pszObjectName, (*tmdbAction.pAccomplishRef));
			int r = DbOperation(tmdbAction.pszObjectName, tmdbAction.pDescirbe, 
				tmdbAction.nActionType, tmdbAction.nTaskNo);
			if (r < 0 && !m_pDbConnection->isConnected())
			{
				break;
			}
		}
		if (m_actionUncommitted.size()>TMDB_COMMIT_VOLUME)
		{
			CommitActions();
		}
		m_tLastDbActionTime = time(NULL);
	}
}

int CTMDBWorker::DbOperation(const char *pszObjectName, CFieldDescribe *pDescirbe, 
							 TTmdbActionType nActionType, int nTaskNo)
{
	TTaskMethod *pTaskMethod = FindMethod(pszObjectName);
	
	if (pTaskMethod == NULL)
	{
		return -1;
	}
	
	int ret = 0;
	for (int nRetryTimes=2; nRetryTimes>0; nRetryTimes--)		//重做2次
	{
		try {
			switch(pTaskMethod->nMethodType) {
			case TMT_TABLE:
				switch(nActionType) {
				case TA_INSERT:
					ret = DbTableOperation(pDescirbe, pTaskMethod->szInsertCommand,
						pTaskMethod->keyPosition, nActionType,pTaskMethod->bHasSystemID);
					break;
				case TA_UPDATE:
					{
						bool bHasSystemID=pTaskMethod->bHasSystemID;
						if (strcmp(pTaskMethod->pszObjectName,"t_Oper_User")==0)
						{
							bHasSystemID = false;
						}
						ret = DbTableOperation(pDescirbe, pTaskMethod->szUpdateCommand, 
							pTaskMethod->keyPosition, nActionType,bHasSystemID);
						break;
					}

				case TA_DELETE:
					ret = DbTableOperation(pDescirbe, pTaskMethod->szDeleteCommand, 
						pTaskMethod->keyPosition, nActionType,pTaskMethod->bHasSystemID);
					break;
				default:
					RAISE_DESIGN_ERROR("Invalid tdmb action\n");
				}
				nRetryTimes = 0;					//成功了不需要重做
				break;
			case TMT_SP:
				ret = DbSpOperation(pDescirbe, pTaskMethod->pszKeyName, nActionType);
				nRetryTimes = 0;					//成功了不需要重做
				break;
			default:
				RAISE_DESIGN_ERROR("Invalid tdmb method type\n");
			}
		}	
		catch(SAException &x)
		{
			ret = -2;
			REPORT_EVENT(LOG_CRITICAL, "Database", 
				"Database Operation Exception, TaskNo=%d Object=%s ActionType=%d Message=%s",
				nTaskNo, pszObjectName, nActionType, (const char*)x.ErrText());

			try
			{
				if (!CheckDbConnection(x.ErrNativeCode()))
				{
					RollbackActions();
					nRetryTimes = 0;
				}
			}
			catch(SAException &)
			{
			}
		}
	}
	if(ret ==0 )
	{
		m_nCount++;
		//BIZ_OPERATION_LOG2("Database Operation Success, Object=%s ActionType=%d\n",pszObjectName, nActionType);
	}
	else
	{
		BIZ_OPERATION_LOG3("Database Operation Failed, Object=%s ActionType=%d ret=%d\n",
			pszObjectName, nActionType,ret);
	}
	return ret;
}

TTaskMethod *CTMDBWorker::FindMethod(const char *pszObjectName)
{
	CTaskMethodMap::iterator i = m_mapTaskMethod.find(pszObjectName);
	if (i == m_mapTaskMethod.end())
	{
		return NULL;
	}
	return (*i).second;
}

int CTMDBWorker::DbTableOperation(CFieldDescribe *pDescirbe, const char *pszSQLCommand,
								  int *pKeyPosition, TTmdbActionType nActionType,bool bHasSystemID)
{
	SACommand *pSACommand = GetSACommand(pszSQLCommand);

	assert(pSACommand != NULL);
	
	int nParamPosition = 1;
	if (nActionType == TA_INSERT || nActionType == TA_UPDATE)
	{
		for (int i=0; i<pDescirbe->GetMemberCount(); i++)
		{
			BindParam(pDescirbe->GetMemberDesc(i), nParamPosition, pSACommand);
			nParamPosition++;
		}
	}
	
	if (nActionType == TA_DELETE || nActionType == TA_UPDATE)
	{
		int *pCurrPosition = pKeyPosition;
		while (*pKeyPosition > 0)
		{
			BindParam(pDescirbe->GetMemberDesc(*pKeyPosition-1), nParamPosition, pSACommand);
			pKeyPosition++;
			nParamPosition++;
		}
	}

	if (bHasSystemID)
	{
		pSACommand->Param(nParamPosition).setAsString() = m_pSystemID;
	}
	
	
//	REPORT_EVENT(LOG_CRITICAL,"test","%s \n",pSACommand->CommandText());

	pSACommand->Execute();

//	m_pDbConnection->Commit();

	return 0;
}

int CTMDBWorker::DbSpOperation(CFieldDescribe *pDescirbe, const char *pszKeyName, TTmdbActionType nActionType)
{
	m_pSACommand->setCommandText(pszKeyName);//, SA_CmdStoredProc);

	m_pSACommand->Param("i_ActionType").setAsLong() = nActionType;

	char szTemp[1000] = "i_";
	for (int i=0; i<pDescirbe->GetMemberCount(); i++)
	{
		strcpy(szTemp+2, pDescirbe->GetMemberDesc(i)->szName);
		BindParam(pDescirbe->GetMemberDesc(i), szTemp, m_pSACommand);
	}
	
	m_pSACommand->Execute();

	m_pDbConnection->Commit();

	return m_pSACommand->Param("o_ReturnNo").asLong();
}

void CTMDBWorker::BindParam(TMemberDesc *pMemberDesc, int nParamPosition, SACommand *pSACommand)
{
	char strTemp[2] = {'\0', '\0'};
	char *pMemberData = m_pWorkData+pMemberDesc->nStructOffset;
	switch(pMemberDesc->nType) {
	case FT_WORD:						//short
		pSACommand->Param(nParamPosition).setAsShort() = *((short *)pMemberData);
		break;
	case FT_DWORD:						//long
		pSACommand->Param(nParamPosition).setAsLong() = *((int *)pMemberData);
		break;
	case FT_REAL4:
		pSACommand->Param(nParamPosition).setAsDouble() = *((REAL4 *)pMemberData);
		break;
	case FT_REAL8:						//double
		if (*((REAL8 *)pMemberData) == DOUBLE_NaN)
		{
			pSACommand->Param(nParamPosition).setAsNull();
		}
		else
		{
			pSACommand->Param(nParamPosition).setAsDouble() = *((REAL8 *)pMemberData);
		}
		break;
	case FT_BYTE:
		if (pMemberDesc->nSize == 1)
		{
			strTemp[0] = *pMemberData;
			pSACommand->Param(nParamPosition).setAsString() = strTemp;
		}
		else
		{
			pSACommand->Param(nParamPosition).setAsString() = pMemberData;
		}
		break;
	}
}

void CTMDBWorker::BindParam(TMemberDesc *pMemberDesc, const char *pszParamName, SACommand *pSACommand)
{
	char strTemp[2] = {'\0', '\0'};
	char *pMemberData = m_pWorkData+pMemberDesc->nStructOffset;
	switch(pMemberDesc->nType) {
	case FT_WORD:						//short
		pSACommand->Param(pszParamName).setAsShort() = *((short *)pMemberData);
		break;
	case FT_DWORD:						//long
		pSACommand->Param(pszParamName).setAsLong() = *((int *)pMemberData);
		break;
	case FT_REAL4:
		pSACommand->Param(pszParamName).setAsDouble() = *((REAL4 *)pMemberData);
		break;
	case FT_REAL8:						//double
		if (*((REAL8 *)pMemberData) == DOUBLE_NaN)
		{
			pSACommand->Param(pszParamName).setAsNull();
		}
		else
		{
			pSACommand->Param(pszParamName).setAsDouble() = *((REAL8 *)pMemberData);
		}
		break;
	case FT_BYTE:
		if (pMemberDesc->nSize == 1)
		{
			strTemp[0] = *pMemberData;
			pSACommand->Param(pszParamName).setAsString() = strTemp;
		}
		else
		{
			pSACommand->Param(pszParamName).setAsString() = pMemberData;
		}
		break;
	}
}

SACommand *CTMDBWorker::GetSACommand(const char *pszSQL)
{
	SACommand *pSACommand = NULL;

	CSACommandCache::iterator i = m_cacheSACommand.find(pszSQL);

	if (i == m_cacheSACommand.end())
	{
		pSACommand = new SACommand(m_pDbConnection);
		pSACommand->setCommandText(pszSQL, SA_CmdSQLStmt);
		m_cacheSACommand[pszSQL] = pSACommand;
	}
	else
	{
		pSACommand = (*i).second;
	}

	return pSACommand;
}

void CTMDBWorker::CommitActions()
{
	if (m_actionUncommitted.size() <= 0)
	{
		return;
	}
	if (m_actionUncommitted.back().nActionType != TA_COMMIT)
	{
		return;
	}

	try
	{
		m_pDbConnection->Commit();
	}	
	catch(SAException &x)
	{
		BIZ_EXCEPTION_LOG1("Database Operation Exception, Commit error, Message=%s\n",
			(const char*)x.ErrText());
		try
		{
			CheckDbConnection(x.ErrNativeCode());
			RollbackActions();
		}
		catch(SAException &)
		{
		}
	}

	vector<TTmdbAction>::iterator i=m_actionUncommitted.begin();
	for (; i!=m_actionUncommitted.end(); i++)
	{
		if (i->pAccomplishRef != NULL)
		{
			//使调度器知道该工作已经做完
			i->pAccomplisLock->Lock();
			(*(i->pAccomplishRef))--;
			i->pAccomplisLock->UnLock();	
		}
	}

	m_actionUncommitted.clear();
}


void CTMDBWorker::RollbackActions()
{
	try
	{
		m_pDbConnection->Rollback();
	}
	catch(SAException &x)
	{
		BIZ_EXCEPTION_LOG1("Database Operation Exception, Rollback error, Message=%s\n",
			(const char*)x.ErrText());
	}
	m_mutexTask.Lock();
	vector<TTmdbAction>::reverse_iterator i=m_actionUncommitted.rbegin();
	for (; i!=m_actionUncommitted.rend(); i++)
	{
		m_queueTask.push_front(*i);
	}	
	
	m_actionUncommitted.clear();
	m_mutexTask.UnLock();

	BIZ_STATUS_LOG1("CTMDBWorker::RollbackActions [%d]\n", m_nWorkerID);
}

bool CTMDBWorker::CheckDbConnection(int nErrorNativeCode)
{
	m_pDbConnection->CheckConntectionError(nErrorNativeCode);
	if (!m_pDbConnection->isConnected())
	{
		m_nConnectTimerCount = 0;
		return false;
	}
	return true;
}

void CTMDBWorker::EnableDbKeepAlive(int nTimeout)
{
	m_nDbKeepAliveTimeout = nTimeout;
}

void CTMDBWorker::DbKeepAlive()
{
	time_t tNow = time(NULL);
	if (m_nDbKeepAliveTimeout>0 && tNow-m_tLastDbActionTime > m_nDbKeepAliveTimeout)
	{
		m_pDbConnection->KeepAlive();
		m_tLastDbActionTime = time(NULL);
	}
}

CTMDBWorker::CTaskQueue * CTMDBWorker::GetQueueTask()
{	
	return &m_queueTask; 
}
