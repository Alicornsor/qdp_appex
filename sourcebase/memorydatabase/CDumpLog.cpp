/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company 上海量投网络科技有限公司
///@file CDumpLog.cpp
///@brief实现了类CDumpLog
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CDumpLog.h"
#include "monitorIndex.h"

///本宏控制是否使用单行方式进行输出
#define SINGLE_LINE

CDataSyncStatusDumpTrigger::CDataSyncStatusDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CDataSyncStatusDumpTrigger::~CDataSyncStatusDumpTrigger(void)
{
}


void CDataSyncStatusDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CDataSyncStatusDumpTrigger");
	pLogger->output(indent,0,"CDataSyncStatusDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CDataSyncStatusDumpTrigger::beforeAdd(CWriteableDataSyncStatus *pDataSyncStatus)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"DataSyncStatus,add");
		pDataSyncStatus->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add DataSyncStatus\n");
		pDataSyncStatus->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CDataSyncStatusDumpTrigger::beforeUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"DataSyncStatus,upd");
		pNewDataSyncStatus->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update DataSyncStatus\n");
		pNewDataSyncStatus->dumpDiff(m_output,pDataSyncStatus);
#endif
		fflush(m_output);
	}
}
	
void CDataSyncStatusDumpTrigger::beforeRemove(CDataSyncStatus *pDataSyncStatus)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"DataSyncStatus,del");
		pDataSyncStatus->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove DataSyncStatus\n");
		pDataSyncStatus->dump(m_output);
#endif
		fflush(m_output);
	}
}

CSystemStatusDumpTrigger::CSystemStatusDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CSystemStatusDumpTrigger::~CSystemStatusDumpTrigger(void)
{
}


void CSystemStatusDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CSystemStatusDumpTrigger");
	pLogger->output(indent,0,"CSystemStatusDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CSystemStatusDumpTrigger::beforeAdd(CWriteableSystemStatus *pSystemStatus)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"SystemStatus,add");
		pSystemStatus->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add SystemStatus\n");
		pSystemStatus->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CSystemStatusDumpTrigger::beforeUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"SystemStatus,upd");
		pNewSystemStatus->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update SystemStatus\n");
		pNewSystemStatus->dumpDiff(m_output,pSystemStatus);
#endif
		fflush(m_output);
	}
}
	
void CSystemStatusDumpTrigger::beforeRemove(CSystemStatus *pSystemStatus)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"SystemStatus,del");
		pSystemStatus->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove SystemStatus\n");
		pSystemStatus->dump(m_output);
#endif
		fflush(m_output);
	}
}

COrderActionDumpTrigger::COrderActionDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

COrderActionDumpTrigger::~COrderActionDumpTrigger(void)
{
}


void COrderActionDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("COrderActionDumpTrigger");
	pLogger->output(indent,0,"COrderActionDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void COrderActionDumpTrigger::beforeAdd(CWriteableOrderAction *pOrderAction)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"OrderAction,add");
		pOrderAction->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add OrderAction\n");
		pOrderAction->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void COrderActionDumpTrigger::beforeUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"OrderAction,upd");
		pNewOrderAction->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update OrderAction\n");
		pNewOrderAction->dumpDiff(m_output,pOrderAction);
#endif
		fflush(m_output);
	}
}
	
void COrderActionDumpTrigger::beforeRemove(COrderAction *pOrderAction)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"OrderAction,del");
		pOrderAction->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove OrderAction\n");
		pOrderAction->dump(m_output);
#endif
		fflush(m_output);
	}
}

COrderDumpTrigger::COrderDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

COrderDumpTrigger::~COrderDumpTrigger(void)
{
}


void COrderDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("COrderDumpTrigger");
	pLogger->output(indent,0,"COrderDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void COrderDumpTrigger::beforeAdd(CWriteableOrder *pOrder)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Order,add");
		pOrder->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add Order\n");
		pOrder->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void COrderDumpTrigger::beforeUpdate(COrder *pOrder, CWriteableOrder *pNewOrder)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Order,upd");
		pNewOrder->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update Order\n");
		pNewOrder->dumpDiff(m_output,pOrder);
#endif
		fflush(m_output);
	}
}
	
void COrderDumpTrigger::beforeRemove(COrder *pOrder)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Order,del");
		pOrder->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove Order\n");
		pOrder->dump(m_output);
#endif
		fflush(m_output);
	}
}

CTradeDumpTrigger::CTradeDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CTradeDumpTrigger::~CTradeDumpTrigger(void)
{
}


void CTradeDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CTradeDumpTrigger");
	pLogger->output(indent,0,"CTradeDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CTradeDumpTrigger::beforeAdd(CWriteableTrade *pTrade)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Trade,add");
		pTrade->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add Trade\n");
		pTrade->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CTradeDumpTrigger::beforeUpdate(CTrade *pTrade, CWriteableTrade *pNewTrade)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Trade,upd");
		pNewTrade->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update Trade\n");
		pNewTrade->dumpDiff(m_output,pTrade);
#endif
		fflush(m_output);
	}
}
	
void CTradeDumpTrigger::beforeRemove(CTrade *pTrade)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Trade,del");
		pTrade->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove Trade\n");
		pTrade->dump(m_output);
#endif
		fflush(m_output);
	}
}

CPreOrderDumpTrigger::CPreOrderDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CPreOrderDumpTrigger::~CPreOrderDumpTrigger(void)
{
}


void CPreOrderDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CPreOrderDumpTrigger");
	pLogger->output(indent,0,"CPreOrderDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CPreOrderDumpTrigger::beforeAdd(CWriteablePreOrder *pPreOrder)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"PreOrder,add");
		pPreOrder->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add PreOrder\n");
		pPreOrder->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CPreOrderDumpTrigger::beforeUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"PreOrder,upd");
		pNewPreOrder->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update PreOrder\n");
		pNewPreOrder->dumpDiff(m_output,pPreOrder);
#endif
		fflush(m_output);
	}
}
	
void CPreOrderDumpTrigger::beforeRemove(CPreOrder *pPreOrder)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"PreOrder,del");
		pPreOrder->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove PreOrder\n");
		pPreOrder->dump(m_output);
#endif
		fflush(m_output);
	}
}

CIndexPreOrderDumpTrigger::CIndexPreOrderDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CIndexPreOrderDumpTrigger::~CIndexPreOrderDumpTrigger(void)
{
}


void CIndexPreOrderDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CIndexPreOrderDumpTrigger");
	pLogger->output(indent,0,"CIndexPreOrderDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CIndexPreOrderDumpTrigger::beforeAdd(CWriteableIndexPreOrder *pIndexPreOrder)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"IndexPreOrder,add");
		pIndexPreOrder->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add IndexPreOrder\n");
		pIndexPreOrder->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CIndexPreOrderDumpTrigger::beforeUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"IndexPreOrder,upd");
		pNewIndexPreOrder->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update IndexPreOrder\n");
		pNewIndexPreOrder->dumpDiff(m_output,pIndexPreOrder);
#endif
		fflush(m_output);
	}
}
	
void CIndexPreOrderDumpTrigger::beforeRemove(CIndexPreOrder *pIndexPreOrder)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"IndexPreOrder,del");
		pIndexPreOrder->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove IndexPreOrder\n");
		pIndexPreOrder->dump(m_output);
#endif
		fflush(m_output);
	}
}

CInvestorPositionDumpTrigger::CInvestorPositionDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CInvestorPositionDumpTrigger::~CInvestorPositionDumpTrigger(void)
{
}


void CInvestorPositionDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CInvestorPositionDumpTrigger");
	pLogger->output(indent,0,"CInvestorPositionDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CInvestorPositionDumpTrigger::beforeAdd(CWriteableInvestorPosition *pInvestorPosition)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorPosition,add");
		pInvestorPosition->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add InvestorPosition\n");
		pInvestorPosition->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CInvestorPositionDumpTrigger::beforeUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorPosition,upd");
		pNewInvestorPosition->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update InvestorPosition\n");
		pNewInvestorPosition->dumpDiff(m_output,pInvestorPosition);
#endif
		fflush(m_output);
	}
}
	
void CInvestorPositionDumpTrigger::beforeRemove(CInvestorPosition *pInvestorPosition)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorPosition,del");
		pInvestorPosition->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove InvestorPosition\n");
		pInvestorPosition->dump(m_output);
#endif
		fflush(m_output);
	}
}

CInvestorAccountDumpTrigger::CInvestorAccountDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CInvestorAccountDumpTrigger::~CInvestorAccountDumpTrigger(void)
{
}


void CInvestorAccountDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CInvestorAccountDumpTrigger");
	pLogger->output(indent,0,"CInvestorAccountDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CInvestorAccountDumpTrigger::beforeAdd(CWriteableInvestorAccount *pInvestorAccount)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorAccount,add");
		pInvestorAccount->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add InvestorAccount\n");
		pInvestorAccount->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CInvestorAccountDumpTrigger::beforeUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorAccount,upd");
		pNewInvestorAccount->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update InvestorAccount\n");
		pNewInvestorAccount->dumpDiff(m_output,pInvestorAccount);
#endif
		fflush(m_output);
	}
}
	
void CInvestorAccountDumpTrigger::beforeRemove(CInvestorAccount *pInvestorAccount)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorAccount,del");
		pInvestorAccount->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove InvestorAccount\n");
		pInvestorAccount->dump(m_output);
#endif
		fflush(m_output);
	}
}

CInvestorAccountDepositDumpTrigger::CInvestorAccountDepositDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CInvestorAccountDepositDumpTrigger::~CInvestorAccountDepositDumpTrigger(void)
{
}


void CInvestorAccountDepositDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CInvestorAccountDepositDumpTrigger");
	pLogger->output(indent,0,"CInvestorAccountDepositDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CInvestorAccountDepositDumpTrigger::beforeAdd(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorAccountDeposit,add");
		pInvestorAccountDeposit->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add InvestorAccountDeposit\n");
		pInvestorAccountDeposit->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CInvestorAccountDepositDumpTrigger::beforeUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorAccountDeposit,upd");
		pNewInvestorAccountDeposit->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update InvestorAccountDeposit\n");
		pNewInvestorAccountDeposit->dumpDiff(m_output,pInvestorAccountDeposit);
#endif
		fflush(m_output);
	}
}
	
void CInvestorAccountDepositDumpTrigger::beforeRemove(CInvestorAccountDeposit *pInvestorAccountDeposit)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorAccountDeposit,del");
		pInvestorAccountDeposit->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove InvestorAccountDeposit\n");
		pInvestorAccountDeposit->dump(m_output);
#endif
		fflush(m_output);
	}
}

CExchangeDumpTrigger::CExchangeDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CExchangeDumpTrigger::~CExchangeDumpTrigger(void)
{
}


void CExchangeDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CExchangeDumpTrigger");
	pLogger->output(indent,0,"CExchangeDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CExchangeDumpTrigger::beforeAdd(CWriteableExchange *pExchange)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Exchange,add");
		pExchange->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add Exchange\n");
		pExchange->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CExchangeDumpTrigger::beforeUpdate(CExchange *pExchange, CWriteableExchange *pNewExchange)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Exchange,upd");
		pNewExchange->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update Exchange\n");
		pNewExchange->dumpDiff(m_output,pExchange);
#endif
		fflush(m_output);
	}
}
	
void CExchangeDumpTrigger::beforeRemove(CExchange *pExchange)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Exchange,del");
		pExchange->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove Exchange\n");
		pExchange->dump(m_output);
#endif
		fflush(m_output);
	}
}

CSeatDumpTrigger::CSeatDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CSeatDumpTrigger::~CSeatDumpTrigger(void)
{
}


void CSeatDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CSeatDumpTrigger");
	pLogger->output(indent,0,"CSeatDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CSeatDumpTrigger::beforeAdd(CWriteableSeat *pSeat)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Seat,add");
		pSeat->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add Seat\n");
		pSeat->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CSeatDumpTrigger::beforeUpdate(CSeat *pSeat, CWriteableSeat *pNewSeat)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Seat,upd");
		pNewSeat->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update Seat\n");
		pNewSeat->dumpDiff(m_output,pSeat);
#endif
		fflush(m_output);
	}
}
	
void CSeatDumpTrigger::beforeRemove(CSeat *pSeat)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Seat,del");
		pSeat->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove Seat\n");
		pSeat->dump(m_output);
#endif
		fflush(m_output);
	}
}

CInstrumentDumpTrigger::CInstrumentDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CInstrumentDumpTrigger::~CInstrumentDumpTrigger(void)
{
}


void CInstrumentDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CInstrumentDumpTrigger");
	pLogger->output(indent,0,"CInstrumentDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CInstrumentDumpTrigger::beforeAdd(CWriteableInstrument *pInstrument)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Instrument,add");
		pInstrument->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add Instrument\n");
		pInstrument->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CInstrumentDumpTrigger::beforeUpdate(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Instrument,upd");
		pNewInstrument->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update Instrument\n");
		pNewInstrument->dumpDiff(m_output,pInstrument);
#endif
		fflush(m_output);
	}
}
	
