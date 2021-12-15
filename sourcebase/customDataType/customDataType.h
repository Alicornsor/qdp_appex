/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file customDataType.h
///@brief定义了交易所内部数据的底层支持类
///@history 
///20050324	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CUSTOMDATATYPE_H
#define CUSTOMDATATYPE_H

#include "UFDataType.h"

/////////////////////////////////////////////////////////////////////////
///CFloatType是一个最小变动价位类
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<22,8> CPriceTickType;
typedef const CUFFloatType<22,8> CReadOnlyPriceTickType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType是一个价格类
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<22,8> CPriceType;
typedef const CUFFloatType<22,8> CReadOnlyPriceType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType是一个比率类
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<22,8> CRatioType;
typedef const CUFFloatType<22,8> CReadOnlyRatioType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType是一个资金类
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<19,3> CMoneyType;
typedef const CUFFloatType<19,3> CReadOnlyMoneyType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType是一个大额数量类
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<19,3> CLargeVolumeType;
typedef const CUFFloatType<19,3> CReadOnlyLargeVolumeType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType是一个市盈率类
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<8,3> CEarningRatioType;
typedef const CUFFloatType<8,3> CReadOnlyEarningRatioType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType是一个汇率中间价类
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<22,8> CExRatePriceType;
typedef const CUFFloatType<22,8> CReadOnlyExRatePriceType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType是一个费用类
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<19,3> CFeeType;
typedef const CUFFloatType<19,3> CReadOnlyFeeType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType是一个库存类
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<19,3> CInventoryType;
typedef const CUFFloatType<19,3> CReadOnlyInventoryType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CNumberType;
typedef CReadOnlyUFIntType CReadOnlyNumberType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个序列号类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CSequenceNoType;
typedef CReadOnlyUFIntType CReadOnlySequenceNoType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个最后修改毫秒类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CMillisecType;
typedef CReadOnlyUFIntType CReadOnlyMillisecType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个按时间排队的序号类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CTimeSortIDType;
typedef CReadOnlyUFIntType CReadOnlyTimeSortIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个数量类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CVolumeType;
typedef CReadOnlyUFIntType CReadOnlyVolumeType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个合约乘数类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CUnderlyingMultipleType;
typedef CReadOnlyUFIntType CReadOnlyUnderlyingMultipleType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个数量乘数类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CVolumeMultipleType;
typedef CReadOnlyUFIntType CReadOnlyVolumeMultipleType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个通讯量类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CCommFluxType;
typedef CReadOnlyUFIntType CReadOnlyCommFluxType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个通讯时段号类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CCommPhaseNoType;
typedef CReadOnlyUFIntType CReadOnlyCommPhaseNoType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个序列系列号类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CSequenceSeriesType;
typedef CReadOnlyUFIntType CReadOnlySequenceSeriesType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个会话编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CSessionIDType;
typedef CReadOnlyUFIntType CReadOnlySessionIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个错误代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CErrorIDType;
typedef CReadOnlyUFIntType CReadOnlyErrorIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个数据中心代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CDataCenterIDType;
typedef CReadOnlyUFIntType CReadOnlyDataCenterIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个前置编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CFrontIDType;
typedef CReadOnlyUFIntType CReadOnlyFrontIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个报单编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CRequestIDType;
typedef CReadOnlyUFIntType CReadOnlyRequestIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个主题代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CTopicIDType;
typedef CReadOnlyUFIntType CReadOnlyTopicIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个Dbmt主题号类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CDbmtTopicIDType;
typedef CReadOnlyUFIntType CReadOnlyDbmtTopicIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个Dbmt序列号类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CDbmtSequenceIDType;
typedef CReadOnlyUFIntType CReadOnlyDbmtSequenceIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个DB命令序号类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CCommandNoType;
typedef CReadOnlyUFIntType CReadOnlyCommandNoType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个结算编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CSettlementIDType;
typedef CReadOnlyUFIntType CReadOnlySettlementIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个累加次数类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CTotalNumsType;
typedef CReadOnlyUFIntType CReadOnlyTotalNumsType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个偏差时间类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CDiffSndType;
typedef CReadOnlyUFIntType CReadOnlyDiffSndType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个交易ID类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CTIDType;
typedef CReadOnlyUFIntType CReadOnlyTIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType是一个时间戳类
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CILocalTimeType;
typedef CReadOnlyUFIntType CReadOnlyILocalTimeType;
	
/////////////////////////////////////////////////////////////////////////
///CLongType是一个本地时间类
/////////////////////////////////////////////////////////////////////////
typedef CUFLongType CLongTimeType;
typedef CReadOnlyUFLongType CReadOnlyLongTimeType;

/////////////////////////////////////////////////////////////////////////
///CRangeIntType是一个月份类
/////////////////////////////////////////////////////////////////////////
typedef CUFRangeIntType<1,12> CMonthType;
typedef const CUFRangeIntType<1,12> CReadOnlyMonthType;
	
/////////////////////////////////////////////////////////////////////////
///CRangeIntType是一个布尔型类
/////////////////////////////////////////////////////////////////////////
typedef CUFRangeIntType<0,1> CBoolType;
typedef const CUFRangeIntType<0,1> CReadOnlyBoolType;
	
/////////////////////////////////////////////////////////////////////////
///CRangeIntType是一个年类
/////////////////////////////////////////////////////////////////////////
typedef CUFRangeIntType<1900,2100> CYearType;
typedef const CUFRangeIntType<1900,2100> CReadOnlyYearType;
	
/////////////////////////////////////////////////////////////////////////
///CRangeIntType是一个日期类
/////////////////////////////////////////////////////////////////////////
typedef CUFRangeIntType<1,31> CDayType;
typedef const CUFRangeIntType<1,31> CReadOnlyDayType;
	
/////////////////////////////////////////////////////////////////////////
///CCharType是一个成交价来源类
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CPriceSourceType;
typedef CReadOnlyUFCharType CReadOnlyPriceSourceType;

/////////////////////////////////////////////////////////////////////////
///CCharType是一个优先权类
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CPriorityType;
typedef CReadOnlyUFCharType CReadOnlyPriorityType;

/////////////////////////////////////////////////////////////////////////
///CCharType是一个客户性别类
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CClientGendreType;
typedef CReadOnlyUFCharType CReadOnlyClientGendreType;

/////////////////////////////////////////////////////////////////////////
///CCharType是一个客户状态类
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CClientStatusType;
typedef CReadOnlyUFCharType CReadOnlyClientStatusType;

/////////////////////////////////////////////////////////////////////////
///CCharType是一个会员状态类
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CParticipantStatusType;
typedef CReadOnlyUFCharType CReadOnlyParticipantStatusType;

/////////////////////////////////////////////////////////////////////////
///CCharType是一个交易角色类
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CTradingRoleType;
typedef CReadOnlyUFCharType CReadOnlyTradingRoleType;

/////////////////////////////////////////////////////////////////////////
///CCharType是一个取值方式类
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CValueModeType;
typedef CReadOnlyUFCharType CReadOnlyValueModeType;

/////////////////////////////////////////////////////////////////////////
///CCharType是一个参与者类型类
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CParticipantTypeType;
typedef CReadOnlyUFCharType CReadOnlyParticipantTypeType;

