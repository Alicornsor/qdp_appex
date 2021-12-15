// ThreadSafeFlow.h: interface for the CThreadSafeFlow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADSAFEFLOW_H__334FD8EF_120B_4E5F_9283_F32A40A3E6CF__INCLUDED_)
#define AFX_THREADSAFEFLOW_H__334FD8EF_120B_4E5F_9283_F32A40A3E6CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Flow.h"

/**CThreadSafeFlow是一个线程安全的流，可以建立在任意流的上面
*/
class CThreadSafeFlow : public CFlow  
{
public:
	CThreadSafeFlow(CFlow *pUnderFlow)
	{
		m_pUnderFlow = pUnderFlow;
		INIT_CRITICAL_VAR(m_criticalVar);
	}
	virtual ~CThreadSafeFlow()
	{
		delete m_pUnderFlow;
		DELETE_CRITICAL_VAR(m_criticalVar)
	}

	/**获取流中已经有的对象的个数
	*@return 对象的个数
	*/
	virtual int GetCount(void)
	{
		ENTER_CRITICAL(m_criticalVar);
		int nCount = m_pUnderFlow->GetCount();
		LEAVE_CRITICAL(m_criticalVar);
		return nCount;
	}
	
	/**获取流的通讯阶段序号
	*@return 流的通讯阶段序号
	*/
	virtual WORD GetCommPhaseNo()
	{
		ENTER_CRITICAL(m_criticalVar);
		WORD wCommPhaseNo = m_pUnderFlow->GetCommPhaseNo();
		LEAVE_CRITICAL(m_criticalVar);
		return wCommPhaseNo;
	}

	/**获取指定编号的对象
	*@param	id	对象序号
	*@param pObject 获取对象的缓冲区
	*@param length 缓冲区大小
	*@return 取出对象的长度
	*/
 	virtual int Get(int id, void *pObject, int length)
	{
		ENTER_CRITICAL(m_criticalVar);
		int nLength = m_pUnderFlow->Get(id, pObject, length);
		LEAVE_CRITICAL(m_criticalVar);
		return nLength;
	}

	/**设置流的通讯阶段序号
	*@param nCommPhaseNo 要设置的流的通讯阶段序号
	*/
	virtual void SetCommPhaseNo(WORD nCommPhaseNo)
	{
		ENTER_CRITICAL(m_criticalVar);
		m_pUnderFlow->SetCommPhaseNo(nCommPhaseNo);
		LEAVE_CRITICAL(m_criticalVar);
	}

	/**将流尾部的对象截掉
	*@param nCount 保留的对象的个数
	*@return true 操作成功； false 操作失败
	*/
	virtual bool Truncate(int nCount) 
	{
		ENTER_CRITICAL(m_criticalVar);
		bool bResult = m_pUnderFlow->Truncate(nCount);
		LEAVE_CRITICAL(m_criticalVar);
		return bResult;
	}

	/**向流中增加一个对象
	*@param	pObject 要增加的对象
	*@param length 增加数据的长度
	*@return 对象在流中的序号，小于0表示增加失败
	*/
	virtual int Append(void *pObject, int length)
	{
		ENTER_CRITICAL(m_criticalVar);
		int nId = m_pUnderFlow->Append(pObject, length);
		LEAVE_CRITICAL(m_criticalVar);
		return nId;
	}
private:
	CFlow *m_pUnderFlow;
	CRITICAL_VAR m_criticalVar;
};

#endif // !defined(AFX_THREADSAFEFLOW_H__334FD8EF_120B_4E5F_9283_F32A40A3E6CF__INCLUDED_)
