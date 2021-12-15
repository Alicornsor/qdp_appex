/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company 上海量投网络科技有限公司
///@file CInitServiceImpl.h
///@brief定义了类CInitServiceImpl
///@history 
///20130701	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CINITSERVICEIMPL_H
#define CINITSERVICEIMPL_H

#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "XtpData.h"
#include "errorDefine.h"
#include "CMemoryDB.h"
#include "tradingTools.h"
#include "baseAlgorithms.h"
#include "HandleNotify.h"

/////////////////////////////////////////////////////////////////////////
///CInitServiceImpl是一个完成交易所数据初始化的实现
///@author	hwp
///@version	1.0,20130701
/////////////////////////////////////////////////////////////////////////
class CInitServiceImpl
{
public:
	///构造函数
	///@param	pDB	本实现使用的内存数据库
	///@param	pErrorEngine	用于报错的错误引擎
	CInitServiceImpl(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CHandleNotify *pHandleNotify);

	///初始化交易所
	///@param	pExchange	要初始化的交易所信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initExchange(CWriteableExchange *pExchange,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化席位
	///@param	pSeat	要初始化的席位信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initSeat(CWriteableSeat *pSeat,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化用户
	///@param	pUser	要初始化的用户信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initUser(CWriteableUser *pUser,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化投资者
	///@param	pInvestor	要初始化的投资者信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initInvestor(CWriteableInvestor *pInvestor,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化交易编码
	///@param	pClientTradingID	要初始化的交易编码信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initClientTradingID(CWriteableClientTradingID *pClientTradingID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化用户投资者关系
	///@param	pUserInvestor	要初始化的用户投资者关系信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initUserInvestor(CWriteableUserInvestor *pUserInvestor,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化用户交易权限
	///@param	pUserTradingRight	要初始化的用户交易权限信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initUserTradingRight(CWriteableUserTradingRight *pUserTradingRight,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化投资者资金账户
	///@param	pInvestorAccount	要初始化的投资者资金账户信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initInvestorAccount(CWriteableInvestorAccount *pInvestorAccount,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化合约
	///@param	pInstrument	要初始化的合约信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initInstrument(CWriteableInstrument *pInstrument,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化投资者保证金率
	///@param	pInvestorMargin	要初始化的投资者保证金率信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initInvestorMargin(CWriteableInvestorMargin *pInvestorMargin,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化投资者手续费
	///@param	pInvestorFee	要初始化的投资者手续费信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initInvestorFee(CWriteableInvestorFee *pInvestorFee,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化投资者持仓
	///@param	pInvestorPosition	要初始化的投资者持仓信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initInvestorPosition(CWriteableInvestorPosition *pInvestorPosition,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化系统状态
	///@param	pSystemStatus	要初始化的系统状态信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initSystemStatus(CWriteableSystemStatus *pSystemStatus,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化合约和合约组关系
	///@param	pInstrumentGroup	要初始化的合约和合约组关系信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initInstrumentGroup(CWriteableInstrumentGroup *pInstrumentGroup,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化交易编码组合保证金类型
	///@param	pClientMarginCombType	要初始化的交易编码组合保证金类型信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initClientMarginCombType(CWriteableClientMarginCombType *pClientMarginCombType,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化金交所递延费率信息表
	///@param	pSGEDeferRate	要初始化的金交所递延费率信息表信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initSGEDeferRate(CWriteableSGEDeferRate *pSGEDeferRate,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化组合合约明细应答
	///@param	pCmbInstrumentDetail	要初始化的组合合约明细应答信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initCmbInstrumentDetail(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化投资者交易权限
	///@param	pInvestorTradingRight	要初始化的投资者交易权限信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initInvestorTradingRight(CWriteableInvestorTradingRight *pInvestorTradingRight,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化交易员IP
	///@param	pUserIP	要初始化的交易员IP信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initUserIP(CWriteableUserIP *pUserIP,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化投资者期权手续费
	///@param	pInvestorOptionFee	要初始化的投资者期权手续费信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initInvestorOptionFee(CWriteableInvestorOptionFee *pInvestorOptionFee,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///初始化QDP系统信息表
	///@param	pSystemInfo	要初始化的QDP系统信息表信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initSystemInfo(CWriteableSystemInfo *pSystemInfo,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///开始交易所数据同步
	///@param	TradingDay	交易日
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool DataSyncStart(CDateType &TradingDay,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///结束交易所数据同步
	///@param	TradingDay	交易日
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool DataSyncEnd(CDateType &TradingDay,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///交易所数据同步状态切换
	///@param	ExchangeID	交易所编号
	///@param	NewStatus	新的状态
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool DataSyncStatusUpdate(CDataSyncStatusType &NewStatus,const TSessionRef &sessionRef,CTransaction *pTransaction);

	virtual bool RspQryExInstrument(CInstrumentField *pInstrumentField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQryExTradingDay(CExchangeTradingDayField *pExchangeTradingDayField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQryExInvestorPosition(CInvestorPositionField *pInvestorPositionField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQryExMarketData(CMarketDataField *pMarketDataField,const TSessionRef &sessionRef,CTransaction *pTransaction);	
	virtual bool RspQryExCapitalData(CExCapitalDataField *pExCapitalDataField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQueryExCmbInstrumentDetail(CCmbInstrumentDetailField *pCmbInstrumentDetailField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	
protected:
	///检查是否超级会话
	///@param	sessionRef	会话引用
	///@return	true表示是，false表示否
	bool isSuperSession(const TSessionRef &sessionRef);
	
	///交易所数据同步前处理
	///@param	pTransaction	本处理属于的事务
	virtual void beforeDataSync(CTransaction *pTransaction);
	
	///交易所数据同步后处理
	///@param	pTransaction	本处理属于的事务
	virtual void afterDataSync(CTransaction *pTransaction);
	
protected:
	CConfig *m_Config;
	CMemoryDB *m_DB;
	CErrorEngine *m_ErrorEngine;
	CBaseAlgorithms baseAlgorithm;
	CHandleNotify *m_pHandleNotify;
};

#ifdef DEBUG_NOT_LOG
void increaseCount(void);
#endif

#endif
