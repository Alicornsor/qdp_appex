/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CFixMem.h
///@brief	定义了类CFixMem
///@history 
///20020214	xuzh		创建该文件
///20020524	xuzh		增加了DEBUG用的dump方法
///20041003	xuzh		通过计数，为getFirst/getNext/endGet函数提高效率
///20050626 xuzh		修改了标示块被使用的方法，同时增加了自动增长的功能
/////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// 现有的数据结构说明
/// 1. 当只有一块内存被申请的时候
///     ____________________________________________________________________________
///	    |TFixMemHeadStruct | 块使用的信息		|(被使用的块) | 未被使用的内存有 	|																
///		|(基本信息)		   |(大小 (size-1)/8*8	|			  | 指针指向下一个空闲	|
///		|__________________|____________________|_____________|_____________________|
/// 
/// 2.当多个内存区域被分配的时候,第一块区域的结构同上,其他新增的内存区域如下图
///     ________________________________________________________________________
///	    |FixMemLinker| 块使用的信息			|(被使用的块) | 未被使用的内存有 	|																
///		|(基本信息)	 |(大小 (size-1)/8*8	|			  | 指针指向下一个空闲	|
///		|___________ |______________________|_____________|_____________________|
///
/// 3.当使用文件的情况,在文件中保存的结构如下:
///     __________________________________________________________________________________
///	    |int 表示多少	| 块使用的信息		| 数据区	| 块使用的信息		| 数据区	  |														
///		|Chunk被分配	|(大小 (size-1)/8*8	|			| (大小 (size-1)/8*8|			  |......
///		|_______________|___________________|___________|___________________|_____________|
///
//////////////////////////////////////////////////////////////////////////


#ifndef CFIXMEM_H
#define CFIXMEM_H

#include "platform.h"
#include "CBaseObject.h"
#include "Allocator.h"
#include <vector>
using namespace std;

#define RESERVE_ID			1024	///保留的ID,自己设置的MemID必须小于这个值

///表示内存空闲的结构
typedef struct TFreeHeadStruct
{
	struct TFreeHeadStruct *pNext;	///指向下一个空闲位置的指针
}	TFreeHead;


struct FixMemLinker
{
//	int allocCounnt;				///这个Chunk有多少区域被分配使用
//	int dummy;
	TFreeHead *pHead;
	FixMemLinker* pNextChunk;
};

typedef struct TFixMemHeadStruct	
{
	///保存单位大小和最大单位数
	int unitSize, maxUnit;
	
	///实际保存的单位大小
	int storeUnitSize;
		
	///已经申请的大小
	int allocCount;
	
	int dummy;

	///已经分配的块数量
	int chunkNumber;

	///空闲队列的头和尾
	TFreeHead *pHead;
	
	///指向下一个快的指针
	FixMemLinker *pNextChunk;

}	TFixMemHead;


///下列宏用于说明CFixMem建立在什么位置
///NORMAL_MEMORY指我们普通使用的内存
#define NORMAL_MEMORY 1
///SHARE_MEMORY指操作系统提供的共享内存
#define SHARE_MEMORY 2
///FILE_MEMORY指我们普通使用的内存，不过需要同时写文件
#define FILE_MEMORY 3

/////////////////////////////////////////////////////////////////////////
///CFixMem是一个固定单位大小，固定上限的内存管理对象。它适用于数量大、经常修改、
///有设计上限的固定数据结构的内存管理需求
///@author	xuzh
///@version	1.0,20020214
/////////////////////////////////////////////////////////////////////////
class CFixMem : public CBaseObject
{
public:
	///构造方法，申请空间，设置初值，建立空闲块链表
	///@param	unitSize	每个单位的大小，以字节计，至少4字节
	///@param	maxUnit	最多包含的单位数量，应当大于0
	///@param   initUnit 初始创建的块数,初始大小为10
	///@param	reuse	说明这个存储是否需要重用
	///@param	reuseID	指向我们需要建立的存储的位置，只有当对普通内存，不重用的情况下，这个值无意义
	///@param	readOnly	1表示该CFixMem是只读的，0表示可以读写
	///@exception	CDesignError	如果参数不符合要求，则抛出此异常
	///@exception	CRuntimeError	如果内存不够，则抛出此异常
	CFixMem(int unitSize, int maxUnit,IMemoryAllocator *pAllocator,bool reuse=false, int reuseID = -1, int readOnly=0,int initUnit=1);

	///析构方法，释放所有空间
	virtual ~CFixMem(void);

	virtual int isA(char *objectType);
	virtual char *getType(void);
	virtual void output(CLogger *pLogger,int indent=0);

	///申请一个单位大小
	///@exception	CRuntimeError	如果申请的量已经达到maxUnit，则抛出此异常
	virtual void *alloc(void);

	///释放一个单位
	///@param	pObject	 要释放的单位地址
	///@exception	CDesignError	如果pObject不符合本CFixMem产生的地址，则抛出此异常
	virtual void free(const void *pObject);

	///释放n个单位
	///@param	pObject	 要释放的单位地址
	///@param	pObject	 连续的N个
	///@exception	CDesignError	如果pObject不符合本CFixMem产生的地址，则抛出此异常
	void free(const void *pObject,int n);

