/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �н���������˾
///@file DbmtServiceXtpLink.h
///@brief��������CDbmtServiceXtpLink
///@history 
///20130119	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef DBMTSERVICEXTPLINK_H
#define DBMTSERVICEXTPLINK_H

#include "ServiceXTPLink.h"
#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "XtpPackageDesc.h"
#include "CErrorEngine.h"
#include "CTransaction.h"
#include "Flow.h"
#include "CDbmtServiceImpl.h"

/////////////////////////////////////////////////////////////////////////
///CDbmtServiceXtpLink��һ��˵�����ڴ����е�Dbmt���������
///@author	hwp
///@version	1.0,20130119
/////////////////////////////////////////////////////////////////////////
class CDbmtServiceXtpLink: public IServiceXTPLink
{
public:
	///���캯��������һ��Dbmt���񣬴���һ���ڴ����е�����
	///@param	ppDbmtService	ָ����dbmt����
	///@param	pErrorEngine	���ڷ��ش��������
	///@param	verbose	true��ʾ��Ҫ��������flase��ʾ����������
	CDbmtServiceXtpLink(CDbmtServiceImpl *pDbmtService,CErrorEngine *pErrorEngine,
						IServiceResponser *pServiceResponser,CFlow* pTradeResult, bool verbose=true);
	
	///��������
	virtual ~CDbmtServiceXtpLink();

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
	CDbmtServiceImpl *m_pService;
	CErrorEngine *m_pErrorEngine;
	IServiceResponser *m_pServiceResponser;
	bool m_verbose;
	CTransaction m_Transaction;	
	CXTPPackage	 *m_pRspMessage;
	CFlow* m_pTradeResult;
};

#endif
