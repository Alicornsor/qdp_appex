// ISAClient.cpp: implementation of the ISAClient class.
//
//////////////////////////////////////////////////////////////////////

#include <SQLAPI.h>
#include "ISAClient.h"

#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>	// memcpy
#include <locale.h>	// setlocale

#include "errmsg.h"

#define SA_Align16(x)	(((x+15) >> 4) << 4)

//////////////////////////////////////////////////////////////////////
// Helpers
//////////////////////////////////////////////////////////////////////

SQLAPI_API char * SA_setlocale(int category, const char *locale)
{
	return setlocale(category, locale);
}

// numeric support/conversions helpers

void LittleEndian10000BaseDivide(
	unsigned int LittleEndianSize,	// in shorts
	const unsigned short Devidend[],
	unsigned short Devisor,
	unsigned short Quotient[],
	unsigned short *pRemainder)
{
	unsigned long ln = 0;
	for(unsigned int i = 0; i < LittleEndianSize; ++i)
	{
		ln *= 10000;
		ln += Devidend[LittleEndianSize-i-1];

		assert((unsigned long)(ln / Devisor) == (unsigned long)(unsigned short)(ln / Devisor));	// no truncation here
		Quotient[LittleEndianSize-i-1] = (unsigned short)(ln / Devisor);
		ln %= Devisor;
	}

	if(pRemainder)
		*pRemainder = (unsigned short)ln;
}

// Character sets conversion helpers

// returns number of chars written
unsigned int SAMultiByteToWideChar(
	wchar_t *pchDataTgt,
	const char *lpch, int nLength, char **lppchStop)
{
	wchar_t *pchData = pchDataTgt;
	const char *mbchar = lpch;
	size_t count = (size_t)nLength;
	while(count > 0)
	{
		int nLen = mbtowc(pchData, mbchar, count);
		if(nLen == -1)	// object that mbchar points to does not form a valid multibyte character within the first count characters
			break;	// stop conversion
		if(nLen == 0)	// mbchar is NULL or the object that it points to is a null character
		{
			// 1 = length of multi-byte '\0'
			++mbchar;
			--count;
		}
		else
		{
			// nLen = length of last multi-byte character
			mbchar += nLen;
			count -= nLen;
		}
		++pchData;
	}

	if(lppchStop)
		*lppchStop = (char*)mbchar;
	return pchData - pchDataTgt;
}

// returns number of chars written
// if pchDataTgt is NULL, function simply counts
unsigned int SAWideCharToMultiByte(
	char *pchDataTgt,
	const wchar_t *lpch, int nLength)
{
	int nWritten = 0;
	for(int i = 0; i < nLength; ++i)
	{
		int nLen;
		if(pchDataTgt)
			nLen = wctomb(pchDataTgt + nWritten, lpch[i]);
		else
		{
			char sTemp[128];
			nLen = wctomb(sTemp, lpch[i]);
		}
		if(nLen == -1)	// the conversion is not possible in the current locale
		{
			if(pchDataTgt)
				pchDataTgt[nWritten] = '?';
			++nWritten;
		}
		else
			nWritten += nLen;
	}

	return nWritten;
}


//////////////////////////////////////////////////////////////////////
// ISAClient Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ISAClient::ISAClient()
{
}

ISAClient::~ISAClient()
{
}

//////////////////////////////////////////////////////////////////////
// ISAConnection Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ISAConnection::ISAConnection(SAConnection *pSAConnection) :
	m_pSAConnection(pSAConnection)
{
}

ISAConnection::~ISAConnection()
{
}

SAConnection *ISAConnection::getSAConnection()
{
	return m_pSAConnection;
}

void ISAConnection::EnumCursors(EnumCursors_t fn, void *pAddlData)
{
	if(!m_pSAConnection)
		return;

	m_pSAConnection->EnumCursors(fn, pAddlData);
}

//////////////////////////////////////////////////////////////////////
// ISACursor Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ISACursor::ISACursor(
	ISAConnection *pISAConnection,
	SACommand *pCommand) :
	m_pISAConnection(pISAConnection),
	m_pCommand(pCommand)
{
	m_pParamBuffer = NULL;
	m_nParamIndSize = 0;
	m_nParamSizeSize = 0;

	m_pSelectBuffer = NULL;
	m_nIndSize = 0;
	m_nSizeSize = 0;
	m_nBulkReadingBufSize = 0;
}

/*virtual */
ISACursor::~ISACursor()
{
	if(m_pParamBuffer)
		free(m_pParamBuffer);
	if(m_pSelectBuffer)
		free(m_pSelectBuffer);
}

/*virtual */
unsigned int ISACursor::InputBufferSize(
	const SAParam &Param) const
{
	assert(Param.ParamDirType() == SA_ParamInput
		|| Param.ParamDirType() == SA_ParamInputOutput);

	if(Param.isNull())
		return 0;

	switch(Param.DataType())
	{
	case SA_dtUnknown:
		throw SAException(SA_Library_Error, -1, -1, IDS_UNKNOWN_PARAMETER_TYPE, (const SAChar*)Param.Name());
	case SA_dtBool:
		assert(false);	// sould be overloaded
		break;
	case SA_dtShort:
		return sizeof(short);
	case SA_dtLong:
		return sizeof(long);
	case SA_dtDouble:
		return sizeof(double);
	case SA_dtNumeric:
		assert(false);	// sould be overloaded
		break;
	case SA_dtDateTime:
		assert(false);	// sould be overloaded
		return 0;
	case SA_dtString:
		// defualt implementation:
		// 1) no space for '\0' is reserved
		// 2) always returns size in single characters (converts to multi-byte under Unicode)
		// So, under Unicode this should be overloaded
		// by clients that bind Unicode strings directly
		// without converting them to multi-byte before binding
		return Param.asString().GetMultiByteCharsLength();
	case SA_dtBytes:
		// in bytes, not characters
		return Param.asBytes().GetBinaryLength();
	case SA_dtLongBinary:
	case SA_dtLongChar:
	case SA_dtBLob:
	case SA_dtCLob:
		assert(false);	// sould be overloaded
		return 0;
	case SA_dtCursor:
		assert(false);	// sould be overloaded
		return 0;
	default:
		assert(false);	// unknown type
	}

	return 0;
}

