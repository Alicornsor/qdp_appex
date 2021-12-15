/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file ReqFlow.cpp
///@brief定义了类CReqFlow
///@history 
///20130703	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "public.h"
#include "ReqFlow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReqFlow::CReqFlow(bool bSyncFlag, int nMaxObjects, int nDataBlockSize)
:CCachedFlow(bSyncFlag, nMaxObjects, nDataBlockSize)
{
	m_bAppendFlag=true;///默认是能Append的
}

CReqFlow::~CReqFlow()
{
}

int CReqFlow::Append(void *pObject, int length)
{
	int nRet = 1;
	if(m_bAppendFlag)
	{
		nRet=CCachedFlow::Append(pObject,length);
	}	
	return nRet;
}

void CReqFlow::SetAppendFlag(bool bAppendFlag)
{
	m_bAppendFlag=bAppendFlag;
}	

bool CReqFlow::GetAppendFlag()
{
	return m_bAppendFlag;
}