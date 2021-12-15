// 交易席位连接
///200150616 xuzh 考虑到交易所查询流必须在所有的流水之前，使用标识符控制
///输入流水的顺序：qdata上场流水->交易所查询流水->交易所推送流水

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
typedef set<string> SetQTestClientID;//客户容器

//交易席位接口
class CQTestTradeLink : public CQTestFtdcTraderSpi,public CBaseExchApi
{
public:
	CQTestTradeLink(char *pszFlowPath);
	~CQTestTradeLink();
	
	//连接
	void OnFrontConnected();
	void OnFrontDisconnected(int nReason);
	//登录
	void OnRspUserLogin(CQTestFtdcRspUserLoginField *pRspUserLogin, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspError(CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	//密码修改应答
	void OnRspUserPasswordUpdate(CQTestFtdcUserPasswordUpdateField *pUserPasswordUpdate, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};
	
	//报单
	void OnRspOrderInsert(CQTestFtdcInputOrderField *pInputOrder, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//撤单
	void OnRspOrderAction(CQTestFtdcOrderActionField *pOrderAction, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	//报单通知
	void OnRtnOrder(CQTestFtdcOrderField *pOrder);
	//成交通知
	void OnRtnTrade(CQTestFtdcTradeField *pTrade);
	
	//合约交易状态通知
	void OnRtnInstrumentStatus(CQTestFtdcInstrumentStatusField *pInstrumentStatus);
	
	void StartWork();
	//收到用户消息包
	void OnPackageStart(int nTopicID, int nSequenceNo);
	char *GetLocalID(const char *pClientID,char cEoFlag =0);
	
	void ReqContract(int reqTime=1);
	void ReqClientPosi(int reqTime=1);
	void ReqMarketData(int reqTime=1);
	///合约查询应答
	void OnRspQryInstrument(CQTestFtdcRspInstrumentField *pRspInstrument, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspQryClientPosition(CQTestFtdcRspClientPositionField *pRspClientPosition, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspQryMarketData(CQTestFtdcMarketDataField *pMarketData, CQTestFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	void SetFensIp(const char *pIpFensIP);
	void SetFrontIp(const char *pIpFrontIP);
	///数据流回退通知
	void OnRtnFlowMessageCancel(CQTestFtdcFlowMessageCancelField *pFlowMessageCancel);
	bool ClientIDExist(const char *pClientID);
	
	///报单
	int ReqOrderInsert(CInputOrderField &Order);
	int ReqOrderInsert(CWriteablePreOrder &Order, bool needOrderLocalID);
	///撤单
	int ReqOrderAction(COrderActionField &OrderAction);
	bool InitClientIDSet(string szClientID);
	void InitClientTradingID(CClientTradingIDField *clientTradingID);
	char *GetLocalID(char cExchangID='s');	
	void QueryFinish();
	
	///200150616 xuzh 考虑到交易所查询流必须在所有的流水之前，使用标识符控制
	///输入流水的顺序：qdata上场流水->交易所查询流水->交易所推送流水
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
	int  m_TradeDate;	//交易日期
	int  m_iSeqNo;
	int  m_iMaxLocalNo;
	int  m_iReqSeqNo;
	
	char m_sMaxLocalNo[50];
	char m_sFlowPath[200];
	
	BYTE           m_Status;              //交易状态
	
	CQTestIpPoolMap m_FrontIpPoolMap;
	CQTestIpPoolMap m_FensIpPoolMap;
	int m_FensId;
	int m_FrontId;
	
	SetQTestClientID m_SetClientID;
	vector<CClientTradingIDField *> m_ClientTradingIDVec;//交易编码的消息存储
	
	CXTPPackage* m_pPubPackage;//写流用的包
	bool m_bCanGetBuf; //是否可以从推送流读取数据
	bool m_breveOver;  //查询是否完成
	
	//用户合约、持仓、日期的查询结果流水
	///200150616 xuzh 考虑到交易所查询流必须在所有的流水之前，使用标识符控制
	///输入流水的顺序：qdata上场流水->交易所查询流水->交易所推送流水
	CExCachedFlow *m_pRryFlow;
	CFlowReader m_qryReader;
	int m_nQryClientTradingCount;
};

#endif
