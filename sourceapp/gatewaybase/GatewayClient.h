/////////////////////////////////////////////////////////////////////////
///@system  中国金融期货交易所行情系统-CFFEX
///@company 中国金融期货交易所
///@file CfmmcReportSessdionFactory
///@brief 定义了CRDR之间数据传送协议
///@history 
///20110815 陶进      创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef __CGateWayClient_H__
#define __CGateWayClient_H__
#include "public.h"
#include "SessionFactory.h"
#include "SelectReactor.h"
#include "TcpXtpSession.h"
#include "XtpData.h"
#include "Flow.h"

#define USER_CHANNEL_DISCONNECTED_ALL 0x1199

class CGateWayClient:public CSessionFactory,public CTcpXtpSessionCallback
{
public:
	CGateWayClient(CFlow *pSubFlow,CSelectReactor *pReactor,DWORD nFrontID,int subcount=0);
	~CGateWayClient();
	virtual void RegisterReportServer(const char *pszServerAddress);
	virtual void Init();
	virtual  void StartConnect();
	virtual  void StopConnect();
	virtual int HandlePackage(CXTPPackage *pXTPPackage, CTcpXtpSession *pSession);
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);
	int SendReportPackage(CXTPPackage *pXTPPackage);
	
protected:
	virtual CSession *CreateSession(CChannel *pChannel, DWORD dwMark);
	virtual void OnSessionConnected(CSession *pSession);
	virtual void OnSessionDisconnected(CSession *pSession, int nReason);
	virtual void InnerLogin();

	CXTPPackage m_Package;
	CFlow  *m_pSubFlow;
	char *m_pzLogPath;
	int m_nsubcount;
	//客户端的Session,用于发送报文
	CTcpXtpSession *m_pSession;
	//是否已经和服务端连接上
	bool m_bConnected;
	DWORD m_nFrontID;
};
#endif

