/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file QtestFtdcUserApiStruct.h
///@brief �����˿ͻ��˽ӿ�ʹ�õ�ҵ�����ݽṹ
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(QTEST_FTDCSTRUCT_H)
#define QTEST_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QTestFtdcUserApiDataType.h"

///��Ϣ�ַ�
struct CQTestFtdcDisseminationField
{
	///����ϵ�к�
	TQTestFtdcSequenceSeriesType	SequenceSeries;
	///���к�
	TQTestFtdcSequenceNoType	SequenceNo;
};

///��Ӧ��Ϣ
struct CQTestFtdcRspInfoField
{
	///�������
	TQTestFtdcErrorIDType	ErrorID;
	///������Ϣ
	TQTestFtdcErrorMsgType	ErrorMsg;
};

///ͨѶ�׶�
struct CQTestFtdcCommPhaseField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///ͨѶʱ�κ�
	TQTestFtdcCommPhaseNoType	CommPhaseNo;
};

///������������
struct CQTestFtdcExchangeTradingDayField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///����������
	TQTestFtdcExchangeIDType	ExchangeID;
};

///����Ự
struct CQTestFtdcSettlementSessionField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
};

///��ǰʱ��
struct CQTestFtdcCurrentTimeField
{
	///��ǰ����
	TQTestFtdcDateType	CurrDate;
	///��ǰʱ��
	TQTestFtdcTimeType	CurrTime;
	///��ǰʱ�䣨���룩
	TQTestFtdcMillisecType	CurrMillisec;
};

///�û���¼����
struct CQTestFtdcReqUserLoginField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///����
	TQTestFtdcPasswordType	Password;
	///�û��˲�Ʒ��Ϣ
	TQTestFtdcProductInfoType	UserProductInfo;
	///�ӿڶ˲�Ʒ��Ϣ
	TQTestFtdcProductInfoType	InterfaceProductInfo;
	///Э����Ϣ
	TQTestFtdcProtocolInfoType	ProtocolInfo;
	///�������Ĵ���
	TQTestFtdcDataCenterIDType	DataCenterID;
};

///�û���¼Ӧ��
struct CQTestFtdcRspUserLoginField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///��¼�ɹ�ʱ��
	TQTestFtdcTimeType	LoginTime;
	///��󱾵ر�����
	TQTestFtdcOrderLocalIDType	MaxOrderLocalID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///����ϵͳ����
	TQTestFtdcTradingSystemNameType	TradingSystemName;
	///�������Ĵ���
	TQTestFtdcDataCenterIDType	DataCenterID;
	///��Ա˽������ǰ����
	TQTestFtdcSequenceNoType	PrivateFlowSize;
	///����Ա˽������ǰ����
	TQTestFtdcSequenceNoType	UserFlowSize;
};

///�û��ǳ�����
struct CQTestFtdcReqUserLogoutField
{
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
};

///�û��ǳ�Ӧ��
struct CQTestFtdcRspUserLogoutField
{
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
};

///���뱨��
struct CQTestFtdcInputOrderField
{
	///�������
	TQTestFtdcOrderSysIDType	OrderSysID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///�����۸�����
	TQTestFtdcOrderPriceTypeType	OrderPriceType;
	///��������
	TQTestFtdcDirectionType	Direction;
	///��Ͽ�ƽ��־
	TQTestFtdcCombOffsetFlagType	CombOffsetFlag;
	///���Ͷ���ױ���־
	TQTestFtdcCombHedgeFlagType	CombHedgeFlag;
	///�۸�
	TQTestFtdcPriceType	LimitPrice;
	///����
	TQTestFtdcVolumeType	VolumeTotalOriginal;
	///��Ч������
	TQTestFtdcTimeConditionType	TimeCondition;
	///GTD����
	TQTestFtdcDateType	GTDDate;
	///�ɽ�������
	TQTestFtdcVolumeConditionType	VolumeCondition;
	///��С�ɽ���
	TQTestFtdcVolumeType	MinVolume;
	///��������
	TQTestFtdcContingentConditionType	ContingentCondition;
	///ֹ���
	TQTestFtdcPriceType	StopPrice;
	///ǿƽԭ��
	TQTestFtdcForceCloseReasonType	ForceCloseReason;
	///���ر������
	TQTestFtdcOrderLocalIDType	OrderLocalID;
	///�Զ������־
	TQTestFtdcBoolType	IsAutoSuspend;
	///ҵ��Ԫ
	TQTestFtdcBusinessUnitType	BusinessUnit;
};

///��������
struct CQTestFtdcOrderActionField
{
	///�������
	TQTestFtdcOrderSysIDType	OrderSysID;
	///���ر������
	TQTestFtdcOrderLocalIDType	OrderLocalID;
	///����������־
	TQTestFtdcActionFlagType	ActionFlag;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///�۸�
	TQTestFtdcPriceType	LimitPrice;
	///�����仯
	TQTestFtdcVolumeType	VolumeChange;
	///�������ر��
	TQTestFtdcOrderLocalIDType	ActionLocalID;
	///ҵ��Ԫ
	TQTestFtdcBusinessUnitType	BusinessUnit;
};

///OTC����
struct CQTestFtdcOTCOrderField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///OTC�������
	TQTestFtdcOTCOrderSysIDType	OTCOrderSysID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///��������
	TQTestFtdcDirectionType	Direction;
	///��ƽ��־
	TQTestFtdcOffsetFlagType	OffsetFlag;
	///Ͷ���ױ���־
	TQTestFtdcHedgeFlagType	HedgeFlag;
	///�۸�
	TQTestFtdcPriceType	Price;
	///����
	TQTestFtdcVolumeType	Volume;
	///���ַ���Ա����
	TQTestFtdcParticipantIDType	OtherParticipantID;
	///���ַ��ͻ�����
	TQTestFtdcClientIDType	OtherClientID;
	///���ַ������û�����
	TQTestFtdcUserIDType	OtherUserID;
	///���ַ���ƽ��־
	TQTestFtdcOffsetFlagType	OtherOffsetFlag;
	///���ַ��ױ���־
	TQTestFtdcHedgeFlagType	OtherHedgeFlag;
	///����OTC�������
	TQTestFtdcOrderLocalIDType	OTCOrderLocalID;
	///OTC����״̬
	TQTestFtdcOTCOrderStatusType	OTCOrderStatus;
	///����ʱ��
	TQTestFtdcTimeType	InsertTime;
	///����ʱ��
	TQTestFtdcTimeType	CancelTime;
	///�����Ա���
	TQTestFtdcParticipantIDType	ClearingPartID;
	///���ַ������Ա���
	TQTestFtdcParticipantIDType	OtherClearingPartID;
};

///���뱨��
struct CQTestFtdcInputQuoteField
{
	///���۱��
	TQTestFtdcQuoteSysIDType	QuoteSysID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///��������
	TQTestFtdcVolumeType	BidVolume;
	///��������
	TQTestFtdcVolumeType	AskVolume;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///���ر��۱��
	TQTestFtdcOrderLocalIDType	QuoteLocalID;
	///ҵ��Ԫ
	TQTestFtdcBusinessUnitType	BusinessUnit;
	///����Ͽ�ƽ��־
	TQTestFtdcCombOffsetFlagType	BidCombOffsetFlag;
	///������ױ���־
	TQTestFtdcCombHedgeFlagType	BidCombHedgeFlag;
	///�򷽼۸�
	TQTestFtdcPriceType	BidPrice;
	///������Ͽ�ƽ��־
	TQTestFtdcCombOffsetFlagType	AskCombOffsetFlag;
	///��������ױ���־
	TQTestFtdcCombHedgeFlagType	AskCombHedgeFlag;
	///�����۸�
	TQTestFtdcPriceType	AskPrice;
};

