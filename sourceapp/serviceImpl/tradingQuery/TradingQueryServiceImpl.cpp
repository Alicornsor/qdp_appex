/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file TradingQueryServiceImpl.cpp
///@brief定义了类 CTradingQueryServiceImpl ，这个类真正实现查询的功能。
///      检查传入的参数，是否为合法的参数。根据参数是否为空，以及数据库模型中定义的查询函数，查询到各个记录。
///@history 
///20121219	longqy@cffex.net 创建文件

#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "TradingQueryServiceImpl.h"
#include "errorDefine.h"
#include "tradingTools.h"
#include "databaseIteratorRepository.h"
#include "TradingQueryPredicts.h"

///-------
//	xuzh，20090327：NT-0070对于qkernel查询的优化
//	xuzh，20090510：NT-0070中对合约查询和行情查询的优化回退
///-------

CTradingQueryImpl::CTradingQueryImpl(CMemoryDB *pDB,CErrorEngine *pEngine)
{
	m_DB = pDB;
	m_ErrorEngine = pEngine;
}

CTradingQueryImpl::~CTradingQueryImpl()
{
}

/*	根据用户类型，判断用户是否管理员。
/// 是管理员，则返回 true; 不是管理员，则返回 false; 
*/
bool CTradingQueryImpl::isAdmin(const CUserIDType &userID,CBrokerIDType &BrokerID)
{
	CUserFactory *thisFactory = m_DB->m_UserFactory;	
	// 在User表中查找用户
	CUser *pUser = thisFactory->findByBrokerIDUserID(BrokerID,userID);	
	if(NULL == pUser)
	{	// 如果没有查询到用户，则表示这个用户非法
		// 因为用户能够登录，即用户存在，这段代码永远也不会执行。
		m_ErrorEngine->reportError(ERROR_USERID_CANNOT_BE_FOUND);
		return false;
	}else
	{
		if( UT_Manager == pUser->UserType)
		{ // 类型是管理员
			return true;
		}else
		{
			return false;
		}
	}	
}

// 这个函数目前不使用
bool CTradingQueryImpl::CheckUser(const CUserIDType& queryUserID,const CUserIDType& loginUserID,CBrokerIDType &BrokerID)
{
	if (queryUserID != loginUserID)
	{	// 用户登录的ID 与 他要查询的 UserID 不一致。不允许查别人的信息
		m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
		return false;
	}

	CUserFactory *thisFactory = m_DB->m_UserFactory;	
	// 在User表中查找用户
	CUser *pUser = thisFactory->findByBrokerIDUserID(BrokerID,queryUserID);	
	if(NULL == pUser)
	{	// 如果没有查询到用户，则表示这个用户非法
		m_ErrorEngine->reportError(ERROR_USERID_CANNOT_BE_FOUND);
		return false;
	}else
	{
		return true;
	}
}

bool CTradingQueryImpl::setRange(const TSessionRef &sessionRef,CParticipantIDType &clearingPartID,
	CParticipantIDType &participantID)
{
	return false;
}

///------
///	当客户要查询报单的时候，不但是要查询 Order 表，还要查询 OrderInsertFailed 即错单表。
/// 输入参数：
/// brokerID		经纪公司编号
/// userID   		用户代码
/// exchangeID		交易所代码
/// investorID		投资者编号
/// orderSysID		报单的系统编号
/// instrumentID	合约代码
/// logBrokerID		登录经纪公司编号
/// logUserID		登录用户代码
/// sessionRef		引用的会话对象
/// pTransaction	事务对象指针
///
/// 输出参数：
///	pIterator		迭代器指针的指针，用于返回查询到的对象
///------
bool CTradingQueryImpl::QueryOrder(
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
					CTransaction *pTransaction)
{
	if (brokerID != logBrokerID)
	{	// 用户登录的BrokerID 与 他要查询的 BrokerID 不一致。不允许查别人的信息
		m_ErrorEngine->reportError(ERROR_BROKERID_MISMATCH); 
		return false;
	}
	if ( ! isAdmin(logUserID,brokerID) )
	{ // 不是管理员，才查其权限
		//从交易所反演之后 报单的UserID没有,在没有userid的情况下，也需要查询
		if ( userID.isNull() )
		{
		  // 支持按InvestorID查询 ，当UserID缺省时，查询该INVESTORID下所有USER的委托 2014-08-07
		  // 没有设置用户ID，强行设置。因为只能查询自己的账户
		  //	userID = logUserID;
			//	USERID和INVESTORID不能同时为空
			if (investorID.isNull())
			{
				m_ErrorEngine->reportError(ERROR_USERID_INVESTORID_BOTHBLANK);
				return false;
			}
			//不能查询未关联到本登录用户的INVESTOR委托
		  	if (! CheckUserInvestor(brokerID,logUserID,investorID))
		  	{
				m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
				return false;
			}
		}
		else
		{
// 			if (userID != logUserID) 
// 			{	// 用户登录的ID 与 他要查询的 UserID 不一致。不允许查别人的信息
// 				m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
// 				return false;
//			}
			userID = logUserID;
			if(!investorID.isNull())
			{
				///xuzh 20150713  不可查询此登录用户无法关联的投资者的报单
		  		if (!CheckUserInvestor(brokerID,logUserID,investorID))
		  		{
					m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
					return false;
				}
			}
		}
	}
	
	COrderFactory *thisFactory = m_DB->m_OrderFactory;
	
	COrderPredict *pPredict;
	pPredict=new COrderAndPredict(new COrderAndPredict(new COrderExchangeIDPredict(&exchangeID,&exchangeID),
				new COrderAndPredict(new COrderInvestorIDPredict(&investorID,&investorID),
				new COrderAndPredict(new COrderInstrumentIDStartPredict(&instrumentID,&instrumentID),
				new COrderOrderSysIDPredict(&orderSysID,&orderSysID) ) ) ),new COrderBrokerIDPredict(&brokerID,&brokerID));
	
	COrderIterator *pBaseIterator;
	if (!userID.isNull())
	{
		if (!exchangeID.isNull())
		{
			if (!orderSysID.isNull())
			{
				pBaseIterator = new COrderSingleIterator(thisFactory,thisFactory->findByExchangeIDAndOrderSysID(exchangeID,orderSysID));
			}
			else if (!investorID.isNull())
			{
				pBaseIterator = new COrderIteratorAllByExchIDInvIDUserID(thisFactory,exchangeID,investorID,userID);
			}
			else if (!instrumentID.isNull())
			{
				pBaseIterator = new COrderIteratorAllByExchIDInstruIDUserID(thisFactory,exchangeID,instrumentID,userID);
			}
			else
			{
				pBaseIterator = new COrderIteratorAll(thisFactory);
			}
		}
		else
		{
//			pBaseIterator = new COrderIteratorAllByUserID(thisFactory,userID);
			pBaseIterator = new COrderIteratorAll(thisFactory);
		}
	}
	else
	{
		if(!investorID.isNull())
		{
			pBaseIterator = new COrderIteratorAllByInvestorID(thisFactory,investorID);
		}
		else
		{
			pBaseIterator = new COrderIteratorAll(thisFactory);
		}
	}

	*pIterator = new COrderFilter(pBaseIterator,pPredict);
	return true;
}

