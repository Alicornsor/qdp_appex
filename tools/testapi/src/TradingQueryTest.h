/////////////////////////////////////////////////////////////////////////
///@system ���ٷ��ǰ��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file TradingQueryTest.h
///@brief��������TradingQueryTest���������Է��ǰ�õĲ�ѯģ��
///@history 
///20121215	longqy@cffex.net �����ļ�

/////////////////////////////////////////////////////////////////////////

#ifndef TRADINGQUERYTEST_H
#define TRADINGQUERYTEST_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PublicFuncs.h"

class   CTradingQueryTest
{
public:
	CTradingQueryTest();
	~CTradingQueryTest();

	void *QueryInvestorPosition(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID );
	void QueryUser(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID );
	void QueryInvestorAccount(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID );
	void QueryInstrument(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID );
	void QueryProduct(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID );
	void QueryExchange(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID);
	void QueryUserInvestor(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID);
	void QueryTradingCode(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID);
	void QueryOrder(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID);
	void QueryTrade(CQdpFtdcUserApi *pUserAPI,int *nOrderLocalID);

private:	
	
};

#endif