///���۲���
struct CQTestFtdcQuoteActionField
{
	///���۱��
	TQTestFtdcQuoteSysIDType	QuoteSysID;
	///���ر��۱��
	TQTestFtdcOrderLocalIDType	QuoteLocalID;
	///����������־
	TQTestFtdcActionFlagType	ActionFlag;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///�������ر��
	TQTestFtdcOrderLocalIDType	ActionLocalID;
	///ҵ��Ԫ
	TQTestFtdcBusinessUnitType	BusinessUnit;
};

///����ִ������
struct CQTestFtdcInputExecOrderField
{
	///��Լ���
	TQTestFtdcInstrumentIDType	InstrumentID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///����ִ��������
	TQTestFtdcOrderLocalIDType	ExecOrderLocalID;
	///����
	TQTestFtdcVolumeType	Volume;
	///ҵ��Ԫ
	TQTestFtdcBusinessUnitType	BusinessUnit;
};

///ִ���������
struct CQTestFtdcExecOrderActionField
{
	///ִ��������
	TQTestFtdcExecOrderSysIDType	ExecOrderSysID;
	///����ִ��������
	TQTestFtdcOrderLocalIDType	ExecOrderLocalID;
	///����������־
	TQTestFtdcActionFlagType	ActionFlag;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///�������ر��
	TQTestFtdcOrderLocalIDType	ActionLocalID;
	///ҵ��Ԫ
	TQTestFtdcBusinessUnitType	BusinessUnit;
};

///�û���¼�˳�
struct CQTestFtdcUserLogoutField
{
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
};

///�û������޸�
struct CQTestFtdcUserPasswordUpdateField
{
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///������
	TQTestFtdcPasswordType	OldPassword;
	///������
	TQTestFtdcPasswordType	NewPassword;
};

///����Ǳ���ϱ���
struct CQTestFtdcInputCombOrderField
{
	///��ϱ������
	TQTestFtdcOrderSysIDType	CombOrderSysID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///�۸�
	TQTestFtdcPriceType	LimitPrice;
	///����
	TQTestFtdcVolumeType	VolumeTotalOriginal;
	///���ر������
	TQTestFtdcOrderLocalIDType	CombOrderLocalID;
	///ҵ��Ԫ
	TQTestFtdcBusinessUnitType	BusinessUnit;
	///��Լ����1
	TQTestFtdcInstrumentIDType	InstrumentID1;
	///��������1
	TQTestFtdcDirectionType	Direction1;
	///���ȳ���1
	TQTestFtdcLegMultipleType	LegMultiple1;
	///��ƽ��־1
	TQTestFtdcOffsetFlagType	OffsetFlag1;
	///Ͷ���ױ���־1
	TQTestFtdcHedgeFlagType	HedgeFlag1;
	///��Լ����2
	TQTestFtdcInstrumentIDType	InstrumentID2;
	///��������2
	TQTestFtdcDirectionType	Direction2;
	///���ȳ���2
	TQTestFtdcLegMultipleType	LegMultiple2;
	///��ƽ��־2
	TQTestFtdcOffsetFlagType	OffsetFlag2;
	///Ͷ���ױ���־2
	TQTestFtdcHedgeFlagType	HedgeFlag2;
	///��Լ����3
	TQTestFtdcInstrumentIDType	InstrumentID3;
	///��������3
	TQTestFtdcDirectionType	Direction3;
	///���ȳ���3
	TQTestFtdcLegMultipleType	LegMultiple3;
	///��ƽ��־3
	TQTestFtdcOffsetFlagType	OffsetFlag3;
	///Ͷ���ױ���־3
	TQTestFtdcHedgeFlagType	HedgeFlag3;
	///��Լ����4
	TQTestFtdcInstrumentIDType	InstrumentID4;
	///��������4
	TQTestFtdcDirectionType	Direction4;
	///���ȳ���4
	TQTestFtdcLegMultipleType	LegMultiple4;
	///��ƽ��־4
	TQTestFtdcOffsetFlagType	OffsetFlag4;
	///Ͷ���ױ���־4
	TQTestFtdcHedgeFlagType	HedgeFlag4;
};

///ǿ���û��˳�
struct CQTestFtdcForceUserExitField
{
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
};

///��Ա�ʽ��ʻ����
struct CQTestFtdcAccountDepositField
{
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///�ʽ��˺�
	TQTestFtdcAccountIDType	Account;
	///�����
	TQTestFtdcMoneyType	Deposit;
};

///������ѯ
struct CQTestFtdcQryOrderField
{
	///��ʼ��Ա����
	TQTestFtdcParticipantIDType	PartIDStart;
	///������Ա����
	TQTestFtdcParticipantIDType	PartIDEnd;
	///�������
	TQTestFtdcOrderSysIDType	OrderSysID;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///��ʼʱ��
	TQTestFtdcTimeType	TimeStart;
	///����ʱ��
	TQTestFtdcTimeType	TimeEnd;
};

///���۲�ѯ
struct CQTestFtdcQryQuoteField
{
	///��ʼ��Ա����
	TQTestFtdcParticipantIDType	PartIDStart;
	///������Ա����
	TQTestFtdcParticipantIDType	PartIDEnd;
	///���۱��
	TQTestFtdcQuoteSysIDType	QuoteSysID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
};

///�ɽ���ѯ
struct CQTestFtdcQryTradeField
{
	///��ʼ��Ա����
	TQTestFtdcParticipantIDType	PartIDStart;
	///������Ա����
	TQTestFtdcParticipantIDType	PartIDEnd;
	///��ʼ��Լ����
	TQTestFtdcInstrumentIDType	InstIDStart;
	///������Լ����
	TQTestFtdcInstrumentIDType	InstIDEnd;
	///�ɽ����
	TQTestFtdcTradeIDType	TradeID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///��ʼʱ��
	TQTestFtdcTimeType	TimeStart;
	///����ʱ��
	TQTestFtdcTimeType	TimeEnd;
};

///�����ѯ
struct CQTestFtdcQryMarketDataField
{
	///��Ʒ����
	TQTestFtdcProductIDType	ProductID;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
};

///�ͻ���ѯ
struct CQTestFtdcQryClientField
{
	///��ʼ��Ա����
	TQTestFtdcParticipantIDType	PartIDStart;
	///������Ա����
	TQTestFtdcParticipantIDType	PartIDEnd;
	///��ʼ�ͻ�����
	TQTestFtdcClientIDType	ClientIDStart;
	///�����ͻ�����
	TQTestFtdcClientIDType	ClientIDEnd;
};

///��Ա�ֲֲ�ѯ
struct CQTestFtdcQryPartPositionField
{
	///��ʼ��Ա����
	TQTestFtdcParticipantIDType	PartIDStart;
	///������Ա����
	TQTestFtdcParticipantIDType	PartIDEnd;
	///��ʼ��Լ����
	TQTestFtdcInstrumentIDType	InstIDStart;
	///������Լ����
	TQTestFtdcInstrumentIDType	InstIDEnd;
};

