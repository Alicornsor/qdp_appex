/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file QdFtdcUserApiStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(Qd_FTDCSTRUCT_H)
#define Qd_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QdFtdcUserApiDataType.h"

///响应信息
struct CQdFtdcRspInfoField
{
	///错误代码
	TQdFtdcErrorIDType	ErrorID;
	///错误信息
	TQdFtdcErrorMsgType	ErrorMsg;
};

///Qdp响应信息
struct CQdFtdcQdpRspInfoField
{
	///错误代码
	TQdFtdcErrorIDType	ErrorID;
	///错误信息
	TQdFtdcQdpErrorMsgType	ErrorMsg;
};

///系统用户登录请求
struct CQdFtdcReqUserLoginField
{
	///交易日
	TQdFtdcDateType	TradingDay;
	///交易用户代码
	TQdFtdcUserIDType	UserID;
	///经纪公司编号
	TQdFtdcBrokerIDType	BrokerID;
	///密码
	TQdFtdcPasswordType	Password;
	///用户端产品信息
	TQdFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TQdFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TQdFtdcProtocolInfoType	ProtocolInfo;
	///IP地址
	TQdFtdcIPAddressType	IPAddress;
	///Mac地址
	TQdFtdcMacAddressType	MacAddress;
	///数据中心代码
	TQdFtdcDataCenterIDType	DataCenterID;
	///动态密码
	TQdFtdcPasswordType	OneTimePassword;
	///终端IP地址
	TQdFtdcIPAddressType	ClientIPAddress;
	///授权编码
	TQdFtdcAuthCodeType	AuthCode;
};

///Qdp系统用户登录请求
struct CQdFtdcQdpReqUserLoginField
{
	///交易日
	TQdFtdcDateType	TradingDay;
	///交易用户代码
	TQdFtdcQdpUserIDType	UserID;
	///经纪公司编号
	TQdFtdcBrokerIDType	BrokerID;
	///密码
	TQdFtdcPasswordType	Password;
	///用户端产品信息
	TQdFtdcQdpProductInfoType	UserProductInfo;
	///接口端产品信息
	TQdFtdcQdpProductInfoType	InterfaceProductInfo;
	///协议信息
	TQdFtdcProtocolInfoType	ProtocolInfo;
	///IP地址
	TQdFtdcIPAddressType	IPAddress;
	///Mac地址
	TQdFtdcMacAddressType	MacAddress;
	///数据中心代码
	TQdFtdcDataCenterIDType	DataCenterID;
	///动态密码
	TQdFtdcPasswordType	OneTimePassword;
	///终端IP地址
	TQdFtdcIPAddressType	ClientIPAddress;
};

///系统用户登录应答
struct CQdFtdcRspUserLoginField
{
	///交易日
	TQdFtdcDateType	TradingDay;
	///经纪公司编号
	TQdFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQdFtdcUserIDType	UserID;
	///登录成功时间
	TQdFtdcTimeType	LoginTime;
	///用户最大本地报单号
	TQdFtdcUserOrderLocalIDType	MaxOrderLocalID;
	///交易系统名称
	TQdFtdcTradingSystemNameType	TradingSystemName;
	///数据中心代码
	TQdFtdcDataCenterIDType	DataCenterID;
	///会员私有流当前长度
	TQdFtdcSequenceNoType	PrivateFlowSize;
	///交易员私有流当前长度
	TQdFtdcSequenceNoType	UserFlowSize;
	///登录附加信息
	TQdFtdcLoginInfoType	LoginInfo;
	///会话编号
	TQdFtdcSessionIDType	SessionID;
	///前置编号
	TQdFtdcFrontIDType	FrontID;
};

