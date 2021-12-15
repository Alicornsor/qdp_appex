1. tload.prj 是将userapi集成到tload中的工程文件
2. tloadx.prj 和userapi是使用动态库调用方式的工程文件
3.字段说明：
sCmdNo,指令编号,指令类型,经纪商编号,交易所编号,投资者编号,交易用户代码,合约代码,用户本地报单编号,报单类型,买卖方向,开平标志,投机套保标志,价格,数量,有效期类型,GTD日期,成交量类型,最小成交量,止损价,强平原因,自动挂起标志,业务单元,重复次数
sCmdNo,CmdType,BrokerID,ExchangeID,OrderSysID,InvestorID,UserID,InstrumentID,UserOrderLocalID,OrderPriceType,Direction,OffsetFlag,HedgeFlag,LimitPrice,Volume,TimeCondition,GTDDate,VolumeCondition,MinVolume,StopPrice,ForceCloseReason,IsAutoSuspend,BusinessUnit,iRepeatNum

4.支持指令类型:可以是数字，也可以是小写，也可以是大写

enum choice	 
{
	0:LOGIN,					//	登录
	1:ORDER,					//	委托
	2:CANCEL,					//	撤单
	3:CANCELALL,				//	撤全部委托
	4:SLEEP,					//	延时
	5:QRYMONEY,				//	资金查询
	6:RESETUSERPASS,				//	重置当前用户密码
	7:QRYORDER,				//	查询委托
	8:QRYTRADE,				//	成交查询
	9:QRYMARKET,				//	行情查询
	10:QRYCLIENTPOSI,				//	客户持仓查询
	11:QRYINSTRUMENT,				//	合约查询
	12:MONEYINOUT,				//	出入金
	13:EXTCMD,					// 	外部指令调用
	14:LOGOUT
};

5.各个应用使用的字段：
LOGIN:
	ShowMsg("%s,登录,席位[%s],密码[%s]",sInputCmd->sCmdNo,sInputCmd->ReqField.UserID,sInputCmd->ReqField.InstrumentID);
ORDER:
	ShowMsg("%s,委托,UserID[%s],BrokerID[%s],InvestorID[%s],InstrumentID[%s],Direction[%s],LimitPrice[%d],LimitPrice[%.3f],UserOrderLocalID[%s]", sInputCmd->sCmdNo, sInputCmd->ReqField.UserID, sInputCmd->ReqField.BrokerID, sInputCmd->ReqField.InvestorID, sInputCmd->ReqField.InstrumentID, GetBsFlag(sInputCmd->ReqField.Direction), sInputCmd->ReqField.Volume, sInputCmd->ReqField.LimitPrice, pOrder.UserOrderLocalID);
CANCEL:
	strcpy(pOrderAction.UserID,sInputCmd->ReqField.UserID);
	strcpy(pOrderAction.BrokerID,sInputCmd->ReqField.BrokerID);
	sInputCmd->ReqField.UserOrderLocalID:填写要撤单的sCmdNo
SLEEP:
	ShowMsg("%s,系统暂停,%d 秒",sInputCmd->sCmdNo,sInputCmd->ReqField.BrokerID);
CANCELALL:
	strcpy(ReqField.InstrumentID,sInputCmd->ReqField.InstrumentID);
	strcpy(ReqField.BrokerID,sInputCmd->ReqField.BrokerID);	
	strcpy(ReqField.UserID ,sInputCmd->ReqField.UserID);
QRYMONEY:
	strcpy(pQryInvestorAccount.BrokerID,sInputCmd->ReqField.BrokerID);
	strcpy(pQryInvestorAccount.UserID,sInputCmd->ReqField.UserID);
	strcpy(pQryInvestorAccount.InvestorID,sInputCmd->ReqField.InvestorID);
RESETUSERPASS:
	strcpy(pUserPasswordUpdate.BrokerID,sInputCmd->ReqField.BrokerID);
	strcpy(pUserPasswordUpdate.UserID,sInputCmd->ReqField.UserID);
	strcpy(pUserPasswordUpdate.NewPassword,sInputCmd->ReqField.InstrumentID);
QRYORDER:
	strcpy(ReqField.BrokerID,sInputCmd->ReqField.BrokerID);	
	strcpy(ReqField.ExchangeID,sInputCmd->ReqField.ExchangeID);
	strcpy(ReqField.InvestorID,sInputCmd->ReqField.InvestorID);
	strcpy(ReqField.InstrumentID,sInputCmd->ReqField.InstrumentID);
	strcpy(ReqField.UserID ,sInputCmd->ReqField.UserID);
QRYTRADE:
	strcpy(ReqField.BrokerID,sInputCmd->ReqField.BrokerID);
	strcpy(ReqField.InvestorID,sInputCmd->ReqField.InvestorID);
	strcpy(ReqField.InstrumentID,sInputCmd->ReqField.InstrumentID);
	strcpy(ReqField.UserID,sInputCmd->ReqField.UserID);
LOGOUT:
	无参数
QRYCLIENTPOSI：
	strcpy(pQryInvestorPosition.BrokerID,sInputCmd->ReqField.BrokerID);
	strcpy(pQryInvestorPosition.InvestorID,sInputCmd->ReqField.InvestorID);
	strcpy(pQryInvestorPosition.InstrumentID,sInputCmd->ReqField.InstrumentID);
	strcpy(pQryInvestorPosition.ExchangeID,sInputCmd->ReqField.ExchangeID);
QRYINSTRUMENT:
	strcpy(pQryInstrument.InstrumentID,sInputCmd->ReqField.InstrumentID);
	strcpy(pQryInstrument.ExchangeID,sInputCmd->ReqField.ExchangeID);
	strcpy(pQryInstrument.InstrumentID,sInputCmd->ReqField.InstrumentID);