void CInstrumentDumpTrigger::beforeRemove(CInstrument *pInstrument)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Instrument,del");
		pInstrument->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove Instrument\n");
		pInstrument->dump(m_output);
#endif
		fflush(m_output);
	}
}

CCmbInstrumentDetailDumpTrigger::CCmbInstrumentDetailDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CCmbInstrumentDetailDumpTrigger::~CCmbInstrumentDetailDumpTrigger(void)
{
}


void CCmbInstrumentDetailDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CCmbInstrumentDetailDumpTrigger");
	pLogger->output(indent,0,"CCmbInstrumentDetailDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CCmbInstrumentDetailDumpTrigger::beforeAdd(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"CmbInstrumentDetail,add");
		pCmbInstrumentDetail->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add CmbInstrumentDetail\n");
		pCmbInstrumentDetail->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CCmbInstrumentDetailDumpTrigger::beforeUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"CmbInstrumentDetail,upd");
		pNewCmbInstrumentDetail->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update CmbInstrumentDetail\n");
		pNewCmbInstrumentDetail->dumpDiff(m_output,pCmbInstrumentDetail);
#endif
		fflush(m_output);
	}
}
	
void CCmbInstrumentDetailDumpTrigger::beforeRemove(CCmbInstrumentDetail *pCmbInstrumentDetail)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"CmbInstrumentDetail,del");
		pCmbInstrumentDetail->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove CmbInstrumentDetail\n");
		pCmbInstrumentDetail->dump(m_output);
#endif
		fflush(m_output);
	}
}

CClientTradingIDDumpTrigger::CClientTradingIDDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CClientTradingIDDumpTrigger::~CClientTradingIDDumpTrigger(void)
{
}


void CClientTradingIDDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CClientTradingIDDumpTrigger");
	pLogger->output(indent,0,"CClientTradingIDDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CClientTradingIDDumpTrigger::beforeAdd(CWriteableClientTradingID *pClientTradingID)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"ClientTradingID,add");
		pClientTradingID->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add ClientTradingID\n");
		pClientTradingID->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CClientTradingIDDumpTrigger::beforeUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"ClientTradingID,upd");
		pNewClientTradingID->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update ClientTradingID\n");
		pNewClientTradingID->dumpDiff(m_output,pClientTradingID);
#endif
		fflush(m_output);
	}
}
	
void CClientTradingIDDumpTrigger::beforeRemove(CClientTradingID *pClientTradingID)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"ClientTradingID,del");
		pClientTradingID->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove ClientTradingID\n");
		pClientTradingID->dump(m_output);
#endif
		fflush(m_output);
	}
}

CInvestorDumpTrigger::CInvestorDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CInvestorDumpTrigger::~CInvestorDumpTrigger(void)
{
}


void CInvestorDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CInvestorDumpTrigger");
	pLogger->output(indent,0,"CInvestorDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CInvestorDumpTrigger::beforeAdd(CWriteableInvestor *pInvestor)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Investor,add");
		pInvestor->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add Investor\n");
		pInvestor->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CInvestorDumpTrigger::beforeUpdate(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Investor,upd");
		pNewInvestor->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update Investor\n");
		pNewInvestor->dumpDiff(m_output,pInvestor);
#endif
		fflush(m_output);
	}
}
	
void CInvestorDumpTrigger::beforeRemove(CInvestor *pInvestor)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"Investor,del");
		pInvestor->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove Investor\n");
		pInvestor->dump(m_output);
#endif
		fflush(m_output);
	}
}

CInvestorMarginDumpTrigger::CInvestorMarginDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CInvestorMarginDumpTrigger::~CInvestorMarginDumpTrigger(void)
{
}


void CInvestorMarginDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CInvestorMarginDumpTrigger");
	pLogger->output(indent,0,"CInvestorMarginDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CInvestorMarginDumpTrigger::beforeAdd(CWriteableInvestorMargin *pInvestorMargin)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorMargin,add");
		pInvestorMargin->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add InvestorMargin\n");
		pInvestorMargin->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CInvestorMarginDumpTrigger::beforeUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorMargin,upd");
		pNewInvestorMargin->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update InvestorMargin\n");
		pNewInvestorMargin->dumpDiff(m_output,pInvestorMargin);
#endif
		fflush(m_output);
	}
}
	
void CInvestorMarginDumpTrigger::beforeRemove(CInvestorMargin *pInvestorMargin)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorMargin,del");
		pInvestorMargin->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove InvestorMargin\n");
		pInvestorMargin->dump(m_output);
#endif
		fflush(m_output);
	}
}

CInvestorFeeDumpTrigger::CInvestorFeeDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CInvestorFeeDumpTrigger::~CInvestorFeeDumpTrigger(void)
{
}


void CInvestorFeeDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CInvestorFeeDumpTrigger");
	pLogger->output(indent,0,"CInvestorFeeDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CInvestorFeeDumpTrigger::beforeAdd(CWriteableInvestorFee *pInvestorFee)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorFee,add");
		pInvestorFee->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add InvestorFee\n");
		pInvestorFee->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CInvestorFeeDumpTrigger::beforeUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorFee,upd");
		pNewInvestorFee->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update InvestorFee\n");
		pNewInvestorFee->dumpDiff(m_output,pInvestorFee);
#endif
		fflush(m_output);
	}
}
	
void CInvestorFeeDumpTrigger::beforeRemove(CInvestorFee *pInvestorFee)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorFee,del");
		pInvestorFee->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove InvestorFee\n");
		pInvestorFee->dump(m_output);
#endif
		fflush(m_output);
	}
}

CUserDumpTrigger::CUserDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CUserDumpTrigger::~CUserDumpTrigger(void)
{
}


void CUserDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CUserDumpTrigger");
	pLogger->output(indent,0,"CUserDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CUserDumpTrigger::beforeAdd(CWriteableUser *pUser)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"User,add");
		pUser->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add User\n");
		pUser->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CUserDumpTrigger::beforeUpdate(CUser *pUser, CWriteableUser *pNewUser)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"User,upd");
		pNewUser->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update User\n");
		pNewUser->dumpDiff(m_output,pUser);
#endif
		fflush(m_output);
	}
}
	
