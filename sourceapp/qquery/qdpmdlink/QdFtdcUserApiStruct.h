/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file QdFtdcUserApiStruct.h
///@brief �����˿ͻ��˽ӿ�ʹ�õ�ҵ�����ݽṹ
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(Qd_FTDCSTRUCT_H)
#define Qd_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QdFtdcUserApiDataType.h"

///��Ӧ��Ϣ
struct CQdFtdcRspInfoField
{
	///�������
	TQdFtdcErrorIDType	ErrorID;
	///������Ϣ
	TQdFtdcErrorMsgType	ErrorMsg;
};

///Qdp��Ӧ��Ϣ
struct CQdFtdcQdpRspInfoField
{
	///�������
	TQdFtdcErrorIDType	ErrorID;
	///������Ϣ
	TQdFtdcQdpErrorMsgType	ErrorMsg;
};

///ϵͳ�û���¼����
struct CQdFtdcReqUserLoginField
{
	///������
	TQdFtdcDateType	TradingDay;
	///�����û�����
	TQdFtdcUserIDType	UserID;
	///���͹�˾���
	TQdFtdcBrokerIDType	BrokerID;
	///����
	TQdFtdcPasswordType	Password;
	///�û��˲�Ʒ��Ϣ
	TQdFtdcProductInfoType	UserProductInfo;
	///�ӿڶ˲�Ʒ��Ϣ
	TQdFtdcProductInfoType	InterfaceProductInfo;
	///Э����Ϣ
	TQdFtdcProtocolInfoType	ProtocolInfo;
	///IP��ַ
	TQdFtdcIPAddressType	IPAddress;
	///Mac��ַ
	TQdFtdcMacAddressType	MacAddress;
	///�������Ĵ���
	TQdFtdcDataCenterIDType	DataCenterID;
	///��̬����
	TQdFtdcPasswordType	OneTimePassword;
	///�ն�IP��ַ
	TQdFtdcIPAddressType	ClientIPAddress;
	///��Ȩ����
	TQdFtdcAuthCodeType	AuthCode;
};

///Qdpϵͳ�û���¼����
struct CQdFtdcQdpReqUserLoginField
{
	///������
	TQdFtdcDateType	TradingDay;
	///�����û�����
	TQdFtdcQdpUserIDType	UserID;
	///���͹�˾���
	TQdFtdcBrokerIDType	BrokerID;
	///����
	TQdFtdcPasswordType	Password;
	///�û��˲�Ʒ��Ϣ
	TQdFtdcQdpProductInfoType	UserProductInfo;
	///�ӿڶ˲�Ʒ��Ϣ
	TQdFtdcQdpProductInfoType	InterfaceProductInfo;
	///Э����Ϣ
	TQdFtdcProtocolInfoType	ProtocolInfo;
	///IP��ַ
	TQdFtdcIPAddressType	IPAddress;
	///Mac��ַ
	TQdFtdcMacAddressType	MacAddress;
	///�������Ĵ���
	TQdFtdcDataCenterIDType	DataCenterID;
	///��̬����
	TQdFtdcPasswordType	OneTimePassword;
	///�ն�IP��ַ
	TQdFtdcIPAddressType	ClientIPAddress;
};

///ϵͳ�û���¼Ӧ��
struct CQdFtdcRspUserLoginField
{
	///������
	TQdFtdcDateType	TradingDay;
	///���͹�˾���
	TQdFtdcBrokerIDType	BrokerID;
	///�����û�����
	TQdFtdcUserIDType	UserID;
	///��¼�ɹ�ʱ��
	TQdFtdcTimeType	LoginTime;
	///�û���󱾵ر�����
	TQdFtdcUserOrderLocalIDType	MaxOrderLocalID;
	///����ϵͳ����
	TQdFtdcTradingSystemNameType	TradingSystemName;
	///�������Ĵ���
	TQdFtdcDataCenterIDType	DataCenterID;
	///��Ա˽������ǰ����
	TQdFtdcSequenceNoType	PrivateFlowSize;
	///����Ա˽������ǰ����
	TQdFtdcSequenceNoType	UserFlowSize;
	///��¼������Ϣ
	TQdFtdcLoginInfoType	LoginInfo;
	///�Ự���
	TQdFtdcSessionIDType	SessionID;
	///ǰ�ñ��
	TQdFtdcFrontIDType	FrontID;
};