/* 错单表OrderInsertFailed的表结构跟报单表Order是一样的。对它的查询处理与报单表是一样的。
/// 输入参数：
/// brokerID		经纪公司编号
/// userID   		用户代码
/// exchangeID		交易所代码
/// investorID		投资者编号
/// orderSysID		报单的系统编号
/// instrumentID	合约代码
/// logBrokerID		登录经纪公司编号
/// logUserID		登录用户代码
/// sessionRef		引用的会话对象
/// pTransaction	事务对象指针
///
/// 输出参数：
///	pIterator		迭代器指针的指针，用于返回查询到的对象
*/
bool CTradingQueryImpl::QueryOrderInsertFailed(
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
					CTransaction *pTransaction)	
{
	if (brokerID != logBrokerID)
	{	// 用户登录的BrokerID 与 他要查询的 BrokerID 不一致。不允许查别人的信息
		m_ErrorEngine->reportError(ERROR_BROKERID_MISMATCH); 
		return false;
	}
	if ( ! isAdmin(logUserID,brokerID) )
	{ // 不是管理员，才查其权限
		if ( userID.isNull() )
		{ // 支持按InvestorID查询 ，当UserID缺省时，查询该INVESTORID下所有USER的委托 2014-08-07 liumeng
		  // 没有设置用户ID，强行设置。因为只能查询自己的账户
		  //	userID = logUserID;
			//	USERID和INVESTORID不能同时为空
			if (investorID.isNull())
			{
				m_ErrorEngine->reportError(ERROR_USERID_INVESTORID_BOTHBLANK);
				return false;
			}
			//不能查询未关联到本登录用户的INVESTOR委托
		  	if (! CheckUserInvestor(brokerID,logUserID,investorID))
		  	{
				m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
				return false;
			}
		}else
		{
			if (userID != logUserID) 
			{	// 用户登录的ID 与 他要查询的 UserID 不一致。不允许查别人的信息
				m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
				return false;
			}
		}	
	}
	
	COrderInsertFailedFactory *thisFactory = m_DB->m_OrderInsertFailedFactory;
	
	COrderInsertFailedPredict *pPredict;
	pPredict=new COrderInsertFailedAndPredict(new COrderInsertFailedAndPredict(new COrderInsertFailedUserIDPredict(&userID,&userID),
				new COrderInsertFailedAndPredict(new COrderInsertFailedExchangeIDPredict(&exchangeID,&exchangeID),
				new COrderInsertFailedAndPredict(new COrderInsertFailedInvestorIDPredict(&investorID,&investorID),
				new COrderInsertFailedAndPredict(new COrderInsertFailedInstrumentIDStartPredict(&instrumentID,&instrumentID),
				new COrderInsertFailedOrderSysIDPredict(&orderSysID,&orderSysID) ) ) ) ),new COrderInsertFailedBrokerIDPredict(&brokerID,&brokerID));
	
	COrderInsertFailedIterator *pBaseIterator;
	if (!userID.isNull())
	{
		if (!exchangeID.isNull())
		{
			if (!orderSysID.isNull())
			{
				pBaseIterator = new COrderInsertFailedSingleIterator(thisFactory,thisFactory->findByExchangeIDAndOrderSysID(exchangeID,orderSysID));
			}
			else if (!investorID.isNull())
			{
				// pBaseIterator = new COrderInsertFailedIteratorAllByExchIDCliIDUserID(thisFactory,exchangeID,clientID,userID);
				pBaseIterator = new COrderInsertFailedIteratorAllByExchIDInvIDUserID(thisFactory,exchangeID,investorID,userID);
			}
			else if (!instrumentID.isNull())
			{
				pBaseIterator = new COrderInsertFailedIteratorAllByExchIDInstruIDUserID(thisFactory,exchangeID,instrumentID,userID);
			}		
			else
			{
				pBaseIterator = new COrderInsertFailedIteratorAll(thisFactory);
			}
		}
		else
		{
			pBaseIterator = new COrderInsertFailedIteratorAll(thisFactory);
		}
	}
	else
	{
		pBaseIterator = new COrderInsertFailedIteratorAll(thisFactory);
	}

	*pIterator = new COrderInsertFailedFilter(pBaseIterator,pPredict);
	return true;
}

