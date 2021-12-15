/////////////////////////////////////////////////////////////////////////
///@system ��������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file MarketDataHandler.h
///@brief ����������պͺ�Լ�ŵı�Ų��ҷ���5����������uskernel
///@history 
///20130815	���һ�		�������ļ�
/////////////////////////////////////////////////////////////////////////

#include "platform.h"
#include "FtdPackageDesc.h"
#include "XTPPackage.h"
#include "EventHandler.h"
#include "UdpClient.h"
#include "UFCopy.h"
#include "XtpData.h"
#include "Mutex.h"
#include "HashMap.h"
//#include "CFFEXFtdcUserApiStruct.h"
#include "MarketDataFlowManager.h"

#ifndef _CMarketDataHandler_H_
#define _CMarketDataHandler_H_

typedef map<CInstrumentIDType,CFTDDepthMarketDataField*> CMarketDataMap;
typedef map<int,CMarketDataMap*> CTopicMarketDataMap;
//typedef map<CInstrumentIDType,int> CInstrumentMap;
typedef CHashMap<CInstrumentIDType,DWORD,HashString> CInstrumentMap;


//add by jinpc 20160829֣�ݺ�Լ״̬����
typedef map<CInstrumentIDType,CFTDQmdInstrumentStateField*> CMdInstrumentStateMap;

class CMarketDataHandler : public CEventHandler
{
public:
    // ���캯������Ҫһ����Ч��ָ��CFfexFtdcMduserApiʵ����ָ��
	// 20130821 xuzh ���Ӷ�ʱ�������С�Ĺ��ܣ�������ά���
    CMarketDataHandler(CReactor *pReactor,char * pAddress,CMDFlowManager *pFlowManager);
    ~CMarketDataHandler();
	void SetPubTimer(int nElapse)
	{
		SetTimer(1,nElapse);
	}
	CFTDDepthMarketDataField *GetMaraketData(CExchangeIDType ExchangeID,CInstrumentIDType InstrumentID);
	//�������������¼,���ش˺�Լ��id��
	DWORD InsertMaraketData(int nTopicID,CFTDDepthMarketDataField* pMarketData);
	//add by jinpc 20160829
	//��Լ״̬�洢
	void InsetInstrumentStateMap(CFTDQmdInstrumentStateField *instrumetstate);
	//��ʱ��������
	virtual void OnTimer(int nIDEvent);
	DWORD GetInstrumentIDCount(CInstrumentIDType instrmentID);
	CInstrumentMap * GetInstrumentMap();
	CTopicMarketDataMap m_mapTopicMarketData;
	CInstrumentMap m_mapInstrument;
	//��Լ״̬
	CMdInstrumentStateMap *m_instrumetstate;
private:
	CChannel *m_channel; //�����������
	//CMarketDataMap m_mapMarketData;
	//bool b_insertInstrument;
	DWORD m_InstrumentCount;
	CXTPPackage	 *m_pPackage;
	char m_pMdBuf[1280];//������ջ���
	char m_pAddress[256];
#ifdef WIN32
	CMutex m_lock; //���� m_mapMarketData ��Ҫ��
#else
	CSpinLock m_lock; 
#endif
	CMDFlowManager	*m_pFlowManager;
};

#endif