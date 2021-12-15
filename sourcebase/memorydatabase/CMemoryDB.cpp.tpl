!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file CMemoryDB.cpp
///@brief实现了类CMemoryDB
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CMemoryDB.h"
#include <map>
#include <string>
using namespace std;

#define MEMORYDB_ID			0
#define MAX_TABLE_COUNT		300				///引导块中每块放置的内存数据库表或者索引的数量

CMemoryDB::CMemoryDB(void)
{
	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!
	m_!!@name!!Factory=NULL;
	!!endif!!
	!!next!!
	
	memset( &m_memTableItemInfo, 0x00, sizeof(MemTableItemInfoT) );
}
	
CMemoryDB::~CMemoryDB(void)
{
	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!
	if (m_!!@name!!Factory!=NULL)
		delete m_!!@name!!Factory;
	!!endif!!
	!!next!!
}
	
int CMemoryDB::isA(char *objectType)
{
	if (!strcmp(objectType,"CMemoryDB"))
		return 1;
	return CBaseObject::isA(objectType);
}

char *CMemoryDB::getType(void)
{
	return "CMemoryDB";
}

void CMemoryDB::output(CLogger *pLogger,int indent)
{
	CHECK_TYPE("CMemoryDB");
	pLogger->output(indent,0,"CMemoryDB:");
	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!
	if (m_!!@name!!Factory!=NULL)
		m_!!@name!!Factory->output(pLogger,indent+1);
	!!endif!!
	!!next!!
}

int CMemoryDB::init(CConfig *pConfig,IMemoryAllocator *pAllocator,bool reuse)
{
	if(pAllocator == NULL)
	{
		pAllocator = new CNormalMemoryAllocator();
		pAllocator->init(reuse);
	}
	if(!reuse)
	{
		map<string,int> indexMap;
		pMem=new CFixMem(sizeof(TableStruct),MAX_TABLE_COUNT,pAllocator,false,MEMORYDB_ID);
		TableStruct* pStru = NULL;
		
	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!	
		m_!!@name!!Factory=new C!!@name!!Factory(pConfig,pAllocator,&indexMap);
		if (m_!!@name!!Factory==NULL)
			return 0;
		pStru = (TableStruct *)pMem->alloc();
		strcpy(pStru->tableName,"!!@name!!");
		pStru->reuseID = m_!!@name!!Factory->getReuseID();
				
	!!endif!!
	!!next!!
	
		map<string,int>::iterator it = indexMap.begin();
		for(;it!=indexMap.end();it++)
		{
			pStru = (TableStruct *)pMem->alloc();
			strcpy(pStru->tableName,it->first.c_str());
			pStru->reuseID = it->second;
		}
	}
	else
	{
		pMem=new CFixMem(sizeof(TableStruct),MAX_TABLE_COUNT,pAllocator,true,MEMORYDB_ID);
		map<string,int> blockMap;
		TableStruct* pStru = NULL;
		for(int i=0;i<pMem->getCount();i++)
		{
			pStru = (TableStruct *)pMem->getObject(i);
			blockMap.insert(map<string,int>::value_type(pStru->tableName,pStru->reuseID));
		}
		map<string,int>::iterator it;
			
	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!	
		it = blockMap.find("!!@name!!");
		if(it == blockMap.end())
			m_!!@name!!Factory=new C!!@name!!Factory(pConfig,pAllocator,&blockMap);
		else
			m_!!@name!!Factory=new C!!@name!!Factory(pConfig,pAllocator,&blockMap,true,it->second);
		if (m_!!@name!!Factory==NULL)
			return 0;
				
	!!endif!!
	!!next!!		
	}
	return 1;
}

int CMemoryDB::load(CConfig *pConfig)
{
	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!
	!!if !strcmp(@readTable,"yes")!!
	if (!m_!!@name!!Factory->readCSV(pConfig))
		return 0;
	!!endif!!
	!!endif!!
	!!next!!
	return 1;
}

int CMemoryDB::save(CConfig *pConfig)
{
	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!
	!!if !strcmp(@writeTable,"yes")!!
	if (!m_!!@name!!Factory->writeCSV(pConfig))
		return 0;
	!!endif!!
	!!endif!!
	!!next!!
	return 1;
}

void CMemoryDB::clear(void)
{
	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!
	m_!!@name!!Factory->clearAll();
	!!endif!!
	!!next!!
}

void CMemoryDB::linkAll(void)
{
	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!
	!!let tableName=@name!!
	!!travel foreigns!!
	m_!!@tableName!!Factory->linkAll!!@name!!(m_!!@factory!!Factory);
	!!next!!
	!!endif!!
	!!next!!
}

!!leave!!
