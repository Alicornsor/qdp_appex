/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file TradingQueryServiceImpl.cpp
///@brief�������� CTradingQueryServiceImpl �����������ʵ�ֲ�ѯ�Ĺ��ܡ�
///      ��鴫��Ĳ������Ƿ�Ϊ�Ϸ��Ĳ��������ݲ����Ƿ�Ϊ�գ��Լ����ݿ�ģ���ж���Ĳ�ѯ��������ѯ��������¼��
///@history 
///20121219	longqy@cffex.net �����ļ�

#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "TradingQueryServiceImpl.h"
#include "errorDefine.h"
#include "tradingTools.h"
#include "databaseIteratorRepository.h"
#include "TradingQueryPredicts.h"

///-------
//	xuzh��20090327��NT-0070����qkernel��ѯ���Ż�
//	xuzh��20090510��NT-0070�жԺ�Լ��ѯ�������ѯ���Ż�����
///-------

CTradingQueryImpl::CTradingQueryImpl(CMemoryDB *pDB,CErrorEngine *pEngine)
{
	m_DB = pDB;
	m_ErrorEngine = pEngine;
}

CTradingQueryImpl::~CTradingQueryImpl()
{
}

/*	�����û����ͣ��ж��û��Ƿ����Ա��
/// �ǹ���Ա���򷵻� true; ���ǹ���Ա���򷵻� false; 
*/
bool CTradingQueryImpl::isAdmin(const CUserIDType &userID,CBrokerIDType &BrokerID)
{
	CUserFactory *thisFactory = m_DB->m_UserFactory;	
	// ��User���в����û�
	CUser *pUser = thisFactory->findByBrokerIDUserID(BrokerID,userID);	
	if(NULL == pUser)
	{	// ���û�в�ѯ���û������ʾ����û��Ƿ�
		// ��Ϊ�û��ܹ���¼�����û����ڣ���δ�����ԶҲ����ִ�С�
		m_ErrorEngine->reportError(ERROR_USERID_CANNOT_BE_FOUND);
		return false;
	}else
	{
		if( UT_Manager == pUser->UserType)
		{ // �����ǹ���Ա
			return true;
		}else
		{
			return false;
		}
	}	
}

// �������Ŀǰ��ʹ��
bool CTradingQueryImpl::CheckUser(const CUserIDType& queryUserID,const CUserIDType& loginUserID,CBrokerIDType &BrokerID)
{
	if (queryUserID != loginUserID)
	{	// �û���¼��ID �� ��Ҫ��ѯ�� UserID ��һ�¡����������˵���Ϣ
		m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
		return false;
	}

	CUserFactory *thisFactory = m_DB->m_UserFactory;	
	// ��User���в����û�
	CUser *pUser = thisFactory->findByBrokerIDUserID(BrokerID,queryUserID);	
	if(NULL == pUser)
	{	// ���û�в�ѯ���û������ʾ����û��Ƿ�
		m_ErrorEngine->reportError(ERROR_USERID_CANNOT_BE_FOUND);
		return false;
	}else
	{
		return true;
	}
}

bool CTradingQueryImpl::setRange(const TSessionRef &sessionRef,CParticipantIDType &clearingPartID,
	CParticipantIDType &participantID)
{
	return false;
}

///------
///	���ͻ�Ҫ��ѯ������ʱ�򣬲�����Ҫ��ѯ Order ����Ҫ��ѯ OrderInsertFailed ������
/// ���������
/// brokerID		���͹�˾���
/// userID   		�û�����
/// exchangeID		����������
/// investorID		Ͷ���߱��
/// orderSysID		������ϵͳ���
/// instrumentID	��Լ����
/// logBrokerID		��¼���͹�˾���
/// logUserID		��¼�û�����
/// sessionRef		���õĻỰ����
/// pTransaction	�������ָ��
///
/// ���������
///	pIterator		������ָ���ָ�룬���ڷ��ز�ѯ���Ķ���
///------
bool CTradingQueryImpl::QueryOrder(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CExchangeIDType& exchangeID,
					CInvestorIDType& investorID,
					COrderSysIDType& orderSysID,
					CInstrumentIDType& instrumentID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					COrderIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
	if (brokerID != logBrokerID)
	{	// �û���¼��BrokerID �� ��Ҫ��ѯ�� BrokerID ��һ�¡����������˵���Ϣ
		m_ErrorEngine->reportError(ERROR_BROKERID_MISMATCH); 
		return false;
	}
	if ( ! isAdmin(logUserID,brokerID) )
	{ // ���ǹ���Ա���Ų���Ȩ��
		//�ӽ���������֮�� ������UserIDû��,��û��userid������£�Ҳ��Ҫ��ѯ
		if ( userID.isNull() )
		{
		  // ֧�ְ�InvestorID��ѯ ����UserIDȱʡʱ����ѯ��INVESTORID������USER��ί�� 2014-08-07
		  // û�������û�ID��ǿ�����á���Ϊֻ�ܲ�ѯ�Լ����˻�
		  //	userID = logUserID;
			//	USERID��INVESTORID����ͬʱΪ��
			if (investorID.isNull())
			{
				m_ErrorEngine->reportError(ERROR_USERID_INVESTORID_BOTHBLANK);
				return false;
			}
			//���ܲ�ѯδ����������¼�û���INVESTORί��
		  	if (! CheckUserInvestor(brokerID,logUserID,investorID))
		  	{
				m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
				return false;
			}
		}
		else
		{
// 			if (userID != logUserID) 
// 			{	// �û���¼��ID �� ��Ҫ��ѯ�� UserID ��һ�¡����������˵���Ϣ
// 				m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
// 				return false;
//			}
			userID = logUserID;
			if(!investorID.isNull())
			{
				///xuzh 20150713  ���ɲ�ѯ�˵�¼�û��޷�������Ͷ���ߵı���
		  		if (!CheckUserInvestor(brokerID,logUserID,investorID))
		  		{
					m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
					return false;
				}
			}
		}
	}
	
	COrderFactory *thisFactory = m_DB->m_OrderFactory;
	
	COrderPredict *pPredict;
	pPredict=new COrderAndPredict(new COrderAndPredict(new COrderExchangeIDPredict(&exchangeID,&exchangeID),
				new COrderAndPredict(new COrderInvestorIDPredict(&investorID,&investorID),
				new COrderAndPredict(new COrderInstrumentIDStartPredict(&instrumentID,&instrumentID),
				new COrderOrderSysIDPredict(&orderSysID,&orderSysID) ) ) ),new COrderBrokerIDPredict(&brokerID,&brokerID));
	
	COrderIterator *pBaseIterator;
	if (!userID.isNull())
	{
		if (!exchangeID.isNull())
		{
			if (!orderSysID.isNull())
			{
				pBaseIterator = new COrderSingleIterator(thisFactory,thisFactory->findByExchangeIDAndOrderSysID(exchangeID,orderSysID));
			}
			else if (!investorID.isNull())
			{
				pBaseIterator = new COrderIteratorAllByExchIDInvIDUserID(thisFactory,exchangeID,investorID,userID);
			}
			else if (!instrumentID.isNull())
			{
				pBaseIterator = new COrderIteratorAllByExchIDInstruIDUserID(thisFactory,exchangeID,instrumentID,userID);
			}
			else
			{
				pBaseIterator = new COrderIteratorAll(thisFactory);
			}
		}
		else
		{
//			pBaseIterator = new COrderIteratorAllByUserID(thisFactory,userID);
			pBaseIterator = new COrderIteratorAll(thisFactory);
		}
	}
	else
	{
		if(!investorID.isNull())
		{
			pBaseIterator = new COrderIteratorAllByInvestorID(thisFactory,investorID);
		}
		else
		{
			pBaseIterator = new COrderIteratorAll(thisFactory);
		}
	}

	*pIterator = new COrderFilter(pBaseIterator,pPredict);
	return true;
}

