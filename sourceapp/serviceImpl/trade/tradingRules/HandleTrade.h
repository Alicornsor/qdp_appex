/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file CInitServiceImpl.h
///@brief定义了类CInitServiceImpl
///@history 
///20060113	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CHandleTrade_H
#define CHandleTrade_H

#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "XtpData.h"
#include "errorDefine.h"
#include "CMemoryDB.h"
#include "Flow.h"
#include "XTPPackage.h"
#include "XtpPackageDesc.h"
#include "RuleHandleBase.h"
#include "customDataType.h"
#include "FutureMoneyPosition.h"

/////////////////////////////////////////////////////////////////////////
///CInitServiceImpl是一个完成交易所数据初始化的实现
///@author	xuzh
///@version	1.0,20060113
/////////////////////////////////////////////////////////////////////////
class CHandleTrade : public CRuleHandleBase
{
public:
		
	virtual bool HandleRtnTrade(COrder *pOrder,CTradeField *pTradeField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	
	virtual bool HandleRtnCmbTrade(COrderField *pRtnOrder,CTradeField *pTradeField,const TSessionRef &sessionRef,CTransaction *pTransaction);
protected:
	//构造函数定义为受保护的，是为了防止生成CHandleTrade对象。必须生成子类对象。
	///构造函数
	///@param	pDB	本实现使用的内存数据库
	///@param	pErrorEngine	用于报错的错误引擎
	CHandleTrade(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult);
	
	
	
	///检查是否超级会话
	///@param	sessionRef	会话引用
	///@return	true表示是，false表示否
    virtual bool FieldTransform(CTradeField *pTradeField,  COrder* pOrder);
	
protected:
	CConfig                    *m_pConfig;
	CXTPPackage                *m_pPubMessage;
   	CErrorEngine 	           *m_pErrorEngine;
	vector<CWriteableSeat>  m_Seats;
};



#endif
