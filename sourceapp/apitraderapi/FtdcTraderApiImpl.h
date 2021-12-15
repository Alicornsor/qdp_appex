/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file QdpFtdcTraderApiImpl.h
///@brief �����˿ͻ��˽ӿ�ʵ��
///@history 
///20150522	���һ�		�������ļ�
/////////////////////////////////////////////////////////////////////////

#if !defined(_FTDCTRADERAPIIMPL_H)
#define _FTDCTRADERAPIIMPL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QdpFtdcUserApi.h"
#include "QdpFtdcTraderApi.h"


///����API�ӿ�ʵ��
class CFtdcTraderApiImpl : public CQdpFtdcTraderApi, public CQdpFtdcUserSpi
{
public:	
	///���캯��
	CFtdcTraderApiImpl(const char *pszFlowPath);

	///ɾ���ӿڶ�����
	///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	virtual void Release();
	
	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	virtual void Init();
	
	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	virtual int Join();
	
	///��ȡ��ǰ������
	///@retrun ��ȡ���Ľ�����
	///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
	virtual const char *GetTradingDay();
	
	///ע��ǰ�û������ַ
	///@param pszFrontAddress��ǰ�û������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
	virtual void RegisterFront(char *pszFrontAddress);
	
	///ע�����ַ����������ַ
	///@param pszNsAddress�����ַ����������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
	///@remark RegisterFront������RegisterNameServer
	virtual void RegisterNameServer(char *pszNsAddress);
	
	///ע��ص��ӿ�
	///@param pSpi �����Իص��ӿ����ʵ��
	virtual void RegisterSpi(CQdpFtdcTraderSpi *pSpi);
	
	///����˽������
	///@param nResumeType ˽�����ش���ʽ  
	///        QDP_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        QDP_TERT_RESUME:���ϴ��յ�������
	///        QDP_TERT_QUICK:ֻ���͵�¼��˽����������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�˽���������ݡ�
	virtual void SubscribePrivateTopic(QDP_TE_RESUME_TYPE nResumeType);
	
	///���Ĺ�������
	///@param nResumeType �������ش���ʽ  
	///        QDP_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        QDP_TERT_RESUME:���ϴ��յ�������
	///        QDP_TERT_QUICK:ֻ���͵�¼�󹫹���������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ������������ݡ�
	virtual void SubscribePublicTopic(QDP_TE_RESUME_TYPE nResumeType);

	///���Ľ���Ա����
	///@param nResumeType ����Ա���ش���ʽ  
	///        QDP_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        QDP_TERT_RESUME:���ϴ��յ�������
	///        QDP_TERT_QUICK:ֻ���͵�¼����Ա��������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�����Ա�������ݡ�
	virtual void SubscribeUserTopic(QDP_TE_RESUME_TYPE nResumeType);

	///����������ʱʱ�䡣
	///@param timeout ������ʱʱ��(��)  
	virtual void SetHeartbeatTimeout(unsigned int timeout);
	
	///��������־�ļ�
	///@param pszReqLogFileName ������־�ļ���  
	///@return 0 �����ɹ�
	///@return -1 ����־�ļ�ʧ��
	virtual int OpenRequestLog(const char *pszReqLogFileName);

	///��Ӧ����־�ļ�
	///@param pszRspLogFileName Ӧ����־�ļ���  
	///@return 0 �����ɹ�
	///@return -1 ����־�ļ�ʧ��
	virtual int OpenResponseLog(const char *pszRspLogFileName);


	///�û���¼����
	virtual int ReqUserLogin(CQdpFtdcReqUserLoginField *pReqUserLogin, int nRequestID);

	///�û��˳�����
	virtual int ReqUserLogout(CQdpFtdcReqUserLogoutField *pReqUserLogout, int nRequestID);

	///�û������޸�����
	virtual int ReqUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID);

	///����¼������
	virtual int ReqOrderInsert(CQdpFtdcInputOrderField *pInputOrder, int nRequestID);

	///������������
	virtual int ReqOrderAction(CQdpFtdcOrderActionField *pOrderAction, int nRequestID);

	///������ѯ����
	virtual int ReqQryOrder(CQdpFtdcQryOrderField *pQryOrder, int nRequestID);

	///�ɽ�����ѯ����
	virtual int ReqQryTrade(CQdpFtdcQryTradeField *pQryTrade, int nRequestID);

	///����Ͷ�����˻���ѯ����
	virtual int ReqQryUserInvestor(CQdpFtdcQryUserInvestorField *pQryUserInvestor, int nRequestID);

	///Ͷ�����ʽ��˻���ѯ����
	virtual int ReqQryInvestorAccount(CQdpFtdcQryInvestorAccountField *pQryInvestorAccount, int nRequestID);

	///��Լ��ѯ����
	virtual int ReqQryInstrument(CQdpFtdcQryInstrumentField *pQryInstrument, int nRequestID);

	///��������ѯ����
	virtual int ReqQryExchange(CQdpFtdcQryExchangeField *pQryExchange, int nRequestID);

	///Ͷ���ֲֲ߳�ѯ����
	virtual int ReqQryInvestorPosition(CQdpFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID);

	///������������
	virtual int ReqSubscribeTopic(CQdpFtdcDisseminationField *pDissemination, int nRequestID);

	///�����ѯ����
	virtual int ReqQryTopic(CQdpFtdcDisseminationField *pDissemination, int nRequestID);

	///Ͷ�����������ʲ�ѯ����
	virtual int ReqQryInvestorFee(CQdpFtdcQryInvestorFeeField *pQryInvestorFee, int nRequestID);

	///Ͷ���߱�֤���ʲ�ѯ����
	virtual int ReqQryInvestorMargin(CQdpFtdcQryInvestorMarginField *pQryInvestorMargin, int nRequestID);

	///�������ӷ��ʲ�ѯ����
	virtual int ReqQrySGEDeferRate(CQdpFtdcQrySGEDeferRateField *pQrySGEDeferRate, int nRequestID);

	///Ͷ������Ȩ�������ʲ�ѯ����
	virtual int ReqQryInvestorOptionFee(CQdpFtdcQryInvestorOptionFeeField *pQryInvestorOptionFee, int nRequestID);

	///ʵʱ�����ѯ����
	virtual int ReqQryMarketData(CQdpFtdcQryMarketDataField *pQryMarketData, int nRequestID);
