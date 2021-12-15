
/////////////////////////////////////////////////////////////////////////
///@system 风控前置引擎系统
///@company 上海量投网络科技有限公司
///@file TradingQueryServiceImpl.h
///@brief	定义了TradingQueryServiceImpl的接口
///@history 
///20121115	longqy@cffex.net 创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CTRADINGQUERYSERVICE_H
#define CTRADINGQUERYSERVICE_H

#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "CErrorEngine.h"

#include "QueryComplianceParam.h"

/// 下面两个常量，用于在查询的时候表示不存在的标识符，即不存在的 InvestorID 和 ClientID。
#define CAN_NOT_EXIST_INVESTORID "999999999999999999"
#define CAN_NOT_EXIST_CLIENTID   "999999999999999999"

/////////////////////////////////////////////////////////////////////////
///IInitService是一个描述完成数据初始化的接口，负责将数据初始化命令转化为
///内存数据库的数据
///@author	
///@version	1.0,20121115
/////////////////////////////////////////////////////////////////////////
class CTradingQueryImpl
{
public:
	CTradingQueryImpl(CMemoryDB *pDB,CErrorEngine *pEngine);
	virtual ~CTradingQueryImpl();
	
	///投资者资金查询请求
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败 	
	virtual bool QueryInvestorAccount(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CInvestorIDType& investorID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CInvestorAccountIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///报单查询请求
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败 	
	virtual bool QueryOrder(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CExchangeIDType& exchangeID,
					CInvestorIDType& investorID,
					COrderSysIDType& orderSysID,
					CInstrumentIDType& instrumentID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					COrderIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///成交单查询请求
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败 	
	virtual bool QueryTrade(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CExchangeIDType& exchangeID,
					CInvestorIDType& investorID,
					CTradeIDType& tradeID,
					CInstrumentIDType& instrumentID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CTradeIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///投资者查询请求
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败 	
	virtual bool QueryInvestor(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CInvestorIDType& investorID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CInvestorIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///报单查询请求
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败 	
	virtual bool QueryOrderInsertFailed(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CExchangeIDType& exchangeID,
					CInvestorIDType& investorID,
					COrderSysIDType& orderSysID,
					CInstrumentIDType& instrumentID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					COrderInsertFailedIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///合约查询请求
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败 	
	virtual bool QueryInstrument(
					CExchangeIDType& exchangeID,
					CProductIDType& productID,
					CInstrumentIDType& instrumentID,
					CInstrumentIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///用户查询请求
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败 	
	virtual bool QueryUser(
					CUserIDType& startUserID,
					CUserIDType& endUserID,
					CUserIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///交易所查询请求
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败 	
	virtual bool QueryExchange(
					CExchangeIDType& exchangeID,
					CExchangeIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///可用投资者账户查询请求
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败 	
	virtual bool QueryUserInvestor(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CUserInvestorIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///投资者持仓查询请求
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败 	
	virtual bool QueryInvestorPosition(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CExchangeIDType& exchangeID,
					CInvestorIDType& investorID,
					CInstrumentIDType& instrumentID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CInvestorPositionIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///普通行情查询请求
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败 	
	virtual bool QueryMarketData(
					CExchangeIDType& exchangeID,
					CInstrumentIDType& instrumentID,
					CMarketDataIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);


/*** SIR XLONG BEGIN ***/
	///保证金率查询
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败 	
	virtual bool QueryInvestorMargin(
				CBrokerIDType& brokerID,
				CInstrumentIDType &instrumentID,
				CInvestorMarginIterator** pIterator);
	///手续费率查询
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败 	
	virtual bool QueryInvestorFee(
		CBrokerIDType& brokerID,
		CInstrumentIDType &instrumentID,
		CInvestorFeeIterator** pIterator);

	///投资者查询：根据userID 查询投资者表
	///@param   userID
	///@return	true表示成功，false表示失败 	
	virtual bool QueryUserInvestorByUser(
		CUserIDType& userID,
		CUserInvestorIteratorAllByUserID** pIterator);
/*** SIR XLONG END ***/

	///金交所递延费率查询请求
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败 	
	virtual bool QuerySGEDeferRate(
					CInstrumentIDType& instrumentID,
					CSGEDeferRateIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);


	///交易时间偏差查询请求
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败 	
	virtual bool QueryExchTimeDiff(
					CExchangeIDType& exchangeID,
					CExchTimeDiffIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);
      
private:
	///判断用户是否是系统中有的用户
	///@param	userID	用户的编号
	///@return	true表示是正确，false表示不正确
	bool CheckUser(const CUserIDType& queryUserID,const CUserIDType& loginUserID,CBrokerIDType &BrokerID);
	
	///判断会话是否为管理员
	///@param	sessionRef	会话编号
	///@return	true表示是，false表示不是
	bool isAdmin(const CUserIDType &userID,CBrokerIDType &BrokerID);	
	
	///设置查询范围
	///@param	sessionRef	会话编号
	///@param	clearingPartID	要查询的结算会员编号
	///@param	participantID	要查询的交易会员编号
	///@return	true表示是成功，false表示失败
	bool setRange(const TSessionRef &sessionRef,CParticipantIDType &clearingPartID,
		CParticipantIDType &participantID);
	
	///检查用户投资者关系表，查看输入的参数是否有对应的记录
	///若有记录，则返回ture；否则，返回false。
	///@param	brokerID	经纪公司编号
	///@param	userID		交易用户代码
	///@param	investorID	投资者编号
	bool CheckUserInvestor(const CBrokerIDType& brokerID,
						const CUserIDType& userID,const CInvestorIDType& investorID);

	/*  查询客户与用户的关系，看看是否真的有clientID对应了相应的 userID 记录 */	
	bool CheckUserClient(const CClientIDType& clientID,const CUserIDType& userID);

	void * fromUserGetInvestor(const CBrokerIDType& brokerID,const CUserIDType& userID);
	
	/* userID 查 ClientID*/
	void * fromUserGetInvestorFee(const CBrokerIDType& brokerID,const CUserIDType& userID,const CExchangeIDType& exchangeID);

	void * fromUserGetInvestorMargin(const CBrokerIDType& brokerID,const CUserIDType& userID,const CExchangeIDType& exchangeID);
	
	/* InvestorID 查 ClientID*/
	void * fromUserGetInvestorFee(const CBrokerIDType& brokerID,const CInvestorIDType& investorID,const CExchangeIDType& exchangeID);

	void * fromUserGetInvestorMargin(const CBrokerIDType& brokerID,const CInvestorIDType& investorID,const CExchangeIDType& exchangeID);
	
	void fromUserGetInvestors(const CBrokerIDType& brokerID,const CUserIDType& userID,InvestorIDVector& vInvestorID);	

	void fromInvestorsGetAccount(const CBrokerIDType& brokerID, const CInvestorIDType& investorID, AccountIDVector& vAccountID);
						
	CMemoryDB *m_DB;
	CErrorEngine *m_ErrorEngine;
	/// 不用 bool m_PartQueryMBL;
	

	
	// 需要这个变量vInvestorID，是因为 CInvestorAccountInvestorIDPredict的参数是引用，而这个Predict 在ServiceXTPLink
	// 这一层还要用到。这需要vInvestorID 类似于全局变量，不能用局部变量。
	InvestorIDVector vInvestorID;
	AccountIDVector vAccountID;
};

#endif
