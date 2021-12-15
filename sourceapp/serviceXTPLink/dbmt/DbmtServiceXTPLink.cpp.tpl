!!enter XTP!!
!!function!!
int isDbmtPackage(char *name)
{
	if (!strncmp(name,"dbmt",4))
	{
		return 1;
	}
	return 0;
}

char *getTableName(char *name)
{
	return name+2;
}
!!endfunction!!
#include "DbmtServiceXTPLink.h"
#include "XtpPackageDesc.h"
#include "UFCopy.h"

#define DBMT_BUF_LEN 3900

CDbmtServiceXtpLink::CDbmtServiceXtpLink(CDbmtServiceImpl *pService, CErrorEngine *pErrorEngine,
											IServiceResponser *pServiceResponser,CFlow* pTradeResult, bool verbose)
{
	m_pService=pService;
	m_pErrorEngine=pErrorEngine;
	m_pServiceResponser = pServiceResponser;
	m_verbose=verbose;
	m_pRspMessage = new CXTPPackage;
	m_pRspMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	m_pTradeResult = pTradeResult;	
}

CDbmtServiceXtpLink::~CDbmtServiceXtpLink()
{
	if(m_pRspMessage != NULL)
		m_pRspMessage->Release();
	delete m_pRspMessage;
}

bool CDbmtServiceXtpLink::handleMessage(CXTPPackage *pPackage, const TSessionRef &sessionRef)
{
	char buffer[DBMT_BUF_LEN];
	memset(buffer,0,DBMT_BUF_LEN);
	bool success=true;
	char* errMsg;
	int errorCode;
	switch (pPackage->GetTid())
	{
!!travel packages!!
!!if isDbmtPackage(@usage)!!
!!let tableName=getTableName(@name)!!
!!let msgName=@name!!
!!travel self!!
!!let recordName=@name!!
!!let rowName=@name+4!!
	!!if strcmp(@rowName,"InvestorRight")
	case TID_!!@msgName!!:
	{
		C!!@recordName!!Field field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		
		while(!it.IsEnd())
		{
			CWriteable!!@rowName!! the!!@rowName!!;
			the!!@rowName!!.init();			
			it.Retrieve(&field);
			Copy!!@rowName!!Entity(&the!!@rowName!!,&field);
			!!if (!strcmp("InvestorAccountDeposit",@rowName))!!				
			CAccountDepositResField resFld;
			CopyInvestorAccountDepositEntity(&resFld,&field);
			!!endif!!
			///检查基本字段是否合法
			if (the!!@rowName!!.isValid())
			{
			!!if (!strcmp("InvestorAccountDeposit",@rowName))!!				
				success=m_pService->Sync!!@tableName!!(&the!!@rowName!!,&resFld,field.DbmtTopicID,field.DbmtSequenceID,sessionRef,&m_Transaction);
				if ( !success )
				{
					errorCode = atoi(the!!@rowName!!.AccountInsideSeqNo.getValue());
				}
			!!else
				success=m_pService->Sync!!@tableName!!(&the!!@rowName!!,field.DbmtTopicID,field.DbmtSequenceID,sessionRef,&m_Transaction);
			!!endif!!
			}
			else
			{
				if(sizeof(the!!@rowName!!) < DBMT_BUF_LEN)
				{
					the!!@rowName!!.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"DbmtError","TID_!!@msgName!! is invalid for %s",buffer);
				success = false;
				errorCode = ERROR_BAD_ACCOUNT_DEPOSIT_FIELD;
				//m_pErrorEngine->reportError(ERROR_BAD_ACCOUNT_DEPOSIT_FIELD);
			}
			!!if (!strcmp("InvestorAccountDeposit",@rowName))!!				
			errMsg = m_pErrorEngine->getErrorMsg( errorCode );
			//m_pErrorEngine->getLastError(&errorCode,&errMsg);
			//结果处理，如果是反演，不处理结果
			if (pPackage->GetNoReplayFlag())
			{
				if (field.DbmtSequenceID==0)
				{
					//userapi出入金应答
					CRspInfoField responseField;					
					responseField.ErrorID = errorCode;
					responseField.ErrorMsg = errMsg;
					
					m_pRspMessage->PrepareResponse(pPackage,TID_RspAccountDeposit);					
					XTP_ADD_FIELD(m_pRspMessage,&resFld);
					XTP_ADD_FIELD(m_pRspMessage,&responseField);
					m_pRspMessage->MakePackage();
					if(m_pTradeResult->Append(m_pRspMessage->Address(), m_pRspMessage->Length())<0)
					{
						success=false;				
					}
				}

				//发送出入金通知
				if(success)
				{
					CInvestorAccountDepositNtfField depositField;
					m_pRspMessage->PreparePublish(TID_NtfInvestorAccountDeposit);
					CopyAPIInvestorAccountDepositResEntity(&depositField,&resFld);
					depositField.AccountInsideSeqNo = theInvestorAccountDeposit.AccountInsideSeqNo;
					XTP_ADD_FIELD(m_pRspMessage, &depositField);
					m_pRspMessage->MakePackage();
					if (m_pTradeResult->Append(m_pRspMessage->Address(), m_pRspMessage->Length())<0)
					{
						success=false;
					}				
				}
				
				pPackage->MakeNoBufPackage();
				m_pTradeResult->Append(pPackage->Address(), pPackage->Length());
				pPackage->Pop(XTPHLEN);
			}
			!!endif!!
			!!if strcmp("UpdUser",@tableName)==0 || strcmp("ClientTradingID",@tableName)==0 !!
			if (pPackage->GetNoReplayFlag())
			{			
				pPackage->MakeNoBufPackage();
				m_pTradeResult->Append(pPackage->Address(), pPackage->Length());
				pPackage->Pop(XTPHLEN);
			}
			!!endif!!
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
	}
	break;
	!!endif!!
!!next!!
!!endif!!
!!next!!
	default:
		return true;
	}
	if(success)
		m_Transaction.commit();
	else
		m_Transaction.rollback();
	if(m_verbose)
	{
		if(errorCode == 0)
		{
			//BIZ_OPERATION_LOG0("(OK by dbmt service)\n");
		}
		else
		{
			BIZ_OPERATION_LOG2("(FAILED by dbmt service:%d:%s)\n",errorCode,errMsg);
		}
	}
	return success;
}

bool CDbmtServiceXtpLink::handleRequest(CXTPPackage *pPackage, const TSessionRef &sessionRef,DWORD ResponseSessionID)
{
	return true;
}
