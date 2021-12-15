#ifndef CMoneyPosition_H
#define CMoneyPosition_H

#include "errorDefine.h"
#include "CMemoryDB.h"
#include "Flow.h"
#include "XTPPackage.h"
#include "XtpPackageDesc.h"
#include "UFEntityCopy.h"
#include "baseAlgorithms.h"

#define CCY_RMB "1"				    //人民币
#define CCY_USDOLLOR "2"			//美元

class CInitAccountTrigger:public CDataSyncStatusActionTrigger
{
public:
	///构造方法
	///@param	pDB	使用的内存数据库
	///@param	useCloseProfit	是否计算平仓盈亏
	CInitAccountTrigger(CMemoryDB *pDB)
	{
		m_DB=pDB;		
	}
	
	///更新后触发
	///@param	pSGDataSyncStatus	被刷新的CSGDataSyncStatus
	virtual void afterUpdate(CDataSyncStatus *pDataSyncStatus);
private:
	///使用的内存数据库
	CMemoryDB *m_DB;
};

class CMoneyPosition
{

public:
	///构造函数
	///@param	pDB	本实现使用的内存数据库
	///@param	pErrorEngine	用于报错的错误引擎
	///@param   pConfig 配置文件
	CMoneyPosition(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig);
    
    ///冻结资金
	///@param	pPreOrder  报单
	///@param	pMoney	记录冻结的保证金和手续费
    ///@param	pTransaction 事务标志
    virtual bool OrderInsertMoneyFrozen(CWriteablePreOrder* pPreOrder, CWriteableIndexPreOrder* pIndexPreOrder,CMoneyField* pMoneyField,CTransaction* pTransaction, bool bRedo=false) = 0;
		
	///错单解冻资金
	///@param   pInvestorAccount 对应资金账户指针
	///@param	pInputOrder  报单
	///@param	pTransaction 事务标志
    virtual bool MoneyUnFrozen(CPreOrder* pPreOrder,CTransaction* pTransaction) = 0;

	
	//撤单解冻资金  
    ///@param   pInvestorAccount 对应资金账户指针
	///@param   pOrder     撤单对应的订单   
	///@param	pOrderActionField  撤单应答域
	///@param	pTransaction 事务标志
    virtual bool MoneyUnFrozen(COrder* pOrder,CTransaction* pTransaction) = 0;

	///报单冻结持仓、平仓冻结平仓
	///@param	pPreOrder  报单
	///@param	pTransaction 事务标志
    virtual bool OrderInsertPositionFrozen(CWriteablePreOrder* pPreOrder, CWriteableIndexPreOrder* pIndexPreOrder,CMoneyField* pMoneyField,CTransaction* pTransaction, bool bRedo=false) = 0;

	///根据释放手数失效冻结持仓
	///@paramp  pPreOrder   报单
	//@param	pTransaction 事务标志
    virtual bool PositionUnFrozen(CPreOrder* pPreOrder,CTransaction* pTransaction) = 0;

	///根据释放手数失效冻结持仓
	///@paramp  pPreOrder   报单
	//@param	pTransaction 事务标志
    virtual bool PositionUnFrozen(COrder* pOrder,CTransaction* pTransaction) = 0;

    ///成交释放资金
	///@param   pInvestorAccount 对应资金账户指针
	///@param   pOrder  报单
	///@param	pTrade  成交
	///@param   pReleaseMargin 释放的资金
	///@param	pTransaction 事务标志
    virtual bool TradeMoneyUpdate(CWriteableOrder* pOrder,CWriteableTrade* pTrade, CMoneyField* pMoneyField,CTransaction* pTransaction) = 0;
 

    ///成交更新持仓
	///@param	pInvestorPosition  对应持仓
	///@param   pOrder
	///@param   pTrade   成交
	///@param	pTransaction 事务标志
    virtual bool TradePositionUpdate(COrder* pOrder,CWriteableTrade* pTrade,CMoneyField* pMoneyField,CTransaction* pTransaction) = 0;
public:
	
    ///计算可用资金
	///@paramp  theWriteableInvestorAccount   可写资金账户
    static void ChangeBalanceAndAvailable(CWriteableInvestorAccount* pWtbInvestorAccount);

protected:
	CConfig      *m_pConfig;
	CMemoryDB    *m_pDB;
  	CErrorEngine *m_pErrorEngine;
	static CInitAccountTrigger *m_initTrigger; 
	static int initCount;
	CBaseAlgorithms baseAlgorithm;
};

#endif