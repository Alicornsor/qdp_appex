// AccomplishFlow.cpp: implementation of the CAccomplishFlow class.
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "AccomplishFlow.h"
#include "DbConnection.h"
#include "CDate.h"
#include "customDataType.h"
#include "BaseFunction.h"
#include "XtpData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAccomplishFlow::CAccomplishFlow()
{
	m_wCommPhaseNo = 0;
	m_nCount = 0;

	m_pDbConnection = new CDbConnection;
	m_pSACommand = new SACommand(m_pDbConnection);
	memset(m_pSystemID,0,sizeof(m_pSystemID));
}

CAccomplishFlow::~CAccomplishFlow()
{
	delete m_pSACommand;
	delete m_pDbConnection;
}

bool CAccomplishFlow::ConnectDB(const char *pszDatabaseName,const char *pszUserName, 
							const char *pszPassword)
{
	if(m_pDbConnection->ConnectDB(pszDatabaseName, pszUserName, pszPassword))
	{
		return Load();
	}
	return false;
}

int CAccomplishFlow::GetCount(void)
{
	return m_nCount;
}

const int *CAccomplishFlow::GetCountPtr(void)
{
	return &m_nCount;
}

WORD CAccomplishFlow::GetCommPhaseNo()
{
	return m_wCommPhaseNo;
}

int CAccomplishFlow::Get(int id, void *pObject, int length)
{
	RAISE_DESIGN_ERROR("no implementation\n");
	return 0;
}

void CAccomplishFlow::SetCommPhaseNo(WORD nCommPhaseNo)
{
	NET_STATUS_LOG1("SetCommPhaseNo=[%d]\n",nCommPhaseNo);
	m_wCommPhaseNo = nCommPhaseNo;
	Load();
}

void CAccomplishFlow::SetSystemID(const char *pSystemID)
{
// 	if (pSystemID !=NULL)
// 	{
// 		strncpy(m_pSystemID,pSystemID,4);
// 	}
}

bool CAccomplishFlow::Truncate(int nCount)
{
	m_nCount = nCount;
	NET_STATUS_LOG1("Truncate, m_nCount=[%d]\n",m_nCount);
//	return Save();
	return true;
}

int CAccomplishFlow::Append(void *pObject, int length)
{
	int nPos = m_nCount;
	m_nCount++;
	NET_STATUS_LOG1("Append, m_nCount=[%d]\n",m_nCount);
// 	if (!Save())
// 	{
// 		return -1;
// 	}
	return nPos;
}

bool CAccomplishFlow::Load()
{
	try {
		SACommand cmd(m_pDbConnection);
/*		cmd.setCommandText(
			"SELECT TradingDay FROM ExchangeAdmin.T_ExchangeStatus");
		cmd.Execute();
		if (!cmd.FetchNext())
		{
			return false;
		}
		m_wCommPhaseNo = (WORD)CDate::DateToLong(cmd.Field("TradingDay").asString());
		DEBUG_LOG1("get CommPhaseNo from ExchangeStatus [%d]\n",m_wCommPhaseNo);
*/
		memset(m_pSystemID,0,sizeof(m_pSystemID));
		GetSystemID(m_pDbConnection,m_pSystemID);

// 		cmd.setCommandText("SELECT SequenceNo FROM t_Oper_TmdbAccomplish WHERE CommPhaseNo=:1 AND SystemID=:2");
// 		cmd.Param(1).setAsShort() = m_wCommPhaseNo;
// 		cmd.Param(2).setAsString() = m_pSystemID;
// 		
// 		cmd.Execute();
// 		
// 		if(!cmd.FetchNext())
// 		{
// 			return Truncate(0);
// 		}
// 		m_nCount = cmd.Field("SequenceNo").asLong(); 
// 		NET_STATUS_LOG1("Load, m_nCount=[%d]\n",m_nCount);
		return Truncate(0);
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
		REPORT_EVENT(LOG_ERROR, "Database", "GetSystemID,CPN=%d, Message=%s",
			m_wCommPhaseNo,(const char*)x.ErrText());
		return false;
	}
	return true;
}

