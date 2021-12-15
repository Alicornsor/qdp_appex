//**********************************************************************
//系统名：上海期货交易所系统改造
//公司名：上海复旦金仕达计算机有限公司
//文件名：CDesignError.h
//主要功能:实现了类CDesignError
//修改历史：
//20020214	xuzh		创建该文件
//**********************************************************************

#include "CBaseObject.h"

CDesignError::CDesignError(char *pszMsg, char *pszFile, int nLineNo)
{
	m_pszMsg = new char[strlen(pszMsg)+1];
	strcpy(m_pszMsg, pszMsg);
	m_pszFile = pszFile;
	m_nLineNo = nLineNo;
}

CDesignError::~CDesignError()
{
	delete m_pszMsg;
}

char *CDesignError::GetMsg(void)
{
	return m_pszMsg;
}

char *CDesignError::GetFile(void)
{
	return m_pszFile;
}

int CDesignError::GetLineNo(void)
{
	return m_nLineNo;
}
