/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CInitServiceImpl.h
///@brief��������CInitServiceImpl
///@history 
///20060113	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CHandleNotify_H
#define CHandleNotify_H

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

//����һ���������࣬���ڴ�����ʼ�����ݵļ��
//by wangwei,20130510
#ifndef CINIT_CHECK_TRIGGER_CLASS_20130510
#define CINIT_CHECK_TRIGGER_CLASS_20130510

class CInitCheckTrigger : public CSystemStatusActionTrigger
{
public:
	CInitCheckTrigger(CMemoryDB *pDB,CConfig *pConfig)
	{
		m_pDB=pDB;
		m_Config=pConfig;
	}
	~CInitCheckTrigger()
	{
	}
	virtual void afterUpdate(CSystemStatus *pSystemStatus);
private:
	void businessCheck();
	void genError(const char *format,...);
private:	
	CMemoryDB *m_pDB;
	CConfig *m_Config;
	FILE *output;
	int errorCount;
};

#endif

typedef map<CInstrumentIDType,CInvestorPosition *> CSendInstrumentMap;
typedef map<CProductIDType, CInstrumentStatusField *> CProductStatusMap;

/////////////////////////////////////////////////////////////////////////
///CInitServiceImpl��һ����ɽ��������ݳ�ʼ����ʵ��
///@author	xuzh
///@version	1.0,20060113
/////////////////////////////////////////////////////////////////////////
class CHandleNotify : public CRuleHandleBase
{
public:
	///���캯��
	///@param	pDB	��ʵ��ʹ�õ��ڴ����ݿ�
	///@param	pErrorEngine	���ڱ���Ĵ�������
	CHandleNotify(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult);
//	bool HandleSeatLoginSuccess(CLoginInfoField *pLoginInfo,const TSessionRef &sessionRef,CTransaction *pTransaction,CSeatIDType  &GetSeatID,COrderLocalIDType  &GetOrderLocalID,vector<CWriteablePreOrder*> &PreOrders);	
	bool HandleSeatDisconnected(CSeatField *pSeat,const TSessionRef &sessionRef,CTransaction *pTransaction);//add by wangwei, 20121222
	bool HandleNtfTimeSync(CCurrentTimeField *pCurrTime,const TSessionRef &sessionRef,CTransaction *pTransaction);
	bool HandleMarketDataLastMatch(CMarketDataLastMatchField *marketDataLastMatchedField,const TSessionRef &sessionRef,CTransaction *pTransaction);
//	bool HandleNtfExapiSteadyStatus(CLifeCycleIDField* pLifeCycleField);
	bool HandleInstrumentStatusUpdate(CInstrumentStatusField* pInstrumentStatusField,bool bSendRtn,CTransaction *pTransaction);
	bool HandleInstrumentStatusUpdateEach(CInstrument* pInstrument,CInstrumentStatusField* pInstrumentStatusField,bool bSendRtn,CTransaction *pTransaction);
//	bool HandleRspQryExInstrument(CInstrumentField* pInstrumentField,const TSessionRef &sessionRef,CTransaction *pTransaction);//add by xuzh,20130502
//	bool HandleRspQryExTradingDay(CExchangeTradingDayField* pExchangeTradingDayField,const TSessionRef &sessionRef,CTransaction *pTransaction);//add by xuzh,20130502
//	bool HandleRspQryExClientPosition(CClientPositionField *pClientPositionField,const TSessionRef &sessionRef,CTransaction *pTransaction);//add by xuzh 20150617
//	bool HandleRspQryExMarketData(CMarketDataField *pMarketDataField,const TSessionRef &sessionRef,CTransaction *pTransaction);//add by xuzh 20150617

	void SendQryMarketData(bool bQuerySettlementPrice = false);

	void CZCEInstrumentStatusUpdate(bool bSendRtn = true);

   //���㸡��ӯ��,��ʱ������
	void CalcDynamicProfit(CWriteableMarketData *pMarketData,CInstrument *pInstrument,CTransaction *pTransaction);
protected:
   long GetTimeDiff(CWriteableCurrentTime* pCurrTime);
   long GetSecFromString(const char* pTime);
   
   /// ���� RemoveFaildPreOrder ����ʧ����;�������Ѷ�ʧ�Ķ�����Ԥ��������ɾ�������������
 //  int RemoveFaildPreOrder(CExchangeIDType&  ExchangeID,CSeatIDType&  SeatID,COrderLocalIDType  &OrderLocalID,CTransaction *pTransaction,vector<CWriteablePreOrder*> &PreOrders);
protected:
	CConfig       *m_pConfig;
	CXTPPackage   *m_pPubMessage;
	CErrorEngine  *m_pErrorEngine;
	CWriteableCurrentTime m_LastCalcDynamiceProfitTime;//�ϴμ��㸡��ӯ����ʱ��
	long m_nCalcDynamicProfitTimeCycle;//�㸡��ӯ�������ڣ�����,Ĭ��2000
	bool m_bCalcDynamicProfitSwitch;//���㶯̬Ȩ�濪��
	static CInitCheckTrigger *m_initTrigger;
	static int initCount;

	CFutureMoneyPosition* m_pFutureMoneyPosition;
	CBaseAlgorithms baseAlgorithms;

	CProductStatusMap  m_ProductStatusMap;
};



#endif
