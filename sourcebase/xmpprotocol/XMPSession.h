// XMPSession.h: interface for the CXMPSession class.
//
// 2007.8.1 hwp 增加对心跳超时设置
// 20090427 hwp NT-0071：增加SetHeartbeatMode方法
//                 如果心跳模式为Slave，则与对方的心跳超时时间一致
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMPSESSION_H__D0B1F13E_7E9B_4AB0_BFF7_F20EC92F71CD__INCLUDED_)
#define AFX_XMPSESSION_H__D0B1F13E_7E9B_4AB0_BFF7_F20EC92F71CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Session.h"
#include "XMPProtocol.h"

class CXMPSession : public CSession  
{
public:
	CXMPSession(CReactor *pReactor,CChannel *pChannel);
	virtual ~CXMPSession();
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);
	void SetHeartbeatTimeout(DWORD dwReadTimeout);
	void SetHeartbeatMode(bool bSlaveMode);
protected:
	CXMPProtocol *m_pXMPProtocol;	/**< 容器内的第二层协议(从下部开始)*/

};

#endif // !defined(AFX_XMPSESSION_H__D0B1F13E_7E9B_4AB0_BFF7_F20EC92F71CD__INCLUDED_)