/* ����OrderInsertFailed�ı�ṹ��������Order��һ���ġ������Ĳ�ѯ�����뱨������һ���ġ�
/// ���������
/// brokerID		���͹�˾���
/// userID   		�û�����
/// exchangeID		����������
/// investorID		Ͷ���߱��
/// orderSysID		������ϵͳ���
/// instrumentID	��Լ����
/// logBrokerID		��¼���͹�˾���
/// logUserID		��¼�û�����
/// sessionRef		���õĻỰ����
/// pTransaction	�������ָ��
///
/// ���������
///	pIterator		������ָ���ָ�룬���ڷ��ز�ѯ���Ķ���
*/
bool CTradingQueryImpl::QueryOrderInsertFailed(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CExchangeIDType& exchangeID,
					CInvestorIDType& investorID,
					COrderSysIDType& orderSysID,
					CInstrumentIDType& instrumentID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					COrderInsertFailedIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)	
{
	if (brokerID != logBrokerID)
	{	// �û���¼��BrokerID �� ��Ҫ��ѯ�� BrokerID ��һ�¡����������˵���Ϣ
		m_ErrorEngine->reportError(ERROR_BROKERID_MISMATCH); 
		return false;
	}
	if ( ! isAdmin(logUserID,brokerID) )
	{ // ���ǹ���Ա���Ų���Ȩ��
		if ( userID.isNull() )
		{ // ֧�ְ�InvestorID��ѯ ����UserIDȱʡʱ����ѯ��INVESTORID������USER��ί�� 2014-08-07 liumeng
		  // û�������û�ID��ǿ�����á���Ϊֻ�ܲ�ѯ�Լ����˻�
		  //	userID = logUserID;
			//	USERID��INVESTORID����ͬʱΪ��
			if (investorID.isNull())
			{
				m_ErrorEngine->reportError(ERROR_USERID_INVESTORID_BOTHBLANK);
				return false;
			}
			//���ܲ�ѯδ����������¼�û���INVESTORί��
		  	if (! CheckUserInvestor(brokerID,logUserID,investorID))
		  	{
				m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
				return false;
			}
		}else
		{
			if (userID != logUserID) 
			{	// �û���¼��ID �� ��Ҫ��ѯ�� UserID ��һ�¡����������˵���Ϣ
				m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
				return false;
			}
		}	
	}
	
	COrderInsertFailedFactory *thisFactory = m_DB->m_OrderInsertFailedFactory;
	
	COrderInsertFailedPredict *pPredict;
	pPredict=new COrderInsertFailedAndPredict(new COrderInsertFailedAndPredict(new COrderInsertFailedUserIDPredict(&userID,&userID),
				new COrderInsertFailedAndPredict(new COrderInsertFailedExchangeIDPredict(&exchangeID,&exchangeID),
				new COrderInsertFailedAndPredict(new COrderInsertFailedInvestorIDPredict(&investorID,&investorID),
				new COrderInsertFailedAndPredict(new COrderInsertFailedInstrumentIDStartPredict(&instrumentID,&instrumentID),
				new COrderInsertFailedOrderSysIDPredict(&orderSysID,&orderSysID) ) ) ) ),new COrderInsertFailedBrokerIDPredict(&brokerID,&brokerID));
	
	COrderInsertFailedIterator *pBaseIterator;
	if (!userID.isNull())
	{
		if (!exchangeID.isNull())
		{
			if (!orderSysID.isNull())
			{
				pBaseIterator = new COrderInsertFailedSingleIterator(thisFactory,thisFactory->findByExchangeIDAndOrderSysID(exchangeID,orderSysID));
			}
			else if (!investorID.isNull())
			{
				// pBaseIterator = new COrderInsertFailedIteratorAllByExchIDCliIDUserID(thisFactory,exchangeID,clientID,userID);
				pBaseIterator = new COrderInsertFailedIteratorAllByExchIDInvIDUserID(thisFactory,exchangeID,investorID,userID);
			}
			else if (!instrumentID.isNull())
			{
				pBaseIterator = new COrderInsertFailedIteratorAllByExchIDInstruIDUserID(thisFactory,exchangeID,instrumentID,userID);
			}		
			else
			{
				pBaseIterator = new COrderInsertFailedIteratorAll(thisFactory);
			}
		}
		else
		{
			pBaseIterator = new COrderInsertFailedIteratorAll(thisFactory);
		}
	}
	else
	{
		pBaseIterator = new COrderInsertFailedIteratorAll(thisFactory);
	}

	*pIterator = new COrderInsertFailedFilter(pBaseIterator,pPredict);
	return true;
}

