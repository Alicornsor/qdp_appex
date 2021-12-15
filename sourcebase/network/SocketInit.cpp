// SocketInit.cpp: implementation of the CSocketInit class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "SocketInit.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSocketInit::CSocketInit()
{
#ifdef WIN32
	WSADATA initData;
	initData.wVersion=0;
	initData.wHighVersion=2;
	strcpy(initData.szDescription,"");
	strcpy(initData.szSystemStatus,"");
	initData.iMaxSockets=100;
	initData.lpVendorInfo=0;
	initData.lpVendorInfo="";
	WSAStartup(2,&initData);
	if (WSAStartup(2,&initData)!=0)
		RAISE_RUNTIME_ERROR("Can not init socket");
#endif

}

CSocketInit::~CSocketInit()
{

}
