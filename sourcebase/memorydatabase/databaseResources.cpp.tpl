!!include function.tpl!!
!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseResources.cpp
///@brief实现了若干内存数据资源，可以放置于事务中
///@history 
///20060127	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "databaseResources.h"

!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!command resetEntityMap();!!
!!travel fields!!
!!command addEntity(@name,@type)!!
!!next!!

CMemoryStack<C!!@name!!Resource> C!!@name!!Resource::resourceList;

C!!@name!!Resource * C!!@name!!Resource::alloc(int type, C!!@name!!Factory *pFactory, C!!@name!! *pObject, CWriteable!!@name!! *pWriteableObject, bool updateIndex)
{
	C!!@name!!Resource *pResource=resourceList.alloc();
	pResource->init(type,pFactory,pObject,pWriteableObject,updateIndex);
	return pResource;
}

void C!!@name!!Resource::free(void)
{
	resourceList.free(this);
}

C!!@name!!Resource::C!!@name!!Resource(void)
{
}
!!++!!
C!!@name!!Resource::C!!@name!!Resource(int type, C!!@name!!Factory *pFactory, C!!@name!! *pObject, CWriteable!!@name!! *pWriteableObject, bool updateIndex):
	CDatabaseResource(type,updateIndex)
{
	this->pFactory=pFactory;
	this->ref=pObject;
	if (pFactory==NULL)
	{
		RAISE_DESIGN_ERROR("Invalid pFactory while creating resource");
	}
	if (pObject==NULL)
	{
		RAISE_DESIGN_ERROR("Must have pObject value for database resource");
	}
	if ((type==UPDATE_ACTION)&&(pWriteableObject==NULL))
	{
		RAISE_DESIGN_ERROR("Must have pWriteableObject value while update database resource");
	}
	
	switch (type)
	{
	case CREATE_ACTION:
		break;
	case UPDATE_ACTION:
	case DELETE_ACTION:
		pFactory->retrieve(pObject,&writeableObject);
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}				
}
!!--!!
!!++!!
void C!!@name!!Resource::init(int type, C!!@name!!Factory *pFactory, C!!@name!! *pObject, CWriteable!!@name!! *pWriteableObject, bool updateIndex)
{
	m_type=type;
	m_updateIndex=updateIndex;
	this->pFactory=pFactory;
	this->ref=pObject;
	switch (type)
	{
	case CREATE_ACTION:
		break;
	case UPDATE_ACTION:
	case DELETE_ACTION:
		pFactory->retrieve(pObject,&writeableObject);
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}				
}
!!--!!

C!!@name!!Resource::~C!!@name!!Resource(void)
{
}

void C!!@name!!Resource::commit(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->commitAdd((C!!@name!! *)ref);
		break;
	case UPDATE_ACTION:
		pFactory->commitUpdate((C!!@name!! *)ref,&writeableObject);	
		break;
	case DELETE_ACTION:
		pFactory->commitRemove(&writeableObject);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}
	
void C!!@name!!Resource::rollback(void)
{
	switch (m_type)
	{
	case CREATE_ACTION:
		pFactory->internalRemove((C!!@name!! *)ref,false);
		break;
	case UPDATE_ACTION:
		pFactory->internalUpdate((C!!@name!! *)ref,&writeableObject,m_updateIndex,false);
		break;
	case DELETE_ACTION:
		pFactory->internalAdd(&writeableObject,false);
		break;
	case NONE_ACTION:
		break;
	default:
		RAISE_DESIGN_ERROR("Invalid resource type");
	}
}

int C!!@name!!Resource::getPriority(void)
{
	return !!@priority!!;
}

!!++!!
C!!@name!!Factory *C!!@name!!Resource::getFactory(void)
{
	return pFactory;
}
!!--!!
!!endif!!
!!next!!
!!leave!!
