// XtpData.cpp: 
//
///20090118	hwp		增加了查询的日志（NT-0065）
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "XtpData.h"
#include "XtpPackageDesc.h"

/*** 应用业务FieldID ***/
REGISTER_FIELD(FID_Instrument, CInstrumentField, "合约");

bool CInstrumentField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=10;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"Instrument");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ProductID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ProductID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ProductName.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ProductName,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentName.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentName,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DeliveryYear.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DeliveryYear,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DeliveryMonth.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DeliveryMonth,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MaxLimitOrderVolume.getString(buf);
	thisLen=19+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MaxLimitOrderVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MinLimitOrderVolume.getString(buf);
	thisLen=19+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MinLimitOrderVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MaxMarketOrderVolume.getString(buf);
	thisLen=20+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MaxMarketOrderVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MinMarketOrderVolume.getString(buf);
	thisLen=20+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MinMarketOrderVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	VolumeMultiple.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",VolumeMultiple,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PriceTick.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PriceTick,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Currency.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Currency,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LongPosLimit.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LongPosLimit,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ShortPosLimit.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ShortPosLimit,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LowerLimitPrice.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LowerLimitPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UpperLimitPrice.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UpperLimitPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreSettlementPrice.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreSettlementPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentStatus.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentStatus,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CreateDate.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CreateDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenDate.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExpireDate.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExpireDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	StartDelivDate.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",StartDelivDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	EndDelivDate.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",EndDelivDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BasisPrice.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BasisPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IsTrading.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IsTrading,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UnderlyingInstrID.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UnderlyingInstrID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UnderlyingMultiple.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UnderlyingMultiple,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PositionType.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PositionType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	StrikePrice.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",StrikePrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OptionsType.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OptionsType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ProductClass.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ProductClass,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OptionsMode.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OptionsMode,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ProductGroupID.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ProductGroupID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	APIID.getString(buf);
	thisLen=5+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",APIID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LegQty.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LegQty,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_InstrumentStatus, CInstrumentStatusField, "合约状态");

bool CInstrumentStatusField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=16;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"InstrumentStatus");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ProductID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ProductID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ProductName.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ProductName,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentName.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentName,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DeliveryYear.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DeliveryYear,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DeliveryMonth.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DeliveryMonth,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MaxLimitOrderVolume.getString(buf);
	thisLen=19+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MaxLimitOrderVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MinLimitOrderVolume.getString(buf);
	thisLen=19+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MinLimitOrderVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MaxMarketOrderVolume.getString(buf);
	thisLen=20+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MaxMarketOrderVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MinMarketOrderVolume.getString(buf);
	thisLen=20+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MinMarketOrderVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	VolumeMultiple.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",VolumeMultiple,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PriceTick.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PriceTick,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Currency.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Currency,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LongPosLimit.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LongPosLimit,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ShortPosLimit.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ShortPosLimit,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LowerLimitPrice.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LowerLimitPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UpperLimitPrice.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UpperLimitPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreSettlementPrice.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreSettlementPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentStatus.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentStatus,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CreateDate.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CreateDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenDate.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExpireDate.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExpireDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	StartDelivDate.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",StartDelivDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	EndDelivDate.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",EndDelivDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BasisPrice.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BasisPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IsTrading.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IsTrading,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UnderlyingInstrID.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UnderlyingInstrID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UnderlyingMultiple.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UnderlyingMultiple,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PositionType.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PositionType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	StrikePrice.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",StrikePrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OptionsType.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OptionsType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ProductClass.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ProductClass,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OptionsMode.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OptionsMode,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ProductGroupID.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ProductGroupID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	APIID.getString(buf);
	thisLen=5+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",APIID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LegQty.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LegQty,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_Exchange, CExchangeField, "交易所");

bool CExchangeField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=8;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"Exchange");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeName.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeName,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_ClientTradingID, CClientTradingIDField, "客户交易编码");

bool CClientTradingIDField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=15;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"ClientTradingID");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ParticipantID.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ParticipantID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientRight.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientRight,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientType.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientHedgeFlag.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientHedgeFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IsActive.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IsActive,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	APIID.getString(buf);
	thisLen=5+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",APIID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_InvestorMargin, CInvestorMarginField, "投资者保证金率");

bool CInvestorMarginField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=14;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"InvestorMargin");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	HedgeFlag.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",HedgeFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LongMarginRate.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LongMarginRate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LongMarginAmt.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LongMarginAmt,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ShortMarginRate.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ShortMarginRate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ShortMarginAmt.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ShortMarginAmt,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_InvestorPosition, CInvestorPositionField, "投资者合约持仓");

