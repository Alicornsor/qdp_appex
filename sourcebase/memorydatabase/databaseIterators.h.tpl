!!include function.tpl!!
!!enter system!!
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

!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!command resetEntityMap();!!
!!travel fields!!
!!command addEntity(@name,@type)!!
!!next!!
!!let tableName=@name!!
!!travel search!!
!!if (strcmp(@searchUnique,"yes"))!!
/////////////////////////////////////////////////////////////////////////
///C!!@tableName!!Iterator!!@name!!是一个对!!@usage!!使用!!@name!!方法进行
///查找的枚举器
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@tableName!!Iterator!!@name!!: public C!!@tableName!!Iterator
{
	friend class C!!@tableName!!Factory;
private:
	///检查此对象是否满足条件
	///@param	p!!@tableName!!		要被检查的对象
	///@return	1表示满足条件，0表示不满足条件
	int match(C!!@tableName!! *p!!@tableName!!);

	///在需要的情况下，获取下一个值，如果不是第一次，而且还没有取过下一个值，
	///那么就必须保证叫用时m_pCurrent指向正确的值，否则本方法的结果不确定
	void internalGetNext(void);

	///是否是第一次查询
	int m_isFirstTime;
	
	///是否已经取了下一个对象
	bool m_gotNext;

!!if (strcmp(@indexName,"noIndex"))!!
	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CAVLNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CAVLNode *m_pNext;
!!elseif valid_name("hashIndexName")!!
	///存储最后一次找到的索引节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	CHashIndexNode *m_pCurrent;

	///当m_gotNext为true时，本值下一次next时的开始寻找的节点对应的索引节点，其他情况下无意义
	CHashIndexNode *m_pNext;
!!else!!
	///存储最后一次找到的节点
	///当m_isFirstTime为1时，或者发生了DeleteCurrent时，本值无意义
	C!!@tableName!! *m_pCurrent;
	
	///当m_gotNext为true时，本值下一次next时的开始寻找的节点，其他情况下无意义
	C!!@tableName!! *m_pNext;
!!endif!!

	///用于存储查询参数的对象
	CWriteable!!@tableName!! m_compareObject;
	
	static CMemoryStack<C!!@tableName!!Iterator!!@name!!> iteratorList;
public:
	///构造方法
	///@param	pFactory	要查找的对象工厂
	!!travel parameter!!
	///@param	!!@name!!	!!@desc!!
	!!next!!
	C!!@tableName!!Iterator!!@name!!(C!!@tableName!!Factory *pFactory
		!!travel parameter!!,const !!command getReadOnlyEntityTypeName(@name);!!!!show_string (char *)strResult.c_str()!!& !!@name!!!!next!!)
	{
		init(pFactory!!travel parameter!!,!!@name!!!!next!!);
	}

	///申请一个新的对象
	///@param	pFactory	要查找的对象工厂
	!!travel parameter!!
	///@param	!!@name!!	!!@desc!!
	!!next!!
	static C!!@tableName!!Iterator!!@name!! *alloc(C!!@tableName!!Factory *pFactory
		!!travel parameter!!,const !!command getReadOnlyEntityTypeName(@name);!!!!show_string (char *)strResult.c_str()!!& !!@name!!!!next!!);

	///构造方法
	C!!@tableName!!Iterator!!@name!!(void)
	{
	}

	///初始化
	///@param	pFactory	要查找的对象工厂
	!!travel parameter!!
	///@param	!!@name!!	!!@desc!!
	!!next!!
	void init(C!!@tableName!!Factory *pFactory
		!!travel parameter!!,const !!command getReadOnlyEntityTypeName(@name);!!!!show_string (char *)strResult.c_str()!!& !!@name!!!!next!!);

	///析构方法，将负责释放所占用的空间
	virtual ~C!!@tableName!!Iterator!!@name!!(void);
	
	virtual void free(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///寻找下一个符合条件的C!!@tableName!!，必须在startFind!!@name!!以后，endFind!!@name!!之前叫用
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
!!endif!!
!!next!!

!!endif!!
!!next!!
#endif
!!leave!!
