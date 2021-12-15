/////////////////////////////////////////////////////////////////////////
///@system  QuantDo Trade Engine
///@company Shanghai Quantdo Network Technology Co., Ltd.
///@file ApexFtdcUserApiStruct.h
///@brief Define DataType For API
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(Apex_FTDCSTRUCT_H)
#define Apex_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ApexFtdcUserApiDataType.h"

///Dissemination
struct CApexFtdcDisseminationField
{
	///Sequence Series
	TApexFtdcSequenceSeriesType	SequenceSeries;
	///Sequence Number
	TApexFtdcSequenceNoType	SequenceNo;
};

///Response Info
struct CApexFtdcRspInfoField
{
	///Error ID
	TApexFtdcErrorIDType	ErrorID;
	///Error Msg
	TApexFtdcErrorMsgType	ErrorMsg;
};

///Communication Phase
struct CApexFtdcCommPhaseField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Communication Phase No
	TApexFtdcCommPhaseNoType	CommPhaseNo;
};

///Exchange Trading Day
struct CApexFtdcExchangeTradingDayField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Exchange ID
	TApexFtdcExchangeIDType	ExchangeID;
};

///Settlement Session
struct CApexFtdcSettlementSessionField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
};

///Current Time
struct CApexFtdcCurrentTimeField
{
	///Current Date
	TApexFtdcDateType	CurrDate;
	///Current Time
	TApexFtdcTimeType	CurrTime;
	///Current milli second
	TApexFtdcMillisecType	CurrMillisec;
};

///User Login Request
struct CApexFtdcReqUserLoginField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Password
	TApexFtdcPasswordType	Password;
	///User Product Info
	TApexFtdcProductInfoType	UserProductInfo;
	///API Product Info
	TApexFtdcProductInfoType	InterfaceProductInfo;
	///Protocol Info
	TApexFtdcProtocolInfoType	ProtocolInfo;
	///Data Center ID
	TApexFtdcDataCenterIDType	DataCenterID;
};

///User Login Response
struct CApexFtdcRspUserLoginField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Login Time
	TApexFtdcTimeType	LoginTime;
	///Max Order Local ID
	TApexFtdcOrderLocalIDType	MaxOrderLocalID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Trading System Name
	TApexFtdcTradingSystemNameType	TradingSystemName;
	///Data Center ID
	TApexFtdcDataCenterIDType	DataCenterID;
	///Private Flow Size
	TApexFtdcSequenceNoType	PrivateFlowSize;
	///User Flow Size
	TApexFtdcSequenceNoType	UserFlowSize;
};

///User Logout Request
struct CApexFtdcReqUserLogoutField
{
	///User ID
	TApexFtdcUserIDType	UserID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
};

///User Logout Response
struct CApexFtdcRspUserLogoutField
{
	///User ID
	TApexFtdcUserIDType	UserID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
};

///Order Input
struct CApexFtdcInputOrderField
{
	///Order System ID
	TApexFtdcOrderSysIDType	OrderSysID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Order Price Type
	TApexFtdcOrderPriceTypeType	OrderPriceType;
	///Direction
	TApexFtdcDirectionType	Direction;
	///Combintation Offset Flag
	TApexFtdcCombOffsetFlagType	CombOffsetFlag;
	///Combintation Hedge Flag
	TApexFtdcCombHedgeFlagType	CombHedgeFlag;
	///Limit Price
	TApexFtdcPriceType	LimitPrice;
	///Volume Total Original
	TApexFtdcVolumeType	VolumeTotalOriginal;
	///Time Condition
	TApexFtdcTimeConditionType	TimeCondition;
	///GTD Date
	TApexFtdcDateType	GTDDate;
	///Volume Condition
	TApexFtdcVolumeConditionType	VolumeCondition;
	///Min Volume
	TApexFtdcVolumeType	MinVolume;
	///Contingent Condition
	TApexFtdcContingentConditionType	ContingentCondition;
	///Stop Price
	TApexFtdcPriceType	StopPrice;
	///Force Close Reason
	TApexFtdcForceCloseReasonType	ForceCloseReason;
	///Local Order ID
	TApexFtdcOrderLocalIDType	OrderLocalID;
	///A flag indicating Is Auto Suspend
	TApexFtdcBoolType	IsAutoSuspend;
	///Business Unit
	TApexFtdcBusinessUnitType	BusinessUnit;
};

///Order Action
struct CApexFtdcOrderActionField
{
	///Order Sys ID
	TApexFtdcOrderSysIDType	OrderSysID;
	///Local Order ID
	TApexFtdcOrderLocalIDType	OrderLocalID;
	///Action Flag
	TApexFtdcActionFlagType	ActionFlag;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Limit Price
	TApexFtdcPriceType	LimitPrice;
	///Volume Change
	TApexFtdcVolumeType	VolumeChange;
	///Action Local ID
	TApexFtdcOrderLocalIDType	ActionLocalID;
	///Business Unit
	TApexFtdcBusinessUnitType	BusinessUnit;
};

///OTC Order
struct CApexFtdcOTCOrderField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///OTC Order System ID
	TApexFtdcOTCOrderSysIDType	OTCOrderSysID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Direction
	TApexFtdcDirectionType	Direction;
	///Offset Flag
	TApexFtdcOffsetFlagType	OffsetFlag;
	///Hedge Flag
	TApexFtdcHedgeFlagType	HedgeFlag;
	///Price
	TApexFtdcPriceType	Price;
	///Volume
	TApexFtdcVolumeType	Volume;
	///Other Participant ID
	TApexFtdcParticipantIDType	OtherParticipantID;
	///Other Client ID
	TApexFtdcClientIDType	OtherClientID;
	///Other User ID
	TApexFtdcUserIDType	OtherUserID;
	///Other Offset Flag
	TApexFtdcOffsetFlagType	OtherOffsetFlag;
	///Other Hedge Flag
	TApexFtdcHedgeFlagType	OtherHedgeFlag;
	///Local OTC Order ID
	TApexFtdcOrderLocalIDType	OTCOrderLocalID;
	///OTC Order Status
	TApexFtdcOTCOrderStatusType	OTCOrderStatus;
	///Insert Time
	TApexFtdcTimeType	InsertTime;
	///Cancel Time
	TApexFtdcTimeType	CancelTime;
	///Clearing Participant ID
	TApexFtdcParticipantIDType	ClearingPartID;
	///Other Clearing Participant ID
	TApexFtdcParticipantIDType	OtherClearingPartID;
	///Calendar Date
	TApexFtdcDateType	CalendarDate;
};

///Quote Input
struct CApexFtdcInputQuoteField
{
	///Quote System ID
	TApexFtdcQuoteSysIDType	QuoteSysID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Bid Volume
	TApexFtdcVolumeType	BidVolume;
	///Ask Volume
	TApexFtdcVolumeType	AskVolume;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///QuoteLocal ID
	TApexFtdcOrderLocalIDType	QuoteLocalID;
	///Business Unit
	TApexFtdcBusinessUnitType	BusinessUnit;
	///Bid Combination Offset Flag
	TApexFtdcCombOffsetFlagType	BidCombOffsetFlag;
	///Bid Combination Hedge Flag
	TApexFtdcCombHedgeFlagType	BidCombHedgeFlag;
	///Bid Price
	TApexFtdcPriceType	BidPrice;
	///Ask Combination Offset Flag
	TApexFtdcCombOffsetFlagType	AskCombOffsetFlag;
	///Ask Combination Hedge Flag
	TApexFtdcCombHedgeFlagType	AskCombHedgeFlag;
	///Ask Price
	TApexFtdcPriceType	AskPrice;
};