// align all members to 16-byte boundary
// it will speed up data access on Intel
// and it is very important on RISK 
// platforms (like SPARC Solaris) to avoid non-aligment
void ISACursor::AllocBindBuffer(
	unsigned int nIndSize,
	unsigned int nSizeSize)
{
	m_nParamIndSize = nIndSize;
	m_nParamSizeSize = nSizeSize;

	unsigned int nAllocatedSize = 0;

	int cParamCount = m_pCommand->ParamCount();
	for(int iParam = 0; iParam < cParamCount; ++iParam)
	{
		SAParam &Param = m_pCommand->ParamByIndex(iParam);

		unsigned int nCurParamSize = 0;
		nCurParamSize += SA_Align16(sizeof(unsigned int));	// space allocated for data
		nCurParamSize += SA_Align16(nIndSize);	// null indicator
		nCurParamSize += SA_Align16(nSizeSize);	// space for returned size

		unsigned int nDataSize;
		switch(Param.ParamDirType())
		{
		case SA_ParamInput:
			nDataSize = InputBufferSize(Param);
			break;
		case SA_ParamInputOutput:
			nDataSize = sa_max(InputBufferSize(Param), OutputBufferSize(Param.ParamType(), Param.ParamSize()));
			break;
		case SA_ParamOutput:
		case SA_ParamReturn:
			nDataSize = OutputBufferSize(Param.ParamType(), Param.ParamSize());
			break;
		default:
			nDataSize = 0;
			assert(false);
		}
		nCurParamSize += SA_Align16(nDataSize);

		m_pParamBuffer = realloc(
			m_pParamBuffer,
			nAllocatedSize + nCurParamSize);

		*(unsigned int*)((char*)m_pParamBuffer + nAllocatedSize) = nDataSize;
		nAllocatedSize += nCurParamSize;
	}
}

// align all members to 16-byte boundary
// it will speed up data access on Intel
// and it is very important on RISK 
// platforms (like Sun SPARC) to avoid non-aligment
void ISACursor::AllocBindBuffer(
	int nPlaceHolderCount,
	saPlaceHolder **ppPlaceHolders,
	unsigned int nIndSize,
	unsigned int nSizeSize,
	unsigned int nAddlSize,
	void **ppAddl)
{
	m_nParamIndSize = nIndSize;
	m_nParamSizeSize = nSizeSize;

	unsigned int nAllocatedSize = 0;

	for(int i = 0; i < nPlaceHolderCount; ++i)
	{
		SAParam &Param = *ppPlaceHolders[i]->getParam();

		unsigned int nCurParamSize = 0;
		nCurParamSize += SA_Align16(sizeof(unsigned int));	// space allocated for data
		nCurParamSize += SA_Align16(nIndSize);	// null indicator
		nCurParamSize += SA_Align16(nSizeSize);	// space for returned size

		unsigned int nDataSize;
		switch(Param.ParamDirType())
		{
		case SA_ParamInput:
			nDataSize = InputBufferSize(Param);
			break;
		case SA_ParamInputOutput:
			nDataSize = sa_max(InputBufferSize(Param), OutputBufferSize(Param.ParamType(), Param.ParamSize()));
			break;
		case SA_ParamOutput:
		case SA_ParamReturn:
			nDataSize = OutputBufferSize(Param.ParamType(), Param.ParamSize());
			break;
		default:
			nDataSize = 0;
			assert(false);
		}
		nCurParamSize += SA_Align16(nDataSize);

		m_pParamBuffer = ::realloc(
			m_pParamBuffer,
			nAllocatedSize + nCurParamSize);

		*(unsigned int*)((char*)m_pParamBuffer + nAllocatedSize) = nDataSize;
		nAllocatedSize += nCurParamSize;
	}

	// allocate additional block as requested by caller
	if(nAddlSize)
		m_pParamBuffer = ::realloc(
			m_pParamBuffer,
			nAllocatedSize + SA_Align16(nAddlSize));
	if(ppAddl)
		*ppAddl = (char*)m_pParamBuffer + nAllocatedSize;
}

/*virtual */
unsigned int ISACursor::OutputBufferSize(
	SADataType_t eDataType,
	unsigned int nDataSize) const
{
	switch(eDataType)
	{
		case SA_dtUnknown:
			throw SAException(SA_Library_Error, -1, -1, IDS_UNKNOWN_DATA_TYPE);
		case SA_dtBool:
			assert(false);	// sould be overloaded
			return 0;
		case SA_dtShort:
			return sizeof(short);
		case SA_dtLong:
			return sizeof(long);
		case SA_dtDouble:
			return sizeof(double);
		case SA_dtNumeric:
			assert(false);	// sould be overloaded
		case SA_dtDateTime:
			assert(false);	// sould be overloaded
			return 0;
		case SA_dtBytes:
			return nDataSize;
		case SA_dtString:
			// No space for '\0' is reserved.
			// nDataSize is always (under Unicode or multi-byte builds)
			// assumed to be in bytes, not characters.
			// If above is not true, client should overload.
			return nDataSize;
		case SA_dtLongBinary:
		case SA_dtLongChar:
		case SA_dtBLob:
		case SA_dtCLob:
			assert(false);	// sould be overloaded
			return 0;
		case SA_dtCursor:
			assert(false);	// sould be overloaded
			return 0;
		default:
			assert(false);	// unknown type
	}

	return 0;
}

