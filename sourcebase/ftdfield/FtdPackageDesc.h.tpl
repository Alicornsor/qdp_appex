// FtdPackageDesc.h: 
//
//////////////////////////////////////////////////////////////////////

#if !defined(_FTDPACKAGEDESC_H)
#define _FTDPACKAGEDESC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FtdData.h"
#include "FieldSet.h"

!!enter FTD!!

#define FTD_VERSION !!@version!!

!!travel flows!!
const WORD TSS_!!@name!! = !!@seqseries!!;		//!!@comment!!
!!next!!


!!travel packages!!
//!!@comment!!
const DWORD !!@head!!_TID_!!@name!!=!!@tid!!;
!!next!!

#ifndef FIELD_USE_DEFINE
#define FIELD_USE_DEFINE

#define UNLIMITED_FIELD_OCCUR 1000

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
}	TPackageDefine;

#endif

extern TPackageDefine FTDPackageDefines[];

void FTDC_DEBUG_BODY(DWORD tid, CFieldSet *pPackage, CLogger *pLogger);

#endif
