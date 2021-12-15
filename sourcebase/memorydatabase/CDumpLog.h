/////////////////////////////////////////////////////////////////////////
///@system ��������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CDumpLog.h
///@brief��������CDumpLog
///@history 
///20121227	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CDUMPLOG_H
#define CDUMPLOG_H

#include "CMemoryDB.h"

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusDumpTrigger�ǲ�������ͬ��״̬��ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusDumpTrigger: public CDataSyncStatusActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CDataSyncStatusDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CDataSyncStatusDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pDataSyncStatus	Ҫ�����DataSyncStatus
	virtual void beforeAdd(CWriteableDataSyncStatus *pDataSyncStatus);
	
	///����ǰ����	
	///@param	pDataSyncStatus	��ˢ�µ�CDataSyncStatus
	///@param	pNewDataSyncStatus	�µ�ֵ
	virtual void beforeUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus);
	
	///ɾ��ǰ����
	///@param	pDataSyncStatus	Ҫɾ����CDataSyncStatus
	virtual void beforeRemove(CDataSyncStatus *pDataSyncStatus);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusDumpTrigger�ǲ���QDP״̬��ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusDumpTrigger: public CSystemStatusActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CSystemStatusDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CSystemStatusDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pSystemStatus	Ҫ�����SystemStatus
	virtual void beforeAdd(CWriteableSystemStatus *pSystemStatus);
	
	///����ǰ����	
	///@param	pSystemStatus	��ˢ�µ�CSystemStatus
	///@param	pNewSystemStatus	�µ�ֵ
	virtual void beforeUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus);
	
	///ɾ��ǰ����
	///@param	pSystemStatus	Ҫɾ����CSystemStatus
	virtual void beforeRemove(CSystemStatus *pSystemStatus);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///COrderActionDumpTrigger�ǲ�����������ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionDumpTrigger: public COrderActionActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	COrderActionDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~COrderActionDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pOrderAction	Ҫ�����OrderAction
	virtual void beforeAdd(CWriteableOrderAction *pOrderAction);
	
	///����ǰ����	
	///@param	pOrderAction	��ˢ�µ�COrderAction
	///@param	pNewOrderAction	�µ�ֵ
	virtual void beforeUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction);
	
	///ɾ��ǰ����
	///@param	pOrderAction	Ҫɾ����COrderAction
	virtual void beforeRemove(COrderAction *pOrderAction);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///COrderDumpTrigger�ǲ���ί�б�ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDumpTrigger: public COrderActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	COrderDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~COrderDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pOrder	Ҫ�����Order
	virtual void beforeAdd(CWriteableOrder *pOrder);
	
	///����ǰ����	
	///@param	pOrder	��ˢ�µ�COrder
	///@param	pNewOrder	�µ�ֵ
	virtual void beforeUpdate(COrder *pOrder, CWriteableOrder *pNewOrder);
	
	///ɾ��ǰ����
	///@param	pOrder	Ҫɾ����COrder
	virtual void beforeRemove(COrder *pOrder);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CTradeDumpTrigger�ǲ����ɽ���ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeDumpTrigger: public CTradeActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CTradeDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CTradeDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pTrade	Ҫ�����Trade
	virtual void beforeAdd(CWriteableTrade *pTrade);
	
	///����ǰ����	
	///@param	pTrade	��ˢ�µ�CTrade
	///@param	pNewTrade	�µ�ֵ
	virtual void beforeUpdate(CTrade *pTrade, CWriteableTrade *pNewTrade);
	
	///ɾ��ǰ����
	///@param	pTrade	Ҫɾ����CTrade
	virtual void beforeRemove(CTrade *pTrade);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderDumpTrigger�ǲ���Ԥί�б�ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderDumpTrigger: public CPreOrderActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CPreOrderDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CPreOrderDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pPreOrder	Ҫ�����PreOrder
	virtual void beforeAdd(CWriteablePreOrder *pPreOrder);
	
	///����ǰ����	
	///@param	pPreOrder	��ˢ�µ�CPreOrder
	///@param	pNewPreOrder	�µ�ֵ
	virtual void beforeUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder);
	
	///ɾ��ǰ����
	///@param	pPreOrder	Ҫɾ����CPreOrder
	virtual void beforeRemove(CPreOrder *pPreOrder);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderDumpTrigger�ǲ�������Ԥί�б�ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderDumpTrigger: public CIndexPreOrderActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CIndexPreOrderDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CIndexPreOrderDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pIndexPreOrder	Ҫ�����IndexPreOrder
	virtual void beforeAdd(CWriteableIndexPreOrder *pIndexPreOrder);
	
	///����ǰ����	
	///@param	pIndexPreOrder	��ˢ�µ�CIndexPreOrder
	///@param	pNewIndexPreOrder	�µ�ֵ
	virtual void beforeUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder);
	
	///ɾ��ǰ����
	///@param	pIndexPreOrder	Ҫɾ����CIndexPreOrder
	virtual void beforeRemove(CIndexPreOrder *pIndexPreOrder);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionDumpTrigger�ǲ����ֱֲ�ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionDumpTrigger: public CInvestorPositionActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CInvestorPositionDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CInvestorPositionDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pInvestorPosition	Ҫ�����InvestorPosition
	virtual void beforeAdd(CWriteableInvestorPosition *pInvestorPosition);
	
	///����ǰ����	
	///@param	pInvestorPosition	��ˢ�µ�CInvestorPosition
	///@param	pNewInvestorPosition	�µ�ֵ
	virtual void beforeUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition);
	
	///ɾ��ǰ����
	///@param	pInvestorPosition	Ҫɾ����CInvestorPosition
	virtual void beforeRemove(CInvestorPosition *pInvestorPosition);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDumpTrigger�ǲ����˻�ʵʱ�ʽ��ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDumpTrigger: public CInvestorAccountActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CInvestorAccountDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CInvestorAccountDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pInvestorAccount	Ҫ�����InvestorAccount
	virtual void beforeAdd(CWriteableInvestorAccount *pInvestorAccount);
	
	///����ǰ����	
	///@param	pInvestorAccount	��ˢ�µ�CInvestorAccount
	///@param	pNewInvestorAccount	�µ�ֵ
	virtual void beforeUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount);
	
	///ɾ��ǰ����
	///@param	pInvestorAccount	Ҫɾ����CInvestorAccount
	virtual void beforeRemove(CInvestorAccount *pInvestorAccount);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositDumpTrigger�ǲ����˻�ʵʱ������ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositDumpTrigger: public CInvestorAccountDepositActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CInvestorAccountDepositDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CInvestorAccountDepositDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pInvestorAccountDeposit	Ҫ�����InvestorAccountDeposit
	virtual void beforeAdd(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit);
	
	///����ǰ����	
	///@param	pInvestorAccountDeposit	��ˢ�µ�CInvestorAccountDeposit
	///@param	pNewInvestorAccountDeposit	�µ�ֵ
	virtual void beforeUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit);
	
	///ɾ��ǰ����
	///@param	pInvestorAccountDeposit	Ҫɾ����CInvestorAccountDeposit
	virtual void beforeRemove(CInvestorAccountDeposit *pInvestorAccountDeposit);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CExchangeDumpTrigger�ǲ�����������ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeDumpTrigger: public CExchangeActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CExchangeDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CExchangeDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pExchange	Ҫ�����Exchange
	virtual void beforeAdd(CWriteableExchange *pExchange);
	
	///����ǰ����	
	///@param	pExchange	��ˢ�µ�CExchange
	///@param	pNewExchange	�µ�ֵ
	virtual void beforeUpdate(CExchange *pExchange, CWriteableExchange *pNewExchange);
	
	///ɾ��ǰ����
	///@param	pExchange	Ҫɾ����CExchange
	virtual void beforeRemove(CExchange *pExchange);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CSeatDumpTrigger�ǲ����µ�ϯλ��ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatDumpTrigger: public CSeatActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CSeatDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CSeatDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pSeat	Ҫ�����Seat
	virtual void beforeAdd(CWriteableSeat *pSeat);
	
	///����ǰ����	
	///@param	pSeat	��ˢ�µ�CSeat
	///@param	pNewSeat	�µ�ֵ
	virtual void beforeUpdate(CSeat *pSeat, CWriteableSeat *pNewSeat);
	
	///ɾ��ǰ����
	///@param	pSeat	Ҫɾ����CSeat
	virtual void beforeRemove(CSeat *pSeat);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentDumpTrigger�ǲ����ڻ���Լ��ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentDumpTrigger: public CInstrumentActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CInstrumentDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CInstrumentDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pInstrument	Ҫ�����Instrument
	virtual void beforeAdd(CWriteableInstrument *pInstrument);
	
	///����ǰ����	
	///@param	pInstrument	��ˢ�µ�CInstrument
	///@param	pNewInstrument	�µ�ֵ
	virtual void beforeUpdate(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument);
	
	///ɾ��ǰ����
	///@param	pInstrument	Ҫɾ����CInstrument
	virtual void beforeRemove(CInstrument *pInstrument);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailDumpTrigger�ǲ����ڻ���Ϻ�Լ��ϸ��ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailDumpTrigger: public CCmbInstrumentDetailActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CCmbInstrumentDetailDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CCmbInstrumentDetailDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pCmbInstrumentDetail	Ҫ�����CmbInstrumentDetail
	virtual void beforeAdd(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail);
	
	///����ǰ����	
	///@param	pCmbInstrumentDetail	��ˢ�µ�CCmbInstrumentDetail
	///@param	pNewCmbInstrumentDetail	�µ�ֵ
	virtual void beforeUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail);
	
	///ɾ��ǰ����
	///@param	pCmbInstrumentDetail	Ҫɾ����CCmbInstrumentDetail
	virtual void beforeRemove(CCmbInstrumentDetail *pCmbInstrumentDetail);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDDumpTrigger�ǲ����������ͻ������ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDDumpTrigger: public CClientTradingIDActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CClientTradingIDDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CClientTradingIDDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pClientTradingID	Ҫ�����ClientTradingID
	virtual void beforeAdd(CWriteableClientTradingID *pClientTradingID);
	
	///����ǰ����	
	///@param	pClientTradingID	��ˢ�µ�CClientTradingID
	///@param	pNewClientTradingID	�µ�ֵ
	virtual void beforeUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID);
	
	///ɾ��ǰ����
	///@param	pClientTradingID	Ҫɾ����CClientTradingID
	virtual void beforeRemove(CClientTradingID *pClientTradingID);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorDumpTrigger�ǲ���Ͷ������Ϣ��ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorDumpTrigger: public CInvestorActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CInvestorDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CInvestorDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pInvestor	Ҫ�����Investor
	virtual void beforeAdd(CWriteableInvestor *pInvestor);
	
	///����ǰ����	
	///@param	pInvestor	��ˢ�µ�CInvestor
	///@param	pNewInvestor	�µ�ֵ
	virtual void beforeUpdate(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor);
	
	///ɾ��ǰ����
	///@param	pInvestor	Ҫɾ����CInvestor
	virtual void beforeRemove(CInvestor *pInvestor);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginDumpTrigger�ǲ����ͻ��ڻ���֤���ʱ�ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginDumpTrigger: public CInvestorMarginActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CInvestorMarginDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CInvestorMarginDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pInvestorMargin	Ҫ�����InvestorMargin
	virtual void beforeAdd(CWriteableInvestorMargin *pInvestorMargin);
	
	///����ǰ����	
	///@param	pInvestorMargin	��ˢ�µ�CInvestorMargin
	///@param	pNewInvestorMargin	�µ�ֵ
	virtual void beforeUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin);
	
	///ɾ��ǰ����
	///@param	pInvestorMargin	Ҫɾ����CInvestorMargin
	virtual void beforeRemove(CInvestorMargin *pInvestorMargin);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeDumpTrigger�ǲ����ͻ��������ʱ�ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeDumpTrigger: public CInvestorFeeActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CInvestorFeeDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CInvestorFeeDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pInvestorFee	Ҫ�����InvestorFee
	virtual void beforeAdd(CWriteableInvestorFee *pInvestorFee);
	
	///����ǰ����	
	///@param	pInvestorFee	��ˢ�µ�CInvestorFee
	///@param	pNewInvestorFee	�µ�ֵ
	virtual void beforeUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee);
	
	///ɾ��ǰ����
	///@param	pInvestorFee	Ҫɾ����CInvestorFee
	virtual void beforeRemove(CInvestorFee *pInvestorFee);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CUserDumpTrigger�ǲ����û���ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserDumpTrigger: public CUserActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CUserDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CUserDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pUser	Ҫ�����User
	virtual void beforeAdd(CWriteableUser *pUser);
	
	///����ǰ����	
	///@param	pUser	��ˢ�µ�CUser
	///@param	pNewUser	�µ�ֵ
	virtual void beforeUpdate(CUser *pUser, CWriteableUser *pNewUser);
	
	///ɾ��ǰ����
	///@param	pUser	Ҫɾ����CUser
	virtual void beforeRemove(CUser *pUser);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorDumpTrigger�ǲ����û�Ͷ���߹�ϵ��ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorDumpTrigger: public CUserInvestorActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CUserInvestorDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CUserInvestorDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pUserInvestor	Ҫ�����UserInvestor
	virtual void beforeAdd(CWriteableUserInvestor *pUserInvestor);
	
	///����ǰ����	
	///@param	pUserInvestor	��ˢ�µ�CUserInvestor
	///@param	pNewUserInvestor	�µ�ֵ
	virtual void beforeUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor);
	
	///ɾ��ǰ����
	///@param	pUserInvestor	Ҫɾ����CUserInvestor
	virtual void beforeRemove(CUserInvestor *pUserInvestor);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedDumpTrigger�ǲ�������ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedDumpTrigger: public COrderInsertFailedActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	COrderInsertFailedDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~COrderInsertFailedDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pOrderInsertFailed	Ҫ�����OrderInsertFailed
	virtual void beforeAdd(CWriteableOrderInsertFailed *pOrderInsertFailed);
	
	///����ǰ����	
	///@param	pOrderInsertFailed	��ˢ�µ�COrderInsertFailed
	///@param	pNewOrderInsertFailed	�µ�ֵ
	virtual void beforeUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed);
	
	///ɾ��ǰ����
	///@param	pOrderInsertFailed	Ҫɾ����COrderInsertFailed
	virtual void beforeRemove(COrderInsertFailed *pOrderInsertFailed);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightDumpTrigger�ǲ����û�����Ȩ�ޱ�ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightDumpTrigger: public CUserTradingRightActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CUserTradingRightDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CUserTradingRightDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pUserTradingRight	Ҫ�����UserTradingRight
	virtual void beforeAdd(CWriteableUserTradingRight *pUserTradingRight);
	
	///����ǰ����	
	///@param	pUserTradingRight	��ˢ�µ�CUserTradingRight
	///@param	pNewUserTradingRight	�µ�ֵ
	virtual void beforeUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight);
	
	///ɾ��ǰ����
	///@param	pUserTradingRight	Ҫɾ����CUserTradingRight
	virtual void beforeRemove(CUserTradingRight *pUserTradingRight);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeDumpTrigger�ǲ�����ǰʱ��ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeDumpTrigger: public CCurrentTimeActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CCurrentTimeDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CCurrentTimeDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pCurrentTime	Ҫ�����CurrentTime
	virtual void beforeAdd(CWriteableCurrentTime *pCurrentTime);
	
	///����ǰ����	
	///@param	pCurrentTime	��ˢ�µ�CCurrentTime
	///@param	pNewCurrentTime	�µ�ֵ
	virtual void beforeUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime);
	
	///ɾ��ǰ����
	///@param	pCurrentTime	Ҫɾ����CCurrentTime
	virtual void beforeRemove(CCurrentTime *pCurrentTime);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionDumpTrigger�ǲ�������Ա���߻Ựʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionDumpTrigger: public CUserSessionActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CUserSessionDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CUserSessionDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pUserSession	Ҫ�����UserSession
	virtual void beforeAdd(CWriteableUserSession *pUserSession);
	
	///����ǰ����	
	///@param	pUserSession	��ˢ�µ�CUserSession
	///@param	pNewUserSession	�µ�ֵ
	virtual void beforeUpdate(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession);
	
	///ɾ��ǰ����
	///@param	pUserSession	Ҫɾ����CUserSession
	virtual void beforeRemove(CUserSession *pUserSession);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDDumpTrigger�ǲ�����󱾵ر�����ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDDumpTrigger: public CMaxLocalIDActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CMaxLocalIDDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CMaxLocalIDDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pMaxLocalID	Ҫ�����MaxLocalID
	virtual void beforeAdd(CWriteableMaxLocalID *pMaxLocalID);
	
	///����ǰ����	
	///@param	pMaxLocalID	��ˢ�µ�CMaxLocalID
	///@param	pNewMaxLocalID	�µ�ֵ
	virtual void beforeUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID);
	
	///ɾ��ǰ����
	///@param	pMaxLocalID	Ҫɾ����CMaxLocalID
	virtual void beforeRemove(CMaxLocalID *pMaxLocalID);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDDumpTrigger�ǲ����û����ر�����ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDDumpTrigger: public CBrkUserIDLocalIDActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CBrkUserIDLocalIDDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CBrkUserIDLocalIDDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pBrkUserIDLocalID	Ҫ�����BrkUserIDLocalID
	virtual void beforeAdd(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID);
	
	///����ǰ����	
	///@param	pBrkUserIDLocalID	��ˢ�µ�CBrkUserIDLocalID
	///@param	pNewBrkUserIDLocalID	�µ�ֵ
	virtual void beforeUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID);
	
	///ɾ��ǰ����
	///@param	pBrkUserIDLocalID	Ҫɾ����CBrkUserIDLocalID
	virtual void beforeRemove(CBrkUserIDLocalID *pBrkUserIDLocalID);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionDumpTrigger�ǲ����ͻ���Լ��ֱֲ�ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionDumpTrigger: public CPartClientInsGroupPositionActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CPartClientInsGroupPositionDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CPartClientInsGroupPositionDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pPartClientInsGroupPosition	Ҫ�����PartClientInsGroupPosition
	virtual void beforeAdd(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition);
	
	///����ǰ����	
	///@param	pPartClientInsGroupPosition	��ˢ�µ�CPartClientInsGroupPosition
	///@param	pNewPartClientInsGroupPosition	�µ�ֵ
	virtual void beforeUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition);
	
	///ɾ��ǰ����
	///@param	pPartClientInsGroupPosition	Ҫɾ����CPartClientInsGroupPosition
	virtual void beforeRemove(CPartClientInsGroupPosition *pPartClientInsGroupPosition);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeDumpTrigger�ǲ������ױ�����ϱ�֤������ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeDumpTrigger: public CClientMarginCombTypeActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CClientMarginCombTypeDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CClientMarginCombTypeDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pClientMarginCombType	Ҫ�����ClientMarginCombType
	virtual void beforeAdd(CWriteableClientMarginCombType *pClientMarginCombType);
	
	///����ǰ����	
	///@param	pClientMarginCombType	��ˢ�µ�CClientMarginCombType
	///@param	pNewClientMarginCombType	�µ�ֵ
	virtual void beforeUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType);
	
	///ɾ��ǰ����
	///@param	pClientMarginCombType	Ҫɾ����CClientMarginCombType
	virtual void beforeRemove(CClientMarginCombType *pClientMarginCombType);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupDumpTrigger�ǲ�����Լ�ͺ�Լ���ϵʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupDumpTrigger: public CInstrumentGroupActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CInstrumentGroupDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CInstrumentGroupDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pInstrumentGroup	Ҫ�����InstrumentGroup
	virtual void beforeAdd(CWriteableInstrumentGroup *pInstrumentGroup);
	
	///����ǰ����	
	///@param	pInstrumentGroup	��ˢ�µ�CInstrumentGroup
	///@param	pNewInstrumentGroup	�µ�ֵ
	virtual void beforeUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup);
	
	///ɾ��ǰ����
	///@param	pInstrumentGroup	Ҫɾ����CInstrumentGroup
	virtual void beforeRemove(CInstrumentGroup *pInstrumentGroup);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateDumpTrigger�ǲ����������ӷ��ʱ�ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateDumpTrigger: public CSGEDeferRateActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CSGEDeferRateDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CSGEDeferRateDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pSGEDeferRate	Ҫ�����SGEDeferRate
	virtual void beforeAdd(CWriteableSGEDeferRate *pSGEDeferRate);
	
	///����ǰ����	
	///@param	pSGEDeferRate	��ˢ�µ�CSGEDeferRate
	///@param	pNewSGEDeferRate	�µ�ֵ
	virtual void beforeUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate);
	
	///ɾ��ǰ����
	///@param	pSGEDeferRate	Ҫɾ����CSGEDeferRate
	virtual void beforeRemove(CSGEDeferRate *pSGEDeferRate);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightDumpTrigger�ǲ���Ͷ���߽���Ȩ�ޱ�ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightDumpTrigger: public CInvestorTradingRightActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CInvestorTradingRightDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CInvestorTradingRightDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pInvestorTradingRight	Ҫ�����InvestorTradingRight
	virtual void beforeAdd(CWriteableInvestorTradingRight *pInvestorTradingRight);
	
	///����ǰ����	
	///@param	pInvestorTradingRight	��ˢ�µ�CInvestorTradingRight
	///@param	pNewInvestorTradingRight	�µ�ֵ
	virtual void beforeUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight);
	
	///ɾ��ǰ����
	///@param	pInvestorTradingRight	Ҫɾ����CInvestorTradingRight
	virtual void beforeRemove(CInvestorTradingRight *pInvestorTradingRight);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CUserIPDumpTrigger�ǲ�������ԱIP��ַʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPDumpTrigger: public CUserIPActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CUserIPDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CUserIPDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pUserIP	Ҫ�����UserIP
	virtual void beforeAdd(CWriteableUserIP *pUserIP);
	
	///����ǰ����	
	///@param	pUserIP	��ˢ�µ�CUserIP
	///@param	pNewUserIP	�µ�ֵ
	virtual void beforeUpdate(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP);
	
	///ɾ��ǰ����
	///@param	pUserIP	Ҫɾ����CUserIP
	virtual void beforeRemove(CUserIP *pUserIP);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeDumpTrigger�ǲ����ͻ���Ȩ�������ʱ�ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeDumpTrigger: public CInvestorOptionFeeActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CInvestorOptionFeeDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CInvestorOptionFeeDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pInvestorOptionFee	Ҫ�����InvestorOptionFee
	virtual void beforeAdd(CWriteableInvestorOptionFee *pInvestorOptionFee);
	
	///����ǰ����	
	///@param	pInvestorOptionFee	��ˢ�µ�CInvestorOptionFee
	///@param	pNewInvestorOptionFee	�µ�ֵ
	virtual void beforeUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee);
	
	///ɾ��ǰ����
	///@param	pInvestorOptionFee	Ҫɾ����CInvestorOptionFee
	virtual void beforeRemove(CInvestorOptionFee *pInvestorOptionFee);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataDumpTrigger�ǲ���ʵʱ�����ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataDumpTrigger: public CMarketDataActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CMarketDataDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CMarketDataDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pMarketData	Ҫ�����MarketData
	virtual void beforeAdd(CWriteableMarketData *pMarketData);
	
	///����ǰ����	
	///@param	pMarketData	��ˢ�µ�CMarketData
	///@param	pNewMarketData	�µ�ֵ
	virtual void beforeUpdate(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData);
	
	///ɾ��ǰ����
	///@param	pMarketData	Ҫɾ����CMarketData
	virtual void beforeRemove(CMarketData *pMarketData);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayDumpTrigger�ǲ���ί���ӳٱ�ʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayDumpTrigger: public COrderDelayActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	COrderDelayDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~COrderDelayDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pOrderDelay	Ҫ�����OrderDelay
	virtual void beforeAdd(CWriteableOrderDelay *pOrderDelay);
	
	///����ǰ����	
	///@param	pOrderDelay	��ˢ�µ�COrderDelay
	///@param	pNewOrderDelay	�µ�ֵ
	virtual void beforeUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay);
	
	///ɾ��ǰ����
	///@param	pOrderDelay	Ҫɾ����COrderDelay
	virtual void beforeRemove(COrderDelay *pOrderDelay);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoDumpTrigger�ǲ���QDPϵͳ��Ϣʱ�Ĵ��������ڱ仯ʱ�������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoDumpTrigger: public CSystemInfoActionTrigger
{
public:
	///���췽��
	///@param	output	����õ��ļ�
	///@param	flag	��������ľ������CREATE_ACTION��DELETE_ACTION��UPDATE_ACTION�Ļ�
	CSystemInfoDumpTrigger(FILE *output, int flag=CREATE_ACTION|DELETE_ACTION|UPDATE_ACTION);
	
	///��������
	virtual ~CSystemInfoDumpTrigger(void);

	virtual void output(CLogger *pLogger,int indent=0);

	///����ǰ����
	///@param	pSystemInfo	Ҫ�����SystemInfo
	virtual void beforeAdd(CWriteableSystemInfo *pSystemInfo);
	
	///����ǰ����	
	///@param	pSystemInfo	��ˢ�µ�CSystemInfo
	///@param	pNewSystemInfo	�µ�ֵ
	virtual void beforeUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo);
	
	///ɾ��ǰ����
	///@param	pSystemInfo	Ҫɾ����CSystemInfo
	virtual void beforeRemove(CSystemInfo *pSystemInfo);
	
