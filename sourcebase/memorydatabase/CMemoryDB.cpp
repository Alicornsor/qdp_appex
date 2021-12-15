/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file CMemoryDB.cpp
///@brief实现了类CMemoryDB
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CMemoryDB.h"
#include <map>
#include <string>
using namespace std;

#define MEMORYDB_ID			0
#define MAX_TABLE_COUNT		300				///引导块中每块放置的内存数据库表或者索引的数量

CMemoryDB::CMemoryDB(void)
{
	m_DataSyncStatusFactory=NULL;
	m_SystemStatusFactory=NULL;
	m_OrderActionFactory=NULL;
	m_OrderFactory=NULL;
	m_TradeFactory=NULL;
	m_PreOrderFactory=NULL;
	m_IndexPreOrderFactory=NULL;
	m_InvestorPositionFactory=NULL;
	m_InvestorAccountFactory=NULL;
	m_InvestorAccountDepositFactory=NULL;
	m_ExchangeFactory=NULL;
	m_SeatFactory=NULL;
	m_InstrumentFactory=NULL;
	m_CmbInstrumentDetailFactory=NULL;
	m_ClientTradingIDFactory=NULL;
	m_InvestorFactory=NULL;
	m_InvestorMarginFactory=NULL;
	m_InvestorFeeFactory=NULL;
	m_UserFactory=NULL;
	m_UserInvestorFactory=NULL;
	m_OrderInsertFailedFactory=NULL;
	m_UserTradingRightFactory=NULL;
	m_CurrentTimeFactory=NULL;
	m_UserSessionFactory=NULL;
	m_MaxLocalIDFactory=NULL;
	m_BrkUserIDLocalIDFactory=NULL;
	m_PartClientInsGroupPositionFactory=NULL;
	m_ClientMarginCombTypeFactory=NULL;
	m_InstrumentGroupFactory=NULL;
	m_SGEDeferRateFactory=NULL;
	m_InvestorTradingRightFactory=NULL;
	m_UserIPFactory=NULL;
	m_InvestorOptionFeeFactory=NULL;
	m_MarketDataFactory=NULL;
	m_OrderDelayFactory=NULL;
	m_SystemInfoFactory=NULL;
	
	memset( &m_memTableItemInfo, 0x00, sizeof(MemTableItemInfoT) );
}
	
CMemoryDB::~CMemoryDB(void)
{
	if (m_DataSyncStatusFactory!=NULL)
		delete m_DataSyncStatusFactory;
	if (m_SystemStatusFactory!=NULL)
		delete m_SystemStatusFactory;
	if (m_OrderActionFactory!=NULL)
		delete m_OrderActionFactory;
	if (m_OrderFactory!=NULL)
		delete m_OrderFactory;
	if (m_TradeFactory!=NULL)
		delete m_TradeFactory;
	if (m_PreOrderFactory!=NULL)
		delete m_PreOrderFactory;
	if (m_IndexPreOrderFactory!=NULL)
		delete m_IndexPreOrderFactory;
	if (m_InvestorPositionFactory!=NULL)
		delete m_InvestorPositionFactory;
	if (m_InvestorAccountFactory!=NULL)
		delete m_InvestorAccountFactory;
	if (m_InvestorAccountDepositFactory!=NULL)
		delete m_InvestorAccountDepositFactory;
	if (m_ExchangeFactory!=NULL)
		delete m_ExchangeFactory;
	if (m_SeatFactory!=NULL)
		delete m_SeatFactory;
	if (m_InstrumentFactory!=NULL)
		delete m_InstrumentFactory;
	if (m_CmbInstrumentDetailFactory!=NULL)
		delete m_CmbInstrumentDetailFactory;
	if (m_ClientTradingIDFactory!=NULL)
		delete m_ClientTradingIDFactory;
	if (m_InvestorFactory!=NULL)
		delete m_InvestorFactory;
	if (m_InvestorMarginFactory!=NULL)
		delete m_InvestorMarginFactory;
	if (m_InvestorFeeFactory!=NULL)
		delete m_InvestorFeeFactory;
	if (m_UserFactory!=NULL)
		delete m_UserFactory;
	if (m_UserInvestorFactory!=NULL)
		delete m_UserInvestorFactory;
	if (m_OrderInsertFailedFactory!=NULL)
		delete m_OrderInsertFailedFactory;
	if (m_UserTradingRightFactory!=NULL)
		delete m_UserTradingRightFactory;
	if (m_CurrentTimeFactory!=NULL)
		delete m_CurrentTimeFactory;
	if (m_UserSessionFactory!=NULL)
		delete m_UserSessionFactory;
	if (m_MaxLocalIDFactory!=NULL)
		delete m_MaxLocalIDFactory;
	if (m_BrkUserIDLocalIDFactory!=NULL)
		delete m_BrkUserIDLocalIDFactory;
	if (m_PartClientInsGroupPositionFactory!=NULL)
		delete m_PartClientInsGroupPositionFactory;
	if (m_ClientMarginCombTypeFactory!=NULL)
		delete m_ClientMarginCombTypeFactory;
	if (m_InstrumentGroupFactory!=NULL)
		delete m_InstrumentGroupFactory;
	if (m_SGEDeferRateFactory!=NULL)
		delete m_SGEDeferRateFactory;
	if (m_InvestorTradingRightFactory!=NULL)
		delete m_InvestorTradingRightFactory;
	if (m_UserIPFactory!=NULL)
		delete m_UserIPFactory;
	if (m_InvestorOptionFeeFactory!=NULL)
		delete m_InvestorOptionFeeFactory;
	if (m_MarketDataFactory!=NULL)
		delete m_MarketDataFactory;
	if (m_OrderDelayFactory!=NULL)
		delete m_OrderDelayFactory;
	if (m_SystemInfoFactory!=NULL)
		delete m_SystemInfoFactory;
}
	