/*  QueryTrade ��ѯ�ɽ���
/// ���������
/// brokerID		���͹�˾���
/// userID   		�û�����
/// exchangeID		����������
/// investorID		Ͷ���߱��
/// orderSysID		������ϵͳ���
/// instrumentID	��Լ����
/// logBrokerID		��¼���͹�˾���
/// logUserID		��¼�û�����
/// sessionRef		���õĻỰ����
/// pTransaction	�������ָ��
///
/// ���������
///	pIterator		������ָ���ָ�룬���ڷ��ز�ѯ���Ķ���
*/
bool CTradingQueryImpl::QueryTrade(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CExchangeIDType& exchangeID,
					CInvestorIDType& investorID,
					CTradeIDType& tradeID,
					CInstrumentIDType& instrumentID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CTradeIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
	if (brokerID != logBrokerID)
	{	// �û���¼��BrokerID �� ��Ҫ��ѯ�� BrokerID ��һ�¡����������˵���Ϣ
		m_ErrorEngine->reportError(ERROR_BROKERID_MISMATCH); 
		return false;
	}
	if ( ! isAdmin(logUserID,brokerID) )
	{ // ���ǹ���Ա���Ų���Ȩ��
		if ( userID.isNull() )
		{ // û�������û�ID��ǿ�����á���Ϊֻ�ܲ�ѯ�Լ����˻�
			//userID = logUserID;
			if(investorID.isNull())
			{
				m_ErrorEngine->reportError(ERROR_USERID_INVESTORID_BOTHBLANK);
				return false;
			}
			//���ܲ�ѯδ����������¼�û���INVESTORί��
			if (! CheckUserInvestor(brokerID,logUserID,investorID))
		  	{
				m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
				return false;
			}
		}else
 		{
// 			if (userID != logUserID) 
// 			{	// �û���¼��ID �� ��Ҫ��ѯ�� UserID ��һ�¡����������˵���Ϣ
// 				m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
// 				return false;
// 			}
			if(!investorID.isNull())
			{
				if (! CheckUserInvestor(brokerID,logUserID,investorID))
		  		{
					m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
					return false;
				}
			}
		}	
	}
	
	CTradeFactory *thisFactory = m_DB->m_TradeFactory;
	
	CTradePredict *pPredict;
	pPredict=new CTradeAndPredict(
		new CTradeAndPredict(new CTradeExchangeIDPredict(&exchangeID,&exchangeID),
		new CTradeAndPredict(new CTradeInstrumentIDStartPredict(&instrumentID,&instrumentID),
		new CTradeAndPredict(new CTradeTradeIDPredict(&tradeID,&tradeID),
							 new CTradeInvestorIDPredict(&investorID,&investorID)))),new CTradeBrokerIDPredict(&brokerID,&brokerID));

	CTradeIterator *pBaseIterator;
	if (!userID.isNull())
	{
		if (!exchangeID.isNull())
		{
			if (!tradeID.isNull())
			{
				//pBaseIterator = new CTradeSingleIterator(thisFactory,thisFactory->findByExchangeIDAndTradeID(exchangeID,tradeID));
				pBaseIterator = new CTradeIteratorByExchangeIDAndTradeID(thisFactory,exchangeID,tradeID);
			}
			else if (!investorID.isNull())
			{
//				pBaseIterator = new CTradeIteratorAllByExchIDCliIDUserID(thisFactory,exchangeID,clientID,userID);
				pBaseIterator = new CTradeIteratorAllByExchIDInvIDUserID(thisFactory,exchangeID,investorID,userID);
			}
			else if (!instrumentID.isNull())
			{
				pBaseIterator = new CTradeIteratorAllByExchIDInstruIDUserID(thisFactory,exchangeID,instrumentID,userID);
			}		
			else
			{
				pBaseIterator = new CTradeIteratorAll(thisFactory);
			}
		}
		else
		{
			pBaseIterator = new CTradeIteratorAll(thisFactory);
		}
	}
	else
	{
		if(!investorID.isNull())
		{
			pBaseIterator = new CTradeIteratorAllByInvestorID(thisFactory,investorID);
		}
		else
		{
			pBaseIterator = new CTradeIteratorAll(thisFactory);
		}
	}

	*pIterator = new CTradeFilter(pBaseIterator,pPredict);
	return true;
}


///-----
///	xuzh��20070224�������˿ͻ�������Ϊ��ѯ����
///-----

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionClientTypePredict���ж�һ���ͻ��ֲ��Ƿ�����ͻ�����������ν��
///@author	xuzh
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionClientTypePredict: public CInvestorPositionPredict
{
private:
	CMemoryDB *m_DB;
	CClientTypeType *m_pClientType;
public:
	///���췽��
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	///@param	pClientType	ָ��Ҫ��Ŀͻ����͡����ΪNULL����ֵΪ�ո�����Դ�����
	CInvestorPositionClientTypePredict(CMemoryDB *pDB, CClientTypeType *pClientType)
	{
		m_DB = pDB;
		m_pClientType = pClientType;
	}
};

