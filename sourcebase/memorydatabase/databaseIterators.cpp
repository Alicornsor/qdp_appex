/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseIterators.cpp
///@brief实现了若干个内存数据库的iterator
///@history 
///20060127	hwp		创建该文件
/// 2013-01-22 longqy 添加delete this, 解决对象析构时未释放内存泄露的问题。
/////////////////////////////////////////////////////////////////////////

#include "databaseIterators.h"

//#define COUNT_SEARCH




CMemoryStack<COrderIteratorAllByUserID> COrderIteratorAllByUserID::iteratorList;
void COrderIteratorAllByUserID::init(COrderFactory *pFactory
		, const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use COrderIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.UserID=UserID.getValue();

}

COrderIteratorAllByUserID *COrderIteratorAllByUserID::alloc(COrderFactory *pFactory
		, const CReadOnlyUserIDType& UserID)
{
	COrderIteratorAllByUserID *it;
	it=iteratorList.alloc();
	it->init(pFactory,UserID);
	return it;
}

COrderIteratorAllByUserID::~COrderIteratorAllByUserID(void)
{
	m_Factory->endGet();
}

void COrderIteratorAllByUserID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void COrderIteratorAllByUserID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"COrderIteratorAllByUserID");
	
	char buffer[200];
	
	m_compareObject.UserID.getString(buffer);
	pLogger->output(indent+1,0,"query UserID=%s",buffer);
	
}

void COrderIteratorAllByUserID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(COrder *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(COrder *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void COrderIteratorAllByUserID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void COrderIteratorAllByUserID::UpdateCurrent(CWriteableOrder * pAllByUserID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByUserID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByUserIDForOrder;
#endif

COrder *COrderIteratorAllByUserID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int COrderIteratorAllByUserID::match(COrder *pOrder)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pOrder->UserID.getValue(),m_compareObject.UserID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<COrderIteratorAllByInvestorID> COrderIteratorAllByInvestorID::iteratorList;
void COrderIteratorAllByInvestorID::init(COrderFactory *pFactory
		, const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use COrderIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.InvestorID=InvestorID.getValue();

}

COrderIteratorAllByInvestorID *COrderIteratorAllByInvestorID::alloc(COrderFactory *pFactory
		, const CReadOnlyInvestorIDType& InvestorID)
{
	COrderIteratorAllByInvestorID *it;
	it=iteratorList.alloc();
	it->init(pFactory,InvestorID);
	return it;
}

COrderIteratorAllByInvestorID::~COrderIteratorAllByInvestorID(void)
{
	m_Factory->endGet();
}

void COrderIteratorAllByInvestorID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void COrderIteratorAllByInvestorID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"COrderIteratorAllByInvestorID");
	
	char buffer[200];
	
	m_compareObject.InvestorID.getString(buffer);
	pLogger->output(indent+1,0,"query InvestorID=%s",buffer);
	
}

void COrderIteratorAllByInvestorID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(COrder *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(COrder *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void COrderIteratorAllByInvestorID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void COrderIteratorAllByInvestorID::UpdateCurrent(CWriteableOrder * pAllByInvestorID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByInvestorID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByInvestorIDForOrder;
#endif

COrder *COrderIteratorAllByInvestorID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int COrderIteratorAllByInvestorID::match(COrder *pOrder)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pOrder->InvestorID.getValue(),m_compareObject.InvestorID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<COrderIteratorAllByExchIDInvIDUserID> COrderIteratorAllByExchIDInvIDUserID::iteratorList;
void COrderIteratorAllByExchIDInvIDUserID::init(COrderFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInvestorIDType& InvestorID, const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use COrderIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.ExchangeID=ExchangeID.getValue();
	m_compareObject.InvestorID=InvestorID.getValue();
	m_compareObject.UserID=UserID.getValue();

}

COrderIteratorAllByExchIDInvIDUserID *COrderIteratorAllByExchIDInvIDUserID::alloc(COrderFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInvestorIDType& InvestorID, const CReadOnlyUserIDType& UserID)
{
	COrderIteratorAllByExchIDInvIDUserID *it;
	it=iteratorList.alloc();
	it->init(pFactory,ExchangeID,InvestorID,UserID);
	return it;
}

COrderIteratorAllByExchIDInvIDUserID::~COrderIteratorAllByExchIDInvIDUserID(void)
{
	m_Factory->endGet();
}

void COrderIteratorAllByExchIDInvIDUserID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void COrderIteratorAllByExchIDInvIDUserID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"COrderIteratorAllByExchIDInvIDUserID");
	
	char buffer[200];
	
	m_compareObject.ExchangeID.getString(buffer);
	pLogger->output(indent+1,0,"query ExchangeID=%s",buffer);
	
	m_compareObject.InvestorID.getString(buffer);
	pLogger->output(indent+1,0,"query InvestorID=%s",buffer);
	
	m_compareObject.UserID.getString(buffer);
	pLogger->output(indent+1,0,"query UserID=%s",buffer);
	
}

void COrderIteratorAllByExchIDInvIDUserID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(COrder *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(COrder *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void COrderIteratorAllByExchIDInvIDUserID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void COrderIteratorAllByExchIDInvIDUserID::UpdateCurrent(CWriteableOrder * pAllByExchIDInvIDUserID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByExchIDInvIDUserID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByExchIDInvIDUserIDForOrder;
#endif

COrder *COrderIteratorAllByExchIDInvIDUserID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int COrderIteratorAllByExchIDInvIDUserID::match(COrder *pOrder)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pOrder->ExchangeID.getValue(),m_compareObject.ExchangeID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pOrder->InvestorID.getValue(),m_compareObject.InvestorID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pOrder->UserID.getValue(),m_compareObject.UserID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<COrderIteratorAllByExchIDInstruIDUserID> COrderIteratorAllByExchIDInstruIDUserID::iteratorList;
void COrderIteratorAllByExchIDInstruIDUserID::init(COrderFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInstrumentIDType& InstrumentID, const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use COrderIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.ExchangeID=ExchangeID.getValue();
	m_compareObject.InstrumentID=InstrumentID.getValue();
	m_compareObject.UserID=UserID.getValue();

}

COrderIteratorAllByExchIDInstruIDUserID *COrderIteratorAllByExchIDInstruIDUserID::alloc(COrderFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInstrumentIDType& InstrumentID, const CReadOnlyUserIDType& UserID)
{
	COrderIteratorAllByExchIDInstruIDUserID *it;
	it=iteratorList.alloc();
	it->init(pFactory,ExchangeID,InstrumentID,UserID);
	return it;
}

COrderIteratorAllByExchIDInstruIDUserID::~COrderIteratorAllByExchIDInstruIDUserID(void)
{
	m_Factory->endGet();
}

void COrderIteratorAllByExchIDInstruIDUserID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void COrderIteratorAllByExchIDInstruIDUserID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"COrderIteratorAllByExchIDInstruIDUserID");
	
	char buffer[200];
	
	m_compareObject.ExchangeID.getString(buffer);
	pLogger->output(indent+1,0,"query ExchangeID=%s",buffer);
	
	m_compareObject.InstrumentID.getString(buffer);
	pLogger->output(indent+1,0,"query InstrumentID=%s",buffer);
	
	m_compareObject.UserID.getString(buffer);
	pLogger->output(indent+1,0,"query UserID=%s",buffer);
	
}

void COrderIteratorAllByExchIDInstruIDUserID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(COrder *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(COrder *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void COrderIteratorAllByExchIDInstruIDUserID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void COrderIteratorAllByExchIDInstruIDUserID::UpdateCurrent(CWriteableOrder * pAllByExchIDInstruIDUserID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByExchIDInstruIDUserID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByExchIDInstruIDUserIDForOrder;
#endif

COrder *COrderIteratorAllByExchIDInstruIDUserID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int COrderIteratorAllByExchIDInstruIDUserID::match(COrder *pOrder)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pOrder->ExchangeID.getValue(),m_compareObject.ExchangeID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pOrder->UserID.getValue(),m_compareObject.UserID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<COrderIteratorAll> COrderIteratorAll::iteratorList;
void COrderIteratorAll::init(COrderFactory *pFactory
		)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use COrderIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();

}

COrderIteratorAll *COrderIteratorAll::alloc(COrderFactory *pFactory
		)
{
	COrderIteratorAll *it;
	it=iteratorList.alloc();
	it->init(pFactory);
	return it;
}

COrderIteratorAll::~COrderIteratorAll(void)
{
	m_Factory->endGet();
}

void COrderIteratorAll::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void COrderIteratorAll::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"COrderIteratorAll");
	
	
}

void COrderIteratorAll::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(COrder *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(COrder *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void COrderIteratorAll::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void COrderIteratorAll::UpdateCurrent(CWriteableOrder * pAll,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAll,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllForOrder;
#endif

COrder *COrderIteratorAll::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int COrderIteratorAll::match(COrder *pOrder)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}


CMemoryStack<CTradeIteratorByExchangeIDAndTradeID> CTradeIteratorByExchangeIDAndTradeID::iteratorList;
void CTradeIteratorByExchangeIDAndTradeID::init(CTradeFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyTradeIDType& TradeID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CTradeIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.ExchangeID=ExchangeID.getValue();
	m_compareObject.TradeID=TradeID.getValue();

}

CTradeIteratorByExchangeIDAndTradeID *CTradeIteratorByExchangeIDAndTradeID::alloc(CTradeFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyTradeIDType& TradeID)
{
	CTradeIteratorByExchangeIDAndTradeID *it;
	it=iteratorList.alloc();
	it->init(pFactory,ExchangeID,TradeID);
	return it;
}

CTradeIteratorByExchangeIDAndTradeID::~CTradeIteratorByExchangeIDAndTradeID(void)
{
}

void CTradeIteratorByExchangeIDAndTradeID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CTradeIteratorByExchangeIDAndTradeID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CTradeIteratorByExchangeIDAndTradeID");
	
	char buffer[200];
	
	m_compareObject.ExchangeID.getString(buffer);
	pLogger->output(indent+1,0,"query ExchangeID=%s",buffer);
	
	m_compareObject.TradeID.getString(buffer);
	pLogger->output(indent+1,0,"query TradeID=%s",buffer);
	
}

void CTradeIteratorByExchangeIDAndTradeID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pExchangeIDTradeIDIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pExchangeIDTradeIDIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CTradeIteratorByExchangeIDAndTradeID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CTrade *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CTradeIteratorByExchangeIDAndTradeID::UpdateCurrent(CWriteableTrade * pByExchangeIDAndTradeID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CTrade *)(m_pCurrent->pObject),pByExchangeIDAndTradeID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindByExchangeIDAndTradeIDForTrade;
#endif

CTrade *CTradeIteratorByExchangeIDAndTradeID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindByExchangeIDAndTradeIDForTrade++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CTrade *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CTrade *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CTradeIteratorByExchangeIDAndTradeID::match(CTrade *pTrade)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pTrade->ExchangeID.getValue(),m_compareObject.ExchangeID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pTrade->TradeID.getValue(),m_compareObject.TradeID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CTradeIteratorAllByExchIDInvIDUserID> CTradeIteratorAllByExchIDInvIDUserID::iteratorList;
void CTradeIteratorAllByExchIDInvIDUserID::init(CTradeFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInvestorIDType& InvestorID, const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CTradeIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.ExchangeID=ExchangeID.getValue();
	m_compareObject.InvestorID=InvestorID.getValue();
	m_compareObject.UserID=UserID.getValue();

}

CTradeIteratorAllByExchIDInvIDUserID *CTradeIteratorAllByExchIDInvIDUserID::alloc(CTradeFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInvestorIDType& InvestorID, const CReadOnlyUserIDType& UserID)
{
	CTradeIteratorAllByExchIDInvIDUserID *it;
	it=iteratorList.alloc();
	it->init(pFactory,ExchangeID,InvestorID,UserID);
	return it;
}

CTradeIteratorAllByExchIDInvIDUserID::~CTradeIteratorAllByExchIDInvIDUserID(void)
{
	m_Factory->endGet();
}

void CTradeIteratorAllByExchIDInvIDUserID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CTradeIteratorAllByExchIDInvIDUserID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CTradeIteratorAllByExchIDInvIDUserID");
	
	char buffer[200];
	
	m_compareObject.ExchangeID.getString(buffer);
	pLogger->output(indent+1,0,"query ExchangeID=%s",buffer);
	
	m_compareObject.InvestorID.getString(buffer);
	pLogger->output(indent+1,0,"query InvestorID=%s",buffer);
	
	m_compareObject.UserID.getString(buffer);
	pLogger->output(indent+1,0,"query UserID=%s",buffer);
	
}

void CTradeIteratorAllByExchIDInvIDUserID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CTrade *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CTrade *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CTradeIteratorAllByExchIDInvIDUserID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CTradeIteratorAllByExchIDInvIDUserID::UpdateCurrent(CWriteableTrade * pAllByExchIDInvIDUserID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByExchIDInvIDUserID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByExchIDInvIDUserIDForTrade;
#endif

CTrade *CTradeIteratorAllByExchIDInvIDUserID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CTradeIteratorAllByExchIDInvIDUserID::match(CTrade *pTrade)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pTrade->ExchangeID.getValue(),m_compareObject.ExchangeID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pTrade->InvestorID.getValue(),m_compareObject.InvestorID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pTrade->UserID.getValue(),m_compareObject.UserID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CTradeIteratorAllByInvestorID> CTradeIteratorAllByInvestorID::iteratorList;
void CTradeIteratorAllByInvestorID::init(CTradeFactory *pFactory
		, const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CTradeIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.InvestorID=InvestorID.getValue();

}

CTradeIteratorAllByInvestorID *CTradeIteratorAllByInvestorID::alloc(CTradeFactory *pFactory
		, const CReadOnlyInvestorIDType& InvestorID)
{
	CTradeIteratorAllByInvestorID *it;
	it=iteratorList.alloc();
	it->init(pFactory,InvestorID);
	return it;
}

CTradeIteratorAllByInvestorID::~CTradeIteratorAllByInvestorID(void)
{
	m_Factory->endGet();
}

void CTradeIteratorAllByInvestorID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CTradeIteratorAllByInvestorID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CTradeIteratorAllByInvestorID");
	
	char buffer[200];
	
	m_compareObject.InvestorID.getString(buffer);
	pLogger->output(indent+1,0,"query InvestorID=%s",buffer);
	
}

void CTradeIteratorAllByInvestorID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CTrade *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CTrade *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CTradeIteratorAllByInvestorID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CTradeIteratorAllByInvestorID::UpdateCurrent(CWriteableTrade * pAllByInvestorID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByInvestorID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByInvestorIDForTrade;
#endif

CTrade *CTradeIteratorAllByInvestorID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CTradeIteratorAllByInvestorID::match(CTrade *pTrade)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pTrade->InvestorID.getValue(),m_compareObject.InvestorID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CTradeIteratorAllByExchIDInstruIDUserID> CTradeIteratorAllByExchIDInstruIDUserID::iteratorList;
void CTradeIteratorAllByExchIDInstruIDUserID::init(CTradeFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInstrumentIDType& InstrumentID, const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CTradeIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.ExchangeID=ExchangeID.getValue();
	m_compareObject.InstrumentID=InstrumentID.getValue();
	m_compareObject.UserID=UserID.getValue();

}

CTradeIteratorAllByExchIDInstruIDUserID *CTradeIteratorAllByExchIDInstruIDUserID::alloc(CTradeFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInstrumentIDType& InstrumentID, const CReadOnlyUserIDType& UserID)
{
	CTradeIteratorAllByExchIDInstruIDUserID *it;
	it=iteratorList.alloc();
	it->init(pFactory,ExchangeID,InstrumentID,UserID);
	return it;
}

CTradeIteratorAllByExchIDInstruIDUserID::~CTradeIteratorAllByExchIDInstruIDUserID(void)
{
	m_Factory->endGet();
}

void CTradeIteratorAllByExchIDInstruIDUserID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CTradeIteratorAllByExchIDInstruIDUserID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CTradeIteratorAllByExchIDInstruIDUserID");
	
	char buffer[200];
	
	m_compareObject.ExchangeID.getString(buffer);
	pLogger->output(indent+1,0,"query ExchangeID=%s",buffer);
	
	m_compareObject.InstrumentID.getString(buffer);
	pLogger->output(indent+1,0,"query InstrumentID=%s",buffer);
	
	m_compareObject.UserID.getString(buffer);
	pLogger->output(indent+1,0,"query UserID=%s",buffer);
	
}

void CTradeIteratorAllByExchIDInstruIDUserID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CTrade *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CTrade *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CTradeIteratorAllByExchIDInstruIDUserID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CTradeIteratorAllByExchIDInstruIDUserID::UpdateCurrent(CWriteableTrade * pAllByExchIDInstruIDUserID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByExchIDInstruIDUserID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByExchIDInstruIDUserIDForTrade;
#endif

CTrade *CTradeIteratorAllByExchIDInstruIDUserID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CTradeIteratorAllByExchIDInstruIDUserID::match(CTrade *pTrade)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pTrade->ExchangeID.getValue(),m_compareObject.ExchangeID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pTrade->UserID.getValue(),m_compareObject.UserID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CTradeIteratorAll> CTradeIteratorAll::iteratorList;
void CTradeIteratorAll::init(CTradeFactory *pFactory
		)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CTradeIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();

}

CTradeIteratorAll *CTradeIteratorAll::alloc(CTradeFactory *pFactory
		)
{
	CTradeIteratorAll *it;
	it=iteratorList.alloc();
	it->init(pFactory);
	return it;
}

CTradeIteratorAll::~CTradeIteratorAll(void)
{
	m_Factory->endGet();
}

void CTradeIteratorAll::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CTradeIteratorAll::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CTradeIteratorAll");
	
	
}

void CTradeIteratorAll::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CTrade *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CTrade *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CTradeIteratorAll::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CTradeIteratorAll::UpdateCurrent(CWriteableTrade * pAll,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAll,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllForTrade;
#endif

CTrade *CTradeIteratorAll::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CTradeIteratorAll::match(CTrade *pTrade)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}


CMemoryStack<CPreOrderIteratorByAPIID> CPreOrderIteratorByAPIID::iteratorList;
void CPreOrderIteratorByAPIID::init(CPreOrderFactory *pFactory
		, const CReadOnlyNumberType& APIID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CPreOrderIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.APIID=APIID.getValue();

}

CPreOrderIteratorByAPIID *CPreOrderIteratorByAPIID::alloc(CPreOrderFactory *pFactory
		, const CReadOnlyNumberType& APIID)
{
	CPreOrderIteratorByAPIID *it;
	it=iteratorList.alloc();
	it->init(pFactory,APIID);
	return it;
}

CPreOrderIteratorByAPIID::~CPreOrderIteratorByAPIID(void)
{
}

void CPreOrderIteratorByAPIID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CPreOrderIteratorByAPIID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CPreOrderIteratorByAPIID");
	
	char buffer[200];
	
	m_compareObject.APIID.getString(buffer);
	pLogger->output(indent+1,0,"query APIID=%s",buffer);
	
}

void CPreOrderIteratorByAPIID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pAPIIDIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pAPIIDIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CPreOrderIteratorByAPIID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CPreOrder *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CPreOrderIteratorByAPIID::UpdateCurrent(CWriteablePreOrder * pByAPIID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CPreOrder *)(m_pCurrent->pObject),pByAPIID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindByAPIIDForPreOrder;
#endif

CPreOrder *CPreOrderIteratorByAPIID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindByAPIIDForPreOrder++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CPreOrder *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CPreOrder *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CPreOrderIteratorByAPIID::match(CPreOrder *pPreOrder)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pPreOrder->APIID.getValue(),m_compareObject.APIID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}



