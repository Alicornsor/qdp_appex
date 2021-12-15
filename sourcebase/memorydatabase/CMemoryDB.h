/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file CMemoryDB.h
///@brief定义了类CMemoryDB
///@history 
///20121227	hwp	创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CMEMORYDB_H
#define CMEMORYDB_H

#include "CBaseObject.h"
#include "CConfig.h"
#include "BaseDataStruct.h"
#include "databaseFactories.h"
#include "databaseIterators.h"

struct TableStruct
{
	char tableName[100];
	int  reuseID;
};

/*** SIR XXXXX BEGIN ***/
typedef struct MemTableItemInfoTag
{
	int InvestorAccountDepositCurrentMaxItem;
}MemTableItemInfoT, *pMemTableItemInfoT;
/*** SIR XXXXX END ***/

/////////////////////////////////////////////////////////////////////////
///CMemoryDB是一个内存数据库类，包含了所有定义的表信息
///@author	xuzh
///@version	1.0,20050824
/////////////////////////////////////////////////////////////////////////
class CMemoryDB : public CBaseObject
{
public:
	///构造方法，创建内存数据库
	CMemoryDB(void);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CMemoryDB(void);
	
	virtual int isA(char *objectType);
	virtual char *getType(void);
	virtual void output(CLogger *pLogger,int indent=0);

	///进行初始化工作
	///@param	pConfig	初始化时使用的配置信息
	///@return	1表示成功，0表示失败
	virtual int init(CConfig *pConfig,IMemoryAllocator *pAllocator=NULL,bool reuse=false);
	
	///进行数据载入工作
	///@param	pConfig	载入数据时使用的配置信息
	///@return	1表示成功，0表示失败
	virtual int load(CConfig *pConfig);

	///进行数据存储工作
	///@param	pConfig	保存数据时使用的配置信息
	///@return	1表示成功，0表示失败
	virtual int save(CConfig *pConfig);
	
	///清空所有的数据
	///@return	1表示成功，0表示失败
	virtual void clear(void);
	
	///完成所有外键的连接
	virtual void linkAll(void);
	
	
	
	///数据同步状态表表
	CDataSyncStatusFactory *m_DataSyncStatusFactory;
	
	///QDP状态表表
	CSystemStatusFactory *m_SystemStatusFactory;
	
	///报单操作表
	COrderActionFactory *m_OrderActionFactory;
	
	///委托表表
	COrderFactory *m_OrderFactory;
	
	///成交表表
	CTradeFactory *m_TradeFactory;
	
	///预委托表表
	CPreOrderFactory *m_PreOrderFactory;
	
	///索引预委托表表
	CIndexPreOrderFactory *m_IndexPreOrderFactory;
	
	///持仓表表
	CInvestorPositionFactory *m_InvestorPositionFactory;
	
	///账户实时资金表表
	CInvestorAccountFactory *m_InvestorAccountFactory;
	
	///账户实时出入金表表
	CInvestorAccountDepositFactory *m_InvestorAccountDepositFactory;
	
	///交易所表表
	CExchangeFactory *m_ExchangeFactory;
	
	///下单席位表表
	CSeatFactory *m_SeatFactory;
	
	///期货合约表表
	CInstrumentFactory *m_InstrumentFactory;
	
	///期货组合合约明细表表
	CCmbInstrumentDetailFactory *m_CmbInstrumentDetailFactory;
	
	///交易所客户编码表表
	CClientTradingIDFactory *m_ClientTradingIDFactory;
	
	///投资者信息表表
	CInvestorFactory *m_InvestorFactory;
	
	///客户期货保证金率表表
	CInvestorMarginFactory *m_InvestorMarginFactory;
	
	///客户手续费率表表
	CInvestorFeeFactory *m_InvestorFeeFactory;
	
	///用户表表
	CUserFactory *m_UserFactory;
	
	///用户投资者关系表表
	CUserInvestorFactory *m_UserInvestorFactory;
	
	///错单表表
	COrderInsertFailedFactory *m_OrderInsertFailedFactory;
	
	///用户交易权限表表
	CUserTradingRightFactory *m_UserTradingRightFactory;
	
	///当前时间表
	CCurrentTimeFactory *m_CurrentTimeFactory;
	
	///交易员在线会话表
	CUserSessionFactory *m_UserSessionFactory;
	
	///最大本地报单号表
	CMaxLocalIDFactory *m_MaxLocalIDFactory;
	
	///用户本地报单号表
	CBrkUserIDLocalIDFactory *m_BrkUserIDLocalIDFactory;
	
	///客户合约组持仓表表
	CPartClientInsGroupPositionFactory *m_PartClientInsGroupPositionFactory;
	
	///交易编码组合保证金类型表
	CClientMarginCombTypeFactory *m_ClientMarginCombTypeFactory;
	
	///合约和合约组关系表
	CInstrumentGroupFactory *m_InstrumentGroupFactory;
	
	///金交所递延费率表表
	CSGEDeferRateFactory *m_SGEDeferRateFactory;
	
	///投资者交易权限表表
	CInvestorTradingRightFactory *m_InvestorTradingRightFactory;
	
	///交易员IP地址表
	CUserIPFactory *m_UserIPFactory;
	
	///客户期权手续费率表表
	CInvestorOptionFeeFactory *m_InvestorOptionFeeFactory;
	
	///实时行情表表
	CMarketDataFactory *m_MarketDataFactory;
	
	///委托延迟表表
	COrderDelayFactory *m_OrderDelayFactory;
	
	///QDP系统信息表
	CSystemInfoFactory *m_SystemInfoFactory;
	

/*** SIR XXXXX BEGIN ***/
	MemTableItemInfoT m_memTableItemInfo;
/*** SIR XXXXX END ***/

private:
	CFixMem *pMem;		///用来存放表的信息
};

#endif