///�ͻ��ֲֲ�ѯ
struct CQTestFtdcQryClientPositionField
{
	///��ʼ��Ա����
	TQTestFtdcParticipantIDType	PartIDStart;
	///������Ա����
	TQTestFtdcParticipantIDType	PartIDEnd;
	///��ʼ�ͻ�����
	TQTestFtdcClientIDType	ClientIDStart;
	///�����ͻ�����
	TQTestFtdcClientIDType	ClientIDEnd;
	///��ʼ��Լ����
	TQTestFtdcInstrumentIDType	InstIDStart;
	///������Լ����
	TQTestFtdcInstrumentIDType	InstIDEnd;
	///�ͻ�����
	TQTestFtdcClientTypeType	ClientType;
};

///�����ʽ��ѯ
struct CQTestFtdcQryPartAccountField
{
	///��ʼ��Ա����
	TQTestFtdcParticipantIDType	PartIDStart;
	///������Ա����
	TQTestFtdcParticipantIDType	PartIDEnd;
	///�ʽ��ʺ�
	TQTestFtdcAccountIDType	AccountID;
};

///��Լ��ѯ
struct CQTestFtdcQryInstrumentField
{
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///��Ʒ�����
	TQTestFtdcProductGroupIDType	ProductGroupID;
	///��Ʒ����
	TQTestFtdcProductIDType	ProductID;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
};

///��Լ״̬��ѯ
struct CQTestFtdcQryInstrumentStatusField
{
	///��ʼ��Լ����
	TQTestFtdcInstrumentIDType	InstIDStart;
	///������Լ����
	TQTestFtdcInstrumentIDType	InstIDEnd;
};

///������״̬��ѯ
struct CQTestFtdcQrySGDataSyncStatusField
{
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
};

///�û����߲�ѯ
struct CQTestFtdcQryUserSessionField
{
	///��ʼ�����û�����
	TQTestFtdcUserIDType	UserIDStart;
	///���������û�����
	TQTestFtdcUserIDType	UserIDEnd;
};

///�û���ѯ
struct CQTestFtdcQryUserField
{
	///��ʼ�����û�����
	TQTestFtdcUserIDType	UserIDStart;
	///���������û�����
	TQTestFtdcUserIDType	UserIDEnd;
};

///�����ѯ
struct CQTestFtdcQryBulletinField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///�г�����
	TQTestFtdcMarketIDType	MarketID;
	///������
	TQTestFtdcBulletinIDType	BulletinID;
	///��������
	TQTestFtdcNewsTypeType	NewsType;
	///�����̶�
	TQTestFtdcNewsUrgencyType	NewsUrgency;
};

///��Ա��ѯ
struct CQTestFtdcQryParticipantField
{
	///��ʼ��Ա����
	TQTestFtdcParticipantIDType	PartIDStart;
	///������Ա����
	TQTestFtdcParticipantIDType	PartIDEnd;
};

///��ֵ��Ȳ�ѯ
struct CQTestFtdcQryHedgeVolumeField
{
	///��ʼ��Ա����
	TQTestFtdcParticipantIDType	PartIDStart;
	///������Ա����
	TQTestFtdcParticipantIDType	PartIDEnd;
	///��ʼ�ͻ�����
	TQTestFtdcClientIDType	ClientIDStart;
	///�����ͻ�����
	TQTestFtdcClientIDType	ClientIDEnd;
	///��ʼ��Լ����
	TQTestFtdcInstrumentIDType	InstIDStart;
	///������Լ����
	TQTestFtdcInstrumentIDType	InstIDEnd;
};

///��Լ��λ��ѯ
struct CQTestFtdcQryMBLMarketDataField
{
	///��ʼ��Լ����
	TQTestFtdcInstrumentIDType	InstIDStart;
	///������Լ����
	TQTestFtdcInstrumentIDType	InstIDEnd;
	///��������
	TQTestFtdcDirectionType	Direction;
};

///�����޶��ѯ
struct CQTestFtdcQryCreditLimitField
{
	///���׻�Ա���
	TQTestFtdcParticipantIDType	ParticipantID;
	///�����Ա���
	TQTestFtdcParticipantIDType	ClearingPartID;
};

///�Ǳ���ϱ�����ѯ
struct CQTestFtdcQryCombOrderField
{
	///��ʼ��Ա����
	TQTestFtdcParticipantIDType	PartIDStart;
	///������Ա����
	TQTestFtdcParticipantIDType	PartIDEnd;
	///��ϱ������
	TQTestFtdcOrderSysIDType	CombOrderSysID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
};

///��Ա�ʽ�Ӧ��
struct CQTestFtdcRspPartAccountField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///�ϴν���׼����
	TQTestFtdcMoneyType	PreBalance;
	///��ǰ��֤���ܶ�
	TQTestFtdcMoneyType	CurrMargin;
	///ƽ��ӯ��
	TQTestFtdcMoneyType	CloseProfit;
	///��ȨȨ������֧
	TQTestFtdcMoneyType	Premium;
	///�����
	TQTestFtdcMoneyType	Deposit;
	///������
	TQTestFtdcMoneyType	Withdraw;
	///�ڻ�����׼����
	TQTestFtdcMoneyType	Balance;
	///�����ʽ�
	TQTestFtdcMoneyType	Available;
	///�ʽ��ʺ�
	TQTestFtdcAccountIDType	AccountID;
	///����ı�֤��
	TQTestFtdcMoneyType	FrozenMargin;
	///�����Ȩ����
	TQTestFtdcMoneyType	FrozenPremium;
	///����׼����
	TQTestFtdcMoneyType	BaseReserve;
};

///��Ա�ֲ�Ӧ��
struct CQTestFtdcRspPartPositionField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///Ͷ���ױ���־
	TQTestFtdcHedgeFlagType	HedgeFlag;
	///�ֲֶ�շ���
	TQTestFtdcPosiDirectionType	PosiDirection;
	///���ճֲ�
	TQTestFtdcVolumeType	YdPosition;
	///���ճֲ�
	TQTestFtdcVolumeType	Position;
	///��ͷ����
	TQTestFtdcVolumeType	LongFrozen;
	///��ͷ����
	TQTestFtdcVolumeType	ShortFrozen;
	///���ն�ͷ����
	TQTestFtdcVolumeType	YdLongFrozen;
	///���տ�ͷ����
	TQTestFtdcVolumeType	YdShortFrozen;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///���׽�ɫ
	TQTestFtdcTradingRoleType	TradingRole;
};

///�ͻ��ֲ�Ӧ��
struct CQTestFtdcRspClientPositionField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///Ͷ���ױ���־
	TQTestFtdcHedgeFlagType	HedgeFlag;
	///�ֲֶ�շ���
	TQTestFtdcPosiDirectionType	PosiDirection;
	///���ճֲ�
	TQTestFtdcVolumeType	YdPosition;
	///���ճֲ�
	TQTestFtdcVolumeType	Position;
	///��ͷ����
	TQTestFtdcVolumeType	LongFrozen;
	///��ͷ����
	TQTestFtdcVolumeType	ShortFrozen;
	///���ն�ͷ����
	TQTestFtdcVolumeType	YdLongFrozen;
	///���տ�ͷ����
	TQTestFtdcVolumeType	YdShortFrozen;
	///������ɽ���
	TQTestFtdcVolumeType	BuyTradeVolume;
	///�������ɽ���
	TQTestFtdcVolumeType	SellTradeVolume;
	///�ֲֳɱ�
	TQTestFtdcMoneyType	PositionCost;
	///���ճֲֳɱ�
	TQTestFtdcMoneyType	YdPositionCost;
	///ռ�õı�֤��
	TQTestFtdcMoneyType	UseMargin;
	///����ı�֤��
	TQTestFtdcMoneyType	FrozenMargin;
	///��ͷ����ı�֤��
	TQTestFtdcMoneyType	LongFrozenMargin;
	///��ͷ����ı�֤��
	TQTestFtdcMoneyType	ShortFrozenMargin;
	///�����Ȩ����
	TQTestFtdcMoneyType	FrozenPremium;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
};