// align all members to 16-byte boundary
// it will speed up data access on Intel
// and it is very important on RISK 
// platforms (like Sun SPARC) to avoid non-aligment
void ISACursor::AllocSelectBuffer(
	unsigned int nIndSize,
	unsigned int nSizeSize,
	int nBulkReadingBufSize)
{
	m_nIndSize = nIndSize;
	m_nSizeSize = nSizeSize;
	m_nBulkReadingBufSize = nBulkReadingBufSize;

	unsigned int nAllocatedSize = 0;

	int cFieldCount = m_pCommand->FieldCount();
	int iField;
	for(iField = 1; iField <= cFieldCount; ++iField)
	{
		SAField &Field = m_pCommand->Field(iField);

		unsigned int nCurFieldSize = 0;
		nCurFieldSize += SA_Align16(sizeof(unsigned int));	// space allocated for data
		nCurFieldSize += SA_Align16(nIndSize * nBulkReadingBufSize);	// null indicator
		nCurFieldSize += SA_Align16(nSizeSize * nBulkReadingBufSize);	// space for returned size

		unsigned int nDataSize = OutputBufferSize(
			Field.FieldType(),
			Field.FieldSize());
		nCurFieldSize += SA_Align16(nDataSize * nBulkReadingBufSize);

		m_pSelectBuffer = ::realloc(
			m_pSelectBuffer,
			nAllocatedSize + nCurFieldSize);

		*(unsigned int*)((char*)m_pSelectBuffer + nAllocatedSize) = nDataSize;
		nAllocatedSize += nCurFieldSize;
	}

	void *pBuf = m_pSelectBuffer;
	for(iField = 1; iField <= cFieldCount; ++iField)
	{
		void *pInd;
		void *pSize;
		void *pValue;
		unsigned int nDataBufSize;

		IncFieldBuffer(pBuf, pInd, pSize, nDataBufSize, pValue);

		SetFieldBuffer(
			iField,
			pInd, nIndSize,
			pSize, nSizeSize,
			pValue, nDataBufSize);
	}
}

// default indicator test: -1 is null value
/*virtual */
bool ISACursor::IndicatorIsNull(
	int/* nPos*/,	// 1-based
	SAValueRead &/*vr*/,
	ValueType_t/* eValueType*/,
	void *pInd, unsigned int nIndSize,
	void *pSize, unsigned int nSizeSize,
	unsigned int &nRealSize,
	int nBulkReadingBufPos) const
{
	bool bNull;
	switch(nIndSize)
	{
	case sizeof(char):
		bNull = ((char*)pInd)[nBulkReadingBufPos] == -1;
		break;
	case sizeof(short):
		bNull = ((short*)pInd)[nBulkReadingBufPos] == -1;
		break;
	case sizeof(long):
		bNull = ((long*)pInd)[nBulkReadingBufPos] == -1;
		break;
	default:
		assert(false);	// if none of above then should be overloaded
		bNull = true;
	}

	if(bNull)
		return true;

	switch(nSizeSize)
	{
	case sizeof(unsigned char):
		nRealSize = ((unsigned char*)pSize)[nBulkReadingBufPos];
		break;
	case sizeof(unsigned short):
		nRealSize = ((unsigned short*)pSize)[nBulkReadingBufPos];
		break;
	case sizeof(unsigned long):
		nRealSize = ((unsigned long*)pSize)[nBulkReadingBufPos];
		break;
	default:
		assert(false);	// if none of above then should be overloaded
	}

	return false;
}

void ISACursor::GetFieldBuffer(
	int nPos,	// 1-based
	void *&pValue,
	unsigned int &nFieldBufSize)
{
	if(!m_pSelectBuffer)
	{
		pValue = NULL;
		nFieldBufSize = 0;
		return;
	}

	void *pBuf = m_pSelectBuffer;
	for(int i = 0; i < nPos; ++i)
	{
		void *pInd;
		void *pSize;
		IncFieldBuffer(pBuf, pInd, pSize, nFieldBufSize, pValue);
	}
}

void ISACursor::IncParamBuffer(
	void *&pBuf,
	void *&pInd,
	void *&pSize,
	unsigned int &nDataBufSize,
	void *&pValue)
{
	nDataBufSize = *(unsigned int*)pBuf;
	((char*&)pBuf) += SA_Align16(sizeof(unsigned int));

	pInd = pBuf;
	((char*&)pBuf) += SA_Align16(m_nParamIndSize);

	pSize = pBuf;
	((char*&)pBuf) += SA_Align16(m_nParamSizeSize);

	pValue = pBuf;
	((char*&)pBuf) += SA_Align16(nDataBufSize);
}

void ISACursor::IncFieldBuffer(
	void *&pBuf,
	void *&pInd,
	void *&pSize,
	unsigned int &nDataBufSize,
	void *&pValue)
{
	nDataBufSize = *(unsigned int*)pBuf;
	((char*&)pBuf) += SA_Align16(sizeof(unsigned int));

	pInd = pBuf;
	((char*&)pBuf) += SA_Align16(m_nIndSize * m_nBulkReadingBufSize);

	pSize = pBuf;
	((char*&)pBuf) += SA_Align16(m_nSizeSize * m_nBulkReadingBufSize);

	pValue = pBuf;
	((char*&)pBuf) += SA_Align16(nDataBufSize * m_nBulkReadingBufSize);
}

/*virtual */
bool ISACursor::OutputBindingTypeIsParamType()
{
	return false;
}

