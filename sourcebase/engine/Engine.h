/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file Engine.h
///@brief定义了类CEngine
///@history 
///20060118	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef ENGINE_H
#define ENGINE_H

#include "BaseEngine.h"
#include "IServiceInterface.h"
#include "ServiceXTPLink.h"
#include "FibPublishApi.h"

/////////////////////////////////////////////////////////////////////////
///CEngine是一个XTP消息传送的引擎，包含了一组XTP服务连接
///@author	xuzh
///@version	1.0,20060118
/////////////////////////////////////////////////////////////////////////
class CEngine: protected vector<IServiceXTPLink *>, protected CBaseEngine
{
public:
	///构造函数
	///@param	pConfig	创建引擎需要使用的配置
	///@param	recovery	是否使用恢复模式
	///@param	verbose	true表示要输出结果，flase表示不要输出结果
	CEngine(CConfig *pConfig, bool verbose=true);
	
	virtual ~CEngine(void);
	
	///处理一个内存XTP包
	///@param	pPackage	要处理的XTP包
	virtual void handleMessage(CXTPPackage *pPackage);
	
	///处理一个请求
	///@param	pPackage	要处理的请求
	///@param	nSessionID	会话编号
	virtual void handleRequest(CXTPPackage *pPackage,DWORD nSessionID);

protected:
	///增加一个内存服务连接
	///@param	pLink	要增加的内存服务连接
	void addServiceXTPLink(IServiceXTPLink *pLink);

	///删除一个内存服务连接
	///@param	pLink	要删除的内存服务连接
	///@return	true表示删除成功，flase表示删除失败
	bool removeServiceXTPLink(IServiceXTPLink *pLink);

	int m_seqID;	
};

#endif
