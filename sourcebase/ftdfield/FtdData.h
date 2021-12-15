// FtdData.h: 
//
//////////////////////////////////////////////////////////////////////

#if !defined(_FTDDATA_H)
#define _FTDDATA_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FieldDescribe.h"
#include "customDataType.h"

///系统用户登录请求
class CFTDReqUserLoginField
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
	));
};
const DWORD FTD_FID_ReqUserLogin=0x3001;

///系统用户登录应答
class CFTDRspUserLoginField
{
public:
	///交易日
	CDateType	TradingDay;
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易用户代码
	CUserIDType	UserID;
	///登录成功时间
	CTimeType	LoginTime;
	///用户最大本地报单号
	CUserOrderLocalIDType	MaxOrderLocalID;
	///交易系统名称
	CTradingSystemNameType	TradingSystemName;
	///数据中心代码
	CDataCenterIDType	DataCenterID;
	///会员私有流当前长度
	CSequenceNoType	PrivateFlowSize;
	///交易员私有流当前长度
	CSequenceNoType	UserFlowSize;
	///会话编号
	CSessionIDType	SessionID;
	///前置编号
	CFrontIDType	FrontID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(LoginTime)
		,
		TYPE_DESC(MaxOrderLocalID)
		,
		TYPE_DESC(TradingSystemName)
		,
		TYPE_DESC(DataCenterID)
		,
		TYPE_DESC(PrivateFlowSize)
		,
		TYPE_DESC(UserFlowSize)
		,
		TYPE_DESC(SessionID)
		,
		TYPE_DESC(FrontID)
	));
};
const DWORD FTD_FID_RspUserLogin=0x3002;

///用户登出请求
class CFTDReqUserLogoutField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易用户代码
	CUserIDType	UserID;
	///Session退出原因
	CNumberType	LogoutReason;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(LogoutReason)
	));
};
const DWORD FTD_FID_ReqUserLogout=0x3003;

///用户登出请求
class CFTDRspUserLogoutField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易用户代码
	CUserIDType	UserID;
	///Session退出原因
	CNumberType	LogoutReason;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(LogoutReason)
	));
};
const DWORD FTD_FID_RspUserLogout=0x3003;

///强制用户退出
class CFTDForceUserExitField
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
};
const DWORD FTD_FID_ForceUserExit=0x3005;

///用户口令修改
class CFTDUserPasswordUpdateField
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
};
const DWORD FTD_FID_UserPasswordUpdate=0x3006;

///输入报单
class CFTDInputOrderField
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
	));
};
const DWORD FTD_FID_InputOrder=0x3007;

///报单操作
class CFTDOrderActionField
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
	));
};
const DWORD FTD_FID_OrderAction=0x3008;

///内存表导出
class CFTDMemDbField
{
public:
	///内存表名
	CMemTableNameType	MemTableName;
	TYPE_DESCRIPTOR((
		TYPE_DESC(MemTableName)
	));
};
const DWORD FTD_FID_MemDb=0x3009;

///投资者资金帐户出入金请求
class CFTDReqAccountDepositField
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
	///用户代码
	CUserIDType	UserID;
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
		TYPE_DESC(UserID)
	));
};
const DWORD FTD_FID_ReqAccountDeposit=0x3010;

///投资者资金帐户出入金应答
class CFTDRspAccountDepositField
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
};
const DWORD FTD_FID_RspAccountDeposit=0x3011;

///响应信息
class CFTDRspInfoField
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
};
const DWORD FTD_FID_RspInfo=0x3001;

///报单查询
class CFTDQryOrderField
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
	));
};
const DWORD FTD_FID_QryOrder=0x300A;

///成交查询
class CFTDQryTradeField
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
	));
};
const DWORD FTD_FID_QryTrade=0x300B;

///合约查询
class CFTDQryInstrumentField
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
};
const DWORD FTD_FID_QryInstrument=0x300C;

