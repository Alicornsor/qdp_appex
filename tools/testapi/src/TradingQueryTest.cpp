/////////////////////////////////////////////////////////////////////////
///@system ���ٷ��ǰ��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file TradingQueryTest.cpp
///@brief��������TradingQueryTest���������Է��ǰ�õĲ�ѯģ��
///@history 
///20121215	longqy@cffex.net �����ļ�

/////////////////////////////////////////////////////////////////////////

#include "TradingQueryTest.h"

CTradingQueryTest::CTradingQueryTest()
{

}

CTradingQueryTest::~CTradingQueryTest()
{

}

void *CTradingQueryTest::QueryInvestorPosition(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID )       
{
	CQdpFtdcQryInvestorPositionField CQryInvestorPosition;
	memset(&CQryInvestorPosition,0,sizeof(CQdpFtdcQryInvestorPositionField));
	strncpy(CQryInvestorPosition.InvestorID,"00000002",8);
	strncpy(CQryInvestorPosition.ExchangeID,"CFFEX",5);
	strncpy(CQryInvestorPosition.InstrumentID,"IF1212",6);
	if (pUserAPI==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"OrderFunc"," USERAPIδ����");
		return NULL;
	}
	pUserAPI->ReqQryInvestorPosition(&CQryInvestorPosition,++(*nOrderLocalID));
	return 0;
}

void CTradingQueryTest::QueryUser(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID)
{
	CQdpFtdcQryUserField CQryUser;
	memset(&CQryUser,0,sizeof(CQdpFtdcQryUserField));
	strncpy(CQryUser.StartUserID,"1",1);
	strncpy(CQryUser.EndUserID,"1",1);
	if (pUserAPI==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"OrderFunc"," USERAPIδ����");
		return ;
	}
	pUserAPI->ReqQryUser(&CQryUser,++(*nOrderLocalID));
	return ;
}

void CTradingQueryTest::QueryInvestorAccount(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID)
{
	CQdpFtdcQryInvestorAccountField CQryInvestorAccount;
	memset(&CQryInvestorAccount,0,sizeof(CQdpFtdcQryInvestorAccountField));
	strncpy(CQryInvestorAccount.InvestorID,"8",1);

	if (pUserAPI==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"OrderFunc"," USERAPIδ����");
		return ;
	}
	pUserAPI->ReqQryInvestorAccount(&CQryInvestorAccount,++(*nOrderLocalID));
	return ;
}

void CTradingQueryTest::QueryInstrument(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID)
{
	CQdpFtdcQryInstrumentField CQryInstrument;
	memset(&CQryInstrument,0,sizeof(CQdpFtdcQryInstrumentField));
	strncpy(CQryInstrument.ProductID,"IF",2);
	strncpy(CQryInstrument.InstrumentID,"IF1206",6);

	if (pUserAPI==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"OrderFunc"," USERAPIδ����");
		return ;
	}
	pUserAPI->ReqQryInstrument(&CQryInstrument,++(*nOrderLocalID));
	return ;
}

void CTradingQueryTest::QueryProduct(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID)
{
	CQdpFtdcQryInstrumentField CQryInstrument;
	memset(&CQryInstrument,0,sizeof(CQdpFtdcQryInstrumentField));
	strncpy(CQryInstrument.ProductID,"IF",2);
	strncpy(CQryInstrument.InstrumentID,"IF1206",6);

	if (pUserAPI==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"OrderFunc"," USERAPIδ����");
		return ;
	}
	pUserAPI->ReqQryInstrument(&CQryInstrument,++(*nOrderLocalID));
	return ;
}

void CTradingQueryTest::QueryExchange(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID)
{
	CQdpFtdcQryExchangeField CQryExchange;
	memset(&CQryExchange,0,sizeof(CQdpFtdcQryExchangeField));
	strncpy(CQryExchange.ExchangeID,"CFFEX",6);

	if (pUserAPI==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"OrderFunc"," USERAPIδ����");
		return ;
	}
	pUserAPI->ReqQryExchange(&CQryExchange,++(*nOrderLocalID));
	return ;
}

void CTradingQueryTest::QueryUserInvestor(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID)
{
	CQdpFtdcQryUserInvestorField CQryUserInvestor;
	memset(&CQryUserInvestor,0,sizeof(CQdpFtdcQryUserInvestorField));
	strncpy(CQryUserInvestor.BrokerID,"GTJA",4);
	strncpy(CQryUserInvestor.UserID,"1",1);

	if (pUserAPI==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"OrderFunc"," USERAPIδ����");
		return ;
	}
	pUserAPI->ReqQryUserInvestor(&CQryUserInvestor,++(*nOrderLocalID));
	return ;
}

void CTradingQueryTest::QueryTradingCode(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID)
{
	CQdpFtdcQryTradingCodeField CQryTradingCode;
	memset(&CQryTradingCode,0,sizeof(CQdpFtdcQryTradingCodeField));
	strncpy(CQryTradingCode.BrokerID,"GTJA",4);
	strncpy(CQryTradingCode.InvestorID,"01000014",8);
	strncpy(CQryTradingCode.ExchangeID,"CFFEX",6);
	strncpy(CQryTradingCode.InvestorID,"1",1);

	if (pUserAPI==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"OrderFunc"," USERAPIδ����");
		return ;
	}
	pUserAPI->ReqQryTradingCode(&CQryTradingCode,++(*nOrderLocalID));
	return ;
}

void CTradingQueryTest::QueryOrder(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID)
{
	CQdpFtdcQryOrderField CQryOrder;
	memset(&CQryOrder,0,sizeof(CQdpFtdcQryOrderField));
	strncpy(CQryOrder.ExchangeID,"CFFEX",6);
	strncpy(CQryOrder.InvestorID,"01000014",8);
	strncpy(CQryOrder.InstrumentID,"IF1206",6);
	strncpy(CQryOrder.UserID,"1",1);
//	strncpy(CQryOrder.OrderSysID,"113",3);

	if (pUserAPI==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"QueryOrder"," USERAPIδ����");
		return ;
	}
	pUserAPI->ReqQryOrder(&CQryOrder,++(*nOrderLocalID));
	return ;
}

void CTradingQueryTest::QueryTrade(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID)
{
	CQdpFtdcQryTradeField CQryTrade;
	memset(&CQryTrade,0,sizeof(CQdpFtdcQryTradeField));
	strncpy(CQryTrade.ExchangeID,"CFFEX",6);
	strncpy(CQryTrade.InvestorID,"01000014",8);
	strncpy(CQryTrade.InstrumentID,"IF1206",6);
//	strncpy(CQryTrade.UserID,"1",1);

	if (pUserAPI==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"QueryTrade"," USERAPIδ����");
		return ;
	}
	pUserAPI->ReqQryTrade(&CQryTrade,++(*nOrderLocalID));
	return ;
}

