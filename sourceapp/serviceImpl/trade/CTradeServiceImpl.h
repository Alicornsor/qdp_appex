/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file CInitServiceImpl.h
///@brief定义了类CInitServiceImpl
///@history 
///20060113	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CTRADESERVICEIMPL_H
#define CTRADESERVICEIMPL_H

#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "XtpData.h"
#include "errorDefine.h"
#include "CMemoryDB.h"
#include "CDate.h"
#include "Flow.h"
#include "XTPPackage.h"
#include "XtpPackageDesc.h"
#include "HandleOrder.h"
#include "HandleNotify.h"
#include "HandleTrade.h"
#include "HandleOrderAction.h"

#include "HandleFutureOrder.h"
#include "HandleFutureTrade.h"


#include "BaseExchApi.h"
/////////////////////////////////////////////////////////////////////////
///CInitServiceImpl是一个完成交易所数据初始化的实现
///@author	xuzh
///@version	1.0,20060113
/////////////////////////////////////////////////////////////////////////

class TPosi
{
public:
	CBrokerIDType     BrokerID;
	CInvestorIDType   InvestorID;
	CExchangeIDType   ExchangeID;
	CInstrumentIDType InstrumentID;
	CHedgeFlagType    HedgeFlag;
	CDirectionType	  Direction;
	bool operator > (const TPosi &m)const
	{
		if (BrokerID > m.BrokerID) 
		{
			return true;
		}
		else if (BrokerID < m.BrokerID)
		{
			return false;
		}
		else
		{
			if(InvestorID > m.InvestorID)
			{
				return true;
			}
			else if(InvestorID < m.InvestorID)
			{
				return false;
			}
			else
			{
				if (ExchangeID > m.ExchangeID)
				{
					return true;
				}
				else if (ExchangeID < m.ExchangeID)
				{
					return false;
				}
				else
				{
					if(InstrumentID > m.InstrumentID)
					{
						return true;
					}
					else if(InstrumentID < m.InstrumentID)
					{
						return false;
					}
					else
					{
						if(HedgeFlag > m.HedgeFlag)
						{
							return true;
						}
						else if (HedgeFlag < m.HedgeFlag)
						{
							return false;
						}
						else
						{
							if (Direction > m.Direction)
							{
								return true;
							}
							else
							{
								return false;
							}
						}
					}
				}
			}
		}
	}
};

//综合持仓队列
typedef map<TPosi, CMoneyType, greater<TPosi> >	CPosiMap;

class CTradeServiceImpl
{
public:
	///构造函数
	///@param	pDB	本实现使用的内存数据库
	///@param	pErrorEngine	用于报错的错误引擎
	CTradeServiceImpl(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult);

	///初始化交易所
	///@param	pExchange	要初始化的交易所信息
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool initExchange(CWriteableExchange *pExchange,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool ReqOrderInsert(CXTPPackage *pPackage,const TSessionRef &sessionRef);
	virtual bool ReqOrderAction(CWriteableOrderAction *pOrderAction,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspOrderInsert(CXTPPackage *pPackage,const TSessionRef &sessionRef);
	virtual bool RspOrderAction(COrderField *pRspOrder,CWriteableOrderAction *pOrderAction,COrderActionField* pActField,CRspInfoField*  pRspInfoField,const TSessionRef &sessionRef,CTransaction *pTransaction);	
	virtual bool OnRtnOrder(CXTPPackage *pPackage,const TSessionRef &sessionRef);
	virtual bool OnRtnTrade(CXTPPackage *pPackage,const TSessionRef &sessionRef);
	virtual bool NtfInstrumentStatusUpdate(CInstrumentStatusField* pInstrumentStatusField,bool bSendRtn,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual void DumpDebugInfo(const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual void CleanOrderLocalID();
	// 2013-12-24 longqy 大边保证金中初始化构建表 PartClientInsGroupPosition 中数据
	virtual void BuildInsGroupPosition(CExchangeIDType exchangeID);
	//更新系统状态
	virtual bool UpdateSystemStatus(CSystemStatusField *pSystemStatusField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	//add by jinpc 20160906
	virtual bool DelUserSession(CUserField *pUserField,CTransaction *pTransaction);
	//强制删除session
 	virtual bool ForceUserLogout(CUserSession *pUserSession, CTransaction *pTransaction);
	//更新用户信息
	virtual bool UserUpdate(CUserField *pUserField, CTransaction *pTransaction);

	virtual bool NtfSGEDeferRate(CSGEDeferRateField *pSGEDeferRateField,const TSessionRef &sessionRef,CTransaction *pTransaction);

	//设置郑商所组合合约tick值和涨跌停价
	virtual bool ReqCZCECombMarketData();
	//获取系统交易日
	virtual CTradingDayType GetTradingDay();
	virtual bool ReqMBLMarketData(CQryMBLMarketDataField &pMBLMarketData,const TSessionRef &sessionRef);

	bool ReqNtfTimeSync(CXTPPackage *pPackage,const TSessionRef &sessionRef);

	bool ReqNtfPositionProfit(CXTPPackage *pPackage,const TSessionRef &sessionRef);
protected:
	///检查是否超级会话
	///@param	sessionRef	会话引用
	///@return	true表示是，false表示否
	bool isSuperSession(const TSessionRef &sessionRef);
	virtual CProductClassType getProductClassType(CExchangeIDType ExchangeID,CInstrumentIDType InstrumentID, CNumberType& APIID);	
protected:
	CConfig *m_pConfig;
	CMemoryDB *m_pDB;
	CErrorEngine *m_pErrorEngine;
	CFlow* m_pTradeResult;
	CXTPPackage *m_pPubMessage;
	CHandleNotify *m_pHandleNotify;
	
	CHandleOrder *m_pHandleOrder;	
	// 支持期货、期权等品种
//	CHandleOptionOrder *m_pHandleOptionOrder;
	CHandleFutureOrder *m_pHandleFutureOrder;
	
	CHandleTrade *m_pHandleTrade;
//	CHandleOptionTrade *m_pHandleOptionTrade;
	CHandleFutureTrade *m_pHandleFutureTrade;
	
	CHandleOrderAction *m_pHandleOrderAction;
	CHandleFutureOrderAction *m_pHandleFutureOrderAction;
//	CHandleOptionOrderAction *m_pHandleOptionOrderAction;
	FILE *m_orderActionFailedLog;//撤单错误日志	
// longqy 20141022 大边保证金是否计算的标志
private:
	bool m_bCombMarginSwitch;
	bool m_bOptionSwitch;
	CTransaction m_Transaction;
	char tmp[100];

	typedef set<string> CPartGroupPosition;
	CPartGroupPosition m_PartGroupPosition;
	CPosiMap m_PosiMap;

	CBaseAlgorithms baseAlgorithms;
};
#endif