CMemoryStack<CInvestorPositionIteratorAllByExIDAndInstrumentID> CInvestorPositionIteratorAllByExIDAndInstrumentID::iteratorList;
void CInvestorPositionIteratorAllByExIDAndInstrumentID::init(CInvestorPositionFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInstrumentIDType& InstrumentID)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorPositionIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.ExchangeID=ExchangeID.getValue();
	m_compareObject.InstrumentID=InstrumentID.getValue();

}

CInvestorPositionIteratorAllByExIDAndInstrumentID *CInvestorPositionIteratorAllByExIDAndInstrumentID::alloc(CInvestorPositionFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInstrumentIDType& InstrumentID)
{
	CInvestorPositionIteratorAllByExIDAndInstrumentID *it;
	it=iteratorList.alloc();
	it->init(pFactory,ExchangeID,InstrumentID);
	return it;
}

CInvestorPositionIteratorAllByExIDAndInstrumentID::~CInvestorPositionIteratorAllByExIDAndInstrumentID(void)
{
}

void CInvestorPositionIteratorAllByExIDAndInstrumentID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CInvestorPositionIteratorAllByExIDAndInstrumentID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorPositionIteratorAllByExIDAndInstrumentID");
	
	char buffer[200];
	
	m_compareObject.ExchangeID.getString(buffer);
	pLogger->output(indent+1,0,"query ExchangeID=%s",buffer);
	
	m_compareObject.InstrumentID.getString(buffer);
	pLogger->output(indent+1,0,"query InstrumentID=%s",buffer);
	
}

void CInvestorPositionIteratorAllByExIDAndInstrumentID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pExIDAndInstrumentIDIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pExIDAndInstrumentIDIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CInvestorPositionIteratorAllByExIDAndInstrumentID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CInvestorPosition *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorPositionIteratorAllByExIDAndInstrumentID::UpdateCurrent(CWriteableInvestorPosition * pAllByExIDAndInstrumentID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CInvestorPosition *)(m_pCurrent->pObject),pAllByExIDAndInstrumentID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByExIDAndInstrumentIDForInvestorPosition;
#endif

CInvestorPosition *CInvestorPositionIteratorAllByExIDAndInstrumentID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindAllByExIDAndInstrumentIDForInvestorPosition++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CInvestorPosition *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CInvestorPosition *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CInvestorPositionIteratorAllByExIDAndInstrumentID::match(CInvestorPosition *pInvestorPosition)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInvestorPosition->ExchangeID.getValue(),m_compareObject.ExchangeID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pInvestorPosition->InstrumentID.getValue(),m_compareObject.InstrumentID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CInvestorPositionIteratorByInvestorID> CInvestorPositionIteratorByInvestorID::iteratorList;
void CInvestorPositionIteratorByInvestorID::init(CInvestorPositionFactory *pFactory
		, const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorPositionIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.InvestorID=InvestorID.getValue();
	m_compareObject.InvestorID="";

}

CInvestorPositionIteratorByInvestorID *CInvestorPositionIteratorByInvestorID::alloc(CInvestorPositionFactory *pFactory
		, const CReadOnlyInvestorIDType& InvestorID)
{
	CInvestorPositionIteratorByInvestorID *it;
	it=iteratorList.alloc();
	it->init(pFactory,InvestorID);
	return it;
}

CInvestorPositionIteratorByInvestorID::~CInvestorPositionIteratorByInvestorID(void)
{
}

void CInvestorPositionIteratorByInvestorID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CInvestorPositionIteratorByInvestorID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorPositionIteratorByInvestorID");
	
	char buffer[200];
	
	m_compareObject.InvestorID.getString(buffer);
	pLogger->output(indent+1,0,"query InvestorID=%s",buffer);
	
}

void CInvestorPositionIteratorByInvestorID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pInvestorIDIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pInvestorIDIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CInvestorPositionIteratorByInvestorID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CInvestorPosition *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorPositionIteratorByInvestorID::UpdateCurrent(CWriteableInvestorPosition * pByInvestorID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CInvestorPosition *)(m_pCurrent->pObject),pByInvestorID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindByInvestorIDForInvestorPosition;
#endif

