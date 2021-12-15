/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file UsScheduler.cpp
///@brief实现了类CUsScheduler
///@history 
///20130703	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "public.h"
#include "UsScheduler.h"
#include "XtpPackageDesc.h"

CUsScheduler::CUsScheduler(CFlow *pMemChangeFlow, CFlow *pResultFlow)
{
	m_pPubMessage = new CXTPPackage();
	m_pPubMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	m_pPubMessage->PreparePublish(TID_NtfMemtableChange);

	// longqy 20130910 原来只有一个流对象，发送内存数据库变化的表。现添加一个流对象，发送出入金通知给前置。
	m_pMemChangeFlow = pMemChangeFlow;
	m_pResultFlow=pResultFlow;
}

CUsScheduler::~CUsScheduler()
{
	if(m_pPubMessage!=NULL)
	{
		delete m_pPubMessage;
		m_pPubMessage=NULL;
	}
}

void CUsScheduler::Dispatch(const char *pszObjectName, CFieldDescribe *pDescirbe, const void *pData, CMdbActionTypeType nActionType)
{
	CMemtableChangeField fld;
	fld.MemTableName=pszObjectName;//操作内存表
	//数据变化类型
	switch(nActionType)
	{
		case MDB_INSERT:
		{
			fld.MemtableChangeType=MTC_INSERT;
			break;
		}
		case MDB_UPDATE:
		{
			fld.MemtableChangeType=MTC_UPDATE;
			break;
		}
		case MDB_DELETE:
		{
			fld.MemtableChangeType=MTC_DELETE;
			break;
		}
		case MDB_COMMIT:
		{
			fld.MemtableChangeType=MTC_COMMIT;
			break;
		}
		default:
		{
			//严重错误，不支持的数据库操作类型
			printf("不支持的变化类型\n");
			return;
		}
	}	
	m_pPubMessage->PreparePublish(TID_NtfMemtableChange);
	XTP_ADD_FIELD(m_pPubMessage,&fld);
	m_pPubMessage->AddField(pDescirbe,(void *)pData);//增加可变消息域
	m_pPubMessage->MakePackage();
	//m_pResultFlow->Append(m_pPubMessage->Address(),m_pPubMessage->Length());
	// longqy 20130910 实际上原来就是内存流，这次只是修改了传入参数的名字
	m_pMemChangeFlow->Append(m_pPubMessage->Address(),m_pPubMessage->Length());
}

/*	把出入金通知发送到结果流（内存流）中去，这样前置模块收到这个流，就可以发送给客户。
//	这个函数由触发器 CUsDepositTrigger 调用。
//	longqy 20130904
*/
void CUsScheduler::InvestorAccountDepositNotify(CFieldDescribe *pDescirbe, const void *pData)
{
	int nSeqNo = 0;
	m_pPubMessage->PreparePublish(TID_NtfInvestorAccountDeposit);
	m_pPubMessage->AddField(pDescirbe,(void *)pData);//增加可变消息域
	m_pPubMessage->MakePackage();
	nSeqNo = m_pResultFlow->Append(m_pPubMessage->Address(),m_pPubMessage->Length());
	if(nSeqNo < 0 )
	{  
		REPORT_EVENT(LOG_CRITICAL,"CUsScheduler::InvestorAccountDepositNotify", "Can not Append To ResultFlow");
	}
}