///Qdpϵͳ�û���¼Ӧ��
struct CQdFtdcQdpRspUserLoginField
{
	///������
	TQdFtdcDateType	TradingDay;
	///���͹�˾���
	TQdFtdcBrokerIDType	BrokerID;
	///�����û�����
	TQdFtdcQdpUserIDType	UserID;
	///��¼�ɹ�ʱ��
	TQdFtdcTimeType	LoginTime;
	///�û���󱾵ر�����
	TQdFtdcUserOrderLocalIDType	MaxOrderLocalID;
	///����ϵͳ����
	TQdFtdcTradingSystemNameType	TradingSystemName;
	///�������Ĵ���
	TQdFtdcDataCenterIDType	DataCenterID;
	///��Ա˽������ǰ����
	TQdFtdcSequenceNoType	PrivateFlowSize;
	///����Ա˽������ǰ����
	TQdFtdcSequenceNoType	UserFlowSize;
	///�Ự���
	TQdFtdcSessionIDType	SessionID;
	///ǰ�ñ��
	TQdFtdcFrontIDType	FrontID;
};

///�û��ǳ�����
struct CQdFtdcReqUserLogoutField
{
	///���͹�˾���
	TQdFtdcBrokerIDType	BrokerID;
	///�����û�����
	TQdFtdcUserIDType	UserID;
};

///�û��ǳ�����
struct CQdFtdcRspUserLogoutField
{
	///���͹�˾���
	TQdFtdcBrokerIDType	BrokerID;
	///�����û�����
	TQdFtdcUserIDType	UserID;
};

///�����������
struct CQdFtdcMarketDataBaseField
{
	///������
	TQdFtdcTradingDayType	TradingDay;
	///�����
	TQdFtdcPriceType	PreSettlementPrice;
	///������
	TQdFtdcPriceType	PreClosePrice;
	///��ֲ���
	TQdFtdcLargeVolumeType	PreOpenInterest;
	///����ʵ��
	TQdFtdcRatioType	PreDelta;
};

///Qdp�����������
struct CQdFtdcQdpMarketDataBaseField
{
	///������
	TQdFtdcTradingDayType	TradingDay;
	///���������
	TQdFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQdFtdcSettlementIDType	SettlementID;
	///�����
	TQdFtdcPriceType	PreSettlementPrice;
	///������
	TQdFtdcPriceType	PreClosePrice;
	///��ֲ���
	TQdFtdcLargeVolumeType	PreOpenInterest;
	///����ʵ��
	TQdFtdcRatioType	PreDelta;
};

///���龲̬����
struct CQdFtdcMarketDataStaticField
{
	///����
	TQdFtdcPriceType	OpenPrice;
	///��߼�
	TQdFtdcPriceType	HighestPrice;
	///��ͼ�
	TQdFtdcPriceType	LowestPrice;
	///������
	TQdFtdcPriceType	ClosePrice;
	///��ͣ���
	TQdFtdcPriceType	UpperLimitPrice;
	///��ͣ���
	TQdFtdcPriceType	LowerLimitPrice;
	///�����
	TQdFtdcPriceType	SettlementPrice;
	///����ʵ��
	TQdFtdcRatioType	CurrDelta;
};

///�������³ɽ�����
struct CQdFtdcMarketDataLastMatchField
{
	///���¼�
	TQdFtdcPriceType	LastPrice;
	///����
	TQdFtdcVolumeType	Volume;
	///�ɽ����
	TQdFtdcMoneyType	Turnover;
	///�ֲ���
	TQdFtdcLargeVolumeType	OpenInterest;
};

///�������ż�����
struct CQdFtdcMarketDataBestPriceField
{
	///�����һ
	TQdFtdcPriceType	BidPrice1;
	///������һ
	TQdFtdcVolumeType	BidVolume1;
	///������һ
	TQdFtdcPriceType	AskPrice1;
	///������һ
	TQdFtdcVolumeType	AskVolume1;
};

///�����������������
struct CQdFtdcMarketDataBid23Field
{
	///����۶�
	TQdFtdcPriceType	BidPrice2;
	///��������
	TQdFtdcVolumeType	BidVolume2;
	///�������
	TQdFtdcPriceType	BidPrice3;
	///��������
	TQdFtdcVolumeType	BidVolume3;
};

