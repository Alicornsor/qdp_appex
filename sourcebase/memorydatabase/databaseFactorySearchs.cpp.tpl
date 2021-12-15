!!include function.tpl!!
!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseFactories.pp
///@brief 实现了若干个内存数据库的对象工厂
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "BaseDataStruct.h"
#include "databaseFactories.h"
#include "databaseResources.h"
#include "monitorIndex.h"

//#define COUNT_SEARCH
!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!command resetEntityMap();!!
!!travel fields!!
!!command addEntity(@name,@type)!!
!!next!!
!!let tableName=@name!!
!!travel index!!
int compareFor!!@name!!in!!@tableName!!(const void *pV1, const void *pV2)
{
	C!!@tableName!! *p1,*p2;
	p1=(C!!@tableName!! *)pV1;
	p2=(C!!@tableName!! *)pV2;
	!!if atoi(@son_size)==0!!
		!!error printf("index %s in table %s has no items\n",@name,@tableName)!!
	!!endif!!
	!!travel self!!
	switch (compare(p1->!!@name!!.getValue(),p2->!!@name!!.getValue()))
	{
	!!if !strcmp(@isAsc,"yes")!!
	case 1:
		return 1;
	case -1:
		return -1;
	!!else!!
	case 1:
		return -1;
	case -1:
		return 1;
	!!endif!!
	case 0:
	default:
		break;
	}
	!!next!!
	return 0;
}
!!next!!
!!travel search!!

!!if (!strcmp(@searchUnique,"yes"))!!
#ifdef COUNT_SEARCH
int find!!@name!!For!!@tableName!!=0;
#endif
C!!@tableName!! *C!!@tableName!!Factory::find!!@name!!(!!travel parameter!!!!if (@pumpid!=0)!!, !!endif!! const !!command getReadOnlyEntityTypeName(@name);!!!!show_string (char *)strResult.c_str()!!&  !!@name!!!!next!!)
{
	if (runLevel<!!@runLevel!!)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use find!!@name!! of C!!@tableName!! while run level < !!@runLevel!!");
	}
!!if strcmp(@indexName,"noIndex")!!
#ifdef COUNT_SEARCH
	find!!@name!!For!!@tableName!!++;
#endif
	CAVLNode *pNode;
	!!travel parameter!!
	compareObject.!!@name!!=!!@name!!.getValue();
	!!next!!
	!!travel default!!
	compareObject.!!@name!!=!!@value!!;
	!!next!!
	!!let hasNoCheck="no"!!
	!!travel parameter!!
	!!if strcmp(@checkParameter,"yes")!!
		!!let hasNoCheck="yes"!!
	!!endif!!
	!!next!!
	!!travel default!!
	!!if strcmp(@checkDefault,"yes")!!
		!!let hasNoCheck="yes"!!
	!!endif!!
	!!next!!
	!!if !strcmp(@hasNoCheck,"no")!!	
	pNode=p!!@indexName!!->searchFirstEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	!!else!!
	pNode=p!!@indexName!!->searchFirstGreatEqual(&compareObject);
	if (pNode==NULL)
	{
		return NULL;
	}
	!!travel parameter!!
	!!if !strcmp(@checkParameter,"yes")!!
	if (compare(((C!!@tableName!! *)(pNode->pObject))->!!@name!!.getValue(),!!@name!!.getValue())!=0)
	{
		return NULL;
	}
	!!endif!!
	!!next!!
	!!travel default!!
	!!if !strcmp(@checkDefault,"yes")!!
	if (compare(((C!!@tableName!! *)(pNode->pObject))->!!@name!!.getValue(),!!@value!!)!=0)
	{
		return NULL;
	}
	!!endif!!
	!!next!!
	!!endif!!
	return (C!!@tableName!! *)(pNode->pObject);
!!elseif valid_name("hashIndexName")!!
	CHashIndexNode *pNode;
	!!travel parameter!!
	compareObject.!!@name!!=!!@name!!.getValue();
	!!next!!
	!!travel default!!
	compareObject.!!@name!!=!!@value!!;
	!!next!!
	
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
	compareObject.calHash!!@thisHashKey!!();
	for (pNode=p!!@hashIndexName!!->searchFirstEqual(compareObject.Hash!!@thisHashKey!!);
		pNode!=NULL;
		pNode=p!!@hashIndexName!!->searchNextEqual(pNode))
	{
		if (((C!!@tableName!! *)(pNode->pObject))->Hash!!@thisHashKey!! != compareObject.Hash!!@thisHashKey!!)
		{
			continue;
		}
		!!travel parameter!!
		!!if !strcmp(@checkParameter,"yes")!!
		if (compare(((C!!@tableName!! *)(pNode->pObject))->!!@name!!.getValue(),!!@name!!.getValue())!=0)
		{
			continue;
		}
		!!endif!!
		!!next!!
		!!travel default!!
		!!if !strcmp(@checkDefault,"yes")!!
		if (compare(((C!!@tableName!! *)(pNode->pObject))->!!@name!!.getValue(),!!@value!!)!=0)
		{
			continue;
		}
		!!endif!!
		!!next!!
		return (C!!@tableName!! *)(pNode->pObject);
	}
	return NULL;
