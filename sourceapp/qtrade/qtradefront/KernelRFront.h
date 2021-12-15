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
	DWORD nSessionID;					/**<会话号  */
	DWORD nConnectTime;					/**<连接建立时间  */
	int nDialogFlowSeqNo;				/**<对话流当前序号 */
	int nQueryFlowSeqNo;				/**<查询流当前序号 */
	bool bIsLogin;						/**<是否已经登录  */
	CUserIDType UserID;					/**<会话所属用户代码  */
	CBrokerIDType BrokerID;				/**<会话所属会员代码  */
	int nCommFlux;						/**<单位时间的通讯流量 */
	int nMaxCommFlux;					/**<单位时间的通讯流量上限 */
	CUserTypeType UserType;				/**<用户类型 */
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

	/**处理从客户端发出的FTDC请求

	* @param pFTDCPackage 从客户端发出的FTDC请求

	* @param pSession 接收请求的会话

	* @remark 从CFTDCSessionCallback重载

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
	CFlow* m_pReqFlow;//请求报文流

	CFTDCPackage m_rspPackage;

	typedef CHashMap<DWORD, TFtdSessionInfo, HashInt> CSessionInfoMap;
	CSessionInfoMap m_mapSessionInfo;

	int m_nLifeCycleID;
	CFibClientApi *m_ClientApi;
	DWORD m_nQueryServerID;
	CQueryFlowHandler *m_pQueryFlowHandler;

#ifndef WIN32
	struct timeval m_nBeginTime; //原始采样时间
#else
	struct _timeb  m_nBeginTime;
#endif

	int m_nEvokeCpuInterval;
};


class CKernelRFront:public CBaseExchApi,public CSelectReactor
{
public:
	//pTradeResult是前置的输入,pTSeries是前置的输出
	CKernelRFront(CFlow* pSlogResult, CConfig * pConfig, int nLifeCycleID);	
	virtual ~CKernelRFront();
	virtual bool InitInstance();
	void FrontStartWork();
	bool Init();
private:
	CFlow* m_pSlogResult;
	CConfig	*m_pConfig;	//配置文件
	
	CFtdREngine*  m_pFtdREngine;
	DWORD m_dwFrontID;

	CXTPPackage m_rspPackage;
	CFlowReader m_LoginResultReader;
	int m_nLifeCycleID;
	bool m_bShmFlag;

};

#endif
