/////////////////////////////////////////////////////////////////////////
///@system  QuantDo Trade Engine
///@company Shanghai Quantdo Network Technology Co., Ltd.
///@file ApexFtdcUserApiDataType.h
///@brief Define DataType For API
///@history 
/////////////////////////////////////////////////////////////////////////

#ifndef FTDCDATATYPE_H
#define FTDCDATATYPE_H

enum APEX_TE_RESUME_TYPE
{
	APEX_TERT_RESTART = 0,
	APEX_TERT_RESUME,
	APEX_TERT_QUICK
};

const int APEX_TSS_DIALOG = 1;		//Dialog Flow
const int APEX_TSS_PRIVATE = 2;		//Participant Private Flow
const int APEX_TSS_PUBLIC = 3;		//Public Flow
const int APEX_TSS_QUERY = 4;		//Query
const int APEX_TSS_USER = 5;		//User Private Flow
const int APEX_TSS_FORQUOTE = 6;		//Quote Flow

/////////////////////////////////////////////////////////////////////////
///TFtdcErrorIDType is a type for Error ID
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcErrorIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcPriorityType is a type for Priority
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcPriorityType;

/////////////////////////////////////////////////////////////////////////
///TFtdcSettlementIDType is a type for Settlement ID
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcSettlementIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcMonthCountType is a type for Month Count
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcMonthCountType;

/////////////////////////////////////////////////////////////////////////
///TFtdcTradingSegmentSNType is a type for Trading Segment Serial No
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcTradingSegmentSNType;

/////////////////////////////////////////////////////////////////////////
///TFtdcVolumeType is a type for Volume
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcVolumeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcTimeSortIDType is a type for Time Sort ID
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcTimeSortIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcFrontIDType is a type for Front ID
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcFrontIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcSessionIDType is a type for Session ID
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcSessionIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcSequenceNoType is a type for Sequence No
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcSequenceNoType;

/////////////////////////////////////////////////////////////////////////
///TFtdcBulletinIDType is a type for Bulletin ID
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcBulletinIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcInformationIDType is a type for Information ID
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcInformationIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcMillisecType is a type for Millisecond
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcMillisecType;

/////////////////////////////////////////////////////////////////////////
///TFtdcVolumeMultipleType is a type for Volume Multiplier
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcVolumeMultipleType;

/////////////////////////////////////////////////////////////////////////
///TFtdcImplyLevelType is a type for Implied Level
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcImplyLevelType;

/////////////////////////////////////////////////////////////////////////
///TFtdcStartPosType is a type for Start Position
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcStartPosType;

/////////////////////////////////////////////////////////////////////////
///TFtdcDataCenterIDType is a type for Data Center ID
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcDataCenterIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcAliasType is a type for Alias
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcAliasType[3];

/////////////////////////////////////////////////////////////////////////
///TFtdcOriginalTextType is a type for Original Text
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcOriginalTextType[3];

/////////////////////////////////////////////////////////////////////////
///TFtdcParticipantIDType is a type for Participant ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcParticipantIDType[11];

/////////////////////////////////////////////////////////////////////////
///TFtdcParticipantNameType is a type for Participant Name
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcParticipantNameType[51];

/////////////////////////////////////////////////////////////////////////
///TFtdcParticipantAbbrType is a type for Participant Abbriviation
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcParticipantAbbrType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcUserIDType is a type for User ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcUserIDType[16];

/////////////////////////////////////////////////////////////////////////
///TFtdcPasswordType is a type for Password
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcPasswordType[41];

/////////////////////////////////////////////////////////////////////////
///TFtdcClientIDType is a type for Client ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcClientIDType[11];

/////////////////////////////////////////////////////////////////////////
///TFtdcInstrumentIDType is a type for Instrument ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcInstrumentIDType[31];

