// DbmtRecord.cpp: implementation of the CDbmtRecord class.
//
// 20061030 王维 修改BUG：DBMT不应将浮点数NULL转换成0
// 20070828 王维 调整日志的级别和分类
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "DbmtRecord.h"
#include "CSVParser.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDbmtRecord::CDbmtRecord()
{
	m_nNameBufferLen = 0;
	m_nContentBufferLen = 0;
}

CDbmtRecord::~CDbmtRecord()
{

}

bool CDbmtRecord::Analysis(const char *pszFieldName, const char *pszFieldContent)
{
	if (!AnalysisFieldName(pszFieldName))
	{
		return false;
	}
	return AnalysisFieldContent(pszFieldContent);
}

char *CDbmtRecord::AppendNameToken(const char *pszToken)
{
	int nTokenLen = strlen(pszToken) + 1;
	char *pszTarget = m_chNameBuffer+m_nNameBufferLen;
	memcpy(m_chNameBuffer+m_nNameBufferLen, pszToken, nTokenLen);
	m_nNameBufferLen += nTokenLen;
	return pszTarget;
}

char *CDbmtRecord::AppendContentToken(const char *pszToken)
{
	int nTokenLen = strlen(pszToken) + 1;
	char *pszTarget = m_chContentBuffer+m_nContentBufferLen;
	memcpy(m_chContentBuffer+m_nContentBufferLen, pszToken, nTokenLen);
	m_nContentBufferLen += nTokenLen;
	return pszTarget;
}

bool CDbmtRecord::AnalysisFieldName(const char *pszFieldName)
{
	m_nNameBufferLen = 0;
	m_dbmtFields.clear();
	m_mapDbmtField.clear();
	
	CCSVParser csvParser(pszFieldName);
	TDbmtField field = {NULL, NULL};

	do
	{
		char *pszToken = csvParser.GetNextToken();
		if (pszToken == NULL)
		{
			break;
		}
		field.pFieldName = AppendNameToken(pszToken);
		m_dbmtFields.push_back(field);
	}while (csvParser.GetErrorCode() == CPE_HAS_NEXT);

	return true;
}

bool CDbmtRecord::AnalysisFieldContent(const char *pszFieldContent)
{
	m_nContentBufferLen = 0;
	
	CCSVParser csvParser(pszFieldContent);
	for (int i=0; i<m_dbmtFields.size(); i++)
	{
		char *pszToken = csvParser.GetNextToken();
		if (pszToken == NULL)
		{
			break;
		}
		m_dbmtFields[i].pFieldContent = AppendContentToken(pszToken);
		m_mapDbmtField[m_dbmtFields[i].pFieldName] = m_dbmtFields[i].pFieldContent;
	}

	return true;
}

const char * CDbmtRecord::GetFieldAsString(const char *pszFieldName)
{
	CDbmtFieldMap::iterator itor = m_mapDbmtField.find(pszFieldName);
	if (itor == m_mapDbmtField.end())
	{
		return NULL;
	}

	return (*itor).second;
}

int CDbmtRecord::GetFieldAsInt(const char *pszFieldName)
{
	const char *pszFieldContent = GetFieldAsString(pszFieldName);
	if (pszFieldContent == NULL)
	{
		return 0;
	}
	return atoi(pszFieldContent);
}

double CDbmtRecord::GetFieldAsDouble(const char *pszFieldName)
{
	const char *pszFieldContent = GetFieldAsString(pszFieldName);
	if (pszFieldContent == NULL)
	{
		return DOUBLE_NaN;
	}
	if (*pszFieldContent == '\0')
	{
		return DOUBLE_NaN;
	}
	
	return atof(pszFieldContent);
}

bool CDbmtRecord::TransToStruct(CFieldDescribe *pFieldDesc, char *pBuffer)
{
	for (int i=0; i<pFieldDesc->GetMemberCount(); i++)
	{
		TMemberDesc *pMemberDesc = pFieldDesc->GetMemberDesc(i);
		if (GetFieldAsString(pMemberDesc->szName) == NULL)
		{
			REPORT_EVENT(LOG_ERROR, "DbCommand", "Can't find field[%s] MemTable [%s]", pMemberDesc->szName,pFieldDesc->GetFieldName() );
			return false;
		}
		char *pMember = pBuffer+pMemberDesc->nStructOffset;
//		printf("%d %s\n", pMemberDesc->nType, pMemberDesc->szName);
		switch(pMemberDesc->nType)
		{
		case FT_WORD:
			*((WORD *)pMember) = (WORD)GetFieldAsInt(pMemberDesc->szName);
			break;
		case FT_DWORD:			
			*((DWORD *)pMember) = (DWORD)GetFieldAsInt(pMemberDesc->szName);
			break;
		case FT_BYTE:
			memset(pMember, 0, pMemberDesc->nSize);
			memcpy(pMember, GetFieldAsString(pMemberDesc->szName),
				pMemberDesc->nSize);

			if (pMemberDesc->nSize != 1)
			{
				pMember[pMemberDesc->nSize-1] = '\0';
				char *p = pMember + strlen(pMember);
				while(p > pMember)
				{
					p--;
					if (*p != ' ')
					{
						break;
					}
					*p = '\0';
				}
			}
			break;
		case FT_REAL4:
			*((REAL4 *)pMember) = (REAL4)GetFieldAsDouble(pMemberDesc->szName);
			break;
		case FT_REAL8:
			{
				REAL8 r = (REAL8)GetFieldAsDouble(pMemberDesc->szName);
				memcpy(pMember, &r, sizeof(REAL8));
			}
			break;
		}		
		
	}

	return true;
}

#if 0
int main()
{
	char *pszFieldName = "name,age,money";
	char *pszFieldContent = "\"peter pan\",\"20\",\"123.5\"";
	CDbmtRecord record;
	if (!record.Analysis(pszFieldName, pszFieldContent))
	{
		printf("Analysis fail\n");
		return -1;
	}

	int i = 0;
	for (i=1; i<=record.GetFieldCount(); i++)
	{
		printf("[%s] : [%s]\n", record.GetFieldName(i), record.GetFieldContent(i));
	}
	
	printf("name = [%s]\n", record.GetFieldAsString("name"));
	printf("age = [%d]\n", record.GetFieldAsInt("age"));
	printf("money = [%lf]\n", record.GetFieldAsDouble("money"));

	printf("error str = [%s]\n", record.GetFieldAsString("error str"));
	printf("error int = [%d]\n", record.GetFieldAsInt("error int"));
	printf("error double = [%lf]\n", record.GetFieldAsDouble("error double"));

	return 0;
}
#endif