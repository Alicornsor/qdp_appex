/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file ReqFlow.cpp
///@brief��������CReqFlow
///@history 
///20130703	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#include "public.h"
#include "ReqFlow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReqFlow::CReqFlow(bool bSyncFlag, int nMaxObjects, int nDataBlockSize)
:CCachedFlow(bSyncFlag, nMaxObjects, nDataBlockSize)
{
	m_bAppendFlag=true;///Ĭ������Append��
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