/// ��Լ���ǹ�����Ϣ��ֻҪ���ܹ���¼���û��������Բ�ѯ��Լ��
/// ���������
/// exchangeID		����������
/// productID		��Ʒ����
/// instrumentID	��Լ����
/// sessionRef		���õĻỰ����
/// pTransaction	�������ָ��
///
/// ���������
///	pIterator		������ָ���ָ�룬���ڷ��ز�ѯ���Ķ���
bool CTradingQueryImpl::QueryInstrument(
					CExchangeIDType& exchangeID,
					CProductIDType& productID,
					CInstrumentIDType& instrumentID,
					CInstrumentIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
	
	CInstrumentFactory *thisFactory = m_DB->m_InstrumentFactory;
	
	CInstrumentPredict *pPredict;
	pPredict=new CInstrumentAndPredict(new CInstrumentExchangeIDPredict(&exchangeID,&exchangeID),
				new CInstrumentAndPredict(new CInstrumentProductIDPredict(&productID,&productID),
				new CInstrumentInstrumentIDStartPredict(&instrumentID,&instrumentID)));

	CInstrumentIterator *pBaseIterator;
	if (!instrumentID.isNull())
	{
		pBaseIterator= new CInstrumentIteratorAllByInstrumentID(thisFactory,instrumentID);
	}
	else if(!productID.isNull())
	{
		pBaseIterator= new CInstrumentIteratorAllByProductID(thisFactory,productID);	
	}
	else if(!exchangeID.isNull())
	{
		pBaseIterator= new CInstrumentIteratorAllByExchangeID(thisFactory,exchangeID);	
	}else
	{
		pBaseIterator= new CInstrumentIteratorAll(thisFactory);		
	}

	*pIterator = new CInstrumentFilter(pBaseIterator,pPredict);
	return true;
}

/// ���������
/// exchangeID		����������
/// instrumentID	��Լ����
/// sessionRef		���õĻỰ����
/// pTransaction	�������ָ��
///
/// ���������
///	pIterator		������ָ���ָ�룬���ڷ��ز�ѯ���Ķ���
bool CTradingQueryImpl::QueryMarketData(
					CExchangeIDType& exchangeID,
					CInstrumentIDType& instrumentID,
					CMarketDataIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
	/*CInstrumentFactory *thisFactory = m_DB->m_InstrumentFactory;
	
	CInstrumentPredict *pPredict;
	pPredict=new CInstrumentAndPredict(new CInstrumentExchangeIDPredict(&exchangeID,&exchangeID),
		new CInstrumentInstrumentIDStartPredict(&instrumentID,&instrumentID));

	CInstrumentIterator *pBaseIterator;
	pBaseIterator= new CInstrumentIteratorAllByInstrumentID(thisFactory,instrumentID);

	*pIterator = new CMarketDataOfInstrumentIterator(m_DB->m_MarketDataFactory,new CInstrumentFilter(pBaseIterator,pPredict));*/
	
	CMarketDataFactory *thisFactory = m_DB->m_MarketDataFactory;
	
	CMarketDataPredict *pPredict;
	pPredict=new CMarketDataAndPredict(new CMarketDataExchangeIDPredict(&exchangeID,&exchangeID),
		                               new CMarketDataInstrumentIDStartPredict(&instrumentID,&instrumentID));

	CMarketDataIterator *pBaseIterator;
	pBaseIterator= new CMarketDataIteratorAll(thisFactory);

	*pIterator = new CMarketDataFilter(pBaseIterator, pPredict);
	return true;
}

/// �������Ŀǰû��ʹ��
bool CTradingQueryImpl::QueryUser(
					CUserIDType& userIDStart,
					CUserIDType& userIDEnd,
					CUserIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
	CUserFactory *thisFactory = m_DB->m_UserFactory;
	
	CUserPredict *pPredict;
	pPredict=new CUserUserIDPredict(&userIDStart,&userIDEnd);

	CUserIterator *pBaseIterator;
	pBaseIterator= new CUserIteratorStartByUserID(thisFactory,userIDStart);

	*pIterator = new CUserFilter(pBaseIterator,pPredict,false);
	return true;
}

/*	QueryInvestor ��ѯͶ����
/// ���������
/// brokerID		���͹�˾���
/// userID   		�û�����
/// investorID		Ͷ���߱��
/// logBrokerID		��¼���͹�˾���
/// logUserID		��¼�û�����
/// sessionRef		���õĻỰ����
/// pTransaction	�������ָ��
///
/// ���������
///	pIterator		������ָ���ָ�룬���ڷ��ز�ѯ���Ķ���
*/
bool CTradingQueryImpl::QueryInvestor(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CInvestorIDType& investorID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CInvestorIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)		
{
	if (brokerID != logBrokerID)
	{	// �û���¼��BrokerID �� ��Ҫ��ѯ�� BrokerID ��һ�¡����������˵���Ϣ
		m_ErrorEngine->reportError(ERROR_BROKERID_MISMATCH); 
		return false;
	}
	// Added by Longqy 2012.12.04
	if (!isAdmin(logUserID,brokerID))
	{	
		if ( userID.isNull() )
		{ // û�������û�ID��ǿ�����á���Ϊֻ�ܲ�ѯ�Լ����˻�
			userID = logUserID;
		}else
		{
			if (userID != logUserID) 
			{	// �û���¼��ID �� ��Ҫ��ѯ�� UserID ��һ�¡����������˵���Ϣ
				m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
				return false;
			}
		}
			if (! CheckUserInvestor(brokerID,logUserID,investorID))
		{
			m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
			return false;
		}
	}
	
	CInvestorFactory *thisFactory = m_DB->m_InvestorFactory;
	CInvestorPredict *pPredict;
	pPredict= new CInvestorAndPredict(new CInvestorBrokerIDPredict(&brokerID,&brokerID),
				new CInvestorInvestorIDPredict(&investorID,&investorID));

	CInvestorIterator *pBaseIterator;
	pBaseIterator= new CInvestorIteratorByInvestorID(thisFactory,investorID);

	*pIterator = new CInvestorFilter(pBaseIterator,pPredict,false);
	
	return true;
}

