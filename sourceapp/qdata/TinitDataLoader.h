// TinitDataLoader.h: interface for the CTinitDataLoader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TINITDATALOADER_H__C3742AEF_BA36_45C1_A57D_6942C1698A39__INCLUDED_)
#define AFX_TINITDATALOADER_H__C3742AEF_BA36_45C1_A57D_6942C1698A39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Semaphore.h"
#include "Mutex.h"
#include "customDataType.h"
#include "TinitDataLoadThread.h"
#include "Reactor.h"

const int UM_TINIT_ERROR		= SM_USER+4;
const int UM_TINIT_APPEND_DATA	= SM_USER+5;
const int UM_TINIT_APPEND_END	= SM_USER+6;
	
const int MAX_DATA_LOAD_THREAD	= 1;

class CTinitDataLoader : public ITinitDataLoadAssigner
{
public:
	CTinitDataLoader(CEventHandler *pServer, const char *pszFlowPath);
	virtual ~CTinitDataLoader();
	inline void SetServer();
	bool StartLoadDay(CDateType &WorkDay,CSystemIDType SystemID);
	inline int GetErrorCode();
	inline const char *GetErrorMsg();

	virtual TTinitTableInfo *GetTinitTableInfo(TTinitInitType &nType);
	virtual void OnDataLoadEnd(CTinitDataLoadThread *pTinitDataLoadThread,
		const char *pszTableName, int nErrorCode, const char *pszErrorMsg);

	bool ConnectDB(char *pszDatabaseName, char *pszUserName, char *pszPassword);
	void Cancel();
	bool IsBusy();
private:
	void StartWorkThread(TTinitTableInfo *pTableInfo);
	void SetError(const char *pszTableName, int nErrorCode, const char *pszErrorMsg);
	void AppendData(CTinitDataLoadThread *pDataLoadThread);
private:
	CEventHandler *m_pServer;
	CDateType m_WorkDay;
	int m_nErrorCode;
	string m_strErrorMsg;

	bool m_bShouldRun;
	TTinitInitType m_nTaskType;
	TTinitTableInfo *m_pCurrTask;
	TTinitTableInfo *m_pCurrTableInfo;
	CMutex m_lock;
	int m_nTaskCount;

	CTinitDataLoadThread *m_DataLoadThreads[MAX_DATA_LOAD_THREAD];
	CSystemIDType m_SystemID;
};

inline int CTinitDataLoader::GetErrorCode()
{
	return m_nErrorCode;
}

inline const char *CTinitDataLoader::GetErrorMsg()
{
	return m_strErrorMsg.c_str();
}

#endif // !defined(AFX_TINITDATALOADER_H__C3742AEF_BA36_45C1_A57D_6942C1698A39__INCLUDED_)
