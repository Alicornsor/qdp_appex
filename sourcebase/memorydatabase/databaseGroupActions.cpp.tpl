!!include function.tpl!!
!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseGroupActions.cpp
///@brief实现了若干个内存数据库的群组操作
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "databaseGroupActions.h"

!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!command resetEntityMap();!!
!!travel fields!!
!!command addEntity(@name,@type)!!
!!next!!	
void groupAction(C!!@name!!Iterator *pIterator, T!!@name!!ActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	C!!@name!! *p!!@name!!;
	
	while ((p!!@name!!=pIterator->next())!=NULL)
	{
		if (!actionFunc(p!!@name!!, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(C!!@name!!Iterator *pIterator, T!!@name!!UpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	C!!@name!! *p!!@name!!;
	CWriteable!!@name!! the!!@name!!;
	bool updateIndex;
	C!!@name!!Factory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((p!!@name!!=pIterator->next())!=NULL)
	{
		pFactory->retrieve(p!!@name!!,&the!!@name!!);
		needContinue=updateFunc(&the!!@name!!, pTransaction, parameter, &updateIndex);
		pFactory->update(p!!@name!!,&the!!@name!!,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(C!!@name!!Iterator *pIterator, T!!@name!!SelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	C!!@name!! *p!!@name!!;
	int selected;
	C!!@name!!Factory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((p!!@name!!=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(p!!@name!!, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(p!!@name!!,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

!!endif!!
!!next!!
!!leave!!