///������������������
struct CQdFtdcMarketDataAsk23Field
{
	///�����۶�
	TQdFtdcPriceType	AskPrice2;
	///��������
	TQdFtdcVolumeType	AskVolume2;
	///��������
	TQdFtdcPriceType	AskPrice3;
	///��������
	TQdFtdcVolumeType	AskVolume3;
};

///���������ġ�������
struct CQdFtdcMarketDataBid45Field
{
	///�������
	TQdFtdcPriceType	BidPrice4;
	///��������
	TQdFtdcVolumeType	BidVolume4;
	///�������
	TQdFtdcPriceType	BidPrice5;
	///��������
	TQdFtdcVolumeType	BidVolume5;
};

///���������ġ�������
struct CQdFtdcMarketDataAsk45Field
{
	///��������
	TQdFtdcPriceType	AskPrice4;
	///��������
	TQdFtdcVolumeType	AskVolume4;
	///��������
	TQdFtdcPriceType	AskPrice5;
	///��������
	TQdFtdcVolumeType	AskVolume5;
};

///�������ʱ������
struct CQdFtdcMarketDataUpdateTimeField
{
	///��Լ����
	TQdFtdcInstrumentIDType	InstrumentID;
	///����޸�ʱ��
	TQdFtdcTimeType	UpdateTime;
	///����޸ĺ���
	TQdFtdcMillisecType	UpdateMillisec;
};

///�������
struct CQdFtdcDepthMarketDataField
{
	///������
	TQdFtdcTradingDayType	TradingDay;
	///�����
	TQdFtdcPriceType	PreSettlementPrice;
	///������
	TQdFtdcPriceType	PreClosePrice;
	///��ֲ���
	TQdFtdcLargeVolumeType	PreOpenInterest;
	///����ʵ��
	TQdFtdcRatioType	PreDelta;
	///����
	TQdFtdcPriceType	OpenPrice;
	///��߼�
	TQdFtdcPriceType	HighestPrice;
	///��ͼ�
	TQdFtdcPriceType	LowestPrice;
	///������
	TQdFtdcPriceType	ClosePrice;
	///��ͣ���
	TQdFtdcPriceType	UpperLimitPrice;
	///��ͣ���
	TQdFtdcPriceType	LowerLimitPrice;
	///�����
	TQdFtdcPriceType	SettlementPrice;
	///����ʵ��
	TQdFtdcRatioType	CurrDelta;
	///���¼�
	TQdFtdcPriceType	LastPrice;
	///����
	TQdFtdcVolumeType	Volume;
	///�ɽ����
	TQdFtdcMoneyType	Turnover;
	///�ֲ���
	TQdFtdcLargeVolumeType	OpenInterest;
	///�����һ
	TQdFtdcPriceType	BidPrice1;
	///������һ
	TQdFtdcVolumeType	BidVolume1;
	///������һ
	TQdFtdcPriceType	AskPrice1;
	///������һ
	TQdFtdcVolumeType	AskVolume1;
	///����۶�
	TQdFtdcPriceType	BidPrice2;
	///��������
	TQdFtdcVolumeType	BidVolume2;
	///�������
	TQdFtdcPriceType	BidPrice3;
	///��������
	TQdFtdcVolumeType	BidVolume3;
	///�����۶�
	TQdFtdcPriceType	AskPrice2;
	///��������
	TQdFtdcVolumeType	AskVolume2;
	///��������
	TQdFtdcPriceType	AskPrice3;
	///��������
	TQdFtdcVolumeType	AskVolume3;
	///�������
	TQdFtdcPriceType	BidPrice4;
	///��������
	TQdFtdcVolumeType	BidVolume4;
	///�������
	TQdFtdcPriceType	BidPrice5;
	///��������
	TQdFtdcVolumeType	BidVolume5;
	///��������
	TQdFtdcPriceType	AskPrice4;
	///��������
	TQdFtdcVolumeType	AskVolume4;
	///��������
	TQdFtdcPriceType	AskPrice5;
	///��������
	TQdFtdcVolumeType	AskVolume5;
	///��Լ����
	TQdFtdcInstrumentIDType	InstrumentID;
	///����޸�ʱ��
	TQdFtdcTimeType	UpdateTime;
	///����޸ĺ���
	TQdFtdcMillisecType	UpdateMillisec;
	///����������
	TQdFtdcExchangeIDType	ExchangeID;
	///����������
	TQdFtdcVolumeType	VolumeAskLot;
	///����������
	TQdFtdcVolumeType	VolumeBidLot;
	///��Լ״̬
	TQdFtdcInstrumentStatusType	InstrumentStatus;
};

