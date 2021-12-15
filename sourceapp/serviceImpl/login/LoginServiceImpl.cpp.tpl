// LoginServiceImpl.cpp: implementation of the CLoginServiceImpl class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "LoginServiceImpl.h"
#include "errorDefine.h"
#include "utility.h"
#include "tradingTools.h"
#include "XtpPackageDesc.h"
#include "cryptAll.h"

#define FRONT_TIME_OUT	60

#define REPORT_ERROR(errorid)	{ m_pErrorEngine->reportError(errorid);return false;}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoginServiceImpl::CLoginServiceImpl(CMemoryDB *pDB, CErrorEngine *pErrorEngine)
{
	m_pDB = pDB;
	m_pErrorEngine = pErrorEngine;

	m_loginTimeFirst=true;
	if (!strcmp(currentConfig->getConfig("LoginTimeFirst"),"no"))
	{
		m_loginTimeFirst=false;
	}
	else if (!strcmp(currentConfig->getConfig("LoginTimeFirst"),"yes"))
	{
		m_loginTimeFirst=true;
	}

	m_md5Password=false;	
	if (!strcmp(currentConfig->getConfig("MD5Password"),"no"))
	{
		m_md5Password=false;
	}
	else if (!strcmp(currentConfig->getConfig("MD5Password"),"yes"))
	{
		m_md5Password=true;
	}
}

