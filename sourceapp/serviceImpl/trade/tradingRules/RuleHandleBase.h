/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CInitServiceImpl.h
///@brief��������CInitServiceImpl
///@history 
///20060113	xuzh		�������ļ�
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
	///���캯��
	///@param	pDB	��ʵ��ʹ�õ��ڴ����ݿ�
	///@param	pErrorEngine	���ڱ���Ĵ�������
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