///Qdp系统用户登录应答
struct CQdFtdcQdpRspUserLoginField
{
	///交易日
	TQdFtdcDateType	TradingDay;
	///经纪公司编号
	TQdFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQdFtdcQdpUserIDType	UserID;
	///登录成功时间
	TQdFtdcTimeType	LoginTime;
	///用户最大本地报单号
	TQdFtdcUserOrderLocalIDType	MaxOrderLocalID;
	///交易系统名称
	TQdFtdcTradingSystemNameType	TradingSystemName;
	///数据中心代码
	TQdFtdcDataCenterIDType	DataCenterID;
	///会员私有流当前长度
	TQdFtdcSequenceNoType	PrivateFlowSize;
	///交易员私有流当前长度
	TQdFtdcSequenceNoType	UserFlowSize;
	///会话编号
	TQdFtdcSessionIDType	SessionID;
	///前置编号
	TQdFtdcFrontIDType	FrontID;
};

///用户登出请求
struct CQdFtdcReqUserLogoutField
{
	///经纪公司编号
	TQdFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQdFtdcUserIDType	UserID;
};

///用户登出请求
struct CQdFtdcRspUserLogoutField
{
	///经纪公司编号
	TQdFtdcBrokerIDType	BrokerID;
	///交易用户代码
	TQdFtdcUserIDType	UserID;
};

///行情基础属性
struct CQdFtdcMarketDataBaseField
{
	///交易日
	TQdFtdcTradingDayType	TradingDay;
	///昨结算
	TQdFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TQdFtdcPriceType	PreClosePrice;
	///昨持仓量
	TQdFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TQdFtdcRatioType	PreDelta;
};

///Qdp行情基础属性
struct CQdFtdcQdpMarketDataBaseField
{
	///交易日
	TQdFtdcTradingDayType	TradingDay;
	///结算组代码
	TQdFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQdFtdcSettlementIDType	SettlementID;
	///昨结算
	TQdFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TQdFtdcPriceType	PreClosePrice;
	///昨持仓量
	TQdFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TQdFtdcRatioType	PreDelta;
};

///行情静态属性
struct CQdFtdcMarketDataStaticField
{
	///今开盘
	TQdFtdcPriceType	OpenPrice;
	///最高价
	TQdFtdcPriceType	HighestPrice;
	///最低价
	TQdFtdcPriceType	LowestPrice;
	///今收盘
	TQdFtdcPriceType	ClosePrice;
	///涨停板价
	TQdFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TQdFtdcPriceType	LowerLimitPrice;
	///今结算
	TQdFtdcPriceType	SettlementPrice;
	///今虚实度
	TQdFtdcRatioType	CurrDelta;
};

///行情最新成交属性
struct CQdFtdcMarketDataLastMatchField
{
	///最新价
	TQdFtdcPriceType	LastPrice;
	///数量
	TQdFtdcVolumeType	Volume;
	///成交金额
	TQdFtdcMoneyType	Turnover;
	///持仓量
	TQdFtdcLargeVolumeType	OpenInterest;
};

///行情最优价属性
struct CQdFtdcMarketDataBestPriceField
{
	///申买价一
	TQdFtdcPriceType	BidPrice1;
	///申买量一
	TQdFtdcVolumeType	BidVolume1;
	///申卖价一
	TQdFtdcPriceType	AskPrice1;
	///申卖量一
	TQdFtdcVolumeType	AskVolume1;
};

///行情申买二、三属性
struct CQdFtdcMarketDataBid23Field
{
	///申买价二
	TQdFtdcPriceType	BidPrice2;
	///申买量二
	TQdFtdcVolumeType	BidVolume2;
	///申买价三
	TQdFtdcPriceType	BidPrice3;
	///申买量三
	TQdFtdcVolumeType	BidVolume3;
};

///行情申卖二、三属性
struct CQdFtdcMarketDataAsk23Field
{
	///申卖价二
	TQdFtdcPriceType	AskPrice2;
	///申卖量二
	TQdFtdcVolumeType	AskVolume2;
	///申卖价三
	TQdFtdcPriceType	AskPrice3;
	///申卖量三
	TQdFtdcVolumeType	AskVolume3;
};

