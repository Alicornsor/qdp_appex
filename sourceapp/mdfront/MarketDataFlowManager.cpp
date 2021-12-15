#include "public.h"
#include "MarketDataFlowManager.h"
#include "CachedFileFlow.h"
#include "CDate.h"
#include "FileFlow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMDFlowManager::CMDFlowManager(const char *pszFlowPath)
{
	m_strFlowPath = pszFlowPath;
	m_pTradingDayFlow = new CFileFlow("TradingDay", pszFlowPath, true);
	m_TradingDay = CDate::LongToDate((long)m_pTradingDayFlow->GetCommPhaseNo());	
}

CMDFlowManager::~CMDFlowManager()
{
	for(iterator itor = begin(); itor != end(); itor++)
	{
		delete (*itor).second;
	}
	delete m_pTradingDayFlow;
}

CFlow *CMDFlowManager::GetFlow(DWORD nTopicID)
{
	iterator itor = find(nTopicID);
	if (itor == end())
	{
		return NULL;
	}
	return (*itor).second;
}

bool CMDFlowManager::RegisterTopic(DWORD nTopicID)
{
	if (GetFlow(nTopicID) != NULL)
	{
		//已经注册过了
		return false;
	}

	//这里必须使用false，使用内存流，不保持到文件，因为重启之后，必须到交易所拉回行情，才能恢复合约订阅列表
//	CFlow *pFlow  = new CCachedFileFlow(nTopicID, m_strFlowPath.c_str(), false, 3000000, 0x20000);
	CFlow *pFlow  = new CCachedFlow(false, 0x7fffffff, 0x100000);

	pFlow->SetCommPhaseNo(m_pTradingDayFlow->GetCommPhaseNo());
	(*this)[nTopicID] = pFlow;
	return true;
}


const CDateType &CMDFlowManager::GetTradingDay()
{
	return m_TradingDay;
}

void CMDFlowManager::SetTradingDay(CDateType &TradingDay,CFlow *topicflow)
{
	m_pTradingDayFlow->SetCommPhaseNo(CDate::DateToLong(TradingDay));
	
// 	for(iterator itor = begin(); itor != end(); itor++)
// 	{
 	topicflow->SetCommPhaseNo(m_pTradingDayFlow->GetCommPhaseNo());
// 	}
	// 更新flow的tradingDay  lidp 20140811
	m_TradingDay = CDate::LongToDate((long)m_pTradingDayFlow->GetCommPhaseNo());
}

int CMDFlowManager::PulishToTopic(CPackage *pPackage, const CReadOnlyTopicIDType &TopicID)
{
	CFlow *pFlow = GetFlow(TopicID);
	if (pFlow == NULL)
	{
		return -1;
	}
	
	pPackage->MakePackage();
	return pFlow->Append(pPackage->Address(), pPackage->Length());
}

CChannel *CMDFlowManager::getudpchannel(){
	return uchannel;
}

void CMDFlowManager::setudpchannel(char *udpip){
	CServiceName pName(udpip);
	udpserver=new CUdpServer(&pName);
	uchannel=udpserver->AcceptPublic(0);
}

void CMDFlowManager::setmarketbuf(int ilength,char *buf){
	uchannel->Write(ilength,buf);
	return;
}