bool CInvestorPositionField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=16;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"InvestorPosition");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ParticipantID.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ParticipantID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Direction.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Direction,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	HedgeFlag.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",HedgeFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UsedMargin.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UsedMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Position.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Position,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PositionCost.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PositionCost,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	YdPosition.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",YdPosition,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	YdPositionCost.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",YdPositionCost,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenMargin.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenPosition.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenPosition,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenClosing.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenClosing,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenPremium.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenPremium,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LastTradeID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LastTradeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LastOrderLocalID.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LastOrderLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Currency.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Currency,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PositionProfit.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PositionProfit,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TodayPosition.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TodayPosition,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenTodayClosing.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenTodayClosing,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeType.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LastPrice.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LastPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PositionClose.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PositionClose,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	YdPositionClose.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",YdPositionClose,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	YdFrozenClosing.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",YdFrozenClosing,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CacalProfitPosition.getString(buf);
	thisLen=19+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CacalProfitPosition,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OptionType.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OptionType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	StrikePrice.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",StrikePrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OptionInstrumentID.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OptionInstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TodayPositionCost.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TodayPositionCost,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ShortPosition.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ShortPosition,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_InvestorFee, CInvestorFeeField, "投资者手续费");

bool CInvestorFeeField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=11;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"InvestorFee");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	HedgeFlag.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",HedgeFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenFeeRate.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenFeeRate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenFeeAmt.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenFeeAmt,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OffsetFeeRate.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OffsetFeeRate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OffsetFeeAmt.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OffsetFeeAmt,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OTFeeRate.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OTFeeRate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OTFeeAmt.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OTFeeAmt,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_UserInvestor, CUserInvestorField, "用户投资者关系");

bool CUserInvestorField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=12;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"UserInvestor");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	GrantFuncSet.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",GrantFuncSet,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_Investor, CInvestorField, "投资者");

bool CInvestorField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=8;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"Investor");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorName.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorName,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_InvestorAccount, CInvestorAccountField, "投资者资金账户");

bool CInvestorAccountField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=15;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"InvestorAccount");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreBalance.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreBalance,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreAvailable.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreAvailable,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Deposit.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Deposit,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Withdraw.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Withdraw,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Margin.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Margin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Premium.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Premium,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Fee.getString(buf);
	thisLen=3+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Fee,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenMargin.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenPremium.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenPremium,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenFee.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenFee,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CloseProfit.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CloseProfit,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PositionProfit.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PositionProfit,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Available.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Available,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Balance.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Balance,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LongMargin.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LongMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ShortMargin.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ShortMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LongFrozenMargin.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LongFrozenMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ShortFrozenMargin.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ShortFrozenMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DynamicRights.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DynamicRights,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Risk.getString(buf);
	thisLen=4+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Risk,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OtherFee.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OtherFee,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Mortgage.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Mortgage,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Currency.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Currency,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TotalFrozenPos.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TotalFrozenPos,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TodayInOut.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TodayInOut,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ReleaseMargin.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ReleaseMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IsProfitCanUse.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IsProfitCanUse,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ManualFrozen.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ManualFrozen,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_Money, CMoneyField, "保证金手续费");

bool CMoneyField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=5;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"Money");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	Margin.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Margin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Fee.getString(buf);
	thisLen=3+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Fee,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Premium.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Premium,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MarginChanged.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MarginChanged,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenMarginChanged.getString(buf);
	thisLen=19+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenMarginChanged,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UsedMargin.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UsedMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_ExCapitalData, CExCapitalDataField, "客户资金信息");

bool CExCapitalDataField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=13;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"ExCapitalData");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreBalance.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreBalance,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreAvailable.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreAvailable,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Deposit.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Deposit,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Withdraw.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Withdraw,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Margin.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Margin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Premium.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Premium,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Fee.getString(buf);
	thisLen=3+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Fee,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenMargin.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenPremium.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenPremium,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenFee.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenFee,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CloseProfit.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CloseProfit,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PositionProfit.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PositionProfit,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Available.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Available,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Balance.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Balance,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LongMargin.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LongMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ShortMargin.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ShortMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LongFrozenMargin.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LongFrozenMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ShortFrozenMargin.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ShortFrozenMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DynamicRights.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DynamicRights,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Risk.getString(buf);
	thisLen=4+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Risk,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OtherFee.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OtherFee,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Mortgage.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Mortgage,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Currency.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Currency,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TotalFrozenPos.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TotalFrozenPos,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TodayInOut.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TodayInOut,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ReleaseMargin.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ReleaseMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IsProfitCanUse.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IsProfitCanUse,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ManualFrozen.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ManualFrozen,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_MBLMarketData, CMBLMarketDataField, "分价行情应答");

bool CMBLMarketDataField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=13;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"MBLMarketData");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Direction.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Direction,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Price.getString(buf);
	thisLen=5+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Price,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Volume.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Volume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UpdateTime.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UpdateTime,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UpdateMillisec.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UpdateMillisec,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryMBLMarketData, CQryMBLMarketDataField, "分价行情请求");

bool CQryMBLMarketDataField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=16;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryMBLMarketData");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstIDStart.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstIDStart,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstIDEnd.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstIDEnd,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Direction.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Direction,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogBrokerID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogBrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogUserID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_User, CUserField, "用户");

bool CUserField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=4;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"User");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Password.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Password,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IsActive.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IsActive,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserName.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserName,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserType.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Department.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Department,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	GrantFuncSet.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",GrantFuncSet,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CheckIpMacAddr.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CheckIpMacAddr,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_UserLogin, CUserLoginField, "用户登录");

