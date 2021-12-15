!!include function.tpl!!
!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseGroupActions.h
///@brief定义了若干个内存数据库的群组操作
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef DATABASEGROUPACTIONS_H
#define DATABASEGROUPACTIONS_H

#include "BaseDataStruct.h"
#include "databaseFactories.h"

!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!command resetEntityMap();!!
!!travel fields!!
!!command addEntity(@name,@type)!!
!!next!!

///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* T!!@name!!ActionFunc)(C!!@name!! * p!!@name!!, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* T!!@name!!UpdateFunc)(CWriteable!!@name!! * p!!@name!!, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* T!!@name!!SelectFunc)(C!!@name!! * p!!@name!!,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(C!!@name!!Iterator *pIterator, T!!@name!!ActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(C!!@name!!Iterator *pIterator, T!!@name!!UpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(C!!@name!!Iterator *pIterator, T!!@name!!SelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

!!endif!!
!!next!!
#endif
!!leave!!
