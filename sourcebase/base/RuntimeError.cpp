//**********************************************************************
//文件名：CRuntimeError.h
//主要功能:实现了类CRuntimeError
//修改历史：
//**********************************************************************

#include "CBaseObject.h"

CRuntimeError::CRuntimeError(char *pszMsg, char *pszFile, int nLineNo)
{
	m_pszMsg = new char[strlen(pszMsg)+1];
	strcpy(m_pszMsg, pszMsg);
	m_pszFile = pszFile;
	m_nLineNo = nLineNo;
}

CRuntimeError::~CRuntimeError()
{
	delete m_pszMsg;
}

char *CRuntimeError::GetMsg(void)
{
	return m_pszMsg;
}

char *CRuntimeError::GetFile(void)
{
	return m_pszFile;
}

int CRuntimeError::GetLineNo(void)
{
	return m_nLineNo;
}