/////////////////////////////////////////////////////////////////////////
///TFtdcProductIDType is a type for Product ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcProductIDType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcProductNameType is a type for Product Name
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcProductNameType[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcExchangeIDType is a type for Exchange ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcExchangeIDType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcDateType is a type for Date
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcDateType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcTradingDayType is a type for Trading Day
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcTradingDayType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcTimeType is a type for Time
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcTimeType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcInstrumentNameType is a type for Instrument Name
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcInstrumentNameType[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcProductGroupIDType is a type for Product Group ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcProductGroupIDType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcProductGroupNameType is a type for Product Group Name
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcProductGroupNameType[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcMarketIDType is a type for Market ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcMarketIDType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcSettlementGroupIDType is a type for Settlement Group ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcSettlementGroupIDType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcOrderSysIDType is a type for Order System ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcOrderSysIDType[13];

/////////////////////////////////////////////////////////////////////////
///TFtdcOTCOrderSysIDType is a type for OTC Order System ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcOTCOrderSysIDType[13];

/////////////////////////////////////////////////////////////////////////
///TFtdcExecOrderSysIDType is a type for Execution Order System ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcExecOrderSysIDType[13];

/////////////////////////////////////////////////////////////////////////
///TFtdcQuoteSysIDType is a type for Quote System ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcQuoteSysIDType[13];

/////////////////////////////////////////////////////////////////////////
///TFtdcTradeIDType is a type for Trade ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcTradeIDType[13];

/////////////////////////////////////////////////////////////////////////
///TFtdcOrderLocalIDType is a type for Order Local ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcOrderLocalIDType[13];

/////////////////////////////////////////////////////////////////////////
///TFtdcComeFromType is a type for Source
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcComeFromType[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcAccountIDType is a type for Account ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcAccountIDType[13];

/////////////////////////////////////////////////////////////////////////
///TFtdcNewsTypeType is a type for News Type
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcNewsTypeType[3];

/////////////////////////////////////////////////////////////////////////
///TFtdcAdvanceMonthType is a type for Advance Month
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcAdvanceMonthType[4];

/////////////////////////////////////////////////////////////////////////
///TFtdcCommodityIDType is a type for Commodity ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcCommodityIDType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcIPAddressType is a type for IP Address
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcIPAddressType[16];

/////////////////////////////////////////////////////////////////////////
///TFtdcMultiIPAddressType is a type for Multi IP Address
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcMultiIPAddressType[65];

/////////////////////////////////////////////////////////////////////////
///TFtdcProductInfoType is a type for Product Info
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcProductInfoType[41];

/////////////////////////////////////////////////////////////////////////
///TFtdcProtocolInfoType is a type for Protocol Info
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcProtocolInfoType[41];

/////////////////////////////////////////////////////////////////////////
///TFtdcBusinessUnitType is a type for Business Unit
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcBusinessUnitType[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcTradingSystemNameType is a type for Trading System Name
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcTradingSystemNameType[61];

/////////////////////////////////////////////////////////////////////////
///TFtdcTradingRoleType is a type for Trading Role
/////////////////////////////////////////////////////////////////////////
///Broker
#define APEX_FTDC_ER_Broker '1'
///proprietory
#define APEX_FTDC_ER_Host '2'
///Market Maker
#define APEX_FTDC_ER_MarketMaker '3'

typedef char TApexFtdcTradingRoleType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUserTypeType is a type for User Type
/////////////////////////////////////////////////////////////////////////
///Trader
#define APEX_FTDC_UT_Trader '1'
///Trade Manager
#define APEX_FTDC_UT_TradeManager '2'
///Market Data User
#define APEX_FTDC_UT_MDUser '3'
///Single Trader
#define APEX_FTDC_UT_SingleTrader '4'

typedef char TApexFtdcUserTypeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcProductClassType is a type for Product Class
/////////////////////////////////////////////////////////////////////////
///Futures
#define APEX_FTDC_PC_Futures '1'
///Options
#define APEX_FTDC_PC_Options '2'
///Compound
#define APEX_FTDC_PC_Combination '3'
///Spot
#define APEX_FTDC_PC_Spot '4'
///Exchange of Future for Physical
#define APEX_FTDC_PC_EFP '5'

typedef char TApexFtdcProductClassType;

/////////////////////////////////////////////////////////////////////////
///TFtdcOptionsTypeType is a type for OptionsType
/////////////////////////////////////////////////////////////////////////
///Not an Option Type
#define APEX_FTDC_OT_NotOptions '0'
///Call Options
#define APEX_FTDC_OT_CallOptions '1'
///Put Options
#define APEX_FTDC_OT_PutOptions '2'

typedef char TApexFtdcOptionsTypeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcInstrumentStatusType is a type for Instrument Status
/////////////////////////////////////////////////////////////////////////
///Before Trading
#define APEX_FTDC_IS_BeforeTrading '0'
///No Trading
#define APEX_FTDC_IS_NoTrading '1'
///Continous Trading
#define APEX_FTDC_IS_Continous '2'
///Auction Ordering
#define APEX_FTDC_IS_AuctionOrdering '3'
///Auction Balancing
#define APEX_FTDC_IS_AuctionBalance '4'
///Auction Matching
#define APEX_FTDC_IS_AuctionMatch '5'
///Closed
#define APEX_FTDC_IS_Closed '6'

typedef char TApexFtdcInstrumentStatusType;

/////////////////////////////////////////////////////////////////////////
///TFtdcDirectionType is a type for Trading Direction
/////////////////////////////////////////////////////////////////////////
///Buy
#define APEX_FTDC_D_Buy '0'
///Sell
#define APEX_FTDC_D_Sell '1'

typedef char TApexFtdcDirectionType;

/////////////////////////////////////////////////////////////////////////
///TFtdcPositionTypeType is a type for Position Type
/////////////////////////////////////////////////////////////////////////
///Net
#define APEX_FTDC_PT_Net '1'
///Gross
#define APEX_FTDC_PT_Gross '2'

typedef char TApexFtdcPositionTypeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcPosiDirectionType is a type for Position Direction
/////////////////////////////////////////////////////////////////////////
///Net
#define APEX_FTDC_PD_Net '1'
///Long
#define APEX_FTDC_PD_Long '2'
///Short
#define APEX_FTDC_PD_Short '3'

typedef char TApexFtdcPosiDirectionType;

/////////////////////////////////////////////////////////////////////////
///TFtdcExchangeDataSyncStatusType is a type for Exchange Data Sync Status
/////////////////////////////////////////////////////////////////////////
///Asynchronous
#define APEX_FTDC_EDS_Asynchronous '1'
///Synchronizing
#define APEX_FTDC_EDS_Synchronizing '2'
///Synchronized
#define APEX_FTDC_EDS_Synchronized '3'

typedef char TApexFtdcExchangeDataSyncStatusType;

/////////////////////////////////////////////////////////////////////////
///TFtdcSGDataSyncStatusType is a type for Settlement Group Data Sync Status
/////////////////////////////////////////////////////////////////////////
///Asynchronous
#define APEX_FTDC_SGDS_Asynchronous '1'
///Synchronizing
#define APEX_FTDC_SGDS_Synchronizing '2'
///Synchronized
#define APEX_FTDC_SGDS_Synchronized '3'

typedef char TApexFtdcSGDataSyncStatusType;

/////////////////////////////////////////////////////////////////////////
///TFtdcHedgeFlagType is a type for Hedge Flag
/////////////////////////////////////////////////////////////////////////
///Speculation
#define APEX_FTDC_HF_Speculation '1'
///Arbitrage
#define APEX_FTDC_HF_Arbitrage '2'
///Hedge
#define APEX_FTDC_HF_Hedge '3'
///Market Maker
#define APEX_FTDC_HF_MarketMaker '4'

typedef char TApexFtdcHedgeFlagType;

/////////////////////////////////////////////////////////////////////////
///TFtdcClientTypeType is a type for Client Type
/////////////////////////////////////////////////////////////////////////
///Person
#define APEX_FTDC_CT_Person '0'
///Company
#define APEX_FTDC_CT_Company '1'
///Fund
#define APEX_FTDC_CT_Fund '2'

typedef char TApexFtdcClientTypeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcInstStatusEnterReasonType is a type for Instrument Status Entering Reason
/////////////////////////////////////////////////////////////////////////
///Automatic
#define APEX_FTDC_IER_Automatic '1'
///Manual
#define APEX_FTDC_IER_Manual '2'
///Fuse
#define APEX_FTDC_IER_Fuse '3'
///Manual Fuse
#define APEX_FTDC_IER_FuseManual '4'

typedef char TApexFtdcInstStatusEnterReasonType;

/////////////////////////////////////////////////////////////////////////
///TFtdcOrderPriceTypeType is a type for Order Price Type
/////////////////////////////////////////////////////////////////////////
///Any Price
#define APEX_FTDC_OPT_AnyPrice '1'
///Limit Price
#define APEX_FTDC_OPT_LimitPrice '2'
///Best Price
#define APEX_FTDC_OPT_BestPrice '3'
///Five Level Price
#define APEX_FTDC_OPT_FiveLevelPrice '4'

typedef char TApexFtdcOrderPriceTypeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcOffsetFlagType is a type for Offset Flag
/////////////////////////////////////////////////////////////////////////
///Open
#define APEX_FTDC_OF_Open '0'
///Close
#define APEX_FTDC_OF_Close '1'
///Force Close
#define APEX_FTDC_OF_ForceClose '2'
///Close Today
#define APEX_FTDC_OF_CloseToday '3'
///Close Yesterday
#define APEX_FTDC_OF_CloseYesterday '4'

typedef char TApexFtdcOffsetFlagType;

/////////////////////////////////////////////////////////////////////////
///TFtdcForceCloseReasonType is a type for Force Close Reason
/////////////////////////////////////////////////////////////////////////
///Not Force Close
#define APEX_FTDC_FCC_NotForceClose '0'
///Lack of Deposit
#define APEX_FTDC_FCC_LackDeposit '1'
///Client Over Position Limit
#define APEX_FTDC_FCC_ClientOverPositionLimit '2'
///Member Over Position Limit
#define APEX_FTDC_FCC_MemberOverPositionLimit '3'
///Position Not Multiple of Min Unit
#define APEX_FTDC_FCC_NotMultiple '4'
///Violation
#define APEX_FTDC_FCC_Violation '5'
///Other
#define APEX_FTDC_FCC_Other '6'
///Personal holder approaching Delivery
#define APEX_FTDC_FCC_PersonDeliv '7'

typedef char TApexFtdcForceCloseReasonType;

/////////////////////////////////////////////////////////////////////////
///TFtdcOrderStatusType is a type for Order Status
/////////////////////////////////////////////////////////////////////////
///All Traded
#define APEX_FTDC_OST_AllTraded '0'
///Partially Traded Queueing
#define APEX_FTDC_OST_PartTradedQueueing '1'
///Partially Traded Not Queueing
#define APEX_FTDC_OST_PartTradedNotQueueing '2'
///No Trade Queueing
#define APEX_FTDC_OST_NoTradeQueueing '3'
///No Trade Not Queueing
#define APEX_FTDC_OST_NoTradeNotQueueing '4'
///Canceled
#define APEX_FTDC_OST_Canceled '5'

typedef char TApexFtdcOrderStatusType;

/////////////////////////////////////////////////////////////////////////
///TFtdcOrderTypeType is a type for Order Type
/////////////////////////////////////////////////////////////////////////
///Normal
#define APEX_FTDC_ORDT_Normal '0'
///Derived From Quote
#define APEX_FTDC_ORDT_DeriveFromQuote '1'
///Derived From Combination
#define APEX_FTDC_ORDT_DeriveFromCombination '2'

typedef char TApexFtdcOrderTypeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcOTCOrderStatusType is a type for OTC Order Status
/////////////////////////////////////////////////////////////////////////
///Inputed
#define APEX_FTDC_OOS_Inputed '0'
///Confirmed
#define APEX_FTDC_OOS_Confirmed '1'
///Canceled
#define APEX_FTDC_OOS_Canceled '2'
///Refused
#define APEX_FTDC_OOS_Refused '3'

typedef char TApexFtdcOTCOrderStatusType;

/////////////////////////////////////////////////////////////////////////
///TFtdcTimeConditionType is a type for Time Condition
/////////////////////////////////////////////////////////////////////////
///Immediately Or Cancel
#define APEX_FTDC_TC_IOC '1'
///Good For Segment
#define APEX_FTDC_TC_GFS '2'
///Good For Day
#define APEX_FTDC_TC_GFD '3'
///Good Till Date
#define APEX_FTDC_TC_GTD '4'
///Good Till Cancel
#define APEX_FTDC_TC_GTC '5'
///Good For Auction
#define APEX_FTDC_TC_GFA '6'

typedef char TApexFtdcTimeConditionType;

/////////////////////////////////////////////////////////////////////////
///TFtdcVolumeConditionType is a type for Volume Condition
/////////////////////////////////////////////////////////////////////////
///Any Volumn
#define APEX_FTDC_VC_AV '1'
///Minimum Volumn
#define APEX_FTDC_VC_MV '2'
///All Volumn
#define APEX_FTDC_VC_CV '3'

typedef char TApexFtdcVolumeConditionType;

/////////////////////////////////////////////////////////////////////////
///TFtdcContingentConditionType is a type for Contingent Condition
/////////////////////////////////////////////////////////////////////////
///Immediately
#define APEX_FTDC_CC_Immediately '1'
///Touch
#define APEX_FTDC_CC_Touch '2'

typedef char TApexFtdcContingentConditionType;

/////////////////////////////////////////////////////////////////////////
///TFtdcActionFlagType is a type for Action Flag
/////////////////////////////////////////////////////////////////////////
///Delete
#define APEX_FTDC_AF_Delete '0'
///Suspend
#define APEX_FTDC_AF_Suspend '1'
///Active
#define APEX_FTDC_AF_Active '2'
///Modify
#define APEX_FTDC_AF_Modify '3'

typedef char TApexFtdcActionFlagType;

/////////////////////////////////////////////////////////////////////////
///TFtdcOrderSourceType is a type for Order Source
/////////////////////////////////////////////////////////////////////////
///Participant
#define APEX_FTDC_OSRC_Participant '0'
///Administrator
#define APEX_FTDC_OSRC_Administrator '1'

typedef char TApexFtdcOrderSourceType;

/////////////////////////////////////////////////////////////////////////
///TFtdcTradeTypeType is a type for Trade Type
/////////////////////////////////////////////////////////////////////////
///Common
#define APEX_FTDC_TRDT_Common '0'
///Options Execution
#define APEX_FTDC_TRDT_OptionsExecution '1'
///OTC Trade
#define APEX_FTDC_TRDT_OTC '2'
///EFP Derived Trade
#define APEX_FTDC_TRDT_EFPDerived '3'
///Combination Derived Trade
#define APEX_FTDC_TRDT_CombinationDerived '4'

typedef char TApexFtdcTradeTypeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcPriceSourceType is a type for Price Source
/////////////////////////////////////////////////////////////////////////
///Last Price
#define APEX_FTDC_PSRC_LastPrice '0'
///Buy
#define APEX_FTDC_PSRC_Buy '1'
///Sell
#define APEX_FTDC_PSRC_Sell '2'

typedef char TApexFtdcPriceSourceType;

/////////////////////////////////////////////////////////////////////////
///TFtdcAccountStatusType is a type for Account Status
/////////////////////////////////////////////////////////////////////////
///Enable
#define APEX_FTDC_ACCS_Enable '0'
///Disable
#define APEX_FTDC_ACCS_Disable '1'

typedef char TApexFtdcAccountStatusType;

/////////////////////////////////////////////////////////////////////////
///TFtdcMemberTypeType is a type for Member Type
/////////////////////////////////////////////////////////////////////////
///Trading
#define APEX_FTDC_MT_Trading '0'
///Settlement
#define APEX_FTDC_MT_Settlement '1'
///Compositive
#define APEX_FTDC_MT_Compositive '2'

typedef char TApexFtdcMemberTypeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcExecResultType is a type for Execution Result
/////////////////////////////////////////////////////////////////////////
///Not Executed
#define APEX_FTDC_OER_NoExec 'n'
///Canceled
#define APEX_FTDC_OER_Canceled 'c'
///OK
#define APEX_FTDC_OER_OK '0'
///No Position
#define APEX_FTDC_OER_NoPosition '1'
///No Deposit
#define APEX_FTDC_OER_NoDeposit '2'
///No Participant
#define APEX_FTDC_OER_NoParticipant '3'
///No Client
#define APEX_FTDC_OER_NoClient '4'
///No Instrument
#define APEX_FTDC_OER_NoInstrument '6'
///No Right
#define APEX_FTDC_OER_NoRight '7'
///Invalid Volume
#define APEX_FTDC_OER_InvalidVolume '8'
///No Enough History Trade
#define APEX_FTDC_OER_NoEnoughHistoryTrade '9'

typedef char TApexFtdcExecResultType;

/////////////////////////////////////////////////////////////////////////
///TFtdcYearType is a type for Year
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcYearType;

/////////////////////////////////////////////////////////////////////////
///TFtdcMonthType is a type for Month
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcMonthType;

/////////////////////////////////////////////////////////////////////////
///TFtdcLegMultipleType is a type for Leg Multiplier
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcLegMultipleType;

/////////////////////////////////////////////////////////////////////////
///TFtdcLegIDType is a type for Leg ID
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcLegIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcBoolType is a type for Bool
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcBoolType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUserActiveType is a type for User Active
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcUserActiveType;

/////////////////////////////////////////////////////////////////////////
///TFtdcPriceType is a type for Price
/////////////////////////////////////////////////////////////////////////
typedef double TApexFtdcPriceType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUnderlyingMultipleType is a type for Underlying Multiplier
/////////////////////////////////////////////////////////////////////////
typedef double TApexFtdcUnderlyingMultipleType;

/////////////////////////////////////////////////////////////////////////
///TFtdcCombOffsetFlagType is a type for Combination Offset Flag
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcCombOffsetFlagType[5];

/////////////////////////////////////////////////////////////////////////
///TFtdcCombHedgeFlagType is a type for Combination Hedge Flag
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcCombHedgeFlagType[5];

/////////////////////////////////////////////////////////////////////////
///TFtdcRatioType is a type for Ratio
/////////////////////////////////////////////////////////////////////////
typedef double TApexFtdcRatioType;

/////////////////////////////////////////////////////////////////////////
///TFtdcMoneyType is a type for Money
/////////////////////////////////////////////////////////////////////////
typedef double TApexFtdcMoneyType;

/////////////////////////////////////////////////////////////////////////
///TFtdcLargeVolumeType is a type for Large Volume
/////////////////////////////////////////////////////////////////////////
typedef double TApexFtdcLargeVolumeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcNewsUrgencyType is a type for News Urgency
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcNewsUrgencyType;

/////////////////////////////////////////////////////////////////////////
///TFtdcSequenceSeriesType is a type for Sequence Series
/////////////////////////////////////////////////////////////////////////
typedef short TApexFtdcSequenceSeriesType;

/////////////////////////////////////////////////////////////////////////
///TFtdcCommPhaseNoType is a type for Communication Phase No
/////////////////////////////////////////////////////////////////////////
typedef short TApexFtdcCommPhaseNoType;

/////////////////////////////////////////////////////////////////////////
///TFtdcContentLengthType is a type for Content Length
/////////////////////////////////////////////////////////////////////////
typedef int TApexFtdcContentLengthType;

/////////////////////////////////////////////////////////////////////////
///TFtdcErrorMsgType is a type for Error Msg
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcErrorMsgType[81];

/////////////////////////////////////////////////////////////////////////
///TFtdcAbstractType is a type for Abstract
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcAbstractType[81];

/////////////////////////////////////////////////////////////////////////
///TFtdcContentType is a type for Content
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcContentType[501];

/////////////////////////////////////////////////////////////////////////
///TFtdcURLLinkType is a type for URL Link
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcURLLinkType[201];

/////////////////////////////////////////////////////////////////////////
///TFtdcIdentifiedCardNoType is a type for Identified Card No
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcIdentifiedCardNoType[51];

/////////////////////////////////////////////////////////////////////////
///TFtdcIdentifiedCardNoV1Type is a type for Original IdentifiedCard No (V1)
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcIdentifiedCardNoV1Type[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcPartyNameType is a type for Counter Party Name
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcPartyNameType[81];

/////////////////////////////////////////////////////////////////////////
///TFtdcIdCardTypeType is a type for ID Card Type
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcIdCardTypeType[16];

/////////////////////////////////////////////////////////////////////////
///TFtdcTableNameType is a type for Table Name
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcTableNameType[33];

/////////////////////////////////////////////////////////////////////////
///TFtdcAdminOrderCommandFlagType is a type for Admin Order Command Flag
/////////////////////////////////////////////////////////////////////////
///Invalid Position Force Close
#define APEX_FTDC_AOC_InvalidPositionForceClose '1'
///Initializing Participant Credit Limit
#define APEX_FTDC_AOC_InitCreditLimit '2'
///Alter Participant Credit Limit
#define APEX_FTDC_AOC_AlterCreditLimit '3'
///Cancel Participant Credit Limit
#define APEX_FTDC_AOC_CancelCreditLimit '4'

typedef char TApexFtdcAdminOrderCommandFlagType;

/////////////////////////////////////////////////////////////////////////
///TFtdcCurrencyIDType is a type for Currency ID
/////////////////////////////////////////////////////////////////////////
typedef char TApexFtdcCurrencyIDType[4];

#endif
