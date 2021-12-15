#ifndef __SQLITE3_UTIL_H
#define __SQLITE3_UTIL_H
#include <sqlite3.h>
#ifdef __cplusplus
extern "C" {
#endif

int findIdx(sqlite3_stmt* stat, const char* fieldName);
const char* findName(sqlite3_stmt* stat, int nCol);
const char* findCType(sqlite3_stmt* stat, int nCol);
int findType(sqlite3_stmt* stat, int nCol);
int bindParameterIndex(sqlite3_stmt* stat, const char* szParam);
int bindStrByName(sqlite3_stmt* stat, const char* szParam, const char* szValue);
int bindStrByIdx(sqlite3_stmt* stat, int nParam, const char* szValue);
int bindIntByName(sqlite3_stmt* stat, const char* szParam, const int nValue);
int bindIntByIdx(sqlite3_stmt* stat, int nParam, const int nValue);
int bindDoubleByName(sqlite3_stmt* stat, const char* szParam, const double dwValue);
int bindDoubleByIdx(sqlite3_stmt* stat, int nParam, const double dValue);
int bindBlobByName(sqlite3_stmt* stat, const char* szParam, const void* blobValue, int nLen);
int bindBlobByIdx(sqlite3_stmt* stat, int nParam, const void* blobValue, int nLen);
int bindNullByName(sqlite3_stmt* stat, const char* szParam);
int bindNullByIdx(sqlite3_stmt* stat, int nParam);
#ifdef __cplusplus
}  /* end of the 'extern "C"' block */
#endif

#endif