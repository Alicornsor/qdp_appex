/////////////////////////////////////////////////////////////////////////
///@system 飞马行情系统
///@company 上海量投网络科技有限公司
///@file MarketDataFlowManager
///@brief 行情接收流文件管理，将从交易所接收的行情放入行情流
///@history 
///20130815	徐忠华		创建该文件
/////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MARKETDATAFLOWMANAGER_H__05F8B90F_A369_42A9_B535_35149AEF3EE9__INCLUDED_)
#define AFX_MARKETDATAFLOWMANAGER_H__05F8B90F_A369_42A9_B535_35149AEF3EE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Flow.h"
#include "customDataType.h"
#include "Package.h"
#include "Mutex.h"
#include "UdpChannel.h"
#include "UdpServer.h"
class CMDFlowManager : public map<DWORD, CFlow *>
{
public:
	CMDFlowManager(const char *pszFlowPath);
	~CMDFlowManager();
	CFlow *GetFlow(DWORD nTopicID);
	bool RegisterTopic(DWORD nTopicID);
	const CDateType &GetTradingDay();
	void SetTradingDay(CDateType &TradingDay,CFlow *topicflow);
	int PulishToTopic(CPackage *pPackage, CReadOnlyTopicIDType &TopicID);
#ifdef WIN32
	CMutex lock; //访问 CMarketDataFlowManager 需要锁
#else
	CSpinLock lock;
#endif
	CChannel *getudpchannel();
	void setudpchannel(char *udpip);
	void setmarketbuf(int ilength,char *buf);
private:
	CUdpServer *udpserver;
	CChannel *uchannel;
	string m_strFlowPath;
	CFlow *m_pTradingDayFlow;
	CDateType m_TradingDay;	
};

#endif // !defined(AFX_MARKETDATAFLOWMANAGER_H__05F8B90F_A369_42A9_B535_35149AEF3EE9__INCLUDED_)
