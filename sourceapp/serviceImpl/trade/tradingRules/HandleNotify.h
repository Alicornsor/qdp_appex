/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file CInitServiceImpl.h
///@brief定义了类CInitServiceImpl
///@history 
///20060113	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CHandleNotify_H
#define CHandleNotify_H

#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "XtpData.h"
#include "errorDefine.h"
#include "CMemoryDB.h"
#include "Flow.h"
#include "XTPPackage.h"
#include "XtpPackageDesc.h"
#include "RuleHandleBase.h"
#include "customDataType.h"

//新增一个触发器类，用于触发初始化数据的检查
//by wangwei,20130510
#ifndef CINIT_CHECK_TRIGGER_CLASS_20130510
#define CINIT_CHECK_TRIGGER_CLASS_20130510

class CInitCheckTrigger : public CSystemStatusActionTrigger
{
public:
	CInitCheckTrigger(CMemoryDB *pDB,CConfig *pConfig)
	{
		m_pDB=pDB;
		m_Config=pConfig;
	}
	~CInitCheckTrigger()
	{
	}
	virtual void afterUpdate(CSystemStatus *pSystemStatus);
private:
	void businessCheck();
	void genError(const char *format,...);
private:	
	CMemoryDB *m_pDB;
	CConfig *m_Config;
	FILE *output;
	int errorCount;
};

#endif

typedef map<CInstrumentIDType,CInvestorPosition *> CSendInstrumentMap;
typedef map<CProductIDType, CInstrumentStatusField *> CProductStatusMap;

/////////////////////////////////////////////////////////////////////////
///CInitServiceImpl是一个完成交易所数据初始化的实现
///@author	xuzh
///@version	1.0,20060113
/////////////////////////////////////////////////////////////////////////
class CHandleNotify : public CRuleHandleBase
{
public:
	///构造函数
	///@param	pDB	本实现使用的内存数据库
	///@param	pErrorEngine	用于报错的错误引擎
	CHandleNotify(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult);
//	bool HandleSeatLoginSuccess(CLoginInfoField *pLoginInfo,const TSessionRef &sessionRef,CTransaction *pTransaction,CSeatIDType  &GetSeatID,COrderLocalIDType  &GetOrderLocalID,vector<CWriteablePreOrder*> &PreOrders);	
	bool HandleSeatDisconnected(CSeatField *pSeat,const TSessionRef &sessionRef,CTransaction *pTransaction);//add by wangwei, 20121222
	bool HandleNtfTimeSync(CCurrentTimeField *pCurrTime,const TSessionRef &sessionRef,CTransaction *pTransaction);
	bool HandleMarketDataLastMatch(CMarketDataLastMatchField *marketDataLastMatchedField,const TSessionRef &sessionRef,CTransaction *pTransaction);
//	bool HandleNtfExapiSteadyStatus(CLifeCycleIDField* pLifeCycleField);
	bool HandleInstrumentStatusUpdate(CInstrumentStatusField* pInstrumentStatusField,bool bSendRtn,CTransaction *pTransaction);
	bool HandleInstrumentStatusUpdateEach(CInstrument* pInstrument,CInstrumentStatusField* pInstrumentStatusField,bool bSendRtn,CTransaction *pTransaction);
//	bool HandleRspQryExInstrument(CInstrumentField* pInstrumentField,const TSessionRef &sessionRef,CTransaction *pTransaction);//add by xuzh,20130502
//	bool HandleRspQryExTradingDay(CExchangeTradingDayField* pExchangeTradingDayField,const TSessionRef &sessionRef,CTransaction *pTransaction);//add by xuzh,20130502
//	bool HandleRspQryExClientPosition(CClientPositionField *pClientPositionField,const TSessionRef &sessionRef,CTransaction *pTransaction);//add by xuzh 20150617
//	bool HandleRspQryExMarketData(CMarketDataField *pMarketDataField,const TSessionRef &sessionRef,CTransaction *pTransaction);//add by xuzh 20150617

	void SendQryMarketData(bool bQuerySettlementPrice = false);

	void CZCEInstrumentStatusUpdate(bool bSendRtn = true);

   //计算浮动盈亏,定时器触发
	void CalcDynamicProfit(CWriteableMarketData *pMarketData,CInstrument *pInstrument,CTransaction *pTransaction);
protected:
   long GetTimeDiff(CWriteableCurrentTime* pCurrTime);
   long GetSecFromString(const char* pTime);
   
   /// 函数 RemoveFaildPreOrder 处理丢失的在途订单。把丢失的订单从预报单表中删除，并插入错单表。
 //  int RemoveFaildPreOrder(CExchangeIDType&  ExchangeID,CSeatIDType&  SeatID,COrderLocalIDType  &OrderLocalID,CTransaction *pTransaction,vector<CWriteablePreOrder*> &PreOrders);
protected:
	CConfig       *m_pConfig;
	CXTPPackage   *m_pPubMessage;
	CErrorEngine  *m_pErrorEngine;
	CWriteableCurrentTime m_LastCalcDynamiceProfitTime;//上次计算浮动盈亏的时间
	long m_nCalcDynamicProfitTimeCycle;//算浮动盈亏的周期，毫秒,默认2000
	bool m_bCalcDynamicProfitSwitch;//计算动态权益开关
	static CInitCheckTrigger *m_initTrigger;
	static int initCount;

	CFutureMoneyPosition* m_pFutureMoneyPosition;
	CBaseAlgorithms baseAlgorithms;

	CProductStatusMap  m_ProductStatusMap;
};



#endif
