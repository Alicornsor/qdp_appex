/////////////////////////////////////////////////////////////////////////
///@system  �й������ڻ�����������ϵͳ-CFFEX
///@company �й������ڻ�������
///@file CfmmcReportSessdionFactory
///@brief ������CRDR֮�����ݴ���Э��
///@history 
///20110815 �ս�      �������ļ�
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
	//�ͻ��˵�Session,���ڷ��ͱ���
	CTcpXtpSession *m_pSession;
	//�Ƿ��Ѿ��ͷ����������
	bool m_bConnected;
	DWORD m_nFrontID;
};
#endif

