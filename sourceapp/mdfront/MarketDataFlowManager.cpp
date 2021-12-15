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
		//�Ѿ�ע�����
		return false;
	}

	//�������ʹ��false��ʹ���ڴ����������ֵ��ļ�����Ϊ����֮�󣬱��뵽�������������飬���ָܻ���Լ�����б�
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
	// ����flow��tradingDay  lidp 20140811
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