!!else!!
	C!!@tableName!! *the!!@tableName!!;
	for (the!!@tableName!!=(C!!@tableName!! *)(pMem->getFirst());
		the!!@tableName!!!=NULL;
		the!!@tableName!!=(C!!@tableName!! *)(pMem->getNext()))
	{
		!!travel parameter!!
		!!if !strcmp(@checkParameter,"yes")!!
		if (compare(the!!@tableName!!->!!@name!!.getValue(),!!@name!!.getValue())!=0)
		{
			continue;
		}
		!!endif!!
		!!next!!
		!!travel default!!
		!!if !strcmp(@checkDefault,"yes")!!
		if (compare(the!!@tableName!!->!!@name!!.getValue(),!!@value!!)!=0)
		{
			continue;
		}
		!!endif!!
		!!next!!
		return the!!@tableName!!;
	}
	return NULL;
!!endif!!
}

!!if !strcmp(@isPK,"yes")!!
C!!@tableName!! *C!!@tableName!!Factory::findByPK(!!travel parameter!!!!if (@pumpid!=0)!!, !!endif!! const !!command getReadOnlyEntityTypeName(@name);!!!!show_string (char *)strResult.c_str()!!&  !!@name!!!!next!!)
{
	return find!!@name!!(!!travel parameter!!!!if (@pumpid!=0)!!, !!endif!!!!@name!!!!next!!);
}
	
C!!@tableName!! *C!!@tableName!!Factory::findByPK(CWriteable!!@tableName!! *p!!@tableName!!)
{
	return findByPK(
		!!travel parameter!!
		!!if @pumpid!=0!!
		,
		!!endif!!
		p!!@tableName!!->!!@name!!
		!!next!!
		);
}

bool C!!@tableName!!Factory::retrieveByPK(CWriteable!!@tableName!! *p!!@tableName!!)
{
	C!!@tableName!! *pOriginal!!@tableName!!;
	pOriginal!!@tableName!!=findByPK(p!!@tableName!!);
	if (pOriginal!!@tableName!!==NULL)
	{
		return false;
	}
	retrieve(pOriginal!!@tableName!!,p!!@tableName!!);
	return true;
}

C!!@tableName!! *C!!@tableName!!Factory::addByPK(CWriteable!!@tableName!! *p!!@tableName!!, CTransaction *pTransaction)
{
	C!!@tableName!! *pOriginal!!@tableName!!;
	pOriginal!!@tableName!!=findByPK(p!!@tableName!!);
	if (pOriginal!!@tableName!! != NULL)
	{
		return NULL;
	}
	return add(p!!@tableName!!,pTransaction);
}

bool C!!@tableName!!Factory::updateByPK(CWriteable!!@tableName!! *p!!@tableName!!, CTransaction *pTransaction, bool updateIndex)
{
	C!!@tableName!! *pOriginal!!@tableName!!;
	pOriginal!!@tableName!!=findByPK(p!!@tableName!!);
	if (pOriginal!!@tableName!!==NULL)
	{
		return false;
	}
	p!!@tableName!!->calAllHash();
	update(pOriginal!!@tableName!!,p!!@tableName!!,pTransaction,updateIndex);
	return true;
}

bool C!!@tableName!!Factory::removeByPK(CWriteable!!@tableName!! *p!!@tableName!!, CTransaction *pTransaction)
{
	C!!@tableName!! *pOriginal!!@tableName!!;
	pOriginal!!@tableName!!=findByPK(p!!@tableName!!);
	if (pOriginal!!@tableName!!==NULL)
	{
		return false;
	}
	remove(pOriginal!!@tableName!!,pTransaction);
	return true;
}

!!endif!!

!!else!!
#ifdef COUNT_SEARCH
int multiFind!!@name!!For!!@tableName!!=0;
#endif

C!!@tableName!! *C!!@tableName!!Factory::startFind!!@name!!(!!travel parameter!!!!if (@pumpid!=0)!!, !!endif!! const !!command getReadOnlyEntityTypeName(@name);!!!!show_string (char *)strResult.c_str()!!& !!@name!!!!next!!)
{
	if (runLevel<!!@runLevel!!)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","Can not use startFind!!@name!! of C!!@tableName!! while run level < !!@runLevel!!");
	}
	///如果原来正在查询，就不能再次开始查询了，给出警告错误
	if (pLastFoundInSearch!!@name!!!=NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","start a new find before the end of another one");
		endFind!!@name!!();
	}

	///记录所有的查询值
	!!let searchName=@name!!
	!!travel parameter!!
	query!!@name!!InSearch!!@searchName!!= !!@name!!.getValue();
	!!next!!