/*	QueryInvestorAccount Ͷ�����ʽ��ʺŲ�ѯ
/// ���������
/// brokerID		���͹�˾���
/// userID   		�û�����
/// investorID		Ͷ���߱��
/// logBrokerID		��¼���͹�˾���
/// logUserID		��¼�û�����
/// sessionRef		���õĻỰ����
/// pTransaction	�������ָ��
///
/// ���������
///	pIterator		������ָ���ָ�룬���ڷ��ز�ѯ���Ķ���
*/
bool CTradingQueryImpl::QueryInvestorAccount(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CInvestorIDType& investorID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CInvestorAccountIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
	// InvestorIDVector vInvestorID;
	vInvestorID.clear();
	bool	bHasInvestor = false;
	//  ���InvestorIDΪ�գ��������ֱ�ӷ��� 2013.01.23
/*  ����UserID������Ϊ�ա�
	if (investorID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_QUERY_INVESTORACCOUNT_INVESTORID_ISNULL); 
		return false;
	}
*/	
	if (brokerID != logBrokerID)
	{	// �û���¼��BrokerID �� ��Ҫ��ѯ�� BrokerID ��һ�¡����������˵���Ϣ
		m_ErrorEngine->reportError(ERROR_BROKERID_MISMATCH); 
		return false;
	}
	if (!isAdmin(logUserID,brokerID))
	{	
		if ( userID.isNull() )
		{ // û�������û�ID��ǿ�����á���Ϊֻ�ܲ�ѯ�Լ����˻�
			userID = logUserID;
		}
		else
		{
			if (userID != logUserID) 
			{	// �û���¼��ID �� ��Ҫ��ѯ�� UserID ��һ�¡����������˵���Ϣ
				m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
				return false;
			}
		}

		if (investorID.isNull())
		{
			fromUserGetInvestors(brokerID,userID,vInvestorID);
			bHasInvestor = false;
		}
		else
		{
			if (!CheckUserInvestor(brokerID,logUserID,investorID))
			{
				m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
				return false;
			}
			bHasInvestor = true;
		}		
	}
	else 
	{ // �ǹ���Ա
		if (!investorID.isNull())
		{
			if (! CheckUserInvestor(brokerID,userID,investorID))
			{
				m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
				return false;
			}
			bHasInvestor = true;
		}else
		{
			fromUserGetInvestors(brokerID,userID,vInvestorID);
			bHasInvestor = false;
		}			
	}
	CInvestorAccountFactory *thisFactory = m_DB->m_InvestorAccountFactory;
	CInvestorAccountPredict *pPredict=NULL;
	
	if(bHasInvestor)
	{
		pPredict= new CInvestorAccountAndPredict(new CInvestorAccountBrokerIDPredict(&brokerID,&brokerID),
			new CInvestorAccountInvestorIDPredict(&investorID,&investorID));
	}
	else
	{   // ����investorID Ϊ�գ��� userID ���ҵ� investorID ����
		int iCount;
		CInvestorAccountPredict* pMultiPredict=NULL;
		for(iCount=0;iCount<vInvestorID.size();iCount++)
		{
			if(iCount<1)
			{
				pMultiPredict = new CInvestorAccountInvestorIDPredict(&vInvestorID[iCount],&vInvestorID[iCount]);
			}
			else
			{
				pMultiPredict = new CInvestorAccountOrPredict(pMultiPredict,new CInvestorAccountInvestorIDPredict(&vInvestorID[iCount],&vInvestorID[iCount]));
			}			
		}
		//CInvestorIDType sNotExistInvestorID="999999999999999999";
		CInvestorIDType sNotExistInvestorID = CAN_NOT_EXIST_INVESTORID;
		if (NULL == pMultiPredict)
		{
			pMultiPredict = new CInvestorAccountInvestorIDPredict(&sNotExistInvestorID,&sNotExistInvestorID);
		}

		pPredict= new CInvestorAccountAndPredict(new CInvestorAccountBrokerIDPredict(&brokerID,&brokerID),pMultiPredict);
	}

	CInvestorAccountIterator *pBaseIterator;
	
	if (!investorID.isNull())
	{
		pBaseIterator = new CInvestorAccountIteratorAllByInvestorID(thisFactory,investorID);
	}
	else if( 1 == vInvestorID.size())
	{
		pBaseIterator = new CInvestorAccountIteratorAllByInvestorID(thisFactory,vInvestorID[0]);
	}
	else if(!brokerID.isNull())
	{
		pBaseIterator = new CInvestorAccountIteratorAllByBrokerID(thisFactory,brokerID);
	}
	else
	{
		pBaseIterator = new CInvestorAccountIteratorAll(thisFactory);	
	}

	// ע�⣬������������� false����ʾ�ڲ�ѯ��ʱ�򣬲�Ҫ����һ����¼��һ���ǽ�������һ����¼�����ҷ���������
	//���ܲ���� ���Ϊtrue���м�ֻҪ��һ����¼��������������ѯ����ֹ�����º��滹�м�¼������������Ҳ���ٲ�ѯ��	
	*pIterator = new CInvestorAccountFilter(pBaseIterator,pPredict,false);
	return true;
}

/*	QueryExchange ��������Ϣ��ѯ
/// ��������Ϣ�ǹ����ģ�ֻҪ�ܹ���¼���û������Բ�ѯ������Ҫ����Ȩ�޼�顣
/// ���������
/// exchangeID		����������
/// sessionRef		���õĻỰ����
/// pTransaction	�������ָ��
///
/// ���������
///	pIterator		������ָ���ָ�룬���ڷ��ز�ѯ���Ķ���
*/
bool CTradingQueryImpl::QueryExchange(
					CExchangeIDType& exchangeID,
					CExchangeIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
	CExchangeFactory *thisFactory = m_DB->m_ExchangeFactory;
	CExchangePredict *pPredict;
	pPredict = new CExchangeExchangeIDPredict(&exchangeID,&exchangeID);

	CExchangeIterator *pBaseIterator;
	if (!exchangeID.isNull())
	{
		pBaseIterator = new CExchangeIteratorStartByExchangeID(thisFactory,exchangeID);
	}
	else 
	{
		pBaseIterator = new CExchangeIteratorAll(thisFactory);
	}

	*pIterator = new CExchangeFilter(pBaseIterator,pPredict,false);
	
	return true;

}

