/////////////////////////////////////////////////////////////////////////
///@system 极速风控前置系统
///@company 上海量投网络科技有限公司
///@file TradingResultImpl.cpp
///@brief定义了类TradingResultImpl，计算交易的结果，存入内存数据库
///@history 
///20121219	longqy@cffex.net 创建文件

/////////////////////////////////////////////////////////////////////////

#include "TradingResultImpl.h"
#include "tradingTools.h"

CTradingResultImpl::CTradingResultImpl
(CMemoryDB *pDB,CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow *pFlow)
{
	m_DB = pDB;
	m_ErrorEngine = pErrorEngine;
	m_Config = pConfig;

	m_pSendFlow = pFlow;

	m_pHandleFutureOrder  = new CHandleFutureOrder(pDB,pErrorEngine,pConfig,pFlow);
//	m_pHandleOptionOrder  = new CHandleOptionOrder(pDB,pErrorEngine,pConfig,pFlow);
	
	m_pHandleNotify = new CHandleNotify(pDB,pErrorEngine,pConfig,pFlow);
	
	
	m_pHandleFutureTrade  = new CHandleFutureTrade(pDB,pErrorEngine,pConfig,pFlow);
//	m_pHandleOptionTrade  = new CHandleOptionTrade(pDB,pErrorEngine,pConfig,pFlow);
	
	
	m_pHandleFutureOrderAction =  new CHandleFutureOrderAction(pDB,pErrorEngine,pConfig,pFlow);
//	m_pHandleOptionOrderAction =  new CHandleOptionOrderAction(pDB,pErrorEngine,pConfig,pFlow);
	
	m_PartGroupPosition.clear();
}

CTradingResultImpl::~CTradingResultImpl()
{
}

bool CTradingResultImpl::initExchange(CWriteableExchange *pExchange,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_ExchangeFactory->add(pExchange,pTransaction);		
	return true;
}

bool CTradingResultImpl::initSeat(CWriteableSeat *pSeat,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_SeatFactory->add(pSeat,pTransaction);		
	return true;
}

bool CTradingResultImpl::initUser(CWriteableUser *pUser,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_UserFactory->add(pUser,pTransaction);		
	return true;
}

bool CTradingResultImpl::initInvestor(CWriteableInvestor *pInvestor,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_InvestorFactory->add(pInvestor,pTransaction);		
	return true;
}

bool CTradingResultImpl::initClientTradingID(CWriteableClientTradingID *pClientTradingID,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_ClientTradingIDFactory->add(pClientTradingID,pTransaction);		
	return true;
}

bool CTradingResultImpl::initUserInvestor(CWriteableUserInvestor *pUserInvestor,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_UserInvestorFactory->add(pUserInvestor,pTransaction);		
	return true;
}

bool CTradingResultImpl::initUserTradingRight(CWriteableUserTradingRight *pUserTradingRight,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_UserTradingRightFactory->add(pUserTradingRight,pTransaction);		
	return true;
}

bool CTradingResultImpl::initInvestorAccount(CWriteableInvestorAccount *pInvestorAccount,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_InvestorAccountFactory->add(pInvestorAccount,pTransaction);		
	return true;
}

bool CTradingResultImpl::initInstrument(CWriteableInstrument *pInstrument,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_InstrumentFactory->add(pInstrument,pTransaction);		
	return true;
}

bool CTradingResultImpl::initInvestorMargin(CWriteableInvestorMargin *pInvestorMargin,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_InvestorMarginFactory->add(pInvestorMargin,pTransaction);		
	return true;
}

bool CTradingResultImpl::initInvestorFee(CWriteableInvestorFee *pInvestorFee,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_InvestorFeeFactory->add(pInvestorFee,pTransaction);		
	return true;
}

bool CTradingResultImpl::initInvestorPosition(CWriteableInvestorPosition *pInvestorPosition,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_InvestorPositionFactory->add(pInvestorPosition,pTransaction);		
	return true;
}

bool CTradingResultImpl::initSystemStatus(CWriteableSystemStatus *pSystemStatus,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_SystemStatusFactory->add(pSystemStatus,pTransaction);		
	return true;
}

bool CTradingResultImpl::initInstrumentGroup(CWriteableInstrumentGroup *pInstrumentGroup,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_InstrumentGroupFactory->add(pInstrumentGroup,pTransaction);		
	return true;
}

bool CTradingResultImpl::initClientMarginCombType(CWriteableClientMarginCombType *pClientMarginCombType,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_ClientMarginCombTypeFactory->add(pClientMarginCombType,pTransaction);		
	return true;
}

bool CTradingResultImpl::initSGEDeferRate(CWriteableSGEDeferRate *pSGEDeferRate,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_SGEDeferRateFactory->add(pSGEDeferRate,pTransaction);		
	return true;
}

bool CTradingResultImpl::initCmbInstrumentDetail(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_CmbInstrumentDetailFactory->add(pCmbInstrumentDetail,pTransaction);		
	return true;
}

bool CTradingResultImpl::initUserIP(CWriteableUserIP *pUserIP,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_UserIPFactory->add(pUserIP,pTransaction);		
	return true;
}

bool CTradingResultImpl::initInvestorOptionFee(CWriteableInvestorOptionFee *pInvestorOptionFee,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_InvestorOptionFeeFactory->add(pInvestorOptionFee,pTransaction);		
	return true;
}

bool CTradingResultImpl::DataSyncStart(CDateType &TradingDay,const TSessionRef &sessionRef,CTransaction *pTransaction)
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
	printf("datasync status=>[syncing]!\n");
//
//	//交易所数据同步前处理
//	beforeExchangeSync(pTransaction);

	return true;
}

