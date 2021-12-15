/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file UFEntityCopy.h
///@brief实现了UFEntity之间互相复制的程序
///@history 
///20051210	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef UFEntityCopy_H
#define UFEntityCopy_H

#ifndef CopyPositionEntity
#define CopyPositionEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->ParticipantID=(source)->ParticipantID;	\
			(target)->ClientID=(source)->ClientID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->Direction=(source)->Direction;	\
			(target)->HedgeFlag=(source)->HedgeFlag;	\
			(target)->UsedMargin=(source)->UsedMargin;	\
			(target)->Position=(source)->Position;	\
			(target)->PositionCost=(source)->PositionCost;	\
			(target)->YdPosition=(source)->YdPosition;	\
			(target)->YdPositionCost=(source)->YdPositionCost;	\
			(target)->FrozenMargin=(source)->FrozenMargin;	\
			(target)->FrozenPosition=(source)->FrozenPosition;	\
			(target)->FrozenClosing=(source)->FrozenClosing;	\
			(target)->FrozenPremium=(source)->FrozenPremium;	\
			(target)->LastTradeID=(source)->LastTradeID;	\
			(target)->LastOrderLocalID=(source)->LastOrderLocalID;	\
			(target)->Currency=(source)->Currency;	\
			(target)->PositionProfit=(source)->PositionProfit;	\
			(target)->TodayPosition=(source)->TodayPosition;	\
			(target)->FrozenTodayClosing=(source)->FrozenTodayClosing;	\

#endif
#ifndef CopyAPIInvestorPositionEntity
#define CopyAPIInvestorPositionEntity(target,source)	\
			CopyPositionEntity(target,source);	\

#endif
#ifndef CopyInvestorPositionEntity
#define CopyInvestorPositionEntity(target,source)	\
			CopyPositionEntity(target,source);	\
			(target)->TradeType=(source)->TradeType;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->LastPrice=(source)->LastPrice;	\
			(target)->PositionClose=(source)->PositionClose;	\
			(target)->YdPositionClose=(source)->YdPositionClose;	\
			(target)->YdFrozenClosing=(source)->YdFrozenClosing;	\
			(target)->CacalProfitPosition=(source)->CacalProfitPosition;	\
			(target)->OptionType=(source)->OptionType;	\
			(target)->StrikePrice=(source)->StrikePrice;	\
			(target)->OptionInstrumentID=(source)->OptionInstrumentID;	\
			(target)->TodayPositionCost=(source)->TodayPositionCost;	\
			(target)->ShortPosition=(source)->ShortPosition;	\

#endif
#ifndef CopyAPIInvestorAccountEntity
#define CopyAPIInvestorAccountEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->PreBalance=(source)->PreBalance;	\
			(target)->PreAvailable=(source)->PreAvailable;	\
			(target)->Deposit=(source)->Deposit;	\
			(target)->Withdraw=(source)->Withdraw;	\
			(target)->Margin=(source)->Margin;	\
			(target)->Premium=(source)->Premium;	\
			(target)->Fee=(source)->Fee;	\
			(target)->FrozenMargin=(source)->FrozenMargin;	\
			(target)->FrozenPremium=(source)->FrozenPremium;	\
			(target)->FrozenFee=(source)->FrozenFee;	\
			(target)->CloseProfit=(source)->CloseProfit;	\
			(target)->PositionProfit=(source)->PositionProfit;	\
			(target)->Available=(source)->Available;	\
			(target)->Balance=(source)->Balance;	\
			(target)->LongMargin=(source)->LongMargin;	\
			(target)->ShortMargin=(source)->ShortMargin;	\
			(target)->LongFrozenMargin=(source)->LongFrozenMargin;	\
			(target)->ShortFrozenMargin=(source)->ShortFrozenMargin;	\
			(target)->DynamicRights=(source)->DynamicRights;	\
			(target)->Risk=(source)->Risk;	\
			(target)->OtherFee=(source)->OtherFee;	\
			(target)->Mortgage=(source)->Mortgage;	\
			(target)->Currency=(source)->Currency;	\

#endif
#ifndef CopyInvestorAccountEntity
#define CopyInvestorAccountEntity(target,source)	\
			CopyAPIInvestorAccountEntity(target,source);	\
			(target)->TotalFrozenPos=(source)->TotalFrozenPos;	\
			(target)->TodayInOut=(source)->TodayInOut;	\
			(target)->ReleaseMargin=(source)->ReleaseMargin;	\
			(target)->IsProfitCanUse=(source)->IsProfitCanUse;	\
			(target)->ManualFrozen=(source)->ManualFrozen;	\

#endif
#ifndef CopyInvestorAccountDepositEntity
#define CopyInvestorAccountDepositEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->AccountSeqNo=(source)->AccountSeqNo;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->AccountInsideSeqNo=(source)->AccountInsideSeqNo;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->Amount=(source)->Amount;	\
			(target)->AmountDirection=(source)->AmountDirection;	\

#endif
#ifndef CopyReqInvestorAccountDepositEntity
#define CopyReqInvestorAccountDepositEntity(target,source)	\
			CopyInvestorAccountDepositEntity(target,source);	\
			(target)->UserID=(source)->UserID;	\

#endif
#ifndef CopyAPIInvestorAccountDepositResEntity
#define CopyAPIInvestorAccountDepositResEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->AccountSeqNo=(source)->AccountSeqNo;	\
			(target)->AccountInsideSeqNo=(source)->AccountInsideSeqNo;	\
			(target)->Amount=(source)->Amount;	\
			(target)->AmountDirection=(source)->AmountDirection;	\
			(target)->Available=(source)->Available;	\
			(target)->Balance=(source)->Balance;	\

#endif
#ifndef CopyInvestorAccountDepositNtfEntity
#define CopyInvestorAccountDepositNtfEntity(target,source)	\
			CopyAPIInvestorAccountDepositResEntity(target,source);	\
			(target)->UserID=(source)->UserID;	\

#endif
#ifndef CopySeatEntity
#define CopySeatEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->APIID=(source)->APIID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->ParticipantID=(source)->ParticipantID;	\
			(target)->SeatID=(source)->SeatID;	\
			(target)->SeatPassword=(source)->SeatPassword;	\
			(target)->ApiLinkType=(source)->ApiLinkType;	\
			(target)->RecvRtn=(source)->RecvRtn;	\
			(target)->MainSeat=(source)->MainSeat;	\
			(target)->QueryBase=(source)->QueryBase;	\
			(target)->QueryPosition=(source)->QueryPosition;	\
			(target)->ResumeType=(source)->ResumeType;	\
			(target)->Heartbeat=(source)->Heartbeat;	\
			(target)->IsActive=(source)->IsActive;	\
			(target)->RiskCheck=(source)->RiskCheck;	\
			(target)->FrontAddr=(source)->FrontAddr;	\
			(target)->SeatStatus=(source)->SeatStatus;	\
			(target)->OrderLocalID=(source)->OrderLocalID;	\
			(target)->LinkBrokerID=(source)->LinkBrokerID;	\
			(target)->TradingDay=(source)->TradingDay;	\
			(target)->CheckTradingDay=(source)->CheckTradingDay;	\
			(target)->Custom=(source)->Custom;	\

#endif
#ifndef CopyAPIClientTradingIDEntity
#define CopyAPIClientTradingIDEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->ParticipantID=(source)->ParticipantID;	\
			(target)->ClientID=(source)->ClientID;	\
			(target)->ClientRight=(source)->ClientRight;	\
			(target)->ClientType=(source)->ClientType;	\
			(target)->ClientHedgeFlag=(source)->ClientHedgeFlag;	\
			(target)->IsActive=(source)->IsActive;	\

#endif
#ifndef CopyClientTradingIDEntity
#define CopyClientTradingIDEntity(target,source)	\
			CopyAPIClientTradingIDEntity(target,source);	\
			(target)->APIID=(source)->APIID;	\

#endif
#ifndef CopyInvestorEntity
#define CopyInvestorEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->InvestorName=(source)->InvestorName;	\

#endif
#ifndef CopyAPIInvestorMarginEntity
#define CopyAPIInvestorMarginEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->HedgeFlag=(source)->HedgeFlag;	\
			(target)->LongMarginRate=(source)->LongMarginRate;	\
			(target)->LongMarginAmt=(source)->LongMarginAmt;	\
			(target)->ShortMarginRate=(source)->ShortMarginRate;	\
			(target)->ShortMarginAmt=(source)->ShortMarginAmt;	\

#endif
#ifndef CopyInvestorMarginEntity
#define CopyInvestorMarginEntity(target,source)	\
			CopyAPIInvestorMarginEntity(target,source);	\

#endif
#ifndef CopyAPIInvestorFeeEntity
#define CopyAPIInvestorFeeEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->HedgeFlag=(source)->HedgeFlag;	\
			(target)->OpenFeeRate=(source)->OpenFeeRate;	\
			(target)->OpenFeeAmt=(source)->OpenFeeAmt;	\
			(target)->OffsetFeeRate=(source)->OffsetFeeRate;	\
			(target)->OffsetFeeAmt=(source)->OffsetFeeAmt;	\
			(target)->OTFeeRate=(source)->OTFeeRate;	\
			(target)->OTFeeAmt=(source)->OTFeeAmt;	\

