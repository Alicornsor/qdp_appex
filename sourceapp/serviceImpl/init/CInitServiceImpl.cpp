/////////////////////////////////////////////////////////////////////////
///@system ��������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CInitServiceImpl.h
///@briefʵ������CInitServiceImpl
///@history 
///20150513	xuzh		�������ļ�
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	//�ж�״̬�Ƿ�����
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
	///��齻��������ͬ��״̬
	CDataSyncStatus *pDataSyncStatus = m_DB->m_DataSyncStatusFactory->getFirst();	
	m_DB->m_DataSyncStatusFactory->endGet();

	if (pDataSyncStatus != NULL)
	{
		if (pDataSyncStatus->DataSyncStatus != DS_Asynchronous &&
		pDataSyncStatus->DataSyncStatus != DS_Synchronizing)
		{
			//����ͬ��״̬����ȷ
			m_ErrorEngine->reportError(ERROR_INSUITABLE_DATASYNC_STATUS);
			return false;
		}
	}	
	CWriteableDataSyncStatus DataSyncStatus;
	DataSyncStatus.init();
	DataSyncStatus.DataSyncStatus = DS_Synchronizing;
	DataSyncStatus.TradingDay = TradingDay;
	
	m_DB->m_DataSyncStatusFactory->addOrUpdate(pDataSyncStatus,&DataSyncStatus,pTransaction);
	printf("����ͬ��״̬=>[����ͬ����]��\n");
//
//	//����������ͬ��ǰ����
//	beforeExchangeSync(pTransaction);

	return true;
}

bool CInitServiceImpl::DataSyncEnd(CDateType &TradingDay,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
	///��齻��������ͬ��״̬
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

	///ͬ�����ݺ���
	afterDataSync(pTransaction);

	///�޸�״̬
	CWriteableDataSyncStatus DataSyncStatus;
	DataSyncStatus.init();
	m_DB->m_DataSyncStatusFactory->retrieve(pDataSyncStatus, &DataSyncStatus);
	DataSyncStatus.DataSyncStatus = DS_Synchronized;
	m_DB->m_DataSyncStatusFactory->update(pDataSyncStatus, &DataSyncStatus,pTransaction);
	printf("����ͬ��״̬=>[�Ѿ�ͬ��]��\n");
	m_DB->save(m_Config);
	g_pExchangeLinkManager->StartWork();
	return true;
}

