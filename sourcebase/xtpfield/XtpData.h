// XtpData.h: 
//
///20090118	xuzh		增加了查询的日志（NT-0065）
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XTPDATA_H__EA501ADE_818C_4F9A_8738_AC9CCAF0B941__INCLUDED_)
#define AFX_XTPDATA_H__EA501ADE_818C_4F9A_8738_AC9CCAF0B941__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FieldDescribe.h"
#include "customDataType.h"

///合约
class CInstrumentField
{
public:
	///交易所代码
	CExchangeIDType	ExchangeID;
	///品种代码
	CProductIDType	ProductID;
	///品种名称
	CProductNameType	ProductName;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///合约名称
	CInstrumentNameType	InstrumentName;
	///交割年份
	CYearType	DeliveryYear;
	///交割月
	CMonthType	DeliveryMonth;
	///限价单最大下单量
	CVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	CVolumeType	MinLimitOrderVolume;
	///市价单最大下单量
	CVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	CVolumeType	MinMarketOrderVolume;
	///数量乘数
	CVolumeMultipleType	VolumeMultiple;
	///报价单位
	CPriceTickType	PriceTick;
	///币种
	CCurrencyType	Currency;
	///多头限仓
	CVolumeType	LongPosLimit;
	///空头限仓
	CVolumeType	ShortPosLimit;
	///跌停板价
	CPriceType	LowerLimitPrice;
	///涨停板价
	CPriceType	UpperLimitPrice;
	///昨结算
	CPriceType	PreSettlementPrice;
	///合约交易状态
	CInstrumentStatusType	InstrumentStatus;
	///创建日
	CDateType	CreateDate;
	///上市日
	CDateType	OpenDate;
	///到期日
	CDateType	ExpireDate;
	///开始交割日
	CDateType	StartDelivDate;
	///最后交割日
	CDateType	EndDelivDate;
	///挂牌基准价
	CPriceType	BasisPrice;
	///当前是否交易
	CBoolType	IsTrading;
	///基础商品代码
	CInstrumentIDType	UnderlyingInstrID;
	///基础商品乘数
	CUnderlyingMultipleType	UnderlyingMultiple;
	///持仓类型
	CPositionTypeType	PositionType;
	///执行价
	CPriceType	StrikePrice;
	///期权类型
	COptionsTypeType	OptionsType;
	///产品类型
	CProductClassType	ProductClass;
	///期权行权方式
	COptionsModeType	OptionsMode;
	///产品组
	CProductGroupIDType	ProductGroupID;
	///通道对应的APIID
	CNumberType	APIID;
	///组合合约腿的数量
	CNumberType	LegQty;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(ProductID)
		,
		TYPE_DESC(ProductName)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(InstrumentName)
		,
		TYPE_DESC(DeliveryYear)
		,
		TYPE_DESC(DeliveryMonth)
		,
		TYPE_DESC(MaxLimitOrderVolume)
		,
		TYPE_DESC(MinLimitOrderVolume)
		,
		TYPE_DESC(MaxMarketOrderVolume)
		,
		TYPE_DESC(MinMarketOrderVolume)
		,
		TYPE_DESC(VolumeMultiple)
		,
		TYPE_DESC(PriceTick)
		,
		TYPE_DESC(Currency)
		,
		TYPE_DESC(LongPosLimit)
		,
		TYPE_DESC(ShortPosLimit)
		,
		TYPE_DESC(LowerLimitPrice)
		,
		TYPE_DESC(UpperLimitPrice)
		,
		TYPE_DESC(PreSettlementPrice)
		,
		TYPE_DESC(InstrumentStatus)
		,
		TYPE_DESC(CreateDate)
		,
		TYPE_DESC(OpenDate)
		,
		TYPE_DESC(ExpireDate)
		,
		TYPE_DESC(StartDelivDate)
		,
		TYPE_DESC(EndDelivDate)
		,
		TYPE_DESC(BasisPrice)
		,
		TYPE_DESC(IsTrading)
		,
		TYPE_DESC(UnderlyingInstrID)
		,
		TYPE_DESC(UnderlyingMultiple)
		,
		TYPE_DESC(PositionType)
		,
		TYPE_DESC(StrikePrice)
		,
		TYPE_DESC(OptionsType)
		,
		TYPE_DESC(ProductClass)
		,
		TYPE_DESC(OptionsMode)
		,
		TYPE_DESC(ProductGroupID)
		,
		TYPE_DESC(APIID)
		,
		TYPE_DESC(LegQty)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_Instrument=0x3002;

///合约状态
class CInstrumentStatusField
{
public:
	///交易所代码
	CExchangeIDType	ExchangeID;
	///品种代码
	CProductIDType	ProductID;
	///品种名称
	CProductNameType	ProductName;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///合约名称
	CInstrumentNameType	InstrumentName;
	///交割年份
	CYearType	DeliveryYear;
	///交割月
	CMonthType	DeliveryMonth;
	///限价单最大下单量
	CVolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	CVolumeType	MinLimitOrderVolume;
	///市价单最大下单量
	CVolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	CVolumeType	MinMarketOrderVolume;
	///数量乘数
	CVolumeMultipleType	VolumeMultiple;
	///报价单位
	CPriceTickType	PriceTick;
	///币种
	CCurrencyType	Currency;
	///多头限仓
	CVolumeType	LongPosLimit;
	///空头限仓
	CVolumeType	ShortPosLimit;
	///跌停板价
	CPriceType	LowerLimitPrice;
	///涨停板价
	CPriceType	UpperLimitPrice;
	///昨结算
	CPriceType	PreSettlementPrice;
	///合约交易状态
	CInstrumentStatusType	InstrumentStatus;
	///创建日
	CDateType	CreateDate;
	///上市日
	CDateType	OpenDate;
	///到期日
	CDateType	ExpireDate;
	///开始交割日
	CDateType	StartDelivDate;
	///最后交割日
	CDateType	EndDelivDate;
	///挂牌基准价
	CPriceType	BasisPrice;
	///当前是否交易
	CBoolType	IsTrading;
	///基础商品代码
	CInstrumentIDType	UnderlyingInstrID;
	///基础商品乘数
	CUnderlyingMultipleType	UnderlyingMultiple;
	///持仓类型
	CPositionTypeType	PositionType;
	///执行价
	CPriceType	StrikePrice;
	///期权类型
	COptionsTypeType	OptionsType;
	///产品类型
	CProductClassType	ProductClass;
	///期权行权方式
	COptionsModeType	OptionsMode;
	///产品组
	CProductGroupIDType	ProductGroupID;
	///通道对应的APIID
	CNumberType	APIID;
	///组合合约腿的数量
	CNumberType	LegQty;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(ProductID)
		,
		TYPE_DESC(ProductName)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(InstrumentName)
		,
		TYPE_DESC(DeliveryYear)
		,
		TYPE_DESC(DeliveryMonth)
		,
		TYPE_DESC(MaxLimitOrderVolume)
		,
		TYPE_DESC(MinLimitOrderVolume)
		,
		TYPE_DESC(MaxMarketOrderVolume)
		,
		TYPE_DESC(MinMarketOrderVolume)
		,
		TYPE_DESC(VolumeMultiple)
		,
		TYPE_DESC(PriceTick)
		,
		TYPE_DESC(Currency)
		,
		TYPE_DESC(LongPosLimit)
		,
		TYPE_DESC(ShortPosLimit)
		,
		TYPE_DESC(LowerLimitPrice)
		,
		TYPE_DESC(UpperLimitPrice)
		,
		TYPE_DESC(PreSettlementPrice)
		,
		TYPE_DESC(InstrumentStatus)
		,
		TYPE_DESC(CreateDate)
		,
		TYPE_DESC(OpenDate)
		,
		TYPE_DESC(ExpireDate)
		,
		TYPE_DESC(StartDelivDate)
		,
		TYPE_DESC(EndDelivDate)
		,
		TYPE_DESC(BasisPrice)
		,
		TYPE_DESC(IsTrading)
		,
		TYPE_DESC(UnderlyingInstrID)
		,
		TYPE_DESC(UnderlyingMultiple)
		,
		TYPE_DESC(PositionType)
		,
		TYPE_DESC(StrikePrice)
		,
		TYPE_DESC(OptionsType)
		,
		TYPE_DESC(ProductClass)
		,
		TYPE_DESC(OptionsMode)
		,
		TYPE_DESC(ProductGroupID)
		,
		TYPE_DESC(APIID)
		,
		TYPE_DESC(LegQty)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InstrumentStatus=0x3003;

///交易所
class CExchangeField
{
public:
	///交易日
	CTradingDayType	TradingDay;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///交易所名称
	CExchangeNameType	ExchangeName;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(ExchangeName)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_Exchange=0x3004;

///客户交易编码
class CClientTradingIDField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///资金帐号
	CAccountIDType	AccountID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///会员编号
	CParticipantIDType	ParticipantID;
	///客户代码
	CClientIDType	ClientID;
	///客户代码权限
	CTradingRightType	ClientRight;
	///客户类型
	CClientTypeType	ClientType;
	///客户保值类型
	CHedgeFlagType	ClientHedgeFlag;
	///是否活跃
	CIsActiveType	IsActive;
	///通道对应的APIID
	CNumberType	APIID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(AccountID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(ParticipantID)
		,
		TYPE_DESC(ClientID)
		,
		TYPE_DESC(ClientRight)
		,
		TYPE_DESC(ClientType)
		,
		TYPE_DESC(ClientHedgeFlag)
		,
		TYPE_DESC(IsActive)
		,
		TYPE_DESC(APIID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_ClientTradingID=0x3006;

///投资者保证金率
class CInvestorMarginField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///投资者编码
	CInvestorIDType	InvestorID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///投机套保标志
	CHedgeFlagType	HedgeFlag;
	///多头占用保证金按比例
	CRatioType	LongMarginRate;
	///多头保证金按手数
	CRatioType	LongMarginAmt;
	///空头占用保证金按比例
	CRatioType	ShortMarginRate;
	///空头保证金按手数
	CRatioType	ShortMarginAmt;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(HedgeFlag)
		,
		TYPE_DESC(LongMarginRate)
		,
		TYPE_DESC(LongMarginAmt)
		,
		TYPE_DESC(ShortMarginRate)
		,
		TYPE_DESC(ShortMarginAmt)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorMargin=0x3007;

///投资者合约持仓
class CInvestorPositionField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///会员编号
	CParticipantIDType	ParticipantID;
	///客户代码
	CClientIDType	ClientID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///买卖方向
	CDirectionType	Direction;
	///投机套保标志
	CHedgeFlagType	HedgeFlag;
	///占用保证金
	CMoneyType	UsedMargin;
	///总持仓量
	CVolumeType	Position;
	///今日持仓成本
	CPriceType	PositionCost;
	///昨持仓量(不变值)
	CVolumeType	YdPosition;
	///昨日持仓成本
	CMoneyType	YdPositionCost;
	///冻结的保证金
	CMoneyType	FrozenMargin;
	///开仓冻结持仓
	CVolumeType	FrozenPosition;
	///平仓冻结持仓
	CVolumeType	FrozenClosing;
	///冻结的权利金
	CMoneyType	FrozenPremium;
	///最后一笔成交编号
	CTradeIDType	LastTradeID;
	///最后一笔本地报单编号
	COrderLocalIDType	LastOrderLocalID;
	///币种
	CCurrencyIDType	Currency;
	///持仓盈亏
	CMoneyType	PositionProfit;
	///今持仓量
	CVolumeType	TodayPosition;
	///今仓平仓冻结
	CVolumeType	FrozenTodayClosing;
	///成交类型
	CTradeTypeType	TradeType;
	///资金帐号
	CAccountIDType	AccountID;
	///计算浮动盈亏最新价
	CPriceType	LastPrice;
	///总持仓可平仓数量(包括平仓冻结持仓)
	CVolumeType	PositionClose;
	///昨持仓可平仓数量(包括平仓冻结持仓)
	CVolumeType	YdPositionClose;
	///昨持仓平仓冻结持仓
	CVolumeType	YdFrozenClosing;
	///计算浮动盈亏时的总持仓
	CVolumeType	CacalProfitPosition;
	///期权类型
	COptionsTypeType	OptionType;
	///行权价
	CPriceType	StrikePrice;
	///期权对应的标的合约代码
	CInstrumentIDType	OptionInstrumentID;
	///今仓持仓成本
	CMoneyType	TodayPositionCost;
	///短线持仓
	CVolumeType	ShortPosition;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(ParticipantID)
		,
		TYPE_DESC(ClientID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(Direction)
		,
		TYPE_DESC(HedgeFlag)
		,
		TYPE_DESC(UsedMargin)
		,
		TYPE_DESC(Position)
		,
		TYPE_DESC(PositionCost)
		,
		TYPE_DESC(YdPosition)
		,
		TYPE_DESC(YdPositionCost)
		,
		TYPE_DESC(FrozenMargin)
		,
		TYPE_DESC(FrozenPosition)
		,
		TYPE_DESC(FrozenClosing)
		,
		TYPE_DESC(FrozenPremium)
		,
		TYPE_DESC(LastTradeID)
		,
		TYPE_DESC(LastOrderLocalID)
		,
		TYPE_DESC(Currency)
		,
		TYPE_DESC(PositionProfit)
		,
		TYPE_DESC(TodayPosition)
		,
		TYPE_DESC(FrozenTodayClosing)
		,
		TYPE_DESC(TradeType)
		,
		TYPE_DESC(AccountID)
		,
		TYPE_DESC(LastPrice)
		,
		TYPE_DESC(PositionClose)
		,
		TYPE_DESC(YdPositionClose)
		,
		TYPE_DESC(YdFrozenClosing)
		,
		TYPE_DESC(CacalProfitPosition)
		,
		TYPE_DESC(OptionType)
		,
		TYPE_DESC(StrikePrice)
		,
		TYPE_DESC(OptionInstrumentID)
		,
		TYPE_DESC(TodayPositionCost)
		,
		TYPE_DESC(ShortPosition)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorPosition=0x3008;

///投资者手续费
class CInvestorFeeField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///投资者编码
	CInvestorIDType	InvestorID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///投机套保标志
	CHedgeFlagType	HedgeFlag;
	///开仓手续费按比例
	CRatioType	OpenFeeRate;
	///开仓手续费按手数
	CRatioType	OpenFeeAmt;
	///平仓手续费按比例
	CRatioType	OffsetFeeRate;
	///平仓手续费按手数
	CRatioType	OffsetFeeAmt;
	///平今仓手续费按比例
	CRatioType	OTFeeRate;
	///平今仓手续费按手数
	CRatioType	OTFeeAmt;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(HedgeFlag)
		,
		TYPE_DESC(OpenFeeRate)
		,
		TYPE_DESC(OpenFeeAmt)
		,
		TYPE_DESC(OffsetFeeRate)
		,
		TYPE_DESC(OffsetFeeAmt)
		,
		TYPE_DESC(OTFeeRate)
		,
		TYPE_DESC(OTFeeAmt)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorFee=0x3009;

///用户投资者关系
class CUserInvestorField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易用户代码
	CUserIDType	UserID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///授权功能集
	CGrantFuncSetType	GrantFuncSet;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(GrantFuncSet)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_UserInvestor=0x300B;

///投资者
class CInvestorField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///投资者名称
	CInvestorNameType	InvestorName;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(InvestorName)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_Investor=0x300C;

///投资者资金账户
class CInvestorAccountField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///资金帐号
	CAccountIDType	AccountID;
	///上次结算准备金
	CMoneyType	PreBalance;
	///上日可用资金
	CMoneyType	PreAvailable;
	///入金金额
	CMoneyType	Deposit;
	///出金金额
	CMoneyType	Withdraw;
	///占用保证金
	CMoneyType	Margin;
	///期权权利金收支
	CMoneyType	Premium;
	///手续费
	CMoneyType	Fee;
	///冻结的保证金
	CMoneyType	FrozenMargin;
	///冻结权利金
	CMoneyType	FrozenPremium;
	///冻结手续费
	CMoneyType	FrozenFee;
	///平仓盈亏
	CMoneyType	CloseProfit;
	///持仓盈亏
	CMoneyType	PositionProfit;
	///可用资金
	CMoneyType	Available;
	///结算准备金
	CMoneyType	Balance;
	///多头占用保证金
	CMoneyType	LongMargin;
	///空头占用保证金
	CMoneyType	ShortMargin;
	///多头冻结的保证金
	CMoneyType	LongFrozenMargin;
	///空头冻结的保证金
	CMoneyType	ShortFrozenMargin;
	///动态权益
	CMoneyType	DynamicRights;
	///风险度
	CMoneyType	Risk;
	///其他费用
	CMoneyType	OtherFee;
	///质押金额
	CMoneyType	Mortgage;
	///币种
	CCurrencyIDType	Currency;
	///总冻结持仓
	CVolumeType	TotalFrozenPos;
	///今日出入金
	CMoneyType	TodayInOut;
	///当日释放保证金
	CMoneyType	ReleaseMargin;
	///浮盈是否可用
	CBoolType	IsProfitCanUse;
	///临时冻结资金
	CMoneyType	ManualFrozen;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(AccountID)
		,
		TYPE_DESC(PreBalance)
		,
		TYPE_DESC(PreAvailable)
		,
		TYPE_DESC(Deposit)
		,
		TYPE_DESC(Withdraw)
		,
		TYPE_DESC(Margin)
		,
		TYPE_DESC(Premium)
		,
		TYPE_DESC(Fee)
		,
		TYPE_DESC(FrozenMargin)
		,
		TYPE_DESC(FrozenPremium)
		,
		TYPE_DESC(FrozenFee)
		,
		TYPE_DESC(CloseProfit)
		,
		TYPE_DESC(PositionProfit)
		,
		TYPE_DESC(Available)
		,
		TYPE_DESC(Balance)
		,
		TYPE_DESC(LongMargin)
		,
		TYPE_DESC(ShortMargin)
		,
		TYPE_DESC(LongFrozenMargin)
		,
		TYPE_DESC(ShortFrozenMargin)
		,
		TYPE_DESC(DynamicRights)
		,
		TYPE_DESC(Risk)
		,
		TYPE_DESC(OtherFee)
		,
		TYPE_DESC(Mortgage)
		,
		TYPE_DESC(Currency)
		,
		TYPE_DESC(TotalFrozenPos)
		,
		TYPE_DESC(TodayInOut)
		,
		TYPE_DESC(ReleaseMargin)
		,
		TYPE_DESC(IsProfitCanUse)
		,
		TYPE_DESC(ManualFrozen)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorAccount=0x300E;

///保证金手续费
class CMoneyField
{
public:
	///保证金
	CMoneyType	Margin;
	///手续费
	CMoneyType	Fee;
	///权利金
	CMoneyType	Premium;
	///保证金变化值
	CMoneyType	MarginChanged;
	///冻结保证金变化值
	CMoneyType	FrozenMarginChanged;
	///占用的保证金
	CMoneyType	UsedMargin;
	TYPE_DESCRIPTOR((
		TYPE_DESC(Margin)
		,
		TYPE_DESC(Fee)
		,
		TYPE_DESC(Premium)
		,
		TYPE_DESC(MarginChanged)
		,
		TYPE_DESC(FrozenMarginChanged)
		,
		TYPE_DESC(UsedMargin)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_Money=0x300F;

///客户资金信息
class CExCapitalDataField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///资金帐号
	CAccountIDType	AccountID;
	///上次结算准备金
	CMoneyType	PreBalance;
	///上日可用资金
	CMoneyType	PreAvailable;
	///入金金额
	CMoneyType	Deposit;
	///出金金额
	CMoneyType	Withdraw;
	///占用保证金
	CMoneyType	Margin;
	///期权权利金收支
	CMoneyType	Premium;
	///手续费
	CMoneyType	Fee;
	///冻结的保证金
	CMoneyType	FrozenMargin;
	///冻结权利金
	CMoneyType	FrozenPremium;
	///冻结手续费
	CMoneyType	FrozenFee;
	///平仓盈亏
	CMoneyType	CloseProfit;
	///持仓盈亏
	CMoneyType	PositionProfit;
	///可用资金
	CMoneyType	Available;
	///结算准备金
	CMoneyType	Balance;
	///多头占用保证金
	CMoneyType	LongMargin;
	///空头占用保证金
	CMoneyType	ShortMargin;
	///多头冻结的保证金
	CMoneyType	LongFrozenMargin;
	///空头冻结的保证金
	CMoneyType	ShortFrozenMargin;
	///动态权益
	CMoneyType	DynamicRights;
	///风险度
	CMoneyType	Risk;
	///其他费用
	CMoneyType	OtherFee;
	///质押金额
	CMoneyType	Mortgage;
	///币种
	CCurrencyIDType	Currency;
	///总冻结持仓
	CVolumeType	TotalFrozenPos;
	///今日出入金
	CMoneyType	TodayInOut;
	///当日释放保证金
	CMoneyType	ReleaseMargin;
	///浮盈是否可用
	CBoolType	IsProfitCanUse;
	///临时冻结资金
	CMoneyType	ManualFrozen;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(AccountID)
		,
		TYPE_DESC(PreBalance)
		,
		TYPE_DESC(PreAvailable)
		,
		TYPE_DESC(Deposit)
		,
		TYPE_DESC(Withdraw)
		,
		TYPE_DESC(Margin)
		,
		TYPE_DESC(Premium)
		,
		TYPE_DESC(Fee)
		,
		TYPE_DESC(FrozenMargin)
		,
		TYPE_DESC(FrozenPremium)
		,
		TYPE_DESC(FrozenFee)
		,
		TYPE_DESC(CloseProfit)
		,
		TYPE_DESC(PositionProfit)
		,
		TYPE_DESC(Available)
		,
		TYPE_DESC(Balance)
		,
		TYPE_DESC(LongMargin)
		,
		TYPE_DESC(ShortMargin)
		,
		TYPE_DESC(LongFrozenMargin)
		,
		TYPE_DESC(ShortFrozenMargin)
		,
		TYPE_DESC(DynamicRights)
		,
		TYPE_DESC(Risk)
		,
		TYPE_DESC(OtherFee)
		,
		TYPE_DESC(Mortgage)
		,
		TYPE_DESC(Currency)
		,
		TYPE_DESC(TotalFrozenPos)
		,
		TYPE_DESC(TodayInOut)
		,
		TYPE_DESC(ReleaseMargin)
		,
		TYPE_DESC(IsProfitCanUse)
		,
		TYPE_DESC(ManualFrozen)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_ExCapitalData=0x3008;

///分价行情应答
class CMBLMarketDataField
{
public:
	///合约代码
	CInstrumentIDType	InstrumentID;
	///买卖方向
	CDirectionType	Direction;
	///价格
	CPriceType	Price;
	///数量
	CVolumeType	Volume;
	///最后修改时间
	CTimeType	UpdateTime;
	///最后修改毫秒
	CMillisecType	UpdateMillisec;
	TYPE_DESCRIPTOR((
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(Direction)
		,
		TYPE_DESC(Price)
		,
		TYPE_DESC(Volume)
		,
		TYPE_DESC(UpdateTime)
		,
		TYPE_DESC(UpdateMillisec)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_MBLMarketData=0x3106;

///分价行情请求
class CQryMBLMarketDataField
{
public:
	///交易所代码
	CExchangeIDType	ExchangeID;
	///起始合约代码
	CInstrumentIDType	InstIDStart;
	///结束合约代码
	CInstrumentIDType	InstIDEnd;
	///买卖方向
	CDirectionType	Direction;
	///登录经纪公司编号
	CBrokerIDType	LogBrokerID;
	///登录用户代码
	CUserIDType	LogUserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InstIDStart)
		,
		TYPE_DESC(InstIDEnd)
		,
		TYPE_DESC(Direction)
		,
		TYPE_DESC(LogBrokerID)
		,
		TYPE_DESC(LogUserID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryMBLMarketData=0x3107;

///用户
class CUserField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///用户代码
	CUserIDType	UserID;
	///用户登录密码
	CPasswordType	Password;
	///是否活跃
	CIsActiveType	IsActive;
	///用户名称
	CUserNameType	UserName;
	///用户类型
	CUserTypeType	UserType;
	///营业部
	CDepartmentType	Department;
	///授权功能集
	CGrantFuncSetType	GrantFuncSet;
	///是否检查IP和MAC
	CBoolType	CheckIpMacAddr;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(Password)
		,
		TYPE_DESC(IsActive)
		,
		TYPE_DESC(UserName)
		,
		TYPE_DESC(UserType)
		,
		TYPE_DESC(Department)
		,
		TYPE_DESC(GrantFuncSet)
		,
		TYPE_DESC(CheckIpMacAddr)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_User=0x3020;

///用户登录
class CUserLoginField
{
public:
	///交易日
	CDateType	TradingDay;
	///交易用户代码
	CUserIDType	UserID;
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///密码
	CPasswordType	Password;
	///用户端产品信息
	CProductInfoType	UserProductInfo;
	///接口端产品信息
	CProductInfoType	InterfaceProductInfo;
	///协议信息
	CProtocolInfoType	ProtocolInfo;
	///IP地址
	CIPAddressType	IPAddress;
	///Mac地址
	CMacAddressType	MacAddress;
	///数据中心代码
	CDataCenterIDType	DataCenterID;
	///动态密码
	CPasswordType	OneTimePassword;
	///终端IP地址
	CIPAddressType	ClientIPAddress;
	///登录成功时间
	CTimeType	LoginTime;
	///最大报单本地编号
	CUserOrderLocalIDType	MaxOrderLocalID;
	///交易系统名称
	CTradingSystemNameType	TradingSystemName;
	///用户类型
	CUserTypeType	UserType;
	///最大通讯量
	CCommFluxType	MaxCommFlux;
	///会话编号
	CSessionIDType	SessionID;
	///前置编号
	CFrontIDType	FrontID;
	///Socket编号
	CNumberType	SockID;
	///客户端交易日
	CDateType	ClientTradingDay;
	///写心跳超时时间
	CNumberType	Heartbeat;
	///对话流缓存序号
	CNumberType	DialogSeqno;
	///私有流缓存序号
	CNumberType	PrivateSeqno;
	///公有流缓存序号
	CNumberType	PublicSeqno;
	///生命周期号
	CSequenceNoType	LifeCycleID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(Password)
		,
		TYPE_DESC(UserProductInfo)
		,
		TYPE_DESC(InterfaceProductInfo)
		,
		TYPE_DESC(ProtocolInfo)
		,
		TYPE_DESC(IPAddress)
		,
		TYPE_DESC(MacAddress)
		,
		TYPE_DESC(DataCenterID)
		,
		TYPE_DESC(OneTimePassword)
		,
		TYPE_DESC(ClientIPAddress)
		,
		TYPE_DESC(LoginTime)
		,
		TYPE_DESC(MaxOrderLocalID)
		,
		TYPE_DESC(TradingSystemName)
		,
		TYPE_DESC(UserType)
		,
		TYPE_DESC(MaxCommFlux)
		,
		TYPE_DESC(SessionID)
		,
		TYPE_DESC(FrontID)
		,
		TYPE_DESC(SockID)
		,
		TYPE_DESC(ClientTradingDay)
		,
		TYPE_DESC(Heartbeat)
		,
		TYPE_DESC(DialogSeqno)
		,
		TYPE_DESC(PrivateSeqno)
		,
		TYPE_DESC(PublicSeqno)
		,
		TYPE_DESC(LifeCycleID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_UserLogin=0x3021;

///用户会话
class CUserSessionField
{
public:
	///经纪公司代码
	CBrokerIDType	BrokerID;
	///交易用户代码
	CUserIDType	UserID;
	///交易用户类型
	CUserTypeType	UserType;
	///会话编号
	CSessionIDType	SessionID;
	///前置编号
	CFrontIDType	FrontID;
	///登录时间
	CTimeType	LoginTime;
	///IP地址
	CIPAddressType	IPAddress;
	///Mac地址
	CMacAddressType	MacAddress;
	///用户端产品信息
	CProductInfoType	UserProductInfo;
	///接口端产品信息
	CProductInfoType	InterfaceProductInfo;
	///协议信息
	CProtocolInfoType	ProtocolInfo;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(UserType)
		,
		TYPE_DESC(SessionID)
		,
		TYPE_DESC(FrontID)
		,
		TYPE_DESC(LoginTime)
		,
		TYPE_DESC(IPAddress)
		,
		TYPE_DESC(MacAddress)
		,
		TYPE_DESC(UserProductInfo)
		,
		TYPE_DESC(InterfaceProductInfo)
		,
		TYPE_DESC(ProtocolInfo)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_UserSession=0x3022;

///用户登录退出
class CUserLogoutField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易用户代码
	CUserIDType	UserID;
	///Session退出原因
	CNumberType	LogoutReason;
	///前置编号
	CFrontIDType	FrontID;
	///会话编号
	CSessionIDType	SessionID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(LogoutReason)
		,
		TYPE_DESC(FrontID)
		,
		TYPE_DESC(SessionID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_UserLogout=0x3023;

///席位
class CSeatField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易API中的序号
	CNumberType	APIID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///会员编号
	CParticipantIDType	ParticipantID;
	///席位号
	CSeatIDType	SeatID;
	///席位密码
	CPasswordType	SeatPassword;
	///席位连接api类型
	CApiLinkTypeType	ApiLinkType;
	///是否接收回报
	CBoolType	RecvRtn;
	///席位密码(是否接收所有席位回报)
	CBoolType	MainSeat;
	///是否查询基础信息
	CBoolType	QueryBase;
	///是否查询持仓
	CBoolType	QueryPosition;
	///收取回报的方式
	CNumberType	ResumeType;
	///心跳时间(秒)
	CNumberType	Heartbeat;
	///是否活跃
	CBoolType	IsActive;
	///是否检查资金持仓风控
	CBoolType	RiskCheck;
	///连接地址
	CFrontAddrType	FrontAddr;
	///席位状态
	CSeatStatusType	SeatStatus;
	///本地报单编号
	COrderLocalIDType	OrderLocalID;
	///连接对应的Broker(guofu/sucden/fcstone)
	CBrokerIDType	LinkBrokerID;
	///需要席位操作的交易日期
	CTradingDayType	TradingDay;
	///是否需要检查交易日期
	CBoolType	CheckTradingDay;
	///报盘自定义的属性
	CSeatCustomType	Custom;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(APIID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(ParticipantID)
		,
		TYPE_DESC(SeatID)
		,
		TYPE_DESC(SeatPassword)
		,
		TYPE_DESC(ApiLinkType)
		,
		TYPE_DESC(RecvRtn)
		,
		TYPE_DESC(MainSeat)
		,
		TYPE_DESC(QueryBase)
		,
		TYPE_DESC(QueryPosition)
		,
		TYPE_DESC(ResumeType)
		,
		TYPE_DESC(Heartbeat)
		,
		TYPE_DESC(IsActive)
		,
		TYPE_DESC(RiskCheck)
		,
		TYPE_DESC(FrontAddr)
		,
		TYPE_DESC(SeatStatus)
		,
		TYPE_DESC(OrderLocalID)
		,
		TYPE_DESC(LinkBrokerID)
		,
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(CheckTradingDay)
		,
		TYPE_DESC(Custom)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_Seat=0x3024;

///用户交易权限
class CUserTradingRightField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///用户代码
	CUserIDType	UserID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///合约交易权限
	CTradingRightType	TradingRight;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(TradingRight)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_UserTradingRight=0x3025;

///用户口令修改
class CUserPasswordUpdateField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易用户代码
	CUserIDType	UserID;
	///旧密码
	CPasswordType	OldPassword;
	///新密码
	CPasswordType	NewPassword;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(OldPassword)
		,
		TYPE_DESC(NewPassword)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_UserPasswordUpdate=0x3027;

///强制用户退出
class CForceUserExitField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易用户代码
	CUserIDType	UserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_ForceUserExit=0x3028;

///登陆通知
class CLoginInfoField
{
public:
	///会员编号
	CParticipantIDType	ParticipantID;
	///席位编码
	CSeatIDType	SeatID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///席位本地报单号
	COrderLocalIDType	OrderLocalID;
	///生命周期号
	CSequenceNoType	LifeCycleID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ParticipantID)
		,
		TYPE_DESC(SeatID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(OrderLocalID)
		,
		TYPE_DESC(LifeCycleID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_LoginInfo=0x3029;

///输入报单
class CInputOrderField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///系统报单编号
	COrderSysIDType	OrderSysID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///用户代码
	CUserIDType	UserID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///用户本地报单号
	CUserOrderLocalIDType	UserOrderLocalID;
	///价格类型
	COrderPriceTypeType	OrderPriceType;
	///买卖方向
	CDirectionType	Direction;
	///开平标志
	COffsetFlagType	OffsetFlag;
	///投机套保标志
	CHedgeFlagType	HedgeFlag;
	///价格
	CPriceType	LimitPrice;
	///数量
	CVolumeType	Volume;
	///有效期类型
	CTimeConditionType	TimeCondition;
	///GTD日期
	CDateType	GTDDate;
	///成交量类型
	CVolumeConditionType	VolumeCondition;
	///最小成交量
	CVolumeType	MinVolume;
	///止损价
	CPriceType	StopPrice;
	///强平原因
	CForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	CBoolType	IsAutoSuspend;
	///业务单元
	CBusinessUnitType	BusinessUnit;
	///用户自定义域
	CCustomType	UserCustom;
	///营业部代码
	CBranchIDType	BranchID;
	///记录编号
	CSequenceNoType	RecNum;
	///业务类别
	CBusinessTypeType	BusinessType;
	///交易日
	CTradingDayType	TradingDay;
	///会员编号
	CParticipantIDType	ParticipantID;
	///客户号
	CClientIDType	ClientID;
	///下单席位号
	CSeatIDType	SeatID;
	///插入时间
	CTimeType	InsertTime;
	///本地报单编号
	COrderLocalIDType	OrderLocalID;
	///报单来源
	COrderSourceType	OrderSource;
	///报单状态
	COrderStatusType	OrderStatus;
	///撤销时间
	CTimeType	CancelTime;
	///撤单用户编号
	CUserIDType	CancelUserID;
	///今成交数量
	CVolumeType	VolumeTraded;
	///剩余数量
	CVolumeType	VolumeRemain;
	///前置编号
	CFrontIDType	FrontID;
	///会话编号
	CSessionIDType	SessionID;
	///冻结手续费
	CMoneyType	FrozenFee;
	///冻结的保证金
	CMoneyType	FrozenMargin;
	///期权权利金收支
	CMoneyType	FrozenPremium;
	///资金帐号
	CAccountIDType	AccountID;
	///下单用户编号
	CUserIDType	OrderUserID;
	///交易类型
	CTradeTypeType	TradeType;
	///处理标志
	CDealFlagType	DealFlag;
	///已成交佣金
	CMoneyType	TradeCommision;
	///成交金额
	CMoneyType	TradeAmnt;
	///撤单数量
	CVolumeType	CancleVolume;
	///请求编号
	CRequestIDType	RequestID;
	///通道对应的APIID
	CNumberType	APIID;
	///下单IP地址
	CIPAddressType	IPAddress;
	///下单MAC地址
	CMacAddressType	MacAddress;
	///Ftdengine接受下层时间戳
	CILocalTimeType	FTdRecvDown;
	///接受下层时间戳
	CILocalTimeType	CoreRecvDown;
	///发送上层时间戳
	CILocalTimeType	CoreSendUp;
	///接受上层时间戳
	CILocalTimeType	CoreRecvUp;
	///发送下层时间戳
	CILocalTimeType	CoreSendDown;
	///Ftdengine接受下层时间戳
	CILocalTimeType	FTdSendDown;
	///保证金组合类型
	CClientMarginCombTypeType	MarginCombType;
	///合约组代码
	CInstrumentGroupIDType	InstrumentGroupID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(OrderSysID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(UserOrderLocalID)
		,
		TYPE_DESC(OrderPriceType)
		,
		TYPE_DESC(Direction)
		,
		TYPE_DESC(OffsetFlag)
		,
		TYPE_DESC(HedgeFlag)
		,
		TYPE_DESC(LimitPrice)
		,
		TYPE_DESC(Volume)
		,
		TYPE_DESC(TimeCondition)
		,
		TYPE_DESC(GTDDate)
		,
		TYPE_DESC(VolumeCondition)
		,
		TYPE_DESC(MinVolume)
		,
		TYPE_DESC(StopPrice)
		,
		TYPE_DESC(ForceCloseReason)
		,
		TYPE_DESC(IsAutoSuspend)
		,
		TYPE_DESC(BusinessUnit)
		,
		TYPE_DESC(UserCustom)
		,
		TYPE_DESC(BranchID)
		,
		TYPE_DESC(RecNum)
		,
		TYPE_DESC(BusinessType)
		,
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(ParticipantID)
		,
		TYPE_DESC(ClientID)
		,
		TYPE_DESC(SeatID)
		,
		TYPE_DESC(InsertTime)
		,
		TYPE_DESC(OrderLocalID)
		,
		TYPE_DESC(OrderSource)
		,
		TYPE_DESC(OrderStatus)
		,
		TYPE_DESC(CancelTime)
		,
		TYPE_DESC(CancelUserID)
		,
		TYPE_DESC(VolumeTraded)
		,
		TYPE_DESC(VolumeRemain)
		,
		TYPE_DESC(FrontID)
		,
		TYPE_DESC(SessionID)
		,
		TYPE_DESC(FrozenFee)
		,
		TYPE_DESC(FrozenMargin)
		,
		TYPE_DESC(FrozenPremium)
		,
		TYPE_DESC(AccountID)
		,
		TYPE_DESC(OrderUserID)
		,
		TYPE_DESC(TradeType)
		,
		TYPE_DESC(DealFlag)
		,
		TYPE_DESC(TradeCommision)
		,
		TYPE_DESC(TradeAmnt)
		,
		TYPE_DESC(CancleVolume)
		,
		TYPE_DESC(RequestID)
		,
		TYPE_DESC(APIID)
		,
		TYPE_DESC(IPAddress)
		,
		TYPE_DESC(MacAddress)
		,
		TYPE_DESC(FTdRecvDown)
		,
		TYPE_DESC(CoreRecvDown)
		,
		TYPE_DESC(CoreSendUp)
		,
		TYPE_DESC(CoreRecvUp)
		,
		TYPE_DESC(CoreSendDown)
		,
		TYPE_DESC(FTdSendDown)
		,
		TYPE_DESC(MarginCombType)
		,
		TYPE_DESC(InstrumentGroupID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InputOrder=0x3030;

///报单操作
class COrderActionField
{
public:
	///交易所代码
	CExchangeIDType	ExchangeID;
	///报单编号
	COrderSysIDType	OrderSysID;
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///用户代码
	CUserIDType	UserID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///本次撤单操作的本地编号
	CUserOrderLocalIDType	UserOrderActionLocalID;
	///被撤订单的本地报单编号
	CUserOrderLocalIDType	UserOrderLocalID;
	///报单操作标志
	CActionFlagType	ActionFlag;
	///价格
	CPriceType	LimitPrice;
	///数量变化
	CVolumeType	VolumeChange;
	///记录编号
	CSequenceNoType	RecNum;
	///前置编号
	CFrontIDType	FrontID;
	///会话编号
	CSessionIDType	SessionID;
	///用户自定义域
	CCustomType	UserCustom;
	///下单席位号
	CSeatIDType	SeatID;
	///操作本地编号
	COrderLocalIDType	ActionLocalID;
	///客户代码
	CClientIDType	ClientID;
	///会员代码
	CParticipantIDType	ParticipantID;
	///撤销时间
	CTimeType	CancelTime;
	///操作来源
	CActionSourceType	ActionSource;
	///是否可以参加交易
	CBoolType	Tradable;
	///本地报单编号
	COrderLocalIDType	OrderLocalID;
	///伪造Rtn
	CBoolType	IsForgeRtn;
	///通道对应的APIID
	CNumberType	APIID;
	///下单IP地址
	CIPAddressType	IPAddress;
	///下单MAC地址
	CMacAddressType	MacAddress;
	///撤单对应的报单类别
	COrderActionTypeType	OrderActionType;
	///报单批次号
	COrderSysIDType	OrderBatchNo;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(OrderSysID)
		,
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(UserOrderActionLocalID)
		,
		TYPE_DESC(UserOrderLocalID)
		,
		TYPE_DESC(ActionFlag)
		,
		TYPE_DESC(LimitPrice)
		,
		TYPE_DESC(VolumeChange)
		,
		TYPE_DESC(RecNum)
		,
		TYPE_DESC(FrontID)
		,
		TYPE_DESC(SessionID)
		,
		TYPE_DESC(UserCustom)
		,
		TYPE_DESC(SeatID)
		,
		TYPE_DESC(ActionLocalID)
		,
		TYPE_DESC(ClientID)
		,
		TYPE_DESC(ParticipantID)
		,
		TYPE_DESC(CancelTime)
		,
		TYPE_DESC(ActionSource)
		,
		TYPE_DESC(Tradable)
		,
		TYPE_DESC(OrderLocalID)
		,
		TYPE_DESC(IsForgeRtn)
		,
		TYPE_DESC(APIID)
		,
		TYPE_DESC(IPAddress)
		,
		TYPE_DESC(MacAddress)
		,
		TYPE_DESC(OrderActionType)
		,
		TYPE_DESC(OrderBatchNo)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_OrderAction=0x3031;

///成交
class CTradeField
{
public:
	///交易日
	CTradingDayType	TradingDay;
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///会员编号
	CParticipantIDType	ParticipantID;
	///下单席位号
	CSeatIDType	SeatID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///客户号
	CClientIDType	ClientID;
	///用户编号
	CUserIDType	UserID;
	///成交编号
	CTradeIDType	TradeID;
	///报单编号
	COrderSysIDType	OrderSysID;
	///本地报单编号
	CUserOrderLocalIDType	UserOrderLocalID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///买卖方向
	CDirectionType	Direction;
	///开平标志
	COffsetFlagType	OffsetFlag;
	///投机套保标志
	CHedgeFlagType	HedgeFlag;
	///成交价格
	CPriceType	TradePrice;
	///成交数量
	CVolumeType	TradeVolume;
	///成交时间
	CTimeType	TradeTime;
	///清算会员编号
	CParticipantIDType	ClearingPartID;
	///成交金额
	CMoneyType	TradeAmnt;
	///记录编号
	CSequenceNoType	RecNum;
	///交易类型
	CTradeTypeType	TradeType;
	///佣金
	CMoneyType	Commision;
	///印花税
	CMoneyType	StampTax;
	///过户费
	CMoneyType	TransferFee;
	///手续费
	CMoneyType	UsedFee;
	///占用的保证金
	CMoneyType	UsedMargin;
	///占用权利金
	CMoneyType	Premium;
	///资金帐号
	CAccountIDType	AccountID;
	///下单用户编号
	CUserIDType	OrderUserID;
	///本地报单编号
	COrderLocalIDType	OrderLocalID;
	///伪造Rtn
	CBoolType	IsForgeRtn;
	///业务类别
	CBusinessTypeType	BusinessType;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(ParticipantID)
		,
		TYPE_DESC(SeatID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(ClientID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(TradeID)
		,
		TYPE_DESC(OrderSysID)
		,
		TYPE_DESC(UserOrderLocalID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(Direction)
		,
		TYPE_DESC(OffsetFlag)
		,
		TYPE_DESC(HedgeFlag)
		,
		TYPE_DESC(TradePrice)
		,
		TYPE_DESC(TradeVolume)
		,
		TYPE_DESC(TradeTime)
		,
		TYPE_DESC(ClearingPartID)
		,
		TYPE_DESC(TradeAmnt)
		,
		TYPE_DESC(RecNum)
		,
		TYPE_DESC(TradeType)
		,
		TYPE_DESC(Commision)
		,
		TYPE_DESC(StampTax)
		,
		TYPE_DESC(TransferFee)
		,
		TYPE_DESC(UsedFee)
		,
		TYPE_DESC(UsedMargin)
		,
		TYPE_DESC(Premium)
		,
		TYPE_DESC(AccountID)
		,
		TYPE_DESC(OrderUserID)
		,
		TYPE_DESC(OrderLocalID)
		,
		TYPE_DESC(IsForgeRtn)
		,
		TYPE_DESC(BusinessType)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_Trade=0x3032;

///报单
class COrderField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///系统报单编号
	COrderSysIDType	OrderSysID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///用户代码
	CUserIDType	UserID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///用户本地报单号
	CUserOrderLocalIDType	UserOrderLocalID;
	///价格类型
	COrderPriceTypeType	OrderPriceType;
	///买卖方向
	CDirectionType	Direction;
	///开平标志
	COffsetFlagType	OffsetFlag;
	///投机套保标志
	CHedgeFlagType	HedgeFlag;
	///价格
	CPriceType	LimitPrice;
	///数量
	CVolumeType	Volume;
	///有效期类型
	CTimeConditionType	TimeCondition;
	///GTD日期
	CDateType	GTDDate;
	///成交量类型
	CVolumeConditionType	VolumeCondition;
	///最小成交量
	CVolumeType	MinVolume;
	///止损价
	CPriceType	StopPrice;
	///强平原因
	CForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	CBoolType	IsAutoSuspend;
	///业务单元
	CBusinessUnitType	BusinessUnit;
	///用户自定义域
	CCustomType	UserCustom;
	///营业部代码
	CBranchIDType	BranchID;
	///记录编号
	CSequenceNoType	RecNum;
	///业务类别
	CBusinessTypeType	BusinessType;
	///交易日
	CTradingDayType	TradingDay;
	///会员编号
	CParticipantIDType	ParticipantID;
	///客户号
	CClientIDType	ClientID;
	///下单席位号
	CSeatIDType	SeatID;
	///插入时间
	CTimeType	InsertTime;
	///本地报单编号
	COrderLocalIDType	OrderLocalID;
	///报单来源
	COrderSourceType	OrderSource;
	///报单状态
	COrderStatusType	OrderStatus;
	///撤销时间
	CTimeType	CancelTime;
	///撤单用户编号
	CUserIDType	CancelUserID;
	///今成交数量
	CVolumeType	VolumeTraded;
	///剩余数量
	CVolumeType	VolumeRemain;
	///前置编号
	CFrontIDType	FrontID;
	///会话编号
	CSessionIDType	SessionID;
	///冻结手续费
	CMoneyType	FrozenFee;
	///冻结的保证金
	CMoneyType	FrozenMargin;
	///期权权利金收支
	CMoneyType	FrozenPremium;
	///资金帐号
	CAccountIDType	AccountID;
	///下单用户编号
	CUserIDType	OrderUserID;
	///交易类型
	CTradeTypeType	TradeType;
	///处理标志
	CDealFlagType	DealFlag;
	///已成交佣金
	CMoneyType	TradeCommision;
	///成交金额
	CMoneyType	TradeAmnt;
	///撤单数量
	CVolumeType	CancleVolume;
	///请求编号
	CRequestIDType	RequestID;
	///通道对应的APIID
	CNumberType	APIID;
	///下单IP地址
	CIPAddressType	IPAddress;
	///下单MAC地址
	CMacAddressType	MacAddress;
	///Ftdengine接受下层时间戳
	CILocalTimeType	FTdRecvDown;
	///接受下层时间戳
	CILocalTimeType	CoreRecvDown;
	///发送上层时间戳
	CILocalTimeType	CoreSendUp;
	///接受上层时间戳
	CILocalTimeType	CoreRecvUp;
	///发送下层时间戳
	CILocalTimeType	CoreSendDown;
	///Ftdengine接受下层时间戳
	CILocalTimeType	FTdSendDown;
	///保证金组合类型
	CClientMarginCombTypeType	MarginCombType;
	///合约组代码
	CInstrumentGroupIDType	InstrumentGroupID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(OrderSysID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(UserOrderLocalID)
		,
		TYPE_DESC(OrderPriceType)
		,
		TYPE_DESC(Direction)
		,
		TYPE_DESC(OffsetFlag)
		,
		TYPE_DESC(HedgeFlag)
		,
		TYPE_DESC(LimitPrice)
		,
		TYPE_DESC(Volume)
		,
		TYPE_DESC(TimeCondition)
		,
		TYPE_DESC(GTDDate)
		,
		TYPE_DESC(VolumeCondition)
		,
		TYPE_DESC(MinVolume)
		,
		TYPE_DESC(StopPrice)
		,
		TYPE_DESC(ForceCloseReason)
		,
		TYPE_DESC(IsAutoSuspend)
		,
		TYPE_DESC(BusinessUnit)
		,
		TYPE_DESC(UserCustom)
		,
		TYPE_DESC(BranchID)
		,
		TYPE_DESC(RecNum)
		,
		TYPE_DESC(BusinessType)
		,
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(ParticipantID)
		,
		TYPE_DESC(ClientID)
		,
		TYPE_DESC(SeatID)
		,
		TYPE_DESC(InsertTime)
		,
		TYPE_DESC(OrderLocalID)
		,
		TYPE_DESC(OrderSource)
		,
		TYPE_DESC(OrderStatus)
		,
		TYPE_DESC(CancelTime)
		,
		TYPE_DESC(CancelUserID)
		,
		TYPE_DESC(VolumeTraded)
		,
		TYPE_DESC(VolumeRemain)
		,
		TYPE_DESC(FrontID)
		,
		TYPE_DESC(SessionID)
		,
		TYPE_DESC(FrozenFee)
		,
		TYPE_DESC(FrozenMargin)
		,
		TYPE_DESC(FrozenPremium)
		,
		TYPE_DESC(AccountID)
		,
		TYPE_DESC(OrderUserID)
		,
		TYPE_DESC(TradeType)
		,
		TYPE_DESC(DealFlag)
		,
		TYPE_DESC(TradeCommision)
		,
		TYPE_DESC(TradeAmnt)
		,
		TYPE_DESC(CancleVolume)
		,
		TYPE_DESC(RequestID)
		,
		TYPE_DESC(APIID)
		,
		TYPE_DESC(IPAddress)
		,
		TYPE_DESC(MacAddress)
		,
		TYPE_DESC(FTdRecvDown)
		,
		TYPE_DESC(CoreRecvDown)
		,
		TYPE_DESC(CoreSendUp)
		,
		TYPE_DESC(CoreRecvUp)
		,
		TYPE_DESC(CoreSendDown)
		,
		TYPE_DESC(FTdSendDown)
		,
		TYPE_DESC(MarginCombType)
		,
		TYPE_DESC(InstrumentGroupID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_Order=0x3033;

///市场行情
class CMarketDataField
{
public:
	///交易日
	CTradingDayType	TradingDay;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///今开盘
	CPriceType	OpenPrice;
	///最高价
	CPriceType	HighestPrice;
	///最低价
	CPriceType	LowestPrice;
	///最新价
	CPriceType	LastPrice;
	///数量
	CVolumeType	Volume;
	///成交金额
	CMoneyType	Turnover;
	///跌停板价
	CPriceType	LowerLimitPrice;
	///涨停板价
	CPriceType	UpperLimitPrice;
	///持仓量
	CVolumeType	OpenInterest;
	///昨收盘
	CPriceType	PreClosePrice;
	///昨持仓量
	CVolumeType	PreOpenInterest;
	///昨结算
	CPriceType	PreSettlementPrice;
	///今结算
	CPriceType	SettlementPrice;
	///最后修改毫秒
	CMillisecType	UpdateMillisec;
	///最后修改时间
	CTimeType	UpdateTime;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(OpenPrice)
		,
		TYPE_DESC(HighestPrice)
		,
		TYPE_DESC(LowestPrice)
		,
		TYPE_DESC(LastPrice)
		,
		TYPE_DESC(Volume)
		,
		TYPE_DESC(Turnover)
		,
		TYPE_DESC(LowerLimitPrice)
		,
		TYPE_DESC(UpperLimitPrice)
		,
		TYPE_DESC(OpenInterest)
		,
		TYPE_DESC(PreClosePrice)
		,
		TYPE_DESC(PreOpenInterest)
		,
		TYPE_DESC(PreSettlementPrice)
		,
		TYPE_DESC(SettlementPrice)
		,
		TYPE_DESC(UpdateMillisec)
		,
		TYPE_DESC(UpdateTime)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_MarketData=0x3034;

///行情最新成交属性
class CMarketDataLastMatchField
{
public:
	///交易所代码
	CExchangeIDType	ExchangeID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///最新价
	CPriceType	LastPrice;
	///数量
	CVolumeType	Volume;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(LastPrice)
		,
		TYPE_DESC(Volume)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_MarketDataLastMatch=0x3035;

///市场深度行情
class CDepthMarketDataField
{
public:
	///交易日
	CTradingDayType	TradingDay;
	///结算组代码
	CSettlementGroupIDType	SettlementGroupID;
	///结算编号
	CSettlementIDType	SettlementID;
	///昨结算
	CPriceType	PreSettlementPrice;
	///昨收盘
	CPriceType	PreClosePrice;
	///昨持仓量
	CLargeVolumeType	PreOpenInterest;
	///昨虚实度
	CRatioType	PreDelta;
	///今开盘
	CPriceType	OpenPrice;
	///最高价
	CPriceType	HighestPrice;
	///最低价
	CPriceType	LowestPrice;
	///今收盘
	CPriceType	ClosePrice;
	///涨停板价
	CPriceType	UpperLimitPrice;
	///跌停板价
	CPriceType	LowerLimitPrice;
	///今结算
	CPriceType	SettlementPrice;
	///今虚实度
	CRatioType	CurrDelta;
	///最新价
	CPriceType	LastPrice;
	///数量
	CVolumeType	Volume;
	///成交金额
	CMoneyType	Turnover;
	///持仓量
	CLargeVolumeType	OpenInterest;
	///申买价一
	CPriceType	BidPrice1;
	///申买量一
	CVolumeType	BidVolume1;
	///申卖价一
	CPriceType	AskPrice1;
	///申卖量一
	CVolumeType	AskVolume1;
	///申买价二
	CPriceType	BidPrice2;
	///申买量二
	CVolumeType	BidVolume2;
	///申买价三
	CPriceType	BidPrice3;
	///申买量三
	CVolumeType	BidVolume3;
	///申卖价二
	CPriceType	AskPrice2;
	///申卖量二
	CVolumeType	AskVolume2;
	///申卖价三
	CPriceType	AskPrice3;
	///申卖量三
	CVolumeType	AskVolume3;
	///申买价四
	CPriceType	BidPrice4;
	///申买量四
	CVolumeType	BidVolume4;
	///申买价五
	CPriceType	BidPrice5;
	///申买量五
	CVolumeType	BidVolume5;
	///申卖价四
	CPriceType	AskPrice4;
	///申卖量四
	CVolumeType	AskVolume4;
	///申卖价五
	CPriceType	AskPrice5;
	///申卖量五
	CVolumeType	AskVolume5;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///最后修改时间
	CTimeType	UpdateTime;
	///最后修改毫秒
	CMillisecType	UpdateMillisec;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///申卖价六
	CPriceType	AskPrice6;
	///申卖量六
	CVolumeType	AskVolume6;
	///申卖价七
	CPriceType	AskPrice7;
	///申卖量七
	CVolumeType	AskVolume7;
	///申卖价八
	CPriceType	AskPrice8;
	///申卖量八
	CVolumeType	AskVolume8;
	///申卖价九
	CPriceType	AskPrice9;
	///申卖量九
	CVolumeType	AskVolume9;
	///申买价六
	CPriceType	BidPrice6;
	///申买量六
	CVolumeType	BidVolume6;
	///申买价七
	CPriceType	BidPrice7;
	///申买量七
	CVolumeType	BidVolume7;
	///申买价八
	CPriceType	BidPrice8;
	///申买量八
	CVolumeType	BidVolume8;
	///申买价九
	CPriceType	BidPrice9;
	///申买量九
	CVolumeType	BidVolume9;
	///申卖价十
	CPriceType	AskPrice10;
	///申卖量十
	CVolumeType	AskVolume10;
	///申买价十
	CPriceType	BidPrice10;
	///申买量十
	CVolumeType	BidVolume10;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(SettlementGroupID)
		,
		TYPE_DESC(SettlementID)
		,
		TYPE_DESC(PreSettlementPrice)
		,
		TYPE_DESC(PreClosePrice)
		,
		TYPE_DESC(PreOpenInterest)
		,
		TYPE_DESC(PreDelta)
		,
		TYPE_DESC(OpenPrice)
		,
		TYPE_DESC(HighestPrice)
		,
		TYPE_DESC(LowestPrice)
		,
		TYPE_DESC(ClosePrice)
		,
		TYPE_DESC(UpperLimitPrice)
		,
		TYPE_DESC(LowerLimitPrice)
		,
		TYPE_DESC(SettlementPrice)
		,
		TYPE_DESC(CurrDelta)
		,
		TYPE_DESC(LastPrice)
		,
		TYPE_DESC(Volume)
		,
		TYPE_DESC(Turnover)
		,
		TYPE_DESC(OpenInterest)
		,
		TYPE_DESC(BidPrice1)
		,
		TYPE_DESC(BidVolume1)
		,
		TYPE_DESC(AskPrice1)
		,
		TYPE_DESC(AskVolume1)
		,
		TYPE_DESC(BidPrice2)
		,
		TYPE_DESC(BidVolume2)
		,
		TYPE_DESC(BidPrice3)
		,
		TYPE_DESC(BidVolume3)
		,
		TYPE_DESC(AskPrice2)
		,
		TYPE_DESC(AskVolume2)
		,
		TYPE_DESC(AskPrice3)
		,
		TYPE_DESC(AskVolume3)
		,
		TYPE_DESC(BidPrice4)
		,
		TYPE_DESC(BidVolume4)
		,
		TYPE_DESC(BidPrice5)
		,
		TYPE_DESC(BidVolume5)
		,
		TYPE_DESC(AskPrice4)
		,
		TYPE_DESC(AskVolume4)
		,
		TYPE_DESC(AskPrice5)
		,
		TYPE_DESC(AskVolume5)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(UpdateTime)
		,
		TYPE_DESC(UpdateMillisec)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(AskPrice6)
		,
		TYPE_DESC(AskVolume6)
		,
		TYPE_DESC(AskPrice7)
		,
		TYPE_DESC(AskVolume7)
		,
		TYPE_DESC(AskPrice8)
		,
		TYPE_DESC(AskVolume8)
		,
		TYPE_DESC(AskPrice9)
		,
		TYPE_DESC(AskVolume9)
		,
		TYPE_DESC(BidPrice6)
		,
		TYPE_DESC(BidVolume6)
		,
		TYPE_DESC(BidPrice7)
		,
		TYPE_DESC(BidVolume7)
		,
		TYPE_DESC(BidPrice8)
		,
		TYPE_DESC(BidVolume8)
		,
		TYPE_DESC(BidPrice9)
		,
		TYPE_DESC(BidVolume9)
		,
		TYPE_DESC(AskPrice10)
		,
		TYPE_DESC(AskVolume10)
		,
		TYPE_DESC(BidPrice10)
		,
		TYPE_DESC(BidVolume10)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_DepthMarketData=0x3036;

///行情查询应答
class CRspMarketDataField
{
public:
	///交易所代码
	CExchangeIDType	ExchangeID;
	///交易日
	CTradingDayType	TradingDay;
	///结算组代码
	CSettlementGroupIDType	SettlementGroupID;
	///结算编号
	CSettlementIDType	SettlementID;
	///昨结算
	CPriceType	PreSettlementPrice;
	///昨收盘
	CPriceType	PreClosePrice;
	///昨持仓量
	CLargeVolumeType	PreOpenInterest;
	///昨虚实度
	CRatioType	PreDelta;
	///今开盘
	CPriceType	OpenPrice;
	///最高价
	CPriceType	HighestPrice;
	///最低价
	CPriceType	LowestPrice;
	///今收盘
	CPriceType	ClosePrice;
	///涨停板价
	CPriceType	UpperLimitPrice;
	///跌停板价
	CPriceType	LowerLimitPrice;
	///今结算
	CPriceType	SettlementPrice;
	///今虚实度
	CRatioType	CurrDelta;
	///最新价
	CPriceType	LastPrice;
	///数量
	CVolumeType	Volume;
	///成交金额
	CMoneyType	Turnover;
	///持仓量
	CLargeVolumeType	OpenInterest;
	///申买价一
	CPriceType	BidPrice1;
	///申买量一
	CVolumeType	BidVolume1;
	///申卖价一
	CPriceType	AskPrice1;
	///申卖量一
	CVolumeType	AskVolume1;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///最后修改时间
	CTimeType	UpdateTime;
	///最后修改毫秒
	CMillisecType	UpdateMillisec;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(SettlementGroupID)
		,
		TYPE_DESC(SettlementID)
		,
		TYPE_DESC(PreSettlementPrice)
		,
		TYPE_DESC(PreClosePrice)
		,
		TYPE_DESC(PreOpenInterest)
		,
		TYPE_DESC(PreDelta)
		,
		TYPE_DESC(OpenPrice)
		,
		TYPE_DESC(HighestPrice)
		,
		TYPE_DESC(LowestPrice)
		,
		TYPE_DESC(ClosePrice)
		,
		TYPE_DESC(UpperLimitPrice)
		,
		TYPE_DESC(LowerLimitPrice)
		,
		TYPE_DESC(SettlementPrice)
		,
		TYPE_DESC(CurrDelta)
		,
		TYPE_DESC(LastPrice)
		,
		TYPE_DESC(Volume)
		,
		TYPE_DESC(Turnover)
		,
		TYPE_DESC(OpenInterest)
		,
		TYPE_DESC(BidPrice1)
		,
		TYPE_DESC(BidVolume1)
		,
		TYPE_DESC(AskPrice1)
		,
		TYPE_DESC(AskVolume1)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(UpdateTime)
		,
		TYPE_DESC(UpdateMillisec)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_RspMarketData=0x3037;

///报单查询
class CQryOrderField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///用户代码
	CUserIDType	UserID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///报单编号
	COrderSysIDType	OrderSysID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///登录经纪公司编号
	CBrokerIDType	LogBrokerID;
	///登录用户代码
	CUserIDType	LogUserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(OrderSysID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(LogBrokerID)
		,
		TYPE_DESC(LogUserID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryOrder=0x3040;

///错单查询
class CQryOrderInsertFailedField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///用户代码
	CUserIDType	UserID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///报单编号
	COrderSysIDType	OrderSysID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///登录经纪公司编号
	CBrokerIDType	LogBrokerID;
	///登录用户代码
	CUserIDType	LogUserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(OrderSysID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(LogBrokerID)
		,
		TYPE_DESC(LogUserID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryOrderInsertFailed=0x3041;

///成交查询
class CQryTradeField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///用户代码
	CUserIDType	UserID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///成交编号
	CTradeIDType	TradeID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///登录经纪公司编号
	CBrokerIDType	LogBrokerID;
	///登录用户代码
	CUserIDType	LogUserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(TradeID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(LogBrokerID)
		,
		TYPE_DESC(LogUserID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryTrade=0x3042;

///投资者查询
class CQryInvestorField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///用户代码
	CUserIDType	UserID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///登录经纪公司编号
	CBrokerIDType	LogBrokerID;
	///登录用户代码
	CUserIDType	LogUserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(LogBrokerID)
		,
		TYPE_DESC(LogUserID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInvestor=0x3043;

///投资者资金查询
class CQryInvestorAccountField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///用户代码
	CUserIDType	UserID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///登录经纪公司编号
	CBrokerIDType	LogBrokerID;
	///登录用户代码
	CUserIDType	LogUserID;
	///席位号
	CSeatIDType	SeatID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(LogBrokerID)
		,
		TYPE_DESC(LogUserID)
		,
		TYPE_DESC(SeatID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInvestorAccount=0x3044;

///合约查询
class CQryInstrumentField
{
public:
	///交易所代码
	CExchangeIDType	ExchangeID;
	///品种代码
	CProductIDType	ProductID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(ProductID)
		,
		TYPE_DESC(InstrumentID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInstrument=0x3045;

///用户查询
class CQryUserField
{
public:
	///交易用户代码
	CUserIDType	StartUserID;
	///交易用户代码
	CUserIDType	EndUserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(StartUserID)
		,
		TYPE_DESC(EndUserID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryUser=0x3046;

///投资者持仓请求
class CQryInvestorPositionField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///用户代码
	CUserIDType	UserID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///客户号
	CClientIDType	ClientID;
	///席位号
	CSeatIDType	SeatID;
	///登录经纪公司编号
	CBrokerIDType	LogBrokerID;
	///登录用户代码
	CUserIDType	LogUserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(ClientID)
		,
		TYPE_DESC(SeatID)
		,
		TYPE_DESC(LogBrokerID)
		,
		TYPE_DESC(LogUserID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInvestorPosition=0x3047;

///可用投资者账户查询
class CQryUserInvestorField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///用户代码
	CUserIDType	UserID;
	///登录经纪公司编号
	CBrokerIDType	LogBrokerID;
	///登录用户代码
	CUserIDType	LogUserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(LogBrokerID)
		,
		TYPE_DESC(LogUserID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryUserInvestor=0x3049;

///交易所查询
class CQryExchangeField
{
public:
	///交易所代码
	CExchangeIDType	ExchangeID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryExchange=0x304B;

///响应信息
class CRspInfoField
{
public:
	///错误代码
	CErrorIDType	ErrorID;
	///错误信息
	CErrorMsgType	ErrorMsg;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ErrorID)
		,
		TYPE_DESC(ErrorMsg)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_RspInfo=0x304D;

///交易所应答
class CRspExchangeField
{
public:
	///交易日
	CTradingDayType	TradingDay;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///交易所名称
	CExchangeNameType	ExchangeName;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(ExchangeName)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_RspExchange=0x304E;

///行情查询
class CQryMarketDataField
{
public:
	///交易所代码
	CExchangeIDType	ExchangeID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InstrumentID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryMarketData=0x304F;

///投资者手续费率查询
class CQryInvestorFeeField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///用户代码
	CUserIDType	UserID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///投机套保标志
	CHedgeFlagType	HedgeFlag;
	///登录经纪公司编号
	CBrokerIDType	LogBrokerID;
	///登录用户代码
	CUserIDType	LogUserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(HedgeFlag)
		,
		TYPE_DESC(LogBrokerID)
		,
		TYPE_DESC(LogUserID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInvestorFee=0x3050;

///投资者保证金率查询
class CQryInvestorMarginField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///用户代码
	CUserIDType	UserID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///投机套保标志
	CHedgeFlagType	HedgeFlag;
	///登录经纪公司编号
	CBrokerIDType	LogBrokerID;
	///登录用户代码
	CUserIDType	LogUserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(HedgeFlag)
		,
		TYPE_DESC(LogBrokerID)
		,
		TYPE_DESC(LogUserID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInvestorMargin=0x3051;

///金交所递延费率查询请求
class CQrySGEDeferRateField
{
public:
	///合约代码
	CInstrumentIDType	InstrumentID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(InstrumentID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QrySGEDeferRate=0x3066;

///金交所递延费率查询应答
class CSGEDeferRateField
{
public:
	///合约代码
	CInstrumentIDType	InstrumentID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///交易日期
	CTradingDayType	TradeDate;
	///支付方向
	CPayDirectionType	Direction;
	///递延费率
	CRatioType	DeferRate;
	TYPE_DESCRIPTOR((
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(TradeDate)
		,
		TYPE_DESC(Direction)
		,
		TYPE_DESC(DeferRate)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_SGEDeferRate=0x3067;

///通讯阶段
class CCommPhaseField
{
public:
	///交易日
	CDateType	TradingDay;
	///通讯时段号
	CCommPhaseNoType	CommPhaseNo;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(CommPhaseNo)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_CommPhase=0x3060;

///交易日
class CTradingDayField
{
public:
	///交易日
	CTradingDayType	TradingDay;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_TradingDay=0x3061;

///当前时间
class CCurrentTimeField
{
public:
	///当前日期
	CDateType	CurrDate;
	///当前时间
	CTimeType	CurrTime;
	///当前时间（毫秒）
	CMillisecType	CurrMillisec;
	TYPE_DESCRIPTOR((
		TYPE_DESC(CurrDate)
		,
		TYPE_DESC(CurrTime)
		,
		TYPE_DESC(CurrMillisec)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_CurrentTime=0x3062;

///生命周期号
class CLifeCycleIDField
{
public:
	///生命周期号
	CSequenceNoType	LifeCycleID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(LifeCycleID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_LifeCycleID=0x3063;

///内存表导出
class CMemDbField
{
public:
	///内存表名
	CMemTableNameType	MemTableName;
	TYPE_DESCRIPTOR((
		TYPE_DESC(MemTableName)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_MemDb=0x3064;

///系统状态
class CSystemStatusField
{
public:
	///交易日
	CDateType	TradingDay;
	///系统状态
	CSystemStatusType	SystemStatus;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(SystemStatus)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_SystemStatus=0x3065;

///系统数据同步状态
class CDataSyncStatusField
{
public:
	///交易日
	CDateType	TradingDay;
	///数据同步状态
	CDataSyncStatusType	DataSyncStatus;
	///QDP系统编号
	CSystemIDType	SystemID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(DataSyncStatus)
		,
		TYPE_DESC(SystemID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_DataSyncStatus=0x3070;

///Dbmt投资者资金帐户入金
class CDbmtInvestorAccountDepositField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///资金流水号
	CAccountSeqNoType	AccountSeqNo;
	///资金帐号
	CAccountIDType	AccountID;
	///连续递增的总资金流水号
	CAccountSeqNoType	AccountInsideSeqNo;
	///投资者编号
	CInvestorIDType	InvestorID;
	///金额
	CMoneyType	Amount;
	///出入金方向
	CAccountDirectionType	AmountDirection;
	///Dbmt主题号
	CDbmtTopicIDType	DbmtTopicID;
	///Dbmt序列号
	CDbmtSequenceIDType	DbmtSequenceID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(AccountSeqNo)
		,
		TYPE_DESC(AccountID)
		,
		TYPE_DESC(AccountInsideSeqNo)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(Amount)
		,
		TYPE_DESC(AmountDirection)
		,
		TYPE_DESC(DbmtTopicID)
		,
		TYPE_DESC(DbmtSequenceID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_DbmtInvestorAccountDeposit=0x3071;

///Dbmt用户
class CDbmtUserField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///用户代码
	CUserIDType	UserID;
	///用户登录密码
	CPasswordType	Password;
	///是否活跃
	CIsActiveType	IsActive;
	///用户名称
	CUserNameType	UserName;
	///用户类型
	CUserTypeType	UserType;
	///营业部
	CDepartmentType	Department;
	///授权功能集
	CGrantFuncSetType	GrantFuncSet;
	///是否检查IP和MAC
	CBoolType	CheckIpMacAddr;
	///Dbmt主题号
	CDbmtTopicIDType	DbmtTopicID;
	///Dbmt序列号
	CDbmtSequenceIDType	DbmtSequenceID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(Password)
		,
		TYPE_DESC(IsActive)
		,
		TYPE_DESC(UserName)
		,
		TYPE_DESC(UserType)
		,
		TYPE_DESC(Department)
		,
		TYPE_DESC(GrantFuncSet)
		,
		TYPE_DESC(CheckIpMacAddr)
		,
		TYPE_DESC(DbmtTopicID)
		,
		TYPE_DESC(DbmtSequenceID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_DbmtUser=0x3072;

///内存表变化
class CMemtableChangeField
{
public:
	///内存表变化类型
	CMemtableChangeTypeType	MemtableChangeType;
	///内存表名
	CMemTableNameType	MemTableName;
	TYPE_DESCRIPTOR((
		TYPE_DESC(MemtableChangeType)
		,
		TYPE_DESC(MemTableName)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_MemtableChange=0x3073;

///交易所交易日
class CExchangeTradingDayField
{
public:
	///交易日
	CTradingDayType	TradingDay;
	///交易所代码
	CExchangeIDType	ExchangeID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(ExchangeID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_ExchangeTradingDay=0x3081;

///出入金回报通知
class CInvestorAccountDepositNtfField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///资金帐号
	CAccountIDType	AccountID;
	///资金流水号
	CAccountSeqNoType	AccountSeqNo;
	///连续递增的总资金流水号
	CAccountSeqNoType	AccountInsideSeqNo;
	///金额
	CMoneyType	Amount;
	///出入金方向
	CAccountDirectionType	AmountDirection;
	///可用资金
	CMoneyType	Available;
	///结算准备金
	CMoneyType	Balance;
	///用户代码
	CUserIDType	UserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(AccountID)
		,
		TYPE_DESC(AccountSeqNo)
		,
		TYPE_DESC(AccountInsideSeqNo)
		,
		TYPE_DESC(Amount)
		,
		TYPE_DESC(AmountDirection)
		,
		TYPE_DESC(Available)
		,
		TYPE_DESC(Balance)
		,
		TYPE_DESC(UserID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorAccountDepositNtf=0x3085;

///错单表
class COrderInsertFailedField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///系统报单编号
	COrderSysIDType	OrderSysID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///用户代码
	CUserIDType	UserID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///用户本地报单号
	CUserOrderLocalIDType	UserOrderLocalID;
	///价格类型
	COrderPriceTypeType	OrderPriceType;
	///买卖方向
	CDirectionType	Direction;
	///开平标志
	COffsetFlagType	OffsetFlag;
	///投机套保标志
	CHedgeFlagType	HedgeFlag;
	///价格
	CPriceType	LimitPrice;
	///数量
	CVolumeType	Volume;
	///有效期类型
	CTimeConditionType	TimeCondition;
	///GTD日期
	CDateType	GTDDate;
	///成交量类型
	CVolumeConditionType	VolumeCondition;
	///最小成交量
	CVolumeType	MinVolume;
	///止损价
	CPriceType	StopPrice;
	///强平原因
	CForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	CBoolType	IsAutoSuspend;
	///业务单元
	CBusinessUnitType	BusinessUnit;
	///用户自定义域
	CCustomType	UserCustom;
	///营业部代码
	CBranchIDType	BranchID;
	///记录编号
	CSequenceNoType	RecNum;
	///业务类别
	CBusinessTypeType	BusinessType;
	///交易日
	CTradingDayType	TradingDay;
	///会员编号
	CParticipantIDType	ParticipantID;
	///客户号
	CClientIDType	ClientID;
	///下单席位号
	CSeatIDType	SeatID;
	///插入时间
	CTimeType	InsertTime;
	///本地报单编号
	COrderLocalIDType	OrderLocalID;
	///报单来源
	COrderSourceType	OrderSource;
	///报单状态
	COrderStatusType	OrderStatus;
	///撤销时间
	CTimeType	CancelTime;
	///撤单用户编号
	CUserIDType	CancelUserID;
	///今成交数量
	CVolumeType	VolumeTraded;
	///剩余数量
	CVolumeType	VolumeRemain;
	///前置编号
	CFrontIDType	FrontID;
	///会话编号
	CSessionIDType	SessionID;
	///冻结手续费
	CMoneyType	FrozenFee;
	///冻结的保证金
	CMoneyType	FrozenMargin;
	///期权权利金收支
	CMoneyType	FrozenPremium;
	///资金帐号
	CAccountIDType	AccountID;
	///下单用户编号
	CUserIDType	OrderUserID;
	///交易类型
	CTradeTypeType	TradeType;
	///处理标志
	CDealFlagType	DealFlag;
	///已成交佣金
	CMoneyType	TradeCommision;
	///成交金额
	CMoneyType	TradeAmnt;
	///撤单数量
	CVolumeType	CancleVolume;
	///请求编号
	CRequestIDType	RequestID;
	///通道对应的APIID
	CNumberType	APIID;
	///下单IP地址
	CIPAddressType	IPAddress;
	///下单MAC地址
	CMacAddressType	MacAddress;
	///Ftdengine接受下层时间戳
	CILocalTimeType	FTdRecvDown;
	///接受下层时间戳
	CILocalTimeType	CoreRecvDown;
	///发送上层时间戳
	CILocalTimeType	CoreSendUp;
	///接受上层时间戳
	CILocalTimeType	CoreRecvUp;
	///发送下层时间戳
	CILocalTimeType	CoreSendDown;
	///Ftdengine接受下层时间戳
	CILocalTimeType	FTdSendDown;
	///保证金组合类型
	CClientMarginCombTypeType	MarginCombType;
	///合约组代码
	CInstrumentGroupIDType	InstrumentGroupID;
	///错误信息
	CErrorMsgType	ErrorMsg;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(OrderSysID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(UserOrderLocalID)
		,
		TYPE_DESC(OrderPriceType)
		,
		TYPE_DESC(Direction)
		,
		TYPE_DESC(OffsetFlag)
		,
		TYPE_DESC(HedgeFlag)
		,
		TYPE_DESC(LimitPrice)
		,
		TYPE_DESC(Volume)
		,
		TYPE_DESC(TimeCondition)
		,
		TYPE_DESC(GTDDate)
		,
		TYPE_DESC(VolumeCondition)
		,
		TYPE_DESC(MinVolume)
		,
		TYPE_DESC(StopPrice)
		,
		TYPE_DESC(ForceCloseReason)
		,
		TYPE_DESC(IsAutoSuspend)
		,
		TYPE_DESC(BusinessUnit)
		,
		TYPE_DESC(UserCustom)
		,
		TYPE_DESC(BranchID)
		,
		TYPE_DESC(RecNum)
		,
		TYPE_DESC(BusinessType)
		,
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(ParticipantID)
		,
		TYPE_DESC(ClientID)
		,
		TYPE_DESC(SeatID)
		,
		TYPE_DESC(InsertTime)
		,
		TYPE_DESC(OrderLocalID)
		,
		TYPE_DESC(OrderSource)
		,
		TYPE_DESC(OrderStatus)
		,
		TYPE_DESC(CancelTime)
		,
		TYPE_DESC(CancelUserID)
		,
		TYPE_DESC(VolumeTraded)
		,
		TYPE_DESC(VolumeRemain)
		,
		TYPE_DESC(FrontID)
		,
		TYPE_DESC(SessionID)
		,
		TYPE_DESC(FrozenFee)
		,
		TYPE_DESC(FrozenMargin)
		,
		TYPE_DESC(FrozenPremium)
		,
		TYPE_DESC(AccountID)
		,
		TYPE_DESC(OrderUserID)
		,
		TYPE_DESC(TradeType)
		,
		TYPE_DESC(DealFlag)
		,
		TYPE_DESC(TradeCommision)
		,
		TYPE_DESC(TradeAmnt)
		,
		TYPE_DESC(CancleVolume)
		,
		TYPE_DESC(RequestID)
		,
		TYPE_DESC(APIID)
		,
		TYPE_DESC(IPAddress)
		,
		TYPE_DESC(MacAddress)
		,
		TYPE_DESC(FTdRecvDown)
		,
		TYPE_DESC(CoreRecvDown)
		,
		TYPE_DESC(CoreSendUp)
		,
		TYPE_DESC(CoreRecvUp)
		,
		TYPE_DESC(CoreSendDown)
		,
		TYPE_DESC(FTdSendDown)
		,
		TYPE_DESC(MarginCombType)
		,
		TYPE_DESC(InstrumentGroupID)
		,
		TYPE_DESC(ErrorMsg)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_OrderInsertFailed=0x3086;

///合约和合约组关系
class CInstrumentGroupField
{
public:
	///交易所代码
	CExchangeIDType	ExchangeID;
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///合约组代码
	CInstrumentGroupIDType	InstrumentGroupID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(InstrumentGroupID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InstrumentGroup=0x3088;

///交易编码组合保证金类型
class CClientMarginCombTypeField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///会员代码
	CParticipantIDType	ParticipantID;
	///客户代码
	CClientIDType	ClientID;
	///合约组代码
	CInstrumentGroupIDType	InstrumentGroupID;
	///保证金组合类型
	CClientMarginCombTypeType	MarginCombType;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(ParticipantID)
		,
		TYPE_DESC(ClientID)
		,
		TYPE_DESC(InstrumentGroupID)
		,
		TYPE_DESC(MarginCombType)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_ClientMarginCombType=0x3089;

///登录信息
class CInterLoginInfoField
{
public:
	///IP地址
	CServerAddrType	ServerAddr;
	///最大本地保单号
	CSequenceNoType	MaxLocalID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ServerAddr)
		,
		TYPE_DESC(MaxLocalID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InterLoginInfo=0x3096;

///QDP警告消息通知
class CMessageNotifyInfoField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///修改用户编号
	CUserIDType	UserID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///累加次数
	CTotalNumsType	Nums;
	///业务类别
	CBusinessTypeType	BusinessType;
	///警告信息
	CErrorMsgType	WarnMsg;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(Nums)
		,
		TYPE_DESC(BusinessType)
		,
		TYPE_DESC(WarnMsg)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_MessageNotifyInfo=0x3097;

///出入金请求
class CAccountDepositField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///资金流水号
	CAccountSeqNoType	AccountSeqNo;
	///资金帐号
	CAccountIDType	AccountID;
	///连续递增的总资金流水号
	CAccountSeqNoType	AccountInsideSeqNo;
	///投资者编号
	CInvestorIDType	InvestorID;
	///金额
	CMoneyType	Amount;
	///出入金方向
	CAccountDirectionType	AmountDirection;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(AccountSeqNo)
		,
		TYPE_DESC(AccountID)
		,
		TYPE_DESC(AccountInsideSeqNo)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(Amount)
		,
		TYPE_DESC(AmountDirection)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_AccountDeposit=0x3098;

///出入金应答
class CAccountDepositResField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///资金帐号
	CAccountIDType	AccountID;
	///资金流水号
	CAccountSeqNoType	AccountSeqNo;
	///连续递增的总资金流水号
	CAccountSeqNoType	AccountInsideSeqNo;
	///金额
	CMoneyType	Amount;
	///出入金方向
	CAccountDirectionType	AmountDirection;
	///可用资金
	CMoneyType	Available;
	///结算准备金
	CMoneyType	Balance;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(AccountID)
		,
		TYPE_DESC(AccountSeqNo)
		,
		TYPE_DESC(AccountInsideSeqNo)
		,
		TYPE_DESC(Amount)
		,
		TYPE_DESC(AmountDirection)
		,
		TYPE_DESC(Available)
		,
		TYPE_DESC(Balance)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_AccountDepositRes=0x3099;

///报盘机查询结束消息通知
class CQueryFinishNotifyField
{
public:
	///交易日
	CTradingDayType	TradingDay;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///最大本地报单号
	COrderLocalIDType	MaxOrderLocalID;
	///通道对应的APIID
	CNumberType	APIID;
	///席位连接api类型
	CApiLinkTypeType	ApiLinkType;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(MaxOrderLocalID)
		,
		TYPE_DESC(APIID)
		,
		TYPE_DESC(ApiLinkType)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QueryFinishNotify=0x3100;

///Dbmt客户交易编码交易权限
class CDbmtClientTradingIDField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///资金帐号
	CAccountIDType	AccountID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///会员编号
	CParticipantIDType	ParticipantID;
	///客户代码
	CClientIDType	ClientID;
	///客户代码权限
	CTradingRightType	ClientRight;
	///客户类型
	CClientTypeType	ClientType;
	///客户保值类型
	CHedgeFlagType	ClientHedgeFlag;
	///是否活跃
	CIsActiveType	IsActive;
	///通道对应的APIID
	CNumberType	APIID;
	///Dbmt主题号
	CDbmtTopicIDType	DbmtTopicID;
	///Dbmt序列号
	CDbmtSequenceIDType	DbmtSequenceID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(AccountID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(ParticipantID)
		,
		TYPE_DESC(ClientID)
		,
		TYPE_DESC(ClientRight)
		,
		TYPE_DESC(ClientType)
		,
		TYPE_DESC(ClientHedgeFlag)
		,
		TYPE_DESC(IsActive)
		,
		TYPE_DESC(APIID)
		,
		TYPE_DESC(DbmtTopicID)
		,
		TYPE_DESC(DbmtSequenceID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_DbmtClientTradingID=0x3109;

///组合合约明细
class CCmbInstrumentDetailField
{
public:
	///交易所代码
	CExchangeIDType	ExchangeID;
	///组合合约代码
	CInstrumentIDType	ArbiInstrumentID;
	///单腿合约代码
	CInstrumentIDType	SingleInstrumentID;
	///组合合约腿的数量
	CNumberType	LegNo;
	///买卖方向
	CDirectionType	Direction;
	///数量比例
	CNumberType	Ratio;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(ArbiInstrumentID)
		,
		TYPE_DESC(SingleInstrumentID)
		,
		TYPE_DESC(LegNo)
		,
		TYPE_DESC(Direction)
		,
		TYPE_DESC(Ratio)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_CmbInstrumentDetail=0x3102;

///内部登陆信息
class CInnerLoginField
{
public:
	///接收到流的最大编号
	CSequenceNoType	SequenceNo;
	TYPE_DESCRIPTOR((
		TYPE_DESC(SequenceNo)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InnerLogin=0x3111;

///投资者交易权限
class CInvestorTradingRightField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///合约交易权限
	CTradingRightType	TradingRight;
	///产品类型
	CProductClassType	ProductClass;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(TradingRight)
		,
		TYPE_DESC(ProductClass)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorTradingRight=0x3112;

///Dbmt投资者权限
class CDbmtInvestorTradingRightField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///合约交易权限
	CTradingRightType	TradingRight;
	///产品类型
	CProductClassType	ProductClass;
	///Dbmt主题号
	CDbmtTopicIDType	DbmtTopicID;
	///Dbmt序列号
	CDbmtSequenceIDType	DbmtSequenceID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(TradingRight)
		,
		TYPE_DESC(ProductClass)
		,
		TYPE_DESC(DbmtTopicID)
		,
		TYPE_DESC(DbmtSequenceID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_DbmtInvestorTradingRight=0x3113;

///用户IP
class CUserIPField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易用户代码
	CUserIDType	UserID;
	///IP地址
	CIPAddressType	IPAddress;
	///IP地址掩码
	CIPAddressType	IPMask;
	///MAC地址
	CMacAddressType	MacAddress;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(IPAddress)
		,
		TYPE_DESC(IPMask)
		,
		TYPE_DESC(MacAddress)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_UserIP=0x3114;

///Dbmt用户IP
class CDbmtUserIPField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易用户代码
	CUserIDType	UserID;
	///IP地址
	CIPAddressType	IPAddress;
	///IP地址掩码
	CIPAddressType	IPMask;
	///MAC地址
	CMacAddressType	MacAddress;
	///Dbmt主题号
	CDbmtTopicIDType	DbmtTopicID;
	///Dbmt序列号
	CDbmtSequenceIDType	DbmtSequenceID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(IPAddress)
		,
		TYPE_DESC(IPMask)
		,
		TYPE_DESC(MacAddress)
		,
		TYPE_DESC(DbmtTopicID)
		,
		TYPE_DESC(DbmtSequenceID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_DbmtUserIP=0x3115;

///投资者持仓明细查询请求
class CQryInvestorPositionDetailField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///单腿合约代码
	CInstrumentIDType	InstrumentID;
	///登录经纪公司编号
	CBrokerIDType	LogBrokerID;
	///登录用户代码
	CUserIDType	LogUserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(LogBrokerID)
		,
		TYPE_DESC(LogUserID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInvestorPositionDetail=0x3116;

///投资者持仓明细应答
class CRspInvestorPositionDetailField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///投机套保标志
	CHedgeFlagType	HedgeFlag;
	///买卖方向
	CDirectionType	Direction;
	///开仓日期
	CDateType	OpenDate;
	///成交编号
	CTradeIDType	TradeID;
	///数量
	CVolumeType	Volume;
	///开仓价
	CMoneyType	OpenPrice;
	///交易日
	CDateType	TradingDay;
	///交易类型
	CTradeTypeType	TradeType;
	///组合合约代码
	CInstrumentIDType	CombInstrumentID;
	///逐日盯市平仓盈亏
	CMoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	CMoneyType	CloseProfitByTrade;
	///逐日盯市持仓盈亏
	CMoneyType	PositionProfitByDate;
	///逐笔对冲持仓盈亏
	CMoneyType	PositionProfitByTrade;
	///投资者保证金
	CMoneyType	Margin;
	///交易所保证金
	CMoneyType	ExchMargin;
	///保证金率
	CMoneyType	MarginRateByMoney;
	///保证金率(按手数)
	CMoneyType	MarginRateByVolume;
	///昨结算价
	CPriceType	LastSettlementPrice;
	///结算价
	CPriceType	SettlementPrice;
	///平仓量
	CVolumeType	CloseVolume;
	///平仓金额
	CMoneyType	CloseAmount;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(HedgeFlag)
		,
		TYPE_DESC(Direction)
		,
		TYPE_DESC(OpenDate)
		,
		TYPE_DESC(TradeID)
		,
		TYPE_DESC(Volume)
		,
		TYPE_DESC(OpenPrice)
		,
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(TradeType)
		,
		TYPE_DESC(CombInstrumentID)
		,
		TYPE_DESC(CloseProfitByDate)
		,
		TYPE_DESC(CloseProfitByTrade)
		,
		TYPE_DESC(PositionProfitByDate)
		,
		TYPE_DESC(PositionProfitByTrade)
		,
		TYPE_DESC(Margin)
		,
		TYPE_DESC(ExchMargin)
		,
		TYPE_DESC(MarginRateByMoney)
		,
		TYPE_DESC(MarginRateByVolume)
		,
		TYPE_DESC(LastSettlementPrice)
		,
		TYPE_DESC(SettlementPrice)
		,
		TYPE_DESC(CloseVolume)
		,
		TYPE_DESC(CloseAmount)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_RspInvestorPositionDetail=0x3117;

///投资者持仓明细
class CInvestorPositionDetailField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///投机套保标志
	CHedgeFlagType	HedgeFlag;
	///买卖方向
	CDirectionType	Direction;
	///开仓日期
	CDateType	OpenDate;
	///成交编号
	CTradeIDType	TradeID;
	///数量
	CVolumeType	Volume;
	///开仓价
	CMoneyType	OpenPrice;
	///交易日
	CDateType	TradingDay;
	///交易类型
	CTradeTypeType	TradeType;
	///组合合约代码
	CInstrumentIDType	CombInstrumentID;
	///逐日盯市平仓盈亏
	CMoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	CMoneyType	CloseProfitByTrade;
	///逐日盯市持仓盈亏
	CMoneyType	PositionProfitByDate;
	///逐笔对冲持仓盈亏
	CMoneyType	PositionProfitByTrade;
	///投资者保证金
	CMoneyType	Margin;
	///交易所保证金
	CMoneyType	ExchMargin;
	///保证金率
	CMoneyType	MarginRateByMoney;
	///保证金率(按手数)
	CMoneyType	MarginRateByVolume;
	///昨结算价
	CPriceType	LastSettlementPrice;
	///结算价
	CPriceType	SettlementPrice;
	///平仓量
	CVolumeType	CloseVolume;
	///平仓金额
	CMoneyType	CloseAmount;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(HedgeFlag)
		,
		TYPE_DESC(Direction)
		,
		TYPE_DESC(OpenDate)
		,
		TYPE_DESC(TradeID)
		,
		TYPE_DESC(Volume)
		,
		TYPE_DESC(OpenPrice)
		,
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(TradeType)
		,
		TYPE_DESC(CombInstrumentID)
		,
		TYPE_DESC(CloseProfitByDate)
		,
		TYPE_DESC(CloseProfitByTrade)
		,
		TYPE_DESC(PositionProfitByDate)
		,
		TYPE_DESC(PositionProfitByTrade)
		,
		TYPE_DESC(Margin)
		,
		TYPE_DESC(ExchMargin)
		,
		TYPE_DESC(MarginRateByMoney)
		,
		TYPE_DESC(MarginRateByVolume)
		,
		TYPE_DESC(LastSettlementPrice)
		,
		TYPE_DESC(SettlementPrice)
		,
		TYPE_DESC(CloseVolume)
		,
		TYPE_DESC(CloseAmount)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorPositionDetail=0x3118;

///投资者期权手续费查询请求
class CQryInvestorOptionFeeField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///用户代码
	CUserIDType	UserID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///登录经纪公司编号
	CBrokerIDType	LogBrokerID;
	///登录用户代码
	CUserIDType	LogUserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(LogBrokerID)
		,
		TYPE_DESC(LogUserID)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInvestorOptionFee=0x3121;

///投资者期权手续费
class CInvestorOptionFeeField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易所代码
	CExchangeIDType	ExchangeID;
	///投资者编码
	CInvestorIDType	InvestorID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///开仓手续费按比例
	CRatioType	OpenFeeRate;
	///开仓手续费按手数
	CRatioType	OpenFeeAmt;
	///平仓手续费按比例
	CRatioType	OffsetFeeRate;
	///平仓手续费按手数
	CRatioType	OffsetFeeAmt;
	///平今仓手续费按比例
	CRatioType	OTFeeRate;
	///平今仓手续费按手数
	CRatioType	OTFeeAmt;
	///执行手续费按比例
	CRatioType	StrikeFeeRate;
	///执行手续费按手数
	CRatioType	StrikeFeeAmt;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(OpenFeeRate)
		,
		TYPE_DESC(OpenFeeAmt)
		,
		TYPE_DESC(OffsetFeeRate)
		,
		TYPE_DESC(OffsetFeeAmt)
		,
		TYPE_DESC(OTFeeRate)
		,
		TYPE_DESC(OTFeeAmt)
		,
		TYPE_DESC(StrikeFeeRate)
		,
		TYPE_DESC(StrikeFeeAmt)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorOptionFee=0x3122;

///投资者持仓盈亏
class CPositionProfitField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///投资者编号
	CInvestorIDType	InvestorID;
	///持仓盈亏
	CMoneyType	PositionProfit;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(PositionProfit)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_PositionProfit=0x3123;

///QDP系统信息
class CSystemInfoField
{
public:
	///QDP系统编号
	CSystemIDType	SystemID;
	///QDP系统名称
	CSystemNameType	SystemName;
	///QDP系统IP地址
	CIPAddressType	SystemIP;
	TYPE_DESCRIPTOR((
		TYPE_DESC(SystemID)
		,
		TYPE_DESC(SystemName)
		,
		TYPE_DESC(SystemIP)
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_SystemInfo=0x3124;




#endif
