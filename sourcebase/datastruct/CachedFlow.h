// CachedFlow.h: interface for the CCachedFlow class.
//
// 20070315 hwp ����CCachedFlow���߳�����
// 20090310 hwp ����DeatchUnderFlow����������ȡ����ҽӵ���(NT-0069)
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CACHEDFLOW_H__1A86ED0A_F5FE_4A27_A7AC_BCF24B77DCFA__INCLUDED_)
#define AFX_CACHEDFLOW_H__1A86ED0A_F5FE_4A27_A7AC_BCF24B77DCFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Flow.h"
#include "CacheList.h"
#include "PipeEventHandler.h"

/**�����������Ľڵ�
*/
struct TCachedFlowNode
{
	void * address;				//�����ڻ������е�ƫ����(�����ڻ����У�����������)
	int size;					//����ĳ���(�����ڻ����У�����������)
};

//add by zbz ��չ�������Ϣ������2�ڵ�32��
#define CFNV_MAX_NODE		  0x7fffffff
//#define CFNV_MAX_NODE		0x10000000
#define CFNV_BLOCK_SIZE		0x00010000
#define CFNV_BUCKET_SIZE	(CFNV_MAX_NODE/CFNV_BLOCK_SIZE)

/**CCachedFlowNodeVector�����ڹ������������Ķ��С�����Ϊ����������
* һ������ΪCFNV_BUCKET_SIZE�������������Ĵ�СΪCFNV_BLOCK_SIZE��
* ���ɴ����İ������ڵ�ΪCFNV_MAX_NODE��
*/
class CCachedFlowNodeVector
{
public:
	/**���캯��
	*/
	CCachedFlowNodeVector()
	{
		m_nNodeCount = 0;
		memset(m_pBuckets, 0, CFNV_BUCKET_SIZE*sizeof(TCachedFlowNode *));
	}
	
	/**��������
	*/
	~CCachedFlowNodeVector()
	{
		clear();
	}

	/**���±�ȡ������һ���ڵ�
	*@param n �ڵ���±�
	*@return ȡ���Ľڵ������
	*/
	inline TCachedFlowNode & operator[](size_t n)
	{
		return m_pBuckets[n/CFNV_BLOCK_SIZE][n&(CFNV_BLOCK_SIZE-1)];
	}

	/**�����β������һ�������Ľڵ�
	*@param node Ҫ���ӵĽڵ�
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

	/**��ȡ�����нڵ�ĸ���
	*@return �����нڵ�ĸ���
	*/
	inline size_t size()
	{
		return m_nNodeCount;
	}

	/**��ն���
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
	volatile int m_nNodeCount;							/**< �����нڵ�ĸ���*/
	TCachedFlowNode *m_pBuckets[CFNV_BUCKET_SIZE];		/**< һ������*/
};

/**CCachedFlow�Ǵ��̶���С���������������߶�д�ٶȡ�
* ���ǲ����̰߳�ȫ�������ڻ�����δ����֮ǰ��������һ��д���ߣ�ͬʱ�ж����ȡ��
* �����Թҽ�����һ���������ڳ־û�������������޷����ɵİ���
* ���ڹ���ʱҪָ������Ĵ�С������ʹ���Ƚ��ȳ��ķ���������
* �ڶ�ȡ��ʱ�����������û�У������Ŵӹҽӵ����ж�ȡ��
*/
class CCachedFlow : public CFlow
{
public:
	/**���캯��
	* @param bSyncFlag �ڼ���һ�����ǣ��Ƿ�����ͬ�����ҽӵ�����
	*		 true����ͬ�����ҽӵ�����false��ͬ�����ҽӵ���
	* @param nMaxObjects ��������������,���Ϊ0�����ư��ĸ���
	* @param nDataBlockSize CacheListʹ�õ����������С����ҪС��һ�����ݰ��ĳ���
	*/
	CCachedFlow(bool bSyncFlag, int nMaxObjects, int nDataBlockSize);
	
	/**��������
	*/
	virtual ~CCachedFlow();

	/**��ȡ�����Ѿ��еİ��ĸ���
	*@return ���ĸ���
	*/
	virtual int GetCount(void);
	
