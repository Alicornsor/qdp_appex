
#ifndef _SQLAPI_IMPORT_INCLUDE_
#define _SQLAPI_IMPORT_INCLUDE_

/*----------------------------------------------*/
//	SQLAPI++ ͷ�ļ������ļ�����
/*----------------------------------------------*/

#ifdef _UNICODE
#define SA_UNICODE
#endif // _UNICODE

#include "SQLAPI.h"

// ʹ�þ�̬�� �궨��
#define SQLAPI_STATIC_BUILD

#ifdef _UNICODE
#if !defined(SQLAPI_STATIC_BUILD) && !defined(_DEBUG)
#pragma comment(lib, "sqlapiu.lib")
#pragma message("���ӿ�: lsqlapiu.lib")

#elif !defined(SQLAPI_STATIC_BUILD) && defined(_DEBUG)
#pragma comment(lib, "sqlapiud.lib")
#pragma message("���ӿ�: sqlapiud.lib")

#elif defined(SQLAPI_STATIC_BUILD) && !defined(_DEBUG)
#pragma comment(lib, "sqlapius.lib")
#pragma message("���ӿ�: sqlapius.lib")

#elif defined(SQLAPI_STATIC_BUILD) && defined(_DEBUG)
#pragma comment(lib, "sqlapiusd.lib")
#pragma message("���ӿ�: sqlapiusd.lib")
#else
#error "SQLAPI 4.1.3 UNICODE ���ÿ��ļ�ʧ�ܡ���"
#endif

#else

#if !defined(SQLAPI_STATIC_BUILD) && !defined(_DEBUG)
#pragma comment(lib, "sqlapi.lib")
#pragma message("���ӿ�: lsqlapi.lib")

#elif !defined(SQLAPI_STATIC_BUILD) && defined(_DEBUG)
#pragma comment(lib, "sqlapid.lib")
#pragma message("���ӿ�: sqlapid.lib")

#elif defined(SQLAPI_STATIC_BUILD) && !defined(_DEBUG)
#pragma comment(lib, "sqlapis.lib")
#pragma message("���ӿ�: sqlapis.lib")

#elif defined(SQLAPI_STATIC_BUILD) && defined(_DEBUG)
#pragma comment(lib, "sqlapisd.lib")
#pragma message("���ӿ�: sqlapisd.lib")
#else
#error "SQLAPI 4.1.3 ���ÿ��ļ�ʧ�ܡ���"
#endif

#endif // _UNICODE


#if defined(SQLAPI_STATIC_BUILD)
#pragma comment(lib, "user32.lib")
#pragma message("SQLAPI��̬����: user32.lib")
#pragma comment(lib, "version.lib")
#pragma message("SQLAPI��̬����: version.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma message("SQLAPI��̬����: oleaut32.lib")
#pragma comment(lib, "ole32.lib")
#pragma message("SQLAPI��̬����: ole32.lib")
#endif



#endif //_SQLAPI_IMPORT_INCLUDE_