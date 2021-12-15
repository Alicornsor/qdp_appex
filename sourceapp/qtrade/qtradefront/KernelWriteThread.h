#if !defined(KERNEL_WRITE_THREAD_H)
#define KERNEL_WRITE_THREAD_H

#include "ExCachedFlow.h"
#include "EventDispatcher.h"
#include "FTDCSession.h"
#include "customDataType.h"
#include "XTPPackage.h"
#include "IndexPackageFlow.h"
#include "FtdPackageDesc.h"
#include "UFEntityCopy.h"
#include "KernelRFront.h"

struct TSessionInfo
{
	CFTDCRSession *pSession;
	int nDialogFlowSeqNo;				/**<�Ի�����ǰ��� */
	int nQueryFlowSeqNo;
	CUserIDType UserID;					/**<�Ự�����û�����  */
	CBrokerIDType BrokerID;				/**<�Ự������Ա����  */
	CUserTypeType UserType;				/**<�û����� */
	bool    Disconected;			    //�����Ƿ�Ҫ�Ͽ�,Ϊtrue
	bool    WriteError;
	bool    Logined;
	int     nReason;
};


class CKernelWriteThread : public CReactor, public CSessionCallback
{
public:
	//pTradeResult��ǰ�õ�����,pTSeries��ǰ�õ����
	CKernelWriteThread(CFlow* pTradeResult,CFlow* pSlogResult,DWORD FrontID,int nLifeCycleID,bool bBindThreadsToCPU=false);	

	virtual ~CKernelWriteThread();

	void SetNoShmChannelFlag(bool bFlag);

	void HandleMessage(CXTPPackage *pMessage);

	bool InitInstance();

	TSessionInfo* GetSessionInfo(DWORD nSessionID);

	virtual void OnSessionConnected(CSession *pSession) { NULL; }
	virtual void OnSessionDisconnected(CSession *pSession, int nReason);
	virtual void OnSessionWarning(CSession *pSession, int nReason, int nParam) { NULL; }

	void InputLocalTime(CILocalTimeType &LocalTime)
	{
#ifndef  WIN32
		gettimeofday(&m_nBeginTime, NULL);
		LocalTime = m_nBeginTime.tv_sec*1000000+m_nBeginTime.tv_usec;
#else
		_ftime( &m_nBeginTime );
		LocalTime = m_nBeginTime.time*1000+m_nBeginTime.millitm;
#endif	
	}
	void PrintDelayLog(CInputOrderField &field);
	void DumpDelayLog();

	void SetRedoFlowCnt(int cnt);
protected:

	void Redo();

	virtual bool  HandleOtherTask();

	void HandleRspQuery();

	void OnUserLoginRsp(CXTPPackage *pMessage);

	void OnUserLogoutRsp(CXTPPackage *pMessage, CFTDCRSession *pSession);

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

	
	CIndexPackageFlow *GetUserFlow(const CBrokerIDType &brokerID,const CUserIDType &userID);
	
	void SendToUserFlow(const CBrokerIDType &brokerID,const CUserIDType &userID, int nIndex);
	
	bool PublishFlow(CFTDCRSession *pSession, WORD wSequenceSeries, int nSubStartId,int &nPubStartId);	
	
	void SendToDialogFlow(CFTDCRSession *pSession, CFTDCPackage *pPackage);	

	void SendToQueryFlow(CFTDCRSession *pSession, CFTDCPackage *pPackage);	
	
	list<CUserIDType>* GetUsersByInvestorID(CInvestorIDType& InvestorID);

	bool  m_bBindThreadsToCPU;
private:
	virtual void DispatchIOs();

	DWORD m_dwFrontID;
	CFlowReader m_ResultReader;
	CFlow* m_pTradeResult;
	CFlow* m_pSlogResult;

	CFTDCPackage m_rspPackage;
	CXTPPackage m_XtpPackage;

	bool m_bNoShmChannelFlag;

	CFlow *m_pPrivateFlow;
	CFlow *m_pPublicFlow;
	typedef CHashMap<CBrokerIDType, CIndexPackageFlow *, HashString> CParticipantFlowMap;
	CParticipantFlowMap m_mapPrivateFlow;
	
	typedef map<string, CIndexPackageFlow *> CUserFlowMap;
	CUserFlowMap m_mapUserFlow;
	typedef map<CInvestorIDType,list<CUserIDType>*> CInvestorUserMap;
	CInvestorUserMap m_InvestorUserMap;//investor��user֮��Ķ�Ӧ��ϵ��
	
	typedef map<DWORD, TSessionInfo> CSessionMap;
	CSessionMap m_SessionMap;
	int m_nLifeCycleID;
	CFlowReader m_QueryReader;

	typedef vector<string> CDelayVector;
	CDelayVector m_Delay;
	CDelayVector m_QdpDelay;//��qdp��صı���

#ifndef WIN32
	struct timeval m_nBeginTime; //ԭʼ����ʱ��
#else
	struct _timeb  m_nBeginTime;
#endif
	char tmp[100];
	int m_nRedoFlowCnt;
};

inline CFlow *CKernelWriteThread::GetPublicFlow()
{
	return m_pPublicFlow;
}

#endif
