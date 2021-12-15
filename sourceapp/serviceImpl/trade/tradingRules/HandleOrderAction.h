/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CInitServiceImpl.h
///@brief��������CInitServiceImpl
///@history 
///20060113	xuzh		�������ļ�
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
///CInitServiceImpl��һ����ɽ��������ݳ�ʼ����ʵ��
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
    //���캯������Ϊ�ܱ����ģ���Ϊ�˷�ֹ����CHandleOrderAction���󡣱��������������
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
