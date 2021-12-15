!!let exchangeid=""!!
!!let functionid=""!!
!!let macroid=""!!
!!let fileid=""!!
!!enter exchangeinfo!!
!!travel self!!
!!if @pumpid==0!!
!!let exchangeid=@name!!
!!elseif @pumpid==1!!
!!let functionid=@name!!
!!elseif @pumpid==2!!
!!let macroid=@name!!
!!elseif @pumpid==3!!
!!let fileid=@name!!
!!endif!!
!!next!!
!!leave!!
!!function!!
#include <set>
using namespace std;

struct ltstr
{
	bool operator()(const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) < 0;
	}
};

typedef set<char *, ltstr> CPackageSet;
CPackageSet g_setUsePackage;

bool InUse(char *name)
{
	return (g_setUsePackage.find(name)!=g_setUsePackage.end());
}

!!endfunction!!
!!enter traderapi!!
!!travel self!!	
!!command g_setUsePackage.insert(@name);!!
!!next!!
!!leave!!
/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file !!@fileid!!FtdcTraderApiImpl.cpp
///@brief 实现了客户端接口
///@history 
/////////////////////////////////////////////////////////////////////////

#include "public.h"
#include "FtdcTraderApiImpl.h"
#include "FtdPackageDesc.h"
#include "FtdcUserApiMacro.h"

CFtdcTraderApiImpl::CFtdcTraderApiImpl(const char *pszFlowPath)
{
	m_pUserApi = C!!@functionid!!FtdcUserApi::CreateFtdcUserApi(pszFlowPath, "TraderApi");
	m_pUserApi->RegisterSpi(this);
	m_pSpi = NULL;
}

void CFtdcTraderApiImpl::Init()
{
	static int nTradePrivatePort=39900;
	nTradePrivatePort++;
	m_pUserApi->Init(nTradePrivatePort);
}

int CFtdcTraderApiImpl::Join()
{
	return m_pUserApi->Join();
}

void CFtdcTraderApiImpl::Release()
{
	m_pUserApi->Release();
	m_pUserApi = NULL;
	delete this;
}

const char *CFtdcTraderApiImpl::GetTradingDay()
{
	return m_pUserApi->GetTradingDay();
}

void CFtdcTraderApiImpl::RegisterFront(char *pszFrontAddress)
{
	m_pUserApi->RegisterFront(pszFrontAddress);
}

void CFtdcTraderApiImpl::RegisterNameServer(char *pszNsAddress)
{
	m_pUserApi->RegisterNameServer(pszNsAddress);
}

void CFtdcTraderApiImpl::RegisterSpi(C!!@functionid!!FtdcTraderSpi *pSpi)
{
	m_pSpi = pSpi;
}

void CFtdcTraderApiImpl::SubscribePrivateTopic(!!@macroid!!_TE_RESUME_TYPE nResumeType)
{
	m_pUserApi->SubscribePrivateTopic(nResumeType);
}

void CFtdcTraderApiImpl::SubscribePublicTopic(!!@macroid!!_TE_RESUME_TYPE nResumeType)
{
	m_pUserApi->SubscribePublicTopic(nResumeType);
}

void CFtdcTraderApiImpl::SubscribeUserTopic(!!@macroid!!_TE_RESUME_TYPE nResumeType)
{
	m_pUserApi->SubscribeUserTopic(nResumeType);
}

void CFtdcTraderApiImpl::SetHeartbeatTimeout(unsigned int timeout)
{
	m_pUserApi->SetHeartbeatTimeout(timeout);
}
	
int CFtdcTraderApiImpl::OpenRequestLog(const char *pszReqLogFileName)
{
	return m_pUserApi->OpenRequestLog(pszReqLogFileName);
}

int CFtdcTraderApiImpl::OpenResponseLog(const char *pszRspLogFileName)
{
	return m_pUserApi->OpenResponseLog(pszRspLogFileName);
}

!!enter FTD!!
!!travel packages!!
!!let package_name=@name!!
!!if InUse(@name)!!
!!if !strncmp(@name,"Req",3)!!
///!!@comment!!
int CFtdcTraderApiImpl::!!@name!!(!!travel self!!!!if @pumpid==0!!C!!@functionid!!Ftdc!!@name!!Field *p!!@name!!!!endif!!!!next!!, int nRequestID)
{
	return m_pUserApi->!!@name!!(!!travel self!!!!if @pumpid==0!!p!!@name!!!!endif!!!!next!!, nRequestID);
}
!!endif!!
!!endif!!
!!next!!

C!!@functionid!!FtdcTraderApi *C!!@functionid!!FtdcTraderApi::CreateFtdcTraderApi(const char *pszFlowPath)
{
	return new CFtdcTraderApiImpl(pszFlowPath);
}

const char *C!!@functionid!!FtdcTraderApi::GetVersion(int &nMajorVersion, int &nMinorVersion)
{
		return INTERFACE_PRODUCT_INFO;
}

void CFtdcTraderApiImpl::OnFrontConnected()
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnFrontConnected();
	}
}

void CFtdcTraderApiImpl::OnFrontDisconnected(int nReason)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnFrontDisconnected(nReason);
	}
}
		
void CFtdcTraderApiImpl::OnHeartBeatWarning(int nTimeLapse)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnHeartBeatWarning(nTimeLapse);
	}
}

void CFtdcTraderApiImpl::OnPackageStart(int nTopicID, int nSequenceNo)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnPackageStart(nTopicID, nSequenceNo);
	}
}
	
void CFtdcTraderApiImpl::OnPackageEnd(int nTopicID, int nSequenceNo)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->OnPackageEnd(nTopicID, nSequenceNo);
	}
}

!!travel packages!!
!!if InUse(@name)!!
!!if !strncmp(@name,"Rsp",3)!!

///!!@comment!!
void CFtdcTraderApiImpl::On!!@name!!(!!travel self!!!!if @pumpid!=0!!, !!endif!!C!!@functionid!!Ftdc!!@name!!Field *p!!@name!!!!next!!, int nRequestID, bool bIsLast) 
{
	if(m_pSpi != NULL)
	{
		m_pSpi->On!!@name!!(!!travel self!!!!if @pumpid!=0!!, !!endif!!p!!@name!!!!next!!, nRequestID, bIsLast);
	}
}
!!elseif !strncmp(@name,"Rtn",3)!!

///!!@comment!!
void CFtdcTraderApiImpl::On!!@name!!(!!travel self!!!!if @pumpid!=0!!, !!endif!!C!!@functionid!!Ftdc!!@name!!Field *p!!@name!!!!next!!)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->On!!@name!!(!!travel self!!!!if @pumpid!=0!!, !!endif!!p!!@name!!!!next!!);
	}
}
!!elseif !strncmp(@name,"ErrRtn",6)!!

///!!@comment!!
void CFtdcTraderApiImpl::On!!@name!!(!!travel self!!!!if @pumpid!=0!!, !!endif!!C!!@functionid!!Ftdc!!@name!!Field *p!!@name!!!!next!!)
{
	if(m_pSpi != NULL)
	{
		m_pSpi->On!!@name!!(!!travel self!!!!if @pumpid!=0!!, !!endif!!p!!@name!!!!next!!);
	}
}
!!endif!!
!!endif!!
!!next!!


!!leave!!  
