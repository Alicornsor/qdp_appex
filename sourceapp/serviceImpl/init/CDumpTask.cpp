/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company 上海量投网络科技有限公司
///@file CDumpTask.cpp
///@brief	实现了类CDumpTask和相关类
///@history 
///20091203	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CDumpTask.h"


CDumpDataSyncStatusTask::CDumpDataSyncStatusTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_DataSyncStatusFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "DataSyncStatus.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpDataSyncStatusTask::~CDumpDataSyncStatusTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpDataSyncStatusTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableDataSyncStatus::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableDataSyncStatus[m_size];
		m_next=0;
		CDataSyncStatus *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpSystemStatusTask::CDumpSystemStatusTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_SystemStatusFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "SystemStatus.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpSystemStatusTask::~CDumpSystemStatusTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpSystemStatusTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableSystemStatus::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableSystemStatus[m_size];
		m_next=0;
		CSystemStatus *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpOrderActionTask::CDumpOrderActionTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_OrderActionFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "OrderAction.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpOrderActionTask::~CDumpOrderActionTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpOrderActionTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableOrderAction::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableOrderAction[m_size];
		m_next=0;
		COrderAction *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpOrderTask::CDumpOrderTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_OrderFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "Order.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpOrderTask::~CDumpOrderTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpOrderTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableOrder::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableOrder[m_size];
		m_next=0;
		COrder *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpTradeTask::CDumpTradeTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_TradeFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "Trade.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpTradeTask::~CDumpTradeTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpTradeTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableTrade::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableTrade[m_size];
		m_next=0;
		CTrade *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpPreOrderTask::CDumpPreOrderTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_PreOrderFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "PreOrder.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpPreOrderTask::~CDumpPreOrderTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpPreOrderTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteablePreOrder::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteablePreOrder[m_size];
		m_next=0;
		CPreOrder *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpIndexPreOrderTask::CDumpIndexPreOrderTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_IndexPreOrderFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "IndexPreOrder.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpIndexPreOrderTask::~CDumpIndexPreOrderTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpIndexPreOrderTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableIndexPreOrder::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableIndexPreOrder[m_size];
		m_next=0;
		CIndexPreOrder *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpInvestorPositionTask::CDumpInvestorPositionTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_InvestorPositionFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InvestorPosition.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpInvestorPositionTask::~CDumpInvestorPositionTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpInvestorPositionTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableInvestorPosition::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableInvestorPosition[m_size];
		m_next=0;
		CInvestorPosition *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpInvestorAccountTask::CDumpInvestorAccountTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_InvestorAccountFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InvestorAccount.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpInvestorAccountTask::~CDumpInvestorAccountTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpInvestorAccountTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableInvestorAccount::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableInvestorAccount[m_size];
		m_next=0;
		CInvestorAccount *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpInvestorAccountDepositTask::CDumpInvestorAccountDepositTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_InvestorAccountDepositFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InvestorAccountDeposit.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpInvestorAccountDepositTask::~CDumpInvestorAccountDepositTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpInvestorAccountDepositTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableInvestorAccountDeposit::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableInvestorAccountDeposit[m_size];
		m_next=0;
		CInvestorAccountDeposit *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpExchangeTask::CDumpExchangeTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_ExchangeFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "Exchange.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpExchangeTask::~CDumpExchangeTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpExchangeTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableExchange::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableExchange[m_size];
		m_next=0;
		CExchange *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpSeatTask::CDumpSeatTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_SeatFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "Seat.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpSeatTask::~CDumpSeatTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpSeatTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableSeat::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableSeat[m_size];
		m_next=0;
		CSeat *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpInstrumentTask::CDumpInstrumentTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_InstrumentFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "Instrument.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpInstrumentTask::~CDumpInstrumentTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpInstrumentTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableInstrument::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableInstrument[m_size];
		m_next=0;
		CInstrument *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpCmbInstrumentDetailTask::CDumpCmbInstrumentDetailTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_CmbInstrumentDetailFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "CmbInstrumentDetail.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpCmbInstrumentDetailTask::~CDumpCmbInstrumentDetailTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpCmbInstrumentDetailTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableCmbInstrumentDetail::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableCmbInstrumentDetail[m_size];
		m_next=0;
		CCmbInstrumentDetail *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpClientTradingIDTask::CDumpClientTradingIDTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_ClientTradingIDFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "ClientTradingID.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpClientTradingIDTask::~CDumpClientTradingIDTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpClientTradingIDTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableClientTradingID::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableClientTradingID[m_size];
		m_next=0;
		CClientTradingID *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpInvestorTask::CDumpInvestorTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_InvestorFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "Investor.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpInvestorTask::~CDumpInvestorTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpInvestorTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableInvestor::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableInvestor[m_size];
		m_next=0;
		CInvestor *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpInvestorMarginTask::CDumpInvestorMarginTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_InvestorMarginFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InvestorMargin.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpInvestorMarginTask::~CDumpInvestorMarginTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpInvestorMarginTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableInvestorMargin::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableInvestorMargin[m_size];
		m_next=0;
		CInvestorMargin *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpInvestorFeeTask::CDumpInvestorFeeTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_InvestorFeeFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InvestorFee.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpInvestorFeeTask::~CDumpInvestorFeeTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpInvestorFeeTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableInvestorFee::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableInvestorFee[m_size];
		m_next=0;
		CInvestorFee *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpUserTask::CDumpUserTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_UserFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "User.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpUserTask::~CDumpUserTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpUserTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableUser::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableUser[m_size];
		m_next=0;
		CUser *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpUserInvestorTask::CDumpUserInvestorTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_UserInvestorFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "UserInvestor.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpUserInvestorTask::~CDumpUserInvestorTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpUserInvestorTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableUserInvestor::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableUserInvestor[m_size];
		m_next=0;
		CUserInvestor *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpOrderInsertFailedTask::CDumpOrderInsertFailedTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_OrderInsertFailedFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "OrderInsertFailed.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpOrderInsertFailedTask::~CDumpOrderInsertFailedTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpOrderInsertFailedTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableOrderInsertFailed::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableOrderInsertFailed[m_size];
		m_next=0;
		COrderInsertFailed *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpUserTradingRightTask::CDumpUserTradingRightTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_UserTradingRightFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "UserTradingRight.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpUserTradingRightTask::~CDumpUserTradingRightTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpUserTradingRightTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableUserTradingRight::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableUserTradingRight[m_size];
		m_next=0;
		CUserTradingRight *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpCurrentTimeTask::CDumpCurrentTimeTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_CurrentTimeFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "CurrentTime.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpCurrentTimeTask::~CDumpCurrentTimeTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpCurrentTimeTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableCurrentTime::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableCurrentTime[m_size];
		m_next=0;
		CCurrentTime *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpUserSessionTask::CDumpUserSessionTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_UserSessionFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "UserSession.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpUserSessionTask::~CDumpUserSessionTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpUserSessionTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableUserSession::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableUserSession[m_size];
		m_next=0;
		CUserSession *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpMaxLocalIDTask::CDumpMaxLocalIDTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_MaxLocalIDFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "MaxLocalID.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpMaxLocalIDTask::~CDumpMaxLocalIDTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpMaxLocalIDTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableMaxLocalID::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableMaxLocalID[m_size];
		m_next=0;
		CMaxLocalID *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpBrkUserIDLocalIDTask::CDumpBrkUserIDLocalIDTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_BrkUserIDLocalIDFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "BrkUserIDLocalID.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpBrkUserIDLocalIDTask::~CDumpBrkUserIDLocalIDTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpBrkUserIDLocalIDTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableBrkUserIDLocalID::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableBrkUserIDLocalID[m_size];
		m_next=0;
		CBrkUserIDLocalID *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpPartClientInsGroupPositionTask::CDumpPartClientInsGroupPositionTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_PartClientInsGroupPositionFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "PartClientInsGroupPosition.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpPartClientInsGroupPositionTask::~CDumpPartClientInsGroupPositionTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpPartClientInsGroupPositionTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteablePartClientInsGroupPosition::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteablePartClientInsGroupPosition[m_size];
		m_next=0;
		CPartClientInsGroupPosition *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpClientMarginCombTypeTask::CDumpClientMarginCombTypeTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_ClientMarginCombTypeFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "ClientMarginCombType.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpClientMarginCombTypeTask::~CDumpClientMarginCombTypeTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpClientMarginCombTypeTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableClientMarginCombType::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableClientMarginCombType[m_size];
		m_next=0;
		CClientMarginCombType *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpInstrumentGroupTask::CDumpInstrumentGroupTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_InstrumentGroupFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InstrumentGroup.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpInstrumentGroupTask::~CDumpInstrumentGroupTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpInstrumentGroupTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableInstrumentGroup::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableInstrumentGroup[m_size];
		m_next=0;
		CInstrumentGroup *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpSGEDeferRateTask::CDumpSGEDeferRateTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_SGEDeferRateFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "SGEDeferRate.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpSGEDeferRateTask::~CDumpSGEDeferRateTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpSGEDeferRateTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableSGEDeferRate::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableSGEDeferRate[m_size];
		m_next=0;
		CSGEDeferRate *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpInvestorTradingRightTask::CDumpInvestorTradingRightTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_InvestorTradingRightFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InvestorTradingRight.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpInvestorTradingRightTask::~CDumpInvestorTradingRightTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpInvestorTradingRightTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableInvestorTradingRight::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableInvestorTradingRight[m_size];
		m_next=0;
		CInvestorTradingRight *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpUserIPTask::CDumpUserIPTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_UserIPFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "UserIP.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpUserIPTask::~CDumpUserIPTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpUserIPTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableUserIP::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableUserIP[m_size];
		m_next=0;
		CUserIP *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpInvestorOptionFeeTask::CDumpInvestorOptionFeeTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_InvestorOptionFeeFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InvestorOptionFee.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpInvestorOptionFeeTask::~CDumpInvestorOptionFeeTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpInvestorOptionFeeTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableInvestorOptionFee::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableInvestorOptionFee[m_size];
		m_next=0;
		CInvestorOptionFee *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpMarketDataTask::CDumpMarketDataTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_MarketDataFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "MarketData.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpMarketDataTask::~CDumpMarketDataTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpMarketDataTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableMarketData::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableMarketData[m_size];
		m_next=0;
		CMarketData *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpOrderDelayTask::CDumpOrderDelayTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_OrderDelayFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "OrderDelay.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpOrderDelayTask::~CDumpOrderDelayTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpOrderDelayTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableOrderDelay::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableOrderDelay[m_size];
		m_next=0;
		COrderDelay *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpSystemInfoTask::CDumpSystemInfoTask(CConfig *pConfig,CMemoryDB *pDB): ITask(10)
{
	m_inited=false;
	m_pFactory=pDB->m_SystemInfoFactory;
	m_list=NULL;

	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "SystemInfo.csv");
	m_output=mfopen(szFileName,"wt");
}

