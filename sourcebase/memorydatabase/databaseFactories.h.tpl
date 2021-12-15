!!include function.tpl!!
!!enter system!!
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

!!travel tables!!
class C!!@name!!Factory;
class C!!@name!!Resource;
!!next!!

!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!command resetEntityMap();!!
!!travel fields!!
!!command addEntity(@name,@type)!!
!!next!!
!!let tableName=@name!!
/////////////////////////////////////////////////////////////////////////
///C!!@name!!Factory是一个!!@usage!!的对象工厂。它包含了一批!!@usage!!，
///同时又建立了如下索引，以方便查询：
!!travel index!!
///	!!@name!!
!!next!!
///使用本对象工厂，可以完成对!!@usage!!的增删改查操作。具体方法如下：
///	增加：叫用add，完成加入
///	删除：叫用remove就可以删除
///	查询：有如下方法可以查询：
!!travel search!!
!!if (!strcmp(@searchUnique,"yes"))!!
///		使用find!!@name!!，唯一找到对象
!!else!!
///		使用startFind!!@name!!，findNext!!@name!!和endFind!!@name!!完成查询操作
!!endif!!
!!next!!
///	修改：对于查到的结果，可以通过retrieve取出，修改后，通过update放回
///	事务管理：所有的增加、删除和修改都可以指定事务，在事务commit时，真正写入
///		在retrieve时，也可以指定事务，此时将取出经过update的新数据
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@name!!Factory :public CDatabaseDataFactory
{
public:
	///构造方法
	///@param	maxUnit	初始的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	C!!@name!!Factory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///构造方法
	///@param	pConfig	当前的配置文件，本对象将根据配置文件中的定义Max!!@name!!，设置最到的对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	C!!@name!!Factory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///析构方法，将负责释放所占用的空间
	virtual ~C!!@name!!Factory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///从CSV文件中读取所有的!!@name!!
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(char *filename);

	///从CSV文件中读取所有的!!@name!!，文件名将根据配置文件中的定义!!@name!!CSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int readCSV(CConfig *pConfig);
	
	///向CSV文件中写出所有的!!@name!!
	///@param	filename	文件名
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(char *filename);

	///向CSV文件中写出所有的!!@name!!，文件名将根据配置文件中的定义!!@name!!CSVFile
	///@param	pConfig	当前的配置文件
	///@return	1表示完成，0表示没有完成
	virtual int writeCSV(CConfig *pConfig);

	///将内容写到文件中,用于DEBUG
	virtual void dump(FILE *);

	///将内容写到文件中,用于DEBUG
	virtual void dump(char *filename);

	///清空所有的记录
	virtual void clearAll(void);

	friend class C!!@name!!Resource;

	///将一个C!!@name!!加入到该对象工厂，实质上是完成修改索引的工作
	///@param	p!!@name!!	要加入的!!@name!!
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	C!!@name!! *add(CWriteable!!@name!! *p!!@name!!, CTransaction *pTransaction=NULL);
	
	///刷新该C!!@name!!的值
	///@param	p!!@name!!	被刷新的C!!@name!!
	///@param	pNew!!@name!!	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	void update(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pNew!!@name!!, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///增加或者更新数据
	///@param	p!!@name!!	  需要被刷新或者新增的C!!@name!!,等于NULL表示是需要新增的
	///@param	pNew!!@name!!	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	  是否需要更新索引
	///@param	新增或者修改后的数据
	C!!@name!!* addOrUpdate(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pNew!!@name!!, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///删除一个C!!@name!!，同时删除其索引
	///@param	p!!@name!!	要删除的C!!@name!!
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	void remove(C!!@name!! *p!!@name!!, CTransaction *pTransaction=NULL);
	
	///获取某个C!!@name!!
	///@param	p!!@name!!	要读取的C!!@name!!
	///@param	pTraget!!@name!!	存放结果的C!!@name!!
	void retrieve(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pTarget!!@name!!);
	
	///获取第一个C!!@name!!
	///@return	得到的第一个C!!@name!!，如果没有，则返回NULL
	C!!@name!! *getFirst(void);
	
	///获取下一个C!!@name!!
	///@return	得到下一个C!!@name!!，如果没有，则返回NULL
	C!!@name!! *getNext(void);
	
	///结束获取C!!@name!!
	void endGet(void);

	///加入一个操作触发器
	///@param	pTrigger	要加入的操作触发器
	///@return	1表示成功，0表示失败
	int addActionTrigger(C!!@name!!ActionTrigger *pTrigger);
	
	///删除一个操作触发器
	///@param	pTrigger	要删除的操作触发器
	///@return	1表示成功，0表示失败
	int removeActionTrigger(C!!@name!!ActionTrigger *pTrigger);

	///加入一个确认触发器
	///@param	pTrigger	要加入的确认触发器
	///@return	1表示成功，0表示失败
	int addCommitTrigger(C!!@name!!CommitTrigger *pTrigger);
	
	///删除一个确认触发器
	///@param	pTrigger	要删除的确认触发器
	///@return	1表示成功，0表示失败
	int removeCommitTrigger(C!!@name!!CommitTrigger *pTrigger);
	
	///激活确认触发器，缺省是激活的
	///@param	activation	true表示要激活，false表示要停用
	void activeCommitTrigger(bool activation);

!!travel foreigns!!
	///构造所有!!@comment!!的指针
	///@param	pFactory	构造!!@comment!!的指针时，寻找的对象工厂
	!!if (!strcmp(@foreignStrick,"yes"))!!
	///@exception	如果找不到，则抛出RUNTIME_ERROR
	!!endif!!
	void linkAll!!@name!!(C!!@factory!!Factory *pFactory);
	
!!next!!
	!!let tableName=@name!!
!!travel search!!
!!if (!strcmp(@searchUnique,"yes"))!!
	///寻找C!!@tableName!!
	!!travel parameter!!
	///@param	!!@name!!	!!@desc!!
	!!next!!
	///@return	找到的C!!@tableName!!，如果找不到，返回NULL
	C!!@tableName!! *find!!@name!!(!!travel parameter!!!!if (@pumpid!=0)!!, !!endif!! const !!command getReadOnlyEntityTypeName(@name);!!!!show_string (char *)strResult.c_str()!!&  !!@name!!!!next!!);

	!!if !strcmp(@isPK,"yes")!!
	///根据主码寻找
	!!travel parameter!!
	///@param	!!@name!!	!!@desc!!
	!!next!!
	///@return	找到的C!!@tableName!!，如果找不到，返回NULL
	C!!@tableName!! *findByPK(!!travel parameter!!!!if (@pumpid!=0)!!, !!endif!! const !!command getReadOnlyEntityTypeName(@name);!!!!show_string (char *)strResult.c_str()!!&  !!@name!!!!next!!);
	
	///根据主键寻找C!!@tableName!!
	///@param	p!!@tableName!!	要找的值
	///@return	找到的C!!@tableName!!，如果找不到，返回NULL
	C!!@tableName!! *findByPK(CWriteable!!@tableName!! *p!!@tableName!!);

	///根据主键获取C!!@tableName!!
	///@param	p!!@tableName!!	要获取的值，同时用于存放返回的结果
	///@return	找到的C!!@tableName!!，如果找不到，返回NULL
	bool retrieveByPK(CWriteable!!@tableName!! *p!!@tableName!!);

	///根据主键增加新的C!!@tableName!!
	///@param	p!!@tableName!!	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	返回插入的C!!@tableName!!，如果插入失败，则返回NULL
	C!!@tableName!! *addByPK(CWriteable!!@tableName!! *p!!@tableName!!, CTransaction *pTransaction=NULL);

	///根据主键更新C!!@tableName!!的值
	///@param	p!!@tableName!!	新的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@param	updateIndex	是否需要更新索引
	///@return	true表示成功，false表示失败
	bool updateByPK(CWriteable!!@tableName!! *p!!@tableName!!, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///根据主键删除C!!@tableName!!
	///@param	p!!@tableName!!	要删除的值
	///@param	pTransaction	本次操作所属的事务，如果是NULL，表示不使用事务管理，立即生效，否则需要在该事务commit时生效
	///@return	true表示成功，false表示失败
	bool removeByPK(CWriteable!!@tableName!! *p!!@tableName!!, CTransaction *pTransaction=NULL);
	!!endif!!

!!else!!
	friend class C!!@tableName!!Iterator!!@name!!;

	///开始寻找C!!@tableName!!
	!!travel parameter!!
	///@param	!!@name!!	!!@desc!!
	!!next!!
	///@return	满足条件的地一个C!!@tableName!!，如果找不到，返回NULL
	C!!@tableName!! *startFind!!@name!!(!!travel parameter!!!!if (@pumpid!=0)!!, !!endif!! const !!command getReadOnlyEntityTypeName(@name);!!!!show_string (char *)strResult.c_str()!!& !!@name!!!!next!!);

	///寻找下一个符合条件的C!!@tableName!!，必须在startFind!!@name!!以后，endFind!!@name!!之前叫用
	///@return	下一个满足条件C!!@tableName!!，如果已经没有一个满足要求了，则返回NULL
	C!!@tableName!! *findNext!!@name!!(void);

	///结束这一次查询，在完成查询后必须叫用本方法
	void endFind!!@name!!(void);
	!!endif!!

!!next!!
private:
	///完成自己的初始化工作
	///@param	maxUnit	最多的数据对象个数
	///@param	pAllocator	进行内存管理的分配器
	///@param	pIndexMap	索引名称和内存编号的对应表，在非重用时会写入，在重用时只读出
	///@param	reuse	是否重用
	///@param	reuseID	重用编号，非重用时应当置为-1
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///将一个C!!@name!!加入到该对象工厂，实质上是完成修改索引的工作
	///@param	p!!@name!!	要加入的!!@name!!
	///@param	bNoTransaction 是否不属于任何事务
	///@return	加入后该对象的位置，当pTransaction!=NULL时，总是返回NULL
	C!!@name!! *internalAdd(CWriteable!!@name!! *p!!@name!!, bool bNoTransaction);
	
	
	///刷新该C!!@name!!的键值
	///@param	p!!@name!!	被刷新的C!!@name!!
	///@param	pNew!!@name!!	新的值
	///@param	updateIndex	是否需要更新索引
	///@param	bNoTransaction 是否不属于任何事务
	void internalUpdate(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pNew!!@name!!, bool updateIndex,bool bNoTransaction);
	
	///删除一个C!!@name!!，同时删除其索引
	///@param	p!!@name!!	要删除的C!!@name!!
	///@param	bNoTransaction 是否不属于任何事务
	void internalRemove(C!!@name!! *p!!@name!!, bool bNoTransaction);
/*
	///检查某个C!!@name!!是否属于本对象工厂
	///@param	p!!@name!!	要检查的对象
	///@exception	CDesignError	如果不属于，则抛出此异常
	void checkAddress(C!!@name!! *p!!@name!!);
*/
	///使用的配置文件
	CConfig *m_pConfig;

	!!travel index!!
	///基于!!travel self!!!!if @pumpid!=0!!+!!endif!!!!@name!!!!next!!的索引
	CAVLTree *p!!@name!!;
	!!next!!
	
	!!if valid_name("hashindex")!!
	!!travel hashindex!!
	///基于!!@hashKey!!的hash索引
	CHashIndex *p!!@name!!;
	!!next!!
	!!endif!!
	
	!!travel search!!
	!!if (strcmp(@searchUnique,"yes"))!!
	///按照!!travel parameter!!!!if @pumpid!=0!!，!!endif!!!!@name!!!!next!!检索时，存储的查询参数
	!!let searchName=@name!!
	!!travel parameter!!
	!!show_string getEntityTypeName(@name)!! query!!@name!!InSearch!!@searchName!!;
	!!next!!
	
	///按照!!travel parameter!!!!if @pumpid!=0!!，!!endif!!!!@name!!!!next!!检索时，存储最后一次找到的索引节点
	!!if (strcmp(@indexName,"noIndex"))!!
	CAVLNode *pLastFoundInSearch!!@name!!;
	!!elseif valid_name("hashIndexName")!!
	CHashIndexNode *pLastFoundInSearch!!@name!!;
	!!else!!
	C!!@tableName!! *pLastFoundInSearch!!@name!!;
	!!endif!!
	!!endif!!
	!!next!!
	
	///加入前触发
	///@param	p!!@name!!	要加入的!!@name!!
	virtual void beforeAdd(CWriteable!!@name!! *p!!@name!!);
	
	///加入后触发
	///@param	p!!@name!!	已经加入的!!@name!!
	virtual void afterAdd(C!!@name!! *p!!@name!!);

	///更新前触发	
	///@param	p!!@name!!	被刷新的C!!@name!!
	///@param	pNew!!@name!!	新的值
	virtual void beforeUpdate(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pNew!!@name!!);
	
	///更新后触发
	///@param	p!!@name!!	被刷新的C!!@name!!
	virtual void afterUpdate(C!!@name!! *p!!@name!!);
	
	///删除前触发
	///@param	p!!@name!!	要删除的C!!@name!!
	virtual void beforeRemove(C!!@name!! *p!!@name!!);
	
	///确认加入后触发
	///@param	p!!@name!!	已经加入的!!@name!!
	virtual void commitAdd(C!!@name!! *p!!@name!!);

	///确认更新后触发
	///@param	p!!@name!!	被刷新的C!!@name!!
	///@param	pold!!@name!!	原来的值
	virtual void commitUpdate(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pOld!!@name!!);
	
	///确认删除后触发
	///@param	p!!@name!!	已经删除的C!!@name!!
	virtual void commitRemove(CWriteable!!@name!! *p!!@name!!);

	///所有相关的触发器
	vector<C!!@name!!ActionTrigger *> *pActionTriggers;
	vector<C!!@name!!CommitTrigger *> *pCommitTriggers;
	
	///进行查询时，用于比较的对象
	CWriteable!!@name!! compareObject;
	
	///是否激活确认触发器
	bool m_activeCommitTrigger;
};

!!endif!!
!!next!!
#endif
!!leave!!
