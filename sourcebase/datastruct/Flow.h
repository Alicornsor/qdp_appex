// Flow.h: interface for the CFlow class .
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLOW_H__D2F86CC2_6DC5_11D7_BB64_82A63033BA6B__INCLUDED_)
#define AFX_FLOW_H__D2F86CC2_6DC5_11D7_BB64_82A63033BA6B__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ReadOnlyFlow.h"

/**CFlow是一种对象容器（流）
* 对象只能从尾部添加，可以按序号读出。
*/
class  CFlow : public CReadOnlyFlow
{
public:
	/**构造函数
	* @param nSubjectID 流所对应的主题
	*/
	CFlow();

	/**析构函数
	*/
	virtual ~CFlow();
		
	/**设置流的通讯阶段序号
	*@param nCommPhaseNo 要设置的流的通讯阶段序号
	*/
	virtual void SetCommPhaseNo(WORD nCommPhaseNo) = 0;

	/**将流尾部的对象截掉
	*@param nCount 保留的对象的个数
	*@return true 操作成功； false 操作失败
	*/
	virtual bool Truncate(int nCount) = 0; 

	/**向流中增加一个对象
	*@param	pObject 要增加的对象
	*@param length 增加数据的长度
	*@return 对象在流中的序号，小于0表示增加失败
	*/
	virtual int Append(void *pObject, int length) = 0;

	/**获取指向该流长度的指针
	*@return	指向该流长度的指针
	*/
	virtual const int *GetCountPtr(void) = 0;
};


#endif // !defined(AFX_FLOW_H__D2F86CC2_6DC5_11D7_BB64_82A63033BA6B__INCLUDED_)
