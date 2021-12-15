// XtpPackageDesc.h: 
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XTPPACKAGEDESC_H__EA501ADE_818C_4F9A_8738_AC9CCAF0B941__INCLUDED_)
#define AFX_XTPPACKAGEDESC_H__EA501ADE_818C_4F9A_8738_AC9CCAF0B941__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XtpData.h"
#include "HashMap.h"
#include "FieldSet.h"

!!enter XTP!!
!!travel packages!!
//!!@comment!!
const DWORD TID_!!@name!!=!!@tid!!;
!!next!!

///获取报单的名称
///@param	tid	报单编号
///@return	报单名称
const char *getPackageName(DWORD tid);

#ifndef FIELD_USE_DEFINE
#define FIELD_USE_DEFINE

#define UNLIMITED_FIELD_OCCUR 1000
#define MAX_PACKAGE_NAME_LEN		100
#define MAX_COMMENT_LEN		100
typedef struct
{
	DWORD fid;
	CFieldDescribe *pFieldDescribe;
	int minOccur;
	int maxOccur;
}	TFieldUse;

typedef struct
{
	DWORD tid;
	int fieldUseCount;
	TFieldUse *fieldUse;
	char packageName[MAX_PACKAGE_NAME_LEN];
	char comment[MAX_COMMENT_LEN];
}	TPackageDefine;

#endif

extern TPackageDefine XTPPackageDefines[];

class CXTPPackageDefineMap: public CHashMap<DWORD, TPackageDefine *, HashInt>
{
public:
	CXTPPackageDefineMap(TPackageDefine *pXTPPackageDefines, int nDefineCount)
	{
		for(int i=0; i<nDefineCount; i++)
		{
			Insert(pXTPPackageDefines->tid, pXTPPackageDefines);
			pXTPPackageDefines++;
		}
	}
};

extern CXTPPackageDefineMap g_XTPPackageDefineMap;
void XTP_DEBUG_BODY(DWORD tid, CFieldSet *pPackage, CLogger *pLogger);
#endif
