// FrontTerminalCallback.h: interface for the CFrontTerminalCallback class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRONTTERMINALCALLBACK_H__E6B00A85_B9E7_4D11_9BB7_9A7A29D54D35__INCLUDED_)
#define AFX_FRONTTERMINALCALLBACK_H__E6B00A85_B9E7_4D11_9BB7_9A7A29D54D35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPPackage.h"

const int UM_DISPATCHERMESSAGE  = 0x7777 + SM_USER;
class CFrontTerminalCallback
{
public:
	virtual void HandleMessage(CXTPPackage *pMessage) = 0;

	virtual void OnResponse(CXTPPackage *pPackage) = 0;

	virtual bool DispatcherEvent(int nEventID, DWORD dwParam, void *pParam)=0;
protected:
	virtual ~CFrontTerminalCallback(){};
};

#endif // !defined(AFX_FRONTTERMINALCALLBACK_H__E6B00A85_B9E7_4D11_9BB7_9A7A29D54D35__INCLUDED_)
