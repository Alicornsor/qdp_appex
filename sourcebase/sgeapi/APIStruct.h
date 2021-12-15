#ifndef APISTRUCT_H
#define APISTRUCT_H
#include "ExchangeDataType.h"

#define	CONTINUE_PACKAGE	'C'
#define	LAST_PACKAGE		'L'
#define	OVER_PACKAGE		'O'

//交易响应信息
struct TTRspMsg
{
	char      Flag;		//连续纪录标志
				//   CONTINUE_PACKAGE：有后续纪录
				//   LAST_PACKAGE：最后一条记录，记录内容非空
				//   OVER_PACKAGE：最后一条记录，记录内容空
 	TRspCode  RspCode;	// 响应代码
 				//   RSP000000：交易成功
 				//   其它：　　　交易不成功
	TRspMsg  RspMsg; //响应消息
};

struct TDissemination
{
	WORD  sequenceSeries;				//标示XTP包的处理协议ID
	UINT  sequenceNo;				//当前XTP包的序号
};

//交易员信息  
struct TTrader
{
	TTraderID  traderID;				//交易员代码
	TPersonName  traderName;				//交易员姓名
	TMemberID  memberID;				//会员代码
	TEncryptPwd  password;				//密码
	TOkFlag  isLogin;				//登录标志
	TDestroyFlag  state;				//状态标志
	TLocalNo  localOrderNo;				//最大本地报单号
	TMachineID  machineID;				//前置机编号
	TCertificateNo  certificateNo;			//证件编号
};

//交易员登录请求信息  
struct TReqTraderLogin
{
	TTraderID  traderID;				//交易员代码   (not null)
	TMemberID  memberID;				//会员代码	(not null)
	TPassword  password;				//密码          (not null)
	TDate  tradeDate;				//交易日期      (not null)
	TIpAddress  ipAddress;				//IP地址
	TLocalNo  localOrderNo;				//最大本地报单号  (not null)
	TMachineID  machineID;				//前置机编号
};

//交易员退出请求信息  
struct TReqTraderLogout
{
	TTraderID  traderID;				//交易员代码     (not null)
	TMemberID  memberID;				//会员代码         (not null)
};                                                                        

//现货报单信息  
struct TSpotOrder
{
	TOrderNo  orderNo;				//报单号	
	TInstID  instID;				//合约代码       (not null)
	TClientID  clientID;				//客户代码       (not null)
	TMemberID  memberID;				//会员代码       (not null)
	TBSFlag  buyOrSell;				//买卖方向       (not null)
	TDate  applyDate;				//申报日期
	TTime  applyTime;				//申报时间
	TTraderID  traderID;				//交易员代码   	(not null)
	TPrice  price;					//价格          (not null)
	TVolume  amount;				//数量        	(not null)
	TVolume  remainAmount;				//剩余数量
	TTime  cancelTime;				//撤消时间
	TTraderID  cancelID;				//撤消员代码
	TOrderStatus  status;				//状态
	TSpotMatchType  matchType;			//类型 		(not null)
	TInstID  endorseInstID;				//转让合约代码  (not null)
	TLocalNo  localOrderNo;				//本地报单号    (not null)
};

//现货报单信息(V2)
struct TSpotOrderEx
{
	TOrderNo  orderNo;				//报单号	
	TInstID  instID;				//合约代码       (not null)
	TClientID  clientID;				//客户代码       (not null)
	TMemberID  memberID;				//会员代码       (not null)
	TBSFlag  buyOrSell;				//买卖方向       (not null)
	TDate  applyDate;				//申报日期
	TTime  applyTime;				//申报时间
	TTraderID  traderID;				//交易员代码   	(not null)
	TPrice  price;					//价格          (not null)
	TVolume  amount;				//数量        	(not null)
	TVolume  remainAmount;				//剩余数量
	TTime  cancelTime;				//撤消时间
	TTraderID  cancelID;				//撤消员代码
	TOrderStatus  status;				//状态
	TSpotMatchType  matchType;			//类型 		(not null)
	TInstID  endorseInstID;				//转让合约代码  (not null)
	TLocalNo  localOrderNo;				//本地报单号    (not null)
	TOrderType  orderType;				//指令类型    (not null)
};

//现货成交单信息  
struct TSpotMatch
{
	TMatchNo  matchNo;				//成交编号
	TBSFlag  buyOrSell;				//买卖方向
	TClientID  clientID;				//客户代码
	TAccountType  clientType;				//客户类型
	TMemberID  memberID;				//会员代码
	TInstID  instID;				//合约代码
	TDate  matchDate;				//成交日期
	TTime  matchTime;				//成交时间
	TPrice  price;				//价格
	TVolume  volume;				//数量
	TOrderNo  orderNo;				//系统报单号
	TLocalNo  localOrderNo;				//报单本地编号
	TSpotMatchType  matchType;				//类型
};

//现货行情  
struct TSpotQuotation
{
	TInstID  instID;				//合约代码
	TInstName  name;				//合约名称
	TPrice  lastClose;				//昨收盘
	TPrice  open;				//开盘价
	TPrice  high;				//最高价
	TPrice  low;				//最低价
	TPrice  last;				//最新价
	TPrice  close;				//收盘价
	TPrice  bid1;				//买价1
	TVolume  bidLot1;				//买量1
	TPrice  bid2;				//买价2
	TVolume  bidLot2;				//买量2
	TPrice  bid3;				//买价3
	TVolume  bidLot3;				//买量3
	TPrice  bid4;				//买价4
	TVolume  bidLot4;				//买量4
	TPrice  bid5;				//买价5
	TVolume  bidLot5;				//买量5
	TPrice  ask1;				//卖价1
	TVolume  askLot1;				//卖量1
	TPrice  ask2;				//卖价2
	TVolume  askLot2;				//卖量2
	TPrice  ask3;				//卖价3
	TVolume  askLot3;				//卖量3
	TPrice  ask4;				//卖价4
	TVolume  askLot4;				//卖量4
	TPrice  ask5;				//卖价5
	TVolume  askLot5;				//卖量5
	TVolume  volume;				//成交量（双边）
	TWeight  weight;				//成交（双边）重量
	TPrice  highLimit;				//涨停板
	TPrice  lowLimit;				//跌停板
	TPrice  upDown;				//涨跌
	TRate  upDownRate;				//涨跌幅度
	TMoney  turnOver;				//成交额
	TPrice  average;				//均价
	TDate  quoteDate;				//行情日期
	TDate  quoteTime;				//行情时间
	TSequence  sequenceNo;				//行情序号,每天从1开始递增
};

//现货延期交收报单  
struct TDeferOrder
{
	TOrderNo  orderNo;				//报单号        (not null)
	TClientID  clientID;				//客户代码       (not null)
	TInstID  instID;				//合约代码       (not null)
	TMemberID  memberID;				//会员代码       (not null)
	TBSFlag  buyOrSell;				//买卖方向       (not null)
	TDate  applyDate;				//申报日期
	TTime  applyTime;				//申报时间
	TOffsetFlag  offSetFlag;				//开平仓标志      (not null)
	TPrice  price;				//价格                       (not null)
	TVolume  amount;				//数量            (not null)
	TVolume  remainAmount;				//剩余数量
	TTime  cancelTime;				//撤消时间
	TOrderStatus  status;				//状态
	TLocalNo  localOrderNo;				//本地报单号          (not null)
	TRate  margin;				//保证金率
	TRateType  marginType;				//保证金类型           (not null)
	TTraderID  traderID;				//交易员代码          (not null)
	TTraderID  cancelID;				//撤消员代码
	TMatchType  matchType;				//类型                (not null)
};

//现货延期交收报单(V2)
struct TDeferOrderEx
{
	TOrderNo  orderNo;				//报单号        (not null)
	TClientID  clientID;				//客户代码       (not null)
	TInstID  instID;				//合约代码       (not null)
	TMemberID  memberID;				//会员代码       (not null)
	TBSFlag  buyOrSell;				//买卖方向       (not null)
	TDate  applyDate;				//申报日期
	TTime  applyTime;				//申报时间
	TOffsetFlag  offSetFlag;				//开平仓标志      (not null)
	TPrice  price;				//价格                       (not null)
	TVolume  amount;				//数量            (not null)
	TVolume  remainAmount;				//剩余数量
	TTime  cancelTime;				//撤消时间
	TOrderStatus  status;				//状态
	TLocalNo  localOrderNo;				//本地报单号          (not null)
	TRate  margin;				//保证金率
	TRateType  marginType;				//保证金类型           (not null)
	TTraderID  traderID;				//交易员代码          (not null)
	TTraderID  cancelID;				//撤消员代码
	TMatchType  matchType;				//类型                (not null)
	TOrderType  orderType;				//指令类型    (not null)
};