void ISACursor::ConvertValue(
	int nPos,	// 1 - based
	unsigned int nIndSize,
	void *pNull,
	unsigned int nSizeSize,
	void *pSize,
	unsigned int nBufSize,
	void *pValue,
	ValueType_t eValueType,
	SAValueRead &vr,
	int nBulkReadingBufPos)
{
	unsigned int nRealSize;
	if(IndicatorIsNull(
		nPos,
		vr,
		eValueType,
		pNull, nIndSize,
		pSize, nSizeSize,
		nRealSize,
		nBulkReadingBufPos))
	{
		*vr.m_pbNull = true;
		return;
	}

	const void *pData = (char*)pValue + nBulkReadingBufPos * nBufSize;

	*vr.m_pbNull = false;

	SADataType_t eDataType;
	switch(eValueType)
	{
	case ISA_FieldValue:
		eDataType = ((SAField&)vr).FieldType();
		break;
	default:
		assert(eValueType == ISA_ParamValue);
		if(isOutputParam((SAParam&)vr) &&
			OutputBindingTypeIsParamType())	// virtual call
		{
			eDataType = ((SAParam&)vr).ParamType();
		}
		else
		{
			// in most cases vr.DataType() == ((SAParam&)vr).ParamType()
			// but this can be coerced
			eDataType = vr.DataType();
		}
	}
	switch(eDataType)
	{
	case SA_dtUnknown:
		throw SAException(SA_Library_Error, -1, -1, IDS_UNKNOWN_DATA_TYPE);
	case SA_dtBool:
		vr.m_eDataType = SA_dtBool;
		switch(nRealSize)
		{
		case sizeof(char):
			*(bool*)vr.m_pScalar = *(char*)pData != 0;
			break;
		case sizeof(short):
			*(bool*)vr.m_pScalar = *(short*)pData != 0;
			break;
		case sizeof(long):
			*(bool*)vr.m_pScalar = *(long*)pData != 0;
			break;
		default:
			assert(false);
			break;
		}
		break;
	case SA_dtShort:
		assert(nRealSize <= sizeof(short));	// <= because we do not have SA_dtChar
		vr.m_eDataType = SA_dtShort;
		*(short*)vr.m_pScalar = *(short*)pData;
		break;
	case SA_dtLong:
		assert(nRealSize == sizeof(long));
		vr.m_eDataType = SA_dtLong;
		*(long*)vr.m_pScalar = *(long*)pData;
		break;
	case SA_dtDouble:
		assert(nRealSize == sizeof(double));
		vr.m_eDataType = SA_dtDouble;
		*(double*)vr.m_pScalar = *(double*)pData;
		break;
	case SA_dtNumeric:
		// size can be variable, e.g. in SQLBase, Oracle, Sybase
		assert(nRealSize <= nBufSize);
		vr.m_eDataType = SA_dtNumeric;
		m_pISAConnection->CnvtInternalToNumeric(
			*(SANumeric*)vr.m_pNumeric,
			pData, nRealSize);
		break;
	case SA_dtDateTime:
		assert(nRealSize <= nBufSize);	// size can be variable, e.g. in SQLBase
		vr.m_eDataType = SA_dtDateTime;
		m_pISAConnection->CnvtInternalToDateTime(
			*vr.m_pDateTime,
			pData, nRealSize);
		break;
	case SA_dtString:
		assert(nRealSize <= nBufSize);
		vr.m_eDataType = SA_dtString;
		ConvertString(*vr.m_pString, pData, nRealSize);
		break;
	case SA_dtBytes:
		assert(nRealSize <= nBufSize);
		vr.m_eDataType = SA_dtBytes;
		*vr.m_pString =
			SAString((const void*)pData, nRealSize);
		break;
	case SA_dtLongBinary:
		vr.m_eDataType = SA_dtLongBinary;
		break;
	case SA_dtLongChar:
		vr.m_eDataType = SA_dtLongChar;
		break;
	case SA_dtBLob:
		vr.m_eDataType = SA_dtBLob;
		break;
	case SA_dtCLob:
		vr.m_eDataType = SA_dtCLob;
		break;
	case SA_dtCursor:
		vr.m_eDataType = SA_dtCursor;
		m_pISAConnection->CnvtInternalToCursor(
			vr.m_pCursor, pData);
		break;
	default:
		assert(false);	// unknown type
	}
}

// default implementation assumes that data for
// string is in multibyte format always
// (in both Unicode and multi-byte builds)
// it also assumes that nRealSize is always in bytes not characters
// Should be overloaded by clients if this is not true
/*virtual */
void ISACursor::ConvertString(SAString &String, const void *pData, unsigned int nRealSize)
{
	String = SAString((const char*)pData, nRealSize);
}

void ISACursor::GetParamBuffer(
	const SAParam &SrcParam,
	void *&pValue, unsigned int &nDataBufSize)
{
	void *pBuf = m_pParamBuffer;
	for(int i = 0; i < m_pCommand->ParamCount(); ++i)
	{
		SAParam &Param = m_pCommand->ParamByIndex(i);

		void *pNull;
		void *pSize;
		IncParamBuffer(pBuf, pNull, pSize, nDataBufSize, pValue);

		if(&SrcParam == &Param)
			break;
	}
}

int ISACursor::OutputParamPos(int nParamPos)
{
	assert(nParamPos <= m_pCommand->ParamCount());
	int nPos = 0;
	for(int i = 0; i < nParamPos; ++i)
	{
		SAParam &Param = m_pCommand->ParamByIndex(i);
		if(Param.ParamDirType() == SA_ParamOutput ||
			Param.ParamDirType() == SA_ParamInputOutput)
			++nPos;
	}

	return nPos;
}

void ISACursor::ConvertOutputParams()
{
	int nOutputs = 0;
	void *pBuf = m_pParamBuffer;
	for(int i = 0; i < m_pCommand->ParamCount(); ++i)
	{
		SAParam &Param = m_pCommand->ParamByIndex(i);

		void *pNull;
		void *pSize;
		unsigned int nDataBufSize;
		void *pValue;
		IncParamBuffer(pBuf, pNull, pSize, nDataBufSize, pValue);

		if(!isOutputParam(Param))
			continue;

		int nPos;
		if(Param.ParamDirType() == SA_ParamReturn)
			nPos = 0;
		else
			nPos = ++nOutputs;

		SADataType_t eParamType = Param.ParamType();
		if(eParamType == SA_dtUnknown)
			throw SAException(SA_Library_Error, -1, -1, IDS_UNKNOWN_PARAMETER_TYPE, (const SAChar*)Param.Name());

		ConvertValue(
			nPos,
			m_nParamIndSize, pNull,
			m_nParamSizeSize, pSize,
			nDataBufSize, pValue,
			ISA_ParamValue,	Param, 0);

		if(!Param.isNull() && isLongOrLob(eParamType))
			ConvertLongOrLOB(ISA_ParamValue, Param, pValue, nDataBufSize);
	}
}

