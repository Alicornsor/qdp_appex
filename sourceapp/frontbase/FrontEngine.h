// FrontEngine.h: interface for the CFrontEngine class.
//
// 20070115	hwp	增加对流量控制的设定
// 20070704	hwp	将私有流的分发拆分为进入文件和进入索引两步
// 20070807	hwp	增加设置客户端接口版本范围的方法
// 20071012 hwp	为会话增加UserType信息，并提供了设置和获取的方法
//                  (为支持FTD的ReqSubscribeTopic）
// 20080626 hwp  NT-0041对话流和查询流不再使用Flow对象，只管理序号，减少内存占用
// 20080721 hwp  NT-0045-分席位流控：将流控限额放入SessionInfo中，并提供
//                  设置会话流量限额的接口。
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRONTENGINE_H__A824EA31_6C48_4301_9BE8_894EC1D1B69E__INCLUDED_)
#define AFX_FRONTENGINE_H__A824EA31_6C48_4301_9BE8_894EC1D1B69E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTPPackage.h"
#include "HashMap.h"
#include "Flow.h"
#include "customDataType.h"
#include "SessionFactory.h"
#include "IndexPackageFlow.h"
#include "FrontForwarder.h"
#include "FrontTerminalCallback.h"

struct TFrontSessionInfo
{
	DWORD nSessionID;					/**<会话号  */
	DWORD nConnectTime;					/**<连接建立时间  */
	int nDialogFlowSeqNo;				/**<对话流当前序号 */
	int nQueryFlowSeqNo;				/**<查询流当前序号 */
	bool bIsLogin;						/**<是否已经登录  */
	CUserIDType UserID;					/**<会话所属用户代码  */
	CBrokerIDType BrokerID;	/**<会话所属会员代码  */
	int nCommFlux;						/**<单位时间的通讯流量 */
	int nMaxCommFlux;					/**<单位时间的通讯流量上限 */
	CUserTypeType UserType;				/**<用户类型 */
};

class CFrontEngine : public CSessionFactory, public CFrontTerminalCallback 
{
public:
	CFrontEngine(CReactor *pReactor, CFrontForwarder *pFrontForwarder, 
		const char *pszFlowPath,CSelectReactor* pConnReactor=NULL);
	virtual ~CFrontEngine();
	
	/**处理定时操作，由CReactor调用
	* @param nIDEvent 当自身为定时器时，在定时器链表定时器标识   
	*/
	virtual void OnTimer(int nIDEvent);
	
	inline void SetMaxCommFlux(int nMaxCommFlux);

	void SetInterfaceMinStr(const char *pszInterfaceMinStr);
	void SetInterfaceMaxStr(const char *pszInterfaceMaxStr);
	
protected:
	virtual void OnSessionConnected(CSession *pSession);
	virtual void OnSessionDisconnected(CSession *pSession, int nReason);

protected:
	TFrontSessionInfo *GetSessionInfo(DWORD nSessionID);
	bool GetSessionOwner(DWORD nSessionID, CUserIDType &userID, 
		CBrokerIDType &brokerID);		
	void SetSessionOwner(const DWORD nSessionID, const CUserIDType &userID, 
		const CBrokerIDType &brokerID);
	void ClearSessionOwner(const DWORD nSessionID);
	bool IsSessionLogin(DWORD nSessionID);
	bool SetSessionOwnerType(DWORD nSessionID, const CUserTypeType &UserType);
	bool SetSessionMaxCommFlux(DWORD nSessionID, int nMaxCommFlux);
	CUserTypeType GetSessionOwnerType(DWORD nSessionID);
	void ClearAllMap();
	CIndexPackageFlow *GetPrivateFlow(const CBrokerIDType &brokerID);
	void SendToPrivateFlow(const CBrokerIDType &brokerID, CPackage *pPackage);
	inline CFlow *GetPublicFlow();
	void SendToPublicFlow(CPackage *pPackage);

	/**将报文追加到私有流
	*@param pPackage 要追加的报文
	*@return 追加的报文在私有流中的序号
	*/
	int AppendToPrivateFlow(CPackage *pPackage);

	/**将已加入私有流的报文以下标形式加入会员流中
	*@param brokerID 会员代码
	*@param nIndex 报文在私有流中的序号
	*/
	void SendToPrivateFlow(const CBrokerIDType &brokerID, int nIndex);

	void CheckSession(CSession *pSession, TFrontSessionInfo *pSessionInfo);
	void CalcFlux(CSession *pSession, const int nFlux);

	/**打开Channel日志文件
	*@param pszPath 日志文件路径
	*@return true 成功
	*@return false 失败
	*/
	bool OpenChannelLogFile(const char *pszPath);

	/**关闭Channel日志文件
	*/
	void CloseChannelLogFile();


	//20130827 huwp 修改写slog慢的问题		
	/**设置日志流指针, 并记录Channnel信息
	*@param fp 日志文件指针, NULL表示不记日志
	*@remark
	*/
	void SetLogFlow(CFlow *fp);
protected:
	CFrontForwarder *m_pFrontForwarder;

	CFlow *m_pPrivateFlow;
	
	typedef CHashMap<CBrokerIDType, CIndexPackageFlow *, HashString> CParticipantFlowMap;
	CParticipantFlowMap m_mapPrivateFlow;

	CFlow *m_pPublicFlow;

	CXTPPackage m_reqPackage;
	
	typedef CHashMap<DWORD, TFrontSessionInfo, HashInt> CSessionInfoMap;
	CSessionInfoMap m_mapSessionInfo;

	FILE *m_fpChannelLog;
	CFlow* m_pSlogFlow;

	string m_strFlowPathName;

	int m_nMaxCommFlux;

	string m_strInterfaceMin;		/**<允许登录的接口最小版本*/
	string m_strInterfaceMax;		/**<允许登录的接口最大版本*/
};

inline CFlow *CFrontEngine::GetPublicFlow()
{
	return m_pPublicFlow;
}

inline void CFrontEngine::SetMaxCommFlux(int nMaxCommFlux)
{
	m_nMaxCommFlux = nMaxCommFlux;
}
	
#endif // !defined(AFX_FRONTENGINE_H__A824EA31_6C48_4301_9BE8_894EC1D1B69E__INCLUDED_)