//现货延期交收交割申报报单  
struct TDeferDeliveryAppOrder
{
	TOrderNo  orderNo;				//报单编号
	TClientID  clientID;				//客户代码           (not null)
	TInstID  instID;				//合约代码            (not null)
	TBSFlag  buyOrSell;				//买卖方向          (not null)
	TDate  applyDate;				//申请日期
	TTime  applyTime;				//申请时间
	TVolume  amount;				//数量             (not null)
	TTime  cancelTime;				//撤消时间
	TOrderStatus  status;				//报单状态
	TLocalNo  localOrderID;				//本地报单编号     (not null)
	TMemberID  memberID;				//会员代码           (not null)
	TTraderID  traderID;				//交易员代码         (not null)
	TTraderID  cancelID;				//撤消员代码
	TVolume  remainAmount;				//剩余数量
};

//现货延期交收中立仓申报报单  
struct TMiddleAppOrder
{
	TOrderNo  orderNo;				//报单编号
	TClientID  clientID;				//客户代码        (not null)
	TInstID  instID;				//合约代码        (not null)
	TMemberID  memberID;				//会员代码          (not null)
	TBSFlag  buyOrSell;				//买卖方向          (not null)
	TDate  applyDate;				//申请日期
	TTime  applyTime;				//申请时间
	TVolume  amount;				//数量              (not null)
	TTime  cancelTime;				//撤消时间
	TOrderStatus  status;				//报单状态
	TLocalNo  localOrderID;				//本地报单编号       (not null)
	TTraderID  traderID;				//交易员代码         (not null)
	TTraderID  cancelID;				//撤消员代码
	TVolume  remainAmount;				//剩余数量
};

//现货延期交收成交单  
struct TDeferMatch
{
	TMatchNo  matchNo;				//成交编号
	TBSFlag  buyOrSell;				//买卖方向
	TClientID  clientID;				//客户代码
	TAccountType  clientType;				//客户类型
	TInstID  instID;				//合约代码
	TMemberID  memberID;				//会员代码
	TDate  matchDate;				//成交日期
	TTime  matchTime;				//成交时间
	TPrice  price;				//价格
	TVolume  volume;				//数量
	TOffsetFlag  offsetFlag;				//开平标志
	TOrderNo  orderNo;				//系统报单号
	TLocalNo  localOrderNo;				//报单本地编号
};

//现货延期交收行情  
struct TDeferQuotation
{
	TInstID  instID;				//合约代码
	TInstName  name;				//合约名称
	TPrice  lastSettle;				//昨结算
	TPrice  lastClose;				//昨收盘
	TPrice  open;				//开盘价
	TPrice  high;				//最高价
	TPrice  low;				//最低价
	TPrice  last;				//最新价
	TPrice  close;				//收盘价
	TPrice  settle;				//结算价
	TPrice  bid1;				//买价1
	TVolume  bidLot1;				//买量1
	TPrice  bid2;				//买价2
	TVolume  bidLot2;				//买量2
	TPrice  bid3;				//买价3
	TVolume  bidLot3;				//买量3
	TPrice  bid4;				//买价4
	TVolume  bidLot4;				//买量4
	TPrice  bid5;				//买价5
	TVolume  bidLot5;				//买量5
	TPrice  ask1;				//卖价1
	TVolume  askLot1;				//卖量1
	TPrice  ask2;				//卖价2
	TVolume  askLot2;				//卖量2
	TPrice  ask3;				//卖价>3
	TVolume  askLot3;				//卖量3
	TPrice  ask4;				//卖价4
	TVolume  askLot4;				//卖量4
	TPrice  ask5;				//卖价5
	TVolume  askLot5;				//卖量5
	TVolume  volume;				//成交量
	TWeight  weight;				//成交（双边）重量
	TPrice  highLimit;				//涨停板
	TPrice  lowLimit;				//跌停板
	TVolume  Posi;				//持仓量
	TPrice  upDown;				//涨跌
	TRate  upDownRate;				//涨跌幅度
	TMoney  turnOver;				//成交额
	TPrice  average;				//均价
	TDate  quoteDate;				//行情日期
	TTime  quoteTime;				//行情时间
	TSequence  sequenceNo;				//行情序号
};

//期货报单  
struct TFuturesOrder
{
	TOrderNo  orderNo;				//报单号
	TClientID  clientID;				//客户代码               (not null)
	TInstID  instID;				//合约代码                (not null)
	TMemberID  memberID;				//会员代码               (not null)
	TBSFlag  buyOrSell;				//买卖方向               (not null)
	TDate  applyDate;				//申报日期
	TTime  applyTime;				//申报时间
	TOffsetFlag  offsetFlag;				//开平仓标志      (not null)
	TPrice  price;				//价格                            (not null)
	TVolume  amount;				//数量                      (not null)
	TVolume  remainAmount;				//剩余数量
	TTime  cancelTime;				//撤消时间
	TOrderStatus  status;				//状态
	TLocalNo  localOrderNo;				//本地报单号               (not null)
	TRate  margin;				//保证金率
	TRateType  marginType;				//保证金类型               (not null)
	TTraderID  traderID;				//交易员代码                 (not null)
	TTraderID  cancelID;				//撤消员代码
	TMatchType  matchType;				//类型                         (not null)
};

//递延交割申报成交单  
struct TDeferDeliveryAppMatch
{
	TMatchNo  matchNo;				//成交序号
	TClientID  clientID;				//客户代码
	TInstID  instID;				//合约代码
	TMemberID  memberID;				//会员代码
	TBSFlag  buyOrSell;				//买卖方向
	TVolume  volume;				//数量
	TDate  matchDate;				//成交日期
	TTime  matchTime;				//成交时间
	TOrderNo  orderNo;				//报单号
	TLocalNo  LocalOrderNo;				//报单本地编号
	TOkFlag  middleFlag;				//是否为中立仓
};

//期货成交单  
struct TFuturesMatch
{
	TMatchNo  matchNo;				//成交编号
	TBSFlag  buyOrSell;				//买卖方向
	TClientID  clientID;				//客户代码
	TAccountType  clientType;				//客户类型
	TInstID  instID;				//合约代码
	TMemberID  memberID;				//会员代码
	TDate  matchDate;				//成交日期
	TTime  matchTime;				//成交时间
	TPrice  price;				//价格
	TVolume  volume;				//数量
	TRate  marginRate;				//保证金率
	TRateType  rateType;				//保证金类型
	TOffsetFlag  offsetFlag;				//开平标志
	TOrderNo  orderNo;				//系统报单号
	TLocalNo  localOrderNo;				//报单本地编号
};

//期货行情  
struct TFuturesQuotation
{
	TInstID  instID;				//合约代码
	TInstName  name;				//合约名称
	TPrice  lastSettle;				//昨结算
	TPrice  lastClose;				//昨收盘
	TPrice  open;				//开盘价
	TPrice  high;				//最高价
	TPrice  low;				//最低价
	TPrice  last;				//最新价
	TPrice  close;				//收盘价
	TPrice  settle;				//结算价
	TPrice  bid1;				//买价1
	TVolume  bidLot1;				//买量1
	TPrice  bid2;				//买价2
	TVolume  bidLot2;				//买量2
	TPrice  bid3;				//买价3
	TVolume  bidLot3;				//买量3
	TPrice  bid4;				//买价4
	TVolume  bidLot4;				//买量4
	TPrice  bid5;				//买价5
	TVolume  bidLot5;				//买量5
	TPrice  ask1;				//卖价1
	TVolume  askLot1;				//卖量1
	TPrice  ask2;				//卖价2
	TVolume  askLot2;				//卖量2
	TPrice  ask3;				//卖价>3
	TVolume  askLot3;				//卖量3
	TPrice  ask4;				//卖价4
	TVolume  askLot4;				//卖量4
	TPrice  ask5;				//卖价5
	TVolume  askLot5;				//卖量5
	TVolume  volume;				//成交量
	TWeight  weight;				//成交（双边）重量
	TPrice  highLimit;				//涨停板
	TPrice  lowLimit;				//跌停板
	TVolume  Posi;				//持仓量
	TPrice  upDown;				//涨跌
	TRate  upDownRate;				//涨跌幅度
	TMoney  turnOver;				//成交额
	TPrice  average;				//均价
	TDate  quoteDate;				//行情日期
	TTime  quoteTime;				//行情时间
	TSequence  sequenceNo;				//行情序号
};

