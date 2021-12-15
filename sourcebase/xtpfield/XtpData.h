// XtpData.h: 
//
///20090118	xuzh		�����˲�ѯ����־��NT-0065��
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XTPDATA_H__EA501ADE_818C_4F9A_8738_AC9CCAF0B941__INCLUDED_)
#define AFX_XTPDATA_H__EA501ADE_818C_4F9A_8738_AC9CCAF0B941__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FieldDescribe.h"
#include "customDataType.h"

///��Լ
class CInstrumentField
{
public:
	///����������
	CExchangeIDType	ExchangeID;
	///Ʒ�ִ���
	CProductIDType	ProductID;
	///Ʒ������
	CProductNameType	ProductName;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///��Լ����
	CInstrumentNameType	InstrumentName;
	///�������
	CYearType	DeliveryYear;
	///������
	CMonthType	DeliveryMonth;
	///�޼۵�����µ���
	CVolumeType	MaxLimitOrderVolume;
	///�޼۵���С�µ���
	CVolumeType	MinLimitOrderVolume;
	///�м۵�����µ���
	CVolumeType	MaxMarketOrderVolume;
	///�м۵���С�µ���
	CVolumeType	MinMarketOrderVolume;
	///��������
	CVolumeMultipleType	VolumeMultiple;
	///���۵�λ
	CPriceTickType	PriceTick;
	///����
	CCurrencyType	Currency;
	///��ͷ�޲�
	CVolumeType	LongPosLimit;
	///��ͷ�޲�
	CVolumeType	ShortPosLimit;
	///��ͣ���
	CPriceType	LowerLimitPrice;
	///��ͣ���
	CPriceType	UpperLimitPrice;
	///�����
	CPriceType	PreSettlementPrice;
	///��Լ����״̬
	CInstrumentStatusType	InstrumentStatus;
	///������
	CDateType	CreateDate;
	///������
	CDateType	OpenDate;
	///������
	CDateType	ExpireDate;
	///��ʼ������
	CDateType	StartDelivDate;
	///��󽻸���
	CDateType	EndDelivDate;
	///���ƻ�׼��
	CPriceType	BasisPrice;
	///��ǰ�Ƿ���
	CBoolType	IsTrading;
	///������Ʒ����
	CInstrumentIDType	UnderlyingInstrID;
	///������Ʒ����
	CUnderlyingMultipleType	UnderlyingMultiple;
	///�ֲ�����
	CPositionTypeType	PositionType;
	///ִ�м�
	CPriceType	StrikePrice;
	///��Ȩ����
	COptionsTypeType	OptionsType;
	///��Ʒ����
	CProductClassType	ProductClass;
	///��Ȩ��Ȩ��ʽ
	COptionsModeType	OptionsMode;
	///��Ʒ��
	CProductGroupIDType	ProductGroupID;
	///ͨ����Ӧ��APIID
	CNumberType	APIID;
	///��Ϻ�Լ�ȵ�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_Instrument=0x3002;

///��Լ״̬
class CInstrumentStatusField
{
public:
	///����������
	CExchangeIDType	ExchangeID;
	///Ʒ�ִ���
	CProductIDType	ProductID;
	///Ʒ������
	CProductNameType	ProductName;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///��Լ����
	CInstrumentNameType	InstrumentName;
	///�������
	CYearType	DeliveryYear;
	///������
	CMonthType	DeliveryMonth;
	///�޼۵�����µ���
	CVolumeType	MaxLimitOrderVolume;
	///�޼۵���С�µ���
	CVolumeType	MinLimitOrderVolume;
	///�м۵�����µ���
	CVolumeType	MaxMarketOrderVolume;
	///�м۵���С�µ���
	CVolumeType	MinMarketOrderVolume;
	///��������
	CVolumeMultipleType	VolumeMultiple;
	///���۵�λ
	CPriceTickType	PriceTick;
	///����
	CCurrencyType	Currency;
	///��ͷ�޲�
	CVolumeType	LongPosLimit;
	///��ͷ�޲�
	CVolumeType	ShortPosLimit;
	///��ͣ���
	CPriceType	LowerLimitPrice;
	///��ͣ���
	CPriceType	UpperLimitPrice;
	///�����
	CPriceType	PreSettlementPrice;
	///��Լ����״̬
	CInstrumentStatusType	InstrumentStatus;
	///������
	CDateType	CreateDate;
	///������
	CDateType	OpenDate;
	///������
	CDateType	ExpireDate;
	///��ʼ������
	CDateType	StartDelivDate;
	///��󽻸���
	CDateType	EndDelivDate;
	///���ƻ�׼��
	CPriceType	BasisPrice;
	///��ǰ�Ƿ���
	CBoolType	IsTrading;
	///������Ʒ����
	CInstrumentIDType	UnderlyingInstrID;
	///������Ʒ����
	CUnderlyingMultipleType	UnderlyingMultiple;
	///�ֲ�����
	CPositionTypeType	PositionType;
	///ִ�м�
	CPriceType	StrikePrice;
	///��Ȩ����
	COptionsTypeType	OptionsType;
	///��Ʒ����
	CProductClassType	ProductClass;
	///��Ȩ��Ȩ��ʽ
	COptionsModeType	OptionsMode;
	///��Ʒ��
	CProductGroupIDType	ProductGroupID;
	///ͨ����Ӧ��APIID
	CNumberType	APIID;
	///��Ϻ�Լ�ȵ�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InstrumentStatus=0x3003;

///������
class CExchangeField
{
public:
	///������
	CTradingDayType	TradingDay;
	///����������
	CExchangeIDType	ExchangeID;
	///����������
	CExchangeNameType	ExchangeName;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(ExchangeName)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_Exchange=0x3004;

///�ͻ����ױ���
class CClientTradingIDField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///�ʽ��ʺ�
	CAccountIDType	AccountID;
	///����������
	CExchangeIDType	ExchangeID;
	///��Ա���
	CParticipantIDType	ParticipantID;
	///�ͻ�����
	CClientIDType	ClientID;
	///�ͻ�����Ȩ��
	CTradingRightType	ClientRight;
	///�ͻ�����
	CClientTypeType	ClientType;
	///�ͻ���ֵ����
	CHedgeFlagType	ClientHedgeFlag;
	///�Ƿ��Ծ
	CIsActiveType	IsActive;
	///ͨ����Ӧ��APIID
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_ClientTradingID=0x3006;

///Ͷ���߱�֤����
class CInvestorMarginField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///����������
	CExchangeIDType	ExchangeID;
	///Ͷ���߱���
	CInvestorIDType	InvestorID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///Ͷ���ױ���־
	CHedgeFlagType	HedgeFlag;
	///��ͷռ�ñ�֤�𰴱���
	CRatioType	LongMarginRate;
	///��ͷ��֤������
	CRatioType	LongMarginAmt;
	///��ͷռ�ñ�֤�𰴱���
	CRatioType	ShortMarginRate;
	///��ͷ��֤������
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorMargin=0x3007;

///Ͷ���ߺ�Լ�ֲ�
class CInvestorPositionField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///����������
	CExchangeIDType	ExchangeID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///��Ա���
	CParticipantIDType	ParticipantID;
	///�ͻ�����
	CClientIDType	ClientID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///��������
	CDirectionType	Direction;
	///Ͷ���ױ���־
	CHedgeFlagType	HedgeFlag;
	///ռ�ñ�֤��
	CMoneyType	UsedMargin;
	///�ֲܳ���
	CVolumeType	Position;
	///���ճֲֳɱ�
	CPriceType	PositionCost;
	///��ֲ���(����ֵ)
	CVolumeType	YdPosition;
	///���ճֲֳɱ�
	CMoneyType	YdPositionCost;
	///����ı�֤��
	CMoneyType	FrozenMargin;
	///���ֶ���ֲ�
	CVolumeType	FrozenPosition;
	///ƽ�ֶ���ֲ�
	CVolumeType	FrozenClosing;
	///�����Ȩ����
	CMoneyType	FrozenPremium;
	///���һ�ʳɽ����
	CTradeIDType	LastTradeID;
	///���һ�ʱ��ر������
	COrderLocalIDType	LastOrderLocalID;
	///����
	CCurrencyIDType	Currency;
	///�ֲ�ӯ��
	CMoneyType	PositionProfit;
	///��ֲ���
	CVolumeType	TodayPosition;
	///���ƽ�ֶ���
	CVolumeType	FrozenTodayClosing;
	///�ɽ�����
	CTradeTypeType	TradeType;
	///�ʽ��ʺ�
	CAccountIDType	AccountID;
	///���㸡��ӯ�����¼�
	CPriceType	LastPrice;
	///�ֲֿܳ�ƽ������(����ƽ�ֶ���ֲ�)
	CVolumeType	PositionClose;
	///��ֲֿ�ƽ������(����ƽ�ֶ���ֲ�)
	CVolumeType	YdPositionClose;
	///��ֲ�ƽ�ֶ���ֲ�
	CVolumeType	YdFrozenClosing;
	///���㸡��ӯ��ʱ���ֲܳ�
	CVolumeType	CacalProfitPosition;
	///��Ȩ����
	COptionsTypeType	OptionType;
	///��Ȩ��
	CPriceType	StrikePrice;
	///��Ȩ��Ӧ�ı�ĺ�Լ����
	CInstrumentIDType	OptionInstrumentID;
	///��ֲֳֳɱ�
	CMoneyType	TodayPositionCost;
	///���ֲ߳�
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorPosition=0x3008;

///Ͷ����������
class CInvestorFeeField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///����������
	CExchangeIDType	ExchangeID;
	///Ͷ���߱���
	CInvestorIDType	InvestorID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///Ͷ���ױ���־
	CHedgeFlagType	HedgeFlag;
	///���������Ѱ�����
	CRatioType	OpenFeeRate;
	///���������Ѱ�����
	CRatioType	OpenFeeAmt;
	///ƽ�������Ѱ�����
	CRatioType	OffsetFeeRate;
	///ƽ�������Ѱ�����
	CRatioType	OffsetFeeAmt;
	///ƽ��������Ѱ�����
	CRatioType	OTFeeRate;
	///ƽ��������Ѱ�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorFee=0x3009;

///�û�Ͷ���߹�ϵ
class CUserInvestorField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�����û�����
	CUserIDType	UserID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///��Ȩ���ܼ�
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_UserInvestor=0x300B;

///Ͷ����
class CInvestorField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///Ͷ��������
	CInvestorNameType	InvestorName;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(InvestorName)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_Investor=0x300C;

///Ͷ�����ʽ��˻�
class CInvestorAccountField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///�ʽ��ʺ�
	CAccountIDType	AccountID;
	///�ϴν���׼����
	CMoneyType	PreBalance;
	///���տ����ʽ�
	CMoneyType	PreAvailable;
	///�����
	CMoneyType	Deposit;
	///������
	CMoneyType	Withdraw;
	///ռ�ñ�֤��
	CMoneyType	Margin;
	///��ȨȨ������֧
	CMoneyType	Premium;
	///������
	CMoneyType	Fee;
	///����ı�֤��
	CMoneyType	FrozenMargin;
	///����Ȩ����
	CMoneyType	FrozenPremium;
	///����������
	CMoneyType	FrozenFee;
	///ƽ��ӯ��
	CMoneyType	CloseProfit;
	///�ֲ�ӯ��
	CMoneyType	PositionProfit;
	///�����ʽ�
	CMoneyType	Available;
	///����׼����
	CMoneyType	Balance;
	///��ͷռ�ñ�֤��
	CMoneyType	LongMargin;
	///��ͷռ�ñ�֤��
	CMoneyType	ShortMargin;
	///��ͷ����ı�֤��
	CMoneyType	LongFrozenMargin;
	///��ͷ����ı�֤��
	CMoneyType	ShortFrozenMargin;
	///��̬Ȩ��
	CMoneyType	DynamicRights;
	///���ն�
	CMoneyType	Risk;
	///��������
	CMoneyType	OtherFee;
	///��Ѻ���
	CMoneyType	Mortgage;
	///����
	CCurrencyIDType	Currency;
	///�ܶ���ֲ�
	CVolumeType	TotalFrozenPos;
	///���ճ����
	CMoneyType	TodayInOut;
	///�����ͷű�֤��
	CMoneyType	ReleaseMargin;
	///��ӯ�Ƿ����
	CBoolType	IsProfitCanUse;
	///��ʱ�����ʽ�
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorAccount=0x300E;

///��֤��������
class CMoneyField
{
public:
	///��֤��
	CMoneyType	Margin;
	///������
	CMoneyType	Fee;
	///Ȩ����
	CMoneyType	Premium;
	///��֤��仯ֵ
	CMoneyType	MarginChanged;
	///���ᱣ֤��仯ֵ
	CMoneyType	FrozenMarginChanged;
	///ռ�õı�֤��
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_Money=0x300F;

///�ͻ��ʽ���Ϣ
class CExCapitalDataField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///�ʽ��ʺ�
	CAccountIDType	AccountID;
	///�ϴν���׼����
	CMoneyType	PreBalance;
	///���տ����ʽ�
	CMoneyType	PreAvailable;
	///�����
	CMoneyType	Deposit;
	///������
	CMoneyType	Withdraw;
	///ռ�ñ�֤��
	CMoneyType	Margin;
	///��ȨȨ������֧
	CMoneyType	Premium;
	///������
	CMoneyType	Fee;
	///����ı�֤��
	CMoneyType	FrozenMargin;
	///����Ȩ����
	CMoneyType	FrozenPremium;
	///����������
	CMoneyType	FrozenFee;
	///ƽ��ӯ��
	CMoneyType	CloseProfit;
	///�ֲ�ӯ��
	CMoneyType	PositionProfit;
	///�����ʽ�
	CMoneyType	Available;
	///����׼����
	CMoneyType	Balance;
	///��ͷռ�ñ�֤��
	CMoneyType	LongMargin;
	///��ͷռ�ñ�֤��
	CMoneyType	ShortMargin;
	///��ͷ����ı�֤��
	CMoneyType	LongFrozenMargin;
	///��ͷ����ı�֤��
	CMoneyType	ShortFrozenMargin;
	///��̬Ȩ��
	CMoneyType	DynamicRights;
	///���ն�
	CMoneyType	Risk;
	///��������
	CMoneyType	OtherFee;
	///��Ѻ���
	CMoneyType	Mortgage;
	///����
	CCurrencyIDType	Currency;
	///�ܶ���ֲ�
	CVolumeType	TotalFrozenPos;
	///���ճ����
	CMoneyType	TodayInOut;
	///�����ͷű�֤��
	CMoneyType	ReleaseMargin;
	///��ӯ�Ƿ����
	CBoolType	IsProfitCanUse;
	///��ʱ�����ʽ�
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_ExCapitalData=0x3008;

///�ּ�����Ӧ��
class CMBLMarketDataField
{
public:
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///��������
	CDirectionType	Direction;
	///�۸�
	CPriceType	Price;
	///����
	CVolumeType	Volume;
	///����޸�ʱ��
	CTimeType	UpdateTime;
	///����޸ĺ���
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_MBLMarketData=0x3106;

///�ּ���������
class CQryMBLMarketDataField
{
public:
	///����������
	CExchangeIDType	ExchangeID;
	///��ʼ��Լ����
	CInstrumentIDType	InstIDStart;
	///������Լ����
	CInstrumentIDType	InstIDEnd;
	///��������
	CDirectionType	Direction;
	///��¼���͹�˾���
	CBrokerIDType	LogBrokerID;
	///��¼�û�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryMBLMarketData=0x3107;

///�û�
class CUserField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�û�����
	CUserIDType	UserID;
	///�û���¼����
	CPasswordType	Password;
	///�Ƿ��Ծ
	CIsActiveType	IsActive;
	///�û�����
	CUserNameType	UserName;
	///�û�����
	CUserTypeType	UserType;
	///Ӫҵ��
	CDepartmentType	Department;
	///��Ȩ���ܼ�
	CGrantFuncSetType	GrantFuncSet;
	///�Ƿ���IP��MAC
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_User=0x3020;

///�û���¼
class CUserLoginField
{
public:
	///������
	CDateType	TradingDay;
	///�����û�����
	CUserIDType	UserID;
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///����
	CPasswordType	Password;
	///�û��˲�Ʒ��Ϣ
	CProductInfoType	UserProductInfo;
	///�ӿڶ˲�Ʒ��Ϣ
	CProductInfoType	InterfaceProductInfo;
	///Э����Ϣ
	CProtocolInfoType	ProtocolInfo;
	///IP��ַ
	CIPAddressType	IPAddress;
	///Mac��ַ
	CMacAddressType	MacAddress;
	///�������Ĵ���
	CDataCenterIDType	DataCenterID;
	///��̬����
	CPasswordType	OneTimePassword;
	///�ն�IP��ַ
	CIPAddressType	ClientIPAddress;
	///��¼�ɹ�ʱ��
	CTimeType	LoginTime;
	///��󱨵����ر��
	CUserOrderLocalIDType	MaxOrderLocalID;
	///����ϵͳ����
	CTradingSystemNameType	TradingSystemName;
	///�û�����
	CUserTypeType	UserType;
	///���ͨѶ��
	CCommFluxType	MaxCommFlux;
	///�Ự���
	CSessionIDType	SessionID;
	///ǰ�ñ��
	CFrontIDType	FrontID;
	///Socket���
	CNumberType	SockID;
	///�ͻ��˽�����
	CDateType	ClientTradingDay;
	///д������ʱʱ��
	CNumberType	Heartbeat;
	///�Ի����������
	CNumberType	DialogSeqno;
	///˽�����������
	CNumberType	PrivateSeqno;
	///�������������
	CNumberType	PublicSeqno;
	///�������ں�
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_UserLogin=0x3021;

///�û��Ự
class CUserSessionField
{
public:
	///���͹�˾����
	CBrokerIDType	BrokerID;
	///�����û�����
	CUserIDType	UserID;
	///�����û�����
	CUserTypeType	UserType;
	///�Ự���
	CSessionIDType	SessionID;
	///ǰ�ñ��
	CFrontIDType	FrontID;
	///��¼ʱ��
	CTimeType	LoginTime;
	///IP��ַ
	CIPAddressType	IPAddress;
	///Mac��ַ
	CMacAddressType	MacAddress;
	///�û��˲�Ʒ��Ϣ
	CProductInfoType	UserProductInfo;
	///�ӿڶ˲�Ʒ��Ϣ
	CProductInfoType	InterfaceProductInfo;
	///Э����Ϣ
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_UserSession=0x3022;

///�û���¼�˳�
class CUserLogoutField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�����û�����
	CUserIDType	UserID;
	///Session�˳�ԭ��
	CNumberType	LogoutReason;
	///ǰ�ñ��
	CFrontIDType	FrontID;
	///�Ự���
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_UserLogout=0x3023;

///ϯλ
class CSeatField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///����API�е����
	CNumberType	APIID;
	///����������
	CExchangeIDType	ExchangeID;
	///��Ա���
	CParticipantIDType	ParticipantID;
	///ϯλ��
	CSeatIDType	SeatID;
	///ϯλ����
	CPasswordType	SeatPassword;
	///ϯλ����api����
	CApiLinkTypeType	ApiLinkType;
	///�Ƿ���ջر�
	CBoolType	RecvRtn;
	///ϯλ����(�Ƿ��������ϯλ�ر�)
	CBoolType	MainSeat;
	///�Ƿ��ѯ������Ϣ
	CBoolType	QueryBase;
	///�Ƿ��ѯ�ֲ�
	CBoolType	QueryPosition;
	///��ȡ�ر��ķ�ʽ
	CNumberType	ResumeType;
	///����ʱ��(��)
	CNumberType	Heartbeat;
	///�Ƿ��Ծ
	CBoolType	IsActive;
	///�Ƿ����ʽ�ֲַ��
	CBoolType	RiskCheck;
	///���ӵ�ַ
	CFrontAddrType	FrontAddr;
	///ϯλ״̬
	CSeatStatusType	SeatStatus;
	///���ر������
	COrderLocalIDType	OrderLocalID;
	///���Ӷ�Ӧ��Broker(guofu/sucden/fcstone)
	CBrokerIDType	LinkBrokerID;
	///��Ҫϯλ�����Ľ�������
	CTradingDayType	TradingDay;
	///�Ƿ���Ҫ��齻������
	CBoolType	CheckTradingDay;
	///�����Զ��������
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_Seat=0x3024;

///�û�����Ȩ��
class CUserTradingRightField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///����������
	CExchangeIDType	ExchangeID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///�û�����
	CUserIDType	UserID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///��Լ����Ȩ��
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_UserTradingRight=0x3025;

///�û������޸�
class CUserPasswordUpdateField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�����û�����
	CUserIDType	UserID;
	///������
	CPasswordType	OldPassword;
	///������
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_UserPasswordUpdate=0x3027;

///ǿ���û��˳�
class CForceUserExitField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�����û�����
	CUserIDType	UserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_ForceUserExit=0x3028;

///��½֪ͨ
class CLoginInfoField
{
public:
	///��Ա���
	CParticipantIDType	ParticipantID;
	///ϯλ����
	CSeatIDType	SeatID;
	///����������
	CExchangeIDType	ExchangeID;
	///ϯλ���ر�����
	COrderLocalIDType	OrderLocalID;
	///�������ں�
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_LoginInfo=0x3029;

///���뱨��
class CInputOrderField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///����������
	CExchangeIDType	ExchangeID;
	///ϵͳ�������
	COrderSysIDType	OrderSysID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///�û�����
	CUserIDType	UserID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///�û����ر�����
	CUserOrderLocalIDType	UserOrderLocalID;
	///�۸�����
	COrderPriceTypeType	OrderPriceType;
	///��������
	CDirectionType	Direction;
	///��ƽ��־
	COffsetFlagType	OffsetFlag;
	///Ͷ���ױ���־
	CHedgeFlagType	HedgeFlag;
	///�۸�
	CPriceType	LimitPrice;
	///����
	CVolumeType	Volume;
	///��Ч������
	CTimeConditionType	TimeCondition;
	///GTD����
	CDateType	GTDDate;
	///�ɽ�������
	CVolumeConditionType	VolumeCondition;
	///��С�ɽ���
	CVolumeType	MinVolume;
	///ֹ���
	CPriceType	StopPrice;
	///ǿƽԭ��
	CForceCloseReasonType	ForceCloseReason;
	///�Զ������־
	CBoolType	IsAutoSuspend;
	///ҵ��Ԫ
	CBusinessUnitType	BusinessUnit;
	///�û��Զ�����
	CCustomType	UserCustom;
	///Ӫҵ������
	CBranchIDType	BranchID;
	///��¼���
	CSequenceNoType	RecNum;
	///ҵ�����
	CBusinessTypeType	BusinessType;
	///������
	CTradingDayType	TradingDay;
	///��Ա���
	CParticipantIDType	ParticipantID;
	///�ͻ���
	CClientIDType	ClientID;
	///�µ�ϯλ��
	CSeatIDType	SeatID;
	///����ʱ��
	CTimeType	InsertTime;
	///���ر������
	COrderLocalIDType	OrderLocalID;
	///������Դ
	COrderSourceType	OrderSource;
	///����״̬
	COrderStatusType	OrderStatus;
	///����ʱ��
	CTimeType	CancelTime;
	///�����û����
	CUserIDType	CancelUserID;
	///��ɽ�����
	CVolumeType	VolumeTraded;
	///ʣ������
	CVolumeType	VolumeRemain;
	///ǰ�ñ��
	CFrontIDType	FrontID;
	///�Ự���
	CSessionIDType	SessionID;
	///����������
	CMoneyType	FrozenFee;
	///����ı�֤��
	CMoneyType	FrozenMargin;
	///��ȨȨ������֧
	CMoneyType	FrozenPremium;
	///�ʽ��ʺ�
	CAccountIDType	AccountID;
	///�µ��û����
	CUserIDType	OrderUserID;
	///��������
	CTradeTypeType	TradeType;
	///�����־
	CDealFlagType	DealFlag;
	///�ѳɽ�Ӷ��
	CMoneyType	TradeCommision;
	///�ɽ����
	CMoneyType	TradeAmnt;
	///��������
	CVolumeType	CancleVolume;
	///������
	CRequestIDType	RequestID;
	///ͨ����Ӧ��APIID
	CNumberType	APIID;
	///�µ�IP��ַ
	CIPAddressType	IPAddress;
	///�µ�MAC��ַ
	CMacAddressType	MacAddress;
	///Ftdengine�����²�ʱ���
	CILocalTimeType	FTdRecvDown;
	///�����²�ʱ���
	CILocalTimeType	CoreRecvDown;
	///�����ϲ�ʱ���
	CILocalTimeType	CoreSendUp;
	///�����ϲ�ʱ���
	CILocalTimeType	CoreRecvUp;
	///�����²�ʱ���
	CILocalTimeType	CoreSendDown;
	///Ftdengine�����²�ʱ���
	CILocalTimeType	FTdSendDown;
	///��֤���������
	CClientMarginCombTypeType	MarginCombType;
	///��Լ�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InputOrder=0x3030;

///��������
class COrderActionField
{
public:
	///����������
	CExchangeIDType	ExchangeID;
	///�������
	COrderSysIDType	OrderSysID;
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///�û�����
	CUserIDType	UserID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///���γ��������ı��ر��
	CUserOrderLocalIDType	UserOrderActionLocalID;
	///���������ı��ر������
	CUserOrderLocalIDType	UserOrderLocalID;
	///����������־
	CActionFlagType	ActionFlag;
	///�۸�
	CPriceType	LimitPrice;
	///�����仯
	CVolumeType	VolumeChange;
	///��¼���
	CSequenceNoType	RecNum;
	///ǰ�ñ��
	CFrontIDType	FrontID;
	///�Ự���
	CSessionIDType	SessionID;
	///�û��Զ�����
	CCustomType	UserCustom;
	///�µ�ϯλ��
	CSeatIDType	SeatID;
	///�������ر��
	COrderLocalIDType	ActionLocalID;
	///�ͻ�����
	CClientIDType	ClientID;
	///��Ա����
	CParticipantIDType	ParticipantID;
	///����ʱ��
	CTimeType	CancelTime;
	///������Դ
	CActionSourceType	ActionSource;
	///�Ƿ���Բμӽ���
	CBoolType	Tradable;
	///���ر������
	COrderLocalIDType	OrderLocalID;
	///α��Rtn
	CBoolType	IsForgeRtn;
	///ͨ����Ӧ��APIID
	CNumberType	APIID;
	///�µ�IP��ַ
	CIPAddressType	IPAddress;
	///�µ�MAC��ַ
	CMacAddressType	MacAddress;
	///������Ӧ�ı������
	COrderActionTypeType	OrderActionType;
	///�������κ�
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_OrderAction=0x3031;

///�ɽ�
class CTradeField
{
public:
	///������
	CTradingDayType	TradingDay;
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///����������
	CExchangeIDType	ExchangeID;
	///��Ա���
	CParticipantIDType	ParticipantID;
	///�µ�ϯλ��
	CSeatIDType	SeatID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///�ͻ���
	CClientIDType	ClientID;
	///�û����
	CUserIDType	UserID;
	///�ɽ����
	CTradeIDType	TradeID;
	///�������
	COrderSysIDType	OrderSysID;
	///���ر������
	CUserOrderLocalIDType	UserOrderLocalID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///��������
	CDirectionType	Direction;
	///��ƽ��־
	COffsetFlagType	OffsetFlag;
	///Ͷ���ױ���־
	CHedgeFlagType	HedgeFlag;
	///�ɽ��۸�
	CPriceType	TradePrice;
	///�ɽ�����
	CVolumeType	TradeVolume;
	///�ɽ�ʱ��
	CTimeType	TradeTime;
	///�����Ա���
	CParticipantIDType	ClearingPartID;
	///�ɽ����
	CMoneyType	TradeAmnt;
	///��¼���
	CSequenceNoType	RecNum;
	///��������
	CTradeTypeType	TradeType;
	///Ӷ��
	CMoneyType	Commision;
	///ӡ��˰
	CMoneyType	StampTax;
	///������
	CMoneyType	TransferFee;
	///������
	CMoneyType	UsedFee;
	///ռ�õı�֤��
	CMoneyType	UsedMargin;
	///ռ��Ȩ����
	CMoneyType	Premium;
	///�ʽ��ʺ�
	CAccountIDType	AccountID;
	///�µ��û����
	CUserIDType	OrderUserID;
	///���ر������
	COrderLocalIDType	OrderLocalID;
	///α��Rtn
	CBoolType	IsForgeRtn;
	///ҵ�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_Trade=0x3032;

///����
class COrderField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///����������
	CExchangeIDType	ExchangeID;
	///ϵͳ�������
	COrderSysIDType	OrderSysID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///�û�����
	CUserIDType	UserID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///�û����ر�����
	CUserOrderLocalIDType	UserOrderLocalID;
	///�۸�����
	COrderPriceTypeType	OrderPriceType;
	///��������
	CDirectionType	Direction;
	///��ƽ��־
	COffsetFlagType	OffsetFlag;
	///Ͷ���ױ���־
	CHedgeFlagType	HedgeFlag;
	///�۸�
	CPriceType	LimitPrice;
	///����
	CVolumeType	Volume;
	///��Ч������
	CTimeConditionType	TimeCondition;
	///GTD����
	CDateType	GTDDate;
	///�ɽ�������
	CVolumeConditionType	VolumeCondition;
	///��С�ɽ���
	CVolumeType	MinVolume;
	///ֹ���
	CPriceType	StopPrice;
	///ǿƽԭ��
	CForceCloseReasonType	ForceCloseReason;
	///�Զ������־
	CBoolType	IsAutoSuspend;
	///ҵ��Ԫ
	CBusinessUnitType	BusinessUnit;
	///�û��Զ�����
	CCustomType	UserCustom;
	///Ӫҵ������
	CBranchIDType	BranchID;
	///��¼���
	CSequenceNoType	RecNum;
	///ҵ�����
	CBusinessTypeType	BusinessType;
	///������
	CTradingDayType	TradingDay;
	///��Ա���
	CParticipantIDType	ParticipantID;
	///�ͻ���
	CClientIDType	ClientID;
	///�µ�ϯλ��
	CSeatIDType	SeatID;
	///����ʱ��
	CTimeType	InsertTime;
	///���ر������
	COrderLocalIDType	OrderLocalID;
	///������Դ
	COrderSourceType	OrderSource;
	///����״̬
	COrderStatusType	OrderStatus;
	///����ʱ��
	CTimeType	CancelTime;
	///�����û����
	CUserIDType	CancelUserID;
	///��ɽ�����
	CVolumeType	VolumeTraded;
	///ʣ������
	CVolumeType	VolumeRemain;
	///ǰ�ñ��
	CFrontIDType	FrontID;
	///�Ự���
	CSessionIDType	SessionID;
	///����������
	CMoneyType	FrozenFee;
	///����ı�֤��
	CMoneyType	FrozenMargin;
	///��ȨȨ������֧
	CMoneyType	FrozenPremium;
	///�ʽ��ʺ�
	CAccountIDType	AccountID;
	///�µ��û����
	CUserIDType	OrderUserID;
	///��������
	CTradeTypeType	TradeType;
	///�����־
	CDealFlagType	DealFlag;
	///�ѳɽ�Ӷ��
	CMoneyType	TradeCommision;
	///�ɽ����
	CMoneyType	TradeAmnt;
	///��������
	CVolumeType	CancleVolume;
	///������
	CRequestIDType	RequestID;
	///ͨ����Ӧ��APIID
	CNumberType	APIID;
	///�µ�IP��ַ
	CIPAddressType	IPAddress;
	///�µ�MAC��ַ
	CMacAddressType	MacAddress;
	///Ftdengine�����²�ʱ���
	CILocalTimeType	FTdRecvDown;
	///�����²�ʱ���
	CILocalTimeType	CoreRecvDown;
	///�����ϲ�ʱ���
	CILocalTimeType	CoreSendUp;
	///�����ϲ�ʱ���
	CILocalTimeType	CoreRecvUp;
	///�����²�ʱ���
	CILocalTimeType	CoreSendDown;
	///Ftdengine�����²�ʱ���
	CILocalTimeType	FTdSendDown;
	///��֤���������
	CClientMarginCombTypeType	MarginCombType;
	///��Լ�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_Order=0x3033;

///�г�����
class CMarketDataField
{
public:
	///������
	CTradingDayType	TradingDay;
	///����������
	CExchangeIDType	ExchangeID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///����
	CPriceType	OpenPrice;
	///��߼�
	CPriceType	HighestPrice;
	///��ͼ�
	CPriceType	LowestPrice;
	///���¼�
	CPriceType	LastPrice;
	///����
	CVolumeType	Volume;
	///�ɽ����
	CMoneyType	Turnover;
	///��ͣ���
	CPriceType	LowerLimitPrice;
	///��ͣ���
	CPriceType	UpperLimitPrice;
	///�ֲ���
	CVolumeType	OpenInterest;
	///������
	CPriceType	PreClosePrice;
	///��ֲ���
	CVolumeType	PreOpenInterest;
	///�����
	CPriceType	PreSettlementPrice;
	///�����
	CPriceType	SettlementPrice;
	///����޸ĺ���
	CMillisecType	UpdateMillisec;
	///����޸�ʱ��
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_MarketData=0x3034;

///�������³ɽ�����
class CMarketDataLastMatchField
{
public:
	///����������
	CExchangeIDType	ExchangeID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///���¼�
	CPriceType	LastPrice;
	///����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_MarketDataLastMatch=0x3035;

///�г��������
class CDepthMarketDataField
{
public:
	///������
	CTradingDayType	TradingDay;
	///���������
	CSettlementGroupIDType	SettlementGroupID;
	///������
	CSettlementIDType	SettlementID;
	///�����
	CPriceType	PreSettlementPrice;
	///������
	CPriceType	PreClosePrice;
	///��ֲ���
	CLargeVolumeType	PreOpenInterest;
	///����ʵ��
	CRatioType	PreDelta;
	///����
	CPriceType	OpenPrice;
	///��߼�
	CPriceType	HighestPrice;
	///��ͼ�
	CPriceType	LowestPrice;
	///������
	CPriceType	ClosePrice;
	///��ͣ���
	CPriceType	UpperLimitPrice;
	///��ͣ���
	CPriceType	LowerLimitPrice;
	///�����
	CPriceType	SettlementPrice;
	///����ʵ��
	CRatioType	CurrDelta;
	///���¼�
	CPriceType	LastPrice;
	///����
	CVolumeType	Volume;
	///�ɽ����
	CMoneyType	Turnover;
	///�ֲ���
	CLargeVolumeType	OpenInterest;
	///�����һ
	CPriceType	BidPrice1;
	///������һ
	CVolumeType	BidVolume1;
	///������һ
	CPriceType	AskPrice1;
	///������һ
	CVolumeType	AskVolume1;
	///����۶�
	CPriceType	BidPrice2;
	///��������
	CVolumeType	BidVolume2;
	///�������
	CPriceType	BidPrice3;
	///��������
	CVolumeType	BidVolume3;
	///�����۶�
	CPriceType	AskPrice2;
	///��������
	CVolumeType	AskVolume2;
	///��������
	CPriceType	AskPrice3;
	///��������
	CVolumeType	AskVolume3;
	///�������
	CPriceType	BidPrice4;
	///��������
	CVolumeType	BidVolume4;
	///�������
	CPriceType	BidPrice5;
	///��������
	CVolumeType	BidVolume5;
	///��������
	CPriceType	AskPrice4;
	///��������
	CVolumeType	AskVolume4;
	///��������
	CPriceType	AskPrice5;
	///��������
	CVolumeType	AskVolume5;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///����޸�ʱ��
	CTimeType	UpdateTime;
	///����޸ĺ���
	CMillisecType	UpdateMillisec;
	///����������
	CExchangeIDType	ExchangeID;
	///��������
	CPriceType	AskPrice6;
	///��������
	CVolumeType	AskVolume6;
	///��������
	CPriceType	AskPrice7;
	///��������
	CVolumeType	AskVolume7;
	///�����۰�
	CPriceType	AskPrice8;
	///��������
	CVolumeType	AskVolume8;
	///�����۾�
	CPriceType	AskPrice9;
	///��������
	CVolumeType	AskVolume9;
	///�������
	CPriceType	BidPrice6;
	///��������
	CVolumeType	BidVolume6;
	///�������
	CPriceType	BidPrice7;
	///��������
	CVolumeType	BidVolume7;
	///����۰�
	CPriceType	BidPrice8;
	///��������
	CVolumeType	BidVolume8;
	///����۾�
	CPriceType	BidPrice9;
	///��������
	CVolumeType	BidVolume9;
	///������ʮ
	CPriceType	AskPrice10;
	///������ʮ
	CVolumeType	AskVolume10;
	///�����ʮ
	CPriceType	BidPrice10;
	///������ʮ
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_DepthMarketData=0x3036;

///�����ѯӦ��
class CRspMarketDataField
{
public:
	///����������
	CExchangeIDType	ExchangeID;
	///������
	CTradingDayType	TradingDay;
	///���������
	CSettlementGroupIDType	SettlementGroupID;
	///������
	CSettlementIDType	SettlementID;
	///�����
	CPriceType	PreSettlementPrice;
	///������
	CPriceType	PreClosePrice;
	///��ֲ���
	CLargeVolumeType	PreOpenInterest;
	///����ʵ��
	CRatioType	PreDelta;
	///����
	CPriceType	OpenPrice;
	///��߼�
	CPriceType	HighestPrice;
	///��ͼ�
	CPriceType	LowestPrice;
	///������
	CPriceType	ClosePrice;
	///��ͣ���
	CPriceType	UpperLimitPrice;
	///��ͣ���
	CPriceType	LowerLimitPrice;
	///�����
	CPriceType	SettlementPrice;
	///����ʵ��
	CRatioType	CurrDelta;
	///���¼�
	CPriceType	LastPrice;
	///����
	CVolumeType	Volume;
	///�ɽ����
	CMoneyType	Turnover;
	///�ֲ���
	CLargeVolumeType	OpenInterest;
	///�����һ
	CPriceType	BidPrice1;
	///������һ
	CVolumeType	BidVolume1;
	///������һ
	CPriceType	AskPrice1;
	///������һ
	CVolumeType	AskVolume1;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///����޸�ʱ��
	CTimeType	UpdateTime;
	///����޸ĺ���
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_RspMarketData=0x3037;

///������ѯ
class CQryOrderField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�û�����
	CUserIDType	UserID;
	///����������
	CExchangeIDType	ExchangeID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///�������
	COrderSysIDType	OrderSysID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///��¼���͹�˾���
	CBrokerIDType	LogBrokerID;
	///��¼�û�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryOrder=0x3040;

///����ѯ
class CQryOrderInsertFailedField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�û�����
	CUserIDType	UserID;
	///����������
	CExchangeIDType	ExchangeID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///�������
	COrderSysIDType	OrderSysID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///��¼���͹�˾���
	CBrokerIDType	LogBrokerID;
	///��¼�û�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryOrderInsertFailed=0x3041;

///�ɽ���ѯ
class CQryTradeField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�û�����
	CUserIDType	UserID;
	///����������
	CExchangeIDType	ExchangeID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///�ɽ����
	CTradeIDType	TradeID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///��¼���͹�˾���
	CBrokerIDType	LogBrokerID;
	///��¼�û�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryTrade=0x3042;

///Ͷ���߲�ѯ
class CQryInvestorField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�û�����
	CUserIDType	UserID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///��¼���͹�˾���
	CBrokerIDType	LogBrokerID;
	///��¼�û�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInvestor=0x3043;

///Ͷ�����ʽ��ѯ
class CQryInvestorAccountField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�û�����
	CUserIDType	UserID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///��¼���͹�˾���
	CBrokerIDType	LogBrokerID;
	///��¼�û�����
	CUserIDType	LogUserID;
	///ϯλ��
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInvestorAccount=0x3044;

///��Լ��ѯ
class CQryInstrumentField
{
public:
	///����������
	CExchangeIDType	ExchangeID;
	///Ʒ�ִ���
	CProductIDType	ProductID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(ProductID)
		,
		TYPE_DESC(InstrumentID)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInstrument=0x3045;

///�û���ѯ
class CQryUserField
{
public:
	///�����û�����
	CUserIDType	StartUserID;
	///�����û�����
	CUserIDType	EndUserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(StartUserID)
		,
		TYPE_DESC(EndUserID)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryUser=0x3046;

///Ͷ���ֲ߳�����
class CQryInvestorPositionField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�û�����
	CUserIDType	UserID;
	///����������
	CExchangeIDType	ExchangeID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///�ͻ���
	CClientIDType	ClientID;
	///ϯλ��
	CSeatIDType	SeatID;
	///��¼���͹�˾���
	CBrokerIDType	LogBrokerID;
	///��¼�û�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInvestorPosition=0x3047;

///����Ͷ�����˻���ѯ
class CQryUserInvestorField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�û�����
	CUserIDType	UserID;
	///��¼���͹�˾���
	CBrokerIDType	LogBrokerID;
	///��¼�û�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryUserInvestor=0x3049;

///��������ѯ
class CQryExchangeField
{
public:
	///����������
	CExchangeIDType	ExchangeID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryExchange=0x304B;

///��Ӧ��Ϣ
class CRspInfoField
{
public:
	///�������
	CErrorIDType	ErrorID;
	///������Ϣ
	CErrorMsgType	ErrorMsg;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ErrorID)
		,
		TYPE_DESC(ErrorMsg)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_RspInfo=0x304D;

///������Ӧ��
class CRspExchangeField
{
public:
	///������
	CTradingDayType	TradingDay;
	///����������
	CExchangeIDType	ExchangeID;
	///����������
	CExchangeNameType	ExchangeName;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(ExchangeName)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_RspExchange=0x304E;

///�����ѯ
class CQryMarketDataField
{
public:
	///����������
	CExchangeIDType	ExchangeID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
		,
		TYPE_DESC(InstrumentID)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryMarketData=0x304F;

///Ͷ�����������ʲ�ѯ
class CQryInvestorFeeField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�û�����
	CUserIDType	UserID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///����������
	CExchangeIDType	ExchangeID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///Ͷ���ױ���־
	CHedgeFlagType	HedgeFlag;
	///��¼���͹�˾���
	CBrokerIDType	LogBrokerID;
	///��¼�û�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInvestorFee=0x3050;

///Ͷ���߱�֤���ʲ�ѯ
class CQryInvestorMarginField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�û�����
	CUserIDType	UserID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///����������
	CExchangeIDType	ExchangeID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///Ͷ���ױ���־
	CHedgeFlagType	HedgeFlag;
	///��¼���͹�˾���
	CBrokerIDType	LogBrokerID;
	///��¼�û�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInvestorMargin=0x3051;

///�������ӷ��ʲ�ѯ����
class CQrySGEDeferRateField
{
public:
	///��Լ����
	CInstrumentIDType	InstrumentID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(InstrumentID)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QrySGEDeferRate=0x3066;

///�������ӷ��ʲ�ѯӦ��
class CSGEDeferRateField
{
public:
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///����������
	CExchangeIDType	ExchangeID;
	///��������
	CTradingDayType	TradeDate;
	///֧������
	CPayDirectionType	Direction;
	///���ӷ���
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_SGEDeferRate=0x3067;

///ͨѶ�׶�
class CCommPhaseField
{
public:
	///������
	CDateType	TradingDay;
	///ͨѶʱ�κ�
	CCommPhaseNoType	CommPhaseNo;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(CommPhaseNo)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_CommPhase=0x3060;

///������
class CTradingDayField
{
public:
	///������
	CTradingDayType	TradingDay;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_TradingDay=0x3061;

///��ǰʱ��
class CCurrentTimeField
{
public:
	///��ǰ����
	CDateType	CurrDate;
	///��ǰʱ��
	CTimeType	CurrTime;
	///��ǰʱ�䣨���룩
	CMillisecType	CurrMillisec;
	TYPE_DESCRIPTOR((
		TYPE_DESC(CurrDate)
		,
		TYPE_DESC(CurrTime)
		,
		TYPE_DESC(CurrMillisec)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_CurrentTime=0x3062;

///�������ں�
class CLifeCycleIDField
{
public:
	///�������ں�
	CSequenceNoType	LifeCycleID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(LifeCycleID)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_LifeCycleID=0x3063;

///�ڴ����
class CMemDbField
{
public:
	///�ڴ����
	CMemTableNameType	MemTableName;
	TYPE_DESCRIPTOR((
		TYPE_DESC(MemTableName)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_MemDb=0x3064;

///ϵͳ״̬
class CSystemStatusField
{
public:
	///������
	CDateType	TradingDay;
	///ϵͳ״̬
	CSystemStatusType	SystemStatus;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(SystemStatus)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_SystemStatus=0x3065;

///ϵͳ����ͬ��״̬
class CDataSyncStatusField
{
public:
	///������
	CDateType	TradingDay;
	///����ͬ��״̬
	CDataSyncStatusType	DataSyncStatus;
	///QDPϵͳ���
	CSystemIDType	SystemID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(DataSyncStatus)
		,
		TYPE_DESC(SystemID)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_DataSyncStatus=0x3070;

///DbmtͶ�����ʽ��ʻ����
class CDbmtInvestorAccountDepositField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�ʽ���ˮ��
	CAccountSeqNoType	AccountSeqNo;
	///�ʽ��ʺ�
	CAccountIDType	AccountID;
	///�������������ʽ���ˮ��
	CAccountSeqNoType	AccountInsideSeqNo;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///���
	CMoneyType	Amount;
	///�������
	CAccountDirectionType	AmountDirection;
	///Dbmt�����
	CDbmtTopicIDType	DbmtTopicID;
	///Dbmt���к�
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_DbmtInvestorAccountDeposit=0x3071;

///Dbmt�û�
class CDbmtUserField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�û�����
	CUserIDType	UserID;
	///�û���¼����
	CPasswordType	Password;
	///�Ƿ��Ծ
	CIsActiveType	IsActive;
	///�û�����
	CUserNameType	UserName;
	///�û�����
	CUserTypeType	UserType;
	///Ӫҵ��
	CDepartmentType	Department;
	///��Ȩ���ܼ�
	CGrantFuncSetType	GrantFuncSet;
	///�Ƿ���IP��MAC
	CBoolType	CheckIpMacAddr;
	///Dbmt�����
	CDbmtTopicIDType	DbmtTopicID;
	///Dbmt���к�
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_DbmtUser=0x3072;

///�ڴ��仯
class CMemtableChangeField
{
public:
	///�ڴ��仯����
	CMemtableChangeTypeType	MemtableChangeType;
	///�ڴ����
	CMemTableNameType	MemTableName;
	TYPE_DESCRIPTOR((
		TYPE_DESC(MemtableChangeType)
		,
		TYPE_DESC(MemTableName)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_MemtableChange=0x3073;

///������������
class CExchangeTradingDayField
{
public:
	///������
	CTradingDayType	TradingDay;
	///����������
	CExchangeIDType	ExchangeID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TradingDay)
		,
		TYPE_DESC(ExchangeID)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_ExchangeTradingDay=0x3081;

///�����ر�֪ͨ
class CInvestorAccountDepositNtfField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///�ʽ��ʺ�
	CAccountIDType	AccountID;
	///�ʽ���ˮ��
	CAccountSeqNoType	AccountSeqNo;
	///�������������ʽ���ˮ��
	CAccountSeqNoType	AccountInsideSeqNo;
	///���
	CMoneyType	Amount;
	///�������
	CAccountDirectionType	AmountDirection;
	///�����ʽ�
	CMoneyType	Available;
	///����׼����
	CMoneyType	Balance;
	///�û�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorAccountDepositNtf=0x3085;

///����
class COrderInsertFailedField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///����������
	CExchangeIDType	ExchangeID;
	///ϵͳ�������
	COrderSysIDType	OrderSysID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///�û�����
	CUserIDType	UserID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///�û����ر�����
	CUserOrderLocalIDType	UserOrderLocalID;
	///�۸�����
	COrderPriceTypeType	OrderPriceType;
	///��������
	CDirectionType	Direction;
	///��ƽ��־
	COffsetFlagType	OffsetFlag;
	///Ͷ���ױ���־
	CHedgeFlagType	HedgeFlag;
	///�۸�
	CPriceType	LimitPrice;
	///����
	CVolumeType	Volume;
	///��Ч������
	CTimeConditionType	TimeCondition;
	///GTD����
	CDateType	GTDDate;
	///�ɽ�������
	CVolumeConditionType	VolumeCondition;
	///��С�ɽ���
	CVolumeType	MinVolume;
	///ֹ���
	CPriceType	StopPrice;
	///ǿƽԭ��
	CForceCloseReasonType	ForceCloseReason;
	///�Զ������־
	CBoolType	IsAutoSuspend;
	///ҵ��Ԫ
	CBusinessUnitType	BusinessUnit;
	///�û��Զ�����
	CCustomType	UserCustom;
	///Ӫҵ������
	CBranchIDType	BranchID;
	///��¼���
	CSequenceNoType	RecNum;
	///ҵ�����
	CBusinessTypeType	BusinessType;
	///������
	CTradingDayType	TradingDay;
	///��Ա���
	CParticipantIDType	ParticipantID;
	///�ͻ���
	CClientIDType	ClientID;
	///�µ�ϯλ��
	CSeatIDType	SeatID;
	///����ʱ��
	CTimeType	InsertTime;
	///���ر������
	COrderLocalIDType	OrderLocalID;
	///������Դ
	COrderSourceType	OrderSource;
	///����״̬
	COrderStatusType	OrderStatus;
	///����ʱ��
	CTimeType	CancelTime;
	///�����û����
	CUserIDType	CancelUserID;
	///��ɽ�����
	CVolumeType	VolumeTraded;
	///ʣ������
	CVolumeType	VolumeRemain;
	///ǰ�ñ��
	CFrontIDType	FrontID;
	///�Ự���
	CSessionIDType	SessionID;
	///����������
	CMoneyType	FrozenFee;
	///����ı�֤��
	CMoneyType	FrozenMargin;
	///��ȨȨ������֧
	CMoneyType	FrozenPremium;
	///�ʽ��ʺ�
	CAccountIDType	AccountID;
	///�µ��û����
	CUserIDType	OrderUserID;
	///��������
	CTradeTypeType	TradeType;
	///�����־
	CDealFlagType	DealFlag;
	///�ѳɽ�Ӷ��
	CMoneyType	TradeCommision;
	///�ɽ����
	CMoneyType	TradeAmnt;
	///��������
	CVolumeType	CancleVolume;
	///������
	CRequestIDType	RequestID;
	///ͨ����Ӧ��APIID
	CNumberType	APIID;
	///�µ�IP��ַ
	CIPAddressType	IPAddress;
	///�µ�MAC��ַ
	CMacAddressType	MacAddress;
	///Ftdengine�����²�ʱ���
	CILocalTimeType	FTdRecvDown;
	///�����²�ʱ���
	CILocalTimeType	CoreRecvDown;
	///�����ϲ�ʱ���
	CILocalTimeType	CoreSendUp;
	///�����ϲ�ʱ���
	CILocalTimeType	CoreRecvUp;
	///�����²�ʱ���
	CILocalTimeType	CoreSendDown;
	///Ftdengine�����²�ʱ���
	CILocalTimeType	FTdSendDown;
	///��֤���������
	CClientMarginCombTypeType	MarginCombType;
	///��Լ�����
	CInstrumentGroupIDType	InstrumentGroupID;
	///������Ϣ
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_OrderInsertFailed=0x3086;

///��Լ�ͺ�Լ���ϵ
class CInstrumentGroupField
{
public:
	///����������
	CExchangeIDType	ExchangeID;
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///��Լ�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InstrumentGroup=0x3088;

///���ױ�����ϱ�֤������
class CClientMarginCombTypeField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///��Ա����
	CParticipantIDType	ParticipantID;
	///�ͻ�����
	CClientIDType	ClientID;
	///��Լ�����
	CInstrumentGroupIDType	InstrumentGroupID;
	///��֤���������
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_ClientMarginCombType=0x3089;

///��¼��Ϣ
class CInterLoginInfoField
{
public:
	///IP��ַ
	CServerAddrType	ServerAddr;
	///��󱾵ر�����
	CSequenceNoType	MaxLocalID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ServerAddr)
		,
		TYPE_DESC(MaxLocalID)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InterLoginInfo=0x3096;

///QDP������Ϣ֪ͨ
class CMessageNotifyInfoField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�޸��û����
	CUserIDType	UserID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///����������
	CExchangeIDType	ExchangeID;
	///�ۼӴ���
	CTotalNumsType	Nums;
	///ҵ�����
	CBusinessTypeType	BusinessType;
	///������Ϣ
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_MessageNotifyInfo=0x3097;

///���������
class CAccountDepositField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�ʽ���ˮ��
	CAccountSeqNoType	AccountSeqNo;
	///�ʽ��ʺ�
	CAccountIDType	AccountID;
	///�������������ʽ���ˮ��
	CAccountSeqNoType	AccountInsideSeqNo;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///���
	CMoneyType	Amount;
	///�������
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_AccountDeposit=0x3098;

///�����Ӧ��
class CAccountDepositResField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///�ʽ��ʺ�
	CAccountIDType	AccountID;
	///�ʽ���ˮ��
	CAccountSeqNoType	AccountSeqNo;
	///�������������ʽ���ˮ��
	CAccountSeqNoType	AccountInsideSeqNo;
	///���
	CMoneyType	Amount;
	///�������
	CAccountDirectionType	AmountDirection;
	///�����ʽ�
	CMoneyType	Available;
	///����׼����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_AccountDepositRes=0x3099;

///���̻���ѯ������Ϣ֪ͨ
class CQueryFinishNotifyField
{
public:
	///������
	CTradingDayType	TradingDay;
	///����������
	CExchangeIDType	ExchangeID;
	///��󱾵ر�����
	COrderLocalIDType	MaxOrderLocalID;
	///ͨ����Ӧ��APIID
	CNumberType	APIID;
	///ϯλ����api����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QueryFinishNotify=0x3100;

///Dbmt�ͻ����ױ��뽻��Ȩ��
class CDbmtClientTradingIDField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///�ʽ��ʺ�
	CAccountIDType	AccountID;
	///����������
	CExchangeIDType	ExchangeID;
	///��Ա���
	CParticipantIDType	ParticipantID;
	///�ͻ�����
	CClientIDType	ClientID;
	///�ͻ�����Ȩ��
	CTradingRightType	ClientRight;
	///�ͻ�����
	CClientTypeType	ClientType;
	///�ͻ���ֵ����
	CHedgeFlagType	ClientHedgeFlag;
	///�Ƿ��Ծ
	CIsActiveType	IsActive;
	///ͨ����Ӧ��APIID
	CNumberType	APIID;
	///Dbmt�����
	CDbmtTopicIDType	DbmtTopicID;
	///Dbmt���к�
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_DbmtClientTradingID=0x3109;

///��Ϻ�Լ��ϸ
class CCmbInstrumentDetailField
{
public:
	///����������
	CExchangeIDType	ExchangeID;
	///��Ϻ�Լ����
	CInstrumentIDType	ArbiInstrumentID;
	///���Ⱥ�Լ����
	CInstrumentIDType	SingleInstrumentID;
	///��Ϻ�Լ�ȵ�����
	CNumberType	LegNo;
	///��������
	CDirectionType	Direction;
	///��������
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_CmbInstrumentDetail=0x3102;

///�ڲ���½��Ϣ
class CInnerLoginField
{
public:
	///���յ����������
	CSequenceNoType	SequenceNo;
	TYPE_DESCRIPTOR((
		TYPE_DESC(SequenceNo)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InnerLogin=0x3111;

///Ͷ���߽���Ȩ��
class CInvestorTradingRightField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///����������
	CExchangeIDType	ExchangeID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///��Լ����Ȩ��
	CTradingRightType	TradingRight;
	///��Ʒ����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorTradingRight=0x3112;

///DbmtͶ����Ȩ��
class CDbmtInvestorTradingRightField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///����������
	CExchangeIDType	ExchangeID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///��Լ����Ȩ��
	CTradingRightType	TradingRight;
	///��Ʒ����
	CProductClassType	ProductClass;
	///Dbmt�����
	CDbmtTopicIDType	DbmtTopicID;
	///Dbmt���к�
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_DbmtInvestorTradingRight=0x3113;

///�û�IP
class CUserIPField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�����û�����
	CUserIDType	UserID;
	///IP��ַ
	CIPAddressType	IPAddress;
	///IP��ַ����
	CIPAddressType	IPMask;
	///MAC��ַ
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_UserIP=0x3114;

///Dbmt�û�IP
class CDbmtUserIPField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�����û�����
	CUserIDType	UserID;
	///IP��ַ
	CIPAddressType	IPAddress;
	///IP��ַ����
	CIPAddressType	IPMask;
	///MAC��ַ
	CMacAddressType	MacAddress;
	///Dbmt�����
	CDbmtTopicIDType	DbmtTopicID;
	///Dbmt���к�
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_DbmtUserIP=0x3115;

///Ͷ���ֲ߳���ϸ��ѯ����
class CQryInvestorPositionDetailField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///����������
	CExchangeIDType	ExchangeID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///���Ⱥ�Լ����
	CInstrumentIDType	InstrumentID;
	///��¼���͹�˾���
	CBrokerIDType	LogBrokerID;
	///��¼�û�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInvestorPositionDetail=0x3116;

///Ͷ���ֲ߳���ϸӦ��
class CRspInvestorPositionDetailField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///����������
	CExchangeIDType	ExchangeID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///Ͷ���ױ���־
	CHedgeFlagType	HedgeFlag;
	///��������
	CDirectionType	Direction;
	///��������
	CDateType	OpenDate;
	///�ɽ����
	CTradeIDType	TradeID;
	///����
	CVolumeType	Volume;
	///���ּ�
	CMoneyType	OpenPrice;
	///������
	CDateType	TradingDay;
	///��������
	CTradeTypeType	TradeType;
	///��Ϻ�Լ����
	CInstrumentIDType	CombInstrumentID;
	///���ն���ƽ��ӯ��
	CMoneyType	CloseProfitByDate;
	///��ʶԳ�ƽ��ӯ��
	CMoneyType	CloseProfitByTrade;
	///���ն��гֲ�ӯ��
	CMoneyType	PositionProfitByDate;
	///��ʶԳ�ֲ�ӯ��
	CMoneyType	PositionProfitByTrade;
	///Ͷ���߱�֤��
	CMoneyType	Margin;
	///��������֤��
	CMoneyType	ExchMargin;
	///��֤����
	CMoneyType	MarginRateByMoney;
	///��֤����(������)
	CMoneyType	MarginRateByVolume;
	///������
	CPriceType	LastSettlementPrice;
	///�����
	CPriceType	SettlementPrice;
	///ƽ����
	CVolumeType	CloseVolume;
	///ƽ�ֽ��
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_RspInvestorPositionDetail=0x3117;

///Ͷ���ֲ߳���ϸ
class CInvestorPositionDetailField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///����������
	CExchangeIDType	ExchangeID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///Ͷ���ױ���־
	CHedgeFlagType	HedgeFlag;
	///��������
	CDirectionType	Direction;
	///��������
	CDateType	OpenDate;
	///�ɽ����
	CTradeIDType	TradeID;
	///����
	CVolumeType	Volume;
	///���ּ�
	CMoneyType	OpenPrice;
	///������
	CDateType	TradingDay;
	///��������
	CTradeTypeType	TradeType;
	///��Ϻ�Լ����
	CInstrumentIDType	CombInstrumentID;
	///���ն���ƽ��ӯ��
	CMoneyType	CloseProfitByDate;
	///��ʶԳ�ƽ��ӯ��
	CMoneyType	CloseProfitByTrade;
	///���ն��гֲ�ӯ��
	CMoneyType	PositionProfitByDate;
	///��ʶԳ�ֲ�ӯ��
	CMoneyType	PositionProfitByTrade;
	///Ͷ���߱�֤��
	CMoneyType	Margin;
	///��������֤��
	CMoneyType	ExchMargin;
	///��֤����
	CMoneyType	MarginRateByMoney;
	///��֤����(������)
	CMoneyType	MarginRateByVolume;
	///������
	CPriceType	LastSettlementPrice;
	///�����
	CPriceType	SettlementPrice;
	///ƽ����
	CVolumeType	CloseVolume;
	///ƽ�ֽ��
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorPositionDetail=0x3118;

///Ͷ������Ȩ�����Ѳ�ѯ����
class CQryInvestorOptionFeeField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�û�����
	CUserIDType	UserID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///����������
	CExchangeIDType	ExchangeID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///��¼���͹�˾���
	CBrokerIDType	LogBrokerID;
	///��¼�û�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_QryInvestorOptionFee=0x3121;

///Ͷ������Ȩ������
class CInvestorOptionFeeField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///����������
	CExchangeIDType	ExchangeID;
	///Ͷ���߱���
	CInvestorIDType	InvestorID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///���������Ѱ�����
	CRatioType	OpenFeeRate;
	///���������Ѱ�����
	CRatioType	OpenFeeAmt;
	///ƽ�������Ѱ�����
	CRatioType	OffsetFeeRate;
	///ƽ�������Ѱ�����
	CRatioType	OffsetFeeAmt;
	///ƽ��������Ѱ�����
	CRatioType	OTFeeRate;
	///ƽ��������Ѱ�����
	CRatioType	OTFeeAmt;
	///ִ�������Ѱ�����
	CRatioType	StrikeFeeRate;
	///ִ�������Ѱ�����
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
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_InvestorOptionFee=0x3122;

///Ͷ���ֲ߳�ӯ��
class CPositionProfitField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///Ͷ���߱��
	CInvestorIDType	InvestorID;
	///�ֲ�ӯ��
	CMoneyType	PositionProfit;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(InvestorID)
		,
		TYPE_DESC(PositionProfit)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_PositionProfit=0x3123;

///QDPϵͳ��Ϣ
class CSystemInfoField
{
public:
	///QDPϵͳ���
	CSystemIDType	SystemID;
	///QDPϵͳ����
	CSystemNameType	SystemName;
	///QDPϵͳIP��ַ
	CIPAddressType	SystemIP;
	TYPE_DESCRIPTOR((
		TYPE_DESC(SystemID)
		,
		TYPE_DESC(SystemName)
		,
		TYPE_DESC(SystemIP)
	));
	
	///����field�����buffer�У�buffer����Ϊlen��������Ȳ����������þ��������ԭ��
	///@param	buffer	Ҫ���ý���Ļ�����
	///@param	len	�������ĳ���
	///@return	true��ʾȫ���ųɹ���false��ʾû��ȫ���ųɹ���
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_SystemInfo=0x3124;




#endif