///Quote Action
struct CApexFtdcQuoteActionField
{
	///Quote System ID
	TApexFtdcQuoteSysIDType	QuoteSysID;
	///Local Quote ID
	TApexFtdcOrderLocalIDType	QuoteLocalID;
	///Action Flag
	TApexFtdcActionFlagType	ActionFlag;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Local Action  ID
	TApexFtdcOrderLocalIDType	ActionLocalID;
	///Business Unit
	TApexFtdcBusinessUnitType	BusinessUnit;
};

///Execution Order Input
struct CApexFtdcInputExecOrderField
{
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Execution Order Local ID
	TApexFtdcOrderLocalIDType	ExecOrderLocalID;
	///Volume
	TApexFtdcVolumeType	Volume;
	///Business Unit
	TApexFtdcBusinessUnitType	BusinessUnit;
};

///Execution Order Action
struct CApexFtdcExecOrderActionField
{
	///Execution Order System ID
	TApexFtdcExecOrderSysIDType	ExecOrderSysID;
	///Local Execution Order ID
	TApexFtdcOrderLocalIDType	ExecOrderLocalID;
	///Action Flag
	TApexFtdcActionFlagType	ActionFlag;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Local Action  ID
	TApexFtdcOrderLocalIDType	ActionLocalID;
	///Business Unit
	TApexFtdcBusinessUnitType	BusinessUnit;
};

///User Logout
struct CApexFtdcUserLogoutField
{
	///User ID
	TApexFtdcUserIDType	UserID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
};

///User Password Update
struct CApexFtdcUserPasswordUpdateField
{
	///User ID
	TApexFtdcUserIDType	UserID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Old Password
	TApexFtdcPasswordType	OldPassword;
	///New Password
	TApexFtdcPasswordType	NewPassword;
};

///Combined Order Input
struct CApexFtdcInputCombOrderField
{
	///Combination Order System ID
	TApexFtdcOrderSysIDType	CombOrderSysID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Limit Price
	TApexFtdcPriceType	LimitPrice;
	///Volume Total Original
	TApexFtdcVolumeType	VolumeTotalOriginal;
	///Local Combination Order ID
	TApexFtdcOrderLocalIDType	CombOrderLocalID;
	///Business Unit
	TApexFtdcBusinessUnitType	BusinessUnit;
	///Instrument ID 1
	TApexFtdcInstrumentIDType	InstrumentID1;
	///Direction 1
	TApexFtdcDirectionType	Direction1;
	///Leg Multiple 1
	TApexFtdcLegMultipleType	LegMultiple1;
	///Offset Flag 1
	TApexFtdcOffsetFlagType	OffsetFlag1;
	///Hedge Flag 1
	TApexFtdcHedgeFlagType	HedgeFlag1;
	///Instrument ID 2
	TApexFtdcInstrumentIDType	InstrumentID2;
	///Direction 2
	TApexFtdcDirectionType	Direction2;
	///Leg Multiple 2
	TApexFtdcLegMultipleType	LegMultiple2;
	///Offset Flag 2
	TApexFtdcOffsetFlagType	OffsetFlag2;
	///Hedge Flag 2
	TApexFtdcHedgeFlagType	HedgeFlag2;
	///Instrument ID 3
	TApexFtdcInstrumentIDType	InstrumentID3;
	///Direction 3
	TApexFtdcDirectionType	Direction3;
	///Leg Multiple 3
	TApexFtdcLegMultipleType	LegMultiple3;
	///Offset Flag 3
	TApexFtdcOffsetFlagType	OffsetFlag3;
	///Hedge Flag 3
	TApexFtdcHedgeFlagType	HedgeFlag3;
	///Instrument ID 4
	TApexFtdcInstrumentIDType	InstrumentID4;
	///Direction 4
	TApexFtdcDirectionType	Direction4;
	///Leg Multiple 4
	TApexFtdcLegMultipleType	LegMultiple4;
	///Offset Flag 4
	TApexFtdcOffsetFlagType	OffsetFlag4;
	///Hedge Flag 4
	TApexFtdcHedgeFlagType	HedgeFlag4;
};

///Force User Exit
struct CApexFtdcForceUserExitField
{
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///User ID
	TApexFtdcUserIDType	UserID;
};

///Account Deposit
struct CApexFtdcAccountDepositField
{
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Account
	TApexFtdcAccountIDType	Account;
	///Deposite Amount
	TApexFtdcMoneyType	Deposit;
};

///Order Query
struct CApexFtdcQryOrderField
{
	///Participant ID Start
	TApexFtdcParticipantIDType	PartIDStart;
	///Participant ID End
	TApexFtdcParticipantIDType	PartIDEnd;
	///Order System ID
	TApexFtdcOrderSysIDType	OrderSysID;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Time Start
	TApexFtdcTimeType	TimeStart;
	///Time End
	TApexFtdcTimeType	TimeEnd;
};

///Quote Query
struct CApexFtdcQryQuoteField
{
	///Participant ID Start
	TApexFtdcParticipantIDType	PartIDStart;
	///Participant ID End
	TApexFtdcParticipantIDType	PartIDEnd;
	///Quote System ID
	TApexFtdcQuoteSysIDType	QuoteSysID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///User ID
	TApexFtdcUserIDType	UserID;
};

///Trade Query
struct CApexFtdcQryTradeField
{
	///Participant ID Start
	TApexFtdcParticipantIDType	PartIDStart;
	///Participant ID End
	TApexFtdcParticipantIDType	PartIDEnd;
	///Instrument ID Start
	TApexFtdcInstrumentIDType	InstIDStart;
	///Instrument ID End
	TApexFtdcInstrumentIDType	InstIDEnd;
	///Trade ID
	TApexFtdcTradeIDType	TradeID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Time Start
	TApexFtdcTimeType	TimeStart;
	///Time End
	TApexFtdcTimeType	TimeEnd;
};

///Market Data Query
struct CApexFtdcQryMarketDataField
{
	///Product ID
	TApexFtdcProductIDType	ProductID;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
};

///Client Query
struct CApexFtdcQryClientField
{
	///Participant ID Start
	TApexFtdcParticipantIDType	PartIDStart;
	///Participant ID End
	TApexFtdcParticipantIDType	PartIDEnd;
	///Client ID Start
	TApexFtdcClientIDType	ClientIDStart;
	///Client ID End
	TApexFtdcClientIDType	ClientIDEnd;
};

///Participant Position Query
struct CApexFtdcQryPartPositionField
{
	///Participant ID Start
	TApexFtdcParticipantIDType	PartIDStart;
	///Participant ID End
	TApexFtdcParticipantIDType	PartIDEnd;
	///Instrument ID Start
	TApexFtdcInstrumentIDType	InstIDStart;
	///Instrument ID End
	TApexFtdcInstrumentIDType	InstIDEnd;
};

