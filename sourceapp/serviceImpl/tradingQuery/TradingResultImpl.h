/////////////////////////////////////////////////////////////////////////
///@system 极速风控前置系统
///@company 上海量投网络科技有限公司
///@file TradingResultImpl.h
///@brief定义了类TradingResultImpl，计算交易的结果，存入内存数据库
///@history 
///20121219	longqy@cffex.net 创建文件

/////////////////////////////////////////////////////////////////////////
#ifndef TRADINGRESULTIMPL_H
#define TRADINGRESULTIMPL_H

//#include "IServiceInterface.h"
#include "errorDefine.h"
#include "CMemoryDB.h"
#include "UFCopy.h"

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

/*** SIR XXXXX BEGIN ***/
///出入金来自期货主席
#define INVESTORACCOUNTDEPOSIT_TOPICID_CHAIRMAN      "9001"
#define INVESTORACCOUNTDEPOSIT_FROM_CHAIRMAN         'A'
#define INVESTORACCOUNTDEPOSIT_FROM_MONEYGATE        'M'

///出入金来自场下
#define INVESTORACCOUNTDEPOSIT_TOPICID_FIELD         "9002"
#define INVESTORACCOUNTDEPOSIT_FROM_FIELD            'B'

///出入金来自场下轧差
#define INVESTORACCOUNTDEPOSIT_TOPICID_Netting       "9003"
#define INVESTORACCOUNTDEPOSIT_FROM_Netting            'C'
/*** SIR XXXXX END ***/


/////////////////////////////////////////////////////////////////////////
///CTradingResultImpl 负责接收TResult流数据，并将这些数据转化为
///内存数据库的数据
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

class CTradingResultImpl
{
public:
	CTradingResultImpl(CMemoryDB *pDB,CErrorEngine *pEngine,CConfig *pConfig,CFlow *pFlow);
	 ~CTradingResultImpl();

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

	void beforeDataSync(CTransaction *pTransaction);

	void afterDataSync(CTransaction *pTransaction);

	virtual bool RspQryExInstrument(CInstrumentField *pInstrumentField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQryExTradingDay(CExchangeTradingDayField *pExchangeTradingDayField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQryExInvestorPosition(CInvestorPositionField *pInvestorPositionField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQryExMarketData(CMarketDataField *pMarketDataField,const TSessionRef &sessionRef,CTransaction *pTransaction);	
	virtual bool RspQryExCapitalData(CExCapitalDataField *pExCapitalDataField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQueryExCmbInstrumentDetail(CCmbInstrumentDetailField *pCmbInstrumentDetailField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQryExDiffTime(CExchTimeDiffField *pExchTimeDiffField,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///同步数据库表客户资金帐户出入金
	///@param	pInvestorAccountDeposit	要同步的客户资金帐户出入金信息
	///@param	pResDeposit	出入金应答信息
	///@param	topicID	DBMT的主题号
	///@param	seqID	DBMT的序列号
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncInvestorAccountDeposit(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit,CAccountDepositResField *pResDeposit,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
									const TSessionRef &sessionRef,CTransaction *pTransaction);


	///同步数据库表修改交易用户
	///@param	pUpdUser	要同步的修改交易用户信息
	///@param	topicID	DBMT的主题号
	///@param	seqID	DBMT的序列号
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncUpdUser(CWriteableUser *pUser,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///同步数据库表客户资金帐户出入金的实现
	///@param	pClientTradingID	要同步的客户资金帐户出入金信息
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncClientTradingID(CWriteableClientTradingID *pClientTradingID,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
		const TSessionRef &sessionRef,CTransaction *pTransaction);

	
	bool OnRtnOrder(COrderField *pOrder,const TSessionRef &sessionRef,CTransaction *pTransaction);

	bool OnRtnTrade(CTradeField *pTrade,const TSessionRef &sessionRef,CTransaction *pTransaction);

	bool RspOrderAction(COrderField *pRspOrder,CWriteableOrderAction *pOrderAction,COrderActionField* pActField,
			CRspInfoField*  pRspInfoField,const TSessionRef &sessionRef,CTransaction *pTransaction);

	void DumpDebugInfo(const TSessionRef &sessionRef,CTransaction *pTransaction);

	bool UpdateSystemStatus(CSystemStatusField *pSystemStatusField,const TSessionRef &sessionRef,CTransaction *pTransaction);

	void BuildInsGroupPosition(CExchangeIDType exchangeID);

	bool NtfInstrumentStatusUpdate(CInstrumentStatusField* pInstrumentStatusField,bool bSendRtn,const TSessionRef &sessionRef,CTransaction *pTransaction);

	bool UserUpdate(CDbmtUserField *pUserField, CTransaction *pTransaction);

	bool NtfSGEDeferRate(CSGEDeferRateField *pSGEDeferRateField,const TSessionRef &sessionRef,CTransaction *pTransaction);

	bool NtfTimeSync(CCurrentTimeField *pCurrTime,const TSessionRef &sessionRef,CTransaction *pTransaction);
protected:
	bool isDuplicate(CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID);

	bool suitableTime(void);

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
private:
	CConfig *m_Config;
	CMemoryDB *m_DB;
	CErrorEngine *m_ErrorEngine;

	map<CDbmtTopicIDType,CDbmtSequenceIDType> m_lastSeqMap;

	CTransaction m_Transaction;
	CFlow *m_pSendFlow;

	typedef set<string> CPartGroupPosition;
	CPartGroupPosition m_PartGroupPosition;
	CPosiMap m_PosiMap;

	CBaseAlgorithms baseAlgorithm;
};

#endif