int CMemoryDB::isA(char *objectType)
{
	if (!strcmp(objectType,"CMemoryDB"))
		return 1;
	return CBaseObject::isA(objectType);
}

char *CMemoryDB::getType(void)
{
	return "CMemoryDB";
}

void CMemoryDB::output(CLogger *pLogger,int indent)
{
	CHECK_TYPE("CMemoryDB");
	pLogger->output(indent,0,"CMemoryDB:");
	if (m_DataSyncStatusFactory!=NULL)
		m_DataSyncStatusFactory->output(pLogger,indent+1);
	if (m_SystemStatusFactory!=NULL)
		m_SystemStatusFactory->output(pLogger,indent+1);
	if (m_OrderActionFactory!=NULL)
		m_OrderActionFactory->output(pLogger,indent+1);
	if (m_OrderFactory!=NULL)
		m_OrderFactory->output(pLogger,indent+1);
	if (m_TradeFactory!=NULL)
		m_TradeFactory->output(pLogger,indent+1);
	if (m_PreOrderFactory!=NULL)
		m_PreOrderFactory->output(pLogger,indent+1);
	if (m_IndexPreOrderFactory!=NULL)
		m_IndexPreOrderFactory->output(pLogger,indent+1);
	if (m_InvestorPositionFactory!=NULL)
		m_InvestorPositionFactory->output(pLogger,indent+1);
	if (m_InvestorAccountFactory!=NULL)
		m_InvestorAccountFactory->output(pLogger,indent+1);
	if (m_InvestorAccountDepositFactory!=NULL)
		m_InvestorAccountDepositFactory->output(pLogger,indent+1);
	if (m_ExchangeFactory!=NULL)
		m_ExchangeFactory->output(pLogger,indent+1);
	if (m_SeatFactory!=NULL)
		m_SeatFactory->output(pLogger,indent+1);
	if (m_InstrumentFactory!=NULL)
		m_InstrumentFactory->output(pLogger,indent+1);
	if (m_CmbInstrumentDetailFactory!=NULL)
		m_CmbInstrumentDetailFactory->output(pLogger,indent+1);
	if (m_ClientTradingIDFactory!=NULL)
		m_ClientTradingIDFactory->output(pLogger,indent+1);
	if (m_InvestorFactory!=NULL)
		m_InvestorFactory->output(pLogger,indent+1);
	if (m_InvestorMarginFactory!=NULL)
		m_InvestorMarginFactory->output(pLogger,indent+1);
	if (m_InvestorFeeFactory!=NULL)
		m_InvestorFeeFactory->output(pLogger,indent+1);
	if (m_UserFactory!=NULL)
		m_UserFactory->output(pLogger,indent+1);
	if (m_UserInvestorFactory!=NULL)
		m_UserInvestorFactory->output(pLogger,indent+1);
	if (m_OrderInsertFailedFactory!=NULL)
		m_OrderInsertFailedFactory->output(pLogger,indent+1);
	if (m_UserTradingRightFactory!=NULL)
		m_UserTradingRightFactory->output(pLogger,indent+1);
	if (m_CurrentTimeFactory!=NULL)
		m_CurrentTimeFactory->output(pLogger,indent+1);
	if (m_UserSessionFactory!=NULL)
		m_UserSessionFactory->output(pLogger,indent+1);
	if (m_MaxLocalIDFactory!=NULL)
		m_MaxLocalIDFactory->output(pLogger,indent+1);
	if (m_BrkUserIDLocalIDFactory!=NULL)
		m_BrkUserIDLocalIDFactory->output(pLogger,indent+1);
	if (m_PartClientInsGroupPositionFactory!=NULL)
		m_PartClientInsGroupPositionFactory->output(pLogger,indent+1);
	if (m_ClientMarginCombTypeFactory!=NULL)
		m_ClientMarginCombTypeFactory->output(pLogger,indent+1);
	if (m_InstrumentGroupFactory!=NULL)
		m_InstrumentGroupFactory->output(pLogger,indent+1);
	if (m_SGEDeferRateFactory!=NULL)
		m_SGEDeferRateFactory->output(pLogger,indent+1);
	if (m_InvestorTradingRightFactory!=NULL)
		m_InvestorTradingRightFactory->output(pLogger,indent+1);
	if (m_UserIPFactory!=NULL)
		m_UserIPFactory->output(pLogger,indent+1);
	if (m_InvestorOptionFeeFactory!=NULL)
		m_InvestorOptionFeeFactory->output(pLogger,indent+1);
	if (m_MarketDataFactory!=NULL)
		m_MarketDataFactory->output(pLogger,indent+1);
	if (m_OrderDelayFactory!=NULL)
		m_OrderDelayFactory->output(pLogger,indent+1);
	if (m_SystemInfoFactory!=NULL)
		m_SystemInfoFactory->output(pLogger,indent+1);
}

