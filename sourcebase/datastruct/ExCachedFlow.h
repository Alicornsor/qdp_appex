// CachedFlow.h: interface for the CCachedFlow class.
//
// 20070315 hwp 修正CCachedFlow多线程问题
// 20090310 hwp 增加DeatchUnderFlow方法，可以取消其挂接的流(NT-0069)
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCACHEDFLOW_H__1A86ED0A_F5FE_4A27_A7AC_BCF24B77DCFA__INCLUDED_)
#define AFX_EXCACHEDFLOW_H__1A86ED0A_F5FE_4A27_A7AC_BCF24B77DCFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CachedFlow.h"

class CExCachedFlow : public CCachedFlow
{
public:
	/**构造函数
	* @param bSyncFlag 在加入一个包是，是否立刻同步到挂接的流。
	*		 true立刻同步到挂接的流，false不同步到挂接的流
	* @param nMaxObjects 缓存包的最大数量,如果为0则不限制包的个数
	* @param nDataBlockSize CacheList使用的数据区块大小，不要小于一个数据包的长度
	*/
	CExCachedFlow(bool bSyncFlag, int nMaxObjects, int nDataBlockSize);
	
	/**析构函数
	*/
	virtual ~CExCachedFlow();



	/**向流中增加一个对象
	*@param	pObject 要增加的对象
	*@param length 增加数据的长度
	*@return 对象在流中的序号，小于0表示增加失败
	*/
	virtual int Append(void *pObject, int length);

	/**将缓冲的第一个包从缓冲区中移去
	*@return true 移去第一个包成功
	*@return false 移去第一个包失败
	*/
	bool PopFront();

	//20150604 huwp 添加该函数
	virtual int Get(int id, void **pObject);

	
protected:

	volatile int m_iHaveGetID;


};

#endif // !defined(AFX_CACHEDFLOW_H__B7AC16F2_8521_4AC1_B445_30DDFE2F8F12__INCLUDED_)