/////////////////////////////////////////////////////////////////////////
///CCharType是一个报单类型类
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType COrderTypeType;
typedef CReadOnlyUFCharType CReadOnlyOrderTypeType;

/////////////////////////////////////////////////////////////////////////
///CCharType是一个自动挂起标志类
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CIsAutoSuspendType;
typedef CReadOnlyUFCharType CReadOnlyIsAutoSuspendType;

/////////////////////////////////////////////////////////////////////////
///CCharType是一个合约生命周期状态类
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CInstLifePhaseType;
typedef CReadOnlyUFCharType CReadOnlyInstLifePhaseType;

/////////////////////////////////////////////////////////////////////////
///CCharType是一个强平标志类
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CForceCloseFlagType;
typedef CReadOnlyUFCharType CReadOnlyForceCloseFlagType;

/////////////////////////////////////////////////////////////////////////
///CCharType是一个品种状态类
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CProductStatusType;
typedef CReadOnlyUFCharType CReadOnlyProductStatusType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个最后修改交易用户代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<15> CActiveUserIDType;
typedef const CUFStringType<15> CReadOnlyActiveUserIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个结算会员编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<10> CClearingPartIDType;
typedef const CUFStringType<10> CReadOnlyClearingPartIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个本地报单编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<18> CCombOrderLocalIDType;
typedef const CUFStringType<18> CReadOnlyCombOrderLocalIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个组合系统报单编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<18> CComOrderSysIDType;
typedef const CUFStringType<18> CReadOnlyComOrderSysIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个内存表名类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<60> CMemTableNameType;
typedef const CUFStringType<60> CReadOnlyMemTableNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个报单编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<30> COrderSysIDType;
typedef const CUFStringType<30> CReadOnlyOrderSysIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个成交编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CTradeIDType;
typedef const CUFStringType<20> CReadOnlyTradeIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个用户代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<15> CUserIDType;
typedef const CUFStringType<15> CReadOnlyUserIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个用户代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<15> CTraderIDType;
typedef const CUFStringType<15> CReadOnlyTraderIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个用户代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<15> CUserType;
typedef const CUFStringType<15> CReadOnlyUserType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个交易阶段编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<22> CTradingSegementNoType;
typedef const CUFStringType<22> CReadOnlyTradingSegementNoType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个交易阶段名称类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CTradingSegementNameType;
typedef const CUFStringType<20> CReadOnlyTradingSegementNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个会员名称类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<50> CParticipantNameType;
typedef const CUFStringType<50> CReadOnlyParticipantNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个会员编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<10> CParticipantIDType;
typedef const CUFStringType<10> CReadOnlyParticipantIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个会员简称类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CParticipantAbbrType;
typedef const CUFStringType<20> CReadOnlyParticipantAbbrType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个市场名称类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CMarketNameType;
typedef const CUFStringType<20> CReadOnlyMarketNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个市场代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<10> CMarketIDType;
typedef const CUFStringType<10> CReadOnlyMarketIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个IP地址类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CIPAddressType;
typedef const CUFStringType<20> CReadOnlyIPAddressType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个前置机的连接方式类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<512> CFrontAddrType;
typedef const CUFStringType<512> CReadOnlyFrontAddrType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个Mac地址类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CMacAddressType;
typedef const CUFStringType<20> CReadOnlyMacAddressType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个合约名称类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CInstrumentNameType;
typedef const CUFStringType<20> CReadOnlyInstrumentNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个营业部代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<6> CBranchIDType;
typedef const CUFStringType<6> CReadOnlyBranchIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个合约编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<30> CInstrumentIDType;
typedef const CUFStringType<30> CReadOnlyInstrumentIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个合约在交易所的代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<30> CExchangeInstIDType;
typedef const CUFStringType<30> CReadOnlyExchangeInstIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个证件号码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<50> CIdentifiedCardNoType;
typedef const CUFStringType<50> CReadOnlyIdentifiedCardNoType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个证件类型类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<15> CIdentifiedCardTypeType;
typedef const CUFStringType<15> CReadOnlyIdentifiedCardTypeType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个交易(所)通道类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<10> CExchangeIDType;
typedef const CUFStringType<10> CReadOnlyExchangeIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个交易(所)所名称类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<30> CExchangeNameType;
typedef const CUFStringType<30> CReadOnlyExchangeNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个交易所生命周期状态类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<1> CExchangeLifePhaseType;
typedef const CUFStringType<1> CReadOnlyExchangeLifePhaseType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个日期类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CDateType;
typedef const CUFStringType<8> CReadOnlyDateType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个持仓日期类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CPositionDateTypeType;
typedef const CUFStringType<8> CReadOnlyPositionDateTypeType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个时间类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CTimeType;
typedef const CUFStringType<8> CReadOnlyTimeType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个组合开平标志类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<4> CCombOffsetFlagType;
typedef const CUFStringType<4> CReadOnlyCombOffsetFlagType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个组合合约代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<80> CCombInstrumentIDType;
typedef const CUFStringType<80> CReadOnlyCombInstrumentIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个客户类型类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<1> CClientTypeType;
typedef const CUFStringType<1> CReadOnlyClientTypeType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个客户名称类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<80> CClientNameType;
typedef const CUFStringType<80> CReadOnlyClientNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个客户编码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<18> CClientIDType;
typedef const CUFStringType<18> CReadOnlyClientIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个资金帐号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<12> CAccountIDType;
typedef const CUFStringType<12> CReadOnlyAccountIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个组合投机套保标志类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<4> CCombHedgeFlagType;
typedef const CUFStringType<4> CReadOnlyCombHedgeFlagType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个品种类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<32> CProductType;
typedef const CUFStringType<32> CReadOnlyProductType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个交易编码表类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<18> CClientTradingIDType;
typedef const CUFStringType<18> CReadOnlyClientTradingIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个席位号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<12> CSeatIDType;
typedef const CUFStringType<12> CReadOnlySeatIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个品种名称类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CProductNameType;
typedef const CUFStringType<40> CReadOnlyProductNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个保证金模板代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CMarginTemplateNoType;
typedef const CUFStringType<8> CReadOnlyMarginTemplateNoType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个模板名称类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CTemplateNameType;
typedef const CUFStringType<40> CReadOnlyTemplateNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个手续费模板编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CFeeTemplateNoType;
typedef const CUFStringType<8> CReadOnlyFeeTemplateNoType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个用户本地报单号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<22> CUserOrderLocalIDType;
typedef const CUFStringType<22> CReadOnlyUserOrderLocalIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个用户本地报单号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<22> COrderRefType;
typedef const CUFStringType<22> CReadOnlyOrderRefType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个本地报单编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<32> COrderLocalIDType;
typedef const CUFStringType<32> CReadOnlyOrderLocalIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个投资者编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<18> CInvestorIDType;
typedef const CUFStringType<18> CReadOnlyInvestorIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个投资者名称类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<30> CInvestorNameType;
typedef const CUFStringType<30> CReadOnlyInvestorNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个用户编码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<30> CUserNameType;
typedef const CUFStringType<30> CReadOnlyUserNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个用户组代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<4> CUserGroupIDType;
typedef const CUFStringType<4> CReadOnlyUserGroupIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个密码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CPasswordType;
typedef const CUFStringType<40> CReadOnlyPasswordType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个消息摘要类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<80> CAbstractType;
typedef const CUFStringType<80> CReadOnlyAbstractType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个产品信息类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CProductInfoType;
typedef const CUFStringType<40> CReadOnlyProductInfoType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个协议信息类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CProtocolInfoType;
typedef const CUFStringType<40> CReadOnlyProtocolInfoType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个业务单元类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CBusinessUnitType;
typedef const CUFStringType<20> CReadOnlyBusinessUnitType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个交易系统名称类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<60> CTradingSystemNameType;
typedef const CUFStringType<60> CReadOnlyTradingSystemNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个交易系统名称类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<60> CSystemNameType;
typedef const CUFStringType<60> CReadOnlySystemNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个DB命令类型类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<64> CCommandTypeType;
typedef const CUFStringType<64> CReadOnlyCommandTypeType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个经纪公司代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<10> CBrokerIDType;
typedef const CUFStringType<10> CReadOnlyBrokerIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个用户自定义域类型类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<64> CCustomType;
typedef const CUFStringType<64> CReadOnlyCustomType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个交易日类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CTradingDayType;
typedef const CUFStringType<8> CReadOnlyTradingDayType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个主题名称类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<60> CTopicNameType;
typedef const CUFStringType<60> CReadOnlyTopicNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个错单编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<12> COrderInsertFailedIDType;
typedef const CUFStringType<12> CReadOnlyOrderInsertFailedIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个错单原因类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<200> COrderInsertFailedReasonType;
typedef const CUFStringType<200> CReadOnlyOrderInsertFailedReasonType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个营业部类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CDepartmentType;
typedef const CUFStringType<40> CReadOnlyDepartmentType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个组织机构代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CInstituteCodeType;
typedef const CUFStringType<40> CReadOnlyInstituteCodeType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个用户组类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<4> CClientGroupType;
typedef const CUFStringType<4> CReadOnlyClientGroupType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个会员帐号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CParticipantAccountType;
typedef const CUFStringType<20> CReadOnlyParticipantAccountType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个授权功能号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<4> CGrantFuncSetType;
typedef const CUFStringType<4> CReadOnlyGrantFuncSetType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个品种编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<12> CProductIDType;
typedef const CUFStringType<12> CReadOnlyProductIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个资金流水号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CAccountSeqNoType;
typedef const CUFStringType<20> CReadOnlyAccountSeqNoType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个结算组代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CSettlementGroupIDType;
typedef const CUFStringType<8> CReadOnlySettlementGroupIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个登录时间类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CLoginTimeType;
typedef const CUFStringType<8> CReadOnlyLoginTimeType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个本地时间类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CLocalTimeType;
typedef const CUFStringType<8> CReadOnlyLocalTimeType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个交易所时间类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CExchangeTimeType;
typedef const CUFStringType<8> CReadOnlyExchangeTimeType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个银行代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<3> CBankIDType;
typedef const CUFStringType<3> CReadOnlyBankIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个银行分中心代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<4> CBankBrchIDType;
typedef const CUFStringType<4> CReadOnlyBankBrchIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个银行账号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CBankAccountType;
typedef const CUFStringType<40> CReadOnlyBankAccountType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个名称类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<100> CNameType;
typedef const CUFStringType<100> CReadOnlyNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个业务功能码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<6> CTradeCodeType;
typedef const CUFStringType<6> CReadOnlyTradeCodeType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个流水号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<12> CSerialType;
typedef const CUFStringType<12> CReadOnlySerialType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个渠道标志类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<2> CDeviceIDType;
typedef const CUFStringType<2> CReadOnlyDeviceIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个期货公司银行编码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<32> CBankCodingForFutureType;
typedef const CUFStringType<32> CReadOnlyBankCodingForFutureType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个登录信息类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<256> CLoginInfoType;
typedef const CUFStringType<256> CReadOnlyLoginInfoType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个报盘定义域类型类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<1024> CSeatCustomType;
typedef const CUFStringType<1024> CReadOnlySeatCustomType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个QDP交易中心编号类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<10> CSystemIDType;
typedef const CUFStringType<10> CReadOnlySystemIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个连接信息类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<64> CServerAddrType;
typedef const CUFStringType<64> CReadOnlyServerAddrType;