bool CInitServiceImpl::DataSyncStatusUpdate(CDataSyncStatusType &NewStatus,const TSessionRef &sessionRef,CTransaction *pTransaction)
{
//	///���Ự;
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
//		//Ҫ��ת���Ľ���������ͬ��״̬����ȷ
//		m_ErrorEngine->reportError(ERROR_EXCHANGE_DATASYNC_STATUS_CHANGE_INVALID);
//		return false;
//	}
//
//	///��齻��������ͬ��״̬
//	CDataSyncStatus *pDataSyncStatus = 
//		m_DB->m_DataSyncStatusFactory->getFirst();
//	
//	m_DB->m_DataSyncStatusFactory->endGet();
//
//	if (pDataSyncStatus == NULL)
//	{
//		//����������ͬ��״̬����ȷ
//		m_ErrorEngine->reportError(ERROR_EXCHANGE_DATASYNC_STATUS_CHANGE_INVALID);
//		return false;
//	}
//	if (pDataSyncStatus->DataSyncStatus != DS_Synchronized)
//	{
//		//����������ͬ��״̬����ȷ
//		m_ErrorEngine->reportError(ERROR_EXCHANGE_DATASYNC_STATUS_CHANGE_INVALID);
//		return false;
//	}
//
//	///��������״̬
//	CSGDataSyncStatus *pSGDataSyncStatus;
//	pSGDataSyncStatus = 
//		m_DB->m_SGDataSyncStatusFactory->getFirst();
//	while (pSGDataSyncStatus != NULL)
//	{
//		if (pSGDataSyncStatus->SGDataSyncStatus != 
//			SGDS_Asynchronous)
//		{
//			//���н�����δ����δͬ��״̬
//			m_ErrorEngine->reportError(ERROR_NOT_ALL_SG_ASYNCHRONOUS);
//			return false;
//		}
//		pSGDataSyncStatus = 
//			m_DB->m_SGDataSyncStatusFactory->getNext();
//	}
//	m_DB->m_SGDataSyncStatusFactory->endGet();
//
//	//�޸�״̬
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
	///���������
	///���QDP״̬������
	CSystemStatus *pSystemStatus;
	pSystemStatus=m_DB->m_SystemStatusFactory->getFirst();
	while (	pSystemStatus!=NULL)
	{
		m_DB->m_SystemStatusFactory->remove(pSystemStatus);
		pSystemStatus=m_DB->m_SystemStatusFactory->getNext();
	}
	m_DB->m_SystemStatusFactory->endGet();

	///��ձ�����������
	COrderAction *pOrderAction;
	pOrderAction=m_DB->m_OrderActionFactory->getFirst();
	while (	pOrderAction!=NULL)
	{
		m_DB->m_OrderActionFactory->remove(pOrderAction);
		pOrderAction=m_DB->m_OrderActionFactory->getNext();
	}
	m_DB->m_OrderActionFactory->endGet();

	///��ճֱֲ�����
	CInvestorPosition *pInvestorPosition;
	pInvestorPosition=m_DB->m_InvestorPositionFactory->getFirst();
	while (	pInvestorPosition!=NULL)
	{
		m_DB->m_InvestorPositionFactory->remove(pInvestorPosition);
		pInvestorPosition=m_DB->m_InvestorPositionFactory->getNext();
	}
	m_DB->m_InvestorPositionFactory->endGet();

	///����˻�ʵʱ�ʽ������
	CInvestorAccount *pInvestorAccount;
	pInvestorAccount=m_DB->m_InvestorAccountFactory->getFirst();
	while (	pInvestorAccount!=NULL)
	{
		m_DB->m_InvestorAccountFactory->remove(pInvestorAccount);
		pInvestorAccount=m_DB->m_InvestorAccountFactory->getNext();
	}
	m_DB->m_InvestorAccountFactory->endGet();

	///��ս�����������
	CExchange *pExchange;
	pExchange=m_DB->m_ExchangeFactory->getFirst();
	while (	pExchange!=NULL)
	{
		m_DB->m_ExchangeFactory->remove(pExchange);
		pExchange=m_DB->m_ExchangeFactory->getNext();
	}
	m_DB->m_ExchangeFactory->endGet();

	///����µ�ϯλ������
	CSeat *pSeat;
	pSeat=m_DB->m_SeatFactory->getFirst();
	while (	pSeat!=NULL)
	{
		m_DB->m_SeatFactory->remove(pSeat);
		pSeat=m_DB->m_SeatFactory->getNext();
	}
	m_DB->m_SeatFactory->endGet();

	///����ڻ���Լ������
	CInstrument *pInstrument;
	pInstrument=m_DB->m_InstrumentFactory->getFirst();
	while (	pInstrument!=NULL)
	{
		m_DB->m_InstrumentFactory->remove(pInstrument);
		pInstrument=m_DB->m_InstrumentFactory->getNext();
	}
	m_DB->m_InstrumentFactory->endGet();

	///����ڻ���Ϻ�Լ��ϸ������
	CCmbInstrumentDetail *pCmbInstrumentDetail;
	pCmbInstrumentDetail=m_DB->m_CmbInstrumentDetailFactory->getFirst();
	while (	pCmbInstrumentDetail!=NULL)
	{
		m_DB->m_CmbInstrumentDetailFactory->remove(pCmbInstrumentDetail);
		pCmbInstrumentDetail=m_DB->m_CmbInstrumentDetailFactory->getNext();
	}
	m_DB->m_CmbInstrumentDetailFactory->endGet();

	///��ս������ͻ����������
	CClientTradingID *pClientTradingID;
	pClientTradingID=m_DB->m_ClientTradingIDFactory->getFirst();
	while (	pClientTradingID!=NULL)
	{
		m_DB->m_ClientTradingIDFactory->remove(pClientTradingID);
		pClientTradingID=m_DB->m_ClientTradingIDFactory->getNext();
	}
	m_DB->m_ClientTradingIDFactory->endGet();

	///���Ͷ������Ϣ������
	CInvestor *pInvestor;
	pInvestor=m_DB->m_InvestorFactory->getFirst();
	while (	pInvestor!=NULL)
	{
		m_DB->m_InvestorFactory->remove(pInvestor);
		pInvestor=m_DB->m_InvestorFactory->getNext();
	}
	m_DB->m_InvestorFactory->endGet();

	///��տͻ��ڻ���֤���ʱ�����
	CInvestorMargin *pInvestorMargin;
	pInvestorMargin=m_DB->m_InvestorMarginFactory->getFirst();
	while (	pInvestorMargin!=NULL)
	{
		m_DB->m_InvestorMarginFactory->remove(pInvestorMargin);
		pInvestorMargin=m_DB->m_InvestorMarginFactory->getNext();
	}
	m_DB->m_InvestorMarginFactory->endGet();

	///��տͻ��������ʱ�����
	CInvestorFee *pInvestorFee;
	pInvestorFee=m_DB->m_InvestorFeeFactory->getFirst();
	while (	pInvestorFee!=NULL)
	{
		m_DB->m_InvestorFeeFactory->remove(pInvestorFee);
		pInvestorFee=m_DB->m_InvestorFeeFactory->getNext();
	}
	m_DB->m_InvestorFeeFactory->endGet();

	///����û�������
	CUser *pUser;
	pUser=m_DB->m_UserFactory->getFirst();
	while (	pUser!=NULL)
	{
		m_DB->m_UserFactory->remove(pUser);
		pUser=m_DB->m_UserFactory->getNext();
	}
	m_DB->m_UserFactory->endGet();

	///����û�Ͷ���߹�ϵ������
	CUserInvestor *pUserInvestor;
	pUserInvestor=m_DB->m_UserInvestorFactory->getFirst();
	while (	pUserInvestor!=NULL)
	{
		m_DB->m_UserInvestorFactory->remove(pUserInvestor);
		pUserInvestor=m_DB->m_UserInvestorFactory->getNext();
	}
	m_DB->m_UserInvestorFactory->endGet();

	///����û�����Ȩ�ޱ�����
	CUserTradingRight *pUserTradingRight;
	pUserTradingRight=m_DB->m_UserTradingRightFactory->getFirst();
	while (	pUserTradingRight!=NULL)
	{
		m_DB->m_UserTradingRightFactory->remove(pUserTradingRight);
		pUserTradingRight=m_DB->m_UserTradingRightFactory->getNext();
	}
	m_DB->m_UserTradingRightFactory->endGet();

	///��ս���Ա���߻Ự����
	CUserSession *pUserSession;
	pUserSession=m_DB->m_UserSessionFactory->getFirst();
	while (	pUserSession!=NULL)
	{
		m_DB->m_UserSessionFactory->remove(pUserSession);
		pUserSession=m_DB->m_UserSessionFactory->getNext();
	}
	m_DB->m_UserSessionFactory->endGet();

	///�����󱾵ر���������
	CMaxLocalID *pMaxLocalID;
	pMaxLocalID=m_DB->m_MaxLocalIDFactory->getFirst();
	while (	pMaxLocalID!=NULL)
	{
		m_DB->m_MaxLocalIDFactory->remove(pMaxLocalID);
		pMaxLocalID=m_DB->m_MaxLocalIDFactory->getNext();
	}
	m_DB->m_MaxLocalIDFactory->endGet();

	///����û����ر���������
	CBrkUserIDLocalID *pBrkUserIDLocalID;
	pBrkUserIDLocalID=m_DB->m_BrkUserIDLocalIDFactory->getFirst();
	while (	pBrkUserIDLocalID!=NULL)
	{
		m_DB->m_BrkUserIDLocalIDFactory->remove(pBrkUserIDLocalID);
		pBrkUserIDLocalID=m_DB->m_BrkUserIDLocalIDFactory->getNext();
	}
	m_DB->m_BrkUserIDLocalIDFactory->endGet();

	///��ս��ױ�����ϱ�֤����������
	CClientMarginCombType *pClientMarginCombType;
	pClientMarginCombType=m_DB->m_ClientMarginCombTypeFactory->getFirst();
	while (	pClientMarginCombType!=NULL)
	{
		m_DB->m_ClientMarginCombTypeFactory->remove(pClientMarginCombType);
		pClientMarginCombType=m_DB->m_ClientMarginCombTypeFactory->getNext();
	}
	m_DB->m_ClientMarginCombTypeFactory->endGet();

	///��պ�Լ�ͺ�Լ���ϵ����
	CInstrumentGroup *pInstrumentGroup;
	pInstrumentGroup=m_DB->m_InstrumentGroupFactory->getFirst();
	while (	pInstrumentGroup!=NULL)
	{
		m_DB->m_InstrumentGroupFactory->remove(pInstrumentGroup);
		pInstrumentGroup=m_DB->m_InstrumentGroupFactory->getNext();
	}
	m_DB->m_InstrumentGroupFactory->endGet();

	///��ս������ӷ��ʱ�����
	CSGEDeferRate *pSGEDeferRate;
	pSGEDeferRate=m_DB->m_SGEDeferRateFactory->getFirst();
	while (	pSGEDeferRate!=NULL)
	{
		m_DB->m_SGEDeferRateFactory->remove(pSGEDeferRate);
		pSGEDeferRate=m_DB->m_SGEDeferRateFactory->getNext();
	}
	m_DB->m_SGEDeferRateFactory->endGet();

	///���Ͷ���߽���Ȩ�ޱ�����
	CInvestorTradingRight *pInvestorTradingRight;
	pInvestorTradingRight=m_DB->m_InvestorTradingRightFactory->getFirst();
	while (	pInvestorTradingRight!=NULL)
	{
		m_DB->m_InvestorTradingRightFactory->remove(pInvestorTradingRight);
		pInvestorTradingRight=m_DB->m_InvestorTradingRightFactory->getNext();
	}
	m_DB->m_InvestorTradingRightFactory->endGet();

	///��ս���ԱIP��ַ����
	CUserIP *pUserIP;
	pUserIP=m_DB->m_UserIPFactory->getFirst();
	while (	pUserIP!=NULL)
	{
		m_DB->m_UserIPFactory->remove(pUserIP);
		pUserIP=m_DB->m_UserIPFactory->getNext();
	}
	m_DB->m_UserIPFactory->endGet();

	///��տͻ���Ȩ�������ʱ�����
	CInvestorOptionFee *pInvestorOptionFee;
	pInvestorOptionFee=m_DB->m_InvestorOptionFeeFactory->getFirst();
	while (	pInvestorOptionFee!=NULL)
	{
		m_DB->m_InvestorOptionFeeFactory->remove(pInvestorOptionFee);
		pInvestorOptionFee=m_DB->m_InvestorOptionFeeFactory->getNext();
	}
	m_DB->m_InvestorOptionFeeFactory->endGet();

	///���ί���ӳٱ�����
	COrderDelay *pOrderDelay;
	pOrderDelay=m_DB->m_OrderDelayFactory->getFirst();
	while (	pOrderDelay!=NULL)
	{
		m_DB->m_OrderDelayFactory->remove(pOrderDelay);
		pOrderDelay=m_DB->m_OrderDelayFactory->getNext();
	}
	m_DB->m_OrderDelayFactory->endGet();

	///���QDPϵͳ��Ϣ����
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
	///��ɱ�Ҫ���������
	///��ɽ������ͻ�������Ӧ���ʻ�������
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
		//�ú�Լû�У��Ͳ����º�Լ
		/// ����Լ����ֵ�ĺ����ԣ����Ϸ�����linxb 20130730
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
		//��Լ��Ϣ��ȫ��ͬ���ø���
		const int nBufSize=4000;
		char buf1[nBufSize];
		char buf2[nBufSize];
		memset(buf1,0,nBufSize);
		memset(buf2,0,nBufSize);
		pInstrument->dumpString(buf1);
		wtbInstrument.dumpString(buf2);
		if (strcmp(buf1,buf2))
		{
			
			/// ����Լ����ֵ�ĺ����ԣ����Ϸ�����linxb 20130730
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
	//��Ѱ���Ƿ��м�¼,���û�м�¼���룬����м�¼�����κδ�ʩ
	//�ֲ����������оͻ��нϴ�ı仯���ֲ�ֵ��Ҫ��һ�β�ѯ�������
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
	//�ֲֵĻ��һ�������ֲ�ͬ�������
	//1���Ѿ�ͨ���ļ��ϳ����Ͳ���Ҫ���
	//2��û���ļ��ϳ�������ǰ��ѯ�õ��ֲ֣���ʱ��Ҫ���
	//3��û���ļ��ϳ������в�ѯ�õ��ֲ֣��������������ļ���������ʱ����Ѿ��гɽ�����ֲֳɱ���Ҫ���¼���
	//4�����ֲ̳��Ѿ���ɣ�����������������ʱ�Ѿ��гֲ֣��������


	//���ñ�֤�����¼���һ��
	//�ڻ��������ñ�֤��
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
		//���㸡��ӯ��
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
	
	//EXRISKG-568 ����pExchange��ָ������
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
		//�ú�Լû�У��Ͳ����º�Լ
		/// ����ʽ�����ֵ�ĺ����ԣ����Ϸ�����
		if( !pExCapitalDataField->Available.isValid())
		{
			REPORT_EVENT(LOG_CRITICAL,"InvestorAccount Property Error.","AccountID:[%s],Available:[%f]", \
				pExCapitalDataField->AccountID.getValue(),pExCapitalDataField->Available.getValue());
		}
			m_DB->m_InvestorAccountFactory->add(&wtbAccount,pTransaction);
	}
	else
	{
		//�ʽ���Ϣ��ȫ��ͬ���ø���
		const int nBufSize=4000;
		char buf1[nBufSize];
		char buf2[nBufSize];
		memset(buf1,0,nBufSize);
		memset(buf2,0,nBufSize);
		pAccount->dumpString(buf1);
		wtbAccount.dumpString(buf2);
		if (strcmp(buf1,buf2))
		{
			
			/// ����ʽ�����ֵ�ĺ����ԣ����Ϸ�����
			if( !pExCapitalDataField->Available.isValid())
			{
				REPORT_EVENT(LOG_CRITICAL,"InvestorAccount Property Error.","AccountID:[%s],Available:[%f]", \
					pExCapitalDataField->AccountID.getValue(),pExCapitalDataField->Available.getValue());
			}
/*** SIR XXXXX BEGIN ***/
			//�������͵��ʽ���Ϣ�в���Ͷ���߱�ţ��˴���Ҫ�������¼�¼�е�Ͷ���߱�Ÿ��¹���
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