/*  QueryTrade 查询成交单
/// 输入参数：
/// brokerID		经纪公司编号
/// userID   		用户代码
/// exchangeID		交易所代码
/// investorID		投资者编号
/// orderSysID		报单的系统编号
/// instrumentID	合约代码
/// logBrokerID		登录经纪公司编号
/// logUserID		登录用户代码
/// sessionRef		引用的会话对象
/// pTransaction	事务对象指针
///
/// 输出参数：
///	pIterator		迭代器指针的指针，用于返回查询到的对象
*/
bool CTradingQueryImpl::QueryTrade(
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
					CTransaction *pTransaction)
{
	if (brokerID != logBrokerID)
	{	// 用户登录的BrokerID 与 他要查询的 BrokerID 不一致。不允许查别人的信息
		m_ErrorEngine->reportError(ERROR_BROKERID_MISMATCH); 
		return false;
	}
	if ( ! isAdmin(logUserID,brokerID) )
	{ // 不是管理员，才查其权限
		if ( userID.isNull() )
		{ // 没有设置用户ID，强行设置。因为只能查询自己的账户
			//userID = logUserID;
			if(investorID.isNull())
			{
				m_ErrorEngine->reportError(ERROR_USERID_INVESTORID_BOTHBLANK);
				return false;
			}
			//不能查询未关联到本登录用户的INVESTOR委托
			if (! CheckUserInvestor(brokerID,logUserID,investorID))
		  	{
				m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
				return false;
			}
		}else
 		{
// 			if (userID != logUserID) 
// 			{	// 用户登录的ID 与 他要查询的 UserID 不一致。不允许查别人的信息
// 				m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
// 				return false;
// 			}
			if(!investorID.isNull())
			{
				if (! CheckUserInvestor(brokerID,logUserID,investorID))
		  		{
					m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
					return false;
				}
			}
		}	
	}
	
	CTradeFactory *thisFactory = m_DB->m_TradeFactory;
	
	CTradePredict *pPredict;
	pPredict=new CTradeAndPredict(
		new CTradeAndPredict(new CTradeExchangeIDPredict(&exchangeID,&exchangeID),
		new CTradeAndPredict(new CTradeInstrumentIDStartPredict(&instrumentID,&instrumentID),
		new CTradeAndPredict(new CTradeTradeIDPredict(&tradeID,&tradeID),
							 new CTradeInvestorIDPredict(&investorID,&investorID)))),new CTradeBrokerIDPredict(&brokerID,&brokerID));

	CTradeIterator *pBaseIterator;
	if (!userID.isNull())
	{
		if (!exchangeID.isNull())
		{
			if (!tradeID.isNull())
			{
				//pBaseIterator = new CTradeSingleIterator(thisFactory,thisFactory->findByExchangeIDAndTradeID(exchangeID,tradeID));
				pBaseIterator = new CTradeIteratorByExchangeIDAndTradeID(thisFactory,exchangeID,tradeID);
			}
			else if (!investorID.isNull())
			{
//				pBaseIterator = new CTradeIteratorAllByExchIDCliIDUserID(thisFactory,exchangeID,clientID,userID);
				pBaseIterator = new CTradeIteratorAllByExchIDInvIDUserID(thisFactory,exchangeID,investorID,userID);
			}
			else if (!instrumentID.isNull())
			{
				pBaseIterator = new CTradeIteratorAllByExchIDInstruIDUserID(thisFactory,exchangeID,instrumentID,userID);
			}		
			else
			{
				pBaseIterator = new CTradeIteratorAll(thisFactory);
			}
		}
		else
		{
			pBaseIterator = new CTradeIteratorAll(thisFactory);
		}
	}
	else
	{
		if(!investorID.isNull())
		{
			pBaseIterator = new CTradeIteratorAllByInvestorID(thisFactory,investorID);
		}
		else
		{
			pBaseIterator = new CTradeIteratorAll(thisFactory);
		}
	}

	*pIterator = new CTradeFilter(pBaseIterator,pPredict);
	return true;
}


///-----
///	xuzh，20070224：增加了客户类型作为查询条件
///-----

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionClientTypePredict是判断一个客户持仓是否满足客户类型条件的谓词
///@author	xuzh
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionClientTypePredict: public CInvestorPositionPredict
{
private:
	CMemoryDB *m_DB;
	CClientTypeType *m_pClientType;
public:
	///构造方法
	///@param	pDB	使用的内存数据库
	///@param	pClientType	指向要求的客户类型。如果为NULL或者值为空格，则忽略此条件
	CInvestorPositionClientTypePredict(CMemoryDB *pDB, CClientTypeType *pClientType)
	{
		m_DB = pDB;
		m_pClientType = pClientType;
	}
};

