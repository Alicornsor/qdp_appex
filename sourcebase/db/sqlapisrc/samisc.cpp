// samisc.cpp
//
//////////////////////////////////////////////////////////////////////

#include "osdep.h"

#if (_MSC_VER >= 1300) && (_MSC_VER < 1400) && (WINVER < 0x0500)
// VC7 or later, building with pre-VC7 runtime libraries
// ION: _ftol(double) is available again from Visual C++ 2005
long _ftol2(double dblSource)
{ 
	return _ftol(dblSource);
}
#endif

SAChar *sa_strupr(SAChar *src)
{
	for( int i = 0; 0 != (src[i] = (SAChar)sa_toupper(src[i])); ++i);
	return src;
} 

SAChar *sa_strlwr(SAChar *src)
{
	for( int i = 0; 0 != (src[i] = (SAChar)sa_tolower(src[i])); ++i);
	return src;
} 

long SAExtractVersionFromString(const SAString &sVerString)
{
	// find first #.# and treat it as version
	SAChar *sMajor = NULL, *sMinor = NULL;
	short nMajor = 0, nMinor = 0;

	const SAChar *s = sVerString;
	SAChar *p = (SAChar *)s;
	while(p)
	{
		sMajor = sa_strpbrk(p, _TSA("0123456789"));
		if(!sMajor)
			break;

		nMajor = (short)sa_strtol(sMajor, &p, 10);
		if(*p != _TSA('.') && *p != _TSA(','))
			continue;
		sMinor = sa_strpbrk(p, _TSA("0123456789"));
		if(sMinor != p+1 && (sMinor != p+2 && *(p-1) != _TSA(' ')))
			break;
		nMinor = (short)sa_strtol(sMinor, &p, 10);
		break;
	}

	bool bOk = sMajor != NULL && sMinor != NULL;
	return bOk? SA_MAKELONG(nMinor, nMajor) : 0;
}

#if defined(SQLAPI_WINDOWS)
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
			::free(lpData);

		throw SAException(SA_Library_Error, -1, -1, IDS_GET_LIBRARY_VERSION_FAILS, sDLLName);
	}

	return lpData;
}

long SAGetFileVersionFromString(LPCTSTR sDLLName)
{
	void *lpData = SAGetVersionInfo(sDLLName);

	WORD* ppTranslation[2];
	UINT uLen;
	SAChar szSubBlock[] = _TSA("\\VarFileInfo\\Translation");
	BOOL bOk = ::VerQueryValue(lpData, szSubBlock, (void**)&ppTranslation, &uLen);
	bOk = bOk && uLen >= 4;

	SAChar s[256];
	if(bOk)
#if defined(__BORLANDC__) && (__BORLANDC__ <= 0x0520)
		sprintf(s, _TSA("StringFileInfo\\%.4x%.4x\\FileVersion"), ppTranslation[0][0], ppTranslation[0][1]);
#else
		sa_snprintf(s, 256, _TSA("StringFileInfo\\%.4x%.4x\\FileVersion"), ppTranslation[0][0], ppTranslation[0][1]);
#endif
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
	SAChar szSubBlock[] = _TSA("\\");
	BOOL bOk = ::VerQueryValue(lpData, szSubBlock, (void**)&pVS_FIXEDFILEINFO, &uLen);
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

DWORD SAGetLastErrorText(SAString& sMessage)
{
	LPVOID lpMsgBuf;
	DWORD nReturn = ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|
		FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, ::GetLastError(), 0, (LPTSTR) &lpMsgBuf, 0, NULL);
	sMessage = (const SAChar*)lpMsgBuf;
	::LocalFree(lpMsgBuf);
	return nReturn;
}

HMODULE SALoadLibraryFromList(SAString& sLibsList, SAString& sErrorMessage, SAString& sLibName)
{
	HMODULE hDLL = NULL;
	size_t nStart = 0l, nPos;
	while( NULL == hDLL && nStart != SIZE_MAX )
	{
		nPos = sLibsList.Find(_TSA(';'), nStart);
		sLibName = SIZE_MAX == nPos ? sLibsList.Mid(nStart):sLibsList.Mid(nStart, nPos - nStart);
		hDLL = ::LoadLibrary(sLibName);
		if( NULL == hDLL )
		{
			SAString sMsg;
			if( SAGetLastErrorText(sMsg) )
				sErrorMessage += sLibName + _TSA(": ") + sMsg;
		}
		nStart = SIZE_MAX == nPos ? nPos:(nPos+1);
	}
	return hDLL;
}
#else
void* SALoadLibraryFromList(SAString& sLibsList, SAString& sErrorMessage, SAString& sLibName, int flag)
{
	void* hDLL = NULL;
	size_t nStart = 0l, nPos;
	while( NULL == hDLL && nStart != SIZE_MAX )
	{
		nPos = sLibsList.Find(_TSA(':'), nStart);
		sLibName = SIZE_MAX == nPos ? sLibsList.Mid(nStart):sLibsList.Mid(nStart, nPos - nStart);
		hDLL = ::dlopen(sLibName.GetMultiByteChars(), flag);
		if( NULL == hDLL )
			sErrorMessage += /*sLibName + _TSA(": ") */ _TSA("\n") + SAString(::dlerror()); // dlerror should show library name
		nStart = SIZE_MAX == nPos ? nPos:(nPos+1);
	}
	return hDLL;
}
#endif	// !defined(SQLAPI_WINDOWS)