//现货T+N报单  
struct TForwardOrder
{
	TOrderNo  orderNo;				//报单号             
	TInstID  instID;				//合约代码           (not null)
	TClientID  clientID;				//客户代码            (not null)
	TMemberID  memberID;				//会员代码          (not null)
	TBSFlag  buyOrSell;				//买卖方向          (not null)
	TDate  applyDate;				//申报日期
	TTime  applyTime;				//申报时间
	TTraderID  traderID;				//交易员代码        (not null)
	TPrice  price;				//价格                      (not null)
	TVolume  amount;				//数量               (not null)
	TVolume  remainAmount;				//剩余数量
	TTime  cancelTime;				//撤消时间
	TTraderID  cancelID;				//撤消员代码
	TOrderStatus  status;				//状态
	TLocalNo  localOrderNo;				//本地报单号         (not null)
	TMatchType  matchType;				//类型			(not null)
};

//现货T+N报单(V2)
struct TForwardOrderEx
{
	TOrderNo  orderNo;				//报单号             
	TInstID  instID;				//合约代码           (not null)
	TClientID  clientID;				//客户代码            (not null)
	TMemberID  memberID;				//会员代码          (not null)
	TBSFlag  buyOrSell;				//买卖方向          (not null)
	TDate  applyDate;				//申报日期
	TTime  applyTime;				//申报时间
	TTraderID  traderID;				//交易员代码        (not null)
	TPrice  price;				//价格                      (not null)
	TVolume  amount;				//数量               (not null)
	TVolume  remainAmount;				//剩余数量
	TTime  cancelTime;				//撤消时间
	TTraderID  cancelID;				//撤消员代码
	TOrderStatus  status;				//状态
	TLocalNo  localOrderNo;				//本地报单号         (not null)
	TMatchType  matchType;				//类型			(not null)
	TOrderType  orderType;				//指令类型    (not null)
};

//现货T+N成交单  
struct TForwardMatch
{
	TMatchNo  matchNo;				//成交编号
	TBSFlag  buyOrSell;				//买卖方向
	TClientID  clientID;				//客户代码
	TAccountType  clientType;				//客户类型
	TInstID  instID;				//合约代码
	TMemberID  memberID;				//会员代码
	TDate  matchDate;				//成交日期
	TTime  matchTime;				//成交时间
	TPrice  price;				//价格
	TVolume  volume;				//数量
	TRate  marginRate;				//保证金率
	TRateType  rateType;				//保证金类型
	TOrderNo  orderNo;				//系统报单号
	TLocalNo  localOrderNo;				//报单本地编号
};

//现货T+N行情  
struct TForwardQuotation
{
	TInstID  instID;				//合约代码
	TInstName  name;				//合约名称
	TPrice  lastSettle;				//昨结算
	TPrice  lastClose;				//昨收盘
	TPrice  open;				//开盘价
	TPrice  high;				//最高价
	TPrice  low;				//最低价
	TPrice  last;				//最新价
	TPrice  close;				//收盘价
	TPrice  settle;				//结算价
	TPrice  bid1;				//买价1
	TVolume  bidLot1;				//买量1
	TPrice  bid2;				//买价2
	TVolume  bidLot2;				//买量2
	TPrice  bid3;				//买价3
	TVolume  bidLot3;				//买量3
	TPrice  bid4;				//买价4
	TVolume  bidLot4;				//买量4
	TPrice  bid5;				//买价5
	TVolume  bidLot5;				//买量5
	TPrice  ask1;				//卖价1
	TVolume  askLot1;				//卖量1
	TPrice  ask2;				//卖价2
	TVolume  askLot2;				//卖量2
	TPrice  ask3;				//卖价>3
	TVolume  askLot3;				//卖量3
	TPrice  ask4;				//卖价4
	TVolume  askLot4;				//卖量4
	TPrice  ask5;				//卖价5
	TVolume  askLot5;				//卖量5
	TVolume  volume;				//成交量
	TWeight  weight;				//成交（双边）重量
	TPrice  highLimit;				//涨停板
	TPrice  lowLimit;				//跌停板
	TVolume  Posi;				//持仓量
	TPrice  upDown;				//涨跌
	TRate  upDownRate;				//涨跌幅度
	TMoney  turnOver;				//成交额
	TPrice  average;				//均价
	TDate  quoteDate;				//行情日期
	TTime  quoteTime;				//行情时间
	TSequence  sequenceNo;				//行情序号
};

//交易员密码修改请求  
struct TReqTraderPasswordUpdate
{
	TTraderID  traderID;				//交易员代码(not null)
	TMemberID  memberID;				//会员代码       (not null)
	TPassword  oldPassword;				//旧密码       (not null)
	TPassword  newPassword;				//新密码      (not null)
};

//会员应急密码修改请求  
struct TReqMemberUrgentPasswordUpdate
{
	TMemberID  memberID;				//会员代码      (not null)
	TPassword  oldPassword;				//旧密码         (not null)
	TPassword  newPassword;				//新密码         (not null)
};

//会员资金查询请求  
struct TReqQryMemberCapital
{
	TMemberID  memberID;				//会员代码          (not null)
	TAccountType  accountType;				//帐户类型
};

//会员资金  
struct TMemberCapital
{
	TMemberID  memberID;				//会员代码
	TAccountType  accountType;				//帐户类型
	TMoney  available;				//可提资金
	TMoney  lastBalance;				//上日结算准备金余额
	TMoney  lastOccupied;				//上日占用保证金
	TMoney  todayBalance;				//当日结算准备金余额
	TMoney  todayOccupied;				//当日占用保证金
	TMoney  profit;				//当日盈亏
	TMoney  todayIn;				//当日入金
	TMoney  todayOut;				//当日出金
	TMoney  Payment;				//支付的货款额
	TMoney  Received;				//收到的货款额
	TMoney  miscFee;				//费用
	TMoney  frozen;				//冻结保证金 
	TMoney  basefund;				//基础保证金
};

//Added by qingquan.xue 20140310 begin
struct TMemberCapitalEx
{
	TMemberID		memberID;				// 会员代码 
	TAccountType	accountType;			// 帐户类型 
	//TMoney			totalRights;		// 总权益 
	//TMoney			cash;				// 实有货币资金 
	TMoney			offsetOutLimit;			// 充抵出金限制金额  
	TMoney			lastAvailable;			// 上日可提资金
	TMoney			todayAvailable;			// 当日可提资金 
	TMoney			lastCashBalance;		// 上日货币交易可报价余额 
	TMoney			todayCashBalance;		// 当日货币交易可报价余额 
	TMoney			lastQuotaBalance;		// 上日额度交易可报价余额 
	TMoney			todayQuotaBalance;		// 当日额度交易可报价余额 
	TMoney			todayOffsetQuota;		// 实际充抵额度 
	TMoney			lastUsedOffsetQuota;	// 上日已用充抵额度 
	TMoney			todayUsedOffsetQuota;	// 当日已用充抵额度 
	TMoney			availOffsetQuota;		// 待用充抵额度 
	TMoney			lastCashOccupied;		// 上日货币交易保证金占用 
	TMoney			todayCashOccupied;		// 当日货币交易保证金占用 
	TMoney			lastQuotaOccupied;		// 上日额度交易保证金占用 
	TMoney			todayQuotaOccupied;		// 当日额度交易保证金占用 
	TMoney			cashFrozen;				// 货币交易冻结保证金 
	TMoney			quotaFrozen;			// 额度交易冻结保证金 
	TMoney			profit;					// 当日盈亏 
	TMoney			todayIn;				// 当日入金 
	TMoney			todayOut;				// 当日出金 
	TMoney			Payment;				// 支付的货款额 
	TMoney			Received;				// 收到的货款额 
	TMoney			miscFee;				// 费用 
	TMoney			basefund;				// 基础保证金 
};
// Added by qingquan.xue 20140310 end

//客户库存查询请求  
struct TReqQryClientStorage
{
	TClientID  clientID;				//客户代码     (not null)
	TMemberID  memberID;				//会员代码       (not null)
};

