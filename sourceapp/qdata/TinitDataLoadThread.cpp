// TinitDataLoadThread.cpp: implementation of the CTinitDataLoadThread class.
//
// 20070828 王维 调整日志的级别和分类
// 20081118 王维 NT-0054:增加SACommand预取参数，提高性能
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "TinitDataLoadThread.h"
#include "FileFlow.h"
#include "customDataType.h"

const int RECORD_MAX_SIZE =	5000;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTinitDataLoadThread::CTinitDataLoadThread(int nDataLoadThreadID,ITinitDataLoadAssigner *pAssigner,const char *pszFlowPath)
{
	m_nDataLoadThreadID = nDataLoadThreadID;
	m_pAssigner = pAssigner;
	m_pDataFlow = new CFileFlow(nDataLoadThreadID, pszFlowPath, false);
	m_pDbConnection = new CDbConnection();
	m_saCommand.setConnection(m_pDbConnection);
	m_saCommand.setOption("PreFetchRows") = "1000";
	m_pPubMessage = CXTPPackage::CreatePackage(XTPHLEN);
	buf = new char[RECORD_MAX_SIZE];
}

CTinitDataLoadThread::~CTinitDataLoadThread()
{
	delete m_pPubMessage;
	delete m_pDataFlow;
	delete m_pDbConnection;
}

void CTinitDataLoadThread::Run()
{
	TTinitTableInfo *pTableInfo = NULL;
	TTinitInitType nType = TIT_TD_INIT;
	while((pTableInfo = m_pAssigner->GetTinitTableInfo(nType)) != NULL)
	{
		if (pTableInfo->bCanceled)
		{
			m_pAssigner->OnDataLoadEnd(this, pTableInfo->pszTable, -10, "Canceled");
			continue;
		}
		m_pDataFlow->Truncate(0);
		if (nType == TIT_TD_INIT)
		{
			LoadDay(pTableInfo);
		}
	}
}

void CTinitDataLoadThread::LoadDay(TTinitTableInfo *pTableInfo)
{
	try 
	{
		REPORT_EVENT(LOG_CRITICAL, "SystemInit", "Load %s ......", pTableInfo->pszTable);
		REPORT_EVENT(LOG_DEBUG, "SQLInit", "%s SQL: %s......", pTableInfo->pszTable,pTableInfo->pszSQL);
		m_saCommand.setCommandText(pTableInfo->pszSQL);
		if (pTableInfo->bHasSystemID)
		{
			m_saCommand.Param(1).setAsString() = pTableInfo->SystemID;
		}
		
		//执行SQL命令
		m_saCommand.Execute();
		
		//xuzh 20150817 mysql 下面执行貌似有一点问题哦，就除去了
		//m_pDbConnection->Commit();
		
		//将结果放入文件中
		if(!LoadTable(pTableInfo))
		{
			m_pAssigner->OnDataLoadEnd(this, pTableInfo->pszTable,-1, "LoadTable error");
			return;
		}
		m_pAssigner->OnDataLoadEnd(this, pTableInfo->pszTable, 0, "OK");
	}	
	catch(SAException &x)
	{
		try
		{
			m_pDbConnection->CheckConntectionError(x.ErrNativeCode());
			// on error rollback changes
			m_pDbConnection->Rollback();
		}
		catch(SAException &)
		{
		}
		m_pAssigner->OnDataLoadEnd(this, pTableInfo->pszTable,-2, (const char*)x.ErrText());
	}
}
	
void CTinitDataLoadThread::FlushPackage(DWORD newtid)
{
	if (m_pPubMessage->Length() > 0)
	{
		m_pPubMessage->SetSubjectID(0);
		m_pPubMessage->MakePackage();
		m_pDataFlow->Append(m_pPubMessage->Address(), m_pPubMessage->Length());
	}
	m_pPubMessage->PreparePublish(newtid);
}

bool CTinitDataLoadThread::LoadTable(TTinitTableInfo *pTableInfo)
{
	FlushPackage(pTableInfo->tid);

	while(!pTableInfo->bCanceled)
	{
		bool ret = m_saCommand.FetchNext();
		if (!ret)
		{
			break;
		}
		memset(buf,0,RECORD_MAX_SIZE);
		ret = CDbConnection::GetRow(&m_saCommand, buf, pTableInfo->pFieldDescribe);
		if (ret)
		{
			while(m_pPubMessage->AddField(pTableInfo->pFieldDescribe, buf) < 0)
			{
				FlushPackage(pTableInfo->tid);
			}
		}
	}
	
	FlushPackage(pTableInfo->tid);	
//	delete buf;	
	return true;
}

bool CTinitDataLoadThread::ConnectDB(char *pszDatabaseName, char *pszUserName, char *pszPassword)
{
	return m_pDbConnection->ConnectDB(pszDatabaseName, pszUserName, pszPassword);
}