void ISACursor::ConvertSelectBufferToFields(int nBulkReadingBufPos)
{
	int cFieldCount = m_pCommand->FieldCount();
	void *pBuf = m_pSelectBuffer;
	for(int iField = 1; iField <= cFieldCount ; ++iField)
	{
		SAField &Field = m_pCommand->Field(iField);
		SADataType_t eFieldType = Field.FieldType();
		if(eFieldType == SA_dtUnknown)
			throw SAException(SA_Library_Error, -1, -1, IDS_UNKNOWN_COLUMN_TYPE, (const SAChar*)Field.Name());

		void *pInd;
		void *pSize;
		void *pValue;
		unsigned int nDataBufSize;
		IncFieldBuffer(pBuf, pInd, pSize, nDataBufSize, pValue);

		ConvertValue(
			iField,
			m_nIndSize, pInd,
			m_nSizeSize, pSize,
			nDataBufSize, pValue,
			ISA_FieldValue, Field, nBulkReadingBufPos);

		if(!Field.isNull() && isLongOrLob(eFieldType))
			ConvertLongOrLOB(ISA_FieldValue, Field, pValue, nDataBufSize);
	}
}

/*virtual */
void ISACursor::ConvertLongOrLOB(
	ValueType_t eValueType,
	SAValueRead &vr,
	void *pValue,
	unsigned int nBufSize)
{
	SADataType_t eDataType;
	switch(eValueType)
	{
	case ISA_FieldValue:
		eDataType = ((SAField&)vr).FieldType();
		break;
	default:
		assert(eValueType == ISA_ParamValue);
		eDataType = ((SAParam&)vr).ParamType();
	}
	switch(eDataType)
	{
	case SA_dtLongBinary:
	case SA_dtLongChar:
	case SA_dtBLob:
	case SA_dtCLob:
		if(vr.LongOrLobReaderMode() == SA_LongOrLobReaderDefault)
			ReadLongOrLOB(eValueType, vr, pValue, nBufSize,
			NULL, 0, NULL);
		break;
	default:
		assert(false);
	}
}

int ISACursor::FieldCount(int nCount, ...) const
{
	int nFields = 0;

	va_list argList;
	va_start(argList, nCount);
	
	for(int i = 0; i < nCount; i++)
	{
		// int is OK
		// need a cast here since va_arg only
		// takes fully promoted types
		SADataType_t eDataType = (SADataType_t)va_arg(argList, int);
		for(int j = 0; j < m_pCommand->FieldCount(); j++)
			if(m_pCommand->Field(j+1).FieldType() == eDataType)
				++nFields;
	}

	va_end(argList);
	return nFields;
}

short ISACursor::ParamDirCount(
	int nPlaceHolderCount,
	saPlaceHolder **ppPlaceHolders,
	int nCount, ...) const
{
	short nPlaceHolders = 0;

	va_list argList;
	va_start(argList, nCount);

	for(int i = 0; i < nCount; i++)
	{
		// int is OK
		// need a cast here since va_arg only
		// takes fully promoted types
		SAParamDirType_t eType = (SAParamDirType_t)va_arg(argList, int);
		for(int j = 0; j < nPlaceHolderCount; j++)
			if(ppPlaceHolders[j]->getParam()->ParamDirType() == eType)
				++nPlaceHolders;
	}

	va_end(argList);
	return nPlaceHolders;
}

/*static */
bool ISACursor::isLong(SADataType_t eDataType)
{
	switch(eDataType)
	{
	case SA_dtLongBinary:
	case SA_dtLongChar:
		return true;
	default:
		break;
	}

	return false;
}

/*static */
bool ISACursor::isLob(SADataType_t eDataType)
{
	switch(eDataType)
	{
	case SA_dtBLob:
	case SA_dtCLob:
		return true;
	default:
		break;
	}

	return false;
}

/*static */
bool ISACursor::isLongOrLob(SADataType_t eDataType)
{
	return isLong(eDataType) || isLob(eDataType);
}

/*static */
bool ISACursor::isInputParam(const SAParam& Param)
{
	switch(Param.ParamDirType())
	{
	case SA_ParamInput:
	case SA_ParamInputOutput:
		return true;
	case SA_ParamOutput:
	case SA_ParamReturn:
		break;
	default:
		assert(false);
	}

	return false;
}

/*static */
bool ISACursor::isOutputParam(const SAParam& Param)
{
	switch(Param.ParamDirType())
	{
	case SA_ParamInputOutput:
	case SA_ParamOutput:
	case SA_ParamReturn:
		return true;
	case SA_ParamInput:
		break;
	default:
		assert(false);
	}

	return false;
}

int ISACursor::BulkReadingBufSize() const
{
	SAString s = m_pCommand->Option("BulkReadingBufSize");
	if(s.IsEmpty())
		return 0;	// defaults to non bulk reading
	
	return sa_toi(s);
}

void ISACursor::WriteLongOrLobToInternalValue(SAValue &value)
{
	if(value.m_fnWriter != NULL)
	{
		value.m_pString->Empty();

		unsigned int nActualWrite;
		SAPieceType_t ePieceType = SA_FirstPiece;
		void *pBuf;
		while((nActualWrite = value.InvokeWriter(
			ePieceType, 0xffff, pBuf)) != 0)
		{
			// for non-binary (text) data:
			// nActualWrite is in bytes not characters,
			// so binary processing is used always
			//(*value.m_pString) += SAString(pBuf, nActualWrite);
			int nBinaryLen = value.m_pString->GetBinaryLength();
			memcpy((unsigned char*)value.m_pString->GetBinaryBuffer(nBinaryLen + nActualWrite) + nBinaryLen, pBuf, nActualWrite);
			value.m_pString->ReleaseBinaryBuffer(nBinaryLen + nActualWrite);

			if(ePieceType == SA_LastPiece)
				break;
		}
	}
}