void CUserDumpTrigger::beforeRemove(CUser *pUser)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"User,del");
		pUser->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove User\n");
		pUser->dump(m_output);
#endif
		fflush(m_output);
	}
}

CUserInvestorDumpTrigger::CUserInvestorDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CUserInvestorDumpTrigger::~CUserInvestorDumpTrigger(void)
{
}


void CUserInvestorDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CUserInvestorDumpTrigger");
	pLogger->output(indent,0,"CUserInvestorDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CUserInvestorDumpTrigger::beforeAdd(CWriteableUserInvestor *pUserInvestor)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"UserInvestor,add");
		pUserInvestor->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add UserInvestor\n");
		pUserInvestor->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CUserInvestorDumpTrigger::beforeUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"UserInvestor,upd");
		pNewUserInvestor->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update UserInvestor\n");
		pNewUserInvestor->dumpDiff(m_output,pUserInvestor);
#endif
		fflush(m_output);
	}
}
	
void CUserInvestorDumpTrigger::beforeRemove(CUserInvestor *pUserInvestor)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"UserInvestor,del");
		pUserInvestor->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove UserInvestor\n");
		pUserInvestor->dump(m_output);
#endif
		fflush(m_output);
	}
}

COrderInsertFailedDumpTrigger::COrderInsertFailedDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

COrderInsertFailedDumpTrigger::~COrderInsertFailedDumpTrigger(void)
{
}


void COrderInsertFailedDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("COrderInsertFailedDumpTrigger");
	pLogger->output(indent,0,"COrderInsertFailedDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void COrderInsertFailedDumpTrigger::beforeAdd(CWriteableOrderInsertFailed *pOrderInsertFailed)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"OrderInsertFailed,add");
		pOrderInsertFailed->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add OrderInsertFailed\n");
		pOrderInsertFailed->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void COrderInsertFailedDumpTrigger::beforeUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"OrderInsertFailed,upd");
		pNewOrderInsertFailed->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update OrderInsertFailed\n");
		pNewOrderInsertFailed->dumpDiff(m_output,pOrderInsertFailed);
#endif
		fflush(m_output);
	}
}
	
void COrderInsertFailedDumpTrigger::beforeRemove(COrderInsertFailed *pOrderInsertFailed)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"OrderInsertFailed,del");
		pOrderInsertFailed->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove OrderInsertFailed\n");
		pOrderInsertFailed->dump(m_output);
#endif
		fflush(m_output);
	}
}

CUserTradingRightDumpTrigger::CUserTradingRightDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CUserTradingRightDumpTrigger::~CUserTradingRightDumpTrigger(void)
{
}


void CUserTradingRightDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CUserTradingRightDumpTrigger");
	pLogger->output(indent,0,"CUserTradingRightDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CUserTradingRightDumpTrigger::beforeAdd(CWriteableUserTradingRight *pUserTradingRight)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"UserTradingRight,add");
		pUserTradingRight->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add UserTradingRight\n");
		pUserTradingRight->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CUserTradingRightDumpTrigger::beforeUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"UserTradingRight,upd");
		pNewUserTradingRight->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update UserTradingRight\n");
		pNewUserTradingRight->dumpDiff(m_output,pUserTradingRight);
#endif
		fflush(m_output);
	}
}
	
void CUserTradingRightDumpTrigger::beforeRemove(CUserTradingRight *pUserTradingRight)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"UserTradingRight,del");
		pUserTradingRight->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove UserTradingRight\n");
		pUserTradingRight->dump(m_output);
#endif
		fflush(m_output);
	}
}

CCurrentTimeDumpTrigger::CCurrentTimeDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CCurrentTimeDumpTrigger::~CCurrentTimeDumpTrigger(void)
{
}


void CCurrentTimeDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CCurrentTimeDumpTrigger");
	pLogger->output(indent,0,"CCurrentTimeDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CCurrentTimeDumpTrigger::beforeAdd(CWriteableCurrentTime *pCurrentTime)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"CurrentTime,add");
		pCurrentTime->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add CurrentTime\n");
		pCurrentTime->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CCurrentTimeDumpTrigger::beforeUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"CurrentTime,upd");
		pNewCurrentTime->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update CurrentTime\n");
		pNewCurrentTime->dumpDiff(m_output,pCurrentTime);
#endif
		fflush(m_output);
	}
}
	
void CCurrentTimeDumpTrigger::beforeRemove(CCurrentTime *pCurrentTime)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"CurrentTime,del");
		pCurrentTime->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove CurrentTime\n");
		pCurrentTime->dump(m_output);
#endif
		fflush(m_output);
	}
}

CUserSessionDumpTrigger::CUserSessionDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CUserSessionDumpTrigger::~CUserSessionDumpTrigger(void)
{
}


void CUserSessionDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CUserSessionDumpTrigger");
	pLogger->output(indent,0,"CUserSessionDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CUserSessionDumpTrigger::beforeAdd(CWriteableUserSession *pUserSession)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"UserSession,add");
		pUserSession->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add UserSession\n");
		pUserSession->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CUserSessionDumpTrigger::beforeUpdate(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"UserSession,upd");
		pNewUserSession->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update UserSession\n");
		pNewUserSession->dumpDiff(m_output,pUserSession);
#endif
		fflush(m_output);
	}
}
	
void CUserSessionDumpTrigger::beforeRemove(CUserSession *pUserSession)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"UserSession,del");
		pUserSession->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove UserSession\n");
		pUserSession->dump(m_output);
#endif
		fflush(m_output);
	}
}

CMaxLocalIDDumpTrigger::CMaxLocalIDDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CMaxLocalIDDumpTrigger::~CMaxLocalIDDumpTrigger(void)
{
}


void CMaxLocalIDDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CMaxLocalIDDumpTrigger");
	pLogger->output(indent,0,"CMaxLocalIDDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CMaxLocalIDDumpTrigger::beforeAdd(CWriteableMaxLocalID *pMaxLocalID)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"MaxLocalID,add");
		pMaxLocalID->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add MaxLocalID\n");
		pMaxLocalID->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CMaxLocalIDDumpTrigger::beforeUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"MaxLocalID,upd");
		pNewMaxLocalID->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update MaxLocalID\n");
		pNewMaxLocalID->dumpDiff(m_output,pMaxLocalID);
#endif
		fflush(m_output);
	}
}
	
void CMaxLocalIDDumpTrigger::beforeRemove(CMaxLocalID *pMaxLocalID)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"MaxLocalID,del");
		pMaxLocalID->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove MaxLocalID\n");
		pMaxLocalID->dump(m_output);
