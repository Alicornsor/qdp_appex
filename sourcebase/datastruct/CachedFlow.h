// CachedFlow.h: interface for the CCachedFlow class.
//
// 20070315 hwp 修正CCachedFlow多线程问题
// 20090310 hwp 增加DeatchUnderFlow方法，可以取消其挂接的流(NT-0069)
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CACHEDFLOW_H__1A86ED0A_F5FE_4A27_A7AC_BCF24B77DCFA__INCLUDED_)
#define AFX_CACHEDFLOW_H__1A86ED0A_F5FE_4A27_A7AC_BCF24B77DCFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Flow.h"
#include "CacheList.h"
#include "PipeEventHandler.h"

/**缓存中索引的节点
*/
struct TCachedFlowNode
{
	void * address;				//对象在缓冲区中的偏移量(当包在缓存中，此项有意义)
	int size;					//对象的长度(当包在缓存中，此项有意义)
};

//add by zbz 扩展放入的消息个数由2亿到32亿
#define CFNV_MAX_NODE		  0x7fffffff
//#define CFNV_MAX_NODE		0x10000000
#define CFNV_BLOCK_SIZE		0x00010000
#define CFNV_BUCKET_SIZE	(CFNV_MAX_NODE/CFNV_BLOCK_SIZE)

/**CCachedFlowNodeVector是用于管理包的索引的队列。它分为两级存贮。
* 一级存贮为CFNV_BUCKET_SIZE个，二级存贮的大小为CFNV_BLOCK_SIZE。
* 最多可存贮的包索引节点为CFNV_MAX_NODE个
*/
class CCachedFlowNodeVector
{
public:
	/**构造函数
	*/
	CCachedFlowNodeVector()
	{
		m_nNodeCount = 0;
		memset(m_pBuckets, 0, CFNV_BUCKET_SIZE*sizeof(TCachedFlowNode *));
	}
	
	/**析构函数
	*/
	~CCachedFlowNodeVector()
	{
		clear();
	}

	/**按下标取索引的一个节点
	*@param n 节点的下标
	*@return 取出的节点的引用
	*/
	inline TCachedFlowNode & operator[](size_t n)
	{
		return m_pBuckets[n/CFNV_BLOCK_SIZE][n&(CFNV_BLOCK_SIZE-1)];
	}

	/**向队列尾部添加一个索引的节点
	*@param node 要添加的节点
	*/
	inline void push_back(TCachedFlowNode &node)
	{
		if (m_nNodeCount % CFNV_BLOCK_SIZE == 0)
		{
			m_pBuckets[m_nNodeCount/CFNV_BLOCK_SIZE] = new TCachedFlowNode[CFNV_BLOCK_SIZE];
		}
		(*this)[m_nNodeCount] = node;
		m_nNodeCount++;	
	}

	/**获取队列中节点的个数
	*@return 队列中节点的个数
	*/
	inline size_t size()
	{
		return m_nNodeCount;
	}

	/**清空队列
	*/
	inline void clear()
	{
		m_nNodeCount = 0;
		for (int i=0; i<CFNV_BUCKET_SIZE; i++)
		{
			if (m_pBuckets[i] == NULL)
			{
				break;
			}
			//delete m_pBuckets[i];
			// 2013-01-22 longqy 
			delete [] m_pBuckets[i];
		}
		memset(m_pBuckets, 0, CFNV_BUCKET_SIZE*sizeof(TCachedFlowNode *));
	}
	
private:
	volatile int m_nNodeCount;							/**< 队列中节点的个数*/
	TCachedFlowNode *m_pBuckets[CFNV_BUCKET_SIZE];		/**< 一级缓存*/
};

/**CCachedFlow是带固定大小缓存的流，用于提高读写速度。
* 它是部分线程安全的流，在缓冲区未用完之前，可以有一个写入者，同时有多个读取者
* 它可以挂接另外一个流，用于持久化或存贮缓冲区无法容纳的包。
* 它在构造时要指定缓存的大小。缓存使用先进先出的方法管理。
* 在读取包时，如果缓存中没有，则试着从挂接的流中读取。
*/
class CCachedFlow : public CFlow
{
public:
	/**构造函数
	* @param bSyncFlag 在加入一个包是，是否立刻同步到挂接的流。
	*		 true立刻同步到挂接的流，false不同步到挂接的流
	* @param nMaxObjects 缓存包的最大数量,如果为0则不限制包的个数
	* @param nDataBlockSize CacheList使用的数据区块大小，不要小于一个数据包的长度
	*/
	CCachedFlow(bool bSyncFlag, int nMaxObjects, int nDataBlockSize);
	
