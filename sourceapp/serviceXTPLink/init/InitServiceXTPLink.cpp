/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company QuantDo Platform
///@file InitServiceMemoryLink.h
///@brief实现了类CInitServiceMemoryLink
///@history 
///20130701	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "InitServiceXTPLink.h"
#include "XtpPackageDesc.h"
#include "UFCopy.h"

CInitServiceXTPLink::CInitServiceXTPLink(CInitServiceImpl *pInitService,
				 CErrorEngine *pErrorEngine,IServiceResponser *pServiceResponser,CFlow* pTradeResult,bool verbose)
{
	m_pInitService=pInitService;
	m_pErrorEngine=pErrorEngine;
	m_pRspMessage = new CXTPPackage;
	m_pRspMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	m_pServiceResponser = pServiceResponser;
	m_verbose=verbose;
	m_pTradeResult = pTradeResult;
}
	
CInitServiceXTPLink::~CInitServiceXTPLink()
{
	if(m_pRspMessage != NULL)
		m_pRspMessage->Release();
	delete m_pRspMessage;
}

bool CInitServiceXTPLink::handleRequest(CXTPPackage *pPackage, const TSessionRef &sessionRef,DWORD responseSession)
{
	return true;
}

bool CInitServiceXTPLink::handleMessage(CXTPPackage *pPackage, const TSessionRef &sessionRef)
{
	//必须初始化，by wangwei,20130116
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
				success=m_pInitService->initExchange(&theExchange,sessionRef,&m_Transaction);
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
				success=m_pInitService->initSeat(&theSeat,sessionRef,&m_Transaction);
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
				success=m_pInitService->initUser(&theUser,sessionRef,&m_Transaction);
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
				success=m_pInitService->initInvestor(&theInvestor,sessionRef,&m_Transaction);
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
				success=m_pInitService->initClientTradingID(&theClientTradingID,sessionRef,&m_Transaction);
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
				success=m_pInitService->initUserInvestor(&theUserInvestor,sessionRef,&m_Transaction);
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
				success=m_pInitService->initUserTradingRight(&theUserTradingRight,sessionRef,&m_Transaction);
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
				success=m_pInitService->initInvestorAccount(&theInvestorAccount,sessionRef,&m_Transaction);
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
				success=m_pInitService->initInstrument(&theInstrument,sessionRef,&m_Transaction);
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
				success=m_pInitService->initInvestorMargin(&theInvestorMargin,sessionRef,&m_Transaction);
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
				success=m_pInitService->initInvestorFee(&theInvestorFee,sessionRef,&m_Transaction);
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
				success=m_pInitService->initInvestorPosition(&theInvestorPosition,sessionRef,&m_Transaction);
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
				success=m_pInitService->initSystemStatus(&theSystemStatus,sessionRef,&m_Transaction);
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
				success=m_pInitService->initInstrumentGroup(&theInstrumentGroup,sessionRef,&m_Transaction);
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
				success=m_pInitService->initClientMarginCombType(&theClientMarginCombType,sessionRef,&m_Transaction);
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
				success=m_pInitService->initSGEDeferRate(&theSGEDeferRate,sessionRef,&m_Transaction);
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
				success=m_pInitService->initCmbInstrumentDetail(&theCmbInstrumentDetail,sessionRef,&m_Transaction);
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
	case TID_InitInvestorTradingRight:
	{
		CInvestorTradingRightField field;
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
				success=m_pInitService->initInvestorTradingRight(&theInvestorTradingRight,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theInvestorTradingRight) < 3900)
				{
					theInvestorTradingRight.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitInvestorTradingRight is invalid for %s",buffer);
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
				success=m_pInitService->initUserIP(&theUserIP,sessionRef,&m_Transaction);
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
				success=m_pInitService->initInvestorOptionFee(&theInvestorOptionFee,sessionRef,&m_Transaction);
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
	case TID_InitSystemInfo:
	{
		CSystemInfoField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		while(!it.IsEnd())
		{
			CWriteableSystemInfo theSystemInfo;
			theSystemInfo.init();			
			it.Retrieve(&field);
			CopySystemInfoEntity(&theSystemInfo,&field);
			///检查基本字段是否合法
			if (theSystemInfo.isValid())
			{
				success=m_pInitService->initSystemInfo(&theSystemInfo,sessionRef,&m_Transaction);
			}
			else
			{
				if(sizeof(theSystemInfo) < 3900)
				{
					theSystemInfo.dumpString(buffer);
				}
				else
				{
				 	sprintf(buffer,"FieldCheck Error!");
				}				

				REPORT_EVENT(LOG_CRITICAL,"InitError","TID_InitSystemInfo is invalid for %s",buffer);
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
		success=m_pInitService->DataSyncStart(field.TradingDay,sessionRef,&m_Transaction);
		m_pErrorEngine->getLastError(&errorCode,&errMsg);
		break;
	}
	case TID_DataSyncEnd:
	{
		CTradingDayField field;
		CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
		it.Retrieve(&field);
		success=m_pInitService->DataSyncEnd(field.TradingDay,sessionRef,&m_Transaction);
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
			m_pInitService->RspQryExInstrument(&field,sessionRef,&m_Transaction);
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
			m_pInitService->RspQryExTradingDay(&field,sessionRef,&m_Transaction);
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
			m_pInitService->RspQryExInvestorPosition(&field,sessionRef,&m_Transaction);
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
			m_pInitService->RspQryExMarketData(&field,sessionRef,&m_Transaction);
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
			m_pInitService->RspQryExCapitalData(&field,sessionRef,&m_Transaction);
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
			m_pInitService->RspQueryExCmbInstrumentDetail(&field,sessionRef,&m_Transaction);
			it.Next();
		}
		break;
	}
	default:
		return true;
	}
	if (pPackage->GetNoReplayFlag() && success)
	{
		pPackage->MakeNoBufPackage();
		m_pTradeResult->Append(pPackage->Address(), pPackage->Length());
		pPackage->Pop(XTPHLEN);
	}
	if (success)		
		m_Transaction.commit();
	else
		m_Transaction.rollback();
	if(m_verbose)
	{
		if(errorCode == 0)
		{
			//BIZ_OPERATION_LOG0("(OK by exchange init service)\n");
		}
		else
		{
			BIZ_OPERATION_LOG2("(FAILED by exchange init service:%d:%s)\n",errorCode,errMsg);
		}
	}
	return success;
}

