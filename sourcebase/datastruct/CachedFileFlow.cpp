// CachedFileFlow.cpp: implementation of the CCachedFileFlow class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "CachedFileFlow.h"
#include "FileFlow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCachedFileFlow::CCachedFileFlow(const char *pszFlowName, const char *pszFlowPath, 
								 bool bReuse, int nMaxObjects, int nDataBlockSize)
:CCachedFlow(true, nMaxObjects, nDataBlockSize)
{
	m_pUnderFlow = new CFileFlow(pszFlowName, pszFlowPath, bReuse);
	CCachedFlow::AttachUnderFlow(m_pUnderFlow);
}

CCachedFileFlow::CCachedFileFlow(int nFlowID, const char *pszFlowPath, 
								 bool bReuse, int nMaxObjects, int nDataBlockSize)
:CCachedFlow(true, nMaxObjects, nDataBlockSize)
{
	m_pUnderFlow = new CFileFlow(nFlowID, pszFlowPath, bReuse);
	CCachedFlow::AttachUnderFlow(m_pUnderFlow);
}

CCachedFileFlow::~CCachedFileFlow()
{
	delete m_pUnderFlow;
	m_pUnderFlow = NULL;
}

int CCachedFileFlow::AttachUnderFlow(CFlow *pFlow)
{
	RAISE_DESIGN_ERROR("CCachedFileFlow can't attach under flow");
	return -1;
}

void CCachedFileFlow::FlushToDisk(void )
{
	// ע������Ͳ������һ��Ҫ���ļ���
	//(CFileFlow *)m_pUnderFlow->FlushToDisk();
	CFileFlow * pFileflow = (CFileFlow *)m_pUnderFlow ;
	pFileflow->FlushToDisk();
}
