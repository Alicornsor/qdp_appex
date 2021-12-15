/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseGroupActions.cpp
///@brief实现了若干个内存数据库的群组操作
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "databaseGroupActions.h"

void groupAction(CDataSyncStatusIterator *pIterator, TDataSyncStatusActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CDataSyncStatus *pDataSyncStatus;
	
	while ((pDataSyncStatus=pIterator->next())!=NULL)
	{
		if (!actionFunc(pDataSyncStatus, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CDataSyncStatusIterator *pIterator, TDataSyncStatusUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CDataSyncStatus *pDataSyncStatus;
	CWriteableDataSyncStatus theDataSyncStatus;
	bool updateIndex;
	CDataSyncStatusFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pDataSyncStatus=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pDataSyncStatus,&theDataSyncStatus);
		needContinue=updateFunc(&theDataSyncStatus, pTransaction, parameter, &updateIndex);
		pFactory->update(pDataSyncStatus,&theDataSyncStatus,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CDataSyncStatusIterator *pIterator, TDataSyncStatusSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CDataSyncStatus *pDataSyncStatus;
	int selected;
	CDataSyncStatusFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pDataSyncStatus=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pDataSyncStatus, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pDataSyncStatus,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CSystemStatusIterator *pIterator, TSystemStatusActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CSystemStatus *pSystemStatus;
	
	while ((pSystemStatus=pIterator->next())!=NULL)
	{
		if (!actionFunc(pSystemStatus, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CSystemStatusIterator *pIterator, TSystemStatusUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CSystemStatus *pSystemStatus;
	CWriteableSystemStatus theSystemStatus;
	bool updateIndex;
	CSystemStatusFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pSystemStatus=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pSystemStatus,&theSystemStatus);
		needContinue=updateFunc(&theSystemStatus, pTransaction, parameter, &updateIndex);
		pFactory->update(pSystemStatus,&theSystemStatus,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CSystemStatusIterator *pIterator, TSystemStatusSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CSystemStatus *pSystemStatus;
	int selected;
	CSystemStatusFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pSystemStatus=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pSystemStatus, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pSystemStatus,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(COrderActionIterator *pIterator, TOrderActionActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	COrderAction *pOrderAction;
	
	while ((pOrderAction=pIterator->next())!=NULL)
	{
		if (!actionFunc(pOrderAction, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(COrderActionIterator *pIterator, TOrderActionUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	COrderAction *pOrderAction;
	CWriteableOrderAction theOrderAction;
	bool updateIndex;
	COrderActionFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pOrderAction=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pOrderAction,&theOrderAction);
		needContinue=updateFunc(&theOrderAction, pTransaction, parameter, &updateIndex);
		pFactory->update(pOrderAction,&theOrderAction,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(COrderActionIterator *pIterator, TOrderActionSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	COrderAction *pOrderAction;
	int selected;
	COrderActionFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pOrderAction=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pOrderAction, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pOrderAction,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(COrderIterator *pIterator, TOrderActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	COrder *pOrder;
	
	while ((pOrder=pIterator->next())!=NULL)
	{
		if (!actionFunc(pOrder, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(COrderIterator *pIterator, TOrderUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	COrder *pOrder;
	CWriteableOrder theOrder;
	bool updateIndex;
	COrderFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pOrder=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pOrder,&theOrder);
		needContinue=updateFunc(&theOrder, pTransaction, parameter, &updateIndex);
		pFactory->update(pOrder,&theOrder,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(COrderIterator *pIterator, TOrderSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	COrder *pOrder;
	int selected;
	COrderFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pOrder=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pOrder, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pOrder,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CTradeIterator *pIterator, TTradeActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CTrade *pTrade;
	
	while ((pTrade=pIterator->next())!=NULL)
	{
		if (!actionFunc(pTrade, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CTradeIterator *pIterator, TTradeUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CTrade *pTrade;
	CWriteableTrade theTrade;
	bool updateIndex;
	CTradeFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pTrade=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pTrade,&theTrade);
		needContinue=updateFunc(&theTrade, pTransaction, parameter, &updateIndex);
		pFactory->update(pTrade,&theTrade,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CTradeIterator *pIterator, TTradeSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CTrade *pTrade;
	int selected;
	CTradeFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pTrade=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pTrade, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pTrade,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CPreOrderIterator *pIterator, TPreOrderActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CPreOrder *pPreOrder;
	
	while ((pPreOrder=pIterator->next())!=NULL)
	{
		if (!actionFunc(pPreOrder, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CPreOrderIterator *pIterator, TPreOrderUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CPreOrder *pPreOrder;
	CWriteablePreOrder thePreOrder;
	bool updateIndex;
	CPreOrderFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pPreOrder=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pPreOrder,&thePreOrder);
		needContinue=updateFunc(&thePreOrder, pTransaction, parameter, &updateIndex);
		pFactory->update(pPreOrder,&thePreOrder,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CPreOrderIterator *pIterator, TPreOrderSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CPreOrder *pPreOrder;
	int selected;
	CPreOrderFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pPreOrder=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pPreOrder, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pPreOrder,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CIndexPreOrderIterator *pIterator, TIndexPreOrderActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CIndexPreOrder *pIndexPreOrder;
	
	while ((pIndexPreOrder=pIterator->next())!=NULL)
	{
		if (!actionFunc(pIndexPreOrder, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CIndexPreOrderIterator *pIterator, TIndexPreOrderUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CIndexPreOrder *pIndexPreOrder;
	CWriteableIndexPreOrder theIndexPreOrder;
	bool updateIndex;
	CIndexPreOrderFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pIndexPreOrder=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pIndexPreOrder,&theIndexPreOrder);
		needContinue=updateFunc(&theIndexPreOrder, pTransaction, parameter, &updateIndex);
		pFactory->update(pIndexPreOrder,&theIndexPreOrder,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CIndexPreOrderIterator *pIterator, TIndexPreOrderSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CIndexPreOrder *pIndexPreOrder;
	int selected;
	CIndexPreOrderFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pIndexPreOrder=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pIndexPreOrder, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pIndexPreOrder,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CInvestorPositionIterator *pIterator, TInvestorPositionActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorPosition *pInvestorPosition;
	
	while ((pInvestorPosition=pIterator->next())!=NULL)
	{
		if (!actionFunc(pInvestorPosition, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CInvestorPositionIterator *pIterator, TInvestorPositionUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorPosition *pInvestorPosition;
	CWriteableInvestorPosition theInvestorPosition;
	bool updateIndex;
	CInvestorPositionFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestorPosition=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pInvestorPosition,&theInvestorPosition);
		needContinue=updateFunc(&theInvestorPosition, pTransaction, parameter, &updateIndex);
		pFactory->update(pInvestorPosition,&theInvestorPosition,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CInvestorPositionIterator *pIterator, TInvestorPositionSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorPosition *pInvestorPosition;
	int selected;
	CInvestorPositionFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestorPosition=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pInvestorPosition, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pInvestorPosition,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CInvestorAccountIterator *pIterator, TInvestorAccountActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorAccount *pInvestorAccount;
	
	while ((pInvestorAccount=pIterator->next())!=NULL)
	{
		if (!actionFunc(pInvestorAccount, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CInvestorAccountIterator *pIterator, TInvestorAccountUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorAccount *pInvestorAccount;
	CWriteableInvestorAccount theInvestorAccount;
	bool updateIndex;
	CInvestorAccountFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestorAccount=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pInvestorAccount,&theInvestorAccount);
		needContinue=updateFunc(&theInvestorAccount, pTransaction, parameter, &updateIndex);
		pFactory->update(pInvestorAccount,&theInvestorAccount,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CInvestorAccountIterator *pIterator, TInvestorAccountSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorAccount *pInvestorAccount;
	int selected;
	CInvestorAccountFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestorAccount=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pInvestorAccount, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pInvestorAccount,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CInvestorAccountDepositIterator *pIterator, TInvestorAccountDepositActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorAccountDeposit *pInvestorAccountDeposit;
	
	while ((pInvestorAccountDeposit=pIterator->next())!=NULL)
	{
		if (!actionFunc(pInvestorAccountDeposit, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CInvestorAccountDepositIterator *pIterator, TInvestorAccountDepositUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorAccountDeposit *pInvestorAccountDeposit;
	CWriteableInvestorAccountDeposit theInvestorAccountDeposit;
	bool updateIndex;
	CInvestorAccountDepositFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestorAccountDeposit=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pInvestorAccountDeposit,&theInvestorAccountDeposit);
		needContinue=updateFunc(&theInvestorAccountDeposit, pTransaction, parameter, &updateIndex);
		pFactory->update(pInvestorAccountDeposit,&theInvestorAccountDeposit,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CInvestorAccountDepositIterator *pIterator, TInvestorAccountDepositSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorAccountDeposit *pInvestorAccountDeposit;
	int selected;
	CInvestorAccountDepositFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestorAccountDeposit=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pInvestorAccountDeposit, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pInvestorAccountDeposit,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CExchangeIterator *pIterator, TExchangeActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CExchange *pExchange;
	
	while ((pExchange=pIterator->next())!=NULL)
	{
		if (!actionFunc(pExchange, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CExchangeIterator *pIterator, TExchangeUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CExchange *pExchange;
	CWriteableExchange theExchange;
	bool updateIndex;
	CExchangeFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pExchange=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pExchange,&theExchange);
		needContinue=updateFunc(&theExchange, pTransaction, parameter, &updateIndex);
		pFactory->update(pExchange,&theExchange,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CExchangeIterator *pIterator, TExchangeSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CExchange *pExchange;
	int selected;
	CExchangeFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pExchange=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pExchange, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pExchange,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CSeatIterator *pIterator, TSeatActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CSeat *pSeat;
	
	while ((pSeat=pIterator->next())!=NULL)
	{
		if (!actionFunc(pSeat, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CSeatIterator *pIterator, TSeatUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CSeat *pSeat;
	CWriteableSeat theSeat;
	bool updateIndex;
	CSeatFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pSeat=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pSeat,&theSeat);
		needContinue=updateFunc(&theSeat, pTransaction, parameter, &updateIndex);
		pFactory->update(pSeat,&theSeat,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CSeatIterator *pIterator, TSeatSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CSeat *pSeat;
	int selected;
	CSeatFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pSeat=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pSeat, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pSeat,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CInstrumentIterator *pIterator, TInstrumentActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInstrument *pInstrument;
	
	while ((pInstrument=pIterator->next())!=NULL)
	{
		if (!actionFunc(pInstrument, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CInstrumentIterator *pIterator, TInstrumentUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInstrument *pInstrument;
	CWriteableInstrument theInstrument;
	bool updateIndex;
	CInstrumentFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInstrument=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pInstrument,&theInstrument);
		needContinue=updateFunc(&theInstrument, pTransaction, parameter, &updateIndex);
		pFactory->update(pInstrument,&theInstrument,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CInstrumentIterator *pIterator, TInstrumentSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInstrument *pInstrument;
	int selected;
	CInstrumentFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInstrument=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pInstrument, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pInstrument,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CCmbInstrumentDetailIterator *pIterator, TCmbInstrumentDetailActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CCmbInstrumentDetail *pCmbInstrumentDetail;
	
	while ((pCmbInstrumentDetail=pIterator->next())!=NULL)
	{
		if (!actionFunc(pCmbInstrumentDetail, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CCmbInstrumentDetailIterator *pIterator, TCmbInstrumentDetailUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CCmbInstrumentDetail *pCmbInstrumentDetail;
	CWriteableCmbInstrumentDetail theCmbInstrumentDetail;
	bool updateIndex;
	CCmbInstrumentDetailFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pCmbInstrumentDetail=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pCmbInstrumentDetail,&theCmbInstrumentDetail);
		needContinue=updateFunc(&theCmbInstrumentDetail, pTransaction, parameter, &updateIndex);
		pFactory->update(pCmbInstrumentDetail,&theCmbInstrumentDetail,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CCmbInstrumentDetailIterator *pIterator, TCmbInstrumentDetailSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CCmbInstrumentDetail *pCmbInstrumentDetail;
	int selected;
	CCmbInstrumentDetailFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pCmbInstrumentDetail=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pCmbInstrumentDetail, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pCmbInstrumentDetail,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CClientTradingIDIterator *pIterator, TClientTradingIDActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CClientTradingID *pClientTradingID;
	
	while ((pClientTradingID=pIterator->next())!=NULL)
	{
		if (!actionFunc(pClientTradingID, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CClientTradingIDIterator *pIterator, TClientTradingIDUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CClientTradingID *pClientTradingID;
	CWriteableClientTradingID theClientTradingID;
	bool updateIndex;
	CClientTradingIDFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pClientTradingID=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pClientTradingID,&theClientTradingID);
		needContinue=updateFunc(&theClientTradingID, pTransaction, parameter, &updateIndex);
		pFactory->update(pClientTradingID,&theClientTradingID,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CClientTradingIDIterator *pIterator, TClientTradingIDSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CClientTradingID *pClientTradingID;
	int selected;
	CClientTradingIDFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pClientTradingID=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pClientTradingID, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pClientTradingID,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CInvestorIterator *pIterator, TInvestorActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestor *pInvestor;
	
	while ((pInvestor=pIterator->next())!=NULL)
	{
		if (!actionFunc(pInvestor, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CInvestorIterator *pIterator, TInvestorUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestor *pInvestor;
	CWriteableInvestor theInvestor;
	bool updateIndex;
	CInvestorFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestor=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pInvestor,&theInvestor);
		needContinue=updateFunc(&theInvestor, pTransaction, parameter, &updateIndex);
		pFactory->update(pInvestor,&theInvestor,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CInvestorIterator *pIterator, TInvestorSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestor *pInvestor;
	int selected;
	CInvestorFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestor=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pInvestor, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pInvestor,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CInvestorMarginIterator *pIterator, TInvestorMarginActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorMargin *pInvestorMargin;
	
	while ((pInvestorMargin=pIterator->next())!=NULL)
	{
		if (!actionFunc(pInvestorMargin, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CInvestorMarginIterator *pIterator, TInvestorMarginUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorMargin *pInvestorMargin;
	CWriteableInvestorMargin theInvestorMargin;
	bool updateIndex;
	CInvestorMarginFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestorMargin=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pInvestorMargin,&theInvestorMargin);
		needContinue=updateFunc(&theInvestorMargin, pTransaction, parameter, &updateIndex);
		pFactory->update(pInvestorMargin,&theInvestorMargin,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CInvestorMarginIterator *pIterator, TInvestorMarginSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorMargin *pInvestorMargin;
	int selected;
	CInvestorMarginFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestorMargin=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pInvestorMargin, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pInvestorMargin,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CInvestorFeeIterator *pIterator, TInvestorFeeActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorFee *pInvestorFee;
	
	while ((pInvestorFee=pIterator->next())!=NULL)
	{
		if (!actionFunc(pInvestorFee, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CInvestorFeeIterator *pIterator, TInvestorFeeUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorFee *pInvestorFee;
	CWriteableInvestorFee theInvestorFee;
	bool updateIndex;
	CInvestorFeeFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestorFee=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pInvestorFee,&theInvestorFee);
		needContinue=updateFunc(&theInvestorFee, pTransaction, parameter, &updateIndex);
		pFactory->update(pInvestorFee,&theInvestorFee,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CInvestorFeeIterator *pIterator, TInvestorFeeSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorFee *pInvestorFee;
	int selected;
	CInvestorFeeFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestorFee=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pInvestorFee, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pInvestorFee,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CUserIterator *pIterator, TUserActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CUser *pUser;
	
	while ((pUser=pIterator->next())!=NULL)
	{
		if (!actionFunc(pUser, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CUserIterator *pIterator, TUserUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CUser *pUser;
	CWriteableUser theUser;
	bool updateIndex;
	CUserFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pUser=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pUser,&theUser);
		needContinue=updateFunc(&theUser, pTransaction, parameter, &updateIndex);
		pFactory->update(pUser,&theUser,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CUserIterator *pIterator, TUserSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CUser *pUser;
	int selected;
	CUserFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pUser=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pUser, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pUser,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CUserInvestorIterator *pIterator, TUserInvestorActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CUserInvestor *pUserInvestor;
	
	while ((pUserInvestor=pIterator->next())!=NULL)
	{
		if (!actionFunc(pUserInvestor, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CUserInvestorIterator *pIterator, TUserInvestorUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CUserInvestor *pUserInvestor;
	CWriteableUserInvestor theUserInvestor;
	bool updateIndex;
	CUserInvestorFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pUserInvestor=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pUserInvestor,&theUserInvestor);
		needContinue=updateFunc(&theUserInvestor, pTransaction, parameter, &updateIndex);
		pFactory->update(pUserInvestor,&theUserInvestor,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CUserInvestorIterator *pIterator, TUserInvestorSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CUserInvestor *pUserInvestor;
	int selected;
	CUserInvestorFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pUserInvestor=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pUserInvestor, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pUserInvestor,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(COrderInsertFailedIterator *pIterator, TOrderInsertFailedActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	COrderInsertFailed *pOrderInsertFailed;
	
	while ((pOrderInsertFailed=pIterator->next())!=NULL)
	{
		if (!actionFunc(pOrderInsertFailed, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(COrderInsertFailedIterator *pIterator, TOrderInsertFailedUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	COrderInsertFailed *pOrderInsertFailed;
	CWriteableOrderInsertFailed theOrderInsertFailed;
	bool updateIndex;
	COrderInsertFailedFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pOrderInsertFailed=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pOrderInsertFailed,&theOrderInsertFailed);
		needContinue=updateFunc(&theOrderInsertFailed, pTransaction, parameter, &updateIndex);
		pFactory->update(pOrderInsertFailed,&theOrderInsertFailed,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(COrderInsertFailedIterator *pIterator, TOrderInsertFailedSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	COrderInsertFailed *pOrderInsertFailed;
	int selected;
	COrderInsertFailedFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pOrderInsertFailed=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pOrderInsertFailed, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pOrderInsertFailed,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CUserTradingRightIterator *pIterator, TUserTradingRightActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CUserTradingRight *pUserTradingRight;
	
	while ((pUserTradingRight=pIterator->next())!=NULL)
	{
		if (!actionFunc(pUserTradingRight, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CUserTradingRightIterator *pIterator, TUserTradingRightUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CUserTradingRight *pUserTradingRight;
	CWriteableUserTradingRight theUserTradingRight;
	bool updateIndex;
	CUserTradingRightFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pUserTradingRight=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pUserTradingRight,&theUserTradingRight);
		needContinue=updateFunc(&theUserTradingRight, pTransaction, parameter, &updateIndex);
		pFactory->update(pUserTradingRight,&theUserTradingRight,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CUserTradingRightIterator *pIterator, TUserTradingRightSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CUserTradingRight *pUserTradingRight;
	int selected;
	CUserTradingRightFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pUserTradingRight=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pUserTradingRight, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pUserTradingRight,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CCurrentTimeIterator *pIterator, TCurrentTimeActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CCurrentTime *pCurrentTime;
	
	while ((pCurrentTime=pIterator->next())!=NULL)
	{
		if (!actionFunc(pCurrentTime, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CCurrentTimeIterator *pIterator, TCurrentTimeUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CCurrentTime *pCurrentTime;
	CWriteableCurrentTime theCurrentTime;
	bool updateIndex;
	CCurrentTimeFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pCurrentTime=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pCurrentTime,&theCurrentTime);
		needContinue=updateFunc(&theCurrentTime, pTransaction, parameter, &updateIndex);
		pFactory->update(pCurrentTime,&theCurrentTime,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CCurrentTimeIterator *pIterator, TCurrentTimeSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CCurrentTime *pCurrentTime;
	int selected;
	CCurrentTimeFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pCurrentTime=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pCurrentTime, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pCurrentTime,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CUserSessionIterator *pIterator, TUserSessionActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CUserSession *pUserSession;
	
	while ((pUserSession=pIterator->next())!=NULL)
	{
		if (!actionFunc(pUserSession, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CUserSessionIterator *pIterator, TUserSessionUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CUserSession *pUserSession;
	CWriteableUserSession theUserSession;
	bool updateIndex;
	CUserSessionFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pUserSession=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pUserSession,&theUserSession);
		needContinue=updateFunc(&theUserSession, pTransaction, parameter, &updateIndex);
		pFactory->update(pUserSession,&theUserSession,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CUserSessionIterator *pIterator, TUserSessionSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CUserSession *pUserSession;
	int selected;
	CUserSessionFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pUserSession=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pUserSession, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pUserSession,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CMaxLocalIDIterator *pIterator, TMaxLocalIDActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CMaxLocalID *pMaxLocalID;
	
	while ((pMaxLocalID=pIterator->next())!=NULL)
	{
		if (!actionFunc(pMaxLocalID, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CMaxLocalIDIterator *pIterator, TMaxLocalIDUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CMaxLocalID *pMaxLocalID;
	CWriteableMaxLocalID theMaxLocalID;
	bool updateIndex;
	CMaxLocalIDFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pMaxLocalID=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pMaxLocalID,&theMaxLocalID);
		needContinue=updateFunc(&theMaxLocalID, pTransaction, parameter, &updateIndex);
		pFactory->update(pMaxLocalID,&theMaxLocalID,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CMaxLocalIDIterator *pIterator, TMaxLocalIDSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CMaxLocalID *pMaxLocalID;
	int selected;
	CMaxLocalIDFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pMaxLocalID=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pMaxLocalID, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pMaxLocalID,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CBrkUserIDLocalIDIterator *pIterator, TBrkUserIDLocalIDActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CBrkUserIDLocalID *pBrkUserIDLocalID;
	
	while ((pBrkUserIDLocalID=pIterator->next())!=NULL)
	{
		if (!actionFunc(pBrkUserIDLocalID, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CBrkUserIDLocalIDIterator *pIterator, TBrkUserIDLocalIDUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CBrkUserIDLocalID *pBrkUserIDLocalID;
	CWriteableBrkUserIDLocalID theBrkUserIDLocalID;
	bool updateIndex;
	CBrkUserIDLocalIDFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pBrkUserIDLocalID=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pBrkUserIDLocalID,&theBrkUserIDLocalID);
		needContinue=updateFunc(&theBrkUserIDLocalID, pTransaction, parameter, &updateIndex);
		pFactory->update(pBrkUserIDLocalID,&theBrkUserIDLocalID,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CBrkUserIDLocalIDIterator *pIterator, TBrkUserIDLocalIDSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CBrkUserIDLocalID *pBrkUserIDLocalID;
	int selected;
	CBrkUserIDLocalIDFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pBrkUserIDLocalID=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pBrkUserIDLocalID, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pBrkUserIDLocalID,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CPartClientInsGroupPositionIterator *pIterator, TPartClientInsGroupPositionActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CPartClientInsGroupPosition *pPartClientInsGroupPosition;
	
	while ((pPartClientInsGroupPosition=pIterator->next())!=NULL)
	{
		if (!actionFunc(pPartClientInsGroupPosition, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CPartClientInsGroupPositionIterator *pIterator, TPartClientInsGroupPositionUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CPartClientInsGroupPosition *pPartClientInsGroupPosition;
	CWriteablePartClientInsGroupPosition thePartClientInsGroupPosition;
	bool updateIndex;
	CPartClientInsGroupPositionFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pPartClientInsGroupPosition=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pPartClientInsGroupPosition,&thePartClientInsGroupPosition);
		needContinue=updateFunc(&thePartClientInsGroupPosition, pTransaction, parameter, &updateIndex);
		pFactory->update(pPartClientInsGroupPosition,&thePartClientInsGroupPosition,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CPartClientInsGroupPositionIterator *pIterator, TPartClientInsGroupPositionSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CPartClientInsGroupPosition *pPartClientInsGroupPosition;
	int selected;
	CPartClientInsGroupPositionFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pPartClientInsGroupPosition=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pPartClientInsGroupPosition, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pPartClientInsGroupPosition,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CClientMarginCombTypeIterator *pIterator, TClientMarginCombTypeActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CClientMarginCombType *pClientMarginCombType;
	
	while ((pClientMarginCombType=pIterator->next())!=NULL)
	{
		if (!actionFunc(pClientMarginCombType, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CClientMarginCombTypeIterator *pIterator, TClientMarginCombTypeUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CClientMarginCombType *pClientMarginCombType;
	CWriteableClientMarginCombType theClientMarginCombType;
	bool updateIndex;
	CClientMarginCombTypeFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pClientMarginCombType=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pClientMarginCombType,&theClientMarginCombType);
		needContinue=updateFunc(&theClientMarginCombType, pTransaction, parameter, &updateIndex);
		pFactory->update(pClientMarginCombType,&theClientMarginCombType,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CClientMarginCombTypeIterator *pIterator, TClientMarginCombTypeSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CClientMarginCombType *pClientMarginCombType;
	int selected;
	CClientMarginCombTypeFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pClientMarginCombType=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pClientMarginCombType, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pClientMarginCombType,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CInstrumentGroupIterator *pIterator, TInstrumentGroupActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInstrumentGroup *pInstrumentGroup;
	
	while ((pInstrumentGroup=pIterator->next())!=NULL)
	{
		if (!actionFunc(pInstrumentGroup, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CInstrumentGroupIterator *pIterator, TInstrumentGroupUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInstrumentGroup *pInstrumentGroup;
	CWriteableInstrumentGroup theInstrumentGroup;
	bool updateIndex;
	CInstrumentGroupFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInstrumentGroup=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pInstrumentGroup,&theInstrumentGroup);
		needContinue=updateFunc(&theInstrumentGroup, pTransaction, parameter, &updateIndex);
		pFactory->update(pInstrumentGroup,&theInstrumentGroup,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CInstrumentGroupIterator *pIterator, TInstrumentGroupSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInstrumentGroup *pInstrumentGroup;
	int selected;
	CInstrumentGroupFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInstrumentGroup=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pInstrumentGroup, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pInstrumentGroup,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CSGEDeferRateIterator *pIterator, TSGEDeferRateActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CSGEDeferRate *pSGEDeferRate;
	
	while ((pSGEDeferRate=pIterator->next())!=NULL)
	{
		if (!actionFunc(pSGEDeferRate, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CSGEDeferRateIterator *pIterator, TSGEDeferRateUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CSGEDeferRate *pSGEDeferRate;
	CWriteableSGEDeferRate theSGEDeferRate;
	bool updateIndex;
	CSGEDeferRateFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pSGEDeferRate=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pSGEDeferRate,&theSGEDeferRate);
		needContinue=updateFunc(&theSGEDeferRate, pTransaction, parameter, &updateIndex);
		pFactory->update(pSGEDeferRate,&theSGEDeferRate,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CSGEDeferRateIterator *pIterator, TSGEDeferRateSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CSGEDeferRate *pSGEDeferRate;
	int selected;
	CSGEDeferRateFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pSGEDeferRate=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pSGEDeferRate, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pSGEDeferRate,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CInvestorTradingRightIterator *pIterator, TInvestorTradingRightActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorTradingRight *pInvestorTradingRight;
	
	while ((pInvestorTradingRight=pIterator->next())!=NULL)
	{
		if (!actionFunc(pInvestorTradingRight, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CInvestorTradingRightIterator *pIterator, TInvestorTradingRightUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorTradingRight *pInvestorTradingRight;
	CWriteableInvestorTradingRight theInvestorTradingRight;
	bool updateIndex;
	CInvestorTradingRightFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestorTradingRight=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pInvestorTradingRight,&theInvestorTradingRight);
		needContinue=updateFunc(&theInvestorTradingRight, pTransaction, parameter, &updateIndex);
		pFactory->update(pInvestorTradingRight,&theInvestorTradingRight,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CInvestorTradingRightIterator *pIterator, TInvestorTradingRightSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorTradingRight *pInvestorTradingRight;
	int selected;
	CInvestorTradingRightFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestorTradingRight=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pInvestorTradingRight, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pInvestorTradingRight,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CUserIPIterator *pIterator, TUserIPActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CUserIP *pUserIP;
	
	while ((pUserIP=pIterator->next())!=NULL)
	{
		if (!actionFunc(pUserIP, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CUserIPIterator *pIterator, TUserIPUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CUserIP *pUserIP;
	CWriteableUserIP theUserIP;
	bool updateIndex;
	CUserIPFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pUserIP=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pUserIP,&theUserIP);
		needContinue=updateFunc(&theUserIP, pTransaction, parameter, &updateIndex);
		pFactory->update(pUserIP,&theUserIP,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CUserIPIterator *pIterator, TUserIPSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CUserIP *pUserIP;
	int selected;
	CUserIPFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pUserIP=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pUserIP, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pUserIP,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CInvestorOptionFeeIterator *pIterator, TInvestorOptionFeeActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorOptionFee *pInvestorOptionFee;
	
	while ((pInvestorOptionFee=pIterator->next())!=NULL)
	{
		if (!actionFunc(pInvestorOptionFee, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CInvestorOptionFeeIterator *pIterator, TInvestorOptionFeeUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorOptionFee *pInvestorOptionFee;
	CWriteableInvestorOptionFee theInvestorOptionFee;
	bool updateIndex;
	CInvestorOptionFeeFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestorOptionFee=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pInvestorOptionFee,&theInvestorOptionFee);
		needContinue=updateFunc(&theInvestorOptionFee, pTransaction, parameter, &updateIndex);
		pFactory->update(pInvestorOptionFee,&theInvestorOptionFee,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CInvestorOptionFeeIterator *pIterator, TInvestorOptionFeeSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CInvestorOptionFee *pInvestorOptionFee;
	int selected;
	CInvestorOptionFeeFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pInvestorOptionFee=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pInvestorOptionFee, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pInvestorOptionFee,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CMarketDataIterator *pIterator, TMarketDataActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CMarketData *pMarketData;
	
	while ((pMarketData=pIterator->next())!=NULL)
	{
		if (!actionFunc(pMarketData, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CMarketDataIterator *pIterator, TMarketDataUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CMarketData *pMarketData;
	CWriteableMarketData theMarketData;
	bool updateIndex;
	CMarketDataFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pMarketData=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pMarketData,&theMarketData);
		needContinue=updateFunc(&theMarketData, pTransaction, parameter, &updateIndex);
		pFactory->update(pMarketData,&theMarketData,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CMarketDataIterator *pIterator, TMarketDataSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CMarketData *pMarketData;
	int selected;
	CMarketDataFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pMarketData=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pMarketData, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pMarketData,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(COrderDelayIterator *pIterator, TOrderDelayActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	COrderDelay *pOrderDelay;
	
	while ((pOrderDelay=pIterator->next())!=NULL)
	{
		if (!actionFunc(pOrderDelay, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(COrderDelayIterator *pIterator, TOrderDelayUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	COrderDelay *pOrderDelay;
	CWriteableOrderDelay theOrderDelay;
	bool updateIndex;
	COrderDelayFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pOrderDelay=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pOrderDelay,&theOrderDelay);
		needContinue=updateFunc(&theOrderDelay, pTransaction, parameter, &updateIndex);
		pFactory->update(pOrderDelay,&theOrderDelay,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(COrderDelayIterator *pIterator, TOrderDelaySelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	COrderDelay *pOrderDelay;
	int selected;
	COrderDelayFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pOrderDelay=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pOrderDelay, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pOrderDelay,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

void groupAction(CSystemInfoIterator *pIterator, TSystemInfoActionFunc actionFunc,
	CTransaction *pTransaction, void *parameter)
{
	CSystemInfo *pSystemInfo;
	
	while ((pSystemInfo=pIterator->next())!=NULL)
	{
		if (!actionFunc(pSystemInfo, pTransaction, parameter))
		{
			return;
		}
	}
}

void groupUpdate(CSystemInfoIterator *pIterator, TSystemInfoUpdateFunc updateFunc,
	CTransaction *pTransaction, void *parameter)
{
	CSystemInfo *pSystemInfo;
	CWriteableSystemInfo theSystemInfo;
	bool updateIndex;
	CSystemInfoFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pSystemInfo=pIterator->next())!=NULL)
	{
		pFactory->retrieve(pSystemInfo,&theSystemInfo);
		needContinue=updateFunc(&theSystemInfo, pTransaction, parameter, &updateIndex);
		pFactory->update(pSystemInfo,&theSystemInfo,pTransaction,updateIndex);
		if (!needContinue)
		{
			return;
		}
	}
}

void groupDelete(CSystemInfoIterator *pIterator, TSystemInfoSelectFunc selectFunc,
	CTransaction *pTransaction, void *parameter)
{
	CSystemInfo *pSystemInfo;
	int selected;
	CSystemInfoFactory *pFactory;
	int needContinue;
	
	pFactory=pIterator->getFactory();
	
	while ((pSystemInfo=pIterator->next())!=NULL)
	{
		if (selectFunc==NULL)
		{
			needContinue=1;
			selected=1;
		}
		else
		{
			needContinue=selectFunc(pSystemInfo, pTransaction, parameter, &selected);
		}
		if (selected)
		{
			pFactory->remove(pSystemInfo,pTransaction);
		}
		if (!needContinue)
		{
			return;
		}
	}
}

