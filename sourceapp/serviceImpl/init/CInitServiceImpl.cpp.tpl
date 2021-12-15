!!function!!
#include <vector>
#include <map>
using namespace std;

int isInitPackage(char *usage)
{
	if (strcmp(usage,"exchangeInit")==0)
	{
		return 1;
	}
	return 0;
}

char *getTableName(char *name)
{
	return name+4;
}

bool isFinalManager(char *name)
{
	if (!strcmp(name,"root"))
	{
		return true;
	}
	if (!strcmp(name,"none"))
	{
		return true;
	}
	if (!strcmp(name,"SettlementGroup"))
	{
		return true;
	}
	if (!strcmp(name,"implied"))
	{
		return true;
	}
	return false;
}

typedef struct
{
	char *name;
	char *manager;
	char *deductManager;
}	TManagerItem;

class CManagerMap: protected vector<TManagerItem *>
{
public:
	void add(char *name,char *manager)
	{
		TManagerItem *pItem=new TManagerItem;
		pItem->name=name;
		pItem->manager=manager,
		pItem->deductManager=NULL;
		push_back(pItem);
	}
	char *getManager(char *name)
	{
		iterator it;
		for (it=begin();it<end();it++)
		{
			if (!strcmp(name,(*it)->name))
			{
				return (*it)->manager;
			}
		}
		return NULL;
	}
	char *getDeductManager(char *name)
	{
		iterator it;
		for (it=begin();it<end();it++)
		{
			if (!strcmp(name,(*it)->name))
			{
				if ((*it)->deductManager==NULL)
				{
					printf("can not find deduct manager for %s\n",name);
					exit(1);
				}
				return (*it)->deductManager;
			}
		}
		printf("can not find deduct manager for %s\n",name);
		exit(1);
		return NULL;
	}
	void deduct(void)
	{
		iterator it;
		int level=0;
		for (it=begin();it<end();it++)
		{
			char *thisManager;
			thisManager=(*it)->manager;
			while (!isFinalManager(thisManager))
			{
				char *deductManager;

				level++;
				deductManager=getManager(thisManager);
				if (deductManager==NULL)
				{
					printf("can not find manager of %s\n",thisManager);
					exit(1);
				}
				if (level>10)
				{
					printf("too many levels while finding deduct manager %s\n",(*it)->name);
					exit(1);
				}
				thisManager=deductManager;
			}
			(*it)->deductManager=thisManager;
		}
	}
	void dump(void)
	{
		iterator it;
		for (it=begin();it<end();it++)
		{
			printf("%s->(%s,%s)\n",(*it)->name,(*it)->manager,(*it)->deductManager);
		}
	}
};

CManagerMap managers;

class CInitList: protected vector<char *>
{
public:
	CInitList(char *name)
	{
		m_name=name;
	}
	void add(char *name)
	{
		push_back(name);
	}
	void remove(char *name)
	{
		iterator it;
		for (it=begin();it<end();it++)
		{
			if (!strcmp(name,*it))
			{
				erase(it);
				return;
			}
		}
		printf("%s%s在MDB中存在，而在XTP中不存在\n",m_name,name);
		exit(1);
	}
	void checkEmpty(void)
	{
		iterator it;
		if (size()==0)
		{
			return;
		}
		for (it=begin();it<end();it++)
		{
			printf("%s%s在XTP中存在，而在MDB中不存在\n",m_name,*it);
		}
		exit(1);
	}
private:
	char *m_name;
};
CInitList exchangeInitList("交易所初始化数据");

!!endfunction!!
!!comment 完成表管理关系的连接!!
!!enter system!!
	!!travel tables!!
		!!if !strcmp(@hasTable,"yes")!!
			!!command managers.add(@name,@manager)!!
		!!endif!!
	!!next!!
!!leave!!
!!comment 推导最终的表管理关系!!
!!command managers.deduct()!!
!!comment 检查XTP中的初始化数据和内存数据库中定义的是否完全相同!!
!!enter XTP!!
	!!travel packages!!
		!!if isInitPackage(@usage)!!
			!!command exchangeInitList.add(getTableName(@name))!!
		!!endif!!
	!!next!!
!!leave!!
!!enter system!!
	!!travel tables!!
		!!if !strcmp(@hasTable,"yes")&&!strcmp(@readTable,"yes")!!
			!!if !strcmp(managers.getDeductManager(@name),"root")!!
				!!command exchangeInitList.remove(@name)!!
			!!endif!!
		!!endif!!
	!!next!!
