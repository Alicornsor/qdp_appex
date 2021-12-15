/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file Engine.cpp
///@brief	实现了类CEngine
///@history 
///20060118	xuzh		创建该文件
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
	///	xuzh，20070723：在发生紧急处理时，忽略这个消息
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
/*  2015-01-30 longqy 不再写日志
	else
	{
		BIZ_OPERATION_LOG0("\t(ignore by engine)");
	}
	if (pPackage->GetTid()==TID_NtfCommPhaseChange)
	{
		///在进行初始化时，handleInput的值会继续增加，但是tseriesLen的值会清零，
		///这就造成handleInput的值大于tseriesLen的值，这是不合理的。所以，我们在
		///这里，将handleInput的值也清零。也就是说，handleInput的定义将不再是本
		///引擎处理的消息总数，而是本引擎在本交易日内处理的消息总数。在当前情况下，
		///这是无所谓的。
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

