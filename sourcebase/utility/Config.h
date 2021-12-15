//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIG_H__3CEEB59A_CE1E_4CB6_A275_A1B663ACEB4E__INCLUDED_)
#define AFX_CONFIG_H__3CEEB59A_CE1E_4CB6_A275_A1B663ACEB4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

void GetConfigString(const char *filename, char *key, char *val, int size);
int GetConfigInt(const char *filename, char *key);

#endif // !defined(AFX_CONFIG_H__3CEEB59A_CE1E_4CB6_A275_A1B663ACEB4E__INCLUDED_)
