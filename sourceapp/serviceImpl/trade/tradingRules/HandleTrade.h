/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CInitServiceImpl.h
///@brief��������CInitServiceImpl
///@history 
///20060113	xuzh		�������ļ�
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
///CInitServiceImpl��һ����ɽ��������ݳ�ʼ����ʵ��
///@author	xuzh
///@version	1.0,20060113
/////////////////////////////////////////////////////////////////////////
class CHandleTrade : public CRuleHandleBase
{
public:
		
	virtual bool HandleRtnTrade(COrder *pOrder,CTradeField *pTradeField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	
	virtual bool HandleRtnCmbTrade(COrderField *pRtnOrder,CTradeField *pTradeField,const TSessionRef &sessionRef,CTransaction *pTransaction);
protected:
	//���캯������Ϊ�ܱ����ģ���Ϊ�˷�ֹ����CHandleTrade���󡣱��������������
	///���캯��
	///@param	pDB	��ʵ��ʹ�õ��ڴ����ݿ�
	///@param	pErrorEngine	���ڱ���Ĵ�������
	CHandleTrade(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult);
	
	
	
	///����Ƿ񳬼��Ự
	///@param	sessionRef	�Ự����
	///@return	true��ʾ�ǣ�false��ʾ��
    virtual bool FieldTransform(CTradeField *pTradeField,  COrder* pOrder);
	
protected:
	CConfig                    *m_pConfig;
	CXTPPackage                *m_pPubMessage;
   	CErrorEngine 	           *m_pErrorEngine;
	vector<CWriteableSeat>  m_Seats;
};



#endif