bool CUserLoginField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=9;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"UserLogin");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Password.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Password,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserProductInfo.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserProductInfo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InterfaceProductInfo.getString(buf);
	thisLen=20+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InterfaceProductInfo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ProtocolInfo.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ProtocolInfo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IPAddress.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IPAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MacAddress.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MacAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DataCenterID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DataCenterID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OneTimePassword.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OneTimePassword,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientIPAddress.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientIPAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LoginTime.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LoginTime,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MaxOrderLocalID.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MaxOrderLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradingSystemName.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingSystemName,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserType.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MaxCommFlux.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MaxCommFlux,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SessionID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SessionID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrontID.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrontID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SockID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SockID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientTradingDay.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientTradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Heartbeat.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Heartbeat,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DialogSeqno.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DialogSeqno,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PrivateSeqno.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PrivateSeqno,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PublicSeqno.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PublicSeqno,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LifeCycleID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LifeCycleID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_UserSession, CUserSessionField, "用户会话");

bool CUserSessionField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=11;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"UserSession");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserType.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SessionID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SessionID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrontID.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrontID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LoginTime.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LoginTime,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IPAddress.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IPAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MacAddress.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MacAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserProductInfo.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserProductInfo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InterfaceProductInfo.getString(buf);
	thisLen=20+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InterfaceProductInfo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ProtocolInfo.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ProtocolInfo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_UserLogout, CUserLogoutField, "用户登录退出");

bool CUserLogoutField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=10;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"UserLogout");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogoutReason.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogoutReason,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrontID.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrontID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SessionID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SessionID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_Seat, CSeatField, "席位");

bool CSeatField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=4;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"Seat");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	APIID.getString(buf);
	thisLen=5+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",APIID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ParticipantID.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ParticipantID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SeatID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SeatID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SeatPassword.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SeatPassword,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ApiLinkType.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ApiLinkType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	RecvRtn.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",RecvRtn,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MainSeat.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MainSeat,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	QueryBase.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",QueryBase,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	QueryPosition.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",QueryPosition,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ResumeType.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ResumeType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Heartbeat.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Heartbeat,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IsActive.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IsActive,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	RiskCheck.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",RiskCheck,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrontAddr.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrontAddr,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SeatStatus.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SeatStatus,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderLocalID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LinkBrokerID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LinkBrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CheckTradingDay.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CheckTradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Custom.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Custom,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_UserTradingRight, CUserTradingRightField, "用户交易权限");

bool CUserTradingRightField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=16;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"UserTradingRight");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradingRight.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingRight,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_UserPasswordUpdate, CUserPasswordUpdateField, "用户口令修改");

bool CUserPasswordUpdateField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=18;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"UserPasswordUpdate");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OldPassword.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OldPassword,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	NewPassword.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",NewPassword,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_ForceUserExit, CForceUserExitField, "强制用户退出");

bool CForceUserExitField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=13;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"ForceUserExit");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_LoginInfo, CLoginInfoField, "登陆通知");

bool CLoginInfoField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=9;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"LoginInfo");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	ParticipantID.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ParticipantID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SeatID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SeatID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderLocalID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LifeCycleID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LifeCycleID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_InputOrder, CInputOrderField, "输入报单");

bool CInputOrderField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=10;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"InputOrder");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderSysID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderSysID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserOrderLocalID.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserOrderLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderPriceType.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderPriceType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Direction.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Direction,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OffsetFlag.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OffsetFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	HedgeFlag.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",HedgeFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LimitPrice.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LimitPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Volume.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Volume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TimeCondition.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TimeCondition,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	GTDDate.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",GTDDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	VolumeCondition.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",VolumeCondition,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MinVolume.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MinVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	StopPrice.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",StopPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ForceCloseReason.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ForceCloseReason,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IsAutoSuspend.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IsAutoSuspend,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BusinessUnit.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BusinessUnit,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserCustom.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserCustom,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BranchID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BranchID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	RecNum.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",RecNum,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BusinessType.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BusinessType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ParticipantID.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ParticipantID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SeatID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SeatID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InsertTime.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InsertTime,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderLocalID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderSource.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderSource,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderStatus.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderStatus,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CancelTime.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CancelTime,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CancelUserID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CancelUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	VolumeTraded.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",VolumeTraded,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	VolumeRemain.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",VolumeRemain,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrontID.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrontID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SessionID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SessionID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenFee.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenFee,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenMargin.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenPremium.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenPremium,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderUserID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeType.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DealFlag.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DealFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeCommision.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeCommision,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeAmnt.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeAmnt,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CancleVolume.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CancleVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	RequestID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",RequestID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	APIID.getString(buf);
	thisLen=5+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",APIID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IPAddress.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IPAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MacAddress.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MacAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FTdRecvDown.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FTdRecvDown,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CoreRecvDown.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CoreRecvDown,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CoreSendUp.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CoreSendUp,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CoreRecvUp.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CoreRecvUp,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CoreSendDown.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CoreSendDown,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FTdSendDown.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FTdSendDown,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MarginCombType.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MarginCombType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentGroupID.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentGroupID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_OrderAction, COrderActionField, "报单操作");