///�������
struct CQdFtdcQdpDepthMarketDataField
{
	///������
	TQdFtdcTradingDayType	TradingDay;
	///���������
	TQdFtdcSettlementGroupIDType	SettlementGroupID;
	///������
	TQdFtdcSettlementIDType	SettlementID;
	///�����
	TQdFtdcPriceType	PreSettlementPrice;
	///������
	TQdFtdcPriceType	PreClosePrice;
	///��ֲ���
	TQdFtdcLargeVolumeType	PreOpenInterest;
	///����ʵ��
	TQdFtdcRatioType	PreDelta;
	///����
	TQdFtdcPriceType	OpenPrice;
	///��߼�
	TQdFtdcPriceType	HighestPrice;
	///��ͼ�
	TQdFtdcPriceType	LowestPrice;
	///������
	TQdFtdcPriceType	ClosePrice;
	///��ͣ���
	TQdFtdcPriceType	UpperLimitPrice;
	///��ͣ���
	TQdFtdcPriceType	LowerLimitPrice;
	///�����
	TQdFtdcPriceType	SettlementPrice;
	///����ʵ��
	TQdFtdcRatioType	CurrDelta;
	///���¼�
	TQdFtdcPriceType	LastPrice;
	///����
	TQdFtdcVolumeType	Volume;
	///�ɽ����
	TQdFtdcMoneyType	Turnover;
	///�ֲ���
	TQdFtdcLargeVolumeType	OpenInterest;
	///�����һ
	TQdFtdcPriceType	BidPrice1;
	///������һ
	TQdFtdcVolumeType	BidVolume1;
	///������һ
	TQdFtdcPriceType	AskPrice1;
	///������һ
	TQdFtdcVolumeType	AskVolume1;
	///����۶�
	TQdFtdcPriceType	BidPrice2;
	///��������
	TQdFtdcVolumeType	BidVolume2;
	///�������
	TQdFtdcPriceType	BidPrice3;
	///��������
	TQdFtdcVolumeType	BidVolume3;
	///�����۶�
	TQdFtdcPriceType	AskPrice2;
	///��������
	TQdFtdcVolumeType	AskVolume2;
	///��������
	TQdFtdcPriceType	AskPrice3;
	///��������
	TQdFtdcVolumeType	AskVolume3;
	///�������
	TQdFtdcPriceType	BidPrice4;
	///��������
	TQdFtdcVolumeType	BidVolume4;
	///�������
	TQdFtdcPriceType	BidPrice5;
	///��������
	TQdFtdcVolumeType	BidVolume5;
	///��������
	TQdFtdcPriceType	AskPrice4;
	///��������
	TQdFtdcVolumeType	AskVolume4;
	///��������
	TQdFtdcPriceType	AskPrice5;
	///��������
	TQdFtdcVolumeType	AskVolume5;
	///��Լ����
	TQdFtdcInstrumentIDType	InstrumentID;
	///����޸�ʱ��
	TQdFtdcTimeType	UpdateTime;
	///����޸ĺ���
	TQdFtdcMillisecType	UpdateMillisec;
	///����������
	TQdFtdcExchangeIDType	ExchangeID;
};

///���ĺ�Լ�������Ϣ
struct CQdFtdcSpecificInstrumentField
{
	///��Լ����
	TQdFtdcInstrumentIDType	InstrumentID;
};

///����������
struct CQdFtdcMarketDataExchangeIDField
{
	///����������
	TQdFtdcExchangeIDType	ExchangeID;
};

///Qdp����������
struct CQdFtdcQdpMarketDataExchangeIDField
{
	///����������
	TQdFtdcExchangeIDType	ExchangeID;
};

///�����ڴ������ѯ
struct CQdFtdcShmDepthMarketDataField
{
	///��Լ����
	TQdFtdcInstrumentIDType	InstrumentID;
	///IP��ַ
	TQdFtdcIPAddressType	IPAddress;
	///���ĺ�
	TQdFtdcTopicIDType	TopicID;
};

