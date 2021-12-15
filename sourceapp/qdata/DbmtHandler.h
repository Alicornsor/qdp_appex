// DbmtHandler.h: interface for the CDbmtHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBMTHANDLER_H__6F0E5A7C_8496_449A_B06F_A12822C7FFFB__INCLUDED_)
#define AFX_DBMTHANDLER_H__6F0E5A7C_8496_449A_B06F_A12822C7FFFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EventHandler.h"
#include "DbConnection.h"
#include "Flow.h"
#include "customDataType.h"
#include "XTPPackage.h"
#include "DbmtPackage.h"

class CDbmtHandler : public CEventHandler
{
public:
	CDbmtHandler(CReactor *pReactor, CDbConnection *pDbConnection,CFlow *pUnderFlow,int nCommandNo);
	virtual ~CDbmtHandler();

	inline CFlow *GetDbmtFlow();
	void SetCommPhaseNo(WORD nCommPhaseNo);
	int CheckDbCommand();
	virtual void OnTimer(int nIDEvent);
	void MySetTimer(int nElapse);
	void SetSystemID(char* pSystemID);
private:
	int LoadDbCommand();
private:
	CDbConnection *m_pDbConnection;
	CFlow *m_pUnderFlow;
	SACommand m_saCommand;
	CDateType m_TradingDay;
	CDbmtPackage m_dbmtPackage;
	int m_nDbmtCount;
	char m_pSystemID[5];
};

#endif // !defined(AFX_DBMTHANDLER_H__6F0E5A7C_8496_449A_B06F_A12822C7FFFB__INCLUDED_)