SAMutex::SAMutex()
{
#if defined(SQLAPI_WINDOWS)
#ifdef SA_USE_MUTEXT_LOCK
	m_hMutex = ::CreateMutex(NULL, FALSE, NULL);
#else
	::InitializeCriticalSection(&m_hCriticalSection);
#endif
#endif	// defined(SQLAPI_WINDOWS)

#if defined(SA_USE_PTHREAD)
	pthread_mutex_init(&m_mutex, NULL);
	m_locks = 0;
	pthread_mutex_init(&m_helper_mutex, NULL);
#endif	// defined(SA_USE_PTHREAD)
}

/*virtual */
SAMutex::~SAMutex()
{
#if defined(SQLAPI_WINDOWS)
#ifdef SA_USE_MUTEXT_LOCK
	::CloseHandle(m_hMutex);
#else
	::DeleteCriticalSection(&m_hCriticalSection);
#endif
#endif	// defined(SQLAPI_WINDOWS)

#if defined(SA_USE_PTHREAD)
	pthread_mutex_destroy(&m_helper_mutex);
	pthread_mutex_destroy(&m_mutex);
#endif	// defined(SA_USE_PTHREAD)
}

void SAMutex::Wait()
{
#if defined(SQLAPI_WINDOWS)
#ifdef SA_USE_MUTEXT_LOCK
	::WaitForSingleObject(m_hMutex, INFINITE);
#else
	::EnterCriticalSection(&m_hCriticalSection);
#endif
#endif	// defined(SQLAPI_WINDOWS)

#if defined(SA_USE_PTHREAD)
	pthread_mutex_lock(&m_helper_mutex);
	if(m_locks && pthread_self() == m_owner_thread)
	{
		++m_locks;
		pthread_mutex_unlock(&m_helper_mutex);
	}
	else
	{
		pthread_mutex_unlock(&m_helper_mutex);
		pthread_mutex_lock(&m_mutex);
		pthread_mutex_lock(&m_helper_mutex);
		m_owner_thread = pthread_self();
		assert(m_locks == 0);
		++m_locks;
		pthread_mutex_unlock(&m_helper_mutex);
	}
#endif	// defined(SA_USE_PTHREAD)
}

void SAMutex::Release()
{
#if defined(SQLAPI_WINDOWS)
#ifdef SA_USE_MUTEXT_LOCK
	::ReleaseMutex(m_hMutex);
#else
	::LeaveCriticalSection(&m_hCriticalSection);
#endif
#endif	// defined(SQLAPI_WINDOWS)

#if defined(SA_USE_PTHREAD)
	pthread_mutex_lock(&m_helper_mutex);
	if(m_owner_thread == pthread_self() && (--m_locks == 0))
		pthread_mutex_unlock(&m_mutex);
	pthread_mutex_unlock(&m_helper_mutex);
#endif	// defined(SA_USE_PTHREAD)
}

SACriticalSectionScope::SACriticalSectionScope(SAMutex *pSAMutex) :
	m_pSAMutex(pSAMutex)
{
	m_pSAMutex->Wait();
}

/*virtual */
SACriticalSectionScope::~SACriticalSectionScope()
{
	m_pSAMutex->Release();
}

#ifdef SA_INTERNAL_STRTOULL
#include <errno.h>
#include <ctype.h>
#include <limits.h>

#ifndef UINT64_C
#ifdef _MSC_VER
#pragma warning (disable: 4146)
#define UINT64_C(c) c##ui64
#else
#define UINT64_C(c) c##ULL
#endif
#endif

#ifndef ULLONG_MAX
#define ULLONG_MAX 0xffffffffffffffff
#endif

sa_uint64_t sa_strtoull(const char *nptr, char **endptr, int base)
{
	sa_uint64_t result = 0;

	const char *p;
	const char *first_nonspace;
	const char *digits_start;

	int sign = 1;
	int out_of_range = 0;

	p = nptr;

	if( 0 != base && (base < 2 || base > 36) )
		goto invalid_input;

	while( isspace((unsigned char)(*p)) )
		p++;

	first_nonspace = p;

	if( '+' == *p )
		++p;
	else if( '-' == *p )
	{
		++p;
		sign = -1;
	}

	if( base == 0 )
	{
		if( '0' == *p )
		{
			if( 'x' == p[1] || 'X' == p[1] )
			{
				if( isxdigit((unsigned char)p[2]) )
				{
					p += 2;
					base = 16;
				} 
				else
					base = 10;
			}
			else
			{
				++p;
				base = 8;
			}
		}
		else
			base = 10;
	}
	else if( 16 == base && '0' == *p && ('x' == p[1] || 'X' == p[1]) )
		p += 2;

	digits_start = p;

	for( ; *p ; ++p ) 
	{
		int digit = ('0' <= *p && *p <= '9') ? (*p - '0')
			: ('a' <= *p && *p <= 'z') ? (*p - 'a' + 10)
			: ('A' <= *p && *p <= 'Z') ? (*p - 'A' + 10) : 36;

		if( digit < base )
		{
			if( (result > (ULLONG_MAX / base)) || ((result * base) > (ULLONG_MAX - digit)) )
			{
				out_of_range = 1;
				break;
			}

			result = result * base + digit;
		} 
		else
			break;
	}

	if( p == first_nonspace )
		p = nptr;

	if( endptr )
		*endptr = (char*)p;

	if( out_of_range )
	{
		errno = ERANGE;
		return ULLONG_MAX;
	}

	if( p > first_nonspace && p == digits_start )
		goto invalid_input;

	return (sign > 0 ? result : -result);

invalid_input:
	errno = EINVAL;
	if( endptr )
		*endptr = (char *) p;
	return 0;
}
#endif // SA_INTERNAL_STRTOULL
