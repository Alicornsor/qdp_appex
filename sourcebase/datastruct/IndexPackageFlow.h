// IndexPackageFlow.h: interface for the CIndexPackageFlow class.
//
// 20070905 hwp 增加了GetPackageIndex方法
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INDEXPACKAGEFLOW_H__C65A6874_466C_4F86_A80A_D1E16F00FFC7__INCLUDED_)
#define AFX_INDEXPACKAGEFLOW_H__C65A6874_466C_4F86_A80A_D1E16F00FFC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ReadOnlyFlow.h"

class CIndexPackageFlow : public CReadOnlyFlow  
{
public:
	CIndexPackageFlow();
	virtual ~CIndexPackageFlow();

	/**获取流中已经有的包个数
	*@return 包个数
	*/
	virtual int GetCount(void);
	
	virtual void AttachUnderFlow(CReadOnlyFlow *pFlow);

	virtual CReadOnlyFlow *DeatchUnderFlow();

	/**将流尾部的包截掉
	*@param nCount 保留的包的个数
	*@return true 操作成功； false 操作失败
	*/
	virtual bool Truncate(int nCount); 

	/**向流中增加一个对象
	*@param nIndex 对象在下层流中的序号
	*@return 对象在流中的序号，小于0表示增加失败
	*/
	virtual int Append(int nIndex);
	
	/**获取指定编号的对象
	*@param	id	对象序号
	*@param pObject 获取对象的缓冲区
	*@param length 缓冲区大小
	*@return 取出对象的长度
	*/
 	virtual int Get(int id, void *pObject, int length);
	
	virtual WORD GetCommPhaseNo();
	
	virtual void SetCommPhaseNo(WORD nCommPhaseNo);

	/**获取指定编号的对象在下层流中的序号
	*@param	id	对象序号
	*@return 取出对象的在下层流中的序号
	*/
	int GetPackageIndex(int id);
protected:
	typedef vector<DWORD> CPackageIndex;
	CPackageIndex m_PackageIndex;
	CReadOnlyFlow *m_pUnderFlow; 
	DWORD m_nCommPhaseNo;
};

#endif // !defined(AFX_INDEXPACKAGEFLOW_H__C65A6874_466C_4F86_A80A_D1E16F00FFC7__INCLUDED_)