bool CTradingResultImpl::DataSyncEnd(CDateType &TradingDay,const TSessionRef &sessionRef,CTransaction *pTransaction)
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
	printf("datasync status=>[end sync]\n");
	m_DB->save(m_Config);
	return true;
}

void CTradingResultImpl::beforeDataSync(CTransaction *pTransaction)
{
	///清空由数据
	///清空QDP状态表数据
	CSystemStatus *pSystemStatus;
	pSystemStatus=m_DB->m_SystemStatusFactory->getFirst();
	while (	pSystemStatus!=NULL)
	{
		m_DB->m_SystemStatusFactory->remove(pSystemStatus);
		pSystemStatus=m_DB->m_SystemStatusFactory->getNext();
	}
	m_DB->m_SystemStatusFactory->endGet();

	///清空报单操作数据
	COrderAction *pOrderAction;
	pOrderAction=m_DB->m_OrderActionFactory->getFirst();
	while (	pOrderAction!=NULL)
	{
		m_DB->m_OrderActionFactory->remove(pOrderAction);
		pOrderAction=m_DB->m_OrderActionFactory->getNext();
	}
	m_DB->m_OrderActionFactory->endGet();

	///清空持仓表数据
	CInvestorPosition *pInvestorPosition;
	pInvestorPosition=m_DB->m_InvestorPositionFactory->getFirst();
	while (	pInvestorPosition!=NULL)
	{
		m_DB->m_InvestorPositionFactory->remove(pInvestorPosition);
		pInvestorPosition=m_DB->m_InvestorPositionFactory->getNext();
	}
	m_DB->m_InvestorPositionFactory->endGet();

	///清空账户实时资金表数据
	CInvestorAccount *pInvestorAccount;
	pInvestorAccount=m_DB->m_InvestorAccountFactory->getFirst();
	while (	pInvestorAccount!=NULL)
	{
		m_DB->m_InvestorAccountFactory->remove(pInvestorAccount);
		pInvestorAccount=m_DB->m_InvestorAccountFactory->getNext();
	}
	m_DB->m_InvestorAccountFactory->endGet();

	///清空交易所表数据
	CExchange *pExchange;
	pExchange=m_DB->m_ExchangeFactory->getFirst();
	while (	pExchange!=NULL)
	{
		m_DB->m_ExchangeFactory->remove(pExchange);
		pExchange=m_DB->m_ExchangeFactory->getNext();
	}
	m_DB->m_ExchangeFactory->endGet();

	///清空下单席位表数据
	CSeat *pSeat;
	pSeat=m_DB->m_SeatFactory->getFirst();
	while (	pSeat!=NULL)
	{
		m_DB->m_SeatFactory->remove(pSeat);
		pSeat=m_DB->m_SeatFactory->getNext();
	}
	m_DB->m_SeatFactory->endGet();

	///清空期货合约表数据
	CInstrument *pInstrument;
	pInstrument=m_DB->m_InstrumentFactory->getFirst();
	while (	pInstrument!=NULL)
	{
		m_DB->m_InstrumentFactory->remove(pInstrument);
		pInstrument=m_DB->m_InstrumentFactory->getNext();
	}
	m_DB->m_InstrumentFactory->endGet();

	///清空期货组合合约明细表数据
	CCmbInstrumentDetail *pCmbInstrumentDetail;
	pCmbInstrumentDetail=m_DB->m_CmbInstrumentDetailFactory->getFirst();
	while (	pCmbInstrumentDetail!=NULL)
	{
		m_DB->m_CmbInstrumentDetailFactory->remove(pCmbInstrumentDetail);
		pCmbInstrumentDetail=m_DB->m_CmbInstrumentDetailFactory->getNext();
	}
	m_DB->m_CmbInstrumentDetailFactory->endGet();

	///清空交易所客户编码表数据
	CClientTradingID *pClientTradingID;
	pClientTradingID=m_DB->m_ClientTradingIDFactory->getFirst();
	while (	pClientTradingID!=NULL)
	{
		m_DB->m_ClientTradingIDFactory->remove(pClientTradingID);
		pClientTradingID=m_DB->m_ClientTradingIDFactory->getNext();
	}
	m_DB->m_ClientTradingIDFactory->endGet();

	///清空投资者信息表数据
	CInvestor *pInvestor;
	pInvestor=m_DB->m_InvestorFactory->getFirst();
	while (	pInvestor!=NULL)
	{
		m_DB->m_InvestorFactory->remove(pInvestor);
		pInvestor=m_DB->m_InvestorFactory->getNext();
	}
	m_DB->m_InvestorFactory->endGet();

	///清空客户期货保证金率表数据
	CInvestorMargin *pInvestorMargin;
	pInvestorMargin=m_DB->m_InvestorMarginFactory->getFirst();
	while (	pInvestorMargin!=NULL)
	{
		m_DB->m_InvestorMarginFactory->remove(pInvestorMargin);
		pInvestorMargin=m_DB->m_InvestorMarginFactory->getNext();
	}
	m_DB->m_InvestorMarginFactory->endGet();

	///清空客户手续费率表数据
	CInvestorFee *pInvestorFee;
	pInvestorFee=m_DB->m_InvestorFeeFactory->getFirst();
	while (	pInvestorFee!=NULL)
	{
		m_DB->m_InvestorFeeFactory->remove(pInvestorFee);
		pInvestorFee=m_DB->m_InvestorFeeFactory->getNext();
	}
	m_DB->m_InvestorFeeFactory->endGet();

	///清空用户表数据
	CUser *pUser;
	pUser=m_DB->m_UserFactory->getFirst();
	while (	pUser!=NULL)
	{
		m_DB->m_UserFactory->remove(pUser);
		pUser=m_DB->m_UserFactory->getNext();
	}
	m_DB->m_UserFactory->endGet();

	///清空用户投资者关系表数据
	CUserInvestor *pUserInvestor;
	pUserInvestor=m_DB->m_UserInvestorFactory->getFirst();
	while (	pUserInvestor!=NULL)
	{
		m_DB->m_UserInvestorFactory->remove(pUserInvestor);
		pUserInvestor=m_DB->m_UserInvestorFactory->getNext();
	}
	m_DB->m_UserInvestorFactory->endGet();

	///清空用户交易权限表数据
	CUserTradingRight *pUserTradingRight;
	pUserTradingRight=m_DB->m_UserTradingRightFactory->getFirst();
	while (	pUserTradingRight!=NULL)
	{
		m_DB->m_UserTradingRightFactory->remove(pUserTradingRight);
		pUserTradingRight=m_DB->m_UserTradingRightFactory->getNext();
	}
	m_DB->m_UserTradingRightFactory->endGet();

	///清空交易员在线会话数据
	CUserSession *pUserSession;
	pUserSession=m_DB->m_UserSessionFactory->getFirst();
	while (	pUserSession!=NULL)
	{
		m_DB->m_UserSessionFactory->remove(pUserSession);
		pUserSession=m_DB->m_UserSessionFactory->getNext();
	}
	m_DB->m_UserSessionFactory->endGet();

	///清空最大本地报单号数据
	CMaxLocalID *pMaxLocalID;
	pMaxLocalID=m_DB->m_MaxLocalIDFactory->getFirst();
	while (	pMaxLocalID!=NULL)
	{
		m_DB->m_MaxLocalIDFactory->remove(pMaxLocalID);
		pMaxLocalID=m_DB->m_MaxLocalIDFactory->getNext();
	}
	m_DB->m_MaxLocalIDFactory->endGet();

	///清空交易编码组合保证金类型数据
	CClientMarginCombType *pClientMarginCombType;
	pClientMarginCombType=m_DB->m_ClientMarginCombTypeFactory->getFirst();
	while (	pClientMarginCombType!=NULL)
	{
		m_DB->m_ClientMarginCombTypeFactory->remove(pClientMarginCombType);
		pClientMarginCombType=m_DB->m_ClientMarginCombTypeFactory->getNext();
	}
	m_DB->m_ClientMarginCombTypeFactory->endGet();

	///清空合约和合约组关系数据
	CInstrumentGroup *pInstrumentGroup;
	pInstrumentGroup=m_DB->m_InstrumentGroupFactory->getFirst();
	while (	pInstrumentGroup!=NULL)
	{
		m_DB->m_InstrumentGroupFactory->remove(pInstrumentGroup);
		pInstrumentGroup=m_DB->m_InstrumentGroupFactory->getNext();
	}
	m_DB->m_InstrumentGroupFactory->endGet();

	///清空金交所递延费率表数据
	CSGEDeferRate *pSGEDeferRate;
	pSGEDeferRate=m_DB->m_SGEDeferRateFactory->getFirst();
	while (	pSGEDeferRate!=NULL)
	{
		m_DB->m_SGEDeferRateFactory->remove(pSGEDeferRate);
		pSGEDeferRate=m_DB->m_SGEDeferRateFactory->getNext();
	}
	m_DB->m_SGEDeferRateFactory->endGet();

	///清空交易员IP地址数据
	CUserIP *pUserIP;
	pUserIP=m_DB->m_UserIPFactory->getFirst();
	while (	pUserIP!=NULL)
	{
		m_DB->m_UserIPFactory->remove(pUserIP);
		pUserIP=m_DB->m_UserIPFactory->getNext();
	}
	m_DB->m_UserIPFactory->endGet();

	///清空客户期权手续费率表数据
	CInvestorOptionFee *pInvestorOptionFee;
	pInvestorOptionFee=m_DB->m_InvestorOptionFeeFactory->getFirst();
	while (	pInvestorOptionFee!=NULL)
	{
		m_DB->m_InvestorOptionFeeFactory->remove(pInvestorOptionFee);
		pInvestorOptionFee=m_DB->m_InvestorOptionFeeFactory->getNext();
	}
	m_DB->m_InvestorOptionFeeFactory->endGet();

	///清空委托延迟表数据
	COrderDelay *pOrderDelay;
	pOrderDelay=m_DB->m_OrderDelayFactory->getFirst();
	while (	pOrderDelay!=NULL)
	{
		m_DB->m_OrderDelayFactory->remove(pOrderDelay);
		pOrderDelay=m_DB->m_OrderDelayFactory->getNext();
	}
	m_DB->m_OrderDelayFactory->endGet();

}
	
