/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file QtestFtdcUserApiStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(QTEST_FTDCSTRUCT_H)
#define QTEST_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QTestFtdcUserApiDataType.h"

///信息分发
struct CQTestFtdcDisseminationField
{
	///序列系列号
	TQTestFtdcSequenceSeriesType	SequenceSeries;
	///序列号
	TQTestFtdcSequenceNoType	SequenceNo;
};

///响应信息
struct CQTestFtdcRspInfoField
{
	///错误代码
	TQTestFtdcErrorIDType	ErrorID;
	///错误信息
	TQTestFtdcErrorMsgType	ErrorMsg;
};

///通讯阶段
struct CQTestFtdcCommPhaseField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///通讯时段号
	TQTestFtdcCommPhaseNoType	CommPhaseNo;
};

///交易所交易日
struct CQTestFtdcExchangeTradingDayField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///交易所代码
	TQTestFtdcExchangeIDType	ExchangeID;
};

///结算会话
struct CQTestFtdcSettlementSessionField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
};

///当前时间
struct CQTestFtdcCurrentTimeField
{
	///当前日期
	TQTestFtdcDateType	CurrDate;
	///当前时间
	TQTestFtdcTimeType	CurrTime;
	///当前时间（毫秒）
	TQTestFtdcMillisecType	CurrMillisec;
};

///用户登录请求
struct CQTestFtdcReqUserLoginField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///密码
	TQTestFtdcPasswordType	Password;
	///用户端产品信息
	TQTestFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TQTestFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TQTestFtdcProtocolInfoType	ProtocolInfo;
	///数据中心代码
	TQTestFtdcDataCenterIDType	DataCenterID;
};

///用户登录应答
struct CQTestFtdcRspUserLoginField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///登录成功时间
	TQTestFtdcTimeType	LoginTime;
	///最大本地报单号
	TQTestFtdcOrderLocalIDType	MaxOrderLocalID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///交易系统名称
	TQTestFtdcTradingSystemNameType	TradingSystemName;
	///数据中心代码
	TQTestFtdcDataCenterIDType	DataCenterID;
	///会员私有流当前长度
	TQTestFtdcSequenceNoType	PrivateFlowSize;
	///交易员私有流当前长度
	TQTestFtdcSequenceNoType	UserFlowSize;
};

///用户登出请求
struct CQTestFtdcReqUserLogoutField
{
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
};

///用户登出应答
struct CQTestFtdcRspUserLogoutField
{
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
};

///输入报单
struct CQTestFtdcInputOrderField
{
	///报单编号
	TQTestFtdcOrderSysIDType	OrderSysID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///报单价格条件
	TQTestFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TQTestFtdcDirectionType	Direction;
	///组合开平标志
	TQTestFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TQTestFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TQTestFtdcPriceType	LimitPrice;
	///数量
	TQTestFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TQTestFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TQTestFtdcDateType	GTDDate;
	///成交量类型
	TQTestFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TQTestFtdcVolumeType	MinVolume;
	///触发条件
	TQTestFtdcContingentConditionType	ContingentCondition;
	///止损价
	TQTestFtdcPriceType	StopPrice;
	///强平原因
	TQTestFtdcForceCloseReasonType	ForceCloseReason;
	///本地报单编号
	TQTestFtdcOrderLocalIDType	OrderLocalID;
	///自动挂起标志
	TQTestFtdcBoolType	IsAutoSuspend;
	///业务单元
	TQTestFtdcBusinessUnitType	BusinessUnit;
};

///报单操作
struct CQTestFtdcOrderActionField
{
	///报单编号
	TQTestFtdcOrderSysIDType	OrderSysID;
	///本地报单编号
	TQTestFtdcOrderLocalIDType	OrderLocalID;
	///报单操作标志
	TQTestFtdcActionFlagType	ActionFlag;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///价格
	TQTestFtdcPriceType	LimitPrice;
	///数量变化
	TQTestFtdcVolumeType	VolumeChange;
	///操作本地编号
	TQTestFtdcOrderLocalIDType	ActionLocalID;
	///业务单元
	TQTestFtdcBusinessUnitType	BusinessUnit;
};

///OTC报单
struct CQTestFtdcOTCOrderField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///OTC报单编号
	TQTestFtdcOTCOrderSysIDType	OTCOrderSysID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQTestFtdcDirectionType	Direction;
	///开平标志
	TQTestFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TQTestFtdcHedgeFlagType	HedgeFlag;
	///价格
	TQTestFtdcPriceType	Price;
	///数量
	TQTestFtdcVolumeType	Volume;
	///对手方会员代码
	TQTestFtdcParticipantIDType	OtherParticipantID;
	///对手方客户代码
	TQTestFtdcClientIDType	OtherClientID;
	///对手方交易用户代码
	TQTestFtdcUserIDType	OtherUserID;
	///对手方开平标志
	TQTestFtdcOffsetFlagType	OtherOffsetFlag;
	///对手方套保标志
	TQTestFtdcHedgeFlagType	OtherHedgeFlag;
	///本地OTC报单编号
	TQTestFtdcOrderLocalIDType	OTCOrderLocalID;
	///OTC报单状态
	TQTestFtdcOTCOrderStatusType	OTCOrderStatus;
	///插入时间
	TQTestFtdcTimeType	InsertTime;
	///撤销时间
	TQTestFtdcTimeType	CancelTime;
	///结算会员编号
	TQTestFtdcParticipantIDType	ClearingPartID;
	///对手方结算会员编号
	TQTestFtdcParticipantIDType	OtherClearingPartID;
};

///输入报价
struct CQTestFtdcInputQuoteField
{
	///报价编号
	TQTestFtdcQuoteSysIDType	QuoteSysID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///买入数量
	TQTestFtdcVolumeType	BidVolume;
	///卖出数量
	TQTestFtdcVolumeType	AskVolume;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///本地报价编号
	TQTestFtdcOrderLocalIDType	QuoteLocalID;
	///业务单元
	TQTestFtdcBusinessUnitType	BusinessUnit;
	///买方组合开平标志
	TQTestFtdcCombOffsetFlagType	BidCombOffsetFlag;
	///买方组合套保标志
	TQTestFtdcCombHedgeFlagType	BidCombHedgeFlag;
	///买方价格
	TQTestFtdcPriceType	BidPrice;
	///卖方组合开平标志
	TQTestFtdcCombOffsetFlagType	AskCombOffsetFlag;
	///卖方组合套保标志
	TQTestFtdcCombHedgeFlagType	AskCombHedgeFlag;
	///卖方价格
	TQTestFtdcPriceType	AskPrice;
};