CInvestorPosition *CInvestorPositionIteratorByInvestorID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindByInvestorIDForInvestorPosition++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CInvestorPosition *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CInvestorPosition *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CInvestorPositionIteratorByInvestorID::match(CInvestorPosition *pInvestorPosition)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInvestorPosition->InvestorID.getValue(),m_compareObject.InvestorID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CInvestorPositionIteratorAllByBrokerID> CInvestorPositionIteratorAllByBrokerID::iteratorList;
void CInvestorPositionIteratorAllByBrokerID::init(CInvestorPositionFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorPositionIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.BrokerID=BrokerID.getValue();

}

CInvestorPositionIteratorAllByBrokerID *CInvestorPositionIteratorAllByBrokerID::alloc(CInvestorPositionFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID)
{
	CInvestorPositionIteratorAllByBrokerID *it;
	it=iteratorList.alloc();
	it->init(pFactory,BrokerID);
	return it;
}

CInvestorPositionIteratorAllByBrokerID::~CInvestorPositionIteratorAllByBrokerID(void)
{
	m_Factory->endGet();
}

void CInvestorPositionIteratorAllByBrokerID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInvestorPositionIteratorAllByBrokerID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorPositionIteratorAllByBrokerID");
	
	char buffer[200];
	
	m_compareObject.BrokerID.getString(buffer);
	pLogger->output(indent+1,0,"query BrokerID=%s",buffer);
	
}

void CInvestorPositionIteratorAllByBrokerID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInvestorPosition *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInvestorPosition *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInvestorPositionIteratorAllByBrokerID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorPositionIteratorAllByBrokerID::UpdateCurrent(CWriteableInvestorPosition * pAllByBrokerID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByBrokerID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByBrokerIDForInvestorPosition;
#endif

CInvestorPosition *CInvestorPositionIteratorAllByBrokerID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInvestorPositionIteratorAllByBrokerID::match(CInvestorPosition *pInvestorPosition)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInvestorPosition->BrokerID.getValue(),m_compareObject.BrokerID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CInvestorPositionIteratorAllByInstrumentID> CInvestorPositionIteratorAllByInstrumentID::iteratorList;
void CInvestorPositionIteratorAllByInstrumentID::init(CInvestorPositionFactory *pFactory
		, const CReadOnlyInstrumentIDType& InstrumentID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorPositionIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.InstrumentID=InstrumentID.getValue();

}

CInvestorPositionIteratorAllByInstrumentID *CInvestorPositionIteratorAllByInstrumentID::alloc(CInvestorPositionFactory *pFactory
		, const CReadOnlyInstrumentIDType& InstrumentID)
{
	CInvestorPositionIteratorAllByInstrumentID *it;
	it=iteratorList.alloc();
	it->init(pFactory,InstrumentID);
	return it;
}

CInvestorPositionIteratorAllByInstrumentID::~CInvestorPositionIteratorAllByInstrumentID(void)
{
	m_Factory->endGet();
}

void CInvestorPositionIteratorAllByInstrumentID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInvestorPositionIteratorAllByInstrumentID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorPositionIteratorAllByInstrumentID");
	
	char buffer[200];
	
	m_compareObject.InstrumentID.getString(buffer);
	pLogger->output(indent+1,0,"query InstrumentID=%s",buffer);
	
}

void CInvestorPositionIteratorAllByInstrumentID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInvestorPosition *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInvestorPosition *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInvestorPositionIteratorAllByInstrumentID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorPositionIteratorAllByInstrumentID::UpdateCurrent(CWriteableInvestorPosition * pAllByInstrumentID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByInstrumentID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByInstrumentIDForInvestorPosition;
#endif

CInvestorPosition *CInvestorPositionIteratorAllByInstrumentID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInvestorPositionIteratorAllByInstrumentID::match(CInvestorPosition *pInvestorPosition)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInvestorPosition->InstrumentID.getValue(),m_compareObject.InstrumentID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CInvestorPositionIteratorAllByExchangeID> CInvestorPositionIteratorAllByExchangeID::iteratorList;
void CInvestorPositionIteratorAllByExchangeID::init(CInvestorPositionFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorPositionIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.ExchangeID=ExchangeID.getValue();

}

CInvestorPositionIteratorAllByExchangeID *CInvestorPositionIteratorAllByExchangeID::alloc(CInvestorPositionFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID)
{
	CInvestorPositionIteratorAllByExchangeID *it;
	it=iteratorList.alloc();
	it->init(pFactory,ExchangeID);
	return it;
}

CInvestorPositionIteratorAllByExchangeID::~CInvestorPositionIteratorAllByExchangeID(void)
{
	m_Factory->endGet();
}

void CInvestorPositionIteratorAllByExchangeID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInvestorPositionIteratorAllByExchangeID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorPositionIteratorAllByExchangeID");
	
	char buffer[200];
	
	m_compareObject.ExchangeID.getString(buffer);
	pLogger->output(indent+1,0,"query ExchangeID=%s",buffer);
	
}

void CInvestorPositionIteratorAllByExchangeID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInvestorPosition *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInvestorPosition *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInvestorPositionIteratorAllByExchangeID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorPositionIteratorAllByExchangeID::UpdateCurrent(CWriteableInvestorPosition * pAllByExchangeID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByExchangeID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByExchangeIDForInvestorPosition;
#endif

CInvestorPosition *CInvestorPositionIteratorAllByExchangeID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInvestorPositionIteratorAllByExchangeID::match(CInvestorPosition *pInvestorPosition)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInvestorPosition->ExchangeID.getValue(),m_compareObject.ExchangeID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CInvestorPositionIteratorAllByInvestorIDAndInstrumentID> CInvestorPositionIteratorAllByInvestorIDAndInstrumentID::iteratorList;
void CInvestorPositionIteratorAllByInvestorIDAndInstrumentID::init(CInvestorPositionFactory *pFactory
		, const CReadOnlyInvestorIDType& InvestorID, const CReadOnlyInstrumentIDType& InstrumentID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorPositionIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.InvestorID=InvestorID.getValue();
	m_compareObject.InstrumentID=InstrumentID.getValue();

}

CInvestorPositionIteratorAllByInvestorIDAndInstrumentID *CInvestorPositionIteratorAllByInvestorIDAndInstrumentID::alloc(CInvestorPositionFactory *pFactory
		, const CReadOnlyInvestorIDType& InvestorID, const CReadOnlyInstrumentIDType& InstrumentID)
{
	CInvestorPositionIteratorAllByInvestorIDAndInstrumentID *it;
	it=iteratorList.alloc();
	it->init(pFactory,InvestorID,InstrumentID);
	return it;
}

CInvestorPositionIteratorAllByInvestorIDAndInstrumentID::~CInvestorPositionIteratorAllByInvestorIDAndInstrumentID(void)
{
	m_Factory->endGet();
}

void CInvestorPositionIteratorAllByInvestorIDAndInstrumentID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInvestorPositionIteratorAllByInvestorIDAndInstrumentID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorPositionIteratorAllByInvestorIDAndInstrumentID");
	
	char buffer[200];
	
	m_compareObject.InvestorID.getString(buffer);
	pLogger->output(indent+1,0,"query InvestorID=%s",buffer);
	
	m_compareObject.InstrumentID.getString(buffer);
	pLogger->output(indent+1,0,"query InstrumentID=%s",buffer);
	
}

void CInvestorPositionIteratorAllByInvestorIDAndInstrumentID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInvestorPosition *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInvestorPosition *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInvestorPositionIteratorAllByInvestorIDAndInstrumentID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorPositionIteratorAllByInvestorIDAndInstrumentID::UpdateCurrent(CWriteableInvestorPosition * pAllByInvestorIDAndInstrumentID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByInvestorIDAndInstrumentID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByInvestorIDAndInstrumentIDForInvestorPosition;
#endif

CInvestorPosition *CInvestorPositionIteratorAllByInvestorIDAndInstrumentID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInvestorPositionIteratorAllByInvestorIDAndInstrumentID::match(CInvestorPosition *pInvestorPosition)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInvestorPosition->InvestorID.getValue(),m_compareObject.InvestorID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pInvestorPosition->InstrumentID.getValue(),m_compareObject.InstrumentID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CInvestorPositionIteratorAll> CInvestorPositionIteratorAll::iteratorList;
void CInvestorPositionIteratorAll::init(CInvestorPositionFactory *pFactory
		)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorPositionIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();

}

CInvestorPositionIteratorAll *CInvestorPositionIteratorAll::alloc(CInvestorPositionFactory *pFactory
		)
{
	CInvestorPositionIteratorAll *it;
	it=iteratorList.alloc();
	it->init(pFactory);
	return it;
}

CInvestorPositionIteratorAll::~CInvestorPositionIteratorAll(void)
{
	m_Factory->endGet();
}

void CInvestorPositionIteratorAll::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInvestorPositionIteratorAll::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorPositionIteratorAll");
	
	
}

void CInvestorPositionIteratorAll::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInvestorPosition *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInvestorPosition *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInvestorPositionIteratorAll::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorPositionIteratorAll::UpdateCurrent(CWriteableInvestorPosition * pAll,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAll,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllForInvestorPosition;
#endif

CInvestorPosition *CInvestorPositionIteratorAll::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInvestorPositionIteratorAll::match(CInvestorPosition *pInvestorPosition)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}


CMemoryStack<CInvestorAccountIteratorAllByInvestorID> CInvestorAccountIteratorAllByInvestorID::iteratorList;
void CInvestorAccountIteratorAllByInvestorID::init(CInvestorAccountFactory *pFactory
		, const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorAccountIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.InvestorID=InvestorID.getValue();

}

CInvestorAccountIteratorAllByInvestorID *CInvestorAccountIteratorAllByInvestorID::alloc(CInvestorAccountFactory *pFactory
		, const CReadOnlyInvestorIDType& InvestorID)
{
	CInvestorAccountIteratorAllByInvestorID *it;
	it=iteratorList.alloc();
	it->init(pFactory,InvestorID);
	return it;
}

CInvestorAccountIteratorAllByInvestorID::~CInvestorAccountIteratorAllByInvestorID(void)
{
	m_Factory->endGet();
}

void CInvestorAccountIteratorAllByInvestorID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInvestorAccountIteratorAllByInvestorID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorAccountIteratorAllByInvestorID");
	
	char buffer[200];
	
	m_compareObject.InvestorID.getString(buffer);
	pLogger->output(indent+1,0,"query InvestorID=%s",buffer);
	
}

void CInvestorAccountIteratorAllByInvestorID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInvestorAccount *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInvestorAccount *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInvestorAccountIteratorAllByInvestorID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorAccountIteratorAllByInvestorID::UpdateCurrent(CWriteableInvestorAccount * pAllByInvestorID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByInvestorID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByInvestorIDForInvestorAccount;
#endif

CInvestorAccount *CInvestorAccountIteratorAllByInvestorID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInvestorAccountIteratorAllByInvestorID::match(CInvestorAccount *pInvestorAccount)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInvestorAccount->InvestorID.getValue(),m_compareObject.InvestorID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CInvestorAccountIteratorAllByBrokerID> CInvestorAccountIteratorAllByBrokerID::iteratorList;
void CInvestorAccountIteratorAllByBrokerID::init(CInvestorAccountFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorAccountIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.BrokerID=BrokerID.getValue();

}

CInvestorAccountIteratorAllByBrokerID *CInvestorAccountIteratorAllByBrokerID::alloc(CInvestorAccountFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID)
{
	CInvestorAccountIteratorAllByBrokerID *it;
	it=iteratorList.alloc();
	it->init(pFactory,BrokerID);
	return it;
}

CInvestorAccountIteratorAllByBrokerID::~CInvestorAccountIteratorAllByBrokerID(void)
{
	m_Factory->endGet();
}

void CInvestorAccountIteratorAllByBrokerID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInvestorAccountIteratorAllByBrokerID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorAccountIteratorAllByBrokerID");
	
	char buffer[200];
	
	m_compareObject.BrokerID.getString(buffer);
	pLogger->output(indent+1,0,"query BrokerID=%s",buffer);
	
}

