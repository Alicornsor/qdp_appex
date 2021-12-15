// TestApi.cpp : Defines the entry point for the console application.
//
#include "PublicFuncs.h"
#include "TraderSpi.h"

#include "CachedFlow.h"
#include "QdpFtdcTraderApi.h"
#include <iostream>

const int ERR_ARGUMENT = -1;
const int ERR_OPENFILE = -2;
const int PORT_ID_API=36000;
int g_nSwitch=0;

FILE * g_fpRecv=NULL;
FILE * g_fpSend=NULL;
extern int g_nOrdSpeed;

void usage(char* pName)
{
	printf("usage:%s [0/1/2/3]\n",pName);
	printf("\t0->�� Order.csv ��ȡԤ�趩������;\n\t1->[�۸�]=NaN;\n\t2->[�۸�]=INF;\n\t3->[�۸�]=3500.59999999999\n");
	printf("\t4->����rsptm�Ĺ���\n");
}

int main(int argc, char* argv[])
{
	if(argc==1)
	{
		usage(argv[0]);
		return ERR_ARGUMENT;
	}
	if(argc > 1)
		g_nSwitch = atoi(argv[1]);
	bool bread=readconfig();
	if (!bread)
	{
		REPORT_EVENT(LOG_CRITICAL,"read config","read config fail");
		return -1;
	}
	//�����洢��Ӧʱ���map
	g_mpOrdLoopTm=new map<DWORD,int>();

	//open file
	g_fpRspTm=fopen("rsptm.log","w");
	fprintf(g_fpRspTm,"�����ţ���Ӧ΢��\n");

	char flnm[256];
	sprintf(flnm,"send.csv",g_nOrdSpeed);

	CQdpFtdcUserApi *pTrader = CQdpFtdcUserApi::CreateFtdcUserApi(g_pFlowPath);	
	g_puserapi=pTrader;

 	CTraderSpi spi(pTrader);
 	pTrader->RegisterFront(g_frontaddr);	
	pTrader->SubscribePrivateTopic(QDP_TERT_RESTART);
	pTrader->SubscribePublicTopic(QDP_TERT_RESUME);
	pTrader->RegisterSpi(&spi);
	pTrader->Init(PORT_ID_API);

	pTrader->Join();
	pTrader->Release();


	return 0;
}