bool COrderActionField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=11;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"OrderAction");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderSysID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderSysID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserOrderActionLocalID.getString(buf);
	thisLen=22+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserOrderActionLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserOrderLocalID.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserOrderLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ActionFlag.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ActionFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LimitPrice.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LimitPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	VolumeChange.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",VolumeChange,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	RecNum.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",RecNum,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrontID.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrontID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SessionID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SessionID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserCustom.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserCustom,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SeatID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SeatID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ActionLocalID.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ActionLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ParticipantID.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ParticipantID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CancelTime.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CancelTime,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ActionSource.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ActionSource,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Tradable.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Tradable,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderLocalID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IsForgeRtn.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IsForgeRtn,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	APIID.getString(buf);
	thisLen=5+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",APIID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IPAddress.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IPAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MacAddress.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MacAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderActionType.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderActionType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderBatchNo.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderBatchNo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_Trade, CTradeField, "成交");

bool CTradeField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=5;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"Trade");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ParticipantID.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ParticipantID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SeatID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SeatID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeID.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderSysID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderSysID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserOrderLocalID.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserOrderLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Direction.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Direction,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OffsetFlag.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OffsetFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	HedgeFlag.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",HedgeFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradePrice.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradePrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeVolume.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeTime.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeTime,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClearingPartID.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClearingPartID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeAmnt.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeAmnt,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	RecNum.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",RecNum,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeType.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Commision.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Commision,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	StampTax.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",StampTax,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TransferFee.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TransferFee,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UsedFee.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UsedFee,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UsedMargin.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UsedMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Premium.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Premium,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderUserID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderLocalID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IsForgeRtn.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IsForgeRtn,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BusinessType.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BusinessType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_Order, COrderField, "报单");

bool COrderField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=5;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"Order");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderSysID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderSysID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserOrderLocalID.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserOrderLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderPriceType.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderPriceType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Direction.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Direction,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OffsetFlag.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OffsetFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	HedgeFlag.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",HedgeFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LimitPrice.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LimitPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Volume.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Volume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TimeCondition.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TimeCondition,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	GTDDate.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",GTDDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	VolumeCondition.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",VolumeCondition,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MinVolume.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MinVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	StopPrice.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",StopPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ForceCloseReason.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ForceCloseReason,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IsAutoSuspend.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IsAutoSuspend,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BusinessUnit.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BusinessUnit,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserCustom.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserCustom,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BranchID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BranchID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	RecNum.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",RecNum,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BusinessType.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BusinessType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ParticipantID.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ParticipantID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SeatID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SeatID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InsertTime.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InsertTime,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderLocalID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderSource.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderSource,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderStatus.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderStatus,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CancelTime.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CancelTime,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CancelUserID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CancelUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	VolumeTraded.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",VolumeTraded,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	VolumeRemain.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",VolumeRemain,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrontID.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrontID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SessionID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SessionID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenFee.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenFee,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenMargin.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenPremium.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenPremium,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderUserID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeType.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DealFlag.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DealFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeCommision.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeCommision,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeAmnt.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeAmnt,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CancleVolume.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CancleVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	RequestID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",RequestID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	APIID.getString(buf);
	thisLen=5+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",APIID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IPAddress.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IPAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MacAddress.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MacAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FTdRecvDown.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FTdRecvDown,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CoreRecvDown.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CoreRecvDown,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CoreSendUp.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CoreSendUp,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CoreRecvUp.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CoreRecvUp,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CoreSendDown.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CoreSendDown,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FTdSendDown.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FTdSendDown,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MarginCombType.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MarginCombType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentGroupID.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentGroupID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_MarketData, CMarketDataField, "市场行情");

bool CMarketDataField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=10;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"MarketData");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenPrice.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	HighestPrice.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",HighestPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LowestPrice.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LowestPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LastPrice.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LastPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Volume.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Volume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Turnover.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Turnover,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LowerLimitPrice.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LowerLimitPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UpperLimitPrice.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UpperLimitPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenInterest.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenInterest,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreClosePrice.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreClosePrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreOpenInterest.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreOpenInterest,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreSettlementPrice.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreSettlementPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SettlementPrice.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SettlementPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UpdateMillisec.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UpdateMillisec,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UpdateTime.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UpdateTime,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_MarketDataLastMatch, CMarketDataLastMatchField, "行情最新成交属性");

bool CMarketDataLastMatchField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=19;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"MarketDataLastMatch");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LastPrice.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LastPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Volume.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Volume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_DepthMarketData, CDepthMarketDataField, "市场深度行情");