//客户库存  
struct TClientStorage
{
	TClientID  clientID;				//客户代码
	TMemberID  memberID;				//会员代码
	TVarietyID  varietyID;				//交割品种代码
	TWeight  totalStorage;				//库存总量
	TWeight  availableStorage;				//可用库存
	TWeight  frozenStorage;				//现货冻结库存
	TWeight  pendStorage;				//待提库存
	TWeight  impawnStorage;				//质押库存
	TWeight  lawFrozen;				//法律冻结库存
	TWeight  todayBuy;				//当日买入
	TWeight  todaySell;				//当日卖出
	TWeight  todayDeposit;				//当日存入
	TWeight  todayDraw;				//当日提出
	TWeight  todayLend;				//当日借出
	TWeight  todayBorrow;				//当日借入
	TWeight  todayShiftOut;				//当日转出
	TWeight  todayShiftIn;				//当日转入
};

// Added by qingquan.xue 20140310 begin
struct TClientStorageEx
{
	TClientID	clientID;				//客户代码
	TMemberID	memberID;				//会员代码
	TVarietyID  varietyID;				//交割品种代码
	TWeight		totalStorage;			//库存总量
	TWeight		availableStorage;		//可用库存
	TWeight		frozenStorage;			//现货冻结库存
	TWeight		pendStorage;			//待提库存
	TWeight		impawnStorage;			//质押库存
	TWeight		lawFrozen;				//法律冻结库存
	TWeight		todayBuy;				//当日买入
	TWeight		todaySell;				//当日卖出
	TWeight		todayDeposit;			//当日存入
	TWeight		todayDraw;				//当日提出
	TWeight		todayLend;				//当日借出
	TWeight		todayBorrow;			//当日借入
	TWeight		todayShiftOut;			//当日转出
	TWeight		todayShiftIn;			//当日转入
	TWeight		offsetStorage;			//充抵库存
};
// Added by qingquan.xue 20140310 end

//报单查询请求  
struct TReqQryOrder
{
	TInstID  instID;				//合约代码
	TMarketID  marketID;				//市场代码         (not null)
	TOrderNo  orderNo;				//报单号
	TClientID  clientID;				//客户代码
	TMemberID  memberID;				//会员代码
	TOffsetFlag  offsetFlag;				//开平标志
};

//本地报单号查询请求
struct TReqQryLocalOrder
{
	TMemberID  memberID;				//会员代码		(not null)
	TClientID  clientID;				//会员代码      (not null)
	TLocalNo  localOrderNo;				//本地报单号    (not null)
};

//成交查询请求  
struct TReqQryMatch
{
	TInstID  instID;				//合约代码
	TMarketID  marketID;				//市场代码      (not null)
	TOrderNo  orderNo;				//报单号
	TClientID  clientID;				//客户代码
	TMemberID  memberID;				//会员代码
	TMatchNo  matchNo;				//成交编号
};

//行情查询请求  
struct TReqQryQuotation
{
	TInstID  instID;				//合约代码
	TMarketID  marketID;				//市场代码        (not null)
};

//会员持仓查询请求  
struct TReqQryMemberPosi
{
	TMemberID  memberID;				//会员代码
	TMarketID  marketID;				//市场代码         (not null)
	TInstID  instID;				//合约代码
};

//会员现货延期交收持仓  
struct TDeferMemberPosi
{
	TMemberID  memberID;				//会员代码
	TInstID  instID;				//合约代码
	TVolume  longPosi;				//多头持仓量
	TVolume  shortPosi;				//空头持仓量
	TVolume  lastLong;				//上日多头持仓
	TVolume  lastShort;				//上日空头持仓
	TVolume  todayLong;				//今日多头开仓
	TVolume  todayShort;				//今日空头开仓
	TVolume  todayOffsetLong;				//今日多头平仓量
	TVolume  todayOffsetShort;				//今日空头平仓量
	TMoney  longTurnOver;				//多头持仓金额
	TMoney  shortTurnOver;				//空头持仓金额
	TVolume  deliveryApplyLongFrozen;				//交割申报多头冻结
	TVolume  deliveryApplyShortFrozen;				//交割申报空头冻结
	TVolume  deliveryApplyLong;				//交割申报使用多头持仓
	TVolume  deliveryApplyShort;				//交割申报使用空头持仓
	TVolume  longLimitFrozen;				//多头开仓冻结限额
	TVolume  shortLimitFrozen;				//空头开仓冻结限额
	TVolume  offsetLongFrozen;				//多头平仓冻结
	TVolume  offsetShortFrozen;				//空头平仓冻结
};

//会员期货持仓  
struct TFuturesMemberPosi
{
	TMemberID  memberID;				//会员代码
	TInstID  instID;				//合约代码
	TVolume  longPosi;				//多头持仓量
	TVolume  shortPosi;				//空头持仓量
	TVolume  lastLong;				//上日多头持仓
	TVolume  lastShort;				//上日空头持仓
	TVolume  todayLong;				//今日多头开仓
	TVolume  todayShort;				//今日空头开仓
	TVolume  todayOffsetLong;				//今日多头平仓量
	TVolume  todayOffsetShort;				//今日空头平仓量
	TMoney  longTurnOver;				//多头持仓金额
	TMoney  shortTurnOver;				//空头持仓金额
	TVolume  longLimitFrozen;				//多头开仓冻结限额
	TVolume  shortLimitFrozen;				//空头开仓冻结限额
	TVolume  offsetLongFrozen;				//多头平仓冻结
	TVolume  offsetShortFrozen;				//空头平仓冻结
};

//会员现货T+N持仓  
struct TForwardMemberPosi
{
	TMemberID  memberID;				//会员代码
	TInstID  instID;				//合约代码
	TDate  dueDate;				//到期日
	TVolume  longPosi;				//多头持仓量
	TVolume  shortPosi;				//空头持仓量
	TVolume  lastLong;				//上日多头持仓
	TVolume  lastShort;				//上日空头持仓
	TVolume  todayLong;				//今日多头开仓
	TVolume  todayShort;				//今日空头开仓
	TVolume  todayOffsetLong;				//今日多头平仓量
	TVolume  todayOffsetShort;				//今日空头平仓量
	TMoney  longTurnOver;				//多头持仓金额
	TMoney  shortTurnOver;				//空头持仓金额
	TVolume  longLimitFrozen;				//多头开仓冻结限额
	TVolume  shortLimitFrozen;				//空头开仓冻结限额
	TVolume  offsetLongFrozen;				//多头平仓冻结
	TVolume  offsetShortFrozen;				//空头平仓冻结
};

//客户持仓查询请求  
struct TReqQryClientPosi
{
	TClientID  clientID;				//客户代码
	TMemberID  memberID;				//会员代码    (not null)
	TMarketID  marketID;				//市场代码      (not null)
	TInstID  instID;				//合约代码
};

//客户现货延期交收持仓  
struct TDeferClientPosi
{
	TInstID  instID;				//合约代码
	TClientID  clientID;				//客户代码
	TMemberID  memberID;				//会员代码
	TVolume  longPosi;				//多头持仓量
	TVolume  shortPosi;				//空头持仓量
	TVolume  lastLong;				//上日多头持仓
	TVolume  lastShort;				//上日空头持仓
	TVolume  todayLong;				//今日多头开仓
	TVolume  todayShort;				//今日空头开仓
	TVolume  todayOffsetLong;				//今日多头平仓量
	TVolume  todayOffsetShort;				//今日空头平仓量
	TMoney  longTurnOver;				//多头持仓金额
	TMoney  shortTurnOver;				//空头持仓金额
	TVolume  deliveryApplyLongFrozen;				//交割申报多头冻结
	TVolume  deliveryApplyShortFrozen;				//交割申报空头冻结
	TVolume  deliveryApplyLong;				//交割申报使用多头持仓
	TVolume  deliveryApplyShort;				//交割申报使用空头
	TVolume  longLimitFrozen;				//持仓多头开仓冻结限额
	TVolume  shortLimitFrozen;				//空头开仓冻结限额
	TVolume  offsetLongFrozen;				//多头平仓冻结
	TVolume  offsetShortFrozen;				//空头平仓冻结
};

