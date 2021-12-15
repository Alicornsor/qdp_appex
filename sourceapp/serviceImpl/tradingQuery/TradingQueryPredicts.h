/////////////////////////////////////////////////////////////////////////
///@system 极速风控前置 执行引擎系统
///@company 上海量投网络科技有限公司
///@file TradingQueryPredicts.h
///@brief	定义了查询用的各种基础的谓词
///@history 
///20121115		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef TRADINGQUERYPREDICTS_H
#define TRADINGQUERYPREDICTS_H

#include "databaseIteratorRepository.h"

/////////////////////////////////////////////////////////////////////////
///COrderActionExchangeIDPredict是判断一个报单操作是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionExchangeIDPredict: public COrderActionPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderActionExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~COrderActionExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderAction	要被判断的报单操作
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionOrderSysIDPredict是判断一个报单操作是否满足报单编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionOrderSysIDPredict: public COrderActionPredict
{
private:
	COrderSysIDType *m_pOrderSysIDStart;
	COrderSysIDType *m_pOrderSysIDEnd;
public:
	///构造方法
	///@param	pOrderSysIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pOrderSysIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderActionOrderSysIDPredict(COrderSysIDType *pOrderSysIDStart, COrderSysIDType *pOrderSysIDEnd)
	{
		m_pOrderSysIDStart=pOrderSysIDStart;
		m_pOrderSysIDEnd=pOrderSysIDEnd;
	}

	virtual ~COrderActionOrderSysIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderAction	要被判断的报单操作
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionBrokerIDPredict是判断一个报单操作是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionBrokerIDPredict: public COrderActionPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderActionBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~COrderActionBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderAction	要被判断的报单操作
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionInvestorIDPredict是判断一个报单操作是否满足投资者编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionInvestorIDPredict: public COrderActionPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderActionInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~COrderActionInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderAction	要被判断的报单操作
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionUserIDPredict是判断一个报单操作是否满足用户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionUserIDPredict: public COrderActionPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///构造方法
	///@param	pUserIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pUserIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderActionUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~COrderActionUserIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderAction	要被判断的报单操作
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionInstrumentIDStartPredict是判断一个报单操作是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionInstrumentIDStartPredict: public COrderActionPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	COrderActionInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~COrderActionInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderAction	要被判断的报单操作
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionClientIDPredict是判断一个报单操作是否满足客户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionClientIDPredict: public COrderActionPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///构造方法
	///@param	pClientIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pClientIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderActionClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~COrderActionClientIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderAction	要被判断的报单操作
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionParticipantIDPredict是判断一个报单操作是否满足会员代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionParticipantIDPredict: public COrderActionPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///构造方法
	///@param	pParticipantIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pParticipantIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderActionParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~COrderActionParticipantIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderAction	要被判断的报单操作
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderAction *pOrderAction);
};

