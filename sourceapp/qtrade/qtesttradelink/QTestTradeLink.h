// ����ϯλ����
///200150616 xuzh ���ǵ���������ѯ�����������е���ˮ֮ǰ��ʹ�ñ�ʶ������
///������ˮ��˳��qdata�ϳ���ˮ->��������ѯ��ˮ->������������ˮ

#ifndef __CQTESTTRADE_LINK_H
#define __CQTESTTRADE_LINK_H

#include "QTestFtdcTraderApi.h"
#include "QTestFtdcUserApiStruct.h"
#include "platform.h"
#include "BaseExchApi.h"
#include "XTPPackage.h"
#include "FlowReader.h"
#include "ExCachedFlow.h"



typedef map<int, string>  CQTestIpPoolMap;
typedef set<string> SetQTestClientID;//�ͻ�����

//����ϯλ�ӿ�
class CQTestTradeLink : public CQTestFtdcTraderSpi,public CBaseExchApi
{
public:
	CQTestTradeLink(char *pszFlowPath);
	~CQTestTradeLink();
	
	//����
	void OnFrontConnected();
	void OnFrontDisconnected(int nReason);
	//��¼
	void OnRspUserLogin(CQTestFtdcRspUserLoginField *pRspUserLogin, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspError(CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	//�����޸�Ӧ��
	void OnRspUserPasswordUpdate(CQTestFtdcUserPasswordUpdateField *pUserPasswordUpdate, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};
	
	//����
	void OnRspOrderInsert(CQTestFtdcInputOrderField *pInputOrder, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//����
	void OnRspOrderAction(CQTestFtdcOrderActionField *pOrderAction, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	//����֪ͨ
	void OnRtnOrder(CQTestFtdcOrderField *pOrder);
	//�ɽ�֪ͨ
	void OnRtnTrade(CQTestFtdcTradeField *pTrade);
	
	//��Լ����״̬֪ͨ
	void OnRtnInstrumentStatus(CQTestFtdcInstrumentStatusField *pInstrumentStatus);
	
	void StartWork();
	//�յ��û���Ϣ��
	void OnPackageStart(int nTopicID, int nSequenceNo);
	char *GetLocalID(const char *pClientID,char cEoFlag =0);
	
	void ReqContract(int reqTime=1);
	void ReqClientPosi(int reqTime=1);
	void ReqMarketData(int reqTime=1);
	///��Լ��ѯӦ��
	void OnRspQryInstrument(CQTestFtdcRspInstrumentField *pRspInstrument, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspQryClientPosition(CQTestFtdcRspClientPositionField *pRspClientPosition, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspQryMarketData(CQTestFtdcMarketDataField *pMarketData, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	void SetFensIp(const char *pIpFensIP);
	void SetFrontIp(const char *pIpFrontIP);
	///����������֪ͨ
	void OnRtnFlowMessageCancel(CQTestFtdcFlowMessageCancelField *pFlowMessageCancel);
	bool ClientIDExist(const char *pClientID);
	
	///����
	int ReqOrderInsert(CInputOrderField &Order);
	int ReqOrderInsert(CWriteablePreOrder &Order, bool needOrderLocalID);
	///����
	int ReqOrderAction(COrderActionField &OrderAction);
	bool InitClientIDSet(string szClientID);
	void InitClientTradingID(CClientTradingIDField *clientTradingID);
	char *GetLocalID(char cExchangID='s');	
	void QueryFinish();
	
	///200150616 xuzh ���ǵ���������ѯ�����������е���ˮ֮ǰ��ʹ�ñ�ʶ������
	///������ˮ��˳��qdata�ϳ���ˮ->��������ѯ��ˮ->������������ˮ
	virtual bool GetNextUseNoBuf(CPackage *pPackage);
	
protected:
	void Login();
	long GenPhaseId();

	void TransReqOrderInsert(CQTestFtdcInputOrderField &pOrder,CInputOrderField &Order);
	void TransReqOrderInsert(CQTestFtdcInputOrderField &pOrder,CWriteablePreOrder &Order);
	void TransRspOrder(CQTestFtdcInputOrderField *pInputOrder,CInputOrderField &Order);
	
	void TransReqOrderAction(CQTestFtdcOrderActionField &pOrderAction,COrderActionField &OrderAction);
	void TransRspAction(CQTestFtdcOrderActionField *pOrderAction,COrderActionField &OrderAction);
	
	void TransRtnOrder(CQTestFtdcOrderField *pOrder,COrderField &Order);
	void TransRtnDelOrder(CQTestFtdcOrderField *pOrder,COrderActionField &OrderAction);
	void TransRtnTrade(CQTestFtdcTradeField *pTrade,CTradeField &Trade);
	
private:
	CQTestFtdcTraderApi *m_pUserApi;
	int  m_TradeDate;	//��������
	int  m_iSeqNo;
	int  m_iMaxLocalNo;
	int  m_iReqSeqNo;
	
	char m_sMaxLocalNo[50];
	char m_sFlowPath[200];
	
	BYTE           m_Status;              //����״̬
	
	CQTestIpPoolMap m_FrontIpPoolMap;
	CQTestIpPoolMap m_FensIpPoolMap;
	int m_FensId;
	int m_FrontId;
	
	SetQTestClientID m_SetClientID;
	vector<CClientTradingIDField *> m_ClientTradingIDVec;//���ױ������Ϣ�洢
	
	CXTPPackage* m_pPubPackage;//д���õİ�
	bool m_bCanGetBuf; //�Ƿ���Դ���������ȡ����
	bool m_breveOver;  //��ѯ�Ƿ����
	
	//�û���Լ���ֲ֡����ڵĲ�ѯ�����ˮ
	///200150616 xuzh ���ǵ���������ѯ�����������е���ˮ֮ǰ��ʹ�ñ�ʶ������
	///������ˮ��˳��qdata�ϳ���ˮ->��������ѯ��ˮ->������������ˮ
	CExCachedFlow *m_pRryFlow;
	CFlowReader m_qryReader;
	int m_nQryClientTradingCount;
};

#endif