///��Լ��ѯӦ��
struct CQTestFtdcRspInstrumentField
{
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///��Ʒ����
	TQTestFtdcProductIDType	ProductID;
	///��Ʒ�����
	TQTestFtdcProductGroupIDType	ProductGroupID;
	///������Ʒ����
	TQTestFtdcInstrumentIDType	UnderlyingInstrID;
	///��Ʒ����
	TQTestFtdcProductClassType	ProductClass;
	///�ֲ�����
	TQTestFtdcPositionTypeType	PositionType;
	///ִ�м�
	TQTestFtdcPriceType	StrikePrice;
	///��Ȩ����
	TQTestFtdcOptionsTypeType	OptionsType;
	///��Լ��������
	TQTestFtdcVolumeMultipleType	VolumeMultiple;
	///��Լ������Ʒ����
	TQTestFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///��Լ����
	TQTestFtdcInstrumentNameType	InstrumentName;
	///�������
	TQTestFtdcYearType	DeliveryYear;
	///������
	TQTestFtdcMonthType	DeliveryMonth;
	///��ǰ�·�
	TQTestFtdcAdvanceMonthType	AdvanceMonth;
	///��ǰ�Ƿ���
	TQTestFtdcBoolType	IsTrading;
	///������
	TQTestFtdcDateType	CreateDate;
	///������
	TQTestFtdcDateType	OpenDate;
	///������
	TQTestFtdcDateType	ExpireDate;
	///��ʼ������
	TQTestFtdcDateType	StartDelivDate;
	///��󽻸���
	TQTestFtdcDateType	EndDelivDate;
	///���ƻ�׼��
	TQTestFtdcPriceType	BasisPrice;
	///�м۵�����µ���
	TQTestFtdcVolumeType	MaxMarketOrderVolume;
	///�м۵���С�µ���
	TQTestFtdcVolumeType	MinMarketOrderVolume;
	///�޼۵�����µ���
	TQTestFtdcVolumeType	MaxLimitOrderVolume;
	///�޼۵���С�µ���
	TQTestFtdcVolumeType	MinLimitOrderVolume;
	///��С�䶯��λ
	TQTestFtdcPriceType	PriceTick;
	///��������Ȼ�˿���
	TQTestFtdcMonthCountType	AllowDelivPersonOpen;
};

///��Ϣ��ѯ
struct CQTestFtdcQryInformationField
{
	///��ʼ��Ϣ����
	TQTestFtdcInformationIDType	InformationIDStart;
	///������Ϣ����
	TQTestFtdcInformationIDType	InformationIDEnd;
};

///��Ϣ��ѯ
struct CQTestFtdcInformationField
{
	///��Ϣ���
	TQTestFtdcInformationIDType	InformationID;
	///���к�
	TQTestFtdcSequenceNoType	SequenceNo;
	///��Ϣ����
	TQTestFtdcContentType	Content;
	///���ĳ���
	TQTestFtdcContentLengthType	ContentLength;
	///�Ƿ����
	TQTestFtdcBoolType	IsAccomplished;
};

///�����޶�
struct CQTestFtdcCreditLimitField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///�ϴν���׼����
	TQTestFtdcMoneyType	PreBalance;
	///��ǰ��֤���ܶ�
	TQTestFtdcMoneyType	CurrMargin;
	///ƽ��ӯ��
	TQTestFtdcMoneyType	CloseProfit;
	///��ȨȨ������֧
	TQTestFtdcMoneyType	Premium;
	///�����
	TQTestFtdcMoneyType	Deposit;
	///������
	TQTestFtdcMoneyType	Withdraw;
	///�ڻ�����׼����
	TQTestFtdcMoneyType	Balance;
	///�����ʽ�
	TQTestFtdcMoneyType	Available;
	///���׻�Ա���
	TQTestFtdcParticipantIDType	ParticipantID;
	///�����Ա���
	TQTestFtdcParticipantIDType	ClearingPartID;
	///����ı�֤��
	TQTestFtdcMoneyType	FrozenMargin;
	///�����Ȩ����
	TQTestFtdcMoneyType	FrozenPremium;
};

///�ͻ���ѯӦ��
struct CQTestFtdcRspClientField
{
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�ͻ�����
	TQTestFtdcPartyNameType	ClientName;
	///֤������
	TQTestFtdcIdCardTypeType	IdentifiedCardType;
	///ԭ֤������
	TQTestFtdcIdentifiedCardNoV1Type	UseLess;
	///���׽�ɫ
	TQTestFtdcTradingRoleType	TradingRole;
	///�ͻ�����
	TQTestFtdcClientTypeType	ClientType;
	///�Ƿ��Ծ
	TQTestFtdcBoolType	IsActive;
	///��Ա��
	TQTestFtdcParticipantIDType	ParticipantID;
	///֤������
	TQTestFtdcIdentifiedCardNoType	IdentifiedCardNo;
};

///����������
struct CQTestFtdcFlowMessageCancelField
{
	///����ϵ�к�
	TQTestFtdcSequenceSeriesType	SequenceSeries;
	///������
	TQTestFtdcDateType	TradingDay;
	///�������Ĵ���
	TQTestFtdcDataCenterIDType	DataCenterID;
	///������ʼ���к�
	TQTestFtdcSequenceNoType	StartSequenceNo;
	///���˽������к�
	TQTestFtdcSequenceNoType	EndSequenceNo;
};

///��Ա
struct CQTestFtdcParticipantField
{
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///��Ա����
	TQTestFtdcParticipantNameType	ParticipantName;
	///��Ա���
	TQTestFtdcParticipantAbbrType	ParticipantAbbr;
	///��Ա����
	TQTestFtdcMemberTypeType	MemberType;
	///�Ƿ��Ծ
	TQTestFtdcBoolType	IsActive;
};

///�û�
struct CQTestFtdcUserField
{
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///�����û�����
	TQTestFtdcUserTypeType	UserType;
	///����
	TQTestFtdcPasswordType	Password;
	///����ԱȨ��
	TQTestFtdcUserActiveType	IsActive;
};

///�ͻ�
struct CQTestFtdcClientField
{
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�ͻ�����
	TQTestFtdcPartyNameType	ClientName;
	///֤������
	TQTestFtdcIdCardTypeType	IdentifiedCardType;
	///֤������
	TQTestFtdcIdentifiedCardNoType	IdentifiedCardNo;
	///���׽�ɫ
	TQTestFtdcTradingRoleType	TradingRole;
	///�ͻ�����
	TQTestFtdcClientTypeType	ClientType;
	///�Ƿ��Ծ
	TQTestFtdcBoolType	IsActive;
	///�ͻ���������
	TQTestFtdcHedgeFlagType	HedgeFlag;
};

///�û��Ự
struct CQTestFtdcUserSessionField
{
	///ǰ�ñ��
	TQTestFtdcFrontIDType	FrontID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///�����û�����
	TQTestFtdcUserTypeType	UserType;
	///�Ự���
	TQTestFtdcSessionIDType	SessionID;
	///��¼ʱ��
	TQTestFtdcTimeType	LoginTime;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///IP��ַ
	TQTestFtdcIPAddressType	IPAddress;
	///�û��˲�Ʒ��Ϣ
	TQTestFtdcProductInfoType	UserProductInfo;
	///�ӿڶ˲�Ʒ��Ϣ
	TQTestFtdcProductInfoType	InterfaceProductInfo;
	///Э����Ϣ
	TQTestFtdcProtocolInfoType	ProtocolInfo;
};

