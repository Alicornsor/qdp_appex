// DbmtHandler.h: interface for the CDbmtHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DFMTHANDLER_H__6F0E5A7C_8496_449A_B06F_A12822C7FFFB__INCLUDED_)
#define AFX_DFMTHANDLER_H__6F0E5A7C_8496_449A_B06F_A12822C7FFFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EventHandler.h"
#include "Flow.h"
#include "customDataType.h"
#include "XTPPackage.h"
#include "DbmtPackage.h"
#include "TBCommandFile.h"

class CDfmtHandler : public CEventHandler
{
public:
	CDfmtHandler(CReactor *pReactor, const char *pszDataFile, CFlow *pUnderFlow,int nDbmtCount);
	virtual ~CDfmtHandler();

	void SetCommPhaseNo(WORD nCommPhaseNo);
	int CheckDfCommand();
	virtual void OnTimer(int nIDEvent);
	void MySetTimer(int nElapse);

private:
	void rtrim(char *buffer);
	
private:
	CFlow *m_pUnderFlow;
	CDateType m_TradingDay;
	CDbmtPackage m_dbmtPackage;
	char m_sDataFile[FILENAMELENGTH];
	int m_nDbmtCount;
};

inline void CDfmtHandler::rtrim(char *buffer)
{
	int notSpacePos=0;
	for(int i=0;i<MAXLINELENGTH;i++)
	{
		if( *(buffer+i)=='\n')
		{
			*(buffer+i)=0;
			break;
		}
		else if ( *(buffer+i)==0 )
		{
			break;
		}
		else if ( *(buffer+i)!=' ')
		{
			notSpacePos=i;
		}

	}
	*(buffer+notSpacePos+1)=0;
	return ;
}

#endif // !defined(AFX_DFMTHANDLER_H__6F0E5A7C_8496_449A_B06F_A12822C7FFFB__INCLUDED_)
