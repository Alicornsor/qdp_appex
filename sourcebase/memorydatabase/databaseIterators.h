/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseIterators.h
///@brief定义了若干个内存数据库的iterator
///@history 
///20060127	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef DATABASEITERATORS_H
#define DATABASEITERATORS_H

#include "BaseDataStruct.h"
#include "databaseFactories.h"
#include "MemoryStack.h"




/////////////////////////////////////////////////////////////////////////
///COrderIteratorAllByUserID是一个对委托表使用AllByUserID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderIteratorAllByUserID: public COrderIterator
{
	friend class COrderFactory;
private:
	///检查此对象是否满足条件
	///@param	pOrder		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(COrder *pOrder);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	COrder *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	COrder *m_pNext;

	///用于存储查询参数的对象
	CWriteableOrder m_compareObject;
	
	static CMemoryStack<COrderIteratorAllByUserID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	UserID	交易用户代码
	COrderIteratorAllByUserID(COrderFactory *pFactory
		,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,UserID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	UserID	交易用户代码
	static COrderIteratorAllByUserID *alloc(COrderFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///构造方法
	COrderIteratorAllByUserID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	UserID	交易用户代码
	void init(COrderFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///析构方法，将负责释放所占用的空间
	virtual ~COrderIteratorAllByUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的COrder，必须在startFindAllByUserID以后，endFindAllByUserID之前叫用
	///@return	下一个满足条件COrder，如果已经没有一个满足要求了，则返回NULL
	virtual COrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByUserID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrder * pAllByUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///COrderIteratorAllByInvestorID是一个对委托表使用AllByInvestorID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderIteratorAllByInvestorID: public COrderIterator
{
	friend class COrderFactory;
private:
	///检查此对象是否满足条件
	///@param	pOrder		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(COrder *pOrder);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	COrder *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	COrder *m_pNext;

	///用于存储查询参数的对象
	CWriteableOrder m_compareObject;
	
	static CMemoryStack<COrderIteratorAllByInvestorID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	投资者编号
	COrderIteratorAllByInvestorID(COrderFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,InvestorID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	投资者编号
	static COrderIteratorAllByInvestorID *alloc(COrderFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///构造方法
	COrderIteratorAllByInvestorID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	投资者编号
	void init(COrderFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///析构方法，将负责释放所占用的空间
	virtual ~COrderIteratorAllByInvestorID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的COrder，必须在startFindAllByInvestorID以后，endFindAllByInvestorID之前叫用
	///@return	下一个满足条件COrder，如果已经没有一个满足要求了，则返回NULL
	virtual COrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByInvestorID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrder * pAllByInvestorID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///COrderIteratorAllByExchIDInvIDUserID是一个对委托表使用AllByExchIDInvIDUserID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderIteratorAllByExchIDInvIDUserID: public COrderIterator
{
	friend class COrderFactory;
private:
	///检查此对象是否满足条件
	///@param	pOrder		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(COrder *pOrder);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	COrder *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	COrder *m_pNext;

	///用于存储查询参数的对象
	CWriteableOrder m_compareObject;
	
	static CMemoryStack<COrderIteratorAllByExchIDInvIDUserID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	UserID	交易用户代码
	COrderIteratorAllByExchIDInvIDUserID(COrderFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,ExchangeID,InvestorID,UserID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	UserID	交易用户代码
	static COrderIteratorAllByExchIDInvIDUserID *alloc(COrderFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID);

	///构造方法
	COrderIteratorAllByExchIDInvIDUserID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	UserID	交易用户代码
	void init(COrderFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID);

	///析构方法，将负责释放所占用的空间
	virtual ~COrderIteratorAllByExchIDInvIDUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的COrder，必须在startFindAllByExchIDInvIDUserID以后，endFindAllByExchIDInvIDUserID之前叫用
	///@return	下一个满足条件COrder，如果已经没有一个满足要求了，则返回NULL
	virtual COrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByExchIDInvIDUserID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrder * pAllByExchIDInvIDUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///COrderIteratorAllByExchIDInstruIDUserID是一个对委托表使用AllByExchIDInstruIDUserID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderIteratorAllByExchIDInstruIDUserID: public COrderIterator
{
	friend class COrderFactory;
private:
	///检查此对象是否满足条件
	///@param	pOrder		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(COrder *pOrder);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	COrder *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	COrder *m_pNext;

	///用于存储查询参数的对象
	CWriteableOrder m_compareObject;
	
	static CMemoryStack<COrderIteratorAllByExchIDInstruIDUserID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约号
	///@param	UserID	交易用户代码
	COrderIteratorAllByExchIDInstruIDUserID(COrderFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,ExchangeID,InstrumentID,UserID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约号
	///@param	UserID	交易用户代码
	static COrderIteratorAllByExchIDInstruIDUserID *alloc(COrderFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID);

	///构造方法
	COrderIteratorAllByExchIDInstruIDUserID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约号
	///@param	UserID	交易用户代码
	void init(COrderFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID);

	///析构方法，将负责释放所占用的空间
	virtual ~COrderIteratorAllByExchIDInstruIDUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的COrder，必须在startFindAllByExchIDInstruIDUserID以后，endFindAllByExchIDInstruIDUserID之前叫用
	///@return	下一个满足条件COrder，如果已经没有一个满足要求了，则返回NULL
	virtual COrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByExchIDInstruIDUserID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrder * pAllByExchIDInstruIDUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///COrderIteratorAll是一个对委托表使用All方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderIteratorAll: public COrderIterator
{
	friend class COrderFactory;
private:
	///检查此对象是否满足条件
	///@param	pOrder		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(COrder *pOrder);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	COrder *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	COrder *m_pNext;

	///用于存储查询参数的对象
	CWriteableOrder m_compareObject;
	
	static CMemoryStack<COrderIteratorAll> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	COrderIteratorAll(COrderFactory *pFactory
		)
	{
		init(pFactory);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	static COrderIteratorAll *alloc(COrderFactory *pFactory
		);

	///构造方法
	COrderIteratorAll(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	void init(COrderFactory *pFactory
		);

	///析构方法，将负责释放所占用的空间
	virtual ~COrderIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的COrder，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件COrder，如果已经没有一个满足要求了，则返回NULL
	virtual COrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAll 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrder * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CTradeIteratorByExchangeIDAndTradeID是一个对成交表使用ByExchangeIDAndTradeID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeIteratorByExchangeIDAndTradeID: public CTradeIterator
{
	friend class CTradeFactory;
private:
	///检查此对象是否满足条件
	///@param	pTrade		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CTrade *pTrade);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteableTrade m_compareObject;
	
	static CMemoryStack<CTradeIteratorByExchangeIDAndTradeID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	TradeID	成交编号
	CTradeIteratorByExchangeIDAndTradeID(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyTradeIDType& TradeID)
	{
		init(pFactory,ExchangeID,TradeID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	TradeID	成交编号
	static CTradeIteratorByExchangeIDAndTradeID *alloc(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyTradeIDType& TradeID);

	///构造方法
	CTradeIteratorByExchangeIDAndTradeID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	TradeID	成交编号
	void init(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyTradeIDType& TradeID);

	///析构方法，将负责释放所占用的空间
	virtual ~CTradeIteratorByExchangeIDAndTradeID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CTrade，必须在startFindByExchangeIDAndTradeID以后，endFindByExchangeIDAndTradeID之前叫用
	///@return	下一个满足条件CTrade，如果已经没有一个满足要求了，则返回NULL
	virtual CTrade *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pByExchangeIDAndTradeID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableTrade * pByExchangeIDAndTradeID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CTradeIteratorAllByExchIDInvIDUserID是一个对成交表使用AllByExchIDInvIDUserID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeIteratorAllByExchIDInvIDUserID: public CTradeIterator
{
	friend class CTradeFactory;
private:
	///检查此对象是否满足条件
	///@param	pTrade		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CTrade *pTrade);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CTrade *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CTrade *m_pNext;

	///用于存储查询参数的对象
	CWriteableTrade m_compareObject;
	
	static CMemoryStack<CTradeIteratorAllByExchIDInvIDUserID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	UserID	交易用户代码
	CTradeIteratorAllByExchIDInvIDUserID(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,ExchangeID,InvestorID,UserID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	UserID	交易用户代码
	static CTradeIteratorAllByExchIDInvIDUserID *alloc(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID);

	///构造方法
	CTradeIteratorAllByExchIDInvIDUserID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	UserID	交易用户代码
	void init(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID);

	///析构方法，将负责释放所占用的空间
	virtual ~CTradeIteratorAllByExchIDInvIDUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CTrade，必须在startFindAllByExchIDInvIDUserID以后，endFindAllByExchIDInvIDUserID之前叫用
	///@return	下一个满足条件CTrade，如果已经没有一个满足要求了，则返回NULL
	virtual CTrade *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByExchIDInvIDUserID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableTrade * pAllByExchIDInvIDUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CTradeIteratorAllByInvestorID是一个对成交表使用AllByInvestorID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeIteratorAllByInvestorID: public CTradeIterator
{
	friend class CTradeFactory;
private:
	///检查此对象是否满足条件
	///@param	pTrade		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CTrade *pTrade);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CTrade *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CTrade *m_pNext;

	///用于存储查询参数的对象
	CWriteableTrade m_compareObject;
	
	static CMemoryStack<CTradeIteratorAllByInvestorID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	投资者编号
	CTradeIteratorAllByInvestorID(CTradeFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,InvestorID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	投资者编号
	static CTradeIteratorAllByInvestorID *alloc(CTradeFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///构造方法
	CTradeIteratorAllByInvestorID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	投资者编号
	void init(CTradeFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///析构方法，将负责释放所占用的空间
	virtual ~CTradeIteratorAllByInvestorID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CTrade，必须在startFindAllByInvestorID以后，endFindAllByInvestorID之前叫用
	///@return	下一个满足条件CTrade，如果已经没有一个满足要求了，则返回NULL
	virtual CTrade *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByInvestorID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableTrade * pAllByInvestorID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CTradeIteratorAllByExchIDInstruIDUserID是一个对成交表使用AllByExchIDInstruIDUserID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeIteratorAllByExchIDInstruIDUserID: public CTradeIterator
{
	friend class CTradeFactory;
private:
	///检查此对象是否满足条件
	///@param	pTrade		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CTrade *pTrade);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CTrade *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CTrade *m_pNext;

	///用于存储查询参数的对象
	CWriteableTrade m_compareObject;
	
	static CMemoryStack<CTradeIteratorAllByExchIDInstruIDUserID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约号
	///@param	UserID	交易用户代码
	CTradeIteratorAllByExchIDInstruIDUserID(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,ExchangeID,InstrumentID,UserID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约号
	///@param	UserID	交易用户代码
	static CTradeIteratorAllByExchIDInstruIDUserID *alloc(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID);

	///构造方法
	CTradeIteratorAllByExchIDInstruIDUserID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约号
	///@param	UserID	交易用户代码
	void init(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID);

	///析构方法，将负责释放所占用的空间
	virtual ~CTradeIteratorAllByExchIDInstruIDUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CTrade，必须在startFindAllByExchIDInstruIDUserID以后，endFindAllByExchIDInstruIDUserID之前叫用
	///@return	下一个满足条件CTrade，如果已经没有一个满足要求了，则返回NULL
	virtual CTrade *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByExchIDInstruIDUserID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableTrade * pAllByExchIDInstruIDUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CTradeIteratorAll是一个对成交表使用All方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeIteratorAll: public CTradeIterator
{
	friend class CTradeFactory;
private:
	///检查此对象是否满足条件
	///@param	pTrade		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CTrade *pTrade);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CTrade *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CTrade *m_pNext;

	///用于存储查询参数的对象
	CWriteableTrade m_compareObject;
	
	static CMemoryStack<CTradeIteratorAll> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	CTradeIteratorAll(CTradeFactory *pFactory
		)
	{
		init(pFactory);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	static CTradeIteratorAll *alloc(CTradeFactory *pFactory
		);

	///构造方法
	CTradeIteratorAll(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	void init(CTradeFactory *pFactory
		);

	///析构方法，将负责释放所占用的空间
	virtual ~CTradeIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CTrade，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CTrade，如果已经没有一个满足要求了，则返回NULL
	virtual CTrade *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAll 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableTrade * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderIteratorByAPIID是一个对预委托表使用ByAPIID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderIteratorByAPIID: public CPreOrderIterator
{
	friend class CPreOrderFactory;
private:
	///检查此对象是否满足条件
	///@param	pPreOrder		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CPreOrder *pPreOrder);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteablePreOrder m_compareObject;
	
	static CMemoryStack<CPreOrderIteratorByAPIID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	APIID	通道号
	CPreOrderIteratorByAPIID(CPreOrderFactory *pFactory
		,const CReadOnlyNumberType& APIID)
	{
		init(pFactory,APIID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	APIID	通道号
	static CPreOrderIteratorByAPIID *alloc(CPreOrderFactory *pFactory
		,const CReadOnlyNumberType& APIID);

	///构造方法
	CPreOrderIteratorByAPIID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	APIID	通道号
	void init(CPreOrderFactory *pFactory
		,const CReadOnlyNumberType& APIID);

	///析构方法，将负责释放所占用的空间
	virtual ~CPreOrderIteratorByAPIID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CPreOrder，必须在startFindByAPIID以后，endFindByAPIID之前叫用
	///@return	下一个满足条件CPreOrder，如果已经没有一个满足要求了，则返回NULL
	virtual CPreOrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pByAPIID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteablePreOrder * pByAPIID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIteratorAllByExIDAndInstrumentID是一个对持仓表使用AllByExIDAndInstrumentID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIteratorAllByExIDAndInstrumentID: public CInvestorPositionIterator
{
	friend class CInvestorPositionFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorPosition		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorPosition *pInvestorPosition);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorPosition m_compareObject;
	
	static CMemoryStack<CInvestorPositionIteratorAllByExIDAndInstrumentID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约编号
	CInvestorPositionIteratorAllByExIDAndInstrumentID(CInvestorPositionFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID)
	{
		init(pFactory,ExchangeID,InstrumentID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约编号
	static CInvestorPositionIteratorAllByExIDAndInstrumentID *alloc(CInvestorPositionFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID);

	///构造方法
	CInvestorPositionIteratorAllByExIDAndInstrumentID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约编号
	void init(CInvestorPositionFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorPositionIteratorAllByExIDAndInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorPosition，必须在startFindAllByExIDAndInstrumentID以后，endFindAllByExIDAndInstrumentID之前叫用
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByExIDAndInstrumentID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorPosition * pAllByExIDAndInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIteratorByInvestorID是一个对持仓表使用ByInvestorID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIteratorByInvestorID: public CInvestorPositionIterator
{
	friend class CInvestorPositionFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorPosition		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorPosition *pInvestorPosition);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorPosition m_compareObject;
	
	static CMemoryStack<CInvestorPositionIteratorByInvestorID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	投资者号
	CInvestorPositionIteratorByInvestorID(CInvestorPositionFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,InvestorID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	投资者号
	static CInvestorPositionIteratorByInvestorID *alloc(CInvestorPositionFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///构造方法
	CInvestorPositionIteratorByInvestorID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	投资者号
	void init(CInvestorPositionFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorPositionIteratorByInvestorID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorPosition，必须在startFindByInvestorID以后，endFindByInvestorID之前叫用
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pByInvestorID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorPosition * pByInvestorID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIteratorAllByBrokerID是一个对持仓表使用AllByBrokerID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIteratorAllByBrokerID: public CInvestorPositionIterator
{
	friend class CInvestorPositionFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorPosition		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorPosition *pInvestorPosition);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInvestorPosition *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInvestorPosition *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorPosition m_compareObject;
	
	static CMemoryStack<CInvestorPositionIteratorAllByBrokerID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	CInvestorPositionIteratorAllByBrokerID(CInvestorPositionFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID)
	{
		init(pFactory,BrokerID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	static CInvestorPositionIteratorAllByBrokerID *alloc(CInvestorPositionFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///构造方法
	CInvestorPositionIteratorAllByBrokerID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	void init(CInvestorPositionFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorPositionIteratorAllByBrokerID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorPosition，必须在startFindAllByBrokerID以后，endFindAllByBrokerID之前叫用
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByBrokerID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorPosition * pAllByBrokerID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIteratorAllByInstrumentID是一个对持仓表使用AllByInstrumentID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIteratorAllByInstrumentID: public CInvestorPositionIterator
{
	friend class CInvestorPositionFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorPosition		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorPosition *pInvestorPosition);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInvestorPosition *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInvestorPosition *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorPosition m_compareObject;
	
	static CMemoryStack<CInvestorPositionIteratorAllByInstrumentID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	InstrumentID	合约代码
	CInvestorPositionIteratorAllByInstrumentID(CInvestorPositionFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID)
	{
		init(pFactory,InstrumentID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	InstrumentID	合约代码
	static CInvestorPositionIteratorAllByInstrumentID *alloc(CInvestorPositionFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///构造方法
	CInvestorPositionIteratorAllByInstrumentID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	InstrumentID	合约代码
	void init(CInvestorPositionFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorPositionIteratorAllByInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorPosition，必须在startFindAllByInstrumentID以后，endFindAllByInstrumentID之前叫用
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByInstrumentID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorPosition * pAllByInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIteratorAllByExchangeID是一个对持仓表使用AllByExchangeID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIteratorAllByExchangeID: public CInvestorPositionIterator
{
	friend class CInvestorPositionFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorPosition		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorPosition *pInvestorPosition);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInvestorPosition *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInvestorPosition *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorPosition m_compareObject;
	
	static CMemoryStack<CInvestorPositionIteratorAllByExchangeID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所编号
	CInvestorPositionIteratorAllByExchangeID(CInvestorPositionFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID)
	{
		init(pFactory,ExchangeID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所编号
	static CInvestorPositionIteratorAllByExchangeID *alloc(CInvestorPositionFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID);

	///构造方法
	CInvestorPositionIteratorAllByExchangeID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所编号
	void init(CInvestorPositionFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorPositionIteratorAllByExchangeID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorPosition，必须在startFindAllByExchangeID以后，endFindAllByExchangeID之前叫用
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByExchangeID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorPosition * pAllByExchangeID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIteratorAllByInvestorIDAndInstrumentID是一个对持仓表使用AllByInvestorIDAndInstrumentID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIteratorAllByInvestorIDAndInstrumentID: public CInvestorPositionIterator
{
	friend class CInvestorPositionFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorPosition		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorPosition *pInvestorPosition);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInvestorPosition *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInvestorPosition *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorPosition m_compareObject;
	
	static CMemoryStack<CInvestorPositionIteratorAllByInvestorIDAndInstrumentID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	客户号
	///@param	InstrumentID	合约代码
	CInvestorPositionIteratorAllByInvestorIDAndInstrumentID(CInvestorPositionFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyInstrumentIDType& InstrumentID)
	{
		init(pFactory,InvestorID,InstrumentID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	客户号
	///@param	InstrumentID	合约代码
	static CInvestorPositionIteratorAllByInvestorIDAndInstrumentID *alloc(CInvestorPositionFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyInstrumentIDType& InstrumentID);

	///构造方法
	CInvestorPositionIteratorAllByInvestorIDAndInstrumentID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	客户号
	///@param	InstrumentID	合约代码
	void init(CInvestorPositionFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyInstrumentIDType& InstrumentID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorPositionIteratorAllByInvestorIDAndInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorPosition，必须在startFindAllByInvestorIDAndInstrumentID以后，endFindAllByInvestorIDAndInstrumentID之前叫用
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByInvestorIDAndInstrumentID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorPosition * pAllByInvestorIDAndInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIteratorAll是一个对持仓表使用All方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIteratorAll: public CInvestorPositionIterator
{
	friend class CInvestorPositionFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorPosition		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorPosition *pInvestorPosition);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInvestorPosition *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInvestorPosition *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorPosition m_compareObject;
	
	static CMemoryStack<CInvestorPositionIteratorAll> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	CInvestorPositionIteratorAll(CInvestorPositionFactory *pFactory
		)
	{
		init(pFactory);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	static CInvestorPositionIteratorAll *alloc(CInvestorPositionFactory *pFactory
		);

	///构造方法
	CInvestorPositionIteratorAll(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	void init(CInvestorPositionFactory *pFactory
		);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorPositionIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorPosition，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAll 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorPosition * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountIteratorAllByInvestorID是一个对账户实时资金表使用AllByInvestorID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountIteratorAllByInvestorID: public CInvestorAccountIterator
{
	friend class CInvestorAccountFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorAccount		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorAccount *pInvestorAccount);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInvestorAccount *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInvestorAccount *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorAccount m_compareObject;
	
	static CMemoryStack<CInvestorAccountIteratorAllByInvestorID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	投资者编号
	CInvestorAccountIteratorAllByInvestorID(CInvestorAccountFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,InvestorID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	投资者编号
	static CInvestorAccountIteratorAllByInvestorID *alloc(CInvestorAccountFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///构造方法
	CInvestorAccountIteratorAllByInvestorID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	投资者编号
	void init(CInvestorAccountFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorAccountIteratorAllByInvestorID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorAccount，必须在startFindAllByInvestorID以后，endFindAllByInvestorID之前叫用
	///@return	下一个满足条件CInvestorAccount，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccount *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByInvestorID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccount * pAllByInvestorID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorAccountIteratorAllByBrokerID是一个对账户实时资金表使用AllByBrokerID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountIteratorAllByBrokerID: public CInvestorAccountIterator
{
	friend class CInvestorAccountFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorAccount		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorAccount *pInvestorAccount);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInvestorAccount *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInvestorAccount *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorAccount m_compareObject;
	
	static CMemoryStack<CInvestorAccountIteratorAllByBrokerID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	CInvestorAccountIteratorAllByBrokerID(CInvestorAccountFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID)
	{
		init(pFactory,BrokerID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	static CInvestorAccountIteratorAllByBrokerID *alloc(CInvestorAccountFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///构造方法
	CInvestorAccountIteratorAllByBrokerID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	void init(CInvestorAccountFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorAccountIteratorAllByBrokerID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorAccount，必须在startFindAllByBrokerID以后，endFindAllByBrokerID之前叫用
	///@return	下一个满足条件CInvestorAccount，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccount *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByBrokerID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccount * pAllByBrokerID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorAccountIteratorAll是一个对账户实时资金表使用All方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountIteratorAll: public CInvestorAccountIterator
{
	friend class CInvestorAccountFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorAccount		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorAccount *pInvestorAccount);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInvestorAccount *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInvestorAccount *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorAccount m_compareObject;
	
	static CMemoryStack<CInvestorAccountIteratorAll> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	CInvestorAccountIteratorAll(CInvestorAccountFactory *pFactory
		)
	{
		init(pFactory);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	static CInvestorAccountIteratorAll *alloc(CInvestorAccountFactory *pFactory
		);

	///构造方法
	CInvestorAccountIteratorAll(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	void init(CInvestorAccountFactory *pFactory
		);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorAccountIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorAccount，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CInvestorAccount，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccount *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAll 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccount * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CExchangeIteratorStartByExchangeID是一个对交易所表使用StartByExchangeID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeIteratorStartByExchangeID: public CExchangeIterator
{
	friend class CExchangeFactory;
private:
	///检查此对象是否满足条件
	///@param	pExchange		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CExchange *pExchange);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteableExchange m_compareObject;
	
	static CMemoryStack<CExchangeIteratorStartByExchangeID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	CExchangeIteratorStartByExchangeID(CExchangeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID)
	{
		init(pFactory,ExchangeID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	static CExchangeIteratorStartByExchangeID *alloc(CExchangeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID);

	///构造方法
	CExchangeIteratorStartByExchangeID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	void init(CExchangeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID);

	///析构方法，将负责释放所占用的空间
	virtual ~CExchangeIteratorStartByExchangeID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CExchange，必须在startFindStartByExchangeID以后，endFindStartByExchangeID之前叫用
	///@return	下一个满足条件CExchange，如果已经没有一个满足要求了，则返回NULL
	virtual CExchange *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pStartByExchangeID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableExchange * pStartByExchangeID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CExchangeIteratorAll是一个对交易所表使用All方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeIteratorAll: public CExchangeIterator
{
	friend class CExchangeFactory;
private:
	///检查此对象是否满足条件
	///@param	pExchange		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CExchange *pExchange);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CExchange *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CExchange *m_pNext;

	///用于存储查询参数的对象
	CWriteableExchange m_compareObject;
	
	static CMemoryStack<CExchangeIteratorAll> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	CExchangeIteratorAll(CExchangeFactory *pFactory
		)
	{
		init(pFactory);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	static CExchangeIteratorAll *alloc(CExchangeFactory *pFactory
		);

	///构造方法
	CExchangeIteratorAll(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	void init(CExchangeFactory *pFactory
		);

	///析构方法，将负责释放所占用的空间
	virtual ~CExchangeIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CExchange，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CExchange，如果已经没有一个满足要求了，则返回NULL
	virtual CExchange *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAll 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableExchange * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInstrumentIteratorAllByInstrumentID是一个对期货合约表使用AllByInstrumentID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentIteratorAllByInstrumentID: public CInstrumentIterator
{
	friend class CInstrumentFactory;
private:
	///检查此对象是否满足条件
	///@param	pInstrument		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInstrument *pInstrument);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteableInstrument m_compareObject;
	
	static CMemoryStack<CInstrumentIteratorAllByInstrumentID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	InstrumentID	合约代码
	CInstrumentIteratorAllByInstrumentID(CInstrumentFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID)
	{
		init(pFactory,InstrumentID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	InstrumentID	合约代码
	static CInstrumentIteratorAllByInstrumentID *alloc(CInstrumentFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///构造方法
	CInstrumentIteratorAllByInstrumentID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	InstrumentID	合约代码
	void init(CInstrumentFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInstrumentIteratorAllByInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInstrument，必须在startFindAllByInstrumentID以后，endFindAllByInstrumentID之前叫用
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrument *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByInstrumentID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrument * pAllByInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInstrumentIteratorAllByExchangeID是一个对期货合约表使用AllByExchangeID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentIteratorAllByExchangeID: public CInstrumentIterator
{
	friend class CInstrumentFactory;
private:
	///检查此对象是否满足条件
	///@param	pInstrument		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInstrument *pInstrument);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInstrument *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInstrument *m_pNext;

	///用于存储查询参数的对象
	CWriteableInstrument m_compareObject;
	
	static CMemoryStack<CInstrumentIteratorAllByExchangeID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所编号
	CInstrumentIteratorAllByExchangeID(CInstrumentFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID)
	{
		init(pFactory,ExchangeID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所编号
	static CInstrumentIteratorAllByExchangeID *alloc(CInstrumentFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID);

	///构造方法
	CInstrumentIteratorAllByExchangeID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所编号
	void init(CInstrumentFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInstrumentIteratorAllByExchangeID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInstrument，必须在startFindAllByExchangeID以后，endFindAllByExchangeID之前叫用
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrument *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByExchangeID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrument * pAllByExchangeID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInstrumentIteratorAllByProductID是一个对期货合约表使用AllByProductID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentIteratorAllByProductID: public CInstrumentIterator
{
	friend class CInstrumentFactory;
private:
	///检查此对象是否满足条件
	///@param	pInstrument		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInstrument *pInstrument);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInstrument *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInstrument *m_pNext;

	///用于存储查询参数的对象
	CWriteableInstrument m_compareObject;
	
	static CMemoryStack<CInstrumentIteratorAllByProductID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	ProductID	产品代码
	CInstrumentIteratorAllByProductID(CInstrumentFactory *pFactory
		,const CReadOnlyProductIDType& ProductID)
	{
		init(pFactory,ProductID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	ProductID	产品代码
	static CInstrumentIteratorAllByProductID *alloc(CInstrumentFactory *pFactory
		,const CReadOnlyProductIDType& ProductID);

	///构造方法
	CInstrumentIteratorAllByProductID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	ProductID	产品代码
	void init(CInstrumentFactory *pFactory
		,const CReadOnlyProductIDType& ProductID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInstrumentIteratorAllByProductID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInstrument，必须在startFindAllByProductID以后，endFindAllByProductID之前叫用
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrument *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByProductID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrument * pAllByProductID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInstrumentIteratorAll是一个对期货合约表使用All方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentIteratorAll: public CInstrumentIterator
{
	friend class CInstrumentFactory;
private:
	///检查此对象是否满足条件
	///@param	pInstrument		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInstrument *pInstrument);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInstrument *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInstrument *m_pNext;

	///用于存储查询参数的对象
	CWriteableInstrument m_compareObject;
	
	static CMemoryStack<CInstrumentIteratorAll> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	CInstrumentIteratorAll(CInstrumentFactory *pFactory
		)
	{
		init(pFactory);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	static CInstrumentIteratorAll *alloc(CInstrumentFactory *pFactory
		);

	///构造方法
	CInstrumentIteratorAll(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	void init(CInstrumentFactory *pFactory
		);

	///析构方法，将负责释放所占用的空间
	virtual ~CInstrumentIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInstrument，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrument *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAll 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrument * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID是一个对期货组合合约明细表使用AllByExchangeIDAndArbiInstrumentID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID: public CCmbInstrumentDetailIterator
{
	friend class CCmbInstrumentDetailFactory;
private:
	///检查此对象是否满足条件
	///@param	pCmbInstrumentDetail		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CCmbInstrumentDetail *pCmbInstrumentDetail);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteableCmbInstrumentDetail m_compareObject;
	
	static CMemoryStack<CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所编号
	///@param	ArbiInstrumentID	组合合约编号
	CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID(CCmbInstrumentDetailFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& ArbiInstrumentID)
	{
		init(pFactory,ExchangeID,ArbiInstrumentID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所编号
	///@param	ArbiInstrumentID	组合合约编号
	static CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID *alloc(CCmbInstrumentDetailFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& ArbiInstrumentID);

	///构造方法
	CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所编号
	///@param	ArbiInstrumentID	组合合约编号
	void init(CCmbInstrumentDetailFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& ArbiInstrumentID);

	///析构方法，将负责释放所占用的空间
	virtual ~CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CCmbInstrumentDetail，必须在startFindAllByExchangeIDAndArbiInstrumentID以后，endFindAllByExchangeIDAndArbiInstrumentID之前叫用
	///@return	下一个满足条件CCmbInstrumentDetail，如果已经没有一个满足要求了，则返回NULL
	virtual CCmbInstrumentDetail *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByExchangeIDAndArbiInstrumentID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableCmbInstrumentDetail * pAllByExchangeIDAndArbiInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID是一个对期货组合合约明细表使用AllByExchangeIDAndSingleInstrumentID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID: public CCmbInstrumentDetailIterator
{
	friend class CCmbInstrumentDetailFactory;
private:
	///检查此对象是否满足条件
	///@param	pCmbInstrumentDetail		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CCmbInstrumentDetail *pCmbInstrumentDetail);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteableCmbInstrumentDetail m_compareObject;
	
	static CMemoryStack<CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所编号
	///@param	SingleInstrumentID	单腿合约编号
	CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID(CCmbInstrumentDetailFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& SingleInstrumentID)
	{
		init(pFactory,ExchangeID,SingleInstrumentID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所编号
	///@param	SingleInstrumentID	单腿合约编号
	static CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID *alloc(CCmbInstrumentDetailFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& SingleInstrumentID);

	///构造方法
	CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所编号
	///@param	SingleInstrumentID	单腿合约编号
	void init(CCmbInstrumentDetailFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& SingleInstrumentID);

	///析构方法，将负责释放所占用的空间
	virtual ~CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CCmbInstrumentDetail，必须在startFindAllByExchangeIDAndSingleInstrumentID以后，endFindAllByExchangeIDAndSingleInstrumentID之前叫用
	///@return	下一个满足条件CCmbInstrumentDetail，如果已经没有一个满足要求了，则返回NULL
	virtual CCmbInstrumentDetail *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByExchangeIDAndSingleInstrumentID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableCmbInstrumentDetail * pAllByExchangeIDAndSingleInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDIteratorByBrokerIDInvestorID是一个对交易所客户编码表使用ByBrokerIDInvestorID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDIteratorByBrokerIDInvestorID: public CClientTradingIDIterator
{
	friend class CClientTradingIDFactory;
private:
	///检查此对象是否满足条件
	///@param	pClientTradingID		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CClientTradingID *pClientTradingID);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteableClientTradingID m_compareObject;
	
	static CMemoryStack<CClientTradingIDIteratorByBrokerIDInvestorID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪商编号
	///@param	InvestorID	客户编码
	CClientTradingIDIteratorByBrokerIDInvestorID(CClientTradingIDFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,BrokerID,InvestorID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪商编号
	///@param	InvestorID	客户编码
	static CClientTradingIDIteratorByBrokerIDInvestorID *alloc(CClientTradingIDFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyInvestorIDType& InvestorID);

	///构造方法
	CClientTradingIDIteratorByBrokerIDInvestorID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪商编号
	///@param	InvestorID	客户编码
	void init(CClientTradingIDFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyInvestorIDType& InvestorID);

	///析构方法，将负责释放所占用的空间
	virtual ~CClientTradingIDIteratorByBrokerIDInvestorID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CClientTradingID，必须在startFindByBrokerIDInvestorID以后，endFindByBrokerIDInvestorID之前叫用
	///@return	下一个满足条件CClientTradingID，如果已经没有一个满足要求了，则返回NULL
	virtual CClientTradingID *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pByBrokerIDInvestorID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableClientTradingID * pByBrokerIDInvestorID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CClientTradingIDIteratorAllByBrokerID是一个对交易所客户编码表使用AllByBrokerID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDIteratorAllByBrokerID: public CClientTradingIDIterator
{
	friend class CClientTradingIDFactory;
private:
	///检查此对象是否满足条件
	///@param	pClientTradingID		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CClientTradingID *pClientTradingID);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CClientTradingID *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CClientTradingID *m_pNext;

	///用于存储查询参数的对象
	CWriteableClientTradingID m_compareObject;
	
	static CMemoryStack<CClientTradingIDIteratorAllByBrokerID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	CClientTradingIDIteratorAllByBrokerID(CClientTradingIDFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID)
	{
		init(pFactory,BrokerID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	static CClientTradingIDIteratorAllByBrokerID *alloc(CClientTradingIDFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///构造方法
	CClientTradingIDIteratorAllByBrokerID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	void init(CClientTradingIDFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///析构方法，将负责释放所占用的空间
	virtual ~CClientTradingIDIteratorAllByBrokerID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CClientTradingID，必须在startFindAllByBrokerID以后，endFindAllByBrokerID之前叫用
	///@return	下一个满足条件CClientTradingID，如果已经没有一个满足要求了，则返回NULL
	virtual CClientTradingID *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByBrokerID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableClientTradingID * pAllByBrokerID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CClientTradingIDIteratorAll是一个对交易所客户编码表使用All方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDIteratorAll: public CClientTradingIDIterator
{
	friend class CClientTradingIDFactory;
private:
	///检查此对象是否满足条件
	///@param	pClientTradingID		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CClientTradingID *pClientTradingID);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CClientTradingID *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CClientTradingID *m_pNext;

	///用于存储查询参数的对象
	CWriteableClientTradingID m_compareObject;
	
	static CMemoryStack<CClientTradingIDIteratorAll> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	CClientTradingIDIteratorAll(CClientTradingIDFactory *pFactory
		)
	{
		init(pFactory);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	static CClientTradingIDIteratorAll *alloc(CClientTradingIDFactory *pFactory
		);

	///构造方法
	CClientTradingIDIteratorAll(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	void init(CClientTradingIDFactory *pFactory
		);

	///析构方法，将负责释放所占用的空间
	virtual ~CClientTradingIDIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CClientTradingID，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CClientTradingID，如果已经没有一个满足要求了，则返回NULL
	virtual CClientTradingID *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAll 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableClientTradingID * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorIteratorByInvestorID是一个对投资者信息表使用ByInvestorID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorIteratorByInvestorID: public CInvestorIterator
{
	friend class CInvestorFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestor		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestor *pInvestor);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestor m_compareObject;
	
	static CMemoryStack<CInvestorIteratorByInvestorID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	投资者编号
	CInvestorIteratorByInvestorID(CInvestorFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,InvestorID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	投资者编号
	static CInvestorIteratorByInvestorID *alloc(CInvestorFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///构造方法
	CInvestorIteratorByInvestorID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	InvestorID	投资者编号
	void init(CInvestorFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorIteratorByInvestorID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestor，必须在startFindByInvestorID以后，endFindByInvestorID之前叫用
	///@return	下一个满足条件CInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestor *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pByInvestorID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestor * pByInvestorID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginIteratorByBrkIDExIDIstIDVstID是一个对客户期货保证金率表使用ByBrkIDExIDIstIDVstID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginIteratorByBrkIDExIDIstIDVstID: public CInvestorMarginIterator
{
	friend class CInvestorMarginFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorMargin		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorMargin *pInvestorMargin);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorMargin m_compareObject;
	
	static CMemoryStack<CInvestorMarginIteratorByBrkIDExIDIstIDVstID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约代码
	///@param	InvestorID	投资者编码
	CInvestorMarginIteratorByBrkIDExIDIstIDVstID(CInvestorMarginFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,BrokerID,ExchangeID,InstrumentID,InvestorID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约代码
	///@param	InvestorID	投资者编码
	static CInvestorMarginIteratorByBrkIDExIDIstIDVstID *alloc(CInvestorMarginFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyInvestorIDType& InvestorID);

	///构造方法
	CInvestorMarginIteratorByBrkIDExIDIstIDVstID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约代码
	///@param	InvestorID	投资者编码
	void init(CInvestorMarginFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyInvestorIDType& InvestorID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorMarginIteratorByBrkIDExIDIstIDVstID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorMargin，必须在startFindByBrkIDExIDIstIDVstID以后，endFindByBrkIDExIDIstIDVstID之前叫用
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorMargin *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pByBrkIDExIDIstIDVstID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorMargin * pByBrkIDExIDIstIDVstID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorMarginIteratorByInstrumentID是一个对客户期货保证金率表使用ByInstrumentID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginIteratorByInstrumentID: public CInvestorMarginIterator
{
	friend class CInvestorMarginFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorMargin		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorMargin *pInvestorMargin);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInvestorMargin *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInvestorMargin *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorMargin m_compareObject;
	
	static CMemoryStack<CInvestorMarginIteratorByInstrumentID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	InstrumentID	合约代码
	CInvestorMarginIteratorByInstrumentID(CInvestorMarginFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID)
	{
		init(pFactory,InstrumentID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	InstrumentID	合约代码
	static CInvestorMarginIteratorByInstrumentID *alloc(CInvestorMarginFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///构造方法
	CInvestorMarginIteratorByInstrumentID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	InstrumentID	合约代码
	void init(CInvestorMarginFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorMarginIteratorByInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorMargin，必须在startFindByInstrumentID以后，endFindByInstrumentID之前叫用
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorMargin *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pByInstrumentID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorMargin * pByInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorMarginIteratorByBrokerID是一个对客户期货保证金率表使用ByBrokerID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginIteratorByBrokerID: public CInvestorMarginIterator
{
	friend class CInvestorMarginFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorMargin		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorMargin *pInvestorMargin);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInvestorMargin *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInvestorMargin *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorMargin m_compareObject;
	
	static CMemoryStack<CInvestorMarginIteratorByBrokerID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	合约代码
	CInvestorMarginIteratorByBrokerID(CInvestorMarginFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID)
	{
		init(pFactory,BrokerID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	合约代码
	static CInvestorMarginIteratorByBrokerID *alloc(CInvestorMarginFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///构造方法
	CInvestorMarginIteratorByBrokerID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	合约代码
	void init(CInvestorMarginFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorMarginIteratorByBrokerID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorMargin，必须在startFindByBrokerID以后，endFindByBrokerID之前叫用
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorMargin *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pByBrokerID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorMargin * pByBrokerID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorMarginIteratorAll是一个对客户期货保证金率表使用All方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginIteratorAll: public CInvestorMarginIterator
{
	friend class CInvestorMarginFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorMargin		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorMargin *pInvestorMargin);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInvestorMargin *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInvestorMargin *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorMargin m_compareObject;
	
	static CMemoryStack<CInvestorMarginIteratorAll> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	CInvestorMarginIteratorAll(CInvestorMarginFactory *pFactory
		)
	{
		init(pFactory);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	static CInvestorMarginIteratorAll *alloc(CInvestorMarginFactory *pFactory
		);

	///构造方法
	CInvestorMarginIteratorAll(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	void init(CInvestorMarginFactory *pFactory
		);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorMarginIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorMargin，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorMargin *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAll 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorMargin * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeIteratorByInstrumentID是一个对客户手续费率表使用ByInstrumentID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeIteratorByInstrumentID: public CInvestorFeeIterator
{
	friend class CInvestorFeeFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorFee		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorFee *pInvestorFee);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorFee m_compareObject;
	
	static CMemoryStack<CInvestorFeeIteratorByInstrumentID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	InstrumentID	合约编号
	CInvestorFeeIteratorByInstrumentID(CInvestorFeeFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID)
	{
		init(pFactory,InstrumentID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	InstrumentID	合约编号
	static CInvestorFeeIteratorByInstrumentID *alloc(CInvestorFeeFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///构造方法
	CInvestorFeeIteratorByInstrumentID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	InstrumentID	合约编号
	void init(CInvestorFeeFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorFeeIteratorByInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorFee，必须在startFindByInstrumentID以后，endFindByInstrumentID之前叫用
	///@return	下一个满足条件CInvestorFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorFee *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pByInstrumentID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorFee * pByInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorFeeIteratorByBrokerID是一个对客户手续费率表使用ByBrokerID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeIteratorByBrokerID: public CInvestorFeeIterator
{
	friend class CInvestorFeeFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorFee		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorFee *pInvestorFee);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInvestorFee *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInvestorFee *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorFee m_compareObject;
	
	static CMemoryStack<CInvestorFeeIteratorByBrokerID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	合约编号
	CInvestorFeeIteratorByBrokerID(CInvestorFeeFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID)
	{
		init(pFactory,BrokerID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	合约编号
	static CInvestorFeeIteratorByBrokerID *alloc(CInvestorFeeFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///构造方法
	CInvestorFeeIteratorByBrokerID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	合约编号
	void init(CInvestorFeeFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorFeeIteratorByBrokerID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorFee，必须在startFindByBrokerID以后，endFindByBrokerID之前叫用
	///@return	下一个满足条件CInvestorFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorFee *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pByBrokerID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorFee * pByBrokerID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorFeeIteratorAll是一个对客户手续费率表使用All方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeIteratorAll: public CInvestorFeeIterator
{
	friend class CInvestorFeeFactory;
private:
	///检查此对象是否满足条件
	///@param	pInvestorFee		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CInvestorFee *pInvestorFee);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CInvestorFee *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CInvestorFee *m_pNext;

	///用于存储查询参数的对象
	CWriteableInvestorFee m_compareObject;
	
	static CMemoryStack<CInvestorFeeIteratorAll> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	CInvestorFeeIteratorAll(CInvestorFeeFactory *pFactory
		)
	{
		init(pFactory);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	static CInvestorFeeIteratorAll *alloc(CInvestorFeeFactory *pFactory
		);

	///构造方法
	CInvestorFeeIteratorAll(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	void init(CInvestorFeeFactory *pFactory
		);

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorFeeIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CInvestorFee，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CInvestorFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorFee *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAll 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorFee * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserIteratorStartByUserID是一个对用户表使用StartByUserID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIteratorStartByUserID: public CUserIterator
{
	friend class CUserFactory;
private:
	///检查此对象是否满足条件
	///@param	pUser		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CUser *pUser);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteableUser m_compareObject;
	
	static CMemoryStack<CUserIteratorStartByUserID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	UserID	用户编号
	CUserIteratorStartByUserID(CUserFactory *pFactory
		,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,UserID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	UserID	用户编号
	static CUserIteratorStartByUserID *alloc(CUserFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///构造方法
	CUserIteratorStartByUserID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	UserID	用户编号
	void init(CUserFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///析构方法，将负责释放所占用的空间
	virtual ~CUserIteratorStartByUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CUser，必须在startFindStartByUserID以后，endFindStartByUserID之前叫用
	///@return	下一个满足条件CUser，如果已经没有一个满足要求了，则返回NULL
	virtual CUser *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pStartByUserID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUser * pStartByUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorIteratorByBrokerIDInvestorID是一个对用户投资者关系表使用ByBrokerIDInvestorID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorIteratorByBrokerIDInvestorID: public CUserInvestorIterator
{
	friend class CUserInvestorFactory;
private:
	///检查此对象是否满足条件
	///@param	pUserInvestor		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CUserInvestor *pUserInvestor);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteableUserInvestor m_compareObject;
	
	static CMemoryStack<CUserInvestorIteratorByBrokerIDInvestorID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	///@param	InvestorID	投资者编号
	CUserInvestorIteratorByBrokerIDInvestorID(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,BrokerID,InvestorID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	///@param	InvestorID	投资者编号
	static CUserInvestorIteratorByBrokerIDInvestorID *alloc(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyInvestorIDType& InvestorID);

	///构造方法
	CUserInvestorIteratorByBrokerIDInvestorID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	///@param	InvestorID	投资者编号
	void init(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyInvestorIDType& InvestorID);

	///析构方法，将负责释放所占用的空间
	virtual ~CUserInvestorIteratorByBrokerIDInvestorID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CUserInvestor，必须在startFindByBrokerIDInvestorID以后，endFindByBrokerIDInvestorID之前叫用
	///@return	下一个满足条件CUserInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CUserInvestor *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pByBrokerIDInvestorID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserInvestor * pByBrokerIDInvestorID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CUserInvestorIteratorAllByUserID是一个对用户投资者关系表使用AllByUserID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorIteratorAllByUserID: public CUserInvestorIterator
{
	friend class CUserInvestorFactory;
private:
	///检查此对象是否满足条件
	///@param	pUserInvestor		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CUserInvestor *pUserInvestor);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CUserInvestor *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CUserInvestor *m_pNext;

	///用于存储查询参数的对象
	CWriteableUserInvestor m_compareObject;
	
	static CMemoryStack<CUserInvestorIteratorAllByUserID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	UserID	会员代码
	CUserInvestorIteratorAllByUserID(CUserInvestorFactory *pFactory
		,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,UserID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	UserID	会员代码
	static CUserInvestorIteratorAllByUserID *alloc(CUserInvestorFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///构造方法
	CUserInvestorIteratorAllByUserID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	UserID	会员代码
	void init(CUserInvestorFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///析构方法，将负责释放所占用的空间
	virtual ~CUserInvestorIteratorAllByUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CUserInvestor，必须在startFindAllByUserID以后，endFindAllByUserID之前叫用
	///@return	下一个满足条件CUserInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CUserInvestor *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByUserID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserInvestor * pAllByUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CUserInvestorIteratorAllByBrokerIDUserID是一个对用户投资者关系表使用AllByBrokerIDUserID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorIteratorAllByBrokerIDUserID: public CUserInvestorIterator
{
	friend class CUserInvestorFactory;
private:
	///检查此对象是否满足条件
	///@param	pUserInvestor		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CUserInvestor *pUserInvestor);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CUserInvestor *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CUserInvestor *m_pNext;

	///用于存储查询参数的对象
	CWriteableUserInvestor m_compareObject;
	
	static CMemoryStack<CUserInvestorIteratorAllByBrokerIDUserID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	///@param	UserID	会员代码
	CUserInvestorIteratorAllByBrokerIDUserID(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,BrokerID,UserID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	///@param	UserID	会员代码
	static CUserInvestorIteratorAllByBrokerIDUserID *alloc(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyUserIDType& UserID);

	///构造方法
	CUserInvestorIteratorAllByBrokerIDUserID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	///@param	UserID	会员代码
	void init(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyUserIDType& UserID);

	///析构方法，将负责释放所占用的空间
	virtual ~CUserInvestorIteratorAllByBrokerIDUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CUserInvestor，必须在startFindAllByBrokerIDUserID以后，endFindAllByBrokerIDUserID之前叫用
	///@return	下一个满足条件CUserInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CUserInvestor *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByBrokerIDUserID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserInvestor * pAllByBrokerIDUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CUserInvestorIteratorAllByBrokerID是一个对用户投资者关系表使用AllByBrokerID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorIteratorAllByBrokerID: public CUserInvestorIterator
{
	friend class CUserInvestorFactory;
private:
	///检查此对象是否满足条件
	///@param	pUserInvestor		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CUserInvestor *pUserInvestor);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CUserInvestor *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CUserInvestor *m_pNext;

	///用于存储查询参数的对象
	CWriteableUserInvestor m_compareObject;
	
	static CMemoryStack<CUserInvestorIteratorAllByBrokerID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	CUserInvestorIteratorAllByBrokerID(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID)
	{
		init(pFactory,BrokerID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	static CUserInvestorIteratorAllByBrokerID *alloc(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///构造方法
	CUserInvestorIteratorAllByBrokerID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	void init(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///析构方法，将负责释放所占用的空间
	virtual ~CUserInvestorIteratorAllByBrokerID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CUserInvestor，必须在startFindAllByBrokerID以后，endFindAllByBrokerID之前叫用
	///@return	下一个满足条件CUserInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CUserInvestor *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByBrokerID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserInvestor * pAllByBrokerID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CUserInvestorIteratorAll是一个对用户投资者关系表使用All方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorIteratorAll: public CUserInvestorIterator
{
	friend class CUserInvestorFactory;
private:
	///检查此对象是否满足条件
	///@param	pUserInvestor		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CUserInvestor *pUserInvestor);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CUserInvestor *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CUserInvestor *m_pNext;

	///用于存储查询参数的对象
	CWriteableUserInvestor m_compareObject;
	
	static CMemoryStack<CUserInvestorIteratorAll> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	CUserInvestorIteratorAll(CUserInvestorFactory *pFactory
		)
	{
		init(pFactory);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	static CUserInvestorIteratorAll *alloc(CUserInvestorFactory *pFactory
		);

	///构造方法
	CUserInvestorIteratorAll(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	void init(CUserInvestorFactory *pFactory
		);

	///析构方法，将负责释放所占用的空间
	virtual ~CUserInvestorIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CUserInvestor，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CUserInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CUserInvestor *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAll 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserInvestor * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedIteratorAllByExchIDInvIDUserID是一个对错单表使用AllByExchIDInvIDUserID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedIteratorAllByExchIDInvIDUserID: public COrderInsertFailedIterator
{
	friend class COrderInsertFailedFactory;
private:
	///检查此对象是否满足条件
	///@param	pOrderInsertFailed		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(COrderInsertFailed *pOrderInsertFailed);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	COrderInsertFailed *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	COrderInsertFailed *m_pNext;

	///用于存储查询参数的对象
	CWriteableOrderInsertFailed m_compareObject;
	
	static CMemoryStack<COrderInsertFailedIteratorAllByExchIDInvIDUserID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	UserID	交易用户代码
	COrderInsertFailedIteratorAllByExchIDInvIDUserID(COrderInsertFailedFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,ExchangeID,InvestorID,UserID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	UserID	交易用户代码
	static COrderInsertFailedIteratorAllByExchIDInvIDUserID *alloc(COrderInsertFailedFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID);

	///构造方法
	COrderInsertFailedIteratorAllByExchIDInvIDUserID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	UserID	交易用户代码
	void init(COrderInsertFailedFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID);

	///析构方法，将负责释放所占用的空间
	virtual ~COrderInsertFailedIteratorAllByExchIDInvIDUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的COrderInsertFailed，必须在startFindAllByExchIDInvIDUserID以后，endFindAllByExchIDInvIDUserID之前叫用
	///@return	下一个满足条件COrderInsertFailed，如果已经没有一个满足要求了，则返回NULL
	virtual COrderInsertFailed *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByExchIDInvIDUserID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrderInsertFailed * pAllByExchIDInvIDUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedIteratorAllByExchIDInstruIDUserID是一个对错单表使用AllByExchIDInstruIDUserID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedIteratorAllByExchIDInstruIDUserID: public COrderInsertFailedIterator
{
	friend class COrderInsertFailedFactory;
private:
	///检查此对象是否满足条件
	///@param	pOrderInsertFailed		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(COrderInsertFailed *pOrderInsertFailed);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	COrderInsertFailed *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	COrderInsertFailed *m_pNext;

	///用于存储查询参数的对象
	CWriteableOrderInsertFailed m_compareObject;
	
	static CMemoryStack<COrderInsertFailedIteratorAllByExchIDInstruIDUserID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约号
	///@param	UserID	交易用户代码
	COrderInsertFailedIteratorAllByExchIDInstruIDUserID(COrderInsertFailedFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,ExchangeID,InstrumentID,UserID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约号
	///@param	UserID	交易用户代码
	static COrderInsertFailedIteratorAllByExchIDInstruIDUserID *alloc(COrderInsertFailedFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID);

	///构造方法
	COrderInsertFailedIteratorAllByExchIDInstruIDUserID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约号
	///@param	UserID	交易用户代码
	void init(COrderInsertFailedFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID);

	///析构方法，将负责释放所占用的空间
	virtual ~COrderInsertFailedIteratorAllByExchIDInstruIDUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的COrderInsertFailed，必须在startFindAllByExchIDInstruIDUserID以后，endFindAllByExchIDInstruIDUserID之前叫用
	///@return	下一个满足条件COrderInsertFailed，如果已经没有一个满足要求了，则返回NULL
	virtual COrderInsertFailed *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByExchIDInstruIDUserID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrderInsertFailed * pAllByExchIDInstruIDUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedIteratorAll是一个对错单表使用All方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedIteratorAll: public COrderInsertFailedIterator
{
	friend class COrderInsertFailedFactory;
private:
	///检查此对象是否满足条件
	///@param	pOrderInsertFailed		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(COrderInsertFailed *pOrderInsertFailed);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	COrderInsertFailed *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	COrderInsertFailed *m_pNext;

	///用于存储查询参数的对象
	CWriteableOrderInsertFailed m_compareObject;
	
	static CMemoryStack<COrderInsertFailedIteratorAll> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	COrderInsertFailedIteratorAll(COrderInsertFailedFactory *pFactory
		)
	{
		init(pFactory);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	static COrderInsertFailedIteratorAll *alloc(COrderInsertFailedFactory *pFactory
		);

	///构造方法
	COrderInsertFailedIteratorAll(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	void init(COrderInsertFailedFactory *pFactory
		);

	///析构方法，将负责释放所占用的空间
	virtual ~COrderInsertFailedIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的COrderInsertFailed，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件COrderInsertFailed，如果已经没有一个满足要求了，则返回NULL
	virtual COrderInsertFailed *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAll 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrderInsertFailed * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};



/////////////////////////////////////////////////////////////////////////
///CUserSessionIteratorByUserID是一个对交易员在线会话使用ByUserID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionIteratorByUserID: public CUserSessionIterator
{
	friend class CUserSessionFactory;
private:
	///检查此对象是否满足条件
	///@param	pUserSession		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CUserSession *pUserSession);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteableUserSession m_compareObject;
	
	static CMemoryStack<CUserSessionIteratorByUserID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	UserID	用户号
	CUserSessionIteratorByUserID(CUserSessionFactory *pFactory
		,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,UserID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	UserID	用户号
	static CUserSessionIteratorByUserID *alloc(CUserSessionFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///构造方法
	CUserSessionIteratorByUserID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	UserID	用户号
	void init(CUserSessionFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///析构方法，将负责释放所占用的空间
	virtual ~CUserSessionIteratorByUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CUserSession，必须在startFindByUserID以后，endFindByUserID之前叫用
	///@return	下一个满足条件CUserSession，如果已经没有一个满足要求了，则返回NULL
	virtual CUserSession *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pByUserID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserSession * pByUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};






/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateIteratorAllByInstrumentID是一个对金交所递延费率表使用AllByInstrumentID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateIteratorAllByInstrumentID: public CSGEDeferRateIterator
{
	friend class CSGEDeferRateFactory;
private:
	///检查此对象是否满足条件
	///@param	pSGEDeferRate		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CSGEDeferRate *pSGEDeferRate);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CSGEDeferRate *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CSGEDeferRate *m_pNext;

	///用于存储查询参数的对象
	CWriteableSGEDeferRate m_compareObject;
	
	static CMemoryStack<CSGEDeferRateIteratorAllByInstrumentID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	InstrumentID	合约代码
	CSGEDeferRateIteratorAllByInstrumentID(CSGEDeferRateFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID)
	{
		init(pFactory,InstrumentID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	InstrumentID	合约代码
	static CSGEDeferRateIteratorAllByInstrumentID *alloc(CSGEDeferRateFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///构造方法
	CSGEDeferRateIteratorAllByInstrumentID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	InstrumentID	合约代码
	void init(CSGEDeferRateFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///析构方法，将负责释放所占用的空间
	virtual ~CSGEDeferRateIteratorAllByInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CSGEDeferRate，必须在startFindAllByInstrumentID以后，endFindAllByInstrumentID之前叫用
	///@return	下一个满足条件CSGEDeferRate，如果已经没有一个满足要求了，则返回NULL
	virtual CSGEDeferRate *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAllByInstrumentID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSGEDeferRate * pAllByInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateIteratorAll是一个对金交所递延费率表使用All方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateIteratorAll: public CSGEDeferRateIterator
{
	friend class CSGEDeferRateFactory;
private:
	///检查此对象是否满足条件
	///@param	pSGEDeferRate		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CSGEDeferRate *pSGEDeferRate);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CSGEDeferRate *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CSGEDeferRate *m_pNext;

	///用于存储查询参数的对象
	CWriteableSGEDeferRate m_compareObject;
	
	static CMemoryStack<CSGEDeferRateIteratorAll> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	CSGEDeferRateIteratorAll(CSGEDeferRateFactory *pFactory
		)
	{
		init(pFactory);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	static CSGEDeferRateIteratorAll *alloc(CSGEDeferRateFactory *pFactory
		);

	///构造方法
	CSGEDeferRateIteratorAll(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	void init(CSGEDeferRateFactory *pFactory
		);

	///析构方法，将负责释放所占用的空间
	virtual ~CSGEDeferRateIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CSGEDeferRate，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CSGEDeferRate，如果已经没有一个满足要求了，则返回NULL
	virtual CSGEDeferRate *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAll 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSGEDeferRate * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CUserIPIteratorByUserID是一个对交易员IP地址使用ByUserID方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPIteratorByUserID: public CUserIPIterator
{
	friend class CUserIPFactory;
private:
	///检查此对象是否满足条件
	///@param	pUserIP		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CUserIP *pUserIP);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;

	///用于存储查询参数的对象
	CWriteableUserIP m_compareObject;
	
	static CMemoryStack<CUserIPIteratorByUserID> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	///@param	UserID	用户编号
	CUserIPIteratorByUserID(CUserIPFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,BrokerID,UserID);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	///@param	UserID	用户编号
	static CUserIPIteratorByUserID *alloc(CUserIPFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyUserIDType& UserID);

	///构造方法
	CUserIPIteratorByUserID(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	///@param	BrokerID	经纪公司代码
	///@param	UserID	用户编号
	void init(CUserIPFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyUserIDType& UserID);

	///析构方法，将负责释放所占用的空间
	virtual ~CUserIPIteratorByUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CUserIP，必须在startFindByUserID以后，endFindByUserID之前叫用
	///@return	下一个满足条件CUserIP，如果已经没有一个满足要求了，则返回NULL
	virtual CUserIP *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pByUserID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserIP * pByUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CMarketDataIteratorAll是一个对实时行情表使用All方法进行
///查找的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataIteratorAll: public CMarketDataIterator
{
	friend class CMarketDataFactory;
private:
	///检查此对象是否满足条件
	///@param	pMarketData		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(CMarketData *pMarketData);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CMarketData *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	CMarketData *m_pNext;

	///用于存储查询参数的对象
	CWriteableMarketData m_compareObject;
	
	static CMemoryStack<CMarketDataIteratorAll> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	CMarketDataIteratorAll(CMarketDataFactory *pFactory
		)
	{
		init(pFactory);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	static CMarketDataIteratorAll *alloc(CMarketDataFactory *pFactory
		);

	///构造方法
	CMarketDataIteratorAll(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	void init(CMarketDataFactory *pFactory
		);

	///析构方法，将负责释放所占用的空间
	virtual ~CMarketDataIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的CMarketData，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CMarketData，如果已经没有一个满足要求了，则返回NULL
	virtual CMarketData *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pAll 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableMarketData * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};



#endif