///��Ʒ��
struct CQTestFtdcProductGroupField
{
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///��Ʒ�����
	TQTestFtdcProductGroupIDType	ProductGroupID;
	///��Ʒ������
	TQTestFtdcProductGroupNameType	ProductGroupName;
	///��Ʒ����
	TQTestFtdcCommodityIDType	CommodityID;
};

///��Ʒ
struct CQTestFtdcProductField
{
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///��Ʒ����
	TQTestFtdcProductIDType	ProductID;
	///��Ʒ�����
	TQTestFtdcProductGroupIDType	ProductGroupID;
	///��Ʒ����
	TQTestFtdcProductNameType	ProductName;
	///��Ʒ����
	TQTestFtdcProductClassType	ProductClass;
};

///��Լ
struct CQTestFtdcInstrumentField
{
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///��Ʒ����
	TQTestFtdcProductIDType	ProductID;
	///��Ʒ�����
	TQTestFtdcProductGroupIDType	ProductGroupID;
	///������Ʒ����
	TQTestFtdcInstrumentIDType	UnderlyingInstrID;
	///��Ʒ����
	TQTestFtdcProductClassType	ProductClass;
	///�ֲ�����
	TQTestFtdcPositionTypeType	PositionType;
	///ִ�м�
	TQTestFtdcPriceType	StrikePrice;
	///��Ȩ����
	TQTestFtdcOptionsTypeType	OptionsType;
	///��Լ��������
	TQTestFtdcVolumeMultipleType	VolumeMultiple;
	///��Լ������Ʒ����
	TQTestFtdcUnderlyingMultipleType	UnderlyingMultiple;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///��Լ����
	TQTestFtdcInstrumentNameType	InstrumentName;
	///�������
	TQTestFtdcYearType	DeliveryYear;
	///������
	TQTestFtdcMonthType	DeliveryMonth;
	///��ǰ�·�
	TQTestFtdcAdvanceMonthType	AdvanceMonth;
	///��ǰ�Ƿ���
	TQTestFtdcBoolType	IsTrading;
};

///��Ͻ��׺�Լ�ĵ���
struct CQTestFtdcCombinationLegField
{
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///��Ϻ�Լ����
	TQTestFtdcInstrumentIDType	CombInstrumentID;
	///���ȱ��
	TQTestFtdcLegIDType	LegID;
	///���Ⱥ�Լ����
	TQTestFtdcInstrumentIDType	LegInstrumentID;
	///��������
	TQTestFtdcDirectionType	Direction;
	///���ȳ���
	TQTestFtdcLegMultipleType	LegMultiple;
	///�Ƶ�����
	TQTestFtdcImplyLevelType	ImplyLevel;
};

///�˻��ʽ���Ϣ
struct CQTestFtdcAccountInfoField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///�ϴν���׼����
	TQTestFtdcMoneyType	PreBalance;
	///��ǰ��֤���ܶ�
	TQTestFtdcMoneyType	CurrMargin;
	///ƽ��ӯ��
	TQTestFtdcMoneyType	CloseProfit;
	///��ȨȨ������֧
	TQTestFtdcMoneyType	Premium;
	///�����
	TQTestFtdcMoneyType	Deposit;
	///������
	TQTestFtdcMoneyType	Withdraw;
	///�ڻ�����׼����
	TQTestFtdcMoneyType	Balance;
	///�����ʽ�
	TQTestFtdcMoneyType	Available;
	///��������
	TQTestFtdcDateType	DateAccountOpen;
	///�ϴν��������
	TQTestFtdcDateType	PreDate;
	///�Ͻ���ı��
	TQTestFtdcSettlementIDType	PreSettlementID;
	///�ϴα�֤���ܶ�
	TQTestFtdcMoneyType	PreMargin;
	///�ڻ���֤��
	TQTestFtdcMoneyType	FuturesMargin;
	///��Ȩ��֤��
	TQTestFtdcMoneyType	OptionsMargin;
	///�ֲ�ӯ��
	TQTestFtdcMoneyType	PositionProfit;
	///����ӯ��
	TQTestFtdcMoneyType	Profit;
	///��Ϣ����
	TQTestFtdcMoneyType	Interest;
	///������
	TQTestFtdcMoneyType	Fee;
	///����Ѻ���
	TQTestFtdcMoneyType	TotalCollateral;
	///����Ѻ�ֵı�֤����
	TQTestFtdcMoneyType	CollateralForMargin;
	///�ϴ��ʽ���Ϣ����
	TQTestFtdcMoneyType	PreAccmulateInterest;
	///�ʽ���Ϣ����
	TQTestFtdcMoneyType	AccumulateInterest;
	///��Ѻ�����ѻ���
	TQTestFtdcMoneyType	AccumulateFee;
	///�����ʽ�
	TQTestFtdcMoneyType	ForzenDeposit;
	///�ʻ�״̬
	TQTestFtdcAccountStatusType	AccountStatus;
	///�ʽ��ʺ�
	TQTestFtdcAccountIDType	AccountID;
};

///��Ա��Լ�ֲ�
struct CQTestFtdcPartPositionField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///Ͷ���ױ���־
	TQTestFtdcHedgeFlagType	HedgeFlag;
	///�ֲֶ�շ���
	TQTestFtdcPosiDirectionType	PosiDirection;
	///���ճֲ�
	TQTestFtdcVolumeType	YdPosition;
	///���ճֲ�
	TQTestFtdcVolumeType	Position;
	///��ͷ����
	TQTestFtdcVolumeType	LongFrozen;
	///��ͷ����
	TQTestFtdcVolumeType	ShortFrozen;
	///���ն�ͷ����
	TQTestFtdcVolumeType	YdLongFrozen;
	///���տ�ͷ����
	TQTestFtdcVolumeType	YdShortFrozen;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///���׽�ɫ
	TQTestFtdcTradingRoleType	TradingRole;
};

///�ͻ���Լ�ֲ�
struct CQTestFtdcClientPositionField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///Ͷ���ױ���־
	TQTestFtdcHedgeFlagType	HedgeFlag;
	///�ֲֶ�շ���
	TQTestFtdcPosiDirectionType	PosiDirection;
	///���ճֲ�
	TQTestFtdcVolumeType	YdPosition;
	///���ճֲ�
	TQTestFtdcVolumeType	Position;
	///��ͷ����
	TQTestFtdcVolumeType	LongFrozen;
	///��ͷ����
	TQTestFtdcVolumeType	ShortFrozen;
	///���ն�ͷ����
	TQTestFtdcVolumeType	YdLongFrozen;
	///���տ�ͷ����
	TQTestFtdcVolumeType	YdShortFrozen;
	///������ɽ���
	TQTestFtdcVolumeType	BuyTradeVolume;
	///�������ɽ���
	TQTestFtdcVolumeType	SellTradeVolume;
	///�ֲֳɱ�
	TQTestFtdcMoneyType	PositionCost;
	///���ճֲֳɱ�
	TQTestFtdcMoneyType	YdPositionCost;
	///ռ�õı�֤��
	TQTestFtdcMoneyType	UseMargin;
	///����ı�֤��
	TQTestFtdcMoneyType	FrozenMargin;
	///��ͷ����ı�֤��
	TQTestFtdcMoneyType	LongFrozenMargin;
	///��ͷ����ı�֤��
	TQTestFtdcMoneyType	ShortFrozenMargin;
	///�����Ȩ����
	TQTestFtdcMoneyType	FrozenPremium;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
};

