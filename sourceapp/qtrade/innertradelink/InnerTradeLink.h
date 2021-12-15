/// ֤ȯ����ϯλ����
/// 20150630 ���һ� ����
//////////////////////////////////////////////////////////////////////////

#ifndef __STOCKTRADE_LINK_H
#define __STOCKTRADE_LINK_H

#include "platform.h"
#include "BaseExchApi.h"
#include "XTPPackage.h"
#include "FlowReader.h"
#include "Flow.h"
//#include "TcpXtpGateway.h"
#include "TcpXtpSessionFactory.h"
#include "XtpClient.h"

typedef map<int, string>  CStockIpPoolMap;
typedef set<string> SetStockClientID;//�ͻ�����
typedef vector<CClientTradingIDField *> VecClientTradingID;

//����ϯλ�ӿ�
class CInnerTradeLink : public CBaseExchApi,public CXtpClientCallback
{
public:
	CInnerTradeLink(const char *pSendAdr);
	~CInnerTradeLink();

	void StartWork();

	void InterLogin();
	virtual void InterLogined(CInterLoginInfoField *pInterLoginInfoField);
	virtual void OnSessionConnected(CSession *pSession);
	virtual void OnSessionDisconnected(CSession *pSession, int nReason);
	virtual int  GetAPIID();
	
	///����
	int ReqOrderInsert(CInputOrderField &Order);
	int ReqOrderInsert(CWriteablePreOrder &Order, bool needOrderLocalID);
	///����	
	int ReqOrderAction(COrderActionField &OrderAction);
	
	///��ֲ�
	bool ReqQryInvestorPosition(CQryInvestorPositionField &pInvestor);
	bool RspQryInvestorPosition(CInvestorPositionField &pInvestor);
	
	bool ReqQry(CInputOrderField &pInvestor);
	virtual char *GetLocalID(char cExchangID='s');
	
	///200150616 xuzh ���ǵ���������ѯ�����������е���ˮ֮ǰ��ʹ�ñ�ʶ������
	///������ˮ��˳��qdata�ϳ���ˮ->��������ѯ��ˮ->������������ˮ
	virtual bool GetNextUseNoBuf(CPackage *pPackage);
	
	void InitClientTradingID(CClientTradingIDField *clientTradingID);

	void SetMaxLocalID(int nMaxLocalID);
protected:
	long GenPhaseId();
	int  m_iMaxLocalNo;
	char m_sMaxLocalNo[50];
private:

	char m_sSvr[100];
	int  m_TradeDate;	//��������

	int  m_iSeqNo;
	int  m_iReqSeqNo;

	BYTE               m_Status;              //����״̬
	SetStockClientID   m_SetStockClientID;
	VecClientTradingID m_ClientTradingIDVec;  //���ױ������Ϣ�洢
	CXTPPackage        *m_pPubPackage;        //д���õİ�

	//char m_sFlowPath[200];

	//CTcpXtpGateway *m_pSendGetWay;
	//������
	CFlow *m_pSendFlow;
	CXtpClient *m_pSendClient;

	//���ն�
	CTcpXtpSessionFactory *m_pRevSessionFactory;

	char m_sSendAdr[128];
//	char m_sRecvAdr[128];
};


class CSGETradeLink : public CInnerTradeLink
{
public:
	CSGETradeLink(const char *pSendAdr);
	~CSGETradeLink();
	
	virtual char *GetLocalID(char cExchangID='s');
};

#endif
