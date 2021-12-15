// FTDCPubEndPoint.cpp: implementation of the CFTDCPubEndPoint class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "FTDCPubEndPoint.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFTDCPubEndPoint::CFTDCPubEndPoint(CReadOnlyFlow *pFlow, WORD nSequenceSeries, int nStartId,
								 CProtocol *pSendProtocol)
{
	m_pFlow = pFlow;
	m_nSequenceSeries = nSequenceSeries;
	m_pSendProtocol = pSendProtocol;
    //by caojl 20140409 解决合约订阅超过113程序崩溃缺陷   API需要重新编译
	m_SendPackage.ConstructAllocate(FTDC_PACKAGE_MAX_SIZE+FTDCHLEN, 1000);
	m_flowReader.AttachFlow(pFlow, nStartId);
}

CFTDCPubEndPoint::~CFTDCPubEndPoint()
{
}

CPackage *CFTDCPubEndPoint::GetNextDataPackage()
{
	m_SendPackage.AllocateMax();
	if(m_flowReader.GetNext(&m_SendPackage))
	{
		TFTDCHeader  *pHeader = m_SendPackage.GetFTDCHeader();
		pHeader->SequenceNumber = m_flowReader.GetId();
		pHeader->SequenceSeries = m_nSequenceSeries;
		return &m_SendPackage;
	}
	return NULL;
}

int CFTDCPubEndPoint::PublishSend()
{
	int nCount = 0;
	for(; nCount<40; nCount++)
	{
		CPackage *pPackage = GetNextDataPackage();	
		if (pPackage == NULL)
		{
			break;
		}
		if (m_pSendProtocol->Send(pPackage) != 0)
		{
			break;
		}			
	}
	return nCount;
}

void CFTDCPubEndPoint::MoveTo(int nOffset)
{
	if (m_flowReader.GetId() == nOffset)
	{
		return;
	}
	m_flowReader.SetId(nOffset);
}