void CInvestorAccountIteratorAllByBrokerID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInvestorAccount *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInvestorAccount *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInvestorAccountIteratorAllByBrokerID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorAccountIteratorAllByBrokerID::UpdateCurrent(CWriteableInvestorAccount * pAllByBrokerID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByBrokerID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByBrokerIDForInvestorAccount;
#endif

CInvestorAccount *CInvestorAccountIteratorAllByBrokerID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInvestorAccountIteratorAllByBrokerID::match(CInvestorAccount *pInvestorAccount)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInvestorAccount->BrokerID.getValue(),m_compareObject.BrokerID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CInvestorAccountIteratorAll> CInvestorAccountIteratorAll::iteratorList;
void CInvestorAccountIteratorAll::init(CInvestorAccountFactory *pFactory
		)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorAccountIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();

}

CInvestorAccountIteratorAll *CInvestorAccountIteratorAll::alloc(CInvestorAccountFactory *pFactory
		)
{
	CInvestorAccountIteratorAll *it;
	it=iteratorList.alloc();
	it->init(pFactory);
	return it;
}

CInvestorAccountIteratorAll::~CInvestorAccountIteratorAll(void)
{
	m_Factory->endGet();
}

void CInvestorAccountIteratorAll::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInvestorAccountIteratorAll::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorAccountIteratorAll");
	
	
}

void CInvestorAccountIteratorAll::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInvestorAccount *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInvestorAccount *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInvestorAccountIteratorAll::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorAccountIteratorAll::UpdateCurrent(CWriteableInvestorAccount * pAll,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAll,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllForInvestorAccount;
#endif

CInvestorAccount *CInvestorAccountIteratorAll::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInvestorAccountIteratorAll::match(CInvestorAccount *pInvestorAccount)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}



CMemoryStack<CExchangeIteratorStartByExchangeID> CExchangeIteratorStartByExchangeID::iteratorList;
void CExchangeIteratorStartByExchangeID::init(CExchangeFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CExchangeIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.ExchangeID=ExchangeID.getValue();

}

CExchangeIteratorStartByExchangeID *CExchangeIteratorStartByExchangeID::alloc(CExchangeFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID)
{
	CExchangeIteratorStartByExchangeID *it;
	it=iteratorList.alloc();
	it->init(pFactory,ExchangeID);
	return it;
}

CExchangeIteratorStartByExchangeID::~CExchangeIteratorStartByExchangeID(void)
{
}

void CExchangeIteratorStartByExchangeID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CExchangeIteratorStartByExchangeID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CExchangeIteratorStartByExchangeID");
	
	char buffer[200];
	
	m_compareObject.ExchangeID.getString(buffer);
	pLogger->output(indent+1,0,"query ExchangeID=%s",buffer);
	
}

void CExchangeIteratorStartByExchangeID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pExchangeIDIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pExchangeIDIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CExchangeIteratorStartByExchangeID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CExchange *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CExchangeIteratorStartByExchangeID::UpdateCurrent(CWriteableExchange * pStartByExchangeID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CExchange *)(m_pCurrent->pObject),pStartByExchangeID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindStartByExchangeIDForExchange;
#endif

CExchange *CExchangeIteratorStartByExchangeID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindStartByExchangeIDForExchange++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CExchange *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CExchange *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CExchangeIteratorStartByExchangeID::match(CExchange *pExchange)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}

CMemoryStack<CExchangeIteratorAll> CExchangeIteratorAll::iteratorList;
void CExchangeIteratorAll::init(CExchangeFactory *pFactory
		)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CExchangeIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();

}

CExchangeIteratorAll *CExchangeIteratorAll::alloc(CExchangeFactory *pFactory
		)
{
	CExchangeIteratorAll *it;
	it=iteratorList.alloc();
	it->init(pFactory);
	return it;
}

CExchangeIteratorAll::~CExchangeIteratorAll(void)
{
	m_Factory->endGet();
}

void CExchangeIteratorAll::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CExchangeIteratorAll::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CExchangeIteratorAll");
	
	
}

void CExchangeIteratorAll::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CExchange *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CExchange *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CExchangeIteratorAll::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CExchangeIteratorAll::UpdateCurrent(CWriteableExchange * pAll,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAll,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllForExchange;
#endif

CExchange *CExchangeIteratorAll::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CExchangeIteratorAll::match(CExchange *pExchange)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}



CMemoryStack<CInstrumentIteratorAllByInstrumentID> CInstrumentIteratorAllByInstrumentID::iteratorList;
void CInstrumentIteratorAllByInstrumentID::init(CInstrumentFactory *pFactory
		, const CReadOnlyInstrumentIDType& InstrumentID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CInstrumentIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.InstrumentID=InstrumentID.getValue();

}

CInstrumentIteratorAllByInstrumentID *CInstrumentIteratorAllByInstrumentID::alloc(CInstrumentFactory *pFactory
		, const CReadOnlyInstrumentIDType& InstrumentID)
{
	CInstrumentIteratorAllByInstrumentID *it;
	it=iteratorList.alloc();
	it->init(pFactory,InstrumentID);
	return it;
}

CInstrumentIteratorAllByInstrumentID::~CInstrumentIteratorAllByInstrumentID(void)
{
}

void CInstrumentIteratorAllByInstrumentID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CInstrumentIteratorAllByInstrumentID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInstrumentIteratorAllByInstrumentID");
	
	char buffer[200];
	
	m_compareObject.InstrumentID.getString(buffer);
	pLogger->output(indent+1,0,"query InstrumentID=%s",buffer);
	
}

void CInstrumentIteratorAllByInstrumentID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pInstrumentIDIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pInstrumentIDIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CInstrumentIteratorAllByInstrumentID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CInstrument *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CInstrumentIteratorAllByInstrumentID::UpdateCurrent(CWriteableInstrument * pAllByInstrumentID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CInstrument *)(m_pCurrent->pObject),pAllByInstrumentID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByInstrumentIDForInstrument;
#endif

CInstrument *CInstrumentIteratorAllByInstrumentID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindAllByInstrumentIDForInstrument++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CInstrument *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CInstrument *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CInstrumentIteratorAllByInstrumentID::match(CInstrument *pInstrument)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}

CMemoryStack<CInstrumentIteratorAllByExchangeID> CInstrumentIteratorAllByExchangeID::iteratorList;
void CInstrumentIteratorAllByExchangeID::init(CInstrumentFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CInstrumentIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.ExchangeID=ExchangeID.getValue();

}

CInstrumentIteratorAllByExchangeID *CInstrumentIteratorAllByExchangeID::alloc(CInstrumentFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID)
{
	CInstrumentIteratorAllByExchangeID *it;
	it=iteratorList.alloc();
	it->init(pFactory,ExchangeID);
	return it;
}

CInstrumentIteratorAllByExchangeID::~CInstrumentIteratorAllByExchangeID(void)
{
	m_Factory->endGet();
}

void CInstrumentIteratorAllByExchangeID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInstrumentIteratorAllByExchangeID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInstrumentIteratorAllByExchangeID");
	
	char buffer[200];
	
	m_compareObject.ExchangeID.getString(buffer);
	pLogger->output(indent+1,0,"query ExchangeID=%s",buffer);
	
}

void CInstrumentIteratorAllByExchangeID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInstrument *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInstrument *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInstrumentIteratorAllByExchangeID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInstrumentIteratorAllByExchangeID::UpdateCurrent(CWriteableInstrument * pAllByExchangeID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByExchangeID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByExchangeIDForInstrument;
#endif

CInstrument *CInstrumentIteratorAllByExchangeID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInstrumentIteratorAllByExchangeID::match(CInstrument *pInstrument)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInstrument->ExchangeID.getValue(),m_compareObject.ExchangeID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CInstrumentIteratorAllByProductID> CInstrumentIteratorAllByProductID::iteratorList;
void CInstrumentIteratorAllByProductID::init(CInstrumentFactory *pFactory
		, const CReadOnlyProductIDType& ProductID)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CInstrumentIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.ProductID=ProductID.getValue();

}

CInstrumentIteratorAllByProductID *CInstrumentIteratorAllByProductID::alloc(CInstrumentFactory *pFactory
		, const CReadOnlyProductIDType& ProductID)
{
	CInstrumentIteratorAllByProductID *it;
	it=iteratorList.alloc();
	it->init(pFactory,ProductID);
	return it;
}

CInstrumentIteratorAllByProductID::~CInstrumentIteratorAllByProductID(void)
{
	m_Factory->endGet();
}

void CInstrumentIteratorAllByProductID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInstrumentIteratorAllByProductID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInstrumentIteratorAllByProductID");
	
	char buffer[200];
	
	m_compareObject.ProductID.getString(buffer);
	pLogger->output(indent+1,0,"query ProductID=%s",buffer);
	
}

void CInstrumentIteratorAllByProductID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInstrument *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInstrument *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInstrumentIteratorAllByProductID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInstrumentIteratorAllByProductID::UpdateCurrent(CWriteableInstrument * pAllByProductID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByProductID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByProductIDForInstrument;
#endif

CInstrument *CInstrumentIteratorAllByProductID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInstrumentIteratorAllByProductID::match(CInstrument *pInstrument)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInstrument->ProductID.getValue(),m_compareObject.ProductID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CInstrumentIteratorAll> CInstrumentIteratorAll::iteratorList;
void CInstrumentIteratorAll::init(CInstrumentFactory *pFactory
		)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CInstrumentIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();

}

CInstrumentIteratorAll *CInstrumentIteratorAll::alloc(CInstrumentFactory *pFactory
		)
{
	CInstrumentIteratorAll *it;
	it=iteratorList.alloc();
	it->init(pFactory);
	return it;
}

CInstrumentIteratorAll::~CInstrumentIteratorAll(void)
{
	m_Factory->endGet();
}

void CInstrumentIteratorAll::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInstrumentIteratorAll::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInstrumentIteratorAll");
	
	
}

void CInstrumentIteratorAll::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInstrument *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInstrument *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInstrumentIteratorAll::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInstrumentIteratorAll::UpdateCurrent(CWriteableInstrument * pAll,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAll,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllForInstrument;
#endif

CInstrument *CInstrumentIteratorAll::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInstrumentIteratorAll::match(CInstrument *pInstrument)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}


CMemoryStack<CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID> CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID::iteratorList;
void CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID::init(CCmbInstrumentDetailFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInstrumentIDType& ArbiInstrumentID)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CCmbInstrumentDetailIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.ExchangeID=ExchangeID.getValue();
	m_compareObject.ArbiInstrumentID=ArbiInstrumentID.getValue();

}

CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID *CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID::alloc(CCmbInstrumentDetailFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInstrumentIDType& ArbiInstrumentID)
{
	CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID *it;
	it=iteratorList.alloc();
	it->init(pFactory,ExchangeID,ArbiInstrumentID);
	return it;
}

CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID::~CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID(void)
{
}

void CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID");
	
	char buffer[200];
	
	m_compareObject.ExchangeID.getString(buffer);
	pLogger->output(indent+1,0,"query ExchangeID=%s",buffer);
	
	m_compareObject.ArbiInstrumentID.getString(buffer);
	pLogger->output(indent+1,0,"query ArbiInstrumentID=%s",buffer);
	
}

void CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pExchangeIDArbiInstrumentIDIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pExchangeIDArbiInstrumentIDIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CCmbInstrumentDetail *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID::UpdateCurrent(CWriteableCmbInstrumentDetail * pAllByExchangeIDAndArbiInstrumentID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CCmbInstrumentDetail *)(m_pCurrent->pObject),pAllByExchangeIDAndArbiInstrumentID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByExchangeIDAndArbiInstrumentIDForCmbInstrumentDetail;
#endif

CCmbInstrumentDetail *CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindAllByExchangeIDAndArbiInstrumentIDForCmbInstrumentDetail++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CCmbInstrumentDetail *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CCmbInstrumentDetail *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID::match(CCmbInstrumentDetail *pCmbInstrumentDetail)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pCmbInstrumentDetail->ExchangeID.getValue(),m_compareObject.ExchangeID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pCmbInstrumentDetail->ArbiInstrumentID.getValue(),m_compareObject.ArbiInstrumentID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID> CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID::iteratorList;
void CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID::init(CCmbInstrumentDetailFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInstrumentIDType& SingleInstrumentID)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CCmbInstrumentDetailIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.ExchangeID=ExchangeID.getValue();
	m_compareObject.SingleInstrumentID=SingleInstrumentID.getValue();

}

CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID *CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID::alloc(CCmbInstrumentDetailFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInstrumentIDType& SingleInstrumentID)
{
	CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID *it;
	it=iteratorList.alloc();
	it->init(pFactory,ExchangeID,SingleInstrumentID);
	return it;
}

CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID::~CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID(void)
{
}

void CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID");
	
	char buffer[200];
	
	m_compareObject.ExchangeID.getString(buffer);
	pLogger->output(indent+1,0,"query ExchangeID=%s",buffer);
	
	m_compareObject.SingleInstrumentID.getString(buffer);
	pLogger->output(indent+1,0,"query SingleInstrumentID=%s",buffer);
	
}

void CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pExchangeIDSingleInstrumentIDIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pExchangeIDSingleInstrumentIDIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CCmbInstrumentDetail *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID::UpdateCurrent(CWriteableCmbInstrumentDetail * pAllByExchangeIDAndSingleInstrumentID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CCmbInstrumentDetail *)(m_pCurrent->pObject),pAllByExchangeIDAndSingleInstrumentID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByExchangeIDAndSingleInstrumentIDForCmbInstrumentDetail;
#endif

CCmbInstrumentDetail *CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindAllByExchangeIDAndSingleInstrumentIDForCmbInstrumentDetail++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CCmbInstrumentDetail *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CCmbInstrumentDetail *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID::match(CCmbInstrumentDetail *pCmbInstrumentDetail)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pCmbInstrumentDetail->ExchangeID.getValue(),m_compareObject.ExchangeID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pCmbInstrumentDetail->SingleInstrumentID.getValue(),m_compareObject.SingleInstrumentID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}


CMemoryStack<CClientTradingIDIteratorByBrokerIDInvestorID> CClientTradingIDIteratorByBrokerIDInvestorID::iteratorList;
void CClientTradingIDIteratorByBrokerIDInvestorID::init(CClientTradingIDFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID, const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CClientTradingIDIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.BrokerID=BrokerID.getValue();
	m_compareObject.InvestorID=InvestorID.getValue();

}

CClientTradingIDIteratorByBrokerIDInvestorID *CClientTradingIDIteratorByBrokerIDInvestorID::alloc(CClientTradingIDFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID, const CReadOnlyInvestorIDType& InvestorID)
{
	CClientTradingIDIteratorByBrokerIDInvestorID *it;
	it=iteratorList.alloc();
	it->init(pFactory,BrokerID,InvestorID);
	return it;
}

CClientTradingIDIteratorByBrokerIDInvestorID::~CClientTradingIDIteratorByBrokerIDInvestorID(void)
{
}

void CClientTradingIDIteratorByBrokerIDInvestorID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CClientTradingIDIteratorByBrokerIDInvestorID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CClientTradingIDIteratorByBrokerIDInvestorID");
	
	char buffer[200];
	
	m_compareObject.BrokerID.getString(buffer);
	pLogger->output(indent+1,0,"query BrokerID=%s",buffer);
	
	m_compareObject.InvestorID.getString(buffer);
	pLogger->output(indent+1,0,"query InvestorID=%s",buffer);
	
}

void CClientTradingIDIteratorByBrokerIDInvestorID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pBrokerIDInvestorIDIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pBrokerIDInvestorIDIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CClientTradingIDIteratorByBrokerIDInvestorID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CClientTradingID *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CClientTradingIDIteratorByBrokerIDInvestorID::UpdateCurrent(CWriteableClientTradingID * pByBrokerIDInvestorID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CClientTradingID *)(m_pCurrent->pObject),pByBrokerIDInvestorID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindByBrokerIDInvestorIDForClientTradingID;
#endif

CClientTradingID *CClientTradingIDIteratorByBrokerIDInvestorID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindByBrokerIDInvestorIDForClientTradingID++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CClientTradingID *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CClientTradingID *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CClientTradingIDIteratorByBrokerIDInvestorID::match(CClientTradingID *pClientTradingID)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pClientTradingID->BrokerID.getValue(),m_compareObject.BrokerID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pClientTradingID->InvestorID.getValue(),m_compareObject.InvestorID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CClientTradingIDIteratorAllByBrokerID> CClientTradingIDIteratorAllByBrokerID::iteratorList;
void CClientTradingIDIteratorAllByBrokerID::init(CClientTradingIDFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CClientTradingIDIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.BrokerID=BrokerID.getValue();

}

CClientTradingIDIteratorAllByBrokerID *CClientTradingIDIteratorAllByBrokerID::alloc(CClientTradingIDFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID)
{
	CClientTradingIDIteratorAllByBrokerID *it;
	it=iteratorList.alloc();
	it->init(pFactory,BrokerID);
	return it;
}

CClientTradingIDIteratorAllByBrokerID::~CClientTradingIDIteratorAllByBrokerID(void)
{
	m_Factory->endGet();
}

void CClientTradingIDIteratorAllByBrokerID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CClientTradingIDIteratorAllByBrokerID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CClientTradingIDIteratorAllByBrokerID");
	
	char buffer[200];
	
	m_compareObject.BrokerID.getString(buffer);
	pLogger->output(indent+1,0,"query BrokerID=%s",buffer);
	
}

void CClientTradingIDIteratorAllByBrokerID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CClientTradingID *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CClientTradingID *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CClientTradingIDIteratorAllByBrokerID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CClientTradingIDIteratorAllByBrokerID::UpdateCurrent(CWriteableClientTradingID * pAllByBrokerID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByBrokerID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByBrokerIDForClientTradingID;
#endif

CClientTradingID *CClientTradingIDIteratorAllByBrokerID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CClientTradingIDIteratorAllByBrokerID::match(CClientTradingID *pClientTradingID)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pClientTradingID->BrokerID.getValue(),m_compareObject.BrokerID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CClientTradingIDIteratorAll> CClientTradingIDIteratorAll::iteratorList;
void CClientTradingIDIteratorAll::init(CClientTradingIDFactory *pFactory
		)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CClientTradingIDIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();

}

CClientTradingIDIteratorAll *CClientTradingIDIteratorAll::alloc(CClientTradingIDFactory *pFactory
		)
{
	CClientTradingIDIteratorAll *it;
	it=iteratorList.alloc();
	it->init(pFactory);
	return it;
}

CClientTradingIDIteratorAll::~CClientTradingIDIteratorAll(void)
{
	m_Factory->endGet();
}

void CClientTradingIDIteratorAll::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CClientTradingIDIteratorAll::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CClientTradingIDIteratorAll");
	
	
}

void CClientTradingIDIteratorAll::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CClientTradingID *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CClientTradingID *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CClientTradingIDIteratorAll::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CClientTradingIDIteratorAll::UpdateCurrent(CWriteableClientTradingID * pAll,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAll,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllForClientTradingID;
#endif

CClientTradingID *CClientTradingIDIteratorAll::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CClientTradingIDIteratorAll::match(CClientTradingID *pClientTradingID)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}


CMemoryStack<CInvestorIteratorByInvestorID> CInvestorIteratorByInvestorID::iteratorList;
void CInvestorIteratorByInvestorID::init(CInvestorFactory *pFactory
		, const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.InvestorID=InvestorID.getValue();

}

CInvestorIteratorByInvestorID *CInvestorIteratorByInvestorID::alloc(CInvestorFactory *pFactory
		, const CReadOnlyInvestorIDType& InvestorID)
{
	CInvestorIteratorByInvestorID *it;
	it=iteratorList.alloc();
	it->init(pFactory,InvestorID);
	return it;
}

CInvestorIteratorByInvestorID::~CInvestorIteratorByInvestorID(void)
{
}

void CInvestorIteratorByInvestorID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CInvestorIteratorByInvestorID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorIteratorByInvestorID");
	
	char buffer[200];
	
	m_compareObject.InvestorID.getString(buffer);
	pLogger->output(indent+1,0,"query InvestorID=%s",buffer);
	
}

void CInvestorIteratorByInvestorID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pBrokerIDInvestorIDIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pBrokerIDInvestorIDIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CInvestorIteratorByInvestorID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CInvestor *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorIteratorByInvestorID::UpdateCurrent(CWriteableInvestor * pByInvestorID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CInvestor *)(m_pCurrent->pObject),pByInvestorID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindByInvestorIDForInvestor;
#endif

CInvestor *CInvestorIteratorByInvestorID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindByInvestorIDForInvestor++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CInvestor *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CInvestor *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CInvestorIteratorByInvestorID::match(CInvestor *pInvestor)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInvestor->InvestorID.getValue(),m_compareObject.InvestorID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}


CMemoryStack<CInvestorMarginIteratorByBrkIDExIDIstIDVstID> CInvestorMarginIteratorByBrkIDExIDIstIDVstID::iteratorList;
void CInvestorMarginIteratorByBrkIDExIDIstIDVstID::init(CInvestorMarginFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInstrumentIDType& InstrumentID, const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorMarginIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.BrokerID=BrokerID.getValue();
	m_compareObject.ExchangeID=ExchangeID.getValue();
	m_compareObject.InstrumentID=InstrumentID.getValue();
	m_compareObject.InvestorID=InvestorID.getValue();

}

CInvestorMarginIteratorByBrkIDExIDIstIDVstID *CInvestorMarginIteratorByBrkIDExIDIstIDVstID::alloc(CInvestorMarginFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInstrumentIDType& InstrumentID, const CReadOnlyInvestorIDType& InvestorID)
{
	CInvestorMarginIteratorByBrkIDExIDIstIDVstID *it;
	it=iteratorList.alloc();
	it->init(pFactory,BrokerID,ExchangeID,InstrumentID,InvestorID);
	return it;
}

CInvestorMarginIteratorByBrkIDExIDIstIDVstID::~CInvestorMarginIteratorByBrkIDExIDIstIDVstID(void)
{
}

void CInvestorMarginIteratorByBrkIDExIDIstIDVstID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CInvestorMarginIteratorByBrkIDExIDIstIDVstID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorMarginIteratorByBrkIDExIDIstIDVstID");
	
	char buffer[200];
	
	m_compareObject.BrokerID.getString(buffer);
	pLogger->output(indent+1,0,"query BrokerID=%s",buffer);
	
	m_compareObject.ExchangeID.getString(buffer);
	pLogger->output(indent+1,0,"query ExchangeID=%s",buffer);
	
	m_compareObject.InstrumentID.getString(buffer);
	pLogger->output(indent+1,0,"query InstrumentID=%s",buffer);
	
	m_compareObject.InvestorID.getString(buffer);
	pLogger->output(indent+1,0,"query InvestorID=%s",buffer);
	
}

void CInvestorMarginIteratorByBrkIDExIDIstIDVstID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pBrkIDExIDIstIDVstIDIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pBrkIDExIDIstIDVstIDIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CInvestorMarginIteratorByBrkIDExIDIstIDVstID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CInvestorMargin *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorMarginIteratorByBrkIDExIDIstIDVstID::UpdateCurrent(CWriteableInvestorMargin * pByBrkIDExIDIstIDVstID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CInvestorMargin *)(m_pCurrent->pObject),pByBrkIDExIDIstIDVstID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindByBrkIDExIDIstIDVstIDForInvestorMargin;
#endif

CInvestorMargin *CInvestorMarginIteratorByBrkIDExIDIstIDVstID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindByBrkIDExIDIstIDVstIDForInvestorMargin++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CInvestorMargin *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CInvestorMargin *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CInvestorMarginIteratorByBrkIDExIDIstIDVstID::match(CInvestorMargin *pInvestorMargin)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInvestorMargin->BrokerID.getValue(),m_compareObject.BrokerID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pInvestorMargin->ExchangeID.getValue(),m_compareObject.ExchangeID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pInvestorMargin->InstrumentID.getValue(),m_compareObject.InstrumentID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pInvestorMargin->InvestorID.getValue(),m_compareObject.InvestorID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CInvestorMarginIteratorByInstrumentID> CInvestorMarginIteratorByInstrumentID::iteratorList;
void CInvestorMarginIteratorByInstrumentID::init(CInvestorMarginFactory *pFactory
		, const CReadOnlyInstrumentIDType& InstrumentID)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorMarginIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.InstrumentID=InstrumentID.getValue();

}

