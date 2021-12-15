#ifndef CMoneyPosition_H
#define CMoneyPosition_H

#include "errorDefine.h"
#include "CMemoryDB.h"
#include "Flow.h"
#include "XTPPackage.h"
#include "XtpPackageDesc.h"
#include "UFEntityCopy.h"
#include "baseAlgorithms.h"

#define CCY_RMB "1"				    //�����
#define CCY_USDOLLOR "2"			//��Ԫ

class CInitAccountTrigger:public CDataSyncStatusActionTrigger
{
public:
	///���췽��
	///@param	pDB	ʹ�õ��ڴ����ݿ�
	///@param	useCloseProfit	�Ƿ����ƽ��ӯ��
	CInitAccountTrigger(CMemoryDB *pDB)
	{
		m_DB=pDB;		
	}
	
	///���º󴥷�
	///@param	pSGDataSyncStatus	��ˢ�µ�CSGDataSyncStatus
	virtual void afterUpdate(CDataSyncStatus *pDataSyncStatus);
private:
	///ʹ�õ��ڴ����ݿ�
	CMemoryDB *m_DB;
};

class CMoneyPosition
{

public:
	///���캯��
	///@param	pDB	��ʵ��ʹ�õ��ڴ����ݿ�
	///@param	pErrorEngine	���ڱ���Ĵ�������
	///@param   pConfig �����ļ�
	CMoneyPosition(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig);
    
    ///�����ʽ�
	///@param	pPreOrder  ����
	///@param	pMoney	��¼����ı�֤���������
    ///@param	pTransaction �����־
    virtual bool OrderInsertMoneyFrozen(CWriteablePreOrder* pPreOrder, CWriteableIndexPreOrder* pIndexPreOrder,CMoneyField* pMoneyField,CTransaction* pTransaction, bool bRedo=false) = 0;
		
	///���ⶳ�ʽ�
	///@param   pInvestorAccount ��Ӧ�ʽ��˻�ָ��
	///@param	pInputOrder  ����
	///@param	pTransaction �����־
    virtual bool MoneyUnFrozen(CPreOrder* pPreOrder,CTransaction* pTransaction) = 0;

	
	//�����ⶳ�ʽ�  
    ///@param   pInvestorAccount ��Ӧ�ʽ��˻�ָ��
	///@param   pOrder     ������Ӧ�Ķ���   
	///@param	pOrderActionField  ����Ӧ����
	///@param	pTransaction �����־
    virtual bool MoneyUnFrozen(COrder* pOrder,CTransaction* pTransaction) = 0;

	///��������ֲ֡�ƽ�ֶ���ƽ��
	///@param	pPreOrder  ����
	///@param	pTransaction �����־
    virtual bool OrderInsertPositionFrozen(CWriteablePreOrder* pPreOrder, CWriteableIndexPreOrder* pIndexPreOrder,CMoneyField* pMoneyField,CTransaction* pTransaction, bool bRedo=false) = 0;

	///�����ͷ�����ʧЧ����ֲ�
	///@paramp  pPreOrder   ����
	//@param	pTransaction �����־
    virtual bool PositionUnFrozen(CPreOrder* pPreOrder,CTransaction* pTransaction) = 0;

	///�����ͷ�����ʧЧ����ֲ�
	///@paramp  pPreOrder   ����
	//@param	pTransaction �����־
    virtual bool PositionUnFrozen(COrder* pOrder,CTransaction* pTransaction) = 0;

    ///�ɽ��ͷ��ʽ�
	///@param   pInvestorAccount ��Ӧ�ʽ��˻�ָ��
	///@param   pOrder  ����
	///@param	pTrade  �ɽ�
	///@param   pReleaseMargin �ͷŵ��ʽ�
	///@param	pTransaction �����־
    virtual bool TradeMoneyUpdate(CWriteableOrder* pOrder,CWriteableTrade* pTrade, CMoneyField* pMoneyField,CTransaction* pTransaction) = 0;
 

    ///�ɽ����³ֲ�
	///@param	pInvestorPosition  ��Ӧ�ֲ�
	///@param   pOrder
	///@param   pTrade   �ɽ�
	///@param	pTransaction �����־
    virtual bool TradePositionUpdate(COrder* pOrder,CWriteableTrade* pTrade,CMoneyField* pMoneyField,CTransaction* pTransaction) = 0;
public:
	
    ///��������ʽ�
	///@paramp  theWriteableInvestorAccount   ��д�ʽ��˻�
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