/// 合约表是公开信息，只要是能够登录的用户，都可以查询合约表
/// 输入参数：
/// exchangeID		交易所代码
/// productID		产品代码
/// instrumentID	合约代码
/// sessionRef		引用的会话对象
/// pTransaction	事务对象指针
///
/// 输出参数：
///	pIterator		迭代器指针的指针，用于返回查询到的对象
bool CTradingQueryImpl::QueryInstrument(
					CExchangeIDType& exchangeID,
					CProductIDType& productID,
					CInstrumentIDType& instrumentID,
					CInstrumentIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
	
	CInstrumentFactory *thisFactory = m_DB->m_InstrumentFactory;
	
	CInstrumentPredict *pPredict;
	pPredict=new CInstrumentAndPredict(new CInstrumentExchangeIDPredict(&exchangeID,&exchangeID),
				new CInstrumentAndPredict(new CInstrumentProductIDPredict(&productID,&productID),
				new CInstrumentInstrumentIDStartPredict(&instrumentID,&instrumentID)));

	CInstrumentIterator *pBaseIterator;
	if (!instrumentID.isNull())
	{
		pBaseIterator= new CInstrumentIteratorAllByInstrumentID(thisFactory,instrumentID);
	}
	else if(!productID.isNull())
	{
		pBaseIterator= new CInstrumentIteratorAllByProductID(thisFactory,productID);	
	}
	else if(!exchangeID.isNull())
	{
		pBaseIterator= new CInstrumentIteratorAllByExchangeID(thisFactory,exchangeID);	
	}else
	{
		pBaseIterator= new CInstrumentIteratorAll(thisFactory);		
	}

	*pIterator = new CInstrumentFilter(pBaseIterator,pPredict);
	return true;
}

/// 输入参数：
/// exchangeID		交易所代码
/// instrumentID	合约代码
/// sessionRef		引用的会话对象
/// pTransaction	事务对象指针
///
/// 输出参数：
///	pIterator		迭代器指针的指针，用于返回查询到的对象
bool CTradingQueryImpl::QueryMarketData(
					CExchangeIDType& exchangeID,
					CInstrumentIDType& instrumentID,
					CMarketDataIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
	/*CInstrumentFactory *thisFactory = m_DB->m_InstrumentFactory;
	
	CInstrumentPredict *pPredict;
	pPredict=new CInstrumentAndPredict(new CInstrumentExchangeIDPredict(&exchangeID,&exchangeID),
		new CInstrumentInstrumentIDStartPredict(&instrumentID,&instrumentID));

	CInstrumentIterator *pBaseIterator;
	pBaseIterator= new CInstrumentIteratorAllByInstrumentID(thisFactory,instrumentID);

	*pIterator = new CMarketDataOfInstrumentIterator(m_DB->m_MarketDataFactory,new CInstrumentFilter(pBaseIterator,pPredict));*/
	
	CMarketDataFactory *thisFactory = m_DB->m_MarketDataFactory;
	
	CMarketDataPredict *pPredict;
	pPredict=new CMarketDataAndPredict(new CMarketDataExchangeIDPredict(&exchangeID,&exchangeID),
		                               new CMarketDataInstrumentIDStartPredict(&instrumentID,&instrumentID));

	CMarketDataIterator *pBaseIterator;
	pBaseIterator= new CMarketDataIteratorAll(thisFactory);

	*pIterator = new CMarketDataFilter(pBaseIterator, pPredict);
	return true;
}

/// 这个函数目前没有使用
bool CTradingQueryImpl::QueryUser(
					CUserIDType& userIDStart,
					CUserIDType& userIDEnd,
					CUserIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
	CUserFactory *thisFactory = m_DB->m_UserFactory;
	
	CUserPredict *pPredict;
	pPredict=new CUserUserIDPredict(&userIDStart,&userIDEnd);

	CUserIterator *pBaseIterator;
	pBaseIterator= new CUserIteratorStartByUserID(thisFactory,userIDStart);

	*pIterator = new CUserFilter(pBaseIterator,pPredict,false);
	return true;
}

/*	QueryInvestor 查询投资者
/// 输入参数：
/// brokerID		经纪公司编号
/// userID   		用户代码
/// investorID		投资者编号
/// logBrokerID		登录经纪公司编号
/// logUserID		登录用户代码
/// sessionRef		引用的会话对象
/// pTransaction	事务对象指针
///
/// 输出参数：
///	pIterator		迭代器指针的指针，用于返回查询到的对象
*/
bool CTradingQueryImpl::QueryInvestor(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CInvestorIDType& investorID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CInvestorIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)		
{
	if (brokerID != logBrokerID)
	{	// 用户登录的BrokerID 与 他要查询的 BrokerID 不一致。不允许查别人的信息
		m_ErrorEngine->reportError(ERROR_BROKERID_MISMATCH); 
		return false;
	}
	// Added by Longqy 2012.12.04
	if (!isAdmin(logUserID,brokerID))
	{	
		if ( userID.isNull() )
		{ // 没有设置用户ID，强行设置。因为只能查询自己的账户
			userID = logUserID;
		}else
		{
			if (userID != logUserID) 
			{	// 用户登录的ID 与 他要查询的 UserID 不一致。不允许查别人的信息
				m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
				return false;
			}
		}
			if (! CheckUserInvestor(brokerID,logUserID,investorID))
		{
			m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
			return false;
		}
	}
	
	CInvestorFactory *thisFactory = m_DB->m_InvestorFactory;
	CInvestorPredict *pPredict;
	pPredict= new CInvestorAndPredict(new CInvestorBrokerIDPredict(&brokerID,&brokerID),
				new CInvestorInvestorIDPredict(&investorID,&investorID));

	CInvestorIterator *pBaseIterator;
	pBaseIterator= new CInvestorIteratorByInvestorID(thisFactory,investorID);

	*pIterator = new CInvestorFilter(pBaseIterator,pPredict,false);
	
	return true;
}