void CTradingResultImpl::afterDataSync(CTransaction *pTransaction)
{
	///完成必要的外键连接
	///完成交易所客户编码表对应的帐户的连接
	m_DB->m_ClientTradingIDFactory->linkAllInvestorAccount(m_DB->m_InvestorAccountFactory);

}

bool CTradingResultImpl::RspQryExInstrument(CInstrumentField *pInstrumentField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	bool bSuccess=true;
	if (pInstrumentField==NULL)
	{
		return false;
	}
	CInstrument* pInstrument = m_DB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pInstrumentField->ExchangeID,pInstrumentField->InstrumentID);
	
	CWriteableInstrument wtbInstrument;
	CopyInstrumentEntity(&wtbInstrument,pInstrumentField);
	
	if (pInstrument==NULL)
	{
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

bool CTradingResultImpl::RspQryExInvestorPosition(CInvestorPositionField *pInvestorPositionField,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CTradingResultImpl::RspQryExMarketData(CMarketDataField *pMarketDataField,const TSessionRef &sessionRef,CTransaction *pTransaction)
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
		m_pHandleNotify->CalcDynamicProfit(&wtbmarketData,pInstrument,pTransaction);
	}
	return true;
}

bool CTradingResultImpl::RspQryExTradingDay(CExchangeTradingDayField *pExchangeTradingDayField,const TSessionRef &sessionRef,CTransaction *pTransaction)
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
	wtbExchange.ExchangeName="";
	
	//EXRISKG-568 引用pExchange空指针问题
	wtbExchange.ExchangeID=pExchangeTradingDayField->ExchangeID;
	wtbExchange.TradingDay=pExchangeTradingDayField->TradingDay;
	if (pExchange==NULL)
	{
		m_DB->m_ExchangeFactory->add(&wtbExchange,pTransaction);
	}
	else
	{
		CopyExchangeEntity(&wtbExchange,pExchange);
		wtbExchange.ExchangeID=pExchangeTradingDayField->ExchangeID;
		wtbExchange.TradingDay=pExchangeTradingDayField->TradingDay;
		m_DB->m_ExchangeFactory->update(pExchange,&wtbExchange,pTransaction);
	}
	return true;
}

