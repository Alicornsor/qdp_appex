// ReadOnlyFlow.h: interface for the CReadOnlyFlow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READONLYFLOW_H__9BFF4BE3_1853_4B6A_90DE_4DB34A222AF1__INCLUDED_)
#define AFX_READONLYFLOW_H__9BFF4BE3_1853_4B6A_90DE_4DB34A222AF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**CReadOnlyFlow是一种对象容器（流）,流中的对象可以按序号读出。
* CReadOnlyFlow只定义的操作接口，需要派生类中实现具体的方法
*/
class CReadOnlyFlow  
{
public:
	CReadOnlyFlow();
	virtual ~CReadOnlyFlow();

	/**获取流中已经有的对象的个数
	*@return 对象的个数
	*/
	virtual int GetCount(void) = 0;
	
	/**获取流的通讯阶段序号
	*@return 流的通讯阶段序号
	*/
	virtual WORD GetCommPhaseNo() = 0;

	/**获取指定编号的对象
	*@param	id	对象序号
	*@param pObject 获取对象的缓冲区
	*@param length 缓冲区大小
	*@return 取出对象的长度
	*/
 	virtual int Get(int id, void *pObject, int length) = 0;
	//20150604 huwp 添加该函数
	virtual int Get(int id, void **pObject){return 0;};
};

#endif // !defined(AFX_READONLYFLOW_H__9BFF4BE3_1853_4B6A_90DE_4DB34A222AF1__INCLUDED_)