#endif
#ifndef CopyInvestorFeeEntity
#define CopyInvestorFeeEntity(target,source)	\
			CopyAPIInvestorFeeEntity(target,source);	\

#endif
#ifndef CopyBankAccEntity
#define CopyBankAccEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->Currency=(source)->Currency;	\
			(target)->BankID=(source)->BankID;	\
			(target)->BankName=(source)->BankName;	\
			(target)->BankAccount=(source)->BankAccount;	\

#endif
#ifndef CopyBFTransferInterfaceEntity
#define CopyBFTransferInterfaceEntity(target,source)	\
			(target)->APIID=(source)->APIID;	\
			(target)->FrontID=(source)->FrontID;	\
			(target)->RequestID=(source)->RequestID;	\
			(target)->InstallID=(source)->InstallID;	\
			CopyTransferSerialEntity(target,source);	\

#endif
#ifndef CopyTransferSerialEntity
#define CopyTransferSerialEntity(target,source)	\
			(target)->PlateSerial=(source)->PlateSerial;	\
			(target)->TradeDate=(source)->TradeDate;	\
			(target)->TradingDay=(source)->TradingDay;	\
			(target)->TradingTime=(source)->TradingTime;	\
			(target)->TradeCode=(source)->TradeCode;	\
			(target)->SessionID=(source)->SessionID;	\
			(target)->BankID=(source)->BankID;	\
			(target)->BankBrchID=(source)->BankBrchID;	\
			(target)->BankAccType=(source)->BankAccType;	\
			(target)->BankAccount=(source)->BankAccount;	\
			(target)->Currency=(source)->Currency;	\
			(target)->BankSerial=(source)->BankSerial;	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->BrokerBranchID=(source)->BrokerBranchID;	\
			(target)->FutureAccType=(source)->FutureAccType;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->FutureSerial=(source)->FutureSerial;	\
			(target)->IdCardType=(source)->IdCardType;	\
			(target)->IdentifiedCardNo=(source)->IdentifiedCardNo;	\
			(target)->TradeAmount=(source)->TradeAmount;	\
			(target)->CustFee=(source)->CustFee;	\
			(target)->BrokerFee=(source)->BrokerFee;	\
			(target)->AvailabilityFlag=(source)->AvailabilityFlag;	\
			(target)->OperatorCode=(source)->OperatorCode;	\
			(target)->BankNewAccount=(source)->BankNewAccount;	\
			CopyErrorTypeEntity(target,source);	\

#endif
#ifndef CopyUserEntity
#define CopyUserEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->Password=(source)->Password;	\
			(target)->IsActive=(source)->IsActive;	\
			(target)->UserName=(source)->UserName;	\
			(target)->UserType=(source)->UserType;	\
			(target)->Department=(source)->Department;	\
			(target)->GrantFuncSet=(source)->GrantFuncSet;	\
			(target)->CheckIpMacAddr=(source)->CheckIpMacAddr;	\

#endif
#ifndef CopyAPIUserInvestorEntity
#define CopyAPIUserInvestorEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->InvestorID=(source)->InvestorID;	\

#endif
#ifndef CopyUserInvestorEntity
#define CopyUserInvestorEntity(target,source)	\
			CopyAPIUserInvestorEntity(target,source);	\
			(target)->GrantFuncSet=(source)->GrantFuncSet;	\

#endif
#ifndef CopyUserTradingRightEntity
#define CopyUserTradingRightEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->TradingRight=(source)->TradingRight;	\

#endif
#ifndef CopyUserFunctionRightEntity
#define CopyUserFunctionRightEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->GrantFuncSet=(source)->GrantFuncSet;	\

#endif
#ifndef CopyDataSyncStatusEntity
#define CopyDataSyncStatusEntity(target,source)	\
			(target)->TradingDay=(source)->TradingDay;	\
			(target)->DataSyncStatus=(source)->DataSyncStatus;	\
			(target)->SystemID=(source)->SystemID;	\

#endif
#ifndef CopyTBCommandEntity
#define CopyTBCommandEntity(target,source)	\
			(target)->CommandNo=(source)->CommandNo;	\
			(target)->CommandDate=(source)->CommandDate;	\
			(target)->CommandTime=(source)->CommandTime;	\
			(target)->CommandType=(source)->CommandType;	\
			(target)->FieldName=(source)->FieldName;	\
			(target)->FieldContent=(source)->FieldContent;	\

#endif
#ifndef CopyAPIInstrumentEntity
#define CopyAPIInstrumentEntity(target,source)	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->ProductID=(source)->ProductID;	\
			(target)->ProductName=(source)->ProductName;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->InstrumentName=(source)->InstrumentName;	\
			(target)->DeliveryYear=(source)->DeliveryYear;	\
			(target)->DeliveryMonth=(source)->DeliveryMonth;	\
			(target)->MaxLimitOrderVolume=(source)->MaxLimitOrderVolume;	\
			(target)->MinLimitOrderVolume=(source)->MinLimitOrderVolume;	\
			(target)->MaxMarketOrderVolume=(source)->MaxMarketOrderVolume;	\
			(target)->MinMarketOrderVolume=(source)->MinMarketOrderVolume;	\
			(target)->VolumeMultiple=(source)->VolumeMultiple;	\
			(target)->PriceTick=(source)->PriceTick;	\
			(target)->Currency=(source)->Currency;	\
			(target)->LongPosLimit=(source)->LongPosLimit;	\
			(target)->ShortPosLimit=(source)->ShortPosLimit;	\
			(target)->LowerLimitPrice=(source)->LowerLimitPrice;	\
			(target)->UpperLimitPrice=(source)->UpperLimitPrice;	\
			(target)->PreSettlementPrice=(source)->PreSettlementPrice;	\
			(target)->InstrumentStatus=(source)->InstrumentStatus;	\
			(target)->CreateDate=(source)->CreateDate;	\
			(target)->OpenDate=(source)->OpenDate;	\
			(target)->ExpireDate=(source)->ExpireDate;	\
			(target)->StartDelivDate=(source)->StartDelivDate;	\
			(target)->EndDelivDate=(source)->EndDelivDate;	\
			(target)->BasisPrice=(source)->BasisPrice;	\
			(target)->IsTrading=(source)->IsTrading;	\
			(target)->UnderlyingInstrID=(source)->UnderlyingInstrID;	\
			(target)->UnderlyingMultiple=(source)->UnderlyingMultiple;	\
			(target)->PositionType=(source)->PositionType;	\
			(target)->StrikePrice=(source)->StrikePrice;	\
			(target)->OptionsType=(source)->OptionsType;	\
			(target)->ProductClass=(source)->ProductClass;	\
			(target)->OptionsMode=(source)->OptionsMode;	\

#endif
#ifndef CopyInstrumentEntity
#define CopyInstrumentEntity(target,source)	\
			CopyAPIInstrumentEntity(target,source);	\
			(target)->ProductGroupID=(source)->ProductGroupID;	\
			(target)->APIID=(source)->APIID;	\
			(target)->LegQty=(source)->LegQty;	\

#endif
#ifndef CopyCmbInstrumentDetailEntity
#define CopyCmbInstrumentDetailEntity(target,source)	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->ArbiInstrumentID=(source)->ArbiInstrumentID;	\
			(target)->SingleInstrumentID=(source)->SingleInstrumentID;	\
			(target)->LegNo=(source)->LegNo;	\
			(target)->Direction=(source)->Direction;	\
			(target)->Ratio=(source)->Ratio;	\

#endif
#ifndef CopyInstrumentStatusEntity
#define CopyInstrumentStatusEntity(target,source)	\
			CopyInstrumentEntity(target,source);	\

#endif
#ifndef CopyAPIExchangeEntity
#define CopyAPIExchangeEntity(target,source)	\
			CopyTradingDayEntity(target,source);	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->ExchangeName=(source)->ExchangeName;	\

#endif
#ifndef CopyExchangeEntity
#define CopyExchangeEntity(target,source)	\
			CopyAPIExchangeEntity(target,source);	\

#endif
#ifndef CopySystemStatusEntity
#define CopySystemStatusEntity(target,source)	\
			(target)->TradingDay=(source)->TradingDay;	\
			(target)->SystemStatus=(source)->SystemStatus;	\

#endif
#ifndef CopyExchTimeDiffEntity
#define CopyExchTimeDiffEntity(target,source)	\
			(target)->TradingDay=(source)->TradingDay;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->LoginTime=(source)->LoginTime;	\
			(target)->LocalTime=(source)->LocalTime;	\
			(target)->DiffSnd=(source)->DiffSnd;	\

