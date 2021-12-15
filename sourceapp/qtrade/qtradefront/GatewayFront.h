#ifndef __CGateWayFront_H__
#define __CGateWayFront_H__

#include "SessionFactory.h"
#include "customDataType.h"
#include "TcpXtpSession.h"
#include "Reactor.h"
#include "CachedFileFlow.h"
#include "XtpPackageDesc.h"
#include "FrontForwarder.h"
#include "FrontTerminal.h"
#include "BaseExchApi.h"
#include "GatewayServer.h"
#include "CConfig.h"

class CGateWayFront :public CBaseExchApi,public CSelectReactor
{
public:
	CGateWayFront(CFlow *pDownFlow, int nLifeCycleID,CConfig * pConfig);
	~CGateWayFront();
	void FrontStartWork();
	bool Init();
	

private:
	CFlow* m_pTradeResult;
	int m_nLifeCycleID;//�������ں�	
	CConfig	*m_pConfig;	//�����ļ�
	
	CFrontTerminal *m_pFrontTerminal;
	CFrontForwarder *m_pFrontForwarder;
	CGateWayServer *m_pGateWayServer;

	char m_sGateWayAddr[30];
	char m_sQueryAddr[30];
};
#endif