!!if strcmp(@indexName,"noIndex")!!
#ifdef COUNT_SEARCH
	multiFind!!@name!!For!!@tableName!!++;
#endif
	///根据参数和缺省值，设置用于比较的对象的各个分量
	C!!@tableName!! *the!!@tableName!!;
	!!travel parameter!!
	compareObject.!!@name!!=!!@name!!.getValue();
	!!next!!
	!!travel default!!
	compareObject.!!@name!!=!!@value!!;
	!!next!!
	
	///在索引中寻找第一个满足条件的
	pLastFoundInSearch!!@name!!=p!!@indexName!!->searchFirstGreatEqual(&compareObject);
	
	///如果没有找到，则返回
	if (pLastFoundInSearch!!@name!!==NULL)
	{
		return NULL;
	}

	///获取找到的对象
	the!!@tableName!!=(C!!@tableName!! *)(pLastFoundInSearch!!@name!!->pObject);
	
	///如果有一个条件不满足，则失败返回
	!!travel parameter!!
	!!if !strcmp(@checkParameter,"yes")!!
	if (compare(the!!@tableName!!->!!@name!!.getValue(),!!@name!!.getValue()))
	{
		pLastFoundInSearch!!@searchName!!=NULL;
		return NULL;
	}
	!!endif!!
	!!next!!
	!!travel default!!
	!!if !strcmp(@checkDefault,"yes")!!
	if (compare(the!!@tableName!!->!!@name!!,!!@value!!))
	{
		pLastFoundInSearch!!@searchName!!=NULL;
		return NULL;
	}
	!!endif!!
	!!next!!

	///返回找到的结果
	return the!!@tableName!!;
!!elseif valid_name("hashIndexName")!!
	C!!@tableName!! *the!!@tableName!!;
	!!travel parameter!!
	compareObject.!!@name!!=!!@name!!.getValue();
	!!next!!
	!!travel default!!
	compareObject.!!@name!!=!!@value!!;
	!!next!!
	
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
	compareObject.calHash!!@thisHashKey!!();

	
	for (pLastFoundInSearch!!@name!!=p!!@hashIndexName!!->searchFirstEqual(compareObject.Hash!!@thisHashKey!!);
		pLastFoundInSearch!!@name!! !=NULL;
		pLastFoundInSearch!!@name!!=p!!@hashIndexName!!->searchNextEqual(pLastFoundInSearch!!@name!!))
	{
		the!!@tableName!!=(C!!@tableName!! *)(pLastFoundInSearch!!@name!!->pObject);
		if (the!!@tableName!!->Hash!!@thisHashKey!! != compareObject.Hash!!@thisHashKey!!)
		{
			continue;
		}
		!!travel parameter!!
		!!if !strcmp(@checkParameter,"yes")!!
		if (compare(the!!@tableName!!->!!@name!!.getValue(),!!@name!!.getValue())!=0)
		{
			continue;
		}
		!!endif!!
		!!next!!
		!!travel default!!
		!!if !strcmp(@checkDefault,"yes")!!
		if (compare(the!!@tableName!!->!!@name!!.getValue(),!!@value!!)!=0)
		{
			continue;
		}
		!!endif!!
		!!next!!
		return the!!@tableName!!;
	}
	return NULL;
!!else!!
	///如果一个对象也没有，就返回失败
	pLastFoundInSearch!!@name!!=(C!!@tableName!! *)(pMem->getFirst());
	
	if (pLastFoundInSearch!!@name!!==NULL)
	{
		return NULL;
	}
	
	///如果第一个不正确，则使用findNext!!@searchName!!来寻找下一个
	!!travel parameter!!
	!!if !strcmp(@checkParameter,"yes")!!
	if (compare(pLastFoundInSearch!!@searchName!!->!!@name!!.getValue(),!!@name!!.getValue()))
	{
		return findNext!!@searchName!!();
	}
	!!endif!!
	!!next!!
	!!travel default!!
	!!if !strcmp(@checkDefault,"yes")!!
	if (compare(pLastFoundInSearch!!@searchName!!->!!@name!!,!!@value!!))
	{
		return findNext!!@searchName!!();
	}
	!!endif!!
	!!next!!
	
	///返回找到的结果
	return pLastFoundInSearch!!@name!!;
!!endif!!
}

