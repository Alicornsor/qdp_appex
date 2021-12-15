
/////////////////////////////////////////////////////////////////////////
///@system ���ǰ������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file TradingQueryServiceImpl.h
///@brief	������TradingQueryServiceImpl�Ľӿ�
///@history 
///20121115	longqy@cffex.net �������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CTRADINGQUERYSERVICE_H
#define CTRADINGQUERYSERVICE_H

#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "CErrorEngine.h"

#include "QueryComplianceParam.h"

/// �������������������ڲ�ѯ��ʱ���ʾ�����ڵı�ʶ�����������ڵ� InvestorID �� ClientID��
#define CAN_NOT_EXIST_INVESTORID "999999999999999999"
#define CAN_NOT_EXIST_CLIENTID   "999999999999999999"

/////////////////////////////////////////////////////////////////////////
///IInitService��һ������������ݳ�ʼ���Ľӿڣ��������ݳ�ʼ������ת��Ϊ
///�ڴ����ݿ������
///@author	
///@version	1.0,20121115
/////////////////////////////////////////////////////////////////////////
class CTradingQueryImpl
{
public:
	CTradingQueryImpl(CMemoryDB *pDB,CErrorEngine *pEngine);
	virtual ~CTradingQueryImpl();
	
	///Ͷ�����ʽ��ѯ����
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QueryInvestorAccount(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CInvestorIDType& investorID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CInvestorAccountIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///������ѯ����
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QueryOrder(
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
					CTransaction *pTransaction);

	///�ɽ�����ѯ����
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QueryTrade(
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
					CTransaction *pTransaction);

	///Ͷ���߲�ѯ����
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QueryInvestor(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CInvestorIDType& investorID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CInvestorIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///������ѯ����
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QueryOrderInsertFailed(
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
					CTransaction *pTransaction);

	///��Լ��ѯ����
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QueryInstrument(
					CExchangeIDType& exchangeID,
					CProductIDType& productID,
					CInstrumentIDType& instrumentID,
					CInstrumentIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///�û���ѯ����
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QueryUser(
					CUserIDType& startUserID,
					CUserIDType& endUserID,
					CUserIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///��������ѯ����
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QueryExchange(
					CExchangeIDType& exchangeID,
					CExchangeIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///����Ͷ�����˻���ѯ����
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QueryUserInvestor(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CUserInvestorIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///Ͷ���ֲֲ߳�ѯ����
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QueryInvestorPosition(
					CBrokerIDType& brokerID,
					CUserIDType& userID,
					CExchangeIDType& exchangeID,
					CInvestorIDType& investorID,
					CInstrumentIDType& instrumentID,
					CBrokerIDType& logBrokerID,
					CUserIDType& logUserID,
					CInvestorPositionIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);

	///��ͨ�����ѯ����
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QueryMarketData(
					CExchangeIDType& exchangeID,
					CInstrumentIDType& instrumentID,
					CMarketDataIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);


/*** SIR XLONG BEGIN ***/
	///��֤���ʲ�ѯ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QueryInvestorMargin(
				CBrokerIDType& brokerID,
				CInstrumentIDType &instrumentID,
				CInvestorMarginIterator** pIterator);
	///�������ʲ�ѯ
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QueryInvestorFee(
		CBrokerIDType& brokerID,
		CInstrumentIDType &instrumentID,
		CInvestorFeeIterator** pIterator);

	///Ͷ���߲�ѯ������userID ��ѯͶ���߱�
	///@param   userID
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QueryUserInvestorByUser(
		CUserIDType& userID,
		CUserInvestorIteratorAllByUserID** pIterator);
/*** SIR XLONG END ***/

	///�������ӷ��ʲ�ѯ����
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QuerySGEDeferRate(
					CInstrumentIDType& instrumentID,
					CSGEDeferRateIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);


	///����ʱ��ƫ���ѯ����
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ�� 	
	virtual bool QueryExchTimeDiff(
					CExchangeIDType& exchangeID,
					CExchTimeDiffIterator** pIterator,
					const TSessionRef &sessionRef,
					CTransaction *pTransaction);
      
private:
	///�ж��û��Ƿ���ϵͳ���е��û�
	///@param	userID	�û��ı��
	///@return	true��ʾ����ȷ��false��ʾ����ȷ
	bool CheckUser(const CUserIDType& queryUserID,const CUserIDType& loginUserID,CBrokerIDType &BrokerID);
	
	///�жϻỰ�Ƿ�Ϊ����Ա
	///@param	sessionRef	�Ự���
	///@return	true��ʾ�ǣ�false��ʾ����
	bool isAdmin(const CUserIDType &userID,CBrokerIDType &BrokerID);	
	
	///���ò�ѯ��Χ
	///@param	sessionRef	�Ự���
	///@param	clearingPartID	Ҫ��ѯ�Ľ����Ա���
	///@param	participantID	Ҫ��ѯ�Ľ��׻�Ա���
	///@return	true��ʾ�ǳɹ���false��ʾʧ��
	bool setRange(const TSessionRef &sessionRef,CParticipantIDType &clearingPartID,
		CParticipantIDType &participantID);
	
	///����û�Ͷ���߹�ϵ���鿴����Ĳ����Ƿ��ж�Ӧ�ļ�¼
	///���м�¼���򷵻�ture�����򣬷���false��
	///@param	brokerID	���͹�˾���
	///@param	userID		�����û�����
	///@param	investorID	Ͷ���߱��
	bool CheckUserInvestor(const CBrokerIDType& brokerID,
						const CUserIDType& userID,const CInvestorIDType& investorID);

	/*  ��ѯ�ͻ����û��Ĺ�ϵ�������Ƿ������clientID��Ӧ����Ӧ�� userID ��¼ */	
	bool CheckUserClient(const CClientIDType& clientID,const CUserIDType& userID);

	void * fromUserGetInvestor(const CBrokerIDType& brokerID,const CUserIDType& userID);
	
	/* userID �� ClientID*/
	void * fromUserGetInvestorFee(const CBrokerIDType& brokerID,const CUserIDType& userID,const CExchangeIDType& exchangeID);

	void * fromUserGetInvestorMargin(const CBrokerIDType& brokerID,const CUserIDType& userID,const CExchangeIDType& exchangeID);
	
	/* InvestorID �� ClientID*/
	void * fromUserGetInvestorFee(const CBrokerIDType& brokerID,const CInvestorIDType& investorID,const CExchangeIDType& exchangeID);

	void * fromUserGetInvestorMargin(const CBrokerIDType& brokerID,const CInvestorIDType& investorID,const CExchangeIDType& exchangeID);
	
	void fromUserGetInvestors(const CBrokerIDType& brokerID,const CUserIDType& userID,InvestorIDVector& vInvestorID);	

	void fromInvestorsGetAccount(const CBrokerIDType& brokerID, const CInvestorIDType& investorID, AccountIDVector& vAccountID);
						
	CMemoryDB *m_DB;
	CErrorEngine *m_ErrorEngine;
	/// ���� bool m_PartQueryMBL;
	

	
	// ��Ҫ�������vInvestorID������Ϊ CInvestorAccountInvestorIDPredict�Ĳ��������ã������Predict ��ServiceXTPLink
	// ��һ�㻹Ҫ�õ�������ҪvInvestorID ������ȫ�ֱ����������þֲ�������
	InvestorIDVector vInvestorID;
	AccountIDVector vAccountID;
};

#endif
