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

///ϵͳ�û���¼����
class CFTDReqUserLoginField
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

///ϵͳ�û���¼Ӧ��
class CFTDRspUserLoginField
{
public:
	///������
	CDateType	TradingDay;
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�����û�����
	CUserIDType	UserID;
	///��¼�ɹ�ʱ��
	CTimeType	LoginTime;
	///�û���󱾵ر�����
	CUserOrderLocalIDType	MaxOrderLocalID;
	///����ϵͳ����
	CTradingSystemNameType	TradingSystemName;
	///�������Ĵ���
	CDataCenterIDType	DataCenterID;
	///��Ա˽������ǰ����
	CSequenceNoType	PrivateFlowSize;
	///����Ա˽������ǰ����
	CSequenceNoType	UserFlowSize;
	///�Ự���
	CSessionIDType	SessionID;
	///ǰ�ñ��
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

///�û��ǳ�����
class CFTDReqUserLogoutField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�����û�����
	CUserIDType	UserID;
	///Session�˳�ԭ��
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

///�û��ǳ�����
class CFTDRspUserLogoutField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�����û�����
	CUserIDType	UserID;
	///Session�˳�ԭ��
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

///ǿ���û��˳�
class CFTDForceUserExitField
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
};
const DWORD FTD_FID_ForceUserExit=0x3005;

///�û������޸�
class CFTDUserPasswordUpdateField
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
};
const DWORD FTD_FID_UserPasswordUpdate=0x3006;

///���뱨��
class CFTDInputOrderField
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

///��������
class CFTDOrderActionField
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

///�ڴ����
class CFTDMemDbField
{
public:
	///�ڴ����
	CMemTableNameType	MemTableName;
	TYPE_DESCRIPTOR((
		TYPE_DESC(MemTableName)
	));
};
const DWORD FTD_FID_MemDb=0x3009;

///Ͷ�����ʽ��ʻ����������
class CFTDReqAccountDepositField
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
	///�û�����
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

///Ͷ�����ʽ��ʻ������Ӧ��
class CFTDRspAccountDepositField
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
};
const DWORD FTD_FID_RspAccountDeposit=0x3011;

///��Ӧ��Ϣ
class CFTDRspInfoField
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
};
const DWORD FTD_FID_RspInfo=0x3001;

///������ѯ
class CFTDQryOrderField
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

///�ɽ���ѯ
class CFTDQryTradeField
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

///��Լ��ѯ
class CFTDQryInstrumentField
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
};
const DWORD FTD_FID_QryInstrument=0x300C;

///��Լ��ѯӦ��
class CFTDRspInstrumentField
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

///��Լ״̬
class CFTDInstrumentStatusField
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

///Ͷ�����ʽ��ѯ
class CFTDQryInvestorAccountField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�û�����
	CUserIDType	UserID;
	///Ͷ���߱��
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

///Ͷ�����ʽ�Ӧ��
class CFTDRspInvestorAccountField
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

///����Ͷ���߲�ѯ
class CFTDQryUserInvestorField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�û�����
	CUserIDType	UserID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(BrokerID)
		,
		TYPE_DESC(UserID)
	));
};
const DWORD FTD_FID_QryUserInvestor=0x3011;

///����Ͷ����Ӧ��
class CFTDRspUserInvestorField
{
public:
	///���͹�˾���
	CBrokerIDType	BrokerID;
	///�����û�����
	CUserIDType	UserID;
	///Ͷ���߱��
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

///���ױ����ѯ
class CFTDQryTradingCodeField
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

///���ױ����ѯ
class CFTDRspTradingCodeField
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

///��������ѯ����
class CFTDQryExchangeField
{
public:
	///����������
	CExchangeIDType	ExchangeID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
	));
};
const DWORD FTD_FID_QryExchange=0x3015;

///��������ѯӦ��
class CFTDRspExchangeField
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
};
const DWORD FTD_FID_RspExchange=0x3016;

///Ͷ���ֲֲ߳�ѯ����
class CFTDQryInvestorPositionField
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

