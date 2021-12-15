// MDFront.h: interface for the CMDFront class.
// ����Դǰ�ã�����api������Դ�Ľ���
// 20071017 ���һ�	���Ӷ���ָ�ReqSubscribeTopic����ʹ����Ա�˿�������
//                  ���������ش��������ڽ���Ա�˱�֤�����������  
// 20080116 ���һ�	���������ش������ֶζ�ʧ��BUG��
//					���Ӻ���RspTopicMarketDataVersion����������ǰ���������
// 20080626 ���һ�  NT-0041�Ի�������ʹ��Flow����ֻ������ţ������ڴ�ռ��
// 20080727 ���һ�  NT-0048:��չCSessionFactory::CreateSession���������ڴ���
//                  �Ựʱ���ֲ�ͬ������
// 20081128 ���һ�  NT-0056-UserAPI���Ӳ�ѯ��������ǰ���ȵķ���
// 20090310 ���һ�  NT-0068:���Ӷ�SSL�ļ�飬�޸��˷���OnReqUserLogin 
//                  OnReqUserLogin����������ߣ����ô����ӶԷ���ֵ�ļ��
// 20090310 ���һ�  NT-0069:MdKernel�е�����ǰ��֧�ֶ��߳�
// 20090428 ���һ�  NT-0069:ʹ�ü��������CMDServiceSynchronizer�ݹ��������
// 20090514 ���һ�  NT-0081:����mdkernel�ظ���¼����
// 20100125 ���һ�	NT-0095:PublishFlowsʹ��SessionInfo�л����TradingDay��DataCenterID;
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDFRONT_H__9061C690_1892_4A31_9D6F_A180857D3F20__INCLUDED_)
#define AFX_MDFRONT_H__9061C690_1892_4A31_9D6F_A180857D3F20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HashMap.h"
#include "Flow.h"
#include "customDataType.h"
#include "SessionFactory.h"
#include "IndexPackageFlow.h"
#include "FTDCSession.h"
#include "FtdData.h"
#include "MarketDataFlowManager.h"
#include "CTransaction.h"
#include "XtpData.h"
#include "CErrorEngine.h"
#include "MarketDataHandler.h"
#include "system.h"

const int MDF_MAX_SEQUENCE_SERIES = 100;

const int UM_MDFRONT_SERVICE_SYNC			= 0x41C00 + SM_USER;
const int UM_MDFRONT_ADD_SESSION			= 0x41C01 + SM_USER;
const int UM_MDFRONT_DEL_SESSION			= 0x41C02 + SM_USER;
const int UM_MDFRONT_COMMPHASE_CHANGE		= 0x41C03 + SM_USER;

//�����ڴ�����
#define  SHMCOUNT   1000000 
//����������� 
#define MDQDP 0
#define MDCFFEX 1
#define MDSHFE 2
#define MDZCE 3
#define MDDCE 4
#define MDZQ 9
//����flag
#define FOPEN 1
//�ر�flag
#define FCLOSE 1

#define CFFEXTOPIC			100
#define SHFETOPIC			1001
#define ZCETOPIC			120
#define DCETOPIC			110
#define ZQTOPIC				130
#define CQGTOPIC			200
#define CTPTOPIC			300
#define PATSTOPIC			800
#define ESTOPIC		    	900
#define SGETOPIC		    1000

#define	ProductInfo  "QDP_v1.0"	//��Ʒ��Ϣ

typedef struct
{
	CFrontIDType	frontID;
	CSessionIDType	sessionID;
}	MDTSessionRef;

class CMDServiceSynchronizer
{
public:
	CMDServiceSynchronizer(CEventHandler *pSynchronizee)
		:m_semStartLock(0), m_semEndLock(0)
	{
		m_pSynchronizee = pSynchronizee;
		m_nSyncCount = 0;
	}
	~CMDServiceSynchronizer()
	{
	}
	void Wait()
	{
		m_nSyncCount ++;
		if (m_nSyncCount > 1)		//�Ѿ���ÿ���Ȩ
		{
			return;
		}
		m_pSynchronizee->PostEvent(UM_MDFRONT_SERVICE_SYNC, 0, this);
		m_semStartLock.Lock();
	}
	void End()
	{
		m_nSyncCount--;
		if (m_nSyncCount == 0)
		{
			m_semEndLock.UnLock();
		}
	}
	void Start()
	{
		m_semStartLock.UnLock();
		m_semEndLock.Lock();
	}
private:
	CSemaphore m_semStartLock;
	CSemaphore m_semEndLock;
	CEventHandler *m_pSynchronizee;
	int m_nSyncCount;
};

struct TMDFrontSessionInfo
{
	DWORD nSessionID;
	CSession *pSession;
	DWORD nConnectTime;
	bool bIsLogin;
	CUserIDType UserID;
	CParticipantIDType ParticipantID;
	CDateType TradingDay;
	CDataCenterIDType DataCenterID;
	int nDialogFlowSeqNo;				/**<�Ի�����ǰ��� */
	TMDFrontSessionInfo& operator =(const TMDFrontSessionInfo &r)
	{
		memcpy(this, &r, sizeof(TMDFrontSessionInfo));
		return *this;
	}
};

