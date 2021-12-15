/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file QdpFtdcUserApiImpl.h
///@brief �����˿ͻ��˽ӿ�ʵ��
///@history 
///20150522 xuzh create
/////////////////////////////////////////////////////////////////////////

#if !defined(_FTDCUSERAPIIMPL_H)
#define _FTDCUSERAPIIMPL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FtdcUserApiImplBase.h"

class CFtdcUserApiImpl : public CFtdcUserApiImplBase
{
public:	
	CFtdcUserApiImpl(const char *pszFlowPath, const char *pszUserApiType, CReactor *pReactor);
	virtual void HandleResponse(CFTDCPackage *pMessage, WORD nSequenceSeries);

	///�û��˳�����
	virtual int ReqUserLogout(CQdpFtdcReqUserLogoutField *pReqUserLogout, int nRequestID);

	///�û������޸�����
	virtual int ReqUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID);

	///ǿ���û��˳�����
	virtual int ReqForceUserExit(CQdpFtdcForceUserExitField *pForceUserExit, int nRequestID);

	///�û��Ựɾ������
	virtual int ReqForceUserLogout(CQdpFtdcForceUserExitField *pForceUserExit, int nRequestID);

	///���󵼳��ڴ����ݿ�
	virtual int ReqDumpMemDb(CQdpFtdcMemDbField *pMemDb, int nRequestID);

	///����¼������
	virtual int ReqOrderInsert(CQdpFtdcInputOrderField *pInputOrder, int nRequestID);

	///������������
	virtual int ReqOrderAction(CQdpFtdcOrderActionField *pOrderAction, int nRequestID);

	///Ͷ�����ʽ��ʻ����������
	virtual int ReqAccountDeposit(CQdpFtdcReqAccountDepositField *pReqAccountDeposit, int nRequestID);

	///������ѯ����
	virtual int ReqQryOrder(CQdpFtdcQryOrderField *pQryOrder, int nRequestID);

	///�ɽ�����ѯ����
	virtual int ReqQryTrade(CQdpFtdcQryTradeField *pQryTrade, int nRequestID);

	///����Ͷ�����˻���ѯ����
	virtual int ReqQryUserInvestor(CQdpFtdcQryUserInvestorField *pQryUserInvestor, int nRequestID);

	///���ױ����ѯ����
	virtual int ReqQryTradingCode(CQdpFtdcQryTradingCodeField *pQryTradingCode, int nRequestID);

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

	///�û���ѯ����
	virtual int ReqQryUser(CQdpFtdcQryUserField *pQryUser, int nRequestID);

	///Ͷ�����������ʲ�ѯ����
	virtual int ReqQryInvestorFee(CQdpFtdcQryInvestorFeeField *pQryInvestorFee, int nRequestID);

	///Ͷ���߱�֤���ʲ�ѯ����
	virtual int ReqQryInvestorMargin(CQdpFtdcQryInvestorMarginField *pQryInvestorMargin, int nRequestID);

	///�������ӷ��ʲ�ѯ����
	virtual int ReqQrySGEDeferRate(CQdpFtdcQrySGEDeferRateField *pQrySGEDeferRate, int nRequestID);

	///�ֲ���ϸ��ѯ����
	virtual int ReqQryInvestorPositionDetail(CQdpFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID);

	///Ͷ������Ȩ�������ʲ�ѯ����
	virtual int ReqQryInvestorOptionFee(CQdpFtdcQryInvestorOptionFeeField *pQryInvestorOptionFee, int nRequestID);

	///Topic��ѯ
	virtual int ReqTopicSearch(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID);

	///���ĺ�Լ�������Ϣ
	virtual int ReqSubMarketData(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID);

	///�˶���Լ�������Ϣ
	virtual int ReqUnSubMarketData(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID);

	///ʵʱ�����ѯ����
	virtual int ReqQryMarketData(CQdpFtdcQryMarketDataField *pQryMarketData, int nRequestID);

	///�����ѯ����
	virtual int ReqQryDepthMarketData(CQdpFtdcQryMarketDataField *pQryMarketData, int nRequestID);

	///�ּ۱��ѯ����
	virtual int ReqQryMBLMarketData(CQdpFtdcQryMBLMarketDataField *pQryMBLMarketData, int nRequestID);
private:
	///����Ӧ��
	void OnRspError(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�û���¼Ӧ��
	void OnRspUserLogin(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�û��˳�Ӧ��
	void OnRspUserLogout(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�û������޸�Ӧ��
	void OnRspUserPasswordUpdate(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///ǿ���û��˳�Ӧ��
	void OnRspForceUserExit(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�û��Ựɾ��Ӧ��
	void OnRspForceUserLogout(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///����¼��Ӧ��
	void OnRspOrderInsert(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///��������Ӧ��
	void OnRspOrderAction(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///Ͷ�����ʽ��ʻ������Ӧ��
	void OnRspAccountDeposit(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///����������֪ͨ
	void OnRtnFlowMessageCancel(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�ɽ��ر�
	void OnRtnTrade(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�����ر�
	void OnRtnOrder(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///����¼�����ر�
	void OnErrRtnOrderInsert(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///������������ر�
	void OnErrRtnOrderAction(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///��Լ����״̬֪ͨ
	void OnRtnInstrumentStatus(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�˻������ر�
	void OnRtnInvestorAccountDeposit(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///QDP������Ϣ֪ͨ
	void OnRtnMessageNotify(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�������ӷ���֪ͨ
	void OnRtnSGEDeferRate(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///֣�ݺ�Լ״̬
	void OnRtnQmdInstrumentStatu(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///������ѯӦ��
	void OnRspQryOrder(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�ɽ�����ѯӦ��
	void OnRspQryTrade(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///����Ͷ�����˻���ѯӦ��
	void OnRspQryUserInvestor(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///���ױ����ѯӦ��
	void OnRspQryTradingCode(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///Ͷ�����ʽ��˻���ѯӦ��
	void OnRspQryInvestorAccount(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///��Լ��ѯӦ��
	void OnRspQryInstrument(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///��������ѯӦ��
	void OnRspQryExchange(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///Ͷ���ֲֲ߳�ѯӦ��
	void OnRspQryInvestorPosition(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///��������Ӧ��
	void OnRspSubscribeTopic(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�����ѯӦ��
	void OnRspQryTopic(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�û���ѯӦ��
	void OnRspQryUser(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///Ͷ�����������ʲ�ѯӦ��
	void OnRspQryInvestorFee(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///Ͷ���߱�֤���ʲ�ѯӦ��
	void OnRspQryInvestorMargin(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�������ӷ��ʲ�ѯӦ��
	void OnRspQrySGEDeferRate(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�ֲ���ϸ��ѯӦ��
	void OnRspQryInvestorPositionDetail(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///Ͷ������Ȩ�������ʲ�ѯӦ��
	void OnRspQryInvestorOptionFee(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�������֪ͨ
	void OnRtnDepthMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�������֪ͨ
	void OnRtnMultiDepthMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///���ĺ�Լ�������Ϣ
	void OnRspSubMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�˶���Լ�������Ϣ
	void OnRspUnSubMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///ʵʱ�����ѯӦ��
	void OnRspQryMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�����ѯӦ��
	void OnRspQryDepthMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
	///�ּ۱��ѯӦ��
	void OnRspQryMBLMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries);
	
};

#endif