	/**��ȡָ��������ȵ�ָ��
	*@return	ָ��������ȵ�ָ��
	*/
	virtual const int *GetCountPtr(void);

	/**zbz 20101013 ��ȡ������Ϣ�����ۼƵ�ָ��
	*@return ָ��������ȵ�ָ��
	*/
	//del by wangwei,20140929
//	virtual const int *GetPushPtr(void);
	
	/**zbz 20101013 ��ȡ������Ϣ�����ۼƵ�ָ��
	*@return ָ��������ȵ�ָ��
	*/
	//del by wangwei,20140929
//	virtual const int *GetPushSize(void);


	/**��ȡ����ͨѶ�׶����
	*@return ����ͨѶ�׶����
	*/
	virtual WORD GetCommPhaseNo();

	/**��������ͨѶ�׶����
	*@param nCommPhaseNo Ҫ���õ�����ͨѶ�׶����
	*/
	virtual void SetCommPhaseNo(WORD nCommPhaseNo);
	
	/**�ҽ���һ����
	* @param pFlow ��Ҫ�ҽӵ���
	* @return 
	*/
	virtual int AttachUnderFlow(CFlow *pFlow);

	/**ȡ��ԭ�ҽӵ���
	* @return ԭ�ҽӵ���
	*/
	virtual CFlow *DeatchUnderFlow();

	/**ȡ���ҽӵ��������İ�����
	* @return �ҽӵ��������İ�����
	*/
	int GetUnderCount();

	/**��ջ���
	*/
	void Clear();

	/**�������еİ�ͬ�����ҽӵ�����
	* @return 0 �ɹ� <0 ʧ��
	*/
	int SyncUnderFlow(int id);

	/**����β���İ��ص�
	*@param nCount �����İ��ĸ���
	*@return true �����ɹ��� false ����ʧ��
	*/
	virtual bool Truncate(int nCount); 

	/**����������һ������
	*@param	pObject Ҫ���ӵĶ���
	*@param length �������ݵĳ���
	*@return ���������е���ţ�С��0��ʾ����ʧ��
	*/
	virtual int Append(void *pObject, int length);

	/**��ȡָ����ŵĶ���
	*@param	id	�������
	*@param pObject ��ȡ����Ļ�����
	*@param length ��������С
	*@return ȡ������ĳ���
	*/
 	virtual int Get(int id, void *pObject, int length);
 	
	/**������ĵ�һ�����ӻ���������ȥ
	*@return true ��ȥ��һ�����ɹ�
	*@return false ��ȥ��һ����ʧ��
	*/
	bool PopFront();
	
	/**ճ��һ���۲���
	*@param pEventHandler �۲������Ƿ����ӣ�����֪ͨ��Ϣ
	*/
	virtual void AttachObserver(CPipeEventHandler *pEventHandler);
	
	/**ɾ��һ���۲���
	*/
	virtual void DeatchObserver();
	
protected:
	bool m_bSyncFlag;				/**<�ڼ���һ�����ǣ��Ƿ�����ͬ�����ҽӵ���*/
	CFlow *m_pUnderFlow;			/**<�ҽӵ���*/

	volatile int m_nFirstID;		/**<�����е�һ���������*/

	int m_nMaxObjects;				/**<��������������*/
	int m_nDataBlockSize;			/**<CacheListʹ�õ����������С*/

	CCacheList m_CacheList;			/**<�������ݵĻ���*/
	
	typedef CCachedFlowNodeVector CNodeQueue;
	CNodeQueue m_NodeQueue;			/**<��������*/
	
	WORD m_nCommPhaseNo;			/**<ͨѶ�׶����*/

	//add zbz 20101013
	//del by wangwei,20140929
//	int	m_nPushCount;				/*�ۼƷ������Ϣ������*/
//	size_t m_nPushSizeByte;   	/*�ۼƷ������Ϣ������*/
//	int	 m_nPushSizeM;
	
	CPipeEventHandler *m_pEventHandler;
};

#endif // !defined(AFX_CACHEDFLOW_H__B7AC16F2_8521_4AC1_B445_30DDFE2F8F12__INCLUDED_)