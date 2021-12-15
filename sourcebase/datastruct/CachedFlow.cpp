// CachedFlow.cpp: implementation of the CCachedFlow class.
//
// 20070828 hwp 修改异常退出的方式
// 20090310 hwp 增加DeatchUnderFlow方法，可以取消其挂接的流(NT-0069)
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "CachedFlow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCachedFlow::CCachedFlow(bool bSyncFlag, int nMaxObjects, int nDataBlockSize)
:m_CacheList(nDataBlockSize)
{
	m_nMaxObjects = nMaxObjects;
	m_nDataBlockSize = nDataBlockSize;
	m_pUnderFlow = NULL;
	m_bSyncFlag = bSyncFlag;
	m_nCommPhaseNo = 0;
//	m_nPushCount=0;
//	m_nPushSizeByte=0;
//	m_nPushSizeM=0;
	m_pEventHandler=NULL;
	Clear();
}

CCachedFlow::~CCachedFlow()
{
	delete m_pUnderFlow;
	m_pUnderFlow = NULL;
}

void CCachedFlow::Clear()
{
	m_nFirstID = 0;
	m_NodeQueue.clear();
	m_CacheList.Clear();	
}

int CCachedFlow::AttachUnderFlow(CFlow *pFlow)
{
	m_pUnderFlow = pFlow;

	m_nCommPhaseNo = pFlow->GetCommPhaseNo();

	//清空缓存
	Clear();
	
	//将下层流的对象载入缓存
	char *buf = new char[m_nDataBlockSize];
	for(int i=0; i<m_pUnderFlow->GetCount(); i++){
		int len = m_pUnderFlow->Get(i, buf, m_nDataBlockSize);
		Append(buf, len);
	}
	// 2013-1-18 longqy  内存空间是由 new[] 分配，释放时用 delete[] 比较规范
	//delete buf;
	delete[] buf;

	return 0;
}
	
CFlow *CCachedFlow::DeatchUnderFlow()
{
	CFlow *pFlow = m_pUnderFlow;
	m_pUnderFlow = NULL;
	return pFlow;
}
	
int CCachedFlow::GetCount(void)
{
	return m_NodeQueue.size();

}

const int *CCachedFlow::GetCountPtr(void)
{
	if(m_pUnderFlow == NULL){
		return NULL;
	}
	return m_pUnderFlow->GetCountPtr();
}

//del by wangwei,20140929
/*const int *CCachedFlow::GetPushPtr(void)
{
	return &m_nPushCount;
}
*/
//del by wangwei,20140929
/*const int *CCachedFlow::GetPushSize(void)
{
	return &m_nPushSizeM;
}
*/

int CCachedFlow::Append(void *pObject, int length)
{
	int nCount = m_NodeQueue.size();
	if( m_nMaxObjects>0 && nCount-m_nFirstID>=m_nMaxObjects){
		if(m_pUnderFlow != NULL && 
			m_pUnderFlow->GetCount()<m_nFirstID){
			//这时加入缓存会导致某个对象既不在缓存中，也不在下层流中，
			//因此,这种情况下返回-1,表示Append失败
			return -1;
		}
		PopFront();
	}
	TCachedFlowNode node;
	node.address = m_CacheList.PushBack(pObject, length);
	node.size = length;
	m_NodeQueue.push_back(node);
	if (m_bSyncFlag) 
	{
		SyncUnderFlow(nCount);
	}
	
	//add by zbz
	//del by wangwei,20140929
//	m_nPushCount=nCount;
//	m_nPushSizeByte=m_nPushSizeByte+length+sizeof(TCachedFlowNode);
//	m_nPushSizeM=m_nPushSizeByte/(1024);
	
	//产生通知 m_pEventHandler 在这里的唯一作用，就是通知流上有新的数据。
	if (m_pEventHandler)
		m_pEventHandler->Notify();
	
	return nCount;
}
	
int CCachedFlow::Get(int id, void *pObject, int length)
{
	if(id >= m_nFirstID){			//要找的对象在缓存内
		TCachedFlowNode node = m_NodeQueue[id];
		if(node.size > length){		//获取对象的缓冲区太小
			EMERGENCY_EXIT("Insufficient buffer length while reading CFlow");
		}
		memcpy(pObject, node.address, node.size);
		return node.size;
	}
	else if (m_pUnderFlow != NULL)
	{
		return m_pUnderFlow->Get(id, pObject, length);
	}
	return -1;
}

int CCachedFlow::GetUnderCount()
{
	if(m_pUnderFlow == NULL){
		return -1;
	}
	return m_pUnderFlow->GetCount();
}

int CCachedFlow::SyncUnderFlow(int id)
{
	int undercount = GetUnderCount();
	if(id != undercount){
		return -1;
	}

	if(GetCount() == undercount){
		return -1;
	}

	TCachedFlowNode node = m_NodeQueue[undercount];
	m_pUnderFlow->Append(node.address, node.size);	
	return 0;
}


WORD CCachedFlow::GetCommPhaseNo()
{
	return m_nCommPhaseNo;
}
	
void CCachedFlow::SetCommPhaseNo(WORD nCommPhaseNo)
{
	if (m_nCommPhaseNo != nCommPhaseNo)
	{
		Clear();
		m_nCommPhaseNo = nCommPhaseNo;
	}
	if (m_pUnderFlow != NULL)
	{
		m_pUnderFlow->SetCommPhaseNo(nCommPhaseNo);
	}
}

bool CCachedFlow::Truncate(int nCount)
{
	if (m_pUnderFlow != NULL)
	{	
		//update 20120308 
		if(!m_pUnderFlow->Truncate(nCount))
		{
			return false;
		}
		CCachedFlow::AttachUnderFlow(m_pUnderFlow);
	}
	//add 20120308 zbz
	else
	{
		if (nCount == 0)
		{
			CCachedFlow::Clear();
		}
		else
		{
			RAISE_DESIGN_ERROR("CCachedFlow can't truncate great 0 ");
			return false;
		}
	}	
	return true;
}

bool CCachedFlow::PopFront()
{
	if (m_nFirstID >= GetCount())
	{
		return false;
	}
	m_CacheList.PopFront( m_NodeQueue[m_nFirstID].size );
	m_NodeQueue[m_nFirstID].address = NULL;
	m_nFirstID++;
	return true;
}

void CCachedFlow::AttachObserver(CPipeEventHandler *pEventHandler)
{
	m_pEventHandler=pEventHandler;
}
void CCachedFlow::DeatchObserver()
{
	m_pEventHandler=NULL;
}
	
