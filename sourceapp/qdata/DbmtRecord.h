// DbmtRecord.h: interface for the CDbmtRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBMTRECORD_H__031FB628_F06A_40A6_BC49_ECDA4FBEF91E__INCLUDED_)
#define AFX_DBMTRECORD_H__031FB628_F06A_40A6_BC49_ECDA4FBEF91E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FieldDescribe.h"

const int DBMT_RECORD_MAX_SIZE = 4096;

class CDbmtRecord  
{
public:
	CDbmtRecord();
	virtual ~CDbmtRecord();
	bool Analysis(const char *pszFieldName, const char *pszFieldContent);
	inline int GetFieldCount();
	inline const char *GetFieldName(int nIndex);
	inline const char *GetFieldContent(int nIndex);

	bool AnalysisFieldName(const char *pszFieldName);
	bool AnalysisFieldContent(const char *pszFieldContent);

	bool TransToStruct(CFieldDescribe *pFieldDesc, char *pBuffer);

	const char *GetFieldAsString(const char *pszFieldName);
	int GetFieldAsInt(const char *pszFieldName);
	double GetFieldAsDouble(const char *pszFieldName);
private:
	char *AppendNameToken(const char *pszToken);
	char *AppendContentToken(const char *pszToken);
private:
	struct TDbmtField
	{
		char *pFieldName;
		char *pFieldContent;
	};

	vector<TDbmtField> m_dbmtFields;

	struct ltstr
	{
	  bool operator()(const char* s1, const char* s2) const
	  {
		return strcmp(s1, s2) < 0;
	  }
	};
	typedef map<const char*, const char *, ltstr> CDbmtFieldMap;
	CDbmtFieldMap m_mapDbmtField;

	char m_chNameBuffer[DBMT_RECORD_MAX_SIZE];
	int m_nNameBufferLen;
	char m_chContentBuffer[DBMT_RECORD_MAX_SIZE];
	int m_nContentBufferLen;
};

inline int CDbmtRecord::GetFieldCount()
{
	return m_dbmtFields.size();
}

inline const char * CDbmtRecord::GetFieldName(int nIndex)
{
	return m_dbmtFields[nIndex-1].pFieldName;
}

inline const char * CDbmtRecord::GetFieldContent(int nIndex)
{
	return m_dbmtFields[nIndex-1].pFieldContent;
}

#endif // !defined(AFX_DBMTRECORD_H__031FB628_F06A_40A6_BC49_ECDA4FBEF91E__INCLUDED_)
