// ObjAllocator.cpp: implementation of the CObjAllocator class.
// 
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "ObjAllocator.h"

const int OA_MALLOC_SIZE	= OA_MAX_BYTES * 16 + OA_ALIGN;
const int OA_FREE_INIT_SIZE	= 20;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CObjAllocator::CObjAllocator()
// 2013-01-28 longqy 初始化的顺序跟定义的一致
: m_nUsedSize(0), m_pStartFree(NULL), m_pEndFree(NULL), m_pMallocHead(NULL)
{
	memset(m_aFreeList, 0, sizeof(char *) * OA_NFREELISTS);
}

CObjAllocator::~CObjAllocator()
{
	char *p = NULL;
	for (;m_pMallocHead != NULL;)
	{
		p = m_pMallocHead;
		m_pMallocHead = *((char **)m_pMallocHead);
		delete p;
	}
}

void * CObjAllocator::Allocate(int n)
{
	if (n > OA_MAX_BYTES)
	{
		return NULL;
	}
	m_nUsedSize += n;
	TOA_Obj **ppMyFreeList = m_aFreeList+FreeListIndex(n);
	TOA_Obj *pResult = *ppMyFreeList;
	if (pResult == NULL)
	{
		return ReFill(RoundUp(n));
	}
	*ppMyFreeList = pResult->pFreeListLink;
	return pResult;
}

void CObjAllocator::Deallocate(void *p, int n)
{
	TOA_Obj **ppMyFreeList = m_aFreeList + FreeListIndex(n);
	TOA_Obj *q = (TOA_Obj *)p;
	q->pFreeListLink = *ppMyFreeList;
	*ppMyFreeList = q;
	m_nUsedSize -= n;
}

void *CObjAllocator::ReFill(int nSize)
{
	int nObjs = OA_FREE_INIT_SIZE;
	char *pChunk = ChunkAlloc(nSize, nObjs);
	if (nObjs == 1)
	{
		return pChunk;
	}
	TOA_Obj **ppMyFreeList = m_aFreeList+FreeListIndex(nSize);
	TOA_Obj *pCurrentObj, *pNextObj;
	*ppMyFreeList = pNextObj = (TOA_Obj *)(pChunk + nSize);
	for (int i=1; ; i++)
	{
		pCurrentObj = pNextObj;
		pNextObj = (TOA_Obj *)((char *)pNextObj + nSize);
		if (nObjs - 1 == i)
		{
			pCurrentObj->pFreeListLink = NULL;
			break;
		}
		else
		{
			pCurrentObj->pFreeListLink = pNextObj;
		}
	}
	return pChunk;
}

char *CObjAllocator::ChunkAlloc(int nSize, int &nObjs)
{
	char *pResult = NULL;
	int nTotalBytes = nSize * nObjs;
	int nBytesLeft = m_pEndFree - m_pStartFree;
	if (nBytesLeft < nTotalBytes)
	{
		if (nBytesLeft >= nSize)
		{
			nObjs = nBytesLeft/nSize;
			nTotalBytes = nSize * nObjs;
		}
		else
		{
			char *p = new char[OA_MALLOC_SIZE];
			*((char **)p) = m_pMallocHead;
			m_pMallocHead = p;
			m_pStartFree = m_pMallocHead + OA_ALIGN;
			m_pEndFree = m_pMallocHead + OA_MALLOC_SIZE;
			return ChunkAlloc(nSize, nObjs);
		}
	}
	pResult = m_pStartFree;
	m_pStartFree += nTotalBytes;
	return pResult;
}

