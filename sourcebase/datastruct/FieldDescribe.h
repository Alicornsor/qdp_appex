// FieldDescribe.h: interface for the CFieldDescribe class .
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELDDESCRIBE_H__1E41C27A_C6C8_4820_94AF_1581CE41F7C7__INCLUDED_)
#define AFX_FIELDDESCRIBE_H__1E41C27A_C6C8_4820_94AF_1581CE41F7C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UFDataType.h"
//add zbz 有原来的最多50个字段扩展为80个字段
#define MAX_MEMB				80
#define MAX_FIELD_NAME_LEN		100

/**每种数据类型的标示符
*/
enum MemberType{
	FT_BYTE,
	FT_WORD,
	FT_DWORD,
	FT_REAL4,
	FT_REAL8,
	FT_LONG,
};

/**类成员属性结构
*/
struct TMemberDesc{
	MemberType nType;			/**<成员类型*/
	int nStructOffset;			/**<成员在类中的偏移量*/
	int nStreamOffset;			/**<成员在字节流中的偏移量*/
	int nSize;					/**<成员长度*/
	char szName[30];			/**<成员名称*/
};

#define DEF_SETUP_MEMBER(type,id) 	void SetupMember(type &,int offset,char *name,int length){	SetupMember(id,offset,name,length); }
	
/**域的描述类
*/
class  CFieldDescribe  
{
public:
    typedef void (*describeFunc)(); /**< 定义一个指针函数类型 */
    	
	/**构造函数，并执行传进的指针函数
	* @param FieldID 域ID
	* @param nStructSize 域大小
	* @param pszFieldName 域名
	* @param pszComment 域说明
	* @param func    指向一个函数的指针
	*/
	CFieldDescribe(WORD FieldID, int nStructSize, const char *pszFieldName, const char *pszComment, describeFunc func);

	/**析构函数
	*/
	~CFieldDescribe();
public:
	/**填充类型INT1类型Id FT_BYTE的对照表的方法
	*/	
	DEF_SETUP_MEMBER(CUFBaseCharType,FT_BYTE);
	
	/**填充类型INT2类型Id FT_WORD的对照表的方法
	*/
	//DEF_SETUP_MEMBER(INT2,FT_WORD);
	
	/**填充类型INT4类型Id FT_DWORD的对照表的方法
	*/
	DEF_SETUP_MEMBER(CUFBaseIntType,FT_DWORD);
	
	/**填充类型INT8类型Id FT_LONG的对照表的方法
	*/
	DEF_SETUP_MEMBER(CUFBaseLongType,FT_LONG);

	/**填充类型BYTE类型Id FT_BYTE的对照表的方法
	*/
	//DEF_SETUP_MEMBER(BYTE,FT_BYTE);
	
	/**填充类型WORD类型Id FT_WORD的对照表的方法
	*/
	DEF_SETUP_MEMBER(CUFBaseWordType,FT_WORD);
	
	/**填充类型DWORD类型Id FT_DWORD的对照表的方法
	*/
	//DEF_SETUP_MEMBER(DWORD,FT_DWORD);
	
	/**填充类型REAL4类型Id FT_REAL4的对照表的方法
	*/
	//DEF_SETUP_MEMBER(REAL4,FT_REAL4);
	
	/**填充类型REAL8类型Id FT_REAL8的对照表的方法
	*/
	DEF_SETUP_MEMBER(CUFBaseFloatType,FT_REAL8);
	
	/**填充类型BYTEARRAY类型Id FT_BYTE的对照表的方法
	*/
	DEF_SETUP_MEMBER(CUFBaseStringType,FT_BYTE);

	/**将对象转换为字节流
	* @param pStruct 要转换的对象
	* @param pStream 转换出的字节流
	* @remark 字节流中的成员变量是高位在前
	*/
	void StructToStream(char *pStruct,char *pStream,bool bInSys=false);

	/**将字节流转换为对象
	* @param pStruct 转换的出对象
	* @param pStream 要转换的字节流
	* @remark 字节流中的成员变量必须是高位在前
	*/
	void StreamToStruct(char *pStruct,char *pStream,bool bInSys=false);
	
	/**获取域大小
	* @return 返回域大小
	*/	
	inline int GetStructSize();
	
	/**获取类转换成的字节流长度
	* @return 返回类转换成的字节流长度
	*/	
	inline int GetStreamSize();

	/**类成员个数
	* @return 返回类成员个数
	*/
	inline int GetMemberCount();
	
	/**获取域中每个成员的描述
	* @param index 成员在描述对照表中的位置
	* @return 返回成员描述
	*/
	inline TMemberDesc *GetMemberDesc(int index);

	/**获取域的名称
	* @return 域的名称
	*/
	inline const char *GetFieldName();
private:

	/**填充类型和类型Id对照表
	* @param nType 成员类型
	* @param nStructOffset 成员在类中的偏移量
	* @param nSize 成员长度
	* @param szName 成员名称
	*/
	inline void SetupMember(MemberType nType,int nStructOffset,char *szName,int nSize);
public:
	WORD m_FieldID;			/**<域ID */
	char m_szComment[MAX_FIELD_NAME_LEN];		/**<域注释 */
	int m_nStructSize;			/**<域大小*/
	int m_nStreamSize;			/**<域转换成的字节流长度*/
private:
	int m_nTotalMember;			/**<域成员个数*/
	char m_szFieldName[MAX_FIELD_NAME_LEN];
	TMemberDesc m_MemberDesc[MAX_MEMB];	/**<域成员属性数组*/

};

inline void CFieldDescribe::SetupMember(MemberType nType,int nStructOffset,
		char *szName,int nSize)
{
	TMemberDesc *p=&m_MemberDesc[m_nTotalMember];
	p->nType=nType;
	p->nStructOffset=nStructOffset;
	p->nStreamOffset=m_nStreamSize;
	p->nSize=nSize;
	strcpy(p->szName,szName);

	m_nStreamSize+=nSize;
	m_nTotalMember++;
}

inline int CFieldDescribe::GetStructSize()
{
	return m_nStructSize;
}

inline int CFieldDescribe::GetStreamSize()
{
	return m_nStreamSize;
}

inline int CFieldDescribe::GetMemberCount()
{
	return m_nTotalMember;
}

inline TMemberDesc * CFieldDescribe::GetMemberDesc(int index)
{
	return &m_MemberDesc[index];
}

inline const char *CFieldDescribe::GetFieldName()
{
	return m_szFieldName;
}

#define TYPE_DESCRIPTOR(members) void DescribeMembers() { members; } static CFieldDescribe m_Describe 

#define TYPE_DESC(member) m_Describe.SetupMember(member,(char *)&member-(char *)this,#member,sizeof(member))

#define REGISTER_FIELD(fid,field, comment)   static void DescribeMemberOf##field() { field f; f.DescribeMembers(); } CFieldDescribe field::m_Describe(fid,sizeof(field),#field,comment,&DescribeMemberOf##field)

#endif // !defined(AFX_FIELDDESCRIBE_H__1E41C27A_C6C8_4820_94AF_1581CE41F7C7__INCLUDED_)
