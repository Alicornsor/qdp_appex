// ExCachedFlow.cpp: implementation of the CCachedFlow class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "ExCachedFlow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExCachedFlow::CExCachedFlow(bool bSyncFlag, int nMaxObjects, int nDataBlockSize)
:CCachedFlow(bSyncFlag,nMaxObjects,nDataBlockSize)
{
	m_iHaveGetID = -1;

}

CExCachedFlow::~CExCachedFlow()
{

}



int CExCachedFlow::Append(void *pObject, int length)
{
	int nCount = m_NodeQueue.size();

	while(PopFront());

	TCachedFlowNode node;
	node.address = m_CacheList.PushBack(pObject, length);
	node.size = length;
	m_NodeQueue.push_back(node);
	if (m_bSyncFlag) 
	{
		SyncUnderFlow(nCount);
	}	
	//����֪ͨ m_pEventHandler �������Ψһ���ã�����֪ͨ�������µ����ݡ�
	if (m_pEventHandler)
		m_pEventHandler->Notify();
	
	return nCount;
}
	

bool CExCachedFlow::PopFront()
{
	if (m_nFirstID >= GetCount())
	{
		return false;
	}
	//Ҫpop�����ݴ��ڵ����Ѿ�ȡ������������pop��ȥ
	if (m_nFirstID >= m_iHaveGetID)
	{
		return false;
	}	
	m_CacheList.PopFront( m_NodeQueue[m_nFirstID].size );
	m_NodeQueue[m_nFirstID].address = NULL;
	m_nFirstID++;
	return true;
}


//20150604 huwp ��Ӹú���
int CExCachedFlow::Get(int id, void **pObject)
{
	if(id >= m_nFirstID)
	{	
		//Ҫ�ҵĶ����ڻ�����
		TCachedFlowNode node = m_NodeQueue[id];
		*pObject = node.address;
		m_iHaveGetID = id;
		return node.size;
	}
	return -1;
};
