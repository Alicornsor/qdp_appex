// FtdPackageDesc.h: 
//
//////////////////////////////////////////////////////////////////////

#if !defined(_FTDPACKAGEDESC_H)
#define _FTDPACKAGEDESC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FtdData.h"
#include "FieldSet.h"


#define FTD_VERSION 1

const WORD TSS_DIALOG = 1;		//对话流
const WORD TSS_PRIVATE = 2;		//客户私有流
const WORD TSS_PUBLIC = 3;		//公共流
const WORD TSS_QUERY = 4;		//查询
const WORD TSS_USER = 5;		//用户私有流


//错误应答
const DWORD FTD_TID_RspError=0x00005000;
//用户登录请求
const DWORD FTD_TID_ReqUserLogin=0x00005001;
//用户登录应答
const DWORD FTD_TID_RspUserLogin=0x00005002;
//用户退出请求
const DWORD FTD_TID_ReqUserLogout=0x00005003;
//用户退出应答
const DWORD FTD_TID_RspUserLogout=0x00005004;
//用户密码修改请求
const DWORD FTD_TID_ReqUserPasswordUpdate=0x00005005;
//用户密码修改应答
const DWORD FTD_TID_RspUserPasswordUpdate=0x00005006;
//强制用户退出请求
const DWORD FTD_TID_ReqForceUserExit=0x00005007;
//强制用户退出应答
const DWORD FTD_TID_RspForceUserExit=0x00005008;
//用户会话删除请求
const DWORD FTD_TID_ReqForceUserLogout=0x00005009;
//用户会话删除应答
const DWORD FTD_TID_RspForceUserLogout=0x0000500A;
//请求导出内存数据库
const DWORD FTD_TID_ReqDumpMemDb=0x0000501B;
//报单录入请求
const DWORD FTD_TID_ReqOrderInsert=0x00005020;
//报单录入应答
const DWORD FTD_TID_RspOrderInsert=0x00005021;
//报单操作请求
const DWORD FTD_TID_ReqOrderAction=0x00005022;
//报单操作应答
const DWORD FTD_TID_RspOrderAction=0x00005023;
//投资者资金帐户出入金请求
const DWORD FTD_TID_ReqAccountDeposit=0x00005024;
//投资者资金帐户出入金应答
const DWORD FTD_TID_RspAccountDeposit=0x00005025;
//数据流回退通知
const DWORD FTD_TID_RtnFlowMessageCancel=0x00005030;
//内部分发信息通知
const DWORD FTD_TID_IntlRtnDissemination=0x00005031;
//成交回报
const DWORD FTD_TID_RtnTrade=0x00005032;
//报单回报
const DWORD FTD_TID_RtnOrder=0x00005033;
//报单录入错误回报
const DWORD FTD_TID_ErrRtnOrderInsert=0x00005034;
//报单操作错误回报
const DWORD FTD_TID_ErrRtnOrderAction=0x00005035;
//合约交易状态通知
const DWORD FTD_TID_RtnInstrumentStatus=0x00005036;
//账户出入金回报
const DWORD FTD_TID_RtnInvestorAccountDeposit=0x00005037;
//QDP警告消息通知
const DWORD FTD_TID_RtnMessageNotify=0x00005038;
//金交所递延费率通知
const DWORD FTD_TID_RtnSGEDeferRate=0x0000503F;
//郑州合约状态
const DWORD FTD_TID_RtnQmdInstrumentStatu=0x00005040;
//报单查询请求
const DWORD FTD_TID_ReqQryOrder=0x00005041;
//报单查询应答
const DWORD FTD_TID_RspQryOrder=0x00005042;
//成交单查询请求
const DWORD FTD_TID_ReqQryTrade=0x00005043;
//成交单查询应答
const DWORD FTD_TID_RspQryTrade=0x00005044;
//可用投资者账户查询请求
const DWORD FTD_TID_ReqQryUserInvestor=0x00005045;
//可用投资者账户查询应答
const DWORD FTD_TID_RspQryUserInvestor=0x00005046;
//交易编码查询请求
const DWORD FTD_TID_ReqQryTradingCode=0x00005047;
//交易编码查询应答
const DWORD FTD_TID_RspQryTradingCode=0x00005048;
//投资者资金账户查询请求
const DWORD FTD_TID_ReqQryInvestorAccount=0x00005049;
//投资者资金账户查询应答
const DWORD FTD_TID_RspQryInvestorAccount=0x0000504A;
//合约查询请求
const DWORD FTD_TID_ReqQryInstrument=0x0000504B;
//合约查询应答
const DWORD FTD_TID_RspQryInstrument=0x0000504C;
//交易所查询请求
const DWORD FTD_TID_ReqQryExchange=0x0000504D;
//交易所查询应答
const DWORD FTD_TID_RspQryExchange=0x0000504E;
//投资者持仓查询请求
const DWORD FTD_TID_ReqQryInvestorPosition=0x0000504F;
//投资者持仓查询应答
const DWORD FTD_TID_RspQryInvestorPosition=0x00005050;
//订阅主题请求
const DWORD FTD_TID_ReqSubscribeTopic=0x00005051;
//订阅主题应答
const DWORD FTD_TID_RspSubscribeTopic=0x00005052;
//主题查询请求
const DWORD FTD_TID_ReqQryTopic=0x00005055;
//主题查询应答
const DWORD FTD_TID_RspQryTopic=0x00005056;
//用户查询请求
const DWORD FTD_TID_ReqQryUser=0x00005057;
//用户查询应答
const DWORD FTD_TID_RspQryUser=0x00005058;
//投资者手续费率查询请求
const DWORD FTD_TID_ReqQryInvestorFee=0x00005059;
//投资者手续费率查询应答
const DWORD FTD_TID_RspQryInvestorFee=0x00005060;
//投资者保证金率查询请求
const DWORD FTD_TID_ReqQryInvestorMargin=0x00005061;
//投资者保证金率查询应答
const DWORD FTD_TID_RspQryInvestorMargin=0x00005062;
//金交所递延费率查询请求
const DWORD FTD_TID_ReqQrySGEDeferRate=0x00005088;
//金交所递延费率查询应答
const DWORD FTD_TID_RspQrySGEDeferRate=0x00005089;
//持仓明细查询请求
const DWORD FTD_TID_ReqQryInvestorPositionDetail=0x00005098;
//持仓明细查询应答
const DWORD FTD_TID_RspQryInvestorPositionDetail=0x00005099;
//投资者期权手续费率查询请求
const DWORD FTD_TID_ReqQryInvestorOptionFee=0x00005102;
//投资者期权手续费率查询应答
const DWORD FTD_TID_RspQryInvestorOptionFee=0x00005103;
//内部深度行情通知
const DWORD FTD_TID_IntlRtnDepthMarketData=0x00005070;
//Topic查询应答
const DWORD FTD_TID_IntlTopicSearch=0x00005080;
//Topic查询
const DWORD FTD_TID_ReqTopicSearch=0x00005081;
//深度行情通知
const DWORD FTD_TID_RtnDepthMarketData=0x00005071;
//深度行情通知
const DWORD FTD_TID_RtnMultiDepthMarketData=0x00005072;
//订阅合约的相关信息
const DWORD FTD_TID_ReqSubMarketData=0x00005073;
//订阅合约的相关信息
const DWORD FTD_TID_RspSubMarketData=0x00005074;
//退订合约的相关信息
const DWORD FTD_TID_ReqUnSubMarketData=0x00005075;
//退订合约的相关信息
const DWORD FTD_TID_RspUnSubMarketData=0x00005076;
//实时行情查询请求
const DWORD FTD_TID_ReqQryMarketData=0x00005078;
//实时行情查询应答
const DWORD FTD_TID_RspQryMarketData=0x00005079;
//行情查询请求
const DWORD FTD_TID_ReqQryDepthMarketData=0x00005082;
//行情查询应答
const DWORD FTD_TID_RspQryDepthMarketData=0x00005083;
//分价表查询请求
const DWORD FTD_TID_ReqQryMBLMarketData=0x00005084;
//分价表查询应答
const DWORD FTD_TID_RspQryMBLMarketData=0x00005085;

#ifndef FIELD_USE_DEFINE
#define FIELD_USE_DEFINE

#define UNLIMITED_FIELD_OCCUR 1000

typedef struct
{
	DWORD fid;
	CFieldDescribe *pFieldDescribe;
	int minOccur;
	int maxOccur;
}	TFieldUse;

typedef struct
{
	DWORD tid;
	int fieldUseCount;
	TFieldUse *fieldUse;
}	TPackageDefine;

#endif

extern TPackageDefine FTDPackageDefines[];

void FTDC_DEBUG_BODY(DWORD tid, CFieldSet *pPackage, CLogger *pLogger);

#endif