///合约查询应答
class CFTDRspInstrumentField
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
	));
};
const DWORD FTD_FID_RspInstrument=0x300D;

///合约状态
class CFTDInstrumentStatusField
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
	));
};
const DWORD FTD_FID_InstrumentStatus=0x300E;

///投资者资金查询
class CFTDQryInvestorAccountField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///用户代码
	CUserIDType	UserID;
	///投资者编号
	CInvestorIDType	InvestorID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(InvestorID)
	));
};
const DWORD FTD_FID_QryInvestorAccount=0x300F;

///投资者资金应答
class CFTDRspInvestorAccountField
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
	));
};
const DWORD FTD_FID_RspInvestorAccount=0x3010;

///可用投资者查询
class CFTDQryUserInvestorField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///用户代码
	CUserIDType	UserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
	));
};
const DWORD FTD_FID_QryUserInvestor=0x3011;

///可用投资者应答
class CFTDRspUserInvestorField
{
public:
	///经纪公司编号
	CBrokerIDType	BrokerID;
	///交易用户代码
	CUserIDType	UserID;
	///投资者编号
	CInvestorIDType	InvestorID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(InvestorID)
	));
};
const DWORD FTD_FID_RspUserInvestor=0x3012;

///交易编码查询
class CFTDQryTradingCodeField
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
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(ExchangeID)
	));
};
const DWORD FTD_FID_QryTradingCode=0x3013;

///交易编码查询
class CFTDRspTradingCodeField
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
	));
};
const DWORD FTD_FID_RspTradingCode=0x3014;

///交易所查询请求
class CFTDQryExchangeField
{
public:
	///交易所代码
	CExchangeIDType	ExchangeID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
	));
};
const DWORD FTD_FID_QryExchange=0x3015;

///交易所查询应答
class CFTDRspExchangeField
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
};
const DWORD FTD_FID_RspExchange=0x3016;

///投资者持仓查询请求
class CFTDQryInvestorPositionField
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
	));
};
const DWORD FTD_FID_QryInvestorPosition=0x3017;

///投资者持仓查询应答
class CFTDRspInvestorPositionField
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
	));
};
const DWORD FTD_FID_RspInvestorPosition=0x3018;

///用户查询
class CFTDQryUserField
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
};
const DWORD FTD_FID_QryUser=0x301B;

///用户
class CFTDUserField
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
};
const DWORD FTD_FID_User=0x301C;

///投资者手续费率查询
class CFTDQryInvestorFeeField
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
	));
};
const DWORD FTD_FID_QryInvestorFee=0x301D;

///投资者手续费率
class CFTDInvestorFeeField
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
};
const DWORD FTD_FID_InvestorFee=0x301E;

///投资者保证金率查询
class CFTDQryInvestorMarginField
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
	));
};
const DWORD FTD_FID_QryInvestorMargin=0x301F;

///投资者保证金率
class CFTDInvestorMarginField
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
};
const DWORD FTD_FID_InvestorMargin=0x3020;

///实时行情查询请求
class CFTDQryMarketDataField
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
};
const DWORD FTD_FID_QryMarketData=0x3054;

///实时行情查询应答
class CFTDMarketDataField
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
};
const DWORD FTD_FID_MarketData=0x3055;

///行情查询应答
class CFTDRspMarketDataField
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
};
const DWORD FTD_FID_RspMarketData=0x3055;

///金交所递延费率查询请求
class CFTDQrySGEDeferRateField
{
public:
	///合约代码
	CInstrumentIDType	InstrumentID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(InstrumentID)
	));
};
const DWORD FTD_FID_QrySGEDeferRate=0x3059;

///金交所递延费率查询应答
class CFTDSGEDeferRateField
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
};
const DWORD FTD_FID_SGEDeferRate=0x305A;

///分价表查询请求
class CFTDQryMBLMarketDataField
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
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InstIDStart)
		,
		TYPE_DESC(InstIDEnd)
		,
		TYPE_DESC(Direction)
	));
};
const DWORD FTD_FID_QryMBLMarketData=0x305B;