///报价操作
struct CQTestFtdcQuoteActionField
{
	///报价编号
	TQTestFtdcQuoteSysIDType	QuoteSysID;
	///本地报价编号
	TQTestFtdcOrderLocalIDType	QuoteLocalID;
	///报单操作标志
	TQTestFtdcActionFlagType	ActionFlag;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///操作本地编号
	TQTestFtdcOrderLocalIDType	ActionLocalID;
	///业务单元
	TQTestFtdcBusinessUnitType	BusinessUnit;
};

///输入执行宣告
struct CQTestFtdcInputExecOrderField
{
	///合约编号
	TQTestFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///本地执行宣告编号
	TQTestFtdcOrderLocalIDType	ExecOrderLocalID;
	///数量
	TQTestFtdcVolumeType	Volume;
	///业务单元
	TQTestFtdcBusinessUnitType	BusinessUnit;
};

///执行宣告操作
struct CQTestFtdcExecOrderActionField
{
	///执行宣告编号
	TQTestFtdcExecOrderSysIDType	ExecOrderSysID;
	///本地执行宣告编号
	TQTestFtdcOrderLocalIDType	ExecOrderLocalID;
	///报单操作标志
	TQTestFtdcActionFlagType	ActionFlag;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///操作本地编号
	TQTestFtdcOrderLocalIDType	ActionLocalID;
	///业务单元
	TQTestFtdcBusinessUnitType	BusinessUnit;
};

///用户登录退出
struct CQTestFtdcUserLogoutField
{
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
};

///用户口令修改
struct CQTestFtdcUserPasswordUpdateField
{
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///旧密码
	TQTestFtdcPasswordType	OldPassword;
	///新密码
	TQTestFtdcPasswordType	NewPassword;
};

///输入非标组合报单
struct CQTestFtdcInputCombOrderField
{
	///组合报单编号
	TQTestFtdcOrderSysIDType	CombOrderSysID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///价格
	TQTestFtdcPriceType	LimitPrice;
	///数量
	TQTestFtdcVolumeType	VolumeTotalOriginal;
	///本地报单编号
	TQTestFtdcOrderLocalIDType	CombOrderLocalID;
	///业务单元
	TQTestFtdcBusinessUnitType	BusinessUnit;
	///合约代码1
	TQTestFtdcInstrumentIDType	InstrumentID1;
	///买卖方向1
	TQTestFtdcDirectionType	Direction1;
	///分腿乘数1
	TQTestFtdcLegMultipleType	LegMultiple1;
	///开平标志1
	TQTestFtdcOffsetFlagType	OffsetFlag1;
	///投机套保标志1
	TQTestFtdcHedgeFlagType	HedgeFlag1;
	///合约代码2
	TQTestFtdcInstrumentIDType	InstrumentID2;
	///买卖方向2
	TQTestFtdcDirectionType	Direction2;
	///分腿乘数2
	TQTestFtdcLegMultipleType	LegMultiple2;
	///开平标志2
	TQTestFtdcOffsetFlagType	OffsetFlag2;
	///投机套保标志2
	TQTestFtdcHedgeFlagType	HedgeFlag2;
	///合约代码3
	TQTestFtdcInstrumentIDType	InstrumentID3;
	///买卖方向3
	TQTestFtdcDirectionType	Direction3;
	///分腿乘数3
	TQTestFtdcLegMultipleType	LegMultiple3;
	///开平标志3
	TQTestFtdcOffsetFlagType	OffsetFlag3;
	///投机套保标志3
	TQTestFtdcHedgeFlagType	HedgeFlag3;
	///合约代码4
	TQTestFtdcInstrumentIDType	InstrumentID4;
	///买卖方向4
	TQTestFtdcDirectionType	Direction4;
	///分腿乘数4
	TQTestFtdcLegMultipleType	LegMultiple4;
	///开平标志4
	TQTestFtdcOffsetFlagType	OffsetFlag4;
	///投机套保标志4
	TQTestFtdcHedgeFlagType	HedgeFlag4;
};

///强制用户退出
struct CQTestFtdcForceUserExitField
{
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
};

///会员资金帐户入金
struct CQTestFtdcAccountDepositField
{
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///资金账号
	TQTestFtdcAccountIDType	Account;
	///入金金额
	TQTestFtdcMoneyType	Deposit;
};

///报单查询
struct CQTestFtdcQryOrderField
{
	///起始会员代码
	TQTestFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TQTestFtdcParticipantIDType	PartIDEnd;
	///报单编号
	TQTestFtdcOrderSysIDType	OrderSysID;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///开始时间
	TQTestFtdcTimeType	TimeStart;
	///结束时间
	TQTestFtdcTimeType	TimeEnd;
};

///报价查询
struct CQTestFtdcQryQuoteField
{
	///起始会员代码
	TQTestFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TQTestFtdcParticipantIDType	PartIDEnd;
	///报价编号
	TQTestFtdcQuoteSysIDType	QuoteSysID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
};

///成交查询
struct CQTestFtdcQryTradeField
{
	///起始会员代码
	TQTestFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TQTestFtdcParticipantIDType	PartIDEnd;
	///起始合约代码
	TQTestFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TQTestFtdcInstrumentIDType	InstIDEnd;
	///成交编号
	TQTestFtdcTradeIDType	TradeID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///开始时间
	TQTestFtdcTimeType	TimeStart;
	///结束时间
	TQTestFtdcTimeType	TimeEnd;
};

///行情查询
struct CQTestFtdcQryMarketDataField
{
	///产品代码
	TQTestFtdcProductIDType	ProductID;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
};

///客户查询
struct CQTestFtdcQryClientField
{
	///起始会员代码
	TQTestFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TQTestFtdcParticipantIDType	PartIDEnd;
	///起始客户代码
	TQTestFtdcClientIDType	ClientIDStart;
	///结束客户代码
	TQTestFtdcClientIDType	ClientIDEnd;
};

///会员持仓查询
struct CQTestFtdcQryPartPositionField
{
	///起始会员代码
	TQTestFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TQTestFtdcParticipantIDType	PartIDEnd;
	///起始合约代码
	TQTestFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TQTestFtdcInstrumentIDType	InstIDEnd;
};

///客户持仓查询
struct CQTestFtdcQryClientPositionField
{
	///起始会员代码
	TQTestFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TQTestFtdcParticipantIDType	PartIDEnd;
	///起始客户代码
	TQTestFtdcClientIDType	ClientIDStart;
	///结束客户代码
	TQTestFtdcClientIDType	ClientIDEnd;
	///起始合约代码
	TQTestFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TQTestFtdcInstrumentIDType	InstIDEnd;
	///客户类型
	TQTestFtdcClientTypeType	ClientType;
};

///交易资金查询
struct CQTestFtdcQryPartAccountField
{
	///起始会员代码
	TQTestFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TQTestFtdcParticipantIDType	PartIDEnd;
	///资金帐号
	TQTestFtdcAccountIDType	AccountID;
};

