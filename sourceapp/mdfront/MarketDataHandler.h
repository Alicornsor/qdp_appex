/////////////////////////////////////////////////////////////////////////
///@system 飞马行情系统
///@company 上海量投网络科技有限公司
///@file MarketDataHandler.h
///@brief 管理行情快照和合约号的编号并且发送5秒快照行情给uskernel
///@history 
///20130815	徐忠华		创建该文件
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


//add by jinpc 20160829郑州合约状态推送
typedef map<CInstrumentIDType,CFTDQmdInstrumentStateField*> CMdInstrumentStateMap;

class CMarketDataHandler : public CEventHandler
{
public:
    // 构造函数，需要一个有效的指向CFfexFtdcMduserApi实例的指针
	// 20130821 xuzh 增加定时输出流大小的功能，便于运维监控
    CMarketDataHandler(CReactor *pReactor,char * pAddress,CMDFlowManager *pFlowManager);
    ~CMarketDataHandler();
	void SetPubTimer(int nElapse)
	{
		SetTimer(1,nElapse);
	}
	CFTDDepthMarketDataField *GetMaraketData(CExchangeIDType ExchangeID,CInstrumentIDType InstrumentID);
	//插入最新行情记录,返回此合约的id号
	DWORD InsertMaraketData(int nTopicID,CFTDDepthMarketDataField* pMarketData);
	//add by jinpc 20160829
	//合约状态存储
	void InsetInstrumentStateMap(CFTDQmdInstrumentStateField *instrumetstate);
	//定时发布行情
	virtual void OnTimer(int nIDEvent);
	DWORD GetInstrumentIDCount(CInstrumentIDType instrmentID);
	CInstrumentMap * GetInstrumentMap();
	CTopicMarketDataMap m_mapTopicMarketData;
	CInstrumentMap m_mapInstrument;
	//合约状态
	CMdInstrumentStateMap *m_instrumetstate;
private:
	CChannel *m_channel; //发送行情快照
	//CMarketDataMap m_mapMarketData;
	//bool b_insertInstrument;
	DWORD m_InstrumentCount;
	CXTPPackage	 *m_pPackage;
	char m_pMdBuf[1280];//行情接收缓存
	char m_pAddress[256];
#ifdef WIN32
	CMutex m_lock; //访问 m_mapMarketData 需要锁
#else
	CSpinLock m_lock; 
#endif
	CMDFlowManager	*m_pFlowManager;
};

#endif