!!leave!!
!!command exchangeInitList.checkEmpty()!!
!!enter XTP!!
/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company 上海量投网络科技有限公司
///@file CInitServiceImpl.h
///@brief实现了类CInitServiceImpl
///@history 
///20150513	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CInitServiceImpl.h"
#include "UFEntityCopy.h"
#include "ExchangeLinkManager.h"
#include "ExchangeLinkTimer.h"

extern CExchangeLinkManager* g_pExchangeLinkManager;
extern CLinkReactor* g_pConnReactor;

CInitServiceImpl::CInitServiceImpl(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CHandleNotify *pHandleNotify)
{
	m_DB=pDB;
	m_ErrorEngine=pErrorEngine;
	m_Config=pConfig;
	m_pHandleNotify =pHandleNotify;
}

bool CInitServiceImpl::isSuperSession(const TSessionRef &sessionRef)
{
	if (sessionRef.SessionID!=0)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_SESSION);
		return false;
	}
	return true;
}

!!travel packages!!
!!if isInitPackage(@usage)!!
!!let tableName=getTableName(@name)!!
bool CInitServiceImpl::init!!@tableName!!(CWriteable!!@tableName!! *p!!@tableName!!,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
!!if (strcmp(@tableName,"SystemInfo"))!!
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_!!@tableName!!Factory->add(p!!@tableName!!,pTransaction);
	return true;
!!else!!
	if (m_DB->m_SystemInfoFactory->findBySystemID(pSystemInfo->SystemID)==NULL)
	{
		m_DB->m_SystemInfoFactory->add(pSystemInfo,pTransaction);
		return true;
	}
	return false;
!!endif!!
}

!!endif!!
!!next!!
bool CInitServiceImpl::DataSyncStart(CDateType &TradingDay,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	///检查交易所数据同步状态
	CDataSyncStatus *pDataSyncStatus = m_DB->m_DataSyncStatusFactory->getFirst();	
	m_DB->m_DataSyncStatusFactory->endGet();

	if (pDataSyncStatus != NULL)
	{
		if (pDataSyncStatus->DataSyncStatus != DS_Asynchronous &&
		pDataSyncStatus->DataSyncStatus != DS_Synchronizing)
		{
			//数据同步状态不正确
			m_ErrorEngine->reportError(ERROR_INSUITABLE_DATASYNC_STATUS);
			return false;
		}
	}	
	CWriteableDataSyncStatus DataSyncStatus;
	DataSyncStatus.init();
	DataSyncStatus.DataSyncStatus = DS_Synchronizing;
	DataSyncStatus.TradingDay = TradingDay;
	
	m_DB->m_DataSyncStatusFactory->addOrUpdate(pDataSyncStatus,&DataSyncStatus,pTransaction);
	printf("datasync status is syncing\n");
//
//	//交易所数据同步前处理
//	beforeExchangeSync(pTransaction);

	return true;
}

bool CInitServiceImpl::DataSyncEnd(CDateType &TradingDay,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	///检查交易所数据同步状态
	CDataSyncStatus *pDataSyncStatus = m_DB->m_DataSyncStatusFactory->getFirst();	
	m_DB->m_DataSyncStatusFactory->endGet();

	if (pDataSyncStatus == NULL)
	{
		m_ErrorEngine->reportError(ERROR_INSUITABLE_DATASYNC_STATUS);
		return false;
	}
	
	if (pDataSyncStatus->DataSyncStatus != DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INSUITABLE_DATASYNC_STATUS);
		return false;
	}

	///同步数据后处理
	afterDataSync(pTransaction);

	///修改状态
	CWriteableDataSyncStatus DataSyncStatus;
	DataSyncStatus.init();
	m_DB->m_DataSyncStatusFactory->retrieve(pDataSyncStatus, &DataSyncStatus);
	DataSyncStatus.DataSyncStatus = DS_Synchronized;
	m_DB->m_DataSyncStatusFactory->update(pDataSyncStatus, &DataSyncStatus,pTransaction);
	printf("datasync status is end\n");
	m_DB->save(m_Config);
	g_pExchangeLinkManager->StartWork();
	g_pConnReactor->PostLinkTimer();
	return true;
}

bool CInitServiceImpl::DataSyncStatusUpdate(CDataSyncStatusType &NewStatus,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	return true;
}
!!leave!!

