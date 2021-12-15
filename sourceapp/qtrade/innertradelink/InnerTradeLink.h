/// 证券交易席位连接
/// 20150630 徐忠华 创建
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
typedef set<string> SetStockClientID;//客户容器
typedef vector<CClientTradingIDField *> VecClientTradingID;

//交易席位接口
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
	
	///报单
	int ReqOrderInsert(CInputOrderField &Order);
	int ReqOrderInsert(CWriteablePreOrder &Order, bool needOrderLocalID);
	///撤单	
	int ReqOrderAction(COrderActionField &OrderAction);
	
	///查持仓
	bool ReqQryInvestorPosition(CQryInvestorPositionField &pInvestor);
	bool RspQryInvestorPosition(CInvestorPositionField &pInvestor);
	
	bool ReqQry(CInputOrderField &pInvestor);
	virtual char *GetLocalID(char cExchangID='s');
	
	///200150616 xuzh 考虑到交易所查询流必须在所有的流水之前，使用标识符控制
	///输入流水的顺序：qdata上场流水->交易所查询流水->交易所推送流水
	virtual bool GetNextUseNoBuf(CPackage *pPackage);
	
	void InitClientTradingID(CClientTradingIDField *clientTradingID);

	void SetMaxLocalID(int nMaxLocalID);
protected:
	long GenPhaseId();
	int  m_iMaxLocalNo;
	char m_sMaxLocalNo[50];
private:

	char m_sSvr[100];
	int  m_TradeDate;	//交易日期

	int  m_iSeqNo;
	int  m_iReqSeqNo;

	BYTE               m_Status;              //交易状态
	SetStockClientID   m_SetStockClientID;
	VecClientTradingID m_ClientTradingIDVec;  //交易编码的消息存储
	CXTPPackage        *m_pPubPackage;        //写流用的包

	//char m_sFlowPath[200];

	//CTcpXtpGateway *m_pSendGetWay;
	//发送流
	CFlow *m_pSendFlow;
	CXtpClient *m_pSendClient;

	//接收端
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
