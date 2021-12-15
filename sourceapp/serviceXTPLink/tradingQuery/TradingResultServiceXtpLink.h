/////////////////////////////////////////////////////////////////////////
///@system 极速风控前置系统
///@company 上海量投网络科技有限公司
///@file TradingResultServiceXtpLink.h
///@brief定义了类TradingResultServiceXtpLink，计算交易的结果
///@history 
///20121214	longqy@cffex.net 创建文件

/////////////////////////////////////////////////////////////////////////

#ifndef TRADINGRESULTSERVICEXTPLINK_H
#define TRADINGRESULTSERVICEXTPLINK_H

#include "ServiceXTPLink.h"
#include "CErrorEngine.h"
#include "CTransaction.h"
#include "LogMemoryDatabaseTable.h"
#include "TradingResultImpl.h"

/////////////////////////////////////////////////////////////////////////
///CTradingResultServiceXtpLink是一个说明在内存运行，计算交易结果的服务的连接
///@author	Longqy
///@version	1.0,20121214
/////////////////////////////////////////////////////////////////////////

class CTradingResultServiceXtpLink: public IServiceXTPLink
{
public:
///构造函数，根据一个查询服务，创建一个计算交易结果的连接	
CTradingResultServiceXtpLink(CTradingResultImpl *pQueryService,
CErrorEngine *pErrorEngine, IServiceResponser *pServiceResponser, CMemoryDB *pDB, bool verbose, bool md5Password);

	///析构函数
	virtual ~CTradingResultServiceXtpLink();

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
private:
	void ResponseErrorMsg(CXTPPackage *pPackage,DWORD rspTID,DWORD dwSessionID);
	CTradingResultImpl *m_pTradingResultService;
	CErrorEngine *m_pErrorEngine;
	IServiceResponser *m_pServiceResponser;
	CMemoryDB *m_pDB;
	bool m_verbose;
	CTransaction m_Transaction;	
	CXTPPackage	 *m_pRspMessage;
	bool m_md5Password;
	// CLogMemoryDatabaseTable *m_pLogTable;
};

extern CLogMemoryDatabaseTable	g_logMemoryDBTable;

#endif
