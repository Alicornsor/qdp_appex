/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file CLoginServiceXTPLink.cpp
///@brief实现了类CLoginServiceXTPLink
///@history 
///20130701	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "LoginServiceXTPLink.h"
#include "XtpPackageDesc.h"
#include "UFCopy.h"
#include "CTransaction.h"
#include "monitorIndex.h"

CEventMonitor loginMonitor;
extern const char *APP_NAME;

static char *makeSessionBuffer(const TSessionRef &sessionRef)
{
	static char buffer[100];
	sprintf(buffer,"front=%d,session=%d",sessionRef.FrontID.getValue(),sessionRef.SessionID.getValue());
	return buffer;
}

CLoginServiceXTPLink::CLoginServiceXTPLink(CLoginServiceImpl *pLoginService, CErrorEngine *pErrorEngine,IServiceResponser *pServiceResponser,bool verbose)
{
	m_pLoginService = pLoginService;
	m_pErrorEngine=pErrorEngine;
	m_pServiceResponser = pServiceResponser;
	m_verbose=verbose;
	m_pRspMessage = new CXTPPackage;
	m_pRspMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
//	m_handleLoginIndex= new CIntTotalMonitorIndex("HandleLogin",5);
//	m_handleLoginErrorIndex= new CIntTotalMonitorIndex("HandleLoginError",5);
}

CLoginServiceXTPLink::~CLoginServiceXTPLink()
{
	if(m_pRspMessage != NULL)
		m_pRspMessage->Release();	
	delete m_pRspMessage;
}

