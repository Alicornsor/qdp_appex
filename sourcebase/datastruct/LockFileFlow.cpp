/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file LockFileFlow.cpp
///@brief定义了类CLockFileFlow
///@history 
///20130703	hwp		创建该文件
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


