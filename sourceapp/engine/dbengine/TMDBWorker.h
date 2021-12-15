// TMDBWorker.h: interface for the CTMDBWorker class
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TMDBWORKER_H__F249E0F2_D273_402C_9AF3_FC12BA8FF048__INCLUDED_)
#define AFX_TMDBWORKER_H__F249E0F2_D273_402C_9AF3_FC12BA8FF048__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"
#include "FieldDescribe.h"
#include "CacheList.h"
#include "Mutex.h"

enum TTmdbActionType
{
	TA_INSERT,
	TA_UPDATE,
	TA_DELETE,
	TA_COMMIT,
};

struct TTmdbAction
{
	CMutex *pAccomplisLock;
	int *pAccomplishRef;
	int nTaskNo;
	const char *pszObjectName;
	CFieldDescribe *pDescirbe;
	//void *pData;
	fpos_t fposData;
	TTmdbActionType nActionType;
};

enum TTaskMethodType
{
	TMT_TABLE,
	TMT_SP
};

const int MAX_TASK_COMMAND_LEN	= 4000;

struct TTaskMethod
{
	int nWorkerID;
	CFieldDescribe *pDescirbe;
	TTaskMethodType nMethodType;
	const char *pszObjectName;
	const char *pszKeyName;
	char szInsertCommand[MAX_TASK_COMMAND_LEN];
	char szUpdateCommand[MAX_TASK_COMMAND_LEN];
	char szDeleteCommand[MAX_TASK_COMMAND_LEN];
	int keyPosition[10];
	bool bHasSystemID;
};

class CDbConnection;
class SACommand;

class ITMDBSyncChecker
{
public:
	virtual bool CheckTaskSync(int nTaskNo) = 0;
protected:
	virtual ~ITMDBSyncChecker(){};
};

class CTMDBWorker : public CThread
{
public:
	CTMDBWorker(int nWorkerID, ITMDBSyncChecker *pSyncChecker, const char *pszWorkFilePath);
	virtual ~CTMDBWorker();

	void InitMethod(TTaskMethod *pTaskMethod);
	
	bool ConnectDB(const char *pszDatabaseName, const char *pszUserName, 
		const char *pszPassword);

	void AssignTask(CMutex *pAccomplisLock, int *pAccomplishRef, int nTaskNo, const char *pszObjectName, 
		CFieldDescribe *pDescirbe, const void *pData, TTmdbActionType nActionType);
	
	void Stop();

	void Reset();

	int GetCount(void);

	void EnableDbKeepAlive(int nTimeout);

	void SetSystemID(const char *pSystemID);

private:
	virtual void Run();
	void Work(); 
	int DbOperation(const char *pszObjectName, CFieldDescribe *pDescirbe, 
		TTmdbActionType nAction, int nTaskNo);

	int DbTableOperation(CFieldDescribe *pDescirbe, const char *pszSQLCommand, 
		int *pKeyPosition, TTmdbActionType nActionType,bool bHasSystemID=true);
	int DbSpOperation(CFieldDescribe *pDescirbe, const char *pszKeyName, 
		TTmdbActionType nActionType);

	TTaskMethod *FindMethod(const char *pszObjectName);
	void BindParam(TMemberDesc *pMemberDesc, int nParamPosition, SACommand *pCommand);
	void BindParam(TMemberDesc *pMemberDesc, const char *pszParamName, SACommand *pSACommand);

	void SaveAction(TTmdbAction *pAction, void *pData, FILE *fp);
	void LoadAction(TTmdbAction *pAction, void *pData, FILE *fp);

	SACommand *GetSACommand(const char *pszSQL);

	void CommitActions();

	void RollbackActions();

	bool CheckDbConnection(int nErrorNativeCode);

	void DbKeepAlive();
private:
	int m_nWorkerID;
	CDbConnection *m_pDbConnection;
	SACommand *m_pSACommand;

//	CCacheList m_listTaskData;

	typedef map<const char *, TTaskMethod *, ltstr>  CTaskMethodMap;
	CTaskMethodMap m_mapTaskMethod;

	CMutex m_mutexTask;
	char *m_pWorkData;

	bool m_bShouldRun;

	ITMDBSyncChecker *m_pSyncChecker;

	int m_nCount;

	FILE *m_fpTmdbAction;
	fpos_t m_fposWrite;
	string m_strWorkFileName;

	typedef deque<TTmdbAction> CTaskQueue;
	CTaskQueue m_queueTask;

	typedef map<const char *, SACommand *> CSACommandCache;
	CSACommandCache m_cacheSACommand;

	vector<TTmdbAction> m_actionUncommitted;

	int m_nConnectTimerCount;

	int m_nActionCount;

	int m_nDbKeepAliveTimeout;
	time_t m_tLastDbActionTime;

	char m_pSystemID[5];

public:
	CTaskQueue *GetQueueTask();
};

inline int CTMDBWorker::GetCount(void)
{
	return m_nCount;
}

#endif // !defined(AFX_TMDBWORKER_H__F249E0F2_D273_402C_9AF3_FC12BA8FF048__INCLUDED_)
