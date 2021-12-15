// SQLAPI.cpp : Defines the entry point for the DLL application.
//

#include <SQLAPI.h>

#include "ISAClient.h"
#include "errmsg.h"

#ifdef SQLAPI_AllClients
#define SQLAPI_odbcClient
#define SQLAPI_oraClient
#define SQLAPI_ssClient
#define SQLAPI_ibClient
#define SQLAPI_sbClient
#define SQLAPI_db2Client
#define SQLAPI_infClient
#define SQLAPI_sybClient
#define SQLAPI_myClient
#define SQLAPI_pgClient
#endif

#ifdef SQLAPI_odbcClient
#include "odbcClient.h"
#endif
#ifdef SQLAPI_oraClient
#include "oraClient.h"
#endif
#ifdef SQLAPI_ssClient
#include "ssClient.h"
#endif
#ifdef SQLAPI_ibClient
#include "ibClient.h"
#endif
#ifdef SQLAPI_sbClient
#include "sbClient.h"
#endif
#ifdef SQLAPI_db2Client
#include "db2Client.h"
#endif
#ifdef SQLAPI_infClient
#include "infClient.h"
#endif
#ifdef SQLAPI_sybClient
#include "sybClient.h"
#endif
#ifdef SQLAPI_myClient
#include "myClient.h"
#endif
#ifdef SQLAPI_pgClient
#include "pgClient.h"
#endif

#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#ifdef LINUX
#include <wchar.h>
#include <wctype.h>
#endif

#ifdef SQLAPI_odbcClient
static IodbcClient odbcClient;	// ODBC client
#endif
#ifdef SQLAPI_oraClient
static IoraClient oraClient;	// Oracle client
#endif
#ifdef SQLAPI_ssClient
static IssClient ssClient;		// Microsoft SQL Server client
#endif
#ifdef SQLAPI_ibClient
static IibClient ibClient;		// InterBase client
#endif
#ifdef SQLAPI_sbClient
static IsbClient sbClient;		// Centura SqlBase client
#endif
#ifdef SQLAPI_db2Client
static Idb2Client db2Client;	// DB2 client
#endif
#ifdef SQLAPI_infClient
static IinfClient infClient;	// Informix client
#endif
#ifdef SQLAPI_sybClient
static IsybClient sybClient;	// Sybase client
#endif
#ifdef SQLAPI_myClient
static ImyClient myClient;	// MySQL client
#endif
#ifdef SQLAPI_pgClient
static IpgClient pgClient;	// MySQL client
#endif

static ISAClient *stat_SAClients[] =
{
	NULL,
#ifdef SQLAPI_odbcClient
	&odbcClient,
#else
	NULL,
#endif
#ifdef SQLAPI_oraClient
	&oraClient,
#else
	NULL,
#endif
#ifdef SQLAPI_ssClient
	&ssClient,
#else
	NULL,
#endif
#ifdef SQLAPI_ibClient
	&ibClient,
#else
	NULL,
#endif
#ifdef SQLAPI_sbClient
	&sbClient,
#else
	NULL,
#endif
#ifdef SQLAPI_db2Client
	&db2Client,
#else
	NULL,
#endif
#ifdef SQLAPI_infClient
	&infClient,
#else
	NULL,
#endif
#ifdef SQLAPI_sybClient
	&sybClient,
#else
	NULL,
#endif
#ifdef SQLAPI_myClient
	&myClient,
#else
	NULL,
#endif
#ifdef SQLAPI_pgClient
	&pgClient
#else
	NULL
#endif
};

struct sa_Commands
{
	SACommand	*pCommand;
	ISACursor	*pISACursor;
	sa_Commands	*Next;
};

#if !defined(SA_NO_TRIAL)

const char *sTrialText ="";
/*
const char *sTrialText =
	"Thank you for trying SQLAPI++ Library.\n"
	"\n"
	"This version is for evaluation purpose only.\n"
	"You can register SQLAPI++ using online registration service.\n"
	"\n"
	"For additional information visit:\n"
	"    SQLAPI++ Home (http://www.sqlapi.com)\n"
	"For help on using the Library e-mail to:\n"
	"    howto@sqlapi.com";
*/

const char *sTrialCaption =
	"SQLAPI++ Registration Reminder";

static void CheckTrial()
{
	return;
	static bool bCheckedTrial = false;
	if(!bCheckedTrial)
	{

		#if defined(WIN32) || defined(_WINDOWS)
		::MessageBox(NULL, 
			sTrialText,
			sTrialCaption, 0);
		bCheckedTrial = true;

		#else	// never set bCheckedTrial = true; in Linux/Unix
		srand((unsigned)time(NULL));
		int nRand = rand();
		if(nRand % 5 == 0)
			SAException::throwUserException(-1, "Trial version exception:\n%s", sTrialText);
		printf("%s\n\n", sTrialText);
		#endif	// defined(WIN32) || defined(_WINDOWS)
	}
}

#endif	// !defined(SA_NO_TRIAL)


//////////////////////////////////////////////////////////////////////
// SAString Class
//////////////////////////////////////////////////////////////////////

// For an empty string, m_pchData will point here
// (note: avoids special case of checking for NULL m_pchData)
// empty string data (and locked)
static long  _saInitData[] = {
	0,	// pConvertedData
#ifdef SA_UNICODE
	0,	// nBinaryDataLengthDiff
#endif	// SA_UNICODE
	-1,	// nRefs
	0,	// nDataLength
	0,	// nAllocLength
	0	// SAChar data[nAllocLength]
};
static SAStringData *_saDataNil = (SAStringData *)&_saInitData;
static const SAChar *_saPchNil = (const SAChar *)(((unsigned char*)&_saInitData)+sizeof(SAStringData));
// special function to make saEmptyString work even during initialization
static const SAString &saGetEmptyString()
{
	return *(SAString *)&_saPchNil;
}
#define saEmptyString saGetEmptyString()

void SAString::AllocBuffer(int nLen)
// always allocate one extra character for '\0' termination
// assumes [optimistically] that data length will equal allocation length
{
	assert(nLen >= 0);
	assert(nLen <= INT_MAX-1);    // max size (enough room for 1 extra)

	if (nLen == 0)
		Init();
	else
	{
		SAStringData *pData;
		pData = (SAStringData*)
			new unsigned char[sizeof(SAStringData) + (nLen+1)*sizeof(SAChar)];
		pData->nAllocLength = nLen;

		// start of SAString special
		pData->pConvertedData = NULL;
#ifdef SA_UNICODE
		pData->nBinaryDataLengthDiff = 0;
#endif	// SA_UNICODE
		// end of SAString special

		pData->nRefs = 1;
		pData->data()[nLen] = _SA('\0');
		pData->nDataLength = nLen;
		m_pchData = pData->data();
	}
}

/*static */
void SAString::FreeData(SAStringData *pData)
{
	delete [] (unsigned char*)pData->pConvertedData;
	delete[] (unsigned char*)pData;
}

//////////////////////////////////////////////////////////////////////////////
// concatenate in place

#ifdef SA_UNICODE

void SAString::ConcatBinaryInPlace(int nSrcLenInBytes, const void *pSrcData)
{
	// concatenating an empty string is a no-op!
	if (nSrcLenInBytes == 0)
		return;

	// if a conversion has been made already, it is not valid any more
	delete [] (unsigned char*)GetData()->pConvertedData;
	GetData()->pConvertedData = NULL;

	// if the buffer is too small, or we have a width mis-match, just
	//   allocate a new buffer (slow but sure)
	int nNewLenInBytes = GetBinaryLength() + nSrcLenInBytes;
	int nBinaryDataLengthDiff = nNewLenInBytes % sizeof(SAChar);
	// allocate at least so many characters that all binary data could be stored (round up if necessary)
	int nNewLenInChars = nNewLenInBytes / sizeof(SAChar) + (nBinaryDataLengthDiff? 1 : 0);
	if (GetData()->nRefs > 1 || nNewLenInChars > GetData()->nAllocLength)
	{
		// we have to grow the buffer, use the ConcatCopy routine
		SAStringData *pOldData = GetData();
		ConcatBinaryCopy(GetBinaryLength(), (const void*)m_pchData, nSrcLenInBytes, pSrcData);
		assert(pOldData != NULL);
		SAString::Release(pOldData);
	}
	else
	{
		// fast concatenation when buffer big enough
		memcpy((unsigned char*)m_pchData+GetBinaryLength(), pSrcData, nSrcLenInBytes);
		GetData()->nDataLength = nNewLenInChars;
		GetData()->nBinaryDataLengthDiff = nBinaryDataLengthDiff;
		assert(GetData()->nDataLength <= GetData()->nAllocLength);
		m_pchData[GetData()->nDataLength] = _SA('\0');
	}
}

#endif	// SA_UNICODE

void SAString::ConcatInPlace(int nSrcLen, const SAChar *lpszSrcData)
{
	//  -- the main routine for += operators

	// concatenating an empty string is a no-op!
	if (nSrcLen == 0)
		return;

	// if a conversion has been made already, it is not valid any more
	delete [] (unsigned char*)GetData()->pConvertedData;
	GetData()->pConvertedData = NULL;
	// whether we have binary data or not
	// it will no longer be binary after we apply SAChar* concatenation
#ifdef SA_UNICODE
	GetData()->nBinaryDataLengthDiff = 0;
#endif

	// if the buffer is too small, or we have a width mis-match, just
	//   allocate a new buffer (slow but sure)
	if (GetData()->nRefs > 1 || GetData()->nDataLength + nSrcLen > GetData()->nAllocLength)
	{
		// we have to grow the buffer, use the ConcatCopy routine
		SAStringData *pOldData = GetData();
		ConcatCopy(GetData()->nDataLength, m_pchData, nSrcLen, lpszSrcData);
		assert(pOldData != NULL);
		SAString::Release(pOldData);
	}
	else
	{
		// fast concatenation when buffer big enough
		memcpy(m_pchData+GetData()->nDataLength, lpszSrcData, nSrcLen*sizeof(SAChar));
		GetData()->nDataLength += nSrcLen;
		assert(GetData()->nDataLength <= GetData()->nAllocLength);
		m_pchData[GetData()->nDataLength] = '\0';
	}
}

const SAString &SAString::operator+=(const SAChar *lpsz)
{
	ConcatInPlace(SafeStrlen(lpsz), lpsz);
	return *this;
}

const SAString &SAString::operator+=(SAChar ch)
{
	ConcatInPlace(1, &ch);
	return *this;
}

#ifdef SA_UNICODE
const SAString &SAString::operator+=(char ch)
{
	*this += (SAChar)ch;
	return *this;
}
#endif	// SA_UNICODE


const SAString& SAString::operator+=(const SAString &string)
{
#ifdef SA_UNICODE

	// Under Unicode we should be aware that *this or string (or both)
	// can be binary string with length not being multiply of sizeof(SAChar),
	// so we should concatinate bytes, not characters
	ConcatBinaryInPlace(string.GetBinaryLength(), (const void*)string);
	return *this;

#else	// !SA_UNICODE

	// byte == character in non-Unicode build
	ConcatInPlace(string.GetData()->nDataLength, string.m_pchData);
	return *this;

#endif	// !SA_UNICODE
}

///////////////////////////////////////////////////////////////////////////////
// Advanced direct buffer access

SAChar *SAString::GetBuffer(int nMinBufLength)
{
	assert(nMinBufLength >= 0);

	if (GetData()->nRefs > 1 || nMinBufLength > GetData()->nAllocLength)
	{
		// we have to grow the buffer
		SAStringData *pOldData = GetData();
		int nOldLen = GetData()->nDataLength;   // AllocBuffer will tromp it
		if (nMinBufLength < nOldLen)
			nMinBufLength = nOldLen;
		AllocBuffer(nMinBufLength);
		memcpy(m_pchData, pOldData->data(), (nOldLen+1)*sizeof(SAChar));
		GetData()->nDataLength = nOldLen;
		SAString::Release(pOldData);
	}
	assert(GetData()->nRefs <= 1);

	// return a pointer to the character storage for this string
	assert(m_pchData != NULL);
	return m_pchData;
}

void SAString::ReleaseBuffer(int nNewLength)
{
	CopyBeforeWrite();  // just in case GetBuffer was not called

	if (nNewLength == -1)
		nNewLength = sa_strlen(m_pchData); // zero terminated

	assert(nNewLength <= GetData()->nAllocLength);
	GetData()->nDataLength = nNewLength;
	m_pchData[nNewLength] = '\0';

#ifdef SA_UNICODE
	GetData()->nBinaryDataLengthDiff = 0;
#endif	// SA_UNICODE
}

SAChar *SAString::LockBuffer()
{
	SAChar *lpsz = GetBuffer(0);
	GetData()->nRefs = -1;
	return lpsz;
}

void SAString::UnlockBuffer()
{
	assert(GetData()->nRefs == -1);
	if (GetData() != _saDataNil)
		GetData()->nRefs = 1;
}

void SAString::CopyBeforeWrite()
{
	if (GetData()->nRefs > 1)
	{
		SAStringData *pData = GetData();
		Release();
		AllocBuffer(pData->nDataLength);
		memcpy(m_pchData, pData->data(), (pData->nDataLength+1)*sizeof(SAChar));
	}
	// start of SAString special
	else
	{
		// if a conversion has been made already, it is not valid any more
		delete [] (unsigned char*)GetData()->pConvertedData;
		GetData()->pConvertedData = NULL;

#ifdef SA_UNICODE
		GetData()->nBinaryDataLengthDiff = 0;
#endif	// SA_UNICODE
	}
	// end of SAString special
	assert(GetData()->nRefs <= 1);
}

void SAString::AllocBeforeWrite(int nLen)
{
	if (GetData()->nRefs > 1 || nLen > GetData()->nAllocLength)
	{
		Release();
		AllocBuffer(nLen);
	}
	// start of SAString special
	else
	{
		// if a conversion has been made already, it is not valid any more
		delete [] (unsigned char*)GetData()->pConvertedData;
		GetData()->pConvertedData = NULL;

#ifdef SA_UNICODE
		GetData()->nBinaryDataLengthDiff = 0;
#endif	// SA_UNICODE
	}
	// end of SAString special
	assert(GetData()->nRefs <= 1);
}

void SAString::Release()
{
	if (GetData() != _saDataNil)
	{
		assert(GetData()->nRefs != 0);
		if(--GetData()->nRefs <= 0)
			FreeData(GetData());
		Init();
	}
}

/*static */
void SAString::Release(SAStringData *pData)
{
	if (pData != _saDataNil)
	{
		assert(pData->nRefs != 0);
		if (--pData->nRefs <= 0)
			FreeData(pData);
	}
}

