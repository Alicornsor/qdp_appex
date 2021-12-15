/////////////////////////////////////////////////////////////////////////
///@system 极速风控前置系统
///@company 上海量投网络科技有限公司
///@file TradingResultServiceXtpLink.cpp
///@brief定义了类TradingResultServiceXtpLink，计算交易的结果
///@history 
///20121214	longqy@cffex.net 创建文件

/////////////////////////////////////////////////////////////////////////
#include "TradingResultServiceXtpLink.h"
#include "XtpPackageDesc.h"
#include "UFCopy.h"
#include "cryptUtility.h"
//#include "tradingTools.h"

#define DBMT_BUF_LEN 3900

CTradingResultServiceXtpLink::CTradingResultServiceXtpLink(CTradingResultImpl 
					*pQueryService,CErrorEngine *pErrorEngine,IServiceResponser *pServiceResponser, CMemoryDB *pDB, bool verbose, bool md5Password)
{
	m_pTradingResultService=pQueryService;
	m_pErrorEngine=pErrorEngine;
	m_pServiceResponser = pServiceResponser;
	m_pDB = pDB;
	m_verbose=verbose;
	m_pRspMessage = new CXTPPackage;
	m_pRspMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	if (! g_logMemoryDBTable.canLog())
	{
		g_logMemoryDBTable.init();
	}
	m_md5Password = md5Password;
}					

CTradingResultServiceXtpLink::~CTradingResultServiceXtpLink()
{
	if(m_pRspMessage != NULL)
		m_pRspMessage->Release();
	delete m_pRspMessage;
}

void CTradingResultServiceXtpLink::ResponseErrorMsg(CXTPPackage *pPackage,DWORD rspTID,DWORD dwSessionID)
{
	CRspInfoField responseField;
	char* errMsg;
	int errorCode;
	m_pErrorEngine->getLastError(&errorCode,&errMsg);
	responseField.ErrorID = errorCode;
	responseField.ErrorMsg = errMsg;
	m_pRspMessage->PrepareResponse(pPackage, rspTID);
	XTP_ADD_FIELD(m_pRspMessage,&responseField);
	m_pServiceResponser->SendResponse(m_pRspMessage,dwSessionID);
}

