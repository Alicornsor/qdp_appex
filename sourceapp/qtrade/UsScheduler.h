/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file UsScheduler.h
///@brief��������CUsScheduler
///@history 
///20130703	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef _MDB_SCHEDULER_H_20130105
#define _MDB_SCHEDULER_H_20130105

#include "EventHandler.h"
#include "Flow.h"
#include "XTPPackage.h"
#include "customDataType.h"

class CUsScheduler
{
public:
	CUsScheduler(CFlow *pMemChangeFlow,CFlow *pResultFlow);
	virtual ~CUsScheduler();
	virtual void Dispatch(const char *pszObjectName, CFieldDescribe *pDescirbe, const void *pData, CMdbActionTypeType nActionType);
	virtual void InvestorAccountDepositNotify(CFieldDescribe *pDescirbe, const void *pData);

private:	
	CXTPPackage	*m_pPubMessage;
	CFlow *m_pMemChangeFlow;

	// longqy 20130909 ���ڳ����ر�
	CFlow *m_pResultFlow;

};

#endif