#endif
#ifndef CopyAPIInputOrderEntity
#define CopyAPIInputOrderEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->OrderSysID=(source)->OrderSysID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->UserOrderLocalID=(source)->UserOrderLocalID;	\
			(target)->OrderPriceType=(source)->OrderPriceType;	\
			(target)->Direction=(source)->Direction;	\
			(target)->OffsetFlag=(source)->OffsetFlag;	\
			(target)->HedgeFlag=(source)->HedgeFlag;	\
			(target)->LimitPrice=(source)->LimitPrice;	\
			(target)->Volume=(source)->Volume;	\
			(target)->TimeCondition=(source)->TimeCondition;	\
			(target)->GTDDate=(source)->GTDDate;	\
			(target)->VolumeCondition=(source)->VolumeCondition;	\
			(target)->MinVolume=(source)->MinVolume;	\
			(target)->StopPrice=(source)->StopPrice;	\
			(target)->ForceCloseReason=(source)->ForceCloseReason;	\
			(target)->IsAutoSuspend=(source)->IsAutoSuspend;	\
			(target)->BusinessUnit=(source)->BusinessUnit;	\
			(target)->UserCustom=(source)->UserCustom;	\
			(target)->BranchID=(source)->BranchID;	\
			(target)->RecNum=(source)->RecNum;	\
			(target)->BusinessType=(source)->BusinessType;	\

#endif
#ifndef CopyInnerBaseOrderEntity
#define CopyInnerBaseOrderEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->UserOrderLocalID=(source)->UserOrderLocalID;	\
			(target)->UserCustom=(source)->UserCustom;	\

#endif
#ifndef CopyInnerAPIOrderEntity
#define CopyInnerAPIOrderEntity(target,source)	\
			CopyTradingDayEntity(target,source);	\
			(target)->ParticipantID=(source)->ParticipantID;	\
			(target)->ClientID=(source)->ClientID;	\
			(target)->SeatID=(source)->SeatID;	\
			(target)->InsertTime=(source)->InsertTime;	\
			(target)->OrderLocalID=(source)->OrderLocalID;	\
			(target)->OrderSource=(source)->OrderSource;	\
			(target)->OrderStatus=(source)->OrderStatus;	\
			(target)->CancelTime=(source)->CancelTime;	\
			(target)->CancelUserID=(source)->CancelUserID;	\
			(target)->VolumeTraded=(source)->VolumeTraded;	\
			(target)->VolumeRemain=(source)->VolumeRemain;	\
			(target)->FrontID=(source)->FrontID;	\
			(target)->SessionID=(source)->SessionID;	\

#endif
#ifndef CopyInnerAPIOrder2Entity
#define CopyInnerAPIOrder2Entity(target,source)	\
			(target)->FrozenFee=(source)->FrozenFee;	\
			(target)->FrozenMargin=(source)->FrozenMargin;	\
			(target)->FrozenPremium=(source)->FrozenPremium;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->OrderUserID=(source)->OrderUserID;	\
			(target)->TradeType=(source)->TradeType;	\
			(target)->DealFlag=(source)->DealFlag;	\
			(target)->TradeCommision=(source)->TradeCommision;	\
			(target)->TradeAmnt=(source)->TradeAmnt;	\
			(target)->CancleVolume=(source)->CancleVolume;	\
			(target)->RequestID=(source)->RequestID;	\
			(target)->APIID=(source)->APIID;	\
			(target)->IPAddress=(source)->IPAddress;	\
			(target)->MacAddress=(source)->MacAddress;	\

#endif
#ifndef CopyAPIOrderEntity
#define CopyAPIOrderEntity(target,source)	\
			CopyAPIInputOrderEntity(target,source);	\
			CopyInnerAPIOrderEntity(target,source);	\

#endif
#ifndef CopyOrderEntity
#define CopyOrderEntity(target,source)	\
			CopyAPIOrderEntity(target,source);	\
			CopyInnerAPIOrder2Entity(target,source);	\
			(target)->FTdRecvDown=(source)->FTdRecvDown;	\
			(target)->CoreRecvDown=(source)->CoreRecvDown;	\
			(target)->CoreSendUp=(source)->CoreSendUp;	\
			(target)->CoreRecvUp=(source)->CoreRecvUp;	\
			(target)->CoreSendDown=(source)->CoreSendDown;	\
			(target)->FTdSendDown=(source)->FTdSendDown;	\
			(target)->MarginCombType=(source)->MarginCombType;	\
			(target)->InstrumentGroupID=(source)->InstrumentGroupID;	\

#endif
#ifndef CopyPreOrderEntity
#define CopyPreOrderEntity(target,source)	\
			CopyOrderEntity(target,source);	\

#endif
#ifndef CopyIndexPreOrderEntity
#define CopyIndexPreOrderEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->HedgeFlag=(source)->HedgeFlag;	\
			(target)->Direction=(source)->Direction;	\
			(target)->APIID=(source)->APIID;	\
			(target)->ClientID=(source)->ClientID;	\
			(target)->MarginCombType=(source)->MarginCombType;	\
			(target)->InstrumentGroupID=(source)->InstrumentGroupID;	\

#endif
#ifndef CopyInputOrderEntity
#define CopyInputOrderEntity(target,source)	\
			CopyOrderEntity(target,source);	\

#endif
#ifndef CopyAPIOrderActionEntity
#define CopyAPIOrderActionEntity(target,source)	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->OrderSysID=(source)->OrderSysID;	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->UserOrderActionLocalID=(source)->UserOrderActionLocalID;	\
			(target)->UserOrderLocalID=(source)->UserOrderLocalID;	\
			(target)->ActionFlag=(source)->ActionFlag;	\
			(target)->LimitPrice=(source)->LimitPrice;	\
			(target)->VolumeChange=(source)->VolumeChange;	\
			(target)->RecNum=(source)->RecNum;	\
			(target)->FrontID=(source)->FrontID;	\
			(target)->SessionID=(source)->SessionID;	\

#endif
#ifndef CopyOrderActionEntity
#define CopyOrderActionEntity(target,source)	\
			CopyAPIOrderActionEntity(target,source);	\
			(target)->UserCustom=(source)->UserCustom;	\
			(target)->SeatID=(source)->SeatID;	\
			(target)->ActionLocalID=(source)->ActionLocalID;	\
			(target)->ClientID=(source)->ClientID;	\
			(target)->ParticipantID=(source)->ParticipantID;	\
			(target)->CancelTime=(source)->CancelTime;	\
			(target)->ActionSource=(source)->ActionSource;	\
			(target)->Tradable=(source)->Tradable;	\
			(target)->OrderLocalID=(source)->OrderLocalID;	\
			(target)->IsForgeRtn=(source)->IsForgeRtn;	\
			(target)->APIID=(source)->APIID;	\
			(target)->IPAddress=(source)->IPAddress;	\
			(target)->MacAddress=(source)->MacAddress;	\
			(target)->OrderActionType=(source)->OrderActionType;	\
			(target)->OrderBatchNo=(source)->OrderBatchNo;	\

#endif
#ifndef CopyOrderInsertFailedEntity
#define CopyOrderInsertFailedEntity(target,source)	\
			CopyOrderEntity(target,source);	\
			(target)->ErrorMsg=(source)->ErrorMsg;	\

#endif
#ifndef CopyAPITradeEntity
#define CopyAPITradeEntity(target,source)	\
			CopyTradingDayEntity(target,source);	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->ParticipantID=(source)->ParticipantID;	\
			(target)->SeatID=(source)->SeatID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->ClientID=(source)->ClientID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->TradeID=(source)->TradeID;	\
			(target)->OrderSysID=(source)->OrderSysID;	\
			(target)->UserOrderLocalID=(source)->UserOrderLocalID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->Direction=(source)->Direction;	\
			(target)->OffsetFlag=(source)->OffsetFlag;	\
			(target)->HedgeFlag=(source)->HedgeFlag;	\
			(target)->TradePrice=(source)->TradePrice;	\
			(target)->TradeVolume=(source)->TradeVolume;	\
			(target)->TradeTime=(source)->TradeTime;	\
			(target)->ClearingPartID=(source)->ClearingPartID;	\
			(target)->TradeAmnt=(source)->TradeAmnt;	\
			(target)->RecNum=(source)->RecNum;	\
			(target)->TradeType=(source)->TradeType;	\

#endif
#ifndef CopyTradeEntity
#define CopyTradeEntity(target,source)	\
			CopyAPITradeEntity(target,source);	\
			(target)->Commision=(source)->Commision;	\
			(target)->StampTax=(source)->StampTax;	\
			(target)->TransferFee=(source)->TransferFee;	\
			(target)->UsedFee=(source)->UsedFee;	\
			(target)->UsedMargin=(source)->UsedMargin;	\
			(target)->Premium=(source)->Premium;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->OrderUserID=(source)->OrderUserID;	\
			(target)->OrderLocalID=(source)->OrderLocalID;	\
			(target)->IsForgeRtn=(source)->IsForgeRtn;	\
			(target)->BusinessType=(source)->BusinessType;	\

#endif
#ifndef CopyQryMarketDataEntity
#define CopyQryMarketDataEntity(target,source)	\
			CopyAPIQryMarketDataEntity(target,source);	\

#endif
#ifndef CopyTradingDayEntity
#define CopyTradingDayEntity(target,source)	\
			(target)->TradingDay=(source)->TradingDay;	\

