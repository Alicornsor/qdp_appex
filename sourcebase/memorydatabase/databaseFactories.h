/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseFactories.h
///@brief定义了若干个内存数据库的对象工厂
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef DATABASEFACTORIES_H
#define DATABASEFACTORIES_H

#include "platform.h"
#include "CBaseObject.h"
#include "CConfig.h"
#include "CAVLTree.h"
#include "CHashIndex.h"
#include "customDataType.h"
#include "CDatabaseDataFactory.h"
#include "CTransaction.h"
#include "BaseDataStruct.h"
#include "CDatabaseResource.h"
#include "Allocator.h"

class CDataSyncStatusFactory;
class CDataSyncStatusResource;
class CSystemStatusFactory;
class CSystemStatusResource;
class COrderActionFactory;
class COrderActionResource;
class COrderFactory;
class COrderResource;
class CTradeFactory;
class CTradeResource;
class CPreOrderFactory;
class CPreOrderResource;
class CIndexPreOrderFactory;
class CIndexPreOrderResource;
class CInvestorPositionFactory;
class CInvestorPositionResource;
class CInvestorAccountFactory;
class CInvestorAccountResource;
class CInvestorAccountDepositFactory;
class CInvestorAccountDepositResource;
class CExchangeFactory;
class CExchangeResource;
class CSeatFactory;
class CSeatResource;
class CInstrumentFactory;
class CInstrumentResource;
class CCmbInstrumentDetailFactory;
class CCmbInstrumentDetailResource;
class CClientTradingIDFactory;
class CClientTradingIDResource;
class CInvestorFactory;
class CInvestorResource;
class CInvestorMarginFactory;
class CInvestorMarginResource;
class CInvestorFeeFactory;
class CInvestorFeeResource;
class CUserFactory;
class CUserResource;
class CUserInvestorFactory;
class CUserInvestorResource;
class COrderInsertFailedFactory;
class COrderInsertFailedResource;
class CUserTradingRightFactory;
class CUserTradingRightResource;
class CCurrentTimeFactory;
class CCurrentTimeResource;
class CUserSessionFactory;
class CUserSessionResource;
class CMaxLocalIDFactory;
class CMaxLocalIDResource;
class CBrkUserIDLocalIDFactory;
class CBrkUserIDLocalIDResource;
class CPartClientInsGroupPositionFactory;
class CPartClientInsGroupPositionResource;
class CClientMarginCombTypeFactory;
class CClientMarginCombTypeResource;
class CInstrumentGroupFactory;
class CInstrumentGroupResource;
class CSGEDeferRateFactory;
class CSGEDeferRateResource;
class CInvestorTradingRightFactory;
class CInvestorTradingRightResource;
class CUserIPFactory;
class CUserIPResource;
class CInvestorOptionFeeFactory;
class CInvestorOptionFeeResource;
class CMarketDataFactory;
class CMarketDataResource;
class COrderDelayFactory;
class COrderDelayResource;
class CSystemInfoFactory;
class CSystemInfoResource;

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusFactory是一个数据同步状态表的对象工厂。它包含了一批数据同步状态表，
///同时又建立了如下索引，以方便查询：
///	TradingdayIndex
///使用本对象工厂，可以完成对数据同步状态表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByTradingday，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CDataSyncStatusFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxDataSyncStatus，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CDataSyncStatusFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CDataSyncStatusFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的DataSyncStatus
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的DataSyncStatus，文件名将根据配置文件中的定义DataSyncStatusCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的DataSyncStatus
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的DataSyncStatus，文件名将根据配置文件中的定义DataSyncStatusCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CDataSyncStatusResource;

	///将一个CDataSyncStatus加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pDataSyncStatus	要加入的DataSyncStatus
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CDataSyncStatus *add(CWriteableDataSyncStatus *pDataSyncStatus, CTransaction *pTransaction=NULL);
	
	///刷新该CDataSyncStatus的值
	///@param	pDataSyncStatus	被刷新的CDataSyncStatus
	///@param	pNewDataSyncStatus	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pDataSyncStatus	  需要被刷新或者新增的CDataSyncStatus,等于NULL表示是需要新增的
	///@param	pNewDataSyncStatus	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CDataSyncStatus* addOrUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CDataSyncStatus，同时删除其索引
	///@param	pDataSyncStatus	要删除的CDataSyncStatus
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CDataSyncStatus *pDataSyncStatus, CTransaction *pTransaction=NULL);
	
	///获取某个CDataSyncStatus
	///@param	pDataSyncStatus	要读取的CDataSyncStatus
	///@param	pTragetDataSyncStatus	存放结果的CDataSyncStatus
	void retrieve(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pTargetDataSyncStatus);
	
	///获取第一个CDataSyncStatus
	///@return	得到的第一个CDataSyncStatus，如果没有，则返回NULL
	CDataSyncStatus *getFirst(void);
	
	///获取下一个CDataSyncStatus
	///@return	得到下一个CDataSyncStatus，如果没有，则返回NULL
	CDataSyncStatus *getNext(void);
	
	///结束获取CDataSyncStatus
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CDataSyncStatusActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CDataSyncStatusActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CDataSyncStatusCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CDataSyncStatusCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CDataSyncStatus
	///@param	TradingDay	交易日
	///@return	找到的CDataSyncStatus，如果找不到，返回NULL
	CDataSyncStatus *findByTradingday( const CReadOnlyDateType&  TradingDay);



