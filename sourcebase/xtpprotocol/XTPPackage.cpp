// XTPPackage.cpp: implementation of the CXTPPackage class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "XTPPackage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CXTPPackage::CXTPPackage()
{
	m_XTPHeader.Chain=CHAIN_LAST;
	SetType(true);
}

CXTPPackage::~CXTPPackage()
{

}

DWORD CXTPPackage::GetActiveID()
{
	if (m_XTPHeader.Type == XTP_PUBLISH)
	{
		return m_XTPHeader.SubjectID;
	}
	return 0;
}

int CXTPPackage::ValidPackage()
{
	if(Length()<XTPHLEN)
		return -1;			//包头长度不对

	m_XTPHeader.FromStream(m_pHead);

/*	char *pData=m_pHead+XTPHLEN;
	if(m_XTPHeader.ContentLength!=Length()-XTPHLEN)
	{
		DEBUG_LOG3("Tid=%08x,Length()-XTPHLEN=%d m_XTPHeader.ContentLength=%d\n",
			m_XTPHeader.Tid, Length(), m_XTPHeader.ContentLength);
		return -2;			//包体长度与包头不符
	}*/


	Pop(XTPHLEN);

	Truncate(m_XTPHeader.ContentLength);

	return m_XTPHeader.ContentLength+XTPHLEN;
}

int CXTPPackage::MakePackage()
{
	m_XTPHeader.ContentLength = Length();
	char *pBuffer = Push(XTPHLEN);
	if (pBuffer == NULL) 
	{
		return -1;
	}
	m_XTPHeader.ToStream(pBuffer);
//	DEBUG_LOG0("CXTPPackage::MakePackage End\n");
	return 0;
}
//20150604 huwp 添加该函数
int CXTPPackage::MakeNoBufPackage()
{
	m_XTPHeader.ContentLength = Length();
	 m_pHead-=XTPHLEN;
	char *pBuffer = m_pHead;
	if (pBuffer == NULL) 
	{
		return -1;
	}
	m_XTPHeader.ToStream(pBuffer);
	return 0;
}
void CXTPPackage::PrepareRequest(DWORD tid, BYTE chain)
{
	AllocateMax();
	Truncate(0);
	memset(&m_XTPHeader, 0, sizeof(TXTPHeader));
	m_XTPHeader.Tid = tid;
	m_XTPHeader.Chain = chain;
	m_XTPHeader.Type = XTP_REQUEST;
}


void CXTPPackage::PrepareResponse(CXTPPackage *pRequest, DWORD tid, BYTE chain)
{
	AllocateMax();
	Truncate(0);
	TXTPHeader *pReqHeader = pRequest->GetXTPHeader();
	m_XTPHeader.Type = XTP_RESPONSE;
	m_XTPHeader.Chain = chain;
	m_XTPHeader.ContentLength = 0;
	m_XTPHeader.SubjectID = 0;
	m_XTPHeader.Tid = tid;
	m_XTPHeader.CommPhaseNo = 0;
	m_XTPHeader.SequenceNo = 0;
	m_XTPHeader.RequestID = pReqHeader->RequestID;
	m_XTPHeader.SessionID = pReqHeader->SessionID;
	m_XTPHeader.FrontID = pReqHeader->FrontID;
}
	
void CXTPPackage::PreparePublish(DWORD tid, BYTE chain)
{
	AllocateMax();
	Truncate(0);
	memset(&m_XTPHeader, 0, sizeof(TXTPHeader));
	m_XTPHeader.Tid = tid;
	m_XTPHeader.Chain = chain;
	m_XTPHeader.Type = XTP_PUBLISH;
	
}

CXTPPackage *CXTPPackage::CreatePackage(int nHeaderReserve)
{
	CXTPPackage *pPackage = new CXTPPackage;
	pPackage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE, nHeaderReserve);
	return pPackage;
}

void CXTPPackage::OutputHeader(CLogger *pLogger)
{
	TXTPHeader *pHeader = GetXTPHeader();
	pLogger->output(LL_DEBUG, "\tXTP PACKAGE HEADER\n");
	pLogger->output(LL_DEBUG, "\tType[0X%02X],Chain[0X%02X],ContentLength[%d],",
		pHeader->Type&0xFF, pHeader->Chain&0xFF, pHeader->ContentLength&0xFFFF);
	pLogger->output(LL_DEBUG, "SubjectID[0X%08X],Tid[0X%08X]\n",
		pHeader->SubjectID, pHeader->Tid);
	pLogger->output(LL_DEBUG, "\tCommPhaseNo[%d],SequenceNo[%d],RequestID[%d]",
		pHeader->CommPhaseNo, pHeader->SequenceNo, pHeader->RequestID);
	pLogger->output(LL_DEBUG, "SessionID[%d],FrontID[%d]\n",
		pHeader->SessionID, pHeader->FrontID);	
}

