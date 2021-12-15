// FTDCSubEndPoint.cpp: implementation of the CFTDCSubEndPoint class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "FTDCSubEndPoint.h"
#include "FTDCPackage.h"

const DWORD NAK_TIMEOUT	= 100;			//每一次NAK在NAK_TIMEOUT毫秒后发出，以后超时加倍
const DWORD RECV_HEARTBEAT_TIMEOUT	= 2000;	//接收心跳超时时间，单位为毫秒

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFTDCSubEndPoint::CFTDCSubEndPoint(CFTDCSubscriber *pSubscriber)
{
	m_pSubscriber = pSubscriber;
}

CFTDCSubEndPoint::~CFTDCSubEndPoint()
{

}

int CFTDCSubEndPoint::HandlePackage(CFTDCPackage *pFTDCPackage)
{
	if (pFTDCPackage->GetFTDCHeader()->SequenceNumber != m_pSubscriber->GetReceivedCount()+1)
	{	
		return -1;
	}

	m_pSubscriber->HandleMessage(pFTDCPackage);
	return 0;
}