bool CTradingResultImpl::RspQryExCapitalData(CExCapitalDataField *pExCapitalDataField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	bool bSuccess=true;
	if (pExCapitalDataField==NULL)
	{
		return false;
	}
	CInvestorAccount* pAccount = m_DB->m_InvestorAccountFactory->findByBrokerIDAccountID(pExCapitalDataField->BrokerID, pExCapitalDataField->AccountID);
	
	CWriteableInvestorAccount wtbAccount;
	CopyAPIInvestorAccountEntity(&wtbAccount,pExCapitalDataField);
	
	if (pAccount==NULL)
	{
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

bool CTradingResultImpl::RspQueryExCmbInstrumentDetail(CCmbInstrumentDetailField *pCmbInstrumentDetailField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	bool bSuccess=true;
	if (pCmbInstrumentDetailField==NULL)
	{
		return false;
	}
	CCmbInstrumentDetail* pCmbInstrumentDetail = m_DB->m_CmbInstrumentDetailFactory->findByExchangeIDAndArbiInstrumentIDAndSingelInstrumentID(
		pCmbInstrumentDetailField->ExchangeID, pCmbInstrumentDetailField->ArbiInstrumentID, pCmbInstrumentDetailField->SingleInstrumentID);
	
	CWriteableCmbInstrumentDetail wtbCmbInstrumentDetail;
	CopyCmbInstrumentDetailEntity(&wtbCmbInstrumentDetail,pCmbInstrumentDetailField);
	
	if (pCmbInstrumentDetail==NULL)
	{
		m_DB->m_CmbInstrumentDetailFactory->add(&wtbCmbInstrumentDetail,pTransaction);
	}
	else
	{
		m_DB->m_CmbInstrumentDetailFactory->update(pCmbInstrumentDetail,&wtbCmbInstrumentDetail,pTransaction);		
	}
	return true;
}

bool CTradingResultImpl::isDuplicate(CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID)
{
	if (seqID>0)
	{
		map<CDbmtTopicIDType,CDbmtSequenceIDType>::iterator it;
		it=m_lastSeqMap.find(topicID);
		if (it==m_lastSeqMap.end())
		{
			///这个主题号是初次出现
			m_lastSeqMap.insert(pair<CDbmtTopicIDType,CDbmtSequenceIDType>(topicID,seqID));
			return false;
		}
		if (seqID<=it->second)
		{
			///小于等于上次的序列号，说明是重复的
			return true;
		}
		else
		{
			///设置上次的序列号
			it->second=seqID;
			return false;
		}
	}
	return false;
}


bool CTradingResultImpl::suitableTime(void)
{
	return (getDataSyncStatus(m_DB)==DS_Synchronized);
}

bool CTradingResultImpl::SyncInvestorAccountDeposit(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit,CAccountDepositResField *pResDeposit,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
									const TSessionRef &sessionRef,CTransaction *pTransaction)
{
/*** SIR XXXXX BEGIN ***/
    std::string accountSeqNo( pInvestorAccountDeposit->AccountSeqNo.getValue() );
    if ( accountSeqNo.size() < 3 )
    {//资金流水号格式错误
        printf("[ERR][%s]AccountSeqNo format error, eg A_1 or B_1\n", accountSeqNo.c_str());
		//用AccountInsideSeqNo将错误码返回
		pInvestorAccountDeposit->AccountInsideSeqNo = ERROR_DUPLICATE_DEPOSIT_FIELD;
        return false;    
    }
    
    switch(accountSeqNo[0])
    {
    case INVESTORACCOUNTDEPOSIT_FROM_CHAIRMAN:
    	topicID = INVESTORACCOUNTDEPOSIT_TOPICID_CHAIRMAN;
	break;
    case INVESTORACCOUNTDEPOSIT_FROM_MONEYGATE:
    	topicID = INVESTORACCOUNTDEPOSIT_TOPICID_CHAIRMAN;
	break;
    case INVESTORACCOUNTDEPOSIT_FROM_FIELD:
    	topicID = INVESTORACCOUNTDEPOSIT_TOPICID_FIELD;
	break;
	case INVESTORACCOUNTDEPOSIT_FROM_Netting:
		topicID = INVESTORACCOUNTDEPOSIT_TOPICID_Netting;
	break;
    default:
    	//资金流水号格式错误
	printf("[ERR][%s]AccountSeqNo format error, eg A_1 or B_1 or C_1\n", accountSeqNo.c_str());
	//用AccountInsideSeqNo将错误码返回
	pInvestorAccountDeposit->AccountInsideSeqNo = ERROR_DUPLICATE_DEPOSIT_FIELD;
	return false;  
	break;
    }
    seqID = atoi(accountSeqNo.substr(2).c_str());
/*** SIR XXXXX END ***/
	
	if (isDuplicate(topicID,seqID))
	{
	    printf("[ERR][%s]AccountSeqNo is duplicate\n", accountSeqNo.c_str());
		//用AccountInsideSeqNo将错误码返回
		pInvestorAccountDeposit->AccountInsideSeqNo = ERROR_DUPLICATE_DEPOSIT_FIELD;
		return false;
	}
	if (!suitableTime())
	{
		return false;
	}

	CInvestorAccount *pInvestorAccount=NULL;
	CWriteableInvestorAccount theInvestorAccount;
	theInvestorAccount.init();
	if (pInvestorAccountDeposit->BrokerID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_BROKERID_CANNOT_BE_BLANK);
		return false;
	}
	
	if(pInvestorAccountDeposit->AccountID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_ACCOUNT_CANNOT_BE_BLANK);
		return false;
	}
	
	pInvestorAccount=m_DB->m_InvestorAccountFactory->findByBrokerIDAccountID(pInvestorAccountDeposit->BrokerID,pInvestorAccountDeposit->AccountID);	
	
	if (pInvestorAccount==NULL)
	{
		m_ErrorEngine->reportError(ERROR_CAN_NOT_FIND_ACCOUNT);
		REPORT_EVENT(LOG_CRITICAL,"DBMTError","Can sync account deposit for %s",pInvestorAccountDeposit->AccountID.getValue());
		return false;
	}

		m_DB->m_InvestorAccountFactory->retrieve(pInvestorAccount,&theInvestorAccount);		
		//pInvestorAccountDeposit->Amount始终是一个正值，出入金是靠方向判断的
		if (pInvestorAccountDeposit->AmountDirection==AD_In)
		{
			theInvestorAccount.Deposit+=pInvestorAccountDeposit->Amount;
			theInvestorAccount.Balance+=pInvestorAccountDeposit->Amount;
			theInvestorAccount.Available+=pInvestorAccountDeposit->Amount;
			theInvestorAccount.DynamicRights+=pInvestorAccountDeposit->Amount;
			REPORT_EVENT(LOG_CRITICAL,"AccountDeposit","account[%s]deposit[%f]元\n",pInvestorAccountDeposit->AccountID.getValue(),pInvestorAccountDeposit->Amount.getValue());
		}
		else
		{
			theInvestorAccount.Withdraw+=pInvestorAccountDeposit->Amount;
			theInvestorAccount.Balance-=pInvestorAccountDeposit->Amount;
			theInvestorAccount.Available-=pInvestorAccountDeposit->Amount;
			theInvestorAccount.DynamicRights-=pInvestorAccountDeposit->Amount;
			/*** SIR XXXXX BEGIN ***/
			//出金后可用资金和结算准备金不能为负数
			//此需求暂时不启用

			std::string accountSeqNo( pInvestorAccountDeposit->AccountSeqNo.getValue() );
			if (INVESTORACCOUNTDEPOSIT_FROM_MONEYGATE == accountSeqNo[0])
			{
				theInvestorAccount.ManualFrozen-=pInvestorAccountDeposit->Amount;//通过网关实现的出金要解冻临时冻结资金
				theInvestorAccount.Available+=pInvestorAccountDeposit->Amount;//有效前面已经冻结过,解冻后要加回来
			}
			REPORT_EVENT(LOG_CRITICAL,"AccountDeposit","account[%s]withdraw[%f]\n",pInvestorAccountDeposit->AccountID.getValue(),pInvestorAccountDeposit->Amount.getValue());
				
		}
		m_DB->m_InvestorAccountFactory->update(pInvestorAccount,&theInvestorAccount,pTransaction);
		return true;
}

