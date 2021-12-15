// samisc.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMISC_H__03CBE8D1_50AF_44A0_BC10_FA83E300D215__INCLUDED_)
#define AFX_SAMISC_H__03CBE8D1_50AF_44A0_BC10_FA83E300D215__INCLUDED_

#define SA_MAKELONG(a, b)      (((long)((short)(a))) | (((long)((short)(b))) << 16))

extern long SAExtractVersionFromString(const SAString &sVerString);

#if defined(_WINDOWS) || defined(WIN32)
extern void *SAGetVersionInfo(LPCTSTR sDLLName);
extern long SAGetFileVersionFromString(LPCTSTR sDLLName);
extern long SAGetProductVersion(LPCTSTR sDLLName);
#endif	// defined(_WINDOWS) || defined(WIN32)


#endif // !defined(AFX_SAMISC_H__03CBE8D1_50AF_44A0_BC10_FA83E300D215__INCLUDED_)
