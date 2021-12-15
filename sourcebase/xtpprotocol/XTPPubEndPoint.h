// XTPPubEndPoint.h: interface for the CXTPPubEndPoint class.
//
// 2006.10.20 hwp 增加发送状态日志
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XTPPUBENDPOINT_H__93E840F9_7AEE_406D_A53E_283C938D4713__INCLUDED_)
#define AFX_XTPPUBENDPOINT_H__93E840F9_7AEE_406D_A53E_283C938D4713__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Protocol.h"
#include "PublishPort.h"
#include "HashMap.h"

class CXTPPubHelper
{
public:
	virtual void SendHeartBeat(DWORD nSubjectID, WORD nCommPhaseNo, DWORD nSeqNo){};
	virtual ~CXTPPubHelper(){};
};

class CXTPPubEndPoint 
{
public:
	CXTPPubEndPoint(CReadOnlyFlow *pFlow, DWORD nSubjectID,
		CProtocol *pSendProtocol, CXTPPubHelper *pControlHelper);
	virtual ~CXTPPubEndPoint();
	void Publish(DWORD nCurrClock,int DriveFlag);
	void OnNak(DWORD dwSubscriberID, int nStartID, DWORD dwNakTime);
	void OnAck(DWORD dwSubscriberID, int nStartID, DWORD dwAckTime);
	void OnTimer(DWORD nCurrClock,int DriveFlag=0);
	inline DWORD GetSubjectID();
private:
	void CreatePublishPort(DWORD dwSubscriberID, int nStartID, DWORD dwNakTime);
	void RemovePublishPort(CPublishPort *pPublishPort);
private:
	DWORD m_nSubjectID;
	vector<CPublishPort *> m_PublishPorts;
	CReadOnlyFlow *m_pFlow;
	DWORD m_nSendHeartbeatClock;
	DWORD m_nLogClock;
	DWORD m_nLastSendClock;
	CProtocol *m_pSendProtocol; 
	CXTPPubHelper *m_pControlHelper;
	CXTPPackage m_SendPackage;
	DWORD	m_nLastRandClock;
};

inline DWORD CXTPPubEndPoint::GetSubjectID()
{
	return m_nSubjectID;
}

#endif // !defined(AFX_XTPPUBENDPOINT_H__93E840F9_7AEE_406D_A53E_283C938D4713__INCLUDED_)
