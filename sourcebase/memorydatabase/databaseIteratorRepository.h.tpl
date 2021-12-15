!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseIteratorRepository.h
///@brief	定义了若干个内存数据库的iterator库，以便各种查询
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef DATABASEITERATORREPOSITORY_H
#define DATABASEITERATORREPOSITORY_H

#include "BaseDataStruct.h"
#include "databaseFactories.h"

!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!let tableName=@name!!
/////////////////////////////////////////////////////////////////////////
///C!!@tableName!!SingleIterator是至多返回一个!!@usage!!的枚举器
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@tableName!!SingleIterator: public C!!@tableName!!Iterator
{
private:
	C!!@tableName!! *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	C!!@tableName!!SingleIterator(C!!@tableName!!Factory *pFactory,C!!@tableName!! *pResult)
		:C!!@tableName!!Iterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~C!!@tableName!!SingleIterator(void)
	{
	}

	///寻找下一个符合条件的C!!@tableName!!
	///@return	下一个满足条件C!!@tableName!!，如果已经没有一个满足要求了，则返回NULL
	virtual C!!@tableName!! *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	p!!@name!! 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteable!!@tableName!! * p!!@name!!,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///C!!@tableName!!Predict是判断一个!!@usage!!是否符合条件的谓词
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@tableName!!Predict
{
public:
	virtual ~C!!@tableName!!Predict(){};

	///判断是否合法
	///@param	p!!@tableName!!	要被判断的!!@usage!!
	///@return	true表示合法，false表示不合法
	virtual bool isValid(C!!@tableName!! *p!!@tableName!!)=0;
};

/////////////////////////////////////////////////////////////////////////
///C!!@tableName!!AndPredict是对两个!!@usage!!谓词的与谓词
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@tableName!!AndPredict : public C!!@tableName!!Predict
{
private:
	C!!@tableName!!Predict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	C!!@tableName!!AndPredict(C!!@tableName!!Predict *p1, C!!@tableName!!Predict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~C!!@tableName!!AndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	p!!@tableName!!	要被判断的!!@usage!!
	///@return	true表示合法，false表示不合法
	virtual bool isValid(C!!@tableName!! *p!!@tableName!!)
	{
		return m_p1->isValid(p!!@tableName!!) && m_p2->isValid(p!!@tableName!!);
	}
};

/////////////////////////////////////////////////////////////////////////
///C!!@tableName!!OrPredict是对两个!!@usage!!谓词的或谓词
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@tableName!!OrPredict : public C!!@tableName!!Predict
{
private:
	C!!@tableName!!Predict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	C!!@tableName!!OrPredict(C!!@tableName!!Predict *p1, C!!@tableName!!Predict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~C!!@tableName!!OrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	p!!@tableName!!	要被判断的!!@usage!!
	///@return	true表示合法，false表示不合法
	virtual bool isValid(C!!@tableName!! *p!!@tableName!!)
	{
		return m_p1->isValid(p!!@tableName!!) || m_p2->isValid(p!!@tableName!!);
	}
};

/////////////////////////////////////////////////////////////////////////
///C!!@tableName!!NotPredict是对一个!!@usage!!谓词的非谓词
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@tableName!!NotPredict : public C!!@tableName!!Predict
{
private:
	C!!@tableName!!Predict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	C!!@tableName!!NotPredict(C!!@tableName!!Predict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~C!!@tableName!!NotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	p!!@tableName!!	要被判断的!!@usage!!
	///@return	true表示合法，false表示不合法
	virtual bool isValid(C!!@tableName!! *p!!@tableName!!)
	{
		return !m_predict->isValid(p!!@tableName!!);
	}
};

/////////////////////////////////////////////////////////////////////////
///C!!@tableName!!Filter是一个对已有的!!@usage!!枚举器进行过滤的枚举器
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@tableName!!Filter: public C!!@tableName!!Iterator
{
private:
	C!!@tableName!!Iterator *m_baseIterator;
	C!!@tableName!!Predict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	C!!@tableName!!Filter(C!!@tableName!!Iterator *pBaseIterator, C!!@tableName!!Predict *pPredict, bool continueResult=false)
		:C!!@tableName!!Iterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~C!!@tableName!!Filter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的C!!@tableName!!
	///@return	下一个满足条件C!!@tableName!!，如果已经没有一个满足要求了，则返回NULL
	virtual C!!@tableName!! *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	p!!@name!! 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteable!!@tableName!! * p!!@name!!,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///C!!@tableName!!LinkIterator是连接两个!!@usage!!枚举器的枚举器
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@tableName!!LinkIterator: public C!!@tableName!!Iterator
{
private:
	C!!@tableName!!Iterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	C!!@tableName!!LinkIterator(C!!@tableName!!Iterator *pBaseIterator1,C!!@tableName!!Iterator *pBaseIterator2)
		:C!!@tableName!!Iterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~C!!@tableName!!LinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的C!!@tableName!!
	///@return	下一个满足条件C!!@tableName!!，如果已经没有一个满足要求了，则返回NULL
	virtual C!!@tableName!! *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	p!!@name!! 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteable!!@tableName!! * p!!@name!!,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

!!travel foreigns!!
!!let foreignName=@name!!
/////////////////////////////////////////////////////////////////////////
///C!!@foreignName!!Of!!@tableName!!Iterator是一个!!@usage!!枚举器!!@comment!!的枚举器
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@foreignName!!Of!!@tableName!!Iterator: public C!!@factory!!Iterator
{
private:
	C!!@tableName!!Iterator *m_baseIterator;
	C!!@factory!! *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	C!!@foreignName!!Of!!@tableName!!Iterator(C!!@factory!!Factory *pFactory,C!!@tableName!!Iterator *pBaseIterator)
		:C!!@factory!!Iterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~C!!@foreignName!!Of!!@tableName!!Iterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的C!!@factory!!
	///@return	下一个满足条件C!!@factory!!，如果已经没有一个满足要求了，则返回NULL
	virtual C!!@factory!! *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	p!!@factory!! 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteable!!@factory!! *p!!@factory!!,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

!!next!!

!!endif!!
!!next!!
#endif
!!leave!!
