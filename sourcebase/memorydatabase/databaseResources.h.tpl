!!include function.tpl!!
!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseResources.h
///@brief定义了若干内存数据资源，可以放置于事务中
///@history 
///20060127	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef DATABASERESOURCES_H
#define DATABASERESOURCES_H

#include "databaseData.h"
#include "MemoryStack.h"

!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!command resetEntityMap();!!
!!travel fields!!
!!command addEntity(@name,@type)!!
!!next!!
/////////////////////////////////////////////////////////////////////////
///C!!@name!!Resource是一个说明在C!!@name!!Factory中使用事务管理的原子资源
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@name!!Resource : public CDatabaseResource
{
public:
	///构造方法
	C!!@name!!Resource(void);
!!++!!
	///构造方法
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的C!!@name!!Factory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	C!!@name!!Resource(int type, C!!@name!!Factory *pFactory, C!!@name!! *pObject, CWriteable!!@name!! *pWriteableObject, bool updateIndex=true);
!!--!!
	virtual ~C!!@name!!Resource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的C!!@name!!Factory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, C!!@name!!Factory *pFactory, C!!@name!! *pObject, CWriteable!!@name!! *pWriteableObject, bool updateIndex=true)
	{
		m_type=type;
		m_updateIndex=updateIndex;
		this->pFactory=pFactory;
		this->ref=(void *)pObject;
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

	///释放自己
	virtual void free(void);

	///获取本资源所在的C!!@name!!Factory
	///@return	该C!!@name!!Factory
	C!!@name!!Factory *getFactory(void)
	{
		return pFactory;
	}

	///完成提交
	virtual void commit(void);
	
	///完成滚回
	virtual void rollback(void);
	
	///获取优先级，优先级可以控制commit时的次序
	///@return	本资源的优先级，0表示最高，1表示正常，1表示最低
	virtual int getPriority(void);

	///申请一个有指定内容的资源
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的C!!@name!!Factory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static C!!@name!!Resource *alloc(int type, C!!@name!!Factory *pFactory, C!!@name!! *pObject, CWriteable!!@name!! *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	C!!@name!!Factory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteable!!@name!! writeableObject;
	
	static CMemoryStack<C!!@name!!Resource> resourceList;
};

!!endif!!
!!next!!
#endif
!!leave!!