bool CTradingResultServiceXtpLink::handleMessage(CXTPPackage *pPackage, const TSessionRef &sessionRef)
{
	char buffer[3900];
	memset(buffer,0,3900);
	bool success=true;
	char* errMsg="";
	int errorCode=0;
	switch (pPackage->GetTid())
	{
	case TID_InitExchange:
	{
		CExchangeField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableExchange theExchange;
			theExchange.init();			
			it.Retrieve(&field);
			CopyExchangeEntity(&theExchange,&field);
			///检查基本字段是否合法
			if (theExchange.isValid())
			{
				success=m_pTradingResultService->initExchange(&theExchange,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theExchange) < 3900)
				{
					theExchange.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitExchange is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitSeat:
	{
		CSeatField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableSeat theSeat;
			theSeat.init();			
			it.Retrieve(&field);
			CopySeatEntity(&theSeat,&field);
			///检查基本字段是否合法
			if (theSeat.isValid())
			{
				success=m_pTradingResultService->initSeat(&theSeat,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theSeat) < 3900)
				{
					theSeat.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitSeat is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitUser:
	{
		CUserField field;
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
				success=m_pTradingResultService->initUser(&theUser,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theUser) < 3900)
				{
					theUser.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitUser is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitInvestor:
	{
		CInvestorField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableInvestor theInvestor;
			theInvestor.init();			
			it.Retrieve(&field);
			CopyInvestorEntity(&theInvestor,&field);
			///检查基本字段是否合法
			if (theInvestor.isValid())
			{
				success=m_pTradingResultService->initInvestor(&theInvestor,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theInvestor) < 3900)
				{
					theInvestor.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitInvestor is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitClientTradingID:
	{
		CClientTradingIDField field;
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
				success=m_pTradingResultService->initClientTradingID(&theClientTradingID,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theClientTradingID) < 3900)
				{
					theClientTradingID.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitClientTradingID is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitUserInvestor:
	{
		CUserInvestorField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableUserInvestor theUserInvestor;
			theUserInvestor.init();			
			it.Retrieve(&field);
			CopyUserInvestorEntity(&theUserInvestor,&field);
			///检查基本字段是否合法
			if (theUserInvestor.isValid())
			{
				success=m_pTradingResultService->initUserInvestor(&theUserInvestor,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theUserInvestor) < 3900)
				{
					theUserInvestor.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitUserInvestor is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitUserTradingRight:
	{
		CUserTradingRightField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableUserTradingRight theUserTradingRight;
			theUserTradingRight.init();			
			it.Retrieve(&field);
			CopyUserTradingRightEntity(&theUserTradingRight,&field);
			///检查基本字段是否合法
			if (theUserTradingRight.isValid())
			{
				success=m_pTradingResultService->initUserTradingRight(&theUserTradingRight,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theUserTradingRight) < 3900)
				{
					theUserTradingRight.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitUserTradingRight is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitInvestorAccount:
	{
		CInvestorAccountField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableInvestorAccount theInvestorAccount;
			theInvestorAccount.init();			
			it.Retrieve(&field);
			CopyInvestorAccountEntity(&theInvestorAccount,&field);
			///检查基本字段是否合法
			if (theInvestorAccount.isValid())
			{
				success=m_pTradingResultService->initInvestorAccount(&theInvestorAccount,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theInvestorAccount) < 3900)
				{
					theInvestorAccount.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitInvestorAccount is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitInstrument:
	{
		CInstrumentField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableInstrument theInstrument;
			theInstrument.init();			
			it.Retrieve(&field);
			CopyInstrumentEntity(&theInstrument,&field);
			///检查基本字段是否合法
			if (theInstrument.isValid())
			{
				success=m_pTradingResultService->initInstrument(&theInstrument,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theInstrument) < 3900)
				{
					theInstrument.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitInstrument is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitInvestorMargin:
	{
		CInvestorMarginField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableInvestorMargin theInvestorMargin;
			theInvestorMargin.init();			
			it.Retrieve(&field);
			CopyInvestorMarginEntity(&theInvestorMargin,&field);
			///检查基本字段是否合法
			if (theInvestorMargin.isValid())
			{
				success=m_pTradingResultService->initInvestorMargin(&theInvestorMargin,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theInvestorMargin) < 3900)
				{
					theInvestorMargin.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitInvestorMargin is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitInvestorFee:
	{
		CInvestorFeeField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableInvestorFee theInvestorFee;
			theInvestorFee.init();			
			it.Retrieve(&field);
			CopyInvestorFeeEntity(&theInvestorFee,&field);
			///检查基本字段是否合法
			if (theInvestorFee.isValid())
			{
				success=m_pTradingResultService->initInvestorFee(&theInvestorFee,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theInvestorFee) < 3900)
				{
					theInvestorFee.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitInvestorFee is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitInvestorPosition:
	{
		CInvestorPositionField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableInvestorPosition theInvestorPosition;
			theInvestorPosition.init();			
			it.Retrieve(&field);
			CopyInvestorPositionEntity(&theInvestorPosition,&field);
			///检查基本字段是否合法
			if (theInvestorPosition.isValid())
			{
				success=m_pTradingResultService->initInvestorPosition(&theInvestorPosition,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theInvestorPosition) < 3900)
				{
					theInvestorPosition.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitInvestorPosition is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitSystemStatus:
	{
		CSystemStatusField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableSystemStatus theSystemStatus;
			theSystemStatus.init();			
			it.Retrieve(&field);
			CopySystemStatusEntity(&theSystemStatus,&field);
			///检查基本字段是否合法
			if (theSystemStatus.isValid())
			{
				success=m_pTradingResultService->initSystemStatus(&theSystemStatus,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theSystemStatus) < 3900)
				{
					theSystemStatus.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitSystemStatus is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitInstrumentGroup:
	{
		CInstrumentGroupField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableInstrumentGroup theInstrumentGroup;
			theInstrumentGroup.init();			
			it.Retrieve(&field);
			CopyInstrumentGroupEntity(&theInstrumentGroup,&field);
			///检查基本字段是否合法
			if (theInstrumentGroup.isValid())
			{
				success=m_pTradingResultService->initInstrumentGroup(&theInstrumentGroup,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theInstrumentGroup) < 3900)
				{
					theInstrumentGroup.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitInstrumentGroup is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitClientMarginCombType:
	{
		CClientMarginCombTypeField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableClientMarginCombType theClientMarginCombType;
			theClientMarginCombType.init();			
			it.Retrieve(&field);
			CopyClientMarginCombTypeEntity(&theClientMarginCombType,&field);
			///检查基本字段是否合法
			if (theClientMarginCombType.isValid())
			{
				success=m_pTradingResultService->initClientMarginCombType(&theClientMarginCombType,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theClientMarginCombType) < 3900)
				{
					theClientMarginCombType.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitClientMarginCombType is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitSGEDeferRate:
	{
		CSGEDeferRateField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableSGEDeferRate theSGEDeferRate;
			theSGEDeferRate.init();			
			it.Retrieve(&field);
			CopySGEDeferRateEntity(&theSGEDeferRate,&field);
			///检查基本字段是否合法
			if (theSGEDeferRate.isValid())
			{
				success=m_pTradingResultService->initSGEDeferRate(&theSGEDeferRate,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theSGEDeferRate) < 3900)
				{
					theSGEDeferRate.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitSGEDeferRate is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitCmbInstrumentDetail:
	{
		CCmbInstrumentDetailField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableCmbInstrumentDetail theCmbInstrumentDetail;
			theCmbInstrumentDetail.init();			
			it.Retrieve(&field);
			CopyCmbInstrumentDetailEntity(&theCmbInstrumentDetail,&field);
			///检查基本字段是否合法
			if (theCmbInstrumentDetail.isValid())
			{
				success=m_pTradingResultService->initCmbInstrumentDetail(&theCmbInstrumentDetail,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theCmbInstrumentDetail) < 3900)
				{
					theCmbInstrumentDetail.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitCmbInstrumentDetail is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitUserIP:
	{
		CUserIPField field;
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
				success=m_pTradingResultService->initUserIP(&theUserIP,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theUserIP) < 3900)
				{
					theUserIP.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitUserIP is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_InitInvestorOptionFee:
	{
		CInvestorOptionFeeField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableInvestorOptionFee theInvestorOptionFee;
			theInvestorOptionFee.init();			
			it.Retrieve(&field);
			CopyInvestorOptionFeeEntity(&theInvestorOptionFee,&field);
			///检查基本字段是否合法
			if (theInvestorOptionFee.isValid())
			{
				success=m_pTradingResultService->initInvestorOptionFee(&theInvestorOptionFee,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theInvestorOptionFee) < 3900)
				{
					theInvestorOptionFee.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitInvestorOptionFee is invalid for %s",buffer);
				success = false;
				m_pErrorEngine->reportError(ERROR_BAD_ORDER_FIELD);
			}
			it.Next();
		}
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_DataSyncStart:
	{
		CTradingDayField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		it.Retrieve(&field);
		success=m_pTradingResultService->DataSyncStart(field.TradingDay,sessionRef,&m_Transaction);
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_DataSyncEnd:
	{
		CTradingDayField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		it.Retrieve(&field);
		success=m_pTradingResultService->DataSyncEnd(field.TradingDay,sessionRef,&m_Transaction);
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}	
	//报盘机查询合约后的通知信息，需要以这种形式给Kernel
	case TID_RspQueryExInstrument:
	{
		//查询成功，取出合约信息，更新内存表
		CInstrumentField field;			
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			it.Retrieve(&field);
			m_pTradingResultService->RspQryExInstrument(&field,sessionRef,&m_Transaction);
			it.Next();
		}
		break;
	}
	//报盘机发送的交易所-交易日的查询应答
	case TID_RspQueryExTradingDay:
	{
		CExchangeTradingDayField field;	
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			it.Retrieve(&field);
			m_pTradingResultService->RspQryExTradingDay(&field,sessionRef,&m_Transaction);
			it.Next();
		}
		break;
	}
	//报盘机发送的客户持仓查询应答
	case TID_RspQueryExInvestorPosition:
	{
		CInvestorPositionField field;	
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			it.Retrieve(&field);
			m_pTradingResultService->RspQryExInvestorPosition(&field,sessionRef,&m_Transaction);
			it.Next();
		}		
		break;
	}
	//报盘机发送的行情查询应答
	case TID_RspQueryExMarketData:
	{
		CMarketDataField field;	
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			it.Retrieve(&field);
			m_pTradingResultService->RspQryExMarketData(&field,sessionRef,&m_Transaction);
			it.Next();
		}
		break;
	}
	//报盘机发送的资金查询应答
	case TID_RspQueryExCapitalData:
	{
		CExCapitalDataField field;	
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			it.Retrieve(&field);
			m_pTradingResultService->RspQryExCapitalData(&field,sessionRef,&m_Transaction);
			it.Next();
		}
		break;
	}
	//报盘机查询组合合约明细应答
	case TID_RspQueryExCmbInstrumentDetail:
	{
		CCmbInstrumentDetailField field;	
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			it.Retrieve(&field);
			m_pTradingResultService->RspQueryExCmbInstrumentDetail(&field,sessionRef,&m_Transaction);
			it.Next();
		}
		break;
	}
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
				success=m_pTradingResultService->SyncInvestorAccountDeposit(&theInvestorAccountDeposit,&resFld,field.DbmtTopicID,field.DbmtSequenceID,sessionRef,&m_Transaction);
				if ( !success )
				{
					errorCode = atoi(theInvestorAccountDeposit.AccountInsideSeqNo.getValue());
				}
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
					success = m_pTradingResultService->UserUpdate(&field,&m_Transaction);
					if (!success)
					{
						errorCode = ERROR_BAD_ACCOUNT_DEPOSIT_FIELD;
					}
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
					success=m_pTradingResultService->SyncClientTradingID(&theClientTradingID,field.DbmtTopicID,field.DbmtSequenceID,sessionRef,&m_Transaction);
					if (!success)
					{
						errorCode = ERROR_BAD_ACCOUNT_DEPOSIT_FIELD;
					}
				}
				it.Next();
			}
			m_pErrorEngine->getLastError(&errorCode,&errMsg);
		}
	break;
	case  TID_NtfOrder:
	{
		COrderField field;
		XTP_GET_SINGLE_FIELD(pPackage,&field);			
		success = m_pTradingResultService->OnRtnOrder(&field,sessionRef,&m_Transaction);	
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break; 
	}
	case  TID_NtfTrade:
	{
		CTradeField tradeField;
		XTP_GET_SINGLE_FIELD(pPackage,&tradeField);
		success = m_pTradingResultService->OnRtnTrade(&tradeField,sessionRef,&m_Transaction);
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}	
	case TID_RspOrderAction:
		{
			CRspInfoField exRspInfoField;
			COrderActionField orderActionField;
			XTP_GET_SINGLE_FIELD(pPackage,&exRspInfoField);
			XTP_GET_SINGLE_FIELD(pPackage,&orderActionField);
	
			COrderField order;
			CWriteableOrderAction theOrderAction;
			theOrderAction.init();
			success = m_pTradingResultService->RspOrderAction(&order,&theOrderAction,&orderActionField,&exRspInfoField,sessionRef,&m_Transaction);			
			break;
		}			//新增指令，用于导出内存表，供测试使用 by wangwei,20130114
	case TID_ReqDumpMemDb:
		{
			REPORT_EVENT(LOG_CRITICAL,"CTradeServiceXTPLink", "导出内存表!");
			m_pTradingResultService->DumpDebugInfo(sessionRef,&m_Transaction);
			break;
		}
	//这了的改变主要是合约下场成功之后，后续动作的完善
	case TID_UpdateSystemStatus:
		{
			CSystemStatusField field;
			XTP_GET_SINGLE_FIELD(pPackage,&field);
			//入库
			success = m_pTradingResultService->UpdateSystemStatus(&field,sessionRef,&m_Transaction);
			break;
		}
	case TID_QueryBaseFinish:
		{
			CQueryFinishNotifyField field;
			XTP_GET_SINGLE_FIELD(pPackage,&field);
			//计算大边保证金
			//查询结束之后，需要计算大边保证金情况
			m_pTradingResultService->BuildInsGroupPosition(field.ExchangeID);
			break;
		}
    case  TID_NtfInstrumentStatusUpdate:
		{			
			CInstrumentStatusField field;			
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
			while(!it.IsEnd())
			{
				it.Retrieve(&field);
				success = m_pTradingResultService->NtfInstrumentStatusUpdate(&field,pPackage->GetNoReplayFlag(),sessionRef,&m_Transaction);
				it.Next();
			}		
			break;
		}
	case TID_NtfSGEDeferRate:
		{
			CSGEDeferRateField field;
			XTP_GET_SINGLE_FIELD(pPackage,&field);
			
			//业务处理
			success = m_pTradingResultService->NtfSGEDeferRate(&field,sessionRef,&m_Transaction);
			break;
		}
	case TID_NtfTimeSync:
		{
			CCurrentTimeField timeField;
			XTP_GET_SINGLE_FIELD(pPackage,&timeField);
			success=m_pTradingResultService->NtfTimeSync(&timeField,sessionRef,&m_Transaction);
			break;
		}
	case  TID_RspUserLogin:
		{
			CUserLoginField userLogInField;
			CRspInfoField	   info;
			XTP_GET_SINGLE_FIELD(pPackage,&userLogInField);
			XTP_GET_SINGLE_FIELD(pPackage,&info);

			if (info.ErrorID ==0 && userLogInField.SessionID !=0)
			{
				CUserSession *pUserSession = m_pDB->m_UserSessionFactory->findBySessionIDFrontID(userLogInField.SessionID,userLogInField.FrontID);
				if (pUserSession == NULL)
				{
					CWriteableUserSession wtbUserSession;
					wtbUserSession.init();
					CopyUserSessionEntity(&wtbUserSession,&userLogInField);
					success = m_pDB->m_UserSessionFactory->add(&wtbUserSession,&m_Transaction) != NULL;
				}
			}
			break;
		}
	case  TID_RspUserLogout:
		{
			CUserLogoutField userLogoutField;
			CRspInfoField	 info;
			XTP_GET_SINGLE_FIELD(pPackage,&userLogoutField);
			XTP_GET_SINGLE_FIELD(pPackage,&info);
			
			if (info.ErrorID ==0 && userLogoutField.SessionID !=0)
			{
				CUserSession *pUserSession = m_pDB->m_UserSessionFactory->findBySessionIDFrontID(userLogoutField.SessionID,userLogoutField.FrontID);
				if (pUserSession != NULL)
				{
					m_pDB->m_UserSessionFactory->remove(pUserSession,&m_Transaction);
				}
			}
			break;
		}
	case  TID_RspUserPasswordUpdate:
		{
			CUserPasswordUpdateField field;
			CRspInfoField	   info;
			XTP_GET_SINGLE_FIELD(pPackage,&field);
			XTP_GET_SINGLE_FIELD(pPackage,&info);
			
			if (info.ErrorID ==0)
			{
				CUser *pUser = m_pDB->m_UserFactory->findByBrokerIDUserID(field.BrokerID,field.UserID);
				if (pUser != NULL)
				{
					CWriteableUser wtbUser;
					m_pDB->m_UserFactory->retrieve(pUser,&wtbUser);
					if (m_md5Password)
					{
						char md5Password[40];
						MD5Hex(md5Password,field.UserID,field.NewPassword);
						wtbUser.Password=md5Password;
					}
					else
					{
						wtbUser.Password =field.NewPassword;
					}
					m_pDB->m_UserFactory->update(pUser,&wtbUser,&m_Transaction);
				}
			}
			break;
		}
	case TID_InitSystemInfo:
		{
			CSystemInfoField field;
			XTP_GET_SINGLE_FIELD(pPackage,&field);
			
			CSystemInfo *pSystemInfo = m_pDB->m_SystemInfoFactory->findBySystemID(field.SystemID);
			if (pSystemInfo == NULL)
			{
				CWriteableSystemInfo wtbSystemInfo;
				wtbSystemInfo.init();
				CopySystemInfoEntity(&wtbSystemInfo,&field);
				m_pDB->m_SystemInfoFactory->add(&wtbSystemInfo,&m_Transaction);
			}
			break;
		}
		//报盘机发送的交易时间偏差查询应答
	case TID_RspQueryExchDiffTime:
		{
			CExchTimeDiffField field;	
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
			while(!it.IsEnd())
			{
				it.Retrieve(&field);
				m_pTradingResultService->RspQryExDiffTime(&field,sessionRef,&m_Transaction);
				it.Next();
			}
			break;
		}
	default:
		return true;
	}
	if (success)		
		m_Transaction.commit();
	else
		m_Transaction.rollback();
	return success;
}

bool CTradingResultServiceXtpLink::handleRequest(CXTPPackage *pPackage, const TSessionRef &sessionRef,DWORD ResponseSessionID)						
{
	return true;
}