///Client Position Query
struct CApexFtdcQryClientPositionField
{
	///Participant ID Start
	TApexFtdcParticipantIDType	PartIDStart;
	///Participant ID End
	TApexFtdcParticipantIDType	PartIDEnd;
	///Client ID Start
	TApexFtdcClientIDType	ClientIDStart;
	///Client ID End
	TApexFtdcClientIDType	ClientIDEnd;
	///Instrument ID Start
	TApexFtdcInstrumentIDType	InstIDStart;
	///Instrument ID End
	TApexFtdcInstrumentIDType	InstIDEnd;
	///Client Type
	TApexFtdcClientTypeType	ClientType;
};

///Participant Account Query
struct CApexFtdcQryPartAccountField
{
	///Participant ID Start
	TApexFtdcParticipantIDType	PartIDStart;
	///Participant ID End
	TApexFtdcParticipantIDType	PartIDEnd;
	///Account ID
	TApexFtdcAccountIDType	AccountID;
};

///Instrument Query
struct CApexFtdcQryInstrumentField
{
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Product Group ID
	TApexFtdcProductGroupIDType	ProductGroupID;
	///Product ID
	TApexFtdcProductIDType	ProductID;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
};

///Instrument Status Query
struct CApexFtdcQryInstrumentStatusField
{
	///Instrument ID Start
	TApexFtdcInstrumentIDType	InstIDStart;
	///Instrument ID End
	TApexFtdcInstrumentIDType	InstIDEnd;
};

///Settlement Group Data Synchronization Status Query
struct CApexFtdcQrySGDataSyncStatusField
{
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
};

///User Session Query
struct CApexFtdcQryUserSessionField
{
	///User ID Start
	TApexFtdcUserIDType	UserIDStart;
	///User ID End
	TApexFtdcUserIDType	UserIDEnd;
};

///User Query
struct CApexFtdcQryUserField
{
	///User ID Start
	TApexFtdcUserIDType	UserIDStart;
	///User ID End
	TApexFtdcUserIDType	UserIDEnd;
};

///Bulletin Query
struct CApexFtdcQryBulletinField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Market ID
	TApexFtdcMarketIDType	MarketID;
	///Bulletin ID
	TApexFtdcBulletinIDType	BulletinID;
	///News Type
	TApexFtdcNewsTypeType	NewsType;
	///News Urgency
	TApexFtdcNewsUrgencyType	NewsUrgency;
};

///Participant Query
struct CApexFtdcQryParticipantField
{
	///Participant ID Start
	TApexFtdcParticipantIDType	PartIDStart;
	///Participant ID End
	TApexFtdcParticipantIDType	PartIDEnd;
};

///Hedge Volume Query
struct CApexFtdcQryHedgeVolumeField
{
	///Participant ID Start
	TApexFtdcParticipantIDType	PartIDStart;
	///Participant ID End
	TApexFtdcParticipantIDType	PartIDEnd;
	///Client ID Start
	TApexFtdcClientIDType	ClientIDStart;
	///Client ID End
	TApexFtdcClientIDType	ClientIDEnd;
	///Instrument ID Start
	TApexFtdcInstrumentIDType	InstIDStart;
	///Instrument ID End
	TApexFtdcInstrumentIDType	InstIDEnd;
};

///Pending Order Breakdown List Query
struct CApexFtdcQryMBLMarketDataField
{
	///Instrument ID Start
	TApexFtdcInstrumentIDType	InstIDStart;
	///Instrument ID End
	TApexFtdcInstrumentIDType	InstIDEnd;
	///Direction
	TApexFtdcDirectionType	Direction;
};

///Credit Limit Query
struct CApexFtdcQryCreditLimitField
{
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Clearing Member ID
	TApexFtdcParticipantIDType	ClearingPartID;
};

///Compund Order Query
struct CApexFtdcQryCombOrderField
{
	///Partipant ID Start
	TApexFtdcParticipantIDType	PartIDStart;
	///Partipant ID End
	TApexFtdcParticipantIDType	PartIDEnd;
	///Combination Order System ID
	TApexFtdcOrderSysIDType	CombOrderSysID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///User ID
	TApexFtdcUserIDType	UserID;
};

///Participant Account Response
struct CApexFtdcRspPartAccountField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Previous Balance
	TApexFtdcMoneyType	PreBalance;
	///Current Margin
	TApexFtdcMoneyType	CurrMargin;
	///Close Profit/Loss
	TApexFtdcMoneyType	CloseProfit;
	///Premium
	TApexFtdcMoneyType	Premium;
	///Deposit
	TApexFtdcMoneyType	Deposit;
	///withdrawal
	TApexFtdcMoneyType	Withdraw;
	///Balance
	TApexFtdcMoneyType	Balance;
	///Available
	TApexFtdcMoneyType	Available;
	///Account ID
	TApexFtdcAccountIDType	AccountID;
	///Frozen Margin
	TApexFtdcMoneyType	FrozenMargin;
	///Frozen Premium
	TApexFtdcMoneyType	FrozenPremium;
	///Base Reserve
	TApexFtdcMoneyType	BaseReserve;
};

///Participant Position Response
struct CApexFtdcRspPartPositionField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Hedge Flag
	TApexFtdcHedgeFlagType	HedgeFlag;
	///Position Direction
	TApexFtdcPosiDirectionType	PosiDirection;
	///Yesterday Position
	TApexFtdcVolumeType	YdPosition;
	///Position
	TApexFtdcVolumeType	Position;
	///Long Frozen
	TApexFtdcVolumeType	LongFrozen;
	///Short Frozen
	TApexFtdcVolumeType	ShortFrozen;
	///Yesterday Long Frozen
	TApexFtdcVolumeType	YdLongFrozen;
	///Yesterday Short Frozen
	TApexFtdcVolumeType	YdShortFrozen;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Trading Role
	TApexFtdcTradingRoleType	TradingRole;
};

///Client Position Response
struct CApexFtdcRspClientPositionField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Hedge Flag
	TApexFtdcHedgeFlagType	HedgeFlag;
	///Position Direction
	TApexFtdcPosiDirectionType	PosiDirection;
	///Yesterday Position
	TApexFtdcVolumeType	YdPosition;
	///Position
	TApexFtdcVolumeType	Position;
	///Long Frozen
	TApexFtdcVolumeType	LongFrozen;
	///Short Frozen
	TApexFtdcVolumeType	ShortFrozen;
	///Yesterday Long Frozen
	TApexFtdcVolumeType	YdLongFrozen;
	///Yesterday Short Frozen
	TApexFtdcVolumeType	YdShortFrozen;
	///Buy Trade Volume
	TApexFtdcVolumeType	BuyTradeVolume;
	///Sell Trade Volume
	TApexFtdcVolumeType	SellTradeVolume;
	///Position Cost
	TApexFtdcMoneyType	PositionCost;
	///Yesterday Position Cost
	TApexFtdcMoneyType	YdPositionCost;
	///Used Margin
	TApexFtdcMoneyType	UseMargin;
	///Frozen Margin
	TApexFtdcMoneyType	FrozenMargin;
	///Long Frozen Margin
	TApexFtdcMoneyType	LongFrozenMargin;
	///Short Frozen Margin
	TApexFtdcMoneyType	ShortFrozenMargin;
	///Frozen Premium
	TApexFtdcMoneyType	FrozenPremium;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
};

