/////////////////////////////////////////////////////////////////////////
///@system 极速风控前置系统
///@company 上海量投网络科技有限公司
///@file TradingQueryTest.h
///@brief定义了类TradingQueryTest，用来测试风控前置的查询模块
///@history 
///20121215	longqy@cffex.net 创建文件

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