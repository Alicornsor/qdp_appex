/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CHashIndex.cpp
///@brief	实现了类CHashIndex
///@history 
///20020611	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CHashIndex.h"
#include "HashMap.h"

CHashIndex::CHashIndex(int hashKeySize, IMemoryAllocator *pAllocator,bool reuse, int reuseID, int readOnly)
{
	int i = 0;
	for (;i<__stl_num_primes;i++)
	{
		if (__stl_prime_list[i]>=hashKeySize)
		{
			m_hashKeySize=__stl_prime_list[i];
			break;
		}
	}
	if (i==__stl_num_primes)
	{
		RAISE_RUNTIME_ERROR("Too large hash size");
	}
	pIndexMem=new CFixMem(sizeof(CHashIndexNode),4096*8,pAllocator,reuse,reuseID,readOnly);
	if (pIndexMem==NULL)
	{
		RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (!reuse)
	{
		init();
	}
}

CHashIndex::~CHashIndex(void)
{
	delete pIndexMem;
}

void CHashIndex::init(void)
{
	for (int i=0;i<m_hashKeySize;i++)
	{
		CHashIndexNode *pNode=(CHashIndexNode *)(pIndexMem->alloc());
		pNode->pObject=NULL;
		pNode->next=NULL;
	}
}
