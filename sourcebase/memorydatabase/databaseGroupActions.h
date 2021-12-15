/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseGroupActions.h
///@brief定义了若干个内存数据库的群组操作
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef DATABASEGROUPACTIONS_H
#define DATABASEGROUPACTIONS_H

#include "BaseDataStruct.h"
#include "databaseFactories.h"


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TDataSyncStatusActionFunc)(CDataSyncStatus * pDataSyncStatus, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TDataSyncStatusUpdateFunc)(CWriteableDataSyncStatus * pDataSyncStatus, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TDataSyncStatusSelectFunc)(CDataSyncStatus * pDataSyncStatus,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CDataSyncStatusIterator *pIterator, TDataSyncStatusActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CDataSyncStatusIterator *pIterator, TDataSyncStatusUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CDataSyncStatusIterator *pIterator, TDataSyncStatusSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TSystemStatusActionFunc)(CSystemStatus * pSystemStatus, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TSystemStatusUpdateFunc)(CWriteableSystemStatus * pSystemStatus, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TSystemStatusSelectFunc)(CSystemStatus * pSystemStatus,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CSystemStatusIterator *pIterator, TSystemStatusActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CSystemStatusIterator *pIterator, TSystemStatusUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CSystemStatusIterator *pIterator, TSystemStatusSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TOrderActionActionFunc)(COrderAction * pOrderAction, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TOrderActionUpdateFunc)(CWriteableOrderAction * pOrderAction, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TOrderActionSelectFunc)(COrderAction * pOrderAction,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(COrderActionIterator *pIterator, TOrderActionActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(COrderActionIterator *pIterator, TOrderActionUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(COrderActionIterator *pIterator, TOrderActionSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TOrderActionFunc)(COrder * pOrder, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TOrderUpdateFunc)(CWriteableOrder * pOrder, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TOrderSelectFunc)(COrder * pOrder,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(COrderIterator *pIterator, TOrderActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(COrderIterator *pIterator, TOrderUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(COrderIterator *pIterator, TOrderSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TTradeActionFunc)(CTrade * pTrade, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TTradeUpdateFunc)(CWriteableTrade * pTrade, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TTradeSelectFunc)(CTrade * pTrade,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CTradeIterator *pIterator, TTradeActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CTradeIterator *pIterator, TTradeUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CTradeIterator *pIterator, TTradeSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TPreOrderActionFunc)(CPreOrder * pPreOrder, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TPreOrderUpdateFunc)(CWriteablePreOrder * pPreOrder, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TPreOrderSelectFunc)(CPreOrder * pPreOrder,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CPreOrderIterator *pIterator, TPreOrderActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CPreOrderIterator *pIterator, TPreOrderUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CPreOrderIterator *pIterator, TPreOrderSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TIndexPreOrderActionFunc)(CIndexPreOrder * pIndexPreOrder, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TIndexPreOrderUpdateFunc)(CWriteableIndexPreOrder * pIndexPreOrder, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TIndexPreOrderSelectFunc)(CIndexPreOrder * pIndexPreOrder,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CIndexPreOrderIterator *pIterator, TIndexPreOrderActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CIndexPreOrderIterator *pIterator, TIndexPreOrderUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CIndexPreOrderIterator *pIterator, TIndexPreOrderSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorPositionActionFunc)(CInvestorPosition * pInvestorPosition, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorPositionUpdateFunc)(CWriteableInvestorPosition * pInvestorPosition, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorPositionSelectFunc)(CInvestorPosition * pInvestorPosition,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CInvestorPositionIterator *pIterator, TInvestorPositionActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CInvestorPositionIterator *pIterator, TInvestorPositionUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CInvestorPositionIterator *pIterator, TInvestorPositionSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorAccountActionFunc)(CInvestorAccount * pInvestorAccount, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorAccountUpdateFunc)(CWriteableInvestorAccount * pInvestorAccount, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorAccountSelectFunc)(CInvestorAccount * pInvestorAccount,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CInvestorAccountIterator *pIterator, TInvestorAccountActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CInvestorAccountIterator *pIterator, TInvestorAccountUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CInvestorAccountIterator *pIterator, TInvestorAccountSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorAccountDepositActionFunc)(CInvestorAccountDeposit * pInvestorAccountDeposit, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorAccountDepositUpdateFunc)(CWriteableInvestorAccountDeposit * pInvestorAccountDeposit, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorAccountDepositSelectFunc)(CInvestorAccountDeposit * pInvestorAccountDeposit,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CInvestorAccountDepositIterator *pIterator, TInvestorAccountDepositActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CInvestorAccountDepositIterator *pIterator, TInvestorAccountDepositUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CInvestorAccountDepositIterator *pIterator, TInvestorAccountDepositSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TExchangeActionFunc)(CExchange * pExchange, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TExchangeUpdateFunc)(CWriteableExchange * pExchange, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TExchangeSelectFunc)(CExchange * pExchange,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CExchangeIterator *pIterator, TExchangeActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CExchangeIterator *pIterator, TExchangeUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CExchangeIterator *pIterator, TExchangeSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TSeatActionFunc)(CSeat * pSeat, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TSeatUpdateFunc)(CWriteableSeat * pSeat, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TSeatSelectFunc)(CSeat * pSeat,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CSeatIterator *pIterator, TSeatActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CSeatIterator *pIterator, TSeatUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CSeatIterator *pIterator, TSeatSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInstrumentActionFunc)(CInstrument * pInstrument, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInstrumentUpdateFunc)(CWriteableInstrument * pInstrument, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInstrumentSelectFunc)(CInstrument * pInstrument,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CInstrumentIterator *pIterator, TInstrumentActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CInstrumentIterator *pIterator, TInstrumentUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CInstrumentIterator *pIterator, TInstrumentSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TCmbInstrumentDetailActionFunc)(CCmbInstrumentDetail * pCmbInstrumentDetail, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TCmbInstrumentDetailUpdateFunc)(CWriteableCmbInstrumentDetail * pCmbInstrumentDetail, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TCmbInstrumentDetailSelectFunc)(CCmbInstrumentDetail * pCmbInstrumentDetail,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CCmbInstrumentDetailIterator *pIterator, TCmbInstrumentDetailActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CCmbInstrumentDetailIterator *pIterator, TCmbInstrumentDetailUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CCmbInstrumentDetailIterator *pIterator, TCmbInstrumentDetailSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TClientTradingIDActionFunc)(CClientTradingID * pClientTradingID, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TClientTradingIDUpdateFunc)(CWriteableClientTradingID * pClientTradingID, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TClientTradingIDSelectFunc)(CClientTradingID * pClientTradingID,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CClientTradingIDIterator *pIterator, TClientTradingIDActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CClientTradingIDIterator *pIterator, TClientTradingIDUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CClientTradingIDIterator *pIterator, TClientTradingIDSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorActionFunc)(CInvestor * pInvestor, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorUpdateFunc)(CWriteableInvestor * pInvestor, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorSelectFunc)(CInvestor * pInvestor,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CInvestorIterator *pIterator, TInvestorActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CInvestorIterator *pIterator, TInvestorUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CInvestorIterator *pIterator, TInvestorSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorMarginActionFunc)(CInvestorMargin * pInvestorMargin, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorMarginUpdateFunc)(CWriteableInvestorMargin * pInvestorMargin, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorMarginSelectFunc)(CInvestorMargin * pInvestorMargin,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CInvestorMarginIterator *pIterator, TInvestorMarginActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CInvestorMarginIterator *pIterator, TInvestorMarginUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CInvestorMarginIterator *pIterator, TInvestorMarginSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorFeeActionFunc)(CInvestorFee * pInvestorFee, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorFeeUpdateFunc)(CWriteableInvestorFee * pInvestorFee, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorFeeSelectFunc)(CInvestorFee * pInvestorFee,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CInvestorFeeIterator *pIterator, TInvestorFeeActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CInvestorFeeIterator *pIterator, TInvestorFeeUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CInvestorFeeIterator *pIterator, TInvestorFeeSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TUserActionFunc)(CUser * pUser, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TUserUpdateFunc)(CWriteableUser * pUser, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TUserSelectFunc)(CUser * pUser,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CUserIterator *pIterator, TUserActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CUserIterator *pIterator, TUserUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CUserIterator *pIterator, TUserSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TUserInvestorActionFunc)(CUserInvestor * pUserInvestor, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TUserInvestorUpdateFunc)(CWriteableUserInvestor * pUserInvestor, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TUserInvestorSelectFunc)(CUserInvestor * pUserInvestor,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CUserInvestorIterator *pIterator, TUserInvestorActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CUserInvestorIterator *pIterator, TUserInvestorUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CUserInvestorIterator *pIterator, TUserInvestorSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TOrderInsertFailedActionFunc)(COrderInsertFailed * pOrderInsertFailed, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TOrderInsertFailedUpdateFunc)(CWriteableOrderInsertFailed * pOrderInsertFailed, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TOrderInsertFailedSelectFunc)(COrderInsertFailed * pOrderInsertFailed,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(COrderInsertFailedIterator *pIterator, TOrderInsertFailedActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(COrderInsertFailedIterator *pIterator, TOrderInsertFailedUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(COrderInsertFailedIterator *pIterator, TOrderInsertFailedSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TUserTradingRightActionFunc)(CUserTradingRight * pUserTradingRight, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TUserTradingRightUpdateFunc)(CWriteableUserTradingRight * pUserTradingRight, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TUserTradingRightSelectFunc)(CUserTradingRight * pUserTradingRight,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CUserTradingRightIterator *pIterator, TUserTradingRightActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CUserTradingRightIterator *pIterator, TUserTradingRightUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CUserTradingRightIterator *pIterator, TUserTradingRightSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TCurrentTimeActionFunc)(CCurrentTime * pCurrentTime, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TCurrentTimeUpdateFunc)(CWriteableCurrentTime * pCurrentTime, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TCurrentTimeSelectFunc)(CCurrentTime * pCurrentTime,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CCurrentTimeIterator *pIterator, TCurrentTimeActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CCurrentTimeIterator *pIterator, TCurrentTimeUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CCurrentTimeIterator *pIterator, TCurrentTimeSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TUserSessionActionFunc)(CUserSession * pUserSession, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TUserSessionUpdateFunc)(CWriteableUserSession * pUserSession, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TUserSessionSelectFunc)(CUserSession * pUserSession,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CUserSessionIterator *pIterator, TUserSessionActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CUserSessionIterator *pIterator, TUserSessionUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CUserSessionIterator *pIterator, TUserSessionSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TMaxLocalIDActionFunc)(CMaxLocalID * pMaxLocalID, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TMaxLocalIDUpdateFunc)(CWriteableMaxLocalID * pMaxLocalID, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TMaxLocalIDSelectFunc)(CMaxLocalID * pMaxLocalID,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CMaxLocalIDIterator *pIterator, TMaxLocalIDActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CMaxLocalIDIterator *pIterator, TMaxLocalIDUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CMaxLocalIDIterator *pIterator, TMaxLocalIDSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TBrkUserIDLocalIDActionFunc)(CBrkUserIDLocalID * pBrkUserIDLocalID, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TBrkUserIDLocalIDUpdateFunc)(CWriteableBrkUserIDLocalID * pBrkUserIDLocalID, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TBrkUserIDLocalIDSelectFunc)(CBrkUserIDLocalID * pBrkUserIDLocalID,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CBrkUserIDLocalIDIterator *pIterator, TBrkUserIDLocalIDActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CBrkUserIDLocalIDIterator *pIterator, TBrkUserIDLocalIDUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CBrkUserIDLocalIDIterator *pIterator, TBrkUserIDLocalIDSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TPartClientInsGroupPositionActionFunc)(CPartClientInsGroupPosition * pPartClientInsGroupPosition, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TPartClientInsGroupPositionUpdateFunc)(CWriteablePartClientInsGroupPosition * pPartClientInsGroupPosition, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TPartClientInsGroupPositionSelectFunc)(CPartClientInsGroupPosition * pPartClientInsGroupPosition,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CPartClientInsGroupPositionIterator *pIterator, TPartClientInsGroupPositionActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CPartClientInsGroupPositionIterator *pIterator, TPartClientInsGroupPositionUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CPartClientInsGroupPositionIterator *pIterator, TPartClientInsGroupPositionSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TClientMarginCombTypeActionFunc)(CClientMarginCombType * pClientMarginCombType, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TClientMarginCombTypeUpdateFunc)(CWriteableClientMarginCombType * pClientMarginCombType, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TClientMarginCombTypeSelectFunc)(CClientMarginCombType * pClientMarginCombType,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CClientMarginCombTypeIterator *pIterator, TClientMarginCombTypeActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CClientMarginCombTypeIterator *pIterator, TClientMarginCombTypeUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CClientMarginCombTypeIterator *pIterator, TClientMarginCombTypeSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInstrumentGroupActionFunc)(CInstrumentGroup * pInstrumentGroup, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInstrumentGroupUpdateFunc)(CWriteableInstrumentGroup * pInstrumentGroup, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInstrumentGroupSelectFunc)(CInstrumentGroup * pInstrumentGroup,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CInstrumentGroupIterator *pIterator, TInstrumentGroupActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CInstrumentGroupIterator *pIterator, TInstrumentGroupUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CInstrumentGroupIterator *pIterator, TInstrumentGroupSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TSGEDeferRateActionFunc)(CSGEDeferRate * pSGEDeferRate, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TSGEDeferRateUpdateFunc)(CWriteableSGEDeferRate * pSGEDeferRate, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TSGEDeferRateSelectFunc)(CSGEDeferRate * pSGEDeferRate,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CSGEDeferRateIterator *pIterator, TSGEDeferRateActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CSGEDeferRateIterator *pIterator, TSGEDeferRateUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CSGEDeferRateIterator *pIterator, TSGEDeferRateSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorTradingRightActionFunc)(CInvestorTradingRight * pInvestorTradingRight, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorTradingRightUpdateFunc)(CWriteableInvestorTradingRight * pInvestorTradingRight, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorTradingRightSelectFunc)(CInvestorTradingRight * pInvestorTradingRight,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CInvestorTradingRightIterator *pIterator, TInvestorTradingRightActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CInvestorTradingRightIterator *pIterator, TInvestorTradingRightUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CInvestorTradingRightIterator *pIterator, TInvestorTradingRightSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TUserIPActionFunc)(CUserIP * pUserIP, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TUserIPUpdateFunc)(CWriteableUserIP * pUserIP, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TUserIPSelectFunc)(CUserIP * pUserIP,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CUserIPIterator *pIterator, TUserIPActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CUserIPIterator *pIterator, TUserIPUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CUserIPIterator *pIterator, TUserIPSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorOptionFeeActionFunc)(CInvestorOptionFee * pInvestorOptionFee, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorOptionFeeUpdateFunc)(CWriteableInvestorOptionFee * pInvestorOptionFee, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TInvestorOptionFeeSelectFunc)(CInvestorOptionFee * pInvestorOptionFee,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CInvestorOptionFeeIterator *pIterator, TInvestorOptionFeeActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CInvestorOptionFeeIterator *pIterator, TInvestorOptionFeeUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CInvestorOptionFeeIterator *pIterator, TInvestorOptionFeeSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TMarketDataActionFunc)(CMarketData * pMarketData, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TMarketDataUpdateFunc)(CWriteableMarketData * pMarketData, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TMarketDataSelectFunc)(CMarketData * pMarketData,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CMarketDataIterator *pIterator, TMarketDataActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CMarketDataIterator *pIterator, TMarketDataUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CMarketDataIterator *pIterator, TMarketDataSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TOrderDelayActionFunc)(COrderDelay * pOrderDelay, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TOrderDelayUpdateFunc)(CWriteableOrderDelay * pOrderDelay, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TOrderDelaySelectFunc)(COrderDelay * pOrderDelay,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(COrderDelayIterator *pIterator, TOrderDelayActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(COrderDelayIterator *pIterator, TOrderDelayUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(COrderDelayIterator *pIterator, TOrderDelaySelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);


///操作函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TSystemInfoActionFunc)(CSystemInfo * pSystemInfo, CTransaction * pTransaction,
	void * parameter);

///更新函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TSystemInfoUpdateFunc)(CWriteableSystemInfo * pSystemInfo, CTransaction * pTransaction,
	void * parameter, bool * pUpdateIndex);

///选择函数类型定义，返回1表示需要继续操作，0表示需要结束操作
typedef int (* TSystemInfoSelectFunc)(CSystemInfo * pSystemInfo,CTransaction * pTransaction, 
	void * parameter,int *pSelected);

///对一个枚举器的所有对象进行某项操作
///@param	pIterator	进行操作的枚举器
///@param	actionFunc	实际操作的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用actionFunc
void groupAction(CSystemInfoIterator *pIterator, TSystemInfoActionFunc actionFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行更新操作
///@param	pIterator	进行操作的枚举器
///@param	updateFunc	实际进行更新的函数
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用updateFunc
void groupUpdate(CSystemInfoIterator *pIterator, TSystemInfoUpdateFunc updateFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

///对一个枚举器的所有对象进行删除操作
///@param	pIterator	进行操作的枚举器
///@param	selectFunc	实际需要删除的判断函数，NULL表示需要全部删除
///@param	pTransaction	操作属于的事务，NULL表示不使用事务
///@param	parameter	传递的参数，将代入每次叫用selectFunc
void groupDelete(CSystemInfoIterator *pIterator, TSystemInfoSelectFunc selectFunc,
	CTransaction *pTransaction=NULL, void *parameter=NULL);

#endif
