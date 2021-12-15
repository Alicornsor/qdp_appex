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
	case TID_DbInvestorAccountDeposit:
	{
		CDbmtInvestorAccountDepositField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		
		while(!it.IsEnd())
		{
			CWriteableInvestorAccountDeposit theInvestorAccountDeposit;
			theInvestorAccountDeposit.init();			
			it.Retrieve(&field);
			CopyInvestorAccountDepositEntity(&theInvestorAccountDeposit,&field);
			CAccountDepositResField resFld;
			CopyInvestorAccountDepositEntity(&resFld,&field);
			///检查基本字段是否合法
			if (theInvestorAccountDeposit.isValid())
			{
				success=m_pService->SyncInvestorAccountDeposit(&theInvestorAccountDeposit,&resFld,field.DbmtTopicID,field.DbmtSequenceID,sessionRef,&m_Transaction);
				if ( !success )
				{
					errorCode = atoi(theInvestorAccountDeposit.AccountInsideSeqNo.getValue());
				}
			}
			else
			{
				if(sizeof(theInvestorAccountDeposit) < DBMT_BUF_LEN)
				{
					theInvestorAccountDeposit.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"DbmtError","TID_DbInvestorAccountDeposit is invalid for %s",buffer);
				success = false;
				errorCode = ERROR_BAD_ACCOUNT_DEPOSIT_FIELD;
				//m_pErrorEngine->reportError(ERROR_BAD_ACCOUNT_DEPOSIT_FIELD);
			}
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
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
	}
	break;
	case TID_DbInsUser:
	{
		CDbmtUserField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		
		while(!it.IsEnd())
		{
			CWriteableUser theUser;
			theUser.init();			
			it.Retrieve(&field);
			CopyUserEntity(&theUser,&field);
			///检查基本字段是否合法
			if (theUser.isValid())
			{
				success=m_pService->SyncInsUser(&theUser,field.DbmtTopicID,field.DbmtSequenceID,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theUser) < DBMT_BUF_LEN)
				{
					theUser.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"DbmtError","TID_DbInsUser is invalid for %s",buffer);
				success = false;
				errorCode = ERROR_BAD_ACCOUNT_DEPOSIT_FIELD;
				//m_pErrorEngine->reportError(ERROR_BAD_ACCOUNT_DEPOSIT_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
	}
	break;
	case TID_DbUpdUser:
	{
		CDbmtUserField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		
		while(!it.IsEnd())
		{
			CWriteableUser theUser;
			theUser.init();			
			it.Retrieve(&field);
			CopyUserEntity(&theUser,&field);
			///检查基本字段是否合法
			if (theUser.isValid())
			{
				success=m_pService->SyncUpdUser(&theUser,field.DbmtTopicID,field.DbmtSequenceID,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theUser) < DBMT_BUF_LEN)
				{
					theUser.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"DbmtError","TID_DbUpdUser is invalid for %s",buffer);
				success = false;
				errorCode = ERROR_BAD_ACCOUNT_DEPOSIT_FIELD;
				//m_pErrorEngine->reportError(ERROR_BAD_ACCOUNT_DEPOSIT_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
	}
	break;
	case TID_DbClientTradingID:
	{
		CDbmtClientTradingIDField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		
		while(!it.IsEnd())
		{
			CWriteableClientTradingID theClientTradingID;
			theClientTradingID.init();			
			it.Retrieve(&field);
			CopyClientTradingIDEntity(&theClientTradingID,&field);
			///检查基本字段是否合法
			if (theClientTradingID.isValid())
			{
				success=m_pService->SyncClientTradingID(&theClientTradingID,field.DbmtTopicID,field.DbmtSequenceID,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theClientTradingID) < DBMT_BUF_LEN)
				{
					theClientTradingID.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"DbmtError","TID_DbClientTradingID is invalid for %s",buffer);
				success = false;
				errorCode = ERROR_BAD_ACCOUNT_DEPOSIT_FIELD;
				//m_pErrorEngine->reportError(ERROR_BAD_ACCOUNT_DEPOSIT_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
	}
	break;
	case TID_DbUpdInvestorTradingRight:
	{
		CDbmtInvestorTradingRightField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		
		while(!it.IsEnd())
		{
			CWriteableInvestorTradingRight theInvestorTradingRight;
			theInvestorTradingRight.init();			
			it.Retrieve(&field);
			CopyInvestorTradingRightEntity(&theInvestorTradingRight,&field);
			///检查基本字段是否合法
			if (theInvestorTradingRight.isValid())
			{
				success=m_pService->SyncUpdInvestorTradingRight(&theInvestorTradingRight,field.DbmtTopicID,field.DbmtSequenceID,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theInvestorTradingRight) < DBMT_BUF_LEN)
				{
					theInvestorTradingRight.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"DbmtError","TID_DbUpdInvestorTradingRight is invalid for %s",buffer);
				success = false;
				errorCode = ERROR_BAD_ACCOUNT_DEPOSIT_FIELD;
				//m_pErrorEngine->reportError(ERROR_BAD_ACCOUNT_DEPOSIT_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
	}
	break;
	case TID_DbInsInvestorTradingRight:
	{
		CDbmtInvestorTradingRightField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		
		while(!it.IsEnd())
		{
			CWriteableInvestorTradingRight theInvestorTradingRight;
			theInvestorTradingRight.init();			
			it.Retrieve(&field);
			CopyInvestorTradingRightEntity(&theInvestorTradingRight,&field);
			///检查基本字段是否合法
			if (theInvestorTradingRight.isValid())
			{
				success=m_pService->SyncInsInvestorTradingRight(&theInvestorTradingRight,field.DbmtTopicID,field.DbmtSequenceID,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theInvestorTradingRight) < DBMT_BUF_LEN)
				{
					theInvestorTradingRight.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"DbmtError","TID_DbInsInvestorTradingRight is invalid for %s",buffer);
				success = false;
				errorCode = ERROR_BAD_ACCOUNT_DEPOSIT_FIELD;
				//m_pErrorEngine->reportError(ERROR_BAD_ACCOUNT_DEPOSIT_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
	}
	break;
	case TID_DbDelInvestorTradingRight:
	{
		CDbmtInvestorTradingRightField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		
		while(!it.IsEnd())
		{
			CWriteableInvestorTradingRight theInvestorTradingRight;
			theInvestorTradingRight.init();			
			it.Retrieve(&field);
			CopyInvestorTradingRightEntity(&theInvestorTradingRight,&field);
			///检查基本字段是否合法
			if (theInvestorTradingRight.isValid())
			{
				success=m_pService->SyncDelInvestorTradingRight(&theInvestorTradingRight,field.DbmtTopicID,field.DbmtSequenceID,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theInvestorTradingRight) < DBMT_BUF_LEN)
				{
					theInvestorTradingRight.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"DbmtError","TID_DbDelInvestorTradingRight is invalid for %s",buffer);
				success = false;
				errorCode = ERROR_BAD_ACCOUNT_DEPOSIT_FIELD;
				//m_pErrorEngine->reportError(ERROR_BAD_ACCOUNT_DEPOSIT_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
	}
	break;
	case TID_DbUpdUserIP:
	{
		CDbmtUserIPField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		
		while(!it.IsEnd())
		{
			CWriteableUserIP theUserIP;
			theUserIP.init();			
			it.Retrieve(&field);
			CopyUserIPEntity(&theUserIP,&field);
			///检查基本字段是否合法
			if (theUserIP.isValid())
			{
				success=m_pService->SyncUpdUserIP(&theUserIP,field.DbmtTopicID,field.DbmtSequenceID,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theUserIP) < DBMT_BUF_LEN)
				{
					theUserIP.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"DbmtError","TID_DbUpdUserIP is invalid for %s",buffer);
				success = false;
				errorCode = ERROR_BAD_ACCOUNT_DEPOSIT_FIELD;
				//m_pErrorEngine->reportError(ERROR_BAD_ACCOUNT_DEPOSIT_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
	}
	break;
	case TID_DbInsUserIP:
	{
		CDbmtUserIPField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		
		while(!it.IsEnd())
		{
			CWriteableUserIP theUserIP;
			theUserIP.init();			
			it.Retrieve(&field);
			CopyUserIPEntity(&theUserIP,&field);
			///检查基本字段是否合法
			if (theUserIP.isValid())
			{
				success=m_pService->SyncInsUserIP(&theUserIP,field.DbmtTopicID,field.DbmtSequenceID,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theUserIP) < DBMT_BUF_LEN)
				{
					theUserIP.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"DbmtError","TID_DbInsUserIP is invalid for %s",buffer);
				success = false;
				errorCode = ERROR_BAD_ACCOUNT_DEPOSIT_FIELD;
				//m_pErrorEngine->reportError(ERROR_BAD_ACCOUNT_DEPOSIT_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
	}
	break;
	case TID_DbDelUserIP:
	{
		CDbmtUserIPField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		
		while(!it.IsEnd())
		{
			CWriteableUserIP theUserIP;
			theUserIP.init();			
			it.Retrieve(&field);
			CopyUserIPEntity(&theUserIP,&field);
			///检查基本字段是否合法
			if (theUserIP.isValid())
			{
				success=m_pService->SyncDelUserIP(&theUserIP,field.DbmtTopicID,field.DbmtSequenceID,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theUserIP) < DBMT_BUF_LEN)
				{
					theUserIP.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"DbmtError","TID_DbDelUserIP is invalid for %s",buffer);
				success = false;
				errorCode = ERROR_BAD_ACCOUNT_DEPOSIT_FIELD;
				//m_pErrorEngine->reportError(ERROR_BAD_ACCOUNT_DEPOSIT_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
	}
	break;
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
