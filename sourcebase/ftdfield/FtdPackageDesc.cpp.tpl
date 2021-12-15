// FtdPackageDesc.cpp: 
//
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "FtdPackageDesc.h"
#include "HashMap.h"

!!enter FTD!!
!!travel packages!!
TFieldUse !!@head!!!!@name!!FieldUse[]=
{
	!!travel self!!
		!!if @pumpid!=0!!
			,
		!!endif!!
		{ !!@head!!_FID_!!@name!!, &(CFTD!!@name!!Field::m_Describe), !!@minOccur!!, !!if !strcmp(@maxOccur,"*")!! UNLIMITED_FIELD_OCCUR !!else!! !!@maxOccur!! !!endif!! }
	!!next!!
};

!!next!!

TPackageDefine FTDPackageDefines[]=
{
!!travel packages!!
	!!if @pumpid!=0!!
		,
	!!endif!!
	{ !!@head!!_TID_!!@name!!, !!@son_size!!, !!@head!!!!@name!!FieldUse }
!!next!!
};

!!leave!!


class CFTDCPackageDefineMap: public CHashMap<DWORD, TPackageDefine *, HashInt>
{
public:
	CFTDCPackageDefineMap(TPackageDefine *pFTDCPackageDefines, int nDefineCount)
	{
		for(int i=0; i<nDefineCount; i++)
		{
			Insert(pFTDCPackageDefines->tid, pFTDCPackageDefines);
			pFTDCPackageDefines++;
		}
	}
};

CFTDCPackageDefineMap g_FTDCPackageDefineMap(FTDPackageDefines, sizeof(FTDPackageDefines)/ sizeof(TPackageDefine));

void FTDC_DEBUG_BODY(DWORD tid, CFieldSet *pPackage, CLogger *pLogger)
{
	pLogger->output("\tFTDC PACKAGE CONTENT START\n");					
	TPackageDefine **pFind = g_FTDCPackageDefineMap.Find(tid);	
	if(pFind == NULL)													
	{																	
		pLogger->output("\tCan't find package define [0x%08x]\n", tid);				
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
	pLogger->output("\tFTDC PACKAGE CONTENT END\n");						
}
