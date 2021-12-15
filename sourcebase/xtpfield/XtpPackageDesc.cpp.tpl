// XtpPackageDesc.cpp: 
//
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "XtpPackageDesc.h"

!!enter XTP!!

const char *getPackageName(DWORD tid)
{
	switch (tid)
	{
	!!travel packages!!
	case TID_!!@name!!:
		return "!!@name!!";
	!!next!!
	}
	return "unknown";
}

!!travel packages!!
TFieldUse !!@name!!FieldUse[]=
{
	!!travel self!!
		!!if @pumpid!=0!!
			,
		!!endif!!
		{ FID_!!@name!!, &C!!@name!!Field::m_Describe, !!@minOccur!!, !!if !strcmp(@maxOccur,"*")!! UNLIMITED_FIELD_OCCUR !!else!! !!@maxOccur!! !!endif!! }
	!!next!!
};

!!next!!

TPackageDefine XTPPackageDefines[]=
{
!!travel packages!!
	!!if @pumpid!=0!!
		,
	!!endif!!
	{ TID_!!@name!!, !!@son_size!!, !!@name!!FieldUse, "!!@name!!", "!!@comment!!" }
!!next!!
};

!!leave!!

CXTPPackageDefineMap g_XTPPackageDefineMap(XTPPackageDefines, sizeof(XTPPackageDefines)/ sizeof(TPackageDefine));

void XTP_DEBUG_BODY(DWORD tid, CFieldSet *pPackage, CLogger *pLogger)
{
	pLogger->output(LL_DEBUG, "\tXTP PACKAGE CONTENT START\n");					
	TPackageDefine **pFind = g_XTPPackageDefineMap.Find(tid);	
	if(pFind == NULL)													
	{																	
		pLogger->output(LL_DEBUG, "\tCan't find package define [%08x]\n", tid);				
		return;															
	}																	
	char buf[10000];													
	TPackageDefine *pPackageDefine = *pFind;							
	CFieldTypeIterator itor = pPackage->GetFieldTypeIterator();			
	while(!itor.IsEnd())												
	{																	
		TFieldHeader fieldHeader;										
		itor.RetrieveHeader(fieldHeader);								
		TFieldUse *pFieldUse = pPackageDefine->fieldUse;				
		for(int i=0; i<pPackageDefine->fieldUseCount; i++)				
		{																
			if(pFieldUse->fid == fieldHeader.FieldID)					
			{															
				itor.Retrieve(pFieldUse->pFieldDescribe, buf);			
				FIELD_DEBUG(buf, pFieldUse->pFieldDescribe, pLogger);	
				break;													
			}															
			pFieldUse++;												
		}																
		itor.Next();													
	}																	
	pLogger->output(LL_DEBUG, "\tXTP PACKAGE CONTENT END\n");						
}
