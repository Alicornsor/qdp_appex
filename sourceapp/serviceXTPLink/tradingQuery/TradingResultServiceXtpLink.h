/////////////////////////////////////////////////////////////////////////
///@system ���ٷ��ǰ��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file TradingResultServiceXtpLink.h
///@brief��������TradingResultServiceXtpLink�����㽻�׵Ľ��
///@history 
///20121214	longqy@cffex.net �����ļ�

/////////////////////////////////////////////////////////////////////////

#ifndef TRADINGRESULTSERVICEXTPLINK_H
#define TRADINGRESULTSERVICEXTPLINK_H

#include "ServiceXTPLink.h"
#include "CErrorEngine.h"
#include "CTransaction.h"
#include "LogMemoryDatabaseTable.h"
#include "TradingResultImpl.h"

/////////////////////////////////////////////////////////////////////////
///CTradingResultServiceXtpLink��һ��˵�����ڴ����У����㽻�׽���ķ��������
///@author	Longqy
///@version	1.0,20121214
/////////////////////////////////////////////////////////////////////////

class CTradingResultServiceXtpLink: public IServiceXTPLink
{
public:
///���캯��������һ����ѯ���񣬴���һ�����㽻�׽��������	
CTradingResultServiceXtpLink(CTradingResultImpl *pQueryService,
CErrorEngine *pErrorEngine, IServiceResponser *pServiceResponser, CMemoryDB *pDB, bool verbose, bool md5Password);

	///��������
	virtual ~CTradingResultServiceXtpLink();

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
private:
	void ResponseErrorMsg(CXTPPackage *pPackage,DWORD rspTID,DWORD dwSessionID);
	CTradingResultImpl *m_pTradingResultService;
	CErrorEngine *m_pErrorEngine;
	IServiceResponser *m_pServiceResponser;
	CMemoryDB *m_pDB;
	bool m_verbose;
	CTransaction m_Transaction;	
	CXTPPackage	 *m_pRspMessage;
	bool m_md5Password;
	// CLogMemoryDatabaseTable *m_pLogTable;
};

extern CLogMemoryDatabaseTable	g_logMemoryDBTable;

#endif