bool CTradingResultImpl::SyncUpdUser(CWriteableUser *pUser,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	
	if (isDuplicate(topicID,seqID))
	{
		return false;
	}
	if (!suitableTime())
	{
		return false;
	}

	return m_DB->m_UserFactory->updateByPK(pUser,pTransaction);
}

///同步数据库表客户资金帐户出入金的实现
///@param	pClientTradingID	要同步的客户资金帐户出入金信息
///@param	pTransaction	本操作属于的事务
///@return	true表示成功，false表示失败
bool CTradingResultImpl::SyncClientTradingID(CWriteableClientTradingID *pClientTradingID,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
										   const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	if (isDuplicate(topicID,seqID))
	{
		return false;
	}
	if (!suitableTime())
	{
		return false;
	}

	bool success=true;
	CClientTradingID *pClientTradingIDRight=NULL;
	CWriteableClientTradingID theClientTradingID;
	theClientTradingID.init();
	
	if (pClientTradingID->BrokerID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_BROKERID_CANNOT_BE_BLANK);
		return false;
	}
	
	if(pClientTradingID->ExchangeID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_EXCHANGEID_CANNOTBEBLANK);
		return false;
	}
	
	if(pClientTradingID->ParticipantID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_PARTICIPANTID_NOTNULL);
		return false;
	}
	
	if(pClientTradingID->ClientID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_CLIENTID_NOTNULL);
		return false;
	}
	
	
	pClientTradingIDRight=m_DB->m_ClientTradingIDFactory->findByBrokerIDExchangeIDPartClientID(pClientTradingID->BrokerID,pClientTradingID->ExchangeID,
		pClientTradingID->ParticipantID,pClientTradingID->ClientID);	
	
	if (pClientTradingIDRight==NULL)
	{
		m_DB->m_ClientTradingIDFactory->add(pClientTradingID,pTransaction);
	}
	else
	{
		m_DB->m_ClientTradingIDFactory->retrieve(pClientTradingIDRight,&theClientTradingID);
		//上场只修改isActive和ClientRight字段
		theClientTradingID.IsActive=pClientTradingID->IsActive;
		theClientTradingID.ClientRight=pClientTradingID->ClientRight;
		m_DB->m_ClientTradingIDFactory->update(pClientTradingIDRight,&theClientTradingID,pTransaction);
	}

	return success;
}


