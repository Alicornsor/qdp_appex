/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company 上海量投网络科技有限公司
///@file CDumpLog.h
///@brief定义了类CDumpLog
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CDUMPLOG_H
#define CDUMPLOG_H

#include "CMemoryDB.h"

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusDumpTrigger是操作数据同步状态表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusDumpTrigger: public CDataSyncStatusActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CDataSyncStatusDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CDataSyncStatusDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pDataSyncStatus	要加入的DataSyncStatus
	virtual void beforeAdd(CWriteableDataSyncStatus *pDataSyncStatus);
	
	///更新前触发	
	///@param	pDataSyncStatus	被刷新的CDataSyncStatus
	///@param	pNewDataSyncStatus	新的值
	virtual void beforeUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus);
	
	///删除前触发
	///@param	pDataSyncStatus	要删除的CDataSyncStatus
	virtual void beforeRemove(CDataSyncStatus *pDataSyncStatus);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusDumpTrigger是操作QDP状态表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusDumpTrigger: public CSystemStatusActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CSystemStatusDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CSystemStatusDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pSystemStatus	要加入的SystemStatus
	virtual void beforeAdd(CWriteableSystemStatus *pSystemStatus);
	
	///更新前触发	
	///@param	pSystemStatus	被刷新的CSystemStatus
	///@param	pNewSystemStatus	新的值
	virtual void beforeUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus);
	
	///删除前触发
	///@param	pSystemStatus	要删除的CSystemStatus
	virtual void beforeRemove(CSystemStatus *pSystemStatus);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///COrderActionDumpTrigger是操作报单操作时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionDumpTrigger: public COrderActionActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	COrderActionDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~COrderActionDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pOrderAction	要加入的OrderAction
	virtual void beforeAdd(CWriteableOrderAction *pOrderAction);
	
	///更新前触发	
	///@param	pOrderAction	被刷新的COrderAction
	///@param	pNewOrderAction	新的值
	virtual void beforeUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction);
	
	///删除前触发
	///@param	pOrderAction	要删除的COrderAction
	virtual void beforeRemove(COrderAction *pOrderAction);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///COrderDumpTrigger是操作委托表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDumpTrigger: public COrderActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	COrderDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~COrderDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pOrder	要加入的Order
	virtual void beforeAdd(CWriteableOrder *pOrder);
	
	///更新前触发	
	///@param	pOrder	被刷新的COrder
	///@param	pNewOrder	新的值
	virtual void beforeUpdate(COrder *pOrder, CWriteableOrder *pNewOrder);
	
	///删除前触发
	///@param	pOrder	要删除的COrder
	virtual void beforeRemove(COrder *pOrder);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CTradeDumpTrigger是操作成交表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeDumpTrigger: public CTradeActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CTradeDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CTradeDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pTrade	要加入的Trade
	virtual void beforeAdd(CWriteableTrade *pTrade);
	
	///更新前触发	
	///@param	pTrade	被刷新的CTrade
	///@param	pNewTrade	新的值
	virtual void beforeUpdate(CTrade *pTrade, CWriteableTrade *pNewTrade);
	
	///删除前触发
	///@param	pTrade	要删除的CTrade
	virtual void beforeRemove(CTrade *pTrade);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderDumpTrigger是操作预委托表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderDumpTrigger: public CPreOrderActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CPreOrderDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CPreOrderDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pPreOrder	要加入的PreOrder
	virtual void beforeAdd(CWriteablePreOrder *pPreOrder);
	
	///更新前触发	
	///@param	pPreOrder	被刷新的CPreOrder
	///@param	pNewPreOrder	新的值
	virtual void beforeUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder);
	
	///删除前触发
	///@param	pPreOrder	要删除的CPreOrder
	virtual void beforeRemove(CPreOrder *pPreOrder);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderDumpTrigger是操作索引预委托表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderDumpTrigger: public CIndexPreOrderActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CIndexPreOrderDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CIndexPreOrderDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pIndexPreOrder	要加入的IndexPreOrder
	virtual void beforeAdd(CWriteableIndexPreOrder *pIndexPreOrder);
	
	///更新前触发	
	///@param	pIndexPreOrder	被刷新的CIndexPreOrder
	///@param	pNewIndexPreOrder	新的值
	virtual void beforeUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder);
	
	///删除前触发
	///@param	pIndexPreOrder	要删除的CIndexPreOrder
	virtual void beforeRemove(CIndexPreOrder *pIndexPreOrder);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionDumpTrigger是操作持仓表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionDumpTrigger: public CInvestorPositionActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CInvestorPositionDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CInvestorPositionDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pInvestorPosition	要加入的InvestorPosition
	virtual void beforeAdd(CWriteableInvestorPosition *pInvestorPosition);
	
	///更新前触发	
	///@param	pInvestorPosition	被刷新的CInvestorPosition
	///@param	pNewInvestorPosition	新的值
	virtual void beforeUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition);
	
	///删除前触发
	///@param	pInvestorPosition	要删除的CInvestorPosition
	virtual void beforeRemove(CInvestorPosition *pInvestorPosition);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDumpTrigger是操作账户实时资金表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDumpTrigger: public CInvestorAccountActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CInvestorAccountDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CInvestorAccountDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pInvestorAccount	要加入的InvestorAccount
	virtual void beforeAdd(CWriteableInvestorAccount *pInvestorAccount);
	
	///更新前触发	
	///@param	pInvestorAccount	被刷新的CInvestorAccount
	///@param	pNewInvestorAccount	新的值
	virtual void beforeUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount);
	
	///删除前触发
	///@param	pInvestorAccount	要删除的CInvestorAccount
	virtual void beforeRemove(CInvestorAccount *pInvestorAccount);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositDumpTrigger是操作账户实时出入金表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositDumpTrigger: public CInvestorAccountDepositActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CInvestorAccountDepositDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CInvestorAccountDepositDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pInvestorAccountDeposit	要加入的InvestorAccountDeposit
	virtual void beforeAdd(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit);
	
	///更新前触发	
	///@param	pInvestorAccountDeposit	被刷新的CInvestorAccountDeposit
	///@param	pNewInvestorAccountDeposit	新的值
	virtual void beforeUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit);
	
	///删除前触发
	///@param	pInvestorAccountDeposit	要删除的CInvestorAccountDeposit
	virtual void beforeRemove(CInvestorAccountDeposit *pInvestorAccountDeposit);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CExchangeDumpTrigger是操作交易所表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeDumpTrigger: public CExchangeActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CExchangeDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CExchangeDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pExchange	要加入的Exchange
	virtual void beforeAdd(CWriteableExchange *pExchange);
	
	///更新前触发	
	///@param	pExchange	被刷新的CExchange
	///@param	pNewExchange	新的值
	virtual void beforeUpdate(CExchange *pExchange, CWriteableExchange *pNewExchange);
	
	///删除前触发
	///@param	pExchange	要删除的CExchange
	virtual void beforeRemove(CExchange *pExchange);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CSeatDumpTrigger是操作下单席位表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatDumpTrigger: public CSeatActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CSeatDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CSeatDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pSeat	要加入的Seat
	virtual void beforeAdd(CWriteableSeat *pSeat);
	
	///更新前触发	
	///@param	pSeat	被刷新的CSeat
	///@param	pNewSeat	新的值
	virtual void beforeUpdate(CSeat *pSeat, CWriteableSeat *pNewSeat);
	
	///删除前触发
	///@param	pSeat	要删除的CSeat
	virtual void beforeRemove(CSeat *pSeat);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentDumpTrigger是操作期货合约表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentDumpTrigger: public CInstrumentActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CInstrumentDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CInstrumentDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pInstrument	要加入的Instrument
	virtual void beforeAdd(CWriteableInstrument *pInstrument);
	
	///更新前触发	
	///@param	pInstrument	被刷新的CInstrument
	///@param	pNewInstrument	新的值
	virtual void beforeUpdate(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument);
	
	///删除前触发
	///@param	pInstrument	要删除的CInstrument
	virtual void beforeRemove(CInstrument *pInstrument);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailDumpTrigger是操作期货组合合约明细表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailDumpTrigger: public CCmbInstrumentDetailActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CCmbInstrumentDetailDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CCmbInstrumentDetailDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pCmbInstrumentDetail	要加入的CmbInstrumentDetail
	virtual void beforeAdd(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail);
	
	///更新前触发	
	///@param	pCmbInstrumentDetail	被刷新的CCmbInstrumentDetail
	///@param	pNewCmbInstrumentDetail	新的值
	virtual void beforeUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail);
	
	///删除前触发
	///@param	pCmbInstrumentDetail	要删除的CCmbInstrumentDetail
	virtual void beforeRemove(CCmbInstrumentDetail *pCmbInstrumentDetail);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDDumpTrigger是操作交易所客户编码表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDDumpTrigger: public CClientTradingIDActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CClientTradingIDDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CClientTradingIDDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pClientTradingID	要加入的ClientTradingID
	virtual void beforeAdd(CWriteableClientTradingID *pClientTradingID);
	
	///更新前触发	
	///@param	pClientTradingID	被刷新的CClientTradingID
	///@param	pNewClientTradingID	新的值
	virtual void beforeUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID);
	
	///删除前触发
	///@param	pClientTradingID	要删除的CClientTradingID
	virtual void beforeRemove(CClientTradingID *pClientTradingID);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorDumpTrigger是操作投资者信息表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorDumpTrigger: public CInvestorActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CInvestorDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CInvestorDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pInvestor	要加入的Investor
	virtual void beforeAdd(CWriteableInvestor *pInvestor);
	
	///更新前触发	
	///@param	pInvestor	被刷新的CInvestor
	///@param	pNewInvestor	新的值
	virtual void beforeUpdate(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor);
	
	///删除前触发
	///@param	pInvestor	要删除的CInvestor
	virtual void beforeRemove(CInvestor *pInvestor);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginDumpTrigger是操作客户期货保证金率表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginDumpTrigger: public CInvestorMarginActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CInvestorMarginDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CInvestorMarginDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pInvestorMargin	要加入的InvestorMargin
	virtual void beforeAdd(CWriteableInvestorMargin *pInvestorMargin);
	
	///更新前触发	
	///@param	pInvestorMargin	被刷新的CInvestorMargin
	///@param	pNewInvestorMargin	新的值
	virtual void beforeUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin);
	
	///删除前触发
	///@param	pInvestorMargin	要删除的CInvestorMargin
	virtual void beforeRemove(CInvestorMargin *pInvestorMargin);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeDumpTrigger是操作客户手续费率表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeDumpTrigger: public CInvestorFeeActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CInvestorFeeDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CInvestorFeeDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pInvestorFee	要加入的InvestorFee
	virtual void beforeAdd(CWriteableInvestorFee *pInvestorFee);
	
	///更新前触发	
	///@param	pInvestorFee	被刷新的CInvestorFee
	///@param	pNewInvestorFee	新的值
	virtual void beforeUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee);
	
	///删除前触发
	///@param	pInvestorFee	要删除的CInvestorFee
	virtual void beforeRemove(CInvestorFee *pInvestorFee);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CUserDumpTrigger是操作用户表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserDumpTrigger: public CUserActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CUserDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CUserDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pUser	要加入的User
	virtual void beforeAdd(CWriteableUser *pUser);
	
	///更新前触发	
	///@param	pUser	被刷新的CUser
	///@param	pNewUser	新的值
	virtual void beforeUpdate(CUser *pUser, CWriteableUser *pNewUser);
	
	///删除前触发
	///@param	pUser	要删除的CUser
	virtual void beforeRemove(CUser *pUser);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorDumpTrigger是操作用户投资者关系表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorDumpTrigger: public CUserInvestorActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CUserInvestorDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CUserInvestorDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pUserInvestor	要加入的UserInvestor
	virtual void beforeAdd(CWriteableUserInvestor *pUserInvestor);
	
	///更新前触发	
	///@param	pUserInvestor	被刷新的CUserInvestor
	///@param	pNewUserInvestor	新的值
	virtual void beforeUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor);
	
	///删除前触发
	///@param	pUserInvestor	要删除的CUserInvestor
	virtual void beforeRemove(CUserInvestor *pUserInvestor);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedDumpTrigger是操作错单表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedDumpTrigger: public COrderInsertFailedActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	COrderInsertFailedDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~COrderInsertFailedDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pOrderInsertFailed	要加入的OrderInsertFailed
	virtual void beforeAdd(CWriteableOrderInsertFailed *pOrderInsertFailed);
	
	///更新前触发	
	///@param	pOrderInsertFailed	被刷新的COrderInsertFailed
	///@param	pNewOrderInsertFailed	新的值
	virtual void beforeUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed);
	
	///删除前触发
	///@param	pOrderInsertFailed	要删除的COrderInsertFailed
	virtual void beforeRemove(COrderInsertFailed *pOrderInsertFailed);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightDumpTrigger是操作用户交易权限表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightDumpTrigger: public CUserTradingRightActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CUserTradingRightDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CUserTradingRightDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pUserTradingRight	要加入的UserTradingRight
	virtual void beforeAdd(CWriteableUserTradingRight *pUserTradingRight);
	
	///更新前触发	
	///@param	pUserTradingRight	被刷新的CUserTradingRight
	///@param	pNewUserTradingRight	新的值
	virtual void beforeUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight);
	
	///删除前触发
	///@param	pUserTradingRight	要删除的CUserTradingRight
	virtual void beforeRemove(CUserTradingRight *pUserTradingRight);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeDumpTrigger是操作当前时间时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeDumpTrigger: public CCurrentTimeActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CCurrentTimeDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CCurrentTimeDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pCurrentTime	要加入的CurrentTime
	virtual void beforeAdd(CWriteableCurrentTime *pCurrentTime);
	
	///更新前触发	
	///@param	pCurrentTime	被刷新的CCurrentTime
	///@param	pNewCurrentTime	新的值
	virtual void beforeUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime);
	
	///删除前触发
	///@param	pCurrentTime	要删除的CCurrentTime
	virtual void beforeRemove(CCurrentTime *pCurrentTime);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionDumpTrigger是操作交易员在线会话时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionDumpTrigger: public CUserSessionActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CUserSessionDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CUserSessionDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pUserSession	要加入的UserSession
	virtual void beforeAdd(CWriteableUserSession *pUserSession);
	
	///更新前触发	
	///@param	pUserSession	被刷新的CUserSession
	///@param	pNewUserSession	新的值
	virtual void beforeUpdate(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession);
	
	///删除前触发
	///@param	pUserSession	要删除的CUserSession
	virtual void beforeRemove(CUserSession *pUserSession);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDDumpTrigger是操作最大本地报单号时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDDumpTrigger: public CMaxLocalIDActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CMaxLocalIDDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CMaxLocalIDDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pMaxLocalID	要加入的MaxLocalID
	virtual void beforeAdd(CWriteableMaxLocalID *pMaxLocalID);
	
	///更新前触发	
	///@param	pMaxLocalID	被刷新的CMaxLocalID
	///@param	pNewMaxLocalID	新的值
	virtual void beforeUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID);
	
	///删除前触发
	///@param	pMaxLocalID	要删除的CMaxLocalID
	virtual void beforeRemove(CMaxLocalID *pMaxLocalID);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDDumpTrigger是操作用户本地报单号时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDDumpTrigger: public CBrkUserIDLocalIDActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CBrkUserIDLocalIDDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CBrkUserIDLocalIDDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pBrkUserIDLocalID	要加入的BrkUserIDLocalID
	virtual void beforeAdd(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID);
	
	///更新前触发	
	///@param	pBrkUserIDLocalID	被刷新的CBrkUserIDLocalID
	///@param	pNewBrkUserIDLocalID	新的值
	virtual void beforeUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID);
	
	///删除前触发
	///@param	pBrkUserIDLocalID	要删除的CBrkUserIDLocalID
	virtual void beforeRemove(CBrkUserIDLocalID *pBrkUserIDLocalID);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionDumpTrigger是操作客户合约组持仓表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionDumpTrigger: public CPartClientInsGroupPositionActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CPartClientInsGroupPositionDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CPartClientInsGroupPositionDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pPartClientInsGroupPosition	要加入的PartClientInsGroupPosition
	virtual void beforeAdd(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition);
	
	///更新前触发	
	///@param	pPartClientInsGroupPosition	被刷新的CPartClientInsGroupPosition
	///@param	pNewPartClientInsGroupPosition	新的值
	virtual void beforeUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition);
	
	///删除前触发
	///@param	pPartClientInsGroupPosition	要删除的CPartClientInsGroupPosition
	virtual void beforeRemove(CPartClientInsGroupPosition *pPartClientInsGroupPosition);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeDumpTrigger是操作交易编码组合保证金类型时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeDumpTrigger: public CClientMarginCombTypeActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CClientMarginCombTypeDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CClientMarginCombTypeDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pClientMarginCombType	要加入的ClientMarginCombType
	virtual void beforeAdd(CWriteableClientMarginCombType *pClientMarginCombType);
	
	///更新前触发	
	///@param	pClientMarginCombType	被刷新的CClientMarginCombType
	///@param	pNewClientMarginCombType	新的值
	virtual void beforeUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType);
	
	///删除前触发
	///@param	pClientMarginCombType	要删除的CClientMarginCombType
	virtual void beforeRemove(CClientMarginCombType *pClientMarginCombType);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupDumpTrigger是操作合约和合约组关系时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupDumpTrigger: public CInstrumentGroupActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CInstrumentGroupDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CInstrumentGroupDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pInstrumentGroup	要加入的InstrumentGroup
	virtual void beforeAdd(CWriteableInstrumentGroup *pInstrumentGroup);
	
	///更新前触发	
	///@param	pInstrumentGroup	被刷新的CInstrumentGroup
	///@param	pNewInstrumentGroup	新的值
	virtual void beforeUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup);
	
	///删除前触发
	///@param	pInstrumentGroup	要删除的CInstrumentGroup
	virtual void beforeRemove(CInstrumentGroup *pInstrumentGroup);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateDumpTrigger是操作金交所递延费率表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateDumpTrigger: public CSGEDeferRateActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CSGEDeferRateDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CSGEDeferRateDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pSGEDeferRate	要加入的SGEDeferRate
	virtual void beforeAdd(CWriteableSGEDeferRate *pSGEDeferRate);
	
	///更新前触发	
	///@param	pSGEDeferRate	被刷新的CSGEDeferRate
	///@param	pNewSGEDeferRate	新的值
	virtual void beforeUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate);
	
	///删除前触发
	///@param	pSGEDeferRate	要删除的CSGEDeferRate
	virtual void beforeRemove(CSGEDeferRate *pSGEDeferRate);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightDumpTrigger是操作投资者交易权限表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightDumpTrigger: public CInvestorTradingRightActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CInvestorTradingRightDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CInvestorTradingRightDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pInvestorTradingRight	要加入的InvestorTradingRight
	virtual void beforeAdd(CWriteableInvestorTradingRight *pInvestorTradingRight);
	
	///更新前触发	
	///@param	pInvestorTradingRight	被刷新的CInvestorTradingRight
	///@param	pNewInvestorTradingRight	新的值
	virtual void beforeUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight);
	
	///删除前触发
	///@param	pInvestorTradingRight	要删除的CInvestorTradingRight
	virtual void beforeRemove(CInvestorTradingRight *pInvestorTradingRight);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CUserIPDumpTrigger是操作交易员IP地址时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPDumpTrigger: public CUserIPActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CUserIPDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CUserIPDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pUserIP	要加入的UserIP
	virtual void beforeAdd(CWriteableUserIP *pUserIP);
	
	///更新前触发	
	///@param	pUserIP	被刷新的CUserIP
	///@param	pNewUserIP	新的值
	virtual void beforeUpdate(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP);
	
	///删除前触发
	///@param	pUserIP	要删除的CUserIP
	virtual void beforeRemove(CUserIP *pUserIP);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeDumpTrigger是操作客户期权手续费率表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeDumpTrigger: public CInvestorOptionFeeActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CInvestorOptionFeeDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CInvestorOptionFeeDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pInvestorOptionFee	要加入的InvestorOptionFee
	virtual void beforeAdd(CWriteableInvestorOptionFee *pInvestorOptionFee);
	
	///更新前触发	
	///@param	pInvestorOptionFee	被刷新的CInvestorOptionFee
	///@param	pNewInvestorOptionFee	新的值
	virtual void beforeUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee);
	
	///删除前触发
	///@param	pInvestorOptionFee	要删除的CInvestorOptionFee
	virtual void beforeRemove(CInvestorOptionFee *pInvestorOptionFee);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataDumpTrigger是操作实时行情表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataDumpTrigger: public CMarketDataActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CMarketDataDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CMarketDataDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pMarketData	要加入的MarketData
	virtual void beforeAdd(CWriteableMarketData *pMarketData);
	
	///更新前触发	
	///@param	pMarketData	被刷新的CMarketData
	///@param	pNewMarketData	新的值
	virtual void beforeUpdate(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData);
	
	///删除前触发
	///@param	pMarketData	要删除的CMarketData
	virtual void beforeRemove(CMarketData *pMarketData);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayDumpTrigger是操作委托延迟表时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayDumpTrigger: public COrderDelayActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	COrderDelayDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~COrderDelayDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pOrderDelay	要加入的OrderDelay
	virtual void beforeAdd(CWriteableOrderDelay *pOrderDelay);
	
	///更新前触发	
	///@param	pOrderDelay	被刷新的COrderDelay
	///@param	pNewOrderDelay	新的值
	virtual void beforeUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay);
	
	///删除前触发
	///@param	pOrderDelay	要删除的COrderDelay
	virtual void beforeRemove(COrderDelay *pOrderDelay);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoDumpTrigger是操作QDP系统信息时的触发器，在变化时进行输出
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoDumpTrigger: public CSystemInfoActionTrigger
{
public:
	///构造方法
	///@param	output	输出用的文件
	///@param	flag	控制输出的具体项，是CREATE_ACTION、DELETE_ACTION和UPDATE_ACTION的或
	CSystemInfoDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///析构方法
	virtual ~CSystemInfoDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///加入前触发
	///@param	pSystemInfo	要加入的SystemInfo
	virtual void beforeAdd(CWriteableSystemInfo *pSystemInfo);
	
	///更新前触发	
	///@param	pSystemInfo	被刷新的CSystemInfo
	///@param	pNewSystemInfo	新的值
	virtual void beforeUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo);
	
	///删除前触发
	///@param	pSystemInfo	要删除的CSystemInfo
	virtual void beforeRemove(CSystemInfo *pSystemInfo);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CDumpLog是一个将所有的修改以Dump方式输出的交易引擎提醒实现
