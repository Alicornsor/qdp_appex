#ifndef CFutureMoneyPosition_H
#define CFutureMoneyPosition_H
#include "system.h"
#include "MoneyPosition.h"

class CFutureMoneyPosition : public CMoneyPosition
{
public:
	///构造函数
	///@param	pDB	本实现使用的内存数据库
	///@param	pErrorEngine	用于报错的错误引擎
	///@param   pConfig 配置文件
	CFutureMoneyPosition(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig);
	virtual ~CFutureMoneyPosition();
    
	
    ///冻结资金
	///@param	pPreOrder  报单
	///@param	pMoney	记录冻结的保证金和手续费
    ///@param	pTransaction 事务标志
    virtual bool OrderInsertMoneyFrozen(CWriteablePreOrder* pPreOrder, CWriteableIndexPreOrder* pIndexPreOrder,CMoneyField* pMoneyField,CTransaction* pTransaction, bool bRedo=false);
		
	///错单解冻资金
	///@param   pInvestorAccount 对应资金账户指针
	///@param	pInputOrder  报单
	///@param	pTransaction 事务标志
    virtual bool MoneyUnFrozen(CPreOrder* pPreOrder,CTransaction* pTransaction);
	
	//撤单解冻资金  
    ///@param   pInvestorAccount 对应资金账户指针
	///@param   pOrder     撤单对应的订单   
	///@param	pOrderActionField  撤单应答域
	///@param	pTransaction 事务标志
    virtual bool MoneyUnFrozen(COrder* pOrder,CTransaction* pTransaction);

	///报单冻结持仓、平仓冻结平仓
	///@param	pPreOrder  报单
	///@param	pTransaction 事务标志
    virtual bool OrderInsertPositionFrozen(CWriteablePreOrder* pPreOrder, CWriteableIndexPreOrder* pIndexPreOrder,CMoneyField* pMoneyField,CTransaction* pTransaction, bool bRedo=false);
	
	///根据释放手数失效冻结持仓
	///@paramp  pPreOrder   报单
	//@param	pTransaction 事务标志
    virtual bool PositionUnFrozen(CPreOrder* pPreOrder,CTransaction* pTransaction);
	
	///根据释放手数失效冻结持仓
	///@paramp  pPreOrder   报单
	//@param	pTransaction 事务标志
    virtual bool PositionUnFrozen(COrder* pOrder,CTransaction* pTransaction);
	
    ///成交释放资金
	///@param   pInvestorAccount 对应资金账户指针
	///@param   pOrder  报单
	///@param	pTrade  成交
	///@param   pReleaseMargin 释放的资金
	///@param	pTransaction 事务标志
    virtual bool TradeMoneyUpdate(CWriteableOrder* pOrder,CWriteableTrade* pTrade, CMoneyField* pMoneyField,CTransaction* pTransaction);
 

    ///成交更新持仓
	///@param	pInvestorPosition  对应持仓
	///@param   pOrder
	///@param   pTrade   成交
	///@param	pTransaction 事务标志
    virtual bool TradePositionUpdate(COrder* pOrder,CWriteableTrade* pTrade,CMoneyField* pMoneyField,CTransaction* pTransaction);

protected:
	
	bool TradeMoneyTradeWithNet(CIndexPreOrder *pIndexPreOrder,CWriteableIndexPreOrder *pWtbIndexPreOrder,CWriteableOrder* pOrder,CWriteableTrade* pTrade,CMoneyField* pMoneyField,CTransaction* pTransaction);
	
	bool TradeMoneyTradeWithGross(CIndexPreOrder *pIndexPreOrder,CWriteableIndexPreOrder *pWtbIndexPreOrder,CWriteableOrder* pOrder,CWriteableTrade* pTrade,CMoneyField* pMoneyField,CTransaction* pTransaction);
	

};

#endif