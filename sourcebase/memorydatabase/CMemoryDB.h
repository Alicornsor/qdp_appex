/////////////////////////////////////////////////////////////////////////
///@system ִ������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CMemoryDB.h
///@brief��������CMemoryDB
///@history 
///20121227	hwp	�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CMEMORYDB_H
#define CMEMORYDB_H

#include "CBaseObject.h"
#include "CConfig.h"
#include "BaseDataStruct.h"
#include "databaseFactories.h"
#include "databaseIterators.h"

struct TableStruct
{
	char tableName[100];
	int  reuseID;
};

/*** SIR XXXXX BEGIN ***/
typedef struct MemTableItemInfoTag
{
	int InvestorAccountDepositCurrentMaxItem;
}MemTableItemInfoT, *pMemTableItemInfoT;
/*** SIR XXXXX END ***/

/////////////////////////////////////////////////////////////////////////
///CMemoryDB��һ���ڴ����ݿ��࣬���������ж���ı���Ϣ
///@author	xuzh
///@version	1.0,20050824
/////////////////////////////////////////////////////////////////////////
class CMemoryDB : public CBaseObject
{
public:
	///���췽���������ڴ����ݿ�
	CMemoryDB(void);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CMemoryDB(void);
	
	virtual int isA(char *objectType);
	virtual char *getType(void);
	virtual void output(CLogger *pLogger,int indent=0);

	///���г�ʼ������
	///@param	pConfig	��ʼ��ʱʹ�õ�������Ϣ
	///@return	1��ʾ�ɹ���0��ʾʧ��
	virtual int init(CConfig *pConfig,IMemoryAllocator *pAllocator=NULL,bool reuse=false);
	
	///�����������빤��
	///@param	pConfig	��������ʱʹ�õ�������Ϣ
	///@return	1��ʾ�ɹ���0��ʾʧ��
	virtual int load(CConfig *pConfig);

	///�������ݴ洢����
	///@param	pConfig	��������ʱʹ�õ�������Ϣ
	///@return	1��ʾ�ɹ���0��ʾʧ��
	virtual int save(CConfig *pConfig);
	
	///������е�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	virtual void clear(void);
	
	///����������������
	virtual void linkAll(void);
	
	
	
	///����ͬ��״̬���
	CDataSyncStatusFactory *m_DataSyncStatusFactory;
	
	///QDP״̬���
	CSystemStatusFactory *m_SystemStatusFactory;
	
	///����������
	COrderActionFactory *m_OrderActionFactory;
	
	///ί�б��
	COrderFactory *m_OrderFactory;
	
	///�ɽ����
	CTradeFactory *m_TradeFactory;
	
	///Ԥί�б��
	CPreOrderFactory *m_PreOrderFactory;
	
	///����Ԥί�б��
	CIndexPreOrderFactory *m_IndexPreOrderFactory;
	
	///�ֱֲ��
	CInvestorPositionFactory *m_InvestorPositionFactory;
	
	///�˻�ʵʱ�ʽ���
	CInvestorAccountFactory *m_InvestorAccountFactory;
	
	///�˻�ʵʱ�������
	CInvestorAccountDepositFactory *m_InvestorAccountDepositFactory;
	
	///���������
	CExchangeFactory *m_ExchangeFactory;
	
	///�µ�ϯλ���
	CSeatFactory *m_SeatFactory;
	
	///�ڻ���Լ���
	CInstrumentFactory *m_InstrumentFactory;
	
	///�ڻ���Ϻ�Լ��ϸ���
	CCmbInstrumentDetailFactory *m_CmbInstrumentDetailFactory;
	
	///�������ͻ�������
	CClientTradingIDFactory *m_ClientTradingIDFactory;
	
	///Ͷ������Ϣ���
	CInvestorFactory *m_InvestorFactory;
	
	///�ͻ��ڻ���֤���ʱ��
	CInvestorMarginFactory *m_InvestorMarginFactory;
	
	///�ͻ��������ʱ��
	CInvestorFeeFactory *m_InvestorFeeFactory;
	
	///�û����
	CUserFactory *m_UserFactory;
	
	///�û�Ͷ���߹�ϵ���
	CUserInvestorFactory *m_UserInvestorFactory;
	
	///�����
	COrderInsertFailedFactory *m_OrderInsertFailedFactory;
	
	///�û�����Ȩ�ޱ��
	CUserTradingRightFactory *m_UserTradingRightFactory;
	
	///��ǰʱ���
	CCurrentTimeFactory *m_CurrentTimeFactory;
	
	///����Ա���߻Ự��
	CUserSessionFactory *m_UserSessionFactory;
	
	///��󱾵ر����ű�
	CMaxLocalIDFactory *m_MaxLocalIDFactory;
	
	///�û����ر����ű�
	CBrkUserIDLocalIDFactory *m_BrkUserIDLocalIDFactory;
	
	///�ͻ���Լ��ֱֲ��
	CPartClientInsGroupPositionFactory *m_PartClientInsGroupPositionFactory;
	
	///���ױ�����ϱ�֤�����ͱ�
	CClientMarginCombTypeFactory *m_ClientMarginCombTypeFactory;
	
	///��Լ�ͺ�Լ���ϵ��
	CInstrumentGroupFactory *m_InstrumentGroupFactory;
	
	///�������ӷ��ʱ��
	CSGEDeferRateFactory *m_SGEDeferRateFactory;
	
	///Ͷ���߽���Ȩ�ޱ��
	CInvestorTradingRightFactory *m_InvestorTradingRightFactory;
	
	///����ԱIP��ַ��
	CUserIPFactory *m_UserIPFactory;
	
	///�ͻ���Ȩ�������ʱ��
	CInvestorOptionFeeFactory *m_InvestorOptionFeeFactory;
	
	///ʵʱ������
	CMarketDataFactory *m_MarketDataFactory;
	
	///ί���ӳٱ��
	COrderDelayFactory *m_OrderDelayFactory;
	
	///QDPϵͳ��Ϣ��
	CSystemInfoFactory *m_SystemInfoFactory;
	

/*** SIR XXXXX BEGIN ***/
	MemTableItemInfoT m_memTableItemInfo;
/*** SIR XXXXX END ***/

private:
	CFixMem *pMem;		///������ű����Ϣ
};

#endif
