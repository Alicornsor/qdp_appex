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

extern CExchangeLinkManager* g_pExchangeLinkManager;

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

bool CInitServiceImpl::initExchange(CWriteableExchange *pExchange,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initSeat(CWriteableSeat *pSeat,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initUser(CWriteableUser *pUser,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initInvestor(CWriteableInvestor *pInvestor,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initClientTradingID(CWriteableClientTradingID *pClientTradingID,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initUserInvestor(CWriteableUserInvestor *pUserInvestor,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initUserTradingRight(CWriteableUserTradingRight *pUserTradingRight,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initInvestorAccount(CWriteableInvestorAccount *pInvestorAccount,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initInstrument(CWriteableInstrument *pInstrument,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initInvestorMargin(CWriteableInvestorMargin *pInvestorMargin,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initInvestorFee(CWriteableInvestorFee *pInvestorFee,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initInvestorPosition(CWriteableInvestorPosition *pInvestorPosition,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initSystemStatus(CWriteableSystemStatus *pSystemStatus,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initInstrumentGroup(CWriteableInstrumentGroup *pInstrumentGroup,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initClientMarginCombType(CWriteableClientMarginCombType *pClientMarginCombType,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initSGEDeferRate(CWriteableSGEDeferRate *pSGEDeferRate,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initCmbInstrumentDetail(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initInvestorTradingRight(CWriteableInvestorTradingRight *pInvestorTradingRight,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//判断状态是否允许
	if (getDataSyncStatus(m_DB)!=DS_Synchronizing)
	{
		m_ErrorEngine->reportError(ERROR_INVALID_DATASYNC_STATUS_WHILE_INITING);
		return false;
	}
	m_DB->m_InvestorTradingRightFactory->add(pInvestorTradingRight,pTransaction);
	return true;
}

bool CInitServiceImpl::initUserIP(CWriteableUserIP *pUserIP,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initInvestorOptionFee(CWriteableInvestorOptionFee *pInvestorOptionFee,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::initSystemInfo(CWriteableSystemInfo *pSystemInfo,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	if (m_DB->m_SystemInfoFactory->findBySystemID(pSystemInfo->SystemID)==NULL)
	{
		m_DB->m_SystemInfoFactory->add(pSystemInfo,pTransaction);
		return true;
	}
	return false;
}

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
	printf("数据同步状态=>[正在同步中]！\n");
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
	printf("数据同步状态=>[已经同步]！\n");
	m_DB->save(m_Config);
	g_pExchangeLinkManager->StartWork();
	return true;
}

bool CInitServiceImpl::DataSyncStatusUpdate(CDataSyncStatusType &NewStatus,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
//	///检查会话;
//	CUserSession *pUserSession = m_DB->m_UserSessionFactory->findBySessionID(
//		sessionRef.sessionID, sessionRef.frontID);
//	if (pUserSession == NULL)
//	{
//		m_ErrorEngine->reportError(ERROR_USER_NOT_LOGIN);
//		return false;
//	}
//
//	if (pUserSession->UserType != UT_TradeManager)
//	{
//		m_ErrorEngine->reportError(ERROR_USER_NO_PERMISSION);
//		return false;
//	}
//
//	if (NewStatus != DS_Asynchronous)
//	{
//		//要求转换的交易所数据同步状态不正确
//		m_ErrorEngine->reportError(ERROR_EXCHANGE_DATASYNC_STATUS_CHANGE_INVALID);
//		return false;
//	}
//
//	///检查交易所数据同步状态
//	CDataSyncStatus *pDataSyncStatus = 
//		m_DB->m_DataSyncStatusFactory->getFirst();
//	
//	m_DB->m_DataSyncStatusFactory->endGet();
//
//	if (pDataSyncStatus == NULL)
//	{
//		//交易所数据同步状态不正确
//		m_ErrorEngine->reportError(ERROR_EXCHANGE_DATASYNC_STATUS_CHANGE_INVALID);
//		return false;
//	}
//	if (pDataSyncStatus->DataSyncStatus != DS_Synchronized)
//	{
//		//交易所数据同步状态不正确
//		m_ErrorEngine->reportError(ERROR_EXCHANGE_DATASYNC_STATUS_CHANGE_INVALID);
//		return false;
//	}
//
//	///检查结算组状态
//	CSGDataSyncStatus *pSGDataSyncStatus;
//	pSGDataSyncStatus = 
//		m_DB->m_SGDataSyncStatusFactory->getFirst();
//	while (pSGDataSyncStatus != NULL)
//	{
//		if (pSGDataSyncStatus->SGDataSyncStatus != 
//			SGDS_Asynchronous)
//		{
//			//仍有结算组未处于未同步状态
//			m_ErrorEngine->reportError(ERROR_NOT_ALL_SG_ASYNCHRONOUS);
//			return false;
//		}
//		pSGDataSyncStatus = 
//			m_DB->m_SGDataSyncStatusFactory->getNext();
//	}
//	m_DB->m_SGDataSyncStatusFactory->endGet();
//
//	//修改状态
//	CWriteableDataSyncStatus DataSyncStatus;
//	m_DB->m_DataSyncStatusFactory->retrieve(
//		pDataSyncStatus, &DataSyncStatus);
//
//	DataSyncStatus.DataSyncStatus = DS_Asynchronous;
//
//	m_DB->m_DataSyncStatusFactory->update(
//		pDataSyncStatus, &DataSyncStatus,pTransaction);
//
	return true;
}

void CInitServiceImpl::beforeDataSync(CTransaction *pTransaction)
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

	///清空用户本地报单号数据
	CBrkUserIDLocalID *pBrkUserIDLocalID;
	pBrkUserIDLocalID=m_DB->m_BrkUserIDLocalIDFactory->getFirst();
	while (	pBrkUserIDLocalID!=NULL)
	{
		m_DB->m_BrkUserIDLocalIDFactory->remove(pBrkUserIDLocalID);
		pBrkUserIDLocalID=m_DB->m_BrkUserIDLocalIDFactory->getNext();
	}
	m_DB->m_BrkUserIDLocalIDFactory->endGet();

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

	///清空投资者交易权限表数据
	CInvestorTradingRight *pInvestorTradingRight;
	pInvestorTradingRight=m_DB->m_InvestorTradingRightFactory->getFirst();
	while (	pInvestorTradingRight!=NULL)
	{
		m_DB->m_InvestorTradingRightFactory->remove(pInvestorTradingRight);
		pInvestorTradingRight=m_DB->m_InvestorTradingRightFactory->getNext();
	}
	m_DB->m_InvestorTradingRightFactory->endGet();

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

	///清空QDP系统信息数据
	CSystemInfo *pSystemInfo;
	pSystemInfo=m_DB->m_SystemInfoFactory->getFirst();
	while (	pSystemInfo!=NULL)
	{
		m_DB->m_SystemInfoFactory->remove(pSystemInfo);
		pSystemInfo=m_DB->m_SystemInfoFactory->getNext();
	}
	m_DB->m_SystemInfoFactory->endGet();

}
	
void CInitServiceImpl::afterDataSync(CTransaction *pTransaction)
{
	///完成必要的外键连接
	///完成交易所客户编码表对应的帐户的连接
	m_DB->m_ClientTradingIDFactory->linkAllInvestorAccount(m_DB->m_InvestorAccountFactory);

}

bool CInitServiceImpl::RspQryExInstrument(CInstrumentField *pInstrumentField,const TSessionRef &sessionRef,CTransaction *pTransaction)
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

bool CInitServiceImpl::RspQryExInvestorPosition(CInvestorPositionField *pInvestorPositionField,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	//先寻找是否有记录,如果没有记录加入，如果有记录则不做任何措施
	//持仓数据在盘中就会有较大的变化，持仓值需要第一次查询结果即可
	if(NULL==pInvestorPositionField)
	{
		return true;
	}

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
		REPORT_EVENT(LOG_CRITICAL,"CHandleNotify","Cannot Find Corresponding Instrument %s",pInvestorPositionField->InstrumentID.getValue());
		return false;
	}

	CWriteableInvestorPosition  wtbInvestorPosition;
	wtbInvestorPosition.init();
	CopyInvestorPositionEntity(&wtbInvestorPosition,pInvestorPositionField);
	//持仓的获得一般有四种不同的情况：
	//1、已经通过文件上场，就不需要添加
	//2、没有文件上场，开盘前查询得到持仓，此时需要添加
	//3、没有文件上场，盘中查询得到持仓，（或者清理流文件启动）此时如果已经有成交，昨持仓成本需要重新计算
	//4、开盘持仓已经完成，盘中重新启动，此时已经有持仓，无需添加


	//暂用保证金重新计算一下
	//期货计算暂用保证金
	CInvestorMargin *pInvestorMargin = baseAlgorithm.getInvestorMargin(m_DB,pInstrument,pInvestorPositionField->BrokerID,pInvestorPositionField->InvestorID,pInvestorPositionField->HedgeFlag);

	if(pInstrument->ProductClass != PC_SGE_SPOT)
	{
		CMarketData *pMarketData = m_DB->m_MarketDataFactory->findByExchangeIDAndInstrumentID(pInvestorPositionField->ExchangeID,pInvestorPositionField->InstrumentID);
		if(pMarketData!=NULL && pInstrument->ProductClass != PC_Options)
		{
			wtbInvestorPosition.YdPositionCost = wtbInvestorPosition.YdPosition * pMarketData->PreSettlementPrice * pInstrument->VolumeMultiple;
			wtbInvestorPosition.PositionCost = wtbInvestorPosition.Position * pMarketData->PreSettlementPrice * pInstrument->VolumeMultiple;
		}
		
		if(wtbInvestorPosition.Direction == D_Buy && pInstrument->ProductClass != PC_Options)
		{
			if (pInvestorMargin != NULL)
				wtbInvestorPosition.UsedMargin = pInvestorMargin->LongMarginAmt * wtbInvestorPosition.Position + wtbInvestorPosition.PositionCost * pInvestorMargin->LongMarginRate;
		}
		else if(wtbInvestorPosition.Direction == D_Sell)
		{
			if (pInvestorMargin != NULL)
				wtbInvestorPosition.UsedMargin = pInvestorMargin->ShortMarginAmt * wtbInvestorPosition.Position + wtbInvestorPosition.PositionCost * pInvestorMargin->ShortMarginRate;
		}
		else
		{
			wtbInvestorPosition.UsedMargin = 0.0;
		}
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
		m_pHandleNotify->CalcDynamicProfit(&wtbmarketData,pInstrument,pTransaction);
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

bool CInitServiceImpl::RspQryExCapitalData(CExCapitalDataField *pExCapitalDataField,const TSessionRef &sessionRef,CTransaction *pTransaction)
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
