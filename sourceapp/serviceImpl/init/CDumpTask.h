/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company 上海量投网络科技有限公司
///@file CDumpTask.h
///@brief	定义了类CDumpTask和相关类
///@history 
///20091203	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CDUMPTASK_H
#define CDUMPTASK_H

#include "CLinkTask.h"
#include "databaseData.h"


/////////////////////////////////////////////////////////////////////////
///CDumpDataSyncStatusTask是一个完成输出数据同步状态表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpDataSyncStatusTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpDataSyncStatusTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpDataSyncStatusTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CDataSyncStatusFactory *m_pFactory;
	FILE *m_output;
	CWriteableDataSyncStatus *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpSystemStatusTask是一个完成输出QDP状态表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpSystemStatusTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpSystemStatusTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpSystemStatusTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CSystemStatusFactory *m_pFactory;
	FILE *m_output;
	CWriteableSystemStatus *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpOrderActionTask是一个完成输出报单操作的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpOrderActionTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpOrderActionTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpOrderActionTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	COrderActionFactory *m_pFactory;
	FILE *m_output;
	CWriteableOrderAction *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpOrderTask是一个完成输出委托表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpOrderTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpOrderTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpOrderTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	COrderFactory *m_pFactory;
	FILE *m_output;
	CWriteableOrder *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpTradeTask是一个完成输出成交表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpTradeTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpTradeTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpTradeTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CTradeFactory *m_pFactory;
	FILE *m_output;
	CWriteableTrade *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpPreOrderTask是一个完成输出预委托表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpPreOrderTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpPreOrderTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpPreOrderTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CPreOrderFactory *m_pFactory;
	FILE *m_output;
	CWriteablePreOrder *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpIndexPreOrderTask是一个完成输出索引预委托表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpIndexPreOrderTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpIndexPreOrderTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpIndexPreOrderTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CIndexPreOrderFactory *m_pFactory;
	FILE *m_output;
	CWriteableIndexPreOrder *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorPositionTask是一个完成输出持仓表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorPositionTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpInvestorPositionTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpInvestorPositionTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CInvestorPositionFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestorPosition *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorAccountTask是一个完成输出账户实时资金表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorAccountTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpInvestorAccountTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpInvestorAccountTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CInvestorAccountFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestorAccount *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorAccountDepositTask是一个完成输出账户实时出入金表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorAccountDepositTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpInvestorAccountDepositTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpInvestorAccountDepositTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CInvestorAccountDepositFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestorAccountDeposit *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpExchangeTask是一个完成输出交易所表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpExchangeTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpExchangeTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpExchangeTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CExchangeFactory *m_pFactory;
	FILE *m_output;
	CWriteableExchange *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpSeatTask是一个完成输出下单席位表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpSeatTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpSeatTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpSeatTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CSeatFactory *m_pFactory;
	FILE *m_output;
	CWriteableSeat *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInstrumentTask是一个完成输出期货合约表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInstrumentTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpInstrumentTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpInstrumentTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CInstrumentFactory *m_pFactory;
	FILE *m_output;
	CWriteableInstrument *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpCmbInstrumentDetailTask是一个完成输出期货组合合约明细表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpCmbInstrumentDetailTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpCmbInstrumentDetailTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpCmbInstrumentDetailTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CCmbInstrumentDetailFactory *m_pFactory;
	FILE *m_output;
	CWriteableCmbInstrumentDetail *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpClientTradingIDTask是一个完成输出交易所客户编码表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpClientTradingIDTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpClientTradingIDTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpClientTradingIDTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CClientTradingIDFactory *m_pFactory;
	FILE *m_output;
	CWriteableClientTradingID *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorTask是一个完成输出投资者信息表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpInvestorTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpInvestorTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CInvestorFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestor *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorMarginTask是一个完成输出客户期货保证金率表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorMarginTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpInvestorMarginTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpInvestorMarginTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CInvestorMarginFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestorMargin *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorFeeTask是一个完成输出客户手续费率表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorFeeTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpInvestorFeeTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpInvestorFeeTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CInvestorFeeFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestorFee *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpUserTask是一个完成输出用户表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpUserTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpUserTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpUserTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CUserFactory *m_pFactory;
	FILE *m_output;
	CWriteableUser *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpUserInvestorTask是一个完成输出用户投资者关系表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpUserInvestorTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpUserInvestorTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpUserInvestorTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CUserInvestorFactory *m_pFactory;
	FILE *m_output;
	CWriteableUserInvestor *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpOrderInsertFailedTask是一个完成输出错单表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpOrderInsertFailedTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpOrderInsertFailedTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpOrderInsertFailedTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	COrderInsertFailedFactory *m_pFactory;
	FILE *m_output;
	CWriteableOrderInsertFailed *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpUserTradingRightTask是一个完成输出用户交易权限表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpUserTradingRightTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpUserTradingRightTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpUserTradingRightTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CUserTradingRightFactory *m_pFactory;
	FILE *m_output;
	CWriteableUserTradingRight *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpCurrentTimeTask是一个完成输出当前时间的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpCurrentTimeTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpCurrentTimeTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpCurrentTimeTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CCurrentTimeFactory *m_pFactory;
	FILE *m_output;
	CWriteableCurrentTime *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpUserSessionTask是一个完成输出交易员在线会话的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpUserSessionTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpUserSessionTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpUserSessionTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CUserSessionFactory *m_pFactory;
	FILE *m_output;
	CWriteableUserSession *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpMaxLocalIDTask是一个完成输出最大本地报单号的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpMaxLocalIDTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpMaxLocalIDTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpMaxLocalIDTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CMaxLocalIDFactory *m_pFactory;
	FILE *m_output;
	CWriteableMaxLocalID *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpBrkUserIDLocalIDTask是一个完成输出用户本地报单号的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpBrkUserIDLocalIDTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpBrkUserIDLocalIDTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpBrkUserIDLocalIDTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CBrkUserIDLocalIDFactory *m_pFactory;
	FILE *m_output;
	CWriteableBrkUserIDLocalID *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpPartClientInsGroupPositionTask是一个完成输出客户合约组持仓表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpPartClientInsGroupPositionTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpPartClientInsGroupPositionTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpPartClientInsGroupPositionTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CPartClientInsGroupPositionFactory *m_pFactory;
	FILE *m_output;
	CWriteablePartClientInsGroupPosition *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpClientMarginCombTypeTask是一个完成输出交易编码组合保证金类型的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpClientMarginCombTypeTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpClientMarginCombTypeTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpClientMarginCombTypeTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CClientMarginCombTypeFactory *m_pFactory;
	FILE *m_output;
	CWriteableClientMarginCombType *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInstrumentGroupTask是一个完成输出合约和合约组关系的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInstrumentGroupTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpInstrumentGroupTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpInstrumentGroupTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CInstrumentGroupFactory *m_pFactory;
	FILE *m_output;
	CWriteableInstrumentGroup *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpSGEDeferRateTask是一个完成输出金交所递延费率表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpSGEDeferRateTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpSGEDeferRateTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpSGEDeferRateTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CSGEDeferRateFactory *m_pFactory;
	FILE *m_output;
	CWriteableSGEDeferRate *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorTradingRightTask是一个完成输出投资者交易权限表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorTradingRightTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpInvestorTradingRightTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpInvestorTradingRightTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CInvestorTradingRightFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestorTradingRight *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpUserIPTask是一个完成输出交易员IP地址的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpUserIPTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpUserIPTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpUserIPTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CUserIPFactory *m_pFactory;
	FILE *m_output;
	CWriteableUserIP *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorOptionFeeTask是一个完成输出客户期权手续费率表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorOptionFeeTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpInvestorOptionFeeTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpInvestorOptionFeeTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CInvestorOptionFeeFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestorOptionFee *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpMarketDataTask是一个完成输出实时行情表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpMarketDataTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpMarketDataTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpMarketDataTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CMarketDataFactory *m_pFactory;
	FILE *m_output;
	CWriteableMarketData *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpOrderDelayTask是一个完成输出委托延迟表的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpOrderDelayTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpOrderDelayTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpOrderDelayTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	COrderDelayFactory *m_pFactory;
	FILE *m_output;
	CWriteableOrderDelay *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpSystemInfoTask是一个完成输出QDP系统信息的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpSystemInfoTask: public ITask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpSystemInfoTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	~CDumpSystemInfoTask(void);
	
	///运行一步
	///@param	pCost	返回本步完成的权值
	///@return	true表示需要继续运行，false表示不需要继续运行
	virtual bool step(int *pCost);

private:
	CSystemInfoFactory *m_pFactory;
	FILE *m_output;
	CWriteableSystemInfo *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpTask是一个完成输出整个内存数据库的任务类
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpTask: public CLinkTask
{
public:
	///构造函数
	///@param	pConfig	使用的配置文件
	///@param	pDB	使用的内存数据库
	CDumpTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///析构函数
	virtual ~CDumpTask(void)
	{
	}
};


#endif
