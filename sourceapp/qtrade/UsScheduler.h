/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file UsScheduler.h
///@brief定义了类CUsScheduler
///@history 
///20130703	hwp		创建该文件
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

	// longqy 20130909 用于出入金回报
	CFlow *m_pResultFlow;

};

#endif
