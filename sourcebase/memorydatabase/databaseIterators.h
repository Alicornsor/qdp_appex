/////////////////////////////////////////////////////////////////////////
///@system ִ������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file databaseIterators.h
///@brief���������ɸ��ڴ����ݿ��iterator
///@history 
///20060127	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef DATABASEITERATORS_H
#define DATABASEITERATORS_H

#include "BaseDataStruct.h"
#include "databaseFactories.h"
#include "MemoryStack.h"




/////////////////////////////////////////////////////////////////////////
///COrderIteratorAllByUserID��һ����ί�б�ʹ��AllByUserID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderIteratorAllByUserID: public COrderIterator
{
	friend class COrderFactory;
private:
	///���˶����Ƿ���������
	///@param	pOrder		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(COrder *pOrder);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	COrder *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	COrder *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableOrder m_compareObject;
	
	static CMemoryStack<COrderIteratorAllByUserID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	UserID	�����û�����
	COrderIteratorAllByUserID(COrderFactory *pFactory
		,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,UserID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	UserID	�����û�����
	static COrderIteratorAllByUserID *alloc(COrderFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///���췽��
	COrderIteratorAllByUserID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	UserID	�����û�����
	void init(COrderFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderIteratorAllByUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������COrder��������startFindAllByUserID�Ժ�endFindAllByUserID֮ǰ����
	///@return	��һ����������COrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByUserID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrder * pAllByUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///COrderIteratorAllByInvestorID��һ����ί�б�ʹ��AllByInvestorID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderIteratorAllByInvestorID: public COrderIterator
{
	friend class COrderFactory;
private:
	///���˶����Ƿ���������
	///@param	pOrder		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(COrder *pOrder);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	COrder *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	COrder *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableOrder m_compareObject;
	
	static CMemoryStack<COrderIteratorAllByInvestorID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	Ͷ���߱��
	COrderIteratorAllByInvestorID(COrderFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,InvestorID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	Ͷ���߱��
	static COrderIteratorAllByInvestorID *alloc(COrderFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///���췽��
	COrderIteratorAllByInvestorID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	Ͷ���߱��
	void init(COrderFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderIteratorAllByInvestorID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������COrder��������startFindAllByInvestorID�Ժ�endFindAllByInvestorID֮ǰ����
	///@return	��һ����������COrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByInvestorID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrder * pAllByInvestorID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///COrderIteratorAllByExchIDInvIDUserID��һ����ί�б�ʹ��AllByExchIDInvIDUserID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderIteratorAllByExchIDInvIDUserID: public COrderIterator
{
	friend class COrderFactory;
private:
	///���˶����Ƿ���������
	///@param	pOrder		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(COrder *pOrder);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	COrder *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	COrder *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableOrder m_compareObject;
	
	static CMemoryStack<COrderIteratorAllByExchIDInvIDUserID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	UserID	�����û�����
	COrderIteratorAllByExchIDInvIDUserID(COrderFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,ExchangeID,InvestorID,UserID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	UserID	�����û�����
	static COrderIteratorAllByExchIDInvIDUserID *alloc(COrderFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID);

	///���췽��
	COrderIteratorAllByExchIDInvIDUserID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	UserID	�����û�����
	void init(COrderFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderIteratorAllByExchIDInvIDUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������COrder��������startFindAllByExchIDInvIDUserID�Ժ�endFindAllByExchIDInvIDUserID֮ǰ����
	///@return	��һ����������COrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByExchIDInvIDUserID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrder * pAllByExchIDInvIDUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///COrderIteratorAllByExchIDInstruIDUserID��һ����ί�б�ʹ��AllByExchIDInstruIDUserID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderIteratorAllByExchIDInstruIDUserID: public COrderIterator
{
	friend class COrderFactory;
private:
	///���˶����Ƿ���������
	///@param	pOrder		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(COrder *pOrder);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	COrder *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	COrder *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableOrder m_compareObject;
	
	static CMemoryStack<COrderIteratorAllByExchIDInstruIDUserID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ��
	///@param	UserID	�����û�����
	COrderIteratorAllByExchIDInstruIDUserID(COrderFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,ExchangeID,InstrumentID,UserID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ��
	///@param	UserID	�����û�����
	static COrderIteratorAllByExchIDInstruIDUserID *alloc(COrderFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID);

	///���췽��
	COrderIteratorAllByExchIDInstruIDUserID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ��
	///@param	UserID	�����û�����
	void init(COrderFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderIteratorAllByExchIDInstruIDUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������COrder��������startFindAllByExchIDInstruIDUserID�Ժ�endFindAllByExchIDInstruIDUserID֮ǰ����
	///@return	��һ����������COrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByExchIDInstruIDUserID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrder * pAllByExchIDInstruIDUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///COrderIteratorAll��һ����ί�б�ʹ��All��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderIteratorAll: public COrderIterator
{
	friend class COrderFactory;
private:
	///���˶����Ƿ���������
	///@param	pOrder		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(COrder *pOrder);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	COrder *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	COrder *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableOrder m_compareObject;
	
	static CMemoryStack<COrderIteratorAll> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	COrderIteratorAll(COrderFactory *pFactory
		)
	{
		init(pFactory);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	static COrderIteratorAll *alloc(COrderFactory *pFactory
		);

	///���췽��
	COrderIteratorAll(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	void init(COrderFactory *pFactory
		);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������COrder��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������COrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAll ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrder * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CTradeIteratorByExchangeIDAndTradeID��һ���Գɽ���ʹ��ByExchangeIDAndTradeID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeIteratorByExchangeIDAndTradeID: public CTradeIterator
{
	friend class CTradeFactory;
private:
	///���˶����Ƿ���������
	///@param	pTrade		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CTrade *pTrade);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableTrade m_compareObject;
	
	static CMemoryStack<CTradeIteratorByExchangeIDAndTradeID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	TradeID	�ɽ����
	CTradeIteratorByExchangeIDAndTradeID(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyTradeIDType& TradeID)
	{
		init(pFactory,ExchangeID,TradeID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	TradeID	�ɽ����
	static CTradeIteratorByExchangeIDAndTradeID *alloc(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyTradeIDType& TradeID);

	///���췽��
	CTradeIteratorByExchangeIDAndTradeID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	TradeID	�ɽ����
	void init(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyTradeIDType& TradeID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CTradeIteratorByExchangeIDAndTradeID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CTrade��������startFindByExchangeIDAndTradeID�Ժ�endFindByExchangeIDAndTradeID֮ǰ����
	///@return	��һ����������CTrade������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CTrade *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pByExchangeIDAndTradeID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableTrade * pByExchangeIDAndTradeID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CTradeIteratorAllByExchIDInvIDUserID��һ���Գɽ���ʹ��AllByExchIDInvIDUserID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeIteratorAllByExchIDInvIDUserID: public CTradeIterator
{
	friend class CTradeFactory;
private:
	///���˶����Ƿ���������
	///@param	pTrade		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CTrade *pTrade);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CTrade *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CTrade *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableTrade m_compareObject;
	
	static CMemoryStack<CTradeIteratorAllByExchIDInvIDUserID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	UserID	�����û�����
	CTradeIteratorAllByExchIDInvIDUserID(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,ExchangeID,InvestorID,UserID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	UserID	�����û�����
	static CTradeIteratorAllByExchIDInvIDUserID *alloc(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID);

	///���췽��
	CTradeIteratorAllByExchIDInvIDUserID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	UserID	�����û�����
	void init(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CTradeIteratorAllByExchIDInvIDUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CTrade��������startFindAllByExchIDInvIDUserID�Ժ�endFindAllByExchIDInvIDUserID֮ǰ����
	///@return	��һ����������CTrade������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CTrade *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByExchIDInvIDUserID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableTrade * pAllByExchIDInvIDUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CTradeIteratorAllByInvestorID��һ���Գɽ���ʹ��AllByInvestorID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeIteratorAllByInvestorID: public CTradeIterator
{
	friend class CTradeFactory;
private:
	///���˶����Ƿ���������
	///@param	pTrade		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CTrade *pTrade);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CTrade *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CTrade *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableTrade m_compareObject;
	
	static CMemoryStack<CTradeIteratorAllByInvestorID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	Ͷ���߱��
	CTradeIteratorAllByInvestorID(CTradeFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,InvestorID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	Ͷ���߱��
	static CTradeIteratorAllByInvestorID *alloc(CTradeFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///���췽��
	CTradeIteratorAllByInvestorID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	Ͷ���߱��
	void init(CTradeFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CTradeIteratorAllByInvestorID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CTrade��������startFindAllByInvestorID�Ժ�endFindAllByInvestorID֮ǰ����
	///@return	��һ����������CTrade������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CTrade *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByInvestorID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableTrade * pAllByInvestorID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CTradeIteratorAllByExchIDInstruIDUserID��һ���Գɽ���ʹ��AllByExchIDInstruIDUserID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeIteratorAllByExchIDInstruIDUserID: public CTradeIterator
{
	friend class CTradeFactory;
private:
	///���˶����Ƿ���������
	///@param	pTrade		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CTrade *pTrade);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CTrade *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CTrade *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableTrade m_compareObject;
	
	static CMemoryStack<CTradeIteratorAllByExchIDInstruIDUserID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ��
	///@param	UserID	�����û�����
	CTradeIteratorAllByExchIDInstruIDUserID(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,ExchangeID,InstrumentID,UserID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ��
	///@param	UserID	�����û�����
	static CTradeIteratorAllByExchIDInstruIDUserID *alloc(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID);

	///���췽��
	CTradeIteratorAllByExchIDInstruIDUserID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ��
	///@param	UserID	�����û�����
	void init(CTradeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CTradeIteratorAllByExchIDInstruIDUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CTrade��������startFindAllByExchIDInstruIDUserID�Ժ�endFindAllByExchIDInstruIDUserID֮ǰ����
	///@return	��һ����������CTrade������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CTrade *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByExchIDInstruIDUserID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableTrade * pAllByExchIDInstruIDUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CTradeIteratorAll��һ���Գɽ���ʹ��All��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeIteratorAll: public CTradeIterator
{
	friend class CTradeFactory;
private:
	///���˶����Ƿ���������
	///@param	pTrade		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CTrade *pTrade);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CTrade *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CTrade *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableTrade m_compareObject;
	
	static CMemoryStack<CTradeIteratorAll> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	CTradeIteratorAll(CTradeFactory *pFactory
		)
	{
		init(pFactory);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	static CTradeIteratorAll *alloc(CTradeFactory *pFactory
		);

	///���췽��
	CTradeIteratorAll(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	void init(CTradeFactory *pFactory
		);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CTradeIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CTrade��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CTrade������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CTrade *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAll ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableTrade * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderIteratorByAPIID��һ����Ԥί�б�ʹ��ByAPIID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderIteratorByAPIID: public CPreOrderIterator
{
	friend class CPreOrderFactory;
private:
	///���˶����Ƿ���������
	///@param	pPreOrder		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CPreOrder *pPreOrder);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteablePreOrder m_compareObject;
	
	static CMemoryStack<CPreOrderIteratorByAPIID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	APIID	ͨ����
	CPreOrderIteratorByAPIID(CPreOrderFactory *pFactory
		,const CReadOnlyNumberType& APIID)
	{
		init(pFactory,APIID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	APIID	ͨ����
	static CPreOrderIteratorByAPIID *alloc(CPreOrderFactory *pFactory
		,const CReadOnlyNumberType& APIID);

	///���췽��
	CPreOrderIteratorByAPIID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	APIID	ͨ����
	void init(CPreOrderFactory *pFactory
		,const CReadOnlyNumberType& APIID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CPreOrderIteratorByAPIID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CPreOrder��������startFindByAPIID�Ժ�endFindByAPIID֮ǰ����
	///@return	��һ����������CPreOrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CPreOrder *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pByAPIID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteablePreOrder * pByAPIID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIteratorAllByExIDAndInstrumentID��һ���Գֱֲ�ʹ��AllByExIDAndInstrumentID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIteratorAllByExIDAndInstrumentID: public CInvestorPositionIterator
{
	friend class CInvestorPositionFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorPosition		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorPosition *pInvestorPosition);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorPosition m_compareObject;
	
	static CMemoryStack<CInvestorPositionIteratorAllByExIDAndInstrumentID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ���
	CInvestorPositionIteratorAllByExIDAndInstrumentID(CInvestorPositionFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID)
	{
		init(pFactory,ExchangeID,InstrumentID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ���
	static CInvestorPositionIteratorAllByExIDAndInstrumentID *alloc(CInvestorPositionFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID);

	///���췽��
	CInvestorPositionIteratorAllByExIDAndInstrumentID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ���
	void init(CInvestorPositionFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorPositionIteratorAllByExIDAndInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorPosition��������startFindAllByExIDAndInstrumentID�Ժ�endFindAllByExIDAndInstrumentID֮ǰ����
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByExIDAndInstrumentID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorPosition * pAllByExIDAndInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIteratorByInvestorID��һ���Գֱֲ�ʹ��ByInvestorID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIteratorByInvestorID: public CInvestorPositionIterator
{
	friend class CInvestorPositionFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorPosition		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorPosition *pInvestorPosition);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorPosition m_compareObject;
	
	static CMemoryStack<CInvestorPositionIteratorByInvestorID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	Ͷ���ߺ�
	CInvestorPositionIteratorByInvestorID(CInvestorPositionFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,InvestorID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	Ͷ���ߺ�
	static CInvestorPositionIteratorByInvestorID *alloc(CInvestorPositionFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///���췽��
	CInvestorPositionIteratorByInvestorID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	Ͷ���ߺ�
	void init(CInvestorPositionFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorPositionIteratorByInvestorID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorPosition��������startFindByInvestorID�Ժ�endFindByInvestorID֮ǰ����
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pByInvestorID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorPosition * pByInvestorID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIteratorAllByBrokerID��һ���Գֱֲ�ʹ��AllByBrokerID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIteratorAllByBrokerID: public CInvestorPositionIterator
{
	friend class CInvestorPositionFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorPosition		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorPosition *pInvestorPosition);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInvestorPosition *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInvestorPosition *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorPosition m_compareObject;
	
	static CMemoryStack<CInvestorPositionIteratorAllByBrokerID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	CInvestorPositionIteratorAllByBrokerID(CInvestorPositionFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID)
	{
		init(pFactory,BrokerID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	static CInvestorPositionIteratorAllByBrokerID *alloc(CInvestorPositionFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///���췽��
	CInvestorPositionIteratorAllByBrokerID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	void init(CInvestorPositionFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorPositionIteratorAllByBrokerID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorPosition��������startFindAllByBrokerID�Ժ�endFindAllByBrokerID֮ǰ����
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByBrokerID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorPosition * pAllByBrokerID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIteratorAllByInstrumentID��һ���Գֱֲ�ʹ��AllByInstrumentID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIteratorAllByInstrumentID: public CInvestorPositionIterator
{
	friend class CInvestorPositionFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorPosition		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorPosition *pInvestorPosition);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInvestorPosition *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInvestorPosition *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorPosition m_compareObject;
	
	static CMemoryStack<CInvestorPositionIteratorAllByInstrumentID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InstrumentID	��Լ����
	CInvestorPositionIteratorAllByInstrumentID(CInvestorPositionFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID)
	{
		init(pFactory,InstrumentID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InstrumentID	��Լ����
	static CInvestorPositionIteratorAllByInstrumentID *alloc(CInvestorPositionFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///���췽��
	CInvestorPositionIteratorAllByInstrumentID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InstrumentID	��Լ����
	void init(CInvestorPositionFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorPositionIteratorAllByInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorPosition��������startFindAllByInstrumentID�Ժ�endFindAllByInstrumentID֮ǰ����
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByInstrumentID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorPosition * pAllByInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIteratorAllByExchangeID��һ���Գֱֲ�ʹ��AllByExchangeID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIteratorAllByExchangeID: public CInvestorPositionIterator
{
	friend class CInvestorPositionFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorPosition		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorPosition *pInvestorPosition);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInvestorPosition *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInvestorPosition *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorPosition m_compareObject;
	
	static CMemoryStack<CInvestorPositionIteratorAllByExchangeID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	���������
	CInvestorPositionIteratorAllByExchangeID(CInvestorPositionFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID)
	{
		init(pFactory,ExchangeID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	���������
	static CInvestorPositionIteratorAllByExchangeID *alloc(CInvestorPositionFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID);

	///���췽��
	CInvestorPositionIteratorAllByExchangeID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	���������
	void init(CInvestorPositionFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorPositionIteratorAllByExchangeID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorPosition��������startFindAllByExchangeID�Ժ�endFindAllByExchangeID֮ǰ����
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByExchangeID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorPosition * pAllByExchangeID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIteratorAllByInvestorIDAndInstrumentID��һ���Գֱֲ�ʹ��AllByInvestorIDAndInstrumentID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIteratorAllByInvestorIDAndInstrumentID: public CInvestorPositionIterator
{
	friend class CInvestorPositionFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorPosition		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorPosition *pInvestorPosition);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInvestorPosition *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInvestorPosition *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorPosition m_compareObject;
	
	static CMemoryStack<CInvestorPositionIteratorAllByInvestorIDAndInstrumentID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	�ͻ���
	///@param	InstrumentID	��Լ����
	CInvestorPositionIteratorAllByInvestorIDAndInstrumentID(CInvestorPositionFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyInstrumentIDType& InstrumentID)
	{
		init(pFactory,InvestorID,InstrumentID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	�ͻ���
	///@param	InstrumentID	��Լ����
	static CInvestorPositionIteratorAllByInvestorIDAndInstrumentID *alloc(CInvestorPositionFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyInstrumentIDType& InstrumentID);

	///���췽��
	CInvestorPositionIteratorAllByInvestorIDAndInstrumentID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	�ͻ���
	///@param	InstrumentID	��Լ����
	void init(CInvestorPositionFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyInstrumentIDType& InstrumentID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorPositionIteratorAllByInvestorIDAndInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorPosition��������startFindAllByInvestorIDAndInstrumentID�Ժ�endFindAllByInvestorIDAndInstrumentID֮ǰ����
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByInvestorIDAndInstrumentID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorPosition * pAllByInvestorIDAndInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIteratorAll��һ���Գֱֲ�ʹ��All��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIteratorAll: public CInvestorPositionIterator
{
	friend class CInvestorPositionFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorPosition		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorPosition *pInvestorPosition);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInvestorPosition *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInvestorPosition *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorPosition m_compareObject;
	
	static CMemoryStack<CInvestorPositionIteratorAll> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	CInvestorPositionIteratorAll(CInvestorPositionFactory *pFactory
		)
	{
		init(pFactory);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	static CInvestorPositionIteratorAll *alloc(CInvestorPositionFactory *pFactory
		);

	///���췽��
	CInvestorPositionIteratorAll(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	void init(CInvestorPositionFactory *pFactory
		);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorPositionIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorPosition��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorPosition *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAll ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorPosition * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountIteratorAllByInvestorID��һ�����˻�ʵʱ�ʽ��ʹ��AllByInvestorID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountIteratorAllByInvestorID: public CInvestorAccountIterator
{
	friend class CInvestorAccountFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorAccount		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorAccount *pInvestorAccount);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInvestorAccount *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInvestorAccount *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorAccount m_compareObject;
	
	static CMemoryStack<CInvestorAccountIteratorAllByInvestorID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	Ͷ���߱��
	CInvestorAccountIteratorAllByInvestorID(CInvestorAccountFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,InvestorID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	Ͷ���߱��
	static CInvestorAccountIteratorAllByInvestorID *alloc(CInvestorAccountFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///���췽��
	CInvestorAccountIteratorAllByInvestorID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	Ͷ���߱��
	void init(CInvestorAccountFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorAccountIteratorAllByInvestorID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorAccount��������startFindAllByInvestorID�Ժ�endFindAllByInvestorID֮ǰ����
	///@return	��һ����������CInvestorAccount������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccount *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByInvestorID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccount * pAllByInvestorID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorAccountIteratorAllByBrokerID��һ�����˻�ʵʱ�ʽ��ʹ��AllByBrokerID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountIteratorAllByBrokerID: public CInvestorAccountIterator
{
	friend class CInvestorAccountFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorAccount		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorAccount *pInvestorAccount);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInvestorAccount *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInvestorAccount *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorAccount m_compareObject;
	
	static CMemoryStack<CInvestorAccountIteratorAllByBrokerID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	CInvestorAccountIteratorAllByBrokerID(CInvestorAccountFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID)
	{
		init(pFactory,BrokerID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	static CInvestorAccountIteratorAllByBrokerID *alloc(CInvestorAccountFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///���췽��
	CInvestorAccountIteratorAllByBrokerID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	void init(CInvestorAccountFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorAccountIteratorAllByBrokerID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorAccount��������startFindAllByBrokerID�Ժ�endFindAllByBrokerID֮ǰ����
	///@return	��һ����������CInvestorAccount������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccount *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByBrokerID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccount * pAllByBrokerID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorAccountIteratorAll��һ�����˻�ʵʱ�ʽ��ʹ��All��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountIteratorAll: public CInvestorAccountIterator
{
	friend class CInvestorAccountFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorAccount		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorAccount *pInvestorAccount);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInvestorAccount *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInvestorAccount *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorAccount m_compareObject;
	
	static CMemoryStack<CInvestorAccountIteratorAll> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	CInvestorAccountIteratorAll(CInvestorAccountFactory *pFactory
		)
	{
		init(pFactory);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	static CInvestorAccountIteratorAll *alloc(CInvestorAccountFactory *pFactory
		);

	///���췽��
	CInvestorAccountIteratorAll(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	void init(CInvestorAccountFactory *pFactory
		);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorAccountIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorAccount��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CInvestorAccount������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccount *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAll ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccount * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CExchangeIteratorStartByExchangeID��һ���Խ�������ʹ��StartByExchangeID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeIteratorStartByExchangeID: public CExchangeIterator
{
	friend class CExchangeFactory;
private:
	///���˶����Ƿ���������
	///@param	pExchange		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CExchange *pExchange);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableExchange m_compareObject;
	
	static CMemoryStack<CExchangeIteratorStartByExchangeID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	CExchangeIteratorStartByExchangeID(CExchangeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID)
	{
		init(pFactory,ExchangeID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	static CExchangeIteratorStartByExchangeID *alloc(CExchangeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID);

	///���췽��
	CExchangeIteratorStartByExchangeID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	void init(CExchangeFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CExchangeIteratorStartByExchangeID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CExchange��������startFindStartByExchangeID�Ժ�endFindStartByExchangeID֮ǰ����
	///@return	��һ����������CExchange������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CExchange *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pStartByExchangeID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableExchange * pStartByExchangeID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CExchangeIteratorAll��һ���Խ�������ʹ��All��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeIteratorAll: public CExchangeIterator
{
	friend class CExchangeFactory;
private:
	///���˶����Ƿ���������
	///@param	pExchange		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CExchange *pExchange);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CExchange *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CExchange *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableExchange m_compareObject;
	
	static CMemoryStack<CExchangeIteratorAll> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	CExchangeIteratorAll(CExchangeFactory *pFactory
		)
	{
		init(pFactory);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	static CExchangeIteratorAll *alloc(CExchangeFactory *pFactory
		);

	///���췽��
	CExchangeIteratorAll(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	void init(CExchangeFactory *pFactory
		);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CExchangeIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CExchange��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CExchange������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CExchange *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAll ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableExchange * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInstrumentIteratorAllByInstrumentID��һ�����ڻ���Լ��ʹ��AllByInstrumentID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentIteratorAllByInstrumentID: public CInstrumentIterator
{
	friend class CInstrumentFactory;
private:
	///���˶����Ƿ���������
	///@param	pInstrument		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInstrument *pInstrument);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInstrument m_compareObject;
	
	static CMemoryStack<CInstrumentIteratorAllByInstrumentID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InstrumentID	��Լ����
	CInstrumentIteratorAllByInstrumentID(CInstrumentFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID)
	{
		init(pFactory,InstrumentID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InstrumentID	��Լ����
	static CInstrumentIteratorAllByInstrumentID *alloc(CInstrumentFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///���췽��
	CInstrumentIteratorAllByInstrumentID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InstrumentID	��Լ����
	void init(CInstrumentFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInstrumentIteratorAllByInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInstrument��������startFindAllByInstrumentID�Ժ�endFindAllByInstrumentID֮ǰ����
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrument *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByInstrumentID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrument * pAllByInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInstrumentIteratorAllByExchangeID��һ�����ڻ���Լ��ʹ��AllByExchangeID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentIteratorAllByExchangeID: public CInstrumentIterator
{
	friend class CInstrumentFactory;
private:
	///���˶����Ƿ���������
	///@param	pInstrument		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInstrument *pInstrument);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInstrument *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInstrument *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInstrument m_compareObject;
	
	static CMemoryStack<CInstrumentIteratorAllByExchangeID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	���������
	CInstrumentIteratorAllByExchangeID(CInstrumentFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID)
	{
		init(pFactory,ExchangeID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	���������
	static CInstrumentIteratorAllByExchangeID *alloc(CInstrumentFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID);

	///���췽��
	CInstrumentIteratorAllByExchangeID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	���������
	void init(CInstrumentFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInstrumentIteratorAllByExchangeID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInstrument��������startFindAllByExchangeID�Ժ�endFindAllByExchangeID֮ǰ����
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrument *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByExchangeID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrument * pAllByExchangeID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInstrumentIteratorAllByProductID��һ�����ڻ���Լ��ʹ��AllByProductID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentIteratorAllByProductID: public CInstrumentIterator
{
	friend class CInstrumentFactory;
private:
	///���˶����Ƿ���������
	///@param	pInstrument		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInstrument *pInstrument);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInstrument *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInstrument *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInstrument m_compareObject;
	
	static CMemoryStack<CInstrumentIteratorAllByProductID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ProductID	��Ʒ����
	CInstrumentIteratorAllByProductID(CInstrumentFactory *pFactory
		,const CReadOnlyProductIDType& ProductID)
	{
		init(pFactory,ProductID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ProductID	��Ʒ����
	static CInstrumentIteratorAllByProductID *alloc(CInstrumentFactory *pFactory
		,const CReadOnlyProductIDType& ProductID);

	///���췽��
	CInstrumentIteratorAllByProductID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ProductID	��Ʒ����
	void init(CInstrumentFactory *pFactory
		,const CReadOnlyProductIDType& ProductID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInstrumentIteratorAllByProductID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInstrument��������startFindAllByProductID�Ժ�endFindAllByProductID֮ǰ����
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrument *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByProductID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrument * pAllByProductID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInstrumentIteratorAll��һ�����ڻ���Լ��ʹ��All��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentIteratorAll: public CInstrumentIterator
{
	friend class CInstrumentFactory;
private:
	///���˶����Ƿ���������
	///@param	pInstrument		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInstrument *pInstrument);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInstrument *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInstrument *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInstrument m_compareObject;
	
	static CMemoryStack<CInstrumentIteratorAll> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	CInstrumentIteratorAll(CInstrumentFactory *pFactory
		)
	{
		init(pFactory);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	static CInstrumentIteratorAll *alloc(CInstrumentFactory *pFactory
		);

	///���췽��
	CInstrumentIteratorAll(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	void init(CInstrumentFactory *pFactory
		);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInstrumentIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInstrument��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrument *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAll ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrument * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID��һ�����ڻ���Ϻ�Լ��ϸ��ʹ��AllByExchangeIDAndArbiInstrumentID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID: public CCmbInstrumentDetailIterator
{
	friend class CCmbInstrumentDetailFactory;
private:
	///���˶����Ƿ���������
	///@param	pCmbInstrumentDetail		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CCmbInstrumentDetail *pCmbInstrumentDetail);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableCmbInstrumentDetail m_compareObject;
	
	static CMemoryStack<CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	���������
	///@param	ArbiInstrumentID	��Ϻ�Լ���
	CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID(CCmbInstrumentDetailFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& ArbiInstrumentID)
	{
		init(pFactory,ExchangeID,ArbiInstrumentID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	���������
	///@param	ArbiInstrumentID	��Ϻ�Լ���
	static CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID *alloc(CCmbInstrumentDetailFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& ArbiInstrumentID);

	///���췽��
	CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	���������
	///@param	ArbiInstrumentID	��Ϻ�Լ���
	void init(CCmbInstrumentDetailFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& ArbiInstrumentID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CCmbInstrumentDetail��������startFindAllByExchangeIDAndArbiInstrumentID�Ժ�endFindAllByExchangeIDAndArbiInstrumentID֮ǰ����
	///@return	��һ����������CCmbInstrumentDetail������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CCmbInstrumentDetail *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByExchangeIDAndArbiInstrumentID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableCmbInstrumentDetail * pAllByExchangeIDAndArbiInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID��һ�����ڻ���Ϻ�Լ��ϸ��ʹ��AllByExchangeIDAndSingleInstrumentID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID: public CCmbInstrumentDetailIterator
{
	friend class CCmbInstrumentDetailFactory;
private:
	///���˶����Ƿ���������
	///@param	pCmbInstrumentDetail		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CCmbInstrumentDetail *pCmbInstrumentDetail);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableCmbInstrumentDetail m_compareObject;
	
	static CMemoryStack<CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	���������
	///@param	SingleInstrumentID	���Ⱥ�Լ���
	CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID(CCmbInstrumentDetailFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& SingleInstrumentID)
	{
		init(pFactory,ExchangeID,SingleInstrumentID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	���������
	///@param	SingleInstrumentID	���Ⱥ�Լ���
	static CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID *alloc(CCmbInstrumentDetailFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& SingleInstrumentID);

	///���췽��
	CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	���������
	///@param	SingleInstrumentID	���Ⱥ�Լ���
	void init(CCmbInstrumentDetailFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& SingleInstrumentID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CCmbInstrumentDetail��������startFindAllByExchangeIDAndSingleInstrumentID�Ժ�endFindAllByExchangeIDAndSingleInstrumentID֮ǰ����
	///@return	��һ����������CCmbInstrumentDetail������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CCmbInstrumentDetail *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByExchangeIDAndSingleInstrumentID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableCmbInstrumentDetail * pAllByExchangeIDAndSingleInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDIteratorByBrokerIDInvestorID��һ���Խ������ͻ������ʹ��ByBrokerIDInvestorID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDIteratorByBrokerIDInvestorID: public CClientTradingIDIterator
{
	friend class CClientTradingIDFactory;
private:
	///���˶����Ƿ���������
	///@param	pClientTradingID		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CClientTradingID *pClientTradingID);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableClientTradingID m_compareObject;
	
	static CMemoryStack<CClientTradingIDIteratorByBrokerIDInvestorID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	�����̱��
	///@param	InvestorID	�ͻ�����
	CClientTradingIDIteratorByBrokerIDInvestorID(CClientTradingIDFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,BrokerID,InvestorID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	�����̱��
	///@param	InvestorID	�ͻ�����
	static CClientTradingIDIteratorByBrokerIDInvestorID *alloc(CClientTradingIDFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyInvestorIDType& InvestorID);

	///���췽��
	CClientTradingIDIteratorByBrokerIDInvestorID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	�����̱��
	///@param	InvestorID	�ͻ�����
	void init(CClientTradingIDFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyInvestorIDType& InvestorID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CClientTradingIDIteratorByBrokerIDInvestorID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CClientTradingID��������startFindByBrokerIDInvestorID�Ժ�endFindByBrokerIDInvestorID֮ǰ����
	///@return	��һ����������CClientTradingID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CClientTradingID *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pByBrokerIDInvestorID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableClientTradingID * pByBrokerIDInvestorID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CClientTradingIDIteratorAllByBrokerID��һ���Խ������ͻ������ʹ��AllByBrokerID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDIteratorAllByBrokerID: public CClientTradingIDIterator
{
	friend class CClientTradingIDFactory;
private:
	///���˶����Ƿ���������
	///@param	pClientTradingID		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CClientTradingID *pClientTradingID);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CClientTradingID *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CClientTradingID *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableClientTradingID m_compareObject;
	
	static CMemoryStack<CClientTradingIDIteratorAllByBrokerID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	CClientTradingIDIteratorAllByBrokerID(CClientTradingIDFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID)
	{
		init(pFactory,BrokerID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	static CClientTradingIDIteratorAllByBrokerID *alloc(CClientTradingIDFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///���췽��
	CClientTradingIDIteratorAllByBrokerID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	void init(CClientTradingIDFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CClientTradingIDIteratorAllByBrokerID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CClientTradingID��������startFindAllByBrokerID�Ժ�endFindAllByBrokerID֮ǰ����
	///@return	��һ����������CClientTradingID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CClientTradingID *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByBrokerID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableClientTradingID * pAllByBrokerID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CClientTradingIDIteratorAll��һ���Խ������ͻ������ʹ��All��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDIteratorAll: public CClientTradingIDIterator
{
	friend class CClientTradingIDFactory;
private:
	///���˶����Ƿ���������
	///@param	pClientTradingID		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CClientTradingID *pClientTradingID);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CClientTradingID *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CClientTradingID *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableClientTradingID m_compareObject;
	
	static CMemoryStack<CClientTradingIDIteratorAll> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	CClientTradingIDIteratorAll(CClientTradingIDFactory *pFactory
		)
	{
		init(pFactory);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	static CClientTradingIDIteratorAll *alloc(CClientTradingIDFactory *pFactory
		);

	///���췽��
	CClientTradingIDIteratorAll(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	void init(CClientTradingIDFactory *pFactory
		);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CClientTradingIDIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CClientTradingID��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CClientTradingID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CClientTradingID *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAll ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableClientTradingID * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorIteratorByInvestorID��һ����Ͷ������Ϣ��ʹ��ByInvestorID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorIteratorByInvestorID: public CInvestorIterator
{
	friend class CInvestorFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestor		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestor *pInvestor);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestor m_compareObject;
	
	static CMemoryStack<CInvestorIteratorByInvestorID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	Ͷ���߱��
	CInvestorIteratorByInvestorID(CInvestorFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,InvestorID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	Ͷ���߱��
	static CInvestorIteratorByInvestorID *alloc(CInvestorFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///���췽��
	CInvestorIteratorByInvestorID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InvestorID	Ͷ���߱��
	void init(CInvestorFactory *pFactory
		,const CReadOnlyInvestorIDType& InvestorID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorIteratorByInvestorID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestor��������startFindByInvestorID�Ժ�endFindByInvestorID֮ǰ����
	///@return	��һ����������CInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestor *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pByInvestorID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestor * pByInvestorID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginIteratorByBrkIDExIDIstIDVstID��һ���Կͻ��ڻ���֤���ʱ�ʹ��ByBrkIDExIDIstIDVstID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginIteratorByBrkIDExIDIstIDVstID: public CInvestorMarginIterator
{
	friend class CInvestorMarginFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorMargin		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorMargin *pInvestorMargin);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorMargin m_compareObject;
	
	static CMemoryStack<CInvestorMarginIteratorByBrkIDExIDIstIDVstID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ����
	///@param	InvestorID	Ͷ���߱���
	CInvestorMarginIteratorByBrkIDExIDIstIDVstID(CInvestorMarginFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,BrokerID,ExchangeID,InstrumentID,InvestorID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ����
	///@param	InvestorID	Ͷ���߱���
	static CInvestorMarginIteratorByBrkIDExIDIstIDVstID *alloc(CInvestorMarginFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyInvestorIDType& InvestorID);

	///���췽��
	CInvestorMarginIteratorByBrkIDExIDIstIDVstID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ����
	///@param	InvestorID	Ͷ���߱���
	void init(CInvestorMarginFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyInvestorIDType& InvestorID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorMarginIteratorByBrkIDExIDIstIDVstID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorMargin��������startFindByBrkIDExIDIstIDVstID�Ժ�endFindByBrkIDExIDIstIDVstID֮ǰ����
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorMargin *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pByBrkIDExIDIstIDVstID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorMargin * pByBrkIDExIDIstIDVstID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorMarginIteratorByInstrumentID��һ���Կͻ��ڻ���֤���ʱ�ʹ��ByInstrumentID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginIteratorByInstrumentID: public CInvestorMarginIterator
{
	friend class CInvestorMarginFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorMargin		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorMargin *pInvestorMargin);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInvestorMargin *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInvestorMargin *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorMargin m_compareObject;
	
	static CMemoryStack<CInvestorMarginIteratorByInstrumentID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InstrumentID	��Լ����
	CInvestorMarginIteratorByInstrumentID(CInvestorMarginFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID)
	{
		init(pFactory,InstrumentID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InstrumentID	��Լ����
	static CInvestorMarginIteratorByInstrumentID *alloc(CInvestorMarginFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///���췽��
	CInvestorMarginIteratorByInstrumentID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InstrumentID	��Լ����
	void init(CInvestorMarginFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorMarginIteratorByInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorMargin��������startFindByInstrumentID�Ժ�endFindByInstrumentID֮ǰ����
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorMargin *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pByInstrumentID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorMargin * pByInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorMarginIteratorByBrokerID��һ���Կͻ��ڻ���֤���ʱ�ʹ��ByBrokerID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginIteratorByBrokerID: public CInvestorMarginIterator
{
	friend class CInvestorMarginFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorMargin		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorMargin *pInvestorMargin);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInvestorMargin *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInvestorMargin *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorMargin m_compareObject;
	
	static CMemoryStack<CInvestorMarginIteratorByBrokerID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	��Լ����
	CInvestorMarginIteratorByBrokerID(CInvestorMarginFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID)
	{
		init(pFactory,BrokerID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	��Լ����
	static CInvestorMarginIteratorByBrokerID *alloc(CInvestorMarginFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///���췽��
	CInvestorMarginIteratorByBrokerID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	��Լ����
	void init(CInvestorMarginFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorMarginIteratorByBrokerID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorMargin��������startFindByBrokerID�Ժ�endFindByBrokerID֮ǰ����
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorMargin *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pByBrokerID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorMargin * pByBrokerID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorMarginIteratorAll��һ���Կͻ��ڻ���֤���ʱ�ʹ��All��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginIteratorAll: public CInvestorMarginIterator
{
	friend class CInvestorMarginFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorMargin		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorMargin *pInvestorMargin);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInvestorMargin *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInvestorMargin *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorMargin m_compareObject;
	
	static CMemoryStack<CInvestorMarginIteratorAll> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	CInvestorMarginIteratorAll(CInvestorMarginFactory *pFactory
		)
	{
		init(pFactory);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	static CInvestorMarginIteratorAll *alloc(CInvestorMarginFactory *pFactory
		);

	///���췽��
	CInvestorMarginIteratorAll(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	void init(CInvestorMarginFactory *pFactory
		);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorMarginIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorMargin��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorMargin *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAll ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorMargin * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeIteratorByInstrumentID��һ���Կͻ��������ʱ�ʹ��ByInstrumentID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeIteratorByInstrumentID: public CInvestorFeeIterator
{
	friend class CInvestorFeeFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorFee		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorFee *pInvestorFee);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorFee m_compareObject;
	
	static CMemoryStack<CInvestorFeeIteratorByInstrumentID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InstrumentID	��Լ���
	CInvestorFeeIteratorByInstrumentID(CInvestorFeeFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID)
	{
		init(pFactory,InstrumentID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InstrumentID	��Լ���
	static CInvestorFeeIteratorByInstrumentID *alloc(CInvestorFeeFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///���췽��
	CInvestorFeeIteratorByInstrumentID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InstrumentID	��Լ���
	void init(CInvestorFeeFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorFeeIteratorByInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorFee��������startFindByInstrumentID�Ժ�endFindByInstrumentID֮ǰ����
	///@return	��һ����������CInvestorFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorFee *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pByInstrumentID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorFee * pByInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorFeeIteratorByBrokerID��һ���Կͻ��������ʱ�ʹ��ByBrokerID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeIteratorByBrokerID: public CInvestorFeeIterator
{
	friend class CInvestorFeeFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorFee		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorFee *pInvestorFee);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInvestorFee *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInvestorFee *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorFee m_compareObject;
	
	static CMemoryStack<CInvestorFeeIteratorByBrokerID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	��Լ���
	CInvestorFeeIteratorByBrokerID(CInvestorFeeFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID)
	{
		init(pFactory,BrokerID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	��Լ���
	static CInvestorFeeIteratorByBrokerID *alloc(CInvestorFeeFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///���췽��
	CInvestorFeeIteratorByBrokerID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	��Լ���
	void init(CInvestorFeeFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorFeeIteratorByBrokerID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorFee��������startFindByBrokerID�Ժ�endFindByBrokerID֮ǰ����
	///@return	��һ����������CInvestorFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorFee *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pByBrokerID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorFee * pByBrokerID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CInvestorFeeIteratorAll��һ���Կͻ��������ʱ�ʹ��All��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeIteratorAll: public CInvestorFeeIterator
{
	friend class CInvestorFeeFactory;
private:
	///���˶����Ƿ���������
	///@param	pInvestorFee		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CInvestorFee *pInvestorFee);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CInvestorFee *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CInvestorFee *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableInvestorFee m_compareObject;
	
	static CMemoryStack<CInvestorFeeIteratorAll> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	CInvestorFeeIteratorAll(CInvestorFeeFactory *pFactory
		)
	{
		init(pFactory);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	static CInvestorFeeIteratorAll *alloc(CInvestorFeeFactory *pFactory
		);

	///���췽��
	CInvestorFeeIteratorAll(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	void init(CInvestorFeeFactory *pFactory
		);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorFeeIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CInvestorFee��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CInvestorFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorFee *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAll ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorFee * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserIteratorStartByUserID��һ�����û���ʹ��StartByUserID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIteratorStartByUserID: public CUserIterator
{
	friend class CUserFactory;
private:
	///���˶����Ƿ���������
	///@param	pUser		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CUser *pUser);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableUser m_compareObject;
	
	static CMemoryStack<CUserIteratorStartByUserID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	UserID	�û����
	CUserIteratorStartByUserID(CUserFactory *pFactory
		,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,UserID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	UserID	�û����
	static CUserIteratorStartByUserID *alloc(CUserFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///���췽��
	CUserIteratorStartByUserID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	UserID	�û����
	void init(CUserFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserIteratorStartByUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CUser��������startFindStartByUserID�Ժ�endFindStartByUserID֮ǰ����
	///@return	��һ����������CUser������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUser *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pStartByUserID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUser * pStartByUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorIteratorByBrokerIDInvestorID��һ�����û�Ͷ���߹�ϵ��ʹ��ByBrokerIDInvestorID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorIteratorByBrokerIDInvestorID: public CUserInvestorIterator
{
	friend class CUserInvestorFactory;
private:
	///���˶����Ƿ���������
	///@param	pUserInvestor		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CUserInvestor *pUserInvestor);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableUserInvestor m_compareObject;
	
	static CMemoryStack<CUserInvestorIteratorByBrokerIDInvestorID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	///@param	InvestorID	Ͷ���߱��
	CUserInvestorIteratorByBrokerIDInvestorID(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyInvestorIDType& InvestorID)
	{
		init(pFactory,BrokerID,InvestorID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	///@param	InvestorID	Ͷ���߱��
	static CUserInvestorIteratorByBrokerIDInvestorID *alloc(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyInvestorIDType& InvestorID);

	///���췽��
	CUserInvestorIteratorByBrokerIDInvestorID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	///@param	InvestorID	Ͷ���߱��
	void init(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyInvestorIDType& InvestorID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserInvestorIteratorByBrokerIDInvestorID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CUserInvestor��������startFindByBrokerIDInvestorID�Ժ�endFindByBrokerIDInvestorID֮ǰ����
	///@return	��һ����������CUserInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserInvestor *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pByBrokerIDInvestorID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserInvestor * pByBrokerIDInvestorID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CUserInvestorIteratorAllByUserID��һ�����û�Ͷ���߹�ϵ��ʹ��AllByUserID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorIteratorAllByUserID: public CUserInvestorIterator
{
	friend class CUserInvestorFactory;
private:
	///���˶����Ƿ���������
	///@param	pUserInvestor		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CUserInvestor *pUserInvestor);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CUserInvestor *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CUserInvestor *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableUserInvestor m_compareObject;
	
	static CMemoryStack<CUserInvestorIteratorAllByUserID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	UserID	��Ա����
	CUserInvestorIteratorAllByUserID(CUserInvestorFactory *pFactory
		,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,UserID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	UserID	��Ա����
	static CUserInvestorIteratorAllByUserID *alloc(CUserInvestorFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///���췽��
	CUserInvestorIteratorAllByUserID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	UserID	��Ա����
	void init(CUserInvestorFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserInvestorIteratorAllByUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CUserInvestor��������startFindAllByUserID�Ժ�endFindAllByUserID֮ǰ����
	///@return	��һ����������CUserInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserInvestor *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByUserID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserInvestor * pAllByUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CUserInvestorIteratorAllByBrokerIDUserID��һ�����û�Ͷ���߹�ϵ��ʹ��AllByBrokerIDUserID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorIteratorAllByBrokerIDUserID: public CUserInvestorIterator
{
	friend class CUserInvestorFactory;
private:
	///���˶����Ƿ���������
	///@param	pUserInvestor		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CUserInvestor *pUserInvestor);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CUserInvestor *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CUserInvestor *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableUserInvestor m_compareObject;
	
	static CMemoryStack<CUserInvestorIteratorAllByBrokerIDUserID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	///@param	UserID	��Ա����
	CUserInvestorIteratorAllByBrokerIDUserID(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,BrokerID,UserID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	///@param	UserID	��Ա����
	static CUserInvestorIteratorAllByBrokerIDUserID *alloc(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyUserIDType& UserID);

	///���췽��
	CUserInvestorIteratorAllByBrokerIDUserID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	///@param	UserID	��Ա����
	void init(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyUserIDType& UserID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserInvestorIteratorAllByBrokerIDUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CUserInvestor��������startFindAllByBrokerIDUserID�Ժ�endFindAllByBrokerIDUserID֮ǰ����
	///@return	��һ����������CUserInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserInvestor *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByBrokerIDUserID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserInvestor * pAllByBrokerIDUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CUserInvestorIteratorAllByBrokerID��һ�����û�Ͷ���߹�ϵ��ʹ��AllByBrokerID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorIteratorAllByBrokerID: public CUserInvestorIterator
{
	friend class CUserInvestorFactory;
private:
	///���˶����Ƿ���������
	///@param	pUserInvestor		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CUserInvestor *pUserInvestor);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CUserInvestor *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CUserInvestor *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableUserInvestor m_compareObject;
	
	static CMemoryStack<CUserInvestorIteratorAllByBrokerID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	CUserInvestorIteratorAllByBrokerID(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID)
	{
		init(pFactory,BrokerID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	static CUserInvestorIteratorAllByBrokerID *alloc(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///���췽��
	CUserInvestorIteratorAllByBrokerID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	void init(CUserInvestorFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserInvestorIteratorAllByBrokerID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CUserInvestor��������startFindAllByBrokerID�Ժ�endFindAllByBrokerID֮ǰ����
	///@return	��һ����������CUserInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserInvestor *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByBrokerID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserInvestor * pAllByBrokerID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CUserInvestorIteratorAll��һ�����û�Ͷ���߹�ϵ��ʹ��All��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorIteratorAll: public CUserInvestorIterator
{
	friend class CUserInvestorFactory;
private:
	///���˶����Ƿ���������
	///@param	pUserInvestor		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CUserInvestor *pUserInvestor);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CUserInvestor *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CUserInvestor *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableUserInvestor m_compareObject;
	
	static CMemoryStack<CUserInvestorIteratorAll> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	CUserInvestorIteratorAll(CUserInvestorFactory *pFactory
		)
	{
		init(pFactory);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	static CUserInvestorIteratorAll *alloc(CUserInvestorFactory *pFactory
		);

	///���췽��
	CUserInvestorIteratorAll(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	void init(CUserInvestorFactory *pFactory
		);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserInvestorIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CUserInvestor��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CUserInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserInvestor *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAll ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserInvestor * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedIteratorAllByExchIDInvIDUserID��һ���Դ���ʹ��AllByExchIDInvIDUserID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedIteratorAllByExchIDInvIDUserID: public COrderInsertFailedIterator
{
	friend class COrderInsertFailedFactory;
private:
	///���˶����Ƿ���������
	///@param	pOrderInsertFailed		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(COrderInsertFailed *pOrderInsertFailed);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	COrderInsertFailed *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	COrderInsertFailed *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableOrderInsertFailed m_compareObject;
	
	static CMemoryStack<COrderInsertFailedIteratorAllByExchIDInvIDUserID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	UserID	�����û�����
	COrderInsertFailedIteratorAllByExchIDInvIDUserID(COrderInsertFailedFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,ExchangeID,InvestorID,UserID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	UserID	�����û�����
	static COrderInsertFailedIteratorAllByExchIDInvIDUserID *alloc(COrderInsertFailedFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID);

	///���췽��
	COrderInsertFailedIteratorAllByExchIDInvIDUserID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	UserID	�����û�����
	void init(COrderInsertFailedFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInvestorIDType& InvestorID,const CReadOnlyUserIDType& UserID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderInsertFailedIteratorAllByExchIDInvIDUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������COrderInsertFailed��������startFindAllByExchIDInvIDUserID�Ժ�endFindAllByExchIDInvIDUserID֮ǰ����
	///@return	��һ����������COrderInsertFailed������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrderInsertFailed *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByExchIDInvIDUserID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrderInsertFailed * pAllByExchIDInvIDUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedIteratorAllByExchIDInstruIDUserID��һ���Դ���ʹ��AllByExchIDInstruIDUserID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedIteratorAllByExchIDInstruIDUserID: public COrderInsertFailedIterator
{
	friend class COrderInsertFailedFactory;
private:
	///���˶����Ƿ���������
	///@param	pOrderInsertFailed		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(COrderInsertFailed *pOrderInsertFailed);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	COrderInsertFailed *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	COrderInsertFailed *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableOrderInsertFailed m_compareObject;
	
	static CMemoryStack<COrderInsertFailedIteratorAllByExchIDInstruIDUserID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ��
	///@param	UserID	�����û�����
	COrderInsertFailedIteratorAllByExchIDInstruIDUserID(COrderInsertFailedFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,ExchangeID,InstrumentID,UserID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ��
	///@param	UserID	�����û�����
	static COrderInsertFailedIteratorAllByExchIDInstruIDUserID *alloc(COrderInsertFailedFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID);

	///���췽��
	COrderInsertFailedIteratorAllByExchIDInstruIDUserID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ��
	///@param	UserID	�����û�����
	void init(COrderInsertFailedFactory *pFactory
		,const CReadOnlyExchangeIDType& ExchangeID,const CReadOnlyInstrumentIDType& InstrumentID,const CReadOnlyUserIDType& UserID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderInsertFailedIteratorAllByExchIDInstruIDUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������COrderInsertFailed��������startFindAllByExchIDInstruIDUserID�Ժ�endFindAllByExchIDInstruIDUserID֮ǰ����
	///@return	��һ����������COrderInsertFailed������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrderInsertFailed *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByExchIDInstruIDUserID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrderInsertFailed * pAllByExchIDInstruIDUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedIteratorAll��һ���Դ���ʹ��All��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedIteratorAll: public COrderInsertFailedIterator
{
	friend class COrderInsertFailedFactory;
private:
	///���˶����Ƿ���������
	///@param	pOrderInsertFailed		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(COrderInsertFailed *pOrderInsertFailed);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	COrderInsertFailed *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	COrderInsertFailed *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableOrderInsertFailed m_compareObject;
	
	static CMemoryStack<COrderInsertFailedIteratorAll> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	COrderInsertFailedIteratorAll(COrderInsertFailedFactory *pFactory
		)
	{
		init(pFactory);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	static COrderInsertFailedIteratorAll *alloc(COrderInsertFailedFactory *pFactory
		);

	///���췽��
	COrderInsertFailedIteratorAll(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	void init(COrderInsertFailedFactory *pFactory
		);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderInsertFailedIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������COrderInsertFailed��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������COrderInsertFailed������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrderInsertFailed *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAll ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrderInsertFailed * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};



/////////////////////////////////////////////////////////////////////////
///CUserSessionIteratorByUserID��һ���Խ���Ա���߻Ựʹ��ByUserID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionIteratorByUserID: public CUserSessionIterator
{
	friend class CUserSessionFactory;
private:
	///���˶����Ƿ���������
	///@param	pUserSession		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CUserSession *pUserSession);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableUserSession m_compareObject;
	
	static CMemoryStack<CUserSessionIteratorByUserID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	UserID	�û���
	CUserSessionIteratorByUserID(CUserSessionFactory *pFactory
		,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,UserID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	UserID	�û���
	static CUserSessionIteratorByUserID *alloc(CUserSessionFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///���췽��
	CUserSessionIteratorByUserID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	UserID	�û���
	void init(CUserSessionFactory *pFactory
		,const CReadOnlyUserIDType& UserID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserSessionIteratorByUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CUserSession��������startFindByUserID�Ժ�endFindByUserID֮ǰ����
	///@return	��һ����������CUserSession������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserSession *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pByUserID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserSession * pByUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};






/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateIteratorAllByInstrumentID��һ���Խ������ӷ��ʱ�ʹ��AllByInstrumentID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateIteratorAllByInstrumentID: public CSGEDeferRateIterator
{
	friend class CSGEDeferRateFactory;
private:
	///���˶����Ƿ���������
	///@param	pSGEDeferRate		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CSGEDeferRate *pSGEDeferRate);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CSGEDeferRate *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CSGEDeferRate *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableSGEDeferRate m_compareObject;
	
	static CMemoryStack<CSGEDeferRateIteratorAllByInstrumentID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InstrumentID	��Լ����
	CSGEDeferRateIteratorAllByInstrumentID(CSGEDeferRateFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID)
	{
		init(pFactory,InstrumentID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InstrumentID	��Լ����
	static CSGEDeferRateIteratorAllByInstrumentID *alloc(CSGEDeferRateFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///���췽��
	CSGEDeferRateIteratorAllByInstrumentID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	InstrumentID	��Լ����
	void init(CSGEDeferRateFactory *pFactory
		,const CReadOnlyInstrumentIDType& InstrumentID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CSGEDeferRateIteratorAllByInstrumentID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CSGEDeferRate��������startFindAllByInstrumentID�Ժ�endFindAllByInstrumentID֮ǰ����
	///@return	��һ����������CSGEDeferRate������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSGEDeferRate *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAllByInstrumentID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSGEDeferRate * pAllByInstrumentID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};
/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateIteratorAll��һ���Խ������ӷ��ʱ�ʹ��All��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateIteratorAll: public CSGEDeferRateIterator
{
	friend class CSGEDeferRateFactory;
private:
	///���˶����Ƿ���������
	///@param	pSGEDeferRate		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CSGEDeferRate *pSGEDeferRate);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CSGEDeferRate *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CSGEDeferRate *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableSGEDeferRate m_compareObject;
	
	static CMemoryStack<CSGEDeferRateIteratorAll> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	CSGEDeferRateIteratorAll(CSGEDeferRateFactory *pFactory
		)
	{
		init(pFactory);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	static CSGEDeferRateIteratorAll *alloc(CSGEDeferRateFactory *pFactory
		);

	///���췽��
	CSGEDeferRateIteratorAll(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	void init(CSGEDeferRateFactory *pFactory
		);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CSGEDeferRateIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CSGEDeferRate��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CSGEDeferRate������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSGEDeferRate *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAll ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSGEDeferRate * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CUserIPIteratorByUserID��һ���Խ���ԱIP��ַʹ��ByUserID��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPIteratorByUserID: public CUserIPIterator
{
	friend class CUserIPFactory;
private:
	///���˶����Ƿ���������
	///@param	pUserIP		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CUserIP *pUserIP);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��������ڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CAVLNode *m_pCurrent;

	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ��Ӧ�������ڵ㣬���������������
	CAVLNode *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableUserIP m_compareObject;
	
	static CMemoryStack<CUserIPIteratorByUserID> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	///@param	UserID	�û����
	CUserIPIteratorByUserID(CUserIPFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyUserIDType& UserID)
	{
		init(pFactory,BrokerID,UserID);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	///@param	UserID	�û����
	static CUserIPIteratorByUserID *alloc(CUserIPFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyUserIDType& UserID);

	///���췽��
	CUserIPIteratorByUserID(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	///@param	BrokerID	���͹�˾����
	///@param	UserID	�û����
	void init(CUserIPFactory *pFactory
		,const CReadOnlyBrokerIDType& BrokerID,const CReadOnlyUserIDType& UserID);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserIPIteratorByUserID(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CUserIP��������startFindByUserID�Ժ�endFindByUserID֮ǰ����
	///@return	��һ����������CUserIP������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserIP *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pByUserID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserIP * pByUserID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CMarketDataIteratorAll��һ����ʵʱ�����ʹ��All��������
///���ҵ�ö����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataIteratorAll: public CMarketDataIterator
{
	friend class CMarketDataFactory;
private:
	///���˶����Ƿ���������
	///@param	pMarketData		Ҫ�����Ķ���
	///@return	1��ʾ����������0��ʾ����������
	int match(CMarketData *pMarketData);

	///����Ҫ������£���ȡ��һ��ֵ��������ǵ�һ�Σ����һ�û��ȡ����һ��ֵ��
	///��ô�ͱ��뱣֤����ʱm_pCurrentָ����ȷ��ֵ�����򱾷����Ľ����ȷ��
	void internalGetNext(void);

	///�Ƿ��ǵ�һ�β�ѯ
	int m_isFirstTime;
	
	///�Ƿ��Ѿ�ȡ����һ������
	bool m_gotNext;

	///�洢���һ���ҵ��Ľڵ�
	///��m_isFirstTimeΪ1ʱ�����߷�����DeleteCurrentʱ����ֵ������
	CMarketData *m_pCurrent;
	
	///��m_gotNextΪtrueʱ����ֵ��һ��nextʱ�Ŀ�ʼѰ�ҵĽڵ㣬���������������
	CMarketData *m_pNext;

	///���ڴ洢��ѯ�����Ķ���
	CWriteableMarketData m_compareObject;
	
	static CMemoryStack<CMarketDataIteratorAll> iteratorList;
public:
	///���췽��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	CMarketDataIteratorAll(CMarketDataFactory *pFactory
		)
	{
		init(pFactory);
	}

	///����һ���µĶ���
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	static CMarketDataIteratorAll *alloc(CMarketDataFactory *pFactory
		);

	///���췽��
	CMarketDataIteratorAll(void)
	{
	}

	///��ʼ��
	///@param	pFactory	Ҫ���ҵĶ��󹤳�
	void init(CMarketDataFactory *pFactory
		);

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CMarketDataIteratorAll(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///Ѱ����һ������������CMarketData��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CMarketData������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CMarketData *next(void);
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pAll ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableMarketData * pAll,CTransaction *pTransaction = NULL, bool updateIndex=true);
};



#endif
