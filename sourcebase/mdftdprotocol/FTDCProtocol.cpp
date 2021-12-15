// FTDCProtocl.cpp: implementation of the CFTDCProtocl class.
//
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "FTDCProtocol.h"
#include "FTDCPackage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFTDCProtocol::CFTDCProtocol(CReactor *pReactor)
:CProtocol(pReactor, FTDCHLEN, new CFTDCPackage(), new CFTDCPackage())
{
	m_pmapSubInstrument = NULL;
}

CFTDCProtocol::~CFTDCProtocol()
{
	Clear();
}

void CFTDCProtocol::Clear()
{
	CSubEndPointMap::iterator sitor = m_mapSubEndPoint.Begin();
	while (!sitor.IsEnd())
	{
		delete (*sitor);
		sitor++;
	}
	m_mapSubEndPoint.Clear();

	CPubEndPointMap::iterator pitor = m_mapPubEndPoint.Begin();
	while (!pitor.IsEnd())
	{
		delete (*pitor);
		pitor++;
	}
	m_mapPubEndPoint.Clear();
}

int CFTDCProtocol::Pop(CPackage *pPackage)
{
	CFTDCPackage *pFTDCPackage = (CFTDCPackage *)pPackage;
	CFTDCSubEndPoint *pSubEndPoint = GetSubEndPoint(pFTDCPackage->GetFTDCHeader()->SequenceSeries);
	if (pSubEndPoint != NULL)
	{
		return pSubEndPoint->HandlePackage(pFTDCPackage);
	}

	return CProtocol::Pop(pPackage);
}

void CFTDCProtocol::PublishSend()
{
	CPubEndPointMap::iterator pitor = m_mapPubEndPoint.Begin();
	while (!pitor.IsEnd())
	{
		(*pitor)->PublishSend();
		pitor++;
	}
}

int CFTDCProtocol::OnRecvErrorPackage(CPackage *pPackage)
{
	NotifyError(MSG_FTDCERR_BADPACKAGE, 0, this);
	return 0;
}

void CFTDCProtocol::Publish(CReadOnlyFlow *pFlow, WORD nSequenceSeries, int nStartId)
{
//	DEBUG_LOG2("nSequenceSeries=[%d], nStartId=[%d]\n",
//		nSequenceSeries, nStartId);
	CFTDCPubEndPoint *pPubEndPoint = GetPubEndPoint(nSequenceSeries);
	if (pPubEndPoint == NULL)
	{
		pPubEndPoint = new CFTDCPubEndPoint(pFlow, nSequenceSeries, nStartId, this,m_pmapSubInstrument);
		m_mapPubEndPoint.Insert(nSequenceSeries, pPubEndPoint);
	}
	pPubEndPoint->MoveTo(nStartId);
}

void CFTDCProtocol::UnPublish(WORD nSequenceSeries)
{
	CFTDCPubEndPoint *pPubEndPoint = GetPubEndPoint(nSequenceSeries);
	if (pPubEndPoint != NULL)
	{
		delete pPubEndPoint;
		m_mapPubEndPoint.Erase(nSequenceSeries);
	}
}

void CFTDCProtocol::RegisterSubscriber(CFTDCSubscriber *pSubscriber)
{
	WORD nSequenceSeries = pSubscriber->GetSequenceSeries();
	CFTDCSubEndPoint *pSubEndPoint = GetSubEndPoint(nSequenceSeries);
	if (pSubEndPoint == NULL)
	{
		pSubEndPoint = new CFTDCSubEndPoint(pSubscriber);
		m_mapSubEndPoint.Insert(nSequenceSeries, pSubEndPoint);
	}
}

void CFTDCProtocol::UnRegisterSubscriber(CFTDCSubscriber *pSubscriber)
{
	WORD nSequenceSeries = pSubscriber->GetSequenceSeries();
	CFTDCSubEndPoint *pSubEndPoint = GetSubEndPoint(nSequenceSeries);
	if (pSubEndPoint != NULL)
	{
		delete pSubEndPoint;
		m_mapSubEndPoint.Erase(nSequenceSeries);
	}
}

CFTDCSubEndPoint *CFTDCProtocol::GetSubEndPoint(WORD nSequenceSeries)
{
	CFTDCSubEndPoint **pFind = m_mapSubEndPoint.Find(nSequenceSeries);
	if (pFind != NULL)
	{
		return (*pFind);
	}
	return NULL;
}

CFTDCPubEndPoint *CFTDCProtocol::GetPubEndPoint(WORD nSequenceSeries)
{
	CFTDCPubEndPoint **pFind = m_mapPubEndPoint.Find(nSequenceSeries);
	if (pFind != NULL)
	{
		return (*pFind);
	}
	return NULL;
}

void CFTDCProtocol::SetCommPhaseNo(WORD wCommPhaseNo)
{
	CSubEndPointMap::iterator sitor = m_mapSubEndPoint.Begin();
	while (!sitor.IsEnd())
	{
		(*sitor)->SetCommPhaseNo(wCommPhaseNo);
		sitor++;
	}
}

void CFTDCProtocol::SetSubInstrumentMap(CSubInstrumentMap *pmapSubInstrument)
{
	m_pmapSubInstrument = pmapSubInstrument;
}

