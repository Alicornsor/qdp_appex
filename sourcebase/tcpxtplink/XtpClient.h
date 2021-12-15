/////////////////////////////////////////////////////////////////////////
///@system  中国金融期货交易所行情系统-CFFEX
///@company 中国金融期货交易所
///@file CfmmcReportSessdionFactory
///@brief 定义了CRDR之间数据传送协议
///@history 
///20110815 陶进      创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef __XtpClient_H__
#define __XtpClient_H__
#include "public.h"
#include "SessionFactory.h"
#include "SelectReactor.h"
#include "TcpXtpSession.h"
#include "XtpData.h"
#include "Flow.h"
#include "CachedFlow.h"

#define USER_CHANNEL_DISCONNECTED_ALL 0x1199

class CXtpClientCallback
{
public:
	virtual int  GetAPIID()=0;
	virtual void InterLogined(CInterLoginInfoField *pInterLoginInfoField)= 0;
	virtual void OnSessionConnected(CSession *pSession)=0;
	virtual void OnSessionDisconnected(CSession *pSession, int nReason)=0;
	virtual ~CXtpClientCallback(){};
};

class CLockedCacheFlow : public CCachedFlow
{
public:
	CLockedCacheFlow(bool bSyncFlag, int nMaxObjects, int nDataBlockSize)
		:CCachedFlow(bSyncFlag, nMaxObjects, nDataBlockSize)
	{
		m_nCount = CCachedFlow::GetCount();
	}
	
	virtual int GetCount(void)
	{
		return m_nCount;
	}
	
	virtual bool Truncate(int nCount)
	{
		m_lock.Lock();
		bool bRet = CCachedFlow::Truncate(nCount);
		m_nCount = CCachedFlow::GetCount();
		m_lock.UnLock();
		return bRet;
	}
	
	virtual int Append(void *pObject, int length)
	{
		m_lock.Lock();
		int nRet = -1;
		if( m_nMaxObjects<=0 || m_NodeQueue.size()-m_nFirstID<m_nMaxObjects)
		{
			nRet = CCachedFlow::Append(pObject, length);
			m_nCount = CCachedFlow::GetCount();
		}
		m_lock.UnLock();
		return nRet;
	}
	
	virtual int Get(int id, void *pObject, int length)
	{
		m_lock.Lock();
		int nRet = CCachedFlow::Get(id, pObject, length);
		m_nCount = CCachedFlow::GetCount();
		PopFront();
		m_lock.UnLock();
		return nRet;
	}
	
private:
	int m_nCount;
	CMutex m_lock;
};

class CXtpClient:public CSessionFactory,public CTcpXtpSessionCallback
{
public:
	CXtpClient(CSelectReactor *pReactor,CFlow *pSerailFlow,int subcount,CSelectReactor* pConnReactor=NULL);
	~CXtpClient();
	virtual void RegisterReportServer(const char *pszServerAddress);
	virtual void Init();
	virtual  void StartConnect();
	virtual  void StopConnect();
	virtual int HandlePackage(CXTPPackage *pXTPPackage, CTcpXtpSession *pSession);
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);
	int SendReportPackage(CXTPPackage *pXTPPackage);
	void RegClientCallback(CXtpClientCallback *pClientCallback);

	virtual int Append(CXTPPackage *pXTPPackage);
protected:
	virtual CSession *CreateSession(CChannel *pChannel, DWORD dwMark);
	virtual void OnSessionConnected(CSession *pSession);
	virtual void OnSessionDisconnected(CSession *pSession, int nReason);

	CXTPPackage m_XtpPackage;
	char *m_pzLogPath;
	CTcpXtpSession *m_pSession;
	bool m_bConnected;
	CXtpClientCallback *m_pClientCallBack;

	CPipeEventHandler *m_pPipeEventHandler;
	bool  m_bFirstLogined;
private:
	void CreateSendFlow();
	void RemoveSendFlow();
public:
	CFlow *m_pSerialFlow;//接受流
	CFlow *m_pSendFlow;//发送流
	int m_nsubcount;
};
#endif

