// XTPSubEndPoint.h: interface for the CXTPSubEndPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XTPSUBENDPOINT_H__27554866_860A_4566_B4C9_674C9F0FBF02__INCLUDED_)
#define AFX_XTPSUBENDPOINT_H__27554866_860A_4566_B4C9_674C9F0FBF02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Protocol.h"
#include "Subscriber.h"
#include "OrderingQ.h"

class CXTPSubHelper
{
public:
	virtual void SendNak(DWORD nSubjectID, WORD nCommPhaseNo, DWORD dwSubscriberID,
		DWORD nSeqNo) = 0;
	virtual void SendAck(DWORD nSubjectID, WORD nCommPhaseNo, DWORD dwSubscriberID,
		DWORD nSeqNo) = 0;
	virtual ~CXTPSubHelper(){};
};

class CXTPSubEndPoint
{
public:
	CXTPSubEndPoint(CSubscriber *pSubscriber, DWORD dwSubscriberID, CXTPSubHelper *pControlHelper);
	virtual ~CXTPSubEndPoint();

	int HandlePackage(CXTPPackage *pXTPPackage, DWORD nCurrClock);
	void OnTimer(DWORD nCurrClock);
	void OnHeartBeat(WORD nCommPhaseNo, int nSeqNo, DWORD nCurrClock);
	inline DWORD GetSubjectID();
	void SetSubCommPhaseNo(WORD wCommPhaseNo);
	inline void SetAvailable(); //add by shepf Set m_available
private:
	int Delivery(CXTPPackage *pXTPPackage);
	
private:
	CSubscriber *m_pSubscriber;
	CXTPSubHelper *m_pControlHelper;
	COrderingQ m_orderingQ;
	DWORD m_nDisorderClock;
	DWORD m_nDeliveryClock;
	DWORD m_nNakInterval;
	WORD m_wSubCommPhaseNo;
	DWORD m_dwSubscriberID;
	DWORD m_dwLastAckClock;
	DWORD m_dwGroupID;
	WORD m_available;		//add by shepf 标志CXTPSubEndPoint是否可用
};

inline DWORD CXTPSubEndPoint::GetSubjectID()
{
	return m_pSubscriber->GetSubjectID();
}

//add by shepf 
inline void CXTPSubEndPoint::SetAvailable()
{
	m_available = 0;
	return ;
}

#endif // !defined(AFX_XTPSUBENDPOINT_H__27554866_860A_4566_B4C9_674C9F0FBF02__INCLUDED_)