int CMemoryDB::init(CConfig *pConfig,IMemoryAllocator *pAllocator,bool reuse)
{
	if(pAllocator == NULL)
	{
		pAllocator = new CNormalMemoryAllocator();
		pAllocator->init(reuse);
	}
	if(!reuse)
	{
		map<string,int> indexMap;
		pMem=new CFixMem(sizeof(TableStruct),MAX_TABLE_COUNT,pAllocator,false,MEMORYDB_ID);
		TableStruct* pStru = NULL;
		
		m_DataSyncStatusFactory=new CDataSyncStatusFactory(pConfig,pAllocator,&indexMap);
		if (m_DataSyncStatusFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"DataSyncStatus");
		pStru->reuseID = m_DataSyncStatusFactory->getReuseID();
				
		m_SystemStatusFactory=new CSystemStatusFactory(pConfig,pAllocator,&indexMap);
		if (m_SystemStatusFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"SystemStatus");
		pStru->reuseID = m_SystemStatusFactory->getReuseID();
				
		m_OrderActionFactory=new COrderActionFactory(pConfig,pAllocator,&indexMap);
		if (m_OrderActionFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"OrderAction");
		pStru->reuseID = m_OrderActionFactory->getReuseID();
				
		m_OrderFactory=new COrderFactory(pConfig,pAllocator,&indexMap);
		if (m_OrderFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"Order");
		pStru->reuseID = m_OrderFactory->getReuseID();
				
		m_TradeFactory=new CTradeFactory(pConfig,pAllocator,&indexMap);
		if (m_TradeFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"Trade");
		pStru->reuseID = m_TradeFactory->getReuseID();
				
		m_PreOrderFactory=new CPreOrderFactory(pConfig,pAllocator,&indexMap);
		if (m_PreOrderFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"PreOrder");
		pStru->reuseID = m_PreOrderFactory->getReuseID();
				
		m_IndexPreOrderFactory=new CIndexPreOrderFactory(pConfig,pAllocator,&indexMap);
		if (m_IndexPreOrderFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"IndexPreOrder");
		pStru->reuseID = m_IndexPreOrderFactory->getReuseID();
				
		m_InvestorPositionFactory=new CInvestorPositionFactory(pConfig,pAllocator,&indexMap);
		if (m_InvestorPositionFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"InvestorPosition");
		pStru->reuseID = m_InvestorPositionFactory->getReuseID();
				
		m_InvestorAccountFactory=new CInvestorAccountFactory(pConfig,pAllocator,&indexMap);
		if (m_InvestorAccountFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"InvestorAccount");
		pStru->reuseID = m_InvestorAccountFactory->getReuseID();
				
		m_InvestorAccountDepositFactory=new CInvestorAccountDepositFactory(pConfig,pAllocator,&indexMap);
		if (m_InvestorAccountDepositFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"InvestorAccountDeposit");
		pStru->reuseID = m_InvestorAccountDepositFactory->getReuseID();
				
		m_ExchangeFactory=new CExchangeFactory(pConfig,pAllocator,&indexMap);
		if (m_ExchangeFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"Exchange");
		pStru->reuseID = m_ExchangeFactory->getReuseID();
				
		m_SeatFactory=new CSeatFactory(pConfig,pAllocator,&indexMap);
		if (m_SeatFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"Seat");
		pStru->reuseID = m_SeatFactory->getReuseID();
				
		m_InstrumentFactory=new CInstrumentFactory(pConfig,pAllocator,&indexMap);
		if (m_InstrumentFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"Instrument");
		pStru->reuseID = m_InstrumentFactory->getReuseID();
				
		m_CmbInstrumentDetailFactory=new CCmbInstrumentDetailFactory(pConfig,pAllocator,&indexMap);
		if (m_CmbInstrumentDetailFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"CmbInstrumentDetail");
		pStru->reuseID = m_CmbInstrumentDetailFactory->getReuseID();
				
		m_ClientTradingIDFactory=new CClientTradingIDFactory(pConfig,pAllocator,&indexMap);
		if (m_ClientTradingIDFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"ClientTradingID");
		pStru->reuseID = m_ClientTradingIDFactory->getReuseID();
				
		m_InvestorFactory=new CInvestorFactory(pConfig,pAllocator,&indexMap);
		if (m_InvestorFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"Investor");
		pStru->reuseID = m_InvestorFactory->getReuseID();
				
		m_InvestorMarginFactory=new CInvestorMarginFactory(pConfig,pAllocator,&indexMap);
		if (m_InvestorMarginFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"InvestorMargin");
		pStru->reuseID = m_InvestorMarginFactory->getReuseID();
				
		m_InvestorFeeFactory=new CInvestorFeeFactory(pConfig,pAllocator,&indexMap);
		if (m_InvestorFeeFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"InvestorFee");
		pStru->reuseID = m_InvestorFeeFactory->getReuseID();
				
		m_UserFactory=new CUserFactory(pConfig,pAllocator,&indexMap);
		if (m_UserFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"User");
		pStru->reuseID = m_UserFactory->getReuseID();
				
		m_UserInvestorFactory=new CUserInvestorFactory(pConfig,pAllocator,&indexMap);
		if (m_UserInvestorFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"UserInvestor");
		pStru->reuseID = m_UserInvestorFactory->getReuseID();
				
		m_OrderInsertFailedFactory=new COrderInsertFailedFactory(pConfig,pAllocator,&indexMap);
		if (m_OrderInsertFailedFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"OrderInsertFailed");
		pStru->reuseID = m_OrderInsertFailedFactory->getReuseID();
				
		m_UserTradingRightFactory=new CUserTradingRightFactory(pConfig,pAllocator,&indexMap);
		if (m_UserTradingRightFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"UserTradingRight");
		pStru->reuseID = m_UserTradingRightFactory->getReuseID();
				
		m_CurrentTimeFactory=new CCurrentTimeFactory(pConfig,pAllocator,&indexMap);
		if (m_CurrentTimeFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"CurrentTime");
		pStru->reuseID = m_CurrentTimeFactory->getReuseID();
				
		m_UserSessionFactory=new CUserSessionFactory(pConfig,pAllocator,&indexMap);
		if (m_UserSessionFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"UserSession");
		pStru->reuseID = m_UserSessionFactory->getReuseID();
				
		m_MaxLocalIDFactory=new CMaxLocalIDFactory(pConfig,pAllocator,&indexMap);
		if (m_MaxLocalIDFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"MaxLocalID");
		pStru->reuseID = m_MaxLocalIDFactory->getReuseID();
				
		m_BrkUserIDLocalIDFactory=new CBrkUserIDLocalIDFactory(pConfig,pAllocator,&indexMap);
		if (m_BrkUserIDLocalIDFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"BrkUserIDLocalID");
		pStru->reuseID = m_BrkUserIDLocalIDFactory->getReuseID();
				
		m_PartClientInsGroupPositionFactory=new CPartClientInsGroupPositionFactory(pConfig,pAllocator,&indexMap);
		if (m_PartClientInsGroupPositionFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"PartClientInsGroupPosition");
		pStru->reuseID = m_PartClientInsGroupPositionFactory->getReuseID();
				
		m_ClientMarginCombTypeFactory=new CClientMarginCombTypeFactory(pConfig,pAllocator,&indexMap);
		if (m_ClientMarginCombTypeFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"ClientMarginCombType");
		pStru->reuseID = m_ClientMarginCombTypeFactory->getReuseID();
				
		m_InstrumentGroupFactory=new CInstrumentGroupFactory(pConfig,pAllocator,&indexMap);
		if (m_InstrumentGroupFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"InstrumentGroup");
		pStru->reuseID = m_InstrumentGroupFactory->getReuseID();
				
		m_SGEDeferRateFactory=new CSGEDeferRateFactory(pConfig,pAllocator,&indexMap);
		if (m_SGEDeferRateFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"SGEDeferRate");
		pStru->reuseID = m_SGEDeferRateFactory->getReuseID();
				
		m_InvestorTradingRightFactory=new CInvestorTradingRightFactory(pConfig,pAllocator,&indexMap);
		if (m_InvestorTradingRightFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"InvestorTradingRight");
		pStru->reuseID = m_InvestorTradingRightFactory->getReuseID();
				
		m_UserIPFactory=new CUserIPFactory(pConfig,pAllocator,&indexMap);
		if (m_UserIPFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"UserIP");
		pStru->reuseID = m_UserIPFactory->getReuseID();
				
		m_InvestorOptionFeeFactory=new CInvestorOptionFeeFactory(pConfig,pAllocator,&indexMap);
		if (m_InvestorOptionFeeFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"InvestorOptionFee");
		pStru->reuseID = m_InvestorOptionFeeFactory->getReuseID();
				
		m_MarketDataFactory=new CMarketDataFactory(pConfig,pAllocator,&indexMap);
		if (m_MarketDataFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"MarketData");
		pStru->reuseID = m_MarketDataFactory->getReuseID();
				
		m_OrderDelayFactory=new COrderDelayFactory(pConfig,pAllocator,&indexMap);
		if (m_OrderDelayFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"OrderDelay");
		pStru->reuseID = m_OrderDelayFactory->getReuseID();
				
		m_SystemInfoFactory=new CSystemInfoFactory(pConfig,pAllocator,&indexMap);
		if (m_SystemInfoFactory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"SystemInfo");
		pStru->reuseID = m_SystemInfoFactory->getReuseID();
				
	
		map<string,int>::iterator it = indexMap.begin();
		for(;it!=indexMap.end();it++)
		{
			pStru = (TableStruct *)pMem->alloc();
			strcpy(pStru->tableName,it->first.c_str());
			pStru->reuseID = it->second;
		}
	}
	else
	{
		pMem=new CFixMem(sizeof(TableStruct),MAX_TABLE_COUNT,pAllocator,true,MEMORYDB_ID);
		map<string,int> blockMap;
		TableStruct* pStru = NULL;
		for(int i=0;i<pMem->getCount();i++)
		{
			pStru = (TableStruct *)pMem->getObject(i);
			blockMap.insert(map<string,int>::value_type(pStru->tableName,pStru->reuseID));
		}
		map<string,int>::iterator it;
			
		it = blockMap.find("DataSyncStatus");
		if(it == blockMap.end())
			m_DataSyncStatusFactory=new CDataSyncStatusFactory(pConfig,pAllocator,&blockMap);
		else
			m_DataSyncStatusFactory=new CDataSyncStatusFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_DataSyncStatusFactory==NULL)
			return 0;
				
		it = blockMap.find("SystemStatus");
		if(it == blockMap.end())
			m_SystemStatusFactory=new CSystemStatusFactory(pConfig,pAllocator,&blockMap);
		else
			m_SystemStatusFactory=new CSystemStatusFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_SystemStatusFactory==NULL)
			return 0;
				
		it = blockMap.find("OrderAction");
		if(it == blockMap.end())
			m_OrderActionFactory=new COrderActionFactory(pConfig,pAllocator,&blockMap);
		else
			m_OrderActionFactory=new COrderActionFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_OrderActionFactory==NULL)
			return 0;
				
		it = blockMap.find("Order");
		if(it == blockMap.end())
			m_OrderFactory=new COrderFactory(pConfig,pAllocator,&blockMap);
		else
			m_OrderFactory=new COrderFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_OrderFactory==NULL)
			return 0;
				
		it = blockMap.find("Trade");
		if(it == blockMap.end())
			m_TradeFactory=new CTradeFactory(pConfig,pAllocator,&blockMap);
		else
			m_TradeFactory=new CTradeFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_TradeFactory==NULL)
			return 0;
				
		it = blockMap.find("PreOrder");
		if(it == blockMap.end())
			m_PreOrderFactory=new CPreOrderFactory(pConfig,pAllocator,&blockMap);
		else
			m_PreOrderFactory=new CPreOrderFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_PreOrderFactory==NULL)
			return 0;
				
		it = blockMap.find("IndexPreOrder");
		if(it == blockMap.end())
			m_IndexPreOrderFactory=new CIndexPreOrderFactory(pConfig,pAllocator,&blockMap);
		else
			m_IndexPreOrderFactory=new CIndexPreOrderFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_IndexPreOrderFactory==NULL)
			return 0;
				
		it = blockMap.find("InvestorPosition");
		if(it == blockMap.end())
			m_InvestorPositionFactory=new CInvestorPositionFactory(pConfig,pAllocator,&blockMap);
		else
			m_InvestorPositionFactory=new CInvestorPositionFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_InvestorPositionFactory==NULL)
			return 0;
				
		it = blockMap.find("InvestorAccount");
		if(it == blockMap.end())
			m_InvestorAccountFactory=new CInvestorAccountFactory(pConfig,pAllocator,&blockMap);
		else
			m_InvestorAccountFactory=new CInvestorAccountFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_InvestorAccountFactory==NULL)
			return 0;
				
		it = blockMap.find("InvestorAccountDeposit");
		if(it == blockMap.end())
			m_InvestorAccountDepositFactory=new CInvestorAccountDepositFactory(pConfig,pAllocator,&blockMap);
		else
			m_InvestorAccountDepositFactory=new CInvestorAccountDepositFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_InvestorAccountDepositFactory==NULL)
			return 0;
				
		it = blockMap.find("Exchange");
		if(it == blockMap.end())
			m_ExchangeFactory=new CExchangeFactory(pConfig,pAllocator,&blockMap);
		else
			m_ExchangeFactory=new CExchangeFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_ExchangeFactory==NULL)
			return 0;
				
		it = blockMap.find("Seat");
		if(it == blockMap.end())
			m_SeatFactory=new CSeatFactory(pConfig,pAllocator,&blockMap);
		else
			m_SeatFactory=new CSeatFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_SeatFactory==NULL)
			return 0;
				
		it = blockMap.find("Instrument");
		if(it == blockMap.end())
			m_InstrumentFactory=new CInstrumentFactory(pConfig,pAllocator,&blockMap);
		else
			m_InstrumentFactory=new CInstrumentFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_InstrumentFactory==NULL)
			return 0;
				
		it = blockMap.find("CmbInstrumentDetail");
		if(it == blockMap.end())
			m_CmbInstrumentDetailFactory=new CCmbInstrumentDetailFactory(pConfig,pAllocator,&blockMap);
		else
			m_CmbInstrumentDetailFactory=new CCmbInstrumentDetailFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_CmbInstrumentDetailFactory==NULL)
			return 0;
				
		it = blockMap.find("ClientTradingID");
		if(it == blockMap.end())
			m_ClientTradingIDFactory=new CClientTradingIDFactory(pConfig,pAllocator,&blockMap);
		else
			m_ClientTradingIDFactory=new CClientTradingIDFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_ClientTradingIDFactory==NULL)
			return 0;
				
		it = blockMap.find("Investor");
		if(it == blockMap.end())
			m_InvestorFactory=new CInvestorFactory(pConfig,pAllocator,&blockMap);
		else
			m_InvestorFactory=new CInvestorFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_InvestorFactory==NULL)
			return 0;
				
		it = blockMap.find("InvestorMargin");
		if(it == blockMap.end())
			m_InvestorMarginFactory=new CInvestorMarginFactory(pConfig,pAllocator,&blockMap);
		else
			m_InvestorMarginFactory=new CInvestorMarginFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_InvestorMarginFactory==NULL)
			return 0;
				
		it = blockMap.find("InvestorFee");
		if(it == blockMap.end())
			m_InvestorFeeFactory=new CInvestorFeeFactory(pConfig,pAllocator,&blockMap);
		else
			m_InvestorFeeFactory=new CInvestorFeeFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_InvestorFeeFactory==NULL)
			return 0;
				
		it = blockMap.find("User");
		if(it == blockMap.end())
			m_UserFactory=new CUserFactory(pConfig,pAllocator,&blockMap);
		else
			m_UserFactory=new CUserFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_UserFactory==NULL)
			return 0;
				
		it = blockMap.find("UserInvestor");
		if(it == blockMap.end())
			m_UserInvestorFactory=new CUserInvestorFactory(pConfig,pAllocator,&blockMap);
		else
			m_UserInvestorFactory=new CUserInvestorFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_UserInvestorFactory==NULL)
			return 0;
				
		it = blockMap.find("OrderInsertFailed");
		if(it == blockMap.end())
			m_OrderInsertFailedFactory=new COrderInsertFailedFactory(pConfig,pAllocator,&blockMap);
		else
			m_OrderInsertFailedFactory=new COrderInsertFailedFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_OrderInsertFailedFactory==NULL)
			return 0;
				
		it = blockMap.find("UserTradingRight");
		if(it == blockMap.end())
			m_UserTradingRightFactory=new CUserTradingRightFactory(pConfig,pAllocator,&blockMap);
		else
			m_UserTradingRightFactory=new CUserTradingRightFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_UserTradingRightFactory==NULL)
			return 0;
				
		it = blockMap.find("CurrentTime");
		if(it == blockMap.end())
			m_CurrentTimeFactory=new CCurrentTimeFactory(pConfig,pAllocator,&blockMap);
		else
			m_CurrentTimeFactory=new CCurrentTimeFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_CurrentTimeFactory==NULL)
			return 0;
				
		it = blockMap.find("UserSession");
		if(it == blockMap.end())
			m_UserSessionFactory=new CUserSessionFactory(pConfig,pAllocator,&blockMap);
		else
			m_UserSessionFactory=new CUserSessionFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_UserSessionFactory==NULL)
			return 0;
				
		it = blockMap.find("MaxLocalID");
		if(it == blockMap.end())
			m_MaxLocalIDFactory=new CMaxLocalIDFactory(pConfig,pAllocator,&blockMap);
		else
			m_MaxLocalIDFactory=new CMaxLocalIDFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_MaxLocalIDFactory==NULL)
			return 0;
				
		it = blockMap.find("BrkUserIDLocalID");
		if(it == blockMap.end())
			m_BrkUserIDLocalIDFactory=new CBrkUserIDLocalIDFactory(pConfig,pAllocator,&blockMap);
		else
			m_BrkUserIDLocalIDFactory=new CBrkUserIDLocalIDFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_BrkUserIDLocalIDFactory==NULL)
			return 0;
				
		it = blockMap.find("PartClientInsGroupPosition");
		if(it == blockMap.end())
			m_PartClientInsGroupPositionFactory=new CPartClientInsGroupPositionFactory(pConfig,pAllocator,&blockMap);
		else
			m_PartClientInsGroupPositionFactory=new CPartClientInsGroupPositionFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_PartClientInsGroupPositionFactory==NULL)
			return 0;
				
		it = blockMap.find("ClientMarginCombType");
		if(it == blockMap.end())
			m_ClientMarginCombTypeFactory=new CClientMarginCombTypeFactory(pConfig,pAllocator,&blockMap);
		else
			m_ClientMarginCombTypeFactory=new CClientMarginCombTypeFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_ClientMarginCombTypeFactory==NULL)
			return 0;
				
		it = blockMap.find("InstrumentGroup");
		if(it == blockMap.end())
			m_InstrumentGroupFactory=new CInstrumentGroupFactory(pConfig,pAllocator,&blockMap);
		else
			m_InstrumentGroupFactory=new CInstrumentGroupFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_InstrumentGroupFactory==NULL)
			return 0;
				
		it = blockMap.find("SGEDeferRate");
		if(it == blockMap.end())
			m_SGEDeferRateFactory=new CSGEDeferRateFactory(pConfig,pAllocator,&blockMap);
		else
			m_SGEDeferRateFactory=new CSGEDeferRateFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_SGEDeferRateFactory==NULL)
			return 0;
				
		it = blockMap.find("InvestorTradingRight");
		if(it == blockMap.end())
			m_InvestorTradingRightFactory=new CInvestorTradingRightFactory(pConfig,pAllocator,&blockMap);
		else
			m_InvestorTradingRightFactory=new CInvestorTradingRightFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_InvestorTradingRightFactory==NULL)
			return 0;
				
		it = blockMap.find("UserIP");
		if(it == blockMap.end())
			m_UserIPFactory=new CUserIPFactory(pConfig,pAllocator,&blockMap);
		else
			m_UserIPFactory=new CUserIPFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_UserIPFactory==NULL)
			return 0;
				
		it = blockMap.find("InvestorOptionFee");
		if(it == blockMap.end())
			m_InvestorOptionFeeFactory=new CInvestorOptionFeeFactory(pConfig,pAllocator,&blockMap);
		else
			m_InvestorOptionFeeFactory=new CInvestorOptionFeeFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_InvestorOptionFeeFactory==NULL)
			return 0;
				
		it = blockMap.find("MarketData");
		if(it == blockMap.end())
			m_MarketDataFactory=new CMarketDataFactory(pConfig,pAllocator,&blockMap);
		else
			m_MarketDataFactory=new CMarketDataFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_MarketDataFactory==NULL)
			return 0;
				
		it = blockMap.find("OrderDelay");
		if(it == blockMap.end())
			m_OrderDelayFactory=new COrderDelayFactory(pConfig,pAllocator,&blockMap);
		else
			m_OrderDelayFactory=new COrderDelayFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_OrderDelayFactory==NULL)
			return 0;
				
		it = blockMap.find("SystemInfo");
		if(it == blockMap.end())
			m_SystemInfoFactory=new CSystemInfoFactory(pConfig,pAllocator,&blockMap);
		else
			m_SystemInfoFactory=new CSystemInfoFactory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_SystemInfoFactory==NULL)
			return 0;
				
	}
	return 1;
}