///Instrument Response
struct CApexFtdcRspInstrumentField
{
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Product ID
	TApexFtdcProductIDType	ProductID;
	///Product Group ID
	TApexFtdcProductGroupIDType	ProductGroupID;
	///Underlying Instrument ID
	TApexFtdcInstrumentIDType	UnderlyingInstrID;
	///Product Class
	TApexFtdcProductClassType	ProductClass;
	///Position Type
	TApexFtdcPositionTypeType	PositionType;
	///Strike Price
	TApexFtdcPriceType	StrikePrice;
	///Options Type
	TApexFtdcOptionsTypeType	OptionsType;
	///Volume Multiple
	TApexFtdcVolumeMultipleType	VolumeMultiple;
	///Underlying Multiple
	TApexFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Instrument Name
	TApexFtdcInstrumentNameType	InstrumentName;
	///Delivery Year
	TApexFtdcYearType	DeliveryYear;
	///Delivery Month
	TApexFtdcMonthType	DeliveryMonth;
	///Advance Month
	TApexFtdcAdvanceMonthType	AdvanceMonth;
	///A flag indicating Is Trading now
	TApexFtdcBoolType	IsTrading;
	///Currency ID
	TApexFtdcCurrencyIDType	CurrencyID;
	///Create Date
	TApexFtdcDateType	CreateDate;
	///Open Date
	TApexFtdcDateType	OpenDate;
	///Expiry Date
	TApexFtdcDateType	ExpireDate;
	///Start Delivery Date
	TApexFtdcDateType	StartDelivDate;
	///End Delivery Date
	TApexFtdcDateType	EndDelivDate;
	///Basis Price
	TApexFtdcPriceType	BasisPrice;
	///Max Market Order Volume
	TApexFtdcVolumeType	MaxMarketOrderVolume;
	///Min Market Order Volume
	TApexFtdcVolumeType	MinMarketOrderVolume;
	///Max Limit Order Volume
	TApexFtdcVolumeType	MaxLimitOrderVolume;
	///Min Limit Order Volume
	TApexFtdcVolumeType	MinLimitOrderVolume;
	///Price Tick
	TApexFtdcPriceType	PriceTick;
	///Allow Deliver Person Open
	TApexFtdcMonthCountType	AllowDelivPersonOpen;
};

///Information Query
struct CApexFtdcQryInformationField
{
	///Information ID Start
	TApexFtdcInformationIDType	InformationIDStart;
	///Information ID End
	TApexFtdcInformationIDType	InformationIDEnd;
};

///Information
struct CApexFtdcInformationField
{
	///Information ID
	TApexFtdcInformationIDType	InformationID;
	///Sequence No
	TApexFtdcSequenceNoType	SequenceNo;
	///Content
	TApexFtdcContentType	Content;
	///Content Length
	TApexFtdcContentLengthType	ContentLength;
	///Is Accomplished
	TApexFtdcBoolType	IsAccomplished;
};

///Credit Limit
struct CApexFtdcCreditLimitField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Previous Balance
	TApexFtdcMoneyType	PreBalance;
	///Current Margin
	TApexFtdcMoneyType	CurrMargin;
	///Close Profit/Loss
	TApexFtdcMoneyType	CloseProfit;
	///Premium
	TApexFtdcMoneyType	Premium;
	///Deposit
	TApexFtdcMoneyType	Deposit;
	///withdrawal
	TApexFtdcMoneyType	Withdraw;
	///Balance
	TApexFtdcMoneyType	Balance;
	///Available
	TApexFtdcMoneyType	Available;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Clearing Participant ID
	TApexFtdcParticipantIDType	ClearingPartID;
	///Frozen Margin
	TApexFtdcMoneyType	FrozenMargin;
	///Frozen Premium
	TApexFtdcMoneyType	FrozenPremium;
};

///Client Response
struct CApexFtdcRspClientField
{
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///Client Name
	TApexFtdcPartyNameType	ClientName;
	///ID Card Type
	TApexFtdcIdCardTypeType	IdentifiedCardType;
	///Original ID Number
	TApexFtdcIdentifiedCardNoV1Type	UseLess;
	///Trading Role
	TApexFtdcTradingRoleType	TradingRole;
	///Client Type
	TApexFtdcClientTypeType	ClientType;
	///Is Active
	TApexFtdcBoolType	IsActive;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///ID Card Number
	TApexFtdcIdentifiedCardNoType	IdentifiedCardNo;
};

///Flow Message Cancellation
struct CApexFtdcFlowMessageCancelField
{
	///Sequence Series
	TApexFtdcSequenceSeriesType	SequenceSeries;
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Data Center ID
	TApexFtdcDataCenterIDType	DataCenterID;
	///Start Sequence Number
	TApexFtdcSequenceNoType	StartSequenceNo;
	///End Sequence Number
	TApexFtdcSequenceNoType	EndSequenceNo;
};

///Participant
struct CApexFtdcParticipantField
{
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Participant Name
	TApexFtdcParticipantNameType	ParticipantName;
	///Participant Abbreviation
	TApexFtdcParticipantAbbrType	ParticipantAbbr;
	///Member Type
	TApexFtdcMemberTypeType	MemberType;
	///A flag indicating Is Active Participant
	TApexFtdcBoolType	IsActive;
};

///User
struct CApexFtdcUserField
{
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///User Type
	TApexFtdcUserTypeType	UserType;
	///Password
	TApexFtdcPasswordType	Password;
	///A flag indicating Is Active User
	TApexFtdcUserActiveType	IsActive;
};

///User Session
struct CApexFtdcUserSessionField
{
	///Front ID
	TApexFtdcFrontIDType	FrontID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///User Type
	TApexFtdcUserTypeType	UserType;
	///Session ID
	TApexFtdcSessionIDType	SessionID;
	///Login Time
	TApexFtdcTimeType	LoginTime;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///IP Address
	TApexFtdcIPAddressType	IPAddress;
	///User Product Info
	TApexFtdcProductInfoType	UserProductInfo;
	///Interface Product Info
	TApexFtdcProductInfoType	InterfaceProductInfo;
	///Protocol Info
	TApexFtdcProtocolInfoType	ProtocolInfo;
};

///Product Group
struct CApexFtdcProductGroupField
{
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Product Group ID
	TApexFtdcProductGroupIDType	ProductGroupID;
	///Product Group Name
	TApexFtdcProductGroupNameType	ProductGroupName;
	///Commodity ID
	TApexFtdcCommodityIDType	CommodityID;
};

///Product
struct CApexFtdcProductField
{
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Product ID
	TApexFtdcProductIDType	ProductID;
	///Product Group ID
	TApexFtdcProductGroupIDType	ProductGroupID;
	///Product Name
	TApexFtdcProductNameType	ProductName;
	///Product Class
	TApexFtdcProductClassType	ProductClass;
};

///Instrument
struct CApexFtdcInstrumentField
{
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Product ID
	TApexFtdcProductIDType	ProductID;
	///Product Group ID
	TApexFtdcProductGroupIDType	ProductGroupID;
	///Underlying Instrument ID
	TApexFtdcInstrumentIDType	UnderlyingInstrID;
	///Product Class
	TApexFtdcProductClassType	ProductClass;
	///Position Type
	TApexFtdcPositionTypeType	PositionType;
	///Strike Price
	TApexFtdcPriceType	StrikePrice;
	///Options Type
	TApexFtdcOptionsTypeType	OptionsType;
	///Volume Multiple
	TApexFtdcVolumeMultipleType	VolumeMultiple;
	///Underlying Multiple
	TApexFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Instrument Name
	TApexFtdcInstrumentNameType	InstrumentName;
	///Delivery Year
	TApexFtdcYearType	DeliveryYear;
	///Delivery Month
	TApexFtdcMonthType	DeliveryMonth;
	///Advance Month
	TApexFtdcAdvanceMonthType	AdvanceMonth;
	///A flag indicating Is Trading now
	TApexFtdcBoolType	IsTrading;
	///Currency ID
	TApexFtdcCurrencyIDType	CurrencyID;
};

