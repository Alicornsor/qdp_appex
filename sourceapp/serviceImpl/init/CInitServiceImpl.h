/////////////////////////////////////////////////////////////////////////
///@system ��������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CInitServiceImpl.h
///@brief��������CInitServiceImpl
///@history 
///20130701	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CINITSERVICEIMPL_H
#define CINITSERVICEIMPL_H

#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "XtpData.h"
#include "errorDefine.h"
#include "CMemoryDB.h"
#include "tradingTools.h"
#include "baseAlgorithms.h"
#include "HandleNotify.h"

/////////////////////////////////////////////////////////////////////////
///CInitServiceImpl��һ����ɽ��������ݳ�ʼ����ʵ��
///@author	hwp
///@version	1.0,20130701
/////////////////////////////////////////////////////////////////////////
class CInitServiceImpl
{
public:
	///���캯��
	///@param	pDB	��ʵ��ʹ�õ��ڴ����ݿ�
	///@param	pErrorEngine	���ڱ���Ĵ�������
	CInitServiceImpl(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CHandleNotify *pHandleNotify);

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

	///��ʼ��Ͷ���߽���Ȩ��
	///@param	pInvestorTradingRight	Ҫ��ʼ����Ͷ���߽���Ȩ����Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initInvestorTradingRight(CWriteableInvestorTradingRight *pInvestorTradingRight,const TSessionRef &sessionRef,CTransaction *pTransaction);

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

	///��ʼ��QDPϵͳ��Ϣ��
	///@param	pSystemInfo	Ҫ��ʼ����QDPϵͳ��Ϣ����Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool initSystemInfo(CWriteableSystemInfo *pSystemInfo,const TSessionRef &sessionRef,CTransaction *pTransaction);

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

	///����������ͬ��״̬�л�
	///@param	ExchangeID	���������
	///@param	NewStatus	�µ�״̬
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool DataSyncStatusUpdate(CDataSyncStatusType &NewStatus,const TSessionRef &sessionRef,CTransaction *pTransaction);

	virtual bool RspQryExInstrument(CInstrumentField *pInstrumentField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQryExTradingDay(CExchangeTradingDayField *pExchangeTradingDayField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQryExInvestorPosition(CInvestorPositionField *pInvestorPositionField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQryExMarketData(CMarketDataField *pMarketDataField,const TSessionRef &sessionRef,CTransaction *pTransaction);	
	virtual bool RspQryExCapitalData(CExCapitalDataField *pExCapitalDataField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool RspQueryExCmbInstrumentDetail(CCmbInstrumentDetailField *pCmbInstrumentDetailField,const TSessionRef &sessionRef,CTransaction *pTransaction);
	
protected:
	///����Ƿ񳬼��Ự
	///@param	sessionRef	�Ự����
	///@return	true��ʾ�ǣ�false��ʾ��
	bool isSuperSession(const TSessionRef &sessionRef);
	
	///����������ͬ��ǰ����
	///@param	pTransaction	���������ڵ�����
	virtual void beforeDataSync(CTransaction *pTransaction);
	
	///����������ͬ������
	///@param	pTransaction	���������ڵ�����
	virtual void afterDataSync(CTransaction *pTransaction);
	
protected:
	CConfig *m_Config;
	CMemoryDB *m_DB;
	CErrorEngine *m_ErrorEngine;
	CBaseAlgorithms baseAlgorithm;
	CHandleNotify *m_pHandleNotify;
};

#ifdef DEBUG_NOT_LOG
void increaseCount(void);
#endif

#endif