///行情申买四、五属性
struct CQdFtdcMarketDataBid45Field
{
	///申买价四
	TQdFtdcPriceType	BidPrice4;
	///申买量四
	TQdFtdcVolumeType	BidVolume4;
	///申买价五
	TQdFtdcPriceType	BidPrice5;
	///申买量五
	TQdFtdcVolumeType	BidVolume5;
};

///行情申卖四、五属性
struct CQdFtdcMarketDataAsk45Field
{
	///申卖价四
	TQdFtdcPriceType	AskPrice4;
	///申卖量四
	TQdFtdcVolumeType	AskVolume4;
	///申卖价五
	TQdFtdcPriceType	AskPrice5;
	///申卖量五
	TQdFtdcVolumeType	AskVolume5;
};

///行情更新时间属性
struct CQdFtdcMarketDataUpdateTimeField
{
	///合约代码
	TQdFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TQdFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQdFtdcMillisecType	UpdateMillisec;
};

///深度行情
struct CQdFtdcDepthMarketDataField
{
	///交易日
	TQdFtdcTradingDayType	TradingDay;
	///昨结算
	TQdFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TQdFtdcPriceType	PreClosePrice;
	///昨持仓量
	TQdFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TQdFtdcRatioType	PreDelta;
	///今开盘
	TQdFtdcPriceType	OpenPrice;
	///最高价
	TQdFtdcPriceType	HighestPrice;
	///最低价
	TQdFtdcPriceType	LowestPrice;
	///今收盘
	TQdFtdcPriceType	ClosePrice;
	///涨停板价
	TQdFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TQdFtdcPriceType	LowerLimitPrice;
	///今结算
	TQdFtdcPriceType	SettlementPrice;
	///今虚实度
	TQdFtdcRatioType	CurrDelta;
	///最新价
	TQdFtdcPriceType	LastPrice;
	///数量
	TQdFtdcVolumeType	Volume;
	///成交金额
	TQdFtdcMoneyType	Turnover;
	///持仓量
	TQdFtdcLargeVolumeType	OpenInterest;
	///申买价一
	TQdFtdcPriceType	BidPrice1;
	///申买量一
	TQdFtdcVolumeType	BidVolume1;
	///申卖价一
	TQdFtdcPriceType	AskPrice1;
	///申卖量一
	TQdFtdcVolumeType	AskVolume1;
	///申买价二
	TQdFtdcPriceType	BidPrice2;
	///申买量二
	TQdFtdcVolumeType	BidVolume2;
	///申买价三
	TQdFtdcPriceType	BidPrice3;
	///申买量三
	TQdFtdcVolumeType	BidVolume3;
	///申卖价二
	TQdFtdcPriceType	AskPrice2;
	///申卖量二
	TQdFtdcVolumeType	AskVolume2;
	///申卖价三
	TQdFtdcPriceType	AskPrice3;
	///申卖量三
	TQdFtdcVolumeType	AskVolume3;
	///申买价四
	TQdFtdcPriceType	BidPrice4;
	///申买量四
	TQdFtdcVolumeType	BidVolume4;
	///申买价五
	TQdFtdcPriceType	BidPrice5;
	///申买量五
	TQdFtdcVolumeType	BidVolume5;
	///申卖价四
	TQdFtdcPriceType	AskPrice4;
	///申卖量四
	TQdFtdcVolumeType	AskVolume4;
	///申卖价五
	TQdFtdcPriceType	AskPrice5;
	///申卖量五
	TQdFtdcVolumeType	AskVolume5;
	///合约代码
	TQdFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TQdFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQdFtdcMillisecType	UpdateMillisec;
	///交易所代码
	TQdFtdcExchangeIDType	ExchangeID;
	///总卖出数量
	TQdFtdcVolumeType	VolumeAskLot;
	///总买入数量
	TQdFtdcVolumeType	VolumeBidLot;
	///合约状态
	TQdFtdcInstrumentStatusType	InstrumentStatus;
};

