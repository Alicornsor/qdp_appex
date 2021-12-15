/////////////////////////////////////////////////////////////////////////
///@system ִ������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file databaseGroupActions.h
///@brief���������ɸ��ڴ����ݿ��Ⱥ�����
///@history 
///20121227	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef DATABASEGROUPACTIONS_H
#define DATABASEGROUPACTIONS_H

#include "BaseDataStruct.h"
#include "databaseFactories.h"


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TDataSyncStatusActionFunc)(CDataSyncStatus * pDataSyncStatus, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TDataSyncStatusUpdateFunc)(CWriteableDataSyncStatus * pDataSyncStatus, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TDataSyncStatusSelectFunc)(CDataSyncStatus * pDataSyncStatus,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CDataSyncStatusIterator *pIterator, TDataSyncStatusActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CDataSyncStatusIterator *pIterator, TDataSyncStatusUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CDataSyncStatusIterator *pIterator, TDataSyncStatusSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TSystemStatusActionFunc)(CSystemStatus * pSystemStatus, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TSystemStatusUpdateFunc)(CWriteableSystemStatus * pSystemStatus, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TSystemStatusSelectFunc)(CSystemStatus * pSystemStatus,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CSystemStatusIterator *pIterator, TSystemStatusActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CSystemStatusIterator *pIterator, TSystemStatusUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CSystemStatusIterator *pIterator, TSystemStatusSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TOrderActionActionFunc)(COrderAction * pOrderAction, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TOrderActionUpdateFunc)(CWriteableOrderAction * pOrderAction, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TOrderActionSelectFunc)(COrderAction * pOrderAction,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(COrderActionIterator *pIterator, TOrderActionActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(COrderActionIterator *pIterator, TOrderActionUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(COrderActionIterator *pIterator, TOrderActionSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TOrderActionFunc)(COrder * pOrder, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TOrderUpdateFunc)(CWriteableOrder * pOrder, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TOrderSelectFunc)(COrder * pOrder,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(COrderIterator *pIterator, TOrderActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(COrderIterator *pIterator, TOrderUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(COrderIterator *pIterator, TOrderSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TTradeActionFunc)(CTrade * pTrade, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TTradeUpdateFunc)(CWriteableTrade * pTrade, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TTradeSelectFunc)(CTrade * pTrade,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CTradeIterator *pIterator, TTradeActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CTradeIterator *pIterator, TTradeUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CTradeIterator *pIterator, TTradeSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TPreOrderActionFunc)(CPreOrder * pPreOrder, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TPreOrderUpdateFunc)(CWriteablePreOrder * pPreOrder, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TPreOrderSelectFunc)(CPreOrder * pPreOrder,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CPreOrderIterator *pIterator, TPreOrderActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CPreOrderIterator *pIterator, TPreOrderUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CPreOrderIterator *pIterator, TPreOrderSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TIndexPreOrderActionFunc)(CIndexPreOrder * pIndexPreOrder, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TIndexPreOrderUpdateFunc)(CWriteableIndexPreOrder * pIndexPreOrder, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TIndexPreOrderSelectFunc)(CIndexPreOrder * pIndexPreOrder,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CIndexPreOrderIterator *pIterator, TIndexPreOrderActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CIndexPreOrderIterator *pIterator, TIndexPreOrderUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CIndexPreOrderIterator *pIterator, TIndexPreOrderSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorPositionActionFunc)(CInvestorPosition * pInvestorPosition, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorPositionUpdateFunc)(CWriteableInvestorPosition * pInvestorPosition, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorPositionSelectFunc)(CInvestorPosition * pInvestorPosition,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CInvestorPositionIterator *pIterator, TInvestorPositionActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CInvestorPositionIterator *pIterator, TInvestorPositionUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CInvestorPositionIterator *pIterator, TInvestorPositionSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorAccountActionFunc)(CInvestorAccount * pInvestorAccount, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorAccountUpdateFunc)(CWriteableInvestorAccount * pInvestorAccount, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorAccountSelectFunc)(CInvestorAccount * pInvestorAccount,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CInvestorAccountIterator *pIterator, TInvestorAccountActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CInvestorAccountIterator *pIterator, TInvestorAccountUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CInvestorAccountIterator *pIterator, TInvestorAccountSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorAccountDepositActionFunc)(CInvestorAccountDeposit * pInvestorAccountDeposit, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorAccountDepositUpdateFunc)(CWriteableInvestorAccountDeposit * pInvestorAccountDeposit, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorAccountDepositSelectFunc)(CInvestorAccountDeposit * pInvestorAccountDeposit,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CInvestorAccountDepositIterator *pIterator, TInvestorAccountDepositActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CInvestorAccountDepositIterator *pIterator, TInvestorAccountDepositUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CInvestorAccountDepositIterator *pIterator, TInvestorAccountDepositSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TExchangeActionFunc)(CExchange * pExchange, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TExchangeUpdateFunc)(CWriteableExchange * pExchange, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TExchangeSelectFunc)(CExchange * pExchange,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CExchangeIterator *pIterator, TExchangeActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CExchangeIterator *pIterator, TExchangeUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CExchangeIterator *pIterator, TExchangeSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TSeatActionFunc)(CSeat * pSeat, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TSeatUpdateFunc)(CWriteableSeat * pSeat, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TSeatSelectFunc)(CSeat * pSeat,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CSeatIterator *pIterator, TSeatActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CSeatIterator *pIterator, TSeatUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CSeatIterator *pIterator, TSeatSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInstrumentActionFunc)(CInstrument * pInstrument, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInstrumentUpdateFunc)(CWriteableInstrument * pInstrument, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInstrumentSelectFunc)(CInstrument * pInstrument,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CInstrumentIterator *pIterator, TInstrumentActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CInstrumentIterator *pIterator, TInstrumentUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CInstrumentIterator *pIterator, TInstrumentSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TCmbInstrumentDetailActionFunc)(CCmbInstrumentDetail * pCmbInstrumentDetail, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TCmbInstrumentDetailUpdateFunc)(CWriteableCmbInstrumentDetail * pCmbInstrumentDetail, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TCmbInstrumentDetailSelectFunc)(CCmbInstrumentDetail * pCmbInstrumentDetail,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CCmbInstrumentDetailIterator *pIterator, TCmbInstrumentDetailActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CCmbInstrumentDetailIterator *pIterator, TCmbInstrumentDetailUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CCmbInstrumentDetailIterator *pIterator, TCmbInstrumentDetailSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TClientTradingIDActionFunc)(CClientTradingID * pClientTradingID, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TClientTradingIDUpdateFunc)(CWriteableClientTradingID * pClientTradingID, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TClientTradingIDSelectFunc)(CClientTradingID * pClientTradingID,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CClientTradingIDIterator *pIterator, TClientTradingIDActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CClientTradingIDIterator *pIterator, TClientTradingIDUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CClientTradingIDIterator *pIterator, TClientTradingIDSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorActionFunc)(CInvestor * pInvestor, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorUpdateFunc)(CWriteableInvestor * pInvestor, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorSelectFunc)(CInvestor * pInvestor,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CInvestorIterator *pIterator, TInvestorActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CInvestorIterator *pIterator, TInvestorUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CInvestorIterator *pIterator, TInvestorSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorMarginActionFunc)(CInvestorMargin * pInvestorMargin, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorMarginUpdateFunc)(CWriteableInvestorMargin * pInvestorMargin, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorMarginSelectFunc)(CInvestorMargin * pInvestorMargin,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CInvestorMarginIterator *pIterator, TInvestorMarginActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CInvestorMarginIterator *pIterator, TInvestorMarginUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CInvestorMarginIterator *pIterator, TInvestorMarginSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorFeeActionFunc)(CInvestorFee * pInvestorFee, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorFeeUpdateFunc)(CWriteableInvestorFee * pInvestorFee, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorFeeSelectFunc)(CInvestorFee * pInvestorFee,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CInvestorFeeIterator *pIterator, TInvestorFeeActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CInvestorFeeIterator *pIterator, TInvestorFeeUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CInvestorFeeIterator *pIterator, TInvestorFeeSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TUserActionFunc)(CUser * pUser, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TUserUpdateFunc)(CWriteableUser * pUser, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TUserSelectFunc)(CUser * pUser,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CUserIterator *pIterator, TUserActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CUserIterator *pIterator, TUserUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CUserIterator *pIterator, TUserSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TUserInvestorActionFunc)(CUserInvestor * pUserInvestor, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TUserInvestorUpdateFunc)(CWriteableUserInvestor * pUserInvestor, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TUserInvestorSelectFunc)(CUserInvestor * pUserInvestor,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CUserInvestorIterator *pIterator, TUserInvestorActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CUserInvestorIterator *pIterator, TUserInvestorUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CUserInvestorIterator *pIterator, TUserInvestorSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TOrderInsertFailedActionFunc)(COrderInsertFailed * pOrderInsertFailed, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TOrderInsertFailedUpdateFunc)(CWriteableOrderInsertFailed * pOrderInsertFailed, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TOrderInsertFailedSelectFunc)(COrderInsertFailed * pOrderInsertFailed,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(COrderInsertFailedIterator *pIterator, TOrderInsertFailedActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(COrderInsertFailedIterator *pIterator, TOrderInsertFailedUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(COrderInsertFailedIterator *pIterator, TOrderInsertFailedSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TUserTradingRightActionFunc)(CUserTradingRight * pUserTradingRight, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TUserTradingRightUpdateFunc)(CWriteableUserTradingRight * pUserTradingRight, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TUserTradingRightSelectFunc)(CUserTradingRight * pUserTradingRight,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CUserTradingRightIterator *pIterator, TUserTradingRightActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CUserTradingRightIterator *pIterator, TUserTradingRightUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CUserTradingRightIterator *pIterator, TUserTradingRightSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TCurrentTimeActionFunc)(CCurrentTime * pCurrentTime, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TCurrentTimeUpdateFunc)(CWriteableCurrentTime * pCurrentTime, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TCurrentTimeSelectFunc)(CCurrentTime * pCurrentTime,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CCurrentTimeIterator *pIterator, TCurrentTimeActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CCurrentTimeIterator *pIterator, TCurrentTimeUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CCurrentTimeIterator *pIterator, TCurrentTimeSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TUserSessionActionFunc)(CUserSession * pUserSession, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TUserSessionUpdateFunc)(CWriteableUserSession * pUserSession, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TUserSessionSelectFunc)(CUserSession * pUserSession,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CUserSessionIterator *pIterator, TUserSessionActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CUserSessionIterator *pIterator, TUserSessionUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CUserSessionIterator *pIterator, TUserSessionSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TMaxLocalIDActionFunc)(CMaxLocalID * pMaxLocalID, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TMaxLocalIDUpdateFunc)(CWriteableMaxLocalID * pMaxLocalID, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TMaxLocalIDSelectFunc)(CMaxLocalID * pMaxLocalID,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CMaxLocalIDIterator *pIterator, TMaxLocalIDActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CMaxLocalIDIterator *pIterator, TMaxLocalIDUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CMaxLocalIDIterator *pIterator, TMaxLocalIDSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TBrkUserIDLocalIDActionFunc)(CBrkUserIDLocalID * pBrkUserIDLocalID, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TBrkUserIDLocalIDUpdateFunc)(CWriteableBrkUserIDLocalID * pBrkUserIDLocalID, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TBrkUserIDLocalIDSelectFunc)(CBrkUserIDLocalID * pBrkUserIDLocalID,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CBrkUserIDLocalIDIterator *pIterator, TBrkUserIDLocalIDActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CBrkUserIDLocalIDIterator *pIterator, TBrkUserIDLocalIDUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CBrkUserIDLocalIDIterator *pIterator, TBrkUserIDLocalIDSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TPartClientInsGroupPositionActionFunc)(CPartClientInsGroupPosition * pPartClientInsGroupPosition, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TPartClientInsGroupPositionUpdateFunc)(CWriteablePartClientInsGroupPosition * pPartClientInsGroupPosition, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TPartClientInsGroupPositionSelectFunc)(CPartClientInsGroupPosition * pPartClientInsGroupPosition,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CPartClientInsGroupPositionIterator *pIterator, TPartClientInsGroupPositionActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CPartClientInsGroupPositionIterator *pIterator, TPartClientInsGroupPositionUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CPartClientInsGroupPositionIterator *pIterator, TPartClientInsGroupPositionSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TClientMarginCombTypeActionFunc)(CClientMarginCombType * pClientMarginCombType, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TClientMarginCombTypeUpdateFunc)(CWriteableClientMarginCombType * pClientMarginCombType, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TClientMarginCombTypeSelectFunc)(CClientMarginCombType * pClientMarginCombType,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CClientMarginCombTypeIterator *pIterator, TClientMarginCombTypeActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CClientMarginCombTypeIterator *pIterator, TClientMarginCombTypeUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CClientMarginCombTypeIterator *pIterator, TClientMarginCombTypeSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInstrumentGroupActionFunc)(CInstrumentGroup * pInstrumentGroup, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInstrumentGroupUpdateFunc)(CWriteableInstrumentGroup * pInstrumentGroup, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInstrumentGroupSelectFunc)(CInstrumentGroup * pInstrumentGroup,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CInstrumentGroupIterator *pIterator, TInstrumentGroupActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CInstrumentGroupIterator *pIterator, TInstrumentGroupUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CInstrumentGroupIterator *pIterator, TInstrumentGroupSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TSGEDeferRateActionFunc)(CSGEDeferRate * pSGEDeferRate, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TSGEDeferRateUpdateFunc)(CWriteableSGEDeferRate * pSGEDeferRate, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TSGEDeferRateSelectFunc)(CSGEDeferRate * pSGEDeferRate,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CSGEDeferRateIterator *pIterator, TSGEDeferRateActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CSGEDeferRateIterator *pIterator, TSGEDeferRateUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CSGEDeferRateIterator *pIterator, TSGEDeferRateSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorTradingRightActionFunc)(CInvestorTradingRight * pInvestorTradingRight, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorTradingRightUpdateFunc)(CWriteableInvestorTradingRight * pInvestorTradingRight, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorTradingRightSelectFunc)(CInvestorTradingRight * pInvestorTradingRight,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CInvestorTradingRightIterator *pIterator, TInvestorTradingRightActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CInvestorTradingRightIterator *pIterator, TInvestorTradingRightUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CInvestorTradingRightIterator *pIterator, TInvestorTradingRightSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TUserIPActionFunc)(CUserIP * pUserIP, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TUserIPUpdateFunc)(CWriteableUserIP * pUserIP, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TUserIPSelectFunc)(CUserIP * pUserIP,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CUserIPIterator *pIterator, TUserIPActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CUserIPIterator *pIterator, TUserIPUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CUserIPIterator *pIterator, TUserIPSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorOptionFeeActionFunc)(CInvestorOptionFee * pInvestorOptionFee, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorOptionFeeUpdateFunc)(CWriteableInvestorOptionFee * pInvestorOptionFee, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TInvestorOptionFeeSelectFunc)(CInvestorOptionFee * pInvestorOptionFee,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CInvestorOptionFeeIterator *pIterator, TInvestorOptionFeeActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CInvestorOptionFeeIterator *pIterator, TInvestorOptionFeeUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CInvestorOptionFeeIterator *pIterator, TInvestorOptionFeeSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TMarketDataActionFunc)(CMarketData * pMarketData, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TMarketDataUpdateFunc)(CWriteableMarketData * pMarketData, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TMarketDataSelectFunc)(CMarketData * pMarketData,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CMarketDataIterator *pIterator, TMarketDataActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CMarketDataIterator *pIterator, TMarketDataUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CMarketDataIterator *pIterator, TMarketDataSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TOrderDelayActionFunc)(COrderDelay * pOrderDelay, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TOrderDelayUpdateFunc)(CWriteableOrderDelay * pOrderDelay, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TOrderDelaySelectFunc)(COrderDelay * pOrderDelay,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(COrderDelayIterator *pIterator, TOrderDelayActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(COrderDelayIterator *pIterator, TOrderDelayUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(COrderDelayIterator *pIterator, TOrderDelaySelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///�����������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TSystemInfoActionFunc)(CSystemInfo * pSystemInfo, CTransaction * pTransaction,
	void * parameter);

///���º������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TSystemInfoUpdateFunc)(CWriteableSystemInfo * pSystemInfo, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///ѡ�������Ͷ��壬����1��ʾ��Ҫ����������0��ʾ��Ҫ��������
typedef int (* TSystemInfoSelectFunc)(CSystemInfo * pSystemInfo,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///��һ��ö���������ж������ĳ�����
///@param	pIterator	���в�����ö����
///@param	actionFunc	ʵ�ʲ����ĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���actionFunc
void groupAction(CSystemInfoIterator *pIterator, TSystemInfoActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж�����и��²���
///@param	pIterator	���в�����ö����
///@param	updateFunc	ʵ�ʽ��и��µĺ���
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���updateFunc
void groupUpdate(CSystemInfoIterator *pIterator, TSystemInfoUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///��һ��ö���������ж������ɾ������
///@param	pIterator	���в�����ö����
///@param	selectFunc	ʵ����Ҫɾ�����жϺ�����NULL��ʾ��Ҫȫ��ɾ��
///@param	pTransaction	�������ڵ�����NULL��ʾ��ʹ������
///@param	parameter	���ݵĲ�����������ÿ�ν���selectFunc
void groupDelete(CSystemInfoIterator *pIterator, TSystemInfoSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

#endif
