/////////////////////////////////////////////////////////////////////////
///@system ���ٷ��ǰ��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file TradingResultImpl.h
///@brief��������TradingResultImpl�����㽻�׵Ľ���������ڴ����ݿ�
///@history 
///20121219	longqy@cffex.net �����ļ�

/////////////////////////////////////////////////////////////////////////
#ifndef TRADINGRESULTIMPL_H
#define TRADINGRESULTIMPL_H

//#include "IServiceInterface.h"
#include "errorDefine.h"
#include "CMemoryDB.h"
#include "UFCopy.h"

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

/*** SIR XXXXX BEGIN ***/
///����������ڻ���ϯ
#define INVESTORACCOUNTDEPOSIT_TOPICID_CHAIRMAN      "9001"
#define INVESTORACCOUNTDEPOSIT_FROM_CHAIRMAN         'A'
#define INVESTORACCOUNTDEPOSIT_FROM_MONEYGATE        'M'

///��������Գ���
#define INVESTORACCOUNTDEPOSIT_TOPICID_FIELD         "9002"
#define INVESTORACCOUNTDEPOSIT_FROM_FIELD            'B'

///��������Գ�������
#define INVESTORACCOUNTDEPOSIT_TOPICID_Netting       "9003"
#define INVESTORACCOUNTDEPOSIT_FROM_Netting            'C'
/*** SIR XXXXX END ***/


/////////////////////////////////////////////////////////////////////////
///CTradingResultImpl �������TResult�����ݣ�������Щ����ת��Ϊ
///�ڴ����ݿ������
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

class CTradingResultImpl
{
public:
	CTradingResultImpl(CMemoryDB *pDB,CErrorEngine *pEngine,CConfig *pConfig,CFlow *pFlow);
	 ~CTradingResultImpl();

