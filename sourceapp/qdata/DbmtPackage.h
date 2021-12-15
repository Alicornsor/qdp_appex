// DbmtPackage.h: interface for the CDbmtPackage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBMTPACKAGE_H__7CA8AE45_64B2_4937_A07C_30E621E29BE1__INCLUDED_)
#define AFX_DBMTPACKAGE_H__7CA8AE45_64B2_4937_A07C_30E621E29BE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPPackage.h"
#include "FieldDescribe.h"
#include "customDataType.h"

struct TDbmtCommandInfo
{
	char *pszCommand;
	DWORD tid;
	CFieldDescribe *pFieldDesc;
};
// 
struct TDbmtPackageHeader
{
	CCommandNoType CommandNo;
	CCommandTypeType CommandType;
	TYPE_DESCRIPTOR((
		TYPE_DESC(CommandNo)
		,
		TYPE_DESC(CommandType)
	));
};

#define DBMTHLEN sizeof(TDbmtPackageHeader)
#define DBMT_MAX_PACKAGE_SIZE	10000

class CDbmtPackage : public CXTPPackage  
{
public:
	CDbmtPackage();
	virtual ~CDbmtPackage();

	static void InitCommandInfoMap(TDbmtCommandInfo *pComamndInfo);

	inline CCommandNoType &GetCommandNo();
	inline void SetCommandNo(const CCommandNoType &CommandNo);
	inline CCommandTypeType &GetCommandType();
	inline void SetCommandType(const CCommandTypeType &CommandType);
	bool AnalysisRecord(const char *pszFieldName, const char *pszFieldContent);
private:
	TDbmtPackageHeader m_dbmtHeader;
	
	struct ltstr
	{
		bool operator()(const char* s1, const char* s2) const
		{
			return strcmp(s1, s2) < 0;
		}
	};	

	typedef map<const char *, TDbmtCommandInfo *, ltstr> CCommandInfoMap;
	static CCommandInfoMap m_mapCommandInfo;
};

inline CCommandNoType &CDbmtPackage::GetCommandNo()
{
	return m_dbmtHeader.CommandNo;
}

inline void CDbmtPackage::SetCommandNo(const CCommandNoType &CommandNo)
{
	m_dbmtHeader.CommandNo = CommandNo;
}

inline CCommandTypeType &CDbmtPackage::GetCommandType()
{
	return m_dbmtHeader.CommandType;
}

inline void CDbmtPackage::SetCommandType(const CCommandTypeType &CommandType)
{
	m_dbmtHeader.CommandType = CommandType;
	m_dbmtHeader.CommandType.trimRight();
}

#endif // !defined(AFX_DBMTPACKAGE_H__7CA8AE45_64B2_4937_A07C_30E621E29BE1__INCLUDED_)
