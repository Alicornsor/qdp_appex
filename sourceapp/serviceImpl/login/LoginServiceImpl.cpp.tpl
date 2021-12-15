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
	
	///һ���Ϸ��Լ��
	///����Ƿ��Ѿ����������ݳ�ʼ��
	CDataSyncStatus *pDataSyncStatus;
	pDataSyncStatus=m_pDB->m_DataSyncStatusFactory->getFirst();
	if ((pDataSyncStatus==NULL)||(pDataSyncStatus->DataSyncStatus==DS_Synchronizing))
	{
		REPORT_ERROR(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
	}
	m_pDB->m_DataSyncStatusFactory->endGet();
	//chengm 20180524 ??dumptool��?��?��a��|������o?TD����???��??��??
	if (UserProductInfo == USER_PRODUCT_INFO_DUMPTOOL)
	{
		return true;
	}
	//����BrokerID����ΪNULL
	if (BrokerID.isNull())
	{
		REPORT_ERROR(ERROR_BROKERID_CANNOT_BE_BLANK);
	}

	///1.����û�
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

  //2.����û�����
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
	
	//3.����Ա��ϵ
	//��Ա���е�BrokerID�������½����������ͬ, wangwei	
	//�ҳ���һ��brokerid,Ĭ�������Ա����ֻ����һ��brokerid
	//�Ƶ�����1�� ����User���е�BrokerID���ж���,by wangwei,20130530
/*	CParticipant *pParticipant=m_pDB->m_ParticipantFactory->getFirst();
	m_pDB->m_ParticipantFactory->endGet();
	if (pParticipant->BrokerID != BrokerID)
	{
		REPORT_ERROR(ERROR_USER_NOT_BELONG_TO_THIS_PARTICIPANT);
	}
*/	


	///4.����session�Ƿ��Ѿ�����
	CUserSession *pUserSession = NULL; pUserSession=m_pDB->m_UserSessionFactory->findBySessionIDFrontID(sessionRef.SessionID, sessionRef.FrontID);
	if (pUserSession != NULL)
	{
		REPORT_ERROR(ERROR_DUPLICATE_SESSION);
	}
	
	//ip��ַ��mac��ַ��֤ add by jinpc 
	if (pUser->CheckIpMacAddr.getValue())
	{
		///����û�IP��ַ
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
	///5.����Ƿ��ѵ�¼
	/*pUserSession = m_pDB->m_UserSessionFactory->findByBrokerIDUserID(BrokerID,UserID);
	if (pUserSession != NULL)
	{
		if (m_loginTimeFirst && (pUserSession->IPAddress != IPAddress))
		{
			///��ͬIP��ַ��Դ����ͬ�û���Ӧ����Ϊ���ظ���¼
			REPORT_ERROR(ERROR_USER_RELOGIN);
		}
		else
		{
			///��ͬIP��ַ���ظ���¼����Ҫ��ԭ���Ļ�Ա�߳�ȥ
			m_pDB->m_UserSessionFactory->remove(pUserSession,pTransaction);
			pUserSession=NULL;
		}
	}*/
	
	///��������UserSession��
	///��д��¼reCUserSession
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

	///��UserSession�������ӻ��޸ļ�¼reCUserSession	
	m_pDB->m_UserSessionFactory->addOrUpdate(pUserSession, &UserSession, pTransaction, 1);

	///��������
	///���ؽ�����
	TradingDay = getTradingDay(m_pDB);

	///���ص�¼ʱ��
	LoginTime = UserSession.LoginTime;
	
	///����ϵͳ����
	TradingSystemName = tradingSystemName;
	
	///-------
	///xuzh��20070624���������û����͵ķ��أ���ǰ�û�����ϯλ�������
	///-------
	///�����û�����
	UserType = pUser->UserType;
	
	///-------
	///xuzh��20080717�����������ͨѶ���ķ��أ������û�������������
	///-------
	///�������ͨѶ��
	//�����ػ���,wangwei 20121218
	MaxCommFlux=INT_MAX;
	
	///�ӱ��������ҳ����û�����󱾵ر�����
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
	///һ���Ϸ��Լ��
	///���Ự;
	if (BrokerID.isNull())
	{
		REPORT_ERROR(ERROR_BROKERID_CANNOT_BE_BLANK);
	}
	
	CUserSession *pUserSession = m_pDB->m_UserSessionFactory->findBySessionIDFrontID(sessionRef.SessionID,sessionRef.FrontID);
	if (pUserSession == NULL)
	{
		REPORT_ERROR(ERROR_USER_NOT_LOGIN);
	}

	//����û�����
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
	
	//����Ա����

	if (pUserSession->BrokerID != BrokerID)
	{
		REPORT_ERROR(ERROR_BROKERID_DIFFWITH_LOGIN);
	}

	///�������»Ự״̬
	//��Ψһ�����������޸ģ�ֻ��ɾ��
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
	///һ���Ϸ��Լ��
	///���Ự;
	//BrokerID����ΪNULL,20130530,wangwei
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

	///����ɾ���Ự
	//��Ψһ�����������޸ģ�ֻ��ɾ��
	m_pDB->m_UserSessionFactory->remove(pUserSession, pTransaction);

	///����������û��ı���

	//////////////////////////////////////////////////////////////////////////
	return true;
}

bool CLoginServiceImpl::ForceUserExit(CReadOnlyUserIDType &UserID,
		CReadOnlyBrokerIDType &BrokerID,
		const TSessionRef &sessionRef, CTransaction *pTransaction)
{
	///һ���Ϸ��Լ��
	//BrokerID����ΪNULL,20130530,wangwei
	if (BrokerID.isNull())
	{
		REPORT_ERROR(ERROR_BROKERID_CANNOT_BE_BLANK);
	}	
	CUser *pUser = m_pDB->m_UserFactory->findByBrokerIDUserID(BrokerID,UserID);
	if (pUser == NULL)
	{
		REPORT_ERROR(ERROR_USER_NOT_FOUND);
	}

	///����ɾ���û��Ự
	if (!ForceUserLogout(UserID, BrokerID, sessionRef, pTransaction))
	{
		int nLastErrorID = 0;
		m_pErrorEngine->getLastError(&nLastErrorID);
		if (nLastErrorID != ERROR_TARGET_USER_NOT_LOGIN)
		{
			REPORT_ERROR(nLastErrorID);
		}
	}

	///������ֹ���û�
	CWriteableUser User;
	m_pDB->m_UserFactory->retrieve(pUser, &User);
	User.IsActive = UIA_NoActive;
	m_pDB->m_UserFactory->update(pUser, &User, pTransaction);

	return true;
}

/*
void CLoginServiceImpl::ForceLogout(CTransaction *pTransaction)
{	
	///�ҵ���ǰ���ϵ����лỰ
	CUserSessionIteratorByFrontID it(m_pDB->m_UserSessionFactory);
	CUserSession *pUserSession = NULL;
	while ((pUserSession=it.next()) !=NULL)
	{
		///�����Ѿ���¼�ĻỰ��ȫ��ǿ���˳�
		//��Ψһ�����������޸ģ�ֻ��ɾ��
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
	//BrokerID����ΪNULL,20130530,wangwei
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
		//��config�ļ�������MD5Password=yes��ʾ����md5,Ĭ��Ϊno
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
	//����У��
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
	
	///�����޸�����
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
		///û�й�10�룬�ǾͲ�����ˡ��������Ϊ�����Ч��
		return true;
	}

	CFrontStatus *pFrontStatus;
	CWriteableFrontStatus theFrontStatus;
	int now=getSecondOfDay(CurrTime);

	///������ǰ�õ�״̬	
	pFrontStatus=m_pDB->m_FrontStatusFactory->getFirst();
	while (pFrontStatus!=NULL)
	{
		if ((pFrontStatus->IsActive)&&(now-getSecondOfDay(pFrontStatus->LastReportTime)>FRONT_TIME_OUT))
		{
			///ԭ��״̬�ǻ�Ծ�ģ������Ѿ���1����û�и���״̬�ˣ��Ǿͽ����״̬��Ϊ����Ծ
			m_pDB->m_FrontStatusFactory->retrieve(pFrontStatus,&theFrontStatus);
			theFrontStatus.IsActive=0;
			m_pDB->m_FrontStatusFactory->update(pFrontStatus,&theFrontStatus,pTransaction);
			
			///ǿ���û��˳�
			ForceLogout(pFrontStatus->FrontID,pTransaction);
		}
		pFrontStatus=m_pDB->m_FrontStatusFactory->getNext();
	}
	m_pDB->m_FrontStatusFactory->endGet();
*/	
	return true;
}
