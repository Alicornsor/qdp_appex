#include "TypeDefine.h"

extern bool bCmdLFlag;
extern ST_MARCO sMarcoArray[200];
extern int iMarcoCount;
extern int iTotalCmdNum;
extern ST_INPUT_CMD  *sInputCmdArray;
extern ST_INPUT_CMD  *sInputCmd;

// const char *GetInstrumentStatus(char chUserType)
// {
// 	switch(chUserType) 
// 	{
// 	case QDP_FTDC_IS_BeforeTrading:		
// 		return "开盘前";
// 	case QDP_FTDC_IS_NoTrading:	
// 		return "非交易";	
// 	case QDP_FTDC_IS_Continous:	
// 		return "连续交易";
// 	case QDP_FTDC_IS_AuctionOrdering:		
// 		return "集合竞价报单";
// 	case QDP_FTDC_IS_AuctionBalance:	
// 		return "集合竞价平衡";	
// 	case QDP_FTDC_IS_AuctionMatch:	
// 		return "集合竞价撮合";
// 	case QDP_FTDC_IS_Closed:	
// 		return "收盘";
// 	default:		
// 		break;
// 	}
// 	return "未知";
// }
// 
// const char *GetAdminOrder(char chUserType)
// {
// 	switch(chUserType) 
// 	{
// 	case '2':		
// 		return "初始化";
// 	case '3':	
// 		return "调整";
// 	case '4':
// 		return "取消";
// 	default:		
// 		break;
// 	}
// 	return "未知";
// }
// 
// const char *GetOpFlag(char chUserType)
// {
// 	switch(chUserType)
// 	{
// 	case '1':		
// 		return "增加";
// 	case '2':	
// 		return "修改";
// 	case '3':
// 		return "删除";
// 	default:		
// 		break;
// 	}
// 	return "未知";
// }
// 
// const char *GetEnterReason(char chUserType)
// {
// 	switch(chUserType) 
// 	{
// 	case '1':		
// 		return "自动";
// 	case '2':	
// 		return "手动";
// 	case '3':
// 		return "熔自";
// 	case '4':
// 		return "熔断";
// 	default:		
// 		break;
// 	}
// 	return "未知";
// }
// 
// const char *GetBsFlag(char chUserType)
// {
// 	switch(chUserType)
// 	{
// 	case '0':		
// 		return "买入";
// 	case '1':	
// 		return "卖出";
// 	default:		
// 		break;
// 	}
// 	return "未知";
// }
// 
// const char *GetHedgeFlag(char chUserType)
// {
// 	switch(chUserType) 
// 	{
// 	case QDP_FTDC_CHF_Speculation:		
// 		return "投机";
// 	case QDP_FTDC_CHF_Hedge:	
// 		return "套保";	
// 	default:		
// 		break;
// 	}
// 	return "未知";
// }
// 
// const char *GetPosiDirection(char chUserType)
// {
// 	switch(chUserType)
// 	{
// 	case QDP_FTDC_D_Buy:	
// 		return "多头";	
// 	case QDP_FTDC_D_Sell:	
// 		return "空头";	
// 	default:		
// 		break;
// 	}
// 	return "未知";
// }
// 
// const char *GetBsflag(char chUserType)
// {
// 	switch(chUserType) 
// 	{
// 	case QDP_FTDC_D_Buy:		
// 		return "买";
// 	case QDP_FTDC_D_Sell:	
// 		return "卖";
// 	default:		
// 		break;
// 	}
// 	return "未知";
// }
// 
// const char *GetOffsetFlag(char chUserType)
// {
// 	switch(chUserType) 
// 	{
// 	case QDP_FTDC_OF_Open:		
// 		return "开仓";
// 	case QDP_FTDC_OF_Close:	
// 		return "平仓";
// 	case QDP_FTDC_OF_ForceClose:		
// 		return "强平";
// 	case QDP_FTDC_OF_CloseToday:	
// 		return "平今";
// 	case QDP_FTDC_OF_CloseYesterday:		
// 		return "平昨";
// 	default:		
// 		break;
// 	}
// 	return "未知";
// }
// 
// const char *GetOrderStatus(char chUserType)
// {
// 	switch(chUserType) 
// 	{
// 	case QDP_FTDC_OS_AllTraded:		
// 		return "全部成交";
// 	case QDP_FTDC_OS_PartTradedQueueing:	
// 		return "部分成交还在队列中";	
// 	case QDP_FTDC_OS_PartTradedNotQueueing:	
// 		return "部分成交不在队列中";
// 	case QDP_FTDC_OS_NoTradeQueueing:		
// 		return "未成交还在队列中";
// 	case QDP_FTDC_OS_NoTradeNotQueueing:	
// 		return "未成交不在队列中";	
// 	case QDP_FTDC_OS_Canceled:	
// 		return "撤单";
// 	default:		
// 		break;
// 	}
// 	return "未知";
//}