	/**析构函数
	*/
	virtual ~CCachedFlow();

	/**获取流中已经有的包的个数
	*@return 包的个数
	*/
	virtual int GetCount(void);
	
	/**获取指向该流长度的指针
	*@return	指向该流长度的指针
	*/
	virtual const int *GetCountPtr(void);

	/**zbz 20101013 获取放入消息个数累计的指针
	*@return 指向该流长度的指针
	*/
	//del by wangwei,20140929
//	virtual const int *GetPushPtr(void);
	
	/**zbz 20101013 获取放入消息个数累计的指针
	*@return 指向该流长度的指针
	*/
	//del by wangwei,20140929
//	virtual const int *GetPushSize(void);


	/**获取流的通讯阶段序号
	*@return 流的通讯阶段序号
	*/
	virtual WORD GetCommPhaseNo();

	/**设置流的通讯阶段序号
	*@param nCommPhaseNo 要设置的流的通讯阶段序号
	*/
	virtual void SetCommPhaseNo(WORD nCommPhaseNo);
	
	/**挂接另一个流
	* @param pFlow 所要挂接的流
	* @return 
	*/
	virtual int AttachUnderFlow(CFlow *pFlow);

	/**取消原挂接的流
	* @return 原挂接的流
	*/
	virtual CFlow *DeatchUnderFlow();

	/**取出挂接的流存贮的包数量
	* @return 挂接的流存贮的包数量
	*/
	int GetUnderCount();

	/**清空缓存
	*/
	void Clear();

	/**将缓存中的包同步到挂接的流中
	* @return 0 成功 <0 失败
	*/
	int SyncUnderFlow(int id);

	/**将流尾部的包截掉
	*@param nCount 保留的包的个数
	*@return true 操作成功； false 操作失败
	*/
	virtual bool Truncate(int nCount); 

	/**向流中增加一个对象
	*@param	pObject 要增加的对象
	*@param length 增加数据的长度
	*@return 对象在流中的序号，小于0表示增加失败
	*/
	virtual int Append(void *pObject, int length);

	/**获取指定编号的对象
	*@param	id	对象序号
	*@param pObject 获取对象的缓冲区
	*@param length 缓冲区大小
	*@return 取出对象的长度
	*/
 	virtual int Get(int id, void *pObject, int length);
 	
	/**将缓冲的第一个包从缓冲区中移去
	*@return true 移去第一个包成功
	*@return false 移去第一个包失败
	*/
	bool PopFront();
	
	/**粘帖一个观察者
	*@param pEventHandler 观察内容是否增加，产生通知消息
	*/
	virtual void AttachObserver(CPipeEventHandler *pEventHandler);
	
	/**删除一个观察者
	*/
	virtual void DeatchObserver();
	
protected:
	bool m_bSyncFlag;				/**<在加入一个包是，是否立刻同步到挂接的流*/
	CFlow *m_pUnderFlow;			/**<挂接的流*/

	volatile int m_nFirstID;		/**<缓存中第一个包的序号*/

	int m_nMaxObjects;				/**<缓存包的最大数量*/
	int m_nDataBlockSize;			/**<CacheList使用的数据区块大小*/

	CCacheList m_CacheList;			/**<包中数据的缓存*/
	
	typedef CCachedFlowNodeVector CNodeQueue;
	CNodeQueue m_NodeQueue;			/**<包的索引*/
	
	WORD m_nCommPhaseNo;			/**<通讯阶段序号*/

	//add zbz 20101013
	//del by wangwei,20140929
//	int	m_nPushCount;				/*累计放入的消息报个数*/
//	size_t m_nPushSizeByte;   	/*累计放入的消息报长度*/
//	int	 m_nPushSizeM;
	
	CPipeEventHandler *m_pEventHandler;
};

#endif // !defined(AFX_CACHEDFLOW_H__B7AC16F2_8521_4AC1_B445_30DDFE2F8F12__INCLUDED_)