bool CDepthMarketDataField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=15;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"DepthMarketData");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SettlementGroupID.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SettlementGroupID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SettlementID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SettlementID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreSettlementPrice.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreSettlementPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreClosePrice.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreClosePrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreOpenInterest.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreOpenInterest,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreDelta.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreDelta,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenPrice.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	HighestPrice.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",HighestPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LowestPrice.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LowestPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClosePrice.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClosePrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UpperLimitPrice.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UpperLimitPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LowerLimitPrice.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LowerLimitPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SettlementPrice.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SettlementPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CurrDelta.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CurrDelta,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LastPrice.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LastPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Volume.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Volume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Turnover.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Turnover,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenInterest.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenInterest,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidPrice1.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidPrice1,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidVolume1.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidVolume1,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskPrice1.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskPrice1,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskVolume1.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskVolume1,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidPrice2.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidPrice2,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidVolume2.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidVolume2,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidPrice3.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidPrice3,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidVolume3.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidVolume3,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskPrice2.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskPrice2,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskVolume2.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskVolume2,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskPrice3.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskPrice3,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskVolume3.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskVolume3,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidPrice4.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidPrice4,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidVolume4.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidVolume4,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidPrice5.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidPrice5,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidVolume5.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidVolume5,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskPrice4.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskPrice4,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskVolume4.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskVolume4,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskPrice5.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskPrice5,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskVolume5.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskVolume5,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UpdateTime.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UpdateTime,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UpdateMillisec.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UpdateMillisec,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskPrice6.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskPrice6,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskVolume6.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskVolume6,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskPrice7.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskPrice7,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskVolume7.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskVolume7,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskPrice8.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskPrice8,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskVolume8.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskVolume8,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskPrice9.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskPrice9,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskVolume9.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskVolume9,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidPrice6.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidPrice6,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidVolume6.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidVolume6,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidPrice7.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidPrice7,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidVolume7.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidVolume7,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidPrice8.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidPrice8,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidVolume8.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidVolume8,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidPrice9.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidPrice9,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidVolume9.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidVolume9,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskPrice10.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskPrice10,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskVolume10.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskVolume10,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidPrice10.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidPrice10,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidVolume10.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidVolume10,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_RspMarketData, CRspMarketDataField, "行情查询应答");

bool CRspMarketDataField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=13;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"RspMarketData");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SettlementGroupID.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SettlementGroupID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SettlementID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SettlementID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreSettlementPrice.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreSettlementPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreClosePrice.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreClosePrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreOpenInterest.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreOpenInterest,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PreDelta.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PreDelta,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenPrice.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	HighestPrice.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",HighestPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LowestPrice.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LowestPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClosePrice.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClosePrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UpperLimitPrice.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UpperLimitPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LowerLimitPrice.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LowerLimitPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SettlementPrice.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SettlementPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CurrDelta.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CurrDelta,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LastPrice.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LastPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Volume.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Volume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Turnover.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Turnover,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenInterest.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenInterest,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidPrice1.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidPrice1,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BidVolume1.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BidVolume1,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskPrice1.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskPrice1,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AskVolume1.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AskVolume1,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UpdateTime.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UpdateTime,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UpdateMillisec.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UpdateMillisec,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryOrder, CQryOrderField, "报单查询");

bool CQryOrderField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=8;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryOrder");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderSysID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderSysID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogBrokerID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogBrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogUserID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryOrderInsertFailed, CQryOrderInsertFailedField, "错单查询");

bool CQryOrderInsertFailedField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=20;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryOrderInsertFailed");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderSysID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderSysID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogBrokerID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogBrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogUserID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryTrade, CQryTradeField, "成交查询");

bool CQryTradeField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=8;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryTrade");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeID.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogBrokerID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogBrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogUserID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryInvestor, CQryInvestorField, "投资者查询");

bool CQryInvestorField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=11;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryInvestor");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogBrokerID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogBrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogUserID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryInvestorAccount, CQryInvestorAccountField, "投资者资金查询");

bool CQryInvestorAccountField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=18;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryInvestorAccount");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogBrokerID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogBrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogUserID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SeatID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SeatID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryInstrument, CQryInstrumentField, "合约查询");

bool CQryInstrumentField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=13;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryInstrument");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ProductID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ProductID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryUser, CQryUserField, "用户查询");

bool CQryUserField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=7;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryUser");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	StartUserID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",StartUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	EndUserID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",EndUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryInvestorPosition, CQryInvestorPositionField, "投资者持仓请求");

bool CQryInvestorPositionField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=19;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryInvestorPosition");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SeatID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SeatID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogBrokerID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogBrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogUserID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryUserInvestor, CQryUserInvestorField, "可用投资者账户查询");

bool CQryUserInvestorField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=15;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryUserInvestor");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogBrokerID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogBrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogUserID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryExchange, CQryExchangeField, "交易所查询");

bool CQryExchangeField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=11;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryExchange");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_RspInfo, CRspInfoField, "响应信息");

bool CRspInfoField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=7;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"RspInfo");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	ErrorID.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ErrorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ErrorMsg.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ErrorMsg,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_RspExchange, CRspExchangeField, "交易所应答");

