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
// 		return "����ǰ";
// 	case QDP_FTDC_IS_NoTrading:	
// 		return "�ǽ���";	
// 	case QDP_FTDC_IS_Continous:	
// 		return "��������";
// 	case QDP_FTDC_IS_AuctionOrdering:		
// 		return "���Ͼ��۱���";
// 	case QDP_FTDC_IS_AuctionBalance:	
// 		return "���Ͼ���ƽ��";	
// 	case QDP_FTDC_IS_AuctionMatch:	
// 		return "���Ͼ��۴��";
// 	case QDP_FTDC_IS_Closed:	
// 		return "����";
// 	default:		
// 		break;
// 	}
// 	return "δ֪";
// }
// 
// const char *GetAdminOrder(char chUserType)
// {
// 	switch(chUserType) 
// 	{
// 	case '2':		
// 		return "��ʼ��";
// 	case '3':	
// 		return "����";
// 	case '4':
// 		return "ȡ��";
// 	default:		
// 		break;
// 	}
// 	return "δ֪";
// }
// 
// const char *GetOpFlag(char chUserType)
// {
// 	switch(chUserType)
// 	{
// 	case '1':		
// 		return "����";
// 	case '2':	
// 		return "�޸�";
// 	case '3':
// 		return "ɾ��";
// 	default:		
// 		break;
// 	}
// 	return "δ֪";
// }
// 
// const char *GetEnterReason(char chUserType)
// {
// 	switch(chUserType) 
// 	{
// 	case '1':		
// 		return "�Զ�";
// 	case '2':	
// 		return "�ֶ�";
// 	case '3':
// 		return "����";
// 	case '4':
// 		return "�۶�";
// 	default:		
// 		break;
// 	}
// 	return "δ֪";
// }
// 
// const char *GetBsFlag(char chUserType)
// {
// 	switch(chUserType)
// 	{
// 	case '0':		
// 		return "����";
// 	case '1':	
// 		return "����";
// 	default:		
// 		break;
// 	}
// 	return "δ֪";
// }
// 
// const char *GetHedgeFlag(char chUserType)
// {
// 	switch(chUserType) 
// 	{
// 	case QDP_FTDC_CHF_Speculation:		
// 		return "Ͷ��";
// 	case QDP_FTDC_CHF_Hedge:	
// 		return "�ױ�";	
// 	default:		
// 		break;
// 	}
// 	return "δ֪";
// }
// 
// const char *GetPosiDirection(char chUserType)
// {
// 	switch(chUserType)
// 	{
// 	case QDP_FTDC_D_Buy:	
// 		return "��ͷ";	
// 	case QDP_FTDC_D_Sell:	
// 		return "��ͷ";	
// 	default:		
// 		break;
// 	}
// 	return "δ֪";
// }
// 
// const char *GetBsflag(char chUserType)
// {
// 	switch(chUserType) 
// 	{
// 	case QDP_FTDC_D_Buy:		
// 		return "��";
// 	case QDP_FTDC_D_Sell:	
// 		return "��";
// 	default:		
// 		break;
// 	}
// 	return "δ֪";
// }
// 
// const char *GetOffsetFlag(char chUserType)
// {
// 	switch(chUserType) 
// 	{
// 	case QDP_FTDC_OF_Open:		
// 		return "����";
// 	case QDP_FTDC_OF_Close:	
// 		return "ƽ��";
// 	case QDP_FTDC_OF_ForceClose:		
// 		return "ǿƽ";
// 	case QDP_FTDC_OF_CloseToday:	
// 		return "ƽ��";
// 	case QDP_FTDC_OF_CloseYesterday:		
// 		return "ƽ��";
// 	default:		
// 		break;
// 	}
// 	return "δ֪";
// }
// 
// const char *GetOrderStatus(char chUserType)
// {
// 	switch(chUserType) 
// 	{
// 	case QDP_FTDC_OS_AllTraded:		
// 		return "ȫ���ɽ�";
// 	case QDP_FTDC_OS_PartTradedQueueing:	
// 		return "���ֳɽ����ڶ�����";	
// 	case QDP_FTDC_OS_PartTradedNotQueueing:	
// 		return "���ֳɽ����ڶ�����";
// 	case QDP_FTDC_OS_NoTradeQueueing:		
// 		return "δ�ɽ����ڶ�����";
// 	case QDP_FTDC_OS_NoTradeNotQueueing:	
// 		return "δ�ɽ����ڶ�����";	
// 	case QDP_FTDC_OS_Canceled:	
// 		return "����";
// 	default:		
// 		break;
// 	}
// 	return "δ֪";
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
			// ����ȫ�ֺ��滻
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
	
	// ��һ����¼��Ӧ����judge ָ��
	if(iLast < 1) return true;

	//	�ϱʼ�¼��Replyֵ
	if(strcmp(sInputCmd->ReqField.BrokerID,"LASTREPLY") == 0)
		dLastValue = sInputCmdArray[iLast-1].dCurMoney;

	//	�ϱʼ�¼��statusֵ
	if(strcmp(sInputCmd->ReqField.BrokerID,"LASTSTATUS") == 0)
		dLastValue = sInputCmdArray[iLast-1].pRspInfo.ErrorID;

	//	�ϱʼ�¼���ۼ�ѭ������
	if(strcmp(sInputCmd->ReqField.BrokerID,"LASTCYCLES") == 0)
		dLastValue = sInputCmdArray[iLast-1].iCycleTimes;

	ShowMsg(" %s [%.2f] %s  [%.2f],",
		sInputCmd->ReqField.BrokerID,
		dLastValue,
		sInputCmd->ReqField.InvestorID,
		sInputCmd->ReqField.LimitPrice
		);

	//	���ڵ��ж�
	if(strcmp(sInputCmd->ReqField.InvestorID,"GT") == 0)
	{
		if(dLastValue > sInputCmd->ReqField.LimitPrice)
			return true;
		else
			return false;
	}

	//	���ڵ��ڵ��ж�
	if(strcmp(sInputCmd->ReqField.InvestorID,"GTE") == 0)
	{
		if(dLastValue >= sInputCmd->ReqField.LimitPrice)
			return true;
		else
			return false;
	}

	//	С�ڵ��ж�
	if(strcmp(sInputCmd->ReqField.InvestorID,"LT") == 0)
	{
		if(dLastValue < sInputCmd->ReqField.LimitPrice)
			return true;
		else
			return false;
	}

	//	С�ڵ��ڵ��ж�
	if(strcmp(sInputCmd->ReqField.InvestorID,"LTE") == 0)
	{
		if(dLastValue < sInputCmd->ReqField.LimitPrice)
			return true;
		else
			return false;
	}

	//	���ڵ��ж�
	if(strcmp(sInputCmd->ReqField.InvestorID,"EQ") == 0)
	{
		if(dLastValue == sInputCmd->ReqField.LimitPrice)
			return true;
		else
			return false;
	}

	//	�����ڵ��ж�
	if(strcmp(sInputCmd->ReqField.InvestorID,"NEQ") == 0)
	{
		if(dLastValue != sInputCmd->ReqField.LimitPrice)
			return true;
		else
			return false;
	}

	return 0;
}