//客户期货持仓  
struct TFuturesClientPosi
{
	TInstID  instID;				//合约代码
	TClientID  clientID;				//客户代码
	TMemberID  memberID;				//会员代码
	TVolume  longPosi;				//多头持仓量
	TVolume  shortPosi;				//空头持仓量
	TVolume  lastLong;				//上日多头持仓
	TVolume  lastShort;				//上日空头持仓
	TVolume  todayLong;				//今日多头开仓
	TVolume  todayShort;				//今日空头开仓
	TVolume  todayOffsetLong;				//今日多头平仓量
	TVolume  todayOffsetShort;				//今日空头平仓量
	TMoney  longTurnOver;				//多头持仓金额
	TMoney  shortTurnOver;				//空头持仓金额
	TVolume  longLimitFrozen;				//持仓多头开仓冻结限额
	TVolume  shortLimitFrozen;				//空头开仓冻结限额
	TVolume  offsetLongFrozen;				//多头平仓冻结
	TVolume  offsetShortFrozen;				//空头平仓冻结
};

//客户现货T+N持仓  
struct TForwardClientPosi
{
	TInstID  instID;				//合约代码
	TClientID  clientID;				//客户代码
	TMemberID  memberID;				//会员代码
	TDate  dueDate;				//到期日
	TVolume  longPosi;				//多头持仓量
	TVolume  shortPosi;				//空头持仓量
	TVolume  lastLong;				//上日多头持仓
	TVolume  lastShort;				//上日空头持仓
	TVolume  todayLong;				//今日多头开仓
	TVolume  todayShort;				//今日空头开仓
	TVolume  todayOffsetLong;				//今日多头平仓量
	TVolume  todayOffsetShort;				//今日空头平仓量
	TMoney  longTurnOver;				//多头持仓金额
	TMoney  shortTurnOver;				//空头持仓金额
	TVolume  longLimitFrozen;				//持仓多头开仓冻结限额
	TVolume  shortLimitFrozen;				//空头开仓冻结限额
	TVolume  offsetLongFrozen;				//多头平仓冻结
	TVolume  offsetShortFrozen;				//空头平仓冻结
};

//监控员登录请求  
struct TReqUserLogin
{
	TTraderID  userID;				//操作员代码          (not null)
	TPassword  password;				//密码                   (not null)
	TDate  tradeDate;				//交易日期
	TLocalNo  localOrderNo;				//最大本地报单号       (not null)
	TMachineID  machineID;				//前置机编号
	TOperatorType  operatorType;				//操作员类型      (not null)
	TMonitorType monitorType;			//监控员类型
};

//操作员信息  
struct TUser
{
	TTraderID  userID;				//操作员代码
	TPersonName  userName;				//操作员姓名
	TEncryptPwd  password;				//密码
	TOkFlag  isLogin;				//登录标志
	TDestroyFlag  state;				//状态标志
	TDeptID  deptID;				//部门代码
	TLocalNo  localOrderNo;				//最大本地报单号
	TMachineID  machineID;				//前置机编号
	TMonitorType monitorType;			//监控员类型
};

//监控员退出请求  
struct TReqUserLogout
{
	TTraderID  userID;				//操作员代码          (not null)
};

//合约交易状态信息  
struct TInstState
{
	TInstID  instID;				//合约代码
	TInstStateFlag  tradeState;				//合约交易状态
};

//合约交易状态查询请求  
struct TReqQryInstState
{
	TInstID  instID;				//合约代码
	TMarketID  marketID;				//市场代码       (not null)
};

//市场交易状态信息  
struct TMarketState
{
	TMarketID  marketID;				//市场代码           
	TMarketStateFlag  marketState;				//市场交易状态
};

//市场交易状态查询请求  
struct TReqQryMarketState
{
	TMarketID  marketID;				//市场代码           (not null)
};

//现货延期交收补偿费率信息  
struct TDeferFeeRate
{
	TDate  effectDate;				//日期
	TInstID  instID;				//合约代码
	TPayDirection  payDirection;				//支付方向
	TRate  feeRate;				//递延费率
};

//交易员在线查询请求  
struct TReqQryTrader
{
	TTraderID  traderID;				//交易员代码          
};

//交易所公告信息  
struct TBulletinBoard
{
	TMemberID  memberID;				//会员代码
	TSequence  seqNo;				//序号
	TDate  announceDate;				//发布日期
	TTime  announceTime;				//发布时间
	TDeptID  deptID;				//部门代码
	TName  title;				//标题
	TMemo  content;				//内容
	TTraderID  announcer;				//发布人
};

//会员信息  
struct TMember
{
	TMemberID  memberID;				//会员代码
	TAbbr  abbr;				//简称
	TTradeRight  tradeRight;				//交易权限
	TClassID  classID;				//会员级别
	TBizType  bizType;				//经营性质
	TMemberType  memberType;				//会员类型
	TDestroyFlag  destroyFlag;				//注销状态
	TDate  destroyDate;				//注销日期
	TOkFlag  urgentTradeFlag;				//应急交易标志
	TEncryptPwd  urgentPassword;				//应急交易密码
	TVolume  urgentNumber;				//应急交易次数
	TVolume  traderNumber;				//最大登录交易员数
};

//客户信息  
struct TClient
{
	TClientID  clientID;				//客户代码
	TMemberID  memberID;				//会员代码
	TTradeRight  tradeRight;				//交易权限
	TAccountType  clientType;				//客户类型
	TDestroyFlag  destroyFlag;				//注销状态
	TCode	clientSort;					//客户类别
};

//网络地址限制  
struct TNetworkAddressLimit
{
	TMemberID  memberID;				//会员代码
	TConnectType  connectType;				//上网类型
	TIpAddress  ipAddress;				//IP地址
	TVolume  portNumber;				//端口号
	TOpenFlag  openFlag;				//活跃标志
};

//会员市场权限信息  
struct TMemberMarketRight
{
	TMarketID  marketID;				//市场代码
	TMemberID  memberID;				//会员代码
	TTradeRight  tradeRight;				//交易权限描述
};

//会员现货合约权限信息  
struct TMemberSpotInstRight
{
	TInstID  instID;				//合约代码
	TMemberID  memberID;				//会员代码
	TTradeRight  tradeRight;				//交易权限描述
	TAccountType  accountType;				//帐户类型
};

//会员合约持仓限额  
struct TMemberInstPosiLimit
{
	TMarketID  marketID;				//市场代码
	TMemberID  memberID;				//会员代码
	TInstID  instID;				//合约代码
	TDirection  direction;				//多空方向
	TVolume  limit;				//上限
};

//客户合约持仓限额  
struct TClientInstPosiLimit
{
	TMarketID  marketID;				//市场代码
	TClientID  clientID;				//客户代码
	TMemberID  memberID;				//会员代码
	TInstID  instID;				//合约代码
	TDirection  direction;				//多空方向
	TVolume  limit;				//上限
};

//现货T+N强平成交单  
struct TForwardForceMatch
{
	TMatchNo  matchNo;				//成交编号
	TBSFlag  buyOrSell;				//买卖方向
	TDate  matchDate;				//成交日期
	TTime  matchTime;				//成交时间
	TClientID  clientID;				//客户代码
	TAccountType  clientType;				//客户类型
	TMemberID  memberID;				//会员代码
	TInstID  instID;				//合约代码
	TPrice  price;				//价格
	TVolume  volume;				//数量
	TMatchNo  orignalMatchNo;				//原来成交编号
	TTraderID  operatorID;				//操作员代码
};

//现货撤单请求  
struct TSpotOrderCancel
{
	TOrderNo  orderNo;				//报单号         (not null)
	TInstID  instID;				//合约代码        (not null)
	TClientID  clientID;				//客户代码       (not null)
	TMemberID  memberID;				//会员代码         (not null)
	TTraderID  traderID;				//交易员代码      (not null)
};

//现货延期交收撤单请求  
struct TDeferOrderCancel
{
	TOrderNo  orderNo;				//报单号             (not null)
	TInstID  instID;				//合约代码             (not null)
	TClientID  clientID;				//客户代码           (not null)
	TMemberID  memberID;				//会员代码            (not null)
	TTraderID  traderID;				//交易员代码           (not null)
};

//期货撤单请求  
struct TFuturesOrderCancel
{
	TOrderNo  orderNo;				//报单号               (not null)
	TInstID  instID;				//合约代码              (not null)
	TClientID  clientID;				//客户代码              (not null)
	TMemberID  memberID;				//会员代码              (not null)
	TTraderID  traderID;				//交易员代码          (not null)
};

//现货T+N撤单请求  
struct TForwardOrderCancel
{                                                                           
	TOrderNo  orderNo;				//报单号            (not null)
	TInstID  instID;				//合约代码           (not null)
	TClientID  clientID;				//客户代码          (not null)
	TMemberID  memberID;				//会员代码          (not null)
	TTraderID  traderID;				//交易员代码        (not null)
};

