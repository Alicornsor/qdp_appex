// TinitServer.h: interface for the CTinitServer class.
///@history 
///20121214	徐忠华		创建该文件
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TINITSERVER_H__2D8D681A_1249_435E_B973_6056F7968A53__INCLUDED_)
#define AFX_TINITSERVER_H__2D8D681A_1249_435E_B973_6056F7968A53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FibServerApi.h"
#include "XtpData.h"
#include "TinitDataLoader.h"
#include "HashMap.h"
#include "DbmtHandler.h"
#include "DfmtHandler.h"
#include "FileFlow.h"
#include "FibPubApiManager.h"
#include "XtpClient.h"

class CXtpExClient : public CXtpClient
{
public:
	CXtpExClient(CSelectReactor *pReactor,CFlow *pSerailFlow,int subcount,CSelectReactor* pConnReactor/* =NULL */)
		:CXtpClient(pReactor,pSerailFlow,subcount,pConnReactor)
	{
		
	}
	
	~CXtpExClient() {}
protected:
	virtual CSession *CreateSession(CChannel *pChannel, DWORD dwMark)
	{
		CTcpXtpSession *pSession = new CTcpXtpSession(m_pReactor, pChannel,this);
		pSession->PublishFlow(m_pSerialFlow, 0);
		return pSession;
	}
};

class CTinitServer: public CEventHandler,public CXtpClientCallback
{
public:
	CTinitServer(CReactor *pReactor);
	virtual ~CTinitServer();

	virtual void InterLogined(CInterLoginInfoField *pInterLoginInfoField) {}
	virtual void OnSessionConnected(CSession *pSession) {}
	virtual void OnSessionDisconnected(CSession *pSession, int nReason) {}
	virtual int  GetAPIID() { return 0; }
	
	inline CFlow *GetTinitFlow();
	inline CDbConnection *GetDbConnection();
	bool ConnectDB(char *pszDatabaseName, char *pszUserName, char *pszPassword);
	int Redo();

	/**处理一条事件
	* @param nEventID 事件ID
	* @param dwParam 第一个参数
	* @param pParam 第二个参数
	* @return 处理结果
	*/
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);
	void OnTradingDayInit();
	virtual void OnTimer(int nIDEvent);
private:
	void OnTinitAppendEnd(TTinitInitType nType);
	int	 OnTinitAppendData(CFileFlow *pDataFlow, int nOffset);
	void LoadTradingDay(CTradingDayField &ExchangeTradingDay);
	bool IsBusy();
	void SetError(int nErrorCode, const char *pszErrorMsg);
	void GetSystemID();
private:
	CDbConnection *m_pDbConnection;
	CTradingDayField m_TradingDay;
	CCommPhaseField m_CommPhase;
	CFibPubApiManager *m_pPubApiManager;
	CXTPPackage *m_pPubMessage;
	CTinitDataLoader *m_pDataLoader;
	CFlow *m_pTinitFlow;

	CDbmtHandler *m_pDbmtHandler;
	CDfmtHandler *m_pDfmtHandler;
	bool m_bLoadDataOK;
	//modified by lihh
	CDataSyncStatusType m_DataSyncStatus;
	//CSystemStatusType m_SystemStatus;
	//CTcpXtpGateway *m_pGateway;
	CXtpExClient *m_pSendClient;
	char m_pSystemID[5];
	CSystemInfoField info;
};

inline CFlow *CTinitServer::GetTinitFlow()
{
	return m_pTinitFlow;
}

inline CDbConnection *CTinitServer::GetDbConnection()
{
	return m_pDbConnection;
}

#endif // !defined(AFX_TINITSERVER_H__2D8D681A_1249_435E_B973_6056F7968A53__INCLUDED_)
