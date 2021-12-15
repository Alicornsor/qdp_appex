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
	/*���տͻ�������
	* @param  wait	��ʾ��Ҫ�ȴ������Ӳŷ��أ�0��ʾ���ȴ�
	* @return NULL   ��Channelδ���ɹ�
	* @return ��NULL �µ�Channel
	*/
	virtual CChannel *Accept(int wait);

	virtual int GetId(void);
	
	char *GetMatchIP(char *pszMask,char *OutIP);
	
private:
	int m_nID;	/**< �׽��� */
	CServiceName m_ServiceName;
	bool m_bConnected;
	char *m_pNetworkIP;/**< ������ε�ַ */
	char *m_pMultiCastIP;	/**< ��Ŷಥ��ַ*/
	char m_sHostIP[50];
	
};

#endif // !defined(AFX_MultiSERVER_H__AA737DFB_1BC5_4B35_9EEB_BCC53F1617FC__INCLUDED_)