int CMemoryDB::load(CConfig *pConfig)
{
	if (!m_SystemStatusFactory->readCSV(pConfig))
		return 0;
	if (!m_OrderFactory->readCSV(pConfig))
		return 0;
	if (!m_TradeFactory->readCSV(pConfig))
		return 0;
	if (!m_PreOrderFactory->readCSV(pConfig))
		return 0;
	if (!m_IndexPreOrderFactory->readCSV(pConfig))
		return 0;
	if (!m_InvestorPositionFactory->readCSV(pConfig))
		return 0;
	if (!m_InvestorAccountFactory->readCSV(pConfig))
		return 0;
	if (!m_InvestorAccountDepositFactory->readCSV(pConfig))
		return 0;
	if (!m_ExchangeFactory->readCSV(pConfig))
		return 0;
	if (!m_SeatFactory->readCSV(pConfig))
		return 0;
	if (!m_InstrumentFactory->readCSV(pConfig))
		return 0;
	if (!m_CmbInstrumentDetailFactory->readCSV(pConfig))
		return 0;
	if (!m_ClientTradingIDFactory->readCSV(pConfig))
		return 0;
	if (!m_InvestorFactory->readCSV(pConfig))
		return 0;
	if (!m_InvestorMarginFactory->readCSV(pConfig))
		return 0;
	if (!m_InvestorFeeFactory->readCSV(pConfig))
		return 0;
	if (!m_UserFactory->readCSV(pConfig))
		return 0;
	if (!m_UserInvestorFactory->readCSV(pConfig))
		return 0;
	if (!m_OrderInsertFailedFactory->readCSV(pConfig))
		return 0;
	if (!m_UserTradingRightFactory->readCSV(pConfig))
		return 0;
	if (!m_PartClientInsGroupPositionFactory->readCSV(pConfig))
		return 0;
	if (!m_ClientMarginCombTypeFactory->readCSV(pConfig))
		return 0;
	if (!m_InstrumentGroupFactory->readCSV(pConfig))
		return 0;
	if (!m_SGEDeferRateFactory->readCSV(pConfig))
		return 0;
	if (!m_InvestorTradingRightFactory->readCSV(pConfig))
		return 0;
	if (!m_UserIPFactory->readCSV(pConfig))
		return 0;
	if (!m_InvestorOptionFeeFactory->readCSV(pConfig))
		return 0;
	if (!m_MarketDataFactory->readCSV(pConfig))
		return 0;
	if (!m_SystemInfoFactory->readCSV(pConfig))
		return 0;
	return 1;
}