///Combined Order Leg
struct CApexFtdcCombinationLegField
{
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Combination Instrument ID
	TApexFtdcInstrumentIDType	CombInstrumentID;
	///Leg ID
	TApexFtdcLegIDType	LegID;
	///Leg Instrument ID
	TApexFtdcInstrumentIDType	LegInstrumentID;
	///Direction
	TApexFtdcDirectionType	Direction;
	///Leg Multiple
	TApexFtdcLegMultipleType	LegMultiple;
	///Imply Level
	TApexFtdcImplyLevelType	ImplyLevel;
};

///Account Information
struct CApexFtdcAccountInfoField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Previous Balance
	TApexFtdcMoneyType	PreBalance;
	///Current Margin
	TApexFtdcMoneyType	CurrMargin;
	///Close Profit/Loss
	TApexFtdcMoneyType	CloseProfit;
	///Premium
	TApexFtdcMoneyType	Premium;
	///Deposit
	TApexFtdcMoneyType	Deposit;
	///withdrawal
	TApexFtdcMoneyType	Withdraw;
	///Balance
	TApexFtdcMoneyType	Balance;
	///Available
	TApexFtdcMoneyType	Available;
	///Date Account Open
	TApexFtdcDateType	DateAccountOpen;
	///Previoius Settlement Date
	TApexFtdcDateType	PreDate;
	///Previoius Settlement ID
	TApexFtdcSettlementIDType	PreSettlementID;
	///Previoius Margin
	TApexFtdcMoneyType	PreMargin;
	///Futures Margin
	TApexFtdcMoneyType	FuturesMargin;
	///Options Margin
	TApexFtdcMoneyType	OptionsMargin;
	///Position Profit
	TApexFtdcMoneyType	PositionProfit;
	///Profit/Loss
	TApexFtdcMoneyType	Profit;
	///Interest
	TApexFtdcMoneyType	Interest;
	///Fee
	TApexFtdcMoneyType	Fee;
	///Total Collateral
	TApexFtdcMoneyType	TotalCollateral;
	///Collateral For Margin
	TApexFtdcMoneyType	CollateralForMargin;
	///Previoius Accmulated Interest
	TApexFtdcMoneyType	PreAccmulateInterest;
	///Accumulated Interest
	TApexFtdcMoneyType	AccumulateInterest;
	///Accumulated Fee
	TApexFtdcMoneyType	AccumulateFee;
	///Forzen Deposit
	TApexFtdcMoneyType	ForzenDeposit;
	///Account Status
	TApexFtdcAccountStatusType	AccountStatus;
	///Account ID
	TApexFtdcAccountIDType	AccountID;
};

///Participant Position
struct CApexFtdcPartPositionField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Hedge Flag
	TApexFtdcHedgeFlagType	HedgeFlag;
	///Position Direction
	TApexFtdcPosiDirectionType	PosiDirection;
	///Yesterday Position
	TApexFtdcVolumeType	YdPosition;
	///Position
	TApexFtdcVolumeType	Position;
	///Long Frozen
	TApexFtdcVolumeType	LongFrozen;
	///Short Frozen
	TApexFtdcVolumeType	ShortFrozen;
	///Yesterday Long Frozen
	TApexFtdcVolumeType	YdLongFrozen;
	///Yesterday Short Frozen
	TApexFtdcVolumeType	YdShortFrozen;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Trading Role
	TApexFtdcTradingRoleType	TradingRole;
};

///Client Position
struct CApexFtdcClientPositionField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Hedge Flag
	TApexFtdcHedgeFlagType	HedgeFlag;
	///Position Direction
	TApexFtdcPosiDirectionType	PosiDirection;
	///Yesterday Position
	TApexFtdcVolumeType	YdPosition;
	///Position
	TApexFtdcVolumeType	Position;
	///Long Frozen
	TApexFtdcVolumeType	LongFrozen;
	///Short Frozen
	TApexFtdcVolumeType	ShortFrozen;
	///Yesterday Long Frozen
	TApexFtdcVolumeType	YdLongFrozen;
	///Yesterday Short Frozen
	TApexFtdcVolumeType	YdShortFrozen;
	///Buy Trade Volume
	TApexFtdcVolumeType	BuyTradeVolume;
	///Sell Trade Volume
	TApexFtdcVolumeType	SellTradeVolume;
	///Position Cost
	TApexFtdcMoneyType	PositionCost;
	///Yesterday Position Cost
	TApexFtdcMoneyType	YdPositionCost;
	///Used Margin
	TApexFtdcMoneyType	UseMargin;
	///Frozen Margin
	TApexFtdcMoneyType	FrozenMargin;
	///Long Frozen Margin
	TApexFtdcMoneyType	LongFrozenMargin;
	///Short Frozen Margin
	TApexFtdcMoneyType	ShortFrozenMargin;
	///Frozen Premium
	TApexFtdcMoneyType	FrozenPremium;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
};

///Hedge Volume
struct CApexFtdcHedgeVolumeField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Long Volume Original
	TApexFtdcVolumeType	LongVolumeOriginal;
	///Short Volume Original
	TApexFtdcVolumeType	ShortVolumeOriginal;
	///Long Volume
	TApexFtdcVolumeType	LongVolume;
	///Short Volume
	TApexFtdcVolumeType	ShortVolume;
};

///Market Data
struct CApexFtdcMarketDataField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Last Price
	TApexFtdcPriceType	LastPrice;
	///Previous Settlement Price
	TApexFtdcPriceType	PreSettlementPrice;
	///Previous Close Price
	TApexFtdcPriceType	PreClosePrice;
	///Previous Open Interest
	TApexFtdcLargeVolumeType	PreOpenInterest;
	///Open Price
	TApexFtdcPriceType	OpenPrice;
	///Highest Price
	TApexFtdcPriceType	HighestPrice;
	///Lowest Price
	TApexFtdcPriceType	LowestPrice;
	///Volume
	TApexFtdcVolumeType	Volume;
	///Turnover
	TApexFtdcMoneyType	Turnover;
	///Open Interest
	TApexFtdcLargeVolumeType	OpenInterest;
	///Close Price
	TApexFtdcPriceType	ClosePrice;
	///Settlement Price
	TApexFtdcPriceType	SettlementPrice;
	///Upper Limit Price
	TApexFtdcPriceType	UpperLimitPrice;
	///Lower Limit Price
	TApexFtdcPriceType	LowerLimitPrice;
	///Previoius Delta
	TApexFtdcRatioType	PreDelta;
	///Current Delta
	TApexFtdcRatioType	CurrDelta;
	///Update Time
	TApexFtdcTimeType	UpdateTime;
	///Update Milli second
	TApexFtdcMillisecType	UpdateMillisec;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
};

