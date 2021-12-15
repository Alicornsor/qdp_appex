// FtdEngine.h: interface for the CFtdEngine class.

//

// 20070704 hwp	增加基于交易员的私有流

// 20071012 hwp  增加订阅指令（ReqSubscribeTopic），使交易员端可以自行

//                  控制流的重传，有利于交易员端保证事务的完整性

// 20080626 hwp  NT-0041对话流和查询流不再使用Flow对象，只管理序号，减少内存占用

// 20080701 hwp  NT-0035数据中心通知，登录时检查数据中心代码，根据需要

//                  发出数据流回退通知

// 20080727 hwp  NT-0048:扩展CSessionFactory::CreateSession参数，便于创建

//                  会话时区分不同的连接

// 20081128 hwp  NT-0056-UserAPI增加查询数据流当前长度的方法

//////////////////////////////////////////////////////////////////////



#if !defined(AFX_FTDENGINE_H__A2F23839_A3FB_492C_AF58_0BB3B5CDD26A__INCLUDED_)

#define AFX_FTDENGINE_H__A2F23839_A3FB_492C_AF58_0BB3B5CDD26A__INCLUDED_



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000



#include "FrontEngine.h"

#include "FTDCSession.h"

#include "XtpData.h"

//investor和user之间的对应关系表
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
	//定时时刷，控制单位时间内采样标识灯
	void TimerFlush();
	
	//判断当前是否可以采样
	bool IsCanCatch();

	//原始采样输入
	void InputSample(CUserOrderLocalIDType &OrderLocalID,CUserIDType &UserID);

	//结果采样输入,增加参数ExternalLatency-包括交易系统延时+网络延时(单位是微秒us)，复用BusinessUnit字段-wangwei,20130729
	void InputResult(COrderSysIDType &OrderSysID,CUserOrderLocalIDType &OrderLocalID,CUserIDType &UserID,CBusinessUnitType& ExternalLatency);
	//结果采样输入
	void InputResult(COrderSysIDType &OrderSysID,CUserOrderLocalIDType &OrderLocalID,CUserIDType &UserID);

private:
	int  m_nLampColor;	//信号灯颜色

#ifndef WIN32
	struct timeval m_nBeginTime; //原始采样时间
#else
	struct _timeb  m_nBeginTime;
#endif

	//样本
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

	//Add by zbz 订单响应时间采集的定时器
	virtual void OnTimer(int nIDEvent);


	/**处理从总线收到的XTP报文（交易结果）

	* @param pMessage 从总线收到的XTP报文

	* @remark 从CFrontEngine重载

	*/

	virtual void HandleMessage(CXTPPackage *pMessage);



	/**处理从后台服务收到的应答（查询结果）

	* @param pPackage 从后台服务收到的应答

	* @remark 从CFrontEngine重载

	*/

	virtual void OnResponse(CXTPPackage *pPackage);



	/**处理从客户端发出的FTDC请求

	* @param pFTDCPackage 从客户端发出的FTDC请求

	* @param pSession 接收请求的会话

	* @remark 从CFTDCSessionCallback重载

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
	CInvestorUserMap m_InvestorUserMap;//investor和user之间的对应关系表
	CDelayVector m_Delay;
#ifndef WIN32
	struct timeval m_nBeginTime; //原始采样时间
#else
	struct _timeb  m_nBeginTime;
#endif
	char tmp[100];
};



#endif // !defined(AFX_FTDENGINE_H__A2F23839_A3FB_492C_AF58_0BB3B5CDD26A__INCLUDED_)