#endif
#ifndef CopyMarketDataEntity
#define CopyMarketDataEntity(target,source)	\
			CopyTradingDayEntity(target,source);	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->OpenPrice=(source)->OpenPrice;	\
			(target)->HighestPrice=(source)->HighestPrice;	\
			(target)->LowestPrice=(source)->LowestPrice;	\
			(target)->LastPrice=(source)->LastPrice;	\
			(target)->Volume=(source)->Volume;	\
			(target)->Turnover=(source)->Turnover;	\
			(target)->LowerLimitPrice=(source)->LowerLimitPrice;	\
			(target)->UpperLimitPrice=(source)->UpperLimitPrice;	\
			(target)->OpenInterest=(source)->OpenInterest;	\
			(target)->PreClosePrice=(source)->PreClosePrice;	\
			(target)->PreOpenInterest=(source)->PreOpenInterest;	\
			(target)->PreSettlementPrice=(source)->PreSettlementPrice;	\
			(target)->SettlementPrice=(source)->SettlementPrice;	\
			(target)->UpdateMillisec=(source)->UpdateMillisec;	\
			(target)->UpdateTime=(source)->UpdateTime;	\

#endif
#ifndef CopyMemtableChangeEntity
#define CopyMemtableChangeEntity(target,source)	\
			(target)->MemtableChangeType=(source)->MemtableChangeType;	\
			(target)->MemTableName=(source)->MemTableName;	\

#endif
#ifndef CopyTmdbAccomplishEntity
#define CopyTmdbAccomplishEntity(target,source)	\
			(target)->CommPhaseNo=(source)->CommPhaseNo;	\
			(target)->SequenceNo=(source)->SequenceNo;	\

#endif
#ifndef CopyDbmtRefEntity
#define CopyDbmtRefEntity(target,source)	\
			(target)->DbmtTopicID=(source)->DbmtTopicID;	\
			(target)->DbmtSequenceID=(source)->DbmtSequenceID;	\

#endif
#ifndef CopyDbmtUserEntity
#define CopyDbmtUserEntity(target,source)	\
			CopyUserEntity(target,source);	\
			CopyDbmtRefEntity(target,source);	\

#endif
#ifndef CopyDbmtInvestorAccountDepositEntity
#define CopyDbmtInvestorAccountDepositEntity(target,source)	\
			CopyInvestorAccountDepositEntity(target,source);	\
			CopyDbmtRefEntity(target,source);	\

#endif
#ifndef CopyDbmtClientTradingIDEntity
#define CopyDbmtClientTradingIDEntity(target,source)	\
			CopyClientTradingIDEntity(target,source);	\
			CopyDbmtRefEntity(target,source);	\

#endif
#ifndef CopyErrorTypeEntity
#define CopyErrorTypeEntity(target,source)	\
			(target)->ErrorID=(source)->ErrorID;	\
			(target)->ErrorMsg=(source)->ErrorMsg;	\

#endif
#ifndef CopyAPIUserLogoutEntity
#define CopyAPIUserLogoutEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->LogoutReason=(source)->LogoutReason;	\

#endif
#ifndef CopyUserLogoutEntity
#define CopyUserLogoutEntity(target,source)	\
			CopyAPIUserLogoutEntity(target,source);	\
			(target)->FrontID=(source)->FrontID;	\
			(target)->SessionID=(source)->SessionID;	\

#endif
#ifndef CopyUserPasswordUpdateEntity
#define CopyUserPasswordUpdateEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->OldPassword=(source)->OldPassword;	\
			(target)->NewPassword=(source)->NewPassword;	\

#endif
#ifndef CopyLoginRspEntity
#define CopyLoginRspEntity(target,source)	\
			(target)->TradingDay=(source)->TradingDay;	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->LoginTime=(source)->LoginTime;	\
			(target)->MaxOrderLocalID=(source)->MaxOrderLocalID;	\
			(target)->TradingSystemName=(source)->TradingSystemName;	\
			(target)->DataCenterID=(source)->DataCenterID;	\
			(target)->PrivateFlowSize=(source)->PrivateFlowSize;	\
			(target)->UserFlowSize=(source)->UserFlowSize;	\
			(target)->SessionID=(source)->SessionID;	\
			(target)->FrontID=(source)->FrontID;	\

#endif
#ifndef CopyLoginFullEntity
#define CopyLoginFullEntity(target,source)	\
			CopyLoginBaseEntity(target,source);	\
			CopyLoginExtraEntity(target,source);	\

#endif
#ifndef CopyLoginBaseEntity
#define CopyLoginBaseEntity(target,source)	\
			(target)->TradingDay=(source)->TradingDay;	\
			(target)->UserID=(source)->UserID;	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->Password=(source)->Password;	\
			(target)->UserProductInfo=(source)->UserProductInfo;	\
			(target)->InterfaceProductInfo=(source)->InterfaceProductInfo;	\
			(target)->ProtocolInfo=(source)->ProtocolInfo;	\
			(target)->IPAddress=(source)->IPAddress;	\
			(target)->MacAddress=(source)->MacAddress;	\
			(target)->DataCenterID=(source)->DataCenterID;	\
			(target)->OneTimePassword=(source)->OneTimePassword;	\
			(target)->ClientIPAddress=(source)->ClientIPAddress;	\

#endif
#ifndef CopyLoginExtraEntity
#define CopyLoginExtraEntity(target,source)	\
			(target)->LoginTime=(source)->LoginTime;	\
			(target)->MaxOrderLocalID=(source)->MaxOrderLocalID;	\
			(target)->TradingSystemName=(source)->TradingSystemName;	\
			(target)->UserType=(source)->UserType;	\
			(target)->MaxCommFlux=(source)->MaxCommFlux;	\
			(target)->SessionID=(source)->SessionID;	\
			(target)->FrontID=(source)->FrontID;	\
			(target)->SockID=(source)->SockID;	\
			(target)->ClientTradingDay=(source)->ClientTradingDay;	\
			(target)->Heartbeat=(source)->Heartbeat;	\
			(target)->DialogSeqno=(source)->DialogSeqno;	\
			(target)->PrivateSeqno=(source)->PrivateSeqno;	\
			(target)->PublicSeqno=(source)->PublicSeqno;	\
			(target)->LifeCycleID=(source)->LifeCycleID;	\

#endif
#ifndef CopyLoginInfoEntity
#define CopyLoginInfoEntity(target,source)	\
			(target)->ParticipantID=(source)->ParticipantID;	\
			(target)->SeatID=(source)->SeatID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->OrderLocalID=(source)->OrderLocalID;	\
			(target)->LifeCycleID=(source)->LifeCycleID;	\

#endif
#ifndef CopyCommPhaseEntity
#define CopyCommPhaseEntity(target,source)	\
			(target)->TradingDay=(source)->TradingDay;	\
			(target)->CommPhaseNo=(source)->CommPhaseNo;	\

#endif
#ifndef CopyExchangeTradingDayEntity
#define CopyExchangeTradingDayEntity(target,source)	\
			CopyTradingDayEntity(target,source);	\
			(target)->ExchangeID=(source)->ExchangeID;	\

#endif
#ifndef CopyCurrentTimeEntity
#define CopyCurrentTimeEntity(target,source)	\
			(target)->CurrDate=(source)->CurrDate;	\
			(target)->CurrTime=(source)->CurrTime;	\
			(target)->CurrMillisec=(source)->CurrMillisec;	\

#endif
#ifndef CopyForceUserExitEntity
#define CopyForceUserExitEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\

#endif
#ifndef CopyUserSessionEntity
#define CopyUserSessionEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->UserType=(source)->UserType;	\
			(target)->SessionID=(source)->SessionID;	\
			(target)->FrontID=(source)->FrontID;	\
			(target)->LoginTime=(source)->LoginTime;	\
			(target)->IPAddress=(source)->IPAddress;	\
			(target)->MacAddress=(source)->MacAddress;	\
			(target)->UserProductInfo=(source)->UserProductInfo;	\
			(target)->InterfaceProductInfo=(source)->InterfaceProductInfo;	\
			(target)->ProtocolInfo=(source)->ProtocolInfo;	\

#endif
#ifndef CopyMemDbEntity
#define CopyMemDbEntity(target,source)	\
			(target)->MemTableName=(source)->MemTableName;	\

#endif
#ifndef CopyInitMGateWayEntity
#define CopyInitMGateWayEntity(target,source)	\
			(target)->APIID=(source)->APIID;	\
			(target)->ExSvrType=(source)->ExSvrType;	\

#endif
#ifndef CopyCurrentTradeTimeEntity
#define CopyCurrentTradeTimeEntity(target,source)	\
			CopyCurrentTimeEntity(target,source);	\
			(target)->OldTime=(source)->OldTime;	\
			(target)->OldMillisec=(source)->OldMillisec;	\

#endif
#ifndef CopyMoneyEntity
#define CopyMoneyEntity(target,source)	\
			(target)->Margin=(source)->Margin;	\
			(target)->Fee=(source)->Fee;	\
			(target)->Premium=(source)->Premium;	\
			(target)->MarginChanged=(source)->MarginChanged;	\
			(target)->FrozenMarginChanged=(source)->FrozenMarginChanged;	\
			(target)->UsedMargin=(source)->UsedMargin;	\

#endif
#ifndef CopyMaxLocalIDEntity
#define CopyMaxLocalIDEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->MaxOrderLocalID=(source)->MaxOrderLocalID;	\
			(target)->FrontID=(source)->FrontID;	\
			(target)->SessionID=(source)->SessionID;	\