//现货延期交收交割申报撤单请求  
struct TDeferDeliveryAppOrderCancel
{
	TOrderNo  orderNo;				//报单号               (not null)
	TInstID  instID;				//合约代码              (not null)
	TClientID  clientID;				//客户代码             (not null)
	TMemberID  memberID;				//会员代码		(not null)
	TTraderID  traderID;				//交易员代码       (not null)
};

//现货延期交收中立仓申报撤单请求  
struct TMiddleAppOrderCancel
{
	TOrderNo  orderNo;				//报单号          (not null)
	TInstID  instID;				//合约代码         (not null)
	TClientID  clientID;				//客户代码        (not null)
	TMemberID  memberID;				//会员代码        (not null)
	TTraderID  traderID;				//交易员代码      (not null)
};

//现货T+N到期转让撤单请求  
struct TForwardEndorseOrderCancel
{
	TOrderNo  orderNo;				//报单号        (not null)
	TInstID  instID;				//合约代码       (not null)
	TClientID  clientID;				//客户代码      (not null)
	TMemberID  memberID;				//会员代码      (not null)
	TTraderID  traderID;				//交易员代码     (not null)
};

//现货合约保证金率  
struct TSpotInstMarginRate
{
	TInstID  instID;				//合约代码
	TMemberID  memberID;				//会员代码
	TAccountType  accountType;				//帐户类型
	TRate  marginRate;				//保证金率
	TRateType  rateType;				//保证金类型
};

//递延合约保证金率  
struct TDeferInstMarginRate
{
	TInstID  instID;				//合约代码
	TMemberID  memberID;				//会员代码
	TAccountType  accountType;				//帐户类型
	TRate  marginRate;				//保证金率
	TRateType  rateType;				//保证金类型
	TDirection direction;			//多空方向
};

//期货合约保证金率  
struct TFuturesInstMarginRate
{
	TInstID  instID;				//合约代码
	TMemberID  memberID;				//会员代码
	TAccountType  accountType;				//帐户类型
	TRate  marginRate;				//保证金率
	TRateType  rateType;				//保证金类型
};

//远期合约保证金率  
struct TForwardInstMarginRate
{
	TInstID  instID;				//合约代码
	TMemberID  memberID;				//会员代码
	TAccountType  accountType;				//帐户类型
	TRate  marginRate;				//保证金率
	TRateType  rateType;				//保证金类型
};

//应急交易密码  
struct TUrgentTradePassword
{
	TPassword  urgentPassword;				//应急交易密码
};

//操作员密码  
struct TUserPassword
{
	TTraderID  userID;				//操作员代码
	TPassword  password;				//密码
};

//现货合约  
struct TSpotInst
{
	TInstID  instID;				//合约代码
	TInstName  name;				//合约名称
	TMarketID  marketID;				//市场代码
	TVarietyType  varietyType;				//品种类别
	TVarietyID  varietyID;				//交割品种代码
	TInstUnit  unit;				//交易单位数量
	TPrice  tick;				//最小变动价位
	TVolume  maxHand;				//最大申报限量(单手)
	TVolume  minHand;				//最小申报限量
	TRate  upperLimit;				//涨停板率
	TRate  lowerLimit;				//跌停板率
	TOpenFlag  openFlag;				//活跃标志1活跃;2不活跃3只平 4只开
	TInstStateFlag  tradeState;				//合约交易状态
	TPrice  refPrice;				//参考价
	TRate  recvRate;				//卖方收款比例
};

//现货延期交收合约  
struct TDeferInst
{
	TInstID  instID;				//合约代码
	TInstName  name;				//合约名称
	TMarketID  marketID;				//市场代码
	TVarietyType  varietyType;				//品种类别
	TVarietyID  varietyID;				//交割品种代码
	TInstUnit  unit;				//交易单位数量
	TPrice  tick;				//最小变动价位
	TVolume  maxHand;				//最大申报限量(单手)
	TVolume  minHand;				//最小申报限量
	TRate  upperLimit;				//涨停板率
	TRate  lowerLimit;				//跌停板率
	TOpenFlag  openFlag;				//活跃标志1活跃;2不活跃3只平 4只开
	TInstStateFlag  tradeState;				//合约交易状态
	TPrice  refPrice;				//参考价
};

//期货合约  
struct TFuturesInst
{
	TInstID  instID;				//合约代码
	TInstName  name;				//合约名称
	TMarketID  marketID;				//市场代码
	TVarietyType  varietyType;				//品种类别
	TVarietyID  varietyID;				//交割品种代码
	TInstUnit  unit;				//交易单位数量
	TPrice  tick;				//最小变动价位
	TVolume  maxHand;				//最大申报限量(单手)
	TVolume  minHand;				//最小申报限量
	TRate  upperLimit;				//涨停板率
	TRate  lowerLimit;				//跌停板率
	TOpenFlag  openFlag;				//活跃标志1活跃;2不活跃3只平 4只开
	TInstStateFlag  tradeState;				//合约交易状态
	TPrice  refPrice;				//参考价
};

//现货T+N合约  
struct TForwardInst
{
	TInstID  instID;				//合约代码
	TInstName  name;				//合约名称
	TMarketID  marketID;				//市场代码
	TVarietyType  varietyType;				//品种类别
	TVolume  deliveryDay;				//合约到期日,交割间隔天数
	TVarietyID  varietyID;				//交割品种代码
	TInstUnit  unit;				//交易单位数量
	TPrice  tick;				//最小变动价位
	TVolume  maxHand;				//最大申报限量(单手)
	TVolume  minHand;				//最小申报限量(单手)
	TRate  upperLimit;				//涨停板率
	TRate  lowerLimit;				//跌停板率
	TOpenFlag  openFlag;				//活跃标志1活跃;2不活跃3只平 4只开
	TInstStateFlag  tradeState;				//合约交易状态
	TPrice  refPrice;				//参考价
	TDate  dueDate;				//到期日
};

//市场表  
struct TMarket
{
	TMarketID  marketID;				//市场代码
	TMarketName  name;				//全称
	TMarketType  type;				//类型
	TOkFlag  openFlag;				//活跃标志
	TMarketStateFlag  marketState;				//市场交易状态
};

//交易所表  
struct TExchange
{
	TExchangeID  exchangeID;				//交易所代码
	TExchangeStateFlag  state;				//运行状态
};

//现货T+N强行平仓请求  
struct TReqForwardForceMatch
{
	TClientID  buyerClientID;				//买客户代码   (not null)
	TMemberID  buyerMemberID;				//买会员代码    (not null)
	TClientID  sellClientID;				//卖客户代码    (not null)
	TMemberID  sellMemberID;				//卖会员代码    (not null)
	TInstID  instID;				//合约代码       (not null)
	TPrice  price;				//价格                  (not null)
	TVolume  volume;				//数量           (not null)
	TMatchNo  orignalMatchNo;				//原来成交编号     (not null)
	TTraderID  operatorID;				//操作员代码             (not null)
};

//做市商限额表  
struct TMarketMakerLimit
{
	TMemberID  memberID;				//会员代码
	TInstID  instID;				//合约代码
	TMarketID  marketID;				//市场代码
	TLimitType  limitType;				//限额类型
	TPrice  limit;				//上限
};

//当天现货分钟行情  
struct TMinsSpotQuotation
{
	TInstID  instID;				//合约代码
	TPrice  open;				//开盘价
	TPrice  high;				//最高价
	TPrice  low;				//最低价
	TPrice  close;				//收盘价
	TVolume  volume;				//成交量（双边）
	TDate  quoteDate;				//行情日期
	TDate  quoteTime;				//行情时间
};

//期货分钟行情  
struct TMinsFuturesQuotation
{
	TInstID  instID;				//合约代码
	TInstName  name;				//合约名称
	TPrice  open;				//开盘价
	TPrice  high;				//最高价
	TPrice  low;				//最低价
	TPrice  close;				//收盘价
	TVolume  volume;				//成交量
	TVolume  Posi;				//持仓量
	TDate  quoteDate;				//行情日期
	TTime  quoteTime;				//行情时间
};

//递延分钟行情  
struct TMinsDeferQuotation
{
	TInstID  instID;				//合约代码
	TPrice  open;				//开盘价
	TPrice  high;				//最高价
	TPrice  low;				//最低价
	TPrice  close;				//收盘价
	TVolume  volume;				//成交量
	TVolume  Posi;				//持仓量
	TDate  quoteDate;				//行情日期
	TTime  quoteTime;				//行情时间
};

