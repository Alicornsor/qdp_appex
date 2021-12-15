// ArbProtocol.h: interface for the CArbProtocol class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __CTcpXtpProtocol_H_
#define __CTcpXtpProtocol_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Protocol.h"
#include "XTPPackage.h"
#include "ReadOnlyFlow.h"
#include "FlowReader.h"

class CTcpXtpProtocol : public CProtocol  
{
public:
	CTcpXtpProtocol(CReactor *pReactor,DWORD nSubjectID = 0);
	virtual ~CTcpXtpProtocol();
	int PublishSend();
	void  PublishFlow(CReadOnlyFlow *pFlow, int nStartId);
	void DetachFlow();
	CXTPPackage *GetNextDataPackage();
public:
	CFlowReader m_flowReader;
	CReadOnlyFlow *m_pFlow;
	CXTPPackage	m_SendPackage;
	DWORD m_nSubjectID;
};
#endif