///Full Market Data
struct CApexFtdcDepthMarketDataField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Last Price
	TApexFtdcPriceType	LastPrice;
	///Previous Settlement Price
	TApexFtdcPriceType	PreSettlementPrice;
	///Previous Close Price
	TApexFtdcPriceType	PreClosePrice;
	///Previous Open Interest
	TApexFtdcLargeVolumeType	PreOpenInterest;
	///Open Price
	TApexFtdcPriceType	OpenPrice;
	///Highest Price
	TApexFtdcPriceType	HighestPrice;
	///Lowest Price
	TApexFtdcPriceType	LowestPrice;
	///Volume
	TApexFtdcVolumeType	Volume;
	///Turnover
	TApexFtdcMoneyType	Turnover;
	///Open Interest
	TApexFtdcLargeVolumeType	OpenInterest;
	///Close Price
	TApexFtdcPriceType	ClosePrice;
	///Settlement Price
	TApexFtdcPriceType	SettlementPrice;
	///Upper Limit Price
	TApexFtdcPriceType	UpperLimitPrice;
	///Lower Limit Price
	TApexFtdcPriceType	LowerLimitPrice;
	///Previoius Delta
	TApexFtdcRatioType	PreDelta;
	///Current Delta
	TApexFtdcRatioType	CurrDelta;
	///Update Time
	TApexFtdcTimeType	UpdateTime;
	///Update Milli second
	TApexFtdcMillisecType	UpdateMillisec;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Bid Price 1
	TApexFtdcPriceType	BidPrice1;
	///Bid Volume 1
	TApexFtdcVolumeType	BidVolume1;
	///Ask Price 1
	TApexFtdcPriceType	AskPrice1;
	///Ask Volume 1
	TApexFtdcVolumeType	AskVolume1;
	///Bid Price 2
	TApexFtdcPriceType	BidPrice2;
	///Bid Volume 2
	TApexFtdcVolumeType	BidVolume2;
	///Ask Price 2
	TApexFtdcPriceType	AskPrice2;
	///Ask Volume 2
	TApexFtdcVolumeType	AskVolume2;
	///Bid Price 3
	TApexFtdcPriceType	BidPrice3;
	///Bid Volume 3
	TApexFtdcVolumeType	BidVolume3;
	///Ask Price 3
	TApexFtdcPriceType	AskPrice3;
	///Ask Volume 3
	TApexFtdcVolumeType	AskVolume3;
	///Bid Price 4
	TApexFtdcPriceType	BidPrice4;
	///Bid Volume 4
	TApexFtdcVolumeType	BidVolume4;
	///Ask Price 4
	TApexFtdcPriceType	AskPrice4;
	///Ask Volume 4
	TApexFtdcVolumeType	AskVolume4;
	///Bid Price 5
	TApexFtdcPriceType	BidPrice5;
	///Bid Volume 5
	TApexFtdcVolumeType	BidVolume5;
	///Ask Price 5
	TApexFtdcPriceType	AskPrice5;
	///Ask Volume 5
	TApexFtdcVolumeType	AskVolume5;
	///Upper BandingPrice
	TApexFtdcPriceType	BandingUpperPrice;
	///Lower BandingPrice
	TApexFtdcPriceType	BandingLowerPrice;
	///Reference Price
	TApexFtdcPriceType	ReferencePrice;
	///Calendar Date
	TApexFtdcDateType	CalendarDate;
};

///Pending Order Breakdown List
struct CApexFtdcMBLMarketDataField
{
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Direction
	TApexFtdcDirectionType	Direction;
	///Price
	TApexFtdcPriceType	Price;
	///Volume
	TApexFtdcVolumeType	Volume;
};

///Alias Definition
struct CApexFtdcAliasDefineField
{
	///Start Position
	TApexFtdcStartPosType	StartPos;
	///Alias
	TApexFtdcAliasType	Alias;
	///Original Text
	TApexFtdcOriginalTextType	OriginalText;
};

///Market Data Base Properties
struct CApexFtdcMarketDataBaseField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Previous Settlement Price
	TApexFtdcPriceType	PreSettlementPrice;
	///Previous Close Price
	TApexFtdcPriceType	PreClosePrice;
	///Previous Open Interest
	TApexFtdcLargeVolumeType	PreOpenInterest;
	///Previous Delta
	TApexFtdcRatioType	PreDelta;
};

///Market Data Static Properties
struct CApexFtdcMarketDataStaticField
{
	///Open Price
	TApexFtdcPriceType	OpenPrice;
	///Highest Price
	TApexFtdcPriceType	HighestPrice;
	///Lowest Price
	TApexFtdcPriceType	LowestPrice;
	///Close Price
	TApexFtdcPriceType	ClosePrice;
	///Upper Limit Price
	TApexFtdcPriceType	UpperLimitPrice;
	///Lower Limit Price
	TApexFtdcPriceType	LowerLimitPrice;
	///Settlement Price
	TApexFtdcPriceType	SettlementPrice;
	///Current Delta
	TApexFtdcRatioType	CurrDelta;
};

///Market Data for Last Match
struct CApexFtdcMarketDataLastMatchField
{
	///Last Price
	TApexFtdcPriceType	LastPrice;
	///Volume
	TApexFtdcVolumeType	Volume;
	///Turnover
	TApexFtdcMoneyType	Turnover;
	///Open Interest
	TApexFtdcLargeVolumeType	OpenInterest;
};

///Market Data for Best Price
struct CApexFtdcMarketDataBestPriceField
{
	///Bid Price 1
	TApexFtdcPriceType	BidPrice1;
	///Bid Volume 1
	TApexFtdcVolumeType	BidVolume1;
	///Ask Price 1
	TApexFtdcPriceType	AskPrice1;
	///Ask Volume 1
	TApexFtdcVolumeType	AskVolume1;
};

///Market Data for 2nd and 3rd Bid
struct CApexFtdcMarketDataBid23Field
{
	///Bid Price 2
	TApexFtdcPriceType	BidPrice2;
	///Bid Volume 2
	TApexFtdcVolumeType	BidVolume2;
	///Bid Price 3
	TApexFtdcPriceType	BidPrice3;
	///Bid Volume 3
	TApexFtdcVolumeType	BidVolume3;
};

///Market Data for 2nd and 3rd Ask
struct CApexFtdcMarketDataAsk23Field
{
	///Ask Price 2
	TApexFtdcPriceType	AskPrice2;
	///Ask Volume 2
	TApexFtdcVolumeType	AskVolume2;
	///Ask Price 3
	TApexFtdcPriceType	AskPrice3;
	///Ask Volume 3
	TApexFtdcVolumeType	AskVolume3;
};

///Market Data for 4th and 5th Bid
struct CApexFtdcMarketDataBid45Field
{
	///Bid Price 4
	TApexFtdcPriceType	BidPrice4;
	///Bid Volume 4
	TApexFtdcVolumeType	BidVolume4;
	///Bid Price 5
	TApexFtdcPriceType	BidPrice5;
	///Bid Volume 5
	TApexFtdcVolumeType	BidVolume5;
};

///Market Data for 4th and 5th Ask
struct CApexFtdcMarketDataAsk45Field
{
	///Ask Price 4
	TApexFtdcPriceType	AskPrice4;
	///Ask Volume 4
	TApexFtdcVolumeType	AskVolume4;
	///Ask Price 5
	TApexFtdcPriceType	AskPrice5;
	///Ask Volume 5
	TApexFtdcVolumeType	AskVolume5;
};

