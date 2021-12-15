// FTDCPackage.cpp: implementation of the CFTDCPackage class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "FTDCPackage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CFTDCPackage::CFTDCPackage()
{
	m_FTDCHeader.Version = 0;
	m_FTDCHeader.Chain = FTDC_CHAIN_LAST;
	SetType(true);
}

CFTDCPackage::~CFTDCPackage()
{

}

DWORD CFTDCPackage::GetActiveID()
{
	return m_FTDCHeader.SequenceSeries;
}

int CFTDCPackage::ValidPackage()
{
	if(Length() < FTDCHLEN)
		return -1;			//包头长度不对

	m_FTDCHeader.FromStream(m_pHead);

	char *pData=m_pHead+FTDCHLEN;
	if(m_FTDCHeader.FTDCContentLength != Length()-FTDCHLEN)
	{
		NET_EXCEPTION_LOG3("FTDPackage Length Inconsistent: TransactionId=%08x,Length()-FTDCHLEN=%d m_FTDCHeader.ContentLength=%d\n",
			m_FTDCHeader.TransactionId, Length(), m_FTDCHeader.FTDCContentLength);
		return -2;			//包体长度与包头不符
	}

	Pop(FTDCHLEN);

	return m_FTDCHeader.FTDCContentLength+FTDCHLEN;
}

int CFTDCPackage::MakePackage()
{
	m_FTDCHeader.FTDCContentLength = Length();
	m_FTDCHeader.FieldCount = 0;
	
	CFieldTypeIterator itor = GetFieldTypeIterator();
	while (!itor.IsEnd())
	{
		m_FTDCHeader.FieldCount++;
		itor.Next();
	}
	
	char *pBuffer = Push(FTDCHLEN);
	if (pBuffer == NULL) 
	{
		return -1;
	}
	m_FTDCHeader.ToStream(pBuffer);
//	DEBUG_LOG0("CFTDCPackage::MakePackage End\n");
	return 0;
}

void CFTDCPackage::PreparePackage(DWORD tid, BYTE chain, BYTE version)
{
	AllocateMax();
	Truncate(0);
	memset(&m_FTDCHeader, 0, sizeof(TFTDCHeader));
	m_FTDCHeader.Chain = chain;
	m_FTDCHeader.TransactionId = tid;
	m_FTDCHeader.Version = version;
}

void CFTDCPackage::PrepareResponse(CFTDCPackage *pRequest, DWORD tid, BYTE chain, 
								   BYTE version)
{
	PreparePackage(tid, chain, version);
	SetRequestId(pRequest->GetRequestId());
}

CFTDCPackage *CFTDCPackage::CreatePackage(int nHeaderReserve)
{
	CFTDCPackage *pPackage = new CFTDCPackage;
	pPackage->ConstructAllocate(FTDC_PACKAGE_MAX_SIZE, nHeaderReserve);
	return pPackage;
}

void CFTDCPackage::OutputHeader(CLogger *pLogger)
{
	TFTDCHeader *pHeader = GetFTDCHeader();
	pLogger->output(LL_DEBUG, "\tFTDC PACKAGE HEADER\n");
	pLogger->output(LL_DEBUG, "\tVersion[0X%02X],Chain[0X%02X],SequenceSeries[%d],",
		pHeader->Version&0xFF, pHeader->Chain&0xFF, pHeader->SequenceSeries&0xFFFF);
	pLogger->output(LL_DEBUG, "TransactionId[0X%08X],SequenceNumber[%d]\n",
		pHeader->TransactionId, pHeader->SequenceNumber);
	pLogger->output(LL_DEBUG, "\tFieldCount[%d],FTDCContentLength[%d],RequestId[%d]\n",
		pHeader->FieldCount, pHeader->FTDCContentLength, pHeader->RequestId);	
}
