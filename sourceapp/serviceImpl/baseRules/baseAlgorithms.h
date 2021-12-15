/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CInitServiceImpl.h
///@brief��������CInitServiceImpl
///@history 
///20060113	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CBaseAlgorithms_H
#define CBaseAlgorithms_H

#include "BaseDataStruct.h"
#include "CMemoryDB.h"
#include "XtpData.h"
#include "XTPPackage.h"
#include "CErrorEngine.h"

typedef vector<CInvestorIDType>  InvestorIDVector;

class CBaseAlgorithms
{

public:
	///���캯��
	///@param	pDB	��ʵ��ʹ�õ��ڴ����ݿ�
	///@param	pErrorEngine	���ڱ���Ĵ�������
    CBaseAlgorithms();
	virtual ~CBaseAlgorithms();

	CInvestorMargin *getInvestorMargin(CMemoryDB *m_pDB,CInstrument *pInstrument,
									   const CReadOnlyBrokerIDType &BrokerID,
									   const CReadOnlyInvestorIDType &InvestorID, 
									   const CReadOnlyHedgeFlagType&  HedgeFlag);

	vector<CInvestorMargin*> getInvestorMargin(CMemoryDB *m_pDB,const CExchangeIDType& ExchangeID,
								const CProductIDType& ProductID,
								const CInstrumentIDType& InstrumentID, 
								const CBrokerIDType&  BrokerID,
								const CInvestorIDType&  InvestorID);


	CInvestorFee *getInvestorFee(CMemoryDB *m_pDB,CInstrument *pInstrument,
									   const CReadOnlyBrokerIDType&  BrokerID,
									   const CReadOnlyInvestorIDType&  InvestorID,  
									   const CReadOnlyHedgeFlagType&  HedgeFlag);

	//�õ����㱣֤����������Լ�Ȩ����ʱ��ʹ�õļ۸�
	CPriceTickType GetValuePrice(COrderPriceTypeType OrderPriceType,
									   CPriceType LimitPrice,
									   CInstrument *pInstrument);

	void GetMargin(CVolumeType Volume,
									   CPriceType basePrice,
									   CDirectionType Direction,
									   COffsetFlagType OffsetFlag,
									   CVolumeMultipleType VolumeMultiple,
									   CInvestorMargin *pInvestorMargin,
									   CMoneyField*  theMoneyField);

	void GetFee(CVolumeType Volume,
									   CPriceType basePrice,
									   CDirectionType Direction,
									   COffsetFlagType OffsetFlag,
									   CVolumeMultipleType VolumeMultiple,
									   CInvestorFee *pInvestorFee,
									   CMoneyField*  theMoneyField);

	CMoneyType GetFee(CVolumeType Volume,
									   CPriceType basePrice,
									   CDirectionType Direction,
									   COffsetFlagType OffsetFlag,
									   CVolumeMultipleType VolumeMultiple,
									   CInvestorFee *pInvestorFee);

	void GetPremium(CVolumeType Volume,
									   CPriceType basePrice,
									   CDirectionType Direction,
									   CVolumeMultipleType VolumeMultiple,
									   CMoneyField*  theMoneyField);

	CInvestorAccount *getInvestorAccount(CMemoryDB *m_pDB,CInstrument *pInstrument,const CReadOnlyBrokerIDType BrokerID,const CReadOnlyInvestorIDType InvestorID);
	void ChangeBalanceAndAvailable(CWriteableInvestorAccount* pWtbInvestorAccount);
//	CTradingRightType getInvestorTradingRight(CMemoryDB *m_pDB,CBrokerIDType BrokerID,CExchangeIDType ExchangeID, CInvestorIDType InvestorID,CInstrumentIDType InstrumentID,CProductIDType ProductID);
//	bool RightCheck(CErrorEngine *pErrorEngine,CTradingRightType TradingRightType,COffsetFlagType OffsetFlag);
	//���㸡��ӯ��
	bool CalcPositionProfit(CWriteableInvestorAccount *pInvestorAccount,CWriteableInvestorPosition *pInvestorPosition,CInstrument *pInstrument);

