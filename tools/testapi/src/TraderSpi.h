// TraderSpi.h: interface for the CTraderSpi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRADERSPI_H__4B26E1C3_9EEE_4412_8C08_71BFB55CE6FF__INCLUDED_)
#define AFX_TRADERSPI_H__4B26E1C3_9EEE_4412_8C08_71BFB55CE6FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PublicFuncs.h"

class CTraderSpi : public CQdpFtdcUserSpi  
{
public:
	CTraderSpi(CQdpFtdcUserApi *pTrader);
	virtual ~CTraderSpi();

	virtual void OnFrontConnected();
	virtual void OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//traderSPI
	virtual void OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRtnTrade(CQdpFtdcTradeField *pTrade);
	virtual void OnRtnOrder(CQdpFtdcOrderField *pOrder);
	//QuerySPI
/*	virtual void ReqQryInstrument();
	virtual void RspQryInstrument();
	virtual void ReqQryInvestorAccount();
	virtual void RspQryInvestorAccount();
*/
private:	
	CQdpFtdcUserApi *m_pUserApi;
};

#endif // !defined(AFX_TRADERSPI_H__4B26E1C3_9EEE_4412_8C08_71BFB55CE6FF__INCLUDED_)
