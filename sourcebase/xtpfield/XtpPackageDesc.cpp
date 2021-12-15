// XtpPackageDesc.cpp: 
//
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "XtpPackageDesc.h"


const char *getPackageName(DWORD tid)
{
	switch (tid)
	{
	case TID_Nop:
		return "Nop";
	case TID_RspError:
		return "RspError";
	case TID_ReqUserLogin:
		return "ReqUserLogin";
	case TID_RspUserLogin:
		return "RspUserLogin";
	case TID_ReqUserLogout:
		return "ReqUserLogout";
	case TID_RspUserLogout:
		return "RspUserLogout";
	case TID_ReqOrderInsert:
		return "ReqOrderInsert";
	case TID_RspOrderInsert:
		return "RspOrderInsert";
	case TID_ReqOrderAction:
		return "ReqOrderAction";
	case TID_RspOrderAction:
		return "RspOrderAction";
	case TID_ReqUserPasswordUpdate:
		return "ReqUserPasswordUpdate";
	case TID_RspUserPasswordUpdate:
		return "RspUserPasswordUpdate";
	case TID_ReqForceUserExit:
		return "ReqForceUserExit";
	case TID_RspForceUserExit:
		return "RspForceUserExit";
	case TID_ReqForceUserLogout:
		return "ReqForceUserLogout";
	case TID_RspForceUserLogout:
		return "RspForceUserLogout";
	case TID_ReqDumpMemDb:
		return "ReqDumpMemDb";
	case TID_UpdateSystemStatus:
		return "UpdateSystemStatus";
	case TID_ReqAccountDeposit:
		return "ReqAccountDeposit";
	case TID_RspAccountDeposit:
		return "RspAccountDeposit";
	case TID_ReqQryInvestorAccount:
		return "ReqQryInvestorAccount";
	case TID_RspQryInvestorAccount:
		return "RspQryInvestorAccount";
	case TID_ReqQryOrder:
		return "ReqQryOrder";
	case TID_RspQryOrder:
		return "RspQryOrder";
	case TID_ReqQryTrade:
		return "ReqQryTrade";
	case TID_RspQryTrade:
		return "RspQryTrade";
	case TID_ReqQryInvestor:
		return "ReqQryInvestor";
	case TID_RspQryInvestor:
		return "RspQryInvestor";
	case TID_ReqQryOrderInsertFailed:
		return "ReqQryOrderInsertFailed";
	case TID_ReqQryInstrument:
		return "ReqQryInstrument";
	case TID_RspQryInstrument:
		return "RspQryInstrument";
	case TID_ReqQryUser:
		return "ReqQryUser";
	case TID_RspQryUser:
		return "RspQryUser";
	case TID_ReqQryExchange:
		return "ReqQryExchange";
	case TID_RspQryExchange:
		return "RspQryExchange";
	case TID_ReqQryUserInvestor:
		return "ReqQryUserInvestor";
	case TID_RspQryUserInvestor:
		return "RspQryUserInvestor";
	case TID_ReqQryInvestorPosition:
		return "ReqQryInvestorPosition";
	case TID_RspQryInvestorPosition:
		return "RspQryInvestorPosition";
	case TID_ReqQryMarketData:
		return "ReqQryMarketData";
	case TID_RspQryMarketData:
		return "RspQryMarketData";
	case TID_ReqQryInvestorFee:
		return "ReqQryInvestorFee";
	case TID_RspQryInvestorFee:
		return "RspQryInvestorFee";
	case TID_ReqQryInvestorMargin:
		return "ReqQryInvestorMargin";
	case TID_RspQryInvestorMargin:
		return "RspQryInvestorMargin";
	case TID_ReqQryDepthMarketData:
		return "ReqQryDepthMarketData";
	case TID_RspQryDepthMarketData:
		return "RspQryDepthMarketData";
	case TID_ReqQrySGEDeferRate:
		return "ReqQrySGEDeferRate";
	case TID_RspQrySGEDeferRate:
		return "RspQrySGEDeferRate";
	case TID_ReqQryInvestorPositionDetail:
		return "ReqQryInvestorPositionDetail";
	case TID_RspQryInvestorPositionDetail:
		return "RspQryInvestorPositionDetail";
	case TID_ExInvestorPositionDetail:
		return "ExInvestorPositionDetail";
	case TID_ReqQryInvestorOptionFee:
		return "ReqQryInvestorOptionFee";
	case TID_RspQryInvestorOptionFee:
		return "RspQryInvestorOptionFee";
	case TID_DataSyncStart:
		return "DataSyncStart";
	case TID_DataSyncEnd:
		return "DataSyncEnd";
	case TID_InitExchange:
		return "InitExchange";
	case TID_InitSeat:
		return "InitSeat";
	case TID_InitUser:
		return "InitUser";
	case TID_InitInvestor:
		return "InitInvestor";
	case TID_InitClientTradingID:
		return "InitClientTradingID";
	case TID_InitUserInvestor:
		return "InitUserInvestor";
	case TID_InitUserTradingRight:
		return "InitUserTradingRight";
	case TID_InitInvestorAccount:
		return "InitInvestorAccount";
	case TID_InitInstrument:
		return "InitInstrument";
	case TID_InitInvestorMargin:
		return "InitInvestorMargin";
	case TID_InitInvestorFee:
		return "InitInvestorFee";
	case TID_InitInvestorPosition:
		return "InitInvestorPosition";
	case TID_DbInvestorAccountDeposit:
		return "DbInvestorAccountDeposit";
	case TID_DbInsUser:
		return "DbInsUser";
	case TID_DbUpdUser:
		return "DbUpdUser";
	case TID_InitSystemStatus:
		return "InitSystemStatus";
	case TID_InitInstrumentGroup:
		return "InitInstrumentGroup";
	case TID_InitClientMarginCombType:
		return "InitClientMarginCombType";
	case TID_InitSGEDeferRate:
		return "InitSGEDeferRate";
	case TID_DbClientTradingID:
		return "DbClientTradingID";
	case TID_InitCmbInstrumentDetail:
		return "InitCmbInstrumentDetail";
	case TID_InitInvestorTradingRight:
		return "InitInvestorTradingRight";
	case TID_DbUpdInvestorTradingRight:
		return "DbUpdInvestorTradingRight";
	case TID_DbInsInvestorTradingRight:
		return "DbInsInvestorTradingRight";
	case TID_DbDelInvestorTradingRight:
		return "DbDelInvestorTradingRight";
	case TID_DbUpdUserIP:
		return "DbUpdUserIP";
	case TID_DbInsUserIP:
		return "DbInsUserIP";
	case TID_DbDelUserIP:
		return "DbDelUserIP";
	case TID_InitUserIP:
		return "InitUserIP";
	case TID_InitInvestorOptionFee:
		return "InitInvestorOptionFee";
	case TID_InitSystemInfo:
		return "InitSystemInfo";
	case TID_NtfTimeSync:
		return "NtfTimeSync";
	case TID_NtfCommPhaseChange:
		return "NtfCommPhaseChange";
	case TID_NtfOrder:
		return "NtfOrder";
	case TID_NtfTrade:
		return "NtfTrade";
	case TID_NtfInstrumentStatusUpdate:
		return "NtfInstrumentStatusUpdate";
	case TID_NtfDelUserSession:
		return "NtfDelUserSession";
	case TID_NtfMarketData:
		return "NtfMarketData";
	case TID_NtfLifeCycle:
		return "NtfLifeCycle";
	case TID_NtfErrorOrderInsert:
		return "NtfErrorOrderInsert";
	case TID_NtfErrorOrderAction:
		return "NtfErrorOrderAction";
	case TID_NtfMemtableChange:
		return "NtfMemtableChange";
	case TID_ReqQueryExInstrument:
		return "ReqQueryExInstrument";
	case TID_RspQueryExInstrument:
		return "RspQueryExInstrument";
	case TID_RspQueryExTradingDay:
		return "RspQueryExTradingDay";
	case TID_RspQueryExInvestorPosition:
		return "RspQueryExInvestorPosition";
	case TID_RspQueryExMarketData:
		return "RspQueryExMarketData";
	case TID_ReqRollbakPreOrder:
		return "ReqRollbakPreOrder";
	case TID_NtfInvestorAccountDeposit:
		return "NtfInvestorAccountDeposit";
	case TID_QueryBaseFinish:
		return "QueryBaseFinish";
	case TID_RspQueryExCapitalData:
		return "RspQueryExCapitalData";
	case TID_RspQueryExCmbInstrumentDetail:
		return "RspQueryExCmbInstrumentDetail";
	case TID_NtfSGEDeferRate:
		return "NtfSGEDeferRate";
	case TID_InterLoginInfo:
		return "InterLoginInfo";
	case TID_NtfMessageNotify:
		return "NtfMessageNotify";
	case TID_InnerLogin:
		return "InnerLogin";
	case TID_ExQryMBLMarketData:
		return "ExQryMBLMarketData";
	case TID_ReqQryMBLMarketData:
		return "ReqQryMBLMarketData";
	case TID_RspQryMBLMarketData:
		return "RspQryMBLMarketData";
	case TID_NtfPositionProfit:
		return "NtfPositionProfit";
	}
	return "unknown";
}