/*	QueryInvestorAccount 投资者资金帐号查询
/// 输入参数：
/// brokerID		经纪公司编号
/// userID   		用户代码
/// investorID		投资者编号
/// logBrokerID		登录经纪公司编号
/// logUserID		登录用户代码
/// sessionRef		引用的会话对象
/// pTransaction	事务对象指针
///
/// 输出参数：
///	pIterator		迭代器指针的指针，用于返回查询到的对象
*/
bool CTradingQueryImpl::QueryInvestorAccount(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CInvestorIDType& investorID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CInvestorAccountIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
	// InvestorIDVector vInvestorID;
	vInvestorID.clear();
	bool	bHasInvestor = false;
	//  如果InvestorID为空，则算错误，直接返回 2013.01.23
/*  有了UserID，允许为空。
	if (investorID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_QUERY_INVESTORACCOUNT_INVESTORID_ISNULL); 
		return false;
	}
*/	
	if (brokerID != logBrokerID)
	{	// 用户登录的BrokerID 与 他要查询的 BrokerID 不一致。不允许查别人的信息
		m_ErrorEngine->reportError(ERROR_BROKERID_MISMATCH); 
		return false;
	}
	if (!isAdmin(logUserID,brokerID))
	{	
		if ( userID.isNull() )
		{ // 没有设置用户ID，强行设置。因为只能查询自己的账户
			userID = logUserID;
		}
		else
		{
			if (userID != logUserID) 
			{	// 用户登录的ID 与 他要查询的 UserID 不一致。不允许查别人的信息
				m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
				return false;
			}
		}

		if (investorID.isNull())
		{
			fromUserGetInvestors(brokerID,userID,vInvestorID);
			bHasInvestor = false;
		}
		else
		{
			if (!CheckUserInvestor(brokerID,logUserID,investorID))
			{
				m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
				return false;
			}
			bHasInvestor = true;
		}		
	}
	else 
	{ // 是管理员
		if (!investorID.isNull())
		{
			if (! CheckUserInvestor(brokerID,userID,investorID))
			{
				m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
				return false;
			}
			bHasInvestor = true;
		}else
		{
			fromUserGetInvestors(brokerID,userID,vInvestorID);
			bHasInvestor = false;
		}			
	}
	CInvestorAccountFactory *thisFactory = m_DB->m_InvestorAccountFactory;
	CInvestorAccountPredict *pPredict=NULL;
	
	if(bHasInvestor)
	{
		pPredict= new CInvestorAccountAndPredict(new CInvestorAccountBrokerIDPredict(&brokerID,&brokerID),
			new CInvestorAccountInvestorIDPredict(&investorID,&investorID));
	}
	else
	{   // 参数investorID 为空，从 userID 查找到 investorID 数组
		int iCount;
		CInvestorAccountPredict* pMultiPredict=NULL;
		for(iCount=0;iCount<vInvestorID.size();iCount++)
		{
			if(iCount<1)
			{
				pMultiPredict = new CInvestorAccountInvestorIDPredict(&vInvestorID[iCount],&vInvestorID[iCount]);
			}
			else
			{
				pMultiPredict = new CInvestorAccountOrPredict(pMultiPredict,new CInvestorAccountInvestorIDPredict(&vInvestorID[iCount],&vInvestorID[iCount]));
			}			
		}
		//CInvestorIDType sNotExistInvestorID="999999999999999999";
		CInvestorIDType sNotExistInvestorID = CAN_NOT_EXIST_INVESTORID;
		if (NULL == pMultiPredict)
		{
			pMultiPredict = new CInvestorAccountInvestorIDPredict(&sNotExistInvestorID,&sNotExistInvestorID);
		}

		pPredict= new CInvestorAccountAndPredict(new CInvestorAccountBrokerIDPredict(&brokerID,&brokerID),pMultiPredict);
	}

	CInvestorAccountIterator *pBaseIterator;
	
	if (!investorID.isNull())
	{
		pBaseIterator = new CInvestorAccountIteratorAllByInvestorID(thisFactory,investorID);
	}
	else if( 1 == vInvestorID.size())
	{
		pBaseIterator = new CInvestorAccountIteratorAllByInvestorID(thisFactory,vInvestorID[0]);
	}
	else if(!brokerID.isNull())
	{
		pBaseIterator = new CInvestorAccountIteratorAllByBrokerID(thisFactory,brokerID);
	}
	else
	{
		pBaseIterator = new CInvestorAccountIteratorAll(thisFactory);	
	}

	// 注意，这里第三个参数 false，表示在查询的时候，不要求下一条记录，一定是紧挨着上一条记录，而且符合条件，
	//才能查出。 如果为true，中间只要有一条记录不符合条件，查询即终止。哪怕后面还有记录，符合条件，也不再查询。	
	*pIterator = new CInvestorAccountFilter(pBaseIterator,pPredict,false);
	return true;
}

/*	QueryExchange 交易所信息查询
/// 交易所信息是公开的，只要能够登录的用户都可以查询。不需要进行权限检查。
/// 输入参数：
/// exchangeID		交易所代码
/// sessionRef		引用的会话对象
/// pTransaction	事务对象指针
///
/// 输出参数：
///	pIterator		迭代器指针的指针，用于返回查询到的对象
*/
bool CTradingQueryImpl::QueryExchange(
					CExchangeIDType& exchangeID,
					CExchangeIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
	CExchangeFactory *thisFactory = m_DB->m_ExchangeFactory;
	CExchangePredict *pPredict;
	pPredict = new CExchangeExchangeIDPredict(&exchangeID,&exchangeID);

	CExchangeIterator *pBaseIterator;
	if (!exchangeID.isNull())
	{
		pBaseIterator = new CExchangeIteratorStartByExchangeID(thisFactory,exchangeID);
	}
	else 
	{
		pBaseIterator = new CExchangeIteratorAll(thisFactory);
	}

	*pIterator = new CExchangeFilter(pBaseIterator,pPredict,false);
	
	return true;

}

