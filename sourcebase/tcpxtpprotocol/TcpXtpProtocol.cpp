// ArbProtocol.cpp: implementation of the CArbProtocol class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "TcpXtpProtocol.h"

CTcpXtpProtocol::CTcpXtpProtocol(CReactor *pReactor,DWORD nSubjectID)
:CProtocol(pReactor, XTPHLEN, new CXTPPackage(), new CXTPPackage())
{
	m_pFlow=NULL;
	m_SendPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN, 1000);
	m_nSubjectID = nSubjectID;
}

CTcpXtpProtocol::~CTcpXtpProtocol()
{
}

CXTPPackage *CTcpXtpProtocol::GetNextDataPackage()
{
	m_SendPackage.AllocateMax();
	if(m_flowReader.GetNext(&m_SendPackage))
	{
		TXTPHeader  *pHeader = m_SendPackage.GetXTPHeader();
		pHeader->SequenceNo = m_flowReader.GetId();
		pHeader->SubjectID = m_nSubjectID;
		//pHeader->SequenceSeries = m_nSequenceSeries;
		return &m_SendPackage;
	}
	return NULL;
}

int CTcpXtpProtocol::PublishSend()
{
	int nCount = 0;
	for(; nCount<40; nCount++)
	{
		CXTPPackage *pPackage = GetNextDataPackage();
		if (pPackage == NULL)
		{
			break;
		}
		if (Send(pPackage) != 0)
		{
			break;
		}			
	}
	return nCount;
}

void  CTcpXtpProtocol::PublishFlow(CReadOnlyFlow *pFlow, int nStartId)
{
	m_pFlow=pFlow;
	m_flowReader.AttachFlow(m_pFlow,nStartId);
}

void CTcpXtpProtocol::DetachFlow()
{
	m_flowReader.DetachFlow();
}
