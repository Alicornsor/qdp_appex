/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file TradingQueryServiceXtpLink.h
///@brief定义了类CDbmtServiceXtpLink
///@history 
///20060119	xuzh		创建该文件
///20090118	xuzh		增加了查询的日志（NT-0065）
/////////////////////////////////////////////////////////////////////////

#ifndef TRADINGQUERYSERVICEXTPLINK_H
#define TRADINGQUERYSERVICEXTPLINK_H

#include "ServiceXTPLink.h"
#include "CErrorEngine.h"
#include "CTransaction.h"
#include "XtpData.h"

#include "LogMemoryDatabaseTable.h"
#include "QueryComplianceParam.h"
#include "baseAlgorithms.h"
#include "TradingQueryServiceImpl.h"

typedef map<CExchangeIDType, int> CExchangeMap;
/////////////////////////////////////////////////////////////////////////
///CTradingQueryServiceXtpLink是一个说明在内存运行的交易查询服务的连接
///@author	xuzh
///@version	1.0,20060119
/////////////////////////////////////////////////////////////////////////
class CTradingQueryServiceXtpLink: public IServiceXTPLink
{
public:
	///构造函数，根据一个查询服务，创建一个内存运行的连接
	///@param	pQueryService	指定的dbmt服务
	///@param	pErrorEngine	用于返回错误的引擎
	///@param	pDB	使用的内存数据库
	///@param	verbose	true表示需要输出结果，flase表示不必输出结果
	CTradingQueryServiceXtpLink(CTradingQueryImpl *pQueryService,CErrorEngine *pErrorEngine,
						IServiceResponser *pServiceResponser, CMemoryDB *pDB, bool verbose=true);
	
	///析构函数
	virtual ~CTradingQueryServiceXtpLink();

	///处理一个XTP包
	///@param	pPackage	要处理的XTP包
	///@param	sessionRef	会话引用
	///@return	true表示处理成功，false表示处理失败
	virtual bool handleMessage(CXTPPackage *pPackage, const TSessionRef &sessionRef);

	///处理一个XTP请求
	///@param	pPackage	要处理的XTP包
	///@param	sessionRef	会话引用
	///@return	true表示处理成功，false表示处理失败
	virtual bool handleRequest(CXTPPackage *pPackage,const TSessionRef &sessionRef,DWORD dwReponseSession);
	virtual bool copyInvestorPositionField(CInvestorPositionField *pClientField,CInvestorPositionField *pInvestorField,CInvestorIDType &investorID);
	
private:
	//处理特殊的查询请求
	bool QueryInvestorFee(CXTPPackage *pPackage,CQryInvestorFeeField &field,DWORD ResponseSessionID);
	bool QueryInvestorFeeEach(CInvestorIDType &InvestorID,CXTPPackage *pPackage,CQryInvestorFeeField &field,DWORD ResponseSessionID);

	bool QueryInvestorOptionFee(CXTPPackage *pPackage,CQryInvestorOptionFeeField &field,DWORD ResponseSessionID);
	bool QueryInvestorOptionFeeEach(CInvestorIDType &InvestorID,CXTPPackage *pPackage,CQryInvestorOptionFeeField &field,DWORD ResponseSessionID);
	
	bool QueryInvestorMargin(CXTPPackage *pPackage,CQryInvestorMarginField &field,DWORD ResponseSessionID);
	bool QueryInvestorMarginEach(CInvestorIDType &InvestorID,CXTPPackage *pPackage,CQryInvestorMarginField &field,DWORD ResponseSessionID);

	bool QuerySeatInfo(CXTPPackage *pPackage,CQrySeatInfoField &field,DWORD ResponseSessionID);

	void AddtoFlow(CXTPPackage *pPackage,const TSessionRef& sessionRef,DWORD ResponseSessionID);
	void FlushPackage(bool bLast, DWORD nSessionID);
	bool getClientIDsFromInvestorIDs(CQryInvestorPositionField &invPositionField,ClientIDVector **pVector,const TSessionRef &sessionRef,CTransaction *pTransaction);	
	///输出查询日志
	///@param	sessionRef	会话标识
	///@param	startTime	开始查询时间，以毫秒计
	///@param	endTime	结束查询时间，以毫秒计
	///@param	queryInfo	查询信息
	void ResponseErrorMsg(CXTPPackage *pPackage,DWORD rspTID,DWORD dwSessionID);

	void ResponseNullMsg(CXTPPackage *pPackage,DWORD rspTID,DWORD dwSessionID);
	
	CTradingQueryImpl *m_pService;
	CErrorEngine *m_pErrorEngine;
	IServiceResponser *m_pServiceResponser;
	CMemoryDB *m_pDB;
	bool m_verbose;
	CTransaction m_Transaction;	
	CXTPPackage	 *m_pRspMessage;
	CBaseAlgorithms baseAlgorithm;
	CExchangeInvestorID2ClientIDMap m_mapClientID;
	CExchangeMap m_ExchangeMap;
	char tmp[100];
};

extern CLogMemoryDatabaseTable	g_logMemoryDBTable;

#endif
