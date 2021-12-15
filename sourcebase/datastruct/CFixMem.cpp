/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CFixMem.cpp
///@brief实现了类CFixMem
///@history 
///20020214	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CFixMem.h"
#include <iterator>
using namespace std;

CFixMem::CFixMem(int unitSize, int maxUnit,IMemoryAllocator *pAllocator,bool reuse, int reuseID, int readOnly,int initUnit)
{
	m_unitSize = unitSize;
	m_maxUnit = maxUnit;
	m_readOnly = readOnly;
	m_initUnit = initUnit;
	if(m_maxUnit < initUnit)
		m_maxUnit = initUnit;
	m_pMemoryAllocator = pAllocator;
	if (!reuse)
	{
		m_largestID=0;
	}
	else
	{
		///重用的情况还没有考虑
	}
	InitialMemoryBlock(0,reuse,reuseID,true);	//第一次初始化内存区域
}

CFixMem::~CFixMem(void)
{
	///不做Free
}

int CFixMem::isA(char *objectType)
{
	if (!strcmp(objectType,"CFixMem"))
		return 1;
	return CBaseObject::isA(objectType);
}

char *CFixMem::getType(void)
{
	return "CFixMem";
}

void CFixMem::output(CLogger *pLogger,int indent)
{
	CHECK_TYPE("CFixMem");
	for(int i = 0; i<m_head->chunkNumber;i++)
	{
		pLogger->output(indent,0,"CFixMem:%s:unit_size=%d,max_unit=%d,alloc_unit=%d,address=%p,",
			(m_readOnly?"m_readOnly":"readWrite"),
			m_head->unitSize,m_head->maxUnit,m_head->allocCount,m_myMemoryVect[i]);
	}
}

void *CFixMem::alloc(void)
{
	TFreeHead *pReturn;
	if (m_readOnly)
		RAISE_DESIGN_ERROR("m_readOnly fix memory can not alloc");
	if(m_head->pHead == NULL)
		InitialMemoryBlock(m_head->chunkNumber,false,-1);

	pReturn=m_head->pHead;
	m_head->pHead=m_head->pHead->pNext;
	IncreaseUseCount(pReturn);
	SetBlockUsedState(pReturn,true);
	return pReturn;
}

void CFixMem::free(const void *pObject)
{
	TFreeHead *pCur;
	if (m_readOnly)
		RAISE_DESIGN_ERROR("m_readOnly fix memory can not free");
	//if (!checkAddress(pObject))
	//	RAISE_DESIGN_ERROR("Incorrect object to be free");
	pCur=(TFreeHead *)(pObject);

	if(!GetBlockUsedState(pCur))
		RAISE_DESIGN_ERROR("Incorrect object to be free");
	pCur->pNext=m_head->pHead;
	m_head->pHead=pCur;
	DecreaseUseCount(pObject);
	SetBlockUsedState(pObject,false);
}

void CFixMem::free(const void *pObject,int n)
{
	int nID = GetBlockID(pObject);
	for(int i=nID;i<nID+n;i++)
	{
		const void *p = this->getObject(i);
		if(pObject != NULL){
			free(p);
		}
	}
}

void CFixMem::freeAll(void)
{
	///本函数错误
	TFreeHead *pCur, *pNext;
	for(int i = 0;i<m_head->chunkNumber;i++)
	{
		m_head->allocCount=0;
		m_head->pHead=pCur=(TFreeHead *)m_myMemoryVect[0];
		for (i=0;i<m_head->maxUnit;i++)
		{
			if (i==m_head->maxUnit-1)
				pNext=NULL;
			else
				pNext=(TFreeHead *)((char *)(pCur)+m_head->storeUnitSize);
			pCur->pNext=pNext;
			SetBlockUsedState(pCur,false);
			pCur=pNext;
		}
	}
}



int CFixMem::getCount(void)
{
	return m_head->allocCount;
}


const void *CFixMem::getFirst(void)
{
	//gotCount=0;
	m_lastId=-1;
	return getNext();
}

const void *CFixMem::getNext(void)
{
	if (m_lastId==-2)
		return NULL;
	/*
	if (gotCount>=m_head->allocCount)
	{
		m_lastId=-2;
		return NULL;
	}
	*/
	for (m_lastId++;m_lastId<m_largestID;m_lastId++)
	{
		const void *result=getObject(m_lastId);
		if (result!=NULL)
		{
			//gotCount++;
			return result;
		}
	}
	m_lastId=-2;
	return NULL;
}

void CFixMem::endGet(void)
{
	m_lastId=-2;
}

