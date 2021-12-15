// FieldDescribe.cpp: implementation of the CFieldDescribe class.
//
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "FieldDescribe.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFieldDescribe::CFieldDescribe(WORD FieldID, int nStructSize, const char *pszFieldName, const char *pszComment, describeFunc func)
{
	m_FieldID = FieldID;
	strcpy(m_szFieldName, pszFieldName);
	strcpy(m_szComment, pszComment);
	m_nStructSize = nStructSize;
	m_nStreamSize = 0;
	m_nTotalMember = 0;
	func();
}

CFieldDescribe::~CFieldDescribe()
{

}

void ChangeEndianCopy2(char *pTarget, char *pSource)
{
	pTarget[1] = pSource[0];
	pTarget[0] = pSource[1];
}

void ChangeEndianCopy4(char *pTarget, char *pSource)
{
	pTarget[3] = pSource[0];
	pTarget[2] = pSource[1];
	pTarget[1] = pSource[2];
	pTarget[0] = pSource[3];
}

void ChangeEndianCopy8(char *pTarget, char *pSource)
{
	pTarget[7] = pSource[0];
	pTarget[6] = pSource[1];
	pTarget[5] = pSource[2];
	pTarget[4] = pSource[3];
	pTarget[3] = pSource[4];
	pTarget[2] = pSource[5];
	pTarget[1] = pSource[6];
	pTarget[0] = pSource[7];
}

/**将对象转换为字节流
* @param pStruct 要转换的对象
* @param pStream 转换出的字节流
* @remark 字节流中的成员变量是高位在前
*/
void CFieldDescribe::StructToStream(char *pStruct,char *pStream,bool bInSys)
{
	if(bInSys)
	{
		memcpy(pStream,pStruct,m_nStructSize);
		return;
	}
	for(int i=0;i<m_nTotalMember;i++){
		TMemberDesc *p=&m_MemberDesc[i];
#ifndef _BIG_ENDIAN_						//低位在前
		switch(p->nType){
		case FT_WORD:						//short
			ChangeEndianCopy2(pStream+p->nStreamOffset, pStruct+p->nStructOffset);
			break;
		case FT_DWORD:						//long
		case FT_REAL4:
			ChangeEndianCopy4(pStream+p->nStreamOffset, pStruct+p->nStructOffset);
			break;
		case FT_REAL8:						//double
		case FT_LONG:						//long 64bit
			ChangeEndianCopy8(pStream+p->nStreamOffset, pStruct+p->nStructOffset);
			break;
		case FT_BYTE:
			// memset(pStream+p->nStreamOffset,0,p->nSize);
			memcpy(pStream+p->nStreamOffset,pStruct+p->nStructOffset,p->nSize);
			break;
		}
#else										//高位在前
		//add by zbz
		//memset(pStream+p->nStreamOffset,0,p->nSize);
		memcpy(pStream+p->nStreamOffset,pStruct+p->nStructOffset,p->nSize);
#endif
	}
}

/**将字节流转换为对象
* @param pStruct 转换的出对象
* @param pStream 要转换的字节流
* @remark 字节流中的成员变量必须是高位在前
*/
void CFieldDescribe::StreamToStruct(char *pStruct,char *pStream,bool bInSys)
{
	if(bInSys)
	{
		memcpy(pStruct,pStream,m_nStructSize);
		return;
	}
	for(int i=0;i<m_nTotalMember;i++){
		TMemberDesc *p=&m_MemberDesc[i];
#ifndef _BIG_ENDIAN_						//低位在前
		switch(p->nType){
		case FT_WORD:						//short
			ChangeEndianCopy2(pStruct+p->nStructOffset, pStream+p->nStreamOffset);
			break;
		case FT_DWORD:						//long
		case FT_REAL4:
			ChangeEndianCopy4(pStruct+p->nStructOffset, pStream+p->nStreamOffset);
			break;
		case FT_REAL8:						//double
		case FT_LONG:						//long 64bit
			ChangeEndianCopy8(pStruct+p->nStructOffset, pStream+p->nStreamOffset);
			break;
		case FT_BYTE:
			memcpy(pStruct+p->nStructOffset,pStream+p->nStreamOffset,p->nSize);
			break;
		}
#else										//高位在前
		memcpy(pStruct+p->nStructOffset,pStream+p->nStreamOffset,p->nSize);
#endif
	}
}


