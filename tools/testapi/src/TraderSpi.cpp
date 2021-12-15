// TraderSpi.cpp: implementation of the CTraderSpi class.
//
//////////////////////////////////////////////////////////////////////

#include "TraderSpi.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


extern FILE * g_fpRecv;

CTraderSpi::CTraderSpi(CQdpFtdcUserApi *pTrader):m_pUserApi(pTrader)
{

}

CTraderSpi::~CTraderSpi()
{

}


void CTraderSpi::OnFrontConnected()
{
	CQdpFtdcReqUserLoginField reqUserLogin;
	memset(&reqUserLogin,0,sizeof(CQdpFtdcReqUserLoginField));	
	strcpy(reqUserLogin.BrokerID, g_BrokerID);
	strcpy(reqUserLogin.UserID, g_UserID);
	strcpy(reqUserLogin.Password, g_Password);	
	strcpy(reqUserLogin.UserProductInfo,g_pProductInfo);		
	m_pUserApi->ReqUserLogin(&reqUserLogin, g_nOrdLocalID);	
	REPORT_EVENT(LOG_INFO, "ReqUltraSpeedUserLogin","BrokerID:%s,UserID:%s",g_BrokerID,g_UserID);
	
	printf("请求登录，席位:%s\n",g_UserID);
	//printf("Start Insert Order\n");
#ifdef WIN32
	Sleep(1000);
#else
	usleep(1000);
#endif
	//StartAutoOrder();
}


void CTraderSpi::OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("登录失败...\n");
		return;
	}
	g_nOrdLocalID=atoi(pRspUserLogin->MaxOrderLocalID)+1;
 	REPORT_EVENT(LOG_INFO, "LoginSuccess", "MaxLocalID = %d", g_nOrdLocalID);
 	
 	printf("登录成功，最大本地报单号:%d\n",g_nOrdLocalID);
	printf("开始报单...\n");
 	
 	StartAutoOrder();
}

void CTraderSpi::OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//printf("Recv RspOrderInsert\n");
	#ifdef PERFORM_TEST
				long ltm;
				GET_ACCURATE_USEC_TIME(ltm);
				printf("rsporder,%ld \n",ltm);	
	#endif
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		REPORT_EVENT(LOG_CRITICAL,"OnRspOrderInsert","error,id:%d,msg:%s",pRspInfo->ErrorID,pRspInfo->ErrorMsg);
		return;
	}
	
	if(pInputOrder!=NULL)
	{
		DWORD dwLocalID = atoi(pInputOrder->UserOrderLocalID);
/*
		timeval tvnow;
		gettimeofday(&tvnow,0);


		char buf[256];
		memset(buf,0,256);

		fprintf(g_fpRecv,"%d,%ld\n",dwLocalID,tvnow.tv_sec*1000000+tvnow.tv_usec);

		fflush(g_fpRecv);
*/

		if(g_mpOrdSndTm!=NULL)
		{
#ifdef WIN32
			map<DWORD,_timeb*> ::iterator it=g_mpOrdSndTm->find(dwLocalID);
#else
			map<DWORD,timeval*>::iterator it=g_mpOrdSndTm->find(dwLocalID);
#endif
			//找到了报单信息
			if(it!=g_mpOrdSndTm->end())
			{
/*				timeval tvnow;
				gettimeofday(&tvnow,0);
				timeval* ptv = it->second;
				if(ptv!=NULL)
				{
					int nRspTm = ((tvnow.tv_sec-ptv->tv_sec)*1000000+(tvnow.tv_usec-ptv->tv_usec));
					if(g_mpOrdLoopTm!=NULL)
					{
						g_mpOrdLoopTm->insert(pair<DWORD,int>(dwLocalID,nRspTm));
					}	
					delete ptv;
					ptv=NULL;
				}
*/
				g_mux.Lock();
				g_mpOrdSndTm->erase(it->first);
				g_mux.UnLock();
			}
		}
		
		//dump响应时间
		if(g_mpOrdLoopTm->size()>=10)
		{
			map<DWORD,int>::iterator it=g_mpOrdLoopTm->begin();
				for(;it!=g_mpOrdLoopTm->end();it++)
				{
					fprintf(g_fpRspTm,"%d,%d\n",it->first,it->second);
					printf("LocalID=[%d]Time=[%d]\n",it->first,it->second);
				}
				fflush(g_fpRspTm);
				g_mpOrdLoopTm->clear();
		}	
	}
	
}

int g_rtnTrdCount = 0;
int nshow=2000;

void CTraderSpi::OnRtnTrade(CQdpFtdcTradeField *pTrade)
{
	g_rtnTrdCount++;
	if(g_rtnTrdCount%nshow==0)
	{
		printf("rtn trade %d\n",g_rtnTrdCount);
	}
// 	REPORT_EVENT(LOG_DEBUG,"Hint","OnRtnTrade");
}

int g_rtnOrdCount = 0;
void CTraderSpi::OnRtnOrder(CQdpFtdcOrderField *pOrder)
{
	g_rtnOrdCount++;
	if(g_rtnOrdCount%nshow==0)
	{
		printf("rtn ord %d\n",g_rtnOrdCount);
	}
// 	REPORT_EVENT(LOG_DEBUG,"Hint","OnRtnOrder");
}

