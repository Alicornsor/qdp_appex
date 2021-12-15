// FlowReader.cpp: implementation of the CFlowReader class.
//
// 2007.7.5	hwp	增加了GetNext方法，将流中的数据取到指定的缓冲区里
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "FlowReader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFlowReader::CFlowReader()
{
	m_pFlow = NULL;
	m_nCommPhaseNo = 0;
	m_nNextId = 0;	
}

CFlowReader::~CFlowReader()
{
	DetachFlow();
}

int CFlowReader::AttachFlow(CReadOnlyFlow *pFlow, int nStartId)
{
	m_pFlow = pFlow;
	m_nCommPhaseNo = pFlow->GetCommPhaseNo();	
	SetId(nStartId);
	return 0;
}

CReadOnlyFlow *CFlowReader::DetachFlow()
{
	CReadOnlyFlow *pFlow = m_pFlow;
	m_pFlow = NULL;
	return pFlow;
}

int CFlowReader::GetNext(void *pObject, int length)
{
	if(m_pFlow == NULL)
	{
		return -1;
	}

	WORD nCommPhaseNo = m_pFlow->GetCommPhaseNo();
	if (nCommPhaseNo != m_nCommPhaseNo)
	{
		SetId(0);
		m_nCommPhaseNo = nCommPhaseNo;
	}
	
	if (m_nNextId >= m_pFlow->GetCount())
	{
		return -1;
	}

	int len = m_pFlow->Get(m_nNextId, pObject, length);

	if(len >= 0)
	{
		SetId(1, FROM_HERE);
	}

	return len;
}

bool CFlowReader::GetNext(CPackage *pPackage)
{

	int len = GetNext(pPackage->Address(), pPackage->Length());

	if(len < 0)
	{
		return false;
	}

	pPackage->Truncate(len);
	pPackage->ValidPackage();

	return true;
}
//20150604 huwp 添加该函数
bool CFlowReader::GetNextUseNoBuf(CPackage *pPackage)
{
	if(m_pFlow == NULL)
	{
		return false;
	}
	
	WORD nCommPhaseNo = m_pFlow->GetCommPhaseNo();
	if (nCommPhaseNo != m_nCommPhaseNo)
	{
		SetId(0);
		m_nCommPhaseNo = nCommPhaseNo;
	}
	
	if (m_nNextId >= m_pFlow->GetCount())
	{
		return false;
	}

	void *pData = NULL;
	
	int iLen = m_pFlow->Get(m_nNextId, &pData);	
	if(iLen >= 0)
	{
		SetId(1, FROM_HERE);
	}
	else
	{
		return false;
	}
	pPackage->SetData((char *)pData, iLen);
	pPackage->ValidPackage();
	
	return true;
}