C!!@tableName!! *C!!@tableName!!Factory::findNext!!@name!!(void)
{
	///还没有开始查找，或者已经找到最后一个了，就立即返回
	if (pLastFoundInSearch!!@name!!==NULL)
	{
		return NULL;
	}

!!if strcmp(@indexName,"noIndex")!!
#ifdef COUNT_SEARCH
	multiFind!!@name!!For!!@tableName!!++;
#endif
	C!!@tableName!! *the!!@tableName!!;

	///找下一个节点，如果没有，则查找结束
	pLastFoundInSearch!!@name!!=p!!@indexName!!->getNextNode(pLastFoundInSearch!!@name!!);
	if (pLastFoundInSearch!!@name!!==NULL)
	{
		return NULL;
	}

	the!!@tableName!!=(C!!@tableName!! *)(pLastFoundInSearch!!@name!!->pObject);
	
	///如果有一个条件不满足，则失败返回
	!!travel parameter!!
	!!if !strcmp(@checkParameter,"yes")!!
	if (compare(the!!@tableName!!->!!@name!!,query!!@name!!InSearch!!@searchName!!))
	{
		pLastFoundInSearch!!@searchName!!=NULL;
		return NULL;
	}
	!!endif!!
	!!next!!
	!!travel default!!
	!!if !strcmp(@checkDefault,"yes")!!
	if (compare(the!!@tableName!!->!!@name!!,!!@value!!))
	{
		pLastFoundInSearch!!@searchName!!=NULL;
		return NULL;
	}
	!!endif!!
	!!next!!

	///返回找到的结果
	return the!!@tableName!!;
!!elseif valid_name("hashIndexName")!!
	C!!@tableName!! *the!!@tableName!!;
	
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

	
	for (;;)
	{
		pLastFoundInSearch!!@name!!=p!!@hashIndexName!!->searchNextEqual(pLastFoundInSearch!!@name!!);
		if (pLastFoundInSearch!!@name!!==NULL)
		{
			return NULL;
		}
		the!!@tableName!!=(C!!@tableName!! *)(pLastFoundInSearch!!@name!!->pObject);
		if (the!!@tableName!!->Hash!!@thisHashKey!! != compareObject.Hash!!@thisHashKey!!)
		{
			continue;
		}
		!!travel parameter!!
		!!if !strcmp(@checkParameter,"yes")!!
		if (compare(the!!@tableName!!->!!@name!!.getValue(),compareObject.!!@name!!.getValue())!=0)
		{
			continue;
		}
		!!endif!!
		!!next!!
		!!travel default!!
		!!if !strcmp(@checkDefault,"yes")!!
		if (compare(the!!@tableName!!->!!@name!!.getValue(),compareObject.!!@value!!)!=0)
		{
			continue;
		}
		!!endif!!
		!!next!!
		return the!!@tableName!!;
	}
	return NULL;
!!else!!
	///反复尝试寻找
	for (;;)
	{
		///如果已经没有下一个了，则失败返回
		pLastFoundInSearch!!@name!!=(C!!@tableName!! *)(pMem->getNext());
		if (pLastFoundInSearch!!@name!!==NULL)
		{
			return NULL;
		}

		///如果一个条件不满足，则尝试下一个
		!!travel parameter!!
		!!if !strcmp(@checkParameter,"yes")!!
		if (compare(pLastFoundInSearch!!@searchName!!->!!@name!!,query!!@name!!InSearch!!@searchName!!))
		{
			continue;
		}
		!!endif!!
		!!next!!
		!!travel default!!
		!!if !strcmp(@checkDefault,"yes")!!
		if (compare(pLastFoundInSearch!!@searchName!!->!!@name!!,!!@value!!))
		{
			continue;
		}
		!!endif!!
		!!next!!
		///返回找到的结果
		return pLastFoundInSearch!!@searchName!!;
	}
!!endif!!
}

void C!!@tableName!!Factory::endFind!!@name!!(void)
{
	pLastFoundInSearch!!@name!!=NULL;
}

!!endif!!
!!next!!
!!endif!!
!!next!!
#ifdef COUNT_SEARCH
void showAllSearchCount(void)
{
	printf("\n");
!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!let tableName=@name!!
!!travel search!!
!!if (!strcmp(@searchUnique,"yes"))!!
	if (find!!@name!!For!!@tableName!! !=0)
	{
		printf("\tfind!!@name!!For!!@tableName!!:%d\n",find!!@name!!For!!@tableName!!);
	}
!!else!!
	if (multiFind!!@name!!For!!@tableName!! !=0)
	{
		printf("\tmultiFind!!@name!!For!!@tableName!!:%d\n",multiFind!!@name!!For!!@tableName!!);
	}
!!endif!!
!!next!!
!!endif!!
!!next!!
}

void initAllSearchCount(void)
{
!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!let tableName=@name!!
!!travel search!!
!!if (!strcmp(@searchUnique,"yes"))!!
	find!!@name!!For!!@tableName!!=0;
!!else!!
	multiFind!!@name!!For!!@tableName!!=0;
!!endif!!
!!next!!
!!endif!!
!!next!!
}
#endif
!!leave!!
