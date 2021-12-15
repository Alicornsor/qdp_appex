/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file CInitServiceImpl.h
///@brief定义了类CInitServiceImpl
///@history 
///20060113	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CHandleOrderAction_H
#define CHandleOrderAction_H

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
#include "BaseCheck.h"

/////////////////////////////////////////////////////////////////////////
///CInitServiceImpl是一个完成交易所数据初始化的实现
///@author	xuzh
///@version	1.0,20060113
/////////////////////////////////////////////////////////////////////////
class CHandleOrderAction : public CRuleHandleBase
{
public:
	~CHandleOrderAction();
 	bool HandleReqOrderAction(CWriteableOrderAction *pOrderAction,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool HandleRspOrderAction(CWriteableOrderAction *pOrderAction,COrderActionField* pActField,CRspInfoField*  pRspInfoField, COrder* pOrder, const TSessionRef &sessionRef,CTransaction *pTransaction);
protected:
    //构造函数定义为受保护的，是为了防止生成CHandleOrderAction对象。必须生成子类对象。
	CHandleOrderAction(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult);
private:
	void CopyFieldOrderActionFromOrder(COrderActionField* pActField,COrder* pOrder);

protected:
	CConfig                    *m_pConfig;
	CErrorEngine 	           *m_pErrorEngine;
	CBaseCheck* m_pBaseCheck;

};





class CHandleFutureOrderAction: public CHandleOrderAction
{

public:
    CHandleFutureOrderAction(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult);
	~CHandleFutureOrderAction();
};

#endif