bool CRspExchangeField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=11;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"RspExchange");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeName.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeName,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryMarketData, CQryMarketDataField, "行情查询");

bool CQryMarketDataField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=13;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryMarketData");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryInvestorFee, CQryInvestorFeeField, "投资者手续费率查询");

bool CQryInvestorFeeField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=14;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryInvestorFee");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	HedgeFlag.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",HedgeFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogBrokerID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogBrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogUserID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryInvestorMargin, CQryInvestorMarginField, "投资者保证金率查询");

bool CQryInvestorMarginField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=17;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryInvestorMargin");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	HedgeFlag.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",HedgeFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogBrokerID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogBrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogUserID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QrySGEDeferRate, CQrySGEDeferRateField, "金交所递延费率查询请求");

bool CQrySGEDeferRateField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=15;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QrySGEDeferRate");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_SGEDeferRate, CSGEDeferRateField, "金交所递延费率查询应答");

bool CSGEDeferRateField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=12;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"SGEDeferRate");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeDate.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Direction.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Direction,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DeferRate.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DeferRate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_CommPhase, CCommPhaseField, "通讯阶段");

bool CCommPhaseField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=9;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"CommPhase");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CommPhaseNo.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CommPhaseNo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_TradingDay, CTradingDayField, "交易日");

bool CTradingDayField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=10;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"TradingDay");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_CurrentTime, CCurrentTimeField, "当前时间");

bool CCurrentTimeField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=11;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"CurrentTime");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	CurrDate.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CurrDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CurrTime.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CurrTime,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CurrMillisec.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CurrMillisec,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_LifeCycleID, CLifeCycleIDField, "生命周期号");

bool CLifeCycleIDField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=11;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"LifeCycleID");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	LifeCycleID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LifeCycleID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_MemDb, CMemDbField, "内存表导出");

bool CMemDbField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=5;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"MemDb");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	MemTableName.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MemTableName,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_SystemStatus, CSystemStatusField, "系统状态");

bool CSystemStatusField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=12;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"SystemStatus");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SystemStatus.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SystemStatus,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_DataSyncStatus, CDataSyncStatusField, "系统数据同步状态");

bool CDataSyncStatusField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=14;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"DataSyncStatus");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DataSyncStatus.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DataSyncStatus,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SystemID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SystemID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_DbmtInvestorAccountDeposit, CDbmtInvestorAccountDepositField, "Dbmt投资者资金帐户入金");

bool CDbmtInvestorAccountDepositField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=26;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"DbmtInvestorAccountDeposit");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountSeqNo.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountSeqNo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountInsideSeqNo.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountInsideSeqNo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Amount.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Amount,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AmountDirection.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AmountDirection,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DbmtTopicID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DbmtTopicID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DbmtSequenceID.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DbmtSequenceID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_DbmtUser, CDbmtUserField, "Dbmt用户");

bool CDbmtUserField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=8;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"DbmtUser");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Password.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Password,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IsActive.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IsActive,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserName.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserName,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserType.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Department.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Department,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	GrantFuncSet.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",GrantFuncSet,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CheckIpMacAddr.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CheckIpMacAddr,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DbmtTopicID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DbmtTopicID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DbmtSequenceID.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DbmtSequenceID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_MemtableChange, CMemtableChangeField, "内存表变化");

bool CMemtableChangeField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=14;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"MemtableChange");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	MemtableChangeType.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MemtableChangeType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MemTableName.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MemTableName,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_ExchangeTradingDay, CExchangeTradingDayField, "交易所交易日");

bool CExchangeTradingDayField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=18;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"ExchangeTradingDay");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_InvestorAccountDepositNtf, CInvestorAccountDepositNtfField, "出入金回报通知");

bool CInvestorAccountDepositNtfField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=25;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"InvestorAccountDepositNtf");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountSeqNo.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountSeqNo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountInsideSeqNo.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountInsideSeqNo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Amount.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Amount,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AmountDirection.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AmountDirection,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Available.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Available,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Balance.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Balance,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_OrderInsertFailed, COrderInsertFailedField, "错单表");