!!enter system!!
void CInitServiceImpl::beforeDataSync(CTransaction *pTransaction)
{
	///清空由数据
!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!if !strcmp(managers.getDeductManager(@name),"root") || !strcmp(managers.getDeductManager(@name),"SettlementGroup")!!
	///清空!!@usage!!数据
	C!!@name!! *p!!@name!!;
	p!!@name!!=m_DB->m_!!@name!!Factory->getFirst();
	while (	p!!@name!!!=NULL)
	{
		m_DB->m_!!@name!!Factory->remove(p!!@name!!);
		p!!@name!!=m_DB->m_!!@name!!Factory->getNext();
	}
	m_DB->m_!!@name!!Factory->endGet();

!!endif!!
!!endif!!
!!next!!
}
	
void CInitServiceImpl::afterDataSync(CTransaction *pTransaction)
{
	///完成必要的外键连接
!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!if !strcmp(managers.getDeductManager(@name),"root")!!
!!let tableName=@name!!
!!travel foreigns!!
!!if !strcmp(managers.getDeductManager(@factory),"root")!!
	///完成!!@usage!!!!@comment!!的连接
	m_DB->m_!!@tableName!!Factory->linkAll!!@name!!(m_DB->m_!!@factory!!Factory);

!!endif!!
!!next!!
!!endif!!
!!endif!!
!!next!!
}
!!leave!!

bool CInitServiceImpl::RspQryExInstrument(CInstrumentField *pInstrumentField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	bool bSuccess=true;
	if (pInstrumentField==NULL)
	{
		return false;
	}
	CInstrument* pInstrument = m_DB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pInstrumentField->ExchangeID,pInstrumentField->InstrumentID);
	
	CWriteableInstrument wtbInstrument;
	
	if (pInstrument==NULL)
	{
		CopyInstrumentEntity(&wtbInstrument,pInstrumentField);
		//该合约没有，就插入新合约
		/// 检查合约属性值的合理性，不合法报错。linxb 20130730
		if( !pInstrumentField->PreSettlementPrice.isValid()  || 
			pInstrumentField->MaxLimitOrderVolume  < 0      ||
			pInstrumentField->MinLimitOrderVolume  < 0      ||
			pInstrumentField->MaxMarketOrderVolume < 0      ||
			pInstrumentField->MinMarketOrderVolume  < 0 )
		{
			REPORT_EVENT(LOG_CRITICAL,"Instrument Property Error.","InstrumentID:[%s],PreSettlementPrice:[%f], MaxLimitOrderVolume:[%d],MinLimitOrderVolume:[%d],MaxMarketOrderVolume:[%d],MinMarketOrderVolume:[%d]", \
				pInstrumentField->InstrumentID.getValue(),pInstrumentField->PreSettlementPrice.getValue(),pInstrumentField->MaxLimitOrderVolume.getValue(), \
				pInstrumentField->MinLimitOrderVolume.getValue(), pInstrumentField->MaxMarketOrderVolume.getValue(),pInstrumentField->MinMarketOrderVolume.getValue());
		}
		m_DB->m_InstrumentFactory->add(&wtbInstrument,pTransaction);
	}
	else
	{
		//合约信息完全相同不用更新
		const int nBufSize=4000;
		char buf1[nBufSize];
		char buf2[nBufSize];
		memset(buf1,0,nBufSize);
		memset(buf2,0,nBufSize);
		pInstrument->dumpString(buf1);
		m_DB->m_InstrumentFactory->retrieve(pInstrument,&wtbInstrument);
		CopyInstrumentEntity(&wtbInstrument,pInstrumentField);
		wtbInstrument.dumpString(buf2);
		if (strcmp(buf1,buf2))
		{
			
			/// 检查合约属性值的合理性，不合法报错。linxb 20130730
			if( !pInstrumentField->PreSettlementPrice.isValid()  || 
				pInstrumentField->MaxLimitOrderVolume  < 0      ||
				pInstrumentField->MinLimitOrderVolume  < 0      ||
				pInstrumentField->MaxMarketOrderVolume < 0      ||
				pInstrumentField->MinMarketOrderVolume  < 0 )
			{
				REPORT_EVENT(LOG_CRITICAL,"Instrument Property Error.","InstrumentID:[%s],PreSettlementPrice:[%f], MaxLimitOrderVolume:[%d],MinLimitOrderVolume:[%d],MaxMarketOrderVolume:[%d],MinMarketOrderVolume:[%d]", \
					pInstrumentField->InstrumentID.getValue(),pInstrumentField->PreSettlementPrice.getValue(),pInstrumentField->MaxLimitOrderVolume.getValue(), \
					pInstrumentField->MinLimitOrderVolume.getValue(), pInstrumentField->MaxMarketOrderVolume.getValue(),pInstrumentField->MinMarketOrderVolume.getValue());
			}
			m_DB->m_InstrumentFactory->update(pInstrument,&wtbInstrument,pTransaction);
		}		
	}
	return true;
}