///合约查询
struct CQTestFtdcQryInstrumentField
{
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///产品组代码
	TQTestFtdcProductGroupIDType	ProductGroupID;
	///产品代码
	TQTestFtdcProductIDType	ProductID;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
};

///合约状态查询
struct CQTestFtdcQryInstrumentStatusField
{
	///起始合约代码
	TQTestFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TQTestFtdcInstrumentIDType	InstIDEnd;
};

///结算组状态查询
struct CQTestFtdcQrySGDataSyncStatusField
{
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
};

///用户在线查询
struct CQTestFtdcQryUserSessionField
{
	///起始交易用户代码
	TQTestFtdcUserIDType	UserIDStart;
	///结束交易用户代码
	TQTestFtdcUserIDType	UserIDEnd;
};

///用户查询
struct CQTestFtdcQryUserField
{
	///起始交易用户代码
	TQTestFtdcUserIDType	UserIDStart;
	///结束交易用户代码
	TQTestFtdcUserIDType	UserIDEnd;
};

///公告查询
struct CQTestFtdcQryBulletinField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///市场代码
	TQTestFtdcMarketIDType	MarketID;
	///公告编号
	TQTestFtdcBulletinIDType	BulletinID;
	///公告类型
	TQTestFtdcNewsTypeType	NewsType;
	///紧急程度
	TQTestFtdcNewsUrgencyType	NewsUrgency;
};

///会员查询
struct CQTestFtdcQryParticipantField
{
	///起始会员代码
	TQTestFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TQTestFtdcParticipantIDType	PartIDEnd;
};

///保值额度查询
struct CQTestFtdcQryHedgeVolumeField
{
	///起始会员代码
	TQTestFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TQTestFtdcParticipantIDType	PartIDEnd;
	///起始客户代码
	TQTestFtdcClientIDType	ClientIDStart;
	///结束客户代码
	TQTestFtdcClientIDType	ClientIDEnd;
	///起始合约代码
	TQTestFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TQTestFtdcInstrumentIDType	InstIDEnd;
};

///合约价位查询
struct CQTestFtdcQryMBLMarketDataField
{
	///起始合约代码
	TQTestFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TQTestFtdcInstrumentIDType	InstIDEnd;
	///买卖方向
	TQTestFtdcDirectionType	Direction;
};

///信用限额查询
struct CQTestFtdcQryCreditLimitField
{
	///交易会员编号
	TQTestFtdcParticipantIDType	ParticipantID;
	///结算会员编号
	TQTestFtdcParticipantIDType	ClearingPartID;
};

///非标组合报单查询
struct CQTestFtdcQryCombOrderField
{
	///起始会员代码
	TQTestFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TQTestFtdcParticipantIDType	PartIDEnd;
	///组合报单编号
	TQTestFtdcOrderSysIDType	CombOrderSysID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
};

///会员资金应答
struct CQTestFtdcRspPartAccountField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///上次结算准备金
	TQTestFtdcMoneyType	PreBalance;
	///当前保证金总额
	TQTestFtdcMoneyType	CurrMargin;
	///平仓盈亏
	TQTestFtdcMoneyType	CloseProfit;
	///期权权利金收支
	TQTestFtdcMoneyType	Premium;
	///入金金额
	TQTestFtdcMoneyType	Deposit;
	///出金金额
	TQTestFtdcMoneyType	Withdraw;
	///期货结算准备金
	TQTestFtdcMoneyType	Balance;
	///可提资金
	TQTestFtdcMoneyType	Available;
	///资金帐号
	TQTestFtdcAccountIDType	AccountID;
	///冻结的保证金
	TQTestFtdcMoneyType	FrozenMargin;
	///冻结的权利金
	TQTestFtdcMoneyType	FrozenPremium;
	///基本准备金
	TQTestFtdcMoneyType	BaseReserve;
};

///会员持仓应答
struct CQTestFtdcRspPartPositionField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///投机套保标志
	TQTestFtdcHedgeFlagType	HedgeFlag;
	///持仓多空方向
	TQTestFtdcPosiDirectionType	PosiDirection;
	///上日持仓
	TQTestFtdcVolumeType	YdPosition;
	///今日持仓
	TQTestFtdcVolumeType	Position;
	///多头冻结
	TQTestFtdcVolumeType	LongFrozen;
	///空头冻结
	TQTestFtdcVolumeType	ShortFrozen;
	///昨日多头冻结
	TQTestFtdcVolumeType	YdLongFrozen;
	///昨日空头冻结
	TQTestFtdcVolumeType	YdShortFrozen;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///交易角色
	TQTestFtdcTradingRoleType	TradingRole;
};

///客户持仓应答
struct CQTestFtdcRspClientPositionField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///投机套保标志
	TQTestFtdcHedgeFlagType	HedgeFlag;
	///持仓多空方向
	TQTestFtdcPosiDirectionType	PosiDirection;
	///上日持仓
	TQTestFtdcVolumeType	YdPosition;
	///今日持仓
	TQTestFtdcVolumeType	Position;
	///多头冻结
	TQTestFtdcVolumeType	LongFrozen;
	///空头冻结
	TQTestFtdcVolumeType	ShortFrozen;
	///昨日多头冻结
	TQTestFtdcVolumeType	YdLongFrozen;
	///昨日空头冻结
	TQTestFtdcVolumeType	YdShortFrozen;
	///当日买成交量
	TQTestFtdcVolumeType	BuyTradeVolume;
	///当日卖成交量
	TQTestFtdcVolumeType	SellTradeVolume;
	///持仓成本
	TQTestFtdcMoneyType	PositionCost;
	///昨日持仓成本
	TQTestFtdcMoneyType	YdPositionCost;
	///占用的保证金
	TQTestFtdcMoneyType	UseMargin;
	///冻结的保证金
	TQTestFtdcMoneyType	FrozenMargin;
	///多头冻结的保证金
	TQTestFtdcMoneyType	LongFrozenMargin;
	///空头冻结的保证金
	TQTestFtdcMoneyType	ShortFrozenMargin;
	///冻结的权利金
	TQTestFtdcMoneyType	FrozenPremium;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
};

