/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file LockFileFlow.cpp
///@brief��������CLockFileFlow
///@history 
///20130703	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#include "public.h"
#include "LockFileFlow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLockFileFlow::CLockFileFlow(const char *pszFlowName, const char *pszFlowPath,bool bReuse, int nMaxObjects, int nDataBlockSize)
:CCachedFileFlow(pszFlowName, pszFlowPath, bReuse,nMaxObjects,nDataBlockSize)
{
}

CLockFileFlow::~CLockFileFlow()
{
}

int CLockFileFlow::Append(void *pObject, int length)
{
	m_Mutex.Lock();
	CCachedFlow::Append(pObject,length);
	m_Mutex.UnLock();
	return 1;
}