/*	QueryUserInvestor ����Ͷ�����˻���ѯ������ѯ�û���Ͷ�����ʺŵĹ�ϵ
/// ���������
/// brokerID		���͹�˾���
/// userID   		�û�����
/// logBrokerID		��¼���͹�˾���
/// logUserID		��¼�û�����
/// sessionRef		���õĻỰ����
/// pTransaction	�������ָ��
///
/// ���������
///	pIterator		������ָ���ָ�룬���ڷ��ز�ѯ���Ķ���
*/
bool CTradingQueryImpl::QueryUserInvestor(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CUserInvestorIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
/*
	if (userID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_QUERY_USERINVESTOR_USERID_ISNULL); 
		return false;
	}
*/	
	if (brokerID != logBrokerID)
	{	// �û���¼��BrokerID �� ��Ҫ��ѯ�� BrokerID ��һ�¡����������˵���Ϣ
		m_ErrorEngine->reportError(ERROR_BROKERID_MISMATCH); 
		return false;
	}
	if ( ! isAdmin(logUserID,brokerID) )
	{ // ���ǹ���Ա���Ų���Ȩ��
		if ( userID.isNull() )
		{ // û�������û�ID��ǿ�����á���Ϊֻ�ܲ�ѯ�Լ����˻�
			userID = logUserID;
		}else
		{
			if (userID != logUserID) 
			{	// �û���¼��ID �� ��Ҫ��ѯ�� UserID ��һ�¡����������˵���Ϣ
				m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
				return false;
			}
		}
	}
		
	CUserInvestorFactory *thisFactory = m_DB->m_UserInvestorFactory;
	
	CUserInvestorPredict *pPredict;
	pPredict = new CUserInvestorAndPredict(new CUserInvestorBrokerIDPredict(&brokerID,&brokerID),
					new CUserInvestorUserIDPredict(&userID,&userID));

	CUserInvestorIterator *pBaseIterator;
	if (!userID.isNull())
	{
		pBaseIterator = new CUserInvestorIteratorAllByUserID(thisFactory,userID);
	}
	else if(!brokerID.isNull())
	{
		pBaseIterator = new CUserInvestorIteratorAllByBrokerID(thisFactory,brokerID);
	}
	else
	{
		pBaseIterator = new CUserInvestorIteratorAll(thisFactory);
	}

	*pIterator = new CUserInvestorFilter(pBaseIterator,pPredict,false);
	return true;
}

/*  QueryInvestorPosition Ͷ���ֲֲ߳�ѯ
//  ����ӿ�API��ѯ����InvestorPosition�������ڴ����ݿ���û��InvestorPosition��ʵ�����Ǵ�
//  InvestorPosition���в�ѯ��
//  ע����������Ĳ��� clientID���ڿͻ���API��û�еġ�ֻ������һ�����ӵġ���Ϊ��XTP��ͨ��InvestorID 
//  �ҵ����ClientID��
/// ���������
/// brokerID		���͹�˾���
/// userID   		�û�����
/// exchangeID		����������
/// investorID		Ͷ���߱��
/// instrumentID	��Լ����
/// clientID		�ͻ�����
/// logBrokerID		��¼���͹�˾���
/// logUserID		��¼�û�����
/// sessionRef		���õĻỰ����
/// pTransaction	�������ָ��
///
/// ���������
///	pIterator		������ָ���ָ�룬���ڷ��ز�ѯ���Ķ���
*/
bool CTradingQueryImpl::QueryInvestorPosition(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CExchangeIDType& exchangeID,
					CInvestorIDType& investorID,
					CInstrumentIDType& instrumentID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CInvestorPositionIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction)
{
	if (brokerID != logBrokerID)
	{	// �û���¼��BrokerID �� ��Ҫ��ѯ�� BrokerID ��һ�¡����������˵���Ϣ
		m_ErrorEngine->reportError(ERROR_BROKERID_MISMATCH); 
		return false;
	}
	
	bool bHasInvestor = false;
	vInvestorID.clear();
	if (!isAdmin(logUserID,brokerID))
	{
		if ( userID.isNull() )
		{ // û�������û�ID��ǿ�����á���Ϊֻ�ܲ�ѯ�Լ����˻�
			userID = logUserID;
		}
		else
		{
			if (userID != logUserID) 
			{	// �û���¼��ID �� ��Ҫ��ѯ�� UserID ��һ�¡����������˵���Ϣ
				m_ErrorEngine->reportError(ERROR_USER_MISMATCH); 
				return false;
			}
		}
	
		// ���investorID����ֵ���ͽ�����ݼ�飬����Ҫ��ѯ��investorID���û��Ƿ��й�ϵ���޹�ϵ���򱨴�
		if (!investorID.isNull())
		{
			bHasInvestor = true;
			if (! CheckUserInvestor(brokerID,logUserID,investorID))
			{
				m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
				return false;
			}
			vInvestorID.push_back(investorID);
		}
		else
		{
			// ����investorID Ϊ�գ��� userID ���ҵ� investorID ����
			fromUserGetInvestors(brokerID,userID,vInvestorID);
		}
	}
	else
	{ // �ǹ���Ա
		// ���investorID����ֵ���ͽ�����ݼ�飬����Ҫ��ѯ��investorID���û��Ƿ��й�ϵ���޹�ϵ���򱨴�
		if (!investorID.isNull())
		{
			if (! CheckUserInvestor(brokerID,userID,investorID))
			{
				m_ErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
				return false;
			}
			vInvestorID.push_back(investorID);
		}
		else
		{	
			// ����investorID Ϊ�գ��� userID ���ҵ� investorID ����
			fromUserGetInvestors(brokerID,userID,vInvestorID);
		}	
	}
	
	
	CInvestorPositionFactory *thisFactory = m_DB->m_InvestorPositionFactory;
	CInvestorPositionPredict *pPredict;

  
	int iCount;
	CInvestorPositionPredict* pMultiPredict=NULL;
	for(iCount=0;iCount<vInvestorID.size();iCount++)
	{
		CInvestorPositionPredict *pTmpPredict= new CInvestorPositionInvestorIDPredict(&vInvestorID[iCount],&vInvestorID[iCount]);
		if(pMultiPredict==NULL)
		{
			pMultiPredict = pTmpPredict;
		}
		else
		{
			pMultiPredict = new CInvestorPositionOrPredict(pMultiPredict,pTmpPredict);
		}	
	}
	CClientIDType sNotExistInvestorID = CAN_NOT_EXIST_INVESTORID;
	if (NULL == pMultiPredict)
	{
		pMultiPredict = new CInvestorPositionClientIDPredict(&sNotExistInvestorID,&sNotExistInvestorID);
	}

	pPredict= new CInvestorPositionAndPredict(new CInvestorPositionBrokerIDPredict(&brokerID,&brokerID),pMultiPredict);


	CInvestorPositionIterator *pBaseIterator;

	if (!instrumentID.isNull())
	{
		pBaseIterator = new CInvestorPositionIteratorAllByInstrumentID(thisFactory,instrumentID);
	}
	else if(!exchangeID.isNull())
	{
		pBaseIterator = new CInvestorPositionIteratorAllByExchangeID(thisFactory,exchangeID);
	}
	else
	{
		pBaseIterator = new CInvestorPositionIteratorAll(thisFactory);
	}

	*pIterator = new CInvestorPositionFilter(pBaseIterator,pPredict,false);
	return true;
}

