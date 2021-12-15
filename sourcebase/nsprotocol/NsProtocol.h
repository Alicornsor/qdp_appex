// NsProtocol.h: interface for the CNsProtocol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NSPROTOCOL_H__77447CDB_7E7A_4F08_974E_DDD67406C27F__INCLUDED_)
#define AFX_NSPROTOCOL_H__77447CDB_7E7A_4F08_974E_DDD67406C27F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Protocol.h"
#include "NsPackage.h"

class CNsProtocol : public CProtocol  
{
public:
	CNsProtocol(CReactor *pReactor);
	virtual ~CNsProtocol();

};

#endif // !defined(AFX_NSPROTOCOL_H__77447CDB_7E7A_4F08_974E_DDD67406C27F__INCLUDED_)