CInvestorMarginIteratorByInstrumentID *CInvestorMarginIteratorByInstrumentID::alloc(CInvestorMarginFactory *pFactory
		, const CReadOnlyInstrumentIDType& InstrumentID)
{
	CInvestorMarginIteratorByInstrumentID *it;
	it=iteratorList.alloc();
	it->init(pFactory,InstrumentID);
	return it;
}

CInvestorMarginIteratorByInstrumentID::~CInvestorMarginIteratorByInstrumentID(void)
{
	m_Factory->endGet();
}

void CInvestorMarginIteratorByInstrumentID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInvestorMarginIteratorByInstrumentID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorMarginIteratorByInstrumentID");
	
	char buffer[200];
	
	m_compareObject.InstrumentID.getString(buffer);
	pLogger->output(indent+1,0,"query InstrumentID=%s",buffer);
	
}

void CInvestorMarginIteratorByInstrumentID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInvestorMargin *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInvestorMargin *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInvestorMarginIteratorByInstrumentID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorMarginIteratorByInstrumentID::UpdateCurrent(CWriteableInvestorMargin * pByInstrumentID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pByInstrumentID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindByInstrumentIDForInvestorMargin;
#endif

CInvestorMargin *CInvestorMarginIteratorByInstrumentID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInvestorMarginIteratorByInstrumentID::match(CInvestorMargin *pInvestorMargin)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInvestorMargin->InstrumentID.getValue(),m_compareObject.InstrumentID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CInvestorMarginIteratorByBrokerID> CInvestorMarginIteratorByBrokerID::iteratorList;
void CInvestorMarginIteratorByBrokerID::init(CInvestorMarginFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorMarginIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.BrokerID=BrokerID.getValue();

}

CInvestorMarginIteratorByBrokerID *CInvestorMarginIteratorByBrokerID::alloc(CInvestorMarginFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID)
{
	CInvestorMarginIteratorByBrokerID *it;
	it=iteratorList.alloc();
	it->init(pFactory,BrokerID);
	return it;
}

CInvestorMarginIteratorByBrokerID::~CInvestorMarginIteratorByBrokerID(void)
{
	m_Factory->endGet();
}

void CInvestorMarginIteratorByBrokerID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInvestorMarginIteratorByBrokerID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorMarginIteratorByBrokerID");
	
	char buffer[200];
	
	m_compareObject.BrokerID.getString(buffer);
	pLogger->output(indent+1,0,"query BrokerID=%s",buffer);
	
}

void CInvestorMarginIteratorByBrokerID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInvestorMargin *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInvestorMargin *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInvestorMarginIteratorByBrokerID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorMarginIteratorByBrokerID::UpdateCurrent(CWriteableInvestorMargin * pByBrokerID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pByBrokerID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindByBrokerIDForInvestorMargin;
#endif

CInvestorMargin *CInvestorMarginIteratorByBrokerID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInvestorMarginIteratorByBrokerID::match(CInvestorMargin *pInvestorMargin)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInvestorMargin->BrokerID.getValue(),m_compareObject.BrokerID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CInvestorMarginIteratorAll> CInvestorMarginIteratorAll::iteratorList;
void CInvestorMarginIteratorAll::init(CInvestorMarginFactory *pFactory
		)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorMarginIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();

}

CInvestorMarginIteratorAll *CInvestorMarginIteratorAll::alloc(CInvestorMarginFactory *pFactory
		)
{
	CInvestorMarginIteratorAll *it;
	it=iteratorList.alloc();
	it->init(pFactory);
	return it;
}

CInvestorMarginIteratorAll::~CInvestorMarginIteratorAll(void)
{
	m_Factory->endGet();
}

void CInvestorMarginIteratorAll::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInvestorMarginIteratorAll::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorMarginIteratorAll");
	
	
}

void CInvestorMarginIteratorAll::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInvestorMargin *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInvestorMargin *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInvestorMarginIteratorAll::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorMarginIteratorAll::UpdateCurrent(CWriteableInvestorMargin * pAll,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAll,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllForInvestorMargin;
#endif

CInvestorMargin *CInvestorMarginIteratorAll::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInvestorMarginIteratorAll::match(CInvestorMargin *pInvestorMargin)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}


CMemoryStack<CInvestorFeeIteratorByInstrumentID> CInvestorFeeIteratorByInstrumentID::iteratorList;
void CInvestorFeeIteratorByInstrumentID::init(CInvestorFeeFactory *pFactory
		, const CReadOnlyInstrumentIDType& InstrumentID)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorFeeIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.InstrumentID=InstrumentID.getValue();

}

CInvestorFeeIteratorByInstrumentID *CInvestorFeeIteratorByInstrumentID::alloc(CInvestorFeeFactory *pFactory
		, const CReadOnlyInstrumentIDType& InstrumentID)
{
	CInvestorFeeIteratorByInstrumentID *it;
	it=iteratorList.alloc();
	it->init(pFactory,InstrumentID);
	return it;
}

CInvestorFeeIteratorByInstrumentID::~CInvestorFeeIteratorByInstrumentID(void)
{
}

void CInvestorFeeIteratorByInstrumentID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CInvestorFeeIteratorByInstrumentID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorFeeIteratorByInstrumentID");
	
	char buffer[200];
	
	m_compareObject.InstrumentID.getString(buffer);
	pLogger->output(indent+1,0,"query InstrumentID=%s",buffer);
	
}

void CInvestorFeeIteratorByInstrumentID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pInstrumentIDIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pInstrumentIDIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CInvestorFeeIteratorByInstrumentID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CInvestorFee *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorFeeIteratorByInstrumentID::UpdateCurrent(CWriteableInvestorFee * pByInstrumentID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CInvestorFee *)(m_pCurrent->pObject),pByInstrumentID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindByInstrumentIDForInvestorFee;
#endif

CInvestorFee *CInvestorFeeIteratorByInstrumentID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindByInstrumentIDForInvestorFee++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CInvestorFee *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CInvestorFee *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CInvestorFeeIteratorByInstrumentID::match(CInvestorFee *pInvestorFee)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInvestorFee->InstrumentID.getValue(),m_compareObject.InstrumentID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CInvestorFeeIteratorByBrokerID> CInvestorFeeIteratorByBrokerID::iteratorList;
void CInvestorFeeIteratorByBrokerID::init(CInvestorFeeFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorFeeIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.BrokerID=BrokerID.getValue();

}

CInvestorFeeIteratorByBrokerID *CInvestorFeeIteratorByBrokerID::alloc(CInvestorFeeFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID)
{
	CInvestorFeeIteratorByBrokerID *it;
	it=iteratorList.alloc();
	it->init(pFactory,BrokerID);
	return it;
}

CInvestorFeeIteratorByBrokerID::~CInvestorFeeIteratorByBrokerID(void)
{
	m_Factory->endGet();
}

void CInvestorFeeIteratorByBrokerID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInvestorFeeIteratorByBrokerID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorFeeIteratorByBrokerID");
	
	char buffer[200];
	
	m_compareObject.BrokerID.getString(buffer);
	pLogger->output(indent+1,0,"query BrokerID=%s",buffer);
	
}

void CInvestorFeeIteratorByBrokerID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInvestorFee *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInvestorFee *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInvestorFeeIteratorByBrokerID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorFeeIteratorByBrokerID::UpdateCurrent(CWriteableInvestorFee * pByBrokerID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pByBrokerID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindByBrokerIDForInvestorFee;
#endif

CInvestorFee *CInvestorFeeIteratorByBrokerID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInvestorFeeIteratorByBrokerID::match(CInvestorFee *pInvestorFee)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pInvestorFee->BrokerID.getValue(),m_compareObject.BrokerID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CInvestorFeeIteratorAll> CInvestorFeeIteratorAll::iteratorList;
void CInvestorFeeIteratorAll::init(CInvestorFeeFactory *pFactory
		)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CInvestorFeeIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();

}

CInvestorFeeIteratorAll *CInvestorFeeIteratorAll::alloc(CInvestorFeeFactory *pFactory
		)
{
	CInvestorFeeIteratorAll *it;
	it=iteratorList.alloc();
	it->init(pFactory);
	return it;
}

CInvestorFeeIteratorAll::~CInvestorFeeIteratorAll(void)
{
	m_Factory->endGet();
}

void CInvestorFeeIteratorAll::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CInvestorFeeIteratorAll::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorFeeIteratorAll");
	
	
}

void CInvestorFeeIteratorAll::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CInvestorFee *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CInvestorFee *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CInvestorFeeIteratorAll::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CInvestorFeeIteratorAll::UpdateCurrent(CWriteableInvestorFee * pAll,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAll,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllForInvestorFee;
#endif

CInvestorFee *CInvestorFeeIteratorAll::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CInvestorFeeIteratorAll::match(CInvestorFee *pInvestorFee)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}


CMemoryStack<CUserIteratorStartByUserID> CUserIteratorStartByUserID::iteratorList;
void CUserIteratorStartByUserID::init(CUserFactory *pFactory
		, const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CUserIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.UserID=UserID.getValue();

}

CUserIteratorStartByUserID *CUserIteratorStartByUserID::alloc(CUserFactory *pFactory
		, const CReadOnlyUserIDType& UserID)
{
	CUserIteratorStartByUserID *it;
	it=iteratorList.alloc();
	it->init(pFactory,UserID);
	return it;
}

CUserIteratorStartByUserID::~CUserIteratorStartByUserID(void)
{
}

void CUserIteratorStartByUserID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CUserIteratorStartByUserID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CUserIteratorStartByUserID");
	
	char buffer[200];
	
	m_compareObject.UserID.getString(buffer);
	pLogger->output(indent+1,0,"query UserID=%s",buffer);
	
}

void CUserIteratorStartByUserID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pUserIDIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pUserIDIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CUserIteratorStartByUserID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CUser *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CUserIteratorStartByUserID::UpdateCurrent(CWriteableUser * pStartByUserID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CUser *)(m_pCurrent->pObject),pStartByUserID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindStartByUserIDForUser;
#endif

CUser *CUserIteratorStartByUserID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindStartByUserIDForUser++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CUser *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CUser *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CUserIteratorStartByUserID::match(CUser *pUser)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}


CMemoryStack<CUserInvestorIteratorByBrokerIDInvestorID> CUserInvestorIteratorByBrokerIDInvestorID::iteratorList;
void CUserInvestorIteratorByBrokerIDInvestorID::init(CUserInvestorFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID, const CReadOnlyInvestorIDType& InvestorID)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CUserInvestorIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.BrokerID=BrokerID.getValue();
	m_compareObject.InvestorID=InvestorID.getValue();

}

CUserInvestorIteratorByBrokerIDInvestorID *CUserInvestorIteratorByBrokerIDInvestorID::alloc(CUserInvestorFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID, const CReadOnlyInvestorIDType& InvestorID)
{
	CUserInvestorIteratorByBrokerIDInvestorID *it;
	it=iteratorList.alloc();
	it->init(pFactory,BrokerID,InvestorID);
	return it;
}

CUserInvestorIteratorByBrokerIDInvestorID::~CUserInvestorIteratorByBrokerIDInvestorID(void)
{
}

void CUserInvestorIteratorByBrokerIDInvestorID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CUserInvestorIteratorByBrokerIDInvestorID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CUserInvestorIteratorByBrokerIDInvestorID");
	
	char buffer[200];
	
	m_compareObject.BrokerID.getString(buffer);
	pLogger->output(indent+1,0,"query BrokerID=%s",buffer);
	
	m_compareObject.InvestorID.getString(buffer);
	pLogger->output(indent+1,0,"query InvestorID=%s",buffer);
	
}