bool CInitServiceImpl::RspQryExInvestorPosition(CInvestorPositionField *pInvestorPositionField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//先寻找是否有记录,如果没有记录加入，如果有记录则不做任何措施
	//持仓数据在盘中就会有较大的变化，持仓值需要第一次查询结果即可
	if(NULL==pInvestorPositionField)
	{
		return true;
	}

	//查询当前方向的持仓是否存在
	CInvestorPosition *pInvestorPosition =  m_DB->m_InvestorPositionFactory->findByBrkIDExIDInvIDInsDirHed(
			pInvestorPositionField->BrokerID,pInvestorPositionField->ExchangeID,pInvestorPositionField->InvestorID,
			pInvestorPositionField->InstrumentID,pInvestorPositionField->Direction,pInvestorPositionField->HedgeFlag);
	if(NULL!=pInvestorPosition)
	{
		return true;
	}

	CInstrument *pInstrument = m_DB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pInvestorPositionField->ExchangeID,pInvestorPositionField->InstrumentID);
	if( NULL ==  pInstrument )
	{
		REPORT_EVENT(LOG_CRITICAL,"RspQryExInvestorPosition","Cannot Find Corresponding Instrument %s",pInvestorPositionField->InstrumentID.getValue());
		return false;
	}

	CWriteableInvestorPosition  wtbInvestorPosition;
	wtbInvestorPosition.init();
	CopyInvestorPositionEntity(&wtbInvestorPosition,pInvestorPositionField);

	//期货计算暂用保证金
	CInvestorMargin *pInvestorMargin = baseAlgorithm.getInvestorMargin(m_DB,pInstrument,pInvestorPositionField->BrokerID,pInvestorPositionField->InvestorID,pInvestorPositionField->HedgeFlag);		
	CMarketData *pMarketData = m_DB->m_MarketDataFactory->findByExchangeIDAndInstrumentID(pInvestorPositionField->ExchangeID,pInvestorPositionField->InstrumentID);
	if(pMarketData!=NULL && pInstrument->ProductClass != PC_Options)
	{
		wtbInvestorPosition.YdPositionCost = fabs(wtbInvestorPosition.YdPosition) * pMarketData->PreSettlementPrice * pInstrument->VolumeMultiple;
		wtbInvestorPosition.PositionCost = wtbInvestorPosition.YdPositionCost;
	}
	
	if(wtbInvestorPosition.Position >0 && pInstrument->ProductClass != PC_Options)
	{
		if (pInvestorMargin != NULL)
			wtbInvestorPosition.UsedMargin = pInvestorMargin->LongMarginAmt * wtbInvestorPosition.Position;
	}
	else if(wtbInvestorPosition.Position <0)
	{
		if (pInvestorMargin != NULL)
			wtbInvestorPosition.UsedMargin = pInvestorMargin->ShortMarginAmt * wtbInvestorPosition.Position * -1;
	}
	else
	{
		wtbInvestorPosition.UsedMargin = 0.0;
	}
	m_DB->m_InvestorPositionFactory->add(&wtbInvestorPosition,pTransaction);
	return true;
}

