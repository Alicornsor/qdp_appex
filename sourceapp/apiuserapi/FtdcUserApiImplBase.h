/////////////////////////////////////////////////////////////////////////
///@system ��һ��������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file FtdcUserApiImpl.h
///@brief �����˿ͻ��˽ӿ�ʵ��
///@history 
///20060106	��ά �������ļ�
///20061012	��ά ���Ӷ�SSL���У���֧��
///20070216	�½�   ���tradeapi���ص�Ԥ����ֵ��
///20070806	��ά ���ӷ�����
///                SubscribeUserTopic ���Ľ���Ա����
///                SetHeartbeatTimeout ����������ʱʱ�䡣
///                OpenRequestLog ��������־�ļ�
///                OpenResponseLog ��Ӧ����־�ļ�
///20070924 ��ά �����̳й�ϵ����֧��nameserver
// 20080727 ��ά NT-0048:��չCSessionFactory::CreateSession���������ڴ���
//                 �Ựʱ���ֲ�ͬ������
// 20090504 ��ά NT-0072:����UserAPI�����̲߳���ȫ����
// 20090505 ��ά NT-0073:����UserAPI�������������������
//                         �����Ի����������������
//                         �汾��Ϣ������������ʱ���ʾ��С�汾��
/////////////////////////////////////////////////////////////////////////

#if !defined(_FTDCUSERAPIIMPLBASE_H)
#define _FTDCUSERAPIIMPLBASE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Flow.h"
#include "Mutex.h"
#include "FtdcUserApiMacro.h"
#include FTDCUSERAPI_H
#include "NsSessionFactory.h"
#include "SelectReactor.h"
#include "FTDCSubscriber.h"
#include "FtdPackageDesc.h"
#include "FTDCSession.h"
#include "Storage.h"
#include "PipeEventHandler.h"
#include "UFEntityCopy.h"

///tradeapi���ص�Ԥ����ֵ
#define MAXQUERYUNFINISHED	1
#define MAXQUERYPERSECOND	50