///TOPIC��ѯ
struct CQdFtdcTopicSearchField
{
	///���ĺ�
	TQdFtdcTopicIDType	TopicID;
};

///�ּ�����
struct CQdFtdcMBLMarketDataField
{
	///��Լ����
	TQdFtdcInstrumentIDType	InstrumentID;
	///��������
	TQdFtdcDirectionType	Direction;
	///�۸�
	TQdFtdcPriceType	Price;
	///����
	TQdFtdcVolumeType	Volume;
	///����޸�ʱ��
	TQdFtdcTimeType	UpdateTime;
	///����޸ĺ���
	TQdFtdcMillisecType	UpdateMillisec;
};

///������Լ��������
struct CQdFtdcMarketDataCMBVolumeField
{
	///����������
	TQdFtdcVolumeType	VolumeAskLot;
	///����������
	TQdFtdcVolumeType	VolumeBidLot;
};

///��Լ״̬
struct CQdFtdcQmdInstrumentStateField
{
	///����������
	TQdFtdcExchangeIDType	ExchangeID;
	///��Լ����
	TQdFtdcInstrumentIDType	InstrumentID;
	///��Լ����״̬
	TQdFtdcInstrumentStatusType	InstrumentStatus;
};

///�����Լ״̬
struct CQdFtdcMarketDataInstrumentStatusField
{
	///��Լ״̬
	TQdFtdcInstrumentStatusType	InstrumentStatus;
};

///��Ϣ�ַ�
struct CQdFtdcDisseminationField
{
	///����ϵ�к�
	TQdFtdcSequenceSeriesType	SequenceSeries;
	///���к�
	TQdFtdcSequenceNoType	SequenceNo;
};

///Qdp��Ϣ�ַ�
struct CQdFtdcQdpDisseminationField
{
	///����ϵ�к�
	TQdFtdcSequenceSeriesType	SequenceSeries;
	///���к�
	TQdFtdcSequenceNoType	SequenceNo;
};

///�����ѯ
struct CQdFtdcQryMarketDataField
{
	///����������
	TQdFtdcExchangeIDType	ExchangeID;
	///��Լ����
	TQdFtdcInstrumentIDType	InstrumentID;
};

///����Ӧ��
struct CQdFtdcRspMarketDataField
{
	///����������
	TQdFtdcExchangeIDType	ExchangeID;
	///������
	TQdFtdcTradingDayType	TradingDay;
	///�����
	TQdFtdcPriceType	PreSettlementPrice;
	///������
	TQdFtdcPriceType	PreClosePrice;
	///��ֲ���
	TQdFtdcLargeVolumeType	PreOpenInterest;
	///����ʵ��
	TQdFtdcRatioType	PreDelta;
	///����
	TQdFtdcPriceType	OpenPrice;
	///��߼�
	TQdFtdcPriceType	HighestPrice;
	///��ͼ�
	TQdFtdcPriceType	LowestPrice;
	///������
	TQdFtdcPriceType	ClosePrice;
	///��ͣ���
	TQdFtdcPriceType	UpperLimitPrice;
	///��ͣ���
	TQdFtdcPriceType	LowerLimitPrice;
	///�����
	TQdFtdcPriceType	SettlementPrice;
	///����ʵ��
	TQdFtdcRatioType	CurrDelta;
	///���¼�
	TQdFtdcPriceType	LastPrice;
	///����
	TQdFtdcVolumeType	Volume;
	///�ɽ����
	TQdFtdcMoneyType	Turnover;
	///�ֲ���
	TQdFtdcLargeVolumeType	OpenInterest;
	///�����һ
	TQdFtdcPriceType	BidPrice1;
	///������һ
	TQdFtdcVolumeType	BidVolume1;
	///������һ
	TQdFtdcPriceType	AskPrice1;
	///������һ
	TQdFtdcVolumeType	AskVolume1;
	///��Լ����
	TQdFtdcInstrumentIDType	InstrumentID;
	///����޸�ʱ��
	TQdFtdcTimeType	UpdateTime;
	///����޸ĺ���
	TQdFtdcMillisecType	UpdateMillisec;
	///��Լ״̬
	TQdFtdcInstrumentStatusType	InstrumentStatus;
};



#endif