///深度行情
struct CQdFtdcQdpDepthMarketDataField
{
	///交易日
	TQdFtdcTradingDayType	TradingDay;
	///结算组代码
	TQdFtdcSettlementGroupIDType	SettlementGroupID;
	///结算编号
	TQdFtdcSettlementIDType	SettlementID;
	///昨结算
	TQdFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TQdFtdcPriceType	PreClosePrice;
	///昨持仓量
	TQdFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TQdFtdcRatioType	PreDelta;
	///今开盘
	TQdFtdcPriceType	OpenPrice;
	///最高价
	TQdFtdcPriceType	HighestPrice;
	///最低价
	TQdFtdcPriceType	LowestPrice;
	///今收盘
	TQdFtdcPriceType	ClosePrice;
	///涨停板价
	TQdFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TQdFtdcPriceType	LowerLimitPrice;
	///今结算
	TQdFtdcPriceType	SettlementPrice;
	///今虚实度
	TQdFtdcRatioType	CurrDelta;
	///最新价
	TQdFtdcPriceType	LastPrice;
	///数量
	TQdFtdcVolumeType	Volume;
	///成交金额
	TQdFtdcMoneyType	Turnover;
	///持仓量
	TQdFtdcLargeVolumeType	OpenInterest;
	///申买价一
	TQdFtdcPriceType	BidPrice1;
	///申买量一
	TQdFtdcVolumeType	BidVolume1;
	///申卖价一
	TQdFtdcPriceType	AskPrice1;
	///申卖量一
	TQdFtdcVolumeType	AskVolume1;
	///申买价二
	TQdFtdcPriceType	BidPrice2;
	///申买量二
	TQdFtdcVolumeType	BidVolume2;
	///申买价三
	TQdFtdcPriceType	BidPrice3;
	///申买量三
	TQdFtdcVolumeType	BidVolume3;
	///申卖价二
	TQdFtdcPriceType	AskPrice2;
	///申卖量二
	TQdFtdcVolumeType	AskVolume2;
	///申卖价三
	TQdFtdcPriceType	AskPrice3;
	///申卖量三
	TQdFtdcVolumeType	AskVolume3;
	///申买价四
	TQdFtdcPriceType	BidPrice4;
	///申买量四
	TQdFtdcVolumeType	BidVolume4;
	///申买价五
	TQdFtdcPriceType	BidPrice5;
	///申买量五
	TQdFtdcVolumeType	BidVolume5;
	///申卖价四
	TQdFtdcPriceType	AskPrice4;
	///申卖量四
	TQdFtdcVolumeType	AskVolume4;
	///申卖价五
	TQdFtdcPriceType	AskPrice5;
	///申卖量五
	TQdFtdcVolumeType	AskVolume5;
	///合约代码
	TQdFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TQdFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQdFtdcMillisecType	UpdateMillisec;
	///交易所代码
	TQdFtdcExchangeIDType	ExchangeID;
};

///订阅合约的相关信息
struct CQdFtdcSpecificInstrumentField
{
	///合约代码
	TQdFtdcInstrumentIDType	InstrumentID;
};

///交易所代码
struct CQdFtdcMarketDataExchangeIDField
{
	///交易所代码
	TQdFtdcExchangeIDType	ExchangeID;
};

///Qdp交易所代码
struct CQdFtdcQdpMarketDataExchangeIDField
{
	///交易所代码
	TQdFtdcExchangeIDType	ExchangeID;
};

///共享内存行情查询
struct CQdFtdcShmDepthMarketDataField
{
	///合约代码
	TQdFtdcInstrumentIDType	InstrumentID;
	///IP地址
	TQdFtdcIPAddressType	IPAddress;
	///订阅号
	TQdFtdcTopicIDType	TopicID;
};