//////////////////////////////////////////////////////////////////////
// SADummyConverter Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SADummyConverter::SADummyConverter()
{
	m_nExternalDataSize = 0;
	m_bFinalPiecePending = false;

	m_eCnvtPieceType = SA_OnePiece;	// assumption only
}

//////////////////////////////////////////////////////////////////////
// Helpers
//////////////////////////////////////////////////////////////////////

void SADummyConverter::FlushExternalData(
	unsigned char *
#ifndef NDEBUG
	pData
#endif
	, unsigned int &nDataSize)
{
	assert(!SADummyConverter::IsEmpty());

	assert(pData == m_pExternalData);	// we are just a repeater, we are not expected to copy data into pData
	nDataSize = m_nExternalDataSize;

	// we've given all the data
	m_nExternalDataSize = 0;
}

void SADummyConverter::SetExternalData(unsigned char *pExternalData, unsigned int nExternalDataSize)
{
	m_pExternalData = pExternalData;
	m_nExternalDataSize = nExternalDataSize;
}

//////////////////////////////////////////////////////////////////////
// Overides
//////////////////////////////////////////////////////////////////////

/*virtual */
void SADummyConverter::PutStream(unsigned char *pExternalData, unsigned int nExternalDataSize, SAPieceType_t eExternalPieceType)
{
	// we do not support several PutStream calls one by one (no buffering)
	// if buffering is required, it should be implemented transparently by
	// inherited classes
	assert(SADummyConverter::IsEmpty());

	SetExternalData(pExternalData, nExternalDataSize);
	m_eExternalPieceType = eExternalPieceType;

	// special case
	if((eExternalPieceType == SA_OnePiece || eExternalPieceType == SA_LastPiece))
		m_bFinalPiecePending = true;
}

bool SADummyConverter::StreamIsEnough(
	unsigned int nWantedSize, unsigned int nExternalDataSize) const
{
	assert(nExternalDataSize <= nWantedSize);

	bool bFinalExternalPiece = m_eExternalPieceType == SA_OnePiece || m_eExternalPieceType == SA_LastPiece;
	// check if there isn't enough data
	if(!bFinalExternalPiece && nExternalDataSize < nWantedSize)
		return false;

	return true;
}

/*virtual */
bool SADummyConverter::GetStream(unsigned char *pData, unsigned int nWantedSize, unsigned int &nDataSize, SAPieceType_t &eCnvtPieceType)
{
	// we do not support buffering
	// if buffering is required, it should be implemented transparently
	// by inherited classes
	if(SADummyConverter::IsEmpty())
		return false;

	assert(m_nExternalDataSize <= nWantedSize);

	bool bFinalExternalPiece = m_eExternalPieceType == SA_OnePiece || m_eExternalPieceType == SA_LastPiece;
	// check if there isn't enough data
	if(!bFinalExternalPiece && m_nExternalDataSize < nWantedSize)
		return false;

	// we have enough data to return, let us do it
	FlushExternalData(pData, nDataSize);
	m_bFinalPiecePending = false;

	// virtual call, it shows if inherited class(es) caches some data
	bool bEmptyAfterFlush = IsEmpty();

	// adjust m_eCnvtPieceType
	switch(m_eCnvtPieceType)
	{
	case SA_OnePiece:
		if(!bEmptyAfterFlush || !bFinalExternalPiece)
			m_eCnvtPieceType = SA_FirstPiece;
		break;
	case SA_FirstPiece:
	case SA_NextPiece:
		m_eCnvtPieceType = bFinalExternalPiece? (bEmptyAfterFlush? SA_LastPiece : SA_NextPiece) : SA_NextPiece;
		break;
	default:
		assert(false);
	}
	
	eCnvtPieceType = m_eCnvtPieceType;
	return true;
}

/*virtual */
bool SADummyConverter::IsEmpty() const
{
	return m_nExternalDataSize == 0 && !m_bFinalPiecePending;
}

//////////////////////////////////////////////////////////////////////
// SABufferConverter Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SABufferConverter::SABufferConverter()
{
	m_nBufferSizeAtGetAppendBufferCall = 0;
}

/*virtual */
SABufferConverter::~SABufferConverter()
{
}

//////////////////////////////////////////////////////////////////////
// Helpers
//////////////////////////////////////////////////////////////////////

unsigned char *SABufferConverter::GetAppendBuffer(int nAppendBytesMaxCount)
{
	m_nBufferSizeAtGetAppendBufferCall = m_Buffer.GetBinaryLength();
	void *pBuf = m_Buffer.GetBinaryBuffer(m_nBufferSizeAtGetAppendBufferCall + nAppendBytesMaxCount);
	return (unsigned char*)pBuf + m_nBufferSizeAtGetAppendBufferCall;
}

void SABufferConverter::ReleaseAppendBuffer(int nAppendBytesCount)
{
	m_Buffer.ReleaseBinaryBuffer(m_nBufferSizeAtGetAppendBufferCall + nAppendBytesCount);
}

//////////////////////////////////////////////////////////////////////
// Overides
//////////////////////////////////////////////////////////////////////