const void *CFixMem::getObject(const int id)
{
	TFreeHead *pCur;
	if ((id<0)||(id>=m_head->maxUnit*m_head->chunkNumber))
		RAISE_DESIGN_ERROR("invalid id in getting CFixMem object");
	pCur=(TFreeHead *)(m_myMemoryVect[id/m_head->maxUnit]+(id%m_head->maxUnit)*(m_head->storeUnitSize));
//	if(!GetBlockUsedState(pCur))
	if(!GetBlockUsedState(id))
		return NULL;
	else
		return pCur;
	return NULL;
}

void CFixMem::updateObject(const void *pObject)
{
	if (m_readOnly)
		RAISE_DESIGN_ERROR("m_readOnly fix memory can not update");
	/*if (!checkAddress(pObject))
	{
		RAISE_DESIGN_ERROR("Incorrect Object to be update");
	}*/
	return;
}

const void *CFixMem::getStartAddress(void)
{
	return m_myMemoryVect[0];
}

const int CFixMem::getMemoryBlockID(void)
{
	return m_firstBlockID;
}

int CFixMem::checkAddress(const void *pObject)
{
	int offset;
	int nID = GetBlockID(pObject);
	offset=(char *)pObject-m_myMemoryVect[nID/m_head->maxUnit];
	if ((offset<0)||(offset%(m_head->storeUnitSize)!=0)||(offset/(m_head->storeUnitSize)>=m_head->maxUnit))
		return 0;
	else
		return 1;
	return 1;
}


void CFixMem::SetBlockUsedState(int blockID,bool bUsed)
{
	int chunkID = blockID/m_maxUnit;
	//char *psz = m_pUsedBlockInfoOffset + (blockID/8);
	char *psz = m_myMemoryVect[chunkID] - m_blockIndexSize + ((blockID%m_maxUnit)/8);
	int bit = blockID%m_maxUnit%8;
	if(bUsed)
		(*psz) |= (1 << (7-bit));
	else
		(*psz) &= ~(1 << (7-bit));
	if (bUsed)
	{
		if (blockID >= m_largestID)
		{
			m_largestID=blockID+1;
		}
	}
}

void CFixMem::SetBlockUsedState(const void *pvoid,bool bUsed)
{
	SetBlockUsedState(GetBlockID(pvoid),bUsed);
}

bool CFixMem::GetBlockUsedState(int blockID)
{
	//char *psz = m_pUsedBlockInfoOffset + (blockID/8);
	int chunkID = blockID/m_maxUnit;
	char *psz = m_myMemoryVect[chunkID] -  m_blockIndexSize + ((blockID%m_maxUnit)/8);
	//unsigned char sz = *psz;
	int bit = blockID%m_maxUnit%8;
	return (((*psz) & (1 << (7-bit))) != 0);
}

bool CFixMem::GetBlockUsedState(const void *pvoid)
{
	return GetBlockUsedState(GetBlockID(pvoid));
}


void CFixMem::dump(FILE *fp)
{
	fprintf(fp, "CFixMem={ this=%p\n", this);
	fprintf(fp,	"\tUnitSize=%d,  maxUnit=%d\n", m_head->unitSize, m_head->maxUnit);
	for(int i=0;i<m_head->chunkNumber;i++)
		fprintf(fp, "\tmyMemory %d = %p\n",i,m_myMemoryVect[i]);
	fprintf(fp, "\tpHead=%p,    pHead->pNext=%p,  &(pHead->pNext)=%p\n",m_head->pHead, m_head->pHead->pNext, &(m_head->pHead->pNext));
	fprintf(fp,	"\tallocCount=%d, m_lastId=%d\n", m_head->allocCount,m_lastId);	
	fprintf(fp,"}\n");
}

int	CFixMem::getIDByAddress(const void* pvoid)
{
	vector<char *>::iterator it = lower_bound(m_myMemoryVect.begin(),m_myMemoryVect.end(),pvoid);
	if(it == m_myMemoryVect.end())
	{
		it--;
	}
	else
	{
		if(*it != pvoid)
			it--;
	}

	int dis = distance(m_myMemoryVect.begin(),it);
	return dis;
}

int CFixMem::GetBlockID(const void *pvoid)
{
	int dis = getIDByAddress(pvoid);
	int ID = dis*m_maxUnit + ((char *)pvoid - m_myMemoryVect[dis])/m_head->storeUnitSize;
	return ID;
}

void CFixMem::IncreaseUseCount(const void *pvoid)
{
	m_head->allocCount++;
	/*
	int dis = getIDByAddress(pvoid);
	if(dis == 0)
		m_head->allocCount++;
	else
	{
		FixMemLinker *pLink = (FixMemLinker *)(m_myMemoryVect[dis] - m_blockIndexSize - sizeof(FixMemLinker));
		pLink->allocCounnt++;
		m_head->allocCount++;
	}
	*/
}

