1. tload.prj �ǽ�userapi���ɵ�tload�еĹ����ļ�
2. tloadx.prj ��userapi��ʹ�ö�̬����÷�ʽ�Ĺ����ļ�
3.�ֶ�˵����
sCmdNo,ָ����,ָ������,�����̱��,���������,Ͷ���߱��,�����û�����,��Լ����,�û����ر������,��������,��������,��ƽ��־,Ͷ���ױ���־,�۸�,����,��Ч������,GTD����,�ɽ�������,��С�ɽ���,ֹ���,ǿƽԭ��,�Զ������־,ҵ��Ԫ,�ظ�����
sCmdNo,CmdType,BrokerID,ExchangeID,OrderSysID,InvestorID,UserID,InstrumentID,UserOrderLocalID,OrderPriceType,Direction,OffsetFlag,HedgeFlag,LimitPrice,Volume,TimeCondition,GTDDate,VolumeCondition,MinVolume,StopPrice,ForceCloseReason,IsAutoSuspend,BusinessUnit,iRepeatNum

4.֧��ָ������:���������֣�Ҳ������Сд��Ҳ�����Ǵ�д

enum choice	 
{
	0:LOGIN,					//	��¼
	1:ORDER,					//	ί��
	2:CANCEL,					//	����
	3:CANCELALL,				//	��ȫ��ί��
	4:SLEEP,					//	��ʱ
	5:QRYMONEY,				//	�ʽ��ѯ
	6:RESETUSERPASS,				//	���õ�ǰ�û�����
	7:QRYORDER,				//	��ѯί��
	8:QRYTRADE,				//	�ɽ���ѯ
	9:QRYMARKET,				//	�����ѯ
	10:QRYCLIENTPOSI,				//	�ͻ��ֲֲ�ѯ
	11:QRYINSTRUMENT,				//	��Լ��ѯ
	12:MONEYINOUT,				//	�����
	13:EXTCMD,					// 	�ⲿָ�����
	14:LOGOUT
};

5.����Ӧ��ʹ�õ��ֶΣ�
LOGIN:
	ShowMsg("%s,��¼,ϯλ[%s],����[%s]",sInputCmd->sCmdNo,sInputCmd->ReqField.UserID,sInputCmd->ReqField.InstrumentID);
ORDER:
	ShowMsg("%s,ί��,UserID[%s],BrokerID[%s],InvestorID[%s],InstrumentID[%s],Direction[%s],LimitPrice[%d],LimitPrice[%.3f],UserOrderLocalID[%s]", sInputCmd->sCmdNo, sInputCmd->ReqField.UserID, sInputCmd->ReqField.BrokerID, sInputCmd->ReqField.InvestorID, sInputCmd->ReqField.InstrumentID, GetBsFlag(sInputCmd->ReqField.Direction), sInputCmd->ReqField.Volume, sInputCmd->ReqField.LimitPrice, pOrder.UserOrderLocalID);
CANCEL:
	strcpy(pOrderAction.UserID,sInputCmd->ReqField.UserID);
	strcpy(pOrderAction.BrokerID,sInputCmd->ReqField.BrokerID);
	sInputCmd->ReqField.UserOrderLocalID:��дҪ������sCmdNo
SLEEP:
	ShowMsg("%s,ϵͳ��ͣ,%d ��",sInputCmd->sCmdNo,sInputCmd->ReqField.BrokerID);
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
	�޲���
QRYCLIENTPOSI��
	strcpy(pQryInvestorPosition.BrokerID,sInputCmd->ReqField.BrokerID);
	strcpy(pQryInvestorPosition.InvestorID,sInputCmd->ReqField.InvestorID);
	strcpy(pQryInvestorPosition.InstrumentID,sInputCmd->ReqField.InstrumentID);
	strcpy(pQryInvestorPosition.ExchangeID,sInputCmd->ReqField.ExchangeID);
QRYINSTRUMENT:
	strcpy(pQryInstrument.InstrumentID,sInputCmd->ReqField.InstrumentID);
	strcpy(pQryInstrument.ExchangeID,sInputCmd->ReqField.ExchangeID);
	strcpy(pQryInstrument.InstrumentID,sInputCmd->ReqField.InstrumentID);

