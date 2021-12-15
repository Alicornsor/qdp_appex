// NsPackage.h: interface for the CNsPackage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NSPACKAGE_H__57EF2472_C4E1_4C2D_BDBB_2381A4FE1B25__INCLUDED_)
#define AFX_NSPACKAGE_H__57EF2472_C4E1_4C2D_BDBB_2381A4FE1B25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Package.h"

const int NS_PACKAGE_MAX_SIZE = 1024;
const int NSHLEN = 0;

class CNsPackage : public CPackage  
{
public:
	CNsPackage();
	virtual ~CNsPackage();

	virtual DWORD GetActiveID();
	
	virtual int ValidPackage();
	
	virtual int MakePackage();

};

#endif // !defined(AFX_NSPACKAGE_H__57EF2472_C4E1_4C2D_BDBB_2381A4FE1B25__INCLUDED_)
