#include "ProcessCmd.h"
#include "Processor.h"
#include "utility.h"

extern CProcessor *pProcessor;

extern char  m_TradeIp[30];
extern char  m_DefaultUser[30];
extern char  m_DefaultPass[30];

extern int iProcessorCount;
extern int iWaitOrderPos;  // 在途委托总数 
extern int iTotalOrderCnt;  // 总委托总数 
extern bool bWaitActionFlag;
extern list<int>  orderActionList;
extern bool bFastFlag;
extern int iCurCmdPos;	// 当前提交的InputCmd 的 序号
extern ST_INPUT_CMD  *sInputCmdArray;
extern char m_ExternCmd[30];
extern UF_INT8    lReqTime;    //请求开始时间



enum choice	 
{
	NULLCMD,				//  此命令无法执行
	LOGIN,					//	登录
	ORDER,					//	委托
	CANCEL,					//	撤单
	CANCELALL,				//	撤全部委托
	SLEEP,					//	延时
	QRYMONEY,				//	资金查询
	RESETUSERPASS,			//	重置当前用户密码
	QRYORDER,				//	查询委托
	QRYTRADE,				//	成交查询
	QRYMARKET,				//	行情查询
	QRYCLIENTPOSI,			//	客户持仓查询
	QRYINSTRUMENT,			//	合约查询
	MONEYINOUT,				//	出入金
	BTRANSF,                //  银转期
	FTRANSB,                //  期转银
	QRYEXCHTIMEDIFF,        //  查询交易所时间偏差
	QRYBANK,                //  查询签约银行
	QRYBANKFUND,            //  查询银行余额
	QRYBFINTERFACE,         //  查询转账流水
	FORQUOTE,				//  询价
	QRYFORQUOTE,			//  询价查询
	EXECORDER,				//  行权
	EXECCANCEL,				//  行权撤单
	QRYEXECORDER,			//  行权报单查询
	EXTCMD,					//  外部指令调用
	LOGOUT
};

char *pCmdList[] = 
{
	"NULLCMD",
	"LOGIN",
	"ORDER",
	"CANCEL",
	"CANCELALL",
	"SLEEP",
	"QRYMONEY",
	"RESETUSERPASS",
	"QRYORDER",
	"QRYTRADE",
	"QRYMARKET",
	"QRYCLIENTPOSI",
	"QRYINSTRUMENT",
	"MONEYINOUT",
	"BTRANSF",
	"FTRANSB",
	"QRYEXCHTIMEDIFF",
	"QRYBANK",
	"QRYBANKFUND",
	"QRYBFINTERFACE",
	"FORQUOTE",				//  询价
	"QRYFORQUOTE",			//  询价查询
	"EXECORDER",				//  行权
	"EXECCANCEL",				//  行权撤单
	"QRYEXECORDER",			//  行权报单查询
	"EXTCMD",
	"LOGOUT"
};

int DecodeInputLine(char *buf,ST_INPUT_CMD &t_set)
{
	char stmp[500]; //will modify by 2012/05/20
	int iLen = 0;
	int i,j=0;
	int iCount = 0 ;

	memset(&t_set,0,sizeof(t_set));

	for (i=0;i<strlen(buf);i++)
	{
		stmp[j] = buf[i];
		if(stmp[j] == ',' || i==strlen(buf)-1)
		{
			stmp[j] = 0;
			j = 0;
			trim(stmp);
			//如果是null,改为''
			if(strcmp(stmp,"null")==0||strcmp(stmp,"NULL")==0)
			{
				memset(stmp,0,sizeof(stmp));
			}
			switch(iCount)
			{
			//	指令编号,指令类型,经纪商编号,交易所编号,投资者编号,交易用户代码
			case 0:
					strcpy(t_set.sCmdNo,stmp);					
					break;
			case 1:
				{
					strcpy(t_set.sCmdType,stmp);
					//如果sCmdType是按照 数字，则直接分类
					//如果sCmdType是按照 字母，需要比较出分类
					int iPos=0;
					int iipos = atoi(t_set.sCmdType);
					//最大类型应该是1000
					if((0<iipos)&& (iipos<=1000))
					{
						iPos = iipos;
					}
					else
					{
						strupr(t_set.sCmdType);
						for(iPos = LOGIN; iPos<= LOGOUT; iPos++)
						{
							if(strcmp(t_set.sCmdType,pCmdList[iPos]) == 0)
							{
								break;
							}
						}
					}
					t_set.sCmdTypeNum = iPos;
					break;
				}
			case 2:
					strcpy(t_set.ReqField.BrokerID,stmp);					
					break;
			case 3:
					strcpy(t_set.ReqField.ExchangeID,stmp);					
					break;
			case 4:
					strcpy(t_set.ReqField.OrderSysID,stmp);
					break;
			case 5:
					strcpy(t_set.ReqField.InvestorID,stmp);					
					break;
			case 6:
					strcpy(t_set.ReqField.UserID,stmp);					
					break;
			//	合约代码,用户本地报单编号,报单类型,买卖方向,开平标志,投机套保标志
			case 7:
					strcpy(t_set.ReqField.InstrumentID,stmp);					
					break;
			case 8:
					strcpy(t_set.ReqField.UserOrderLocalID,stmp);	
					if(strlen(stmp)==0)	
						t_set.bLocalIdFlag = false;
					else
						t_set.bLocalIdFlag = true;
					break;
			case 9:
					t_set.ReqField.OrderPriceType = stmp[0];					
					break;
			case 10:
					t_set.ReqField.Direction	=	stmp[0];					
					break;
			case 11:	
					t_set.ReqField.OffsetFlag = stmp[0];
					break;
			case 12:
					t_set.ReqField.HedgeFlag = stmp[0];
					break;
			//价格,数量,有效期类型,GTD日期,成交量类型
			case 13:
					t_set.ReqField.LimitPrice = atof(stmp);					
					break;
			case 14:
					t_set.ReqField.Volume = atol(stmp);					
					break;
			case 15:
					t_set.ReqField.TimeCondition = stmp[0];					
					break;
			case 16:
					strcpy(t_set.ReqField.GTDDate,stmp);					
					break;
			case 17:
					t_set.ReqField.VolumeCondition = stmp[0];					
					break;
			//最小成交量,止损价,强平原因
			case 18:
					t_set.ReqField.MinVolume = atol(stmp);					
					break;				
			case 19:
					t_set.ReqField.StopPrice =  atof(stmp);					
					break;
			case 20:
					t_set.ReqField.ForceCloseReason  = stmp[0];
					break;
			//自动挂起标志,业务单元,重复次数,业务类型
			case 21:
					t_set.ReqField.IsAutoSuspend = atoi(stmp);					
					break;
			case 22:
					strcpy(t_set.ReqField.BusinessUnit,stmp);					
					break;
			case 23:
					t_set.iRepeatNum = atoi(stmp);	
					// 默认设置为1次
					if(t_set.iRepeatNum == 0)
					{
						t_set.iRepeatNum = 1;
					}
					break;
			case 24:
					t_set.ReqField.BusinessType =stmp[0];					
					break;
			};
			iCount ++;
		}
		else
		{
			j++;
		}
	}		
	return 0;
}

