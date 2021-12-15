// mdusertest.cpp : 
//一个简单的例子，介绍CFfexFtdcMduserApi和CFfexFtdcMduserSpi接口的使用。

#include "MarketDataHandler.h"
#include "UFCopy.h"
#include "XtpPackageDesc.h"

//在行情UDP报文广播中，由于没有使用协议栈，只保留XTP报文，故将包头设置为40(XTP报文头大小为36)
//可以一次发送更多的合约行情
//#define MDXTP_PACKAGE_MAX_SIZE 2240

CMarketDataHandler::CMarketDataHandler(CReactor *pReactor,char * pAddress,CMDFlowManager *pFlowManager):CEventHandler(pReactor)
{
	m_InstrumentCount = 1;
	m_pFlowManager = pFlowManager;
	//CServiceName *sn = new CServiceName(pAddress);
	//strcpy(m_pAddress,pAddress);
	//CUdpClient * m_client = new CUdpClient(); 
	//m_channel = m_client->Connect(sn);
	m_pPackage = new CXTPPackage();
	m_pPackage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,XTPHLEN);
	//合约状态
	m_instrumetstate=new CMdInstrumentStateMap();
}

CMarketDataHandler::~CMarketDataHandler()
{
	delete m_channel;
	delete m_pPackage;
}


CFTDDepthMarketDataField* CMarketDataHandler::GetMaraketData(CExchangeIDType ExchangeID,CInstrumentIDType InstrumentID)
{
	CTopicMarketDataMap::iterator iterTopic;
	CFTDDepthMarketDataField *pFTDDepthMarketDataField = NULL;

 	for(iterTopic= m_mapTopicMarketData.begin();iterTopic!=m_mapTopicMarketData.end();iterTopic++)
 	{
		CMarketDataMap * pMarketDataMap = iterTopic->second;

		CMarketDataMap::iterator iter = pMarketDataMap->find(InstrumentID);
		if(iter != pMarketDataMap->end())
		{
			pFTDDepthMarketDataField = iter->second;
			return pFTDDepthMarketDataField;
		}
	}
	return pFTDDepthMarketDataField;
}
DWORD CMarketDataHandler::InsertMaraketData(int nTopicID,CFTDDepthMarketDataField* pMarketData)
{
	m_lock.Lock();

	CMarketDataMap * pMarketDataMap = NULL;
	CTopicMarketDataMap::iterator iterTopic = m_mapTopicMarketData.find(nTopicID);
	if(iterTopic == m_mapTopicMarketData.end())
	{	
		pMarketDataMap = new CMarketDataMap();	
		m_mapTopicMarketData.insert(CTopicMarketDataMap::value_type(nTopicID,pMarketDataMap));
	}
	else
	{
		pMarketDataMap = iterTopic->second;
	}

	CMarketDataMap::iterator iter = pMarketDataMap->find(pMarketData->InstrumentID);
	if(iter == pMarketDataMap->end())
	{
		CFTDDepthMarketDataField * p = new CFTDDepthMarketDataField();		
		memcpy(p,pMarketData,sizeof(CFTDDepthMarketDataField));
		pMarketDataMap->insert(CMarketDataMap::value_type(p->InstrumentID,p));
	}
	else
	{
		CFTDDepthMarketDataField * p = iter->second;
		memcpy(p,pMarketData,sizeof(CFTDDepthMarketDataField));
    }

	DWORD dFindInstrumentCount = m_InstrumentCount;
	DWORD *pFind = m_mapInstrument.Find(pMarketData->InstrumentID);
	if(pFind == NULL )
	{
		m_mapInstrument.Insert(pMarketData->InstrumentID,m_InstrumentCount);
		m_InstrumentCount++;
	}
	else
	{
		dFindInstrumentCount = *pFind;
	}
	m_lock.UnLock();

	return dFindInstrumentCount;
}



DWORD CMarketDataHandler::GetInstrumentIDCount(CInstrumentIDType instrmentID)
{
	DWORD *iter = m_mapInstrument.Find(instrmentID);
	if(iter == NULL)
	{
		return -1;
	}
	else
	{
		return *iter;
	}
}

CInstrumentMap * CMarketDataHandler::GetInstrumentMap()
{
	return &m_mapInstrument;
}

void CMarketDataHandler::OnTimer(int nIDEvent)
{
// 	m_lock.Lock();
// 
// 	//20131008 xuzh 修改为发送多有的快照，解决由于不一样的主题中合约不一样导致有的合约无法发送快照的bug
// 	//找出map的第一个元素
// 
// 	m_pPackage->PreparePublish(TID_NtfMarketDataLastMatch);
// 	CTopicMarketDataMap::iterator iterTopic = m_mapTopicMarketData.begin();
// 	while(iterTopic!=m_mapTopicMarketData.end())
// 	{
// 		CMarketDataMap * pMarketDataMap = iterTopic->second;
// 		CMarketDataMap::iterator iter;
// 		for(iter = pMarketDataMap->begin();iter != pMarketDataMap->end();iter++)
// 		{
// 			CFTDDepthMarketDataField *psend =iter->second;
// 			CMarketDataLastMatchField p;
// 			p.ExchangeID = psend->ExchangeID;
// 			p.InstrumentID = psend->InstrumentID;
// 			p.LastPrice = psend->LastPrice;
// 			p.Volume = psend->Volume;
// 			if(XTP_ADD_FIELD(m_pPackage,&p)<0) 
// 			{ 
// 				//如果增加数据失败，说明已经满了，就将前面的全部发生再重新建立一个新包
// 				m_pPackage->MakePackage();
// 				//发送
// 				int len=m_pPackage->Length();
// 				m_channel->Write(m_pPackage->Length(),m_pPackage->Address());
// 				//重新新建一个包
// 				m_pPackage->PreparePublish(TID_NtfMarketDataLastMatch);
// 				XTP_ADD_FIELD(m_pPackage,&p);						
// 			} 
// 		}
// 		iterTopic++;
// 	}
// 	//发送最后一个批次
// 	m_pPackage->MakePackage();
// 	m_channel->Write(m_pPackage->Length(),m_pPackage->Address());
// 	m_lock.UnLock();
// 
// 	REPORT_EVENT(LOG_INFO, "MSCFFEX","定时向 %s 发送行情 !",m_pAddress);
// 
// 	//输出流大小
// 	char flowoutbuf[256];
// 	memset(flowoutbuf,0,sizeof(flowoutbuf));
// 	CMDFlowManager::iterator iterflow = m_pFlowManager->begin();
// 	while (iterflow!=m_pFlowManager->end())
// 	{
// 		sprintf(flowoutbuf,"[%d](%d)",iterflow->first,iterflow->second->GetCount());
// 		REPORT_EVENT(LOG_INFO, "MSCFFEX","FLOW SIZE:%s",flowoutbuf);
// 		iterflow++;
// 	}
}
void CMarketDataHandler::InsetInstrumentStateMap(CFTDQmdInstrumentStateField *instrumetstate)
{
	CMdInstrumentStateMap::iterator iter = m_instrumetstate->find(instrumetstate->InstrumentID);
	if( iter == m_instrumetstate->end() )
	{
		CFTDQmdInstrumentStateField *p = new CFTDQmdInstrumentStateField();		
		memcpy(p,instrumetstate,sizeof(CFTDQmdInstrumentStateField));
		m_instrumetstate->insert(CMdInstrumentStateMap::value_type(instrumetstate->InstrumentID,p));
	}
	else
	{
		CFTDQmdInstrumentStateField * p = iter->second;
		memcpy(p,instrumetstate,sizeof(CFTDQmdInstrumentStateField));
	}
	
}