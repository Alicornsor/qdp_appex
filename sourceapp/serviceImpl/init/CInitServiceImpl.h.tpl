!!enter XTP!!
!!function!!
int isInitPackage(char *usage)
{
	if (strcmp(usage,"exchangeInit")==0)
	{
		return 1;
	}
	return 0;
}

char *getTableName(char *name)
{
	return name+4;
}
!!endfunction!!
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

!!travel packages!!
!!if isInitPackage(@usage)!!
!!let tableName=getTableName(@name)!!
	///��ʼ��!!@comment!!
	///@param	p!!@tableName!!	Ҫ��ʼ����!!@comment!!��Ϣ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool init!!@tableName!!(CWriteable!!@tableName!! *p!!@tableName!!,const TSessionRef &sessionRef,CTransaction *pTransaction);

!!endif!!
!!next!!
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
	virtual bool RspQryExDiffTime(CExchTimeDiffField *pExchTimeDiffField,const TSessionRef &sessionRef,CTransaction *pTransaction);
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
!!leave!!