CLoginServiceImpl::~CLoginServiceImpl()
{
}
/*
bool CLoginServiceImpl::CheckUserFunctionRight(int reqTid, int *pRspTid,
	const TSessionRef &sessionRef, CTransaction *pTransaction)
{
	CUserSession *pUserSession;

	switch (reqTid)
	{
	!!enter XTP!!
	!!travel packages!!
	!!if !strcmp(@usage,"request")!!
		#ifdef Func!!show_string @name+3!!
		case TID_!!@name!!:
			pUserSession=m_pDB->m_UserSessionFactory->findBySessionID(sessionRef.SessionID);
			if ((pUserSession==NULL)||(pUserSession->UserType!=UT_Manager))
			{
				return true;
			}
			if (!hasRight(m_pDB,pUserSession->UserID,Func!!show_string @name+3!!))
			{
				*pRspTid=TID_Rsp!!show_string @name+3!!;
				REPORT_ERROR(ERROR_NO_FUNCTION_RIGHT);
			}
			return true;
		#endif
	!!endif!!
	!!next!!
	!!leave!!
	}
	return true;
}
*/
bool CLoginServiceImpl::UserLogin(CReadOnlyUserIDType &UserID,	
	CBrokerIDType &BrokerID,
	CReadOnlyPasswordType &Password, 
	CReadOnlyIPAddressType &IPAddress,
	CReadOnlyMacAddressType &MacAddress,
	CDateType &TradingDay,
	CTimeType &LoginTime,
	CUserOrderLocalIDType &MaxOrderLocalID,
	CReadOnlyProductInfoType &UserProductInfo,
	CReadOnlyProductInfoType &InterfaceProductInfo,
	CReadOnlyProtocolInfoType &ProtocolInfo,
	CTradingSystemNameType &TradingSystemName,
	CUserTypeType &UserType,
	CCommFluxType &MaxCommFlux,
	const TSessionRef &sessionRef, CTransaction *pTransaction)
{
	
	///一、合法性检查
	///检查是否已经进行了数据初始化
	CDataSyncStatus *pDataSyncStatus;
	pDataSyncStatus=m_pDB->m_DataSyncStatusFactory->getFirst();
	if ((pDataSyncStatus==NULL)||(pDataSyncStatus->DataSyncStatus==DS_Synchronizing))
	{
		REPORT_ERROR(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
	}
	m_pDB->m_DataSyncStatusFactory->endGet();
	//chengm 20180524 ??dumptool×?ì?êa′|àí￡o?TDèμ???ó??§??
	if (UserProductInfo == USER_PRODUCT_INFO_DUMPTOOL)
	{
		return true;
	}
	//新增BrokerID不能为NULL
	if (BrokerID.isNull())
	{
		REPORT_ERROR(ERROR_BROKERID_CANNOT_BE_BLANK);
	}

	///1.检查用户
	CUser *pUser = m_pDB->m_UserFactory->findByBrokerIDUserID(BrokerID,UserID);
	if (pUser == NULL)
	{
		REPORT_ERROR(ERROR_INVALID_USER_OR_PASSWORD);
	}
	if (pUser->IsActive!=UIA_Active)
	{
		REPORT_ERROR(ERROR_USER_NOT_ACTIVE);
	}	
	if (pUser->BrokerID!=BrokerID)
	{
		REPORT_ERROR(ERROR_USER_NOT_BELONG_TO_THIS_PARTICIPANT);
	}

  //2.检查用户密码
	if (!m_md5Password)
	{
		if (pUser->Password != Password)
		{
			REPORT_ERROR(ERROR_INVALID_USER_OR_PASSWORD);
		}
	}
	else
	{
		char md5Password[33];
		MD5Hex(md5Password,UserID,Password);
		if (pUser->Password != md5Password)
		{
			REPORT_ERROR(ERROR_INVALID_USER_OR_PASSWORD);
		}
	}	
	
	//3.检查会员关系
	//会员表中的BrokerID必须与登陆传上来的相同, wangwei	
	//找出第一个brokerid,默认这个会员表中只会有一个brokerid
	//移到步骤1中 ，用User表中的BrokerID进行对照,by wangwei,20130530
/*	CParticipant *pParticipant=m_pDB->m_ParticipantFactory->getFirst();
	m_pDB->m_ParticipantFactory->endGet();
	if (pParticipant->BrokerID != BrokerID)
	{
		REPORT_ERROR(ERROR_USER_NOT_BELONG_TO_THIS_PARTICIPANT);
	}
*/	


	///4.检查该session是否已经存在
	CUserSession *pUserSession = NULL; pUserSession=m_pDB->m_UserSessionFactory->findBySessionIDFrontID(sessionRef.SessionID, sessionRef.FrontID);
	if (pUserSession != NULL)
	{
		REPORT_ERROR(ERROR_DUPLICATE_SESSION);
	}
	
	//ip地址，mac地址验证 add by jinpc 
	if (pUser->CheckIpMacAddr.getValue())
	{
		///检查用户IP地址
		bool bValidIpFlag = false;
		CUserIPIteratorByUserID itorUserIP(m_pDB->m_UserIPFactory,BrokerID,UserID);
		CUserIP *pUserIP = NULL;
		while((pUserIP = itorUserIP.next()) != NULL)
		{
			if (CheckIpAddressMatch(IPAddress, pUserIP->IPAddress, pUserIP->IPMask))
			{
				if ( (MacAddress == pUserIP->MacAddress) || MacAddress.isNull() )
				{
					bValidIpFlag=true;
					break;
				}
			}
		}
		if (!bValidIpFlag)
		{
			REPORT_ERROR(ERROR_INVALID_LOGIN_IPADDRESS);
		}
	}
	///5.检查是否已登录
	/*pUserSession = m_pDB->m_UserSessionFactory->findByBrokerIDUserID(BrokerID,UserID);
	if (pUserSession != NULL)
	{
		if (m_loginTimeFirst && (pUserSession->IPAddress != IPAddress))
		{
			///不同IP地址来源的相同用户，应当认为是重复登录
			REPORT_ERROR(ERROR_USER_RELOGIN);
		}
		else
		{
			///相同IP地址的重复登录，需要把原来的会员踢出去
			m_pDB->m_UserSessionFactory->remove(pUserSession,pTransaction);
			pUserSession=NULL;
		}
	}*/
	
	///二、操作UserSession表
	///填写记录reCUserSession
	CWriteableUserSession UserSession;
//	UserSession.FrontID = sessionRef.frontID;
	UserSession.LoginTime = getCurrentTime(m_pDB);
	UserSession.BrokerID = BrokerID;
	UserSession.SessionID = sessionRef.SessionID;
	UserSession.FrontID = sessionRef.FrontID;
	UserSession.UserID = pUser->UserID;
	UserSession.UserType = pUser->UserType;
	UserSession.IPAddress = IPAddress;
	UserSession.MacAddress = MacAddress;
	UserSession.UserProductInfo = UserProductInfo;
	UserSession.InterfaceProductInfo = InterfaceProductInfo;
	UserSession.ProtocolInfo = ProtocolInfo;

	///向UserSession表中增加或修改记录reCUserSession	
	m_pDB->m_UserSessionFactory->addOrUpdate(pUserSession, &UserSession, pTransaction, 1);

	///三、返回
	///返回交易日
	TradingDay = getTradingDay(m_pDB);

	///返回登录时间
	LoginTime = UserSession.LoginTime;
	
	///返回系统名称
	TradingSystemName = tradingSystemName;
	
	///-------
	///xuzh，20070624：增加了用户类型的返回，供前置机进行席位输出控制
	///-------
	///返回用户类型
	UserType = pUser->UserType;
	
	///-------
	///xuzh，20080717：增加了最大通讯量的返回，供分用户进行流量控制
	///-------
	///返回最大通讯量
	//无流控机制,wangwei 20121218
	MaxCommFlux=INT_MAX;
	
	///从报单表中找出该用户的最大本地报单号
	//CMaxLocalID *pMaxID = m_pDB->m_MaxLocalIDFactory->findByBrokerIDUserID(BrokerID,UserID);
	//if(pMaxID != NULL)
	//{
	//	MaxOrderLocalID = pMaxID->MaxOrderLocalID;
	//}
	//else
	//{
	CWriteableMaxLocalID wtbMaxLocalID;
	wtbMaxLocalID.init();
	wtbMaxLocalID.FrontID = sessionRef.FrontID;
	wtbMaxLocalID.SessionID = sessionRef.SessionID;
	wtbMaxLocalID.BrokerID = BrokerID;
	wtbMaxLocalID.UserID = UserID;
	wtbMaxLocalID.MaxOrderLocalID = "";
	wtbMaxLocalID.IPAddress = IPAddress;
	wtbMaxLocalID.MacAddress = MacAddress;
	m_pDB->m_MaxLocalIDFactory->add(&wtbMaxLocalID,pTransaction);
	MaxOrderLocalID = "";	
	//}
	return true;
}

bool CLoginServiceImpl::UserLogout(CReadOnlyUserIDType &UserID,	
		CReadOnlyBrokerIDType &BrokerID,
		const TSessionRef &sessionRef, CTransaction *pTransaction)
{
	///一、合法性检查
	///检查会话;
	if (BrokerID.isNull())
	{
		REPORT_ERROR(ERROR_BROKERID_CANNOT_BE_BLANK);
	}
	
	CUserSession *pUserSession = m_pDB->m_UserSessionFactory->findBySessionIDFrontID(sessionRef.SessionID,sessionRef.FrontID);
	if (pUserSession == NULL)
	{
		REPORT_ERROR(ERROR_USER_NOT_LOGIN);
	}

	//检查用户代码
	if (!UserID.isNull())
	{
		if (pUserSession->UserID != UserID)
		{
			REPORT_ERROR(ERROR_NOT_LOGINED_BY_THIS_USER);
		}
	}
	else
	{
		REPORT_ERROR(ERROR_USERID_CANNOT_BE_BLANK);
	}
	
	//检查会员代码

	if (pUserSession->BrokerID != BrokerID)
	{
		REPORT_ERROR(ERROR_BROKERID_DIFFWITH_LOGIN);
	}

	///二、更新会话状态
	//多唯一索引，不能修改，只能删除
	m_pDB->m_UserSessionFactory->remove(pUserSession, pTransaction);
	
	CMaxLocalID *pMaxLocalID = m_pDB->m_MaxLocalIDFactory->findByFrontIDSessionID(sessionRef.FrontID,sessionRef.SessionID);
	if (pMaxLocalID != NULL)
	{
		m_pDB->m_MaxLocalIDFactory->remove(pMaxLocalID,pTransaction);
	}

	return true;
}

bool CLoginServiceImpl::ForceUserLogout(CReadOnlyUserIDType &UserID,
		CReadOnlyBrokerIDType &BrokerID,
		const TSessionRef &sessionRef, CTransaction *pTransaction)
{
	///一、合法性检查
	///检查会话;
	//BrokerID不能为NULL,20130530,wangwei
	if (BrokerID.isNull())
	{
		REPORT_ERROR(ERROR_BROKERID_CANNOT_BE_BLANK);
	}

	CUserSession *pUserSession = m_pDB->m_UserSessionFactory->findBySessionIDFrontID(sessionRef.SessionID,sessionRef.FrontID);
	if (pUserSession == NULL)
	{
		REPORT_ERROR(ERROR_USER_NOT_LOGIN);
	}

	if (pUserSession->UserType != UT_Manager)
	{
		REPORT_ERROR(ERROR_USER_NO_PERMISSION);
	}

	pUserSession = m_pDB->m_UserSessionFactory->findByBrokerIDUserIDSFID(BrokerID,UserID,sessionRef.SessionID,sessionRef.FrontID);
	if (pUserSession == NULL)
	{
		REPORT_ERROR(ERROR_TARGET_USER_NOT_LOGIN);
	}

	CUser *pUser = m_pDB->m_UserFactory->findByBrokerIDUserID(BrokerID,UserID);
	if (pUser == NULL)
	{
		REPORT_ERROR(ERROR_INVALID_USER_OR_PASSWORD);
	}
	if (pUser->BrokerID!=BrokerID)
	{
		REPORT_ERROR(ERROR_USER_NOT_BELONG_TO_THIS_PARTICIPANT);
	}

	///二、删除会话
	//多唯一索引，不能修改，只能删除
	m_pDB->m_UserSessionFactory->remove(pUserSession, pTransaction);

	///三、挂起该用户的报单

	//////////////////////////////////////////////////////////////////////////
	return true;
}

bool CLoginServiceImpl::ForceUserExit(CReadOnlyUserIDType &UserID,
		CReadOnlyBrokerIDType &BrokerID,
		const TSessionRef &sessionRef, CTransaction *pTransaction)
{
	///一、合法性检查
	//BrokerID不能为NULL,20130530,wangwei
	if (BrokerID.isNull())
	{
		REPORT_ERROR(ERROR_BROKERID_CANNOT_BE_BLANK);
	}	
	CUser *pUser = m_pDB->m_UserFactory->findByBrokerIDUserID(BrokerID,UserID);
	if (pUser == NULL)
	{
		REPORT_ERROR(ERROR_USER_NOT_FOUND);
	}

	///二、删除用户会话
	if (!ForceUserLogout(UserID, BrokerID, sessionRef, pTransaction))
	{
		int nLastErrorID = 0;
		m_pErrorEngine->getLastError(&nLastErrorID);
		if (nLastErrorID != ERROR_TARGET_USER_NOT_LOGIN)
		{
			REPORT_ERROR(nLastErrorID);
		}
	}

	///三、禁止该用户
	CWriteableUser User;
	m_pDB->m_UserFactory->retrieve(pUser, &User);
	User.IsActive = UIA_NoActive;
	m_pDB->m_UserFactory->update(pUser, &User, pTransaction);

	return true;
}

/*
void CLoginServiceImpl::ForceLogout(CTransaction *pTransaction)
{	
	///找到该前置上的所有会话
	CUserSessionIteratorByFrontID it(m_pDB->m_UserSessionFactory);
	CUserSession *pUserSession = NULL;
	while ((pUserSession=it.next()) !=NULL)
	{
		///对于已经登录的会话，全部强制退出
		//多唯一索引，不能修改，只能删除
		it.DeleteCurrent(pTransaction);
	}
}
*/

bool CLoginServiceImpl::RspUserPasswordUpdate(CUserPasswordUpdateField *pField, CTransaction *pTransaction)
{
	CUser *pUser = m_pDB->m_UserFactory->findByBrokerIDUserID(pField->BrokerID,pField->UserID);
	if (pUser != NULL && pUser->Password == pField->OldPassword)
	{
		CWriteableUser wtbUser;
		m_pDB->m_UserFactory->retrieve(pUser,&wtbUser);
		wtbUser.Password = pField->NewPassword;
		m_pDB->m_UserFactory->update(pUser,&wtbUser,pTransaction);
	}
	return true;
}

bool CLoginServiceImpl::UserPasswordUpdate(CReadOnlyUserIDType &UserID,	
		CBrokerIDType &BrokerID,
		CReadOnlyPasswordType &OldPassword, 
		CReadOnlyPasswordType &NewPassword, 
		const TSessionRef &sessionRef, CTransaction *pTransaction)
{
	//BrokerID不能为NULL,20130530,wangwei
	if (BrokerID.isNull())
	{
		REPORT_ERROR(ERROR_BROKERID_CANNOT_BE_BLANK);
	}
	CUserSession *pUserSession = m_pDB->m_UserSessionFactory->findBySessionIDFrontID(sessionRef.SessionID,sessionRef.FrontID);
	if (pUserSession == NULL)
	{
		REPORT_ERROR(ERROR_USER_NOT_LOGIN);
	}
	if (pUserSession->UserID != UserID)
	{
		REPORT_ERROR(ERROR_USER_MISMATCH);
	}
	CUser *pUser = m_pDB->m_UserFactory->findByBrokerIDUserID(BrokerID,UserID);
	if (pUser == NULL)
	{
		REPORT_ERROR(ERROR_INVALID_USER_OR_PASSWORD);
	}
	
	pUser = m_pDB->m_UserFactory->findByBrokerIDUserID(BrokerID,UserID);
	if (pUser == NULL)
	{
		REPORT_ERROR(ERROR_INVALID_USER_OR_PASSWORD);
	}
	if ((pUser->UserType!=UT_Manager) && (pUser->BrokerID != BrokerID))
	{
		REPORT_ERROR(ERROR_NOT_LOGINED_BY_THIS_PARTICIPANT);
	}
	if (!m_md5Password)
	{
		//在config文件中设置MD5Password=yes表示启用md5,默认为no
		if (pUser->Password != OldPassword)
		{
			REPORT_ERROR(ERROR_INVALID_USER_OR_PASSWORD);
		}
	}
	else
	{
		char md5OldPassword[33];
		MD5Hex(md5OldPassword,UserID,OldPassword);
		if (pUser->Password != md5OldPassword)
		{
			REPORT_ERROR(ERROR_INVALID_USER_OR_PASSWORD);
		}
	}
	//密码校验
	if (NewPassword=="")
	{
		REPORT_ERROR(ERROR_NEWPASSWD_CANNOT_BENULL);
	}
	if (strstr(NewPassword.getValue()," ")!=NULL)
	{
		REPORT_ERROR(ERROR_NEWPASSWD_CONTAIN_SPACE);
	}

	int nPasswdLen=strlen(NewPassword.getValue());
	if (nPasswdLen<3)
	{
		REPORT_ERROR(ERROR_NEWPASSWD_TOOSHORT);
	}
	if (nPasswdLen>15)
	{
		REPORT_ERROR(ERROR_NEWPASSWD_TOOLONG);
	}	
	
	///二、修改密码
	CWriteableUser User;
	User.init();
	m_pDB->m_UserFactory->retrieve(pUser, &User);
	if (!m_md5Password)
	{
		User.Password = NewPassword;
	}
	else
	{
		char md5Password[33];
		MD5Hex(md5Password,UserID,NewPassword);
		User.Password=md5Password;
	}
	m_pDB->m_UserFactory->update(pUser, &User, pTransaction, false);

	return true;
}

bool CLoginServiceImpl::TimeSync(CReadOnlyTimeType &CurrTime,
	const TSessionRef &sessionRef,CTransaction *pTransaction)
{
/*
	CReadOnlyTimeType &oldTime=getCurrentTime(m_pDB);

	if (!strncmp(CurrTime,oldTime,7))
	{
		///没有过10秒，那就不检查了。这仅仅是为了提高效率
		return true;
	}

	CFrontStatus *pFrontStatus;
	CWriteableFrontStatus theFrontStatus;
	int now=getSecondOfDay(CurrTime);

	///逐个检查前置的状态	
	pFrontStatus=m_pDB->m_FrontStatusFactory->getFirst();
	while (pFrontStatus!=NULL)
	{
		if ((pFrontStatus->IsActive)&&(now-getSecondOfDay(pFrontStatus->LastReportTime)>FRONT_TIME_OUT))
		{
			///原来状态是活跃的，而且已经有1分钟没有更新状态了，那就将其的状态改为不活跃
			m_pDB->m_FrontStatusFactory->retrieve(pFrontStatus,&theFrontStatus);
			theFrontStatus.IsActive=0;
			m_pDB->m_FrontStatusFactory->update(pFrontStatus,&theFrontStatus,pTransaction);
			
			///强制用户退出
			ForceLogout(pFrontStatus->FrontID,pTransaction);
		}
		pFrontStatus=m_pDB->m_FrontStatusFactory->getNext();
	}
	m_pDB->m_FrontStatusFactory->endGet();
*/	
	return true;
}