int CAccomplishFlow::GetSystemID(CDbConnection *pDbConnection,char *systemid)
{
	typedef vector<string> CIPVec;
	CIPVec IPVect;
	IPVect.clear();
	bool ret =GetIPAddress(&IPVect);
	if (!ret || IPVect.size()==0)
	{
		REPORT_EVENT(LOG_CRITICAL, "GetSystemID", "获取本机IP地址失败! ret=%d ip_size=%d",ret,IPVect.size());
		exit(-1);
	}
	
	typedef map<string,CSystemInfoField> CSystemMap;
	CSystemMap SystemMap;
	SystemMap.clear();
	CSystemInfoField SystemInfo;
	SACommand cmd(pDbConnection,"SELECT systemip,systemid,systemname FROM t_sync_systeminfo");
	cmd.Execute();
	while (cmd.FetchNext())
	{
		CDbConnection::GetRow(&cmd,(char *)&SystemInfo, &SystemInfo.m_Describe);
		SystemMap.insert(CSystemMap::value_type(SystemInfo.SystemIP.getValue(),SystemInfo));
	}
	
	if (SystemMap.size()==0)
	{
		REPORT_EVENT(LOG_CRITICAL, "GetSystemID", "从数据库获取交易中心失败!");
		exit(-1);
	}
	
	int len = IPVect.size();
	for (int i=0;i<len;i++)
	{
		for(CSystemMap::iterator pSysIter =SystemMap.begin();pSysIter!=SystemMap.end();pSysIter++)
		{
			if (strcmp(IPVect[i].c_str(),pSysIter->first.c_str())==0)
			{
				strcpy(systemid,pSysIter->second.SystemID.getValue());
				return 0;
			}
		}
	}
	REPORT_EVENT(LOG_CRITICAL, "GetSystemID", "从数据库获取匹配的交易中心失败!");
	exit(-1);
}

bool CAccomplishFlow::Save()
{
	try {
		if (!m_pDbConnection->isConnected())
		{
			m_pDbConnection->ConnectDB();
			if (!m_pDbConnection->isConnected())
			{
				REPORT_EVENT(LOG_CRITICAL, "Database", "CAccomplishFlow Connect Error");
				return false;
			}
		}
		
// 		SACommand cmd(m_pDbConnection, 
// 			"UPDATE t_Oper_TmdbAccomplish SET SequenceNo=:1 WHERE CommPhaseNo=:2 AND SystemID=:3");
// 
// 
// 		cmd.Param(1).setAsLong() = m_nCount;
// 		cmd.Param(2).setAsShort() = m_wCommPhaseNo;
// 		cmd.Param(3).setAsString() = m_pSystemID;
// 
// 		cmd.Execute();
// 		REPORT_EVENT(LOG_INFO, "ustmdb", "Save:Update, CommPhaseNo=[%d],m_nCount=[%d]",
// 			m_wCommPhaseNo, m_nCount);
// 		
// 		if(cmd.RowsAffected() != 1)
// 		{
// 			cmd.setCommandText(
// 				"INSERT INTO t_Oper_TmdbAccomplish(SequenceNo,CommPhaseNo,SystemID) VALUES(:1, :2, :3)");
// 			cmd.Param(1).setAsLong() = m_nCount;
// 			cmd.Param(2).setAsShort() = m_wCommPhaseNo;
// 			cmd.Param(3).setAsString() = m_pSystemID;
// 			cmd.Execute();
// 			REPORT_EVENT(LOG_INFO, "ustmdb", "Save:Insert, CommPhaseNo=[%d],m_nCount=[%d]",
// 				m_wCommPhaseNo, m_nCount);
// 		}
// 
// 		m_pDbConnection->Commit();

	}	
	catch(SAException &x)
	{
		try
		{
			m_pDbConnection->CheckConntectionError(x.ErrNativeCode());
			// on error rollback changes
			m_pDbConnection->Rollback();
			REPORT_EVENT(LOG_CRITICAL, "Database", "CAccomplishFlow Exception, Message=%s",
				(const char*)x.ErrText());
			
		}
		catch(SAException &)
		{
		}
		return false;
	}
	return true;
}