///Ͷ���ֲֲ߳�ѯӦ��
class CFTDRspInvestorPositionField
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

///�û���ѯ
class CFTDQryUserField
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
};
const DWORD FTD_FID_QryUser=0x301B;

///�û�
class CFTDUserField
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
};
const DWORD FTD_FID_User=0x301C;

///Ͷ�����������ʲ�ѯ
class CFTDQryInvestorFeeField
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

///Ͷ������������
class CFTDInvestorFeeField
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
};
const DWORD FTD_FID_InvestorFee=0x301E;

///Ͷ���߱�֤���ʲ�ѯ
class CFTDQryInvestorMarginField
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

///Ͷ���߱�֤����
class CFTDInvestorMarginField
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
};
const DWORD FTD_FID_InvestorMargin=0x3020;

///ʵʱ�����ѯ����
class CFTDQryMarketDataField
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
};
const DWORD FTD_FID_QryMarketData=0x3054;

///ʵʱ�����ѯӦ��
class CFTDMarketDataField
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
};
const DWORD FTD_FID_MarketData=0x3055;

///�����ѯӦ��
class CFTDRspMarketDataField
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
};
const DWORD FTD_FID_RspMarketData=0x3055;

///�������ӷ��ʲ�ѯ����
class CFTDQrySGEDeferRateField
{
public:
	///��Լ����
	CInstrumentIDType	InstrumentID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(InstrumentID)
	));
};
const DWORD FTD_FID_QrySGEDeferRate=0x3059;

///�������ӷ��ʲ�ѯӦ��
class CFTDSGEDeferRateField
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
};
const DWORD FTD_FID_SGEDeferRate=0x305A;

///�ּ۱��ѯ����
class CFTDQryMBLMarketDataField
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

///�ּ۱��ѯӦ��
class CFTDMBLMarketDataField
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
};
const DWORD FTD_FID_MBLMarketData=0x305C;

///��ѯ�ֲ���ϸ����
class CFTDQryInvestorPositionDetailField
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

///��ѯ�ֲ���ϸӦ��
class CFTDRspInvestorPositionDetailField
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
};
const DWORD FTD_FID_RspInvestorPositionDetail=0x305E;

///Ͷ������Ȩ�������ʲ�ѯ
class CFTDQryInvestorOptionFeeField
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

///Ͷ������Ȩ��������
class CFTDRspInvestorOptionFeeField
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
};
const DWORD FTD_FID_RspInvestorOptionFee=0x3063;

///�ɽ�
class CFTDTradeField
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

///����
class CFTDOrderField
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

///����������
class CFTDFlowMessageCancelField
{
public:
	///����ϵ�к�
	CSequenceSeriesType	SequenceSeries;
	///������
	CDateType	TradingDay;
	///�������Ĵ���
	CDataCenterIDType	DataCenterID;
	///������ʼ���к�
	CSequenceNoType	StartSequenceNo;
	///���˽������к�
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

///��Ϣ�ַ�
class CFTDDisseminationField
{
public:
	///����ϵ�к�
	CSequenceSeriesType	SequenceSeries;
	///���к�
	CSequenceNoType	SequenceNo;
	TYPE_DESCRIPTOR((
		TYPE_DESC(SequenceSeries)
		,
		TYPE_DESC(SequenceNo)
	));
};
const DWORD FTD_FID_Dissemination=0x3033;

///�������
class CFTDInvestorAccountDepositResField
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
};
const DWORD FTD_FID_InvestorAccountDepositRes=0x3034;

///QDP������Ϣ֪ͨ
class CFTDMessageNotifyInfoField
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
};
const DWORD FTD_FID_MessageNotifyInfo=0x3035;

///�����������
class CFTDMarketDataBaseField
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