private:
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason);
		
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///���Ļص���ʼ֪ͨ����API�յ�һ�����ĺ����ȵ��ñ�������Ȼ���Ǹ�������Ļص�������Ǳ��Ļص�����֪ͨ��
	///@param nTopicID ������루��˽���������������������ȣ�
	///@param nSequenceNo �������
	virtual void OnPackageStart(int nTopicID, int nSequenceNo);
	
	///���Ļص�����֪ͨ����API�յ�һ�����ĺ����ȵ��ñ��Ļص���ʼ֪ͨ��Ȼ���Ǹ�������Ļص��������ñ�������
	///@param nTopicID ������루��˽���������������������ȣ�
	///@param nSequenceNo �������
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo);
	

	///����Ӧ��
	virtual void OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�û���¼Ӧ��
	virtual void OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�û��˳�Ӧ��
	virtual void OnRspUserLogout(CQdpFtdcRspUserLogoutField *pRspUserLogout, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�û������޸�Ӧ��
	virtual void OnRspUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����¼��Ӧ��
	virtual void OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������Ӧ��
	virtual void OnRspOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����������֪ͨ
	virtual void OnRtnFlowMessageCancel(CQdpFtdcFlowMessageCancelField *pFlowMessageCancel);

	///�ɽ��ر�
	virtual void OnRtnTrade(CQdpFtdcTradeField *pTrade);

	///�����ر�
	virtual void OnRtnOrder(CQdpFtdcOrderField *pOrder);

	///����¼�����ر�
	virtual void OnErrRtnOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo);

	///������������ر�
	virtual void OnErrRtnOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo);

	///��Լ����״̬֪ͨ
	virtual void OnRtnInstrumentStatus(CQdpFtdcInstrumentStatusField *pInstrumentStatus);

	///�˻������ر�
	virtual void OnRtnInvestorAccountDeposit(CQdpFtdcInvestorAccountDepositResField *pInvestorAccountDepositRes);

	///QDP������Ϣ֪ͨ
	virtual void OnRtnMessageNotify(CQdpFtdcMessageNotifyInfoField *pMessageNotifyInfo);

	///�������ӷ���֪ͨ
	virtual void OnRtnSGEDeferRate(CQdpFtdcSGEDeferRateField *pSGEDeferRate);

	///������ѯӦ��
	virtual void OnRspQryOrder(CQdpFtdcOrderField *pOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�ɽ�����ѯӦ��
	virtual void OnRspQryTrade(CQdpFtdcTradeField *pTrade, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����Ͷ�����˻���ѯӦ��
	virtual void OnRspQryUserInvestor(CQdpFtdcRspUserInvestorField *pRspUserInvestor, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ�����ʽ��˻���ѯӦ��
	virtual void OnRspQryInvestorAccount(CQdpFtdcRspInvestorAccountField *pRspInvestorAccount, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��Լ��ѯӦ��
	virtual void OnRspQryInstrument(CQdpFtdcRspInstrumentField *pRspInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������ѯӦ��
	virtual void OnRspQryExchange(CQdpFtdcRspExchangeField *pRspExchange, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ���ֲֲ߳�ѯӦ��
	virtual void OnRspQryInvestorPosition(CQdpFtdcRspInvestorPositionField *pRspInvestorPosition, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������Ӧ��
	virtual void OnRspSubscribeTopic(CQdpFtdcDisseminationField *pDissemination, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯӦ��
	virtual void OnRspQryTopic(CQdpFtdcDisseminationField *pDissemination, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ�����������ʲ�ѯӦ��
	virtual void OnRspQryInvestorFee(CQdpFtdcInvestorFeeField *pInvestorFee, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ���߱�֤���ʲ�ѯӦ��
	virtual void OnRspQryInvestorMargin(CQdpFtdcInvestorMarginField *pInvestorMargin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�������ӷ��ʲ�ѯӦ��
	virtual void OnRspQrySGEDeferRate(CQdpFtdcSGEDeferRateField *pSGEDeferRate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ������Ȩ�������ʲ�ѯӦ��
	virtual void OnRspQryInvestorOptionFee(CQdpFtdcRspInvestorOptionFeeField *pRspInvestorOptionFee, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ʵʱ�����ѯӦ��
	virtual void OnRspQryMarketData(CQdpFtdcMarketDataField *pMarketData, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
private:
	CQdpFtdcUserApi *m_pUserApi;
	CQdpFtdcTraderSpi *m_pSpi;
};


#endif
