#ifndef __QDPMD_LINK_H
#define __QDPMD_LINK_H

#include "QdFtdcMdApi.h"
#include "QdFtdcUserApiStruct.h"
#include "platform.h"
#include "BaseExchApi.h"
#include "FlowReader.h"
#include "XTPPackage.h"

//交易席位接口
class CQdpMDLink : public CQdFtdcMduserSpi,public CBaseExchApi
{
public:
	CQdpMDLink(char *pszFlowPath);
	~CQdpMDLink();

	//连接
	void OnFrontConnected();
	void OnFrontDisconnected(int nReason);
	///用户登录应答
	void OnRspUserLogin(CQdFtdcRspUserLoginField *pRspUserLogin, CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspError(CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspQryMarketData(CQdFtdcRspMarketDataField *pRspMarketData, CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	void OnRtnQmdInstrumentStatu(CQdFtdcQmdInstrumentStateField *pQmdInstrumentState);
	
	bool ReqQryMarketData(CExchangeIDType ExchangeID,CInstrumentIDType InstrumentID);

	void SetFrontIp(const char *pIpFrontIP);
	void StartWork();

protected:
	void Login();

private:
	CQdFtdcMduserApi *m_pUserApi;
	char m_sFlowPath[200];
	char m_FrontIP[256];

	int  m_DisconnectNum;
	CXTPPackage* m_pPubPackage;//写流用的包
};

#endif
