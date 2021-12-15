// FlowReader.h: interface for the CFlowReader class.
//
// 2007.7.5	hwp	增加了GetNext方法，将流中的数据取到指定的缓冲区里
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLOWREADER_H__B9DB0445_E13B_4192_83B6_DBBD0528CB9A__INCLUDED_)
#define AFX_FLOWREADER_H__B9DB0445_E13B_4192_83B6_DBBD0528CB9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ReadOnlyFlow.h"
#include "Package.h"

/**CFlowReader是用于流的读取的迭代器
*/
class CFlowReader  
{
public:
	//SetID时用的计算相对位置的标识，类似于fseek中用的SEEK_XXX宏
	enum SeekFlag{
		FROM_HEAD,
		FROM_HERE,
		FROM_END
	};
public:
	/**构造函数
	*/
	CFlowReader();

	/**析构函数
	*/
	virtual ~CFlowReader();

	/**挂接到一个流上
	*@param	pFlow	要读取的CReadOnlyFlow
	*@param	startId	开始读取的编号，这个编号可以大于目前pFlow中的最大编号
	*/
	int AttachFlow(CReadOnlyFlow *pFlow, int nStartId);

	/**卸下挂接的主题
	*@return pFlow	原来挂接的流
	*/
	CReadOnlyFlow *DetachFlow();

	/**设置下一个要读取的编号
	* @param	id	下一个要读取的编号，这个编号可以大于目前pFlow中的最大编号
	* @param	from	编号的计算方法，可以是
	*		FROM_HEAD	从头计算
	*		FROM_HERE	从当前位置计算
	*		FROM_END	从尾计算
	*/
	inline void SetId(int id, SeekFlag from = FROM_HEAD);
	
	/**从CReadOnlyFlow中是否还有东西可读
	* @return	true 表示还有，false 表示没有
	*/
	inline bool Available(void);

	/**获取该CReadOnlyFlow中已经有的对象个数
	* @return	对象个数
	*/
	inline int GetCount(void);

	/**获取该reader所关联的subject
	* @return	返回该Reader所操作的Subject
	*/
	inline CReadOnlyFlow *GetFlow(void);
		
	/**获取下一个要读取的编号
	* @return  下一个要读的对象的编号
	*/
	inline int GetId(void);
	inline int*  GetIdPtr(void);

	/*将挂接的流中的下一个包取到指定的缓冲区中
	*@param	id	对象序号
	*@param pObject 获取对象的缓冲区
	*@param length 缓冲区大小
	*@return 取出对象的长度
	*/
	int GetNext(void *pObject, int length);

	/*将挂接的流中的下一个包取到指定的包对象中
	*@param pPackage 用于存贮取出数据的包对象
	*@return true 获取成功，false 获取失败
	*@remark 包必须有足够的空间
	*/
	bool GetNext(CPackage *pPackage);

	bool GetNextUseNoBuf(CPackage *pPackage);
	
	/**获取通讯阶段编号
	*@return 通讯阶段编号
	*/
	inline WORD GetCommPhaseNo();
protected:
	CReadOnlyFlow *m_pFlow;					/**< 存储所关联的流 */
	WORD m_nCommPhaseNo;			/**< 当前通讯阶段序号 */
	int m_nNextId;					/**< 下一个要读的对象的编号 */
};

inline bool CFlowReader::Available(void)
{
	return GetCount()>m_nNextId;
}


inline int CFlowReader::GetCount(void)
{
	return m_pFlow->GetCount();
}
	
inline int CFlowReader::GetId(void)
{
	return m_nNextId;
}
inline int*  CFlowReader::GetIdPtr(void)
{
	return &m_nNextId;
}
inline CReadOnlyFlow *CFlowReader::GetFlow()
{
	return m_pFlow;
}

inline void CFlowReader::SetId(int id, SeekFlag from)
{
	if (from==FROM_HEAD)
		m_nNextId=id;
	else if (from==FROM_HERE)
		m_nNextId+=id;
	else if (from==FROM_END)
		m_nNextId=m_pFlow->GetCount()+id;
	else
		RAISE_DESIGN_ERROR("Invalid from parameter while calling setId of CFlowReader");
}

inline WORD CFlowReader::GetCommPhaseNo()
{
	return m_nCommPhaseNo;
}

#endif // !defined(AFX_FLOWREADER_H__B9DB0445_E13B_4192_83B6_DBBD0528CB9A__INCLUDED_)