///分价表查询应答
class CFTDMBLMarketDataField
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
};
const DWORD FTD_FID_MBLMarketData=0x305C;

///查询持仓明细请求
class CFTDQryInvestorPositionDetailField
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
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(InstrumentID)
	));
};
const DWORD FTD_FID_QryInvestorPositionDetail=0x305D;

///查询持仓明细应答
class CFTDRspInvestorPositionDetailField
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
};
const DWORD FTD_FID_RspInvestorPositionDetail=0x305E;

///投资者期权手续费率查询
class CFTDQryInvestorOptionFeeField
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
	));
};
const DWORD FTD_FID_QryInvestorOptionFee=0x3062;

///投资者期权手续费率
class CFTDRspInvestorOptionFeeField
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
};
const DWORD FTD_FID_RspInvestorOptionFee=0x3063;

///成交
class CFTDTradeField
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
	));
};
const DWORD FTD_FID_Trade=0x3030;

///报单
class CFTDOrderField
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
	));
};
const DWORD FTD_FID_Order=0x3031;

///数据流回退
class CFTDFlowMessageCancelField
{
public:
	///序列系列号
	CSequenceSeriesType	SequenceSeries;
	///交易日
	CDateType	TradingDay;
	///数据中心代码
	CDataCenterIDType	DataCenterID;
	///回退起始序列号
	CSequenceNoType	StartSequenceNo;
	///回退结束序列号
	CSequenceNoType	EndSequenceNo;
	TYPE_DESCRIPTOR((
		TYPE_DESC(SequenceSeries)
		,
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(DataCenterID)
		,
		TYPE_DESC(StartSequenceNo)
		,
		TYPE_DESC(EndSequenceNo)
	));
};
const DWORD FTD_FID_FlowMessageCancel=0x3032;

///信息分发
class CFTDDisseminationField
{
public:
	///序列系列号
	CSequenceSeriesType	SequenceSeries;
	///序列号
	CSequenceNoType	SequenceNo;
	TYPE_DESCRIPTOR((
		TYPE_DESC(SequenceSeries)
		,
		TYPE_DESC(SequenceNo)
	));
};
const DWORD FTD_FID_Dissemination=0x3033;

///出入金结果
class CFTDInvestorAccountDepositResField
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
};
const DWORD FTD_FID_InvestorAccountDepositRes=0x3034;

///QDP警告消息通知
class CFTDMessageNotifyInfoField
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
};
const DWORD FTD_FID_MessageNotifyInfo=0x3035;

///行情基础属性
class CFTDMarketDataBaseField
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
	));
};
const DWORD FTD_FID_MarketDataBase=0x3041;

///行情静态属性
class CFTDMarketDataStaticField
{
public:
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
	TYPE_DESCRIPTOR((
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
	));
};
const DWORD FTD_FID_MarketDataStatic=0x3042;

///行情最新成交属性
class CFTDMarketDataLastMatchField
{
public:
	///最新价
	CPriceType	LastPrice;
	///数量
	CVolumeType	Volume;
	///成交金额
	CMoneyType	Turnover;
	///持仓量
	CLargeVolumeType	OpenInterest;
	TYPE_DESCRIPTOR((
		TYPE_DESC(LastPrice)
		,
		TYPE_DESC(Volume)
		,
		TYPE_DESC(Turnover)
		,
		TYPE_DESC(OpenInterest)
	));
};
const DWORD FTD_FID_MarketDataLastMatch=0x3043;

///行情最优价属性
class CFTDMarketDataBestPriceField
{
public:
	///申买价一
	CPriceType	BidPrice1;
	///申买量一
	CVolumeType	BidVolume1;
	///申卖价一
	CPriceType	AskPrice1;
	///申卖量一
	CVolumeType	AskVolume1;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BidPrice1)
		,
		TYPE_DESC(BidVolume1)
		,
		TYPE_DESC(AskPrice1)
		,
		TYPE_DESC(AskVolume1)
	));
};
const DWORD FTD_FID_MarketDataBestPrice=0x3045;