	///��ʼ��������
	///@param	pExchange	Ҫ��ʼ���Ľ�������Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initExchange(CWriteableExchange *pExchange,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ��ϯλ
	///@param	pSeat	Ҫ��ʼ����ϯλ��Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initSeat(CWriteableSeat *pSeat,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ���û�
	///@param	pUser	Ҫ��ʼ�����û���Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initUser(CWriteableUser *pUser,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ��Ͷ����
	///@param	pInvestor	Ҫ��ʼ����Ͷ������Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initInvestor(CWriteableInvestor *pInvestor,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ�����ױ���
	///@param	pClientTradingID	Ҫ��ʼ���Ľ��ױ�����Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initClientTradingID(CWriteableClientTradingID *pClientTradingID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ���û�Ͷ���߹�ϵ
	///@param	pUserInvestor	Ҫ��ʼ�����û�Ͷ���߹�ϵ��Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initUserInvestor(CWriteableUserInvestor *pUserInvestor,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ���û�����Ȩ��
	///@param	pUserTradingRight	Ҫ��ʼ�����û�����Ȩ����Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initUserTradingRight(CWriteableUserTradingRight *pUserTradingRight,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ��Ͷ�����ʽ��˻�
	///@param	pInvestorAccount	Ҫ��ʼ����Ͷ�����ʽ��˻���Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initInvestorAccount(CWriteableInvestorAccount *pInvestorAccount,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ����Լ
	///@param	pInstrument	Ҫ��ʼ���ĺ�Լ��Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initInstrument(CWriteableInstrument *pInstrument,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ��Ͷ���߱�֤����
	///@param	pInvestorMargin	Ҫ��ʼ����Ͷ���߱�֤������Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initInvestorMargin(CWriteableInvestorMargin *pInvestorMargin,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ��Ͷ����������
	///@param	pInvestorFee	Ҫ��ʼ����Ͷ������������Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initInvestorFee(CWriteableInvestorFee *pInvestorFee,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ��Ͷ���ֲ߳�
	///@param	pInvestorPosition	Ҫ��ʼ����Ͷ���ֲ߳���Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initInvestorPosition(CWriteableInvestorPosition *pInvestorPosition,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ��ϵͳ״̬
	///@param	pSystemStatus	Ҫ��ʼ����ϵͳ״̬��Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initSystemStatus(CWriteableSystemStatus *pSystemStatus,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ����Լ�ͺ�Լ���ϵ
	///@param	pInstrumentGroup	Ҫ��ʼ���ĺ�Լ�ͺ�Լ���ϵ��Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initInstrumentGroup(CWriteableInstrumentGroup *pInstrumentGroup,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ�����ױ�����ϱ�֤������
	///@param	pClientMarginCombType	Ҫ��ʼ���Ľ��ױ�����ϱ�֤��������Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initClientMarginCombType(CWriteableClientMarginCombType *pClientMarginCombType,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ���������ӷ�����Ϣ��
	///@param	pSGEDeferRate	Ҫ��ʼ���Ľ������ӷ�����Ϣ����Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initSGEDeferRate(CWriteableSGEDeferRate *pSGEDeferRate,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ����Ϻ�Լ��ϸӦ��
	///@param	pCmbInstrumentDetail	Ҫ��ʼ������Ϻ�Լ��ϸӦ����Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initCmbInstrumentDetail(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ������ԱIP
	///@param	pUserIP	Ҫ��ʼ���Ľ���ԱIP��Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initUserIP(CWriteableUserIP *pUserIP,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ��Ͷ������Ȩ������
	///@param	pInvestorOptionFee	Ҫ��ʼ����Ͷ������Ȩ��������Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initInvestorOptionFee(CWriteableInvestorOptionFee *pInvestorOptionFee,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��ʼ����������ͬ��
	///@param	TradingDay	������
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool DataSyncStart(CDateType &TradingDay,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///��������������ͬ��
	///@param	TradingDay	������
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool DataSyncEnd(CDateType &TradingDay,const TSessionRef &sessionRef,CTransaction *pTransaction);

	void beforeDataSync(CTransaction *pTransaction);

	void afterDataSync(CTransaction *pTransaction);

	virtual bool RspQryExInstrument(CInstrumentField *pInstrumentField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQryExTradingDay(CExchangeTradingDayField *pExchangeTradingDayField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQryExInvestorPosition(CInvestorPositionField *pInvestorPositionField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQryExMarketData(CMarketDataField *pMarketDataField,const TSessionRef &sessionRef,CTransaction *pTransaction);	
	virtual bool RspQryExCapitalData(CExCapitalDataField *pExCapitalDataField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQueryExCmbInstrumentDetail(CCmbInstrumentDetailField *pCmbInstrumentDetailField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQryExDiffTime(CExchTimeDiffField *pExchTimeDiffField,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///ͬ�����ݿ��ͻ��ʽ��ʻ������
	///@param	pInvestorAccountDeposit	Ҫͬ���Ŀͻ��ʽ��ʻ��������Ϣ
	///@param	pResDeposit	�����Ӧ����Ϣ
	///@param	topicID	DBMT�������
	///@param	seqID	DBMT�����к�
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncInvestorAccountDeposit(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit,CAccountDepositResField *pResDeposit,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
									const TSessionRef &sessionRef,CTransaction *pTransaction);


	///ͬ�����ݿ���޸Ľ����û�
	///@param	pUpdUser	Ҫͬ�����޸Ľ����û���Ϣ
	///@param	topicID	DBMT�������
	///@param	seqID	DBMT�����к�
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncUpdUser(CWriteableUser *pUser,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///ͬ�����ݿ��ͻ��ʽ��ʻ�������ʵ��
	///@param	pClientTradingID	Ҫͬ���Ŀͻ��ʽ��ʻ��������Ϣ
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncClientTradingID(CWriteableClientTradingID *pClientTradingID,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
		const TSessionRef &sessionRef,CTransaction *pTransaction);

	
	bool OnRtnOrder(COrderField *pOrder,const TSessionRef &sessionRef,CTransaction *pTransaction);

	bool OnRtnTrade(CTradeField *pTrade,const TSessionRef &sessionRef,CTransaction *pTransaction);

	bool RspOrderAction(COrderField *pRspOrder,CWriteableOrderAction *pOrderAction,COrderActionField* pActField,
			CRspInfoField*  pRspInfoField,const TSessionRef &sessionRef,CTransaction *pTransaction);

	void DumpDebugInfo(const TSessionRef &sessionRef,CTransaction *pTransaction);

	bool UpdateSystemStatus(CSystemStatusField *pSystemStatusField,const TSessionRef &sessionRef,CTransaction *pTransaction);

	void BuildInsGroupPosition(CExchangeIDType exchangeID);

	bool NtfInstrumentStatusUpdate(CInstrumentStatusField* pInstrumentStatusField,bool bSendRtn,const TSessionRef &sessionRef,CTransaction *pTransaction);

	bool UserUpdate(CDbmtUserField *pUserField, CTransaction *pTransaction);

	bool NtfSGEDeferRate(CSGEDeferRateField *pSGEDeferRateField,const TSessionRef &sessionRef,CTransaction *pTransaction);

	bool NtfTimeSync(CCurrentTimeField *pCurrTime,const TSessionRef &sessionRef,CTransaction *pTransaction);
protected:
	bool isDuplicate(CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID);

	bool suitableTime(void);

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
private:
	CConfig *m_Config;
	CMemoryDB *m_DB;
	CErrorEngine *m_ErrorEngine;

	map<CDbmtTopicIDType,CDbmtSequenceIDType> m_lastSeqMap;

	CTransaction m_Transaction;
	CFlow *m_pSendFlow;

	typedef set<string> CPartGroupPosition;
	CPartGroupPosition m_PartGroupPosition;
	CPosiMap m_PosiMap;

	CBaseAlgorithms baseAlgorithm;
};

#endif