void SAString::Init()
{
	m_pchData = saEmptyString.m_pchData;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SAStringData *SAString::GetData() const
{
	assert(m_pchData != NULL);
	return ((SAStringData *)m_pchData)-1;
}

SAString::SAString()
{
	Init();
}

SAString::SAString(const SAString &stringSrc)
{
	assert(stringSrc.GetData()->nRefs != 0);
	if (stringSrc.GetData()->nRefs >= 0)
	{
		assert(stringSrc.GetData() != _saDataNil);
		m_pchData = stringSrc.m_pchData;
		++GetData()->nRefs;
	}
	else
	{
		Init();
		*this = stringSrc;	//*this = stringSrc.m_pchData; - not right, will not copy strings with embedded '\0'
	}
}

SAString::SAString(const SAChar *lpsz)
{
	Init();
	int nLen = SafeStrlen(lpsz);
	if (nLen != 0)
	{
		AllocBuffer(nLen);
		memcpy(m_pchData, lpsz, nLen*sizeof(SAChar));
	}
}

/////////////////////////////////////////////////////////////////////////////
// Special conversion constructors

#ifdef SA_UNICODE

SAString::SAString(const char *lpsz)
{
	Init();
	int nSrcLen = lpsz != NULL ? strlen(lpsz) : 0;
	if (nSrcLen != 0)
	{
		AllocBuffer(nSrcLen);
		ReleaseBuffer(SAMultiByteToWideChar(m_pchData, lpsz, nSrcLen));
	}
}

SAString::SAString(const char *lpch, int nLength)
{
	Init();
	if (nLength != 0)
	{
		AllocBuffer(nLength);
		ReleaseBuffer(SAMultiByteToWideChar(m_pchData, lpch, nLength));
	}
}

#else	// !SA_UNICODE

SAString::SAString(const wchar_t *lpsz)
{
	Init();
	int nSrcLen = lpsz != NULL ? wcslen(lpsz) : 0;
	if (nSrcLen != 0)
	{
		AllocBuffer(nSrcLen*2);
		ReleaseBuffer(SAWideCharToMultiByte(m_pchData, lpsz, nSrcLen));
	}
}

SAString::SAString(const wchar_t *lpch, int nLength)
{
	Init();
	if (nLength != 0)
	{
		AllocBuffer(nLength*2);
		ReleaseBuffer(SAWideCharToMultiByte(m_pchData, lpch, nLength));
	}
}

#endif //!SA_UNICODE

SAString::SAString(const SAChar *lpch, int nLength)
{
	Init();
	if (nLength != 0)
	{
		assert(lpch);
		AllocBuffer(nLength);
		memcpy(m_pchData, lpch, nLength*sizeof(SAChar));
	}
}

SAString::SAString(const unsigned char *psz)
{
	Init();
	*this = (const char*)psz;
}

//////////////////////////////////////////////////////////////////////////////
// More sophisticated construction

SAString::SAString(SAChar ch, int nLength)
{
	Init();
	if (nLength >= 1)
	{
		AllocBuffer(nLength);
#ifdef SA_UNICODE
		for (int i = 0; i < nLength; ++i)
			m_pchData[i] = ch;
#else
		memset(m_pchData, ch, nLength);
#endif
	}
}

SAString::~SAString()
{
	if (GetData() != _saDataNil)
	{
		//  free any attached data
		if (--GetData()->nRefs <= 0)
			FreeData(GetData());
	}
}

void SAString::Empty()
{
	if (GetData()->nDataLength == 0)
		return;

	if (GetData()->nRefs >= 0)
		Release();
	else
		*this =	_saPchNil;

	assert(GetData()->nDataLength == 0);
	assert(GetData()->nRefs < 0 || GetData()->nAllocLength == 0);
}

bool SAString::IsEmpty() const
{
	return GetData()->nDataLength == 0;
}

int SAString::GetLength() const
{
	return GetData()->nDataLength;
}

SAString::operator const SAChar *() const
{
	return m_pchData;
}

//////////////////////////////////////////////////////////////////////////////
// Assignment operators
//  All assign a new value to the string
//      (a) first see if the buffer is big enough
//      (b) if enough room, copy on top of old buffer, set size and type
//      (c) otherwise free old string data, and create a new one
//
//  All routines return the new string (but as a 'const SAString&' so that
//      assigning it again will cause a copy, eg: s1 = s2 = "hi there".
//

#ifdef SA_UNICODE

void SAString::AssignBinaryCopy(int nSrcLenInBytes, const void *pSrcData)
{
	int nBinaryDataLengthDiff = nSrcLenInBytes % sizeof(SAChar);
	// allocate at least so many characters that all binary data could be stored (round up if necessary)
	int nSrcLenInChars = nSrcLenInBytes / sizeof(SAChar) + (nBinaryDataLengthDiff? 1 : 0);

	AllocBeforeWrite(nSrcLenInChars);
	memcpy(m_pchData, pSrcData, nSrcLenInBytes);
	GetData()->nDataLength = nSrcLenInChars;
	m_pchData[nSrcLenInChars] = '\0';

	// if nSrcLenInBytes is not a multiply of sizeof(SAChar)
	// we have to save the difference
	GetData()->nBinaryDataLengthDiff = nBinaryDataLengthDiff;
}

#endif	// SA_UNICODE

void SAString::AssignCopy(int nSrcLen, const SAChar *lpszSrcData)
{
	AllocBeforeWrite(nSrcLen);
	memcpy(m_pchData, lpszSrcData, nSrcLen*sizeof(SAChar));
	GetData()->nDataLength = nSrcLen;
	m_pchData[nSrcLen] = '\0';
}

const SAString &SAString::operator=(const SAString &stringSrc)
{
	if (m_pchData != stringSrc.m_pchData)
	{
		if ((GetData()->nRefs < 0 && GetData() != _saDataNil) ||
			stringSrc.GetData()->nRefs < 0)
		{
			// actual copy necessary since one of the strings is locked
#ifdef SA_UNICODE

			// Under Unicode we should be aware that stringSrc
			// can be binary string with length not being multiply of sizeof(SAChar),
			// so we should copy bytes, not characters
			AssignBinaryCopy(stringSrc.GetBinaryLength(), (const void*)stringSrc);

#else	// !SA_UNICODE

			AssignCopy(stringSrc.GetData()->nDataLength, stringSrc.m_pchData);

#endif	// !SA_UNICODE
		}
		else
		{
			// can just copy references around
			Release();
			assert(stringSrc.GetData() != _saDataNil);
			m_pchData = stringSrc.m_pchData;
			++GetData()->nRefs;
		}
	}
	return *this;
}

const SAString &SAString::operator =(const SAChar *lpsz)
{
	AssignCopy(SafeStrlen(lpsz), lpsz);
	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// Special conversion assignment

#ifdef SA_UNICODE

const SAString &SAString::operator=(const char *lpsz)
{
	int nSrcLen = lpsz? strlen(lpsz) : 0;
	AllocBeforeWrite(nSrcLen);
	ReleaseBuffer(SAMultiByteToWideChar(m_pchData, lpsz, nSrcLen));
	return *this;
}

#else //!SA_UNICODE

const SAString &SAString::operator=(const wchar_t *lpsz)
{
	int nSrcLen = lpsz? wcslen(lpsz) : 0;
	AllocBeforeWrite(nSrcLen*2);
	ReleaseBuffer(SAWideCharToMultiByte(m_pchData, lpsz, nSrcLen));
	return *this;
}

#endif  //!SA_UNICODE

const SAString &SAString::operator=(SAChar ch)
{
	AssignCopy(1, &ch);
	return *this;
}

#ifdef SA_UNICODE

const SAString &SAString::operator=(char ch)
{
	*this = (SAChar)ch;
	return *this;
}

#endif

const SAString &SAString::operator=(const unsigned char *psz)
{
	*this = (const char *)psz;
	return *this;
}

//////////////////////////////////////////////////////////////////////////////
// concatenation

// NOTE: "operator+" is done as friend functions for simplicity
//      There are three variants:
//          SAString + SAString
// and for ? = SAChar, const SAChar*
//          SAString + ?
//          ? + CString

#ifdef SA_UNICODE

void SAString::ConcatBinaryCopy(int nSrc1LenInBytes, const void *pSrc1Data,
	int nSrc2LenInBytes, const void *pSrc2Data)
{
	// -- master concatenation routine (binary)
	// Concatenate two sources
	// -- assume that 'this' is a new SAString object

	int nNewLenInBytes = nSrc1LenInBytes + nSrc2LenInBytes;
	if (nNewLenInBytes != 0)
	{
		int nBinaryDataLengthDiff = nNewLenInBytes % sizeof(SAChar);
		// allocate at least so many characters that all binary data could be stored (round up if necessary)
		int nNewLenInChars = nNewLenInBytes / sizeof(SAChar) + (nBinaryDataLengthDiff? 1 : 0);

		AllocBuffer(nNewLenInChars);
		// if nNewLengthInBytes is not a multiply of sizeof(SAChar)
		// we have to save the difference
		GetData()->nBinaryDataLengthDiff = nBinaryDataLengthDiff;
		memcpy((unsigned char*)m_pchData, pSrc1Data, nSrc1LenInBytes);
		memcpy((unsigned char*)m_pchData+nSrc1LenInBytes, pSrc2Data, nSrc2LenInBytes);
	}
}

#endif	// SA_UNICODE

void SAString::ConcatCopy(int nSrc1Len, const SAChar *lpszSrc1Data,
	int nSrc2Len, const SAChar *lpszSrc2Data)
{
	// -- master concatenation routine
	// Concatenate two sources
	// -- assume that 'this' is a new SAString object

	int nNewLen = nSrc1Len + nSrc2Len;
	if (nNewLen != 0)
	{
		AllocBuffer(nNewLen);
		memcpy(m_pchData, lpszSrc1Data, nSrc1Len*sizeof(SAChar));
		memcpy(m_pchData+nSrc1Len, lpszSrc2Data, nSrc2Len*sizeof(SAChar));
	}
}

SAString operator+(const SAString &string1, const SAString &string2)
{
#ifdef SA_UNICODE

	// Under Unicode we should be aware that *this or string (or both)
	// can be binary string with length not being multiply of sizeof(SAChar),
	// so we should concatinate bytes, not characters
	SAString s;
	s.ConcatBinaryCopy(string1.GetBinaryLength(), (const void*)string1,
		string2.GetBinaryLength(), (const void*)string2);
	return s;

#else	// !SA_UNICODE

	SAString s;
	s.ConcatCopy(string1.GetData()->nDataLength, string1.m_pchData,
		string2.GetData()->nDataLength, string2.m_pchData);
	return s;

#endif	// !SA_UNICODE
}

SAString operator+(const SAString &string, const SAChar *lpsz)
{
	SAString s;
	s.ConcatCopy(string.GetData()->nDataLength, string.m_pchData,
		SAString::SafeStrlen(lpsz), lpsz);
	return s;
}

SAString operator+(const SAChar *lpsz, const SAString &string)
{
	SAString s;
	s.ConcatCopy(SAString::SafeStrlen(lpsz), lpsz, string.GetData()->nDataLength,
		string.m_pchData);
	return s;
}

SAString operator+(const SAString &string1, SAChar ch)
{
	SAString s;
	s.ConcatCopy(string1.GetData()->nDataLength, string1.m_pchData, 1, &ch);
	return s;
}

SAString operator+(SAChar ch, const SAString &string)
{
	SAString s;
	s.ConcatCopy(1, &ch, string.GetData()->nDataLength, string.m_pchData);
	return s;
}

#ifdef SA_UNICODE
SAString operator+(const SAString &string, char ch)
{
	return string + (SAChar)ch;
}

SAString operator+(char ch, const SAString &string)
{
	return (SAChar)ch + string;
}
#endif

/////////////////////////////////////////////////////////////////////////////
// SAString formatting

#define FORCE_ANSI      0x10000
#define FORCE_UNICODE   0x20000
#define FORCE_INT64     0x40000

void SAString::FormatV(const SAChar *lpszFormat, va_list argList)
{
	assert(lpszFormat);

	va_list argListSave = argList;

	// make a guess at the maximum length of the resulting string
	int nMaxLen = 0;
	for (const SAChar *lpsz = lpszFormat; *lpsz != '\0'; lpsz = sa_csinc(lpsz))
	{
		// handle '%' character, but watch out for '%%'
		if (*lpsz != '%' || *(lpsz = sa_csinc(lpsz)) == '%')
		{
			nMaxLen += sa_clen(lpsz);
			continue;
		}

		int nItemLen = 0;

		// handle '%' character with format
		int nWidth = 0;
		for (; *lpsz != '\0'; lpsz = sa_csinc(lpsz))
		{
			// check for valid flags
			if (*lpsz == '#')
				nMaxLen += 2;   // for '0x'
			else if (*lpsz == '*')
				nWidth = va_arg(argList, int);
			else if (*lpsz == '-' || *lpsz == '+' || *lpsz == '0' ||
				*lpsz == ' ')
				;
			else // hit non-flag character
				break;
		}
		// get width and skip it
		if (nWidth == 0)
		{
			// width indicated by
			nWidth = sa_toi(lpsz);
			for (; *lpsz != '\0' && sa_isdigit(*lpsz); lpsz = sa_csinc(lpsz))
				;
		}
		assert(nWidth >= 0);

		int nPrecision = 0;
		if (*lpsz == '.')
		{
			// skip past '.' separator (width.precision)
			lpsz = sa_csinc(lpsz);

			// get precision and skip it
			if (*lpsz == '*')
			{
				nPrecision = va_arg(argList, int);
				lpsz = sa_csinc(lpsz);
			}
			else
			{
				nPrecision = sa_toi(lpsz);
				for (; *lpsz != '\0' && sa_isdigit(*lpsz); lpsz = sa_csinc(lpsz))
					;
			}
			assert(nPrecision >= 0);
		}

		// should be on type modifier or specifier
		int nModifier = 0;
		if (sa_strncmp(lpsz, _SA("I64"), 3) == 0)
		{
			lpsz += 3;
			nModifier = FORCE_INT64;
#if !defined(_X86_) && !defined(_ALPHA_)
			// __int64 is only available on X86 and ALPHA platforms
			assert(false);
#endif
		}
		else
		{
			switch (*lpsz)
			{
			// modifiers that affect size
			case 'h':
				nModifier = FORCE_ANSI;
				lpsz = sa_csinc(lpsz);
				break;
			case 'l':
				nModifier = FORCE_UNICODE;
				lpsz = sa_csinc(lpsz);
				break;

			// modifiers that do not affect size
			case 'F':
			case 'N':
			case 'L':
				lpsz = sa_csinc(lpsz);
				break;
			}
		}

		// now should be on specifier
		switch (*lpsz | nModifier)
		{
		// single characters
		case 'c':
		case 'C':
			nItemLen = 2;
			// int is OK
			// need a cast here since va_arg only
			// takes fully promoted types
			(void)va_arg(argList, int/*SAChar*/);
			break;
		case 'c'|FORCE_ANSI:
		case 'C'|FORCE_ANSI:
			nItemLen = 2;
			// int is OK
			// need a cast here since va_arg only
			// takes fully promoted types
			(void)va_arg(argList, int/*char*/);
			break;
		case 'c'|FORCE_UNICODE:
		case 'C'|FORCE_UNICODE:
			nItemLen = 2;
			// int is OK
			// need a cast here since va_arg only
			// takes fully promoted types
			(void)va_arg(argList, int/*wchar_t*/);
			break;

		// strings
		case 's':
			{
				const SAChar *pstrNextArg = va_arg(argList, const SAChar*);
				if (pstrNextArg == NULL)
				   nItemLen = 6;  // "(null)"
				else
				{
				   nItemLen = sa_strlen(pstrNextArg);
				   nItemLen = sa_max(1, nItemLen);
				}
			}
			break;

		case 'S':
			{
#ifndef SA_UNICODE
				wchar_t *pstrNextArg = va_arg(argList, wchar_t*);
				if (pstrNextArg == NULL)
				   nItemLen = 6;  // "(null)"
				else
				{
				   nItemLen = wcslen(pstrNextArg);
				   nItemLen = sa_max(1, nItemLen);
				}
#else
				const char *pstrNextArg = va_arg(argList, const char*);
				if (pstrNextArg == NULL)
				   nItemLen = 6; // "(null)"
				else
				{
				   nItemLen = strlen(pstrNextArg);
				   nItemLen = sa_max(1, nItemLen);
				}
#endif
			}
			break;

		case 's'|FORCE_ANSI:
		case 'S'|FORCE_ANSI:
			{
				const char *pstrNextArg = va_arg(argList, const char*);
				if (pstrNextArg == NULL)
				   nItemLen = 6; // "(null)"
				else
				{
				   nItemLen = strlen(pstrNextArg);
				   nItemLen = sa_max(1, nItemLen);
				}
			}
			break;

		case 's'|FORCE_UNICODE:
		case 'S'|FORCE_UNICODE:
			{
				wchar_t *pstrNextArg = va_arg(argList, wchar_t*);
				if (pstrNextArg == NULL)
				   nItemLen = 6; // "(null)"
				else
				{
				   nItemLen = wcslen(pstrNextArg);
				   nItemLen = sa_max(1, nItemLen);
				}
			}
			break;
		}

		// adjust nItemLen for strings
		if (nItemLen != 0)
		{
			if (nPrecision != 0)
				nItemLen = sa_min(nItemLen, nPrecision);
			nItemLen = sa_max(nItemLen, nWidth);
		}
		else
		{
			switch (*lpsz)
			{
			// integers
			case 'd':
			case 'i':
			case 'u':
			case 'x':
			case 'X':
			case 'o':
				if (nModifier & FORCE_INT64)
					(void)va_arg(argList, int);	// __int64 in original code
				else
					(void)va_arg(argList, int);
				nItemLen = 32;
				nItemLen = sa_max(nItemLen, nWidth+nPrecision);
				break;

			case 'e':
			case 'g':
			case 'G':
				(void)va_arg(argList, double);
				nItemLen = 128;
				nItemLen = sa_max(nItemLen, nWidth+nPrecision);
				break;

			case 'f':
				{
					double f;
					SAChar *pszTemp;

					// 312 == strlen("-1+(309 zeroes).")
					// 309 zeroes == max precision of a double
					// 6 == adjustment in case precision is not specified,
					//   which means that the precision defaults to 6
					pszTemp = (SAChar *)malloc(sa_max(nWidth, 312+nPrecision+6));

					f = va_arg(argList, double);
					sa_sprintf( pszTemp, _SA( "%*.*f" ), nWidth, nPrecision+6, f );
					nItemLen = sa_strlen(pszTemp);
					::free(pszTemp);
				}
				break;

			case 'p':
				(void)va_arg(argList, void*);
				nItemLen = 32;
				nItemLen = sa_max(nItemLen, nWidth+nPrecision);
				break;

			// no output
			case 'n':
				(void)va_arg(argList, int*);
				break;

			default:
				assert(false);  // unknown formatting option
			}
		}

		// adjust nMaxLen for output nItemLen
		nMaxLen += nItemLen;
	}

	// if the buffer is too small, or we have a width mis-match, just
	// allocate a new buffer (slow but sure)
	if (GetData()->nRefs > 1 || nMaxLen > GetData()->nAllocLength)
	{
		// we have to grow the buffer
		Release();
		AllocBuffer(nMaxLen);
	}
	if(!(sa_vsprintf(m_pchData, lpszFormat, argListSave) <= nMaxLen))
		assert(false);
	ReleaseBuffer();

	va_end(argListSave);
}

// formatting (using wsprintf style formatting)
void SAString::Format(const SAChar *lpszFormat, ...)
{
	assert(lpszFormat);

	va_list argList;
	va_start(argList, lpszFormat);
	FormatV(lpszFormat, argList);
	va_end(argList);
}

/*static */
int SAString::SafeStrlen(const SAChar *lpsz)
{
	return (lpsz == NULL) ? 0 : sa_strlen(lpsz);
}

SAString SAString::Mid(int nFirst) const
{
	return Mid(nFirst, GetData()->nDataLength - nFirst);
}

SAString SAString::Mid(int nFirst, int nCount) const
{
	// optimize case of returning empty string
	if(nFirst > GetLength())
		return _saPchNil;

	// out-of-bounds requests return sensible things
	if (nFirst < 0)
		nFirst = 0;
	if (nCount < 0)
		nCount = 0;

	if (nFirst + nCount > GetLength())
		nCount = GetLength() - nFirst;
	if (nFirst > GetLength())
		nCount = 0;

	assert(nFirst >= 0);
	assert(nFirst + nCount <= GetData()->nDataLength);

	// optimize case of returning entire string
	if (nFirst == 0 && nFirst + nCount == GetData()->nDataLength)
		return *this;

	SAString dest(m_pchData+nFirst, nCount);
	return dest;
}

SAString SAString::Right(int nCount) const
{
	if (nCount < 0)
		nCount = 0;
	if (nCount >= GetData()->nDataLength)
		return *this;

	SAString dest(m_pchData+GetData()->nDataLength-nCount, nCount);
	return dest;
}

SAString SAString::Left(int nCount) const
{
	if (nCount < 0)
		nCount = 0;
	if (nCount >= GetData()->nDataLength)
		return *this;

	SAString dest(m_pchData, nCount);
	return dest;
}

//////////////////////////////////////////////////////////////////////////////
// Advanced manipulation

int SAString::Delete(int nIndex, int nCount /* = 1 */)
{
	if (nIndex < 0)
		nIndex = 0;
	int nNewLength = GetData()->nDataLength;
	if (nCount > 0 && nIndex < nNewLength)
	{
		CopyBeforeWrite();
		int nBytesToCopy = nNewLength - (nIndex + nCount) + 1;

		memcpy(m_pchData + nIndex,
			m_pchData + nIndex + nCount, nBytesToCopy * sizeof(SAChar));
		GetData()->nDataLength = nNewLength - nCount;
	}

	return nNewLength;
}

int SAString::Insert(int nIndex, SAChar ch)
{
	CopyBeforeWrite();

	if (nIndex < 0)
		nIndex = 0;

	int nNewLength = GetData()->nDataLength;
	if (nIndex > nNewLength)
		nIndex = nNewLength;
	nNewLength++;

	if (GetData()->nAllocLength < nNewLength)
	{
		SAStringData *pOldData = GetData();
		SAChar *pstr = m_pchData;
		AllocBuffer(nNewLength);
		memcpy(m_pchData, pstr, (pOldData->nDataLength+1)*sizeof(SAChar));
		SAString::Release(pOldData);
	}

	// move existing bytes down
	memcpy(m_pchData + nIndex + 1,
		m_pchData + nIndex, (nNewLength-nIndex)*sizeof(SAChar));
	m_pchData[nIndex] = ch;
	GetData()->nDataLength = nNewLength;

	return nNewLength;
}

int SAString::Insert(int nIndex, const SAChar *pstr)
{
	if (nIndex < 0)
		nIndex = 0;

	int nInsertLength = SafeStrlen(pstr);
	int nNewLength = GetData()->nDataLength;
	if (nInsertLength > 0)
	{
		CopyBeforeWrite();
		if (nIndex > nNewLength)
			nIndex = nNewLength;
		nNewLength += nInsertLength;

		if (GetData()->nAllocLength < nNewLength)
		{
			SAStringData *pOldData = GetData();
			SAChar* pstr = m_pchData;
			AllocBuffer(nNewLength);
			memcpy(m_pchData, pstr, (pOldData->nDataLength+1)*sizeof(SAChar));
			SAString::Release(pOldData);
		}

		// move existing bytes down
		memcpy(m_pchData + nIndex + nInsertLength,
			m_pchData + nIndex,
			(nNewLength-nIndex-nInsertLength+1)*sizeof(SAChar));
		memcpy(m_pchData + nIndex,
			pstr, nInsertLength*sizeof(SAChar));
		GetData()->nDataLength = nNewLength;
	}

	return nNewLength;
}

int SAString::Replace(const SAChar *lpszOld, const SAChar *lpszNew)
{
	// can't have empty or NULL lpszOld

	int nSourceLen = SafeStrlen(lpszOld);
	if (nSourceLen == 0)
		return 0;
	int nReplacementLen = SafeStrlen(lpszNew);

	// loop once to figure out the size of the result string
	int nCount = 0;
	SAChar *lpszStart = m_pchData;
	SAChar *lpszEnd = m_pchData + GetData()->nDataLength;
	SAChar *lpszTarget;
	while (lpszStart < lpszEnd)
	{
		while ((lpszTarget = sa_strstr(lpszStart, lpszOld)) != NULL)
		{
			nCount++;
			lpszStart = lpszTarget + nSourceLen;
		}
		lpszStart += sa_strlen(lpszStart) + 1;
	}

	// if any changes were made, make them
	if (nCount > 0)
	{
		CopyBeforeWrite();

		// if the buffer is too small, just
		//   allocate a new buffer (slow but sure)
		int nOldLength = GetData()->nDataLength;
		int nNewLength =  nOldLength + (nReplacementLen-nSourceLen)*nCount;
		if (GetData()->nAllocLength < nNewLength || GetData()->nRefs > 1)
		{
			SAStringData *pOldData = GetData();
			SAChar *pstr = m_pchData;
			AllocBuffer(nNewLength);
			memcpy(m_pchData, pstr, pOldData->nDataLength*sizeof(SAChar));
			SAString::Release(pOldData);
		}
		// else, we just do it in-place
		lpszStart = m_pchData;
		lpszEnd = m_pchData + GetData()->nDataLength;

		// loop again to actually do the work
		while (lpszStart < lpszEnd)
		{
			while ( (lpszTarget = sa_strstr(lpszStart, lpszOld)) != NULL)
			{
				int nBalance = nOldLength - (lpszTarget - m_pchData + nSourceLen);
				memmove(lpszTarget + nReplacementLen, lpszTarget + nSourceLen,
					nBalance * sizeof(SAChar));
				memcpy(lpszTarget, lpszNew, nReplacementLen*sizeof(SAChar));
				lpszStart = lpszTarget + nReplacementLen;
				lpszStart[nBalance] = '\0';
				nOldLength += (nReplacementLen - nSourceLen);
			}
			lpszStart += sa_strlen(lpszStart) + 1;
		}
		assert(m_pchData[nNewLength] == '\0');
		GetData()->nDataLength = nNewLength;
	}

	return nCount;
}

void SAString::TrimRight(const SAChar *lpszTargetList)
{
	// find beginning of trailing matches
	// by starting at beginning (DBCS aware)

	CopyBeforeWrite();
	SAChar *lpsz = m_pchData;
	SAChar *lpszLast = NULL;

	while (*lpsz != '\0')
	{
		if (sa_strchr(lpszTargetList, *lpsz) != NULL)
		{
			if (lpszLast == NULL)
				lpszLast = lpsz;
		}
		else
			lpszLast = NULL;
		++lpsz;
	}

	if (lpszLast != NULL)
	{
		// truncate at left-most matching character
		*lpszLast = '\0';
		GetData()->nDataLength = lpszLast - m_pchData;
	}
}

void SAString::TrimRight(SAChar chTarget)
{
	// find beginning of trailing matches
	// by starting at beginning (DBCS aware)

	CopyBeforeWrite();
	SAChar *lpsz = m_pchData;
	SAChar *lpszLast = NULL;

	while (*lpsz != '\0')
	{
		if (*lpsz == chTarget)
		{
			if (lpszLast == NULL)
				lpszLast = lpsz;
		}
		else
			lpszLast = NULL;
		++lpsz;
	}

	if (lpszLast != NULL)
	{
		// truncate at left-most matching character
		*lpszLast = '\0';
		GetData()->nDataLength = lpszLast - m_pchData;
	}
}

void SAString::TrimRight()
{
	// find beginning of trailing spaces by starting at beginning (DBCS aware)

	CopyBeforeWrite();
	SAChar *lpsz = m_pchData;
	SAChar *lpszLast = NULL;

	while (*lpsz != '\0')
	{
		if (sa_isspace(*lpsz))
		{
			if (lpszLast == NULL)
				lpszLast = lpsz;
		}
		else
			lpszLast = NULL;
		++lpsz;
	}

	if (lpszLast != NULL)
	{
		// truncate at trailing space start
		*lpszLast = '\0';
		GetData()->nDataLength = lpszLast - m_pchData;
	}
}

void SAString::TrimLeft(const SAChar *lpszTargets)
{
	// if we're not trimming anything, we're not doing any work
	if (SafeStrlen(lpszTargets) == 0)
		return;

	CopyBeforeWrite();
	const SAChar *lpsz = m_pchData;

	while (*lpsz != '\0')
	{
		if (sa_strchr(lpszTargets, *lpsz) == NULL)
			break;
		++lpsz;
	}

	if (lpsz != m_pchData)
	{
		// fix up data and length
		int nDataLength = GetData()->nDataLength - (lpsz - m_pchData);
		memmove(m_pchData, lpsz, (nDataLength+1)*sizeof(SAChar));
		GetData()->nDataLength = nDataLength;
	}
}

void SAString::TrimLeft(SAChar chTarget)
{
	// find first non-matching character

	CopyBeforeWrite();
	const SAChar *lpsz = m_pchData;

	while (chTarget == *lpsz)
		++lpsz;

	if (lpsz != m_pchData)
	{
		// fix up data and length
		int nDataLength = GetData()->nDataLength - (lpsz - m_pchData);
		memmove(m_pchData, lpsz, (nDataLength+1)*sizeof(SAChar));
		GetData()->nDataLength = nDataLength;
	}
}

void SAString::TrimLeft()
{
	// find first non-space character

	CopyBeforeWrite();
	const SAChar *lpsz = m_pchData;

	while (sa_isspace(*lpsz))
		++lpsz;

	if (lpsz != m_pchData)
	{
		// fix up data and length
		int nDataLength = GetData()->nDataLength - (lpsz - m_pchData);
		memmove(m_pchData, lpsz, (nDataLength+1)*sizeof(SAChar));
		GetData()->nDataLength = nDataLength;
	}
}

int SAString::Compare(const SAChar *lpsz) const
{
	assert(lpsz);
	return sa_strcmp(m_pchData, lpsz);
}

int SAString::CompareNoCase(const SAChar *lpsz) const
{
	assert(lpsz);

	// implement our own case-insensitive comparison
	// by converting to lower case before comparison
	const SAChar *psThis = m_pchData;
	const SAChar *psOther = lpsz;

	while(*psThis && *psOther)
	{
		int iThis = sa_tolower(*psThis);
		int iOther = sa_tolower(*psOther);
		if(iThis == iOther)
		{
			++psThis;
			++psOther;
			continue;
		}

		if(iThis > iOther)
			return 1;
		return -1;
	}

	if(*psThis && !*psOther)
		return 1;
	if(!*psThis && *psOther)
		return -1;
	assert(!*psThis && !*psOther);
	return 0;
}

int SAString::Collate(const SAChar *lpsz) const
{
	assert(lpsz);
	return sa_strcoll(m_pchData, lpsz);
}

bool operator==(const SAString &s1, const SAString &s2)
{
	return s1.Compare(s2) == 0;
}
bool operator==(const SAString &s1, const SAChar *s2)
{
	return s1.Compare(s2) == 0;
}
bool operator==(const SAChar *s1, const SAString &s2)
{
	return s2.Compare(s1) == 0;
}
bool operator!=(const SAString &s1, const SAString &s2)
{
	return s1.Compare(s2) != 0;
}
bool operator!=(const SAString &s1, const SAChar *s2)
{
	return s1.Compare(s2) != 0;
}
bool operator!=(const SAChar *s1, const SAString &s2)
{
	return s2.Compare(s1) != 0;
}
bool operator<(const SAString &s1, const SAString &s2)
{
	return s1.Compare(s2) < 0;
}
bool operator<(const SAString &s1, const SAChar *s2)
{
	return s1.Compare(s2) < 0;
}
bool operator<(const SAChar *s1, const SAString &s2)
{
	return s2.Compare(s1) > 0;
}
bool operator>(const SAString &s1, const SAString &s2)
{
	return s1.Compare(s2) > 0;
}
bool operator>(const SAString &s1, const SAChar *s2)
{
	return s1.Compare(s2) > 0;
}
bool operator>(const SAChar *s1, const SAString &s2)
{
	return s2.Compare(s1) < 0;
}
bool operator<=(const SAString &s1, const SAString &s2)
{
	return s1.Compare(s2) <= 0;
}
bool operator<=(const SAString &s1, const SAChar *s2)
{
	return s1.Compare(s2) <= 0;
}
bool operator<=(const SAChar *s1, const SAString &s2)
{
	return s2.Compare(s1) >= 0;
}
bool operator>=(const SAString &s1, const SAString &s2)
{
	return s1.Compare(s2) >= 0;
}
bool operator>=(const SAString &s1, const SAChar *s2)
{
	return s1.Compare(s2) >= 0;
}
bool operator>=(const SAChar *s1, const SAString &s2)
{
	return s2.Compare(s1) <= 0;
}

//////////////////////////////////////////////////////////////////////////////
// Finding

int SAString::Find(SAChar ch) const
{
	return Find(ch, 0);
}

int SAString::Find(SAChar ch, int nStart) const
{
	int nLength = GetData()->nDataLength;
	if (nStart >= nLength)
		return -1;

	// find first single character
	const SAChar *lpsz = sa_strchr(m_pchData + nStart, ch);

	// return -1 if not found and index otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

int SAString::FindOneOf(const SAChar *lpszCharSet) const
{
	assert(lpszCharSet);
	const SAChar *lpsz = sa_strpbrk(m_pchData, lpszCharSet);
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

int SAString::ReverseFind(SAChar ch) const
{
	// find last single character
	const SAChar *lpsz = sa_strrchr(m_pchData, ch);

	// return -1 if not found, distance from beginning otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

// find a sub-string (like strstr)
int SAString::Find(const SAChar *lpszSub) const
{
	return Find(lpszSub, 0);
}

int SAString::Find(const SAChar *lpszSub, int nStart) const
{
	assert(lpszSub);

	int nLength = GetData()->nDataLength;
	if (nStart > nLength)
		return -1;

	// find first matching substring
	const SAChar *lpsz = sa_strstr(m_pchData + nStart, lpszSub);

	// return -1 for not found, distance from beginning otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

// Special constructor and buffer access routines to manipulate binary data

// constructor for binary data (no converion to SAChar)
SAString::SAString(const void *pBuffer, int nLengthInBytes)
{
#ifdef SA_UNICODE

	Init();
	if (nLengthInBytes != 0)
	{
		assert(pBuffer);
		int nBinaryDataLengthDiff = nLengthInBytes % sizeof(SAChar);
		// allocate at least so many characters that all binary data can be stored (round up if necessary)
		int nLengthInChars = nLengthInBytes / sizeof(SAChar) + (nBinaryDataLengthDiff? 1 : 0);
		AllocBuffer(nLengthInChars);
		// if nLengthInBytes is not a multiply of sizeof(SAChar)
		// we have to save the difference
		GetData()->nBinaryDataLengthDiff = nBinaryDataLengthDiff;
		memcpy(m_pchData, pBuffer, nLengthInBytes);
	}

#else	// !SA_UNICODE

	// byte == character in non-Unicode build
	Init();
	if (nLengthInBytes != 0)
	{
		assert(pBuffer);
		AllocBuffer(nLengthInBytes);
		memcpy(m_pchData, pBuffer, nLengthInBytes);
	}

#endif	// !SA_UNICODE
}

// get binary data length (in bytes)
int SAString::GetBinaryLength() const
{
#ifdef SA_UNICODE

	return GetLength()*sizeof(SAChar) - GetData()->nBinaryDataLengthDiff;

#else	// !SA_UNICODE

	// byte == character in non-Unicode build
	return GetLength();

#endif	// !SA_UNICODE
}

// return pointer to const binary data buffer
SAString::operator const void *() const
{
	return (const void *)m_pchData;
}

// get pointer to modifiable binary data buffer at least as long as nMinBufLengthInBytes
void *SAString::GetBinaryBuffer(int nMinBufLengthInBytes)
{
#ifdef SA_UNICODE

	// convert bytes count to characters count (round up if necessasry)
	int nMinBufLengthInChars = nMinBufLengthInBytes / sizeof(SAChar) + (nMinBufLengthInBytes % sizeof(SAChar)? 1 : 0);
	// if current LengthInBytes is not a multiply of sizeof(SAChar)
	// we have to save the difference
	// because GetBuffer may discard it
	int nSave = GetData()->nBinaryDataLengthDiff;
	void *pRet = GetBuffer(nMinBufLengthInChars);
	// then restore the difference
	GetData()->nBinaryDataLengthDiff = nSave;
	return pRet;

#else	// !SA_UNICODE

	// byte == character in non-Unicode build
	return GetBuffer(nMinBufLengthInBytes);

#endif	// !SA_UNICODE
}

// release buffer, setting length to nNewLength (or to first nul if -1)
void SAString::ReleaseBinaryBuffer(int nNewLengthInBytes)
{
#ifdef SA_UNICODE

	int nBinaryDataLengthDiff = nNewLengthInBytes % sizeof(SAChar);
	// release at least so many characters that all binary data can be stored (round up if necessary)
	int nNewLengthInChars = nNewLengthInBytes / sizeof(SAChar) + (nBinaryDataLengthDiff? 1 : 0);
	ReleaseBuffer(nNewLengthInChars);
	// if nNewLengthInBytes is not a multiply of sizeof(SAChar)
	// we have to save the difference
	GetData()->nBinaryDataLengthDiff = nBinaryDataLengthDiff;

#else	// !SA_UNICODE

	// byte == character in non-Unicode build
	ReleaseBuffer(nNewLengthInBytes);

#endif	// !SA_UNICODE
}

// Special conversion functions (multi byte <-> unicode)
#ifdef SA_UNICODE

static void ConvertToMultiByteChars(SAStringData *pData)
{
	if(pData->pConvertedData)	// already converted and cached
		return;

	// calculate multi-byte length
	int mbLen = SAWideCharToMultiByte(
		NULL, pData->data(), pData->nDataLength);

	// alocate space for conversion
	pData->pConvertedData = (SAStringConvertedData *)
		new unsigned char[sizeof(SAStringConvertedData) + (mbLen+1)*sizeof(char)];
	pData->pConvertedData->nDataLength = mbLen;
	pData->pConvertedData->data()[mbLen] = '\0';

	// now actually convert
	SAWideCharToMultiByte(pData->pConvertedData->data(), pData->data(), pData->nDataLength);
}

const char *SAString::GetMultiByteChars() const
{
	ConvertToMultiByteChars(GetData());
	return GetData()->pConvertedData->data();
}

int SAString::GetMultiByteCharsLength() const
{
	ConvertToMultiByteChars(GetData());
	return GetData()->pConvertedData->nDataLength;
}

#else	// !SA_UNICODE

static void ConvertToWideChars(SAStringData *pData)
{
	if(pData->pConvertedData)	// already converted and cached
		return;

	// alocate space for conversion
	pData->pConvertedData = (SAStringConvertedData *)
		new unsigned char[sizeof(SAStringConvertedData) + (pData->nDataLength+1)*sizeof(wchar_t)];

	int wLen = SAMultiByteToWideChar(pData->pConvertedData->data(), pData->data(), pData->nDataLength);
	pData->pConvertedData->nDataLength = wLen;
	pData->pConvertedData->data()[wLen] = '\0';
}

const wchar_t *SAString::GetWideChars() const
{
	ConvertToWideChars(GetData());
	return GetData()->pConvertedData->data();
}

int SAString::GetWideCharsLength() const
{
	ConvertToWideChars(GetData());
	return GetData()->pConvertedData->nDataLength;
}

#endif	// !SA_UNICODE

//////////////////////////////////////////////////////////////////////
// SADateTime Class
//////////////////////////////////////////////////////////////////////

/*static */
long  SADateTime::m_saMonthDays[13] =



	{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

// thanks to Microsoft for AFX_STATIC BOOL AFXAPI _AfxOleDateFromTm
/*static */
bool SADateTime::DateFromTm(unsigned short wYear, unsigned short wMonth, unsigned short wDay,
	unsigned short wHour, unsigned short wMinute, unsigned short wSecond,
	unsigned long nNanoSecond,
	double &dtDest)
{
	wYear += (unsigned short)1900;
	// Validate year and month (ignore day of week and milliseconds)
	if (wYear > 9999 || wMonth < 1 || wMonth > 12)
		return false;

	//  Check for leap year and set the number of days in the month
	bool bLeapYear = ((wYear & 3) == 0) &&
		((wYear % 100) != 0 || (wYear % 400) == 0);

	int nDaysInMonth =
		m_saMonthDays[wMonth] - m_saMonthDays[wMonth-1] +
		((bLeapYear && wDay == 29 && wMonth == 2) ? 1 : 0);

	// Finish validating the date
	if (wDay < 1 || wDay > nDaysInMonth ||
		wHour > 23 || wMinute > 59 ||
		wSecond > 59)
	{
		return false;
	}

	// Cache the date in days and time in fractional days
	long nDate;
	double dblTime;

	//It is a valid date; make Jan 1, 1AD be 1
	nDate = wYear*365L + wYear/4 - wYear/100 + wYear/400 +
		m_saMonthDays[wMonth-1] + wDay;

	//  If leap year and it's before March, subtract 1:
	if (wMonth <= 2 && bLeapYear)
		--nDate;

	//  Offset so that 12/30/1899 is 0
	nDate -= 693959L;

	dblTime = (((long)wHour * 3600L) +  // hrs in seconds
		((long)wMinute * 60L) +  // mins in seconds
		((long)wSecond)) / 86400.;
	// add nanoseconds
	double dNanoSec = (double)nNanoSecond/(24.0*60.0*60.0*1e9);
	dblTime += dNanoSec;

	dtDest = (double) nDate + ((nDate >= 0) ? dblTime : -dblTime);

	return true;
}

// AFX_STATIC BOOL AFXAPI _AfxTmFromOleDate(DATE dtSrc, struct tm& tmDest)
/*static */
bool SADateTime::TmFromDate(
	double dtSrc,
	struct tm &tmDest, unsigned long &nNanoSecond)
{
	long MIN_DATE		=	(-657434L);  // about year 100
	long MAX_DATE		=	2958465L;    // about year 9999
//	double HALF_SECOND	=	(1.0/172800.0);

	// The legal range does not actually span year 0 to 9999.
	if (dtSrc > MAX_DATE || dtSrc < MIN_DATE) // about year 100 to about 9999
		return false;

	long nDaysAbsolute;     // Number of days since 1/1/0
	long nSecsInDay;        // Time in seconds since midnight
	long nMinutesInDay;     // Minutes in day

	long n400Years;         // Number of 400 year increments since 1/1/0
	long n400Century;       // Century within 400 year block (0,1,2 or 3)
	long n4Years;           // Number of 4 year increments since 1/1/0
	long n4Day;             // Day within 4 year block
							//  (0 is 1/1/yr1, 1460 is 12/31/yr4)
	long n4Yr;              // Year within 4 year block (0,1,2 or 3)
	bool bLeap4 = true;     // TRUE if 4 year block includes leap year

	double dblDate = dtSrc; // tempory serial date

	// MS Original Code:Round to the second
	// MS Original Code:dblDate += ((dtSrc > 0.0) ? HALF_SECOND : -HALF_SECOND);
	// SQLAPI++ Code:No rounding, we will maintain nanoseconds

	nDaysAbsolute = (long)dblDate + 693959L; // Add days from 1/1/0 to 12/30/1899

	dblDate = fabs(dblDate);
	double dblTime = dblDate - floor(dblDate);
	nSecsInDay = (long)(dblTime * 86400.);

	// Calculate the day of week (sun=1, mon=2...)
	//   -1 because 1/1/0 is Sat.  +1 because we want 1-based
	tmDest.tm_wday = (int)((nDaysAbsolute - 1) % 7L) + 1;

	// Leap years every 4 yrs except centuries not multiples of 400.
	n400Years = (long)(nDaysAbsolute / 146097L);

	// Set nDaysAbsolute to day within 400-year block
	nDaysAbsolute %= 146097L;

	// -1 because first century has extra day
	n400Century = (long)((nDaysAbsolute - 1) / 36524L);

	// Non-leap century
	if (n400Century != 0)
	{
		// Set nDaysAbsolute to day within century
		nDaysAbsolute = (nDaysAbsolute - 1) % 36524L;

		// +1 because 1st 4 year increment has 1460 days
		n4Years = (long)((nDaysAbsolute + 1) / 1461L);

		if (n4Years != 0)
			n4Day = (long)((nDaysAbsolute + 1) % 1461L);
		else
		{
			bLeap4 = false;
			n4Day = (long)nDaysAbsolute;
		}
	}
	else
	{
		// Leap century - not special case!
		n4Years = (long)(nDaysAbsolute / 1461L);
		n4Day = (long)(nDaysAbsolute % 1461L);
	}

	if (bLeap4)
	{
		// -1 because first year has 366 days
		n4Yr = (n4Day - 1) / 365;

		if (n4Yr != 0)
			n4Day = (n4Day - 1) % 365;
	}
	else
	{
		n4Yr = n4Day / 365;
		n4Day %= 365;
	}

	// n4Day is now 0-based day of year. Save 1-based day of year, year number
	tmDest.tm_yday = (int)n4Day + 1;
	tmDest.tm_year = n400Years * 400 + n400Century * 100 + n4Years * 4 + n4Yr;

	// Handle leap year: before, on, and after Feb. 29.
	if (n4Yr == 0 && bLeap4)
	{
		// Leap Year
		if (n4Day == 59)
		{
			/* Feb. 29 */
			tmDest.tm_mon = 2;
			tmDest.tm_mday = 29;

			goto DoTime;
		}

		// Pretend it's not a leap year for month/day comp.
		if (n4Day >= 60)
			--n4Day;
	}

	// Make n4DaY a 1-based day of non-leap year and compute
	//  month/day for everything but Feb. 29.
	++n4Day;

	// Month number always >= n/32, so save some loop time */
	for (tmDest.tm_mon = (n4Day >> 5) + 1;
		n4Day > m_saMonthDays[tmDest.tm_mon]; tmDest.tm_mon++);

	tmDest.tm_mday = (int)(n4Day - m_saMonthDays[tmDest.tm_mon-1]);

DoTime:
	if (nSecsInDay == 0)
		tmDest.tm_hour = tmDest.tm_min = tmDest.tm_sec = 0;
	else
	{
		tmDest.tm_sec = (int)nSecsInDay % 60L;
		nMinutesInDay = nSecsInDay / 60L;
		tmDest.tm_min = (int)nMinutesInDay % 60;
		tmDest.tm_hour = (int)nMinutesInDay / 60;
	}
	double dNanoSecs = dblTime - ((double)nSecsInDay/86400.0);
	assert(dNanoSecs >= 0);
	dNanoSecs *= 24.0 * 60.0 * 60.0 * 1e9;
	assert(dNanoSecs < 1e9);
	nNanoSecond = (unsigned long)dNanoSecs;
	assert(nNanoSecond <= 999999999);

	tmDest.tm_year -= 1900;  // year is based on 1900
	tmDest.tm_mon -= 1;      // month of year is 0-based
	tmDest.tm_wday -= 1;     // day of week is 0-based
	tmDest.tm_yday -= 1;     // day of year is 0-based
	return true;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void SADateTime::Init_Tm()
{
	memset(&m_tm, 0, sizeof(m_tm));
	m_nFraction = 0;
}

SADateTime::SADateTime()
{
	if(!TmFromDate(0.0, m_tm, m_nFraction))
	{
		assert(false);
		Init_Tm();
	}
}

SADateTime::SADateTime(const SADateTime &other)
{
	m_tm = other.m_tm;
	m_nFraction = other.m_nFraction;
}

SADateTime::SADateTime(const struct tm &tmValue)
{
	m_tm = tmValue;
	m_nFraction = 0;
}

SADateTime::operator struct tm &()
{
	return m_tm;
}

SADateTime::operator struct tm() const
{
	return m_tm;
}

SADateTime::SADateTime(double dt)
{
	if(!TmFromDate(dt, m_tm, m_nFraction))
		Init_Tm();
}

SADateTime::operator double() const
{
	double dt;
	if(DateFromTm(
		(unsigned short)m_tm.tm_year, (unsigned short)(m_tm.tm_mon + 1), (unsigned short)m_tm.tm_mday,
		(unsigned short)m_tm.tm_hour, (unsigned short)m_tm.tm_min, (unsigned short)m_tm.tm_sec,
		m_nFraction,
		dt))
		return dt;

	return (double)0;
}

SADateTime::SADateTime(int nYear, int nMonth, int nDay, int nHour, int nMinute, int nSecond)
{
	m_tm.tm_year = nYear - 1900;
	m_tm.tm_mon = nMonth - 1;
	m_tm.tm_mday = nDay;
	m_tm.tm_hour = nHour;
	m_tm.tm_min = nMinute;
	m_tm.tm_sec = nSecond;

	// complete structure
	m_tm.tm_isdst = -1;

	// Validate year and month
	if(nYear > 9999 || nMonth < 1 || nMonth > 12)
		return;

	//  Check for leap year and set the number of days in the month
	bool bLeapYear = ((nYear & 3) == 0) &&
		((nYear % 100) != 0 || (nYear % 400) == 0);

	int nDaysInMonth =
		m_saMonthDays[nMonth] - m_saMonthDays[nMonth-1] +
		((bLeapYear && nDay == 29 && nMonth == 2) ? 1 : 0);

	// Finish validating the date
	if (nDay < 1 || nDay > nDaysInMonth ||
		nHour > 23 || nMinute > 59 ||
		nSecond > 59)
	{
		return;
	}

	// Cache the date in days
	long nDate;

	//It is a valid date; make Jan 1, 1AD be 1
	nDate = nYear*365L + nYear/4 - nYear/100 + nYear/400 +
		m_saMonthDays[nMonth-1] + nDay;

	//  If leap year and it's before March, subtract 1:
	if (nMonth <= 2 && bLeapYear)
		--nDate;

	//   -1 because 1/1/0 is Sat.
	m_tm.tm_wday = (int)((nDate - 1) % 7L);
	// -1 because we want zero-based
	m_tm.tm_yday = nDate - ((nYear-1)*365L + (nYear-1)/4 - (nYear-1)/100 + (nYear-1)/400 +
		m_saMonthDays[12-1] + 31) - 1;

	m_nFraction = 0;
}

unsigned long SADateTime::Fraction() const
{
	return m_nFraction;
}
unsigned long &SADateTime::Fraction()
{
	return m_nFraction;
}

int SADateTime::GetYear() const
{
	return m_tm.tm_year + 1900;
}

int SADateTime::GetMonth() const
{
	return m_tm.tm_mon + 1;
}

int SADateTime::GetDay() const
{
	return m_tm.tm_mday;
}

int SADateTime::GetHour() const
{
	return m_tm.tm_hour;
}

int SADateTime::GetMinute() const
{
	return m_tm.tm_min;
}

int SADateTime::GetSecond() const
{
	return m_tm.tm_sec;
}

int SADateTime::GetDayOfWeek() const
{
	return m_tm.tm_wday + 1;
}

int SADateTime::GetDayOfYear() const
{
	return m_tm.tm_yday + 1;
}

/*static */
SADateTime SADateTime::GetCurrentTime()
{
	SADateTime dt;
	time_t long_time;

	time(&long_time);				// Get time as long integer
#if defined(_REENTRANT)
	localtime_r(&long_time, &(struct tm &)dt);	// Convert to local time
#else
	dt = *localtime(&long_time);	// Convert to local time
#endif

	return dt;
}

//////////////////////////////////////////////////////////////////////
// saOptions Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

saOptions::saOptions()
{
	m_nOptionCount = 0;
	m_ppOptions	= NULL;
}

/*virtual */
saOptions::~saOptions()
{
	while(m_nOptionCount)
		delete m_ppOptions[--m_nOptionCount];
	if(m_ppOptions)
	{
		free(m_ppOptions);
		m_ppOptions = NULL;
	}
}

SAString &saOptions::operator[](const SAString &sOptionName)
{
	SAParam *pRef = NULL;

	// check if option already exists
	for(int i = 0; i < m_nOptionCount; i++)
		if(m_ppOptions[i]->Name().CompareNoCase(sOptionName) == 0)
		{
			pRef = m_ppOptions[i];
			break;
		}

	if(!pRef)	// create new option
	{
		pRef = new SAParam(NULL, sOptionName, SA_dtString, -1, -1, -1, -1, SA_ParamInputOutput);

		m_ppOptions = (SAParam**)realloc(m_ppOptions, (m_nOptionCount+1)*sizeof(SAParam*));
		m_ppOptions[m_nOptionCount] = pRef;
		++m_nOptionCount;
	}

	return pRef->setAsString();
}

SAString saOptions::operator[](const SAString &sOptionName) const
{
	SAString s;

	for(int i = 0; i < m_nOptionCount; i++)
		if(m_ppOptions[i]->Name().CompareNoCase(sOptionName) == 0)
			return m_ppOptions[i]->asString();

	return "";
}

//////////////////////////////////////////////////////////////////////
// SAPos Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SAPos::SAPos(int nByID)
{
	m_sName.Format(_SA("%d"), nByID);
}

SAPos::SAPos(const SAString& sByName) :
	m_sName(sByName)
{
}

//////////////////////////////////////////////////////////////////////
// SAConnection Class

//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SAConnection::SAConnection()
{
	m_eSAClient			= SA_Client_NotSpecified;
	m_pISAConnection	= NULL;
	m_pCommands			= NULL;

	m_eIsolationLevel	= SA_LevelUnknown;
	m_eAutoCommit		= SA_AutoCommitUnknown;
}

SAConnection::~SAConnection()
{
	// we are in destructor, so no exception throwing
	try
	{
		setClient(SA_Client_NotSpecified);

		// walk through registered commands and reregister them
		sa_Commands **pp = &m_pCommands;
		while(*pp)
		{
			SACommand *pCommand = (*pp)->pCommand;
			assert(pCommand);

			pCommand->m_pConnection = NULL;

			pp = &(*pp)->Next;
		}
	}
	catch(SAException &)
	{
		delete m_pISAConnection;
	}
}

void SAConnection::EnumCursors(EnumCursors_t fn, void *pAddlData)
{
	sa_Commands *p = m_pCommands;
	while(p)
	{
		fn(p->pISACursor, pAddlData);
		p = p->Next;
	}
}

void SAConnection::RegisterCommand(SACommand *pCommand)
{
	sa_Commands **pp = &m_pCommands;
	while(*pp)
	{
		assert((*pp)->pCommand != pCommand);
		pp = &(*pp)->Next;
	}

	*pp = new sa_Commands;
	(*pp)->pCommand = pCommand;
	(*pp)->pISACursor = m_pISAConnection? m_pISAConnection->NewCursor(pCommand) : NULL;
	(*pp)->Next = NULL;
}

void SAConnection::UnRegisterCommand(SACommand *pCommand)
{
	sa_Commands **pp = &m_pCommands;
	while(*pp)
	{
		if((*pp)->pCommand == pCommand)
		{
			sa_Commands *pNext = (*pp)->Next;
			delete (*pp)->pISACursor;
			delete *pp;
			*pp = pNext;
			return;
		}
		pp = &(*pp)->Next;
	}

	assert(false);
}

ISACursor *SAConnection::GetISACursor(SACommand *pCommand)
{
	sa_Commands *p = m_pCommands;
	while(p)
	{
		if(p->pCommand == pCommand)
			return p->pISACursor;
		p = p->Next;
	}

	assert(false);
	return NULL;
}

void SAConnection::setClient(SAClient_t eSAClient)
{
	// nothing to do
	if(eSAClient == m_eSAClient)
		return;

	// dispose previous  connection and release client interface
	if(m_eSAClient != SA_Client_NotSpecified)
	{
		if(isConnected())
			Disconnect();
		m_pISAConnection->UnInitializeClient();
		delete m_pISAConnection;
		m_pISAConnection = 0;
		m_eSAClient = SA_Client_NotSpecified;
	}

	// set new client interface
	if(eSAClient != SA_Client_NotSpecified)
	{
		ISAClient *pISAClient = stat_SAClients[eSAClient];
		if(!pISAClient)
			throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SUPPORTED);

		ISAConnection *pISAConnection = pISAClient->QueryConnectionInterface(this);
		try
		{
			pISAConnection->InitializeClient();
		}
		catch(SAException &)	// clean up on error
		{
			delete pISAConnection;
			throw;
		}
		m_pISAConnection = pISAConnection;
		m_eSAClient = eSAClient;
	}

	// walk through registered commands and reregister them
	sa_Commands **pp = &m_pCommands;
	while(*pp)
	{
		SACommand *pCommand = (*pp)->pCommand;
		assert(pCommand);

		delete (*pp)->pISACursor;
		(*pp)->pISACursor = NULL;
		(*pp)->pISACursor = m_pISAConnection? m_pISAConnection->NewCursor(pCommand) : NULL;
		pp = &(*pp)->Next;
	}
}

SAClient_t SAConnection::Client() const
{
	return m_eSAClient;
}

long SAConnection::ClientVersion() const
{
	if(!m_pISAConnection)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	return m_pISAConnection->GetClientVersion();
}

long SAConnection::ServerVersion() const
{
	if(!m_pISAConnection)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	return m_pISAConnection->GetServerVersion();
}

SAString SAConnection::ServerVersionString() const
{
	if(!m_pISAConnection)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	return m_pISAConnection->GetServerVersionString();
}

bool SAConnection::isConnected() const
{
	if(!m_pISAConnection)
		return false;

	return m_pISAConnection->IsConnected();
}

void SAConnection::Connect(
	const SAString &sDBString,
	const SAString &sUserID,
	const SAString &sPassword,
	SAClient_t eSAClient)
{
	if(eSAClient != SA_Client_NotSpecified)
		setClient(eSAClient);

	if(!m_pISAConnection)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	// now actually connect
	m_pISAConnection->Connect(sDBString, sUserID, sPassword);

#if !defined(SA_NO_TRIAL)
	CheckTrial();
#endif	// !defined(SA_NO_TRIAL)
}

void SAConnection::Disconnect()
{
	if(!m_pISAConnection)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	// walk through all commands and close them
	sa_Commands *p = m_pCommands;
	while(p)
	{
		SACommand *pCommand = p->pCommand;
		assert(pCommand);

		if(pCommand->isOpened())
			pCommand->Close();

		p = p->Next;
	}

	// now actually disconnect
	m_pISAConnection->Disconnect();
}

void SAConnection::Commit()
{
	if(!m_pISAConnection)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	if(m_pISAConnection->IsConnected())
		m_pISAConnection->Commit();
}

void SAConnection::Rollback()
{
	if(!m_pISAConnection)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	if(m_pISAConnection->IsConnected())
		m_pISAConnection->Rollback();
}

void SAConnection::setIsolationLevel(
	SAIsolationLevel_t eIsolationLevel)
{
	if(!m_pISAConnection)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	if(eIsolationLevel == m_eIsolationLevel)
		return;
	if(eIsolationLevel == SA_LevelUnknown)
		return;

	m_pISAConnection->setIsolationLevel(eIsolationLevel);
	m_eIsolationLevel = eIsolationLevel;
}

SAIsolationLevel_t SAConnection::IsolationLevel() const
{
	return m_eIsolationLevel;
}

void SAConnection::setAutoCommit(SAAutoCommit_t eAutoCommit)
{
	if(!m_pISAConnection)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	if(eAutoCommit == m_eAutoCommit)
		return;
	if(eAutoCommit == SA_AutoCommitUnknown)
		return;

	m_pISAConnection->setAutoCommit(eAutoCommit);
	m_eAutoCommit = eAutoCommit;

	// notify commands
	sa_Commands *p = m_pCommands;
	while(p)
	{
		p->pISACursor->OnConnectionAutoCommitChanged();
		p = p->Next;
	}
}

SAAutoCommit_t SAConnection::AutoCommit() const
{
	return m_eAutoCommit;
}

SAString &SAConnection::setOption(const SAString &sOptionName)
{
	SAString &s = m_Options[sOptionName];
	return s;
}

SAString SAConnection::Option(const SAString &sOptionName) const
{
	SAString s = m_Options[sOptionName];
	return s;
}

saAPI *SAConnection::NativeAPI() const
{
	if(!m_pISAConnection)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	return m_pISAConnection->NativeAPI();
}

saConnectionHandles *SAConnection::NativeHandles()
{
	if(!m_pISAConnection)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	return m_pISAConnection->NativeHandles();
}

//////////////////////////////////////////////////////////////////////
// SACommand Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void SACommand::Init()
{
	m_pConnection = NULL;

	m_eCmdType = SA_CmdUnknown;
	m_bPrepared = false;
	m_bExecuted = false;
	m_bFieldsDescribed = false;
	m_bSelectBuffersSet = false;

	m_bParamsKnown = false;
	m_nPlaceHolderCount = 0;
	m_ppPlaceHolders = NULL;
	m_nParamCount = 0;
	m_ppParams	= NULL;
	m_nCurParamID = 0;

	m_nFieldCount = 0;
	m_ppFields = NULL;
}

SAParam &SACommand::CreateParam(
	const SAString &sName,
	SADataType_t eParamType,
	int nNativeType,
	int nParamSize,
	int	nParamPrecision,
	int	nParamScale,
	SAParamDirType_t eDirType)
{
	m_bParamsKnown = true;
	return CreateParam(sName, eParamType, nNativeType,
		nParamSize, nParamPrecision, nParamScale, eDirType, sName, -1, -1);
}

SAParam &SACommand::CreateParam(
	const SAString &sName,
	SADataType_t eParamType,
	int nNativeType,
	int nParamSize,
	int	nParamPrecision,
	int	nParamScale,
	SAParamDirType_t eDirType,
	const SAString &sFullName,
	int nStart,	// param position in SQL statement
	int nEnd)	// param end position in SQL statemen
{
	SAParam *pRef = NULL;
	// first see if param with given name already exist
	for(int i = 0; i < m_nParamCount; ++i)
		if(m_ppParams[i]->m_sName.CompareNoCase(sName) == 0) {
			pRef = m_ppParams[i];
			break;
		}
	if(!pRef)	// create param
	{
		pRef = new SAParam(this, sName, eParamType, nNativeType, nParamSize, nParamPrecision, nParamScale, eDirType);

		m_ppParams = (SAParam**)realloc(m_ppParams, (m_nParamCount+1)*sizeof(SAParam*));
		m_ppParams[m_nParamCount] = pRef;
		++m_nParamCount;
	}

	// create place holder
	m_ppPlaceHolders = (saPlaceHolder**)realloc(m_ppPlaceHolders, (m_nPlaceHolderCount+1)*sizeof(saPlaceHolder));
	m_ppPlaceHolders[m_nPlaceHolderCount] = new saPlaceHolder(sFullName, nStart, nEnd, pRef);
	++m_nPlaceHolderCount;

	return *pRef;
}

void SACommand::CreateField(
	const SAString &sName,
	SADataType_t eFieldType,
	int nNativeType,
	int nFieldSize,
	int nFieldPrecision,
	int nFieldScale,
	bool bFieldRequired)
{
	SAField *pField =
		new SAField(
		*this, m_nFieldCount+1, sName,
		eFieldType, nNativeType,
		nFieldSize, nFieldPrecision, nFieldScale, bFieldRequired);
	m_ppFields = (SAField**)realloc(m_ppFields, (m_nFieldCount+1)*sizeof(SAField*));
	m_ppFields[m_nFieldCount] = pField;
	++m_nFieldCount;
}

void SACommand::UnDescribeParams()
{
	DestroyParams();
	m_bParamsKnown = false;
}

void SACommand::DestroyParams()
{
	while(m_nPlaceHolderCount)
		delete m_ppPlaceHolders[--m_nPlaceHolderCount];
	if(m_ppPlaceHolders)
	{
		free(m_ppPlaceHolders);
		m_ppPlaceHolders = NULL;
	}
	while(m_nParamCount)
		delete m_ppParams[--m_nParamCount];
	if(m_ppParams)
	{
		free(m_ppParams);
		m_ppParams = NULL;
	}
}

void SACommand::DestroyFields()
{
	while(m_nFieldCount)
		delete m_ppFields[--m_nFieldCount];
	if(m_ppFields)
	{
		free(m_ppFields);
		m_ppFields = NULL;
	}

	m_bFieldsDescribed = false;
	m_bSelectBuffersSet = false;
}

// construct command with no associated connection
SACommand::SACommand()
{
	Init();

	setConnection(NULL);
	setCommandText("");
}

// construct command based on the given connection
SACommand::SACommand(
	SAConnection *pConnection,
	const SAString &sSQL,
	SACommandType_t eCmdType)
{
	Init();

	setConnection(pConnection);
	setCommandText(sSQL, eCmdType);
}

/*virtual */
SACommand::~SACommand()
{
	UnDescribeParams();
	DestroyFields();

	// we are in destructor, so no exception throwing
	try
	{
		setConnection(NULL);
	}
	catch(SAException &)
	{
		if(m_pConnection)
			m_pConnection->UnRegisterCommand(this);
	}
}

SAConnection* SACommand::Connection() const
{
	return m_pConnection;
}

void SACommand::setConnection(SAConnection *pConnection)
{
	if(m_pConnection)
	{
		if(isOpened())
			Close();
		m_pConnection->UnRegisterCommand(this);
	}

	m_pConnection = pConnection;
	if(m_pConnection)
		m_pConnection->RegisterCommand(this);
}

void SACommand::Open()
{
	ISACursor *pISACursor = m_pConnection? m_pConnection->GetISACursor(this) : NULL;
	if(!pISACursor)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	pISACursor->Open();
}

bool SACommand::isOpened()
{
	ISACursor *pISACursor = m_pConnection? m_pConnection->GetISACursor(this) : NULL;
	if(!pISACursor)
		return false;

	return pISACursor->IsOpened();
}

void SACommand::Close()
{
	ISACursor *pISACursor = m_pConnection? m_pConnection->GetISACursor(this) : NULL;
	if(!pISACursor)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	UnPrepare();

	pISACursor->Close();
}


void SACommand::ParseCmd(
	const SAString &sCmd,
	SACommandType_t eCmdType)
{
	UnDescribeParams();
	m_sCmd = sCmd;
	m_eCmdType = eCmdType;
	m_nCurParamID = 1;
	
	if(eCmdType == SA_CmdStoredProc)
		return;	// no parsing required if this is stored proc name

	SAString sName, sFullName;

	const SAChar Literals[] = {'\'', '"', '`', 0};
	const SAChar NameDelimiters[] = {' ', ',', ';', ')', '\r', '\n', 0};

	const SAChar *Value, *CurPos, *StartPos;
	SAChar CurChar;
	bool Literal;
	bool EmbeddedLiteral;

	SAString sCmdToAnalyse = sCmd;
	Value = sCmdToAnalyse;
	CurPos = Value;
	Literal = false;
	EmbeddedLiteral = false;
	// simple test for StoredProc - no spaces
	bool bSpacesInCmd = false;
	do
	{
		CurChar = *CurPos;
		// check that this command can not be a stored procedure
		if(!bSpacesInCmd && CurChar == ' ' && !Literal)
			bSpacesInCmd = true;
		if((CurChar == ':') && !Literal && (*(CurPos + 1) != ':' && *(CurPos + 1) != '='))
		{
			StartPos = CurPos;
			while((CurChar != 0) && (Literal || !sa_strchr(NameDelimiters, CurChar)))
			{
				++CurPos;
				CurChar = *CurPos;
				if(CurChar && sa_strchr(Literals, CurChar))
				{
					Literal = !Literal;
					if(CurPos == StartPos + 1)
						EmbeddedLiteral = true;
				}
			}
			if(EmbeddedLiteral)
			{
				const SAChar *sTemp = StartPos + 1;
				const SAChar *sTempLast = CurPos-1;
				if(*sTemp && sa_strchr(Literals, *sTemp))
					++sTemp;
				if(*sTempLast && sa_strchr(Literals, *sTempLast))
					--sTempLast;
				sName = SAString(sTemp, sTempLast-sTemp+1);

				EmbeddedLiteral = false;
			}
			else
				sName = SAString(StartPos + 1, CurPos-StartPos-1);

			sFullName = SAString(StartPos + 1, CurPos-StartPos-1);

			CreateParam(
				sName,
				SA_dtUnknown,
				-1,	// native data type
				0, -1, -1,	// size, precision, scale
				SA_ParamInput,
				sFullName, StartPos-Value, CurPos-1-Value);
		}
		else if(CurChar && sa_strchr(Literals, CurChar))
			Literal = !Literal;
		++CurPos;
	}
	while(CurChar != 0);

	if(m_nParamCount > 0)
	{
		m_bParamsKnown = true;
		if(m_eCmdType == SA_CmdUnknown)
			m_eCmdType = SA_CmdSQLStmt;
	}

	// still unknown
	if(m_eCmdType == SA_CmdUnknown)
	{
		if(bSpacesInCmd || sCmdToAnalyse.IsEmpty())
			m_eCmdType = SA_CmdSQLStmt;
		else
			m_eCmdType = SA_CmdStoredProc;
	}

	if(m_eCmdType == SA_CmdSQLStmt && !m_bParamsKnown)
		m_bParamsKnown = true;

	assert(m_eCmdType != SA_CmdUnknown);
}

void SACommand::UnSetCommandText()
{
	UnPrepare();

	UnDescribeParams();
	m_eCmdType = SA_CmdUnknown;
	m_sCmd.Empty();
}

SAString SACommand::CommandText() const
{
	return m_sCmd;
}
SACommandType_t SACommand::CommandType() const
{
	return m_eCmdType;
}

void SACommand::UnExecute()
{
	// notify DBMS client API
	// that it can release resources from previous execution
	if(m_bExecuted)
	{
		ISACursor *pISACursor = m_pConnection? m_pConnection->GetISACursor(this) : NULL;
		if(!pISACursor)
			throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

		pISACursor->UnExecute();
	}

	DestroyFields();
	m_nCurParamID = 1;

	m_bExecuted = false;
}

void SACommand::UnPrepare()
{
	UnExecute();

	m_bPrepared = false;
}

void SACommand::setCommandText(
	const SAString &sCmd,
	SACommandType_t eCmdType)
{
	UnSetCommandText();	// clean up
	ParseCmd(sCmd, eCmdType);
}

void SACommand::Prepare()
{
	if(m_bPrepared)
		return;

	ISACursor *pISACursor = m_pConnection? m_pConnection->GetISACursor(this) : NULL;
	if(!pISACursor)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	UnPrepare();

	if(!isOpened())
		Open();

	pISACursor->Prepare(
		m_sCmd,
		m_eCmdType,
		m_nPlaceHolderCount, m_ppPlaceHolders);
	m_bPrepared = true;
}

void SACommand::Execute()
{       
	ISACursor *pISACursor = m_pConnection? m_pConnection->GetISACursor(this) : NULL;
	if(!pISACursor)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	UnExecute();

	// if not yet
	Prepare();


	pISACursor->Execute(m_nPlaceHolderCount, m_ppPlaceHolders);
	m_bExecuted = true;
}

void SACommand::Cancel()
{
	ISACursor *pISACursor = m_pConnection? m_pConnection->GetISACursor(this) : NULL;
	if(!pISACursor)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	pISACursor->Cancel();
}

bool SACommand::isResultSet()
{
	ISACursor *pISACursor = m_pConnection? m_pConnection->GetISACursor(this) : NULL;
	if(!pISACursor)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	if(!m_bExecuted)	// no need to disturb native API
		return false;

	return pISACursor->ResultSetExists();
}

#include <locale.h>

bool SACommand::FetchNext()
{
	if(!m_bFieldsDescribed)
		DescribeFields();

	ISACursor *pISACursor = m_pConnection? m_pConnection->GetISACursor(this) : NULL;
	if(!pISACursor)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	if(!m_bSelectBuffersSet)
	{
		pISACursor->SetSelectBuffers();
		m_bSelectBuffersSet = true;
	}

	bool bFetch = pISACursor->FetchNext();
	if(!bFetch)
	{
		if(isResultSet())	// new result set available?
		{
			DestroyFields();
			DescribeFields();
		}
	}
	return bFetch;
}

long SACommand::RowsAffected()
{
	ISACursor *pISACursor = m_pConnection? m_pConnection->GetISACursor(this) : NULL;
	if(!pISACursor)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	if(!m_bExecuted)	// no need to disturb native API
		return -1;

	return pISACursor->GetRowsAffected();
}

void SACommand::GetParamsSP()
{
	assert(m_bParamsKnown == false);
	ISACursor *pISACursor = m_pConnection? m_pConnection->GetISACursor(this) : NULL;
	if(!pISACursor)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	if(!isOpened())
		Open();

	pISACursor->DescribeParamSP();
	m_bParamsKnown = true;
}

int SACommand::ParamCount()
{
	if(!m_bParamsKnown)
	{
		assert(m_eCmdType == SA_CmdStoredProc);
		GetParamsSP();
	}
	return m_nParamCount;
}

SAParam &SACommand::ParamByIndex(int i)	// zero based index of C array
{
	if(!m_bParamsKnown)
	{
		assert(m_eCmdType == SA_CmdStoredProc);
		GetParamsSP();
	}
	assert(i < m_nParamCount);
	return *m_ppParams[i];
}

SAParam &SACommand::Param(int nParamByID)	// id in SQL statement, not in C array
{
	SAString s;
	s.Format(_SA("%d"), nParamByID);
	return Param(s);
}


SAParam &SACommand::Param(const SAString& sParamByName)
{
	int iReturn = -1;
	int i;
	for(i = 0; i < ParamCount(); i++)
	{
		if(ParamByIndex(i).Name().CompareNoCase(sParamByName) == 0)
			return ParamByIndex(i);

		// save, may be useful for special test
		if(iReturn == -1 && ParamByIndex(i).ParamDirType() == SA_ParamReturn)
			iReturn = i;
	}

	// special test for return of a fuction
	// we can refer to this parameter as "RETURN_VALUE"
	// on all DMBSs regardless of how they describe it (to be portable)
	if(sParamByName.CompareNoCase(_SA("RETURN_VALUE")) == 0 && iReturn != -1)
		return ParamByIndex(iReturn);

	if(i >= ParamCount())
		throw SAException(SA_Library_Error, -1, -1, IDS_BIND_VAR_NOT_FOUND, (const SAChar*)sParamByName);

	return *((SAParam *)0);
}

SACommand &SACommand::operator << (const SAPos& pos)
{
	m_sCurParamName = pos.m_sName;
	m_nCurParamID = sa_toi(m_sCurParamName);

	return *this;
}

SACommand &SACommand::operator << (const SANull&)
{
	SAParam &param =
		m_nCurParamID >= 1? Param(m_nCurParamID) : Param(m_sCurParamName);
	m_nCurParamID++;

	param.setAsNull();
	return *this;
}

SACommand &SACommand::operator << (bool Value)
{
	SAParam &param =
		m_nCurParamID >= 1? Param(m_nCurParamID) : Param(m_sCurParamName);
	m_nCurParamID++;

	param.setAsBool() = Value;
	return *this;
}

SACommand &SACommand::operator << (short Value)
{
	SAParam &param =
		m_nCurParamID >= 1? Param(m_nCurParamID) : Param(m_sCurParamName);
	m_nCurParamID++;

	param.setAsShort() = Value;
	return *this;
}

SACommand &SACommand::operator << (long Value)
{
	SAParam &param =
		m_nCurParamID >= 1? Param(m_nCurParamID) : Param(m_sCurParamName);
	m_nCurParamID++;

	param.setAsLong() = Value;
	return *this;
}

SACommand &SACommand::operator << (double Value)
{
	SAParam &param =
		m_nCurParamID >= 1? Param(m_nCurParamID) : Param(m_sCurParamName);
	m_nCurParamID++;
	param.setAsDouble() = Value;
	return *this;
}

SACommand &SACommand::operator << (const SADateTime &Value)
{
	SAParam &param =
		m_nCurParamID >= 1? Param(m_nCurParamID) : Param(m_sCurParamName);
	m_nCurParamID++;

	param.setAsDateTime() = Value;
	return *this;
}

SACommand &SACommand::operator << (const struct tm &Value)
{
	SAParam &param =
		m_nCurParamID >= 1? Param(m_nCurParamID) : Param(m_sCurParamName);
	m_nCurParamID++;

	param.setAsDateTime() = Value;
	return *this;
}

// special overload for string constants
SACommand &SACommand::operator << (const SAChar *Value)
{
	return operator << (SAString(Value));
}

SACommand &SACommand::operator << (const SAString &Value)
{
	SAParam &param =
		m_nCurParamID >= 1? Param(m_nCurParamID) : Param(m_sCurParamName);
	m_nCurParamID++;

	param.setAsString() = Value;
	return *this;
}

SACommand &SACommand::operator << (const SABytes &Value)
{
	SAParam &param =
		m_nCurParamID >= 1? Param(m_nCurParamID) : Param(m_sCurParamName);
	m_nCurParamID++;

	param.setAsBytes() = Value;
	return *this;
}

SACommand &SACommand::operator << (const SALongBinary &Value)
{
	SAParam &param =
		m_nCurParamID >= 1? Param(m_nCurParamID) : Param(m_sCurParamName);
	m_nCurParamID++;

	param.setAsLongBinary(
		Value.m_fnWriter,
		Value.m_nWriterPieceSize,
		Value.m_pAddlData) = Value;
	return *this;
}

SACommand &SACommand::operator << (const SALongChar &Value)
{
	SAParam &param =
		m_nCurParamID >= 1? Param(m_nCurParamID) : Param(m_sCurParamName);
	m_nCurParamID++;

	param.setAsLongChar(
		Value.m_fnWriter,
		Value.m_nWriterPieceSize,
		Value.m_pAddlData) = Value;
	return *this;
}

SACommand &SACommand::operator << (const SABLob &Value)
{
	SAParam &param =
		m_nCurParamID >= 1? Param(m_nCurParamID) : Param(m_sCurParamName);
	m_nCurParamID++;


	param.setAsBLob(
		Value.m_fnWriter,
		Value.m_nWriterPieceSize,
		Value.m_pAddlData) = Value;
	return *this;
}

SACommand &SACommand::operator << (const SACLob &Value)
{
	SAParam &param =
		m_nCurParamID >= 1? Param(m_nCurParamID) : Param(m_sCurParamName);
	m_nCurParamID++;

	param.setAsCLob(
		Value.m_fnWriter,
		Value.m_nWriterPieceSize,
		Value.m_pAddlData) = Value;
	return *this;
}

void SACommand::DescribeFields()
{
	assert(m_bFieldsDescribed == false);

	ISACursor *pISACursor = m_pConnection? m_pConnection->GetISACursor(this) : NULL;
	if(!pISACursor)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	DestroyFields();

	pISACursor->DescribeFields(&SACommand::CreateField);
	m_bFieldsDescribed = true;
}

int SACommand::FieldCount()
{
	if(!m_bFieldsDescribed)
		DescribeFields();

	return m_nFieldCount;
}

SAField &SACommand::Field(int nField)	// 1-based field number in result set
{
	if(!m_bFieldsDescribed)
		DescribeFields();

	assert(nField > 0);
	assert(nField <= m_nFieldCount);
	return *m_ppFields[nField-1];
}

SAField &SACommand::Field(const SAString& sField)
{
//printf("WWWWWWWWWW sfiled=%s\n",(char *)&sField);
	int i;
	for(i = 0; i < FieldCount(); i++)
		if(m_ppFields[i]->Name().CompareNoCase(sField) == 0)
			return *m_ppFields[i];

	if(i >= FieldCount())
		throw SAException(SA_Library_Error, -1, -1, IDS_FIELD_NOT_FOUND, (const SAChar*)sField);

	return *((SAField *)0);
}

SAField &SACommand::operator[](int nField)	// 1-based field number in result set
{
	return Field(nField);
}

SAField &SACommand::operator[](const SAString& sField)
{
	return Field(sField);
}

SAString &SACommand::setOption(const SAString &sOptionName)
{
	SAString &s = m_Options[sOptionName];
	return s;
}

SAString SACommand::Option(const SAString &sOptionName) const
{
	SAString s = m_Options[sOptionName];
	return s.IsEmpty() && m_pConnection? m_pConnection->Option(sOptionName) : s;
}

saCommandHandles *SACommand::NativeHandles()
{
	ISACursor *pISACursor = m_pConnection? m_pConnection->GetISACursor(this) : NULL;
	if(!pISACursor)
		throw SAException(SA_Library_Error, -1, -1, IDS_CLIENT_NOT_SET);

	if(!isOpened())
		Open();

	return pISACursor->NativeHandles();
}

//////////////////////////////////////////////////////////////////////
// SAException Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SAException::SAException(
	SAErrorClass_t eError,
	int nNativeError,
	int nErrPos,
	const SAString &sMsg) :
	m_eErrorClass(eError),
	m_nNativeError(nNativeError),
	m_nErrPos(nErrPos),
	m_sMsg(sMsg)
{
}

SAException::SAException(
	SAErrorClass_t eError,
	int nNativeError,
	int nErrPos,
	const SAChar *lpszFormat, ...) :
	m_eErrorClass(eError),
	m_nNativeError(nNativeError),
	m_nErrPos(nErrPos)
{
	va_list argList;
	va_start(argList, lpszFormat);
	m_sMsg.FormatV(lpszFormat, argList);
	va_end(argList);
}

SAException::SAException(const SAException &other)
{
	m_eErrorClass	= other.m_eErrorClass;
	m_nNativeError	= other.m_nNativeError;
	m_nErrPos		= other.m_nErrPos;
	m_sMsg			= other.m_sMsg;
}

/*virtual */
SAException::~SAException()
{
}

/*static */
void SAException::throwUserException(
	int nUserCode,
	const SAChar *lpszFormat, ...)
{
	va_list argList;
	va_start(argList, lpszFormat);
	SAString sMsg;
	sMsg.FormatV(lpszFormat, argList);
	va_end(argList);

	throw SAUserException(nUserCode, sMsg);
}

SAErrorClass_t SAException::ErrClass() const
{
	return m_eErrorClass;
}
int SAException::ErrNativeCode() const
{
	return m_nNativeError;
}
int SAException::ErrPos() const
{
	return m_nErrPos;
}
SAString SAException::ErrText() const
{
	return m_sMsg;
}

SAUserException::SAUserException(int nUserCode, const SAString &sMsg) :
	SAException(SA_UserGenerated_Error, nUserCode, -1, sMsg)
{
}

/*virtual */
SAUserException::~SAUserException()
{
}

//////////////////////////////////////////////////////////////////////
// saPlaceHolder Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

saPlaceHolder::saPlaceHolder(
	const SAString &sFullName,
	int nStart,
	int nEnd,
	SAParam *pParamRef) :
	m_sFullName(sFullName),
	m_nStart(nStart),
	m_nEnd(nEnd),
	m_pParamRef(pParamRef)
{
}

/*virtual */
saPlaceHolder::~saPlaceHolder()
{
}

const SAString &saPlaceHolder::getFullName() const
{
	return m_sFullName;
}

int saPlaceHolder::getStart() const
{
	return m_nStart;
}

int saPlaceHolder::getEnd() const
{
	return m_nEnd;
}

SAParam *saPlaceHolder::getParam() const
{
	return m_pParamRef;
}

//////////////////////////////////////////////////////////////////////

// SAValue Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SAValueRead::SAValueRead(SADataType_t eDataType) :
	m_eReaderMode(SA_LongOrLobReaderDefault),	// into internal buffer
	m_nReaderWantedPieceSize(0),
	m_pReaderAddlData(NULL),
	m_pReaderBuf(NULL),
	m_nReaderAlloc(0)
{
	m_eDataType = eDataType;

	// null indicator
	m_bInternalNull = true;
	m_pbNull = &m_bInternalNull;
	// scalar types
	memset(&m_InternalScalar, 0, sizeof(m_InternalScalar));
	m_pScalar = &m_InternalScalar;
	// an exact numeric value with a fixed precision and scale
	m_pNumeric = &m_InternalNumeric;
	// Date time
	m_pDateTime = &m_InternalDateTime;
	// variable length types (string, bytes, Longs and Lobs)
	m_pString = &m_InternalString;
	// Cursor
	m_pCursor = &m_InternalCursor;
}

SAValue::SAValue(SADataType_t eDataType) :
	SAValueRead(eDataType),
	m_fnWriter(NULL),	// from internal buffer
	m_nWriterSize(0),			// by default blob will be bound by max avail Pieces
	m_pWriterAddlData(NULL),	// no data for default writer
	m_pWriterBuf(NULL),
	m_nWriterAlloc(0)
{
}

SAValueRead::~SAValueRead()
{
	if(m_pReaderBuf)
		free(m_pReaderBuf);
}

SAValue::~SAValue()
{
	if(m_pWriterBuf)
		free(m_pWriterBuf);
}

SADataType_t SAValueRead::DataType() const
{
	return m_eDataType;
}

bool SAValueRead::isNull() const
{
	return *m_pbNull;
}

void SAValue::setAsNull()
{
	*m_pbNull = true;
}

void SAValue::setAsUnknown()
{
	m_eDataType = SA_dtUnknown;
}

#define SAValueConvertScalar(targetType) case SA_dtBool: return (targetType)*(bool*)m_pScalar; case SA_dtShort: return (targetType)*(short*)m_pScalar; case SA_dtLong: return (targetType)*(long*)m_pScalar; case SA_dtDouble: return (targetType)*(double*)m_pScalar;

signed short SAValueRead::asShort() const
{
	if(isNull())
		return 0;

	switch(m_eDataType)
	{
		SAValueConvertScalar(short)

	case SA_dtUnknown:
		assert(false);
		break;
	case SA_dtNumeric:
		return (short)(double)(*m_pNumeric);
	case SA_dtDateTime:
		assert(false);	// do not convert to short from date/time
		break;
	case SA_dtString:
		// try to convert
		{
			SAChar *pEnd;
			double d = sa_strtod(*m_pString, &pEnd);
			if(*pEnd != 0)
				throw SAException(SA_Library_Error, -1, -1, IDS_CONVERTION_FROM_STRING_TO_SHORT_ERROR, (const SAChar*)*m_pString);
			return (short)d;
		}
	case SA_dtBytes:
		assert(false);	// do not convert to short from bytes
		break;
	case SA_dtLongBinary:
	case SA_dtLongChar:
	case SA_dtBLob:
	case SA_dtCLob:
		assert(false);	// do not convert to short from Lob
		break;
	case SA_dtCursor:
		assert(false);
		break;
	default:
		assert(false);	// unknown type
	}
	
	return 0;
}

short &SAValue::setAsShort()
{
	*m_pbNull = false;
	m_eDataType = SA_dtShort;
	return *(short*)m_pScalar;
}

signed long SAValueRead::asLong() const
{
	if(isNull())
		return 0;

	switch(m_eDataType)
	{
		SAValueConvertScalar(long)

	case SA_dtUnknown:
		assert(false);
		break;
	case SA_dtNumeric:
		return (long)(double)(*m_pNumeric);
	case SA_dtDateTime:
		assert(false);	// do not convert to long from date/time
		break;
	case SA_dtString:
		// try to convert
		{
			SAChar *pEnd;
			double d = sa_strtod(*m_pString, &pEnd);
			if(*pEnd != 0)
				throw SAException(SA_Library_Error, -1, -1, IDS_CONVERTION_FROM_STRING_TO_LONG_ERROR, (const SAChar*)*m_pString);
			return (long)d;
		}
	case SA_dtBytes:
		assert(false);	// do not convert to long from bytes
		break;
	case SA_dtLongBinary:
	case SA_dtLongChar:
	case SA_dtBLob:
	case SA_dtCLob:
		assert(false);	// do not convert to long from Lob
		break;
	case SA_dtCursor:
		assert(false);
		break;
	default:
		assert(false);	// unknown type
	}
	
	return 0;
}

long &SAValue::setAsLong()
{
	*m_pbNull = false;
	m_eDataType = SA_dtLong;
	return *(long*)m_pScalar;
}

double SAValueRead::asDouble() const
{
	if(isNull())
		return 0;

	switch(m_eDataType)
	{
		SAValueConvertScalar(double)

	case SA_dtUnknown:
		assert(false);
		break;
	case SA_dtNumeric:
		return (double)(*m_pNumeric);
	case SA_dtDateTime:
		assert(false);	// do not convert to double from date/time
		break;
	case SA_dtString:
		// try to convert
		{
			SAChar *pEnd;
			double d = sa_strtod(*m_pString, &pEnd);
			if(*pEnd != 0)
				throw SAException(SA_Library_Error, -1, -1, IDS_CONVERTION_FROM_STRING_TO_DOUBLE_ERROR, (const SAChar*)*m_pString);
			return d;
		}
	case SA_dtBytes:
		assert(false);	// do not convert to double from bytes
		break;
	case SA_dtLongBinary:
	case SA_dtLongChar:
	case SA_dtBLob:
	case SA_dtCLob:
		assert(false);	// do not convert to double from Lob
		break;
	case SA_dtCursor:
		assert(false);
		break;
	default:
		assert(false);	// unknown type
	}
	
	return 0;
}

double &SAValue::setAsDouble()
{
	*m_pbNull = false;
	m_eDataType = SA_dtDouble;
	return *(double*)m_pScalar;
}

SANumeric SAValueRead::asNumeric() const
{
	if(isNull())
		return (double)0;

	switch(m_eDataType)
	{
		// all scalar types are converted to SANumeric through double
		SAValueConvertScalar(double)

	case SA_dtUnknown:
		assert(false);
		break;
	case SA_dtNumeric:
		return *m_pNumeric;
	case SA_dtDateTime:
		assert(false);	// do not convert to SANumeric from date/time
		break;
	case SA_dtString:
		// try to convert from const SAChar*
		{
			SANumeric num;
			num = *m_pString;
			return num;
		}
	case SA_dtBytes:
		assert(false);	// do not convert to SANumeric from bytes
		break;
	case SA_dtLongBinary:
	case SA_dtLongChar:
	case SA_dtBLob:
	case SA_dtCLob:
		assert(false);	// do not convert to SANumeric from Lob
		break;
	case SA_dtCursor:
		assert(false);
		break;
	default:
		assert(false);	// unknown type
	}
	
	return (double)0;
}

SANumeric &SAValue::setAsNumeric()
{
	*m_pbNull = false;
	m_eDataType = SA_dtNumeric;
	return *m_pNumeric;
}

bool SAValueRead::asBool() const
{
	if(isNull())
		return false;

	switch(m_eDataType)
	{
	case SA_dtBool:
		return *(bool*)m_pScalar;
	case SA_dtShort:
		return *(short*)m_pScalar != 0;
	case SA_dtLong:
		return *(short*)m_pScalar != 0;
	case SA_dtDouble:
		return *(short*)m_pScalar != 0;

	case SA_dtUnknown:
		assert(false);
		break;
	case SA_dtNumeric:
		assert(false);	// do not convert to bool from numeric
	case SA_dtDateTime:
		assert(false);	// do not convert to bool from date/time
		break;
	case SA_dtString:
		assert(false);	// do not convert to bool from string
		break;
	case SA_dtBytes:
		assert(false);	// do not convert to bool from bytes
		break;
	case SA_dtLongBinary:
	case SA_dtLongChar:
	case SA_dtBLob:
	case SA_dtCLob:
		assert(false);	// do not convert to bool from Lob
		break;
	case SA_dtCursor:
		assert(false);
		break;
	default:
		assert(false);	// unknown type
	}
	
	return false;
}

bool &SAValue::setAsBool()
{
	*m_pbNull = false;
	m_eDataType = SA_dtBool;
	return *(bool*)m_pScalar;
}

SADateTime SAValueRead::asDateTime() const
{
	assert(!isNull());
	switch(m_eDataType)
	{
	case SA_dtUnknown:
		assert(false);	// do not convert to date/time from NULL
		break;
	case SA_dtBool:
	case SA_dtShort:
	case SA_dtLong:
	case SA_dtDouble:
		assert(false);	// do not convert to date/time from scalar types
		break;
	case SA_dtNumeric:
		assert(false);	// do not convert to date/time from numeric
	case SA_dtDateTime:
		return *m_pDateTime;
	case SA_dtString:
	case SA_dtBytes:
		assert(false);	// do not convert to date/time from string
	case SA_dtLongBinary:
	case SA_dtLongChar:
	case SA_dtBLob:
	case SA_dtCLob:
		assert(false);	// do not convert to date/time from Blob
	case SA_dtCursor:
		assert(false);
		break;
	default:
		assert(false);	// unknown type
	}

	SADateTime dt;
	return dt;
}

SADateTime &SAValue::setAsDateTime()
{
	*m_pbNull = false;
	m_eDataType = SA_dtDateTime;
	return *m_pDateTime;
}

SAString SAValueRead::asString() const
{
	if(isNull())
		return SAString();

	int nLenInBytes;
	SAString s;
	struct tm tmTemp;
	
	switch(m_eDataType)
	{
	case SA_dtUnknown:
		assert(false);
		break;
	case SA_dtBool:
		if(*(bool *)m_pScalar)
			return _SA("true");
		return _SA("false");
	case SA_dtShort:
		s.Format(_SA("%hd"), *(short*)m_pScalar);
		return s;
	case SA_dtLong:
		s.Format(_SA("%ld"), *(long*)m_pScalar);
		return s;
	case SA_dtDouble:	// 15 is the maximum precision of double
		s.Format(_SA("%.*g"), 15, *(double*)m_pScalar);
		return s;
	case SA_dtNumeric:
		return m_pNumeric->operator SAString();
	case SA_dtDateTime:
		tmTemp = *m_pDateTime;
		s = asctime(&tmTemp);
		s.Delete(s.GetLength()-1);	// remove '\n'
		return s;
	case SA_dtString:
	case SA_dtLongChar:
	case SA_dtCLob:
		return *m_pString;
	case SA_dtBytes:
	case SA_dtLongBinary:
	case SA_dtBLob:
		// convert to hexadecimal string
		nLenInBytes = m_pString->GetBinaryLength();
		if(nLenInBytes)
		{
			SAChar *p2 = s.GetBuffer(nLenInBytes*2);	// 2 characters for each byte
			const void *p = *m_pString;
			for(int i = 0; i < nLenInBytes; ++i)
			{
				sa_sprintf(p2, _SA("%02x"), *(const unsigned char*)p);
				++((const unsigned char*&)p);
				p2 += 2;
			}
			s.ReleaseBuffer(nLenInBytes*2);
		}
		return s;
	case SA_dtCursor:
		assert(false);
		break;
	default:
		assert(false);	// unknown type
	}

	return SAString();
}

SAString &SAValue::setAsString()
{
	*m_pbNull = false;
	m_eDataType = SA_dtString;
	return *m_pString;
}

SAString SAValueRead::asBytes() const
{
	if(isNull())
		return "";

	switch(m_eDataType)
	{
	case SA_dtUnknown:
		assert(false);
		break;
	case SA_dtBool:
		return SAString((const void*)m_pScalar, sizeof(bool));
	case SA_dtShort:
		return SAString((const void*)m_pScalar, sizeof(short));
	case SA_dtLong:
		return SAString((const void*)m_pScalar, sizeof(long));
	case SA_dtDouble:
		return SAString((const void*)m_pScalar, sizeof(double));
	case SA_dtNumeric:
		return SAString((const void*)m_pNumeric, sizeof(SANumeric));
	case SA_dtDateTime:
		return SAString((const void*)m_pDateTime, sizeof(SADateTime));
	case SA_dtString:
	case SA_dtBytes:
	case SA_dtLongBinary:
	case SA_dtLongChar:
	case SA_dtBLob:
	case SA_dtCLob:
		return *m_pString;
	case SA_dtCursor:
		assert(false);
		break;
	default:
		assert(false);	// unknown type
	}

	return "";
}

SAString &SAValue::setAsBytes()
{
	*m_pbNull = false;
	m_eDataType = SA_dtBytes;
	return *m_pString;
}

SAString SAValueRead::asLongOrLob() const
{
	if(isNull())
		return "";

	SAString s;
	switch(m_eDataType)
	{
	case SA_dtUnknown:
		assert(false);
		break;
	case SA_dtBool:
	case SA_dtShort:
	case SA_dtLong:
	case SA_dtDouble:
		assert(false);	// do not convert from scalar types
		break;
	case SA_dtNumeric:
		assert(false);	// do not convert from numeric
		break;
	case SA_dtDateTime:
		assert(false);	// do not convert from date/time
		break;
	case SA_dtString:
	case SA_dtBytes:
	case SA_dtLongBinary:
	case SA_dtLongChar:
	case SA_dtBLob:
	case SA_dtCLob:
		return *m_pString;
	case SA_dtCursor:
		assert(false);	// do not convert from cursor
		break;
	default:
		assert(false);	// unknown type
	}

	return "";
}

SAString SAValueRead::asLongBinary() const
{
	return asLongOrLob();
}

SAString SAValueRead::asLongChar() const
{
	return asLongOrLob();
}

SAString SAValueRead::asBLob() const
{
	return asLongOrLob();
}

SAString SAValueRead::asCLob() const
{
	return asLongOrLob();
}

SAValueRead::operator bool() const
{
	return asBool();
}

SAValueRead::operator short() const
{
	return asShort();
}

SAValueRead::operator long() const
{
	return asLong();
}

SAValueRead::operator double() const
{
	return asDouble();
}

SAValueRead::operator SADateTime() const
{
	return asDateTime();
}

SAValueRead::operator SAString() const
{
	return asString();
}

SAValueRead::operator SACommand *() const
{
	return asCursor();
}

SAString &SAValue::setAsLongBinary(
	saLongOrLobWriter_t fnWriter,
	unsigned int nWriterSize, void *pAddlData)
{
	*m_pbNull = false;
	m_eDataType = SA_dtLongBinary;
	m_fnWriter = fnWriter;
	m_nWriterSize = nWriterSize;
	m_pWriterAddlData = pAddlData;
	return *m_pString;
}

SAString &SAValue::setAsLongChar(
	saLongOrLobWriter_t fnWriter,
	unsigned int nWriterSize, void *pAddlData)
{
	*m_pbNull = false;
	m_eDataType = SA_dtLongChar;
	m_fnWriter = fnWriter;
	m_nWriterSize = nWriterSize;
	m_pWriterAddlData = pAddlData;
	return *m_pString;
}

SAString &SAValue::setAsBLob(
	saLongOrLobWriter_t fnWriter,
	unsigned int nWriterSize, void *pAddlData)
{
	*m_pbNull = false;
	m_eDataType = SA_dtBLob;
	m_fnWriter = fnWriter;
	m_nWriterSize = nWriterSize;
	m_pWriterAddlData = pAddlData;
	return *m_pString;
}

SAString &SAValue::setAsCLob(
	saLongOrLobWriter_t fnWriter,
	unsigned int nWriterSize, void *pAddlData)
{
	*m_pbNull = false;
	m_eDataType = SA_dtCLob;
	m_fnWriter = fnWriter;
	m_nWriterSize = nWriterSize;
	m_pWriterAddlData = pAddlData;
	return *m_pString;
}

SACommand *SAValueRead::asCursor() const
{
	if(isNull())
		return NULL;

	switch(m_eDataType)
	{
	case SA_dtUnknown:
		assert(false);
		break;
	case SA_dtCursor:
		return m_pCursor;
	default:
		assert(false);	// do not convert from any type other then cursor
	}

	return NULL;
}

SACommand *&SAValue::setAsCursor()
{
	*m_pbNull = false;
	m_eDataType = SA_dtCursor;
	return m_pCursor;
}

void SAValueRead::setLongOrLobReaderMode(SALongOrLobReaderModes_t eMode)
{
	m_eReaderMode = eMode;
}

SALongOrLobReaderModes_t SAValueRead::LongOrLobReaderMode() const
{
	return m_eReaderMode;
}

unsigned int SAValueRead::PrepareReader(
	unsigned int nExpectedSizeMax,	// to optimaze buf allocation for internal buffer, 0 = unknown
	unsigned int nCallerMaxSize,	// max Piece that can be proceeced by API
	unsigned char *&pBuf,
	saLongOrLobReader_t fnReader,
	unsigned int nReaderWantedPieceSize,
	void *pReaderAddlData,
	bool bAddSpaceForNull)
{
	m_fnReader = fnReader;
	m_nReaderWantedPieceSize = nReaderWantedPieceSize;
	m_pReaderAddlData = pReaderAddlData;

	m_nExpectedSizeMax = nExpectedSizeMax;
	m_nReaderRead = 0;
	m_nPieceSize = sa_min(m_nReaderWantedPieceSize? m_nReaderWantedPieceSize : 0xFFFF, nCallerMaxSize);

	if(m_fnReader == NULL)	// prepare internal buffer
	{
		// if max size of data is known then alloc the whole buffer at once
		// otherwise allocate space for one piece of data
		unsigned int nPrepareSize = nExpectedSizeMax? nExpectedSizeMax : m_nPieceSize;
		pBuf = (unsigned char*)m_pString->GetBinaryBuffer(nPrepareSize);

		return sa_min(m_nPieceSize, nPrepareSize);
	}

	// prepare buffer for user supplied handler
	if(m_nReaderAlloc < m_nPieceSize + (bAddSpaceForNull? 1:0))
	{
		m_nReaderAlloc = m_nPieceSize + (bAddSpaceForNull? 1:0);
		m_pReaderBuf = (unsigned char*)realloc(m_pReaderBuf, m_nReaderAlloc);
	}
	pBuf = m_pReaderBuf;

	return m_nPieceSize;
}

void SAValueRead::InvokeReader(
	SAPieceType_t ePieceType,
	unsigned char *&pBuf,
	unsigned int nPieceLen)
{
	m_nReaderRead += nPieceLen;
	assert(m_nExpectedSizeMax == 0 || m_nReaderRead <= m_nExpectedSizeMax);

	if(m_fnReader == NULL)
	{
		// data was fetched into internal buffer, just prepare for next iteration
		m_pString->ReleaseBinaryBuffer(m_nReaderRead);

		if(ePieceType != SA_OnePiece && ePieceType != SA_LastPiece)
		{
			if(m_nExpectedSizeMax == 0)	// blob size was unknown
			{
				// expand buffer == prepare it for the next iteration
				// buffer can be relocated, we are ready
				pBuf = (unsigned char*)m_pString->GetBinaryBuffer(m_nReaderRead + m_nPieceSize);
				pBuf += m_nReaderRead;
			}
			else	// buffer is big enough, just increase the pointer == prepare it for the next iteration
				pBuf += nPieceLen;
		}
	}
	else
	{
		// call user supplied handler
		assert(nPieceLen <= m_nReaderAlloc);
		m_fnReader(ePieceType, pBuf, nPieceLen, m_nExpectedSizeMax, m_pReaderAddlData);
	}
}

unsigned int SAValue::InvokeWriter(
	SAPieceType_t &ePieceType,
	int nCallerMaxSize,
	void *&pBuf)
{
	assert(!isNull());

	unsigned int nSize =
		sa_min(m_nWriterSize? m_nWriterSize : 0xFFFF, nCallerMaxSize);

	if(ePieceType == SA_FirstPiece)
		m_nWriterWritten = 0;

	if(m_fnWriter == NULL)	// use internal buffer
	{
		pBuf = (void*)(const void*)*m_pString;
		(const unsigned char *&)pBuf += m_nWriterWritten;
		unsigned int nWritten =
			(unsigned int)m_pString->GetBinaryLength() > m_nWriterWritten? sa_min(nSize, m_pString->GetBinaryLength() - m_nWriterWritten) : 0;
		m_nWriterWritten += nWritten;

		if(m_nWriterWritten < (unsigned int)m_pString->GetBinaryLength())
			ePieceType = SA_NextPiece;
		else
			ePieceType = SA_LastPiece;

		return nWritten;
	}

	if(m_nWriterAlloc < nSize)
	{
		m_pWriterBuf = realloc(m_pWriterBuf, nSize);
		m_nWriterAlloc = nSize;
	}
	pBuf = m_pWriterBuf;

	unsigned int nWritten = m_fnWriter(ePieceType, m_pWriterBuf, nSize, m_pWriterAddlData);
	m_nWriterWritten += nWritten;

	if(ePieceType == SA_FirstPiece)
		ePieceType = SA_NextPiece;

	return nWritten;
}

void SAValueRead::setDataStorage(void *pStorage, SADataType_t eDataType)
{
	m_eDataType = eDataType;

	if(pStorage)
	{
		m_pScalar = pStorage;
		m_pNumeric = (SANumeric *)pStorage;
		m_pDateTime = (SADateTime *)pStorage;
		m_pString = (SAString *)pStorage;
		m_pCursor = (SACommand *)pStorage;
	}
	else
	{
		m_pScalar = &m_InternalScalar;
		m_pNumeric = &m_InternalNumeric;
		m_pDateTime = &m_InternalDateTime;
		m_pString = &m_InternalString;
		m_pCursor = &m_InternalCursor;
	}
}

void SAValueRead::setIndicatorStorage(bool *pStorage)
{
	if(pStorage)
		m_pbNull = pStorage;
	else
		m_pbNull = &m_bInternalNull;
}

//////////////////////////////////////////////////////////////////////
// SAParam Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SAParam::SAParam(
	SACommand *pCommand,
	const SAString &sName,
	SADataType_t eParamType,
	int nNativeType,
	int nParamSize,
	int	nParamPrecision,
	int	nParamScale,
	SAParamDirType_t eDirType) :
		SAValue(eParamType),
		m_pCommand(pCommand),
		m_sName(sName),
		m_eParamType(eParamType),
		m_nNativeType(nNativeType),
		m_nParamSize(nParamSize),
		m_nParamPrecision(nParamPrecision),
		m_nParamScale(nParamScale),
		m_eDirType(eDirType)
{
}

/*virtual */
SAParam::~SAParam()
{
}

void SAParam::ReadLongOrLob(
	saLongOrLobReader_t fnReader,
	unsigned int nReaderWantedSize,
	void *pAddlData)
{
	assert(m_pCommand);
	ISACursor *pISACursor = m_pCommand->Connection()->GetISACursor(m_pCommand);
	assert(pISACursor);

	void *pValue;
	unsigned int nParamBufSize;
	pISACursor->GetParamBuffer(*this, pValue, nParamBufSize);
	pISACursor->ReadLongOrLOB(ISACursor::ISA_ParamValue, *this, pValue, nParamBufSize, fnReader, nReaderWantedSize, pAddlData);
}

const SAString &SAParam::Name() const
{
	return m_sName;
}
SADataType_t SAParam::ParamType() const
{
	return m_eParamType;
}
void SAParam::setParamType(SADataType_t eParamType)
{
	m_eParamType = eParamType;
}
int SAParam::ParamNativeType() const
{
	return m_nNativeType;
}
void SAParam::setParamNativeType(int nNativeType)
{
	m_nNativeType = nNativeType;
}
int SAParam::ParamSize() const
{
	return m_nParamSize;
}
void SAParam::setParamSize(int nParamSize)
{
	m_nParamSize = nParamSize;
}
SAParamDirType_t SAParam::ParamDirType() const
{
	return m_eDirType;
}
void SAParam::setParamDirType(SAParamDirType_t eParamDirType)
{
	m_eDirType = eParamDirType;
}
int SAParam::ParamPrecision() const
{
	return m_nParamPrecision;
}
void SAParam::setParamPrecision(int precision)
{
	m_nParamPrecision = precision;
}
int SAParam::ParamScale() const
{
	return m_nParamScale;
}
void SAParam::setParamScale(int scale)
{
	m_nParamScale = scale;
}

//////////////////////////////////////////////////////////////////////
// SAField Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SAField::SAField(
		SACommand &Command,
		int nPos,	// 1-based
		const SAString &sName,
		SADataType_t eFieldType,
		int nNativeType,
		int nFieldSize,
		int nFieldPrecision,
		int nFieldScale,
		bool bFieldRequired) :
	SAValueRead(eFieldType),
	m_Command(Command),
	m_nPos(nPos),
	m_sName(sName),
	m_eFieldType(eFieldType),
	m_nNativeType(nNativeType),
	m_nFieldSize(nFieldSize),
	m_nFieldPrecision(nFieldPrecision),
	m_nFieldScale(nFieldScale),
	m_bFieldRequired(bFieldRequired)
{
}

/*virtual */
SAField::~SAField()
{
}

void SAField::ReadLongOrLob(
	saLongOrLobReader_t fnReader,
	unsigned int nReaderWantedSize,
	void *pAddlData)
{
	ISACursor *pISACursor = m_Command.Connection()->GetISACursor(&m_Command);
	assert(pISACursor);

	void *pValue;
	unsigned int nFieldBufSize;
	pISACursor->GetFieldBuffer(Pos(), pValue, nFieldBufSize);

	pISACursor->ReadLongOrLOB(ISACursor::ISA_FieldValue, *this, pValue, nFieldBufSize, fnReader, nReaderWantedSize, pAddlData);
}

int SAField::Pos() const
{
	return m_nPos;
}
const SAString &SAField::Name() const
{
	return m_sName;
}
SADataType_t SAField::FieldType() const
{
	return m_eFieldType;
}
int SAField::FieldNativeType() const
{
	return m_nNativeType;
}
int SAField::FieldSize() const
{
	return m_nFieldSize;
}
int SAField::FieldPrecision() const
{
	return m_nFieldPrecision;
}
int SAField::FieldScale() const
{
	return m_nFieldScale;
}
bool SAField::isFieldRequired() const
{
	return m_bFieldRequired;
}

SABytes::SABytes(
	const SAString &sData) :
	SAString(sData)
{
}

SALongOrLob::SALongOrLob(
	const SAString &sData) :
	SAString(sData)
{
}

SALongOrLob::SALongOrLob(
	saLongOrLobWriter_t fnWriter,
	unsigned int nWriterPieceSize,
	void *pAddlData) :
	m_fnWriter(fnWriter),
	m_nWriterPieceSize(nWriterPieceSize),
	m_pAddlData(pAddlData)
{
}

SALongBinary::SALongBinary(
	const SAString &sData) :
	SALongOrLob(sData)
{
}

SALongBinary::SALongBinary(
	saLongOrLobWriter_t fnWriter,
	unsigned int nWriterPieceSize,
	void *pAddlData) :
	SALongOrLob(fnWriter, nWriterPieceSize, pAddlData)
{
}

SALongChar::SALongChar(
	const SAString &sData) :
	SALongOrLob(sData)
{
}

SALongChar::SALongChar(
	saLongOrLobWriter_t fnWriter,
	unsigned int nWriterPieceSize,
	void *pAddlData) :
	SALongOrLob(fnWriter, nWriterPieceSize, pAddlData)
{
}

SABLob::SABLob(
	const SAString &sData) :
	SALongOrLob(sData)
{
}

SABLob::SABLob(
	saLongOrLobWriter_t fnWriter,
	unsigned int nWriterPieceSize,
	void *pAddlData) :
	SALongOrLob(fnWriter, nWriterPieceSize, pAddlData)
{
}

SACLob::SACLob(
	const SAString &sData) :
	SALongOrLob(sData)
{
}

SACLob::SACLob(
	saLongOrLobWriter_t fnWriter,
	unsigned int nWriterPieceSize,
	void *pAddlData) :
	SALongOrLob(fnWriter, nWriterPieceSize, pAddlData)
{
}

//////////////////////////////////////////////////////////////////////
// SANumeric Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// SANumeric Helpers
//////////////////////////////////////////////////////////////////////

static void LittleEndianDivide(
	const unsigned char Devidend[],
	unsigned char Devisor,
	unsigned char Quotient[],
	unsigned char *pRemainder)
{
	unsigned short sh = 0;
	for(int i = 0; i < SA_NUMERIC_MANTISSA_SIZE; ++i)
	{
		sh <<= 8;
		sh = (unsigned short)(sh + Devidend[SA_NUMERIC_MANTISSA_SIZE-i-1]);

		assert(sh / Devisor == (unsigned char)(sh / Devisor));	// no truncation here
		Quotient[SA_NUMERIC_MANTISSA_SIZE-i-1] = (unsigned char)(sh / Devisor);
		sh %= Devisor;
	}

	if(pRemainder)
		*pRemainder = (unsigned char)sh;
}

static bool MantissaIsZero(const unsigned char Mantissa[])
{
	for(unsigned int i = 0; i < SA_NUMERIC_MANTISSA_SIZE; ++i)
		if(Mantissa[i])
			return false;

	return true;
}

//////////////////////////////////////////////////////////////////////
// Implementation
//////////////////////////////////////////////////////////////////////

void SANumeric::InitZero()
{
	precision = 1;
	scale = 0;
	sign = 1;

	memset(val, 0, sizeof(val));
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SANumeric::SANumeric()
{
	InitZero();
}

// initializes from double
SANumeric::SANumeric(double d)
{
	InitZero();
	*this = d;
}

SANumeric &SANumeric::operator=(double d)
{
	InitZero();

	SAString s;
	s.Format(_SA("%.*e"), 15, d);
	
	int p = s.Find(_SA('.'));
	int e = s.Find(_SA('e'));
	
	SAString sSign;
	SAString sInt;
	if(s.Left(1) == _SA('-'))
	{
		sSign = s.Left(1);
		sInt = s.Mid(1, p-1);
	}
	else
		sInt = s.Left(p);
	
	SAString sDec = s.Mid(p+1, e-p-1);
	sDec.TrimRight(_SA('0'));
	SAString sExp = s.Mid(e+1);
	int nExp10 = sa_toi(sExp);
	
	SAString sResult = sInt + sDec;

	int Precision = sResult.GetLength();
	int Scale = sDec.GetLength();

	if(nExp10 + 1 >= 0)
	{
		if(nExp10 + 1 < Precision)
			sResult.Insert(nExp10 + 1, _SA('.'));
		else
			sResult += SAString(_SA('0'), nExp10 - Scale);
	}
	else
		sResult = _SA('.') + SAString(_SA('0'), -(nExp10 + 1)) + sResult;
	
	*this = sSign + sResult;

	return *this;
}

// initialize from string
SANumeric &SANumeric::operator=(const SAChar *s)
{
	if(!s || !*s)
		throw SAException(SA_Library_Error, -1, -1, IDS_CONVERTION_FROM_STRING_TO_NUMERIC_ERROR, s);

	InitZero();

	// set sign
	if(*s == _SA('-'))
	{
		this->sign = 0;
		++s;
	}
	else
	{
		this->sign = 1;
		if(*s == _SA('+'))
			++s;
	}

	// convert from string to little endian 10000-based number
	unsigned short Num10000[64];
	memset(Num10000, 0, sizeof(Num10000));
	int Num10000pos = 0;
	int i = sa_strlen(s);
	this->precision = (unsigned char)i;
	while(i > 0)
	{
		if(s[i-1] == '.')
			this->scale = (unsigned char)(this->precision-- - i--);
		unsigned short i0 = (unsigned short)(i > 0? s[--i] - _SA('0') : 0);
		assert(i0 <= 9);
		if(s[i-1] == '.')
			this->scale = (unsigned char)(this->precision-- - i--);
		unsigned short i1 = (unsigned short)(i > 0? s[--i] - _SA('0') : 0);
		assert(i1 <= 9);
		if(s[i-1] == '.')
			this->scale = (unsigned char)(this->precision-- - i--);
		unsigned short i2 = (unsigned short)(i > 0? s[--i] - _SA('0') : 0);
		assert(i2 <= 9);
		if(s[i-1] == '.')
			this->scale = (unsigned char)(this->precision-- - i--);
		unsigned short i3 = (unsigned short)(i > 0? s[--i] - _SA('0') : 0);
		assert(i3 <= 9);

		Num10000[Num10000pos++] = (unsigned short)(i0 + 10*i1 + 100*i2 + 1000*i3);
	}

	// convert mantissa
	unsigned short Zero[sizeof(Num10000)/sizeof(short)];
	memset(Zero, 0, sizeof(Zero));

	int Num256pos = 0;
	while(memcmp(Num10000, Zero, sizeof(Num10000)) != 0)
	{
		unsigned short Reminder;
		LittleEndian10000BaseDivide(
			sizeof(Num10000)/sizeof(short),
			Num10000,
			256,
			Num10000,
			&Reminder);

		assert(Reminder == (unsigned char)Reminder);	// no truncation here
		this->val[Num256pos++] = (unsigned char)Reminder;
		if(Num256pos == sizeof(this->val))
			break;	// we have to truncate the number
	}

	return *this;
}

//////////////////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////////////////

SANumeric::operator double() const
{
	double n = 0.;
	double e = 1;
	for(unsigned int iVal = 0; iVal < sizeof(val); ++iVal)
	{
		n += this->val[iVal] * e;
		e *= 256;
	}

	for(unsigned char iScale = 0; iScale < this->scale; iScale++)
		n /= 10;

	if(this->sign == 0)	// for negative numbers
		n = -n;

	return n;
}

SANumeric::operator SAString() const
{
	unsigned char Devidend[sizeof(val)];
	memcpy(Devidend, val, sizeof(val));

	SAString s;
	if(MantissaIsZero(Devidend))
		s = _SA("0");
	else
	{
		unsigned char iScale = this->scale;
		while(!MantissaIsZero(Devidend))
		{
			unsigned char Reminder;
			LittleEndianDivide(Devidend, 10, Devidend, &Reminder);

			s = SAChar(Reminder + '0') + s;
			if(iScale && iScale-- == 1)
				s = SAChar('.') + s;
		}
		while(iScale > 0)
		{
			s = SAChar('0') + s;
			if(iScale-- == 1)
				s = SAChar('.') + s;
		}
		if(this->sign == 0)	// for negative numbers
			s = _SA("-") + s;
	}

	return s;
}