///��ֵ�����
struct CQTestFtdcHedgeVolumeField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///��ͷ��ֵ������������
	TQTestFtdcVolumeType	LongVolumeOriginal;
	///��ͷ��ֵ������������
	TQTestFtdcVolumeType	ShortVolumeOriginal;
	///��ͷ��ֵ���
	TQTestFtdcVolumeType	LongVolume;
	///��ͷ��ֵ���
	TQTestFtdcVolumeType	ShortVolume;
};

///�г�����
struct CQTestFtdcMarketDataField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///���¼�
	TQTestFtdcPriceType	LastPrice;
	///�����
	TQTestFtdcPriceType	PreSettlementPrice;
	///������
	TQTestFtdcPriceType	PreClosePrice;
	///��ֲ���
	TQTestFtdcLargeVolumeType	PreOpenInterest;
	///����
	TQTestFtdcPriceType	OpenPrice;
	///��߼�
	TQTestFtdcPriceType	HighestPrice;
	///��ͼ�
	TQTestFtdcPriceType	LowestPrice;
	///����
	TQTestFtdcVolumeType	Volume;
	///�ɽ����
	TQTestFtdcMoneyType	Turnover;
	///�ֲ���
	TQTestFtdcLargeVolumeType	OpenInterest;
	///������
	TQTestFtdcPriceType	ClosePrice;
	///�����
	TQTestFtdcPriceType	SettlementPrice;
	///��ͣ���
	TQTestFtdcPriceType	UpperLimitPrice;
	///��ͣ���
	TQTestFtdcPriceType	LowerLimitPrice;
	///����ʵ��
	TQTestFtdcRatioType	PreDelta;
	///����ʵ��
	TQTestFtdcRatioType	CurrDelta;
	///����޸�ʱ��
	TQTestFtdcTimeType	UpdateTime;
	///����޸ĺ���
	TQTestFtdcMillisecType	UpdateMillisec;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
};

///����г�����
struct CQTestFtdcDepthMarketDataField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///���¼�
	TQTestFtdcPriceType	LastPrice;
	///�����
	TQTestFtdcPriceType	PreSettlementPrice;
	///������
	TQTestFtdcPriceType	PreClosePrice;
	///��ֲ���
	TQTestFtdcLargeVolumeType	PreOpenInterest;
	///����
	TQTestFtdcPriceType	OpenPrice;
	///��߼�
	TQTestFtdcPriceType	HighestPrice;
	///��ͼ�
	TQTestFtdcPriceType	LowestPrice;
	///����
	TQTestFtdcVolumeType	Volume;
	///�ɽ����
	TQTestFtdcMoneyType	Turnover;
	///�ֲ���
	TQTestFtdcLargeVolumeType	OpenInterest;
	///������
	TQTestFtdcPriceType	ClosePrice;
	///�����
	TQTestFtdcPriceType	SettlementPrice;
	///��ͣ���
	TQTestFtdcPriceType	UpperLimitPrice;
	///��ͣ���
	TQTestFtdcPriceType	LowerLimitPrice;
	///����ʵ��
	TQTestFtdcRatioType	PreDelta;
	///����ʵ��
	TQTestFtdcRatioType	CurrDelta;
	///����޸�ʱ��
	TQTestFtdcTimeType	UpdateTime;
	///����޸ĺ���
	TQTestFtdcMillisecType	UpdateMillisec;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///�����һ
	TQTestFtdcPriceType	BidPrice1;
	///������һ
	TQTestFtdcVolumeType	BidVolume1;
	///������һ
	TQTestFtdcPriceType	AskPrice1;
	///������һ
	TQTestFtdcVolumeType	AskVolume1;
	///����۶�
	TQTestFtdcPriceType	BidPrice2;
	///��������
	TQTestFtdcVolumeType	BidVolume2;
	///�����۶�
	TQTestFtdcPriceType	AskPrice2;
	///��������
	TQTestFtdcVolumeType	AskVolume2;
	///�������
	TQTestFtdcPriceType	BidPrice3;
	///��������
	TQTestFtdcVolumeType	BidVolume3;
	///��������
	TQTestFtdcPriceType	AskPrice3;
	///��������
	TQTestFtdcVolumeType	AskVolume3;
	///�������
	TQTestFtdcPriceType	BidPrice4;
	///��������
	TQTestFtdcVolumeType	BidVolume4;
	///��������
	TQTestFtdcPriceType	AskPrice4;
	///��������
	TQTestFtdcVolumeType	AskVolume4;
	///�������
	TQTestFtdcPriceType	BidPrice5;
	///��������
	TQTestFtdcVolumeType	BidVolume5;
	///��������
	TQTestFtdcPriceType	AskPrice5;
	///��������
	TQTestFtdcVolumeType	AskVolume5;
};

///�ּ۱�
struct CQTestFtdcMBLMarketDataField
{
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///��������
	TQTestFtdcDirectionType	Direction;
	///�۸�
	TQTestFtdcPriceType	Price;
	///����
	TQTestFtdcVolumeType	Volume;
};

///��������
struct CQTestFtdcAliasDefineField
{
	///��ʼλ��
	TQTestFtdcStartPosType	StartPos;
	///����
	TQTestFtdcAliasType	Alias;
	///ԭ��
	TQTestFtdcOriginalTextType	OriginalText;
};

///�����������
struct CQTestFtdcMarketDataBaseField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///�����
	TQTestFtdcPriceType	PreSettlementPrice;
	///������
	TQTestFtdcPriceType	PreClosePrice;
	///��ֲ���
	TQTestFtdcLargeVolumeType	PreOpenInterest;
	///����ʵ��
	TQTestFtdcRatioType	PreDelta;
};

///���龲̬����
struct CQTestFtdcMarketDataStaticField
{
	///����
	TQTestFtdcPriceType	OpenPrice;
	///��߼�
	TQTestFtdcPriceType	HighestPrice;
	///��ͼ�
	TQTestFtdcPriceType	LowestPrice;
	///������
	TQTestFtdcPriceType	ClosePrice;
	///��ͣ���
	TQTestFtdcPriceType	UpperLimitPrice;
	///��ͣ���
	TQTestFtdcPriceType	LowerLimitPrice;
	///�����
	TQTestFtdcPriceType	SettlementPrice;
	///����ʵ��
	TQTestFtdcRatioType	CurrDelta;
};

///�������³ɽ�����
struct CQTestFtdcMarketDataLastMatchField
{
	///���¼�
	TQTestFtdcPriceType	LastPrice;
	///����
	TQTestFtdcVolumeType	Volume;
	///�ɽ����
	TQTestFtdcMoneyType	Turnover;
	///�ֲ���
	TQTestFtdcLargeVolumeType	OpenInterest;
};

///�������ż�����
struct CQTestFtdcMarketDataBestPriceField
{
	///�����һ
	TQTestFtdcPriceType	BidPrice1;
	///������һ
	TQTestFtdcVolumeType	BidVolume1;
	///������һ
	TQTestFtdcPriceType	AskPrice1;
	///������һ
	TQTestFtdcVolumeType	AskVolume1;
};

