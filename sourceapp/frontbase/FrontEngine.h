// FrontEngine.h: interface for the CFrontEngine class.
//
// 20070115	hwp	���Ӷ��������Ƶ��趨
// 20070704	hwp	��˽�����ķַ����Ϊ�����ļ��ͽ�����������
// 20070807	hwp	�������ÿͻ��˽ӿڰ汾��Χ�ķ���
// 20071012 hwp	Ϊ�Ự����UserType��Ϣ�����ṩ�����úͻ�ȡ�ķ���
//                  (Ϊ֧��FTD��ReqSubscribeTopic��
// 20080626 hwp  NT-0041�Ի����Ͳ�ѯ������ʹ��Flow����ֻ������ţ������ڴ�ռ��
// 20080721 hwp  NT-0045-��ϯλ���أ��������޶����SessionInfo�У����ṩ
//                  ���ûỰ�����޶�Ľӿڡ�
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
	DWORD nSessionID;					/**<�Ự��  */
	DWORD nConnectTime;					/**<���ӽ���ʱ��  */
	int nDialogFlowSeqNo;				/**<�Ի�����ǰ��� */
	int nQueryFlowSeqNo;				/**<��ѯ����ǰ��� */
	bool bIsLogin;						/**<�Ƿ��Ѿ���¼  */
	CUserIDType UserID;					/**<�Ự�����û�����  */
	CBrokerIDType BrokerID;	/**<�Ự������Ա����  */
	int nCommFlux;						/**<��λʱ���ͨѶ���� */
	int nMaxCommFlux;					/**<��λʱ���ͨѶ�������� */
	CUserTypeType UserType;				/**<�û����� */
};

class CFrontEngine : public CSessionFactory, public CFrontTerminalCallback 
{
public:
	CFrontEngine(CReactor *pReactor, CFrontForwarder *pFrontForwarder, 
		const char *pszFlowPath,CSelectReactor* pConnReactor=NULL);
	virtual ~CFrontEngine();
	
	/**����ʱ��������CReactor����
	* @param nIDEvent ������Ϊ��ʱ��ʱ���ڶ�ʱ������ʱ����ʶ   
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

	/**������׷�ӵ�˽����
	*@param pPackage Ҫ׷�ӵı���
	*@return ׷�ӵı�����˽�����е����
	*/
	int AppendToPrivateFlow(CPackage *pPackage);

	/**���Ѽ���˽�����ı������±���ʽ�����Ա����
	*@param brokerID ��Ա����
	*@param nIndex ������˽�����е����
	*/
	void SendToPrivateFlow(const CBrokerIDType &brokerID, int nIndex);

	void CheckSession(CSession *pSession, TFrontSessionInfo *pSessionInfo);
	void CalcFlux(CSession *pSession, const int nFlux);

	/**��Channel��־�ļ�
	*@param pszPath ��־�ļ�·��
	*@return true �ɹ�
	*@return false ʧ��
	*/
	bool OpenChannelLogFile(const char *pszPath);

	/**�ر�Channel��־�ļ�
	*/
	void CloseChannelLogFile();


	//20130827 huwp �޸�дslog��������		
	/**������־��ָ��, ����¼Channnel��Ϣ
	*@param fp ��־�ļ�ָ��, NULL��ʾ������־
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

	string m_strInterfaceMin;		/**<�����¼�Ľӿ���С�汾*/
	string m_strInterfaceMax;		/**<�����¼�Ľӿ����汾*/
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
