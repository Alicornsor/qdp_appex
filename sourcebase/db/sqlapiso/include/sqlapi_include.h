
#ifndef _SQLAPI_IMPORT_INCLUDE_
#define _SQLAPI_IMPORT_INCLUDE_

/*----------------------------------------------*/
//	SQLAPI++ 头文件及库文件引用
/*----------------------------------------------*/

#ifdef _UNICODE
#define SA_UNICODE
#endif // _UNICODE

#include "SQLAPI.h"

// 使用静态库 宏定义
#define SQLAPI_STATIC_BUILD

#ifdef _UNICODE
#if !defined(SQLAPI_STATIC_BUILD) && !defined(_DEBUG)
#pragma comment(lib, "sqlapiu.lib")
#pragma message("链接库: lsqlapiu.lib")

#elif !defined(SQLAPI_STATIC_BUILD) && defined(_DEBUG)
#pragma comment(lib, "sqlapiud.lib")
#pragma message("链接库: sqlapiud.lib")

#elif defined(SQLAPI_STATIC_BUILD) && !defined(_DEBUG)
#pragma comment(lib, "sqlapius.lib")
#pragma message("链接库: sqlapius.lib")

#elif defined(SQLAPI_STATIC_BUILD) && defined(_DEBUG)
#pragma comment(lib, "sqlapiusd.lib")
#pragma message("链接库: sqlapiusd.lib")
#else
#error "SQLAPI 4.1.3 UNICODE 引用库文件失败……"
#endif

#else

#if !defined(SQLAPI_STATIC_BUILD) && !defined(_DEBUG)
#pragma comment(lib, "sqlapi.lib")
#pragma message("链接库: lsqlapi.lib")

#elif !defined(SQLAPI_STATIC_BUILD) && defined(_DEBUG)
#pragma comment(lib, "sqlapid.lib")
#pragma message("链接库: sqlapid.lib")

#elif defined(SQLAPI_STATIC_BUILD) && !defined(_DEBUG)
#pragma comment(lib, "sqlapis.lib")
#pragma message("链接库: sqlapis.lib")

#elif defined(SQLAPI_STATIC_BUILD) && defined(_DEBUG)
#pragma comment(lib, "sqlapisd.lib")
#pragma message("链接库: sqlapisd.lib")
#else
#error "SQLAPI 4.1.3 引用库文件失败……"
#endif

#endif // _UNICODE


#if defined(SQLAPI_STATIC_BUILD)
#pragma comment(lib, "user32.lib")
#pragma message("SQLAPI静态链接: user32.lib")
#pragma comment(lib, "version.lib")
#pragma message("SQLAPI静态链接: version.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma message("SQLAPI静态链接: oleaut32.lib")
#pragma comment(lib, "ole32.lib")
#pragma message("SQLAPI静态链接: ole32.lib")
#endif



#endif //_SQLAPI_IMPORT_INCLUDE_