///�����������������
struct CQTestFtdcMarketDataBid23Field
{
	///����۶�
	TQTestFtdcPriceType	BidPrice2;
	///��������
	TQTestFtdcVolumeType	BidVolume2;
	///�������
	TQTestFtdcPriceType	BidPrice3;
	///��������
	TQTestFtdcVolumeType	BidVolume3;
};

///������������������
struct CQTestFtdcMarketDataAsk23Field
{
	///�����۶�
	TQTestFtdcPriceType	AskPrice2;
	///��������
	TQTestFtdcVolumeType	AskVolume2;
	///��������
	TQTestFtdcPriceType	AskPrice3;
	///��������
	TQTestFtdcVolumeType	AskVolume3;
};

///���������ġ�������
struct CQTestFtdcMarketDataBid45Field
{
	///�������
	TQTestFtdcPriceType	BidPrice4;
	///��������
	TQTestFtdcVolumeType	BidVolume4;
	///�������
	TQTestFtdcPriceType	BidPrice5;
	///��������
	TQTestFtdcVolumeType	BidVolume5;
};

///���������ġ�������
struct CQTestFtdcMarketDataAsk45Field
{
	///��������
	TQTestFtdcPriceType	AskPrice4;
	///��������
	TQTestFtdcVolumeType	AskVolume4;
	///��������
	TQTestFtdcPriceType	AskPrice5;
	///��������
	TQTestFtdcVolumeType	AskVolume5;
};

///�������ʱ������
struct CQTestFtdcMarketDataUpdateTimeField
{
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///����޸�ʱ��
	TQTestFtdcTimeType	UpdateTime;
	///����޸ĺ���
	TQTestFtdcMillisecType	UpdateMillisec;
};

///����
struct CQTestFtdcQuoteField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///���۱��
	TQTestFtdcQuoteSysIDType	QuoteSysID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///��������
	TQTestFtdcVolumeType	BidVolume;
	///��������
	TQTestFtdcVolumeType	AskVolume;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///���ر��۱��
	TQTestFtdcOrderLocalIDType	QuoteLocalID;
	///ҵ��Ԫ
	TQTestFtdcBusinessUnitType	BusinessUnit;
	///����Ͽ�ƽ��־
	TQTestFtdcCombOffsetFlagType	BidCombOffsetFlag;
	///������ױ���־
	TQTestFtdcCombHedgeFlagType	BidCombHedgeFlag;
	///�򷽼۸�
	TQTestFtdcPriceType	BidPrice;
	///������Ͽ�ƽ��־
	TQTestFtdcCombOffsetFlagType	AskCombOffsetFlag;
	///��������ױ���־
	TQTestFtdcCombHedgeFlagType	AskCombHedgeFlag;
	///�����۸�
	TQTestFtdcPriceType	AskPrice;
	///����ʱ��
	TQTestFtdcTimeType	InsertTime;
	///����ʱ��
	TQTestFtdcTimeType	CancelTime;
	///�ɽ�ʱ��
	TQTestFtdcTimeType	TradeTime;
	///�򷽱������
	TQTestFtdcOrderSysIDType	BidOrderSysID;
	///�����������
	TQTestFtdcOrderSysIDType	AskOrderSysID;
	///�����Ա���
	TQTestFtdcParticipantIDType	ClearingPartID;
};

///�ɽ�
struct CQTestFtdcTradeField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///�ɽ����
	TQTestFtdcTradeIDType	TradeID;
	///��������
	TQTestFtdcDirectionType	Direction;
	///�������
	TQTestFtdcOrderSysIDType	OrderSysID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///���׽�ɫ
	TQTestFtdcTradingRoleType	TradingRole;
	///�ʽ��ʺ�
	TQTestFtdcAccountIDType	AccountID;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///��ƽ��־
	TQTestFtdcOffsetFlagType	OffsetFlag;
	///Ͷ���ױ���־
	TQTestFtdcHedgeFlagType	HedgeFlag;
	///�۸�
	TQTestFtdcPriceType	Price;
	///����
	TQTestFtdcVolumeType	Volume;
	///�ɽ�ʱ��
	TQTestFtdcTimeType	TradeTime;
	///�ɽ�����
	TQTestFtdcTradeTypeType	TradeType;
	///�ɽ�����Դ
	TQTestFtdcPriceSourceType	PriceSource;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///���ر������
	TQTestFtdcOrderLocalIDType	OrderLocalID;
	///�����Ա���
	TQTestFtdcParticipantIDType	ClearingPartID;
	///ҵ��Ԫ
	TQTestFtdcBusinessUnitType	BusinessUnit;
};

///����
struct CQTestFtdcOrderField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///�������
	TQTestFtdcOrderSysIDType	OrderSysID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///�����۸�����
	TQTestFtdcOrderPriceTypeType	OrderPriceType;
	///��������
	TQTestFtdcDirectionType	Direction;
	///��Ͽ�ƽ��־
	TQTestFtdcCombOffsetFlagType	CombOffsetFlag;
	///���Ͷ���ױ���־
	TQTestFtdcCombHedgeFlagType	CombHedgeFlag;
	///�۸�
	TQTestFtdcPriceType	LimitPrice;
	///����
	TQTestFtdcVolumeType	VolumeTotalOriginal;
	///��Ч������
	TQTestFtdcTimeConditionType	TimeCondition;
	///GTD����
	TQTestFtdcDateType	GTDDate;
	///�ɽ�������
	TQTestFtdcVolumeConditionType	VolumeCondition;
	///��С�ɽ���
	TQTestFtdcVolumeType	MinVolume;
	///��������
	TQTestFtdcContingentConditionType	ContingentCondition;
	///ֹ���
	TQTestFtdcPriceType	StopPrice;
	///ǿƽԭ��
	TQTestFtdcForceCloseReasonType	ForceCloseReason;
	///���ر������
	TQTestFtdcOrderLocalIDType	OrderLocalID;
	///�Զ������־
	TQTestFtdcBoolType	IsAutoSuspend;
	///������Դ
	TQTestFtdcOrderSourceType	OrderSource;
	///����״̬
	TQTestFtdcOrderStatusType	OrderStatus;
	///��������
	TQTestFtdcOrderTypeType	OrderType;
	///��ɽ�����
	TQTestFtdcVolumeType	VolumeTraded;
	///ʣ������
	TQTestFtdcVolumeType	VolumeTotal;
	///��������
	TQTestFtdcDateType	InsertDate;
	///����ʱ��
	TQTestFtdcTimeType	InsertTime;
	///����ʱ��
	TQTestFtdcTimeType	ActiveTime;
	///����ʱ��
	TQTestFtdcTimeType	SuspendTime;
	///����޸�ʱ��
	TQTestFtdcTimeType	UpdateTime;
	///����ʱ��
	TQTestFtdcTimeType	CancelTime;
	///����޸Ľ����û�����
	TQTestFtdcUserIDType	ActiveUserID;
	///����Ȩ
	TQTestFtdcPriorityType	Priority;
	///��ʱ���Ŷӵ����
	TQTestFtdcTimeSortIDType	TimeSortID;
	///�����Ա���
	TQTestFtdcParticipantIDType	ClearingPartID;
	///ҵ��Ԫ
	TQTestFtdcBusinessUnitType	BusinessUnit;
};

