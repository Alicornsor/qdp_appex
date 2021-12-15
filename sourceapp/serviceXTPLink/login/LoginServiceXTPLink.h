/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file LoginServiceXTPLink.h
///@brief��������CLoginServiceXTPLink
///@history 
///20130701	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef LOGINSERVICEXTPLINK_H
#define LOGINSERVICEXTPLINK_H

#include "ServiceXTPLink.h"
#include "IServiceInterface.h"
#include "databaseData.h"
#include "CTransaction.h"
#include "CErrorEngine.h"
#include "CTransaction.h"
#include "monitorIndex.h"
#include "Flow.h"
#include "LoginServiceImpl.h"

/////////////////////////////////////////////////////////////////////////
///CLoginServiceMemoryLink��һ��˵�����ڴ����е�Login���������
///@author	hwp
///@version	1.0,20130701
/////////////////////////////////////////////////////////////////////////

class CLoginServiceXTPLink : public IServiceXTPLink
{
public:
	///���캯��������һ��login���񣬴���һ���ڴ����е�����
	///@param	pLoginService	ָ����trade����
	///@param	pErrorEngine	���ڷ��ش��������
	///@param	verbose	true��ʾ��Ҫ��������flase��ʾ����������
	CLoginServiceXTPLink(CLoginServiceImpl *pLoginService,CErrorEngine *pErrorEngine,IServiceResponser *pServiceResponser,bool verbose=true);
	
	///��������
	virtual ~CLoginServiceXTPLink();

	///����һ��XTP��
	///@param	pPackage	Ҫ�����XTP��
	///@param	sessionRef	�Ự����
	///@return	true��ʾ����ɹ���false��ʾ����ʧ��
	virtual bool handleMessage(CXTPPackage *pPackage,  const TSessionRef &sessionRef);

	///����һ��XTP����
	///@param	pPackage	Ҫ�����XTP��
	///@param	sessionRef	�Ự����
	///@return	true��ʾ����ɹ���false��ʾ����ʧ��
	virtual bool handleRequest(CXTPPackage *pPackage,const TSessionRef &sessionRef,DWORD dwReponseSession);
	
private:
	CLoginServiceImpl *m_pLoginService;
	CErrorEngine *m_pErrorEngine;
	IServiceResponser *m_pServiceResponser;
	bool m_verbose;
	CTransaction m_Transaction;	
	CXTPPackage	 *m_pRspMessage;
};

#endif
