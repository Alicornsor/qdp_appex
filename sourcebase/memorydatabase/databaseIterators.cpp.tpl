!!include function.tpl!!
!!enter system!!
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

!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!command resetEntityMap();!!
!!travel fields!!
!!command addEntity(@name,@type)!!
!!next!!	
!!let tableName=@name!!
!!travel search!!
!!if (strcmp(@searchUnique,"yes"))!!
CMemoryStack<C!!@tableName!!Iterator!!@name!!> C!!@tableName!!Iterator!!@name!!::iteratorList;
!!++!!
C!!@tableName!!Iterator!!@name!!::C!!@tableName!!Iterator!!@name!!(C!!@tableName!!Factory *pFactory
		!!travel parameter!!, const !!command getReadOnlyEntityTypeName(@name);!!!!show_string (char *)strResult.c_str()!!& !!@name!!!!next!!)
{
	init(pFactory!!travel parameter!!,!!@name!!!!next!!);
}
!!--!!
!!if valid_name("hashIndexName")!!
	!!let thisHashIndexName=@hashIndexName!!
	!!enter tables!!
		!!enter_expr @tableName!!
			!!enter hashindex!!
				!!enter_expr @thisHashIndexName!!
					!!let thisHashKey=@hashKey!!
				!!leave!!
			!!leave!!
		!!leave!!
	!!leave!!
!!endif!!
void C!!@tableName!!Iterator!!@name!!::init(C!!@tableName!!Factory *pFactory
		!!travel parameter!!, const !!command getReadOnlyEntityTypeName(@name);!!!!show_string (char *)strResult.c_str()!!& !!@name!!!!next!!)
{
	if (runLevel<!!@runLevel!!)
	{
		RAISE_RUNTIME_ERROR("Can not use C!!@tableName!!Iterator while run level < !!@runLevel!!");
	}
	m_Factory=pFactory;
	m_isFirstTime=1;
	m_gotNext=false;
	m_pCurrent=NULL;
	m_pNext=NULL;

	///根据参数和缺省值，设置用于比较的对象的各个分量
	m_compareObject.init();
	!!travel parameter!!
	m_compareObject.!!@name!!=!!@name!!.getValue();
	!!next!!
	!!travel default!!
	m_compareObject.!!@name!!=!!@value!!;
	!!next!!

	!!if valid_name("hashIndexName")!!
	m_compareObject.calHash!!@thisHashKey!!();
	!!endif!!
}

C!!@tableName!!Iterator!!@name!! *C!!@tableName!!Iterator!!@name!!::alloc(C!!@tableName!!Factory *pFactory
		!!travel parameter!!, const !!command getReadOnlyEntityTypeName(@name);!!!!show_string (char *)strResult.c_str()!!& !!@name!!!!next!!)
{
	C!!@tableName!!Iterator!!@name!! *it;
	it=iteratorList.alloc();
	it->init(pFactory!!travel parameter!!,!!@name!!!!next!!);
	return it;
}

C!!@tableName!!Iterator!!@name!!::~C!!@tableName!!Iterator!!@name!!(void)
{
	!!if !strcmp(@indexName,"noIndex")!!
	m_Factory->endGet();
	!!endif!!
}

void C!!@tableName!!Iterator!!@name!!::free(void)
{
	!!if (strcmp(@indexName,"noIndex"))!!
	!!elseif valid_name("hashIndexName")!!
	!!else!!
	m_Factory->endGet();
	!!endif!!
	iteratorList.free(this);
	delete this;
}

void C!!@tableName!!Iterator!!@name!!::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"C!!@tableName!!Iterator!!@name!!");
	
	!!if atoi(@parameter.son_size)>0!!
	char buffer[200];
	!!endif!!
	
	!!travel parameter!!
	m_compareObject.!!@name!!.getString(buffer);
	pLogger->output(indent+1,0,"query !!@name!!=%s",buffer);
	
	!!next!!
}

void C!!@tableName!!Iterator!!@name!!::internalGetNext()
{
!!if (strcmp(@indexName,"noIndex"))!!
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->p!!@indexName!!->searchFirstGreatEqual(&m_compareObject);

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
			m_pNext=m_Factory->p!!@indexName!!->getNextNode(m_pCurrent);
		}
	}
	m_gotNext=true;
