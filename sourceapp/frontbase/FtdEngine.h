// FtdEngine.h: interface for the CFtdEngine class.

//

// 20070704 hwp	���ӻ��ڽ���Ա��˽����

// 20071012 hwp  ���Ӷ���ָ�ReqSubscribeTopic����ʹ����Ա�˿�������

//                  ���������ش��������ڽ���Ա�˱�֤�����������

// 20080626 hwp  NT-0041�Ի����Ͳ�ѯ������ʹ��Flow����ֻ������ţ������ڴ�ռ��

// 20080701 hwp  NT-0035��������֪ͨ����¼ʱ����������Ĵ��룬������Ҫ

//                  ��������������֪ͨ

// 20080727 hwp  NT-0048:��չCSessionFactory::CreateSession���������ڴ���

//                  �Ựʱ���ֲ�ͬ������

// 20081128 hwp  NT-0056-UserAPI���Ӳ�ѯ��������ǰ���ȵķ���

//////////////////////////////////////////////////////////////////////



#if !defined(AFX_FTDENGINE_H__A2F23839_A3FB_492C_AF58_0BB3B5CDD26A__INCLUDED_)

#define AFX_FTDENGINE_H__A2F23839_A3FB_492C_AF58_0BB3B5CDD26A__INCLUDED_



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000



#include "FrontEngine.h"

#include "FTDCSession.h"

#include "XtpData.h"

//investor��user֮��Ķ�Ӧ��ϵ��
typedef map<CInvestorIDType,list<CUserIDType>*> CInvestorUserMap;

const int FTDE_MAX_SEQUENCE_SERIES = 10;



struct TFtdeDisseminationField

{

	WORD wSequenceSeries;

	int nSubStartId;

	int nPubStartId;

};

struct TFtdeDisseminationInfo

{

	DWORD nSessionID;

	CDateType TradingDay;

	CDataCenterIDType DataCenterID;
	
	int nFieldCount;

	TFtdeDisseminationField Fields[FTDE_MAX_SEQUENCE_SERIES];

};

typedef vector<string> CDelayVector;

class CCalcOrderRespTime
{
public:
	CCalcOrderRespTime();
	~CCalcOrderRespTime();
	//��ʱʱˢ�����Ƶ�λʱ���ڲ�����ʶ��
	void TimerFlush();
	
	//�жϵ�ǰ�Ƿ���Բ���
	bool IsCanCatch();

	//ԭʼ��������
	void InputSample(CUserOrderLocalIDType &OrderLocalID,CUserIDType &UserID);

	//�����������,���Ӳ���ExternalLatency-��������ϵͳ��ʱ+������ʱ(��λ��΢��us)������BusinessUnit�ֶ�-wangwei,20130729
	void InputResult(COrderSysIDType &OrderSysID,CUserOrderLocalIDType &OrderLocalID,CUserIDType &UserID,CBusinessUnitType& ExternalLatency);
	//�����������
	void InputResult(COrderSysIDType &OrderSysID,CUserOrderLocalIDType &OrderLocalID,CUserIDType &UserID);

private:
	int  m_nLampColor;	//�źŵ���ɫ

#ifndef WIN32
	struct timeval m_nBeginTime; //ԭʼ����ʱ��
#else
	struct _timeb  m_nBeginTime;
#endif

	//����
	CUserOrderLocalIDType	m_OrderLocalID;
	CUserIDType	m_UserID;
	int m_CostTime;
};


class CFrontFlowBroken

{

public:

	CFrontFlowBroken();

	~CFrontFlowBroken();

	void Clear();

	

	void RegisterDataCenter(const CDataCenterIDType &DataCenterID);



	void RegisterParticpantFlowBorken(const CBrokerIDType &BrokerID,

		int nSequenceNo);

//	void RegisterUserFlowBorken(const CUserIDType &UserID, int nSequenceNo);



	void RegisterPublicFlowBroken(int nSequenceNo);

	

	const CDataCenterIDType &GetDataCenter();

	int GetParticpantFlowBorken(const CBrokerIDType &BrokerID);

	int GetUserFlowBroken(const CBrokerIDType &BrokerID,const CUserIDType &UserID);

	int GetPublicFlowBroken();

protected:

	typedef map<CBrokerIDType, int> CParticipantFlowBrokenMap;

	CParticipantFlowBrokenMap m_mapPrivateFlowBroken;



	typedef map<string, int> CUserFlowBrokenMap;

	CUserFlowBrokenMap m_mapUserFlowBroken;

	

