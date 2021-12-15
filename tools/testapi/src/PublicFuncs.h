// PublicFuncs.h: interface for the PublicFuncs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUBLICFUNCS_H__F565A242_2630_4908_B2B8_011FDAA45C89__INCLUDED_)
#define AFX_PUBLICFUNCS_H__F565A242_2630_4908_B2B8_011FDAA45C89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "platform.h"
#include "FtdcUserApiImpl.h"
#include "SelectReactor.h"
#include "CConfig.h"
#include "QdpFtdcUserApiStruct.h"
#include "QdpFtdcUserApi.h"
#include "CFilelogService.h"

const int BUFLEN=512;

class PublicFuncs  
{
public:
	PublicFuncs();
	virtual ~PublicFuncs();
};

extern TQdpFtdcUserIDType	g_UserID;
extern TQdpFtdcBrokerIDType	g_BrokerID;
extern TQdpFtdcPasswordType	g_Password;
extern char g_frontaddr[BUFLEN];
extern char g_pFlowPath[BUFLEN];
extern int g_nOrdLocalID;
extern char* g_pProductInfo;
extern CQdpFtdcUserApi * g_puserapi;
extern bool StartAutoOrder();
#ifdef WIN32
	extern map<DWORD,_timeb*>* g_mpOrdSndTm;
#else
	extern map<DWORD,timeval*>* g_mpOrdSndTm;
#endif
extern map<DWORD,int>* g_mpOrdLoopTm;
extern CMutex g_mux;
extern FILE* g_fpRspTm;

extern bool readconfig();

#endif // !defined(AFX_PUBLICFUNCS_H__F565A242_2630_4908_B2B8_011FDAA45C89__INCLUDED_)