int CMemoryDB::save(CConfig *pConfig)
{
	if (!m_DataSyncStatusFactory->writeCSV(pConfig))
		return 0;
	if (!m_SystemStatusFactory->writeCSV(pConfig))
		return 0;
	if (!m_OrderActionFactory->writeCSV(pConfig))
		return 0;
	if (!m_OrderFactory->writeCSV(pConfig))
		return 0;
	if (!m_TradeFactory->writeCSV(pConfig))
		return 0;
	if (!m_PreOrderFactory->writeCSV(pConfig))
		return 0;
	if (!m_IndexPreOrderFactory->writeCSV(pConfig))
		return 0;
	if (!m_InvestorPositionFactory->writeCSV(pConfig))
		return 0;
	if (!m_InvestorAccountFactory->writeCSV(pConfig))
		return 0;
	if (!m_InvestorAccountDepositFactory->writeCSV(pConfig))
		return 0;
	if (!m_ExchangeFactory->writeCSV(pConfig))
		return 0;
	if (!m_SeatFactory->writeCSV(pConfig))
		return 0;
	if (!m_InstrumentFactory->writeCSV(pConfig))
		return 0;
	if (!m_CmbInstrumentDetailFactory->writeCSV(pConfig))
		return 0;
	if (!m_ClientTradingIDFactory->writeCSV(pConfig))
		return 0;
	if (!m_InvestorFactory->writeCSV(pConfig))
		return 0;
	if (!m_InvestorMarginFactory->writeCSV(pConfig))
		return 0;
	if (!m_InvestorFeeFactory->writeCSV(pConfig))
		return 0;
	if (!m_UserFactory->writeCSV(pConfig))
		return 0;
	if (!m_UserInvestorFactory->writeCSV(pConfig))
		return 0;
	if (!m_OrderInsertFailedFactory->writeCSV(pConfig))
		return 0;
	if (!m_UserTradingRightFactory->writeCSV(pConfig))
		return 0;
	if (!m_CurrentTimeFactory->writeCSV(pConfig))
		return 0;
	if (!m_UserSessionFactory->writeCSV(pConfig))
		return 0;
	if (!m_MaxLocalIDFactory->writeCSV(pConfig))
		return 0;
	if (!m_BrkUserIDLocalIDFactory->writeCSV(pConfig))
		return 0;
	if (!m_PartClientInsGroupPositionFactory->writeCSV(pConfig))
		return 0;
	if (!m_ClientMarginCombTypeFactory->writeCSV(pConfig))
		return 0;
	if (!m_InstrumentGroupFactory->writeCSV(pConfig))
		return 0;
	if (!m_SGEDeferRateFactory->writeCSV(pConfig))
		return 0;
	if (!m_InvestorTradingRightFactory->writeCSV(pConfig))
		return 0;
	if (!m_UserIPFactory->writeCSV(pConfig))
		return 0;
	if (!m_InvestorOptionFeeFactory->writeCSV(pConfig))
		return 0;
	if (!m_MarketDataFactory->writeCSV(pConfig))
		return 0;
	if (!m_OrderDelayFactory->writeCSV(pConfig))
		return 0;
	if (!m_SystemInfoFactory->writeCSV(pConfig))
		return 0;
	return 1;
}

