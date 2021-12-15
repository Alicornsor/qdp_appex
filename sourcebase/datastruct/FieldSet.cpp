// FieldSet.cpp: implementation of the CFieldSet class.
//
// 20070806 赵鸿昊 增加FIELD_TO_STRING方法，将一个field转换成一行文本输出
// 20070827 赵鸿昊 修正CFieldIteratorBase未进行指针越界检查，无法应付错误报文的问题
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "FieldSet.h"

//////////////////////////////////////////////////////////////////////
CFieldIteratorBase::CFieldIteratorBase(char *pHead, char *pEnd, CFieldDescribe *pFieldDescribe)
{
	m_pData = NULL;
	m_pCurr = pHead;
	m_pEnd = pEnd;
	m_pFieldDescribe = pFieldDescribe;
	
	Next();
};
	
void CFieldIteratorBase::Next()
{
	m_pData = NULL;
	while (m_pData == NULL)
	{
		if(DataRemain() < sizeof(TFieldHeader))
		{
			break;
		}
		GetHeader();
		m_pCurr += sizeof(TFieldHeader);
		
		if(DataRemain() < m_fieldHeader.Size)
		{
			break;
		} 
		if (m_pFieldDescribe==NULL || m_fieldHeader.FieldID == m_pFieldDescribe->m_FieldID) 
		{
			m_pData = m_pCurr;
		}
		m_pCurr += m_fieldHeader.Size;
	}
}
//////////////////////////////////////////////////////////////////////
CNamedFieldIterator::CNamedFieldIterator(char *pHead, char *pEnd, CFieldDescribe *pFieldDescribe,bool bInSys)
:CFieldIteratorBase(pHead, pEnd, pFieldDescribe)
{
	m_bInSys = bInSys;
}

int CNamedFieldIterator::Retrieve(void *pStruct)
{
	if(m_pData == NULL)
	{
		return 0;
	}
	
	m_pFieldDescribe->StreamToStruct((char *)pStruct, m_pData,m_bInSys);
	if(m_bInSys)
	{
			return m_pFieldDescribe->GetStructSize();
	}
	else
	{
			return m_pFieldDescribe->GetStreamSize();
	}
}
//////////////////////////////////////////////////////////////////////
CFieldTypeIterator::CFieldTypeIterator(char *pHead, char *pEnd,bool bInSys)
:CFieldIteratorBase(pHead, pEnd, NULL)
{
	m_bInSys = bInSys;
}

int CFieldTypeIterator::Retrieve(CFieldDescribe *pFieldDescribe, void *pStruct)
{
	if(m_pData == NULL)
	{
		return 0;
	}
	
	pFieldDescribe->StreamToStruct((char *)pStruct, m_pData,m_bInSys);

	if(m_bInSys)
	{
			return pFieldDescribe->GetStructSize();
	}
	else
	{
			return pFieldDescribe->GetStreamSize();
	}
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFieldSet::CFieldSet()
{
	m_bInSys = false;
}

CFieldSet::~CFieldSet()
{

}

int CFieldSet::GetSingleField(CFieldDescribe *pFieldDescribe, void *pField)
{
	CNamedFieldIterator itor = GetNamedFieldIterator(pFieldDescribe);
	if (itor.IsEnd())
	{
		return 0;
	}
	return itor.Retrieve(pField);
}

//只分配了空间
char * CFieldSet::AllocField(WORD wFieldID, WORD wSize)
{
	//新域加入后，包长不能超过缓冲区的长度
	if (m_pTail+wSize+sizeof(TFieldHeader) >= 
		m_pPackageBuffer->Data()+m_pPackageBuffer->Length()) 
	{
		return NULL;
	}

	TFieldHeader fh;
	fh.FieldID = wFieldID;
	fh.Size = wSize;
	CHANGE_ENDIAN(fh.FieldID);
	CHANGE_ENDIAN(fh.Size);

	memcpy(m_pTail, &fh, sizeof(fh));

	char *pBuf = m_pTail + sizeof(TFieldHeader);
	m_pTail += sizeof(TFieldHeader) + wSize;
	return pBuf;
}
void CFieldSet::SetType(bool bInSys)
{
	m_bInSys = bInSys;
}
void FIELD_DEBUG(char *pData, CFieldDescribe *pFieldDescribe, CLogger *pLogger)
{
	pLogger->output(LL_DEBUG, "\tFIELD [%s] START\n", pFieldDescribe->GetFieldName());  
	for (int i=0; i<pFieldDescribe->GetMemberCount(); i++)
	{
		TMemberDesc *pMemberDesc=pFieldDescribe->GetMemberDesc(i);
		pLogger->output(LL_DEBUG, "\t\t\t[%s][%d]",pMemberDesc->szName, pMemberDesc->nType&0xFF);
		char *pMember = pData+pMemberDesc->nStructOffset;
		switch(pMemberDesc->nType)
		{
		case FT_WORD:
			pLogger->output(LL_DEBUG, "[%d]\n", *((WORD *)pMember)&0xFFFF);
			break;
		case FT_DWORD:			
			pLogger->output(LL_DEBUG, "[%d]\n", *((DWORD *)pMember));
			break;
		case FT_BYTE:
			if (pMemberDesc->nSize == 1)
			{
				pLogger->output(LL_DEBUG, "[%d]\n", *pMember&0xFF);
			}
			else
			{
				pLogger->output(LL_DEBUG, "[%s]\n", pMember);
			}
			break;
		case FT_REAL4:
			pLogger->output(LL_DEBUG, "[%f]\n",*((REAL4 *)pMember));
			break;
		case FT_REAL8:
			{
				double d;
				memcpy(&d, pMember, sizeof(REAL8));
				if (d == DOUBLE_NaN)
				{
					pLogger->output(LL_DEBUG, "[]\n");
				}
				else
				{
					pLogger->output(LL_DEBUG, "[%lf]\n",d);
				}
			}
			break;
		}		
	}	
	pLogger->output(LL_DEBUG, "\tFIELD [%s] END\n", pFieldDescribe->GetFieldName());  
}

void FIELD_TO_STRING(char *pData, CFieldDescribe *pFieldDescribe, FILE *fp)
{
	fprintf(fp, "[%s,", pFieldDescribe->GetFieldName());
	for (int i=0; i<pFieldDescribe->GetMemberCount(); i++)
	{
		TMemberDesc *pMemberDesc=pFieldDescribe->GetMemberDesc(i);
		fprintf(fp, "%s,", pMemberDesc->szName);
		char *pMember = pData+pMemberDesc->nStructOffset;
		switch(pMemberDesc->nType)
		{
		case FT_WORD:
			fprintf(fp, "%d", *((WORD *)pMember)&0xFFFF);
			break;
		case FT_DWORD:			
			fprintf(fp, "%ld", *((DWORD *)pMember));
			break;
		case FT_BYTE:
			if (pMemberDesc->nSize == 1)
			{
				if (isprint(*pMember&0xFF))
				{
					fprintf(fp, "%c", *pMember&0xFF);
				}
			}
			else
			{
				fprintf(fp, "%s", pMember);
			}
			break;
		case FT_REAL4:
			fprintf(fp, "%f",*((REAL4 *)pMember));
			break;
		case FT_REAL8:
			{
				double d;
				memcpy(&d, pMember, sizeof(REAL8));
				if (d != DOUBLE_NaN)
				{
					fprintf(fp, "%lf,",d);
				}
			}
			break;
		}
		if (i != pFieldDescribe->GetMemberCount()-1)
		{
			fprintf(fp, ",");
		}
	}		
	fprintf(fp, "]");
}
