!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseIteratorRepository.cpp
///@brief	实现了若干个内存数据库的iterator库，以便各种查询
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "databaseIteratorRepository.h"

!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!let tableName=@name!!
C!!@tableName!! *C!!@tableName!!SingleIterator::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	m_finished=true;
	return m_pResult;
}
	
void C!!@tableName!!SingleIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->remove(m_pResult,pTransaction);
}
	
void C!!@tableName!!SingleIterator::UpdateCurrent(CWriteable!!@tableName!! * p!!@name!!,CTransaction *pTransaction, bool updateIndex)
{
	if ((m_finished)||(m_pResult==NULL))
	{
		RAISE_RUNTIME_ERROR("Delete NULL record");
	}
	m_Factory->update(m_pResult,p!!@name!!,pTransaction,updateIndex);
}

C!!@tableName!! *C!!@tableName!!Filter::next(void)
{
	if (m_finished)
	{
		return NULL;
	}
	for (;;)
	{
		C!!@tableName!! *pResult;
		pResult=m_baseIterator->next();
		if (pResult==NULL)
		{
			m_finished=true;
			return NULL;
		}
		if (m_predict->isValid(pResult))
		{
			return pResult;
		}
		if (m_continueResult)
		{
			m_finished=true;
			return NULL;
		}
	}
}
	
void C!!@tableName!!Filter::DeleteCurrent(CTransaction *pTransaction)
{
	m_baseIterator->DeleteCurrent(pTransaction);
}
	
void C!!@tableName!!Filter::UpdateCurrent(CWriteable!!@tableName!! * p!!@name!!,CTransaction *pTransaction, bool updateIndex)
{
	m_baseIterator->UpdateCurrent(p!!@name!!,pTransaction,updateIndex);
}

C!!@tableName!! *C!!@tableName!!LinkIterator::next(void)
{
	for (;m_id<2;m_id++)
	{
		for (;;)
		{
			C!!@tableName!! *pResult;
			pResult=m_baseIterator[m_id]->next();
			if (pResult==NULL)
			{
				break;
			}
			return pResult;
		}
	}
	return NULL;
}
	
void C!!@tableName!!LinkIterator::DeleteCurrent(CTransaction *pTransaction)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->DeleteCurrent(pTransaction);
}
	
void C!!@tableName!!LinkIterator::UpdateCurrent(CWriteable!!@tableName!! * p!!@name!!,CTransaction *pTransaction, bool updateIndex)
{
	if (m_id>=2)
	{
		RAISE_RUNTIME_ERROR("Delete Empty");
	}
	m_baseIterator[m_id]->UpdateCurrent(p!!@name!!,pTransaction,updateIndex);
}

!!travel foreigns!!
!!let foreignName=@name!!
C!!@factory!! *C!!@foreignName!!Of!!@tableName!!Iterator::next(void)
{
	C!!@tableName!! *p!!@tableName!!;
	while ((p!!@tableName!!=m_baseIterator->next())!=NULL)
	{
		m_current=p!!@tableName!!->get!!@foreignName!!();
		if (m_current!=NULL)
		{
			return m_current;
		}
	}
	return NULL;
}
	
void C!!@foreignName!!Of!!@tableName!!Iterator::DeleteCurrent(CTransaction *pTransaction)
{
	m_Factory->remove(m_current,pTransaction);
}
	
void C!!@foreignName!!Of!!@tableName!!Iterator::UpdateCurrent(CWriteable!!@factory!! *p!!@factory!!,CTransaction *pTransaction, bool updateIndex)
{
	m_Factory->update(m_current,p!!@factory!!,pTransaction,updateIndex);
}

!!next!!!!endif!!
!!next!!
!!leave!!