bool CInitServiceImpl::RspQryExMarketData(CMarketDataField *pMarketDataField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	if (NULL!=pMarketDataField)
	{
		CWriteableMarketData wtbmarketData;
		CInstrument *pInstrument = m_DB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pMarketDataField->ExchangeID,
			pMarketDataField->InstrumentID);
		if(NULL!=pInstrument)
		{
			if(pInstrument->UpperLimitPrice==0.0 ||
			   pInstrument->PreSettlementPrice==0.0)
			{
				CWriteableInstrument WriteableInstrument; 
				m_DB->m_InstrumentFactory->retrieve(pInstrument,&WriteableInstrument);
				WriteableInstrument.UpperLimitPrice = pMarketDataField->UpperLimitPrice;
				WriteableInstrument.LowerLimitPrice = pMarketDataField->LowerLimitPrice;
				WriteableInstrument.PreSettlementPrice = pMarketDataField->PreSettlementPrice;
				m_DB->m_InstrumentFactory->update(pInstrument,&WriteableInstrument);
			}
		}
		else
		{
			REPORT_EVENT(LOG_CRITICAL,"RspQryExMarketData","no instrument[%s] found!",pMarketDataField->InstrumentID.getValue());
			return false;
		}

		CMarketData *pMarketData = m_DB->m_MarketDataFactory->findByExchangeIDAndInstrumentID(pMarketDataField->ExchangeID,
			pMarketDataField->InstrumentID);
		if(pMarketData==NULL)
		{
			CopyMarketDataEntity(&wtbmarketData,pMarketDataField);
			wtbmarketData.ExchangeID = pInstrument->ExchangeID;
			pMarketData = m_DB->m_MarketDataFactory->add(&wtbmarketData,pTransaction);
		}
		else
		{
			m_DB->m_MarketDataFactory->retrieve(pMarketData,&wtbmarketData);
			CopyMarketDataEntity(&wtbmarketData,pMarketDataField);
			wtbmarketData.ExchangeID = pInstrument->ExchangeID;
			m_DB->m_MarketDataFactory->update(pMarketData,&wtbmarketData,pTransaction);
		}
		//计算浮动盈亏
		//m_pHandleNotify->CalcDynamicProfit(&wtbmarketData,pInstrument,pTransaction);
	}
	return true;
}

bool CInitServiceImpl::RspQryExTradingDay(CExchangeTradingDayField *pExchangeTradingDayField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	bool bSuccess=true;
	if (pExchangeTradingDayField==NULL)
	{
		return false;
	}
	if (pExchangeTradingDayField->TradingDay.isNull())
	{
		return false;
	}
	CExchange* pExchange=m_DB->m_ExchangeFactory->findByExchangeID(pExchangeTradingDayField->ExchangeID);
	
	CWriteableExchange wtbExchange;		

	if (pExchange==NULL)
	{
		wtbExchange.ExchangeName="";	
		//EXRISKG-568 引用pExchange空指针问题
		wtbExchange.ExchangeID=pExchangeTradingDayField->ExchangeID;
		wtbExchange.TradingDay=pExchangeTradingDayField->TradingDay;
		m_DB->m_ExchangeFactory->add(&wtbExchange,pTransaction);
	}
	else
	{
		m_DB->m_ExchangeFactory->retrieve(pExchange,&wtbExchange);
		wtbExchange.ExchangeID=pExchangeTradingDayField->ExchangeID;
		wtbExchange.TradingDay=pExchangeTradingDayField->TradingDay;
		m_DB->m_ExchangeFactory->update(pExchange,&wtbExchange,pTransaction);
	}
	return true;
}

bool CInitServiceImpl::RspQryExCapitalData(CExCapitalDataField *pExCapitalDataField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	bool bSuccess=true;
	if (pExCapitalDataField==NULL)
	{
		return false;
	}
	CInvestorAccount* pAccount = m_DB->m_InvestorAccountFactory->findByBrokerIDAccountID(pExCapitalDataField->BrokerID, pExCapitalDataField->AccountID);
	
	CWriteableInvestorAccount wtbAccount;
	
	if (pAccount==NULL)
	{
		CopyAPIInvestorAccountEntity(&wtbAccount,pExCapitalDataField);
		//该合约没有，就插入新合约
		/// 检查资金属性值的合理性，不合法报错
		if( !pExCapitalDataField->Available.isValid())
		{
			REPORT_EVENT(LOG_CRITICAL,"InvestorAccount Property Error.","AccountID:[%s],Available:[%f]", \
				pExCapitalDataField->AccountID.getValue(),pExCapitalDataField->Available.getValue());
		}
			m_DB->m_InvestorAccountFactory->add(&wtbAccount,pTransaction);
	}
	else
	{
		//资金信息完全相同不用更新
		const int nBufSize=4000;
		char buf1[nBufSize];
		char buf2[nBufSize];
		memset(buf1,0,nBufSize);
		memset(buf2,0,nBufSize);
		pAccount->dumpString(buf1);
		m_DB->m_InvestorAccountFactory->retrieve(pAccount,&wtbAccount);
		CopyAPIInvestorAccountEntity(&wtbAccount,pExCapitalDataField);
		wtbAccount.dumpString(buf2);
		if (strcmp(buf1,buf2))
		{
			
			/// 检查资金属性值的合理性，不合法报错
			if( !pExCapitalDataField->Available.isValid())
			{
				REPORT_EVENT(LOG_CRITICAL,"InvestorAccount Property Error.","AccountID:[%s],Available:[%f]", \
					pExCapitalDataField->AccountID.getValue(),pExCapitalDataField->Available.getValue());
			}
/*** SIR XXXXX BEGIN ***/
			//由于推送的资金消息中不含投资者编号，此处需要将待更新记录中的投资者编号更新过来
			wtbAccount.InvestorID = pAccount->InvestorID; 
/*** SIR XXXXX END ***/
			m_DB->m_InvestorAccountFactory->update(pAccount,&wtbAccount,pTransaction);
		}		
	}
	return true;
}

