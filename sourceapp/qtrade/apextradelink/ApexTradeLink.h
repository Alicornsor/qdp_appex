// ����ϯλ����
///200150616 xuzh ���ǵ���������ѯ�����������е���ˮ֮ǰ��ʹ�ñ�ʶ������
///������ˮ��˳��qdata�ϳ���ˮ->��������ѯ��ˮ->������������ˮ

#ifndef __APEXTRADE_LINK_H
#define __APEXTRADE_LINK_H

#include "ApexFtdcTraderApi.h"
#include "ApexFtdcUserApiStruct.h"
#include "platform.h"
#include "BaseExchApi.h"
#include "XTPPackage.h"
#include "FlowReader.h"
#include "ExCachedFlow.h"


typedef map<int, string>  CApexIpPoolMap;
typedef set<string> SetApexClientID;//�ͻ�����

typedef struct 
{
	CInvestorPositionField Position;
	int	 long_posi;
	int  short_posi;
}TNetPosi;

typedef map<string,TNetPosi> CNetPosiMap;
typedef map<string, CClientTradingIDField *> ClientTradingIDMap;

//����ϯλ�ӿ�
class CApexTradeLink : public CApexFtdcTraderSpi,public CBaseExchApi
{
public:
	CApexTradeLink(char *pszFlowPath);
	~CApexTradeLink();

	//����
	void OnFrontConnected();
	void OnFrontDisconnected(int nReason);
	//��¼
	void OnRspUserLogin(CApexFtdcRspUserLoginField *pRspUserLogin, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspError(CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//�����޸�Ӧ��
	void OnRspUserPasswordUpdate(CApexFtdcUserPasswordUpdateField *pUserPasswordUpdate, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	//����
	void OnRspOrderInsert(CApexFtdcInputOrderField *pInputOrder, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//����
	void OnRspOrderAction(CApexFtdcOrderActionField *pOrderAction, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//����֪ͨ
	void OnRtnOrder(CApexFtdcOrderField *pOrder);
	//�ɽ�֪ͨ
	void OnRtnTrade(CApexFtdcTradeField *pTrade);

	//��Լ����״̬֪ͨ
	void OnRtnInstrumentStatus(CApexFtdcInstrumentStatusField *pInstrumentStatus);

	void StartWork();
	//�յ��û���Ϣ��
	void OnPackageStart(int nTopicID, int nSequenceNo);
	char *GetLocalID(const char *pClientID,char cEoFlag =0);
	
	void ReqContract(int reqTime=1);
	void ReqClientPosi(int reqTime=1);
	void ReqMarketData(int reqTime=1);
	///��Լ��ѯӦ��
	void OnRspQryInstrument(CApexFtdcRspInstrumentField *pRspInstrument, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspQryClientPosition(CApexFtdcRspClientPositionField *pRspClientPosition, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspQryMarketData(CApexFtdcMarketDataField *pMarketData, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	void SetFensIp(const char *pIpFensIP);
	void SetFrontIp(const char *pIpFrontIP);
	///����������֪ͨ
	void OnRtnFlowMessageCancel(CApexFtdcFlowMessageCancelField *pFlowMessageCancel);
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

	void TransReqOrderInsert(CApexFtdcInputOrderField &pOrder,CWriteablePreOrder &Order);
	void TransReqOrderInsert(CApexFtdcInputOrderField &pOrder,CInputOrderField &Order);
	void TransRspOrder(CApexFtdcInputOrderField *pInputOrder,CInputOrderField &Order);
	
	void TransReqOrderAction(CApexFtdcOrderActionField &pOrderAction,COrderActionField &OrderAction);
	void TransRspAction(CApexFtdcOrderActionField *pOrderAction,COrderActionField &OrderAction);
	
	void TransRtnOrder(CApexFtdcOrderField *pOrder,COrderField &Order);
	void TransRtnDelOrder(CApexFtdcOrderField *pOrder,COrderActionField &OrderAction);
	void TransRtnTrade(CApexFtdcTradeField *pTrade,CTradeField &Trade);

private:
	CApexFtdcTraderApi *m_pUserApi;
	char  m_TradeDate[9];	//��������
	int  m_iSeqNo;
	int  m_iMaxLocalNo;
	int  m_iReqSeqNo;

	char m_sMaxLocalNo[50];
	char m_sFlowPath[200];

	BYTE           m_Status;              //����״̬
	
	CApexIpPoolMap m_FrontIpPoolMap;
	CApexIpPoolMap m_FensIpPoolMap;
	int m_FensId;
	int m_FrontId;

	SetApexClientID m_SetClientID;
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

	CNetPosiMap m_NetPosiMap;

	TNetPosi posi;
	char tmp[50];

	ClientTradingIDMap m_ClientTradingIDMap;//���ڲ��ң�ʹ�ý��ױ������
};

#endif