#endif
#ifndef CopyBrkUseridLocalIDEntity
#define CopyBrkUseridLocalIDEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->UserOrderLocalID=(source)->UserOrderLocalID;	\
			(target)->APIID=(source)->APIID;	\
			(target)->OrderLocalID=(source)->OrderLocalID;	\

#endif
#ifndef CopyAPIQryUserEntity
#define CopyAPIQryUserEntity(target,source)	\
			(target)->StartUserID=(source)->StartUserID;	\
			(target)->EndUserID=(source)->EndUserID;	\

#endif
#ifndef CopyAPIQryInvestorEntity
#define CopyAPIQryInvestorEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->InvestorID=(source)->InvestorID;	\

#endif
#ifndef CopyQryInvestorEntity
#define CopyQryInvestorEntity(target,source)	\
			CopyAPIQryInvestorEntity(target,source);	\
			CopyLoginUserEntity(target,source);	\

#endif
#ifndef CopyAPIQryInvestorAccountEntity
#define CopyAPIQryInvestorAccountEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->InvestorID=(source)->InvestorID;	\

#endif
#ifndef CopyQryInvestorAccountEntity
#define CopyQryInvestorAccountEntity(target,source)	\
			CopyAPIQryInvestorAccountEntity(target,source);	\
			CopyLoginUserEntity(target,source);	\
			(target)->SeatID=(source)->SeatID;	\

#endif
#ifndef CopyAPIQryClientTradingIDEntity
#define CopyAPIQryClientTradingIDEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\

#endif
#ifndef CopyQryClientTradingIDEntity
#define CopyQryClientTradingIDEntity(target,source)	\
			CopyAPIQryClientTradingIDEntity(target,source);	\
			CopyLoginUserEntity(target,source);	\

#endif
#ifndef CopyAPIQryOrderEntity
#define CopyAPIQryOrderEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->OrderSysID=(source)->OrderSysID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\

#endif
#ifndef CopyQryOrderEntity
#define CopyQryOrderEntity(target,source)	\
			CopyAPIQryOrderEntity(target,source);	\
			CopyLoginUserEntity(target,source);	\

#endif
#ifndef CopyAPIQryTradeEntity
#define CopyAPIQryTradeEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->TradeID=(source)->TradeID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\

#endif
#ifndef CopyQryTradeEntity
#define CopyQryTradeEntity(target,source)	\
			CopyAPIQryTradeEntity(target,source);	\
			CopyLoginUserEntity(target,source);	\

#endif
#ifndef CopyAPIQryExchangeEntity
#define CopyAPIQryExchangeEntity(target,source)	\
			(target)->ExchangeID=(source)->ExchangeID;	\

#endif
#ifndef CopyAPIQryInstrumentEntity
#define CopyAPIQryInstrumentEntity(target,source)	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->ProductID=(source)->ProductID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\

#endif
#ifndef CopyAPIQryMarketDataEntity
#define CopyAPIQryMarketDataEntity(target,source)	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\

#endif
#ifndef CopyAPIQryInvestorPositionEntity
#define CopyAPIQryInvestorPositionEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\

#endif
#ifndef CopyQryInvestorPositionEntity
#define CopyQryInvestorPositionEntity(target,source)	\
			CopyAPIQryInvestorPositionEntity(target,source);	\
			(target)->ClientID=(source)->ClientID;	\
			(target)->SeatID=(source)->SeatID;	\
			CopyLoginUserEntity(target,source);	\

#endif
#ifndef CopyAPIQryUserInvestorEntity
#define CopyAPIQryUserInvestorEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\

#endif
#ifndef CopyQryUserInvestorEntity
#define CopyQryUserInvestorEntity(target,source)	\
			CopyAPIQryUserInvestorEntity(target,source);	\
			CopyLoginUserEntity(target,source);	\

#endif
#ifndef CopyAPIQryComplianceParamEntity
#define CopyAPIQryComplianceParamEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\

#endif
#ifndef CopyQryComplianceParamEntity
#define CopyQryComplianceParamEntity(target,source)	\
			CopyAPIQryComplianceParamEntity(target,source);	\
			CopyLoginUserEntity(target,source);	\

#endif
#ifndef CopyAPIQryInvestorFeeEntity
#define CopyAPIQryInvestorFeeEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->HedgeFlag=(source)->HedgeFlag;	\

#endif
#ifndef CopyQryInvestorFeeEntity
#define CopyQryInvestorFeeEntity(target,source)	\
			CopyAPIQryInvestorFeeEntity(target,source);	\
			CopyLoginUserEntity(target,source);	\

#endif
#ifndef CopyAPIQryInvestorMarginEntity
#define CopyAPIQryInvestorMarginEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->HedgeFlag=(source)->HedgeFlag;	\

#endif
#ifndef CopyQryInvestorMarginEntity
#define CopyQryInvestorMarginEntity(target,source)	\
			CopyAPIQryInvestorMarginEntity(target,source);	\
			CopyLoginUserEntity(target,source);	\

#endif
#ifndef CopyAPIQryExchangeDiffTimeEntity
#define CopyAPIQryExchangeDiffTimeEntity(target,source)	\
			(target)->ExchangeID=(source)->ExchangeID;	\

#endif
#ifndef CopyAPIExchangeDiffTimeEntity
#define CopyAPIExchangeDiffTimeEntity(target,source)	\
			CopyTradingDayEntity(target,source);	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->ExchangeTime=(source)->ExchangeTime;	\
			(target)->DiffSnd=(source)->DiffSnd;	\

#endif
#ifndef CopyAPIQryContractBankEntity
#define CopyAPIQryContractBankEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->Currency=(source)->Currency;	\
			(target)->BankID=(source)->BankID;	\
			(target)->BankBrchID=(source)->BankBrchID;	\

#endif
#ifndef CopyQryContractBankEntity
#define CopyQryContractBankEntity(target,source)	\
			CopyAPIQryContractBankEntity(target,source);	\
			CopyLoginUserEntity(target,source);	\

#endif
#ifndef CopyAPIContractBankEntity
#define CopyAPIContractBankEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->Currency=(source)->Currency;	\
			(target)->BankID=(source)->BankID;	\
			(target)->BankBrchID=(source)->BankBrchID;	\
			(target)->BankName=(source)->BankName;	\

#endif
#ifndef CopyQueryExBankAccountEntity
#define CopyQueryExBankAccountEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->UserPassword=(source)->UserPassword;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->Password=(source)->Password;	\
			(target)->Currency=(source)->Currency;	\

#endif
#ifndef CopyAPIReqQueryAccountEntity
#define CopyAPIReqQueryAccountEntity(target,source)	\
			(target)->TradeCode=(source)->TradeCode;	\
			(target)->BankID=(source)->BankID;	\
			(target)->BankBrchID=(source)->BankBrchID;	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->BrokerBranchID=(source)->BrokerBranchID;	\
			(target)->TradeDate=(source)->TradeDate;	\
			(target)->TradeTime=(source)->TradeTime;	\
			(target)->BankSerial=(source)->BankSerial;	\
			(target)->TradingDay=(source)->TradingDay;	\
			(target)->PlateSerial=(source)->PlateSerial;	\
			(target)->LastFragment=(source)->LastFragment;	\
			(target)->SessionID=(source)->SessionID;	\
			(target)->CustomerName=(source)->CustomerName;	\
			(target)->IdCardType=(source)->IdCardType;	\
			(target)->IdentifiedCardNo=(source)->IdentifiedCardNo;	\
			(target)->CustType=(source)->CustType;	\
			(target)->BankAccount=(source)->BankAccount;	\
			(target)->BankPassWord=(source)->BankPassWord;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->Password=(source)->Password;	\
			(target)->FutureSerial=(source)->FutureSerial;	\
			(target)->InstallID=(source)->InstallID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->VerifyCertNoFlag=(source)->VerifyCertNoFlag;	\
			(target)->Currency=(source)->Currency;	\
			(target)->Digest=(source)->Digest;	\
			(target)->BankAccType=(source)->BankAccType;	\
			(target)->DeviceID=(source)->DeviceID;	\
			(target)->BankSecuAccType=(source)->BankSecuAccType;	\
			(target)->BankCodingForFuture=(source)->BankCodingForFuture;	\
			(target)->BankSecuAcc=(source)->BankSecuAcc;	\
			(target)->BankPwdFlag=(source)->BankPwdFlag;	\
			(target)->SecuPwdFlag=(source)->SecuPwdFlag;	\
			(target)->OperNo=(source)->OperNo;	\
			(target)->RequestID=(source)->RequestID;	\
			(target)->TID=(source)->TID;	\

#endif
#ifndef CopyReqQueryAccountEntity
#define CopyReqQueryAccountEntity(target,source)	\
			CopyAPIReqQueryAccountEntity(target,source);	\
			CopyLoginUserEntity(target,source);	\