///@author	xuzh
///@version	1.0,20041001
/////////////////////////////////////////////////////////////////////////
class CDumpLog
{
public:
	///构造方法，创建一个输出器
	///@param	pDB	要输出的内存数据库
	///@param	pConfig	配置信息
	CDumpLog(CMemoryDB *pDB, CConfig *pConfig);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CDumpLog(void);

	///启动dump
	void start(void);
	
	///停止dump
	void stop(void);
	
	///是否已经启动
	///@return	1表示已经启动，0表示没有启动
	int isStarted(void);
	
	///输出信息
	///@param	format	信息格式，按照fprintf的要求
	///@param	...	信息的详细内容
	void dumpMsg(char *format,...);

private:
	///输出文件
	FILE *m_DumpOutput;
	
	///内存数据库
	CMemoryDB *m_DB;
	
	///是否已经启动
	int m_Started;
	
	CDataSyncStatusDumpTrigger *m_DataSyncStatusTrigger;
	CSystemStatusDumpTrigger *m_SystemStatusTrigger;
	COrderActionDumpTrigger *m_OrderActionTrigger;
	COrderDumpTrigger *m_OrderTrigger;
	CTradeDumpTrigger *m_TradeTrigger;
	CPreOrderDumpTrigger *m_PreOrderTrigger;
	CIndexPreOrderDumpTrigger *m_IndexPreOrderTrigger;
	CInvestorPositionDumpTrigger *m_InvestorPositionTrigger;
	CInvestorAccountDumpTrigger *m_InvestorAccountTrigger;
	CInvestorAccountDepositDumpTrigger *m_InvestorAccountDepositTrigger;
	CExchangeDumpTrigger *m_ExchangeTrigger;
	CSeatDumpTrigger *m_SeatTrigger;
	CInstrumentDumpTrigger *m_InstrumentTrigger;
	CCmbInstrumentDetailDumpTrigger *m_CmbInstrumentDetailTrigger;
	CClientTradingIDDumpTrigger *m_ClientTradingIDTrigger;
	CInvestorDumpTrigger *m_InvestorTrigger;
	CInvestorMarginDumpTrigger *m_InvestorMarginTrigger;
	CInvestorFeeDumpTrigger *m_InvestorFeeTrigger;
	CUserDumpTrigger *m_UserTrigger;
	CUserInvestorDumpTrigger *m_UserInvestorTrigger;
	COrderInsertFailedDumpTrigger *m_OrderInsertFailedTrigger;
	CUserTradingRightDumpTrigger *m_UserTradingRightTrigger;
	CCurrentTimeDumpTrigger *m_CurrentTimeTrigger;
	CUserSessionDumpTrigger *m_UserSessionTrigger;
	CMaxLocalIDDumpTrigger *m_MaxLocalIDTrigger;
	CBrkUserIDLocalIDDumpTrigger *m_BrkUserIDLocalIDTrigger;
	CPartClientInsGroupPositionDumpTrigger *m_PartClientInsGroupPositionTrigger;
	CClientMarginCombTypeDumpTrigger *m_ClientMarginCombTypeTrigger;
	CInstrumentGroupDumpTrigger *m_InstrumentGroupTrigger;
	CSGEDeferRateDumpTrigger *m_SGEDeferRateTrigger;
	CInvestorTradingRightDumpTrigger *m_InvestorTradingRightTrigger;
	CUserIPDumpTrigger *m_UserIPTrigger;
	CInvestorOptionFeeDumpTrigger *m_InvestorOptionFeeTrigger;
	CMarketDataDumpTrigger *m_MarketDataTrigger;
	COrderDelayDumpTrigger *m_OrderDelayTrigger;
	CSystemInfoDumpTrigger *m_SystemInfoTrigger;
};

#endif
