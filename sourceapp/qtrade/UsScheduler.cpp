/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file UsScheduler.cpp
///@briefʵ������CUsScheduler
///@history 
///20130703	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#include "public.h"
#include "UsScheduler.h"
#include "XtpPackageDesc.h"

CUsScheduler::CUsScheduler(CFlow *pMemChangeFlow, CFlow *pResultFlow)
{
	m_pPubMessage = new CXTPPackage();
	m_pPubMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	m_pPubMessage->PreparePublish(TID_NtfMemtableChange);

	// longqy 20130910 ԭ��ֻ��һ�������󣬷����ڴ����ݿ�仯�ı������һ�������󣬷��ͳ����֪ͨ��ǰ�á�
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
	fld.MemTableName=pszObjectName;//�����ڴ��
	//���ݱ仯����
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
			//���ش��󣬲�֧�ֵ����ݿ��������
			printf("��֧�ֵı仯����\n");
			return;
		}
	}	
	m_pPubMessage->PreparePublish(TID_NtfMemtableChange);
	XTP_ADD_FIELD(m_pPubMessage,&fld);
	m_pPubMessage->AddField(pDescirbe,(void *)pData);//���ӿɱ���Ϣ��
	m_pPubMessage->MakePackage();
	//m_pResultFlow->Append(m_pPubMessage->Address(),m_pPubMessage->Length());
	// longqy 20130910 ʵ����ԭ�������ڴ��������ֻ���޸��˴������������
	m_pMemChangeFlow->Append(m_pPubMessage->Address(),m_pPubMessage->Length());
}

/*	�ѳ����֪ͨ���͵���������ڴ�������ȥ������ǰ��ģ���յ���������Ϳ��Է��͸��ͻ���
//	��������ɴ����� CUsDepositTrigger ���á�
//	longqy 20130904
*/
void CUsScheduler::InvestorAccountDepositNotify(CFieldDescribe *pDescirbe, const void *pData)
{
	int nSeqNo = 0;
	m_pPubMessage->PreparePublish(TID_NtfInvestorAccountDeposit);
	m_pPubMessage->AddField(pDescirbe,(void *)pData);//���ӿɱ���Ϣ��
	m_pPubMessage->MakePackage();
	nSeqNo = m_pResultFlow->Append(m_pPubMessage->Address(),m_pPubMessage->Length());
	if(nSeqNo < 0 )
	{  
		REPORT_EVENT(LOG_CRITICAL,"CUsScheduler::InvestorAccountDepositNotify", "Can not Append To ResultFlow");
	}
}