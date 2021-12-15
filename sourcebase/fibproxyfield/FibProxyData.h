// FibProxyData.h: 
//
//////////////////////////////////////////////////////////////////////

#if !defined(_FIBPROXYDATA_H)
#define _FIBPROXYDATA_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FieldDescribe.h"

#define FPP_FTD_VERSION 200

//错误应答
const DWORD FPP_TID_RspError=0x00000001;
//用户登录请求
const DWORD FPP_TID_ReqUserLogin=0x00001001;
//用户登录应答
const DWORD FPP_TID_RspUserLogin=0x00001002;

const DWORD FPP_TID_ReqSubscribe = 0x00001003;

const DWORD FPP_TID_RspSubscribe = 0x00001004;

const DWORD FPP_TID_ReqQryFlow = 0x00001005;

const DWORD FPP_TID_RspQryFlow = 0x00001006;

const DWORD FPP_TID_TRANSFER = 0x0000A001;

//灾备切换控制新增
const DWORD FPP_TID_ReqSwitch = 0x0000A010;
const DWORD FPP_TID_RspSwitch = 0x0000A011;

DefineUFType(UFIntType,FPPErrorIDType)
DefineUFType(UFWordType,FPPSequenceSeriesType)
DefineUFType(UFIntType,FPPSequenceNoType)
DefineStringType(80,FPPErrorMsgType)
DefineStringType(15,FPPUserIDType)
DefineStringType(40,FPPPasswordType)
DefineStringType(8,FPPDateType)
DefineStringType(8,FPPTimeType)
DefineStringType(40,FPPProductInfoType)

///信息分发
class CFPPDisseminationField
{
public:
	///序列系列号
	CFPPSequenceSeriesType	SequenceSeries;
	///序列号
	CFPPSequenceNoType	SequenceNo;
	TYPE_DESCRIPTOR((
		TYPE_DESC(SequenceSeries)
		,
		TYPE_DESC(SequenceNo)
	));
};
const DWORD FPP_Dissemination=0x0001;

///响应信息
class CFPPRspInfoField
{
public:
	///错误代码
	CFPPErrorIDType	ErrorID;
	///错误信息
	CFPPErrorMsgType	ErrorMsg;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ErrorID)
		,
		TYPE_DESC(ErrorMsg)
	));
};
const DWORD FPP_FID_RspInfo=0x0003;

///用户登录请求
class CFPPReqUserLoginField
{
public:
	///交易日
	CFPPDateType	TradingDay;
	///交易用户代码
	CFPPUserIDType	UserID;
	///密码
	CFPPPasswordType	Password;
	///用户端产品信息
	CFPPProductInfoType	UserProductInfo;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(UserID)
		,
		TYPE_DESC(Password)
		,
		TYPE_DESC(UserProductInfo)
	));
};
const DWORD FPP_FID_ReqUserLogin=0x000A;

///用户登录应答
class CFPPRspUserLoginField
{
public:
	///交易日
	CFPPDateType	TradingDay;
	///登录成功时间
	CFPPTimeType	LoginTime;
	///交易用户代码
	CFPPUserIDType	UserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(LoginTime)
		,
		TYPE_DESC(UserID)
	));
};
const DWORD FPP_FID_RspUserLogin=0x000B;

#endif