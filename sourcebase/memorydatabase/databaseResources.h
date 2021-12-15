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

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusResource是一个说明在CDataSyncStatusFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusResource : public CDatabaseResource
{
public:
	///构造方法
	CDataSyncStatusResource(void);
	virtual ~CDataSyncStatusResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CDataSyncStatusFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CDataSyncStatusFactory *pFactory, CDataSyncStatus *pObject, CWriteableDataSyncStatus *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CDataSyncStatusFactory
	///@return	该CDataSyncStatusFactory
	CDataSyncStatusFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CDataSyncStatusFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CDataSyncStatusResource *alloc(int type, CDataSyncStatusFactory *pFactory, CDataSyncStatus *pObject, CWriteableDataSyncStatus *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CDataSyncStatusFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableDataSyncStatus writeableObject;
	
	static CMemoryStack<CDataSyncStatusResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusResource是一个说明在CSystemStatusFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusResource : public CDatabaseResource
{
public:
	///构造方法
	CSystemStatusResource(void);
	virtual ~CSystemStatusResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CSystemStatusFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CSystemStatusFactory *pFactory, CSystemStatus *pObject, CWriteableSystemStatus *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CSystemStatusFactory
	///@return	该CSystemStatusFactory
	CSystemStatusFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CSystemStatusFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CSystemStatusResource *alloc(int type, CSystemStatusFactory *pFactory, CSystemStatus *pObject, CWriteableSystemStatus *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CSystemStatusFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableSystemStatus writeableObject;
	
	static CMemoryStack<CSystemStatusResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///COrderActionResource是一个说明在COrderActionFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionResource : public CDatabaseResource
{
public:
	///构造方法
	COrderActionResource(void);
	virtual ~COrderActionResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的COrderActionFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, COrderActionFactory *pFactory, COrderAction *pObject, CWriteableOrderAction *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的COrderActionFactory
	///@return	该COrderActionFactory
	COrderActionFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的COrderActionFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static COrderActionResource *alloc(int type, COrderActionFactory *pFactory, COrderAction *pObject, CWriteableOrderAction *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	COrderActionFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableOrderAction writeableObject;
	
	static CMemoryStack<COrderActionResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///COrderResource是一个说明在COrderFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderResource : public CDatabaseResource
{
public:
	///构造方法
	COrderResource(void);
	virtual ~COrderResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的COrderFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, COrderFactory *pFactory, COrder *pObject, CWriteableOrder *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的COrderFactory
	///@return	该COrderFactory
	COrderFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的COrderFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static COrderResource *alloc(int type, COrderFactory *pFactory, COrder *pObject, CWriteableOrder *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	COrderFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableOrder writeableObject;
	
	static CMemoryStack<COrderResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CTradeResource是一个说明在CTradeFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeResource : public CDatabaseResource
{
public:
	///构造方法
	CTradeResource(void);
	virtual ~CTradeResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CTradeFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CTradeFactory *pFactory, CTrade *pObject, CWriteableTrade *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CTradeFactory
	///@return	该CTradeFactory
	CTradeFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CTradeFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CTradeResource *alloc(int type, CTradeFactory *pFactory, CTrade *pObject, CWriteableTrade *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CTradeFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableTrade writeableObject;
	
	static CMemoryStack<CTradeResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderResource是一个说明在CPreOrderFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderResource : public CDatabaseResource
{
public:
	///构造方法
	CPreOrderResource(void);
	virtual ~CPreOrderResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CPreOrderFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CPreOrderFactory *pFactory, CPreOrder *pObject, CWriteablePreOrder *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CPreOrderFactory
	///@return	该CPreOrderFactory
	CPreOrderFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CPreOrderFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CPreOrderResource *alloc(int type, CPreOrderFactory *pFactory, CPreOrder *pObject, CWriteablePreOrder *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CPreOrderFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteablePreOrder writeableObject;
	
	static CMemoryStack<CPreOrderResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderResource是一个说明在CIndexPreOrderFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderResource : public CDatabaseResource
{
public:
	///构造方法
	CIndexPreOrderResource(void);
	virtual ~CIndexPreOrderResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CIndexPreOrderFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CIndexPreOrderFactory *pFactory, CIndexPreOrder *pObject, CWriteableIndexPreOrder *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CIndexPreOrderFactory
	///@return	该CIndexPreOrderFactory
	CIndexPreOrderFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CIndexPreOrderFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CIndexPreOrderResource *alloc(int type, CIndexPreOrderFactory *pFactory, CIndexPreOrder *pObject, CWriteableIndexPreOrder *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CIndexPreOrderFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableIndexPreOrder writeableObject;
	
	static CMemoryStack<CIndexPreOrderResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionResource是一个说明在CInvestorPositionFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionResource : public CDatabaseResource
{
public:
	///构造方法
	CInvestorPositionResource(void);
	virtual ~CInvestorPositionResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CInvestorPositionFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CInvestorPositionFactory *pFactory, CInvestorPosition *pObject, CWriteableInvestorPosition *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CInvestorPositionFactory
	///@return	该CInvestorPositionFactory
	CInvestorPositionFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CInvestorPositionFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CInvestorPositionResource *alloc(int type, CInvestorPositionFactory *pFactory, CInvestorPosition *pObject, CWriteableInvestorPosition *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CInvestorPositionFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableInvestorPosition writeableObject;
	
	static CMemoryStack<CInvestorPositionResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountResource是一个说明在CInvestorAccountFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountResource : public CDatabaseResource
{
public:
	///构造方法
	CInvestorAccountResource(void);
	virtual ~CInvestorAccountResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CInvestorAccountFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CInvestorAccountFactory *pFactory, CInvestorAccount *pObject, CWriteableInvestorAccount *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CInvestorAccountFactory
	///@return	该CInvestorAccountFactory
	CInvestorAccountFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CInvestorAccountFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CInvestorAccountResource *alloc(int type, CInvestorAccountFactory *pFactory, CInvestorAccount *pObject, CWriteableInvestorAccount *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CInvestorAccountFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableInvestorAccount writeableObject;
	
	static CMemoryStack<CInvestorAccountResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositResource是一个说明在CInvestorAccountDepositFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositResource : public CDatabaseResource
{
public:
	///构造方法
	CInvestorAccountDepositResource(void);
	virtual ~CInvestorAccountDepositResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CInvestorAccountDepositFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CInvestorAccountDepositFactory *pFactory, CInvestorAccountDeposit *pObject, CWriteableInvestorAccountDeposit *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CInvestorAccountDepositFactory
	///@return	该CInvestorAccountDepositFactory
	CInvestorAccountDepositFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CInvestorAccountDepositFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CInvestorAccountDepositResource *alloc(int type, CInvestorAccountDepositFactory *pFactory, CInvestorAccountDeposit *pObject, CWriteableInvestorAccountDeposit *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CInvestorAccountDepositFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableInvestorAccountDeposit writeableObject;
	
	static CMemoryStack<CInvestorAccountDepositResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CExchangeResource是一个说明在CExchangeFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeResource : public CDatabaseResource
{
public:
	///构造方法
	CExchangeResource(void);
	virtual ~CExchangeResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CExchangeFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CExchangeFactory *pFactory, CExchange *pObject, CWriteableExchange *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CExchangeFactory
	///@return	该CExchangeFactory
	CExchangeFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CExchangeFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CExchangeResource *alloc(int type, CExchangeFactory *pFactory, CExchange *pObject, CWriteableExchange *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CExchangeFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableExchange writeableObject;
	
	static CMemoryStack<CExchangeResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CSeatResource是一个说明在CSeatFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatResource : public CDatabaseResource
{
public:
	///构造方法
	CSeatResource(void);
	virtual ~CSeatResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CSeatFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CSeatFactory *pFactory, CSeat *pObject, CWriteableSeat *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CSeatFactory
	///@return	该CSeatFactory
	CSeatFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CSeatFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CSeatResource *alloc(int type, CSeatFactory *pFactory, CSeat *pObject, CWriteableSeat *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CSeatFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableSeat writeableObject;
	
	static CMemoryStack<CSeatResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentResource是一个说明在CInstrumentFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentResource : public CDatabaseResource
{
public:
	///构造方法
	CInstrumentResource(void);
	virtual ~CInstrumentResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CInstrumentFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CInstrumentFactory *pFactory, CInstrument *pObject, CWriteableInstrument *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CInstrumentFactory
	///@return	该CInstrumentFactory
	CInstrumentFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CInstrumentFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CInstrumentResource *alloc(int type, CInstrumentFactory *pFactory, CInstrument *pObject, CWriteableInstrument *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CInstrumentFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableInstrument writeableObject;
	
	static CMemoryStack<CInstrumentResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailResource是一个说明在CCmbInstrumentDetailFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailResource : public CDatabaseResource
{
public:
	///构造方法
	CCmbInstrumentDetailResource(void);
	virtual ~CCmbInstrumentDetailResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CCmbInstrumentDetailFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CCmbInstrumentDetailFactory *pFactory, CCmbInstrumentDetail *pObject, CWriteableCmbInstrumentDetail *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CCmbInstrumentDetailFactory
	///@return	该CCmbInstrumentDetailFactory
	CCmbInstrumentDetailFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CCmbInstrumentDetailFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CCmbInstrumentDetailResource *alloc(int type, CCmbInstrumentDetailFactory *pFactory, CCmbInstrumentDetail *pObject, CWriteableCmbInstrumentDetail *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CCmbInstrumentDetailFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableCmbInstrumentDetail writeableObject;
	
	static CMemoryStack<CCmbInstrumentDetailResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDResource是一个说明在CClientTradingIDFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDResource : public CDatabaseResource
{
public:
	///构造方法
	CClientTradingIDResource(void);
	virtual ~CClientTradingIDResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CClientTradingIDFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CClientTradingIDFactory *pFactory, CClientTradingID *pObject, CWriteableClientTradingID *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CClientTradingIDFactory
	///@return	该CClientTradingIDFactory
	CClientTradingIDFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CClientTradingIDFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CClientTradingIDResource *alloc(int type, CClientTradingIDFactory *pFactory, CClientTradingID *pObject, CWriteableClientTradingID *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CClientTradingIDFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableClientTradingID writeableObject;
	
	static CMemoryStack<CClientTradingIDResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorResource是一个说明在CInvestorFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorResource : public CDatabaseResource
{
public:
	///构造方法
	CInvestorResource(void);
	virtual ~CInvestorResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CInvestorFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CInvestorFactory *pFactory, CInvestor *pObject, CWriteableInvestor *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CInvestorFactory
	///@return	该CInvestorFactory
	CInvestorFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CInvestorFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CInvestorResource *alloc(int type, CInvestorFactory *pFactory, CInvestor *pObject, CWriteableInvestor *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CInvestorFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableInvestor writeableObject;
	
	static CMemoryStack<CInvestorResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginResource是一个说明在CInvestorMarginFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginResource : public CDatabaseResource
{
public:
	///构造方法
	CInvestorMarginResource(void);
	virtual ~CInvestorMarginResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CInvestorMarginFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CInvestorMarginFactory *pFactory, CInvestorMargin *pObject, CWriteableInvestorMargin *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CInvestorMarginFactory
	///@return	该CInvestorMarginFactory
	CInvestorMarginFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CInvestorMarginFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CInvestorMarginResource *alloc(int type, CInvestorMarginFactory *pFactory, CInvestorMargin *pObject, CWriteableInvestorMargin *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CInvestorMarginFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableInvestorMargin writeableObject;
	
	static CMemoryStack<CInvestorMarginResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeResource是一个说明在CInvestorFeeFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeResource : public CDatabaseResource
{
public:
	///构造方法
	CInvestorFeeResource(void);
	virtual ~CInvestorFeeResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CInvestorFeeFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CInvestorFeeFactory *pFactory, CInvestorFee *pObject, CWriteableInvestorFee *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CInvestorFeeFactory
	///@return	该CInvestorFeeFactory
	CInvestorFeeFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CInvestorFeeFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CInvestorFeeResource *alloc(int type, CInvestorFeeFactory *pFactory, CInvestorFee *pObject, CWriteableInvestorFee *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CInvestorFeeFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableInvestorFee writeableObject;
	
	static CMemoryStack<CInvestorFeeResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CUserResource是一个说明在CUserFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserResource : public CDatabaseResource
{
public:
	///构造方法
	CUserResource(void);
	virtual ~CUserResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CUserFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CUserFactory *pFactory, CUser *pObject, CWriteableUser *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CUserFactory
	///@return	该CUserFactory
	CUserFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CUserFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CUserResource *alloc(int type, CUserFactory *pFactory, CUser *pObject, CWriteableUser *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CUserFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableUser writeableObject;
	
	static CMemoryStack<CUserResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorResource是一个说明在CUserInvestorFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorResource : public CDatabaseResource
{
public:
	///构造方法
	CUserInvestorResource(void);
	virtual ~CUserInvestorResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CUserInvestorFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CUserInvestorFactory *pFactory, CUserInvestor *pObject, CWriteableUserInvestor *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CUserInvestorFactory
	///@return	该CUserInvestorFactory
	CUserInvestorFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CUserInvestorFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CUserInvestorResource *alloc(int type, CUserInvestorFactory *pFactory, CUserInvestor *pObject, CWriteableUserInvestor *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CUserInvestorFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableUserInvestor writeableObject;
	
	static CMemoryStack<CUserInvestorResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedResource是一个说明在COrderInsertFailedFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedResource : public CDatabaseResource
{
public:
	///构造方法
	COrderInsertFailedResource(void);
	virtual ~COrderInsertFailedResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的COrderInsertFailedFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, COrderInsertFailedFactory *pFactory, COrderInsertFailed *pObject, CWriteableOrderInsertFailed *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的COrderInsertFailedFactory
	///@return	该COrderInsertFailedFactory
	COrderInsertFailedFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的COrderInsertFailedFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static COrderInsertFailedResource *alloc(int type, COrderInsertFailedFactory *pFactory, COrderInsertFailed *pObject, CWriteableOrderInsertFailed *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	COrderInsertFailedFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableOrderInsertFailed writeableObject;
	
	static CMemoryStack<COrderInsertFailedResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightResource是一个说明在CUserTradingRightFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightResource : public CDatabaseResource
{
public:
	///构造方法
	CUserTradingRightResource(void);
	virtual ~CUserTradingRightResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CUserTradingRightFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CUserTradingRightFactory *pFactory, CUserTradingRight *pObject, CWriteableUserTradingRight *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CUserTradingRightFactory
	///@return	该CUserTradingRightFactory
	CUserTradingRightFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CUserTradingRightFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CUserTradingRightResource *alloc(int type, CUserTradingRightFactory *pFactory, CUserTradingRight *pObject, CWriteableUserTradingRight *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CUserTradingRightFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableUserTradingRight writeableObject;
	
	static CMemoryStack<CUserTradingRightResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeResource是一个说明在CCurrentTimeFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeResource : public CDatabaseResource
{
public:
	///构造方法
	CCurrentTimeResource(void);
	virtual ~CCurrentTimeResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CCurrentTimeFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CCurrentTimeFactory *pFactory, CCurrentTime *pObject, CWriteableCurrentTime *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CCurrentTimeFactory
	///@return	该CCurrentTimeFactory
	CCurrentTimeFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CCurrentTimeFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CCurrentTimeResource *alloc(int type, CCurrentTimeFactory *pFactory, CCurrentTime *pObject, CWriteableCurrentTime *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CCurrentTimeFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableCurrentTime writeableObject;
	
	static CMemoryStack<CCurrentTimeResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionResource是一个说明在CUserSessionFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionResource : public CDatabaseResource
{
public:
	///构造方法
	CUserSessionResource(void);
	virtual ~CUserSessionResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CUserSessionFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CUserSessionFactory *pFactory, CUserSession *pObject, CWriteableUserSession *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CUserSessionFactory
	///@return	该CUserSessionFactory
	CUserSessionFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CUserSessionFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CUserSessionResource *alloc(int type, CUserSessionFactory *pFactory, CUserSession *pObject, CWriteableUserSession *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CUserSessionFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableUserSession writeableObject;
	
	static CMemoryStack<CUserSessionResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDResource是一个说明在CMaxLocalIDFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDResource : public CDatabaseResource
{
public:
	///构造方法
	CMaxLocalIDResource(void);
	virtual ~CMaxLocalIDResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CMaxLocalIDFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CMaxLocalIDFactory *pFactory, CMaxLocalID *pObject, CWriteableMaxLocalID *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CMaxLocalIDFactory
	///@return	该CMaxLocalIDFactory
	CMaxLocalIDFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CMaxLocalIDFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CMaxLocalIDResource *alloc(int type, CMaxLocalIDFactory *pFactory, CMaxLocalID *pObject, CWriteableMaxLocalID *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CMaxLocalIDFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableMaxLocalID writeableObject;
	
	static CMemoryStack<CMaxLocalIDResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDResource是一个说明在CBrkUserIDLocalIDFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDResource : public CDatabaseResource
{
public:
	///构造方法
	CBrkUserIDLocalIDResource(void);
	virtual ~CBrkUserIDLocalIDResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CBrkUserIDLocalIDFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CBrkUserIDLocalIDFactory *pFactory, CBrkUserIDLocalID *pObject, CWriteableBrkUserIDLocalID *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CBrkUserIDLocalIDFactory
	///@return	该CBrkUserIDLocalIDFactory
	CBrkUserIDLocalIDFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CBrkUserIDLocalIDFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CBrkUserIDLocalIDResource *alloc(int type, CBrkUserIDLocalIDFactory *pFactory, CBrkUserIDLocalID *pObject, CWriteableBrkUserIDLocalID *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CBrkUserIDLocalIDFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableBrkUserIDLocalID writeableObject;
	
	static CMemoryStack<CBrkUserIDLocalIDResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionResource是一个说明在CPartClientInsGroupPositionFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionResource : public CDatabaseResource
{
public:
	///构造方法
	CPartClientInsGroupPositionResource(void);
	virtual ~CPartClientInsGroupPositionResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CPartClientInsGroupPositionFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CPartClientInsGroupPositionFactory *pFactory, CPartClientInsGroupPosition *pObject, CWriteablePartClientInsGroupPosition *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CPartClientInsGroupPositionFactory
	///@return	该CPartClientInsGroupPositionFactory
	CPartClientInsGroupPositionFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CPartClientInsGroupPositionFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CPartClientInsGroupPositionResource *alloc(int type, CPartClientInsGroupPositionFactory *pFactory, CPartClientInsGroupPosition *pObject, CWriteablePartClientInsGroupPosition *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CPartClientInsGroupPositionFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteablePartClientInsGroupPosition writeableObject;
	
	static CMemoryStack<CPartClientInsGroupPositionResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeResource是一个说明在CClientMarginCombTypeFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeResource : public CDatabaseResource
{
public:
	///构造方法
	CClientMarginCombTypeResource(void);
	virtual ~CClientMarginCombTypeResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CClientMarginCombTypeFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CClientMarginCombTypeFactory *pFactory, CClientMarginCombType *pObject, CWriteableClientMarginCombType *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CClientMarginCombTypeFactory
	///@return	该CClientMarginCombTypeFactory
	CClientMarginCombTypeFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CClientMarginCombTypeFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CClientMarginCombTypeResource *alloc(int type, CClientMarginCombTypeFactory *pFactory, CClientMarginCombType *pObject, CWriteableClientMarginCombType *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CClientMarginCombTypeFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableClientMarginCombType writeableObject;
	
	static CMemoryStack<CClientMarginCombTypeResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupResource是一个说明在CInstrumentGroupFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupResource : public CDatabaseResource
{
public:
	///构造方法
	CInstrumentGroupResource(void);
	virtual ~CInstrumentGroupResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CInstrumentGroupFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CInstrumentGroupFactory *pFactory, CInstrumentGroup *pObject, CWriteableInstrumentGroup *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CInstrumentGroupFactory
	///@return	该CInstrumentGroupFactory
	CInstrumentGroupFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CInstrumentGroupFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CInstrumentGroupResource *alloc(int type, CInstrumentGroupFactory *pFactory, CInstrumentGroup *pObject, CWriteableInstrumentGroup *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CInstrumentGroupFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableInstrumentGroup writeableObject;
	
	static CMemoryStack<CInstrumentGroupResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateResource是一个说明在CSGEDeferRateFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateResource : public CDatabaseResource
{
public:
	///构造方法
	CSGEDeferRateResource(void);
	virtual ~CSGEDeferRateResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CSGEDeferRateFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CSGEDeferRateFactory *pFactory, CSGEDeferRate *pObject, CWriteableSGEDeferRate *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CSGEDeferRateFactory
	///@return	该CSGEDeferRateFactory
	CSGEDeferRateFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CSGEDeferRateFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CSGEDeferRateResource *alloc(int type, CSGEDeferRateFactory *pFactory, CSGEDeferRate *pObject, CWriteableSGEDeferRate *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CSGEDeferRateFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableSGEDeferRate writeableObject;
	
	static CMemoryStack<CSGEDeferRateResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightResource是一个说明在CInvestorTradingRightFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightResource : public CDatabaseResource
{
public:
	///构造方法
	CInvestorTradingRightResource(void);
	virtual ~CInvestorTradingRightResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CInvestorTradingRightFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CInvestorTradingRightFactory *pFactory, CInvestorTradingRight *pObject, CWriteableInvestorTradingRight *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CInvestorTradingRightFactory
	///@return	该CInvestorTradingRightFactory
	CInvestorTradingRightFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CInvestorTradingRightFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CInvestorTradingRightResource *alloc(int type, CInvestorTradingRightFactory *pFactory, CInvestorTradingRight *pObject, CWriteableInvestorTradingRight *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CInvestorTradingRightFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableInvestorTradingRight writeableObject;
	
	static CMemoryStack<CInvestorTradingRightResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CUserIPResource是一个说明在CUserIPFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPResource : public CDatabaseResource
{
public:
	///构造方法
	CUserIPResource(void);
	virtual ~CUserIPResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CUserIPFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CUserIPFactory *pFactory, CUserIP *pObject, CWriteableUserIP *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CUserIPFactory
	///@return	该CUserIPFactory
	CUserIPFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CUserIPFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CUserIPResource *alloc(int type, CUserIPFactory *pFactory, CUserIP *pObject, CWriteableUserIP *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CUserIPFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableUserIP writeableObject;
	
	static CMemoryStack<CUserIPResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeResource是一个说明在CInvestorOptionFeeFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeResource : public CDatabaseResource
{
public:
	///构造方法
	CInvestorOptionFeeResource(void);
	virtual ~CInvestorOptionFeeResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CInvestorOptionFeeFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CInvestorOptionFeeFactory *pFactory, CInvestorOptionFee *pObject, CWriteableInvestorOptionFee *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CInvestorOptionFeeFactory
	///@return	该CInvestorOptionFeeFactory
	CInvestorOptionFeeFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CInvestorOptionFeeFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CInvestorOptionFeeResource *alloc(int type, CInvestorOptionFeeFactory *pFactory, CInvestorOptionFee *pObject, CWriteableInvestorOptionFee *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CInvestorOptionFeeFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableInvestorOptionFee writeableObject;
	
	static CMemoryStack<CInvestorOptionFeeResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataResource是一个说明在CMarketDataFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataResource : public CDatabaseResource
{
public:
	///构造方法
	CMarketDataResource(void);
	virtual ~CMarketDataResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CMarketDataFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CMarketDataFactory *pFactory, CMarketData *pObject, CWriteableMarketData *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CMarketDataFactory
	///@return	该CMarketDataFactory
	CMarketDataFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CMarketDataFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CMarketDataResource *alloc(int type, CMarketDataFactory *pFactory, CMarketData *pObject, CWriteableMarketData *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CMarketDataFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableMarketData writeableObject;
	
	static CMemoryStack<CMarketDataResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayResource是一个说明在COrderDelayFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayResource : public CDatabaseResource
{
public:
	///构造方法
	COrderDelayResource(void);
	virtual ~COrderDelayResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的COrderDelayFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, COrderDelayFactory *pFactory, COrderDelay *pObject, CWriteableOrderDelay *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的COrderDelayFactory
	///@return	该COrderDelayFactory
	COrderDelayFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的COrderDelayFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static COrderDelayResource *alloc(int type, COrderDelayFactory *pFactory, COrderDelay *pObject, CWriteableOrderDelay *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	COrderDelayFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableOrderDelay writeableObject;
	
	static CMemoryStack<COrderDelayResource> resourceList;
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoResource是一个说明在CSystemInfoFactory中使用事务管理的原子资源
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoResource : public CDatabaseResource
{
public:
	///构造方法
	CSystemInfoResource(void);
	virtual ~CSystemInfoResource(void);

	///初始化
	///@param	type	资源类型，应当是CREATE_ACTION、DELETE_ACTION或UPDATE_ACTION
	///@param	pFactory	本资源所在的CSystemInfoFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	void init(int type, CSystemInfoFactory *pFactory, CSystemInfo *pObject, CWriteableSystemInfo *pWriteableObject, bool updateIndex=true)
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

	///获取本资源所在的CSystemInfoFactory
	///@return	该CSystemInfoFactory
	CSystemInfoFactory *getFactory(void)
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
	///@param	pFactory	本资源所在的CSystemInfoFactory
	///@param	pObject	本资源的地址
	///@param	pWriteableObject	新的对象值，当type为UPDATE_ACTION时有效，在目前的实现中没有用处
	///@param	updateIndex	是否更新索引
	///@return	返回一个有指定内容的资源
	static CSystemInfoResource *alloc(int type, CSystemInfoFactory *pFactory, CSystemInfo *pObject, CWriteableSystemInfo *pWriteableObject, bool updateIndex=true);
private:
	///存放本资源所在的对象工厂
	CSystemInfoFactory *pFactory;
	
	///存放本资源修改前的值，当type为CREATE_ACTION和DELETE_ACTION时，本项无意义
	CWriteableSystemInfo writeableObject;
	
	static CMemoryStack<CSystemInfoResource> resourceList;
};

#endif
