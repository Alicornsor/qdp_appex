// samisc.cpp
//
//////////////////////////////////////////////////////////////////////

#include <SQLAPI.h>
#include "samisc.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>	// strtol

#include "errmsg.h"

long SAExtractVersionFromString(const SAString &sVerString)
{
	// find first #.# and treat it as version
	SAChar *sMajor = NULL, *sMinor = NULL;
	short nMajor = 0, nMinor = 0;

	const SAChar *s = sVerString;
	SAChar *p = (SAChar *)s;
	while(p)
	{
		sMajor = sa_strpbrk(p, _SA("0123456789"));
		if(!sMajor)
			break;

		nMajor = (short)sa_strtol(sMajor, &p, 10);
		if(*p != _SA('.') && *p != _SA(','))
			continue;
		sMinor = sa_strpbrk(p, _SA("0123456789"));
		if(sMinor != p+1 && (sMinor != p+2 && *(p-1) != _SA(' ')))
			break;
		nMinor = (short)sa_strtol(sMinor, &p, 10);
		break;
	}

	bool bOk = sMajor != NULL && sMinor != NULL;
	return bOk? SA_MAKELONG(nMinor, nMajor) : 0;
}

#if defined(_WINDOWS) || defined(WIN32)
void *SAGetVersionInfo(LPCTSTR sDLLName)
{
	DWORD dwHandle;
	DWORD dwLen  = ::GetFileVersionInfoSize(
		(LPTSTR)sDLLName, &dwHandle);

	if(!dwLen)
		throw SAException(SA_Library_Error, -1, -1, IDS_GET_LIBRARY_VERSION_FAILS, sDLLName);

	void *lpData = malloc(dwLen);
	if(!::GetFileVersionInfo(
		(LPTSTR)sDLLName,
		dwHandle, dwLen, lpData))
	{
		if(lpData)
			free(lpData);

		throw SAException(SA_Library_Error, -1, -1, IDS_GET_LIBRARY_VERSION_FAILS, sDLLName);
	}

	return lpData;
}

long SAGetFileVersionFromString(LPCTSTR sDLLName)
{
	void *lpData = SAGetVersionInfo(sDLLName);

	WORD* ppTranslation[2];
	UINT uLen;
	BOOL bOk = ::VerQueryValue(lpData,
		_SA("\\VarFileInfo\\Translation"), (void**)&ppTranslation, &uLen);
	bOk = bOk && uLen >= 4;

	SAChar s[256];
	if(bOk)
		sa_sprintf(s, _SA("StringFileInfo\\%.4x%.4x\\FileVersion"), ppTranslation[0][0], ppTranslation[0][1]);

	SAChar *sProductVersion = NULL;
	bOk = bOk && ::VerQueryValue(lpData,
		s, (void**)&sProductVersion, &uLen);

	if(!bOk)
	{
		if(lpData)
			::free(lpData);

		throw SAException(SA_Library_Error, -1, -1, IDS_GET_LIBRARY_VERSION_FAILS, sDLLName);
	}

	long nVersion = ::SAExtractVersionFromString(sProductVersion);
	if(lpData)
		::free(lpData);

	return nVersion;
}

long SAGetProductVersion(LPCTSTR sDLLName)
{
	void *lpData = SAGetVersionInfo(sDLLName);

	VS_FIXEDFILEINFO *pVS_FIXEDFILEINFO;
	UINT uLen;
	BOOL bOk = ::VerQueryValue(lpData, _SA("\\"), (void**)&pVS_FIXEDFILEINFO, &uLen);
	if(!bOk)
	{
		if(lpData)
			::free(lpData);

		throw SAException(SA_Library_Error, -1, -1, IDS_GET_LIBRARY_VERSION_FAILS, sDLLName);
	}

	long nVersion = pVS_FIXEDFILEINFO->dwProductVersionMS;
	if(lpData)
		::free(lpData);

	return nVersion;
}
#endif	// defined(_WINDOWS) || defined(WIN32)
