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
	//由于对端发送的行情不是按照顺序，会根据合约的订阅情况跳号，这里不需要做号码判断。
	//由于是tcp链接,默认只要后面的报文的序号比前面的大就可以了
	//xuzh 20120511 用于合约订阅的修改
	if (pFTDCPackage->GetFTDCHeader()->SequenceNumber < m_pSubscriber->GetReceivedCount()+1)
	{	
		return -1;
	}

	m_pSubscriber->HandleMessage(pFTDCPackage);
	return 0;
}