TFieldUse NopFieldUse[]=
{
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  1  }
};

TFieldUse RspErrorFieldUse[]=
{
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  1  }
};

TFieldUse ReqUserLoginFieldUse[]=
{
		{ FID_UserLogin, &CUserLoginField::m_Describe, 1,  1  }
};

TFieldUse RspUserLoginFieldUse[]=
{
		{ FID_UserLogin, &CUserLoginField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  1  }
};

TFieldUse ReqUserLogoutFieldUse[]=
{
		{ FID_UserLogout, &CUserLogoutField::m_Describe, 1,  1  }
};

TFieldUse RspUserLogoutFieldUse[]=
{
		{ FID_UserLogout, &CUserLogoutField::m_Describe, 1,  1  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  1  }
};

TFieldUse ReqOrderInsertFieldUse[]=
{
		{ FID_InputOrder, &CInputOrderField::m_Describe, 1,  1  }
};

TFieldUse RspOrderInsertFieldUse[]=
{
		{ FID_InputOrder, &CInputOrderField::m_Describe, 1,  1  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  1  }
};

TFieldUse ReqOrderActionFieldUse[]=
{
		{ FID_OrderAction, &COrderActionField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse RspOrderActionFieldUse[]=
{
		{ FID_OrderAction, &COrderActionField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqUserPasswordUpdateFieldUse[]=
{
		{ FID_UserPasswordUpdate, &CUserPasswordUpdateField::m_Describe, 1,  1  }
};

TFieldUse RspUserPasswordUpdateFieldUse[]=
{
		{ FID_UserPasswordUpdate, &CUserPasswordUpdateField::m_Describe, 1,  1  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  1  }
};

TFieldUse ReqForceUserExitFieldUse[]=
{
		{ FID_ForceUserExit, &CForceUserExitField::m_Describe, 1,  1  }
};

TFieldUse RspForceUserExitFieldUse[]=
{
		{ FID_ForceUserExit, &CForceUserExitField::m_Describe, 1,  1  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  1  }
};

TFieldUse ReqForceUserLogoutFieldUse[]=
{
		{ FID_ForceUserExit, &CForceUserExitField::m_Describe, 1,  1  }
};

TFieldUse RspForceUserLogoutFieldUse[]=
{
		{ FID_ForceUserExit, &CForceUserExitField::m_Describe, 1,  1  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  1  }
};

TFieldUse ReqDumpMemDbFieldUse[]=
{
		{ FID_MemDb, &CMemDbField::m_Describe, 1,  1  }
};

TFieldUse UpdateSystemStatusFieldUse[]=
{
		{ FID_SystemStatus, &CSystemStatusField::m_Describe, 1,  1  }
};

TFieldUse ReqAccountDepositFieldUse[]=
{
		{ FID_AccountDeposit, &CAccountDepositField::m_Describe, 1,  1  }
};

TFieldUse RspAccountDepositFieldUse[]=
{
		{ FID_AccountDepositRes, &CAccountDepositResField::m_Describe, 1,  1  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  1  }
};

TFieldUse ReqQryInvestorAccountFieldUse[]=
{
		{ FID_QryInvestorAccount, &CQryInvestorAccountField::m_Describe, 1,  1  }
};

TFieldUse RspQryInvestorAccountFieldUse[]=
{
		{ FID_InvestorAccount, &CInvestorAccountField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqQryOrderFieldUse[]=
{
		{ FID_QryOrder, &CQryOrderField::m_Describe, 1,  1  }
};

TFieldUse RspQryOrderFieldUse[]=
{
		{ FID_Order, &COrderField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqQryTradeFieldUse[]=
{
		{ FID_QryTrade, &CQryTradeField::m_Describe, 1,  1  }
};

TFieldUse RspQryTradeFieldUse[]=
{
		{ FID_Trade, &CTradeField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqQryInvestorFieldUse[]=
{
		{ FID_QryInvestor, &CQryInvestorField::m_Describe, 1,  1  }
};

TFieldUse RspQryInvestorFieldUse[]=
{
		{ FID_Investor, &CInvestorField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqQryOrderInsertFailedFieldUse[]=
{
		{ FID_QryOrderInsertFailed, &CQryOrderInsertFailedField::m_Describe, 1,  1  }
};

TFieldUse ReqQryInstrumentFieldUse[]=
{
		{ FID_QryInstrument, &CQryInstrumentField::m_Describe, 1,  1  }
};

TFieldUse RspQryInstrumentFieldUse[]=
{
		{ FID_Instrument, &CInstrumentField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqQryUserFieldUse[]=
{
		{ FID_QryUser, &CQryUserField::m_Describe, 1,  1  }
};

TFieldUse RspQryUserFieldUse[]=
{
		{ FID_User, &CUserField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  1  }
};

TFieldUse ReqQryExchangeFieldUse[]=
{
		{ FID_QryExchange, &CQryExchangeField::m_Describe, 1,  1  }
};

TFieldUse RspQryExchangeFieldUse[]=
{
		{ FID_RspExchange, &CRspExchangeField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqQryUserInvestorFieldUse[]=
{
		{ FID_QryUserInvestor, &CQryUserInvestorField::m_Describe, 1,  1  }
};

TFieldUse RspQryUserInvestorFieldUse[]=
{
		{ FID_UserInvestor, &CUserInvestorField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqQryInvestorPositionFieldUse[]=
{
		{ FID_QryInvestorPosition, &CQryInvestorPositionField::m_Describe, 1,  1  }
};

TFieldUse RspQryInvestorPositionFieldUse[]=
{
		{ FID_InvestorPosition, &CInvestorPositionField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqQryMarketDataFieldUse[]=
{
		{ FID_QryMarketData, &CQryMarketDataField::m_Describe, 1,  1  }
};

TFieldUse RspQryMarketDataFieldUse[]=
{
		{ FID_MarketData, &CMarketDataField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqQryInvestorFeeFieldUse[]=
{
		{ FID_QryInvestorFee, &CQryInvestorFeeField::m_Describe, 1,  1  }
};

TFieldUse RspQryInvestorFeeFieldUse[]=
{
		{ FID_InvestorFee, &CInvestorFeeField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqQryInvestorMarginFieldUse[]=
{
		{ FID_QryInvestorMargin, &CQryInvestorMarginField::m_Describe, 1,  1  }
};

TFieldUse RspQryInvestorMarginFieldUse[]=
{
		{ FID_InvestorMargin, &CInvestorMarginField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqQryDepthMarketDataFieldUse[]=
{
		{ FID_QryMarketData, &CQryMarketDataField::m_Describe, 1,  1  }
};

TFieldUse RspQryDepthMarketDataFieldUse[]=
{
		{ FID_RspMarketData, &CRspMarketDataField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqQrySGEDeferRateFieldUse[]=
{
		{ FID_QrySGEDeferRate, &CQrySGEDeferRateField::m_Describe, 1,  1  }
};

TFieldUse RspQrySGEDeferRateFieldUse[]=
{
		{ FID_SGEDeferRate, &CSGEDeferRateField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqQryInvestorPositionDetailFieldUse[]=
{
		{ FID_QryInvestorPositionDetail, &CQryInvestorPositionDetailField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse RspQryInvestorPositionDetailFieldUse[]=
{
		{ FID_RspInvestorPositionDetail, &CRspInvestorPositionDetailField::m_Describe, 1,  1  }
};

TFieldUse ExInvestorPositionDetailFieldUse[]=
{
		{ FID_InvestorPositionDetail, &CInvestorPositionDetailField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqQryInvestorOptionFeeFieldUse[]=
{
		{ FID_QryInvestorOptionFee, &CQryInvestorOptionFeeField::m_Describe, 1,  1  }
};

TFieldUse RspQryInvestorOptionFeeFieldUse[]=
{
		{ FID_InvestorOptionFee, &CInvestorOptionFeeField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse DataSyncStartFieldUse[]=
{
		{ FID_TradingDay, &CTradingDayField::m_Describe, 1,  1  }
};

TFieldUse DataSyncEndFieldUse[]=
{
		{ FID_TradingDay, &CTradingDayField::m_Describe, 1,  1  }
};

TFieldUse InitExchangeFieldUse[]=
{
		{ FID_Exchange, &CExchangeField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitSeatFieldUse[]=
{
		{ FID_Seat, &CSeatField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitUserFieldUse[]=
{
		{ FID_User, &CUserField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitInvestorFieldUse[]=
{
		{ FID_Investor, &CInvestorField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitClientTradingIDFieldUse[]=
{
		{ FID_ClientTradingID, &CClientTradingIDField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitUserInvestorFieldUse[]=
{
		{ FID_UserInvestor, &CUserInvestorField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitUserTradingRightFieldUse[]=
{
		{ FID_UserTradingRight, &CUserTradingRightField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitInvestorAccountFieldUse[]=
{
		{ FID_InvestorAccount, &CInvestorAccountField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitInstrumentFieldUse[]=
{
		{ FID_Instrument, &CInstrumentField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitInvestorMarginFieldUse[]=
{
		{ FID_InvestorMargin, &CInvestorMarginField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitInvestorFeeFieldUse[]=
{
		{ FID_InvestorFee, &CInvestorFeeField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitInvestorPositionFieldUse[]=
{
		{ FID_InvestorPosition, &CInvestorPositionField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse DbInvestorAccountDepositFieldUse[]=
{
		{ FID_DbmtInvestorAccountDeposit, &CDbmtInvestorAccountDepositField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse DbInsUserFieldUse[]=
{
		{ FID_DbmtUser, &CDbmtUserField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse DbUpdUserFieldUse[]=
{
		{ FID_DbmtUser, &CDbmtUserField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitSystemStatusFieldUse[]=
{
		{ FID_SystemStatus, &CSystemStatusField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitInstrumentGroupFieldUse[]=
{
		{ FID_InstrumentGroup, &CInstrumentGroupField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitClientMarginCombTypeFieldUse[]=
{
		{ FID_ClientMarginCombType, &CClientMarginCombTypeField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitSGEDeferRateFieldUse[]=
{
		{ FID_SGEDeferRate, &CSGEDeferRateField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse DbClientTradingIDFieldUse[]=
{
		{ FID_DbmtClientTradingID, &CDbmtClientTradingIDField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitCmbInstrumentDetailFieldUse[]=
{
		{ FID_CmbInstrumentDetail, &CCmbInstrumentDetailField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitInvestorTradingRightFieldUse[]=
{
		{ FID_InvestorTradingRight, &CInvestorTradingRightField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse DbUpdInvestorTradingRightFieldUse[]=
{
		{ FID_DbmtInvestorTradingRight, &CDbmtInvestorTradingRightField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse DbInsInvestorTradingRightFieldUse[]=
{
		{ FID_DbmtInvestorTradingRight, &CDbmtInvestorTradingRightField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse DbDelInvestorTradingRightFieldUse[]=
{
		{ FID_DbmtInvestorTradingRight, &CDbmtInvestorTradingRightField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse DbUpdUserIPFieldUse[]=
{
		{ FID_DbmtUserIP, &CDbmtUserIPField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse DbInsUserIPFieldUse[]=
{
		{ FID_DbmtUserIP, &CDbmtUserIPField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse DbDelUserIPFieldUse[]=
{
		{ FID_DbmtUserIP, &CDbmtUserIPField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitUserIPFieldUse[]=
{
		{ FID_UserIP, &CUserIPField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitInvestorOptionFeeFieldUse[]=
{
		{ FID_InvestorOptionFee, &CInvestorOptionFeeField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse InitSystemInfoFieldUse[]=
{
		{ FID_SystemInfo, &CSystemInfoField::m_Describe, 1,  1  }
};

TFieldUse NtfTimeSyncFieldUse[]=
{
		{ FID_CurrentTime, &CCurrentTimeField::m_Describe, 1,  1  }
};

TFieldUse NtfCommPhaseChangeFieldUse[]=
{
		{ FID_CommPhase, &CCommPhaseField::m_Describe, 1,  1  }
};

TFieldUse NtfOrderFieldUse[]=
{
		{ FID_Order, &COrderField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse NtfTradeFieldUse[]=
{
		{ FID_Trade, &CTradeField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse NtfInstrumentStatusUpdateFieldUse[]=
{
		{ FID_InstrumentStatus, &CInstrumentStatusField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse NtfDelUserSessionFieldUse[]=
{
		{ FID_UserSession, &CUserSessionField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse NtfMarketDataFieldUse[]=
{
		{ FID_MarketData, &CMarketDataField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse NtfLifeCycleFieldUse[]=
{
		{ FID_LifeCycleID, &CLifeCycleIDField::m_Describe, 1,  1  }
};

TFieldUse NtfErrorOrderInsertFieldUse[]=
{
		{ FID_InputOrder, &CInputOrderField::m_Describe, 1,  1  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  1  }
};

TFieldUse NtfErrorOrderActionFieldUse[]=
{
		{ FID_OrderAction, &COrderActionField::m_Describe, 1,  1  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  1  }
};

TFieldUse NtfMemtableChangeFieldUse[]=
{
		{ FID_MemtableChange, &CMemtableChangeField::m_Describe, 1,  1  }
};

TFieldUse ReqQueryExInstrumentFieldUse[]=
{
		{ FID_Exchange, &CExchangeField::m_Describe, 1,  1  }
};

TFieldUse RspQueryExInstrumentFieldUse[]=
{
		{ FID_Instrument, &CInstrumentField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse RspQueryExTradingDayFieldUse[]=
{
		{ FID_ExchangeTradingDay, &CExchangeTradingDayField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse RspQueryExInvestorPositionFieldUse[]=
{
		{ FID_InvestorPosition, &CInvestorPositionField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse RspQueryExMarketDataFieldUse[]=
{
		{ FID_MarketData, &CMarketDataField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse ReqRollbakPreOrderFieldUse[]=
{
		{ FID_QueryFinishNotify, &CQueryFinishNotifyField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse NtfInvestorAccountDepositFieldUse[]=
{
		{ FID_InvestorAccountDepositNtf, &CInvestorAccountDepositNtfField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse QueryBaseFinishFieldUse[]=
{
		{ FID_QueryFinishNotify, &CQueryFinishNotifyField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse RspQueryExCapitalDataFieldUse[]=
{
		{ FID_ExCapitalData, &CExCapitalDataField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse RspQueryExCmbInstrumentDetailFieldUse[]=
{
		{ FID_CmbInstrumentDetail, &CCmbInstrumentDetailField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse NtfSGEDeferRateFieldUse[]=
{
		{ FID_SGEDeferRate, &CSGEDeferRateField::m_Describe, 1,  1  }
};

TFieldUse InterLoginInfoFieldUse[]=
{
		{ FID_InterLoginInfo, &CInterLoginInfoField::m_Describe, 1,  1  }
};

TFieldUse NtfMessageNotifyFieldUse[]=
{
		{ FID_MessageNotifyInfo, &CMessageNotifyInfoField::m_Describe, 1,  1  }
};

TFieldUse InnerLoginFieldUse[]=
{
		{ FID_InnerLogin, &CInnerLoginField::m_Describe, 1,  1  }
};

TFieldUse ExQryMBLMarketDataFieldUse[]=
{
		{ FID_MBLMarketData, &CMBLMarketDataField::m_Describe, 1,  1  }
};

TFieldUse ReqQryMBLMarketDataFieldUse[]=
{
		{ FID_QryMBLMarketData, &CQryMBLMarketDataField::m_Describe, 1,  1  }
};

TFieldUse RspQryMBLMarketDataFieldUse[]=
{
		{ FID_MBLMarketData, &CMBLMarketDataField::m_Describe, 1,  1  }
			,
		{ FID_RspInfo, &CRspInfoField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};

TFieldUse NtfPositionProfitFieldUse[]=
{
		{ FID_PositionProfit, &CPositionProfitField::m_Describe, 1,  UNLIMITED_FIELD_OCCUR  }
};


TPackageDefine XTPPackageDefines[]=
{
	{ TID_Nop, 1, NopFieldUse, "Nop", "空操作" }
		,
	{ TID_RspError, 1, RspErrorFieldUse, "RspError", "错误应答" }
		,
	{ TID_ReqUserLogin, 1, ReqUserLoginFieldUse, "ReqUserLogin", "用户登录请求" }
		,
	{ TID_RspUserLogin, 2, RspUserLoginFieldUse, "RspUserLogin", "用户登录应答" }
		,
	{ TID_ReqUserLogout, 1, ReqUserLogoutFieldUse, "ReqUserLogout", "用户退出请求" }
		,
	{ TID_RspUserLogout, 2, RspUserLogoutFieldUse, "RspUserLogout", "用户退出应答" }
		,
	{ TID_ReqOrderInsert, 1, ReqOrderInsertFieldUse, "ReqOrderInsert", "报单录入请求" }
		,
	{ TID_RspOrderInsert, 2, RspOrderInsertFieldUse, "RspOrderInsert", "报单录入应答" }
		,
	{ TID_ReqOrderAction, 1, ReqOrderActionFieldUse, "ReqOrderAction", "报单操作请求" }
		,
	{ TID_RspOrderAction, 2, RspOrderActionFieldUse, "RspOrderAction", "报单操作应答" }
		,
	{ TID_ReqUserPasswordUpdate, 1, ReqUserPasswordUpdateFieldUse, "ReqUserPasswordUpdate", "用户密码修改请求" }
		,
	{ TID_RspUserPasswordUpdate, 2, RspUserPasswordUpdateFieldUse, "RspUserPasswordUpdate", "用户密码修改应答" }
		,
	{ TID_ReqForceUserExit, 1, ReqForceUserExitFieldUse, "ReqForceUserExit", "强制用户退出请求" }
		,
	{ TID_RspForceUserExit, 2, RspForceUserExitFieldUse, "RspForceUserExit", "强制用户退出应答" }
		,
	{ TID_ReqForceUserLogout, 1, ReqForceUserLogoutFieldUse, "ReqForceUserLogout", "用户会话删除请求" }
		,
	{ TID_RspForceUserLogout, 2, RspForceUserLogoutFieldUse, "RspForceUserLogout", "用户会话删除应答" }
		,
	{ TID_ReqDumpMemDb, 1, ReqDumpMemDbFieldUse, "ReqDumpMemDb", "请求导出内存数据库" }
		,
	{ TID_UpdateSystemStatus, 1, UpdateSystemStatusFieldUse, "UpdateSystemStatus", "更新系统状态" }
		,
	{ TID_ReqAccountDeposit, 1, ReqAccountDepositFieldUse, "ReqAccountDeposit", "投资者资金帐户出入金请求" }
		,
	{ TID_RspAccountDeposit, 2, RspAccountDepositFieldUse, "RspAccountDeposit", "投资者资金帐户出入金应答" }
		,
	{ TID_ReqQryInvestorAccount, 1, ReqQryInvestorAccountFieldUse, "ReqQryInvestorAccount", "投资者资金查询请求" }
		,
	{ TID_RspQryInvestorAccount, 2, RspQryInvestorAccountFieldUse, "RspQryInvestorAccount", "投资者资金查询应答" }
		,
	{ TID_ReqQryOrder, 1, ReqQryOrderFieldUse, "ReqQryOrder", "报单查询请求" }
		,
	{ TID_RspQryOrder, 2, RspQryOrderFieldUse, "RspQryOrder", "报单查询应答" }
		,
	{ TID_ReqQryTrade, 1, ReqQryTradeFieldUse, "ReqQryTrade", "成交单查询请求" }
		,
	{ TID_RspQryTrade, 2, RspQryTradeFieldUse, "RspQryTrade", "成交单查询应答" }
		,
	{ TID_ReqQryInvestor, 1, ReqQryInvestorFieldUse, "ReqQryInvestor", "投资者查询请求" }
		,
	{ TID_RspQryInvestor, 2, RspQryInvestorFieldUse, "RspQryInvestor", "投资者查询应答" }
		,
	{ TID_ReqQryOrderInsertFailed, 1, ReqQryOrderInsertFailedFieldUse, "ReqQryOrderInsertFailed", "报单查询请求" }
		,
	{ TID_ReqQryInstrument, 1, ReqQryInstrumentFieldUse, "ReqQryInstrument", "合约查询请求" }
		,
	{ TID_RspQryInstrument, 2, RspQryInstrumentFieldUse, "RspQryInstrument", "合约查询应答" }
		,
	{ TID_ReqQryUser, 1, ReqQryUserFieldUse, "ReqQryUser", "用户查询请求" }
		,
	{ TID_RspQryUser, 2, RspQryUserFieldUse, "RspQryUser", "用户查询应答" }
		,
	{ TID_ReqQryExchange, 1, ReqQryExchangeFieldUse, "ReqQryExchange", "交易所查询请求" }
		,
	{ TID_RspQryExchange, 2, RspQryExchangeFieldUse, "RspQryExchange", "交易所查询应答" }
		,
	{ TID_ReqQryUserInvestor, 1, ReqQryUserInvestorFieldUse, "ReqQryUserInvestor", "可用投资者账户查询请求" }
		,
	{ TID_RspQryUserInvestor, 2, RspQryUserInvestorFieldUse, "RspQryUserInvestor", "可用投资者账户查询应答" }
		,
	{ TID_ReqQryInvestorPosition, 1, ReqQryInvestorPositionFieldUse, "ReqQryInvestorPosition", "投资者持仓查询请求" }
		,
	{ TID_RspQryInvestorPosition, 2, RspQryInvestorPositionFieldUse, "RspQryInvestorPosition", "投资者持仓查询应答" }
		,
	{ TID_ReqQryMarketData, 1, ReqQryMarketDataFieldUse, "ReqQryMarketData", "普通行情查询请求" }
		,
	{ TID_RspQryMarketData, 2, RspQryMarketDataFieldUse, "RspQryMarketData", "普通行情查询应答" }
		,
	{ TID_ReqQryInvestorFee, 1, ReqQryInvestorFeeFieldUse, "ReqQryInvestorFee", "投资者手续费率查询请求" }
		,
	{ TID_RspQryInvestorFee, 2, RspQryInvestorFeeFieldUse, "RspQryInvestorFee", "投资者手续费率查询应答" }
		,
	{ TID_ReqQryInvestorMargin, 1, ReqQryInvestorMarginFieldUse, "ReqQryInvestorMargin", "投资者保证金率查询请求" }
		,
	{ TID_RspQryInvestorMargin, 2, RspQryInvestorMarginFieldUse, "RspQryInvestorMargin", "投资者保证金率查询应答" }
		,
	{ TID_ReqQryDepthMarketData, 1, ReqQryDepthMarketDataFieldUse, "ReqQryDepthMarketData", "行情查询请求" }
		,
	{ TID_RspQryDepthMarketData, 2, RspQryDepthMarketDataFieldUse, "RspQryDepthMarketData", "行情查询应答" }
		,
	{ TID_ReqQrySGEDeferRate, 1, ReqQrySGEDeferRateFieldUse, "ReqQrySGEDeferRate", "金交所递延费率查询请求" }
		,
	{ TID_RspQrySGEDeferRate, 2, RspQrySGEDeferRateFieldUse, "RspQrySGEDeferRate", "金交所递延费率查询应答" }
		,
	{ TID_ReqQryInvestorPositionDetail, 1, ReqQryInvestorPositionDetailFieldUse, "ReqQryInvestorPositionDetail", "持仓明细查询请求" }
		,
	{ TID_RspQryInvestorPositionDetail, 1, RspQryInvestorPositionDetailFieldUse, "RspQryInvestorPositionDetail", "持仓明细查询应答" }
		,
	{ TID_ExInvestorPositionDetail, 1, ExInvestorPositionDetailFieldUse, "ExInvestorPositionDetail", "持仓明细表" }
		,
	{ TID_ReqQryInvestorOptionFee, 1, ReqQryInvestorOptionFeeFieldUse, "ReqQryInvestorOptionFee", "投资者期权手续费率查询请求" }
		,
	{ TID_RspQryInvestorOptionFee, 2, RspQryInvestorOptionFeeFieldUse, "RspQryInvestorOptionFee", "投资者期权手续费率查询应答" }
		,
	{ TID_DataSyncStart, 1, DataSyncStartFieldUse, "DataSyncStart", "数据同步开始" }
		,
	{ TID_DataSyncEnd, 1, DataSyncEndFieldUse, "DataSyncEnd", "数据同步结束" }
		,
	{ TID_InitExchange, 1, InitExchangeFieldUse, "InitExchange", "交易所" }
		,
	{ TID_InitSeat, 1, InitSeatFieldUse, "InitSeat", "席位" }
		,
	{ TID_InitUser, 1, InitUserFieldUse, "InitUser", "用户" }
		,
	{ TID_InitInvestor, 1, InitInvestorFieldUse, "InitInvestor", "投资者" }
		,
	{ TID_InitClientTradingID, 1, InitClientTradingIDFieldUse, "InitClientTradingID", "交易编码" }
		,
	{ TID_InitUserInvestor, 1, InitUserInvestorFieldUse, "InitUserInvestor", "用户投资者关系" }
		,
	{ TID_InitUserTradingRight, 1, InitUserTradingRightFieldUse, "InitUserTradingRight", "用户交易权限" }
		,
	{ TID_InitInvestorAccount, 1, InitInvestorAccountFieldUse, "InitInvestorAccount", "投资者资金账户" }
		,
	{ TID_InitInstrument, 1, InitInstrumentFieldUse, "InitInstrument", "合约" }
		,
	{ TID_InitInvestorMargin, 1, InitInvestorMarginFieldUse, "InitInvestorMargin", "投资者保证金率" }
		,
	{ TID_InitInvestorFee, 1, InitInvestorFeeFieldUse, "InitInvestorFee", "投资者手续费" }
		,
	{ TID_InitInvestorPosition, 1, InitInvestorPositionFieldUse, "InitInvestorPosition", "投资者持仓" }
		,
	{ TID_DbInvestorAccountDeposit, 1, DbInvestorAccountDepositFieldUse, "DbInvestorAccountDeposit", "客户资金帐户出入金" }
		,
	{ TID_DbInsUser, 1, DbInsUserFieldUse, "DbInsUser", "增加交易用户" }
		,
	{ TID_DbUpdUser, 1, DbUpdUserFieldUse, "DbUpdUser", "修改交易用户" }
		,
	{ TID_InitSystemStatus, 1, InitSystemStatusFieldUse, "InitSystemStatus", "系统状态" }
		,
	{ TID_InitInstrumentGroup, 1, InitInstrumentGroupFieldUse, "InitInstrumentGroup", "合约和合约组关系" }
		,
	{ TID_InitClientMarginCombType, 1, InitClientMarginCombTypeFieldUse, "InitClientMarginCombType", "交易编码组合保证金类型" }
		,
	{ TID_InitSGEDeferRate, 1, InitSGEDeferRateFieldUse, "InitSGEDeferRate", "金交所递延费率信息表" }
		,
	{ TID_DbClientTradingID, 1, DbClientTradingIDFieldUse, "DbClientTradingID", "客户资金帐户出入金" }
		,
	{ TID_InitCmbInstrumentDetail, 1, InitCmbInstrumentDetailFieldUse, "InitCmbInstrumentDetail", "组合合约明细应答" }
		,
	{ TID_InitInvestorTradingRight, 1, InitInvestorTradingRightFieldUse, "InitInvestorTradingRight", "投资者交易权限" }
		,
	{ TID_DbUpdInvestorTradingRight, 1, DbUpdInvestorTradingRightFieldUse, "DbUpdInvestorTradingRight", "修改投资者权限" }
		,
	{ TID_DbInsInvestorTradingRight, 1, DbInsInvestorTradingRightFieldUse, "DbInsInvestorTradingRight", "增加投资者权限" }
		,
	{ TID_DbDelInvestorTradingRight, 1, DbDelInvestorTradingRightFieldUse, "DbDelInvestorTradingRight", "删除投资者权限" }
		,
	{ TID_DbUpdUserIP, 1, DbUpdUserIPFieldUse, "DbUpdUserIP", "交易员IP" }
		,
	{ TID_DbInsUserIP, 1, DbInsUserIPFieldUse, "DbInsUserIP", "交易员IP" }
		,
	{ TID_DbDelUserIP, 1, DbDelUserIPFieldUse, "DbDelUserIP", "交易员IP" }
		,
	{ TID_InitUserIP, 1, InitUserIPFieldUse, "InitUserIP", "交易员IP" }
		,
	{ TID_InitInvestorOptionFee, 1, InitInvestorOptionFeeFieldUse, "InitInvestorOptionFee", "投资者期权手续费" }
		,
	{ TID_InitSystemInfo, 1, InitSystemInfoFieldUse, "InitSystemInfo", "QDP系统信息表" }
		,
	{ TID_NtfTimeSync, 1, NtfTimeSyncFieldUse, "NtfTimeSync", "时间同步" }
		,
	{ TID_NtfCommPhaseChange, 1, NtfCommPhaseChangeFieldUse, "NtfCommPhaseChange", "通讯阶段切换通知" }
		,
	{ TID_NtfOrder, 1, NtfOrderFieldUse, "NtfOrder", "报单通知" }
		,
	{ TID_NtfTrade, 1, NtfTradeFieldUse, "NtfTrade", "成交通知" }
		,
	{ TID_NtfInstrumentStatusUpdate, 1, NtfInstrumentStatusUpdateFieldUse, "NtfInstrumentStatusUpdate", "合约交易状态改变通知" }
		,
	{ TID_NtfDelUserSession, 1, NtfDelUserSessionFieldUse, "NtfDelUserSession", "会话删除通知" }
		,
	{ TID_NtfMarketData, 1, NtfMarketDataFieldUse, "NtfMarketData", "普通行情通知" }
		,
	{ TID_NtfLifeCycle, 1, NtfLifeCycleFieldUse, "NtfLifeCycle", "通知生命周期号" }
		,
	{ TID_NtfErrorOrderInsert, 2, NtfErrorOrderInsertFieldUse, "NtfErrorOrderInsert", "报单录入错误通知" }
		,
	{ TID_NtfErrorOrderAction, 2, NtfErrorOrderActionFieldUse, "NtfErrorOrderAction", "报单操作错误通知" }
		,
	{ TID_NtfMemtableChange, 1, NtfMemtableChangeFieldUse, "NtfMemtableChange", "内存表变化通知" }
		,
	{ TID_ReqQueryExInstrument, 1, ReqQueryExInstrumentFieldUse, "ReqQueryExInstrument", "通知报盘机查询合约请求" }
		,
	{ TID_RspQueryExInstrument, 2, RspQueryExInstrumentFieldUse, "RspQueryExInstrument", "报盘机查询合约应答" }
		,
	{ TID_RspQueryExTradingDay, 2, RspQueryExTradingDayFieldUse, "RspQueryExTradingDay", "报盘机查询交易日应答" }
		,
	{ TID_RspQueryExInvestorPosition, 2, RspQueryExInvestorPositionFieldUse, "RspQueryExInvestorPosition", "报盘机查询客户持仓应答" }
		,
	{ TID_RspQueryExMarketData, 2, RspQueryExMarketDataFieldUse, "RspQueryExMarketData", "报盘机查询行情应答" }
		,
	{ TID_ReqRollbakPreOrder, 1, ReqRollbakPreOrderFieldUse, "ReqRollbakPreOrder", "解冻InnerLink未报入交易的报单" }
		,
	{ TID_NtfInvestorAccountDeposit, 1, NtfInvestorAccountDepositFieldUse, "NtfInvestorAccountDeposit", "出入金回报通知" }
		,
	{ TID_QueryBaseFinish, 1, QueryBaseFinishFieldUse, "QueryBaseFinish", "报盘机查询结束" }
		,
	{ TID_RspQueryExCapitalData, 2, RspQueryExCapitalDataFieldUse, "RspQueryExCapitalData", "报盘机查询资金应答" }
		,
	{ TID_RspQueryExCmbInstrumentDetail, 2, RspQueryExCmbInstrumentDetailFieldUse, "RspQueryExCmbInstrumentDetail", "报盘机查询组合合约明细应答" }
		,
	{ TID_NtfSGEDeferRate, 1, NtfSGEDeferRateFieldUse, "NtfSGEDeferRate", "金交所递延费率通知" }
		,
	{ TID_InterLoginInfo, 1, InterLoginInfoFieldUse, "InterLoginInfo", "成功登陆通知" }
		,
	{ TID_NtfMessageNotify, 1, NtfMessageNotifyFieldUse, "NtfMessageNotify", "QDP警告消息通知" }
		,
	{ TID_InnerLogin, 1, InnerLoginFieldUse, "InnerLogin", "内部登录请求" }
		,
	{ TID_ExQryMBLMarketData, 1, ExQryMBLMarketDataFieldUse, "ExQryMBLMarketData", "内部分价表查询应答" }
		,
	{ TID_ReqQryMBLMarketData, 1, ReqQryMBLMarketDataFieldUse, "ReqQryMBLMarketData", "分价表查询请求" }
		,
	{ TID_RspQryMBLMarketData, 2, RspQryMBLMarketDataFieldUse, "RspQryMBLMarketData", "分价表查询应答" }
		,
	{ TID_NtfPositionProfit, 1, NtfPositionProfitFieldUse, "NtfPositionProfit", "内存表变化通知" }
};


CXTPPackageDefineMap g_XTPPackageDefineMap(XTPPackageDefines, sizeof(XTPPackageDefines)/ sizeof(TPackageDefine));

void XTP_DEBUG_BODY(DWORD tid, CFieldSet *pPackage, CLogger *pLogger)
{
	pLogger->output(LL_DEBUG, "\tXTP PACKAGE CONTENT START\n");					
	TPackageDefine **pFind = g_XTPPackageDefineMap.Find(tid);	
	if(pFind == NULL)													
	{																	
		pLogger->output(LL_DEBUG, "\tCan't find package define [%08x]\n", tid);				
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
	pLogger->output(LL_DEBUG, "\tXTP PACKAGE CONTENT END\n");						
}