///���龲̬����
class CFTDMarketDataStaticField
{
public:
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

///�������³ɽ�����
class CFTDMarketDataLastMatchField
{
public:
	///���¼�
	CPriceType	LastPrice;
	///����
	CVolumeType	Volume;
	///�ɽ����
	CMoneyType	Turnover;
	///�ֲ���
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

///�������ż�����
class CFTDMarketDataBestPriceField
{
public:
	///�����һ
	CPriceType	BidPrice1;
	///������һ
	CVolumeType	BidVolume1;
	///������һ
	CPriceType	AskPrice1;
	///������һ
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

///�����������������
class CFTDMarketDataBid23Field
{
public:
	///����۶�
	CPriceType	BidPrice2;
	///��������
	CVolumeType	BidVolume2;
	///�������
	CPriceType	BidPrice3;
	///��������
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

///������������������
class CFTDMarketDataAsk23Field
{
public:
	///�����۶�
	CPriceType	AskPrice2;
	///��������
	CVolumeType	AskVolume2;
	///��������
	CPriceType	AskPrice3;
	///��������
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

///���������ġ�������
class CFTDMarketDataBid45Field
{
public:
	///�������
	CPriceType	BidPrice4;
	///��������
	CVolumeType	BidVolume4;
	///�������
	CPriceType	BidPrice5;
	///��������
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

///���������ġ�������
class CFTDMarketDataAsk45Field
{
public:
	///��������
	CPriceType	AskPrice4;
	///��������
	CVolumeType	AskVolume4;
	///��������
	CPriceType	AskPrice5;
	///��������
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

///�������ʱ������
class CFTDMarketDataUpdateTimeField
{
public:
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///����޸�ʱ��
	CTimeType	UpdateTime;
	///����޸ĺ���
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

///�������
class CFTDDepthMarketDataField
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
};
const DWORD FTD_FID_DepthMarketData=0x3051;

///���ĺ�Լ�������Ϣ
class CFTDSpecificInstrumentField
{
public:
	///��Լ����
	CInstrumentIDType	InstrumentID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(InstrumentID)
	));
};
const DWORD FTD_FID_SpecificInstrument=0x3052;

///�����ڴ������ѯ
class CFTDShmDepthMarketDataField
{
public:
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///IP��ַ
	CIPAddressType	IPAddress;
	///���ĺ�
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

///����������
class CFTDMarketDataExchangeIDField
{
public:
	///����������
	CExchangeIDType	ExchangeID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(ExchangeID)
	));
};
const DWORD FTD_FID_MarketDataExchangeID=0x3056;

///TOPIC��ѯ
class CFTDTopicSearchField
{
public:
	///���ĺ�
	CTopicIDType	TopicID;
	TYPE_DESCRIPTOR((
		TYPE_DESC(TopicID)
	));
};
const DWORD FTD_FID_TopicSearch=0x3057;

///��Լ״̬
class CFTDQmdInstrumentStateField
{
public:
	///����������
	CExchangeIDType	ExchangeID;
	///��Լ����
	CInstrumentIDType	InstrumentID;
	///��Լ����״̬
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

///����������������
class CFTDMarketDataAsk67Field
{
public:
	///��������
	CPriceType	AskPrice6;
	///��������
	CVolumeType	AskVolume6;
	///��������
	CPriceType	AskPrice7;
	///��������
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

///���������˾�����
class CFTDMarketDataAsk89Field
{
public:
	///�����۰�
	CPriceType	AskPrice8;
	///��������
	CVolumeType	AskVolume8;
	///�����۾�
	CPriceType	AskPrice9;
	///��������
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

///����������������
class CFTDMarketDataBid67Field
{
public:
	///�������
	CPriceType	BidPrice6;
	///��������
	CVolumeType	BidVolume6;
	///�������
	CPriceType	BidPrice7;
	///��������
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

///��������˾�����
class CFTDMarketDataBid89Field
{
public:
	///����۰�
	CPriceType	BidPrice8;
	///��������
	CVolumeType	BidVolume8;
	///����۾�
	CPriceType	BidPrice9;
	///��������
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

///������������ʮ����
class CFTDMarketDataAskBid10Field
{
public:
	///������ʮ
	CPriceType	AskPrice10;
	///������ʮ
	CVolumeType	AskVolume10;
	///�����ʮ
	CPriceType	BidPrice10;
	///������ʮ
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