///合约查询应答
struct CQTestFtdcRspInstrumentField
{
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///产品代码
	TQTestFtdcProductIDType	ProductID;
	///产品组代码
	TQTestFtdcProductGroupIDType	ProductGroupID;
	///基础商品代码
	TQTestFtdcInstrumentIDType	UnderlyingInstrID;
	///产品类型
	TQTestFtdcProductClassType	ProductClass;
	///持仓类型
	TQTestFtdcPositionTypeType	PositionType;
	///执行价
	TQTestFtdcPriceType	StrikePrice;
	///期权类型
	TQTestFtdcOptionsTypeType	OptionsType;
	///合约数量乘数
	TQTestFtdcVolumeMultipleType	VolumeMultiple;
	///合约基础商品乘数
	TQTestFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///合约名称
	TQTestFtdcInstrumentNameType	InstrumentName;
	///交割年份
	TQTestFtdcYearType	DeliveryYear;
	///交割月
	TQTestFtdcMonthType	DeliveryMonth;
	///提前月份
	TQTestFtdcAdvanceMonthType	AdvanceMonth;
	///当前是否交易
	TQTestFtdcBoolType	IsTrading;
	///创建日
	TQTestFtdcDateType	CreateDate;
	///上市日
	TQTestFtdcDateType	OpenDate;
	///到期日
	TQTestFtdcDateType	ExpireDate;
	///开始交割日
	TQTestFtdcDateType	StartDelivDate;
	///最后交割日
	TQTestFtdcDateType	EndDelivDate;
	///挂牌基准价
	TQTestFtdcPriceType	BasisPrice;
	///市价单最大下单量
	TQTestFtdcVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	TQTestFtdcVolumeType	MinMarketOrderVolume;
	///限价单最大下单量
	TQTestFtdcVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	TQTestFtdcVolumeType	MinLimitOrderVolume;
	///最小变动价位
	TQTestFtdcPriceType	PriceTick;
	///交割月自然人开仓
	TQTestFtdcMonthCountType	AllowDelivPersonOpen;
};

///信息查询
struct CQTestFtdcQryInformationField
{
	///起始信息代码
	TQTestFtdcInformationIDType	InformationIDStart;
	///结束信息代码
	TQTestFtdcInformationIDType	InformationIDEnd;
};

///信息查询
struct CQTestFtdcInformationField
{
	///信息编号
	TQTestFtdcInformationIDType	InformationID;
	///序列号
	TQTestFtdcSequenceNoType	SequenceNo;
	///消息正文
	TQTestFtdcContentType	Content;
	///正文长度
	TQTestFtdcContentLengthType	ContentLength;
	///是否完成
	TQTestFtdcBoolType	IsAccomplished;
};

///信用限额
struct CQTestFtdcCreditLimitField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///上次结算准备金
	TQTestFtdcMoneyType	PreBalance;
	///当前保证金总额
	TQTestFtdcMoneyType	CurrMargin;
	///平仓盈亏
	TQTestFtdcMoneyType	CloseProfit;
	///期权权利金收支
	TQTestFtdcMoneyType	Premium;
	///入金金额
	TQTestFtdcMoneyType	Deposit;
	///出金金额
	TQTestFtdcMoneyType	Withdraw;
	///期货结算准备金
	TQTestFtdcMoneyType	Balance;
	///可提资金
	TQTestFtdcMoneyType	Available;
	///交易会员编号
	TQTestFtdcParticipantIDType	ParticipantID;
	///结算会员编号
	TQTestFtdcParticipantIDType	ClearingPartID;
	///冻结的保证金
	TQTestFtdcMoneyType	FrozenMargin;
	///冻结的权利金
	TQTestFtdcMoneyType	FrozenPremium;
};

///客户查询应答
struct CQTestFtdcRspClientField
{
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///客户名称
	TQTestFtdcPartyNameType	ClientName;
	///证件类型
	TQTestFtdcIdCardTypeType	IdentifiedCardType;
	///原证件号码
	TQTestFtdcIdentifiedCardNoV1Type	UseLess;
	///交易角色
	TQTestFtdcTradingRoleType	TradingRole;
	///客户类型
	TQTestFtdcClientTypeType	ClientType;
	///是否活跃
	TQTestFtdcBoolType	IsActive;
	///会员号
	TQTestFtdcParticipantIDType	ParticipantID;
	///证件号码
	TQTestFtdcIdentifiedCardNoType	IdentifiedCardNo;
};

///数据流回退
struct CQTestFtdcFlowMessageCancelField
{
	///序列系列号
	TQTestFtdcSequenceSeriesType	SequenceSeries;
	///交易日
	TQTestFtdcDateType	TradingDay;
	///数据中心代码
	TQTestFtdcDataCenterIDType	DataCenterID;
	///回退起始序列号
	TQTestFtdcSequenceNoType	StartSequenceNo;
	///回退结束序列号
	TQTestFtdcSequenceNoType	EndSequenceNo;
};

///会员
struct CQTestFtdcParticipantField
{
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///会员名称
	TQTestFtdcParticipantNameType	ParticipantName;
	///会员简称
	TQTestFtdcParticipantAbbrType	ParticipantAbbr;
	///会员类型
	TQTestFtdcMemberTypeType	MemberType;
	///是否活跃
	TQTestFtdcBoolType	IsActive;
};

///用户
struct CQTestFtdcUserField
{
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///交易用户类型
	TQTestFtdcUserTypeType	UserType;
	///密码
	TQTestFtdcPasswordType	Password;
	///交易员权限
	TQTestFtdcUserActiveType	IsActive;
};

///客户
struct CQTestFtdcClientField
{
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///客户名称
	TQTestFtdcPartyNameType	ClientName;
	///证件类型
	TQTestFtdcIdCardTypeType	IdentifiedCardType;
	///证件号码
	TQTestFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///交易角色
	TQTestFtdcTradingRoleType	TradingRole;
	///客户类型
	TQTestFtdcClientTypeType	ClientType;
	///是否活跃
	TQTestFtdcBoolType	IsActive;
	///客户交易类型
	TQTestFtdcHedgeFlagType	HedgeFlag;
};

///用户会话
struct CQTestFtdcUserSessionField
{
	///前置编号
	TQTestFtdcFrontIDType	FrontID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///交易用户类型
	TQTestFtdcUserTypeType	UserType;
	///会话编号
	TQTestFtdcSessionIDType	SessionID;
	///登录时间
	TQTestFtdcTimeType	LoginTime;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///IP地址
	TQTestFtdcIPAddressType	IPAddress;
	///用户端产品信息
	TQTestFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TQTestFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TQTestFtdcProtocolInfoType	ProtocolInfo;
};

///产品组
struct CQTestFtdcProductGroupField
{
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///产品组代码
	TQTestFtdcProductGroupIDType	ProductGroupID;
	///产品组名称
	TQTestFtdcProductGroupNameType	ProductGroupName;
	///商品代码
	TQTestFtdcCommodityIDType	CommodityID;
};

///产品
struct CQTestFtdcProductField
{
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///产品代码
	TQTestFtdcProductIDType	ProductID;
	///产品组代码
	TQTestFtdcProductGroupIDType	ProductGroupID;
	///产品名称
	TQTestFtdcProductNameType	ProductName;
	///产品类型
	TQTestFtdcProductClassType	ProductClass;
};

