// mdusertest.cpp : 
//һ���򵥵����ӣ�����CFfexFtdcMduserApi��CFfexFtdcMduserSpi�ӿڵ�ʹ�á�

#include "MarketDataHandler.h"
#include "UFCopy.h"
#include "XtpPackageDesc.h"

//������UDP���Ĺ㲥�У�����û��ʹ��Э��ջ��ֻ����XTP���ģ��ʽ���ͷ����Ϊ40(XTP����ͷ��СΪ36)
//����һ�η��͸���ĺ�Լ����
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
	//��Լ״̬
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
// 	//20131008 xuzh �޸�Ϊ���Ͷ��еĿ��գ�������ڲ�һ���������к�Լ��һ�������еĺ�Լ�޷����Ϳ��յ�bug
// 	//�ҳ�map�ĵ�һ��Ԫ��
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
// 				//�����������ʧ�ܣ�˵���Ѿ����ˣ��ͽ�ǰ���ȫ�����������½���һ���°�
// 				m_pPackage->MakePackage();
// 				//����
// 				int len=m_pPackage->Length();
// 				m_channel->Write(m_pPackage->Length(),m_pPackage->Address());
// 				//�����½�һ����
// 				m_pPackage->PreparePublish(TID_NtfMarketDataLastMatch);
// 				XTP_ADD_FIELD(m_pPackage,&p);						
// 			} 
// 		}
// 		iterTopic++;
// 	}
// 	//�������һ������
// 	m_pPackage->MakePackage();
// 	m_channel->Write(m_pPackage->Length(),m_pPackage->Address());
// 	m_lock.UnLock();
// 
// 	REPORT_EVENT(LOG_INFO, "MSCFFEX","��ʱ�� %s �������� !",m_pAddress);
// 
// 	//�������С
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