	bool RightCheck(CErrorEngine *pErrorEngine,CTradingRightType TradingRightType,COffsetFlagType OffsetFlag);

	CInvestorMargin *getInvestorStockMargin(CMemoryDB *m_pDB,CInstrument *pInstrument,const CReadOnlyBrokerIDType&  BrokerID,const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag);
	CInvestorFee *getInvestorStockFee(CMemoryDB *m_pDB,CInstrument *pInstrument,const CReadOnlyBrokerIDType&  BrokerID,const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag);
	
	CPriceTickType GetStockValuePrice(CWriteablePreOrder* pOrder, CInstrument *pInstrument);

	CVolumeType GetStockValueVolume(CWriteablePreOrder* pOrder, CInstrument *pInstrument);

	void GetStockYhs(CPriceType basePrice,
									   CVolumeType baseVolume,
									   CWriteablePreOrder* pOrder,
									   CInvestorMargin *pInvestorMargin,
									   CInstrument *pInstrument,
									   CMoneyField*  theMoneyField);

	void GetStockSxf(CPriceType basePrice,
									   CVolumeType baseVolume,
									   CWriteablePreOrder* pOrder,
									   CInvestorFee *pInvestorFee,
									   CInstrument *pInstrument,
									   CMoneyField*  theMoneyField);

	void GetStockGhf(CPriceType basePrice,
									   CVolumeType baseVolume,
									   CWriteablePreOrder* pOrder,
									   CInvestorFee *pInvestorFee,
									   CInstrument *pInstrument,
									   CMoneyField*  theMoneyField);

	//����user���ڵ�Invesors
	void fromUserGetInvestors(CMemoryDB *m_pDB,const CBrokerIDType& brokerID,const CUserIDType& userID,InvestorIDVector& vInvestorID);
	
	///����û�Ͷ���߹�ϵ���鿴����Ĳ����Ƿ��ж�Ӧ�ļ�¼
	///���м�¼���򷵻�ture�����򣬷���false��
	///@param	brokerID	���͹�˾���
	///@param	userID		�����û�����
	///@param	investorID	Ͷ���߱��
	bool CheckUserInvestor(CMemoryDB *m_pDB,const CBrokerIDType& brokerID,const CUserIDType& userID,const CInvestorIDType& investorID);


	CInvestorPosition* GetInvestorPositon(CMemoryDB *m_pDB,CDirectionType Direction, 
											COffsetFlagType OffsetFlag, 
											CBrokerIDType BrokerID, 
											CExchangeIDType ExchangeID, 
											CInvestorIDType InvestorID,
											CInstrumentIDType InstrumentID,
											CHedgeFlagType HedgeFlag,
											CTransaction *pTransaction);

	double GetPremium(CVolumeType baseVolume,
										CPriceType basePrice,
										CDirectionType Direction,
									    CVolumeMultipleType  VolumeMultiple);

	CInvestorOptionFee *getInvestorOptionFee(CMemoryDB *m_pDB,CInstrument *pInstrument,
										const CReadOnlyBrokerIDType&  BrokerID,
										const CReadOnlyInvestorIDType&  InvestorID);

	void GetOptionFee(CVolumeType Volume,
										CPriceType basePrice,
										CDirectionType Direction,
										COffsetFlagType OffsetFlag,
										CVolumeMultipleType VolumeMultiple,
										CInvestorOptionFee *pInvestorOptionFee,
									    CMoneyField*  theMoneyField);

	CMoneyType GetOptionFee(CVolumeType Volume,
										CPriceType basePrice,
										CDirectionType Direction,
										COffsetFlagType OffsetFlag,
										CVolumeMultipleType VolumeMultiple,
										CInvestorOptionFee *pInvestorOptionFee);



	void GetStrikeFee(CVolumeType Volume,
										CPriceType basePrice,
										CVolumeMultipleType VolumeMultiple,
										CInvestorOptionFee *pInvestorOptionFee,
										CMoneyField*  theMoneyField);

};

#endif