///行情申买二、三属性
class CFTDMarketDataBid23Field
{
public:
	///申买价二
	CPriceType	BidPrice2;
	///申买量二
	CVolumeType	BidVolume2;
	///申买价三
	CPriceType	BidPrice3;
	///申买量三
	CVolumeType	BidVolume3;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BidPrice2)
		,
		TYPE_DESC(BidVolume2)
		,
		TYPE_DESC(BidPrice3)
		,
		TYPE_DESC(BidVolume3)
	));
};
const DWORD FTD_FID_MarketDataBid23=0x3046;

///行情申卖二、三属性
class CFTDMarketDataAsk23Field
{
public:
	///申卖价二
	CPriceType	AskPrice2;
	///申卖量二
	CVolumeType	AskVolume2;
	///申卖价三
	CPriceType	AskPrice3;
	///申卖量三
	CVolumeType	AskVolume3;
	TYPE_DESCRIPTOR((
		TYPE_DESC(AskPrice2)
		,
		TYPE_DESC(AskVolume2)
		,
		TYPE_DESC(AskPrice3)
		,
		TYPE_DESC(AskVolume3)
	));
};
const DWORD FTD_FID_MarketDataAsk23=0x3047;

///行情申买四、五属性
class CFTDMarketDataBid45Field
{
public:
	///申买价四
	CPriceType	BidPrice4;
	///申买量四
	CVolumeType	BidVolume4;
	///申买价五
	CPriceType	BidPrice5;
	///申买量五
	CVolumeType	BidVolume5;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BidPrice4)
		,
		TYPE_DESC(BidVolume4)
		,
		TYPE_DESC(BidPrice5)
		,
		TYPE_DESC(BidVolume5)
	));
};
const DWORD FTD_FID_MarketDataBid45=0x3048;

///行情申卖四、五属性
class CFTDMarketDataAsk45Field
{
public:
	///申卖价四
	CPriceType	AskPrice4;
	///申卖量四
	CVolumeType	AskVolume4;
	///申卖价五
	CPriceType	AskPrice5;
	///申卖量五
	CVolumeType	AskVolume5;
	TYPE_DESCRIPTOR((
		TYPE_DESC(AskPrice4)
		,
		TYPE_DESC(AskVolume4)
		,
		TYPE_DESC(AskPrice5)
		,
		TYPE_DESC(AskVolume5)
	));
};
const DWORD FTD_FID_MarketDataAsk45=0x3049;

///行情更新时间属性
class CFTDMarketDataUpdateTimeField
{
public:
	///合约代码
	CInstrumentIDType	InstrumentID;
	///最后修改时间
	CTimeType	UpdateTime;
	///最后修改毫秒
	CMillisecType	UpdateMillisec;
	TYPE_DESCRIPTOR((
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(UpdateTime)
		,
		TYPE_DESC(UpdateMillisec)
	));
};
const DWORD FTD_FID_MarketDataUpdateTime=0x3050;

///深度行情
class CFTDDepthMarketDataField
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
};
const DWORD FTD_FID_DepthMarketData=0x3051;

///订阅合约的相关信息
class CFTDSpecificInstrumentField
{
public:
	///合约代码
	CInstrumentIDType	InstrumentID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(InstrumentID)
	));
};
const DWORD FTD_FID_SpecificInstrument=0x3052;

///共享内存行情查询
class CFTDShmDepthMarketDataField
{
public:
	///合约代码
	CInstrumentIDType	InstrumentID;
	///IP地址
	CIPAddressType	IPAddress;
	///订阅号
	CTopicIDType	TopicID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(IPAddress)
		,
		TYPE_DESC(TopicID)
	));
};
const DWORD FTD_FID_ShmDepthMarketData=0x3053;