///TOPIC查询
struct CQdFtdcTopicSearchField
{
	///订阅号
	TQdFtdcTopicIDType	TopicID;
};

///分价行情
struct CQdFtdcMBLMarketDataField
{
	///合约代码
	TQdFtdcInstrumentIDType	InstrumentID;
	///买卖方向
	TQdFtdcDirectionType	Direction;
	///价格
	TQdFtdcPriceType	Price;
	///数量
	TQdFtdcVolumeType	Volume;
	///最后修改时间
	TQdFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQdFtdcMillisecType	UpdateMillisec;
};

///套利合约买卖总量
struct CQdFtdcMarketDataCMBVolumeField
{
	///总卖出数量
	TQdFtdcVolumeType	VolumeAskLot;
	///总买入数量
	TQdFtdcVolumeType	VolumeBidLot;
};

///合约状态
struct CQdFtdcQmdInstrumentStateField
{
	///交易所代码
	TQdFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQdFtdcInstrumentIDType	InstrumentID;
	///合约交易状态
	TQdFtdcInstrumentStatusType	InstrumentStatus;
};

///行情合约状态
struct CQdFtdcMarketDataInstrumentStatusField
{
	///合约状态
	TQdFtdcInstrumentStatusType	InstrumentStatus;
};

///信息分发
struct CQdFtdcDisseminationField
{
	///序列系列号
	TQdFtdcSequenceSeriesType	SequenceSeries;
	///序列号
	TQdFtdcSequenceNoType	SequenceNo;
};

///Qdp信息分发
struct CQdFtdcQdpDisseminationField
{
	///序列系列号
	TQdFtdcSequenceSeriesType	SequenceSeries;
	///序列号
	TQdFtdcSequenceNoType	SequenceNo;
};

///行情查询
struct CQdFtdcQryMarketDataField
{
	///交易所代码
	TQdFtdcExchangeIDType	ExchangeID;
	///合约代码
	TQdFtdcInstrumentIDType	InstrumentID;
};

///行情应答
struct CQdFtdcRspMarketDataField
{
	///交易所代码
	TQdFtdcExchangeIDType	ExchangeID;
	///交易日
	TQdFtdcTradingDayType	TradingDay;
	///昨结算
	TQdFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TQdFtdcPriceType	PreClosePrice;
	///昨持仓量
	TQdFtdcLargeVolumeType	PreOpenInterest;
	///昨虚实度
	TQdFtdcRatioType	PreDelta;
	///今开盘
	TQdFtdcPriceType	OpenPrice;
	///最高价
	TQdFtdcPriceType	HighestPrice;
	///最低价
	TQdFtdcPriceType	LowestPrice;
	///今收盘
	TQdFtdcPriceType	ClosePrice;
	///涨停板价
	TQdFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TQdFtdcPriceType	LowerLimitPrice;
	///今结算
	TQdFtdcPriceType	SettlementPrice;
	///今虚实度
	TQdFtdcRatioType	CurrDelta;
	///最新价
	TQdFtdcPriceType	LastPrice;
	///数量
	TQdFtdcVolumeType	Volume;
	///成交金额
	TQdFtdcMoneyType	Turnover;
	///持仓量
	TQdFtdcLargeVolumeType	OpenInterest;
	///申买价一
	TQdFtdcPriceType	BidPrice1;
	///申买量一
	TQdFtdcVolumeType	BidVolume1;
	///申卖价一
	TQdFtdcPriceType	AskPrice1;
	///申卖量一
	TQdFtdcVolumeType	AskVolume1;
	///合约代码
	TQdFtdcInstrumentIDType	InstrumentID;
	///最后修改时间
	TQdFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TQdFtdcMillisecType	UpdateMillisec;
	///合约状态
	TQdFtdcInstrumentStatusType	InstrumentStatus;
};



#endif