void delFrontCh( char *p, char ch )
{
	int i, j;
	for ( i = 0; i < strlen( p ); i++ )
	{
		if ( p[ i ] == ch )
		{
			for ( j = i; j < strlen( p ) - 1; j++ )
			{
				p[ j ] = p [ j + 1 ];			
			}
			p[ strlen( p ) - 1 ] = '\0';
		}
		else
		{
			break;
		}
		i--;
	}
} 

void ShowMsg(const char *msg,...)
{
	if (!bCmdLFlag)
	{
		va_list msgargs;
		va_start (msgargs,msg);
		vfprintf(stdout, msg, msgargs);
		va_end (msgargs);
		fflush(stdout);
//		printf("[PROCESS]-->%d \n",pProcessor->m_nRequestID);
	}
}

void ReplaceMarcoStr(CQdpFtdcInputOrderField *sCmd)
{
	int		ilen,iCnt = 0;
	char	sTmp[40];
	char	*p;
	char	*ps;

	p = (char *)sCmd;
	ps = p;
	for(ilen = 0; ilen < sizeof(CQdpFtdcInputOrderField); ilen++)
	{
		sTmp[iCnt] = p[ilen];
		
		if(p[ilen] == 0)
		{
//			printf("[%s]",sTmp);
			// 进行全局宏替换
			for(int j=1;j<=iMarcoCount;j++)
			{
				if(strcmp(sTmp,sMarcoArray[j].sMarcoId)==0)
				{
					strcpy(ps,sMarcoArray[j].sMarcoValue);
				}
			}

			iCnt = 0;
			ps = &p[ilen]+1;
		}
	  else
			iCnt ++;
	}

	return;
}
	
void ReplaceSpChar(char *str, char ch_in, char ch_rp)
{
	char *pt = str;
	while (*pt != '\0')
	{
		if (*pt == ch_in)
		{
			*pt = ch_rp;
		}
		pt++;
	}
}

bool CheckCondition(int iLast)
{
	double dLastValue = 0;
	
	// 第一条记录不应该是judge 指令
	if(iLast < 1) return true;

	//	上笔记录的Reply值
	if(strcmp(sInputCmd->ReqField.BrokerID,"LASTREPLY") == 0)
		dLastValue = sInputCmdArray[iLast-1].dCurMoney;

	//	上笔记录的status值
	if(strcmp(sInputCmd->ReqField.BrokerID,"LASTSTATUS") == 0)
		dLastValue = sInputCmdArray[iLast-1].pRspInfo.ErrorID;

	//	上笔记录的累计循环次数
	if(strcmp(sInputCmd->ReqField.BrokerID,"LASTCYCLES") == 0)
		dLastValue = sInputCmdArray[iLast-1].iCycleTimes;

	ShowMsg(" %s [%.2f] %s  [%.2f],",
		sInputCmd->ReqField.BrokerID,
		dLastValue,
		sInputCmd->ReqField.InvestorID,
		sInputCmd->ReqField.LimitPrice
		);

	//	大于的判定
	if(strcmp(sInputCmd->ReqField.InvestorID,"GT") == 0)
	{
		if(dLastValue > sInputCmd->ReqField.LimitPrice)
			return true;
		else
			return false;
	}

	//	大于等于的判定
	if(strcmp(sInputCmd->ReqField.InvestorID,"GTE") == 0)
	{
		if(dLastValue >= sInputCmd->ReqField.LimitPrice)
			return true;
		else
			return false;
	}

	//	小于的判定
	if(strcmp(sInputCmd->ReqField.InvestorID,"LT") == 0)
	{
		if(dLastValue < sInputCmd->ReqField.LimitPrice)
			return true;
		else
			return false;
	}

	//	小于等于的判定
	if(strcmp(sInputCmd->ReqField.InvestorID,"LTE") == 0)
	{
		if(dLastValue < sInputCmd->ReqField.LimitPrice)
			return true;
		else
			return false;
	}

	//	等于的判定
	if(strcmp(sInputCmd->ReqField.InvestorID,"EQ") == 0)
	{
		if(dLastValue == sInputCmd->ReqField.LimitPrice)
			return true;
		else
			return false;
	}

	//	不等于的判定
	if(strcmp(sInputCmd->ReqField.InvestorID,"NEQ") == 0)
	{
		if(dLastValue != sInputCmd->ReqField.LimitPrice)
			return true;
		else
			return false;
	}

	return 0;
}