bool CTradingResultImpl::OnRtnOrder(COrderField *pOrder,const TSessionRef &sessionRef,CTransaction *pTransaction)
{    
	bool bSuccess = true;
	CProductClassType eProductType = PC_Unknown;
	CInstrument *pInstrument = m_DB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pOrder->ExchangeID,pOrder->InstrumentID);
	if (pInstrument != NULL)
	{
		eProductType = pInstrument->ProductClass;
	}
	switch (eProductType )
	{
	case PC_Futures:
		{
			m_pHandleOrder = m_pHandleFutureOrder;
			break;
		}
// 	case PC_Options:
// 		{
// 			m_pHandleOrder = m_pHandleOptionOrder;
// 			break;
// 		}
	default:     // 未找到合约类型，直接返回。
		{	
			REPORT_EVENT(LOG_WARNING,"Can not Find Instrument Class ", "In Line %d of File %s.\n",__LINE__,__FILE__);
			return false;
		}
	}

	if (pOrder->OffsetFlag.isNull() ||
		!pOrder->OffsetFlag.isValid())
	{
		pOrder->OffsetFlag=OF_Open;
	}
	
	CClientTradingID * pClientTradingID=m_DB->m_ClientTradingIDFactory->findByBrokerIDExchangeIDPartClientID(pOrder->BrokerID,\
		pOrder->ExchangeID,pOrder->ParticipantID,pOrder->ClientID);
	if(pClientTradingID==NULL)
	{
		REPORT_EVENT(LOG_WARNING,"Can not Find ClientTradingID ", "BrokerID:%s,ExchangeID:%s,ParticipantID:%s, ClientID:%s In Line %d of File %s.\n",
			pOrder->BrokerID.getValue(),pOrder->ExchangeID.getValue(),pOrder->ParticipantID.getValue(),pOrder->ClientID.getValue(), __LINE__,__FILE__);
		return false;
	}
	///填入客户号/会员号
	pOrder->InvestorID=pClientTradingID->InvestorID;
	bSuccess = m_pHandleOrder->HandleRtnOrder(pOrder,sessionRef,pTransaction,false);
	return bSuccess;
}

bool CTradingResultImpl::OnRtnTrade(CTradeField *pTradeField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	bool bSuccess = false;
	COrder *pOrder = m_DB->m_OrderFactory->findByExchangeIDAndOrderSysID(pTradeField->ExchangeID,pTradeField->OrderSysID);
    if(NULL == pOrder)  //找不到对应报单
	{
		REPORT_EVENT(LOG_CRITICAL, "Cann't Find Corresponding Order For Trade ","ClientID=[%s], OrderSysID=[%s].\n",pTradeField->ClientID.getValue(),pTradeField->OrderSysID.getValue());   
		return false;
	}
	
	CTrade *pTrade  = m_DB->m_TradeFactory->findByExchangeIDTradeIDOrderSysID(pTradeField->ExchangeID,pTradeField->TradeID,pTradeField->OrderSysID);
    if(NULL != pTrade)   // 重复的成交
	{
		REPORT_EVENT(LOG_CRITICAL, "Duplicate Trade ","ClientID=[%s], OrderSysID=[%s].\n",pTradeField->ClientID.getValue(),pTradeField->OrderSysID.getValue());   
		return false;
	}


	CProductClassType eProductType = PC_Unknown;
	CInstrument *pInstrument = m_DB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pTradeField->ExchangeID,pTradeField->InstrumentID);
	if (pInstrument != NULL)
	{
		eProductType = pInstrument->ProductClass;
	}
	switch (eProductType )
	{
	case PC_Futures:
		{
			m_pHandleTrade = m_pHandleFutureTrade;
			break;
		}
// 	case PC_Options:
// 		{
// 			m_pHandleTrade = m_pHandleOptionTrade;
// 			break;
// 		}
	default:
		{
			REPORT_EVENT(LOG_WARNING,"Can not Find Instrument Class ", "In Line %d of File %s.\n",__LINE__,__FILE__);
			return false;
		}
	}
	
	return m_pHandleTrade->HandleRtnTrade(pOrder,pTradeField,sessionRef,pTransaction);
}

bool CTradingResultImpl::RspOrderAction(COrderField *pRspOrder,CWriteableOrderAction *pOrderAction,COrderActionField* pActField,CRspInfoField*  pRspInfoField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
    bool bSuccess = true;
	COrder* pOrder = m_DB->m_OrderFactory->findByExchangeIDAndOrderSysID(pActField->ExchangeID,pActField->OrderSysID);
	if(NULL == pOrder)  //找不到该笔订单
	{
		REPORT_EVENT(LOG_WARNING,"Can not Find Ref Order ", "In Line %d of File %s.\n",__LINE__,__FILE__);
		return false;
	}
	pActField->InvestorID = pOrder->InvestorID;
	pActField->ClientID = pOrder->ClientID;
	pActField->ParticipantID = pOrder->ParticipantID;
	CProductClassType eProductType = PC_Unknown;
	CInstrument *pInstrument = m_DB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pOrder->ExchangeID,pOrder->InstrumentID);
	if (pInstrument != NULL)
	{
		eProductType = pInstrument->ProductClass;
	}
	switch (eProductType)
	{
	case PC_Futures:
		{
			m_pHandleOrderAction = m_pHandleFutureOrderAction;
			break;
		}
// 	case PC_Options:
// 		{
// 			m_pHandleOrderAction = m_pHandleOptionOrderAction;
// 			break;
// 		}
	default:     // 未找到合约类型，直接返回。
		{	
			REPORT_EVENT(LOG_WARNING,"Can not Find Instrument Class ", "In Line %d of File %s.\n",__LINE__,__FILE__);
			return false;
		}
	}
	
	bSuccess = m_pHandleOrderAction->HandleRspOrderAction(pOrderAction,pActField,pRspInfoField,pOrder,sessionRef,pTransaction);
	return bSuccess;
}