class CMDFront : public CEventHandler, public CSessionCallback, public CFTDCSessionCallback
{
public:
	CMDFront(CReactor *pReactor, DWORD nFrontID, CMDFlowManager *pFlowManager,CEventHandler *pFrontManager,CMarketDataHandler * pMarketDataHandler);
	virtual ~CMDFront();

	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);
	/**����ӿͻ��˷�����FTDC����
	* @param pFTDCPackage �ӿͻ��˷�����FTDC����
	* @param pSession ��������ĻỰ
	* @remark ��CFTDCSessionCallback����
	*/
	virtual int HandlePackage(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession);
	
	void OnCommPhaseChange(WORD nCommPhaseNo);

	int AddSession(CFTDCSession *pSession);
	int DelSession(DWORD dwSessionID, int nErrorCode);
	CFTDCSession * GetSession(DWORD dwSessionID);
	void ChangeDateDisconnectAll();
protected:
	virtual void OnSessionConnected(CSession *pSession);
	virtual void OnSessionDisconnected(CSession *pSession, int nReason);
	virtual void OnSessionWarning(CSession *pSession, int nReason, int nParam);
	
private:
	void DisconnectAll(int nReason);
	void ClearAllMap();
	bool IsSessionLogin(DWORD nSessionID);
	bool GetSessionOwner(DWORD nSessionID, CUserIDType &userID, CParticipantIDType &participantID);		
	void SetSessionOwner(DWORD nSessionID, CUserIDType &userID, CParticipantIDType &participantID);	
	void SetResumeInfo(DWORD nSessionID, const CDateType &TradingDay, 
		const CDataCenterIDType &DataCenterID);
	void ClearSessionOwner(const DWORD nSessionID);
	void SendToDialogFlow(CFTDCSession *pSession, CFTDCPackage *pPackage);
	void SendErrorRsp(CFTDCSession *pSession, const int nErrorCode, const char *pszErrorMsg);
	void SetErrorInfo(CFTDRspInfoField *pRspInfoField);

	int OnReqUserLogin(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession);
	void OnReqUserLogout(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession);

	int OnReqSubMarketData(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession);
	int OnReqUnSubMarketData(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession);

	int OnReqTopicSearch(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession);
	void PublishFlows(CFTDCPackage *pSubscribePackage, CFTDCSession *pSession, CFTDCPackage *pRspPackage);
	void RspTopicMarketData(CFTDCSession *pSession, CFTDCPackage *pFTDCPackage, CReadOnlyTopicIDType &TopicID);
	void RspTopicMarketDataVersion(CFTDCSession *pSession, CFTDCPackage *pFTDCPackage, 
		CReadOnlyTopicIDType &TopicID, CReadOnlySequenceNoType &Version);
	void OnReqSubscribeTopic(CFTDCPackage *pPackage, CFTDCSession *pSession);
	int OnReqQryTopic(CFTDCPackage *pPackage, CFTDCSession *pSession);
	int OnRspQryDepthMarketData(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession);
	void OnRtnMarketDataInstrumentState(CFTDCSession *pSession, CFTDCPackage *pFTDCPackage,
								  CReadOnlyTopicIDType &TopicID);
private:
	DWORD m_nFrontID;

	typedef CHashMap<DWORD, TMDFrontSessionInfo, HashInt> CSessionInfoMap;
	CSessionInfoMap m_mapSessionInfo;

	CMDFlowManager *m_pFlowManager;
	
	CFTDCPackage m_rspPackage;

	CMDServiceSynchronizer m_Synchronizer;
	CEventHandler * m_pFrontManager;
	CErrorEngine *m_pErrorEngine;
	CMarketDataHandler * m_marketDataHandler;

	//�¶��ĺ�Լ��
	map<CInstrumentIDType,CInstrumentIDType> n_newInstrument; 
};

class CMDFrontManager : public CSessionFactory
{
public:
	CMDFrontManager(CReactor *pReactor, DWORD nFrontID, CMDFlowManager *pFlowManager,CMarketDataHandler * pMarketDataHandler);
	~CMDFrontManager();
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);
	virtual CSession *CreateSession(CChannel *pChannel, DWORD dwMark);
	void OnCommPhaseChange(WORD nCommPhaseNo);
	CSelectReactor * CreateFront(int nFrontCount);
	void DisconnectFronts();
private:
	int m_nNextFront;
	int m_nFrontID;
	vector<CReactor *> m_Reactors;
	vector<CMDFront *> m_Fronts;
	CMDFlowManager *m_pFlowManager;
	CMarketDataHandler * m_pMarketDataHandler;
};

#endif // !defined(AFX_MDFRONT_H__9061C690_1892_4A31_9D6F_A180857D3F20__INCLUDED_)
