/////////////////////////////////////////////////////////////////////////
///@system  �й������ڻ�����������ϵͳ-CFFEX
///@company �й������ڻ�������
///@file CfmmcReportSessdionFactory
///@brief ������CRDR֮�����ݴ���Э��
///@history 
///20110815 �ս�      �������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef __TcpXtpSessionFactory_H__
#define __TcpXtpSessionFactory_H__
#include "public.h"
#include "SessionFactory.h"
#include "SelectReactor.h"
#include "TcpXtpSession.h"
#include "XtpData.h"
#include "Flow.h"

#define USER_CHANNEL_DISCONNECTED_ALL 0x1199

class CTcpXtpSessionFactory:public CSessionFactory,public CTcpXtpSessionCallback
{
public:
	CTcpXtpSessionFactory(CFlow *pSubFlow,CSelectReactor *pReactor,int subcount,CSelectReactor* pConnReactor=NULL);
	~CTcpXtpSessionFactory();
	virtual void RegisterReportServer(const char *pszServerAddress);
	virtual void Init();
	virtual  void StartConnect();
	virtual  void StopConnect();
	virtual int HandlePackage(CXTPPackage *pXTPPackage, CTcpXtpSession *pSession);
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);
protected:
	virtual CSession *CreateSession(CChannel *pChannel, DWORD dwMark);
	virtual void OnSessionConnected(CSession *pSession);
	virtual void OnSessionDisconnected(CSession *pSession, int nReason);
	virtual void InterLogin(CTcpXtpSession *pSession);

	CXTPPackage m_LoginPackage;
	CFlow  *m_pSubFlow;
	char *m_pzLogPath;
	int m_nsubcount;
};
#endif