void CMemoryDB::clear(void)
{
	m_DataSyncStatusFactory->clearAll();
	m_SystemStatusFactory->clearAll();
	m_OrderActionFactory->clearAll();
	m_OrderFactory->clearAll();
	m_TradeFactory->clearAll();
	m_PreOrderFactory->clearAll();
	m_IndexPreOrderFactory->clearAll();
	m_InvestorPositionFactory->clearAll();
	m_InvestorAccountFactory->clearAll();
	m_InvestorAccountDepositFactory->clearAll();
	m_ExchangeFactory->clearAll();
	m_SeatFactory->clearAll();
	m_InstrumentFactory->clearAll();
	m_CmbInstrumentDetailFactory->clearAll();
	m_ClientTradingIDFactory->clearAll();
	m_InvestorFactory->clearAll();
	m_InvestorMarginFactory->clearAll();
	m_InvestorFeeFactory->clearAll();
	m_UserFactory->clearAll();
	m_UserInvestorFactory->clearAll();
	m_OrderInsertFailedFactory->clearAll();
	m_UserTradingRightFactory->clearAll();
	m_CurrentTimeFactory->clearAll();
	m_UserSessionFactory->clearAll();
	m_MaxLocalIDFactory->clearAll();
	m_BrkUserIDLocalIDFactory->clearAll();
	m_PartClientInsGroupPositionFactory->clearAll();
	m_ClientMarginCombTypeFactory->clearAll();
	m_InstrumentGroupFactory->clearAll();
	m_SGEDeferRateFactory->clearAll();
	m_InvestorTradingRightFactory->clearAll();
	m_UserIPFactory->clearAll();
	m_InvestorOptionFeeFactory->clearAll();
	m_MarketDataFactory->clearAll();
	m_OrderDelayFactory->clearAll();
	m_SystemInfoFactory->clearAll();
}