///合约
struct CQTestFtdcInstrumentField
{
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///产品代码
	TQTestFtdcProductIDType	ProductID;
	///产品组代码
	TQTestFtdcProductGroupIDType	ProductGroupID;
	///基础商品代码
	TQTestFtdcInstrumentIDType	UnderlyingInstrID;
	///产品类型
	TQTestFtdcProductClassType	ProductClass;
	///持仓类型
	TQTestFtdcPositionTypeType	PositionType;
	///执行价
	TQTestFtdcPriceType	StrikePrice;
	///期权类型
	TQTestFtdcOptionsTypeType	OptionsType;
	///合约数量乘数
	TQTestFtdcVolumeMultipleType	VolumeMultiple;
	///合约基础商品乘数
	TQTestFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///合约名称
	TQTestFtdcInstrumentNameType	InstrumentName;
	///交割年份
	TQTestFtdcYearType	DeliveryYear;
	///交割月
	TQTestFtdcMonthType	DeliveryMonth;
	///提前月份
	TQTestFtdcAdvanceMonthType	AdvanceMonth;
	///当前是否交易
	TQTestFtdcBoolType	IsTrading;
};

///组合交易合约的单腿
struct CQTestFtdcCombinationLegField
{
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///组合合约代码
	TQTestFtdcInstrumentIDType	CombInstrumentID;
	///单腿编号
	TQTestFtdcLegIDType	LegID;
	///单腿合约代码
	TQTestFtdcInstrumentIDType	LegInstrumentID;
	///买卖方向
	TQTestFtdcDirectionType	Direction;
	///单腿乘数
	TQTestFtdcLegMultipleType	LegMultiple;
	///推导层数
	TQTestFtdcImplyLevelType	ImplyLevel;
};

///账户资金信息
struct CQTestFtdcAccountInfoField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///上次结算准备金
	TQTestFtdcMoneyType	PreBalance;
	///当前保证金总额
	TQTestFtdcMoneyType	CurrMargin;
	///平仓盈亏
	TQTestFtdcMoneyType	CloseProfit;
	///期权权利金收支
	TQTestFtdcMoneyType	Premium;
	///入金金额
	TQTestFtdcMoneyType	Deposit;
	///出金金额
	TQTestFtdcMoneyType	Withdraw;
	///期货结算准备金
	TQTestFtdcMoneyType	Balance;
	///可提资金
	TQTestFtdcMoneyType	Available;
	///开户日期
	TQTestFtdcDateType	DateAccountOpen;
	///上次结算的日期
	TQTestFtdcDateType	PreDate;
	///上结算的编号
	TQTestFtdcSettlementIDType	PreSettlementID;
	///上次保证金总额
	TQTestFtdcMoneyType	PreMargin;
	///期货保证金
	TQTestFtdcMoneyType	FuturesMargin;
	///期权保证金
	TQTestFtdcMoneyType	OptionsMargin;
	///持仓盈亏
	TQTestFtdcMoneyType	PositionProfit;
	///当日盈亏
	TQTestFtdcMoneyType	Profit;
	///利息收入
	TQTestFtdcMoneyType	Interest;
	///手续费
	TQTestFtdcMoneyType	Fee;
	///总质押金额
	TQTestFtdcMoneyType	TotalCollateral;
	///用质押抵的保证金金额
	TQTestFtdcMoneyType	CollateralForMargin;
	///上次资金利息积数
	TQTestFtdcMoneyType	PreAccmulateInterest;
	///资金利息积数
	TQTestFtdcMoneyType	AccumulateInterest;
	///质押手续费积数
	TQTestFtdcMoneyType	AccumulateFee;
	///冻结资金
	TQTestFtdcMoneyType	ForzenDeposit;
	///帐户状态
	TQTestFtdcAccountStatusType	AccountStatus;
	///资金帐号
	TQTestFtdcAccountIDType	AccountID;
};

///会员合约持仓
struct CQTestFtdcPartPositionField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///投机套保标志
	TQTestFtdcHedgeFlagType	HedgeFlag;
	///持仓多空方向
	TQTestFtdcPosiDirectionType	PosiDirection;
	///上日持仓
	TQTestFtdcVolumeType	YdPosition;
	///今日持仓
	TQTestFtdcVolumeType	Position;
	///多头冻结
	TQTestFtdcVolumeType	LongFrozen;
	///空头冻结
	TQTestFtdcVolumeType	ShortFrozen;
	///昨日多头冻结
	TQTestFtdcVolumeType	YdLongFrozen;
	///昨日空头冻结
	TQTestFtdcVolumeType	YdShortFrozen;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///交易角色
	TQTestFtdcTradingRoleType	TradingRole;
};

///客户合约持仓
struct CQTestFtdcClientPositionField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///投机套保标志
	TQTestFtdcHedgeFlagType	HedgeFlag;
	///持仓多空方向
	TQTestFtdcPosiDirectionType	PosiDirection;
	///上日持仓
	TQTestFtdcVolumeType	YdPosition;
	///今日持仓
	TQTestFtdcVolumeType	Position;
	///多头冻结
	TQTestFtdcVolumeType	LongFrozen;
	///空头冻结
	TQTestFtdcVolumeType	ShortFrozen;
	///昨日多头冻结
	TQTestFtdcVolumeType	YdLongFrozen;
	///昨日空头冻结
	TQTestFtdcVolumeType	YdShortFrozen;
	///当日买成交量
	TQTestFtdcVolumeType	BuyTradeVolume;
	///当日卖成交量
	TQTestFtdcVolumeType	SellTradeVolume;
	///持仓成本
	TQTestFtdcMoneyType	PositionCost;
	///昨日持仓成本
	TQTestFtdcMoneyType	YdPositionCost;
	///占用的保证金
	TQTestFtdcMoneyType	UseMargin;
	///冻结的保证金
	TQTestFtdcMoneyType	FrozenMargin;
	///多头冻结的保证金
	TQTestFtdcMoneyType	LongFrozenMargin;
	///空头冻结的保证金
	TQTestFtdcMoneyType	ShortFrozenMargin;
	///冻结的权利金
	TQTestFtdcMoneyType	FrozenPremium;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
};

///保值额度量
struct CQTestFtdcHedgeVolumeField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///多头保值额度最初申请量
	TQTestFtdcVolumeType	LongVolumeOriginal;
	///空头保值额度最初申请量
	TQTestFtdcVolumeType	ShortVolumeOriginal;
	///多头保值额度
	TQTestFtdcVolumeType	LongVolume;
	///空头保值额度
	TQTestFtdcVolumeType	ShortVolume;
};