#endif
		fflush(m_output);
	}
}

CBrkUserIDLocalIDDumpTrigger::CBrkUserIDLocalIDDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CBrkUserIDLocalIDDumpTrigger::~CBrkUserIDLocalIDDumpTrigger(void)
{
}


void CBrkUserIDLocalIDDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CBrkUserIDLocalIDDumpTrigger");
	pLogger->output(indent,0,"CBrkUserIDLocalIDDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CBrkUserIDLocalIDDumpTrigger::beforeAdd(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"BrkUserIDLocalID,add");
		pBrkUserIDLocalID->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add BrkUserIDLocalID\n");
		pBrkUserIDLocalID->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CBrkUserIDLocalIDDumpTrigger::beforeUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"BrkUserIDLocalID,upd");
		pNewBrkUserIDLocalID->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update BrkUserIDLocalID\n");
		pNewBrkUserIDLocalID->dumpDiff(m_output,pBrkUserIDLocalID);
#endif
		fflush(m_output);
	}
}
	
void CBrkUserIDLocalIDDumpTrigger::beforeRemove(CBrkUserIDLocalID *pBrkUserIDLocalID)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"BrkUserIDLocalID,del");
		pBrkUserIDLocalID->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove BrkUserIDLocalID\n");
		pBrkUserIDLocalID->dump(m_output);
#endif
		fflush(m_output);
	}
}

CPartClientInsGroupPositionDumpTrigger::CPartClientInsGroupPositionDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CPartClientInsGroupPositionDumpTrigger::~CPartClientInsGroupPositionDumpTrigger(void)
{
}


void CPartClientInsGroupPositionDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CPartClientInsGroupPositionDumpTrigger");
	pLogger->output(indent,0,"CPartClientInsGroupPositionDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CPartClientInsGroupPositionDumpTrigger::beforeAdd(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"PartClientInsGroupPosition,add");
		pPartClientInsGroupPosition->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add PartClientInsGroupPosition\n");
		pPartClientInsGroupPosition->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CPartClientInsGroupPositionDumpTrigger::beforeUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"PartClientInsGroupPosition,upd");
		pNewPartClientInsGroupPosition->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update PartClientInsGroupPosition\n");
		pNewPartClientInsGroupPosition->dumpDiff(m_output,pPartClientInsGroupPosition);
#endif
		fflush(m_output);
	}
}
	
void CPartClientInsGroupPositionDumpTrigger::beforeRemove(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"PartClientInsGroupPosition,del");
		pPartClientInsGroupPosition->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove PartClientInsGroupPosition\n");
		pPartClientInsGroupPosition->dump(m_output);
#endif
		fflush(m_output);
	}
}

CClientMarginCombTypeDumpTrigger::CClientMarginCombTypeDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CClientMarginCombTypeDumpTrigger::~CClientMarginCombTypeDumpTrigger(void)
{
}


void CClientMarginCombTypeDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CClientMarginCombTypeDumpTrigger");
	pLogger->output(indent,0,"CClientMarginCombTypeDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CClientMarginCombTypeDumpTrigger::beforeAdd(CWriteableClientMarginCombType *pClientMarginCombType)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"ClientMarginCombType,add");
		pClientMarginCombType->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add ClientMarginCombType\n");
		pClientMarginCombType->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CClientMarginCombTypeDumpTrigger::beforeUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"ClientMarginCombType,upd");
		pNewClientMarginCombType->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update ClientMarginCombType\n");
		pNewClientMarginCombType->dumpDiff(m_output,pClientMarginCombType);
#endif
		fflush(m_output);
	}
}
	
void CClientMarginCombTypeDumpTrigger::beforeRemove(CClientMarginCombType *pClientMarginCombType)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"ClientMarginCombType,del");
		pClientMarginCombType->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove ClientMarginCombType\n");
		pClientMarginCombType->dump(m_output);
#endif
		fflush(m_output);
	}
}

CInstrumentGroupDumpTrigger::CInstrumentGroupDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CInstrumentGroupDumpTrigger::~CInstrumentGroupDumpTrigger(void)
{
}


void CInstrumentGroupDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CInstrumentGroupDumpTrigger");
	pLogger->output(indent,0,"CInstrumentGroupDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CInstrumentGroupDumpTrigger::beforeAdd(CWriteableInstrumentGroup *pInstrumentGroup)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InstrumentGroup,add");
		pInstrumentGroup->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add InstrumentGroup\n");
		pInstrumentGroup->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CInstrumentGroupDumpTrigger::beforeUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InstrumentGroup,upd");
		pNewInstrumentGroup->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update InstrumentGroup\n");
		pNewInstrumentGroup->dumpDiff(m_output,pInstrumentGroup);
#endif
		fflush(m_output);
	}
}
	
void CInstrumentGroupDumpTrigger::beforeRemove(CInstrumentGroup *pInstrumentGroup)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InstrumentGroup,del");
		pInstrumentGroup->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove InstrumentGroup\n");
		pInstrumentGroup->dump(m_output);
#endif
		fflush(m_output);
	}
}

CSGEDeferRateDumpTrigger::CSGEDeferRateDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CSGEDeferRateDumpTrigger::~CSGEDeferRateDumpTrigger(void)
{
}


void CSGEDeferRateDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CSGEDeferRateDumpTrigger");
	pLogger->output(indent,0,"CSGEDeferRateDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CSGEDeferRateDumpTrigger::beforeAdd(CWriteableSGEDeferRate *pSGEDeferRate)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"SGEDeferRate,add");
		pSGEDeferRate->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add SGEDeferRate\n");
		pSGEDeferRate->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CSGEDeferRateDumpTrigger::beforeUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"SGEDeferRate,upd");
		pNewSGEDeferRate->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update SGEDeferRate\n");
		pNewSGEDeferRate->dumpDiff(m_output,pSGEDeferRate);
#endif
		fflush(m_output);
	}
}
	
void CSGEDeferRateDumpTrigger::beforeRemove(CSGEDeferRate *pSGEDeferRate)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"SGEDeferRate,del");
		pSGEDeferRate->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove SGEDeferRate\n");
		pSGEDeferRate->dump(m_output);
#endif
		fflush(m_output);
	}
}

CInvestorTradingRightDumpTrigger::CInvestorTradingRightDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CInvestorTradingRightDumpTrigger::~CInvestorTradingRightDumpTrigger(void)
{
}


void CInvestorTradingRightDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CInvestorTradingRightDumpTrigger");
	pLogger->output(indent,0,"CInvestorTradingRightDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CInvestorTradingRightDumpTrigger::beforeAdd(CWriteableInvestorTradingRight *pInvestorTradingRight)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorTradingRight,add");
		pInvestorTradingRight->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add InvestorTradingRight\n");
		pInvestorTradingRight->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CInvestorTradingRightDumpTrigger::beforeUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorTradingRight,upd");
		pNewInvestorTradingRight->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update InvestorTradingRight\n");
		pNewInvestorTradingRight->dumpDiff(m_output,pInvestorTradingRight);
#endif
		fflush(m_output);
	}
}
	
void CInvestorTradingRightDumpTrigger::beforeRemove(CInvestorTradingRight *pInvestorTradingRight)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorTradingRight,del");
		pInvestorTradingRight->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove InvestorTradingRight\n");
		pInvestorTradingRight->dump(m_output);
#endif
		fflush(m_output);
	}
}

CUserIPDumpTrigger::CUserIPDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CUserIPDumpTrigger::~CUserIPDumpTrigger(void)
{
}


void CUserIPDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CUserIPDumpTrigger");
	pLogger->output(indent,0,"CUserIPDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CUserIPDumpTrigger::beforeAdd(CWriteableUserIP *pUserIP)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"UserIP,add");
		pUserIP->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add UserIP\n");
		pUserIP->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CUserIPDumpTrigger::beforeUpdate(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"UserIP,upd");
		pNewUserIP->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update UserIP\n");
		pNewUserIP->dumpDiff(m_output,pUserIP);
#endif
		fflush(m_output);
	}
}
	
void CUserIPDumpTrigger::beforeRemove(CUserIP *pUserIP)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"UserIP,del");
		pUserIP->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove UserIP\n");
		pUserIP->dump(m_output);
#endif
		fflush(m_output);
	}
}

CInvestorOptionFeeDumpTrigger::CInvestorOptionFeeDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CInvestorOptionFeeDumpTrigger::~CInvestorOptionFeeDumpTrigger(void)
{
}


void CInvestorOptionFeeDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CInvestorOptionFeeDumpTrigger");
	pLogger->output(indent,0,"CInvestorOptionFeeDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CInvestorOptionFeeDumpTrigger::beforeAdd(CWriteableInvestorOptionFee *pInvestorOptionFee)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorOptionFee,add");
		pInvestorOptionFee->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add InvestorOptionFee\n");
		pInvestorOptionFee->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CInvestorOptionFeeDumpTrigger::beforeUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorOptionFee,upd");
		pNewInvestorOptionFee->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update InvestorOptionFee\n");
		pNewInvestorOptionFee->dumpDiff(m_output,pInvestorOptionFee);
#endif
		fflush(m_output);
	}
}
	
void CInvestorOptionFeeDumpTrigger::beforeRemove(CInvestorOptionFee *pInvestorOptionFee)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"InvestorOptionFee,del");
		pInvestorOptionFee->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove InvestorOptionFee\n");
		pInvestorOptionFee->dump(m_output);
#endif
		fflush(m_output);
	}
}

CMarketDataDumpTrigger::CMarketDataDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CMarketDataDumpTrigger::~CMarketDataDumpTrigger(void)
{
}


void CMarketDataDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CMarketDataDumpTrigger");
	pLogger->output(indent,0,"CMarketDataDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CMarketDataDumpTrigger::beforeAdd(CWriteableMarketData *pMarketData)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"MarketData,add");
		pMarketData->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add MarketData\n");
		pMarketData->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CMarketDataDumpTrigger::beforeUpdate(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"MarketData,upd");
		pNewMarketData->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update MarketData\n");
		pNewMarketData->dumpDiff(m_output,pMarketData);
#endif
		fflush(m_output);
	}
}
	
void CMarketDataDumpTrigger::beforeRemove(CMarketData *pMarketData)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"MarketData,del");
		pMarketData->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove MarketData\n");
		pMarketData->dump(m_output);
#endif
		fflush(m_output);
	}
}

COrderDelayDumpTrigger::COrderDelayDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

COrderDelayDumpTrigger::~COrderDelayDumpTrigger(void)
{
}


void COrderDelayDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("COrderDelayDumpTrigger");
	pLogger->output(indent,0,"COrderDelayDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void COrderDelayDumpTrigger::beforeAdd(CWriteableOrderDelay *pOrderDelay)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"OrderDelay,add");
		pOrderDelay->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add OrderDelay\n");
		pOrderDelay->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void COrderDelayDumpTrigger::beforeUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"OrderDelay,upd");
		pNewOrderDelay->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update OrderDelay\n");
		pNewOrderDelay->dumpDiff(m_output,pOrderDelay);
#endif
		fflush(m_output);
	}
}
	
void COrderDelayDumpTrigger::beforeRemove(COrderDelay *pOrderDelay)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"OrderDelay,del");
		pOrderDelay->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove OrderDelay\n");
		pOrderDelay->dump(m_output);
#endif
		fflush(m_output);
	}
}

CSystemInfoDumpTrigger::CSystemInfoDumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

CSystemInfoDumpTrigger::~CSystemInfoDumpTrigger(void)
{
}


void CSystemInfoDumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("CSystemInfoDumpTrigger");
	pLogger->output(indent,0,"CSystemInfoDumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void CSystemInfoDumpTrigger::beforeAdd(CWriteableSystemInfo *pSystemInfo)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"SystemInfo,add");
		pSystemInfo->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add SystemInfo\n");
		pSystemInfo->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void CSystemInfoDumpTrigger::beforeUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"SystemInfo,upd");
		pNewSystemInfo->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update SystemInfo\n");
		pNewSystemInfo->dumpDiff(m_output,pSystemInfo);
#endif
		fflush(m_output);
	}
}
	
void CSystemInfoDumpTrigger::beforeRemove(CSystemInfo *pSystemInfo)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"SystemInfo,del");
		pSystemInfo->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove SystemInfo\n");
		pSystemInfo->dump(m_output);
#endif
		fflush(m_output);
	}
}

