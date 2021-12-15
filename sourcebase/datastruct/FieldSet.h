// FieldSet.h: interface for the CFieldSet class.
//
// 20070806 赵鸿昊 增加FIELD_TO_STRING方法，将一个field转换成一行文本输出
// 20070827 赵鸿昊 修正CFieldIteratorBase未进行指针越界检查，无法应付错误报文的问题
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELDSET_H__83362A2A_0A24_46AE_A788_295CB18F6BF3__INCLUDED_)
#define AFX_FIELDSET_H__83362A2A_0A24_46AE_A788_295CB18F6BF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FieldDescribe.h"
#include "Package.h"

struct TFieldHeader
{
	WORD FieldID;
	WORD Size;
};

/**域迭代器基类
*/
class CFieldIteratorBase
{
public:
	/**构造函数
	* @param pHead 包内数据的头指针
	* @param pEnd 包内数据的尾指针
	* @param pFieldDescribe 要遍历的域的描述字
	*/
	CFieldIteratorBase(char *pHead, char *pEnd, CFieldDescribe *pFieldDescribe);

	/**迭代器指到下一个域
	*/
	void Next();
	
	/**是否还有更多的域
	* @return true 没有更多的域\n
	* @return false 还有更多的域
	*/
	inline bool IsEnd();

	/**取出当前域的头
	* @param fieldHeader 取出的当前域的头
	*/
	inline void RetrieveHeader(TFieldHeader &fieldHeader);
public:
	bool m_bInSys;	
private:
	inline void GetHeader();
	inline int DataRemain();
	
protected:
	TFieldHeader m_fieldHeader;
	CFieldDescribe *m_pFieldDescribe;
	char *m_pEnd;
	char *m_pCurr;
	char *m_pData;
};

inline bool CFieldIteratorBase::IsEnd()
{
	return m_pData == NULL;
}

inline int CFieldIteratorBase::DataRemain()
{
	return m_pEnd - m_pCurr;
}

inline void CFieldIteratorBase::RetrieveHeader(TFieldHeader &fieldHeader)
{
	fieldHeader = m_fieldHeader;
}

inline void CFieldIteratorBase::GetHeader()
{
	memcpy(&m_fieldHeader, m_pCurr, sizeof(TFieldHeader));
	CHANGE_ENDIAN(m_fieldHeader.FieldID);
	CHANGE_ENDIAN(m_fieldHeader.Size);
}


/**遍历整个包的迭代器
*/
class CFieldTypeIterator : public CFieldIteratorBase
{
public:
	/**构造函数
	* @param pHead 包内数据的头指针
	* @param pEnd 包内数据的尾指针
	*/
	CFieldTypeIterator(char *pHead, char *pEnd,bool bInSys);
	
	/**从缓冲区中读到一个域中
	* @param pFieldDescribe 要获取域的描述字
	* @param field 这个域的引用
	* @return 0 没有记录
	* @return >0  读取记录的长度
	*/
	int Retrieve(CFieldDescribe *pFieldDescribe, void *pStruct);
};

/**根据指定的FieldDescribe得到的迭代器
*/
class  CNamedFieldIterator : public CFieldIteratorBase
{
public:
	/**构造函数
	* @param pHead 包内数据的头指针
	* @param pEnd 包内数据的尾指针
	* @param pFieldDescribe 要遍历的域的描述字
	*/
	CNamedFieldIterator(char *pHead, char *pEnd, CFieldDescribe *pFieldDescribe,bool bInSys);
	
	/**从缓冲区中读到一个域中
	* @param field 这个域的引用
	* @return 0 没有记录
	* @return >0  读取记录的长度
	*/
	int Retrieve(void *pStruct);
};

class CFieldSet : public CPackage
{
public:
	CFieldSet();
	virtual ~CFieldSet();

	/**获取一个域
	* @param field 传入一个具体类型的域
	* @return 0 没有记录
	* @return >0  读取记录的长度
	*/
	int GetSingleField(CFieldDescribe *pFieldDescribe, void *pField);
		
	int AddField(CFieldDescribe *pFieldDescribe, const void *pField);
	
	/**根据指定域的描述信息，获取指定域的迭代器
	* @param field 传入具体类型的域的类型指针
	* @return 指定域的迭代器 
	*/
	inline CNamedFieldIterator GetNamedFieldIterator(CFieldDescribe *pFieldDescribe);

	/**获取整个包的迭代器
	* @param field 传入具体类型的域的类型指针
	* @return 指定域的迭代器 
	*/
	inline CFieldTypeIterator GetFieldTypeIterator();
//private:
	/**为某类型的域分配空间
	* @param FieldID  域类型id
	* @param Size 域的长度
	* @return 返回分配后域的地址
	*/
	char * AllocField(WORD wFieldID,WORD wSize);
	void SetType(bool bInSys);
private:
	bool m_bInSys;
};

inline CNamedFieldIterator CFieldSet::GetNamedFieldIterator(CFieldDescribe *pFieldDescribe)
{
	return CNamedFieldIterator(m_pHead, m_pTail, pFieldDescribe,m_bInSys);
}

inline CFieldTypeIterator CFieldSet::GetFieldTypeIterator()
{
	return CFieldTypeIterator(m_pHead, m_pTail,m_bInSys);
}

inline int CFieldSet::AddField(CFieldDescribe *pFieldDescribe, const void *pField)
{
	char *buf = NULL;
	if(m_bInSys)
	{
		buf = AllocField(pFieldDescribe->m_FieldID, pFieldDescribe->m_nStructSize);
	}
	else
	{
		buf = AllocField(pFieldDescribe->m_FieldID, pFieldDescribe->m_nStreamSize);
	}
	if(buf == NULL)
	{
		return -1;
	}
	pFieldDescribe->StructToStream((char *)pField, buf,m_bInSys);
	return 0;
}

void FIELD_DEBUG(char *pData, CFieldDescribe *pFieldDescribe, CLogger *pLogger);
void FIELD_TO_STRING(char *pData, CFieldDescribe *pFieldDescribe, FILE *fp);
#endif // !defined(AFX_FIELDSET_H__83362A2A_0A24_46AE_A788_295CB18F6BF3__INCLUDED_)
