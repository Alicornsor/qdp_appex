// FtdPackageDesc.cpp: 
//
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "FtdPackageDesc.h"
#include "HashMap.h"

TFieldUse FTDRspErrorFieldUse[]=
{
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDReqUserLoginFieldUse[]=
{
		{ FTD_FID_ReqUserLogin, &(CFTDReqUserLoginField::m_Describe), 1,  1  }
			,
		{ FTD_FID_Dissemination, &(CFTDDisseminationField::m_Describe), 0,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDRspUserLoginFieldUse[]=
{
		{ FTD_FID_RspUserLogin, &(CFTDRspUserLoginField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDReqUserLogoutFieldUse[]=
{
		{ FTD_FID_ReqUserLogout, &(CFTDReqUserLogoutField::m_Describe), 1,  1  }
};

TFieldUse FTDRspUserLogoutFieldUse[]=
{
		{ FTD_FID_RspUserLogout, &(CFTDRspUserLogoutField::m_Describe), 1,  1  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDReqUserPasswordUpdateFieldUse[]=
{
		{ FTD_FID_UserPasswordUpdate, &(CFTDUserPasswordUpdateField::m_Describe), 1,  1  }
};

TFieldUse FTDRspUserPasswordUpdateFieldUse[]=
{
		{ FTD_FID_UserPasswordUpdate, &(CFTDUserPasswordUpdateField::m_Describe), 1,  1  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDReqForceUserExitFieldUse[]=
{
		{ FTD_FID_ForceUserExit, &(CFTDForceUserExitField::m_Describe), 1,  1  }
};

TFieldUse FTDRspForceUserExitFieldUse[]=
{
		{ FTD_FID_ForceUserExit, &(CFTDForceUserExitField::m_Describe), 1,  1  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDReqForceUserLogoutFieldUse[]=
{
		{ FTD_FID_ForceUserExit, &(CFTDForceUserExitField::m_Describe), 1,  1  }
};

TFieldUse FTDRspForceUserLogoutFieldUse[]=
{
		{ FTD_FID_ForceUserExit, &(CFTDForceUserExitField::m_Describe), 1,  1  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDReqDumpMemDbFieldUse[]=
{
		{ FTD_FID_MemDb, &(CFTDMemDbField::m_Describe), 1,  1  }
};

TFieldUse FTDReqOrderInsertFieldUse[]=
{
		{ FTD_FID_InputOrder, &(CFTDInputOrderField::m_Describe), 1,  1  }
};

TFieldUse FTDRspOrderInsertFieldUse[]=
{
		{ FTD_FID_InputOrder, &(CFTDInputOrderField::m_Describe), 1,  1  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDReqOrderActionFieldUse[]=
{
		{ FTD_FID_OrderAction, &(CFTDOrderActionField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDRspOrderActionFieldUse[]=
{
		{ FTD_FID_OrderAction, &(CFTDOrderActionField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDReqAccountDepositFieldUse[]=
{
		{ FTD_FID_ReqAccountDeposit, &(CFTDReqAccountDepositField::m_Describe), 1,  1  }
};

TFieldUse FTDRspAccountDepositFieldUse[]=
{
		{ FTD_FID_RspAccountDeposit, &(CFTDRspAccountDepositField::m_Describe), 1,  1  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDRtnFlowMessageCancelFieldUse[]=
{
		{ FTD_FID_FlowMessageCancel, &(CFTDFlowMessageCancelField::m_Describe), 0,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDIntlRtnDisseminationFieldUse[]=
{
		{ FTD_FID_Dissemination, &(CFTDDisseminationField::m_Describe), 0,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDRtnTradeFieldUse[]=
{
		{ FTD_FID_Trade, &(CFTDTradeField::m_Describe), 1,  1  }
};

TFieldUse FTDRtnOrderFieldUse[]=
{
		{ FTD_FID_Order, &(CFTDOrderField::m_Describe), 1,  1  }
};

TFieldUse FTDErrRtnOrderInsertFieldUse[]=
{
		{ FTD_FID_InputOrder, &(CFTDInputOrderField::m_Describe), 1,  1  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDErrRtnOrderActionFieldUse[]=
{
		{ FTD_FID_OrderAction, &(CFTDOrderActionField::m_Describe), 1,  1  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDRtnInstrumentStatusFieldUse[]=
{
		{ FTD_FID_InstrumentStatus, &(CFTDInstrumentStatusField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDRtnInvestorAccountDepositFieldUse[]=
{
		{ FTD_FID_InvestorAccountDepositRes, &(CFTDInvestorAccountDepositResField::m_Describe), 1,  1  }
};

TFieldUse FTDRtnMessageNotifyFieldUse[]=
{
		{ FTD_FID_MessageNotifyInfo, &(CFTDMessageNotifyInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDRtnSGEDeferRateFieldUse[]=
{
		{ FTD_FID_SGEDeferRate, &(CFTDSGEDeferRateField::m_Describe), 1,  1  }
};

TFieldUse FTDRtnQmdInstrumentStatuFieldUse[]=
{
		{ FTD_FID_QmdInstrumentState, &(CFTDQmdInstrumentStateField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDReqQryOrderFieldUse[]=
{
		{ FTD_FID_QryOrder, &(CFTDQryOrderField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryOrderFieldUse[]=
{
		{ FTD_FID_Order, &(CFTDOrderField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDReqQryTradeFieldUse[]=
{
		{ FTD_FID_QryTrade, &(CFTDQryTradeField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryTradeFieldUse[]=
{
		{ FTD_FID_Trade, &(CFTDTradeField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDReqQryUserInvestorFieldUse[]=
{
		{ FTD_FID_QryUserInvestor, &(CFTDQryUserInvestorField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryUserInvestorFieldUse[]=
{
		{ FTD_FID_RspUserInvestor, &(CFTDRspUserInvestorField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDReqQryTradingCodeFieldUse[]=
{
		{ FTD_FID_QryTradingCode, &(CFTDQryTradingCodeField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryTradingCodeFieldUse[]=
{
		{ FTD_FID_RspTradingCode, &(CFTDRspTradingCodeField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDReqQryInvestorAccountFieldUse[]=
{
		{ FTD_FID_QryInvestorAccount, &(CFTDQryInvestorAccountField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryInvestorAccountFieldUse[]=
{
		{ FTD_FID_RspInvestorAccount, &(CFTDRspInvestorAccountField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDReqQryInstrumentFieldUse[]=
{
		{ FTD_FID_QryInstrument, &(CFTDQryInstrumentField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryInstrumentFieldUse[]=
{
		{ FTD_FID_RspInstrument, &(CFTDRspInstrumentField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDReqQryExchangeFieldUse[]=
{
		{ FTD_FID_QryExchange, &(CFTDQryExchangeField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryExchangeFieldUse[]=
{
		{ FTD_FID_RspExchange, &(CFTDRspExchangeField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDReqQryInvestorPositionFieldUse[]=
{
		{ FTD_FID_QryInvestorPosition, &(CFTDQryInvestorPositionField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryInvestorPositionFieldUse[]=
{
		{ FTD_FID_RspInvestorPosition, &(CFTDRspInvestorPositionField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDReqSubscribeTopicFieldUse[]=
{
		{ FTD_FID_Dissemination, &(CFTDDisseminationField::m_Describe), 0,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDRspSubscribeTopicFieldUse[]=
{
		{ FTD_FID_Dissemination, &(CFTDDisseminationField::m_Describe), 0,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDReqQryTopicFieldUse[]=
{
		{ FTD_FID_Dissemination, &(CFTDDisseminationField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryTopicFieldUse[]=
{
		{ FTD_FID_Dissemination, &(CFTDDisseminationField::m_Describe), 1,  1  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDReqQryUserFieldUse[]=
{
		{ FTD_FID_QryUser, &(CFTDQryUserField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryUserFieldUse[]=
{
		{ FTD_FID_User, &(CFTDUserField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDReqQryInvestorFeeFieldUse[]=
{
		{ FTD_FID_QryInvestorFee, &(CFTDQryInvestorFeeField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryInvestorFeeFieldUse[]=
{
		{ FTD_FID_InvestorFee, &(CFTDInvestorFeeField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDReqQryInvestorMarginFieldUse[]=
{
		{ FTD_FID_QryInvestorMargin, &(CFTDQryInvestorMarginField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryInvestorMarginFieldUse[]=
{
		{ FTD_FID_InvestorMargin, &(CFTDInvestorMarginField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDReqQrySGEDeferRateFieldUse[]=
{
		{ FTD_FID_QrySGEDeferRate, &(CFTDQrySGEDeferRateField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQrySGEDeferRateFieldUse[]=
{
		{ FTD_FID_SGEDeferRate, &(CFTDSGEDeferRateField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDReqQryInvestorPositionDetailFieldUse[]=
{
		{ FTD_FID_QryInvestorPositionDetail, &(CFTDQryInvestorPositionDetailField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDRspQryInvestorPositionDetailFieldUse[]=
{
		{ FTD_FID_RspInvestorPositionDetail, &(CFTDRspInvestorPositionDetailField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDReqQryInvestorOptionFeeFieldUse[]=
{
		{ FTD_FID_QryInvestorOptionFee, &(CFTDQryInvestorOptionFeeField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryInvestorOptionFeeFieldUse[]=
{
		{ FTD_FID_RspInvestorOptionFee, &(CFTDRspInvestorOptionFeeField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDIntlRtnDepthMarketDataFieldUse[]=
{
		{ FTD_FID_MarketDataBase, &(CFTDMarketDataBaseField::m_Describe), 0,  1  }
			,
		{ FTD_FID_MarketDataStatic, &(CFTDMarketDataStaticField::m_Describe), 0,  1  }
			,
		{ FTD_FID_MarketDataLastMatch, &(CFTDMarketDataLastMatchField::m_Describe), 0,  1  }
			,
		{ FTD_FID_MarketDataBestPrice, &(CFTDMarketDataBestPriceField::m_Describe), 0,  1  }
			,
		{ FTD_FID_MarketDataBid23, &(CFTDMarketDataBid23Field::m_Describe), 0,  1  }
			,
		{ FTD_FID_MarketDataAsk23, &(CFTDMarketDataAsk23Field::m_Describe), 0,  1  }
			,
		{ FTD_FID_MarketDataBid45, &(CFTDMarketDataBid45Field::m_Describe), 0,  1  }
			,
		{ FTD_FID_MarketDataAsk45, &(CFTDMarketDataAsk45Field::m_Describe), 0,  1  }
			,
		{ FTD_FID_MarketDataUpdateTime, &(CFTDMarketDataUpdateTimeField::m_Describe), 1,  1  }
			,
		{ FTD_FID_MarketDataExchangeID, &(CFTDMarketDataExchangeIDField::m_Describe), 0,  1  }
			,
		{ FTD_FID_MarketDataBid67, &(CFTDMarketDataBid67Field::m_Describe), 0,  1  }
			,
		{ FTD_FID_MarketDataAsk67, &(CFTDMarketDataAsk67Field::m_Describe), 0,  1  }
			,
		{ FTD_FID_MarketDataBid89, &(CFTDMarketDataBid89Field::m_Describe), 0,  1  }
			,
		{ FTD_FID_MarketDataAsk89, &(CFTDMarketDataAsk89Field::m_Describe), 0,  1  }
			,
		{ FTD_FID_MarketDataAskBid10, &(CFTDMarketDataAskBid10Field::m_Describe), 0,  1  }
};

TFieldUse FTDIntlTopicSearchFieldUse[]=
{
		{ FTD_FID_TopicSearch, &(CFTDTopicSearchField::m_Describe), 0,  1  }
};

TFieldUse FTDReqTopicSearchFieldUse[]=
{
		{ FTD_FID_SpecificInstrument, &(CFTDSpecificInstrumentField::m_Describe), 0,  1  }
};

TFieldUse FTDRtnDepthMarketDataFieldUse[]=
{
		{ FTD_FID_DepthMarketData, &(CFTDDepthMarketDataField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDRtnMultiDepthMarketDataFieldUse[]=
{
		{ FTD_FID_DepthMarketData, &(CFTDDepthMarketDataField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDReqSubMarketDataFieldUse[]=
{
		{ FTD_FID_SpecificInstrument, &(CFTDSpecificInstrumentField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDRspSubMarketDataFieldUse[]=
{
		{ FTD_FID_SpecificInstrument, &(CFTDSpecificInstrumentField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDReqUnSubMarketDataFieldUse[]=
{
		{ FTD_FID_SpecificInstrument, &(CFTDSpecificInstrumentField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDRspUnSubMarketDataFieldUse[]=
{
		{ FTD_FID_SpecificInstrument, &(CFTDSpecificInstrumentField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  1  }
};

TFieldUse FTDReqQryMarketDataFieldUse[]=
{
		{ FTD_FID_QryMarketData, &(CFTDQryMarketDataField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryMarketDataFieldUse[]=
{
		{ FTD_FID_MarketData, &(CFTDMarketDataField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDReqQryDepthMarketDataFieldUse[]=
{
		{ FTD_FID_QryMarketData, &(CFTDQryMarketDataField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryDepthMarketDataFieldUse[]=
{
		{ FTD_FID_RspMarketData, &(CFTDRspMarketDataField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse FTDReqQryMBLMarketDataFieldUse[]=
{
		{ FTD_FID_QryMBLMarketData, &(CFTDQryMBLMarketDataField::m_Describe), 1,  1  }
};

TFieldUse FTDRspQryMBLMarketDataFieldUse[]=
{
		{ FTD_FID_MBLMarketData, &(CFTDMBLMarketDataField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FTD_FID_RspInfo, &(CFTDRspInfoField::m_Describe), 1,  UNLIMITED_FIELD_OCCUR  }
};


TPackageDefine FTDPackageDefines[]=
{
	{ FTD_TID_RspError, 1, FTDRspErrorFieldUse }
		,
	{ FTD_TID_ReqUserLogin, 2, FTDReqUserLoginFieldUse }
		,
	{ FTD_TID_RspUserLogin, 2, FTDRspUserLoginFieldUse }
		,
	{ FTD_TID_ReqUserLogout, 1, FTDReqUserLogoutFieldUse }
		,
	{ FTD_TID_RspUserLogout, 2, FTDRspUserLogoutFieldUse }
		,
	{ FTD_TID_ReqUserPasswordUpdate, 1, FTDReqUserPasswordUpdateFieldUse }
		,
	{ FTD_TID_RspUserPasswordUpdate, 2, FTDRspUserPasswordUpdateFieldUse }
		,
	{ FTD_TID_ReqForceUserExit, 1, FTDReqForceUserExitFieldUse }
		,
	{ FTD_TID_RspForceUserExit, 2, FTDRspForceUserExitFieldUse }
		,
	{ FTD_TID_ReqForceUserLogout, 1, FTDReqForceUserLogoutFieldUse }
		,
	{ FTD_TID_RspForceUserLogout, 2, FTDRspForceUserLogoutFieldUse }
		,
	{ FTD_TID_ReqDumpMemDb, 1, FTDReqDumpMemDbFieldUse }
		,
	{ FTD_TID_ReqOrderInsert, 1, FTDReqOrderInsertFieldUse }
		,
	{ FTD_TID_RspOrderInsert, 2, FTDRspOrderInsertFieldUse }
		,
	{ FTD_TID_ReqOrderAction, 1, FTDReqOrderActionFieldUse }
		,
	{ FTD_TID_RspOrderAction, 2, FTDRspOrderActionFieldUse }
		,
	{ FTD_TID_ReqAccountDeposit, 1, FTDReqAccountDepositFieldUse }
		,
	{ FTD_TID_RspAccountDeposit, 2, FTDRspAccountDepositFieldUse }
		,
	{ FTD_TID_RtnFlowMessageCancel, 1, FTDRtnFlowMessageCancelFieldUse }
		,
	{ FTD_TID_IntlRtnDissemination, 1, FTDIntlRtnDisseminationFieldUse }
		,
	{ FTD_TID_RtnTrade, 1, FTDRtnTradeFieldUse }
		,
	{ FTD_TID_RtnOrder, 1, FTDRtnOrderFieldUse }
		,
	{ FTD_TID_ErrRtnOrderInsert, 2, FTDErrRtnOrderInsertFieldUse }
		,
	{ FTD_TID_ErrRtnOrderAction, 2, FTDErrRtnOrderActionFieldUse }
		,
	{ FTD_TID_RtnInstrumentStatus, 1, FTDRtnInstrumentStatusFieldUse }
		,
	{ FTD_TID_RtnInvestorAccountDeposit, 1, FTDRtnInvestorAccountDepositFieldUse }
		,
	{ FTD_TID_RtnMessageNotify, 1, FTDRtnMessageNotifyFieldUse }
		,
	{ FTD_TID_RtnSGEDeferRate, 1, FTDRtnSGEDeferRateFieldUse }
		,
	{ FTD_TID_RtnQmdInstrumentStatu, 1, FTDRtnQmdInstrumentStatuFieldUse }
		,
	{ FTD_TID_ReqQryOrder, 1, FTDReqQryOrderFieldUse }
		,
	{ FTD_TID_RspQryOrder, 2, FTDRspQryOrderFieldUse }
		,
	{ FTD_TID_ReqQryTrade, 1, FTDReqQryTradeFieldUse }
		,
	{ FTD_TID_RspQryTrade, 2, FTDRspQryTradeFieldUse }
		,
	{ FTD_TID_ReqQryUserInvestor, 1, FTDReqQryUserInvestorFieldUse }
		,
	{ FTD_TID_RspQryUserInvestor, 2, FTDRspQryUserInvestorFieldUse }
		,
	{ FTD_TID_ReqQryTradingCode, 1, FTDReqQryTradingCodeFieldUse }
		,
	{ FTD_TID_RspQryTradingCode, 2, FTDRspQryTradingCodeFieldUse }
		,
	{ FTD_TID_ReqQryInvestorAccount, 1, FTDReqQryInvestorAccountFieldUse }
		,
	{ FTD_TID_RspQryInvestorAccount, 2, FTDRspQryInvestorAccountFieldUse }
		,
	{ FTD_TID_ReqQryInstrument, 1, FTDReqQryInstrumentFieldUse }
		,
	{ FTD_TID_RspQryInstrument, 2, FTDRspQryInstrumentFieldUse }
		,
	{ FTD_TID_ReqQryExchange, 1, FTDReqQryExchangeFieldUse }
		,
	{ FTD_TID_RspQryExchange, 2, FTDRspQryExchangeFieldUse }
		,
	{ FTD_TID_ReqQryInvestorPosition, 1, FTDReqQryInvestorPositionFieldUse }
		,
	{ FTD_TID_RspQryInvestorPosition, 2, FTDRspQryInvestorPositionFieldUse }
		,
	{ FTD_TID_ReqSubscribeTopic, 1, FTDReqSubscribeTopicFieldUse }
		,
	{ FTD_TID_RspSubscribeTopic, 2, FTDRspSubscribeTopicFieldUse }
		,
	{ FTD_TID_ReqQryTopic, 1, FTDReqQryTopicFieldUse }
		,
	{ FTD_TID_RspQryTopic, 2, FTDRspQryTopicFieldUse }
		,
	{ FTD_TID_ReqQryUser, 1, FTDReqQryUserFieldUse }
		,
	{ FTD_TID_RspQryUser, 2, FTDRspQryUserFieldUse }
		,
	{ FTD_TID_ReqQryInvestorFee, 1, FTDReqQryInvestorFeeFieldUse }
		,
	{ FTD_TID_RspQryInvestorFee, 2, FTDRspQryInvestorFeeFieldUse }
		,
	{ FTD_TID_ReqQryInvestorMargin, 1, FTDReqQryInvestorMarginFieldUse }
		,
	{ FTD_TID_RspQryInvestorMargin, 2, FTDRspQryInvestorMarginFieldUse }
		,
	{ FTD_TID_ReqQrySGEDeferRate, 1, FTDReqQrySGEDeferRateFieldUse }
		,
	{ FTD_TID_RspQrySGEDeferRate, 2, FTDRspQrySGEDeferRateFieldUse }
		,
	{ FTD_TID_ReqQryInvestorPositionDetail, 1, FTDReqQryInvestorPositionDetailFieldUse }
		,
	{ FTD_TID_RspQryInvestorPositionDetail, 2, FTDRspQryInvestorPositionDetailFieldUse }
		,
	{ FTD_TID_ReqQryInvestorOptionFee, 1, FTDReqQryInvestorOptionFeeFieldUse }
		,
	{ FTD_TID_RspQryInvestorOptionFee, 2, FTDRspQryInvestorOptionFeeFieldUse }
		,
	{ FTD_TID_IntlRtnDepthMarketData, 15, FTDIntlRtnDepthMarketDataFieldUse }
		,
	{ FTD_TID_IntlTopicSearch, 1, FTDIntlTopicSearchFieldUse }
		,
	{ FTD_TID_ReqTopicSearch, 1, FTDReqTopicSearchFieldUse }
		,
	{ FTD_TID_RtnDepthMarketData, 1, FTDRtnDepthMarketDataFieldUse }
		,
	{ FTD_TID_RtnMultiDepthMarketData, 1, FTDRtnMultiDepthMarketDataFieldUse }
		,
	{ FTD_TID_ReqSubMarketData, 1, FTDReqSubMarketDataFieldUse }
		,
	{ FTD_TID_RspSubMarketData, 2, FTDRspSubMarketDataFieldUse }
		,
	{ FTD_TID_ReqUnSubMarketData, 1, FTDReqUnSubMarketDataFieldUse }
		,
	{ FTD_TID_RspUnSubMarketData, 2, FTDRspUnSubMarketDataFieldUse }
		,
	{ FTD_TID_ReqQryMarketData, 1, FTDReqQryMarketDataFieldUse }
		,
	{ FTD_TID_RspQryMarketData, 2, FTDRspQryMarketDataFieldUse }
		,
	{ FTD_TID_ReqQryDepthMarketData, 1, FTDReqQryDepthMarketDataFieldUse }
		,
	{ FTD_TID_RspQryDepthMarketData, 2, FTDRspQryDepthMarketDataFieldUse }
		,
	{ FTD_TID_ReqQryMBLMarketData, 1, FTDReqQryMBLMarketDataFieldUse }
		,
	{ FTD_TID_RspQryMBLMarketData, 2, FTDRspQryMBLMarketDataFieldUse }
};



class CFTDCPackageDefineMap: public CHashMap<DWORD, TPackageDefine *, HashInt>
{
public:
	CFTDCPackageDefineMap(TPackageDefine *pFTDCPackageDefines, int nDefineCount)
	{
		for(int i=0; i<nDefineCount; i++)
		{
			Insert(pFTDCPackageDefines->tid, pFTDCPackageDefines);
			pFTDCPackageDefines++;
		}
	}
};

CFTDCPackageDefineMap g_FTDCPackageDefineMap(FTDPackageDefines, sizeof(FTDPackageDefines)/ sizeof(TPackageDefine));

void FTDC_DEBUG_BODY(DWORD tid, CFieldSet *pPackage, CLogger *pLogger)
{
	pLogger->output("\tFTDC PACKAGE CONTENT START\n");					
	TPackageDefine **pFind = g_FTDCPackageDefineMap.Find(tid);	
	if(pFind == NULL)													
	{																	
		pLogger->output("\tCan't find package define [0x%08x]\n", tid);				
		return;															
	}																	
	char buf[10000];													
	TPackageDefine *pPackageDefine = *pFind;							
	CFieldTypeIterator itor = pPackage->GetFieldTypeIterator();			
	while(!itor.IsEnd())												
	{																	
		TFieldHeader fieldHeader;										
		itor.RetrieveHeader(fieldHeader);								
		TFieldUse *pFieldUse = pPackageDefine->fieldUse;				
		for(int i=0; i<pPackageDefine->fieldUseCount; i++)				
		{																
			if(pFieldUse->fid == fieldHeader.FieldID)					
			{															
				itor.Retrieve(pFieldUse->pFieldDescribe, buf);			
				FIELD_DEBUG(buf, pFieldUse->pFieldDescribe, pLogger);	
				break;													
			}															
			pFieldUse++;												
		}																
		itor.Next();													
	}																	
	pLogger->output("\tFTDC PACKAGE CONTENT END\n");						
}
