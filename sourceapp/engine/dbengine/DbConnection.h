// DbConnection.h: interface for the CDbConnection class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBCONNECTION_H__649DF011_DFAE_47DE_BD82_B00B6005B4CE__INCLUDED_)
#define AFX_DBCONNECTION_H__649DF011_DFAE_47DE_BD82_B00B6005B4CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SQLAPI.h"
#include "FieldDescribe.h"

class CDbConnection : public SAConnection 
{
public:
	CDbConnection();
	virtual ~CDbConnection();
	bool ConnectDB(const char *pszDatabaseName, const char *pszUserName, const char *pszPassword, int iDatabaseType=0);
	void CheckConntectionError(int nErrorNativeCode);
	bool ConnectDB();
	void KeepAlive();

	static bool GetRow(SACommand *pCommand, char *buf, CFieldDescribe *pFieldDescribe);
private:

private:
	string m_strDatabaseName;
	string m_strUserName;
	string m_strPassword;
	int m_iDatabaseType;
};

#endif // !defined(AFX_DBCONNECTION_H__649DF011_DFAE_47DE_BD82_B00B6005B4CE__INCLUDED_)