///市场行情
struct CQTestFtdcMarketDataField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///最新价
	TQTestFtdcPriceType	LastPrice;
	///昨结算
	TQTestFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TQTestFtdcPriceType	PreClosePrice;
	///昨持仓量
	TQTestFtdcLargeVolumeType	PreOpenInterest;
	///今开盘
	TQTestFtdcPriceType	OpenPrice;
	///最高价
	TQTestFtdcPriceType	HighestPrice;
	///最低价
	TQTestFtdcPriceType	LowestPrice;
	///数量
	TQTestFtdcVolumeType	Volume;
	///成交金额
	TQTestFtdcMoneyType	Turnover;
	///持仓量
	TQTestFtdcLargeVolumeType	OpenInterest;
	///今收盘
	TQTestFtdcPriceType	ClosePrice;
	///今结算
	TQTestFtdcPriceType	SettlementPrice;
	///涨停板价
	TQTestFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TQTestFtdcPriceType	LowerLimitPrice;
	///昨虚实度
	TQTestFtdcRatioType	PreDelta;
	///今虚实度
	TQTestFtdcRatioType	CurrDelta;
	///最后修改时间
	TQTestFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQTestFtdcMillisecType	UpdateMillisec;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
};

///深度市场行情
struct CQTestFtdcDepthMarketDataField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///最新价
	TQTestFtdcPriceType	LastPrice;
	///昨结算
	TQTestFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TQTestFtdcPriceType	PreClosePrice;
	///昨持仓量
	TQTestFtdcLargeVolumeType	PreOpenInterest;
	///今开盘
	TQTestFtdcPriceType	OpenPrice;
	///最高价
	TQTestFtdcPriceType	HighestPrice;
	///最低价
	TQTestFtdcPriceType	LowestPrice;
	///数量
	TQTestFtdcVolumeType	Volume;
	///成交金额
	TQTestFtdcMoneyType	Turnover;
	///持仓量
	TQTestFtdcLargeVolumeType	OpenInterest;
	///今收盘
	TQTestFtdcPriceType	ClosePrice;
	///今结算
	TQTestFtdcPriceType	SettlementPrice;
	///涨停板价
	TQTestFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TQTestFtdcPriceType	LowerLimitPrice;
	///昨虚实度
	TQTestFtdcRatioType	PreDelta;
	///今虚实度
	TQTestFtdcRatioType	CurrDelta;
	///最后修改时间
	TQTestFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQTestFtdcMillisecType	UpdateMillisec;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///申买价一
	TQTestFtdcPriceType	BidPrice1;
	///申买量一
	TQTestFtdcVolumeType	BidVolume1;
	///申卖价一
	TQTestFtdcPriceType	AskPrice1;
	///申卖量一
	TQTestFtdcVolumeType	AskVolume1;
	///申买价二
	TQTestFtdcPriceType	BidPrice2;
	///申买量二
	TQTestFtdcVolumeType	BidVolume2;
	///申卖价二
	TQTestFtdcPriceType	AskPrice2;
	///申卖量二
	TQTestFtdcVolumeType	AskVolume2;
	///申买价三
	TQTestFtdcPriceType	BidPrice3;
	///申买量三
	TQTestFtdcVolumeType	BidVolume3;
	///申卖价三
	TQTestFtdcPriceType	AskPrice3;
	///申卖量三
	TQTestFtdcVolumeType	AskVolume3;
	///申买价四
	TQTestFtdcPriceType	BidPrice4;
	///申买量四
	TQTestFtdcVolumeType	BidVolume4;
	///申卖价四
	TQTestFtdcPriceType	AskPrice4;
	///申卖量四
	TQTestFtdcVolumeType	AskVolume4;
	///申买价五
	TQTestFtdcPriceType	BidPrice5;
	///申买量五
	TQTestFtdcVolumeType	BidVolume5;
	///申卖价五
	TQTestFtdcPriceType	AskPrice5;
	///申卖量五
	TQTestFtdcVolumeType	AskVolume5;
};

///分价表
struct CQTestFtdcMBLMarketDataField
{
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQTestFtdcDirectionType	Direction;
	///价格
	TQTestFtdcPriceType	Price;
	///数量
	TQTestFtdcVolumeType	Volume;
};

///别名定义
struct CQTestFtdcAliasDefineField
{
	///起始位置
	TQTestFtdcStartPosType	StartPos;
	///别名
	TQTestFtdcAliasType	Alias;
	///原文
	TQTestFtdcOriginalTextType	OriginalText;
};

///行情基础属性
struct CQTestFtdcMarketDataBaseField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///昨结算
	TQTestFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TQTestFtdcPriceType	PreClosePrice;
	///昨持仓量
	TQTestFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TQTestFtdcRatioType	PreDelta;
};

///行情静态属性
struct CQTestFtdcMarketDataStaticField
{
	///今开盘
	TQTestFtdcPriceType	OpenPrice;
	///最高价
	TQTestFtdcPriceType	HighestPrice;
	///最低价
	TQTestFtdcPriceType	LowestPrice;
	///今收盘
	TQTestFtdcPriceType	ClosePrice;
	///涨停板价
	TQTestFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TQTestFtdcPriceType	LowerLimitPrice;
	///今结算
	TQTestFtdcPriceType	SettlementPrice;
	///今虚实度
	TQTestFtdcRatioType	CurrDelta;
};

///行情最新成交属性
struct CQTestFtdcMarketDataLastMatchField
{
	///最新价
	TQTestFtdcPriceType	LastPrice;
	///数量
	TQTestFtdcVolumeType	Volume;
	///成交金额
	TQTestFtdcMoneyType	Turnover;
	///持仓量
	TQTestFtdcLargeVolumeType	OpenInterest;
};

///行情最优价属性
struct CQTestFtdcMarketDataBestPriceField
{
	///申买价一
	TQTestFtdcPriceType	BidPrice1;
	///申买量一
	TQTestFtdcVolumeType	BidVolume1;
	///申卖价一
	TQTestFtdcPriceType	AskPrice1;
	///申卖量一
	TQTestFtdcVolumeType	AskVolume1;
};

///行情申买二、三属性
struct CQTestFtdcMarketDataBid23Field
{
	///申买价二
	TQTestFtdcPriceType	BidPrice2;
	///申买量二
	TQTestFtdcVolumeType	BidVolume2;
	///申买价三
	TQTestFtdcPriceType	BidPrice3;
	///申买量三
	TQTestFtdcVolumeType	BidVolume3;
};

///行情申卖二、三属性
struct CQTestFtdcMarketDataAsk23Field
{
	///申卖价二
	TQTestFtdcPriceType	AskPrice2;
	///申卖量二
	TQTestFtdcVolumeType	AskVolume2;
	///申卖价三
	TQTestFtdcPriceType	AskPrice3;
	///申卖量三
	TQTestFtdcVolumeType	AskVolume3;
};

///行情申买四、五属性
struct CQTestFtdcMarketDataBid45Field
{
	///申买价四
	TQTestFtdcPriceType	BidPrice4;
	///申买量四
	TQTestFtdcVolumeType	BidVolume4;
	///申买价五
	TQTestFtdcPriceType	BidPrice5;
	///申买量五
	TQTestFtdcVolumeType	BidVolume5;
};