	int m_nPublicFlowBroken;



	CDataCenterIDType m_DataCenterID;	

};



class CFtdEngine : public CFrontEngine, public CFTDCSessionCallback 

{

public:

	CFtdEngine(CReactor *pReactor, CFrontForwarder *pFrontForwarder,

		const char *pszFlowPath,CFlow* pSlogResult,CSelectReactor* pConnReactor=NULL);

	virtual ~CFtdEngine();

	//Add by zbz ������Ӧʱ��ɼ��Ķ�ʱ��
	virtual void OnTimer(int nIDEvent);


	/**����������յ���XTP���ģ����׽����

	* @param pMessage �������յ���XTP����

	* @remark ��CFrontEngine����

	*/

	virtual void HandleMessage(CXTPPackage *pMessage);



	/**����Ӻ�̨�����յ���Ӧ�𣨲�ѯ�����

	* @param pPackage �Ӻ�̨�����յ���Ӧ��

	* @remark ��CFrontEngine����

	*/

	virtual void OnResponse(CXTPPackage *pPackage);



	/**����ӿͻ��˷�����FTDC����

	* @param pFTDCPackage �ӿͻ��˷�����FTDC����

	* @param pSession ��������ĻỰ

	* @remark ��CFTDCSessionCallback����

	*/

	virtual int HandlePackage(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession);


	virtual bool DispatcherEvent(int nEventID, DWORD dwParam, void *pParam);

	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);

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
	void PrintDelayLog(CInputOrderField &field);
	void DumpDelayLog();
protected:

	virtual CSession *CreateSession(CChannel *pChannel, DWORD);

	virtual void OnSessionDisconnected(CSession *pSession, int nReason);



	bool HandleNotify(CXTPPackage *pMessage);

	bool HandleResponse(CXTPPackage *pMessage);



	CIndexPackageFlow *GetUserFlow(const CBrokerIDType &brokerID,const CUserIDType &userID);

	void SendToUserFlow(const CBrokerIDType &brokerID,const CUserIDType &userID, int nIndex);



	bool PublishFlow(CFTDCSession *pSession, WORD wSequenceSeries, int nSubStartId,

		int &nPubStartId, bool bCheckDataCenter);



	void SendToDialogFlow(CFTDCSession *pSession, CFTDCPackage *pPackage);

	void SendToQueryFlow(CFTDCSession *pSession, CFTDCPackage *pPackage);

	list<CUserIDType>* GetUsersByInvestorID(CInvestorIDType& InvestorID);

private:

	void SendErrorRsp(CFTDCPackage *pRequest, CFTDCSession *pSession, 

		const int nErrorCode, const char *pszErrorMsg);

//	void OnNtfDataCenterDesc(CXTPPackage *pMessage);



	void OnNtfSwitch(CXTPPackage *pMessage);



	void OnNtfCommPhaseChange(CXTPPackage *pMessage);

	void OnNtfDelUserSession(CXTPPackage *pMessage);



	int OnReqUserLogin(CFTDCPackage *pPackage, CFTDCSession *pSession);

	int OnReqSubscribeTopic(CFTDCPackage *pPackage, CFTDCSession *pSession);

	void OnUserLoginRsp(CXTPPackage *pMessage, CFTDCSession *pSession);

	void OnUserLogoutRsp(CXTPPackage *pMessage, CFTDCSession *pSession);

	int OnReqQryTopic(CFTDCPackage *pPackage, CFTDCSession *pSession);

private:

	CFTDCPackage m_rspPackage;

	typedef CHashMap<DWORD, TFtdeDisseminationInfo, HashInt> CDisseminationInfoMap;

	CDisseminationInfoMap m_mapDisseminationInfo;



	typedef map<string, CIndexPackageFlow *> CUserFlowMap;

	CUserFlowMap m_mapUserFlow;

	CDateType m_TradingDay;

//	CDataCenterIDType m_DataCenterID;

	CFrontFlowBroken m_FrontFlowBroken;

	CCalcOrderRespTime m_CalcOrderRespTime;
	CInvestorUserMap m_InvestorUserMap;//investor��user֮��Ķ�Ӧ��ϵ��
	CDelayVector m_Delay;
#ifndef WIN32
	struct timeval m_nBeginTime; //ԭʼ����ʱ��
#else
	struct _timeb  m_nBeginTime;
#endif
	char tmp[100];
};



#endif // !defined(AFX_FTDENGINE_H__A2F23839_A3FB_492C_AF58_0BB3B5CDD26A__INCLUDED_)