/*virtual */
bool SABufferConverter::GetStream(
	unsigned char *pData,
	unsigned int nWantedSize,
	unsigned int &nDataSize,
	SAPieceType_t &eDataPieceType)
{
	// do not simply return false
	// let parent class do this
	// (and maybe some additional processing, for example reporting empty last piece)
	if(SABufferConverter::IsEmpty())
		return SADummyConverter::GetStream(
			pData,
			nWantedSize,
			nDataSize,
			eDataPieceType);

	if(m_Buffer.IsEmpty())
	{
		bool bRes = SADummyConverter::GetStream(pData, nWantedSize, nDataSize, eDataPieceType);
		if(bRes)	// buffer is empty but parent converter has enough data
			return bRes;

		// we need to save data (buffering)
		FlushExternalData(pData, nDataSize);
		void *pBuf = m_Buffer.GetBinaryBuffer(nDataSize);
		memcpy(pBuf, pData, nDataSize);
		m_Buffer.ReleaseBinaryBuffer(nDataSize);
		return false;
	}

	// extend the buffer
	// concatenate old buffer with new data
	int nCurSize = m_Buffer.GetBinaryLength();
	if(SADummyConverter::IsEmpty())
		nDataSize = 0;
	else
		FlushExternalData(pData, nDataSize);
	unsigned char *pBuf = (unsigned char*)m_Buffer.GetBinaryBuffer(nCurSize + nDataSize);
	memcpy(pBuf+nCurSize, pData, nDataSize);

	int nSizeToReturn = sa_min(nCurSize + nDataSize, nWantedSize);
	if(StreamIsEnough(nWantedSize, nSizeToReturn))
	{
		// move some data from buffer to parent converter
		memcpy(pData, pBuf, nSizeToReturn);
		SetExternalData(pData, nSizeToReturn);

		// shrink the buffer
		// use memmove, areas can overlap
		memmove(pBuf, pBuf + nSizeToReturn, nCurSize + nDataSize - nSizeToReturn);
		m_Buffer.ReleaseBinaryBuffer(nCurSize + nDataSize - nSizeToReturn);
		
		// we do not simply return data to caller
		// instead, we let parent class to do that
		// (and maybe some additional processing, for example reporting last piece or eDataPieceType management)
		bool bRes = SADummyConverter::GetStream(
			pData,
			nWantedSize,
			nDataSize,
			eDataPieceType);
		assert(bRes);
		return bRes;
	}

	// !StreamIsEnough(...)
	m_Buffer.ReleaseBinaryBuffer(nCurSize + nDataSize);
	// do not simply return false
	// let parent class do this
	// (and maybe some additional processing, for example reporting empty last piece)
	return SADummyConverter::GetStream(
		pData,
		nWantedSize,
		nDataSize,
		eDataPieceType);
}

/*virtual */
bool SABufferConverter::IsEmpty() const
{
	if(m_Buffer.IsEmpty())
		return SADummyConverter::IsEmpty();

	return false;
}


//////////////////////////////////////////////////////////////////////
// SAUnicode2MultibyteConverter Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SAUnicode2MultibyteConverter::SAUnicode2MultibyteConverter()
{
	m_ReminderBytesCount = 0;
}

/*virtual */
SAUnicode2MultibyteConverter::~SAUnicode2MultibyteConverter()
{
}

//////////////////////////////////////////////////////////////////////
// Overides
//////////////////////////////////////////////////////////////////////

/*virtual */
bool SAUnicode2MultibyteConverter::GetStream(
	unsigned char *pData,
	unsigned int nWantedSize,
	unsigned int &nDataSize,
	SAPieceType_t &eDataPieceType)
{
	// do not simply return false
	// let parent class do this
	// (and maybe some additional processing, for example reporting empty last piece)
	if(SAUnicode2MultibyteConverter::IsEmpty())
		return SABufferConverter::GetStream(
			pData,
			nWantedSize,
			nDataSize,
			eDataPieceType);

	// very simple technique: convert all the data and put it 
	// into the buffer of parent class, then let it deal with it
	if(SADummyConverter::IsEmpty())
		nDataSize = 0;
	else
		FlushExternalData(pData, nDataSize);

	// chek if we have a reminder from previous conversion
	unsigned char *pNewData = pData;
	if(m_ReminderBytesCount)
	{
		assert(m_ReminderBytesCount < sizeof(wchar_t));
		// try to complete one Unicode character
		while(m_ReminderBytesCount < sizeof(wchar_t) && nDataSize > 0)
		{
			m_chReminderBytes[m_ReminderBytesCount] = *pNewData;
			++m_ReminderBytesCount;
			--nDataSize;
			++pNewData;
		}
	}
	assert(m_ReminderBytesCount <= sizeof(wchar_t));
	
	int nNewUnicodeChars = nDataSize/sizeof(wchar_t);

	if(m_ReminderBytesCount == sizeof(wchar_t) || nNewUnicodeChars)
	{
		// assume that each Unicode character can be converted to max MB_CUR_MAX character
		int nNewMultiByteBytesMax = MB_CUR_MAX*(nNewUnicodeChars + (m_ReminderBytesCount? 1 :0));
		void *pMultiByteBuffer = GetAppendBuffer(nNewMultiByteBytesMax);

		int nNewReminderMultiByteBytes = 0;
		if(m_ReminderBytesCount)
		{
			assert(m_ReminderBytesCount == sizeof(wchar_t));
			nNewReminderMultiByteBytes = SAWideCharToMultiByte(
				(char*)pMultiByteBuffer,
				(wchar_t*)m_chReminderBytes, 1);

			// reminder has been converted, flush it
			m_ReminderBytesCount = 0;
		}

		int nNewDataMultiByteBytes = 0;
		if(nNewUnicodeChars)
		{
			nNewDataMultiByteBytes =
				SAWideCharToMultiByte(
				(char*)pMultiByteBuffer + nNewReminderMultiByteBytes,
				(const wchar_t*)pNewData, nNewUnicodeChars);
		}

		assert(nNewReminderMultiByteBytes+nNewDataMultiByteBytes <= nNewMultiByteBytesMax);
		ReleaseAppendBuffer(nNewReminderMultiByteBytes+nNewDataMultiByteBytes);
	}

	// save new reminder bytes if any
	unsigned int NewReminderBytesCount = nDataSize%sizeof(wchar_t);
	if(NewReminderBytesCount)
	{
		assert(m_ReminderBytesCount == 0);
		while(m_ReminderBytesCount < NewReminderBytesCount)
		{
			m_chReminderBytes[m_ReminderBytesCount] = pNewData[nNewUnicodeChars*sizeof(wchar_t)+m_ReminderBytesCount];
			++m_ReminderBytesCount;
		}
	}

	return SABufferConverter::GetStream(
		pData,
		nWantedSize,
		nDataSize,
		eDataPieceType);
}

