/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file TradingQueryServiceXtpLink.h
///@brief��������CDbmtServiceXtpLink
///@history 
///20060119	xuzh		�������ļ�
///20090118	xuzh		�����˲�ѯ����־��NT-0065��
/////////////////////////////////////////////////////////////////////////

#ifndef TRADINGQUERYSERVICEXTPLINK_H
#define TRADINGQUERYSERVICEXTPLINK_H

#include "ServiceXTPLink.h"
#include "CErrorEngine.h"
#include "CTransaction.h"
#include "XtpData.h"

#include "LogMemoryDatabaseTable.h"
#include "QueryComplianceParam.h"
#include "baseAlgorithms.h"
#include "TradingQueryServiceImpl.h"

typedef map<CExchangeIDType, int> CExchangeMap;
/////////////////////////////////////////////////////////////////////////
///CTradingQueryServiceXtpLink��һ��˵�����ڴ����еĽ��ײ�ѯ���������
///@author	xuzh
///@version	1.0,20060119
/////////////////////////////////////////////////////////////////////////
class CTradingQueryServiceXtpLink: public IServiceXTPLink
{
public:
	///���캯��������һ����ѯ���񣬴���һ���ڴ����е�����
	///@param	pQueryService	ָ����dbmt����
	///@param	pErrorEngine	���ڷ��ش��������
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	///@param	verbose	true��ʾ��Ҫ��������flase��ʾ����������
	CTradingQueryServiceXtpLink(CTradingQueryImpl *pQueryService,CErrorEngine *pErrorEngine,
						IServiceResponser *pServiceResponser, CMemoryDB *pDB, bool verbose=true);
	
	///��������
	virtual ~CTradingQueryServiceXtpLink();

	///����һ��XTP��
	///@param	pPackage	Ҫ�����XTP��
	///@param	sessionRef	�Ự����
	///@return	true��ʾ����ɹ���false��ʾ����ʧ��
	virtual bool handleMessage(CXTPPackage *pPackage, const TSessionRef &sessionRef);

	///����һ��XTP����
	///@param	pPackage	Ҫ�����XTP��
	///@param	sessionRef	�Ự����
	///@return	true��ʾ����ɹ���false��ʾ����ʧ��
	virtual bool handleRequest(CXTPPackage *pPackage,const TSessionRef &sessionRef,DWORD dwReponseSession);
	virtual bool copyInvestorPositionField(CInvestorPositionField *pClientField,CInvestorPositionField *pInvestorField,CInvestorIDType &investorID);
	
private:
	//��������Ĳ�ѯ����
	bool QueryInvestorFee(CXTPPackage *pPackage,CQryInvestorFeeField &field,DWORD ResponseSessionID);
	bool QueryInvestorFeeEach(CInvestorIDType &InvestorID,CXTPPackage *pPackage,CQryInvestorFeeField &field,DWORD ResponseSessionID);

	bool QueryInvestorOptionFee(CXTPPackage *pPackage,CQryInvestorOptionFeeField &field,DWORD ResponseSessionID);
	bool QueryInvestorOptionFeeEach(CInvestorIDType &InvestorID,CXTPPackage *pPackage,CQryInvestorOptionFeeField &field,DWORD ResponseSessionID);
	
	bool QueryInvestorMargin(CXTPPackage *pPackage,CQryInvestorMarginField &field,DWORD ResponseSessionID);
	bool QueryInvestorMarginEach(CInvestorIDType &InvestorID,CXTPPackage *pPackage,CQryInvestorMarginField &field,DWORD ResponseSessionID);

	bool QuerySeatInfo(CXTPPackage *pPackage,CQrySeatInfoField &field,DWORD ResponseSessionID);

	void AddtoFlow(CXTPPackage *pPackage,const TSessionRef& sessionRef,DWORD ResponseSessionID);
	void FlushPackage(bool bLast, DWORD nSessionID);
	bool getClientIDsFromInvestorIDs(CQryInvestorPositionField &invPositionField,ClientIDVector **pVector,const TSessionRef &sessionRef,CTransaction *pTransaction);	
	///�����ѯ��־
	///@param	sessionRef	�Ự��ʶ
	///@param	startTime	��ʼ��ѯʱ�䣬�Ժ����
	///@param	endTime	������ѯʱ�䣬�Ժ����
	///@param	queryInfo	��ѯ��Ϣ
	void ResponseErrorMsg(CXTPPackage *pPackage,DWORD rspTID,DWORD dwSessionID);

	void ResponseNullMsg(CXTPPackage *pPackage,DWORD rspTID,DWORD dwSessionID);
	
	CTradingQueryImpl *m_pService;
	CErrorEngine *m_pErrorEngine;
	IServiceResponser *m_pServiceResponser;
	CMemoryDB *m_pDB;
	bool m_verbose;
	CTransaction m_Transaction;	
	CXTPPackage	 *m_pRspMessage;
	CBaseAlgorithms baseAlgorithm;
	CExchangeInvestorID2ClientIDMap m_mapClientID;
	CExchangeMap m_ExchangeMap;
	char tmp[100];
};

extern CLogMemoryDatabaseTable	g_logMemoryDBTable;

#endif
