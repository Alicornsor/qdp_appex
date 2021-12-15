/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file CInitServiceImpl.h
///@brief定义了类CInitServiceImpl
///@history 
///20060113	xuzh		创建该文件
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
	///构造函数
	///@param	pDB	本实现使用的内存数据库
	///@param	pErrorEngine	用于报错的错误引擎
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

	//得到计算保证金和手续费以及权利金时的使用的价格
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
	//计算浮动盈亏
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

	//查找user对于的Invesors
	void fromUserGetInvestors(CMemoryDB *m_pDB,const CBrokerIDType& brokerID,const CUserIDType& userID,InvestorIDVector& vInvestorID);
	
	///检查用户投资者关系表，查看输入的参数是否有对应的记录
	///若有记录，则返回ture；否则，返回false。
	///@param	brokerID	经纪公司编号
	///@param	userID		交易用户代码
	///@param	investorID	投资者编号
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
