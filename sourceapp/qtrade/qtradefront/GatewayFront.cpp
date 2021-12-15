#include "public.h"
#include "GatewayFront.h"
#include "XtpData.h"


CGateWayFront::CGateWayFront(CFlow *pDownFlow, int nLifeCycleID,CConfig * pConfig)
{
	m_pTradeResult =pDownFlow;
	m_nLifeCycleID =nLifeCycleID;
	m_pConfig = pConfig;
	m_pSeriesFlow =new CExCachedFlow(false, 0x7fffffff, 0x100000);
	m_reader.AttachFlow(m_pSeriesFlow,0);

	memset(m_sGateWayAddr,0,sizeof(m_sGateWayAddr));
	memset(m_sQueryAddr,0,sizeof(m_sQueryAddr));
	Init();
}

CGateWayFront::~CGateWayFront()
{
	delete m_pGateWayServer;
	delete m_pFrontForwarder;
	delete m_pFrontTerminal;
}

bool CGateWayFront::Init()
{
	char *qquery=m_pConfig->getConfig("qquery");
	strncpy(m_sQueryAddr,qquery,sizeof(m_sQueryAddr));

	char *gateway=m_pConfig->getConfig("GateUfd");
	strncpy(m_sGateWayAddr,gateway,sizeof(m_sGateWayAddr));

	m_pFrontTerminal = new CFrontTerminal;
	CFibClientApi *pClientApi = CFibClientApi::CreateClientApi(this, 0);
	pClientApi->RegisterServer(0, m_sQueryAddr, m_pFrontTerminal);
	m_pFrontForwarder = new CFrontForwarder(0, m_pSeriesFlow,0, pClientApi);

	m_pGateWayServer = new CGateWayServer(this,m_pTradeResult,m_pFrontForwarder);
	m_pGateWayServer->RegisterListener(m_sGateWayAddr);

	return true;
}

void CGateWayFront::FrontStartWork()
{
	Create();
	REPORT_EVENT(LOG_CRITICAL,"CGateWayFront::FrontStartWork","GatewayFront open port\n");

	m_pGateWayServer->EnableListener(true);
}