void CUserInvestorIteratorByBrokerIDInvestorID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pBrokerIDInvestorIDIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pBrokerIDInvestorIDIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CUserInvestorIteratorByBrokerIDInvestorID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CUserInvestor *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CUserInvestorIteratorByBrokerIDInvestorID::UpdateCurrent(CWriteableUserInvestor * pByBrokerIDInvestorID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CUserInvestor *)(m_pCurrent->pObject),pByBrokerIDInvestorID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindByBrokerIDInvestorIDForUserInvestor;
#endif

CUserInvestor *CUserInvestorIteratorByBrokerIDInvestorID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindByBrokerIDInvestorIDForUserInvestor++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CUserInvestor *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CUserInvestor *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CUserInvestorIteratorByBrokerIDInvestorID::match(CUserInvestor *pUserInvestor)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pUserInvestor->BrokerID.getValue(),m_compareObject.BrokerID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pUserInvestor->InvestorID.getValue(),m_compareObject.InvestorID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CUserInvestorIteratorAllByUserID> CUserInvestorIteratorAllByUserID::iteratorList;
void CUserInvestorIteratorAllByUserID::init(CUserInvestorFactory *pFactory
		, const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CUserInvestorIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.UserID=UserID.getValue();

}

CUserInvestorIteratorAllByUserID *CUserInvestorIteratorAllByUserID::alloc(CUserInvestorFactory *pFactory
		, const CReadOnlyUserIDType& UserID)
{
	CUserInvestorIteratorAllByUserID *it;
	it=iteratorList.alloc();
	it->init(pFactory,UserID);
	return it;
}

CUserInvestorIteratorAllByUserID::~CUserInvestorIteratorAllByUserID(void)
{
	m_Factory->endGet();
}

void CUserInvestorIteratorAllByUserID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CUserInvestorIteratorAllByUserID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CUserInvestorIteratorAllByUserID");
	
	char buffer[200];
	
	m_compareObject.UserID.getString(buffer);
	pLogger->output(indent+1,0,"query UserID=%s",buffer);
	
}

void CUserInvestorIteratorAllByUserID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CUserInvestor *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CUserInvestor *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CUserInvestorIteratorAllByUserID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CUserInvestorIteratorAllByUserID::UpdateCurrent(CWriteableUserInvestor * pAllByUserID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByUserID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByUserIDForUserInvestor;
#endif

CUserInvestor *CUserInvestorIteratorAllByUserID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CUserInvestorIteratorAllByUserID::match(CUserInvestor *pUserInvestor)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pUserInvestor->UserID.getValue(),m_compareObject.UserID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CUserInvestorIteratorAllByBrokerIDUserID> CUserInvestorIteratorAllByBrokerIDUserID::iteratorList;
void CUserInvestorIteratorAllByBrokerIDUserID::init(CUserInvestorFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID, const CReadOnlyUserIDType& UserID)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CUserInvestorIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.BrokerID=BrokerID.getValue();
	m_compareObject.UserID=UserID.getValue();

}

CUserInvestorIteratorAllByBrokerIDUserID *CUserInvestorIteratorAllByBrokerIDUserID::alloc(CUserInvestorFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID, const CReadOnlyUserIDType& UserID)
{
	CUserInvestorIteratorAllByBrokerIDUserID *it;
	it=iteratorList.alloc();
	it->init(pFactory,BrokerID,UserID);
	return it;
}

CUserInvestorIteratorAllByBrokerIDUserID::~CUserInvestorIteratorAllByBrokerIDUserID(void)
{
	m_Factory->endGet();
}

void CUserInvestorIteratorAllByBrokerIDUserID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CUserInvestorIteratorAllByBrokerIDUserID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CUserInvestorIteratorAllByBrokerIDUserID");
	
	char buffer[200];
	
	m_compareObject.BrokerID.getString(buffer);
	pLogger->output(indent+1,0,"query BrokerID=%s",buffer);
	
	m_compareObject.UserID.getString(buffer);
	pLogger->output(indent+1,0,"query UserID=%s",buffer);
	
}

void CUserInvestorIteratorAllByBrokerIDUserID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CUserInvestor *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CUserInvestor *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CUserInvestorIteratorAllByBrokerIDUserID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CUserInvestorIteratorAllByBrokerIDUserID::UpdateCurrent(CWriteableUserInvestor * pAllByBrokerIDUserID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByBrokerIDUserID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByBrokerIDUserIDForUserInvestor;
#endif

CUserInvestor *CUserInvestorIteratorAllByBrokerIDUserID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CUserInvestorIteratorAllByBrokerIDUserID::match(CUserInvestor *pUserInvestor)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pUserInvestor->BrokerID.getValue(),m_compareObject.BrokerID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pUserInvestor->UserID.getValue(),m_compareObject.UserID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CUserInvestorIteratorAllByBrokerID> CUserInvestorIteratorAllByBrokerID::iteratorList;
void CUserInvestorIteratorAllByBrokerID::init(CUserInvestorFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CUserInvestorIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.BrokerID=BrokerID.getValue();

}

CUserInvestorIteratorAllByBrokerID *CUserInvestorIteratorAllByBrokerID::alloc(CUserInvestorFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID)
{
	CUserInvestorIteratorAllByBrokerID *it;
	it=iteratorList.alloc();
	it->init(pFactory,BrokerID);
	return it;
}

CUserInvestorIteratorAllByBrokerID::~CUserInvestorIteratorAllByBrokerID(void)
{
	m_Factory->endGet();
}

void CUserInvestorIteratorAllByBrokerID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CUserInvestorIteratorAllByBrokerID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CUserInvestorIteratorAllByBrokerID");
	
	char buffer[200];
	
	m_compareObject.BrokerID.getString(buffer);
	pLogger->output(indent+1,0,"query BrokerID=%s",buffer);
	
}

void CUserInvestorIteratorAllByBrokerID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CUserInvestor *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CUserInvestor *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CUserInvestorIteratorAllByBrokerID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CUserInvestorIteratorAllByBrokerID::UpdateCurrent(CWriteableUserInvestor * pAllByBrokerID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByBrokerID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByBrokerIDForUserInvestor;
#endif

CUserInvestor *CUserInvestorIteratorAllByBrokerID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CUserInvestorIteratorAllByBrokerID::match(CUserInvestor *pUserInvestor)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pUserInvestor->BrokerID.getValue(),m_compareObject.BrokerID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<CUserInvestorIteratorAll> CUserInvestorIteratorAll::iteratorList;
void CUserInvestorIteratorAll::init(CUserInvestorFactory *pFactory
		)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CUserInvestorIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();

}

CUserInvestorIteratorAll *CUserInvestorIteratorAll::alloc(CUserInvestorFactory *pFactory
		)
{
	CUserInvestorIteratorAll *it;
	it=iteratorList.alloc();
	it->init(pFactory);
	return it;
}

CUserInvestorIteratorAll::~CUserInvestorIteratorAll(void)
{
	m_Factory->endGet();
}

void CUserInvestorIteratorAll::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CUserInvestorIteratorAll::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CUserInvestorIteratorAll");
	
	
}

void CUserInvestorIteratorAll::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CUserInvestor *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CUserInvestor *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CUserInvestorIteratorAll::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CUserInvestorIteratorAll::UpdateCurrent(CWriteableUserInvestor * pAll,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAll,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllForUserInvestor;
#endif

CUserInvestor *CUserInvestorIteratorAll::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CUserInvestorIteratorAll::match(CUserInvestor *pUserInvestor)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}


CMemoryStack<COrderInsertFailedIteratorAllByExchIDInvIDUserID> COrderInsertFailedIteratorAllByExchIDInvIDUserID::iteratorList;
void COrderInsertFailedIteratorAllByExchIDInvIDUserID::init(COrderInsertFailedFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInvestorIDType& InvestorID, const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use COrderInsertFailedIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.ExchangeID=ExchangeID.getValue();
	m_compareObject.InvestorID=InvestorID.getValue();
	m_compareObject.UserID=UserID.getValue();

}

COrderInsertFailedIteratorAllByExchIDInvIDUserID *COrderInsertFailedIteratorAllByExchIDInvIDUserID::alloc(COrderInsertFailedFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInvestorIDType& InvestorID, const CReadOnlyUserIDType& UserID)
{
	COrderInsertFailedIteratorAllByExchIDInvIDUserID *it;
	it=iteratorList.alloc();
	it->init(pFactory,ExchangeID,InvestorID,UserID);
	return it;
}

COrderInsertFailedIteratorAllByExchIDInvIDUserID::~COrderInsertFailedIteratorAllByExchIDInvIDUserID(void)
{
	m_Factory->endGet();
}

void COrderInsertFailedIteratorAllByExchIDInvIDUserID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void COrderInsertFailedIteratorAllByExchIDInvIDUserID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"COrderInsertFailedIteratorAllByExchIDInvIDUserID");
	
	char buffer[200];
	
	m_compareObject.ExchangeID.getString(buffer);
	pLogger->output(indent+1,0,"query ExchangeID=%s",buffer);
	
	m_compareObject.InvestorID.getString(buffer);
	pLogger->output(indent+1,0,"query InvestorID=%s",buffer);
	
	m_compareObject.UserID.getString(buffer);
	pLogger->output(indent+1,0,"query UserID=%s",buffer);
	
}

void COrderInsertFailedIteratorAllByExchIDInvIDUserID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(COrderInsertFailed *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(COrderInsertFailed *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void COrderInsertFailedIteratorAllByExchIDInvIDUserID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void COrderInsertFailedIteratorAllByExchIDInvIDUserID::UpdateCurrent(CWriteableOrderInsertFailed * pAllByExchIDInvIDUserID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByExchIDInvIDUserID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByExchIDInvIDUserIDForOrderInsertFailed;
#endif

COrderInsertFailed *COrderInsertFailedIteratorAllByExchIDInvIDUserID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int COrderInsertFailedIteratorAllByExchIDInvIDUserID::match(COrderInsertFailed *pOrderInsertFailed)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pOrderInsertFailed->ExchangeID.getValue(),m_compareObject.ExchangeID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pOrderInsertFailed->InvestorID.getValue(),m_compareObject.InvestorID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pOrderInsertFailed->UserID.getValue(),m_compareObject.UserID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<COrderInsertFailedIteratorAllByExchIDInstruIDUserID> COrderInsertFailedIteratorAllByExchIDInstruIDUserID::iteratorList;
void COrderInsertFailedIteratorAllByExchIDInstruIDUserID::init(COrderInsertFailedFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInstrumentIDType& InstrumentID, const CReadOnlyUserIDType& UserID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use COrderInsertFailedIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.ExchangeID=ExchangeID.getValue();
	m_compareObject.InstrumentID=InstrumentID.getValue();
	m_compareObject.UserID=UserID.getValue();

}

COrderInsertFailedIteratorAllByExchIDInstruIDUserID *COrderInsertFailedIteratorAllByExchIDInstruIDUserID::alloc(COrderInsertFailedFactory *pFactory
		, const CReadOnlyExchangeIDType& ExchangeID, const CReadOnlyInstrumentIDType& InstrumentID, const CReadOnlyUserIDType& UserID)
{
	COrderInsertFailedIteratorAllByExchIDInstruIDUserID *it;
	it=iteratorList.alloc();
	it->init(pFactory,ExchangeID,InstrumentID,UserID);
	return it;
}

COrderInsertFailedIteratorAllByExchIDInstruIDUserID::~COrderInsertFailedIteratorAllByExchIDInstruIDUserID(void)
{
	m_Factory->endGet();
}

void COrderInsertFailedIteratorAllByExchIDInstruIDUserID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void COrderInsertFailedIteratorAllByExchIDInstruIDUserID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"COrderInsertFailedIteratorAllByExchIDInstruIDUserID");
	
	char buffer[200];
	
	m_compareObject.ExchangeID.getString(buffer);
	pLogger->output(indent+1,0,"query ExchangeID=%s",buffer);
	
	m_compareObject.InstrumentID.getString(buffer);
	pLogger->output(indent+1,0,"query InstrumentID=%s",buffer);
	
	m_compareObject.UserID.getString(buffer);
	pLogger->output(indent+1,0,"query UserID=%s",buffer);
	
}

void COrderInsertFailedIteratorAllByExchIDInstruIDUserID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(COrderInsertFailed *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(COrderInsertFailed *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void COrderInsertFailedIteratorAllByExchIDInstruIDUserID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void COrderInsertFailedIteratorAllByExchIDInstruIDUserID::UpdateCurrent(CWriteableOrderInsertFailed * pAllByExchIDInstruIDUserID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByExchIDInstruIDUserID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByExchIDInstruIDUserIDForOrderInsertFailed;
#endif

COrderInsertFailed *COrderInsertFailedIteratorAllByExchIDInstruIDUserID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int COrderInsertFailedIteratorAllByExchIDInstruIDUserID::match(COrderInsertFailed *pOrderInsertFailed)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pOrderInsertFailed->ExchangeID.getValue(),m_compareObject.ExchangeID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pOrderInsertFailed->UserID.getValue(),m_compareObject.UserID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}

CMemoryStack<COrderInsertFailedIteratorAll> COrderInsertFailedIteratorAll::iteratorList;
void COrderInsertFailedIteratorAll::init(COrderInsertFailedFactory *pFactory
		)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use COrderInsertFailedIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();

}

COrderInsertFailedIteratorAll *COrderInsertFailedIteratorAll::alloc(COrderInsertFailedFactory *pFactory
		)
{
	COrderInsertFailedIteratorAll *it;
	it=iteratorList.alloc();
	it->init(pFactory);
	return it;
}

COrderInsertFailedIteratorAll::~COrderInsertFailedIteratorAll(void)
{
	m_Factory->endGet();
}

void COrderInsertFailedIteratorAll::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void COrderInsertFailedIteratorAll::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"COrderInsertFailedIteratorAll");
	
	
}