///Market Data Update Time
struct CApexFtdcMarketDataUpdateTimeField
{
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Update Time
	TApexFtdcTimeType	UpdateTime;
	///Last Update in Milli-Sececond
	TApexFtdcMillisecType	UpdateMillisec;
	///Calendar Date
	TApexFtdcDateType	CalendarDate;
};

///Market Data PriceBanding Properties
struct CApexFtdcMarketDataRealPriceBandingField
{
	///Upper BandingPrice
	TApexFtdcPriceType	BandingUpperPrice;
	///Lower BandingPrice
	TApexFtdcPriceType	BandingLowerPrice;
	///Reference Price
	TApexFtdcPriceType	ReferencePrice;
};

///Quote
struct CApexFtdcQuoteField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Quote System ID
	TApexFtdcQuoteSysIDType	QuoteSysID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Bid Volume
	TApexFtdcVolumeType	BidVolume;
	///Ask Volume
	TApexFtdcVolumeType	AskVolume;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///QuoteLocal ID
	TApexFtdcOrderLocalIDType	QuoteLocalID;
	///Business Unit
	TApexFtdcBusinessUnitType	BusinessUnit;
	///Bid Combination Offset Flag
	TApexFtdcCombOffsetFlagType	BidCombOffsetFlag;
	///Bid Combination Hedge Flag
	TApexFtdcCombHedgeFlagType	BidCombHedgeFlag;
	///Bid Price
	TApexFtdcPriceType	BidPrice;
	///Ask Combination Offset Flag
	TApexFtdcCombOffsetFlagType	AskCombOffsetFlag;
	///Ask Combination Hedge Flag
	TApexFtdcCombHedgeFlagType	AskCombHedgeFlag;
	///Ask Price
	TApexFtdcPriceType	AskPrice;
	///Insert Time
	TApexFtdcTimeType	InsertTime;
	///Cancel Time
	TApexFtdcTimeType	CancelTime;
	///Trade Time
	TApexFtdcTimeType	TradeTime;
	///Bid Order System ID
	TApexFtdcOrderSysIDType	BidOrderSysID;
	///Ask Order System ID
	TApexFtdcOrderSysIDType	AskOrderSysID;
	///Clearing Participant ID
	TApexFtdcParticipantIDType	ClearingPartID;
	///Calendar Date
	TApexFtdcDateType	CalendarDate;
};

///Trade
struct CApexFtdcTradeField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Trade ID
	TApexFtdcTradeIDType	TradeID;
	///Direction
	TApexFtdcDirectionType	Direction;
	///Order System ID
	TApexFtdcOrderSysIDType	OrderSysID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///Trading Role
	TApexFtdcTradingRoleType	TradingRole;
	///Account ID
	TApexFtdcAccountIDType	AccountID;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Offset Flag
	TApexFtdcOffsetFlagType	OffsetFlag;
	///Hedge Flag
	TApexFtdcHedgeFlagType	HedgeFlag;
	///Price
	TApexFtdcPriceType	Price;
	///Volume
	TApexFtdcVolumeType	Volume;
	///Trade Time
	TApexFtdcTimeType	TradeTime;
	///TradeType
	TApexFtdcTradeTypeType	TradeType;
	///Price Source
	TApexFtdcPriceSourceType	PriceSource;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Local Order ID
	TApexFtdcOrderLocalIDType	OrderLocalID;
	///Clearing Participant ID
	TApexFtdcParticipantIDType	ClearingPartID;
	///Business Unit
	TApexFtdcBusinessUnitType	BusinessUnit;
	///Calendar Date
	TApexFtdcDateType	CalendarDate;
};

///Order
struct CApexFtdcOrderField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Order System ID
	TApexFtdcOrderSysIDType	OrderSysID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Order Price Type
	TApexFtdcOrderPriceTypeType	OrderPriceType;
	///Direction
	TApexFtdcDirectionType	Direction;
	///Combintation Offset Flag
	TApexFtdcCombOffsetFlagType	CombOffsetFlag;
	///Combintation Hedge Flag
	TApexFtdcCombHedgeFlagType	CombHedgeFlag;
	///Limit Price
	TApexFtdcPriceType	LimitPrice;
	///Volume Total Original
	TApexFtdcVolumeType	VolumeTotalOriginal;
	///Time Condition
	TApexFtdcTimeConditionType	TimeCondition;
	///GTD Date
	TApexFtdcDateType	GTDDate;
	///Volume Condition
	TApexFtdcVolumeConditionType	VolumeCondition;
	///Min Volume
	TApexFtdcVolumeType	MinVolume;
	///Contingent Condition
	TApexFtdcContingentConditionType	ContingentCondition;
	///Stop Price
	TApexFtdcPriceType	StopPrice;
	///Force Close Reason
	TApexFtdcForceCloseReasonType	ForceCloseReason;
	///Local Order ID
	TApexFtdcOrderLocalIDType	OrderLocalID;
	///A flag indicating Is Auto Suspend
	TApexFtdcBoolType	IsAutoSuspend;
	///Order Source
	TApexFtdcOrderSourceType	OrderSource;
	///Order Status
	TApexFtdcOrderStatusType	OrderStatus;
	///Order Type
	TApexFtdcOrderTypeType	OrderType;
	///Volume Traded
	TApexFtdcVolumeType	VolumeTraded;
	///Volume Total
	TApexFtdcVolumeType	VolumeTotal;
	///Insert Date
	TApexFtdcDateType	InsertDate;
	///Insert Time
	TApexFtdcTimeType	InsertTime;
	///Active Time
	TApexFtdcTimeType	ActiveTime;
	///Suspend Time
	TApexFtdcTimeType	SuspendTime;
	///Update Time
	TApexFtdcTimeType	UpdateTime;
	///Cancel Time
	TApexFtdcTimeType	CancelTime;
	///Active User ID
	TApexFtdcUserIDType	ActiveUserID;
	///Priority
	TApexFtdcPriorityType	Priority;
	///Time Sort ID
	TApexFtdcTimeSortIDType	TimeSortID;
	///Clearing Part ID
	TApexFtdcParticipantIDType	ClearingPartID;
	///Business Unit
	TApexFtdcBusinessUnitType	BusinessUnit;
	///Calendar Date
	TApexFtdcDateType	CalendarDate;
};

///Execution Order
struct CApexFtdcExecOrderField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Execution Order Local ID
	TApexFtdcOrderLocalIDType	ExecOrderLocalID;
	///Volume
	TApexFtdcVolumeType	Volume;
	///Business Unit
	TApexFtdcBusinessUnitType	BusinessUnit;
	///Execution Order System ID
	TApexFtdcExecOrderSysIDType	ExecOrderSysID;
	///Insert Date
	TApexFtdcDateType	InsertDate;
	///Insert Time
	TApexFtdcTimeType	InsertTime;
	///Cancel Time
	TApexFtdcTimeType	CancelTime;
	///Execution Result
	TApexFtdcExecResultType	ExecResult;
	///Clearing Partition ID
	TApexFtdcParticipantIDType	ClearingPartID;
	///Calendar Date
	TApexFtdcDateType	CalendarDate;
};