private:
	FILE *m_output;
	int m_flag;
};

/////////////////////////////////////////////////////////////////////////
///CDumpLog��һ�������е��޸���Dump��ʽ����Ľ�����������ʵ��
///@author	xuzh
///@version	1.0,20041001
/////////////////////////////////////////////////////////////////////////
class CDumpLog
{
public:
	///���췽��������һ�������
	///@param	pDB	Ҫ������ڴ����ݿ�
	///@param	pConfig	������Ϣ
	CDumpLog(CMemoryDB *pDB, CConfig *pConfig);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CDumpLog(void);

	///����dump
	void start(void);
	
	///ֹͣdump
	void stop(void);
	
	///�Ƿ��Ѿ�����
	///@return	1��ʾ�Ѿ�������0��ʾû������
	int isStarted(void);
	
	///�����Ϣ
	///@param	format	��Ϣ��ʽ������fprintf��Ҫ��
	///@param	...	��Ϣ����ϸ����
	void dumpMsg(char *format,...);

private:
	///����ļ�
	FILE *m_DumpOutput;
	
	///�ڴ����ݿ�
	CMemoryDB *m_DB;
	
	///�Ƿ��Ѿ�����
	int m_Started;
	
	CDataSyncStatusDumpTrigger *m_DataSyncStatusTrigger;
	CSystemStatusDumpTrigger *m_SystemStatusTrigger;
	COrderActionDumpTrigger *m_OrderActionTrigger;
	COrderDumpTrigger *m_OrderTrigger;
	CTradeDumpTrigger *m_TradeTrigger;
	CPreOrderDumpTrigger *m_PreOrderTrigger;
	CIndexPreOrderDumpTrigger *m_IndexPreOrderTrigger;
	CInvestorPositionDumpTrigger *m_InvestorPositionTrigger;
	CInvestorAccountDumpTrigger *m_InvestorAccountTrigger;
	CInvestorAccountDepositDumpTrigger *m_InvestorAccountDepositTrigger;
	CExchangeDumpTrigger *m_ExchangeTrigger;
	CSeatDumpTrigger *m_SeatTrigger;
	CInstrumentDumpTrigger *m_InstrumentTrigger;
	CCmbInstrumentDetailDumpTrigger *m_CmbInstrumentDetailTrigger;
	CClientTradingIDDumpTrigger *m_ClientTradingIDTrigger;
	CInvestorDumpTrigger *m_InvestorTrigger;
	CInvestorMarginDumpTrigger *m_InvestorMarginTrigger;
	CInvestorFeeDumpTrigger *m_InvestorFeeTrigger;
	CUserDumpTrigger *m_UserTrigger;
	CUserInvestorDumpTrigger *m_UserInvestorTrigger;
	COrderInsertFailedDumpTrigger *m_OrderInsertFailedTrigger;
	CUserTradingRightDumpTrigger *m_UserTradingRightTrigger;
	CCurrentTimeDumpTrigger *m_CurrentTimeTrigger;
	CUserSessionDumpTrigger *m_UserSessionTrigger;
	CMaxLocalIDDumpTrigger *m_MaxLocalIDTrigger;
	CBrkUserIDLocalIDDumpTrigger *m_BrkUserIDLocalIDTrigger;
	CPartClientInsGroupPositionDumpTrigger *m_PartClientInsGroupPositionTrigger;
	CClientMarginCombTypeDumpTrigger *m_ClientMarginCombTypeTrigger;
	CInstrumentGroupDumpTrigger *m_InstrumentGroupTrigger;
	CSGEDeferRateDumpTrigger *m_SGEDeferRateTrigger;
	CInvestorTradingRightDumpTrigger *m_InvestorTradingRightTrigger;
	CUserIPDumpTrigger *m_UserIPTrigger;
	CInvestorOptionFeeDumpTrigger *m_InvestorOptionFeeTrigger;
	CMarketDataDumpTrigger *m_MarketDataTrigger;
	COrderDelayDumpTrigger *m_OrderDelayTrigger;
	CSystemInfoDumpTrigger *m_SystemInfoTrigger;
};

#endif
