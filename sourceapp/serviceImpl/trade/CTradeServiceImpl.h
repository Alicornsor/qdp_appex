/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CInitServiceImpl.h
///@brief��������CInitServiceImpl
///@history 
///20060113	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CTRADESERVICEIMPL_H
#define CTRADESERVICEIMPL_H

#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "XtpData.h"
#include "errorDefine.h"
#include "CMemoryDB.h"
#include "CDate.h"
#include "Flow.h"
#include "XTPPackage.h"
#include "XtpPackageDesc.h"
#include "HandleOrder.h"
#include "HandleNotify.h"
#include "HandleTrade.h"
#include "HandleOrderAction.h"

#include "HandleFutureOrder.h"
#include "HandleFutureTrade.h"


#include "BaseExchApi.h"
/////////////////////////////////////////////////////////////////////////
///CInitServiceImpl��һ����ɽ��������ݳ�ʼ����ʵ��
///@author	xuzh
///@version	1.0,20060113
/////////////////////////////////////////////////////////////////////////

class TPosi
{
public:
	CBrokerIDType     BrokerID;
	CInvestorIDType   InvestorID;
	CExchangeIDType   ExchangeID;
	CInstrumentIDType InstrumentID;
	CHedgeFlagType    HedgeFlag;
	CDirectionType	  Direction;
	bool operator > (const TPosi &m)const
	{
		if (BrokerID > m.BrokerID) 
		{
			return true;
		}
		else if (BrokerID < m.BrokerID)
		{
			return false;
		}
		else
		{
			if(InvestorID > m.InvestorID)
			{
				return true;
			}
			else if(InvestorID < m.InvestorID)
			{
				return false;
			}
			else
			{
				if (ExchangeID > m.ExchangeID)
				{
					return true;
				}
				else if (ExchangeID < m.ExchangeID)
				{
					return false;
				}
				else
				{
					if(InstrumentID > m.InstrumentID)
					{
						return true;
					}
					else if(InstrumentID < m.InstrumentID)
					{
						return false;
					}
					else
					{
						if(HedgeFlag > m.HedgeFlag)
						{
							return true;
						}
						else if (HedgeFlag < m.HedgeFlag)
						{
							return false;
						}
						else
						{
							if (Direction > m.Direction)
							{
								return true;
							}
							else
							{
								return false;
							}
						}
					}
				}
			}
		}
	}
};

//�ۺϳֲֶ���
typedef map<TPosi, CMoneyType, greater<TPosi> >	CPosiMap;

class CTradeServiceImpl
{
public:
	///���캯��
	///@param	pDB	��ʵ��ʹ�õ��ڴ����ݿ�
	///@param	pErrorEngine	���ڱ���Ĵ�������
	CTradeServiceImpl(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult);

	///��ʼ��������
	///@param	pExchange	Ҫ��ʼ���Ľ�������Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initExchange(CWriteableExchange *pExchange,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool ReqOrderInsert(CXTPPackage *pPackage,const TSessionRef &sessionRef);
	virtual bool ReqOrderAction(CWriteableOrderAction *pOrderAction,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspOrderInsert(CXTPPackage *pPackage,const TSessionRef &sessionRef);
	virtual bool RspOrderAction(COrderField *pRspOrder,CWriteableOrderAction *pOrderAction,COrderActionField* pActField,CRspInfoField*  pRspInfoField,const TSessionRef &sessionRef,CTransaction *pTransaction);	
	virtual bool OnRtnOrder(CXTPPackage *pPackage,const TSessionRef &sessionRef);
	virtual bool OnRtnTrade(CXTPPackage *pPackage,const TSessionRef &sessionRef);
	virtual bool NtfInstrumentStatusUpdate(CInstrumentStatusField* pInstrumentStatusField,bool bSendRtn,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual void DumpDebugInfo(const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual void CleanOrderLocalID();
	// 2013-12-24 longqy ��߱�֤���г�ʼ�������� PartClientInsGroupPosition ������
	virtual void BuildInsGroupPosition(CExchangeIDType exchangeID);
	//����ϵͳ״̬
	virtual bool UpdateSystemStatus(CSystemStatusField *pSystemStatusField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	//add by jinpc 20160906
	virtual bool DelUserSession(CUserField *pUserField,CTransaction *pTransaction);
	//ǿ��ɾ��session
 	virtual bool ForceUserLogout(CUserSession *pUserSession, CTransaction *pTransaction);
	//�����û���Ϣ
	virtual bool UserUpdate(CUserField *pUserField, CTransaction *pTransaction);

	virtual bool NtfSGEDeferRate(CSGEDeferRateField *pSGEDeferRateField,const TSessionRef &sessionRef,CTransaction *pTransaction);

	//����֣������Ϻ�Լtickֵ���ǵ�ͣ��
	virtual bool ReqCZCECombMarketData();
	//��ȡϵͳ������
	virtual CTradingDayType GetTradingDay();
	virtual bool ReqMBLMarketData(CQryMBLMarketDataField &pMBLMarketData,const TSessionRef &sessionRef);

	bool ReqNtfTimeSync(CXTPPackage *pPackage,const TSessionRef &sessionRef);

	bool ReqNtfPositionProfit(CXTPPackage *pPackage,const TSessionRef &sessionRef);
protected:
	///����Ƿ񳬼��Ự
	///@param	sessionRef	�Ự����
	///@return	true��ʾ�ǣ�false��ʾ��
	bool isSuperSession(const TSessionRef &sessionRef);
	virtual CProductClassType getProductClassType(CExchangeIDType ExchangeID,CInstrumentIDType InstrumentID, CNumberType& APIID);	
protected:
	CConfig *m_pConfig;
	CMemoryDB *m_pDB;
	CErrorEngine *m_pErrorEngine;
	CFlow* m_pTradeResult;
	CXTPPackage *m_pPubMessage;
	CHandleNotify *m_pHandleNotify;
	
	CHandleOrder *m_pHandleOrder;	
	// ֧���ڻ�����Ȩ��Ʒ��
//	CHandleOptionOrder *m_pHandleOptionOrder;
	CHandleFutureOrder *m_pHandleFutureOrder;
	
	CHandleTrade *m_pHandleTrade;
//	CHandleOptionTrade *m_pHandleOptionTrade;
	CHandleFutureTrade *m_pHandleFutureTrade;
	
	CHandleOrderAction *m_pHandleOrderAction;
	CHandleFutureOrderAction *m_pHandleFutureOrderAction;
//	CHandleOptionOrderAction *m_pHandleOptionOrderAction;
	FILE *m_orderActionFailedLog;//����������־	
// longqy 20141022 ��߱�֤���Ƿ����ı�־
private:
	bool m_bCombMarginSwitch;
	bool m_bOptionSwitch;
	CTransaction m_Transaction;
	char tmp[100];

	typedef set<string> CPartGroupPosition;
	CPartGroupPosition m_PartGroupPosition;
	CPosiMap m_PosiMap;

	CBaseAlgorithms baseAlgorithms;
};
#endif