	///全部释放
	virtual void freeAll(void);

	///获取本CFixMem中已经有的纪录个数
	///@return	纪录个数
	virtual int getCount(void);

	///获取第一个纪录，这里的次序是不一定的，只有一种情况是有保障的，就是如果我们只申请，
	///从不释放，那么获取的次序和写入的次序是相同的。
	///@return	第一个纪录的地址，如果没有纪录，则返回NULL
	virtual const void *getFirst(void);

	///获取下一个纪录，这里的次序是不一定的，只有一种情况是有保障的，就是如果我们只申请，
	///从不释放，那么获取的次序和写入的次序是相同的。
	///@return	下一个纪录的地址，如果没有下一个纪录，则返回NULL
	virtual const void *getNext(void);

	///结束搜索纪录
	virtual void endGet(void);

	///按照下标方式，获取纪录
	///@param	id	纪录的编号，范围应当在0至maxUnt-1
	///@return	该编号的纪录。如果该纪录已经删除了，那么返回NULL
	virtual const void *getObject(const int id);

	///提示CFixMem，系统修改了pObject指向的内容，对于FILE_MEMORY的情况，需要写盘
	///@param	pObject	提示修改的对象地址
	virtual void updateObject(const void *pObject);

	///获取申请得到的内存的首地址
	///@return	首地址
	virtual const void *getStartAddress(void);

	///获取作为共享内存方式得到的共享内存号
	///@return	共享内存号，如果不使用共享内存，则返回-1
	virtual const int getMemoryBlockID(void);

	///检查本CFixMem是否正常
	///@param	freeCount	要确认空闲的块数量是此值，如果输入-1，表示不必做此项检查
	///@return	1表示正常，0表示不正常
	//	virtual int isValid(int freeCount=-1);

	///将内容写到文件中,用于DEBUG
	void dump(FILE *);
private:
	///分配内存块
	///@param blockID 内存快的ID,从0开始
	///@param reuse   是否重用
	///@param	space	指向我们需要建立的存储的位置，只有当对普通内存，不重用的情况下，这个值无意义
	///		当media=NORMAL_MEMORY时，space指向内存中的实际空间
	///		当media=SHARE_MEMORY时，space是共享内存编号的整数指针
	///		当media=FILE_MEMORY时，space指向文件名
	void InitialMemoryBlock(int blockID,bool reuse,int reuseID,bool isInit = false);

	///增加内存分配的引用计数
	///@param 新引用的内存地址
	void IncreaseUseCount(const void *pObject);

	///减少内存分配的引用计数
	///@param 新引用的内存地址
	void DecreaseUseCount(const void *pObject);

	///检查pObject是否指向本CFixMem中一个合法的对象
	///@param	pObject	要检查的地址
	///@return	1表示合法，0表示非法
	virtual int checkAddress(const void *pObject);

	int	getIDByAddress(const void* pObject);

private:
	///共享内存的编号，对于非共享内存，该值为-1
	int reuseID;

	///头说明块的位置
	TFixMemHead *m_head;

	///实际内容的空间首地址
	//char *m_myMemory;
	vector<char *> m_myMemoryVect;

	///使用getFirst、getNext和endGet时保存上一次返回值
	int m_lastId;

	///表示本CFixMem是否只读
	int m_readOnly;

	///表示本次叫用getFirst,getNext，共返回了几个，用于对此函数进行优化
	//int gotCount;

	///表示本CFixMem中存在的最大编号，不保证该编号有值，但是保证大于等于该编号的没有值
	int m_largestID;

	///表示保存哪些块被使用的信息的首地址，防止进程结束的情况下重新捡回时需要遍历操作的问题
	char *m_pUsedBlockInfoOffset;

	///表示标示内存使用状况的列表的大小
	int   m_blockIndexSize;

	///表示存储的对象的大小
	int   m_unitSize;

	///每一块最多可以存储的内存快大小
	int   m_maxUnit;


	int	  m_initUnit;


	int	  m_firstBlockID;

	IMemoryAllocator *m_pMemoryAllocator;

	int   m_reuseID;

public:		//这里声明成public 是为了测试，将来会改成private		
	///设置第n个块的使用状态
	///@param	blockID	内存块的标示
	///@param	bUsed	使用状态,true 表示使用，false 表示free
	void SetBlockUsedState(int blockID,bool bUsed);

	///获取第n个块的使用状态
	///@param	blockID	内存块的标示
	///@return	true表示已被使用，false表示未被使用
	bool GetBlockUsedState(int blockID);

	///设置第n个块的使用状态
	///@param	pvoid	内存块地址
	///@param	bUsed	使用状态,true 表示使用，false 表示free
	void SetBlockUsedState(const void *pvoid,bool bUsed);

	///获取第n个块的使用状态
	///@param	pvoid	内存块地址
	///@return	true表示已被使用，false表示未被使用
	bool GetBlockUsedState(const void *pvoid);

	///根据地址取得内存块的序列编号
	///@param	pvoid	内存块地址
	///@return	内存块的序号
	int  GetBlockID(const void *pvoid);

	///获取重用的块号
	///@return	重用编号
	int GetReuseID();

	///获取保存数量的指针
	///@return	保存数量的指针
	const int *GetCountPtr(void);
};


#endif
