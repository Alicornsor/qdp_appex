#include "sqlite3util.h"
#include <stdio.h>
#include <string.h>
//////////////////////////////////////////////////////////////////////////
int findIdx(sqlite3_stmt* stat, int nCols, const char* fieldName)
{
	if (fieldName)
	{
		for (int nField = 0; nField < nCols; nField++)
		{
			const char* szTemp = sqlite3_column_name(stat, nField);

			if (strcmp(fieldName, szTemp) == 0)
			{
				return nField;
			}
		}
	}
	return -1;
}

const char* findName(sqlite3_stmt* stat, int nCol)
{
	return sqlite3_column_name(stat, nCol);
}
const char* findCType(sqlite3_stmt* stat, int nCol)
{
	return sqlite3_column_decltype(stat, nCol);
}
int findType(sqlite3_stmt* stat, int nCol)
{
	return sqlite3_column_type(stat, nCol);
}
//////////////////////////////////////////////////////////////////////////
int bindParameterIndex(sqlite3_stmt* stat, const char* szParam)
{
	int nParam = sqlite3_bind_parameter_index(stat, szParam);
	return nParam;
}

int bindStrByName(sqlite3_stmt* stat, const char* szParam, const char* szValue)
{
	int nParam = bindParameterIndex(stat, szParam);
	return bindStrByIdx(stat, nParam, szValue);
}

int bindStrByIdx(sqlite3_stmt* stat, int nParam, const char* szValue)
{
	int nRes = sqlite3_bind_text(stat, nParam, szValue, -1, SQLITE_TRANSIENT);

	return nRes;
}

int bindIntByName(sqlite3_stmt* stat, const char* szParam, const int nValue)
{
	int nParam = bindParameterIndex(stat, szParam);
	return bindIntByIdx(stat, nParam, nValue);
}

int bindIntByIdx(sqlite3_stmt* stat, int nParam, const int nValue)
{
	int nRes = sqlite3_bind_int(stat, nParam, nValue);

	return nRes;
}

int bindDoubleByName(sqlite3_stmt* stat, const char* szParam, const double dwValue)
{
	int nParam = bindParameterIndex(stat, szParam);
	return bindDoubleByIdx(stat, nParam, dwValue);
}
int bindDoubleByIdx(sqlite3_stmt* stat, int nParam, const double dValue)
{
	int nRes = sqlite3_bind_double(stat, nParam, dValue);

	return nRes;
}

int bindBlobByName(sqlite3_stmt* stat, const char* szParam, const void* blobValue, int nLen)
{
	int nParam = bindParameterIndex(stat, szParam);
	return bindBlobByIdx(stat, nParam, blobValue, nLen);
}
int bindBlobByIdx(sqlite3_stmt* stat, int nParam, const void* blobValue, int nLen)
{
	int nRes = sqlite3_bind_blob(stat, nParam,
								blobValue, nLen, SQLITE_TRANSIENT);

	return nRes;
}
int bindNullByName(sqlite3_stmt* stat, const char* szParam)
{
	int nParam = bindParameterIndex(stat, szParam);
	return bindNullByIdx(stat, nParam);
}
int bindNullByIdx(sqlite3_stmt* stat, int nParam)
{
	int nRes = sqlite3_bind_null(stat, nParam);
	
	return nRes;
}