CDumpSystemInfoTask::~CDumpSystemInfoTask(void)
{
	if (m_list!=NULL)
	{
		delete m_list;
	}
}
	
bool CDumpSystemInfoTask::step(int *pCost)
{
	if (!m_inited)
	{
		m_inited=true;
		m_size=m_pFactory->getCount();
		*pCost=m_size/10000;

		if (m_output!=NULL)
		{
			CWriteableSystemInfo::writeCSVHead(m_output);
		}
		else
		{
			*pCost=0;
			return false;
		}
		
		m_list=new CWriteableSystemInfo[m_size];
		m_next=0;
		CSystemInfo *pData;
		pData=m_pFactory->getFirst();
		while (pData!=NULL)
		{
			m_list[m_next++]=*pData;
			pData=m_pFactory->getNext();
		}
		m_pFactory->endGet();
		m_next=0;
		return true;
	}
	else
	{
		int i;
		*pCost=1;
		for (i=0;i<100;i++)
		{
			if (m_next==m_size)
			{
				if (m_output!=NULL)
				{
					fclose(m_output);
					m_output=NULL;
				}
				return false;
			}
			if (m_output!=NULL)
			{
				m_list[m_next].writeCSV(m_output);
			}
			m_next++;
		}
		return true;
	}
}


CDumpTask::CDumpTask(CConfig *pConfig,CMemoryDB *pDB): CLinkTask()
{
	addTask(new CDumpDataSyncStatusTask(pConfig,pDB));
	addTask(new CDumpSystemStatusTask(pConfig,pDB));
	addTask(new CDumpOrderActionTask(pConfig,pDB));
	addTask(new CDumpOrderTask(pConfig,pDB));
	addTask(new CDumpTradeTask(pConfig,pDB));
	addTask(new CDumpPreOrderTask(pConfig,pDB));
	addTask(new CDumpIndexPreOrderTask(pConfig,pDB));
	addTask(new CDumpInvestorPositionTask(pConfig,pDB));
	addTask(new CDumpInvestorAccountTask(pConfig,pDB));
	addTask(new CDumpInvestorAccountDepositTask(pConfig,pDB));
	addTask(new CDumpExchangeTask(pConfig,pDB));
	addTask(new CDumpSeatTask(pConfig,pDB));
	addTask(new CDumpInstrumentTask(pConfig,pDB));
	addTask(new CDumpCmbInstrumentDetailTask(pConfig,pDB));
	addTask(new CDumpClientTradingIDTask(pConfig,pDB));
	addTask(new CDumpInvestorTask(pConfig,pDB));
	addTask(new CDumpInvestorMarginTask(pConfig,pDB));
	addTask(new CDumpInvestorFeeTask(pConfig,pDB));
	addTask(new CDumpUserTask(pConfig,pDB));
	addTask(new CDumpUserInvestorTask(pConfig,pDB));
	addTask(new CDumpOrderInsertFailedTask(pConfig,pDB));
	addTask(new CDumpUserTradingRightTask(pConfig,pDB));
	addTask(new CDumpCurrentTimeTask(pConfig,pDB));
	addTask(new CDumpUserSessionTask(pConfig,pDB));
	addTask(new CDumpMaxLocalIDTask(pConfig,pDB));
	addTask(new CDumpBrkUserIDLocalIDTask(pConfig,pDB));
	addTask(new CDumpPartClientInsGroupPositionTask(pConfig,pDB));
	addTask(new CDumpClientMarginCombTypeTask(pConfig,pDB));
	addTask(new CDumpInstrumentGroupTask(pConfig,pDB));
	addTask(new CDumpSGEDeferRateTask(pConfig,pDB));
	addTask(new CDumpInvestorTradingRightTask(pConfig,pDB));
	addTask(new CDumpUserIPTask(pConfig,pDB));
	addTask(new CDumpInvestorOptionFeeTask(pConfig,pDB));
	addTask(new CDumpMarketDataTask(pConfig,pDB));
	addTask(new CDumpOrderDelayTask(pConfig,pDB));
	addTask(new CDumpSystemInfoTask(pConfig,pDB));
}