/*  ��ѯ�û�Ͷ���߹�ϵ�������Ƿ������brokerID��userID��investorID��ϵļ�¼
//  ���û�������ļ�¼��˵����Щ�������Ϸ����û����������дinvestorID֮���ֵ��ȥ��ѯ���˵Ĳ���
//  �ڵ����������ǰ��Ҫ��֤���� investorID ��Ϊ�ա�
*/
bool CTradingQueryImpl::CheckUserInvestor(const CBrokerIDType& brokerID,
						const CUserIDType& userID,const CInvestorIDType& investorID)
{
	CUserInvestorFactory *thisFactory = m_DB->m_UserInvestorFactory;	
	CUserInvestor * pData = thisFactory->findByBrokerIDUserIDInvestorID(brokerID,userID,investorID);		
	if(pData)
	{	// �м�¼����ΪbrokerID+userID+investorID�����������Խ����Ψһ��
/*
	if (brokerID.isNull())
		{	// brokerIDΪ�գ�˵��brokerIDΪ�κ�ֵ������
			return true;
		}
		if(pData->BrokerID == brokerID)
		{
			return true;
		}else
		{// brokerID ���¼��һ����˵��������¼�������ƥ�䡣�� �������Ϸ�
			return false;
		}
*/
		return true;
	}else
	{
		return false;
	}
}
/*	���û���UserID������ѯ�û���InvestorID��Ŀǰ��һ���û�����Ӧ4��InvestorID��4������������
/// ������� userID һ������Ϊ�ա�brokerID ����Ϊ�ա�
/// ���ڱ� ClientTradingID
*/
void * CTradingQueryImpl::fromUserGetInvestor(const CBrokerIDType& brokerID,const CUserIDType& userID)
{
	CClientTradingIDPredict *pMultiPredict = NULL;
	int	count = 1;

	CUserInvestorFactory *thisFactory = m_DB->m_UserInvestorFactory;	
	CUserInvestor * pData = thisFactory->startFindAllByUserID(userID);		
	while(pData)
	{	// �ҵ�һ����¼�� ����� brokerID ��Ϊ�գ���ʾ brokerID ��������
		if( (brokerID.isNull() ) ||( brokerID == pData->BrokerID))
		{
			// CInvestorIDType sInvestorID;
			// sInvestorID = pData->InvestorID;
			if(count<2)
			{
				pMultiPredict = new CClientTradingIDInvestorIDPredict( 
					const_cast<CInvestorIDType *>(&(pData->InvestorID)),
					const_cast<CInvestorIDType *>(&(pData->InvestorID)) );
				count++;
			}else
			{
				pMultiPredict = new CClientTradingIDOrPredict(pMultiPredict,new CClientTradingIDInvestorIDPredict(
					const_cast<CInvestorIDType *>(&(pData->InvestorID)),
					const_cast<CInvestorIDType *>(&(pData->InvestorID)) ) );
				count++;
			}
		}
		pData = thisFactory->findNextAllByUserID();
	}
	thisFactory->endFindAllByUserID();
	return pMultiPredict;
}


/*	���û���UserID������ѯ�û���InvestorID��Ŀǰ��һ���û�����Ӧ4��InvestorID��4�������������ٲ�ѯ��ClientID
/// ������� userID һ������Ϊ�ա�brokerID ����Ϊ�ա�
/// ����ֱ���ҵ�InvestorIDs
*/
void CTradingQueryImpl::fromUserGetInvestors(const CBrokerIDType& brokerID,const CUserIDType& userID,InvestorIDVector& vInvestorID)
{
	int	count = 1;
	CInvestorIDType sInvestorID;

	CUserInvestorFactory *thisFactory = m_DB->m_UserInvestorFactory;	
	CUserInvestor * pData = thisFactory->startFindAllByUserID(userID);		
	while(pData)
	{	// �ҵ�һ����¼�� ����� brokerID ��Ϊ�գ���ʾ brokerID ��������
		//if( (brokerID.isNull() ) ||( brokerID == pData->BrokerID))
		//{
			sInvestorID = pData->InvestorID;
			vInvestorID.push_back(sInvestorID);
		//}
		pData = thisFactory->findNextAllByUserID();
	}
	thisFactory->endFindAllByUserID();
	return ;
}

/*** SIR XLONG BEGIN ***/
///��֤���ʲ�ѯ:����brokerID�Լ�instrumentID ��ѯ��֤���ʱ�
///˵�������brokerIDΪ�գ������instrumentID�Ƿ�Ϊ�յ�����Ż�CInvestorMarginIteratorAll��instrumentIDΪ�գ�����CInvestorMarginIteratorByInstrumentID��instrumentID��Ϊ�գ�
///      ���򷵻�CInvestorMarginIteratorByBrokerID
///@param   brokerID
///@param	instrumentID
///@return	true��ʾ�ɹ���false��ʾʧ�� 	
bool CTradingQueryImpl::QueryInvestorMargin(
								 CBrokerIDType& brokerID,
								 CInstrumentIDType &instrumentID,
								 CInvestorMarginIterator** pIterator)
{
	CInvestorMarginFactory *pFactory = m_DB->m_InvestorMarginFactory;
	if (!pFactory)
	{
		m_ErrorEngine->reportError(ERROR_NO_CLIENT_MARGIN_FEE_DATA);
		return false;
	}
	
	if (brokerID.isNull())
	{
		if (instrumentID.isNull())
		{
			*pIterator = new CInvestorMarginIteratorAll(pFactory);
		}
		else
		{
			*pIterator = new CInvestorMarginIteratorByInstrumentID(pFactory, instrumentID);
		}
	}
	else
	{
		*pIterator = new CInvestorMarginIteratorByBrokerID(pFactory, brokerID);
	}

	return true;
}

