/////////////////////////////////////////////////////////////////////////
///@system QuantDo Trade Engine
///@company Shanghai Quantdo Network Technology Co., Ltd.
///@file ApexFtdcTraderApi.h
///@brief Defines Client Side Interface
///@history
///20161212	Xu Zhonghua		Creation
/////////////////////////////////////////////////////////////////////////

#if !defined(APEX_FTDCTRADERAPI_H)
#define APEX_FTDCTRADERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ApexFtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport)
#else
#define TRADER_API_EXPORT __declspec(dllimport)
#endif
#else
#define TRADER_API_EXPORT 
#endif

class CApexFtdcTraderSpi
{
public:
	///Invoked when connection is established between client and server (which is before login)
	virtual void OnFrontConnected(){};
	
	///Invoked on disconnected. API automatically tries to reconnect when it happens. No special handling required on client side
	///@param nReason Reason of error
	///        0x1001 Network Read Failure
	///        0x1002 Network Write Failure
	///        0x2001 Heartbeat Answer Timeout
	///        0x2002 Failed Sending Heartbeat
	///        0x2003 Incorrect Response Received
	virtual void OnFrontDisconnected(int nReason){};
		
	///Heartbeat Timeout Warning. Invoked when response is not received in a long time.
	///@param nTimeLapse: Timespan(in seconds) after last response is received
	virtual void OnHeartBeatWarning(int nTimeLapse){};
	
	///Invoked on Return Package Starts. This is the first function invoked when a return is received. Followed by callbacks of various data fields. Ends with "OnPackageEnd"
	///@param nTopicID: Topic ID (e.g. Private Stream, Public Stream or Market Data Stream)
	///@param nSequenceNo: Sequence Number
	virtual void OnPackageStart(int nTopicID, int nSequenceNo){};
	