/*	QueryUserInvestor 可用投资者账户查询，即查询用户与投资者帐号的关系
/// 输入参数：
/// brokerID		经纪公司编号
/// userID   		用户代码
/// logBrokerID		登录经纪公司编号
/// logUserID		登录用户代码
/// sessionRef		引用的会话对象
/// pTransaction	事务对象指针
///
/// 输出参数：
///	pIterator		迭代器指针的指针，用于返回查询到的对象
*/
bool CTradingQueryImpl::QueryUserInvestor(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CUserInvestorIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
/*
	if (userID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_QUERY_USERINVESTOR_USERID_ISNULL); 
		return false;
	}
*/	
	if (brokerID != logBrokerID)
	{	// 用户登录的BrokerID 与 他要查询的 BrokerID 不一致。不允许查别人的信息
		m_ErrorEngine->reportError(ERROR_BROKERID_MISMATCH); 
		return false;
	}
	if ( ! isAdmin(logUserID,brokerID) )
	{ // 不是管理员，才查其权限
		if ( userID.isNull() )
		{ // 没有设置用户ID，强行设置。因为只能查询自己的账户
			userID = logUserID;
		}else
		{
			if (userID != logUserID) 
			{	// 用户登录的ID 与 他要查询的 UserID 不一致。不允许查别人的信息
				m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
				return false;
			}
		}
	}
		
	CUserInvestorFactory *thisFactory = m_DB->m_UserInvestorFactory;
	
	CUserInvestorPredict *pPredict;
	pPredict = new CUserInvestorAndPredict(new CUserInvestorBrokerIDPredict(&brokerID,&brokerID),
					new CUserInvestorUserIDPredict(&userID,&userID));

	CUserInvestorIterator *pBaseIterator;
	if (!userID.isNull())
	{
		pBaseIterator = new CUserInvestorIteratorAllByUserID(thisFactory,userID);
	}
	else if(!brokerID.isNull())
	{
		pBaseIterator = new CUserInvestorIteratorAllByBrokerID(thisFactory,brokerID);
	}
	else
	{
		pBaseIterator = new CUserInvestorIteratorAll(thisFactory);
	}

	*pIterator = new CUserInvestorFilter(pBaseIterator,pPredict,false);
	return true;
}

/*  QueryInvestorPosition 投资者持仓查询
//  对外接口API查询的是InvestorPosition，但是内存数据库中没有InvestorPosition表，实际上是从
//  InvestorPosition表中查询的
//  注意这个函数的参数 clientID，在客户端API是没有的。只是在这一层才添加的。因为在XTP层通过InvestorID 
//  找到多个ClientID。
/// 输入参数：
/// brokerID		经纪公司编号
/// userID   		用户代码
/// exchangeID		交易所代码
/// investorID		投资者编号
/// instrumentID	合约代码
/// clientID		客户编码
/// logBrokerID		登录经纪公司编号
/// logUserID		登录用户代码
/// sessionRef		引用的会话对象
/// pTransaction	事务对象指针
///
/// 输出参数：
///	pIterator		迭代器指针的指针，用于返回查询到的对象
*/
bool CTradingQueryImpl::QueryInvestorPosition(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CExchangeIDType& exchangeID,
					CInvestorIDType& investorID,
					CInstrumentIDType& instrumentID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CInvestorPositionIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
	if (brokerID != logBrokerID)
	{	// 用户登录的BrokerID 与 他要查询的 BrokerID 不一致。不允许查别人的信息
		m_ErrorEngine->reportError(ERROR_BROKERID_MISMATCH); 
		return false;
	}
	
	bool bHasInvestor = false;
	vInvestorID.clear();
	if (!isAdmin(logUserID,brokerID))
	{
		if ( userID.isNull() )
		{ // 没有设置用户ID，强行设置。因为只能查询自己的账户
			userID = logUserID;
		}
		else
		{
			if (userID != logUserID) 
			{	// 用户登录的ID 与 他要查询的 UserID 不一致。不允许查别人的信息
				m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
				return false;
			}
		}
	
		// 如果investorID中有值，就进行身份检查，看看要查询的investorID与用户是否有关系。无关系，则报错
		if (!investorID.isNull())
		{
			bHasInvestor = true;
			if (! CheckUserInvestor(brokerID,logUserID,investorID))
			{
				m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
				return false;
			}
			vInvestorID.push_back(investorID);
		}
		else
		{
			// 参数investorID 为空，从 userID 查找到 investorID 数组
			fromUserGetInvestors(brokerID,userID,vInvestorID);
		}
	}
	else
	{ // 是管理员
		// 如果investorID中有值，就进行身份检查，看看要查询的investorID与用户是否有关系。无关系，则报错
		if (!investorID.isNull())
		{
			if (! CheckUserInvestor(brokerID,userID,investorID))
			{
				m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
				return false;
			}
			vInvestorID.push_back(investorID);
		}
		else
		{	
			// 参数investorID 为空，从 userID 查找到 investorID 数组
			fromUserGetInvestors(brokerID,userID,vInvestorID);
		}	
	}
	
	
	CInvestorPositionFactory *thisFactory = m_DB->m_InvestorPositionFactory;
	CInvestorPositionPredict *pPredict;

  
	int iCount;
	CInvestorPositionPredict* pMultiPredict=NULL;
	for(iCount=0;iCount<vInvestorID.size();iCount++)
	{
		CInvestorPositionPredict *pTmpPredict= new CInvestorPositionInvestorIDPredict(&vInvestorID[iCount],&vInvestorID[iCount]);
		if(pMultiPredict==NULL)
		{
			pMultiPredict = pTmpPredict;
		}
		else
		{
			pMultiPredict = new CInvestorPositionOrPredict(pMultiPredict,pTmpPredict);
		}	
	}
	CClientIDType sNotExistInvestorID = CAN_NOT_EXIST_INVESTORID;
	if (NULL == pMultiPredict)
	{
		pMultiPredict = new CInvestorPositionClientIDPredict(&sNotExistInvestorID,&sNotExistInvestorID);
	}

	pPredict= new CInvestorPositionAndPredict(new CInvestorPositionBrokerIDPredict(&brokerID,&brokerID),pMultiPredict);


	CInvestorPositionIterator *pBaseIterator;

	if (!instrumentID.isNull())
	{
		pBaseIterator = new CInvestorPositionIteratorAllByInstrumentID(thisFactory,instrumentID);
	}
	else if(!exchangeID.isNull())
	{
		pBaseIterator = new CInvestorPositionIteratorAllByExchangeID(thisFactory,exchangeID);
	}
	else
	{
		pBaseIterator = new CInvestorPositionIteratorAll(thisFactory);
	}

	*pIterator = new CInvestorPositionFilter(pBaseIterator,pPredict,false);
	return true;
}

