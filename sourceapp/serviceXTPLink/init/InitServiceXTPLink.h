/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file InitServiceMemoryLink.h
///@brief��������CInitServiceMemoryLink
///@history 
///20130701	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef INITSERVICEXTPLINK_H
#define INITSERVICEXTPLINK_H

#include "ServiceXTPLink.h"
#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "XtpData.h"
#include "CErrorEngine.h"
#include "CTransaction.h"
#include "Flow.h"
#include "CInitServiceImpl.h"

/////////////////////////////////////////////////////////////////////////
///CInitServiceMemoryLink��һ��˵��ʹ��XTP��Init���������
///@author	hwp
///@version	1.0,20130701
/////////////////////////////////////////////////////////////////////////
class CInitServiceXTPLink: public IServiceXTPLink
{
public:
	///���캯��������һ��������init���񣬴���һ��ʹ��XTP������
	///@param	pInitService	ָ���Ľ�����init����
	///@param	pErrorEngine	���ڷ��ش��������
	///@param	verbose	true��ʾ��Ҫ��������flase��ʾ����������
	CInitServiceXTPLink(CInitServiceImpl *pInitService,CErrorEngine *pErrorEngine,IServiceResponser *pServiceResponser,CFlow* pTradeResult,bool verbose=true);
	
	virtual ~CInitServiceXTPLink();

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
	
	//virtual void setFlow(CFlow *pFlow);
private:
	CInitServiceImpl *m_pInitService;
	CErrorEngine *m_pErrorEngine;
	bool m_verbose;
	CTransaction m_Transaction;
	CXTPPackage	 *m_pRspMessage;
	IServiceResponser *m_pServiceResponser;
	CFlow* m_pTradeResult;
};

#endif