	///Invoked on Return Package Ends. When a return is received. "OnPackageStart" is invoked first. Followed by callbacks of various data fields. Finally this function.
	///@param nTopicID: Topic ID (e.g. Private Stream, Public Stream or Market Data Stream)
	///@param nSequenceNo: Sequence Number
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo){};


	///Error Response
	virtual void OnRspError(CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///User Login Response
	virtual void OnRspUserLogin(CApexFtdcRspUserLoginField *pRspUserLogin, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///User Logout Response
	virtual void OnRspUserLogout(CApexFtdcRspUserLogoutField *pRspUserLogout, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Order Inserting Response
	virtual void OnRspOrderInsert(CApexFtdcInputOrderField *pInputOrder, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Order Action Response
	virtual void OnRspOrderAction(CApexFtdcOrderActionField *pOrderAction, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Quote Inserting Response
	virtual void OnRspQuoteInsert(CApexFtdcInputQuoteField *pInputQuote, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Quote Action Response
	virtual void OnRspQuoteAction(CApexFtdcQuoteActionField *pQuoteAction, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///User Password Update Response
	virtual void OnRspUserPasswordUpdate(CApexFtdcUserPasswordUpdateField *pUserPasswordUpdate, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Execution Order Inserting Response
	virtual void OnRspExecOrderInsert(CApexFtdcInputExecOrderField *pInputExecOrder, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Execution Order Action Response
	virtual void OnRspExecOrderAction(CApexFtdcExecOrderActionField *pExecOrderAction, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Admin Order Inserting Response
	virtual void OnRspAdminOrderInsert(CApexFtdcInputAdminOrderField *pInputAdminOrder, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Combined Order Inserting Response
	virtual void OnRspCombOrderInsert(CApexFtdcInputCombOrderField *pInputCombOrder, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Topic Subscription Response
	virtual void OnRspSubscribeTopic(CApexFtdcDisseminationField *pDissemination, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Participant Account Query Response
	virtual void OnRspQryPartAccount(CApexFtdcRspPartAccountField *pRspPartAccount, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Order Query Response
	virtual void OnRspQryOrder(CApexFtdcOrderField *pOrder, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Quote Query Response
	virtual void OnRspQryQuote(CApexFtdcQuoteField *pQuote, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Trade Query Response
	virtual void OnRspQryTrade(CApexFtdcTradeField *pTrade, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Client Query Response
	virtual void OnRspQryClient(CApexFtdcRspClientField *pRspClient, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Participant Position Query Response
	virtual void OnRspQryPartPosition(CApexFtdcRspPartPositionField *pRspPartPosition, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Client Position Query Response
	virtual void OnRspQryClientPosition(CApexFtdcRspClientPositionField *pRspClientPosition, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Instrument Query Response
	virtual void OnRspQryInstrument(CApexFtdcRspInstrumentField *pRspInstrument, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Instrument Status Query Response
	virtual void OnRspQryInstrumentStatus(CApexFtdcInstrumentStatusField *pInstrumentStatus, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Hedge Volumn Query Response
	virtual void OnRspQryHedgeVolume(CApexFtdcHedgeVolumeField *pHedgeVolume, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Credit Limit Query Response
	virtual void OnRspQryCreditLimit(CApexFtdcCreditLimitField *pCreditLimit, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Combined Order Query Response
	virtual void OnRspQryCombOrder(CApexFtdcCombOrderField *pCombOrder, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Ordinary Market Data Query Response
	virtual void OnRspQryMarketData(CApexFtdcMarketDataField *pMarketData, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Bulletin Query Response
	virtual void OnRspQryBulletin(CApexFtdcBulletinField *pBulletin, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Topic Query Response
	virtual void OnRspQryTopic(CApexFtdcDisseminationField *pDissemination, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Pending Order Breakdown List Query Response
	virtual void OnRspQryMBLMarketData(CApexFtdcMBLMarketDataField *pMBLMarketData, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Trade Return Object
	virtual void OnRtnTrade(CApexFtdcTradeField *pTrade) {};

	///Order Return Object
	virtual void OnRtnOrder(CApexFtdcOrderField *pOrder) {};

	///Execution Order Return Object
	virtual void OnRtnExecOrder(CApexFtdcExecOrderField *pExecOrder) {};

	///Quote Return Object
	virtual void OnRtnQuote(CApexFtdcQuoteField *pQuote) {};

	///Combined Order Return Object
	virtual void OnRtnCombOrder(CApexFtdcCombOrderField *pCombOrder) {};

	///Instrument Status Return Object
	virtual void OnRtnInstrumentStatus(CApexFtdcInstrumentStatusField *pInstrumentStatus) {};

	///Instrument Insertion Return Object
	virtual void OnRtnInsInstrument(CApexFtdcInstrumentField *pInstrument) {};

	///Instrument Deletion Return Object
	virtual void OnRtnDelInstrument(CApexFtdcInstrumentField *pInstrument) {};

	///Combined Instrument Leg Insertion Return Object
	virtual void OnRtnInsCombinationLeg(CApexFtdcCombinationLegField *pCombinationLeg) {};

	///Combined Instrument Leg Deletion Return Object
	virtual void OnRtnDelCombinationLeg(CApexFtdcCombinationLegField *pCombinationLeg) {};

	///Alias Definition Return Object
	virtual void OnRtnAliasDefine(CApexFtdcAliasDefineField *pAliasDefine) {};

	///Flow Message Cancellation Return Object
	virtual void OnRtnFlowMessageCancel(CApexFtdcFlowMessageCancelField *pFlowMessageCancel) {};

	///Bulletin Return Object
	virtual void OnRtnBulletin(CApexFtdcBulletinField *pBulletin) {};

	///Order Insertion Error Return Object
	virtual void OnErrRtnOrderInsert(CApexFtdcInputOrderField *pInputOrder, CApexFtdcRspInfoField *pRspInfo) {};

	///Order Action Error Return Object
	virtual void OnErrRtnOrderAction(CApexFtdcOrderActionField *pOrderAction, CApexFtdcRspInfoField *pRspInfo) {};

	///Quote Insertion Error Return Object
	virtual void OnErrRtnQuoteInsert(CApexFtdcInputQuoteField *pInputQuote, CApexFtdcRspInfoField *pRspInfo) {};

	///Quote Action Error Return Object
	virtual void OnErrRtnQuoteAction(CApexFtdcQuoteActionField *pQuoteAction, CApexFtdcRspInfoField *pRspInfo) {};

	///Execution Order Insertion Error Return Object
	virtual void OnErrRtnExecOrderInsert(CApexFtdcInputExecOrderField *pInputExecOrder, CApexFtdcRspInfoField *pRspInfo) {};

	///Execution Order Action Error Return Object
	virtual void OnErrRtnExecOrderAction(CApexFtdcExecOrderActionField *pExecOrderAction, CApexFtdcRspInfoField *pRspInfo) {};

	///Combined Order Insertion Error Return Object
	virtual void OnErrRtnCombOrderInsert(CApexFtdcInputCombOrderField *pInputCombOrder, CApexFtdcRspInfoField *pRspInfo) {};

	///Quote Response
	virtual void OnRspForQuote(CApexFtdcInputReqForQuoteField *pInputReqForQuote, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Request For Quote Return Object
	virtual void OnRtnForQuote(CApexFtdcInputReqForQuoteField *pInputReqForQuote) {};
};

class TRADER_API_EXPORT CApexFtdcTraderApi
{
public:
	///Create TraderApi
	///@param pszFlowPath: Directory to store subscription file. Default to current direction
	///@return API Instance created
	static CApexFtdcTraderApi *CreateFtdcTraderApi(const char *pszFlowPath = "");
	
	///Obtain System Version
	///@param nMajorVersion
	///@param nMinorVersion
	///@return System Identification String
	static const char *GetVersion();
	
	///Release API instance
	///@remark Use this function to release API instance after usage
	virtual void Release() = 0;
	
	///Initialization Function
	///@remark Launch an API thread to connect to server, API starts working upon invokation of this function
	virtual void Init() = 0;
	
	///Join Current Thread to API Thread
	///@return Thread exit code
	virtual int Join() = 0;
	
	///Obtain System Trading Day
	///@retrun: Trading day obtained
	///@remark Only works after login
	virtual const char *GetTradingDay() = 0;
	
	///Register Front-End
	///@param pszFrontAddress¡êoNetwork address of trading front
	///@remark Format of address being: "protocol://ipaddress:port", for e.g. "tcp://127.0.0.1:17001" 
	///@remark "tcp" represents transportation protocal, "127.0.0.1" represents server address, "17001" represents port number
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	//Register Front-End against Nameserver
	///@param pszNsAddress¡êoNetwork address of nameserver
	///@remark Format of address being¡êo"protocol://ipaddress:port", for e.g. "tcp://ns1.example.com:17001" 
	///@remark "tcp" represents transportation protocal, "ns1.example.com" represents server address, "17001" represents port number
	///@remark RegisterFront has priority over RegisterNameServer
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	///Register Service Provider Interface
	///@param pSpi: Pointer against an instance inherited from SPI
	virtual void RegisterSpi(CApexFtdcTraderSpi *pSpi) = 0;
	
	///Register Certificate
	///@param pszCertFileName: Certificate filename
	///@param pszKeyFileName: User private key filename
	///@param pszCaFileName: Trusted CA Certificate filename
	///@param pszKeyFilePassword: User private key file password
	///@return 0 Success
	///@return -1 Failed loading trusted CA certificate file
	///@return -2 Failed loading user certificate
	///@return -3 Failed loading user private key file
	///@return -4 User certificate authentication failure
	virtual int RegisterCertificateFile(const char *pszCertFileName, const char *pszKeyFileName, 
		const char *pszCaFileName, const char *pszKeyFilePassword) = 0;

	///Subscribe Private Topic
	///@param nResumeType: Topic resending type  
	///        APEX_TERT_RESTART: Resend from beginning of day
	///        APEX_TERT_RESUME: Resend from last received mesage
	///        APEX_TERT_QUICK: Don't resend
	///@remark This function has to be invoked before "Init" function if you wish to receive messages from private topic
	virtual void SubscribePrivateTopic(APEX_TE_RESUME_TYPE nResumeType) = 0;
	
	///Subscribe Public Topic
	///@param nResumeType: Topic resending type   
	///        APEX_TERT_RESTART: Resend from beginning of day
	///        APEX_TERT_RESUME: Resend from last received mesage
	///        APEX_TERT_QUICK: Don't resend
	///@remark This function has to be invoked before "Init" function if you wish to receive messages from public topic
	virtual void SubscribePublicTopic(APEX_TE_RESUME_TYPE nResumeType) = 0;

	///Subscribe User Topic
	///@param nResumeType: Topic resending type
	///        APEX_TERT_RESTART: Resend from beginning of day
	///        APEX_TERT_RESUME: Resend from last received mesage
	///        APEX_TERT_QUICK: Don't resend
	///@remark This function has to be invoked before "Init" function if you wish to receive messages from user topic
	virtual void SubscribeUserTopic(APEX_TE_RESUME_TYPE nResumeType) = 0;
	
	///Set Heartbeat Timeout
	///@param timeout: Heartbeat timeout (Second)  
	virtual void SetHeartbeatTimeout(unsigned int timeout) = 0;
	
	///Open Request Logfile
	///@param pszReqLogFileName: Request Log filename  
	///@return 0: Success
	///@return -1: Failed
	virtual int OpenRequestLog(const char *pszReqLogFileName) = 0;

	///Open Response Logfile
	///@param pszRspLogFileName: Response Log filename  
	///@return 0: Success
	///@return -1: Failed
	virtual int OpenResponseLog(const char *pszRspLogFileName) = 0;
	
	///Subscribe Quote Topic
	///@param nResumeType: Topic resending type  
	///        APEX_TERT_RESTART: Resend from beginning of day
	///        APEX_TERT_RESUME: Resend from last received mesage
	///        APEX_TERT_QUICK: Don't Resend
	///@remark This function has to be invoked before "Init" function if you wish to receive messages from quote topic
	virtual void SubscribeForQuote(APEX_TE_RESUME_TYPE nResumeType) = 0;


	///User Login Request
	virtual int ReqUserLogin(CApexFtdcReqUserLoginField *pReqUserLogin, int nRequestID) = 0;

	///User Logout Request
	virtual int ReqUserLogout(CApexFtdcReqUserLogoutField *pReqUserLogout, int nRequestID) = 0;

	///Order Inserting Request
	virtual int ReqOrderInsert(CApexFtdcInputOrderField *pInputOrder, int nRequestID) = 0;

	///Order Action Request
	virtual int ReqOrderAction(CApexFtdcOrderActionField *pOrderAction, int nRequestID) = 0;

	///Quote Inserting Request
	virtual int ReqQuoteInsert(CApexFtdcInputQuoteField *pInputQuote, int nRequestID) = 0;

	///Quote Action Request
	virtual int ReqQuoteAction(CApexFtdcQuoteActionField *pQuoteAction, int nRequestID) = 0;

	///User Password Update Request
	virtual int ReqUserPasswordUpdate(CApexFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) = 0;

	///Execution Order Inserting Request
	virtual int ReqExecOrderInsert(CApexFtdcInputExecOrderField *pInputExecOrder, int nRequestID) = 0;

	///Execution Order Action Request
	virtual int ReqExecOrderAction(CApexFtdcExecOrderActionField *pExecOrderAction, int nRequestID) = 0;

	///Admin Order Inserting Request
	virtual int ReqAdminOrderInsert(CApexFtdcInputAdminOrderField *pInputAdminOrder, int nRequestID) = 0;

	///Combined Order Inserting Request
	virtual int ReqCombOrderInsert(CApexFtdcInputCombOrderField *pInputCombOrder, int nRequestID) = 0;

	///Topic Subscription Request
	virtual int ReqSubscribeTopic(CApexFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///Participant Account Query Request
	virtual int ReqQryPartAccount(CApexFtdcQryPartAccountField *pQryPartAccount, int nRequestID) = 0;

	///Order Query Request
	virtual int ReqQryOrder(CApexFtdcQryOrderField *pQryOrder, int nRequestID) = 0;

	///Quote Query Request
	virtual int ReqQryQuote(CApexFtdcQryQuoteField *pQryQuote, int nRequestID) = 0;

	///Trade Query Request
	virtual int ReqQryTrade(CApexFtdcQryTradeField *pQryTrade, int nRequestID) = 0;

	///Client Query Request
	virtual int ReqQryClient(CApexFtdcQryClientField *pQryClient, int nRequestID) = 0;

	///Participant Position Query Request
	virtual int ReqQryPartPosition(CApexFtdcQryPartPositionField *pQryPartPosition, int nRequestID) = 0;

	///Client Position Query Request
	virtual int ReqQryClientPosition(CApexFtdcQryClientPositionField *pQryClientPosition, int nRequestID) = 0;

	///Instrument Query Request
	virtual int ReqQryInstrument(CApexFtdcQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///Instrument Status Query Request
	virtual int ReqQryInstrumentStatus(CApexFtdcQryInstrumentStatusField *pQryInstrumentStatus, int nRequestID) = 0;

	///Hedge Volumn Query Request
	virtual int ReqQryHedgeVolume(CApexFtdcQryHedgeVolumeField *pQryHedgeVolume, int nRequestID) = 0;

	///Credit Limit Query Request
	virtual int ReqQryCreditLimit(CApexFtdcQryCreditLimitField *pQryCreditLimit, int nRequestID) = 0;

	///Combined Order Query Request
	virtual int ReqQryCombOrder(CApexFtdcQryCombOrderField *pQryCombOrder, int nRequestID) = 0;

	///Ordinary Market Data Query Request
	virtual int ReqQryMarketData(CApexFtdcQryMarketDataField *pQryMarketData, int nRequestID) = 0;

	///Bulletin Query Request
	virtual int ReqQryBulletin(CApexFtdcQryBulletinField *pQryBulletin, int nRequestID) = 0;

	///Topic Query Request
	virtual int ReqQryTopic(CApexFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///Pending Order Breakdown List Query Request
	virtual int ReqQryMBLMarketData(CApexFtdcQryMBLMarketDataField *pQryMBLMarketData, int nRequestID) = 0;

	///Request for Quote
	virtual int ReqForQuote(CApexFtdcInputReqForQuoteField *pInputReqForQuote, int nRequestID) = 0;
protected:
	~CApexFtdcTraderApi(){};
};

#endif
