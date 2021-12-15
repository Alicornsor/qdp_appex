// DbmtPackage.cpp: implementation of the CDbmtPackage class.
//
// 20070828 ��ά ������־�ļ���ͷ���
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "DbmtPackage.h"
#include "DbmtRecord.h"

extern DWORD DBMT_PACKAGE_MODE;

CDbmtPackage::CCommandInfoMap CDbmtPackage::m_mapCommandInfo;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDbmtPackage::CDbmtPackage()
{

}

CDbmtPackage::~CDbmtPackage()
{

}

bool CDbmtPackage::AnalysisRecord(const char *pszFieldName, const char *pszFieldContent)
{
	CCommandInfoMap::iterator itor = m_mapCommandInfo.find(m_dbmtHeader.CommandType);
	if (itor == m_mapCommandInfo.end())
	{
		return false;
	}

	CDbmtRecord record;
	if(!record.Analysis(pszFieldName, pszFieldContent))
	{
		return false;
	}
	
	char buf[DBMT_MAX_PACKAGE_SIZE];

	TDbmtCommandInfo *pCommandInfo = (*itor).second;

	if (!record.TransToStruct(pCommandInfo->pFieldDesc, buf))
	{
		REPORT_EVENT(LOG_ERROR, "DbCommand", "Error on analysis [%s]", pCommandInfo->pszCommand);
		
		return false;
	}

	PreparePublish(pCommandInfo->tid);
	//�Ǽǰ������Ϊdbmt
	SetSessionID(DBMT_PACKAGE_MODE);
	//�Ǽ����ΪCommandNo
	SetFrontID(GetCommandNo());
	AddField(pCommandInfo->pFieldDesc, buf);

	return true;
}

void CDbmtPackage::InitCommandInfoMap(TDbmtCommandInfo *pComamndInfo)
{
	while (pComamndInfo->pszCommand != NULL)
	{
		m_mapCommandInfo[pComamndInfo->pszCommand] =  pComamndInfo;
		pComamndInfo++;
	}
}