CDumpLog::CDumpLog(CMemoryDB *pDB, CConfig *pConfig)
{
	char *fileName=pConfig->getConfig("DumpOutput");

	// 2013-1-18 longqy 把下面这行提到前面来了。之前有可能会没有初始化就使用。
	m_Started=0;

	if (*fileName=='\0')
	{
		m_DumpOutput=NULL;
		return;
	}
	if (!strcmp(fileName,"stdout"))
	{
		m_DumpOutput=stdout;
	}
	else if (!strcmp(fileName,"stderr"))
	{
		m_DumpOutput=stderr;
	}
	else
	{
		m_DumpOutput=mfopen(fileName,"wt");
	}
	if (m_DumpOutput==NULL)
	{
		REPORT_EVENT(LOG_INFO,"EnvError","write dump file failed");
		return;
	}
	m_DB=pDB;
	// m_Started=0;

	m_DataSyncStatusTrigger=new CDataSyncStatusDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_SystemStatusTrigger=new CSystemStatusDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_OrderActionTrigger=new COrderActionDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_OrderTrigger=new COrderDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_TradeTrigger=new CTradeDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_PreOrderTrigger=new CPreOrderDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_IndexPreOrderTrigger=new CIndexPreOrderDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_InvestorPositionTrigger=new CInvestorPositionDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_InvestorAccountTrigger=new CInvestorAccountDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_InvestorAccountDepositTrigger=new CInvestorAccountDepositDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_ExchangeTrigger=new CExchangeDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_SeatTrigger=new CSeatDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_InstrumentTrigger=new CInstrumentDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_CmbInstrumentDetailTrigger=new CCmbInstrumentDetailDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_ClientTradingIDTrigger=new CClientTradingIDDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_InvestorTrigger=new CInvestorDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_InvestorMarginTrigger=new CInvestorMarginDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_InvestorFeeTrigger=new CInvestorFeeDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_UserTrigger=new CUserDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_UserInvestorTrigger=new CUserInvestorDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_OrderInsertFailedTrigger=new COrderInsertFailedDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_UserTradingRightTrigger=new CUserTradingRightDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_CurrentTimeTrigger=new CCurrentTimeDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_UserSessionTrigger=new CUserSessionDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_MaxLocalIDTrigger=new CMaxLocalIDDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_BrkUserIDLocalIDTrigger=new CBrkUserIDLocalIDDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_PartClientInsGroupPositionTrigger=new CPartClientInsGroupPositionDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_ClientMarginCombTypeTrigger=new CClientMarginCombTypeDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_InstrumentGroupTrigger=new CInstrumentGroupDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_SGEDeferRateTrigger=new CSGEDeferRateDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_InvestorTradingRightTrigger=new CInvestorTradingRightDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_UserIPTrigger=new CUserIPDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_InvestorOptionFeeTrigger=new CInvestorOptionFeeDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_MarketDataTrigger=new CMarketDataDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_OrderDelayTrigger=new COrderDelayDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	m_SystemInfoTrigger=new CSystemInfoDumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
}

CDumpLog::~CDumpLog(void)
{
	stop();
	if (m_DumpOutput==NULL)
	{
		return;
	}
	delete m_DataSyncStatusTrigger;
	delete m_SystemStatusTrigger;
	delete m_OrderActionTrigger;
	delete m_OrderTrigger;
	delete m_TradeTrigger;
	delete m_PreOrderTrigger;
	delete m_IndexPreOrderTrigger;
	delete m_InvestorPositionTrigger;
	delete m_InvestorAccountTrigger;
	delete m_InvestorAccountDepositTrigger;
	delete m_ExchangeTrigger;
	delete m_SeatTrigger;
	delete m_InstrumentTrigger;
	delete m_CmbInstrumentDetailTrigger;
	delete m_ClientTradingIDTrigger;
	delete m_InvestorTrigger;
	delete m_InvestorMarginTrigger;
	delete m_InvestorFeeTrigger;
	delete m_UserTrigger;
	delete m_UserInvestorTrigger;
	delete m_OrderInsertFailedTrigger;
	delete m_UserTradingRightTrigger;
	delete m_CurrentTimeTrigger;
	delete m_UserSessionTrigger;
	delete m_MaxLocalIDTrigger;
	delete m_BrkUserIDLocalIDTrigger;
	delete m_PartClientInsGroupPositionTrigger;
	delete m_ClientMarginCombTypeTrigger;
	delete m_InstrumentGroupTrigger;
	delete m_SGEDeferRateTrigger;
	delete m_InvestorTradingRightTrigger;
	delete m_UserIPTrigger;
	delete m_InvestorOptionFeeTrigger;
	delete m_MarketDataTrigger;
	delete m_OrderDelayTrigger;
	delete m_SystemInfoTrigger;
	if ((m_DumpOutput!=NULL)&&(m_DumpOutput!=stdout)&&(m_DumpOutput!=stderr))
	{
		fclose(m_DumpOutput);
	}
}

int CDumpLog::isStarted(void)
{
	return m_Started;
}

