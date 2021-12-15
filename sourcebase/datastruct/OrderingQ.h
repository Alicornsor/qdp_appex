// OrderingQ.h: interface for the COrderingQ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ORDERINGQ_H__693B097B_0EC8_4790_A580_32B118575EBC__INCLUDED_)
#define AFX_ORDERINGQ_H__693B097B_0EC8_4790_A580_32B118575EBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CacheList.h"

struct CDataItem;

class COrderingQ  
{
public:
	COrderingQ(int nMaxSlot, int nDataBlockSize = 40000);
	virtual ~COrderingQ();
	
	bool EnQueue(int nIndex, void *pData, int nDataLen);

	void DeQueue();

	void *QueueFront(int &nDataLen);

	void Clear();

	inline int GetStartIndex();
	
	inline void SetStartIndex(int nStartIndex);
	
	inline bool IsEmpty();
protected:
	CDataItem **m_pSlot;
	int m_nMaxSlot;
	int m_nSlotHead;

	CDataItem *m_pDataItem;
	int m_nMaxDataItem;
	int m_nDataItemHead;
	int m_nDataItemTail;
	
	CCacheList m_cacheList;

	int m_nStartIndex;
};

inline int COrderingQ::GetStartIndex()
{
	return m_nStartIndex;
}

inline void COrderingQ::SetStartIndex(int nStartIndex)
{
	Clear();
	m_nStartIndex = nStartIndex;
}

inline bool COrderingQ::IsEmpty()
{
	return m_nDataItemHead == m_nDataItemTail;
}

#endif // !defined(AFX_ORDERINGQ_H__693B097B_0EC8_4790_A580_32B118575EBC__INCLUDED_)
