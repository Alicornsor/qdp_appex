/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file QdpFtdcUserApiImpl.cpp
///@brief ʵ���˿ͻ��˽ӿ�
///@history 
///20150522 xuzh create
/////////////////////////////////////////////////////////////////////////

#include "public.h"
#include "FtdcUserApiImpl.h"

CFtdcUserApiImpl::CFtdcUserApiImpl(const char *pszFlowPath, const char *pszUserApiType, CReactor *pReactor)
:CFtdcUserApiImplBase(pszFlowPath, pszUserApiType, pReactor)
{
}

///�û��˳�����
int CFtdcUserApiImpl::ReqUserLogout(CQdpFtdcReqUserLogoutField *pReqUserLogout, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqUserLogout, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDReqUserLogoutField ReqUserLogoutField;
	memcpy(&ReqUserLogoutField, pReqUserLogout, sizeof(CFTDReqUserLogoutField));
	FTDC_ADD_FIELD(&m_reqPackage, &ReqUserLogoutField);

	int nRet = RequestToDialogFlow();
	if(m_fpRequstDump != NULL)
	{
		char szTimeBuffer[20];
		time_t dwCurrTime = m_pReactor->Time();
		strftime(szTimeBuffer, sizeof(szTimeBuffer),
			"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
		fprintf(m_fpRequstDump, "%s,ReqUserLogout,%d,", szTimeBuffer, nRet);
		FIELD_TO_STRING((char *)pReqUserLogout, &CFTDReqUserLogoutField::m_Describe, m_fpRequstDump);
		fprintf(m_fpRequstDump, "\n");
		fflush(m_fpRequstDump);
	}
	m_mutexAction.UnLock();
	
	return nRet;
}
///�û������޸�����
int CFtdcUserApiImpl::ReqUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqUserPasswordUpdate, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDUserPasswordUpdateField UserPasswordUpdateField;
	memcpy(&UserPasswordUpdateField, pUserPasswordUpdate, sizeof(CFTDUserPasswordUpdateField));
	FTDC_ADD_FIELD(&m_reqPackage, &UserPasswordUpdateField);

	int nRet = RequestToDialogFlow();
	if(m_fpRequstDump != NULL)
	{
		char szTimeBuffer[20];
		time_t dwCurrTime = m_pReactor->Time();
		strftime(szTimeBuffer, sizeof(szTimeBuffer),
			"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
		fprintf(m_fpRequstDump, "%s,ReqUserPasswordUpdate,%d,", szTimeBuffer, nRet);
		FIELD_TO_STRING((char *)pUserPasswordUpdate, &CFTDUserPasswordUpdateField::m_Describe, m_fpRequstDump);
		fprintf(m_fpRequstDump, "\n");
		fflush(m_fpRequstDump);
	}
	m_mutexAction.UnLock();
	
	return nRet;
}
///ǿ���û��˳�����
int CFtdcUserApiImpl::ReqForceUserExit(CQdpFtdcForceUserExitField *pForceUserExit, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqForceUserExit, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDForceUserExitField ForceUserExitField;
	memcpy(&ForceUserExitField, pForceUserExit, sizeof(CFTDForceUserExitField));
	FTDC_ADD_FIELD(&m_reqPackage, &ForceUserExitField);

	int nRet = RequestToDialogFlow();
	if(m_fpRequstDump != NULL)
	{
		char szTimeBuffer[20];
		time_t dwCurrTime = m_pReactor->Time();
		strftime(szTimeBuffer, sizeof(szTimeBuffer),
			"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
		fprintf(m_fpRequstDump, "%s,ReqForceUserExit,%d,", szTimeBuffer, nRet);
		FIELD_TO_STRING((char *)pForceUserExit, &CFTDForceUserExitField::m_Describe, m_fpRequstDump);
		fprintf(m_fpRequstDump, "\n");
		fflush(m_fpRequstDump);
	}
	m_mutexAction.UnLock();
	
	return nRet;
}
///�û��Ựɾ������
int CFtdcUserApiImpl::ReqForceUserLogout(CQdpFtdcForceUserExitField *pForceUserExit, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqForceUserLogout, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDForceUserExitField ForceUserExitField;
	memcpy(&ForceUserExitField, pForceUserExit, sizeof(CFTDForceUserExitField));
	FTDC_ADD_FIELD(&m_reqPackage, &ForceUserExitField);

	int nRet = RequestToDialogFlow();
	if(m_fpRequstDump != NULL)
	{
		char szTimeBuffer[20];
		time_t dwCurrTime = m_pReactor->Time();
		strftime(szTimeBuffer, sizeof(szTimeBuffer),
			"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
		fprintf(m_fpRequstDump, "%s,ReqForceUserLogout,%d,", szTimeBuffer, nRet);
		FIELD_TO_STRING((char *)pForceUserExit, &CFTDForceUserExitField::m_Describe, m_fpRequstDump);
		fprintf(m_fpRequstDump, "\n");
		fflush(m_fpRequstDump);
	}
	m_mutexAction.UnLock();
	
	return nRet;
}
///���󵼳��ڴ����ݿ�
int CFtdcUserApiImpl::ReqDumpMemDb(CQdpFtdcMemDbField *pMemDb, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqDumpMemDb, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDMemDbField MemDbField;
	memcpy(&MemDbField, pMemDb, sizeof(CFTDMemDbField));
	FTDC_ADD_FIELD(&m_reqPackage, &MemDbField);

	int nRet = RequestToDialogFlow();
	if(m_fpRequstDump != NULL)
	{
		char szTimeBuffer[20];
		time_t dwCurrTime = m_pReactor->Time();
		strftime(szTimeBuffer, sizeof(szTimeBuffer),
			"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
		fprintf(m_fpRequstDump, "%s,ReqDumpMemDb,%d,", szTimeBuffer, nRet);
		FIELD_TO_STRING((char *)pMemDb, &CFTDMemDbField::m_Describe, m_fpRequstDump);
		fprintf(m_fpRequstDump, "\n");
		fflush(m_fpRequstDump);
	}
	m_mutexAction.UnLock();
	
	return nRet;
}
///����¼������
int CFtdcUserApiImpl::ReqOrderInsert(CQdpFtdcInputOrderField *pInputOrder, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqOrderInsert, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDInputOrderField InputOrderField;
	memcpy(&InputOrderField, pInputOrder, sizeof(CFTDInputOrderField));
	FTDC_ADD_FIELD(&m_reqPackage, &InputOrderField);

	int nRet = RequestToDialogFlow();
	if(m_fpRequstDump != NULL)
	{
		char szTimeBuffer[20];
		time_t dwCurrTime = m_pReactor->Time();
		strftime(szTimeBuffer, sizeof(szTimeBuffer),
			"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
		fprintf(m_fpRequstDump, "%s,ReqOrderInsert,%d,", szTimeBuffer, nRet);
		FIELD_TO_STRING((char *)pInputOrder, &CFTDInputOrderField::m_Describe, m_fpRequstDump);
		fprintf(m_fpRequstDump, "\n");
		fflush(m_fpRequstDump);
	}
	m_mutexAction.UnLock();
	
	return nRet;
}
///������������
int CFtdcUserApiImpl::ReqOrderAction(CQdpFtdcOrderActionField *pOrderAction, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqOrderAction, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDOrderActionField OrderActionField;
	memcpy(&OrderActionField, pOrderAction, sizeof(CFTDOrderActionField));
	FTDC_ADD_FIELD(&m_reqPackage, &OrderActionField);

	int nRet = RequestToDialogFlow();
	if(m_fpRequstDump != NULL)
	{
		char szTimeBuffer[20];
		time_t dwCurrTime = m_pReactor->Time();
		strftime(szTimeBuffer, sizeof(szTimeBuffer),
			"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
		fprintf(m_fpRequstDump, "%s,ReqOrderAction,%d,", szTimeBuffer, nRet);
		FIELD_TO_STRING((char *)pOrderAction, &CFTDOrderActionField::m_Describe, m_fpRequstDump);
		fprintf(m_fpRequstDump, "\n");
		fflush(m_fpRequstDump);
	}
	m_mutexAction.UnLock();
	
	return nRet;
}
///Ͷ�����ʽ��ʻ����������
int CFtdcUserApiImpl::ReqAccountDeposit(CQdpFtdcReqAccountDepositField *pReqAccountDeposit, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqAccountDeposit, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDReqAccountDepositField ReqAccountDepositField;
	memcpy(&ReqAccountDepositField, pReqAccountDeposit, sizeof(CFTDReqAccountDepositField));
	FTDC_ADD_FIELD(&m_reqPackage, &ReqAccountDepositField);

	int nRet = RequestToDialogFlow();
	if(m_fpRequstDump != NULL)
	{
		char szTimeBuffer[20];
		time_t dwCurrTime = m_pReactor->Time();
		strftime(szTimeBuffer, sizeof(szTimeBuffer),
			"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
		fprintf(m_fpRequstDump, "%s,ReqAccountDeposit,%d,", szTimeBuffer, nRet);
		FIELD_TO_STRING((char *)pReqAccountDeposit, &CFTDReqAccountDepositField::m_Describe, m_fpRequstDump);
		fprintf(m_fpRequstDump, "\n");
		fflush(m_fpRequstDump);
	}
	m_mutexAction.UnLock();
	
	return nRet;
}
///������ѯ����
int CFtdcUserApiImpl::ReqQryOrder(CQdpFtdcQryOrderField *pQryOrder, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryOrder, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryOrderField QryOrderField;
	memcpy(&QryOrderField, pQryOrder, sizeof(CFTDQryOrderField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryOrderField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///�ɽ�����ѯ����
int CFtdcUserApiImpl::ReqQryTrade(CQdpFtdcQryTradeField *pQryTrade, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryTrade, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryTradeField QryTradeField;
	memcpy(&QryTradeField, pQryTrade, sizeof(CFTDQryTradeField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryTradeField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///����Ͷ�����˻���ѯ����
int CFtdcUserApiImpl::ReqQryUserInvestor(CQdpFtdcQryUserInvestorField *pQryUserInvestor, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryUserInvestor, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryUserInvestorField QryUserInvestorField;
	memcpy(&QryUserInvestorField, pQryUserInvestor, sizeof(CFTDQryUserInvestorField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryUserInvestorField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///���ױ����ѯ����
int CFtdcUserApiImpl::ReqQryTradingCode(CQdpFtdcQryTradingCodeField *pQryTradingCode, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryTradingCode, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryTradingCodeField QryTradingCodeField;
	memcpy(&QryTradingCodeField, pQryTradingCode, sizeof(CFTDQryTradingCodeField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryTradingCodeField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///Ͷ�����ʽ��˻���ѯ����
int CFtdcUserApiImpl::ReqQryInvestorAccount(CQdpFtdcQryInvestorAccountField *pQryInvestorAccount, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryInvestorAccount, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryInvestorAccountField QryInvestorAccountField;
	memcpy(&QryInvestorAccountField, pQryInvestorAccount, sizeof(CFTDQryInvestorAccountField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryInvestorAccountField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///��Լ��ѯ����
int CFtdcUserApiImpl::ReqQryInstrument(CQdpFtdcQryInstrumentField *pQryInstrument, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryInstrument, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryInstrumentField QryInstrumentField;
	memcpy(&QryInstrumentField, pQryInstrument, sizeof(CFTDQryInstrumentField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryInstrumentField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///��������ѯ����
int CFtdcUserApiImpl::ReqQryExchange(CQdpFtdcQryExchangeField *pQryExchange, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryExchange, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryExchangeField QryExchangeField;
	memcpy(&QryExchangeField, pQryExchange, sizeof(CFTDQryExchangeField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryExchangeField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///Ͷ���ֲֲ߳�ѯ����
int CFtdcUserApiImpl::ReqQryInvestorPosition(CQdpFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryInvestorPosition, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryInvestorPositionField QryInvestorPositionField;
	memcpy(&QryInvestorPositionField, pQryInvestorPosition, sizeof(CFTDQryInvestorPositionField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryInvestorPositionField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///������������
int CFtdcUserApiImpl::ReqSubscribeTopic(CQdpFtdcDisseminationField *pDissemination, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqSubscribeTopic, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDDisseminationField DisseminationField;
	memcpy(&DisseminationField, pDissemination, sizeof(CFTDDisseminationField));
	FTDC_ADD_FIELD(&m_reqPackage, &DisseminationField);

	int nRet = RequestToDialogFlow();
	if(m_fpRequstDump != NULL)
	{
		char szTimeBuffer[20];
		time_t dwCurrTime = m_pReactor->Time();
		strftime(szTimeBuffer, sizeof(szTimeBuffer),
			"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
		fprintf(m_fpRequstDump, "%s,ReqSubscribeTopic,%d,", szTimeBuffer, nRet);
		FIELD_TO_STRING((char *)pDissemination, &CFTDDisseminationField::m_Describe, m_fpRequstDump);
		fprintf(m_fpRequstDump, "\n");
		fflush(m_fpRequstDump);
	}
	m_mutexAction.UnLock();
	
	return nRet;
}
///�����ѯ����
int CFtdcUserApiImpl::ReqQryTopic(CQdpFtdcDisseminationField *pDissemination, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryTopic, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDDisseminationField DisseminationField;
	memcpy(&DisseminationField, pDissemination, sizeof(CFTDDisseminationField));
	FTDC_ADD_FIELD(&m_reqPackage, &DisseminationField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///�û���ѯ����
int CFtdcUserApiImpl::ReqQryUser(CQdpFtdcQryUserField *pQryUser, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryUser, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryUserField QryUserField;
	memcpy(&QryUserField, pQryUser, sizeof(CFTDQryUserField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryUserField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///Ͷ�����������ʲ�ѯ����
int CFtdcUserApiImpl::ReqQryInvestorFee(CQdpFtdcQryInvestorFeeField *pQryInvestorFee, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryInvestorFee, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryInvestorFeeField QryInvestorFeeField;
	memcpy(&QryInvestorFeeField, pQryInvestorFee, sizeof(CFTDQryInvestorFeeField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryInvestorFeeField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///Ͷ���߱�֤���ʲ�ѯ����
int CFtdcUserApiImpl::ReqQryInvestorMargin(CQdpFtdcQryInvestorMarginField *pQryInvestorMargin, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryInvestorMargin, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryInvestorMarginField QryInvestorMarginField;
	memcpy(&QryInvestorMarginField, pQryInvestorMargin, sizeof(CFTDQryInvestorMarginField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryInvestorMarginField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///�������ӷ��ʲ�ѯ����
int CFtdcUserApiImpl::ReqQrySGEDeferRate(CQdpFtdcQrySGEDeferRateField *pQrySGEDeferRate, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQrySGEDeferRate, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQrySGEDeferRateField QrySGEDeferRateField;
	memcpy(&QrySGEDeferRateField, pQrySGEDeferRate, sizeof(CFTDQrySGEDeferRateField));
	FTDC_ADD_FIELD(&m_reqPackage, &QrySGEDeferRateField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///�ֲ���ϸ��ѯ����
int CFtdcUserApiImpl::ReqQryInvestorPositionDetail(CQdpFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryInvestorPositionDetail, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryInvestorPositionDetailField QryInvestorPositionDetailField;
	memcpy(&QryInvestorPositionDetailField, pQryInvestorPositionDetail, sizeof(CFTDQryInvestorPositionDetailField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryInvestorPositionDetailField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///Ͷ������Ȩ�������ʲ�ѯ����
int CFtdcUserApiImpl::ReqQryInvestorOptionFee(CQdpFtdcQryInvestorOptionFeeField *pQryInvestorOptionFee, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryInvestorOptionFee, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryInvestorOptionFeeField QryInvestorOptionFeeField;
	memcpy(&QryInvestorOptionFeeField, pQryInvestorOptionFee, sizeof(CFTDQryInvestorOptionFeeField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryInvestorOptionFeeField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///Topic��ѯ
int CFtdcUserApiImpl::ReqTopicSearch(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqTopicSearch, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDSpecificInstrumentField SpecificInstrumentField;
	memcpy(&SpecificInstrumentField, pSpecificInstrument, sizeof(CFTDSpecificInstrumentField));
	FTDC_ADD_FIELD(&m_reqPackage, &SpecificInstrumentField);

	int nRet = RequestToDialogFlow();
	if(m_fpRequstDump != NULL)
	{
		char szTimeBuffer[20];
		time_t dwCurrTime = m_pReactor->Time();
		strftime(szTimeBuffer, sizeof(szTimeBuffer),
			"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
		fprintf(m_fpRequstDump, "%s,ReqTopicSearch,%d,", szTimeBuffer, nRet);
		FIELD_TO_STRING((char *)pSpecificInstrument, &CFTDSpecificInstrumentField::m_Describe, m_fpRequstDump);
		fprintf(m_fpRequstDump, "\n");
		fflush(m_fpRequstDump);
	}
	m_mutexAction.UnLock();
	
	return nRet;
}
///���ĺ�Լ�������Ϣ
int CFtdcUserApiImpl::ReqSubMarketData(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqSubMarketData, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDSpecificInstrumentField SpecificInstrumentField;
	memcpy(&SpecificInstrumentField, pSpecificInstrument, sizeof(CFTDSpecificInstrumentField));
	FTDC_ADD_FIELD(&m_reqPackage, &SpecificInstrumentField);

	int nRet = RequestToDialogFlow();
	if(m_fpRequstDump != NULL)
	{
		char szTimeBuffer[20];
		time_t dwCurrTime = m_pReactor->Time();
		strftime(szTimeBuffer, sizeof(szTimeBuffer),
			"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
		fprintf(m_fpRequstDump, "%s,ReqSubMarketData,%d,", szTimeBuffer, nRet);
		FIELD_TO_STRING((char *)pSpecificInstrument, &CFTDSpecificInstrumentField::m_Describe, m_fpRequstDump);
		fprintf(m_fpRequstDump, "\n");
		fflush(m_fpRequstDump);
	}
	m_mutexAction.UnLock();
	
	return nRet;
}
///�˶���Լ�������Ϣ
int CFtdcUserApiImpl::ReqUnSubMarketData(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqUnSubMarketData, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDSpecificInstrumentField SpecificInstrumentField;
	memcpy(&SpecificInstrumentField, pSpecificInstrument, sizeof(CFTDSpecificInstrumentField));
	FTDC_ADD_FIELD(&m_reqPackage, &SpecificInstrumentField);

	int nRet = RequestToDialogFlow();
	if(m_fpRequstDump != NULL)
	{
		char szTimeBuffer[20];
		time_t dwCurrTime = m_pReactor->Time();
		strftime(szTimeBuffer, sizeof(szTimeBuffer),
			"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
		fprintf(m_fpRequstDump, "%s,ReqUnSubMarketData,%d,", szTimeBuffer, nRet);
		FIELD_TO_STRING((char *)pSpecificInstrument, &CFTDSpecificInstrumentField::m_Describe, m_fpRequstDump);
		fprintf(m_fpRequstDump, "\n");
		fflush(m_fpRequstDump);
	}
	m_mutexAction.UnLock();
	
	return nRet;
}
///ʵʱ�����ѯ����
int CFtdcUserApiImpl::ReqQryMarketData(CQdpFtdcQryMarketDataField *pQryMarketData, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryMarketData, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryMarketDataField QryMarketDataField;
	memcpy(&QryMarketDataField, pQryMarketData, sizeof(CFTDQryMarketDataField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryMarketDataField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///�����ѯ����
int CFtdcUserApiImpl::ReqQryDepthMarketData(CQdpFtdcQryMarketDataField *pQryMarketData, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryDepthMarketData, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryMarketDataField QryMarketDataField;
	memcpy(&QryMarketDataField, pQryMarketData, sizeof(CFTDQryMarketDataField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryMarketDataField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}
///�ּ۱��ѯ����
int CFtdcUserApiImpl::ReqQryMBLMarketData(CQdpFtdcQryMBLMarketDataField *pQryMBLMarketData, int nRequestID)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqQryMBLMarketData, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	
	CFTDQryMBLMarketDataField QryMBLMarketDataField;
	memcpy(&QryMBLMarketDataField, pQryMBLMarketData, sizeof(CFTDQryMBLMarketDataField));
	FTDC_ADD_FIELD(&m_reqPackage, &QryMBLMarketDataField);

	int nRet = RequestToQueryFlow();
	m_mutexAction.UnLock();
	
	return nRet;
}

void CFtdcUserApiImpl::HandleResponse(CFTDCPackage *pMessage, WORD nSequenceSeries)
{

	switch(pMessage->GetTID()) {
	///����Ӧ��
	case FTD_TID_RspError:
		OnRspError(pMessage, nSequenceSeries);
		break;
	///�û���¼Ӧ��
	case FTD_TID_RspUserLogin:
		OnRspUserLogin(pMessage, nSequenceSeries);
		break;
	///�û��˳�Ӧ��
	case FTD_TID_RspUserLogout:
		OnRspUserLogout(pMessage, nSequenceSeries);
		break;
	///�û������޸�Ӧ��
	case FTD_TID_RspUserPasswordUpdate:
		OnRspUserPasswordUpdate(pMessage, nSequenceSeries);
		break;
	///ǿ���û��˳�Ӧ��
	case FTD_TID_RspForceUserExit:
		OnRspForceUserExit(pMessage, nSequenceSeries);
		break;
	///�û��Ựɾ��Ӧ��
	case FTD_TID_RspForceUserLogout:
		OnRspForceUserLogout(pMessage, nSequenceSeries);
		break;
	///����¼��Ӧ��
	case FTD_TID_RspOrderInsert:
		OnRspOrderInsert(pMessage, nSequenceSeries);
		break;
	///��������Ӧ��
	case FTD_TID_RspOrderAction:
		OnRspOrderAction(pMessage, nSequenceSeries);
		break;
	///Ͷ�����ʽ��ʻ������Ӧ��
	case FTD_TID_RspAccountDeposit:
		OnRspAccountDeposit(pMessage, nSequenceSeries);
		break;
	///����������֪ͨ
	case FTD_TID_RtnFlowMessageCancel:
		OnRtnFlowMessageCancel(pMessage, nSequenceSeries);
		break;
	///�ڲ��ַ���Ϣ֪ͨ
	case FTD_TID_IntlRtnDissemination:
		OnIntlRtnDissemination(pMessage, nSequenceSeries);
		break;
	///�ɽ��ر�
	case FTD_TID_RtnTrade:
		OnRtnTrade(pMessage, nSequenceSeries);
		break;
	///�����ر�
	case FTD_TID_RtnOrder:
		OnRtnOrder(pMessage, nSequenceSeries);
		break;
	///����¼�����ر�
	case FTD_TID_ErrRtnOrderInsert:
		OnErrRtnOrderInsert(pMessage, nSequenceSeries);
		break;
	///������������ر�
	case FTD_TID_ErrRtnOrderAction:
		OnErrRtnOrderAction(pMessage, nSequenceSeries);
		break;
	///��Լ����״̬֪ͨ
	case FTD_TID_RtnInstrumentStatus:
		OnRtnInstrumentStatus(pMessage, nSequenceSeries);
		break;
	///�˻������ر�
	case FTD_TID_RtnInvestorAccountDeposit:
		OnRtnInvestorAccountDeposit(pMessage, nSequenceSeries);
		break;
	///QDP������Ϣ֪ͨ
	case FTD_TID_RtnMessageNotify:
		OnRtnMessageNotify(pMessage, nSequenceSeries);
		break;
	///�������ӷ���֪ͨ
	case FTD_TID_RtnSGEDeferRate:
		OnRtnSGEDeferRate(pMessage, nSequenceSeries);
		break;
	///֣�ݺ�Լ״̬
	case FTD_TID_RtnQmdInstrumentStatu:
		OnRtnQmdInstrumentStatu(pMessage, nSequenceSeries);
		break;
	///������ѯӦ��
	case FTD_TID_RspQryOrder:
		OnRspQryOrder(pMessage, nSequenceSeries);
		break;
	///�ɽ�����ѯӦ��
	case FTD_TID_RspQryTrade:
		OnRspQryTrade(pMessage, nSequenceSeries);
		break;
	///����Ͷ�����˻���ѯӦ��
	case FTD_TID_RspQryUserInvestor:
		OnRspQryUserInvestor(pMessage, nSequenceSeries);
		break;
	///���ױ����ѯӦ��
	case FTD_TID_RspQryTradingCode:
		OnRspQryTradingCode(pMessage, nSequenceSeries);
		break;
	///Ͷ�����ʽ��˻���ѯӦ��
	case FTD_TID_RspQryInvestorAccount:
		OnRspQryInvestorAccount(pMessage, nSequenceSeries);
		break;
	///��Լ��ѯӦ��
	case FTD_TID_RspQryInstrument:
		OnRspQryInstrument(pMessage, nSequenceSeries);
		break;
	///��������ѯӦ��
	case FTD_TID_RspQryExchange:
		OnRspQryExchange(pMessage, nSequenceSeries);
		break;
	///Ͷ���ֲֲ߳�ѯӦ��
	case FTD_TID_RspQryInvestorPosition:
		OnRspQryInvestorPosition(pMessage, nSequenceSeries);
		break;
	///��������Ӧ��
	case FTD_TID_RspSubscribeTopic:
		OnRspSubscribeTopic(pMessage, nSequenceSeries);
		break;
	///�����ѯӦ��
	case FTD_TID_RspQryTopic:
		OnRspQryTopic(pMessage, nSequenceSeries);
		break;
	///�û���ѯӦ��
	case FTD_TID_RspQryUser:
		OnRspQryUser(pMessage, nSequenceSeries);
		break;
	///Ͷ�����������ʲ�ѯӦ��
	case FTD_TID_RspQryInvestorFee:
		OnRspQryInvestorFee(pMessage, nSequenceSeries);
		break;
	///Ͷ���߱�֤���ʲ�ѯӦ��
	case FTD_TID_RspQryInvestorMargin:
		OnRspQryInvestorMargin(pMessage, nSequenceSeries);
		break;
	///�������ӷ��ʲ�ѯӦ��
	case FTD_TID_RspQrySGEDeferRate:
		OnRspQrySGEDeferRate(pMessage, nSequenceSeries);
		break;
	///�ֲ���ϸ��ѯӦ��
	case FTD_TID_RspQryInvestorPositionDetail:
		OnRspQryInvestorPositionDetail(pMessage, nSequenceSeries);
		break;
	///Ͷ������Ȩ�������ʲ�ѯӦ��
	case FTD_TID_RspQryInvestorOptionFee:
		OnRspQryInvestorOptionFee(pMessage, nSequenceSeries);
		break;
	///�ڲ��������֪ͨ
	case FTD_TID_IntlRtnDepthMarketData:
		OnIntlRtnDepthMarketData(pMessage, nSequenceSeries);
		break;
	///Topic��ѯӦ��
	case FTD_TID_IntlTopicSearch:
		OnIntlTopicSearch(pMessage, nSequenceSeries);
		break;
	///�������֪ͨ
	case FTD_TID_RtnDepthMarketData:
		OnRtnDepthMarketData(pMessage, nSequenceSeries);
		break;
	///�������֪ͨ
	case FTD_TID_RtnMultiDepthMarketData:
		OnRtnMultiDepthMarketData(pMessage, nSequenceSeries);
		break;
	///���ĺ�Լ�������Ϣ
	case FTD_TID_RspSubMarketData:
		OnRspSubMarketData(pMessage, nSequenceSeries);
		break;
	///�˶���Լ�������Ϣ
	case FTD_TID_RspUnSubMarketData:
		OnRspUnSubMarketData(pMessage, nSequenceSeries);
		break;
	///ʵʱ�����ѯӦ��
	case FTD_TID_RspQryMarketData:
		OnRspQryMarketData(pMessage, nSequenceSeries);
		break;
	///�����ѯӦ��
	case FTD_TID_RspQryDepthMarketData:
		OnRspQryDepthMarketData(pMessage, nSequenceSeries);
		break;
	///�ּ۱��ѯӦ��
	case FTD_TID_RspQryMBLMarketData:
		OnRspQryMBLMarketData(pMessage, nSequenceSeries);
		break;
	default:
		break;
	}
}

CQdpFtdcUserApi *CQdpFtdcUserApi::CreateFtdcUserApi(const char *pszFlowPath,
													const char *pszUserApiType)
{
	return new CFtdcUserApiImpl(pszFlowPath, pszUserApiType, new CSelectReactor());
}

const char *CQdpFtdcUserApi::GetVersion(int &nMajorVersion, int &nMinorVersion)
{
		#ifdef WIN32
			return "Win UserApi "QVERSION" "SUFFIX_STR;
		#else
			return "Linux UserApi "QVERSION" "SUFFIX_STR;
		#endif
}


///����Ӧ��
void CFtdcUserApiImpl::OnRspError(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	if (m_pSpi != NULL)
	{
		m_pSpi->OnRspError(pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///�û���¼Ӧ��
void CFtdcUserApiImpl::OnRspUserLogin(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDRspUserLoginField RspUserLogin;
	CQdpFtdcRspUserLoginField *pRspUserLogin = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDRspUserLoginField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&RspUserLogin);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pRspUserLogin = (CQdpFtdcRspUserLoginField *)&RspUserLogin;
			m_pSpi->OnRspUserLogin(pRspUserLogin, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		
	}
	
	if (pRspUserLogin == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspUserLogin(pRspUserLogin, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///�û��˳�Ӧ��
void CFtdcUserApiImpl::OnRspUserLogout(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDRspUserLogoutField RspUserLogout;
	CQdpFtdcRspUserLogoutField *pRspUserLogout = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDRspUserLogoutField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&RspUserLogout);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pRspUserLogout = (CQdpFtdcRspUserLogoutField *)&RspUserLogout;
			m_pSpi->OnRspUserLogout(pRspUserLogout, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		
	}
	
	if (pRspUserLogout == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspUserLogout(pRspUserLogout, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///�û������޸�Ӧ��
void CFtdcUserApiImpl::OnRspUserPasswordUpdate(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDUserPasswordUpdateField UserPasswordUpdate;
	CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDUserPasswordUpdateField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&UserPasswordUpdate);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pUserPasswordUpdate = (CQdpFtdcUserPasswordUpdateField *)&UserPasswordUpdate;
			m_pSpi->OnRspUserPasswordUpdate(pUserPasswordUpdate, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspUserPasswordUpdate,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&UserPasswordUpdate, &CFTDUserPasswordUpdateField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pUserPasswordUpdate == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspUserPasswordUpdate(pUserPasswordUpdate, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///ǿ���û��˳�Ӧ��
void CFtdcUserApiImpl::OnRspForceUserExit(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDForceUserExitField ForceUserExit;
	CQdpFtdcForceUserExitField *pForceUserExit = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDForceUserExitField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&ForceUserExit);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pForceUserExit = (CQdpFtdcForceUserExitField *)&ForceUserExit;
			m_pSpi->OnRspForceUserExit(pForceUserExit, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspForceUserExit,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&ForceUserExit, &CFTDForceUserExitField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pForceUserExit == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspForceUserExit(pForceUserExit, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///�û��Ựɾ��Ӧ��
void CFtdcUserApiImpl::OnRspForceUserLogout(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDForceUserExitField ForceUserExit;
	CQdpFtdcForceUserExitField *pForceUserExit = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDForceUserExitField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&ForceUserExit);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pForceUserExit = (CQdpFtdcForceUserExitField *)&ForceUserExit;
			m_pSpi->OnRspForceUserLogout(pForceUserExit, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspForceUserLogout,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&ForceUserExit, &CFTDForceUserExitField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pForceUserExit == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspForceUserLogout(pForceUserExit, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///����¼��Ӧ��
void CFtdcUserApiImpl::OnRspOrderInsert(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDInputOrderField InputOrder;
	CQdpFtdcInputOrderField *pInputOrder = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDInputOrderField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&InputOrder);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pInputOrder = (CQdpFtdcInputOrderField *)&InputOrder;
			m_pSpi->OnRspOrderInsert(pInputOrder, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspOrderInsert,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&InputOrder, &CFTDInputOrderField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pInputOrder == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspOrderInsert(pInputOrder, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///��������Ӧ��
void CFtdcUserApiImpl::OnRspOrderAction(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDOrderActionField OrderAction;
	CQdpFtdcOrderActionField *pOrderAction = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDOrderActionField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&OrderAction);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pOrderAction = (CQdpFtdcOrderActionField *)&OrderAction;
			m_pSpi->OnRspOrderAction(pOrderAction, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspOrderAction,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&OrderAction, &CFTDOrderActionField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pOrderAction == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspOrderAction(pOrderAction, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///Ͷ�����ʽ��ʻ������Ӧ��
void CFtdcUserApiImpl::OnRspAccountDeposit(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDRspAccountDepositField RspAccountDeposit;
	CQdpFtdcRspAccountDepositField *pRspAccountDeposit = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDRspAccountDepositField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&RspAccountDeposit);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pRspAccountDeposit = (CQdpFtdcRspAccountDepositField *)&RspAccountDeposit;
			m_pSpi->OnRspAccountDeposit(pRspAccountDeposit, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspAccountDeposit,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&RspAccountDeposit, &CFTDRspAccountDepositField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pRspAccountDeposit == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspAccountDeposit(pRspAccountDeposit, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///����������֪ͨ
void CFtdcUserApiImpl::OnRtnFlowMessageCancel(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageStart((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
	CFTDFlowMessageCancelField FlowMessageCancel;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDFlowMessageCancelField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&FlowMessageCancel);
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRtnFlowMessageCancel,", szTimeBuffer);
			FIELD_TO_STRING((char *)&FlowMessageCancel, &CFTDFlowMessageCancelField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		if (m_pSpi != NULL)
		{
			m_pSpi->OnRtnFlowMessageCancel((CQdpFtdcFlowMessageCancelField *)&FlowMessageCancel);
		}
		itor.Next();
	}
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageEnd((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
}

///�ɽ��ر�
void CFtdcUserApiImpl::OnRtnTrade(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageStart((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
	CFTDTradeField Trade;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDTradeField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&Trade);
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRtnTrade,", szTimeBuffer);
			FIELD_TO_STRING((char *)&Trade, &CFTDTradeField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		if (m_pSpi != NULL)
		{
			m_pSpi->OnRtnTrade((CQdpFtdcTradeField *)&Trade);
		}
		itor.Next();
	}
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageEnd((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
}

///�����ر�
void CFtdcUserApiImpl::OnRtnOrder(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageStart((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
	CFTDOrderField Order;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDOrderField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&Order);
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRtnOrder,", szTimeBuffer);
			FIELD_TO_STRING((char *)&Order, &CFTDOrderField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		if (m_pSpi != NULL)
		{
			m_pSpi->OnRtnOrder((CQdpFtdcOrderField *)&Order);
		}
		itor.Next();
	}
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageEnd((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
}

///����¼�����ر�
void CFtdcUserApiImpl::OnErrRtnOrderInsert(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageStart((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDInputOrderField InputOrder;
	CQdpFtdcInputOrderField *pInputOrder = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDInputOrderField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&InputOrder);
		itor.Next();
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnErrRtnOrderInsert,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&InputOrder, &CFTDInputOrderField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pInputOrder = (CQdpFtdcInputOrderField *)&InputOrder;
			m_pSpi->OnErrRtnOrderInsert(pInputOrder, pRspInfoField);
		}
	}
	
	if (pInputOrder == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnErrRtnOrderInsert(pInputOrder, pRspInfoField);
	}
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageEnd((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
}

///������������ر�
void CFtdcUserApiImpl::OnErrRtnOrderAction(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageStart((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDOrderActionField OrderAction;
	CQdpFtdcOrderActionField *pOrderAction = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDOrderActionField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&OrderAction);
		itor.Next();
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnErrRtnOrderAction,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&OrderAction, &CFTDOrderActionField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pOrderAction = (CQdpFtdcOrderActionField *)&OrderAction;
			m_pSpi->OnErrRtnOrderAction(pOrderAction, pRspInfoField);
		}
	}
	
	if (pOrderAction == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnErrRtnOrderAction(pOrderAction, pRspInfoField);
	}
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageEnd((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
}

///��Լ����״̬֪ͨ
void CFtdcUserApiImpl::OnRtnInstrumentStatus(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageStart((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
	CFTDInstrumentStatusField InstrumentStatus;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDInstrumentStatusField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&InstrumentStatus);
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRtnInstrumentStatus,", szTimeBuffer);
			FIELD_TO_STRING((char *)&InstrumentStatus, &CFTDInstrumentStatusField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		if (m_pSpi != NULL)
		{
			m_pSpi->OnRtnInstrumentStatus((CQdpFtdcInstrumentStatusField *)&InstrumentStatus);
		}
		itor.Next();
	}
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageEnd((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
}

///�˻������ر�
void CFtdcUserApiImpl::OnRtnInvestorAccountDeposit(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageStart((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
	CFTDInvestorAccountDepositResField InvestorAccountDepositRes;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDInvestorAccountDepositResField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&InvestorAccountDepositRes);
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRtnInvestorAccountDeposit,", szTimeBuffer);
			FIELD_TO_STRING((char *)&InvestorAccountDepositRes, &CFTDInvestorAccountDepositResField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		if (m_pSpi != NULL)
		{
			m_pSpi->OnRtnInvestorAccountDeposit((CQdpFtdcInvestorAccountDepositResField *)&InvestorAccountDepositRes);
		}
		itor.Next();
	}
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageEnd((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
}

///QDP������Ϣ֪ͨ
void CFtdcUserApiImpl::OnRtnMessageNotify(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageStart((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
	CFTDMessageNotifyInfoField MessageNotifyInfo;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDMessageNotifyInfoField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&MessageNotifyInfo);
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRtnMessageNotify,", szTimeBuffer);
			FIELD_TO_STRING((char *)&MessageNotifyInfo, &CFTDMessageNotifyInfoField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		if (m_pSpi != NULL)
		{
			m_pSpi->OnRtnMessageNotify((CQdpFtdcMessageNotifyInfoField *)&MessageNotifyInfo);
		}
		itor.Next();
	}
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageEnd((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
}

///�������ӷ���֪ͨ
void CFtdcUserApiImpl::OnRtnSGEDeferRate(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageStart((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
	CFTDSGEDeferRateField SGEDeferRate;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDSGEDeferRateField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&SGEDeferRate);
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRtnSGEDeferRate,", szTimeBuffer);
			FIELD_TO_STRING((char *)&SGEDeferRate, &CFTDSGEDeferRateField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		if (m_pSpi != NULL)
		{
			m_pSpi->OnRtnSGEDeferRate((CQdpFtdcSGEDeferRateField *)&SGEDeferRate);
		}
		itor.Next();
	}
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageEnd((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
}

///֣�ݺ�Լ״̬
void CFtdcUserApiImpl::OnRtnQmdInstrumentStatu(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageStart((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
	CFTDQmdInstrumentStateField QmdInstrumentState;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDQmdInstrumentStateField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&QmdInstrumentState);
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRtnQmdInstrumentStatu,", szTimeBuffer);
			FIELD_TO_STRING((char *)&QmdInstrumentState, &CFTDQmdInstrumentStateField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		if (m_pSpi != NULL)
		{
			m_pSpi->OnRtnQmdInstrumentStatu((CQdpFtdcQmdInstrumentStateField *)&QmdInstrumentState);
		}
		itor.Next();
	}
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageEnd((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
}

///������ѯӦ��
void CFtdcUserApiImpl::OnRspQryOrder(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDOrderField Order;
	CQdpFtdcOrderField *pOrder = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDOrderField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&Order);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pOrder = (CQdpFtdcOrderField *)&Order;
			m_pSpi->OnRspQryOrder(pOrder, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryOrder,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&Order, &CFTDOrderField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pOrder == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryOrder(pOrder, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///�ɽ�����ѯӦ��
void CFtdcUserApiImpl::OnRspQryTrade(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDTradeField Trade;
	CQdpFtdcTradeField *pTrade = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDTradeField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&Trade);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pTrade = (CQdpFtdcTradeField *)&Trade;
			m_pSpi->OnRspQryTrade(pTrade, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryTrade,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&Trade, &CFTDTradeField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pTrade == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryTrade(pTrade, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///����Ͷ�����˻���ѯӦ��
void CFtdcUserApiImpl::OnRspQryUserInvestor(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDRspUserInvestorField RspUserInvestor;
	CQdpFtdcRspUserInvestorField *pRspUserInvestor = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDRspUserInvestorField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&RspUserInvestor);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pRspUserInvestor = (CQdpFtdcRspUserInvestorField *)&RspUserInvestor;
			m_pSpi->OnRspQryUserInvestor(pRspUserInvestor, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryUserInvestor,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&RspUserInvestor, &CFTDRspUserInvestorField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pRspUserInvestor == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryUserInvestor(pRspUserInvestor, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///���ױ����ѯӦ��
void CFtdcUserApiImpl::OnRspQryTradingCode(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDRspTradingCodeField RspTradingCode;
	CQdpFtdcRspTradingCodeField *pRspTradingCode = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDRspTradingCodeField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&RspTradingCode);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pRspTradingCode = (CQdpFtdcRspTradingCodeField *)&RspTradingCode;
			m_pSpi->OnRspQryTradingCode(pRspTradingCode, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryTradingCode,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&RspTradingCode, &CFTDRspTradingCodeField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pRspTradingCode == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryTradingCode(pRspTradingCode, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///Ͷ�����ʽ��˻���ѯӦ��
void CFtdcUserApiImpl::OnRspQryInvestorAccount(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDRspInvestorAccountField RspInvestorAccount;
	CQdpFtdcRspInvestorAccountField *pRspInvestorAccount = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDRspInvestorAccountField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&RspInvestorAccount);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pRspInvestorAccount = (CQdpFtdcRspInvestorAccountField *)&RspInvestorAccount;
			m_pSpi->OnRspQryInvestorAccount(pRspInvestorAccount, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryInvestorAccount,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&RspInvestorAccount, &CFTDRspInvestorAccountField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pRspInvestorAccount == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorAccount(pRspInvestorAccount, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///��Լ��ѯӦ��
void CFtdcUserApiImpl::OnRspQryInstrument(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDRspInstrumentField RspInstrument;
	CQdpFtdcRspInstrumentField *pRspInstrument = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDRspInstrumentField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&RspInstrument);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pRspInstrument = (CQdpFtdcRspInstrumentField *)&RspInstrument;
			m_pSpi->OnRspQryInstrument(pRspInstrument, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryInstrument,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&RspInstrument, &CFTDRspInstrumentField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pRspInstrument == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInstrument(pRspInstrument, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///��������ѯӦ��
void CFtdcUserApiImpl::OnRspQryExchange(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDRspExchangeField RspExchange;
	CQdpFtdcRspExchangeField *pRspExchange = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDRspExchangeField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&RspExchange);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pRspExchange = (CQdpFtdcRspExchangeField *)&RspExchange;
			m_pSpi->OnRspQryExchange(pRspExchange, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryExchange,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&RspExchange, &CFTDRspExchangeField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pRspExchange == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryExchange(pRspExchange, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///Ͷ���ֲֲ߳�ѯӦ��
void CFtdcUserApiImpl::OnRspQryInvestorPosition(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDRspInvestorPositionField RspInvestorPosition;
	CQdpFtdcRspInvestorPositionField *pRspInvestorPosition = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDRspInvestorPositionField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&RspInvestorPosition);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pRspInvestorPosition = (CQdpFtdcRspInvestorPositionField *)&RspInvestorPosition;
			m_pSpi->OnRspQryInvestorPosition(pRspInvestorPosition, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryInvestorPosition,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&RspInvestorPosition, &CFTDRspInvestorPositionField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pRspInvestorPosition == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorPosition(pRspInvestorPosition, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///��������Ӧ��
void CFtdcUserApiImpl::OnRspSubscribeTopic(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDDisseminationField Dissemination;
	CQdpFtdcDisseminationField *pDissemination = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDDisseminationField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&Dissemination);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pDissemination = (CQdpFtdcDisseminationField *)&Dissemination;
			m_pSpi->OnRspSubscribeTopic(pDissemination, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspSubscribeTopic,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&Dissemination, &CFTDDisseminationField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pDissemination == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspSubscribeTopic(pDissemination, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///�����ѯӦ��
void CFtdcUserApiImpl::OnRspQryTopic(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDDisseminationField Dissemination;
	CQdpFtdcDisseminationField *pDissemination = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDDisseminationField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&Dissemination);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pDissemination = (CQdpFtdcDisseminationField *)&Dissemination;
			m_pSpi->OnRspQryTopic(pDissemination, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryTopic,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&Dissemination, &CFTDDisseminationField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pDissemination == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryTopic(pDissemination, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///�û���ѯӦ��
void CFtdcUserApiImpl::OnRspQryUser(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDUserField User;
	CQdpFtdcUserField *pUser = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDUserField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&User);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pUser = (CQdpFtdcUserField *)&User;
			m_pSpi->OnRspQryUser(pUser, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryUser,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&User, &CFTDUserField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pUser == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryUser(pUser, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///Ͷ�����������ʲ�ѯӦ��
void CFtdcUserApiImpl::OnRspQryInvestorFee(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDInvestorFeeField InvestorFee;
	CQdpFtdcInvestorFeeField *pInvestorFee = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDInvestorFeeField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&InvestorFee);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pInvestorFee = (CQdpFtdcInvestorFeeField *)&InvestorFee;
			m_pSpi->OnRspQryInvestorFee(pInvestorFee, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryInvestorFee,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&InvestorFee, &CFTDInvestorFeeField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pInvestorFee == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorFee(pInvestorFee, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///Ͷ���߱�֤���ʲ�ѯӦ��
void CFtdcUserApiImpl::OnRspQryInvestorMargin(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDInvestorMarginField InvestorMargin;
	CQdpFtdcInvestorMarginField *pInvestorMargin = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDInvestorMarginField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&InvestorMargin);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pInvestorMargin = (CQdpFtdcInvestorMarginField *)&InvestorMargin;
			m_pSpi->OnRspQryInvestorMargin(pInvestorMargin, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryInvestorMargin,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&InvestorMargin, &CFTDInvestorMarginField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pInvestorMargin == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorMargin(pInvestorMargin, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///�������ӷ��ʲ�ѯӦ��
void CFtdcUserApiImpl::OnRspQrySGEDeferRate(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDSGEDeferRateField SGEDeferRate;
	CQdpFtdcSGEDeferRateField *pSGEDeferRate = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDSGEDeferRateField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&SGEDeferRate);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pSGEDeferRate = (CQdpFtdcSGEDeferRateField *)&SGEDeferRate;
			m_pSpi->OnRspQrySGEDeferRate(pSGEDeferRate, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQrySGEDeferRate,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&SGEDeferRate, &CFTDSGEDeferRateField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pSGEDeferRate == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQrySGEDeferRate(pSGEDeferRate, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///�ֲ���ϸ��ѯӦ��
void CFtdcUserApiImpl::OnRspQryInvestorPositionDetail(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDRspInvestorPositionDetailField RspInvestorPositionDetail;
	CQdpFtdcRspInvestorPositionDetailField *pRspInvestorPositionDetail = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDRspInvestorPositionDetailField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&RspInvestorPositionDetail);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pRspInvestorPositionDetail = (CQdpFtdcRspInvestorPositionDetailField *)&RspInvestorPositionDetail;
			m_pSpi->OnRspQryInvestorPositionDetail(pRspInvestorPositionDetail, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryInvestorPositionDetail,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&RspInvestorPositionDetail, &CFTDRspInvestorPositionDetailField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pRspInvestorPositionDetail == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorPositionDetail(pRspInvestorPositionDetail, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///Ͷ������Ȩ�������ʲ�ѯӦ��
void CFtdcUserApiImpl::OnRspQryInvestorOptionFee(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDRspInvestorOptionFeeField RspInvestorOptionFee;
	CQdpFtdcRspInvestorOptionFeeField *pRspInvestorOptionFee = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDRspInvestorOptionFeeField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&RspInvestorOptionFee);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pRspInvestorOptionFee = (CQdpFtdcRspInvestorOptionFeeField *)&RspInvestorOptionFee;
			m_pSpi->OnRspQryInvestorOptionFee(pRspInvestorOptionFee, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryInvestorOptionFee,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&RspInvestorOptionFee, &CFTDRspInvestorOptionFeeField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pRspInvestorOptionFee == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryInvestorOptionFee(pRspInvestorOptionFee, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///�������֪ͨ
void CFtdcUserApiImpl::OnRtnDepthMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageStart((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
	CFTDDepthMarketDataField DepthMarketData;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDDepthMarketDataField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&DepthMarketData);
		CFtdcUserApiImplBase::OnRtnDepthMarketData(&DepthMarketData, nSequenceSeries);
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRtnDepthMarketData,", szTimeBuffer);
			FIELD_TO_STRING((char *)&DepthMarketData, &CFTDDepthMarketDataField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		if (m_pSpi != NULL)
		{
			m_pSpi->OnRtnDepthMarketData((CQdpFtdcDepthMarketDataField *)&DepthMarketData);
		}
		itor.Next();
	}
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageEnd((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
}

///�������֪ͨ
void CFtdcUserApiImpl::OnRtnMultiDepthMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageStart((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
	CFTDDepthMarketDataField DepthMarketData;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDDepthMarketDataField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&DepthMarketData);
		CFtdcUserApiImplBase::OnRtnDepthMarketData(&DepthMarketData, nSequenceSeries);
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRtnMultiDepthMarketData,", szTimeBuffer);
			FIELD_TO_STRING((char *)&DepthMarketData, &CFTDDepthMarketDataField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		if (m_pSpi != NULL)
		{
			m_pSpi->OnRtnMultiDepthMarketData((CQdpFtdcDepthMarketDataField *)&DepthMarketData);
		}
		itor.Next();
	}
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageEnd((int)nSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
}

///���ĺ�Լ�������Ϣ
void CFtdcUserApiImpl::OnRspSubMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDSpecificInstrumentField SpecificInstrument;
	CQdpFtdcSpecificInstrumentField *pSpecificInstrument = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDSpecificInstrumentField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&SpecificInstrument);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pSpecificInstrument = (CQdpFtdcSpecificInstrumentField *)&SpecificInstrument;
			m_pSpi->OnRspSubMarketData(pSpecificInstrument, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspSubMarketData,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&SpecificInstrument, &CFTDSpecificInstrumentField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pSpecificInstrument == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspSubMarketData(pSpecificInstrument, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///�˶���Լ�������Ϣ
void CFtdcUserApiImpl::OnRspUnSubMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDSpecificInstrumentField SpecificInstrument;
	CQdpFtdcSpecificInstrumentField *pSpecificInstrument = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDSpecificInstrumentField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&SpecificInstrument);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pSpecificInstrument = (CQdpFtdcSpecificInstrumentField *)&SpecificInstrument;
			m_pSpi->OnRspUnSubMarketData(pSpecificInstrument, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspUnSubMarketData,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&SpecificInstrument, &CFTDSpecificInstrumentField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pSpecificInstrument == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspUnSubMarketData(pSpecificInstrument, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///ʵʱ�����ѯӦ��
void CFtdcUserApiImpl::OnRspQryMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDMarketDataField MarketData;
	CQdpFtdcMarketDataField *pMarketData = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDMarketDataField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&MarketData);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pMarketData = (CQdpFtdcMarketDataField *)&MarketData;
			m_pSpi->OnRspQryMarketData(pMarketData, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryMarketData,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&MarketData, &CFTDMarketDataField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pMarketData == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryMarketData(pMarketData, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///�����ѯӦ��
void CFtdcUserApiImpl::OnRspQryDepthMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDRspMarketDataField RspMarketData;
	CQdpFtdcRspMarketDataField *pRspMarketData = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDRspMarketDataField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&RspMarketData);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pRspMarketData = (CQdpFtdcRspMarketDataField *)&RspMarketData;
			m_pSpi->OnRspQryDepthMarketData(pRspMarketData, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryDepthMarketData,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&RspMarketData, &CFTDRspMarketDataField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pRspMarketData == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryDepthMarketData(pRspMarketData, pRspInfoField, pMessage->GetRequestId(), true);
	}
}

///�ּ۱��ѯӦ��
void CFtdcUserApiImpl::OnRspQryMBLMarketData(CFTDCPackage *pMessage, WORD nSequenceSeries)
{
	CFTDRspInfoField rspInfoField;
	CQdpFtdcRspInfoField *pRspInfoField = (CQdpFtdcRspInfoField *)&rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		pRspInfoField = NULL;
	}
	CFTDMBLMarketDataField MBLMarketData;
	CQdpFtdcMBLMarketDataField *pMBLMarketData = NULL;
	CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDMBLMarketDataField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&MBLMarketData);
		itor.Next();
		if (m_pSpi != NULL)
		{
			bool bIsLast = false;
			if (pMessage->GetChain() == FTDC_CHAIN_LAST	&& itor.IsEnd())
			{
				bIsLast = true;
			}
			pMBLMarketData = (CQdpFtdcMBLMarketDataField *)&MBLMarketData;
			m_pSpi->OnRspQryMBLMarketData(pMBLMarketData, pRspInfoField, pMessage->GetRequestId(), bIsLast);
		}
		if(m_fpResponseDump != NULL)
		{
			char szTimeBuffer[20];
			time_t dwCurrTime = m_pReactor->Time();
			strftime(szTimeBuffer, sizeof(szTimeBuffer),
				"%Y%m%d %H:%M:%S",localtime(&dwCurrTime));
			fprintf(m_fpResponseDump, "%s,OnRspQryMBLMarketData,", szTimeBuffer);
			if(pRspInfoField != NULL)
			{
				fprintf(m_fpResponseDump,"%d,%s,", pRspInfoField->ErrorID, pRspInfoField->ErrorMsg);
			}
			else
			{
				fprintf(m_fpResponseDump,",,");
			}
			FIELD_TO_STRING((char *)&MBLMarketData, &CFTDMBLMarketDataField::m_Describe, m_fpResponseDump);
			fprintf(m_fpResponseDump, "\n");
			fflush(m_fpResponseDump);
		}
		
	}
	
	if (pMBLMarketData == NULL && m_pSpi != NULL)
	{
		m_pSpi->OnRspQryMBLMarketData(pMBLMarketData, pRspInfoField, pMessage->GetRequestId(), true);
	}
}


