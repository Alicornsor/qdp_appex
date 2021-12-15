#ifndef CFutureMoneyPosition_H
#define CFutureMoneyPosition_H
#include "system.h"
#include "MoneyPosition.h"

class CFutureMoneyPosition : public CMoneyPosition
{
public:
	///���캯��
	///@param	pDB	��ʵ��ʹ�õ��ڴ����ݿ�
	///@param	pErrorEngine	���ڱ���Ĵ�������
	///@param   pConfig �����ļ�
	CFutureMoneyPosition(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig);
	virtual ~CFutureMoneyPosition();
    
	
    ///�����ʽ�
	///@param	pPreOrder  ����
	///@param	pMoney	��¼����ı�֤���������
    ///@param	pTransaction �����־
    virtual bool OrderInsertMoneyFrozen(CWriteablePreOrder* pPreOrder, CWriteableIndexPreOrder* pIndexPreOrder,CMoneyField* pMoneyField,CTransaction* pTransaction, bool bRedo=false);
		
	///���ⶳ�ʽ�
	///@param   pInvestorAccount ��Ӧ�ʽ��˻�ָ��
	///@param	pInputOrder  ����
	///@param	pTransaction �����־
    virtual bool MoneyUnFrozen(CPreOrder* pPreOrder,CTransaction* pTransaction);
	
	//�����ⶳ�ʽ�  
    ///@param   pInvestorAccount ��Ӧ�ʽ��˻�ָ��
	///@param   pOrder     ������Ӧ�Ķ���   
	///@param	pOrderActionField  ����Ӧ����
	///@param	pTransaction �����־
    virtual bool MoneyUnFrozen(COrder* pOrder,CTransaction* pTransaction);

	///��������ֲ֡�ƽ�ֶ���ƽ��
	///@param	pPreOrder  ����
	///@param	pTransaction �����־
    virtual bool OrderInsertPositionFrozen(CWriteablePreOrder* pPreOrder, CWriteableIndexPreOrder* pIndexPreOrder,CMoneyField* pMoneyField,CTransaction* pTransaction, bool bRedo=false);
	
	///�����ͷ�����ʧЧ����ֲ�
	///@paramp  pPreOrder   ����
	//@param	pTransaction �����־
    virtual bool PositionUnFrozen(CPreOrder* pPreOrder,CTransaction* pTransaction);
	
	///�����ͷ�����ʧЧ����ֲ�
	///@paramp  pPreOrder   ����
	//@param	pTransaction �����־
    virtual bool PositionUnFrozen(COrder* pOrder,CTransaction* pTransaction);
	
    ///�ɽ��ͷ��ʽ�
	///@param   pInvestorAccount ��Ӧ�ʽ��˻�ָ��
	///@param   pOrder  ����
	///@param	pTrade  �ɽ�
	///@param   pReleaseMargin �ͷŵ��ʽ�
	///@param	pTransaction �����־
    virtual bool TradeMoneyUpdate(CWriteableOrder* pOrder,CWriteableTrade* pTrade, CMoneyField* pMoneyField,CTransaction* pTransaction);
 

    ///�ɽ����³ֲ�
	///@param	pInvestorPosition  ��Ӧ�ֲ�
	///@param   pOrder
	///@param   pTrade   �ɽ�
	///@param	pTransaction �����־
    virtual bool TradePositionUpdate(COrder* pOrder,CWriteableTrade* pTrade,CMoneyField* pMoneyField,CTransaction* pTransaction);

protected:
	
	bool TradeMoneyTradeWithNet(CIndexPreOrder *pIndexPreOrder,CWriteableIndexPreOrder *pWtbIndexPreOrder,CWriteableOrder* pOrder,CWriteableTrade* pTrade,CMoneyField* pMoneyField,CTransaction* pTransaction);
	
	bool TradeMoneyTradeWithGross(CIndexPreOrder *pIndexPreOrder,CWriteableIndexPreOrder *pWtbIndexPreOrder,CWriteableOrder* pOrder,CWriteableTrade* pTrade,CMoneyField* pMoneyField,CTransaction* pTransaction);
	

};

#endif