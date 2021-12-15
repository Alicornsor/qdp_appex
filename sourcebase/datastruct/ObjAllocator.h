// ObjAllocator.h: interface for the CObjAllocator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJALLOCATOR_H__59711751_8025_4E46_BF42_ADB1DE03F639__INCLUDED_)
#define AFX_OBJALLOCATOR_H__59711751_8025_4E46_BF42_ADB1DE03F639__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const int OA_ALIGN		= 8;
const int OA_MAX_BYTES	= 512;
const int OA_NFREELISTS	= OA_MAX_BYTES/OA_ALIGN;

union TOA_Obj
{
	union TOA_Obj *pFreeListLink;
	char pClientData[1];
};
/**CObjAllocator是一种内存管理器，提供了分配内存和释放内存的接口。
* 其算法模仿SGI STL，使用两级内存管理，适用于大量小块的内存分配。
*/
class CObjAllocator  
{
public:
	CObjAllocator();
	virtual ~CObjAllocator();
	void * Allocate(int n);
	void Deallocate(void *p, int n);
	inline int GetUsedSize()
	{
		return m_nUsedSize;
	}
private:
	inline int RoundUp(int nBytes) 
    { 
		return (((nBytes) + (int) OA_ALIGN-1) & ~((int) OA_ALIGN - 1)); 
	}
	inline int FreeListIndex(int nBytes) 
	{
        return (((nBytes) + (int)OA_ALIGN-1)/(int)OA_ALIGN - 1);
	}
	void *ReFill(int nSize);
	char *ChunkAlloc(int nSize, int &nObjs);
private:
	int m_nUsedSize;
	TOA_Obj * m_aFreeList[OA_NFREELISTS];
	char * m_pStartFree;
	char * m_pEndFree;
	char * m_pMallocHead;
};

#endif // !defined(AFX_OBJALLOCATOR_H__59711751_8025_4E46_BF42_ADB1DE03F639__INCLUDED_)
