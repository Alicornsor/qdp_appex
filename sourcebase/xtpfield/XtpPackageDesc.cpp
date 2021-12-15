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
	{ TID_Nop, 1, NopFieldUse, "Nop", "�ղ���" }
		,
	{ TID_RspError, 1, RspErrorFieldUse, "RspError", "����Ӧ��" }
		,
	{ TID_ReqUserLogin, 1, ReqUserLoginFieldUse, "ReqUserLogin", "�û���¼����" }
		,
	{ TID_RspUserLogin, 2, RspUserLoginFieldUse, "RspUserLogin", "�û���¼Ӧ��" }
		,
	{ TID_ReqUserLogout, 1, ReqUserLogoutFieldUse, "ReqUserLogout", "�û��˳�����" }
		,
	{ TID_RspUserLogout, 2, RspUserLogoutFieldUse, "RspUserLogout", "�û��˳�Ӧ��" }
		,
	{ TID_ReqOrderInsert, 1, ReqOrderInsertFieldUse, "ReqOrderInsert", "����¼������" }
		,
	{ TID_RspOrderInsert, 2, RspOrderInsertFieldUse, "RspOrderInsert", "����¼��Ӧ��" }
		,
	{ TID_ReqOrderAction, 1, ReqOrderActionFieldUse, "ReqOrderAction", "������������" }
		,
	{ TID_RspOrderAction, 2, RspOrderActionFieldUse, "RspOrderAction", "��������Ӧ��" }
		,
	{ TID_ReqUserPasswordUpdate, 1, ReqUserPasswordUpdateFieldUse, "ReqUserPasswordUpdate", "�û������޸�����" }
		,
	{ TID_RspUserPasswordUpdate, 2, RspUserPasswordUpdateFieldUse, "RspUserPasswordUpdate", "�û������޸�Ӧ��" }
		,
	{ TID_ReqForceUserExit, 1, ReqForceUserExitFieldUse, "ReqForceUserExit", "ǿ���û��˳�����" }
		,
	{ TID_RspForceUserExit, 2, RspForceUserExitFieldUse, "RspForceUserExit", "ǿ���û��˳�Ӧ��" }
		,
	{ TID_ReqForceUserLogout, 1, ReqForceUserLogoutFieldUse, "ReqForceUserLogout", "�û��Ựɾ������" }
		,
	{ TID_RspForceUserLogout, 2, RspForceUserLogoutFieldUse, "RspForceUserLogout", "�û��Ựɾ��Ӧ��" }
		,
	{ TID_ReqDumpMemDb, 1, ReqDumpMemDbFieldUse, "ReqDumpMemDb", "���󵼳��ڴ����ݿ�" }
		,
	{ TID_UpdateSystemStatus, 1, UpdateSystemStatusFieldUse, "UpdateSystemStatus", "����ϵͳ״̬" }
		,
	{ TID_ReqAccountDeposit, 1, ReqAccountDepositFieldUse, "ReqAccountDeposit", "Ͷ�����ʽ��ʻ����������" }
		,
	{ TID_RspAccountDeposit, 2, RspAccountDepositFieldUse, "RspAccountDeposit", "Ͷ�����ʽ��ʻ������Ӧ��" }
		,
	{ TID_ReqQryInvestorAccount, 1, ReqQryInvestorAccountFieldUse, "ReqQryInvestorAccount", "Ͷ�����ʽ��ѯ����" }
		,
	{ TID_RspQryInvestorAccount, 2, RspQryInvestorAccountFieldUse, "RspQryInvestorAccount", "Ͷ�����ʽ��ѯӦ��" }
		,
	{ TID_ReqQryOrder, 1, ReqQryOrderFieldUse, "ReqQryOrder", "������ѯ����" }
		,
	{ TID_RspQryOrder, 2, RspQryOrderFieldUse, "RspQryOrder", "������ѯӦ��" }
		,
	{ TID_ReqQryTrade, 1, ReqQryTradeFieldUse, "ReqQryTrade", "�ɽ�����ѯ����" }
		,
	{ TID_RspQryTrade, 2, RspQryTradeFieldUse, "RspQryTrade", "�ɽ�����ѯӦ��" }
		,
	{ TID_ReqQryInvestor, 1, ReqQryInvestorFieldUse, "ReqQryInvestor", "Ͷ���߲�ѯ����" }
		,
	{ TID_RspQryInvestor, 2, RspQryInvestorFieldUse, "RspQryInvestor", "Ͷ���߲�ѯӦ��" }
		,
	{ TID_ReqQryOrderInsertFailed, 1, ReqQryOrderInsertFailedFieldUse, "ReqQryOrderInsertFailed", "������ѯ����" }
		,
	{ TID_ReqQryInstrument, 1, ReqQryInstrumentFieldUse, "ReqQryInstrument", "��Լ��ѯ����" }
		,
	{ TID_RspQryInstrument, 2, RspQryInstrumentFieldUse, "RspQryInstrument", "��Լ��ѯӦ��" }
		,
	{ TID_ReqQryUser, 1, ReqQryUserFieldUse, "ReqQryUser", "�û���ѯ����" }
		,
	{ TID_RspQryUser, 2, RspQryUserFieldUse, "RspQryUser", "�û���ѯӦ��" }
		,
	{ TID_ReqQryExchange, 1, ReqQryExchangeFieldUse, "ReqQryExchange", "��������ѯ����" }
		,
	{ TID_RspQryExchange, 2, RspQryExchangeFieldUse, "RspQryExchange", "��������ѯӦ��" }
		,
	{ TID_ReqQryUserInvestor, 1, ReqQryUserInvestorFieldUse, "ReqQryUserInvestor", "����Ͷ�����˻���ѯ����" }
		,
	{ TID_RspQryUserInvestor, 2, RspQryUserInvestorFieldUse, "RspQryUserInvestor", "����Ͷ�����˻���ѯӦ��" }
		,
	{ TID_ReqQryInvestorPosition, 1, ReqQryInvestorPositionFieldUse, "ReqQryInvestorPosition", "Ͷ���ֲֲ߳�ѯ����" }
		,
	{ TID_RspQryInvestorPosition, 2, RspQryInvestorPositionFieldUse, "RspQryInvestorPosition", "Ͷ���ֲֲ߳�ѯӦ��" }
		,
	{ TID_ReqQryMarketData, 1, ReqQryMarketDataFieldUse, "ReqQryMarketData", "��ͨ�����ѯ����" }
		,
	{ TID_RspQryMarketData, 2, RspQryMarketDataFieldUse, "RspQryMarketData", "��ͨ�����ѯӦ��" }
		,
	{ TID_ReqQryInvestorFee, 1, ReqQryInvestorFeeFieldUse, "ReqQryInvestorFee", "Ͷ�����������ʲ�ѯ����" }
		,
	{ TID_RspQryInvestorFee, 2, RspQryInvestorFeeFieldUse, "RspQryInvestorFee", "Ͷ�����������ʲ�ѯӦ��" }
		,
	{ TID_ReqQryInvestorMargin, 1, ReqQryInvestorMarginFieldUse, "ReqQryInvestorMargin", "Ͷ���߱�֤���ʲ�ѯ����" }
		,
	{ TID_RspQryInvestorMargin, 2, RspQryInvestorMarginFieldUse, "RspQryInvestorMargin", "Ͷ���߱�֤���ʲ�ѯӦ��" }
		,
	{ TID_ReqQryDepthMarketData, 1, ReqQryDepthMarketDataFieldUse, "ReqQryDepthMarketData", "�����ѯ����" }
		,
	{ TID_RspQryDepthMarketData, 2, RspQryDepthMarketDataFieldUse, "RspQryDepthMarketData", "�����ѯӦ��" }
		,
	{ TID_ReqQrySGEDeferRate, 1, ReqQrySGEDeferRateFieldUse, "ReqQrySGEDeferRate", "�������ӷ��ʲ�ѯ����" }
		,
	{ TID_RspQrySGEDeferRate, 2, RspQrySGEDeferRateFieldUse, "RspQrySGEDeferRate", "�������ӷ��ʲ�ѯӦ��" }
		,
	{ TID_ReqQryInvestorPositionDetail, 1, ReqQryInvestorPositionDetailFieldUse, "ReqQryInvestorPositionDetail", "�ֲ���ϸ��ѯ����" }
		,
	{ TID_RspQryInvestorPositionDetail, 1, RspQryInvestorPositionDetailFieldUse, "RspQryInvestorPositionDetail", "�ֲ���ϸ��ѯӦ��" }
		,
	{ TID_ExInvestorPositionDetail, 1, ExInvestorPositionDetailFieldUse, "ExInvestorPositionDetail", "�ֲ���ϸ��" }
		,
	{ TID_ReqQryInvestorOptionFee, 1, ReqQryInvestorOptionFeeFieldUse, "ReqQryInvestorOptionFee", "Ͷ������Ȩ�������ʲ�ѯ����" }
		,
	{ TID_RspQryInvestorOptionFee, 2, RspQryInvestorOptionFeeFieldUse, "RspQryInvestorOptionFee", "Ͷ������Ȩ�������ʲ�ѯӦ��" }
		,
	{ TID_DataSyncStart, 1, DataSyncStartFieldUse, "DataSyncStart", "����ͬ����ʼ" }
		,
	{ TID_DataSyncEnd, 1, DataSyncEndFieldUse, "DataSyncEnd", "����ͬ������" }
		,
	{ TID_InitExchange, 1, InitExchangeFieldUse, "InitExchange", "������" }
		,
	{ TID_InitSeat, 1, InitSeatFieldUse, "InitSeat", "ϯλ" }
		,
	{ TID_InitUser, 1, InitUserFieldUse, "InitUser", "�û�" }
		,
	{ TID_InitInvestor, 1, InitInvestorFieldUse, "InitInvestor", "Ͷ����" }
		,
	{ TID_InitClientTradingID, 1, InitClientTradingIDFieldUse, "InitClientTradingID", "���ױ���" }
		,
	{ TID_InitUserInvestor, 1, InitUserInvestorFieldUse, "InitUserInvestor", "�û�Ͷ���߹�ϵ" }
		,
	{ TID_InitUserTradingRight, 1, InitUserTradingRightFieldUse, "InitUserTradingRight", "�û�����Ȩ��" }
		,
	{ TID_InitInvestorAccount, 1, InitInvestorAccountFieldUse, "InitInvestorAccount", "Ͷ�����ʽ��˻�" }
		,
	{ TID_InitInstrument, 1, InitInstrumentFieldUse, "InitInstrument", "��Լ" }
		,
	{ TID_InitInvestorMargin, 1, InitInvestorMarginFieldUse, "InitInvestorMargin", "Ͷ���߱�֤����" }
		,
	{ TID_InitInvestorFee, 1, InitInvestorFeeFieldUse, "InitInvestorFee", "Ͷ����������" }
		,
	{ TID_InitInvestorPosition, 1, InitInvestorPositionFieldUse, "InitInvestorPosition", "Ͷ���ֲ߳�" }
		,
	{ TID_DbInvestorAccountDeposit, 1, DbInvestorAccountDepositFieldUse, "DbInvestorAccountDeposit", "�ͻ��ʽ��ʻ������" }
		,
	{ TID_DbInsUser, 1, DbInsUserFieldUse, "DbInsUser", "���ӽ����û�" }
		,
	{ TID_DbUpdUser, 1, DbUpdUserFieldUse, "DbUpdUser", "�޸Ľ����û�" }
		,
	{ TID_InitSystemStatus, 1, InitSystemStatusFieldUse, "InitSystemStatus", "ϵͳ״̬" }
		,
	{ TID_InitInstrumentGroup, 1, InitInstrumentGroupFieldUse, "InitInstrumentGroup", "��Լ�ͺ�Լ���ϵ" }
		,
	{ TID_InitClientMarginCombType, 1, InitClientMarginCombTypeFieldUse, "InitClientMarginCombType", "���ױ�����ϱ�֤������" }
		,
	{ TID_InitSGEDeferRate, 1, InitSGEDeferRateFieldUse, "InitSGEDeferRate", "�������ӷ�����Ϣ��" }
		,
	{ TID_DbClientTradingID, 1, DbClientTradingIDFieldUse, "DbClientTradingID", "�ͻ��ʽ��ʻ������" }
		,
	{ TID_InitCmbInstrumentDetail, 1, InitCmbInstrumentDetailFieldUse, "InitCmbInstrumentDetail", "��Ϻ�Լ��ϸӦ��" }
		,
	{ TID_InitInvestorTradingRight, 1, InitInvestorTradingRightFieldUse, "InitInvestorTradingRight", "Ͷ���߽���Ȩ��" }
		,
	{ TID_DbUpdInvestorTradingRight, 1, DbUpdInvestorTradingRightFieldUse, "DbUpdInvestorTradingRight", "�޸�Ͷ����Ȩ��" }
		,
	{ TID_DbInsInvestorTradingRight, 1, DbInsInvestorTradingRightFieldUse, "DbInsInvestorTradingRight", "����Ͷ����Ȩ��" }
		,
	{ TID_DbDelInvestorTradingRight, 1, DbDelInvestorTradingRightFieldUse, "DbDelInvestorTradingRight", "ɾ��Ͷ����Ȩ��" }
		,
	{ TID_DbUpdUserIP, 1, DbUpdUserIPFieldUse, "DbUpdUserIP", "����ԱIP" }
		,
	{ TID_DbInsUserIP, 1, DbInsUserIPFieldUse, "DbInsUserIP", "����ԱIP" }
		,
	{ TID_DbDelUserIP, 1, DbDelUserIPFieldUse, "DbDelUserIP", "����ԱIP" }
		,
	{ TID_InitUserIP, 1, InitUserIPFieldUse, "InitUserIP", "����ԱIP" }
		,
	{ TID_InitInvestorOptionFee, 1, InitInvestorOptionFeeFieldUse, "InitInvestorOptionFee", "Ͷ������Ȩ������" }
		,
	{ TID_InitSystemInfo, 1, InitSystemInfoFieldUse, "InitSystemInfo", "QDPϵͳ��Ϣ��" }
		,
	{ TID_NtfTimeSync, 1, NtfTimeSyncFieldUse, "NtfTimeSync", "ʱ��ͬ��" }
		,
	{ TID_NtfCommPhaseChange, 1, NtfCommPhaseChangeFieldUse, "NtfCommPhaseChange", "ͨѶ�׶��л�֪ͨ" }
		,
	{ TID_NtfOrder, 1, NtfOrderFieldUse, "NtfOrder", "����֪ͨ" }
		,
	{ TID_NtfTrade, 1, NtfTradeFieldUse, "NtfTrade", "�ɽ�֪ͨ" }
		,
	{ TID_NtfInstrumentStatusUpdate, 1, NtfInstrumentStatusUpdateFieldUse, "NtfInstrumentStatusUpdate", "��Լ����״̬�ı�֪ͨ" }
		,
	{ TID_NtfDelUserSession, 1, NtfDelUserSessionFieldUse, "NtfDelUserSession", "�Ựɾ��֪ͨ" }
		,
	{ TID_NtfMarketData, 1, NtfMarketDataFieldUse, "NtfMarketData", "��ͨ����֪ͨ" }
		,
	{ TID_NtfLifeCycle, 1, NtfLifeCycleFieldUse, "NtfLifeCycle", "֪ͨ�������ں�" }
		,
	{ TID_NtfErrorOrderInsert, 2, NtfErrorOrderInsertFieldUse, "NtfErrorOrderInsert", "����¼�����֪ͨ" }
		,
	{ TID_NtfErrorOrderAction, 2, NtfErrorOrderActionFieldUse, "NtfErrorOrderAction", "������������֪ͨ" }
		,
	{ TID_NtfMemtableChange, 1, NtfMemtableChangeFieldUse, "NtfMemtableChange", "�ڴ��仯֪ͨ" }
		,
	{ TID_ReqQueryExInstrument, 1, ReqQueryExInstrumentFieldUse, "ReqQueryExInstrument", "֪ͨ���̻���ѯ��Լ����" }
		,
	{ TID_RspQueryExInstrument, 2, RspQueryExInstrumentFieldUse, "RspQueryExInstrument", "���̻���ѯ��ԼӦ��" }
		,
	{ TID_RspQueryExTradingDay, 2, RspQueryExTradingDayFieldUse, "RspQueryExTradingDay", "���̻���ѯ������Ӧ��" }
		,
	{ TID_RspQueryExInvestorPosition, 2, RspQueryExInvestorPositionFieldUse, "RspQueryExInvestorPosition", "���̻���ѯ�ͻ��ֲ�Ӧ��" }
		,
	{ TID_RspQueryExMarketData, 2, RspQueryExMarketDataFieldUse, "RspQueryExMarketData", "���̻���ѯ����Ӧ��" }
		,
	{ TID_ReqRollbakPreOrder, 1, ReqRollbakPreOrderFieldUse, "ReqRollbakPreOrder", "�ⶳInnerLinkδ���뽻�׵ı���" }
		,
	{ TID_NtfInvestorAccountDeposit, 1, NtfInvestorAccountDepositFieldUse, "NtfInvestorAccountDeposit", "�����ر�֪ͨ" }
		,
	{ TID_QueryBaseFinish, 1, QueryBaseFinishFieldUse, "QueryBaseFinish", "���̻���ѯ����" }
		,
	{ TID_RspQueryExCapitalData, 2, RspQueryExCapitalDataFieldUse, "RspQueryExCapitalData", "���̻���ѯ�ʽ�Ӧ��" }
		,
	{ TID_RspQueryExCmbInstrumentDetail, 2, RspQueryExCmbInstrumentDetailFieldUse, "RspQueryExCmbInstrumentDetail", "���̻���ѯ��Ϻ�Լ��ϸӦ��" }
		,
	{ TID_NtfSGEDeferRate, 1, NtfSGEDeferRateFieldUse, "NtfSGEDeferRate", "�������ӷ���֪ͨ" }
		,
	{ TID_InterLoginInfo, 1, InterLoginInfoFieldUse, "InterLoginInfo", "�ɹ���½֪ͨ" }
		,
	{ TID_NtfMessageNotify, 1, NtfMessageNotifyFieldUse, "NtfMessageNotify", "QDP������Ϣ֪ͨ" }
		,
	{ TID_InnerLogin, 1, InnerLoginFieldUse, "InnerLogin", "�ڲ���¼����" }
		,
	{ TID_ExQryMBLMarketData, 1, ExQryMBLMarketDataFieldUse, "ExQryMBLMarketData", "�ڲ��ּ۱��ѯӦ��" }
		,
	{ TID_ReqQryMBLMarketData, 1, ReqQryMBLMarketDataFieldUse, "ReqQryMBLMarketData", "�ּ۱��ѯ����" }
		,
	{ TID_RspQryMBLMarketData, 2, RspQryMBLMarketDataFieldUse, "RspQryMBLMarketData", "�ּ۱��ѯӦ��" }
		,
	{ TID_NtfPositionProfit, 1, NtfPositionProfitFieldUse, "NtfPositionProfit", "�ڴ��仯֪ͨ" }
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