private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CDataSyncStatus加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pDataSyncStatus	要加入的DataSyncStatus
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CDataSyncStatus *internalAdd(CWriteableDataSyncStatus *pDataSyncStatus, bool bNoTransaction);
	
	
	///刷新该CDataSyncStatus的键值
	///@param	pDataSyncStatus	被刷新的CDataSyncStatus
	///@param	pNewDataSyncStatus	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus, bool updateIndex,bool bNoTransaction);
	
	///删除一个CDataSyncStatus，同时删除其索引
	///@param	pDataSyncStatus	要删除的CDataSyncStatus
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CDataSyncStatus *pDataSyncStatus, bool bNoTransaction);
/*
	///检查某个CDataSyncStatus是否属于本对象工厂
	///@param	pDataSyncStatus	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CDataSyncStatus *pDataSyncStatus);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于TradingDay的索引
	CAVLTree *pTradingdayIndex;
	
	
	
	///加入前触发
	///@param	pDataSyncStatus	要加入的DataSyncStatus
	virtual void beforeAdd(CWriteableDataSyncStatus *pDataSyncStatus);
	
	///加入后触发
	///@param	pDataSyncStatus	已经加入的DataSyncStatus
	virtual void afterAdd(CDataSyncStatus *pDataSyncStatus);

	///更新前触发	
	///@param	pDataSyncStatus	被刷新的CDataSyncStatus
	///@param	pNewDataSyncStatus	新的值
	virtual void beforeUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus);
	
	///更新后触发
	///@param	pDataSyncStatus	被刷新的CDataSyncStatus
	virtual void afterUpdate(CDataSyncStatus *pDataSyncStatus);
	
	///删除前触发
	///@param	pDataSyncStatus	要删除的CDataSyncStatus
	virtual void beforeRemove(CDataSyncStatus *pDataSyncStatus);
	
	///确认加入后触发
	///@param	pDataSyncStatus	已经加入的DataSyncStatus
	virtual void commitAdd(CDataSyncStatus *pDataSyncStatus);

	///确认更新后触发
	///@param	pDataSyncStatus	被刷新的CDataSyncStatus
	///@param	poldDataSyncStatus	原来的值
	virtual void commitUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pOldDataSyncStatus);
	
	///确认删除后触发
	///@param	pDataSyncStatus	已经删除的CDataSyncStatus
	virtual void commitRemove(CWriteableDataSyncStatus *pDataSyncStatus);

	///所有相关的触发器
	vector<CDataSyncStatusActionTrigger *> *pActionTriggers;
	vector<CDataSyncStatusCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableDataSyncStatus compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusFactory是一个QDP状态表的对象工厂。它包含了一批QDP状态表，
///同时又建立了如下索引，以方便查询：
///	TradingDay
///使用本对象工厂，可以完成对QDP状态表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByTradingDay，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CSystemStatusFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxSystemStatus，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CSystemStatusFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CSystemStatusFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的SystemStatus
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的SystemStatus，文件名将根据配置文件中的定义SystemStatusCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的SystemStatus
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的SystemStatus，文件名将根据配置文件中的定义SystemStatusCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CSystemStatusResource;

	///将一个CSystemStatus加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pSystemStatus	要加入的SystemStatus
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CSystemStatus *add(CWriteableSystemStatus *pSystemStatus, CTransaction *pTransaction=NULL);
	
	///刷新该CSystemStatus的值
	///@param	pSystemStatus	被刷新的CSystemStatus
	///@param	pNewSystemStatus	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pSystemStatus	  需要被刷新或者新增的CSystemStatus,等于NULL表示是需要新增的
	///@param	pNewSystemStatus	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CSystemStatus* addOrUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CSystemStatus，同时删除其索引
	///@param	pSystemStatus	要删除的CSystemStatus
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CSystemStatus *pSystemStatus, CTransaction *pTransaction=NULL);
	
	///获取某个CSystemStatus
	///@param	pSystemStatus	要读取的CSystemStatus
	///@param	pTragetSystemStatus	存放结果的CSystemStatus
	void retrieve(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pTargetSystemStatus);
	
	///获取第一个CSystemStatus
	///@return	得到的第一个CSystemStatus，如果没有，则返回NULL
	CSystemStatus *getFirst(void);
	
	///获取下一个CSystemStatus
	///@return	得到下一个CSystemStatus，如果没有，则返回NULL
	CSystemStatus *getNext(void);
	
	///结束获取CSystemStatus
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CSystemStatusActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CSystemStatusActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CSystemStatusCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CSystemStatusCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CSystemStatus
	///@param	TradingDay	交易日
	///@return	找到的CSystemStatus，如果找不到，返回NULL
	CSystemStatus *findByTradingDay( const CReadOnlyDateType&  TradingDay);

	///根据主码寻找
	///@param	TradingDay	交易日
	///@return	找到的CSystemStatus，如果找不到，返回NULL
	CSystemStatus *findByPK( const CReadOnlyDateType&  TradingDay);
	
	///根据主键寻找CSystemStatus
	///@param	pSystemStatus	要找的值
	///@return	找到的CSystemStatus，如果找不到，返回NULL
	CSystemStatus *findByPK(CWriteableSystemStatus *pSystemStatus);

	///根据主键获取CSystemStatus
	///@param	pSystemStatus	要获取的值，同时用于存放返回的结果
	///@return	找到的CSystemStatus，如果找不到，返回NULL
	bool retrieveByPK(CWriteableSystemStatus *pSystemStatus);

	///根据主键增加新的CSystemStatus
	///@param	pSystemStatus	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CSystemStatus，如果插入失败，则返回NULL
	CSystemStatus *addByPK(CWriteableSystemStatus *pSystemStatus, CTransaction *pTransaction=NULL);

	///根据主键更新CSystemStatus的值
	///@param	pSystemStatus	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableSystemStatus *pSystemStatus, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CSystemStatus
	///@param	pSystemStatus	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableSystemStatus *pSystemStatus, CTransaction *pTransaction=NULL);


private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CSystemStatus加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pSystemStatus	要加入的SystemStatus
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CSystemStatus *internalAdd(CWriteableSystemStatus *pSystemStatus, bool bNoTransaction);
	
	
	///刷新该CSystemStatus的键值
	///@param	pSystemStatus	被刷新的CSystemStatus
	///@param	pNewSystemStatus	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus, bool updateIndex,bool bNoTransaction);
	
	///删除一个CSystemStatus，同时删除其索引
	///@param	pSystemStatus	要删除的CSystemStatus
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CSystemStatus *pSystemStatus, bool bNoTransaction);
/*
	///检查某个CSystemStatus是否属于本对象工厂
	///@param	pSystemStatus	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CSystemStatus *pSystemStatus);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于TradingDay的索引
	CAVLTree *pTradingDay;
	
	
	
	///加入前触发
	///@param	pSystemStatus	要加入的SystemStatus
	virtual void beforeAdd(CWriteableSystemStatus *pSystemStatus);
	
	///加入后触发
	///@param	pSystemStatus	已经加入的SystemStatus
	virtual void afterAdd(CSystemStatus *pSystemStatus);

	///更新前触发	
	///@param	pSystemStatus	被刷新的CSystemStatus
	///@param	pNewSystemStatus	新的值
	virtual void beforeUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus);
	
	///更新后触发
	///@param	pSystemStatus	被刷新的CSystemStatus
	virtual void afterUpdate(CSystemStatus *pSystemStatus);
	
	///删除前触发
	///@param	pSystemStatus	要删除的CSystemStatus
	virtual void beforeRemove(CSystemStatus *pSystemStatus);
	
	///确认加入后触发
	///@param	pSystemStatus	已经加入的SystemStatus
	virtual void commitAdd(CSystemStatus *pSystemStatus);

	///确认更新后触发
	///@param	pSystemStatus	被刷新的CSystemStatus
	///@param	poldSystemStatus	原来的值
	virtual void commitUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pOldSystemStatus);
	
	///确认删除后触发
	///@param	pSystemStatus	已经删除的CSystemStatus
	virtual void commitRemove(CWriteableSystemStatus *pSystemStatus);

	///所有相关的触发器
	vector<CSystemStatusActionTrigger *> *pActionTriggers;
	vector<CSystemStatusCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableSystemStatus compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///COrderActionFactory是一个报单操作的对象工厂。它包含了一批报单操作，
///同时又建立了如下索引，以方便查询：
///使用本对象工厂，可以完成对报单操作的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	COrderActionFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxOrderAction，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	COrderActionFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~COrderActionFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的OrderAction
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的OrderAction，文件名将根据配置文件中的定义OrderActionCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的OrderAction
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的OrderAction，文件名将根据配置文件中的定义OrderActionCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class COrderActionResource;

	///将一个COrderAction加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pOrderAction	要加入的OrderAction
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	COrderAction *add(CWriteableOrderAction *pOrderAction, CTransaction *pTransaction=NULL);
	
	///刷新该COrderAction的值
	///@param	pOrderAction	被刷新的COrderAction
	///@param	pNewOrderAction	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pOrderAction	  需要被刷新或者新增的COrderAction,等于NULL表示是需要新增的
	///@param	pNewOrderAction	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	COrderAction* addOrUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个COrderAction，同时删除其索引
	///@param	pOrderAction	要删除的COrderAction
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(COrderAction *pOrderAction, CTransaction *pTransaction=NULL);
	
	///获取某个COrderAction
	///@param	pOrderAction	要读取的COrderAction
	///@param	pTragetOrderAction	存放结果的COrderAction
	void retrieve(COrderAction *pOrderAction, CWriteableOrderAction *pTargetOrderAction);
	
	///获取第一个COrderAction
	///@return	得到的第一个COrderAction，如果没有，则返回NULL
	COrderAction *getFirst(void);
	
	///获取下一个COrderAction
	///@return	得到下一个COrderAction，如果没有，则返回NULL
	COrderAction *getNext(void);
	
	///结束获取COrderAction
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(COrderActionActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(COrderActionActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(COrderActionCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(COrderActionCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///构造所有对应的报单的指针
	///@param	pFactory	构造对应的报单的指针时，寻找的对象工厂
	void linkAllOrder(COrderFactory *pFactory);
	
	///构造所有对应的报单的指针
	///@param	pFactory	构造对应的报单的指针时，寻找的对象工厂
	void linkAllPreOrder(CPreOrderFactory *pFactory);
	
private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个COrderAction加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pOrderAction	要加入的OrderAction
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	COrderAction *internalAdd(CWriteableOrderAction *pOrderAction, bool bNoTransaction);
	
	
	///刷新该COrderAction的键值
	///@param	pOrderAction	被刷新的COrderAction
	///@param	pNewOrderAction	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction, bool updateIndex,bool bNoTransaction);
	
	///删除一个COrderAction，同时删除其索引
	///@param	pOrderAction	要删除的COrderAction
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(COrderAction *pOrderAction, bool bNoTransaction);
/*
	///检查某个COrderAction是否属于本对象工厂
	///@param	pOrderAction	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(COrderAction *pOrderAction);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	
	
	
	///加入前触发
	///@param	pOrderAction	要加入的OrderAction
	virtual void beforeAdd(CWriteableOrderAction *pOrderAction);
	
	///加入后触发
	///@param	pOrderAction	已经加入的OrderAction
	virtual void afterAdd(COrderAction *pOrderAction);

	///更新前触发	
	///@param	pOrderAction	被刷新的COrderAction
	///@param	pNewOrderAction	新的值
	virtual void beforeUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction);
	
	///更新后触发
	///@param	pOrderAction	被刷新的COrderAction
	virtual void afterUpdate(COrderAction *pOrderAction);
	
	///删除前触发
	///@param	pOrderAction	要删除的COrderAction
	virtual void beforeRemove(COrderAction *pOrderAction);
	
	///确认加入后触发
	///@param	pOrderAction	已经加入的OrderAction
	virtual void commitAdd(COrderAction *pOrderAction);

	///确认更新后触发
	///@param	pOrderAction	被刷新的COrderAction
	///@param	poldOrderAction	原来的值
	virtual void commitUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pOldOrderAction);
	
	///确认删除后触发
	///@param	pOrderAction	已经删除的COrderAction
	virtual void commitRemove(CWriteableOrderAction *pOrderAction);

	///所有相关的触发器
	vector<COrderActionActionTrigger *> *pActionTriggers;
	vector<COrderActionCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableOrderAction compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///COrderFactory是一个委托表的对象工厂。它包含了一批委托表，
///同时又建立了如下索引，以方便查询：
///使用本对象工厂，可以完成对委托表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByExchangeIDAndOrderSysID，唯一找到对象
///		使用findByUserIDAndUserOrderLocalID，唯一找到对象
///		使用startFindAllByUserID，findNextAllByUserID和endFindAllByUserID完成查询操作
///		使用startFindAllByInvestorID，findNextAllByInvestorID和endFindAllByInvestorID完成查询操作
///		使用startFindAllByExchIDInvIDUserID，findNextAllByExchIDInvIDUserID和endFindAllByExchIDInvIDUserID完成查询操作
///		使用startFindAllByExchIDInstruIDUserID，findNextAllByExchIDInstruIDUserID和endFindAllByExchIDInstruIDUserID完成查询操作
///		使用startFindAll，findNextAll和endFindAll完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	COrderFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxOrder，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	COrderFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~COrderFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的Order
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的Order，文件名将根据配置文件中的定义OrderCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的Order
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的Order，文件名将根据配置文件中的定义OrderCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class COrderResource;

	///将一个COrder加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pOrder	要加入的Order
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	COrder *add(CWriteableOrder *pOrder, CTransaction *pTransaction=NULL);
	
	///刷新该COrder的值
	///@param	pOrder	被刷新的COrder
	///@param	pNewOrder	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(COrder *pOrder, CWriteableOrder *pNewOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pOrder	  需要被刷新或者新增的COrder,等于NULL表示是需要新增的
	///@param	pNewOrder	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	COrder* addOrUpdate(COrder *pOrder, CWriteableOrder *pNewOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个COrder，同时删除其索引
	///@param	pOrder	要删除的COrder
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(COrder *pOrder, CTransaction *pTransaction=NULL);
	
	///获取某个COrder
	///@param	pOrder	要读取的COrder
	///@param	pTragetOrder	存放结果的COrder
	void retrieve(COrder *pOrder, CWriteableOrder *pTargetOrder);
	
	///获取第一个COrder
	///@return	得到的第一个COrder，如果没有，则返回NULL
	COrder *getFirst(void);
	
	///获取下一个COrder
	///@return	得到下一个COrder，如果没有，则返回NULL
	COrder *getNext(void);
	
	///结束获取COrder
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(COrderActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(COrderActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(COrderCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(COrderCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///构造所有对应的投资者的指针
	///@param	pFactory	构造对应的投资者的指针时，寻找的对象工厂
	void linkAllInvestor(CInvestorFactory *pFactory);
	
	///构造所有对应的交易编码的指针
	///@param	pFactory	构造对应的交易编码的指针时，寻找的对象工厂
	void linkAllClientTradingID(CClientTradingIDFactory *pFactory);
	
	///构造所有对应的帐户的指针
	///@param	pFactory	构造对应的帐户的指针时，寻找的对象工厂
	void linkAllInvestorAccount(CInvestorAccountFactory *pFactory);
	
	///构造所有对应的合约持仓信息的指针
	///@param	pFactory	构造对应的合约持仓信息的指针时，寻找的对象工厂
	void linkAllInvestorPosition(CInvestorPositionFactory *pFactory);
	
	///构造所有对应的合约信息的指针
	///@param	pFactory	构造对应的合约信息的指针时，寻找的对象工厂
	void linkAllInstrument(CInstrumentFactory *pFactory);
	
	///构造所有对应的投资者保证金率信息的指针
	///@param	pFactory	构造对应的投资者保证金率信息的指针时，寻找的对象工厂
	void linkAllInvestorMargin(CInvestorMarginFactory *pFactory);
	
	///构造所有对应的投资者手续费率信息的指针
	///@param	pFactory	构造对应的投资者手续费率信息的指针时，寻找的对象工厂
	void linkAllInvestorFee(CInvestorFeeFactory *pFactory);
	
	///构造所有对应的投资者期权手续费率信息的指针
	///@param	pFactory	构造对应的投资者期权手续费率信息的指针时，寻找的对象工厂
	void linkAllInvestorOptionFee(CInvestorOptionFeeFactory *pFactory);
	
	///构造所有对应的合约大边组持仓信息的指针
	///@param	pFactory	构造对应的合约大边组持仓信息的指针时，寻找的对象工厂
	void linkAllClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory);
	
	///寻找COrder
	///@param	ExchangeID	交易所代码
	///@param	OrderSysID	资金帐号
	///@return	找到的COrder，如果找不到，返回NULL
	COrder *findByExchangeIDAndOrderSysID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyOrderSysIDType&  OrderSysID);

	///根据主码寻找
	///@param	ExchangeID	交易所代码
	///@param	OrderSysID	资金帐号
	///@return	找到的COrder，如果找不到，返回NULL
	COrder *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyOrderSysIDType&  OrderSysID);
	
	///根据主键寻找COrder
	///@param	pOrder	要找的值
	///@return	找到的COrder，如果找不到，返回NULL
	COrder *findByPK(CWriteableOrder *pOrder);

	///根据主键获取COrder
	///@param	pOrder	要获取的值，同时用于存放返回的结果
	///@return	找到的COrder，如果找不到，返回NULL
	bool retrieveByPK(CWriteableOrder *pOrder);

	///根据主键增加新的COrder
	///@param	pOrder	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的COrder，如果插入失败，则返回NULL
	COrder *addByPK(CWriteableOrder *pOrder, CTransaction *pTransaction=NULL);

	///根据主键更新COrder的值
	///@param	pOrder	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableOrder *pOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除COrder
	///@param	pOrder	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableOrder *pOrder, CTransaction *pTransaction=NULL);


	///寻找COrder
	///@param	BrokerID	经纪公司代码
	///@param	UserID	交易用户代码
	///@param	UserOrderLocalID	用户本地报单编号
	///@param	FrontID	前置号
	///@param	SessionID	会话号
	///@return	找到的COrder，如果找不到，返回NULL
	COrder *findByUserIDAndUserOrderLocalID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyUserOrderLocalIDType&  UserOrderLocalID,  const CReadOnlyFrontIDType&  FrontID,  const CReadOnlySessionIDType&  SessionID);



	friend class COrderIteratorAllByUserID;

	///开始寻找COrder
	///@param	UserID	交易用户代码
	///@return	满足条件的地一个COrder，如果找不到，返回NULL
	COrder *startFindAllByUserID( const CReadOnlyUserIDType& UserID);

	///寻找下一个符合条件的COrder，必须在startFindAllByUserID以后，endFindAllByUserID之前叫用
	///@return	下一个满足条件COrder，如果已经没有一个满足要求了，则返回NULL
	COrder *findNextAllByUserID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByUserID(void);

	friend class COrderIteratorAllByInvestorID;

	///开始寻找COrder
	///@param	InvestorID	投资者编号
	///@return	满足条件的地一个COrder，如果找不到，返回NULL
	COrder *startFindAllByInvestorID( const CReadOnlyInvestorIDType& InvestorID);

	///寻找下一个符合条件的COrder，必须在startFindAllByInvestorID以后，endFindAllByInvestorID之前叫用
	///@return	下一个满足条件COrder，如果已经没有一个满足要求了，则返回NULL
	COrder *findNextAllByInvestorID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByInvestorID(void);

	friend class COrderIteratorAllByExchIDInvIDUserID;

	///开始寻找COrder
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	UserID	交易用户代码
	///@return	满足条件的地一个COrder，如果找不到，返回NULL
	COrder *startFindAllByExchIDInvIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInvestorIDType& InvestorID,  const CReadOnlyUserIDType& UserID);

	///寻找下一个符合条件的COrder，必须在startFindAllByExchIDInvIDUserID以后，endFindAllByExchIDInvIDUserID之前叫用
	///@return	下一个满足条件COrder，如果已经没有一个满足要求了，则返回NULL
	COrder *findNextAllByExchIDInvIDUserID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByExchIDInvIDUserID(void);

	friend class COrderIteratorAllByExchIDInstruIDUserID;

	///开始寻找COrder
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约号
	///@param	UserID	交易用户代码
	///@return	满足条件的地一个COrder，如果找不到，返回NULL
	COrder *startFindAllByExchIDInstruIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& InstrumentID,  const CReadOnlyUserIDType& UserID);

	///寻找下一个符合条件的COrder，必须在startFindAllByExchIDInstruIDUserID以后，endFindAllByExchIDInstruIDUserID之前叫用
	///@return	下一个满足条件COrder，如果已经没有一个满足要求了，则返回NULL
	COrder *findNextAllByExchIDInstruIDUserID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByExchIDInstruIDUserID(void);

	friend class COrderIteratorAll;

	///开始寻找COrder
	///@return	满足条件的地一个COrder，如果找不到，返回NULL
	COrder *startFindAll();

	///寻找下一个符合条件的COrder，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件COrder，如果已经没有一个满足要求了，则返回NULL
	COrder *findNextAll(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAll(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个COrder加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pOrder	要加入的Order
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	COrder *internalAdd(CWriteableOrder *pOrder, bool bNoTransaction);
	
	
	///刷新该COrder的键值
	///@param	pOrder	被刷新的COrder
	///@param	pNewOrder	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(COrder *pOrder, CWriteableOrder *pNewOrder, bool updateIndex,bool bNoTransaction);
	
	///删除一个COrder，同时删除其索引
	///@param	pOrder	要删除的COrder
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(COrder *pOrder, bool bNoTransaction);
/*
	///检查某个COrder是否属于本对象工厂
	///@param	pOrder	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(COrder *pOrder);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	
	///基于ExchangeIDOrderSysID的hash索引
	CHashIndex *pExchangeIDOrderSysIDHashIndex;
	///基于UserIDAndUserOrderLocalID的hash索引
	CHashIndex *pUserIDAndUserOrderLocalIDHashIndex;
	
	///按照UserID检索时，存储的查询参数
	CUserIDType queryUserIDInSearchAllByUserID;
	
	///按照UserID检索时，存储最后一次找到的索引节点
	COrder *pLastFoundInSearchAllByUserID;
	///按照InvestorID检索时，存储的查询参数
	CInvestorIDType queryInvestorIDInSearchAllByInvestorID;
	
	///按照InvestorID检索时，存储最后一次找到的索引节点
	COrder *pLastFoundInSearchAllByInvestorID;
	///按照ExchangeID，InvestorID，UserID检索时，存储的查询参数
	CExchangeIDType queryExchangeIDInSearchAllByExchIDInvIDUserID;
	CInvestorIDType queryInvestorIDInSearchAllByExchIDInvIDUserID;
	CUserIDType queryUserIDInSearchAllByExchIDInvIDUserID;
	
	///按照ExchangeID，InvestorID，UserID检索时，存储最后一次找到的索引节点
	COrder *pLastFoundInSearchAllByExchIDInvIDUserID;
	///按照ExchangeID，InstrumentID，UserID检索时，存储的查询参数
	CExchangeIDType queryExchangeIDInSearchAllByExchIDInstruIDUserID;
	CInstrumentIDType queryInstrumentIDInSearchAllByExchIDInstruIDUserID;
	CUserIDType queryUserIDInSearchAllByExchIDInstruIDUserID;
	
	///按照ExchangeID，InstrumentID，UserID检索时，存储最后一次找到的索引节点
	COrder *pLastFoundInSearchAllByExchIDInstruIDUserID;
	///按照检索时，存储的查询参数
	
	///按照检索时，存储最后一次找到的索引节点
	COrder *pLastFoundInSearchAll;
	
	///加入前触发
	///@param	pOrder	要加入的Order
	virtual void beforeAdd(CWriteableOrder *pOrder);
	
	///加入后触发
	///@param	pOrder	已经加入的Order
	virtual void afterAdd(COrder *pOrder);

	///更新前触发	
	///@param	pOrder	被刷新的COrder
	///@param	pNewOrder	新的值
	virtual void beforeUpdate(COrder *pOrder, CWriteableOrder *pNewOrder);
	
	///更新后触发
	///@param	pOrder	被刷新的COrder
	virtual void afterUpdate(COrder *pOrder);
	
	///删除前触发
	///@param	pOrder	要删除的COrder
	virtual void beforeRemove(COrder *pOrder);
	
	///确认加入后触发
	///@param	pOrder	已经加入的Order
	virtual void commitAdd(COrder *pOrder);

	///确认更新后触发
	///@param	pOrder	被刷新的COrder
	///@param	poldOrder	原来的值
	virtual void commitUpdate(COrder *pOrder, CWriteableOrder *pOldOrder);
	
	///确认删除后触发
	///@param	pOrder	已经删除的COrder
	virtual void commitRemove(CWriteableOrder *pOrder);

	///所有相关的触发器
	vector<COrderActionTrigger *> *pActionTriggers;
	vector<COrderCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableOrder compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CTradeFactory是一个成交表的对象工厂。它包含了一批成交表，
///同时又建立了如下索引，以方便查询：
///	ExchangeIDTradeIDIndex
///	ExchangeIDTradeIDOrderSysIDIndex
///使用本对象工厂，可以完成对成交表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByExchangeIDTradeIDOrderSysID，唯一找到对象
///		使用startFindByExchangeIDAndTradeID，findNextByExchangeIDAndTradeID和endFindByExchangeIDAndTradeID完成查询操作
///		使用startFindAllByExchIDInvIDUserID，findNextAllByExchIDInvIDUserID和endFindAllByExchIDInvIDUserID完成查询操作
///		使用startFindAllByInvestorID，findNextAllByInvestorID和endFindAllByInvestorID完成查询操作
///		使用startFindAllByExchIDInstruIDUserID，findNextAllByExchIDInstruIDUserID和endFindAllByExchIDInstruIDUserID完成查询操作
///		使用startFindAll，findNextAll和endFindAll完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CTradeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxTrade，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CTradeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CTradeFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的Trade
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的Trade，文件名将根据配置文件中的定义TradeCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的Trade
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的Trade，文件名将根据配置文件中的定义TradeCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CTradeResource;

	///将一个CTrade加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pTrade	要加入的Trade
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CTrade *add(CWriteableTrade *pTrade, CTransaction *pTransaction=NULL);
	
	///刷新该CTrade的值
	///@param	pTrade	被刷新的CTrade
	///@param	pNewTrade	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CTrade *pTrade, CWriteableTrade *pNewTrade, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pTrade	  需要被刷新或者新增的CTrade,等于NULL表示是需要新增的
	///@param	pNewTrade	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CTrade* addOrUpdate(CTrade *pTrade, CWriteableTrade *pNewTrade, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CTrade，同时删除其索引
	///@param	pTrade	要删除的CTrade
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CTrade *pTrade, CTransaction *pTransaction=NULL);
	
	///获取某个CTrade
	///@param	pTrade	要读取的CTrade
	///@param	pTragetTrade	存放结果的CTrade
	void retrieve(CTrade *pTrade, CWriteableTrade *pTargetTrade);
	
	///获取第一个CTrade
	///@return	得到的第一个CTrade，如果没有，则返回NULL
	CTrade *getFirst(void);
	
	///获取下一个CTrade
	///@return	得到下一个CTrade，如果没有，则返回NULL
	CTrade *getNext(void);
	
	///结束获取CTrade
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CTradeActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CTradeActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CTradeCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CTradeCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CTrade
	///@param	ExchangeID	交易所编号
	///@param	TradeID	成交编号
	///@param	OrderSysID	系统报单号
	///@return	找到的CTrade，如果找不到，返回NULL
	CTrade *findByExchangeIDTradeIDOrderSysID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyTradeIDType&  TradeID,  const CReadOnlyOrderSysIDType&  OrderSysID);

	///根据主码寻找
	///@param	ExchangeID	交易所编号
	///@param	TradeID	成交编号
	///@param	OrderSysID	系统报单号
	///@return	找到的CTrade，如果找不到，返回NULL
	CTrade *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyTradeIDType&  TradeID,  const CReadOnlyOrderSysIDType&  OrderSysID);
	
	///根据主键寻找CTrade
	///@param	pTrade	要找的值
	///@return	找到的CTrade，如果找不到，返回NULL
	CTrade *findByPK(CWriteableTrade *pTrade);

	///根据主键获取CTrade
	///@param	pTrade	要获取的值，同时用于存放返回的结果
	///@return	找到的CTrade，如果找不到，返回NULL
	bool retrieveByPK(CWriteableTrade *pTrade);

	///根据主键增加新的CTrade
	///@param	pTrade	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CTrade，如果插入失败，则返回NULL
	CTrade *addByPK(CWriteableTrade *pTrade, CTransaction *pTransaction=NULL);

	///根据主键更新CTrade的值
	///@param	pTrade	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableTrade *pTrade, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CTrade
	///@param	pTrade	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableTrade *pTrade, CTransaction *pTransaction=NULL);


	friend class CTradeIteratorByExchangeIDAndTradeID;

	///开始寻找CTrade
	///@param	ExchangeID	交易所代码
	///@param	TradeID	成交编号
	///@return	满足条件的地一个CTrade，如果找不到，返回NULL
	CTrade *startFindByExchangeIDAndTradeID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyTradeIDType& TradeID);

	///寻找下一个符合条件的CTrade，必须在startFindByExchangeIDAndTradeID以后，endFindByExchangeIDAndTradeID之前叫用
	///@return	下一个满足条件CTrade，如果已经没有一个满足要求了，则返回NULL
	CTrade *findNextByExchangeIDAndTradeID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindByExchangeIDAndTradeID(void);

	friend class CTradeIteratorAllByExchIDInvIDUserID;

	///开始寻找CTrade
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	UserID	交易用户代码
	///@return	满足条件的地一个CTrade，如果找不到，返回NULL
	CTrade *startFindAllByExchIDInvIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInvestorIDType& InvestorID,  const CReadOnlyUserIDType& UserID);

	///寻找下一个符合条件的CTrade，必须在startFindAllByExchIDInvIDUserID以后，endFindAllByExchIDInvIDUserID之前叫用
	///@return	下一个满足条件CTrade，如果已经没有一个满足要求了，则返回NULL
	CTrade *findNextAllByExchIDInvIDUserID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByExchIDInvIDUserID(void);

	friend class CTradeIteratorAllByInvestorID;

	///开始寻找CTrade
	///@param	InvestorID	投资者编号
	///@return	满足条件的地一个CTrade，如果找不到，返回NULL
	CTrade *startFindAllByInvestorID( const CReadOnlyInvestorIDType& InvestorID);

	///寻找下一个符合条件的CTrade，必须在startFindAllByInvestorID以后，endFindAllByInvestorID之前叫用
	///@return	下一个满足条件CTrade，如果已经没有一个满足要求了，则返回NULL
	CTrade *findNextAllByInvestorID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByInvestorID(void);

	friend class CTradeIteratorAllByExchIDInstruIDUserID;

	///开始寻找CTrade
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约号
	///@param	UserID	交易用户代码
	///@return	满足条件的地一个CTrade，如果找不到，返回NULL
	CTrade *startFindAllByExchIDInstruIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& InstrumentID,  const CReadOnlyUserIDType& UserID);

	///寻找下一个符合条件的CTrade，必须在startFindAllByExchIDInstruIDUserID以后，endFindAllByExchIDInstruIDUserID之前叫用
	///@return	下一个满足条件CTrade，如果已经没有一个满足要求了，则返回NULL
	CTrade *findNextAllByExchIDInstruIDUserID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByExchIDInstruIDUserID(void);

	friend class CTradeIteratorAll;

	///开始寻找CTrade
	///@return	满足条件的地一个CTrade，如果找不到，返回NULL
	CTrade *startFindAll();

	///寻找下一个符合条件的CTrade，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CTrade，如果已经没有一个满足要求了，则返回NULL
	CTrade *findNextAll(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAll(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CTrade加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pTrade	要加入的Trade
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CTrade *internalAdd(CWriteableTrade *pTrade, bool bNoTransaction);
	
	
	///刷新该CTrade的键值
	///@param	pTrade	被刷新的CTrade
	///@param	pNewTrade	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CTrade *pTrade, CWriteableTrade *pNewTrade, bool updateIndex,bool bNoTransaction);
	
	///删除一个CTrade，同时删除其索引
	///@param	pTrade	要删除的CTrade
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CTrade *pTrade, bool bNoTransaction);
/*
	///检查某个CTrade是否属于本对象工厂
	///@param	pTrade	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CTrade *pTrade);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于ExchangeID+TradeID的索引
	CAVLTree *pExchangeIDTradeIDIndex;
	///基于ExchangeID+TradeID+OrderSysID的索引
	CAVLTree *pExchangeIDTradeIDOrderSysIDIndex;
	
	
	///按照ExchangeID，TradeID检索时，存储的查询参数
	CExchangeIDType queryExchangeIDInSearchByExchangeIDAndTradeID;
	CTradeIDType queryTradeIDInSearchByExchangeIDAndTradeID;
	
	///按照ExchangeID，TradeID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchByExchangeIDAndTradeID;
	///按照ExchangeID，InvestorID，UserID检索时，存储的查询参数
	CExchangeIDType queryExchangeIDInSearchAllByExchIDInvIDUserID;
	CInvestorIDType queryInvestorIDInSearchAllByExchIDInvIDUserID;
	CUserIDType queryUserIDInSearchAllByExchIDInvIDUserID;
	
	///按照ExchangeID，InvestorID，UserID检索时，存储最后一次找到的索引节点
	CTrade *pLastFoundInSearchAllByExchIDInvIDUserID;
	///按照InvestorID检索时，存储的查询参数
	CInvestorIDType queryInvestorIDInSearchAllByInvestorID;
	
	///按照InvestorID检索时，存储最后一次找到的索引节点
	CTrade *pLastFoundInSearchAllByInvestorID;
	///按照ExchangeID，InstrumentID，UserID检索时，存储的查询参数
	CExchangeIDType queryExchangeIDInSearchAllByExchIDInstruIDUserID;
	CInstrumentIDType queryInstrumentIDInSearchAllByExchIDInstruIDUserID;
	CUserIDType queryUserIDInSearchAllByExchIDInstruIDUserID;
	
	///按照ExchangeID，InstrumentID，UserID检索时，存储最后一次找到的索引节点
	CTrade *pLastFoundInSearchAllByExchIDInstruIDUserID;
	///按照检索时，存储的查询参数
	
	///按照检索时，存储最后一次找到的索引节点
	CTrade *pLastFoundInSearchAll;
	
	///加入前触发
	///@param	pTrade	要加入的Trade
	virtual void beforeAdd(CWriteableTrade *pTrade);
	
	///加入后触发
	///@param	pTrade	已经加入的Trade
	virtual void afterAdd(CTrade *pTrade);

	///更新前触发	
	///@param	pTrade	被刷新的CTrade
	///@param	pNewTrade	新的值
	virtual void beforeUpdate(CTrade *pTrade, CWriteableTrade *pNewTrade);
	
	///更新后触发
	///@param	pTrade	被刷新的CTrade
	virtual void afterUpdate(CTrade *pTrade);
	
	///删除前触发
	///@param	pTrade	要删除的CTrade
	virtual void beforeRemove(CTrade *pTrade);
	
	///确认加入后触发
	///@param	pTrade	已经加入的Trade
	virtual void commitAdd(CTrade *pTrade);

	///确认更新后触发
	///@param	pTrade	被刷新的CTrade
	///@param	poldTrade	原来的值
	virtual void commitUpdate(CTrade *pTrade, CWriteableTrade *pOldTrade);
	
	///确认删除后触发
	///@param	pTrade	已经删除的CTrade
	virtual void commitRemove(CWriteableTrade *pTrade);

	///所有相关的触发器
	vector<CTradeActionTrigger *> *pActionTriggers;
	vector<CTradeCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableTrade compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderFactory是一个预委托表的对象工厂。它包含了一批预委托表，
///同时又建立了如下索引，以方便查询：
///	APIIDAndOrderLocalIDIndex
///	APIIDIndex
///使用本对象工厂，可以完成对预委托表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByAPIIDAndOrderLocalID，唯一找到对象
///		使用findByUserIDAndUserOrderLocalID，唯一找到对象
///		使用startFindByAPIID，findNextByAPIID和endFindByAPIID完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CPreOrderFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxPreOrder，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CPreOrderFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CPreOrderFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的PreOrder
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的PreOrder，文件名将根据配置文件中的定义PreOrderCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的PreOrder
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的PreOrder，文件名将根据配置文件中的定义PreOrderCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CPreOrderResource;

	///将一个CPreOrder加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pPreOrder	要加入的PreOrder
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CPreOrder *add(CWriteablePreOrder *pPreOrder, CTransaction *pTransaction=NULL);
	
	///刷新该CPreOrder的值
	///@param	pPreOrder	被刷新的CPreOrder
	///@param	pNewPreOrder	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pPreOrder	  需要被刷新或者新增的CPreOrder,等于NULL表示是需要新增的
	///@param	pNewPreOrder	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CPreOrder* addOrUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CPreOrder，同时删除其索引
	///@param	pPreOrder	要删除的CPreOrder
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CPreOrder *pPreOrder, CTransaction *pTransaction=NULL);
	
	///获取某个CPreOrder
	///@param	pPreOrder	要读取的CPreOrder
	///@param	pTragetPreOrder	存放结果的CPreOrder
	void retrieve(CPreOrder *pPreOrder, CWriteablePreOrder *pTargetPreOrder);
	
	///获取第一个CPreOrder
	///@return	得到的第一个CPreOrder，如果没有，则返回NULL
	CPreOrder *getFirst(void);
	
	///获取下一个CPreOrder
	///@return	得到下一个CPreOrder，如果没有，则返回NULL
	CPreOrder *getNext(void);
	
	///结束获取CPreOrder
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CPreOrderActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CPreOrderActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CPreOrderCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CPreOrderCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///构造所有对应的投资者的指针
	///@param	pFactory	构造对应的投资者的指针时，寻找的对象工厂
	void linkAllInvestor(CInvestorFactory *pFactory);
	
	///构造所有对应的交易编码的指针
	///@param	pFactory	构造对应的交易编码的指针时，寻找的对象工厂
	void linkAllClientTradingID(CClientTradingIDFactory *pFactory);
	
	///构造所有对应的帐户的指针
	///@param	pFactory	构造对应的帐户的指针时，寻找的对象工厂
	void linkAllInvestorAccount(CInvestorAccountFactory *pFactory);
	
	///构造所有对应的合约持仓信息的指针
	///@param	pFactory	构造对应的合约持仓信息的指针时，寻找的对象工厂
	void linkAllInvestorPosition(CInvestorPositionFactory *pFactory);
	
	///构造所有对应的合约信息的指针
	///@param	pFactory	构造对应的合约信息的指针时，寻找的对象工厂
	void linkAllInstrument(CInstrumentFactory *pFactory);
	
	///构造所有对应的投资者保证金率信息的指针
	///@param	pFactory	构造对应的投资者保证金率信息的指针时，寻找的对象工厂
	void linkAllInvestorMargin(CInvestorMarginFactory *pFactory);
	
	///构造所有对应的投资者手续费率信息的指针
	///@param	pFactory	构造对应的投资者手续费率信息的指针时，寻找的对象工厂
	void linkAllInvestorFee(CInvestorFeeFactory *pFactory);
	
	///构造所有对应的投资者期权手续费率信息的指针
	///@param	pFactory	构造对应的投资者期权手续费率信息的指针时，寻找的对象工厂
	void linkAllInvestorOptionFee(CInvestorOptionFeeFactory *pFactory);
	
	///构造所有对应的合约大边组持仓信息的指针
	///@param	pFactory	构造对应的合约大边组持仓信息的指针时，寻找的对象工厂
	void linkAllClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory);
	
	///寻找CPreOrder
	///@param	APIID	通道编号
	///@param	OrderLocalID	本地报单编号
	///@return	找到的CPreOrder，如果找不到，返回NULL
	CPreOrder *findByAPIIDAndOrderLocalID( const CReadOnlyNumberType&  APIID,  const CReadOnlyOrderLocalIDType&  OrderLocalID);

	///根据主码寻找
	///@param	APIID	通道编号
	///@param	OrderLocalID	本地报单编号
	///@return	找到的CPreOrder，如果找不到，返回NULL
	CPreOrder *findByPK( const CReadOnlyNumberType&  APIID,  const CReadOnlyOrderLocalIDType&  OrderLocalID);
	
	///根据主键寻找CPreOrder
	///@param	pPreOrder	要找的值
	///@return	找到的CPreOrder，如果找不到，返回NULL
	CPreOrder *findByPK(CWriteablePreOrder *pPreOrder);

	///根据主键获取CPreOrder
	///@param	pPreOrder	要获取的值，同时用于存放返回的结果
	///@return	找到的CPreOrder，如果找不到，返回NULL
	bool retrieveByPK(CWriteablePreOrder *pPreOrder);

	///根据主键增加新的CPreOrder
	///@param	pPreOrder	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CPreOrder，如果插入失败，则返回NULL
	CPreOrder *addByPK(CWriteablePreOrder *pPreOrder, CTransaction *pTransaction=NULL);

	///根据主键更新CPreOrder的值
	///@param	pPreOrder	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteablePreOrder *pPreOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CPreOrder
	///@param	pPreOrder	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteablePreOrder *pPreOrder, CTransaction *pTransaction=NULL);


	///寻找CPreOrder
	///@param	BrokerID	经纪公司代码
	///@param	UserID	交易用户代码
	///@param	UserOrderLocalID	用户本地报单编号
	///@param	FrontID	前置号
	///@param	SessionID	会话号
	///@return	找到的CPreOrder，如果找不到，返回NULL
	CPreOrder *findByUserIDAndUserOrderLocalID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyUserOrderLocalIDType&  UserOrderLocalID,  const CReadOnlyFrontIDType&  FrontID,  const CReadOnlySessionIDType&  SessionID);



	friend class CPreOrderIteratorByAPIID;

	///开始寻找CPreOrder
	///@param	APIID	通道号
	///@return	满足条件的地一个CPreOrder，如果找不到，返回NULL
	CPreOrder *startFindByAPIID( const CReadOnlyNumberType& APIID);

	///寻找下一个符合条件的CPreOrder，必须在startFindByAPIID以后，endFindByAPIID之前叫用
	///@return	下一个满足条件CPreOrder，如果已经没有一个满足要求了，则返回NULL
	CPreOrder *findNextByAPIID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindByAPIID(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CPreOrder加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pPreOrder	要加入的PreOrder
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CPreOrder *internalAdd(CWriteablePreOrder *pPreOrder, bool bNoTransaction);
	
	
	///刷新该CPreOrder的键值
	///@param	pPreOrder	被刷新的CPreOrder
	///@param	pNewPreOrder	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder, bool updateIndex,bool bNoTransaction);
	
	///删除一个CPreOrder，同时删除其索引
	///@param	pPreOrder	要删除的CPreOrder
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CPreOrder *pPreOrder, bool bNoTransaction);
/*
	///检查某个CPreOrder是否属于本对象工厂
	///@param	pPreOrder	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CPreOrder *pPreOrder);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于APIID+OrderLocalID的索引
	CAVLTree *pAPIIDAndOrderLocalIDIndex;
	///基于APIID的索引
	CAVLTree *pAPIIDIndex;
	
	///基于UserIDAndUserOrderLocalID的hash索引
	CHashIndex *pUserIDAndUserOrderLocalIDHashIndex;
	
	///按照APIID检索时，存储的查询参数
	CNumberType queryAPIIDInSearchByAPIID;
	
	///按照APIID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchByAPIID;
	
	///加入前触发
	///@param	pPreOrder	要加入的PreOrder
	virtual void beforeAdd(CWriteablePreOrder *pPreOrder);
	
	///加入后触发
	///@param	pPreOrder	已经加入的PreOrder
	virtual void afterAdd(CPreOrder *pPreOrder);

	///更新前触发	
	///@param	pPreOrder	被刷新的CPreOrder
	///@param	pNewPreOrder	新的值
	virtual void beforeUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder);
	
	///更新后触发
	///@param	pPreOrder	被刷新的CPreOrder
	virtual void afterUpdate(CPreOrder *pPreOrder);
	
	///删除前触发
	///@param	pPreOrder	要删除的CPreOrder
	virtual void beforeRemove(CPreOrder *pPreOrder);
	
	///确认加入后触发
	///@param	pPreOrder	已经加入的PreOrder
	virtual void commitAdd(CPreOrder *pPreOrder);

	///确认更新后触发
	///@param	pPreOrder	被刷新的CPreOrder
	///@param	poldPreOrder	原来的值
	virtual void commitUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pOldPreOrder);
	
	///确认删除后触发
	///@param	pPreOrder	已经删除的CPreOrder
	virtual void commitRemove(CWriteablePreOrder *pPreOrder);

	///所有相关的触发器
	vector<CPreOrderActionTrigger *> *pActionTriggers;
	vector<CPreOrderCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteablePreOrder compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderFactory是一个索引预委托表的对象工厂。它包含了一批索引预委托表，
///同时又建立了如下索引，以方便查询：
///使用本对象工厂，可以完成对索引预委托表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByALLFlds，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CIndexPreOrderFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxIndexPreOrder，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CIndexPreOrderFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CIndexPreOrderFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的IndexPreOrder
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的IndexPreOrder，文件名将根据配置文件中的定义IndexPreOrderCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的IndexPreOrder
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的IndexPreOrder，文件名将根据配置文件中的定义IndexPreOrderCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CIndexPreOrderResource;

	///将一个CIndexPreOrder加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pIndexPreOrder	要加入的IndexPreOrder
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CIndexPreOrder *add(CWriteableIndexPreOrder *pIndexPreOrder, CTransaction *pTransaction=NULL);
	
	///刷新该CIndexPreOrder的值
	///@param	pIndexPreOrder	被刷新的CIndexPreOrder
	///@param	pNewIndexPreOrder	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pIndexPreOrder	  需要被刷新或者新增的CIndexPreOrder,等于NULL表示是需要新增的
	///@param	pNewIndexPreOrder	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CIndexPreOrder* addOrUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CIndexPreOrder，同时删除其索引
	///@param	pIndexPreOrder	要删除的CIndexPreOrder
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CIndexPreOrder *pIndexPreOrder, CTransaction *pTransaction=NULL);
	
	///获取某个CIndexPreOrder
	///@param	pIndexPreOrder	要读取的CIndexPreOrder
	///@param	pTragetIndexPreOrder	存放结果的CIndexPreOrder
	void retrieve(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pTargetIndexPreOrder);
	
	///获取第一个CIndexPreOrder
	///@return	得到的第一个CIndexPreOrder，如果没有，则返回NULL
	CIndexPreOrder *getFirst(void);
	
	///获取下一个CIndexPreOrder
	///@return	得到下一个CIndexPreOrder，如果没有，则返回NULL
	CIndexPreOrder *getNext(void);
	
	///结束获取CIndexPreOrder
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CIndexPreOrderActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CIndexPreOrderActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CIndexPreOrderCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CIndexPreOrderCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///构造所有对应的投资者的指针
	///@param	pFactory	构造对应的投资者的指针时，寻找的对象工厂
	void linkAllInvestor(CInvestorFactory *pFactory);
	
	///构造所有对应的交易编码的指针
	///@param	pFactory	构造对应的交易编码的指针时，寻找的对象工厂
	void linkAllClientTradingID(CClientTradingIDFactory *pFactory);
	
	///构造所有对应的帐户的指针
	///@param	pFactory	构造对应的帐户的指针时，寻找的对象工厂
	void linkAllInvestorAccount(CInvestorAccountFactory *pFactory);
	
	///构造所有对应的合约信息的指针
	///@param	pFactory	构造对应的合约信息的指针时，寻找的对象工厂
	void linkAllInstrument(CInstrumentFactory *pFactory);
	
	///构造所有对应的投资者保证金率信息的指针
	///@param	pFactory	构造对应的投资者保证金率信息的指针时，寻找的对象工厂
	void linkAllInvestorMargin(CInvestorMarginFactory *pFactory);
	
	///构造所有对应的投资者手续费率信息的指针
	///@param	pFactory	构造对应的投资者手续费率信息的指针时，寻找的对象工厂
	void linkAllInvestorFee(CInvestorFeeFactory *pFactory);
	
	///构造所有对应的合约大边组持仓信息的指针
	///@param	pFactory	构造对应的合约大边组持仓信息的指针时，寻找的对象工厂
	void linkAllClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory);
	
	///寻找CIndexPreOrder
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	InstrumentID	合约编号
	///@param	HedgeFlag	投机套保标志
	///@return	找到的CIndexPreOrder，如果找不到，返回NULL
	CIndexPreOrder *findByALLFlds( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyHedgeFlagType&  HedgeFlag);

	///根据主码寻找
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	InstrumentID	合约编号
	///@param	HedgeFlag	投机套保标志
	///@return	找到的CIndexPreOrder，如果找不到，返回NULL
	CIndexPreOrder *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyHedgeFlagType&  HedgeFlag);
	
	///根据主键寻找CIndexPreOrder
	///@param	pIndexPreOrder	要找的值
	///@return	找到的CIndexPreOrder，如果找不到，返回NULL
	CIndexPreOrder *findByPK(CWriteableIndexPreOrder *pIndexPreOrder);

	///根据主键获取CIndexPreOrder
	///@param	pIndexPreOrder	要获取的值，同时用于存放返回的结果
	///@return	找到的CIndexPreOrder，如果找不到，返回NULL
	bool retrieveByPK(CWriteableIndexPreOrder *pIndexPreOrder);

	///根据主键增加新的CIndexPreOrder
	///@param	pIndexPreOrder	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CIndexPreOrder，如果插入失败，则返回NULL
	CIndexPreOrder *addByPK(CWriteableIndexPreOrder *pIndexPreOrder, CTransaction *pTransaction=NULL);

	///根据主键更新CIndexPreOrder的值
	///@param	pIndexPreOrder	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableIndexPreOrder *pIndexPreOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CIndexPreOrder
	///@param	pIndexPreOrder	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableIndexPreOrder *pIndexPreOrder, CTransaction *pTransaction=NULL);


private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CIndexPreOrder加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pIndexPreOrder	要加入的IndexPreOrder
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CIndexPreOrder *internalAdd(CWriteableIndexPreOrder *pIndexPreOrder, bool bNoTransaction);
	
	
	///刷新该CIndexPreOrder的键值
	///@param	pIndexPreOrder	被刷新的CIndexPreOrder
	///@param	pNewIndexPreOrder	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder, bool updateIndex,bool bNoTransaction);
	
	///删除一个CIndexPreOrder，同时删除其索引
	///@param	pIndexPreOrder	要删除的CIndexPreOrder
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CIndexPreOrder *pIndexPreOrder, bool bNoTransaction);
/*
	///检查某个CIndexPreOrder是否属于本对象工厂
	///@param	pIndexPreOrder	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CIndexPreOrder *pIndexPreOrder);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	
	///基于ALLFlds的hash索引
	CHashIndex *pALLFldsHashIndex;
	
	
	///加入前触发
	///@param	pIndexPreOrder	要加入的IndexPreOrder
	virtual void beforeAdd(CWriteableIndexPreOrder *pIndexPreOrder);
	
	///加入后触发
	///@param	pIndexPreOrder	已经加入的IndexPreOrder
	virtual void afterAdd(CIndexPreOrder *pIndexPreOrder);

	///更新前触发	
	///@param	pIndexPreOrder	被刷新的CIndexPreOrder
	///@param	pNewIndexPreOrder	新的值
	virtual void beforeUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder);
	
	///更新后触发
	///@param	pIndexPreOrder	被刷新的CIndexPreOrder
	virtual void afterUpdate(CIndexPreOrder *pIndexPreOrder);
	
	///删除前触发
	///@param	pIndexPreOrder	要删除的CIndexPreOrder
	virtual void beforeRemove(CIndexPreOrder *pIndexPreOrder);
	
	///确认加入后触发
	///@param	pIndexPreOrder	已经加入的IndexPreOrder
	virtual void commitAdd(CIndexPreOrder *pIndexPreOrder);

	///确认更新后触发
	///@param	pIndexPreOrder	被刷新的CIndexPreOrder
	///@param	poldIndexPreOrder	原来的值
	virtual void commitUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pOldIndexPreOrder);
	
	///确认删除后触发
	///@param	pIndexPreOrder	已经删除的CIndexPreOrder
	virtual void commitRemove(CWriteableIndexPreOrder *pIndexPreOrder);

	///所有相关的触发器
	vector<CIndexPreOrderActionTrigger *> *pActionTriggers;
	vector<CIndexPreOrderCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableIndexPreOrder compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionFactory是一个持仓表的对象工厂。它包含了一批持仓表，
///同时又建立了如下索引，以方便查询：
///	BrkIDExIDInvIDInsIDDirHedIndex
///	ExIDAndInstrumentIDIndex
///	InvestorIDIndex
///使用本对象工厂，可以完成对持仓表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrkIDExIDInvIDInsDirHed，唯一找到对象
///		使用startFindAllByExIDAndInstrumentID，findNextAllByExIDAndInstrumentID和endFindAllByExIDAndInstrumentID完成查询操作
///		使用startFindByInvestorID，findNextByInvestorID和endFindByInvestorID完成查询操作
///		使用startFindAllByBrokerID，findNextAllByBrokerID和endFindAllByBrokerID完成查询操作
///		使用startFindAllByInstrumentID，findNextAllByInstrumentID和endFindAllByInstrumentID完成查询操作
///		使用startFindAllByExchangeID，findNextAllByExchangeID和endFindAllByExchangeID完成查询操作
///		使用startFindAllByInvestorIDAndInstrumentID，findNextAllByInvestorIDAndInstrumentID和endFindAllByInvestorIDAndInstrumentID完成查询操作
///		使用startFindAll，findNextAll和endFindAll完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorPositionFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxInvestorPosition，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorPositionFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorPositionFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的InvestorPosition
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的InvestorPosition，文件名将根据配置文件中的定义InvestorPositionCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的InvestorPosition
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的InvestorPosition，文件名将根据配置文件中的定义InvestorPositionCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CInvestorPositionResource;

	///将一个CInvestorPosition加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestorPosition	要加入的InvestorPosition
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestorPosition *add(CWriteableInvestorPosition *pInvestorPosition, CTransaction *pTransaction=NULL);
	
	///刷新该CInvestorPosition的值
	///@param	pInvestorPosition	被刷新的CInvestorPosition
	///@param	pNewInvestorPosition	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pInvestorPosition	  需要被刷新或者新增的CInvestorPosition,等于NULL表示是需要新增的
	///@param	pNewInvestorPosition	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CInvestorPosition* addOrUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CInvestorPosition，同时删除其索引
	///@param	pInvestorPosition	要删除的CInvestorPosition
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CInvestorPosition *pInvestorPosition, CTransaction *pTransaction=NULL);
	
	///获取某个CInvestorPosition
	///@param	pInvestorPosition	要读取的CInvestorPosition
	///@param	pTragetInvestorPosition	存放结果的CInvestorPosition
	void retrieve(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pTargetInvestorPosition);
	
	///获取第一个CInvestorPosition
	///@return	得到的第一个CInvestorPosition，如果没有，则返回NULL
	CInvestorPosition *getFirst(void);
	
	///获取下一个CInvestorPosition
	///@return	得到下一个CInvestorPosition，如果没有，则返回NULL
	CInvestorPosition *getNext(void);
	
	///结束获取CInvestorPosition
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CInvestorPositionActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CInvestorPositionActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CInvestorPositionCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CInvestorPositionCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CInvestorPosition
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	InstrumentID	合约编号
	///@param	Direction	多空方向
	///@param	HedgeFlag	投机套保标志
	///@return	找到的CInvestorPosition，如果找不到，返回NULL
	CInvestorPosition *findByBrkIDExIDInvIDInsDirHed( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyDirectionType&  Direction,  const CReadOnlyHedgeFlagType&  HedgeFlag);

	///根据主码寻找
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	InstrumentID	合约编号
	///@param	Direction	多空方向
	///@param	HedgeFlag	投机套保标志
	///@return	找到的CInvestorPosition，如果找不到，返回NULL
	CInvestorPosition *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyDirectionType&  Direction,  const CReadOnlyHedgeFlagType&  HedgeFlag);
	
	///根据主键寻找CInvestorPosition
	///@param	pInvestorPosition	要找的值
	///@return	找到的CInvestorPosition，如果找不到，返回NULL
	CInvestorPosition *findByPK(CWriteableInvestorPosition *pInvestorPosition);

	///根据主键获取CInvestorPosition
	///@param	pInvestorPosition	要获取的值，同时用于存放返回的结果
	///@return	找到的CInvestorPosition，如果找不到，返回NULL
	bool retrieveByPK(CWriteableInvestorPosition *pInvestorPosition);

	///根据主键增加新的CInvestorPosition
	///@param	pInvestorPosition	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CInvestorPosition，如果插入失败，则返回NULL
	CInvestorPosition *addByPK(CWriteableInvestorPosition *pInvestorPosition, CTransaction *pTransaction=NULL);

	///根据主键更新CInvestorPosition的值
	///@param	pInvestorPosition	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableInvestorPosition *pInvestorPosition, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CInvestorPosition
	///@param	pInvestorPosition	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableInvestorPosition *pInvestorPosition, CTransaction *pTransaction=NULL);


	friend class CInvestorPositionIteratorAllByExIDAndInstrumentID;

	///开始寻找CInvestorPosition
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约编号
	///@return	满足条件的地一个CInvestorPosition，如果找不到，返回NULL
	CInvestorPosition *startFindAllByExIDAndInstrumentID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& InstrumentID);

	///寻找下一个符合条件的CInvestorPosition，必须在startFindAllByExIDAndInstrumentID以后，endFindAllByExIDAndInstrumentID之前叫用
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	CInvestorPosition *findNextAllByExIDAndInstrumentID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByExIDAndInstrumentID(void);

	friend class CInvestorPositionIteratorByInvestorID;

	///开始寻找CInvestorPosition
	///@param	InvestorID	投资者号
	///@return	满足条件的地一个CInvestorPosition，如果找不到，返回NULL
	CInvestorPosition *startFindByInvestorID( const CReadOnlyInvestorIDType& InvestorID);

	///寻找下一个符合条件的CInvestorPosition，必须在startFindByInvestorID以后，endFindByInvestorID之前叫用
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	CInvestorPosition *findNextByInvestorID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindByInvestorID(void);

	friend class CInvestorPositionIteratorAllByBrokerID;

	///开始寻找CInvestorPosition
	///@param	BrokerID	经纪公司代码
	///@return	满足条件的地一个CInvestorPosition，如果找不到，返回NULL
	CInvestorPosition *startFindAllByBrokerID( const CReadOnlyBrokerIDType& BrokerID);

	///寻找下一个符合条件的CInvestorPosition，必须在startFindAllByBrokerID以后，endFindAllByBrokerID之前叫用
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	CInvestorPosition *findNextAllByBrokerID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByBrokerID(void);

	friend class CInvestorPositionIteratorAllByInstrumentID;

	///开始寻找CInvestorPosition
	///@param	InstrumentID	合约代码
	///@return	满足条件的地一个CInvestorPosition，如果找不到，返回NULL
	CInvestorPosition *startFindAllByInstrumentID( const CReadOnlyInstrumentIDType& InstrumentID);

	///寻找下一个符合条件的CInvestorPosition，必须在startFindAllByInstrumentID以后，endFindAllByInstrumentID之前叫用
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	CInvestorPosition *findNextAllByInstrumentID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByInstrumentID(void);

	friend class CInvestorPositionIteratorAllByExchangeID;

	///开始寻找CInvestorPosition
	///@param	ExchangeID	交易所编号
	///@return	满足条件的地一个CInvestorPosition，如果找不到，返回NULL
	CInvestorPosition *startFindAllByExchangeID( const CReadOnlyExchangeIDType& ExchangeID);

	///寻找下一个符合条件的CInvestorPosition，必须在startFindAllByExchangeID以后，endFindAllByExchangeID之前叫用
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	CInvestorPosition *findNextAllByExchangeID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByExchangeID(void);

	friend class CInvestorPositionIteratorAllByInvestorIDAndInstrumentID;

	///开始寻找CInvestorPosition
	///@param	InvestorID	客户号
	///@param	InstrumentID	合约代码
	///@return	满足条件的地一个CInvestorPosition，如果找不到，返回NULL
	CInvestorPosition *startFindAllByInvestorIDAndInstrumentID( const CReadOnlyInvestorIDType& InvestorID,  const CReadOnlyInstrumentIDType& InstrumentID);

	///寻找下一个符合条件的CInvestorPosition，必须在startFindAllByInvestorIDAndInstrumentID以后，endFindAllByInvestorIDAndInstrumentID之前叫用
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	CInvestorPosition *findNextAllByInvestorIDAndInstrumentID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByInvestorIDAndInstrumentID(void);

	friend class CInvestorPositionIteratorAll;

	///开始寻找CInvestorPosition
	///@return	满足条件的地一个CInvestorPosition，如果找不到，返回NULL
	CInvestorPosition *startFindAll();

	///寻找下一个符合条件的CInvestorPosition，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	CInvestorPosition *findNextAll(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAll(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CInvestorPosition加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestorPosition	要加入的InvestorPosition
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestorPosition *internalAdd(CWriteableInvestorPosition *pInvestorPosition, bool bNoTransaction);
	
	
	///刷新该CInvestorPosition的键值
	///@param	pInvestorPosition	被刷新的CInvestorPosition
	///@param	pNewInvestorPosition	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition, bool updateIndex,bool bNoTransaction);
	
	///删除一个CInvestorPosition，同时删除其索引
	///@param	pInvestorPosition	要删除的CInvestorPosition
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CInvestorPosition *pInvestorPosition, bool bNoTransaction);
/*
	///检查某个CInvestorPosition是否属于本对象工厂
	///@param	pInvestorPosition	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CInvestorPosition *pInvestorPosition);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于BrokerID+ExchangeID+InvestorID+InstrumentID+Direction+HedgeFlag的索引
	CAVLTree *pBrkIDExIDInvIDInsIDDirHedIndex;
	///基于ExchangeID+InstrumentID的索引
	CAVLTree *pExIDAndInstrumentIDIndex;
	///基于InvestorID的索引
	CAVLTree *pInvestorIDIndex;
	
	
	///按照ExchangeID，InstrumentID检索时，存储的查询参数
	CExchangeIDType queryExchangeIDInSearchAllByExIDAndInstrumentID;
	CInstrumentIDType queryInstrumentIDInSearchAllByExIDAndInstrumentID;
	
	///按照ExchangeID，InstrumentID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchAllByExIDAndInstrumentID;
	///按照InvestorID检索时，存储的查询参数
	CInvestorIDType queryInvestorIDInSearchByInvestorID;
	
	///按照InvestorID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchByInvestorID;
	///按照BrokerID检索时，存储的查询参数
	CBrokerIDType queryBrokerIDInSearchAllByBrokerID;
	
	///按照BrokerID检索时，存储最后一次找到的索引节点
	CInvestorPosition *pLastFoundInSearchAllByBrokerID;
	///按照InstrumentID检索时，存储的查询参数
	CInstrumentIDType queryInstrumentIDInSearchAllByInstrumentID;
	
	///按照InstrumentID检索时，存储最后一次找到的索引节点
	CInvestorPosition *pLastFoundInSearchAllByInstrumentID;
	///按照ExchangeID检索时，存储的查询参数
	CExchangeIDType queryExchangeIDInSearchAllByExchangeID;
	
	///按照ExchangeID检索时，存储最后一次找到的索引节点
	CInvestorPosition *pLastFoundInSearchAllByExchangeID;
	///按照InvestorID，InstrumentID检索时，存储的查询参数
	CInvestorIDType queryInvestorIDInSearchAllByInvestorIDAndInstrumentID;
	CInstrumentIDType queryInstrumentIDInSearchAllByInvestorIDAndInstrumentID;
	
	///按照InvestorID，InstrumentID检索时，存储最后一次找到的索引节点
	CInvestorPosition *pLastFoundInSearchAllByInvestorIDAndInstrumentID;
	///按照检索时，存储的查询参数
	
	///按照检索时，存储最后一次找到的索引节点
	CInvestorPosition *pLastFoundInSearchAll;
	
	///加入前触发
	///@param	pInvestorPosition	要加入的InvestorPosition
	virtual void beforeAdd(CWriteableInvestorPosition *pInvestorPosition);
	
	///加入后触发
	///@param	pInvestorPosition	已经加入的InvestorPosition
	virtual void afterAdd(CInvestorPosition *pInvestorPosition);

	///更新前触发	
	///@param	pInvestorPosition	被刷新的CInvestorPosition
	///@param	pNewInvestorPosition	新的值
	virtual void beforeUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition);
	
	///更新后触发
	///@param	pInvestorPosition	被刷新的CInvestorPosition
	virtual void afterUpdate(CInvestorPosition *pInvestorPosition);
	
	///删除前触发
	///@param	pInvestorPosition	要删除的CInvestorPosition
	virtual void beforeRemove(CInvestorPosition *pInvestorPosition);
	
	///确认加入后触发
	///@param	pInvestorPosition	已经加入的InvestorPosition
	virtual void commitAdd(CInvestorPosition *pInvestorPosition);

	///确认更新后触发
	///@param	pInvestorPosition	被刷新的CInvestorPosition
	///@param	poldInvestorPosition	原来的值
	virtual void commitUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pOldInvestorPosition);
	
	///确认删除后触发
	///@param	pInvestorPosition	已经删除的CInvestorPosition
	virtual void commitRemove(CWriteableInvestorPosition *pInvestorPosition);

	///所有相关的触发器
	vector<CInvestorPositionActionTrigger *> *pActionTriggers;
	vector<CInvestorPositionCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableInvestorPosition compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountFactory是一个账户实时资金表的对象工厂。它包含了一批账户实时资金表，
///同时又建立了如下索引，以方便查询：
///	BrokerIDAccountIDIndex
///	BrokerIDInvestorIDIndex
///使用本对象工厂，可以完成对账户实时资金表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrokerIDAccountID，唯一找到对象
///		使用startFindAllByInvestorID，findNextAllByInvestorID和endFindAllByInvestorID完成查询操作
///		使用findByBrokerIDInvestorID，唯一找到对象
///		使用startFindAllByBrokerID，findNextAllByBrokerID和endFindAllByBrokerID完成查询操作
///		使用startFindAll，findNextAll和endFindAll完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorAccountFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxInvestorAccount，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorAccountFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorAccountFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的InvestorAccount
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的InvestorAccount，文件名将根据配置文件中的定义InvestorAccountCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的InvestorAccount
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的InvestorAccount，文件名将根据配置文件中的定义InvestorAccountCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CInvestorAccountResource;

	///将一个CInvestorAccount加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestorAccount	要加入的InvestorAccount
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestorAccount *add(CWriteableInvestorAccount *pInvestorAccount, CTransaction *pTransaction=NULL);
	
	///刷新该CInvestorAccount的值
	///@param	pInvestorAccount	被刷新的CInvestorAccount
	///@param	pNewInvestorAccount	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pInvestorAccount	  需要被刷新或者新增的CInvestorAccount,等于NULL表示是需要新增的
	///@param	pNewInvestorAccount	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CInvestorAccount* addOrUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CInvestorAccount，同时删除其索引
	///@param	pInvestorAccount	要删除的CInvestorAccount
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CInvestorAccount *pInvestorAccount, CTransaction *pTransaction=NULL);
	
	///获取某个CInvestorAccount
	///@param	pInvestorAccount	要读取的CInvestorAccount
	///@param	pTragetInvestorAccount	存放结果的CInvestorAccount
	void retrieve(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pTargetInvestorAccount);
	
	///获取第一个CInvestorAccount
	///@return	得到的第一个CInvestorAccount，如果没有，则返回NULL
	CInvestorAccount *getFirst(void);
	
	///获取下一个CInvestorAccount
	///@return	得到下一个CInvestorAccount，如果没有，则返回NULL
	CInvestorAccount *getNext(void);
	
	///结束获取CInvestorAccount
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CInvestorAccountActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CInvestorAccountActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CInvestorAccountCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CInvestorAccountCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CInvestorAccount
	///@param	BrokerID	经纪商编号
	///@param	AccountID	资金帐号
	///@return	找到的CInvestorAccount，如果找不到，返回NULL
	CInvestorAccount *findByBrokerIDAccountID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyAccountIDType&  AccountID);

	///根据主码寻找
	///@param	BrokerID	经纪商编号
	///@param	AccountID	资金帐号
	///@return	找到的CInvestorAccount，如果找不到，返回NULL
	CInvestorAccount *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyAccountIDType&  AccountID);
	
	///根据主键寻找CInvestorAccount
	///@param	pInvestorAccount	要找的值
	///@return	找到的CInvestorAccount，如果找不到，返回NULL
	CInvestorAccount *findByPK(CWriteableInvestorAccount *pInvestorAccount);

	///根据主键获取CInvestorAccount
	///@param	pInvestorAccount	要获取的值，同时用于存放返回的结果
	///@return	找到的CInvestorAccount，如果找不到，返回NULL
	bool retrieveByPK(CWriteableInvestorAccount *pInvestorAccount);

	///根据主键增加新的CInvestorAccount
	///@param	pInvestorAccount	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CInvestorAccount，如果插入失败，则返回NULL
	CInvestorAccount *addByPK(CWriteableInvestorAccount *pInvestorAccount, CTransaction *pTransaction=NULL);

	///根据主键更新CInvestorAccount的值
	///@param	pInvestorAccount	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableInvestorAccount *pInvestorAccount, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CInvestorAccount
	///@param	pInvestorAccount	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableInvestorAccount *pInvestorAccount, CTransaction *pTransaction=NULL);


	friend class CInvestorAccountIteratorAllByInvestorID;

	///开始寻找CInvestorAccount
	///@param	InvestorID	投资者编号
	///@return	满足条件的地一个CInvestorAccount，如果找不到，返回NULL
	CInvestorAccount *startFindAllByInvestorID( const CReadOnlyInvestorIDType& InvestorID);

	///寻找下一个符合条件的CInvestorAccount，必须在startFindAllByInvestorID以后，endFindAllByInvestorID之前叫用
	///@return	下一个满足条件CInvestorAccount，如果已经没有一个满足要求了，则返回NULL
	CInvestorAccount *findNextAllByInvestorID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByInvestorID(void);

	///寻找CInvestorAccount
	///@param	BrokerID	经纪商编号
	///@param	InvestorID	投资者编号
	///@return	找到的CInvestorAccount，如果找不到，返回NULL
	CInvestorAccount *findByBrokerIDInvestorID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInvestorIDType&  InvestorID);



	friend class CInvestorAccountIteratorAllByBrokerID;

	///开始寻找CInvestorAccount
	///@param	BrokerID	经纪公司代码
	///@return	满足条件的地一个CInvestorAccount，如果找不到，返回NULL
	CInvestorAccount *startFindAllByBrokerID( const CReadOnlyBrokerIDType& BrokerID);

	///寻找下一个符合条件的CInvestorAccount，必须在startFindAllByBrokerID以后，endFindAllByBrokerID之前叫用
	///@return	下一个满足条件CInvestorAccount，如果已经没有一个满足要求了，则返回NULL
	CInvestorAccount *findNextAllByBrokerID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByBrokerID(void);

	friend class CInvestorAccountIteratorAll;

	///开始寻找CInvestorAccount
	///@return	满足条件的地一个CInvestorAccount，如果找不到，返回NULL
	CInvestorAccount *startFindAll();

	///寻找下一个符合条件的CInvestorAccount，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CInvestorAccount，如果已经没有一个满足要求了，则返回NULL
	CInvestorAccount *findNextAll(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAll(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CInvestorAccount加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestorAccount	要加入的InvestorAccount
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestorAccount *internalAdd(CWriteableInvestorAccount *pInvestorAccount, bool bNoTransaction);
	
	
	///刷新该CInvestorAccount的键值
	///@param	pInvestorAccount	被刷新的CInvestorAccount
	///@param	pNewInvestorAccount	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount, bool updateIndex,bool bNoTransaction);
	
	///删除一个CInvestorAccount，同时删除其索引
	///@param	pInvestorAccount	要删除的CInvestorAccount
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CInvestorAccount *pInvestorAccount, bool bNoTransaction);
/*
	///检查某个CInvestorAccount是否属于本对象工厂
	///@param	pInvestorAccount	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CInvestorAccount *pInvestorAccount);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于BrokerID+AccountID的索引
	CAVLTree *pBrokerIDAccountIDIndex;
	///基于BrokerID+InvestorID的索引
	CAVLTree *pBrokerIDInvestorIDIndex;
	
	
	///按照InvestorID检索时，存储的查询参数
	CInvestorIDType queryInvestorIDInSearchAllByInvestorID;
	
	///按照InvestorID检索时，存储最后一次找到的索引节点
	CInvestorAccount *pLastFoundInSearchAllByInvestorID;
	///按照BrokerID检索时，存储的查询参数
	CBrokerIDType queryBrokerIDInSearchAllByBrokerID;
	
	///按照BrokerID检索时，存储最后一次找到的索引节点
	CInvestorAccount *pLastFoundInSearchAllByBrokerID;
	///按照检索时，存储的查询参数
	
	///按照检索时，存储最后一次找到的索引节点
	CInvestorAccount *pLastFoundInSearchAll;
	
	///加入前触发
	///@param	pInvestorAccount	要加入的InvestorAccount
	virtual void beforeAdd(CWriteableInvestorAccount *pInvestorAccount);
	
	///加入后触发
	///@param	pInvestorAccount	已经加入的InvestorAccount
	virtual void afterAdd(CInvestorAccount *pInvestorAccount);

	///更新前触发	
	///@param	pInvestorAccount	被刷新的CInvestorAccount
	///@param	pNewInvestorAccount	新的值
	virtual void beforeUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount);
	
	///更新后触发
	///@param	pInvestorAccount	被刷新的CInvestorAccount
	virtual void afterUpdate(CInvestorAccount *pInvestorAccount);
	
	///删除前触发
	///@param	pInvestorAccount	要删除的CInvestorAccount
	virtual void beforeRemove(CInvestorAccount *pInvestorAccount);
	
	///确认加入后触发
	///@param	pInvestorAccount	已经加入的InvestorAccount
	virtual void commitAdd(CInvestorAccount *pInvestorAccount);

	///确认更新后触发
	///@param	pInvestorAccount	被刷新的CInvestorAccount
	///@param	poldInvestorAccount	原来的值
	virtual void commitUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pOldInvestorAccount);
	
	///确认删除后触发
	///@param	pInvestorAccount	已经删除的CInvestorAccount
	virtual void commitRemove(CWriteableInvestorAccount *pInvestorAccount);

	///所有相关的触发器
	vector<CInvestorAccountActionTrigger *> *pActionTriggers;
	vector<CInvestorAccountCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableInvestorAccount compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositFactory是一个账户实时出入金表的对象工厂。它包含了一批账户实时出入金表，
///同时又建立了如下索引，以方便查询：
///	BrokerIDAccountSeqNoIndex
///使用本对象工厂，可以完成对账户实时出入金表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrokerIDAccountSeqNo，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorAccountDepositFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxInvestorAccountDeposit，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorAccountDepositFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorAccountDepositFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的InvestorAccountDeposit
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的InvestorAccountDeposit，文件名将根据配置文件中的定义InvestorAccountDepositCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的InvestorAccountDeposit
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的InvestorAccountDeposit，文件名将根据配置文件中的定义InvestorAccountDepositCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CInvestorAccountDepositResource;

	///将一个CInvestorAccountDeposit加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestorAccountDeposit	要加入的InvestorAccountDeposit
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestorAccountDeposit *add(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit, CTransaction *pTransaction=NULL);
	
	///刷新该CInvestorAccountDeposit的值
	///@param	pInvestorAccountDeposit	被刷新的CInvestorAccountDeposit
	///@param	pNewInvestorAccountDeposit	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pInvestorAccountDeposit	  需要被刷新或者新增的CInvestorAccountDeposit,等于NULL表示是需要新增的
	///@param	pNewInvestorAccountDeposit	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CInvestorAccountDeposit* addOrUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CInvestorAccountDeposit，同时删除其索引
	///@param	pInvestorAccountDeposit	要删除的CInvestorAccountDeposit
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CInvestorAccountDeposit *pInvestorAccountDeposit, CTransaction *pTransaction=NULL);
	
	///获取某个CInvestorAccountDeposit
	///@param	pInvestorAccountDeposit	要读取的CInvestorAccountDeposit
	///@param	pTragetInvestorAccountDeposit	存放结果的CInvestorAccountDeposit
	void retrieve(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pTargetInvestorAccountDeposit);
	
	///获取第一个CInvestorAccountDeposit
	///@return	得到的第一个CInvestorAccountDeposit，如果没有，则返回NULL
	CInvestorAccountDeposit *getFirst(void);
	
	///获取下一个CInvestorAccountDeposit
	///@return	得到下一个CInvestorAccountDeposit，如果没有，则返回NULL
	CInvestorAccountDeposit *getNext(void);
	
	///结束获取CInvestorAccountDeposit
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CInvestorAccountDepositActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CInvestorAccountDepositActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CInvestorAccountDepositCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CInvestorAccountDepositCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CInvestorAccountDeposit
	///@param	BrokerID	经纪商编号
	///@param	AccountSeqNo	资金流水号
	///@return	找到的CInvestorAccountDeposit，如果找不到，返回NULL
	CInvestorAccountDeposit *findByBrokerIDAccountSeqNo( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyAccountSeqNoType&  AccountSeqNo);

	///根据主码寻找
	///@param	BrokerID	经纪商编号
	///@param	AccountSeqNo	资金流水号
	///@return	找到的CInvestorAccountDeposit，如果找不到，返回NULL
	CInvestorAccountDeposit *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyAccountSeqNoType&  AccountSeqNo);
	
	///根据主键寻找CInvestorAccountDeposit
	///@param	pInvestorAccountDeposit	要找的值
	///@return	找到的CInvestorAccountDeposit，如果找不到，返回NULL
	CInvestorAccountDeposit *findByPK(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit);

	///根据主键获取CInvestorAccountDeposit
	///@param	pInvestorAccountDeposit	要获取的值，同时用于存放返回的结果
	///@return	找到的CInvestorAccountDeposit，如果找不到，返回NULL
	bool retrieveByPK(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit);

	///根据主键增加新的CInvestorAccountDeposit
	///@param	pInvestorAccountDeposit	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CInvestorAccountDeposit，如果插入失败，则返回NULL
	CInvestorAccountDeposit *addByPK(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit, CTransaction *pTransaction=NULL);

	///根据主键更新CInvestorAccountDeposit的值
	///@param	pInvestorAccountDeposit	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CInvestorAccountDeposit
	///@param	pInvestorAccountDeposit	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit, CTransaction *pTransaction=NULL);


private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CInvestorAccountDeposit加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestorAccountDeposit	要加入的InvestorAccountDeposit
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestorAccountDeposit *internalAdd(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit, bool bNoTransaction);
	
	
	///刷新该CInvestorAccountDeposit的键值
	///@param	pInvestorAccountDeposit	被刷新的CInvestorAccountDeposit
	///@param	pNewInvestorAccountDeposit	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit, bool updateIndex,bool bNoTransaction);
	
	///删除一个CInvestorAccountDeposit，同时删除其索引
	///@param	pInvestorAccountDeposit	要删除的CInvestorAccountDeposit
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CInvestorAccountDeposit *pInvestorAccountDeposit, bool bNoTransaction);
/*
	///检查某个CInvestorAccountDeposit是否属于本对象工厂
	///@param	pInvestorAccountDeposit	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CInvestorAccountDeposit *pInvestorAccountDeposit);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于BrokerID+AccountSeqNo的索引
	CAVLTree *pBrokerIDAccountSeqNoIndex;
	
	
	
	///加入前触发
	///@param	pInvestorAccountDeposit	要加入的InvestorAccountDeposit
	virtual void beforeAdd(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit);
	
	///加入后触发
	///@param	pInvestorAccountDeposit	已经加入的InvestorAccountDeposit
	virtual void afterAdd(CInvestorAccountDeposit *pInvestorAccountDeposit);

	///更新前触发	
	///@param	pInvestorAccountDeposit	被刷新的CInvestorAccountDeposit
	///@param	pNewInvestorAccountDeposit	新的值
	virtual void beforeUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit);
	
	///更新后触发
	///@param	pInvestorAccountDeposit	被刷新的CInvestorAccountDeposit
	virtual void afterUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit);
	
	///删除前触发
	///@param	pInvestorAccountDeposit	要删除的CInvestorAccountDeposit
	virtual void beforeRemove(CInvestorAccountDeposit *pInvestorAccountDeposit);
	
	///确认加入后触发
	///@param	pInvestorAccountDeposit	已经加入的InvestorAccountDeposit
	virtual void commitAdd(CInvestorAccountDeposit *pInvestorAccountDeposit);

	///确认更新后触发
	///@param	pInvestorAccountDeposit	被刷新的CInvestorAccountDeposit
	///@param	poldInvestorAccountDeposit	原来的值
	virtual void commitUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pOldInvestorAccountDeposit);
	
	///确认删除后触发
	///@param	pInvestorAccountDeposit	已经删除的CInvestorAccountDeposit
	virtual void commitRemove(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit);

	///所有相关的触发器
	vector<CInvestorAccountDepositActionTrigger *> *pActionTriggers;
	vector<CInvestorAccountDepositCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableInvestorAccountDeposit compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CExchangeFactory是一个交易所表的对象工厂。它包含了一批交易所表，
///同时又建立了如下索引，以方便查询：
///	ExchangeIDIndex
///使用本对象工厂，可以完成对交易所表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByExchangeID，唯一找到对象
///		使用startFindStartByExchangeID，findNextStartByExchangeID和endFindStartByExchangeID完成查询操作
///		使用startFindAll，findNextAll和endFindAll完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CExchangeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxExchange，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CExchangeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CExchangeFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的Exchange
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的Exchange，文件名将根据配置文件中的定义ExchangeCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的Exchange
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的Exchange，文件名将根据配置文件中的定义ExchangeCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CExchangeResource;

	///将一个CExchange加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pExchange	要加入的Exchange
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CExchange *add(CWriteableExchange *pExchange, CTransaction *pTransaction=NULL);
	
	///刷新该CExchange的值
	///@param	pExchange	被刷新的CExchange
	///@param	pNewExchange	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CExchange *pExchange, CWriteableExchange *pNewExchange, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pExchange	  需要被刷新或者新增的CExchange,等于NULL表示是需要新增的
	///@param	pNewExchange	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CExchange* addOrUpdate(CExchange *pExchange, CWriteableExchange *pNewExchange, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CExchange，同时删除其索引
	///@param	pExchange	要删除的CExchange
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CExchange *pExchange, CTransaction *pTransaction=NULL);
	
	///获取某个CExchange
	///@param	pExchange	要读取的CExchange
	///@param	pTragetExchange	存放结果的CExchange
	void retrieve(CExchange *pExchange, CWriteableExchange *pTargetExchange);
	
	///获取第一个CExchange
	///@return	得到的第一个CExchange，如果没有，则返回NULL
	CExchange *getFirst(void);
	
	///获取下一个CExchange
	///@return	得到下一个CExchange，如果没有，则返回NULL
	CExchange *getNext(void);
	
	///结束获取CExchange
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CExchangeActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CExchangeActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CExchangeCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CExchangeCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CExchange
	///@param	ExchangeID	交易所代码
	///@return	找到的CExchange，如果找不到，返回NULL
	CExchange *findByExchangeID( const CReadOnlyExchangeIDType&  ExchangeID);

	///根据主码寻找
	///@param	ExchangeID	交易所代码
	///@return	找到的CExchange，如果找不到，返回NULL
	CExchange *findByPK( const CReadOnlyExchangeIDType&  ExchangeID);
	
	///根据主键寻找CExchange
	///@param	pExchange	要找的值
	///@return	找到的CExchange，如果找不到，返回NULL
	CExchange *findByPK(CWriteableExchange *pExchange);

	///根据主键获取CExchange
	///@param	pExchange	要获取的值，同时用于存放返回的结果
	///@return	找到的CExchange，如果找不到，返回NULL
	bool retrieveByPK(CWriteableExchange *pExchange);

	///根据主键增加新的CExchange
	///@param	pExchange	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CExchange，如果插入失败，则返回NULL
	CExchange *addByPK(CWriteableExchange *pExchange, CTransaction *pTransaction=NULL);

	///根据主键更新CExchange的值
	///@param	pExchange	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableExchange *pExchange, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CExchange
	///@param	pExchange	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableExchange *pExchange, CTransaction *pTransaction=NULL);


	friend class CExchangeIteratorStartByExchangeID;

	///开始寻找CExchange
	///@param	ExchangeID	交易所代码
	///@return	满足条件的地一个CExchange，如果找不到，返回NULL
	CExchange *startFindStartByExchangeID( const CReadOnlyExchangeIDType& ExchangeID);

	///寻找下一个符合条件的CExchange，必须在startFindStartByExchangeID以后，endFindStartByExchangeID之前叫用
	///@return	下一个满足条件CExchange，如果已经没有一个满足要求了，则返回NULL
	CExchange *findNextStartByExchangeID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindStartByExchangeID(void);

	friend class CExchangeIteratorAll;

	///开始寻找CExchange
	///@return	满足条件的地一个CExchange，如果找不到，返回NULL
	CExchange *startFindAll();

	///寻找下一个符合条件的CExchange，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CExchange，如果已经没有一个满足要求了，则返回NULL
	CExchange *findNextAll(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAll(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CExchange加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pExchange	要加入的Exchange
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CExchange *internalAdd(CWriteableExchange *pExchange, bool bNoTransaction);
	
	
	///刷新该CExchange的键值
	///@param	pExchange	被刷新的CExchange
	///@param	pNewExchange	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CExchange *pExchange, CWriteableExchange *pNewExchange, bool updateIndex,bool bNoTransaction);
	
	///删除一个CExchange，同时删除其索引
	///@param	pExchange	要删除的CExchange
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CExchange *pExchange, bool bNoTransaction);
/*
	///检查某个CExchange是否属于本对象工厂
	///@param	pExchange	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CExchange *pExchange);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于ExchangeID的索引
	CAVLTree *pExchangeIDIndex;
	
	
	///按照ExchangeID检索时，存储的查询参数
	CExchangeIDType queryExchangeIDInSearchStartByExchangeID;
	
	///按照ExchangeID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchStartByExchangeID;
	///按照检索时，存储的查询参数
	
	///按照检索时，存储最后一次找到的索引节点
	CExchange *pLastFoundInSearchAll;
	
	///加入前触发
	///@param	pExchange	要加入的Exchange
	virtual void beforeAdd(CWriteableExchange *pExchange);
	
	///加入后触发
	///@param	pExchange	已经加入的Exchange
	virtual void afterAdd(CExchange *pExchange);

	///更新前触发	
	///@param	pExchange	被刷新的CExchange
	///@param	pNewExchange	新的值
	virtual void beforeUpdate(CExchange *pExchange, CWriteableExchange *pNewExchange);
	
	///更新后触发
	///@param	pExchange	被刷新的CExchange
	virtual void afterUpdate(CExchange *pExchange);
	
	///删除前触发
	///@param	pExchange	要删除的CExchange
	virtual void beforeRemove(CExchange *pExchange);
	
	///确认加入后触发
	///@param	pExchange	已经加入的Exchange
	virtual void commitAdd(CExchange *pExchange);

	///确认更新后触发
	///@param	pExchange	被刷新的CExchange
	///@param	poldExchange	原来的值
	virtual void commitUpdate(CExchange *pExchange, CWriteableExchange *pOldExchange);
	
	///确认删除后触发
	///@param	pExchange	已经删除的CExchange
	virtual void commitRemove(CWriteableExchange *pExchange);

	///所有相关的触发器
	vector<CExchangeActionTrigger *> *pActionTriggers;
	vector<CExchangeCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableExchange compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CSeatFactory是一个下单席位表的对象工厂。它包含了一批下单席位表，
///同时又建立了如下索引，以方便查询：
///	BrokerIDExchangeIDSeatIDIndex
///	ExchangeIDParticipantIDSeatIDIndex
///使用本对象工厂，可以完成对下单席位表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrokerIDExchangeIDSeatID，唯一找到对象
///		使用findByExchangeIDParticipantIDSeatID，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CSeatFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxSeat，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CSeatFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CSeatFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的Seat
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的Seat，文件名将根据配置文件中的定义SeatCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的Seat
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的Seat，文件名将根据配置文件中的定义SeatCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CSeatResource;

	///将一个CSeat加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pSeat	要加入的Seat
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CSeat *add(CWriteableSeat *pSeat, CTransaction *pTransaction=NULL);
	
	///刷新该CSeat的值
	///@param	pSeat	被刷新的CSeat
	///@param	pNewSeat	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CSeat *pSeat, CWriteableSeat *pNewSeat, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pSeat	  需要被刷新或者新增的CSeat,等于NULL表示是需要新增的
	///@param	pNewSeat	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CSeat* addOrUpdate(CSeat *pSeat, CWriteableSeat *pNewSeat, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CSeat，同时删除其索引
	///@param	pSeat	要删除的CSeat
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CSeat *pSeat, CTransaction *pTransaction=NULL);
	
	///获取某个CSeat
	///@param	pSeat	要读取的CSeat
	///@param	pTragetSeat	存放结果的CSeat
	void retrieve(CSeat *pSeat, CWriteableSeat *pTargetSeat);
	
	///获取第一个CSeat
	///@return	得到的第一个CSeat，如果没有，则返回NULL
	CSeat *getFirst(void);
	
	///获取下一个CSeat
	///@return	得到下一个CSeat，如果没有，则返回NULL
	CSeat *getNext(void);
	
	///结束获取CSeat
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CSeatActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CSeatActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CSeatCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CSeatCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CSeat
	///@param	BrokerID	经纪商编号
	///@param	ExchangeID	交易所代码
	///@param	SeatID	席位号
	///@return	找到的CSeat，如果找不到，返回NULL
	CSeat *findByBrokerIDExchangeIDSeatID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlySeatIDType&  SeatID);

	///根据主码寻找
	///@param	BrokerID	经纪商编号
	///@param	ExchangeID	交易所代码
	///@param	SeatID	席位号
	///@return	找到的CSeat，如果找不到，返回NULL
	CSeat *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlySeatIDType&  SeatID);
	
	///根据主键寻找CSeat
	///@param	pSeat	要找的值
	///@return	找到的CSeat，如果找不到，返回NULL
	CSeat *findByPK(CWriteableSeat *pSeat);

	///根据主键获取CSeat
	///@param	pSeat	要获取的值，同时用于存放返回的结果
	///@return	找到的CSeat，如果找不到，返回NULL
	bool retrieveByPK(CWriteableSeat *pSeat);

	///根据主键增加新的CSeat
	///@param	pSeat	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CSeat，如果插入失败，则返回NULL
	CSeat *addByPK(CWriteableSeat *pSeat, CTransaction *pTransaction=NULL);

	///根据主键更新CSeat的值
	///@param	pSeat	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableSeat *pSeat, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CSeat
	///@param	pSeat	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableSeat *pSeat, CTransaction *pTransaction=NULL);


	///寻找CSeat
	///@param	ExchangeID	交易所代码
	///@param	ParticipantID	会员编号
	///@param	SeatID	席位号
	///@return	找到的CSeat，如果找不到，返回NULL
	CSeat *findByExchangeIDParticipantIDSeatID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyParticipantIDType&  ParticipantID,  const CReadOnlySeatIDType&  SeatID);



private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CSeat加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pSeat	要加入的Seat
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CSeat *internalAdd(CWriteableSeat *pSeat, bool bNoTransaction);
	
	
	///刷新该CSeat的键值
	///@param	pSeat	被刷新的CSeat
	///@param	pNewSeat	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CSeat *pSeat, CWriteableSeat *pNewSeat, bool updateIndex,bool bNoTransaction);
	
	///删除一个CSeat，同时删除其索引
	///@param	pSeat	要删除的CSeat
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CSeat *pSeat, bool bNoTransaction);
/*
	///检查某个CSeat是否属于本对象工厂
	///@param	pSeat	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CSeat *pSeat);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于BrokerID+ExchangeID+SeatID的索引
	CAVLTree *pBrokerIDExchangeIDSeatIDIndex;
	///基于ExchangeID+ParticipantID+SeatID的索引
	CAVLTree *pExchangeIDParticipantIDSeatIDIndex;
	
	
	
	///加入前触发
	///@param	pSeat	要加入的Seat
	virtual void beforeAdd(CWriteableSeat *pSeat);
	
	///加入后触发
	///@param	pSeat	已经加入的Seat
	virtual void afterAdd(CSeat *pSeat);

	///更新前触发	
	///@param	pSeat	被刷新的CSeat
	///@param	pNewSeat	新的值
	virtual void beforeUpdate(CSeat *pSeat, CWriteableSeat *pNewSeat);
	
	///更新后触发
	///@param	pSeat	被刷新的CSeat
	virtual void afterUpdate(CSeat *pSeat);
	
	///删除前触发
	///@param	pSeat	要删除的CSeat
	virtual void beforeRemove(CSeat *pSeat);
	
	///确认加入后触发
	///@param	pSeat	已经加入的Seat
	virtual void commitAdd(CSeat *pSeat);

	///确认更新后触发
	///@param	pSeat	被刷新的CSeat
	///@param	poldSeat	原来的值
	virtual void commitUpdate(CSeat *pSeat, CWriteableSeat *pOldSeat);
	
	///确认删除后触发
	///@param	pSeat	已经删除的CSeat
	virtual void commitRemove(CWriteableSeat *pSeat);

	///所有相关的触发器
	vector<CSeatActionTrigger *> *pActionTriggers;
	vector<CSeatCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableSeat compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentFactory是一个期货合约表的对象工厂。它包含了一批期货合约表，
///同时又建立了如下索引，以方便查询：
///	ExchangeIDInstrumentIDIndex
///	InstrumentIDIndex
///使用本对象工厂，可以完成对期货合约表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByExchangeIDAndInstrumentID，唯一找到对象
///		使用startFindAllByInstrumentID，findNextAllByInstrumentID和endFindAllByInstrumentID完成查询操作
///		使用startFindAllByExchangeID，findNextAllByExchangeID和endFindAllByExchangeID完成查询操作
///		使用startFindAllByProductID，findNextAllByProductID和endFindAllByProductID完成查询操作
///		使用startFindAll，findNextAll和endFindAll完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInstrumentFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxInstrument，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInstrumentFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CInstrumentFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的Instrument
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的Instrument，文件名将根据配置文件中的定义InstrumentCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的Instrument
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的Instrument，文件名将根据配置文件中的定义InstrumentCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CInstrumentResource;

	///将一个CInstrument加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInstrument	要加入的Instrument
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInstrument *add(CWriteableInstrument *pInstrument, CTransaction *pTransaction=NULL);
	
	///刷新该CInstrument的值
	///@param	pInstrument	被刷新的CInstrument
	///@param	pNewInstrument	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pInstrument	  需要被刷新或者新增的CInstrument,等于NULL表示是需要新增的
	///@param	pNewInstrument	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CInstrument* addOrUpdate(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CInstrument，同时删除其索引
	///@param	pInstrument	要删除的CInstrument
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CInstrument *pInstrument, CTransaction *pTransaction=NULL);
	
	///获取某个CInstrument
	///@param	pInstrument	要读取的CInstrument
	///@param	pTragetInstrument	存放结果的CInstrument
	void retrieve(CInstrument *pInstrument, CWriteableInstrument *pTargetInstrument);
	
	///获取第一个CInstrument
	///@return	得到的第一个CInstrument，如果没有，则返回NULL
	CInstrument *getFirst(void);
	
	///获取下一个CInstrument
	///@return	得到下一个CInstrument，如果没有，则返回NULL
	CInstrument *getNext(void);
	
	///结束获取CInstrument
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CInstrumentActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CInstrumentActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CInstrumentCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CInstrumentCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CInstrument
	///@param	ExchangeID	交易所编号
	///@param	InstrumentID	合约编号
	///@return	找到的CInstrument，如果找不到，返回NULL
	CInstrument *findByExchangeIDAndInstrumentID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID);

	///根据主码寻找
	///@param	ExchangeID	交易所编号
	///@param	InstrumentID	合约编号
	///@return	找到的CInstrument，如果找不到，返回NULL
	CInstrument *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID);
	
	///根据主键寻找CInstrument
	///@param	pInstrument	要找的值
	///@return	找到的CInstrument，如果找不到，返回NULL
	CInstrument *findByPK(CWriteableInstrument *pInstrument);

	///根据主键获取CInstrument
	///@param	pInstrument	要获取的值，同时用于存放返回的结果
	///@return	找到的CInstrument，如果找不到，返回NULL
	bool retrieveByPK(CWriteableInstrument *pInstrument);

	///根据主键增加新的CInstrument
	///@param	pInstrument	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CInstrument，如果插入失败，则返回NULL
	CInstrument *addByPK(CWriteableInstrument *pInstrument, CTransaction *pTransaction=NULL);

	///根据主键更新CInstrument的值
	///@param	pInstrument	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableInstrument *pInstrument, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CInstrument
	///@param	pInstrument	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableInstrument *pInstrument, CTransaction *pTransaction=NULL);


	friend class CInstrumentIteratorAllByInstrumentID;

	///开始寻找CInstrument
	///@param	InstrumentID	合约代码
	///@return	满足条件的地一个CInstrument，如果找不到，返回NULL
	CInstrument *startFindAllByInstrumentID( const CReadOnlyInstrumentIDType& InstrumentID);

	///寻找下一个符合条件的CInstrument，必须在startFindAllByInstrumentID以后，endFindAllByInstrumentID之前叫用
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	CInstrument *findNextAllByInstrumentID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByInstrumentID(void);

	friend class CInstrumentIteratorAllByExchangeID;

	///开始寻找CInstrument
	///@param	ExchangeID	交易所编号
	///@return	满足条件的地一个CInstrument，如果找不到，返回NULL
	CInstrument *startFindAllByExchangeID( const CReadOnlyExchangeIDType& ExchangeID);

	///寻找下一个符合条件的CInstrument，必须在startFindAllByExchangeID以后，endFindAllByExchangeID之前叫用
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	CInstrument *findNextAllByExchangeID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByExchangeID(void);

	friend class CInstrumentIteratorAllByProductID;

	///开始寻找CInstrument
	///@param	ProductID	产品代码
	///@return	满足条件的地一个CInstrument，如果找不到，返回NULL
	CInstrument *startFindAllByProductID( const CReadOnlyProductIDType& ProductID);

	///寻找下一个符合条件的CInstrument，必须在startFindAllByProductID以后，endFindAllByProductID之前叫用
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	CInstrument *findNextAllByProductID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByProductID(void);

	friend class CInstrumentIteratorAll;

	///开始寻找CInstrument
	///@return	满足条件的地一个CInstrument，如果找不到，返回NULL
	CInstrument *startFindAll();

	///寻找下一个符合条件的CInstrument，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	CInstrument *findNextAll(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAll(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CInstrument加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInstrument	要加入的Instrument
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInstrument *internalAdd(CWriteableInstrument *pInstrument, bool bNoTransaction);
	
	
	///刷新该CInstrument的键值
	///@param	pInstrument	被刷新的CInstrument
	///@param	pNewInstrument	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument, bool updateIndex,bool bNoTransaction);
	
	///删除一个CInstrument，同时删除其索引
	///@param	pInstrument	要删除的CInstrument
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CInstrument *pInstrument, bool bNoTransaction);
/*
	///检查某个CInstrument是否属于本对象工厂
	///@param	pInstrument	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CInstrument *pInstrument);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于ExchangeID+InstrumentID的索引
	CAVLTree *pExchangeIDInstrumentIDIndex;
	///基于InstrumentID的索引
	CAVLTree *pInstrumentIDIndex;
	
	
	///按照InstrumentID检索时，存储的查询参数
	CInstrumentIDType queryInstrumentIDInSearchAllByInstrumentID;
	
	///按照InstrumentID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchAllByInstrumentID;
	///按照ExchangeID检索时，存储的查询参数
	CExchangeIDType queryExchangeIDInSearchAllByExchangeID;
	
	///按照ExchangeID检索时，存储最后一次找到的索引节点
	CInstrument *pLastFoundInSearchAllByExchangeID;
	///按照ProductID检索时，存储的查询参数
	CProductIDType queryProductIDInSearchAllByProductID;
	
	///按照ProductID检索时，存储最后一次找到的索引节点
	CInstrument *pLastFoundInSearchAllByProductID;
	///按照检索时，存储的查询参数
	
	///按照检索时，存储最后一次找到的索引节点
	CInstrument *pLastFoundInSearchAll;
	
	///加入前触发
	///@param	pInstrument	要加入的Instrument
	virtual void beforeAdd(CWriteableInstrument *pInstrument);
	
	///加入后触发
	///@param	pInstrument	已经加入的Instrument
	virtual void afterAdd(CInstrument *pInstrument);

	///更新前触发	
	///@param	pInstrument	被刷新的CInstrument
	///@param	pNewInstrument	新的值
	virtual void beforeUpdate(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument);
	
	///更新后触发
	///@param	pInstrument	被刷新的CInstrument
	virtual void afterUpdate(CInstrument *pInstrument);
	
	///删除前触发
	///@param	pInstrument	要删除的CInstrument
	virtual void beforeRemove(CInstrument *pInstrument);
	
	///确认加入后触发
	///@param	pInstrument	已经加入的Instrument
	virtual void commitAdd(CInstrument *pInstrument);

	///确认更新后触发
	///@param	pInstrument	被刷新的CInstrument
	///@param	poldInstrument	原来的值
	virtual void commitUpdate(CInstrument *pInstrument, CWriteableInstrument *pOldInstrument);
	
	///确认删除后触发
	///@param	pInstrument	已经删除的CInstrument
	virtual void commitRemove(CWriteableInstrument *pInstrument);

	///所有相关的触发器
	vector<CInstrumentActionTrigger *> *pActionTriggers;
	vector<CInstrumentCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableInstrument compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailFactory是一个期货组合合约明细表的对象工厂。它包含了一批期货组合合约明细表，
///同时又建立了如下索引，以方便查询：
///	ExchangeIDArbiInstrumentIDSingelInstrumentIDIndex
///	ExchangeIDArbiInstrumentIDIndex
///	ExchangeIDSingleInstrumentIDIndex
///使用本对象工厂，可以完成对期货组合合约明细表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByExchangeIDAndArbiInstrumentIDAndSingelInstrumentID，唯一找到对象
///		使用startFindAllByExchangeIDAndArbiInstrumentID，findNextAllByExchangeIDAndArbiInstrumentID和endFindAllByExchangeIDAndArbiInstrumentID完成查询操作
///		使用startFindAllByExchangeIDAndSingleInstrumentID，findNextAllByExchangeIDAndSingleInstrumentID和endFindAllByExchangeIDAndSingleInstrumentID完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CCmbInstrumentDetailFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxCmbInstrumentDetail，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CCmbInstrumentDetailFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CCmbInstrumentDetailFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的CmbInstrumentDetail
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的CmbInstrumentDetail，文件名将根据配置文件中的定义CmbInstrumentDetailCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的CmbInstrumentDetail
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的CmbInstrumentDetail，文件名将根据配置文件中的定义CmbInstrumentDetailCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CCmbInstrumentDetailResource;

	///将一个CCmbInstrumentDetail加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pCmbInstrumentDetail	要加入的CmbInstrumentDetail
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CCmbInstrumentDetail *add(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail, CTransaction *pTransaction=NULL);
	
	///刷新该CCmbInstrumentDetail的值
	///@param	pCmbInstrumentDetail	被刷新的CCmbInstrumentDetail
	///@param	pNewCmbInstrumentDetail	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pCmbInstrumentDetail	  需要被刷新或者新增的CCmbInstrumentDetail,等于NULL表示是需要新增的
	///@param	pNewCmbInstrumentDetail	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CCmbInstrumentDetail* addOrUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CCmbInstrumentDetail，同时删除其索引
	///@param	pCmbInstrumentDetail	要删除的CCmbInstrumentDetail
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CCmbInstrumentDetail *pCmbInstrumentDetail, CTransaction *pTransaction=NULL);
	
	///获取某个CCmbInstrumentDetail
	///@param	pCmbInstrumentDetail	要读取的CCmbInstrumentDetail
	///@param	pTragetCmbInstrumentDetail	存放结果的CCmbInstrumentDetail
	void retrieve(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pTargetCmbInstrumentDetail);
	
	///获取第一个CCmbInstrumentDetail
	///@return	得到的第一个CCmbInstrumentDetail，如果没有，则返回NULL
	CCmbInstrumentDetail *getFirst(void);
	
	///获取下一个CCmbInstrumentDetail
	///@return	得到下一个CCmbInstrumentDetail，如果没有，则返回NULL
	CCmbInstrumentDetail *getNext(void);
	
	///结束获取CCmbInstrumentDetail
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CCmbInstrumentDetailActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CCmbInstrumentDetailActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CCmbInstrumentDetailCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CCmbInstrumentDetailCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CCmbInstrumentDetail
	///@param	ExchangeID	交易所编号
	///@param	ArbiInstrumentID	组合合约编号
	///@param	SingleInstrumentID	单腿合约编号
	///@return	找到的CCmbInstrumentDetail，如果找不到，返回NULL
	CCmbInstrumentDetail *findByExchangeIDAndArbiInstrumentIDAndSingelInstrumentID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  ArbiInstrumentID,  const CReadOnlyInstrumentIDType&  SingleInstrumentID);

	///根据主码寻找
	///@param	ExchangeID	交易所编号
	///@param	ArbiInstrumentID	组合合约编号
	///@param	SingleInstrumentID	单腿合约编号
	///@return	找到的CCmbInstrumentDetail，如果找不到，返回NULL
	CCmbInstrumentDetail *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  ArbiInstrumentID,  const CReadOnlyInstrumentIDType&  SingleInstrumentID);
	
	///根据主键寻找CCmbInstrumentDetail
	///@param	pCmbInstrumentDetail	要找的值
	///@return	找到的CCmbInstrumentDetail，如果找不到，返回NULL
	CCmbInstrumentDetail *findByPK(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail);

	///根据主键获取CCmbInstrumentDetail
	///@param	pCmbInstrumentDetail	要获取的值，同时用于存放返回的结果
	///@return	找到的CCmbInstrumentDetail，如果找不到，返回NULL
	bool retrieveByPK(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail);

	///根据主键增加新的CCmbInstrumentDetail
	///@param	pCmbInstrumentDetail	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CCmbInstrumentDetail，如果插入失败，则返回NULL
	CCmbInstrumentDetail *addByPK(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail, CTransaction *pTransaction=NULL);

	///根据主键更新CCmbInstrumentDetail的值
	///@param	pCmbInstrumentDetail	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CCmbInstrumentDetail
	///@param	pCmbInstrumentDetail	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail, CTransaction *pTransaction=NULL);


	friend class CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID;

	///开始寻找CCmbInstrumentDetail
	///@param	ExchangeID	交易所编号
	///@param	ArbiInstrumentID	组合合约编号
	///@return	满足条件的地一个CCmbInstrumentDetail，如果找不到，返回NULL
	CCmbInstrumentDetail *startFindAllByExchangeIDAndArbiInstrumentID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& ArbiInstrumentID);

	///寻找下一个符合条件的CCmbInstrumentDetail，必须在startFindAllByExchangeIDAndArbiInstrumentID以后，endFindAllByExchangeIDAndArbiInstrumentID之前叫用
	///@return	下一个满足条件CCmbInstrumentDetail，如果已经没有一个满足要求了，则返回NULL
	CCmbInstrumentDetail *findNextAllByExchangeIDAndArbiInstrumentID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByExchangeIDAndArbiInstrumentID(void);

	friend class CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID;

	///开始寻找CCmbInstrumentDetail
	///@param	ExchangeID	交易所编号
	///@param	SingleInstrumentID	单腿合约编号
	///@return	满足条件的地一个CCmbInstrumentDetail，如果找不到，返回NULL
	CCmbInstrumentDetail *startFindAllByExchangeIDAndSingleInstrumentID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& SingleInstrumentID);

	///寻找下一个符合条件的CCmbInstrumentDetail，必须在startFindAllByExchangeIDAndSingleInstrumentID以后，endFindAllByExchangeIDAndSingleInstrumentID之前叫用
	///@return	下一个满足条件CCmbInstrumentDetail，如果已经没有一个满足要求了，则返回NULL
	CCmbInstrumentDetail *findNextAllByExchangeIDAndSingleInstrumentID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByExchangeIDAndSingleInstrumentID(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CCmbInstrumentDetail加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pCmbInstrumentDetail	要加入的CmbInstrumentDetail
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CCmbInstrumentDetail *internalAdd(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail, bool bNoTransaction);
	
	
	///刷新该CCmbInstrumentDetail的键值
	///@param	pCmbInstrumentDetail	被刷新的CCmbInstrumentDetail
	///@param	pNewCmbInstrumentDetail	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail, bool updateIndex,bool bNoTransaction);
	
	///删除一个CCmbInstrumentDetail，同时删除其索引
	///@param	pCmbInstrumentDetail	要删除的CCmbInstrumentDetail
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CCmbInstrumentDetail *pCmbInstrumentDetail, bool bNoTransaction);
/*
	///检查某个CCmbInstrumentDetail是否属于本对象工厂
	///@param	pCmbInstrumentDetail	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CCmbInstrumentDetail *pCmbInstrumentDetail);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于ExchangeID+ArbiInstrumentID+SingleInstrumentID的索引
	CAVLTree *pExchangeIDArbiInstrumentIDSingelInstrumentIDIndex;
	///基于ExchangeID+ArbiInstrumentID的索引
	CAVLTree *pExchangeIDArbiInstrumentIDIndex;
	///基于ExchangeID+SingleInstrumentID的索引
	CAVLTree *pExchangeIDSingleInstrumentIDIndex;
	
	
	///按照ExchangeID，ArbiInstrumentID检索时，存储的查询参数
	CExchangeIDType queryExchangeIDInSearchAllByExchangeIDAndArbiInstrumentID;
	CInstrumentIDType queryArbiInstrumentIDInSearchAllByExchangeIDAndArbiInstrumentID;
	
	///按照ExchangeID，ArbiInstrumentID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID;
	///按照ExchangeID，SingleInstrumentID检索时，存储的查询参数
	CExchangeIDType queryExchangeIDInSearchAllByExchangeIDAndSingleInstrumentID;
	CInstrumentIDType querySingleInstrumentIDInSearchAllByExchangeIDAndSingleInstrumentID;
	
	///按照ExchangeID，SingleInstrumentID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID;
	
	///加入前触发
	///@param	pCmbInstrumentDetail	要加入的CmbInstrumentDetail
	virtual void beforeAdd(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail);
	
	///加入后触发
	///@param	pCmbInstrumentDetail	已经加入的CmbInstrumentDetail
	virtual void afterAdd(CCmbInstrumentDetail *pCmbInstrumentDetail);

	///更新前触发	
	///@param	pCmbInstrumentDetail	被刷新的CCmbInstrumentDetail
	///@param	pNewCmbInstrumentDetail	新的值
	virtual void beforeUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail);
	
	///更新后触发
	///@param	pCmbInstrumentDetail	被刷新的CCmbInstrumentDetail
	virtual void afterUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail);
	
	///删除前触发
	///@param	pCmbInstrumentDetail	要删除的CCmbInstrumentDetail
	virtual void beforeRemove(CCmbInstrumentDetail *pCmbInstrumentDetail);
	
	///确认加入后触发
	///@param	pCmbInstrumentDetail	已经加入的CmbInstrumentDetail
	virtual void commitAdd(CCmbInstrumentDetail *pCmbInstrumentDetail);

	///确认更新后触发
	///@param	pCmbInstrumentDetail	被刷新的CCmbInstrumentDetail
	///@param	poldCmbInstrumentDetail	原来的值
	virtual void commitUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pOldCmbInstrumentDetail);
	
	///确认删除后触发
	///@param	pCmbInstrumentDetail	已经删除的CCmbInstrumentDetail
	virtual void commitRemove(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail);

	///所有相关的触发器
	vector<CCmbInstrumentDetailActionTrigger *> *pActionTriggers;
	vector<CCmbInstrumentDetailCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableCmbInstrumentDetail compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDFactory是一个交易所客户编码表的对象工厂。它包含了一批交易所客户编码表，
///同时又建立了如下索引，以方便查询：
///	BrkIDExIDInvIDHdgFlgIndex
///	BrokerIDInvestorIDIndex
///使用本对象工厂，可以完成对交易所客户编码表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrokerIDExchangeIDPartClientID，唯一找到对象
///		使用findByBrkIDExIDInvIDHdgFlg，唯一找到对象
///		使用startFindByBrokerIDInvestorID，findNextByBrokerIDInvestorID和endFindByBrokerIDInvestorID完成查询操作
///		使用startFindAllByBrokerID，findNextAllByBrokerID和endFindAllByBrokerID完成查询操作
///		使用startFindAll，findNextAll和endFindAll完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CClientTradingIDFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxClientTradingID，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CClientTradingIDFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CClientTradingIDFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的ClientTradingID
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的ClientTradingID，文件名将根据配置文件中的定义ClientTradingIDCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的ClientTradingID
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的ClientTradingID，文件名将根据配置文件中的定义ClientTradingIDCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CClientTradingIDResource;

	///将一个CClientTradingID加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pClientTradingID	要加入的ClientTradingID
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CClientTradingID *add(CWriteableClientTradingID *pClientTradingID, CTransaction *pTransaction=NULL);
	
	///刷新该CClientTradingID的值
	///@param	pClientTradingID	被刷新的CClientTradingID
	///@param	pNewClientTradingID	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pClientTradingID	  需要被刷新或者新增的CClientTradingID,等于NULL表示是需要新增的
	///@param	pNewClientTradingID	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CClientTradingID* addOrUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CClientTradingID，同时删除其索引
	///@param	pClientTradingID	要删除的CClientTradingID
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CClientTradingID *pClientTradingID, CTransaction *pTransaction=NULL);
	
	///获取某个CClientTradingID
	///@param	pClientTradingID	要读取的CClientTradingID
	///@param	pTragetClientTradingID	存放结果的CClientTradingID
	void retrieve(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pTargetClientTradingID);
	
	///获取第一个CClientTradingID
	///@return	得到的第一个CClientTradingID，如果没有，则返回NULL
	CClientTradingID *getFirst(void);
	
	///获取下一个CClientTradingID
	///@return	得到下一个CClientTradingID，如果没有，则返回NULL
	CClientTradingID *getNext(void);
	
	///结束获取CClientTradingID
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CClientTradingIDActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CClientTradingIDActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CClientTradingIDCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CClientTradingIDCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///构造所有对应的帐户的指针
	///@param	pFactory	构造对应的帐户的指针时，寻找的对象工厂
	void linkAllInvestorAccount(CInvestorAccountFactory *pFactory);
	
	///寻找CClientTradingID
	///@param	BrokerID	经纪商编号
	///@param	ExchangeID	交易所编码
	///@param	ParticipantID	会员号
	///@param	ClientID	客户编码
	///@return	找到的CClientTradingID，如果找不到，返回NULL
	CClientTradingID *findByBrokerIDExchangeIDPartClientID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyParticipantIDType&  ParticipantID,  const CReadOnlyClientIDType&  ClientID);

	///根据主码寻找
	///@param	BrokerID	经纪商编号
	///@param	ExchangeID	交易所编码
	///@param	ParticipantID	会员号
	///@param	ClientID	客户编码
	///@return	找到的CClientTradingID，如果找不到，返回NULL
	CClientTradingID *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyParticipantIDType&  ParticipantID,  const CReadOnlyClientIDType&  ClientID);
	
	///根据主键寻找CClientTradingID
	///@param	pClientTradingID	要找的值
	///@return	找到的CClientTradingID，如果找不到，返回NULL
	CClientTradingID *findByPK(CWriteableClientTradingID *pClientTradingID);

	///根据主键获取CClientTradingID
	///@param	pClientTradingID	要获取的值，同时用于存放返回的结果
	///@return	找到的CClientTradingID，如果找不到，返回NULL
	bool retrieveByPK(CWriteableClientTradingID *pClientTradingID);

	///根据主键增加新的CClientTradingID
	///@param	pClientTradingID	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CClientTradingID，如果插入失败，则返回NULL
	CClientTradingID *addByPK(CWriteableClientTradingID *pClientTradingID, CTransaction *pTransaction=NULL);

	///根据主键更新CClientTradingID的值
	///@param	pClientTradingID	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableClientTradingID *pClientTradingID, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CClientTradingID
	///@param	pClientTradingID	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableClientTradingID *pClientTradingID, CTransaction *pTransaction=NULL);


	///寻找CClientTradingID
	///@param	BrokerID	经纪商编号
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编码
	///@param	ClientHedgeFlag	投机套保标志
	///@return	找到的CClientTradingID，如果找不到，返回NULL
	CClientTradingID *findByBrkIDExIDInvIDHdgFlg( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  ClientHedgeFlag);



	friend class CClientTradingIDIteratorByBrokerIDInvestorID;

	///开始寻找CClientTradingID
	///@param	BrokerID	经纪商编号
	///@param	InvestorID	客户编码
	///@return	满足条件的地一个CClientTradingID，如果找不到，返回NULL
	CClientTradingID *startFindByBrokerIDInvestorID( const CReadOnlyBrokerIDType& BrokerID,  const CReadOnlyInvestorIDType& InvestorID);

	///寻找下一个符合条件的CClientTradingID，必须在startFindByBrokerIDInvestorID以后，endFindByBrokerIDInvestorID之前叫用
	///@return	下一个满足条件CClientTradingID，如果已经没有一个满足要求了，则返回NULL
	CClientTradingID *findNextByBrokerIDInvestorID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindByBrokerIDInvestorID(void);

	friend class CClientTradingIDIteratorAllByBrokerID;

	///开始寻找CClientTradingID
	///@param	BrokerID	经纪公司代码
	///@return	满足条件的地一个CClientTradingID，如果找不到，返回NULL
	CClientTradingID *startFindAllByBrokerID( const CReadOnlyBrokerIDType& BrokerID);

	///寻找下一个符合条件的CClientTradingID，必须在startFindAllByBrokerID以后，endFindAllByBrokerID之前叫用
	///@return	下一个满足条件CClientTradingID，如果已经没有一个满足要求了，则返回NULL
	CClientTradingID *findNextAllByBrokerID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByBrokerID(void);

	friend class CClientTradingIDIteratorAll;

	///开始寻找CClientTradingID
	///@return	满足条件的地一个CClientTradingID，如果找不到，返回NULL
	CClientTradingID *startFindAll();

	///寻找下一个符合条件的CClientTradingID，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CClientTradingID，如果已经没有一个满足要求了，则返回NULL
	CClientTradingID *findNextAll(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAll(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CClientTradingID加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pClientTradingID	要加入的ClientTradingID
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CClientTradingID *internalAdd(CWriteableClientTradingID *pClientTradingID, bool bNoTransaction);
	
	
	///刷新该CClientTradingID的键值
	///@param	pClientTradingID	被刷新的CClientTradingID
	///@param	pNewClientTradingID	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID, bool updateIndex,bool bNoTransaction);
	
	///删除一个CClientTradingID，同时删除其索引
	///@param	pClientTradingID	要删除的CClientTradingID
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CClientTradingID *pClientTradingID, bool bNoTransaction);
/*
	///检查某个CClientTradingID是否属于本对象工厂
	///@param	pClientTradingID	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CClientTradingID *pClientTradingID);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于BrokerID+ExchangeID+InvestorID+ClientHedgeFlag的索引
	CAVLTree *pBrkIDExIDInvIDHdgFlgIndex;
	///基于BrokerID+InvestorID的索引
	CAVLTree *pBrokerIDInvestorIDIndex;
	
	///基于BrokerIDExchangeIDPartClientID的hash索引
	CHashIndex *pBrokerIDExchangeIDPartClientIDHashIndex;
	
	///按照BrokerID，InvestorID检索时，存储的查询参数
	CBrokerIDType queryBrokerIDInSearchByBrokerIDInvestorID;
	CInvestorIDType queryInvestorIDInSearchByBrokerIDInvestorID;
	
	///按照BrokerID，InvestorID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchByBrokerIDInvestorID;
	///按照BrokerID检索时，存储的查询参数
	CBrokerIDType queryBrokerIDInSearchAllByBrokerID;
	
	///按照BrokerID检索时，存储最后一次找到的索引节点
	CClientTradingID *pLastFoundInSearchAllByBrokerID;
	///按照检索时，存储的查询参数
	
	///按照检索时，存储最后一次找到的索引节点
	CClientTradingID *pLastFoundInSearchAll;
	
	///加入前触发
	///@param	pClientTradingID	要加入的ClientTradingID
	virtual void beforeAdd(CWriteableClientTradingID *pClientTradingID);
	
	///加入后触发
	///@param	pClientTradingID	已经加入的ClientTradingID
	virtual void afterAdd(CClientTradingID *pClientTradingID);

	///更新前触发	
	///@param	pClientTradingID	被刷新的CClientTradingID
	///@param	pNewClientTradingID	新的值
	virtual void beforeUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID);
	
	///更新后触发
	///@param	pClientTradingID	被刷新的CClientTradingID
	virtual void afterUpdate(CClientTradingID *pClientTradingID);
	
	///删除前触发
	///@param	pClientTradingID	要删除的CClientTradingID
	virtual void beforeRemove(CClientTradingID *pClientTradingID);
	
	///确认加入后触发
	///@param	pClientTradingID	已经加入的ClientTradingID
	virtual void commitAdd(CClientTradingID *pClientTradingID);

	///确认更新后触发
	///@param	pClientTradingID	被刷新的CClientTradingID
	///@param	poldClientTradingID	原来的值
	virtual void commitUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pOldClientTradingID);
	
	///确认删除后触发
	///@param	pClientTradingID	已经删除的CClientTradingID
	virtual void commitRemove(CWriteableClientTradingID *pClientTradingID);

	///所有相关的触发器
	vector<CClientTradingIDActionTrigger *> *pActionTriggers;
	vector<CClientTradingIDCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableClientTradingID compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFactory是一个投资者信息表的对象工厂。它包含了一批投资者信息表，
///同时又建立了如下索引，以方便查询：
///	BrokerIDInvestorIDIndex
///使用本对象工厂，可以完成对投资者信息表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrokerIDInvestorID，唯一找到对象
///		使用startFindByInvestorID，findNextByInvestorID和endFindByInvestorID完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxInvestor，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的Investor
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的Investor，文件名将根据配置文件中的定义InvestorCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的Investor
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的Investor，文件名将根据配置文件中的定义InvestorCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CInvestorResource;

	///将一个CInvestor加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestor	要加入的Investor
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestor *add(CWriteableInvestor *pInvestor, CTransaction *pTransaction=NULL);
	
	///刷新该CInvestor的值
	///@param	pInvestor	被刷新的CInvestor
	///@param	pNewInvestor	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pInvestor	  需要被刷新或者新增的CInvestor,等于NULL表示是需要新增的
	///@param	pNewInvestor	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CInvestor* addOrUpdate(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CInvestor，同时删除其索引
	///@param	pInvestor	要删除的CInvestor
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CInvestor *pInvestor, CTransaction *pTransaction=NULL);
	
	///获取某个CInvestor
	///@param	pInvestor	要读取的CInvestor
	///@param	pTragetInvestor	存放结果的CInvestor
	void retrieve(CInvestor *pInvestor, CWriteableInvestor *pTargetInvestor);
	
	///获取第一个CInvestor
	///@return	得到的第一个CInvestor，如果没有，则返回NULL
	CInvestor *getFirst(void);
	
	///获取下一个CInvestor
	///@return	得到下一个CInvestor，如果没有，则返回NULL
	CInvestor *getNext(void);
	
	///结束获取CInvestor
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CInvestorActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CInvestorActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CInvestorCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CInvestorCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CInvestor
	///@param	BrokerID	经纪公司代码
	///@param	InvestorID	投资者编号
	///@return	找到的CInvestor，如果找不到，返回NULL
	CInvestor *findByBrokerIDInvestorID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInvestorIDType&  InvestorID);

	///根据主码寻找
	///@param	BrokerID	经纪公司代码
	///@param	InvestorID	投资者编号
	///@return	找到的CInvestor，如果找不到，返回NULL
	CInvestor *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInvestorIDType&  InvestorID);
	
	///根据主键寻找CInvestor
	///@param	pInvestor	要找的值
	///@return	找到的CInvestor，如果找不到，返回NULL
	CInvestor *findByPK(CWriteableInvestor *pInvestor);

	///根据主键获取CInvestor
	///@param	pInvestor	要获取的值，同时用于存放返回的结果
	///@return	找到的CInvestor，如果找不到，返回NULL
	bool retrieveByPK(CWriteableInvestor *pInvestor);

	///根据主键增加新的CInvestor
	///@param	pInvestor	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CInvestor，如果插入失败，则返回NULL
	CInvestor *addByPK(CWriteableInvestor *pInvestor, CTransaction *pTransaction=NULL);

	///根据主键更新CInvestor的值
	///@param	pInvestor	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableInvestor *pInvestor, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CInvestor
	///@param	pInvestor	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableInvestor *pInvestor, CTransaction *pTransaction=NULL);


	friend class CInvestorIteratorByInvestorID;

	///开始寻找CInvestor
	///@param	InvestorID	投资者编号
	///@return	满足条件的地一个CInvestor，如果找不到，返回NULL
	CInvestor *startFindByInvestorID( const CReadOnlyInvestorIDType& InvestorID);

	///寻找下一个符合条件的CInvestor，必须在startFindByInvestorID以后，endFindByInvestorID之前叫用
	///@return	下一个满足条件CInvestor，如果已经没有一个满足要求了，则返回NULL
	CInvestor *findNextByInvestorID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindByInvestorID(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CInvestor加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestor	要加入的Investor
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestor *internalAdd(CWriteableInvestor *pInvestor, bool bNoTransaction);
	
	
	///刷新该CInvestor的键值
	///@param	pInvestor	被刷新的CInvestor
	///@param	pNewInvestor	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor, bool updateIndex,bool bNoTransaction);
	
	///删除一个CInvestor，同时删除其索引
	///@param	pInvestor	要删除的CInvestor
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CInvestor *pInvestor, bool bNoTransaction);
/*
	///检查某个CInvestor是否属于本对象工厂
	///@param	pInvestor	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CInvestor *pInvestor);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于BrokerID+InvestorID的索引
	CAVLTree *pBrokerIDInvestorIDIndex;
	
	
	///按照InvestorID检索时，存储的查询参数
	CInvestorIDType queryInvestorIDInSearchByInvestorID;
	
	///按照InvestorID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchByInvestorID;
	
	///加入前触发
	///@param	pInvestor	要加入的Investor
	virtual void beforeAdd(CWriteableInvestor *pInvestor);
	
	///加入后触发
	///@param	pInvestor	已经加入的Investor
	virtual void afterAdd(CInvestor *pInvestor);

	///更新前触发	
	///@param	pInvestor	被刷新的CInvestor
	///@param	pNewInvestor	新的值
	virtual void beforeUpdate(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor);
	
	///更新后触发
	///@param	pInvestor	被刷新的CInvestor
	virtual void afterUpdate(CInvestor *pInvestor);
	
	///删除前触发
	///@param	pInvestor	要删除的CInvestor
	virtual void beforeRemove(CInvestor *pInvestor);
	
	///确认加入后触发
	///@param	pInvestor	已经加入的Investor
	virtual void commitAdd(CInvestor *pInvestor);

	///确认更新后触发
	///@param	pInvestor	被刷新的CInvestor
	///@param	poldInvestor	原来的值
	virtual void commitUpdate(CInvestor *pInvestor, CWriteableInvestor *pOldInvestor);
	
	///确认删除后触发
	///@param	pInvestor	已经删除的CInvestor
	virtual void commitRemove(CWriteableInvestor *pInvestor);

	///所有相关的触发器
	vector<CInvestorActionTrigger *> *pActionTriggers;
	vector<CInvestorCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableInvestor compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginFactory是一个客户期货保证金率表的对象工厂。它包含了一批客户期货保证金率表，
///同时又建立了如下索引，以方便查询：
///	BrokerIDClientIDIndex
///	BrkIDExIDIstIDVstIDHdgIndex
///	BrkIDExIDIstIDVstIDIndex
///使用本对象工厂，可以完成对客户期货保证金率表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrokerIDClientID，唯一找到对象
///		使用findByBrkIDExIDIstIDVstIDHdg，唯一找到对象
///		使用startFindByBrkIDExIDIstIDVstID，findNextByBrkIDExIDIstIDVstID和endFindByBrkIDExIDIstIDVstID完成查询操作
///		使用startFindByInstrumentID，findNextByInstrumentID和endFindByInstrumentID完成查询操作
///		使用startFindByBrokerID，findNextByBrokerID和endFindByBrokerID完成查询操作
///		使用startFindAll，findNextAll和endFindAll完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorMarginFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxInvestorMargin，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorMarginFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorMarginFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的InvestorMargin
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的InvestorMargin，文件名将根据配置文件中的定义InvestorMarginCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的InvestorMargin
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的InvestorMargin，文件名将根据配置文件中的定义InvestorMarginCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CInvestorMarginResource;

	///将一个CInvestorMargin加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestorMargin	要加入的InvestorMargin
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestorMargin *add(CWriteableInvestorMargin *pInvestorMargin, CTransaction *pTransaction=NULL);
	
	///刷新该CInvestorMargin的值
	///@param	pInvestorMargin	被刷新的CInvestorMargin
	///@param	pNewInvestorMargin	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pInvestorMargin	  需要被刷新或者新增的CInvestorMargin,等于NULL表示是需要新增的
	///@param	pNewInvestorMargin	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CInvestorMargin* addOrUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CInvestorMargin，同时删除其索引
	///@param	pInvestorMargin	要删除的CInvestorMargin
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CInvestorMargin *pInvestorMargin, CTransaction *pTransaction=NULL);
	
	///获取某个CInvestorMargin
	///@param	pInvestorMargin	要读取的CInvestorMargin
	///@param	pTragetInvestorMargin	存放结果的CInvestorMargin
	void retrieve(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pTargetInvestorMargin);
	
	///获取第一个CInvestorMargin
	///@return	得到的第一个CInvestorMargin，如果没有，则返回NULL
	CInvestorMargin *getFirst(void);
	
	///获取下一个CInvestorMargin
	///@return	得到下一个CInvestorMargin，如果没有，则返回NULL
	CInvestorMargin *getNext(void);
	
	///结束获取CInvestorMargin
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CInvestorMarginActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CInvestorMarginActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CInvestorMarginCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CInvestorMarginCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CInvestorMargin
	///@param	BrokerID	经纪公司代码
	///@param	InvestorID	客户编码
	///@return	找到的CInvestorMargin，如果找不到，返回NULL
	CInvestorMargin *findByBrokerIDClientID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInvestorIDType&  InvestorID);



	///寻找CInvestorMargin
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约代码
	///@param	InvestorID	投资者编码
	///@param	HedgeFlag	投机套保标志
	///@return	找到的CInvestorMargin，如果找不到，返回NULL
	CInvestorMargin *findByBrkIDExIDIstIDVstIDHdg( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag);

	///根据主码寻找
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约代码
	///@param	InvestorID	投资者编码
	///@param	HedgeFlag	投机套保标志
	///@return	找到的CInvestorMargin，如果找不到，返回NULL
	CInvestorMargin *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag);
	
	///根据主键寻找CInvestorMargin
	///@param	pInvestorMargin	要找的值
	///@return	找到的CInvestorMargin，如果找不到，返回NULL
	CInvestorMargin *findByPK(CWriteableInvestorMargin *pInvestorMargin);

	///根据主键获取CInvestorMargin
	///@param	pInvestorMargin	要获取的值，同时用于存放返回的结果
	///@return	找到的CInvestorMargin，如果找不到，返回NULL
	bool retrieveByPK(CWriteableInvestorMargin *pInvestorMargin);

	///根据主键增加新的CInvestorMargin
	///@param	pInvestorMargin	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CInvestorMargin，如果插入失败，则返回NULL
	CInvestorMargin *addByPK(CWriteableInvestorMargin *pInvestorMargin, CTransaction *pTransaction=NULL);

	///根据主键更新CInvestorMargin的值
	///@param	pInvestorMargin	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableInvestorMargin *pInvestorMargin, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CInvestorMargin
	///@param	pInvestorMargin	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableInvestorMargin *pInvestorMargin, CTransaction *pTransaction=NULL);


	friend class CInvestorMarginIteratorByBrkIDExIDIstIDVstID;

	///开始寻找CInvestorMargin
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约代码
	///@param	InvestorID	投资者编码
	///@return	满足条件的地一个CInvestorMargin，如果找不到，返回NULL
	CInvestorMargin *startFindByBrkIDExIDIstIDVstID( const CReadOnlyBrokerIDType& BrokerID,  const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& InstrumentID,  const CReadOnlyInvestorIDType& InvestorID);

	///寻找下一个符合条件的CInvestorMargin，必须在startFindByBrkIDExIDIstIDVstID以后，endFindByBrkIDExIDIstIDVstID之前叫用
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	CInvestorMargin *findNextByBrkIDExIDIstIDVstID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindByBrkIDExIDIstIDVstID(void);

	friend class CInvestorMarginIteratorByInstrumentID;

	///开始寻找CInvestorMargin
	///@param	InstrumentID	合约代码
	///@return	满足条件的地一个CInvestorMargin，如果找不到，返回NULL
	CInvestorMargin *startFindByInstrumentID( const CReadOnlyInstrumentIDType& InstrumentID);

	///寻找下一个符合条件的CInvestorMargin，必须在startFindByInstrumentID以后，endFindByInstrumentID之前叫用
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	CInvestorMargin *findNextByInstrumentID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindByInstrumentID(void);

	friend class CInvestorMarginIteratorByBrokerID;

	///开始寻找CInvestorMargin
	///@param	BrokerID	合约代码
	///@return	满足条件的地一个CInvestorMargin，如果找不到，返回NULL
	CInvestorMargin *startFindByBrokerID( const CReadOnlyBrokerIDType& BrokerID);

	///寻找下一个符合条件的CInvestorMargin，必须在startFindByBrokerID以后，endFindByBrokerID之前叫用
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	CInvestorMargin *findNextByBrokerID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindByBrokerID(void);

	friend class CInvestorMarginIteratorAll;

	///开始寻找CInvestorMargin
	///@return	满足条件的地一个CInvestorMargin，如果找不到，返回NULL
	CInvestorMargin *startFindAll();

	///寻找下一个符合条件的CInvestorMargin，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	CInvestorMargin *findNextAll(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAll(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CInvestorMargin加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestorMargin	要加入的InvestorMargin
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestorMargin *internalAdd(CWriteableInvestorMargin *pInvestorMargin, bool bNoTransaction);
	
	
	///刷新该CInvestorMargin的键值
	///@param	pInvestorMargin	被刷新的CInvestorMargin
	///@param	pNewInvestorMargin	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin, bool updateIndex,bool bNoTransaction);
	
	///删除一个CInvestorMargin，同时删除其索引
	///@param	pInvestorMargin	要删除的CInvestorMargin
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CInvestorMargin *pInvestorMargin, bool bNoTransaction);
/*
	///检查某个CInvestorMargin是否属于本对象工厂
	///@param	pInvestorMargin	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CInvestorMargin *pInvestorMargin);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于BrokerID+InvestorID的索引
	CAVLTree *pBrokerIDClientIDIndex;
	///基于BrokerID+ExchangeID+InstrumentID+InvestorID+HedgeFlag的索引
	CAVLTree *pBrkIDExIDIstIDVstIDHdgIndex;
	///基于BrokerID+ExchangeID+InstrumentID+InvestorID的索引
	CAVLTree *pBrkIDExIDIstIDVstIDIndex;
	
	///基于InstrumentAndClientID的hash索引
	CHashIndex *pInstrumentAndClientID;
	
	///按照BrokerID，ExchangeID，InstrumentID，InvestorID检索时，存储的查询参数
	CBrokerIDType queryBrokerIDInSearchByBrkIDExIDIstIDVstID;
	CExchangeIDType queryExchangeIDInSearchByBrkIDExIDIstIDVstID;
	CInstrumentIDType queryInstrumentIDInSearchByBrkIDExIDIstIDVstID;
	CInvestorIDType queryInvestorIDInSearchByBrkIDExIDIstIDVstID;
	
	///按照BrokerID，ExchangeID，InstrumentID，InvestorID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchByBrkIDExIDIstIDVstID;
	///按照InstrumentID检索时，存储的查询参数
	CInstrumentIDType queryInstrumentIDInSearchByInstrumentID;
	
	///按照InstrumentID检索时，存储最后一次找到的索引节点
	CInvestorMargin *pLastFoundInSearchByInstrumentID;
	///按照BrokerID检索时，存储的查询参数
	CBrokerIDType queryBrokerIDInSearchByBrokerID;
	
	///按照BrokerID检索时，存储最后一次找到的索引节点
	CInvestorMargin *pLastFoundInSearchByBrokerID;
	///按照检索时，存储的查询参数
	
	///按照检索时，存储最后一次找到的索引节点
	CInvestorMargin *pLastFoundInSearchAll;
	
	///加入前触发
	///@param	pInvestorMargin	要加入的InvestorMargin
	virtual void beforeAdd(CWriteableInvestorMargin *pInvestorMargin);
	
	///加入后触发
	///@param	pInvestorMargin	已经加入的InvestorMargin
	virtual void afterAdd(CInvestorMargin *pInvestorMargin);

	///更新前触发	
	///@param	pInvestorMargin	被刷新的CInvestorMargin
	///@param	pNewInvestorMargin	新的值
	virtual void beforeUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin);
	
	///更新后触发
	///@param	pInvestorMargin	被刷新的CInvestorMargin
	virtual void afterUpdate(CInvestorMargin *pInvestorMargin);
	
	///删除前触发
	///@param	pInvestorMargin	要删除的CInvestorMargin
	virtual void beforeRemove(CInvestorMargin *pInvestorMargin);
	
	///确认加入后触发
	///@param	pInvestorMargin	已经加入的InvestorMargin
	virtual void commitAdd(CInvestorMargin *pInvestorMargin);

	///确认更新后触发
	///@param	pInvestorMargin	被刷新的CInvestorMargin
	///@param	poldInvestorMargin	原来的值
	virtual void commitUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pOldInvestorMargin);
	
	///确认删除后触发
	///@param	pInvestorMargin	已经删除的CInvestorMargin
	virtual void commitRemove(CWriteableInvestorMargin *pInvestorMargin);

	///所有相关的触发器
	vector<CInvestorMarginActionTrigger *> *pActionTriggers;
	vector<CInvestorMarginCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableInvestorMargin compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeFactory是一个客户手续费率表的对象工厂。它包含了一批客户手续费率表，
///同时又建立了如下索引，以方便查询：
///	InstrumentIDIndex
///	BrkIDExIDIstIDVstIDHdgIndex
///使用本对象工厂，可以完成对客户手续费率表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrkIDExIDIstIDVstIDHdg，唯一找到对象
///		使用startFindByInstrumentID，findNextByInstrumentID和endFindByInstrumentID完成查询操作
///		使用startFindByBrokerID，findNextByBrokerID和endFindByBrokerID完成查询操作
///		使用startFindAll，findNextAll和endFindAll完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorFeeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxInvestorFee，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorFeeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorFeeFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的InvestorFee
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的InvestorFee，文件名将根据配置文件中的定义InvestorFeeCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的InvestorFee
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的InvestorFee，文件名将根据配置文件中的定义InvestorFeeCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CInvestorFeeResource;

	///将一个CInvestorFee加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestorFee	要加入的InvestorFee
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestorFee *add(CWriteableInvestorFee *pInvestorFee, CTransaction *pTransaction=NULL);
	
	///刷新该CInvestorFee的值
	///@param	pInvestorFee	被刷新的CInvestorFee
	///@param	pNewInvestorFee	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pInvestorFee	  需要被刷新或者新增的CInvestorFee,等于NULL表示是需要新增的
	///@param	pNewInvestorFee	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CInvestorFee* addOrUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CInvestorFee，同时删除其索引
	///@param	pInvestorFee	要删除的CInvestorFee
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CInvestorFee *pInvestorFee, CTransaction *pTransaction=NULL);
	
	///获取某个CInvestorFee
	///@param	pInvestorFee	要读取的CInvestorFee
	///@param	pTragetInvestorFee	存放结果的CInvestorFee
	void retrieve(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pTargetInvestorFee);
	
	///获取第一个CInvestorFee
	///@return	得到的第一个CInvestorFee，如果没有，则返回NULL
	CInvestorFee *getFirst(void);
	
	///获取下一个CInvestorFee
	///@return	得到下一个CInvestorFee，如果没有，则返回NULL
	CInvestorFee *getNext(void);
	
	///结束获取CInvestorFee
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CInvestorFeeActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CInvestorFeeActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CInvestorFeeCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CInvestorFeeCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CInvestorFee
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约代码
	///@param	InvestorID	客户号
	///@param	HedgeFlag	投机套保标志
	///@return	找到的CInvestorFee，如果找不到，返回NULL
	CInvestorFee *findByBrkIDExIDIstIDVstIDHdg( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag);

	///根据主码寻找
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约代码
	///@param	InvestorID	客户号
	///@param	HedgeFlag	投机套保标志
	///@return	找到的CInvestorFee，如果找不到，返回NULL
	CInvestorFee *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag);
	
	///根据主键寻找CInvestorFee
	///@param	pInvestorFee	要找的值
	///@return	找到的CInvestorFee，如果找不到，返回NULL
	CInvestorFee *findByPK(CWriteableInvestorFee *pInvestorFee);

	///根据主键获取CInvestorFee
	///@param	pInvestorFee	要获取的值，同时用于存放返回的结果
	///@return	找到的CInvestorFee，如果找不到，返回NULL
	bool retrieveByPK(CWriteableInvestorFee *pInvestorFee);

	///根据主键增加新的CInvestorFee
	///@param	pInvestorFee	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CInvestorFee，如果插入失败，则返回NULL
	CInvestorFee *addByPK(CWriteableInvestorFee *pInvestorFee, CTransaction *pTransaction=NULL);

	///根据主键更新CInvestorFee的值
	///@param	pInvestorFee	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableInvestorFee *pInvestorFee, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CInvestorFee
	///@param	pInvestorFee	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableInvestorFee *pInvestorFee, CTransaction *pTransaction=NULL);


	friend class CInvestorFeeIteratorByInstrumentID;

	///开始寻找CInvestorFee
	///@param	InstrumentID	合约编号
	///@return	满足条件的地一个CInvestorFee，如果找不到，返回NULL
	CInvestorFee *startFindByInstrumentID( const CReadOnlyInstrumentIDType& InstrumentID);

	///寻找下一个符合条件的CInvestorFee，必须在startFindByInstrumentID以后，endFindByInstrumentID之前叫用
	///@return	下一个满足条件CInvestorFee，如果已经没有一个满足要求了，则返回NULL
	CInvestorFee *findNextByInstrumentID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindByInstrumentID(void);

	friend class CInvestorFeeIteratorByBrokerID;

	///开始寻找CInvestorFee
	///@param	BrokerID	合约编号
	///@return	满足条件的地一个CInvestorFee，如果找不到，返回NULL
	CInvestorFee *startFindByBrokerID( const CReadOnlyBrokerIDType& BrokerID);

	///寻找下一个符合条件的CInvestorFee，必须在startFindByBrokerID以后，endFindByBrokerID之前叫用
	///@return	下一个满足条件CInvestorFee，如果已经没有一个满足要求了，则返回NULL
	CInvestorFee *findNextByBrokerID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindByBrokerID(void);

	friend class CInvestorFeeIteratorAll;

	///开始寻找CInvestorFee
	///@return	满足条件的地一个CInvestorFee，如果找不到，返回NULL
	CInvestorFee *startFindAll();

	///寻找下一个符合条件的CInvestorFee，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CInvestorFee，如果已经没有一个满足要求了，则返回NULL
	CInvestorFee *findNextAll(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAll(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CInvestorFee加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestorFee	要加入的InvestorFee
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestorFee *internalAdd(CWriteableInvestorFee *pInvestorFee, bool bNoTransaction);
	
	
	///刷新该CInvestorFee的键值
	///@param	pInvestorFee	被刷新的CInvestorFee
	///@param	pNewInvestorFee	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee, bool updateIndex,bool bNoTransaction);
	
	///删除一个CInvestorFee，同时删除其索引
	///@param	pInvestorFee	要删除的CInvestorFee
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CInvestorFee *pInvestorFee, bool bNoTransaction);
/*
	///检查某个CInvestorFee是否属于本对象工厂
	///@param	pInvestorFee	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CInvestorFee *pInvestorFee);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于InstrumentID的索引
	CAVLTree *pInstrumentIDIndex;
	///基于BrokerID+ExchangeID+InstrumentID+InvestorID+HedgeFlag的索引
	CAVLTree *pBrkIDExIDIstIDVstIDHdgIndex;
	
	
	///按照InstrumentID检索时，存储的查询参数
	CInstrumentIDType queryInstrumentIDInSearchByInstrumentID;
	
	///按照InstrumentID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchByInstrumentID;
	///按照BrokerID检索时，存储的查询参数
	CBrokerIDType queryBrokerIDInSearchByBrokerID;
	
	///按照BrokerID检索时，存储最后一次找到的索引节点
	CInvestorFee *pLastFoundInSearchByBrokerID;
	///按照检索时，存储的查询参数
	
	///按照检索时，存储最后一次找到的索引节点
	CInvestorFee *pLastFoundInSearchAll;
	
	///加入前触发
	///@param	pInvestorFee	要加入的InvestorFee
	virtual void beforeAdd(CWriteableInvestorFee *pInvestorFee);
	
	///加入后触发
	///@param	pInvestorFee	已经加入的InvestorFee
	virtual void afterAdd(CInvestorFee *pInvestorFee);

	///更新前触发	
	///@param	pInvestorFee	被刷新的CInvestorFee
	///@param	pNewInvestorFee	新的值
	virtual void beforeUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee);
	
	///更新后触发
	///@param	pInvestorFee	被刷新的CInvestorFee
	virtual void afterUpdate(CInvestorFee *pInvestorFee);
	
	///删除前触发
	///@param	pInvestorFee	要删除的CInvestorFee
	virtual void beforeRemove(CInvestorFee *pInvestorFee);
	
	///确认加入后触发
	///@param	pInvestorFee	已经加入的InvestorFee
	virtual void commitAdd(CInvestorFee *pInvestorFee);

	///确认更新后触发
	///@param	pInvestorFee	被刷新的CInvestorFee
	///@param	poldInvestorFee	原来的值
	virtual void commitUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pOldInvestorFee);
	
	///确认删除后触发
	///@param	pInvestorFee	已经删除的CInvestorFee
	virtual void commitRemove(CWriteableInvestorFee *pInvestorFee);

	///所有相关的触发器
	vector<CInvestorFeeActionTrigger *> *pActionTriggers;
	vector<CInvestorFeeCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableInvestorFee compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CUserFactory是一个用户表的对象工厂。它包含了一批用户表，
///同时又建立了如下索引，以方便查询：
///	BrokerIDUserIDIndex
///	UserIDIndex
///使用本对象工厂，可以完成对用户表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrokerIDUserID，唯一找到对象
///		使用startFindStartByUserID，findNextStartByUserID和endFindStartByUserID完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CUserFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxUser，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CUserFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CUserFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的User
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的User，文件名将根据配置文件中的定义UserCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的User
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的User，文件名将根据配置文件中的定义UserCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CUserResource;

	///将一个CUser加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pUser	要加入的User
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CUser *add(CWriteableUser *pUser, CTransaction *pTransaction=NULL);
	
	///刷新该CUser的值
	///@param	pUser	被刷新的CUser
	///@param	pNewUser	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CUser *pUser, CWriteableUser *pNewUser, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pUser	  需要被刷新或者新增的CUser,等于NULL表示是需要新增的
	///@param	pNewUser	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CUser* addOrUpdate(CUser *pUser, CWriteableUser *pNewUser, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CUser，同时删除其索引
	///@param	pUser	要删除的CUser
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CUser *pUser, CTransaction *pTransaction=NULL);
	
	///获取某个CUser
	///@param	pUser	要读取的CUser
	///@param	pTragetUser	存放结果的CUser
	void retrieve(CUser *pUser, CWriteableUser *pTargetUser);
	
	///获取第一个CUser
	///@return	得到的第一个CUser，如果没有，则返回NULL
	CUser *getFirst(void);
	
	///获取下一个CUser
	///@return	得到下一个CUser，如果没有，则返回NULL
	CUser *getNext(void);
	
	///结束获取CUser
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CUserActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CUserActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CUserCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CUserCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CUser
	///@param	BrokerID	经纪公司代码
	///@param	UserID	交易用户代码
	///@return	找到的CUser，如果找不到，返回NULL
	CUser *findByBrokerIDUserID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID);

	///根据主码寻找
	///@param	BrokerID	经纪公司代码
	///@param	UserID	交易用户代码
	///@return	找到的CUser，如果找不到，返回NULL
	CUser *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID);
	
	///根据主键寻找CUser
	///@param	pUser	要找的值
	///@return	找到的CUser，如果找不到，返回NULL
	CUser *findByPK(CWriteableUser *pUser);

	///根据主键获取CUser
	///@param	pUser	要获取的值，同时用于存放返回的结果
	///@return	找到的CUser，如果找不到，返回NULL
	bool retrieveByPK(CWriteableUser *pUser);

	///根据主键增加新的CUser
	///@param	pUser	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CUser，如果插入失败，则返回NULL
	CUser *addByPK(CWriteableUser *pUser, CTransaction *pTransaction=NULL);

	///根据主键更新CUser的值
	///@param	pUser	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableUser *pUser, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CUser
	///@param	pUser	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableUser *pUser, CTransaction *pTransaction=NULL);


	friend class CUserIteratorStartByUserID;

	///开始寻找CUser
	///@param	UserID	用户编号
	///@return	满足条件的地一个CUser，如果找不到，返回NULL
	CUser *startFindStartByUserID( const CReadOnlyUserIDType& UserID);

	///寻找下一个符合条件的CUser，必须在startFindStartByUserID以后，endFindStartByUserID之前叫用
	///@return	下一个满足条件CUser，如果已经没有一个满足要求了，则返回NULL
	CUser *findNextStartByUserID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindStartByUserID(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CUser加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pUser	要加入的User
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CUser *internalAdd(CWriteableUser *pUser, bool bNoTransaction);
	
	
	///刷新该CUser的键值
	///@param	pUser	被刷新的CUser
	///@param	pNewUser	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CUser *pUser, CWriteableUser *pNewUser, bool updateIndex,bool bNoTransaction);
	
	///删除一个CUser，同时删除其索引
	///@param	pUser	要删除的CUser
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CUser *pUser, bool bNoTransaction);
/*
	///检查某个CUser是否属于本对象工厂
	///@param	pUser	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CUser *pUser);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于BrokerID+UserID的索引
	CAVLTree *pBrokerIDUserIDIndex;
	///基于UserID的索引
	CAVLTree *pUserIDIndex;
	
	
	///按照UserID检索时，存储的查询参数
	CUserIDType queryUserIDInSearchStartByUserID;
	
	///按照UserID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchStartByUserID;
	
	///加入前触发
	///@param	pUser	要加入的User
	virtual void beforeAdd(CWriteableUser *pUser);
	
	///加入后触发
	///@param	pUser	已经加入的User
	virtual void afterAdd(CUser *pUser);

	///更新前触发	
	///@param	pUser	被刷新的CUser
	///@param	pNewUser	新的值
	virtual void beforeUpdate(CUser *pUser, CWriteableUser *pNewUser);
	
	///更新后触发
	///@param	pUser	被刷新的CUser
	virtual void afterUpdate(CUser *pUser);
	
	///删除前触发
	///@param	pUser	要删除的CUser
	virtual void beforeRemove(CUser *pUser);
	
	///确认加入后触发
	///@param	pUser	已经加入的User
	virtual void commitAdd(CUser *pUser);

	///确认更新后触发
	///@param	pUser	被刷新的CUser
	///@param	poldUser	原来的值
	virtual void commitUpdate(CUser *pUser, CWriteableUser *pOldUser);
	
	///确认删除后触发
	///@param	pUser	已经删除的CUser
	virtual void commitRemove(CWriteableUser *pUser);

	///所有相关的触发器
	vector<CUserActionTrigger *> *pActionTriggers;
	vector<CUserCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableUser compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorFactory是一个用户投资者关系表的对象工厂。它包含了一批用户投资者关系表，
///同时又建立了如下索引，以方便查询：
///	BrokerIDUserIDInvestorIDIndex
///	BrokerIDInvestorIDIndex
///使用本对象工厂，可以完成对用户投资者关系表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrokerIDUserIDInvestorID，唯一找到对象
///		使用startFindByBrokerIDInvestorID，findNextByBrokerIDInvestorID和endFindByBrokerIDInvestorID完成查询操作
///		使用startFindAllByUserID，findNextAllByUserID和endFindAllByUserID完成查询操作
///		使用startFindAllByBrokerIDUserID，findNextAllByBrokerIDUserID和endFindAllByBrokerIDUserID完成查询操作
///		使用startFindAllByBrokerID，findNextAllByBrokerID和endFindAllByBrokerID完成查询操作
///		使用startFindAll，findNextAll和endFindAll完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CUserInvestorFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxUserInvestor，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CUserInvestorFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CUserInvestorFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的UserInvestor
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的UserInvestor，文件名将根据配置文件中的定义UserInvestorCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的UserInvestor
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的UserInvestor，文件名将根据配置文件中的定义UserInvestorCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CUserInvestorResource;

	///将一个CUserInvestor加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pUserInvestor	要加入的UserInvestor
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CUserInvestor *add(CWriteableUserInvestor *pUserInvestor, CTransaction *pTransaction=NULL);
	
	///刷新该CUserInvestor的值
	///@param	pUserInvestor	被刷新的CUserInvestor
	///@param	pNewUserInvestor	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pUserInvestor	  需要被刷新或者新增的CUserInvestor,等于NULL表示是需要新增的
	///@param	pNewUserInvestor	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CUserInvestor* addOrUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CUserInvestor，同时删除其索引
	///@param	pUserInvestor	要删除的CUserInvestor
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CUserInvestor *pUserInvestor, CTransaction *pTransaction=NULL);
	
	///获取某个CUserInvestor
	///@param	pUserInvestor	要读取的CUserInvestor
	///@param	pTragetUserInvestor	存放结果的CUserInvestor
	void retrieve(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pTargetUserInvestor);
	
	///获取第一个CUserInvestor
	///@return	得到的第一个CUserInvestor，如果没有，则返回NULL
	CUserInvestor *getFirst(void);
	
	///获取下一个CUserInvestor
	///@return	得到下一个CUserInvestor，如果没有，则返回NULL
	CUserInvestor *getNext(void);
	
	///结束获取CUserInvestor
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CUserInvestorActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CUserInvestorActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CUserInvestorCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CUserInvestorCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CUserInvestor
	///@param	BrokerID	经纪公司代码
	///@param	UserID	交易用户代码
	///@param	InvestorID	投资者编号
	///@return	找到的CUserInvestor，如果找不到，返回NULL
	CUserInvestor *findByBrokerIDUserIDInvestorID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyInvestorIDType&  InvestorID);

	///根据主码寻找
	///@param	BrokerID	经纪公司代码
	///@param	UserID	交易用户代码
	///@param	InvestorID	投资者编号
	///@return	找到的CUserInvestor，如果找不到，返回NULL
	CUserInvestor *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyInvestorIDType&  InvestorID);
	
	///根据主键寻找CUserInvestor
	///@param	pUserInvestor	要找的值
	///@return	找到的CUserInvestor，如果找不到，返回NULL
	CUserInvestor *findByPK(CWriteableUserInvestor *pUserInvestor);

	///根据主键获取CUserInvestor
	///@param	pUserInvestor	要获取的值，同时用于存放返回的结果
	///@return	找到的CUserInvestor，如果找不到，返回NULL
	bool retrieveByPK(CWriteableUserInvestor *pUserInvestor);

	///根据主键增加新的CUserInvestor
	///@param	pUserInvestor	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CUserInvestor，如果插入失败，则返回NULL
	CUserInvestor *addByPK(CWriteableUserInvestor *pUserInvestor, CTransaction *pTransaction=NULL);

	///根据主键更新CUserInvestor的值
	///@param	pUserInvestor	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableUserInvestor *pUserInvestor, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CUserInvestor
	///@param	pUserInvestor	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableUserInvestor *pUserInvestor, CTransaction *pTransaction=NULL);


	friend class CUserInvestorIteratorByBrokerIDInvestorID;

	///开始寻找CUserInvestor
	///@param	BrokerID	经纪公司代码
	///@param	InvestorID	投资者编号
	///@return	满足条件的地一个CUserInvestor，如果找不到，返回NULL
	CUserInvestor *startFindByBrokerIDInvestorID( const CReadOnlyBrokerIDType& BrokerID,  const CReadOnlyInvestorIDType& InvestorID);

	///寻找下一个符合条件的CUserInvestor，必须在startFindByBrokerIDInvestorID以后，endFindByBrokerIDInvestorID之前叫用
	///@return	下一个满足条件CUserInvestor，如果已经没有一个满足要求了，则返回NULL
	CUserInvestor *findNextByBrokerIDInvestorID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindByBrokerIDInvestorID(void);

	friend class CUserInvestorIteratorAllByUserID;

	///开始寻找CUserInvestor
	///@param	UserID	会员代码
	///@return	满足条件的地一个CUserInvestor，如果找不到，返回NULL
	CUserInvestor *startFindAllByUserID( const CReadOnlyUserIDType& UserID);

	///寻找下一个符合条件的CUserInvestor，必须在startFindAllByUserID以后，endFindAllByUserID之前叫用
	///@return	下一个满足条件CUserInvestor，如果已经没有一个满足要求了，则返回NULL
	CUserInvestor *findNextAllByUserID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByUserID(void);

	friend class CUserInvestorIteratorAllByBrokerIDUserID;

	///开始寻找CUserInvestor
	///@param	BrokerID	经纪公司代码
	///@param	UserID	会员代码
	///@return	满足条件的地一个CUserInvestor，如果找不到，返回NULL
	CUserInvestor *startFindAllByBrokerIDUserID( const CReadOnlyBrokerIDType& BrokerID,  const CReadOnlyUserIDType& UserID);

	///寻找下一个符合条件的CUserInvestor，必须在startFindAllByBrokerIDUserID以后，endFindAllByBrokerIDUserID之前叫用
	///@return	下一个满足条件CUserInvestor，如果已经没有一个满足要求了，则返回NULL
	CUserInvestor *findNextAllByBrokerIDUserID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByBrokerIDUserID(void);

	friend class CUserInvestorIteratorAllByBrokerID;

	///开始寻找CUserInvestor
	///@param	BrokerID	经纪公司代码
	///@return	满足条件的地一个CUserInvestor，如果找不到，返回NULL
	CUserInvestor *startFindAllByBrokerID( const CReadOnlyBrokerIDType& BrokerID);

	///寻找下一个符合条件的CUserInvestor，必须在startFindAllByBrokerID以后，endFindAllByBrokerID之前叫用
	///@return	下一个满足条件CUserInvestor，如果已经没有一个满足要求了，则返回NULL
	CUserInvestor *findNextAllByBrokerID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByBrokerID(void);

	friend class CUserInvestorIteratorAll;

	///开始寻找CUserInvestor
	///@return	满足条件的地一个CUserInvestor，如果找不到，返回NULL
	CUserInvestor *startFindAll();

	///寻找下一个符合条件的CUserInvestor，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CUserInvestor，如果已经没有一个满足要求了，则返回NULL
	CUserInvestor *findNextAll(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAll(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CUserInvestor加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pUserInvestor	要加入的UserInvestor
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CUserInvestor *internalAdd(CWriteableUserInvestor *pUserInvestor, bool bNoTransaction);
	
	
	///刷新该CUserInvestor的键值
	///@param	pUserInvestor	被刷新的CUserInvestor
	///@param	pNewUserInvestor	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor, bool updateIndex,bool bNoTransaction);
	
	///删除一个CUserInvestor，同时删除其索引
	///@param	pUserInvestor	要删除的CUserInvestor
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CUserInvestor *pUserInvestor, bool bNoTransaction);
/*
	///检查某个CUserInvestor是否属于本对象工厂
	///@param	pUserInvestor	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CUserInvestor *pUserInvestor);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于BrokerID+UserID+InvestorID的索引
	CAVLTree *pBrokerIDUserIDInvestorIDIndex;
	///基于BrokerID+InvestorID的索引
	CAVLTree *pBrokerIDInvestorIDIndex;
	
	
	///按照BrokerID，InvestorID检索时，存储的查询参数
	CBrokerIDType queryBrokerIDInSearchByBrokerIDInvestorID;
	CInvestorIDType queryInvestorIDInSearchByBrokerIDInvestorID;
	
	///按照BrokerID，InvestorID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchByBrokerIDInvestorID;
	///按照UserID检索时，存储的查询参数
	CUserIDType queryUserIDInSearchAllByUserID;
	
	///按照UserID检索时，存储最后一次找到的索引节点
	CUserInvestor *pLastFoundInSearchAllByUserID;
	///按照BrokerID，UserID检索时，存储的查询参数
	CBrokerIDType queryBrokerIDInSearchAllByBrokerIDUserID;
	CUserIDType queryUserIDInSearchAllByBrokerIDUserID;
	
	///按照BrokerID，UserID检索时，存储最后一次找到的索引节点
	CUserInvestor *pLastFoundInSearchAllByBrokerIDUserID;
	///按照BrokerID检索时，存储的查询参数
	CBrokerIDType queryBrokerIDInSearchAllByBrokerID;
	
	///按照BrokerID检索时，存储最后一次找到的索引节点
	CUserInvestor *pLastFoundInSearchAllByBrokerID;
	///按照检索时，存储的查询参数
	
	///按照检索时，存储最后一次找到的索引节点
	CUserInvestor *pLastFoundInSearchAll;
	
	///加入前触发
	///@param	pUserInvestor	要加入的UserInvestor
	virtual void beforeAdd(CWriteableUserInvestor *pUserInvestor);
	
	///加入后触发
	///@param	pUserInvestor	已经加入的UserInvestor
	virtual void afterAdd(CUserInvestor *pUserInvestor);

	///更新前触发	
	///@param	pUserInvestor	被刷新的CUserInvestor
	///@param	pNewUserInvestor	新的值
	virtual void beforeUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor);
	
	///更新后触发
	///@param	pUserInvestor	被刷新的CUserInvestor
	virtual void afterUpdate(CUserInvestor *pUserInvestor);
	
	///删除前触发
	///@param	pUserInvestor	要删除的CUserInvestor
	virtual void beforeRemove(CUserInvestor *pUserInvestor);
	
	///确认加入后触发
	///@param	pUserInvestor	已经加入的UserInvestor
	virtual void commitAdd(CUserInvestor *pUserInvestor);

	///确认更新后触发
	///@param	pUserInvestor	被刷新的CUserInvestor
	///@param	poldUserInvestor	原来的值
	virtual void commitUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pOldUserInvestor);
	
	///确认删除后触发
	///@param	pUserInvestor	已经删除的CUserInvestor
	virtual void commitRemove(CWriteableUserInvestor *pUserInvestor);

	///所有相关的触发器
	vector<CUserInvestorActionTrigger *> *pActionTriggers;
	vector<CUserInvestorCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableUserInvestor compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedFactory是一个错单表的对象工厂。它包含了一批错单表，
///同时又建立了如下索引，以方便查询：
///	OrderUserIDIndex
///	OrderLocalIDIndex
///	ExchangeIDOrderSysIDIndex
///	ExchangeIDSeatIDOrderLocalIDIndex
///使用本对象工厂，可以完成对错单表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByOrderUserID，唯一找到对象
///		使用findByOrderLocalID，唯一找到对象
///		使用findByExchangeIDAndOrderSysID，唯一找到对象
///		使用startFindAllByExchIDInvIDUserID，findNextAllByExchIDInvIDUserID和endFindAllByExchIDInvIDUserID完成查询操作
///		使用startFindAllByExchIDInstruIDUserID，findNextAllByExchIDInstruIDUserID和endFindAllByExchIDInstruIDUserID完成查询操作
///		使用startFindAll，findNextAll和endFindAll完成查询操作
///		使用findByExchangeIDSeatIDAndOrderLocalID，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	COrderInsertFailedFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxOrderInsertFailed，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	COrderInsertFailedFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~COrderInsertFailedFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的OrderInsertFailed
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的OrderInsertFailed，文件名将根据配置文件中的定义OrderInsertFailedCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的OrderInsertFailed
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的OrderInsertFailed，文件名将根据配置文件中的定义OrderInsertFailedCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class COrderInsertFailedResource;

	///将一个COrderInsertFailed加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pOrderInsertFailed	要加入的OrderInsertFailed
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	COrderInsertFailed *add(CWriteableOrderInsertFailed *pOrderInsertFailed, CTransaction *pTransaction=NULL);
	
	///刷新该COrderInsertFailed的值
	///@param	pOrderInsertFailed	被刷新的COrderInsertFailed
	///@param	pNewOrderInsertFailed	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pOrderInsertFailed	  需要被刷新或者新增的COrderInsertFailed,等于NULL表示是需要新增的
	///@param	pNewOrderInsertFailed	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	COrderInsertFailed* addOrUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个COrderInsertFailed，同时删除其索引
	///@param	pOrderInsertFailed	要删除的COrderInsertFailed
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(COrderInsertFailed *pOrderInsertFailed, CTransaction *pTransaction=NULL);
	
	///获取某个COrderInsertFailed
	///@param	pOrderInsertFailed	要读取的COrderInsertFailed
	///@param	pTragetOrderInsertFailed	存放结果的COrderInsertFailed
	void retrieve(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pTargetOrderInsertFailed);
	
	///获取第一个COrderInsertFailed
	///@return	得到的第一个COrderInsertFailed，如果没有，则返回NULL
	COrderInsertFailed *getFirst(void);
	
	///获取下一个COrderInsertFailed
	///@return	得到下一个COrderInsertFailed，如果没有，则返回NULL
	COrderInsertFailed *getNext(void);
	
	///结束获取COrderInsertFailed
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(COrderInsertFailedActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(COrderInsertFailedActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(COrderInsertFailedCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(COrderInsertFailedCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///构造所有对应的帐户的指针
	///@param	pFactory	构造对应的帐户的指针时，寻找的对象工厂
	void linkAllInvestorAccount(CInvestorAccountFactory *pFactory);
	
	///构造所有对应的合约持仓信息的指针
	///@param	pFactory	构造对应的合约持仓信息的指针时，寻找的对象工厂
	void linkAllInvestorPosition(CInvestorPositionFactory *pFactory);
	
	///构造所有对应的合约信息的指针
	///@param	pFactory	构造对应的合约信息的指针时，寻找的对象工厂
	void linkAllInstrument(CInstrumentFactory *pFactory);
	
	///构造所有对应的投资者保证金率信息的指针
	///@param	pFactory	构造对应的投资者保证金率信息的指针时，寻找的对象工厂
	void linkAllInvestorMargin(CInvestorMarginFactory *pFactory);
	
	///构造所有对应的投资者手续费率信息的指针
	///@param	pFactory	构造对应的投资者手续费率信息的指针时，寻找的对象工厂
	void linkAllInvestorFee(CInvestorFeeFactory *pFactory);
	
	///寻找COrderInsertFailed
	///@param	OrderUserID	交易用户代码
	///@return	找到的COrderInsertFailed，如果找不到，返回NULL
	COrderInsertFailed *findByOrderUserID( const CReadOnlyUserIDType&  OrderUserID);



	///寻找COrderInsertFailed
	///@param	OrderLocalID	本地报单号
	///@return	找到的COrderInsertFailed，如果找不到，返回NULL
	COrderInsertFailed *findByOrderLocalID( const CReadOnlyOrderLocalIDType&  OrderLocalID);



	///寻找COrderInsertFailed
	///@param	ExchangeID	交易所代码
	///@param	OrderSysID	资金帐号
	///@return	找到的COrderInsertFailed，如果找不到，返回NULL
	COrderInsertFailed *findByExchangeIDAndOrderSysID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyOrderSysIDType&  OrderSysID);



	friend class COrderInsertFailedIteratorAllByExchIDInvIDUserID;

	///开始寻找COrderInsertFailed
	///@param	ExchangeID	交易所代码
	///@param	InvestorID	投资者编号
	///@param	UserID	交易用户代码
	///@return	满足条件的地一个COrderInsertFailed，如果找不到，返回NULL
	COrderInsertFailed *startFindAllByExchIDInvIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInvestorIDType& InvestorID,  const CReadOnlyUserIDType& UserID);

	///寻找下一个符合条件的COrderInsertFailed，必须在startFindAllByExchIDInvIDUserID以后，endFindAllByExchIDInvIDUserID之前叫用
	///@return	下一个满足条件COrderInsertFailed，如果已经没有一个满足要求了，则返回NULL
	COrderInsertFailed *findNextAllByExchIDInvIDUserID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByExchIDInvIDUserID(void);

	friend class COrderInsertFailedIteratorAllByExchIDInstruIDUserID;

	///开始寻找COrderInsertFailed
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约号
	///@param	UserID	交易用户代码
	///@return	满足条件的地一个COrderInsertFailed，如果找不到，返回NULL
	COrderInsertFailed *startFindAllByExchIDInstruIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& InstrumentID,  const CReadOnlyUserIDType& UserID);

	///寻找下一个符合条件的COrderInsertFailed，必须在startFindAllByExchIDInstruIDUserID以后，endFindAllByExchIDInstruIDUserID之前叫用
	///@return	下一个满足条件COrderInsertFailed，如果已经没有一个满足要求了，则返回NULL
	COrderInsertFailed *findNextAllByExchIDInstruIDUserID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByExchIDInstruIDUserID(void);

	friend class COrderInsertFailedIteratorAll;

	///开始寻找COrderInsertFailed
	///@return	满足条件的地一个COrderInsertFailed，如果找不到，返回NULL
	COrderInsertFailed *startFindAll();

	///寻找下一个符合条件的COrderInsertFailed，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件COrderInsertFailed，如果已经没有一个满足要求了，则返回NULL
	COrderInsertFailed *findNextAll(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAll(void);

	///寻找COrderInsertFailed
	///@param	ExchangeID	交易所代码
	///@param	SeatID	席位代码
	///@param	OrderLocalID	本地报单编号
	///@return	找到的COrderInsertFailed，如果找不到，返回NULL
	COrderInsertFailed *findByExchangeIDSeatIDAndOrderLocalID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlySeatIDType&  SeatID,  const CReadOnlyOrderLocalIDType&  OrderLocalID);

	///根据主码寻找
	///@param	ExchangeID	交易所代码
	///@param	SeatID	席位代码
	///@param	OrderLocalID	本地报单编号
	///@return	找到的COrderInsertFailed，如果找不到，返回NULL
	COrderInsertFailed *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlySeatIDType&  SeatID,  const CReadOnlyOrderLocalIDType&  OrderLocalID);
	
	///根据主键寻找COrderInsertFailed
	///@param	pOrderInsertFailed	要找的值
	///@return	找到的COrderInsertFailed，如果找不到，返回NULL
	COrderInsertFailed *findByPK(CWriteableOrderInsertFailed *pOrderInsertFailed);

	///根据主键获取COrderInsertFailed
	///@param	pOrderInsertFailed	要获取的值，同时用于存放返回的结果
	///@return	找到的COrderInsertFailed，如果找不到，返回NULL
	bool retrieveByPK(CWriteableOrderInsertFailed *pOrderInsertFailed);

	///根据主键增加新的COrderInsertFailed
	///@param	pOrderInsertFailed	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的COrderInsertFailed，如果插入失败，则返回NULL
	COrderInsertFailed *addByPK(CWriteableOrderInsertFailed *pOrderInsertFailed, CTransaction *pTransaction=NULL);

	///根据主键更新COrderInsertFailed的值
	///@param	pOrderInsertFailed	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableOrderInsertFailed *pOrderInsertFailed, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除COrderInsertFailed
	///@param	pOrderInsertFailed	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableOrderInsertFailed *pOrderInsertFailed, CTransaction *pTransaction=NULL);


private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个COrderInsertFailed加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pOrderInsertFailed	要加入的OrderInsertFailed
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	COrderInsertFailed *internalAdd(CWriteableOrderInsertFailed *pOrderInsertFailed, bool bNoTransaction);
	
	
	///刷新该COrderInsertFailed的键值
	///@param	pOrderInsertFailed	被刷新的COrderInsertFailed
	///@param	pNewOrderInsertFailed	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed, bool updateIndex,bool bNoTransaction);
	
	///删除一个COrderInsertFailed，同时删除其索引
	///@param	pOrderInsertFailed	要删除的COrderInsertFailed
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(COrderInsertFailed *pOrderInsertFailed, bool bNoTransaction);
/*
	///检查某个COrderInsertFailed是否属于本对象工厂
	///@param	pOrderInsertFailed	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(COrderInsertFailed *pOrderInsertFailed);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于OrderUserID的索引
	CAVLTree *pOrderUserIDIndex;
	///基于OrderLocalID的索引
	CAVLTree *pOrderLocalIDIndex;
	///基于ExchangeID+OrderSysID的索引
	CAVLTree *pExchangeIDOrderSysIDIndex;
	///基于ExchangeID+SeatID+OrderLocalID的索引
	CAVLTree *pExchangeIDSeatIDOrderLocalIDIndex;
	
	
	///按照ExchangeID，InvestorID，UserID检索时，存储的查询参数
	CExchangeIDType queryExchangeIDInSearchAllByExchIDInvIDUserID;
	CInvestorIDType queryInvestorIDInSearchAllByExchIDInvIDUserID;
	CUserIDType queryUserIDInSearchAllByExchIDInvIDUserID;
	
	///按照ExchangeID，InvestorID，UserID检索时，存储最后一次找到的索引节点
	COrderInsertFailed *pLastFoundInSearchAllByExchIDInvIDUserID;
	///按照ExchangeID，InstrumentID，UserID检索时，存储的查询参数
	CExchangeIDType queryExchangeIDInSearchAllByExchIDInstruIDUserID;
	CInstrumentIDType queryInstrumentIDInSearchAllByExchIDInstruIDUserID;
	CUserIDType queryUserIDInSearchAllByExchIDInstruIDUserID;
	
	///按照ExchangeID，InstrumentID，UserID检索时，存储最后一次找到的索引节点
	COrderInsertFailed *pLastFoundInSearchAllByExchIDInstruIDUserID;
	///按照检索时，存储的查询参数
	
	///按照检索时，存储最后一次找到的索引节点
	COrderInsertFailed *pLastFoundInSearchAll;
	
	///加入前触发
	///@param	pOrderInsertFailed	要加入的OrderInsertFailed
	virtual void beforeAdd(CWriteableOrderInsertFailed *pOrderInsertFailed);
	
	///加入后触发
	///@param	pOrderInsertFailed	已经加入的OrderInsertFailed
	virtual void afterAdd(COrderInsertFailed *pOrderInsertFailed);

	///更新前触发	
	///@param	pOrderInsertFailed	被刷新的COrderInsertFailed
	///@param	pNewOrderInsertFailed	新的值
	virtual void beforeUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed);
	
	///更新后触发
	///@param	pOrderInsertFailed	被刷新的COrderInsertFailed
	virtual void afterUpdate(COrderInsertFailed *pOrderInsertFailed);
	
	///删除前触发
	///@param	pOrderInsertFailed	要删除的COrderInsertFailed
	virtual void beforeRemove(COrderInsertFailed *pOrderInsertFailed);
	
	///确认加入后触发
	///@param	pOrderInsertFailed	已经加入的OrderInsertFailed
	virtual void commitAdd(COrderInsertFailed *pOrderInsertFailed);

	///确认更新后触发
	///@param	pOrderInsertFailed	被刷新的COrderInsertFailed
	///@param	poldOrderInsertFailed	原来的值
	virtual void commitUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pOldOrderInsertFailed);
	
	///确认删除后触发
	///@param	pOrderInsertFailed	已经删除的COrderInsertFailed
	virtual void commitRemove(CWriteableOrderInsertFailed *pOrderInsertFailed);

	///所有相关的触发器
	vector<COrderInsertFailedActionTrigger *> *pActionTriggers;
	vector<COrderInsertFailedCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableOrderInsertFailed compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightFactory是一个用户交易权限表的对象工厂。它包含了一批用户交易权限表，
///同时又建立了如下索引，以方便查询：
///	BrkExIDInsUserInvIndex
///使用本对象工厂，可以完成对用户交易权限表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrkExIDInsUserInv，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CUserTradingRightFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxUserTradingRight，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CUserTradingRightFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CUserTradingRightFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的UserTradingRight
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的UserTradingRight，文件名将根据配置文件中的定义UserTradingRightCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的UserTradingRight
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的UserTradingRight，文件名将根据配置文件中的定义UserTradingRightCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CUserTradingRightResource;

	///将一个CUserTradingRight加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pUserTradingRight	要加入的UserTradingRight
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CUserTradingRight *add(CWriteableUserTradingRight *pUserTradingRight, CTransaction *pTransaction=NULL);
	
	///刷新该CUserTradingRight的值
	///@param	pUserTradingRight	被刷新的CUserTradingRight
	///@param	pNewUserTradingRight	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pUserTradingRight	  需要被刷新或者新增的CUserTradingRight,等于NULL表示是需要新增的
	///@param	pNewUserTradingRight	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CUserTradingRight* addOrUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CUserTradingRight，同时删除其索引
	///@param	pUserTradingRight	要删除的CUserTradingRight
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CUserTradingRight *pUserTradingRight, CTransaction *pTransaction=NULL);
	
	///获取某个CUserTradingRight
	///@param	pUserTradingRight	要读取的CUserTradingRight
	///@param	pTragetUserTradingRight	存放结果的CUserTradingRight
	void retrieve(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pTargetUserTradingRight);
	
	///获取第一个CUserTradingRight
	///@return	得到的第一个CUserTradingRight，如果没有，则返回NULL
	CUserTradingRight *getFirst(void);
	
	///获取下一个CUserTradingRight
	///@return	得到下一个CUserTradingRight，如果没有，则返回NULL
	CUserTradingRight *getNext(void);
	
	///结束获取CUserTradingRight
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CUserTradingRightActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CUserTradingRightActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CUserTradingRightCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CUserTradingRightCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CUserTradingRight
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约编号
	///@param	UserID	登录用户代码
	///@param	InvestorID	投资者代码
	///@return	找到的CUserTradingRight，如果找不到，返回NULL
	CUserTradingRight *findByBrkExIDInsUserInv( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyInvestorIDType&  InvestorID);

	///根据主码寻找
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约编号
	///@param	UserID	登录用户代码
	///@param	InvestorID	投资者代码
	///@return	找到的CUserTradingRight，如果找不到，返回NULL
	CUserTradingRight *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyInvestorIDType&  InvestorID);
	
	///根据主键寻找CUserTradingRight
	///@param	pUserTradingRight	要找的值
	///@return	找到的CUserTradingRight，如果找不到，返回NULL
	CUserTradingRight *findByPK(CWriteableUserTradingRight *pUserTradingRight);

	///根据主键获取CUserTradingRight
	///@param	pUserTradingRight	要获取的值，同时用于存放返回的结果
	///@return	找到的CUserTradingRight，如果找不到，返回NULL
	bool retrieveByPK(CWriteableUserTradingRight *pUserTradingRight);

	///根据主键增加新的CUserTradingRight
	///@param	pUserTradingRight	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CUserTradingRight，如果插入失败，则返回NULL
	CUserTradingRight *addByPK(CWriteableUserTradingRight *pUserTradingRight, CTransaction *pTransaction=NULL);

	///根据主键更新CUserTradingRight的值
	///@param	pUserTradingRight	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableUserTradingRight *pUserTradingRight, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CUserTradingRight
	///@param	pUserTradingRight	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableUserTradingRight *pUserTradingRight, CTransaction *pTransaction=NULL);


private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CUserTradingRight加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pUserTradingRight	要加入的UserTradingRight
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CUserTradingRight *internalAdd(CWriteableUserTradingRight *pUserTradingRight, bool bNoTransaction);
	
	
	///刷新该CUserTradingRight的键值
	///@param	pUserTradingRight	被刷新的CUserTradingRight
	///@param	pNewUserTradingRight	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight, bool updateIndex,bool bNoTransaction);
	
	///删除一个CUserTradingRight，同时删除其索引
	///@param	pUserTradingRight	要删除的CUserTradingRight
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CUserTradingRight *pUserTradingRight, bool bNoTransaction);
/*
	///检查某个CUserTradingRight是否属于本对象工厂
	///@param	pUserTradingRight	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CUserTradingRight *pUserTradingRight);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于BrokerID+ExchangeID+InstrumentID+UserID+InvestorID的索引
	CAVLTree *pBrkExIDInsUserInvIndex;
	
	
	
	///加入前触发
	///@param	pUserTradingRight	要加入的UserTradingRight
	virtual void beforeAdd(CWriteableUserTradingRight *pUserTradingRight);
	
	///加入后触发
	///@param	pUserTradingRight	已经加入的UserTradingRight
	virtual void afterAdd(CUserTradingRight *pUserTradingRight);

	///更新前触发	
	///@param	pUserTradingRight	被刷新的CUserTradingRight
	///@param	pNewUserTradingRight	新的值
	virtual void beforeUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight);
	
	///更新后触发
	///@param	pUserTradingRight	被刷新的CUserTradingRight
	virtual void afterUpdate(CUserTradingRight *pUserTradingRight);
	
	///删除前触发
	///@param	pUserTradingRight	要删除的CUserTradingRight
	virtual void beforeRemove(CUserTradingRight *pUserTradingRight);
	
	///确认加入后触发
	///@param	pUserTradingRight	已经加入的UserTradingRight
	virtual void commitAdd(CUserTradingRight *pUserTradingRight);

	///确认更新后触发
	///@param	pUserTradingRight	被刷新的CUserTradingRight
	///@param	poldUserTradingRight	原来的值
	virtual void commitUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pOldUserTradingRight);
	
	///确认删除后触发
	///@param	pUserTradingRight	已经删除的CUserTradingRight
	virtual void commitRemove(CWriteableUserTradingRight *pUserTradingRight);

	///所有相关的触发器
	vector<CUserTradingRightActionTrigger *> *pActionTriggers;
	vector<CUserTradingRightCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableUserTradingRight compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeFactory是一个当前时间的对象工厂。它包含了一批当前时间，
///同时又建立了如下索引，以方便查询：
///使用本对象工厂，可以完成对当前时间的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CCurrentTimeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxCurrentTime，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CCurrentTimeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CCurrentTimeFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的CurrentTime
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的CurrentTime，文件名将根据配置文件中的定义CurrentTimeCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的CurrentTime
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的CurrentTime，文件名将根据配置文件中的定义CurrentTimeCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CCurrentTimeResource;

	///将一个CCurrentTime加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pCurrentTime	要加入的CurrentTime
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CCurrentTime *add(CWriteableCurrentTime *pCurrentTime, CTransaction *pTransaction=NULL);
	
	///刷新该CCurrentTime的值
	///@param	pCurrentTime	被刷新的CCurrentTime
	///@param	pNewCurrentTime	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pCurrentTime	  需要被刷新或者新增的CCurrentTime,等于NULL表示是需要新增的
	///@param	pNewCurrentTime	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CCurrentTime* addOrUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CCurrentTime，同时删除其索引
	///@param	pCurrentTime	要删除的CCurrentTime
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CCurrentTime *pCurrentTime, CTransaction *pTransaction=NULL);
	
	///获取某个CCurrentTime
	///@param	pCurrentTime	要读取的CCurrentTime
	///@param	pTragetCurrentTime	存放结果的CCurrentTime
	void retrieve(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pTargetCurrentTime);
	
	///获取第一个CCurrentTime
	///@return	得到的第一个CCurrentTime，如果没有，则返回NULL
	CCurrentTime *getFirst(void);
	
	///获取下一个CCurrentTime
	///@return	得到下一个CCurrentTime，如果没有，则返回NULL
	CCurrentTime *getNext(void);
	
	///结束获取CCurrentTime
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CCurrentTimeActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CCurrentTimeActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CCurrentTimeCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CCurrentTimeCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CCurrentTime加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pCurrentTime	要加入的CurrentTime
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CCurrentTime *internalAdd(CWriteableCurrentTime *pCurrentTime, bool bNoTransaction);
	
	
	///刷新该CCurrentTime的键值
	///@param	pCurrentTime	被刷新的CCurrentTime
	///@param	pNewCurrentTime	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime, bool updateIndex,bool bNoTransaction);
	
	///删除一个CCurrentTime，同时删除其索引
	///@param	pCurrentTime	要删除的CCurrentTime
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CCurrentTime *pCurrentTime, bool bNoTransaction);
/*
	///检查某个CCurrentTime是否属于本对象工厂
	///@param	pCurrentTime	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CCurrentTime *pCurrentTime);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	
	
	
	///加入前触发
	///@param	pCurrentTime	要加入的CurrentTime
	virtual void beforeAdd(CWriteableCurrentTime *pCurrentTime);
	
	///加入后触发
	///@param	pCurrentTime	已经加入的CurrentTime
	virtual void afterAdd(CCurrentTime *pCurrentTime);

	///更新前触发	
	///@param	pCurrentTime	被刷新的CCurrentTime
	///@param	pNewCurrentTime	新的值
	virtual void beforeUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime);
	
	///更新后触发
	///@param	pCurrentTime	被刷新的CCurrentTime
	virtual void afterUpdate(CCurrentTime *pCurrentTime);
	
	///删除前触发
	///@param	pCurrentTime	要删除的CCurrentTime
	virtual void beforeRemove(CCurrentTime *pCurrentTime);
	
	///确认加入后触发
	///@param	pCurrentTime	已经加入的CurrentTime
	virtual void commitAdd(CCurrentTime *pCurrentTime);

	///确认更新后触发
	///@param	pCurrentTime	被刷新的CCurrentTime
	///@param	poldCurrentTime	原来的值
	virtual void commitUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pOldCurrentTime);
	
	///确认删除后触发
	///@param	pCurrentTime	已经删除的CCurrentTime
	virtual void commitRemove(CWriteableCurrentTime *pCurrentTime);

	///所有相关的触发器
	vector<CCurrentTimeActionTrigger *> *pActionTriggers;
	vector<CCurrentTimeCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableCurrentTime compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionFactory是一个交易员在线会话的对象工厂。它包含了一批交易员在线会话，
///同时又建立了如下索引，以方便查询：
///	SessionIDFrontIDIndex
///	BrokerIDUserIDSFIDIndex
///	UserIndex
///使用本对象工厂，可以完成对交易员在线会话的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findBySessionIDFrontID，唯一找到对象
///		使用findByBrokerIDUserIDSFID，唯一找到对象
///		使用startFindByUserID，findNextByUserID和endFindByUserID完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CUserSessionFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxUserSession，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CUserSessionFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CUserSessionFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的UserSession
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的UserSession，文件名将根据配置文件中的定义UserSessionCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的UserSession
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的UserSession，文件名将根据配置文件中的定义UserSessionCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CUserSessionResource;

	///将一个CUserSession加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pUserSession	要加入的UserSession
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CUserSession *add(CWriteableUserSession *pUserSession, CTransaction *pTransaction=NULL);
	
	///刷新该CUserSession的值
	///@param	pUserSession	被刷新的CUserSession
	///@param	pNewUserSession	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pUserSession	  需要被刷新或者新增的CUserSession,等于NULL表示是需要新增的
	///@param	pNewUserSession	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CUserSession* addOrUpdate(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CUserSession，同时删除其索引
	///@param	pUserSession	要删除的CUserSession
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CUserSession *pUserSession, CTransaction *pTransaction=NULL);
	
	///获取某个CUserSession
	///@param	pUserSession	要读取的CUserSession
	///@param	pTragetUserSession	存放结果的CUserSession
	void retrieve(CUserSession *pUserSession, CWriteableUserSession *pTargetUserSession);
	
	///获取第一个CUserSession
	///@return	得到的第一个CUserSession，如果没有，则返回NULL
	CUserSession *getFirst(void);
	
	///获取下一个CUserSession
	///@return	得到下一个CUserSession，如果没有，则返回NULL
	CUserSession *getNext(void);
	
	///结束获取CUserSession
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CUserSessionActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CUserSessionActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CUserSessionCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CUserSessionCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CUserSession
	///@param	SessionID	会话号
	///@param	FrontID	前置编号
	///@return	找到的CUserSession，如果找不到，返回NULL
	CUserSession *findBySessionIDFrontID( const CReadOnlySessionIDType&  SessionID,  const CReadOnlyFrontIDType&  FrontID);

	///根据主码寻找
	///@param	SessionID	会话号
	///@param	FrontID	前置编号
	///@return	找到的CUserSession，如果找不到，返回NULL
	CUserSession *findByPK( const CReadOnlySessionIDType&  SessionID,  const CReadOnlyFrontIDType&  FrontID);
	
	///根据主键寻找CUserSession
	///@param	pUserSession	要找的值
	///@return	找到的CUserSession，如果找不到，返回NULL
	CUserSession *findByPK(CWriteableUserSession *pUserSession);

	///根据主键获取CUserSession
	///@param	pUserSession	要获取的值，同时用于存放返回的结果
	///@return	找到的CUserSession，如果找不到，返回NULL
	bool retrieveByPK(CWriteableUserSession *pUserSession);

	///根据主键增加新的CUserSession
	///@param	pUserSession	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CUserSession，如果插入失败，则返回NULL
	CUserSession *addByPK(CWriteableUserSession *pUserSession, CTransaction *pTransaction=NULL);

	///根据主键更新CUserSession的值
	///@param	pUserSession	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableUserSession *pUserSession, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CUserSession
	///@param	pUserSession	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableUserSession *pUserSession, CTransaction *pTransaction=NULL);


	///寻找CUserSession
	///@param	BrokerID	经纪公司编号
	///@param	UserID	用户号
	///@param	SessionID	会话号
	///@param	FrontID	前置编号
	///@return	找到的CUserSession，如果找不到，返回NULL
	CUserSession *findByBrokerIDUserIDSFID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlySessionIDType&  SessionID,  const CReadOnlyFrontIDType&  FrontID);



	friend class CUserSessionIteratorByUserID;

	///开始寻找CUserSession
	///@param	UserID	用户号
	///@return	满足条件的地一个CUserSession，如果找不到，返回NULL
	CUserSession *startFindByUserID( const CReadOnlyUserIDType& UserID);

	///寻找下一个符合条件的CUserSession，必须在startFindByUserID以后，endFindByUserID之前叫用
	///@return	下一个满足条件CUserSession，如果已经没有一个满足要求了，则返回NULL
	CUserSession *findNextByUserID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindByUserID(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CUserSession加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pUserSession	要加入的UserSession
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CUserSession *internalAdd(CWriteableUserSession *pUserSession, bool bNoTransaction);
	
	
	///刷新该CUserSession的键值
	///@param	pUserSession	被刷新的CUserSession
	///@param	pNewUserSession	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession, bool updateIndex,bool bNoTransaction);
	
	///删除一个CUserSession，同时删除其索引
	///@param	pUserSession	要删除的CUserSession
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CUserSession *pUserSession, bool bNoTransaction);
/*
	///检查某个CUserSession是否属于本对象工厂
	///@param	pUserSession	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CUserSession *pUserSession);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于SessionID+FrontID的索引
	CAVLTree *pSessionIDFrontIDIndex;
	///基于BrokerID+UserID+SessionID+FrontID的索引
	CAVLTree *pBrokerIDUserIDSFIDIndex;
	///基于UserID的索引
	CAVLTree *pUserIndex;
	
	
	///按照UserID检索时，存储的查询参数
	CUserIDType queryUserIDInSearchByUserID;
	
	///按照UserID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchByUserID;
	
	///加入前触发
	///@param	pUserSession	要加入的UserSession
	virtual void beforeAdd(CWriteableUserSession *pUserSession);
	
	///加入后触发
	///@param	pUserSession	已经加入的UserSession
	virtual void afterAdd(CUserSession *pUserSession);

	///更新前触发	
	///@param	pUserSession	被刷新的CUserSession
	///@param	pNewUserSession	新的值
	virtual void beforeUpdate(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession);
	
	///更新后触发
	///@param	pUserSession	被刷新的CUserSession
	virtual void afterUpdate(CUserSession *pUserSession);
	
	///删除前触发
	///@param	pUserSession	要删除的CUserSession
	virtual void beforeRemove(CUserSession *pUserSession);
	
	///确认加入后触发
	///@param	pUserSession	已经加入的UserSession
	virtual void commitAdd(CUserSession *pUserSession);

	///确认更新后触发
	///@param	pUserSession	被刷新的CUserSession
	///@param	poldUserSession	原来的值
	virtual void commitUpdate(CUserSession *pUserSession, CWriteableUserSession *pOldUserSession);
	
	///确认删除后触发
	///@param	pUserSession	已经删除的CUserSession
	virtual void commitRemove(CWriteableUserSession *pUserSession);

	///所有相关的触发器
	vector<CUserSessionActionTrigger *> *pActionTriggers;
	vector<CUserSessionCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableUserSession compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDFactory是一个最大本地报单号的对象工厂。它包含了一批最大本地报单号，
///同时又建立了如下索引，以方便查询：
///使用本对象工厂，可以完成对最大本地报单号的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByFrontIDSessionID，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CMaxLocalIDFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxMaxLocalID，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CMaxLocalIDFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CMaxLocalIDFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的MaxLocalID
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的MaxLocalID，文件名将根据配置文件中的定义MaxLocalIDCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的MaxLocalID
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的MaxLocalID，文件名将根据配置文件中的定义MaxLocalIDCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CMaxLocalIDResource;

	///将一个CMaxLocalID加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pMaxLocalID	要加入的MaxLocalID
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CMaxLocalID *add(CWriteableMaxLocalID *pMaxLocalID, CTransaction *pTransaction=NULL);
	
	///刷新该CMaxLocalID的值
	///@param	pMaxLocalID	被刷新的CMaxLocalID
	///@param	pNewMaxLocalID	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pMaxLocalID	  需要被刷新或者新增的CMaxLocalID,等于NULL表示是需要新增的
	///@param	pNewMaxLocalID	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CMaxLocalID* addOrUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CMaxLocalID，同时删除其索引
	///@param	pMaxLocalID	要删除的CMaxLocalID
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CMaxLocalID *pMaxLocalID, CTransaction *pTransaction=NULL);
	
	///获取某个CMaxLocalID
	///@param	pMaxLocalID	要读取的CMaxLocalID
	///@param	pTragetMaxLocalID	存放结果的CMaxLocalID
	void retrieve(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pTargetMaxLocalID);
	
	///获取第一个CMaxLocalID
	///@return	得到的第一个CMaxLocalID，如果没有，则返回NULL
	CMaxLocalID *getFirst(void);
	
	///获取下一个CMaxLocalID
	///@return	得到下一个CMaxLocalID，如果没有，则返回NULL
	CMaxLocalID *getNext(void);
	
	///结束获取CMaxLocalID
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CMaxLocalIDActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CMaxLocalIDActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CMaxLocalIDCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CMaxLocalIDCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CMaxLocalID
	///@param	FrontID	前置编号
	///@param	SessionID	会话号
	///@return	找到的CMaxLocalID，如果找不到，返回NULL
	CMaxLocalID *findByFrontIDSessionID( const CReadOnlyFrontIDType&  FrontID,  const CReadOnlySessionIDType&  SessionID);

	///根据主码寻找
	///@param	FrontID	前置编号
	///@param	SessionID	会话号
	///@return	找到的CMaxLocalID，如果找不到，返回NULL
	CMaxLocalID *findByPK( const CReadOnlyFrontIDType&  FrontID,  const CReadOnlySessionIDType&  SessionID);
	
	///根据主键寻找CMaxLocalID
	///@param	pMaxLocalID	要找的值
	///@return	找到的CMaxLocalID，如果找不到，返回NULL
	CMaxLocalID *findByPK(CWriteableMaxLocalID *pMaxLocalID);

	///根据主键获取CMaxLocalID
	///@param	pMaxLocalID	要获取的值，同时用于存放返回的结果
	///@return	找到的CMaxLocalID，如果找不到，返回NULL
	bool retrieveByPK(CWriteableMaxLocalID *pMaxLocalID);

	///根据主键增加新的CMaxLocalID
	///@param	pMaxLocalID	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CMaxLocalID，如果插入失败，则返回NULL
	CMaxLocalID *addByPK(CWriteableMaxLocalID *pMaxLocalID, CTransaction *pTransaction=NULL);

	///根据主键更新CMaxLocalID的值
	///@param	pMaxLocalID	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableMaxLocalID *pMaxLocalID, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CMaxLocalID
	///@param	pMaxLocalID	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableMaxLocalID *pMaxLocalID, CTransaction *pTransaction=NULL);


private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CMaxLocalID加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pMaxLocalID	要加入的MaxLocalID
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CMaxLocalID *internalAdd(CWriteableMaxLocalID *pMaxLocalID, bool bNoTransaction);
	
	
	///刷新该CMaxLocalID的键值
	///@param	pMaxLocalID	被刷新的CMaxLocalID
	///@param	pNewMaxLocalID	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID, bool updateIndex,bool bNoTransaction);
	
	///删除一个CMaxLocalID，同时删除其索引
	///@param	pMaxLocalID	要删除的CMaxLocalID
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CMaxLocalID *pMaxLocalID, bool bNoTransaction);
/*
	///检查某个CMaxLocalID是否属于本对象工厂
	///@param	pMaxLocalID	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CMaxLocalID *pMaxLocalID);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	
	///基于FrontIDSessionID的hash索引
	CHashIndex *pFrontIDSessionIDHashIndex;
	
	
	///加入前触发
	///@param	pMaxLocalID	要加入的MaxLocalID
	virtual void beforeAdd(CWriteableMaxLocalID *pMaxLocalID);
	
	///加入后触发
	///@param	pMaxLocalID	已经加入的MaxLocalID
	virtual void afterAdd(CMaxLocalID *pMaxLocalID);

	///更新前触发	
	///@param	pMaxLocalID	被刷新的CMaxLocalID
	///@param	pNewMaxLocalID	新的值
	virtual void beforeUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID);
	
	///更新后触发
	///@param	pMaxLocalID	被刷新的CMaxLocalID
	virtual void afterUpdate(CMaxLocalID *pMaxLocalID);
	
	///删除前触发
	///@param	pMaxLocalID	要删除的CMaxLocalID
	virtual void beforeRemove(CMaxLocalID *pMaxLocalID);
	
	///确认加入后触发
	///@param	pMaxLocalID	已经加入的MaxLocalID
	virtual void commitAdd(CMaxLocalID *pMaxLocalID);

	///确认更新后触发
	///@param	pMaxLocalID	被刷新的CMaxLocalID
	///@param	poldMaxLocalID	原来的值
	virtual void commitUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pOldMaxLocalID);
	
	///确认删除后触发
	///@param	pMaxLocalID	已经删除的CMaxLocalID
	virtual void commitRemove(CWriteableMaxLocalID *pMaxLocalID);

	///所有相关的触发器
	vector<CMaxLocalIDActionTrigger *> *pActionTriggers;
	vector<CMaxLocalIDCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableMaxLocalID compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDFactory是一个用户本地报单号的对象工厂。它包含了一批用户本地报单号，
///同时又建立了如下索引，以方便查询：
///使用本对象工厂，可以完成对用户本地报单号的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrokerIDUserIDLocalID，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CBrkUserIDLocalIDFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxBrkUserIDLocalID，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CBrkUserIDLocalIDFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CBrkUserIDLocalIDFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的BrkUserIDLocalID
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的BrkUserIDLocalID，文件名将根据配置文件中的定义BrkUserIDLocalIDCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的BrkUserIDLocalID
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的BrkUserIDLocalID，文件名将根据配置文件中的定义BrkUserIDLocalIDCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CBrkUserIDLocalIDResource;

	///将一个CBrkUserIDLocalID加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pBrkUserIDLocalID	要加入的BrkUserIDLocalID
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CBrkUserIDLocalID *add(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID, CTransaction *pTransaction=NULL);
	
	///刷新该CBrkUserIDLocalID的值
	///@param	pBrkUserIDLocalID	被刷新的CBrkUserIDLocalID
	///@param	pNewBrkUserIDLocalID	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pBrkUserIDLocalID	  需要被刷新或者新增的CBrkUserIDLocalID,等于NULL表示是需要新增的
	///@param	pNewBrkUserIDLocalID	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CBrkUserIDLocalID* addOrUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CBrkUserIDLocalID，同时删除其索引
	///@param	pBrkUserIDLocalID	要删除的CBrkUserIDLocalID
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CBrkUserIDLocalID *pBrkUserIDLocalID, CTransaction *pTransaction=NULL);
	
	///获取某个CBrkUserIDLocalID
	///@param	pBrkUserIDLocalID	要读取的CBrkUserIDLocalID
	///@param	pTragetBrkUserIDLocalID	存放结果的CBrkUserIDLocalID
	void retrieve(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pTargetBrkUserIDLocalID);
	
	///获取第一个CBrkUserIDLocalID
	///@return	得到的第一个CBrkUserIDLocalID，如果没有，则返回NULL
	CBrkUserIDLocalID *getFirst(void);
	
	///获取下一个CBrkUserIDLocalID
	///@return	得到下一个CBrkUserIDLocalID，如果没有，则返回NULL
	CBrkUserIDLocalID *getNext(void);
	
	///结束获取CBrkUserIDLocalID
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CBrkUserIDLocalIDActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CBrkUserIDLocalIDActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CBrkUserIDLocalIDCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CBrkUserIDLocalIDCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///构造所有对应的报单的指针
	///@param	pFactory	构造对应的报单的指针时，寻找的对象工厂
	void linkAllPreOrder(CPreOrderFactory *pFactory);
	
	///寻找CBrkUserIDLocalID
	///@param	BrokerID	经纪公司编号
	///@param	UserID	用户编号
	///@param	UserOrderLocalID	本地报单号
	///@return	找到的CBrkUserIDLocalID，如果找不到，返回NULL
	CBrkUserIDLocalID *findByBrokerIDUserIDLocalID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyUserOrderLocalIDType&  UserOrderLocalID);

	///根据主码寻找
	///@param	BrokerID	经纪公司编号
	///@param	UserID	用户编号
	///@param	UserOrderLocalID	本地报单号
	///@return	找到的CBrkUserIDLocalID，如果找不到，返回NULL
	CBrkUserIDLocalID *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyUserOrderLocalIDType&  UserOrderLocalID);
	
	///根据主键寻找CBrkUserIDLocalID
	///@param	pBrkUserIDLocalID	要找的值
	///@return	找到的CBrkUserIDLocalID，如果找不到，返回NULL
	CBrkUserIDLocalID *findByPK(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID);

	///根据主键获取CBrkUserIDLocalID
	///@param	pBrkUserIDLocalID	要获取的值，同时用于存放返回的结果
	///@return	找到的CBrkUserIDLocalID，如果找不到，返回NULL
	bool retrieveByPK(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID);

	///根据主键增加新的CBrkUserIDLocalID
	///@param	pBrkUserIDLocalID	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CBrkUserIDLocalID，如果插入失败，则返回NULL
	CBrkUserIDLocalID *addByPK(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID, CTransaction *pTransaction=NULL);

	///根据主键更新CBrkUserIDLocalID的值
	///@param	pBrkUserIDLocalID	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CBrkUserIDLocalID
	///@param	pBrkUserIDLocalID	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID, CTransaction *pTransaction=NULL);


private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CBrkUserIDLocalID加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pBrkUserIDLocalID	要加入的BrkUserIDLocalID
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CBrkUserIDLocalID *internalAdd(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID, bool bNoTransaction);
	
	
	///刷新该CBrkUserIDLocalID的键值
	///@param	pBrkUserIDLocalID	被刷新的CBrkUserIDLocalID
	///@param	pNewBrkUserIDLocalID	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID, bool updateIndex,bool bNoTransaction);
	
	///删除一个CBrkUserIDLocalID，同时删除其索引
	///@param	pBrkUserIDLocalID	要删除的CBrkUserIDLocalID
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CBrkUserIDLocalID *pBrkUserIDLocalID, bool bNoTransaction);
/*
	///检查某个CBrkUserIDLocalID是否属于本对象工厂
	///@param	pBrkUserIDLocalID	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CBrkUserIDLocalID *pBrkUserIDLocalID);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	
	///基于BrokerIDUserIDLocalID的hash索引
	CHashIndex *pBrokerIDUserIDLocalIDHashIndex;
	
	
	///加入前触发
	///@param	pBrkUserIDLocalID	要加入的BrkUserIDLocalID
	virtual void beforeAdd(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID);
	
	///加入后触发
	///@param	pBrkUserIDLocalID	已经加入的BrkUserIDLocalID
	virtual void afterAdd(CBrkUserIDLocalID *pBrkUserIDLocalID);

	///更新前触发	
	///@param	pBrkUserIDLocalID	被刷新的CBrkUserIDLocalID
	///@param	pNewBrkUserIDLocalID	新的值
	virtual void beforeUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID);
	
	///更新后触发
	///@param	pBrkUserIDLocalID	被刷新的CBrkUserIDLocalID
	virtual void afterUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID);
	
	///删除前触发
	///@param	pBrkUserIDLocalID	要删除的CBrkUserIDLocalID
	virtual void beforeRemove(CBrkUserIDLocalID *pBrkUserIDLocalID);
	
	///确认加入后触发
	///@param	pBrkUserIDLocalID	已经加入的BrkUserIDLocalID
	virtual void commitAdd(CBrkUserIDLocalID *pBrkUserIDLocalID);

	///确认更新后触发
	///@param	pBrkUserIDLocalID	被刷新的CBrkUserIDLocalID
	///@param	poldBrkUserIDLocalID	原来的值
	virtual void commitUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pOldBrkUserIDLocalID);
	
	///确认删除后触发
	///@param	pBrkUserIDLocalID	已经删除的CBrkUserIDLocalID
	virtual void commitRemove(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID);

	///所有相关的触发器
	vector<CBrkUserIDLocalIDActionTrigger *> *pActionTriggers;
	vector<CBrkUserIDLocalIDCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableBrkUserIDLocalID compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionFactory是一个客户合约组持仓表的对象工厂。它包含了一批客户合约组持仓表，
///同时又建立了如下索引，以方便查询：
///使用本对象工厂，可以完成对客户合约组持仓表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrokerClientAndInsGroup，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CPartClientInsGroupPositionFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxPartClientInsGroupPosition，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CPartClientInsGroupPositionFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CPartClientInsGroupPositionFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的PartClientInsGroupPosition
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的PartClientInsGroupPosition，文件名将根据配置文件中的定义PartClientInsGroupPositionCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的PartClientInsGroupPosition
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的PartClientInsGroupPosition，文件名将根据配置文件中的定义PartClientInsGroupPositionCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CPartClientInsGroupPositionResource;

	///将一个CPartClientInsGroupPosition加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pPartClientInsGroupPosition	要加入的PartClientInsGroupPosition
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CPartClientInsGroupPosition *add(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition, CTransaction *pTransaction=NULL);
	
	///刷新该CPartClientInsGroupPosition的值
	///@param	pPartClientInsGroupPosition	被刷新的CPartClientInsGroupPosition
	///@param	pNewPartClientInsGroupPosition	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pPartClientInsGroupPosition	  需要被刷新或者新增的CPartClientInsGroupPosition,等于NULL表示是需要新增的
	///@param	pNewPartClientInsGroupPosition	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CPartClientInsGroupPosition* addOrUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CPartClientInsGroupPosition，同时删除其索引
	///@param	pPartClientInsGroupPosition	要删除的CPartClientInsGroupPosition
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CTransaction *pTransaction=NULL);
	
	///获取某个CPartClientInsGroupPosition
	///@param	pPartClientInsGroupPosition	要读取的CPartClientInsGroupPosition
	///@param	pTragetPartClientInsGroupPosition	存放结果的CPartClientInsGroupPosition
	void retrieve(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pTargetPartClientInsGroupPosition);
	
	///获取第一个CPartClientInsGroupPosition
	///@return	得到的第一个CPartClientInsGroupPosition，如果没有，则返回NULL
	CPartClientInsGroupPosition *getFirst(void);
	
	///获取下一个CPartClientInsGroupPosition
	///@return	得到下一个CPartClientInsGroupPosition，如果没有，则返回NULL
	CPartClientInsGroupPosition *getNext(void);
	
	///结束获取CPartClientInsGroupPosition
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CPartClientInsGroupPositionActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CPartClientInsGroupPositionActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CPartClientInsGroupPositionCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CPartClientInsGroupPositionCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CPartClientInsGroupPosition
	///@param	BrokerID	会员号
	///@param	ClientID	客户号
	///@param	InstrumentGroupID	合约组号
	///@return	找到的CPartClientInsGroupPosition，如果找不到，返回NULL
	CPartClientInsGroupPosition *findByBrokerClientAndInsGroup( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyClientIDType&  ClientID,  const CReadOnlyInstrumentGroupIDType&  InstrumentGroupID);



private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CPartClientInsGroupPosition加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pPartClientInsGroupPosition	要加入的PartClientInsGroupPosition
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CPartClientInsGroupPosition *internalAdd(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition, bool bNoTransaction);
	
	
	///刷新该CPartClientInsGroupPosition的键值
	///@param	pPartClientInsGroupPosition	被刷新的CPartClientInsGroupPosition
	///@param	pNewPartClientInsGroupPosition	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition, bool updateIndex,bool bNoTransaction);
	
	///删除一个CPartClientInsGroupPosition，同时删除其索引
	///@param	pPartClientInsGroupPosition	要删除的CPartClientInsGroupPosition
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CPartClientInsGroupPosition *pPartClientInsGroupPosition, bool bNoTransaction);
/*
	///检查某个CPartClientInsGroupPosition是否属于本对象工厂
	///@param	pPartClientInsGroupPosition	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CPartClientInsGroupPosition *pPartClientInsGroupPosition);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	
	///基于PartClientAndInsGroup的hash索引
	CHashIndex *pPartClientAndInsGroupHashIndex;
	
	
	///加入前触发
	///@param	pPartClientInsGroupPosition	要加入的PartClientInsGroupPosition
	virtual void beforeAdd(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition);
	
	///加入后触发
	///@param	pPartClientInsGroupPosition	已经加入的PartClientInsGroupPosition
	virtual void afterAdd(CPartClientInsGroupPosition *pPartClientInsGroupPosition);

	///更新前触发	
	///@param	pPartClientInsGroupPosition	被刷新的CPartClientInsGroupPosition
	///@param	pNewPartClientInsGroupPosition	新的值
	virtual void beforeUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition);
	
	///更新后触发
	///@param	pPartClientInsGroupPosition	被刷新的CPartClientInsGroupPosition
	virtual void afterUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition);
	
	///删除前触发
	///@param	pPartClientInsGroupPosition	要删除的CPartClientInsGroupPosition
	virtual void beforeRemove(CPartClientInsGroupPosition *pPartClientInsGroupPosition);
	
	///确认加入后触发
	///@param	pPartClientInsGroupPosition	已经加入的PartClientInsGroupPosition
	virtual void commitAdd(CPartClientInsGroupPosition *pPartClientInsGroupPosition);

	///确认更新后触发
	///@param	pPartClientInsGroupPosition	被刷新的CPartClientInsGroupPosition
	///@param	poldPartClientInsGroupPosition	原来的值
	virtual void commitUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pOldPartClientInsGroupPosition);
	
	///确认删除后触发
	///@param	pPartClientInsGroupPosition	已经删除的CPartClientInsGroupPosition
	virtual void commitRemove(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition);

	///所有相关的触发器
	vector<CPartClientInsGroupPositionActionTrigger *> *pActionTriggers;
	vector<CPartClientInsGroupPositionCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteablePartClientInsGroupPosition compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeFactory是一个交易编码组合保证金类型的对象工厂。它包含了一批交易编码组合保证金类型，
///同时又建立了如下索引，以方便查询：
///使用本对象工厂，可以完成对交易编码组合保证金类型的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrokerClientAndInsGroup，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CClientMarginCombTypeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxClientMarginCombType，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CClientMarginCombTypeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CClientMarginCombTypeFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的ClientMarginCombType
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的ClientMarginCombType，文件名将根据配置文件中的定义ClientMarginCombTypeCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的ClientMarginCombType
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的ClientMarginCombType，文件名将根据配置文件中的定义ClientMarginCombTypeCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CClientMarginCombTypeResource;

	///将一个CClientMarginCombType加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pClientMarginCombType	要加入的ClientMarginCombType
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CClientMarginCombType *add(CWriteableClientMarginCombType *pClientMarginCombType, CTransaction *pTransaction=NULL);
	
	///刷新该CClientMarginCombType的值
	///@param	pClientMarginCombType	被刷新的CClientMarginCombType
	///@param	pNewClientMarginCombType	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pClientMarginCombType	  需要被刷新或者新增的CClientMarginCombType,等于NULL表示是需要新增的
	///@param	pNewClientMarginCombType	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CClientMarginCombType* addOrUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CClientMarginCombType，同时删除其索引
	///@param	pClientMarginCombType	要删除的CClientMarginCombType
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CClientMarginCombType *pClientMarginCombType, CTransaction *pTransaction=NULL);
	
	///获取某个CClientMarginCombType
	///@param	pClientMarginCombType	要读取的CClientMarginCombType
	///@param	pTragetClientMarginCombType	存放结果的CClientMarginCombType
	void retrieve(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pTargetClientMarginCombType);
	
	///获取第一个CClientMarginCombType
	///@return	得到的第一个CClientMarginCombType，如果没有，则返回NULL
	CClientMarginCombType *getFirst(void);
	
	///获取下一个CClientMarginCombType
	///@return	得到下一个CClientMarginCombType，如果没有，则返回NULL
	CClientMarginCombType *getNext(void);
	
	///结束获取CClientMarginCombType
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CClientMarginCombTypeActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CClientMarginCombTypeActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CClientMarginCombTypeCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CClientMarginCombTypeCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CClientMarginCombType
	///@param	BrokerID	会员号
	///@param	ClientID	客户号
	///@param	InstrumentGroupID	客户号
	///@return	找到的CClientMarginCombType，如果找不到，返回NULL
	CClientMarginCombType *findByBrokerClientAndInsGroup( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyClientIDType&  ClientID,  const CReadOnlyInstrumentGroupIDType&  InstrumentGroupID);

	///根据主码寻找
	///@param	BrokerID	会员号
	///@param	ClientID	客户号
	///@param	InstrumentGroupID	客户号
	///@return	找到的CClientMarginCombType，如果找不到，返回NULL
	CClientMarginCombType *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyClientIDType&  ClientID,  const CReadOnlyInstrumentGroupIDType&  InstrumentGroupID);
	
	///根据主键寻找CClientMarginCombType
	///@param	pClientMarginCombType	要找的值
	///@return	找到的CClientMarginCombType，如果找不到，返回NULL
	CClientMarginCombType *findByPK(CWriteableClientMarginCombType *pClientMarginCombType);

	///根据主键获取CClientMarginCombType
	///@param	pClientMarginCombType	要获取的值，同时用于存放返回的结果
	///@return	找到的CClientMarginCombType，如果找不到，返回NULL
	bool retrieveByPK(CWriteableClientMarginCombType *pClientMarginCombType);

	///根据主键增加新的CClientMarginCombType
	///@param	pClientMarginCombType	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CClientMarginCombType，如果插入失败，则返回NULL
	CClientMarginCombType *addByPK(CWriteableClientMarginCombType *pClientMarginCombType, CTransaction *pTransaction=NULL);

	///根据主键更新CClientMarginCombType的值
	///@param	pClientMarginCombType	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableClientMarginCombType *pClientMarginCombType, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CClientMarginCombType
	///@param	pClientMarginCombType	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableClientMarginCombType *pClientMarginCombType, CTransaction *pTransaction=NULL);


private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CClientMarginCombType加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pClientMarginCombType	要加入的ClientMarginCombType
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CClientMarginCombType *internalAdd(CWriteableClientMarginCombType *pClientMarginCombType, bool bNoTransaction);
	
	
	///刷新该CClientMarginCombType的键值
	///@param	pClientMarginCombType	被刷新的CClientMarginCombType
	///@param	pNewClientMarginCombType	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType, bool updateIndex,bool bNoTransaction);
	
	///删除一个CClientMarginCombType，同时删除其索引
	///@param	pClientMarginCombType	要删除的CClientMarginCombType
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CClientMarginCombType *pClientMarginCombType, bool bNoTransaction);
/*
	///检查某个CClientMarginCombType是否属于本对象工厂
	///@param	pClientMarginCombType	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CClientMarginCombType *pClientMarginCombType);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	
	///基于ClientAndInsGroup的hash索引
	CHashIndex *pClientAndInsGroupHashIndex;
	
	
	///加入前触发
	///@param	pClientMarginCombType	要加入的ClientMarginCombType
	virtual void beforeAdd(CWriteableClientMarginCombType *pClientMarginCombType);
	
	///加入后触发
	///@param	pClientMarginCombType	已经加入的ClientMarginCombType
	virtual void afterAdd(CClientMarginCombType *pClientMarginCombType);

	///更新前触发	
	///@param	pClientMarginCombType	被刷新的CClientMarginCombType
	///@param	pNewClientMarginCombType	新的值
	virtual void beforeUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType);
	
	///更新后触发
	///@param	pClientMarginCombType	被刷新的CClientMarginCombType
	virtual void afterUpdate(CClientMarginCombType *pClientMarginCombType);
	
	///删除前触发
	///@param	pClientMarginCombType	要删除的CClientMarginCombType
	virtual void beforeRemove(CClientMarginCombType *pClientMarginCombType);
	
	///确认加入后触发
	///@param	pClientMarginCombType	已经加入的ClientMarginCombType
	virtual void commitAdd(CClientMarginCombType *pClientMarginCombType);

	///确认更新后触发
	///@param	pClientMarginCombType	被刷新的CClientMarginCombType
	///@param	poldClientMarginCombType	原来的值
	virtual void commitUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pOldClientMarginCombType);
	
	///确认删除后触发
	///@param	pClientMarginCombType	已经删除的CClientMarginCombType
	virtual void commitRemove(CWriteableClientMarginCombType *pClientMarginCombType);

	///所有相关的触发器
	vector<CClientMarginCombTypeActionTrigger *> *pActionTriggers;
	vector<CClientMarginCombTypeCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableClientMarginCombType compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupFactory是一个合约和合约组关系的对象工厂。它包含了一批合约和合约组关系，
///同时又建立了如下索引，以方便查询：
///使用本对象工厂，可以完成对合约和合约组关系的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrokerInstrumentID，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInstrumentGroupFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxInstrumentGroup，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInstrumentGroupFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CInstrumentGroupFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的InstrumentGroup
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的InstrumentGroup，文件名将根据配置文件中的定义InstrumentGroupCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的InstrumentGroup
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的InstrumentGroup，文件名将根据配置文件中的定义InstrumentGroupCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CInstrumentGroupResource;

	///将一个CInstrumentGroup加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInstrumentGroup	要加入的InstrumentGroup
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInstrumentGroup *add(CWriteableInstrumentGroup *pInstrumentGroup, CTransaction *pTransaction=NULL);
	
	///刷新该CInstrumentGroup的值
	///@param	pInstrumentGroup	被刷新的CInstrumentGroup
	///@param	pNewInstrumentGroup	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pInstrumentGroup	  需要被刷新或者新增的CInstrumentGroup,等于NULL表示是需要新增的
	///@param	pNewInstrumentGroup	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CInstrumentGroup* addOrUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CInstrumentGroup，同时删除其索引
	///@param	pInstrumentGroup	要删除的CInstrumentGroup
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CInstrumentGroup *pInstrumentGroup, CTransaction *pTransaction=NULL);
	
	///获取某个CInstrumentGroup
	///@param	pInstrumentGroup	要读取的CInstrumentGroup
	///@param	pTragetInstrumentGroup	存放结果的CInstrumentGroup
	void retrieve(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pTargetInstrumentGroup);
	
	///获取第一个CInstrumentGroup
	///@return	得到的第一个CInstrumentGroup，如果没有，则返回NULL
	CInstrumentGroup *getFirst(void);
	
	///获取下一个CInstrumentGroup
	///@return	得到下一个CInstrumentGroup，如果没有，则返回NULL
	CInstrumentGroup *getNext(void);
	
	///结束获取CInstrumentGroup
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CInstrumentGroupActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CInstrumentGroupActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CInstrumentGroupCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CInstrumentGroupCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CInstrumentGroup
	///@param	ExchangeID	交易所代码
	///@param	BrokerID	会员号
	///@param	InstrumentID	合约号
	///@return	找到的CInstrumentGroup，如果找不到，返回NULL
	CInstrumentGroup *findByBrokerInstrumentID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInstrumentIDType&  InstrumentID);

	///根据主码寻找
	///@param	ExchangeID	交易所代码
	///@param	BrokerID	会员号
	///@param	InstrumentID	合约号
	///@return	找到的CInstrumentGroup，如果找不到，返回NULL
	CInstrumentGroup *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInstrumentIDType&  InstrumentID);
	
	///根据主键寻找CInstrumentGroup
	///@param	pInstrumentGroup	要找的值
	///@return	找到的CInstrumentGroup，如果找不到，返回NULL
	CInstrumentGroup *findByPK(CWriteableInstrumentGroup *pInstrumentGroup);

	///根据主键获取CInstrumentGroup
	///@param	pInstrumentGroup	要获取的值，同时用于存放返回的结果
	///@return	找到的CInstrumentGroup，如果找不到，返回NULL
	bool retrieveByPK(CWriteableInstrumentGroup *pInstrumentGroup);

	///根据主键增加新的CInstrumentGroup
	///@param	pInstrumentGroup	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CInstrumentGroup，如果插入失败，则返回NULL
	CInstrumentGroup *addByPK(CWriteableInstrumentGroup *pInstrumentGroup, CTransaction *pTransaction=NULL);

	///根据主键更新CInstrumentGroup的值
	///@param	pInstrumentGroup	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableInstrumentGroup *pInstrumentGroup, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CInstrumentGroup
	///@param	pInstrumentGroup	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableInstrumentGroup *pInstrumentGroup, CTransaction *pTransaction=NULL);


private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CInstrumentGroup加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInstrumentGroup	要加入的InstrumentGroup
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInstrumentGroup *internalAdd(CWriteableInstrumentGroup *pInstrumentGroup, bool bNoTransaction);
	
	
	///刷新该CInstrumentGroup的键值
	///@param	pInstrumentGroup	被刷新的CInstrumentGroup
	///@param	pNewInstrumentGroup	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup, bool updateIndex,bool bNoTransaction);
	
	///删除一个CInstrumentGroup，同时删除其索引
	///@param	pInstrumentGroup	要删除的CInstrumentGroup
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CInstrumentGroup *pInstrumentGroup, bool bNoTransaction);
/*
	///检查某个CInstrumentGroup是否属于本对象工厂
	///@param	pInstrumentGroup	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CInstrumentGroup *pInstrumentGroup);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	
	///基于BrokerInstrumentID的hash索引
	CHashIndex *pBrokerInstrumentIDHashIndex;
	
	
	///加入前触发
	///@param	pInstrumentGroup	要加入的InstrumentGroup
	virtual void beforeAdd(CWriteableInstrumentGroup *pInstrumentGroup);
	
	///加入后触发
	///@param	pInstrumentGroup	已经加入的InstrumentGroup
	virtual void afterAdd(CInstrumentGroup *pInstrumentGroup);

	///更新前触发	
	///@param	pInstrumentGroup	被刷新的CInstrumentGroup
	///@param	pNewInstrumentGroup	新的值
	virtual void beforeUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup);
	
	///更新后触发
	///@param	pInstrumentGroup	被刷新的CInstrumentGroup
	virtual void afterUpdate(CInstrumentGroup *pInstrumentGroup);
	
	///删除前触发
	///@param	pInstrumentGroup	要删除的CInstrumentGroup
	virtual void beforeRemove(CInstrumentGroup *pInstrumentGroup);
	
	///确认加入后触发
	///@param	pInstrumentGroup	已经加入的InstrumentGroup
	virtual void commitAdd(CInstrumentGroup *pInstrumentGroup);

	///确认更新后触发
	///@param	pInstrumentGroup	被刷新的CInstrumentGroup
	///@param	poldInstrumentGroup	原来的值
	virtual void commitUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pOldInstrumentGroup);
	
	///确认删除后触发
	///@param	pInstrumentGroup	已经删除的CInstrumentGroup
	virtual void commitRemove(CWriteableInstrumentGroup *pInstrumentGroup);

	///所有相关的触发器
	vector<CInstrumentGroupActionTrigger *> *pActionTriggers;
	vector<CInstrumentGroupCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableInstrumentGroup compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateFactory是一个金交所递延费率表的对象工厂。它包含了一批金交所递延费率表，
///同时又建立了如下索引，以方便查询：
///	TradeDateInstrumentIDIndex
///使用本对象工厂，可以完成对金交所递延费率表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByTradeDateInstrumentIDIndex，唯一找到对象
///		使用startFindAllByInstrumentID，findNextAllByInstrumentID和endFindAllByInstrumentID完成查询操作
///		使用startFindAll，findNextAll和endFindAll完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CSGEDeferRateFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxSGEDeferRate，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CSGEDeferRateFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CSGEDeferRateFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的SGEDeferRate
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的SGEDeferRate，文件名将根据配置文件中的定义SGEDeferRateCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的SGEDeferRate
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的SGEDeferRate，文件名将根据配置文件中的定义SGEDeferRateCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CSGEDeferRateResource;

	///将一个CSGEDeferRate加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pSGEDeferRate	要加入的SGEDeferRate
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CSGEDeferRate *add(CWriteableSGEDeferRate *pSGEDeferRate, CTransaction *pTransaction=NULL);
	
	///刷新该CSGEDeferRate的值
	///@param	pSGEDeferRate	被刷新的CSGEDeferRate
	///@param	pNewSGEDeferRate	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pSGEDeferRate	  需要被刷新或者新增的CSGEDeferRate,等于NULL表示是需要新增的
	///@param	pNewSGEDeferRate	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CSGEDeferRate* addOrUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CSGEDeferRate，同时删除其索引
	///@param	pSGEDeferRate	要删除的CSGEDeferRate
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CSGEDeferRate *pSGEDeferRate, CTransaction *pTransaction=NULL);
	
	///获取某个CSGEDeferRate
	///@param	pSGEDeferRate	要读取的CSGEDeferRate
	///@param	pTragetSGEDeferRate	存放结果的CSGEDeferRate
	void retrieve(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pTargetSGEDeferRate);
	
	///获取第一个CSGEDeferRate
	///@return	得到的第一个CSGEDeferRate，如果没有，则返回NULL
	CSGEDeferRate *getFirst(void);
	
	///获取下一个CSGEDeferRate
	///@return	得到下一个CSGEDeferRate，如果没有，则返回NULL
	CSGEDeferRate *getNext(void);
	
	///结束获取CSGEDeferRate
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CSGEDeferRateActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CSGEDeferRateActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CSGEDeferRateCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CSGEDeferRateCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CSGEDeferRate
	///@param	TradeDate	交易日期
	///@param	InstrumentID	合约代码
	///@return	找到的CSGEDeferRate，如果找不到，返回NULL
	CSGEDeferRate *findByTradeDateInstrumentIDIndex( const CReadOnlyTradingDayType&  TradeDate,  const CReadOnlyInstrumentIDType&  InstrumentID);

	///根据主码寻找
	///@param	TradeDate	交易日期
	///@param	InstrumentID	合约代码
	///@return	找到的CSGEDeferRate，如果找不到，返回NULL
	CSGEDeferRate *findByPK( const CReadOnlyTradingDayType&  TradeDate,  const CReadOnlyInstrumentIDType&  InstrumentID);
	
	///根据主键寻找CSGEDeferRate
	///@param	pSGEDeferRate	要找的值
	///@return	找到的CSGEDeferRate，如果找不到，返回NULL
	CSGEDeferRate *findByPK(CWriteableSGEDeferRate *pSGEDeferRate);

	///根据主键获取CSGEDeferRate
	///@param	pSGEDeferRate	要获取的值，同时用于存放返回的结果
	///@return	找到的CSGEDeferRate，如果找不到，返回NULL
	bool retrieveByPK(CWriteableSGEDeferRate *pSGEDeferRate);

	///根据主键增加新的CSGEDeferRate
	///@param	pSGEDeferRate	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CSGEDeferRate，如果插入失败，则返回NULL
	CSGEDeferRate *addByPK(CWriteableSGEDeferRate *pSGEDeferRate, CTransaction *pTransaction=NULL);

	///根据主键更新CSGEDeferRate的值
	///@param	pSGEDeferRate	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableSGEDeferRate *pSGEDeferRate, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CSGEDeferRate
	///@param	pSGEDeferRate	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableSGEDeferRate *pSGEDeferRate, CTransaction *pTransaction=NULL);


	friend class CSGEDeferRateIteratorAllByInstrumentID;

	///开始寻找CSGEDeferRate
	///@param	InstrumentID	合约代码
	///@return	满足条件的地一个CSGEDeferRate，如果找不到，返回NULL
	CSGEDeferRate *startFindAllByInstrumentID( const CReadOnlyInstrumentIDType& InstrumentID);

	///寻找下一个符合条件的CSGEDeferRate，必须在startFindAllByInstrumentID以后，endFindAllByInstrumentID之前叫用
	///@return	下一个满足条件CSGEDeferRate，如果已经没有一个满足要求了，则返回NULL
	CSGEDeferRate *findNextAllByInstrumentID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAllByInstrumentID(void);

	friend class CSGEDeferRateIteratorAll;

	///开始寻找CSGEDeferRate
	///@return	满足条件的地一个CSGEDeferRate，如果找不到，返回NULL
	CSGEDeferRate *startFindAll();

	///寻找下一个符合条件的CSGEDeferRate，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CSGEDeferRate，如果已经没有一个满足要求了，则返回NULL
	CSGEDeferRate *findNextAll(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAll(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CSGEDeferRate加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pSGEDeferRate	要加入的SGEDeferRate
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CSGEDeferRate *internalAdd(CWriteableSGEDeferRate *pSGEDeferRate, bool bNoTransaction);
	
	
	///刷新该CSGEDeferRate的键值
	///@param	pSGEDeferRate	被刷新的CSGEDeferRate
	///@param	pNewSGEDeferRate	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate, bool updateIndex,bool bNoTransaction);
	
	///删除一个CSGEDeferRate，同时删除其索引
	///@param	pSGEDeferRate	要删除的CSGEDeferRate
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CSGEDeferRate *pSGEDeferRate, bool bNoTransaction);
/*
	///检查某个CSGEDeferRate是否属于本对象工厂
	///@param	pSGEDeferRate	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CSGEDeferRate *pSGEDeferRate);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于TradeDate+InstrumentID的索引
	CAVLTree *pTradeDateInstrumentIDIndex;
	
	
	///按照InstrumentID检索时，存储的查询参数
	CInstrumentIDType queryInstrumentIDInSearchAllByInstrumentID;
	
	///按照InstrumentID检索时，存储最后一次找到的索引节点
	CSGEDeferRate *pLastFoundInSearchAllByInstrumentID;
	///按照检索时，存储的查询参数
	
	///按照检索时，存储最后一次找到的索引节点
	CSGEDeferRate *pLastFoundInSearchAll;
	
	///加入前触发
	///@param	pSGEDeferRate	要加入的SGEDeferRate
	virtual void beforeAdd(CWriteableSGEDeferRate *pSGEDeferRate);
	
	///加入后触发
	///@param	pSGEDeferRate	已经加入的SGEDeferRate
	virtual void afterAdd(CSGEDeferRate *pSGEDeferRate);

	///更新前触发	
	///@param	pSGEDeferRate	被刷新的CSGEDeferRate
	///@param	pNewSGEDeferRate	新的值
	virtual void beforeUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate);
	
	///更新后触发
	///@param	pSGEDeferRate	被刷新的CSGEDeferRate
	virtual void afterUpdate(CSGEDeferRate *pSGEDeferRate);
	
	///删除前触发
	///@param	pSGEDeferRate	要删除的CSGEDeferRate
	virtual void beforeRemove(CSGEDeferRate *pSGEDeferRate);
	
	///确认加入后触发
	///@param	pSGEDeferRate	已经加入的SGEDeferRate
	virtual void commitAdd(CSGEDeferRate *pSGEDeferRate);

	///确认更新后触发
	///@param	pSGEDeferRate	被刷新的CSGEDeferRate
	///@param	poldSGEDeferRate	原来的值
	virtual void commitUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pOldSGEDeferRate);
	
	///确认删除后触发
	///@param	pSGEDeferRate	已经删除的CSGEDeferRate
	virtual void commitRemove(CWriteableSGEDeferRate *pSGEDeferRate);

	///所有相关的触发器
	vector<CSGEDeferRateActionTrigger *> *pActionTriggers;
	vector<CSGEDeferRateCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableSGEDeferRate compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightFactory是一个投资者交易权限表的对象工厂。它包含了一批投资者交易权限表，
///同时又建立了如下索引，以方便查询：
///	BrkExIDInsInvIndex
///使用本对象工厂，可以完成对投资者交易权限表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrkExIDInsInv，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorTradingRightFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxInvestorTradingRight，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorTradingRightFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorTradingRightFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的InvestorTradingRight
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的InvestorTradingRight，文件名将根据配置文件中的定义InvestorTradingRightCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的InvestorTradingRight
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的InvestorTradingRight，文件名将根据配置文件中的定义InvestorTradingRightCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CInvestorTradingRightResource;

	///将一个CInvestorTradingRight加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestorTradingRight	要加入的InvestorTradingRight
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestorTradingRight *add(CWriteableInvestorTradingRight *pInvestorTradingRight, CTransaction *pTransaction=NULL);
	
	///刷新该CInvestorTradingRight的值
	///@param	pInvestorTradingRight	被刷新的CInvestorTradingRight
	///@param	pNewInvestorTradingRight	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pInvestorTradingRight	  需要被刷新或者新增的CInvestorTradingRight,等于NULL表示是需要新增的
	///@param	pNewInvestorTradingRight	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CInvestorTradingRight* addOrUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CInvestorTradingRight，同时删除其索引
	///@param	pInvestorTradingRight	要删除的CInvestorTradingRight
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CInvestorTradingRight *pInvestorTradingRight, CTransaction *pTransaction=NULL);
	
	///获取某个CInvestorTradingRight
	///@param	pInvestorTradingRight	要读取的CInvestorTradingRight
	///@param	pTragetInvestorTradingRight	存放结果的CInvestorTradingRight
	void retrieve(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pTargetInvestorTradingRight);
	
	///获取第一个CInvestorTradingRight
	///@return	得到的第一个CInvestorTradingRight，如果没有，则返回NULL
	CInvestorTradingRight *getFirst(void);
	
	///获取下一个CInvestorTradingRight
	///@return	得到下一个CInvestorTradingRight，如果没有，则返回NULL
	CInvestorTradingRight *getNext(void);
	
	///结束获取CInvestorTradingRight
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CInvestorTradingRightActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CInvestorTradingRightActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CInvestorTradingRightCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CInvestorTradingRightCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CInvestorTradingRight
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约编号
	///@param	InvestorID	投资者代码
	///@param	ProductClass	产品类型
	///@return	找到的CInvestorTradingRight，如果找不到，返回NULL
	CInvestorTradingRight *findByBrkExIDInsInv( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyProductClassType&  ProductClass);

	///根据主码寻找
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约编号
	///@param	InvestorID	投资者代码
	///@param	ProductClass	产品类型
	///@return	找到的CInvestorTradingRight，如果找不到，返回NULL
	CInvestorTradingRight *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyProductClassType&  ProductClass);
	
	///根据主键寻找CInvestorTradingRight
	///@param	pInvestorTradingRight	要找的值
	///@return	找到的CInvestorTradingRight，如果找不到，返回NULL
	CInvestorTradingRight *findByPK(CWriteableInvestorTradingRight *pInvestorTradingRight);

	///根据主键获取CInvestorTradingRight
	///@param	pInvestorTradingRight	要获取的值，同时用于存放返回的结果
	///@return	找到的CInvestorTradingRight，如果找不到，返回NULL
	bool retrieveByPK(CWriteableInvestorTradingRight *pInvestorTradingRight);

	///根据主键增加新的CInvestorTradingRight
	///@param	pInvestorTradingRight	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CInvestorTradingRight，如果插入失败，则返回NULL
	CInvestorTradingRight *addByPK(CWriteableInvestorTradingRight *pInvestorTradingRight, CTransaction *pTransaction=NULL);

	///根据主键更新CInvestorTradingRight的值
	///@param	pInvestorTradingRight	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableInvestorTradingRight *pInvestorTradingRight, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CInvestorTradingRight
	///@param	pInvestorTradingRight	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableInvestorTradingRight *pInvestorTradingRight, CTransaction *pTransaction=NULL);


private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CInvestorTradingRight加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestorTradingRight	要加入的InvestorTradingRight
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestorTradingRight *internalAdd(CWriteableInvestorTradingRight *pInvestorTradingRight, bool bNoTransaction);
	
	
	///刷新该CInvestorTradingRight的键值
	///@param	pInvestorTradingRight	被刷新的CInvestorTradingRight
	///@param	pNewInvestorTradingRight	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight, bool updateIndex,bool bNoTransaction);
	
	///删除一个CInvestorTradingRight，同时删除其索引
	///@param	pInvestorTradingRight	要删除的CInvestorTradingRight
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CInvestorTradingRight *pInvestorTradingRight, bool bNoTransaction);
/*
	///检查某个CInvestorTradingRight是否属于本对象工厂
	///@param	pInvestorTradingRight	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CInvestorTradingRight *pInvestorTradingRight);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于BrokerID+ExchangeID+InstrumentID+InvestorID+ProductClass的索引
	CAVLTree *pBrkExIDInsInvIndex;
	
	
	
	///加入前触发
	///@param	pInvestorTradingRight	要加入的InvestorTradingRight
	virtual void beforeAdd(CWriteableInvestorTradingRight *pInvestorTradingRight);
	
	///加入后触发
	///@param	pInvestorTradingRight	已经加入的InvestorTradingRight
	virtual void afterAdd(CInvestorTradingRight *pInvestorTradingRight);

	///更新前触发	
	///@param	pInvestorTradingRight	被刷新的CInvestorTradingRight
	///@param	pNewInvestorTradingRight	新的值
	virtual void beforeUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight);
	
	///更新后触发
	///@param	pInvestorTradingRight	被刷新的CInvestorTradingRight
	virtual void afterUpdate(CInvestorTradingRight *pInvestorTradingRight);
	
	///删除前触发
	///@param	pInvestorTradingRight	要删除的CInvestorTradingRight
	virtual void beforeRemove(CInvestorTradingRight *pInvestorTradingRight);
	
	///确认加入后触发
	///@param	pInvestorTradingRight	已经加入的InvestorTradingRight
	virtual void commitAdd(CInvestorTradingRight *pInvestorTradingRight);

	///确认更新后触发
	///@param	pInvestorTradingRight	被刷新的CInvestorTradingRight
	///@param	poldInvestorTradingRight	原来的值
	virtual void commitUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pOldInvestorTradingRight);
	
	///确认删除后触发
	///@param	pInvestorTradingRight	已经删除的CInvestorTradingRight
	virtual void commitRemove(CWriteableInvestorTradingRight *pInvestorTradingRight);

	///所有相关的触发器
	vector<CInvestorTradingRightActionTrigger *> *pActionTriggers;
	vector<CInvestorTradingRightCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableInvestorTradingRight compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CUserIPFactory是一个交易员IP地址的对象工厂。它包含了一批交易员IP地址，
///同时又建立了如下索引，以方便查询：
///	UserIPMaskIndex
///使用本对象工厂，可以完成对交易员IP地址的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用startFindByUserID，findNextByUserID和endFindByUserID完成查询操作
///		使用findByUserIPAndMask，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CUserIPFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxUserIP，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CUserIPFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CUserIPFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的UserIP
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的UserIP，文件名将根据配置文件中的定义UserIPCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的UserIP
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的UserIP，文件名将根据配置文件中的定义UserIPCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CUserIPResource;

	///将一个CUserIP加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pUserIP	要加入的UserIP
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CUserIP *add(CWriteableUserIP *pUserIP, CTransaction *pTransaction=NULL);
	
	///刷新该CUserIP的值
	///@param	pUserIP	被刷新的CUserIP
	///@param	pNewUserIP	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pUserIP	  需要被刷新或者新增的CUserIP,等于NULL表示是需要新增的
	///@param	pNewUserIP	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CUserIP* addOrUpdate(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CUserIP，同时删除其索引
	///@param	pUserIP	要删除的CUserIP
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CUserIP *pUserIP, CTransaction *pTransaction=NULL);
	
	///获取某个CUserIP
	///@param	pUserIP	要读取的CUserIP
	///@param	pTragetUserIP	存放结果的CUserIP
	void retrieve(CUserIP *pUserIP, CWriteableUserIP *pTargetUserIP);
	
	///获取第一个CUserIP
	///@return	得到的第一个CUserIP，如果没有，则返回NULL
	CUserIP *getFirst(void);
	
	///获取下一个CUserIP
	///@return	得到下一个CUserIP，如果没有，则返回NULL
	CUserIP *getNext(void);
	
	///结束获取CUserIP
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CUserIPActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CUserIPActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CUserIPCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CUserIPCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	friend class CUserIPIteratorByUserID;

	///开始寻找CUserIP
	///@param	BrokerID	经纪公司代码
	///@param	UserID	用户编号
	///@return	满足条件的地一个CUserIP，如果找不到，返回NULL
	CUserIP *startFindByUserID( const CReadOnlyBrokerIDType& BrokerID,  const CReadOnlyUserIDType& UserID);

	///寻找下一个符合条件的CUserIP，必须在startFindByUserID以后，endFindByUserID之前叫用
	///@return	下一个满足条件CUserIP，如果已经没有一个满足要求了，则返回NULL
	CUserIP *findNextByUserID(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindByUserID(void);

	///寻找CUserIP
	///@param	BrokerID	经纪公司代码
	///@param	UserID	用户编号
	///@param	IPAddress	IP地址
	///@param	IPMask	IP地址掩码
	///@return	找到的CUserIP，如果找不到，返回NULL
	CUserIP *findByUserIPAndMask( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyIPAddressType&  IPAddress,  const CReadOnlyIPAddressType&  IPMask);

	///根据主码寻找
	///@param	BrokerID	经纪公司代码
	///@param	UserID	用户编号
	///@param	IPAddress	IP地址
	///@param	IPMask	IP地址掩码
	///@return	找到的CUserIP，如果找不到，返回NULL
	CUserIP *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyIPAddressType&  IPAddress,  const CReadOnlyIPAddressType&  IPMask);
	
	///根据主键寻找CUserIP
	///@param	pUserIP	要找的值
	///@return	找到的CUserIP，如果找不到，返回NULL
	CUserIP *findByPK(CWriteableUserIP *pUserIP);

	///根据主键获取CUserIP
	///@param	pUserIP	要获取的值，同时用于存放返回的结果
	///@return	找到的CUserIP，如果找不到，返回NULL
	bool retrieveByPK(CWriteableUserIP *pUserIP);

	///根据主键增加新的CUserIP
	///@param	pUserIP	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CUserIP，如果插入失败，则返回NULL
	CUserIP *addByPK(CWriteableUserIP *pUserIP, CTransaction *pTransaction=NULL);

	///根据主键更新CUserIP的值
	///@param	pUserIP	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableUserIP *pUserIP, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CUserIP
	///@param	pUserIP	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableUserIP *pUserIP, CTransaction *pTransaction=NULL);


private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CUserIP加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pUserIP	要加入的UserIP
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CUserIP *internalAdd(CWriteableUserIP *pUserIP, bool bNoTransaction);
	
	
	///刷新该CUserIP的键值
	///@param	pUserIP	被刷新的CUserIP
	///@param	pNewUserIP	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP, bool updateIndex,bool bNoTransaction);
	
	///删除一个CUserIP，同时删除其索引
	///@param	pUserIP	要删除的CUserIP
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CUserIP *pUserIP, bool bNoTransaction);
/*
	///检查某个CUserIP是否属于本对象工厂
	///@param	pUserIP	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CUserIP *pUserIP);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于BrokerID+UserID+IPAddress+IPMask的索引
	CAVLTree *pUserIPMaskIndex;
	
	
	///按照BrokerID，UserID检索时，存储的查询参数
	CBrokerIDType queryBrokerIDInSearchByUserID;
	CUserIDType queryUserIDInSearchByUserID;
	
	///按照BrokerID，UserID检索时，存储最后一次找到的索引节点
	CAVLNode *pLastFoundInSearchByUserID;
	
	///加入前触发
	///@param	pUserIP	要加入的UserIP
	virtual void beforeAdd(CWriteableUserIP *pUserIP);
	
	///加入后触发
	///@param	pUserIP	已经加入的UserIP
	virtual void afterAdd(CUserIP *pUserIP);

	///更新前触发	
	///@param	pUserIP	被刷新的CUserIP
	///@param	pNewUserIP	新的值
	virtual void beforeUpdate(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP);
	
	///更新后触发
	///@param	pUserIP	被刷新的CUserIP
	virtual void afterUpdate(CUserIP *pUserIP);
	
	///删除前触发
	///@param	pUserIP	要删除的CUserIP
	virtual void beforeRemove(CUserIP *pUserIP);
	
	///确认加入后触发
	///@param	pUserIP	已经加入的UserIP
	virtual void commitAdd(CUserIP *pUserIP);

	///确认更新后触发
	///@param	pUserIP	被刷新的CUserIP
	///@param	poldUserIP	原来的值
	virtual void commitUpdate(CUserIP *pUserIP, CWriteableUserIP *pOldUserIP);
	
	///确认删除后触发
	///@param	pUserIP	已经删除的CUserIP
	virtual void commitRemove(CWriteableUserIP *pUserIP);

	///所有相关的触发器
	vector<CUserIPActionTrigger *> *pActionTriggers;
	vector<CUserIPCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableUserIP compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeFactory是一个客户期权手续费率表的对象工厂。它包含了一批客户期权手续费率表，
///同时又建立了如下索引，以方便查询：
///使用本对象工厂，可以完成对客户期权手续费率表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByBrkIDExIDIstIDVstID，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorOptionFeeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxInvestorOptionFee，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CInvestorOptionFeeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorOptionFeeFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的InvestorOptionFee
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的InvestorOptionFee，文件名将根据配置文件中的定义InvestorOptionFeeCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的InvestorOptionFee
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的InvestorOptionFee，文件名将根据配置文件中的定义InvestorOptionFeeCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CInvestorOptionFeeResource;

	///将一个CInvestorOptionFee加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestorOptionFee	要加入的InvestorOptionFee
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestorOptionFee *add(CWriteableInvestorOptionFee *pInvestorOptionFee, CTransaction *pTransaction=NULL);
	
	///刷新该CInvestorOptionFee的值
	///@param	pInvestorOptionFee	被刷新的CInvestorOptionFee
	///@param	pNewInvestorOptionFee	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pInvestorOptionFee	  需要被刷新或者新增的CInvestorOptionFee,等于NULL表示是需要新增的
	///@param	pNewInvestorOptionFee	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CInvestorOptionFee* addOrUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CInvestorOptionFee，同时删除其索引
	///@param	pInvestorOptionFee	要删除的CInvestorOptionFee
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CInvestorOptionFee *pInvestorOptionFee, CTransaction *pTransaction=NULL);
	
	///获取某个CInvestorOptionFee
	///@param	pInvestorOptionFee	要读取的CInvestorOptionFee
	///@param	pTragetInvestorOptionFee	存放结果的CInvestorOptionFee
	void retrieve(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pTargetInvestorOptionFee);
	
	///获取第一个CInvestorOptionFee
	///@return	得到的第一个CInvestorOptionFee，如果没有，则返回NULL
	CInvestorOptionFee *getFirst(void);
	
	///获取下一个CInvestorOptionFee
	///@return	得到下一个CInvestorOptionFee，如果没有，则返回NULL
	CInvestorOptionFee *getNext(void);
	
	///结束获取CInvestorOptionFee
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CInvestorOptionFeeActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CInvestorOptionFeeActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CInvestorOptionFeeCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CInvestorOptionFeeCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CInvestorOptionFee
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约代码
	///@param	InvestorID	投资者号
	///@return	找到的CInvestorOptionFee，如果找不到，返回NULL
	CInvestorOptionFee *findByBrkIDExIDIstIDVstID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID);

	///根据主码寻找
	///@param	BrokerID	经纪公司代码
	///@param	ExchangeID	交易所代码
	///@param	InstrumentID	合约代码
	///@param	InvestorID	投资者号
	///@return	找到的CInvestorOptionFee，如果找不到，返回NULL
	CInvestorOptionFee *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID);
	
	///根据主键寻找CInvestorOptionFee
	///@param	pInvestorOptionFee	要找的值
	///@return	找到的CInvestorOptionFee，如果找不到，返回NULL
	CInvestorOptionFee *findByPK(CWriteableInvestorOptionFee *pInvestorOptionFee);

	///根据主键获取CInvestorOptionFee
	///@param	pInvestorOptionFee	要获取的值，同时用于存放返回的结果
	///@return	找到的CInvestorOptionFee，如果找不到，返回NULL
	bool retrieveByPK(CWriteableInvestorOptionFee *pInvestorOptionFee);

	///根据主键增加新的CInvestorOptionFee
	///@param	pInvestorOptionFee	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CInvestorOptionFee，如果插入失败，则返回NULL
	CInvestorOptionFee *addByPK(CWriteableInvestorOptionFee *pInvestorOptionFee, CTransaction *pTransaction=NULL);

	///根据主键更新CInvestorOptionFee的值
	///@param	pInvestorOptionFee	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableInvestorOptionFee *pInvestorOptionFee, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CInvestorOptionFee
	///@param	pInvestorOptionFee	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableInvestorOptionFee *pInvestorOptionFee, CTransaction *pTransaction=NULL);


private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CInvestorOptionFee加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pInvestorOptionFee	要加入的InvestorOptionFee
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CInvestorOptionFee *internalAdd(CWriteableInvestorOptionFee *pInvestorOptionFee, bool bNoTransaction);
	
	
	///刷新该CInvestorOptionFee的键值
	///@param	pInvestorOptionFee	被刷新的CInvestorOptionFee
	///@param	pNewInvestorOptionFee	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee, bool updateIndex,bool bNoTransaction);
	
	///删除一个CInvestorOptionFee，同时删除其索引
	///@param	pInvestorOptionFee	要删除的CInvestorOptionFee
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CInvestorOptionFee *pInvestorOptionFee, bool bNoTransaction);
/*
	///检查某个CInvestorOptionFee是否属于本对象工厂
	///@param	pInvestorOptionFee	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CInvestorOptionFee *pInvestorOptionFee);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	
	///基于BrkIDExIDIstIDVstID的hash索引
	CHashIndex *pBrkIDExIDIstIDVstIDHashIndex;
	
	
	///加入前触发
	///@param	pInvestorOptionFee	要加入的InvestorOptionFee
	virtual void beforeAdd(CWriteableInvestorOptionFee *pInvestorOptionFee);
	
	///加入后触发
	///@param	pInvestorOptionFee	已经加入的InvestorOptionFee
	virtual void afterAdd(CInvestorOptionFee *pInvestorOptionFee);

	///更新前触发	
	///@param	pInvestorOptionFee	被刷新的CInvestorOptionFee
	///@param	pNewInvestorOptionFee	新的值
	virtual void beforeUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee);
	
	///更新后触发
	///@param	pInvestorOptionFee	被刷新的CInvestorOptionFee
	virtual void afterUpdate(CInvestorOptionFee *pInvestorOptionFee);
	
	///删除前触发
	///@param	pInvestorOptionFee	要删除的CInvestorOptionFee
	virtual void beforeRemove(CInvestorOptionFee *pInvestorOptionFee);
	
	///确认加入后触发
	///@param	pInvestorOptionFee	已经加入的InvestorOptionFee
	virtual void commitAdd(CInvestorOptionFee *pInvestorOptionFee);

	///确认更新后触发
	///@param	pInvestorOptionFee	被刷新的CInvestorOptionFee
	///@param	poldInvestorOptionFee	原来的值
	virtual void commitUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pOldInvestorOptionFee);
	
	///确认删除后触发
	///@param	pInvestorOptionFee	已经删除的CInvestorOptionFee
	virtual void commitRemove(CWriteableInvestorOptionFee *pInvestorOptionFee);

	///所有相关的触发器
	vector<CInvestorOptionFeeActionTrigger *> *pActionTriggers;
	vector<CInvestorOptionFeeCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableInvestorOptionFee compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataFactory是一个实时行情表的对象工厂。它包含了一批实时行情表，
///同时又建立了如下索引，以方便查询：
///	ExchangeIDAndInstrumentIDIndex
///使用本对象工厂，可以完成对实时行情表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findByExchangeIDAndInstrumentID，唯一找到对象
///		使用startFindAll，findNextAll和endFindAll完成查询操作
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CMarketDataFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxMarketData，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CMarketDataFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CMarketDataFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的MarketData
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的MarketData，文件名将根据配置文件中的定义MarketDataCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的MarketData
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的MarketData，文件名将根据配置文件中的定义MarketDataCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CMarketDataResource;

	///将一个CMarketData加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pMarketData	要加入的MarketData
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CMarketData *add(CWriteableMarketData *pMarketData, CTransaction *pTransaction=NULL);
	
	///刷新该CMarketData的值
	///@param	pMarketData	被刷新的CMarketData
	///@param	pNewMarketData	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pMarketData	  需要被刷新或者新增的CMarketData,等于NULL表示是需要新增的
	///@param	pNewMarketData	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CMarketData* addOrUpdate(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CMarketData，同时删除其索引
	///@param	pMarketData	要删除的CMarketData
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CMarketData *pMarketData, CTransaction *pTransaction=NULL);
	
	///获取某个CMarketData
	///@param	pMarketData	要读取的CMarketData
	///@param	pTragetMarketData	存放结果的CMarketData
	void retrieve(CMarketData *pMarketData, CWriteableMarketData *pTargetMarketData);
	
	///获取第一个CMarketData
	///@return	得到的第一个CMarketData，如果没有，则返回NULL
	CMarketData *getFirst(void);
	
	///获取下一个CMarketData
	///@return	得到下一个CMarketData，如果没有，则返回NULL
	CMarketData *getNext(void);
	
	///结束获取CMarketData
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CMarketDataActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CMarketDataActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CMarketDataCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CMarketDataCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CMarketData
	///@param	ExchangeID	交易所编号
	///@param	InstrumentID	合约编号
	///@return	找到的CMarketData，如果找不到，返回NULL
	CMarketData *findByExchangeIDAndInstrumentID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID);

	///根据主码寻找
	///@param	ExchangeID	交易所编号
	///@param	InstrumentID	合约编号
	///@return	找到的CMarketData，如果找不到，返回NULL
	CMarketData *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID);
	
	///根据主键寻找CMarketData
	///@param	pMarketData	要找的值
	///@return	找到的CMarketData，如果找不到，返回NULL
	CMarketData *findByPK(CWriteableMarketData *pMarketData);

	///根据主键获取CMarketData
	///@param	pMarketData	要获取的值，同时用于存放返回的结果
	///@return	找到的CMarketData，如果找不到，返回NULL
	bool retrieveByPK(CWriteableMarketData *pMarketData);

	///根据主键增加新的CMarketData
	///@param	pMarketData	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CMarketData，如果插入失败，则返回NULL
	CMarketData *addByPK(CWriteableMarketData *pMarketData, CTransaction *pTransaction=NULL);

	///根据主键更新CMarketData的值
	///@param	pMarketData	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableMarketData *pMarketData, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CMarketData
	///@param	pMarketData	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableMarketData *pMarketData, CTransaction *pTransaction=NULL);


	friend class CMarketDataIteratorAll;

	///开始寻找CMarketData
	///@return	满足条件的地一个CMarketData，如果找不到，返回NULL
	CMarketData *startFindAll();

	///寻找下一个符合条件的CMarketData，必须在startFindAll以后，endFindAll之前叫用
	///@return	下一个满足条件CMarketData，如果已经没有一个满足要求了，则返回NULL
	CMarketData *findNextAll(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFindAll(void);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CMarketData加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pMarketData	要加入的MarketData
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CMarketData *internalAdd(CWriteableMarketData *pMarketData, bool bNoTransaction);
	
	
	///刷新该CMarketData的键值
	///@param	pMarketData	被刷新的CMarketData
	///@param	pNewMarketData	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData, bool updateIndex,bool bNoTransaction);
	
	///删除一个CMarketData，同时删除其索引
	///@param	pMarketData	要删除的CMarketData
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CMarketData *pMarketData, bool bNoTransaction);
/*
	///检查某个CMarketData是否属于本对象工厂
	///@param	pMarketData	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CMarketData *pMarketData);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于ExchangeID+InstrumentID的索引
	CAVLTree *pExchangeIDAndInstrumentIDIndex;
	
	
	///按照检索时，存储的查询参数
	
	///按照检索时，存储最后一次找到的索引节点
	CMarketData *pLastFoundInSearchAll;
	
	///加入前触发
	///@param	pMarketData	要加入的MarketData
	virtual void beforeAdd(CWriteableMarketData *pMarketData);
	
	///加入后触发
	///@param	pMarketData	已经加入的MarketData
	virtual void afterAdd(CMarketData *pMarketData);

	///更新前触发	
	///@param	pMarketData	被刷新的CMarketData
	///@param	pNewMarketData	新的值
	virtual void beforeUpdate(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData);
	
	///更新后触发
	///@param	pMarketData	被刷新的CMarketData
	virtual void afterUpdate(CMarketData *pMarketData);
	
	///删除前触发
	///@param	pMarketData	要删除的CMarketData
	virtual void beforeRemove(CMarketData *pMarketData);
	
	///确认加入后触发
	///@param	pMarketData	已经加入的MarketData
	virtual void commitAdd(CMarketData *pMarketData);

	///确认更新后触发
	///@param	pMarketData	被刷新的CMarketData
	///@param	poldMarketData	原来的值
	virtual void commitUpdate(CMarketData *pMarketData, CWriteableMarketData *pOldMarketData);
	
	///确认删除后触发
	///@param	pMarketData	已经删除的CMarketData
	virtual void commitRemove(CWriteableMarketData *pMarketData);

	///所有相关的触发器
	vector<CMarketDataActionTrigger *> *pActionTriggers;
	vector<CMarketDataCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableMarketData compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayFactory是一个委托延迟表的对象工厂。它包含了一批委托延迟表，
///同时又建立了如下索引，以方便查询：
///使用本对象工厂，可以完成对委托延迟表的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	COrderDelayFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxOrderDelay，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	COrderDelayFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~COrderDelayFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的OrderDelay
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的OrderDelay，文件名将根据配置文件中的定义OrderDelayCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的OrderDelay
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的OrderDelay，文件名将根据配置文件中的定义OrderDelayCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class COrderDelayResource;

	///将一个COrderDelay加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pOrderDelay	要加入的OrderDelay
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	COrderDelay *add(CWriteableOrderDelay *pOrderDelay, CTransaction *pTransaction=NULL);
	
	///刷新该COrderDelay的值
	///@param	pOrderDelay	被刷新的COrderDelay
	///@param	pNewOrderDelay	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pOrderDelay	  需要被刷新或者新增的COrderDelay,等于NULL表示是需要新增的
	///@param	pNewOrderDelay	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	COrderDelay* addOrUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个COrderDelay，同时删除其索引
	///@param	pOrderDelay	要删除的COrderDelay
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(COrderDelay *pOrderDelay, CTransaction *pTransaction=NULL);
	
	///获取某个COrderDelay
	///@param	pOrderDelay	要读取的COrderDelay
	///@param	pTragetOrderDelay	存放结果的COrderDelay
	void retrieve(COrderDelay *pOrderDelay, CWriteableOrderDelay *pTargetOrderDelay);
	
	///获取第一个COrderDelay
	///@return	得到的第一个COrderDelay，如果没有，则返回NULL
	COrderDelay *getFirst(void);
	
	///获取下一个COrderDelay
	///@return	得到下一个COrderDelay，如果没有，则返回NULL
	COrderDelay *getNext(void);
	
	///结束获取COrderDelay
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(COrderDelayActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(COrderDelayActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(COrderDelayCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(COrderDelayCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个COrderDelay加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pOrderDelay	要加入的OrderDelay
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	COrderDelay *internalAdd(CWriteableOrderDelay *pOrderDelay, bool bNoTransaction);
	
	
	///刷新该COrderDelay的键值
	///@param	pOrderDelay	被刷新的COrderDelay
	///@param	pNewOrderDelay	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay, bool updateIndex,bool bNoTransaction);
	
	///删除一个COrderDelay，同时删除其索引
	///@param	pOrderDelay	要删除的COrderDelay
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(COrderDelay *pOrderDelay, bool bNoTransaction);
/*
	///检查某个COrderDelay是否属于本对象工厂
	///@param	pOrderDelay	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(COrderDelay *pOrderDelay);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	
	
	
	///加入前触发
	///@param	pOrderDelay	要加入的OrderDelay
	virtual void beforeAdd(CWriteableOrderDelay *pOrderDelay);
	
	///加入后触发
	///@param	pOrderDelay	已经加入的OrderDelay
	virtual void afterAdd(COrderDelay *pOrderDelay);

	///更新前触发	
	///@param	pOrderDelay	被刷新的COrderDelay
	///@param	pNewOrderDelay	新的值
	virtual void beforeUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay);
	
	///更新后触发
	///@param	pOrderDelay	被刷新的COrderDelay
	virtual void afterUpdate(COrderDelay *pOrderDelay);
	
	///删除前触发
	///@param	pOrderDelay	要删除的COrderDelay
	virtual void beforeRemove(COrderDelay *pOrderDelay);
	
	///确认加入后触发
	///@param	pOrderDelay	已经加入的OrderDelay
	virtual void commitAdd(COrderDelay *pOrderDelay);

	///确认更新后触发
	///@param	pOrderDelay	被刷新的COrderDelay
	///@param	poldOrderDelay	原来的值
	virtual void commitUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pOldOrderDelay);
	
	///确认删除后触发
	///@param	pOrderDelay	已经删除的COrderDelay
	virtual void commitRemove(CWriteableOrderDelay *pOrderDelay);

	///所有相关的触发器
	vector<COrderDelayActionTrigger *> *pActionTriggers;
	vector<COrderDelayCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableOrderDelay compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoFactory是一个QDP系统信息的对象工厂。它包含了一批QDP系统信息，
///同时又建立了如下索引，以方便查询：
///	SystemIDIndex
///使用本对象工厂，可以完成对QDP系统信息的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
///		使用findBySystemID，唯一找到对象
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoFactory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CSystemInfoFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义MaxSystemInfo，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	CSystemInfoFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CSystemInfoFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的SystemInfo
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的SystemInfo，文件名将根据配置文件中的定义SystemInfoCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的SystemInfo
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的SystemInfo，文件名将根据配置文件中的定义SystemInfoCSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class CSystemInfoResource;

	///将一个CSystemInfo加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pSystemInfo	要加入的SystemInfo
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CSystemInfo *add(CWriteableSystemInfo *pSystemInfo, CTransaction *pTransaction=NULL);
	
	///刷新该CSystemInfo的值
	///@param	pSystemInfo	被刷新的CSystemInfo
	///@param	pNewSystemInfo	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	pSystemInfo	  需要被刷新或者新增的CSystemInfo,等于NULL表示是需要新增的
	///@param	pNewSystemInfo	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	CSystemInfo* addOrUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个CSystemInfo，同时删除其索引
	///@param	pSystemInfo	要删除的CSystemInfo
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(CSystemInfo *pSystemInfo, CTransaction *pTransaction=NULL);
	
	///获取某个CSystemInfo
	///@param	pSystemInfo	要读取的CSystemInfo
	///@param	pTragetSystemInfo	存放结果的CSystemInfo
	void retrieve(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pTargetSystemInfo);
	
	///获取第一个CSystemInfo
	///@return	得到的第一个CSystemInfo，如果没有，则返回NULL
	CSystemInfo *getFirst(void);
	
	///获取下一个CSystemInfo
	///@return	得到下一个CSystemInfo，如果没有，则返回NULL
	CSystemInfo *getNext(void);
	
	///结束获取CSystemInfo
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(CSystemInfoActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(CSystemInfoActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(CSystemInfoCommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(CSystemInfoCommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

	///寻找CSystemInfo
	///@param	SystemID	交易所编号
	///@return	找到的CSystemInfo，如果找不到，返回NULL
	CSystemInfo *findBySystemID( const CReadOnlySystemIDType&  SystemID);

	///根据主码寻找
	///@param	SystemID	交易所编号
	///@return	找到的CSystemInfo，如果找不到，返回NULL
	CSystemInfo *findByPK( const CReadOnlySystemIDType&  SystemID);
	
	///根据主键寻找CSystemInfo
	///@param	pSystemInfo	要找的值
	///@return	找到的CSystemInfo，如果找不到，返回NULL
	CSystemInfo *findByPK(CWriteableSystemInfo *pSystemInfo);

	///根据主键获取CSystemInfo
	///@param	pSystemInfo	要获取的值，同时用于存放返回的结果
	///@return	找到的CSystemInfo，如果找不到，返回NULL
	bool retrieveByPK(CWriteableSystemInfo *pSystemInfo);

	///根据主键增加新的CSystemInfo
	///@param	pSystemInfo	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的CSystemInfo，如果插入失败，则返回NULL
	CSystemInfo *addByPK(CWriteableSystemInfo *pSystemInfo, CTransaction *pTransaction=NULL);

	///根据主键更新CSystemInfo的值
	///@param	pSystemInfo	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteableSystemInfo *pSystemInfo, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除CSystemInfo
	///@param	pSystemInfo	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteableSystemInfo *pSystemInfo, CTransaction *pTransaction=NULL);


private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个CSystemInfo加入到该对象工厂，实质上是完成修改索引的工作
	///@param	pSystemInfo	要加入的SystemInfo
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	CSystemInfo *internalAdd(CWriteableSystemInfo *pSystemInfo, bool bNoTransaction);
	
	
	///刷新该CSystemInfo的键值
	///@param	pSystemInfo	被刷新的CSystemInfo
	///@param	pNewSystemInfo	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo, bool updateIndex,bool bNoTransaction);
	
	///删除一个CSystemInfo，同时删除其索引
	///@param	pSystemInfo	要删除的CSystemInfo
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(CSystemInfo *pSystemInfo, bool bNoTransaction);
/*
	///检查某个CSystemInfo是否属于本对象工厂
	///@param	pSystemInfo	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(CSystemInfo *pSystemInfo);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	///基于SystemID的索引
	CAVLTree *pSystemIDIndex;
	
	
	
	///加入前触发
	///@param	pSystemInfo	要加入的SystemInfo
	virtual void beforeAdd(CWriteableSystemInfo *pSystemInfo);
	
	///加入后触发
	///@param	pSystemInfo	已经加入的SystemInfo
	virtual void afterAdd(CSystemInfo *pSystemInfo);

	///更新前触发	
	///@param	pSystemInfo	被刷新的CSystemInfo
	///@param	pNewSystemInfo	新的值
	virtual void beforeUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo);
	
	///更新后触发
	///@param	pSystemInfo	被刷新的CSystemInfo
	virtual void afterUpdate(CSystemInfo *pSystemInfo);
	
	///删除前触发
	///@param	pSystemInfo	要删除的CSystemInfo
	virtual void beforeRemove(CSystemInfo *pSystemInfo);
	
	///确认加入后触发
	///@param	pSystemInfo	已经加入的SystemInfo
	virtual void commitAdd(CSystemInfo *pSystemInfo);

	///确认更新后触发
	///@param	pSystemInfo	被刷新的CSystemInfo
	///@param	poldSystemInfo	原来的值
	virtual void commitUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pOldSystemInfo);
	
	///确认删除后触发
	///@param	pSystemInfo	已经删除的CSystemInfo
	virtual void commitRemove(CWriteableSystemInfo *pSystemInfo);

	///所有相关的触发器
	vector<CSystemInfoActionTrigger *> *pActionTriggers;
	vector<CSystemInfoCommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteableSystemInfo compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

#endif
