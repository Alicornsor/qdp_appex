/////////////////////////////////////////////////////////////////////////
///@system ��������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CDumpTask.h
///@brief	��������CDumpTask�������
///@history 
///20091203	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CDUMPTASK_H
#define CDUMPTASK_H

#include "CLinkTask.h"
#include "databaseData.h"


/////////////////////////////////////////////////////////////////////////
///CDumpDataSyncStatusTask��һ������������ͬ��״̬���������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpDataSyncStatusTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpDataSyncStatusTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpDataSyncStatusTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CDataSyncStatusFactory *m_pFactory;
	FILE *m_output;
	CWriteableDataSyncStatus *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpSystemStatusTask��һ��������QDP״̬���������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpSystemStatusTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpSystemStatusTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpSystemStatusTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CSystemStatusFactory *m_pFactory;
	FILE *m_output;
	CWriteableSystemStatus *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpOrderActionTask��һ������������������������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpOrderActionTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpOrderActionTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpOrderActionTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	COrderActionFactory *m_pFactory;
	FILE *m_output;
	CWriteableOrderAction *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpOrderTask��һ��������ί�б��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpOrderTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpOrderTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpOrderTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	COrderFactory *m_pFactory;
	FILE *m_output;
	CWriteableOrder *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpTradeTask��һ���������ɽ����������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpTradeTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpTradeTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpTradeTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CTradeFactory *m_pFactory;
	FILE *m_output;
	CWriteableTrade *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpPreOrderTask��һ��������Ԥί�б��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpPreOrderTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpPreOrderTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpPreOrderTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CPreOrderFactory *m_pFactory;
	FILE *m_output;
	CWriteablePreOrder *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpIndexPreOrderTask��һ������������Ԥί�б��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpIndexPreOrderTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpIndexPreOrderTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpIndexPreOrderTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CIndexPreOrderFactory *m_pFactory;
	FILE *m_output;
	CWriteableIndexPreOrder *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorPositionTask��һ���������ֱֲ��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorPositionTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpInvestorPositionTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpInvestorPositionTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CInvestorPositionFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestorPosition *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorAccountTask��һ���������˻�ʵʱ�ʽ���������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorAccountTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpInvestorAccountTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpInvestorAccountTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CInvestorAccountFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestorAccount *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorAccountDepositTask��һ���������˻�ʵʱ�������������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorAccountDepositTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpInvestorAccountDepositTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpInvestorAccountDepositTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CInvestorAccountDepositFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestorAccountDeposit *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpExchangeTask��һ�����������������������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpExchangeTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpExchangeTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpExchangeTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CExchangeFactory *m_pFactory;
	FILE *m_output;
	CWriteableExchange *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpSeatTask��һ���������µ�ϯλ���������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpSeatTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpSeatTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpSeatTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CSeatFactory *m_pFactory;
	FILE *m_output;
	CWriteableSeat *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInstrumentTask��һ���������ڻ���Լ���������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInstrumentTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpInstrumentTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpInstrumentTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CInstrumentFactory *m_pFactory;
	FILE *m_output;
	CWriteableInstrument *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpCmbInstrumentDetailTask��һ���������ڻ���Ϻ�Լ��ϸ���������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpCmbInstrumentDetailTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpCmbInstrumentDetailTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpCmbInstrumentDetailTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CCmbInstrumentDetailFactory *m_pFactory;
	FILE *m_output;
	CWriteableCmbInstrumentDetail *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpClientTradingIDTask��һ���������������ͻ�������������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpClientTradingIDTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpClientTradingIDTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpClientTradingIDTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CClientTradingIDFactory *m_pFactory;
	FILE *m_output;
	CWriteableClientTradingID *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorTask��һ��������Ͷ������Ϣ���������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpInvestorTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpInvestorTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CInvestorFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestor *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorMarginTask��һ���������ͻ��ڻ���֤���ʱ��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorMarginTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpInvestorMarginTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpInvestorMarginTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CInvestorMarginFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestorMargin *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorFeeTask��һ���������ͻ��������ʱ��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorFeeTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpInvestorFeeTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpInvestorFeeTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CInvestorFeeFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestorFee *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpUserTask��һ���������û����������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpUserTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpUserTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpUserTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CUserFactory *m_pFactory;
	FILE *m_output;
	CWriteableUser *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpUserInvestorTask��һ���������û�Ͷ���߹�ϵ���������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpUserInvestorTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpUserInvestorTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpUserInvestorTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CUserInvestorFactory *m_pFactory;
	FILE *m_output;
	CWriteableUserInvestor *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpOrderInsertFailedTask��һ�������������������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpOrderInsertFailedTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpOrderInsertFailedTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpOrderInsertFailedTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	COrderInsertFailedFactory *m_pFactory;
	FILE *m_output;
	CWriteableOrderInsertFailed *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpUserTradingRightTask��һ���������û�����Ȩ�ޱ��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpUserTradingRightTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpUserTradingRightTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpUserTradingRightTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CUserTradingRightFactory *m_pFactory;
	FILE *m_output;
	CWriteableUserTradingRight *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpCurrentTimeTask��һ����������ǰʱ���������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpCurrentTimeTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpCurrentTimeTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpCurrentTimeTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CCurrentTimeFactory *m_pFactory;
	FILE *m_output;
	CWriteableCurrentTime *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpUserSessionTask��һ������������Ա���߻Ự��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpUserSessionTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpUserSessionTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpUserSessionTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CUserSessionFactory *m_pFactory;
	FILE *m_output;
	CWriteableUserSession *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpMaxLocalIDTask��һ����������󱾵ر����ŵ�������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpMaxLocalIDTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpMaxLocalIDTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpMaxLocalIDTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CMaxLocalIDFactory *m_pFactory;
	FILE *m_output;
	CWriteableMaxLocalID *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpBrkUserIDLocalIDTask��һ���������û����ر����ŵ�������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpBrkUserIDLocalIDTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpBrkUserIDLocalIDTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpBrkUserIDLocalIDTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CBrkUserIDLocalIDFactory *m_pFactory;
	FILE *m_output;
	CWriteableBrkUserIDLocalID *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpPartClientInsGroupPositionTask��һ���������ͻ���Լ��ֱֲ��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpPartClientInsGroupPositionTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpPartClientInsGroupPositionTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpPartClientInsGroupPositionTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CPartClientInsGroupPositionFactory *m_pFactory;
	FILE *m_output;
	CWriteablePartClientInsGroupPosition *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpClientMarginCombTypeTask��һ�����������ױ�����ϱ�֤�����͵�������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpClientMarginCombTypeTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpClientMarginCombTypeTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpClientMarginCombTypeTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CClientMarginCombTypeFactory *m_pFactory;
	FILE *m_output;
	CWriteableClientMarginCombType *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInstrumentGroupTask��һ����������Լ�ͺ�Լ���ϵ��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInstrumentGroupTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpInstrumentGroupTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpInstrumentGroupTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CInstrumentGroupFactory *m_pFactory;
	FILE *m_output;
	CWriteableInstrumentGroup *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpSGEDeferRateTask��һ���������������ӷ��ʱ��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpSGEDeferRateTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpSGEDeferRateTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpSGEDeferRateTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CSGEDeferRateFactory *m_pFactory;
	FILE *m_output;
	CWriteableSGEDeferRate *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorTradingRightTask��һ��������Ͷ���߽���Ȩ�ޱ��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorTradingRightTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpInvestorTradingRightTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpInvestorTradingRightTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CInvestorTradingRightFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestorTradingRight *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpUserIPTask��һ������������ԱIP��ַ��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpUserIPTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpUserIPTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpUserIPTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CUserIPFactory *m_pFactory;
	FILE *m_output;
	CWriteableUserIP *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpInvestorOptionFeeTask��һ���������ͻ���Ȩ�������ʱ��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpInvestorOptionFeeTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpInvestorOptionFeeTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpInvestorOptionFeeTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CInvestorOptionFeeFactory *m_pFactory;
	FILE *m_output;
	CWriteableInvestorOptionFee *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpMarketDataTask��һ��������ʵʱ������������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpMarketDataTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpMarketDataTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpMarketDataTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CMarketDataFactory *m_pFactory;
	FILE *m_output;
	CWriteableMarketData *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpOrderDelayTask��һ��������ί���ӳٱ��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpOrderDelayTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpOrderDelayTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpOrderDelayTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	COrderDelayFactory *m_pFactory;
	FILE *m_output;
	CWriteableOrderDelay *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpSystemInfoTask��һ��������QDPϵͳ��Ϣ��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpSystemInfoTask: public ITask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpSystemInfoTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	~CDumpSystemInfoTask(void);
	
	///����һ��
	///@param	pCost	���ر�����ɵ�Ȩֵ
	///@return	true��ʾ��Ҫ�������У�false��ʾ����Ҫ��������
	virtual bool step(int *pCost);

private:
	CSystemInfoFactory *m_pFactory;
	FILE *m_output;
	CWriteableSystemInfo *m_list;
	int m_size;
	int m_next;
	bool m_inited;
};


/////////////////////////////////////////////////////////////////////////
///CDumpTask��һ�������������ڴ����ݿ��������
///@author	xuzh
///@version	1.0,20091203
/////////////////////////////////////////////////////////////////////////
class CDumpTask: public CLinkTask
{
public:
	///���캯��
	///@param	pConfig	ʹ�õ������ļ�
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	CDumpTask(CConfig *pConfig,CMemoryDB *pDB);
	
	///��������
	virtual ~CDumpTask(void)
	{
	}
};


#endif