bool COrderInsertFailedField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=17;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"OrderInsertFailed");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderSysID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderSysID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserOrderLocalID.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserOrderLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderPriceType.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderPriceType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Direction.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Direction,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OffsetFlag.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OffsetFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	HedgeFlag.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",HedgeFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LimitPrice.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LimitPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Volume.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Volume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TimeCondition.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TimeCondition,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	GTDDate.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",GTDDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	VolumeCondition.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",VolumeCondition,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MinVolume.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MinVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	StopPrice.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",StopPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ForceCloseReason.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ForceCloseReason,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IsAutoSuspend.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IsAutoSuspend,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BusinessUnit.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BusinessUnit,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserCustom.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserCustom,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BranchID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BranchID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	RecNum.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",RecNum,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BusinessType.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BusinessType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ParticipantID.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ParticipantID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SeatID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SeatID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InsertTime.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InsertTime,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderLocalID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderSource.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderSource,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderStatus.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderStatus,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CancelTime.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CancelTime,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CancelUserID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CancelUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	VolumeTraded.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",VolumeTraded,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	VolumeRemain.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",VolumeRemain,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrontID.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrontID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SessionID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SessionID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenFee.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenFee,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenMargin.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FrozenPremium.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FrozenPremium,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OrderUserID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OrderUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeType.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DealFlag.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DealFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeCommision.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeCommision,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeAmnt.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeAmnt,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CancleVolume.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CancleVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	RequestID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",RequestID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	APIID.getString(buf);
	thisLen=5+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",APIID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IPAddress.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IPAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MacAddress.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MacAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FTdRecvDown.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FTdRecvDown,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CoreRecvDown.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CoreRecvDown,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CoreSendUp.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CoreSendUp,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CoreRecvUp.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CoreRecvUp,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CoreSendDown.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CoreSendDown,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	FTdSendDown.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",FTdSendDown,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MarginCombType.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MarginCombType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentGroupID.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentGroupID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ErrorMsg.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ErrorMsg,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_InstrumentGroup, CInstrumentGroupField, "合约和合约组关系");

bool CInstrumentGroupField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=15;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"InstrumentGroup");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentGroupID.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentGroupID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_ClientMarginCombType, CClientMarginCombTypeField, "交易编码组合保证金类型");

bool CClientMarginCombTypeField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=20;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"ClientMarginCombType");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ParticipantID.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ParticipantID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentGroupID.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentGroupID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MarginCombType.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MarginCombType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_InterLoginInfo, CInterLoginInfoField, "登录信息");

bool CInterLoginInfoField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=14;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"InterLoginInfo");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	ServerAddr.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ServerAddr,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MaxLocalID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MaxLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_MessageNotifyInfo, CMessageNotifyInfoField, "QDP警告消息通知");

bool CMessageNotifyInfoField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=17;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"MessageNotifyInfo");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Nums.getString(buf);
	thisLen=4+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Nums,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	BusinessType.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BusinessType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	WarnMsg.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",WarnMsg,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_AccountDeposit, CAccountDepositField, "出入金请求");

bool CAccountDepositField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=14;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"AccountDeposit");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountSeqNo.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountSeqNo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountInsideSeqNo.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountInsideSeqNo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Amount.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Amount,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AmountDirection.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AmountDirection,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_AccountDepositRes, CAccountDepositResField, "出入金应答");

bool CAccountDepositResField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=17;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"AccountDepositRes");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountSeqNo.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountSeqNo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountInsideSeqNo.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountInsideSeqNo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Amount.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Amount,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AmountDirection.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AmountDirection,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Available.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Available,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Balance.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Balance,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QueryFinishNotify, CQueryFinishNotifyField, "报盘机查询结束消息通知");

bool CQueryFinishNotifyField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=17;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QueryFinishNotify");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MaxOrderLocalID.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MaxOrderLocalID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	APIID.getString(buf);
	thisLen=5+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",APIID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ApiLinkType.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ApiLinkType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_DbmtClientTradingID, CDbmtClientTradingIDField, "Dbmt客户交易编码交易权限");

bool CDbmtClientTradingIDField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=19;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"DbmtClientTradingID");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	AccountID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",AccountID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ParticipantID.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ParticipantID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientRight.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientRight,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientType.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ClientHedgeFlag.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ClientHedgeFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IsActive.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IsActive,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	APIID.getString(buf);
	thisLen=5+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",APIID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DbmtTopicID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DbmtTopicID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DbmtSequenceID.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DbmtSequenceID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_CmbInstrumentDetail, CCmbInstrumentDetailField, "组合合约明细");

bool CCmbInstrumentDetailField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=19;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"CmbInstrumentDetail");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ArbiInstrumentID.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ArbiInstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SingleInstrumentID.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SingleInstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LegNo.getString(buf);
	thisLen=5+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LegNo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Direction.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Direction,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Ratio.getString(buf);
	thisLen=5+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Ratio,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_InnerLogin, CInnerLoginField, "内部登陆信息");

bool CInnerLoginField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=10;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"InnerLogin");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	SequenceNo.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SequenceNo,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_InvestorTradingRight, CInvestorTradingRightField, "投资者交易权限");

bool CInvestorTradingRightField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=20;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"InvestorTradingRight");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradingRight.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingRight,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ProductClass.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ProductClass,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_DbmtInvestorTradingRight, CDbmtInvestorTradingRightField, "Dbmt投资者权限");

bool CDbmtInvestorTradingRightField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=24;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"DbmtInvestorTradingRight");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradingRight.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingRight,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ProductClass.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ProductClass,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DbmtTopicID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DbmtTopicID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DbmtSequenceID.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DbmtSequenceID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_UserIP, CUserIPField, "用户IP");

bool CUserIPField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=6;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"UserIP");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IPAddress.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IPAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IPMask.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IPMask,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MacAddress.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MacAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_DbmtUserIP, CDbmtUserIPField, "Dbmt用户IP");