#endif
#ifndef CopyAPIReqTransferEntity
#define CopyAPIReqTransferEntity(target,source)	\
			(target)->TradeCode=(source)->TradeCode;	\
			(target)->BankID=(source)->BankID;	\
			(target)->BankBrchID=(source)->BankBrchID;	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->BrokerBranchID=(source)->BrokerBranchID;	\
			(target)->TradeDate=(source)->TradeDate;	\
			(target)->TradingTime=(source)->TradingTime;	\
			(target)->BankSerial=(source)->BankSerial;	\
			(target)->TradingDay=(source)->TradingDay;	\
			(target)->PlateSerial=(source)->PlateSerial;	\
			(target)->LastFragment=(source)->LastFragment;	\
			(target)->SessionID=(source)->SessionID;	\
			(target)->CustomerName=(source)->CustomerName;	\
			(target)->IdCardType=(source)->IdCardType;	\
			(target)->IdentifiedCardNo=(source)->IdentifiedCardNo;	\
			(target)->CustType=(source)->CustType;	\
			(target)->BankAccount=(source)->BankAccount;	\
			(target)->BankPassWord=(source)->BankPassWord;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->Password=(source)->Password;	\
			(target)->InstallID=(source)->InstallID;	\
			(target)->FutureSerial=(source)->FutureSerial;	\
			(target)->UserID=(source)->UserID;	\
			(target)->VerifyCertNoFlag=(source)->VerifyCertNoFlag;	\
			(target)->Currency=(source)->Currency;	\
			(target)->TradeAmount=(source)->TradeAmount;	\
			(target)->FutureFetchAmount=(source)->FutureFetchAmount;	\
			(target)->FeePayFlag=(source)->FeePayFlag;	\
			(target)->CustFee=(source)->CustFee;	\
			(target)->BrokerFee=(source)->BrokerFee;	\
			(target)->Message=(source)->Message;	\
			(target)->Digest=(source)->Digest;	\
			(target)->BankAccType=(source)->BankAccType;	\
			(target)->DeviceID=(source)->DeviceID;	\
			(target)->BankSecuAccType=(source)->BankSecuAccType;	\
			(target)->BankCodingForFuture=(source)->BankCodingForFuture;	\
			(target)->BankSecuAcc=(source)->BankSecuAcc;	\
			(target)->BankPwdFlag=(source)->BankPwdFlag;	\
			(target)->SecuPwdFlag=(source)->SecuPwdFlag;	\
			(target)->OperNo=(source)->OperNo;	\
			(target)->RequestID=(source)->RequestID;	\
			(target)->TID=(source)->TID;	\
			(target)->TransferStatus=(source)->TransferStatus;	\

#endif
#ifndef CopyReqTransferEntity
#define CopyReqTransferEntity(target,source)	\
			CopyAPIReqTransferEntity(target,source);	\
			CopyLoginUserEntity(target,source);	\

#endif
#ifndef CopyAPIQryTransferSerialEntity
#define CopyAPIQryTransferSerialEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->BankID=(source)->BankID;	\
			(target)->Currency=(source)->Currency;	\

#endif
#ifndef CopyQryTransferSerialEntity
#define CopyQryTransferSerialEntity(target,source)	\
			CopyAPIQryTransferSerialEntity(target,source);	\
			CopyLoginUserEntity(target,source);	\

#endif
#ifndef CopyAPITransferSerialEntity
#define CopyAPITransferSerialEntity(target,source)	\
			CopyTransferSerialEntity(target,source);	\

#endif
#ifndef CopyAPINotifyQueryAccountEntity
#define CopyAPINotifyQueryAccountEntity(target,source)	\
			CopyAPIReqQueryAccountEntity(target,source);	\
			(target)->BankUseAmount=(source)->BankUseAmount;	\
			(target)->BankFetchAmount=(source)->BankFetchAmount;	\
			CopyErrorTypeEntity(target,source);	\

#endif
#ifndef CopyAPIRspTransferEntity
#define CopyAPIRspTransferEntity(target,source)	\
			CopyAPIReqTransferEntity(target,source);	\
			CopyErrorTypeEntity(target,source);	\

#endif
#ifndef CopyLoginUserEntity
#define CopyLoginUserEntity(target,source)	\
			(target)->LogBrokerID=(source)->LogBrokerID;	\
			(target)->LogUserID=(source)->LogUserID;	\

#endif
#ifndef CopyMarketDataBaseEntity
#define CopyMarketDataBaseEntity(target,source)	\
			CopyTradingDayEntity(target,source);	\
			(target)->SettlementGroupID=(source)->SettlementGroupID;	\
			(target)->SettlementID=(source)->SettlementID;	\
			(target)->PreSettlementPrice=(source)->PreSettlementPrice;	\
			(target)->PreClosePrice=(source)->PreClosePrice;	\
			(target)->PreOpenInterest=(source)->PreOpenInterest;	\
			(target)->PreDelta=(source)->PreDelta;	\

#endif
#ifndef CopyMarketDataStaticEntity
#define CopyMarketDataStaticEntity(target,source)	\
			(target)->OpenPrice=(source)->OpenPrice;	\
			(target)->HighestPrice=(source)->HighestPrice;	\
			(target)->LowestPrice=(source)->LowestPrice;	\
			(target)->ClosePrice=(source)->ClosePrice;	\
			(target)->UpperLimitPrice=(source)->UpperLimitPrice;	\
			(target)->LowerLimitPrice=(source)->LowerLimitPrice;	\
			(target)->SettlementPrice=(source)->SettlementPrice;	\
			(target)->CurrDelta=(source)->CurrDelta;	\

#endif
#ifndef CopyMarketDataLastMatchEntity
#define CopyMarketDataLastMatchEntity(target,source)	\
			(target)->LastPrice=(source)->LastPrice;	\
			(target)->Volume=(source)->Volume;	\
			(target)->Turnover=(source)->Turnover;	\
			(target)->OpenInterest=(source)->OpenInterest;	\

#endif
#ifndef CopyMarketDataLastMatchUSKernelEntity
#define CopyMarketDataLastMatchUSKernelEntity(target,source)	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->LastPrice=(source)->LastPrice;	\
			(target)->Volume=(source)->Volume;	\

#endif
#ifndef CopyMarketDataBestPriceEntity
#define CopyMarketDataBestPriceEntity(target,source)	\
			(target)->BidPrice1=(source)->BidPrice1;	\
			(target)->BidVolume1=(source)->BidVolume1;	\
			(target)->AskPrice1=(source)->AskPrice1;	\
			(target)->AskVolume1=(source)->AskVolume1;	\

#endif
#ifndef CopyMarketDataBid23Entity
#define CopyMarketDataBid23Entity(target,source)	\
			(target)->BidPrice2=(source)->BidPrice2;	\
			(target)->BidVolume2=(source)->BidVolume2;	\
			(target)->BidPrice3=(source)->BidPrice3;	\
			(target)->BidVolume3=(source)->BidVolume3;	\

#endif
#ifndef CopyMarketDataAsk23Entity
#define CopyMarketDataAsk23Entity(target,source)	\
			(target)->AskPrice2=(source)->AskPrice2;	\
			(target)->AskVolume2=(source)->AskVolume2;	\
			(target)->AskPrice3=(source)->AskPrice3;	\
			(target)->AskVolume3=(source)->AskVolume3;	\

#endif
#ifndef CopyMarketDataBid45Entity
#define CopyMarketDataBid45Entity(target,source)	\
			(target)->BidPrice4=(source)->BidPrice4;	\
			(target)->BidVolume4=(source)->BidVolume4;	\
			(target)->BidPrice5=(source)->BidPrice5;	\
			(target)->BidVolume5=(source)->BidVolume5;	\

#endif
#ifndef CopyMarketDataAsk45Entity
#define CopyMarketDataAsk45Entity(target,source)	\
			(target)->AskPrice4=(source)->AskPrice4;	\
			(target)->AskVolume4=(source)->AskVolume4;	\
			(target)->AskPrice5=(source)->AskPrice5;	\
			(target)->AskVolume5=(source)->AskVolume5;	\

#endif
#ifndef CopyMarketDataUpdateTimeEntity
#define CopyMarketDataUpdateTimeEntity(target,source)	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->UpdateTime=(source)->UpdateTime;	\
			(target)->UpdateMillisec=(source)->UpdateMillisec;	\

#endif
#ifndef CopyMarketDataExchangeIDEntity
#define CopyMarketDataExchangeIDEntity(target,source)	\
			(target)->ExchangeID=(source)->ExchangeID;	\

#endif
#ifndef CopyMarketDataAsk67Entity
#define CopyMarketDataAsk67Entity(target,source)	\
			(target)->AskPrice6=(source)->AskPrice6;	\
			(target)->AskVolume6=(source)->AskVolume6;	\
			(target)->AskPrice7=(source)->AskPrice7;	\
			(target)->AskVolume7=(source)->AskVolume7;	\

#endif
#ifndef CopyMarketDataAsk89Entity
#define CopyMarketDataAsk89Entity(target,source)	\
			(target)->AskPrice8=(source)->AskPrice8;	\
			(target)->AskVolume8=(source)->AskVolume8;	\
			(target)->AskPrice9=(source)->AskPrice9;	\
			(target)->AskVolume9=(source)->AskVolume9;	\

#endif
#ifndef CopyMarketDataBid67Entity
#define CopyMarketDataBid67Entity(target,source)	\
			(target)->BidPrice6=(source)->BidPrice6;	\
			(target)->BidVolume6=(source)->BidVolume6;	\
			(target)->BidPrice7=(source)->BidPrice7;	\
			(target)->BidVolume7=(source)->BidVolume7;	\