bool CLoginServiceXTPLink::handleMessage(CXTPPackage *pPackage, const TSessionRef &sessionRef)
{
	bool success;
	CRspInfoField responseField;
	char* errMsg;
	int errorCode;
	switch (pPackage->GetTid())
	{
	case TID_ReqUserLogin:
		{			
			m_pRspMessage->PrepareResponse(pPackage,TID_RspUserLogin);
			CUserLoginField userLogInField;
			XTP_GET_SINGLE_FIELD(pPackage,&userLogInField);
			success = m_pLoginService->UserLogin(userLogInField.UserID,
							userLogInField.BrokerID,
							userLogInField.Password,
							userLogInField.IPAddress,
							userLogInField.MacAddress,        //登陆MAC备案
							userLogInField.TradingDay,
							userLogInField.LoginTime,
							userLogInField.MaxOrderLocalID,
							userLogInField.UserProductInfo,
							userLogInField.InterfaceProductInfo,
							userLogInField.ProtocolInfo,
							userLogInField.TradingSystemName,
							userLogInField.UserType,
							userLogInField.MaxCommFlux,
							sessionRef,
							&m_Transaction);			
			m_pErrorEngine->getLastError(&errorCode,&errMsg);
			
			userLogInField.TradingSystemName=APP_NAME;
			userLogInField.FrontID = sessionRef.FrontID;
			userLogInField.SessionID = sessionRef.SessionID;
			XTP_ADD_FIELD(m_pRspMessage,&userLogInField);
			if (success)
			{
				loginMonitor.report("LoginSuccess",userLogInField.IPAddress,userLogInField.UserID,makeSessionBuffer(sessionRef));
				REPORT_EVENT(LOG_CRITICAL, "LoginSuccess", "IP[%s],user[%s],UserProductInfo[%s], InterfaceProductInfo[%s],ProtocolInfo[%s]",
					userLogInField.IPAddress.getValue(),userLogInField.UserID.getValue(),userLogInField.UserProductInfo.getValue(),userLogInField.InterfaceProductInfo.getValue(),userLogInField.ProtocolInfo.getValue());
			}
			else
			{
				char fullMessage[1000];
				sprintf(fullMessage,"%s %s",errMsg,makeSessionBuffer(sessionRef));
				loginMonitor.report("LoginFailed",userLogInField.IPAddress,	userLogInField.UserID,fullMessage);
				// 2013-10-23 longqy 用户名密码错误的时候，输出用户名。2015-02-10 不再输出密码
				REPORT_EVENT(LOG_CRITICAL, "LoginFailed", "IP[%s],BrokerID[%s],UserID[%s],Password[%s],UserProductInfo[%s], InterfaceProductInfo[%s],ProtocolInfo[%s]",
					userLogInField.IPAddress.getValue(),userLogInField.BrokerID.getValue(),userLogInField.UserID.getValue(),"******",userLogInField.UserProductInfo.getValue(),userLogInField.InterfaceProductInfo.getValue(),userLogInField.ProtocolInfo.getValue());
			}
		}
		break;
	case TID_ReqUserLogout:
		{
			m_pRspMessage->PrepareResponse(pPackage,TID_RspUserLogout);
			CUserLogoutField userLogOutField;
			XTP_GET_SINGLE_FIELD(pPackage,&userLogOutField);
			success = m_pLoginService->UserLogout(userLogOutField.UserID,userLogOutField.BrokerID,
										sessionRef,&m_Transaction);
			m_pErrorEngine->getLastError(&errorCode,&errMsg);
			XTP_ADD_FIELD(m_pRspMessage,&userLogOutField);
			if (success)
			{
				loginMonitor.report("LogOutSuccess","",userLogOutField.UserID,makeSessionBuffer(sessionRef));
			}
			else
			{
				loginMonitor.report("LogOutFailed","",userLogOutField.UserID,makeSessionBuffer(sessionRef));
			}
		}
		break;

	case TID_ReqUserPasswordUpdate:
		{
			m_pRspMessage->PrepareResponse(pPackage,TID_RspUserPasswordUpdate);
			CUserPasswordUpdateField fieldUserPasswordUpdate;
			XTP_GET_SINGLE_FIELD(pPackage,&fieldUserPasswordUpdate);
			success = m_pLoginService->UserPasswordUpdate(fieldUserPasswordUpdate.UserID,
							fieldUserPasswordUpdate.BrokerID,
							fieldUserPasswordUpdate.OldPassword,
							fieldUserPasswordUpdate.NewPassword,
							sessionRef,
							&m_Transaction);			
			m_pErrorEngine->getLastError(&errorCode,&errMsg);
			XTP_ADD_FIELD(m_pRspMessage,&fieldUserPasswordUpdate);
		}
		break;
	case  TID_RspUserPasswordUpdate:
		{
			CUserPasswordUpdateField field;
			CRspInfoField	   info;
			XTP_GET_SINGLE_FIELD(pPackage,&field);
			XTP_GET_SINGLE_FIELD(pPackage,&info);
			
			if (info.ErrorID ==0)
			{
				success = m_pLoginService->RspUserPasswordUpdate(&field,&m_Transaction);	
			}
			break;
		}
	default:
		return true;
	}

	//modified by chengm 20160714 login,logout不需要反演
	//以上都需要反演
// 	if (pPackage->GetNoReplayFlag())
// 	{
// 		pPackage->MakeNoBufPackage();
// 		m_pTradeResult->Append(pPackage->Address(), pPackage->Length());
// 		pPackage->Pop(XTPHLEN);
// 	}


	if(success)
		m_Transaction.commit();
	else
		m_Transaction.rollback();
	if (m_verbose)
	{
		if(errorCode == 0)
		{
			//BIZ_OPERATION_LOG0("(OK by login service)\n");
		}
		else
		{
			BIZ_OPERATION_LOG2("(FAILED by login service:%d:%s)\n",errorCode,errMsg);
		}
	}

	if (pPackage->GetNoReplayFlag())
	{
		responseField.ErrorID = errorCode;
		responseField.ErrorMsg = errMsg;
		XTP_ADD_FIELD(m_pRspMessage,&responseField);
		m_pRspMessage->MakePackage();
		m_pServiceResponser->SendResponse(m_pRspMessage);
	}

	return success;
}

bool CLoginServiceXTPLink::handleRequest(CXTPPackage *pPackage, const TSessionRef &sessionRef,DWORD ResponseSessionID)
{
	return true;
}
 
