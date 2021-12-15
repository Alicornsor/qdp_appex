// FileInitReactor.h: interface for the CFileInitReactor class.
//
/* ----------------------------------------------------------
 * 修改日期：2006.9.29
 * 修改人员：王维 
 * 修改描述：调整日志信息.
 * 备注信息：CFileInitReactor增加m_pMonitorIndexTimer,m_strErrorMsg成员
 * ----------------------------------------------------------
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEINITREACTOR_H__ECBE27C7_3D57_476D_BC46_E05BE3202902__INCLUDED_)
#define AFX_FILEINITREACTOR_H__ECBE27C7_3D57_476D_BC46_E05BE3202902__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SelectReactor.h"
#include "FieldDescribe.h"
#include "customDataType.h"
#include "FibPubApiManager.h"
#include "Flow.h"
#include "DfmtHandler.h"
#include "TcpXtpGateway.h"
#include "TinitServer.h"

class CFileInitReactor : public CSelectReactor,public CXtpClientCallback  
{
public:
	CFileInitReactor(const char *pszWorkDay);

	virtual ~CFileInitReactor();

	virtual void InterLogined(CInterLoginInfoField *pInterLoginInfoField) {}
	virtual void OnSessionConnected(CSession *pSession) {}
	virtual void OnSessionDisconnected(CSession *pSession, int nReason) {}
	virtual int  GetAPIID() { return 0; }

	/**初始化实例
	* @reutrn true 初始化成功  false 初始化失败
	* @remark 初始化通讯接口、流管理器、排队服务等
	*/
	virtual bool InitInstance();

	/**清理实例
	* @remark 清理通讯接口、流管理器、排队服务等
	*/
	virtual void ExitInstance();

	int Redo();

private:
	bool LoadFromCSV(const char *pszCSVPath);
	bool LoadTable(const char *pszCSVFileName,	CFieldDescribe *pFieldDesc, int nTid);
	void FlushPackage(DWORD newtid);
	
private:
	CDateType m_WorkDay; 
	CFlow *m_pTinitFlow;
	CFibPubApiManager *m_pPubApiManager;
	CXTPPackage *m_pPubMessage;
	CDfmtHandler *m_pDfmtHandler;
	CEventHandler *m_pMonitorIndexTimer;
	string m_strErrorMsg;
	bool m_bNeedLoad;
//	CTcpXtpGateway *m_pGateway;
	CXtpExClient *m_pSendClient;
};

#endif // !defined(AFX_FILEINITREACTOR_H__ECBE27C7_3D57_476D_BC46_E05BE3202902__INCLUDED_)