void CFixMem::DecreaseUseCount(const void *pvoid)
{
	m_head->allocCount--;
	if (m_head->allocCount==0)
	{
		m_largestID=0;
	}
	/*
	int dis = getIDByAddress(pvoid);
	if(dis == 0)
		m_head->allocCount--;
	else
	{
		FixMemLinker *pLink = (FixMemLinker *)(m_myMemoryVect[dis] - m_blockIndexSize - sizeof(FixMemLinker));
		pLink->allocCounnt--;
		m_head->allocCount--;
	}
	*/
}

void CFixMem::InitialMemoryBlock(int blockID,bool reuse, int reuseID,bool isInit)
{
	int i;
	TFreeHead *pCur, *pNext;
	int storeUnitSize = 0;
	int totalSize = 0;

	m_lastId=-2;

	///这里去掉了多余的4个字节，采用了别的方式 
	storeUnitSize=((m_unitSize-1)/8+1)*8;

	m_blockIndexSize = ((m_maxUnit-1)/64+1)*8;	///1个char可以表示8个块的信息。

	if(blockID == 0 ) //第一块区域和后面的区域的头大小是不一样的
		totalSize= storeUnitSize*m_maxUnit+sizeof(TFixMemHead)+m_blockIndexSize;
	else
		totalSize = storeUnitSize*m_maxUnit+sizeof(FixMemLinker)+m_blockIndexSize;

	char *pMem;
	if (!reuse)
	{	
		m_reuseID = reuseID;
		pMem = (char *)m_pMemoryAllocator->alloc(totalSize,m_reuseID,false);		
		if(blockID == 0)
			m_head = (TFixMemHead *)pMem;
		if(blockID == 0)	//如果是第一块，我们需要初始化头。
		{
			m_pUsedBlockInfoOffset = (char *)(m_head+1);
			memset(m_pUsedBlockInfoOffset,0,m_blockIndexSize);
			m_myMemoryVect.push_back( (char *)(m_pUsedBlockInfoOffset + m_blockIndexSize));
			m_head->unitSize=m_unitSize;
			m_head->maxUnit=m_maxUnit;
			m_head->storeUnitSize=storeUnitSize;
			m_head->allocCount=0;
			m_head->pHead=pCur=(TFreeHead *)m_myMemoryVect[0];
			m_head->chunkNumber = 1;
			m_head->pNextChunk = NULL;
		}
		else
		{
			FixMemLinker* pLinker = (FixMemLinker*)pMem;
			//pLinker->allocCounnt = 0;
			pLinker->pNextChunk = NULL;
			pLinker->pHead = (TFreeHead *)(pMem + sizeof(FixMemLinker)+m_blockIndexSize);  
			memset(pMem+sizeof(FixMemLinker),0,m_blockIndexSize);
			m_myMemoryVect.push_back((char *)pLinker->pHead);
			pCur = pLinker->pHead;

			FixMemLinker** pLinkNextPoint = &m_head->pNextChunk;
			for(int i = 1;i<m_head->chunkNumber;i++)
			{
				pLinkNextPoint = &(*pLinkNextPoint)->pNextChunk;
			}
			*pLinkNextPoint = pLinker;
			m_head->chunkNumber++;
			if(!isInit)
				m_head->pHead = pCur;
		}

		for (i=0;i<m_maxUnit;i++)
		{
			if (i==m_maxUnit-1)
				pNext=NULL;
			else
				pNext=(TFreeHead *)((char *)(pCur)+storeUnitSize);
			pCur->pNext=pNext;
			pCur=pNext;
		}
	}
	else
	{
		m_reuseID = reuseID;
		pMem = (char *)m_pMemoryAllocator->alloc(totalSize,reuseID,true);
		if(blockID == 0)
			m_head = (TFixMemHead *)pMem;		
		m_pUsedBlockInfoOffset = (char *)(m_head+1);

		m_myMemoryVect.clear();
		m_myMemoryVect.push_back((char *)(m_pUsedBlockInfoOffset + m_blockIndexSize));

		FixMemLinker** pLinkNextPoint = &m_head->pNextChunk;
		for(int i = 1;i<m_head->chunkNumber;i++)
		{
			m_myMemoryVect.push_back((char *)(*pLinkNextPoint)->pHead);
			pLinkNextPoint = &(*pLinkNextPoint)->pNextChunk;
		}
		if ((m_unitSize!=m_head->unitSize)||(storeUnitSize!=m_head->storeUnitSize)||(m_maxUnit!=m_head->maxUnit))
			RAISE_DESIGN_ERROR("Invalid unit size or max unit while reuse normal memory");		
	}
	return;
}

int CFixMem::GetReuseID()
{
	return m_reuseID;
}

const int *CFixMem::GetCountPtr(void)
{
	return &(m_head->allocCount);
}
