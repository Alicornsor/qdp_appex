!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file CMemoryDB.h
///@brief定义了类CMemoryDB
///@history 
///20121227	hwp	创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CMEMORYDB_H
#define CMEMORYDB_H

#include "CBaseObject.h"
#include "CConfig.h"
#include "BaseDataStruct.h"
#include "databaseFactories.h"
#include "databaseIterators.h"

struct TableStruct
{
	char tableName[100];
	int  reuseID;
};

/*** SIR XXXXX BEGIN ***/
typedef struct MemTableItemInfoTag
{
	int InvestorAccountDepositCurrentMaxItem;
}MemTableItemInfoT, *pMemTableItemInfoT;
/*** SIR XXXXX END ***/

/////////////////////////////////////////////////////////////////////////
///CMemoryDB是一个内存数据库类，包含了所有定义的表信息
///@author	xuzh
///@version	1.0,20050824
/////////////////////////////////////////////////////////////////////////
class CMemoryDB : public CBaseObject
{
public:
	///构造方法，创建内存数据库
	CMemoryDB(void);
	
	///析构方法，将负责释放所占用的空间
	virtual ~CMemoryDB(void);
	
	virtual int isA(char *objectType);
	virtual char *getType(void);
	virtual void output(CLogger *pLogger,int indent=0);

	///进行初始化工作
	///@param	pConfig	初始化时使用的配置信息
	///@return	1表示成功，0表示失败
	virtual int init(CConfig *pConfig,IMemoryAllocator *pAllocator=NULL,bool reuse=false);
	
	///进行数据载入工作
	///@param	pConfig	载入数据时使用的配置信息
	///@return	1表示成功，0表示失败
	virtual int load(CConfig *pConfig);

	///进行数据存储工作
	///@param	pConfig	保存数据时使用的配置信息
	///@return	1表示成功，0表示失败
	virtual int save(CConfig *pConfig);
	
	///清空所有的数据
	///@return	1表示成功，0表示失败
	virtual void clear(void);
	
	///完成所有外键的连接
	virtual void linkAll(void);
	
	
	
	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!
	///!!@usage!!表
	C!!@name!!Factory *m_!!@name!!Factory;
	
	!!endif!!
	!!next!!

/*** SIR XXXXX BEGIN ***/
	MemTableItemInfoT m_memTableItemInfo;
/*** SIR XXXXX END ***/

private:
	CFixMem *pMem;		///用来存放表的信息
};

#endif
!!leave!!