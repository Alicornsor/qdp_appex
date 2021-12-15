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

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusSingleIterator是至多返回一个数据同步状态表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusSingleIterator: public CDataSyncStatusIterator
{
private:
	CDataSyncStatus *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CDataSyncStatusSingleIterator(CDataSyncStatusFactory *pFactory,CDataSyncStatus *pResult)
		:CDataSyncStatusIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CDataSyncStatusSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CDataSyncStatus
	///@return	下一个满足条件CDataSyncStatus，如果已经没有一个满足要求了，则返回NULL
	virtual CDataSyncStatus *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pDataSyncStatus 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableDataSyncStatus * pDataSyncStatus,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusPredict是判断一个数据同步状态表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusPredict
{
public:
	virtual ~CDataSyncStatusPredict(){};

	///判断是否合法
	///@param	pDataSyncStatus	要被判断的数据同步状态表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CDataSyncStatus *pDataSyncStatus)=0;
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusAndPredict是对两个数据同步状态表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusAndPredict : public CDataSyncStatusPredict
{
private:
	CDataSyncStatusPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CDataSyncStatusAndPredict(CDataSyncStatusPredict *p1, CDataSyncStatusPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CDataSyncStatusAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pDataSyncStatus	要被判断的数据同步状态表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CDataSyncStatus *pDataSyncStatus)
	{
		return m_p1->isValid(pDataSyncStatus) && m_p2->isValid(pDataSyncStatus);
	}
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusOrPredict是对两个数据同步状态表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusOrPredict : public CDataSyncStatusPredict
{
private:
	CDataSyncStatusPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CDataSyncStatusOrPredict(CDataSyncStatusPredict *p1, CDataSyncStatusPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CDataSyncStatusOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pDataSyncStatus	要被判断的数据同步状态表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CDataSyncStatus *pDataSyncStatus)
	{
		return m_p1->isValid(pDataSyncStatus) || m_p2->isValid(pDataSyncStatus);
	}
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusNotPredict是对一个数据同步状态表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusNotPredict : public CDataSyncStatusPredict
{
private:
	CDataSyncStatusPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CDataSyncStatusNotPredict(CDataSyncStatusPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CDataSyncStatusNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pDataSyncStatus	要被判断的数据同步状态表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CDataSyncStatus *pDataSyncStatus)
	{
		return !m_predict->isValid(pDataSyncStatus);
	}
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusFilter是一个对已有的数据同步状态表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusFilter: public CDataSyncStatusIterator
{
private:
	CDataSyncStatusIterator *m_baseIterator;
	CDataSyncStatusPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CDataSyncStatusFilter(CDataSyncStatusIterator *pBaseIterator, CDataSyncStatusPredict *pPredict, bool continueResult=false)
		:CDataSyncStatusIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CDataSyncStatusFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CDataSyncStatus
	///@return	下一个满足条件CDataSyncStatus，如果已经没有一个满足要求了，则返回NULL
	virtual CDataSyncStatus *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pDataSyncStatus 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableDataSyncStatus * pDataSyncStatus,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusLinkIterator是连接两个数据同步状态表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusLinkIterator: public CDataSyncStatusIterator
{
private:
	CDataSyncStatusIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CDataSyncStatusLinkIterator(CDataSyncStatusIterator *pBaseIterator1,CDataSyncStatusIterator *pBaseIterator2)
		:CDataSyncStatusIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CDataSyncStatusLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CDataSyncStatus
	///@return	下一个满足条件CDataSyncStatus，如果已经没有一个满足要求了，则返回NULL
	virtual CDataSyncStatus *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pDataSyncStatus 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableDataSyncStatus * pDataSyncStatus,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CSystemStatusSingleIterator是至多返回一个QDP状态表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusSingleIterator: public CSystemStatusIterator
{
private:
	CSystemStatus *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CSystemStatusSingleIterator(CSystemStatusFactory *pFactory,CSystemStatus *pResult)
		:CSystemStatusIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CSystemStatusSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CSystemStatus
	///@return	下一个满足条件CSystemStatus，如果已经没有一个满足要求了，则返回NULL
	virtual CSystemStatus *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pSystemStatus 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSystemStatus * pSystemStatus,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusPredict是判断一个QDP状态表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusPredict
{
public:
	virtual ~CSystemStatusPredict(){};

	///判断是否合法
	///@param	pSystemStatus	要被判断的QDP状态表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSystemStatus *pSystemStatus)=0;
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusAndPredict是对两个QDP状态表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusAndPredict : public CSystemStatusPredict
{
private:
	CSystemStatusPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CSystemStatusAndPredict(CSystemStatusPredict *p1, CSystemStatusPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CSystemStatusAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pSystemStatus	要被判断的QDP状态表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSystemStatus *pSystemStatus)
	{
		return m_p1->isValid(pSystemStatus) && m_p2->isValid(pSystemStatus);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusOrPredict是对两个QDP状态表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusOrPredict : public CSystemStatusPredict
{
private:
	CSystemStatusPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CSystemStatusOrPredict(CSystemStatusPredict *p1, CSystemStatusPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CSystemStatusOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pSystemStatus	要被判断的QDP状态表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSystemStatus *pSystemStatus)
	{
		return m_p1->isValid(pSystemStatus) || m_p2->isValid(pSystemStatus);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusNotPredict是对一个QDP状态表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusNotPredict : public CSystemStatusPredict
{
private:
	CSystemStatusPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CSystemStatusNotPredict(CSystemStatusPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CSystemStatusNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pSystemStatus	要被判断的QDP状态表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSystemStatus *pSystemStatus)
	{
		return !m_predict->isValid(pSystemStatus);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusFilter是一个对已有的QDP状态表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusFilter: public CSystemStatusIterator
{
private:
	CSystemStatusIterator *m_baseIterator;
	CSystemStatusPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CSystemStatusFilter(CSystemStatusIterator *pBaseIterator, CSystemStatusPredict *pPredict, bool continueResult=false)
		:CSystemStatusIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CSystemStatusFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CSystemStatus
	///@return	下一个满足条件CSystemStatus，如果已经没有一个满足要求了，则返回NULL
	virtual CSystemStatus *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pSystemStatus 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSystemStatus * pSystemStatus,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusLinkIterator是连接两个QDP状态表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusLinkIterator: public CSystemStatusIterator
{
private:
	CSystemStatusIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CSystemStatusLinkIterator(CSystemStatusIterator *pBaseIterator1,CSystemStatusIterator *pBaseIterator2)
		:CSystemStatusIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CSystemStatusLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CSystemStatus
	///@return	下一个满足条件CSystemStatus，如果已经没有一个满足要求了，则返回NULL
	virtual CSystemStatus *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pSystemStatus 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSystemStatus * pSystemStatus,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///COrderActionSingleIterator是至多返回一个报单操作的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionSingleIterator: public COrderActionIterator
{
private:
	COrderAction *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	COrderActionSingleIterator(COrderActionFactory *pFactory,COrderAction *pResult)
		:COrderActionIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~COrderActionSingleIterator(void)
	{
	}

	///寻找下一个符合条件的COrderAction
	///@return	下一个满足条件COrderAction，如果已经没有一个满足要求了，则返回NULL
	virtual COrderAction *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pOrderAction 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrderAction * pOrderAction,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionPredict是判断一个报单操作是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionPredict
{
public:
	virtual ~COrderActionPredict(){};

	///判断是否合法
	///@param	pOrderAction	要被判断的报单操作
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderAction *pOrderAction)=0;
};

/////////////////////////////////////////////////////////////////////////
///COrderActionAndPredict是对两个报单操作谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionAndPredict : public COrderActionPredict
{
private:
	COrderActionPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	COrderActionAndPredict(COrderActionPredict *p1, COrderActionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~COrderActionAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pOrderAction	要被判断的报单操作
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderAction *pOrderAction)
	{
		return m_p1->isValid(pOrderAction) && m_p2->isValid(pOrderAction);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderActionOrPredict是对两个报单操作谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionOrPredict : public COrderActionPredict
{
private:
	COrderActionPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	COrderActionOrPredict(COrderActionPredict *p1, COrderActionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~COrderActionOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pOrderAction	要被判断的报单操作
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderAction *pOrderAction)
	{
		return m_p1->isValid(pOrderAction) || m_p2->isValid(pOrderAction);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderActionNotPredict是对一个报单操作谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionNotPredict : public COrderActionPredict
{
private:
	COrderActionPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	COrderActionNotPredict(COrderActionPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~COrderActionNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pOrderAction	要被判断的报单操作
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderAction *pOrderAction)
	{
		return !m_predict->isValid(pOrderAction);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderActionFilter是一个对已有的报单操作枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionFilter: public COrderActionIterator
{
private:
	COrderActionIterator *m_baseIterator;
	COrderActionPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	COrderActionFilter(COrderActionIterator *pBaseIterator, COrderActionPredict *pPredict, bool continueResult=false)
		:COrderActionIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~COrderActionFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的COrderAction
	///@return	下一个满足条件COrderAction，如果已经没有一个满足要求了，则返回NULL
	virtual COrderAction *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pOrderAction 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrderAction * pOrderAction,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderActionLinkIterator是连接两个报单操作枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionLinkIterator: public COrderActionIterator
{
private:
	COrderActionIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	COrderActionLinkIterator(COrderActionIterator *pBaseIterator1,COrderActionIterator *pBaseIterator2)
		:COrderActionIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~COrderActionLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的COrderAction
	///@return	下一个满足条件COrderAction，如果已经没有一个满足要求了，则返回NULL
	virtual COrderAction *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pOrderAction 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrderAction * pOrderAction,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderOfOrderActionIterator是一个报单操作枚举器对应的报单的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderOfOrderActionIterator: public COrderIterator
{
private:
	COrderActionIterator *m_baseIterator;
	COrder *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	COrderOfOrderActionIterator(COrderFactory *pFactory,COrderActionIterator *pBaseIterator)
		:COrderIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~COrderOfOrderActionIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的COrder
	///@return	下一个满足条件COrder，如果已经没有一个满足要求了，则返回NULL
	virtual COrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pOrder 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrder *pOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderOfOrderActionIterator是一个报单操作枚举器对应的报单的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderOfOrderActionIterator: public CPreOrderIterator
{
private:
	COrderActionIterator *m_baseIterator;
	CPreOrder *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CPreOrderOfOrderActionIterator(CPreOrderFactory *pFactory,COrderActionIterator *pBaseIterator)
		:CPreOrderIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CPreOrderOfOrderActionIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CPreOrder
	///@return	下一个满足条件CPreOrder，如果已经没有一个满足要求了，则返回NULL
	virtual CPreOrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pPreOrder 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteablePreOrder *pPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///COrderSingleIterator是至多返回一个委托表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderSingleIterator: public COrderIterator
{
private:
	COrder *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	COrderSingleIterator(COrderFactory *pFactory,COrder *pResult)
		:COrderIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~COrderSingleIterator(void)
	{
	}

	///寻找下一个符合条件的COrder
	///@return	下一个满足条件COrder，如果已经没有一个满足要求了，则返回NULL
	virtual COrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pOrder 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrder * pOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderPredict是判断一个委托表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderPredict
{
public:
	virtual ~COrderPredict(){};

	///判断是否合法
	///@param	pOrder	要被判断的委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrder *pOrder)=0;
};

/////////////////////////////////////////////////////////////////////////
///COrderAndPredict是对两个委托表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderAndPredict : public COrderPredict
{
private:
	COrderPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	COrderAndPredict(COrderPredict *p1, COrderPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~COrderAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pOrder	要被判断的委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrder *pOrder)
	{
		return m_p1->isValid(pOrder) && m_p2->isValid(pOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderOrPredict是对两个委托表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderOrPredict : public COrderPredict
{
private:
	COrderPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	COrderOrPredict(COrderPredict *p1, COrderPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~COrderOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pOrder	要被判断的委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrder *pOrder)
	{
		return m_p1->isValid(pOrder) || m_p2->isValid(pOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderNotPredict是对一个委托表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderNotPredict : public COrderPredict
{
private:
	COrderPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	COrderNotPredict(COrderPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~COrderNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pOrder	要被判断的委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrder *pOrder)
	{
		return !m_predict->isValid(pOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderFilter是一个对已有的委托表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderFilter: public COrderIterator
{
private:
	COrderIterator *m_baseIterator;
	COrderPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	COrderFilter(COrderIterator *pBaseIterator, COrderPredict *pPredict, bool continueResult=false)
		:COrderIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~COrderFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的COrder
	///@return	下一个满足条件COrder，如果已经没有一个满足要求了，则返回NULL
	virtual COrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pOrder 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrder * pOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderLinkIterator是连接两个委托表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderLinkIterator: public COrderIterator
{
private:
	COrderIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	COrderLinkIterator(COrderIterator *pBaseIterator1,COrderIterator *pBaseIterator2)
		:COrderIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~COrderLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的COrder
	///@return	下一个满足条件COrder，如果已经没有一个满足要求了，则返回NULL
	virtual COrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pOrder 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrder * pOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOfOrderIterator是一个委托表枚举器对应的投资者的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOfOrderIterator: public CInvestorIterator
{
private:
	COrderIterator *m_baseIterator;
	CInvestor *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorOfOrderIterator(CInvestorFactory *pFactory,COrderIterator *pBaseIterator)
		:CInvestorIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestor
	///@return	下一个满足条件CInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestor *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestor 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestor *pInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDOfOrderIterator是一个委托表枚举器对应的交易编码的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDOfOrderIterator: public CClientTradingIDIterator
{
private:
	COrderIterator *m_baseIterator;
	CClientTradingID *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CClientTradingIDOfOrderIterator(CClientTradingIDFactory *pFactory,COrderIterator *pBaseIterator)
		:CClientTradingIDIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CClientTradingIDOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CClientTradingID
	///@return	下一个满足条件CClientTradingID，如果已经没有一个满足要求了，则返回NULL
	virtual CClientTradingID *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pClientTradingID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableClientTradingID *pClientTradingID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountOfOrderIterator是一个委托表枚举器对应的帐户的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountOfOrderIterator: public CInvestorAccountIterator
{
private:
	COrderIterator *m_baseIterator;
	CInvestorAccount *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorAccountOfOrderIterator(CInvestorAccountFactory *pFactory,COrderIterator *pBaseIterator)
		:CInvestorAccountIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorAccountOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorAccount
	///@return	下一个满足条件CInvestorAccount，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccount *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorAccount 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccount *pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionOfOrderIterator是一个委托表枚举器对应的合约持仓信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionOfOrderIterator: public CInvestorPositionIterator
{
private:
	COrderIterator *m_baseIterator;
	CInvestorPosition *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorPositionOfOrderIterator(CInvestorPositionFactory *pFactory,COrderIterator *pBaseIterator)
		:CInvestorPositionIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorPositionOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorPosition
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorPosition 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorPosition *pInvestorPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentOfOrderIterator是一个委托表枚举器对应的合约信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentOfOrderIterator: public CInstrumentIterator
{
private:
	COrderIterator *m_baseIterator;
	CInstrument *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInstrumentOfOrderIterator(CInstrumentFactory *pFactory,COrderIterator *pBaseIterator)
		:CInstrumentIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInstrumentOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInstrument
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrument *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInstrument 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrument *pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginOfOrderIterator是一个委托表枚举器对应的投资者保证金率信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginOfOrderIterator: public CInvestorMarginIterator
{
private:
	COrderIterator *m_baseIterator;
	CInvestorMargin *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorMarginOfOrderIterator(CInvestorMarginFactory *pFactory,COrderIterator *pBaseIterator)
		:CInvestorMarginIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorMarginOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorMargin
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorMargin *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorMargin 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorMargin *pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeOfOrderIterator是一个委托表枚举器对应的投资者手续费率信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeOfOrderIterator: public CInvestorFeeIterator
{
private:
	COrderIterator *m_baseIterator;
	CInvestorFee *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorFeeOfOrderIterator(CInvestorFeeFactory *pFactory,COrderIterator *pBaseIterator)
		:CInvestorFeeIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorFeeOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorFee
	///@return	下一个满足条件CInvestorFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorFee *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorFee 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorFee *pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeOfOrderIterator是一个委托表枚举器对应的投资者期权手续费率信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeOfOrderIterator: public CInvestorOptionFeeIterator
{
private:
	COrderIterator *m_baseIterator;
	CInvestorOptionFee *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorOptionFeeOfOrderIterator(CInvestorOptionFeeFactory *pFactory,COrderIterator *pBaseIterator)
		:CInvestorOptionFeeIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorOptionFeeOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorOptionFee
	///@return	下一个满足条件CInvestorOptionFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorOptionFee *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorOptionFee 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorOptionFee *pInvestorOptionFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientGroupPositionOfOrderIterator是一个委托表枚举器对应的合约大边组持仓信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientGroupPositionOfOrderIterator: public CPartClientInsGroupPositionIterator
{
private:
	COrderIterator *m_baseIterator;
	CPartClientInsGroupPosition *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CClientGroupPositionOfOrderIterator(CPartClientInsGroupPositionFactory *pFactory,COrderIterator *pBaseIterator)
		:CPartClientInsGroupPositionIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CClientGroupPositionOfOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CPartClientInsGroupPosition
	///@return	下一个满足条件CPartClientInsGroupPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CPartClientInsGroupPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pPartClientInsGroupPosition 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CTradeSingleIterator是至多返回一个成交表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeSingleIterator: public CTradeIterator
{
private:
	CTrade *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CTradeSingleIterator(CTradeFactory *pFactory,CTrade *pResult)
		:CTradeIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CTradeSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CTrade
	///@return	下一个满足条件CTrade，如果已经没有一个满足要求了，则返回NULL
	virtual CTrade *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pTrade 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableTrade * pTrade,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CTradePredict是判断一个成交表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradePredict
{
public:
	virtual ~CTradePredict(){};

	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade)=0;
};

/////////////////////////////////////////////////////////////////////////
///CTradeAndPredict是对两个成交表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeAndPredict : public CTradePredict
{
private:
	CTradePredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CTradeAndPredict(CTradePredict *p1, CTradePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CTradeAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade)
	{
		return m_p1->isValid(pTrade) && m_p2->isValid(pTrade);
	}
};

/////////////////////////////////////////////////////////////////////////
///CTradeOrPredict是对两个成交表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeOrPredict : public CTradePredict
{
private:
	CTradePredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CTradeOrPredict(CTradePredict *p1, CTradePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CTradeOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade)
	{
		return m_p1->isValid(pTrade) || m_p2->isValid(pTrade);
	}
};

/////////////////////////////////////////////////////////////////////////
///CTradeNotPredict是对一个成交表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeNotPredict : public CTradePredict
{
private:
	CTradePredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CTradeNotPredict(CTradePredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CTradeNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pTrade	要被判断的成交表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CTrade *pTrade)
	{
		return !m_predict->isValid(pTrade);
	}
};

/////////////////////////////////////////////////////////////////////////
///CTradeFilter是一个对已有的成交表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeFilter: public CTradeIterator
{
private:
	CTradeIterator *m_baseIterator;
	CTradePredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CTradeFilter(CTradeIterator *pBaseIterator, CTradePredict *pPredict, bool continueResult=false)
		:CTradeIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CTradeFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CTrade
	///@return	下一个满足条件CTrade，如果已经没有一个满足要求了，则返回NULL
	virtual CTrade *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pTrade 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableTrade * pTrade,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CTradeLinkIterator是连接两个成交表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeLinkIterator: public CTradeIterator
{
private:
	CTradeIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CTradeLinkIterator(CTradeIterator *pBaseIterator1,CTradeIterator *pBaseIterator2)
		:CTradeIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CTradeLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CTrade
	///@return	下一个满足条件CTrade，如果已经没有一个满足要求了，则返回NULL
	virtual CTrade *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pTrade 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableTrade * pTrade,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CPreOrderSingleIterator是至多返回一个预委托表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderSingleIterator: public CPreOrderIterator
{
private:
	CPreOrder *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CPreOrderSingleIterator(CPreOrderFactory *pFactory,CPreOrder *pResult)
		:CPreOrderIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CPreOrderSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CPreOrder
	///@return	下一个满足条件CPreOrder，如果已经没有一个满足要求了，则返回NULL
	virtual CPreOrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pPreOrder 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteablePreOrder * pPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderPredict是判断一个预委托表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderPredict
{
public:
	virtual ~CPreOrderPredict(){};

	///判断是否合法
	///@param	pPreOrder	要被判断的预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPreOrder *pPreOrder)=0;
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderAndPredict是对两个预委托表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderAndPredict : public CPreOrderPredict
{
private:
	CPreOrderPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CPreOrderAndPredict(CPreOrderPredict *p1, CPreOrderPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CPreOrderAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pPreOrder	要被判断的预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPreOrder *pPreOrder)
	{
		return m_p1->isValid(pPreOrder) && m_p2->isValid(pPreOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderOrPredict是对两个预委托表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderOrPredict : public CPreOrderPredict
{
private:
	CPreOrderPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CPreOrderOrPredict(CPreOrderPredict *p1, CPreOrderPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CPreOrderOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pPreOrder	要被判断的预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPreOrder *pPreOrder)
	{
		return m_p1->isValid(pPreOrder) || m_p2->isValid(pPreOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderNotPredict是对一个预委托表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderNotPredict : public CPreOrderPredict
{
private:
	CPreOrderPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CPreOrderNotPredict(CPreOrderPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CPreOrderNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pPreOrder	要被判断的预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPreOrder *pPreOrder)
	{
		return !m_predict->isValid(pPreOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderFilter是一个对已有的预委托表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderFilter: public CPreOrderIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CPreOrderPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CPreOrderFilter(CPreOrderIterator *pBaseIterator, CPreOrderPredict *pPredict, bool continueResult=false)
		:CPreOrderIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CPreOrderFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CPreOrder
	///@return	下一个满足条件CPreOrder，如果已经没有一个满足要求了，则返回NULL
	virtual CPreOrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pPreOrder 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteablePreOrder * pPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderLinkIterator是连接两个预委托表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderLinkIterator: public CPreOrderIterator
{
private:
	CPreOrderIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CPreOrderLinkIterator(CPreOrderIterator *pBaseIterator1,CPreOrderIterator *pBaseIterator2)
		:CPreOrderIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CPreOrderLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CPreOrder
	///@return	下一个满足条件CPreOrder，如果已经没有一个满足要求了，则返回NULL
	virtual CPreOrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pPreOrder 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteablePreOrder * pPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOfPreOrderIterator是一个预委托表枚举器对应的投资者的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOfPreOrderIterator: public CInvestorIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CInvestor *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorOfPreOrderIterator(CInvestorFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CInvestorIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestor
	///@return	下一个满足条件CInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestor *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestor 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestor *pInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDOfPreOrderIterator是一个预委托表枚举器对应的交易编码的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDOfPreOrderIterator: public CClientTradingIDIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CClientTradingID *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CClientTradingIDOfPreOrderIterator(CClientTradingIDFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CClientTradingIDIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CClientTradingIDOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CClientTradingID
	///@return	下一个满足条件CClientTradingID，如果已经没有一个满足要求了，则返回NULL
	virtual CClientTradingID *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pClientTradingID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableClientTradingID *pClientTradingID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountOfPreOrderIterator是一个预委托表枚举器对应的帐户的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountOfPreOrderIterator: public CInvestorAccountIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CInvestorAccount *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorAccountOfPreOrderIterator(CInvestorAccountFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CInvestorAccountIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorAccountOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorAccount
	///@return	下一个满足条件CInvestorAccount，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccount *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorAccount 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccount *pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionOfPreOrderIterator是一个预委托表枚举器对应的合约持仓信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionOfPreOrderIterator: public CInvestorPositionIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CInvestorPosition *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorPositionOfPreOrderIterator(CInvestorPositionFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CInvestorPositionIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorPositionOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorPosition
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorPosition 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorPosition *pInvestorPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentOfPreOrderIterator是一个预委托表枚举器对应的合约信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentOfPreOrderIterator: public CInstrumentIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CInstrument *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInstrumentOfPreOrderIterator(CInstrumentFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CInstrumentIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInstrumentOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInstrument
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrument *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInstrument 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrument *pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginOfPreOrderIterator是一个预委托表枚举器对应的投资者保证金率信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginOfPreOrderIterator: public CInvestorMarginIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CInvestorMargin *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorMarginOfPreOrderIterator(CInvestorMarginFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CInvestorMarginIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorMarginOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorMargin
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorMargin *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorMargin 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorMargin *pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeOfPreOrderIterator是一个预委托表枚举器对应的投资者手续费率信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeOfPreOrderIterator: public CInvestorFeeIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CInvestorFee *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorFeeOfPreOrderIterator(CInvestorFeeFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CInvestorFeeIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorFeeOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorFee
	///@return	下一个满足条件CInvestorFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorFee *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorFee 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorFee *pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeOfPreOrderIterator是一个预委托表枚举器对应的投资者期权手续费率信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeOfPreOrderIterator: public CInvestorOptionFeeIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CInvestorOptionFee *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorOptionFeeOfPreOrderIterator(CInvestorOptionFeeFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CInvestorOptionFeeIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorOptionFeeOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorOptionFee
	///@return	下一个满足条件CInvestorOptionFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorOptionFee *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorOptionFee 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorOptionFee *pInvestorOptionFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientGroupPositionOfPreOrderIterator是一个预委托表枚举器对应的合约大边组持仓信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientGroupPositionOfPreOrderIterator: public CPartClientInsGroupPositionIterator
{
private:
	CPreOrderIterator *m_baseIterator;
	CPartClientInsGroupPosition *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CClientGroupPositionOfPreOrderIterator(CPartClientInsGroupPositionFactory *pFactory,CPreOrderIterator *pBaseIterator)
		:CPartClientInsGroupPositionIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CClientGroupPositionOfPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CPartClientInsGroupPosition
	///@return	下一个满足条件CPartClientInsGroupPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CPartClientInsGroupPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pPartClientInsGroupPosition 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderSingleIterator是至多返回一个索引预委托表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderSingleIterator: public CIndexPreOrderIterator
{
private:
	CIndexPreOrder *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CIndexPreOrderSingleIterator(CIndexPreOrderFactory *pFactory,CIndexPreOrder *pResult)
		:CIndexPreOrderIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CIndexPreOrderSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CIndexPreOrder
	///@return	下一个满足条件CIndexPreOrder，如果已经没有一个满足要求了，则返回NULL
	virtual CIndexPreOrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pIndexPreOrder 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableIndexPreOrder * pIndexPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderPredict是判断一个索引预委托表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderPredict
{
public:
	virtual ~CIndexPreOrderPredict(){};

	///判断是否合法
	///@param	pIndexPreOrder	要被判断的索引预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder)=0;
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderAndPredict是对两个索引预委托表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderAndPredict : public CIndexPreOrderPredict
{
private:
	CIndexPreOrderPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CIndexPreOrderAndPredict(CIndexPreOrderPredict *p1, CIndexPreOrderPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CIndexPreOrderAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pIndexPreOrder	要被判断的索引预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder)
	{
		return m_p1->isValid(pIndexPreOrder) && m_p2->isValid(pIndexPreOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderOrPredict是对两个索引预委托表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderOrPredict : public CIndexPreOrderPredict
{
private:
	CIndexPreOrderPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CIndexPreOrderOrPredict(CIndexPreOrderPredict *p1, CIndexPreOrderPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CIndexPreOrderOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pIndexPreOrder	要被判断的索引预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder)
	{
		return m_p1->isValid(pIndexPreOrder) || m_p2->isValid(pIndexPreOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderNotPredict是对一个索引预委托表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderNotPredict : public CIndexPreOrderPredict
{
private:
	CIndexPreOrderPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CIndexPreOrderNotPredict(CIndexPreOrderPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CIndexPreOrderNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pIndexPreOrder	要被判断的索引预委托表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CIndexPreOrder *pIndexPreOrder)
	{
		return !m_predict->isValid(pIndexPreOrder);
	}
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderFilter是一个对已有的索引预委托表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderFilter: public CIndexPreOrderIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CIndexPreOrderPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CIndexPreOrderFilter(CIndexPreOrderIterator *pBaseIterator, CIndexPreOrderPredict *pPredict, bool continueResult=false)
		:CIndexPreOrderIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CIndexPreOrderFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CIndexPreOrder
	///@return	下一个满足条件CIndexPreOrder，如果已经没有一个满足要求了，则返回NULL
	virtual CIndexPreOrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pIndexPreOrder 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableIndexPreOrder * pIndexPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderLinkIterator是连接两个索引预委托表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderLinkIterator: public CIndexPreOrderIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CIndexPreOrderLinkIterator(CIndexPreOrderIterator *pBaseIterator1,CIndexPreOrderIterator *pBaseIterator2)
		:CIndexPreOrderIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CIndexPreOrderLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CIndexPreOrder
	///@return	下一个满足条件CIndexPreOrder，如果已经没有一个满足要求了，则返回NULL
	virtual CIndexPreOrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pIndexPreOrder 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableIndexPreOrder * pIndexPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOfIndexPreOrderIterator是一个索引预委托表枚举器对应的投资者的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOfIndexPreOrderIterator: public CInvestorIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CInvestor *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorOfIndexPreOrderIterator(CInvestorFactory *pFactory,CIndexPreOrderIterator *pBaseIterator)
		:CInvestorIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorOfIndexPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestor
	///@return	下一个满足条件CInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestor *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestor 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestor *pInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDOfIndexPreOrderIterator是一个索引预委托表枚举器对应的交易编码的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDOfIndexPreOrderIterator: public CClientTradingIDIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CClientTradingID *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CClientTradingIDOfIndexPreOrderIterator(CClientTradingIDFactory *pFactory,CIndexPreOrderIterator *pBaseIterator)
		:CClientTradingIDIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CClientTradingIDOfIndexPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CClientTradingID
	///@return	下一个满足条件CClientTradingID，如果已经没有一个满足要求了，则返回NULL
	virtual CClientTradingID *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pClientTradingID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableClientTradingID *pClientTradingID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountOfIndexPreOrderIterator是一个索引预委托表枚举器对应的帐户的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountOfIndexPreOrderIterator: public CInvestorAccountIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CInvestorAccount *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorAccountOfIndexPreOrderIterator(CInvestorAccountFactory *pFactory,CIndexPreOrderIterator *pBaseIterator)
		:CInvestorAccountIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorAccountOfIndexPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorAccount
	///@return	下一个满足条件CInvestorAccount，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccount *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorAccount 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccount *pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentOfIndexPreOrderIterator是一个索引预委托表枚举器对应的合约信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentOfIndexPreOrderIterator: public CInstrumentIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CInstrument *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInstrumentOfIndexPreOrderIterator(CInstrumentFactory *pFactory,CIndexPreOrderIterator *pBaseIterator)
		:CInstrumentIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInstrumentOfIndexPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInstrument
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrument *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInstrument 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrument *pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginOfIndexPreOrderIterator是一个索引预委托表枚举器对应的投资者保证金率信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginOfIndexPreOrderIterator: public CInvestorMarginIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CInvestorMargin *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorMarginOfIndexPreOrderIterator(CInvestorMarginFactory *pFactory,CIndexPreOrderIterator *pBaseIterator)
		:CInvestorMarginIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorMarginOfIndexPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorMargin
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorMargin *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorMargin 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorMargin *pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeOfIndexPreOrderIterator是一个索引预委托表枚举器对应的投资者手续费率信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeOfIndexPreOrderIterator: public CInvestorFeeIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CInvestorFee *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorFeeOfIndexPreOrderIterator(CInvestorFeeFactory *pFactory,CIndexPreOrderIterator *pBaseIterator)
		:CInvestorFeeIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorFeeOfIndexPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorFee
	///@return	下一个满足条件CInvestorFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorFee *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorFee 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorFee *pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientGroupPositionOfIndexPreOrderIterator是一个索引预委托表枚举器对应的合约大边组持仓信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientGroupPositionOfIndexPreOrderIterator: public CPartClientInsGroupPositionIterator
{
private:
	CIndexPreOrderIterator *m_baseIterator;
	CPartClientInsGroupPosition *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CClientGroupPositionOfIndexPreOrderIterator(CPartClientInsGroupPositionFactory *pFactory,CIndexPreOrderIterator *pBaseIterator)
		:CPartClientInsGroupPositionIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CClientGroupPositionOfIndexPreOrderIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CPartClientInsGroupPosition
	///@return	下一个满足条件CPartClientInsGroupPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CPartClientInsGroupPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pPartClientInsGroupPosition 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorPositionSingleIterator是至多返回一个持仓表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionSingleIterator: public CInvestorPositionIterator
{
private:
	CInvestorPosition *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CInvestorPositionSingleIterator(CInvestorPositionFactory *pFactory,CInvestorPosition *pResult)
		:CInvestorPositionIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CInvestorPositionSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CInvestorPosition
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorPosition 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorPosition * pInvestorPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionPredict是判断一个持仓表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionPredict
{
public:
	virtual ~CInvestorPositionPredict(){};

	///判断是否合法
	///@param	pInvestorPosition	要被判断的持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorPosition *pInvestorPosition)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionAndPredict是对两个持仓表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionAndPredict : public CInvestorPositionPredict
{
private:
	CInvestorPositionPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorPositionAndPredict(CInvestorPositionPredict *p1, CInvestorPositionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorPositionAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestorPosition	要被判断的持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorPosition *pInvestorPosition)
	{
		return m_p1->isValid(pInvestorPosition) && m_p2->isValid(pInvestorPosition);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionOrPredict是对两个持仓表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionOrPredict : public CInvestorPositionPredict
{
private:
	CInvestorPositionPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorPositionOrPredict(CInvestorPositionPredict *p1, CInvestorPositionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorPositionOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestorPosition	要被判断的持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorPosition *pInvestorPosition)
	{
		return m_p1->isValid(pInvestorPosition) || m_p2->isValid(pInvestorPosition);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionNotPredict是对一个持仓表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionNotPredict : public CInvestorPositionPredict
{
private:
	CInvestorPositionPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CInvestorPositionNotPredict(CInvestorPositionPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CInvestorPositionNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pInvestorPosition	要被判断的持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorPosition *pInvestorPosition)
	{
		return !m_predict->isValid(pInvestorPosition);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionFilter是一个对已有的持仓表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionFilter: public CInvestorPositionIterator
{
private:
	CInvestorPositionIterator *m_baseIterator;
	CInvestorPositionPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CInvestorPositionFilter(CInvestorPositionIterator *pBaseIterator, CInvestorPositionPredict *pPredict, bool continueResult=false)
		:CInvestorPositionIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CInvestorPositionFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CInvestorPosition
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorPosition 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorPosition * pInvestorPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionLinkIterator是连接两个持仓表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionLinkIterator: public CInvestorPositionIterator
{
private:
	CInvestorPositionIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CInvestorPositionLinkIterator(CInvestorPositionIterator *pBaseIterator1,CInvestorPositionIterator *pBaseIterator2)
		:CInvestorPositionIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CInvestorPositionLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CInvestorPosition
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorPosition 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorPosition * pInvestorPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorAccountSingleIterator是至多返回一个账户实时资金表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountSingleIterator: public CInvestorAccountIterator
{
private:
	CInvestorAccount *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CInvestorAccountSingleIterator(CInvestorAccountFactory *pFactory,CInvestorAccount *pResult)
		:CInvestorAccountIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CInvestorAccountSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CInvestorAccount
	///@return	下一个满足条件CInvestorAccount，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccount *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorAccount 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccount * pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountPredict是判断一个账户实时资金表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountPredict
{
public:
	virtual ~CInvestorAccountPredict(){};

	///判断是否合法
	///@param	pInvestorAccount	要被判断的账户实时资金表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorAccount *pInvestorAccount)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountAndPredict是对两个账户实时资金表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountAndPredict : public CInvestorAccountPredict
{
private:
	CInvestorAccountPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorAccountAndPredict(CInvestorAccountPredict *p1, CInvestorAccountPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorAccountAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestorAccount	要被判断的账户实时资金表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorAccount *pInvestorAccount)
	{
		return m_p1->isValid(pInvestorAccount) && m_p2->isValid(pInvestorAccount);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountOrPredict是对两个账户实时资金表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountOrPredict : public CInvestorAccountPredict
{
private:
	CInvestorAccountPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorAccountOrPredict(CInvestorAccountPredict *p1, CInvestorAccountPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorAccountOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestorAccount	要被判断的账户实时资金表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorAccount *pInvestorAccount)
	{
		return m_p1->isValid(pInvestorAccount) || m_p2->isValid(pInvestorAccount);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountNotPredict是对一个账户实时资金表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountNotPredict : public CInvestorAccountPredict
{
private:
	CInvestorAccountPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CInvestorAccountNotPredict(CInvestorAccountPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CInvestorAccountNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pInvestorAccount	要被判断的账户实时资金表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorAccount *pInvestorAccount)
	{
		return !m_predict->isValid(pInvestorAccount);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountFilter是一个对已有的账户实时资金表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountFilter: public CInvestorAccountIterator
{
private:
	CInvestorAccountIterator *m_baseIterator;
	CInvestorAccountPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CInvestorAccountFilter(CInvestorAccountIterator *pBaseIterator, CInvestorAccountPredict *pPredict, bool continueResult=false)
		:CInvestorAccountIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CInvestorAccountFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CInvestorAccount
	///@return	下一个满足条件CInvestorAccount，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccount *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorAccount 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccount * pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountLinkIterator是连接两个账户实时资金表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountLinkIterator: public CInvestorAccountIterator
{
private:
	CInvestorAccountIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CInvestorAccountLinkIterator(CInvestorAccountIterator *pBaseIterator1,CInvestorAccountIterator *pBaseIterator2)
		:CInvestorAccountIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CInvestorAccountLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CInvestorAccount
	///@return	下一个满足条件CInvestorAccount，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccount *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorAccount 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccount * pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositSingleIterator是至多返回一个账户实时出入金表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositSingleIterator: public CInvestorAccountDepositIterator
{
private:
	CInvestorAccountDeposit *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CInvestorAccountDepositSingleIterator(CInvestorAccountDepositFactory *pFactory,CInvestorAccountDeposit *pResult)
		:CInvestorAccountDepositIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CInvestorAccountDepositSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CInvestorAccountDeposit
	///@return	下一个满足条件CInvestorAccountDeposit，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccountDeposit *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorAccountDeposit 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccountDeposit * pInvestorAccountDeposit,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositPredict是判断一个账户实时出入金表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositPredict
{
public:
	virtual ~CInvestorAccountDepositPredict(){};

	///判断是否合法
	///@param	pInvestorAccountDeposit	要被判断的账户实时出入金表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorAccountDeposit *pInvestorAccountDeposit)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositAndPredict是对两个账户实时出入金表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositAndPredict : public CInvestorAccountDepositPredict
{
private:
	CInvestorAccountDepositPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorAccountDepositAndPredict(CInvestorAccountDepositPredict *p1, CInvestorAccountDepositPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorAccountDepositAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestorAccountDeposit	要被判断的账户实时出入金表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return m_p1->isValid(pInvestorAccountDeposit) && m_p2->isValid(pInvestorAccountDeposit);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositOrPredict是对两个账户实时出入金表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositOrPredict : public CInvestorAccountDepositPredict
{
private:
	CInvestorAccountDepositPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorAccountDepositOrPredict(CInvestorAccountDepositPredict *p1, CInvestorAccountDepositPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorAccountDepositOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestorAccountDeposit	要被判断的账户实时出入金表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return m_p1->isValid(pInvestorAccountDeposit) || m_p2->isValid(pInvestorAccountDeposit);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositNotPredict是对一个账户实时出入金表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositNotPredict : public CInvestorAccountDepositPredict
{
private:
	CInvestorAccountDepositPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CInvestorAccountDepositNotPredict(CInvestorAccountDepositPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CInvestorAccountDepositNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pInvestorAccountDeposit	要被判断的账户实时出入金表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return !m_predict->isValid(pInvestorAccountDeposit);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositFilter是一个对已有的账户实时出入金表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositFilter: public CInvestorAccountDepositIterator
{
private:
	CInvestorAccountDepositIterator *m_baseIterator;
	CInvestorAccountDepositPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CInvestorAccountDepositFilter(CInvestorAccountDepositIterator *pBaseIterator, CInvestorAccountDepositPredict *pPredict, bool continueResult=false)
		:CInvestorAccountDepositIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CInvestorAccountDepositFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CInvestorAccountDeposit
	///@return	下一个满足条件CInvestorAccountDeposit，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccountDeposit *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorAccountDeposit 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccountDeposit * pInvestorAccountDeposit,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositLinkIterator是连接两个账户实时出入金表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositLinkIterator: public CInvestorAccountDepositIterator
{
private:
	CInvestorAccountDepositIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CInvestorAccountDepositLinkIterator(CInvestorAccountDepositIterator *pBaseIterator1,CInvestorAccountDepositIterator *pBaseIterator2)
		:CInvestorAccountDepositIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CInvestorAccountDepositLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CInvestorAccountDeposit
	///@return	下一个满足条件CInvestorAccountDeposit，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccountDeposit *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorAccountDeposit 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccountDeposit * pInvestorAccountDeposit,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CExchangeSingleIterator是至多返回一个交易所表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeSingleIterator: public CExchangeIterator
{
private:
	CExchange *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CExchangeSingleIterator(CExchangeFactory *pFactory,CExchange *pResult)
		:CExchangeIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CExchangeSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CExchange
	///@return	下一个满足条件CExchange，如果已经没有一个满足要求了，则返回NULL
	virtual CExchange *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pExchange 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableExchange * pExchange,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CExchangePredict是判断一个交易所表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangePredict
{
public:
	virtual ~CExchangePredict(){};

	///判断是否合法
	///@param	pExchange	要被判断的交易所表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CExchange *pExchange)=0;
};

/////////////////////////////////////////////////////////////////////////
///CExchangeAndPredict是对两个交易所表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeAndPredict : public CExchangePredict
{
private:
	CExchangePredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CExchangeAndPredict(CExchangePredict *p1, CExchangePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CExchangeAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pExchange	要被判断的交易所表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CExchange *pExchange)
	{
		return m_p1->isValid(pExchange) && m_p2->isValid(pExchange);
	}
};

/////////////////////////////////////////////////////////////////////////
///CExchangeOrPredict是对两个交易所表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeOrPredict : public CExchangePredict
{
private:
	CExchangePredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CExchangeOrPredict(CExchangePredict *p1, CExchangePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CExchangeOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pExchange	要被判断的交易所表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CExchange *pExchange)
	{
		return m_p1->isValid(pExchange) || m_p2->isValid(pExchange);
	}
};

/////////////////////////////////////////////////////////////////////////
///CExchangeNotPredict是对一个交易所表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeNotPredict : public CExchangePredict
{
private:
	CExchangePredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CExchangeNotPredict(CExchangePredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CExchangeNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pExchange	要被判断的交易所表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CExchange *pExchange)
	{
		return !m_predict->isValid(pExchange);
	}
};

/////////////////////////////////////////////////////////////////////////
///CExchangeFilter是一个对已有的交易所表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeFilter: public CExchangeIterator
{
private:
	CExchangeIterator *m_baseIterator;
	CExchangePredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CExchangeFilter(CExchangeIterator *pBaseIterator, CExchangePredict *pPredict, bool continueResult=false)
		:CExchangeIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CExchangeFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CExchange
	///@return	下一个满足条件CExchange，如果已经没有一个满足要求了，则返回NULL
	virtual CExchange *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pExchange 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableExchange * pExchange,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CExchangeLinkIterator是连接两个交易所表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeLinkIterator: public CExchangeIterator
{
private:
	CExchangeIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CExchangeLinkIterator(CExchangeIterator *pBaseIterator1,CExchangeIterator *pBaseIterator2)
		:CExchangeIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CExchangeLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CExchange
	///@return	下一个满足条件CExchange，如果已经没有一个满足要求了，则返回NULL
	virtual CExchange *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pExchange 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableExchange * pExchange,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CSeatSingleIterator是至多返回一个下单席位表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatSingleIterator: public CSeatIterator
{
private:
	CSeat *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CSeatSingleIterator(CSeatFactory *pFactory,CSeat *pResult)
		:CSeatIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CSeatSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CSeat
	///@return	下一个满足条件CSeat，如果已经没有一个满足要求了，则返回NULL
	virtual CSeat *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pSeat 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSeat * pSeat,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSeatPredict是判断一个下单席位表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatPredict
{
public:
	virtual ~CSeatPredict(){};

	///判断是否合法
	///@param	pSeat	要被判断的下单席位表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSeat *pSeat)=0;
};

/////////////////////////////////////////////////////////////////////////
///CSeatAndPredict是对两个下单席位表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatAndPredict : public CSeatPredict
{
private:
	CSeatPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CSeatAndPredict(CSeatPredict *p1, CSeatPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CSeatAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pSeat	要被判断的下单席位表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSeat *pSeat)
	{
		return m_p1->isValid(pSeat) && m_p2->isValid(pSeat);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSeatOrPredict是对两个下单席位表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatOrPredict : public CSeatPredict
{
private:
	CSeatPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CSeatOrPredict(CSeatPredict *p1, CSeatPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CSeatOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pSeat	要被判断的下单席位表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSeat *pSeat)
	{
		return m_p1->isValid(pSeat) || m_p2->isValid(pSeat);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSeatNotPredict是对一个下单席位表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatNotPredict : public CSeatPredict
{
private:
	CSeatPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CSeatNotPredict(CSeatPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CSeatNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pSeat	要被判断的下单席位表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSeat *pSeat)
	{
		return !m_predict->isValid(pSeat);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSeatFilter是一个对已有的下单席位表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatFilter: public CSeatIterator
{
private:
	CSeatIterator *m_baseIterator;
	CSeatPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CSeatFilter(CSeatIterator *pBaseIterator, CSeatPredict *pPredict, bool continueResult=false)
		:CSeatIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CSeatFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CSeat
	///@return	下一个满足条件CSeat，如果已经没有一个满足要求了，则返回NULL
	virtual CSeat *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pSeat 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSeat * pSeat,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSeatLinkIterator是连接两个下单席位表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatLinkIterator: public CSeatIterator
{
private:
	CSeatIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CSeatLinkIterator(CSeatIterator *pBaseIterator1,CSeatIterator *pBaseIterator2)
		:CSeatIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CSeatLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CSeat
	///@return	下一个满足条件CSeat，如果已经没有一个满足要求了，则返回NULL
	virtual CSeat *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pSeat 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSeat * pSeat,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInstrumentSingleIterator是至多返回一个期货合约表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentSingleIterator: public CInstrumentIterator
{
private:
	CInstrument *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CInstrumentSingleIterator(CInstrumentFactory *pFactory,CInstrument *pResult)
		:CInstrumentIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CInstrumentSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CInstrument
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrument *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInstrument 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrument * pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentPredict是判断一个期货合约表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentPredict
{
public:
	virtual ~CInstrumentPredict(){};

	///判断是否合法
	///@param	pInstrument	要被判断的期货合约表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInstrument *pInstrument)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentAndPredict是对两个期货合约表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentAndPredict : public CInstrumentPredict
{
private:
	CInstrumentPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInstrumentAndPredict(CInstrumentPredict *p1, CInstrumentPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInstrumentAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInstrument	要被判断的期货合约表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInstrument *pInstrument)
	{
		return m_p1->isValid(pInstrument) && m_p2->isValid(pInstrument);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentOrPredict是对两个期货合约表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentOrPredict : public CInstrumentPredict
{
private:
	CInstrumentPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInstrumentOrPredict(CInstrumentPredict *p1, CInstrumentPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInstrumentOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInstrument	要被判断的期货合约表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInstrument *pInstrument)
	{
		return m_p1->isValid(pInstrument) || m_p2->isValid(pInstrument);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentNotPredict是对一个期货合约表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentNotPredict : public CInstrumentPredict
{
private:
	CInstrumentPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CInstrumentNotPredict(CInstrumentPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CInstrumentNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pInstrument	要被判断的期货合约表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInstrument *pInstrument)
	{
		return !m_predict->isValid(pInstrument);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentFilter是一个对已有的期货合约表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentFilter: public CInstrumentIterator
{
private:
	CInstrumentIterator *m_baseIterator;
	CInstrumentPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CInstrumentFilter(CInstrumentIterator *pBaseIterator, CInstrumentPredict *pPredict, bool continueResult=false)
		:CInstrumentIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CInstrumentFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CInstrument
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrument *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInstrument 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrument * pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentLinkIterator是连接两个期货合约表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentLinkIterator: public CInstrumentIterator
{
private:
	CInstrumentIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CInstrumentLinkIterator(CInstrumentIterator *pBaseIterator1,CInstrumentIterator *pBaseIterator2)
		:CInstrumentIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CInstrumentLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CInstrument
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrument *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInstrument 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrument * pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailSingleIterator是至多返回一个期货组合合约明细表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailSingleIterator: public CCmbInstrumentDetailIterator
{
private:
	CCmbInstrumentDetail *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CCmbInstrumentDetailSingleIterator(CCmbInstrumentDetailFactory *pFactory,CCmbInstrumentDetail *pResult)
		:CCmbInstrumentDetailIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CCmbInstrumentDetailSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CCmbInstrumentDetail
	///@return	下一个满足条件CCmbInstrumentDetail，如果已经没有一个满足要求了，则返回NULL
	virtual CCmbInstrumentDetail *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pCmbInstrumentDetail 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableCmbInstrumentDetail * pCmbInstrumentDetail,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailPredict是判断一个期货组合合约明细表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailPredict
{
public:
	virtual ~CCmbInstrumentDetailPredict(){};

	///判断是否合法
	///@param	pCmbInstrumentDetail	要被判断的期货组合合约明细表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CCmbInstrumentDetail *pCmbInstrumentDetail)=0;
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailAndPredict是对两个期货组合合约明细表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailAndPredict : public CCmbInstrumentDetailPredict
{
private:
	CCmbInstrumentDetailPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CCmbInstrumentDetailAndPredict(CCmbInstrumentDetailPredict *p1, CCmbInstrumentDetailPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CCmbInstrumentDetailAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pCmbInstrumentDetail	要被判断的期货组合合约明细表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return m_p1->isValid(pCmbInstrumentDetail) && m_p2->isValid(pCmbInstrumentDetail);
	}
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailOrPredict是对两个期货组合合约明细表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailOrPredict : public CCmbInstrumentDetailPredict
{
private:
	CCmbInstrumentDetailPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CCmbInstrumentDetailOrPredict(CCmbInstrumentDetailPredict *p1, CCmbInstrumentDetailPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CCmbInstrumentDetailOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pCmbInstrumentDetail	要被判断的期货组合合约明细表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return m_p1->isValid(pCmbInstrumentDetail) || m_p2->isValid(pCmbInstrumentDetail);
	}
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailNotPredict是对一个期货组合合约明细表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailNotPredict : public CCmbInstrumentDetailPredict
{
private:
	CCmbInstrumentDetailPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CCmbInstrumentDetailNotPredict(CCmbInstrumentDetailPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CCmbInstrumentDetailNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pCmbInstrumentDetail	要被判断的期货组合合约明细表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return !m_predict->isValid(pCmbInstrumentDetail);
	}
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailFilter是一个对已有的期货组合合约明细表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailFilter: public CCmbInstrumentDetailIterator
{
private:
	CCmbInstrumentDetailIterator *m_baseIterator;
	CCmbInstrumentDetailPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CCmbInstrumentDetailFilter(CCmbInstrumentDetailIterator *pBaseIterator, CCmbInstrumentDetailPredict *pPredict, bool continueResult=false)
		:CCmbInstrumentDetailIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CCmbInstrumentDetailFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CCmbInstrumentDetail
	///@return	下一个满足条件CCmbInstrumentDetail，如果已经没有一个满足要求了，则返回NULL
	virtual CCmbInstrumentDetail *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pCmbInstrumentDetail 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableCmbInstrumentDetail * pCmbInstrumentDetail,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailLinkIterator是连接两个期货组合合约明细表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailLinkIterator: public CCmbInstrumentDetailIterator
{
private:
	CCmbInstrumentDetailIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CCmbInstrumentDetailLinkIterator(CCmbInstrumentDetailIterator *pBaseIterator1,CCmbInstrumentDetailIterator *pBaseIterator2)
		:CCmbInstrumentDetailIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CCmbInstrumentDetailLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CCmbInstrumentDetail
	///@return	下一个满足条件CCmbInstrumentDetail，如果已经没有一个满足要求了，则返回NULL
	virtual CCmbInstrumentDetail *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pCmbInstrumentDetail 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableCmbInstrumentDetail * pCmbInstrumentDetail,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CClientTradingIDSingleIterator是至多返回一个交易所客户编码表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDSingleIterator: public CClientTradingIDIterator
{
private:
	CClientTradingID *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CClientTradingIDSingleIterator(CClientTradingIDFactory *pFactory,CClientTradingID *pResult)
		:CClientTradingIDIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CClientTradingIDSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CClientTradingID
	///@return	下一个满足条件CClientTradingID，如果已经没有一个满足要求了，则返回NULL
	virtual CClientTradingID *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pClientTradingID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableClientTradingID * pClientTradingID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDPredict是判断一个交易所客户编码表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDPredict
{
public:
	virtual ~CClientTradingIDPredict(){};

	///判断是否合法
	///@param	pClientTradingID	要被判断的交易所客户编码表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientTradingID *pClientTradingID)=0;
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDAndPredict是对两个交易所客户编码表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDAndPredict : public CClientTradingIDPredict
{
private:
	CClientTradingIDPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CClientTradingIDAndPredict(CClientTradingIDPredict *p1, CClientTradingIDPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CClientTradingIDAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pClientTradingID	要被判断的交易所客户编码表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientTradingID *pClientTradingID)
	{
		return m_p1->isValid(pClientTradingID) && m_p2->isValid(pClientTradingID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDOrPredict是对两个交易所客户编码表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDOrPredict : public CClientTradingIDPredict
{
private:
	CClientTradingIDPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CClientTradingIDOrPredict(CClientTradingIDPredict *p1, CClientTradingIDPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CClientTradingIDOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pClientTradingID	要被判断的交易所客户编码表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientTradingID *pClientTradingID)
	{
		return m_p1->isValid(pClientTradingID) || m_p2->isValid(pClientTradingID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDNotPredict是对一个交易所客户编码表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDNotPredict : public CClientTradingIDPredict
{
private:
	CClientTradingIDPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CClientTradingIDNotPredict(CClientTradingIDPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CClientTradingIDNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pClientTradingID	要被判断的交易所客户编码表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientTradingID *pClientTradingID)
	{
		return !m_predict->isValid(pClientTradingID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDFilter是一个对已有的交易所客户编码表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDFilter: public CClientTradingIDIterator
{
private:
	CClientTradingIDIterator *m_baseIterator;
	CClientTradingIDPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CClientTradingIDFilter(CClientTradingIDIterator *pBaseIterator, CClientTradingIDPredict *pPredict, bool continueResult=false)
		:CClientTradingIDIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CClientTradingIDFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CClientTradingID
	///@return	下一个满足条件CClientTradingID，如果已经没有一个满足要求了，则返回NULL
	virtual CClientTradingID *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pClientTradingID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableClientTradingID * pClientTradingID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDLinkIterator是连接两个交易所客户编码表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDLinkIterator: public CClientTradingIDIterator
{
private:
	CClientTradingIDIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CClientTradingIDLinkIterator(CClientTradingIDIterator *pBaseIterator1,CClientTradingIDIterator *pBaseIterator2)
		:CClientTradingIDIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CClientTradingIDLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CClientTradingID
	///@return	下一个满足条件CClientTradingID，如果已经没有一个满足要求了，则返回NULL
	virtual CClientTradingID *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pClientTradingID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableClientTradingID * pClientTradingID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountOfClientTradingIDIterator是一个交易所客户编码表枚举器对应的帐户的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountOfClientTradingIDIterator: public CInvestorAccountIterator
{
private:
	CClientTradingIDIterator *m_baseIterator;
	CInvestorAccount *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorAccountOfClientTradingIDIterator(CInvestorAccountFactory *pFactory,CClientTradingIDIterator *pBaseIterator)
		:CInvestorAccountIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorAccountOfClientTradingIDIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorAccount
	///@return	下一个满足条件CInvestorAccount，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccount *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorAccount 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccount *pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorSingleIterator是至多返回一个投资者信息表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorSingleIterator: public CInvestorIterator
{
private:
	CInvestor *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CInvestorSingleIterator(CInvestorFactory *pFactory,CInvestor *pResult)
		:CInvestorIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CInvestorSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CInvestor
	///@return	下一个满足条件CInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestor *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestor 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestor * pInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPredict是判断一个投资者信息表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPredict
{
public:
	virtual ~CInvestorPredict(){};

	///判断是否合法
	///@param	pInvestor	要被判断的投资者信息表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestor *pInvestor)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAndPredict是对两个投资者信息表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAndPredict : public CInvestorPredict
{
private:
	CInvestorPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorAndPredict(CInvestorPredict *p1, CInvestorPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestor	要被判断的投资者信息表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestor *pInvestor)
	{
		return m_p1->isValid(pInvestor) && m_p2->isValid(pInvestor);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOrPredict是对两个投资者信息表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOrPredict : public CInvestorPredict
{
private:
	CInvestorPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorOrPredict(CInvestorPredict *p1, CInvestorPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestor	要被判断的投资者信息表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestor *pInvestor)
	{
		return m_p1->isValid(pInvestor) || m_p2->isValid(pInvestor);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorNotPredict是对一个投资者信息表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorNotPredict : public CInvestorPredict
{
private:
	CInvestorPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CInvestorNotPredict(CInvestorPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CInvestorNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pInvestor	要被判断的投资者信息表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestor *pInvestor)
	{
		return !m_predict->isValid(pInvestor);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFilter是一个对已有的投资者信息表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFilter: public CInvestorIterator
{
private:
	CInvestorIterator *m_baseIterator;
	CInvestorPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CInvestorFilter(CInvestorIterator *pBaseIterator, CInvestorPredict *pPredict, bool continueResult=false)
		:CInvestorIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CInvestorFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CInvestor
	///@return	下一个满足条件CInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestor *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestor 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestor * pInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorLinkIterator是连接两个投资者信息表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorLinkIterator: public CInvestorIterator
{
private:
	CInvestorIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CInvestorLinkIterator(CInvestorIterator *pBaseIterator1,CInvestorIterator *pBaseIterator2)
		:CInvestorIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CInvestorLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CInvestor
	///@return	下一个满足条件CInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestor *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestor 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestor * pInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorMarginSingleIterator是至多返回一个客户期货保证金率表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginSingleIterator: public CInvestorMarginIterator
{
private:
	CInvestorMargin *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CInvestorMarginSingleIterator(CInvestorMarginFactory *pFactory,CInvestorMargin *pResult)
		:CInvestorMarginIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CInvestorMarginSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CInvestorMargin
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorMargin *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorMargin 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorMargin * pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginPredict是判断一个客户期货保证金率表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginPredict
{
public:
	virtual ~CInvestorMarginPredict(){};

	///判断是否合法
	///@param	pInvestorMargin	要被判断的客户期货保证金率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorMargin *pInvestorMargin)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginAndPredict是对两个客户期货保证金率表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginAndPredict : public CInvestorMarginPredict
{
private:
	CInvestorMarginPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorMarginAndPredict(CInvestorMarginPredict *p1, CInvestorMarginPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorMarginAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestorMargin	要被判断的客户期货保证金率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorMargin *pInvestorMargin)
	{
		return m_p1->isValid(pInvestorMargin) && m_p2->isValid(pInvestorMargin);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginOrPredict是对两个客户期货保证金率表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginOrPredict : public CInvestorMarginPredict
{
private:
	CInvestorMarginPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorMarginOrPredict(CInvestorMarginPredict *p1, CInvestorMarginPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorMarginOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestorMargin	要被判断的客户期货保证金率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorMargin *pInvestorMargin)
	{
		return m_p1->isValid(pInvestorMargin) || m_p2->isValid(pInvestorMargin);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginNotPredict是对一个客户期货保证金率表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginNotPredict : public CInvestorMarginPredict
{
private:
	CInvestorMarginPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CInvestorMarginNotPredict(CInvestorMarginPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CInvestorMarginNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pInvestorMargin	要被判断的客户期货保证金率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorMargin *pInvestorMargin)
	{
		return !m_predict->isValid(pInvestorMargin);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginFilter是一个对已有的客户期货保证金率表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginFilter: public CInvestorMarginIterator
{
private:
	CInvestorMarginIterator *m_baseIterator;
	CInvestorMarginPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CInvestorMarginFilter(CInvestorMarginIterator *pBaseIterator, CInvestorMarginPredict *pPredict, bool continueResult=false)
		:CInvestorMarginIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CInvestorMarginFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CInvestorMargin
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorMargin *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorMargin 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorMargin * pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginLinkIterator是连接两个客户期货保证金率表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginLinkIterator: public CInvestorMarginIterator
{
private:
	CInvestorMarginIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CInvestorMarginLinkIterator(CInvestorMarginIterator *pBaseIterator1,CInvestorMarginIterator *pBaseIterator2)
		:CInvestorMarginIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CInvestorMarginLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CInvestorMargin
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorMargin *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorMargin 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorMargin * pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorFeeSingleIterator是至多返回一个客户手续费率表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeSingleIterator: public CInvestorFeeIterator
{
private:
	CInvestorFee *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CInvestorFeeSingleIterator(CInvestorFeeFactory *pFactory,CInvestorFee *pResult)
		:CInvestorFeeIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CInvestorFeeSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CInvestorFee
	///@return	下一个满足条件CInvestorFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorFee *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorFee 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorFee * pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeePredict是判断一个客户手续费率表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeePredict
{
public:
	virtual ~CInvestorFeePredict(){};

	///判断是否合法
	///@param	pInvestorFee	要被判断的客户手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorFee *pInvestorFee)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeAndPredict是对两个客户手续费率表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeAndPredict : public CInvestorFeePredict
{
private:
	CInvestorFeePredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorFeeAndPredict(CInvestorFeePredict *p1, CInvestorFeePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorFeeAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestorFee	要被判断的客户手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorFee *pInvestorFee)
	{
		return m_p1->isValid(pInvestorFee) && m_p2->isValid(pInvestorFee);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeOrPredict是对两个客户手续费率表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeOrPredict : public CInvestorFeePredict
{
private:
	CInvestorFeePredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorFeeOrPredict(CInvestorFeePredict *p1, CInvestorFeePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorFeeOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestorFee	要被判断的客户手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorFee *pInvestorFee)
	{
		return m_p1->isValid(pInvestorFee) || m_p2->isValid(pInvestorFee);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeNotPredict是对一个客户手续费率表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeNotPredict : public CInvestorFeePredict
{
private:
	CInvestorFeePredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CInvestorFeeNotPredict(CInvestorFeePredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CInvestorFeeNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pInvestorFee	要被判断的客户手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorFee *pInvestorFee)
	{
		return !m_predict->isValid(pInvestorFee);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeFilter是一个对已有的客户手续费率表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeFilter: public CInvestorFeeIterator
{
private:
	CInvestorFeeIterator *m_baseIterator;
	CInvestorFeePredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CInvestorFeeFilter(CInvestorFeeIterator *pBaseIterator, CInvestorFeePredict *pPredict, bool continueResult=false)
		:CInvestorFeeIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CInvestorFeeFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CInvestorFee
	///@return	下一个满足条件CInvestorFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorFee *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorFee 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorFee * pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeLinkIterator是连接两个客户手续费率表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeLinkIterator: public CInvestorFeeIterator
{
private:
	CInvestorFeeIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CInvestorFeeLinkIterator(CInvestorFeeIterator *pBaseIterator1,CInvestorFeeIterator *pBaseIterator2)
		:CInvestorFeeIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CInvestorFeeLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CInvestorFee
	///@return	下一个满足条件CInvestorFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorFee *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorFee 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorFee * pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CUserSingleIterator是至多返回一个用户表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSingleIterator: public CUserIterator
{
private:
	CUser *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CUserSingleIterator(CUserFactory *pFactory,CUser *pResult)
		:CUserIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CUserSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CUser
	///@return	下一个满足条件CUser，如果已经没有一个满足要求了，则返回NULL
	virtual CUser *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pUser 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUser * pUser,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserPredict是判断一个用户表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserPredict
{
public:
	virtual ~CUserPredict(){};

	///判断是否合法
	///@param	pUser	要被判断的用户表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUser *pUser)=0;
};

/////////////////////////////////////////////////////////////////////////
///CUserAndPredict是对两个用户表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserAndPredict : public CUserPredict
{
private:
	CUserPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CUserAndPredict(CUserPredict *p1, CUserPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CUserAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pUser	要被判断的用户表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUser *pUser)
	{
		return m_p1->isValid(pUser) && m_p2->isValid(pUser);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserOrPredict是对两个用户表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserOrPredict : public CUserPredict
{
private:
	CUserPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CUserOrPredict(CUserPredict *p1, CUserPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CUserOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pUser	要被判断的用户表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUser *pUser)
	{
		return m_p1->isValid(pUser) || m_p2->isValid(pUser);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserNotPredict是对一个用户表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserNotPredict : public CUserPredict
{
private:
	CUserPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CUserNotPredict(CUserPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CUserNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pUser	要被判断的用户表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUser *pUser)
	{
		return !m_predict->isValid(pUser);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserFilter是一个对已有的用户表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserFilter: public CUserIterator
{
private:
	CUserIterator *m_baseIterator;
	CUserPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CUserFilter(CUserIterator *pBaseIterator, CUserPredict *pPredict, bool continueResult=false)
		:CUserIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CUserFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CUser
	///@return	下一个满足条件CUser，如果已经没有一个满足要求了，则返回NULL
	virtual CUser *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pUser 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUser * pUser,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserLinkIterator是连接两个用户表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserLinkIterator: public CUserIterator
{
private:
	CUserIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CUserLinkIterator(CUserIterator *pBaseIterator1,CUserIterator *pBaseIterator2)
		:CUserIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CUserLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CUser
	///@return	下一个满足条件CUser，如果已经没有一个满足要求了，则返回NULL
	virtual CUser *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pUser 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUser * pUser,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CUserInvestorSingleIterator是至多返回一个用户投资者关系表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorSingleIterator: public CUserInvestorIterator
{
private:
	CUserInvestor *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CUserInvestorSingleIterator(CUserInvestorFactory *pFactory,CUserInvestor *pResult)
		:CUserInvestorIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CUserInvestorSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CUserInvestor
	///@return	下一个满足条件CUserInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CUserInvestor *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pUserInvestor 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserInvestor * pUserInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorPredict是判断一个用户投资者关系表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorPredict
{
public:
	virtual ~CUserInvestorPredict(){};

	///判断是否合法
	///@param	pUserInvestor	要被判断的用户投资者关系表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserInvestor *pUserInvestor)=0;
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorAndPredict是对两个用户投资者关系表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorAndPredict : public CUserInvestorPredict
{
private:
	CUserInvestorPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CUserInvestorAndPredict(CUserInvestorPredict *p1, CUserInvestorPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CUserInvestorAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pUserInvestor	要被判断的用户投资者关系表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserInvestor *pUserInvestor)
	{
		return m_p1->isValid(pUserInvestor) && m_p2->isValid(pUserInvestor);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorOrPredict是对两个用户投资者关系表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorOrPredict : public CUserInvestorPredict
{
private:
	CUserInvestorPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CUserInvestorOrPredict(CUserInvestorPredict *p1, CUserInvestorPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CUserInvestorOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pUserInvestor	要被判断的用户投资者关系表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserInvestor *pUserInvestor)
	{
		return m_p1->isValid(pUserInvestor) || m_p2->isValid(pUserInvestor);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorNotPredict是对一个用户投资者关系表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorNotPredict : public CUserInvestorPredict
{
private:
	CUserInvestorPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CUserInvestorNotPredict(CUserInvestorPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CUserInvestorNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pUserInvestor	要被判断的用户投资者关系表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserInvestor *pUserInvestor)
	{
		return !m_predict->isValid(pUserInvestor);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorFilter是一个对已有的用户投资者关系表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorFilter: public CUserInvestorIterator
{
private:
	CUserInvestorIterator *m_baseIterator;
	CUserInvestorPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CUserInvestorFilter(CUserInvestorIterator *pBaseIterator, CUserInvestorPredict *pPredict, bool continueResult=false)
		:CUserInvestorIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CUserInvestorFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CUserInvestor
	///@return	下一个满足条件CUserInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CUserInvestor *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pUserInvestor 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserInvestor * pUserInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorLinkIterator是连接两个用户投资者关系表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorLinkIterator: public CUserInvestorIterator
{
private:
	CUserInvestorIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CUserInvestorLinkIterator(CUserInvestorIterator *pBaseIterator1,CUserInvestorIterator *pBaseIterator2)
		:CUserInvestorIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CUserInvestorLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CUserInvestor
	///@return	下一个满足条件CUserInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CUserInvestor *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pUserInvestor 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserInvestor * pUserInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedSingleIterator是至多返回一个错单表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedSingleIterator: public COrderInsertFailedIterator
{
private:
	COrderInsertFailed *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	COrderInsertFailedSingleIterator(COrderInsertFailedFactory *pFactory,COrderInsertFailed *pResult)
		:COrderInsertFailedIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~COrderInsertFailedSingleIterator(void)
	{
	}

	///寻找下一个符合条件的COrderInsertFailed
	///@return	下一个满足条件COrderInsertFailed，如果已经没有一个满足要求了，则返回NULL
	virtual COrderInsertFailed *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pOrderInsertFailed 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrderInsertFailed * pOrderInsertFailed,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedPredict是判断一个错单表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedPredict
{
public:
	virtual ~COrderInsertFailedPredict(){};

	///判断是否合法
	///@param	pOrderInsertFailed	要被判断的错单表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed)=0;
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedAndPredict是对两个错单表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedAndPredict : public COrderInsertFailedPredict
{
private:
	COrderInsertFailedPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	COrderInsertFailedAndPredict(COrderInsertFailedPredict *p1, COrderInsertFailedPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~COrderInsertFailedAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pOrderInsertFailed	要被判断的错单表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed)
	{
		return m_p1->isValid(pOrderInsertFailed) && m_p2->isValid(pOrderInsertFailed);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedOrPredict是对两个错单表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedOrPredict : public COrderInsertFailedPredict
{
private:
	COrderInsertFailedPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	COrderInsertFailedOrPredict(COrderInsertFailedPredict *p1, COrderInsertFailedPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~COrderInsertFailedOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pOrderInsertFailed	要被判断的错单表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed)
	{
		return m_p1->isValid(pOrderInsertFailed) || m_p2->isValid(pOrderInsertFailed);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedNotPredict是对一个错单表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedNotPredict : public COrderInsertFailedPredict
{
private:
	COrderInsertFailedPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	COrderInsertFailedNotPredict(COrderInsertFailedPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~COrderInsertFailedNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pOrderInsertFailed	要被判断的错单表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderInsertFailed *pOrderInsertFailed)
	{
		return !m_predict->isValid(pOrderInsertFailed);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedFilter是一个对已有的错单表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedFilter: public COrderInsertFailedIterator
{
private:
	COrderInsertFailedIterator *m_baseIterator;
	COrderInsertFailedPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	COrderInsertFailedFilter(COrderInsertFailedIterator *pBaseIterator, COrderInsertFailedPredict *pPredict, bool continueResult=false)
		:COrderInsertFailedIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~COrderInsertFailedFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的COrderInsertFailed
	///@return	下一个满足条件COrderInsertFailed，如果已经没有一个满足要求了，则返回NULL
	virtual COrderInsertFailed *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pOrderInsertFailed 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrderInsertFailed * pOrderInsertFailed,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedLinkIterator是连接两个错单表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedLinkIterator: public COrderInsertFailedIterator
{
private:
	COrderInsertFailedIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	COrderInsertFailedLinkIterator(COrderInsertFailedIterator *pBaseIterator1,COrderInsertFailedIterator *pBaseIterator2)
		:COrderInsertFailedIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~COrderInsertFailedLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的COrderInsertFailed
	///@return	下一个满足条件COrderInsertFailed，如果已经没有一个满足要求了，则返回NULL
	virtual COrderInsertFailed *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pOrderInsertFailed 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrderInsertFailed * pOrderInsertFailed,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountOfOrderInsertFailedIterator是一个错单表枚举器对应的帐户的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountOfOrderInsertFailedIterator: public CInvestorAccountIterator
{
private:
	COrderInsertFailedIterator *m_baseIterator;
	CInvestorAccount *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorAccountOfOrderInsertFailedIterator(CInvestorAccountFactory *pFactory,COrderInsertFailedIterator *pBaseIterator)
		:CInvestorAccountIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorAccountOfOrderInsertFailedIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorAccount
	///@return	下一个满足条件CInvestorAccount，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccount *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorAccount 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccount *pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionOfOrderInsertFailedIterator是一个错单表枚举器对应的合约持仓信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionOfOrderInsertFailedIterator: public CInvestorPositionIterator
{
private:
	COrderInsertFailedIterator *m_baseIterator;
	CInvestorPosition *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorPositionOfOrderInsertFailedIterator(CInvestorPositionFactory *pFactory,COrderInsertFailedIterator *pBaseIterator)
		:CInvestorPositionIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorPositionOfOrderInsertFailedIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorPosition
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorPosition 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorPosition *pInvestorPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentOfOrderInsertFailedIterator是一个错单表枚举器对应的合约信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentOfOrderInsertFailedIterator: public CInstrumentIterator
{
private:
	COrderInsertFailedIterator *m_baseIterator;
	CInstrument *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInstrumentOfOrderInsertFailedIterator(CInstrumentFactory *pFactory,COrderInsertFailedIterator *pBaseIterator)
		:CInstrumentIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInstrumentOfOrderInsertFailedIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInstrument
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrument *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInstrument 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrument *pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginOfOrderInsertFailedIterator是一个错单表枚举器对应的投资者保证金率信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginOfOrderInsertFailedIterator: public CInvestorMarginIterator
{
private:
	COrderInsertFailedIterator *m_baseIterator;
	CInvestorMargin *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorMarginOfOrderInsertFailedIterator(CInvestorMarginFactory *pFactory,COrderInsertFailedIterator *pBaseIterator)
		:CInvestorMarginIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorMarginOfOrderInsertFailedIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorMargin
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorMargin *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorMargin 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorMargin *pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeOfOrderInsertFailedIterator是一个错单表枚举器对应的投资者手续费率信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeOfOrderInsertFailedIterator: public CInvestorFeeIterator
{
private:
	COrderInsertFailedIterator *m_baseIterator;
	CInvestorFee *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CInvestorFeeOfOrderInsertFailedIterator(CInvestorFeeFactory *pFactory,COrderInsertFailedIterator *pBaseIterator)
		:CInvestorFeeIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CInvestorFeeOfOrderInsertFailedIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CInvestorFee
	///@return	下一个满足条件CInvestorFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorFee *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorFee 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorFee *pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CUserTradingRightSingleIterator是至多返回一个用户交易权限表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightSingleIterator: public CUserTradingRightIterator
{
private:
	CUserTradingRight *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CUserTradingRightSingleIterator(CUserTradingRightFactory *pFactory,CUserTradingRight *pResult)
		:CUserTradingRightIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CUserTradingRightSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CUserTradingRight
	///@return	下一个满足条件CUserTradingRight，如果已经没有一个满足要求了，则返回NULL
	virtual CUserTradingRight *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pUserTradingRight 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserTradingRight * pUserTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightPredict是判断一个用户交易权限表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightPredict
{
public:
	virtual ~CUserTradingRightPredict(){};

	///判断是否合法
	///@param	pUserTradingRight	要被判断的用户交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserTradingRight *pUserTradingRight)=0;
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightAndPredict是对两个用户交易权限表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightAndPredict : public CUserTradingRightPredict
{
private:
	CUserTradingRightPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CUserTradingRightAndPredict(CUserTradingRightPredict *p1, CUserTradingRightPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CUserTradingRightAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pUserTradingRight	要被判断的用户交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserTradingRight *pUserTradingRight)
	{
		return m_p1->isValid(pUserTradingRight) && m_p2->isValid(pUserTradingRight);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightOrPredict是对两个用户交易权限表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightOrPredict : public CUserTradingRightPredict
{
private:
	CUserTradingRightPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CUserTradingRightOrPredict(CUserTradingRightPredict *p1, CUserTradingRightPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CUserTradingRightOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pUserTradingRight	要被判断的用户交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserTradingRight *pUserTradingRight)
	{
		return m_p1->isValid(pUserTradingRight) || m_p2->isValid(pUserTradingRight);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightNotPredict是对一个用户交易权限表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightNotPredict : public CUserTradingRightPredict
{
private:
	CUserTradingRightPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CUserTradingRightNotPredict(CUserTradingRightPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CUserTradingRightNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pUserTradingRight	要被判断的用户交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserTradingRight *pUserTradingRight)
	{
		return !m_predict->isValid(pUserTradingRight);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightFilter是一个对已有的用户交易权限表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightFilter: public CUserTradingRightIterator
{
private:
	CUserTradingRightIterator *m_baseIterator;
	CUserTradingRightPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CUserTradingRightFilter(CUserTradingRightIterator *pBaseIterator, CUserTradingRightPredict *pPredict, bool continueResult=false)
		:CUserTradingRightIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CUserTradingRightFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CUserTradingRight
	///@return	下一个满足条件CUserTradingRight，如果已经没有一个满足要求了，则返回NULL
	virtual CUserTradingRight *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pUserTradingRight 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserTradingRight * pUserTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightLinkIterator是连接两个用户交易权限表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightLinkIterator: public CUserTradingRightIterator
{
private:
	CUserTradingRightIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CUserTradingRightLinkIterator(CUserTradingRightIterator *pBaseIterator1,CUserTradingRightIterator *pBaseIterator2)
		:CUserTradingRightIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CUserTradingRightLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CUserTradingRight
	///@return	下一个满足条件CUserTradingRight，如果已经没有一个满足要求了，则返回NULL
	virtual CUserTradingRight *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pUserTradingRight 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserTradingRight * pUserTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CCurrentTimeSingleIterator是至多返回一个当前时间的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeSingleIterator: public CCurrentTimeIterator
{
private:
	CCurrentTime *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CCurrentTimeSingleIterator(CCurrentTimeFactory *pFactory,CCurrentTime *pResult)
		:CCurrentTimeIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CCurrentTimeSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CCurrentTime
	///@return	下一个满足条件CCurrentTime，如果已经没有一个满足要求了，则返回NULL
	virtual CCurrentTime *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pCurrentTime 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableCurrentTime * pCurrentTime,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimePredict是判断一个当前时间是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimePredict
{
public:
	virtual ~CCurrentTimePredict(){};

	///判断是否合法
	///@param	pCurrentTime	要被判断的当前时间
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CCurrentTime *pCurrentTime)=0;
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeAndPredict是对两个当前时间谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeAndPredict : public CCurrentTimePredict
{
private:
	CCurrentTimePredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CCurrentTimeAndPredict(CCurrentTimePredict *p1, CCurrentTimePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CCurrentTimeAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pCurrentTime	要被判断的当前时间
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CCurrentTime *pCurrentTime)
	{
		return m_p1->isValid(pCurrentTime) && m_p2->isValid(pCurrentTime);
	}
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeOrPredict是对两个当前时间谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeOrPredict : public CCurrentTimePredict
{
private:
	CCurrentTimePredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CCurrentTimeOrPredict(CCurrentTimePredict *p1, CCurrentTimePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CCurrentTimeOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pCurrentTime	要被判断的当前时间
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CCurrentTime *pCurrentTime)
	{
		return m_p1->isValid(pCurrentTime) || m_p2->isValid(pCurrentTime);
	}
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeNotPredict是对一个当前时间谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeNotPredict : public CCurrentTimePredict
{
private:
	CCurrentTimePredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CCurrentTimeNotPredict(CCurrentTimePredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CCurrentTimeNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pCurrentTime	要被判断的当前时间
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CCurrentTime *pCurrentTime)
	{
		return !m_predict->isValid(pCurrentTime);
	}
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeFilter是一个对已有的当前时间枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeFilter: public CCurrentTimeIterator
{
private:
	CCurrentTimeIterator *m_baseIterator;
	CCurrentTimePredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CCurrentTimeFilter(CCurrentTimeIterator *pBaseIterator, CCurrentTimePredict *pPredict, bool continueResult=false)
		:CCurrentTimeIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CCurrentTimeFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CCurrentTime
	///@return	下一个满足条件CCurrentTime，如果已经没有一个满足要求了，则返回NULL
	virtual CCurrentTime *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pCurrentTime 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableCurrentTime * pCurrentTime,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeLinkIterator是连接两个当前时间枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeLinkIterator: public CCurrentTimeIterator
{
private:
	CCurrentTimeIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CCurrentTimeLinkIterator(CCurrentTimeIterator *pBaseIterator1,CCurrentTimeIterator *pBaseIterator2)
		:CCurrentTimeIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CCurrentTimeLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CCurrentTime
	///@return	下一个满足条件CCurrentTime，如果已经没有一个满足要求了，则返回NULL
	virtual CCurrentTime *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pCurrentTime 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableCurrentTime * pCurrentTime,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CUserSessionSingleIterator是至多返回一个交易员在线会话的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionSingleIterator: public CUserSessionIterator
{
private:
	CUserSession *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CUserSessionSingleIterator(CUserSessionFactory *pFactory,CUserSession *pResult)
		:CUserSessionIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CUserSessionSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CUserSession
	///@return	下一个满足条件CUserSession，如果已经没有一个满足要求了，则返回NULL
	virtual CUserSession *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pUserSession 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserSession * pUserSession,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionPredict是判断一个交易员在线会话是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionPredict
{
public:
	virtual ~CUserSessionPredict(){};

	///判断是否合法
	///@param	pUserSession	要被判断的交易员在线会话
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserSession *pUserSession)=0;
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionAndPredict是对两个交易员在线会话谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionAndPredict : public CUserSessionPredict
{
private:
	CUserSessionPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CUserSessionAndPredict(CUserSessionPredict *p1, CUserSessionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CUserSessionAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pUserSession	要被判断的交易员在线会话
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserSession *pUserSession)
	{
		return m_p1->isValid(pUserSession) && m_p2->isValid(pUserSession);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionOrPredict是对两个交易员在线会话谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionOrPredict : public CUserSessionPredict
{
private:
	CUserSessionPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CUserSessionOrPredict(CUserSessionPredict *p1, CUserSessionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CUserSessionOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pUserSession	要被判断的交易员在线会话
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserSession *pUserSession)
	{
		return m_p1->isValid(pUserSession) || m_p2->isValid(pUserSession);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionNotPredict是对一个交易员在线会话谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionNotPredict : public CUserSessionPredict
{
private:
	CUserSessionPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CUserSessionNotPredict(CUserSessionPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CUserSessionNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pUserSession	要被判断的交易员在线会话
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserSession *pUserSession)
	{
		return !m_predict->isValid(pUserSession);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionFilter是一个对已有的交易员在线会话枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionFilter: public CUserSessionIterator
{
private:
	CUserSessionIterator *m_baseIterator;
	CUserSessionPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CUserSessionFilter(CUserSessionIterator *pBaseIterator, CUserSessionPredict *pPredict, bool continueResult=false)
		:CUserSessionIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CUserSessionFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CUserSession
	///@return	下一个满足条件CUserSession，如果已经没有一个满足要求了，则返回NULL
	virtual CUserSession *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pUserSession 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserSession * pUserSession,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionLinkIterator是连接两个交易员在线会话枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionLinkIterator: public CUserSessionIterator
{
private:
	CUserSessionIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CUserSessionLinkIterator(CUserSessionIterator *pBaseIterator1,CUserSessionIterator *pBaseIterator2)
		:CUserSessionIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CUserSessionLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CUserSession
	///@return	下一个满足条件CUserSession，如果已经没有一个满足要求了，则返回NULL
	virtual CUserSession *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pUserSession 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserSession * pUserSession,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDSingleIterator是至多返回一个最大本地报单号的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDSingleIterator: public CMaxLocalIDIterator
{
private:
	CMaxLocalID *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CMaxLocalIDSingleIterator(CMaxLocalIDFactory *pFactory,CMaxLocalID *pResult)
		:CMaxLocalIDIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CMaxLocalIDSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CMaxLocalID
	///@return	下一个满足条件CMaxLocalID，如果已经没有一个满足要求了，则返回NULL
	virtual CMaxLocalID *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pMaxLocalID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableMaxLocalID * pMaxLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDPredict是判断一个最大本地报单号是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDPredict
{
public:
	virtual ~CMaxLocalIDPredict(){};

	///判断是否合法
	///@param	pMaxLocalID	要被判断的最大本地报单号
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CMaxLocalID *pMaxLocalID)=0;
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDAndPredict是对两个最大本地报单号谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDAndPredict : public CMaxLocalIDPredict
{
private:
	CMaxLocalIDPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CMaxLocalIDAndPredict(CMaxLocalIDPredict *p1, CMaxLocalIDPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CMaxLocalIDAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pMaxLocalID	要被判断的最大本地报单号
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CMaxLocalID *pMaxLocalID)
	{
		return m_p1->isValid(pMaxLocalID) && m_p2->isValid(pMaxLocalID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDOrPredict是对两个最大本地报单号谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDOrPredict : public CMaxLocalIDPredict
{
private:
	CMaxLocalIDPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CMaxLocalIDOrPredict(CMaxLocalIDPredict *p1, CMaxLocalIDPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CMaxLocalIDOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pMaxLocalID	要被判断的最大本地报单号
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CMaxLocalID *pMaxLocalID)
	{
		return m_p1->isValid(pMaxLocalID) || m_p2->isValid(pMaxLocalID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDNotPredict是对一个最大本地报单号谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDNotPredict : public CMaxLocalIDPredict
{
private:
	CMaxLocalIDPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CMaxLocalIDNotPredict(CMaxLocalIDPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CMaxLocalIDNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pMaxLocalID	要被判断的最大本地报单号
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CMaxLocalID *pMaxLocalID)
	{
		return !m_predict->isValid(pMaxLocalID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDFilter是一个对已有的最大本地报单号枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDFilter: public CMaxLocalIDIterator
{
private:
	CMaxLocalIDIterator *m_baseIterator;
	CMaxLocalIDPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CMaxLocalIDFilter(CMaxLocalIDIterator *pBaseIterator, CMaxLocalIDPredict *pPredict, bool continueResult=false)
		:CMaxLocalIDIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CMaxLocalIDFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CMaxLocalID
	///@return	下一个满足条件CMaxLocalID，如果已经没有一个满足要求了，则返回NULL
	virtual CMaxLocalID *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pMaxLocalID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableMaxLocalID * pMaxLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDLinkIterator是连接两个最大本地报单号枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDLinkIterator: public CMaxLocalIDIterator
{
private:
	CMaxLocalIDIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CMaxLocalIDLinkIterator(CMaxLocalIDIterator *pBaseIterator1,CMaxLocalIDIterator *pBaseIterator2)
		:CMaxLocalIDIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CMaxLocalIDLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CMaxLocalID
	///@return	下一个满足条件CMaxLocalID，如果已经没有一个满足要求了，则返回NULL
	virtual CMaxLocalID *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pMaxLocalID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableMaxLocalID * pMaxLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDSingleIterator是至多返回一个用户本地报单号的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDSingleIterator: public CBrkUserIDLocalIDIterator
{
private:
	CBrkUserIDLocalID *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CBrkUserIDLocalIDSingleIterator(CBrkUserIDLocalIDFactory *pFactory,CBrkUserIDLocalID *pResult)
		:CBrkUserIDLocalIDIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CBrkUserIDLocalIDSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CBrkUserIDLocalID
	///@return	下一个满足条件CBrkUserIDLocalID，如果已经没有一个满足要求了，则返回NULL
	virtual CBrkUserIDLocalID *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pBrkUserIDLocalID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableBrkUserIDLocalID * pBrkUserIDLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDPredict是判断一个用户本地报单号是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDPredict
{
public:
	virtual ~CBrkUserIDLocalIDPredict(){};

	///判断是否合法
	///@param	pBrkUserIDLocalID	要被判断的用户本地报单号
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CBrkUserIDLocalID *pBrkUserIDLocalID)=0;
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDAndPredict是对两个用户本地报单号谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDAndPredict : public CBrkUserIDLocalIDPredict
{
private:
	CBrkUserIDLocalIDPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CBrkUserIDLocalIDAndPredict(CBrkUserIDLocalIDPredict *p1, CBrkUserIDLocalIDPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CBrkUserIDLocalIDAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pBrkUserIDLocalID	要被判断的用户本地报单号
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return m_p1->isValid(pBrkUserIDLocalID) && m_p2->isValid(pBrkUserIDLocalID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDOrPredict是对两个用户本地报单号谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDOrPredict : public CBrkUserIDLocalIDPredict
{
private:
	CBrkUserIDLocalIDPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CBrkUserIDLocalIDOrPredict(CBrkUserIDLocalIDPredict *p1, CBrkUserIDLocalIDPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CBrkUserIDLocalIDOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pBrkUserIDLocalID	要被判断的用户本地报单号
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return m_p1->isValid(pBrkUserIDLocalID) || m_p2->isValid(pBrkUserIDLocalID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDNotPredict是对一个用户本地报单号谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDNotPredict : public CBrkUserIDLocalIDPredict
{
private:
	CBrkUserIDLocalIDPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CBrkUserIDLocalIDNotPredict(CBrkUserIDLocalIDPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CBrkUserIDLocalIDNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pBrkUserIDLocalID	要被判断的用户本地报单号
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return !m_predict->isValid(pBrkUserIDLocalID);
	}
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDFilter是一个对已有的用户本地报单号枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDFilter: public CBrkUserIDLocalIDIterator
{
private:
	CBrkUserIDLocalIDIterator *m_baseIterator;
	CBrkUserIDLocalIDPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CBrkUserIDLocalIDFilter(CBrkUserIDLocalIDIterator *pBaseIterator, CBrkUserIDLocalIDPredict *pPredict, bool continueResult=false)
		:CBrkUserIDLocalIDIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CBrkUserIDLocalIDFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CBrkUserIDLocalID
	///@return	下一个满足条件CBrkUserIDLocalID，如果已经没有一个满足要求了，则返回NULL
	virtual CBrkUserIDLocalID *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pBrkUserIDLocalID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableBrkUserIDLocalID * pBrkUserIDLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDLinkIterator是连接两个用户本地报单号枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDLinkIterator: public CBrkUserIDLocalIDIterator
{
private:
	CBrkUserIDLocalIDIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CBrkUserIDLocalIDLinkIterator(CBrkUserIDLocalIDIterator *pBaseIterator1,CBrkUserIDLocalIDIterator *pBaseIterator2)
		:CBrkUserIDLocalIDIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CBrkUserIDLocalIDLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CBrkUserIDLocalID
	///@return	下一个满足条件CBrkUserIDLocalID，如果已经没有一个满足要求了，则返回NULL
	virtual CBrkUserIDLocalID *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pBrkUserIDLocalID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableBrkUserIDLocalID * pBrkUserIDLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderOfBrkUserIDLocalIDIterator是一个用户本地报单号枚举器对应的报单的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderOfBrkUserIDLocalIDIterator: public CPreOrderIterator
{
private:
	CBrkUserIDLocalIDIterator *m_baseIterator;
	CPreOrder *m_current;
public:
	///构造函数
	///@param	pFactory	要使用的对象工厂
	///@param	pBaseIterator	基础的枚举器
	CPreOrderOfBrkUserIDLocalIDIterator(CPreOrderFactory *pFactory,CBrkUserIDLocalIDIterator *pBaseIterator)
		:CPreOrderIterator(pFactory)
	{
		m_baseIterator=pBaseIterator;
		m_current=NULL;
	}
	
	///析构函数
	virtual ~CPreOrderOfBrkUserIDLocalIDIterator(void)
	{
		m_baseIterator->free();
	}

	///寻找下一个符合条件的CPreOrder
	///@return	下一个满足条件CPreOrder，如果已经没有一个满足要求了，则返回NULL
	virtual CPreOrder *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pPreOrder 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteablePreOrder *pPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionSingleIterator是至多返回一个客户合约组持仓表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionSingleIterator: public CPartClientInsGroupPositionIterator
{
private:
	CPartClientInsGroupPosition *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CPartClientInsGroupPositionSingleIterator(CPartClientInsGroupPositionFactory *pFactory,CPartClientInsGroupPosition *pResult)
		:CPartClientInsGroupPositionIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CPartClientInsGroupPositionSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CPartClientInsGroupPosition
	///@return	下一个满足条件CPartClientInsGroupPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CPartClientInsGroupPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pPartClientInsGroupPosition 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteablePartClientInsGroupPosition * pPartClientInsGroupPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionPredict是判断一个客户合约组持仓表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionPredict
{
public:
	virtual ~CPartClientInsGroupPositionPredict(){};

	///判断是否合法
	///@param	pPartClientInsGroupPosition	要被判断的客户合约组持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition)=0;
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionAndPredict是对两个客户合约组持仓表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionAndPredict : public CPartClientInsGroupPositionPredict
{
private:
	CPartClientInsGroupPositionPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CPartClientInsGroupPositionAndPredict(CPartClientInsGroupPositionPredict *p1, CPartClientInsGroupPositionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CPartClientInsGroupPositionAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pPartClientInsGroupPosition	要被判断的客户合约组持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return m_p1->isValid(pPartClientInsGroupPosition) && m_p2->isValid(pPartClientInsGroupPosition);
	}
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionOrPredict是对两个客户合约组持仓表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionOrPredict : public CPartClientInsGroupPositionPredict
{
private:
	CPartClientInsGroupPositionPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CPartClientInsGroupPositionOrPredict(CPartClientInsGroupPositionPredict *p1, CPartClientInsGroupPositionPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CPartClientInsGroupPositionOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pPartClientInsGroupPosition	要被判断的客户合约组持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return m_p1->isValid(pPartClientInsGroupPosition) || m_p2->isValid(pPartClientInsGroupPosition);
	}
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionNotPredict是对一个客户合约组持仓表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionNotPredict : public CPartClientInsGroupPositionPredict
{
private:
	CPartClientInsGroupPositionPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CPartClientInsGroupPositionNotPredict(CPartClientInsGroupPositionPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CPartClientInsGroupPositionNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pPartClientInsGroupPosition	要被判断的客户合约组持仓表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return !m_predict->isValid(pPartClientInsGroupPosition);
	}
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionFilter是一个对已有的客户合约组持仓表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionFilter: public CPartClientInsGroupPositionIterator
{
private:
	CPartClientInsGroupPositionIterator *m_baseIterator;
	CPartClientInsGroupPositionPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CPartClientInsGroupPositionFilter(CPartClientInsGroupPositionIterator *pBaseIterator, CPartClientInsGroupPositionPredict *pPredict, bool continueResult=false)
		:CPartClientInsGroupPositionIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CPartClientInsGroupPositionFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CPartClientInsGroupPosition
	///@return	下一个满足条件CPartClientInsGroupPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CPartClientInsGroupPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pPartClientInsGroupPosition 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteablePartClientInsGroupPosition * pPartClientInsGroupPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionLinkIterator是连接两个客户合约组持仓表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionLinkIterator: public CPartClientInsGroupPositionIterator
{
private:
	CPartClientInsGroupPositionIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CPartClientInsGroupPositionLinkIterator(CPartClientInsGroupPositionIterator *pBaseIterator1,CPartClientInsGroupPositionIterator *pBaseIterator2)
		:CPartClientInsGroupPositionIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CPartClientInsGroupPositionLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CPartClientInsGroupPosition
	///@return	下一个满足条件CPartClientInsGroupPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CPartClientInsGroupPosition *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pPartClientInsGroupPosition 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteablePartClientInsGroupPosition * pPartClientInsGroupPosition,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeSingleIterator是至多返回一个交易编码组合保证金类型的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeSingleIterator: public CClientMarginCombTypeIterator
{
private:
	CClientMarginCombType *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CClientMarginCombTypeSingleIterator(CClientMarginCombTypeFactory *pFactory,CClientMarginCombType *pResult)
		:CClientMarginCombTypeIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CClientMarginCombTypeSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CClientMarginCombType
	///@return	下一个满足条件CClientMarginCombType，如果已经没有一个满足要求了，则返回NULL
	virtual CClientMarginCombType *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pClientMarginCombType 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableClientMarginCombType * pClientMarginCombType,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypePredict是判断一个交易编码组合保证金类型是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypePredict
{
public:
	virtual ~CClientMarginCombTypePredict(){};

	///判断是否合法
	///@param	pClientMarginCombType	要被判断的交易编码组合保证金类型
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientMarginCombType *pClientMarginCombType)=0;
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeAndPredict是对两个交易编码组合保证金类型谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeAndPredict : public CClientMarginCombTypePredict
{
private:
	CClientMarginCombTypePredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CClientMarginCombTypeAndPredict(CClientMarginCombTypePredict *p1, CClientMarginCombTypePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CClientMarginCombTypeAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pClientMarginCombType	要被判断的交易编码组合保证金类型
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientMarginCombType *pClientMarginCombType)
	{
		return m_p1->isValid(pClientMarginCombType) && m_p2->isValid(pClientMarginCombType);
	}
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeOrPredict是对两个交易编码组合保证金类型谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeOrPredict : public CClientMarginCombTypePredict
{
private:
	CClientMarginCombTypePredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CClientMarginCombTypeOrPredict(CClientMarginCombTypePredict *p1, CClientMarginCombTypePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CClientMarginCombTypeOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pClientMarginCombType	要被判断的交易编码组合保证金类型
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientMarginCombType *pClientMarginCombType)
	{
		return m_p1->isValid(pClientMarginCombType) || m_p2->isValid(pClientMarginCombType);
	}
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeNotPredict是对一个交易编码组合保证金类型谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeNotPredict : public CClientMarginCombTypePredict
{
private:
	CClientMarginCombTypePredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CClientMarginCombTypeNotPredict(CClientMarginCombTypePredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CClientMarginCombTypeNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pClientMarginCombType	要被判断的交易编码组合保证金类型
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CClientMarginCombType *pClientMarginCombType)
	{
		return !m_predict->isValid(pClientMarginCombType);
	}
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeFilter是一个对已有的交易编码组合保证金类型枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeFilter: public CClientMarginCombTypeIterator
{
private:
	CClientMarginCombTypeIterator *m_baseIterator;
	CClientMarginCombTypePredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CClientMarginCombTypeFilter(CClientMarginCombTypeIterator *pBaseIterator, CClientMarginCombTypePredict *pPredict, bool continueResult=false)
		:CClientMarginCombTypeIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CClientMarginCombTypeFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CClientMarginCombType
	///@return	下一个满足条件CClientMarginCombType，如果已经没有一个满足要求了，则返回NULL
	virtual CClientMarginCombType *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pClientMarginCombType 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableClientMarginCombType * pClientMarginCombType,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeLinkIterator是连接两个交易编码组合保证金类型枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeLinkIterator: public CClientMarginCombTypeIterator
{
private:
	CClientMarginCombTypeIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CClientMarginCombTypeLinkIterator(CClientMarginCombTypeIterator *pBaseIterator1,CClientMarginCombTypeIterator *pBaseIterator2)
		:CClientMarginCombTypeIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CClientMarginCombTypeLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CClientMarginCombType
	///@return	下一个满足条件CClientMarginCombType，如果已经没有一个满足要求了，则返回NULL
	virtual CClientMarginCombType *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pClientMarginCombType 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableClientMarginCombType * pClientMarginCombType,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupSingleIterator是至多返回一个合约和合约组关系的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupSingleIterator: public CInstrumentGroupIterator
{
private:
	CInstrumentGroup *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CInstrumentGroupSingleIterator(CInstrumentGroupFactory *pFactory,CInstrumentGroup *pResult)
		:CInstrumentGroupIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CInstrumentGroupSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CInstrumentGroup
	///@return	下一个满足条件CInstrumentGroup，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrumentGroup *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInstrumentGroup 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrumentGroup * pInstrumentGroup,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupPredict是判断一个合约和合约组关系是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupPredict
{
public:
	virtual ~CInstrumentGroupPredict(){};

	///判断是否合法
	///@param	pInstrumentGroup	要被判断的合约和合约组关系
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInstrumentGroup *pInstrumentGroup)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupAndPredict是对两个合约和合约组关系谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupAndPredict : public CInstrumentGroupPredict
{
private:
	CInstrumentGroupPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInstrumentGroupAndPredict(CInstrumentGroupPredict *p1, CInstrumentGroupPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInstrumentGroupAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInstrumentGroup	要被判断的合约和合约组关系
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInstrumentGroup *pInstrumentGroup)
	{
		return m_p1->isValid(pInstrumentGroup) && m_p2->isValid(pInstrumentGroup);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupOrPredict是对两个合约和合约组关系谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupOrPredict : public CInstrumentGroupPredict
{
private:
	CInstrumentGroupPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInstrumentGroupOrPredict(CInstrumentGroupPredict *p1, CInstrumentGroupPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInstrumentGroupOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInstrumentGroup	要被判断的合约和合约组关系
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInstrumentGroup *pInstrumentGroup)
	{
		return m_p1->isValid(pInstrumentGroup) || m_p2->isValid(pInstrumentGroup);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupNotPredict是对一个合约和合约组关系谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupNotPredict : public CInstrumentGroupPredict
{
private:
	CInstrumentGroupPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CInstrumentGroupNotPredict(CInstrumentGroupPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CInstrumentGroupNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pInstrumentGroup	要被判断的合约和合约组关系
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInstrumentGroup *pInstrumentGroup)
	{
		return !m_predict->isValid(pInstrumentGroup);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupFilter是一个对已有的合约和合约组关系枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupFilter: public CInstrumentGroupIterator
{
private:
	CInstrumentGroupIterator *m_baseIterator;
	CInstrumentGroupPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CInstrumentGroupFilter(CInstrumentGroupIterator *pBaseIterator, CInstrumentGroupPredict *pPredict, bool continueResult=false)
		:CInstrumentGroupIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CInstrumentGroupFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CInstrumentGroup
	///@return	下一个满足条件CInstrumentGroup，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrumentGroup *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInstrumentGroup 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrumentGroup * pInstrumentGroup,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupLinkIterator是连接两个合约和合约组关系枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupLinkIterator: public CInstrumentGroupIterator
{
private:
	CInstrumentGroupIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CInstrumentGroupLinkIterator(CInstrumentGroupIterator *pBaseIterator1,CInstrumentGroupIterator *pBaseIterator2)
		:CInstrumentGroupIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CInstrumentGroupLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CInstrumentGroup
	///@return	下一个满足条件CInstrumentGroup，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrumentGroup *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInstrumentGroup 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrumentGroup * pInstrumentGroup,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateSingleIterator是至多返回一个金交所递延费率表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateSingleIterator: public CSGEDeferRateIterator
{
private:
	CSGEDeferRate *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CSGEDeferRateSingleIterator(CSGEDeferRateFactory *pFactory,CSGEDeferRate *pResult)
		:CSGEDeferRateIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CSGEDeferRateSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CSGEDeferRate
	///@return	下一个满足条件CSGEDeferRate，如果已经没有一个满足要求了，则返回NULL
	virtual CSGEDeferRate *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pSGEDeferRate 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSGEDeferRate * pSGEDeferRate,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRatePredict是判断一个金交所递延费率表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRatePredict
{
public:
	virtual ~CSGEDeferRatePredict(){};

	///判断是否合法
	///@param	pSGEDeferRate	要被判断的金交所递延费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSGEDeferRate *pSGEDeferRate)=0;
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateAndPredict是对两个金交所递延费率表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateAndPredict : public CSGEDeferRatePredict
{
private:
	CSGEDeferRatePredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CSGEDeferRateAndPredict(CSGEDeferRatePredict *p1, CSGEDeferRatePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CSGEDeferRateAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pSGEDeferRate	要被判断的金交所递延费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSGEDeferRate *pSGEDeferRate)
	{
		return m_p1->isValid(pSGEDeferRate) && m_p2->isValid(pSGEDeferRate);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateOrPredict是对两个金交所递延费率表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateOrPredict : public CSGEDeferRatePredict
{
private:
	CSGEDeferRatePredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CSGEDeferRateOrPredict(CSGEDeferRatePredict *p1, CSGEDeferRatePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CSGEDeferRateOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pSGEDeferRate	要被判断的金交所递延费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSGEDeferRate *pSGEDeferRate)
	{
		return m_p1->isValid(pSGEDeferRate) || m_p2->isValid(pSGEDeferRate);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateNotPredict是对一个金交所递延费率表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateNotPredict : public CSGEDeferRatePredict
{
private:
	CSGEDeferRatePredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CSGEDeferRateNotPredict(CSGEDeferRatePredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CSGEDeferRateNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pSGEDeferRate	要被判断的金交所递延费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSGEDeferRate *pSGEDeferRate)
	{
		return !m_predict->isValid(pSGEDeferRate);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateFilter是一个对已有的金交所递延费率表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateFilter: public CSGEDeferRateIterator
{
private:
	CSGEDeferRateIterator *m_baseIterator;
	CSGEDeferRatePredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CSGEDeferRateFilter(CSGEDeferRateIterator *pBaseIterator, CSGEDeferRatePredict *pPredict, bool continueResult=false)
		:CSGEDeferRateIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CSGEDeferRateFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CSGEDeferRate
	///@return	下一个满足条件CSGEDeferRate，如果已经没有一个满足要求了，则返回NULL
	virtual CSGEDeferRate *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pSGEDeferRate 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSGEDeferRate * pSGEDeferRate,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateLinkIterator是连接两个金交所递延费率表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateLinkIterator: public CSGEDeferRateIterator
{
private:
	CSGEDeferRateIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CSGEDeferRateLinkIterator(CSGEDeferRateIterator *pBaseIterator1,CSGEDeferRateIterator *pBaseIterator2)
		:CSGEDeferRateIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CSGEDeferRateLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CSGEDeferRate
	///@return	下一个满足条件CSGEDeferRate，如果已经没有一个满足要求了，则返回NULL
	virtual CSGEDeferRate *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pSGEDeferRate 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSGEDeferRate * pSGEDeferRate,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightSingleIterator是至多返回一个投资者交易权限表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightSingleIterator: public CInvestorTradingRightIterator
{
private:
	CInvestorTradingRight *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CInvestorTradingRightSingleIterator(CInvestorTradingRightFactory *pFactory,CInvestorTradingRight *pResult)
		:CInvestorTradingRightIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CInvestorTradingRightSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CInvestorTradingRight
	///@return	下一个满足条件CInvestorTradingRight，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorTradingRight *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorTradingRight 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorTradingRight * pInvestorTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightPredict是判断一个投资者交易权限表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightPredict
{
public:
	virtual ~CInvestorTradingRightPredict(){};

	///判断是否合法
	///@param	pInvestorTradingRight	要被判断的投资者交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightAndPredict是对两个投资者交易权限表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightAndPredict : public CInvestorTradingRightPredict
{
private:
	CInvestorTradingRightPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorTradingRightAndPredict(CInvestorTradingRightPredict *p1, CInvestorTradingRightPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorTradingRightAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestorTradingRight	要被判断的投资者交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight)
	{
		return m_p1->isValid(pInvestorTradingRight) && m_p2->isValid(pInvestorTradingRight);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightOrPredict是对两个投资者交易权限表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightOrPredict : public CInvestorTradingRightPredict
{
private:
	CInvestorTradingRightPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorTradingRightOrPredict(CInvestorTradingRightPredict *p1, CInvestorTradingRightPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorTradingRightOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestorTradingRight	要被判断的投资者交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight)
	{
		return m_p1->isValid(pInvestorTradingRight) || m_p2->isValid(pInvestorTradingRight);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightNotPredict是对一个投资者交易权限表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightNotPredict : public CInvestorTradingRightPredict
{
private:
	CInvestorTradingRightPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CInvestorTradingRightNotPredict(CInvestorTradingRightPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CInvestorTradingRightNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pInvestorTradingRight	要被判断的投资者交易权限表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorTradingRight *pInvestorTradingRight)
	{
		return !m_predict->isValid(pInvestorTradingRight);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightFilter是一个对已有的投资者交易权限表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightFilter: public CInvestorTradingRightIterator
{
private:
	CInvestorTradingRightIterator *m_baseIterator;
	CInvestorTradingRightPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CInvestorTradingRightFilter(CInvestorTradingRightIterator *pBaseIterator, CInvestorTradingRightPredict *pPredict, bool continueResult=false)
		:CInvestorTradingRightIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CInvestorTradingRightFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CInvestorTradingRight
	///@return	下一个满足条件CInvestorTradingRight，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorTradingRight *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorTradingRight 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorTradingRight * pInvestorTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightLinkIterator是连接两个投资者交易权限表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightLinkIterator: public CInvestorTradingRightIterator
{
private:
	CInvestorTradingRightIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CInvestorTradingRightLinkIterator(CInvestorTradingRightIterator *pBaseIterator1,CInvestorTradingRightIterator *pBaseIterator2)
		:CInvestorTradingRightIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CInvestorTradingRightLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CInvestorTradingRight
	///@return	下一个满足条件CInvestorTradingRight，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorTradingRight *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorTradingRight 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorTradingRight * pInvestorTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CUserIPSingleIterator是至多返回一个交易员IP地址的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPSingleIterator: public CUserIPIterator
{
private:
	CUserIP *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CUserIPSingleIterator(CUserIPFactory *pFactory,CUserIP *pResult)
		:CUserIPIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CUserIPSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CUserIP
	///@return	下一个满足条件CUserIP，如果已经没有一个满足要求了，则返回NULL
	virtual CUserIP *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pUserIP 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserIP * pUserIP,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserIPPredict是判断一个交易员IP地址是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPPredict
{
public:
	virtual ~CUserIPPredict(){};

	///判断是否合法
	///@param	pUserIP	要被判断的交易员IP地址
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserIP *pUserIP)=0;
};

/////////////////////////////////////////////////////////////////////////
///CUserIPAndPredict是对两个交易员IP地址谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPAndPredict : public CUserIPPredict
{
private:
	CUserIPPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CUserIPAndPredict(CUserIPPredict *p1, CUserIPPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CUserIPAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pUserIP	要被判断的交易员IP地址
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserIP *pUserIP)
	{
		return m_p1->isValid(pUserIP) && m_p2->isValid(pUserIP);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserIPOrPredict是对两个交易员IP地址谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPOrPredict : public CUserIPPredict
{
private:
	CUserIPPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CUserIPOrPredict(CUserIPPredict *p1, CUserIPPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CUserIPOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pUserIP	要被判断的交易员IP地址
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserIP *pUserIP)
	{
		return m_p1->isValid(pUserIP) || m_p2->isValid(pUserIP);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserIPNotPredict是对一个交易员IP地址谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPNotPredict : public CUserIPPredict
{
private:
	CUserIPPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CUserIPNotPredict(CUserIPPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CUserIPNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pUserIP	要被判断的交易员IP地址
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CUserIP *pUserIP)
	{
		return !m_predict->isValid(pUserIP);
	}
};

/////////////////////////////////////////////////////////////////////////
///CUserIPFilter是一个对已有的交易员IP地址枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPFilter: public CUserIPIterator
{
private:
	CUserIPIterator *m_baseIterator;
	CUserIPPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CUserIPFilter(CUserIPIterator *pBaseIterator, CUserIPPredict *pPredict, bool continueResult=false)
		:CUserIPIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CUserIPFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CUserIP
	///@return	下一个满足条件CUserIP，如果已经没有一个满足要求了，则返回NULL
	virtual CUserIP *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pUserIP 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserIP * pUserIP,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CUserIPLinkIterator是连接两个交易员IP地址枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPLinkIterator: public CUserIPIterator
{
private:
	CUserIPIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CUserIPLinkIterator(CUserIPIterator *pBaseIterator1,CUserIPIterator *pBaseIterator2)
		:CUserIPIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CUserIPLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CUserIP
	///@return	下一个满足条件CUserIP，如果已经没有一个满足要求了，则返回NULL
	virtual CUserIP *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pUserIP 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserIP * pUserIP,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeSingleIterator是至多返回一个客户期权手续费率表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeSingleIterator: public CInvestorOptionFeeIterator
{
private:
	CInvestorOptionFee *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CInvestorOptionFeeSingleIterator(CInvestorOptionFeeFactory *pFactory,CInvestorOptionFee *pResult)
		:CInvestorOptionFeeIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CInvestorOptionFeeSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CInvestorOptionFee
	///@return	下一个满足条件CInvestorOptionFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorOptionFee *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorOptionFee 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorOptionFee * pInvestorOptionFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeePredict是判断一个客户期权手续费率表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeePredict
{
public:
	virtual ~CInvestorOptionFeePredict(){};

	///判断是否合法
	///@param	pInvestorOptionFee	要被判断的客户期权手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee)=0;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeAndPredict是对两个客户期权手续费率表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeAndPredict : public CInvestorOptionFeePredict
{
private:
	CInvestorOptionFeePredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorOptionFeeAndPredict(CInvestorOptionFeePredict *p1, CInvestorOptionFeePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorOptionFeeAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestorOptionFee	要被判断的客户期权手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee)
	{
		return m_p1->isValid(pInvestorOptionFee) && m_p2->isValid(pInvestorOptionFee);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeOrPredict是对两个客户期权手续费率表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeOrPredict : public CInvestorOptionFeePredict
{
private:
	CInvestorOptionFeePredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CInvestorOptionFeeOrPredict(CInvestorOptionFeePredict *p1, CInvestorOptionFeePredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CInvestorOptionFeeOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pInvestorOptionFee	要被判断的客户期权手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee)
	{
		return m_p1->isValid(pInvestorOptionFee) || m_p2->isValid(pInvestorOptionFee);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeNotPredict是对一个客户期权手续费率表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeNotPredict : public CInvestorOptionFeePredict
{
private:
	CInvestorOptionFeePredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CInvestorOptionFeeNotPredict(CInvestorOptionFeePredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CInvestorOptionFeeNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pInvestorOptionFee	要被判断的客户期权手续费率表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CInvestorOptionFee *pInvestorOptionFee)
	{
		return !m_predict->isValid(pInvestorOptionFee);
	}
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeFilter是一个对已有的客户期权手续费率表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeFilter: public CInvestorOptionFeeIterator
{
private:
	CInvestorOptionFeeIterator *m_baseIterator;
	CInvestorOptionFeePredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CInvestorOptionFeeFilter(CInvestorOptionFeeIterator *pBaseIterator, CInvestorOptionFeePredict *pPredict, bool continueResult=false)
		:CInvestorOptionFeeIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CInvestorOptionFeeFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CInvestorOptionFee
	///@return	下一个满足条件CInvestorOptionFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorOptionFee *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorOptionFee 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorOptionFee * pInvestorOptionFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeLinkIterator是连接两个客户期权手续费率表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeLinkIterator: public CInvestorOptionFeeIterator
{
private:
	CInvestorOptionFeeIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CInvestorOptionFeeLinkIterator(CInvestorOptionFeeIterator *pBaseIterator1,CInvestorOptionFeeIterator *pBaseIterator2)
		:CInvestorOptionFeeIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CInvestorOptionFeeLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CInvestorOptionFee
	///@return	下一个满足条件CInvestorOptionFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorOptionFee *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorOptionFee 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorOptionFee * pInvestorOptionFee,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CMarketDataSingleIterator是至多返回一个实时行情表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataSingleIterator: public CMarketDataIterator
{
private:
	CMarketData *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CMarketDataSingleIterator(CMarketDataFactory *pFactory,CMarketData *pResult)
		:CMarketDataIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CMarketDataSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CMarketData
	///@return	下一个满足条件CMarketData，如果已经没有一个满足要求了，则返回NULL
	virtual CMarketData *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pMarketData 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableMarketData * pMarketData,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataPredict是判断一个实时行情表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataPredict
{
public:
	virtual ~CMarketDataPredict(){};

	///判断是否合法
	///@param	pMarketData	要被判断的实时行情表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CMarketData *pMarketData)=0;
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataAndPredict是对两个实时行情表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataAndPredict : public CMarketDataPredict
{
private:
	CMarketDataPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CMarketDataAndPredict(CMarketDataPredict *p1, CMarketDataPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CMarketDataAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pMarketData	要被判断的实时行情表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CMarketData *pMarketData)
	{
		return m_p1->isValid(pMarketData) && m_p2->isValid(pMarketData);
	}
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataOrPredict是对两个实时行情表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataOrPredict : public CMarketDataPredict
{
private:
	CMarketDataPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CMarketDataOrPredict(CMarketDataPredict *p1, CMarketDataPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CMarketDataOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pMarketData	要被判断的实时行情表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CMarketData *pMarketData)
	{
		return m_p1->isValid(pMarketData) || m_p2->isValid(pMarketData);
	}
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataNotPredict是对一个实时行情表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataNotPredict : public CMarketDataPredict
{
private:
	CMarketDataPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CMarketDataNotPredict(CMarketDataPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CMarketDataNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pMarketData	要被判断的实时行情表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CMarketData *pMarketData)
	{
		return !m_predict->isValid(pMarketData);
	}
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataFilter是一个对已有的实时行情表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataFilter: public CMarketDataIterator
{
private:
	CMarketDataIterator *m_baseIterator;
	CMarketDataPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CMarketDataFilter(CMarketDataIterator *pBaseIterator, CMarketDataPredict *pPredict, bool continueResult=false)
		:CMarketDataIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CMarketDataFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CMarketData
	///@return	下一个满足条件CMarketData，如果已经没有一个满足要求了，则返回NULL
	virtual CMarketData *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pMarketData 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableMarketData * pMarketData,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataLinkIterator是连接两个实时行情表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataLinkIterator: public CMarketDataIterator
{
private:
	CMarketDataIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CMarketDataLinkIterator(CMarketDataIterator *pBaseIterator1,CMarketDataIterator *pBaseIterator2)
		:CMarketDataIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CMarketDataLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CMarketData
	///@return	下一个满足条件CMarketData，如果已经没有一个满足要求了，则返回NULL
	virtual CMarketData *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pMarketData 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableMarketData * pMarketData,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///COrderDelaySingleIterator是至多返回一个委托延迟表的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelaySingleIterator: public COrderDelayIterator
{
private:
	COrderDelay *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	COrderDelaySingleIterator(COrderDelayFactory *pFactory,COrderDelay *pResult)
		:COrderDelayIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~COrderDelaySingleIterator(void)
	{
	}

	///寻找下一个符合条件的COrderDelay
	///@return	下一个满足条件COrderDelay，如果已经没有一个满足要求了，则返回NULL
	virtual COrderDelay *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pOrderDelay 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrderDelay * pOrderDelay,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayPredict是判断一个委托延迟表是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayPredict
{
public:
	virtual ~COrderDelayPredict(){};

	///判断是否合法
	///@param	pOrderDelay	要被判断的委托延迟表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderDelay *pOrderDelay)=0;
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayAndPredict是对两个委托延迟表谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayAndPredict : public COrderDelayPredict
{
private:
	COrderDelayPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	COrderDelayAndPredict(COrderDelayPredict *p1, COrderDelayPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~COrderDelayAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pOrderDelay	要被判断的委托延迟表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderDelay *pOrderDelay)
	{
		return m_p1->isValid(pOrderDelay) && m_p2->isValid(pOrderDelay);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayOrPredict是对两个委托延迟表谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayOrPredict : public COrderDelayPredict
{
private:
	COrderDelayPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	COrderDelayOrPredict(COrderDelayPredict *p1, COrderDelayPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~COrderDelayOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pOrderDelay	要被判断的委托延迟表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderDelay *pOrderDelay)
	{
		return m_p1->isValid(pOrderDelay) || m_p2->isValid(pOrderDelay);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayNotPredict是对一个委托延迟表谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayNotPredict : public COrderDelayPredict
{
private:
	COrderDelayPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	COrderDelayNotPredict(COrderDelayPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~COrderDelayNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pOrderDelay	要被判断的委托延迟表
	///@return	true表示合法，false表示不合法
	virtual bool isValid(COrderDelay *pOrderDelay)
	{
		return !m_predict->isValid(pOrderDelay);
	}
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayFilter是一个对已有的委托延迟表枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayFilter: public COrderDelayIterator
{
private:
	COrderDelayIterator *m_baseIterator;
	COrderDelayPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	COrderDelayFilter(COrderDelayIterator *pBaseIterator, COrderDelayPredict *pPredict, bool continueResult=false)
		:COrderDelayIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~COrderDelayFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的COrderDelay
	///@return	下一个满足条件COrderDelay，如果已经没有一个满足要求了，则返回NULL
	virtual COrderDelay *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pOrderDelay 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrderDelay * pOrderDelay,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayLinkIterator是连接两个委托延迟表枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayLinkIterator: public COrderDelayIterator
{
private:
	COrderDelayIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	COrderDelayLinkIterator(COrderDelayIterator *pBaseIterator1,COrderDelayIterator *pBaseIterator2)
		:COrderDelayIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~COrderDelayLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的COrderDelay
	///@return	下一个满足条件COrderDelay，如果已经没有一个满足要求了，则返回NULL
	virtual COrderDelay *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pOrderDelay 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrderDelay * pOrderDelay,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


/////////////////////////////////////////////////////////////////////////
///CSystemInfoSingleIterator是至多返回一个QDP系统信息的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoSingleIterator: public CSystemInfoIterator
{
private:
	CSystemInfo *m_pResult;
	bool m_finished;
public:
	///构造方法
	///@param	pFactory	要使用的对象工厂
	///@param	pResult	要返回的单个结果
	CSystemInfoSingleIterator(CSystemInfoFactory *pFactory,CSystemInfo *pResult)
		:CSystemInfoIterator(pFactory)
	{
		m_pResult=pResult;
		m_finished=false;
	}

	///构造方法
	virtual ~CSystemInfoSingleIterator(void)
	{
	}

	///寻找下一个符合条件的CSystemInfo
	///@return	下一个满足条件CSystemInfo，如果已经没有一个满足要求了，则返回NULL
	virtual CSystemInfo *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pSystemInfo 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSystemInfo * pSystemInfo,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoPredict是判断一个QDP系统信息是否符合条件的谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoPredict
{
public:
	virtual ~CSystemInfoPredict(){};

	///判断是否合法
	///@param	pSystemInfo	要被判断的QDP系统信息
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSystemInfo *pSystemInfo)=0;
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoAndPredict是对两个QDP系统信息谓词的与谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoAndPredict : public CSystemInfoPredict
{
private:
	CSystemInfoPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CSystemInfoAndPredict(CSystemInfoPredict *p1, CSystemInfoPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CSystemInfoAndPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pSystemInfo	要被判断的QDP系统信息
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSystemInfo *pSystemInfo)
	{
		return m_p1->isValid(pSystemInfo) && m_p2->isValid(pSystemInfo);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoOrPredict是对两个QDP系统信息谓词的或谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoOrPredict : public CSystemInfoPredict
{
private:
	CSystemInfoPredict *m_p1,*m_p2;
public:
	///构造方法
	///@param	p1	第一个谓词
	///@param	p2	第二个谓词
	CSystemInfoOrPredict(CSystemInfoPredict *p1, CSystemInfoPredict *p2)
	{
		m_p1=p1;
		m_p2=p2;
	}
	
	///析构方法
	virtual ~CSystemInfoOrPredict(void)
	{
		delete m_p1;
		delete m_p2;
	}

	///判断是否合法
	///@param	pSystemInfo	要被判断的QDP系统信息
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSystemInfo *pSystemInfo)
	{
		return m_p1->isValid(pSystemInfo) || m_p2->isValid(pSystemInfo);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoNotPredict是对一个QDP系统信息谓词的非谓词
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoNotPredict : public CSystemInfoPredict
{
private:
	CSystemInfoPredict *m_predict;
public:
	///构造方法
	///@param	predict	基础谓词
	CSystemInfoNotPredict(CSystemInfoPredict *predict)
	{
		m_predict=predict;
	}
	
	///析构方法
	virtual ~CSystemInfoNotPredict(void)
	{
		delete m_predict;
	}

	///判断是否合法
	///@param	pSystemInfo	要被判断的QDP系统信息
	///@return	true表示合法，false表示不合法
	virtual bool isValid(CSystemInfo *pSystemInfo)
	{
		return !m_predict->isValid(pSystemInfo);
	}
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoFilter是一个对已有的QDP系统信息枚举器进行过滤的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoFilter: public CSystemInfoIterator
{
private:
	CSystemInfoIterator *m_baseIterator;
	CSystemInfoPredict *m_predict;
	bool m_continueResult;
	bool m_finished;
public:
	///构造函数
	///@param	pBaseIterator	基础的枚举器
	///@param	pPredict	判定是否合法的谓词
	///@param	continueResult	true表示如果结果集必须是基础枚举器给出的连续结果，false表示不必如此
	CSystemInfoFilter(CSystemInfoIterator *pBaseIterator, CSystemInfoPredict *pPredict, bool continueResult=false)
		:CSystemInfoIterator()
	{
		m_baseIterator=pBaseIterator;
		m_predict=pPredict;
		m_continueResult=continueResult;
		m_finished=false;
	}
	
	///析构函数
	virtual ~CSystemInfoFilter(void)
	{
		m_baseIterator->free();
		delete m_predict;
	}

	///寻找下一个符合条件的CSystemInfo
	///@return	下一个满足条件CSystemInfo，如果已经没有一个满足要求了，则返回NULL
	virtual CSystemInfo *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pSystemInfo 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSystemInfo * pSystemInfo,CTransaction *pTransaction = NULL, bool updateIndex=true);
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoLinkIterator是连接两个QDP系统信息枚举器的枚举器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoLinkIterator: public CSystemInfoIterator
{
private:
	CSystemInfoIterator *m_baseIterator[2];
	int m_id;
public:
	///构造函数
	///@param	pBaseIterator1	基础的枚举器1
	///@param	pBaseIterator2	基础的枚举器2
	CSystemInfoLinkIterator(CSystemInfoIterator *pBaseIterator1,CSystemInfoIterator *pBaseIterator2)
		:CSystemInfoIterator()
	{
		m_baseIterator[0]=pBaseIterator1;
		m_baseIterator[1]=pBaseIterator2;
		m_id=0;
	}
	
	///析构函数
	virtual ~CSystemInfoLinkIterator(void)
	{
		for (int i=0;i<2;i++)
		{
			m_baseIterator[i]->free();
		}
	}

	///寻找下一个符合条件的CSystemInfo
	///@return	下一个满足条件CSystemInfo，如果已经没有一个满足要求了，则返回NULL
	virtual CSystemInfo *next(void);
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL);
	
	///更新当前Iterator指向的纪录
	///@param	pSystemInfo 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSystemInfo * pSystemInfo,CTransaction *pTransaction = NULL, bool updateIndex=true);
};


#endif