void CMemoryDB::linkAll(void)
{
	m_OrderActionFactory->linkAllOrder(m_OrderFactory);
	m_OrderActionFactory->linkAllPreOrder(m_PreOrderFactory);
	m_OrderFactory->linkAllInvestor(m_InvestorFactory);
	m_OrderFactory->linkAllClientTradingID(m_ClientTradingIDFactory);
	m_OrderFactory->linkAllInvestorAccount(m_InvestorAccountFactory);
	m_OrderFactory->linkAllInvestorPosition(m_InvestorPositionFactory);
	m_OrderFactory->linkAllInstrument(m_InstrumentFactory);
	m_OrderFactory->linkAllInvestorMargin(m_InvestorMarginFactory);
	m_OrderFactory->linkAllInvestorFee(m_InvestorFeeFactory);
	m_OrderFactory->linkAllInvestorOptionFee(m_InvestorOptionFeeFactory);
	m_OrderFactory->linkAllClientGroupPosition(m_PartClientInsGroupPositionFactory);
	m_PreOrderFactory->linkAllInvestor(m_InvestorFactory);
	m_PreOrderFactory->linkAllClientTradingID(m_ClientTradingIDFactory);
	m_PreOrderFactory->linkAllInvestorAccount(m_InvestorAccountFactory);
	m_PreOrderFactory->linkAllInvestorPosition(m_InvestorPositionFactory);
	m_PreOrderFactory->linkAllInstrument(m_InstrumentFactory);
	m_PreOrderFactory->linkAllInvestorMargin(m_InvestorMarginFactory);
	m_PreOrderFactory->linkAllInvestorFee(m_InvestorFeeFactory);
	m_PreOrderFactory->linkAllInvestorOptionFee(m_InvestorOptionFeeFactory);
	m_PreOrderFactory->linkAllClientGroupPosition(m_PartClientInsGroupPositionFactory);
	m_IndexPreOrderFactory->linkAllInvestor(m_InvestorFactory);
	m_IndexPreOrderFactory->linkAllClientTradingID(m_ClientTradingIDFactory);
	m_IndexPreOrderFactory->linkAllInvestorAccount(m_InvestorAccountFactory);
	m_IndexPreOrderFactory->linkAllInstrument(m_InstrumentFactory);
	m_IndexPreOrderFactory->linkAllInvestorMargin(m_InvestorMarginFactory);
	m_IndexPreOrderFactory->linkAllInvestorFee(m_InvestorFeeFactory);
	m_IndexPreOrderFactory->linkAllClientGroupPosition(m_PartClientInsGroupPositionFactory);
	m_ClientTradingIDFactory->linkAllInvestorAccount(m_InvestorAccountFactory);
	m_OrderInsertFailedFactory->linkAllInvestorAccount(m_InvestorAccountFactory);
	m_OrderInsertFailedFactory->linkAllInvestorPosition(m_InvestorPositionFactory);
	m_OrderInsertFailedFactory->linkAllInstrument(m_InstrumentFactory);
	m_OrderInsertFailedFactory->linkAllInvestorMargin(m_InvestorMarginFactory);
	m_OrderInsertFailedFactory->linkAllInvestorFee(m_InvestorFeeFactory);
	m_BrkUserIDLocalIDFactory->linkAllPreOrder(m_PreOrderFactory);
}

