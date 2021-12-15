!!enter XTP!!
!!function!!
int isInitPackage(char *usage)
{
	if (strcmp(usage,"exchangeInit")==0)
	{
		return 1;
	}
	return 0;
}

char *getTableName(char *name)
{
	return name+4;
}
!!endfunction!!
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

!!travel packages!!
!!if isInitPackage(@usage)!!
!!let tableName=getTableName(@name)!!
	///初始化!!@comment!!
	///@param	p!!@tableName!!	要初始化的!!@comment!!信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool init!!@tableName!!(CWriteable!!@tableName!! *p!!@tableName!!,const TSessionRef &sessionRef,CTransaction *pTransaction);

!!endif!!
!!next!!
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
	virtual bool RspQryExDiffTime(CExchTimeDiffField *pExchTimeDiffField,const TSessionRef &sessionRef,CTransaction *pTransaction);
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
!!leave!!