void CTradingResultImpl::DumpDebugInfo(const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	m_pHandleFutureOrder->DumpDebugInfo();	
}

bool CTradingResultImpl::UpdateSystemStatus(CSystemStatusField *pSystemStatusField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	CWriteableSystemStatus SystemStatus;
	SystemStatus.SystemStatus = pSystemStatusField->SystemStatus;
	
	CSystemStatus* pSystemStatus=m_DB->m_SystemStatusFactory->getFirst();
	m_DB->m_SystemStatusFactory->endGet();
	if (pSystemStatus==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"UpdateSystemStatus","error:no UpdateSystemStatus");
	}
	else
	{
		SystemStatus.TradingDay = pSystemStatus->TradingDay;
		m_DB->m_SystemStatusFactory->addOrUpdate(pSystemStatus,&SystemStatus,pTransaction);	
	}
	return true;
}

void CTradingResultImpl::BuildInsGroupPosition(CExchangeIDType exchangeID)
{
	if (!m_PartGroupPosition.insert(exchangeID.getValue()).second)
	{
		return;
	}
	CInvestorPositionFactory *pPositionFactory = m_DB->m_InvestorPositionFactory;
	CInvestorPosition* pInvestorPosition=NULL;
	CInvestorAccount *pInvestorAccount=NULL;
	CWriteableInvestorAccount wtbAccount;
	CWriteableInvestorPositionLimit wtbLimit;
	m_PosiMap.clear();
	CPosiMap::iterator posi_iter;
	TPosi posi;
	for (pInvestorPosition = pPositionFactory->getFirst();pInvestorPosition != NULL;pInvestorPosition = pPositionFactory->getNext())	
	{
		//如果交易所对不上，不需要计算
		if(pInvestorPosition->ExchangeID != exchangeID ||
			pInvestorPosition->Position == 0)
		{
			continue;
		}

		//获取品种限额
		CInstrument *pInstrument = m_DB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(pInvestorPosition->ExchangeID,pInvestorPosition->InstrumentID);
		if (pInstrument == NULL)
		{
			REPORT_EVENT(LOG_CRITICAL,"BuildInsGroupPosition","can not find instrument:%s,exchangeid:%s",\
				pInvestorPosition->InstrumentID.getValue(),pInvestorPosition->ExchangeID.getValue());
			continue;
		}
		CInvestorPositionLimit *pLimit = m_DB->m_InvestorPositionLimitFactory->findByBrkIDVstIDExIDIstID(pInvestorPosition->BrokerID,\
			pInvestorPosition->InvestorID,pInvestorPosition->ExchangeID,pInstrument->ProductID.getValue());
		if (pLimit != NULL)
		{
			wtbLimit.init();
			m_DB->m_InvestorPositionLimitFactory->retrieve(pLimit,&wtbLimit);
			if (pInvestorPosition->Direction == D_Buy)
			{
				wtbLimit.LongPosition += pInvestorPosition->YdPosition;
			}
			else if (pInvestorPosition->Direction == D_Sell)
			{
				wtbLimit.ShortPosition += pInvestorPosition->YdPosition;
			}
			else
			{
				if (pInvestorPosition->Position >0)
				{
					wtbLimit.LongPosition += pInvestorPosition->YdPosition;
				}
				else
				{
					wtbLimit.ShortPosition -= pInvestorPosition->YdPosition;
				}
			}
			m_DB->m_InvestorPositionLimitFactory->update(pLimit,&wtbLimit);
		}
		
		pInvestorAccount = m_DB->m_InvestorAccountFactory->findByBrokerIDInvestorID(pInvestorPosition->BrokerID,pInvestorPosition->InvestorID);
		if (pInvestorAccount == NULL)
		{
			REPORT_EVENT(LOG_CRITICAL,"BuildInsGroupPosition","can not find account,but have positions brokerid:%s,investorid:%s",\
				pInvestorPosition->BrokerID.getValue(),pInvestorPosition->InvestorID.getValue());
			continue;
		}
		m_DB->m_InvestorAccountFactory->retrieve(pInvestorAccount,&wtbAccount);
		if (pInvestorPosition->Direction == D_Net)
		{
			wtbAccount.Margin += pInvestorPosition->UsedMargin;
		}
		else
		{
			memset(&posi,0,sizeof(TPosi));
			posi.BrokerID = pInvestorPosition->BrokerID;
			posi.InvestorID = pInvestorPosition->InvestorID;
			posi.ExchangeID = pInvestorPosition->ExchangeID;
			posi.InstrumentID = pInvestorPosition->InstrumentID;
			posi.HedgeFlag = pInvestorPosition->HedgeFlag;
			posi.Direction = pInvestorPosition->Direction==D_Buy ? D_Sell : D_Buy;
			posi_iter = m_PosiMap.find(posi);
			if (posi_iter == m_PosiMap.end())
			{
				posi.Direction=pInvestorPosition->Direction;
				m_PosiMap.insert(CPosiMap::value_type(posi,pInvestorPosition->UsedMargin));
				wtbAccount.Margin += pInvestorPosition->UsedMargin;
			}
			else 
			{
				if (pInvestorPosition->UsedMargin > posi_iter->second)
				{
					wtbAccount.Margin += (pInvestorPosition->UsedMargin - posi_iter->second);
					m_PosiMap.erase(posi_iter);
				}
				else
				{
					m_PosiMap.erase(posi_iter);
					continue;
				}
			}
		}
		baseAlgorithm.ChangeBalanceAndAvailable(&wtbAccount);
		m_DB->m_InvestorAccountFactory->update(pInvestorAccount,&wtbAccount);
	}
	pPositionFactory->endGet();
}