///�������ʲ�ѯ������brokerID�Լ�instrumentID ��ѯ�������ʱ�
///˵�������brokerIDΪ�գ������instrumentID�Ƿ�Ϊ�յ�����Ż�CInvestorMarginIteratorAll��instrumentIDΪ�գ�����CInvestorMarginIteratorByInstrumentID��instrumentID��Ϊ�գ�
///      ���򷵻�CInvestorMarginIteratorByBrokerID
///@param   brokerID
///@param	instrumentID
///@return	true��ʾ�ɹ���false��ʾʧ�� 	
bool CTradingQueryImpl:: QueryInvestorFee(
							  CBrokerIDType& brokerID,
							  CInstrumentIDType &instrumentID,
							  CInvestorFeeIterator** pIterator)

{
	CInvestorFeeFactory *pFactory = m_DB->m_InvestorFeeFactory;
	if (!pFactory) 
	{
		m_ErrorEngine->reportError(ERROR_NO_CLIENT_MARGIN_FEE_DATA);
		return false;
	}
	
	if (brokerID.isNull())
	{
		if (instrumentID.isNull())
		{
			*pIterator = new CInvestorFeeIteratorAll(pFactory);
		}
		else
		{
			*pIterator = new CInvestorFeeIteratorByInstrumentID(pFactory, instrumentID);
		}
	}
	else
	{
		*pIterator = new CInvestorFeeIteratorByBrokerID(pFactory, brokerID);
	}
	return true;
}

///Ͷ���߲�ѯ������userID ��ѯͶ���߱�
///@param   userID
///@return	true��ʾ�ɹ���false��ʾʧ�� 	
bool CTradingQueryImpl:: QueryUserInvestorByUser(
										  CUserIDType& userID,
										  CUserInvestorIteratorAllByUserID** pIterator)
										  
{
	CUserInvestorFactory *pFactory = m_DB->m_UserInvestorFactory;
	if (!pFactory) 
	{
		m_ErrorEngine->reportError(ERROR_USERID_INVESTORID_BOTHBLANK);
		return false;
	}
	
	if (userID.isNull())
	{
		m_ErrorEngine->reportError(ERROR_USERID_INVESTORID_BOTHBLANK);
		return false;
	}
	else
	{
		*pIterator = new CUserInvestorIteratorAllByUserID(pFactory, userID);
	}
	return true;
}
/*** SIR XLONG END ***/

void CTradingQueryImpl::fromInvestorsGetAccount(const CBrokerIDType& brokerID, const CInvestorIDType& investorID, AccountIDVector& vAccountID)
{
	CAccountIDType sAccountID;

	CInvestorAccountFactory *thisFactory = m_DB->m_InvestorAccountFactory;	
	CInvestorAccount * pData = thisFactory->findByBrokerIDInvestorID(brokerID, investorID);
	
	if (NULL != pData)
	{
		sAccountID = pData->AccountID;
		vector<CAccountIDType>::iterator result = find( vAccountID.begin( ), vAccountID.end( ), sAccountID );
		if ( result == vAccountID.end( ) )
		{
			vAccountID.push_back(sAccountID);
		}
	}

	return ;
}

///�������ӷ��ʲ�ѯ����
///@param	sessionRef	�Ự����
///@param	pTransaction	���������ڵ�����
///@return	true��ʾ�ɹ���false��ʾʧ�� 	
bool CTradingQueryImpl::QuerySGEDeferRate(
				   CInstrumentIDType& instrumentID,
				   CSGEDeferRateIterator** pIterator,
				   const TSessionRef &sessionRef,
				   CTransaction *pTransaction)
{
	CSGEDeferRateFactory *thisFactory = m_DB->m_SGEDeferRateFactory;
	
	if (!instrumentID.isNull())
	{
		*pIterator = new CSGEDeferRateIteratorAllByInstrumentID(thisFactory,instrumentID);
	}
	else 
	{
		*pIterator = new CSGEDeferRateIteratorAll(thisFactory);
	}
	
	return true;
}


/*	QueryExchange ����ʱ��ƫ���ѯ����
/// ����ʱ��ƫ���ǹ����ģ�ֻҪ�ܹ���¼���û������Բ�ѯ������Ҫ����Ȩ�޼�顣
/// ���������
/// exchangeID		����������
/// sessionRef		���õĻỰ����
/// pTransaction	�������ָ��
///
/// ���������
///	pIterator		������ָ���ָ�룬���ڷ��ز�ѯ���Ķ���
*/
bool CTradingQueryImpl::QueryExchTimeDiff(
										  CExchangeIDType& exchangeID,
										  CExchTimeDiffIterator** pIterator,
										  const TSessionRef &sessionRef,
										  CTransaction *pTransaction)
{
	CExchTimeDiffFactory *thisFactory = m_DB->m_ExchTimeDiffFactory;
	CExchTimeDiffPredict *pPredict;
	pPredict = new CExchTimeDiffExchangeIDPredict(&exchangeID,&exchangeID);
	
	CExchTimeDiffIterator *pBaseIterator;
	if (!exchangeID.isNull())
	{
		pBaseIterator = new CExchTimeDiffIteratorStartByExchangeID(thisFactory,exchangeID);
	}
	else 
	{
		pBaseIterator = new CExchTimeDiffIteratorAll(thisFactory);
	}
	
	*pIterator = new CExchTimeDiffFilter(pBaseIterator,pPredict,false);
	
	return true;
	
}