/*virtual */
bool SAUnicode2MultibyteConverter::IsEmpty() const
{
	if(!m_ReminderBytesCount)
		return SABufferConverter::IsEmpty();

	return false;
}


//////////////////////////////////////////////////////////////////////
// SAMultibyte2UnicodeConverter Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SAMultibyte2UnicodeConverter::SAMultibyte2UnicodeConverter()
{
	m_bFatalError = false;
	m_chReminderBytes = NULL;
	m_ReminderBytesCount = 0;
}

/*virtual */
SAMultibyte2UnicodeConverter::~SAMultibyte2UnicodeConverter()
{
	if(m_chReminderBytes)
		::free(m_chReminderBytes);
}

//////////////////////////////////////////////////////////////////////
// Overides
//////////////////////////////////////////////////////////////////////

/*virtual */
bool SAMultibyte2UnicodeConverter::GetStream(
	unsigned char *pData,
	unsigned int nWantedSize,
	unsigned int &nDataSize,
	SAPieceType_t &eDataPieceType)
{
	// do not simply return false
	// let parent class do this (and maybe some additional processing)
	if(SAMultibyte2UnicodeConverter::IsEmpty())
		return SABufferConverter::GetStream(
			pData,
			nWantedSize,
			nDataSize,
			eDataPieceType);

	// very simple trick: convert all the data and put it
	// into the buffer of parent class, then let it deal with it
	if(SADummyConverter::IsEmpty())
		nDataSize = 0;
	else
		FlushExternalData(pData, nDataSize);

	// chek if we have a reminder from previous conversion
	unsigned char *pNewData = pData;
	bool bConvertedFromReminder = false;
	wchar_t wchConvertedFromReminder = 0;
	if(m_ReminderBytesCount)
	{
		assert(m_ReminderBytesCount < (unsigned int)MB_CUR_MAX);
		// try to complete one Mulibyte character
		while(m_ReminderBytesCount < (unsigned int)MB_CUR_MAX && nDataSize > 0)
		{
			m_chReminderBytes[m_ReminderBytesCount] = *pNewData;
			++m_ReminderBytesCount;
			--nDataSize;
			++pNewData;

			// check if Multibyte character has got valid
			int n = ::mbtowc(&wchConvertedFromReminder, m_chReminderBytes, 2);
			if(n >= 0)
			{
				assert((unsigned int)n == m_ReminderBytesCount);
				bConvertedFromReminder = true;
				break;
			}
		}
	}
	assert(m_ReminderBytesCount <= (unsigned int)MB_CUR_MAX);
	if(m_ReminderBytesCount == (unsigned int)MB_CUR_MAX && !bConvertedFromReminder)
	{
		m_bFatalError = true;
		// reminder could not be converted, flush it
		m_ReminderBytesCount = 0;
	}

	// if we have got fatal error just flush
	// buffered data (already converted and valid) to client if any
	if(m_bFatalError)
		return SABufferConverter::GetStream(pData, nWantedSize, nDataSize, eDataPieceType);
	
	unsigned int nNewMultibyteBytes = nDataSize;
	unsigned int nNewReminderBytesCount = nNewMultibyteBytes;	// worst case
	char *lpchStop = (char*)pNewData;	// worst case

	if(bConvertedFromReminder || nNewMultibyteBytes)
	{
		// in the worst case each byte can represent a Unicode character
		unsigned int nNewUnicodeBytesMax = sizeof(wchar_t)*(nNewMultibyteBytes + (bConvertedFromReminder?1:0));
		void *pUnicodeBuffer = GetAppendBuffer(nNewUnicodeBytesMax);

		if(bConvertedFromReminder)
		{
			assert(m_ReminderBytesCount == sizeof(wchar_t));
			memcpy(pUnicodeBuffer, &wchConvertedFromReminder, sizeof(wchConvertedFromReminder));

			// reminder has been converted, flush it
			m_ReminderBytesCount = 0;
		}

		unsigned int nNewDataUnicodeChars = 0;
		if(nNewMultibyteBytes)
		{
			nNewDataUnicodeChars =
				SAMultiByteToWideChar(
				(wchar_t*)pUnicodeBuffer + (bConvertedFromReminder?1:0),
				(const char*)pNewData, nNewMultibyteBytes, &lpchStop);
			nNewReminderBytesCount = nNewMultibyteBytes - ((char *)lpchStop-(char *)pNewData);
		}

		assert(sizeof(wchar_t) * (nNewDataUnicodeChars + (bConvertedFromReminder?1:0)) <= nNewUnicodeBytesMax);
		ReleaseAppendBuffer(sizeof(wchar_t) * (nNewDataUnicodeChars + (bConvertedFromReminder?1:0)));
	}

	// save new reminder bytes if any
	if(nNewReminderBytesCount)
	{
		assert(m_ReminderBytesCount == 0);
		if(nNewReminderBytesCount < (unsigned int)MB_CUR_MAX)	// not fatal yet
		{
			m_chReminderBytes = (char*)::realloc(m_chReminderBytes, MB_CUR_MAX);
			while(m_ReminderBytesCount < nNewReminderBytesCount)
			{
				m_chReminderBytes[m_ReminderBytesCount] = lpchStop[m_ReminderBytesCount];
				++m_ReminderBytesCount;
			}
		}
		else
		{
			m_bFatalError = true;
		}
	}

	return SABufferConverter::GetStream(
		pData,
		nWantedSize,
		nDataSize,
		eDataPieceType);
}

/*virtual */
bool SAMultibyte2UnicodeConverter::IsEmpty() const
{
	if(!m_ReminderBytesCount)
		return SABufferConverter::IsEmpty();

	return false;
}
