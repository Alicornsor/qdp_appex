/////////////////////////////////////////////////////////////////////////
///@system ��������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file MarketDataFlowManager
///@brief ����������ļ��������ӽ��������յ��������������
///@history 
///20130815	���һ�		�������ļ�
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
	CMutex lock; //���� CMarketDataFlowManager ��Ҫ��
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