int ProcessCmd(ST_INPUT_CMD *sInputCmd,FILE* f_out,int pos)
{
	char szbuf[200];
	int	 iRet=0;
	int  iMaxWaitTime = 0;

	if(pProcessor != NULL)
		pProcessor-> m_bFirstPackage = true;

	//	全局宏替换
	ReplaceMarcoStr(&sInputCmd->ReqField);

	switch (sInputCmd->sCmdTypeNum) 
	{
		case LOGIN:
				sprintf(szbuf,"%s@%s",sInputCmd->ReqField.UserID,m_TradeIp);				
				if(pProcessor!=NULL)
				{					
					pProcessor->Release();
					delete pProcessor;
					pProcessor=NULL;
					ShowMsg("\n beforeLogin: 席位退出\n");
				}
//				printf("第 %d 次创建API \n",iProcessorCount);
				if (strcmp(sInputCmd->ReqField.BrokerID,"用户") == 0)
				{
					pProcessor = new CProcessor(iProcessorCount++,sInputCmd->ReqField.BrokerID,sInputCmd->ReqField.UserID,sInputCmd->ReqField.InstrumentID,f_out,true);
				}
				else
				{
					pProcessor = new CProcessor(iProcessorCount++,sInputCmd->ReqField.BrokerID,sInputCmd->ReqField.UserID,sInputCmd->ReqField.InstrumentID,f_out);
				}
				
				ShowMsg("%s,登录,席位[%s],密码[%s]",sInputCmd->sCmdNo,sInputCmd->ReqField.UserID,sInputCmd->ReqField.InstrumentID);

				iRet = pProcessor->ReqUserLogin(NULL,NULL,NULL);
				if(iRet!=0)
					break;
				pProcessor->WaitAction(10);
				iTotalOrderCnt= 0;  // 总委托总数 
				iWaitOrderPos = 0;
				ShowMsg("\n");
				break;
		case ORDER:
				CQdpFtdcInputOrderField pOrder;
				memcpy(&pOrder,&sInputCmd->ReqField,sizeof(CQdpFtdcInputOrderField));
				
				//	不填入本地报单号则自动获取
				if(sInputCmd->bLocalIdFlag == false)
					sprintf(pOrder.UserOrderLocalID,"%08u",pProcessor->m_iLocalNo++);
				else
					sprintf(pOrder.UserOrderLocalID,"%08s",sInputCmd->ReqField.UserOrderLocalID);
				
				// 写回sInputCmd,做异步处理的判定用 
				strcpy(sInputCmd->ReqField.UserOrderLocalID,pOrder.UserOrderLocalID);
				
				if (NULL == pOrder.BusinessType)
				{
					pOrder.BusinessType =  QDP_FTDC_BT_Normal;
				}
				else
				{
					printf("交割申报");
				}

				if(bWaitActionFlag != true)
				ShowMsg("%s,委托,UserID[%s],BrokerID[%s],InvestorID[%s],InstrumentID[%s],Direction[%c],Volume[%d],LimitPrice[%.3f],UserOrderLocalID[%s]",
						sInputCmd->sCmdNo,
						sInputCmd->ReqField.UserID,
						sInputCmd->ReqField.BrokerID,
						sInputCmd->ReqField.InvestorID,
						sInputCmd->ReqField.InstrumentID,
						sInputCmd->ReqField.Direction,
						sInputCmd->ReqField.Volume,
						sInputCmd->ReqField.LimitPrice,
						pOrder.UserOrderLocalID
						);
				printf("\n");
				GET_ACCURATE_USEC_TIME(lReqTime);
#ifdef WIN32
				printf("SendReq UserOrderLocalID[%s]-[%I64d],",pOrder.UserOrderLocalID,lReqTime);
#else
				printf("SendReq UserOrderLocalID[%s]-[%lld],",pOrder.UserOrderLocalID,lReqTime);
#endif
				iRet = pProcessor->m_pFfexFtdcUserApi->ReqOrderInsert(&pOrder, pProcessor->m_nRequestID++);
				if(iRet!=0)
					break;

				//撤单记录到orderActionList		
				orderActionList.push_back(pos);
				iTotalOrderCnt++ ;  // 总委托总数

//				if(sInputCmd->iRepeatNum == 0  // 连续指令的  && bFastFlag == false)
				//	20100518 modi 
				if(bFastFlag == false)
				{
					pProcessor->WaitAction(10);					
				}				
				break;
		case CANCEL:
			{
				SLEEP_SECONDS(1);
				CQdpFtdcOrderActionField pOrderAction;
				memset(&pOrderAction,0,sizeof(pOrderAction));

				pOrderAction.ActionFlag = QDP_FTDC_AF_Delete;	//报单操作标志	
				strcpy(pOrderAction.UserID,sInputCmd->ReqField.UserID);
				// 根据指令编号查找系统委托号				
				sprintf(pOrderAction.UserOrderActionLocalID,"%08u",pProcessor->m_iLocalNo++);
				strcpy(pOrderAction.BrokerID,sInputCmd->ReqField.BrokerID);
				strcpy(pOrderAction.ExchangeID,sInputCmd->ReqField.ExchangeID);
				strcpy(pOrderAction.InvestorID,sInputCmd->ReqField.InvestorID);

				int i = 0;
				int iPos = -1;				
				for(i=0; i<= iCurCmdPos;i++)
				{
					if((sInputCmdArray[i].sCmdTypeNum==ORDER))
					{
						iPos = i;
						//如果输入为空表示是最近一笔委托
						if(strcmp("",sInputCmd->ReqField.UserOrderLocalID) !=0)
						{
							if (strcmp(sInputCmd->ReqField.UserOrderLocalID,sInputCmdArray[i].sCmdNo)==0) 
							{ 
								break;
							}
						}
					}
				}				
			
				if ( iPos > -1 && (strcmp("",sInputCmdArray[iPos].ReqField.OrderSysID) !=0))
				{					
					strcpy(pOrderAction.OrderSysID,sInputCmdArray[iPos].ReqField.OrderSysID);
					ShowMsg("%s,撤单,UserID[%s],BrokerID[%s],InvestorID[%s],ExchangeID[%s],撤单号[%s],本地报单号[%s]",
							sInputCmd->sCmdNo,
							pOrderAction.UserID,
							pOrderAction.BrokerID,
							pOrderAction.InvestorID,
							pOrderAction.ExchangeID,
							pOrderAction.OrderSysID,
							pOrderAction.UserOrderActionLocalID);
					GET_ACCURATE_USEC_TIME(lReqTime);
#ifdef WIN32
					printf("SendReqAction UserOrderLocalID[%s]-[%I64d],",pOrder.UserOrderLocalID,lReqTime);
#else
					printf("SendReqAction UserOrderLocalID[%s]-[%lld],",pOrder.UserOrderLocalID,lReqTime);
#endif
					iRet = pProcessor->m_pFfexFtdcUserApi->ReqOrderAction(&pOrderAction,pProcessor->m_nRequestID++);
					if(iRet!=0)
						break;					
					pProcessor->WaitAction(10);
					ShowMsg("\n");
				}
				else
				{
					ShowMsg("%s,撤单失败,未找到报单\n",sInputCmd->sCmdNo);
					sInputCmd->pRspInfo.ErrorID = 100;
					strcpy(sInputCmd->pRspInfo.ErrorMsg,"撤单失败");
				}
				break;
			}
		case CANCELALL:
			{
				pProcessor->m_iTotalRecordCnt = orderActionList.size();
				ShowMsg("%s 全部撤单 ==> 共 %d 笔可撤委托\n",sInputCmd->sCmdNo,pProcessor->m_iTotalRecordCnt);

				list<int>::iterator iter = orderActionList.begin();
				while(iter != orderActionList.end())
				{
					int ipos = *iter;
					sInputCmd = &sInputCmdArray[ipos];
					CQdpFtdcOrderActionField pOrderAction;
					memset(&pOrderAction,0,sizeof(pOrderAction));
					pOrderAction.ActionFlag = QDP_FTDC_AF_Delete;
					strcpy(pOrderAction.UserID,sInputCmd->ReqField.UserID);
					strcpy(pOrderAction.BrokerID,sInputCmd->ReqField.BrokerID);
					strcpy(pOrderAction.ExchangeID,sInputCmd->ReqField.ExchangeID);
					strcpy(pOrderAction.InvestorID,sInputCmd->ReqField.InvestorID);
					strcpy(pOrderAction.UserOrderLocalID,sInputCmd->ReqField.UserOrderLocalID);
					strcpy(pOrderAction.OrderSysID,sInputCmd->ReqField.OrderSysID);

					sprintf(pOrderAction.UserOrderActionLocalID,"%012u",pProcessor->m_iLocalNo++);
					
 					ShowMsg(" --> 撤单: UserID[%s],BrokerID[%s],ExchangeID[%s],InvestorID[%s],UserOrderLocalID[%s],OrderSysID[%s],UserOrderActionLocalID[%s]",
						pOrderAction.UserID,
						pOrderAction.BrokerID,
						pOrderAction.ExchangeID,
						pOrderAction.InvestorID,
						pOrderAction.UserOrderLocalID,
						pOrderAction.OrderSysID,
						pOrderAction.UserOrderActionLocalID);

 					iRet = pProcessor->m_pFfexFtdcUserApi->ReqOrderAction(&pOrderAction,pProcessor->m_nRequestID++);
					if(iRet != 0)
					{
						//发送不成功，重新发送
						SLEEP_SECONDS(10);
						continue;
					}
 					pProcessor->WaitAction(10);
					//如果没有回来，指针不会往后走
					if(sInputCmd->bReciveRsp)
						iter++;
				}
				orderActionList.clear();
				break;
			}
		case SLEEP:	
			{
				ShowMsg("%s,系统暂停,%s 秒",sInputCmd->sCmdNo,sInputCmd->ReqField.BrokerID);
				ShowMsg(" ==> ");
				int sleepseconds = atoi(sInputCmd->ReqField.BrokerID);
				SLEEP_SECONDS(sleepseconds);
				ShowMsg(" 成功 \n");
				break;
			}
		case QRYMONEY:
				// 防止查询资金指令比委托先到，特延时一秒处理
				SLEEP_SECONDS(1);
				CQdpFtdcQryInvestorAccountField pQryInvestorAccount;
				memset(&pQryInvestorAccount,0,sizeof(pQryInvestorAccount));
				strcpy(pQryInvestorAccount.BrokerID,sInputCmd->ReqField.BrokerID);
				strcpy(pQryInvestorAccount.UserID,sInputCmd->ReqField.UserID);
				strcpy(pQryInvestorAccount.InvestorID,sInputCmd->ReqField.InvestorID);

				ShowMsg("%s,资金查询,BrokerID[%s],UserID[%s],InvestorID[%s]",sInputCmd->sCmdNo,sInputCmd->ReqField.BrokerID,sInputCmd->ReqField.UserID,sInputCmd->ReqField.InvestorID);
				iRet = pProcessor->m_pFfexFtdcUserApi->ReqQryInvestorAccount(&pQryInvestorAccount,pProcessor->m_nRequestID++) ;
				if(iRet!=0)
					break;
				pProcessor->WaitAction(5);
				ShowMsg("\n");
				break;
		case RESETUSERPASS:
				CQdpFtdcUserPasswordUpdateField pUserPasswordUpdate;
				strcpy(pUserPasswordUpdate.BrokerID,sInputCmd->ReqField.BrokerID);
				strcpy(pUserPasswordUpdate.UserID,sInputCmd->ReqField.UserID);
				strcpy(pUserPasswordUpdate.OldPassword,sInputCmd->ReqField.OrderSysID);
				strcpy(pUserPasswordUpdate.NewPassword,sInputCmd->ReqField.InstrumentID);
				ShowMsg("%s,修改密码,BrokerID[%s],UserID[%s],PassWord[%s]",sInputCmd->ReqField.BrokerID,sInputCmd->ReqField.UserID,sInputCmd->ReqField.InstrumentID);
				iRet = pProcessor->m_pFfexFtdcUserApi->ReqUserPasswordUpdate(&pUserPasswordUpdate,pProcessor->m_nRequestID++);
				if(iRet!=0)
					break;
				pProcessor->WaitAction(5);
				break;
		case QRYORDER:
			{	
				SLEEP_SECONDS(1);
				///报单查询请求			
				CQdpFtdcQryOrderField ReqField;			
				memset(&ReqField,0,sizeof(ReqField));
				strcpy(ReqField.BrokerID,sInputCmd->ReqField.BrokerID);	
				strcpy(ReqField.ExchangeID,sInputCmd->ReqField.ExchangeID);
				strcpy(ReqField.InvestorID,sInputCmd->ReqField.InvestorID);
				strcpy(ReqField.InstrumentID,sInputCmd->ReqField.InstrumentID);
				strcpy(ReqField.UserID ,sInputCmd->ReqField.UserID);
				int i = 0;
				int iPos = -1;
				for(i=0; i<= iCurCmdPos;i++)
				{
					if((sInputCmdArray[i].sCmdTypeNum==ORDER))
					{
						iPos = i;
						//如果输入为空表示是最近一笔委托
						if(strcmp("",sInputCmd->ReqField.UserOrderLocalID) !=0)
						{
							if (strcmp(sInputCmd->ReqField.UserOrderLocalID,sInputCmdArray[i].sCmdNo)==0) 
							{ 
								break;
							}
						}
					}
				}

				//ShowMsg("iPos = %d, iTime= %d",iPos,iTime);
				ShowMsg("%s,委托查询,UserID:%s,BrokerID:%s,InvestorID:%s,InstrumentID:%s,OrderSysID:%s",
					sInputCmd->sCmdNo,
					sInputCmd->ReqField.UserID,
					sInputCmd->ReqField.BrokerID,
					sInputCmd->ReqField.InvestorID,
					sInputCmd->ReqField.InstrumentID,
					(iPos> -1)?sInputCmdArray[iPos].ReqField.OrderSysID:"");

				if ( iPos > -1 && (strcmp("",sInputCmdArray[iPos].ReqField.OrderSysID) !=0))
				{			
					strcpy(ReqField.OrderSysID,sInputCmdArray[iPos].ReqField.OrderSysID);
					
					iRet = pProcessor->m_pFfexFtdcUserApi->ReqQryOrder(&ReqField,pProcessor->m_nRequestID++);
					if(iRet!=0)
						break;
					pProcessor->WaitAction(5);
				}
				else
				{
					ShowMsg("委托查询失败\n");
					sInputCmd->pRspInfo.ErrorID = 100;
					strcpy(sInputCmd->pRspInfo.ErrorMsg,"委托查询失败");
				}
				break;
			}
		case QRYTRADE:
			{
				SLEEP_SECONDS(1);
				///成交查询请求			
				CQdpFtdcQryTradeField ReqField;			
				memset(&ReqField,0,sizeof(ReqField));
				strcpy(ReqField.BrokerID,sInputCmd->ReqField.BrokerID);
				strcpy(ReqField.InvestorID,sInputCmd->ReqField.InvestorID);
				strcpy(ReqField.InstrumentID,sInputCmd->ReqField.InstrumentID);
				strcpy(ReqField.UserID,sInputCmd->ReqField.UserID);
				int i = 0;
				int iPos = -1;
				for(i=0; i<= iCurCmdPos;i++)
				{
					if((sInputCmdArray[i].sCmdTypeNum==ORDER))
					{
						iPos = i;
						//如果输入为空表示是最近一笔委托
						if(strcmp("",sInputCmd->ReqField.UserOrderLocalID) !=0)
						{
							if (strcmp(sInputCmd->ReqField.UserOrderLocalID,sInputCmdArray[i].sCmdNo)==0) 
							{ 
								break;
							}
						}
					}
				}
				
				ShowMsg("%s,成交查询,UserID:%s,ParticipantID:%s,ClientID:%s,InstrumentID:%s,OrderSysID:%s,[TradeID:%s] ",
					sInputCmd->sCmdNo,
					sInputCmd->ReqField.UserID,
					sInputCmd->ReqField.BrokerID,
					sInputCmd->ReqField.InvestorID,
					sInputCmd->ReqField.InstrumentID,
					(iPos> -1)?sInputCmdArray[iPos].ReqField.OrderSysID:"",
					(iPos> -1)?sInputCmdArray[iPos].TradeID:""
						);
				
				if ( iPos > -1 && (strcmp("",sInputCmdArray[iPos].TradeID) !=0))
				{			
					strcpy(ReqField.TradeID,sInputCmdArray[iPos].TradeID);
					strcpy(sInputCmd->ReqField.OrderSysID,sInputCmdArray[iPos].ReqField.OrderSysID);
					
					iRet = pProcessor->m_pFfexFtdcUserApi->ReqQryTrade(&ReqField,pProcessor->m_nRequestID++) ;
					if(iRet!=0)
						break;
					pProcessor->WaitAction(5);
				}
				else
				{
					ShowMsg("成交查询失败\n");
					sInputCmd->pRspInfo.ErrorID = 100;
					strcpy(sInputCmd->pRspInfo.ErrorMsg,"成交查询失败");
				}
				break;
			}
		case LOGOUT:
				pProcessor->Release();
				delete pProcessor;
				pProcessor=NULL;
				ShowMsg("%s,席位退出",sInputCmd->sCmdNo);
				ShowMsg(" ==>  成功 \n");
				break;
		case MONEYINOUT:	
				CQdpFtdcReqAccountDepositField pDeposit;
				memset(&pDeposit, 0, sizeof(CQdpFtdcReqAccountDepositField));
				strcpy(pDeposit.BrokerID,sInputCmd->ReqField.BrokerID);
				strcpy(pDeposit.AccountSeqNo,sInputCmd->ReqField.OrderSysID);
				strcpy(pDeposit.InvestorID,sInputCmd->ReqField.InvestorID);
				strcpy(pDeposit.UserID,sInputCmd->ReqField.UserID);
				strcpy(pDeposit.AccountID,sInputCmd->ReqField.InstrumentID);
				pDeposit.AmountDirection = sInputCmd->ReqField.Direction;
				pDeposit.Amount = sInputCmd->ReqField.LimitPrice;
				ShowMsg("%s,出入金请求,BrokerID[%s],UserID[%s],InverstorID[%s]AccountID[%s]AccountSeqNo[%s]AmountDirection[%c]Amount[%.2f]",
					sInputCmd->sCmdNo,sInputCmd->ReqField.BrokerID,sInputCmd->ReqField.UserID,sInputCmd->ReqField.InvestorID,sInputCmd->ReqField.InstrumentID,
					sInputCmd->ReqField.OrderSysID,sInputCmd->ReqField.Direction,sInputCmd->ReqField.LimitPrice);
				iRet = pProcessor->m_pFfexFtdcUserApi->ReqAccountDeposit(&pDeposit,pProcessor->m_nRequestID++);
				if(iRet!=0)
					break;
				pProcessor->WaitAction(5);				
				break;
		case EXTCMD:
				sprintf(szbuf,"%s %s %s ",m_ExternCmd,sInputCmd->ReqField.UserID,sInputCmd->ReqField.InstrumentID);
				ShowMsg("%s,外部过程调用[%s],%s,%s",
						sInputCmd->sCmdNo,
					sInputCmd->ReqField.BusinessUnit,
					sInputCmd->ReqField.UserID,
					sInputCmd->ReqField.InstrumentID
					);
				system(szbuf);
				ShowMsg(" ==>[%s]成功\n",sInputCmd->ReqField.BusinessUnit);
				break;
		case QRYCLIENTPOSI:
				SLEEP_SECONDS(1);
				CQdpFtdcQryInvestorPositionField pQryInvestorPosition;
				strcpy(pQryInvestorPosition.BrokerID,sInputCmd->ReqField.BrokerID);
				strcpy(pQryInvestorPosition.InvestorID,sInputCmd->ReqField.InvestorID);
				strcpy(pQryInvestorPosition.InstrumentID,sInputCmd->ReqField.InstrumentID);
				strcpy(pQryInvestorPosition.ExchangeID,sInputCmd->ReqField.ExchangeID);
				strcpy(pQryInvestorPosition.UserID,sInputCmd->ReqField.UserID);
				ShowMsg("%s,客户持仓查询,ExchangeID[%s],BrokerID[%s],InvestorID[%s],InstrumentID[%s]",
					sInputCmd->sCmdNo,
					sInputCmd->ReqField.ExchangeID,
					sInputCmd->ReqField.BrokerID,
					sInputCmd->ReqField.InvestorID,
					sInputCmd->ReqField.InstrumentID);
				iRet = pProcessor->m_pFfexFtdcUserApi->ReqQryInvestorPosition(&pQryInvestorPosition,pProcessor->m_nRequestID++);
				if(iRet!=0)
					break;
				pProcessor->WaitAction(5);			
				ShowMsg("\n");
				break;
		case QRYINSTRUMENT:
				CQdpFtdcQryInstrumentField pQryInstrument;
				memset(&pQryInstrument,0,sizeof(pQryInstrument));
				strcpy(pQryInstrument.InstrumentID,sInputCmd->ReqField.InstrumentID);
				strcpy(pQryInstrument.ExchangeID,sInputCmd->ReqField.ExchangeID);
				ShowMsg("%s,合约查询,InstrumentID[%s],ExchangeID[%s]",
					sInputCmd->sCmdNo,
					sInputCmd->ReqField.InstrumentID,
					sInputCmd->ReqField.ExchangeID);
				iRet = pProcessor->m_pFfexFtdcUserApi->ReqQryInstrument(&pQryInstrument,pProcessor->m_nRequestID++);
				if(iRet!=0)
					break;
				pProcessor->WaitAction(2);			
				ShowMsg("\n");				
				break;
		case QRYMARKET:
				CQdpFtdcQryMarketDataField pQryMarketData;
				memset(&pQryMarketData,0,sizeof(pQryMarketData));
				strcpy(pQryMarketData.InstrumentID,sInputCmd->ReqField.InstrumentID);
				strcpy(pQryMarketData.ExchangeID,sInputCmd->ReqField.ExchangeID);
				ShowMsg("%s,实时行情查询,InstrumentID[%s],ExchangeID[%s]",
					sInputCmd->sCmdNo, 
					sInputCmd->ReqField.InstrumentID, 
					sInputCmd->ReqField.ExchangeID);
				iRet = pProcessor->m_pFfexFtdcUserApi->ReqQryMarketData(&pQryMarketData,pProcessor->m_nRequestID++);
				if(iRet!=0)
					break;
				pProcessor->WaitAction(2);			
				ShowMsg("\n");	
				break;
// 		case QRYEXCHTIMEDIFF:
// 				CQdpFtdcQryExchangeDiffTimeField pQryExchangeDiffTime;
// 				memset(&pQryExchangeDiffTime,0,sizeof(pQryExchangeDiffTime));
// 				strcpy(pQryExchangeDiffTime.ExchangeID,sInputCmd->ReqField.ExchangeID);
// 				ShowMsg("%s,交易所时间偏差查询,ExchangeID[%s]",sInputCmd->sCmdNo, sInputCmd->ReqField.ExchangeID);
// 				iRet = pProcessor->m_pFfexFtdcUserApi->ReqQryExchangeDiffTime(&pQryExchangeDiffTime,pProcessor->m_nRequestID++);
// 				if(iRet!=0)
// 					break;
// 				pProcessor->WaitAction(2);			
// 				ShowMsg("\n");	
// 				break;
// 		case QRYBANK:
// 				CQdpFtdcQryContractBankField pQryContractBank;
// 				memset(&pQryContractBank,0,sizeof(pQryContractBank));
// 				strcpy(pQryContractBank.BrokerID,sInputCmd->ReqField.BrokerID);
// 				strcpy(pQryContractBank.InvestorID,sInputCmd->ReqField.InvestorID);
// 				strcpy(pQryContractBank.UserID,sInputCmd->ReqField.UserID);
// 				ShowMsg("%s,签约银行查询,BrokerID[%s],InvestorID[%s],UserID[%s]",
// 					sInputCmd->sCmdNo,
// 					sInputCmd->ReqField.BrokerID,
// 					sInputCmd->ReqField.InvestorID,
// 					sInputCmd->ReqField.UserID);
// 				iRet = pProcessor->m_pFfexFtdcUserApi->ReqQryContractBank(&pQryContractBank,pProcessor->m_nRequestID++);
// 				if(iRet!=0)
// 					break;
// 				pProcessor->WaitAction(2);			
// 				ShowMsg("\n");	
// 				break;
// 		case QRYBANKFUND:
// 				CQdpFtdcReqQueryAccountField pReqQueryAccount;
// 				memset(&pReqQueryAccount,0,sizeof(pReqQueryAccount));
// 				strcpy(pReqQueryAccount.BrokerID,sInputCmd->ReqField.BrokerID);
// 				strcpy(pReqQueryAccount.InvestorID,sInputCmd->ReqField.InvestorID);
// 				strcpy(pReqQueryAccount.UserID,sInputCmd->ReqField.UserID);
// 				strcpy(pReqQueryAccount.AccountID,sInputCmd->ReqField.InstrumentID);
// 				strcpy(pReqQueryAccount.BankID,sInputCmd->ReqField.ExchangeID);
// 				strcpy(pReqQueryAccount.BankPassWord,sInputCmd->ReqField.UserOrderLocalID);
// 				strcpy(pReqQueryAccount.TradeDate,sInputCmd->ReqField.GTDDate);
// 				ShowMsg("%s,银行余额查询,BrokerID[%s],InvestorID[%s],UserID[%s],AccountID[%s],BankID[%s], BankPassWord[%s],TradeDate[%s]",
// 					sInputCmd->sCmdNo,
// 					sInputCmd->ReqField.BrokerID,
// 					sInputCmd->ReqField.InvestorID,
// 					sInputCmd->ReqField.UserID,
// 					sInputCmd->ReqField.InstrumentID,
// 					sInputCmd->ReqField.ExchangeID,
// 					sInputCmd->ReqField.UserOrderLocalID,
// 					sInputCmd->ReqField.GTDDate);
// 				iRet = pProcessor->m_pFfexFtdcUserApi->ReqQueryBankAccountMoneyByFuture(&pReqQueryAccount,pProcessor->m_nRequestID++);
// 				if(iRet!=0)
// 					break;
// 				pProcessor->WaitAction(2);			
// 				ShowMsg("\n");	
// 				break;
// 		case QRYBFINTERFACE:
// 				CQdpFtdcQryTransferSerialField pQryTransferSerial;
// 				memset(&pQryTransferSerial,0,sizeof(pQryTransferSerial));
// 				strcpy(pQryTransferSerial.BrokerID,sInputCmd->ReqField.BrokerID);
// 				strcpy(pQryTransferSerial.InvestorID,sInputCmd->ReqField.InvestorID);
// 				strcpy(pQryTransferSerial.UserID,sInputCmd->ReqField.UserID);
// 				strcpy(pQryTransferSerial.BankID,sInputCmd->ReqField.ExchangeID);
// 				ShowMsg("%s,转账流水查询,BrokerID[%s],InvestorID[%s],UserID[%s],BankID[%s]",
// 					sInputCmd->sCmdNo,
// 					sInputCmd->ReqField.BrokerID,
// 					sInputCmd->ReqField.InvestorID,
// 					sInputCmd->ReqField.UserID,
// 					sInputCmd->ReqField.ExchangeID);
// 				iRet = pProcessor->m_pFfexFtdcUserApi->ReqQryTransferSerial(&pQryTransferSerial,pProcessor->m_nRequestID++);
// 				if(iRet!=0)
// 					break;
// 				pProcessor->WaitAction(2);			
// 				ShowMsg("\n");	
// 				break;
// 		case BTRANSF:	
// 				CQdpFtdcReqTransferField pReqTransfer;
// 				memset(&pReqTransfer, 0, sizeof(pReqTransfer));
// 				strcpy(pReqTransfer.BrokerID,sInputCmd->ReqField.BrokerID);
// 				strcpy(pReqTransfer.InvestorID,sInputCmd->ReqField.InvestorID);
// 				strcpy(pReqTransfer.UserID,sInputCmd->ReqField.UserID);
// 				strcpy(pReqTransfer.AccountID,sInputCmd->ReqField.InstrumentID);
// 				strcpy(pReqTransfer.BankID,sInputCmd->ReqField.ExchangeID);
// 				strcpy(pReqTransfer.BankPassWord,sInputCmd->ReqField.UserOrderLocalID);
// 				strcpy(pReqTransfer.Password,sInputCmd->ReqField.OrderSysID);
// 				pReqTransfer.TradeAmount = sInputCmd->ReqField.LimitPrice;
// 
// 				ShowMsg("%s,银转期请求,BrokerID[%s],UserID[%s],InverstorID[%s]AccountID[%s]BankID[%s]BankPassWord[%s]PassWord[%s]TradeAmount[%.2f]",
// 					sInputCmd->sCmdNo,sInputCmd->ReqField.BrokerID,sInputCmd->ReqField.UserID,sInputCmd->ReqField.InvestorID,sInputCmd->ReqField.InstrumentID,
// 					sInputCmd->ReqField.ExchangeID,sInputCmd->ReqField.UserOrderLocalID,sInputCmd->ReqField.OrderSysID,sInputCmd->ReqField.LimitPrice);
// 				iRet = pProcessor->m_pFfexFtdcUserApi->ReqFromBankToFutureByFuture(&pReqTransfer,pProcessor->m_nRequestID++);
// 				if(iRet!=0)
// 					break;
// 				pProcessor->WaitAction(5);				
// 				break;
// 		case FTRANSB:	
// 				CQdpFtdcReqTransferField pReqTransfer1;
// 				memset(&pReqTransfer1, 0, sizeof(pReqTransfer));
// 				strcpy(pReqTransfer1.BrokerID,sInputCmd->ReqField.BrokerID);
// 				strcpy(pReqTransfer1.InvestorID,sInputCmd->ReqField.InvestorID);
// 				strcpy(pReqTransfer1.UserID,sInputCmd->ReqField.UserID);
// 				strcpy(pReqTransfer1.AccountID,sInputCmd->ReqField.InstrumentID);
// 				strcpy(pReqTransfer1.BankID,sInputCmd->ReqField.ExchangeID);
// 				strcpy(pReqTransfer1.BankPassWord,sInputCmd->ReqField.UserOrderLocalID);
// 				strcpy(pReqTransfer1.Password,sInputCmd->ReqField.OrderSysID);
// 				pReqTransfer1.TradeAmount = sInputCmd->ReqField.LimitPrice;
// 
// 				ShowMsg("%s,期转银请求,BrokerID[%s],UserID[%s],InverstorID[%s]AccountID[%s]BankID[%s]BankPassWord[%s]PassWord[%s]TradeAmount[%.2f]",
// 					sInputCmd->sCmdNo,sInputCmd->ReqField.BrokerID,sInputCmd->ReqField.UserID,sInputCmd->ReqField.InvestorID,sInputCmd->ReqField.InstrumentID,
// 					sInputCmd->ReqField.ExchangeID,sInputCmd->ReqField.UserOrderLocalID,sInputCmd->ReqField.OrderSysID,sInputCmd->ReqField.LimitPrice);
// 				iRet = pProcessor->m_pFfexFtdcUserApi->ReqFromFutureToBankByFuture(&pReqTransfer1,pProcessor->m_nRequestID++);
// 
// 				if(iRet!=0)
// 					break;
// 				pProcessor->WaitAction(5);				
// 				break;
// 		case FORQUOTE:	
// 			CQdpFtdcInputForQuoteField InputForQuote;
// 			memset(&InputForQuote, 0, sizeof(CQdpFtdcInputForQuoteField));
// 
// 			//	不填入本地报单号则自动获取
// 			if(sInputCmd->bLocalIdFlag == false)
// 				sprintf(InputForQuote.UserOrderLocalID,"%012u",pProcessor->m_iLocalNo++);
// 			else
// 				sprintf(InputForQuote.UserOrderLocalID,"%012s",sInputCmd->ReqField.UserOrderLocalID);
// 			
// 			// 写回sInputCmd,做异步处理的判定用 
// 			strcpy(sInputCmd->ReqField.UserOrderLocalID,InputForQuote.UserOrderLocalID);
// 
// 			strcpy(InputForQuote.BrokerID,sInputCmd->ReqField.BrokerID);
// 			strcpy(InputForQuote.UserID,sInputCmd->ReqField.UserID);
// 			strcpy(InputForQuote.InvestorID,sInputCmd->ReqField.InvestorID);
// 			strcpy(InputForQuote.ExchangeID,sInputCmd->ReqField.ExchangeID);
// 			strcpy(InputForQuote.InstrumentID,sInputCmd->ReqField.InstrumentID);
// 			ShowMsg("%s,询价录入请求,BrokerID[%s],InvestorID[%s],ExchangeID[%s]InstrumentID[%s]",
// 				sInputCmd->sCmdNo,sInputCmd->ReqField.BrokerID,sInputCmd->ReqField.InvestorID,sInputCmd->ReqField.ExchangeID,sInputCmd->ReqField.InstrumentID);
// 			iRet = pProcessor->m_pFfexFtdcUserApi->ReqForQuoteInsert(&InputForQuote,pProcessor->m_nRequestID++);
// 			if(iRet!=0)
// 				break;
// 			pProcessor->WaitAction(5);				
// 				break;
// 		case QRYFORQUOTE:	
// 			CQdpFtdcQryForQuoteField QryForQuote;
// 			memset(&QryForQuote, 0, sizeof(CQdpFtdcQryForQuoteField));
// 			strcpy(QryForQuote.BrokerID,sInputCmd->ReqField.BrokerID);
// 			strcpy(QryForQuote.InvestorID,sInputCmd->ReqField.InvestorID);
// 			strcpy(QryForQuote.ExchangeID,sInputCmd->ReqField.ExchangeID);
// 			strcpy(QryForQuote.InstrumentID,sInputCmd->ReqField.InstrumentID);
// 			ShowMsg("%s,询价查询请求,BrokerID[%s],InvestorID[%s],ExchangeID[%s]InstrumentID[%s]",
// 				sInputCmd->sCmdNo,sInputCmd->ReqField.BrokerID,sInputCmd->ReqField.InvestorID,sInputCmd->ReqField.ExchangeID,sInputCmd->ReqField.InstrumentID);
// 			iRet = pProcessor->m_pFfexFtdcUserApi->ReqQryForQuote(&QryForQuote,pProcessor->m_nRequestID++);
// 			if(iRet!=0)
// 				break;
// 			pProcessor->WaitAction(5);				
// 				break;
// 		case EXECORDER:	
// 			CQdpFtdcInputExecOrderField InputExecOrder;
// 			memset(&InputExecOrder, 0, sizeof(CQdpFtdcInputExecOrderField));
// 			
// 			//	不填入本地报单号则自动获取
// 			if(sInputCmd->bLocalIdFlag == false)
// 				sprintf(InputExecOrder.UserOrderLocalID,"%012u",pProcessor->m_iLocalNo++);
// 			else
// 				sprintf(InputExecOrder.UserOrderLocalID,"%012s",sInputCmd->ReqField.UserOrderLocalID);
// 			
// 			// 写回sInputCmd,做异步处理的判定用 
// 			strcpy(sInputCmd->ReqField.UserOrderLocalID,InputExecOrder.UserOrderLocalID);
// 			
// 			strcpy(InputExecOrder.BrokerID,sInputCmd->ReqField.BrokerID);
// 			strcpy(InputExecOrder.UserID,sInputCmd->ReqField.UserID);
// 			strcpy(InputExecOrder.InvestorID,sInputCmd->ReqField.InvestorID);
// 			strcpy(InputExecOrder.ExchangeID,sInputCmd->ReqField.ExchangeID);
// 			strcpy(InputExecOrder.InstrumentID,sInputCmd->ReqField.InstrumentID);
// 			InputExecOrder.HedgeFlag = sInputCmd->ReqField.HedgeFlag;
// 			InputExecOrder.PosiDirection = sInputCmd->ReqField.Direction;
// 			InputExecOrder.Volume = sInputCmd->ReqField.Volume;
// 			InputExecOrder.ActionType = sInputCmd->ReqField.OrderPriceType;
// 			ShowMsg("%s,行权录入请求,BrokerID[%s],UserID[%s]InvestorID[%s],ExchangeID[%s],InstrumentID[%s],HedgeFlag[%c],PosiDirection[%c],Volume[%d],ActionType[%c]",
// 				sInputCmd->sCmdNo,sInputCmd->ReqField.BrokerID,sInputCmd->ReqField.UserID,sInputCmd->ReqField.InvestorID,sInputCmd->ReqField.ExchangeID,\
// 				sInputCmd->ReqField.InstrumentID,sInputCmd->ReqField.HedgeFlag,sInputCmd->ReqField.Direction,sInputCmd->ReqField.Volume,sInputCmd->ReqField.OrderPriceType);
// 			iRet = pProcessor->m_pFfexFtdcUserApi->ReqExecOrderInsert(&InputExecOrder,pProcessor->m_nRequestID++);
// 			if(iRet!=0)
// 				break;
// 			pProcessor->WaitAction(5);				
// 				break;
// 		case EXECCANCEL:
// 			{
// 				SLEEP_SECONDS(1);
// 				CQdpFtdcExecOrderActionField pOrderAction;
// 				memset(&pOrderAction,0,sizeof(CQdpFtdcExecOrderActionField));
// 				
// 				pOrderAction.ActionFlag = QDP_FTDC_AF_Delete;	//报单操作标志	
// 				strcpy(pOrderAction.UserID,sInputCmd->ReqField.UserID);
// 				// 根据指令编号查找系统委托号				
// 				sprintf(pOrderAction.UserOrderActionLocalID,"%012u",pProcessor->m_iLocalNo++);
// 				strcpy(pOrderAction.BrokerID,sInputCmd->ReqField.BrokerID);
// 				strcpy(pOrderAction.ExchangeID,sInputCmd->ReqField.ExchangeID);
// 				//				strcpy(pOrderAction.InvestorID,sInputCmd->ReqField.InvestorID);
// 				
// 				int i = 0;
// 				int iPos = -1;				
// 				for(i=0; i<= iCurCmdPos;i++)
// 				{
// 					if((sInputCmdArray[i].sCmdTypeNum==EXECORDER))
// 					{
// 						iPos = i;
// 						//如果输入为空表示是最近一笔委托
// 						if(strcmp("",sInputCmd->ReqField.UserOrderLocalID) !=0)
// 						{
// 							if (strcmp(sInputCmd->ReqField.UserOrderLocalID,sInputCmdArray[i].sCmdNo)==0) 
// 							{ 
// 								break;
// 							}
// 						}
// 					}
// 				}				
// 				
// 				if ( iPos > -1 && (strcmp("",sInputCmdArray[iPos].ReqField.OrderSysID) !=0))
// 				{					
// 					strcpy(pOrderAction.OrderSysID,sInputCmdArray[iPos].ReqField.OrderSysID);
// 					ShowMsg("%s,行权撤单,UserID[%s],BrokerID[%s],InvestorID[%s],ExchangeID[%s],报单号[%s],本地撤单号[%s]",
// 						sInputCmd->sCmdNo,
// 						pOrderAction.UserID,
// 						pOrderAction.BrokerID,
// 						pOrderAction.InvestorID,
// 						pOrderAction.ExchangeID,
// 						pOrderAction.OrderSysID,
// 						pOrderAction.UserOrderActionLocalID);	
// 					iRet = pProcessor->m_pFfexFtdcUserApi->ReqExecOrderAction(&pOrderAction,pProcessor->m_nRequestID++);
// 					if(iRet!=0)
// 						break;					
// 					pProcessor->WaitAction(10);
// 					ShowMsg("\n");
// 				}
// 				else
// 				{
// 					ShowMsg("%s,行权撤单失败,未找到报单\n",sInputCmd->sCmdNo);
// 					sInputCmd->pRspInfo.ErrorID = 100;
// 					strcpy(sInputCmd->pRspInfo.ErrorMsg,"行权撤单失败");
// 				}
// 				break;
// 			}
// 		case QRYEXECORDER:	
// 			CQdpFtdcQryExecOrderField QryExecOrder;
// 			memset(&QryExecOrder, 0, sizeof(CQdpFtdcQryExecOrderField));
// 			strcpy(QryExecOrder.BrokerID,sInputCmd->ReqField.BrokerID);
// 			strcpy(QryExecOrder.InvestorID,sInputCmd->ReqField.InvestorID);
// 			strcpy(QryExecOrder.ExchangeID,sInputCmd->ReqField.ExchangeID);
// 			strcpy(QryExecOrder.InstrumentID,sInputCmd->ReqField.InstrumentID);
// 			ShowMsg("%s,行权查询请求,BrokerID[%s],InvestorID[%s],ExchangeID[%s]InstrumentID[%s]",
// 				sInputCmd->sCmdNo,sInputCmd->ReqField.BrokerID,sInputCmd->ReqField.InvestorID,sInputCmd->ReqField.ExchangeID,sInputCmd->ReqField.InstrumentID);
// 			iRet = pProcessor->m_pFfexFtdcUserApi->ReqQryExecOrder(&QryExecOrder,pProcessor->m_nRequestID++);
// 			if(iRet!=0)
// 				break;
// 			pProcessor->WaitAction(5);				
// 				break;
		default:
				ShowMsg("=>%s,未知的指令类型 [%s]!\n",sInputCmd->sCmdNo,sInputCmd->sCmdType);
				sInputCmd->pRspInfo.ErrorID = -1;
				strcpy(sInputCmd->pRspInfo.ErrorMsg,"未知的指令类型");
				break;
	}

	//返回执行结果
	return iRet;
}
