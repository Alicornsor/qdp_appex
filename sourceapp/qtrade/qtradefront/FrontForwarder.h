// FrontForwarder.h: interface for the CFrontForwarder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRONTFORWARDER_H__3283F1B3_BEAE_4777_8D3D_100DC58ACB14__INCLUDED_)
#define AFX_FRONTFORWARDER_H__3283F1B3_BEAE_4777_8D3D_100DC58ACB14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FibClientApi.h"
#include "Flow.h"

class CFrontForwarder  
{
public:
	CFrontForwarder(DWORD nFrontID, CFlow *pPublishFlow,
		DWORD nQueryServerID, CFibClientApi *pFibClientApi);
	virtual ~CFrontForwarder();

	void PrepareForward(CXTPPackage *pXTPPackage,DWORD tid, DWORD nSessionID, DWORD nRequestID);
	void ForwardTransaction(CXTPPackage *pXTPPackage);
	int ForwardQuery(CXTPPackage *pXTPPackage);
	void SetCommPhaseNo(WORD nCommPhaseNo);
	inline DWORD GetFrontID();
private:
	DWORD m_nFrontID;
	CFlow *m_pPublishFlow;
	DWORD m_nQueryServerID;
	CFibClientApi *m_pFibClientApi;	
};

inline DWORD CFrontForwarder::GetFrontID()
{
	return m_nFrontID;
}

#endif // !defined(AFX_FRONTFORWARDER_H__3283F1B3_BEAE_4777_8D3D_100DC58ACB14__INCLUDED_)
