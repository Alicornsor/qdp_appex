/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file Engine.cpp
///@brief	ʵ������CEngine
///@history 
///20060118	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#include "Engine.h"
#include "XtpPackageDesc.h"
#include "public.h"

/////////////////////////////////////////////////////////////////////////
CEngine::CEngine(CConfig *pConfig, bool verbose)
	: CBaseEngine(pConfig,verbose)
{
	m_seqID=1;
}
	
CEngine::~CEngine(void)
{
}
	
void CEngine::handleMessage(CXTPPackage *pPackage)
{
	///------
	///	xuzh��20070723���ڷ�����������ʱ�����������Ϣ
	///------
// 	DWORD dwTid = pPackage->GetTid();
// 	if (dwTid==TID_ReqOrderInsert)
// 	{
// 		printTime("CEngine::handleMessage TID_ReqOrderInsert");
// 	}
// 	
// 	if (dwTid==TID_RspOrderInsert)
// 	{
// 		printTime("CEngine::handleMessage TID_RspOrderInsert");
// 	}
	

	TSessionRef sessionRef;
	sessionRef.FrontID = pPackage->GetFrontID();
	sessionRef.SessionID = pPackage->GetSessionID();
	sessionRef.RequestID = pPackage->GetRequestID();

	iterator it;

	for (it=begin();it<end();it++)
	{
		if (!(*it)->handleMessage(pPackage,sessionRef))
		{
			break;
		}
	}
/*  2015-01-30 longqy ����д��־
	else
	{
		BIZ_OPERATION_LOG0("\t(ignore by engine)");
	}
	if (pPackage->GetTid()==TID_NtfCommPhaseChange)
	{
		///�ڽ��г�ʼ��ʱ��handleInput��ֵ��������ӣ�����tseriesLen��ֵ�����㣬
		///������handleInput��ֵ����tseriesLen��ֵ�����ǲ�����ġ����ԣ�������
		///�����handleInput��ֵҲ���㡣Ҳ����˵��handleInput�Ķ��彫�����Ǳ�
		///���洦�����Ϣ���������Ǳ������ڱ��������ڴ������Ϣ�������ڵ�ǰ����£�
		///��������ν�ġ�
		m_handleInputIndex->incValue(-m_handleInputIndex->getTotalValue());
	}
	m_handleInputIndex->incValue();
	endProcess(m_seqID++);
*/
//	m_pDB->save(m_pConfig);
}

void CEngine::handleRequest(CXTPPackage *pPackage,DWORD nSessionID)
{
	TSessionRef sessionRef;
	sessionRef.FrontID = pPackage->GetFrontID();
	sessionRef.SessionID = pPackage->GetSessionID();
	iterator it;
	for (it=begin();it<end();it++)
	{
		(*it)->handleRequest(pPackage,sessionRef,nSessionID);
	}
}

void CEngine::addServiceXTPLink(IServiceXTPLink *pLink)
{
	push_back(pLink);
}

bool CEngine::removeServiceXTPLink(IServiceXTPLink *pLink)
{
	iterator it;
	for (it=begin();it<end();it++)
	{
		if (*it==pLink)
		{
			erase(it);
			return true;
		}
	}
	return false;
}