/*  查询用户投资者关系表，看看是否真的有brokerID，userID，investorID组合的记录
//  如果没有这样的记录，说明这些参数不合法。用户不能随便填写investorID之类的值，去查询别人的参数
//  在调用这个函数前，要保证参数 investorID 不为空。
*/
bool CTradingQueryImpl::CheckUserInvestor(const CBrokerIDType& brokerID,
						const CUserIDType& userID,const CInvestorIDType& investorID)
{
	CUserInvestorFactory *thisFactory = m_DB->m_UserInvestorFactory;	
	CUserInvestor * pData = thisFactory->findByBrokerIDUserIDInvestorID(brokerID,userID,investorID);		
	if(pData)
	{	// 有记录。因为brokerID+userID+investorID是主键，所以结果是唯一的
/*
	if (brokerID.isNull())
		{	// brokerID为空，说明brokerID为任何值都可以
			return true;
		}
		if(pData->BrokerID == brokerID)
		{
			return true;
		}else
		{// brokerID 与记录不一样，说明这条记录与参数不匹配。即 参数不合法
			return false;
		}
*/
		return true;
	}else
	{
		return false;
	}
}
/*	从用户的UserID，来查询用户的InvestorID。目前，一个用户最多对应4个InvestorID（4个交易所）。
/// 输入参数 userID 一定不能为空。brokerID 可以为空。
/// 用于表 ClientTradingID
*/
void * CTradingQueryImpl::fromUserGetInvestor(const CBrokerIDType& brokerID,const CUserIDType& userID)
{
	CClientTradingIDPredict *pMultiPredict = NULL;
	int	count = 1;

	CUserInvestorFactory *thisFactory = m_DB->m_UserInvestorFactory;	
	CUserInvestor * pData = thisFactory->startFindAllByUserID(userID);		
	while(pData)
	{	// 找到一个记录。 输入的 brokerID 若为空，表示 brokerID 不做限制
		if( (brokerID.isNull() ) ||( brokerID == pData->BrokerID))
		{
			// CInvestorIDType sInvestorID;
			// sInvestorID = pData->InvestorID;
			if(count<2)
			{
				pMultiPredict = new CClientTradingIDInvestorIDPredict( 
					const_cast<CInvestorIDType *>(&(pData->InvestorID)),
					const_cast<CInvestorIDType *>(&(pData->InvestorID)) );
				count++;
			}else
			{
				pMultiPredict = new CClientTradingIDOrPredict(pMultiPredict,new CClientTradingIDInvestorIDPredict(
					const_cast<CInvestorIDType *>(&(pData->InvestorID)),
					const_cast<CInvestorIDType *>(&(pData->InvestorID)) ) );
				count++;
			}
		}
		pData = thisFactory->findNextAllByUserID();
	}
	thisFactory->endFindAllByUserID();
	return pMultiPredict;
}


/*	从用户的UserID，来查询用户的InvestorID。目前，一个用户最多对应4个InvestorID（4个交易所）。再查询到ClientID
/// 输入参数 userID 一定不能为空。brokerID 可以为空。
/// 用于直接找到InvestorIDs
*/
void CTradingQueryImpl::fromUserGetInvestors(const CBrokerIDType& brokerID,const CUserIDType& userID,InvestorIDVector& vInvestorID)
{
	int	count = 1;
	CInvestorIDType sInvestorID;

	CUserInvestorFactory *thisFactory = m_DB->m_UserInvestorFactory;	
	CUserInvestor * pData = thisFactory->startFindAllByUserID(userID);		
	while(pData)
	{	// 找到一个记录。 输入的 brokerID 若为空，表示 brokerID 不做限制
		//if( (brokerID.isNull() ) ||( brokerID == pData->BrokerID))
		//{
			sInvestorID = pData->InvestorID;
			vInvestorID.push_back(sInvestorID);
		//}
		pData = thisFactory->findNextAllByUserID();
	}
	thisFactory->endFindAllByUserID();
	return ;
}

/*** SIR XLONG BEGIN ***/
///保证金率查询:根据brokerID以及instrumentID 查询保证金率表
///说明：如果brokerID为空，则根据instrumentID是否为空的情况放回CInvestorMarginIteratorAll（instrumentID为空）或者CInvestorMarginIteratorByInstrumentID（instrumentID不为空）
///      否则返回CInvestorMarginIteratorByBrokerID
///@param   brokerID
///@param	instrumentID
///@return	true表示成功，false表示失败 	
bool CTradingQueryImpl::QueryInvestorMargin(
								 CBrokerIDType& brokerID,
								 CInstrumentIDType &instrumentID,
								 CInvestorMarginIterator** pIterator)
{
	CInvestorMarginFactory *pFactory = m_DB->m_InvestorMarginFactory;
	if (!pFactory)
	{
		m_ErrorEngine->reportError(ERROR_NO_CLIENT_MARGIN_FEE_DATA);
		return false;
	}
	
	if (brokerID.isNull())
	{
		if (instrumentID.isNull())
		{
			*pIterator = new CInvestorMarginIteratorAll(pFactory);
		}
		else
		{
			*pIterator = new CInvestorMarginIteratorByInstrumentID(pFactory, instrumentID);
		}
	}
	else
	{
		*pIterator = new CInvestorMarginIteratorByBrokerID(pFactory, brokerID);
	}

	return true;
}

