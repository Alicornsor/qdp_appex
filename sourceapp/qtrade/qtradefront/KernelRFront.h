#if !defined(KERNEL_RFRONT_H)
#define KERNEL_RFRONT_H

#include "ExCachedFlow.h"
#include "LockFileFlow.h"
#include "FtdEngine.h"
#include "FrontTerminal.h"
#include "FrontForwarder.h"
#include "SelectReactor.h"
#include "CConfig.h"
#include "BaseExchApi.h"
#include "XtpPackageDesc.h"
#include "FTDCRSession.h"

#define  NO_SUBSCRIBE   -99

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TFtdSessionInfo
{
	DWORD nSessionID;					/**<�Ự��  */
	DWORD nConnectTime;					/**<���ӽ���ʱ��  */
	int nDialogFlowSeqNo;				/**<�Ի�����ǰ��� */
	int nQueryFlowSeqNo;				/**<��ѯ����ǰ��� */
	bool bIsLogin;						/**<�Ƿ��Ѿ���¼  */
	CUserIDType UserID;					/**<�Ự�����û�����  */
	CBrokerIDType BrokerID;				/**<�Ự������Ա����  */
	int nCommFlux;						/**<��λʱ���ͨѶ���� */
	int nMaxCommFlux;					/**<��λʱ���ͨѶ�������� */
	CUserTypeType UserType;				/**<�û����� */
};

class CQueryFlowHandler : public CResponseHandler
{
public:
	CQueryFlowHandler() {}
	~CQueryFlowHandler() {}
	
	virtual void OnResponse(CXTPPackage *pPackage);
};

class CFtdREngine : public CSessionFactory, public CFTDCRSessionCallback
{

public:

	CFtdREngine(CReactor *pReactor,char *pQquery,CFlow* pReqFlow,CFlow* pReadSlogResult,
		DWORD nFrontID,int nLifeCycleID,int nEvokeCpuInterval,CSelectReactor* pConnReactor=NULL);
	
	virtual ~CFtdREngine();

	virtual void OnTimer(int nIDEvent);

	/**����ӿͻ��˷�����FTDC����

	* @param pFTDCPackage �ӿͻ��˷�����FTDC����

	* @param pSession ��������ĻỰ

	* @remark ��CFTDCSessionCallback����

	*/
	virtual int HandlePackage(CFTDCPackage *pFTDCPackage, CFTDCRSession *pSession);

	void InputLong(long &LocalTime)
	{
#ifndef  WIN32
		gettimeofday(&m_nBeginTime, NULL);
		LocalTime = m_nBeginTime.tv_sec*1000000+m_nBeginTime.tv_usec;
#else
		_ftime( &m_nBeginTime );
		LocalTime = m_nBeginTime.time*1000+m_nBeginTime.millitm;
#endif	
	}
protected:
	TFtdSessionInfo *GetSessionInfo(DWORD nSessionID);
	bool GetSessionOwner(DWORD nSessionID, CUserIDType &userID, 
		CBrokerIDType &brokerID);		
	void SetSessionOwner(const DWORD nSessionID, const CUserIDType &userID, 
		const CBrokerIDType &brokerID);

	int OnReqUserLogin(CFTDCPackage *pPackage, CFTDCRSession *pSession);
	
	virtual CSession *CreateSession(CChannel *pChannel, DWORD);

	virtual void OnSessionConnected(CSession *pSession);
	
	virtual void OnSessionDisconnected(CSession *pSession, int nReason);

protected:

	void SendError(CFTDCRSession *pSession,const int nErrorCode, const char *pszErrorMsg);

	void SendErrorRsp(CFTDCPackage *pRequest, CFTDCRSession *pSession, 		
		const int nErrorCode, const char *pszErrorMsg);
protected:
	CFlow* m_pReadSlogFlow;
	DWORD m_dwFrontID;
	CXTPPackage m_reqPackage;
	CFlow* m_pReqFlow;//��������

	CFTDCPackage m_rspPackage;

	typedef CHashMap<DWORD, TFtdSessionInfo, HashInt> CSessionInfoMap;
	CSessionInfoMap m_mapSessionInfo;

	int m_nLifeCycleID;
	CFibClientApi *m_ClientApi;
	DWORD m_nQueryServerID;
	CQueryFlowHandler *m_pQueryFlowHandler;

#ifndef WIN32
	struct timeval m_nBeginTime; //ԭʼ����ʱ��
#else
	struct _timeb  m_nBeginTime;
#endif

	int m_nEvokeCpuInterval;
};


class CKernelRFront:public CBaseExchApi,public CSelectReactor
{
public:
	//pTradeResult��ǰ�õ�����,pTSeries��ǰ�õ����
	CKernelRFront(CFlow* pSlogResult, CConfig * pConfig, int nLifeCycleID);	
	virtual ~CKernelRFront();
	virtual bool InitInstance();
	void FrontStartWork();
	bool Init();
private:
	CFlow* m_pSlogResult;
	CConfig	*m_pConfig;	//�����ļ�
	
	CFtdREngine*  m_pFtdREngine;
	DWORD m_dwFrontID;

	CXTPPackage m_rspPackage;
	CFlowReader m_LoginResultReader;
	int m_nLifeCycleID;
	bool m_bShmFlag;

};

#endif
