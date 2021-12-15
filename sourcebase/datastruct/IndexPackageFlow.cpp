// IndexPackageFlow.cpp: implementation of the CIndexPackageFlow class.
//
// 20070905 hwp 增加了GetPackageIndex方法
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "IndexPackageFlow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIndexPackageFlow::CIndexPackageFlow()
{
	m_pUnderFlow = NULL;
	m_nCommPhaseNo = 0;
}

CIndexPackageFlow::~CIndexPackageFlow()
{

}

int CIndexPackageFlow::GetCount(void)
{
	return m_PackageIndex.size();
}
	
int CIndexPackageFlow::Append(int nIndex)
{
	m_PackageIndex.push_back(nIndex);
	return m_PackageIndex.size()-1;
}
	
int CIndexPackageFlow::Get(int id, void *pObject, int length)
{
	return m_pUnderFlow->Get(m_PackageIndex[id], pObject,length);
}

void CIndexPackageFlow::AttachUnderFlow(CReadOnlyFlow *pFlow)
{
	m_pUnderFlow = pFlow;
	m_nCommPhaseNo = pFlow->GetCommPhaseNo();
}

CReadOnlyFlow *CIndexPackageFlow::DeatchUnderFlow()
{
	CReadOnlyFlow *pFlow = m_pUnderFlow;
	m_pUnderFlow = NULL;
	return pFlow;
}
	
WORD CIndexPackageFlow::GetCommPhaseNo()
{
	return m_nCommPhaseNo;
}
	
void CIndexPackageFlow::SetCommPhaseNo(WORD nCommPhaseNo)
{
	if (m_nCommPhaseNo != nCommPhaseNo)
	{
		m_PackageIndex.clear();
		m_nCommPhaseNo = nCommPhaseNo;
	}
}

bool CIndexPackageFlow::Truncate(int nCount)
{
	if (nCount <= GetCount())
	{
		return true;
	}
	m_PackageIndex.resize(nCount);
	return true;
}

int CIndexPackageFlow::GetPackageIndex(int id)
{
	return m_PackageIndex[id];
}