!!elseif valid_name("hashIndexName")!!
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///第一次进入，在索引中寻找第一个满足条件的
		m_pNext=m_Factory->p!!@hashIndexName!!->searchFirstEqual(m_compareObject.Hash!!@thisHashKey!!);

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
			m_pNext=m_Factory->p!!@hashIndexName!!->searchNextEqual(m_pCurrent);
		}
	}
	m_gotNext=true;
!!else
	if (m_gotNext)
	{
		///已经取过下一个了
		return;
	}
	if (m_isFirstTime)
	{
		///找到第一个对象
		m_pNext=(C!!@tableName!! *)(m_Factory->getFirst());
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
			m_pNext=(C!!@tableName!! *)(m_Factory->getNext());
		}
	}
	m_gotNext=true;
!!endif!!
}


void C!!@tableName!!Iterator!!@name!!::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法删除
		return;
	}
	internalGetNext();
!!if (strcmp(@indexName,"noIndex"))!!
	m_Factory->remove((C!!@tableName!! *)(m_pCurrent->pObject),pTransaction);
!!elseif valid_name("hashIndexName")!!
	m_Factory->remove((C!!@tableName!! *)(m_pCurrent->pObject),pTransaction);
!!else!!
	m_Factory->remove(m_pCurrent,pTransaction);
!!endif!!
	m_pCurrent=NULL;
}
	

void C!!@tableName!!Iterator!!@name!!::UpdateCurrent(CWriteable!!@tableName!! * p!!@name!!,CTransaction* pTransaction, bool updateIndex)
{
	if (m_pCurrent==NULL)
	{
		///当前节点不存在，所以也无法修改
		return;
	}
!!if (strcmp(@indexName,"noIndex"))!!
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((C!!@tableName!! *)(m_pCurrent->pObject),p!!@name!!,pTransaction,updateIndex);
!!elseif valid_name("hashIndexName")!!
	if (updateIndex)
	{
		///要更新索引，那就必须预取下一个
		internalGetNext();
	}
	m_Factory->update((C!!@tableName!! *)(m_pCurrent->pObject),p!!@name!!,pTransaction,updateIndex);
!!else!!
	///本枚举器不需要更新索引，所以直接修改无妨
	m_Factory->update(m_pCurrent,p!!@name!!,pTransaction,updateIndex);
!!endif!!
}

#ifdef COUNT_SEARCH
extern int multiFind!!@name!!For!!@tableName!!;
#endif

C!!@tableName!! *C!!@tableName!!Iterator!!@name!!::next(void)
{
!!if (strcmp(@indexName,"noIndex"))!!
#ifdef COUNT_SEARCH
	multiFind!!@name!!For!!@tableName!!++;
#endif
	internalGetNext();
	m_gotNext = false;
	m_pCurrent=m_pNext;

	///如果没有下一个对象了，则失败返回
	if (m_pCurrent==NULL)
	{
		return NULL;
	}		

	if (match((C!!@tableName!! *)(m_pCurrent->pObject)))
	{
		///符合条件，那就返回它
		return (C!!@tableName!! *)(m_pCurrent->pObject);
	}
	
	///不符合条件，那就不用做了
	m_pCurrent=NULL;
	return NULL;
!!elseif valid_name("hashIndexName")!!
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
		
		if (match((C!!@tableName!! *)(m_pCurrent->pObject)))
		{
			///符合条件，那就返回它
			return (C!!@tableName!! *)(m_pCurrent->pObject);
		}
		///不符合，那就再看下一个		
	}
!!else!!
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
!!endif!!
}

int C!!@tableName!!Iterator!!@name!!::match(C!!@tableName!! *p!!@tableName!!)
{
	///如果有一个条件不满足，则失败返回
!!if valid_name("hashIndexName")!!
	if (p!!@tableName!!->Hash!!@thisHashKey!! != m_compareObject.Hash!!@thisHashKey!!)
	{
		return 0;
	}
!!endif!!
!!travel parameter!!
!!if !strcmp(@checkParameter,"yes")!!
	if (compare(p!!@tableName!!->!!@name!!.getValue(),m_compareObject.!!@name!!.getValue())!=0)
	{
		return 0;
	}
!!endif!!
!!next!!
!!travel default!!
!!if !strcmp(@checkDefault,"yes")!!
	if (compare(p!!@tableName!!->!!@name!!.getValue(),!!@value!!)!=0)
	{
		return 0;
	}
!!endif!!
!!next!!
	return 1;
}

!!endif!!
!!next!!

!!endif!!
!!next!!
!!leave!!
