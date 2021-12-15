/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file QTestFtdcTraderApi.h
///@brief �����˿ͻ��˽ӿ�
///@history
///20150520	���һ�	�������ļ�
/////////////////////////////////////////////////////////////////////////

#if !defined(QTEST_FTDCTRADERAPI_H)
#define QTEST_FTDCTRADERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QTestFtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport)
#else
#define TRADER_API_EXPORT __declspec(dllimport)
#endif
#else
#define TRADER_API_EXPORT 
#endif

class CQTestFtdcTraderSpi
{
public:
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected(){};
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason){};
		
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse){};
	
	///���Ļص���ʼ֪ͨ����API�յ�һ�����ĺ����ȵ��ñ�������Ȼ���Ǹ�������Ļص�������Ǳ��Ļص�����֪ͨ��
	///@param nTopicID ������루��˽���������������������ȣ�
	///@param nSequenceNo �������
	virtual void OnPackageStart(int nTopicID, int nSequenceNo){};
	
	///���Ļص�����֪ͨ����API�յ�һ�����ĺ����ȵ��ñ��Ļص���ʼ֪ͨ��Ȼ���Ǹ�������Ļص��������ñ�������
	///@param nTopicID ������루��˽���������������������ȣ�
	///@param nSequenceNo �������
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo){};


	///����Ӧ��
	virtual void OnRspError(CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�û���¼Ӧ��
	virtual void OnRspUserLogin(CQTestFtdcRspUserLoginField *pRspUserLogin, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�û��˳�Ӧ��
	virtual void OnRspUserLogout(CQTestFtdcRspUserLogoutField *pRspUserLogout, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����¼��Ӧ��
	virtual void OnRspOrderInsert(CQTestFtdcInputOrderField *pInputOrder, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������Ӧ��
	virtual void OnRspOrderAction(CQTestFtdcOrderActionField *pOrderAction, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����¼��Ӧ��
	virtual void OnRspQuoteInsert(CQTestFtdcInputQuoteField *pInputQuote, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///���۲���Ӧ��
	virtual void OnRspQuoteAction(CQTestFtdcQuoteActionField *pQuoteAction, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�û������޸�Ӧ��
	virtual void OnRspUserPasswordUpdate(CQTestFtdcUserPasswordUpdateField *pUserPasswordUpdate, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///ִ������¼��Ӧ��
	virtual void OnRspExecOrderInsert(CQTestFtdcInputExecOrderField *pInputExecOrder, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///ִ���������Ӧ��
	virtual void OnRspExecOrderAction(CQTestFtdcExecOrderActionField *pExecOrderAction, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///������¼��Ӧ��
	virtual void OnRspAdminOrderInsert(CQTestFtdcInputAdminOrderField *pInputAdminOrder, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�Ǳ���ϱ���¼��Ӧ��
	virtual void OnRspCombOrderInsert(CQTestFtdcInputCombOrderField *pInputCombOrder, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������Ӧ��
	virtual void OnRspSubscribeTopic(CQTestFtdcDisseminationField *pDissemination, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Ա�ʽ��ѯӦ��
	virtual void OnRspQryPartAccount(CQTestFtdcRspPartAccountField *pRspPartAccount, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///������ѯӦ��
	virtual void OnRspQryOrder(CQTestFtdcOrderField *pOrder, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///���۲�ѯӦ��
	virtual void OnRspQryQuote(CQTestFtdcQuoteField *pQuote, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ɽ�����ѯӦ��
	virtual void OnRspQryTrade(CQTestFtdcTradeField *pTrade, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Ա�ͻ���ѯӦ��
	virtual void OnRspQryClient(CQTestFtdcRspClientField *pRspClient, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Ա�ֲֲ�ѯӦ��
	virtual void OnRspQryPartPosition(CQTestFtdcRspPartPositionField *pRspPartPosition, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ͻ��ֲֲ�ѯӦ��
	virtual void OnRspQryClientPosition(CQTestFtdcRspClientPositionField *pRspClientPosition, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Լ��ѯӦ��
	virtual void OnRspQryInstrument(CQTestFtdcRspInstrumentField *pRspInstrument, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Լ����״̬��ѯӦ��
	virtual void OnRspQryInstrumentStatus(CQTestFtdcInstrumentStatusField *pInstrumentStatus, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��ֵ���Ӧ��
	virtual void OnRspQryHedgeVolume(CQTestFtdcHedgeVolumeField *pHedgeVolume, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����޶��ѯӦ��
	virtual void OnRspQryCreditLimit(CQTestFtdcCreditLimitField *pCreditLimit, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�Ǳ���ϱ�����ѯӦ��
	virtual void OnRspQryCombOrder(CQTestFtdcCombOrderField *pCombOrder, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��ͨ�����ѯӦ��
	virtual void OnRspQryMarketData(CQTestFtdcMarketDataField *pMarketData, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����������ѯ����Ӧ��
	virtual void OnRspQryBulletin(CQTestFtdcBulletinField *pBulletin, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯӦ��
	virtual void OnRspQryTopic(CQTestFtdcDisseminationField *pDissemination, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Լ��λ��ѯӦ��
	virtual void OnRspQryMBLMarketData(CQTestFtdcMBLMarketDataField *pMBLMarketData, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ɽ��ر�
	virtual void OnRtnTrade(CQTestFtdcTradeField *pTrade) {};

	///�����ر�
	virtual void OnRtnOrder(CQTestFtdcOrderField *pOrder) {};

	///ִ������ر�
	virtual void OnRtnExecOrder(CQTestFtdcExecOrderField *pExecOrder) {};

	///���ۻر�
	virtual void OnRtnQuote(CQTestFtdcQuoteField *pQuote) {};

	///�Ǳ���ϱ����ر�
	virtual void OnRtnCombOrder(CQTestFtdcCombOrderField *pCombOrder) {};

	///��Լ����״̬֪ͨ
	virtual void OnRtnInstrumentStatus(CQTestFtdcInstrumentStatusField *pInstrumentStatus) {};

	///���Ӻ�Լ֪ͨ
	virtual void OnRtnInsInstrument(CQTestFtdcInstrumentField *pInstrument) {};

	///ɾ����Լ֪ͨ
	virtual void OnRtnDelInstrument(CQTestFtdcInstrumentField *pInstrument) {};

	///���Ӻ�Լ����֪ͨ
	virtual void OnRtnInsCombinationLeg(CQTestFtdcCombinationLegField *pCombinationLeg) {};

	///ɾ����Լ����֪ͨ
	virtual void OnRtnDelCombinationLeg(CQTestFtdcCombinationLegField *pCombinationLeg) {};

	///��������֪ͨ
	virtual void OnRtnAliasDefine(CQTestFtdcAliasDefineField *pAliasDefine) {};

	///����������֪ͨ
	virtual void OnRtnFlowMessageCancel(CQTestFtdcFlowMessageCancelField *pFlowMessageCancel) {};

	///����֪ͨ
	virtual void OnRtnBulletin(CQTestFtdcBulletinField *pBulletin) {};

	///����¼�����ر�
	virtual void OnErrRtnOrderInsert(CQTestFtdcInputOrderField *pInputOrder, CQTestFtdcRspInfoField *pRspInfo) {};

	///������������ر�
	virtual void OnErrRtnOrderAction(CQTestFtdcOrderActionField *pOrderAction, CQTestFtdcRspInfoField *pRspInfo) {};

	///����¼�����ر�
	virtual void OnErrRtnQuoteInsert(CQTestFtdcInputQuoteField *pInputQuote, CQTestFtdcRspInfoField *pRspInfo) {};

	///���۲�������ر�
	virtual void OnErrRtnQuoteAction(CQTestFtdcQuoteActionField *pQuoteAction, CQTestFtdcRspInfoField *pRspInfo) {};

	///ִ������¼�����ر�
	virtual void OnErrRtnExecOrderInsert(CQTestFtdcInputExecOrderField *pInputExecOrder, CQTestFtdcRspInfoField *pRspInfo) {};

	///ִ�������������ر�
	virtual void OnErrRtnExecOrderAction(CQTestFtdcExecOrderActionField *pExecOrderAction, CQTestFtdcRspInfoField *pRspInfo) {};

	///�Ǳ���ϱ���¼�����ر�
	virtual void OnErrRtnCombOrderInsert(CQTestFtdcInputCombOrderField *pInputCombOrder, CQTestFtdcRspInfoField *pRspInfo) {};

	///ѯ��Ӧ��
	virtual void OnRspForQuote(CQTestFtdcInputReqForQuoteField *pInputReqForQuote, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///ѯ��֪ͨ
	virtual void OnRtnForQuote(CQTestFtdcInputReqForQuoteField *pInputReqForQuote) {};
};

class TRADER_API_EXPORT CQTestFtdcTraderApi
{
public:
	///����TraderApi
	///@param pszFlowPath ����������Ϣ�ļ���Ŀ¼��Ĭ��Ϊ��ǰĿ¼
	///@return ��������UserApi
	static CQTestFtdcTraderApi *CreateFtdcTraderApi(const char *pszFlowPath = "");
	
	///��ȡϵͳ�汾��
	///@param nMajorVersion ���汾��
	///@param nMinorVersion �Ӱ汾��
	///@return ϵͳ��ʶ�ַ���
	static const char *GetVersion();
	
	///ɾ���ӿڶ�����
	///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	virtual void Release() = 0;
	
	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	virtual void Init() = 0;
	
	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	virtual int Join() = 0;
	
	///��ȡ��ǰ������
	///@retrun ��ȡ���Ľ�����
	///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
	virtual const char *GetTradingDay() = 0;
	
	///ע��ǰ�û������ַ
	///@param pszFrontAddress��ǰ�û������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///ע�����ַ����������ַ
	///@param pszNsAddress�����ַ����������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
	///@remark RegisterFront������RegisterNameServer
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	///ע��ص��ӿ�
	///@param pSpi �����Իص��ӿ����ʵ��
	virtual void RegisterSpi(CQTestFtdcTraderSpi *pSpi) = 0;
	
	///����֤��
	///@param pszCertFileName �û�֤���ļ���
	///@param pszKeyFileName �û�˽Կ�ļ���
	///@param pszCaFileName ������CA֤���ļ���
	///@param pszKeyFilePassword �û�˽Կ�ļ�����
	///@return 0 �����ɹ�
	///@return -1 ������CA֤������ʧ��
	///@return -2 �û�֤������ʧ��
	///@return -3 �û�˽Կ����ʧ��	
	///@return -4 �û�֤��У��ʧ��
	virtual int RegisterCertificateFile(const char *pszCertFileName, const char *pszKeyFileName, 
		const char *pszCaFileName, const char *pszKeyFilePassword) = 0;

	///����˽������
	///@param nResumeType ˽�����ش���ʽ  
	///        QTEST_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        QTEST_TERT_RESUME:���ϴ��յ�������
	///        QTEST_TERT_QUICK:ֻ���͵�¼��˽����������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�˽���������ݡ�
	virtual void SubscribePrivateTopic(QTEST_TE_RESUME_TYPE nResumeType) = 0;
	
	///���Ĺ�������
	///@param nResumeType �������ش���ʽ  
	///        QTEST_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        QTEST_TERT_RESUME:���ϴ��յ�������
	///        QTEST_TERT_QUICK:ֻ���͵�¼�󹫹���������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ������������ݡ�
	virtual void SubscribePublicTopic(QTEST_TE_RESUME_TYPE nResumeType) = 0;

	///���Ľ���Ա����
	///@param nResumeType ����Ա���ش���ʽ  
	///        QTEST_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        QTEST_TERT_RESUME:���ϴ��յ�������
	///        QTEST_TERT_QUICK:ֻ���͵�¼����Ա��������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�����Ա�������ݡ�
	virtual void SubscribeUserTopic(QTEST_TE_RESUME_TYPE nResumeType) = 0;
	
	///����������ʱʱ�䡣
	///@param timeout ������ʱʱ��(��)  
	virtual void SetHeartbeatTimeout(unsigned int timeout) = 0;
	
	///��������־�ļ�
	///@param pszReqLogFileName ������־�ļ���  
	///@return 0 �����ɹ�
	///@return -1 ����־�ļ�ʧ��
	virtual int OpenRequestLog(const char *pszReqLogFileName) = 0;

	///��Ӧ����־�ļ�
	///@param pszRspLogFileName Ӧ����־�ļ���  
	///@return 0 �����ɹ�
	///@return -1 ����־�ļ�ʧ��
	virtual int OpenResponseLog(const char *pszRspLogFileName) = 0;
	
	///����ѯ������
	///@param nResumeType ѯ�����ش���ʽ  
	///        TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        TERT_RESUME:���ϴ��յ�������
	///        TERT_QUICK:ֻ���͵�¼��ѯ����������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�ѯ���������ݡ�
	virtual void SubscribeForQuote(QTEST_TE_RESUME_TYPE nResumeType) = 0;


	///�û���¼����
	virtual int ReqUserLogin(CQTestFtdcReqUserLoginField *pReqUserLogin, int nRequestID) = 0;

	///�û��˳�����
	virtual int ReqUserLogout(CQTestFtdcReqUserLogoutField *pReqUserLogout, int nRequestID) = 0;

	///����¼������
	virtual int ReqOrderInsert(CQTestFtdcInputOrderField *pInputOrder, int nRequestID) = 0;

	///������������
	virtual int ReqOrderAction(CQTestFtdcOrderActionField *pOrderAction, int nRequestID) = 0;

	///����¼������
	virtual int ReqQuoteInsert(CQTestFtdcInputQuoteField *pInputQuote, int nRequestID) = 0;

	///���۲�������
	virtual int ReqQuoteAction(CQTestFtdcQuoteActionField *pQuoteAction, int nRequestID) = 0;

	///�û������޸�����
	virtual int ReqUserPasswordUpdate(CQTestFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) = 0;

	///ִ������¼������
	virtual int ReqExecOrderInsert(CQTestFtdcInputExecOrderField *pInputExecOrder, int nRequestID) = 0;

	///ִ�������������
	virtual int ReqExecOrderAction(CQTestFtdcExecOrderActionField *pExecOrderAction, int nRequestID) = 0;

	///������¼������
	virtual int ReqAdminOrderInsert(CQTestFtdcInputAdminOrderField *pInputAdminOrder, int nRequestID) = 0;

	///�Ǳ���ϱ���¼������
	virtual int ReqCombOrderInsert(CQTestFtdcInputCombOrderField *pInputCombOrder, int nRequestID) = 0;

	///������������
	virtual int ReqSubscribeTopic(CQTestFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///��Ա�ʽ��ѯ����
	virtual int ReqQryPartAccount(CQTestFtdcQryPartAccountField *pQryPartAccount, int nRequestID) = 0;

	///������ѯ����
	virtual int ReqQryOrder(CQTestFtdcQryOrderField *pQryOrder, int nRequestID) = 0;

	///���۲�ѯ����
	virtual int ReqQryQuote(CQTestFtdcQryQuoteField *pQryQuote, int nRequestID) = 0;

	///�ɽ�����ѯ����
	virtual int ReqQryTrade(CQTestFtdcQryTradeField *pQryTrade, int nRequestID) = 0;

	///��Ա�ͻ���ѯ����
	virtual int ReqQryClient(CQTestFtdcQryClientField *pQryClient, int nRequestID) = 0;

	///��Ա�ֲֲ�ѯ����
	virtual int ReqQryPartPosition(CQTestFtdcQryPartPositionField *pQryPartPosition, int nRequestID) = 0;

	///�ͻ��ֲֲ�ѯ����
	virtual int ReqQryClientPosition(CQTestFtdcQryClientPositionField *pQryClientPosition, int nRequestID) = 0;

	///��Լ��ѯ����
	virtual int ReqQryInstrument(CQTestFtdcQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///��Լ����״̬��ѯ����
	virtual int ReqQryInstrumentStatus(CQTestFtdcQryInstrumentStatusField *pQryInstrumentStatus, int nRequestID) = 0;

	///��ֵ��Ȳ�ѯ
	virtual int ReqQryHedgeVolume(CQTestFtdcQryHedgeVolumeField *pQryHedgeVolume, int nRequestID) = 0;

	///�����޶��ѯ����
	virtual int ReqQryCreditLimit(CQTestFtdcQryCreditLimitField *pQryCreditLimit, int nRequestID) = 0;

	///�Ǳ���ϱ�����ѯ����
	virtual int ReqQryCombOrder(CQTestFtdcQryCombOrderField *pQryCombOrder, int nRequestID) = 0;

	///��ͨ�����ѯ����
	virtual int ReqQryMarketData(CQTestFtdcQryMarketDataField *pQryMarketData, int nRequestID) = 0;

	///�����������ѯ����
	virtual int ReqQryBulletin(CQTestFtdcQryBulletinField *pQryBulletin, int nRequestID) = 0;

	///�����ѯ����
	virtual int ReqQryTopic(CQTestFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///��Լ��λ��ѯ
	virtual int ReqQryMBLMarketData(CQTestFtdcQryMBLMarketDataField *pQryMBLMarketData, int nRequestID) = 0;

	///ѯ������
	virtual int ReqForQuote(CQTestFtdcInputReqForQuoteField *pInputReqForQuote, int nRequestID) = 0;
protected:
	~CQTestFtdcTraderApi(){};
};

#endif