///行情申卖四、五属性
struct CQTestFtdcMarketDataAsk45Field
{
	///申卖价四
	TQTestFtdcPriceType	AskPrice4;
	///申卖量四
	TQTestFtdcVolumeType	AskVolume4;
	///申卖价五
	TQTestFtdcPriceType	AskPrice5;
	///申卖量五
	TQTestFtdcVolumeType	AskVolume5;
};

///行情更新时间属性
struct CQTestFtdcMarketDataUpdateTimeField
{
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TQTestFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQTestFtdcMillisecType	UpdateMillisec;
};

///报价
struct CQTestFtdcQuoteField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///报价编号
	TQTestFtdcQuoteSysIDType	QuoteSysID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///买入数量
	TQTestFtdcVolumeType	BidVolume;
	///卖出数量
	TQTestFtdcVolumeType	AskVolume;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///本地报价编号
	TQTestFtdcOrderLocalIDType	QuoteLocalID;
	///业务单元
	TQTestFtdcBusinessUnitType	BusinessUnit;
	///买方组合开平标志
	TQTestFtdcCombOffsetFlagType	BidCombOffsetFlag;
	///买方组合套保标志
	TQTestFtdcCombHedgeFlagType	BidCombHedgeFlag;
	///买方价格
	TQTestFtdcPriceType	BidPrice;
	///卖方组合开平标志
	TQTestFtdcCombOffsetFlagType	AskCombOffsetFlag;
	///卖方组合套保标志
	TQTestFtdcCombHedgeFlagType	AskCombHedgeFlag;
	///卖方价格
	TQTestFtdcPriceType	AskPrice;
	///插入时间
	TQTestFtdcTimeType	InsertTime;
	///撤销时间
	TQTestFtdcTimeType	CancelTime;
	///成交时间
	TQTestFtdcTimeType	TradeTime;
	///买方报单编号
	TQTestFtdcOrderSysIDType	BidOrderSysID;
	///卖方报单编号
	TQTestFtdcOrderSysIDType	AskOrderSysID;
	///结算会员编号
	TQTestFtdcParticipantIDType	ClearingPartID;
};

///成交
struct CQTestFtdcTradeField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///成交编号
	TQTestFtdcTradeIDType	TradeID;
	///买卖方向
	TQTestFtdcDirectionType	Direction;
	///报单编号
	TQTestFtdcOrderSysIDType	OrderSysID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易角色
	TQTestFtdcTradingRoleType	TradingRole;
	///资金帐号
	TQTestFtdcAccountIDType	AccountID;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///开平标志
	TQTestFtdcOffsetFlagType	OffsetFlag;
	///投机套保标志
	TQTestFtdcHedgeFlagType	HedgeFlag;
	///价格
	TQTestFtdcPriceType	Price;
	///数量
	TQTestFtdcVolumeType	Volume;
	///成交时间
	TQTestFtdcTimeType	TradeTime;
	///成交类型
	TQTestFtdcTradeTypeType	TradeType;
	///成交价来源
	TQTestFtdcPriceSourceType	PriceSource;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///本地报单编号
	TQTestFtdcOrderLocalIDType	OrderLocalID;
	///结算会员编号
	TQTestFtdcParticipantIDType	ClearingPartID;
	///业务单元
	TQTestFtdcBusinessUnitType	BusinessUnit;
};

///报单
struct CQTestFtdcOrderField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///报单编号
	TQTestFtdcOrderSysIDType	OrderSysID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///报单价格条件
	TQTestFtdcOrderPriceTypeType	OrderPriceType;
	///买卖方向
	TQTestFtdcDirectionType	Direction;
	///组合开平标志
	TQTestFtdcCombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	TQTestFtdcCombHedgeFlagType	CombHedgeFlag;
	///价格
	TQTestFtdcPriceType	LimitPrice;
	///数量
	TQTestFtdcVolumeType	VolumeTotalOriginal;
	///有效期类型
	TQTestFtdcTimeConditionType	TimeCondition;
	///GTD日期
	TQTestFtdcDateType	GTDDate;
	///成交量类型
	TQTestFtdcVolumeConditionType	VolumeCondition;
	///最小成交量
	TQTestFtdcVolumeType	MinVolume;
	///触发条件
	TQTestFtdcContingentConditionType	ContingentCondition;
	///止损价
	TQTestFtdcPriceType	StopPrice;
	///强平原因
	TQTestFtdcForceCloseReasonType	ForceCloseReason;
	///本地报单编号
	TQTestFtdcOrderLocalIDType	OrderLocalID;
	///自动挂起标志
	TQTestFtdcBoolType	IsAutoSuspend;
	///报单来源
	TQTestFtdcOrderSourceType	OrderSource;
	///报单状态
	TQTestFtdcOrderStatusType	OrderStatus;
	///报单类型
	TQTestFtdcOrderTypeType	OrderType;
	///今成交数量
	TQTestFtdcVolumeType	VolumeTraded;
	///剩余数量
	TQTestFtdcVolumeType	VolumeTotal;
	///报单日期
	TQTestFtdcDateType	InsertDate;
	///插入时间
	TQTestFtdcTimeType	InsertTime;
	///激活时间
	TQTestFtdcTimeType	ActiveTime;
	///挂起时间
	TQTestFtdcTimeType	SuspendTime;
	///最后修改时间
	TQTestFtdcTimeType	UpdateTime;
	///撤销时间
	TQTestFtdcTimeType	CancelTime;
	///最后修改交易用户代码
	TQTestFtdcUserIDType	ActiveUserID;
	///优先权
	TQTestFtdcPriorityType	Priority;
	///按时间排队的序号
	TQTestFtdcTimeSortIDType	TimeSortID;
	///结算会员编号
	TQTestFtdcParticipantIDType	ClearingPartID;
	///业务单元
	TQTestFtdcBusinessUnitType	BusinessUnit;
};

///执行宣告
struct CQTestFtdcExecOrderField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///合约编号
	TQTestFtdcInstrumentIDType	InstrumentID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///本地执行宣告编号
	TQTestFtdcOrderLocalIDType	ExecOrderLocalID;
	///数量
	TQTestFtdcVolumeType	Volume;
	///业务单元
	TQTestFtdcBusinessUnitType	BusinessUnit;
	///执行宣告编号
	TQTestFtdcExecOrderSysIDType	ExecOrderSysID;
	///报单日期
	TQTestFtdcDateType	InsertDate;
	///插入时间
	TQTestFtdcTimeType	InsertTime;
	///撤销时间
	TQTestFtdcTimeType	CancelTime;
	///执行结果
	TQTestFtdcExecResultType	ExecResult;
	///结算会员编号
	TQTestFtdcParticipantIDType	ClearingPartID;
};

