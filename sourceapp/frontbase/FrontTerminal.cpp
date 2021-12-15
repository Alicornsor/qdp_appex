// FrontTerminal.cpp: implementation of the CFrontTerminal class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "FrontTerminal.h"
#include "FlowReader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFrontTerminal::CFrontTerminal()
{
}

CFrontTerminal::~CFrontTerminal()
{

}
void CFrontTerminal::OnResponse(CXTPPackage *pPackage)
{
	for (int i=0; i<m_frontTerminalCallbacks.size(); i++)
	{
		m_frontTerminalCallbacks[i]->OnResponse(pPackage);
	}
}

void CFrontTerminal::RegisterCallback(CFrontTerminalCallback *pFrontTerminalCallback)
{
	m_frontTerminalCallbacks.push_back(pFrontTerminalCallback);
}


void CFrontTerminal::HandleMessage(CXTPPackage *pMessage)
{
	for (int i=0; i<m_frontTerminalCallbacks.size(); i++)
	{
		m_frontTerminalCallbacks[i]->HandleMessage(pMessage);
	}
}

void CFrontTerminal::DispatcherMessage(CXTPPackage *pMessage)
{
	DWORD Frontid=pMessage->GetFrontID();
	//Frontid=0;
	Frontid = Frontid > (m_frontTerminalCallbacks.size()-1) ? 0 :Frontid; 
	m_frontTerminalCallbacks[Frontid]->DispatcherEvent(UM_DISPATCHERMESSAGE,0,pMessage);
}