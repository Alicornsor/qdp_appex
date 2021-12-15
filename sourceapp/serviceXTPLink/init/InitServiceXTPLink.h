/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file InitServiceMemoryLink.h
///@brief定义了类CInitServiceMemoryLink
///@history 
///20130701	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef INITSERVICEXTPLINK_H
#define INITSERVICEXTPLINK_H

#include "ServiceXTPLink.h"
#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "XtpData.h"
#include "CErrorEngine.h"
#include "CTransaction.h"
#include "Flow.h"
#include "CInitServiceImpl.h"

/////////////////////////////////////////////////////////////////////////
///CInitServiceMemoryLink是一个说明使用XTP的Init服务的连接
///@author	hwp
///@version	1.0,20130701
/////////////////////////////////////////////////////////////////////////
class CInitServiceXTPLink: public IServiceXTPLink
{
public:
	///构造函数，根据一个交易所init服务，创建一个使用XTP的连接
	///@param	pInitService	指定的交易所init服务
	///@param	pErrorEngine	用于返回错误的引擎
	///@param	verbose	true表示需要输出结果，flase表示不必输出结果
	CInitServiceXTPLink(CInitServiceImpl *pInitService,CErrorEngine *pErrorEngine,IServiceResponser *pServiceResponser,CFlow* pTradeResult,bool verbose=true);
	
	virtual ~CInitServiceXTPLink();

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
	
	//virtual void setFlow(CFlow *pFlow);
private:
	CInitServiceImpl *m_pInitService;
	CErrorEngine *m_pErrorEngine;
	bool m_verbose;
	CTransaction m_Transaction;
	CXTPPackage	 *m_pRspMessage;
	IServiceResponser *m_pServiceResponser;
	CFlow* m_pTradeResult;
};

#endif