#endif
#ifndef CopyMarketDataBid89Entity
#define CopyMarketDataBid89Entity(target,source)	\
			(target)->BidPrice8=(source)->BidPrice8;	\
			(target)->BidVolume8=(source)->BidVolume8;	\
			(target)->BidPrice9=(source)->BidPrice9;	\
			(target)->BidVolume9=(source)->BidVolume9;	\

#endif
#ifndef CopyMarketDataAskBid10Entity
#define CopyMarketDataAskBid10Entity(target,source)	\
			(target)->AskPrice10=(source)->AskPrice10;	\
			(target)->AskVolume10=(source)->AskVolume10;	\
			(target)->BidPrice10=(source)->BidPrice10;	\
			(target)->BidVolume10=(source)->BidVolume10;	\

#endif
#ifndef CopyRspMarketDataEntity
#define CopyRspMarketDataEntity(target,source)	\
			CopyMarketDataExchangeIDEntity(target,source);	\
			CopyMarketDataBaseEntity(target,source);	\
			CopyMarketDataStaticEntity(target,source);	\
			CopyMarketDataLastMatchEntity(target,source);	\
			CopyMarketDataBestPriceEntity(target,source);	\
			CopyMarketDataUpdateTimeEntity(target,source);	\

#endif
#ifndef CopyDepthMarketDataEntity
#define CopyDepthMarketDataEntity(target,source)	\
			CopyMarketDataBaseEntity(target,source);	\
			CopyMarketDataStaticEntity(target,source);	\
			CopyMarketDataLastMatchEntity(target,source);	\
			CopyMarketDataBestPriceEntity(target,source);	\
			CopyMarketDataBid23Entity(target,source);	\
			CopyMarketDataAsk23Entity(target,source);	\
			CopyMarketDataBid45Entity(target,source);	\
			CopyMarketDataAsk45Entity(target,source);	\
			CopyMarketDataUpdateTimeEntity(target,source);	\
			CopyMarketDataExchangeIDEntity(target,source);	\
			CopyMarketDataAsk67Entity(target,source);	\
			CopyMarketDataAsk89Entity(target,source);	\
			CopyMarketDataBid67Entity(target,source);	\
			CopyMarketDataBid89Entity(target,source);	\
			CopyMarketDataAskBid10Entity(target,source);	\

#endif
#ifndef CopySpecificInstrumentEntity
#define CopySpecificInstrumentEntity(target,source)	\
			(target)->InstrumentID=(source)->InstrumentID;	\

#endif
#ifndef CopyTopicSearchEntity
#define CopyTopicSearchEntity(target,source)	\
			(target)->TopicID=(source)->TopicID;	\

#endif
#ifndef CopyShmDepthMarketDataEntity
#define CopyShmDepthMarketDataEntity(target,source)	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->IPAddress=(source)->IPAddress;	\
			(target)->TopicID=(source)->TopicID;	\

#endif
#ifndef CopyClientMarginCombTypeEntity
#define CopyClientMarginCombTypeEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->ParticipantID=(source)->ParticipantID;	\
			(target)->ClientID=(source)->ClientID;	\
			(target)->InstrumentGroupID=(source)->InstrumentGroupID;	\
			(target)->MarginCombType=(source)->MarginCombType;	\

#endif
#ifndef CopyInstrumentGroupEntity
#define CopyInstrumentGroupEntity(target,source)	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->InstrumentGroupID=(source)->InstrumentGroupID;	\

#endif
#ifndef CopyPartClientInsGroupPositionEntity
#define CopyPartClientInsGroupPositionEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->ParticipantID=(source)->ParticipantID;	\
			(target)->ClientID=(source)->ClientID;	\
			(target)->InstrumentGroupID=(source)->InstrumentGroupID;	\
			(target)->LongPosition=(source)->LongPosition;	\
			(target)->LongMargin=(source)->LongMargin;	\
			(target)->ShortPosition=(source)->ShortPosition;	\
			(target)->ShortMargin=(source)->ShortMargin;	\
			(target)->ActualMargin =(source)->ActualMargin ;	\
			(target)->LongFrozenPosition=(source)->LongFrozenPosition;	\
			(target)->LongFrozenMargin=(source)->LongFrozenMargin;	\
			(target)->ShortFrozenPosition=(source)->ShortFrozenPosition;	\
			(target)->ShortFrozenMargin=(source)->ShortFrozenMargin;	\
			(target)->ActualFrozenMargin =(source)->ActualFrozenMargin ;	\

#endif
#ifndef CopyInterLoginInfoEntity
#define CopyInterLoginInfoEntity(target,source)	\
			(target)->ServerAddr=(source)->ServerAddr;	\
			(target)->MaxLocalID=(source)->MaxLocalID;	\

#endif
#ifndef CopyAPIMessageNotifyInfoEntity
#define CopyAPIMessageNotifyInfoEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->Nums=(source)->Nums;	\
			(target)->BusinessType=(source)->BusinessType;	\
			(target)->WarnMsg=(source)->WarnMsg;	\

#endif
#ifndef CopyMessageNotifyInfoEntity
#define CopyMessageNotifyInfoEntity(target,source)	\
			CopyAPIMessageNotifyInfoEntity(target,source);	\

#endif
#ifndef CopyQueryFinishNotifyEntity
#define CopyQueryFinishNotifyEntity(target,source)	\
			CopyExchangeTradingDayEntity(target,source);	\
			(target)->MaxOrderLocalID=(source)->MaxOrderLocalID;	\
			(target)->APIID=(source)->APIID;	\
			(target)->ApiLinkType=(source)->ApiLinkType;	\

#endif
#ifndef CopyInvestorLinkerEntity
#define CopyInvestorLinkerEntity(target,source)	\
			(target)->UserID=(source)->UserID;	\
			(target)->APIID=(source)->APIID;	\
			(target)->InvestorID=(source)->InvestorID;	\

#endif
#ifndef CopyAPIReqBankFutureTransEntity
#define CopyAPIReqBankFutureTransEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->BankID=(source)->BankID;	\
			(target)->BankAccount=(source)->BankAccount;	\
			(target)->Currency=(source)->Currency;	\
			(target)->Amount=(source)->Amount;	\
			(target)->AmountDirection=(source)->AmountDirection;	\
			(target)->AccountPwd=(source)->AccountPwd;	\
			(target)->BankPwd=(source)->BankPwd;	\

#endif
#ifndef CopyAPIBankFutureTransEntity
#define CopyAPIBankFutureTransEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->AccountID=(source)->AccountID;	\
			(target)->BankID=(source)->BankID;	\
			(target)->BankAccount=(source)->BankAccount;	\
			(target)->Currency=(source)->Currency;	\
			(target)->Amount=(source)->Amount;	\
			(target)->AmountDirection=(source)->AmountDirection;	\
			(target)->TransTime=(source)->TransTime;	\
			(target)->ProcStatus=(source)->ProcStatus;	\

#endif
#ifndef CopyAPIQryInvestorInventoryEntity
#define CopyAPIQryInvestorInventoryEntity(target,source)	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->ProductID=(source)->ProductID;	\

#endif
#ifndef CopyQryInvestorInventoryEntity
#define CopyQryInvestorInventoryEntity(target,source)	\
			CopyAPIQryInvestorInventoryEntity(target,source);	\
			(target)->LogBrokerID=(source)->LogBrokerID;	\
			(target)->LogUserID=(source)->LogUserID;	\

#endif
#ifndef CopyAPIInvestorInventoryEntity
#define CopyAPIInvestorInventoryEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->ProductID=(source)->ProductID;	\
			(target)->TotalInventory=(source)->TotalInventory;	\
			(target)->AvailInventory=(source)->AvailInventory;	\
			(target)->FrozenInventory=(source)->FrozenInventory;	\

#endif
#ifndef CopyInvestorInventoryEntity
#define CopyInvestorInventoryEntity(target,source)	\
			CopyAPIInvestorInventoryEntity(target,source);	\

#endif
#ifndef CopyInnerLoginEntity
#define CopyInnerLoginEntity(target,source)	\
			(target)->SequenceNo=(source)->SequenceNo;	\

#endif
#ifndef CopySGEDeferRateEntity
#define CopySGEDeferRateEntity(target,source)	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->TradeDate=(source)->TradeDate;	\
			(target)->Direction=(source)->Direction;	\
			(target)->DeferRate=(source)->DeferRate;	\

#endif
#ifndef CopyQrySGEDeferRateEntity
#define CopyQrySGEDeferRateEntity(target,source)	\
			(target)->InstrumentID=(source)->InstrumentID;	\

#endif
#ifndef CopyInvestorTradingRightEntity
#define CopyInvestorTradingRightEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->TradingRight=(source)->TradingRight;	\
			(target)->ProductClass=(source)->ProductClass;	\

#endif
#ifndef CopyDbmtInvestorTradingRightEntity
#define CopyDbmtInvestorTradingRightEntity(target,source)	\
			CopyInvestorTradingRightEntity(target,source);	\
			CopyDbmtRefEntity(target,source);	\