//远期分钟行情  
struct TMinsForwardQuotation
{
	TInstID  instID;				//合约代码
	TPrice  open;				//开盘价
	TPrice  high;				//最高价
	TPrice  low;				//最低价
	TPrice  close;				//收盘价
	TVolume  volume;				//成交量
	TVolume  Posi;				//持仓量
	TDate  quoteDate;				//行情日期
	TTime  quoteTime;				//行情时间
};

//现货合约交易状态控制表  
struct TSpotInstStateControl
{
	TInstStateFlag  state;				//合约交易状态
	TTime  startTime;				//进入时间
	TInstID  instID;				//合约代码
};

//递延合约交易状态控制表  
struct TDeferInstStateControl
{
	TInstStateFlag  state;				//合约交易状态
	TTime  startTime;				//进入时间
	TInstID  instID;				//合约代码
};

//期货合约交易状态控制表  
struct TFuturesInstStateControl
{
	TInstStateFlag  state;				//合约交易状态
	TTime  startTime;				//进入时间
	TInstID  instID;				//合约代码
};

//远期合约交易状态控制表  
struct TForwardInstStateControl
{
	TInstStateFlag  state;				//合约交易状态
	TTime  startTime;				//进入时间
	TInstID  instID;				//合约代码
};

//会员递延合约持仓限额  
struct TMemberDeferPosiLimit
{
	TMemberID  memberID;				//会员代码
	TInstID  instID;				//合约代码
	TDirection  direction;				//多空方向
	TVolume  limit;				//上限
	TAccountType clientType;	//客户类型
};

//客户递延合约持仓限额  
struct TClientDeferPosiLimit
{
	TClientID  clientID;				//客户代码
	TMemberID  memberID;				//会员代码
	TInstID  instID;				//合约代码
	TDirection  direction;				//多空方向
	TVolume  limit;				//上限
	TCode	clientSort;			//客户类别
	TAccountType clientType;	//客户类型
};

//会员期货合约持仓限额  
struct TMemberFuturesPosiLimit
{
	TMemberID  memberID;				//会员代码
	TInstID  instID;				//合约代码
	TDirection  direction;				//多空方向
	TVolume  limit;				//上限
};

//客户期货合约持仓限额  
struct TClientFuturesPosiLimit
{
	TClientID  clientID;				//客户代码
	TMemberID  memberID;				//会员代码
	TInstID  instID;				//合约代码
	TDirection  direction;				//多空方向
	TVolume  limit;				//上限
};

//会员远期合约持仓限额  
struct TMemberForwardPosiLimit
{
	TMemberID  memberID;				//会员代码
	TInstID  instID;				//合约代码
	TDirection  direction;				//多空方向
	TVolume  limit;				//上限
};

//客户远期合约持仓限额  
struct TClientForwardPosiLimit
{
	TClientID  clientID;				//客户代码
	TMemberID  memberID;				//会员代码
	TInstID  instID;				//合约代码
	TDirection  direction;				//多空方向
	TVolume  limit;				//上限
};

//会员现货市场权限  
struct TMemberSpotMarketRight
{
	TMarketID  marketID;				//市场代码
	TMemberID  memberID;				//会员代码
	TTradeRight  tradeRight;				//交易权限描述
};

//会员递延市场权限  
struct TMemberDeferMarketRight
{
	TMarketID  marketID;				//市场代码
	TMemberID  memberID;				//会员代码
	TTradeRight  tradeRight;				//交易权限描述
};

//会员递延合约权限  
struct TMemberDeferInstRight
{
	TInstID  instID;				//合约代码
	TMemberID  memberID;				//会员代码
	TAccountType  accountType;				//帐户类型
	TTradeRight  tradeRight;				//交易权限描述
};

//会员期货市场权限  
struct TMemberFuturesMarketRight
{
	TMarketID  marketID;				//市场代码
	TMemberID  memberID;				//会员代码
	TTradeRight  tradeRight;				//交易权限描述
};

//会员期货合约权限  
struct TMemberFuturesInstRight
{
	TInstID  instID;				//合约代码
	TMemberID  memberID;				//会员代码
	TAccountType  accountType;				//帐户类型
	TTradeRight  tradeRight;				//交易权限描述
};

//会员远期市场权限  
struct TMemberForwardMarketRight
{
	TMarketID  marketID;				//市场代码
	TMemberID  memberID;				//会员代码
	TTradeRight  tradeRight;				//交易权限描述
};

//会员远期合约权限  
struct TMemberForwardInstRight
{
	TInstID  instID;				//合约代码
	TMemberID  memberID;				//会员代码
	TAccountType  accountType;				//帐户类型
	TTradeRight  tradeRight;				//交易权限描述
};

//市场交易状态控制表  
struct TMarketStateControl
{
	TMarketStateFlag  state;				//市场交易状态
	TTime  startTime;				//进入时间
	TMarketID  marketID;				//市场代码
};

//远期应急报单  
struct TUrgentForwardOrder
{
	TOrderNo  orderNo;				//报单号           
	TClientID  clientID;				//客户代码         (not null)
	TInstID  instID;				//合约代码          (not null)
	TMemberID  memberID;				//会员代码        (not null)
	TBSFlag  buyOrSell;				//买卖方向       (not null)
	TDate  applyDate;				//申报日期
	TTime  applyTime;				//申报时间
	TOffsetFlag  offsetFlag;				//开平仓标志   (not null)
	TPrice  price;				//价格                         (not null)
	TVolume  amount;				//数量                  (not null)
	TVolume  remainAmount;				//剩余数量
	TOrderStatus  status;				//状态
	TLocalNo  localOrderNo;				//本地报单号            (not null)
	TRate  margin;				//保证金率
	TRateType  marginType;				//保证金类型             (not null)
	TTraderID  traderID;				//交易员代码            (not null)
	TTime  cancelTime;				//撤消时间
	TTraderID  cancelID;				//撤消员代码
	TTraderID  checkID;				//复核员代码
	TCheckFlag  checkFlag;				//复核标志
	TMatchType  matchType;				//类型                   (not null)
	TOrderType  orderType;				//指令类型    (not null)
};

//期货应急报单  
struct TUrgentFuturesOrder
{
	TOrderNo  orderNo;				//报单号
	TClientID  clientID;				//客户代码
	TInstID  instID;				//合约代码
	TMemberID  memberID;				//会员代码
	TBSFlag  buyOrSell;				//买卖方向
	TDate  applyDate;				//申报日期
	TTime  applyTime;				//申报时间
	TOffsetFlag  offSetFlag;				//开平仓标志
	TPrice  price;				//价格
	TVolume  amount;				//数量
	TVolume  remainAmount;				//剩余数量
	TOrderStatus  status;				//状态
	TLocalNo  localOrderNo;				//本地报单号
	TRate  margin;				//保证金率
	TRateType  marginType;				//保证金类型
	TTraderID  traderID;				//交易员代码
	TTime  cancelTime;				//撤消时间
	TTraderID  cancelID;				//撤消员代码
	TTraderID  checkID;				//复核员代码
	TCheckFlag  checkFlag;				//复核标志
	TMatchType  matchType;				//类型
};

//递延应急报单
struct TUrgentDeferOrder
{
	TOrderNo  orderNo;				//报单号
	TBSFlag  buyOrSell;				//买卖方向
	TDate  applyDate;				//申报日期
	TTime  applyTime;				//申报时间
	TOffsetFlag  offSetFlag;				//开平仓标志
	TPrice  price;				//价格
	TVolume  amount;				//数量
	TVolume  remainAmount;				//剩余数量
	TOrderStatus  status;				//状态
	TLocalNo  localOrderNo;				//本地报单号
	TRate  margin;				//保证金率
	TRateType  marginType;				//保证金类型
	TClientID  clientID;				//客户代码
	TInstID  instID;				//合约代码
	TMemberID  memberID;				//会员代码
	TTraderID  traderID;				//交易员代码
	TTime  cancelTime;				//撤消时间
	TTraderID  cancelID;				//撤消员代码
	TTraderID  checkID;				//复核员代码
	TCheckFlag  checkFlag;				//复核标志
	TMatchType  matchType;				//类型
	TOrderType  orderType;				//指令类型    (not null)
};