///Combined Order
struct CApexFtdcCombOrderField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Combination Order System ID
	TApexFtdcOrderSysIDType	CombOrderSysID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///User ID
	TApexFtdcUserIDType	UserID;
	///Limit Price
	TApexFtdcPriceType	LimitPrice;
	///Volume Total Original
	TApexFtdcVolumeType	VolumeTotalOriginal;
	///Local Combination Order ID
	TApexFtdcOrderLocalIDType	CombOrderLocalID;
	///Business Unit
	TApexFtdcBusinessUnitType	BusinessUnit;
	///Instrument ID 1
	TApexFtdcInstrumentIDType	InstrumentID1;
	///Direction 1
	TApexFtdcDirectionType	Direction1;
	///Leg Multiple 1
	TApexFtdcLegMultipleType	LegMultiple1;
	///Offset Flag 1
	TApexFtdcOffsetFlagType	OffsetFlag1;
	///Hedge Flag 1
	TApexFtdcHedgeFlagType	HedgeFlag1;
	///Instrument ID 2
	TApexFtdcInstrumentIDType	InstrumentID2;
	///Direction 2
	TApexFtdcDirectionType	Direction2;
	///Leg Multiple 2
	TApexFtdcLegMultipleType	LegMultiple2;
	///Offset Flag 2
	TApexFtdcOffsetFlagType	OffsetFlag2;
	///Hedge Flag 2
	TApexFtdcHedgeFlagType	HedgeFlag2;
	///Instrument ID 3
	TApexFtdcInstrumentIDType	InstrumentID3;
	///Direction 3
	TApexFtdcDirectionType	Direction3;
	///Leg Multiple 3
	TApexFtdcLegMultipleType	LegMultiple3;
	///Offset Flag 3
	TApexFtdcOffsetFlagType	OffsetFlag3;
	///Hedge Flag 3
	TApexFtdcHedgeFlagType	HedgeFlag3;
	///Instrument ID 4
	TApexFtdcInstrumentIDType	InstrumentID4;
	///Direction 4
	TApexFtdcDirectionType	Direction4;
	///Leg Multiple 4
	TApexFtdcLegMultipleType	LegMultiple4;
	///Offset Flag 4
	TApexFtdcOffsetFlagType	OffsetFlag4;
	///Hedge Flag 4
	TApexFtdcHedgeFlagType	HedgeFlag4;
	///Order Source
	TApexFtdcOrderSourceType	OrderSource;
	///VolumeT raded
	TApexFtdcVolumeType	VolumeTraded;
	///Volume Total
	TApexFtdcVolumeType	VolumeTotal;
	///Insert Date
	TApexFtdcDateType	InsertDate;
	///Insert Time
	TApexFtdcTimeType	InsertTime;
	///Clearing Participant ID
	TApexFtdcParticipantIDType	ClearingPartID;
	///Calendar Date
	TApexFtdcDateType	CalendarDate;
};

///Admin Order
struct CApexFtdcAdminOrderField
{
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Admin Order Command
	TApexFtdcAdminOrderCommandFlagType	AdminOrderCommand;
	///Clearing Participant ID
	TApexFtdcParticipantIDType	ClearingPartID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Amount
	TApexFtdcMoneyType	Amount;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
};

///Admin Order Input
struct CApexFtdcInputAdminOrderField
{
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Admin Order Command
	TApexFtdcAdminOrderCommandFlagType	AdminOrderCommand;
	///Clearing Participant ID
	TApexFtdcParticipantIDType	ClearingPartID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Amount
	TApexFtdcMoneyType	Amount;
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
};

///Bulletin
struct CApexFtdcBulletinField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Bulletin ID
	TApexFtdcBulletinIDType	BulletinID;
	///Sequence No
	TApexFtdcSequenceNoType	SequenceNo;
	///News Type
	TApexFtdcNewsTypeType	NewsType;
	///News Urgency Level
	TApexFtdcNewsUrgencyType	NewsUrgency;
	///Send Time
	TApexFtdcTimeType	SendTime;
	///Abstract
	TApexFtdcAbstractType	Abstract;
	///Come From
	TApexFtdcComeFromType	ComeFrom;
	///Content
	TApexFtdcContentType	Content;
	///URL Link
	TApexFtdcURLLinkType	URLLink;
	///Market ID
	TApexFtdcMarketIDType	MarketID;
	///Calendar Date
	TApexFtdcDateType	CalendarDate;
};

///Exchange Data Synchronization Status
struct CApexFtdcExchangeDataSyncStatusField
{
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Exchange ID
	TApexFtdcExchangeIDType	ExchangeID;
	///ExchangeData Sync Status
	TApexFtdcExchangeDataSyncStatusType	ExchangeDataSyncStatus;
};

///Settlement Group Data Synchronization Status
struct CApexFtdcSGDataSyncStatusField
{
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Trading Day
	TApexFtdcDateType	TradingDay;
	///Settlement ID
	TApexFtdcSettlementIDType	SettlementID;
	///Settlement Group Data Sync Status
	TApexFtdcSGDataSyncStatusType	SGDataSyncStatus;
};

///Instrument Status
struct CApexFtdcInstrumentStatusField
{
	///Settlement Group ID
	TApexFtdcSettlementGroupIDType	SettlementGroupID;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Instrument Status
	TApexFtdcInstrumentStatusType	InstrumentStatus;
	///Trading Segment Sequence Number
	TApexFtdcTradingSegmentSNType	TradingSegmentSN;
	///Enter Time
	TApexFtdcTimeType	EnterTime;
	///Enter Reason
	TApexFtdcInstStatusEnterReasonType	EnterReason;
	///Calendar Date
	TApexFtdcDateType	CalendarDate;
};

///Client Position Query
struct CApexFtdcQryClientPositionV1Field
{
	///Participant ID Start
	TApexFtdcParticipantIDType	PartIDStart;
	///Participant ID End
	TApexFtdcParticipantIDType	PartIDEnd;
	///Client ID Start
	TApexFtdcClientIDType	ClientIDStart;
	///Client ID End
	TApexFtdcClientIDType	ClientIDEnd;
	///Instrument ID Start
	TApexFtdcInstrumentIDType	InstIDStart;
	///Instrument ID End
	TApexFtdcInstrumentIDType	InstIDEnd;
};

///Request For Quote Input
struct CApexFtdcInputReqForQuoteField
{
	///Request For Quote ID
	TApexFtdcQuoteSysIDType	ReqForQuoteID;
	///Participant ID
	TApexFtdcParticipantIDType	ParticipantID;
	///Client ID
	TApexFtdcClientIDType	ClientID;
	///Instrument ID
	TApexFtdcInstrumentIDType	InstrumentID;
	///Trading Day
	TApexFtdcTradingDayType	TradingDay;
	///Request For Quote Time
	TApexFtdcTimeType	ReqForQuoteTime;
	///Calendar Date
	TApexFtdcDateType	CalendarDate;
};

///Dump MemTable
struct CApexFtdcDumpMemTableField
{
	///Table Name
	TApexFtdcTableNameType	TableName;
};

///Multi Heartbeat
struct CApexFtdcMultiHeartbeatField
{
	///Current Time
	TApexFtdcTimeType	CurrTime;
	///MultiCastIP
	TApexFtdcMultiIPAddressType	MultiCastIP;
};



#endif