bool CTradingResultImpl::NtfInstrumentStatusUpdate(CInstrumentStatusField* pInstrumentStatusField,bool bSendRtn,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	bool bSuccess = true;
	bSuccess = m_pHandleNotify->HandleInstrumentStatusUpdate(pInstrumentStatusField,bSendRtn,pTransaction);
	return bSuccess;
}

bool CTradingResultImpl::UserUpdate(CDbmtUserField *pUserField, CTransaction *pTransaction)
{
	if (isDuplicate(pUserField->DbmtTopicID,pUserField->DbmtSequenceID))
	{
		return false;
	}
	if (!suitableTime())
	{
		return false;
	}
	
	CWriteableUser wuser;
	CUser *user=m_DB->m_UserFactory->findByBrokerIDUserID(pUserField->BrokerID,pUserField->UserID);
	if (NULL == user)
	{
		m_ErrorEngine->reportError(ERROR_USER_NOT_FOUND);
		return false;
	}

	if (pUserField->IsActive == UIA_NoActive)
	{
		CUserSession *pUserSession = m_DB->m_UserSessionFactory->startFindByUserID(pUserField->UserID);
		for(;NULL!=pUserSession;pUserSession=m_DB->m_UserSessionFactory->findNextByUserID())
		{
			m_DB->m_UserSessionFactory->remove(pUserSession, pTransaction);
		}
		m_DB->m_UserSessionFactory->endFindByUserID();

		CMaxLocalID *pMaxLocalID = m_DB->m_MaxLocalIDFactory->getFirst();
		while (	pMaxLocalID!=NULL)
		{
			if (pMaxLocalID->UserID == pUserField->UserID)
			{
				m_DB->m_MaxLocalIDFactory->remove(pMaxLocalID);
			}
			pMaxLocalID=m_DB->m_MaxLocalIDFactory->getNext();
		}
		m_DB->m_MaxLocalIDFactory->endGet();
	}

	//更新user表
	m_DB->m_UserFactory->retrieve(user,&wuser);
	CopyUserEntity(&wuser,pUserField);
	m_DB->m_UserFactory->update(user,&wuser,pTransaction);	
	return true;
}

bool CTradingResultImpl::NtfSGEDeferRate(CSGEDeferRateField *pSGEDeferRateField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	CSGEDeferRate* pSGEDeferRate = m_DB->m_SGEDeferRateFactory->findByTradeDateInstrumentIDIndex(pSGEDeferRateField->TradeDate,
		pSGEDeferRateField->InstrumentID);
	
	CWriteableSGEDeferRate wtbSGEDeferRate;
	if (NULL == pSGEDeferRate)
	{
		memset(&wtbSGEDeferRate,0,sizeof(CWriteableSGEDeferRate));
		CopySGEDeferRateEntity(&wtbSGEDeferRate,pSGEDeferRateField);
		m_DB->m_SGEDeferRateFactory->add(&wtbSGEDeferRate, pTransaction);
	}
	else
	{
		m_DB->m_SGEDeferRateFactory->retrieve(pSGEDeferRate, &wtbSGEDeferRate);
		wtbSGEDeferRate.DeferRate = pSGEDeferRateField->DeferRate;
		wtbSGEDeferRate.Direction = pSGEDeferRateField->Direction;
		m_DB->m_SGEDeferRateFactory->update(pSGEDeferRate, &wtbSGEDeferRate, pTransaction);
	}
	
	return true;
}

bool CTradingResultImpl::NtfTimeSync(CCurrentTimeField *pCurrTime,const TSessionRef &sessionRef,CTransaction *pTransaction)
{	
	bool bSuccess = true;
	bSuccess = m_pHandleNotify->HandleNtfTimeSync(pCurrTime,sessionRef,pTransaction); 
	return bSuccess;
}

bool CTradingResultImpl::RspQryExDiffTime(CExchTimeDiffField *pExchTimeDiffField,const TSessionRef &sessionRef,CTransaction *pTransaction)
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
	
	wtbExchTimeDiff.ExchangeID=pExchTimeDiffField->ExchangeID;
	wtbExchTimeDiff.TradingDay=pExchTimeDiffField->TradingDay;
	wtbExchTimeDiff.LoginTime=pExchTimeDiffField->LoginTime;
	wtbExchTimeDiff.LocalTime=pExchTimeDiffField->LocalTime;
	wtbExchTimeDiff.DiffSnd=pExchTimeDiffField->DiffSnd;
	if (NULL == pExchTimeDiff)
	{
		m_DB->m_ExchTimeDiffFactory->add(&wtbExchTimeDiff,pTransaction);
	}
	else
	{
		CopyExchTimeDiffEntity(&wtbExchTimeDiff,pExchTimeDiff);
		wtbExchTimeDiff.TradingDay=pExchTimeDiffField->TradingDay;
		wtbExchTimeDiff.LoginTime=pExchTimeDiffField->LoginTime;
		wtbExchTimeDiff.LocalTime=pExchTimeDiffField->LocalTime;
		wtbExchTimeDiff.DiffSnd=pExchTimeDiffField->DiffSnd;
		m_DB->m_ExchTimeDiffFactory->update(pExchTimeDiff,&wtbExchTimeDiff,pTransaction);
	}
	return true;
}






