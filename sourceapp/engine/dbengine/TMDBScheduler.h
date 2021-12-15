// TMDBScheduler.h: interface for the CTMDBScheduler class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TMDBSCHEDULER_H__85843A69_0BA0_45A1_99ED_79D3A9590BB7__INCLUDED_)
#define AFX_TMDBSCHEDULER_H__85843A69_0BA0_45A1_99ED_79D3A9590BB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EventHandler.h"
#include "TMDBWorker.h"
#include "Flow.h"
#include "monitorIndex.h"
#include "AccomplishFlow.h"

struct TTmdbTask
{
	int nTaskNo;
	int nActionCount;
};

class CTMDBScheduler  : public CEventHandler, public ITMDBSyncChecker
{
public:
	CTMDBScheduler(CReactor *pReactor, CAccomplishFlow *pAccomplishFlow, const char *pszWorkFilePath);
	virtual ~CTMDBScheduler();

	bool Init(const char *pszDatabaseName, const char *pszUserName, const char *pszPassword);
	void AssignTask(DWORD nTaskNo);
	void SetCommitPoint(DWORD nTaskNo);
	void Dispatch(const char *pszObjectName, CFieldDescribe *pDescirbe, 
		const void *pData, TTmdbActionType nActionType);

	virtual void OnTimer(int nIDEvent);

	virtual bool CheckTaskSync(int nTaskNo);

	void SetAccomplishCommPhaseNo(WORD wCommPhaseNo);
	CTMDBWorker *GetWorker(int nWorkerID);

	void StartAllNonSyncThread(const char *pSystemID);
	
private:
	void PrepareTaskMethod(TTaskMethod *pTaskMethod);
	CTMDBWorker *GetWorker(const char *pszObjectName);

	void RefreshCurrTaskNo();
private:
	typedef map<int, CTMDBWorker *> CWorkerMap;
	CWorkerMap m_mapWorker;
	
	typedef deque<TTmdbTask> CTaskQueue;
	CTaskQueue m_queueTask;

	typedef map<const char *, CTMDBWorker *, ltstr> CDispatchMap;
	CDispatchMap m_mapDispatch;

	int m_nCurrTaskNo;

	CAccomplishFlow *m_pAccomplishFlow;

	CIntTotalMonitorIndex *m_pCountIndex;
	CMutex m_mutexAccomplishCount;
	
	string m_strWorkFilePath;
public:
	int GetCurrTaskNo();
	//CTaskQueue *GetQueueTask(){	return &m_queueTask; };
};

inline int CTMDBScheduler::GetCurrTaskNo()
{
	return m_nCurrTaskNo; 
}

#endif // !defined(AFX_TMDBSCHEDULER_H__85843A69_0BA0_45A1_99ED_79D3A9590BB7__INCLUDED_)