/////////////////////////////////////////////////////////////////////////
///CVStringType是一个错误信息类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<80> CErrorMsgType;
typedef const CUFStringType<80> CReadOnlyErrorMsgType;

/////////////////////////////////////////////////////////////////////////
///CVStringType是一个字段名类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<2048> CFieldNameType;
typedef const CUFStringType<2048> CReadOnlyFieldNameType;

/////////////////////////////////////////////////////////////////////////
///CVStringType是一个字段内容类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<2048> CFieldContentType;
typedef const CUFStringType<2048> CReadOnlyFieldContentType;

/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个成交量类型类
/////////////////////////////////////////////////////////////////////////
///任何数量
#define VC_AV '1'
///最小数量
#define VC_MV '2'
///全部数量
#define VC_CV '3'

class CVolumeConditionType : public CUFCharType					
{														
public:													
	CVolumeConditionType(void)									
	{													
	}													
	CVolumeConditionType(const CVolumeConditionType &v)				
	{													
		setValue(v.getValue());							
	}													
	CVolumeConditionType(const char v)							
	{													
		setValue(v);									
	}													
	CVolumeConditionType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CVolumeConditionType& operator=(const CVolumeConditionType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CVolumeConditionType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CVolumeConditionType CReadOnlyVolumeConditionType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个进入本状态原因类
/////////////////////////////////////////////////////////////////////////
///自动切换
#define ER_Automatic '1'
///手动切换
#define ER_Manual '2'
///熔断
#define ER_Fuse '3'

class CEnterReasonType : public CUFCharType					
{														
public:													
	CEnterReasonType(void)									
	{													
	}													
	CEnterReasonType(const CEnterReasonType &v)				
	{													
		setValue(v.getValue());							
	}													
	CEnterReasonType(const char v)							
	{													
		setValue(v);									
	}													
	CEnterReasonType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CEnterReasonType& operator=(const CEnterReasonType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CEnterReasonType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CEnterReasonType CReadOnlyEnterReasonType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个内存数据表操作类型类
/////////////////////////////////////////////////////////////////////////
///插入
#define MDB_INSERT '0'
///更新
#define MDB_UPDATE '1'
///删除
#define MDB_DELETE '2'
///提交
#define MDB_COMMIT '3'

class CMdbActionTypeType : public CUFCharType					
{														
public:													
	CMdbActionTypeType(void)									
	{													
	}													
	CMdbActionTypeType(const CMdbActionTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CMdbActionTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CMdbActionTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CMdbActionTypeType& operator=(const CMdbActionTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CMdbActionTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CMdbActionTypeType CReadOnlyMdbActionTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个强平原因类
/////////////////////////////////////////////////////////////////////////
///非强平
#define FCR_NotForceClose '0'
///资金不足
#define FCR_LackDeposit '1'
///客户超仓
#define FCR_ClientOverPositionLimit '2'
///会员超仓
#define FCR_MemberOverPositionLimit '3'
///持仓非整数倍
#define FCR_NotMultiple '4'

class CForceCloseReasonType : public CUFCharType					
{														
public:													
	CForceCloseReasonType(void)									
	{													
	}													
	CForceCloseReasonType(const CForceCloseReasonType &v)				
	{													
		setValue(v.getValue());							
	}													
	CForceCloseReasonType(const char v)							
	{													
		setValue(v);									
	}													
	CForceCloseReasonType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CForceCloseReasonType& operator=(const CForceCloseReasonType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CForceCloseReasonType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01234"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01234",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01234",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CForceCloseReasonType CReadOnlyForceCloseReasonType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个合约交易状态类
/////////////////////////////////////////////////////////////////////////
///开盘前
#define IS_BeforeTrading '0'
///非交易
#define IS_NoTrading '1'
///连续交易
#define IS_Continous '2'
///集合竞价报单
#define IS_AuctionOrdering '3'
///集合竞价价格平衡
#define IS_AuctionBalance '4'
///集合竞价撮合
#define IS_AuctionMatch '5'
///收盘
#define IS_Closed '6'

class CInstrumentStatusType : public CUFCharType					
{														
public:													
	CInstrumentStatusType(void)									
	{													
	}													
	CInstrumentStatusType(const CInstrumentStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	CInstrumentStatusType(const char v)							
	{													
		setValue(v);									
	}													
	CInstrumentStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CInstrumentStatusType& operator=(const CInstrumentStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CInstrumentStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0123456"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0123456",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0123456",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CInstrumentStatusType CReadOnlyInstrumentStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个开平标志类
/////////////////////////////////////////////////////////////////////////
///开仓
#define OF_Open '0'
///平仓
#define OF_Close '1'
///强平
#define OF_ForceClose '2'
///平今
#define OF_CloseToday '3'
///平昨
#define OF_CloseYesterday '4'

class COffsetFlagType : public CUFCharType					
{														
public:													
	COffsetFlagType(void)									
	{													
	}													
	COffsetFlagType(const COffsetFlagType &v)				
	{													
		setValue(v.getValue());							
	}													
	COffsetFlagType(const char v)							
	{													
		setValue(v);									
	}													
	COffsetFlagType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COffsetFlagType& operator=(const COffsetFlagType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COffsetFlagType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01234"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01234",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01234",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COffsetFlagType CReadOnlyOffsetFlagType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个报单价格条件类
/////////////////////////////////////////////////////////////////////////
///任意价
#define OPT_AnyPrice '1'
///限价
#define OPT_LimitPrice '2'
///最优价
#define OPT_BestPrice '3'
///五档价
#define OPT_FiveLevelPrice '4'

class COrderPriceTypeType : public CUFCharType					
{														
public:													
	COrderPriceTypeType(void)									
	{													
	}													
	COrderPriceTypeType(const COrderPriceTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	COrderPriceTypeType(const char v)							
	{													
		setValue(v);									
	}													
	COrderPriceTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COrderPriceTypeType& operator=(const COrderPriceTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COrderPriceTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("1234"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("1234",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("1234",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COrderPriceTypeType CReadOnlyOrderPriceTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个报单状态类
/////////////////////////////////////////////////////////////////////////
///全部成交
#define OS_AllTraded '0'
///部分成交还在队列中
#define OS_PartTradedQueueing '1'
///部分成交不在队列中
#define OS_PartTradedNotQueueing '2'
///未成交还在队列中
#define OS_NoTradeQueueing '3'
///未成交不在队列中
#define OS_NoTradeNotQueueing '4'
///撤单
#define OS_Canceled '5'
///订单已报入交易所未应答
#define OS_AcceptedNoReply '6'

class COrderStatusType : public CUFCharType					
{														
public:													
	COrderStatusType(void)									
	{													
	}													
	COrderStatusType(const COrderStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	COrderStatusType(const char v)							
	{													
		setValue(v);									
	}													
	COrderStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COrderStatusType& operator=(const COrderStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COrderStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0123456"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0123456",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0123456",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COrderStatusType CReadOnlyOrderStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个内存表变化类型类
/////////////////////////////////////////////////////////////////////////
///插入
#define MTC_INSERT '0'
///修改
#define MTC_UPDATE '1'
///删除
#define MTC_DELETE '2'
///提交
#define MTC_COMMIT '3'

class CMemtableChangeTypeType : public CUFCharType					
{														
public:													
	CMemtableChangeTypeType(void)									
	{													
	}													
	CMemtableChangeTypeType(const CMemtableChangeTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CMemtableChangeTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CMemtableChangeTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CMemtableChangeTypeType& operator=(const CMemtableChangeTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CMemtableChangeTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CMemtableChangeTypeType CReadOnlyMemtableChangeTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个用户类型类
/////////////////////////////////////////////////////////////////////////
///自然人
#define UT_Person '1'
///理财产品
#define UT_Product '2'
///期货公司管理员
#define UT_Manager '3'
///席位
#define UT_Seat '4'

class CUserTypeType : public CUFCharType					
{														
public:													
	CUserTypeType(void)									
	{													
	}													
	CUserTypeType(const CUserTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CUserTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CUserTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CUserTypeType& operator=(const CUserTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CUserTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("1234"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("1234",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("1234",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CUserTypeType CReadOnlyUserTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个交易权限类
/////////////////////////////////////////////////////////////////////////
///可以交易
#define TR_Allow '0'
///只能平仓
#define TR_CloseOnly '1'
///不能交易
#define TR_Forbidden '2'

class CTradingRightType : public CUFCharType					
{														
public:													
	CTradingRightType(void)									
	{													
	}													
	CTradingRightType(const CTradingRightType &v)				
	{													
		setValue(v.getValue());							
	}													
	CTradingRightType(const char v)							
	{													
		setValue(v);									
	}													
	CTradingRightType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CTradingRightType& operator=(const CTradingRightType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CTradingRightType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CTradingRightType CReadOnlyTradingRightType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个有效期类型类
/////////////////////////////////////////////////////////////////////////
///立即完成，否则撤销
#define TC_IOC '1'
///本节有效
#define TC_GFS '2'
///当日有效
#define TC_GFD '3'
///指定日期前有效
#define TC_GTD '4'
///撤销前有效
#define TC_GTC '5'
///集合竞价有效
#define TC_GFA '6'

class CTimeConditionType : public CUFCharType					
{														
public:													
	CTimeConditionType(void)									
	{													
	}													
	CTimeConditionType(const CTimeConditionType &v)				
	{													
		setValue(v.getValue());							
	}													
	CTimeConditionType(const char v)							
	{													
		setValue(v);									
	}													
	CTimeConditionType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CTimeConditionType& operator=(const CTimeConditionType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CTimeConditionType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123456"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123456",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123456",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CTimeConditionType CReadOnlyTimeConditionType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个持仓多空方向类
/////////////////////////////////////////////////////////////////////////
///净
#define PD_Net '1'
///多头
#define PD_Long '2'
///空头
#define PD_Short '3'

class CPosiDirectionType : public CUFCharType					
{														
public:													
	CPosiDirectionType(void)									
	{													
	}													
	CPosiDirectionType(const CPosiDirectionType &v)				
	{													
		setValue(v.getValue());							
	}													
	CPosiDirectionType(const char v)							
	{													
		setValue(v);									
	}													
	CPosiDirectionType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CPosiDirectionType& operator=(const CPosiDirectionType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CPosiDirectionType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CPosiDirectionType CReadOnlyPosiDirectionType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个报单来源类
/////////////////////////////////////////////////////////////////////////
///来自参与者
#define OS_Participant '0'
///来自管理员
#define OS_Administrator '1'

class COrderSourceType : public CUFCharType					
{														
public:													
	COrderSourceType(void)									
	{													
	}													
	COrderSourceType(const COrderSourceType &v)				
	{													
		setValue(v.getValue());							
	}													
	COrderSourceType(const char v)							
	{													
		setValue(v);									
	}													
	COrderSourceType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COrderSourceType& operator=(const COrderSourceType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COrderSourceType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COrderSourceType CReadOnlyOrderSourceType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个会员类型类
/////////////////////////////////////////////////////////////////////////
///交易会员
#define MT_Trading '0'
///结算会员
#define MT_Settlement '1'

class CMemberTypeType : public CUFCharType					
{														
public:													
	CMemberTypeType(void)									
	{													
	}													
	CMemberTypeType(const CMemberTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CMemberTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CMemberTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CMemberTypeType& operator=(const CMemberTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CMemberTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CMemberTypeType CReadOnlyMemberTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个买卖方向类
/////////////////////////////////////////////////////////////////////////
///买
#define D_Buy '0'
///卖
#define D_Sell '1'
///净
#define D_Net '2'

class CDirectionType : public CUFCharType					
{														
public:													
	CDirectionType(void)									
	{													
	}													
	CDirectionType(const CDirectionType &v)				
	{													
		setValue(v.getValue());							
	}													
	CDirectionType(const char v)							
	{													
		setValue(v);									
	}													
	CDirectionType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CDirectionType& operator=(const CDirectionType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CDirectionType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CDirectionType CReadOnlyDirectionType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个币种类
/////////////////////////////////////////////////////////////////////////
///人民币
#define C_CNY '1'
///美元
#define C_UDOLLAR '2'
///新加坡元
#define C_SGD '3'

class CCurrencyType : public CUFCharType					
{														
public:													
	CCurrencyType(void)									
	{													
	}													
	CCurrencyType(const CCurrencyType &v)				
	{													
		setValue(v.getValue());							
	}													
	CCurrencyType(const char v)							
	{													
		setValue(v);									
	}													
	CCurrencyType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CCurrencyType& operator=(const CCurrencyType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CCurrencyType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CCurrencyType CReadOnlyCurrencyType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个处理标志类
/////////////////////////////////////////////////////////////////////////
///已处理
#define DF_Done '1'
///等待处理
#define DF_Wait '2'

class CDealFlagType : public CUFCharType					
{														
public:													
	CDealFlagType(void)									
	{													
	}													
	CDealFlagType(const CDealFlagType &v)				
	{													
		setValue(v.getValue());							
	}													
	CDealFlagType(const char v)							
	{													
		setValue(v);									
	}													
	CDealFlagType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CDealFlagType& operator=(const CDealFlagType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CDealFlagType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CDealFlagType CReadOnlyDealFlagType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个出入金方向类
/////////////////////////////////////////////////////////////////////////
///入金
#define AD_In '1'
///出金
#define AD_Out '2'

class CAccountDirectionType : public CUFCharType					
{														
public:													
	CAccountDirectionType(void)									
	{													
	}													
	CAccountDirectionType(const CAccountDirectionType &v)				
	{													
		setValue(v.getValue());							
	}													
	CAccountDirectionType(const char v)							
	{													
		setValue(v);									
	}													
	CAccountDirectionType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CAccountDirectionType& operator=(const CAccountDirectionType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CAccountDirectionType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CAccountDirectionType CReadOnlyAccountDirectionType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个系统状态类
/////////////////////////////////////////////////////////////////////////
///场下数据可操作状态
#define SS_DbOperational '0'
///场下数据开始导入
#define SS_DbBeginImporting '1'
///数据可上场
#define SS_SyncDataReady '2'
///数据同步中
#define SS_DataSyncing '3'
///数据已上场
#define SS_DataSynced '4'
///合约交易日数据下场成功
#define SS_InstrumentTradingDayDown '5'
///今日交易结束
#define SS_TradingDayOver '6'

class CSystemStatusType : public CUFCharType					
{														
public:													
	CSystemStatusType(void)									
	{													
	}													
	CSystemStatusType(const CSystemStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	CSystemStatusType(const char v)							
	{													
		setValue(v);									
	}													
	CSystemStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CSystemStatusType& operator=(const CSystemStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CSystemStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0123456"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0123456",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0123456",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CSystemStatusType CReadOnlySystemStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个投机套保标志类
/////////////////////////////////////////////////////////////////////////
///投机
#define CHF_Speculation '1'
///套利
#define CHF_Arbitrage '2'
///套保
#define CHF_Hedge '3'
///做市商
#define CHF_MarketMaker '4'

class CHedgeFlagType : public CUFCharType					
{														
public:													
	CHedgeFlagType(void)									
	{													
	}													
	CHedgeFlagType(const CHedgeFlagType &v)				
	{													
		setValue(v.getValue());							
	}													
	CHedgeFlagType(const char v)							
	{													
		setValue(v);									
	}													
	CHedgeFlagType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CHedgeFlagType& operator=(const CHedgeFlagType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CHedgeFlagType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("1234"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("1234",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("1234",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CHedgeFlagType CReadOnlyHedgeFlagType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个操作标志类
/////////////////////////////////////////////////////////////////////////
///删除
#define AF_Delete '0'
///挂起
#define AF_Suspend '1'
///激活
#define AF_Active '2'
///修改
#define AF_Modify '3'

class CActionFlagType : public CUFCharType					
{														
public:													
	CActionFlagType(void)									
	{													
	}													
	CActionFlagType(const CActionFlagType &v)				
	{													
		setValue(v.getValue());							
	}													
	CActionFlagType(const char v)							
	{													
		setValue(v);									
	}													
	CActionFlagType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CActionFlagType& operator=(const CActionFlagType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CActionFlagType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CActionFlagType CReadOnlyActionFlagType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个报单操作状态类
/////////////////////////////////////////////////////////////////////////
///已经提交
#define OAS_Submitted 'a'
///已经接受
#define OAS_Accepted 'b'
///已经被拒绝
#define OAS_Rejected 'c'

class COrderActionStatusType : public CUFCharType					
{														
public:													
	COrderActionStatusType(void)									
	{													
	}													
	COrderActionStatusType(const COrderActionStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	COrderActionStatusType(const char v)							
	{													
		setValue(v);									
	}													
	COrderActionStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COrderActionStatusType& operator=(const COrderActionStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COrderActionStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("abc"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("abc",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("abc",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COrderActionStatusType CReadOnlyOrderActionStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个保证金取值模式类
/////////////////////////////////////////////////////////////////////////
///按比例
#define MVM_Ratio '1'
///按手数
#define MVM_Amt '2'

class CMarginValueModeType : public CUFCharType					
{														
public:													
	CMarginValueModeType(void)									
	{													
	}													
	CMarginValueModeType(const CMarginValueModeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CMarginValueModeType(const char v)							
	{													
		setValue(v);									
	}													
	CMarginValueModeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CMarginValueModeType& operator=(const CMarginValueModeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CMarginValueModeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CMarginValueModeType CReadOnlyMarginValueModeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个手续费取值模式类
/////////////////////////////////////////////////////////////////////////
///按比例
#define FVM_Ratio '1'
///按手数
#define FVM_Amt '2'

class CFeeValueModeType : public CUFCharType					
{														
public:													
	CFeeValueModeType(void)									
	{													
	}													
	CFeeValueModeType(const CFeeValueModeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CFeeValueModeType(const char v)							
	{													
		setValue(v);									
	}													
	CFeeValueModeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CFeeValueModeType& operator=(const CFeeValueModeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CFeeValueModeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CFeeValueModeType CReadOnlyFeeValueModeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个交易所数据同步状态类
/////////////////////////////////////////////////////////////////////////
///未同步
#define DS_Asynchronous '1'
///同步中
#define DS_Synchronizing '2'
///已同步
#define DS_Synchronized '3'

class CDataSyncStatusType : public CUFCharType					
{														
public:													
	CDataSyncStatusType(void)									
	{													
	}													
	CDataSyncStatusType(const CDataSyncStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	CDataSyncStatusType(const char v)							
	{													
		setValue(v);									
	}													
	CDataSyncStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CDataSyncStatusType& operator=(const CDataSyncStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CDataSyncStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CDataSyncStatusType CReadOnlyDataSyncStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个持仓类型类
/////////////////////////////////////////////////////////////////////////
///净持仓
#define PT_Net '1'
///综合持仓
#define PT_Gross '2'

class CPositionTypeType : public CUFCharType					
{														
public:													
	CPositionTypeType(void)									
	{													
	}													
	CPositionTypeType(const CPositionTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CPositionTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CPositionTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CPositionTypeType& operator=(const CPositionTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CPositionTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CPositionTypeType CReadOnlyPositionTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个期权类型类
/////////////////////////////////////////////////////////////////////////
///非期权
#define OT_NotOptions '0'
///看涨
#define OT_CallOptions '1'
///看跌
#define OT_PutOptions '2'

class COptionsTypeType : public CUFCharType					
{														
public:													
	COptionsTypeType(void)									
	{													
	}													
	COptionsTypeType(const COptionsTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	COptionsTypeType(const char v)							
	{													
		setValue(v);									
	}													
	COptionsTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COptionsTypeType& operator=(const COptionsTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COptionsTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COptionsTypeType CReadOnlyOptionsTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个席位状态类
/////////////////////////////////////////////////////////////////////////
///不活跃
#define SS_NotActive '0'
///已登录
#define SS_Login '1'
///已登出
#define SS_Logout '2'

class CSeatStatusType : public CUFCharType					
{														
public:													
	CSeatStatusType(void)									
	{													
	}													
	CSeatStatusType(const CSeatStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	CSeatStatusType(const char v)							
	{													
		setValue(v);									
	}													
	CSeatStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CSeatStatusType& operator=(const CSeatStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CSeatStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CSeatStatusType CReadOnlySeatStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个操作来源类
/////////////////////////////////////////////////////////////////////////
///用户
#define AS_User '0'
///内部
#define AS_Internal '1'
///管理员
#define AS_Administrator '2'

class CActionSourceType : public CUFCharType					
{														
public:													
	CActionSourceType(void)									
	{													
	}													
	CActionSourceType(const CActionSourceType &v)				
	{													
		setValue(v.getValue());							
	}													
	CActionSourceType(const char v)							
	{													
		setValue(v);									
	}													
	CActionSourceType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CActionSourceType& operator=(const CActionSourceType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CActionSourceType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CActionSourceType CReadOnlyActionSourceType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个是否活跃类
/////////////////////////////////////////////////////////////////////////
///不活跃
#define UIA_NoActive '0'
///活跃
#define UIA_Active '1'

class CIsActiveType : public CUFCharType					
{														
public:													
	CIsActiveType(void)									
	{													
	}													
	CIsActiveType(const CIsActiveType &v)				
	{													
		setValue(v.getValue());							
	}													
	CIsActiveType(const char v)							
	{													
		setValue(v);									
	}													
	CIsActiveType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CIsActiveType& operator=(const CIsActiveType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CIsActiveType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CIsActiveType CReadOnlyIsActiveType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个使用api类型类
/////////////////////////////////////////////////////////////////////////
///内部Link
#define ALT_INNER '0'
///QDPMDLink
#define ALT_QDPMD 'g'
///QTestLink
#define ALT_QDPTEST 'q'
///APEXLink
#define ALT_APEX 'p'

class CApiLinkTypeType : public CUFCharType					
{														
public:													
	CApiLinkTypeType(void)									
	{													
	}													
	CApiLinkTypeType(const CApiLinkTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CApiLinkTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CApiLinkTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CApiLinkTypeType& operator=(const CApiLinkTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CApiLinkTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0gqp"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0gqp",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0gqp",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CApiLinkTypeType CReadOnlyApiLinkTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个触发条件类
/////////////////////////////////////////////////////////////////////////
///立即
#define CC_Immediately '1'
///止损
#define CC_Touch '2'
///止赢
#define CC_TouchProfit '3'
///预埋单
#define CC_ParkedOrder '4'
///最新价大于条件价
#define CC_LastPriceGreaterThanStopPrice '5'
///最新价大于等于条件价
#define CC_LastPriceGreaterEqualStopPrice '6'
///最新价小于条件价
#define CC_LastPriceLesserThanStopPrice '7'
///最新价小于等于条件价
#define CC_LastPriceLesserEqualStopPrice '8'
///卖一价大于条件价
#define CC_AskPriceGreaterThanStopPrice '9'
///卖一价大于等于条件价
#define CC_AskPriceGreaterEqualStopPrice 'A'
///卖一价小于条件价
#define CC_AskPriceLesserThanStopPrice 'B'
///卖一价小于等于条件价
#define CC_AskPriceLesserEqualStopPrice 'C'
///买一价大于条件价
#define CC_BidPriceGreaterThanStopPrice 'D'
///买一价大于等于条件价
#define CC_BidPriceGreaterEqualStopPrice 'E'
///买一价小于条件价
#define CC_BidPriceLesserThanStopPrice 'F'
///买一价小于等于条件价
#define CC_BidPriceLesserEqualStopPrice 'H'

class CContingentConditionType : public CUFCharType					
{														
public:													
	CContingentConditionType(void)									
	{													
	}													
	CContingentConditionType(const CContingentConditionType &v)				
	{													
		setValue(v.getValue());							
	}													
	CContingentConditionType(const char v)							
	{													
		setValue(v);									
	}													
	CContingentConditionType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CContingentConditionType& operator=(const CContingentConditionType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CContingentConditionType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123456789ABCDEFH"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123456789ABCDEFH",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123456789ABCDEFH",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CContingentConditionType CReadOnlyContingentConditionType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个产品类型类
/////////////////////////////////////////////////////////////////////////
///未知类型
#define PC_Unknown '0'
///期货
#define PC_Futures '1'
///期权
#define PC_Options '2'
///组合
#define PC_Combination '3'
///即期
#define PC_Spot '4'
///期转现
#define PC_EFP '5'
///证券
#define PC_Stocks '7'
///股票期权
#define PC_StockOptions '8'

class CProductClassType : public CUFCharType					
{														
public:													
	CProductClassType(void)									
	{													
	}													
	CProductClassType(const CProductClassType &v)				
	{													
		setValue(v.getValue());							
	}													
	CProductClassType(const char v)							
	{													
		setValue(v);									
	}													
	CProductClassType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CProductClassType& operator=(const CProductClassType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CProductClassType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01234578"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01234578",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01234578",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CProductClassType CReadOnlyProductClassType;		


/////////////////////////////////////////////////////////////////////////
///CStringType是一个产品组代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CProductGroupIDType;
typedef const CUFStringType<8> CReadOnlyProductGroupIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个币种代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<3> CCurrencyIDType;
typedef const CUFStringType<3> CReadOnlyCurrencyIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType是一个币种名称类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CCurrencyNameType;
typedef const CUFStringType<20> CReadOnlyCurrencyNameType;

/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个组合保证金类型类
/////////////////////////////////////////////////////////////////////////
///单腿保证金组合
#define MCT_SingleLeg '0'
///合约组大边保证金组合
#define MCT_BigLeg '1'
///组合合约保证金
#define MCT_CombMargin '2'
///Span保证金
#define MCT_SpanMargin '3'
///组合剩余合约单向大边
#define MCT_CombLeftMaxMargin '4'
///组合剩余合约双边
#define MCT_CombLeftAllMargin '5'
///盘后大单边盘中双边
#define MCT_TradedBigLeg '6'
///合约对锁
#define MCT_InstrumentBigLeg '7'

class CClientMarginCombTypeType : public CUFCharType					
{														
public:													
	CClientMarginCombTypeType(void)									
	{													
	}													
	CClientMarginCombTypeType(const CClientMarginCombTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CClientMarginCombTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CClientMarginCombTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CClientMarginCombTypeType& operator=(const CClientMarginCombTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CClientMarginCombTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01234567"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01234567",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01234567",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CClientMarginCombTypeType CReadOnlyClientMarginCombTypeType;		


/////////////////////////////////////////////////////////////////////////
///CStringType是一个合约组代码类
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<30> CInstrumentGroupIDType;
typedef const CUFStringType<30> CReadOnlyInstrumentGroupIDType;

/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个业务类别类
/////////////////////////////////////////////////////////////////////////
///普通
#define BT_Normal '1'
///撤单
#define BT_Cancel '2'
///ETF申赎
#define BT_AppliedForRedeemed '3'
///最优五档即时成交剩余撤销
#define BT_FiveLevelIOC '4'
///最优五档即时成交剩余转限价
#define BT_FiveLevelGFD '5'
///即时成交剩余撤销
#define BT_BestPriceIOC '6'
///全额成交或撤销
#define BT_FOK '7'
///本方最优价格
#define BT_SelfGFD '8'
///对方最优价格
#define BT_CpGFD '9'
///金交所中立仓申报
#define BT_SGEMidApp 'a'
///套利组合单
#define BT_Combination 'b'
///套利非组合单
#define BT_Grab 'c'
///金交所递延交割申报
#define BT_SGEDeferDeliApp 'd'
///互换单
#define BT_SWAP 'e'

class CBusinessTypeType : public CUFCharType					
{														
public:													
	CBusinessTypeType(void)									
	{													
	}													
	CBusinessTypeType(const CBusinessTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CBusinessTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CBusinessTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CBusinessTypeType& operator=(const CBusinessTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CBusinessTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123456789abcde"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123456789abcde",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123456789abcde",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CBusinessTypeType CReadOnlyBusinessTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个处理状态类
/////////////////////////////////////////////////////////////////////////
///处理正确
#define PS_OK '0'
///处理中稍后查询
#define PS_PROCESSING '1'
///正在冲正
#define PS_REVERSING '2'
///冲正失败
#define PS_REVFAIL '3'
///冲正正确
#define PS_REVOK '4'

class CProcStatusType : public CUFCharType					
{														
public:													
	CProcStatusType(void)									
	{													
	}													
	CProcStatusType(const CProcStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	CProcStatusType(const char v)							
	{													
		setValue(v);									
	}													
	CProcStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CProcStatusType& operator=(const CProcStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CProcStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01234"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01234",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01234",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CProcStatusType CReadOnlyProcStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个转账交易状态类
/////////////////////////////////////////////////////////////////////////
///正常
#define TS_TRFS_Normal '0'
///被冲正
#define TS_TRFS_Repealed '1'

class CTransferStatusType : public CUFCharType					
{														
public:													
	CTransferStatusType(void)									
	{													
	}													
	CTransferStatusType(const CTransferStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	CTransferStatusType(const char v)							
	{													
		setValue(v);									
	}													
	CTransferStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CTransferStatusType& operator=(const CTransferStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CTransferStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CTransferStatusType CReadOnlyTransferStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个费用支付标志类
/////////////////////////////////////////////////////////////////////////
///由受益方支付费用
#define FPF_FPF_BEN '0'
///由发送方支付费用
#define FPF_FPF_OUR '1'
///由发送方支付发起的费用，受益方支付接受的费用
#define FPF_FPF_SHA '2'

class CFeePayFlagType : public CUFCharType					
{														
public:													
	CFeePayFlagType(void)									
	{													
	}													
	CFeePayFlagType(const CFeePayFlagType &v)				
	{													
		setValue(v.getValue());							
	}													
	CFeePayFlagType(const char v)							
	{													
		setValue(v);									
	}													
	CFeePayFlagType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CFeePayFlagType& operator=(const CFeePayFlagType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CFeePayFlagType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CFeePayFlagType CReadOnlyFeePayFlagType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个密码标志类
/////////////////////////////////////////////////////////////////////////
///不核对
#define PF_BPWDF_NoCheck '0'
///明文核对
#define PF_BPWDF_BlankCheck '1'
///密文核对
#define PF_BPWDF_EncryptCheck '2'

class CPwdFlagType : public CUFCharType					
{														
public:													
	CPwdFlagType(void)									
	{													
	}													
	CPwdFlagType(const CPwdFlagType &v)				
	{													
		setValue(v.getValue());							
	}													
	CPwdFlagType(const char v)							
	{													
		setValue(v);									
	}													
	CPwdFlagType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CPwdFlagType& operator=(const CPwdFlagType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CPwdFlagType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CPwdFlagType CReadOnlyPwdFlagType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个银行账号类型类
/////////////////////////////////////////////////////////////////////////
///存折
#define BAT_VBAT_BankBook '1'
///储蓄卡
#define BAT_VBAT_BankCard '2'
///信用卡
#define BAT_VBAT_CreditCard '3'

class CBankAccTypeType : public CUFCharType					
{														
public:													
	CBankAccTypeType(void)									
	{													
	}													
	CBankAccTypeType(const CBankAccTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CBankAccTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CBankAccTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CBankAccTypeType& operator=(const CBankAccTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CBankAccTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CBankAccTypeType CReadOnlyBankAccTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个是否标志类
/////////////////////////////////////////////////////////////////////////
///是
#define YNI_YNI_Yes '0'
///否
#define YNI_YNI_No '1'

class CYesNoIndicatorType : public CUFCharType					
{														
public:													
	CYesNoIndicatorType(void)									
	{													
	}													
	CYesNoIndicatorType(const CYesNoIndicatorType &v)				
	{													
		setValue(v.getValue());							
	}													
	CYesNoIndicatorType(const char v)							
	{													
		setValue(v);									
	}													
	CYesNoIndicatorType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CYesNoIndicatorType& operator=(const CYesNoIndicatorType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CYesNoIndicatorType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CYesNoIndicatorType CReadOnlyYesNoIndicatorType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个有效标志类
/////////////////////////////////////////////////////////////////////////
///未确认
#define ALF_AVAF_Invalid '0'
///有效
#define ALF_AVAF_Valid '1'
///冲正
#define ALF_AVAF_Repeal '2'
///失败
#define ALF_AVAF_FAIL '3'

class CAvailabilityFlagType : public CUFCharType					
{														
public:													
	CAvailabilityFlagType(void)									
	{													
	}													
	CAvailabilityFlagType(const CAvailabilityFlagType &v)				
	{													
		setValue(v.getValue());							
	}													
	CAvailabilityFlagType(const char v)							
	{													
		setValue(v);									
	}													
	CAvailabilityFlagType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CAvailabilityFlagType& operator=(const CAvailabilityFlagType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CAvailabilityFlagType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CAvailabilityFlagType CReadOnlyAvailabilityFlagType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个金交所递延支付方向类
/////////////////////////////////////////////////////////////////////////
///多付空
#define PD_Buy '0'
///空付多
#define PD_Sell '1'
///支付方向未定
#define PD_Unknown '2'

class CPayDirectionType : public CUFCharType					
{														
public:													
	CPayDirectionType(void)									
	{													
	}													
	CPayDirectionType(const CPayDirectionType &v)				
	{													
		setValue(v.getValue());							
	}													
	CPayDirectionType(const char v)							
	{													
		setValue(v);									
	}													
	CPayDirectionType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CPayDirectionType& operator=(const CPayDirectionType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CPayDirectionType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CPayDirectionType CReadOnlyPayDirectionType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个执行类型类
/////////////////////////////////////////////////////////////////////////
///执行
#define AT_Exec '1'
///放弃
#define AT_Abandon '2'

class CActionTypeType : public CUFCharType					
{														
public:													
	CActionTypeType(void)									
	{													
	}													
	CActionTypeType(const CActionTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CActionTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CActionTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CActionTypeType& operator=(const CActionTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CActionTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CActionTypeType CReadOnlyActionTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个期权行权后是否保留期货头寸的标记类
/////////////////////////////////////////////////////////////////////////
///保留
#define RPFT_Reserve '0'
///不保留
#define RPFT_UnReserve '1'

class CReservePositionFlagTypeType : public CUFCharType					
{														
public:													
	CReservePositionFlagTypeType(void)									
	{													
	}													
	CReservePositionFlagTypeType(const CReservePositionFlagTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CReservePositionFlagTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CReservePositionFlagTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CReservePositionFlagTypeType& operator=(const CReservePositionFlagTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CReservePositionFlagTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CReservePositionFlagTypeType CReadOnlyReservePositionFlagTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个期权行权后生成的头寸是否自动平仓类
/////////////////////////////////////////////////////////////////////////
///自动平仓
#define CFT_AutoClose '0'
///免于自动平仓
#define CFT_NotToClose '1'

class CCloseFlagTypeType : public CUFCharType					
{														
public:													
	CCloseFlagTypeType(void)									
	{													
	}													
	CCloseFlagTypeType(const CCloseFlagTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CCloseFlagTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CCloseFlagTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CCloseFlagTypeType& operator=(const CCloseFlagTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CCloseFlagTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CCloseFlagTypeType CReadOnlyCloseFlagTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个执行结果类
/////////////////////////////////////////////////////////////////////////
///没有执行
#define ERT_NoExec 'n'
///已经取消
#define ERT_Canceled 'c'
///执行成功
#define ERT_OK '0'
///未知
#define ERT_Unknown 'a'

class CExecResultTypeType : public CUFCharType					
{														
public:													
	CExecResultTypeType(void)									
	{													
	}													
	CExecResultTypeType(const CExecResultTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CExecResultTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CExecResultTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CExecResultTypeType& operator=(const CExecResultTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CExecResultTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("nc0a"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("nc0a",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("nc0a",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CExecResultTypeType CReadOnlyExecResultTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个询价状态类
/////////////////////////////////////////////////////////////////////////
///已经提交
#define FQST_Submitted 'a'
///已经接受
#define FQST_Accepted 'b'
///已经被拒绝
#define FQST_Rejected 'c'

class CForQuoteStatusTypeType : public CUFCharType					
{														
public:													
	CForQuoteStatusTypeType(void)									
	{													
	}													
	CForQuoteStatusTypeType(const CForQuoteStatusTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CForQuoteStatusTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CForQuoteStatusTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CForQuoteStatusTypeType& operator=(const CForQuoteStatusTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CForQuoteStatusTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("abc"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("abc",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("abc",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CForQuoteStatusTypeType CReadOnlyForQuoteStatusTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个撤单对应的报单类别类
/////////////////////////////////////////////////////////////////////////
///普通报单
#define OAT_Order '1'
///期权行权申请执行
#define OAT_ExecOrder '2'
///期权行权申请放弃
#define OAT_AbandonOrder '3'
///双边报价单
#define OAT_Quote '4'
///单边报价单
#define OAT_SingleQuote '5'
///报价衍生委托单
#define OAT_QuoteOrder '5'

class COrderActionTypeType : public CUFCharType					
{														
public:													
	COrderActionTypeType(void)									
	{													
	}													
	COrderActionTypeType(const COrderActionTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	COrderActionTypeType(const char v)							
	{													
		setValue(v);									
	}													
	COrderActionTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COrderActionTypeType& operator=(const COrderActionTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COrderActionTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123455"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123455",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123455",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COrderActionTypeType CReadOnlyOrderActionTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个投资者类别类
/////////////////////////////////////////////////////////////////////////
///普通投资者
#define OAT_Normal '1'
///做市商
#define OAT_MarketMaker '2'

class CInvestorSortType : public CUFCharType					
{														
public:													
	CInvestorSortType(void)									
	{													
	}													
	CInvestorSortType(const CInvestorSortType &v)				
	{													
		setValue(v.getValue());							
	}													
	CInvestorSortType(const char v)							
	{													
		setValue(v);									
	}													
	CInvestorSortType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CInvestorSortType& operator=(const CInvestorSortType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CInvestorSortType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CInvestorSortType CReadOnlyInvestorSortType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个成交类型类
/////////////////////////////////////////////////////////////////////////
///普通成交
#define TT_Normal '1'
///组合成交
#define TT_Combination '2'

class CTradeTypeType : public CUFCharType					
{														
public:													
	CTradeTypeType(void)									
	{													
	}													
	CTradeTypeType(const CTradeTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CTradeTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CTradeTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CTradeTypeType& operator=(const CTradeTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CTradeTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CTradeTypeType CReadOnlyTradeTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType是一个期权行权方式类
/////////////////////////////////////////////////////////////////////////
///不行权
#define OM_NullOptions '0'
///欧式行权
#define OM_EuOptions 'E'
///美式行权
#define OM_AmOptions 'A'

class COptionsModeType : public CUFCharType					
{														
public:													
	COptionsModeType(void)									
	{													
	}													
	COptionsModeType(const COptionsModeType &v)				
	{													
		setValue(v.getValue());							
	}													
	COptionsModeType(const char v)							
	{													
		setValue(v);									
	}													
	COptionsModeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COptionsModeType& operator=(const COptionsModeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COptionsModeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0EA"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0EA",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0EA",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COptionsModeType CReadOnlyOptionsModeType;		


#endif