#define MAXDIALOGUNFINISHED	1500
#define MAXDIALOGPERSECOND	3000 
#define CFFEXTOPIC			100
#define SHFETOPIC			1001
#define ZCETOPIC			120
#define DCETOPIC			110
#define ZQTOPIC				130
#define CQGTOPIC			200
#define CTPTOPIC			300
#define PATSTOPIC			800
#define YISHENSTOPIC		900
#define SGETOPIC		    1000
#define GET_PART_MARKETDATA(name)											\
		case FTD_FID_##name:												\
			{																\
				CFTD##name##Field field##name;								\
				titor.Retrieve(&field##name.m_Describe, &field##name);		\
				Copy##name##Entity(pTopicDepthMarketData, &field##name);	\
			}																\
			break;


class CFtdcUserApiImplBase;
class CFtdcUserSubscriber;

class CMarketDataFlowManager
{
public:
	CMarketDataFlowManager(const char *pszFlowPath);
	~CMarketDataFlowManager();
	CFlow *GetFlow(DWORD nTopicID);
	bool RegisterTopic(DWORD nTopicID);
private:
	typedef CHashMap<DWORD, CFlow *, HashInt> CFlowMap;
	CFlowMap m_mapFlow;
	string m_strFlowPath;
};

struct CTopicDepthMarketDataField : public CFTDDepthMarketDataField
{
	WORD SequenceSeries;
};
class CTopicDepthMarketDataStorage :public CStorage<CTopicDepthMarketDataField>
{
public:
	DEFINE_INDEX_FUNC_2(0, WORD, SequenceSeries, const char *, InstrumentID);
	CTopicDepthMarketDataStorage()
	{
		CREATE_INDEX_2(SequenceSeries, InstrumentID);
	}
};
class CFtdcUserResumeInfo
{
public:
	CFtdcUserResumeInfo(const char *pszPath, const char *pszUserApiType,
		const char *pszFileName);
	~CFtdcUserResumeInfo();
	const CDateType &GetTradingDay();
	const CDataCenterIDType &GetDataCenterID();
	bool Update(const CDateType &TradingDay, CDataCenterIDType &DataCenterID);
public:
	bool SerializeLoad();
	bool SerializeStore();
private:
	void InitResumeInfo();
private:
	enum{
		FILE_VERSION = 1
	};
private:
	string m_strFullFileName;
	int m_nFileVersion;
	CDateType m_TradingDay;
	CDataCenterIDType m_DataCenterID;
};

typedef map<CInstrumentIDType,CInstrumentIDType> InstrumetIdMap;
class CFtdcUserApiImplBase : public FTDCUSERAPI, public CNsSessionFactory, public CFTDCSessionCallback
{
public:
	CFtdcUserApiImplBase(const char *pszFlowPath, const char *pszUserApiType,
		CReactor *pReactor);
	
	~CFtdcUserApiImplBase();

	virtual void SetMultiCast(bool bMultiCast=false);
	virtual void RegMultiTopicID(int TopicID);
	virtual void Init(int nPrivatePort);
	
	virtual int Join();
	
	virtual void Release();

	virtual const char *GetTradingDay();
	
	virtual void RegisterNameServer(char *pszFrontAddress);
	
	virtual void RegisterFront(char *pszFrontAddress);
	
	virtual void RegisterSpi(FTDCUSERSPI *pSpi);
		
	virtual void SubscribeMarketDataTopic(int nTopicID, TE_RESUME_TYPE nResume);

	virtual void SubscribePrivateTopic(TE_RESUME_TYPE nResumeType);
	
	virtual void SubscribePublicTopic(TE_RESUME_TYPE nResumeType);

	virtual void SubscribeUserTopic(TE_RESUME_TYPE nResumeType);

	virtual int SubMarketData(char *ppInstrumentID[], int nCount);
	
	virtual int UnSubMarketData(char *ppInstrumentID[], int nCount);		
	
	virtual void SetHeartbeatTimeout(unsigned int timeout);

	virtual int OpenRequestLog(const char *pszReqLogFileName);

	virtual int OpenResponseLog(const char *pszRspLogFileName);
	
	virtual int ReqDumpMemDb(FTDCMEMDBFIELD *pMemDb, int nRequestID)=0;
	
	virtual int ReqUserLogin(FTDCREQUSERLOGINFIELD *pReqUserLoginField, int nRequestID);
	
	virtual void HandleResponse(CFTDCPackage *pMessage, WORD wSequenceSeries) = 0;

	virtual int HandlePackage(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession);
	
	CReactor *GetReactor();
protected:
	virtual CSession *CreateSession(CChannel *pChannel, DWORD);
	virtual void OnSessionConnected(CSession *pSession);
	virtual void OnSessionDisconnected(CSession *pSession, int nReason);
	virtual void OnSessionWarning(CSession *pSession, int nReason, int nParam);	

	int RequestToDialogFlow();
	int RequestToQueryFlow();
	int RequestDirectly();
    void OnIntlTopicSearch(CFTDCPackage *pMessage, WORD wSequenceSeries,bool bDoodle=false);
	void OnIntlRtnDepthMarketData(CFTDCPackage *pMessage, WORD wSequenceSeries,bool bDoodle=false);
	void OnIntlRtnDissemination(CFTDCPackage *pMessage, WORD wSequenceSeries);

	void OnRtnDepthMarketData(CFTDDepthMarketDataField *pMarketData, WORD wSequenceSeries);

	//�����ಥ�����ӿ�
	void  OnMultiHeartbeat(char *CurrTime,char *MultiCastIP);

	friend class CMDMultiPackageHandler;
private:
	void CreateDialogFlow();
	void RemoveDialogFlow();
	void CreateQueryFlow();
	void RemoveQueryFlow();
	void CreateSubscriber(int nTopicID, CFlow *pFlow, TE_RESUME_TYPE nResumeType);

    ///���Session��ʹ�õı���IP��ַ��Ӧ��MAC
    ///@param	ipAddressBuffer �洢MAC��ַ��buffer, buffer�ĳ��Ȳ�С��17
    ///@return	д��buffer�����ݳ��ȣ�-1��ʾ��ȡMAC���󣻻��MAC��ַ��ʽΪ00:0C:29:F1:07:B5
    ///@author  lidp 20140716
    int GetSessionLocalMac(char * macAddressBuffer);

protected:
	FTDCUSERSPI *m_pSpi;
	CFTDCPackage m_reqPackage;
	CMutex m_mutexAction;
	FILE *m_fpRequstDump;
	FILE *m_fpResponseDump;

private:

	CFlow *m_pDialogReqFlow;
	CFlow *m_pQueryReqFlow;
	CFlow *m_pPrivateFlow;
	CFlow *m_pUserFlow;
	CFlow *m_pPublicFlow;

	typedef map<WORD, CFtdcUserSubscriber *> CUserSubscriberMap;
	CUserSubscriberMap m_mapSubscriber;
	CMarketDataFlowManager *m_pMarketDataFlowManager;
	DWORD m_nSessionID;
	string m_strFlowPath;
	DWORD m_dwHeartbeatTimeout;

	CTopicDepthMarketDataStorage m_storageTopicDepthMarketData;
	CFtdcUserResumeInfo m_ResumeInfo;
	bool m_bManagedResume;
	string m_strUserApiType;
	
	CPipeEventHandler *m_pPipeEventHandler;
	typedef CHashMap<CInstrumentIDType,CFTDSpecificInstrumentField,HashString> m_mapAllSubInstruments;
	typedef CHashMap<CInstrumentIDType,CFTDSpecificInstrumentField,HashString> m_mapAllUnSubInstruments;
	//�ಥ����
	bool m_bMultiCastFlag;
	vector<int> m_vMultiTopicID;

	vector<CInstrumentIDType> m_instrumentid;

	InstrumetIdMap instrumentidmap;
	
	char **b_ppInstrumentID;
	int i_count;

};

class CApiWorkThread : public CReactor
{
public:

	CApiWorkThread();

	~CApiWorkThread();

	/**????IO??????
	* @param pEventHandler ???????? 
	*/
	virtual void RegisterIO(CEventHandler *pEventHandler);
	
	/**???list?????IO??????
	* @param pEventHandler ???????? 
	*/
	virtual void RemoveIO(CEventHandler *pEventHandler);

protected:
	
private:
	virtual void DispatchIOs();

	CEventHandler * m_pApiSession;
};



#endif