//现货应急报单
struct TUrgentSpotOrder
{
	TOrderNo  orderNo;				//报单号
	TInstID  instID;				//合约代码
	TClientID  clientID;				//客户代码
	TMemberID  memberID;				//会员代码
	TBSFlag  buyOrSell;				//买卖方向
	TDate  applyDate;				//申报日期
	TTime  applyTime;				//申报时间
	TTraderID  traderID;				//交易员代码
	TPrice  price;				//价格
	TVolume  amount;				//数量
	TVolume  remainAmount;				//剩余数量
	TTime  cancelTime;				//撤消时间
	TTraderID  cancelID;				//撤消员代码
	TOrderStatus  Status;				//状态
	TLocalNo  localOrderNo;				//本地报单号
	TTraderID  checkID;				//复核员代码
	TCheckFlag  checkFlag;				//复核标志
	TSpotMatchType  matchType;				//类型
	TOrderType  orderType;				//指令类型    (not null)
};

//应急报单查询请求  
struct TReqQryUrgentOrder
{
	TMarketID  marketID;				//市场代码             (not null)
};

//现货应急报单撤单请求  
struct TUrgentSpotOrderCancel
{
	TOrderNo  orderNo;				//报单号            (not null)
	TInstID  instID;				//合约代码           (not null)
	TClientID  clientID;				//客户代码           (not null)
	TMemberID  memberID;				//会员代码            (not null)
	TTraderID  traderID;				//交易员代码          (not null)
};

//递延应急报单撤单请求  
struct TUrgentDeferOrderCancel
{
	TOrderNo  orderNo;				//报单号             (not null)
	TInstID  instID;				//合约代码             (not null)
	TClientID  clientID;				//客户代码            (not null)
	TMemberID  memberID;				//会员代码              (not null)
	TTraderID  traderID;				//交易员代码            (not null)
};

//期货应急报单撤单请求  
struct TUrgentFuturesOrderCancel
{
	TOrderNo  orderNo;				//报单号                 (not null)
	TInstID  instID;				//合约代码              (not null)
	TClientID  clientID;				//客户代码              (not null)
	TMemberID  memberID;				//会员代码              (not null)
	TTraderID  traderID;				//交易员代码            (not null)
};

//远期应急报单撤单请求  
struct TUrgentForwardOrderCancel
{
	TOrderNo  orderNo;				//报单号           (not null)
	TInstID  instID;				//合约代码          (not null)
	TClientID  clientID;				//客户代码		(not null)
	TMemberID  memberID;				//会员代码       (not null)
	TTraderID  traderID;				//交易员代码      (not null)
};

//会员超仓查询请求  
struct TReqQryMemberPosiOver
{
	TMemberID  memberID;				//会员代码           (not null)
	TMarketID  marketID;				//市场代码            (not null)
	TInstID  instID;				//合约代码            (not null)
	TAccountType accountType;       // 账户类型           (not null)
	TTraderID  userID;				//操作员代码           (not null)
};

//会员超仓查询响应  
struct TRspQryMemberPosiOver
{
	TMemberID  memberID;				//会员代码
	TMarketID  marketID;				//市场代码
	TClientID  clientID;				//客户代码
	TInstID  instID;				//合约代码
	TBSFlag  buyOrSell;				//买卖方向
	TVolume  amount;				//数量
};

//客户超仓查询请求  
struct TReqQryClientPosiOver
{
	TClientID  clientID;				//客户代码          (not null)
	TMarketID  marketID;				//市场代码          (not null)
	TInstID  instID;				//合约代码           (not null)
	TTraderID  userID;				//操作员代码          (not null)
};

//客户超仓查询响应  
struct TRspQryClientPosiOver
{
	TMemberID  memberID;				//会员代码
	TClientID  clientID;				//客户代码
	TMarketID  marketID;				//市场代码
	TInstID  instID;				//合约代码
	TBSFlag  buyOrSell;				//买卖方向
	TVolume  amount;				//数量
};

//资金不足查询请求  
struct TReqQryCapitalLack
{
	TMemberID  memberID;				//会员代码           (not null)
	TClientID  clientID;				//客户代码 add by chechao,2011.12.19
	TMarketID  marketID;				//市场代码           (not null)
	TInstID  instID;				//合约代码            (not null)
	TAccountType  accountType;				//帐户类型    (not null)
	TVolume  amount;				//数量              (not null)
	TBSFlag  buyOrSell;				//买卖方向            (not null)
	TTraderID  userID;				//操作员代码          (not null)
};

//资金不足查询响应  
struct TRspQryCapitalLack
{
	TMemberID  memberID;				//会员代码
	TClientID  clientID;				//客户代码
	TMarketID  marketID;				//市场代码
	TInstID  instID;				//合约代码
	TBSFlag  buyOrSell;				//买卖方向
	TVolume  amount;				//总持仓
	TVolume	 availAmount;			//可用持仓
};

//递延费率查询请求  
struct TReqQryDeferFeeRate
{
	TDate  effectDateBegin;				//起始日期
	TDate  effectDateEnd;				//截至日期
};

//国际行情信息  
struct TInterQuotation
{
	TAbstract  content;				//内容
	TTraderID  announcer;				//发布人
	TTime  announceTime;				//发布时间
	TDate  announceDate;				//发布日期
};

//交易所公告信息查询请求  
struct TReqQryBulletinBoard
{
	TMemberID  memberID;				//会员代码
	TDate  announceDate;				//发布日期
};

//强制交易员退出请求  
struct TReqForceTraderLogout
{
	TTraderID  traderID;				//交易员代码         (not null)
	TMemberID  memberID;				//会员代码           (not null)
	TTraderID  userID;				//操作员代码        (not null)
};

//行情分钟查询请求  
struct TReqQryMinsQuotation
{
	TInstID  instID;				//合约代码          (not null)
	TMarketID  marketID;				//市场代码         (not null)
	TTime  lastTime;				//上一次时间
};

//资金请求  
struct TReqCapital
{
	TMemberID  memberID;				//会员代码             
	TAccountType  accountType;				//帐户类型      
	TMoney  capital;				//资金
};

//资金流水  
struct TCapitalSeq
{
	TDate  i_accountDate;				//日期
	TMemberID  i_memberID;				//会员代码
	TAccountType  i_accountType;				//账户类型
	TBizSort  i_bizSort;				//业务类型
	TMoney  i_effectAmount;				//发生金额
};

//仓储变化明细  
struct TStorageWasteBook
{
	TDate  i_transDate;				//实际发生日期
	TTime  i_transTime;				//实际发生时间
	TClientID  i_clientID;				//客户代码
	TMemberID  i_memberID;				//会员代码
	TAccountType  i_accountType;				//账户类型
	TMatchNo  i_sheetNo;				//单据编号
	TTransType  i_transType;				//交易类型
	TVarietyID  i_varietyID;				//交割品种代码
	TWeight  i_stdStorage;				//发生标准重量
};

//状态模式  
struct TStateMode
{
	TMarketID  marketID;				//市场代码
	TInstID  instID;				//合约代码
};

//会员客户查询请求  
struct TReqQryClient
{
	TMemberID  memberID;				//会员代码         (not null)
	TClientID  clientID;				//客户代码
};

//递延交收行情  
struct TDeferDeliveryQuotation
{
	TInstID  instID;				//合约代码
	TVolume  bidLot;				//买量
	TVolume  askLot;				//卖量
	TVolume  midBidLot;				//中立仓买量
	TVolume  midAskLot;				//中立仓卖量
};

//强平成交单  
struct TReqForceMatch
{
	TClientID  clientID;				//客户代码
	TInstID  instID;				//合约代码
	TPrice  price;				//平仓价格
	TVolume  offset;				//平仓数量
};

//交割品种代码  
struct TVariety
{
	TVarietyID  varietyID;				//交割品种代码
	TName  name;				//交割品种全称
	TAbbr  abbr;				//简称
	TVarietyType  varietyType;				//品种类别
	TWeight  minPickup;				//最小提货数量
	TWeight  defaultStdWeight;		//默认标准重量 add by litian 20061018
	TWeight  pickupBase;				//提货步长
	TUnitID  weightUnit;				//重量单位
	TDestroyFlag  destroyFlag;				//注销标志
};

//中立仓保证金率  
struct TMiddleMarginRate
{
	TInstID  instID;				//合约代码
	TRate  marginRate;				//保证金率
};

//版本信息 
struct TVersion
{
	TVersionInfo versionInfo;		//版本号
};

#endif	