///手续费率查询：根据brokerID以及instrumentID 查询手续费率表
///说明：如果brokerID为空，则根据instrumentID是否为空的情况放回CInvestorMarginIteratorAll（instrumentID为空）或者CInvestorMarginIteratorByInstrumentID（instrumentID不为空）
///      否则返回CInvestorMarginIteratorByBrokerID
///@param   brokerID
///@param	instrumentID
///@return	true表示成功，false表示失败 	
bool CTradingQueryImpl:: QueryInvestorFee(
							  CBrokerIDType& brokerID,
							  CInstrumentIDType &instrumentID,
							  CInvestorFeeIterator** pIterator)

{
	CInvestorFeeFactory *pFactory = m_DB->m_InvestorFeeFactory;
	if (!pFactory) 
	{
		m_ErrorEngine->reportError(ERROR_NO_CLIENT_MARGIN_FEE_DATA);
		return false;
	}
	
	if (brokerID.isNull())
	{
		if (instrumentID.isNull())
		{
			*pIterator = new CInvestorFeeIteratorAll(pFactory);
		}
		else
		{
			*pIterator = new CInvestorFeeIteratorByInstrumentID(pFactory, instrumentID);
		}
	}
	else
	{
		*pIterator = new CInvestorFeeIteratorByBrokerID(pFactory, brokerID);
	}
	return true;
}

///投资者查询：根据userID 查询投资者表
///@param   userID
///@return	true表示成功，false表示失败 	
bool CTradingQueryImpl:: QueryUserInvestorByUser(
										  CUserIDType& userID,
										  CUserInvestorIteratorAllByUserID** pIterator)
										  
{
	CUserInvestorFactory *pFactory = m_DB->m_UserInvestorFactory;
	if (!pFactory) 
	{
		m_ErrorEngine->reportError(ERROR_USERID_INVESTORID_BOTHBLANK);
		return false;
	}
	
	if (userID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_USERID_INVESTORID_BOTHBLANK);
		return false;
	}
	else
	{
		*pIterator = new CUserInvestorIteratorAllByUserID(pFactory, userID);
	}
	return true;
}
/*** SIR XLONG END ***/

void CTradingQueryImpl::fromInvestorsGetAccount(const CBrokerIDType& brokerID, const CInvestorIDType& investorID, AccountIDVector& vAccountID)
{
	CAccountIDType sAccountID;

	CInvestorAccountFactory *thisFactory = m_DB->m_InvestorAccountFactory;	
	CInvestorAccount * pData = thisFactory->findByBrokerIDInvestorID(brokerID, investorID);
	
	if (NULL != pData)
	{
		sAccountID = pData->AccountID;
		vector<CAccountIDType>::iterator result = find( vAccountID.begin( ), vAccountID.end( ), sAccountID );
		if ( result == vAccountID.end( ) )
		{
			vAccountID.push_back(sAccountID);
		}
	}

	return ;
}

///金交所递延费率查询请求
///@param	sessionRef	会话引用
///@param	pTransaction	本操作属于的事务
///@return	true表示成功，false表示失败 	
bool CTradingQueryImpl::QuerySGEDeferRate(
				   CInstrumentIDType& instrumentID,
				   CSGEDeferRateIterator** pIterator,
				   const TSessionRef &sessionRef,
				   CTransaction *pTransaction)
{
	CSGEDeferRateFactory *thisFactory = m_DB->m_SGEDeferRateFactory;
	
	if (!instrumentID.isNull())
	{
		*pIterator = new CSGEDeferRateIteratorAllByInstrumentID(thisFactory,instrumentID);
	}
	else 
	{
		*pIterator = new CSGEDeferRateIteratorAll(thisFactory);
	}
	
	return true;
}


/*	QueryExchange 交易时间偏差查询请求
/// 交易时间偏差是公开的，只要能够登录的用户都可以查询。不需要进行权限检查。
/// 输入参数：
/// exchangeID		交易所代码
/// sessionRef		引用的会话对象
/// pTransaction	事务对象指针
///
/// 输出参数：
///	pIterator		迭代器指针的指针，用于返回查询到的对象
*/
bool CTradingQueryImpl::QueryExchTimeDiff(
										  CExchangeIDType& exchangeID,
										  CExchTimeDiffIterator** pIterator,
										  const TSessionRef &sessionRef,
										  CTransaction *pTransaction)
{
	CExchTimeDiffFactory *thisFactory = m_DB->m_ExchTimeDiffFactory;
	CExchTimeDiffPredict *pPredict;
	pPredict = new CExchTimeDiffExchangeIDPredict(&exchangeID,&exchangeID);
	
	CExchTimeDiffIterator *pBaseIterator;
	if (!exchangeID.isNull())
	{
		pBaseIterator = new CExchTimeDiffIteratorStartByExchangeID(thisFactory,exchangeID);
	}
	else 
	{
		pBaseIterator = new CExchTimeDiffIteratorAll(thisFactory);
	}
	
	*pIterator = new CExchTimeDiffFilter(pBaseIterator,pPredict,false);
	
	return true;
	
}