#endif
#ifndef CopyQmdInstrumentStateEntity
#define CopyQmdInstrumentStateEntity(target,source)	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->InstrumentStatus=(source)->InstrumentStatus;	\

#endif
#ifndef CopyUserIPEntity
#define CopyUserIPEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->IPAddress=(source)->IPAddress;	\
			(target)->IPMask=(source)->IPMask;	\
			(target)->MacAddress=(source)->MacAddress;	\

#endif
#ifndef CopyDbmtUserIPEntity
#define CopyDbmtUserIPEntity(target,source)	\
			CopyUserIPEntity(target,source);	\
			CopyDbmtRefEntity(target,source);	\

#endif
#ifndef CopyMBLMarketDataEntity
#define CopyMBLMarketDataEntity(target,source)	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->Direction=(source)->Direction;	\
			(target)->Price=(source)->Price;	\
			(target)->Volume=(source)->Volume;	\
			(target)->UpdateTime=(source)->UpdateTime;	\
			(target)->UpdateMillisec=(source)->UpdateMillisec;	\

#endif
#ifndef CopyQryMBLMarketDataEntity
#define CopyQryMBLMarketDataEntity(target,source)	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InstIDStart=(source)->InstIDStart;	\
			(target)->InstIDEnd=(source)->InstIDEnd;	\
			(target)->Direction=(source)->Direction;	\

#endif
#ifndef CopyEXMBLMarketDataEntity
#define CopyEXMBLMarketDataEntity(target,source)	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InstIDStart=(source)->InstIDStart;	\
			(target)->InstIDEnd=(source)->InstIDEnd;	\
			(target)->Direction=(source)->Direction;	\
			(target)->LogBrokerID=(source)->LogBrokerID;	\
			(target)->LogUserID=(source)->LogUserID;	\

#endif
#ifndef CopyInvestorMarginCombTypeEntity
#define CopyInvestorMarginCombTypeEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->InstrumentGroupID=(source)->InstrumentGroupID;	\
			(target)->MarginCombType=(source)->MarginCombType;	\

#endif
#ifndef CopyLegPositionEntity
#define CopyLegPositionEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->HedgeFlag=(source)->HedgeFlag;	\
			(target)->LongCombPosition=(source)->LongCombPosition;	\
			(target)->LongLegPosition=(source)->LongLegPosition;	\
			(target)->LongLegMargin=(source)->LongLegMargin;	\
			(target)->LongLegFrozenMargin=(source)->LongLegFrozenMargin;	\
			(target)->ShortCombPosition=(source)->ShortCombPosition;	\
			(target)->ShortLegPosition=(source)->ShortLegPosition;	\
			(target)->ShortLegMargin=(source)->ShortLegMargin;	\
			(target)->ShortLegFrozenMargin=(source)->ShortLegFrozenMargin;	\
			(target)->ActualMargin=(source)->ActualMargin;	\
			(target)->ActualFrozenMargin=(source)->ActualFrozenMargin;	\

#endif
#ifndef CopyCombPositionLegDetailEntity
#define CopyCombPositionLegDetailEntity(target,source)	\
			(target)->RecId=(source)->RecId;	\
			(target)->TradingDay=(source)->TradingDay;	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->CombInstrumentID=(source)->CombInstrumentID;	\
			(target)->UsedMargin=(source)->UsedMargin;	\
			(target)->HedgeFlag=(source)->HedgeFlag;	\
			(target)->Position=(source)->Position;	\
			(target)->Leg1InstrumentID=(source)->Leg1InstrumentID;	\
			(target)->Leg1Margin=(source)->Leg1Margin;	\
			(target)->Leg1Direction=(source)->Leg1Direction;	\
			(target)->Leg1Position=(source)->Leg1Position;	\
			(target)->Leg2InstrumentID=(source)->Leg2InstrumentID;	\
			(target)->Leg2Margin=(source)->Leg2Margin;	\
			(target)->Leg2Direction=(source)->Leg2Direction;	\
			(target)->Leg2Position=(source)->Leg2Position;	\
			(target)->Leg3InstrumentID=(source)->Leg3InstrumentID;	\
			(target)->Leg3Margin=(source)->Leg3Margin;	\
			(target)->Leg3Direction=(source)->Leg3Direction;	\
			(target)->Leg3Position=(source)->Leg3Position;	\

#endif
#ifndef CopyCmbPosiLgDtlIndexEntity
#define CopyCmbPosiLgDtlIndexEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->HedgeFlag=(source)->HedgeFlag;	\
			(target)->Direction=(source)->Direction;	\
			(target)->RecId=(source)->RecId;	\

#endif
#ifndef CopyAPIQryInvestorPositionDetailEntity
#define CopyAPIQryInvestorPositionDetailEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\

#endif
#ifndef CopyQryInvestorPositionDetailEntity
#define CopyQryInvestorPositionDetailEntity(target,source)	\
			CopyAPIQryInvestorPositionDetailEntity(target,source);	\
			CopyLoginUserEntity(target,source);	\

#endif
#ifndef CopyInvestorPositionDetailEntity
#define CopyInvestorPositionDetailEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->HedgeFlag=(source)->HedgeFlag;	\
			(target)->Direction=(source)->Direction;	\
			(target)->OpenDate=(source)->OpenDate;	\
			(target)->TradeID=(source)->TradeID;	\
			(target)->Volume=(source)->Volume;	\
			(target)->OpenPrice=(source)->OpenPrice;	\
			(target)->TradingDay=(source)->TradingDay;	\
			(target)->TradeType=(source)->TradeType;	\
			(target)->CombInstrumentID=(source)->CombInstrumentID;	\
			(target)->CloseProfitByDate=(source)->CloseProfitByDate;	\
			(target)->CloseProfitByTrade=(source)->CloseProfitByTrade;	\
			(target)->PositionProfitByDate=(source)->PositionProfitByDate;	\
			(target)->PositionProfitByTrade=(source)->PositionProfitByTrade;	\
			(target)->Margin=(source)->Margin;	\
			(target)->ExchMargin=(source)->ExchMargin;	\
			(target)->MarginRateByMoney=(source)->MarginRateByMoney;	\
			(target)->MarginRateByVolume=(source)->MarginRateByVolume;	\
			(target)->LastSettlementPrice=(source)->LastSettlementPrice;	\
			(target)->SettlementPrice=(source)->SettlementPrice;	\
			(target)->CloseVolume=(source)->CloseVolume;	\
			(target)->CloseAmount=(source)->CloseAmount;	\

#endif
#ifndef CopyAPIQryInvestorOptionFeeEntity
#define CopyAPIQryInvestorOptionFeeEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\

#endif
#ifndef CopyQryInvestorOptionFeeEntity
#define CopyQryInvestorOptionFeeEntity(target,source)	\
			CopyAPIQryInvestorOptionFeeEntity(target,source);	\
			CopyLoginUserEntity(target,source);	\

#endif
#ifndef CopyInvestorOptionFeeEntity
#define CopyInvestorOptionFeeEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->OpenFeeRate=(source)->OpenFeeRate;	\
			(target)->OpenFeeAmt=(source)->OpenFeeAmt;	\
			(target)->OffsetFeeRate=(source)->OffsetFeeRate;	\
			(target)->OffsetFeeAmt=(source)->OffsetFeeAmt;	\
			(target)->OTFeeRate=(source)->OTFeeRate;	\
			(target)->OTFeeAmt=(source)->OTFeeAmt;	\
			(target)->StrikeFeeRate=(source)->StrikeFeeRate;	\
			(target)->StrikeFeeAmt=(source)->StrikeFeeAmt;	\

#endif
#ifndef CopyInvestorTradingRightEntity
#define CopyInvestorTradingRightEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->ExchangeID=(source)->ExchangeID;	\
			(target)->InstrumentID=(source)->InstrumentID;	\
			(target)->TradingRight=(source)->TradingRight;	\
			(target)->ProductClass=(source)->ProductClass;	\

#endif
#ifndef CopyOrderDelayEntity
#define CopyOrderDelayEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->UserID=(source)->UserID;	\
			(target)->UserOrderLocalID=(source)->UserOrderLocalID;	\
			(target)->FrontID=(source)->FrontID;	\
			(target)->SessionID=(source)->SessionID;	\
			(target)->RequestID=(source)->RequestID;	\
			(target)->FTdRecvDown=(source)->FTdRecvDown;	\
			(target)->CoreRecvDown=(source)->CoreRecvDown;	\
			(target)->CoreSendUp=(source)->CoreSendUp;	\
			(target)->CoreRecvUp=(source)->CoreRecvUp;	\
			(target)->CoreSendDown=(source)->CoreSendDown;	\

#endif
#ifndef CopyPositionProfitEntity
#define CopyPositionProfitEntity(target,source)	\
			(target)->BrokerID=(source)->BrokerID;	\
			(target)->InvestorID=(source)->InvestorID;	\
			(target)->PositionProfit=(source)->PositionProfit;	\

#endif
#ifndef CopySystemInfoEntity
#define CopySystemInfoEntity(target,source)	\
			(target)->SystemID=(source)->SystemID;	\
			(target)->SystemName=(source)->SystemName;	\
			(target)->SystemIP=(source)->SystemIP;	\

#endif

#endif

