/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file CInitServiceImpl.h
///@brief定义了类CInitServiceImpl
///@history 
///20060113	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CRuleHandleBase_H
#define CRuleHandleBase_H

#include "errorDefine.h"
#include "CMemoryDB.h"
#include "Flow.h"
#include "XTPPackage.h"
#include "XtpPackageDesc.h"
#include "RuleHandleBase.h"
#include "UFEntityCopy.h"
#include "MoneyPosition.h"
#include "FutureMoneyPosition.h"
#include "errorDefine.h"

class CRuleHandleBase
{

public:
	///构造函数
	///@param	pDB	本实现使用的内存数据库
	///@param	pErrorEngine	用于报错的错误引擎
    CRuleHandleBase(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,	CFlow* pTradeResult);
	virtual ~CRuleHandleBase();
 
	bool InitIndexPreOrder(CPreOrder *pOrder,CWriteableIndexPreOrder *pIndexPreOrder,CTransaction *pTransaction, bool isRecover=false);
protected:
//    bool  GetMarginAndFee(CInputOrderField *pOrderField,CMoneyField*  theMoneyField);
//    bool  UnFrozenFromOrderInsertFailed(CPreOrder*  pPreOrder);

protected:   
	CConfig   *m_pConfig;
	CMemoryDB *m_pDB;
	CErrorEngine *m_pErrorEngine;
	CMoneyPosition* m_pMoneyPosition;
    CFlow* m_pTradeResult;
	CBaseAlgorithms baseAlgorithms;    
};

#endif
