// MultiServer.h: interface for the CMultiServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MultiSERVER_H__AA737DFB_1BC5_4B35_9EEB_BCC53F1617FC__INCLUDED_)
#define AFX_MultiSERVER_H__AA737DFB_1BC5_4B35_9EEB_BCC53F1617FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Channel.h"
#include "ServiceName.h"
#include "Server.h"

class CMultiServer : public CServerBase 
{
public:
	CMultiServer(CServiceName *pName);
	virtual ~CMultiServer();
	
protected:
	/*接收客户端连接
	* @param  wait	表示需要等待到连接才返回，0表示不等待
	* @return NULL   新Channel未建成功
	* @return 非NULL 新的Channel
	*/
	virtual CChannel *Accept(int wait);

	virtual int GetId(void);
	
	char *GetMatchIP(char *pszMask,char *OutIP);
	
private:
	int m_nID;	/**< 套接字 */
	CServiceName m_ServiceName;
	bool m_bConnected;
	char *m_pNetworkIP;/**< 存放网段地址 */
	char *m_pMultiCastIP;	/**< 存放多播地址*/
	char m_sHostIP[50];
	
};

#endif // !defined(AFX_MultiSERVER_H__AA737DFB_1BC5_4B35_9EEB_BCC53F1617FC__INCLUDED_)
