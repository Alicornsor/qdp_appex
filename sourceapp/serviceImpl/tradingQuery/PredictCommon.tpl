!!function!!
static char *queryNames[]=
{
	"ParticipantID",
	"ClearingPartID",
	"AccountID",
	"ClientID",
	"UserID",
	"OrderSysID",
	"CombOrderSysID",
	"QuoteSysID",
	"TradeID",
	"SettlementGroupID",
	"ProductGroupID",
	"ProductID",
	"ExchangeID",
	"MarketID",
	"BulletinID",
	"NewsType",
	"NewsUrgency",
	"InformationID",
	"Direction",
	"InsertTime",
	"TradeTime",
	"InvestorID",
	"BrokerID"
};

bool needQuery(char *name)
{
	for (int i=0;i<sizeof(queryNames)/sizeof(char *);i++)
	{
		if (!strcmp(queryNames[i],name))
		{
			return true;
		}
	}
	return false;
}

bool needQueryStartWith(char *name)
{
	if (!strcmp(name,"InstrumentID"))
	{
		return true;
	}
	return false;
}

!!endfunction!!
