/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file LoginServiceXTPLink.h
///@brief定义了类CLoginServiceXTPLink
///@history 
///20130701	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef LOGINSERVICEXTPLINK_H
#define LOGINSERVICEXTPLINK_H

#include "ServiceXTPLink.h"
#include "IServiceInterface.h"
#include "databaseData.h"
#include "CTransaction.h"
#include "CErrorEngine.h"
#include "CTransaction.h"
#include "monitorIndex.h"
#include "Flow.h"
#include "LoginServiceImpl.h"

/////////////////////////////////////////////////////////////////////////
///CLoginServiceMemoryLink是一个说明在内存运行的Login服务的连接
///@author	hwp
///@version	1.0,20130701
/////////////////////////////////////////////////////////////////////////

class CLoginServiceXTPLink : public IServiceXTPLink
{
public:
	///构造函数，根据一个login服务，创建一个内存运行的连接
	///@param	pLoginService	指定的trade服务
	///@param	pErrorEngine	用于返回错误的引擎
	///@param	verbose	true表示需要输出结果，flase表示不必输出结果
	CLoginServiceXTPLink(CLoginServiceImpl *pLoginService,CErrorEngine *pErrorEngine,IServiceResponser *pServiceResponser,bool verbose=true);
	
	///析构函数
	virtual ~CLoginServiceXTPLink();

	///处理一个XTP包
	///@param	pPackage	要处理的XTP包
	///@param	sessionRef	会话引用
	///@return	true表示处理成功，false表示处理失败
	virtual bool handleMessage(CXTPPackage *pPackage,  const TSessionRef &sessionRef);

	///处理一个XTP请求
	///@param	pPackage	要处理的XTP包
	///@param	sessionRef	会话引用
	///@return	true表示处理成功，false表示处理失败
	virtual bool handleRequest(CXTPPackage *pPackage,const TSessionRef &sessionRef,DWORD dwReponseSession);
	
private:
	CLoginServiceImpl *m_pLoginService;
	CErrorEngine *m_pErrorEngine;
	IServiceResponser *m_pServiceResponser;
	bool m_verbose;
	CTransaction m_Transaction;	
	CXTPPackage	 *m_pRspMessage;
};

#endif
