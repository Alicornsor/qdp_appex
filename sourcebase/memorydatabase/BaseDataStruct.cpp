/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file BaseDataStruct.cpp
///@brief实现了内存数据库用的基本数据结构类，以及iterator、trigger的基类
///@history 
///20121227	hwp		创建该文件
///		为了NT-0058的需要，增加了读入CSV时自动识别双引号的功能
/////////////////////////////////////////////////////////////////////////

#include "BaseDataStruct.h"
#include "databaseFactories.h"

int compare(const char *s1, const char *s2)
{
	int result=strcmp(s1,s2);
	if (result>0)
		return 1;
	else if (result<0)
		return -1;
	return 0;
}

int compare(const int v1,const int v2)
{
	if (v1>v2)
		return 1;
	if (v1<v2)
		return -1;
	return 0;
}

int compare(const long v1,const long v2)
{
	if (v1>v2)
		return 1;
	if (v1<v2)
		return -1;
	return 0;
}

int compare(const double v1,const double v2)
{
	if (v1>v2+SMALL_DOUBLE)
		return 1;
	if (v1<v2-SMALL_DOUBLE)
		return -1;
	return 0;
}

char *getNextToken(char *buffer)
{
	static char *last;
	char *from, *to;
	
	if (buffer==NULL)
	{
		from=last;
		if (from==NULL)
		{
			return NULL;
		}
	}
	else
	{
		from=buffer;
	}
	
	bool hasQuote=false;
	if (*from=='"')
	{
		from++;
		hasQuote=true;
	}
	to=from;
	while ((*to!='\0')&&(*to!=',')&&(*to!='\n'))
	{
		if (hasQuote && (*to=='"'))
		{
			to++;
			break;
		}
		to++;
	}
	if (*to!=',')
	{
		last=NULL;
	}
	else
	{
		last=to+1;
	}
	if (!hasQuote)
	{
		*to='\0';
	}
	else
	{
		*(to-1)='\0';
	}
	return from;
}


void CWriteableDataSyncStatus::writeCSVHead(FILE *output)
{
	fprintf(output,"TradingDay,DataSyncStatus,SystemID\n");
}
	
void CWriteableDataSyncStatus::init(void)
{
	TradingDay.clear();
	DataSyncStatus.clear();
	SystemID.clear();
}

int CWriteableDataSyncStatus::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableDataSyncStatus),input)!=sizeof(CWriteableDataSyncStatus))
		return 0;
	else
		return 1;
}
	
int CWriteableDataSyncStatus::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			TradingDay=token;
		}
		else
		{
			TradingDay="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			DataSyncStatus=token;
		}
		else
		{
			DataSyncStatus="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SystemID=token;
		}
		else
		{
			SystemID="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"TradingDay"))
			{
				TradingDay=token;
			}
			else if (!strcmp(fieldName,"DataSyncStatus"))
			{
				DataSyncStatus=token;
			}
			else if (!strcmp(fieldName,"SystemID"))
			{
				SystemID=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableDataSyncStatus::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableDataSyncStatus),output)!=sizeof(CWriteableDataSyncStatus))
		return 0;
	else
		return 1;
}

int CWriteableDataSyncStatus::writeCSV(FILE *output) const
{
	char buffer[1025];
	TradingDay.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	DataSyncStatus.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SystemID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableDataSyncStatus::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCDataSyncStatus%s = {\n", index_buf);
	TradingDay.getString(buf);
	fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);	
	DataSyncStatus.getString(buf);
	fprintf(fp,"\t\tDataSyncStatus = %s    [数据同步状态]\n",buf);	
	SystemID.getString(buf);
	fprintf(fp,"\t\tSystemID = %s    [QDP系统编号]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableDataSyncStatus::dumpDiff(FILE *fp, const CWriteableDataSyncStatus *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCDataSyncStatus = {\n");
	TradingDay.getString(buf);
	if (compare(TradingDay.getValue(),pOriginal->TradingDay.getValue())!=0)
	{
		pOriginal->TradingDay.getString(bufOriginal);
		fprintf(fp,"\t\tTradingDay = %s -> %s    [交易日]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);
	}
	DataSyncStatus.getString(buf);
	if (compare(DataSyncStatus.getValue(),pOriginal->DataSyncStatus.getValue())!=0)
	{
		pOriginal->DataSyncStatus.getString(bufOriginal);
		fprintf(fp,"\t\tDataSyncStatus = %s -> %s    [数据同步状态]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDataSyncStatus = %s    [数据同步状态]\n",buf);
	}
	SystemID.getString(buf);
	if (compare(SystemID.getValue(),pOriginal->SystemID.getValue())!=0)
	{
		pOriginal->SystemID.getString(bufOriginal);
		fprintf(fp,"\t\tSystemID = %s -> %s    [QDP系统编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSystemID = %s    [QDP系统编号]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableDataSyncStatus::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	TradingDay.getString(buf);
	fprintf(fp,",TradingDay,%s",buf);	
	DataSyncStatus.getString(buf);
	fprintf(fp,",DataSyncStatus,%s",buf);	
	SystemID.getString(buf);
	fprintf(fp,",SystemID,%s",buf);	
}

void CWriteableDataSyncStatus::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	TradingDay.getString(buf);
	sprintf(p,"TradingDay=%s,",buf);
	p+=strlen(p);
	DataSyncStatus.getString(buf);
	sprintf(p,"DataSyncStatus=%s,",buf);
	p+=strlen(p);
	SystemID.getString(buf);
	sprintf(p,"SystemID=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableDataSyncStatus::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CDataSyncStatus");
	pLogger->output(indent,0,"{");
	TradingDay.getString(buf);
	pLogger->output(indent+1,0,"TradingDay=%s 交易日",buf);
	DataSyncStatus.getString(buf);
	pLogger->output(indent+1,0,"DataSyncStatus=%s 数据同步状态",buf);
	SystemID.getString(buf);
	pLogger->output(indent+1,0,"SystemID=%s QDP系统编号",buf);
	pLogger->output(indent,0,"}");
}

CDataSyncStatusIterator::~CDataSyncStatusIterator(void)
{
}


void CDataSyncStatusIterator::dump(FILE *output)
{
	CDataSyncStatus *pDataSyncStatus;
	
	while ((pDataSyncStatus=next())!=NULL)
	{
		pDataSyncStatus->dump(output);
	}
}



void CWriteableSystemStatus::writeCSVHead(FILE *output)
{
	fprintf(output,"TradingDay,SystemStatus\n");
}
	
void CWriteableSystemStatus::init(void)
{
	TradingDay.clear();
	SystemStatus.clear();
}

int CWriteableSystemStatus::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableSystemStatus),input)!=sizeof(CWriteableSystemStatus))
		return 0;
	else
		return 1;
}
	
int CWriteableSystemStatus::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			TradingDay=token;
		}
		else
		{
			TradingDay="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SystemStatus=token;
		}
		else
		{
			SystemStatus="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"TradingDay"))
			{
				TradingDay=token;
			}
			else if (!strcmp(fieldName,"SystemStatus"))
			{
				SystemStatus=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableSystemStatus::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableSystemStatus),output)!=sizeof(CWriteableSystemStatus))
		return 0;
	else
		return 1;
}

int CWriteableSystemStatus::writeCSV(FILE *output) const
{
	char buffer[1025];
	TradingDay.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SystemStatus.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableSystemStatus::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCSystemStatus%s = {\n", index_buf);
	TradingDay.getString(buf);
	fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);	
	SystemStatus.getString(buf);
	fprintf(fp,"\t\tSystemStatus = %s    [系统状态]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableSystemStatus::dumpDiff(FILE *fp, const CWriteableSystemStatus *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCSystemStatus = {\n");
	TradingDay.getString(buf);
	if (compare(TradingDay.getValue(),pOriginal->TradingDay.getValue())!=0)
	{
		pOriginal->TradingDay.getString(bufOriginal);
		fprintf(fp,"\t\tTradingDay = %s -> %s    [交易日]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);
	}
	SystemStatus.getString(buf);
	if (compare(SystemStatus.getValue(),pOriginal->SystemStatus.getValue())!=0)
	{
		pOriginal->SystemStatus.getString(bufOriginal);
		fprintf(fp,"\t\tSystemStatus = %s -> %s    [系统状态]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSystemStatus = %s    [系统状态]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableSystemStatus::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	TradingDay.getString(buf);
	fprintf(fp,",TradingDay,%s",buf);	
	SystemStatus.getString(buf);
	fprintf(fp,",SystemStatus,%s",buf);	
}

void CWriteableSystemStatus::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	TradingDay.getString(buf);
	sprintf(p,"TradingDay=%s,",buf);
	p+=strlen(p);
	SystemStatus.getString(buf);
	sprintf(p,"SystemStatus=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableSystemStatus::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CSystemStatus");
	pLogger->output(indent,0,"{");
	TradingDay.getString(buf);
	pLogger->output(indent+1,0,"TradingDay=%s 交易日",buf);
	SystemStatus.getString(buf);
	pLogger->output(indent+1,0,"SystemStatus=%s 系统状态",buf);
	pLogger->output(indent,0,"}");
}

CSystemStatusIterator::~CSystemStatusIterator(void)
{
}


void CSystemStatusIterator::dump(FILE *output)
{
	CSystemStatus *pSystemStatus;
	
	while ((pSystemStatus=next())!=NULL)
	{
		pSystemStatus->dump(output);
	}
}



void CWriteableOrderAction::writeCSVHead(FILE *output)
{
	fprintf(output,"ExchangeID,OrderSysID,BrokerID,InvestorID,UserID,InstrumentID,UserOrderActionLocalID,UserOrderLocalID,ActionFlag,LimitPrice,VolumeChange,RecNum,FrontID,SessionID,UserCustom,SeatID,ActionLocalID,ClientID,ParticipantID,CancelTime,ActionSource,Tradable,OrderLocalID,IsForgeRtn,APIID,IPAddress,MacAddress,OrderActionType,OrderBatchNo\n");
}
	
void CWriteableOrderAction::init(void)
{
	ExchangeID.clear();
	OrderSysID.clear();
	BrokerID.clear();
	InvestorID.clear();
	UserID.clear();
	InstrumentID.clear();
	UserOrderActionLocalID.clear();
	UserOrderLocalID.clear();
	ActionFlag.clear();
	LimitPrice.clear();
	VolumeChange.clear();
	RecNum.clear();
	FrontID.clear();
	SessionID.clear();
	UserCustom.clear();
	SeatID.clear();
	ActionLocalID.clear();
	ClientID.clear();
	ParticipantID.clear();
	CancelTime.clear();
	ActionSource.clear();
	Tradable.clear();
	OrderLocalID.clear();
	IsForgeRtn.clear();
	APIID.clear();
	IPAddress.clear();
	MacAddress.clear();
	OrderActionType.clear();
	OrderBatchNo.clear();
	pOrder=NULL;
	pPreOrder=NULL;
}

int CWriteableOrderAction::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableOrderAction),input)!=sizeof(CWriteableOrderAction))
		return 0;
	else
		return 1;
}
	
int CWriteableOrderAction::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderSysID=token;
		}
		else
		{
			OrderSysID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserID=token;
		}
		else
		{
			UserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserOrderActionLocalID=token;
		}
		else
		{
			UserOrderActionLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserOrderLocalID=token;
		}
		else
		{
			UserOrderLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ActionFlag=token;
		}
		else
		{
			ActionFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LimitPrice=token;
		}
		else
		{
			LimitPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			VolumeChange=token;
		}
		else
		{
			VolumeChange="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			RecNum=token;
		}
		else
		{
			RecNum="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrontID=token;
		}
		else
		{
			FrontID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SessionID=token;
		}
		else
		{
			SessionID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserCustom=token;
		}
		else
		{
			UserCustom="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SeatID=token;
		}
		else
		{
			SeatID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ActionLocalID=token;
		}
		else
		{
			ActionLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ClientID=token;
		}
		else
		{
			ClientID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ParticipantID=token;
		}
		else
		{
			ParticipantID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CancelTime=token;
		}
		else
		{
			CancelTime="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ActionSource=token;
		}
		else
		{
			ActionSource="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Tradable=token;
		}
		else
		{
			Tradable="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderLocalID=token;
		}
		else
		{
			OrderLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IsForgeRtn=token;
		}
		else
		{
			IsForgeRtn="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			APIID=token;
		}
		else
		{
			APIID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IPAddress=token;
		}
		else
		{
			IPAddress="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MacAddress=token;
		}
		else
		{
			MacAddress="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderActionType=token;
		}
		else
		{
			OrderActionType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderBatchNo=token;
		}
		else
		{
			OrderBatchNo="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"OrderSysID"))
			{
				OrderSysID=token;
			}
			else if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"UserID"))
			{
				UserID=token;
			}
			else if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"UserOrderActionLocalID"))
			{
				UserOrderActionLocalID=token;
			}
			else if (!strcmp(fieldName,"UserOrderLocalID"))
			{
				UserOrderLocalID=token;
			}
			else if (!strcmp(fieldName,"ActionFlag"))
			{
				ActionFlag=token;
			}
			else if (!strcmp(fieldName,"LimitPrice"))
			{
				LimitPrice=token;
			}
			else if (!strcmp(fieldName,"VolumeChange"))
			{
				VolumeChange=token;
			}
			else if (!strcmp(fieldName,"RecNum"))
			{
				RecNum=token;
			}
			else if (!strcmp(fieldName,"FrontID"))
			{
				FrontID=token;
			}
			else if (!strcmp(fieldName,"SessionID"))
			{
				SessionID=token;
			}
			else if (!strcmp(fieldName,"UserCustom"))
			{
				UserCustom=token;
			}
			else if (!strcmp(fieldName,"SeatID"))
			{
				SeatID=token;
			}
			else if (!strcmp(fieldName,"ActionLocalID"))
			{
				ActionLocalID=token;
			}
			else if (!strcmp(fieldName,"ClientID"))
			{
				ClientID=token;
			}
			else if (!strcmp(fieldName,"ParticipantID"))
			{
				ParticipantID=token;
			}
			else if (!strcmp(fieldName,"CancelTime"))
			{
				CancelTime=token;
			}
			else if (!strcmp(fieldName,"ActionSource"))
			{
				ActionSource=token;
			}
			else if (!strcmp(fieldName,"Tradable"))
			{
				Tradable=token;
			}
			else if (!strcmp(fieldName,"OrderLocalID"))
			{
				OrderLocalID=token;
			}
			else if (!strcmp(fieldName,"IsForgeRtn"))
			{
				IsForgeRtn=token;
			}
			else if (!strcmp(fieldName,"APIID"))
			{
				APIID=token;
			}
			else if (!strcmp(fieldName,"IPAddress"))
			{
				IPAddress=token;
			}
			else if (!strcmp(fieldName,"MacAddress"))
			{
				MacAddress=token;
			}
			else if (!strcmp(fieldName,"OrderActionType"))
			{
				OrderActionType=token;
			}
			else if (!strcmp(fieldName,"OrderBatchNo"))
			{
				OrderBatchNo=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableOrderAction::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableOrderAction),output)!=sizeof(CWriteableOrderAction))
		return 0;
	else
		return 1;
}

int CWriteableOrderAction::writeCSV(FILE *output) const
{
	char buffer[1025];
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderSysID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserOrderActionLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserOrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ActionFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LimitPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	VolumeChange.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	RecNum.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrontID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SessionID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserCustom.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SeatID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ActionLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ClientID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ParticipantID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CancelTime.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ActionSource.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Tradable.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IsForgeRtn.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	APIID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IPAddress.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MacAddress.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderActionType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderBatchNo.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableOrderAction::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCOrderAction%s = {\n", index_buf);
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	OrderSysID.getString(buf);
	fprintf(fp,"\t\tOrderSysID = %s    [报单编号]\n",buf);	
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);	
	UserID.getString(buf);
	fprintf(fp,"\t\tUserID = %s    [用户代码]\n",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	UserOrderActionLocalID.getString(buf);
	fprintf(fp,"\t\tUserOrderActionLocalID = %s    [本次撤单操作的本地编号]\n",buf);	
	UserOrderLocalID.getString(buf);
	fprintf(fp,"\t\tUserOrderLocalID = %s    [被撤订单的本地报单编号]\n",buf);	
	ActionFlag.getString(buf);
	fprintf(fp,"\t\tActionFlag = %s    [报单操作标志]\n",buf);	
	LimitPrice.getString(buf);
	fprintf(fp,"\t\tLimitPrice = %s    [价格]\n",buf);	
	VolumeChange.getString(buf);
	fprintf(fp,"\t\tVolumeChange = %s    [数量变化]\n",buf);	
	RecNum.getString(buf);
	fprintf(fp,"\t\tRecNum = %s    [记录编号]\n",buf);	
	FrontID.getString(buf);
	fprintf(fp,"\t\tFrontID = %s    [前置编号]\n",buf);	
	SessionID.getString(buf);
	fprintf(fp,"\t\tSessionID = %s    [会话编号]\n",buf);	
	UserCustom.getString(buf);
	fprintf(fp,"\t\tUserCustom = %s    [用户自定义域]\n",buf);	
	SeatID.getString(buf);
	fprintf(fp,"\t\tSeatID = %s    [下单席位号]\n",buf);	
	ActionLocalID.getString(buf);
	fprintf(fp,"\t\tActionLocalID = %s    [操作本地编号]\n",buf);	
	ClientID.getString(buf);
	fprintf(fp,"\t\tClientID = %s    [客户代码]\n",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,"\t\tParticipantID = %s    [会员代码]\n",buf);	
	CancelTime.getString(buf);
	fprintf(fp,"\t\tCancelTime = %s    [撤销时间]\n",buf);	
	ActionSource.getString(buf);
	fprintf(fp,"\t\tActionSource = %s    [操作来源]\n",buf);	
	Tradable.getString(buf);
	fprintf(fp,"\t\tTradable = %s    [是否可以参加交易]\n",buf);	
	OrderLocalID.getString(buf);
	fprintf(fp,"\t\tOrderLocalID = %s    [本地报单编号]\n",buf);	
	IsForgeRtn.getString(buf);
	fprintf(fp,"\t\tIsForgeRtn = %s    [伪造Rtn]\n",buf);	
	APIID.getString(buf);
	fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);	
	IPAddress.getString(buf);
	fprintf(fp,"\t\tIPAddress = %s    [下单IP地址]\n",buf);	
	MacAddress.getString(buf);
	fprintf(fp,"\t\tMacAddress = %s    [下单MAC地址]\n",buf);	
	OrderActionType.getString(buf);
	fprintf(fp,"\t\tOrderActionType = %s    [撤单对应的报单类别]\n",buf);	
	OrderBatchNo.getString(buf);
	fprintf(fp,"\t\tOrderBatchNo = %s    [报单批次号]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableOrderAction::dumpDiff(FILE *fp, const CWriteableOrderAction *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCOrderAction = {\n");
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	OrderSysID.getString(buf);
	if (compare(OrderSysID.getValue(),pOriginal->OrderSysID.getValue())!=0)
	{
		pOriginal->OrderSysID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderSysID = %s -> %s    [报单编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderSysID = %s    [报单编号]\n",buf);
	}
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);
	}
	UserID.getString(buf);
	if (compare(UserID.getValue(),pOriginal->UserID.getValue())!=0)
	{
		pOriginal->UserID.getString(bufOriginal);
		fprintf(fp,"\t\tUserID = %s -> %s    [用户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserID = %s    [用户代码]\n",buf);
	}
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	UserOrderActionLocalID.getString(buf);
	if (compare(UserOrderActionLocalID.getValue(),pOriginal->UserOrderActionLocalID.getValue())!=0)
	{
		pOriginal->UserOrderActionLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tUserOrderActionLocalID = %s -> %s    [本次撤单操作的本地编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserOrderActionLocalID = %s    [本次撤单操作的本地编号]\n",buf);
	}
	UserOrderLocalID.getString(buf);
	if (compare(UserOrderLocalID.getValue(),pOriginal->UserOrderLocalID.getValue())!=0)
	{
		pOriginal->UserOrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tUserOrderLocalID = %s -> %s    [被撤订单的本地报单编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserOrderLocalID = %s    [被撤订单的本地报单编号]\n",buf);
	}
	ActionFlag.getString(buf);
	if (compare(ActionFlag.getValue(),pOriginal->ActionFlag.getValue())!=0)
	{
		pOriginal->ActionFlag.getString(bufOriginal);
		fprintf(fp,"\t\tActionFlag = %s -> %s    [报单操作标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tActionFlag = %s    [报单操作标志]\n",buf);
	}
	LimitPrice.getString(buf);
	if (compare(LimitPrice.getValue(),pOriginal->LimitPrice.getValue())!=0)
	{
		pOriginal->LimitPrice.getString(bufOriginal);
		fprintf(fp,"\t\tLimitPrice = %s -> %s    [价格]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLimitPrice = %s    [价格]\n",buf);
	}
	VolumeChange.getString(buf);
	if (compare(VolumeChange.getValue(),pOriginal->VolumeChange.getValue())!=0)
	{
		pOriginal->VolumeChange.getString(bufOriginal);
		fprintf(fp,"\t\tVolumeChange = %s -> %s    [数量变化]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tVolumeChange = %s    [数量变化]\n",buf);
	}
	RecNum.getString(buf);
	if (compare(RecNum.getValue(),pOriginal->RecNum.getValue())!=0)
	{
		pOriginal->RecNum.getString(bufOriginal);
		fprintf(fp,"\t\tRecNum = %s -> %s    [记录编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tRecNum = %s    [记录编号]\n",buf);
	}
	FrontID.getString(buf);
	if (compare(FrontID.getValue(),pOriginal->FrontID.getValue())!=0)
	{
		pOriginal->FrontID.getString(bufOriginal);
		fprintf(fp,"\t\tFrontID = %s -> %s    [前置编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrontID = %s    [前置编号]\n",buf);
	}
	SessionID.getString(buf);
	if (compare(SessionID.getValue(),pOriginal->SessionID.getValue())!=0)
	{
		pOriginal->SessionID.getString(bufOriginal);
		fprintf(fp,"\t\tSessionID = %s -> %s    [会话编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSessionID = %s    [会话编号]\n",buf);
	}
	UserCustom.getString(buf);
	if (compare(UserCustom.getValue(),pOriginal->UserCustom.getValue())!=0)
	{
		pOriginal->UserCustom.getString(bufOriginal);
		fprintf(fp,"\t\tUserCustom = %s -> %s    [用户自定义域]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserCustom = %s    [用户自定义域]\n",buf);
	}
	SeatID.getString(buf);
	if (compare(SeatID.getValue(),pOriginal->SeatID.getValue())!=0)
	{
		pOriginal->SeatID.getString(bufOriginal);
		fprintf(fp,"\t\tSeatID = %s -> %s    [下单席位号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSeatID = %s    [下单席位号]\n",buf);
	}
	ActionLocalID.getString(buf);
	if (compare(ActionLocalID.getValue(),pOriginal->ActionLocalID.getValue())!=0)
	{
		pOriginal->ActionLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tActionLocalID = %s -> %s    [操作本地编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tActionLocalID = %s    [操作本地编号]\n",buf);
	}
	ClientID.getString(buf);
	if (compare(ClientID.getValue(),pOriginal->ClientID.getValue())!=0)
	{
		pOriginal->ClientID.getString(bufOriginal);
		fprintf(fp,"\t\tClientID = %s -> %s    [客户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tClientID = %s    [客户代码]\n",buf);
	}
	ParticipantID.getString(buf);
	if (compare(ParticipantID.getValue(),pOriginal->ParticipantID.getValue())!=0)
	{
		pOriginal->ParticipantID.getString(bufOriginal);
		fprintf(fp,"\t\tParticipantID = %s -> %s    [会员代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tParticipantID = %s    [会员代码]\n",buf);
	}
	CancelTime.getString(buf);
	if (compare(CancelTime.getValue(),pOriginal->CancelTime.getValue())!=0)
	{
		pOriginal->CancelTime.getString(bufOriginal);
		fprintf(fp,"\t\tCancelTime = %s -> %s    [撤销时间]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCancelTime = %s    [撤销时间]\n",buf);
	}
	ActionSource.getString(buf);
	if (compare(ActionSource.getValue(),pOriginal->ActionSource.getValue())!=0)
	{
		pOriginal->ActionSource.getString(bufOriginal);
		fprintf(fp,"\t\tActionSource = %s -> %s    [操作来源]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tActionSource = %s    [操作来源]\n",buf);
	}
	Tradable.getString(buf);
	if (compare(Tradable.getValue(),pOriginal->Tradable.getValue())!=0)
	{
		pOriginal->Tradable.getString(bufOriginal);
		fprintf(fp,"\t\tTradable = %s -> %s    [是否可以参加交易]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradable = %s    [是否可以参加交易]\n",buf);
	}
	OrderLocalID.getString(buf);
	if (compare(OrderLocalID.getValue(),pOriginal->OrderLocalID.getValue())!=0)
	{
		pOriginal->OrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderLocalID = %s -> %s    [本地报单编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderLocalID = %s    [本地报单编号]\n",buf);
	}
	IsForgeRtn.getString(buf);
	if (compare(IsForgeRtn.getValue(),pOriginal->IsForgeRtn.getValue())!=0)
	{
		pOriginal->IsForgeRtn.getString(bufOriginal);
		fprintf(fp,"\t\tIsForgeRtn = %s -> %s    [伪造Rtn]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIsForgeRtn = %s    [伪造Rtn]\n",buf);
	}
	APIID.getString(buf);
	if (compare(APIID.getValue(),pOriginal->APIID.getValue())!=0)
	{
		pOriginal->APIID.getString(bufOriginal);
		fprintf(fp,"\t\tAPIID = %s -> %s    [通道对应的APIID]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);
	}
	IPAddress.getString(buf);
	if (compare(IPAddress.getValue(),pOriginal->IPAddress.getValue())!=0)
	{
		pOriginal->IPAddress.getString(bufOriginal);
		fprintf(fp,"\t\tIPAddress = %s -> %s    [下单IP地址]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIPAddress = %s    [下单IP地址]\n",buf);
	}
	MacAddress.getString(buf);
	if (compare(MacAddress.getValue(),pOriginal->MacAddress.getValue())!=0)
	{
		pOriginal->MacAddress.getString(bufOriginal);
		fprintf(fp,"\t\tMacAddress = %s -> %s    [下单MAC地址]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMacAddress = %s    [下单MAC地址]\n",buf);
	}
	OrderActionType.getString(buf);
	if (compare(OrderActionType.getValue(),pOriginal->OrderActionType.getValue())!=0)
	{
		pOriginal->OrderActionType.getString(bufOriginal);
		fprintf(fp,"\t\tOrderActionType = %s -> %s    [撤单对应的报单类别]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderActionType = %s    [撤单对应的报单类别]\n",buf);
	}
	OrderBatchNo.getString(buf);
	if (compare(OrderBatchNo.getValue(),pOriginal->OrderBatchNo.getValue())!=0)
	{
		pOriginal->OrderBatchNo.getString(bufOriginal);
		fprintf(fp,"\t\tOrderBatchNo = %s -> %s    [报单批次号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderBatchNo = %s    [报单批次号]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableOrderAction::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	OrderSysID.getString(buf);
	fprintf(fp,",OrderSysID,%s",buf);	
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	UserID.getString(buf);
	fprintf(fp,",UserID,%s",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	UserOrderActionLocalID.getString(buf);
	fprintf(fp,",UserOrderActionLocalID,%s",buf);	
	UserOrderLocalID.getString(buf);
	fprintf(fp,",UserOrderLocalID,%s",buf);	
	ActionFlag.getString(buf);
	fprintf(fp,",ActionFlag,%s",buf);	
	LimitPrice.getString(buf);
	fprintf(fp,",LimitPrice,%s",buf);	
	VolumeChange.getString(buf);
	fprintf(fp,",VolumeChange,%s",buf);	
	RecNum.getString(buf);
	fprintf(fp,",RecNum,%s",buf);	
	FrontID.getString(buf);
	fprintf(fp,",FrontID,%s",buf);	
	SessionID.getString(buf);
	fprintf(fp,",SessionID,%s",buf);	
	UserCustom.getString(buf);
	fprintf(fp,",UserCustom,%s",buf);	
	SeatID.getString(buf);
	fprintf(fp,",SeatID,%s",buf);	
	ActionLocalID.getString(buf);
	fprintf(fp,",ActionLocalID,%s",buf);	
	ClientID.getString(buf);
	fprintf(fp,",ClientID,%s",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,",ParticipantID,%s",buf);	
	CancelTime.getString(buf);
	fprintf(fp,",CancelTime,%s",buf);	
	ActionSource.getString(buf);
	fprintf(fp,",ActionSource,%s",buf);	
	Tradable.getString(buf);
	fprintf(fp,",Tradable,%s",buf);	
	OrderLocalID.getString(buf);
	fprintf(fp,",OrderLocalID,%s",buf);	
	IsForgeRtn.getString(buf);
	fprintf(fp,",IsForgeRtn,%s",buf);	
	APIID.getString(buf);
	fprintf(fp,",APIID,%s",buf);	
	IPAddress.getString(buf);
	fprintf(fp,",IPAddress,%s",buf);	
	MacAddress.getString(buf);
	fprintf(fp,",MacAddress,%s",buf);	
	OrderActionType.getString(buf);
	fprintf(fp,",OrderActionType,%s",buf);	
	OrderBatchNo.getString(buf);
	fprintf(fp,",OrderBatchNo,%s",buf);	
}

void CWriteableOrderAction::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	OrderSysID.getString(buf);
	sprintf(p,"OrderSysID=%s,",buf);
	p+=strlen(p);
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	UserID.getString(buf);
	sprintf(p,"UserID=%s,",buf);
	p+=strlen(p);
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	UserOrderActionLocalID.getString(buf);
	sprintf(p,"UserOrderActionLocalID=%s,",buf);
	p+=strlen(p);
	UserOrderLocalID.getString(buf);
	sprintf(p,"UserOrderLocalID=%s,",buf);
	p+=strlen(p);
	ActionFlag.getString(buf);
	sprintf(p,"ActionFlag=%s,",buf);
	p+=strlen(p);
	LimitPrice.getString(buf);
	sprintf(p,"LimitPrice=%s,",buf);
	p+=strlen(p);
	VolumeChange.getString(buf);
	sprintf(p,"VolumeChange=%s,",buf);
	p+=strlen(p);
	RecNum.getString(buf);
	sprintf(p,"RecNum=%s,",buf);
	p+=strlen(p);
	FrontID.getString(buf);
	sprintf(p,"FrontID=%s,",buf);
	p+=strlen(p);
	SessionID.getString(buf);
	sprintf(p,"SessionID=%s,",buf);
	p+=strlen(p);
	UserCustom.getString(buf);
	sprintf(p,"UserCustom=%s,",buf);
	p+=strlen(p);
	SeatID.getString(buf);
	sprintf(p,"SeatID=%s,",buf);
	p+=strlen(p);
	ActionLocalID.getString(buf);
	sprintf(p,"ActionLocalID=%s,",buf);
	p+=strlen(p);
	ClientID.getString(buf);
	sprintf(p,"ClientID=%s,",buf);
	p+=strlen(p);
	ParticipantID.getString(buf);
	sprintf(p,"ParticipantID=%s,",buf);
	p+=strlen(p);
	CancelTime.getString(buf);
	sprintf(p,"CancelTime=%s,",buf);
	p+=strlen(p);
	ActionSource.getString(buf);
	sprintf(p,"ActionSource=%s,",buf);
	p+=strlen(p);
	Tradable.getString(buf);
	sprintf(p,"Tradable=%s,",buf);
	p+=strlen(p);
	OrderLocalID.getString(buf);
	sprintf(p,"OrderLocalID=%s,",buf);
	p+=strlen(p);
	IsForgeRtn.getString(buf);
	sprintf(p,"IsForgeRtn=%s,",buf);
	p+=strlen(p);
	APIID.getString(buf);
	sprintf(p,"APIID=%s,",buf);
	p+=strlen(p);
	IPAddress.getString(buf);
	sprintf(p,"IPAddress=%s,",buf);
	p+=strlen(p);
	MacAddress.getString(buf);
	sprintf(p,"MacAddress=%s,",buf);
	p+=strlen(p);
	OrderActionType.getString(buf);
	sprintf(p,"OrderActionType=%s,",buf);
	p+=strlen(p);
	OrderBatchNo.getString(buf);
	sprintf(p,"OrderBatchNo=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableOrderAction::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"COrderAction");
	pLogger->output(indent,0,"{");
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	OrderSysID.getString(buf);
	pLogger->output(indent+1,0,"OrderSysID=%s 报单编号",buf);
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编号",buf);
	UserID.getString(buf);
	pLogger->output(indent+1,0,"UserID=%s 用户代码",buf);
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	UserOrderActionLocalID.getString(buf);
	pLogger->output(indent+1,0,"UserOrderActionLocalID=%s 本次撤单操作的本地编号",buf);
	UserOrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"UserOrderLocalID=%s 被撤订单的本地报单编号",buf);
	ActionFlag.getString(buf);
	pLogger->output(indent+1,0,"ActionFlag=%s 报单操作标志",buf);
	LimitPrice.getString(buf);
	pLogger->output(indent+1,0,"LimitPrice=%s 价格",buf);
	VolumeChange.getString(buf);
	pLogger->output(indent+1,0,"VolumeChange=%s 数量变化",buf);
	RecNum.getString(buf);
	pLogger->output(indent+1,0,"RecNum=%s 记录编号",buf);
	FrontID.getString(buf);
	pLogger->output(indent+1,0,"FrontID=%s 前置编号",buf);
	SessionID.getString(buf);
	pLogger->output(indent+1,0,"SessionID=%s 会话编号",buf);
	UserCustom.getString(buf);
	pLogger->output(indent+1,0,"UserCustom=%s 用户自定义域",buf);
	SeatID.getString(buf);
	pLogger->output(indent+1,0,"SeatID=%s 下单席位号",buf);
	ActionLocalID.getString(buf);
	pLogger->output(indent+1,0,"ActionLocalID=%s 操作本地编号",buf);
	ClientID.getString(buf);
	pLogger->output(indent+1,0,"ClientID=%s 客户代码",buf);
	ParticipantID.getString(buf);
	pLogger->output(indent+1,0,"ParticipantID=%s 会员代码",buf);
	CancelTime.getString(buf);
	pLogger->output(indent+1,0,"CancelTime=%s 撤销时间",buf);
	ActionSource.getString(buf);
	pLogger->output(indent+1,0,"ActionSource=%s 操作来源",buf);
	Tradable.getString(buf);
	pLogger->output(indent+1,0,"Tradable=%s 是否可以参加交易",buf);
	OrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"OrderLocalID=%s 本地报单编号",buf);
	IsForgeRtn.getString(buf);
	pLogger->output(indent+1,0,"IsForgeRtn=%s 伪造Rtn",buf);
	APIID.getString(buf);
	pLogger->output(indent+1,0,"APIID=%s 通道对应的APIID",buf);
	IPAddress.getString(buf);
	pLogger->output(indent+1,0,"IPAddress=%s 下单IP地址",buf);
	MacAddress.getString(buf);
	pLogger->output(indent+1,0,"MacAddress=%s 下单MAC地址",buf);
	OrderActionType.getString(buf);
	pLogger->output(indent+1,0,"OrderActionType=%s 撤单对应的报单类别",buf);
	OrderBatchNo.getString(buf);
	pLogger->output(indent+1,0,"OrderBatchNo=%s 报单批次号",buf);
	pLogger->output(indent,0,"}");
}

COrderActionIterator::~COrderActionIterator(void)
{
}


void COrderActionIterator::dump(FILE *output)
{
	COrderAction *pOrderAction;
	
	while ((pOrderAction=next())!=NULL)
	{
		pOrderAction->dump(output);
	}
}



void CWriteableOrder::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,ExchangeID,OrderSysID,InvestorID,UserID,InstrumentID,UserOrderLocalID,OrderPriceType,Direction,OffsetFlag,HedgeFlag,LimitPrice,Volume,TimeCondition,GTDDate,VolumeCondition,MinVolume,StopPrice,ForceCloseReason,IsAutoSuspend,BusinessUnit,UserCustom,BranchID,RecNum,BusinessType,TradingDay,ParticipantID,ClientID,SeatID,InsertTime,OrderLocalID,OrderSource,OrderStatus,CancelTime,CancelUserID,VolumeTraded,VolumeRemain,FrontID,SessionID,FrozenFee,FrozenMargin,FrozenPremium,AccountID,OrderUserID,TradeType,DealFlag,TradeCommision,TradeAmnt,CancleVolume,RequestID,APIID,IPAddress,MacAddress,FTdRecvDown,CoreRecvDown,CoreSendUp,CoreRecvUp,CoreSendDown,FTdSendDown,MarginCombType,InstrumentGroupID\n");
}
	
void CWriteableOrder::init(void)
{
	BrokerID.clear();
	ExchangeID.clear();
	OrderSysID.clear();
	InvestorID.clear();
	UserID.clear();
	InstrumentID.clear();
	UserOrderLocalID.clear();
	OrderPriceType.clear();
	Direction.clear();
	OffsetFlag.clear();
	HedgeFlag.clear();
	LimitPrice.clear();
	Volume.clear();
	TimeCondition.clear();
	GTDDate.clear();
	VolumeCondition.clear();
	MinVolume.clear();
	StopPrice.clear();
	ForceCloseReason.clear();
	IsAutoSuspend.clear();
	BusinessUnit.clear();
	UserCustom.clear();
	BranchID.clear();
	RecNum.clear();
	BusinessType.clear();
	TradingDay.clear();
	ParticipantID.clear();
	ClientID.clear();
	SeatID.clear();
	InsertTime.clear();
	OrderLocalID.clear();
	OrderSource.clear();
	OrderStatus.clear();
	CancelTime.clear();
	CancelUserID.clear();
	VolumeTraded.clear();
	VolumeRemain.clear();
	FrontID.clear();
	SessionID.clear();
	FrozenFee.clear();
	FrozenMargin.clear();
	FrozenPremium.clear();
	AccountID.clear();
	OrderUserID.clear();
	TradeType.clear();
	DealFlag.clear();
	TradeCommision.clear();
	TradeAmnt.clear();
	CancleVolume.clear();
	RequestID.clear();
	APIID.clear();
	IPAddress.clear();
	MacAddress.clear();
	FTdRecvDown.clear();
	CoreRecvDown.clear();
	CoreSendUp.clear();
	CoreRecvUp.clear();
	CoreSendDown.clear();
	FTdSendDown.clear();
	MarginCombType.clear();
	InstrumentGroupID.clear();
	pInvestor=NULL;
	pClientTradingID=NULL;
	pInvestorAccount=NULL;
	pInvestorPosition=NULL;
	pInstrument=NULL;
	pInvestorMargin=NULL;
	pInvestorFee=NULL;
	pInvestorOptionFee=NULL;
	pClientGroupPosition=NULL;
}

int CWriteableOrder::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableOrder),input)!=sizeof(CWriteableOrder))
		return 0;
	else
		return 1;
}
	
int CWriteableOrder::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderSysID=token;
		}
		else
		{
			OrderSysID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserID=token;
		}
		else
		{
			UserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserOrderLocalID=token;
		}
		else
		{
			UserOrderLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderPriceType=token;
		}
		else
		{
			OrderPriceType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Direction=token;
		}
		else
		{
			Direction="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OffsetFlag=token;
		}
		else
		{
			OffsetFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			HedgeFlag=token;
		}
		else
		{
			HedgeFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LimitPrice=token;
		}
		else
		{
			LimitPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Volume=token;
		}
		else
		{
			Volume="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TimeCondition=token;
		}
		else
		{
			TimeCondition="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			GTDDate=token;
		}
		else
		{
			GTDDate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			VolumeCondition=token;
		}
		else
		{
			VolumeCondition="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MinVolume=token;
		}
		else
		{
			MinVolume="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			StopPrice=token;
		}
		else
		{
			StopPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ForceCloseReason=token;
		}
		else
		{
			ForceCloseReason="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IsAutoSuspend=token;
		}
		else
		{
			IsAutoSuspend="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			BusinessUnit=token;
		}
		else
		{
			BusinessUnit="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserCustom=token;
		}
		else
		{
			UserCustom="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			BranchID=token;
		}
		else
		{
			BranchID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			RecNum=token;
		}
		else
		{
			RecNum="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			BusinessType=token;
		}
		else
		{
			BusinessType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradingDay=token;
		}
		else
		{
			TradingDay="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ParticipantID=token;
		}
		else
		{
			ParticipantID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ClientID=token;
		}
		else
		{
			ClientID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SeatID=token;
		}
		else
		{
			SeatID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InsertTime=token;
		}
		else
		{
			InsertTime="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderLocalID=token;
		}
		else
		{
			OrderLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderSource=token;
		}
		else
		{
			OrderSource="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderStatus=token;
		}
		else
		{
			OrderStatus="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CancelTime=token;
		}
		else
		{
			CancelTime="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CancelUserID=token;
		}
		else
		{
			CancelUserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			VolumeTraded=token;
		}
		else
		{
			VolumeTraded="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			VolumeRemain=token;
		}
		else
		{
			VolumeRemain="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrontID=token;
		}
		else
		{
			FrontID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SessionID=token;
		}
		else
		{
			SessionID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenFee=token;
		}
		else
		{
			FrozenFee="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenMargin=token;
		}
		else
		{
			FrozenMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenPremium=token;
		}
		else
		{
			FrozenPremium="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			AccountID=token;
		}
		else
		{
			AccountID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderUserID=token;
		}
		else
		{
			OrderUserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeType=token;
		}
		else
		{
			TradeType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			DealFlag=token;
		}
		else
		{
			DealFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeCommision=token;
		}
		else
		{
			TradeCommision="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeAmnt=token;
		}
		else
		{
			TradeAmnt="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CancleVolume=token;
		}
		else
		{
			CancleVolume="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			RequestID=token;
		}
		else
		{
			RequestID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			APIID=token;
		}
		else
		{
			APIID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IPAddress=token;
		}
		else
		{
			IPAddress="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MacAddress=token;
		}
		else
		{
			MacAddress="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FTdRecvDown=token;
		}
		else
		{
			FTdRecvDown="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreRecvDown=token;
		}
		else
		{
			CoreRecvDown="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreSendUp=token;
		}
		else
		{
			CoreSendUp="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreRecvUp=token;
		}
		else
		{
			CoreRecvUp="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreSendDown=token;
		}
		else
		{
			CoreSendDown="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FTdSendDown=token;
		}
		else
		{
			FTdSendDown="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MarginCombType=token;
		}
		else
		{
			MarginCombType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentGroupID=token;
		}
		else
		{
			InstrumentGroupID="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"OrderSysID"))
			{
				OrderSysID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"UserID"))
			{
				UserID=token;
			}
			else if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"UserOrderLocalID"))
			{
				UserOrderLocalID=token;
			}
			else if (!strcmp(fieldName,"OrderPriceType"))
			{
				OrderPriceType=token;
			}
			else if (!strcmp(fieldName,"Direction"))
			{
				Direction=token;
			}
			else if (!strcmp(fieldName,"OffsetFlag"))
			{
				OffsetFlag=token;
			}
			else if (!strcmp(fieldName,"HedgeFlag"))
			{
				HedgeFlag=token;
			}
			else if (!strcmp(fieldName,"LimitPrice"))
			{
				LimitPrice=token;
			}
			else if (!strcmp(fieldName,"Volume"))
			{
				Volume=token;
			}
			else if (!strcmp(fieldName,"TimeCondition"))
			{
				TimeCondition=token;
			}
			else if (!strcmp(fieldName,"GTDDate"))
			{
				GTDDate=token;
			}
			else if (!strcmp(fieldName,"VolumeCondition"))
			{
				VolumeCondition=token;
			}
			else if (!strcmp(fieldName,"MinVolume"))
			{
				MinVolume=token;
			}
			else if (!strcmp(fieldName,"StopPrice"))
			{
				StopPrice=token;
			}
			else if (!strcmp(fieldName,"ForceCloseReason"))
			{
				ForceCloseReason=token;
			}
			else if (!strcmp(fieldName,"IsAutoSuspend"))
			{
				IsAutoSuspend=token;
			}
			else if (!strcmp(fieldName,"BusinessUnit"))
			{
				BusinessUnit=token;
			}
			else if (!strcmp(fieldName,"UserCustom"))
			{
				UserCustom=token;
			}
			else if (!strcmp(fieldName,"BranchID"))
			{
				BranchID=token;
			}
			else if (!strcmp(fieldName,"RecNum"))
			{
				RecNum=token;
			}
			else if (!strcmp(fieldName,"BusinessType"))
			{
				BusinessType=token;
			}
			else if (!strcmp(fieldName,"TradingDay"))
			{
				TradingDay=token;
			}
			else if (!strcmp(fieldName,"ParticipantID"))
			{
				ParticipantID=token;
			}
			else if (!strcmp(fieldName,"ClientID"))
			{
				ClientID=token;
			}
			else if (!strcmp(fieldName,"SeatID"))
			{
				SeatID=token;
			}
			else if (!strcmp(fieldName,"InsertTime"))
			{
				InsertTime=token;
			}
			else if (!strcmp(fieldName,"OrderLocalID"))
			{
				OrderLocalID=token;
			}
			else if (!strcmp(fieldName,"OrderSource"))
			{
				OrderSource=token;
			}
			else if (!strcmp(fieldName,"OrderStatus"))
			{
				OrderStatus=token;
			}
			else if (!strcmp(fieldName,"CancelTime"))
			{
				CancelTime=token;
			}
			else if (!strcmp(fieldName,"CancelUserID"))
			{
				CancelUserID=token;
			}
			else if (!strcmp(fieldName,"VolumeTraded"))
			{
				VolumeTraded=token;
			}
			else if (!strcmp(fieldName,"VolumeRemain"))
			{
				VolumeRemain=token;
			}
			else if (!strcmp(fieldName,"FrontID"))
			{
				FrontID=token;
			}
			else if (!strcmp(fieldName,"SessionID"))
			{
				SessionID=token;
			}
			else if (!strcmp(fieldName,"FrozenFee"))
			{
				FrozenFee=token;
			}
			else if (!strcmp(fieldName,"FrozenMargin"))
			{
				FrozenMargin=token;
			}
			else if (!strcmp(fieldName,"FrozenPremium"))
			{
				FrozenPremium=token;
			}
			else if (!strcmp(fieldName,"AccountID"))
			{
				AccountID=token;
			}
			else if (!strcmp(fieldName,"OrderUserID"))
			{
				OrderUserID=token;
			}
			else if (!strcmp(fieldName,"TradeType"))
			{
				TradeType=token;
			}
			else if (!strcmp(fieldName,"DealFlag"))
			{
				DealFlag=token;
			}
			else if (!strcmp(fieldName,"TradeCommision"))
			{
				TradeCommision=token;
			}
			else if (!strcmp(fieldName,"TradeAmnt"))
			{
				TradeAmnt=token;
			}
			else if (!strcmp(fieldName,"CancleVolume"))
			{
				CancleVolume=token;
			}
			else if (!strcmp(fieldName,"RequestID"))
			{
				RequestID=token;
			}
			else if (!strcmp(fieldName,"APIID"))
			{
				APIID=token;
			}
			else if (!strcmp(fieldName,"IPAddress"))
			{
				IPAddress=token;
			}
			else if (!strcmp(fieldName,"MacAddress"))
			{
				MacAddress=token;
			}
			else if (!strcmp(fieldName,"FTdRecvDown"))
			{
				FTdRecvDown=token;
			}
			else if (!strcmp(fieldName,"CoreRecvDown"))
			{
				CoreRecvDown=token;
			}
			else if (!strcmp(fieldName,"CoreSendUp"))
			{
				CoreSendUp=token;
			}
			else if (!strcmp(fieldName,"CoreRecvUp"))
			{
				CoreRecvUp=token;
			}
			else if (!strcmp(fieldName,"CoreSendDown"))
			{
				CoreSendDown=token;
			}
			else if (!strcmp(fieldName,"FTdSendDown"))
			{
				FTdSendDown=token;
			}
			else if (!strcmp(fieldName,"MarginCombType"))
			{
				MarginCombType=token;
			}
			else if (!strcmp(fieldName,"InstrumentGroupID"))
			{
				InstrumentGroupID=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableOrder::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableOrder),output)!=sizeof(CWriteableOrder))
		return 0;
	else
		return 1;
}

int CWriteableOrder::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderSysID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserOrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderPriceType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Direction.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OffsetFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	HedgeFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LimitPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Volume.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TimeCondition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	GTDDate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	VolumeCondition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MinVolume.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	StopPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ForceCloseReason.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IsAutoSuspend.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	BusinessUnit.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserCustom.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	BranchID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	RecNum.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	BusinessType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradingDay.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ParticipantID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ClientID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SeatID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InsertTime.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderSource.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderStatus.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CancelTime.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CancelUserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	VolumeTraded.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	VolumeRemain.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrontID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SessionID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenFee.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenPremium.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	AccountID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderUserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	DealFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeCommision.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeAmnt.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CancleVolume.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	RequestID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	APIID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IPAddress.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MacAddress.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FTdRecvDown.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreRecvDown.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreSendUp.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreRecvUp.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreSendDown.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FTdSendDown.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MarginCombType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentGroupID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableOrder::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCOrder%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	OrderSysID.getString(buf);
	fprintf(fp,"\t\tOrderSysID = %s    [系统报单编号]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);	
	UserID.getString(buf);
	fprintf(fp,"\t\tUserID = %s    [用户代码]\n",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	UserOrderLocalID.getString(buf);
	fprintf(fp,"\t\tUserOrderLocalID = %s    [用户本地报单号]\n",buf);	
	OrderPriceType.getString(buf);
	fprintf(fp,"\t\tOrderPriceType = %s    [价格类型]\n",buf);	
	Direction.getString(buf);
	fprintf(fp,"\t\tDirection = %s    [买卖方向]\n",buf);	
	OffsetFlag.getString(buf);
	fprintf(fp,"\t\tOffsetFlag = %s    [开平标志]\n",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);	
	LimitPrice.getString(buf);
	fprintf(fp,"\t\tLimitPrice = %s    [价格]\n",buf);	
	Volume.getString(buf);
	fprintf(fp,"\t\tVolume = %s    [数量]\n",buf);	
	TimeCondition.getString(buf);
	fprintf(fp,"\t\tTimeCondition = %s    [有效期类型]\n",buf);	
	GTDDate.getString(buf);
	fprintf(fp,"\t\tGTDDate = %s    [GTD日期]\n",buf);	
	VolumeCondition.getString(buf);
	fprintf(fp,"\t\tVolumeCondition = %s    [成交量类型]\n",buf);	
	MinVolume.getString(buf);
	fprintf(fp,"\t\tMinVolume = %s    [最小成交量]\n",buf);	
	StopPrice.getString(buf);
	fprintf(fp,"\t\tStopPrice = %s    [止损价]\n",buf);	
	ForceCloseReason.getString(buf);
	fprintf(fp,"\t\tForceCloseReason = %s    [强平原因]\n",buf);	
	IsAutoSuspend.getString(buf);
	fprintf(fp,"\t\tIsAutoSuspend = %s    [自动挂起标志]\n",buf);	
	BusinessUnit.getString(buf);
	fprintf(fp,"\t\tBusinessUnit = %s    [业务单元]\n",buf);	
	UserCustom.getString(buf);
	fprintf(fp,"\t\tUserCustom = %s    [用户自定义域]\n",buf);	
	BranchID.getString(buf);
	fprintf(fp,"\t\tBranchID = %s    [营业部代码]\n",buf);	
	RecNum.getString(buf);
	fprintf(fp,"\t\tRecNum = %s    [记录编号]\n",buf);	
	BusinessType.getString(buf);
	fprintf(fp,"\t\tBusinessType = %s    [业务类别]\n",buf);	
	TradingDay.getString(buf);
	fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,"\t\tParticipantID = %s    [会员编号]\n",buf);	
	ClientID.getString(buf);
	fprintf(fp,"\t\tClientID = %s    [客户号]\n",buf);	
	SeatID.getString(buf);
	fprintf(fp,"\t\tSeatID = %s    [下单席位号]\n",buf);	
	InsertTime.getString(buf);
	fprintf(fp,"\t\tInsertTime = %s    [插入时间]\n",buf);	
	OrderLocalID.getString(buf);
	fprintf(fp,"\t\tOrderLocalID = %s    [本地报单编号]\n",buf);	
	OrderSource.getString(buf);
	fprintf(fp,"\t\tOrderSource = %s    [报单来源]\n",buf);	
	OrderStatus.getString(buf);
	fprintf(fp,"\t\tOrderStatus = %s    [报单状态]\n",buf);	
	CancelTime.getString(buf);
	fprintf(fp,"\t\tCancelTime = %s    [撤销时间]\n",buf);	
	CancelUserID.getString(buf);
	fprintf(fp,"\t\tCancelUserID = %s    [撤单用户编号]\n",buf);	
	VolumeTraded.getString(buf);
	fprintf(fp,"\t\tVolumeTraded = %s    [今成交数量]\n",buf);	
	VolumeRemain.getString(buf);
	fprintf(fp,"\t\tVolumeRemain = %s    [剩余数量]\n",buf);	
	FrontID.getString(buf);
	fprintf(fp,"\t\tFrontID = %s    [前置编号]\n",buf);	
	SessionID.getString(buf);
	fprintf(fp,"\t\tSessionID = %s    [会话编号]\n",buf);	
	FrozenFee.getString(buf);
	fprintf(fp,"\t\tFrozenFee = %s    [冻结手续费]\n",buf);	
	FrozenMargin.getString(buf);
	fprintf(fp,"\t\tFrozenMargin = %s    [冻结的保证金]\n",buf);	
	FrozenPremium.getString(buf);
	fprintf(fp,"\t\tFrozenPremium = %s    [期权权利金收支]\n",buf);	
	AccountID.getString(buf);
	fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);	
	OrderUserID.getString(buf);
	fprintf(fp,"\t\tOrderUserID = %s    [下单用户编号]\n",buf);	
	TradeType.getString(buf);
	fprintf(fp,"\t\tTradeType = %s    [交易类型]\n",buf);	
	DealFlag.getString(buf);
	fprintf(fp,"\t\tDealFlag = %s    [处理标志]\n",buf);	
	TradeCommision.getString(buf);
	fprintf(fp,"\t\tTradeCommision = %s    [已成交佣金]\n",buf);	
	TradeAmnt.getString(buf);
	fprintf(fp,"\t\tTradeAmnt = %s    [成交金额]\n",buf);	
	CancleVolume.getString(buf);
	fprintf(fp,"\t\tCancleVolume = %s    [撤单数量]\n",buf);	
	RequestID.getString(buf);
	fprintf(fp,"\t\tRequestID = %s    [请求编号]\n",buf);	
	APIID.getString(buf);
	fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);	
	IPAddress.getString(buf);
	fprintf(fp,"\t\tIPAddress = %s    [下单IP地址]\n",buf);	
	MacAddress.getString(buf);
	fprintf(fp,"\t\tMacAddress = %s    [下单MAC地址]\n",buf);	
	FTdRecvDown.getString(buf);
	fprintf(fp,"\t\tFTdRecvDown = %s    [Ftdengine接受下层时间戳]\n",buf);	
	CoreRecvDown.getString(buf);
	fprintf(fp,"\t\tCoreRecvDown = %s    [接受下层时间戳]\n",buf);	
	CoreSendUp.getString(buf);
	fprintf(fp,"\t\tCoreSendUp = %s    [发送上层时间戳]\n",buf);	
	CoreRecvUp.getString(buf);
	fprintf(fp,"\t\tCoreRecvUp = %s    [接受上层时间戳]\n",buf);	
	CoreSendDown.getString(buf);
	fprintf(fp,"\t\tCoreSendDown = %s    [发送下层时间戳]\n",buf);	
	FTdSendDown.getString(buf);
	fprintf(fp,"\t\tFTdSendDown = %s    [Ftdengine接受下层时间戳]\n",buf);	
	MarginCombType.getString(buf);
	fprintf(fp,"\t\tMarginCombType = %s    [保证金组合类型]\n",buf);	
	InstrumentGroupID.getString(buf);
	fprintf(fp,"\t\tInstrumentGroupID = %s    [合约组代码]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableOrder::dumpDiff(FILE *fp, const CWriteableOrder *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCOrder = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	OrderSysID.getString(buf);
	if (compare(OrderSysID.getValue(),pOriginal->OrderSysID.getValue())!=0)
	{
		pOriginal->OrderSysID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderSysID = %s -> %s    [系统报单编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderSysID = %s    [系统报单编号]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);
	}
	UserID.getString(buf);
	if (compare(UserID.getValue(),pOriginal->UserID.getValue())!=0)
	{
		pOriginal->UserID.getString(bufOriginal);
		fprintf(fp,"\t\tUserID = %s -> %s    [用户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserID = %s    [用户代码]\n",buf);
	}
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	UserOrderLocalID.getString(buf);
	if (compare(UserOrderLocalID.getValue(),pOriginal->UserOrderLocalID.getValue())!=0)
	{
		pOriginal->UserOrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tUserOrderLocalID = %s -> %s    [用户本地报单号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserOrderLocalID = %s    [用户本地报单号]\n",buf);
	}
	OrderPriceType.getString(buf);
	if (compare(OrderPriceType.getValue(),pOriginal->OrderPriceType.getValue())!=0)
	{
		pOriginal->OrderPriceType.getString(bufOriginal);
		fprintf(fp,"\t\tOrderPriceType = %s -> %s    [价格类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderPriceType = %s    [价格类型]\n",buf);
	}
	Direction.getString(buf);
	if (compare(Direction.getValue(),pOriginal->Direction.getValue())!=0)
	{
		pOriginal->Direction.getString(bufOriginal);
		fprintf(fp,"\t\tDirection = %s -> %s    [买卖方向]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDirection = %s    [买卖方向]\n",buf);
	}
	OffsetFlag.getString(buf);
	if (compare(OffsetFlag.getValue(),pOriginal->OffsetFlag.getValue())!=0)
	{
		pOriginal->OffsetFlag.getString(bufOriginal);
		fprintf(fp,"\t\tOffsetFlag = %s -> %s    [开平标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOffsetFlag = %s    [开平标志]\n",buf);
	}
	HedgeFlag.getString(buf);
	if (compare(HedgeFlag.getValue(),pOriginal->HedgeFlag.getValue())!=0)
	{
		pOriginal->HedgeFlag.getString(bufOriginal);
		fprintf(fp,"\t\tHedgeFlag = %s -> %s    [投机套保标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);
	}
	LimitPrice.getString(buf);
	if (compare(LimitPrice.getValue(),pOriginal->LimitPrice.getValue())!=0)
	{
		pOriginal->LimitPrice.getString(bufOriginal);
		fprintf(fp,"\t\tLimitPrice = %s -> %s    [价格]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLimitPrice = %s    [价格]\n",buf);
	}
	Volume.getString(buf);
	if (compare(Volume.getValue(),pOriginal->Volume.getValue())!=0)
	{
		pOriginal->Volume.getString(bufOriginal);
		fprintf(fp,"\t\tVolume = %s -> %s    [数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tVolume = %s    [数量]\n",buf);
	}
	TimeCondition.getString(buf);
	if (compare(TimeCondition.getValue(),pOriginal->TimeCondition.getValue())!=0)
	{
		pOriginal->TimeCondition.getString(bufOriginal);
		fprintf(fp,"\t\tTimeCondition = %s -> %s    [有效期类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTimeCondition = %s    [有效期类型]\n",buf);
	}
	GTDDate.getString(buf);
	if (compare(GTDDate.getValue(),pOriginal->GTDDate.getValue())!=0)
	{
		pOriginal->GTDDate.getString(bufOriginal);
		fprintf(fp,"\t\tGTDDate = %s -> %s    [GTD日期]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tGTDDate = %s    [GTD日期]\n",buf);
	}
	VolumeCondition.getString(buf);
	if (compare(VolumeCondition.getValue(),pOriginal->VolumeCondition.getValue())!=0)
	{
		pOriginal->VolumeCondition.getString(bufOriginal);
		fprintf(fp,"\t\tVolumeCondition = %s -> %s    [成交量类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tVolumeCondition = %s    [成交量类型]\n",buf);
	}
	MinVolume.getString(buf);
	if (compare(MinVolume.getValue(),pOriginal->MinVolume.getValue())!=0)
	{
		pOriginal->MinVolume.getString(bufOriginal);
		fprintf(fp,"\t\tMinVolume = %s -> %s    [最小成交量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMinVolume = %s    [最小成交量]\n",buf);
	}
	StopPrice.getString(buf);
	if (compare(StopPrice.getValue(),pOriginal->StopPrice.getValue())!=0)
	{
		pOriginal->StopPrice.getString(bufOriginal);
		fprintf(fp,"\t\tStopPrice = %s -> %s    [止损价]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tStopPrice = %s    [止损价]\n",buf);
	}
	ForceCloseReason.getString(buf);
	if (compare(ForceCloseReason.getValue(),pOriginal->ForceCloseReason.getValue())!=0)
	{
		pOriginal->ForceCloseReason.getString(bufOriginal);
		fprintf(fp,"\t\tForceCloseReason = %s -> %s    [强平原因]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tForceCloseReason = %s    [强平原因]\n",buf);
	}
	IsAutoSuspend.getString(buf);
	if (compare(IsAutoSuspend.getValue(),pOriginal->IsAutoSuspend.getValue())!=0)
	{
		pOriginal->IsAutoSuspend.getString(bufOriginal);
		fprintf(fp,"\t\tIsAutoSuspend = %s -> %s    [自动挂起标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIsAutoSuspend = %s    [自动挂起标志]\n",buf);
	}
	BusinessUnit.getString(buf);
	if (compare(BusinessUnit.getValue(),pOriginal->BusinessUnit.getValue())!=0)
	{
		pOriginal->BusinessUnit.getString(bufOriginal);
		fprintf(fp,"\t\tBusinessUnit = %s -> %s    [业务单元]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBusinessUnit = %s    [业务单元]\n",buf);
	}
	UserCustom.getString(buf);
	if (compare(UserCustom.getValue(),pOriginal->UserCustom.getValue())!=0)
	{
		pOriginal->UserCustom.getString(bufOriginal);
		fprintf(fp,"\t\tUserCustom = %s -> %s    [用户自定义域]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserCustom = %s    [用户自定义域]\n",buf);
	}
	BranchID.getString(buf);
	if (compare(BranchID.getValue(),pOriginal->BranchID.getValue())!=0)
	{
		pOriginal->BranchID.getString(bufOriginal);
		fprintf(fp,"\t\tBranchID = %s -> %s    [营业部代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBranchID = %s    [营业部代码]\n",buf);
	}
	RecNum.getString(buf);
	if (compare(RecNum.getValue(),pOriginal->RecNum.getValue())!=0)
	{
		pOriginal->RecNum.getString(bufOriginal);
		fprintf(fp,"\t\tRecNum = %s -> %s    [记录编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tRecNum = %s    [记录编号]\n",buf);
	}
	BusinessType.getString(buf);
	if (compare(BusinessType.getValue(),pOriginal->BusinessType.getValue())!=0)
	{
		pOriginal->BusinessType.getString(bufOriginal);
		fprintf(fp,"\t\tBusinessType = %s -> %s    [业务类别]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBusinessType = %s    [业务类别]\n",buf);
	}
	TradingDay.getString(buf);
	if (compare(TradingDay.getValue(),pOriginal->TradingDay.getValue())!=0)
	{
		pOriginal->TradingDay.getString(bufOriginal);
		fprintf(fp,"\t\tTradingDay = %s -> %s    [交易日]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);
	}
	ParticipantID.getString(buf);
	if (compare(ParticipantID.getValue(),pOriginal->ParticipantID.getValue())!=0)
	{
		pOriginal->ParticipantID.getString(bufOriginal);
		fprintf(fp,"\t\tParticipantID = %s -> %s    [会员编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tParticipantID = %s    [会员编号]\n",buf);
	}
	ClientID.getString(buf);
	if (compare(ClientID.getValue(),pOriginal->ClientID.getValue())!=0)
	{
		pOriginal->ClientID.getString(bufOriginal);
		fprintf(fp,"\t\tClientID = %s -> %s    [客户号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tClientID = %s    [客户号]\n",buf);
	}
	SeatID.getString(buf);
	if (compare(SeatID.getValue(),pOriginal->SeatID.getValue())!=0)
	{
		pOriginal->SeatID.getString(bufOriginal);
		fprintf(fp,"\t\tSeatID = %s -> %s    [下单席位号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSeatID = %s    [下单席位号]\n",buf);
	}
	InsertTime.getString(buf);
	if (compare(InsertTime.getValue(),pOriginal->InsertTime.getValue())!=0)
	{
		pOriginal->InsertTime.getString(bufOriginal);
		fprintf(fp,"\t\tInsertTime = %s -> %s    [插入时间]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInsertTime = %s    [插入时间]\n",buf);
	}
	OrderLocalID.getString(buf);
	if (compare(OrderLocalID.getValue(),pOriginal->OrderLocalID.getValue())!=0)
	{
		pOriginal->OrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderLocalID = %s -> %s    [本地报单编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderLocalID = %s    [本地报单编号]\n",buf);
	}
	OrderSource.getString(buf);
	if (compare(OrderSource.getValue(),pOriginal->OrderSource.getValue())!=0)
	{
		pOriginal->OrderSource.getString(bufOriginal);
		fprintf(fp,"\t\tOrderSource = %s -> %s    [报单来源]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderSource = %s    [报单来源]\n",buf);
	}
	OrderStatus.getString(buf);
	if (compare(OrderStatus.getValue(),pOriginal->OrderStatus.getValue())!=0)
	{
		pOriginal->OrderStatus.getString(bufOriginal);
		fprintf(fp,"\t\tOrderStatus = %s -> %s    [报单状态]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderStatus = %s    [报单状态]\n",buf);
	}
	CancelTime.getString(buf);
	if (compare(CancelTime.getValue(),pOriginal->CancelTime.getValue())!=0)
	{
		pOriginal->CancelTime.getString(bufOriginal);
		fprintf(fp,"\t\tCancelTime = %s -> %s    [撤销时间]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCancelTime = %s    [撤销时间]\n",buf);
	}
	CancelUserID.getString(buf);
	if (compare(CancelUserID.getValue(),pOriginal->CancelUserID.getValue())!=0)
	{
		pOriginal->CancelUserID.getString(bufOriginal);
		fprintf(fp,"\t\tCancelUserID = %s -> %s    [撤单用户编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCancelUserID = %s    [撤单用户编号]\n",buf);
	}
	VolumeTraded.getString(buf);
	if (compare(VolumeTraded.getValue(),pOriginal->VolumeTraded.getValue())!=0)
	{
		pOriginal->VolumeTraded.getString(bufOriginal);
		fprintf(fp,"\t\tVolumeTraded = %s -> %s    [今成交数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tVolumeTraded = %s    [今成交数量]\n",buf);
	}
	VolumeRemain.getString(buf);
	if (compare(VolumeRemain.getValue(),pOriginal->VolumeRemain.getValue())!=0)
	{
		pOriginal->VolumeRemain.getString(bufOriginal);
		fprintf(fp,"\t\tVolumeRemain = %s -> %s    [剩余数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tVolumeRemain = %s    [剩余数量]\n",buf);
	}
	FrontID.getString(buf);
	if (compare(FrontID.getValue(),pOriginal->FrontID.getValue())!=0)
	{
		pOriginal->FrontID.getString(bufOriginal);
		fprintf(fp,"\t\tFrontID = %s -> %s    [前置编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrontID = %s    [前置编号]\n",buf);
	}
	SessionID.getString(buf);
	if (compare(SessionID.getValue(),pOriginal->SessionID.getValue())!=0)
	{
		pOriginal->SessionID.getString(bufOriginal);
		fprintf(fp,"\t\tSessionID = %s -> %s    [会话编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSessionID = %s    [会话编号]\n",buf);
	}
	FrozenFee.getString(buf);
	if (compare(FrozenFee.getValue(),pOriginal->FrozenFee.getValue())!=0)
	{
		pOriginal->FrozenFee.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenFee = %s -> %s    [冻结手续费]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenFee = %s    [冻结手续费]\n",buf);
	}
	FrozenMargin.getString(buf);
	if (compare(FrozenMargin.getValue(),pOriginal->FrozenMargin.getValue())!=0)
	{
		pOriginal->FrozenMargin.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenMargin = %s -> %s    [冻结的保证金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenMargin = %s    [冻结的保证金]\n",buf);
	}
	FrozenPremium.getString(buf);
	if (compare(FrozenPremium.getValue(),pOriginal->FrozenPremium.getValue())!=0)
	{
		pOriginal->FrozenPremium.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenPremium = %s -> %s    [期权权利金收支]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenPremium = %s    [期权权利金收支]\n",buf);
	}
	AccountID.getString(buf);
	if (compare(AccountID.getValue(),pOriginal->AccountID.getValue())!=0)
	{
		pOriginal->AccountID.getString(bufOriginal);
		fprintf(fp,"\t\tAccountID = %s -> %s    [资金帐号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);
	}
	OrderUserID.getString(buf);
	if (compare(OrderUserID.getValue(),pOriginal->OrderUserID.getValue())!=0)
	{
		pOriginal->OrderUserID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderUserID = %s -> %s    [下单用户编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderUserID = %s    [下单用户编号]\n",buf);
	}
	TradeType.getString(buf);
	if (compare(TradeType.getValue(),pOriginal->TradeType.getValue())!=0)
	{
		pOriginal->TradeType.getString(bufOriginal);
		fprintf(fp,"\t\tTradeType = %s -> %s    [交易类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeType = %s    [交易类型]\n",buf);
	}
	DealFlag.getString(buf);
	if (compare(DealFlag.getValue(),pOriginal->DealFlag.getValue())!=0)
	{
		pOriginal->DealFlag.getString(bufOriginal);
		fprintf(fp,"\t\tDealFlag = %s -> %s    [处理标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDealFlag = %s    [处理标志]\n",buf);
	}
	TradeCommision.getString(buf);
	if (compare(TradeCommision.getValue(),pOriginal->TradeCommision.getValue())!=0)
	{
		pOriginal->TradeCommision.getString(bufOriginal);
		fprintf(fp,"\t\tTradeCommision = %s -> %s    [已成交佣金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeCommision = %s    [已成交佣金]\n",buf);
	}
	TradeAmnt.getString(buf);
	if (compare(TradeAmnt.getValue(),pOriginal->TradeAmnt.getValue())!=0)
	{
		pOriginal->TradeAmnt.getString(bufOriginal);
		fprintf(fp,"\t\tTradeAmnt = %s -> %s    [成交金额]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeAmnt = %s    [成交金额]\n",buf);
	}
	CancleVolume.getString(buf);
	if (compare(CancleVolume.getValue(),pOriginal->CancleVolume.getValue())!=0)
	{
		pOriginal->CancleVolume.getString(bufOriginal);
		fprintf(fp,"\t\tCancleVolume = %s -> %s    [撤单数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCancleVolume = %s    [撤单数量]\n",buf);
	}
	RequestID.getString(buf);
	if (compare(RequestID.getValue(),pOriginal->RequestID.getValue())!=0)
	{
		pOriginal->RequestID.getString(bufOriginal);
		fprintf(fp,"\t\tRequestID = %s -> %s    [请求编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tRequestID = %s    [请求编号]\n",buf);
	}
	APIID.getString(buf);
	if (compare(APIID.getValue(),pOriginal->APIID.getValue())!=0)
	{
		pOriginal->APIID.getString(bufOriginal);
		fprintf(fp,"\t\tAPIID = %s -> %s    [通道对应的APIID]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);
	}
	IPAddress.getString(buf);
	if (compare(IPAddress.getValue(),pOriginal->IPAddress.getValue())!=0)
	{
		pOriginal->IPAddress.getString(bufOriginal);
		fprintf(fp,"\t\tIPAddress = %s -> %s    [下单IP地址]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIPAddress = %s    [下单IP地址]\n",buf);
	}
	MacAddress.getString(buf);
	if (compare(MacAddress.getValue(),pOriginal->MacAddress.getValue())!=0)
	{
		pOriginal->MacAddress.getString(bufOriginal);
		fprintf(fp,"\t\tMacAddress = %s -> %s    [下单MAC地址]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMacAddress = %s    [下单MAC地址]\n",buf);
	}
	FTdRecvDown.getString(buf);
	if (compare(FTdRecvDown.getValue(),pOriginal->FTdRecvDown.getValue())!=0)
	{
		pOriginal->FTdRecvDown.getString(bufOriginal);
		fprintf(fp,"\t\tFTdRecvDown = %s -> %s    [Ftdengine接受下层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFTdRecvDown = %s    [Ftdengine接受下层时间戳]\n",buf);
	}
	CoreRecvDown.getString(buf);
	if (compare(CoreRecvDown.getValue(),pOriginal->CoreRecvDown.getValue())!=0)
	{
		pOriginal->CoreRecvDown.getString(bufOriginal);
		fprintf(fp,"\t\tCoreRecvDown = %s -> %s    [接受下层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreRecvDown = %s    [接受下层时间戳]\n",buf);
	}
	CoreSendUp.getString(buf);
	if (compare(CoreSendUp.getValue(),pOriginal->CoreSendUp.getValue())!=0)
	{
		pOriginal->CoreSendUp.getString(bufOriginal);
		fprintf(fp,"\t\tCoreSendUp = %s -> %s    [发送上层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreSendUp = %s    [发送上层时间戳]\n",buf);
	}
	CoreRecvUp.getString(buf);
	if (compare(CoreRecvUp.getValue(),pOriginal->CoreRecvUp.getValue())!=0)
	{
		pOriginal->CoreRecvUp.getString(bufOriginal);
		fprintf(fp,"\t\tCoreRecvUp = %s -> %s    [接受上层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreRecvUp = %s    [接受上层时间戳]\n",buf);
	}
	CoreSendDown.getString(buf);
	if (compare(CoreSendDown.getValue(),pOriginal->CoreSendDown.getValue())!=0)
	{
		pOriginal->CoreSendDown.getString(bufOriginal);
		fprintf(fp,"\t\tCoreSendDown = %s -> %s    [发送下层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreSendDown = %s    [发送下层时间戳]\n",buf);
	}
	FTdSendDown.getString(buf);
	if (compare(FTdSendDown.getValue(),pOriginal->FTdSendDown.getValue())!=0)
	{
		pOriginal->FTdSendDown.getString(bufOriginal);
		fprintf(fp,"\t\tFTdSendDown = %s -> %s    [Ftdengine接受下层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFTdSendDown = %s    [Ftdengine接受下层时间戳]\n",buf);
	}
	MarginCombType.getString(buf);
	if (compare(MarginCombType.getValue(),pOriginal->MarginCombType.getValue())!=0)
	{
		pOriginal->MarginCombType.getString(bufOriginal);
		fprintf(fp,"\t\tMarginCombType = %s -> %s    [保证金组合类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMarginCombType = %s    [保证金组合类型]\n",buf);
	}
	InstrumentGroupID.getString(buf);
	if (compare(InstrumentGroupID.getValue(),pOriginal->InstrumentGroupID.getValue())!=0)
	{
		pOriginal->InstrumentGroupID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentGroupID = %s -> %s    [合约组代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentGroupID = %s    [合约组代码]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableOrder::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	OrderSysID.getString(buf);
	fprintf(fp,",OrderSysID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	UserID.getString(buf);
	fprintf(fp,",UserID,%s",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	UserOrderLocalID.getString(buf);
	fprintf(fp,",UserOrderLocalID,%s",buf);	
	OrderPriceType.getString(buf);
	fprintf(fp,",OrderPriceType,%s",buf);	
	Direction.getString(buf);
	fprintf(fp,",Direction,%s",buf);	
	OffsetFlag.getString(buf);
	fprintf(fp,",OffsetFlag,%s",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,",HedgeFlag,%s",buf);	
	LimitPrice.getString(buf);
	fprintf(fp,",LimitPrice,%s",buf);	
	Volume.getString(buf);
	fprintf(fp,",Volume,%s",buf);	
	TimeCondition.getString(buf);
	fprintf(fp,",TimeCondition,%s",buf);	
	GTDDate.getString(buf);
	fprintf(fp,",GTDDate,%s",buf);	
	VolumeCondition.getString(buf);
	fprintf(fp,",VolumeCondition,%s",buf);	
	MinVolume.getString(buf);
	fprintf(fp,",MinVolume,%s",buf);	
	StopPrice.getString(buf);
	fprintf(fp,",StopPrice,%s",buf);	
	ForceCloseReason.getString(buf);
	fprintf(fp,",ForceCloseReason,%s",buf);	
	IsAutoSuspend.getString(buf);
	fprintf(fp,",IsAutoSuspend,%s",buf);	
	BusinessUnit.getString(buf);
	fprintf(fp,",BusinessUnit,%s",buf);	
	UserCustom.getString(buf);
	fprintf(fp,",UserCustom,%s",buf);	
	BranchID.getString(buf);
	fprintf(fp,",BranchID,%s",buf);	
	RecNum.getString(buf);
	fprintf(fp,",RecNum,%s",buf);	
	BusinessType.getString(buf);
	fprintf(fp,",BusinessType,%s",buf);	
	TradingDay.getString(buf);
	fprintf(fp,",TradingDay,%s",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,",ParticipantID,%s",buf);	
	ClientID.getString(buf);
	fprintf(fp,",ClientID,%s",buf);	
	SeatID.getString(buf);
	fprintf(fp,",SeatID,%s",buf);	
	InsertTime.getString(buf);
	fprintf(fp,",InsertTime,%s",buf);	
	OrderLocalID.getString(buf);
	fprintf(fp,",OrderLocalID,%s",buf);	
	OrderSource.getString(buf);
	fprintf(fp,",OrderSource,%s",buf);	
	OrderStatus.getString(buf);
	fprintf(fp,",OrderStatus,%s",buf);	
	CancelTime.getString(buf);
	fprintf(fp,",CancelTime,%s",buf);	
	CancelUserID.getString(buf);
	fprintf(fp,",CancelUserID,%s",buf);	
	VolumeTraded.getString(buf);
	fprintf(fp,",VolumeTraded,%s",buf);	
	VolumeRemain.getString(buf);
	fprintf(fp,",VolumeRemain,%s",buf);	
	FrontID.getString(buf);
	fprintf(fp,",FrontID,%s",buf);	
	SessionID.getString(buf);
	fprintf(fp,",SessionID,%s",buf);	
	FrozenFee.getString(buf);
	fprintf(fp,",FrozenFee,%s",buf);	
	FrozenMargin.getString(buf);
	fprintf(fp,",FrozenMargin,%s",buf);	
	FrozenPremium.getString(buf);
	fprintf(fp,",FrozenPremium,%s",buf);	
	AccountID.getString(buf);
	fprintf(fp,",AccountID,%s",buf);	
	OrderUserID.getString(buf);
	fprintf(fp,",OrderUserID,%s",buf);	
	TradeType.getString(buf);
	fprintf(fp,",TradeType,%s",buf);	
	DealFlag.getString(buf);
	fprintf(fp,",DealFlag,%s",buf);	
	TradeCommision.getString(buf);
	fprintf(fp,",TradeCommision,%s",buf);	
	TradeAmnt.getString(buf);
	fprintf(fp,",TradeAmnt,%s",buf);	
	CancleVolume.getString(buf);
	fprintf(fp,",CancleVolume,%s",buf);	
	RequestID.getString(buf);
	fprintf(fp,",RequestID,%s",buf);	
	APIID.getString(buf);
	fprintf(fp,",APIID,%s",buf);	
	IPAddress.getString(buf);
	fprintf(fp,",IPAddress,%s",buf);	
	MacAddress.getString(buf);
	fprintf(fp,",MacAddress,%s",buf);	
	FTdRecvDown.getString(buf);
	fprintf(fp,",FTdRecvDown,%s",buf);	
	CoreRecvDown.getString(buf);
	fprintf(fp,",CoreRecvDown,%s",buf);	
	CoreSendUp.getString(buf);
	fprintf(fp,",CoreSendUp,%s",buf);	
	CoreRecvUp.getString(buf);
	fprintf(fp,",CoreRecvUp,%s",buf);	
	CoreSendDown.getString(buf);
	fprintf(fp,",CoreSendDown,%s",buf);	
	FTdSendDown.getString(buf);
	fprintf(fp,",FTdSendDown,%s",buf);	
	MarginCombType.getString(buf);
	fprintf(fp,",MarginCombType,%s",buf);	
	InstrumentGroupID.getString(buf);
	fprintf(fp,",InstrumentGroupID,%s",buf);	
}

void CWriteableOrder::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	OrderSysID.getString(buf);
	sprintf(p,"OrderSysID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	UserID.getString(buf);
	sprintf(p,"UserID=%s,",buf);
	p+=strlen(p);
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	UserOrderLocalID.getString(buf);
	sprintf(p,"UserOrderLocalID=%s,",buf);
	p+=strlen(p);
	OrderPriceType.getString(buf);
	sprintf(p,"OrderPriceType=%s,",buf);
	p+=strlen(p);
	Direction.getString(buf);
	sprintf(p,"Direction=%s,",buf);
	p+=strlen(p);
	OffsetFlag.getString(buf);
	sprintf(p,"OffsetFlag=%s,",buf);
	p+=strlen(p);
	HedgeFlag.getString(buf);
	sprintf(p,"HedgeFlag=%s,",buf);
	p+=strlen(p);
	LimitPrice.getString(buf);
	sprintf(p,"LimitPrice=%s,",buf);
	p+=strlen(p);
	Volume.getString(buf);
	sprintf(p,"Volume=%s,",buf);
	p+=strlen(p);
	TimeCondition.getString(buf);
	sprintf(p,"TimeCondition=%s,",buf);
	p+=strlen(p);
	GTDDate.getString(buf);
	sprintf(p,"GTDDate=%s,",buf);
	p+=strlen(p);
	VolumeCondition.getString(buf);
	sprintf(p,"VolumeCondition=%s,",buf);
	p+=strlen(p);
	MinVolume.getString(buf);
	sprintf(p,"MinVolume=%s,",buf);
	p+=strlen(p);
	StopPrice.getString(buf);
	sprintf(p,"StopPrice=%s,",buf);
	p+=strlen(p);
	ForceCloseReason.getString(buf);
	sprintf(p,"ForceCloseReason=%s,",buf);
	p+=strlen(p);
	IsAutoSuspend.getString(buf);
	sprintf(p,"IsAutoSuspend=%s,",buf);
	p+=strlen(p);
	BusinessUnit.getString(buf);
	sprintf(p,"BusinessUnit=%s,",buf);
	p+=strlen(p);
	UserCustom.getString(buf);
	sprintf(p,"UserCustom=%s,",buf);
	p+=strlen(p);
	BranchID.getString(buf);
	sprintf(p,"BranchID=%s,",buf);
	p+=strlen(p);
	RecNum.getString(buf);
	sprintf(p,"RecNum=%s,",buf);
	p+=strlen(p);
	BusinessType.getString(buf);
	sprintf(p,"BusinessType=%s,",buf);
	p+=strlen(p);
	TradingDay.getString(buf);
	sprintf(p,"TradingDay=%s,",buf);
	p+=strlen(p);
	ParticipantID.getString(buf);
	sprintf(p,"ParticipantID=%s,",buf);
	p+=strlen(p);
	ClientID.getString(buf);
	sprintf(p,"ClientID=%s,",buf);
	p+=strlen(p);
	SeatID.getString(buf);
	sprintf(p,"SeatID=%s,",buf);
	p+=strlen(p);
	InsertTime.getString(buf);
	sprintf(p,"InsertTime=%s,",buf);
	p+=strlen(p);
	OrderLocalID.getString(buf);
	sprintf(p,"OrderLocalID=%s,",buf);
	p+=strlen(p);
	OrderSource.getString(buf);
	sprintf(p,"OrderSource=%s,",buf);
	p+=strlen(p);
	OrderStatus.getString(buf);
	sprintf(p,"OrderStatus=%s,",buf);
	p+=strlen(p);
	CancelTime.getString(buf);
	sprintf(p,"CancelTime=%s,",buf);
	p+=strlen(p);
	CancelUserID.getString(buf);
	sprintf(p,"CancelUserID=%s,",buf);
	p+=strlen(p);
	VolumeTraded.getString(buf);
	sprintf(p,"VolumeTraded=%s,",buf);
	p+=strlen(p);
	VolumeRemain.getString(buf);
	sprintf(p,"VolumeRemain=%s,",buf);
	p+=strlen(p);
	FrontID.getString(buf);
	sprintf(p,"FrontID=%s,",buf);
	p+=strlen(p);
	SessionID.getString(buf);
	sprintf(p,"SessionID=%s,",buf);
	p+=strlen(p);
	FrozenFee.getString(buf);
	sprintf(p,"FrozenFee=%s,",buf);
	p+=strlen(p);
	FrozenMargin.getString(buf);
	sprintf(p,"FrozenMargin=%s,",buf);
	p+=strlen(p);
	FrozenPremium.getString(buf);
	sprintf(p,"FrozenPremium=%s,",buf);
	p+=strlen(p);
	AccountID.getString(buf);
	sprintf(p,"AccountID=%s,",buf);
	p+=strlen(p);
	OrderUserID.getString(buf);
	sprintf(p,"OrderUserID=%s,",buf);
	p+=strlen(p);
	TradeType.getString(buf);
	sprintf(p,"TradeType=%s,",buf);
	p+=strlen(p);
	DealFlag.getString(buf);
	sprintf(p,"DealFlag=%s,",buf);
	p+=strlen(p);
	TradeCommision.getString(buf);
	sprintf(p,"TradeCommision=%s,",buf);
	p+=strlen(p);
	TradeAmnt.getString(buf);
	sprintf(p,"TradeAmnt=%s,",buf);
	p+=strlen(p);
	CancleVolume.getString(buf);
	sprintf(p,"CancleVolume=%s,",buf);
	p+=strlen(p);
	RequestID.getString(buf);
	sprintf(p,"RequestID=%s,",buf);
	p+=strlen(p);
	APIID.getString(buf);
	sprintf(p,"APIID=%s,",buf);
	p+=strlen(p);
	IPAddress.getString(buf);
	sprintf(p,"IPAddress=%s,",buf);
	p+=strlen(p);
	MacAddress.getString(buf);
	sprintf(p,"MacAddress=%s,",buf);
	p+=strlen(p);
	FTdRecvDown.getString(buf);
	sprintf(p,"FTdRecvDown=%s,",buf);
	p+=strlen(p);
	CoreRecvDown.getString(buf);
	sprintf(p,"CoreRecvDown=%s,",buf);
	p+=strlen(p);
	CoreSendUp.getString(buf);
	sprintf(p,"CoreSendUp=%s,",buf);
	p+=strlen(p);
	CoreRecvUp.getString(buf);
	sprintf(p,"CoreRecvUp=%s,",buf);
	p+=strlen(p);
	CoreSendDown.getString(buf);
	sprintf(p,"CoreSendDown=%s,",buf);
	p+=strlen(p);
	FTdSendDown.getString(buf);
	sprintf(p,"FTdSendDown=%s,",buf);
	p+=strlen(p);
	MarginCombType.getString(buf);
	sprintf(p,"MarginCombType=%s,",buf);
	p+=strlen(p);
	InstrumentGroupID.getString(buf);
	sprintf(p,"InstrumentGroupID=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableOrder::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"COrder");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	OrderSysID.getString(buf);
	pLogger->output(indent+1,0,"OrderSysID=%s 系统报单编号",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编号",buf);
	UserID.getString(buf);
	pLogger->output(indent+1,0,"UserID=%s 用户代码",buf);
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	UserOrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"UserOrderLocalID=%s 用户本地报单号",buf);
	OrderPriceType.getString(buf);
	pLogger->output(indent+1,0,"OrderPriceType=%s 价格类型",buf);
	Direction.getString(buf);
	pLogger->output(indent+1,0,"Direction=%s 买卖方向",buf);
	OffsetFlag.getString(buf);
	pLogger->output(indent+1,0,"OffsetFlag=%s 开平标志",buf);
	HedgeFlag.getString(buf);
	pLogger->output(indent+1,0,"HedgeFlag=%s 投机套保标志",buf);
	LimitPrice.getString(buf);
	pLogger->output(indent+1,0,"LimitPrice=%s 价格",buf);
	Volume.getString(buf);
	pLogger->output(indent+1,0,"Volume=%s 数量",buf);
	TimeCondition.getString(buf);
	pLogger->output(indent+1,0,"TimeCondition=%s 有效期类型",buf);
	GTDDate.getString(buf);
	pLogger->output(indent+1,0,"GTDDate=%s GTD日期",buf);
	VolumeCondition.getString(buf);
	pLogger->output(indent+1,0,"VolumeCondition=%s 成交量类型",buf);
	MinVolume.getString(buf);
	pLogger->output(indent+1,0,"MinVolume=%s 最小成交量",buf);
	StopPrice.getString(buf);
	pLogger->output(indent+1,0,"StopPrice=%s 止损价",buf);
	ForceCloseReason.getString(buf);
	pLogger->output(indent+1,0,"ForceCloseReason=%s 强平原因",buf);
	IsAutoSuspend.getString(buf);
	pLogger->output(indent+1,0,"IsAutoSuspend=%s 自动挂起标志",buf);
	BusinessUnit.getString(buf);
	pLogger->output(indent+1,0,"BusinessUnit=%s 业务单元",buf);
	UserCustom.getString(buf);
	pLogger->output(indent+1,0,"UserCustom=%s 用户自定义域",buf);
	BranchID.getString(buf);
	pLogger->output(indent+1,0,"BranchID=%s 营业部代码",buf);
	RecNum.getString(buf);
	pLogger->output(indent+1,0,"RecNum=%s 记录编号",buf);
	BusinessType.getString(buf);
	pLogger->output(indent+1,0,"BusinessType=%s 业务类别",buf);
	TradingDay.getString(buf);
	pLogger->output(indent+1,0,"TradingDay=%s 交易日",buf);
	ParticipantID.getString(buf);
	pLogger->output(indent+1,0,"ParticipantID=%s 会员编号",buf);
	ClientID.getString(buf);
	pLogger->output(indent+1,0,"ClientID=%s 客户号",buf);
	SeatID.getString(buf);
	pLogger->output(indent+1,0,"SeatID=%s 下单席位号",buf);
	InsertTime.getString(buf);
	pLogger->output(indent+1,0,"InsertTime=%s 插入时间",buf);
	OrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"OrderLocalID=%s 本地报单编号",buf);
	OrderSource.getString(buf);
	pLogger->output(indent+1,0,"OrderSource=%s 报单来源",buf);
	OrderStatus.getString(buf);
	pLogger->output(indent+1,0,"OrderStatus=%s 报单状态",buf);
	CancelTime.getString(buf);
	pLogger->output(indent+1,0,"CancelTime=%s 撤销时间",buf);
	CancelUserID.getString(buf);
	pLogger->output(indent+1,0,"CancelUserID=%s 撤单用户编号",buf);
	VolumeTraded.getString(buf);
	pLogger->output(indent+1,0,"VolumeTraded=%s 今成交数量",buf);
	VolumeRemain.getString(buf);
	pLogger->output(indent+1,0,"VolumeRemain=%s 剩余数量",buf);
	FrontID.getString(buf);
	pLogger->output(indent+1,0,"FrontID=%s 前置编号",buf);
	SessionID.getString(buf);
	pLogger->output(indent+1,0,"SessionID=%s 会话编号",buf);
	FrozenFee.getString(buf);
	pLogger->output(indent+1,0,"FrozenFee=%s 冻结手续费",buf);
	FrozenMargin.getString(buf);
	pLogger->output(indent+1,0,"FrozenMargin=%s 冻结的保证金",buf);
	FrozenPremium.getString(buf);
	pLogger->output(indent+1,0,"FrozenPremium=%s 期权权利金收支",buf);
	AccountID.getString(buf);
	pLogger->output(indent+1,0,"AccountID=%s 资金帐号",buf);
	OrderUserID.getString(buf);
	pLogger->output(indent+1,0,"OrderUserID=%s 下单用户编号",buf);
	TradeType.getString(buf);
	pLogger->output(indent+1,0,"TradeType=%s 交易类型",buf);
	DealFlag.getString(buf);
	pLogger->output(indent+1,0,"DealFlag=%s 处理标志",buf);
	TradeCommision.getString(buf);
	pLogger->output(indent+1,0,"TradeCommision=%s 已成交佣金",buf);
	TradeAmnt.getString(buf);
	pLogger->output(indent+1,0,"TradeAmnt=%s 成交金额",buf);
	CancleVolume.getString(buf);
	pLogger->output(indent+1,0,"CancleVolume=%s 撤单数量",buf);
	RequestID.getString(buf);
	pLogger->output(indent+1,0,"RequestID=%s 请求编号",buf);
	APIID.getString(buf);
	pLogger->output(indent+1,0,"APIID=%s 通道对应的APIID",buf);
	IPAddress.getString(buf);
	pLogger->output(indent+1,0,"IPAddress=%s 下单IP地址",buf);
	MacAddress.getString(buf);
	pLogger->output(indent+1,0,"MacAddress=%s 下单MAC地址",buf);
	FTdRecvDown.getString(buf);
	pLogger->output(indent+1,0,"FTdRecvDown=%s Ftdengine接受下层时间戳",buf);
	CoreRecvDown.getString(buf);
	pLogger->output(indent+1,0,"CoreRecvDown=%s 接受下层时间戳",buf);
	CoreSendUp.getString(buf);
	pLogger->output(indent+1,0,"CoreSendUp=%s 发送上层时间戳",buf);
	CoreRecvUp.getString(buf);
	pLogger->output(indent+1,0,"CoreRecvUp=%s 接受上层时间戳",buf);
	CoreSendDown.getString(buf);
	pLogger->output(indent+1,0,"CoreSendDown=%s 发送下层时间戳",buf);
	FTdSendDown.getString(buf);
	pLogger->output(indent+1,0,"FTdSendDown=%s Ftdengine接受下层时间戳",buf);
	MarginCombType.getString(buf);
	pLogger->output(indent+1,0,"MarginCombType=%s 保证金组合类型",buf);
	InstrumentGroupID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentGroupID=%s 合约组代码",buf);
	pLogger->output(indent,0,"}");
}

COrderIterator::~COrderIterator(void)
{
}


void COrderIterator::dump(FILE *output)
{
	COrder *pOrder;
	
	while ((pOrder=next())!=NULL)
	{
		pOrder->dump(output);
	}
}



void CWriteableTrade::writeCSVHead(FILE *output)
{
	fprintf(output,"TradingDay,BrokerID,ExchangeID,ParticipantID,SeatID,InvestorID,ClientID,UserID,TradeID,OrderSysID,UserOrderLocalID,InstrumentID,Direction,OffsetFlag,HedgeFlag,TradePrice,TradeVolume,TradeTime,ClearingPartID,TradeAmnt,RecNum,TradeType,Commision,StampTax,TransferFee,UsedFee,UsedMargin,Premium,AccountID,OrderUserID,OrderLocalID,IsForgeRtn,BusinessType\n");
}
	
void CWriteableTrade::init(void)
{
	TradingDay.clear();
	BrokerID.clear();
	ExchangeID.clear();
	ParticipantID.clear();
	SeatID.clear();
	InvestorID.clear();
	ClientID.clear();
	UserID.clear();
	TradeID.clear();
	OrderSysID.clear();
	UserOrderLocalID.clear();
	InstrumentID.clear();
	Direction.clear();
	OffsetFlag.clear();
	HedgeFlag.clear();
	TradePrice.clear();
	TradeVolume.clear();
	TradeTime.clear();
	ClearingPartID.clear();
	TradeAmnt.clear();
	RecNum.clear();
	TradeType.clear();
	Commision.clear();
	StampTax.clear();
	TransferFee.clear();
	UsedFee.clear();
	UsedMargin.clear();
	Premium.clear();
	AccountID.clear();
	OrderUserID.clear();
	OrderLocalID.clear();
	IsForgeRtn.clear();
	BusinessType.clear();
}

int CWriteableTrade::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableTrade),input)!=sizeof(CWriteableTrade))
		return 0;
	else
		return 1;
}
	
int CWriteableTrade::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			TradingDay=token;
		}
		else
		{
			TradingDay="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ParticipantID=token;
		}
		else
		{
			ParticipantID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SeatID=token;
		}
		else
		{
			SeatID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ClientID=token;
		}
		else
		{
			ClientID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserID=token;
		}
		else
		{
			UserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeID=token;
		}
		else
		{
			TradeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderSysID=token;
		}
		else
		{
			OrderSysID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserOrderLocalID=token;
		}
		else
		{
			UserOrderLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Direction=token;
		}
		else
		{
			Direction="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OffsetFlag=token;
		}
		else
		{
			OffsetFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			HedgeFlag=token;
		}
		else
		{
			HedgeFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradePrice=token;
		}
		else
		{
			TradePrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeVolume=token;
		}
		else
		{
			TradeVolume="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeTime=token;
		}
		else
		{
			TradeTime="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ClearingPartID=token;
		}
		else
		{
			ClearingPartID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeAmnt=token;
		}
		else
		{
			TradeAmnt="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			RecNum=token;
		}
		else
		{
			RecNum="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeType=token;
		}
		else
		{
			TradeType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Commision=token;
		}
		else
		{
			Commision="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			StampTax=token;
		}
		else
		{
			StampTax="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TransferFee=token;
		}
		else
		{
			TransferFee="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UsedFee=token;
		}
		else
		{
			UsedFee="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UsedMargin=token;
		}
		else
		{
			UsedMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Premium=token;
		}
		else
		{
			Premium="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			AccountID=token;
		}
		else
		{
			AccountID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderUserID=token;
		}
		else
		{
			OrderUserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderLocalID=token;
		}
		else
		{
			OrderLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IsForgeRtn=token;
		}
		else
		{
			IsForgeRtn="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			BusinessType=token;
		}
		else
		{
			BusinessType="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"TradingDay"))
			{
				TradingDay=token;
			}
			else if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"ParticipantID"))
			{
				ParticipantID=token;
			}
			else if (!strcmp(fieldName,"SeatID"))
			{
				SeatID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"ClientID"))
			{
				ClientID=token;
			}
			else if (!strcmp(fieldName,"UserID"))
			{
				UserID=token;
			}
			else if (!strcmp(fieldName,"TradeID"))
			{
				TradeID=token;
			}
			else if (!strcmp(fieldName,"OrderSysID"))
			{
				OrderSysID=token;
			}
			else if (!strcmp(fieldName,"UserOrderLocalID"))
			{
				UserOrderLocalID=token;
			}
			else if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"Direction"))
			{
				Direction=token;
			}
			else if (!strcmp(fieldName,"OffsetFlag"))
			{
				OffsetFlag=token;
			}
			else if (!strcmp(fieldName,"HedgeFlag"))
			{
				HedgeFlag=token;
			}
			else if (!strcmp(fieldName,"TradePrice"))
			{
				TradePrice=token;
			}
			else if (!strcmp(fieldName,"TradeVolume"))
			{
				TradeVolume=token;
			}
			else if (!strcmp(fieldName,"TradeTime"))
			{
				TradeTime=token;
			}
			else if (!strcmp(fieldName,"ClearingPartID"))
			{
				ClearingPartID=token;
			}
			else if (!strcmp(fieldName,"TradeAmnt"))
			{
				TradeAmnt=token;
			}
			else if (!strcmp(fieldName,"RecNum"))
			{
				RecNum=token;
			}
			else if (!strcmp(fieldName,"TradeType"))
			{
				TradeType=token;
			}
			else if (!strcmp(fieldName,"Commision"))
			{
				Commision=token;
			}
			else if (!strcmp(fieldName,"StampTax"))
			{
				StampTax=token;
			}
			else if (!strcmp(fieldName,"TransferFee"))
			{
				TransferFee=token;
			}
			else if (!strcmp(fieldName,"UsedFee"))
			{
				UsedFee=token;
			}
			else if (!strcmp(fieldName,"UsedMargin"))
			{
				UsedMargin=token;
			}
			else if (!strcmp(fieldName,"Premium"))
			{
				Premium=token;
			}
			else if (!strcmp(fieldName,"AccountID"))
			{
				AccountID=token;
			}
			else if (!strcmp(fieldName,"OrderUserID"))
			{
				OrderUserID=token;
			}
			else if (!strcmp(fieldName,"OrderLocalID"))
			{
				OrderLocalID=token;
			}
			else if (!strcmp(fieldName,"IsForgeRtn"))
			{
				IsForgeRtn=token;
			}
			else if (!strcmp(fieldName,"BusinessType"))
			{
				BusinessType=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableTrade::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableTrade),output)!=sizeof(CWriteableTrade))
		return 0;
	else
		return 1;
}

int CWriteableTrade::writeCSV(FILE *output) const
{
	char buffer[1025];
	TradingDay.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ParticipantID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SeatID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ClientID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderSysID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserOrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Direction.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OffsetFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	HedgeFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradePrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeVolume.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeTime.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ClearingPartID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeAmnt.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	RecNum.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Commision.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	StampTax.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TransferFee.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UsedFee.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UsedMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Premium.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	AccountID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderUserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IsForgeRtn.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	BusinessType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableTrade::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCTrade%s = {\n", index_buf);
	TradingDay.getString(buf);
	fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);	
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,"\t\tParticipantID = %s    [会员编号]\n",buf);	
	SeatID.getString(buf);
	fprintf(fp,"\t\tSeatID = %s    [下单席位号]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);	
	ClientID.getString(buf);
	fprintf(fp,"\t\tClientID = %s    [客户号]\n",buf);	
	UserID.getString(buf);
	fprintf(fp,"\t\tUserID = %s    [用户编号]\n",buf);	
	TradeID.getString(buf);
	fprintf(fp,"\t\tTradeID = %s    [成交编号]\n",buf);	
	OrderSysID.getString(buf);
	fprintf(fp,"\t\tOrderSysID = %s    [报单编号]\n",buf);	
	UserOrderLocalID.getString(buf);
	fprintf(fp,"\t\tUserOrderLocalID = %s    [本地报单编号]\n",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	Direction.getString(buf);
	fprintf(fp,"\t\tDirection = %s    [买卖方向]\n",buf);	
	OffsetFlag.getString(buf);
	fprintf(fp,"\t\tOffsetFlag = %s    [开平标志]\n",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);	
	TradePrice.getString(buf);
	fprintf(fp,"\t\tTradePrice = %s    [成交价格]\n",buf);	
	TradeVolume.getString(buf);
	fprintf(fp,"\t\tTradeVolume = %s    [成交数量]\n",buf);	
	TradeTime.getString(buf);
	fprintf(fp,"\t\tTradeTime = %s    [成交时间]\n",buf);	
	ClearingPartID.getString(buf);
	fprintf(fp,"\t\tClearingPartID = %s    [清算会员编号]\n",buf);	
	TradeAmnt.getString(buf);
	fprintf(fp,"\t\tTradeAmnt = %s    [成交金额]\n",buf);	
	RecNum.getString(buf);
	fprintf(fp,"\t\tRecNum = %s    [记录编号]\n",buf);	
	TradeType.getString(buf);
	fprintf(fp,"\t\tTradeType = %s    [交易类型]\n",buf);	
	Commision.getString(buf);
	fprintf(fp,"\t\tCommision = %s    [佣金]\n",buf);	
	StampTax.getString(buf);
	fprintf(fp,"\t\tStampTax = %s    [印花税]\n",buf);	
	TransferFee.getString(buf);
	fprintf(fp,"\t\tTransferFee = %s    [过户费]\n",buf);	
	UsedFee.getString(buf);
	fprintf(fp,"\t\tUsedFee = %s    [手续费]\n",buf);	
	UsedMargin.getString(buf);
	fprintf(fp,"\t\tUsedMargin = %s    [占用的保证金]\n",buf);	
	Premium.getString(buf);
	fprintf(fp,"\t\tPremium = %s    [占用权利金]\n",buf);	
	AccountID.getString(buf);
	fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);	
	OrderUserID.getString(buf);
	fprintf(fp,"\t\tOrderUserID = %s    [下单用户编号]\n",buf);	
	OrderLocalID.getString(buf);
	fprintf(fp,"\t\tOrderLocalID = %s    [本地报单编号]\n",buf);	
	IsForgeRtn.getString(buf);
	fprintf(fp,"\t\tIsForgeRtn = %s    [伪造Rtn]\n",buf);	
	BusinessType.getString(buf);
	fprintf(fp,"\t\tBusinessType = %s    [业务类别]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableTrade::dumpDiff(FILE *fp, const CWriteableTrade *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCTrade = {\n");
	TradingDay.getString(buf);
	if (compare(TradingDay.getValue(),pOriginal->TradingDay.getValue())!=0)
	{
		pOriginal->TradingDay.getString(bufOriginal);
		fprintf(fp,"\t\tTradingDay = %s -> %s    [交易日]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);
	}
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	ParticipantID.getString(buf);
	if (compare(ParticipantID.getValue(),pOriginal->ParticipantID.getValue())!=0)
	{
		pOriginal->ParticipantID.getString(bufOriginal);
		fprintf(fp,"\t\tParticipantID = %s -> %s    [会员编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tParticipantID = %s    [会员编号]\n",buf);
	}
	SeatID.getString(buf);
	if (compare(SeatID.getValue(),pOriginal->SeatID.getValue())!=0)
	{
		pOriginal->SeatID.getString(bufOriginal);
		fprintf(fp,"\t\tSeatID = %s -> %s    [下单席位号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSeatID = %s    [下单席位号]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);
	}
	ClientID.getString(buf);
	if (compare(ClientID.getValue(),pOriginal->ClientID.getValue())!=0)
	{
		pOriginal->ClientID.getString(bufOriginal);
		fprintf(fp,"\t\tClientID = %s -> %s    [客户号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tClientID = %s    [客户号]\n",buf);
	}
	UserID.getString(buf);
	if (compare(UserID.getValue(),pOriginal->UserID.getValue())!=0)
	{
		pOriginal->UserID.getString(bufOriginal);
		fprintf(fp,"\t\tUserID = %s -> %s    [用户编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserID = %s    [用户编号]\n",buf);
	}
	TradeID.getString(buf);
	if (compare(TradeID.getValue(),pOriginal->TradeID.getValue())!=0)
	{
		pOriginal->TradeID.getString(bufOriginal);
		fprintf(fp,"\t\tTradeID = %s -> %s    [成交编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeID = %s    [成交编号]\n",buf);
	}
	OrderSysID.getString(buf);
	if (compare(OrderSysID.getValue(),pOriginal->OrderSysID.getValue())!=0)
	{
		pOriginal->OrderSysID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderSysID = %s -> %s    [报单编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderSysID = %s    [报单编号]\n",buf);
	}
	UserOrderLocalID.getString(buf);
	if (compare(UserOrderLocalID.getValue(),pOriginal->UserOrderLocalID.getValue())!=0)
	{
		pOriginal->UserOrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tUserOrderLocalID = %s -> %s    [本地报单编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserOrderLocalID = %s    [本地报单编号]\n",buf);
	}
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	Direction.getString(buf);
	if (compare(Direction.getValue(),pOriginal->Direction.getValue())!=0)
	{
		pOriginal->Direction.getString(bufOriginal);
		fprintf(fp,"\t\tDirection = %s -> %s    [买卖方向]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDirection = %s    [买卖方向]\n",buf);
	}
	OffsetFlag.getString(buf);
	if (compare(OffsetFlag.getValue(),pOriginal->OffsetFlag.getValue())!=0)
	{
		pOriginal->OffsetFlag.getString(bufOriginal);
		fprintf(fp,"\t\tOffsetFlag = %s -> %s    [开平标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOffsetFlag = %s    [开平标志]\n",buf);
	}
	HedgeFlag.getString(buf);
	if (compare(HedgeFlag.getValue(),pOriginal->HedgeFlag.getValue())!=0)
	{
		pOriginal->HedgeFlag.getString(bufOriginal);
		fprintf(fp,"\t\tHedgeFlag = %s -> %s    [投机套保标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);
	}
	TradePrice.getString(buf);
	if (compare(TradePrice.getValue(),pOriginal->TradePrice.getValue())!=0)
	{
		pOriginal->TradePrice.getString(bufOriginal);
		fprintf(fp,"\t\tTradePrice = %s -> %s    [成交价格]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradePrice = %s    [成交价格]\n",buf);
	}
	TradeVolume.getString(buf);
	if (compare(TradeVolume.getValue(),pOriginal->TradeVolume.getValue())!=0)
	{
		pOriginal->TradeVolume.getString(bufOriginal);
		fprintf(fp,"\t\tTradeVolume = %s -> %s    [成交数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeVolume = %s    [成交数量]\n",buf);
	}
	TradeTime.getString(buf);
	if (compare(TradeTime.getValue(),pOriginal->TradeTime.getValue())!=0)
	{
		pOriginal->TradeTime.getString(bufOriginal);
		fprintf(fp,"\t\tTradeTime = %s -> %s    [成交时间]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeTime = %s    [成交时间]\n",buf);
	}
	ClearingPartID.getString(buf);
	if (compare(ClearingPartID.getValue(),pOriginal->ClearingPartID.getValue())!=0)
	{
		pOriginal->ClearingPartID.getString(bufOriginal);
		fprintf(fp,"\t\tClearingPartID = %s -> %s    [清算会员编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tClearingPartID = %s    [清算会员编号]\n",buf);
	}
	TradeAmnt.getString(buf);
	if (compare(TradeAmnt.getValue(),pOriginal->TradeAmnt.getValue())!=0)
	{
		pOriginal->TradeAmnt.getString(bufOriginal);
		fprintf(fp,"\t\tTradeAmnt = %s -> %s    [成交金额]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeAmnt = %s    [成交金额]\n",buf);
	}
	RecNum.getString(buf);
	if (compare(RecNum.getValue(),pOriginal->RecNum.getValue())!=0)
	{
		pOriginal->RecNum.getString(bufOriginal);
		fprintf(fp,"\t\tRecNum = %s -> %s    [记录编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tRecNum = %s    [记录编号]\n",buf);
	}
	TradeType.getString(buf);
	if (compare(TradeType.getValue(),pOriginal->TradeType.getValue())!=0)
	{
		pOriginal->TradeType.getString(bufOriginal);
		fprintf(fp,"\t\tTradeType = %s -> %s    [交易类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeType = %s    [交易类型]\n",buf);
	}
	Commision.getString(buf);
	if (compare(Commision.getValue(),pOriginal->Commision.getValue())!=0)
	{
		pOriginal->Commision.getString(bufOriginal);
		fprintf(fp,"\t\tCommision = %s -> %s    [佣金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCommision = %s    [佣金]\n",buf);
	}
	StampTax.getString(buf);
	if (compare(StampTax.getValue(),pOriginal->StampTax.getValue())!=0)
	{
		pOriginal->StampTax.getString(bufOriginal);
		fprintf(fp,"\t\tStampTax = %s -> %s    [印花税]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tStampTax = %s    [印花税]\n",buf);
	}
	TransferFee.getString(buf);
	if (compare(TransferFee.getValue(),pOriginal->TransferFee.getValue())!=0)
	{
		pOriginal->TransferFee.getString(bufOriginal);
		fprintf(fp,"\t\tTransferFee = %s -> %s    [过户费]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTransferFee = %s    [过户费]\n",buf);
	}
	UsedFee.getString(buf);
	if (compare(UsedFee.getValue(),pOriginal->UsedFee.getValue())!=0)
	{
		pOriginal->UsedFee.getString(bufOriginal);
		fprintf(fp,"\t\tUsedFee = %s -> %s    [手续费]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUsedFee = %s    [手续费]\n",buf);
	}
	UsedMargin.getString(buf);
	if (compare(UsedMargin.getValue(),pOriginal->UsedMargin.getValue())!=0)
	{
		pOriginal->UsedMargin.getString(bufOriginal);
		fprintf(fp,"\t\tUsedMargin = %s -> %s    [占用的保证金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUsedMargin = %s    [占用的保证金]\n",buf);
	}
	Premium.getString(buf);
	if (compare(Premium.getValue(),pOriginal->Premium.getValue())!=0)
	{
		pOriginal->Premium.getString(bufOriginal);
		fprintf(fp,"\t\tPremium = %s -> %s    [占用权利金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPremium = %s    [占用权利金]\n",buf);
	}
	AccountID.getString(buf);
	if (compare(AccountID.getValue(),pOriginal->AccountID.getValue())!=0)
	{
		pOriginal->AccountID.getString(bufOriginal);
		fprintf(fp,"\t\tAccountID = %s -> %s    [资金帐号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);
	}
	OrderUserID.getString(buf);
	if (compare(OrderUserID.getValue(),pOriginal->OrderUserID.getValue())!=0)
	{
		pOriginal->OrderUserID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderUserID = %s -> %s    [下单用户编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderUserID = %s    [下单用户编号]\n",buf);
	}
	OrderLocalID.getString(buf);
	if (compare(OrderLocalID.getValue(),pOriginal->OrderLocalID.getValue())!=0)
	{
		pOriginal->OrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderLocalID = %s -> %s    [本地报单编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderLocalID = %s    [本地报单编号]\n",buf);
	}
	IsForgeRtn.getString(buf);
	if (compare(IsForgeRtn.getValue(),pOriginal->IsForgeRtn.getValue())!=0)
	{
		pOriginal->IsForgeRtn.getString(bufOriginal);
		fprintf(fp,"\t\tIsForgeRtn = %s -> %s    [伪造Rtn]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIsForgeRtn = %s    [伪造Rtn]\n",buf);
	}
	BusinessType.getString(buf);
	if (compare(BusinessType.getValue(),pOriginal->BusinessType.getValue())!=0)
	{
		pOriginal->BusinessType.getString(bufOriginal);
		fprintf(fp,"\t\tBusinessType = %s -> %s    [业务类别]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBusinessType = %s    [业务类别]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableTrade::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	TradingDay.getString(buf);
	fprintf(fp,",TradingDay,%s",buf);	
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,",ParticipantID,%s",buf);	
	SeatID.getString(buf);
	fprintf(fp,",SeatID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	ClientID.getString(buf);
	fprintf(fp,",ClientID,%s",buf);	
	UserID.getString(buf);
	fprintf(fp,",UserID,%s",buf);	
	TradeID.getString(buf);
	fprintf(fp,",TradeID,%s",buf);	
	OrderSysID.getString(buf);
	fprintf(fp,",OrderSysID,%s",buf);	
	UserOrderLocalID.getString(buf);
	fprintf(fp,",UserOrderLocalID,%s",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	Direction.getString(buf);
	fprintf(fp,",Direction,%s",buf);	
	OffsetFlag.getString(buf);
	fprintf(fp,",OffsetFlag,%s",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,",HedgeFlag,%s",buf);	
	TradePrice.getString(buf);
	fprintf(fp,",TradePrice,%s",buf);	
	TradeVolume.getString(buf);
	fprintf(fp,",TradeVolume,%s",buf);	
	TradeTime.getString(buf);
	fprintf(fp,",TradeTime,%s",buf);	
	ClearingPartID.getString(buf);
	fprintf(fp,",ClearingPartID,%s",buf);	
	TradeAmnt.getString(buf);
	fprintf(fp,",TradeAmnt,%s",buf);	
	RecNum.getString(buf);
	fprintf(fp,",RecNum,%s",buf);	
	TradeType.getString(buf);
	fprintf(fp,",TradeType,%s",buf);	
	Commision.getString(buf);
	fprintf(fp,",Commision,%s",buf);	
	StampTax.getString(buf);
	fprintf(fp,",StampTax,%s",buf);	
	TransferFee.getString(buf);
	fprintf(fp,",TransferFee,%s",buf);	
	UsedFee.getString(buf);
	fprintf(fp,",UsedFee,%s",buf);	
	UsedMargin.getString(buf);
	fprintf(fp,",UsedMargin,%s",buf);	
	Premium.getString(buf);
	fprintf(fp,",Premium,%s",buf);	
	AccountID.getString(buf);
	fprintf(fp,",AccountID,%s",buf);	
	OrderUserID.getString(buf);
	fprintf(fp,",OrderUserID,%s",buf);	
	OrderLocalID.getString(buf);
	fprintf(fp,",OrderLocalID,%s",buf);	
	IsForgeRtn.getString(buf);
	fprintf(fp,",IsForgeRtn,%s",buf);	
	BusinessType.getString(buf);
	fprintf(fp,",BusinessType,%s",buf);	
}

void CWriteableTrade::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	TradingDay.getString(buf);
	sprintf(p,"TradingDay=%s,",buf);
	p+=strlen(p);
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	ParticipantID.getString(buf);
	sprintf(p,"ParticipantID=%s,",buf);
	p+=strlen(p);
	SeatID.getString(buf);
	sprintf(p,"SeatID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	ClientID.getString(buf);
	sprintf(p,"ClientID=%s,",buf);
	p+=strlen(p);
	UserID.getString(buf);
	sprintf(p,"UserID=%s,",buf);
	p+=strlen(p);
	TradeID.getString(buf);
	sprintf(p,"TradeID=%s,",buf);
	p+=strlen(p);
	OrderSysID.getString(buf);
	sprintf(p,"OrderSysID=%s,",buf);
	p+=strlen(p);
	UserOrderLocalID.getString(buf);
	sprintf(p,"UserOrderLocalID=%s,",buf);
	p+=strlen(p);
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	Direction.getString(buf);
	sprintf(p,"Direction=%s,",buf);
	p+=strlen(p);
	OffsetFlag.getString(buf);
	sprintf(p,"OffsetFlag=%s,",buf);
	p+=strlen(p);
	HedgeFlag.getString(buf);
	sprintf(p,"HedgeFlag=%s,",buf);
	p+=strlen(p);
	TradePrice.getString(buf);
	sprintf(p,"TradePrice=%s,",buf);
	p+=strlen(p);
	TradeVolume.getString(buf);
	sprintf(p,"TradeVolume=%s,",buf);
	p+=strlen(p);
	TradeTime.getString(buf);
	sprintf(p,"TradeTime=%s,",buf);
	p+=strlen(p);
	ClearingPartID.getString(buf);
	sprintf(p,"ClearingPartID=%s,",buf);
	p+=strlen(p);
	TradeAmnt.getString(buf);
	sprintf(p,"TradeAmnt=%s,",buf);
	p+=strlen(p);
	RecNum.getString(buf);
	sprintf(p,"RecNum=%s,",buf);
	p+=strlen(p);
	TradeType.getString(buf);
	sprintf(p,"TradeType=%s,",buf);
	p+=strlen(p);
	Commision.getString(buf);
	sprintf(p,"Commision=%s,",buf);
	p+=strlen(p);
	StampTax.getString(buf);
	sprintf(p,"StampTax=%s,",buf);
	p+=strlen(p);
	TransferFee.getString(buf);
	sprintf(p,"TransferFee=%s,",buf);
	p+=strlen(p);
	UsedFee.getString(buf);
	sprintf(p,"UsedFee=%s,",buf);
	p+=strlen(p);
	UsedMargin.getString(buf);
	sprintf(p,"UsedMargin=%s,",buf);
	p+=strlen(p);
	Premium.getString(buf);
	sprintf(p,"Premium=%s,",buf);
	p+=strlen(p);
	AccountID.getString(buf);
	sprintf(p,"AccountID=%s,",buf);
	p+=strlen(p);
	OrderUserID.getString(buf);
	sprintf(p,"OrderUserID=%s,",buf);
	p+=strlen(p);
	OrderLocalID.getString(buf);
	sprintf(p,"OrderLocalID=%s,",buf);
	p+=strlen(p);
	IsForgeRtn.getString(buf);
	sprintf(p,"IsForgeRtn=%s,",buf);
	p+=strlen(p);
	BusinessType.getString(buf);
	sprintf(p,"BusinessType=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableTrade::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CTrade");
	pLogger->output(indent,0,"{");
	TradingDay.getString(buf);
	pLogger->output(indent+1,0,"TradingDay=%s 交易日",buf);
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	ParticipantID.getString(buf);
	pLogger->output(indent+1,0,"ParticipantID=%s 会员编号",buf);
	SeatID.getString(buf);
	pLogger->output(indent+1,0,"SeatID=%s 下单席位号",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编号",buf);
	ClientID.getString(buf);
	pLogger->output(indent+1,0,"ClientID=%s 客户号",buf);
	UserID.getString(buf);
	pLogger->output(indent+1,0,"UserID=%s 用户编号",buf);
	TradeID.getString(buf);
	pLogger->output(indent+1,0,"TradeID=%s 成交编号",buf);
	OrderSysID.getString(buf);
	pLogger->output(indent+1,0,"OrderSysID=%s 报单编号",buf);
	UserOrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"UserOrderLocalID=%s 本地报单编号",buf);
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	Direction.getString(buf);
	pLogger->output(indent+1,0,"Direction=%s 买卖方向",buf);
	OffsetFlag.getString(buf);
	pLogger->output(indent+1,0,"OffsetFlag=%s 开平标志",buf);
	HedgeFlag.getString(buf);
	pLogger->output(indent+1,0,"HedgeFlag=%s 投机套保标志",buf);
	TradePrice.getString(buf);
	pLogger->output(indent+1,0,"TradePrice=%s 成交价格",buf);
	TradeVolume.getString(buf);
	pLogger->output(indent+1,0,"TradeVolume=%s 成交数量",buf);
	TradeTime.getString(buf);
	pLogger->output(indent+1,0,"TradeTime=%s 成交时间",buf);
	ClearingPartID.getString(buf);
	pLogger->output(indent+1,0,"ClearingPartID=%s 清算会员编号",buf);
	TradeAmnt.getString(buf);
	pLogger->output(indent+1,0,"TradeAmnt=%s 成交金额",buf);
	RecNum.getString(buf);
	pLogger->output(indent+1,0,"RecNum=%s 记录编号",buf);
	TradeType.getString(buf);
	pLogger->output(indent+1,0,"TradeType=%s 交易类型",buf);
	Commision.getString(buf);
	pLogger->output(indent+1,0,"Commision=%s 佣金",buf);
	StampTax.getString(buf);
	pLogger->output(indent+1,0,"StampTax=%s 印花税",buf);
	TransferFee.getString(buf);
	pLogger->output(indent+1,0,"TransferFee=%s 过户费",buf);
	UsedFee.getString(buf);
	pLogger->output(indent+1,0,"UsedFee=%s 手续费",buf);
	UsedMargin.getString(buf);
	pLogger->output(indent+1,0,"UsedMargin=%s 占用的保证金",buf);
	Premium.getString(buf);
	pLogger->output(indent+1,0,"Premium=%s 占用权利金",buf);
	AccountID.getString(buf);
	pLogger->output(indent+1,0,"AccountID=%s 资金帐号",buf);
	OrderUserID.getString(buf);
	pLogger->output(indent+1,0,"OrderUserID=%s 下单用户编号",buf);
	OrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"OrderLocalID=%s 本地报单编号",buf);
	IsForgeRtn.getString(buf);
	pLogger->output(indent+1,0,"IsForgeRtn=%s 伪造Rtn",buf);
	BusinessType.getString(buf);
	pLogger->output(indent+1,0,"BusinessType=%s 业务类别",buf);
	pLogger->output(indent,0,"}");
}

CTradeIterator::~CTradeIterator(void)
{
}


void CTradeIterator::dump(FILE *output)
{
	CTrade *pTrade;
	
	while ((pTrade=next())!=NULL)
	{
		pTrade->dump(output);
	}
}



void CWriteablePreOrder::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,ExchangeID,OrderSysID,InvestorID,UserID,InstrumentID,UserOrderLocalID,OrderPriceType,Direction,OffsetFlag,HedgeFlag,LimitPrice,Volume,TimeCondition,GTDDate,VolumeCondition,MinVolume,StopPrice,ForceCloseReason,IsAutoSuspend,BusinessUnit,UserCustom,BranchID,RecNum,BusinessType,TradingDay,ParticipantID,ClientID,SeatID,InsertTime,OrderLocalID,OrderSource,OrderStatus,CancelTime,CancelUserID,VolumeTraded,VolumeRemain,FrontID,SessionID,FrozenFee,FrozenMargin,FrozenPremium,AccountID,OrderUserID,TradeType,DealFlag,TradeCommision,TradeAmnt,CancleVolume,RequestID,APIID,IPAddress,MacAddress,FTdRecvDown,CoreRecvDown,CoreSendUp,CoreRecvUp,CoreSendDown,FTdSendDown,MarginCombType,InstrumentGroupID\n");
}
	
void CWriteablePreOrder::init(void)
{
	BrokerID.clear();
	ExchangeID.clear();
	OrderSysID.clear();
	InvestorID.clear();
	UserID.clear();
	InstrumentID.clear();
	UserOrderLocalID.clear();
	OrderPriceType.clear();
	Direction.clear();
	OffsetFlag.clear();
	HedgeFlag.clear();
	LimitPrice.clear();
	Volume.clear();
	TimeCondition.clear();
	GTDDate.clear();
	VolumeCondition.clear();
	MinVolume.clear();
	StopPrice.clear();
	ForceCloseReason.clear();
	IsAutoSuspend.clear();
	BusinessUnit.clear();
	UserCustom.clear();
	BranchID.clear();
	RecNum.clear();
	BusinessType.clear();
	TradingDay.clear();
	ParticipantID.clear();
	ClientID.clear();
	SeatID.clear();
	InsertTime.clear();
	OrderLocalID.clear();
	OrderSource.clear();
	OrderStatus.clear();
	CancelTime.clear();
	CancelUserID.clear();
	VolumeTraded.clear();
	VolumeRemain.clear();
	FrontID.clear();
	SessionID.clear();
	FrozenFee.clear();
	FrozenMargin.clear();
	FrozenPremium.clear();
	AccountID.clear();
	OrderUserID.clear();
	TradeType.clear();
	DealFlag.clear();
	TradeCommision.clear();
	TradeAmnt.clear();
	CancleVolume.clear();
	RequestID.clear();
	APIID.clear();
	IPAddress.clear();
	MacAddress.clear();
	FTdRecvDown.clear();
	CoreRecvDown.clear();
	CoreSendUp.clear();
	CoreRecvUp.clear();
	CoreSendDown.clear();
	FTdSendDown.clear();
	MarginCombType.clear();
	InstrumentGroupID.clear();
	pInvestor=NULL;
	pClientTradingID=NULL;
	pInvestorAccount=NULL;
	pInvestorPosition=NULL;
	pInstrument=NULL;
	pInvestorMargin=NULL;
	pInvestorFee=NULL;
	pInvestorOptionFee=NULL;
	pClientGroupPosition=NULL;
}

int CWriteablePreOrder::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteablePreOrder),input)!=sizeof(CWriteablePreOrder))
		return 0;
	else
		return 1;
}
	
int CWriteablePreOrder::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderSysID=token;
		}
		else
		{
			OrderSysID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserID=token;
		}
		else
		{
			UserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserOrderLocalID=token;
		}
		else
		{
			UserOrderLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderPriceType=token;
		}
		else
		{
			OrderPriceType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Direction=token;
		}
		else
		{
			Direction="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OffsetFlag=token;
		}
		else
		{
			OffsetFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			HedgeFlag=token;
		}
		else
		{
			HedgeFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LimitPrice=token;
		}
		else
		{
			LimitPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Volume=token;
		}
		else
		{
			Volume="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TimeCondition=token;
		}
		else
		{
			TimeCondition="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			GTDDate=token;
		}
		else
		{
			GTDDate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			VolumeCondition=token;
		}
		else
		{
			VolumeCondition="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MinVolume=token;
		}
		else
		{
			MinVolume="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			StopPrice=token;
		}
		else
		{
			StopPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ForceCloseReason=token;
		}
		else
		{
			ForceCloseReason="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IsAutoSuspend=token;
		}
		else
		{
			IsAutoSuspend="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			BusinessUnit=token;
		}
		else
		{
			BusinessUnit="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserCustom=token;
		}
		else
		{
			UserCustom="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			BranchID=token;
		}
		else
		{
			BranchID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			RecNum=token;
		}
		else
		{
			RecNum="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			BusinessType=token;
		}
		else
		{
			BusinessType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradingDay=token;
		}
		else
		{
			TradingDay="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ParticipantID=token;
		}
		else
		{
			ParticipantID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ClientID=token;
		}
		else
		{
			ClientID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SeatID=token;
		}
		else
		{
			SeatID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InsertTime=token;
		}
		else
		{
			InsertTime="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderLocalID=token;
		}
		else
		{
			OrderLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderSource=token;
		}
		else
		{
			OrderSource="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderStatus=token;
		}
		else
		{
			OrderStatus="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CancelTime=token;
		}
		else
		{
			CancelTime="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CancelUserID=token;
		}
		else
		{
			CancelUserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			VolumeTraded=token;
		}
		else
		{
			VolumeTraded="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			VolumeRemain=token;
		}
		else
		{
			VolumeRemain="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrontID=token;
		}
		else
		{
			FrontID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SessionID=token;
		}
		else
		{
			SessionID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenFee=token;
		}
		else
		{
			FrozenFee="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenMargin=token;
		}
		else
		{
			FrozenMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenPremium=token;
		}
		else
		{
			FrozenPremium="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			AccountID=token;
		}
		else
		{
			AccountID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderUserID=token;
		}
		else
		{
			OrderUserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeType=token;
		}
		else
		{
			TradeType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			DealFlag=token;
		}
		else
		{
			DealFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeCommision=token;
		}
		else
		{
			TradeCommision="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeAmnt=token;
		}
		else
		{
			TradeAmnt="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CancleVolume=token;
		}
		else
		{
			CancleVolume="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			RequestID=token;
		}
		else
		{
			RequestID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			APIID=token;
		}
		else
		{
			APIID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IPAddress=token;
		}
		else
		{
			IPAddress="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MacAddress=token;
		}
		else
		{
			MacAddress="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FTdRecvDown=token;
		}
		else
		{
			FTdRecvDown="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreRecvDown=token;
		}
		else
		{
			CoreRecvDown="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreSendUp=token;
		}
		else
		{
			CoreSendUp="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreRecvUp=token;
		}
		else
		{
			CoreRecvUp="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreSendDown=token;
		}
		else
		{
			CoreSendDown="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FTdSendDown=token;
		}
		else
		{
			FTdSendDown="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MarginCombType=token;
		}
		else
		{
			MarginCombType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentGroupID=token;
		}
		else
		{
			InstrumentGroupID="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"OrderSysID"))
			{
				OrderSysID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"UserID"))
			{
				UserID=token;
			}
			else if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"UserOrderLocalID"))
			{
				UserOrderLocalID=token;
			}
			else if (!strcmp(fieldName,"OrderPriceType"))
			{
				OrderPriceType=token;
			}
			else if (!strcmp(fieldName,"Direction"))
			{
				Direction=token;
			}
			else if (!strcmp(fieldName,"OffsetFlag"))
			{
				OffsetFlag=token;
			}
			else if (!strcmp(fieldName,"HedgeFlag"))
			{
				HedgeFlag=token;
			}
			else if (!strcmp(fieldName,"LimitPrice"))
			{
				LimitPrice=token;
			}
			else if (!strcmp(fieldName,"Volume"))
			{
				Volume=token;
			}
			else if (!strcmp(fieldName,"TimeCondition"))
			{
				TimeCondition=token;
			}
			else if (!strcmp(fieldName,"GTDDate"))
			{
				GTDDate=token;
			}
			else if (!strcmp(fieldName,"VolumeCondition"))
			{
				VolumeCondition=token;
			}
			else if (!strcmp(fieldName,"MinVolume"))
			{
				MinVolume=token;
			}
			else if (!strcmp(fieldName,"StopPrice"))
			{
				StopPrice=token;
			}
			else if (!strcmp(fieldName,"ForceCloseReason"))
			{
				ForceCloseReason=token;
			}
			else if (!strcmp(fieldName,"IsAutoSuspend"))
			{
				IsAutoSuspend=token;
			}
			else if (!strcmp(fieldName,"BusinessUnit"))
			{
				BusinessUnit=token;
			}
			else if (!strcmp(fieldName,"UserCustom"))
			{
				UserCustom=token;
			}
			else if (!strcmp(fieldName,"BranchID"))
			{
				BranchID=token;
			}
			else if (!strcmp(fieldName,"RecNum"))
			{
				RecNum=token;
			}
			else if (!strcmp(fieldName,"BusinessType"))
			{
				BusinessType=token;
			}
			else if (!strcmp(fieldName,"TradingDay"))
			{
				TradingDay=token;
			}
			else if (!strcmp(fieldName,"ParticipantID"))
			{
				ParticipantID=token;
			}
			else if (!strcmp(fieldName,"ClientID"))
			{
				ClientID=token;
			}
			else if (!strcmp(fieldName,"SeatID"))
			{
				SeatID=token;
			}
			else if (!strcmp(fieldName,"InsertTime"))
			{
				InsertTime=token;
			}
			else if (!strcmp(fieldName,"OrderLocalID"))
			{
				OrderLocalID=token;
			}
			else if (!strcmp(fieldName,"OrderSource"))
			{
				OrderSource=token;
			}
			else if (!strcmp(fieldName,"OrderStatus"))
			{
				OrderStatus=token;
			}
			else if (!strcmp(fieldName,"CancelTime"))
			{
				CancelTime=token;
			}
			else if (!strcmp(fieldName,"CancelUserID"))
			{
				CancelUserID=token;
			}
			else if (!strcmp(fieldName,"VolumeTraded"))
			{
				VolumeTraded=token;
			}
			else if (!strcmp(fieldName,"VolumeRemain"))
			{
				VolumeRemain=token;
			}
			else if (!strcmp(fieldName,"FrontID"))
			{
				FrontID=token;
			}
			else if (!strcmp(fieldName,"SessionID"))
			{
				SessionID=token;
			}
			else if (!strcmp(fieldName,"FrozenFee"))
			{
				FrozenFee=token;
			}
			else if (!strcmp(fieldName,"FrozenMargin"))
			{
				FrozenMargin=token;
			}
			else if (!strcmp(fieldName,"FrozenPremium"))
			{
				FrozenPremium=token;
			}
			else if (!strcmp(fieldName,"AccountID"))
			{
				AccountID=token;
			}
			else if (!strcmp(fieldName,"OrderUserID"))
			{
				OrderUserID=token;
			}
			else if (!strcmp(fieldName,"TradeType"))
			{
				TradeType=token;
			}
			else if (!strcmp(fieldName,"DealFlag"))
			{
				DealFlag=token;
			}
			else if (!strcmp(fieldName,"TradeCommision"))
			{
				TradeCommision=token;
			}
			else if (!strcmp(fieldName,"TradeAmnt"))
			{
				TradeAmnt=token;
			}
			else if (!strcmp(fieldName,"CancleVolume"))
			{
				CancleVolume=token;
			}
			else if (!strcmp(fieldName,"RequestID"))
			{
				RequestID=token;
			}
			else if (!strcmp(fieldName,"APIID"))
			{
				APIID=token;
			}
			else if (!strcmp(fieldName,"IPAddress"))
			{
				IPAddress=token;
			}
			else if (!strcmp(fieldName,"MacAddress"))
			{
				MacAddress=token;
			}
			else if (!strcmp(fieldName,"FTdRecvDown"))
			{
				FTdRecvDown=token;
			}
			else if (!strcmp(fieldName,"CoreRecvDown"))
			{
				CoreRecvDown=token;
			}
			else if (!strcmp(fieldName,"CoreSendUp"))
			{
				CoreSendUp=token;
			}
			else if (!strcmp(fieldName,"CoreRecvUp"))
			{
				CoreRecvUp=token;
			}
			else if (!strcmp(fieldName,"CoreSendDown"))
			{
				CoreSendDown=token;
			}
			else if (!strcmp(fieldName,"FTdSendDown"))
			{
				FTdSendDown=token;
			}
			else if (!strcmp(fieldName,"MarginCombType"))
			{
				MarginCombType=token;
			}
			else if (!strcmp(fieldName,"InstrumentGroupID"))
			{
				InstrumentGroupID=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteablePreOrder::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteablePreOrder),output)!=sizeof(CWriteablePreOrder))
		return 0;
	else
		return 1;
}

int CWriteablePreOrder::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderSysID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserOrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderPriceType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Direction.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OffsetFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	HedgeFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LimitPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Volume.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TimeCondition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	GTDDate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	VolumeCondition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MinVolume.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	StopPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ForceCloseReason.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IsAutoSuspend.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	BusinessUnit.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserCustom.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	BranchID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	RecNum.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	BusinessType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradingDay.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ParticipantID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ClientID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SeatID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InsertTime.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderSource.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderStatus.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CancelTime.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CancelUserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	VolumeTraded.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	VolumeRemain.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrontID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SessionID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenFee.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenPremium.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	AccountID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderUserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	DealFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeCommision.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeAmnt.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CancleVolume.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	RequestID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	APIID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IPAddress.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MacAddress.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FTdRecvDown.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreRecvDown.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreSendUp.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreRecvUp.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreSendDown.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FTdSendDown.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MarginCombType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentGroupID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteablePreOrder::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCPreOrder%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	OrderSysID.getString(buf);
	fprintf(fp,"\t\tOrderSysID = %s    [系统报单编号]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);	
	UserID.getString(buf);
	fprintf(fp,"\t\tUserID = %s    [用户代码]\n",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	UserOrderLocalID.getString(buf);
	fprintf(fp,"\t\tUserOrderLocalID = %s    [用户本地报单号]\n",buf);	
	OrderPriceType.getString(buf);
	fprintf(fp,"\t\tOrderPriceType = %s    [价格类型]\n",buf);	
	Direction.getString(buf);
	fprintf(fp,"\t\tDirection = %s    [买卖方向]\n",buf);	
	OffsetFlag.getString(buf);
	fprintf(fp,"\t\tOffsetFlag = %s    [开平标志]\n",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);	
	LimitPrice.getString(buf);
	fprintf(fp,"\t\tLimitPrice = %s    [价格]\n",buf);	
	Volume.getString(buf);
	fprintf(fp,"\t\tVolume = %s    [数量]\n",buf);	
	TimeCondition.getString(buf);
	fprintf(fp,"\t\tTimeCondition = %s    [有效期类型]\n",buf);	
	GTDDate.getString(buf);
	fprintf(fp,"\t\tGTDDate = %s    [GTD日期]\n",buf);	
	VolumeCondition.getString(buf);
	fprintf(fp,"\t\tVolumeCondition = %s    [成交量类型]\n",buf);	
	MinVolume.getString(buf);
	fprintf(fp,"\t\tMinVolume = %s    [最小成交量]\n",buf);	
	StopPrice.getString(buf);
	fprintf(fp,"\t\tStopPrice = %s    [止损价]\n",buf);	
	ForceCloseReason.getString(buf);
	fprintf(fp,"\t\tForceCloseReason = %s    [强平原因]\n",buf);	
	IsAutoSuspend.getString(buf);
	fprintf(fp,"\t\tIsAutoSuspend = %s    [自动挂起标志]\n",buf);	
	BusinessUnit.getString(buf);
	fprintf(fp,"\t\tBusinessUnit = %s    [业务单元]\n",buf);	
	UserCustom.getString(buf);
	fprintf(fp,"\t\tUserCustom = %s    [用户自定义域]\n",buf);	
	BranchID.getString(buf);
	fprintf(fp,"\t\tBranchID = %s    [营业部代码]\n",buf);	
	RecNum.getString(buf);
	fprintf(fp,"\t\tRecNum = %s    [记录编号]\n",buf);	
	BusinessType.getString(buf);
	fprintf(fp,"\t\tBusinessType = %s    [业务类别]\n",buf);	
	TradingDay.getString(buf);
	fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,"\t\tParticipantID = %s    [会员编号]\n",buf);	
	ClientID.getString(buf);
	fprintf(fp,"\t\tClientID = %s    [客户号]\n",buf);	
	SeatID.getString(buf);
	fprintf(fp,"\t\tSeatID = %s    [下单席位号]\n",buf);	
	InsertTime.getString(buf);
	fprintf(fp,"\t\tInsertTime = %s    [插入时间]\n",buf);	
	OrderLocalID.getString(buf);
	fprintf(fp,"\t\tOrderLocalID = %s    [本地报单编号]\n",buf);	
	OrderSource.getString(buf);
	fprintf(fp,"\t\tOrderSource = %s    [报单来源]\n",buf);	
	OrderStatus.getString(buf);
	fprintf(fp,"\t\tOrderStatus = %s    [报单状态]\n",buf);	
	CancelTime.getString(buf);
	fprintf(fp,"\t\tCancelTime = %s    [撤销时间]\n",buf);	
	CancelUserID.getString(buf);
	fprintf(fp,"\t\tCancelUserID = %s    [撤单用户编号]\n",buf);	
	VolumeTraded.getString(buf);
	fprintf(fp,"\t\tVolumeTraded = %s    [今成交数量]\n",buf);	
	VolumeRemain.getString(buf);
	fprintf(fp,"\t\tVolumeRemain = %s    [剩余数量]\n",buf);	
	FrontID.getString(buf);
	fprintf(fp,"\t\tFrontID = %s    [前置编号]\n",buf);	
	SessionID.getString(buf);
	fprintf(fp,"\t\tSessionID = %s    [会话编号]\n",buf);	
	FrozenFee.getString(buf);
	fprintf(fp,"\t\tFrozenFee = %s    [冻结手续费]\n",buf);	
	FrozenMargin.getString(buf);
	fprintf(fp,"\t\tFrozenMargin = %s    [冻结的保证金]\n",buf);	
	FrozenPremium.getString(buf);
	fprintf(fp,"\t\tFrozenPremium = %s    [期权权利金收支]\n",buf);	
	AccountID.getString(buf);
	fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);	
	OrderUserID.getString(buf);
	fprintf(fp,"\t\tOrderUserID = %s    [下单用户编号]\n",buf);	
	TradeType.getString(buf);
	fprintf(fp,"\t\tTradeType = %s    [交易类型]\n",buf);	
	DealFlag.getString(buf);
	fprintf(fp,"\t\tDealFlag = %s    [处理标志]\n",buf);	
	TradeCommision.getString(buf);
	fprintf(fp,"\t\tTradeCommision = %s    [已成交佣金]\n",buf);	
	TradeAmnt.getString(buf);
	fprintf(fp,"\t\tTradeAmnt = %s    [成交金额]\n",buf);	
	CancleVolume.getString(buf);
	fprintf(fp,"\t\tCancleVolume = %s    [撤单数量]\n",buf);	
	RequestID.getString(buf);
	fprintf(fp,"\t\tRequestID = %s    [请求编号]\n",buf);	
	APIID.getString(buf);
	fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);	
	IPAddress.getString(buf);
	fprintf(fp,"\t\tIPAddress = %s    [下单IP地址]\n",buf);	
	MacAddress.getString(buf);
	fprintf(fp,"\t\tMacAddress = %s    [下单MAC地址]\n",buf);	
	FTdRecvDown.getString(buf);
	fprintf(fp,"\t\tFTdRecvDown = %s    [Ftdengine接受下层时间戳]\n",buf);	
	CoreRecvDown.getString(buf);
	fprintf(fp,"\t\tCoreRecvDown = %s    [接受下层时间戳]\n",buf);	
	CoreSendUp.getString(buf);
	fprintf(fp,"\t\tCoreSendUp = %s    [发送上层时间戳]\n",buf);	
	CoreRecvUp.getString(buf);
	fprintf(fp,"\t\tCoreRecvUp = %s    [接受上层时间戳]\n",buf);	
	CoreSendDown.getString(buf);
	fprintf(fp,"\t\tCoreSendDown = %s    [发送下层时间戳]\n",buf);	
	FTdSendDown.getString(buf);
	fprintf(fp,"\t\tFTdSendDown = %s    [Ftdengine接受下层时间戳]\n",buf);	
	MarginCombType.getString(buf);
	fprintf(fp,"\t\tMarginCombType = %s    [保证金组合类型]\n",buf);	
	InstrumentGroupID.getString(buf);
	fprintf(fp,"\t\tInstrumentGroupID = %s    [合约组代码]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteablePreOrder::dumpDiff(FILE *fp, const CWriteablePreOrder *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCPreOrder = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	OrderSysID.getString(buf);
	if (compare(OrderSysID.getValue(),pOriginal->OrderSysID.getValue())!=0)
	{
		pOriginal->OrderSysID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderSysID = %s -> %s    [系统报单编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderSysID = %s    [系统报单编号]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);
	}
	UserID.getString(buf);
	if (compare(UserID.getValue(),pOriginal->UserID.getValue())!=0)
	{
		pOriginal->UserID.getString(bufOriginal);
		fprintf(fp,"\t\tUserID = %s -> %s    [用户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserID = %s    [用户代码]\n",buf);
	}
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	UserOrderLocalID.getString(buf);
	if (compare(UserOrderLocalID.getValue(),pOriginal->UserOrderLocalID.getValue())!=0)
	{
		pOriginal->UserOrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tUserOrderLocalID = %s -> %s    [用户本地报单号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserOrderLocalID = %s    [用户本地报单号]\n",buf);
	}
	OrderPriceType.getString(buf);
	if (compare(OrderPriceType.getValue(),pOriginal->OrderPriceType.getValue())!=0)
	{
		pOriginal->OrderPriceType.getString(bufOriginal);
		fprintf(fp,"\t\tOrderPriceType = %s -> %s    [价格类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderPriceType = %s    [价格类型]\n",buf);
	}
	Direction.getString(buf);
	if (compare(Direction.getValue(),pOriginal->Direction.getValue())!=0)
	{
		pOriginal->Direction.getString(bufOriginal);
		fprintf(fp,"\t\tDirection = %s -> %s    [买卖方向]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDirection = %s    [买卖方向]\n",buf);
	}
	OffsetFlag.getString(buf);
	if (compare(OffsetFlag.getValue(),pOriginal->OffsetFlag.getValue())!=0)
	{
		pOriginal->OffsetFlag.getString(bufOriginal);
		fprintf(fp,"\t\tOffsetFlag = %s -> %s    [开平标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOffsetFlag = %s    [开平标志]\n",buf);
	}
	HedgeFlag.getString(buf);
	if (compare(HedgeFlag.getValue(),pOriginal->HedgeFlag.getValue())!=0)
	{
		pOriginal->HedgeFlag.getString(bufOriginal);
		fprintf(fp,"\t\tHedgeFlag = %s -> %s    [投机套保标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);
	}
	LimitPrice.getString(buf);
	if (compare(LimitPrice.getValue(),pOriginal->LimitPrice.getValue())!=0)
	{
		pOriginal->LimitPrice.getString(bufOriginal);
		fprintf(fp,"\t\tLimitPrice = %s -> %s    [价格]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLimitPrice = %s    [价格]\n",buf);
	}
	Volume.getString(buf);
	if (compare(Volume.getValue(),pOriginal->Volume.getValue())!=0)
	{
		pOriginal->Volume.getString(bufOriginal);
		fprintf(fp,"\t\tVolume = %s -> %s    [数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tVolume = %s    [数量]\n",buf);
	}
	TimeCondition.getString(buf);
	if (compare(TimeCondition.getValue(),pOriginal->TimeCondition.getValue())!=0)
	{
		pOriginal->TimeCondition.getString(bufOriginal);
		fprintf(fp,"\t\tTimeCondition = %s -> %s    [有效期类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTimeCondition = %s    [有效期类型]\n",buf);
	}
	GTDDate.getString(buf);
	if (compare(GTDDate.getValue(),pOriginal->GTDDate.getValue())!=0)
	{
		pOriginal->GTDDate.getString(bufOriginal);
		fprintf(fp,"\t\tGTDDate = %s -> %s    [GTD日期]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tGTDDate = %s    [GTD日期]\n",buf);
	}
	VolumeCondition.getString(buf);
	if (compare(VolumeCondition.getValue(),pOriginal->VolumeCondition.getValue())!=0)
	{
		pOriginal->VolumeCondition.getString(bufOriginal);
		fprintf(fp,"\t\tVolumeCondition = %s -> %s    [成交量类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tVolumeCondition = %s    [成交量类型]\n",buf);
	}
	MinVolume.getString(buf);
	if (compare(MinVolume.getValue(),pOriginal->MinVolume.getValue())!=0)
	{
		pOriginal->MinVolume.getString(bufOriginal);
		fprintf(fp,"\t\tMinVolume = %s -> %s    [最小成交量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMinVolume = %s    [最小成交量]\n",buf);
	}
	StopPrice.getString(buf);
	if (compare(StopPrice.getValue(),pOriginal->StopPrice.getValue())!=0)
	{
		pOriginal->StopPrice.getString(bufOriginal);
		fprintf(fp,"\t\tStopPrice = %s -> %s    [止损价]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tStopPrice = %s    [止损价]\n",buf);
	}
	ForceCloseReason.getString(buf);
	if (compare(ForceCloseReason.getValue(),pOriginal->ForceCloseReason.getValue())!=0)
	{
		pOriginal->ForceCloseReason.getString(bufOriginal);
		fprintf(fp,"\t\tForceCloseReason = %s -> %s    [强平原因]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tForceCloseReason = %s    [强平原因]\n",buf);
	}
	IsAutoSuspend.getString(buf);
	if (compare(IsAutoSuspend.getValue(),pOriginal->IsAutoSuspend.getValue())!=0)
	{
		pOriginal->IsAutoSuspend.getString(bufOriginal);
		fprintf(fp,"\t\tIsAutoSuspend = %s -> %s    [自动挂起标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIsAutoSuspend = %s    [自动挂起标志]\n",buf);
	}
	BusinessUnit.getString(buf);
	if (compare(BusinessUnit.getValue(),pOriginal->BusinessUnit.getValue())!=0)
	{
		pOriginal->BusinessUnit.getString(bufOriginal);
		fprintf(fp,"\t\tBusinessUnit = %s -> %s    [业务单元]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBusinessUnit = %s    [业务单元]\n",buf);
	}
	UserCustom.getString(buf);
	if (compare(UserCustom.getValue(),pOriginal->UserCustom.getValue())!=0)
	{
		pOriginal->UserCustom.getString(bufOriginal);
		fprintf(fp,"\t\tUserCustom = %s -> %s    [用户自定义域]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserCustom = %s    [用户自定义域]\n",buf);
	}
	BranchID.getString(buf);
	if (compare(BranchID.getValue(),pOriginal->BranchID.getValue())!=0)
	{
		pOriginal->BranchID.getString(bufOriginal);
		fprintf(fp,"\t\tBranchID = %s -> %s    [营业部代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBranchID = %s    [营业部代码]\n",buf);
	}
	RecNum.getString(buf);
	if (compare(RecNum.getValue(),pOriginal->RecNum.getValue())!=0)
	{
		pOriginal->RecNum.getString(bufOriginal);
		fprintf(fp,"\t\tRecNum = %s -> %s    [记录编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tRecNum = %s    [记录编号]\n",buf);
	}
	BusinessType.getString(buf);
	if (compare(BusinessType.getValue(),pOriginal->BusinessType.getValue())!=0)
	{
		pOriginal->BusinessType.getString(bufOriginal);
		fprintf(fp,"\t\tBusinessType = %s -> %s    [业务类别]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBusinessType = %s    [业务类别]\n",buf);
	}
	TradingDay.getString(buf);
	if (compare(TradingDay.getValue(),pOriginal->TradingDay.getValue())!=0)
	{
		pOriginal->TradingDay.getString(bufOriginal);
		fprintf(fp,"\t\tTradingDay = %s -> %s    [交易日]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);
	}
	ParticipantID.getString(buf);
	if (compare(ParticipantID.getValue(),pOriginal->ParticipantID.getValue())!=0)
	{
		pOriginal->ParticipantID.getString(bufOriginal);
		fprintf(fp,"\t\tParticipantID = %s -> %s    [会员编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tParticipantID = %s    [会员编号]\n",buf);
	}
	ClientID.getString(buf);
	if (compare(ClientID.getValue(),pOriginal->ClientID.getValue())!=0)
	{
		pOriginal->ClientID.getString(bufOriginal);
		fprintf(fp,"\t\tClientID = %s -> %s    [客户号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tClientID = %s    [客户号]\n",buf);
	}
	SeatID.getString(buf);
	if (compare(SeatID.getValue(),pOriginal->SeatID.getValue())!=0)
	{
		pOriginal->SeatID.getString(bufOriginal);
		fprintf(fp,"\t\tSeatID = %s -> %s    [下单席位号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSeatID = %s    [下单席位号]\n",buf);
	}
	InsertTime.getString(buf);
	if (compare(InsertTime.getValue(),pOriginal->InsertTime.getValue())!=0)
	{
		pOriginal->InsertTime.getString(bufOriginal);
		fprintf(fp,"\t\tInsertTime = %s -> %s    [插入时间]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInsertTime = %s    [插入时间]\n",buf);
	}
	OrderLocalID.getString(buf);
	if (compare(OrderLocalID.getValue(),pOriginal->OrderLocalID.getValue())!=0)
	{
		pOriginal->OrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderLocalID = %s -> %s    [本地报单编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderLocalID = %s    [本地报单编号]\n",buf);
	}
	OrderSource.getString(buf);
	if (compare(OrderSource.getValue(),pOriginal->OrderSource.getValue())!=0)
	{
		pOriginal->OrderSource.getString(bufOriginal);
		fprintf(fp,"\t\tOrderSource = %s -> %s    [报单来源]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderSource = %s    [报单来源]\n",buf);
	}
	OrderStatus.getString(buf);
	if (compare(OrderStatus.getValue(),pOriginal->OrderStatus.getValue())!=0)
	{
		pOriginal->OrderStatus.getString(bufOriginal);
		fprintf(fp,"\t\tOrderStatus = %s -> %s    [报单状态]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderStatus = %s    [报单状态]\n",buf);
	}
	CancelTime.getString(buf);
	if (compare(CancelTime.getValue(),pOriginal->CancelTime.getValue())!=0)
	{
		pOriginal->CancelTime.getString(bufOriginal);
		fprintf(fp,"\t\tCancelTime = %s -> %s    [撤销时间]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCancelTime = %s    [撤销时间]\n",buf);
	}
	CancelUserID.getString(buf);
	if (compare(CancelUserID.getValue(),pOriginal->CancelUserID.getValue())!=0)
	{
		pOriginal->CancelUserID.getString(bufOriginal);
		fprintf(fp,"\t\tCancelUserID = %s -> %s    [撤单用户编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCancelUserID = %s    [撤单用户编号]\n",buf);
	}
	VolumeTraded.getString(buf);
	if (compare(VolumeTraded.getValue(),pOriginal->VolumeTraded.getValue())!=0)
	{
		pOriginal->VolumeTraded.getString(bufOriginal);
		fprintf(fp,"\t\tVolumeTraded = %s -> %s    [今成交数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tVolumeTraded = %s    [今成交数量]\n",buf);
	}
	VolumeRemain.getString(buf);
	if (compare(VolumeRemain.getValue(),pOriginal->VolumeRemain.getValue())!=0)
	{
		pOriginal->VolumeRemain.getString(bufOriginal);
		fprintf(fp,"\t\tVolumeRemain = %s -> %s    [剩余数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tVolumeRemain = %s    [剩余数量]\n",buf);
	}
	FrontID.getString(buf);
	if (compare(FrontID.getValue(),pOriginal->FrontID.getValue())!=0)
	{
		pOriginal->FrontID.getString(bufOriginal);
		fprintf(fp,"\t\tFrontID = %s -> %s    [前置编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrontID = %s    [前置编号]\n",buf);
	}
	SessionID.getString(buf);
	if (compare(SessionID.getValue(),pOriginal->SessionID.getValue())!=0)
	{
		pOriginal->SessionID.getString(bufOriginal);
		fprintf(fp,"\t\tSessionID = %s -> %s    [会话编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSessionID = %s    [会话编号]\n",buf);
	}
	FrozenFee.getString(buf);
	if (compare(FrozenFee.getValue(),pOriginal->FrozenFee.getValue())!=0)
	{
		pOriginal->FrozenFee.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenFee = %s -> %s    [冻结手续费]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenFee = %s    [冻结手续费]\n",buf);
	}
	FrozenMargin.getString(buf);
	if (compare(FrozenMargin.getValue(),pOriginal->FrozenMargin.getValue())!=0)
	{
		pOriginal->FrozenMargin.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenMargin = %s -> %s    [冻结的保证金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenMargin = %s    [冻结的保证金]\n",buf);
	}
	FrozenPremium.getString(buf);
	if (compare(FrozenPremium.getValue(),pOriginal->FrozenPremium.getValue())!=0)
	{
		pOriginal->FrozenPremium.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenPremium = %s -> %s    [期权权利金收支]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenPremium = %s    [期权权利金收支]\n",buf);
	}
	AccountID.getString(buf);
	if (compare(AccountID.getValue(),pOriginal->AccountID.getValue())!=0)
	{
		pOriginal->AccountID.getString(bufOriginal);
		fprintf(fp,"\t\tAccountID = %s -> %s    [资金帐号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);
	}
	OrderUserID.getString(buf);
	if (compare(OrderUserID.getValue(),pOriginal->OrderUserID.getValue())!=0)
	{
		pOriginal->OrderUserID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderUserID = %s -> %s    [下单用户编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderUserID = %s    [下单用户编号]\n",buf);
	}
	TradeType.getString(buf);
	if (compare(TradeType.getValue(),pOriginal->TradeType.getValue())!=0)
	{
		pOriginal->TradeType.getString(bufOriginal);
		fprintf(fp,"\t\tTradeType = %s -> %s    [交易类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeType = %s    [交易类型]\n",buf);
	}
	DealFlag.getString(buf);
	if (compare(DealFlag.getValue(),pOriginal->DealFlag.getValue())!=0)
	{
		pOriginal->DealFlag.getString(bufOriginal);
		fprintf(fp,"\t\tDealFlag = %s -> %s    [处理标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDealFlag = %s    [处理标志]\n",buf);
	}
	TradeCommision.getString(buf);
	if (compare(TradeCommision.getValue(),pOriginal->TradeCommision.getValue())!=0)
	{
		pOriginal->TradeCommision.getString(bufOriginal);
		fprintf(fp,"\t\tTradeCommision = %s -> %s    [已成交佣金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeCommision = %s    [已成交佣金]\n",buf);
	}
	TradeAmnt.getString(buf);
	if (compare(TradeAmnt.getValue(),pOriginal->TradeAmnt.getValue())!=0)
	{
		pOriginal->TradeAmnt.getString(bufOriginal);
		fprintf(fp,"\t\tTradeAmnt = %s -> %s    [成交金额]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeAmnt = %s    [成交金额]\n",buf);
	}
	CancleVolume.getString(buf);
	if (compare(CancleVolume.getValue(),pOriginal->CancleVolume.getValue())!=0)
	{
		pOriginal->CancleVolume.getString(bufOriginal);
		fprintf(fp,"\t\tCancleVolume = %s -> %s    [撤单数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCancleVolume = %s    [撤单数量]\n",buf);
	}
	RequestID.getString(buf);
	if (compare(RequestID.getValue(),pOriginal->RequestID.getValue())!=0)
	{
		pOriginal->RequestID.getString(bufOriginal);
		fprintf(fp,"\t\tRequestID = %s -> %s    [请求编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tRequestID = %s    [请求编号]\n",buf);
	}
	APIID.getString(buf);
	if (compare(APIID.getValue(),pOriginal->APIID.getValue())!=0)
	{
		pOriginal->APIID.getString(bufOriginal);
		fprintf(fp,"\t\tAPIID = %s -> %s    [通道对应的APIID]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);
	}
	IPAddress.getString(buf);
	if (compare(IPAddress.getValue(),pOriginal->IPAddress.getValue())!=0)
	{
		pOriginal->IPAddress.getString(bufOriginal);
		fprintf(fp,"\t\tIPAddress = %s -> %s    [下单IP地址]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIPAddress = %s    [下单IP地址]\n",buf);
	}
	MacAddress.getString(buf);
	if (compare(MacAddress.getValue(),pOriginal->MacAddress.getValue())!=0)
	{
		pOriginal->MacAddress.getString(bufOriginal);
		fprintf(fp,"\t\tMacAddress = %s -> %s    [下单MAC地址]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMacAddress = %s    [下单MAC地址]\n",buf);
	}
	FTdRecvDown.getString(buf);
	if (compare(FTdRecvDown.getValue(),pOriginal->FTdRecvDown.getValue())!=0)
	{
		pOriginal->FTdRecvDown.getString(bufOriginal);
		fprintf(fp,"\t\tFTdRecvDown = %s -> %s    [Ftdengine接受下层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFTdRecvDown = %s    [Ftdengine接受下层时间戳]\n",buf);
	}
	CoreRecvDown.getString(buf);
	if (compare(CoreRecvDown.getValue(),pOriginal->CoreRecvDown.getValue())!=0)
	{
		pOriginal->CoreRecvDown.getString(bufOriginal);
		fprintf(fp,"\t\tCoreRecvDown = %s -> %s    [接受下层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreRecvDown = %s    [接受下层时间戳]\n",buf);
	}
	CoreSendUp.getString(buf);
	if (compare(CoreSendUp.getValue(),pOriginal->CoreSendUp.getValue())!=0)
	{
		pOriginal->CoreSendUp.getString(bufOriginal);
		fprintf(fp,"\t\tCoreSendUp = %s -> %s    [发送上层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreSendUp = %s    [发送上层时间戳]\n",buf);
	}
	CoreRecvUp.getString(buf);
	if (compare(CoreRecvUp.getValue(),pOriginal->CoreRecvUp.getValue())!=0)
	{
		pOriginal->CoreRecvUp.getString(bufOriginal);
		fprintf(fp,"\t\tCoreRecvUp = %s -> %s    [接受上层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreRecvUp = %s    [接受上层时间戳]\n",buf);
	}
	CoreSendDown.getString(buf);
	if (compare(CoreSendDown.getValue(),pOriginal->CoreSendDown.getValue())!=0)
	{
		pOriginal->CoreSendDown.getString(bufOriginal);
		fprintf(fp,"\t\tCoreSendDown = %s -> %s    [发送下层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreSendDown = %s    [发送下层时间戳]\n",buf);
	}
	FTdSendDown.getString(buf);
	if (compare(FTdSendDown.getValue(),pOriginal->FTdSendDown.getValue())!=0)
	{
		pOriginal->FTdSendDown.getString(bufOriginal);
		fprintf(fp,"\t\tFTdSendDown = %s -> %s    [Ftdengine接受下层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFTdSendDown = %s    [Ftdengine接受下层时间戳]\n",buf);
	}
	MarginCombType.getString(buf);
	if (compare(MarginCombType.getValue(),pOriginal->MarginCombType.getValue())!=0)
	{
		pOriginal->MarginCombType.getString(bufOriginal);
		fprintf(fp,"\t\tMarginCombType = %s -> %s    [保证金组合类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMarginCombType = %s    [保证金组合类型]\n",buf);
	}
	InstrumentGroupID.getString(buf);
	if (compare(InstrumentGroupID.getValue(),pOriginal->InstrumentGroupID.getValue())!=0)
	{
		pOriginal->InstrumentGroupID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentGroupID = %s -> %s    [合约组代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentGroupID = %s    [合约组代码]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteablePreOrder::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	OrderSysID.getString(buf);
	fprintf(fp,",OrderSysID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	UserID.getString(buf);
	fprintf(fp,",UserID,%s",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	UserOrderLocalID.getString(buf);
	fprintf(fp,",UserOrderLocalID,%s",buf);	
	OrderPriceType.getString(buf);
	fprintf(fp,",OrderPriceType,%s",buf);	
	Direction.getString(buf);
	fprintf(fp,",Direction,%s",buf);	
	OffsetFlag.getString(buf);
	fprintf(fp,",OffsetFlag,%s",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,",HedgeFlag,%s",buf);	
	LimitPrice.getString(buf);
	fprintf(fp,",LimitPrice,%s",buf);	
	Volume.getString(buf);
	fprintf(fp,",Volume,%s",buf);	
	TimeCondition.getString(buf);
	fprintf(fp,",TimeCondition,%s",buf);	
	GTDDate.getString(buf);
	fprintf(fp,",GTDDate,%s",buf);	
	VolumeCondition.getString(buf);
	fprintf(fp,",VolumeCondition,%s",buf);	
	MinVolume.getString(buf);
	fprintf(fp,",MinVolume,%s",buf);	
	StopPrice.getString(buf);
	fprintf(fp,",StopPrice,%s",buf);	
	ForceCloseReason.getString(buf);
	fprintf(fp,",ForceCloseReason,%s",buf);	
	IsAutoSuspend.getString(buf);
	fprintf(fp,",IsAutoSuspend,%s",buf);	
	BusinessUnit.getString(buf);
	fprintf(fp,",BusinessUnit,%s",buf);	
	UserCustom.getString(buf);
	fprintf(fp,",UserCustom,%s",buf);	
	BranchID.getString(buf);
	fprintf(fp,",BranchID,%s",buf);	
	RecNum.getString(buf);
	fprintf(fp,",RecNum,%s",buf);	
	BusinessType.getString(buf);
	fprintf(fp,",BusinessType,%s",buf);	
	TradingDay.getString(buf);
	fprintf(fp,",TradingDay,%s",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,",ParticipantID,%s",buf);	
	ClientID.getString(buf);
	fprintf(fp,",ClientID,%s",buf);	
	SeatID.getString(buf);
	fprintf(fp,",SeatID,%s",buf);	
	InsertTime.getString(buf);
	fprintf(fp,",InsertTime,%s",buf);	
	OrderLocalID.getString(buf);
	fprintf(fp,",OrderLocalID,%s",buf);	
	OrderSource.getString(buf);
	fprintf(fp,",OrderSource,%s",buf);	
	OrderStatus.getString(buf);
	fprintf(fp,",OrderStatus,%s",buf);	
	CancelTime.getString(buf);
	fprintf(fp,",CancelTime,%s",buf);	
	CancelUserID.getString(buf);
	fprintf(fp,",CancelUserID,%s",buf);	
	VolumeTraded.getString(buf);
	fprintf(fp,",VolumeTraded,%s",buf);	
	VolumeRemain.getString(buf);
	fprintf(fp,",VolumeRemain,%s",buf);	
	FrontID.getString(buf);
	fprintf(fp,",FrontID,%s",buf);	
	SessionID.getString(buf);
	fprintf(fp,",SessionID,%s",buf);	
	FrozenFee.getString(buf);
	fprintf(fp,",FrozenFee,%s",buf);	
	FrozenMargin.getString(buf);
	fprintf(fp,",FrozenMargin,%s",buf);	
	FrozenPremium.getString(buf);
	fprintf(fp,",FrozenPremium,%s",buf);	
	AccountID.getString(buf);
	fprintf(fp,",AccountID,%s",buf);	
	OrderUserID.getString(buf);
	fprintf(fp,",OrderUserID,%s",buf);	
	TradeType.getString(buf);
	fprintf(fp,",TradeType,%s",buf);	
	DealFlag.getString(buf);
	fprintf(fp,",DealFlag,%s",buf);	
	TradeCommision.getString(buf);
	fprintf(fp,",TradeCommision,%s",buf);	
	TradeAmnt.getString(buf);
	fprintf(fp,",TradeAmnt,%s",buf);	
	CancleVolume.getString(buf);
	fprintf(fp,",CancleVolume,%s",buf);	
	RequestID.getString(buf);
	fprintf(fp,",RequestID,%s",buf);	
	APIID.getString(buf);
	fprintf(fp,",APIID,%s",buf);	
	IPAddress.getString(buf);
	fprintf(fp,",IPAddress,%s",buf);	
	MacAddress.getString(buf);
	fprintf(fp,",MacAddress,%s",buf);	
	FTdRecvDown.getString(buf);
	fprintf(fp,",FTdRecvDown,%s",buf);	
	CoreRecvDown.getString(buf);
	fprintf(fp,",CoreRecvDown,%s",buf);	
	CoreSendUp.getString(buf);
	fprintf(fp,",CoreSendUp,%s",buf);	
	CoreRecvUp.getString(buf);
	fprintf(fp,",CoreRecvUp,%s",buf);	
	CoreSendDown.getString(buf);
	fprintf(fp,",CoreSendDown,%s",buf);	
	FTdSendDown.getString(buf);
	fprintf(fp,",FTdSendDown,%s",buf);	
	MarginCombType.getString(buf);
	fprintf(fp,",MarginCombType,%s",buf);	
	InstrumentGroupID.getString(buf);
	fprintf(fp,",InstrumentGroupID,%s",buf);	
}

void CWriteablePreOrder::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	OrderSysID.getString(buf);
	sprintf(p,"OrderSysID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	UserID.getString(buf);
	sprintf(p,"UserID=%s,",buf);
	p+=strlen(p);
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	UserOrderLocalID.getString(buf);
	sprintf(p,"UserOrderLocalID=%s,",buf);
	p+=strlen(p);
	OrderPriceType.getString(buf);
	sprintf(p,"OrderPriceType=%s,",buf);
	p+=strlen(p);
	Direction.getString(buf);
	sprintf(p,"Direction=%s,",buf);
	p+=strlen(p);
	OffsetFlag.getString(buf);
	sprintf(p,"OffsetFlag=%s,",buf);
	p+=strlen(p);
	HedgeFlag.getString(buf);
	sprintf(p,"HedgeFlag=%s,",buf);
	p+=strlen(p);
	LimitPrice.getString(buf);
	sprintf(p,"LimitPrice=%s,",buf);
	p+=strlen(p);
	Volume.getString(buf);
	sprintf(p,"Volume=%s,",buf);
	p+=strlen(p);
	TimeCondition.getString(buf);
	sprintf(p,"TimeCondition=%s,",buf);
	p+=strlen(p);
	GTDDate.getString(buf);
	sprintf(p,"GTDDate=%s,",buf);
	p+=strlen(p);
	VolumeCondition.getString(buf);
	sprintf(p,"VolumeCondition=%s,",buf);
	p+=strlen(p);
	MinVolume.getString(buf);
	sprintf(p,"MinVolume=%s,",buf);
	p+=strlen(p);
	StopPrice.getString(buf);
	sprintf(p,"StopPrice=%s,",buf);
	p+=strlen(p);
	ForceCloseReason.getString(buf);
	sprintf(p,"ForceCloseReason=%s,",buf);
	p+=strlen(p);
	IsAutoSuspend.getString(buf);
	sprintf(p,"IsAutoSuspend=%s,",buf);
	p+=strlen(p);
	BusinessUnit.getString(buf);
	sprintf(p,"BusinessUnit=%s,",buf);
	p+=strlen(p);
	UserCustom.getString(buf);
	sprintf(p,"UserCustom=%s,",buf);
	p+=strlen(p);
	BranchID.getString(buf);
	sprintf(p,"BranchID=%s,",buf);
	p+=strlen(p);
	RecNum.getString(buf);
	sprintf(p,"RecNum=%s,",buf);
	p+=strlen(p);
	BusinessType.getString(buf);
	sprintf(p,"BusinessType=%s,",buf);
	p+=strlen(p);
	TradingDay.getString(buf);
	sprintf(p,"TradingDay=%s,",buf);
	p+=strlen(p);
	ParticipantID.getString(buf);
	sprintf(p,"ParticipantID=%s,",buf);
	p+=strlen(p);
	ClientID.getString(buf);
	sprintf(p,"ClientID=%s,",buf);
	p+=strlen(p);
	SeatID.getString(buf);
	sprintf(p,"SeatID=%s,",buf);
	p+=strlen(p);
	InsertTime.getString(buf);
	sprintf(p,"InsertTime=%s,",buf);
	p+=strlen(p);
	OrderLocalID.getString(buf);
	sprintf(p,"OrderLocalID=%s,",buf);
	p+=strlen(p);
	OrderSource.getString(buf);
	sprintf(p,"OrderSource=%s,",buf);
	p+=strlen(p);
	OrderStatus.getString(buf);
	sprintf(p,"OrderStatus=%s,",buf);
	p+=strlen(p);
	CancelTime.getString(buf);
	sprintf(p,"CancelTime=%s,",buf);
	p+=strlen(p);
	CancelUserID.getString(buf);
	sprintf(p,"CancelUserID=%s,",buf);
	p+=strlen(p);
	VolumeTraded.getString(buf);
	sprintf(p,"VolumeTraded=%s,",buf);
	p+=strlen(p);
	VolumeRemain.getString(buf);
	sprintf(p,"VolumeRemain=%s,",buf);
	p+=strlen(p);
	FrontID.getString(buf);
	sprintf(p,"FrontID=%s,",buf);
	p+=strlen(p);
	SessionID.getString(buf);
	sprintf(p,"SessionID=%s,",buf);
	p+=strlen(p);
	FrozenFee.getString(buf);
	sprintf(p,"FrozenFee=%s,",buf);
	p+=strlen(p);
	FrozenMargin.getString(buf);
	sprintf(p,"FrozenMargin=%s,",buf);
	p+=strlen(p);
	FrozenPremium.getString(buf);
	sprintf(p,"FrozenPremium=%s,",buf);
	p+=strlen(p);
	AccountID.getString(buf);
	sprintf(p,"AccountID=%s,",buf);
	p+=strlen(p);
	OrderUserID.getString(buf);
	sprintf(p,"OrderUserID=%s,",buf);
	p+=strlen(p);
	TradeType.getString(buf);
	sprintf(p,"TradeType=%s,",buf);
	p+=strlen(p);
	DealFlag.getString(buf);
	sprintf(p,"DealFlag=%s,",buf);
	p+=strlen(p);
	TradeCommision.getString(buf);
	sprintf(p,"TradeCommision=%s,",buf);
	p+=strlen(p);
	TradeAmnt.getString(buf);
	sprintf(p,"TradeAmnt=%s,",buf);
	p+=strlen(p);
	CancleVolume.getString(buf);
	sprintf(p,"CancleVolume=%s,",buf);
	p+=strlen(p);
	RequestID.getString(buf);
	sprintf(p,"RequestID=%s,",buf);
	p+=strlen(p);
	APIID.getString(buf);
	sprintf(p,"APIID=%s,",buf);
	p+=strlen(p);
	IPAddress.getString(buf);
	sprintf(p,"IPAddress=%s,",buf);
	p+=strlen(p);
	MacAddress.getString(buf);
	sprintf(p,"MacAddress=%s,",buf);
	p+=strlen(p);
	FTdRecvDown.getString(buf);
	sprintf(p,"FTdRecvDown=%s,",buf);
	p+=strlen(p);
	CoreRecvDown.getString(buf);
	sprintf(p,"CoreRecvDown=%s,",buf);
	p+=strlen(p);
	CoreSendUp.getString(buf);
	sprintf(p,"CoreSendUp=%s,",buf);
	p+=strlen(p);
	CoreRecvUp.getString(buf);
	sprintf(p,"CoreRecvUp=%s,",buf);
	p+=strlen(p);
	CoreSendDown.getString(buf);
	sprintf(p,"CoreSendDown=%s,",buf);
	p+=strlen(p);
	FTdSendDown.getString(buf);
	sprintf(p,"FTdSendDown=%s,",buf);
	p+=strlen(p);
	MarginCombType.getString(buf);
	sprintf(p,"MarginCombType=%s,",buf);
	p+=strlen(p);
	InstrumentGroupID.getString(buf);
	sprintf(p,"InstrumentGroupID=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteablePreOrder::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CPreOrder");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	OrderSysID.getString(buf);
	pLogger->output(indent+1,0,"OrderSysID=%s 系统报单编号",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编号",buf);
	UserID.getString(buf);
	pLogger->output(indent+1,0,"UserID=%s 用户代码",buf);
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	UserOrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"UserOrderLocalID=%s 用户本地报单号",buf);
	OrderPriceType.getString(buf);
	pLogger->output(indent+1,0,"OrderPriceType=%s 价格类型",buf);
	Direction.getString(buf);
	pLogger->output(indent+1,0,"Direction=%s 买卖方向",buf);
	OffsetFlag.getString(buf);
	pLogger->output(indent+1,0,"OffsetFlag=%s 开平标志",buf);
	HedgeFlag.getString(buf);
	pLogger->output(indent+1,0,"HedgeFlag=%s 投机套保标志",buf);
	LimitPrice.getString(buf);
	pLogger->output(indent+1,0,"LimitPrice=%s 价格",buf);
	Volume.getString(buf);
	pLogger->output(indent+1,0,"Volume=%s 数量",buf);
	TimeCondition.getString(buf);
	pLogger->output(indent+1,0,"TimeCondition=%s 有效期类型",buf);
	GTDDate.getString(buf);
	pLogger->output(indent+1,0,"GTDDate=%s GTD日期",buf);
	VolumeCondition.getString(buf);
	pLogger->output(indent+1,0,"VolumeCondition=%s 成交量类型",buf);
	MinVolume.getString(buf);
	pLogger->output(indent+1,0,"MinVolume=%s 最小成交量",buf);
	StopPrice.getString(buf);
	pLogger->output(indent+1,0,"StopPrice=%s 止损价",buf);
	ForceCloseReason.getString(buf);
	pLogger->output(indent+1,0,"ForceCloseReason=%s 强平原因",buf);
	IsAutoSuspend.getString(buf);
	pLogger->output(indent+1,0,"IsAutoSuspend=%s 自动挂起标志",buf);
	BusinessUnit.getString(buf);
	pLogger->output(indent+1,0,"BusinessUnit=%s 业务单元",buf);
	UserCustom.getString(buf);
	pLogger->output(indent+1,0,"UserCustom=%s 用户自定义域",buf);
	BranchID.getString(buf);
	pLogger->output(indent+1,0,"BranchID=%s 营业部代码",buf);
	RecNum.getString(buf);
	pLogger->output(indent+1,0,"RecNum=%s 记录编号",buf);
	BusinessType.getString(buf);
	pLogger->output(indent+1,0,"BusinessType=%s 业务类别",buf);
	TradingDay.getString(buf);
	pLogger->output(indent+1,0,"TradingDay=%s 交易日",buf);
	ParticipantID.getString(buf);
	pLogger->output(indent+1,0,"ParticipantID=%s 会员编号",buf);
	ClientID.getString(buf);
	pLogger->output(indent+1,0,"ClientID=%s 客户号",buf);
	SeatID.getString(buf);
	pLogger->output(indent+1,0,"SeatID=%s 下单席位号",buf);
	InsertTime.getString(buf);
	pLogger->output(indent+1,0,"InsertTime=%s 插入时间",buf);
	OrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"OrderLocalID=%s 本地报单编号",buf);
	OrderSource.getString(buf);
	pLogger->output(indent+1,0,"OrderSource=%s 报单来源",buf);
	OrderStatus.getString(buf);
	pLogger->output(indent+1,0,"OrderStatus=%s 报单状态",buf);
	CancelTime.getString(buf);
	pLogger->output(indent+1,0,"CancelTime=%s 撤销时间",buf);
	CancelUserID.getString(buf);
	pLogger->output(indent+1,0,"CancelUserID=%s 撤单用户编号",buf);
	VolumeTraded.getString(buf);
	pLogger->output(indent+1,0,"VolumeTraded=%s 今成交数量",buf);
	VolumeRemain.getString(buf);
	pLogger->output(indent+1,0,"VolumeRemain=%s 剩余数量",buf);
	FrontID.getString(buf);
	pLogger->output(indent+1,0,"FrontID=%s 前置编号",buf);
	SessionID.getString(buf);
	pLogger->output(indent+1,0,"SessionID=%s 会话编号",buf);
	FrozenFee.getString(buf);
	pLogger->output(indent+1,0,"FrozenFee=%s 冻结手续费",buf);
	FrozenMargin.getString(buf);
	pLogger->output(indent+1,0,"FrozenMargin=%s 冻结的保证金",buf);
	FrozenPremium.getString(buf);
	pLogger->output(indent+1,0,"FrozenPremium=%s 期权权利金收支",buf);
	AccountID.getString(buf);
	pLogger->output(indent+1,0,"AccountID=%s 资金帐号",buf);
	OrderUserID.getString(buf);
	pLogger->output(indent+1,0,"OrderUserID=%s 下单用户编号",buf);
	TradeType.getString(buf);
	pLogger->output(indent+1,0,"TradeType=%s 交易类型",buf);
	DealFlag.getString(buf);
	pLogger->output(indent+1,0,"DealFlag=%s 处理标志",buf);
	TradeCommision.getString(buf);
	pLogger->output(indent+1,0,"TradeCommision=%s 已成交佣金",buf);
	TradeAmnt.getString(buf);
	pLogger->output(indent+1,0,"TradeAmnt=%s 成交金额",buf);
	CancleVolume.getString(buf);
	pLogger->output(indent+1,0,"CancleVolume=%s 撤单数量",buf);
	RequestID.getString(buf);
	pLogger->output(indent+1,0,"RequestID=%s 请求编号",buf);
	APIID.getString(buf);
	pLogger->output(indent+1,0,"APIID=%s 通道对应的APIID",buf);
	IPAddress.getString(buf);
	pLogger->output(indent+1,0,"IPAddress=%s 下单IP地址",buf);
	MacAddress.getString(buf);
	pLogger->output(indent+1,0,"MacAddress=%s 下单MAC地址",buf);
	FTdRecvDown.getString(buf);
	pLogger->output(indent+1,0,"FTdRecvDown=%s Ftdengine接受下层时间戳",buf);
	CoreRecvDown.getString(buf);
	pLogger->output(indent+1,0,"CoreRecvDown=%s 接受下层时间戳",buf);
	CoreSendUp.getString(buf);
	pLogger->output(indent+1,0,"CoreSendUp=%s 发送上层时间戳",buf);
	CoreRecvUp.getString(buf);
	pLogger->output(indent+1,0,"CoreRecvUp=%s 接受上层时间戳",buf);
	CoreSendDown.getString(buf);
	pLogger->output(indent+1,0,"CoreSendDown=%s 发送下层时间戳",buf);
	FTdSendDown.getString(buf);
	pLogger->output(indent+1,0,"FTdSendDown=%s Ftdengine接受下层时间戳",buf);
	MarginCombType.getString(buf);
	pLogger->output(indent+1,0,"MarginCombType=%s 保证金组合类型",buf);
	InstrumentGroupID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentGroupID=%s 合约组代码",buf);
	pLogger->output(indent,0,"}");
}

CPreOrderIterator::~CPreOrderIterator(void)
{
}


void CPreOrderIterator::dump(FILE *output)
{
	CPreOrder *pPreOrder;
	
	while ((pPreOrder=next())!=NULL)
	{
		pPreOrder->dump(output);
	}
}



void CWriteableIndexPreOrder::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,ExchangeID,InvestorID,InstrumentID,HedgeFlag,Direction,APIID,ClientID,MarginCombType,InstrumentGroupID\n");
}
	
void CWriteableIndexPreOrder::init(void)
{
	BrokerID.clear();
	ExchangeID.clear();
	InvestorID.clear();
	InstrumentID.clear();
	HedgeFlag.clear();
	Direction.clear();
	APIID.clear();
	ClientID.clear();
	MarginCombType.clear();
	InstrumentGroupID.clear();
	pInvestor=NULL;
	pClientTradingID=NULL;
	pInvestorAccount=NULL;
	pInstrument=NULL;
	pInvestorMargin=NULL;
	pInvestorFee=NULL;
	pClientGroupPosition=NULL;
}

int CWriteableIndexPreOrder::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableIndexPreOrder),input)!=sizeof(CWriteableIndexPreOrder))
		return 0;
	else
		return 1;
}
	
int CWriteableIndexPreOrder::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			HedgeFlag=token;
		}
		else
		{
			HedgeFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Direction=token;
		}
		else
		{
			Direction="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			APIID=token;
		}
		else
		{
			APIID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ClientID=token;
		}
		else
		{
			ClientID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MarginCombType=token;
		}
		else
		{
			MarginCombType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentGroupID=token;
		}
		else
		{
			InstrumentGroupID="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"HedgeFlag"))
			{
				HedgeFlag=token;
			}
			else if (!strcmp(fieldName,"Direction"))
			{
				Direction=token;
			}
			else if (!strcmp(fieldName,"APIID"))
			{
				APIID=token;
			}
			else if (!strcmp(fieldName,"ClientID"))
			{
				ClientID=token;
			}
			else if (!strcmp(fieldName,"MarginCombType"))
			{
				MarginCombType=token;
			}
			else if (!strcmp(fieldName,"InstrumentGroupID"))
			{
				InstrumentGroupID=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableIndexPreOrder::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableIndexPreOrder),output)!=sizeof(CWriteableIndexPreOrder))
		return 0;
	else
		return 1;
}

int CWriteableIndexPreOrder::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	HedgeFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Direction.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	APIID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ClientID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MarginCombType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentGroupID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableIndexPreOrder::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCIndexPreOrder%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);	
	Direction.getString(buf);
	fprintf(fp,"\t\tDirection = %s    [买卖方向]\n",buf);	
	APIID.getString(buf);
	fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);	
	ClientID.getString(buf);
	fprintf(fp,"\t\tClientID = %s    [交易编码]\n",buf);	
	MarginCombType.getString(buf);
	fprintf(fp,"\t\tMarginCombType = %s    [保证金组合类型]\n",buf);	
	InstrumentGroupID.getString(buf);
	fprintf(fp,"\t\tInstrumentGroupID = %s    [合约组代码]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableIndexPreOrder::dumpDiff(FILE *fp, const CWriteableIndexPreOrder *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCIndexPreOrder = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);
	}
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	HedgeFlag.getString(buf);
	if (compare(HedgeFlag.getValue(),pOriginal->HedgeFlag.getValue())!=0)
	{
		pOriginal->HedgeFlag.getString(bufOriginal);
		fprintf(fp,"\t\tHedgeFlag = %s -> %s    [投机套保标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);
	}
	Direction.getString(buf);
	if (compare(Direction.getValue(),pOriginal->Direction.getValue())!=0)
	{
		pOriginal->Direction.getString(bufOriginal);
		fprintf(fp,"\t\tDirection = %s -> %s    [买卖方向]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDirection = %s    [买卖方向]\n",buf);
	}
	APIID.getString(buf);
	if (compare(APIID.getValue(),pOriginal->APIID.getValue())!=0)
	{
		pOriginal->APIID.getString(bufOriginal);
		fprintf(fp,"\t\tAPIID = %s -> %s    [通道对应的APIID]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);
	}
	ClientID.getString(buf);
	if (compare(ClientID.getValue(),pOriginal->ClientID.getValue())!=0)
	{
		pOriginal->ClientID.getString(bufOriginal);
		fprintf(fp,"\t\tClientID = %s -> %s    [交易编码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tClientID = %s    [交易编码]\n",buf);
	}
	MarginCombType.getString(buf);
	if (compare(MarginCombType.getValue(),pOriginal->MarginCombType.getValue())!=0)
	{
		pOriginal->MarginCombType.getString(bufOriginal);
		fprintf(fp,"\t\tMarginCombType = %s -> %s    [保证金组合类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMarginCombType = %s    [保证金组合类型]\n",buf);
	}
	InstrumentGroupID.getString(buf);
	if (compare(InstrumentGroupID.getValue(),pOriginal->InstrumentGroupID.getValue())!=0)
	{
		pOriginal->InstrumentGroupID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentGroupID = %s -> %s    [合约组代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentGroupID = %s    [合约组代码]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableIndexPreOrder::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,",HedgeFlag,%s",buf);	
	Direction.getString(buf);
	fprintf(fp,",Direction,%s",buf);	
	APIID.getString(buf);
	fprintf(fp,",APIID,%s",buf);	
	ClientID.getString(buf);
	fprintf(fp,",ClientID,%s",buf);	
	MarginCombType.getString(buf);
	fprintf(fp,",MarginCombType,%s",buf);	
	InstrumentGroupID.getString(buf);
	fprintf(fp,",InstrumentGroupID,%s",buf);	
}

void CWriteableIndexPreOrder::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	HedgeFlag.getString(buf);
	sprintf(p,"HedgeFlag=%s,",buf);
	p+=strlen(p);
	Direction.getString(buf);
	sprintf(p,"Direction=%s,",buf);
	p+=strlen(p);
	APIID.getString(buf);
	sprintf(p,"APIID=%s,",buf);
	p+=strlen(p);
	ClientID.getString(buf);
	sprintf(p,"ClientID=%s,",buf);
	p+=strlen(p);
	MarginCombType.getString(buf);
	sprintf(p,"MarginCombType=%s,",buf);
	p+=strlen(p);
	InstrumentGroupID.getString(buf);
	sprintf(p,"InstrumentGroupID=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableIndexPreOrder::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CIndexPreOrder");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编号",buf);
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	HedgeFlag.getString(buf);
	pLogger->output(indent+1,0,"HedgeFlag=%s 投机套保标志",buf);
	Direction.getString(buf);
	pLogger->output(indent+1,0,"Direction=%s 买卖方向",buf);
	APIID.getString(buf);
	pLogger->output(indent+1,0,"APIID=%s 通道对应的APIID",buf);
	ClientID.getString(buf);
	pLogger->output(indent+1,0,"ClientID=%s 交易编码",buf);
	MarginCombType.getString(buf);
	pLogger->output(indent+1,0,"MarginCombType=%s 保证金组合类型",buf);
	InstrumentGroupID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentGroupID=%s 合约组代码",buf);
	pLogger->output(indent,0,"}");
}

CIndexPreOrderIterator::~CIndexPreOrderIterator(void)
{
}


void CIndexPreOrderIterator::dump(FILE *output)
{
	CIndexPreOrder *pIndexPreOrder;
	
	while ((pIndexPreOrder=next())!=NULL)
	{
		pIndexPreOrder->dump(output);
	}
}



void CWriteableInvestorPosition::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,ExchangeID,InvestorID,ParticipantID,ClientID,InstrumentID,Direction,HedgeFlag,UsedMargin,Position,PositionCost,YdPosition,YdPositionCost,FrozenMargin,FrozenPosition,FrozenClosing,FrozenPremium,LastTradeID,LastOrderLocalID,Currency,PositionProfit,TodayPosition,FrozenTodayClosing,TradeType,AccountID,LastPrice,PositionClose,YdPositionClose,YdFrozenClosing,CacalProfitPosition,OptionType,StrikePrice,OptionInstrumentID,TodayPositionCost,ShortPosition\n");
}
	
void CWriteableInvestorPosition::init(void)
{
	BrokerID.clear();
	ExchangeID.clear();
	InvestorID.clear();
	ParticipantID.clear();
	ClientID.clear();
	InstrumentID.clear();
	Direction.clear();
	HedgeFlag.clear();
	UsedMargin.clear();
	Position.clear();
	PositionCost.clear();
	YdPosition.clear();
	YdPositionCost.clear();
	FrozenMargin.clear();
	FrozenPosition.clear();
	FrozenClosing.clear();
	FrozenPremium.clear();
	LastTradeID.clear();
	LastOrderLocalID.clear();
	Currency.clear();
	PositionProfit.clear();
	TodayPosition.clear();
	FrozenTodayClosing.clear();
	TradeType.clear();
	AccountID.clear();
	LastPrice.clear();
	PositionClose.clear();
	YdPositionClose.clear();
	YdFrozenClosing.clear();
	CacalProfitPosition.clear();
	OptionType.clear();
	StrikePrice.clear();
	OptionInstrumentID.clear();
	TodayPositionCost.clear();
	ShortPosition.clear();
}

int CWriteableInvestorPosition::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableInvestorPosition),input)!=sizeof(CWriteableInvestorPosition))
		return 0;
	else
		return 1;
}
	
int CWriteableInvestorPosition::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ParticipantID=token;
		}
		else
		{
			ParticipantID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ClientID=token;
		}
		else
		{
			ClientID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Direction=token;
		}
		else
		{
			Direction="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			HedgeFlag=token;
		}
		else
		{
			HedgeFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UsedMargin=token;
		}
		else
		{
			UsedMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Position=token;
		}
		else
		{
			Position="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			PositionCost=token;
		}
		else
		{
			PositionCost="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			YdPosition=token;
		}
		else
		{
			YdPosition="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			YdPositionCost=token;
		}
		else
		{
			YdPositionCost="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenMargin=token;
		}
		else
		{
			FrozenMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenPosition=token;
		}
		else
		{
			FrozenPosition="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenClosing=token;
		}
		else
		{
			FrozenClosing="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenPremium=token;
		}
		else
		{
			FrozenPremium="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LastTradeID=token;
		}
		else
		{
			LastTradeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LastOrderLocalID=token;
		}
		else
		{
			LastOrderLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Currency=token;
		}
		else
		{
			Currency="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			PositionProfit=token;
		}
		else
		{
			PositionProfit="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TodayPosition=token;
		}
		else
		{
			TodayPosition="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenTodayClosing=token;
		}
		else
		{
			FrozenTodayClosing="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeType=token;
		}
		else
		{
			TradeType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			AccountID=token;
		}
		else
		{
			AccountID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LastPrice=token;
		}
		else
		{
			LastPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			PositionClose=token;
		}
		else
		{
			PositionClose="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			YdPositionClose=token;
		}
		else
		{
			YdPositionClose="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			YdFrozenClosing=token;
		}
		else
		{
			YdFrozenClosing="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CacalProfitPosition=token;
		}
		else
		{
			CacalProfitPosition="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OptionType=token;
		}
		else
		{
			OptionType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			StrikePrice=token;
		}
		else
		{
			StrikePrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OptionInstrumentID=token;
		}
		else
		{
			OptionInstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TodayPositionCost=token;
		}
		else
		{
			TodayPositionCost="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ShortPosition=token;
		}
		else
		{
			ShortPosition="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"ParticipantID"))
			{
				ParticipantID=token;
			}
			else if (!strcmp(fieldName,"ClientID"))
			{
				ClientID=token;
			}
			else if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"Direction"))
			{
				Direction=token;
			}
			else if (!strcmp(fieldName,"HedgeFlag"))
			{
				HedgeFlag=token;
			}
			else if (!strcmp(fieldName,"UsedMargin"))
			{
				UsedMargin=token;
			}
			else if (!strcmp(fieldName,"Position"))
			{
				Position=token;
			}
			else if (!strcmp(fieldName,"PositionCost"))
			{
				PositionCost=token;
			}
			else if (!strcmp(fieldName,"YdPosition"))
			{
				YdPosition=token;
			}
			else if (!strcmp(fieldName,"YdPositionCost"))
			{
				YdPositionCost=token;
			}
			else if (!strcmp(fieldName,"FrozenMargin"))
			{
				FrozenMargin=token;
			}
			else if (!strcmp(fieldName,"FrozenPosition"))
			{
				FrozenPosition=token;
			}
			else if (!strcmp(fieldName,"FrozenClosing"))
			{
				FrozenClosing=token;
			}
			else if (!strcmp(fieldName,"FrozenPremium"))
			{
				FrozenPremium=token;
			}
			else if (!strcmp(fieldName,"LastTradeID"))
			{
				LastTradeID=token;
			}
			else if (!strcmp(fieldName,"LastOrderLocalID"))
			{
				LastOrderLocalID=token;
			}
			else if (!strcmp(fieldName,"Currency"))
			{
				Currency=token;
			}
			else if (!strcmp(fieldName,"PositionProfit"))
			{
				PositionProfit=token;
			}
			else if (!strcmp(fieldName,"TodayPosition"))
			{
				TodayPosition=token;
			}
			else if (!strcmp(fieldName,"FrozenTodayClosing"))
			{
				FrozenTodayClosing=token;
			}
			else if (!strcmp(fieldName,"TradeType"))
			{
				TradeType=token;
			}
			else if (!strcmp(fieldName,"AccountID"))
			{
				AccountID=token;
			}
			else if (!strcmp(fieldName,"LastPrice"))
			{
				LastPrice=token;
			}
			else if (!strcmp(fieldName,"PositionClose"))
			{
				PositionClose=token;
			}
			else if (!strcmp(fieldName,"YdPositionClose"))
			{
				YdPositionClose=token;
			}
			else if (!strcmp(fieldName,"YdFrozenClosing"))
			{
				YdFrozenClosing=token;
			}
			else if (!strcmp(fieldName,"CacalProfitPosition"))
			{
				CacalProfitPosition=token;
			}
			else if (!strcmp(fieldName,"OptionType"))
			{
				OptionType=token;
			}
			else if (!strcmp(fieldName,"StrikePrice"))
			{
				StrikePrice=token;
			}
			else if (!strcmp(fieldName,"OptionInstrumentID"))
			{
				OptionInstrumentID=token;
			}
			else if (!strcmp(fieldName,"TodayPositionCost"))
			{
				TodayPositionCost=token;
			}
			else if (!strcmp(fieldName,"ShortPosition"))
			{
				ShortPosition=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableInvestorPosition::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableInvestorPosition),output)!=sizeof(CWriteableInvestorPosition))
		return 0;
	else
		return 1;
}

int CWriteableInvestorPosition::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ParticipantID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ClientID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Direction.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	HedgeFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UsedMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Position.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	PositionCost.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	YdPosition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	YdPositionCost.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenPosition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenClosing.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenPremium.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LastTradeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LastOrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Currency.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	PositionProfit.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TodayPosition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenTodayClosing.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	AccountID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LastPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	PositionClose.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	YdPositionClose.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	YdFrozenClosing.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CacalProfitPosition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OptionType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	StrikePrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OptionInstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TodayPositionCost.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ShortPosition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableInvestorPosition::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCInvestorPosition%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,"\t\tParticipantID = %s    [会员编号]\n",buf);	
	ClientID.getString(buf);
	fprintf(fp,"\t\tClientID = %s    [客户代码]\n",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	Direction.getString(buf);
	fprintf(fp,"\t\tDirection = %s    [买卖方向]\n",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);	
	UsedMargin.getString(buf);
	fprintf(fp,"\t\tUsedMargin = %s    [占用保证金]\n",buf);	
	Position.getString(buf);
	fprintf(fp,"\t\tPosition = %s    [总持仓量]\n",buf);	
	PositionCost.getString(buf);
	fprintf(fp,"\t\tPositionCost = %s    [今日持仓成本]\n",buf);	
	YdPosition.getString(buf);
	fprintf(fp,"\t\tYdPosition = %s    [昨持仓量(不变值)]\n",buf);	
	YdPositionCost.getString(buf);
	fprintf(fp,"\t\tYdPositionCost = %s    [昨日持仓成本]\n",buf);	
	FrozenMargin.getString(buf);
	fprintf(fp,"\t\tFrozenMargin = %s    [冻结的保证金]\n",buf);	
	FrozenPosition.getString(buf);
	fprintf(fp,"\t\tFrozenPosition = %s    [开仓冻结持仓]\n",buf);	
	FrozenClosing.getString(buf);
	fprintf(fp,"\t\tFrozenClosing = %s    [平仓冻结持仓]\n",buf);	
	FrozenPremium.getString(buf);
	fprintf(fp,"\t\tFrozenPremium = %s    [冻结的权利金]\n",buf);	
	LastTradeID.getString(buf);
	fprintf(fp,"\t\tLastTradeID = %s    [最后一笔成交编号]\n",buf);	
	LastOrderLocalID.getString(buf);
	fprintf(fp,"\t\tLastOrderLocalID = %s    [最后一笔本地报单编号]\n",buf);	
	Currency.getString(buf);
	fprintf(fp,"\t\tCurrency = %s    [币种]\n",buf);	
	PositionProfit.getString(buf);
	fprintf(fp,"\t\tPositionProfit = %s    [持仓盈亏]\n",buf);	
	TodayPosition.getString(buf);
	fprintf(fp,"\t\tTodayPosition = %s    [今持仓量]\n",buf);	
	FrozenTodayClosing.getString(buf);
	fprintf(fp,"\t\tFrozenTodayClosing = %s    [今仓平仓冻结]\n",buf);	
	TradeType.getString(buf);
	fprintf(fp,"\t\tTradeType = %s    [成交类型]\n",buf);	
	AccountID.getString(buf);
	fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);	
	LastPrice.getString(buf);
	fprintf(fp,"\t\tLastPrice = %s    [计算浮动盈亏最新价]\n",buf);	
	PositionClose.getString(buf);
	fprintf(fp,"\t\tPositionClose = %s    [总持仓可平仓数量(包括平仓冻结持仓)]\n",buf);	
	YdPositionClose.getString(buf);
	fprintf(fp,"\t\tYdPositionClose = %s    [昨持仓可平仓数量(包括平仓冻结持仓)]\n",buf);	
	YdFrozenClosing.getString(buf);
	fprintf(fp,"\t\tYdFrozenClosing = %s    [昨持仓平仓冻结持仓]\n",buf);	
	CacalProfitPosition.getString(buf);
	fprintf(fp,"\t\tCacalProfitPosition = %s    [计算浮动盈亏时的总持仓]\n",buf);	
	OptionType.getString(buf);
	fprintf(fp,"\t\tOptionType = %s    [期权类型]\n",buf);	
	StrikePrice.getString(buf);
	fprintf(fp,"\t\tStrikePrice = %s    [行权价]\n",buf);	
	OptionInstrumentID.getString(buf);
	fprintf(fp,"\t\tOptionInstrumentID = %s    [期权对应的标的合约代码]\n",buf);	
	TodayPositionCost.getString(buf);
	fprintf(fp,"\t\tTodayPositionCost = %s    [今仓持仓成本]\n",buf);	
	ShortPosition.getString(buf);
	fprintf(fp,"\t\tShortPosition = %s    [短线持仓]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableInvestorPosition::dumpDiff(FILE *fp, const CWriteableInvestorPosition *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCInvestorPosition = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);
	}
	ParticipantID.getString(buf);
	if (compare(ParticipantID.getValue(),pOriginal->ParticipantID.getValue())!=0)
	{
		pOriginal->ParticipantID.getString(bufOriginal);
		fprintf(fp,"\t\tParticipantID = %s -> %s    [会员编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tParticipantID = %s    [会员编号]\n",buf);
	}
	ClientID.getString(buf);
	if (compare(ClientID.getValue(),pOriginal->ClientID.getValue())!=0)
	{
		pOriginal->ClientID.getString(bufOriginal);
		fprintf(fp,"\t\tClientID = %s -> %s    [客户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tClientID = %s    [客户代码]\n",buf);
	}
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	Direction.getString(buf);
	if (compare(Direction.getValue(),pOriginal->Direction.getValue())!=0)
	{
		pOriginal->Direction.getString(bufOriginal);
		fprintf(fp,"\t\tDirection = %s -> %s    [买卖方向]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDirection = %s    [买卖方向]\n",buf);
	}
	HedgeFlag.getString(buf);
	if (compare(HedgeFlag.getValue(),pOriginal->HedgeFlag.getValue())!=0)
	{
		pOriginal->HedgeFlag.getString(bufOriginal);
		fprintf(fp,"\t\tHedgeFlag = %s -> %s    [投机套保标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);
	}
	UsedMargin.getString(buf);
	if (compare(UsedMargin.getValue(),pOriginal->UsedMargin.getValue())!=0)
	{
		pOriginal->UsedMargin.getString(bufOriginal);
		fprintf(fp,"\t\tUsedMargin = %s -> %s    [占用保证金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUsedMargin = %s    [占用保证金]\n",buf);
	}
	Position.getString(buf);
	if (compare(Position.getValue(),pOriginal->Position.getValue())!=0)
	{
		pOriginal->Position.getString(bufOriginal);
		fprintf(fp,"\t\tPosition = %s -> %s    [总持仓量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPosition = %s    [总持仓量]\n",buf);
	}
	PositionCost.getString(buf);
	if (compare(PositionCost.getValue(),pOriginal->PositionCost.getValue())!=0)
	{
		pOriginal->PositionCost.getString(bufOriginal);
		fprintf(fp,"\t\tPositionCost = %s -> %s    [今日持仓成本]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPositionCost = %s    [今日持仓成本]\n",buf);
	}
	YdPosition.getString(buf);
	if (compare(YdPosition.getValue(),pOriginal->YdPosition.getValue())!=0)
	{
		pOriginal->YdPosition.getString(bufOriginal);
		fprintf(fp,"\t\tYdPosition = %s -> %s    [昨持仓量(不变值)]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tYdPosition = %s    [昨持仓量(不变值)]\n",buf);
	}
	YdPositionCost.getString(buf);
	if (compare(YdPositionCost.getValue(),pOriginal->YdPositionCost.getValue())!=0)
	{
		pOriginal->YdPositionCost.getString(bufOriginal);
		fprintf(fp,"\t\tYdPositionCost = %s -> %s    [昨日持仓成本]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tYdPositionCost = %s    [昨日持仓成本]\n",buf);
	}
	FrozenMargin.getString(buf);
	if (compare(FrozenMargin.getValue(),pOriginal->FrozenMargin.getValue())!=0)
	{
		pOriginal->FrozenMargin.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenMargin = %s -> %s    [冻结的保证金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenMargin = %s    [冻结的保证金]\n",buf);
	}
	FrozenPosition.getString(buf);
	if (compare(FrozenPosition.getValue(),pOriginal->FrozenPosition.getValue())!=0)
	{
		pOriginal->FrozenPosition.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenPosition = %s -> %s    [开仓冻结持仓]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenPosition = %s    [开仓冻结持仓]\n",buf);
	}
	FrozenClosing.getString(buf);
	if (compare(FrozenClosing.getValue(),pOriginal->FrozenClosing.getValue())!=0)
	{
		pOriginal->FrozenClosing.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenClosing = %s -> %s    [平仓冻结持仓]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenClosing = %s    [平仓冻结持仓]\n",buf);
	}
	FrozenPremium.getString(buf);
	if (compare(FrozenPremium.getValue(),pOriginal->FrozenPremium.getValue())!=0)
	{
		pOriginal->FrozenPremium.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenPremium = %s -> %s    [冻结的权利金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenPremium = %s    [冻结的权利金]\n",buf);
	}
	LastTradeID.getString(buf);
	if (compare(LastTradeID.getValue(),pOriginal->LastTradeID.getValue())!=0)
	{
		pOriginal->LastTradeID.getString(bufOriginal);
		fprintf(fp,"\t\tLastTradeID = %s -> %s    [最后一笔成交编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLastTradeID = %s    [最后一笔成交编号]\n",buf);
	}
	LastOrderLocalID.getString(buf);
	if (compare(LastOrderLocalID.getValue(),pOriginal->LastOrderLocalID.getValue())!=0)
	{
		pOriginal->LastOrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tLastOrderLocalID = %s -> %s    [最后一笔本地报单编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLastOrderLocalID = %s    [最后一笔本地报单编号]\n",buf);
	}
	Currency.getString(buf);
	if (compare(Currency.getValue(),pOriginal->Currency.getValue())!=0)
	{
		pOriginal->Currency.getString(bufOriginal);
		fprintf(fp,"\t\tCurrency = %s -> %s    [币种]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCurrency = %s    [币种]\n",buf);
	}
	PositionProfit.getString(buf);
	if (compare(PositionProfit.getValue(),pOriginal->PositionProfit.getValue())!=0)
	{
		pOriginal->PositionProfit.getString(bufOriginal);
		fprintf(fp,"\t\tPositionProfit = %s -> %s    [持仓盈亏]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPositionProfit = %s    [持仓盈亏]\n",buf);
	}
	TodayPosition.getString(buf);
	if (compare(TodayPosition.getValue(),pOriginal->TodayPosition.getValue())!=0)
	{
		pOriginal->TodayPosition.getString(bufOriginal);
		fprintf(fp,"\t\tTodayPosition = %s -> %s    [今持仓量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTodayPosition = %s    [今持仓量]\n",buf);
	}
	FrozenTodayClosing.getString(buf);
	if (compare(FrozenTodayClosing.getValue(),pOriginal->FrozenTodayClosing.getValue())!=0)
	{
		pOriginal->FrozenTodayClosing.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenTodayClosing = %s -> %s    [今仓平仓冻结]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenTodayClosing = %s    [今仓平仓冻结]\n",buf);
	}
	TradeType.getString(buf);
	if (compare(TradeType.getValue(),pOriginal->TradeType.getValue())!=0)
	{
		pOriginal->TradeType.getString(bufOriginal);
		fprintf(fp,"\t\tTradeType = %s -> %s    [成交类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeType = %s    [成交类型]\n",buf);
	}
	AccountID.getString(buf);
	if (compare(AccountID.getValue(),pOriginal->AccountID.getValue())!=0)
	{
		pOriginal->AccountID.getString(bufOriginal);
		fprintf(fp,"\t\tAccountID = %s -> %s    [资金帐号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);
	}
	LastPrice.getString(buf);
	if (compare(LastPrice.getValue(),pOriginal->LastPrice.getValue())!=0)
	{
		pOriginal->LastPrice.getString(bufOriginal);
		fprintf(fp,"\t\tLastPrice = %s -> %s    [计算浮动盈亏最新价]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLastPrice = %s    [计算浮动盈亏最新价]\n",buf);
	}
	PositionClose.getString(buf);
	if (compare(PositionClose.getValue(),pOriginal->PositionClose.getValue())!=0)
	{
		pOriginal->PositionClose.getString(bufOriginal);
		fprintf(fp,"\t\tPositionClose = %s -> %s    [总持仓可平仓数量(包括平仓冻结持仓)]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPositionClose = %s    [总持仓可平仓数量(包括平仓冻结持仓)]\n",buf);
	}
	YdPositionClose.getString(buf);
	if (compare(YdPositionClose.getValue(),pOriginal->YdPositionClose.getValue())!=0)
	{
		pOriginal->YdPositionClose.getString(bufOriginal);
		fprintf(fp,"\t\tYdPositionClose = %s -> %s    [昨持仓可平仓数量(包括平仓冻结持仓)]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tYdPositionClose = %s    [昨持仓可平仓数量(包括平仓冻结持仓)]\n",buf);
	}
	YdFrozenClosing.getString(buf);
	if (compare(YdFrozenClosing.getValue(),pOriginal->YdFrozenClosing.getValue())!=0)
	{
		pOriginal->YdFrozenClosing.getString(bufOriginal);
		fprintf(fp,"\t\tYdFrozenClosing = %s -> %s    [昨持仓平仓冻结持仓]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tYdFrozenClosing = %s    [昨持仓平仓冻结持仓]\n",buf);
	}
	CacalProfitPosition.getString(buf);
	if (compare(CacalProfitPosition.getValue(),pOriginal->CacalProfitPosition.getValue())!=0)
	{
		pOriginal->CacalProfitPosition.getString(bufOriginal);
		fprintf(fp,"\t\tCacalProfitPosition = %s -> %s    [计算浮动盈亏时的总持仓]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCacalProfitPosition = %s    [计算浮动盈亏时的总持仓]\n",buf);
	}
	OptionType.getString(buf);
	if (compare(OptionType.getValue(),pOriginal->OptionType.getValue())!=0)
	{
		pOriginal->OptionType.getString(bufOriginal);
		fprintf(fp,"\t\tOptionType = %s -> %s    [期权类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOptionType = %s    [期权类型]\n",buf);
	}
	StrikePrice.getString(buf);
	if (compare(StrikePrice.getValue(),pOriginal->StrikePrice.getValue())!=0)
	{
		pOriginal->StrikePrice.getString(bufOriginal);
		fprintf(fp,"\t\tStrikePrice = %s -> %s    [行权价]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tStrikePrice = %s    [行权价]\n",buf);
	}
	OptionInstrumentID.getString(buf);
	if (compare(OptionInstrumentID.getValue(),pOriginal->OptionInstrumentID.getValue())!=0)
	{
		pOriginal->OptionInstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tOptionInstrumentID = %s -> %s    [期权对应的标的合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOptionInstrumentID = %s    [期权对应的标的合约代码]\n",buf);
	}
	TodayPositionCost.getString(buf);
	if (compare(TodayPositionCost.getValue(),pOriginal->TodayPositionCost.getValue())!=0)
	{
		pOriginal->TodayPositionCost.getString(bufOriginal);
		fprintf(fp,"\t\tTodayPositionCost = %s -> %s    [今仓持仓成本]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTodayPositionCost = %s    [今仓持仓成本]\n",buf);
	}
	ShortPosition.getString(buf);
	if (compare(ShortPosition.getValue(),pOriginal->ShortPosition.getValue())!=0)
	{
		pOriginal->ShortPosition.getString(bufOriginal);
		fprintf(fp,"\t\tShortPosition = %s -> %s    [短线持仓]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tShortPosition = %s    [短线持仓]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableInvestorPosition::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,",ParticipantID,%s",buf);	
	ClientID.getString(buf);
	fprintf(fp,",ClientID,%s",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	Direction.getString(buf);
	fprintf(fp,",Direction,%s",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,",HedgeFlag,%s",buf);	
	UsedMargin.getString(buf);
	fprintf(fp,",UsedMargin,%s",buf);	
	Position.getString(buf);
	fprintf(fp,",Position,%s",buf);	
	PositionCost.getString(buf);
	fprintf(fp,",PositionCost,%s",buf);	
	YdPosition.getString(buf);
	fprintf(fp,",YdPosition,%s",buf);	
	YdPositionCost.getString(buf);
	fprintf(fp,",YdPositionCost,%s",buf);	
	FrozenMargin.getString(buf);
	fprintf(fp,",FrozenMargin,%s",buf);	
	FrozenPosition.getString(buf);
	fprintf(fp,",FrozenPosition,%s",buf);	
	FrozenClosing.getString(buf);
	fprintf(fp,",FrozenClosing,%s",buf);	
	FrozenPremium.getString(buf);
	fprintf(fp,",FrozenPremium,%s",buf);	
	LastTradeID.getString(buf);
	fprintf(fp,",LastTradeID,%s",buf);	
	LastOrderLocalID.getString(buf);
	fprintf(fp,",LastOrderLocalID,%s",buf);	
	Currency.getString(buf);
	fprintf(fp,",Currency,%s",buf);	
	PositionProfit.getString(buf);
	fprintf(fp,",PositionProfit,%s",buf);	
	TodayPosition.getString(buf);
	fprintf(fp,",TodayPosition,%s",buf);	
	FrozenTodayClosing.getString(buf);
	fprintf(fp,",FrozenTodayClosing,%s",buf);	
	TradeType.getString(buf);
	fprintf(fp,",TradeType,%s",buf);	
	AccountID.getString(buf);
	fprintf(fp,",AccountID,%s",buf);	
	LastPrice.getString(buf);
	fprintf(fp,",LastPrice,%s",buf);	
	PositionClose.getString(buf);
	fprintf(fp,",PositionClose,%s",buf);	
	YdPositionClose.getString(buf);
	fprintf(fp,",YdPositionClose,%s",buf);	
	YdFrozenClosing.getString(buf);
	fprintf(fp,",YdFrozenClosing,%s",buf);	
	CacalProfitPosition.getString(buf);
	fprintf(fp,",CacalProfitPosition,%s",buf);	
	OptionType.getString(buf);
	fprintf(fp,",OptionType,%s",buf);	
	StrikePrice.getString(buf);
	fprintf(fp,",StrikePrice,%s",buf);	
	OptionInstrumentID.getString(buf);
	fprintf(fp,",OptionInstrumentID,%s",buf);	
	TodayPositionCost.getString(buf);
	fprintf(fp,",TodayPositionCost,%s",buf);	
	ShortPosition.getString(buf);
	fprintf(fp,",ShortPosition,%s",buf);	
}

void CWriteableInvestorPosition::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	ParticipantID.getString(buf);
	sprintf(p,"ParticipantID=%s,",buf);
	p+=strlen(p);
	ClientID.getString(buf);
	sprintf(p,"ClientID=%s,",buf);
	p+=strlen(p);
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	Direction.getString(buf);
	sprintf(p,"Direction=%s,",buf);
	p+=strlen(p);
	HedgeFlag.getString(buf);
	sprintf(p,"HedgeFlag=%s,",buf);
	p+=strlen(p);
	UsedMargin.getString(buf);
	sprintf(p,"UsedMargin=%s,",buf);
	p+=strlen(p);
	Position.getString(buf);
	sprintf(p,"Position=%s,",buf);
	p+=strlen(p);
	PositionCost.getString(buf);
	sprintf(p,"PositionCost=%s,",buf);
	p+=strlen(p);
	YdPosition.getString(buf);
	sprintf(p,"YdPosition=%s,",buf);
	p+=strlen(p);
	YdPositionCost.getString(buf);
	sprintf(p,"YdPositionCost=%s,",buf);
	p+=strlen(p);
	FrozenMargin.getString(buf);
	sprintf(p,"FrozenMargin=%s,",buf);
	p+=strlen(p);
	FrozenPosition.getString(buf);
	sprintf(p,"FrozenPosition=%s,",buf);
	p+=strlen(p);
	FrozenClosing.getString(buf);
	sprintf(p,"FrozenClosing=%s,",buf);
	p+=strlen(p);
	FrozenPremium.getString(buf);
	sprintf(p,"FrozenPremium=%s,",buf);
	p+=strlen(p);
	LastTradeID.getString(buf);
	sprintf(p,"LastTradeID=%s,",buf);
	p+=strlen(p);
	LastOrderLocalID.getString(buf);
	sprintf(p,"LastOrderLocalID=%s,",buf);
	p+=strlen(p);
	Currency.getString(buf);
	sprintf(p,"Currency=%s,",buf);
	p+=strlen(p);
	PositionProfit.getString(buf);
	sprintf(p,"PositionProfit=%s,",buf);
	p+=strlen(p);
	TodayPosition.getString(buf);
	sprintf(p,"TodayPosition=%s,",buf);
	p+=strlen(p);
	FrozenTodayClosing.getString(buf);
	sprintf(p,"FrozenTodayClosing=%s,",buf);
	p+=strlen(p);
	TradeType.getString(buf);
	sprintf(p,"TradeType=%s,",buf);
	p+=strlen(p);
	AccountID.getString(buf);
	sprintf(p,"AccountID=%s,",buf);
	p+=strlen(p);
	LastPrice.getString(buf);
	sprintf(p,"LastPrice=%s,",buf);
	p+=strlen(p);
	PositionClose.getString(buf);
	sprintf(p,"PositionClose=%s,",buf);
	p+=strlen(p);
	YdPositionClose.getString(buf);
	sprintf(p,"YdPositionClose=%s,",buf);
	p+=strlen(p);
	YdFrozenClosing.getString(buf);
	sprintf(p,"YdFrozenClosing=%s,",buf);
	p+=strlen(p);
	CacalProfitPosition.getString(buf);
	sprintf(p,"CacalProfitPosition=%s,",buf);
	p+=strlen(p);
	OptionType.getString(buf);
	sprintf(p,"OptionType=%s,",buf);
	p+=strlen(p);
	StrikePrice.getString(buf);
	sprintf(p,"StrikePrice=%s,",buf);
	p+=strlen(p);
	OptionInstrumentID.getString(buf);
	sprintf(p,"OptionInstrumentID=%s,",buf);
	p+=strlen(p);
	TodayPositionCost.getString(buf);
	sprintf(p,"TodayPositionCost=%s,",buf);
	p+=strlen(p);
	ShortPosition.getString(buf);
	sprintf(p,"ShortPosition=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableInvestorPosition::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CInvestorPosition");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编号",buf);
	ParticipantID.getString(buf);
	pLogger->output(indent+1,0,"ParticipantID=%s 会员编号",buf);
	ClientID.getString(buf);
	pLogger->output(indent+1,0,"ClientID=%s 客户代码",buf);
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	Direction.getString(buf);
	pLogger->output(indent+1,0,"Direction=%s 买卖方向",buf);
	HedgeFlag.getString(buf);
	pLogger->output(indent+1,0,"HedgeFlag=%s 投机套保标志",buf);
	UsedMargin.getString(buf);
	pLogger->output(indent+1,0,"UsedMargin=%s 占用保证金",buf);
	Position.getString(buf);
	pLogger->output(indent+1,0,"Position=%s 总持仓量",buf);
	PositionCost.getString(buf);
	pLogger->output(indent+1,0,"PositionCost=%s 今日持仓成本",buf);
	YdPosition.getString(buf);
	pLogger->output(indent+1,0,"YdPosition=%s 昨持仓量(不变值)",buf);
	YdPositionCost.getString(buf);
	pLogger->output(indent+1,0,"YdPositionCost=%s 昨日持仓成本",buf);
	FrozenMargin.getString(buf);
	pLogger->output(indent+1,0,"FrozenMargin=%s 冻结的保证金",buf);
	FrozenPosition.getString(buf);
	pLogger->output(indent+1,0,"FrozenPosition=%s 开仓冻结持仓",buf);
	FrozenClosing.getString(buf);
	pLogger->output(indent+1,0,"FrozenClosing=%s 平仓冻结持仓",buf);
	FrozenPremium.getString(buf);
	pLogger->output(indent+1,0,"FrozenPremium=%s 冻结的权利金",buf);
	LastTradeID.getString(buf);
	pLogger->output(indent+1,0,"LastTradeID=%s 最后一笔成交编号",buf);
	LastOrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"LastOrderLocalID=%s 最后一笔本地报单编号",buf);
	Currency.getString(buf);
	pLogger->output(indent+1,0,"Currency=%s 币种",buf);
	PositionProfit.getString(buf);
	pLogger->output(indent+1,0,"PositionProfit=%s 持仓盈亏",buf);
	TodayPosition.getString(buf);
	pLogger->output(indent+1,0,"TodayPosition=%s 今持仓量",buf);
	FrozenTodayClosing.getString(buf);
	pLogger->output(indent+1,0,"FrozenTodayClosing=%s 今仓平仓冻结",buf);
	TradeType.getString(buf);
	pLogger->output(indent+1,0,"TradeType=%s 成交类型",buf);
	AccountID.getString(buf);
	pLogger->output(indent+1,0,"AccountID=%s 资金帐号",buf);
	LastPrice.getString(buf);
	pLogger->output(indent+1,0,"LastPrice=%s 计算浮动盈亏最新价",buf);
	PositionClose.getString(buf);
	pLogger->output(indent+1,0,"PositionClose=%s 总持仓可平仓数量(包括平仓冻结持仓)",buf);
	YdPositionClose.getString(buf);
	pLogger->output(indent+1,0,"YdPositionClose=%s 昨持仓可平仓数量(包括平仓冻结持仓)",buf);
	YdFrozenClosing.getString(buf);
	pLogger->output(indent+1,0,"YdFrozenClosing=%s 昨持仓平仓冻结持仓",buf);
	CacalProfitPosition.getString(buf);
	pLogger->output(indent+1,0,"CacalProfitPosition=%s 计算浮动盈亏时的总持仓",buf);
	OptionType.getString(buf);
	pLogger->output(indent+1,0,"OptionType=%s 期权类型",buf);
	StrikePrice.getString(buf);
	pLogger->output(indent+1,0,"StrikePrice=%s 行权价",buf);
	OptionInstrumentID.getString(buf);
	pLogger->output(indent+1,0,"OptionInstrumentID=%s 期权对应的标的合约代码",buf);
	TodayPositionCost.getString(buf);
	pLogger->output(indent+1,0,"TodayPositionCost=%s 今仓持仓成本",buf);
	ShortPosition.getString(buf);
	pLogger->output(indent+1,0,"ShortPosition=%s 短线持仓",buf);
	pLogger->output(indent,0,"}");
}

CInvestorPositionIterator::~CInvestorPositionIterator(void)
{
}


void CInvestorPositionIterator::dump(FILE *output)
{
	CInvestorPosition *pInvestorPosition;
	
	while ((pInvestorPosition=next())!=NULL)
	{
		pInvestorPosition->dump(output);
	}
}



void CWriteableInvestorAccount::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,InvestorID,AccountID,PreBalance,PreAvailable,Deposit,Withdraw,Margin,Premium,Fee,FrozenMargin,FrozenPremium,FrozenFee,CloseProfit,PositionProfit,Available,Balance,LongMargin,ShortMargin,LongFrozenMargin,ShortFrozenMargin,DynamicRights,Risk,OtherFee,Mortgage,Currency,TotalFrozenPos,TodayInOut,ReleaseMargin,IsProfitCanUse,ManualFrozen\n");
}
	
void CWriteableInvestorAccount::init(void)
{
	BrokerID.clear();
	InvestorID.clear();
	AccountID.clear();
	PreBalance.clear();
	PreAvailable.clear();
	Deposit.clear();
	Withdraw.clear();
	Margin.clear();
	Premium.clear();
	Fee.clear();
	FrozenMargin.clear();
	FrozenPremium.clear();
	FrozenFee.clear();
	CloseProfit.clear();
	PositionProfit.clear();
	Available.clear();
	Balance.clear();
	LongMargin.clear();
	ShortMargin.clear();
	LongFrozenMargin.clear();
	ShortFrozenMargin.clear();
	DynamicRights.clear();
	Risk.clear();
	OtherFee.clear();
	Mortgage.clear();
	Currency.clear();
	TotalFrozenPos.clear();
	TodayInOut.clear();
	ReleaseMargin.clear();
	IsProfitCanUse.clear();
	ManualFrozen.clear();
}

int CWriteableInvestorAccount::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableInvestorAccount),input)!=sizeof(CWriteableInvestorAccount))
		return 0;
	else
		return 1;
}
	
int CWriteableInvestorAccount::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			AccountID=token;
		}
		else
		{
			AccountID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			PreBalance=token;
		}
		else
		{
			PreBalance="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			PreAvailable=token;
		}
		else
		{
			PreAvailable="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Deposit=token;
		}
		else
		{
			Deposit="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Withdraw=token;
		}
		else
		{
			Withdraw="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Margin=token;
		}
		else
		{
			Margin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Premium=token;
		}
		else
		{
			Premium="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Fee=token;
		}
		else
		{
			Fee="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenMargin=token;
		}
		else
		{
			FrozenMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenPremium=token;
		}
		else
		{
			FrozenPremium="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenFee=token;
		}
		else
		{
			FrozenFee="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CloseProfit=token;
		}
		else
		{
			CloseProfit="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			PositionProfit=token;
		}
		else
		{
			PositionProfit="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Available=token;
		}
		else
		{
			Available="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Balance=token;
		}
		else
		{
			Balance="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LongMargin=token;
		}
		else
		{
			LongMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ShortMargin=token;
		}
		else
		{
			ShortMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LongFrozenMargin=token;
		}
		else
		{
			LongFrozenMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ShortFrozenMargin=token;
		}
		else
		{
			ShortFrozenMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			DynamicRights=token;
		}
		else
		{
			DynamicRights="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Risk=token;
		}
		else
		{
			Risk="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OtherFee=token;
		}
		else
		{
			OtherFee="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Mortgage=token;
		}
		else
		{
			Mortgage="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Currency=token;
		}
		else
		{
			Currency="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TotalFrozenPos=token;
		}
		else
		{
			TotalFrozenPos="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TodayInOut=token;
		}
		else
		{
			TodayInOut="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ReleaseMargin=token;
		}
		else
		{
			ReleaseMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IsProfitCanUse=token;
		}
		else
		{
			IsProfitCanUse="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ManualFrozen=token;
		}
		else
		{
			ManualFrozen="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"AccountID"))
			{
				AccountID=token;
			}
			else if (!strcmp(fieldName,"PreBalance"))
			{
				PreBalance=token;
			}
			else if (!strcmp(fieldName,"PreAvailable"))
			{
				PreAvailable=token;
			}
			else if (!strcmp(fieldName,"Deposit"))
			{
				Deposit=token;
			}
			else if (!strcmp(fieldName,"Withdraw"))
			{
				Withdraw=token;
			}
			else if (!strcmp(fieldName,"Margin"))
			{
				Margin=token;
			}
			else if (!strcmp(fieldName,"Premium"))
			{
				Premium=token;
			}
			else if (!strcmp(fieldName,"Fee"))
			{
				Fee=token;
			}
			else if (!strcmp(fieldName,"FrozenMargin"))
			{
				FrozenMargin=token;
			}
			else if (!strcmp(fieldName,"FrozenPremium"))
			{
				FrozenPremium=token;
			}
			else if (!strcmp(fieldName,"FrozenFee"))
			{
				FrozenFee=token;
			}
			else if (!strcmp(fieldName,"CloseProfit"))
			{
				CloseProfit=token;
			}
			else if (!strcmp(fieldName,"PositionProfit"))
			{
				PositionProfit=token;
			}
			else if (!strcmp(fieldName,"Available"))
			{
				Available=token;
			}
			else if (!strcmp(fieldName,"Balance"))
			{
				Balance=token;
			}
			else if (!strcmp(fieldName,"LongMargin"))
			{
				LongMargin=token;
			}
			else if (!strcmp(fieldName,"ShortMargin"))
			{
				ShortMargin=token;
			}
			else if (!strcmp(fieldName,"LongFrozenMargin"))
			{
				LongFrozenMargin=token;
			}
			else if (!strcmp(fieldName,"ShortFrozenMargin"))
			{
				ShortFrozenMargin=token;
			}
			else if (!strcmp(fieldName,"DynamicRights"))
			{
				DynamicRights=token;
			}
			else if (!strcmp(fieldName,"Risk"))
			{
				Risk=token;
			}
			else if (!strcmp(fieldName,"OtherFee"))
			{
				OtherFee=token;
			}
			else if (!strcmp(fieldName,"Mortgage"))
			{
				Mortgage=token;
			}
			else if (!strcmp(fieldName,"Currency"))
			{
				Currency=token;
			}
			else if (!strcmp(fieldName,"TotalFrozenPos"))
			{
				TotalFrozenPos=token;
			}
			else if (!strcmp(fieldName,"TodayInOut"))
			{
				TodayInOut=token;
			}
			else if (!strcmp(fieldName,"ReleaseMargin"))
			{
				ReleaseMargin=token;
			}
			else if (!strcmp(fieldName,"IsProfitCanUse"))
			{
				IsProfitCanUse=token;
			}
			else if (!strcmp(fieldName,"ManualFrozen"))
			{
				ManualFrozen=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableInvestorAccount::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableInvestorAccount),output)!=sizeof(CWriteableInvestorAccount))
		return 0;
	else
		return 1;
}

int CWriteableInvestorAccount::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	AccountID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	PreBalance.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	PreAvailable.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Deposit.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Withdraw.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Margin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Premium.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Fee.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenPremium.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenFee.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CloseProfit.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	PositionProfit.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Available.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Balance.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LongMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ShortMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LongFrozenMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ShortFrozenMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	DynamicRights.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Risk.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OtherFee.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Mortgage.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Currency.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TotalFrozenPos.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TodayInOut.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ReleaseMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IsProfitCanUse.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ManualFrozen.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableInvestorAccount::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCInvestorAccount%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);	
	AccountID.getString(buf);
	fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);	
	PreBalance.getString(buf);
	fprintf(fp,"\t\tPreBalance = %s    [上次结算准备金]\n",buf);	
	PreAvailable.getString(buf);
	fprintf(fp,"\t\tPreAvailable = %s    [上日可用资金]\n",buf);	
	Deposit.getString(buf);
	fprintf(fp,"\t\tDeposit = %s    [入金金额]\n",buf);	
	Withdraw.getString(buf);
	fprintf(fp,"\t\tWithdraw = %s    [出金金额]\n",buf);	
	Margin.getString(buf);
	fprintf(fp,"\t\tMargin = %s    [占用保证金]\n",buf);	
	Premium.getString(buf);
	fprintf(fp,"\t\tPremium = %s    [期权权利金收支]\n",buf);	
	Fee.getString(buf);
	fprintf(fp,"\t\tFee = %s    [手续费]\n",buf);	
	FrozenMargin.getString(buf);
	fprintf(fp,"\t\tFrozenMargin = %s    [冻结的保证金]\n",buf);	
	FrozenPremium.getString(buf);
	fprintf(fp,"\t\tFrozenPremium = %s    [冻结权利金]\n",buf);	
	FrozenFee.getString(buf);
	fprintf(fp,"\t\tFrozenFee = %s    [冻结手续费]\n",buf);	
	CloseProfit.getString(buf);
	fprintf(fp,"\t\tCloseProfit = %s    [平仓盈亏]\n",buf);	
	PositionProfit.getString(buf);
	fprintf(fp,"\t\tPositionProfit = %s    [持仓盈亏]\n",buf);	
	Available.getString(buf);
	fprintf(fp,"\t\tAvailable = %s    [可用资金]\n",buf);	
	Balance.getString(buf);
	fprintf(fp,"\t\tBalance = %s    [结算准备金]\n",buf);	
	LongMargin.getString(buf);
	fprintf(fp,"\t\tLongMargin = %s    [多头占用保证金]\n",buf);	
	ShortMargin.getString(buf);
	fprintf(fp,"\t\tShortMargin = %s    [空头占用保证金]\n",buf);	
	LongFrozenMargin.getString(buf);
	fprintf(fp,"\t\tLongFrozenMargin = %s    [多头冻结的保证金]\n",buf);	
	ShortFrozenMargin.getString(buf);
	fprintf(fp,"\t\tShortFrozenMargin = %s    [空头冻结的保证金]\n",buf);	
	DynamicRights.getString(buf);
	fprintf(fp,"\t\tDynamicRights = %s    [动态权益]\n",buf);	
	Risk.getString(buf);
	fprintf(fp,"\t\tRisk = %s    [风险度]\n",buf);	
	OtherFee.getString(buf);
	fprintf(fp,"\t\tOtherFee = %s    [其他费用]\n",buf);	
	Mortgage.getString(buf);
	fprintf(fp,"\t\tMortgage = %s    [质押金额]\n",buf);	
	Currency.getString(buf);
	fprintf(fp,"\t\tCurrency = %s    [币种]\n",buf);	
	TotalFrozenPos.getString(buf);
	fprintf(fp,"\t\tTotalFrozenPos = %s    [总冻结持仓]\n",buf);	
	TodayInOut.getString(buf);
	fprintf(fp,"\t\tTodayInOut = %s    [今日出入金]\n",buf);	
	ReleaseMargin.getString(buf);
	fprintf(fp,"\t\tReleaseMargin = %s    [当日释放保证金]\n",buf);	
	IsProfitCanUse.getString(buf);
	fprintf(fp,"\t\tIsProfitCanUse = %s    [浮盈是否可用]\n",buf);	
	ManualFrozen.getString(buf);
	fprintf(fp,"\t\tManualFrozen = %s    [临时冻结资金]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableInvestorAccount::dumpDiff(FILE *fp, const CWriteableInvestorAccount *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCInvestorAccount = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);
	}
	AccountID.getString(buf);
	if (compare(AccountID.getValue(),pOriginal->AccountID.getValue())!=0)
	{
		pOriginal->AccountID.getString(bufOriginal);
		fprintf(fp,"\t\tAccountID = %s -> %s    [资金帐号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);
	}
	PreBalance.getString(buf);
	if (compare(PreBalance.getValue(),pOriginal->PreBalance.getValue())!=0)
	{
		pOriginal->PreBalance.getString(bufOriginal);
		fprintf(fp,"\t\tPreBalance = %s -> %s    [上次结算准备金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPreBalance = %s    [上次结算准备金]\n",buf);
	}
	PreAvailable.getString(buf);
	if (compare(PreAvailable.getValue(),pOriginal->PreAvailable.getValue())!=0)
	{
		pOriginal->PreAvailable.getString(bufOriginal);
		fprintf(fp,"\t\tPreAvailable = %s -> %s    [上日可用资金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPreAvailable = %s    [上日可用资金]\n",buf);
	}
	Deposit.getString(buf);
	if (compare(Deposit.getValue(),pOriginal->Deposit.getValue())!=0)
	{
		pOriginal->Deposit.getString(bufOriginal);
		fprintf(fp,"\t\tDeposit = %s -> %s    [入金金额]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDeposit = %s    [入金金额]\n",buf);
	}
	Withdraw.getString(buf);
	if (compare(Withdraw.getValue(),pOriginal->Withdraw.getValue())!=0)
	{
		pOriginal->Withdraw.getString(bufOriginal);
		fprintf(fp,"\t\tWithdraw = %s -> %s    [出金金额]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tWithdraw = %s    [出金金额]\n",buf);
	}
	Margin.getString(buf);
	if (compare(Margin.getValue(),pOriginal->Margin.getValue())!=0)
	{
		pOriginal->Margin.getString(bufOriginal);
		fprintf(fp,"\t\tMargin = %s -> %s    [占用保证金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMargin = %s    [占用保证金]\n",buf);
	}
	Premium.getString(buf);
	if (compare(Premium.getValue(),pOriginal->Premium.getValue())!=0)
	{
		pOriginal->Premium.getString(bufOriginal);
		fprintf(fp,"\t\tPremium = %s -> %s    [期权权利金收支]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPremium = %s    [期权权利金收支]\n",buf);
	}
	Fee.getString(buf);
	if (compare(Fee.getValue(),pOriginal->Fee.getValue())!=0)
	{
		pOriginal->Fee.getString(bufOriginal);
		fprintf(fp,"\t\tFee = %s -> %s    [手续费]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFee = %s    [手续费]\n",buf);
	}
	FrozenMargin.getString(buf);
	if (compare(FrozenMargin.getValue(),pOriginal->FrozenMargin.getValue())!=0)
	{
		pOriginal->FrozenMargin.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenMargin = %s -> %s    [冻结的保证金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenMargin = %s    [冻结的保证金]\n",buf);
	}
	FrozenPremium.getString(buf);
	if (compare(FrozenPremium.getValue(),pOriginal->FrozenPremium.getValue())!=0)
	{
		pOriginal->FrozenPremium.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenPremium = %s -> %s    [冻结权利金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenPremium = %s    [冻结权利金]\n",buf);
	}
	FrozenFee.getString(buf);
	if (compare(FrozenFee.getValue(),pOriginal->FrozenFee.getValue())!=0)
	{
		pOriginal->FrozenFee.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenFee = %s -> %s    [冻结手续费]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenFee = %s    [冻结手续费]\n",buf);
	}
	CloseProfit.getString(buf);
	if (compare(CloseProfit.getValue(),pOriginal->CloseProfit.getValue())!=0)
	{
		pOriginal->CloseProfit.getString(bufOriginal);
		fprintf(fp,"\t\tCloseProfit = %s -> %s    [平仓盈亏]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCloseProfit = %s    [平仓盈亏]\n",buf);
	}
	PositionProfit.getString(buf);
	if (compare(PositionProfit.getValue(),pOriginal->PositionProfit.getValue())!=0)
	{
		pOriginal->PositionProfit.getString(bufOriginal);
		fprintf(fp,"\t\tPositionProfit = %s -> %s    [持仓盈亏]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPositionProfit = %s    [持仓盈亏]\n",buf);
	}
	Available.getString(buf);
	if (compare(Available.getValue(),pOriginal->Available.getValue())!=0)
	{
		pOriginal->Available.getString(bufOriginal);
		fprintf(fp,"\t\tAvailable = %s -> %s    [可用资金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAvailable = %s    [可用资金]\n",buf);
	}
	Balance.getString(buf);
	if (compare(Balance.getValue(),pOriginal->Balance.getValue())!=0)
	{
		pOriginal->Balance.getString(bufOriginal);
		fprintf(fp,"\t\tBalance = %s -> %s    [结算准备金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBalance = %s    [结算准备金]\n",buf);
	}
	LongMargin.getString(buf);
	if (compare(LongMargin.getValue(),pOriginal->LongMargin.getValue())!=0)
	{
		pOriginal->LongMargin.getString(bufOriginal);
		fprintf(fp,"\t\tLongMargin = %s -> %s    [多头占用保证金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLongMargin = %s    [多头占用保证金]\n",buf);
	}
	ShortMargin.getString(buf);
	if (compare(ShortMargin.getValue(),pOriginal->ShortMargin.getValue())!=0)
	{
		pOriginal->ShortMargin.getString(bufOriginal);
		fprintf(fp,"\t\tShortMargin = %s -> %s    [空头占用保证金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tShortMargin = %s    [空头占用保证金]\n",buf);
	}
	LongFrozenMargin.getString(buf);
	if (compare(LongFrozenMargin.getValue(),pOriginal->LongFrozenMargin.getValue())!=0)
	{
		pOriginal->LongFrozenMargin.getString(bufOriginal);
		fprintf(fp,"\t\tLongFrozenMargin = %s -> %s    [多头冻结的保证金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLongFrozenMargin = %s    [多头冻结的保证金]\n",buf);
	}
	ShortFrozenMargin.getString(buf);
	if (compare(ShortFrozenMargin.getValue(),pOriginal->ShortFrozenMargin.getValue())!=0)
	{
		pOriginal->ShortFrozenMargin.getString(bufOriginal);
		fprintf(fp,"\t\tShortFrozenMargin = %s -> %s    [空头冻结的保证金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tShortFrozenMargin = %s    [空头冻结的保证金]\n",buf);
	}
	DynamicRights.getString(buf);
	if (compare(DynamicRights.getValue(),pOriginal->DynamicRights.getValue())!=0)
	{
		pOriginal->DynamicRights.getString(bufOriginal);
		fprintf(fp,"\t\tDynamicRights = %s -> %s    [动态权益]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDynamicRights = %s    [动态权益]\n",buf);
	}
	Risk.getString(buf);
	if (compare(Risk.getValue(),pOriginal->Risk.getValue())!=0)
	{
		pOriginal->Risk.getString(bufOriginal);
		fprintf(fp,"\t\tRisk = %s -> %s    [风险度]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tRisk = %s    [风险度]\n",buf);
	}
	OtherFee.getString(buf);
	if (compare(OtherFee.getValue(),pOriginal->OtherFee.getValue())!=0)
	{
		pOriginal->OtherFee.getString(bufOriginal);
		fprintf(fp,"\t\tOtherFee = %s -> %s    [其他费用]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOtherFee = %s    [其他费用]\n",buf);
	}
	Mortgage.getString(buf);
	if (compare(Mortgage.getValue(),pOriginal->Mortgage.getValue())!=0)
	{
		pOriginal->Mortgage.getString(bufOriginal);
		fprintf(fp,"\t\tMortgage = %s -> %s    [质押金额]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMortgage = %s    [质押金额]\n",buf);
	}
	Currency.getString(buf);
	if (compare(Currency.getValue(),pOriginal->Currency.getValue())!=0)
	{
		pOriginal->Currency.getString(bufOriginal);
		fprintf(fp,"\t\tCurrency = %s -> %s    [币种]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCurrency = %s    [币种]\n",buf);
	}
	TotalFrozenPos.getString(buf);
	if (compare(TotalFrozenPos.getValue(),pOriginal->TotalFrozenPos.getValue())!=0)
	{
		pOriginal->TotalFrozenPos.getString(bufOriginal);
		fprintf(fp,"\t\tTotalFrozenPos = %s -> %s    [总冻结持仓]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTotalFrozenPos = %s    [总冻结持仓]\n",buf);
	}
	TodayInOut.getString(buf);
	if (compare(TodayInOut.getValue(),pOriginal->TodayInOut.getValue())!=0)
	{
		pOriginal->TodayInOut.getString(bufOriginal);
		fprintf(fp,"\t\tTodayInOut = %s -> %s    [今日出入金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTodayInOut = %s    [今日出入金]\n",buf);
	}
	ReleaseMargin.getString(buf);
	if (compare(ReleaseMargin.getValue(),pOriginal->ReleaseMargin.getValue())!=0)
	{
		pOriginal->ReleaseMargin.getString(bufOriginal);
		fprintf(fp,"\t\tReleaseMargin = %s -> %s    [当日释放保证金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tReleaseMargin = %s    [当日释放保证金]\n",buf);
	}
	IsProfitCanUse.getString(buf);
	if (compare(IsProfitCanUse.getValue(),pOriginal->IsProfitCanUse.getValue())!=0)
	{
		pOriginal->IsProfitCanUse.getString(bufOriginal);
		fprintf(fp,"\t\tIsProfitCanUse = %s -> %s    [浮盈是否可用]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIsProfitCanUse = %s    [浮盈是否可用]\n",buf);
	}
	ManualFrozen.getString(buf);
	if (compare(ManualFrozen.getValue(),pOriginal->ManualFrozen.getValue())!=0)
	{
		pOriginal->ManualFrozen.getString(bufOriginal);
		fprintf(fp,"\t\tManualFrozen = %s -> %s    [临时冻结资金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tManualFrozen = %s    [临时冻结资金]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableInvestorAccount::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	AccountID.getString(buf);
	fprintf(fp,",AccountID,%s",buf);	
	PreBalance.getString(buf);
	fprintf(fp,",PreBalance,%s",buf);	
	PreAvailable.getString(buf);
	fprintf(fp,",PreAvailable,%s",buf);	
	Deposit.getString(buf);
	fprintf(fp,",Deposit,%s",buf);	
	Withdraw.getString(buf);
	fprintf(fp,",Withdraw,%s",buf);	
	Margin.getString(buf);
	fprintf(fp,",Margin,%s",buf);	
	Premium.getString(buf);
	fprintf(fp,",Premium,%s",buf);	
	Fee.getString(buf);
	fprintf(fp,",Fee,%s",buf);	
	FrozenMargin.getString(buf);
	fprintf(fp,",FrozenMargin,%s",buf);	
	FrozenPremium.getString(buf);
	fprintf(fp,",FrozenPremium,%s",buf);	
	FrozenFee.getString(buf);
	fprintf(fp,",FrozenFee,%s",buf);	
	CloseProfit.getString(buf);
	fprintf(fp,",CloseProfit,%s",buf);	
	PositionProfit.getString(buf);
	fprintf(fp,",PositionProfit,%s",buf);	
	Available.getString(buf);
	fprintf(fp,",Available,%s",buf);	
	Balance.getString(buf);
	fprintf(fp,",Balance,%s",buf);	
	LongMargin.getString(buf);
	fprintf(fp,",LongMargin,%s",buf);	
	ShortMargin.getString(buf);
	fprintf(fp,",ShortMargin,%s",buf);	
	LongFrozenMargin.getString(buf);
	fprintf(fp,",LongFrozenMargin,%s",buf);	
	ShortFrozenMargin.getString(buf);
	fprintf(fp,",ShortFrozenMargin,%s",buf);	
	DynamicRights.getString(buf);
	fprintf(fp,",DynamicRights,%s",buf);	
	Risk.getString(buf);
	fprintf(fp,",Risk,%s",buf);	
	OtherFee.getString(buf);
	fprintf(fp,",OtherFee,%s",buf);	
	Mortgage.getString(buf);
	fprintf(fp,",Mortgage,%s",buf);	
	Currency.getString(buf);
	fprintf(fp,",Currency,%s",buf);	
	TotalFrozenPos.getString(buf);
	fprintf(fp,",TotalFrozenPos,%s",buf);	
	TodayInOut.getString(buf);
	fprintf(fp,",TodayInOut,%s",buf);	
	ReleaseMargin.getString(buf);
	fprintf(fp,",ReleaseMargin,%s",buf);	
	IsProfitCanUse.getString(buf);
	fprintf(fp,",IsProfitCanUse,%s",buf);	
	ManualFrozen.getString(buf);
	fprintf(fp,",ManualFrozen,%s",buf);	
}

void CWriteableInvestorAccount::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	AccountID.getString(buf);
	sprintf(p,"AccountID=%s,",buf);
	p+=strlen(p);
	PreBalance.getString(buf);
	sprintf(p,"PreBalance=%s,",buf);
	p+=strlen(p);
	PreAvailable.getString(buf);
	sprintf(p,"PreAvailable=%s,",buf);
	p+=strlen(p);
	Deposit.getString(buf);
	sprintf(p,"Deposit=%s,",buf);
	p+=strlen(p);
	Withdraw.getString(buf);
	sprintf(p,"Withdraw=%s,",buf);
	p+=strlen(p);
	Margin.getString(buf);
	sprintf(p,"Margin=%s,",buf);
	p+=strlen(p);
	Premium.getString(buf);
	sprintf(p,"Premium=%s,",buf);
	p+=strlen(p);
	Fee.getString(buf);
	sprintf(p,"Fee=%s,",buf);
	p+=strlen(p);
	FrozenMargin.getString(buf);
	sprintf(p,"FrozenMargin=%s,",buf);
	p+=strlen(p);
	FrozenPremium.getString(buf);
	sprintf(p,"FrozenPremium=%s,",buf);
	p+=strlen(p);
	FrozenFee.getString(buf);
	sprintf(p,"FrozenFee=%s,",buf);
	p+=strlen(p);
	CloseProfit.getString(buf);
	sprintf(p,"CloseProfit=%s,",buf);
	p+=strlen(p);
	PositionProfit.getString(buf);
	sprintf(p,"PositionProfit=%s,",buf);
	p+=strlen(p);
	Available.getString(buf);
	sprintf(p,"Available=%s,",buf);
	p+=strlen(p);
	Balance.getString(buf);
	sprintf(p,"Balance=%s,",buf);
	p+=strlen(p);
	LongMargin.getString(buf);
	sprintf(p,"LongMargin=%s,",buf);
	p+=strlen(p);
	ShortMargin.getString(buf);
	sprintf(p,"ShortMargin=%s,",buf);
	p+=strlen(p);
	LongFrozenMargin.getString(buf);
	sprintf(p,"LongFrozenMargin=%s,",buf);
	p+=strlen(p);
	ShortFrozenMargin.getString(buf);
	sprintf(p,"ShortFrozenMargin=%s,",buf);
	p+=strlen(p);
	DynamicRights.getString(buf);
	sprintf(p,"DynamicRights=%s,",buf);
	p+=strlen(p);
	Risk.getString(buf);
	sprintf(p,"Risk=%s,",buf);
	p+=strlen(p);
	OtherFee.getString(buf);
	sprintf(p,"OtherFee=%s,",buf);
	p+=strlen(p);
	Mortgage.getString(buf);
	sprintf(p,"Mortgage=%s,",buf);
	p+=strlen(p);
	Currency.getString(buf);
	sprintf(p,"Currency=%s,",buf);
	p+=strlen(p);
	TotalFrozenPos.getString(buf);
	sprintf(p,"TotalFrozenPos=%s,",buf);
	p+=strlen(p);
	TodayInOut.getString(buf);
	sprintf(p,"TodayInOut=%s,",buf);
	p+=strlen(p);
	ReleaseMargin.getString(buf);
	sprintf(p,"ReleaseMargin=%s,",buf);
	p+=strlen(p);
	IsProfitCanUse.getString(buf);
	sprintf(p,"IsProfitCanUse=%s,",buf);
	p+=strlen(p);
	ManualFrozen.getString(buf);
	sprintf(p,"ManualFrozen=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableInvestorAccount::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CInvestorAccount");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编号",buf);
	AccountID.getString(buf);
	pLogger->output(indent+1,0,"AccountID=%s 资金帐号",buf);
	PreBalance.getString(buf);
	pLogger->output(indent+1,0,"PreBalance=%s 上次结算准备金",buf);
	PreAvailable.getString(buf);
	pLogger->output(indent+1,0,"PreAvailable=%s 上日可用资金",buf);
	Deposit.getString(buf);
	pLogger->output(indent+1,0,"Deposit=%s 入金金额",buf);
	Withdraw.getString(buf);
	pLogger->output(indent+1,0,"Withdraw=%s 出金金额",buf);
	Margin.getString(buf);
	pLogger->output(indent+1,0,"Margin=%s 占用保证金",buf);
	Premium.getString(buf);
	pLogger->output(indent+1,0,"Premium=%s 期权权利金收支",buf);
	Fee.getString(buf);
	pLogger->output(indent+1,0,"Fee=%s 手续费",buf);
	FrozenMargin.getString(buf);
	pLogger->output(indent+1,0,"FrozenMargin=%s 冻结的保证金",buf);
	FrozenPremium.getString(buf);
	pLogger->output(indent+1,0,"FrozenPremium=%s 冻结权利金",buf);
	FrozenFee.getString(buf);
	pLogger->output(indent+1,0,"FrozenFee=%s 冻结手续费",buf);
	CloseProfit.getString(buf);
	pLogger->output(indent+1,0,"CloseProfit=%s 平仓盈亏",buf);
	PositionProfit.getString(buf);
	pLogger->output(indent+1,0,"PositionProfit=%s 持仓盈亏",buf);
	Available.getString(buf);
	pLogger->output(indent+1,0,"Available=%s 可用资金",buf);
	Balance.getString(buf);
	pLogger->output(indent+1,0,"Balance=%s 结算准备金",buf);
	LongMargin.getString(buf);
	pLogger->output(indent+1,0,"LongMargin=%s 多头占用保证金",buf);
	ShortMargin.getString(buf);
	pLogger->output(indent+1,0,"ShortMargin=%s 空头占用保证金",buf);
	LongFrozenMargin.getString(buf);
	pLogger->output(indent+1,0,"LongFrozenMargin=%s 多头冻结的保证金",buf);
	ShortFrozenMargin.getString(buf);
	pLogger->output(indent+1,0,"ShortFrozenMargin=%s 空头冻结的保证金",buf);
	DynamicRights.getString(buf);
	pLogger->output(indent+1,0,"DynamicRights=%s 动态权益",buf);
	Risk.getString(buf);
	pLogger->output(indent+1,0,"Risk=%s 风险度",buf);
	OtherFee.getString(buf);
	pLogger->output(indent+1,0,"OtherFee=%s 其他费用",buf);
	Mortgage.getString(buf);
	pLogger->output(indent+1,0,"Mortgage=%s 质押金额",buf);
	Currency.getString(buf);
	pLogger->output(indent+1,0,"Currency=%s 币种",buf);
	TotalFrozenPos.getString(buf);
	pLogger->output(indent+1,0,"TotalFrozenPos=%s 总冻结持仓",buf);
	TodayInOut.getString(buf);
	pLogger->output(indent+1,0,"TodayInOut=%s 今日出入金",buf);
	ReleaseMargin.getString(buf);
	pLogger->output(indent+1,0,"ReleaseMargin=%s 当日释放保证金",buf);
	IsProfitCanUse.getString(buf);
	pLogger->output(indent+1,0,"IsProfitCanUse=%s 浮盈是否可用",buf);
	ManualFrozen.getString(buf);
	pLogger->output(indent+1,0,"ManualFrozen=%s 临时冻结资金",buf);
	pLogger->output(indent,0,"}");
}

CInvestorAccountIterator::~CInvestorAccountIterator(void)
{
}


void CInvestorAccountIterator::dump(FILE *output)
{
	CInvestorAccount *pInvestorAccount;
	
	while ((pInvestorAccount=next())!=NULL)
	{
		pInvestorAccount->dump(output);
	}
}



void CWriteableInvestorAccountDeposit::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,AccountSeqNo,AccountID,AccountInsideSeqNo,InvestorID,Amount,AmountDirection\n");
}
	
void CWriteableInvestorAccountDeposit::init(void)
{
	BrokerID.clear();
	AccountSeqNo.clear();
	AccountID.clear();
	AccountInsideSeqNo.clear();
	InvestorID.clear();
	Amount.clear();
	AmountDirection.clear();
}

int CWriteableInvestorAccountDeposit::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableInvestorAccountDeposit),input)!=sizeof(CWriteableInvestorAccountDeposit))
		return 0;
	else
		return 1;
}
	
int CWriteableInvestorAccountDeposit::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			AccountSeqNo=token;
		}
		else
		{
			AccountSeqNo="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			AccountID=token;
		}
		else
		{
			AccountID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			AccountInsideSeqNo=token;
		}
		else
		{
			AccountInsideSeqNo="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Amount=token;
		}
		else
		{
			Amount="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			AmountDirection=token;
		}
		else
		{
			AmountDirection="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"AccountSeqNo"))
			{
				AccountSeqNo=token;
			}
			else if (!strcmp(fieldName,"AccountID"))
			{
				AccountID=token;
			}
			else if (!strcmp(fieldName,"AccountInsideSeqNo"))
			{
				AccountInsideSeqNo=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"Amount"))
			{
				Amount=token;
			}
			else if (!strcmp(fieldName,"AmountDirection"))
			{
				AmountDirection=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableInvestorAccountDeposit::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableInvestorAccountDeposit),output)!=sizeof(CWriteableInvestorAccountDeposit))
		return 0;
	else
		return 1;
}

int CWriteableInvestorAccountDeposit::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	AccountSeqNo.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	AccountID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	AccountInsideSeqNo.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Amount.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	AmountDirection.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableInvestorAccountDeposit::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCInvestorAccountDeposit%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	AccountSeqNo.getString(buf);
	fprintf(fp,"\t\tAccountSeqNo = %s    [资金流水号]\n",buf);	
	AccountID.getString(buf);
	fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);	
	AccountInsideSeqNo.getString(buf);
	fprintf(fp,"\t\tAccountInsideSeqNo = %s    [连续递增的总资金流水号]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);	
	Amount.getString(buf);
	fprintf(fp,"\t\tAmount = %s    [金额]\n",buf);	
	AmountDirection.getString(buf);
	fprintf(fp,"\t\tAmountDirection = %s    [出入金方向]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableInvestorAccountDeposit::dumpDiff(FILE *fp, const CWriteableInvestorAccountDeposit *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCInvestorAccountDeposit = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	AccountSeqNo.getString(buf);
	if (compare(AccountSeqNo.getValue(),pOriginal->AccountSeqNo.getValue())!=0)
	{
		pOriginal->AccountSeqNo.getString(bufOriginal);
		fprintf(fp,"\t\tAccountSeqNo = %s -> %s    [资金流水号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAccountSeqNo = %s    [资金流水号]\n",buf);
	}
	AccountID.getString(buf);
	if (compare(AccountID.getValue(),pOriginal->AccountID.getValue())!=0)
	{
		pOriginal->AccountID.getString(bufOriginal);
		fprintf(fp,"\t\tAccountID = %s -> %s    [资金帐号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);
	}
	AccountInsideSeqNo.getString(buf);
	if (compare(AccountInsideSeqNo.getValue(),pOriginal->AccountInsideSeqNo.getValue())!=0)
	{
		pOriginal->AccountInsideSeqNo.getString(bufOriginal);
		fprintf(fp,"\t\tAccountInsideSeqNo = %s -> %s    [连续递增的总资金流水号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAccountInsideSeqNo = %s    [连续递增的总资金流水号]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);
	}
	Amount.getString(buf);
	if (compare(Amount.getValue(),pOriginal->Amount.getValue())!=0)
	{
		pOriginal->Amount.getString(bufOriginal);
		fprintf(fp,"\t\tAmount = %s -> %s    [金额]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAmount = %s    [金额]\n",buf);
	}
	AmountDirection.getString(buf);
	if (compare(AmountDirection.getValue(),pOriginal->AmountDirection.getValue())!=0)
	{
		pOriginal->AmountDirection.getString(bufOriginal);
		fprintf(fp,"\t\tAmountDirection = %s -> %s    [出入金方向]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAmountDirection = %s    [出入金方向]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableInvestorAccountDeposit::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	AccountSeqNo.getString(buf);
	fprintf(fp,",AccountSeqNo,%s",buf);	
	AccountID.getString(buf);
	fprintf(fp,",AccountID,%s",buf);	
	AccountInsideSeqNo.getString(buf);
	fprintf(fp,",AccountInsideSeqNo,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	Amount.getString(buf);
	fprintf(fp,",Amount,%s",buf);	
	AmountDirection.getString(buf);
	fprintf(fp,",AmountDirection,%s",buf);	
}

void CWriteableInvestorAccountDeposit::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	AccountSeqNo.getString(buf);
	sprintf(p,"AccountSeqNo=%s,",buf);
	p+=strlen(p);
	AccountID.getString(buf);
	sprintf(p,"AccountID=%s,",buf);
	p+=strlen(p);
	AccountInsideSeqNo.getString(buf);
	sprintf(p,"AccountInsideSeqNo=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	Amount.getString(buf);
	sprintf(p,"Amount=%s,",buf);
	p+=strlen(p);
	AmountDirection.getString(buf);
	sprintf(p,"AmountDirection=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableInvestorAccountDeposit::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CInvestorAccountDeposit");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	AccountSeqNo.getString(buf);
	pLogger->output(indent+1,0,"AccountSeqNo=%s 资金流水号",buf);
	AccountID.getString(buf);
	pLogger->output(indent+1,0,"AccountID=%s 资金帐号",buf);
	AccountInsideSeqNo.getString(buf);
	pLogger->output(indent+1,0,"AccountInsideSeqNo=%s 连续递增的总资金流水号",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编号",buf);
	Amount.getString(buf);
	pLogger->output(indent+1,0,"Amount=%s 金额",buf);
	AmountDirection.getString(buf);
	pLogger->output(indent+1,0,"AmountDirection=%s 出入金方向",buf);
	pLogger->output(indent,0,"}");
}

CInvestorAccountDepositIterator::~CInvestorAccountDepositIterator(void)
{
}


void CInvestorAccountDepositIterator::dump(FILE *output)
{
	CInvestorAccountDeposit *pInvestorAccountDeposit;
	
	while ((pInvestorAccountDeposit=next())!=NULL)
	{
		pInvestorAccountDeposit->dump(output);
	}
}



void CWriteableExchange::writeCSVHead(FILE *output)
{
	fprintf(output,"TradingDay,ExchangeID,ExchangeName\n");
}
	
void CWriteableExchange::init(void)
{
	TradingDay.clear();
	ExchangeID.clear();
	ExchangeName.clear();
}

int CWriteableExchange::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableExchange),input)!=sizeof(CWriteableExchange))
		return 0;
	else
		return 1;
}
	
int CWriteableExchange::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			TradingDay=token;
		}
		else
		{
			TradingDay="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeName=token;
		}
		else
		{
			ExchangeName="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"TradingDay"))
			{
				TradingDay=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"ExchangeName"))
			{
				ExchangeName=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableExchange::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableExchange),output)!=sizeof(CWriteableExchange))
		return 0;
	else
		return 1;
}

int CWriteableExchange::writeCSV(FILE *output) const
{
	char buffer[1025];
	TradingDay.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeName.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableExchange::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCExchange%s = {\n", index_buf);
	TradingDay.getString(buf);
	fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	ExchangeName.getString(buf);
	fprintf(fp,"\t\tExchangeName = %s    [交易所名称]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableExchange::dumpDiff(FILE *fp, const CWriteableExchange *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCExchange = {\n");
	TradingDay.getString(buf);
	if (compare(TradingDay.getValue(),pOriginal->TradingDay.getValue())!=0)
	{
		pOriginal->TradingDay.getString(bufOriginal);
		fprintf(fp,"\t\tTradingDay = %s -> %s    [交易日]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	ExchangeName.getString(buf);
	if (compare(ExchangeName.getValue(),pOriginal->ExchangeName.getValue())!=0)
	{
		pOriginal->ExchangeName.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeName = %s -> %s    [交易所名称]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeName = %s    [交易所名称]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableExchange::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	TradingDay.getString(buf);
	fprintf(fp,",TradingDay,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	ExchangeName.getString(buf);
	fprintf(fp,",ExchangeName,%s",buf);	
}

void CWriteableExchange::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	TradingDay.getString(buf);
	sprintf(p,"TradingDay=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	ExchangeName.getString(buf);
	sprintf(p,"ExchangeName=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableExchange::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CExchange");
	pLogger->output(indent,0,"{");
	TradingDay.getString(buf);
	pLogger->output(indent+1,0,"TradingDay=%s 交易日",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	ExchangeName.getString(buf);
	pLogger->output(indent+1,0,"ExchangeName=%s 交易所名称",buf);
	pLogger->output(indent,0,"}");
}

CExchangeIterator::~CExchangeIterator(void)
{
}


void CExchangeIterator::dump(FILE *output)
{
	CExchange *pExchange;
	
	while ((pExchange=next())!=NULL)
	{
		pExchange->dump(output);
	}
}



void CWriteableSeat::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,APIID,ExchangeID,ParticipantID,SeatID,SeatPassword,ApiLinkType,RecvRtn,MainSeat,QueryBase,QueryPosition,ResumeType,Heartbeat,IsActive,RiskCheck,FrontAddr,SeatStatus,OrderLocalID,LinkBrokerID,TradingDay,CheckTradingDay,Custom\n");
}
	
void CWriteableSeat::init(void)
{
	BrokerID.clear();
	APIID.clear();
	ExchangeID.clear();
	ParticipantID.clear();
	SeatID.clear();
	SeatPassword.clear();
	ApiLinkType.clear();
	RecvRtn.clear();
	MainSeat.clear();
	QueryBase.clear();
	QueryPosition.clear();
	ResumeType.clear();
	Heartbeat.clear();
	IsActive.clear();
	RiskCheck.clear();
	FrontAddr.clear();
	SeatStatus.clear();
	OrderLocalID.clear();
	LinkBrokerID.clear();
	TradingDay.clear();
	CheckTradingDay.clear();
	Custom.clear();
}

int CWriteableSeat::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableSeat),input)!=sizeof(CWriteableSeat))
		return 0;
	else
		return 1;
}
	
int CWriteableSeat::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			APIID=token;
		}
		else
		{
			APIID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ParticipantID=token;
		}
		else
		{
			ParticipantID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SeatID=token;
		}
		else
		{
			SeatID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SeatPassword=token;
		}
		else
		{
			SeatPassword="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ApiLinkType=token;
		}
		else
		{
			ApiLinkType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			RecvRtn=token;
		}
		else
		{
			RecvRtn="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MainSeat=token;
		}
		else
		{
			MainSeat="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			QueryBase=token;
		}
		else
		{
			QueryBase="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			QueryPosition=token;
		}
		else
		{
			QueryPosition="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ResumeType=token;
		}
		else
		{
			ResumeType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Heartbeat=token;
		}
		else
		{
			Heartbeat="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IsActive=token;
		}
		else
		{
			IsActive="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			RiskCheck=token;
		}
		else
		{
			RiskCheck="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrontAddr=token;
		}
		else
		{
			FrontAddr="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SeatStatus=token;
		}
		else
		{
			SeatStatus="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderLocalID=token;
		}
		else
		{
			OrderLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LinkBrokerID=token;
		}
		else
		{
			LinkBrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradingDay=token;
		}
		else
		{
			TradingDay="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CheckTradingDay=token;
		}
		else
		{
			CheckTradingDay="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Custom=token;
		}
		else
		{
			Custom="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"APIID"))
			{
				APIID=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"ParticipantID"))
			{
				ParticipantID=token;
			}
			else if (!strcmp(fieldName,"SeatID"))
			{
				SeatID=token;
			}
			else if (!strcmp(fieldName,"SeatPassword"))
			{
				SeatPassword=token;
			}
			else if (!strcmp(fieldName,"ApiLinkType"))
			{
				ApiLinkType=token;
			}
			else if (!strcmp(fieldName,"RecvRtn"))
			{
				RecvRtn=token;
			}
			else if (!strcmp(fieldName,"MainSeat"))
			{
				MainSeat=token;
			}
			else if (!strcmp(fieldName,"QueryBase"))
			{
				QueryBase=token;
			}
			else if (!strcmp(fieldName,"QueryPosition"))
			{
				QueryPosition=token;
			}
			else if (!strcmp(fieldName,"ResumeType"))
			{
				ResumeType=token;
			}
			else if (!strcmp(fieldName,"Heartbeat"))
			{
				Heartbeat=token;
			}
			else if (!strcmp(fieldName,"IsActive"))
			{
				IsActive=token;
			}
			else if (!strcmp(fieldName,"RiskCheck"))
			{
				RiskCheck=token;
			}
			else if (!strcmp(fieldName,"FrontAddr"))
			{
				FrontAddr=token;
			}
			else if (!strcmp(fieldName,"SeatStatus"))
			{
				SeatStatus=token;
			}
			else if (!strcmp(fieldName,"OrderLocalID"))
			{
				OrderLocalID=token;
			}
			else if (!strcmp(fieldName,"LinkBrokerID"))
			{
				LinkBrokerID=token;
			}
			else if (!strcmp(fieldName,"TradingDay"))
			{
				TradingDay=token;
			}
			else if (!strcmp(fieldName,"CheckTradingDay"))
			{
				CheckTradingDay=token;
			}
			else if (!strcmp(fieldName,"Custom"))
			{
				Custom=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableSeat::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableSeat),output)!=sizeof(CWriteableSeat))
		return 0;
	else
		return 1;
}

int CWriteableSeat::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	APIID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ParticipantID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SeatID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SeatPassword.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ApiLinkType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	RecvRtn.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MainSeat.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	QueryBase.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	QueryPosition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ResumeType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Heartbeat.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IsActive.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	RiskCheck.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrontAddr.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SeatStatus.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LinkBrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradingDay.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CheckTradingDay.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Custom.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableSeat::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCSeat%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	APIID.getString(buf);
	fprintf(fp,"\t\tAPIID = %s    [交易API中的序号]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,"\t\tParticipantID = %s    [会员编号]\n",buf);	
	SeatID.getString(buf);
	fprintf(fp,"\t\tSeatID = %s    [席位号]\n",buf);	
	SeatPassword.getString(buf);
	fprintf(fp,"\t\tSeatPassword = %s    [席位密码]\n",buf);	
	ApiLinkType.getString(buf);
	fprintf(fp,"\t\tApiLinkType = %s    [席位连接api类型]\n",buf);	
	RecvRtn.getString(buf);
	fprintf(fp,"\t\tRecvRtn = %s    [是否接收回报]\n",buf);	
	MainSeat.getString(buf);
	fprintf(fp,"\t\tMainSeat = %s    [席位密码(是否接收所有席位回报)]\n",buf);	
	QueryBase.getString(buf);
	fprintf(fp,"\t\tQueryBase = %s    [是否查询基础信息]\n",buf);	
	QueryPosition.getString(buf);
	fprintf(fp,"\t\tQueryPosition = %s    [是否查询持仓]\n",buf);	
	ResumeType.getString(buf);
	fprintf(fp,"\t\tResumeType = %s    [收取回报的方式]\n",buf);	
	Heartbeat.getString(buf);
	fprintf(fp,"\t\tHeartbeat = %s    [心跳时间(秒)]\n",buf);	
	IsActive.getString(buf);
	fprintf(fp,"\t\tIsActive = %s    [是否活跃]\n",buf);	
	RiskCheck.getString(buf);
	fprintf(fp,"\t\tRiskCheck = %s    [是否检查资金持仓风控]\n",buf);	
	FrontAddr.getString(buf);
	fprintf(fp,"\t\tFrontAddr = %s    [连接地址]\n",buf);	
	SeatStatus.getString(buf);
	fprintf(fp,"\t\tSeatStatus = %s    [席位状态]\n",buf);	
	OrderLocalID.getString(buf);
	fprintf(fp,"\t\tOrderLocalID = %s    [本地报单编号]\n",buf);	
	LinkBrokerID.getString(buf);
	fprintf(fp,"\t\tLinkBrokerID = %s    [连接对应的Broker(guofu/sucden/fcstone)]\n",buf);	
	TradingDay.getString(buf);
	fprintf(fp,"\t\tTradingDay = %s    [需要席位操作的交易日期]\n",buf);	
	CheckTradingDay.getString(buf);
	fprintf(fp,"\t\tCheckTradingDay = %s    [是否需要检查交易日期]\n",buf);	
	Custom.getString(buf);
	fprintf(fp,"\t\tCustom = %s    [报盘自定义的属性]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableSeat::dumpDiff(FILE *fp, const CWriteableSeat *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCSeat = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	APIID.getString(buf);
	if (compare(APIID.getValue(),pOriginal->APIID.getValue())!=0)
	{
		pOriginal->APIID.getString(bufOriginal);
		fprintf(fp,"\t\tAPIID = %s -> %s    [交易API中的序号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAPIID = %s    [交易API中的序号]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	ParticipantID.getString(buf);
	if (compare(ParticipantID.getValue(),pOriginal->ParticipantID.getValue())!=0)
	{
		pOriginal->ParticipantID.getString(bufOriginal);
		fprintf(fp,"\t\tParticipantID = %s -> %s    [会员编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tParticipantID = %s    [会员编号]\n",buf);
	}
	SeatID.getString(buf);
	if (compare(SeatID.getValue(),pOriginal->SeatID.getValue())!=0)
	{
		pOriginal->SeatID.getString(bufOriginal);
		fprintf(fp,"\t\tSeatID = %s -> %s    [席位号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSeatID = %s    [席位号]\n",buf);
	}
	SeatPassword.getString(buf);
	if (compare(SeatPassword.getValue(),pOriginal->SeatPassword.getValue())!=0)
	{
		pOriginal->SeatPassword.getString(bufOriginal);
		fprintf(fp,"\t\tSeatPassword = %s -> %s    [席位密码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSeatPassword = %s    [席位密码]\n",buf);
	}
	ApiLinkType.getString(buf);
	if (compare(ApiLinkType.getValue(),pOriginal->ApiLinkType.getValue())!=0)
	{
		pOriginal->ApiLinkType.getString(bufOriginal);
		fprintf(fp,"\t\tApiLinkType = %s -> %s    [席位连接api类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tApiLinkType = %s    [席位连接api类型]\n",buf);
	}
	RecvRtn.getString(buf);
	if (compare(RecvRtn.getValue(),pOriginal->RecvRtn.getValue())!=0)
	{
		pOriginal->RecvRtn.getString(bufOriginal);
		fprintf(fp,"\t\tRecvRtn = %s -> %s    [是否接收回报]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tRecvRtn = %s    [是否接收回报]\n",buf);
	}
	MainSeat.getString(buf);
	if (compare(MainSeat.getValue(),pOriginal->MainSeat.getValue())!=0)
	{
		pOriginal->MainSeat.getString(bufOriginal);
		fprintf(fp,"\t\tMainSeat = %s -> %s    [席位密码(是否接收所有席位回报)]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMainSeat = %s    [席位密码(是否接收所有席位回报)]\n",buf);
	}
	QueryBase.getString(buf);
	if (compare(QueryBase.getValue(),pOriginal->QueryBase.getValue())!=0)
	{
		pOriginal->QueryBase.getString(bufOriginal);
		fprintf(fp,"\t\tQueryBase = %s -> %s    [是否查询基础信息]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tQueryBase = %s    [是否查询基础信息]\n",buf);
	}
	QueryPosition.getString(buf);
	if (compare(QueryPosition.getValue(),pOriginal->QueryPosition.getValue())!=0)
	{
		pOriginal->QueryPosition.getString(bufOriginal);
		fprintf(fp,"\t\tQueryPosition = %s -> %s    [是否查询持仓]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tQueryPosition = %s    [是否查询持仓]\n",buf);
	}
	ResumeType.getString(buf);
	if (compare(ResumeType.getValue(),pOriginal->ResumeType.getValue())!=0)
	{
		pOriginal->ResumeType.getString(bufOriginal);
		fprintf(fp,"\t\tResumeType = %s -> %s    [收取回报的方式]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tResumeType = %s    [收取回报的方式]\n",buf);
	}
	Heartbeat.getString(buf);
	if (compare(Heartbeat.getValue(),pOriginal->Heartbeat.getValue())!=0)
	{
		pOriginal->Heartbeat.getString(bufOriginal);
		fprintf(fp,"\t\tHeartbeat = %s -> %s    [心跳时间(秒)]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tHeartbeat = %s    [心跳时间(秒)]\n",buf);
	}
	IsActive.getString(buf);
	if (compare(IsActive.getValue(),pOriginal->IsActive.getValue())!=0)
	{
		pOriginal->IsActive.getString(bufOriginal);
		fprintf(fp,"\t\tIsActive = %s -> %s    [是否活跃]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIsActive = %s    [是否活跃]\n",buf);
	}
	RiskCheck.getString(buf);
	if (compare(RiskCheck.getValue(),pOriginal->RiskCheck.getValue())!=0)
	{
		pOriginal->RiskCheck.getString(bufOriginal);
		fprintf(fp,"\t\tRiskCheck = %s -> %s    [是否检查资金持仓风控]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tRiskCheck = %s    [是否检查资金持仓风控]\n",buf);
	}
	FrontAddr.getString(buf);
	if (compare(FrontAddr.getValue(),pOriginal->FrontAddr.getValue())!=0)
	{
		pOriginal->FrontAddr.getString(bufOriginal);
		fprintf(fp,"\t\tFrontAddr = %s -> %s    [连接地址]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrontAddr = %s    [连接地址]\n",buf);
	}
	SeatStatus.getString(buf);
	if (compare(SeatStatus.getValue(),pOriginal->SeatStatus.getValue())!=0)
	{
		pOriginal->SeatStatus.getString(bufOriginal);
		fprintf(fp,"\t\tSeatStatus = %s -> %s    [席位状态]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSeatStatus = %s    [席位状态]\n",buf);
	}
	OrderLocalID.getString(buf);
	if (compare(OrderLocalID.getValue(),pOriginal->OrderLocalID.getValue())!=0)
	{
		pOriginal->OrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderLocalID = %s -> %s    [本地报单编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderLocalID = %s    [本地报单编号]\n",buf);
	}
	LinkBrokerID.getString(buf);
	if (compare(LinkBrokerID.getValue(),pOriginal->LinkBrokerID.getValue())!=0)
	{
		pOriginal->LinkBrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tLinkBrokerID = %s -> %s    [连接对应的Broker(guofu/sucden/fcstone)]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLinkBrokerID = %s    [连接对应的Broker(guofu/sucden/fcstone)]\n",buf);
	}
	TradingDay.getString(buf);
	if (compare(TradingDay.getValue(),pOriginal->TradingDay.getValue())!=0)
	{
		pOriginal->TradingDay.getString(bufOriginal);
		fprintf(fp,"\t\tTradingDay = %s -> %s    [需要席位操作的交易日期]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradingDay = %s    [需要席位操作的交易日期]\n",buf);
	}
	CheckTradingDay.getString(buf);
	if (compare(CheckTradingDay.getValue(),pOriginal->CheckTradingDay.getValue())!=0)
	{
		pOriginal->CheckTradingDay.getString(bufOriginal);
		fprintf(fp,"\t\tCheckTradingDay = %s -> %s    [是否需要检查交易日期]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCheckTradingDay = %s    [是否需要检查交易日期]\n",buf);
	}
	Custom.getString(buf);
	if (compare(Custom.getValue(),pOriginal->Custom.getValue())!=0)
	{
		pOriginal->Custom.getString(bufOriginal);
		fprintf(fp,"\t\tCustom = %s -> %s    [报盘自定义的属性]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCustom = %s    [报盘自定义的属性]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableSeat::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	APIID.getString(buf);
	fprintf(fp,",APIID,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,",ParticipantID,%s",buf);	
	SeatID.getString(buf);
	fprintf(fp,",SeatID,%s",buf);	
	SeatPassword.getString(buf);
	fprintf(fp,",SeatPassword,%s",buf);	
	ApiLinkType.getString(buf);
	fprintf(fp,",ApiLinkType,%s",buf);	
	RecvRtn.getString(buf);
	fprintf(fp,",RecvRtn,%s",buf);	
	MainSeat.getString(buf);
	fprintf(fp,",MainSeat,%s",buf);	
	QueryBase.getString(buf);
	fprintf(fp,",QueryBase,%s",buf);	
	QueryPosition.getString(buf);
	fprintf(fp,",QueryPosition,%s",buf);	
	ResumeType.getString(buf);
	fprintf(fp,",ResumeType,%s",buf);	
	Heartbeat.getString(buf);
	fprintf(fp,",Heartbeat,%s",buf);	
	IsActive.getString(buf);
	fprintf(fp,",IsActive,%s",buf);	
	RiskCheck.getString(buf);
	fprintf(fp,",RiskCheck,%s",buf);	
	FrontAddr.getString(buf);
	fprintf(fp,",FrontAddr,%s",buf);	
	SeatStatus.getString(buf);
	fprintf(fp,",SeatStatus,%s",buf);	
	OrderLocalID.getString(buf);
	fprintf(fp,",OrderLocalID,%s",buf);	
	LinkBrokerID.getString(buf);
	fprintf(fp,",LinkBrokerID,%s",buf);	
	TradingDay.getString(buf);
	fprintf(fp,",TradingDay,%s",buf);	
	CheckTradingDay.getString(buf);
	fprintf(fp,",CheckTradingDay,%s",buf);	
	Custom.getString(buf);
	fprintf(fp,",Custom,%s",buf);	
}

void CWriteableSeat::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	APIID.getString(buf);
	sprintf(p,"APIID=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	ParticipantID.getString(buf);
	sprintf(p,"ParticipantID=%s,",buf);
	p+=strlen(p);
	SeatID.getString(buf);
	sprintf(p,"SeatID=%s,",buf);
	p+=strlen(p);
	SeatPassword.getString(buf);
	sprintf(p,"SeatPassword=%s,",buf);
	p+=strlen(p);
	ApiLinkType.getString(buf);
	sprintf(p,"ApiLinkType=%s,",buf);
	p+=strlen(p);
	RecvRtn.getString(buf);
	sprintf(p,"RecvRtn=%s,",buf);
	p+=strlen(p);
	MainSeat.getString(buf);
	sprintf(p,"MainSeat=%s,",buf);
	p+=strlen(p);
	QueryBase.getString(buf);
	sprintf(p,"QueryBase=%s,",buf);
	p+=strlen(p);
	QueryPosition.getString(buf);
	sprintf(p,"QueryPosition=%s,",buf);
	p+=strlen(p);
	ResumeType.getString(buf);
	sprintf(p,"ResumeType=%s,",buf);
	p+=strlen(p);
	Heartbeat.getString(buf);
	sprintf(p,"Heartbeat=%s,",buf);
	p+=strlen(p);
	IsActive.getString(buf);
	sprintf(p,"IsActive=%s,",buf);
	p+=strlen(p);
	RiskCheck.getString(buf);
	sprintf(p,"RiskCheck=%s,",buf);
	p+=strlen(p);
	FrontAddr.getString(buf);
	sprintf(p,"FrontAddr=%s,",buf);
	p+=strlen(p);
	SeatStatus.getString(buf);
	sprintf(p,"SeatStatus=%s,",buf);
	p+=strlen(p);
	OrderLocalID.getString(buf);
	sprintf(p,"OrderLocalID=%s,",buf);
	p+=strlen(p);
	LinkBrokerID.getString(buf);
	sprintf(p,"LinkBrokerID=%s,",buf);
	p+=strlen(p);
	TradingDay.getString(buf);
	sprintf(p,"TradingDay=%s,",buf);
	p+=strlen(p);
	CheckTradingDay.getString(buf);
	sprintf(p,"CheckTradingDay=%s,",buf);
	p+=strlen(p);
	Custom.getString(buf);
	sprintf(p,"Custom=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableSeat::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CSeat");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	APIID.getString(buf);
	pLogger->output(indent+1,0,"APIID=%s 交易API中的序号",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	ParticipantID.getString(buf);
	pLogger->output(indent+1,0,"ParticipantID=%s 会员编号",buf);
	SeatID.getString(buf);
	pLogger->output(indent+1,0,"SeatID=%s 席位号",buf);
	SeatPassword.getString(buf);
	pLogger->output(indent+1,0,"SeatPassword=%s 席位密码",buf);
	ApiLinkType.getString(buf);
	pLogger->output(indent+1,0,"ApiLinkType=%s 席位连接api类型",buf);
	RecvRtn.getString(buf);
	pLogger->output(indent+1,0,"RecvRtn=%s 是否接收回报",buf);
	MainSeat.getString(buf);
	pLogger->output(indent+1,0,"MainSeat=%s 席位密码(是否接收所有席位回报)",buf);
	QueryBase.getString(buf);
	pLogger->output(indent+1,0,"QueryBase=%s 是否查询基础信息",buf);
	QueryPosition.getString(buf);
	pLogger->output(indent+1,0,"QueryPosition=%s 是否查询持仓",buf);
	ResumeType.getString(buf);
	pLogger->output(indent+1,0,"ResumeType=%s 收取回报的方式",buf);
	Heartbeat.getString(buf);
	pLogger->output(indent+1,0,"Heartbeat=%s 心跳时间(秒)",buf);
	IsActive.getString(buf);
	pLogger->output(indent+1,0,"IsActive=%s 是否活跃",buf);
	RiskCheck.getString(buf);
	pLogger->output(indent+1,0,"RiskCheck=%s 是否检查资金持仓风控",buf);
	FrontAddr.getString(buf);
	pLogger->output(indent+1,0,"FrontAddr=%s 连接地址",buf);
	SeatStatus.getString(buf);
	pLogger->output(indent+1,0,"SeatStatus=%s 席位状态",buf);
	OrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"OrderLocalID=%s 本地报单编号",buf);
	LinkBrokerID.getString(buf);
	pLogger->output(indent+1,0,"LinkBrokerID=%s 连接对应的Broker(guofu/sucden/fcstone)",buf);
	TradingDay.getString(buf);
	pLogger->output(indent+1,0,"TradingDay=%s 需要席位操作的交易日期",buf);
	CheckTradingDay.getString(buf);
	pLogger->output(indent+1,0,"CheckTradingDay=%s 是否需要检查交易日期",buf);
	Custom.getString(buf);
	pLogger->output(indent+1,0,"Custom=%s 报盘自定义的属性",buf);
	pLogger->output(indent,0,"}");
}

CSeatIterator::~CSeatIterator(void)
{
}


void CSeatIterator::dump(FILE *output)
{
	CSeat *pSeat;
	
	while ((pSeat=next())!=NULL)
	{
		pSeat->dump(output);
	}
}



void CWriteableInstrument::writeCSVHead(FILE *output)
{
	fprintf(output,"ExchangeID,ProductID,ProductName,InstrumentID,InstrumentName,DeliveryYear,DeliveryMonth,MaxLimitOrderVolume,MinLimitOrderVolume,MaxMarketOrderVolume,MinMarketOrderVolume,VolumeMultiple,PriceTick,Currency,LongPosLimit,ShortPosLimit,LowerLimitPrice,UpperLimitPrice,PreSettlementPrice,InstrumentStatus,CreateDate,OpenDate,ExpireDate,StartDelivDate,EndDelivDate,BasisPrice,IsTrading,UnderlyingInstrID,UnderlyingMultiple,PositionType,StrikePrice,OptionsType,ProductClass,OptionsMode,ProductGroupID,APIID,LegQty\n");
}
	
void CWriteableInstrument::init(void)
{
	ExchangeID.clear();
	ProductID.clear();
	ProductName.clear();
	InstrumentID.clear();
	InstrumentName.clear();
	DeliveryYear.clear();
	DeliveryMonth.clear();
	MaxLimitOrderVolume.clear();
	MinLimitOrderVolume.clear();
	MaxMarketOrderVolume.clear();
	MinMarketOrderVolume.clear();
	VolumeMultiple.clear();
	PriceTick.clear();
	Currency.clear();
	LongPosLimit.clear();
	ShortPosLimit.clear();
	LowerLimitPrice.clear();
	UpperLimitPrice.clear();
	PreSettlementPrice.clear();
	InstrumentStatus.clear();
	CreateDate.clear();
	OpenDate.clear();
	ExpireDate.clear();
	StartDelivDate.clear();
	EndDelivDate.clear();
	BasisPrice.clear();
	IsTrading.clear();
	UnderlyingInstrID.clear();
	UnderlyingMultiple.clear();
	PositionType.clear();
	StrikePrice.clear();
	OptionsType.clear();
	ProductClass.clear();
	OptionsMode.clear();
	ProductGroupID.clear();
	APIID.clear();
	LegQty.clear();
}

int CWriteableInstrument::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableInstrument),input)!=sizeof(CWriteableInstrument))
		return 0;
	else
		return 1;
}
	
int CWriteableInstrument::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ProductID=token;
		}
		else
		{
			ProductID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ProductName=token;
		}
		else
		{
			ProductName="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentName=token;
		}
		else
		{
			InstrumentName="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			DeliveryYear=token;
		}
		else
		{
			DeliveryYear="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			DeliveryMonth=token;
		}
		else
		{
			DeliveryMonth="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MaxLimitOrderVolume=token;
		}
		else
		{
			MaxLimitOrderVolume="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MinLimitOrderVolume=token;
		}
		else
		{
			MinLimitOrderVolume="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MaxMarketOrderVolume=token;
		}
		else
		{
			MaxMarketOrderVolume="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MinMarketOrderVolume=token;
		}
		else
		{
			MinMarketOrderVolume="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			VolumeMultiple=token;
		}
		else
		{
			VolumeMultiple="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			PriceTick=token;
		}
		else
		{
			PriceTick="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Currency=token;
		}
		else
		{
			Currency="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LongPosLimit=token;
		}
		else
		{
			LongPosLimit="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ShortPosLimit=token;
		}
		else
		{
			ShortPosLimit="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LowerLimitPrice=token;
		}
		else
		{
			LowerLimitPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UpperLimitPrice=token;
		}
		else
		{
			UpperLimitPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			PreSettlementPrice=token;
		}
		else
		{
			PreSettlementPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentStatus=token;
		}
		else
		{
			InstrumentStatus="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CreateDate=token;
		}
		else
		{
			CreateDate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OpenDate=token;
		}
		else
		{
			OpenDate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExpireDate=token;
		}
		else
		{
			ExpireDate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			StartDelivDate=token;
		}
		else
		{
			StartDelivDate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			EndDelivDate=token;
		}
		else
		{
			EndDelivDate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			BasisPrice=token;
		}
		else
		{
			BasisPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IsTrading=token;
		}
		else
		{
			IsTrading="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UnderlyingInstrID=token;
		}
		else
		{
			UnderlyingInstrID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UnderlyingMultiple=token;
		}
		else
		{
			UnderlyingMultiple="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			PositionType=token;
		}
		else
		{
			PositionType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			StrikePrice=token;
		}
		else
		{
			StrikePrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OptionsType=token;
		}
		else
		{
			OptionsType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ProductClass=token;
		}
		else
		{
			ProductClass="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OptionsMode=token;
		}
		else
		{
			OptionsMode="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ProductGroupID=token;
		}
		else
		{
			ProductGroupID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			APIID=token;
		}
		else
		{
			APIID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LegQty=token;
		}
		else
		{
			LegQty="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"ProductID"))
			{
				ProductID=token;
			}
			else if (!strcmp(fieldName,"ProductName"))
			{
				ProductName=token;
			}
			else if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"InstrumentName"))
			{
				InstrumentName=token;
			}
			else if (!strcmp(fieldName,"DeliveryYear"))
			{
				DeliveryYear=token;
			}
			else if (!strcmp(fieldName,"DeliveryMonth"))
			{
				DeliveryMonth=token;
			}
			else if (!strcmp(fieldName,"MaxLimitOrderVolume"))
			{
				MaxLimitOrderVolume=token;
			}
			else if (!strcmp(fieldName,"MinLimitOrderVolume"))
			{
				MinLimitOrderVolume=token;
			}
			else if (!strcmp(fieldName,"MaxMarketOrderVolume"))
			{
				MaxMarketOrderVolume=token;
			}
			else if (!strcmp(fieldName,"MinMarketOrderVolume"))
			{
				MinMarketOrderVolume=token;
			}
			else if (!strcmp(fieldName,"VolumeMultiple"))
			{
				VolumeMultiple=token;
			}
			else if (!strcmp(fieldName,"PriceTick"))
			{
				PriceTick=token;
			}
			else if (!strcmp(fieldName,"Currency"))
			{
				Currency=token;
			}
			else if (!strcmp(fieldName,"LongPosLimit"))
			{
				LongPosLimit=token;
			}
			else if (!strcmp(fieldName,"ShortPosLimit"))
			{
				ShortPosLimit=token;
			}
			else if (!strcmp(fieldName,"LowerLimitPrice"))
			{
				LowerLimitPrice=token;
			}
			else if (!strcmp(fieldName,"UpperLimitPrice"))
			{
				UpperLimitPrice=token;
			}
			else if (!strcmp(fieldName,"PreSettlementPrice"))
			{
				PreSettlementPrice=token;
			}
			else if (!strcmp(fieldName,"InstrumentStatus"))
			{
				InstrumentStatus=token;
			}
			else if (!strcmp(fieldName,"CreateDate"))
			{
				CreateDate=token;
			}
			else if (!strcmp(fieldName,"OpenDate"))
			{
				OpenDate=token;
			}
			else if (!strcmp(fieldName,"ExpireDate"))
			{
				ExpireDate=token;
			}
			else if (!strcmp(fieldName,"StartDelivDate"))
			{
				StartDelivDate=token;
			}
			else if (!strcmp(fieldName,"EndDelivDate"))
			{
				EndDelivDate=token;
			}
			else if (!strcmp(fieldName,"BasisPrice"))
			{
				BasisPrice=token;
			}
			else if (!strcmp(fieldName,"IsTrading"))
			{
				IsTrading=token;
			}
			else if (!strcmp(fieldName,"UnderlyingInstrID"))
			{
				UnderlyingInstrID=token;
			}
			else if (!strcmp(fieldName,"UnderlyingMultiple"))
			{
				UnderlyingMultiple=token;
			}
			else if (!strcmp(fieldName,"PositionType"))
			{
				PositionType=token;
			}
			else if (!strcmp(fieldName,"StrikePrice"))
			{
				StrikePrice=token;
			}
			else if (!strcmp(fieldName,"OptionsType"))
			{
				OptionsType=token;
			}
			else if (!strcmp(fieldName,"ProductClass"))
			{
				ProductClass=token;
			}
			else if (!strcmp(fieldName,"OptionsMode"))
			{
				OptionsMode=token;
			}
			else if (!strcmp(fieldName,"ProductGroupID"))
			{
				ProductGroupID=token;
			}
			else if (!strcmp(fieldName,"APIID"))
			{
				APIID=token;
			}
			else if (!strcmp(fieldName,"LegQty"))
			{
				LegQty=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableInstrument::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableInstrument),output)!=sizeof(CWriteableInstrument))
		return 0;
	else
		return 1;
}

int CWriteableInstrument::writeCSV(FILE *output) const
{
	char buffer[1025];
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ProductID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ProductName.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentName.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	DeliveryYear.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	DeliveryMonth.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MaxLimitOrderVolume.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MinLimitOrderVolume.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MaxMarketOrderVolume.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MinMarketOrderVolume.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	VolumeMultiple.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	PriceTick.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Currency.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LongPosLimit.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ShortPosLimit.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LowerLimitPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UpperLimitPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	PreSettlementPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentStatus.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CreateDate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OpenDate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExpireDate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	StartDelivDate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	EndDelivDate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	BasisPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IsTrading.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UnderlyingInstrID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UnderlyingMultiple.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	PositionType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	StrikePrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OptionsType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ProductClass.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OptionsMode.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ProductGroupID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	APIID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LegQty.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableInstrument::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCInstrument%s = {\n", index_buf);
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	ProductID.getString(buf);
	fprintf(fp,"\t\tProductID = %s    [品种代码]\n",buf);	
	ProductName.getString(buf);
	fprintf(fp,"\t\tProductName = %s    [品种名称]\n",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	InstrumentName.getString(buf);
	fprintf(fp,"\t\tInstrumentName = %s    [合约名称]\n",buf);	
	DeliveryYear.getString(buf);
	fprintf(fp,"\t\tDeliveryYear = %s    [交割年份]\n",buf);	
	DeliveryMonth.getString(buf);
	fprintf(fp,"\t\tDeliveryMonth = %s    [交割月]\n",buf);	
	MaxLimitOrderVolume.getString(buf);
	fprintf(fp,"\t\tMaxLimitOrderVolume = %s    [限价单最大下单量]\n",buf);	
	MinLimitOrderVolume.getString(buf);
	fprintf(fp,"\t\tMinLimitOrderVolume = %s    [限价单最小下单量]\n",buf);	
	MaxMarketOrderVolume.getString(buf);
	fprintf(fp,"\t\tMaxMarketOrderVolume = %s    [市价单最大下单量]\n",buf);	
	MinMarketOrderVolume.getString(buf);
	fprintf(fp,"\t\tMinMarketOrderVolume = %s    [市价单最小下单量]\n",buf);	
	VolumeMultiple.getString(buf);
	fprintf(fp,"\t\tVolumeMultiple = %s    [数量乘数]\n",buf);	
	PriceTick.getString(buf);
	fprintf(fp,"\t\tPriceTick = %s    [报价单位]\n",buf);	
	Currency.getString(buf);
	fprintf(fp,"\t\tCurrency = %s    [币种]\n",buf);	
	LongPosLimit.getString(buf);
	fprintf(fp,"\t\tLongPosLimit = %s    [多头限仓]\n",buf);	
	ShortPosLimit.getString(buf);
	fprintf(fp,"\t\tShortPosLimit = %s    [空头限仓]\n",buf);	
	LowerLimitPrice.getString(buf);
	fprintf(fp,"\t\tLowerLimitPrice = %s    [跌停板价]\n",buf);	
	UpperLimitPrice.getString(buf);
	fprintf(fp,"\t\tUpperLimitPrice = %s    [涨停板价]\n",buf);	
	PreSettlementPrice.getString(buf);
	fprintf(fp,"\t\tPreSettlementPrice = %s    [昨结算]\n",buf);	
	InstrumentStatus.getString(buf);
	fprintf(fp,"\t\tInstrumentStatus = %s    [合约交易状态]\n",buf);	
	CreateDate.getString(buf);
	fprintf(fp,"\t\tCreateDate = %s    [创建日]\n",buf);	
	OpenDate.getString(buf);
	fprintf(fp,"\t\tOpenDate = %s    [上市日]\n",buf);	
	ExpireDate.getString(buf);
	fprintf(fp,"\t\tExpireDate = %s    [到期日]\n",buf);	
	StartDelivDate.getString(buf);
	fprintf(fp,"\t\tStartDelivDate = %s    [开始交割日]\n",buf);	
	EndDelivDate.getString(buf);
	fprintf(fp,"\t\tEndDelivDate = %s    [最后交割日]\n",buf);	
	BasisPrice.getString(buf);
	fprintf(fp,"\t\tBasisPrice = %s    [挂牌基准价]\n",buf);	
	IsTrading.getString(buf);
	fprintf(fp,"\t\tIsTrading = %s    [当前是否交易]\n",buf);	
	UnderlyingInstrID.getString(buf);
	fprintf(fp,"\t\tUnderlyingInstrID = %s    [基础商品代码]\n",buf);	
	UnderlyingMultiple.getString(buf);
	fprintf(fp,"\t\tUnderlyingMultiple = %s    [基础商品乘数]\n",buf);	
	PositionType.getString(buf);
	fprintf(fp,"\t\tPositionType = %s    [持仓类型]\n",buf);	
	StrikePrice.getString(buf);
	fprintf(fp,"\t\tStrikePrice = %s    [执行价]\n",buf);	
	OptionsType.getString(buf);
	fprintf(fp,"\t\tOptionsType = %s    [期权类型]\n",buf);	
	ProductClass.getString(buf);
	fprintf(fp,"\t\tProductClass = %s    [产品类型]\n",buf);	
	OptionsMode.getString(buf);
	fprintf(fp,"\t\tOptionsMode = %s    [期权行权方式]\n",buf);	
	ProductGroupID.getString(buf);
	fprintf(fp,"\t\tProductGroupID = %s    [产品组]\n",buf);	
	APIID.getString(buf);
	fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);	
	LegQty.getString(buf);
	fprintf(fp,"\t\tLegQty = %s    [组合合约腿的数量]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableInstrument::dumpDiff(FILE *fp, const CWriteableInstrument *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCInstrument = {\n");
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	ProductID.getString(buf);
	if (compare(ProductID.getValue(),pOriginal->ProductID.getValue())!=0)
	{
		pOriginal->ProductID.getString(bufOriginal);
		fprintf(fp,"\t\tProductID = %s -> %s    [品种代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tProductID = %s    [品种代码]\n",buf);
	}
	ProductName.getString(buf);
	if (compare(ProductName.getValue(),pOriginal->ProductName.getValue())!=0)
	{
		pOriginal->ProductName.getString(bufOriginal);
		fprintf(fp,"\t\tProductName = %s -> %s    [品种名称]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tProductName = %s    [品种名称]\n",buf);
	}
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	InstrumentName.getString(buf);
	if (compare(InstrumentName.getValue(),pOriginal->InstrumentName.getValue())!=0)
	{
		pOriginal->InstrumentName.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentName = %s -> %s    [合约名称]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentName = %s    [合约名称]\n",buf);
	}
	DeliveryYear.getString(buf);
	if (compare(DeliveryYear.getValue(),pOriginal->DeliveryYear.getValue())!=0)
	{
		pOriginal->DeliveryYear.getString(bufOriginal);
		fprintf(fp,"\t\tDeliveryYear = %s -> %s    [交割年份]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDeliveryYear = %s    [交割年份]\n",buf);
	}
	DeliveryMonth.getString(buf);
	if (compare(DeliveryMonth.getValue(),pOriginal->DeliveryMonth.getValue())!=0)
	{
		pOriginal->DeliveryMonth.getString(bufOriginal);
		fprintf(fp,"\t\tDeliveryMonth = %s -> %s    [交割月]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDeliveryMonth = %s    [交割月]\n",buf);
	}
	MaxLimitOrderVolume.getString(buf);
	if (compare(MaxLimitOrderVolume.getValue(),pOriginal->MaxLimitOrderVolume.getValue())!=0)
	{
		pOriginal->MaxLimitOrderVolume.getString(bufOriginal);
		fprintf(fp,"\t\tMaxLimitOrderVolume = %s -> %s    [限价单最大下单量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMaxLimitOrderVolume = %s    [限价单最大下单量]\n",buf);
	}
	MinLimitOrderVolume.getString(buf);
	if (compare(MinLimitOrderVolume.getValue(),pOriginal->MinLimitOrderVolume.getValue())!=0)
	{
		pOriginal->MinLimitOrderVolume.getString(bufOriginal);
		fprintf(fp,"\t\tMinLimitOrderVolume = %s -> %s    [限价单最小下单量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMinLimitOrderVolume = %s    [限价单最小下单量]\n",buf);
	}
	MaxMarketOrderVolume.getString(buf);
	if (compare(MaxMarketOrderVolume.getValue(),pOriginal->MaxMarketOrderVolume.getValue())!=0)
	{
		pOriginal->MaxMarketOrderVolume.getString(bufOriginal);
		fprintf(fp,"\t\tMaxMarketOrderVolume = %s -> %s    [市价单最大下单量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMaxMarketOrderVolume = %s    [市价单最大下单量]\n",buf);
	}
	MinMarketOrderVolume.getString(buf);
	if (compare(MinMarketOrderVolume.getValue(),pOriginal->MinMarketOrderVolume.getValue())!=0)
	{
		pOriginal->MinMarketOrderVolume.getString(bufOriginal);
		fprintf(fp,"\t\tMinMarketOrderVolume = %s -> %s    [市价单最小下单量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMinMarketOrderVolume = %s    [市价单最小下单量]\n",buf);
	}
	VolumeMultiple.getString(buf);
	if (compare(VolumeMultiple.getValue(),pOriginal->VolumeMultiple.getValue())!=0)
	{
		pOriginal->VolumeMultiple.getString(bufOriginal);
		fprintf(fp,"\t\tVolumeMultiple = %s -> %s    [数量乘数]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tVolumeMultiple = %s    [数量乘数]\n",buf);
	}
	PriceTick.getString(buf);
	if (compare(PriceTick.getValue(),pOriginal->PriceTick.getValue())!=0)
	{
		pOriginal->PriceTick.getString(bufOriginal);
		fprintf(fp,"\t\tPriceTick = %s -> %s    [报价单位]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPriceTick = %s    [报价单位]\n",buf);
	}
	Currency.getString(buf);
	if (compare(Currency.getValue(),pOriginal->Currency.getValue())!=0)
	{
		pOriginal->Currency.getString(bufOriginal);
		fprintf(fp,"\t\tCurrency = %s -> %s    [币种]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCurrency = %s    [币种]\n",buf);
	}
	LongPosLimit.getString(buf);
	if (compare(LongPosLimit.getValue(),pOriginal->LongPosLimit.getValue())!=0)
	{
		pOriginal->LongPosLimit.getString(bufOriginal);
		fprintf(fp,"\t\tLongPosLimit = %s -> %s    [多头限仓]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLongPosLimit = %s    [多头限仓]\n",buf);
	}
	ShortPosLimit.getString(buf);
	if (compare(ShortPosLimit.getValue(),pOriginal->ShortPosLimit.getValue())!=0)
	{
		pOriginal->ShortPosLimit.getString(bufOriginal);
		fprintf(fp,"\t\tShortPosLimit = %s -> %s    [空头限仓]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tShortPosLimit = %s    [空头限仓]\n",buf);
	}
	LowerLimitPrice.getString(buf);
	if (compare(LowerLimitPrice.getValue(),pOriginal->LowerLimitPrice.getValue())!=0)
	{
		pOriginal->LowerLimitPrice.getString(bufOriginal);
		fprintf(fp,"\t\tLowerLimitPrice = %s -> %s    [跌停板价]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLowerLimitPrice = %s    [跌停板价]\n",buf);
	}
	UpperLimitPrice.getString(buf);
	if (compare(UpperLimitPrice.getValue(),pOriginal->UpperLimitPrice.getValue())!=0)
	{
		pOriginal->UpperLimitPrice.getString(bufOriginal);
		fprintf(fp,"\t\tUpperLimitPrice = %s -> %s    [涨停板价]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUpperLimitPrice = %s    [涨停板价]\n",buf);
	}
	PreSettlementPrice.getString(buf);
	if (compare(PreSettlementPrice.getValue(),pOriginal->PreSettlementPrice.getValue())!=0)
	{
		pOriginal->PreSettlementPrice.getString(bufOriginal);
		fprintf(fp,"\t\tPreSettlementPrice = %s -> %s    [昨结算]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPreSettlementPrice = %s    [昨结算]\n",buf);
	}
	InstrumentStatus.getString(buf);
	if (compare(InstrumentStatus.getValue(),pOriginal->InstrumentStatus.getValue())!=0)
	{
		pOriginal->InstrumentStatus.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentStatus = %s -> %s    [合约交易状态]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentStatus = %s    [合约交易状态]\n",buf);
	}
	CreateDate.getString(buf);
	if (compare(CreateDate.getValue(),pOriginal->CreateDate.getValue())!=0)
	{
		pOriginal->CreateDate.getString(bufOriginal);
		fprintf(fp,"\t\tCreateDate = %s -> %s    [创建日]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCreateDate = %s    [创建日]\n",buf);
	}
	OpenDate.getString(buf);
	if (compare(OpenDate.getValue(),pOriginal->OpenDate.getValue())!=0)
	{
		pOriginal->OpenDate.getString(bufOriginal);
		fprintf(fp,"\t\tOpenDate = %s -> %s    [上市日]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOpenDate = %s    [上市日]\n",buf);
	}
	ExpireDate.getString(buf);
	if (compare(ExpireDate.getValue(),pOriginal->ExpireDate.getValue())!=0)
	{
		pOriginal->ExpireDate.getString(bufOriginal);
		fprintf(fp,"\t\tExpireDate = %s -> %s    [到期日]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExpireDate = %s    [到期日]\n",buf);
	}
	StartDelivDate.getString(buf);
	if (compare(StartDelivDate.getValue(),pOriginal->StartDelivDate.getValue())!=0)
	{
		pOriginal->StartDelivDate.getString(bufOriginal);
		fprintf(fp,"\t\tStartDelivDate = %s -> %s    [开始交割日]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tStartDelivDate = %s    [开始交割日]\n",buf);
	}
	EndDelivDate.getString(buf);
	if (compare(EndDelivDate.getValue(),pOriginal->EndDelivDate.getValue())!=0)
	{
		pOriginal->EndDelivDate.getString(bufOriginal);
		fprintf(fp,"\t\tEndDelivDate = %s -> %s    [最后交割日]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tEndDelivDate = %s    [最后交割日]\n",buf);
	}
	BasisPrice.getString(buf);
	if (compare(BasisPrice.getValue(),pOriginal->BasisPrice.getValue())!=0)
	{
		pOriginal->BasisPrice.getString(bufOriginal);
		fprintf(fp,"\t\tBasisPrice = %s -> %s    [挂牌基准价]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBasisPrice = %s    [挂牌基准价]\n",buf);
	}
	IsTrading.getString(buf);
	if (compare(IsTrading.getValue(),pOriginal->IsTrading.getValue())!=0)
	{
		pOriginal->IsTrading.getString(bufOriginal);
		fprintf(fp,"\t\tIsTrading = %s -> %s    [当前是否交易]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIsTrading = %s    [当前是否交易]\n",buf);
	}
	UnderlyingInstrID.getString(buf);
	if (compare(UnderlyingInstrID.getValue(),pOriginal->UnderlyingInstrID.getValue())!=0)
	{
		pOriginal->UnderlyingInstrID.getString(bufOriginal);
		fprintf(fp,"\t\tUnderlyingInstrID = %s -> %s    [基础商品代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUnderlyingInstrID = %s    [基础商品代码]\n",buf);
	}
	UnderlyingMultiple.getString(buf);
	if (compare(UnderlyingMultiple.getValue(),pOriginal->UnderlyingMultiple.getValue())!=0)
	{
		pOriginal->UnderlyingMultiple.getString(bufOriginal);
		fprintf(fp,"\t\tUnderlyingMultiple = %s -> %s    [基础商品乘数]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUnderlyingMultiple = %s    [基础商品乘数]\n",buf);
	}
	PositionType.getString(buf);
	if (compare(PositionType.getValue(),pOriginal->PositionType.getValue())!=0)
	{
		pOriginal->PositionType.getString(bufOriginal);
		fprintf(fp,"\t\tPositionType = %s -> %s    [持仓类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPositionType = %s    [持仓类型]\n",buf);
	}
	StrikePrice.getString(buf);
	if (compare(StrikePrice.getValue(),pOriginal->StrikePrice.getValue())!=0)
	{
		pOriginal->StrikePrice.getString(bufOriginal);
		fprintf(fp,"\t\tStrikePrice = %s -> %s    [执行价]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tStrikePrice = %s    [执行价]\n",buf);
	}
	OptionsType.getString(buf);
	if (compare(OptionsType.getValue(),pOriginal->OptionsType.getValue())!=0)
	{
		pOriginal->OptionsType.getString(bufOriginal);
		fprintf(fp,"\t\tOptionsType = %s -> %s    [期权类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOptionsType = %s    [期权类型]\n",buf);
	}
	ProductClass.getString(buf);
	if (compare(ProductClass.getValue(),pOriginal->ProductClass.getValue())!=0)
	{
		pOriginal->ProductClass.getString(bufOriginal);
		fprintf(fp,"\t\tProductClass = %s -> %s    [产品类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tProductClass = %s    [产品类型]\n",buf);
	}
	OptionsMode.getString(buf);
	if (compare(OptionsMode.getValue(),pOriginal->OptionsMode.getValue())!=0)
	{
		pOriginal->OptionsMode.getString(bufOriginal);
		fprintf(fp,"\t\tOptionsMode = %s -> %s    [期权行权方式]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOptionsMode = %s    [期权行权方式]\n",buf);
	}
	ProductGroupID.getString(buf);
	if (compare(ProductGroupID.getValue(),pOriginal->ProductGroupID.getValue())!=0)
	{
		pOriginal->ProductGroupID.getString(bufOriginal);
		fprintf(fp,"\t\tProductGroupID = %s -> %s    [产品组]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tProductGroupID = %s    [产品组]\n",buf);
	}
	APIID.getString(buf);
	if (compare(APIID.getValue(),pOriginal->APIID.getValue())!=0)
	{
		pOriginal->APIID.getString(bufOriginal);
		fprintf(fp,"\t\tAPIID = %s -> %s    [通道对应的APIID]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);
	}
	LegQty.getString(buf);
	if (compare(LegQty.getValue(),pOriginal->LegQty.getValue())!=0)
	{
		pOriginal->LegQty.getString(bufOriginal);
		fprintf(fp,"\t\tLegQty = %s -> %s    [组合合约腿的数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLegQty = %s    [组合合约腿的数量]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableInstrument::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	ProductID.getString(buf);
	fprintf(fp,",ProductID,%s",buf);	
	ProductName.getString(buf);
	fprintf(fp,",ProductName,%s",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	InstrumentName.getString(buf);
	fprintf(fp,",InstrumentName,%s",buf);	
	DeliveryYear.getString(buf);
	fprintf(fp,",DeliveryYear,%s",buf);	
	DeliveryMonth.getString(buf);
	fprintf(fp,",DeliveryMonth,%s",buf);	
	MaxLimitOrderVolume.getString(buf);
	fprintf(fp,",MaxLimitOrderVolume,%s",buf);	
	MinLimitOrderVolume.getString(buf);
	fprintf(fp,",MinLimitOrderVolume,%s",buf);	
	MaxMarketOrderVolume.getString(buf);
	fprintf(fp,",MaxMarketOrderVolume,%s",buf);	
	MinMarketOrderVolume.getString(buf);
	fprintf(fp,",MinMarketOrderVolume,%s",buf);	
	VolumeMultiple.getString(buf);
	fprintf(fp,",VolumeMultiple,%s",buf);	
	PriceTick.getString(buf);
	fprintf(fp,",PriceTick,%s",buf);	
	Currency.getString(buf);
	fprintf(fp,",Currency,%s",buf);	
	LongPosLimit.getString(buf);
	fprintf(fp,",LongPosLimit,%s",buf);	
	ShortPosLimit.getString(buf);
	fprintf(fp,",ShortPosLimit,%s",buf);	
	LowerLimitPrice.getString(buf);
	fprintf(fp,",LowerLimitPrice,%s",buf);	
	UpperLimitPrice.getString(buf);
	fprintf(fp,",UpperLimitPrice,%s",buf);	
	PreSettlementPrice.getString(buf);
	fprintf(fp,",PreSettlementPrice,%s",buf);	
	InstrumentStatus.getString(buf);
	fprintf(fp,",InstrumentStatus,%s",buf);	
	CreateDate.getString(buf);
	fprintf(fp,",CreateDate,%s",buf);	
	OpenDate.getString(buf);
	fprintf(fp,",OpenDate,%s",buf);	
	ExpireDate.getString(buf);
	fprintf(fp,",ExpireDate,%s",buf);	
	StartDelivDate.getString(buf);
	fprintf(fp,",StartDelivDate,%s",buf);	
	EndDelivDate.getString(buf);
	fprintf(fp,",EndDelivDate,%s",buf);	
	BasisPrice.getString(buf);
	fprintf(fp,",BasisPrice,%s",buf);	
	IsTrading.getString(buf);
	fprintf(fp,",IsTrading,%s",buf);	
	UnderlyingInstrID.getString(buf);
	fprintf(fp,",UnderlyingInstrID,%s",buf);	
	UnderlyingMultiple.getString(buf);
	fprintf(fp,",UnderlyingMultiple,%s",buf);	
	PositionType.getString(buf);
	fprintf(fp,",PositionType,%s",buf);	
	StrikePrice.getString(buf);
	fprintf(fp,",StrikePrice,%s",buf);	
	OptionsType.getString(buf);
	fprintf(fp,",OptionsType,%s",buf);	
	ProductClass.getString(buf);
	fprintf(fp,",ProductClass,%s",buf);	
	OptionsMode.getString(buf);
	fprintf(fp,",OptionsMode,%s",buf);	
	ProductGroupID.getString(buf);
	fprintf(fp,",ProductGroupID,%s",buf);	
	APIID.getString(buf);
	fprintf(fp,",APIID,%s",buf);	
	LegQty.getString(buf);
	fprintf(fp,",LegQty,%s",buf);	
}

void CWriteableInstrument::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	ProductID.getString(buf);
	sprintf(p,"ProductID=%s,",buf);
	p+=strlen(p);
	ProductName.getString(buf);
	sprintf(p,"ProductName=%s,",buf);
	p+=strlen(p);
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	InstrumentName.getString(buf);
	sprintf(p,"InstrumentName=%s,",buf);
	p+=strlen(p);
	DeliveryYear.getString(buf);
	sprintf(p,"DeliveryYear=%s,",buf);
	p+=strlen(p);
	DeliveryMonth.getString(buf);
	sprintf(p,"DeliveryMonth=%s,",buf);
	p+=strlen(p);
	MaxLimitOrderVolume.getString(buf);
	sprintf(p,"MaxLimitOrderVolume=%s,",buf);
	p+=strlen(p);
	MinLimitOrderVolume.getString(buf);
	sprintf(p,"MinLimitOrderVolume=%s,",buf);
	p+=strlen(p);
	MaxMarketOrderVolume.getString(buf);
	sprintf(p,"MaxMarketOrderVolume=%s,",buf);
	p+=strlen(p);
	MinMarketOrderVolume.getString(buf);
	sprintf(p,"MinMarketOrderVolume=%s,",buf);
	p+=strlen(p);
	VolumeMultiple.getString(buf);
	sprintf(p,"VolumeMultiple=%s,",buf);
	p+=strlen(p);
	PriceTick.getString(buf);
	sprintf(p,"PriceTick=%s,",buf);
	p+=strlen(p);
	Currency.getString(buf);
	sprintf(p,"Currency=%s,",buf);
	p+=strlen(p);
	LongPosLimit.getString(buf);
	sprintf(p,"LongPosLimit=%s,",buf);
	p+=strlen(p);
	ShortPosLimit.getString(buf);
	sprintf(p,"ShortPosLimit=%s,",buf);
	p+=strlen(p);
	LowerLimitPrice.getString(buf);
	sprintf(p,"LowerLimitPrice=%s,",buf);
	p+=strlen(p);
	UpperLimitPrice.getString(buf);
	sprintf(p,"UpperLimitPrice=%s,",buf);
	p+=strlen(p);
	PreSettlementPrice.getString(buf);
	sprintf(p,"PreSettlementPrice=%s,",buf);
	p+=strlen(p);
	InstrumentStatus.getString(buf);
	sprintf(p,"InstrumentStatus=%s,",buf);
	p+=strlen(p);
	CreateDate.getString(buf);
	sprintf(p,"CreateDate=%s,",buf);
	p+=strlen(p);
	OpenDate.getString(buf);
	sprintf(p,"OpenDate=%s,",buf);
	p+=strlen(p);
	ExpireDate.getString(buf);
	sprintf(p,"ExpireDate=%s,",buf);
	p+=strlen(p);
	StartDelivDate.getString(buf);
	sprintf(p,"StartDelivDate=%s,",buf);
	p+=strlen(p);
	EndDelivDate.getString(buf);
	sprintf(p,"EndDelivDate=%s,",buf);
	p+=strlen(p);
	BasisPrice.getString(buf);
	sprintf(p,"BasisPrice=%s,",buf);
	p+=strlen(p);
	IsTrading.getString(buf);
	sprintf(p,"IsTrading=%s,",buf);
	p+=strlen(p);
	UnderlyingInstrID.getString(buf);
	sprintf(p,"UnderlyingInstrID=%s,",buf);
	p+=strlen(p);
	UnderlyingMultiple.getString(buf);
	sprintf(p,"UnderlyingMultiple=%s,",buf);
	p+=strlen(p);
	PositionType.getString(buf);
	sprintf(p,"PositionType=%s,",buf);
	p+=strlen(p);
	StrikePrice.getString(buf);
	sprintf(p,"StrikePrice=%s,",buf);
	p+=strlen(p);
	OptionsType.getString(buf);
	sprintf(p,"OptionsType=%s,",buf);
	p+=strlen(p);
	ProductClass.getString(buf);
	sprintf(p,"ProductClass=%s,",buf);
	p+=strlen(p);
	OptionsMode.getString(buf);
	sprintf(p,"OptionsMode=%s,",buf);
	p+=strlen(p);
	ProductGroupID.getString(buf);
	sprintf(p,"ProductGroupID=%s,",buf);
	p+=strlen(p);
	APIID.getString(buf);
	sprintf(p,"APIID=%s,",buf);
	p+=strlen(p);
	LegQty.getString(buf);
	sprintf(p,"LegQty=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableInstrument::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CInstrument");
	pLogger->output(indent,0,"{");
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	ProductID.getString(buf);
	pLogger->output(indent+1,0,"ProductID=%s 品种代码",buf);
	ProductName.getString(buf);
	pLogger->output(indent+1,0,"ProductName=%s 品种名称",buf);
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	InstrumentName.getString(buf);
	pLogger->output(indent+1,0,"InstrumentName=%s 合约名称",buf);
	DeliveryYear.getString(buf);
	pLogger->output(indent+1,0,"DeliveryYear=%s 交割年份",buf);
	DeliveryMonth.getString(buf);
	pLogger->output(indent+1,0,"DeliveryMonth=%s 交割月",buf);
	MaxLimitOrderVolume.getString(buf);
	pLogger->output(indent+1,0,"MaxLimitOrderVolume=%s 限价单最大下单量",buf);
	MinLimitOrderVolume.getString(buf);
	pLogger->output(indent+1,0,"MinLimitOrderVolume=%s 限价单最小下单量",buf);
	MaxMarketOrderVolume.getString(buf);
	pLogger->output(indent+1,0,"MaxMarketOrderVolume=%s 市价单最大下单量",buf);
	MinMarketOrderVolume.getString(buf);
	pLogger->output(indent+1,0,"MinMarketOrderVolume=%s 市价单最小下单量",buf);
	VolumeMultiple.getString(buf);
	pLogger->output(indent+1,0,"VolumeMultiple=%s 数量乘数",buf);
	PriceTick.getString(buf);
	pLogger->output(indent+1,0,"PriceTick=%s 报价单位",buf);
	Currency.getString(buf);
	pLogger->output(indent+1,0,"Currency=%s 币种",buf);
	LongPosLimit.getString(buf);
	pLogger->output(indent+1,0,"LongPosLimit=%s 多头限仓",buf);
	ShortPosLimit.getString(buf);
	pLogger->output(indent+1,0,"ShortPosLimit=%s 空头限仓",buf);
	LowerLimitPrice.getString(buf);
	pLogger->output(indent+1,0,"LowerLimitPrice=%s 跌停板价",buf);
	UpperLimitPrice.getString(buf);
	pLogger->output(indent+1,0,"UpperLimitPrice=%s 涨停板价",buf);
	PreSettlementPrice.getString(buf);
	pLogger->output(indent+1,0,"PreSettlementPrice=%s 昨结算",buf);
	InstrumentStatus.getString(buf);
	pLogger->output(indent+1,0,"InstrumentStatus=%s 合约交易状态",buf);
	CreateDate.getString(buf);
	pLogger->output(indent+1,0,"CreateDate=%s 创建日",buf);
	OpenDate.getString(buf);
	pLogger->output(indent+1,0,"OpenDate=%s 上市日",buf);
	ExpireDate.getString(buf);
	pLogger->output(indent+1,0,"ExpireDate=%s 到期日",buf);
	StartDelivDate.getString(buf);
	pLogger->output(indent+1,0,"StartDelivDate=%s 开始交割日",buf);
	EndDelivDate.getString(buf);
	pLogger->output(indent+1,0,"EndDelivDate=%s 最后交割日",buf);
	BasisPrice.getString(buf);
	pLogger->output(indent+1,0,"BasisPrice=%s 挂牌基准价",buf);
	IsTrading.getString(buf);
	pLogger->output(indent+1,0,"IsTrading=%s 当前是否交易",buf);
	UnderlyingInstrID.getString(buf);
	pLogger->output(indent+1,0,"UnderlyingInstrID=%s 基础商品代码",buf);
	UnderlyingMultiple.getString(buf);
	pLogger->output(indent+1,0,"UnderlyingMultiple=%s 基础商品乘数",buf);
	PositionType.getString(buf);
	pLogger->output(indent+1,0,"PositionType=%s 持仓类型",buf);
	StrikePrice.getString(buf);
	pLogger->output(indent+1,0,"StrikePrice=%s 执行价",buf);
	OptionsType.getString(buf);
	pLogger->output(indent+1,0,"OptionsType=%s 期权类型",buf);
	ProductClass.getString(buf);
	pLogger->output(indent+1,0,"ProductClass=%s 产品类型",buf);
	OptionsMode.getString(buf);
	pLogger->output(indent+1,0,"OptionsMode=%s 期权行权方式",buf);
	ProductGroupID.getString(buf);
	pLogger->output(indent+1,0,"ProductGroupID=%s 产品组",buf);
	APIID.getString(buf);
	pLogger->output(indent+1,0,"APIID=%s 通道对应的APIID",buf);
	LegQty.getString(buf);
	pLogger->output(indent+1,0,"LegQty=%s 组合合约腿的数量",buf);
	pLogger->output(indent,0,"}");
}

CInstrumentIterator::~CInstrumentIterator(void)
{
}


void CInstrumentIterator::dump(FILE *output)
{
	CInstrument *pInstrument;
	
	while ((pInstrument=next())!=NULL)
	{
		pInstrument->dump(output);
	}
}



void CWriteableCmbInstrumentDetail::writeCSVHead(FILE *output)
{
	fprintf(output,"ExchangeID,ArbiInstrumentID,SingleInstrumentID,LegNo,Direction,Ratio\n");
}
	
void CWriteableCmbInstrumentDetail::init(void)
{
	ExchangeID.clear();
	ArbiInstrumentID.clear();
	SingleInstrumentID.clear();
	LegNo.clear();
	Direction.clear();
	Ratio.clear();
}

int CWriteableCmbInstrumentDetail::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableCmbInstrumentDetail),input)!=sizeof(CWriteableCmbInstrumentDetail))
		return 0;
	else
		return 1;
}
	
int CWriteableCmbInstrumentDetail::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ArbiInstrumentID=token;
		}
		else
		{
			ArbiInstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SingleInstrumentID=token;
		}
		else
		{
			SingleInstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LegNo=token;
		}
		else
		{
			LegNo="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Direction=token;
		}
		else
		{
			Direction="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Ratio=token;
		}
		else
		{
			Ratio="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"ArbiInstrumentID"))
			{
				ArbiInstrumentID=token;
			}
			else if (!strcmp(fieldName,"SingleInstrumentID"))
			{
				SingleInstrumentID=token;
			}
			else if (!strcmp(fieldName,"LegNo"))
			{
				LegNo=token;
			}
			else if (!strcmp(fieldName,"Direction"))
			{
				Direction=token;
			}
			else if (!strcmp(fieldName,"Ratio"))
			{
				Ratio=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableCmbInstrumentDetail::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableCmbInstrumentDetail),output)!=sizeof(CWriteableCmbInstrumentDetail))
		return 0;
	else
		return 1;
}

int CWriteableCmbInstrumentDetail::writeCSV(FILE *output) const
{
	char buffer[1025];
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ArbiInstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SingleInstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LegNo.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Direction.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Ratio.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableCmbInstrumentDetail::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCCmbInstrumentDetail%s = {\n", index_buf);
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	ArbiInstrumentID.getString(buf);
	fprintf(fp,"\t\tArbiInstrumentID = %s    [组合合约代码]\n",buf);	
	SingleInstrumentID.getString(buf);
	fprintf(fp,"\t\tSingleInstrumentID = %s    [单腿合约代码]\n",buf);	
	LegNo.getString(buf);
	fprintf(fp,"\t\tLegNo = %s    [组合合约腿的数量]\n",buf);	
	Direction.getString(buf);
	fprintf(fp,"\t\tDirection = %s    [买卖方向]\n",buf);	
	Ratio.getString(buf);
	fprintf(fp,"\t\tRatio = %s    [数量比例]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableCmbInstrumentDetail::dumpDiff(FILE *fp, const CWriteableCmbInstrumentDetail *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCCmbInstrumentDetail = {\n");
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	ArbiInstrumentID.getString(buf);
	if (compare(ArbiInstrumentID.getValue(),pOriginal->ArbiInstrumentID.getValue())!=0)
	{
		pOriginal->ArbiInstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tArbiInstrumentID = %s -> %s    [组合合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tArbiInstrumentID = %s    [组合合约代码]\n",buf);
	}
	SingleInstrumentID.getString(buf);
	if (compare(SingleInstrumentID.getValue(),pOriginal->SingleInstrumentID.getValue())!=0)
	{
		pOriginal->SingleInstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tSingleInstrumentID = %s -> %s    [单腿合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSingleInstrumentID = %s    [单腿合约代码]\n",buf);
	}
	LegNo.getString(buf);
	if (compare(LegNo.getValue(),pOriginal->LegNo.getValue())!=0)
	{
		pOriginal->LegNo.getString(bufOriginal);
		fprintf(fp,"\t\tLegNo = %s -> %s    [组合合约腿的数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLegNo = %s    [组合合约腿的数量]\n",buf);
	}
	Direction.getString(buf);
	if (compare(Direction.getValue(),pOriginal->Direction.getValue())!=0)
	{
		pOriginal->Direction.getString(bufOriginal);
		fprintf(fp,"\t\tDirection = %s -> %s    [买卖方向]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDirection = %s    [买卖方向]\n",buf);
	}
	Ratio.getString(buf);
	if (compare(Ratio.getValue(),pOriginal->Ratio.getValue())!=0)
	{
		pOriginal->Ratio.getString(bufOriginal);
		fprintf(fp,"\t\tRatio = %s -> %s    [数量比例]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tRatio = %s    [数量比例]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableCmbInstrumentDetail::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	ArbiInstrumentID.getString(buf);
	fprintf(fp,",ArbiInstrumentID,%s",buf);	
	SingleInstrumentID.getString(buf);
	fprintf(fp,",SingleInstrumentID,%s",buf);	
	LegNo.getString(buf);
	fprintf(fp,",LegNo,%s",buf);	
	Direction.getString(buf);
	fprintf(fp,",Direction,%s",buf);	
	Ratio.getString(buf);
	fprintf(fp,",Ratio,%s",buf);	
}

void CWriteableCmbInstrumentDetail::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	ArbiInstrumentID.getString(buf);
	sprintf(p,"ArbiInstrumentID=%s,",buf);
	p+=strlen(p);
	SingleInstrumentID.getString(buf);
	sprintf(p,"SingleInstrumentID=%s,",buf);
	p+=strlen(p);
	LegNo.getString(buf);
	sprintf(p,"LegNo=%s,",buf);
	p+=strlen(p);
	Direction.getString(buf);
	sprintf(p,"Direction=%s,",buf);
	p+=strlen(p);
	Ratio.getString(buf);
	sprintf(p,"Ratio=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableCmbInstrumentDetail::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CCmbInstrumentDetail");
	pLogger->output(indent,0,"{");
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	ArbiInstrumentID.getString(buf);
	pLogger->output(indent+1,0,"ArbiInstrumentID=%s 组合合约代码",buf);
	SingleInstrumentID.getString(buf);
	pLogger->output(indent+1,0,"SingleInstrumentID=%s 单腿合约代码",buf);
	LegNo.getString(buf);
	pLogger->output(indent+1,0,"LegNo=%s 组合合约腿的数量",buf);
	Direction.getString(buf);
	pLogger->output(indent+1,0,"Direction=%s 买卖方向",buf);
	Ratio.getString(buf);
	pLogger->output(indent+1,0,"Ratio=%s 数量比例",buf);
	pLogger->output(indent,0,"}");
}

CCmbInstrumentDetailIterator::~CCmbInstrumentDetailIterator(void)
{
}


void CCmbInstrumentDetailIterator::dump(FILE *output)
{
	CCmbInstrumentDetail *pCmbInstrumentDetail;
	
	while ((pCmbInstrumentDetail=next())!=NULL)
	{
		pCmbInstrumentDetail->dump(output);
	}
}



void CWriteableClientTradingID::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,InvestorID,AccountID,ExchangeID,ParticipantID,ClientID,ClientRight,ClientType,ClientHedgeFlag,IsActive,APIID\n");
}
	
void CWriteableClientTradingID::init(void)
{
	BrokerID.clear();
	InvestorID.clear();
	AccountID.clear();
	ExchangeID.clear();
	ParticipantID.clear();
	ClientID.clear();
	ClientRight.clear();
	ClientType.clear();
	ClientHedgeFlag.clear();
	IsActive.clear();
	APIID.clear();
	pInvestorAccount=NULL;
}

int CWriteableClientTradingID::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableClientTradingID),input)!=sizeof(CWriteableClientTradingID))
		return 0;
	else
		return 1;
}
	
int CWriteableClientTradingID::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			AccountID=token;
		}
		else
		{
			AccountID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ParticipantID=token;
		}
		else
		{
			ParticipantID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ClientID=token;
		}
		else
		{
			ClientID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ClientRight=token;
		}
		else
		{
			ClientRight="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ClientType=token;
		}
		else
		{
			ClientType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ClientHedgeFlag=token;
		}
		else
		{
			ClientHedgeFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IsActive=token;
		}
		else
		{
			IsActive="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			APIID=token;
		}
		else
		{
			APIID="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"AccountID"))
			{
				AccountID=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"ParticipantID"))
			{
				ParticipantID=token;
			}
			else if (!strcmp(fieldName,"ClientID"))
			{
				ClientID=token;
			}
			else if (!strcmp(fieldName,"ClientRight"))
			{
				ClientRight=token;
			}
			else if (!strcmp(fieldName,"ClientType"))
			{
				ClientType=token;
			}
			else if (!strcmp(fieldName,"ClientHedgeFlag"))
			{
				ClientHedgeFlag=token;
			}
			else if (!strcmp(fieldName,"IsActive"))
			{
				IsActive=token;
			}
			else if (!strcmp(fieldName,"APIID"))
			{
				APIID=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableClientTradingID::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableClientTradingID),output)!=sizeof(CWriteableClientTradingID))
		return 0;
	else
		return 1;
}

int CWriteableClientTradingID::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	AccountID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ParticipantID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ClientID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ClientRight.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ClientType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ClientHedgeFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IsActive.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	APIID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableClientTradingID::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCClientTradingID%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);	
	AccountID.getString(buf);
	fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,"\t\tParticipantID = %s    [会员编号]\n",buf);	
	ClientID.getString(buf);
	fprintf(fp,"\t\tClientID = %s    [客户代码]\n",buf);	
	ClientRight.getString(buf);
	fprintf(fp,"\t\tClientRight = %s    [客户代码权限]\n",buf);	
	ClientType.getString(buf);
	fprintf(fp,"\t\tClientType = %s    [客户类型]\n",buf);	
	ClientHedgeFlag.getString(buf);
	fprintf(fp,"\t\tClientHedgeFlag = %s    [客户保值类型]\n",buf);	
	IsActive.getString(buf);
	fprintf(fp,"\t\tIsActive = %s    [是否活跃]\n",buf);	
	APIID.getString(buf);
	fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableClientTradingID::dumpDiff(FILE *fp, const CWriteableClientTradingID *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCClientTradingID = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);
	}
	AccountID.getString(buf);
	if (compare(AccountID.getValue(),pOriginal->AccountID.getValue())!=0)
	{
		pOriginal->AccountID.getString(bufOriginal);
		fprintf(fp,"\t\tAccountID = %s -> %s    [资金帐号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	ParticipantID.getString(buf);
	if (compare(ParticipantID.getValue(),pOriginal->ParticipantID.getValue())!=0)
	{
		pOriginal->ParticipantID.getString(bufOriginal);
		fprintf(fp,"\t\tParticipantID = %s -> %s    [会员编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tParticipantID = %s    [会员编号]\n",buf);
	}
	ClientID.getString(buf);
	if (compare(ClientID.getValue(),pOriginal->ClientID.getValue())!=0)
	{
		pOriginal->ClientID.getString(bufOriginal);
		fprintf(fp,"\t\tClientID = %s -> %s    [客户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tClientID = %s    [客户代码]\n",buf);
	}
	ClientRight.getString(buf);
	if (compare(ClientRight.getValue(),pOriginal->ClientRight.getValue())!=0)
	{
		pOriginal->ClientRight.getString(bufOriginal);
		fprintf(fp,"\t\tClientRight = %s -> %s    [客户代码权限]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tClientRight = %s    [客户代码权限]\n",buf);
	}
	ClientType.getString(buf);
	if (compare(ClientType.getValue(),pOriginal->ClientType.getValue())!=0)
	{
		pOriginal->ClientType.getString(bufOriginal);
		fprintf(fp,"\t\tClientType = %s -> %s    [客户类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tClientType = %s    [客户类型]\n",buf);
	}
	ClientHedgeFlag.getString(buf);
	if (compare(ClientHedgeFlag.getValue(),pOriginal->ClientHedgeFlag.getValue())!=0)
	{
		pOriginal->ClientHedgeFlag.getString(bufOriginal);
		fprintf(fp,"\t\tClientHedgeFlag = %s -> %s    [客户保值类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tClientHedgeFlag = %s    [客户保值类型]\n",buf);
	}
	IsActive.getString(buf);
	if (compare(IsActive.getValue(),pOriginal->IsActive.getValue())!=0)
	{
		pOriginal->IsActive.getString(bufOriginal);
		fprintf(fp,"\t\tIsActive = %s -> %s    [是否活跃]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIsActive = %s    [是否活跃]\n",buf);
	}
	APIID.getString(buf);
	if (compare(APIID.getValue(),pOriginal->APIID.getValue())!=0)
	{
		pOriginal->APIID.getString(bufOriginal);
		fprintf(fp,"\t\tAPIID = %s -> %s    [通道对应的APIID]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableClientTradingID::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	AccountID.getString(buf);
	fprintf(fp,",AccountID,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,",ParticipantID,%s",buf);	
	ClientID.getString(buf);
	fprintf(fp,",ClientID,%s",buf);	
	ClientRight.getString(buf);
	fprintf(fp,",ClientRight,%s",buf);	
	ClientType.getString(buf);
	fprintf(fp,",ClientType,%s",buf);	
	ClientHedgeFlag.getString(buf);
	fprintf(fp,",ClientHedgeFlag,%s",buf);	
	IsActive.getString(buf);
	fprintf(fp,",IsActive,%s",buf);	
	APIID.getString(buf);
	fprintf(fp,",APIID,%s",buf);	
}

void CWriteableClientTradingID::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	AccountID.getString(buf);
	sprintf(p,"AccountID=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	ParticipantID.getString(buf);
	sprintf(p,"ParticipantID=%s,",buf);
	p+=strlen(p);
	ClientID.getString(buf);
	sprintf(p,"ClientID=%s,",buf);
	p+=strlen(p);
	ClientRight.getString(buf);
	sprintf(p,"ClientRight=%s,",buf);
	p+=strlen(p);
	ClientType.getString(buf);
	sprintf(p,"ClientType=%s,",buf);
	p+=strlen(p);
	ClientHedgeFlag.getString(buf);
	sprintf(p,"ClientHedgeFlag=%s,",buf);
	p+=strlen(p);
	IsActive.getString(buf);
	sprintf(p,"IsActive=%s,",buf);
	p+=strlen(p);
	APIID.getString(buf);
	sprintf(p,"APIID=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableClientTradingID::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CClientTradingID");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编号",buf);
	AccountID.getString(buf);
	pLogger->output(indent+1,0,"AccountID=%s 资金帐号",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	ParticipantID.getString(buf);
	pLogger->output(indent+1,0,"ParticipantID=%s 会员编号",buf);
	ClientID.getString(buf);
	pLogger->output(indent+1,0,"ClientID=%s 客户代码",buf);
	ClientRight.getString(buf);
	pLogger->output(indent+1,0,"ClientRight=%s 客户代码权限",buf);
	ClientType.getString(buf);
	pLogger->output(indent+1,0,"ClientType=%s 客户类型",buf);
	ClientHedgeFlag.getString(buf);
	pLogger->output(indent+1,0,"ClientHedgeFlag=%s 客户保值类型",buf);
	IsActive.getString(buf);
	pLogger->output(indent+1,0,"IsActive=%s 是否活跃",buf);
	APIID.getString(buf);
	pLogger->output(indent+1,0,"APIID=%s 通道对应的APIID",buf);
	pLogger->output(indent,0,"}");
}

CClientTradingIDIterator::~CClientTradingIDIterator(void)
{
}


void CClientTradingIDIterator::dump(FILE *output)
{
	CClientTradingID *pClientTradingID;
	
	while ((pClientTradingID=next())!=NULL)
	{
		pClientTradingID->dump(output);
	}
}



void CWriteableInvestor::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,InvestorID,InvestorName\n");
}
	
void CWriteableInvestor::init(void)
{
	BrokerID.clear();
	InvestorID.clear();
	InvestorName.clear();
}

int CWriteableInvestor::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableInvestor),input)!=sizeof(CWriteableInvestor))
		return 0;
	else
		return 1;
}
	
int CWriteableInvestor::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorName=token;
		}
		else
		{
			InvestorName="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"InvestorName"))
			{
				InvestorName=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableInvestor::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableInvestor),output)!=sizeof(CWriteableInvestor))
		return 0;
	else
		return 1;
}

int CWriteableInvestor::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorName.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableInvestor::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCInvestor%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);	
	InvestorName.getString(buf);
	fprintf(fp,"\t\tInvestorName = %s    [投资者名称]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableInvestor::dumpDiff(FILE *fp, const CWriteableInvestor *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCInvestor = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);
	}
	InvestorName.getString(buf);
	if (compare(InvestorName.getValue(),pOriginal->InvestorName.getValue())!=0)
	{
		pOriginal->InvestorName.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorName = %s -> %s    [投资者名称]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorName = %s    [投资者名称]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableInvestor::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	InvestorName.getString(buf);
	fprintf(fp,",InvestorName,%s",buf);	
}

void CWriteableInvestor::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	InvestorName.getString(buf);
	sprintf(p,"InvestorName=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableInvestor::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CInvestor");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编号",buf);
	InvestorName.getString(buf);
	pLogger->output(indent+1,0,"InvestorName=%s 投资者名称",buf);
	pLogger->output(indent,0,"}");
}

CInvestorIterator::~CInvestorIterator(void)
{
}


void CInvestorIterator::dump(FILE *output)
{
	CInvestor *pInvestor;
	
	while ((pInvestor=next())!=NULL)
	{
		pInvestor->dump(output);
	}
}



void CWriteableInvestorMargin::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,ExchangeID,InvestorID,InstrumentID,HedgeFlag,LongMarginRate,LongMarginAmt,ShortMarginRate,ShortMarginAmt\n");
}
	
void CWriteableInvestorMargin::init(void)
{
	BrokerID.clear();
	ExchangeID.clear();
	InvestorID.clear();
	InstrumentID.clear();
	HedgeFlag.clear();
	LongMarginRate.clear();
	LongMarginAmt.clear();
	ShortMarginRate.clear();
	ShortMarginAmt.clear();
}

int CWriteableInvestorMargin::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableInvestorMargin),input)!=sizeof(CWriteableInvestorMargin))
		return 0;
	else
		return 1;
}
	
int CWriteableInvestorMargin::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			HedgeFlag=token;
		}
		else
		{
			HedgeFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LongMarginRate=token;
		}
		else
		{
			LongMarginRate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LongMarginAmt=token;
		}
		else
		{
			LongMarginAmt="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ShortMarginRate=token;
		}
		else
		{
			ShortMarginRate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ShortMarginAmt=token;
		}
		else
		{
			ShortMarginAmt="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"HedgeFlag"))
			{
				HedgeFlag=token;
			}
			else if (!strcmp(fieldName,"LongMarginRate"))
			{
				LongMarginRate=token;
			}
			else if (!strcmp(fieldName,"LongMarginAmt"))
			{
				LongMarginAmt=token;
			}
			else if (!strcmp(fieldName,"ShortMarginRate"))
			{
				ShortMarginRate=token;
			}
			else if (!strcmp(fieldName,"ShortMarginAmt"))
			{
				ShortMarginAmt=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableInvestorMargin::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableInvestorMargin),output)!=sizeof(CWriteableInvestorMargin))
		return 0;
	else
		return 1;
}

int CWriteableInvestorMargin::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	HedgeFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LongMarginRate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LongMarginAmt.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ShortMarginRate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ShortMarginAmt.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableInvestorMargin::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCInvestorMargin%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编码]\n",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);	
	LongMarginRate.getString(buf);
	fprintf(fp,"\t\tLongMarginRate = %s    [多头占用保证金按比例]\n",buf);	
	LongMarginAmt.getString(buf);
	fprintf(fp,"\t\tLongMarginAmt = %s    [多头保证金按手数]\n",buf);	
	ShortMarginRate.getString(buf);
	fprintf(fp,"\t\tShortMarginRate = %s    [空头占用保证金按比例]\n",buf);	
	ShortMarginAmt.getString(buf);
	fprintf(fp,"\t\tShortMarginAmt = %s    [空头保证金按手数]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableInvestorMargin::dumpDiff(FILE *fp, const CWriteableInvestorMargin *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCInvestorMargin = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编码]\n",buf);
	}
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	HedgeFlag.getString(buf);
	if (compare(HedgeFlag.getValue(),pOriginal->HedgeFlag.getValue())!=0)
	{
		pOriginal->HedgeFlag.getString(bufOriginal);
		fprintf(fp,"\t\tHedgeFlag = %s -> %s    [投机套保标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);
	}
	LongMarginRate.getString(buf);
	if (compare(LongMarginRate.getValue(),pOriginal->LongMarginRate.getValue())!=0)
	{
		pOriginal->LongMarginRate.getString(bufOriginal);
		fprintf(fp,"\t\tLongMarginRate = %s -> %s    [多头占用保证金按比例]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLongMarginRate = %s    [多头占用保证金按比例]\n",buf);
	}
	LongMarginAmt.getString(buf);
	if (compare(LongMarginAmt.getValue(),pOriginal->LongMarginAmt.getValue())!=0)
	{
		pOriginal->LongMarginAmt.getString(bufOriginal);
		fprintf(fp,"\t\tLongMarginAmt = %s -> %s    [多头保证金按手数]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLongMarginAmt = %s    [多头保证金按手数]\n",buf);
	}
	ShortMarginRate.getString(buf);
	if (compare(ShortMarginRate.getValue(),pOriginal->ShortMarginRate.getValue())!=0)
	{
		pOriginal->ShortMarginRate.getString(bufOriginal);
		fprintf(fp,"\t\tShortMarginRate = %s -> %s    [空头占用保证金按比例]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tShortMarginRate = %s    [空头占用保证金按比例]\n",buf);
	}
	ShortMarginAmt.getString(buf);
	if (compare(ShortMarginAmt.getValue(),pOriginal->ShortMarginAmt.getValue())!=0)
	{
		pOriginal->ShortMarginAmt.getString(bufOriginal);
		fprintf(fp,"\t\tShortMarginAmt = %s -> %s    [空头保证金按手数]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tShortMarginAmt = %s    [空头保证金按手数]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableInvestorMargin::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,",HedgeFlag,%s",buf);	
	LongMarginRate.getString(buf);
	fprintf(fp,",LongMarginRate,%s",buf);	
	LongMarginAmt.getString(buf);
	fprintf(fp,",LongMarginAmt,%s",buf);	
	ShortMarginRate.getString(buf);
	fprintf(fp,",ShortMarginRate,%s",buf);	
	ShortMarginAmt.getString(buf);
	fprintf(fp,",ShortMarginAmt,%s",buf);	
}

void CWriteableInvestorMargin::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	HedgeFlag.getString(buf);
	sprintf(p,"HedgeFlag=%s,",buf);
	p+=strlen(p);
	LongMarginRate.getString(buf);
	sprintf(p,"LongMarginRate=%s,",buf);
	p+=strlen(p);
	LongMarginAmt.getString(buf);
	sprintf(p,"LongMarginAmt=%s,",buf);
	p+=strlen(p);
	ShortMarginRate.getString(buf);
	sprintf(p,"ShortMarginRate=%s,",buf);
	p+=strlen(p);
	ShortMarginAmt.getString(buf);
	sprintf(p,"ShortMarginAmt=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableInvestorMargin::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CInvestorMargin");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编码",buf);
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	HedgeFlag.getString(buf);
	pLogger->output(indent+1,0,"HedgeFlag=%s 投机套保标志",buf);
	LongMarginRate.getString(buf);
	pLogger->output(indent+1,0,"LongMarginRate=%s 多头占用保证金按比例",buf);
	LongMarginAmt.getString(buf);
	pLogger->output(indent+1,0,"LongMarginAmt=%s 多头保证金按手数",buf);
	ShortMarginRate.getString(buf);
	pLogger->output(indent+1,0,"ShortMarginRate=%s 空头占用保证金按比例",buf);
	ShortMarginAmt.getString(buf);
	pLogger->output(indent+1,0,"ShortMarginAmt=%s 空头保证金按手数",buf);
	pLogger->output(indent,0,"}");
}

CInvestorMarginIterator::~CInvestorMarginIterator(void)
{
}


void CInvestorMarginIterator::dump(FILE *output)
{
	CInvestorMargin *pInvestorMargin;
	
	while ((pInvestorMargin=next())!=NULL)
	{
		pInvestorMargin->dump(output);
	}
}



void CWriteableInvestorFee::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,ExchangeID,InvestorID,InstrumentID,HedgeFlag,OpenFeeRate,OpenFeeAmt,OffsetFeeRate,OffsetFeeAmt,OTFeeRate,OTFeeAmt\n");
}
	
void CWriteableInvestorFee::init(void)
{
	BrokerID.clear();
	ExchangeID.clear();
	InvestorID.clear();
	InstrumentID.clear();
	HedgeFlag.clear();
	OpenFeeRate.clear();
	OpenFeeAmt.clear();
	OffsetFeeRate.clear();
	OffsetFeeAmt.clear();
	OTFeeRate.clear();
	OTFeeAmt.clear();
}

int CWriteableInvestorFee::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableInvestorFee),input)!=sizeof(CWriteableInvestorFee))
		return 0;
	else
		return 1;
}
	
int CWriteableInvestorFee::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			HedgeFlag=token;
		}
		else
		{
			HedgeFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OpenFeeRate=token;
		}
		else
		{
			OpenFeeRate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OpenFeeAmt=token;
		}
		else
		{
			OpenFeeAmt="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OffsetFeeRate=token;
		}
		else
		{
			OffsetFeeRate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OffsetFeeAmt=token;
		}
		else
		{
			OffsetFeeAmt="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OTFeeRate=token;
		}
		else
		{
			OTFeeRate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OTFeeAmt=token;
		}
		else
		{
			OTFeeAmt="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"HedgeFlag"))
			{
				HedgeFlag=token;
			}
			else if (!strcmp(fieldName,"OpenFeeRate"))
			{
				OpenFeeRate=token;
			}
			else if (!strcmp(fieldName,"OpenFeeAmt"))
			{
				OpenFeeAmt=token;
			}
			else if (!strcmp(fieldName,"OffsetFeeRate"))
			{
				OffsetFeeRate=token;
			}
			else if (!strcmp(fieldName,"OffsetFeeAmt"))
			{
				OffsetFeeAmt=token;
			}
			else if (!strcmp(fieldName,"OTFeeRate"))
			{
				OTFeeRate=token;
			}
			else if (!strcmp(fieldName,"OTFeeAmt"))
			{
				OTFeeAmt=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableInvestorFee::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableInvestorFee),output)!=sizeof(CWriteableInvestorFee))
		return 0;
	else
		return 1;
}

int CWriteableInvestorFee::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	HedgeFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OpenFeeRate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OpenFeeAmt.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OffsetFeeRate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OffsetFeeAmt.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OTFeeRate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OTFeeAmt.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableInvestorFee::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCInvestorFee%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编码]\n",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);	
	OpenFeeRate.getString(buf);
	fprintf(fp,"\t\tOpenFeeRate = %s    [开仓手续费按比例]\n",buf);	
	OpenFeeAmt.getString(buf);
	fprintf(fp,"\t\tOpenFeeAmt = %s    [开仓手续费按手数]\n",buf);	
	OffsetFeeRate.getString(buf);
	fprintf(fp,"\t\tOffsetFeeRate = %s    [平仓手续费按比例]\n",buf);	
	OffsetFeeAmt.getString(buf);
	fprintf(fp,"\t\tOffsetFeeAmt = %s    [平仓手续费按手数]\n",buf);	
	OTFeeRate.getString(buf);
	fprintf(fp,"\t\tOTFeeRate = %s    [平今仓手续费按比例]\n",buf);	
	OTFeeAmt.getString(buf);
	fprintf(fp,"\t\tOTFeeAmt = %s    [平今仓手续费按手数]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableInvestorFee::dumpDiff(FILE *fp, const CWriteableInvestorFee *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCInvestorFee = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编码]\n",buf);
	}
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	HedgeFlag.getString(buf);
	if (compare(HedgeFlag.getValue(),pOriginal->HedgeFlag.getValue())!=0)
	{
		pOriginal->HedgeFlag.getString(bufOriginal);
		fprintf(fp,"\t\tHedgeFlag = %s -> %s    [投机套保标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);
	}
	OpenFeeRate.getString(buf);
	if (compare(OpenFeeRate.getValue(),pOriginal->OpenFeeRate.getValue())!=0)
	{
		pOriginal->OpenFeeRate.getString(bufOriginal);
		fprintf(fp,"\t\tOpenFeeRate = %s -> %s    [开仓手续费按比例]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOpenFeeRate = %s    [开仓手续费按比例]\n",buf);
	}
	OpenFeeAmt.getString(buf);
	if (compare(OpenFeeAmt.getValue(),pOriginal->OpenFeeAmt.getValue())!=0)
	{
		pOriginal->OpenFeeAmt.getString(bufOriginal);
		fprintf(fp,"\t\tOpenFeeAmt = %s -> %s    [开仓手续费按手数]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOpenFeeAmt = %s    [开仓手续费按手数]\n",buf);
	}
	OffsetFeeRate.getString(buf);
	if (compare(OffsetFeeRate.getValue(),pOriginal->OffsetFeeRate.getValue())!=0)
	{
		pOriginal->OffsetFeeRate.getString(bufOriginal);
		fprintf(fp,"\t\tOffsetFeeRate = %s -> %s    [平仓手续费按比例]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOffsetFeeRate = %s    [平仓手续费按比例]\n",buf);
	}
	OffsetFeeAmt.getString(buf);
	if (compare(OffsetFeeAmt.getValue(),pOriginal->OffsetFeeAmt.getValue())!=0)
	{
		pOriginal->OffsetFeeAmt.getString(bufOriginal);
		fprintf(fp,"\t\tOffsetFeeAmt = %s -> %s    [平仓手续费按手数]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOffsetFeeAmt = %s    [平仓手续费按手数]\n",buf);
	}
	OTFeeRate.getString(buf);
	if (compare(OTFeeRate.getValue(),pOriginal->OTFeeRate.getValue())!=0)
	{
		pOriginal->OTFeeRate.getString(bufOriginal);
		fprintf(fp,"\t\tOTFeeRate = %s -> %s    [平今仓手续费按比例]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOTFeeRate = %s    [平今仓手续费按比例]\n",buf);
	}
	OTFeeAmt.getString(buf);
	if (compare(OTFeeAmt.getValue(),pOriginal->OTFeeAmt.getValue())!=0)
	{
		pOriginal->OTFeeAmt.getString(bufOriginal);
		fprintf(fp,"\t\tOTFeeAmt = %s -> %s    [平今仓手续费按手数]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOTFeeAmt = %s    [平今仓手续费按手数]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableInvestorFee::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,",HedgeFlag,%s",buf);	
	OpenFeeRate.getString(buf);
	fprintf(fp,",OpenFeeRate,%s",buf);	
	OpenFeeAmt.getString(buf);
	fprintf(fp,",OpenFeeAmt,%s",buf);	
	OffsetFeeRate.getString(buf);
	fprintf(fp,",OffsetFeeRate,%s",buf);	
	OffsetFeeAmt.getString(buf);
	fprintf(fp,",OffsetFeeAmt,%s",buf);	
	OTFeeRate.getString(buf);
	fprintf(fp,",OTFeeRate,%s",buf);	
	OTFeeAmt.getString(buf);
	fprintf(fp,",OTFeeAmt,%s",buf);	
}

void CWriteableInvestorFee::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	HedgeFlag.getString(buf);
	sprintf(p,"HedgeFlag=%s,",buf);
	p+=strlen(p);
	OpenFeeRate.getString(buf);
	sprintf(p,"OpenFeeRate=%s,",buf);
	p+=strlen(p);
	OpenFeeAmt.getString(buf);
	sprintf(p,"OpenFeeAmt=%s,",buf);
	p+=strlen(p);
	OffsetFeeRate.getString(buf);
	sprintf(p,"OffsetFeeRate=%s,",buf);
	p+=strlen(p);
	OffsetFeeAmt.getString(buf);
	sprintf(p,"OffsetFeeAmt=%s,",buf);
	p+=strlen(p);
	OTFeeRate.getString(buf);
	sprintf(p,"OTFeeRate=%s,",buf);
	p+=strlen(p);
	OTFeeAmt.getString(buf);
	sprintf(p,"OTFeeAmt=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableInvestorFee::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CInvestorFee");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编码",buf);
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	HedgeFlag.getString(buf);
	pLogger->output(indent+1,0,"HedgeFlag=%s 投机套保标志",buf);
	OpenFeeRate.getString(buf);
	pLogger->output(indent+1,0,"OpenFeeRate=%s 开仓手续费按比例",buf);
	OpenFeeAmt.getString(buf);
	pLogger->output(indent+1,0,"OpenFeeAmt=%s 开仓手续费按手数",buf);
	OffsetFeeRate.getString(buf);
	pLogger->output(indent+1,0,"OffsetFeeRate=%s 平仓手续费按比例",buf);
	OffsetFeeAmt.getString(buf);
	pLogger->output(indent+1,0,"OffsetFeeAmt=%s 平仓手续费按手数",buf);
	OTFeeRate.getString(buf);
	pLogger->output(indent+1,0,"OTFeeRate=%s 平今仓手续费按比例",buf);
	OTFeeAmt.getString(buf);
	pLogger->output(indent+1,0,"OTFeeAmt=%s 平今仓手续费按手数",buf);
	pLogger->output(indent,0,"}");
}

CInvestorFeeIterator::~CInvestorFeeIterator(void)
{
}


void CInvestorFeeIterator::dump(FILE *output)
{
	CInvestorFee *pInvestorFee;
	
	while ((pInvestorFee=next())!=NULL)
	{
		pInvestorFee->dump(output);
	}
}



void CWriteableUser::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,UserID,Password,IsActive,UserName,UserType,Department,GrantFuncSet,CheckIpMacAddr\n");
}
	
void CWriteableUser::init(void)
{
	BrokerID.clear();
	UserID.clear();
	Password.clear();
	IsActive.clear();
	UserName.clear();
	UserType.clear();
	Department.clear();
	GrantFuncSet.clear();
	CheckIpMacAddr.clear();
}

int CWriteableUser::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableUser),input)!=sizeof(CWriteableUser))
		return 0;
	else
		return 1;
}
	
int CWriteableUser::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserID=token;
		}
		else
		{
			UserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Password=token;
		}
		else
		{
			Password="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IsActive=token;
		}
		else
		{
			IsActive="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserName=token;
		}
		else
		{
			UserName="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserType=token;
		}
		else
		{
			UserType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Department=token;
		}
		else
		{
			Department="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			GrantFuncSet=token;
		}
		else
		{
			GrantFuncSet="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CheckIpMacAddr=token;
		}
		else
		{
			CheckIpMacAddr="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"UserID"))
			{
				UserID=token;
			}
			else if (!strcmp(fieldName,"Password"))
			{
				Password=token;
			}
			else if (!strcmp(fieldName,"IsActive"))
			{
				IsActive=token;
			}
			else if (!strcmp(fieldName,"UserName"))
			{
				UserName=token;
			}
			else if (!strcmp(fieldName,"UserType"))
			{
				UserType=token;
			}
			else if (!strcmp(fieldName,"Department"))
			{
				Department=token;
			}
			else if (!strcmp(fieldName,"GrantFuncSet"))
			{
				GrantFuncSet=token;
			}
			else if (!strcmp(fieldName,"CheckIpMacAddr"))
			{
				CheckIpMacAddr=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableUser::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableUser),output)!=sizeof(CWriteableUser))
		return 0;
	else
		return 1;
}

int CWriteableUser::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Password.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IsActive.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserName.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Department.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	GrantFuncSet.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CheckIpMacAddr.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableUser::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCUser%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	UserID.getString(buf);
	fprintf(fp,"\t\tUserID = %s    [用户代码]\n",buf);	
	Password.getString(buf);
	fprintf(fp,"\t\tPassword = %s    [用户登录密码]\n",buf);	
	IsActive.getString(buf);
	fprintf(fp,"\t\tIsActive = %s    [是否活跃]\n",buf);	
	UserName.getString(buf);
	fprintf(fp,"\t\tUserName = %s    [用户名称]\n",buf);	
	UserType.getString(buf);
	fprintf(fp,"\t\tUserType = %s    [用户类型]\n",buf);	
	Department.getString(buf);
	fprintf(fp,"\t\tDepartment = %s    [营业部]\n",buf);	
	GrantFuncSet.getString(buf);
	fprintf(fp,"\t\tGrantFuncSet = %s    [授权功能集]\n",buf);	
	CheckIpMacAddr.getString(buf);
	fprintf(fp,"\t\tCheckIpMacAddr = %s    [是否检查IP和MAC]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableUser::dumpDiff(FILE *fp, const CWriteableUser *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCUser = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	UserID.getString(buf);
	if (compare(UserID.getValue(),pOriginal->UserID.getValue())!=0)
	{
		pOriginal->UserID.getString(bufOriginal);
		fprintf(fp,"\t\tUserID = %s -> %s    [用户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserID = %s    [用户代码]\n",buf);
	}
	Password.getString(buf);
	if (compare(Password.getValue(),pOriginal->Password.getValue())!=0)
	{
		pOriginal->Password.getString(bufOriginal);
		fprintf(fp,"\t\tPassword = %s -> %s    [用户登录密码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPassword = %s    [用户登录密码]\n",buf);
	}
	IsActive.getString(buf);
	if (compare(IsActive.getValue(),pOriginal->IsActive.getValue())!=0)
	{
		pOriginal->IsActive.getString(bufOriginal);
		fprintf(fp,"\t\tIsActive = %s -> %s    [是否活跃]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIsActive = %s    [是否活跃]\n",buf);
	}
	UserName.getString(buf);
	if (compare(UserName.getValue(),pOriginal->UserName.getValue())!=0)
	{
		pOriginal->UserName.getString(bufOriginal);
		fprintf(fp,"\t\tUserName = %s -> %s    [用户名称]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserName = %s    [用户名称]\n",buf);
	}
	UserType.getString(buf);
	if (compare(UserType.getValue(),pOriginal->UserType.getValue())!=0)
	{
		pOriginal->UserType.getString(bufOriginal);
		fprintf(fp,"\t\tUserType = %s -> %s    [用户类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserType = %s    [用户类型]\n",buf);
	}
	Department.getString(buf);
	if (compare(Department.getValue(),pOriginal->Department.getValue())!=0)
	{
		pOriginal->Department.getString(bufOriginal);
		fprintf(fp,"\t\tDepartment = %s -> %s    [营业部]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDepartment = %s    [营业部]\n",buf);
	}
	GrantFuncSet.getString(buf);
	if (compare(GrantFuncSet.getValue(),pOriginal->GrantFuncSet.getValue())!=0)
	{
		pOriginal->GrantFuncSet.getString(bufOriginal);
		fprintf(fp,"\t\tGrantFuncSet = %s -> %s    [授权功能集]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tGrantFuncSet = %s    [授权功能集]\n",buf);
	}
	CheckIpMacAddr.getString(buf);
	if (compare(CheckIpMacAddr.getValue(),pOriginal->CheckIpMacAddr.getValue())!=0)
	{
		pOriginal->CheckIpMacAddr.getString(bufOriginal);
		fprintf(fp,"\t\tCheckIpMacAddr = %s -> %s    [是否检查IP和MAC]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCheckIpMacAddr = %s    [是否检查IP和MAC]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableUser::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	UserID.getString(buf);
	fprintf(fp,",UserID,%s",buf);	
	Password.getString(buf);
	fprintf(fp,",Password,%s",buf);	
	IsActive.getString(buf);
	fprintf(fp,",IsActive,%s",buf);	
	UserName.getString(buf);
	fprintf(fp,",UserName,%s",buf);	
	UserType.getString(buf);
	fprintf(fp,",UserType,%s",buf);	
	Department.getString(buf);
	fprintf(fp,",Department,%s",buf);	
	GrantFuncSet.getString(buf);
	fprintf(fp,",GrantFuncSet,%s",buf);	
	CheckIpMacAddr.getString(buf);
	fprintf(fp,",CheckIpMacAddr,%s",buf);	
}

void CWriteableUser::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	UserID.getString(buf);
	sprintf(p,"UserID=%s,",buf);
	p+=strlen(p);
	Password.getString(buf);
	sprintf(p,"Password=%s,",buf);
	p+=strlen(p);
	IsActive.getString(buf);
	sprintf(p,"IsActive=%s,",buf);
	p+=strlen(p);
	UserName.getString(buf);
	sprintf(p,"UserName=%s,",buf);
	p+=strlen(p);
	UserType.getString(buf);
	sprintf(p,"UserType=%s,",buf);
	p+=strlen(p);
	Department.getString(buf);
	sprintf(p,"Department=%s,",buf);
	p+=strlen(p);
	GrantFuncSet.getString(buf);
	sprintf(p,"GrantFuncSet=%s,",buf);
	p+=strlen(p);
	CheckIpMacAddr.getString(buf);
	sprintf(p,"CheckIpMacAddr=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableUser::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CUser");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	UserID.getString(buf);
	pLogger->output(indent+1,0,"UserID=%s 用户代码",buf);
	Password.getString(buf);
	pLogger->output(indent+1,0,"Password=%s 用户登录密码",buf);
	IsActive.getString(buf);
	pLogger->output(indent+1,0,"IsActive=%s 是否活跃",buf);
	UserName.getString(buf);
	pLogger->output(indent+1,0,"UserName=%s 用户名称",buf);
	UserType.getString(buf);
	pLogger->output(indent+1,0,"UserType=%s 用户类型",buf);
	Department.getString(buf);
	pLogger->output(indent+1,0,"Department=%s 营业部",buf);
	GrantFuncSet.getString(buf);
	pLogger->output(indent+1,0,"GrantFuncSet=%s 授权功能集",buf);
	CheckIpMacAddr.getString(buf);
	pLogger->output(indent+1,0,"CheckIpMacAddr=%s 是否检查IP和MAC",buf);
	pLogger->output(indent,0,"}");
}

CUserIterator::~CUserIterator(void)
{
}


void CUserIterator::dump(FILE *output)
{
	CUser *pUser;
	
	while ((pUser=next())!=NULL)
	{
		pUser->dump(output);
	}
}



void CWriteableUserInvestor::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,UserID,InvestorID,GrantFuncSet\n");
}
	
void CWriteableUserInvestor::init(void)
{
	BrokerID.clear();
	UserID.clear();
	InvestorID.clear();
	GrantFuncSet.clear();
}

int CWriteableUserInvestor::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableUserInvestor),input)!=sizeof(CWriteableUserInvestor))
		return 0;
	else
		return 1;
}
	
int CWriteableUserInvestor::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserID=token;
		}
		else
		{
			UserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			GrantFuncSet=token;
		}
		else
		{
			GrantFuncSet="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"UserID"))
			{
				UserID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"GrantFuncSet"))
			{
				GrantFuncSet=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableUserInvestor::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableUserInvestor),output)!=sizeof(CWriteableUserInvestor))
		return 0;
	else
		return 1;
}

int CWriteableUserInvestor::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	GrantFuncSet.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableUserInvestor::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCUserInvestor%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	UserID.getString(buf);
	fprintf(fp,"\t\tUserID = %s    [交易用户代码]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);	
	GrantFuncSet.getString(buf);
	fprintf(fp,"\t\tGrantFuncSet = %s    [授权功能集]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableUserInvestor::dumpDiff(FILE *fp, const CWriteableUserInvestor *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCUserInvestor = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	UserID.getString(buf);
	if (compare(UserID.getValue(),pOriginal->UserID.getValue())!=0)
	{
		pOriginal->UserID.getString(bufOriginal);
		fprintf(fp,"\t\tUserID = %s -> %s    [交易用户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserID = %s    [交易用户代码]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);
	}
	GrantFuncSet.getString(buf);
	if (compare(GrantFuncSet.getValue(),pOriginal->GrantFuncSet.getValue())!=0)
	{
		pOriginal->GrantFuncSet.getString(bufOriginal);
		fprintf(fp,"\t\tGrantFuncSet = %s -> %s    [授权功能集]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tGrantFuncSet = %s    [授权功能集]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableUserInvestor::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	UserID.getString(buf);
	fprintf(fp,",UserID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	GrantFuncSet.getString(buf);
	fprintf(fp,",GrantFuncSet,%s",buf);	
}

void CWriteableUserInvestor::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	UserID.getString(buf);
	sprintf(p,"UserID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	GrantFuncSet.getString(buf);
	sprintf(p,"GrantFuncSet=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableUserInvestor::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CUserInvestor");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	UserID.getString(buf);
	pLogger->output(indent+1,0,"UserID=%s 交易用户代码",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编号",buf);
	GrantFuncSet.getString(buf);
	pLogger->output(indent+1,0,"GrantFuncSet=%s 授权功能集",buf);
	pLogger->output(indent,0,"}");
}

CUserInvestorIterator::~CUserInvestorIterator(void)
{
}


void CUserInvestorIterator::dump(FILE *output)
{
	CUserInvestor *pUserInvestor;
	
	while ((pUserInvestor=next())!=NULL)
	{
		pUserInvestor->dump(output);
	}
}



void CWriteableOrderInsertFailed::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,ExchangeID,OrderSysID,InvestorID,UserID,InstrumentID,UserOrderLocalID,OrderPriceType,Direction,OffsetFlag,HedgeFlag,LimitPrice,Volume,TimeCondition,GTDDate,VolumeCondition,MinVolume,StopPrice,ForceCloseReason,IsAutoSuspend,BusinessUnit,UserCustom,BranchID,RecNum,BusinessType,TradingDay,ParticipantID,ClientID,SeatID,InsertTime,OrderLocalID,OrderSource,OrderStatus,CancelTime,CancelUserID,VolumeTraded,VolumeRemain,FrontID,SessionID,FrozenFee,FrozenMargin,FrozenPremium,AccountID,OrderUserID,TradeType,DealFlag,TradeCommision,TradeAmnt,CancleVolume,RequestID,APIID,IPAddress,MacAddress,FTdRecvDown,CoreRecvDown,CoreSendUp,CoreRecvUp,CoreSendDown,FTdSendDown,MarginCombType,InstrumentGroupID,ErrorMsg\n");
}
	
void CWriteableOrderInsertFailed::init(void)
{
	BrokerID.clear();
	ExchangeID.clear();
	OrderSysID.clear();
	InvestorID.clear();
	UserID.clear();
	InstrumentID.clear();
	UserOrderLocalID.clear();
	OrderPriceType.clear();
	Direction.clear();
	OffsetFlag.clear();
	HedgeFlag.clear();
	LimitPrice.clear();
	Volume.clear();
	TimeCondition.clear();
	GTDDate.clear();
	VolumeCondition.clear();
	MinVolume.clear();
	StopPrice.clear();
	ForceCloseReason.clear();
	IsAutoSuspend.clear();
	BusinessUnit.clear();
	UserCustom.clear();
	BranchID.clear();
	RecNum.clear();
	BusinessType.clear();
	TradingDay.clear();
	ParticipantID.clear();
	ClientID.clear();
	SeatID.clear();
	InsertTime.clear();
	OrderLocalID.clear();
	OrderSource.clear();
	OrderStatus.clear();
	CancelTime.clear();
	CancelUserID.clear();
	VolumeTraded.clear();
	VolumeRemain.clear();
	FrontID.clear();
	SessionID.clear();
	FrozenFee.clear();
	FrozenMargin.clear();
	FrozenPremium.clear();
	AccountID.clear();
	OrderUserID.clear();
	TradeType.clear();
	DealFlag.clear();
	TradeCommision.clear();
	TradeAmnt.clear();
	CancleVolume.clear();
	RequestID.clear();
	APIID.clear();
	IPAddress.clear();
	MacAddress.clear();
	FTdRecvDown.clear();
	CoreRecvDown.clear();
	CoreSendUp.clear();
	CoreRecvUp.clear();
	CoreSendDown.clear();
	FTdSendDown.clear();
	MarginCombType.clear();
	InstrumentGroupID.clear();
	ErrorMsg.clear();
	pInvestorAccount=NULL;
	pInvestorPosition=NULL;
	pInstrument=NULL;
	pInvestorMargin=NULL;
	pInvestorFee=NULL;
}

int CWriteableOrderInsertFailed::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableOrderInsertFailed),input)!=sizeof(CWriteableOrderInsertFailed))
		return 0;
	else
		return 1;
}
	
int CWriteableOrderInsertFailed::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderSysID=token;
		}
		else
		{
			OrderSysID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserID=token;
		}
		else
		{
			UserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserOrderLocalID=token;
		}
		else
		{
			UserOrderLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderPriceType=token;
		}
		else
		{
			OrderPriceType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Direction=token;
		}
		else
		{
			Direction="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OffsetFlag=token;
		}
		else
		{
			OffsetFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			HedgeFlag=token;
		}
		else
		{
			HedgeFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LimitPrice=token;
		}
		else
		{
			LimitPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Volume=token;
		}
		else
		{
			Volume="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TimeCondition=token;
		}
		else
		{
			TimeCondition="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			GTDDate=token;
		}
		else
		{
			GTDDate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			VolumeCondition=token;
		}
		else
		{
			VolumeCondition="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MinVolume=token;
		}
		else
		{
			MinVolume="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			StopPrice=token;
		}
		else
		{
			StopPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ForceCloseReason=token;
		}
		else
		{
			ForceCloseReason="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IsAutoSuspend=token;
		}
		else
		{
			IsAutoSuspend="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			BusinessUnit=token;
		}
		else
		{
			BusinessUnit="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserCustom=token;
		}
		else
		{
			UserCustom="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			BranchID=token;
		}
		else
		{
			BranchID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			RecNum=token;
		}
		else
		{
			RecNum="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			BusinessType=token;
		}
		else
		{
			BusinessType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradingDay=token;
		}
		else
		{
			TradingDay="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ParticipantID=token;
		}
		else
		{
			ParticipantID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ClientID=token;
		}
		else
		{
			ClientID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SeatID=token;
		}
		else
		{
			SeatID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InsertTime=token;
		}
		else
		{
			InsertTime="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderLocalID=token;
		}
		else
		{
			OrderLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderSource=token;
		}
		else
		{
			OrderSource="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderStatus=token;
		}
		else
		{
			OrderStatus="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CancelTime=token;
		}
		else
		{
			CancelTime="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CancelUserID=token;
		}
		else
		{
			CancelUserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			VolumeTraded=token;
		}
		else
		{
			VolumeTraded="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			VolumeRemain=token;
		}
		else
		{
			VolumeRemain="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrontID=token;
		}
		else
		{
			FrontID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SessionID=token;
		}
		else
		{
			SessionID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenFee=token;
		}
		else
		{
			FrozenFee="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenMargin=token;
		}
		else
		{
			FrozenMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrozenPremium=token;
		}
		else
		{
			FrozenPremium="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			AccountID=token;
		}
		else
		{
			AccountID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderUserID=token;
		}
		else
		{
			OrderUserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeType=token;
		}
		else
		{
			TradeType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			DealFlag=token;
		}
		else
		{
			DealFlag="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeCommision=token;
		}
		else
		{
			TradeCommision="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeAmnt=token;
		}
		else
		{
			TradeAmnt="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CancleVolume=token;
		}
		else
		{
			CancleVolume="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			RequestID=token;
		}
		else
		{
			RequestID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			APIID=token;
		}
		else
		{
			APIID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IPAddress=token;
		}
		else
		{
			IPAddress="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MacAddress=token;
		}
		else
		{
			MacAddress="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FTdRecvDown=token;
		}
		else
		{
			FTdRecvDown="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreRecvDown=token;
		}
		else
		{
			CoreRecvDown="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreSendUp=token;
		}
		else
		{
			CoreSendUp="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreRecvUp=token;
		}
		else
		{
			CoreRecvUp="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreSendDown=token;
		}
		else
		{
			CoreSendDown="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FTdSendDown=token;
		}
		else
		{
			FTdSendDown="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MarginCombType=token;
		}
		else
		{
			MarginCombType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentGroupID=token;
		}
		else
		{
			InstrumentGroupID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ErrorMsg=token;
		}
		else
		{
			ErrorMsg="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"OrderSysID"))
			{
				OrderSysID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"UserID"))
			{
				UserID=token;
			}
			else if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"UserOrderLocalID"))
			{
				UserOrderLocalID=token;
			}
			else if (!strcmp(fieldName,"OrderPriceType"))
			{
				OrderPriceType=token;
			}
			else if (!strcmp(fieldName,"Direction"))
			{
				Direction=token;
			}
			else if (!strcmp(fieldName,"OffsetFlag"))
			{
				OffsetFlag=token;
			}
			else if (!strcmp(fieldName,"HedgeFlag"))
			{
				HedgeFlag=token;
			}
			else if (!strcmp(fieldName,"LimitPrice"))
			{
				LimitPrice=token;
			}
			else if (!strcmp(fieldName,"Volume"))
			{
				Volume=token;
			}
			else if (!strcmp(fieldName,"TimeCondition"))
			{
				TimeCondition=token;
			}
			else if (!strcmp(fieldName,"GTDDate"))
			{
				GTDDate=token;
			}
			else if (!strcmp(fieldName,"VolumeCondition"))
			{
				VolumeCondition=token;
			}
			else if (!strcmp(fieldName,"MinVolume"))
			{
				MinVolume=token;
			}
			else if (!strcmp(fieldName,"StopPrice"))
			{
				StopPrice=token;
			}
			else if (!strcmp(fieldName,"ForceCloseReason"))
			{
				ForceCloseReason=token;
			}
			else if (!strcmp(fieldName,"IsAutoSuspend"))
			{
				IsAutoSuspend=token;
			}
			else if (!strcmp(fieldName,"BusinessUnit"))
			{
				BusinessUnit=token;
			}
			else if (!strcmp(fieldName,"UserCustom"))
			{
				UserCustom=token;
			}
			else if (!strcmp(fieldName,"BranchID"))
			{
				BranchID=token;
			}
			else if (!strcmp(fieldName,"RecNum"))
			{
				RecNum=token;
			}
			else if (!strcmp(fieldName,"BusinessType"))
			{
				BusinessType=token;
			}
			else if (!strcmp(fieldName,"TradingDay"))
			{
				TradingDay=token;
			}
			else if (!strcmp(fieldName,"ParticipantID"))
			{
				ParticipantID=token;
			}
			else if (!strcmp(fieldName,"ClientID"))
			{
				ClientID=token;
			}
			else if (!strcmp(fieldName,"SeatID"))
			{
				SeatID=token;
			}
			else if (!strcmp(fieldName,"InsertTime"))
			{
				InsertTime=token;
			}
			else if (!strcmp(fieldName,"OrderLocalID"))
			{
				OrderLocalID=token;
			}
			else if (!strcmp(fieldName,"OrderSource"))
			{
				OrderSource=token;
			}
			else if (!strcmp(fieldName,"OrderStatus"))
			{
				OrderStatus=token;
			}
			else if (!strcmp(fieldName,"CancelTime"))
			{
				CancelTime=token;
			}
			else if (!strcmp(fieldName,"CancelUserID"))
			{
				CancelUserID=token;
			}
			else if (!strcmp(fieldName,"VolumeTraded"))
			{
				VolumeTraded=token;
			}
			else if (!strcmp(fieldName,"VolumeRemain"))
			{
				VolumeRemain=token;
			}
			else if (!strcmp(fieldName,"FrontID"))
			{
				FrontID=token;
			}
			else if (!strcmp(fieldName,"SessionID"))
			{
				SessionID=token;
			}
			else if (!strcmp(fieldName,"FrozenFee"))
			{
				FrozenFee=token;
			}
			else if (!strcmp(fieldName,"FrozenMargin"))
			{
				FrozenMargin=token;
			}
			else if (!strcmp(fieldName,"FrozenPremium"))
			{
				FrozenPremium=token;
			}
			else if (!strcmp(fieldName,"AccountID"))
			{
				AccountID=token;
			}
			else if (!strcmp(fieldName,"OrderUserID"))
			{
				OrderUserID=token;
			}
			else if (!strcmp(fieldName,"TradeType"))
			{
				TradeType=token;
			}
			else if (!strcmp(fieldName,"DealFlag"))
			{
				DealFlag=token;
			}
			else if (!strcmp(fieldName,"TradeCommision"))
			{
				TradeCommision=token;
			}
			else if (!strcmp(fieldName,"TradeAmnt"))
			{
				TradeAmnt=token;
			}
			else if (!strcmp(fieldName,"CancleVolume"))
			{
				CancleVolume=token;
			}
			else if (!strcmp(fieldName,"RequestID"))
			{
				RequestID=token;
			}
			else if (!strcmp(fieldName,"APIID"))
			{
				APIID=token;
			}
			else if (!strcmp(fieldName,"IPAddress"))
			{
				IPAddress=token;
			}
			else if (!strcmp(fieldName,"MacAddress"))
			{
				MacAddress=token;
			}
			else if (!strcmp(fieldName,"FTdRecvDown"))
			{
				FTdRecvDown=token;
			}
			else if (!strcmp(fieldName,"CoreRecvDown"))
			{
				CoreRecvDown=token;
			}
			else if (!strcmp(fieldName,"CoreSendUp"))
			{
				CoreSendUp=token;
			}
			else if (!strcmp(fieldName,"CoreRecvUp"))
			{
				CoreRecvUp=token;
			}
			else if (!strcmp(fieldName,"CoreSendDown"))
			{
				CoreSendDown=token;
			}
			else if (!strcmp(fieldName,"FTdSendDown"))
			{
				FTdSendDown=token;
			}
			else if (!strcmp(fieldName,"MarginCombType"))
			{
				MarginCombType=token;
			}
			else if (!strcmp(fieldName,"InstrumentGroupID"))
			{
				InstrumentGroupID=token;
			}
			else if (!strcmp(fieldName,"ErrorMsg"))
			{
				ErrorMsg=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableOrderInsertFailed::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableOrderInsertFailed),output)!=sizeof(CWriteableOrderInsertFailed))
		return 0;
	else
		return 1;
}

int CWriteableOrderInsertFailed::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderSysID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserOrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderPriceType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Direction.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OffsetFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	HedgeFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LimitPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Volume.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TimeCondition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	GTDDate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	VolumeCondition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MinVolume.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	StopPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ForceCloseReason.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IsAutoSuspend.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	BusinessUnit.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserCustom.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	BranchID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	RecNum.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	BusinessType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradingDay.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ParticipantID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ClientID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SeatID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InsertTime.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderSource.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderStatus.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CancelTime.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CancelUserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	VolumeTraded.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	VolumeRemain.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrontID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SessionID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenFee.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrozenPremium.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	AccountID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderUserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	DealFlag.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeCommision.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeAmnt.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CancleVolume.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	RequestID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	APIID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IPAddress.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MacAddress.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FTdRecvDown.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreRecvDown.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreSendUp.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreRecvUp.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreSendDown.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FTdSendDown.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MarginCombType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentGroupID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ErrorMsg.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableOrderInsertFailed::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCOrderInsertFailed%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	OrderSysID.getString(buf);
	fprintf(fp,"\t\tOrderSysID = %s    [系统报单编号]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);	
	UserID.getString(buf);
	fprintf(fp,"\t\tUserID = %s    [用户代码]\n",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	UserOrderLocalID.getString(buf);
	fprintf(fp,"\t\tUserOrderLocalID = %s    [用户本地报单号]\n",buf);	
	OrderPriceType.getString(buf);
	fprintf(fp,"\t\tOrderPriceType = %s    [价格类型]\n",buf);	
	Direction.getString(buf);
	fprintf(fp,"\t\tDirection = %s    [买卖方向]\n",buf);	
	OffsetFlag.getString(buf);
	fprintf(fp,"\t\tOffsetFlag = %s    [开平标志]\n",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);	
	LimitPrice.getString(buf);
	fprintf(fp,"\t\tLimitPrice = %s    [价格]\n",buf);	
	Volume.getString(buf);
	fprintf(fp,"\t\tVolume = %s    [数量]\n",buf);	
	TimeCondition.getString(buf);
	fprintf(fp,"\t\tTimeCondition = %s    [有效期类型]\n",buf);	
	GTDDate.getString(buf);
	fprintf(fp,"\t\tGTDDate = %s    [GTD日期]\n",buf);	
	VolumeCondition.getString(buf);
	fprintf(fp,"\t\tVolumeCondition = %s    [成交量类型]\n",buf);	
	MinVolume.getString(buf);
	fprintf(fp,"\t\tMinVolume = %s    [最小成交量]\n",buf);	
	StopPrice.getString(buf);
	fprintf(fp,"\t\tStopPrice = %s    [止损价]\n",buf);	
	ForceCloseReason.getString(buf);
	fprintf(fp,"\t\tForceCloseReason = %s    [强平原因]\n",buf);	
	IsAutoSuspend.getString(buf);
	fprintf(fp,"\t\tIsAutoSuspend = %s    [自动挂起标志]\n",buf);	
	BusinessUnit.getString(buf);
	fprintf(fp,"\t\tBusinessUnit = %s    [业务单元]\n",buf);	
	UserCustom.getString(buf);
	fprintf(fp,"\t\tUserCustom = %s    [用户自定义域]\n",buf);	
	BranchID.getString(buf);
	fprintf(fp,"\t\tBranchID = %s    [营业部代码]\n",buf);	
	RecNum.getString(buf);
	fprintf(fp,"\t\tRecNum = %s    [记录编号]\n",buf);	
	BusinessType.getString(buf);
	fprintf(fp,"\t\tBusinessType = %s    [业务类别]\n",buf);	
	TradingDay.getString(buf);
	fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,"\t\tParticipantID = %s    [会员编号]\n",buf);	
	ClientID.getString(buf);
	fprintf(fp,"\t\tClientID = %s    [客户号]\n",buf);	
	SeatID.getString(buf);
	fprintf(fp,"\t\tSeatID = %s    [下单席位号]\n",buf);	
	InsertTime.getString(buf);
	fprintf(fp,"\t\tInsertTime = %s    [插入时间]\n",buf);	
	OrderLocalID.getString(buf);
	fprintf(fp,"\t\tOrderLocalID = %s    [本地报单编号]\n",buf);	
	OrderSource.getString(buf);
	fprintf(fp,"\t\tOrderSource = %s    [报单来源]\n",buf);	
	OrderStatus.getString(buf);
	fprintf(fp,"\t\tOrderStatus = %s    [报单状态]\n",buf);	
	CancelTime.getString(buf);
	fprintf(fp,"\t\tCancelTime = %s    [撤销时间]\n",buf);	
	CancelUserID.getString(buf);
	fprintf(fp,"\t\tCancelUserID = %s    [撤单用户编号]\n",buf);	
	VolumeTraded.getString(buf);
	fprintf(fp,"\t\tVolumeTraded = %s    [今成交数量]\n",buf);	
	VolumeRemain.getString(buf);
	fprintf(fp,"\t\tVolumeRemain = %s    [剩余数量]\n",buf);	
	FrontID.getString(buf);
	fprintf(fp,"\t\tFrontID = %s    [前置编号]\n",buf);	
	SessionID.getString(buf);
	fprintf(fp,"\t\tSessionID = %s    [会话编号]\n",buf);	
	FrozenFee.getString(buf);
	fprintf(fp,"\t\tFrozenFee = %s    [冻结手续费]\n",buf);	
	FrozenMargin.getString(buf);
	fprintf(fp,"\t\tFrozenMargin = %s    [冻结的保证金]\n",buf);	
	FrozenPremium.getString(buf);
	fprintf(fp,"\t\tFrozenPremium = %s    [期权权利金收支]\n",buf);	
	AccountID.getString(buf);
	fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);	
	OrderUserID.getString(buf);
	fprintf(fp,"\t\tOrderUserID = %s    [下单用户编号]\n",buf);	
	TradeType.getString(buf);
	fprintf(fp,"\t\tTradeType = %s    [交易类型]\n",buf);	
	DealFlag.getString(buf);
	fprintf(fp,"\t\tDealFlag = %s    [处理标志]\n",buf);	
	TradeCommision.getString(buf);
	fprintf(fp,"\t\tTradeCommision = %s    [已成交佣金]\n",buf);	
	TradeAmnt.getString(buf);
	fprintf(fp,"\t\tTradeAmnt = %s    [成交金额]\n",buf);	
	CancleVolume.getString(buf);
	fprintf(fp,"\t\tCancleVolume = %s    [撤单数量]\n",buf);	
	RequestID.getString(buf);
	fprintf(fp,"\t\tRequestID = %s    [请求编号]\n",buf);	
	APIID.getString(buf);
	fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);	
	IPAddress.getString(buf);
	fprintf(fp,"\t\tIPAddress = %s    [下单IP地址]\n",buf);	
	MacAddress.getString(buf);
	fprintf(fp,"\t\tMacAddress = %s    [下单MAC地址]\n",buf);	
	FTdRecvDown.getString(buf);
	fprintf(fp,"\t\tFTdRecvDown = %s    [Ftdengine接受下层时间戳]\n",buf);	
	CoreRecvDown.getString(buf);
	fprintf(fp,"\t\tCoreRecvDown = %s    [接受下层时间戳]\n",buf);	
	CoreSendUp.getString(buf);
	fprintf(fp,"\t\tCoreSendUp = %s    [发送上层时间戳]\n",buf);	
	CoreRecvUp.getString(buf);
	fprintf(fp,"\t\tCoreRecvUp = %s    [接受上层时间戳]\n",buf);	
	CoreSendDown.getString(buf);
	fprintf(fp,"\t\tCoreSendDown = %s    [发送下层时间戳]\n",buf);	
	FTdSendDown.getString(buf);
	fprintf(fp,"\t\tFTdSendDown = %s    [Ftdengine接受下层时间戳]\n",buf);	
	MarginCombType.getString(buf);
	fprintf(fp,"\t\tMarginCombType = %s    [保证金组合类型]\n",buf);	
	InstrumentGroupID.getString(buf);
	fprintf(fp,"\t\tInstrumentGroupID = %s    [合约组代码]\n",buf);	
	ErrorMsg.getString(buf);
	fprintf(fp,"\t\tErrorMsg = %s    [错误信息]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableOrderInsertFailed::dumpDiff(FILE *fp, const CWriteableOrderInsertFailed *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCOrderInsertFailed = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	OrderSysID.getString(buf);
	if (compare(OrderSysID.getValue(),pOriginal->OrderSysID.getValue())!=0)
	{
		pOriginal->OrderSysID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderSysID = %s -> %s    [系统报单编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderSysID = %s    [系统报单编号]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);
	}
	UserID.getString(buf);
	if (compare(UserID.getValue(),pOriginal->UserID.getValue())!=0)
	{
		pOriginal->UserID.getString(bufOriginal);
		fprintf(fp,"\t\tUserID = %s -> %s    [用户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserID = %s    [用户代码]\n",buf);
	}
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	UserOrderLocalID.getString(buf);
	if (compare(UserOrderLocalID.getValue(),pOriginal->UserOrderLocalID.getValue())!=0)
	{
		pOriginal->UserOrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tUserOrderLocalID = %s -> %s    [用户本地报单号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserOrderLocalID = %s    [用户本地报单号]\n",buf);
	}
	OrderPriceType.getString(buf);
	if (compare(OrderPriceType.getValue(),pOriginal->OrderPriceType.getValue())!=0)
	{
		pOriginal->OrderPriceType.getString(bufOriginal);
		fprintf(fp,"\t\tOrderPriceType = %s -> %s    [价格类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderPriceType = %s    [价格类型]\n",buf);
	}
	Direction.getString(buf);
	if (compare(Direction.getValue(),pOriginal->Direction.getValue())!=0)
	{
		pOriginal->Direction.getString(bufOriginal);
		fprintf(fp,"\t\tDirection = %s -> %s    [买卖方向]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDirection = %s    [买卖方向]\n",buf);
	}
	OffsetFlag.getString(buf);
	if (compare(OffsetFlag.getValue(),pOriginal->OffsetFlag.getValue())!=0)
	{
		pOriginal->OffsetFlag.getString(bufOriginal);
		fprintf(fp,"\t\tOffsetFlag = %s -> %s    [开平标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOffsetFlag = %s    [开平标志]\n",buf);
	}
	HedgeFlag.getString(buf);
	if (compare(HedgeFlag.getValue(),pOriginal->HedgeFlag.getValue())!=0)
	{
		pOriginal->HedgeFlag.getString(bufOriginal);
		fprintf(fp,"\t\tHedgeFlag = %s -> %s    [投机套保标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tHedgeFlag = %s    [投机套保标志]\n",buf);
	}
	LimitPrice.getString(buf);
	if (compare(LimitPrice.getValue(),pOriginal->LimitPrice.getValue())!=0)
	{
		pOriginal->LimitPrice.getString(bufOriginal);
		fprintf(fp,"\t\tLimitPrice = %s -> %s    [价格]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLimitPrice = %s    [价格]\n",buf);
	}
	Volume.getString(buf);
	if (compare(Volume.getValue(),pOriginal->Volume.getValue())!=0)
	{
		pOriginal->Volume.getString(bufOriginal);
		fprintf(fp,"\t\tVolume = %s -> %s    [数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tVolume = %s    [数量]\n",buf);
	}
	TimeCondition.getString(buf);
	if (compare(TimeCondition.getValue(),pOriginal->TimeCondition.getValue())!=0)
	{
		pOriginal->TimeCondition.getString(bufOriginal);
		fprintf(fp,"\t\tTimeCondition = %s -> %s    [有效期类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTimeCondition = %s    [有效期类型]\n",buf);
	}
	GTDDate.getString(buf);
	if (compare(GTDDate.getValue(),pOriginal->GTDDate.getValue())!=0)
	{
		pOriginal->GTDDate.getString(bufOriginal);
		fprintf(fp,"\t\tGTDDate = %s -> %s    [GTD日期]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tGTDDate = %s    [GTD日期]\n",buf);
	}
	VolumeCondition.getString(buf);
	if (compare(VolumeCondition.getValue(),pOriginal->VolumeCondition.getValue())!=0)
	{
		pOriginal->VolumeCondition.getString(bufOriginal);
		fprintf(fp,"\t\tVolumeCondition = %s -> %s    [成交量类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tVolumeCondition = %s    [成交量类型]\n",buf);
	}
	MinVolume.getString(buf);
	if (compare(MinVolume.getValue(),pOriginal->MinVolume.getValue())!=0)
	{
		pOriginal->MinVolume.getString(bufOriginal);
		fprintf(fp,"\t\tMinVolume = %s -> %s    [最小成交量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMinVolume = %s    [最小成交量]\n",buf);
	}
	StopPrice.getString(buf);
	if (compare(StopPrice.getValue(),pOriginal->StopPrice.getValue())!=0)
	{
		pOriginal->StopPrice.getString(bufOriginal);
		fprintf(fp,"\t\tStopPrice = %s -> %s    [止损价]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tStopPrice = %s    [止损价]\n",buf);
	}
	ForceCloseReason.getString(buf);
	if (compare(ForceCloseReason.getValue(),pOriginal->ForceCloseReason.getValue())!=0)
	{
		pOriginal->ForceCloseReason.getString(bufOriginal);
		fprintf(fp,"\t\tForceCloseReason = %s -> %s    [强平原因]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tForceCloseReason = %s    [强平原因]\n",buf);
	}
	IsAutoSuspend.getString(buf);
	if (compare(IsAutoSuspend.getValue(),pOriginal->IsAutoSuspend.getValue())!=0)
	{
		pOriginal->IsAutoSuspend.getString(bufOriginal);
		fprintf(fp,"\t\tIsAutoSuspend = %s -> %s    [自动挂起标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIsAutoSuspend = %s    [自动挂起标志]\n",buf);
	}
	BusinessUnit.getString(buf);
	if (compare(BusinessUnit.getValue(),pOriginal->BusinessUnit.getValue())!=0)
	{
		pOriginal->BusinessUnit.getString(bufOriginal);
		fprintf(fp,"\t\tBusinessUnit = %s -> %s    [业务单元]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBusinessUnit = %s    [业务单元]\n",buf);
	}
	UserCustom.getString(buf);
	if (compare(UserCustom.getValue(),pOriginal->UserCustom.getValue())!=0)
	{
		pOriginal->UserCustom.getString(bufOriginal);
		fprintf(fp,"\t\tUserCustom = %s -> %s    [用户自定义域]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserCustom = %s    [用户自定义域]\n",buf);
	}
	BranchID.getString(buf);
	if (compare(BranchID.getValue(),pOriginal->BranchID.getValue())!=0)
	{
		pOriginal->BranchID.getString(bufOriginal);
		fprintf(fp,"\t\tBranchID = %s -> %s    [营业部代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBranchID = %s    [营业部代码]\n",buf);
	}
	RecNum.getString(buf);
	if (compare(RecNum.getValue(),pOriginal->RecNum.getValue())!=0)
	{
		pOriginal->RecNum.getString(bufOriginal);
		fprintf(fp,"\t\tRecNum = %s -> %s    [记录编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tRecNum = %s    [记录编号]\n",buf);
	}
	BusinessType.getString(buf);
	if (compare(BusinessType.getValue(),pOriginal->BusinessType.getValue())!=0)
	{
		pOriginal->BusinessType.getString(bufOriginal);
		fprintf(fp,"\t\tBusinessType = %s -> %s    [业务类别]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBusinessType = %s    [业务类别]\n",buf);
	}
	TradingDay.getString(buf);
	if (compare(TradingDay.getValue(),pOriginal->TradingDay.getValue())!=0)
	{
		pOriginal->TradingDay.getString(bufOriginal);
		fprintf(fp,"\t\tTradingDay = %s -> %s    [交易日]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);
	}
	ParticipantID.getString(buf);
	if (compare(ParticipantID.getValue(),pOriginal->ParticipantID.getValue())!=0)
	{
		pOriginal->ParticipantID.getString(bufOriginal);
		fprintf(fp,"\t\tParticipantID = %s -> %s    [会员编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tParticipantID = %s    [会员编号]\n",buf);
	}
	ClientID.getString(buf);
	if (compare(ClientID.getValue(),pOriginal->ClientID.getValue())!=0)
	{
		pOriginal->ClientID.getString(bufOriginal);
		fprintf(fp,"\t\tClientID = %s -> %s    [客户号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tClientID = %s    [客户号]\n",buf);
	}
	SeatID.getString(buf);
	if (compare(SeatID.getValue(),pOriginal->SeatID.getValue())!=0)
	{
		pOriginal->SeatID.getString(bufOriginal);
		fprintf(fp,"\t\tSeatID = %s -> %s    [下单席位号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSeatID = %s    [下单席位号]\n",buf);
	}
	InsertTime.getString(buf);
	if (compare(InsertTime.getValue(),pOriginal->InsertTime.getValue())!=0)
	{
		pOriginal->InsertTime.getString(bufOriginal);
		fprintf(fp,"\t\tInsertTime = %s -> %s    [插入时间]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInsertTime = %s    [插入时间]\n",buf);
	}
	OrderLocalID.getString(buf);
	if (compare(OrderLocalID.getValue(),pOriginal->OrderLocalID.getValue())!=0)
	{
		pOriginal->OrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderLocalID = %s -> %s    [本地报单编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderLocalID = %s    [本地报单编号]\n",buf);
	}
	OrderSource.getString(buf);
	if (compare(OrderSource.getValue(),pOriginal->OrderSource.getValue())!=0)
	{
		pOriginal->OrderSource.getString(bufOriginal);
		fprintf(fp,"\t\tOrderSource = %s -> %s    [报单来源]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderSource = %s    [报单来源]\n",buf);
	}
	OrderStatus.getString(buf);
	if (compare(OrderStatus.getValue(),pOriginal->OrderStatus.getValue())!=0)
	{
		pOriginal->OrderStatus.getString(bufOriginal);
		fprintf(fp,"\t\tOrderStatus = %s -> %s    [报单状态]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderStatus = %s    [报单状态]\n",buf);
	}
	CancelTime.getString(buf);
	if (compare(CancelTime.getValue(),pOriginal->CancelTime.getValue())!=0)
	{
		pOriginal->CancelTime.getString(bufOriginal);
		fprintf(fp,"\t\tCancelTime = %s -> %s    [撤销时间]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCancelTime = %s    [撤销时间]\n",buf);
	}
	CancelUserID.getString(buf);
	if (compare(CancelUserID.getValue(),pOriginal->CancelUserID.getValue())!=0)
	{
		pOriginal->CancelUserID.getString(bufOriginal);
		fprintf(fp,"\t\tCancelUserID = %s -> %s    [撤单用户编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCancelUserID = %s    [撤单用户编号]\n",buf);
	}
	VolumeTraded.getString(buf);
	if (compare(VolumeTraded.getValue(),pOriginal->VolumeTraded.getValue())!=0)
	{
		pOriginal->VolumeTraded.getString(bufOriginal);
		fprintf(fp,"\t\tVolumeTraded = %s -> %s    [今成交数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tVolumeTraded = %s    [今成交数量]\n",buf);
	}
	VolumeRemain.getString(buf);
	if (compare(VolumeRemain.getValue(),pOriginal->VolumeRemain.getValue())!=0)
	{
		pOriginal->VolumeRemain.getString(bufOriginal);
		fprintf(fp,"\t\tVolumeRemain = %s -> %s    [剩余数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tVolumeRemain = %s    [剩余数量]\n",buf);
	}
	FrontID.getString(buf);
	if (compare(FrontID.getValue(),pOriginal->FrontID.getValue())!=0)
	{
		pOriginal->FrontID.getString(bufOriginal);
		fprintf(fp,"\t\tFrontID = %s -> %s    [前置编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrontID = %s    [前置编号]\n",buf);
	}
	SessionID.getString(buf);
	if (compare(SessionID.getValue(),pOriginal->SessionID.getValue())!=0)
	{
		pOriginal->SessionID.getString(bufOriginal);
		fprintf(fp,"\t\tSessionID = %s -> %s    [会话编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSessionID = %s    [会话编号]\n",buf);
	}
	FrozenFee.getString(buf);
	if (compare(FrozenFee.getValue(),pOriginal->FrozenFee.getValue())!=0)
	{
		pOriginal->FrozenFee.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenFee = %s -> %s    [冻结手续费]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenFee = %s    [冻结手续费]\n",buf);
	}
	FrozenMargin.getString(buf);
	if (compare(FrozenMargin.getValue(),pOriginal->FrozenMargin.getValue())!=0)
	{
		pOriginal->FrozenMargin.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenMargin = %s -> %s    [冻结的保证金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenMargin = %s    [冻结的保证金]\n",buf);
	}
	FrozenPremium.getString(buf);
	if (compare(FrozenPremium.getValue(),pOriginal->FrozenPremium.getValue())!=0)
	{
		pOriginal->FrozenPremium.getString(bufOriginal);
		fprintf(fp,"\t\tFrozenPremium = %s -> %s    [期权权利金收支]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrozenPremium = %s    [期权权利金收支]\n",buf);
	}
	AccountID.getString(buf);
	if (compare(AccountID.getValue(),pOriginal->AccountID.getValue())!=0)
	{
		pOriginal->AccountID.getString(bufOriginal);
		fprintf(fp,"\t\tAccountID = %s -> %s    [资金帐号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAccountID = %s    [资金帐号]\n",buf);
	}
	OrderUserID.getString(buf);
	if (compare(OrderUserID.getValue(),pOriginal->OrderUserID.getValue())!=0)
	{
		pOriginal->OrderUserID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderUserID = %s -> %s    [下单用户编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderUserID = %s    [下单用户编号]\n",buf);
	}
	TradeType.getString(buf);
	if (compare(TradeType.getValue(),pOriginal->TradeType.getValue())!=0)
	{
		pOriginal->TradeType.getString(bufOriginal);
		fprintf(fp,"\t\tTradeType = %s -> %s    [交易类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeType = %s    [交易类型]\n",buf);
	}
	DealFlag.getString(buf);
	if (compare(DealFlag.getValue(),pOriginal->DealFlag.getValue())!=0)
	{
		pOriginal->DealFlag.getString(bufOriginal);
		fprintf(fp,"\t\tDealFlag = %s -> %s    [处理标志]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDealFlag = %s    [处理标志]\n",buf);
	}
	TradeCommision.getString(buf);
	if (compare(TradeCommision.getValue(),pOriginal->TradeCommision.getValue())!=0)
	{
		pOriginal->TradeCommision.getString(bufOriginal);
		fprintf(fp,"\t\tTradeCommision = %s -> %s    [已成交佣金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeCommision = %s    [已成交佣金]\n",buf);
	}
	TradeAmnt.getString(buf);
	if (compare(TradeAmnt.getValue(),pOriginal->TradeAmnt.getValue())!=0)
	{
		pOriginal->TradeAmnt.getString(bufOriginal);
		fprintf(fp,"\t\tTradeAmnt = %s -> %s    [成交金额]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeAmnt = %s    [成交金额]\n",buf);
	}
	CancleVolume.getString(buf);
	if (compare(CancleVolume.getValue(),pOriginal->CancleVolume.getValue())!=0)
	{
		pOriginal->CancleVolume.getString(bufOriginal);
		fprintf(fp,"\t\tCancleVolume = %s -> %s    [撤单数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCancleVolume = %s    [撤单数量]\n",buf);
	}
	RequestID.getString(buf);
	if (compare(RequestID.getValue(),pOriginal->RequestID.getValue())!=0)
	{
		pOriginal->RequestID.getString(bufOriginal);
		fprintf(fp,"\t\tRequestID = %s -> %s    [请求编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tRequestID = %s    [请求编号]\n",buf);
	}
	APIID.getString(buf);
	if (compare(APIID.getValue(),pOriginal->APIID.getValue())!=0)
	{
		pOriginal->APIID.getString(bufOriginal);
		fprintf(fp,"\t\tAPIID = %s -> %s    [通道对应的APIID]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);
	}
	IPAddress.getString(buf);
	if (compare(IPAddress.getValue(),pOriginal->IPAddress.getValue())!=0)
	{
		pOriginal->IPAddress.getString(bufOriginal);
		fprintf(fp,"\t\tIPAddress = %s -> %s    [下单IP地址]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIPAddress = %s    [下单IP地址]\n",buf);
	}
	MacAddress.getString(buf);
	if (compare(MacAddress.getValue(),pOriginal->MacAddress.getValue())!=0)
	{
		pOriginal->MacAddress.getString(bufOriginal);
		fprintf(fp,"\t\tMacAddress = %s -> %s    [下单MAC地址]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMacAddress = %s    [下单MAC地址]\n",buf);
	}
	FTdRecvDown.getString(buf);
	if (compare(FTdRecvDown.getValue(),pOriginal->FTdRecvDown.getValue())!=0)
	{
		pOriginal->FTdRecvDown.getString(bufOriginal);
		fprintf(fp,"\t\tFTdRecvDown = %s -> %s    [Ftdengine接受下层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFTdRecvDown = %s    [Ftdengine接受下层时间戳]\n",buf);
	}
	CoreRecvDown.getString(buf);
	if (compare(CoreRecvDown.getValue(),pOriginal->CoreRecvDown.getValue())!=0)
	{
		pOriginal->CoreRecvDown.getString(bufOriginal);
		fprintf(fp,"\t\tCoreRecvDown = %s -> %s    [接受下层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreRecvDown = %s    [接受下层时间戳]\n",buf);
	}
	CoreSendUp.getString(buf);
	if (compare(CoreSendUp.getValue(),pOriginal->CoreSendUp.getValue())!=0)
	{
		pOriginal->CoreSendUp.getString(bufOriginal);
		fprintf(fp,"\t\tCoreSendUp = %s -> %s    [发送上层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreSendUp = %s    [发送上层时间戳]\n",buf);
	}
	CoreRecvUp.getString(buf);
	if (compare(CoreRecvUp.getValue(),pOriginal->CoreRecvUp.getValue())!=0)
	{
		pOriginal->CoreRecvUp.getString(bufOriginal);
		fprintf(fp,"\t\tCoreRecvUp = %s -> %s    [接受上层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreRecvUp = %s    [接受上层时间戳]\n",buf);
	}
	CoreSendDown.getString(buf);
	if (compare(CoreSendDown.getValue(),pOriginal->CoreSendDown.getValue())!=0)
	{
		pOriginal->CoreSendDown.getString(bufOriginal);
		fprintf(fp,"\t\tCoreSendDown = %s -> %s    [发送下层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreSendDown = %s    [发送下层时间戳]\n",buf);
	}
	FTdSendDown.getString(buf);
	if (compare(FTdSendDown.getValue(),pOriginal->FTdSendDown.getValue())!=0)
	{
		pOriginal->FTdSendDown.getString(bufOriginal);
		fprintf(fp,"\t\tFTdSendDown = %s -> %s    [Ftdengine接受下层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFTdSendDown = %s    [Ftdengine接受下层时间戳]\n",buf);
	}
	MarginCombType.getString(buf);
	if (compare(MarginCombType.getValue(),pOriginal->MarginCombType.getValue())!=0)
	{
		pOriginal->MarginCombType.getString(bufOriginal);
		fprintf(fp,"\t\tMarginCombType = %s -> %s    [保证金组合类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMarginCombType = %s    [保证金组合类型]\n",buf);
	}
	InstrumentGroupID.getString(buf);
	if (compare(InstrumentGroupID.getValue(),pOriginal->InstrumentGroupID.getValue())!=0)
	{
		pOriginal->InstrumentGroupID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentGroupID = %s -> %s    [合约组代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentGroupID = %s    [合约组代码]\n",buf);
	}
	ErrorMsg.getString(buf);
	if (compare(ErrorMsg.getValue(),pOriginal->ErrorMsg.getValue())!=0)
	{
		pOriginal->ErrorMsg.getString(bufOriginal);
		fprintf(fp,"\t\tErrorMsg = %s -> %s    [错误信息]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tErrorMsg = %s    [错误信息]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableOrderInsertFailed::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	OrderSysID.getString(buf);
	fprintf(fp,",OrderSysID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	UserID.getString(buf);
	fprintf(fp,",UserID,%s",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	UserOrderLocalID.getString(buf);
	fprintf(fp,",UserOrderLocalID,%s",buf);	
	OrderPriceType.getString(buf);
	fprintf(fp,",OrderPriceType,%s",buf);	
	Direction.getString(buf);
	fprintf(fp,",Direction,%s",buf);	
	OffsetFlag.getString(buf);
	fprintf(fp,",OffsetFlag,%s",buf);	
	HedgeFlag.getString(buf);
	fprintf(fp,",HedgeFlag,%s",buf);	
	LimitPrice.getString(buf);
	fprintf(fp,",LimitPrice,%s",buf);	
	Volume.getString(buf);
	fprintf(fp,",Volume,%s",buf);	
	TimeCondition.getString(buf);
	fprintf(fp,",TimeCondition,%s",buf);	
	GTDDate.getString(buf);
	fprintf(fp,",GTDDate,%s",buf);	
	VolumeCondition.getString(buf);
	fprintf(fp,",VolumeCondition,%s",buf);	
	MinVolume.getString(buf);
	fprintf(fp,",MinVolume,%s",buf);	
	StopPrice.getString(buf);
	fprintf(fp,",StopPrice,%s",buf);	
	ForceCloseReason.getString(buf);
	fprintf(fp,",ForceCloseReason,%s",buf);	
	IsAutoSuspend.getString(buf);
	fprintf(fp,",IsAutoSuspend,%s",buf);	
	BusinessUnit.getString(buf);
	fprintf(fp,",BusinessUnit,%s",buf);	
	UserCustom.getString(buf);
	fprintf(fp,",UserCustom,%s",buf);	
	BranchID.getString(buf);
	fprintf(fp,",BranchID,%s",buf);	
	RecNum.getString(buf);
	fprintf(fp,",RecNum,%s",buf);	
	BusinessType.getString(buf);
	fprintf(fp,",BusinessType,%s",buf);	
	TradingDay.getString(buf);
	fprintf(fp,",TradingDay,%s",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,",ParticipantID,%s",buf);	
	ClientID.getString(buf);
	fprintf(fp,",ClientID,%s",buf);	
	SeatID.getString(buf);
	fprintf(fp,",SeatID,%s",buf);	
	InsertTime.getString(buf);
	fprintf(fp,",InsertTime,%s",buf);	
	OrderLocalID.getString(buf);
	fprintf(fp,",OrderLocalID,%s",buf);	
	OrderSource.getString(buf);
	fprintf(fp,",OrderSource,%s",buf);	
	OrderStatus.getString(buf);
	fprintf(fp,",OrderStatus,%s",buf);	
	CancelTime.getString(buf);
	fprintf(fp,",CancelTime,%s",buf);	
	CancelUserID.getString(buf);
	fprintf(fp,",CancelUserID,%s",buf);	
	VolumeTraded.getString(buf);
	fprintf(fp,",VolumeTraded,%s",buf);	
	VolumeRemain.getString(buf);
	fprintf(fp,",VolumeRemain,%s",buf);	
	FrontID.getString(buf);
	fprintf(fp,",FrontID,%s",buf);	
	SessionID.getString(buf);
	fprintf(fp,",SessionID,%s",buf);	
	FrozenFee.getString(buf);
	fprintf(fp,",FrozenFee,%s",buf);	
	FrozenMargin.getString(buf);
	fprintf(fp,",FrozenMargin,%s",buf);	
	FrozenPremium.getString(buf);
	fprintf(fp,",FrozenPremium,%s",buf);	
	AccountID.getString(buf);
	fprintf(fp,",AccountID,%s",buf);	
	OrderUserID.getString(buf);
	fprintf(fp,",OrderUserID,%s",buf);	
	TradeType.getString(buf);
	fprintf(fp,",TradeType,%s",buf);	
	DealFlag.getString(buf);
	fprintf(fp,",DealFlag,%s",buf);	
	TradeCommision.getString(buf);
	fprintf(fp,",TradeCommision,%s",buf);	
	TradeAmnt.getString(buf);
	fprintf(fp,",TradeAmnt,%s",buf);	
	CancleVolume.getString(buf);
	fprintf(fp,",CancleVolume,%s",buf);	
	RequestID.getString(buf);
	fprintf(fp,",RequestID,%s",buf);	
	APIID.getString(buf);
	fprintf(fp,",APIID,%s",buf);	
	IPAddress.getString(buf);
	fprintf(fp,",IPAddress,%s",buf);	
	MacAddress.getString(buf);
	fprintf(fp,",MacAddress,%s",buf);	
	FTdRecvDown.getString(buf);
	fprintf(fp,",FTdRecvDown,%s",buf);	
	CoreRecvDown.getString(buf);
	fprintf(fp,",CoreRecvDown,%s",buf);	
	CoreSendUp.getString(buf);
	fprintf(fp,",CoreSendUp,%s",buf);	
	CoreRecvUp.getString(buf);
	fprintf(fp,",CoreRecvUp,%s",buf);	
	CoreSendDown.getString(buf);
	fprintf(fp,",CoreSendDown,%s",buf);	
	FTdSendDown.getString(buf);
	fprintf(fp,",FTdSendDown,%s",buf);	
	MarginCombType.getString(buf);
	fprintf(fp,",MarginCombType,%s",buf);	
	InstrumentGroupID.getString(buf);
	fprintf(fp,",InstrumentGroupID,%s",buf);	
	ErrorMsg.getString(buf);
	fprintf(fp,",ErrorMsg,%s",buf);	
}

void CWriteableOrderInsertFailed::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	OrderSysID.getString(buf);
	sprintf(p,"OrderSysID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	UserID.getString(buf);
	sprintf(p,"UserID=%s,",buf);
	p+=strlen(p);
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	UserOrderLocalID.getString(buf);
	sprintf(p,"UserOrderLocalID=%s,",buf);
	p+=strlen(p);
	OrderPriceType.getString(buf);
	sprintf(p,"OrderPriceType=%s,",buf);
	p+=strlen(p);
	Direction.getString(buf);
	sprintf(p,"Direction=%s,",buf);
	p+=strlen(p);
	OffsetFlag.getString(buf);
	sprintf(p,"OffsetFlag=%s,",buf);
	p+=strlen(p);
	HedgeFlag.getString(buf);
	sprintf(p,"HedgeFlag=%s,",buf);
	p+=strlen(p);
	LimitPrice.getString(buf);
	sprintf(p,"LimitPrice=%s,",buf);
	p+=strlen(p);
	Volume.getString(buf);
	sprintf(p,"Volume=%s,",buf);
	p+=strlen(p);
	TimeCondition.getString(buf);
	sprintf(p,"TimeCondition=%s,",buf);
	p+=strlen(p);
	GTDDate.getString(buf);
	sprintf(p,"GTDDate=%s,",buf);
	p+=strlen(p);
	VolumeCondition.getString(buf);
	sprintf(p,"VolumeCondition=%s,",buf);
	p+=strlen(p);
	MinVolume.getString(buf);
	sprintf(p,"MinVolume=%s,",buf);
	p+=strlen(p);
	StopPrice.getString(buf);
	sprintf(p,"StopPrice=%s,",buf);
	p+=strlen(p);
	ForceCloseReason.getString(buf);
	sprintf(p,"ForceCloseReason=%s,",buf);
	p+=strlen(p);
	IsAutoSuspend.getString(buf);
	sprintf(p,"IsAutoSuspend=%s,",buf);
	p+=strlen(p);
	BusinessUnit.getString(buf);
	sprintf(p,"BusinessUnit=%s,",buf);
	p+=strlen(p);
	UserCustom.getString(buf);
	sprintf(p,"UserCustom=%s,",buf);
	p+=strlen(p);
	BranchID.getString(buf);
	sprintf(p,"BranchID=%s,",buf);
	p+=strlen(p);
	RecNum.getString(buf);
	sprintf(p,"RecNum=%s,",buf);
	p+=strlen(p);
	BusinessType.getString(buf);
	sprintf(p,"BusinessType=%s,",buf);
	p+=strlen(p);
	TradingDay.getString(buf);
	sprintf(p,"TradingDay=%s,",buf);
	p+=strlen(p);
	ParticipantID.getString(buf);
	sprintf(p,"ParticipantID=%s,",buf);
	p+=strlen(p);
	ClientID.getString(buf);
	sprintf(p,"ClientID=%s,",buf);
	p+=strlen(p);
	SeatID.getString(buf);
	sprintf(p,"SeatID=%s,",buf);
	p+=strlen(p);
	InsertTime.getString(buf);
	sprintf(p,"InsertTime=%s,",buf);
	p+=strlen(p);
	OrderLocalID.getString(buf);
	sprintf(p,"OrderLocalID=%s,",buf);
	p+=strlen(p);
	OrderSource.getString(buf);
	sprintf(p,"OrderSource=%s,",buf);
	p+=strlen(p);
	OrderStatus.getString(buf);
	sprintf(p,"OrderStatus=%s,",buf);
	p+=strlen(p);
	CancelTime.getString(buf);
	sprintf(p,"CancelTime=%s,",buf);
	p+=strlen(p);
	CancelUserID.getString(buf);
	sprintf(p,"CancelUserID=%s,",buf);
	p+=strlen(p);
	VolumeTraded.getString(buf);
	sprintf(p,"VolumeTraded=%s,",buf);
	p+=strlen(p);
	VolumeRemain.getString(buf);
	sprintf(p,"VolumeRemain=%s,",buf);
	p+=strlen(p);
	FrontID.getString(buf);
	sprintf(p,"FrontID=%s,",buf);
	p+=strlen(p);
	SessionID.getString(buf);
	sprintf(p,"SessionID=%s,",buf);
	p+=strlen(p);
	FrozenFee.getString(buf);
	sprintf(p,"FrozenFee=%s,",buf);
	p+=strlen(p);
	FrozenMargin.getString(buf);
	sprintf(p,"FrozenMargin=%s,",buf);
	p+=strlen(p);
	FrozenPremium.getString(buf);
	sprintf(p,"FrozenPremium=%s,",buf);
	p+=strlen(p);
	AccountID.getString(buf);
	sprintf(p,"AccountID=%s,",buf);
	p+=strlen(p);
	OrderUserID.getString(buf);
	sprintf(p,"OrderUserID=%s,",buf);
	p+=strlen(p);
	TradeType.getString(buf);
	sprintf(p,"TradeType=%s,",buf);
	p+=strlen(p);
	DealFlag.getString(buf);
	sprintf(p,"DealFlag=%s,",buf);
	p+=strlen(p);
	TradeCommision.getString(buf);
	sprintf(p,"TradeCommision=%s,",buf);
	p+=strlen(p);
	TradeAmnt.getString(buf);
	sprintf(p,"TradeAmnt=%s,",buf);
	p+=strlen(p);
	CancleVolume.getString(buf);
	sprintf(p,"CancleVolume=%s,",buf);
	p+=strlen(p);
	RequestID.getString(buf);
	sprintf(p,"RequestID=%s,",buf);
	p+=strlen(p);
	APIID.getString(buf);
	sprintf(p,"APIID=%s,",buf);
	p+=strlen(p);
	IPAddress.getString(buf);
	sprintf(p,"IPAddress=%s,",buf);
	p+=strlen(p);
	MacAddress.getString(buf);
	sprintf(p,"MacAddress=%s,",buf);
	p+=strlen(p);
	FTdRecvDown.getString(buf);
	sprintf(p,"FTdRecvDown=%s,",buf);
	p+=strlen(p);
	CoreRecvDown.getString(buf);
	sprintf(p,"CoreRecvDown=%s,",buf);
	p+=strlen(p);
	CoreSendUp.getString(buf);
	sprintf(p,"CoreSendUp=%s,",buf);
	p+=strlen(p);
	CoreRecvUp.getString(buf);
	sprintf(p,"CoreRecvUp=%s,",buf);
	p+=strlen(p);
	CoreSendDown.getString(buf);
	sprintf(p,"CoreSendDown=%s,",buf);
	p+=strlen(p);
	FTdSendDown.getString(buf);
	sprintf(p,"FTdSendDown=%s,",buf);
	p+=strlen(p);
	MarginCombType.getString(buf);
	sprintf(p,"MarginCombType=%s,",buf);
	p+=strlen(p);
	InstrumentGroupID.getString(buf);
	sprintf(p,"InstrumentGroupID=%s,",buf);
	p+=strlen(p);
	ErrorMsg.getString(buf);
	sprintf(p,"ErrorMsg=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableOrderInsertFailed::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"COrderInsertFailed");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	OrderSysID.getString(buf);
	pLogger->output(indent+1,0,"OrderSysID=%s 系统报单编号",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编号",buf);
	UserID.getString(buf);
	pLogger->output(indent+1,0,"UserID=%s 用户代码",buf);
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	UserOrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"UserOrderLocalID=%s 用户本地报单号",buf);
	OrderPriceType.getString(buf);
	pLogger->output(indent+1,0,"OrderPriceType=%s 价格类型",buf);
	Direction.getString(buf);
	pLogger->output(indent+1,0,"Direction=%s 买卖方向",buf);
	OffsetFlag.getString(buf);
	pLogger->output(indent+1,0,"OffsetFlag=%s 开平标志",buf);
	HedgeFlag.getString(buf);
	pLogger->output(indent+1,0,"HedgeFlag=%s 投机套保标志",buf);
	LimitPrice.getString(buf);
	pLogger->output(indent+1,0,"LimitPrice=%s 价格",buf);
	Volume.getString(buf);
	pLogger->output(indent+1,0,"Volume=%s 数量",buf);
	TimeCondition.getString(buf);
	pLogger->output(indent+1,0,"TimeCondition=%s 有效期类型",buf);
	GTDDate.getString(buf);
	pLogger->output(indent+1,0,"GTDDate=%s GTD日期",buf);
	VolumeCondition.getString(buf);
	pLogger->output(indent+1,0,"VolumeCondition=%s 成交量类型",buf);
	MinVolume.getString(buf);
	pLogger->output(indent+1,0,"MinVolume=%s 最小成交量",buf);
	StopPrice.getString(buf);
	pLogger->output(indent+1,0,"StopPrice=%s 止损价",buf);
	ForceCloseReason.getString(buf);
	pLogger->output(indent+1,0,"ForceCloseReason=%s 强平原因",buf);
	IsAutoSuspend.getString(buf);
	pLogger->output(indent+1,0,"IsAutoSuspend=%s 自动挂起标志",buf);
	BusinessUnit.getString(buf);
	pLogger->output(indent+1,0,"BusinessUnit=%s 业务单元",buf);
	UserCustom.getString(buf);
	pLogger->output(indent+1,0,"UserCustom=%s 用户自定义域",buf);
	BranchID.getString(buf);
	pLogger->output(indent+1,0,"BranchID=%s 营业部代码",buf);
	RecNum.getString(buf);
	pLogger->output(indent+1,0,"RecNum=%s 记录编号",buf);
	BusinessType.getString(buf);
	pLogger->output(indent+1,0,"BusinessType=%s 业务类别",buf);
	TradingDay.getString(buf);
	pLogger->output(indent+1,0,"TradingDay=%s 交易日",buf);
	ParticipantID.getString(buf);
	pLogger->output(indent+1,0,"ParticipantID=%s 会员编号",buf);
	ClientID.getString(buf);
	pLogger->output(indent+1,0,"ClientID=%s 客户号",buf);
	SeatID.getString(buf);
	pLogger->output(indent+1,0,"SeatID=%s 下单席位号",buf);
	InsertTime.getString(buf);
	pLogger->output(indent+1,0,"InsertTime=%s 插入时间",buf);
	OrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"OrderLocalID=%s 本地报单编号",buf);
	OrderSource.getString(buf);
	pLogger->output(indent+1,0,"OrderSource=%s 报单来源",buf);
	OrderStatus.getString(buf);
	pLogger->output(indent+1,0,"OrderStatus=%s 报单状态",buf);
	CancelTime.getString(buf);
	pLogger->output(indent+1,0,"CancelTime=%s 撤销时间",buf);
	CancelUserID.getString(buf);
	pLogger->output(indent+1,0,"CancelUserID=%s 撤单用户编号",buf);
	VolumeTraded.getString(buf);
	pLogger->output(indent+1,0,"VolumeTraded=%s 今成交数量",buf);
	VolumeRemain.getString(buf);
	pLogger->output(indent+1,0,"VolumeRemain=%s 剩余数量",buf);
	FrontID.getString(buf);
	pLogger->output(indent+1,0,"FrontID=%s 前置编号",buf);
	SessionID.getString(buf);
	pLogger->output(indent+1,0,"SessionID=%s 会话编号",buf);
	FrozenFee.getString(buf);
	pLogger->output(indent+1,0,"FrozenFee=%s 冻结手续费",buf);
	FrozenMargin.getString(buf);
	pLogger->output(indent+1,0,"FrozenMargin=%s 冻结的保证金",buf);
	FrozenPremium.getString(buf);
	pLogger->output(indent+1,0,"FrozenPremium=%s 期权权利金收支",buf);
	AccountID.getString(buf);
	pLogger->output(indent+1,0,"AccountID=%s 资金帐号",buf);
	OrderUserID.getString(buf);
	pLogger->output(indent+1,0,"OrderUserID=%s 下单用户编号",buf);
	TradeType.getString(buf);
	pLogger->output(indent+1,0,"TradeType=%s 交易类型",buf);
	DealFlag.getString(buf);
	pLogger->output(indent+1,0,"DealFlag=%s 处理标志",buf);
	TradeCommision.getString(buf);
	pLogger->output(indent+1,0,"TradeCommision=%s 已成交佣金",buf);
	TradeAmnt.getString(buf);
	pLogger->output(indent+1,0,"TradeAmnt=%s 成交金额",buf);
	CancleVolume.getString(buf);
	pLogger->output(indent+1,0,"CancleVolume=%s 撤单数量",buf);
	RequestID.getString(buf);
	pLogger->output(indent+1,0,"RequestID=%s 请求编号",buf);
	APIID.getString(buf);
	pLogger->output(indent+1,0,"APIID=%s 通道对应的APIID",buf);
	IPAddress.getString(buf);
	pLogger->output(indent+1,0,"IPAddress=%s 下单IP地址",buf);
	MacAddress.getString(buf);
	pLogger->output(indent+1,0,"MacAddress=%s 下单MAC地址",buf);
	FTdRecvDown.getString(buf);
	pLogger->output(indent+1,0,"FTdRecvDown=%s Ftdengine接受下层时间戳",buf);
	CoreRecvDown.getString(buf);
	pLogger->output(indent+1,0,"CoreRecvDown=%s 接受下层时间戳",buf);
	CoreSendUp.getString(buf);
	pLogger->output(indent+1,0,"CoreSendUp=%s 发送上层时间戳",buf);
	CoreRecvUp.getString(buf);
	pLogger->output(indent+1,0,"CoreRecvUp=%s 接受上层时间戳",buf);
	CoreSendDown.getString(buf);
	pLogger->output(indent+1,0,"CoreSendDown=%s 发送下层时间戳",buf);
	FTdSendDown.getString(buf);
	pLogger->output(indent+1,0,"FTdSendDown=%s Ftdengine接受下层时间戳",buf);
	MarginCombType.getString(buf);
	pLogger->output(indent+1,0,"MarginCombType=%s 保证金组合类型",buf);
	InstrumentGroupID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentGroupID=%s 合约组代码",buf);
	ErrorMsg.getString(buf);
	pLogger->output(indent+1,0,"ErrorMsg=%s 错误信息",buf);
	pLogger->output(indent,0,"}");
}

COrderInsertFailedIterator::~COrderInsertFailedIterator(void)
{
}


void COrderInsertFailedIterator::dump(FILE *output)
{
	COrderInsertFailed *pOrderInsertFailed;
	
	while ((pOrderInsertFailed=next())!=NULL)
	{
		pOrderInsertFailed->dump(output);
	}
}



void CWriteableUserTradingRight::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,ExchangeID,InstrumentID,UserID,InvestorID,TradingRight\n");
}
	
void CWriteableUserTradingRight::init(void)
{
	BrokerID.clear();
	ExchangeID.clear();
	InstrumentID.clear();
	UserID.clear();
	InvestorID.clear();
	TradingRight.clear();
}

int CWriteableUserTradingRight::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableUserTradingRight),input)!=sizeof(CWriteableUserTradingRight))
		return 0;
	else
		return 1;
}
	
int CWriteableUserTradingRight::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserID=token;
		}
		else
		{
			UserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradingRight=token;
		}
		else
		{
			TradingRight="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"UserID"))
			{
				UserID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"TradingRight"))
			{
				TradingRight=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableUserTradingRight::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableUserTradingRight),output)!=sizeof(CWriteableUserTradingRight))
		return 0;
	else
		return 1;
}

int CWriteableUserTradingRight::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradingRight.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableUserTradingRight::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCUserTradingRight%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	UserID.getString(buf);
	fprintf(fp,"\t\tUserID = %s    [用户代码]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);	
	TradingRight.getString(buf);
	fprintf(fp,"\t\tTradingRight = %s    [合约交易权限]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableUserTradingRight::dumpDiff(FILE *fp, const CWriteableUserTradingRight *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCUserTradingRight = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	UserID.getString(buf);
	if (compare(UserID.getValue(),pOriginal->UserID.getValue())!=0)
	{
		pOriginal->UserID.getString(bufOriginal);
		fprintf(fp,"\t\tUserID = %s -> %s    [用户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserID = %s    [用户代码]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);
	}
	TradingRight.getString(buf);
	if (compare(TradingRight.getValue(),pOriginal->TradingRight.getValue())!=0)
	{
		pOriginal->TradingRight.getString(bufOriginal);
		fprintf(fp,"\t\tTradingRight = %s -> %s    [合约交易权限]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradingRight = %s    [合约交易权限]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableUserTradingRight::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	UserID.getString(buf);
	fprintf(fp,",UserID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	TradingRight.getString(buf);
	fprintf(fp,",TradingRight,%s",buf);	
}

void CWriteableUserTradingRight::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	UserID.getString(buf);
	sprintf(p,"UserID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	TradingRight.getString(buf);
	sprintf(p,"TradingRight=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableUserTradingRight::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CUserTradingRight");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	UserID.getString(buf);
	pLogger->output(indent+1,0,"UserID=%s 用户代码",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编号",buf);
	TradingRight.getString(buf);
	pLogger->output(indent+1,0,"TradingRight=%s 合约交易权限",buf);
	pLogger->output(indent,0,"}");
}

CUserTradingRightIterator::~CUserTradingRightIterator(void)
{
}


void CUserTradingRightIterator::dump(FILE *output)
{
	CUserTradingRight *pUserTradingRight;
	
	while ((pUserTradingRight=next())!=NULL)
	{
		pUserTradingRight->dump(output);
	}
}



void CWriteableCurrentTime::writeCSVHead(FILE *output)
{
	fprintf(output,"CurrDate,CurrTime,CurrMillisec,OldTime,OldMillisec\n");
}
	
void CWriteableCurrentTime::init(void)
{
	CurrDate.clear();
	CurrTime.clear();
	CurrMillisec.clear();
	OldTime.clear();
	OldMillisec.clear();
}

int CWriteableCurrentTime::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableCurrentTime),input)!=sizeof(CWriteableCurrentTime))
		return 0;
	else
		return 1;
}
	
int CWriteableCurrentTime::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			CurrDate=token;
		}
		else
		{
			CurrDate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CurrTime=token;
		}
		else
		{
			CurrTime="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CurrMillisec=token;
		}
		else
		{
			CurrMillisec="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OldTime=token;
		}
		else
		{
			OldTime="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OldMillisec=token;
		}
		else
		{
			OldMillisec="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"CurrDate"))
			{
				CurrDate=token;
			}
			else if (!strcmp(fieldName,"CurrTime"))
			{
				CurrTime=token;
			}
			else if (!strcmp(fieldName,"CurrMillisec"))
			{
				CurrMillisec=token;
			}
			else if (!strcmp(fieldName,"OldTime"))
			{
				OldTime=token;
			}
			else if (!strcmp(fieldName,"OldMillisec"))
			{
				OldMillisec=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableCurrentTime::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableCurrentTime),output)!=sizeof(CWriteableCurrentTime))
		return 0;
	else
		return 1;
}

int CWriteableCurrentTime::writeCSV(FILE *output) const
{
	char buffer[1025];
	CurrDate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CurrTime.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CurrMillisec.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OldTime.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OldMillisec.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableCurrentTime::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCCurrentTime%s = {\n", index_buf);
	CurrDate.getString(buf);
	fprintf(fp,"\t\tCurrDate = %s    [当前日期]\n",buf);	
	CurrTime.getString(buf);
	fprintf(fp,"\t\tCurrTime = %s    [当前时间]\n",buf);	
	CurrMillisec.getString(buf);
	fprintf(fp,"\t\tCurrMillisec = %s    [当前时间（毫秒）]\n",buf);	
	OldTime.getString(buf);
	fprintf(fp,"\t\tOldTime = %s    [原来时间]\n",buf);	
	OldMillisec.getString(buf);
	fprintf(fp,"\t\tOldMillisec = %s    [原来时间（毫秒）]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableCurrentTime::dumpDiff(FILE *fp, const CWriteableCurrentTime *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCCurrentTime = {\n");
	CurrDate.getString(buf);
	if (compare(CurrDate.getValue(),pOriginal->CurrDate.getValue())!=0)
	{
		pOriginal->CurrDate.getString(bufOriginal);
		fprintf(fp,"\t\tCurrDate = %s -> %s    [当前日期]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCurrDate = %s    [当前日期]\n",buf);
	}
	CurrTime.getString(buf);
	if (compare(CurrTime.getValue(),pOriginal->CurrTime.getValue())!=0)
	{
		pOriginal->CurrTime.getString(bufOriginal);
		fprintf(fp,"\t\tCurrTime = %s -> %s    [当前时间]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCurrTime = %s    [当前时间]\n",buf);
	}
	CurrMillisec.getString(buf);
	if (compare(CurrMillisec.getValue(),pOriginal->CurrMillisec.getValue())!=0)
	{
		pOriginal->CurrMillisec.getString(bufOriginal);
		fprintf(fp,"\t\tCurrMillisec = %s -> %s    [当前时间（毫秒）]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCurrMillisec = %s    [当前时间（毫秒）]\n",buf);
	}
	OldTime.getString(buf);
	if (compare(OldTime.getValue(),pOriginal->OldTime.getValue())!=0)
	{
		pOriginal->OldTime.getString(bufOriginal);
		fprintf(fp,"\t\tOldTime = %s -> %s    [原来时间]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOldTime = %s    [原来时间]\n",buf);
	}
	OldMillisec.getString(buf);
	if (compare(OldMillisec.getValue(),pOriginal->OldMillisec.getValue())!=0)
	{
		pOriginal->OldMillisec.getString(bufOriginal);
		fprintf(fp,"\t\tOldMillisec = %s -> %s    [原来时间（毫秒）]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOldMillisec = %s    [原来时间（毫秒）]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableCurrentTime::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	CurrDate.getString(buf);
	fprintf(fp,",CurrDate,%s",buf);	
	CurrTime.getString(buf);
	fprintf(fp,",CurrTime,%s",buf);	
	CurrMillisec.getString(buf);
	fprintf(fp,",CurrMillisec,%s",buf);	
	OldTime.getString(buf);
	fprintf(fp,",OldTime,%s",buf);	
	OldMillisec.getString(buf);
	fprintf(fp,",OldMillisec,%s",buf);	
}

void CWriteableCurrentTime::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	CurrDate.getString(buf);
	sprintf(p,"CurrDate=%s,",buf);
	p+=strlen(p);
	CurrTime.getString(buf);
	sprintf(p,"CurrTime=%s,",buf);
	p+=strlen(p);
	CurrMillisec.getString(buf);
	sprintf(p,"CurrMillisec=%s,",buf);
	p+=strlen(p);
	OldTime.getString(buf);
	sprintf(p,"OldTime=%s,",buf);
	p+=strlen(p);
	OldMillisec.getString(buf);
	sprintf(p,"OldMillisec=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableCurrentTime::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CCurrentTime");
	pLogger->output(indent,0,"{");
	CurrDate.getString(buf);
	pLogger->output(indent+1,0,"CurrDate=%s 当前日期",buf);
	CurrTime.getString(buf);
	pLogger->output(indent+1,0,"CurrTime=%s 当前时间",buf);
	CurrMillisec.getString(buf);
	pLogger->output(indent+1,0,"CurrMillisec=%s 当前时间（毫秒）",buf);
	OldTime.getString(buf);
	pLogger->output(indent+1,0,"OldTime=%s 原来时间",buf);
	OldMillisec.getString(buf);
	pLogger->output(indent+1,0,"OldMillisec=%s 原来时间（毫秒）",buf);
	pLogger->output(indent,0,"}");
}

CCurrentTimeIterator::~CCurrentTimeIterator(void)
{
}


void CCurrentTimeIterator::dump(FILE *output)
{
	CCurrentTime *pCurrentTime;
	
	while ((pCurrentTime=next())!=NULL)
	{
		pCurrentTime->dump(output);
	}
}



void CWriteableUserSession::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,UserID,UserType,SessionID,FrontID,LoginTime,IPAddress,MacAddress,UserProductInfo,InterfaceProductInfo,ProtocolInfo\n");
}
	
void CWriteableUserSession::init(void)
{
	BrokerID.clear();
	UserID.clear();
	UserType.clear();
	SessionID.clear();
	FrontID.clear();
	LoginTime.clear();
	IPAddress.clear();
	MacAddress.clear();
	UserProductInfo.clear();
	InterfaceProductInfo.clear();
	ProtocolInfo.clear();
}

int CWriteableUserSession::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableUserSession),input)!=sizeof(CWriteableUserSession))
		return 0;
	else
		return 1;
}
	
int CWriteableUserSession::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserID=token;
		}
		else
		{
			UserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserType=token;
		}
		else
		{
			UserType="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SessionID=token;
		}
		else
		{
			SessionID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrontID=token;
		}
		else
		{
			FrontID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LoginTime=token;
		}
		else
		{
			LoginTime="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IPAddress=token;
		}
		else
		{
			IPAddress="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MacAddress=token;
		}
		else
		{
			MacAddress="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserProductInfo=token;
		}
		else
		{
			UserProductInfo="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InterfaceProductInfo=token;
		}
		else
		{
			InterfaceProductInfo="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ProtocolInfo=token;
		}
		else
		{
			ProtocolInfo="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"UserID"))
			{
				UserID=token;
			}
			else if (!strcmp(fieldName,"UserType"))
			{
				UserType=token;
			}
			else if (!strcmp(fieldName,"SessionID"))
			{
				SessionID=token;
			}
			else if (!strcmp(fieldName,"FrontID"))
			{
				FrontID=token;
			}
			else if (!strcmp(fieldName,"LoginTime"))
			{
				LoginTime=token;
			}
			else if (!strcmp(fieldName,"IPAddress"))
			{
				IPAddress=token;
			}
			else if (!strcmp(fieldName,"MacAddress"))
			{
				MacAddress=token;
			}
			else if (!strcmp(fieldName,"UserProductInfo"))
			{
				UserProductInfo=token;
			}
			else if (!strcmp(fieldName,"InterfaceProductInfo"))
			{
				InterfaceProductInfo=token;
			}
			else if (!strcmp(fieldName,"ProtocolInfo"))
			{
				ProtocolInfo=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableUserSession::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableUserSession),output)!=sizeof(CWriteableUserSession))
		return 0;
	else
		return 1;
}

int CWriteableUserSession::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SessionID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrontID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LoginTime.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IPAddress.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MacAddress.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserProductInfo.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InterfaceProductInfo.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ProtocolInfo.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableUserSession::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCUserSession%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司代码]\n",buf);	
	UserID.getString(buf);
	fprintf(fp,"\t\tUserID = %s    [交易用户代码]\n",buf);	
	UserType.getString(buf);
	fprintf(fp,"\t\tUserType = %s    [交易用户类型]\n",buf);	
	SessionID.getString(buf);
	fprintf(fp,"\t\tSessionID = %s    [会话编号]\n",buf);	
	FrontID.getString(buf);
	fprintf(fp,"\t\tFrontID = %s    [前置编号]\n",buf);	
	LoginTime.getString(buf);
	fprintf(fp,"\t\tLoginTime = %s    [登录时间]\n",buf);	
	IPAddress.getString(buf);
	fprintf(fp,"\t\tIPAddress = %s    [IP地址]\n",buf);	
	MacAddress.getString(buf);
	fprintf(fp,"\t\tMacAddress = %s    [Mac地址]\n",buf);	
	UserProductInfo.getString(buf);
	fprintf(fp,"\t\tUserProductInfo = %s    [用户端产品信息]\n",buf);	
	InterfaceProductInfo.getString(buf);
	fprintf(fp,"\t\tInterfaceProductInfo = %s    [接口端产品信息]\n",buf);	
	ProtocolInfo.getString(buf);
	fprintf(fp,"\t\tProtocolInfo = %s    [协议信息]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableUserSession::dumpDiff(FILE *fp, const CWriteableUserSession *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCUserSession = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司代码]\n",buf);
	}
	UserID.getString(buf);
	if (compare(UserID.getValue(),pOriginal->UserID.getValue())!=0)
	{
		pOriginal->UserID.getString(bufOriginal);
		fprintf(fp,"\t\tUserID = %s -> %s    [交易用户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserID = %s    [交易用户代码]\n",buf);
	}
	UserType.getString(buf);
	if (compare(UserType.getValue(),pOriginal->UserType.getValue())!=0)
	{
		pOriginal->UserType.getString(bufOriginal);
		fprintf(fp,"\t\tUserType = %s -> %s    [交易用户类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserType = %s    [交易用户类型]\n",buf);
	}
	SessionID.getString(buf);
	if (compare(SessionID.getValue(),pOriginal->SessionID.getValue())!=0)
	{
		pOriginal->SessionID.getString(bufOriginal);
		fprintf(fp,"\t\tSessionID = %s -> %s    [会话编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSessionID = %s    [会话编号]\n",buf);
	}
	FrontID.getString(buf);
	if (compare(FrontID.getValue(),pOriginal->FrontID.getValue())!=0)
	{
		pOriginal->FrontID.getString(bufOriginal);
		fprintf(fp,"\t\tFrontID = %s -> %s    [前置编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrontID = %s    [前置编号]\n",buf);
	}
	LoginTime.getString(buf);
	if (compare(LoginTime.getValue(),pOriginal->LoginTime.getValue())!=0)
	{
		pOriginal->LoginTime.getString(bufOriginal);
		fprintf(fp,"\t\tLoginTime = %s -> %s    [登录时间]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLoginTime = %s    [登录时间]\n",buf);
	}
	IPAddress.getString(buf);
	if (compare(IPAddress.getValue(),pOriginal->IPAddress.getValue())!=0)
	{
		pOriginal->IPAddress.getString(bufOriginal);
		fprintf(fp,"\t\tIPAddress = %s -> %s    [IP地址]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIPAddress = %s    [IP地址]\n",buf);
	}
	MacAddress.getString(buf);
	if (compare(MacAddress.getValue(),pOriginal->MacAddress.getValue())!=0)
	{
		pOriginal->MacAddress.getString(bufOriginal);
		fprintf(fp,"\t\tMacAddress = %s -> %s    [Mac地址]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMacAddress = %s    [Mac地址]\n",buf);
	}
	UserProductInfo.getString(buf);
	if (compare(UserProductInfo.getValue(),pOriginal->UserProductInfo.getValue())!=0)
	{
		pOriginal->UserProductInfo.getString(bufOriginal);
		fprintf(fp,"\t\tUserProductInfo = %s -> %s    [用户端产品信息]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserProductInfo = %s    [用户端产品信息]\n",buf);
	}
	InterfaceProductInfo.getString(buf);
	if (compare(InterfaceProductInfo.getValue(),pOriginal->InterfaceProductInfo.getValue())!=0)
	{
		pOriginal->InterfaceProductInfo.getString(bufOriginal);
		fprintf(fp,"\t\tInterfaceProductInfo = %s -> %s    [接口端产品信息]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInterfaceProductInfo = %s    [接口端产品信息]\n",buf);
	}
	ProtocolInfo.getString(buf);
	if (compare(ProtocolInfo.getValue(),pOriginal->ProtocolInfo.getValue())!=0)
	{
		pOriginal->ProtocolInfo.getString(bufOriginal);
		fprintf(fp,"\t\tProtocolInfo = %s -> %s    [协议信息]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tProtocolInfo = %s    [协议信息]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableUserSession::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	UserID.getString(buf);
	fprintf(fp,",UserID,%s",buf);	
	UserType.getString(buf);
	fprintf(fp,",UserType,%s",buf);	
	SessionID.getString(buf);
	fprintf(fp,",SessionID,%s",buf);	
	FrontID.getString(buf);
	fprintf(fp,",FrontID,%s",buf);	
	LoginTime.getString(buf);
	fprintf(fp,",LoginTime,%s",buf);	
	IPAddress.getString(buf);
	fprintf(fp,",IPAddress,%s",buf);	
	MacAddress.getString(buf);
	fprintf(fp,",MacAddress,%s",buf);	
	UserProductInfo.getString(buf);
	fprintf(fp,",UserProductInfo,%s",buf);	
	InterfaceProductInfo.getString(buf);
	fprintf(fp,",InterfaceProductInfo,%s",buf);	
	ProtocolInfo.getString(buf);
	fprintf(fp,",ProtocolInfo,%s",buf);	
}

void CWriteableUserSession::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	UserID.getString(buf);
	sprintf(p,"UserID=%s,",buf);
	p+=strlen(p);
	UserType.getString(buf);
	sprintf(p,"UserType=%s,",buf);
	p+=strlen(p);
	SessionID.getString(buf);
	sprintf(p,"SessionID=%s,",buf);
	p+=strlen(p);
	FrontID.getString(buf);
	sprintf(p,"FrontID=%s,",buf);
	p+=strlen(p);
	LoginTime.getString(buf);
	sprintf(p,"LoginTime=%s,",buf);
	p+=strlen(p);
	IPAddress.getString(buf);
	sprintf(p,"IPAddress=%s,",buf);
	p+=strlen(p);
	MacAddress.getString(buf);
	sprintf(p,"MacAddress=%s,",buf);
	p+=strlen(p);
	UserProductInfo.getString(buf);
	sprintf(p,"UserProductInfo=%s,",buf);
	p+=strlen(p);
	InterfaceProductInfo.getString(buf);
	sprintf(p,"InterfaceProductInfo=%s,",buf);
	p+=strlen(p);
	ProtocolInfo.getString(buf);
	sprintf(p,"ProtocolInfo=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableUserSession::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CUserSession");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司代码",buf);
	UserID.getString(buf);
	pLogger->output(indent+1,0,"UserID=%s 交易用户代码",buf);
	UserType.getString(buf);
	pLogger->output(indent+1,0,"UserType=%s 交易用户类型",buf);
	SessionID.getString(buf);
	pLogger->output(indent+1,0,"SessionID=%s 会话编号",buf);
	FrontID.getString(buf);
	pLogger->output(indent+1,0,"FrontID=%s 前置编号",buf);
	LoginTime.getString(buf);
	pLogger->output(indent+1,0,"LoginTime=%s 登录时间",buf);
	IPAddress.getString(buf);
	pLogger->output(indent+1,0,"IPAddress=%s IP地址",buf);
	MacAddress.getString(buf);
	pLogger->output(indent+1,0,"MacAddress=%s Mac地址",buf);
	UserProductInfo.getString(buf);
	pLogger->output(indent+1,0,"UserProductInfo=%s 用户端产品信息",buf);
	InterfaceProductInfo.getString(buf);
	pLogger->output(indent+1,0,"InterfaceProductInfo=%s 接口端产品信息",buf);
	ProtocolInfo.getString(buf);
	pLogger->output(indent+1,0,"ProtocolInfo=%s 协议信息",buf);
	pLogger->output(indent,0,"}");
}

CUserSessionIterator::~CUserSessionIterator(void)
{
}


void CUserSessionIterator::dump(FILE *output)
{
	CUserSession *pUserSession;
	
	while ((pUserSession=next())!=NULL)
	{
		pUserSession->dump(output);
	}
}



void CWriteableMaxLocalID::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,UserID,MaxOrderLocalID,FrontID,SessionID\n");
}
	
void CWriteableMaxLocalID::init(void)
{
	BrokerID.clear();
	UserID.clear();
	MaxOrderLocalID.clear();
	FrontID.clear();
	SessionID.clear();
}

int CWriteableMaxLocalID::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableMaxLocalID),input)!=sizeof(CWriteableMaxLocalID))
		return 0;
	else
		return 1;
}
	
int CWriteableMaxLocalID::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserID=token;
		}
		else
		{
			UserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MaxOrderLocalID=token;
		}
		else
		{
			MaxOrderLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrontID=token;
		}
		else
		{
			FrontID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SessionID=token;
		}
		else
		{
			SessionID="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"UserID"))
			{
				UserID=token;
			}
			else if (!strcmp(fieldName,"MaxOrderLocalID"))
			{
				MaxOrderLocalID=token;
			}
			else if (!strcmp(fieldName,"FrontID"))
			{
				FrontID=token;
			}
			else if (!strcmp(fieldName,"SessionID"))
			{
				SessionID=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableMaxLocalID::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableMaxLocalID),output)!=sizeof(CWriteableMaxLocalID))
		return 0;
	else
		return 1;
}

int CWriteableMaxLocalID::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MaxOrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrontID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SessionID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableMaxLocalID::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCMaxLocalID%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司代码]\n",buf);	
	UserID.getString(buf);
	fprintf(fp,"\t\tUserID = %s    [交易用户代码]\n",buf);	
	MaxOrderLocalID.getString(buf);
	fprintf(fp,"\t\tMaxOrderLocalID = %s    [最大报单本地编号]\n",buf);	
	FrontID.getString(buf);
	fprintf(fp,"\t\tFrontID = %s    [前置编号]\n",buf);	
	SessionID.getString(buf);
	fprintf(fp,"\t\tSessionID = %s    [会话编号]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableMaxLocalID::dumpDiff(FILE *fp, const CWriteableMaxLocalID *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCMaxLocalID = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司代码]\n",buf);
	}
	UserID.getString(buf);
	if (compare(UserID.getValue(),pOriginal->UserID.getValue())!=0)
	{
		pOriginal->UserID.getString(bufOriginal);
		fprintf(fp,"\t\tUserID = %s -> %s    [交易用户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserID = %s    [交易用户代码]\n",buf);
	}
	MaxOrderLocalID.getString(buf);
	if (compare(MaxOrderLocalID.getValue(),pOriginal->MaxOrderLocalID.getValue())!=0)
	{
		pOriginal->MaxOrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tMaxOrderLocalID = %s -> %s    [最大报单本地编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMaxOrderLocalID = %s    [最大报单本地编号]\n",buf);
	}
	FrontID.getString(buf);
	if (compare(FrontID.getValue(),pOriginal->FrontID.getValue())!=0)
	{
		pOriginal->FrontID.getString(bufOriginal);
		fprintf(fp,"\t\tFrontID = %s -> %s    [前置编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrontID = %s    [前置编号]\n",buf);
	}
	SessionID.getString(buf);
	if (compare(SessionID.getValue(),pOriginal->SessionID.getValue())!=0)
	{
		pOriginal->SessionID.getString(bufOriginal);
		fprintf(fp,"\t\tSessionID = %s -> %s    [会话编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSessionID = %s    [会话编号]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableMaxLocalID::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	UserID.getString(buf);
	fprintf(fp,",UserID,%s",buf);	
	MaxOrderLocalID.getString(buf);
	fprintf(fp,",MaxOrderLocalID,%s",buf);	
	FrontID.getString(buf);
	fprintf(fp,",FrontID,%s",buf);	
	SessionID.getString(buf);
	fprintf(fp,",SessionID,%s",buf);	
}

void CWriteableMaxLocalID::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	UserID.getString(buf);
	sprintf(p,"UserID=%s,",buf);
	p+=strlen(p);
	MaxOrderLocalID.getString(buf);
	sprintf(p,"MaxOrderLocalID=%s,",buf);
	p+=strlen(p);
	FrontID.getString(buf);
	sprintf(p,"FrontID=%s,",buf);
	p+=strlen(p);
	SessionID.getString(buf);
	sprintf(p,"SessionID=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableMaxLocalID::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CMaxLocalID");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司代码",buf);
	UserID.getString(buf);
	pLogger->output(indent+1,0,"UserID=%s 交易用户代码",buf);
	MaxOrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"MaxOrderLocalID=%s 最大报单本地编号",buf);
	FrontID.getString(buf);
	pLogger->output(indent+1,0,"FrontID=%s 前置编号",buf);
	SessionID.getString(buf);
	pLogger->output(indent+1,0,"SessionID=%s 会话编号",buf);
	pLogger->output(indent,0,"}");
}

CMaxLocalIDIterator::~CMaxLocalIDIterator(void)
{
}


void CMaxLocalIDIterator::dump(FILE *output)
{
	CMaxLocalID *pMaxLocalID;
	
	while ((pMaxLocalID=next())!=NULL)
	{
		pMaxLocalID->dump(output);
	}
}



void CWriteableBrkUserIDLocalID::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,UserID,UserOrderLocalID,APIID,OrderLocalID\n");
}
	
void CWriteableBrkUserIDLocalID::init(void)
{
	BrokerID.clear();
	UserID.clear();
	UserOrderLocalID.clear();
	APIID.clear();
	OrderLocalID.clear();
	pPreOrder=NULL;
}

int CWriteableBrkUserIDLocalID::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableBrkUserIDLocalID),input)!=sizeof(CWriteableBrkUserIDLocalID))
		return 0;
	else
		return 1;
}
	
int CWriteableBrkUserIDLocalID::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserID=token;
		}
		else
		{
			UserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserOrderLocalID=token;
		}
		else
		{
			UserOrderLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			APIID=token;
		}
		else
		{
			APIID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OrderLocalID=token;
		}
		else
		{
			OrderLocalID="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"UserID"))
			{
				UserID=token;
			}
			else if (!strcmp(fieldName,"UserOrderLocalID"))
			{
				UserOrderLocalID=token;
			}
			else if (!strcmp(fieldName,"APIID"))
			{
				APIID=token;
			}
			else if (!strcmp(fieldName,"OrderLocalID"))
			{
				OrderLocalID=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableBrkUserIDLocalID::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableBrkUserIDLocalID),output)!=sizeof(CWriteableBrkUserIDLocalID))
		return 0;
	else
		return 1;
}

int CWriteableBrkUserIDLocalID::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserOrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	APIID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableBrkUserIDLocalID::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCBrkUserIDLocalID%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司代码]\n",buf);	
	UserID.getString(buf);
	fprintf(fp,"\t\tUserID = %s    [交易用户代码]\n",buf);	
	UserOrderLocalID.getString(buf);
	fprintf(fp,"\t\tUserOrderLocalID = %s    [用户本地编号]\n",buf);	
	APIID.getString(buf);
	fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);	
	OrderLocalID.getString(buf);
	fprintf(fp,"\t\tOrderLocalID = %s    [本地报单编号]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableBrkUserIDLocalID::dumpDiff(FILE *fp, const CWriteableBrkUserIDLocalID *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCBrkUserIDLocalID = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司代码]\n",buf);
	}
	UserID.getString(buf);
	if (compare(UserID.getValue(),pOriginal->UserID.getValue())!=0)
	{
		pOriginal->UserID.getString(bufOriginal);
		fprintf(fp,"\t\tUserID = %s -> %s    [交易用户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserID = %s    [交易用户代码]\n",buf);
	}
	UserOrderLocalID.getString(buf);
	if (compare(UserOrderLocalID.getValue(),pOriginal->UserOrderLocalID.getValue())!=0)
	{
		pOriginal->UserOrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tUserOrderLocalID = %s -> %s    [用户本地编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserOrderLocalID = %s    [用户本地编号]\n",buf);
	}
	APIID.getString(buf);
	if (compare(APIID.getValue(),pOriginal->APIID.getValue())!=0)
	{
		pOriginal->APIID.getString(bufOriginal);
		fprintf(fp,"\t\tAPIID = %s -> %s    [通道对应的APIID]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tAPIID = %s    [通道对应的APIID]\n",buf);
	}
	OrderLocalID.getString(buf);
	if (compare(OrderLocalID.getValue(),pOriginal->OrderLocalID.getValue())!=0)
	{
		pOriginal->OrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tOrderLocalID = %s -> %s    [本地报单编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOrderLocalID = %s    [本地报单编号]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableBrkUserIDLocalID::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	UserID.getString(buf);
	fprintf(fp,",UserID,%s",buf);	
	UserOrderLocalID.getString(buf);
	fprintf(fp,",UserOrderLocalID,%s",buf);	
	APIID.getString(buf);
	fprintf(fp,",APIID,%s",buf);	
	OrderLocalID.getString(buf);
	fprintf(fp,",OrderLocalID,%s",buf);	
}

void CWriteableBrkUserIDLocalID::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	UserID.getString(buf);
	sprintf(p,"UserID=%s,",buf);
	p+=strlen(p);
	UserOrderLocalID.getString(buf);
	sprintf(p,"UserOrderLocalID=%s,",buf);
	p+=strlen(p);
	APIID.getString(buf);
	sprintf(p,"APIID=%s,",buf);
	p+=strlen(p);
	OrderLocalID.getString(buf);
	sprintf(p,"OrderLocalID=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableBrkUserIDLocalID::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CBrkUserIDLocalID");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司代码",buf);
	UserID.getString(buf);
	pLogger->output(indent+1,0,"UserID=%s 交易用户代码",buf);
	UserOrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"UserOrderLocalID=%s 用户本地编号",buf);
	APIID.getString(buf);
	pLogger->output(indent+1,0,"APIID=%s 通道对应的APIID",buf);
	OrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"OrderLocalID=%s 本地报单编号",buf);
	pLogger->output(indent,0,"}");
}

CBrkUserIDLocalIDIterator::~CBrkUserIDLocalIDIterator(void)
{
}


void CBrkUserIDLocalIDIterator::dump(FILE *output)
{
	CBrkUserIDLocalID *pBrkUserIDLocalID;
	
	while ((pBrkUserIDLocalID=next())!=NULL)
	{
		pBrkUserIDLocalID->dump(output);
	}
}



void CWriteablePartClientInsGroupPosition::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,ParticipantID,ClientID,InstrumentGroupID,LongPosition,LongMargin,ShortPosition,ShortMargin,ActualMargin ,LongFrozenPosition,LongFrozenMargin,ShortFrozenPosition,ShortFrozenMargin,ActualFrozenMargin \n");
}
	
void CWriteablePartClientInsGroupPosition::init(void)
{
	BrokerID.clear();
	ParticipantID.clear();
	ClientID.clear();
	InstrumentGroupID.clear();
	LongPosition.clear();
	LongMargin.clear();
	ShortPosition.clear();
	ShortMargin.clear();
	ActualMargin .clear();
	LongFrozenPosition.clear();
	LongFrozenMargin.clear();
	ShortFrozenPosition.clear();
	ShortFrozenMargin.clear();
	ActualFrozenMargin .clear();
}

int CWriteablePartClientInsGroupPosition::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteablePartClientInsGroupPosition),input)!=sizeof(CWriteablePartClientInsGroupPosition))
		return 0;
	else
		return 1;
}
	
int CWriteablePartClientInsGroupPosition::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ParticipantID=token;
		}
		else
		{
			ParticipantID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ClientID=token;
		}
		else
		{
			ClientID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentGroupID=token;
		}
		else
		{
			InstrumentGroupID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LongPosition=token;
		}
		else
		{
			LongPosition="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LongMargin=token;
		}
		else
		{
			LongMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ShortPosition=token;
		}
		else
		{
			ShortPosition="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ShortMargin=token;
		}
		else
		{
			ShortMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ActualMargin =token;
		}
		else
		{
			ActualMargin ="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LongFrozenPosition=token;
		}
		else
		{
			LongFrozenPosition="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LongFrozenMargin=token;
		}
		else
		{
			LongFrozenMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ShortFrozenPosition=token;
		}
		else
		{
			ShortFrozenPosition="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ShortFrozenMargin=token;
		}
		else
		{
			ShortFrozenMargin="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ActualFrozenMargin =token;
		}
		else
		{
			ActualFrozenMargin ="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"ParticipantID"))
			{
				ParticipantID=token;
			}
			else if (!strcmp(fieldName,"ClientID"))
			{
				ClientID=token;
			}
			else if (!strcmp(fieldName,"InstrumentGroupID"))
			{
				InstrumentGroupID=token;
			}
			else if (!strcmp(fieldName,"LongPosition"))
			{
				LongPosition=token;
			}
			else if (!strcmp(fieldName,"LongMargin"))
			{
				LongMargin=token;
			}
			else if (!strcmp(fieldName,"ShortPosition"))
			{
				ShortPosition=token;
			}
			else if (!strcmp(fieldName,"ShortMargin"))
			{
				ShortMargin=token;
			}
			else if (!strcmp(fieldName,"ActualMargin "))
			{
				ActualMargin =token;
			}
			else if (!strcmp(fieldName,"LongFrozenPosition"))
			{
				LongFrozenPosition=token;
			}
			else if (!strcmp(fieldName,"LongFrozenMargin"))
			{
				LongFrozenMargin=token;
			}
			else if (!strcmp(fieldName,"ShortFrozenPosition"))
			{
				ShortFrozenPosition=token;
			}
			else if (!strcmp(fieldName,"ShortFrozenMargin"))
			{
				ShortFrozenMargin=token;
			}
			else if (!strcmp(fieldName,"ActualFrozenMargin "))
			{
				ActualFrozenMargin =token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteablePartClientInsGroupPosition::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteablePartClientInsGroupPosition),output)!=sizeof(CWriteablePartClientInsGroupPosition))
		return 0;
	else
		return 1;
}

int CWriteablePartClientInsGroupPosition::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ParticipantID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ClientID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentGroupID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LongPosition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LongMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ShortPosition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ShortMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ActualMargin .getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LongFrozenPosition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LongFrozenMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ShortFrozenPosition.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ShortFrozenMargin.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ActualFrozenMargin .getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteablePartClientInsGroupPosition::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCPartClientInsGroupPosition%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,"\t\tParticipantID = %s    [会员代码]\n",buf);	
	ClientID.getString(buf);
	fprintf(fp,"\t\tClientID = %s    [客户代码]\n",buf);	
	InstrumentGroupID.getString(buf);
	fprintf(fp,"\t\tInstrumentGroupID = %s    [合约组代码]\n",buf);	
	LongPosition.getString(buf);
	fprintf(fp,"\t\tLongPosition = %s    [合约组多头总持仓]\n",buf);	
	LongMargin.getString(buf);
	fprintf(fp,"\t\tLongMargin = %s    [合约组多头保证金之和]\n",buf);	
	ShortPosition.getString(buf);
	fprintf(fp,"\t\tShortPosition = %s    [合约组空头总持仓]\n",buf);	
	ShortMargin.getString(buf);
	fprintf(fp,"\t\tShortMargin = %s    [合约组空头保证金之和]\n",buf);	
	ActualMargin .getString(buf);
	fprintf(fp,"\t\tActualMargin  = %s    [实际收取的保证金]\n",buf);	
	LongFrozenPosition.getString(buf);
	fprintf(fp,"\t\tLongFrozenPosition = %s    [合约组多头冻结总持仓]\n",buf);	
	LongFrozenMargin.getString(buf);
	fprintf(fp,"\t\tLongFrozenMargin = %s    [合约组多头冻结保证金之和]\n",buf);	
	ShortFrozenPosition.getString(buf);
	fprintf(fp,"\t\tShortFrozenPosition = %s    [合约组空头冻结总持仓]\n",buf);	
	ShortFrozenMargin.getString(buf);
	fprintf(fp,"\t\tShortFrozenMargin = %s    [合约组空头冻结保证金之和]\n",buf);	
	ActualFrozenMargin .getString(buf);
	fprintf(fp,"\t\tActualFrozenMargin  = %s    [实际冻结的保证金]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteablePartClientInsGroupPosition::dumpDiff(FILE *fp, const CWriteablePartClientInsGroupPosition *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCPartClientInsGroupPosition = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	ParticipantID.getString(buf);
	if (compare(ParticipantID.getValue(),pOriginal->ParticipantID.getValue())!=0)
	{
		pOriginal->ParticipantID.getString(bufOriginal);
		fprintf(fp,"\t\tParticipantID = %s -> %s    [会员代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tParticipantID = %s    [会员代码]\n",buf);
	}
	ClientID.getString(buf);
	if (compare(ClientID.getValue(),pOriginal->ClientID.getValue())!=0)
	{
		pOriginal->ClientID.getString(bufOriginal);
		fprintf(fp,"\t\tClientID = %s -> %s    [客户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tClientID = %s    [客户代码]\n",buf);
	}
	InstrumentGroupID.getString(buf);
	if (compare(InstrumentGroupID.getValue(),pOriginal->InstrumentGroupID.getValue())!=0)
	{
		pOriginal->InstrumentGroupID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentGroupID = %s -> %s    [合约组代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentGroupID = %s    [合约组代码]\n",buf);
	}
	LongPosition.getString(buf);
	if (compare(LongPosition.getValue(),pOriginal->LongPosition.getValue())!=0)
	{
		pOriginal->LongPosition.getString(bufOriginal);
		fprintf(fp,"\t\tLongPosition = %s -> %s    [合约组多头总持仓]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLongPosition = %s    [合约组多头总持仓]\n",buf);
	}
	LongMargin.getString(buf);
	if (compare(LongMargin.getValue(),pOriginal->LongMargin.getValue())!=0)
	{
		pOriginal->LongMargin.getString(bufOriginal);
		fprintf(fp,"\t\tLongMargin = %s -> %s    [合约组多头保证金之和]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLongMargin = %s    [合约组多头保证金之和]\n",buf);
	}
	ShortPosition.getString(buf);
	if (compare(ShortPosition.getValue(),pOriginal->ShortPosition.getValue())!=0)
	{
		pOriginal->ShortPosition.getString(bufOriginal);
		fprintf(fp,"\t\tShortPosition = %s -> %s    [合约组空头总持仓]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tShortPosition = %s    [合约组空头总持仓]\n",buf);
	}
	ShortMargin.getString(buf);
	if (compare(ShortMargin.getValue(),pOriginal->ShortMargin.getValue())!=0)
	{
		pOriginal->ShortMargin.getString(bufOriginal);
		fprintf(fp,"\t\tShortMargin = %s -> %s    [合约组空头保证金之和]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tShortMargin = %s    [合约组空头保证金之和]\n",buf);
	}
	ActualMargin .getString(buf);
	if (compare(ActualMargin .getValue(),pOriginal->ActualMargin .getValue())!=0)
	{
		pOriginal->ActualMargin .getString(bufOriginal);
		fprintf(fp,"\t\tActualMargin  = %s -> %s    [实际收取的保证金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tActualMargin  = %s    [实际收取的保证金]\n",buf);
	}
	LongFrozenPosition.getString(buf);
	if (compare(LongFrozenPosition.getValue(),pOriginal->LongFrozenPosition.getValue())!=0)
	{
		pOriginal->LongFrozenPosition.getString(bufOriginal);
		fprintf(fp,"\t\tLongFrozenPosition = %s -> %s    [合约组多头冻结总持仓]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLongFrozenPosition = %s    [合约组多头冻结总持仓]\n",buf);
	}
	LongFrozenMargin.getString(buf);
	if (compare(LongFrozenMargin.getValue(),pOriginal->LongFrozenMargin.getValue())!=0)
	{
		pOriginal->LongFrozenMargin.getString(bufOriginal);
		fprintf(fp,"\t\tLongFrozenMargin = %s -> %s    [合约组多头冻结保证金之和]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLongFrozenMargin = %s    [合约组多头冻结保证金之和]\n",buf);
	}
	ShortFrozenPosition.getString(buf);
	if (compare(ShortFrozenPosition.getValue(),pOriginal->ShortFrozenPosition.getValue())!=0)
	{
		pOriginal->ShortFrozenPosition.getString(bufOriginal);
		fprintf(fp,"\t\tShortFrozenPosition = %s -> %s    [合约组空头冻结总持仓]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tShortFrozenPosition = %s    [合约组空头冻结总持仓]\n",buf);
	}
	ShortFrozenMargin.getString(buf);
	if (compare(ShortFrozenMargin.getValue(),pOriginal->ShortFrozenMargin.getValue())!=0)
	{
		pOriginal->ShortFrozenMargin.getString(bufOriginal);
		fprintf(fp,"\t\tShortFrozenMargin = %s -> %s    [合约组空头冻结保证金之和]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tShortFrozenMargin = %s    [合约组空头冻结保证金之和]\n",buf);
	}
	ActualFrozenMargin .getString(buf);
	if (compare(ActualFrozenMargin .getValue(),pOriginal->ActualFrozenMargin .getValue())!=0)
	{
		pOriginal->ActualFrozenMargin .getString(bufOriginal);
		fprintf(fp,"\t\tActualFrozenMargin  = %s -> %s    [实际冻结的保证金]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tActualFrozenMargin  = %s    [实际冻结的保证金]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteablePartClientInsGroupPosition::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,",ParticipantID,%s",buf);	
	ClientID.getString(buf);
	fprintf(fp,",ClientID,%s",buf);	
	InstrumentGroupID.getString(buf);
	fprintf(fp,",InstrumentGroupID,%s",buf);	
	LongPosition.getString(buf);
	fprintf(fp,",LongPosition,%s",buf);	
	LongMargin.getString(buf);
	fprintf(fp,",LongMargin,%s",buf);	
	ShortPosition.getString(buf);
	fprintf(fp,",ShortPosition,%s",buf);	
	ShortMargin.getString(buf);
	fprintf(fp,",ShortMargin,%s",buf);	
	ActualMargin .getString(buf);
	fprintf(fp,",ActualMargin ,%s",buf);	
	LongFrozenPosition.getString(buf);
	fprintf(fp,",LongFrozenPosition,%s",buf);	
	LongFrozenMargin.getString(buf);
	fprintf(fp,",LongFrozenMargin,%s",buf);	
	ShortFrozenPosition.getString(buf);
	fprintf(fp,",ShortFrozenPosition,%s",buf);	
	ShortFrozenMargin.getString(buf);
	fprintf(fp,",ShortFrozenMargin,%s",buf);	
	ActualFrozenMargin .getString(buf);
	fprintf(fp,",ActualFrozenMargin ,%s",buf);	
}

void CWriteablePartClientInsGroupPosition::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	ParticipantID.getString(buf);
	sprintf(p,"ParticipantID=%s,",buf);
	p+=strlen(p);
	ClientID.getString(buf);
	sprintf(p,"ClientID=%s,",buf);
	p+=strlen(p);
	InstrumentGroupID.getString(buf);
	sprintf(p,"InstrumentGroupID=%s,",buf);
	p+=strlen(p);
	LongPosition.getString(buf);
	sprintf(p,"LongPosition=%s,",buf);
	p+=strlen(p);
	LongMargin.getString(buf);
	sprintf(p,"LongMargin=%s,",buf);
	p+=strlen(p);
	ShortPosition.getString(buf);
	sprintf(p,"ShortPosition=%s,",buf);
	p+=strlen(p);
	ShortMargin.getString(buf);
	sprintf(p,"ShortMargin=%s,",buf);
	p+=strlen(p);
	ActualMargin .getString(buf);
	sprintf(p,"ActualMargin =%s,",buf);
	p+=strlen(p);
	LongFrozenPosition.getString(buf);
	sprintf(p,"LongFrozenPosition=%s,",buf);
	p+=strlen(p);
	LongFrozenMargin.getString(buf);
	sprintf(p,"LongFrozenMargin=%s,",buf);
	p+=strlen(p);
	ShortFrozenPosition.getString(buf);
	sprintf(p,"ShortFrozenPosition=%s,",buf);
	p+=strlen(p);
	ShortFrozenMargin.getString(buf);
	sprintf(p,"ShortFrozenMargin=%s,",buf);
	p+=strlen(p);
	ActualFrozenMargin .getString(buf);
	sprintf(p,"ActualFrozenMargin =%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteablePartClientInsGroupPosition::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CPartClientInsGroupPosition");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	ParticipantID.getString(buf);
	pLogger->output(indent+1,0,"ParticipantID=%s 会员代码",buf);
	ClientID.getString(buf);
	pLogger->output(indent+1,0,"ClientID=%s 客户代码",buf);
	InstrumentGroupID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentGroupID=%s 合约组代码",buf);
	LongPosition.getString(buf);
	pLogger->output(indent+1,0,"LongPosition=%s 合约组多头总持仓",buf);
	LongMargin.getString(buf);
	pLogger->output(indent+1,0,"LongMargin=%s 合约组多头保证金之和",buf);
	ShortPosition.getString(buf);
	pLogger->output(indent+1,0,"ShortPosition=%s 合约组空头总持仓",buf);
	ShortMargin.getString(buf);
	pLogger->output(indent+1,0,"ShortMargin=%s 合约组空头保证金之和",buf);
	ActualMargin .getString(buf);
	pLogger->output(indent+1,0,"ActualMargin =%s 实际收取的保证金",buf);
	LongFrozenPosition.getString(buf);
	pLogger->output(indent+1,0,"LongFrozenPosition=%s 合约组多头冻结总持仓",buf);
	LongFrozenMargin.getString(buf);
	pLogger->output(indent+1,0,"LongFrozenMargin=%s 合约组多头冻结保证金之和",buf);
	ShortFrozenPosition.getString(buf);
	pLogger->output(indent+1,0,"ShortFrozenPosition=%s 合约组空头冻结总持仓",buf);
	ShortFrozenMargin.getString(buf);
	pLogger->output(indent+1,0,"ShortFrozenMargin=%s 合约组空头冻结保证金之和",buf);
	ActualFrozenMargin .getString(buf);
	pLogger->output(indent+1,0,"ActualFrozenMargin =%s 实际冻结的保证金",buf);
	pLogger->output(indent,0,"}");
}

CPartClientInsGroupPositionIterator::~CPartClientInsGroupPositionIterator(void)
{
}


void CPartClientInsGroupPositionIterator::dump(FILE *output)
{
	CPartClientInsGroupPosition *pPartClientInsGroupPosition;
	
	while ((pPartClientInsGroupPosition=next())!=NULL)
	{
		pPartClientInsGroupPosition->dump(output);
	}
}



void CWriteableClientMarginCombType::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,ParticipantID,ClientID,InstrumentGroupID,MarginCombType\n");
}
	
void CWriteableClientMarginCombType::init(void)
{
	BrokerID.clear();
	ParticipantID.clear();
	ClientID.clear();
	InstrumentGroupID.clear();
	MarginCombType.clear();
}

int CWriteableClientMarginCombType::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableClientMarginCombType),input)!=sizeof(CWriteableClientMarginCombType))
		return 0;
	else
		return 1;
}
	
int CWriteableClientMarginCombType::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ParticipantID=token;
		}
		else
		{
			ParticipantID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ClientID=token;
		}
		else
		{
			ClientID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentGroupID=token;
		}
		else
		{
			InstrumentGroupID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MarginCombType=token;
		}
		else
		{
			MarginCombType="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"ParticipantID"))
			{
				ParticipantID=token;
			}
			else if (!strcmp(fieldName,"ClientID"))
			{
				ClientID=token;
			}
			else if (!strcmp(fieldName,"InstrumentGroupID"))
			{
				InstrumentGroupID=token;
			}
			else if (!strcmp(fieldName,"MarginCombType"))
			{
				MarginCombType=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableClientMarginCombType::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableClientMarginCombType),output)!=sizeof(CWriteableClientMarginCombType))
		return 0;
	else
		return 1;
}

int CWriteableClientMarginCombType::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ParticipantID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ClientID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentGroupID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MarginCombType.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableClientMarginCombType::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCClientMarginCombType%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,"\t\tParticipantID = %s    [会员代码]\n",buf);	
	ClientID.getString(buf);
	fprintf(fp,"\t\tClientID = %s    [客户代码]\n",buf);	
	InstrumentGroupID.getString(buf);
	fprintf(fp,"\t\tInstrumentGroupID = %s    [合约组代码]\n",buf);	
	MarginCombType.getString(buf);
	fprintf(fp,"\t\tMarginCombType = %s    [保证金组合类型]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableClientMarginCombType::dumpDiff(FILE *fp, const CWriteableClientMarginCombType *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCClientMarginCombType = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	ParticipantID.getString(buf);
	if (compare(ParticipantID.getValue(),pOriginal->ParticipantID.getValue())!=0)
	{
		pOriginal->ParticipantID.getString(bufOriginal);
		fprintf(fp,"\t\tParticipantID = %s -> %s    [会员代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tParticipantID = %s    [会员代码]\n",buf);
	}
	ClientID.getString(buf);
	if (compare(ClientID.getValue(),pOriginal->ClientID.getValue())!=0)
	{
		pOriginal->ClientID.getString(bufOriginal);
		fprintf(fp,"\t\tClientID = %s -> %s    [客户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tClientID = %s    [客户代码]\n",buf);
	}
	InstrumentGroupID.getString(buf);
	if (compare(InstrumentGroupID.getValue(),pOriginal->InstrumentGroupID.getValue())!=0)
	{
		pOriginal->InstrumentGroupID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentGroupID = %s -> %s    [合约组代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentGroupID = %s    [合约组代码]\n",buf);
	}
	MarginCombType.getString(buf);
	if (compare(MarginCombType.getValue(),pOriginal->MarginCombType.getValue())!=0)
	{
		pOriginal->MarginCombType.getString(bufOriginal);
		fprintf(fp,"\t\tMarginCombType = %s -> %s    [保证金组合类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMarginCombType = %s    [保证金组合类型]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableClientMarginCombType::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	ParticipantID.getString(buf);
	fprintf(fp,",ParticipantID,%s",buf);	
	ClientID.getString(buf);
	fprintf(fp,",ClientID,%s",buf);	
	InstrumentGroupID.getString(buf);
	fprintf(fp,",InstrumentGroupID,%s",buf);	
	MarginCombType.getString(buf);
	fprintf(fp,",MarginCombType,%s",buf);	
}

void CWriteableClientMarginCombType::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	ParticipantID.getString(buf);
	sprintf(p,"ParticipantID=%s,",buf);
	p+=strlen(p);
	ClientID.getString(buf);
	sprintf(p,"ClientID=%s,",buf);
	p+=strlen(p);
	InstrumentGroupID.getString(buf);
	sprintf(p,"InstrumentGroupID=%s,",buf);
	p+=strlen(p);
	MarginCombType.getString(buf);
	sprintf(p,"MarginCombType=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableClientMarginCombType::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CClientMarginCombType");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	ParticipantID.getString(buf);
	pLogger->output(indent+1,0,"ParticipantID=%s 会员代码",buf);
	ClientID.getString(buf);
	pLogger->output(indent+1,0,"ClientID=%s 客户代码",buf);
	InstrumentGroupID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentGroupID=%s 合约组代码",buf);
	MarginCombType.getString(buf);
	pLogger->output(indent+1,0,"MarginCombType=%s 保证金组合类型",buf);
	pLogger->output(indent,0,"}");
}

CClientMarginCombTypeIterator::~CClientMarginCombTypeIterator(void)
{
}


void CClientMarginCombTypeIterator::dump(FILE *output)
{
	CClientMarginCombType *pClientMarginCombType;
	
	while ((pClientMarginCombType=next())!=NULL)
	{
		pClientMarginCombType->dump(output);
	}
}



void CWriteableInstrumentGroup::writeCSVHead(FILE *output)
{
	fprintf(output,"ExchangeID,BrokerID,InstrumentID,InstrumentGroupID\n");
}
	
void CWriteableInstrumentGroup::init(void)
{
	ExchangeID.clear();
	BrokerID.clear();
	InstrumentID.clear();
	InstrumentGroupID.clear();
}

int CWriteableInstrumentGroup::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableInstrumentGroup),input)!=sizeof(CWriteableInstrumentGroup))
		return 0;
	else
		return 1;
}
	
int CWriteableInstrumentGroup::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentGroupID=token;
		}
		else
		{
			InstrumentGroupID="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"InstrumentGroupID"))
			{
				InstrumentGroupID=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableInstrumentGroup::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableInstrumentGroup),output)!=sizeof(CWriteableInstrumentGroup))
		return 0;
	else
		return 1;
}

int CWriteableInstrumentGroup::writeCSV(FILE *output) const
{
	char buffer[1025];
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentGroupID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableInstrumentGroup::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCInstrumentGroup%s = {\n", index_buf);
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	InstrumentGroupID.getString(buf);
	fprintf(fp,"\t\tInstrumentGroupID = %s    [合约组代码]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableInstrumentGroup::dumpDiff(FILE *fp, const CWriteableInstrumentGroup *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCInstrumentGroup = {\n");
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	InstrumentGroupID.getString(buf);
	if (compare(InstrumentGroupID.getValue(),pOriginal->InstrumentGroupID.getValue())!=0)
	{
		pOriginal->InstrumentGroupID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentGroupID = %s -> %s    [合约组代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentGroupID = %s    [合约组代码]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableInstrumentGroup::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	InstrumentGroupID.getString(buf);
	fprintf(fp,",InstrumentGroupID,%s",buf);	
}

void CWriteableInstrumentGroup::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	InstrumentGroupID.getString(buf);
	sprintf(p,"InstrumentGroupID=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableInstrumentGroup::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CInstrumentGroup");
	pLogger->output(indent,0,"{");
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	InstrumentGroupID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentGroupID=%s 合约组代码",buf);
	pLogger->output(indent,0,"}");
}

CInstrumentGroupIterator::~CInstrumentGroupIterator(void)
{
}


void CInstrumentGroupIterator::dump(FILE *output)
{
	CInstrumentGroup *pInstrumentGroup;
	
	while ((pInstrumentGroup=next())!=NULL)
	{
		pInstrumentGroup->dump(output);
	}
}



void CWriteableSGEDeferRate::writeCSVHead(FILE *output)
{
	fprintf(output,"InstrumentID,ExchangeID,TradeDate,Direction,DeferRate\n");
}
	
void CWriteableSGEDeferRate::init(void)
{
	InstrumentID.clear();
	ExchangeID.clear();
	TradeDate.clear();
	Direction.clear();
	DeferRate.clear();
}

int CWriteableSGEDeferRate::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableSGEDeferRate),input)!=sizeof(CWriteableSGEDeferRate))
		return 0;
	else
		return 1;
}
	
int CWriteableSGEDeferRate::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradeDate=token;
		}
		else
		{
			TradeDate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Direction=token;
		}
		else
		{
			Direction="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			DeferRate=token;
		}
		else
		{
			DeferRate="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"TradeDate"))
			{
				TradeDate=token;
			}
			else if (!strcmp(fieldName,"Direction"))
			{
				Direction=token;
			}
			else if (!strcmp(fieldName,"DeferRate"))
			{
				DeferRate=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableSGEDeferRate::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableSGEDeferRate),output)!=sizeof(CWriteableSGEDeferRate))
		return 0;
	else
		return 1;
}

int CWriteableSGEDeferRate::writeCSV(FILE *output) const
{
	char buffer[1025];
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradeDate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Direction.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	DeferRate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableSGEDeferRate::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCSGEDeferRate%s = {\n", index_buf);
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	TradeDate.getString(buf);
	fprintf(fp,"\t\tTradeDate = %s    [交易日期]\n",buf);	
	Direction.getString(buf);
	fprintf(fp,"\t\tDirection = %s    [支付方向]\n",buf);	
	DeferRate.getString(buf);
	fprintf(fp,"\t\tDeferRate = %s    [递延费率]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableSGEDeferRate::dumpDiff(FILE *fp, const CWriteableSGEDeferRate *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCSGEDeferRate = {\n");
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	TradeDate.getString(buf);
	if (compare(TradeDate.getValue(),pOriginal->TradeDate.getValue())!=0)
	{
		pOriginal->TradeDate.getString(bufOriginal);
		fprintf(fp,"\t\tTradeDate = %s -> %s    [交易日期]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradeDate = %s    [交易日期]\n",buf);
	}
	Direction.getString(buf);
	if (compare(Direction.getValue(),pOriginal->Direction.getValue())!=0)
	{
		pOriginal->Direction.getString(bufOriginal);
		fprintf(fp,"\t\tDirection = %s -> %s    [支付方向]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDirection = %s    [支付方向]\n",buf);
	}
	DeferRate.getString(buf);
	if (compare(DeferRate.getValue(),pOriginal->DeferRate.getValue())!=0)
	{
		pOriginal->DeferRate.getString(bufOriginal);
		fprintf(fp,"\t\tDeferRate = %s -> %s    [递延费率]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tDeferRate = %s    [递延费率]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableSGEDeferRate::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	TradeDate.getString(buf);
	fprintf(fp,",TradeDate,%s",buf);	
	Direction.getString(buf);
	fprintf(fp,",Direction,%s",buf);	
	DeferRate.getString(buf);
	fprintf(fp,",DeferRate,%s",buf);	
}

void CWriteableSGEDeferRate::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	TradeDate.getString(buf);
	sprintf(p,"TradeDate=%s,",buf);
	p+=strlen(p);
	Direction.getString(buf);
	sprintf(p,"Direction=%s,",buf);
	p+=strlen(p);
	DeferRate.getString(buf);
	sprintf(p,"DeferRate=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableSGEDeferRate::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CSGEDeferRate");
	pLogger->output(indent,0,"{");
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	TradeDate.getString(buf);
	pLogger->output(indent+1,0,"TradeDate=%s 交易日期",buf);
	Direction.getString(buf);
	pLogger->output(indent+1,0,"Direction=%s 支付方向",buf);
	DeferRate.getString(buf);
	pLogger->output(indent+1,0,"DeferRate=%s 递延费率",buf);
	pLogger->output(indent,0,"}");
}

CSGEDeferRateIterator::~CSGEDeferRateIterator(void)
{
}


void CSGEDeferRateIterator::dump(FILE *output)
{
	CSGEDeferRate *pSGEDeferRate;
	
	while ((pSGEDeferRate=next())!=NULL)
	{
		pSGEDeferRate->dump(output);
	}
}



void CWriteableInvestorTradingRight::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,InvestorID,ExchangeID,InstrumentID,TradingRight,ProductClass\n");
}
	
void CWriteableInvestorTradingRight::init(void)
{
	BrokerID.clear();
	InvestorID.clear();
	ExchangeID.clear();
	InstrumentID.clear();
	TradingRight.clear();
	ProductClass.clear();
}

int CWriteableInvestorTradingRight::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableInvestorTradingRight),input)!=sizeof(CWriteableInvestorTradingRight))
		return 0;
	else
		return 1;
}
	
int CWriteableInvestorTradingRight::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			TradingRight=token;
		}
		else
		{
			TradingRight="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ProductClass=token;
		}
		else
		{
			ProductClass="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"TradingRight"))
			{
				TradingRight=token;
			}
			else if (!strcmp(fieldName,"ProductClass"))
			{
				ProductClass=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableInvestorTradingRight::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableInvestorTradingRight),output)!=sizeof(CWriteableInvestorTradingRight))
		return 0;
	else
		return 1;
}

int CWriteableInvestorTradingRight::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	TradingRight.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ProductClass.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableInvestorTradingRight::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCInvestorTradingRight%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	TradingRight.getString(buf);
	fprintf(fp,"\t\tTradingRight = %s    [合约交易权限]\n",buf);	
	ProductClass.getString(buf);
	fprintf(fp,"\t\tProductClass = %s    [产品类型]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableInvestorTradingRight::dumpDiff(FILE *fp, const CWriteableInvestorTradingRight *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCInvestorTradingRight = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编号]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	TradingRight.getString(buf);
	if (compare(TradingRight.getValue(),pOriginal->TradingRight.getValue())!=0)
	{
		pOriginal->TradingRight.getString(bufOriginal);
		fprintf(fp,"\t\tTradingRight = %s -> %s    [合约交易权限]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradingRight = %s    [合约交易权限]\n",buf);
	}
	ProductClass.getString(buf);
	if (compare(ProductClass.getValue(),pOriginal->ProductClass.getValue())!=0)
	{
		pOriginal->ProductClass.getString(bufOriginal);
		fprintf(fp,"\t\tProductClass = %s -> %s    [产品类型]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tProductClass = %s    [产品类型]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableInvestorTradingRight::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	TradingRight.getString(buf);
	fprintf(fp,",TradingRight,%s",buf);	
	ProductClass.getString(buf);
	fprintf(fp,",ProductClass,%s",buf);	
}

void CWriteableInvestorTradingRight::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	TradingRight.getString(buf);
	sprintf(p,"TradingRight=%s,",buf);
	p+=strlen(p);
	ProductClass.getString(buf);
	sprintf(p,"ProductClass=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableInvestorTradingRight::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CInvestorTradingRight");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编号",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	TradingRight.getString(buf);
	pLogger->output(indent+1,0,"TradingRight=%s 合约交易权限",buf);
	ProductClass.getString(buf);
	pLogger->output(indent+1,0,"ProductClass=%s 产品类型",buf);
	pLogger->output(indent,0,"}");
}

CInvestorTradingRightIterator::~CInvestorTradingRightIterator(void)
{
}


void CInvestorTradingRightIterator::dump(FILE *output)
{
	CInvestorTradingRight *pInvestorTradingRight;
	
	while ((pInvestorTradingRight=next())!=NULL)
	{
		pInvestorTradingRight->dump(output);
	}
}



void CWriteableUserIP::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,UserID,IPAddress,IPMask,MacAddress\n");
}
	
void CWriteableUserIP::init(void)
{
	BrokerID.clear();
	UserID.clear();
	IPAddress.clear();
	IPMask.clear();
	MacAddress.clear();
}

int CWriteableUserIP::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableUserIP),input)!=sizeof(CWriteableUserIP))
		return 0;
	else
		return 1;
}
	
int CWriteableUserIP::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserID=token;
		}
		else
		{
			UserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IPAddress=token;
		}
		else
		{
			IPAddress="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			IPMask=token;
		}
		else
		{
			IPMask="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			MacAddress=token;
		}
		else
		{
			MacAddress="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"UserID"))
			{
				UserID=token;
			}
			else if (!strcmp(fieldName,"IPAddress"))
			{
				IPAddress=token;
			}
			else if (!strcmp(fieldName,"IPMask"))
			{
				IPMask=token;
			}
			else if (!strcmp(fieldName,"MacAddress"))
			{
				MacAddress=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableUserIP::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableUserIP),output)!=sizeof(CWriteableUserIP))
		return 0;
	else
		return 1;
}

int CWriteableUserIP::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IPAddress.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	IPMask.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	MacAddress.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableUserIP::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCUserIP%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	UserID.getString(buf);
	fprintf(fp,"\t\tUserID = %s    [交易用户代码]\n",buf);	
	IPAddress.getString(buf);
	fprintf(fp,"\t\tIPAddress = %s    [IP地址]\n",buf);	
	IPMask.getString(buf);
	fprintf(fp,"\t\tIPMask = %s    [IP地址掩码]\n",buf);	
	MacAddress.getString(buf);
	fprintf(fp,"\t\tMacAddress = %s    [MAC地址]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableUserIP::dumpDiff(FILE *fp, const CWriteableUserIP *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCUserIP = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	UserID.getString(buf);
	if (compare(UserID.getValue(),pOriginal->UserID.getValue())!=0)
	{
		pOriginal->UserID.getString(bufOriginal);
		fprintf(fp,"\t\tUserID = %s -> %s    [交易用户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserID = %s    [交易用户代码]\n",buf);
	}
	IPAddress.getString(buf);
	if (compare(IPAddress.getValue(),pOriginal->IPAddress.getValue())!=0)
	{
		pOriginal->IPAddress.getString(bufOriginal);
		fprintf(fp,"\t\tIPAddress = %s -> %s    [IP地址]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIPAddress = %s    [IP地址]\n",buf);
	}
	IPMask.getString(buf);
	if (compare(IPMask.getValue(),pOriginal->IPMask.getValue())!=0)
	{
		pOriginal->IPMask.getString(bufOriginal);
		fprintf(fp,"\t\tIPMask = %s -> %s    [IP地址掩码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tIPMask = %s    [IP地址掩码]\n",buf);
	}
	MacAddress.getString(buf);
	if (compare(MacAddress.getValue(),pOriginal->MacAddress.getValue())!=0)
	{
		pOriginal->MacAddress.getString(bufOriginal);
		fprintf(fp,"\t\tMacAddress = %s -> %s    [MAC地址]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tMacAddress = %s    [MAC地址]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableUserIP::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	UserID.getString(buf);
	fprintf(fp,",UserID,%s",buf);	
	IPAddress.getString(buf);
	fprintf(fp,",IPAddress,%s",buf);	
	IPMask.getString(buf);
	fprintf(fp,",IPMask,%s",buf);	
	MacAddress.getString(buf);
	fprintf(fp,",MacAddress,%s",buf);	
}

void CWriteableUserIP::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	UserID.getString(buf);
	sprintf(p,"UserID=%s,",buf);
	p+=strlen(p);
	IPAddress.getString(buf);
	sprintf(p,"IPAddress=%s,",buf);
	p+=strlen(p);
	IPMask.getString(buf);
	sprintf(p,"IPMask=%s,",buf);
	p+=strlen(p);
	MacAddress.getString(buf);
	sprintf(p,"MacAddress=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableUserIP::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CUserIP");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	UserID.getString(buf);
	pLogger->output(indent+1,0,"UserID=%s 交易用户代码",buf);
	IPAddress.getString(buf);
	pLogger->output(indent+1,0,"IPAddress=%s IP地址",buf);
	IPMask.getString(buf);
	pLogger->output(indent+1,0,"IPMask=%s IP地址掩码",buf);
	MacAddress.getString(buf);
	pLogger->output(indent+1,0,"MacAddress=%s MAC地址",buf);
	pLogger->output(indent,0,"}");
}

CUserIPIterator::~CUserIPIterator(void)
{
}


void CUserIPIterator::dump(FILE *output)
{
	CUserIP *pUserIP;
	
	while ((pUserIP=next())!=NULL)
	{
		pUserIP->dump(output);
	}
}



void CWriteableInvestorOptionFee::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,ExchangeID,InvestorID,InstrumentID,OpenFeeRate,OpenFeeAmt,OffsetFeeRate,OffsetFeeAmt,OTFeeRate,OTFeeAmt,StrikeFeeRate,StrikeFeeAmt\n");
}
	
void CWriteableInvestorOptionFee::init(void)
{
	BrokerID.clear();
	ExchangeID.clear();
	InvestorID.clear();
	InstrumentID.clear();
	OpenFeeRate.clear();
	OpenFeeAmt.clear();
	OffsetFeeRate.clear();
	OffsetFeeAmt.clear();
	OTFeeRate.clear();
	OTFeeAmt.clear();
	StrikeFeeRate.clear();
	StrikeFeeAmt.clear();
}

int CWriteableInvestorOptionFee::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableInvestorOptionFee),input)!=sizeof(CWriteableInvestorOptionFee))
		return 0;
	else
		return 1;
}
	
int CWriteableInvestorOptionFee::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InvestorID=token;
		}
		else
		{
			InvestorID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OpenFeeRate=token;
		}
		else
		{
			OpenFeeRate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OpenFeeAmt=token;
		}
		else
		{
			OpenFeeAmt="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OffsetFeeRate=token;
		}
		else
		{
			OffsetFeeRate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OffsetFeeAmt=token;
		}
		else
		{
			OffsetFeeAmt="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OTFeeRate=token;
		}
		else
		{
			OTFeeRate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OTFeeAmt=token;
		}
		else
		{
			OTFeeAmt="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			StrikeFeeRate=token;
		}
		else
		{
			StrikeFeeRate="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			StrikeFeeAmt=token;
		}
		else
		{
			StrikeFeeAmt="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"InvestorID"))
			{
				InvestorID=token;
			}
			else if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"OpenFeeRate"))
			{
				OpenFeeRate=token;
			}
			else if (!strcmp(fieldName,"OpenFeeAmt"))
			{
				OpenFeeAmt=token;
			}
			else if (!strcmp(fieldName,"OffsetFeeRate"))
			{
				OffsetFeeRate=token;
			}
			else if (!strcmp(fieldName,"OffsetFeeAmt"))
			{
				OffsetFeeAmt=token;
			}
			else if (!strcmp(fieldName,"OTFeeRate"))
			{
				OTFeeRate=token;
			}
			else if (!strcmp(fieldName,"OTFeeAmt"))
			{
				OTFeeAmt=token;
			}
			else if (!strcmp(fieldName,"StrikeFeeRate"))
			{
				StrikeFeeRate=token;
			}
			else if (!strcmp(fieldName,"StrikeFeeAmt"))
			{
				StrikeFeeAmt=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableInvestorOptionFee::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableInvestorOptionFee),output)!=sizeof(CWriteableInvestorOptionFee))
		return 0;
	else
		return 1;
}

int CWriteableInvestorOptionFee::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InvestorID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OpenFeeRate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OpenFeeAmt.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OffsetFeeRate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OffsetFeeAmt.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OTFeeRate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OTFeeAmt.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	StrikeFeeRate.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	StrikeFeeAmt.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableInvestorOptionFee::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCInvestorOptionFee%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	InvestorID.getString(buf);
	fprintf(fp,"\t\tInvestorID = %s    [投资者编码]\n",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	OpenFeeRate.getString(buf);
	fprintf(fp,"\t\tOpenFeeRate = %s    [开仓手续费按比例]\n",buf);	
	OpenFeeAmt.getString(buf);
	fprintf(fp,"\t\tOpenFeeAmt = %s    [开仓手续费按手数]\n",buf);	
	OffsetFeeRate.getString(buf);
	fprintf(fp,"\t\tOffsetFeeRate = %s    [平仓手续费按比例]\n",buf);	
	OffsetFeeAmt.getString(buf);
	fprintf(fp,"\t\tOffsetFeeAmt = %s    [平仓手续费按手数]\n",buf);	
	OTFeeRate.getString(buf);
	fprintf(fp,"\t\tOTFeeRate = %s    [平今仓手续费按比例]\n",buf);	
	OTFeeAmt.getString(buf);
	fprintf(fp,"\t\tOTFeeAmt = %s    [平今仓手续费按手数]\n",buf);	
	StrikeFeeRate.getString(buf);
	fprintf(fp,"\t\tStrikeFeeRate = %s    [执行手续费按比例]\n",buf);	
	StrikeFeeAmt.getString(buf);
	fprintf(fp,"\t\tStrikeFeeAmt = %s    [执行手续费按手数]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableInvestorOptionFee::dumpDiff(FILE *fp, const CWriteableInvestorOptionFee *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCInvestorOptionFee = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	InvestorID.getString(buf);
	if (compare(InvestorID.getValue(),pOriginal->InvestorID.getValue())!=0)
	{
		pOriginal->InvestorID.getString(bufOriginal);
		fprintf(fp,"\t\tInvestorID = %s -> %s    [投资者编码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInvestorID = %s    [投资者编码]\n",buf);
	}
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	OpenFeeRate.getString(buf);
	if (compare(OpenFeeRate.getValue(),pOriginal->OpenFeeRate.getValue())!=0)
	{
		pOriginal->OpenFeeRate.getString(bufOriginal);
		fprintf(fp,"\t\tOpenFeeRate = %s -> %s    [开仓手续费按比例]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOpenFeeRate = %s    [开仓手续费按比例]\n",buf);
	}
	OpenFeeAmt.getString(buf);
	if (compare(OpenFeeAmt.getValue(),pOriginal->OpenFeeAmt.getValue())!=0)
	{
		pOriginal->OpenFeeAmt.getString(bufOriginal);
		fprintf(fp,"\t\tOpenFeeAmt = %s -> %s    [开仓手续费按手数]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOpenFeeAmt = %s    [开仓手续费按手数]\n",buf);
	}
	OffsetFeeRate.getString(buf);
	if (compare(OffsetFeeRate.getValue(),pOriginal->OffsetFeeRate.getValue())!=0)
	{
		pOriginal->OffsetFeeRate.getString(bufOriginal);
		fprintf(fp,"\t\tOffsetFeeRate = %s -> %s    [平仓手续费按比例]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOffsetFeeRate = %s    [平仓手续费按比例]\n",buf);
	}
	OffsetFeeAmt.getString(buf);
	if (compare(OffsetFeeAmt.getValue(),pOriginal->OffsetFeeAmt.getValue())!=0)
	{
		pOriginal->OffsetFeeAmt.getString(bufOriginal);
		fprintf(fp,"\t\tOffsetFeeAmt = %s -> %s    [平仓手续费按手数]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOffsetFeeAmt = %s    [平仓手续费按手数]\n",buf);
	}
	OTFeeRate.getString(buf);
	if (compare(OTFeeRate.getValue(),pOriginal->OTFeeRate.getValue())!=0)
	{
		pOriginal->OTFeeRate.getString(bufOriginal);
		fprintf(fp,"\t\tOTFeeRate = %s -> %s    [平今仓手续费按比例]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOTFeeRate = %s    [平今仓手续费按比例]\n",buf);
	}
	OTFeeAmt.getString(buf);
	if (compare(OTFeeAmt.getValue(),pOriginal->OTFeeAmt.getValue())!=0)
	{
		pOriginal->OTFeeAmt.getString(bufOriginal);
		fprintf(fp,"\t\tOTFeeAmt = %s -> %s    [平今仓手续费按手数]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOTFeeAmt = %s    [平今仓手续费按手数]\n",buf);
	}
	StrikeFeeRate.getString(buf);
	if (compare(StrikeFeeRate.getValue(),pOriginal->StrikeFeeRate.getValue())!=0)
	{
		pOriginal->StrikeFeeRate.getString(bufOriginal);
		fprintf(fp,"\t\tStrikeFeeRate = %s -> %s    [执行手续费按比例]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tStrikeFeeRate = %s    [执行手续费按比例]\n",buf);
	}
	StrikeFeeAmt.getString(buf);
	if (compare(StrikeFeeAmt.getValue(),pOriginal->StrikeFeeAmt.getValue())!=0)
	{
		pOriginal->StrikeFeeAmt.getString(bufOriginal);
		fprintf(fp,"\t\tStrikeFeeAmt = %s -> %s    [执行手续费按手数]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tStrikeFeeAmt = %s    [执行手续费按手数]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableInvestorOptionFee::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	InvestorID.getString(buf);
	fprintf(fp,",InvestorID,%s",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	OpenFeeRate.getString(buf);
	fprintf(fp,",OpenFeeRate,%s",buf);	
	OpenFeeAmt.getString(buf);
	fprintf(fp,",OpenFeeAmt,%s",buf);	
	OffsetFeeRate.getString(buf);
	fprintf(fp,",OffsetFeeRate,%s",buf);	
	OffsetFeeAmt.getString(buf);
	fprintf(fp,",OffsetFeeAmt,%s",buf);	
	OTFeeRate.getString(buf);
	fprintf(fp,",OTFeeRate,%s",buf);	
	OTFeeAmt.getString(buf);
	fprintf(fp,",OTFeeAmt,%s",buf);	
	StrikeFeeRate.getString(buf);
	fprintf(fp,",StrikeFeeRate,%s",buf);	
	StrikeFeeAmt.getString(buf);
	fprintf(fp,",StrikeFeeAmt,%s",buf);	
}

void CWriteableInvestorOptionFee::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	InvestorID.getString(buf);
	sprintf(p,"InvestorID=%s,",buf);
	p+=strlen(p);
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	OpenFeeRate.getString(buf);
	sprintf(p,"OpenFeeRate=%s,",buf);
	p+=strlen(p);
	OpenFeeAmt.getString(buf);
	sprintf(p,"OpenFeeAmt=%s,",buf);
	p+=strlen(p);
	OffsetFeeRate.getString(buf);
	sprintf(p,"OffsetFeeRate=%s,",buf);
	p+=strlen(p);
	OffsetFeeAmt.getString(buf);
	sprintf(p,"OffsetFeeAmt=%s,",buf);
	p+=strlen(p);
	OTFeeRate.getString(buf);
	sprintf(p,"OTFeeRate=%s,",buf);
	p+=strlen(p);
	OTFeeAmt.getString(buf);
	sprintf(p,"OTFeeAmt=%s,",buf);
	p+=strlen(p);
	StrikeFeeRate.getString(buf);
	sprintf(p,"StrikeFeeRate=%s,",buf);
	p+=strlen(p);
	StrikeFeeAmt.getString(buf);
	sprintf(p,"StrikeFeeAmt=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableInvestorOptionFee::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CInvestorOptionFee");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	InvestorID.getString(buf);
	pLogger->output(indent+1,0,"InvestorID=%s 投资者编码",buf);
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	OpenFeeRate.getString(buf);
	pLogger->output(indent+1,0,"OpenFeeRate=%s 开仓手续费按比例",buf);
	OpenFeeAmt.getString(buf);
	pLogger->output(indent+1,0,"OpenFeeAmt=%s 开仓手续费按手数",buf);
	OffsetFeeRate.getString(buf);
	pLogger->output(indent+1,0,"OffsetFeeRate=%s 平仓手续费按比例",buf);
	OffsetFeeAmt.getString(buf);
	pLogger->output(indent+1,0,"OffsetFeeAmt=%s 平仓手续费按手数",buf);
	OTFeeRate.getString(buf);
	pLogger->output(indent+1,0,"OTFeeRate=%s 平今仓手续费按比例",buf);
	OTFeeAmt.getString(buf);
	pLogger->output(indent+1,0,"OTFeeAmt=%s 平今仓手续费按手数",buf);
	StrikeFeeRate.getString(buf);
	pLogger->output(indent+1,0,"StrikeFeeRate=%s 执行手续费按比例",buf);
	StrikeFeeAmt.getString(buf);
	pLogger->output(indent+1,0,"StrikeFeeAmt=%s 执行手续费按手数",buf);
	pLogger->output(indent,0,"}");
}

CInvestorOptionFeeIterator::~CInvestorOptionFeeIterator(void)
{
}


void CInvestorOptionFeeIterator::dump(FILE *output)
{
	CInvestorOptionFee *pInvestorOptionFee;
	
	while ((pInvestorOptionFee=next())!=NULL)
	{
		pInvestorOptionFee->dump(output);
	}
}



void CWriteableMarketData::writeCSVHead(FILE *output)
{
	fprintf(output,"TradingDay,ExchangeID,InstrumentID,OpenPrice,HighestPrice,LowestPrice,LastPrice,Volume,Turnover,LowerLimitPrice,UpperLimitPrice,OpenInterest,PreClosePrice,PreOpenInterest,PreSettlementPrice,SettlementPrice,UpdateMillisec,UpdateTime\n");
}
	
void CWriteableMarketData::init(void)
{
	TradingDay.clear();
	ExchangeID.clear();
	InstrumentID.clear();
	OpenPrice.clear();
	HighestPrice.clear();
	LowestPrice.clear();
	LastPrice.clear();
	Volume.clear();
	Turnover.clear();
	LowerLimitPrice.clear();
	UpperLimitPrice.clear();
	OpenInterest.clear();
	PreClosePrice.clear();
	PreOpenInterest.clear();
	PreSettlementPrice.clear();
	SettlementPrice.clear();
	UpdateMillisec.clear();
	UpdateTime.clear();
}

int CWriteableMarketData::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableMarketData),input)!=sizeof(CWriteableMarketData))
		return 0;
	else
		return 1;
}
	
int CWriteableMarketData::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			TradingDay=token;
		}
		else
		{
			TradingDay="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			ExchangeID=token;
		}
		else
		{
			ExchangeID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			InstrumentID=token;
		}
		else
		{
			InstrumentID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OpenPrice=token;
		}
		else
		{
			OpenPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			HighestPrice=token;
		}
		else
		{
			HighestPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LowestPrice=token;
		}
		else
		{
			LowestPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LastPrice=token;
		}
		else
		{
			LastPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Volume=token;
		}
		else
		{
			Volume="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			Turnover=token;
		}
		else
		{
			Turnover="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			LowerLimitPrice=token;
		}
		else
		{
			LowerLimitPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UpperLimitPrice=token;
		}
		else
		{
			UpperLimitPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			OpenInterest=token;
		}
		else
		{
			OpenInterest="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			PreClosePrice=token;
		}
		else
		{
			PreClosePrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			PreOpenInterest=token;
		}
		else
		{
			PreOpenInterest="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			PreSettlementPrice=token;
		}
		else
		{
			PreSettlementPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SettlementPrice=token;
		}
		else
		{
			SettlementPrice="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UpdateMillisec=token;
		}
		else
		{
			UpdateMillisec="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UpdateTime=token;
		}
		else
		{
			UpdateTime="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"TradingDay"))
			{
				TradingDay=token;
			}
			else if (!strcmp(fieldName,"ExchangeID"))
			{
				ExchangeID=token;
			}
			else if (!strcmp(fieldName,"InstrumentID"))
			{
				InstrumentID=token;
			}
			else if (!strcmp(fieldName,"OpenPrice"))
			{
				OpenPrice=token;
			}
			else if (!strcmp(fieldName,"HighestPrice"))
			{
				HighestPrice=token;
			}
			else if (!strcmp(fieldName,"LowestPrice"))
			{
				LowestPrice=token;
			}
			else if (!strcmp(fieldName,"LastPrice"))
			{
				LastPrice=token;
			}
			else if (!strcmp(fieldName,"Volume"))
			{
				Volume=token;
			}
			else if (!strcmp(fieldName,"Turnover"))
			{
				Turnover=token;
			}
			else if (!strcmp(fieldName,"LowerLimitPrice"))
			{
				LowerLimitPrice=token;
			}
			else if (!strcmp(fieldName,"UpperLimitPrice"))
			{
				UpperLimitPrice=token;
			}
			else if (!strcmp(fieldName,"OpenInterest"))
			{
				OpenInterest=token;
			}
			else if (!strcmp(fieldName,"PreClosePrice"))
			{
				PreClosePrice=token;
			}
			else if (!strcmp(fieldName,"PreOpenInterest"))
			{
				PreOpenInterest=token;
			}
			else if (!strcmp(fieldName,"PreSettlementPrice"))
			{
				PreSettlementPrice=token;
			}
			else if (!strcmp(fieldName,"SettlementPrice"))
			{
				SettlementPrice=token;
			}
			else if (!strcmp(fieldName,"UpdateMillisec"))
			{
				UpdateMillisec=token;
			}
			else if (!strcmp(fieldName,"UpdateTime"))
			{
				UpdateTime=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableMarketData::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableMarketData),output)!=sizeof(CWriteableMarketData))
		return 0;
	else
		return 1;
}

int CWriteableMarketData::writeCSV(FILE *output) const
{
	char buffer[1025];
	TradingDay.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	ExchangeID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	InstrumentID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OpenPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	HighestPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LowestPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LastPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Volume.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	Turnover.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	LowerLimitPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UpperLimitPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	OpenInterest.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	PreClosePrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	PreOpenInterest.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	PreSettlementPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SettlementPrice.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UpdateMillisec.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UpdateTime.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableMarketData::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCMarketData%s = {\n", index_buf);
	TradingDay.getString(buf);
	fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);	
	OpenPrice.getString(buf);
	fprintf(fp,"\t\tOpenPrice = %s    [今开盘]\n",buf);	
	HighestPrice.getString(buf);
	fprintf(fp,"\t\tHighestPrice = %s    [最高价]\n",buf);	
	LowestPrice.getString(buf);
	fprintf(fp,"\t\tLowestPrice = %s    [最低价]\n",buf);	
	LastPrice.getString(buf);
	fprintf(fp,"\t\tLastPrice = %s    [最新价]\n",buf);	
	Volume.getString(buf);
	fprintf(fp,"\t\tVolume = %s    [数量]\n",buf);	
	Turnover.getString(buf);
	fprintf(fp,"\t\tTurnover = %s    [成交金额]\n",buf);	
	LowerLimitPrice.getString(buf);
	fprintf(fp,"\t\tLowerLimitPrice = %s    [跌停板价]\n",buf);	
	UpperLimitPrice.getString(buf);
	fprintf(fp,"\t\tUpperLimitPrice = %s    [涨停板价]\n",buf);	
	OpenInterest.getString(buf);
	fprintf(fp,"\t\tOpenInterest = %s    [持仓量]\n",buf);	
	PreClosePrice.getString(buf);
	fprintf(fp,"\t\tPreClosePrice = %s    [昨收盘]\n",buf);	
	PreOpenInterest.getString(buf);
	fprintf(fp,"\t\tPreOpenInterest = %s    [昨持仓量]\n",buf);	
	PreSettlementPrice.getString(buf);
	fprintf(fp,"\t\tPreSettlementPrice = %s    [昨结算]\n",buf);	
	SettlementPrice.getString(buf);
	fprintf(fp,"\t\tSettlementPrice = %s    [今结算]\n",buf);	
	UpdateMillisec.getString(buf);
	fprintf(fp,"\t\tUpdateMillisec = %s    [最后修改毫秒]\n",buf);	
	UpdateTime.getString(buf);
	fprintf(fp,"\t\tUpdateTime = %s    [最后修改时间]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableMarketData::dumpDiff(FILE *fp, const CWriteableMarketData *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCMarketData = {\n");
	TradingDay.getString(buf);
	if (compare(TradingDay.getValue(),pOriginal->TradingDay.getValue())!=0)
	{
		pOriginal->TradingDay.getString(bufOriginal);
		fprintf(fp,"\t\tTradingDay = %s -> %s    [交易日]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTradingDay = %s    [交易日]\n",buf);
	}
	ExchangeID.getString(buf);
	if (compare(ExchangeID.getValue(),pOriginal->ExchangeID.getValue())!=0)
	{
		pOriginal->ExchangeID.getString(bufOriginal);
		fprintf(fp,"\t\tExchangeID = %s -> %s    [交易所代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tExchangeID = %s    [交易所代码]\n",buf);
	}
	InstrumentID.getString(buf);
	if (compare(InstrumentID.getValue(),pOriginal->InstrumentID.getValue())!=0)
	{
		pOriginal->InstrumentID.getString(bufOriginal);
		fprintf(fp,"\t\tInstrumentID = %s -> %s    [合约代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tInstrumentID = %s    [合约代码]\n",buf);
	}
	OpenPrice.getString(buf);
	if (compare(OpenPrice.getValue(),pOriginal->OpenPrice.getValue())!=0)
	{
		pOriginal->OpenPrice.getString(bufOriginal);
		fprintf(fp,"\t\tOpenPrice = %s -> %s    [今开盘]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOpenPrice = %s    [今开盘]\n",buf);
	}
	HighestPrice.getString(buf);
	if (compare(HighestPrice.getValue(),pOriginal->HighestPrice.getValue())!=0)
	{
		pOriginal->HighestPrice.getString(bufOriginal);
		fprintf(fp,"\t\tHighestPrice = %s -> %s    [最高价]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tHighestPrice = %s    [最高价]\n",buf);
	}
	LowestPrice.getString(buf);
	if (compare(LowestPrice.getValue(),pOriginal->LowestPrice.getValue())!=0)
	{
		pOriginal->LowestPrice.getString(bufOriginal);
		fprintf(fp,"\t\tLowestPrice = %s -> %s    [最低价]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLowestPrice = %s    [最低价]\n",buf);
	}
	LastPrice.getString(buf);
	if (compare(LastPrice.getValue(),pOriginal->LastPrice.getValue())!=0)
	{
		pOriginal->LastPrice.getString(bufOriginal);
		fprintf(fp,"\t\tLastPrice = %s -> %s    [最新价]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLastPrice = %s    [最新价]\n",buf);
	}
	Volume.getString(buf);
	if (compare(Volume.getValue(),pOriginal->Volume.getValue())!=0)
	{
		pOriginal->Volume.getString(bufOriginal);
		fprintf(fp,"\t\tVolume = %s -> %s    [数量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tVolume = %s    [数量]\n",buf);
	}
	Turnover.getString(buf);
	if (compare(Turnover.getValue(),pOriginal->Turnover.getValue())!=0)
	{
		pOriginal->Turnover.getString(bufOriginal);
		fprintf(fp,"\t\tTurnover = %s -> %s    [成交金额]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tTurnover = %s    [成交金额]\n",buf);
	}
	LowerLimitPrice.getString(buf);
	if (compare(LowerLimitPrice.getValue(),pOriginal->LowerLimitPrice.getValue())!=0)
	{
		pOriginal->LowerLimitPrice.getString(bufOriginal);
		fprintf(fp,"\t\tLowerLimitPrice = %s -> %s    [跌停板价]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tLowerLimitPrice = %s    [跌停板价]\n",buf);
	}
	UpperLimitPrice.getString(buf);
	if (compare(UpperLimitPrice.getValue(),pOriginal->UpperLimitPrice.getValue())!=0)
	{
		pOriginal->UpperLimitPrice.getString(bufOriginal);
		fprintf(fp,"\t\tUpperLimitPrice = %s -> %s    [涨停板价]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUpperLimitPrice = %s    [涨停板价]\n",buf);
	}
	OpenInterest.getString(buf);
	if (compare(OpenInterest.getValue(),pOriginal->OpenInterest.getValue())!=0)
	{
		pOriginal->OpenInterest.getString(bufOriginal);
		fprintf(fp,"\t\tOpenInterest = %s -> %s    [持仓量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tOpenInterest = %s    [持仓量]\n",buf);
	}
	PreClosePrice.getString(buf);
	if (compare(PreClosePrice.getValue(),pOriginal->PreClosePrice.getValue())!=0)
	{
		pOriginal->PreClosePrice.getString(bufOriginal);
		fprintf(fp,"\t\tPreClosePrice = %s -> %s    [昨收盘]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPreClosePrice = %s    [昨收盘]\n",buf);
	}
	PreOpenInterest.getString(buf);
	if (compare(PreOpenInterest.getValue(),pOriginal->PreOpenInterest.getValue())!=0)
	{
		pOriginal->PreOpenInterest.getString(bufOriginal);
		fprintf(fp,"\t\tPreOpenInterest = %s -> %s    [昨持仓量]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPreOpenInterest = %s    [昨持仓量]\n",buf);
	}
	PreSettlementPrice.getString(buf);
	if (compare(PreSettlementPrice.getValue(),pOriginal->PreSettlementPrice.getValue())!=0)
	{
		pOriginal->PreSettlementPrice.getString(bufOriginal);
		fprintf(fp,"\t\tPreSettlementPrice = %s -> %s    [昨结算]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tPreSettlementPrice = %s    [昨结算]\n",buf);
	}
	SettlementPrice.getString(buf);
	if (compare(SettlementPrice.getValue(),pOriginal->SettlementPrice.getValue())!=0)
	{
		pOriginal->SettlementPrice.getString(bufOriginal);
		fprintf(fp,"\t\tSettlementPrice = %s -> %s    [今结算]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSettlementPrice = %s    [今结算]\n",buf);
	}
	UpdateMillisec.getString(buf);
	if (compare(UpdateMillisec.getValue(),pOriginal->UpdateMillisec.getValue())!=0)
	{
		pOriginal->UpdateMillisec.getString(bufOriginal);
		fprintf(fp,"\t\tUpdateMillisec = %s -> %s    [最后修改毫秒]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUpdateMillisec = %s    [最后修改毫秒]\n",buf);
	}
	UpdateTime.getString(buf);
	if (compare(UpdateTime.getValue(),pOriginal->UpdateTime.getValue())!=0)
	{
		pOriginal->UpdateTime.getString(bufOriginal);
		fprintf(fp,"\t\tUpdateTime = %s -> %s    [最后修改时间]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUpdateTime = %s    [最后修改时间]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableMarketData::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	TradingDay.getString(buf);
	fprintf(fp,",TradingDay,%s",buf);	
	ExchangeID.getString(buf);
	fprintf(fp,",ExchangeID,%s",buf);	
	InstrumentID.getString(buf);
	fprintf(fp,",InstrumentID,%s",buf);	
	OpenPrice.getString(buf);
	fprintf(fp,",OpenPrice,%s",buf);	
	HighestPrice.getString(buf);
	fprintf(fp,",HighestPrice,%s",buf);	
	LowestPrice.getString(buf);
	fprintf(fp,",LowestPrice,%s",buf);	
	LastPrice.getString(buf);
	fprintf(fp,",LastPrice,%s",buf);	
	Volume.getString(buf);
	fprintf(fp,",Volume,%s",buf);	
	Turnover.getString(buf);
	fprintf(fp,",Turnover,%s",buf);	
	LowerLimitPrice.getString(buf);
	fprintf(fp,",LowerLimitPrice,%s",buf);	
	UpperLimitPrice.getString(buf);
	fprintf(fp,",UpperLimitPrice,%s",buf);	
	OpenInterest.getString(buf);
	fprintf(fp,",OpenInterest,%s",buf);	
	PreClosePrice.getString(buf);
	fprintf(fp,",PreClosePrice,%s",buf);	
	PreOpenInterest.getString(buf);
	fprintf(fp,",PreOpenInterest,%s",buf);	
	PreSettlementPrice.getString(buf);
	fprintf(fp,",PreSettlementPrice,%s",buf);	
	SettlementPrice.getString(buf);
	fprintf(fp,",SettlementPrice,%s",buf);	
	UpdateMillisec.getString(buf);
	fprintf(fp,",UpdateMillisec,%s",buf);	
	UpdateTime.getString(buf);
	fprintf(fp,",UpdateTime,%s",buf);	
}

void CWriteableMarketData::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	TradingDay.getString(buf);
	sprintf(p,"TradingDay=%s,",buf);
	p+=strlen(p);
	ExchangeID.getString(buf);
	sprintf(p,"ExchangeID=%s,",buf);
	p+=strlen(p);
	InstrumentID.getString(buf);
	sprintf(p,"InstrumentID=%s,",buf);
	p+=strlen(p);
	OpenPrice.getString(buf);
	sprintf(p,"OpenPrice=%s,",buf);
	p+=strlen(p);
	HighestPrice.getString(buf);
	sprintf(p,"HighestPrice=%s,",buf);
	p+=strlen(p);
	LowestPrice.getString(buf);
	sprintf(p,"LowestPrice=%s,",buf);
	p+=strlen(p);
	LastPrice.getString(buf);
	sprintf(p,"LastPrice=%s,",buf);
	p+=strlen(p);
	Volume.getString(buf);
	sprintf(p,"Volume=%s,",buf);
	p+=strlen(p);
	Turnover.getString(buf);
	sprintf(p,"Turnover=%s,",buf);
	p+=strlen(p);
	LowerLimitPrice.getString(buf);
	sprintf(p,"LowerLimitPrice=%s,",buf);
	p+=strlen(p);
	UpperLimitPrice.getString(buf);
	sprintf(p,"UpperLimitPrice=%s,",buf);
	p+=strlen(p);
	OpenInterest.getString(buf);
	sprintf(p,"OpenInterest=%s,",buf);
	p+=strlen(p);
	PreClosePrice.getString(buf);
	sprintf(p,"PreClosePrice=%s,",buf);
	p+=strlen(p);
	PreOpenInterest.getString(buf);
	sprintf(p,"PreOpenInterest=%s,",buf);
	p+=strlen(p);
	PreSettlementPrice.getString(buf);
	sprintf(p,"PreSettlementPrice=%s,",buf);
	p+=strlen(p);
	SettlementPrice.getString(buf);
	sprintf(p,"SettlementPrice=%s,",buf);
	p+=strlen(p);
	UpdateMillisec.getString(buf);
	sprintf(p,"UpdateMillisec=%s,",buf);
	p+=strlen(p);
	UpdateTime.getString(buf);
	sprintf(p,"UpdateTime=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableMarketData::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CMarketData");
	pLogger->output(indent,0,"{");
	TradingDay.getString(buf);
	pLogger->output(indent+1,0,"TradingDay=%s 交易日",buf);
	ExchangeID.getString(buf);
	pLogger->output(indent+1,0,"ExchangeID=%s 交易所代码",buf);
	InstrumentID.getString(buf);
	pLogger->output(indent+1,0,"InstrumentID=%s 合约代码",buf);
	OpenPrice.getString(buf);
	pLogger->output(indent+1,0,"OpenPrice=%s 今开盘",buf);
	HighestPrice.getString(buf);
	pLogger->output(indent+1,0,"HighestPrice=%s 最高价",buf);
	LowestPrice.getString(buf);
	pLogger->output(indent+1,0,"LowestPrice=%s 最低价",buf);
	LastPrice.getString(buf);
	pLogger->output(indent+1,0,"LastPrice=%s 最新价",buf);
	Volume.getString(buf);
	pLogger->output(indent+1,0,"Volume=%s 数量",buf);
	Turnover.getString(buf);
	pLogger->output(indent+1,0,"Turnover=%s 成交金额",buf);
	LowerLimitPrice.getString(buf);
	pLogger->output(indent+1,0,"LowerLimitPrice=%s 跌停板价",buf);
	UpperLimitPrice.getString(buf);
	pLogger->output(indent+1,0,"UpperLimitPrice=%s 涨停板价",buf);
	OpenInterest.getString(buf);
	pLogger->output(indent+1,0,"OpenInterest=%s 持仓量",buf);
	PreClosePrice.getString(buf);
	pLogger->output(indent+1,0,"PreClosePrice=%s 昨收盘",buf);
	PreOpenInterest.getString(buf);
	pLogger->output(indent+1,0,"PreOpenInterest=%s 昨持仓量",buf);
	PreSettlementPrice.getString(buf);
	pLogger->output(indent+1,0,"PreSettlementPrice=%s 昨结算",buf);
	SettlementPrice.getString(buf);
	pLogger->output(indent+1,0,"SettlementPrice=%s 今结算",buf);
	UpdateMillisec.getString(buf);
	pLogger->output(indent+1,0,"UpdateMillisec=%s 最后修改毫秒",buf);
	UpdateTime.getString(buf);
	pLogger->output(indent+1,0,"UpdateTime=%s 最后修改时间",buf);
	pLogger->output(indent,0,"}");
}

CMarketDataIterator::~CMarketDataIterator(void)
{
}


void CMarketDataIterator::dump(FILE *output)
{
	CMarketData *pMarketData;
	
	while ((pMarketData=next())!=NULL)
	{
		pMarketData->dump(output);
	}
}



void CWriteableOrderDelay::writeCSVHead(FILE *output)
{
	fprintf(output,"BrokerID,UserID,UserOrderLocalID,FrontID,SessionID,RequestID,FTdRecvDown,CoreRecvDown,CoreSendUp,CoreRecvUp,CoreSendDown\n");
}
	
void CWriteableOrderDelay::init(void)
{
	BrokerID.clear();
	UserID.clear();
	UserOrderLocalID.clear();
	FrontID.clear();
	SessionID.clear();
	RequestID.clear();
	FTdRecvDown.clear();
	CoreRecvDown.clear();
	CoreSendUp.clear();
	CoreRecvUp.clear();
	CoreSendDown.clear();
}

int CWriteableOrderDelay::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableOrderDelay),input)!=sizeof(CWriteableOrderDelay))
		return 0;
	else
		return 1;
}
	
int CWriteableOrderDelay::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			BrokerID=token;
		}
		else
		{
			BrokerID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserID=token;
		}
		else
		{
			UserID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			UserOrderLocalID=token;
		}
		else
		{
			UserOrderLocalID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FrontID=token;
		}
		else
		{
			FrontID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SessionID=token;
		}
		else
		{
			SessionID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			RequestID=token;
		}
		else
		{
			RequestID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			FTdRecvDown=token;
		}
		else
		{
			FTdRecvDown="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreRecvDown=token;
		}
		else
		{
			CoreRecvDown="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreSendUp=token;
		}
		else
		{
			CoreSendUp="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreRecvUp=token;
		}
		else
		{
			CoreRecvUp="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			CoreSendDown=token;
		}
		else
		{
			CoreSendDown="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"BrokerID"))
			{
				BrokerID=token;
			}
			else if (!strcmp(fieldName,"UserID"))
			{
				UserID=token;
			}
			else if (!strcmp(fieldName,"UserOrderLocalID"))
			{
				UserOrderLocalID=token;
			}
			else if (!strcmp(fieldName,"FrontID"))
			{
				FrontID=token;
			}
			else if (!strcmp(fieldName,"SessionID"))
			{
				SessionID=token;
			}
			else if (!strcmp(fieldName,"RequestID"))
			{
				RequestID=token;
			}
			else if (!strcmp(fieldName,"FTdRecvDown"))
			{
				FTdRecvDown=token;
			}
			else if (!strcmp(fieldName,"CoreRecvDown"))
			{
				CoreRecvDown=token;
			}
			else if (!strcmp(fieldName,"CoreSendUp"))
			{
				CoreSendUp=token;
			}
			else if (!strcmp(fieldName,"CoreRecvUp"))
			{
				CoreRecvUp=token;
			}
			else if (!strcmp(fieldName,"CoreSendDown"))
			{
				CoreSendDown=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableOrderDelay::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableOrderDelay),output)!=sizeof(CWriteableOrderDelay))
		return 0;
	else
		return 1;
}

int CWriteableOrderDelay::writeCSV(FILE *output) const
{
	char buffer[1025];
	BrokerID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	UserOrderLocalID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FrontID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SessionID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	RequestID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	FTdRecvDown.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreRecvDown.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreSendUp.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreRecvUp.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	CoreSendDown.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableOrderDelay::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCOrderDelay%s = {\n", index_buf);
	BrokerID.getString(buf);
	fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);	
	UserID.getString(buf);
	fprintf(fp,"\t\tUserID = %s    [用户代码]\n",buf);	
	UserOrderLocalID.getString(buf);
	fprintf(fp,"\t\tUserOrderLocalID = %s    [用户本地报单号]\n",buf);	
	FrontID.getString(buf);
	fprintf(fp,"\t\tFrontID = %s    [前置编号]\n",buf);	
	SessionID.getString(buf);
	fprintf(fp,"\t\tSessionID = %s    [会话编号]\n",buf);	
	RequestID.getString(buf);
	fprintf(fp,"\t\tRequestID = %s    [请求编号]\n",buf);	
	FTdRecvDown.getString(buf);
	fprintf(fp,"\t\tFTdRecvDown = %s    [Ftdengine接受下层时间戳]\n",buf);	
	CoreRecvDown.getString(buf);
	fprintf(fp,"\t\tCoreRecvDown = %s    [接受下层时间戳]\n",buf);	
	CoreSendUp.getString(buf);
	fprintf(fp,"\t\tCoreSendUp = %s    [发送上层时间戳]\n",buf);	
	CoreRecvUp.getString(buf);
	fprintf(fp,"\t\tCoreRecvUp = %s    [接受上层时间戳]\n",buf);	
	CoreSendDown.getString(buf);
	fprintf(fp,"\t\tCoreSendDown = %s    [发送下层时间戳]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableOrderDelay::dumpDiff(FILE *fp, const CWriteableOrderDelay *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCOrderDelay = {\n");
	BrokerID.getString(buf);
	if (compare(BrokerID.getValue(),pOriginal->BrokerID.getValue())!=0)
	{
		pOriginal->BrokerID.getString(bufOriginal);
		fprintf(fp,"\t\tBrokerID = %s -> %s    [经纪公司编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tBrokerID = %s    [经纪公司编号]\n",buf);
	}
	UserID.getString(buf);
	if (compare(UserID.getValue(),pOriginal->UserID.getValue())!=0)
	{
		pOriginal->UserID.getString(bufOriginal);
		fprintf(fp,"\t\tUserID = %s -> %s    [用户代码]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserID = %s    [用户代码]\n",buf);
	}
	UserOrderLocalID.getString(buf);
	if (compare(UserOrderLocalID.getValue(),pOriginal->UserOrderLocalID.getValue())!=0)
	{
		pOriginal->UserOrderLocalID.getString(bufOriginal);
		fprintf(fp,"\t\tUserOrderLocalID = %s -> %s    [用户本地报单号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tUserOrderLocalID = %s    [用户本地报单号]\n",buf);
	}
	FrontID.getString(buf);
	if (compare(FrontID.getValue(),pOriginal->FrontID.getValue())!=0)
	{
		pOriginal->FrontID.getString(bufOriginal);
		fprintf(fp,"\t\tFrontID = %s -> %s    [前置编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFrontID = %s    [前置编号]\n",buf);
	}
	SessionID.getString(buf);
	if (compare(SessionID.getValue(),pOriginal->SessionID.getValue())!=0)
	{
		pOriginal->SessionID.getString(bufOriginal);
		fprintf(fp,"\t\tSessionID = %s -> %s    [会话编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSessionID = %s    [会话编号]\n",buf);
	}
	RequestID.getString(buf);
	if (compare(RequestID.getValue(),pOriginal->RequestID.getValue())!=0)
	{
		pOriginal->RequestID.getString(bufOriginal);
		fprintf(fp,"\t\tRequestID = %s -> %s    [请求编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tRequestID = %s    [请求编号]\n",buf);
	}
	FTdRecvDown.getString(buf);
	if (compare(FTdRecvDown.getValue(),pOriginal->FTdRecvDown.getValue())!=0)
	{
		pOriginal->FTdRecvDown.getString(bufOriginal);
		fprintf(fp,"\t\tFTdRecvDown = %s -> %s    [Ftdengine接受下层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tFTdRecvDown = %s    [Ftdengine接受下层时间戳]\n",buf);
	}
	CoreRecvDown.getString(buf);
	if (compare(CoreRecvDown.getValue(),pOriginal->CoreRecvDown.getValue())!=0)
	{
		pOriginal->CoreRecvDown.getString(bufOriginal);
		fprintf(fp,"\t\tCoreRecvDown = %s -> %s    [接受下层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreRecvDown = %s    [接受下层时间戳]\n",buf);
	}
	CoreSendUp.getString(buf);
	if (compare(CoreSendUp.getValue(),pOriginal->CoreSendUp.getValue())!=0)
	{
		pOriginal->CoreSendUp.getString(bufOriginal);
		fprintf(fp,"\t\tCoreSendUp = %s -> %s    [发送上层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreSendUp = %s    [发送上层时间戳]\n",buf);
	}
	CoreRecvUp.getString(buf);
	if (compare(CoreRecvUp.getValue(),pOriginal->CoreRecvUp.getValue())!=0)
	{
		pOriginal->CoreRecvUp.getString(bufOriginal);
		fprintf(fp,"\t\tCoreRecvUp = %s -> %s    [接受上层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreRecvUp = %s    [接受上层时间戳]\n",buf);
	}
	CoreSendDown.getString(buf);
	if (compare(CoreSendDown.getValue(),pOriginal->CoreSendDown.getValue())!=0)
	{
		pOriginal->CoreSendDown.getString(bufOriginal);
		fprintf(fp,"\t\tCoreSendDown = %s -> %s    [发送下层时间戳]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tCoreSendDown = %s    [发送下层时间戳]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableOrderDelay::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	BrokerID.getString(buf);
	fprintf(fp,",BrokerID,%s",buf);	
	UserID.getString(buf);
	fprintf(fp,",UserID,%s",buf);	
	UserOrderLocalID.getString(buf);
	fprintf(fp,",UserOrderLocalID,%s",buf);	
	FrontID.getString(buf);
	fprintf(fp,",FrontID,%s",buf);	
	SessionID.getString(buf);
	fprintf(fp,",SessionID,%s",buf);	
	RequestID.getString(buf);
	fprintf(fp,",RequestID,%s",buf);	
	FTdRecvDown.getString(buf);
	fprintf(fp,",FTdRecvDown,%s",buf);	
	CoreRecvDown.getString(buf);
	fprintf(fp,",CoreRecvDown,%s",buf);	
	CoreSendUp.getString(buf);
	fprintf(fp,",CoreSendUp,%s",buf);	
	CoreRecvUp.getString(buf);
	fprintf(fp,",CoreRecvUp,%s",buf);	
	CoreSendDown.getString(buf);
	fprintf(fp,",CoreSendDown,%s",buf);	
}

void CWriteableOrderDelay::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	BrokerID.getString(buf);
	sprintf(p,"BrokerID=%s,",buf);
	p+=strlen(p);
	UserID.getString(buf);
	sprintf(p,"UserID=%s,",buf);
	p+=strlen(p);
	UserOrderLocalID.getString(buf);
	sprintf(p,"UserOrderLocalID=%s,",buf);
	p+=strlen(p);
	FrontID.getString(buf);
	sprintf(p,"FrontID=%s,",buf);
	p+=strlen(p);
	SessionID.getString(buf);
	sprintf(p,"SessionID=%s,",buf);
	p+=strlen(p);
	RequestID.getString(buf);
	sprintf(p,"RequestID=%s,",buf);
	p+=strlen(p);
	FTdRecvDown.getString(buf);
	sprintf(p,"FTdRecvDown=%s,",buf);
	p+=strlen(p);
	CoreRecvDown.getString(buf);
	sprintf(p,"CoreRecvDown=%s,",buf);
	p+=strlen(p);
	CoreSendUp.getString(buf);
	sprintf(p,"CoreSendUp=%s,",buf);
	p+=strlen(p);
	CoreRecvUp.getString(buf);
	sprintf(p,"CoreRecvUp=%s,",buf);
	p+=strlen(p);
	CoreSendDown.getString(buf);
	sprintf(p,"CoreSendDown=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableOrderDelay::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"COrderDelay");
	pLogger->output(indent,0,"{");
	BrokerID.getString(buf);
	pLogger->output(indent+1,0,"BrokerID=%s 经纪公司编号",buf);
	UserID.getString(buf);
	pLogger->output(indent+1,0,"UserID=%s 用户代码",buf);
	UserOrderLocalID.getString(buf);
	pLogger->output(indent+1,0,"UserOrderLocalID=%s 用户本地报单号",buf);
	FrontID.getString(buf);
	pLogger->output(indent+1,0,"FrontID=%s 前置编号",buf);
	SessionID.getString(buf);
	pLogger->output(indent+1,0,"SessionID=%s 会话编号",buf);
	RequestID.getString(buf);
	pLogger->output(indent+1,0,"RequestID=%s 请求编号",buf);
	FTdRecvDown.getString(buf);
	pLogger->output(indent+1,0,"FTdRecvDown=%s Ftdengine接受下层时间戳",buf);
	CoreRecvDown.getString(buf);
	pLogger->output(indent+1,0,"CoreRecvDown=%s 接受下层时间戳",buf);
	CoreSendUp.getString(buf);
	pLogger->output(indent+1,0,"CoreSendUp=%s 发送上层时间戳",buf);
	CoreRecvUp.getString(buf);
	pLogger->output(indent+1,0,"CoreRecvUp=%s 接受上层时间戳",buf);
	CoreSendDown.getString(buf);
	pLogger->output(indent+1,0,"CoreSendDown=%s 发送下层时间戳",buf);
	pLogger->output(indent,0,"}");
}

COrderDelayIterator::~COrderDelayIterator(void)
{
}


void COrderDelayIterator::dump(FILE *output)
{
	COrderDelay *pOrderDelay;
	
	while ((pOrderDelay=next())!=NULL)
	{
		pOrderDelay->dump(output);
	}
}



void CWriteableSystemInfo::writeCSVHead(FILE *output)
{
	fprintf(output,"SystemID,SystemName,SystemIP\n");
}
	
void CWriteableSystemInfo::init(void)
{
	SystemID.clear();
	SystemName.clear();
	SystemIP.clear();
}

int CWriteableSystemInfo::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteableSystemInfo),input)!=sizeof(CWriteableSystemInfo))
		return 0;
	else
		return 1;
}
	
int CWriteableSystemInfo::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		token=getNextToken(buffer);
		if (token!=NULL)
		{
			SystemID=token;
		}
		else
		{
			SystemID="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SystemName=token;
		}
		else
		{
			SystemName="";
		}
		token=getNextToken(NULL);
		if (token!=NULL)
		{
			SystemIP=token;
		}
		else
		{
			SystemIP="";
		}
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			if (!strcmp(fieldName,"SystemID"))
			{
				SystemID=token;
			}
			else if (!strcmp(fieldName,"SystemName"))
			{
				SystemName=token;
			}
			else if (!strcmp(fieldName,"SystemIP"))
			{
				SystemIP=token;
			}
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteableSystemInfo::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteableSystemInfo),output)!=sizeof(CWriteableSystemInfo))
		return 0;
	else
		return 1;
}

int CWriteableSystemInfo::writeCSV(FILE *output) const
{
	char buffer[1025];
	SystemID.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SystemName.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,",");
	SystemIP.getString(buffer);
	fprintf(output,"%s",buffer);
	fprintf(output,"\n");
	return 1;
}
void CWriteableSystemInfo::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tCSystemInfo%s = {\n", index_buf);
	SystemID.getString(buf);
	fprintf(fp,"\t\tSystemID = %s    [QDP系统编号]\n",buf);	
	SystemName.getString(buf);
	fprintf(fp,"\t\tSystemName = %s    [QDP系统名称]\n",buf);	
	SystemIP.getString(buf);
	fprintf(fp,"\t\tSystemIP = %s    [QDP系统IP地址]\n",buf);	
	fprintf(fp,"\t}\n");
}

void CWriteableSystemInfo::dumpDiff(FILE *fp, const CWriteableSystemInfo *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tCSystemInfo = {\n");
	SystemID.getString(buf);
	if (compare(SystemID.getValue(),pOriginal->SystemID.getValue())!=0)
	{
		pOriginal->SystemID.getString(bufOriginal);
		fprintf(fp,"\t\tSystemID = %s -> %s    [QDP系统编号]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSystemID = %s    [QDP系统编号]\n",buf);
	}
	SystemName.getString(buf);
	if (compare(SystemName.getValue(),pOriginal->SystemName.getValue())!=0)
	{
		pOriginal->SystemName.getString(bufOriginal);
		fprintf(fp,"\t\tSystemName = %s -> %s    [QDP系统名称]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSystemName = %s    [QDP系统名称]\n",buf);
	}
	SystemIP.getString(buf);
	if (compare(SystemIP.getValue(),pOriginal->SystemIP.getValue())!=0)
	{
		pOriginal->SystemIP.getString(bufOriginal);
		fprintf(fp,"\t\tSystemIP = %s -> %s    [QDP系统IP地址]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\tSystemIP = %s    [QDP系统IP地址]\n",buf);
	}
	fprintf(fp,"\t}\n");
}

void CWriteableSystemInfo::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	SystemID.getString(buf);
	fprintf(fp,",SystemID,%s",buf);	
	SystemName.getString(buf);
	fprintf(fp,",SystemName,%s",buf);	
	SystemIP.getString(buf);
	fprintf(fp,",SystemIP,%s",buf);	
}

void CWriteableSystemInfo::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	SystemID.getString(buf);
	sprintf(p,"SystemID=%s,",buf);
	p+=strlen(p);
	SystemName.getString(buf);
	sprintf(p,"SystemName=%s,",buf);
	p+=strlen(p);
	SystemIP.getString(buf);
	sprintf(p,"SystemIP=%s,",buf);
	p+=strlen(p);
	p--;
	*p='\0';
}

void CWriteableSystemInfo::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"CSystemInfo");
	pLogger->output(indent,0,"{");
	SystemID.getString(buf);
	pLogger->output(indent+1,0,"SystemID=%s QDP系统编号",buf);
	SystemName.getString(buf);
	pLogger->output(indent+1,0,"SystemName=%s QDP系统名称",buf);
	SystemIP.getString(buf);
	pLogger->output(indent+1,0,"SystemIP=%s QDP系统IP地址",buf);
	pLogger->output(indent,0,"}");
}

CSystemInfoIterator::~CSystemInfoIterator(void)
{
}


void CSystemInfoIterator::dump(FILE *output)
{
	CSystemInfo *pSystemInfo;
	
	while ((pSystemInfo=next())!=NULL)
	{
		pSystemInfo->dump(output);
	}
}