bool CDbmtUserIPField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=10;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"DbmtUserIP");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IPAddress.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IPAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	IPMask.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",IPMask,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MacAddress.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MacAddress,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DbmtTopicID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DbmtTopicID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	DbmtSequenceID.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",DbmtSequenceID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryInvestorPositionDetail, CQryInvestorPositionDetailField, "投资者持仓明细查询请求");

bool CQryInvestorPositionDetailField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=25;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryInvestorPositionDetail");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogBrokerID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogBrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogUserID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_RspInvestorPositionDetail, CRspInvestorPositionDetailField, "投资者持仓明细应答");

bool CRspInvestorPositionDetailField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=25;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"RspInvestorPositionDetail");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	HedgeFlag.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",HedgeFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Direction.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Direction,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenDate.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeID.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Volume.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Volume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenPrice.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeType.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CombInstrumentID.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CombInstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CloseProfitByDate.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CloseProfitByDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CloseProfitByTrade.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CloseProfitByTrade,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PositionProfitByDate.getString(buf);
	thisLen=20+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PositionProfitByDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PositionProfitByTrade.getString(buf);
	thisLen=21+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PositionProfitByTrade,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Margin.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Margin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchMargin.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MarginRateByMoney.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MarginRateByMoney,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MarginRateByVolume.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MarginRateByVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LastSettlementPrice.getString(buf);
	thisLen=19+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LastSettlementPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SettlementPrice.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SettlementPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CloseVolume.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CloseVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CloseAmount.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CloseAmount,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_InvestorPositionDetail, CInvestorPositionDetailField, "投资者持仓明细");

bool CInvestorPositionDetailField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=22;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"InvestorPositionDetail");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	HedgeFlag.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",HedgeFlag,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Direction.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Direction,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenDate.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeID.getString(buf);
	thisLen=7+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Volume.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Volume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenPrice.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradingDay.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradingDay,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	TradeType.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",TradeType,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CombInstrumentID.getString(buf);
	thisLen=16+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CombInstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CloseProfitByDate.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CloseProfitByDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CloseProfitByTrade.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CloseProfitByTrade,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PositionProfitByDate.getString(buf);
	thisLen=20+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PositionProfitByDate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PositionProfitByTrade.getString(buf);
	thisLen=21+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PositionProfitByTrade,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	Margin.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",Margin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchMargin.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchMargin,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MarginRateByMoney.getString(buf);
	thisLen=17+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MarginRateByMoney,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	MarginRateByVolume.getString(buf);
	thisLen=18+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",MarginRateByVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LastSettlementPrice.getString(buf);
	thisLen=19+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LastSettlementPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SettlementPrice.getString(buf);
	thisLen=15+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SettlementPrice,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CloseVolume.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CloseVolume,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	CloseAmount.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",CloseAmount,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_QryInvestorOptionFee, CQryInvestorOptionFeeField, "投资者期权手续费查询请求");

bool CQryInvestorOptionFeeField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=20;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"QryInvestorOptionFee");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	UserID.getString(buf);
	thisLen=6+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",UserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogBrokerID.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogBrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	LogUserID.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",LogUserID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_InvestorOptionFee, CInvestorOptionFeeField, "投资者期权手续费");

bool CInvestorOptionFeeField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=17;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"InvestorOptionFee");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	ExchangeID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",ExchangeID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InstrumentID.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InstrumentID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenFeeRate.getString(buf);
	thisLen=11+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenFeeRate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OpenFeeAmt.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OpenFeeAmt,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OffsetFeeRate.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OffsetFeeRate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OffsetFeeAmt.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OffsetFeeAmt,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OTFeeRate.getString(buf);
	thisLen=9+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OTFeeRate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	OTFeeAmt.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",OTFeeAmt,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	StrikeFeeRate.getString(buf);
	thisLen=13+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",StrikeFeeRate,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	StrikeFeeAmt.getString(buf);
	thisLen=12+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",StrikeFeeAmt,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_PositionProfit, CPositionProfitField, "投资者持仓盈亏");

bool CPositionProfitField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=14;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"PositionProfit");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	BrokerID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",BrokerID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	InvestorID.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",InvestorID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	PositionProfit.getString(buf);
	thisLen=14+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",PositionProfit,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

REGISTER_FIELD(FID_SystemInfo, CSystemInfoField, "QDP系统信息");

bool CSystemInfoField::dumpLine(char *buffer, int len)
{
	char *pos=buffer;
	int nameLen=10;
	int thisLen;
	if (len<nameLen+1)
	{
		buffer[0]='\0';
		return false;
	}
	strcpy(pos,"SystemInfo");
	pos+=nameLen;
	len-=nameLen;

	char buf[4000];
	SystemID.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SystemID,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SystemName.getString(buf);
	thisLen=10+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SystemName,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	SystemIP.getString(buf);
	thisLen=8+strlen(buf)+2;
	if (len<thisLen+1)
	{
		return false;
	}
	sprintf(pos,",SystemIP,%s",buf);	
	pos+=thisLen;
	len-=thisLen;
	
	return true;
}

