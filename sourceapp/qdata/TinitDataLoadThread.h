// TinitDataLoadThread.h: interface for the CTinitDataLoadThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TINITDATALOADTHREAD_H__4DEA11C5_6BA2_46BC_B69A_2B542DB08835__INCLUDED_)
#define AFX_TINITDATALOADTHREAD_H__4DEA11C5_6BA2_46BC_B69A_2B542DB08835__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"
#include "XTPPackage.h"
#include "Flow.h"
#include "DbConnection.h"

const int MAX_TASK_COMMAND_LEN	= 1000;

struct TTinitTableInfo
{
    char *pszTable;
	CFieldDescribe *pFieldDescribe;
    char pszSQL[MAX_TASK_COMMAND_LEN];
	DWORD tid;
	int nParaNumber;
	bool bCanceled;
	bool bHasSystemID;
	char SystemID[10];
};

enum TTinitInitType
{
	TIT_TD_INIT,
	TIT_SG_INIT
};

class CTinitDataLoadThread;

class ITinitDataLoadAssigner
{
public:
	virtual TTinitTableInfo *GetTinitTableInfo(TTinitInitType &nType) = 0;
	virtual void OnDataLoadEnd(CTinitDataLoadThread *pTinitDataLoadThread,const char *pszTableName, int nErrorCode, const char *pszErrorMsg) = 0;
};

class CTinitDataLoadThread : public CThread  
{
public:
	CTinitDataLoadThread(int nDataLoadThreadID, ITinitDataLoadAssigner *pAssigner, const char *pszFlowPath);
	virtual ~CTinitDataLoadThread();

	bool ConnectDB(char *pszDatabaseName, char *pszUserName, char *pszPassword);
	inline CFlow *GetDataFlow();

	virtual void Run();
private:
	void LoadDay(TTinitTableInfo *pTableInfo);
	void FlushPackage(DWORD newtid);
	bool LoadTable(TTinitTableInfo *pTableInfo);

private:
	int m_nDataLoadThreadID;
	ITinitDataLoadAssigner *m_pAssigner;
	CXTPPackage *m_pPubMessage;
	SACommand m_saCommand;
	CFlow *m_pDataFlow;
	CDbConnection *m_pDbConnection;
	char *buf;
};

inline CFlow *CTinitDataLoadThread::GetDataFlow()
{
	return m_pDataFlow;
}

#endif // !defined(AFX_TINITDATALOADTHREAD_H__4DEA11C5_6BA2_46BC_B69A_2B542DB08835__INCLUDED_)
