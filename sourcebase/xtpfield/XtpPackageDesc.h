// XtpPackageDesc.h: 
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XTPPACKAGEDESC_H__EA501ADE_818C_4F9A_8738_AC9CCAF0B941__INCLUDED_)
#define AFX_XTPPACKAGEDESC_H__EA501ADE_818C_4F9A_8738_AC9CCAF0B941__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XtpData.h"
#include "HashMap.h"
#include "FieldSet.h"

//空操作
const DWORD TID_Nop=0x00009000;
//错误应答
const DWORD TID_RspError=0x00009001;
//用户登录请求
const DWORD TID_ReqUserLogin=0x00009002;
//用户登录应答
const DWORD TID_RspUserLogin=0x00009003;
//用户退出请求
const DWORD TID_ReqUserLogout=0x00009004;
//用户退出应答
const DWORD TID_RspUserLogout=0x00009005;
//报单录入请求
const DWORD TID_ReqOrderInsert=0x00009006;
//报单录入应答
const DWORD TID_RspOrderInsert=0x00009007;
//报单操作请求
const DWORD TID_ReqOrderAction=0x00009008;
//报单操作应答
const DWORD TID_RspOrderAction=0x00009009;
//用户密码修改请求
const DWORD TID_ReqUserPasswordUpdate=0x0000900A;
//用户密码修改应答
const DWORD TID_RspUserPasswordUpdate=0x0000900B;
//强制用户退出请求
const DWORD TID_ReqForceUserExit=0x0000900C;
//强制用户退出应答
const DWORD TID_RspForceUserExit=0x0000900D;
//用户会话删除请求
const DWORD TID_ReqForceUserLogout=0x0000900E;
//用户会话删除应答
const DWORD TID_RspForceUserLogout=0x0000900F;
//请求导出内存数据库
const DWORD TID_ReqDumpMemDb=0x00009010;
//更新系统状态
const DWORD TID_UpdateSystemStatus=0x00009011;
//投资者资金帐户出入金请求
const DWORD TID_ReqAccountDeposit=0x00009012;
//投资者资金帐户出入金应答
const DWORD TID_RspAccountDeposit=0x00009013;
//投资者资金查询请求
const DWORD TID_ReqQryInvestorAccount=0x00009020;
//投资者资金查询应答
const DWORD TID_RspQryInvestorAccount=0x00009021;
//报单查询请求
const DWORD TID_ReqQryOrder=0x00009022;
//报单查询应答
const DWORD TID_RspQryOrder=0x00009023;
//成交单查询请求
const DWORD TID_ReqQryTrade=0x00009024;
//成交单查询应答
const DWORD TID_RspQryTrade=0x00009025;
//投资者查询请求
const DWORD TID_ReqQryInvestor=0x00009026;
//投资者查询应答
const DWORD TID_RspQryInvestor=0x00009027;
//报单查询请求
const DWORD TID_ReqQryOrderInsertFailed=0x0000902A;
//合约查询请求
const DWORD TID_ReqQryInstrument=0x0000902B;
//合约查询应答
const DWORD TID_RspQryInstrument=0x0000902C;
//用户查询请求
const DWORD TID_ReqQryUser=0x0000902D;
//用户查询应答
const DWORD TID_RspQryUser=0x0000902E;
//交易所查询请求
const DWORD TID_ReqQryExchange=0x00009031;
//交易所查询应答
const DWORD TID_RspQryExchange=0x00009032;
//可用投资者账户查询请求
const DWORD TID_ReqQryUserInvestor=0x00009033;
//可用投资者账户查询应答
const DWORD TID_RspQryUserInvestor=0x00009034;
//投资者持仓查询请求
const DWORD TID_ReqQryInvestorPosition=0x00009035;
//投资者持仓查询应答
const DWORD TID_RspQryInvestorPosition=0x00009036;
//普通行情查询请求
const DWORD TID_ReqQryMarketData=0x0000903D;
//普通行情查询应答
const DWORD TID_RspQryMarketData=0x0000903E;
//投资者手续费率查询请求
const DWORD TID_ReqQryInvestorFee=0x0000903F;
//投资者手续费率查询应答
const DWORD TID_RspQryInvestorFee=0x00009040;
//投资者保证金率查询请求
const DWORD TID_ReqQryInvestorMargin=0x00009041;
//投资者保证金率查询应答
const DWORD TID_RspQryInvestorMargin=0x00009042;
//行情查询请求
const DWORD TID_ReqQryDepthMarketData=0x00009045;
//行情查询应答
const DWORD TID_RspQryDepthMarketData=0x00009046;
//金交所递延费率查询请求
const DWORD TID_ReqQrySGEDeferRate=0x00009049;
//金交所递延费率查询应答
const DWORD TID_RspQrySGEDeferRate=0x0000904A;
//持仓明细查询请求
const DWORD TID_ReqQryInvestorPositionDetail=0x0000904B;
//持仓明细查询应答
const DWORD TID_RspQryInvestorPositionDetail=0x0000904C;
//持仓明细表
const DWORD TID_ExInvestorPositionDetail=0x0000904D;
//投资者期权手续费率查询请求
const DWORD TID_ReqQryInvestorOptionFee=0x00009204;
//投资者期权手续费率查询应答
const DWORD TID_RspQryInvestorOptionFee=0x00009205;
//数据同步开始
const DWORD TID_DataSyncStart=0x00009050;
//数据同步结束
const DWORD TID_DataSyncEnd=0x00009051;
//交易所
const DWORD TID_InitExchange=0x00009052;
//席位
const DWORD TID_InitSeat=0x00009054;
//用户
const DWORD TID_InitUser=0x00009055;
//投资者
const DWORD TID_InitInvestor=0x00009056;
//交易编码
const DWORD TID_InitClientTradingID=0x00009057;
//用户投资者关系
const DWORD TID_InitUserInvestor=0x00009058;
//用户交易权限
const DWORD TID_InitUserTradingRight=0x00009059;
//投资者资金账户
const DWORD TID_InitInvestorAccount=0x0000905A;
//合约
const DWORD TID_InitInstrument=0x0000905B;
//投资者保证金率
const DWORD TID_InitInvestorMargin=0x0000905D;
//投资者手续费
const DWORD TID_InitInvestorFee=0x0000905E;
//投资者持仓
const DWORD TID_InitInvestorPosition=0x0000905F;
//客户资金帐户出入金
const DWORD TID_DbInvestorAccountDeposit=0x00009061;
//增加交易用户
const DWORD TID_DbInsUser=0x00009062;
//修改交易用户
const DWORD TID_DbUpdUser=0x00009063;
//系统状态
const DWORD TID_InitSystemStatus=0x00009064;
//合约和合约组关系
const DWORD TID_InitInstrumentGroup=0x00009065;
//交易编码组合保证金类型
const DWORD TID_InitClientMarginCombType=0x00009066;
//金交所递延费率信息表
const DWORD TID_InitSGEDeferRate=0x00009102;
//客户资金帐户出入金
const DWORD TID_DbClientTradingID=0x00009100;
//组合合约明细应答
const DWORD TID_InitCmbInstrumentDetail=0x00009098;
//投资者交易权限
const DWORD TID_InitInvestorTradingRight=0x00009101;
//修改投资者权限
const DWORD TID_DbUpdInvestorTradingRight=0x00009103;
//增加投资者权限
const DWORD TID_DbInsInvestorTradingRight=0x00009104;
//删除投资者权限
const DWORD TID_DbDelInvestorTradingRight=0x00009105;
//交易员IP
const DWORD TID_DbUpdUserIP=0x00009106;
//交易员IP
const DWORD TID_DbInsUserIP=0x00009107;
//交易员IP
const DWORD TID_DbDelUserIP=0x00009108;
//交易员IP
const DWORD TID_InitUserIP=0x00009109;
//投资者期权手续费
const DWORD TID_InitInvestorOptionFee=0x00009112;
//QDP系统信息表
const DWORD TID_InitSystemInfo=0x00009113;
//时间同步
const DWORD TID_NtfTimeSync=0x00009070;
//通讯阶段切换通知
const DWORD TID_NtfCommPhaseChange=0x00009071;
//报单通知
const DWORD TID_NtfOrder=0x00009072;
//成交通知
const DWORD TID_NtfTrade=0x00009073;
//合约交易状态改变通知
const DWORD TID_NtfInstrumentStatusUpdate=0x00009074;
//会话删除通知
const DWORD TID_NtfDelUserSession=0x00009075;
//普通行情通知
const DWORD TID_NtfMarketData=0x00009076;
//通知生命周期号
const DWORD TID_NtfLifeCycle=0x00009079;
//报单录入错误通知
const DWORD TID_NtfErrorOrderInsert=0x0000907A;
//报单操作错误通知
const DWORD TID_NtfErrorOrderAction=0x0000907B;
//内存表变化通知
const DWORD TID_NtfMemtableChange=0x0000907E;
//通知报盘机查询合约请求
const DWORD TID_ReqQueryExInstrument=0x00009081;
//报盘机查询合约应答
const DWORD TID_RspQueryExInstrument=0x00009082;
//报盘机查询交易日应答
const DWORD TID_RspQueryExTradingDay=0x00009083;
//报盘机查询客户持仓应答
const DWORD TID_RspQueryExInvestorPosition=0x00009084;
//报盘机查询行情应答
const DWORD TID_RspQueryExMarketData=0x00009085;
//解冻InnerLink未报入交易的报单
const DWORD TID_ReqRollbakPreOrder=0x0000909D;
//出入金回报通知
const DWORD TID_NtfInvestorAccountDeposit=0x00009086;
//报盘机查询结束
const DWORD TID_QueryBaseFinish=0x00009087;
//报盘机查询资金应答
const DWORD TID_RspQueryExCapitalData=0x00009088;
//报盘机查询组合合约明细应答
const DWORD TID_RspQueryExCmbInstrumentDetail=0x00009090;
//金交所递延费率通知
const DWORD TID_NtfSGEDeferRate=0x0000909E;
//成功登陆通知
const DWORD TID_InterLoginInfo=0x00009095;
//QDP警告消息通知
const DWORD TID_NtfMessageNotify=0x00009096;
//内部登录请求
const DWORD TID_InnerLogin=0x00009415;
//内部分价表查询应答
const DWORD TID_ExQryMBLMarketData=0x00009416;
//分价表查询请求
const DWORD TID_ReqQryMBLMarketData=0x00009417;
//分价表查询应答
const DWORD TID_RspQryMBLMarketData=0x00009418;
//内存表变化通知
const DWORD TID_NtfPositionProfit=0x00009419;

///获取报单的名称
///@param	tid	报单编号
///@return	报单名称
const char *getPackageName(DWORD tid);

#ifndef FIELD_USE_DEFINE
#define FIELD_USE_DEFINE

#define UNLIMITED_FIELD_OCCUR 1000
#define MAX_PACKAGE_NAME_LEN		100
#define MAX_COMMENT_LEN		100
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
	char packageName[MAX_PACKAGE_NAME_LEN];
	char comment[MAX_COMMENT_LEN];
}	TPackageDefine;

#endif

extern TPackageDefine XTPPackageDefines[];

class CXTPPackageDefineMap: public CHashMap<DWORD, TPackageDefine *, HashInt>
{
public:
	CXTPPackageDefineMap(TPackageDefine *pXTPPackageDefines, int nDefineCount)
	{
		for(int i=0; i<nDefineCount; i++)
		{
			Insert(pXTPPackageDefines->tid, pXTPPackageDefines);
			pXTPPackageDefines++;
		}
	}
};

extern CXTPPackageDefineMap g_XTPPackageDefineMap;
void XTP_DEBUG_BODY(DWORD tid, CFieldSet *pPackage, CLogger *pLogger);
#endif