///非标组合报单
struct CQTestFtdcCombOrderField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///组合报单编号
	TQTestFtdcOrderSysIDType	CombOrderSysID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///交易用户代码
	TQTestFtdcUserIDType	UserID;
	///价格
	TQTestFtdcPriceType	LimitPrice;
	///数量
	TQTestFtdcVolumeType	VolumeTotalOriginal;
	///本地报单编号
	TQTestFtdcOrderLocalIDType	CombOrderLocalID;
	///业务单元
	TQTestFtdcBusinessUnitType	BusinessUnit;
	///合约代码1
	TQTestFtdcInstrumentIDType	InstrumentID1;
	///买卖方向1
	TQTestFtdcDirectionType	Direction1;
	///分腿乘数1
	TQTestFtdcLegMultipleType	LegMultiple1;
	///开平标志1
	TQTestFtdcOffsetFlagType	OffsetFlag1;
	///投机套保标志1
	TQTestFtdcHedgeFlagType	HedgeFlag1;
	///合约代码2
	TQTestFtdcInstrumentIDType	InstrumentID2;
	///买卖方向2
	TQTestFtdcDirectionType	Direction2;
	///分腿乘数2
	TQTestFtdcLegMultipleType	LegMultiple2;
	///开平标志2
	TQTestFtdcOffsetFlagType	OffsetFlag2;
	///投机套保标志2
	TQTestFtdcHedgeFlagType	HedgeFlag2;
	///合约代码3
	TQTestFtdcInstrumentIDType	InstrumentID3;
	///买卖方向3
	TQTestFtdcDirectionType	Direction3;
	///分腿乘数3
	TQTestFtdcLegMultipleType	LegMultiple3;
	///开平标志3
	TQTestFtdcOffsetFlagType	OffsetFlag3;
	///投机套保标志3
	TQTestFtdcHedgeFlagType	HedgeFlag3;
	///合约代码4
	TQTestFtdcInstrumentIDType	InstrumentID4;
	///买卖方向4
	TQTestFtdcDirectionType	Direction4;
	///分腿乘数4
	TQTestFtdcLegMultipleType	LegMultiple4;
	///开平标志4
	TQTestFtdcOffsetFlagType	OffsetFlag4;
	///投机套保标志4
	TQTestFtdcHedgeFlagType	HedgeFlag4;
	///报单来源
	TQTestFtdcOrderSourceType	OrderSource;
	///今成交数量
	TQTestFtdcVolumeType	VolumeTraded;
	///剩余数量
	TQTestFtdcVolumeType	VolumeTotal;
	///报单日期
	TQTestFtdcDateType	InsertDate;
	///插入时间
	TQTestFtdcTimeType	InsertTime;
	///结算会员编号
	TQTestFtdcParticipantIDType	ClearingPartID;
};

///管理报单
struct CQTestFtdcAdminOrderField
{
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///管理报单命令
	TQTestFtdcAdminOrderCommandFlagType	AdminOrderCommand;
	///结算会员编号
	TQTestFtdcParticipantIDType	ClearingPartID;
	///交易会员编号
	TQTestFtdcParticipantIDType	ParticipantID;
	///金额
	TQTestFtdcMoneyType	Amount;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
};

///管理报单输入
struct CQTestFtdcInputAdminOrderField
{
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///管理报单命令
	TQTestFtdcAdminOrderCommandFlagType	AdminOrderCommand;
	///结算会员编号
	TQTestFtdcParticipantIDType	ClearingPartID;
	///交易会员编号
	TQTestFtdcParticipantIDType	ParticipantID;
	///金额
	TQTestFtdcMoneyType	Amount;
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
};

///公告
struct CQTestFtdcBulletinField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///公告编号
	TQTestFtdcBulletinIDType	BulletinID;
	///序列号
	TQTestFtdcSequenceNoType	SequenceNo;
	///公告类型
	TQTestFtdcNewsTypeType	NewsType;
	///紧急程度
	TQTestFtdcNewsUrgencyType	NewsUrgency;
	///发送时间
	TQTestFtdcTimeType	SendTime;
	///消息摘要
	TQTestFtdcAbstractType	Abstract;
	///消息来源
	TQTestFtdcComeFromType	ComeFrom;
	///消息正文
	TQTestFtdcContentType	Content;
	///WEB地址
	TQTestFtdcURLLinkType	URLLink;
	///市场代码
	TQTestFtdcMarketIDType	MarketID;
};

///交易所数据同步状态
struct CQTestFtdcExchangeDataSyncStatusField
{
	///交易日
	TQTestFtdcDateType	TradingDay;
	///交易所代码
	TQTestFtdcExchangeIDType	ExchangeID;
	///交易所数据同步状态
	TQTestFtdcExchangeDataSyncStatusType	ExchangeDataSyncStatus;
};

///结算组数据同步状态
struct CQTestFtdcSGDataSyncStatusField
{
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///交易日
	TQTestFtdcDateType	TradingDay;
	///结算编号
	TQTestFtdcSettlementIDType	SettlementID;
	///结算组数据同步状态
	TQTestFtdcSGDataSyncStatusType	SGDataSyncStatus;
};

///合约状态
struct CQTestFtdcInstrumentStatusField
{
	///结算组代码
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///合约交易状态
	TQTestFtdcInstrumentStatusType	InstrumentStatus;
	///交易阶段编号
	TQTestFtdcTradingSegmentSNType	TradingSegmentSN;
	///进入本状态时间
	TQTestFtdcTimeType	EnterTime;
	///进入本状态原因
	TQTestFtdcInstStatusEnterReasonType	EnterReason;
};

///客户持仓查询
struct CQTestFtdcQryClientPositionV1Field
{
	///起始会员代码
	TQTestFtdcParticipantIDType	PartIDStart;
	///结束会员代码
	TQTestFtdcParticipantIDType	PartIDEnd;
	///起始客户代码
	TQTestFtdcClientIDType	ClientIDStart;
	///结束客户代码
	TQTestFtdcClientIDType	ClientIDEnd;
	///起始合约代码
	TQTestFtdcInstrumentIDType	InstIDStart;
	///结束合约代码
	TQTestFtdcInstrumentIDType	InstIDEnd;
};

///询价
struct CQTestFtdcInputReqForQuoteField
{
	///询价编号
	TQTestFtdcQuoteSysIDType	ReqForQuoteID;
	///会员代码
	TQTestFtdcParticipantIDType	ParticipantID;
	///客户代码
	TQTestFtdcClientIDType	ClientID;
	///合约代码
	TQTestFtdcInstrumentIDType	InstrumentID;
	///交易日期
	TQTestFtdcTradingDayType	TradingDay;
	///询价时间
	TQTestFtdcTimeType	ReqForQuoteTime;
};



#endif