void COrderInsertFailedIteratorAll::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(COrderInsertFailed *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(COrderInsertFailed *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void COrderInsertFailedIteratorAll::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void COrderInsertFailedIteratorAll::UpdateCurrent(CWriteableOrderInsertFailed * pAll,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAll,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllForOrderInsertFailed;
#endif

COrderInsertFailed *COrderInsertFailedIteratorAll::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int COrderInsertFailedIteratorAll::match(COrderInsertFailed *pOrderInsertFailed)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}




CMemoryStack<CUserSessionIteratorByUserID> CUserSessionIteratorByUserID::iteratorList;
void CUserSessionIteratorByUserID::init(CUserSessionFactory *pFactory
		, const CReadOnlyUserIDType& UserID)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CUserSessionIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.UserID=UserID.getValue();

}

CUserSessionIteratorByUserID *CUserSessionIteratorByUserID::alloc(CUserSessionFactory *pFactory
		, const CReadOnlyUserIDType& UserID)
{
	CUserSessionIteratorByUserID *it;
	it=iteratorList.alloc();
	it->init(pFactory,UserID);
	return it;
}

CUserSessionIteratorByUserID::~CUserSessionIteratorByUserID(void)
{
}

void CUserSessionIteratorByUserID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CUserSessionIteratorByUserID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CUserSessionIteratorByUserID");
	
	char buffer[200];
	
	m_compareObject.UserID.getString(buffer);
	pLogger->output(indent+1,0,"query UserID=%s",buffer);
	
}

void CUserSessionIteratorByUserID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pUserIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pUserIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CUserSessionIteratorByUserID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CUserSession *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CUserSessionIteratorByUserID::UpdateCurrent(CWriteableUserSession * pByUserID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CUserSession *)(m_pCurrent->pObject),pByUserID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindByUserIDForUserSession;
#endif

CUserSession *CUserSessionIteratorByUserID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindByUserIDForUserSession++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CUserSession *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CUserSession *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CUserSessionIteratorByUserID::match(CUserSession *pUserSession)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pUserSession->UserID.getValue(),m_compareObject.UserID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}







CMemoryStack<CSGEDeferRateIteratorAllByInstrumentID> CSGEDeferRateIteratorAllByInstrumentID::iteratorList;
void CSGEDeferRateIteratorAllByInstrumentID::init(CSGEDeferRateFactory *pFactory
		, const CReadOnlyInstrumentIDType& InstrumentID)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CSGEDeferRateIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.InstrumentID=InstrumentID.getValue();

}

CSGEDeferRateIteratorAllByInstrumentID *CSGEDeferRateIteratorAllByInstrumentID::alloc(CSGEDeferRateFactory *pFactory
		, const CReadOnlyInstrumentIDType& InstrumentID)
{
	CSGEDeferRateIteratorAllByInstrumentID *it;
	it=iteratorList.alloc();
	it->init(pFactory,InstrumentID);
	return it;
}

CSGEDeferRateIteratorAllByInstrumentID::~CSGEDeferRateIteratorAllByInstrumentID(void)
{
	m_Factory->endGet();
}

void CSGEDeferRateIteratorAllByInstrumentID::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CSGEDeferRateIteratorAllByInstrumentID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CSGEDeferRateIteratorAllByInstrumentID");
	
	char buffer[200];
	
	m_compareObject.InstrumentID.getString(buffer);
	pLogger->output(indent+1,0,"query InstrumentID=%s",buffer);
	
}

void CSGEDeferRateIteratorAllByInstrumentID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CSGEDeferRate *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CSGEDeferRate *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CSGEDeferRateIteratorAllByInstrumentID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CSGEDeferRateIteratorAllByInstrumentID::UpdateCurrent(CWriteableSGEDeferRate * pAllByInstrumentID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAllByInstrumentID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllByInstrumentIDForSGEDeferRate;
#endif

CSGEDeferRate *CSGEDeferRateIteratorAllByInstrumentID::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CSGEDeferRateIteratorAllByInstrumentID::match(CSGEDeferRate *pSGEDeferRate)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}

CMemoryStack<CSGEDeferRateIteratorAll> CSGEDeferRateIteratorAll::iteratorList;
void CSGEDeferRateIteratorAll::init(CSGEDeferRateFactory *pFactory
		)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CSGEDeferRateIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();

}

CSGEDeferRateIteratorAll *CSGEDeferRateIteratorAll::alloc(CSGEDeferRateFactory *pFactory
		)
{
	CSGEDeferRateIteratorAll *it;
	it=iteratorList.alloc();
	it->init(pFactory);
	return it;
}

CSGEDeferRateIteratorAll::~CSGEDeferRateIteratorAll(void)
{
	m_Factory->endGet();
}

void CSGEDeferRateIteratorAll::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CSGEDeferRateIteratorAll::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CSGEDeferRateIteratorAll");
	
	
}

void CSGEDeferRateIteratorAll::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CSGEDeferRate *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CSGEDeferRate *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CSGEDeferRateIteratorAll::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CSGEDeferRateIteratorAll::UpdateCurrent(CWriteableSGEDeferRate * pAll,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAll,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllForSGEDeferRate;
#endif

CSGEDeferRate *CSGEDeferRateIteratorAll::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CSGEDeferRateIteratorAll::match(CSGEDeferRate *pSGEDeferRate)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}



CMemoryStack<CUserIPIteratorByUserID> CUserIPIteratorByUserID::iteratorList;
void CUserIPIteratorByUserID::init(CUserIPFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID, const CReadOnlyUserIDType& UserID)
{
	if (runLevel<0)
	{
		RAISE_RUNTIME_ERROR("Can not use CUserIPIterator while run level < 0");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	m_compareObject.BrokerID=BrokerID.getValue();
	m_compareObject.UserID=UserID.getValue();
	m_compareObject.IPAddress="";
	m_compareObject.IPMask="";

}

CUserIPIteratorByUserID *CUserIPIteratorByUserID::alloc(CUserIPFactory *pFactory
		, const CReadOnlyBrokerIDType& BrokerID, const CReadOnlyUserIDType& UserID)
{
	CUserIPIteratorByUserID *it;
	it=iteratorList.alloc();
	it->init(pFactory,BrokerID,UserID);
	return it;
}

CUserIPIteratorByUserID::~CUserIPIteratorByUserID(void)
{
}

void CUserIPIteratorByUserID::free(void)
{
	iteratorList.free(this);
	delete this;
}

void CUserIPIteratorByUserID::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CUserIPIteratorByUserID");
	
	char buffer[200];
	
	m_compareObject.BrokerID.getString(buffer);
	pLogger->output(indent+1,0,"query BrokerID=%s",buffer);
	
	m_compareObject.UserID.getString(buffer);
	pLogger->output(indent+1,0,"query UserID=%s",buffer);
	
}

void CUserIPIteratorByUserID::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->pUserIPMaskIndex->searchFirstGreatEqual(&m_compareObject);

		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///在索引找下一个节点
			m_pNext=m_Factory->pUserIPMaskIndex->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
}


void CUserIPIteratorByUserID::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove((CUserIP *)(m_pCurrent->pObject),pTransaction);
	m_pCurrent=NULL;
}
	

void CUserIPIteratorByUserID::UpdateCurrent(CWriteableUserIP * pByUserID,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((CUserIP *)(m_pCurrent->pObject),pByUserID,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindByUserIDForUserIP;
#endif

CUserIP *CUserIPIteratorByUserID::next(void)
{
#ifdef COUNT_SEARCH
	multiFindByUserIDForUserIP++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((CUserIP *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (CUserIP *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
}

int CUserIPIteratorByUserID::match(CUserIP *pUserIP)
{
	///如果有一个条件不满足，则失败返回
	if (compare(pUserIP->BrokerID.getValue(),m_compareObject.BrokerID.getValue())!=0)
	{
		return 0;
	}
	if (compare(pUserIP->UserID.getValue(),m_compareObject.UserID.getValue())!=0)
	{
		return 0;
	}
	return 1;
}



CMemoryStack<CMarketDataIteratorAll> CMarketDataIteratorAll::iteratorList;
void CMarketDataIteratorAll::init(CMarketDataFactory *pFactory
		)
{
	if (runLevel<1)
	{
		RAISE_RUNTIME_ERROR("Can not use CMarketDataIterator while run level < 1");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();

}

CMarketDataIteratorAll *CMarketDataIteratorAll::alloc(CMarketDataFactory *pFactory
		)
{
	CMarketDataIteratorAll *it;
	it=iteratorList.alloc();
	it->init(pFactory);
	return it;
}

CMarketDataIteratorAll::~CMarketDataIteratorAll(void)
{
	m_Factory->endGet();
}

void CMarketDataIteratorAll::free(void)
{
	m_Factory->endGet();
	iteratorList.free(this);
	delete this;
}

void CMarketDataIteratorAll::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CMarketDataIteratorAll");
	
	
}

void CMarketDataIteratorAll::internalGetNext()
{
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(CMarketData *)(m_Factory->getFirst());
		///设置非第一次标志
		m_isFirstTime=0;
	}
	else
	{
		if (m_pCurrent==NULL)
		{
			///已经找到最后一个了
			m_pNext=NULL;
		}
		else
		{
			///找到下一个对象
			m_pNext=(CMarketData *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
}


void CMarketDataIteratorAll::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
	m_Factory->remove(m_pCurrent,pTransaction);
	m_pCurrent=NULL;
}
	

void CMarketDataIteratorAll::UpdateCurrent(CWriteableMarketData * pAll,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,pAll,pTransaction,updateIndex);
}

#ifdef COUNT_SEARCH
extern int multiFindAllForMarketData;
#endif

CMarketData *CMarketDataIteratorAll::next(void)
{
	for (;;)
	{
		internalGetNext();
		m_gotNext=false;
		m_pCurrent=m_pNext;

		///如果没有下一个对象了，则失败返回
		if (m_pCurrent==NULL)
		{
			return NULL;
		}
		
		if (match(m_pCurrent))
		{
			///符合条件，那就返回它
			return m_pCurrent;
		}
		///不符合，那就再看下一个		
	}
}

int CMarketDataIteratorAll::match(CMarketData *pMarketData)
{
	///如果有一个条件不满足，则失败返回
	return 1;
}