void CDumpLog::start(void)
{
	if (m_Started)
	{
		return;
	}
	if (m_DumpOutput==NULL)
	{
		return;
	}
	m_DB->m_DataSyncStatusFactory->addActionTrigger(m_DataSyncStatusTrigger);
	m_DB->m_SystemStatusFactory->addActionTrigger(m_SystemStatusTrigger);
	m_DB->m_OrderActionFactory->addActionTrigger(m_OrderActionTrigger);
	m_DB->m_OrderFactory->addActionTrigger(m_OrderTrigger);
	m_DB->m_TradeFactory->addActionTrigger(m_TradeTrigger);
	m_DB->m_PreOrderFactory->addActionTrigger(m_PreOrderTrigger);
	m_DB->m_IndexPreOrderFactory->addActionTrigger(m_IndexPreOrderTrigger);
	m_DB->m_InvestorPositionFactory->addActionTrigger(m_InvestorPositionTrigger);
	m_DB->m_InvestorAccountFactory->addActionTrigger(m_InvestorAccountTrigger);
	m_DB->m_InvestorAccountDepositFactory->addActionTrigger(m_InvestorAccountDepositTrigger);
	m_DB->m_ExchangeFactory->addActionTrigger(m_ExchangeTrigger);
	m_DB->m_SeatFactory->addActionTrigger(m_SeatTrigger);
	m_DB->m_InstrumentFactory->addActionTrigger(m_InstrumentTrigger);
	m_DB->m_CmbInstrumentDetailFactory->addActionTrigger(m_CmbInstrumentDetailTrigger);
	m_DB->m_ClientTradingIDFactory->addActionTrigger(m_ClientTradingIDTrigger);
	m_DB->m_InvestorFactory->addActionTrigger(m_InvestorTrigger);
	m_DB->m_InvestorMarginFactory->addActionTrigger(m_InvestorMarginTrigger);
	m_DB->m_InvestorFeeFactory->addActionTrigger(m_InvestorFeeTrigger);
	m_DB->m_UserFactory->addActionTrigger(m_UserTrigger);
	m_DB->m_UserInvestorFactory->addActionTrigger(m_UserInvestorTrigger);
	m_DB->m_OrderInsertFailedFactory->addActionTrigger(m_OrderInsertFailedTrigger);
	m_DB->m_UserTradingRightFactory->addActionTrigger(m_UserTradingRightTrigger);
	m_DB->m_CurrentTimeFactory->addActionTrigger(m_CurrentTimeTrigger);
	m_DB->m_UserSessionFactory->addActionTrigger(m_UserSessionTrigger);
	m_DB->m_MaxLocalIDFactory->addActionTrigger(m_MaxLocalIDTrigger);
	m_DB->m_BrkUserIDLocalIDFactory->addActionTrigger(m_BrkUserIDLocalIDTrigger);
	m_DB->m_PartClientInsGroupPositionFactory->addActionTrigger(m_PartClientInsGroupPositionTrigger);
	m_DB->m_ClientMarginCombTypeFactory->addActionTrigger(m_ClientMarginCombTypeTrigger);
	m_DB->m_InstrumentGroupFactory->addActionTrigger(m_InstrumentGroupTrigger);
	m_DB->m_SGEDeferRateFactory->addActionTrigger(m_SGEDeferRateTrigger);
	m_DB->m_InvestorTradingRightFactory->addActionTrigger(m_InvestorTradingRightTrigger);
	m_DB->m_UserIPFactory->addActionTrigger(m_UserIPTrigger);
	m_DB->m_InvestorOptionFeeFactory->addActionTrigger(m_InvestorOptionFeeTrigger);
	m_DB->m_MarketDataFactory->addActionTrigger(m_MarketDataTrigger);
	m_DB->m_OrderDelayFactory->addActionTrigger(m_OrderDelayTrigger);
	m_DB->m_SystemInfoFactory->addActionTrigger(m_SystemInfoTrigger);

	// 2013-1-18 longqy 添加下面一行，相当改变其状态后，给这个参数赋正确的值。
	m_Started=1;
}

void CDumpLog::stop()
{
	if (!m_Started)
	{
		return;
	}
	if (m_DumpOutput==NULL)
	{
		return;
	}
	m_DB->m_DataSyncStatusFactory->removeActionTrigger(m_DataSyncStatusTrigger);
	m_DB->m_SystemStatusFactory->removeActionTrigger(m_SystemStatusTrigger);
	m_DB->m_OrderActionFactory->removeActionTrigger(m_OrderActionTrigger);
	m_DB->m_OrderFactory->removeActionTrigger(m_OrderTrigger);
	m_DB->m_TradeFactory->removeActionTrigger(m_TradeTrigger);
	m_DB->m_PreOrderFactory->removeActionTrigger(m_PreOrderTrigger);
	m_DB->m_IndexPreOrderFactory->removeActionTrigger(m_IndexPreOrderTrigger);
	m_DB->m_InvestorPositionFactory->removeActionTrigger(m_InvestorPositionTrigger);
	m_DB->m_InvestorAccountFactory->removeActionTrigger(m_InvestorAccountTrigger);
	m_DB->m_InvestorAccountDepositFactory->removeActionTrigger(m_InvestorAccountDepositTrigger);
	m_DB->m_ExchangeFactory->removeActionTrigger(m_ExchangeTrigger);
	m_DB->m_SeatFactory->removeActionTrigger(m_SeatTrigger);
	m_DB->m_InstrumentFactory->removeActionTrigger(m_InstrumentTrigger);
	m_DB->m_CmbInstrumentDetailFactory->removeActionTrigger(m_CmbInstrumentDetailTrigger);
	m_DB->m_ClientTradingIDFactory->removeActionTrigger(m_ClientTradingIDTrigger);
	m_DB->m_InvestorFactory->removeActionTrigger(m_InvestorTrigger);
	m_DB->m_InvestorMarginFactory->removeActionTrigger(m_InvestorMarginTrigger);
	m_DB->m_InvestorFeeFactory->removeActionTrigger(m_InvestorFeeTrigger);
	m_DB->m_UserFactory->removeActionTrigger(m_UserTrigger);
	m_DB->m_UserInvestorFactory->removeActionTrigger(m_UserInvestorTrigger);
	m_DB->m_OrderInsertFailedFactory->removeActionTrigger(m_OrderInsertFailedTrigger);
	m_DB->m_UserTradingRightFactory->removeActionTrigger(m_UserTradingRightTrigger);
	m_DB->m_CurrentTimeFactory->removeActionTrigger(m_CurrentTimeTrigger);
	m_DB->m_UserSessionFactory->removeActionTrigger(m_UserSessionTrigger);
	m_DB->m_MaxLocalIDFactory->removeActionTrigger(m_MaxLocalIDTrigger);
	m_DB->m_BrkUserIDLocalIDFactory->removeActionTrigger(m_BrkUserIDLocalIDTrigger);
	m_DB->m_PartClientInsGroupPositionFactory->removeActionTrigger(m_PartClientInsGroupPositionTrigger);
	m_DB->m_ClientMarginCombTypeFactory->removeActionTrigger(m_ClientMarginCombTypeTrigger);
	m_DB->m_InstrumentGroupFactory->removeActionTrigger(m_InstrumentGroupTrigger);
	m_DB->m_SGEDeferRateFactory->removeActionTrigger(m_SGEDeferRateTrigger);
	m_DB->m_InvestorTradingRightFactory->removeActionTrigger(m_InvestorTradingRightTrigger);
	m_DB->m_UserIPFactory->removeActionTrigger(m_UserIPTrigger);
	m_DB->m_InvestorOptionFeeFactory->removeActionTrigger(m_InvestorOptionFeeTrigger);
	m_DB->m_MarketDataFactory->removeActionTrigger(m_MarketDataTrigger);
	m_DB->m_OrderDelayFactory->removeActionTrigger(m_OrderDelayTrigger);
	m_DB->m_SystemInfoFactory->removeActionTrigger(m_SystemInfoTrigger);
	
	// 2013-1-18 longqy 添加下面一行，相当改变其状态后，给这个参数赋正确的值。
	m_Started=0;
}

void CDumpLog::dumpMsg(char *format,...)
{
	va_list v;
	
	if (!m_Started)
	{
		return;
	}
	
	va_start(v,format);
	vfprintf(m_DumpOutput,format,v);
	va_end(v);
	fflush(m_DumpOutput);
}

