// FTDCSubEndPoint.h: interface for the CFTDCSubEndPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTDCSUBENDPOINT_H__27554866_860A_4566_B4C9_674C9F0FBF02__INCLUDED_)
#define AFX_FTDCSUBENDPOINT_H__27554866_860A_4566_B4C9_674C9F0FBF02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Protocol.h"
#include "FTDCSubscriber.h"

class CFTDCSubEndPoint
{
public:
	CFTDCSubEndPoint(CFTDCSubscriber *pSubscriber);
	virtual ~CFTDCSubEndPoint();

	int HandlePackage(CFTDCPackage *pFTDCPackage);
	inline WORD GetSequenceSeries();
	inline void SetCommPhaseNo(WORD wCommPhaseNo);
private:
	CFTDCSubscriber *m_pSubscriber;
};

inline WORD CFTDCSubEndPoint::GetSequenceSeries()
{
	return m_pSubscriber->GetSequenceSeries();
}

inline void CFTDCSubEndPoint::SetCommPhaseNo(WORD wCommPhaseNo)
{
	m_pSubscriber->SetCommPhaseNo(wCommPhaseNo);
}

#endif // !defined(AFX_FTDCSUBENDPOINT_H__27554866_860A_4566_B4C9_674C9F0FBF02__INCLUDED_)