///ִ������
struct CQTestFtdcExecOrderField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///��Լ���
	TQTestFtdcInstrumentIDType	InstrumentID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///����ִ��������
	TQTestFtdcOrderLocalIDType	ExecOrderLocalID;
	///����
	TQTestFtdcVolumeType	Volume;
	///ҵ��Ԫ
	TQTestFtdcBusinessUnitType	BusinessUnit;
	///ִ��������
	TQTestFtdcExecOrderSysIDType	ExecOrderSysID;
	///��������
	TQTestFtdcDateType	InsertDate;
	///����ʱ��
	TQTestFtdcTimeType	InsertTime;
	///����ʱ��
	TQTestFtdcTimeType	CancelTime;
	///ִ�н��
	TQTestFtdcExecResultType	ExecResult;
	///�����Ա���
	TQTestFtdcParticipantIDType	ClearingPartID;
};

///�Ǳ���ϱ���
struct CQTestFtdcCombOrderField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///��ϱ������
	TQTestFtdcOrderSysIDType	CombOrderSysID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///�����û�����
	TQTestFtdcUserIDType	UserID;
	///�۸�
	TQTestFtdcPriceType	LimitPrice;
	///����
	TQTestFtdcVolumeType	VolumeTotalOriginal;
	///���ر������
	TQTestFtdcOrderLocalIDType	CombOrderLocalID;
	///ҵ��Ԫ
	TQTestFtdcBusinessUnitType	BusinessUnit;
	///��Լ����1
	TQTestFtdcInstrumentIDType	InstrumentID1;
	///��������1
	TQTestFtdcDirectionType	Direction1;
	///���ȳ���1
	TQTestFtdcLegMultipleType	LegMultiple1;
	///��ƽ��־1
	TQTestFtdcOffsetFlagType	OffsetFlag1;
	///Ͷ���ױ���־1
	TQTestFtdcHedgeFlagType	HedgeFlag1;
	///��Լ����2
	TQTestFtdcInstrumentIDType	InstrumentID2;
	///��������2
	TQTestFtdcDirectionType	Direction2;
	///���ȳ���2
	TQTestFtdcLegMultipleType	LegMultiple2;
	///��ƽ��־2
	TQTestFtdcOffsetFlagType	OffsetFlag2;
	///Ͷ���ױ���־2
	TQTestFtdcHedgeFlagType	HedgeFlag2;
	///��Լ����3
	TQTestFtdcInstrumentIDType	InstrumentID3;
	///��������3
	TQTestFtdcDirectionType	Direction3;
	///���ȳ���3
	TQTestFtdcLegMultipleType	LegMultiple3;
	///��ƽ��־3
	TQTestFtdcOffsetFlagType	OffsetFlag3;
	///Ͷ���ױ���־3
	TQTestFtdcHedgeFlagType	HedgeFlag3;
	///��Լ����4
	TQTestFtdcInstrumentIDType	InstrumentID4;
	///��������4
	TQTestFtdcDirectionType	Direction4;
	///���ȳ���4
	TQTestFtdcLegMultipleType	LegMultiple4;
	///��ƽ��־4
	TQTestFtdcOffsetFlagType	OffsetFlag4;
	///Ͷ���ױ���־4
	TQTestFtdcHedgeFlagType	HedgeFlag4;
	///������Դ
	TQTestFtdcOrderSourceType	OrderSource;
	///��ɽ�����
	TQTestFtdcVolumeType	VolumeTraded;
	///ʣ������
	TQTestFtdcVolumeType	VolumeTotal;
	///��������
	TQTestFtdcDateType	InsertDate;
	///����ʱ��
	TQTestFtdcTimeType	InsertTime;
	///�����Ա���
	TQTestFtdcParticipantIDType	ClearingPartID;
};

///������
struct CQTestFtdcAdminOrderField
{
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///����������
	TQTestFtdcAdminOrderCommandFlagType	AdminOrderCommand;
	///�����Ա���
	TQTestFtdcParticipantIDType	ClearingPartID;
	///���׻�Ա���
	TQTestFtdcParticipantIDType	ParticipantID;
	///���
	TQTestFtdcMoneyType	Amount;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
};

///����������
struct CQTestFtdcInputAdminOrderField
{
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///����������
	TQTestFtdcAdminOrderCommandFlagType	AdminOrderCommand;
	///�����Ա���
	TQTestFtdcParticipantIDType	ClearingPartID;
	///���׻�Ա���
	TQTestFtdcParticipantIDType	ParticipantID;
	///���
	TQTestFtdcMoneyType	Amount;
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
};

///����
struct CQTestFtdcBulletinField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///������
	TQTestFtdcBulletinIDType	BulletinID;
	///���к�
	TQTestFtdcSequenceNoType	SequenceNo;
	///��������
	TQTestFtdcNewsTypeType	NewsType;
	///�����̶�
	TQTestFtdcNewsUrgencyType	NewsUrgency;
	///����ʱ��
	TQTestFtdcTimeType	SendTime;
	///��ϢժҪ
	TQTestFtdcAbstractType	Abstract;
	///��Ϣ��Դ
	TQTestFtdcComeFromType	ComeFrom;
	///��Ϣ����
	TQTestFtdcContentType	Content;
	///WEB��ַ
	TQTestFtdcURLLinkType	URLLink;
	///�г�����
	TQTestFtdcMarketIDType	MarketID;
};

///����������ͬ��״̬
struct CQTestFtdcExchangeDataSyncStatusField
{
	///������
	TQTestFtdcDateType	TradingDay;
	///����������
	TQTestFtdcExchangeIDType	ExchangeID;
	///����������ͬ��״̬
	TQTestFtdcExchangeDataSyncStatusType	ExchangeDataSyncStatus;
};

///����������ͬ��״̬
struct CQTestFtdcSGDataSyncStatusField
{
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQTestFtdcDateType	TradingDay;
	///������
	TQTestFtdcSettlementIDType	SettlementID;
	///����������ͬ��״̬
	TQTestFtdcSGDataSyncStatusType	SGDataSyncStatus;
};

///��Լ״̬
struct CQTestFtdcInstrumentStatusField
{
	///���������
	TQTestFtdcSettlementGroupIDType	SettlementGroupID;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///��Լ����״̬
	TQTestFtdcInstrumentStatusType	InstrumentStatus;
	///���׽׶α��
	TQTestFtdcTradingSegmentSNType	TradingSegmentSN;
	///���뱾״̬ʱ��
	TQTestFtdcTimeType	EnterTime;
	///���뱾״̬ԭ��
	TQTestFtdcInstStatusEnterReasonType	EnterReason;
};

///�ͻ��ֲֲ�ѯ
struct CQTestFtdcQryClientPositionV1Field
{
	///��ʼ��Ա����
	TQTestFtdcParticipantIDType	PartIDStart;
	///������Ա����
	TQTestFtdcParticipantIDType	PartIDEnd;
	///��ʼ�ͻ�����
	TQTestFtdcClientIDType	ClientIDStart;
	///�����ͻ�����
	TQTestFtdcClientIDType	ClientIDEnd;
	///��ʼ��Լ����
	TQTestFtdcInstrumentIDType	InstIDStart;
	///������Լ����
	TQTestFtdcInstrumentIDType	InstIDEnd;
};

///ѯ��
struct CQTestFtdcInputReqForQuoteField
{
	///ѯ�۱��
	TQTestFtdcQuoteSysIDType	ReqForQuoteID;
	///��Ա����
	TQTestFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TQTestFtdcClientIDType	ClientID;
	///��Լ����
	TQTestFtdcInstrumentIDType	InstrumentID;
	///��������
	TQTestFtdcTradingDayType	TradingDay;
	///ѯ��ʱ��
	TQTestFtdcTimeType	ReqForQuoteTime;
};



#endif