/////////////////////////////////////////////////////////////////////////
///COrderBrokerIDPredict是判断一个委托表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderBrokerIDPredict: public COrderPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~COrderBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrder	要被判断的委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderExchangeIDPredict是判断一个委托表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderExchangeIDPredict: public COrderPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~COrderExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrder	要被判断的委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderOrderSysIDPredict是判断一个委托表是否满足系统报单编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderOrderSysIDPredict: public COrderPredict
{
private:
	COrderSysIDType *m_pOrderSysIDStart;
	COrderSysIDType *m_pOrderSysIDEnd;
public:
	///构造方法
	///@param	pOrderSysIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pOrderSysIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderOrderSysIDPredict(COrderSysIDType *pOrderSysIDStart, COrderSysIDType *pOrderSysIDEnd)
	{
		m_pOrderSysIDStart=pOrderSysIDStart;
		m_pOrderSysIDEnd=pOrderSysIDEnd;
	}

	virtual ~COrderOrderSysIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrder	要被判断的委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderInvestorIDPredict是判断一个委托表是否满足投资者编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInvestorIDPredict: public COrderPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~COrderInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrder	要被判断的委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderUserIDPredict是判断一个委托表是否满足用户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderUserIDPredict: public COrderPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///构造方法
	///@param	pUserIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pUserIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~COrderUserIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrder	要被判断的委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderInstrumentIDStartPredict是判断一个委托表是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInstrumentIDStartPredict: public COrderPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	COrderInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~COrderInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrder	要被判断的委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderDirectionPredict是判断一个委托表是否满足买卖方向条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDirectionPredict: public COrderPredict
{
private:
	CDirectionType *m_pDirectionStart;
	CDirectionType *m_pDirectionEnd;
public:
	///构造方法
	///@param	pDirectionStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pDirectionEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderDirectionPredict(CDirectionType *pDirectionStart, CDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~COrderDirectionPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrder	要被判断的委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderParticipantIDPredict是判断一个委托表是否满足会员编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderParticipantIDPredict: public COrderPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///构造方法
	///@param	pParticipantIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pParticipantIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~COrderParticipantIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrder	要被判断的委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderClientIDPredict是判断一个委托表是否满足客户号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderClientIDPredict: public COrderPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///构造方法
	///@param	pClientIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pClientIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~COrderClientIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrder	要被判断的委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertTimePredict是判断一个委托表是否满足插入时间条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertTimePredict: public COrderPredict
{
private:
	CTimeType *m_pInsertTimeStart;
	CTimeType *m_pInsertTimeEnd;
public:
	///构造方法
	///@param	pInsertTimeStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInsertTimeEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderInsertTimePredict(CTimeType *pInsertTimeStart, CTimeType *pInsertTimeEnd)
	{
		m_pInsertTimeStart=pInsertTimeStart;
		m_pInsertTimeEnd=pInsertTimeEnd;
	}

	virtual ~COrderInsertTimePredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrder	要被判断的委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///COrderAccountIDPredict是判断一个委托表是否满足资金帐号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderAccountIDPredict: public COrderPredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///构造方法
	///@param	pAccountIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pAccountIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~COrderAccountIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrder	要被判断的委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrder *pOrder);
};

/////////////////////////////////////////////////////////////////////////
///CTradeBrokerIDPredict是判断一个成交表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeBrokerIDPredict: public CTradePredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CTradeBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CTradeBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeExchangeIDPredict是判断一个成交表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeExchangeIDPredict: public CTradePredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CTradeExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CTradeExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeParticipantIDPredict是判断一个成交表是否满足会员编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeParticipantIDPredict: public CTradePredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///构造方法
	///@param	pParticipantIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pParticipantIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CTradeParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~CTradeParticipantIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeInvestorIDPredict是判断一个成交表是否满足投资者编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeInvestorIDPredict: public CTradePredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CTradeInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CTradeInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeClientIDPredict是判断一个成交表是否满足客户号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeClientIDPredict: public CTradePredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///构造方法
	///@param	pClientIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pClientIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CTradeClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~CTradeClientIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeUserIDPredict是判断一个成交表是否满足用户编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeUserIDPredict: public CTradePredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///构造方法
	///@param	pUserIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pUserIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CTradeUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CTradeUserIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeTradeIDPredict是判断一个成交表是否满足成交编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeTradeIDPredict: public CTradePredict
{
private:
	CTradeIDType *m_pTradeIDStart;
	CTradeIDType *m_pTradeIDEnd;
public:
	///构造方法
	///@param	pTradeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pTradeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CTradeTradeIDPredict(CTradeIDType *pTradeIDStart, CTradeIDType *pTradeIDEnd)
	{
		m_pTradeIDStart=pTradeIDStart;
		m_pTradeIDEnd=pTradeIDEnd;
	}

	virtual ~CTradeTradeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeOrderSysIDPredict是判断一个成交表是否满足报单编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeOrderSysIDPredict: public CTradePredict
{
private:
	COrderSysIDType *m_pOrderSysIDStart;
	COrderSysIDType *m_pOrderSysIDEnd;
public:
	///构造方法
	///@param	pOrderSysIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pOrderSysIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CTradeOrderSysIDPredict(COrderSysIDType *pOrderSysIDStart, COrderSysIDType *pOrderSysIDEnd)
	{
		m_pOrderSysIDStart=pOrderSysIDStart;
		m_pOrderSysIDEnd=pOrderSysIDEnd;
	}

	virtual ~CTradeOrderSysIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeInstrumentIDStartPredict是判断一个成交表是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeInstrumentIDStartPredict: public CTradePredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	CTradeInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CTradeInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeDirectionPredict是判断一个成交表是否满足买卖方向条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeDirectionPredict: public CTradePredict
{
private:
	CDirectionType *m_pDirectionStart;
	CDirectionType *m_pDirectionEnd;
public:
	///构造方法
	///@param	pDirectionStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pDirectionEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CTradeDirectionPredict(CDirectionType *pDirectionStart, CDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~CTradeDirectionPredict()
	{
	}	
	
	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeTradeTimePredict是判断一个成交表是否满足成交时间条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeTradeTimePredict: public CTradePredict
{
private:
	CTimeType *m_pTradeTimeStart;
	CTimeType *m_pTradeTimeEnd;
public:
	///构造方法
	///@param	pTradeTimeStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pTradeTimeEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CTradeTradeTimePredict(CTimeType *pTradeTimeStart, CTimeType *pTradeTimeEnd)
	{
		m_pTradeTimeStart=pTradeTimeStart;
		m_pTradeTimeEnd=pTradeTimeEnd;
	}

	virtual ~CTradeTradeTimePredict()
	{
	}	
	
	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeClearingPartIDPredict是判断一个成交表是否满足清算会员编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeClearingPartIDPredict: public CTradePredict
{
private:
	CParticipantIDType *m_pClearingPartIDStart;
	CParticipantIDType *m_pClearingPartIDEnd;
public:
	///构造方法
	///@param	pClearingPartIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pClearingPartIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CTradeClearingPartIDPredict(CParticipantIDType *pClearingPartIDStart, CParticipantIDType *pClearingPartIDEnd)
	{
		m_pClearingPartIDStart=pClearingPartIDStart;
		m_pClearingPartIDEnd=pClearingPartIDEnd;
	}

	virtual ~CTradeClearingPartIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CTradeAccountIDPredict是判断一个成交表是否满足资金帐号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeAccountIDPredict: public CTradePredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///构造方法
	///@param	pAccountIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pAccountIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CTradeAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~CTradeAccountIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderBrokerIDPredict是判断一个预委托表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderBrokerIDPredict: public CPreOrderPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CPreOrderBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CPreOrderBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pPreOrder	要被判断的预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderExchangeIDPredict是判断一个预委托表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderExchangeIDPredict: public CPreOrderPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CPreOrderExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CPreOrderExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pPreOrder	要被判断的预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderOrderSysIDPredict是判断一个预委托表是否满足系统报单编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderOrderSysIDPredict: public CPreOrderPredict
{
private:
	COrderSysIDType *m_pOrderSysIDStart;
	COrderSysIDType *m_pOrderSysIDEnd;
public:
	///构造方法
	///@param	pOrderSysIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pOrderSysIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CPreOrderOrderSysIDPredict(COrderSysIDType *pOrderSysIDStart, COrderSysIDType *pOrderSysIDEnd)
	{
		m_pOrderSysIDStart=pOrderSysIDStart;
		m_pOrderSysIDEnd=pOrderSysIDEnd;
	}

	virtual ~CPreOrderOrderSysIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pPreOrder	要被判断的预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderInvestorIDPredict是判断一个预委托表是否满足投资者编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderInvestorIDPredict: public CPreOrderPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CPreOrderInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CPreOrderInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pPreOrder	要被判断的预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderUserIDPredict是判断一个预委托表是否满足用户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderUserIDPredict: public CPreOrderPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///构造方法
	///@param	pUserIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pUserIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CPreOrderUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CPreOrderUserIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pPreOrder	要被判断的预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderInstrumentIDStartPredict是判断一个预委托表是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderInstrumentIDStartPredict: public CPreOrderPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	CPreOrderInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CPreOrderInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pPreOrder	要被判断的预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderDirectionPredict是判断一个预委托表是否满足买卖方向条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderDirectionPredict: public CPreOrderPredict
{
private:
	CDirectionType *m_pDirectionStart;
	CDirectionType *m_pDirectionEnd;
public:
	///构造方法
	///@param	pDirectionStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pDirectionEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CPreOrderDirectionPredict(CDirectionType *pDirectionStart, CDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~CPreOrderDirectionPredict()
	{
	}	
	
	///判断是否合法
	///@param	pPreOrder	要被判断的预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderParticipantIDPredict是判断一个预委托表是否满足会员编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderParticipantIDPredict: public CPreOrderPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///构造方法
	///@param	pParticipantIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pParticipantIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CPreOrderParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~CPreOrderParticipantIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pPreOrder	要被判断的预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderClientIDPredict是判断一个预委托表是否满足客户号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderClientIDPredict: public CPreOrderPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///构造方法
	///@param	pClientIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pClientIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CPreOrderClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~CPreOrderClientIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pPreOrder	要被判断的预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderInsertTimePredict是判断一个预委托表是否满足插入时间条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderInsertTimePredict: public CPreOrderPredict
{
private:
	CTimeType *m_pInsertTimeStart;
	CTimeType *m_pInsertTimeEnd;
public:
	///构造方法
	///@param	pInsertTimeStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInsertTimeEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CPreOrderInsertTimePredict(CTimeType *pInsertTimeStart, CTimeType *pInsertTimeEnd)
	{
		m_pInsertTimeStart=pInsertTimeStart;
		m_pInsertTimeEnd=pInsertTimeEnd;
	}

	virtual ~CPreOrderInsertTimePredict()
	{
	}	
	
	///判断是否合法
	///@param	pPreOrder	要被判断的预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderAccountIDPredict是判断一个预委托表是否满足资金帐号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderAccountIDPredict: public CPreOrderPredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///构造方法
	///@param	pAccountIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pAccountIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CPreOrderAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~CPreOrderAccountIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pPreOrder	要被判断的预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPreOrder *pPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderBrokerIDPredict是判断一个索引预委托表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderBrokerIDPredict: public CIndexPreOrderPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CIndexPreOrderBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CIndexPreOrderBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pIndexPreOrder	要被判断的索引预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderExchangeIDPredict是判断一个索引预委托表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderExchangeIDPredict: public CIndexPreOrderPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CIndexPreOrderExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CIndexPreOrderExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pIndexPreOrder	要被判断的索引预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderInvestorIDPredict是判断一个索引预委托表是否满足投资者编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderInvestorIDPredict: public CIndexPreOrderPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CIndexPreOrderInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CIndexPreOrderInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pIndexPreOrder	要被判断的索引预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderInstrumentIDStartPredict是判断一个索引预委托表是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderInstrumentIDStartPredict: public CIndexPreOrderPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	CIndexPreOrderInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CIndexPreOrderInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pIndexPreOrder	要被判断的索引预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderDirectionPredict是判断一个索引预委托表是否满足买卖方向条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderDirectionPredict: public CIndexPreOrderPredict
{
private:
	CDirectionType *m_pDirectionStart;
	CDirectionType *m_pDirectionEnd;
public:
	///构造方法
	///@param	pDirectionStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pDirectionEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CIndexPreOrderDirectionPredict(CDirectionType *pDirectionStart, CDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~CIndexPreOrderDirectionPredict()
	{
	}	
	
	///判断是否合法
	///@param	pIndexPreOrder	要被判断的索引预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderClientIDPredict是判断一个索引预委托表是否满足交易编码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderClientIDPredict: public CIndexPreOrderPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///构造方法
	///@param	pClientIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pClientIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CIndexPreOrderClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~CIndexPreOrderClientIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pIndexPreOrder	要被判断的索引预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionBrokerIDPredict是判断一个持仓表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionBrokerIDPredict: public CInvestorPositionPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorPositionBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorPositionBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorPosition	要被判断的持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionExchangeIDPredict是判断一个持仓表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionExchangeIDPredict: public CInvestorPositionPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorPositionExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CInvestorPositionExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorPosition	要被判断的持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionInvestorIDPredict是判断一个持仓表是否满足投资者编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionInvestorIDPredict: public CInvestorPositionPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorPositionInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorPositionInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorPosition	要被判断的持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionParticipantIDPredict是判断一个持仓表是否满足会员编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionParticipantIDPredict: public CInvestorPositionPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///构造方法
	///@param	pParticipantIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pParticipantIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorPositionParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~CInvestorPositionParticipantIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorPosition	要被判断的持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionClientIDPredict是判断一个持仓表是否满足客户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionClientIDPredict: public CInvestorPositionPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///构造方法
	///@param	pClientIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pClientIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorPositionClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~CInvestorPositionClientIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorPosition	要被判断的持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionInstrumentIDStartPredict是判断一个持仓表是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionInstrumentIDStartPredict: public CInvestorPositionPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	CInvestorPositionInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CInvestorPositionInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorPosition	要被判断的持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionDirectionPredict是判断一个持仓表是否满足买卖方向条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionDirectionPredict: public CInvestorPositionPredict
{
private:
	CDirectionType *m_pDirectionStart;
	CDirectionType *m_pDirectionEnd;
public:
	///构造方法
	///@param	pDirectionStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pDirectionEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorPositionDirectionPredict(CDirectionType *pDirectionStart, CDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~CInvestorPositionDirectionPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorPosition	要被判断的持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionAccountIDPredict是判断一个持仓表是否满足资金帐号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionAccountIDPredict: public CInvestorPositionPredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///构造方法
	///@param	pAccountIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pAccountIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorPositionAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~CInvestorPositionAccountIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorPosition	要被判断的持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorPosition *pInvestorPosition);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountBrokerIDPredict是判断一个账户实时资金表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountBrokerIDPredict: public CInvestorAccountPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorAccountBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorAccountBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorAccount	要被判断的账户实时资金表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorAccount *pInvestorAccount);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountInvestorIDPredict是判断一个账户实时资金表是否满足投资者编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountInvestorIDPredict: public CInvestorAccountPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorAccountInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorAccountInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorAccount	要被判断的账户实时资金表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorAccount *pInvestorAccount);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountAccountIDPredict是判断一个账户实时资金表是否满足资金帐号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountAccountIDPredict: public CInvestorAccountPredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///构造方法
	///@param	pAccountIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pAccountIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorAccountAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~CInvestorAccountAccountIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorAccount	要被判断的账户实时资金表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorAccount *pInvestorAccount);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositBrokerIDPredict是判断一个账户实时出入金表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositBrokerIDPredict: public CInvestorAccountDepositPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorAccountDepositBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorAccountDepositBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorAccountDeposit	要被判断的账户实时出入金表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorAccountDeposit *pInvestorAccountDeposit);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositAccountIDPredict是判断一个账户实时出入金表是否满足资金帐号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositAccountIDPredict: public CInvestorAccountDepositPredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///构造方法
	///@param	pAccountIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pAccountIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorAccountDepositAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~CInvestorAccountDepositAccountIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorAccountDeposit	要被判断的账户实时出入金表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorAccountDeposit *pInvestorAccountDeposit);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositInvestorIDPredict是判断一个账户实时出入金表是否满足投资者编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositInvestorIDPredict: public CInvestorAccountDepositPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorAccountDepositInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorAccountDepositInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorAccountDeposit	要被判断的账户实时出入金表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorAccountDeposit *pInvestorAccountDeposit);
};

/////////////////////////////////////////////////////////////////////////
///CExchangeExchangeIDPredict是判断一个交易所表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeExchangeIDPredict: public CExchangePredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CExchangeExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CExchangeExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pExchange	要被判断的交易所表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CExchange *pExchange);
};

/////////////////////////////////////////////////////////////////////////
///CSeatBrokerIDPredict是判断一个下单席位表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatBrokerIDPredict: public CSeatPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CSeatBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CSeatBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pSeat	要被判断的下单席位表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSeat *pSeat);
};

/////////////////////////////////////////////////////////////////////////
///CSeatExchangeIDPredict是判断一个下单席位表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatExchangeIDPredict: public CSeatPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CSeatExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CSeatExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pSeat	要被判断的下单席位表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSeat *pSeat);
};

/////////////////////////////////////////////////////////////////////////
///CSeatParticipantIDPredict是判断一个下单席位表是否满足会员编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatParticipantIDPredict: public CSeatPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///构造方法
	///@param	pParticipantIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pParticipantIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CSeatParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~CSeatParticipantIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pSeat	要被判断的下单席位表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSeat *pSeat);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentExchangeIDPredict是判断一个期货合约表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentExchangeIDPredict: public CInstrumentPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInstrumentExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CInstrumentExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInstrument	要被判断的期货合约表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInstrument *pInstrument);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentProductIDPredict是判断一个期货合约表是否满足品种代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentProductIDPredict: public CInstrumentPredict
{
private:
	CProductIDType *m_pProductIDStart;
	CProductIDType *m_pProductIDEnd;
public:
	///构造方法
	///@param	pProductIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pProductIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInstrumentProductIDPredict(CProductIDType *pProductIDStart, CProductIDType *pProductIDEnd)
	{
		m_pProductIDStart=pProductIDStart;
		m_pProductIDEnd=pProductIDEnd;
	}

	virtual ~CInstrumentProductIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInstrument	要被判断的期货合约表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInstrument *pInstrument);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentInstrumentIDStartPredict是判断一个期货合约表是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentInstrumentIDStartPredict: public CInstrumentPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	CInstrumentInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CInstrumentInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInstrument	要被判断的期货合约表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInstrument *pInstrument);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentProductGroupIDPredict是判断一个期货合约表是否满足产品组条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentProductGroupIDPredict: public CInstrumentPredict
{
private:
	CProductGroupIDType *m_pProductGroupIDStart;
	CProductGroupIDType *m_pProductGroupIDEnd;
public:
	///构造方法
	///@param	pProductGroupIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pProductGroupIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInstrumentProductGroupIDPredict(CProductGroupIDType *pProductGroupIDStart, CProductGroupIDType *pProductGroupIDEnd)
	{
		m_pProductGroupIDStart=pProductGroupIDStart;
		m_pProductGroupIDEnd=pProductGroupIDEnd;
	}

	virtual ~CInstrumentProductGroupIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInstrument	要被判断的期货合约表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInstrument *pInstrument);
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailExchangeIDPredict是判断一个期货组合合约明细表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailExchangeIDPredict: public CCmbInstrumentDetailPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CCmbInstrumentDetailExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CCmbInstrumentDetailExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pCmbInstrumentDetail	要被判断的期货组合合约明细表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CCmbInstrumentDetail *pCmbInstrumentDetail);
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailDirectionPredict是判断一个期货组合合约明细表是否满足买卖方向条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailDirectionPredict: public CCmbInstrumentDetailPredict
{
private:
	CDirectionType *m_pDirectionStart;
	CDirectionType *m_pDirectionEnd;
public:
	///构造方法
	///@param	pDirectionStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pDirectionEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CCmbInstrumentDetailDirectionPredict(CDirectionType *pDirectionStart, CDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~CCmbInstrumentDetailDirectionPredict()
	{
	}	
	
	///判断是否合法
	///@param	pCmbInstrumentDetail	要被判断的期货组合合约明细表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CCmbInstrumentDetail *pCmbInstrumentDetail);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDBrokerIDPredict是判断一个交易所客户编码表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDBrokerIDPredict: public CClientTradingIDPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CClientTradingIDBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CClientTradingIDBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pClientTradingID	要被判断的交易所客户编码表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientTradingID *pClientTradingID);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDInvestorIDPredict是判断一个交易所客户编码表是否满足投资者编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDInvestorIDPredict: public CClientTradingIDPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CClientTradingIDInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CClientTradingIDInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pClientTradingID	要被判断的交易所客户编码表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientTradingID *pClientTradingID);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDAccountIDPredict是判断一个交易所客户编码表是否满足资金帐号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDAccountIDPredict: public CClientTradingIDPredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///构造方法
	///@param	pAccountIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pAccountIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CClientTradingIDAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~CClientTradingIDAccountIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pClientTradingID	要被判断的交易所客户编码表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientTradingID *pClientTradingID);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDExchangeIDPredict是判断一个交易所客户编码表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDExchangeIDPredict: public CClientTradingIDPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CClientTradingIDExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CClientTradingIDExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pClientTradingID	要被判断的交易所客户编码表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientTradingID *pClientTradingID);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDParticipantIDPredict是判断一个交易所客户编码表是否满足会员编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDParticipantIDPredict: public CClientTradingIDPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///构造方法
	///@param	pParticipantIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pParticipantIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CClientTradingIDParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~CClientTradingIDParticipantIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pClientTradingID	要被判断的交易所客户编码表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientTradingID *pClientTradingID);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDClientIDPredict是判断一个交易所客户编码表是否满足客户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDClientIDPredict: public CClientTradingIDPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///构造方法
	///@param	pClientIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pClientIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CClientTradingIDClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~CClientTradingIDClientIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pClientTradingID	要被判断的交易所客户编码表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientTradingID *pClientTradingID);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorBrokerIDPredict是判断一个投资者信息表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorBrokerIDPredict: public CInvestorPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestor	要被判断的投资者信息表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestor *pInvestor);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorInvestorIDPredict是判断一个投资者信息表是否满足投资者编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorInvestorIDPredict: public CInvestorPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestor	要被判断的投资者信息表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestor *pInvestor);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginBrokerIDPredict是判断一个客户期货保证金率表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginBrokerIDPredict: public CInvestorMarginPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorMarginBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorMarginBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorMargin	要被判断的客户期货保证金率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorMargin *pInvestorMargin);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginExchangeIDPredict是判断一个客户期货保证金率表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginExchangeIDPredict: public CInvestorMarginPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorMarginExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CInvestorMarginExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorMargin	要被判断的客户期货保证金率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorMargin *pInvestorMargin);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginInvestorIDPredict是判断一个客户期货保证金率表是否满足投资者编码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginInvestorIDPredict: public CInvestorMarginPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorMarginInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorMarginInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorMargin	要被判断的客户期货保证金率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorMargin *pInvestorMargin);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginInstrumentIDStartPredict是判断一个客户期货保证金率表是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginInstrumentIDStartPredict: public CInvestorMarginPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	CInvestorMarginInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CInvestorMarginInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorMargin	要被判断的客户期货保证金率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorMargin *pInvestorMargin);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeBrokerIDPredict是判断一个客户手续费率表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeBrokerIDPredict: public CInvestorFeePredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorFeeBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorFeeBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorFee	要被判断的客户手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorFee *pInvestorFee);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeExchangeIDPredict是判断一个客户手续费率表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeExchangeIDPredict: public CInvestorFeePredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorFeeExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CInvestorFeeExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorFee	要被判断的客户手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorFee *pInvestorFee);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeInvestorIDPredict是判断一个客户手续费率表是否满足投资者编码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeInvestorIDPredict: public CInvestorFeePredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorFeeInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorFeeInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorFee	要被判断的客户手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorFee *pInvestorFee);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeInstrumentIDStartPredict是判断一个客户手续费率表是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeInstrumentIDStartPredict: public CInvestorFeePredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	CInvestorFeeInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CInvestorFeeInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorFee	要被判断的客户手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorFee *pInvestorFee);
};

/////////////////////////////////////////////////////////////////////////
///CUserBrokerIDPredict是判断一个用户表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserBrokerIDPredict: public CUserPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CUserBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CUserBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pUser	要被判断的用户表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUser *pUser);
};

/////////////////////////////////////////////////////////////////////////
///CUserUserIDPredict是判断一个用户表是否满足用户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserUserIDPredict: public CUserPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///构造方法
	///@param	pUserIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pUserIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CUserUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CUserUserIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pUser	要被判断的用户表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUser *pUser);
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorBrokerIDPredict是判断一个用户投资者关系表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorBrokerIDPredict: public CUserInvestorPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CUserInvestorBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CUserInvestorBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pUserInvestor	要被判断的用户投资者关系表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserInvestor *pUserInvestor);
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorUserIDPredict是判断一个用户投资者关系表是否满足交易用户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorUserIDPredict: public CUserInvestorPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///构造方法
	///@param	pUserIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pUserIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CUserInvestorUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CUserInvestorUserIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pUserInvestor	要被判断的用户投资者关系表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserInvestor *pUserInvestor);
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorInvestorIDPredict是判断一个用户投资者关系表是否满足投资者编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorInvestorIDPredict: public CUserInvestorPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CUserInvestorInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CUserInvestorInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pUserInvestor	要被判断的用户投资者关系表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserInvestor *pUserInvestor);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedBrokerIDPredict是判断一个错单表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedBrokerIDPredict: public COrderInsertFailedPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderInsertFailedBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~COrderInsertFailedBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderInsertFailed	要被判断的错单表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedExchangeIDPredict是判断一个错单表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedExchangeIDPredict: public COrderInsertFailedPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderInsertFailedExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~COrderInsertFailedExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderInsertFailed	要被判断的错单表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedOrderSysIDPredict是判断一个错单表是否满足系统报单编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedOrderSysIDPredict: public COrderInsertFailedPredict
{
private:
	COrderSysIDType *m_pOrderSysIDStart;
	COrderSysIDType *m_pOrderSysIDEnd;
public:
	///构造方法
	///@param	pOrderSysIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pOrderSysIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderInsertFailedOrderSysIDPredict(COrderSysIDType *pOrderSysIDStart, COrderSysIDType *pOrderSysIDEnd)
	{
		m_pOrderSysIDStart=pOrderSysIDStart;
		m_pOrderSysIDEnd=pOrderSysIDEnd;
	}

	virtual ~COrderInsertFailedOrderSysIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderInsertFailed	要被判断的错单表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedInvestorIDPredict是判断一个错单表是否满足投资者编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedInvestorIDPredict: public COrderInsertFailedPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderInsertFailedInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~COrderInsertFailedInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderInsertFailed	要被判断的错单表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedUserIDPredict是判断一个错单表是否满足用户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedUserIDPredict: public COrderInsertFailedPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///构造方法
	///@param	pUserIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pUserIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderInsertFailedUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~COrderInsertFailedUserIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderInsertFailed	要被判断的错单表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedInstrumentIDStartPredict是判断一个错单表是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedInstrumentIDStartPredict: public COrderInsertFailedPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	COrderInsertFailedInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~COrderInsertFailedInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderInsertFailed	要被判断的错单表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedDirectionPredict是判断一个错单表是否满足买卖方向条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedDirectionPredict: public COrderInsertFailedPredict
{
private:
	CDirectionType *m_pDirectionStart;
	CDirectionType *m_pDirectionEnd;
public:
	///构造方法
	///@param	pDirectionStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pDirectionEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderInsertFailedDirectionPredict(CDirectionType *pDirectionStart, CDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~COrderInsertFailedDirectionPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderInsertFailed	要被判断的错单表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedParticipantIDPredict是判断一个错单表是否满足会员编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedParticipantIDPredict: public COrderInsertFailedPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///构造方法
	///@param	pParticipantIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pParticipantIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderInsertFailedParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~COrderInsertFailedParticipantIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderInsertFailed	要被判断的错单表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedClientIDPredict是判断一个错单表是否满足客户号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedClientIDPredict: public COrderInsertFailedPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///构造方法
	///@param	pClientIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pClientIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderInsertFailedClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~COrderInsertFailedClientIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderInsertFailed	要被判断的错单表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedInsertTimePredict是判断一个错单表是否满足插入时间条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedInsertTimePredict: public COrderInsertFailedPredict
{
private:
	CTimeType *m_pInsertTimeStart;
	CTimeType *m_pInsertTimeEnd;
public:
	///构造方法
	///@param	pInsertTimeStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInsertTimeEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderInsertFailedInsertTimePredict(CTimeType *pInsertTimeStart, CTimeType *pInsertTimeEnd)
	{
		m_pInsertTimeStart=pInsertTimeStart;
		m_pInsertTimeEnd=pInsertTimeEnd;
	}

	virtual ~COrderInsertFailedInsertTimePredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderInsertFailed	要被判断的错单表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedAccountIDPredict是判断一个错单表是否满足资金帐号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedAccountIDPredict: public COrderInsertFailedPredict
{
private:
	CAccountIDType *m_pAccountIDStart;
	CAccountIDType *m_pAccountIDEnd;
public:
	///构造方法
	///@param	pAccountIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pAccountIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderInsertFailedAccountIDPredict(CAccountIDType *pAccountIDStart, CAccountIDType *pAccountIDEnd)
	{
		m_pAccountIDStart=pAccountIDStart;
		m_pAccountIDEnd=pAccountIDEnd;
	}

	virtual ~COrderInsertFailedAccountIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderInsertFailed	要被判断的错单表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed);
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightBrokerIDPredict是判断一个用户交易权限表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightBrokerIDPredict: public CUserTradingRightPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CUserTradingRightBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CUserTradingRightBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pUserTradingRight	要被判断的用户交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserTradingRight *pUserTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightExchangeIDPredict是判断一个用户交易权限表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightExchangeIDPredict: public CUserTradingRightPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CUserTradingRightExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CUserTradingRightExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pUserTradingRight	要被判断的用户交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserTradingRight *pUserTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightInstrumentIDStartPredict是判断一个用户交易权限表是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightInstrumentIDStartPredict: public CUserTradingRightPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	CUserTradingRightInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CUserTradingRightInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pUserTradingRight	要被判断的用户交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserTradingRight *pUserTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightUserIDPredict是判断一个用户交易权限表是否满足用户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightUserIDPredict: public CUserTradingRightPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///构造方法
	///@param	pUserIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pUserIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CUserTradingRightUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CUserTradingRightUserIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pUserTradingRight	要被判断的用户交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserTradingRight *pUserTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightInvestorIDPredict是判断一个用户交易权限表是否满足投资者编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightInvestorIDPredict: public CUserTradingRightPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CUserTradingRightInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CUserTradingRightInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pUserTradingRight	要被判断的用户交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserTradingRight *pUserTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionBrokerIDPredict是判断一个交易员在线会话是否满足经纪公司代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionBrokerIDPredict: public CUserSessionPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CUserSessionBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CUserSessionBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pUserSession	要被判断的交易员在线会话
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserSession *pUserSession);
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionUserIDPredict是判断一个交易员在线会话是否满足交易用户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionUserIDPredict: public CUserSessionPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///构造方法
	///@param	pUserIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pUserIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CUserSessionUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CUserSessionUserIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pUserSession	要被判断的交易员在线会话
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserSession *pUserSession);
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDBrokerIDPredict是判断一个最大本地报单号是否满足经纪公司代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDBrokerIDPredict: public CMaxLocalIDPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CMaxLocalIDBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CMaxLocalIDBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pMaxLocalID	要被判断的最大本地报单号
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CMaxLocalID *pMaxLocalID);
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDUserIDPredict是判断一个最大本地报单号是否满足交易用户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDUserIDPredict: public CMaxLocalIDPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///构造方法
	///@param	pUserIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pUserIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CMaxLocalIDUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CMaxLocalIDUserIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pMaxLocalID	要被判断的最大本地报单号
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CMaxLocalID *pMaxLocalID);
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDBrokerIDPredict是判断一个用户本地报单号是否满足经纪公司代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDBrokerIDPredict: public CBrkUserIDLocalIDPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CBrkUserIDLocalIDBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CBrkUserIDLocalIDBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pBrkUserIDLocalID	要被判断的用户本地报单号
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CBrkUserIDLocalID *pBrkUserIDLocalID);
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDUserIDPredict是判断一个用户本地报单号是否满足交易用户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDUserIDPredict: public CBrkUserIDLocalIDPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///构造方法
	///@param	pUserIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pUserIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CBrkUserIDLocalIDUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CBrkUserIDLocalIDUserIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pBrkUserIDLocalID	要被判断的用户本地报单号
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CBrkUserIDLocalID *pBrkUserIDLocalID);
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionBrokerIDPredict是判断一个客户合约组持仓表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionBrokerIDPredict: public CPartClientInsGroupPositionPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CPartClientInsGroupPositionBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CPartClientInsGroupPositionBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pPartClientInsGroupPosition	要被判断的客户合约组持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition);
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionParticipantIDPredict是判断一个客户合约组持仓表是否满足会员代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionParticipantIDPredict: public CPartClientInsGroupPositionPredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///构造方法
	///@param	pParticipantIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pParticipantIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CPartClientInsGroupPositionParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~CPartClientInsGroupPositionParticipantIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pPartClientInsGroupPosition	要被判断的客户合约组持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition);
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionClientIDPredict是判断一个客户合约组持仓表是否满足客户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionClientIDPredict: public CPartClientInsGroupPositionPredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///构造方法
	///@param	pClientIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pClientIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CPartClientInsGroupPositionClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~CPartClientInsGroupPositionClientIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pPartClientInsGroupPosition	要被判断的客户合约组持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition);
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeBrokerIDPredict是判断一个交易编码组合保证金类型是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeBrokerIDPredict: public CClientMarginCombTypePredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CClientMarginCombTypeBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CClientMarginCombTypeBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pClientMarginCombType	要被判断的交易编码组合保证金类型
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientMarginCombType *pClientMarginCombType);
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeParticipantIDPredict是判断一个交易编码组合保证金类型是否满足会员代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeParticipantIDPredict: public CClientMarginCombTypePredict
{
private:
	CParticipantIDType *m_pParticipantIDStart;
	CParticipantIDType *m_pParticipantIDEnd;
public:
	///构造方法
	///@param	pParticipantIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pParticipantIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CClientMarginCombTypeParticipantIDPredict(CParticipantIDType *pParticipantIDStart, CParticipantIDType *pParticipantIDEnd)
	{
		m_pParticipantIDStart=pParticipantIDStart;
		m_pParticipantIDEnd=pParticipantIDEnd;
	}

	virtual ~CClientMarginCombTypeParticipantIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pClientMarginCombType	要被判断的交易编码组合保证金类型
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientMarginCombType *pClientMarginCombType);
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeClientIDPredict是判断一个交易编码组合保证金类型是否满足客户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeClientIDPredict: public CClientMarginCombTypePredict
{
private:
	CClientIDType *m_pClientIDStart;
	CClientIDType *m_pClientIDEnd;
public:
	///构造方法
	///@param	pClientIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pClientIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CClientMarginCombTypeClientIDPredict(CClientIDType *pClientIDStart, CClientIDType *pClientIDEnd)
	{
		m_pClientIDStart=pClientIDStart;
		m_pClientIDEnd=pClientIDEnd;
	}

	virtual ~CClientMarginCombTypeClientIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pClientMarginCombType	要被判断的交易编码组合保证金类型
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientMarginCombType *pClientMarginCombType);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupExchangeIDPredict是判断一个合约和合约组关系是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupExchangeIDPredict: public CInstrumentGroupPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInstrumentGroupExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CInstrumentGroupExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInstrumentGroup	要被判断的合约和合约组关系
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInstrumentGroup *pInstrumentGroup);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupBrokerIDPredict是判断一个合约和合约组关系是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupBrokerIDPredict: public CInstrumentGroupPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInstrumentGroupBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInstrumentGroupBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInstrumentGroup	要被判断的合约和合约组关系
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInstrumentGroup *pInstrumentGroup);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupInstrumentIDStartPredict是判断一个合约和合约组关系是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupInstrumentIDStartPredict: public CInstrumentGroupPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	CInstrumentGroupInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CInstrumentGroupInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInstrumentGroup	要被判断的合约和合约组关系
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInstrumentGroup *pInstrumentGroup);
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateInstrumentIDStartPredict是判断一个金交所递延费率表是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateInstrumentIDStartPredict: public CSGEDeferRatePredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	CSGEDeferRateInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CSGEDeferRateInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pSGEDeferRate	要被判断的金交所递延费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSGEDeferRate *pSGEDeferRate);
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateExchangeIDPredict是判断一个金交所递延费率表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateExchangeIDPredict: public CSGEDeferRatePredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CSGEDeferRateExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CSGEDeferRateExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pSGEDeferRate	要被判断的金交所递延费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSGEDeferRate *pSGEDeferRate);
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateDirectionPredict是判断一个金交所递延费率表是否满足支付方向条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateDirectionPredict: public CSGEDeferRatePredict
{
private:
	CPayDirectionType *m_pDirectionStart;
	CPayDirectionType *m_pDirectionEnd;
public:
	///构造方法
	///@param	pDirectionStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pDirectionEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CSGEDeferRateDirectionPredict(CPayDirectionType *pDirectionStart, CPayDirectionType *pDirectionEnd)
	{
		m_pDirectionStart=pDirectionStart;
		m_pDirectionEnd=pDirectionEnd;
	}

	virtual ~CSGEDeferRateDirectionPredict()
	{
	}	
	
	///判断是否合法
	///@param	pSGEDeferRate	要被判断的金交所递延费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSGEDeferRate *pSGEDeferRate);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightBrokerIDPredict是判断一个投资者交易权限表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightBrokerIDPredict: public CInvestorTradingRightPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorTradingRightBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorTradingRightBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorTradingRight	要被判断的投资者交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightInvestorIDPredict是判断一个投资者交易权限表是否满足投资者编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightInvestorIDPredict: public CInvestorTradingRightPredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorTradingRightInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorTradingRightInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorTradingRight	要被判断的投资者交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightExchangeIDPredict是判断一个投资者交易权限表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightExchangeIDPredict: public CInvestorTradingRightPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorTradingRightExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CInvestorTradingRightExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorTradingRight	要被判断的投资者交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightInstrumentIDStartPredict是判断一个投资者交易权限表是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightInstrumentIDStartPredict: public CInvestorTradingRightPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	CInvestorTradingRightInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CInvestorTradingRightInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorTradingRight	要被判断的投资者交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight);
};

