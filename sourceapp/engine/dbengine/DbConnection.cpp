// DbConnection.cpp: implementation of the CDbConnection class.
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "DbConnection.h"

#define REPORT_ERROR printf
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDbConnection::CDbConnection()
{

}

CDbConnection::~CDbConnection()
{

}

bool CDbConnection::ConnectDB(const char *pszDatabaseName, const char *pszUserName, const char *pszPassword, int iDatabaseType)
{
	m_strDatabaseName = pszDatabaseName;
	m_strUserName = pszUserName;
	m_strPassword = pszPassword;
	m_iDatabaseType = iDatabaseType;
	return ConnectDB();
}

bool CDbConnection::ConnectDB()
{
	try 
	{
		switch(m_iDatabaseType)
		{
		case 1://sybase
			Connect(m_strDatabaseName.c_str(), m_strUserName.c_str(), m_strPassword.c_str(), SA_Sybase_Client);
			setAutoCommit(SA_AutoCommitOff);
			break;
		default://mysql
			//mysql需要设置编码
			setOption("CharacterSet")="gbk";
			//建立数据库连接
			Connect(m_strDatabaseName.c_str(), m_strUserName.c_str(), m_strPassword.c_str(), SA_MySQL_Client);
			setAutoCommit(SA_AutoCommitOff);
			break;
		}
	}	
	catch(SAException &x)
	{
		REPORT_EVENT(LOG_CRITICAL, "Database", "Connect Database Error, errorid=%d, msg=%s",
			x.ErrNativeCode(),(const char*)x.ErrText());
		try
		{
			CheckConntectionError(x.ErrNativeCode());
			Rollback();
		}
		catch(SAException &)
		{
		}
		return false;
	}
	return true;
}

void CDbConnection::CheckConntectionError(int nErrorNativeCode)
{
	const int ORACLE_CONNECTION_ERROR_CODE[]=
	{
		0, 12500, 1034, 3113, 3114, 12571, 1033, 1012, 28, 3135
	};
	for (int i=0; i<sizeof(ORACLE_CONNECTION_ERROR_CODE)/sizeof(int); i++)
	{
		if (nErrorNativeCode == ORACLE_CONNECTION_ERROR_CODE[i])

		{
			Disconnect();
			break;
		}
	}
}

void CDbConnection::KeepAlive()
{
	SACommand cmd(this, "select * from t_sync_systemstatus");
	try 
	{
		cmd.Execute();
		while(cmd.FetchNext());
	}	
	catch(SAException &x)
	{
		REPORT_EVENT(LOG_CRITICAL, "Database", "KeepAlive Error, errorid=%d, msg=%s",
			x.ErrNativeCode(),(const char*)x.ErrText());
		try
		{
			CheckConntectionError(x.ErrNativeCode());
			Rollback();
		}
		catch(SAException &)
		{
		}
	}
}

bool CDbConnection::GetRow(SACommand *pCommand, char *buf, CFieldDescribe *pFieldDescribe)
{
	for (int i=0; i<pFieldDescribe->GetMemberCount(); i++)
	{		
		TMemberDesc *pMemberDesc=pFieldDescribe->GetMemberDesc(i);
		char *pMember = buf+pMemberDesc->nStructOffset;
		//		printf("%d %s\n", pMemberDesc->nType, pMemberDesc->szName);
		switch(pMemberDesc->nType)
		{
		case FT_WORD:
			*((WORD *)pMember) = pCommand->Field(pMemberDesc->szName).asShort();
			break;
		case FT_DWORD:			
			*((DWORD *)pMember) = pCommand->Field(pMemberDesc->szName).asLong();
			break;
		case FT_BYTE:
			if (pCommand->Field(pMemberDesc->szName).DataType() == SA_dtDateTime)
			{
				//printf("pMemberDesc->szName=%s is datetype",pMemberDesc->szName);
				SADateTime dt = pCommand->Field(pMemberDesc->szName).asDateTime();
				sprintf(pMember, "%04d%02d%02d", dt.GetYear(), dt.GetMonth(), dt.GetDay());
			}
			else
			{
				strncpy(pMember, (const char *)(pCommand->Field(pMemberDesc->szName).asString()), pMemberDesc->nSize);
			}
			
			if (pMemberDesc->nSize != 1)
			{
				pMember[pMemberDesc->nSize-1] = '\0';
				char *p = pMember + strlen(pMember);
				while(p > pMember)
				{
					p--;
					if (*p != ' ')
					{
						break;
					}
					*p = '\0';
				}
			}
			break;
		case FT_REAL4:
			*((REAL4 *)pMember) = pCommand->Field(pMemberDesc->szName).asDouble();
			break;
		case FT_REAL8:
			if (pCommand->Field(pMemberDesc->szName).isNull())
			{
				*((REAL8 *)pMember) = DOUBLE_NaN;
			}
			else
			{
				*((REAL8 *)pMember) = pCommand->Field(pMemberDesc->szName).asDouble();
			}
			break;
		}		
	}
	
	return true;
}
