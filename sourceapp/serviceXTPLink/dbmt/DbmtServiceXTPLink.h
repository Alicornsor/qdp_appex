/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 中金所技术公司
///@file DbmtServiceXtpLink.h
///@brief定义了类CDbmtServiceXtpLink
///@history 
///20130119	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef DBMTSERVICEXTPLINK_H
#define DBMTSERVICEXTPLINK_H

#include "ServiceXTPLink.h"
#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "XtpPackageDesc.h"
#include "CErrorEngine.h"
#include "CTransaction.h"
#include "Flow.h"
#include "CDbmtServiceImpl.h"

/////////////////////////////////////////////////////////////////////////
///CDbmtServiceXtpLink是一个说明在内存运行的Dbmt服务的连接
///@author	hwp
///@version	1.0,20130119
/////////////////////////////////////////////////////////////////////////
class CDbmtServiceXtpLink: public IServiceXTPLink
{
public:
	///构造函数，根据一个Dbmt服务，创建一个内存运行的连接
	///@param	ppDbmtService	指定的dbmt服务
	///@param	pErrorEngine	用于返回错误的引擎
	///@param	verbose	true表示需要输出结果，flase表示不必输出结果
	CDbmtServiceXtpLink(CDbmtServiceImpl *pDbmtService,CErrorEngine *pErrorEngine,
						IServiceResponser *pServiceResponser,CFlow* pTradeResult, bool verbose=true);
	
	///析构函数
	virtual ~CDbmtServiceXtpLink();

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
	CDbmtServiceImpl *m_pService;
	CErrorEngine *m_pErrorEngine;
	IServiceResponser *m_pServiceResponser;
	bool m_verbose;
	CTransaction m_Transaction;	
	CXTPPackage	 *m_pRspMessage;
	CFlow* m_pTradeResult;
};

#endif