///交易所代码
class CFTDMarketDataExchangeIDField
{
public:
	///交易所代码
	CExchangeIDType	ExchangeID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
	));
};
const DWORD FTD_FID_MarketDataExchangeID=0x3056;

///TOPIC查询
class CFTDTopicSearchField
{
public:
	///订阅号
	CTopicIDType	TopicID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TopicID)
	));
};
const DWORD FTD_FID_TopicSearch=0x3057;

///合约状态
class CFTDQmdInstrumentStateField
{
public:
	///交易所代码
	CExchangeIDType	ExchangeID;
	///合约代码
	CInstrumentIDType	InstrumentID;
	///合约交易状态
	CInstrumentStatusType	InstrumentStatus;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InstrumentID)
		,
		TYPE_DESC(InstrumentStatus)
	));
};
const DWORD FTD_FID_QmdInstrumentState=0x3058;

///行情申卖六七属性
class CFTDMarketDataAsk67Field
{
public:
	///申卖价六
	CPriceType	AskPrice6;
	///申卖量六
	CVolumeType	AskVolume6;
	///申卖价七
	CPriceType	AskPrice7;
	///申卖量七
	CVolumeType	AskVolume7;
	TYPE_DESCRIPTOR((
		TYPE_DESC(AskPrice6)
		,
		TYPE_DESC(AskVolume6)
		,
		TYPE_DESC(AskPrice7)
		,
		TYPE_DESC(AskVolume7)
	));
};
const DWORD FTD_FID_MarketDataAsk67=0x3059;

///行情申卖八九属性
class CFTDMarketDataAsk89Field
{
public:
	///申卖价八
	CPriceType	AskPrice8;
	///申卖量八
	CVolumeType	AskVolume8;
	///申卖价九
	CPriceType	AskPrice9;
	///申卖量九
	CVolumeType	AskVolume9;
	TYPE_DESCRIPTOR((
		TYPE_DESC(AskPrice8)
		,
		TYPE_DESC(AskVolume8)
		,
		TYPE_DESC(AskPrice9)
		,
		TYPE_DESC(AskVolume9)
	));
};
const DWORD FTD_FID_MarketDataAsk89=0x305A;

///行情申买六七属性
class CFTDMarketDataBid67Field
{
public:
	///申买价六
	CPriceType	BidPrice6;
	///申买量六
	CVolumeType	BidVolume6;
	///申买价七
	CPriceType	BidPrice7;
	///申买量七
	CVolumeType	BidVolume7;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BidPrice6)
		,
		TYPE_DESC(BidVolume6)
		,
		TYPE_DESC(BidPrice7)
		,
		TYPE_DESC(BidVolume7)
	));
};
const DWORD FTD_FID_MarketDataBid67=0x305B;

///行情申买八九属性
class CFTDMarketDataBid89Field
{
public:
	///申买价八
	CPriceType	BidPrice8;
	///申买量八
	CVolumeType	BidVolume8;
	///申买价九
	CPriceType	BidPrice9;
	///申买量九
	CVolumeType	BidVolume9;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BidPrice8)
		,
		TYPE_DESC(BidVolume8)
		,
		TYPE_DESC(BidPrice9)
		,
		TYPE_DESC(BidVolume9)
	));
};
const DWORD FTD_FID_MarketDataBid89=0x305C;

///行情申买申卖十属性
class CFTDMarketDataAskBid10Field
{
public:
	///申卖价十
	CPriceType	AskPrice10;
	///申卖量十
	CVolumeType	AskVolume10;
	///申买价十
	CPriceType	BidPrice10;
	///申买量十
	CVolumeType	BidVolume10;
	TYPE_DESCRIPTOR((
		TYPE_DESC(AskPrice10)
		,
		TYPE_DESC(AskVolume10)
		,
		TYPE_DESC(BidPrice10)
		,
		TYPE_DESC(BidVolume10)
	));
};
const DWORD FTD_FID_MarketDataAskBid10=0x305D;




#endif