bool CInitServiceImpl::RspQueryExCmbInstrumentDetail(CCmbInstrumentDetailField *pCmbInstrumentDetailField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	bool bSuccess=true;
	if (pCmbInstrumentDetailField==NULL)
	{
		return false;
	}
	CCmbInstrumentDetail* pCmbInstrumentDetail = m_DB->m_CmbInstrumentDetailFactory->findByExchangeIDAndArbiInstrumentIDAndSingelInstrumentID(
		pCmbInstrumentDetailField->ExchangeID, pCmbInstrumentDetailField->ArbiInstrumentID, pCmbInstrumentDetailField->SingleInstrumentID);
	
	CWriteableCmbInstrumentDetail wtbCmbInstrumentDetail;	
	if (pCmbInstrumentDetail==NULL)
	{
		CopyCmbInstrumentDetailEntity(&wtbCmbInstrumentDetail,pCmbInstrumentDetailField);
		m_DB->m_CmbInstrumentDetailFactory->add(&wtbCmbInstrumentDetail,pTransaction);
	}
	else
	{
		m_DB->m_CmbInstrumentDetailFactory->retrieve(pCmbInstrumentDetail,&wtbCmbInstrumentDetail);
		CopyCmbInstrumentDetailEntity(&wtbCmbInstrumentDetail,pCmbInstrumentDetailField);
		m_DB->m_CmbInstrumentDetailFactory->update(pCmbInstrumentDetail,&wtbCmbInstrumentDetail,pTransaction);		
	}
	return true;
}

bool CInitServiceImpl::RspQryExDiffTime(CExchTimeDiffField *pExchTimeDiffField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	bool bSuccess=true;
	if (NULL == pExchTimeDiffField)
	{
		return false;
	}
	if (pExchTimeDiffField->TradingDay.isNull())
	{
		return false;
	}
	
	CExchTimeDiff* pExchTimeDiff=m_DB->m_ExchTimeDiffFactory->findByPK(pExchTimeDiffField->ExchangeID);
	
	CWriteableExchTimeDiff wtbExchTimeDiff;	
	if (NULL == pExchTimeDiff)
	{
		wtbExchTimeDiff.ExchangeID=pExchTimeDiffField->ExchangeID;
		wtbExchTimeDiff.TradingDay=pExchTimeDiffField->TradingDay;
		wtbExchTimeDiff.LoginTime=pExchTimeDiffField->LoginTime;
		wtbExchTimeDiff.LocalTime=pExchTimeDiffField->LocalTime;
		wtbExchTimeDiff.DiffSnd=pExchTimeDiffField->DiffSnd;
		m_DB->m_ExchTimeDiffFactory->add(&wtbExchTimeDiff,pTransaction);
	}
	else
	{
		m_DB->m_ExchTimeDiffFactory->retrieve(pExchTimeDiff,&wtbExchTimeDiff);
		wtbExchTimeDiff.TradingDay=pExchTimeDiffField->TradingDay;
		wtbExchTimeDiff.LoginTime=pExchTimeDiffField->LoginTime;
		wtbExchTimeDiff.LocalTime=pExchTimeDiffField->LocalTime;
		wtbExchTimeDiff.DiffSnd=pExchTimeDiffField->DiffSnd;
		m_DB->m_ExchTimeDiffFactory->update(pExchTimeDiff,&wtbExchTimeDiff,pTransaction);
	}
	return true;
}
