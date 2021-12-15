// FrontTerminal.h: interface for the CFrontTerminal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRONTTERMINAL_H__7E91868E_4859_42F9_97CA_AA3F70ACF3EC__INCLUDED_)
#define AFX_FRONTTERMINAL_H__7E91868E_4859_42F9_97CA_AA3F70ACF3EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Subscriber.h"
#include "FibClientApi.h"
#include "FrontTerminalCallback.h"
#include "Flow.h"

class CFrontTerminal : public CResponseHandler
{
public:
	CFrontTerminal();
	virtual ~CFrontTerminal();

	void RegisterCallback(CFrontTerminalCallback *pFrontTerminalCallback);

	virtual void OnResponse(CXTPPackage *pPackage);

	void HandleMessage(CXTPPackage *pMessage, bool bRedo=false);
	void DispatcherMessage(CXTPPackage *pMessage);
private:
	vector<CFrontTerminalCallback *> m_frontTerminalCallbacks;
};

#endif // !defined(AFX_FRONTTERMINAL_H__7E91868E_4859_42F9_97CA_AA3F70ACF3EC__INCLUDED_)
