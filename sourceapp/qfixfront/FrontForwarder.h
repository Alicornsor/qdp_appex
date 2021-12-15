// FrontForwarder.h: interface for the CFrontForwarder class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _FRONTFORWARDER_H__
#define _FRONTFORWARDER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FibClientApi.h"
#include "Flow.h"
#include "XTPPackage.h"

class CFrontForwarder
{
public:
	CFrontForwarder(DWORD nFrontID, DWORD nQueryServerID, CFibClientApi *pFibClientApi);
	virtual ~CFrontForwarder();

	void PrepareForward(CXTPPackage *pXTPPackage, DWORD tid, DWORD nSessionID, DWORD nRequestID);
	void ForwardTransaction(CXTPPackage *pXTPPackage);
	int ForwardQuery(CXTPPackage *pXTPPackage);
	void SetCommPhaseNo(WORD nCommPhaseNo);
	inline DWORD GetFrontID();
private:
	DWORD m_nFrontID;
	DWORD m_nQueryServerID;
	CFibClientApi *m_pFibClientApi;
};

inline DWORD CFrontForwarder::GetFrontID()
{
	return m_nFrontID;
}
#endif