/////////////////////////////////////////////////////////////////////////
///CUserIPBrokerIDPredict是判断一个交易员IP地址是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPBrokerIDPredict: public CUserIPPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CUserIPBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CUserIPBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pUserIP	要被判断的交易员IP地址
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserIP *pUserIP);
};

/////////////////////////////////////////////////////////////////////////
///CUserIPUserIDPredict是判断一个交易员IP地址是否满足交易用户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPUserIDPredict: public CUserIPPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///构造方法
	///@param	pUserIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pUserIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CUserIPUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~CUserIPUserIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pUserIP	要被判断的交易员IP地址
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserIP *pUserIP);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeBrokerIDPredict是判断一个客户期权手续费率表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeBrokerIDPredict: public CInvestorOptionFeePredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorOptionFeeBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~CInvestorOptionFeeBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorOptionFee	要被判断的客户期权手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeExchangeIDPredict是判断一个客户期权手续费率表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeExchangeIDPredict: public CInvestorOptionFeePredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorOptionFeeExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CInvestorOptionFeeExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorOptionFee	要被判断的客户期权手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeInvestorIDPredict是判断一个客户期权手续费率表是否满足投资者编码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeInvestorIDPredict: public CInvestorOptionFeePredict
{
private:
	CInvestorIDType *m_pInvestorIDStart;
	CInvestorIDType *m_pInvestorIDEnd;
public:
	///构造方法
	///@param	pInvestorIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInvestorIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CInvestorOptionFeeInvestorIDPredict(CInvestorIDType *pInvestorIDStart, CInvestorIDType *pInvestorIDEnd)
	{
		m_pInvestorIDStart=pInvestorIDStart;
		m_pInvestorIDEnd=pInvestorIDEnd;
	}

	virtual ~CInvestorOptionFeeInvestorIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorOptionFee	要被判断的客户期权手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeInstrumentIDStartPredict是判断一个客户期权手续费率表是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeInstrumentIDStartPredict: public CInvestorOptionFeePredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	CInvestorOptionFeeInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CInvestorOptionFeeInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pInvestorOptionFee	要被判断的客户期权手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee);
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataExchangeIDPredict是判断一个实时行情表是否满足交易所代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataExchangeIDPredict: public CMarketDataPredict
{
private:
	CExchangeIDType *m_pExchangeIDStart;
	CExchangeIDType *m_pExchangeIDEnd;
public:
	///构造方法
	///@param	pExchangeIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pExchangeIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	CMarketDataExchangeIDPredict(CExchangeIDType *pExchangeIDStart, CExchangeIDType *pExchangeIDEnd)
	{
		m_pExchangeIDStart=pExchangeIDStart;
		m_pExchangeIDEnd=pExchangeIDEnd;
	}

	virtual ~CMarketDataExchangeIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pMarketData	要被判断的实时行情表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CMarketData *pMarketData);
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataInstrumentIDStartPredict是判断一个实时行情表是否满足开始的合约代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataInstrumentIDStartPredict: public CMarketDataPredict
{
private:
	CInstrumentIDType *m_pInstrumentIDStart;
	CInstrumentIDType *m_pInstrumentIDEnd;
public:
	///构造方法
	///@param	pInstrumentIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pInstrumentIDEnd	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	CMarketDataInstrumentIDStartPredict(CInstrumentIDType *pInstrumentIDStart, CInstrumentIDType *pInstrumentIDEnd)
	{
		m_pInstrumentIDStart=pInstrumentIDStart;
		m_pInstrumentIDEnd=pInstrumentIDEnd;
	}

	virtual ~CMarketDataInstrumentIDStartPredict()
	{
	}	
	
	///判断是否合法
	///@param	pMarketData	要被判断的实时行情表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CMarketData *pMarketData);
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayBrokerIDPredict是判断一个委托延迟表是否满足经纪公司编号条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayBrokerIDPredict: public COrderDelayPredict
{
private:
	CBrokerIDType *m_pBrokerIDStart;
	CBrokerIDType *m_pBrokerIDEnd;
public:
	///构造方法
	///@param	pBrokerIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pBrokerIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderDelayBrokerIDPredict(CBrokerIDType *pBrokerIDStart, CBrokerIDType *pBrokerIDEnd)
	{
		m_pBrokerIDStart=pBrokerIDStart;
		m_pBrokerIDEnd=pBrokerIDEnd;
	}

	virtual ~COrderDelayBrokerIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderDelay	要被判断的委托延迟表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderDelay *pOrderDelay);
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayUserIDPredict是判断一个委托延迟表是否满足用户代码条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayUserIDPredict: public COrderDelayPredict
{
private:
	CUserIDType *m_pUserIDStart;
	CUserIDType *m_pUserIDEnd;
public:
	///构造方法
	///@param	pUserIDStart	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	pUserIDEnd	必须小于等于的值。如果为NULL，则忽略此条件
	COrderDelayUserIDPredict(CUserIDType *pUserIDStart, CUserIDType *pUserIDEnd)
	{
		m_pUserIDStart=pUserIDStart;
		m_pUserIDEnd=pUserIDEnd;
	}

	virtual ~COrderDelayUserIDPredict()
	{
	}	
	
	///判断是否合法
	///@param	pOrderDelay	要被判断的委托延迟表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderDelay *pOrderDelay);
};

#endif
